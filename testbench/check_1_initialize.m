
% This code: 
% 1. Loads all the required data to run the model.
% 2. Estimates the parameters of the natality rate function, 
% the migration cost function and the elasticities of 
% energy productivity growth to global real income grow.
% 3. Simulates the model forward in the baseline scenario 
% and each scenario displayed in the paper. 
% 4. Plots the maps and figures.
% 5. Stores the output.

%% 0. Loads all the necessary data to run the model

clear 
clc

addpath('Functions')

% Set global variables
global H H0 amen_util0 C_vect prod0 pop0 pop0_dens pop1_dens pop5_dens u0...
     trmult_reduced n beta price_energy0 alpha theta Omega HDI0...
     emi0_cell emi0 emi0_ff emi0_no_ff emi_no_ff emi_ff_data_tend chi cost_emi_param...
     a0 a1 a2 a3 b1 b2 b3 S0 S1 S2 S3 S_preind temp_preind...
     forc_sens forc_noCO2 c1 c2 d1 d2 temp1 temp2...
     temp0_local_long temp0_local Delta_temp1 temp_past Delta_temp...
     temp0_global scaler_temp theta_amen_scen theta_prod_scen... 
     lbar lambda gamma1 gamma2 eta mu nu ksi conv_usd ...
     pop_low95 pop_low80 pop_med pop_high80 pop_high95...
     pop_low95_hist pop_low80_hist pop_med_hist pop_high80_hist pop_high95_hist...
     emi_ff_data forc_data length_C_vect table_prop...
     emiCO2_RCP stockCO2_RCP forc_RCP temp_global_RCP...
     price_clean0_world price_clean0 price_fossil0 zeta_clean0 zeta_fossil0 fossil_share epsilon clean_energy_data tCO2_toe...
     clean0_cell fossil0_cell map ...
     color_olive color_darkgreen color_darkcyan color_yellowgreen color_greenyellow  ...
     natal_param name_dam_vect name_dam_long_vect cost_CO2_data a_norm...
     natal_data country_data year_data pop_data max_cumCO2 natal0 natal20
     
% Initialize model
initialize(8.5,19500,1.6) % benchmark estimation

%% Load variables from C/input/


%% Compare ALL variables

