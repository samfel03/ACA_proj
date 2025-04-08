clear
clc
close all

global datafolder

datafolder='/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/EGGW Replication/Data';
inputfolder='/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input';
outputfolder='/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/output';

%% 0. Declare global variables

global H H0 amen_util0 C_vect prod0 pop0 pop0_dens pop1_dens pop5_dens u0 ...
     price_energy0 trmult_reduced n beta ...
     name_type_vect name_long_type_vect name_maps_type_vect ...
     alpha theta Omega HDI0 ...
     emi0_cell emi0 emi0_ff emi0_no_ff emi_no_ff emi_ff_data_tend chi cost_emi_param...
     a0 a1 a2 a3 b1 b2 b3 S0 S1 S2 S3 S_preind temp_preind...
     forc_sens forc_noCO2 c1 c2 d1 d2 temp1 temp2...
     temp0_global temp0_local_long temp0_local scaler_temp Delta_temp1...
     theta_amen_scen theta_prod_scen... 
     lbar lambda gamma1 gamma2 eta mu nu ksi...
     pop_low95 pop_low80 pop_med pop_high80 pop_high95...
     pop_low95_hist pop_low80_hist pop_med_hist pop_high80_hist pop_high95_hist...
     emi_ff_data forc_data length_C_vect...
     emiCO2_RCP stockCO2_RCP forc_RCP temp_global_RCP...
     price_clean0_world price_clean0 price_fossil0 zeta_clean0 zeta_fossil0 fossil_share...
     clean0_cell fossil0_cell epsilon clean_energy_data tCO2_toe map...
     color_olive color_darkgreen color_darkcyan color_yellowgreen color_greenyellow ...
     natal_param conv_usd table_prop...
     name_dam_vect name_dam_long_vect cost_CO2_data a_norm...
     natal_data country_data year_data pop_data temp_past Delta_temp max_cumCO2 natal0 natal20...

%% Launch Function
initialize(8.5,19500,1.6);

%% Global variable statistics
whos global
names = who('global');  %# A cell array of variable names
data = whos('global');  %# A structure array of variable information

for i=1:length(names)
    variable=names{i};
    if(isa(variable,'double')==1)
    display(variable);
    eval(strcat('[min,max]=stats_var(',variable,')'));
    data(i).min = min;
    data(i).max = max;
    %data(i).rows=rows;%data(i).cols=cols;
    data(i).MBytes=0.000001*data(i).bytes;
    end
end

%% Print Global Variables in csv
% Print scalars and vectors (no Matrixes)
printvarlist = {'H','prod0','pop5_dens','u0','a_norm','C_vect','emi0_ff',...
               'emi_no_ff', 'emi0','fossil_share','chi','cost_emi_param','price_clean0_world', 'price_energy0',...
    'zeta_clean0', 'zeta_fossil0', 'S0', 'S1', 'S2', 'S3', 'forc_noCO2', ...
    'temp1', 'temp2', 'temp0_global','temp0_local', ... 
     'scaler_temp', 'theta_amen_scen', 'theta_prod_scen', ...
    'natal_data', 'pop_data','natal0', 'natal20', 'clean_energy_data', 'emi_ff_data', 'emi_ff_data_tend'}; 
for j=1:length(printvarlist)
    var = printvarlist{j};
    display(var);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PRINT FILES AS BINARY (LIKE MAT FILES)
    % Lossless printing in fast binary files: https://www.mathworks.com/matlabcentral/answers/62037-how-can-i-export-data-from-matlab-to-a-txt-file-without-loosing-precision
    address = [inputfolder,'/',var,'.bin']; % set it as binary file
    fprintf("Printing variable %s in: %s\n",var,address);
    fid = fopen(address, 'w');
    eval(strcat('fwrite(fid,', var,', ''double'');'));
    fclose(fid);
end

% Print Matrixes
printmatlist = {'trmult_reduced','temp_past','Delta_temp'};
for j=1:length(printmatlist)
    var = printmatlist{j};
    display(var);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PRINT FILES AS BINARY (LIKE MAT FILES)
    % Lossless printing in fast binary files: https://www.mathworks.com/matlabcentral/answers/62037-how-can-i-export-data-from-matlab-to-a-txt-file-without-loosing-precision
    address = [inputfolder,'/',var,'.bin']; % set it as binary file
    eval(strcat('print_bin_2D_to_C(',var,',address);'));
end

%% Compare C-vs-Matlab Array and Matrixes
main_cmp_C_vs_matlab;

%% Load variables and verify that results are identical
%{
for j=1:length(printvarlist)
    var = printvarlist{j};
    display(var);
    if(~strcmp(var,'theta_amen_scen')&&(~strcmp(var,'theta_prod_scen')))
    address = [inputfolder,'/',var,'.bin']; % set it as binary file
    fprintf("Reading variable %s in: %s2\n",address,var);
    fid = fopen(address, 'r');
    eval(strcat(var,'2=fread(fid, size(',var,'),''double'');')); % H2 = fread(fid, 1, 'double);
    fclose(fid);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
    end
end
assert(sum(diff)==0); %% Vector of differences between variables is zero
%}

%% Dependency study: /Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/matlab/matlab-original
%H0, amen_util0 pop1_dens
% used in some plots: pop0 pop0_dens 
% w0: initialize.m	85	fundamentals.m
% HDI0: initialize.m fundamentals.m plots_backward.m
% u0: plots_central.m, initialize.m, fundamentals.m model_initial_period.m --> useful as supporting variable
% a_norm: plots_central.m, backward_climate.m, fundamentals.m, forward_climate.m, model_initial_period
% trmult_reduced: backward_climate.m initialize.m fundamentals.m forward_climate.m	migration_costs.m model_initial_period.m
% C_vect: estim_model.m plots_central.m initialize.m	fundamentals.m	plots_backward.m
% emi0_ff (scalar): backward_climate.m, initialize.m, forward_climate.m
% emi_no_ff (601x1): plots_append_agg.m, initialize.m	forward_climate.m
% emi0_no_ff (Scalar): initialize.m
% emi0: initialize.m forward_climate.m	
% emi0_cell: initialize.m main.m
% clean0_cell: plots_central.m initialize.m main.m
% fossil_share: estim_model.m backward_climate.m initialize.m fundamentals.m forward_climate.m
% chi (scalar): plots_central.m backward_climate.m initialize.m fundamentals.m forward_climate.m migration_costs.m model_initial_period.m
% cost_CO2_data (202x2): plots_append_agg.m initialize.m plots_backward.m
% cost_emi_param (1x7): plots_central.m plots_append_agg.m backward_climate.m initialize.m forward_climate.m plots_backward.m
% price_clean0_world (scalar): plots_central.m	backward_climate.m initialize.m forward_climate.m
% conv_usd (scalar): plots_append_agg.m initialize.m plots_backward.m
% fossil0_cell (17048x1): plots_central.m initialize.m main.m
% price_clean0 (17048x1): plots_central.m initialize.m main.m
% price_fossil0 (17048x1): plots_central.m initialize.m main.m
% price_energy0 (17048x1): initialize.m fundamentals.m model_initial_period.m
% zeta_clean0 (17048x1): plots_central.m backward_climate.m initialize.m forward_climate.m main.m
% zeta_fossil0 (17048x1): plots_central.m	 backward_climate.m initialize.m forward_climate.m
% a* (Scalar): initialize.m	forward_climate.m
% S_preind (scalar): initialize.m forward_climate.m main.m
% S0 S1 S2 S3 (scalar): initialize.m forward_climate.m main.m
% forc_noCO2 (601x1): initialize.m	forward_climate.m
% c1, c2, d1, d2, forc_data (scalar): initialize.m forward_climate.m main.m
% temp_preind (scalar): plots_central.m	plots_append_agg.m initialize.m plots_taxsub_agg.m
% forc_data (176x1): initialize.m
% temp1, temp2, temp0_global (scalar): initialize.m forward_climate.m main.m
% temp0_local_long (17048x10): initialize.m	main.m 
% temp0_local (17048x1): estim_model.m natal_fct.m plots_central.m initialize.m forward_climate.m plots_backward.m
% Delta_temp1 (17048x1): estim_model.m initialize.m	main.m 
% temp_past (17048x51): estim_model.m backward_climate.m initialize.m main.m
% Delta_temp (17048x50): estim_model.m backward_climate.m initialize.m forward_climate.m main.m             ************* TO BE CHECKED IF NEEDED 
% scaler_temp (17048x1): estim_model.m initialize.m forward_climate.m plots_backward.m
% theta_amen_scen (4x9): estim_model.m backward_climate.m initialize.m forward_climate.m main.m
% theta_prod_scen (4x9): estim_model.m backward_climate.m initialize.m forward_climate.m main.m
% country_data (8568x1): estim_model initialize main
% year_data (8568x1): estim_model initialize main plots_backward
% natal_data (8568x1): estim_model.m initialize.m main plots_backward
% pop_data (8568x1): estim_model.m initialize.m main plots_backward
% natal0 (scalar): natal_fct.m backward_climate.m initialize.m plots_backward.m
% natal20 (scalar): natal_fct.m initialize.m main.m
% pop_low95 (1x101) pop_low80 (1x101) pop_med (1x101) pop_high80 (1x101)
% pop_high95 (1x101) pop_low95_hist (1x151) pop_low80_hist (1x151) pop_med_hist (1x151) pop_high80_hist  (1x151)pop_high95_hist (1x151): used for plotting: plots_central initialize.m main.m
% emiCO2_RCP (601x4): plots_central.m plots_append_agg.m initialize.m plots_taxsub_agg.m main.m	
% forc_RCP (600x4): initialize main
% stockCO2_RCP (600x4): plots_central initialize main
% temp_global_RCP (600x4): plots_central.m	plots_append_agg.m initialize.m plots_taxsub_agg.m main.m
% clean_energy_data (35x1): estim_model.m initialize.m plots_backward.m
% emi_ff_data (50x1): estim_model.m initialize.m plots_backward.m
% emi_ff_data_tend (50x1): estim_model.m initialize.m plots_backward.m
% map (2700x5400): plots
% coeff_pop_i: estim_model.m backward_climate.m forward_climate.m main.m plots_backward.m

%% Print Global Variables in csv
% FULL LIST
%{
printvarlist = {'H','prod0','pop5_dens','u0','a_norm','trmult_reduced','C_vect','emi0_ff',...
               'emi_no_ff', 'emi0','fossil_share','chi','cost_emi_param','price_clean0_world', 'price_energy0',...
    'zeta_clean0', 'zeta_fossil0', 'S0', 'S1', 'S2', 'S3', 'forc_noCO2', ...
    'temp1', 'temp2', 'temp0_global','temp0_local', 'temp_past',... 
    'Delta_temp', 'scaler_temp', 'theta_amen_scen', 'theta_prod_scen', ...
    'natal_data', 'pop_data','natal0', 'natal20', 'clean_energy_data', 'emi_ff_data', 'emi_ff_data_tend'}; 
%}

