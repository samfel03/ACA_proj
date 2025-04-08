#include "init.h"
#include "definitions.h"

void linear_space(const real xmin,
				  const real xmax,
				  const int ngrid,
				  real *grid)
{
	real increment;
	increment = (real)((xmax) - (xmin)) / (ngrid - 1);
	for (int i = 0; i < ngrid; ++i)
		grid[i] = (xmin) + i * increment;
	return;
}

// 1. Set economic parameters
/*
void init_environment(env_t *env)
{
	env->lbar = 5.9174e+09;										// total population
	env->lambda = 0.32;											// congestion externalities
	env->gamma1 = 0.319;										// elasticity of tomorrow's productivity relative to today's innovation
	env->gamma2 = 0.99246;										// elasticity of tomorrow's productivity relative to today's productivity
	env->eta = 1;												// parameter driving scale of technology diffusion
	env->mu = 0.8;												// labor share in production
	env->nu = 0.15;												// intercept parameter in innovation cost function
	env->ksi = 125;												// elasticity of innovation costs relative to innovation
	env->sigma = 4;												// elasticity of substitution
	env->psi_util = 0.045;										// wellbeing parameter
	env->beta = 0.965;											// discount factor for present discounted values
	env->alpha = 0.06;											// agglomeration externalities
	env->theta = 6.5;											// variance productivity shocks
	env->Omega = 0.5;											// variance taste shocks
	env->max_cumCO2 = maxCO2;									// total stock of CO2 in the ground
	env->epsilon = eps;											// elasticity of substitution between fossil fuels and clean energy
	env->tCO2_toe = 2.8466;										// conversion factor: GtCO2 per Gtoe
	env->price_fossil0_world = 72.99 * 10 ^ 9;					// price of fossil fuels in usd/GtCO2
	env->price_clean0_world = 1.15 * 76.34 * 10 ^ 9 / tCO2_toe; // price of clean energy in usd/GtCO2

	return;
}
*/
void init_guesses(env_t *env)
{
	// Guess for coefficients on the natality rate function.
	int i = 0;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	i++;
	env->coeff_pop_i[i] = GUESS_coeff_pop_i[i];
	// Guess for the elasticity of fossil fuel productivity growth to global real GDP growth
	env->upsilon_fossil_i = 1.15;
	// Guess for the elasticity of clean energy productivity growth to global real GDP growth
	env->upsilon_clean_i = 1.15;
	// Load guess for migration costs: estim_model.m
	data_m2 = load('Data/derived/m2.mat');
	m2_i = data_m2.m2;

	return;
}
/*
// 2. Load initial land, amenities, productivities, population and wages
// Output: H0 H n amen_util0 n prod0 pop0 pop5 pop0_dens pop1_dens pop5_dens w0
void init_land_amen_prod_pop_wages(env_t *env)
{
	data_H0 = load('Data/H0_areal.mat');
	H0 = data_H0.H0;
	H = H0(H0 > 0);
	n = length(H); // number of cells with positive land

	data_amen_util_H0 = load('Data/derived/amen_util.mat');
	amen_util_H0 = data_amen_util_H0.amen_util_H0;
	amen_util0 = amen_util_H0(
		:, 3); // ratio of amenities to utility in 2000

	data_prod_H0 = load('Data/derived/prod.mat');
	prod_H0 = data_prod_H0.prod_H0;
	prod0 = prod_H0(
		:, 3); // productivities in 2000

	data_pop = load('Data/pop_Gecon.mat');
	pop_aux = data_pop.pop;
	pop0 = pop_aux(
		:,
		:, 3); // population in 2000
	pop0_dens = pop0(H0 > 0)./ H0(H0 > 0);
	pop5 = pop_aux(
		:,
		:, 4); // population in 2005
	pop5_dens = pop5(H0 > 0)./ H0(H0 > 0);
	pop1_dens = (4 / 5) * pop0_dens + (4 / 5) * pop5_dens;

	data_wage = load('Data/wage_Gecon.mat');
	wage_aux = data_wage.wage;
	w0 = wage_aux(
		:,
		:, 3); // wage in 2000
	w0 = w0(H0 > 0);

	return;
}
// 3. Load and shape utility levels and HDI
// Output: HDI0 u0 a_norm
void init_uti_HDI(env_t *env)
{
	data_HDI_GDPpc = readtable('Data/HDI_GDPpc.csv');
	data_HDI0 = table2array(data_HDI_GDPpc(1
										   : n, 4));

	HDI0 = zeros(180, 360); // Human Development Index in 2000
	HDI0(H0 > 0) = data_HDI0;
	u0 = exp(HDI0(H0 > 0).^ 3. / psi_util); // utility in 2000
	a_norm = amen_util0.*u0;				// amenities in 2000

	return;
}
//// 4. Load trmult
// Output: trmult_reduced
void init_trmult(env_t *env)
{
	// Bilateral trade cost on Earth cells at t=0 only
	data_trmult = load('Data/trmult_reduced.mat');
	trmult_reduced = data_trmult.trmult_reduced;

	return;
}
//// 5. Load countries indices
// Output: C_vect, length_C_vect
void init_countries_indices(env_t *env)
{
	C = csvread('Data/C.csv'); // national demarcations
	C_vect = C(H0 > 0);
	length_C_vect = length(unique(C_vect));
	return;
}
//// 6. Construct CO2 emissions and clean energy use
// Output: emi0_ff,emi_ff,emi0_no_ff,emi_no_ff,emi0,emi0_cell,clean0_cell
void init_CO2_clean_energy(env_t *env)
{
	// Global CO2 emissions from fossil fuels from 2000 to 2600, by IPCC
	emi_ff_RCP = csvread('Data/CO2_ff.csv');
	emi_ff = emi_ff_RCP(
		:, 5 - floor(ind_RCP / 2));
	emi0_ff = emi_ff(1, 1);

	// Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC
	emi_no_ff_RCP = csvread('Data/CO2_noff_smooth.csv');
	emi_no_ff = emi_no_ff_RCP(
		:, 5 - floor(ind_RCP / 2));
	emi0_no_ff = emi_no_ff(1);
	emi_no_ff = emi_no_ff(2
						  : end);

	emi0 = emi0_ff + emi0_no_ff; // total CO2 emissions for 2000

	// CO2 emissions at cell level for 2000
	data_emi = load('Data/CO2_EDGAR.mat'); // cell level CO2 emissions
	emi_cell = data_emi.CO2_EDGAR;
	emi_cell = emi_cell(
		:,
		:, 3);
	emi0_cell = emi_cell(H0 > 0);

	// CO2 emissions and clean energy at the country level for 2000
	emi0_ff_country = csvread('Data/CO2_country.csv');
	emi0_ff_country = emi0_ff_country(
		:, 3);
	emi0_ff_cell = zeros(n, 1);

	clean0_country = csvread('Data/clean_country.csv');
	clean0_country = clean0_country(
		:, 3);
	clean0_cell = zeros(n, 1);

	// Match CO2 emissions and clean energy at the country level for 2000
for
	i = 1 : length_C_vect
				emi0_ff_cell(C_vect == i) = emi0_cell(C_vect == i) * emi0_ff_country(i) / sum(emi0_cell(C_vect == i));
clean0_cell(C_vect == i) = emi0_cell(C_vect == i) * clean0_country(i) / sum(emi0_cell(C_vect == i));
end

	emi0_ff_cell = emi0_ff_cell * emi0_ff / sum(emi0_ff_cell);
emi0_ff_cell = emi0_ff_cell./ H;
clean0_cell = clean0_cell./ H;
return;
}
// 7. Construct energy parameters in technology
// Output: fossil_share chi
void init_energy_tech(env)
{
	// Define global use of fossil fuels and clean energy
	clean0 = sum(clean0_cell.*H);
	fossil0 = emi0_ff;

	// Construct share of fossil fuels in energy composite
	fossil_share = (1 + (price_clean0_world / price_fossil0_world) * (clean0 / fossil0) ^ (1 / epsilon)) ^ (-1);

	// Construct share of energy in production, equations (7) and (44)
	price_energy0_world = ...(fossil_share ^ epsilon * price_fossil0_world ^ (1 - epsilon) + ...(1 - fossil_share) ^ epsilon * price_clean0_world ^ (1 - epsilon)) ^ (1 / (1 - epsilon));
	energy0 = ...(fossil_share * fossil0 ^ ((epsilon - 1) / epsilon) + ...(1 - fossil_share) * clean0 ^ ((epsilon - 1) / epsilon)) ^ (epsilon / (epsilon - 1));
	GDP0 = sum(w0.*pop0_dens.*H);
	energy_share = price_energy0_world * energy0 * (mu + gamma1 / ksi) / GDP0;
	chi = 1 - energy_share / mu;
	return;
}
// 8. Construct extraction cost function
// Output: cost_CO2_data, cost_emi_param, price_clean0_world, conv_usd
void init_extraction_cost_fun(env)
{
	// Read cost extraction data
	cost_CO2_data = csvread('Data/CO2_cost.csv');

	// Define cost extraction function
	costCO2_fct_aux = @(cost_emi_param_aux, cumCO2)... cost_emi_param_aux(1)./ (cost_emi_param_aux(2) + exp(-cost_emi_param_aux(3) * (cumCO2 - cost_emi_param_aux(4)))) - ...(cost_emi_param_aux(5) * 19500. / (cumCO2 - 19500)).^ 3;

	// Find parameters that better fit the data
	options = optimoptions('lsqcurvefit', 'Display', 'none');
	cost_emi_param_i = [2 1 1e-4 5000 1];
	cost_emi_param_f = lsqcurvefit(costCO2_fct_aux, cost_emi_param_i, ... cost_CO2_data(
																		  :, 2),
								   cost_CO2_data(
									   :, 1),
								   [1 0 0 0 0], [Inf Inf 5 * 1e-4 Inf Inf], ... options);

	// Redefine extraction cost function
	cost_emi_param_f(5) = cost_emi_param_f(5) ^ 3;
	cost_emi_param = [cost_emi_param_f maxCO2 3];

	// Define normalization relative to Princeton wage
	GDPpc0 = GDP0 / (w0(3199) * lbar);
	cost_emi_param([1 5]) = cost_emi_param([1 5]) / GDPpc0; // usdP/GtCO2
	price_clean0_world = price_clean0_world / GDPpc0;		// usdP/GtCO2
	conv_usd = 1 / GDPpc0;

	costCO2_fct = @(cumCO2)... cost_emi_param(1)./ (cost_emi_param(2) + exp(-cost_emi_param(3) * (cumCO2 - cost_emi_param(4)))) - ... cost_emi_param(5) * (cost_emi_param(6)./ (cumCO2 - cost_emi_param(6))).^ cost_emi_param(7);

	return;
}
// 9. Construct energy productivity
// Output: fossil0_cell, price_clean0, price_fossil0 price_energy0 zeta_clean0 zeta_fossil0
void init_energy_productivity(env)
{
	// Construct energy use at the cell level, equation (7)
	fossil0_cell = emi0_ff_cell;
	energy0_cell = (fossil_share * fossil0_cell.^ ((epsilon - 1) / epsilon) + ...(1 - fossil_share) * clean0_cell.^ ((epsilon - 1) / epsilon)).^ (epsilon / (epsilon - 1));

	// Construct energy price at the cell level by source, equations (52), (53)
	// and (44)
	const_energy = (1 - env__chi) * env__mu / (env__mu + env__gamma1 / env__ksi);
	price_clean0 = const_energy * (1 - fossil_share) * ...(pop0_dens./ energy0_cell).*(energy0_cell./ clean0_cell).^ (1 / epsilon);
	price_fossil0 = const_energy * fossil_share * ...(pop0_dens./ energy0_cell).*(energy0_cell./ fossil0_cell).^ (1 / epsilon);
	price_energy0 = (fossil_share ^ epsilon * price_fossil0.^ (1 - epsilon) + ...(1 - fossil_share) ^ epsilon * price_clean0.^ (1 - epsilon)).^ (1 / (1 - epsilon));

	// Construct initial energy productivities
	zeta_clean0 = price_clean0_world./ price_clean0;
	zeta_fossil0 = costCO2_fct(0)./ price_fossil0;
	return;
}
// 10. Set carbon circulation parameters
// Output: S0 S1 S2 S3
void init_carbon_circulation(env)
{

	// Read total CO2 emissions from 1999 to 1945
	emiCO2_data = flipud(csvread('Data/CO2_hist.csv'));
	length_emi_data = length(emiCO2_data);

	// Initialize CO2 stock layers, equations (38) and (39)
	S0 = a0 * sum(emiCO2_data) + S_preind;
	S1 = a1*sum(exp(-(0:1:length_emi_data-1)'/b1).*emiCO2_data);
	S2 = a2*sum(exp(-(0:1:length_emi_data-1)'/b2).*emiCO2_data);
	S3 = a3*sum(exp(-(0:1:length_emi_data-1)'/b3).*emiCO2_data);
	//' 

	return;
}
// 11. Set forcing parameters
void init_forcing_sensitivity(env)
{
	// Read non CO2 radiative forcing
	forc_noCO2_RCP = csvread('Data/Forcing_noCO2_smooth.csv');
	forc_noCO2 = forc_noCO2_RCP(
		:, 5 - floor(ind_RCP / 2));

	return;
}
// 12. Set global temperature parameters
// Output: forc_data temp1 temp2 temp0_global
void init_temperature_global(env)
{
	// Read forcing from 2000 to 1825
	forc_data = flipud(csvread('Data/Forcing_hist.csv'));
	length_forc_data = length(forc_data);

	// Initialize temperature layers, equation (41)
	temp1 = (c1/d1)*sum(exp(-(0:1:length_forc_data-1)'/d1).*forc_data);
	temp2 = (c2/d2)*sum(exp(-(0:1:length_forc_data-1)'/d2).*forc_data) + temp_preind;
	temp0_global = temp1 + temp2;

	return;
}
// 13. Local January-July temperature from 1950 to 2000
// Output: temp0_local_long temp0_local Delta_temp1 temp_past Delta_temp
void init_temperature_local(env)
{
	data_temp = load('Data/temp.mat');
	temp0_local_long = data_temp.temp0_local_10y;
	temp0_local = data_temp.temp0_local_10y_mean;
	Delta_temp1 = data_temp.Delta_temp1;
	temp_past = data_temp.temp_10y_past;
	Delta_temp = data_temp.Delta_temp;

	return;
}
// 14. Load temperature scaler (consider reading it from matlab)
// Output: scaler_temp
void init_temperature_scaler(env)
{
	scaler_table = readtable('Data/derived/scaler_temp.csv');
	lat_scaler = table2array(scaler_table(
		:, 1));
	lon_scaler = table2array(scaler_table(
		:, 2));
	scaler_data = table2array(scaler_table(
		:, 5));
	length_scaler = length(lon_scaler);

	// Arrange temperature scaler in a grid
	scaler_grid = NaN(180, 360);
for
	i = 1 : length_scaler
				scaler_grid(90.5 - lat_scaler(i), lon_scaler(i) + 180.5,
							:) = ... scaler_data(i);
end
	scaler_grid(H0 == 0) = NaN;

// Interpolate missing data
scaler_grid_long = [scaler_grid(
	:, 341 : 360) scaler_grid scaler_grid(
	:, 1 : 20)];
H0_long = [H0(
	:, 341 : 360) H0 H0(
	:, 1 : 20)];
for i=1:11 // iterations
    for k=1:5 // radiius of surronding cells
        indi_scaler = (H0_long>0 & isnan(scaler_grid_long));
[ lat_scaler, lon_scaler ] = find(indi_scaler == 1);
cent_scaler = (lon_scaler > 20) & (lon_scaler < 381);
lat_scaler = lat_scaler(cent_scaler);
lon_scaler = lon_scaler(cent_scaler);

length_scaler = length(lat_scaler);
		for
			j = 1 : length_scaler // missing data
						scaler_grid_long(lat_scaler(j), lon_scaler(j)) = nanmean(scaler_grid_long(... lat_scaler(j) - i
																								  : lat_scaler(j) + i, ... lon_scaler(j) - i
																								  : lon_scaler(j) + i),
																				 'all');
		end
			end
				end

					scaler_temp = scaler_grid_long(
						:, 21 : 380);
		scaler_temp = scaler_temp(H0 > 0);

		return;
}
// 15. Load damage functions
// Output: theta_amen_scen
void init_damage_fun(env)
{

	// Read coefficients from damage function estimated in damage_function.do
	theta_amen_logi_vect = readtable('Data/derived/amen_coeff_10y_1h_20b_550d.csv');
	theta_amen_logi_vect = table2array(theta_amen_logi_vect);
	theta_prod_logi_vect = readtable('Data/derived/prod_coeff_10y_1h_20b_550d.csv');
	theta_prod_logi_vect = table2array(theta_prod_logi_vect);

	theta_amen_scen = theta_amen_logi_vect(
		:, 1 : 9);
	theta_prod_scen = theta_prod_logi_vect(
		:, 1 : 9);

	theta_amen_min = theta_amen_scen(1, 9);
	theta_amen_max = theta_amen_scen(2, 9);
	theta_amen_center = theta_amen_scen(3, 9);
	theta_amen_steep = theta_amen_scen(4, 9);
	theta_amen_temp = @(temp) theta_amen_min + ...(theta_amen_max - theta_amen_min)./ ...(1 + exp(theta_amen_steep * (temp - theta_amen_center)));

	theta_prod_min = theta_prod_scen(1, 9);
	theta_prod_max = theta_prod_scen(2, 9);
	theta_prod_center = theta_prod_scen(3, 9);
	theta_prod_steep = theta_prod_scen(4, 9);
	theta_prod_temp = @(temp) theta_prod_min + ...(theta_prod_max - theta_prod_min)./ ...(1 + exp(theta_prod_steep * (temp - theta_prod_center)));

	// Display results for damage function estimates
	
	//temp_cold = -37.79;
	//temp_hot = 25.77;
	//disp(['In the coldest bin of the Earth, ' num2str(temp_cold) 'ºC, ' ... 'a temperature increase in 1ºC changes local amenities by ' ... num2str(100 * theta_amen_temp(temp_cold)) '// and local productivities by ' ... num2str(100 * theta_prod_temp(temp_cold)) '// '])
	//	disp(['In the hottest bin of the Earth, ' num2str(temp_hot) 'ºC, ' ... 'a temperature increase in 1ºC changes local amenities by ' ... num2str(100 * theta_amen_temp(temp_hot)) '// and local productivities by ' ... num2str(100 * theta_prod_temp(temp_hot)) '// '])
	//		disp(['The optimal temperature for amenities is ' num2str(fzero(theta_amen_temp, 0)) 'ºC ' ... 'and for productivities is ' num2str(fzero(theta_prod_temp, 0)) 'ºC '])
	
	return;
}
// 16. Load historical population
// Output: country_data year_data natal_data pop_data natal0 natal20
void init_population_historical(env)
{

	// Read net birth historical data
	birth_death = csvread('Data/birth_death_pop.csv');
	country_data = birth_death(
		:, 1);
	year_data = birth_death(
		:, 2);
	natal_data = birth_death(
		:, 3);
	pop_data = birth_death(
		:, 4);

	// Define natality rates of 2000 and 2020
	natal0 = sum(natal_data(year_data == 2000).*pop_data(year_data == 2000)) / ... sum(pop_data(year_data == 2000));
	natal20 = sum(natal_data(year_data == 2020).*pop_data(year_data == 2020)) / ... sum(pop_data(year_data == 2020));

	// Keep data for years < 2001
	natal_data = natal_data(year_data < 2001);
	country_data = country_data(year_data < 2001);
	pop_data = pop_data(year_data < 2001);
	year_data = year_data(year_data < 2001);
	return;
}
// 17. Load population predictions (UN)
// Output: pop_low95 pop_low80 pop_med pop_high80 pop_high95 pop_low95_hist pop_low80_hist pop_med_hist pop_high80_hist pop_high95_hist
void init_population_prediction(env)
{
	pop_hist = csvread('Data/pop_uncert.csv');

	pop_low95 = pop_hist(1, 51
						 : end);
	pop_low80 = pop_hist(2, 51
						 : end);
	pop_med = pop_hist(3, 51
					   : end);
	pop_high80 = pop_hist(4, 51
						  : end);
	pop_high95 = pop_hist(5, 51
						  : end);

	pop_low95_hist = pop_hist(1,
							  :);
	pop_low80_hist = pop_hist(2,
							  :);
	pop_med_hist = pop_hist(3,
							:);
	pop_high80_hist = pop_hist(4,
							   :);
	pop_high95_hist = pop_hist(5,
							   :);
	return;
}
// 18. Construct climate predictions (IPCC)
// Output: emiCO2_RCP stockCO2_RCP temp_global_RCP
void init_climate_prediction(env)
{

	emi_ff_RCP = csvread('Data/CO2_ff.csv');
	emi_no_ff_RCP = csvread('Data/CO2_noff_smooth.csv');
	emiCO2_RCP = emi_ff_RCP + emi_no_ff_RCP;

	stockCO2_layers_RCP = zeros(4, 600, 4);
	forc_RCP = zeros(600, 4);
	temp_layers_RCP = zeros(2, 600, 4);

	// Construct CO2 stock, forcing and temperature, using data on CO2 emissions
	// and non-CO2 forcing, equations (15) and (37)-(41)
for
	i = 1 : 4 stockCO2_layers_RCP(1, 1, i) = S0 + a0 * emiCO2_RCP(1, i);
stockCO2_layers_RCP(2, 1, i) = (exp(-1 / b1)) * S1 + a1 * emiCO2_RCP(1, i);
stockCO2_layers_RCP(3, 1, i) = (exp(-1 / b2)) * S2 + a2 * emiCO2_RCP(1, i);
stockCO2_layers_RCP(4, 1, i) = (exp(-1 / b3)) * S3 + a3 * emiCO2_RCP(1, i);

forc_RCP(1, i) = forc_sens * log(sum(stockCO2_layers_RCP(
									 :, 1, i)) /
								 S_preind) +
				 forc_noCO2_RCP(1, i);

temp_layers_RCP(1, 1, i) = (exp(-1 / d1)) * temp1 + (c1 / d1) * forc_RCP(1, i);
temp_layers_RCP(2, 1, i) = (exp(-1 / d2)) * temp2 + (c2 / d2) * forc_RCP(1, i);

	for
		t = 1 : 600 - 1 stockCO2_layers_RCP(1, t + 1, i) = stockCO2_layers_RCP(1, t, i) + a0 * emiCO2_RCP(t + 1, i);
	stockCO2_layers_RCP(2, t + 1, i) = (exp(-1 / b1)) * stockCO2_layers_RCP(2, t, i) + a1 * emiCO2_RCP(t + 1, i);
	stockCO2_layers_RCP(3, t + 1, i) = (exp(-1 / b2)) * stockCO2_layers_RCP(3, t, i) + a2 * emiCO2_RCP(t + 1, i);
	stockCO2_layers_RCP(4, t + 1, i) = (exp(-1 / b3)) * stockCO2_layers_RCP(4, t, i) + a3 * emiCO2_RCP(t + 1, i);

	forc_RCP(t + 1, i) = forc_sens * log(sum(stockCO2_layers_RCP(
											 :, t + 1, i)) /
										 S_preind) /
							 log(2) +
						 forc_noCO2_RCP(t + 1, i);

	temp_layers_RCP(1, t + 1, i) = (exp(-1 / d1)) * temp_layers_RCP(1, t, i) + (c1 / d1) * forc_RCP(t + 1, i);
	temp_layers_RCP(2, t + 1, i) = (exp(-1 / d2)) * temp_layers_RCP(2, t, i) + (c2 / d2) * forc_RCP(t + 1, i);
	end

		end
			stockCO2_RCP = permute(sum(stockCO2_layers_RCP, 1), [2 3 1]);
	temp_global_RCP = permute(sum(temp_layers_RCP, 1), [2 3 1]);
	return;
}
// 19. Load historic CO2 emissions
// Output: clean_energy_data emi_ff_data emi_ff_data_tend
void init_CO2_historical(env)
{

	// Historical clean energy use
	clean_energy_data = csvread('Data/clean_energy_hist.csv');
	clean_energy_data = clean_energy_data(1
										  : end - 1); // from 1965 to 1999

	// Historical fossil fuel CO2 emission and its trend
	emi_ff_all = csvread('Data/CO2_hist_ff.csv');
	emi_ff_data = emi_ff_all(
		:, 1);
	emi_ff_data_tend = emi_ff_all(
		:, 2);
	return;
}
// 20. Load gridded map
void init_map(env)
{
	map_data = load('Data/map_grid.mat');
	map = map_data.map; // map of size 2700x5400 for a better resolution of plots
	return;
}
// 21. Preallocation model_initial_period
void init_model_initial_period(env)
{
	// ****************************** model_initial_period.m ******************************
	// Compute parameters
	real denom = 1 + 2 * env__theta;
	real squ = (env__alpha - 1 + (env__lambda + env__gamma1 / env__ksi - (1 - env__mu)) * env__theta); // term in square brackets of flat_R and flat_L
	real flatL = env__lambda - squ / denom;
	real flatR = 1 - env__lambda * env__theta + (1 + env__theta) * squ / denom;
	real flat = flatR - env__theta * flatL;
	real exp_uhatL = flatL / env__Omega + (1 + env__theta) / denom;
	real exp_uhatR = flatR / env__Omega - env__theta * env__theta / denom;

	// Precompute auxiliary variables to equation (75)
	env->FL_H_m2_left[] = H.^((flatL-1/denom)/exp_uhatL);
	env->FL_H_m2_left_exp = flatL/(env__Omega*exp_uhatL);
	env->FL_H_m2_right[] = H.^ (-flatR + env__theta / denom);
	env->FL_H_m2_right_exp =-flatR / env__Omega;
	env->FL_a_norm_exp = (1 + theta) / (denom * exp_uhatL);
	env->FL_prod0_exp = 1 / (denom * exp_uhatL);
	env->FL_price_energy0_exp=-env__theta * mu * (1 - env__chi) / (denom * exp_uhatL);
	env->FR_a_norm_exp = env__theta ^ 2 / denom;
	env->FR_prod0_exp = (1 + env__theta) / denom;
	env->FR_price_energy0_exp=-env__theta * (1 + env__theta) * env__mu * (1 - env__chi) / denom;
	env->uhat_f_exp= 1 / (env__theta * exp_uhatL);

	env->flatL=flatL;
	env->flatR=flatR;
	env->flat=flat;
	env->exp_uhatL=exp_uhatL;
	env->exp_uhatR=exp_uhatR;
	env->aux_denom = denom;

	// Backward Climate Preallocation
	// Precompute auxiliary variables
	env->const_phi = pow((env__gamma1/env__ksi)/(env__nu*(env__mu+env__gamma1/env__ksi)),(1./env__ksi));
	real squ_b = (env__alpha-1+(env__lambda+env__gamma1/env__ksi-(1-env__mu)-env__gamma1/(env__ksi*env__gamma2))*env__theta); // term in square brackets of natural_R and natural_L
	real naturalL = env__lambda - squ_b/denom;
	real naturalR = 1 - env__lambda*env__theta+(1+env__theta)*squ_b/denom;
	real natural = naturalR - env__theta*naturalL;
	exp_uhatL = naturalL/env__Omega + (1+env__theta)/denom;
	exp_uhatR = naturalR/env__Omega - env__theta*env__theta/denom;

	env->naturalL=naturalL;
	env->naturalR=naturalR;
	env->natural=natural;
	env->BW_exp_uhatL=exp_uhatL;
	env->BW_exp_uhatR=exp_uhatR;
	
	// Precompute auxiliary variables to equation (88)
	env->BL_H_m2_left[]=H.^((naturalL-1/denom)/exp_uhatL);
	env->BL_H_m2_left_exp=naturalL/(Omega*exp_uhatL);
	env->BR_H_m2_right[]=H.^(-naturalR+env__theta/denom);
	env->BR_H_m2_right_exp=-naturalR/Omega;

	// Set guesses
	ones_N = ones(env->n,1); // guess for uhat
	ltilde = round(env__lbar/(1+env->natal0)); // guess for global population
	lbar1 = env__lbar;
	
}
*/
void init_all(env_t *env) //, input_t *in, vars_t *vars)
{
	// 1. Initialize the Parameters
	// init_environment(env);
	// 1. Initialize Guesses
	init_guesses(env);
	/*
	// 2. Load initial land, amenities, productivities, population and wages
	init_land_amen_prod_pop_wages(env);
	// 3. Load and shape utility levels and HDI
	init_uti_HDI(env);
	// 4. Load trmult
	init_trmult(env);
	// 5. Load countries indices
	init_countries_indices(env);
	// 6. Construct CO2 emissions and clean energy use
	init_CO2_clean_energy(env);
	// 7. Construct energy parameters in technology
	init_energy_tech(env);
	// 8. Construct extraction cost function
	init_extraction_cost_fun(env);
	// 9. Construct energy productivity
	init_energy_productivity(env);
	// 10. Set carbon circulation parameters
	init_carbon_circulation(env);
	// 11. Set forcing parameters
	init_forcing_sensitivity(env);
	// 12. Set global temperature parameters
	init_temperature_global(env);
	// 13. Local January-July temperature from 1950 to 2000
	init_temperature_local(env);
	// 14. Load temperature scaler
	init_temperature_scaler(env);
	// 15. Load damage functions
	init_damage_fun(env);
	// 16. Load historical population
	init_population_historical(env);
	// 17. Load population predictions (UN)
	init_population_prediction(env);
	// 18. Construct climate predictions (IPCC)
	init_climate_prediction(env);
	// 19. Load historic CO2 emissions
	init_CO2_historical(env);
	// 20. Load gridded map
	init_map(env);
	// 21. Set numerical restrictions on natality functions
	//// 22. Define colors and variable names for plots
	// 21. Preallocation model_initial_period
	init_model_initial_period(env);
	*/
	return;
}

void free_all(env_t *env)
{
	// Free all Variables you have malloced in init_all
	// free(in->idshock);
	return;
}

// ----------------------------- DO NOT USE THIS SECTION FOR NOW
/*
void init_shock(env_t *env)
{
	env->P[IXP(0, 0, 0, 0)] = 0.525;
	env->P[IXP(0, 0, 0, 1)] = 0.35;
}

void init_prealloc(env_t *env, vars_t *vars)
{
	for (int ia = 0; ia < NSTATES_AG; ++ia) {
		env->trate[ia] = env->mu * (1.-env->er[ia]) / (env->l_bar*env->er[ia]);
		real taxrate = env->trate[ia];

		for(int ikm=0;ikm<NKM_GRID;ikm++)
		{
			// Interest Rate
			real irate = env->alpha*(env->ag[ia]*pow(env->km[ikm]/env->er[ia]/env->l_bar,env->alpha-1));
			// Wage
			real wage  =(1.-env->alpha)*(env->ag[ia]*pow(env->km[ikm]/env->er[ia]/env->l_bar,env->alpha));

			for(int iid=0;iid<NSTATES_ID;iid++)
				for(int ik=0;ik<NKGRID;ik++)
				{
					env->wealth[IXV(ia, ikm, iid, ik)] = (irate + 1.-env->delta) * env->k[ik] +
					wage * ( (1.-taxrate)* env->epsilon[iid]*env->l_bar+
							(1.-env->epsilon[iid]) * env->mu
							);
					vars->kprime_a[IXV(ia, ikm, iid, ik)]=0.9*env->k[ik];
				}
		}
	}
}

void init_k(env_t *env, vars_t *vars)
{
	real *x = (real *) malloc(NKGRID*sizeof(real));
	real xmin = 0;
	real xmax = 0.5;

	linear_space(KM_MIN, KM_MAX, NKM_GRID,env->km);
	// linear_space(KM_MIN, KM_MAX, NKM_GRID,env->km_egm);
	for(int ja=0;ja<NSTATES_AG;ja++)
		for(int jkm=0;jkm<NKM_GRID;jkm++)
			for(int jid=0;jid<NSTATES_ID;jid++)
				for(int jk=0;jk<NKGRID;jk++)
					vars->kprime_a[IXV(ja,jkm,jid,jk)] = NKPRIME_SCALE*env->k[jk];

	free(x);
	return;
}
*/
// ----------------------------- END DO NOT USE THIS SECTION FOR NOW