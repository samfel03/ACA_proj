
clear
set more off
ssc install tsegen, replace
ssc install reghdfe
ssc install gtools
net install acreg, from(https://acregstata.weebly.com/uploads/2/9/1/6/29167217) replace

* Estimates the effect of changes in temperature in fundamental amenities and productivity, given by the functions \Lambda^b, \Lambda^a, and described in Section 3.2 and Appendix B
pwd
cd /Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/stata
local datafolder = "../../EGGW Replication/Data"

********************************************************************************
* Read amenities, productivity, pop, wages and realgdp

clear
import delimited "`datafolder'/derived/amen_prod.csv", clear 
qui rename amen_hdi amen_HDI
qui rename pop_x pop
qui rename wage_x wage
qui rename realgdp_x realgdp
// qui rename h0_x size_cell
// qui drop size_cell
// qui gen size_cell = areal*h0_share_x

compress
save "`datafolder'/derived/amen_prod.dta", replace

clear
import delimited "`datafolder'/subcountry_EU.csv", clear 
compress
save "`datafolder'/derived/subcountry_EU.dta", replace


********************************************************************************
* Read HDI and GDPpercap from Kummu

clear 
import delimited "`datafolder'/HDI_GDPpc.csv", clear 
rename lat_17048 lat
rename lon_17048 lon
rename year_17048 year
rename hdi_17048 HDI
rename gdppc_17048 GDPpc

qui keep if year == 1990 | year == 1995 | year == 2000 | year == 2005

merge 1:1 lat lon year using "`datafolder'/derived/amen_prod.dta"
qui drop _merge

qui gen totrealgdp = realgdp*pop
qui gen GDP = GDPpc*pop

gcollapse (mean) HDI totrealgdp GDP (sum) pop size_cell, by(subcountry year)

qui gen HDI3 = (HDI)^3
qui gen logGDP = log(GDP)
qui gen logrealgdp = log(totrealgdp)

* Transform utility
eststo clear
eststo: reghdfe HDI3 logrealgdp [aweight = pop], absorb(subcountry) nocons cluster(subcountry)
matrix coeff_aux = r(table)
scalar rho_simple_pop = coeff_aux[1,1]
estadd local subcountry_fe "X"
estadd local year_fe ""
estadd local weight_pop "X"
estadd local weight_area ""

eststo: reghdfe HDI3 logrealgdp [aweight = pop], absorb(subcountry year) nocons cluster(subcountry)
matrix coeff_aux = r(table)
scalar rho_pop = coeff_aux[1,1]
estadd local subcountry_fe "X"
estadd local year_fe "X"
estadd local weight_pop "X"
estadd local weight_area ""

eststo: reghdfe HDI3 i.year#c.logrealgdp [aweight = pop], absorb(subcountry year) nocons cluster(subcountry)
matrix coeff_aux = r(table)
scalar rho1990_pop = coeff_aux[1,1]
scalar rho1995_pop = coeff_aux[1,6]
scalar rho2000_pop = coeff_aux[1,11]
scalar rho2005_pop = coeff_aux[1,16]
estadd local subcountry_fe "X"
estadd local year_fe "X"
estadd local weight_pop "X"
estadd local weight_area ""

eststo: reghdfe HDI3 logrealgdp [aweight = size_cell], absorb(subcountry) nocons cluster(subcountry)
matrix coeff_aux = r(table)
scalar rho_simple_area = coeff_aux[1,1]
estadd local subcountry_fe "X"
estadd local year_fe ""
estadd local weight_pop ""
estadd local weight_area "X"

eststo: reghdfe HDI3 logrealgdp [aweight = size_cell], absorb(subcountry year) nocons cluster(subcountry)
matrix coeff_aux = r(table)
scalar rho_area = coeff_aux[1,1]
estadd local subcountry_fe "X"
estadd local year_fe "X"
estadd local weight_pop ""
estadd local weight_area "X"

eststo: reghdfe HDI3 i.year#c.logrealgdp [aweight = size_cell], absorb(subcountry year) nocons cluster(subcountry)
matrix coeff_aux = r(table)
scalar rho1990_area = coeff_aux[1,1]
scalar rho1995_area = coeff_aux[1,6]
scalar rho2000_area = coeff_aux[1,11]
scalar rho2005_area = coeff_aux[1,16]
estadd local subcountry_fe "X"
estadd local year_fe "X"
estadd local weight_pop ""
estadd local weight_area "X"

esttab using "Output/utility_parameter.tex", se star(* 0.10 ** 0.05 *** 0.01) r2(4)scalars(rmse "subcountry_fe `subcountry_fe'" "year_fe `year_fe'" "weight_pop `weight_pop'" "weight_area `weight_area'") replace


********************************************************************************
* Read additional geographic data

* Read geographic data
clear
import delimited "`datafolder'/geo_data.csv", clear 
capture rename ïlat lat

compress
save "`datafolder'/derived/geo_data.dta", replace


********************************************************************************
* Read temperature data

clear
import delimited "`datafolder'/temp_data.csv", clear 

qui gegen cell = group(lat lon)
xtset cell year

foreach y of numlist 10 {
	local j = `y'-1

	foreach m of numlist 1 7 {
		qui tsegen temp_`y'y_`m'm = rowtotal(L(0/`j').temp_1y_`m'm)
		qui replace temp_`y'y_`m'm = temp_`y'y_`m'm/`y'
	}
}

qui keep if year == 1990 | year == 1995 | year == 2000 | year == 2005 

foreach y of numlist 1 10 {
	qui gen temp_`y'y_1h = .
	qui replace temp_`y'y_1h = temp_`y'y_1m if lat > 0 
	qui replace temp_`y'y_1h = temp_`y'y_7m if lat < 0 
}

* Merge geographic data
qui merge m:1 lat lon using "`datafolder'/derived/geo_data.dta" 
qui drop _merge

* Merge amenities and productivity
qui merge 1:1 year lat lon using "`datafolder'/derived/amen_prod.dta"
qui drop if _merge != 3
qui drop _merge

* Merge amenities and productivity
qui merge 1:1 year lat lon using "`datafolder'/derived/subcountry_EU.dta"
qui drop if _merge != 3
qui drop _merge

* Generate regressors
qui gen log_amen_HDI = log(amen_HDI)
qui gen log_prod = log(prod)

* Intervals for temp 
foreach y of numlist 1 10 {
	foreach b of numlist 20 50 {

		qui xtile bin`b'_temp_mean_`y'y_1m = temp_`y'y_1m, nq(`b')
		qui xtile bin`b'_temp_mean_`y'y_1h = temp_`y'y_1h, nq(`b')

	}
}

* Generate transformation of natural attributes
qui gen lat_che = lat/90
qui gen lon_che = lon/180
local geo_name "elev rough std_elev dist2coast dist2ocean dist2water"
foreach g of local geo_name {
	qui sum `g'
	qui scalar `g'_min = r(min)
	qui scalar `g'_max = r(max)
	qui gen `g'_che = (`g' - (`g'_min + `g'_max)/2)
	qui sum `g'_che
	qui scalar `g'_che_max = r(max)
	qui replace `g'_che = `g'_che/`g'_che_max
}

foreach g of local geo_name {
	forvalues i=1/5 {
		qui gen `g'_che`i' = cos(`i'*acos(`g'_che))
	}
	drop `g'_che
}

qui gen log_prod_phi = log(prod/phi_1990)
qui replace log_prod_phi = log_prod if year == 1990

compress 
save "`datafolder'/derived/data_damage_fct.dta", replace


********************************************************************************
* Create bins of temp
local month_name "1m 1h"

foreach y of numlist 1 10 {
	foreach b of numlist 20 50 {

		if `b' == 20 {
			matrix bin = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]' 
			local ptiles "2.5 7.5 12.5 17.5 22.5 27.5 32.5 37.5 42.5 47.5 52.5 57.5 62.5 67.5 72.5 77.5 82.5 87.5 92.5 97.5"
			local rptiles "r(r1),r(r2),r(r3),r(r4),r(r5),r(r6),r(r7),r(r8),r(r9),r(r10),r(r11),r(r12),r(r13),r(r14),r(r15),r(r16),r(r17),r(r18),r(r19),r(r20)"
		}
		else if `b' == 50 {
			matrix bin = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50]' 
			local ptiles "1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55 57 59 61 63 65 67 69 71 73 75 77 79 81 83 85 87 89 91 93 95 97 99"
			local rptiles "r(r1),r(r2),r(r3),r(r4),r(r5),r(r6),r(r7),r(r8),r(r9),r(r10),r(r11),r(r12),r(r13),r(r14),r(r15),r(r16),r(r17),r(r18),r(r19),r(r20),r(r21),r(r22),r(r23),r(r24),r(r25),r(r26),r(r27),r(r28),r(r29),r(r30),r(r31),r(r32),r(r33),r(r34),r(r35),r(r36),r(r37),r(r38),r(r39),r(r40),r(r41),r(r42),r(r43),r(r44),r(r45),r(r46),r(r47),r(r48),r(r49),r(r50)"
		}

		foreach x of local month_name {

			use "`datafolder'/derived/data_damage_fct.dta", clear
			qui _pctile temp_`y'y_`x', percentiles(`ptiles')
			matrix temp_pctile = [`rptiles']'

			* Store results from regression as `datafolder'
			qui drop _all
			qui svmat int bin, name(bin)
			qui rename bin1 bin
			qui svmat double temp_pctile, name(temp_pctile)
			qui rename temp_pctile1 temp
			qui drop if bin > `b'

			qui compress
			qui save "`datafolder'/derived/temp_`y'y_`x'_pctile`b'.dta", replace
		}

}
}


********************************************************************************
* Main regression and robustness

local fund_name "amen prod"
local specif_name "base jan 1year 50bins"
local low_high_name "low high"
local conf_name "95 90 80 60"

foreach f of local fund_name {
	foreach s of local specif_name {

		use "`datafolder'/derived/data_damage_fct.dta", clear

		if "`f'" == "amen" {
			qui gen depvar = log_amen_HDI
			qui gen nat_var_aux = 1
			local nat_var nat_var_aux 
			local grid_name "grid_2c"	
			qui gegen grid = group(grid_2c)
			local fe_name "subnalEUctry"
			qui gegen subnal = group(subcountry_eu_ctry)
			local ytitle "Log-Amenities"
			local title "{bf:Log-Amenities}"
			local color_fund "0 139 139"
		}
		else if "`f'" == "prod" {
			qui gen depvar = log_prod_phi
			local grid_name "nat_var"
			qui gen grid = land_type
			local nat_var elev_che1-dist2water_che5
			local fe_name "subnalEUreg"
			qui gegen subnal = group(subcountry_eu_reg)
			local ytitle "Log-Productivities"
			local title "{bf:Log-Productivities}"
			local color_fund "0 100 0"
		}

		if "`s'" == "base" {
			local m "_1h"
			local y "10"
			local b "20"
			local xtitle "January-July Temperature"
			local xlabel "1 "-37.79" 2 " " 3 "-28.98" 4 " " 5 "-21.42" 6 " " 7 "-13.94" 8 " " 9 "-5.74" 10 " " 11 "2.86" 12 " " 13 "11.14" 14 " " 15 "16.85" 16 " " 17 "21.99" 18 " " 19 "25.77" 20 " ""
		}
		else if "`s'" == "jan" {
			local m "_1m"
			local y "10"
			local b "20"
			local xtitle "January Temperature"
			local xlabel "1 "-37.79" 2 " " 3 "-28.98" 4 " " 5 "-21.42" 6 " " 7 "-13.94" 8 " " 9 "-5.74" 10 " " 11 "3.82" 12 " " 13 "14.02" 14 " " 15 "21.80" 16 " " 17 "25.29" 18 " " 19 "26.96" 20 " ""
		}
		else if "`s'" == "1year" {
			local m "_1h"
			local y "1"
			local b "20"
			local xtitle "January-July Temperature"
			local xlabel "1 "-37.79" 2 " " 3 "-28.98" 4 " " 5 "-21.42" 6 " " 7 "-13.94" 8 " " 9 "-5.74" 10 " " 11 "2.86" 12 " " 13 "11.14" 14 " " 15 "16.85" 16 " " 17 "21.99" 18 " " 19 "25.77" 20 " ""
		}
		else if "`s'" == "50bins" {
			local m "_1h"
			local y "10"
			local b "50"
			local xtitle "January-July Temperature"
			local xlabel "1 "-40.39" 2 " " 3 " " 4 " " 5 " " 6 "-30.18" 7 " " 8 " " 9 " " 10 " " 11 "-22.63" 12 " " 13 " " 14 " " 15 " " 16 "-14.95" 17 " " 18 " " 19 " " 20 " " 21 "-7.09" 22 " " 23 " " 24 " " 25 " " 26 "1.43" 27 " " 28 " " 29 " " 30 " " 31 "10.24" 32 " " 33 " " 34 " " 35 " " 36 "16.11" 37 " " 38 " " 39 " " 40 " " 41 "21.16" 42 " " 43 " " 44 " " 45 " " 46 "25.41" 47 " " 48 " " 49 " " 50 " ""
		}

		* Define subnational units
		sum subnal 
		local max_subnal = r(max)
		qui gen fe = (year-1985)/5*`max_subnal'+subnal

		* Define temperature
		forval i = 1/`b' {
			qui gen temp_bin_`i' = 0
			qui replace temp_bin_`i' = temp_`y'y`m' if bin`b'_temp_mean_`y'y`m' == `i' 
		}

		* Run regressions
		acreg depvar temp_bin_1-temp_bin_`b' `nat_var', id(cell) time(year) latitude(lat) longitude(lon) spatial dist(550) pfe1(grid) pfe2(fe)

		* Store results
		matrix coeff_aux = r(table)
		matrix coeff0 = coeff_aux[1,1..`b']'
		matrix se0 = coeff_aux[2,1..`b']'
		matrix p0 = coeff_aux[4,1..`b']'

		if "`b'" == "20" {
			matrix bin = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]' 
		}
		else if "`b'" == "50" {
			matrix bin = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50]' 
		}

		scalar n_obs = e(N)
		foreach c of local conf_name {
			matrix low`c' = coeff0 - invttail(n_obs-1,0.5*(1-`c'/100))*se0
			matrix high`c' = coeff0 + invttail(n_obs-1,0.5*(1-`c'/100))*se0
		}

		* Transform results to `datafolder'
		qui drop _all
		svmat int bin, name(bin)
		rename bin1 bin
		svmat double coeff0, name(coeff0)
		qui rename coeff01 v0
		foreach c of local conf_name {
			foreach l of local low_high_name {
				svmat double `l'`c', name(`l'`c')
				rename `l'`c'1 `l'_`c'pct
			}
		}
		svmat double se0, name(se0)
		rename se01 se
		svmat double p0, name(p0)
		rename p01 p

		qui merge 1:1 bin using "`datafolder'/derived/temp_`y'y`m'_pctile`b'.dta"
		qui drop _merge

		local logis_steep = 0.1
		scalar logis_steep_scalar = `logis_steep'

		* Estimate logistic smoothing
		foreach c of local conf_name {
			foreach l of local low_high_name {
				nl (`l'_`c'pct = {logis_min} + ({logis_max} - {logis_min})/(1+exp(`logis_steep'*(temp - {logis_center=3.75})))) [aweight = 1/se], eps(1e-5)
				predict logist_coeff_`l'`c'
				matrix coeff_logis_`l'`c' = (e(b),logis_steep_scalar)'
			}
		}

		nl (v0 = {logis_min} + ({logis_max} - {logis_min})/(1+exp(`logis_steep'*(temp - {logis_center=3.75})))) [aweight = 1/se], eps(1e-5)
		predict logist_coeff0
		matrix coeff_logis0 = (e(b),logis_steep_scalar)'

		compress
		save "`datafolder'/derived/`f'_point_`y'y`m'_`b'b_550d.dta", replace

		clear

		foreach c of local conf_name {
			foreach l of local low_high_name {
				svmat coeff_logis_`l'`c'
				rename coeff_logis_`l'`c'1 coeff_logis_`l'`c'
			}
		}

		svmat coeff_logis0
		rename coeff_logis01 coeff_logis0

		compress
		save "`datafolder'/derived/`f'_coeff_`y'y`m'_`b'b_550d.dta", replace

		export delimited using  "`datafolder'/derived/`f'_coeff_`y'y`m'_`b'b_550d.csv", replace

		use "`datafolder'/derived/`f'_point_`y'y`m'_`b'b_550d.dta", clear

		if "`f'" == "amen" {
			local yscale_min = -0.05
			if "`s'" != "50bins" {
				local yscale_max = 0.05
				local yscale_sp = 0.025
			}
			else {
				local yscale_max = 0.1
				local yscale_sp = 0.05
			}
		}
		else {
			if "`s'" != "50bins" {
				local yscale_min = -0.3
				local yscale_max = 0.3
				local yscale_sp = 0.1
			}
			else {
				local yscale_min = -1
				local yscale_max = 0.5
				local yscale_sp = 0.5
			}
		}
		
		* Plot bar graph
		graph twoway (bar v0 bin, color("`color_fund'")) ///
			(rcap high_95pct low_95pct bin, color(black)) ///
			(connected logist_coeff0 bin, color(gray) lwidth(0.75) msize(vtiny)) ///
			(connected logist_coeff_low95 bin, color(gray) lpattern(dash) lwidth(0.75) msize(vtiny)) ///
			(connected logist_coeff_high95 bin, color(gray) lpattern(dash) lwidth(0.75) msize(vtiny)), /// 
			graphregion(color(white)) bgcolor(white) ///
			xlabel(`xlabel', labsize(small)) ylabel(, labsize(small)) ///
			legend(order(1 "point estimate" 2 "95% confidence interval" 3 "logistic, point estimate" 4 "logistic, 95% confidence interval") size(small)) ///
			xtitle("`xtitle'", size(small)) ytitle("`ytitle'", size(small)) ///
			title("`title'", color(black) size(medium) ) graphregion(margin(zero)) ///
			yscale(range(`yscale_min' `yscale_max')) ylabel(`yscale_min'(`yscale_sp')`yscale_max')

		* Save graph
		graph export "Maps and Figures/`f'_damage_`y'y`m'_`b'b_550d.png", replace

	}
}


********************************************************************************
* Main regression with different structure of errors

* Baseline specification
local m "_1h"
local y "10"
local b "20"
matrix bin = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]' 

local fund_name "amen prod"
local error_name "1100d homosk hetesk cluster"

foreach f of local fund_name {

	use "`datafolder'/derived/data_damage_fct.dta", clear

	if "`f'" == "amen" {
		qui gen depvar = log_amen_HDI
		qui gen nat_var_aux = 1
		local nat_var nat_var_aux 
		local grid_name "grid_2c"	
		qui gegen grid = group(grid_2c)
		local fe_name "subnalEUctry"
		qui gegen subnal = group(subcountry_eu_ctry)
	}
	else if "`f'" == "prod" {
		qui gen depvar = log_prod_phi
		local grid_name "nat_var"
		qui gen grid = land_type
		local nat_var elev_che1-dist2water_che5
		local fe_name "subnalEUreg"
		qui gegen subnal = group(subcountry_eu_reg)
	}

	* Define subnational units
	sum subnal 
	local max_subnal = r(max)
	gen fe = (year-1985)/5*`max_subnal'+subnal

	* Define temperature
	forval i = 1/`b' {
		qui gen temp_bin_`i' = 0
		qui replace temp_bin_`i' = temp_`y'y`m' if bin`b'_temp_mean_`y'y`m' == `i' 
	}

	* Run regressions, with spatially correlated errors at 1100km
	acreg depvar temp_bin_1-temp_bin_`b' `nat_var', id(cell) time(year) latitude(lat) longitude(lon) spatial dist(1100) pfe1(grid) pfe2(fe)
	matrix coeff_aux = r(table)
	matrix coeff_1100d = coeff_aux[1,1..`b']'
	matrix se_1100d = coeff_aux[2,1..`b']'
	matrix p_1100d = coeff_aux[4,1..`b']'

	* Run regressions, with homoskedastic errors and no correlation
	reghdfe depvar temp_bin_1-temp_bin_`b' `nat_var', absorb(grid fe)
	matrix coeff_aux = r(table)
	matrix coeff_homosk = coeff_aux[1,1..`b']'
	matrix se_homosk = coeff_aux[2,1..`b']'
	matrix p_homosk = coeff_aux[4,1..`b']'

	* Run regressions, with heteroskedastic errors and no correlation
	reghdfe depvar temp_bin_1-temp_bin_`b' `nat_var', absorb(grid fe) vce(robust)
	matrix coeff_aux = r(table)
	matrix coeff_hetesk = coeff_aux[1,1..`b']'
	matrix se_hetesk = coeff_aux[2,1..`b']'
	matrix p_hetesk = coeff_aux[4,1..`b']'

	* Run regressions, clustering errors at subnational level
	reghdfe depvar temp_bin_1-temp_bin_`b' `nat_var', absorb(grid fe) vce(cluster subnal)
	matrix coeff_aux = r(table)
	matrix coeff_cluster = coeff_aux[1,1..`b']'
	matrix se_cluster = coeff_aux[2,1..`b']'
	matrix p_cluster = coeff_aux[4,1..`b']'

	* Save errors
	foreach e of local error_name {

		qui drop _all
		svmat int bin, name(bin)
		rename bin1 bin
		svmat double coeff_`e', name(coeff_`e')
		rename coeff_`e'1 v0
		svmat double se_`e', name(se_`e')
		rename se_`e'1 se
		svmat double p_`e', name(p_`e')
		rename p_`e'1 p

		compress
		save "`datafolder'/derived/`f'_point_`y'y`m'_`b'b_`e'.dta", replace

	}

}


********************************************************************************
* Tables comparing standard errors in the main specification 

local fund_name "amen prod"
local error_name "1100d homosk hetesk cluster"

foreach f of local fund_name {

	* Baseline specification
	local m "_1h"
	local y "10"
	local b "20"

	use "`datafolder'/derived/`f'_point_`y'y`m'_`b'b_550d.dta", clear
	
	qui keep v0 bin se p
	qui replace v0 = round(v0,.0001)
	qui replace se = round(se,.0001)
	format v0 se %8.4f
	qui gen par_i = "("
	qui gen par_f = ")"
	qui gen stars = "\sym{}"
	qui replace stars = "\sym{*}" if p < 0.1
	qui replace stars = "\sym{**}" if p < 0.05
	qui replace stars = "\sym{***}" if p < 0.01
	qui gegen se_550d = concat(par_i se par_f stars)
	qui drop se p
	
	foreach e of local error_name {
		qui merge 1:1 bin using "`datafolder'/derived/`f'_point_`y'y`m'_`b'b_`e'.dta", nogenerate
		qui replace se = round(se,.0001)
		format se %8.4f
		qui replace stars = "\sym{}"
		qui replace stars = "\sym{*}" if p < 0.1
		qui replace stars = "\sym{**}" if p < 0.05
		qui replace stars = "\sym{***}" if p < 0.01
		qui gegen se_`e' = concat(par_i se par_f stars)
		qui drop se p
	}

	rename v0 coeff
	keep coeff se_550d se_1100d se_homosk se_hetesk se_cluster
	
	export delimited using  "Output/`f'_se_robustness.csv", replace

}
