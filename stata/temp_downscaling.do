
clear
set more off
ssc install tsegen, replace

//  Set data folder: Set Working Directory where file is!
pwd
cd /Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/stata
local datafolder = "../../EGGW Replication/Data"

* Estimates the linear downscaling from global to local temperature, given by the function $g(\cdot)$, as described in Section 3.4 and Appendix D

********************************************************************************
* Prepare data

* Read geographic data
clear
import delimited "`datafolder'/geo_data.csv", clear 
capture rename ïlat lat

compress
save "`datafolder'/derived/geo_data.dta", replace


* Read global temperature
import delimited "`datafolder'/global_temp.csv", clear

capture rename ïyear year
sum temp_lndavg if year>=1950 & year<=1981
scalar mean_temp_global = r(mean)
qui gen temp_global_anom = temp_lndavg - mean_temp_global
rename temp_lndavg temp_global

qui gen gg = "_1y_"
qui gen mm = "m"
qui gegen date = concat(gg month mm)
qui drop gg mm month

greshape wide temp_global temp_global_anom, i(year) j(date) string

qui gen temp_global_1y = 0
qui gen temp_global_anom_1y = 0
forvalues i=1/12 {
	qui replace temp_global_1y = temp_global_1y + temp_global_1y_`i'm/12
	qui replace temp_global_anom_1y = temp_global_anom_1y + temp_global_anom_1y_`i'm/12
}

tsset year

foreach y of numlist 10 {
	local j = `y'-1
	
	qui tsegen temp_global_`y'y = rowtotal(L(0/`j').temp_global_1y)
	qui replace temp_global_`y'y = temp_global_`y'y/`y'
	
	qui tsegen temp_global_anom_`y'y = rowtotal(L(0/`j').temp_global_anom_1y)
	qui replace temp_global_anom_`y'y = temp_global_anom_`y'y/`y'
}

* Save data
compress
save "`datafolder'/derived/global_temp.dta", replace

* Read climatology
import delimited "`datafolder'/climatology.csv", clear 

compress
save "`datafolder'/derived/climatology.dta", replace


* Read gridded temperature
clear
import delimited "`datafolder'/temp_data.csv", clear 

qui merge m:1 lat lon using "`datafolder'/derived/climatology.dta", nogen

forvalues m=1/12 {
	qui gen temp_anom_1y_`m'm = temp_1y_`m'm - climatology_`m'm
}

qui gen temp_1y = 0
qui gen temp_anom_1y = 0
qui gen climatology_1y = 0
forvalues m=1/12 {
	qui replace temp_1y = temp_1y + temp_1y_`m'm/12
	qui replace temp_anom_1y = temp_anom_1y + temp_anom_1y_`m'm/12
	qui replace climatology_1y = climatology_1y + climatology_`m'm/12
}

qui gegen cell = group(lat lon)
qui xtset cell year

local anom_name "temp temp_anom"
foreach y of numlist 10 {
	local j = `y'-1
	foreach a of local anom_name {
	
		qui tsegen `a'_`y'y = rowtotal(L(0/`j').`a'_1y)
		qui replace `a'_`y'y = `a'_`y'y/`y'
	
	}
}

* Merge geographic data
qui merge m:1 lat lon using "`datafolder'/derived/geo_data.dta", nogen

* Merge geographic data global temperature
qui merge m:1 year using "`datafolder'/derived/global_temp.dta", keep(3) nogen

* Set period
qui drop if year < 1980 
qui sum year
local year_max = r(max)
qui gen weight = 1/(`year_max' - year + 1)

* Generate regressors for Chebyshev regression
qui gen lat_che = lat/90
qui gen lon_che = lon/180
local geo_name "elev dist2coast dist2ocean dist2water albedo ice veg"
foreach g of local geo_name {
	qui sum `g'
	qui scalar `g'_min = r(min)
	qui scalar `g'_max = r(max)
	qui gen `g'_che = (`g' - (`g'_min + `g'_max)/2)
	qui sum `g'_che
	qui scalar `g'_che_max = r(max)
	qui replace `g'_che = `g'_che/`g'_che_max
	qui drop `g'
}

* Generate regressors for Chebyshev regression in anomalies
local geo_full_name "lat lon elev dist2coast dist2ocean dist2water albedo ice veg"

foreach y of numlist 1 10 {
	forvalues i=1/10 {

		foreach g of local geo_full_name {
			qui gen `g'_che`i'_temp_anom_`y'y = cos(`i'*acos(`g'_che))*temp_global_anom_`y'y
		}

		qui gen lat_lon_che`i'_temp_anom_`y'y = cos(`i'*acos(lat_che))*cos(`i'*acos(lon_che))*temp_global_anom_`y'y
	}
}

drop temp_1y_* climatology* temp_anom_1y_1m-temp_anom_1y_12m temp_global_1y_* temp_global_anom_1y_* rough std_elev land_type cell temp_global_1y-temp_global_anom_10y

compress
save "`datafolder'/derived/downscaling_reg.dta", replace


********************************************************************************
* Perform temperature downscaling

use "`datafolder'/derived/downscaling_reg.dta", clear

foreach i of numlist 1 10 {

	* Unweighted regression in anomalies
	reg temp_anom_`i'y lat_che1_temp_anom_`i'y-lat_lon_che10_temp_anom_`i'y, nocons robust
	matrix aux = e(b)
	matrix coeff_simple_`i'y = aux[1,1..100]

	* Weighted regression in anomalies
	reg temp_anom_`i'y lat_che1_temp_anom_`i'y-lat_lon_che10_temp_anom_`i'y [aweight=weight], nocons robust
	matrix aux = e(b)
	matrix coeff_weight_`i'y = aux[1,1..100]

}

* Create temperature scalers
keep if year == 2000
local scaler_name "simple weight" 

foreach s of local scaler_name {
	foreach y of numlist 1 10 {

		gen scaler_`s'_`y'y = 0
		forvalues i=1/10 {

			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(lat_che))*coeff_`s'_`y'y[1,10*(`i'-1)+1]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(lon_che))*coeff_`s'_`y'y[1,10*(`i'-1)+2]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(elev_che))*coeff_`s'_`y'y[1,10*(`i'-1)+3]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(dist2coast_che))*coeff_`s'_`y'y[1,10*(`i'-1)+4]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(dist2ocean_che))*coeff_`s'_`y'y[1,10*(`i'-1)+5]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(dist2water_che))*coeff_`s'_`y'y[1,10*(`i'-1)+6]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(albedo_che))*coeff_`s'_`y'y[1,10*(`i'-1)+7]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(ice_che))*coeff_`s'_`y'y[1,10*(`i'-1)+8]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(veg_che))*coeff_`s'_`y'y[1,10*(`i'-1)+9]
			qui replace scaler_`s'_`y'y = scaler_`s'_`y'y + cos(`i'*acos(lat_che))*cos(`i'*acos(lon_che))*coeff_`s'_`y'y[1,10*(`i'-1)+10]

		}

		qui replace scaler_`s'_`y'y = . if scaler_`s'_`y'y < 0

	}
}

keep lat lon scaler_simple_1y scaler_simple_10y scaler_weight_1y scaler_weight_10y
export delimited using "`datafolder'/derived/scaler_temp.csv", replace

