
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

%% 1. Estimates natality function, migration costs and energy productivities

% Guess on natality function, migration costs, upsilon_fossil and upsilon_clean
coeff_pop_i = [-0.69;0;-5;-0.51;-0.25;-5;2.88;-0.67]; % [ b0y, b1y, b1y', b2y, bsy, b1T, b2T, bsT ]
upsilon_fossil_i = 1.15;
upsilon_clean_i = 1.15;

% Set speed of update for migration costs, upsilon_fossil and upsilon_clean
update_vect = [1 0.95 0.95]';

% Set tolerance of errors
tol_clean = 1.2; 
tol_fossil = 2.5; 
tol_m2 = 1e9; %1e6;
tol_l = 1e9; %1e6;
tol_nlls = 0;
tol_final_SSR = 1e-5;
tol_m2_inner = 1e-8;
tol_step = 40;
tol_vect = [ tol_clean tol_fossil tol_m2 tol_l ...
    tol_nlls tol_final_SSR tol_m2_inner tol_step ]';

% Parameters
ind_dam = 9;

tic
estim_model( coeff_pop_i, upsilon_fossil_i, upsilon_clean_i, ...
    ind_dam, update_vect, tol_vect );
toc

%% 2. Runs model backward --baseline estimation  

% Set features of the simulation
T_back = 50;            % number of periods
ind_dam = 9;            % damage function level: baseline
name_dam = name_dam_vect{ind_dam};

% Run model backwards
[ l_Warm_b, u_Warm_b, prod_Warm_b, realgdp_Warm_b, amen_Warm_b, ...
    emiCO2_ff_Warm_b, temp_local_Warm_b, ...
    price_emi_Warm_b, clean_Warm_b, ...
    price_clean_Warm_b, net_births_Warm_b ] = ...
    backward_climate( T_back, 1, ind_dam );

% Store results
save(['Data/derived/results_backward_Warm_' name_dam '.mat'],...
    'l_Warm_b', 'u_Warm_b', 'prod_Warm_b', 'realgdp_Warm_b', 'amen_Warm_b', ...
    'emiCO2_ff_Warm_b', 'temp_local_Warm_b', 'price_emi_Warm_b', ...
    'clean_Warm_b', 'price_clean_Warm_b', 'net_births_Warm_b', '-v7.3')
 
%% 3. Runs model forward --baseline estimation 

% Set features of the simulation
T = 400;                    % number of periods
ind_dam = 9;                % damage function level: baseline
% ind_dam = 1;              % damage function level: worst-scenario
name_dam = name_dam_vect{ind_dam};
taxCO2 = zeros(n,T);        % path for carbon taxes
subclean = zeros(n,T);      % path for clean energy subsidies
abat = zeros(n,T);          % path for abatement
val_adap = ones(3,1);       % degree of adaptation: baseline
         
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Model with Warming Damages
display([newline 'Warming Damages' newline])

% Run model forward
[ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
    emiCO2_ff_Warm, emiCO2_total_Warm, stockCO2_Warm, ...
    temp_global_Warm, temp_local_Warm, price_emi_Warm, ...
    clean_Warm, price_clean_Warm, net_births_Warm ] = ...
    forward_climate( T, 1, ind_dam, 0, ...
	taxCO2, subclean, abat, val_adap );

% Store results
save(['Data/derived/results_forward_Warm_' name_dam '.mat'],...
    'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', ...
    'emiCO2_ff_Warm', 'emiCO2_total_Warm', 'stockCO2_Warm', 'temp_global_Warm', ...
    'temp_local_Warm', 'amen_Warm', 'price_emi_Warm', 'clean_Warm', ...
    'price_clean_Warm', 'net_births_Warm', '-v7.3')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Model with no Warming Damages
display([newline 'No Warming Damages' newline])

% Run model forward
[ l_noWarm, u_noWarm, prod_noWarm, realgdp_noWarm, amen_noWarm, ...
    emiCO2_ff_noWarm, emiCO2_total_noWarm, stockCO2_noWarm, ...
    temp_global_noWarm, temp_local_noWarm, price_emi_noWarm, ...
    clean_noWarm, price_clean_noWarm, net_births_noWarm ] = ...
    forward_climate( T, 0, ind_dam, 0, ...
	taxCO2, subclean, abat, val_adap );

% Store results
save('Data/derived/results_forward_noWarm.mat',...
    'l_noWarm', 'u_noWarm', 'prod_noWarm', 'realgdp_noWarm', ...
    'emiCO2_ff_noWarm', 'emiCO2_total_noWarm', 'stockCO2_noWarm', 'temp_global_noWarm', ...
    'temp_local_noWarm', 'amen_noWarm', 'price_emi_noWarm', 'clean_noWarm', ...
    'price_clean_noWarm', 'net_births_noWarm', '-v7.3')

%% 4. Runs model forward --by damage function level

% Set features of the simulation
T = 400;                    % number of periods
taxCO2 = zeros(n,T);        % path for carbon taxes
subclean = zeros(n,T);      % path for clean energy subsidies
abat = zeros(n,T);          % path for abatement
val_adap = ones(3,1);       % degree of adaptation: baseline

for ind_dam = 1:8 
    
	name_dam = name_dam_vect{ind_dam};
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages
    display([newline 'Warming Damages; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean, abat, val_adap );    
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
    
end
 
%% 5. Runs model forward --by damage source

% Set features of the simulation
T = 400;                    % number of periods
ind_dam = 9;                % damage function level: baseline
name_dam = name_dam_vect{ind_dam};
taxCO2 = zeros(n,T);        % path for carbon taxes
subclean = zeros(n,T);      % path for clean energy subsidies
abat = zeros(n,T);          % path for abatement
val_adap = ones(3,1);       % degree of adaptation: baseline

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Model with Warming Damages only on amenities
display([newline 'Warming Damages only on Amenities' newline])

% Run model forward
[ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
    ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
    forward_climate( T, 2, ind_dam, 0, ...
    taxCO2, subclean, abat, val_adap );

% Store results
save(['Data/derived/results_forward_WarmAm_' name_dam '.mat'],...
    'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
    'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Model with Warming Damages only on productivities
display([newline 'Warming Damages only on Productivities' newline])

% Run model forward
[ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
    ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
    forward_climate( T, 3, ind_dam, 0, ...
    taxCO2, subclean, abat, val_adap );

% Store results
save(['Data/derived/results_forward_WarmPr_' name_dam '.mat'],...
    'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
    'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

%% 6. Runs model forward, adaptation --endogenous temp and pop

% Set features of the simulation
T = 400;                    % number of periods
ind_dam = 9;                % damage function level: baseline
name_dam = name_dam_vect{ind_dam};
taxCO2 = zeros(n,T);        % path for carbon taxes
subclean = zeros(n,T);      % path for clean energy subsidies
abat = zeros(n,T);          % path for abatement
val_adap_vect = [1.5 2; 1.125 1.25; 0.5 0.667];     % degree of adaptation
name_adap_vect = {'endTr' 'endMi' 'endIn'};

for type_adap = 1:3
    for ind_adap = 1:2
        
        val_adap = ones(3,1);
        val_adap(type_adap) = val_adap_vect(type_adap,ind_adap);
        name_adap = [name_adap_vect{type_adap} num2str(val_adap_vect(type_adap,ind_adap))];
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Model with Warming Damages, adaptation migration, endogenous
        display([newline 'Warming Damages; name_dam = ' name_dam '; name_adap = ' name_adap newline])
        
        % Run model forward
        [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
            ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
            forward_climate( T, 1, ind_dam, 0, ...
            taxCO2, subclean, abat, val_adap );
        
        % Store results
        save(['Data/derived/results_forward_Warm_' name_dam '_' name_adap '.mat'],...
            'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
            'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Model with no Warming Damages, adaptation migration, endogenous
        display([newline 'No Warming Damages; name_adap = ' name_adap newline])
        
        % Run model forward
        [ l_noWarm, u_noWarm, prod_noWarm, realgdp_noWarm, amen_noWarm, ...
            ~, emiCO2_total_noWarm, ~, temp_global_noWarm, ~, ~, ~, ~, ~ ] = ...
            forward_climate( T, 0, ind_dam, 0, ...
            taxCO2, subclean, abat, val_adap );
        
        % Store results
        save(['Data/derived/results_forward_noWarm_' name_adap '.mat'],...
            'l_noWarm', 'u_noWarm', 'prod_noWarm', 'realgdp_noWarm', 'amen_noWarm', ...
            'emiCO2_total_noWarm', 'temp_global_noWarm', '-v7.3')
        
    end
end

%% 7. Runs model forward, adaptation --exogenous temp and pop

% Set features of the simulation
T = 400;                    % number of periods
ind_dam = 9;                % damage function level: baseline
name_dam  = name_dam_vect{ind_dam};
taxCO2 = zeros(n,T);        % path for carbon taxes
subclean = zeros(n,T);      % path for clean energy subsidies
abat = zeros(n,T);          % path for abatement
val_adap_vect = [1.5 2; 1.125 1.25; 0.5 0.667];     % degree of adaptation
name_adap_vect = {'exoTr' 'exoMi' 'exoIn'};
        
for type_adap = 1:3
    for ind_adap = 1:2
        
        val_adap = ones(3,1);
        val_adap(type_adap) = val_adap_vect(type_adap,ind_adap);
        name_adap = [name_adap_vect{type_adap} num2str(val_adap_vect(type_adap,ind_adap))];
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Model with Warming Damages, adaptation migration, exogenous
        display([newline 'Warming Damages, adaptation migration, exogenous temp and pop' '; name_dam = ' name_dam '; name_adap = ' name_adap newline])
        
        % Run model forward
        [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
            ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
            forward_climate( T, 1, ind_dam, 1, ...
            taxCO2, subclean, abat, val_adap );
        
        % Store results
        save(['Data/derived/results_forward_Warm_' name_dam '_' name_adap '.mat'],...
            'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
            'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Model with no Warming Damages, adaptation migration, exogenous
        display([newline 'No Warming Damages, adaptation migration, exogenous temp and pop' '; name_adap = ' name_adap newline])
        
        % Run model forward
        [ l_noWarm, u_noWarm, prod_noWarm, realgdp_noWarm, amen_noWarm, ...
            ~, emiCO2_total_noWarm, ~, temp_global_noWarm, ~, ~, ~, ~, ~ ] = ...
            forward_climate( T, 0, ind_dam, 1, ...
            taxCO2, subclean, abat, val_adap );
        
        % Store results
        save(['Data/derived/results_forward_noWarm_' name_adap '.mat'],...
            'l_noWarm', 'u_noWarm', 'prod_noWarm', 'realgdp_noWarm', 'amen_noWarm', ...
            'emiCO2_total_noWarm', 'temp_global_noWarm', '-v7.3')
        
    end
end

%% 8. Runs model forward --taxes and subsidies with and without abatement

% Set features of the simulation
T = 400;                    % number of periods
ind_dam = 9;                % damage function level: baseline
% ind_dam = 1;              % damage function level: worst-scenario
name_dam = name_dam_vect{ind_dam};
val_adap = ones(3,1);       % degree of adaptation: baseline
val_pol = 1:3;
% val_pol = 4;
% val_pol = 5;

for ind_pol = val_pol
    
if ind_pol == 1             % carbon taxes of 50%, 100% and 200% with no abatment
taxCO2_vect = [0.5 1 2]; 
subclean_vect = 0; 
abat = zeros(n,T); 
name_abat = ''; 
elseif ind_pol == 2         % carbon taxes of 50%, 100% and 200% with abatment in 2100
taxCO2_vect = [0.5 1 2]; 
subclean_vect = 0; 
abat = zeros(n,T); 
abat(:,100:end) = 1; 
name_abat = '_abat2100_100pp'; 
elseif ind_pol == 3         % clean energy subsidies of 25%, 50% and 75%
taxCO2_vect = 0; 
subclean_vect = [0.25 0.5 0.75];
abat = zeros(n,T); 
name_abat = '';     
elseif ind_pol == 4         % carbon taxes of 50%, 100% and 200% with clean energy subsidies of 25%, 50% and 75%
taxCO2_vect = [0.5 1 2]; 
subclean_vect = [0.25 0.5 0.75];
abat = zeros(n,T); 
name_abat = '';     
elseif ind_pol == 5         % carbon taxes of 50%, 100% and 200% with abatment in 2200
taxCO2_vect = [0.5 1 2]; 
subclean_vect = 0; 
abat = zeros(n,T); 
abat(:,200:end) = 1; 
name_abat = '_abat2200_100pp'; 
end
length_tax = length(taxCO2_vect);
length_sub = length(subclean_vect);

if strcmp(name_abat,'') ~= 1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Model with Warming Damages
display([newline 'Warming Damages; name_dam = ' name_dam ...
	'; tax = 0; subs = 0; name_abat = ' name_abat newline])
        
% Run model forward
[ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
	~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
    forward_climate( T, 1, ind_dam, 0, ...
    zeros(n,T), zeros(n,T), abat, val_adap );
        
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam name_abat '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
end    
    
for ind_sub = 1:length_sub
    for ind_tax = 1:length_tax
        
        taxCO2 = taxCO2_vect(ind_tax)*ones(n,T);
        subclean = subclean_vect(ind_sub)*ones(n,T);
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Model with Warming Damages
        display([newline 'Warming Damages; name_dam = ' name_dam ...
            '; tax = ' num2str(100*taxCO2_vect(ind_tax)) ...
            '; subs = ' num2str(100*subclean_vect(ind_sub)) ...
            '; name_abat = ' name_abat newline])
        
        % Run model forward
        [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
            ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
            forward_climate( T, 1, ind_dam, 0, ...
            taxCO2, subclean, abat, val_adap );
        
        % Store results
        save(['Data/derived/results_forward_Warm_' name_dam ...
            '_tax' num2str(100*taxCO2_vect(ind_tax)) ...
            '_sub' num2str(100*subclean_vect(ind_sub)) name_abat '.mat'],...
            'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
            'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
        
    end
end

end

%% 9. Runs model forward --different values for eps

% Set features of the simulation
T = 400;                         % number of periods
ind_dam = 9;                     % damage function level: baseline
name_dam = name_dam_vect{ind_dam};
taxCO2 = zeros(n,T);             % path for carbon taxes
subclean = zeros(n,T);           % path for clean energy subsidies
abat = zeros(n,T);               % path for abatement
taxCO2_alt = 2*ones(n,T);        % alternative path for carbon taxes
subclean_alt = 0.75*ones(n,T);   % alternative path for clean energy subsidies
abat_alt = zeros(n,T);           % alternative path for abatement
abat_alt(:,100:end) = 1; 
name_abat = '_abat2100_100pp';
val_adap = ones(3,1);            % degree of adaptation: baseline
eps_vect = [0.5 3 6];            % values for eps

for ind_eps = 1:length(eps_vect)
    
    % Initialize model
    initialize(8.5,19500,eps_vect(ind_eps));

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages
    display([newline 'Warming Damages; eps = ' num2str(eps_vect(ind_eps)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_eps' num2str(eps_vect(ind_eps)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with no Warming Damages
    display([newline 'No Warming Damages; eps = ' num2str(eps_vect(ind_eps)) newline])
    
    % Run model forward
    [ l_noWarm, u_noWarm, prod_noWarm, realgdp_noWarm, amen_noWarm, ...
        ~, emiCO2_total_noWarm, ~, temp_global_noWarm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 0, ind_dam, 0, ...
        taxCO2, subclean, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_noWarm_eps' num2str(eps_vect(ind_eps)) '.mat'],...
        'l_noWarm', 'u_noWarm', 'prod_noWarm', 'realgdp_noWarm', 'amen_noWarm', ...
        'emiCO2_total_noWarm', 'temp_global_noWarm', '-v7.3')
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Taxes of 200%
    display([newline 'Warming Damages; eps = ' num2str(eps_vect(ind_eps)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2_alt, subclean, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_tax' num2str(200) ...
        '_sub' num2str(0) '_eps' num2str(eps_vect(ind_eps)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Subsidies of 75%
    display([newline 'Warming Damages; eps = ' num2str(eps_vect(ind_eps)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean_alt, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_tax' num2str(0) ...
        '_sub' num2str(75) '_eps' num2str(eps_vect(ind_eps)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Abatement
    display([newline 'Warming Damages; eps = ' num2str(eps_vect(ind_eps)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean, abat_alt, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam ...
        name_abat '_eps' num2str(eps_vect(ind_eps)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Taxes of 200% with Abatement
    display([newline 'Warming Damages; eps = ' num2str(eps_vect(ind_eps)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2_alt, subclean, abat_alt, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_tax' num2str(200) ...
        '_sub' num2str(0) name_abat '_eps' num2str(eps_vect(ind_eps)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

end

%% 10. Runs model forward --different values for maxCO2

% Set features of the simulation
T = 400;                            % number of periods
ind_dam = 9;                        % damage function level: baseline
name_dam = name_dam_vect{ind_dam};
taxCO2 = zeros(n,T);                % path for carbon taxes
subclean = zeros(n,T);              % path for clean energy subsidies
abat = zeros(n,T);                  % path for abatement
taxCO2_alt = 2*ones(n,T);           % alternative path for carbon taxes
subclean_alt = 0.75*ones(n,T);      % alternative path for clean energy subsidies
abat_alt = zeros(n,T);              % alternative path for abatement
abat_alt(:,100:end) = 1; 
name_abat = '_abat2100_100pp';
val_adap = ones(3,1);               % degree of adaptation: baseline
maxCO2_vect = [7900 45300];         % values for maxCO2 

for ind_maxCO2 = 1:length(maxCO2_vect)
    
    % Initialize model
    initialize(8.5,maxCO2_vect(ind_maxCO2),1.6);
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages
    display([newline 'Warming Damages; maxCO2 = ' num2str(maxCO2_vect(ind_maxCO2)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_maxCO2' num2str(maxCO2_vect(ind_maxCO2)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with no Warming Damages
    display([newline 'No Warming Damages; maxCO2 = ' num2str(maxCO2_vect(ind_maxCO2)) newline])
    
    % Run model forward
    [ l_noWarm, u_noWarm, prod_noWarm, realgdp_noWarm, amen_noWarm, ...
        ~, emiCO2_total_noWarm, ~, temp_global_noWarm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 0, ind_dam, 0, ...
        taxCO2, subclean, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_noWarm_maxCO2' num2str(maxCO2_vect(ind_maxCO2)) '.mat'],...
        'l_noWarm', 'u_noWarm', 'prod_noWarm', 'realgdp_noWarm', 'amen_noWarm', ...
        'emiCO2_total_noWarm', 'temp_global_noWarm', '-v7.3')
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Taxes of 200%
    display([newline 'Warming Damages; maxCO2 = ' num2str(maxCO2_vect(ind_maxCO2)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2_alt, subclean, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_tax' num2str(200) ...
        '_sub' num2str(0) '_maxCO2' num2str(maxCO2_vect(ind_maxCO2)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Subsidies of 75%
    display([newline 'Warming Damages; maxCO2 = ' num2str(maxCO2_vect(ind_maxCO2)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean_alt, abat, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_tax' num2str(0) ...
        '_sub' num2str(75) '_maxCO2' num2str(maxCO2_vect(ind_maxCO2)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Abatement
    display([newline 'Warming Damages; maxCO2 = ' num2str(maxCO2_vect(ind_maxCO2)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2, subclean, abat_alt, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam ...
        name_abat '_maxCO2' num2str(maxCO2_vect(ind_maxCO2)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Model with Warming Damages and Taxes of 200% with Abatement
    display([newline 'Warming Damages; maxCO2 = ' num2str(maxCO2_vect(ind_maxCO2)) '; name_dam = ' name_dam newline])
    
    % Run model forward
    [ l_Warm, u_Warm, prod_Warm, realgdp_Warm, amen_Warm, ...
        ~, emiCO2_total_Warm, ~, temp_global_Warm, ~, ~, ~, ~, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        taxCO2_alt, subclean, abat_alt, val_adap );
    
    % Store results
    save(['Data/derived/results_forward_Warm_' name_dam '_tax' num2str(200) ...
        '_sub' num2str(0) name_abat '_maxCO2' num2str(maxCO2_vect(ind_maxCO2)) '.mat'],...
        'l_Warm', 'u_Warm', 'prod_Warm', 'realgdp_Warm', 'amen_Warm', ...
        'emiCO2_total_Warm', 'temp_global_Warm', '-v7.3')

end

%% 11. Plots time series and maps --backward solution

% Set plot specifications
ind_dam = 9;            % damage function level: baseline

% Plot backward results
plots_backward( ind_dam );

%% 12. Plots time series and maps --central estimation

% Set plot specifications
nbins = 50;             % number of bins in histogram
ind_dam = 9;            % damage function level: baseline
% ind_dam = 1;          % damage function level: worst-scenario
ind_type = 1;           % damage function source: amenities and productivities
name_adap = '';         % baseline degree of adaptation
taxCO2_val = 0;         % no carbon taxes
subclean_val = 0;       % no clean subsidies
name_abat = '';         % no abatement
eps = 1.6;              % baseline elasticity of substitution
maxCO2 = 19500;         % baseline fossil fuel deposit size
beta_plot = beta;       % discount factor
% beta_plot = 0.969;    % discount factor

% Plot baseline results
[ ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~ ] = ...
    plots_central( nbins, ind_dam, ind_type, name_adap, ...
    taxCO2_val, subclean_val, name_abat, eps, maxCO2, beta_plot, 1 );

%% 13. Plots time series and maps --across damage scenarios 

% Set plot specifications
T = 400;                % number of periods
nbins = 50;             % number of bins in histogram
ind_type = 1;           % damage function source: amenities and productivities
name_adap = '';         % baseline degree of adaptation
taxCO2_val = 0;         % no carbon taxes
subclean_val = 0;       % no clean subsidies
name_abat = '';         % no abatement
eps = 1.6;              % baseline elasticity of substitution
maxCO2 = 19500;         % baseline fossil fuel deposit size
beta_plot = beta;       % discount factor
% beta_plot = 0.969;    % discount factor

amen_w_dam = NaN(T,9);
prod_w_dam = NaN(T,9);
realgdp_w_dam = NaN(T,9);
util_w_dam = NaN(T,9);
PDV_realgdp_dam = NaN(n,9);
PDV_util_dam = NaN(n,9);

% Plot results for each level of the damage function
for ind_dam=1:9
    [amen_w_dam(:,ind_dam), prod_w_dam(:,ind_dam), ...
        realgdp_w_dam(:,ind_dam), util_w_dam(:,ind_dam), ...
        PDV_realgdp_dam(:,ind_dam), PDV_util_dam(:,ind_dam), ...
        ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~ ] = ...
        plots_central( nbins, ind_dam, ind_type, name_adap, ...
        taxCO2_val, subclean_val, name_abat, eps, maxCO2, beta_plot, 0 );
end
save('Data/derived/results_dam.mat',...
    'amen_w_dam', 'prod_w_dam', 'realgdp_w_dam', ...
    'util_w_dam','PDV_realgdp_dam','PDV_util_dam','-v7.3')
load('Data/derived/results_dam.mat')

% Plot results for all levels of the damage function
plots_dam_agg( amen_w_dam, prod_w_dam, ...
    realgdp_w_dam, util_w_dam, ...
    PDV_realgdp_dam, PDV_util_dam, beta_plot );

%% 14. Plots time series and maps --across damage sources

% Set plot specifications
T = 400;                % number of periods
nbins = 50;             % number of bins in histogram
ind_dam = 9;            % damage function level: baseline
name_adap = '';         % baseline degree of adaptation
taxCO2_val = 0;         % no carbon taxes
subclean_val = 0;       % no clean subsidies
name_abat = '';         % no abatement
eps = 1.6;              % baseline elasticity of substitution
maxCO2 = 19500;         % baseline fossil fuel deposit size
beta_plot = beta;       % discount factor
% beta_plot = 0.969;    % discount factor

amen_w_source = NaN(T,3);
prod_w_source = NaN(T,3);
realgdp_w_source = NaN(T,3);
util_w_source = NaN(T,3);
PDV_realgdp_source = NaN(n,3);
PDV_util_source = NaN(n,3);

% Plot results for each source of the damage function
for ind_type=1:3
    [amen_w_source(:,ind_type), prod_w_source(:,ind_type), ...
        realgdp_w_source(:,ind_type), util_w_source(:,ind_type), ...
        PDV_realgdp_source(:,ind_type), PDV_util_source(:,ind_type), ...
        ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~ ] = ...
        plots_central( nbins, ind_dam, ind_type, name_adap, ...
        taxCO2_val, subclean_val, name_abat, eps, maxCO2, beta_plot, -1 );
end
save('Data/derived/results_source.mat',...
    'amen_w_source', 'prod_w_source', 'realgdp_w_source', ...
    'util_w_source','PDV_realgdp_source','PDV_util_source','-v7.3')
load('Data/derived/results_source.mat')

% Plot results for all sources of the damage function
plots_source_agg( amen_w_source, prod_w_source, ...
    realgdp_w_source, util_w_source, ...
    PDV_realgdp_source, PDV_util_source, beta_plot );

%% 15. Plots time series and maps --adaptation mechanisms

% Set plot specifications
T = 400;                % number of periods
nbins = 50;             % number of bins in histogram
ind_type = 1;           % damage function source: amenities and productivities
type_adap_long_name = {'Mi';'Tr';'In'};         % source of adaptation
val_adap_mat = [1.125 1.25;1.5 2;0.667 0.5];    % degree of adaptation
var1_name = {'m_2(r)^{';'\varsigma(r,s)^{';'\gamma_1/\xi\cdot'};
var2_name = {'}, ';'}, ';', '};
ind_dam = 9;            % damage function level: baseline
taxCO2_val = 0;         % no carbon taxes
subclean_val = 0;       % no clean subsidies
name_abat = '';         % no abatement
eps = 1.6;              % baseline elasticity of substitution
maxCO2 = 19500;         % baseline fossil fuel deposit size
beta_plot = beta;       % discount factor

names1_exo_end = {'_exo','_exo','_end','_end'};
names2_exo_end = {'exog','exog','endog','endog'};

[amen_w_dam, prod_w_dam, ...
    realgdp_w_dam, util_w_dam, ...
    PDV_realgdp_dam, PDV_util_dam, ...
	~, ~, ~, ~, ~, ~, ~, ~, ~, ~, lbar_w_dam ] = ...
    plots_central( nbins, ind_dam, ind_type, '', ...
    taxCO2_val, subclean_val, name_abat, eps, maxCO2, beta_plot, 0 );

for ind_long = 1:3
    
    type_adap_name = type_adap_long_name{ind_long};
    length_adap = 2*length(val_adap_mat(ind_long,:));
    val_adap = repmat(val_adap_mat(ind_long,:),1,2);
    var1_aux = var1_name{ind_long};
    var2_aux = var2_name{ind_long};
    names_adap = cell(length_adap,1,1);
    long_names_adap = cell(length_adap,1,1);
    amen_w_adap = zeros(T,length_adap);
    prod_w_adap = zeros(T,length_adap);
    realgdp_w_adap = zeros(T,length_adap);
    util_w_adap = zeros(T,length_adap);
    lbar_w_adap = zeros(T,length_adap);
    PDV_realgdp_adap = zeros(n,length_adap);
    PDV_util_adap = zeros(n,length_adap);
    
    for ind_adap = 1:length_adap
        
        names_adap{ind_adap} = [names1_exo_end{ind_adap} type_adap_name num2str(val_adap(ind_adap))];
        long_names_adap{ind_adap} = [var1_aux num2str(val_adap(ind_adap)) var2_aux names2_exo_end{ind_adap} ' temp'];
        
        [amen_w_adap(:,ind_adap), prod_w_adap(:,ind_adap), ...
            realgdp_w_adap(:,ind_adap), util_w_adap(:,ind_adap), ...
            PDV_realgdp_adap(:,ind_adap), PDV_util_adap(:,ind_adap), ...
            ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, lbar_w_adap(:,ind_adap) ] = ...
            plots_central( nbins, ind_dam, ind_type, names_adap{ind_adap}, ...
            taxCO2_val, subclean_val, name_abat, eps, maxCO2, beta_plot, 0 );
    end
    
    save(['Data/derived/results_adap_' type_adap_name '.mat'],...
        'amen_w_dam', 'amen_w_adap', 'prod_w_dam', 'prod_w_adap', ...
        'realgdp_w_dam', 'realgdp_w_adap', 'util_w_dam', 'util_w_adap', ...
        'PDV_realgdp_dam', 'PDV_realgdp_adap', ...
        'PDV_util_dam', 'PDV_util_adap', 'lbar_w_dam', 'lbar_w_adap', '-v7.3')
    load(['Data/derived/results_adap_' type_adap_name '.mat'])
    
    plots_adap_agg( ...
        amen_w_dam, amen_w_adap, prod_w_dam, prod_w_adap, ...
        realgdp_w_dam, realgdp_w_adap, util_w_dam, util_w_adap, ...
        lbar_w_dam, lbar_w_adap , ...
        PDV_realgdp_dam, PDV_realgdp_adap, ...
        PDV_util_dam, PDV_util_adap, ...
        names_adap, long_names_adap, beta_plot );

end

%% 16. Plots time series and maps --taxes and subsidies with and without abatement

% Set plot specifications
T = 400;                % number of periods
nbins = 50;             % number of bins in histogram
ind_dam = 9;            % damage function level: baseline
% ind_dam = 1;          % damage function level: worst-case
ind_type = 1;           % damage function source: amenities and productivities
name_adap = '';         % baseline degree of adaptation
eps = 1.6;              % baseline elasticity of substitution
maxCO2 = 19500;         % baseline fossil fuel deposit size
beta_vect = [beta;0.969];   % discount factor

% Set taxes and subsidies
names_long_taxes = {'tax200p_sub0p';'tax0p_sub75p'}; 
names_long_abat = {'_abat2100_100pp';''}; 

% names_long_taxes = {'tax200p_sub75p'}; 
% names_long_abat = {''}; 

% names_long_taxes = {'tax200p_sub0p'}; 
% names_long_abat = {'_abat2200_100pp'}; 

pop0_weight = pop0_dens.*H/lbar;
name_dam = name_dam_vect{ind_dam};

for ind_long = 1:length(names_long_taxes)
    names_taxes = names_long_taxes{ind_long};
    names_abat = names_long_abat{ind_long};
    n_abat = 2-strcmp(names_abat,'');
    
    if strcmp(names_taxes,'tax200p_sub0p') == 1
        taxCO2_vect = [0.5 1 2];
        subclean_vect = 0;
    elseif strcmp(names_taxes,'tax0p_sub75p') == 1
        taxCO2_vect = 0;
        subclean_vect = [0.25 0.5 0.75];
    elseif strcmp(names_taxes,'tax200p_sub75p') == 1
        taxCO2_vect = [0 0.5 1 2];
        subclean_vect = [0 0.25 0.5 0.75];
    end
    
    length_taxCO2 = length(taxCO2_vect);
    length_subclean = length(subclean_vect);
    
    realgdp_w_Warm_tax = zeros(T,length_taxCO2,length_subclean,n_abat);
    util_w_Warm_tax = zeros(T,length_taxCO2,length_subclean,n_abat);
    PDV_realgdp_Warm_tax = zeros(n,length_taxCO2,length_subclean,n_abat);
    PDV_util_Warm_tax = zeros(n,length_taxCO2,length_subclean,n_abat);
    PDV_realgdp_w_Warm_tax = zeros(length_taxCO2,length_subclean,n_abat);
    PDV_util_w_Warm_tax = zeros(length_taxCO2,length_subclean,n_abat);
    emiCO2_total_Warm_tax = zeros(T,length_taxCO2,length_subclean,n_abat);
    clean_total_Warm_tax = zeros(T,length_taxCO2,length_subclean,n_abat);
    temp_global_Warm_tax = zeros(T,length_taxCO2,length_subclean,n_abat);
    BGP_realgdp_Warm_tax = zeros(length_taxCO2,length_subclean,n_abat);
    BGP_util_Warm_tax = zeros(length_taxCO2,length_subclean,n_abat);
    
    emiCO2_total_Warm = zeros(T,n_abat);
    clean_total_Warm = zeros(T,n_abat);
    temp_global_Warm = zeros(T,n_abat);
    BGP_realgdp_Warm = zeros(n_abat,1);
    BGP_util_Warm = zeros(n_abat,1);
    
    if length_taxCO2 == 1 || length_subclean == 1
        PDV_realgdp_tax_vect = zeros(length_taxCO2*length_subclean+1,length(beta_vect));
        PDV_util_tax_vect = zeros(length_taxCO2*length_subclean+1,length(beta_vect));
    else
        PDV_realgdp_tax_vect = zeros(length_taxCO2,length_subclean,length(beta_vect));
        PDV_util_tax_vect = zeros(length_taxCO2,length_subclean,length(beta_vect));
    end
    
    for ind_beta = 1:length(beta_vect)
        for ind_sub = 1:length_subclean
            for ind_tax = 1:length_taxCO2
                
                [ ~, ~, realgdp_w_Warm_tax(:,ind_tax,ind_sub,1), util_w_Warm_tax(:,ind_tax,ind_sub,1), ...
                    PDV_realgdp_Warm_tax(:,ind_tax,ind_sub,1), PDV_util_Warm_tax(:,ind_tax,ind_sub,1), ...
                    emiCO2_total_Warm_tax(:,ind_tax,ind_sub,1), emiCO2_total_Warm(:,1), ...
                    clean_total_Warm_tax(:,ind_tax,ind_sub,1), clean_total_Warm(:,1), ...
                    temp_global_Warm_tax(:,ind_tax,ind_sub,1), temp_global_Warm(:,1), ...
                    BGP_realgdp_Warm_tax(ind_tax,ind_sub,1), BGP_realgdp_Warm(1), ...
                    BGP_util_Warm_tax(ind_tax,ind_sub,1), BGP_util_Warm(1), ~ ] = ...
                    plots_central( nbins, ind_dam, ind_type, name_adap, ...
                    taxCO2_vect(ind_tax), subclean_vect(ind_sub), ...
                    '', eps, maxCO2, beta_vect(ind_beta), 0 );
                PDV_realgdp_w_Warm_tax(ind_tax,ind_sub,1) = ...
                    sum(pop0_weight.*PDV_realgdp_Warm_tax(:,ind_tax,ind_sub,1));
                PDV_util_w_Warm_tax(ind_tax,ind_sub,1) = ...
                    sum(pop0_weight.*PDV_util_Warm_tax(:,ind_tax,ind_sub,1));
            end
        end
        
        if length_taxCO2 == 1 || length_subclean == 1
            PDV_realgdp_tax_vect(:,ind_beta) = [1; reshape(PDV_realgdp_w_Warm_tax(:,:,1),[],1)];
            PDV_util_tax_vect(:,ind_beta) = [1; reshape(PDV_util_w_Warm_tax(:,:,1),[],1)];
        else
            PDV_realgdp_tax_vect(:,:,ind_beta) = PDV_realgdp_w_Warm_tax(:,:,1);
            PDV_util_tax_vect(:,:,ind_beta) = PDV_util_w_Warm_tax(:,:,1);
        end
    end
    
    % Create tables with BGP and PDV of real GDP and welfare
    if length_taxCO2 > 1
        taxsub_tab = 100*[0 taxCO2_vect]';
        taxsub_cell = cell(length(taxsub_tab),1);
        for y=1:length(taxsub_tab)
            taxsub_cell{y} = ['$\tau$=' num2str(taxsub_tab(y)) '\%'];
        end
    elseif length_subclean > 1
        taxsub_tab = 100*[0 subclean_vect]';
        taxsub_cell = cell(length(taxsub_tab),1);
        for y=1:length(taxsub_tab)
            taxsub_cell{y} = ['$s$=' num2str(taxsub_tab(y)) '\%'];
        end
    end
    
    if length_taxCO2 == 1 || length_subclean == 1
        BGP_realgdp_tab = 100*([BGP_realgdp_Warm(1); reshape(BGP_realgdp_Warm_tax(:,:,1),[],1)]-1);
        BGP_util_tab = 100*([BGP_util_Warm(1); reshape(BGP_util_Warm_tax(:,:,1),[],1)]-1);
        table_tax = table(taxsub_cell,round(BGP_realgdp_tab,3),round(PDV_realgdp_tax_vect,3),round(BGP_util_tab,3),round(PDV_util_tax_vect,3));
        table_tax.Properties.VariableNames = table_prop;
        writetable(table_tax,['Output/table_' name_dam '_' names_taxes '.csv'])
    else
        BGP_tab = 100*([BGP_realgdp_Warm_tax BGP_util_Warm_tax]-1);
        PDV_realgdp_tax_vect(1,1,:) = 1;
        PDV_util_tax_vect(1,1,:) = 1;
        table_PDV_realgdp = table(taxsub_cell(2:end),round(PDV_realgdp_tax_vect(:,:,1),3),round(PDV_realgdp_tax_vect(:,:,2),3));
        table_PDV_util = table(taxsub_cell(2:end),round(PDV_util_tax_vect(:,:,1),3),round(PDV_util_tax_vect(:,:,2),3));
        table_BGP = table(taxsub_cell(2:end),round(BGP_tab,3));
        writetable(table_PDV_realgdp,['Output/table_PDV_realgdp_' name_dam '_' names_taxes '.csv'])
        writetable(table_PDV_util,['Output/table_PDV_util_' name_dam '_' names_taxes '.csv'])
        writetable(table_BGP,['Output/table_BGP_' name_dam '_' names_taxes '.csv'])
    end
    
    if strcmp(names_abat,'') ~= 1
%         names_abat = [names_abat '_all'];
        
        for ind_beta = 1:length(beta_vect)
            for ind_sub = 1:length_subclean
                for ind_tax = 1:length_taxCO2
                    
                    [ ~, ~, realgdp_w_Warm_tax(:,ind_tax,ind_sub,2), util_w_Warm_tax(:,ind_tax,ind_sub,2), ...
                        PDV_realgdp_Warm_tax(:,ind_tax,ind_sub,2), PDV_util_Warm_tax(:,ind_tax,ind_sub,2), ...
                        emiCO2_total_Warm_tax(:,ind_tax,ind_sub,2), emiCO2_total_Warm(:,2), ...
                        clean_total_Warm_tax(:,ind_tax,ind_sub,2), clean_total_Warm(:,2), ...
                        temp_global_Warm_tax(:,ind_tax,ind_sub,2), temp_global_Warm(:,2), ...
                        BGP_realgdp_Warm_tax(ind_tax,ind_sub,2), BGP_realgdp_Warm(2), ...
                        BGP_util_Warm_tax(ind_tax,ind_sub,2), BGP_util_Warm(2), ~ ] = ...
                        plots_central( nbins, ind_dam, ind_type, name_adap, ...
                        taxCO2_vect(ind_tax), subclean_vect(ind_sub), ...
                        names_abat, eps, maxCO2, beta_vect(ind_beta), 0 );
                    PDV_realgdp_w_Warm_tax(ind_tax,ind_sub,2) = ...
                        sum(pop0_weight.*PDV_realgdp_Warm_tax(:,ind_tax,ind_sub,2));
                    PDV_util_w_Warm_tax(ind_tax,ind_sub,2) = ...
                        sum(pop0_weight.*PDV_util_Warm_tax(:,ind_tax,ind_sub,2));
                end
            end
            
            if length_taxCO2 == 1 || length_subclean == 1
                PDV_realgdp_tax_vect(:,ind_beta) = [1; reshape(PDV_realgdp_w_Warm_tax(:,:,2),[],1)];
                PDV_util_tax_vect(:,ind_beta) = [1; reshape(PDV_util_w_Warm_tax(:,:,2),[],1)];
            else
                PDV_realgdp_tax_vect(:,:,ind_beta) = PDV_realgdp_w_Warm_tax(:,:,2);
                PDV_util_tax_vect(:,:,ind_beta) = PDV_util_w_Warm_tax(:,:,2);
            end
        end
        
        % Create tables with BGP and PDV of real GDP and welfare
        if length_taxCO2 == 1 || length_subclean == 1
            BGP_realgdp_tab = 100*([BGP_realgdp_Warm(1); reshape(BGP_realgdp_Warm_tax(:,:,1),[],1)]-1);
            BGP_util_tab = 100*([BGP_util_Warm(1); reshape(BGP_util_Warm_tax(:,:,1),[],1)]-1);
            table_tax = table(taxsub_cell,round(BGP_realgdp_tab,3),round(PDV_realgdp_tax_vect,3),round(BGP_util_tab,3),round(PDV_util_tax_vect,3));
            table_tax.Properties.VariableNames = table_prop;
            writetable(table_tax,['Output/table_' name_dam '_' names_taxes names_abat '.csv'])
        else
            BGP_tab = 100*([BGP_realgdp_Warm_tax BGP_util_Warm_tax]-1);
            table_PDV_realgdp = table(taxsub_cell,round(PDV_realgdp_tax_vect(:,:,1),3),round(PDV_realgdp_tax_vect(:,:,2),3));
            table_PDV_util = table(taxsub_cell,round(PDV_util_tax_vect(:,:,1),3),round(PDV_util_tax_vect(:,:,2),3));
            table_BGP = table(taxsub_cell,round(BGP_tab,3));
            writetable(table_PDV_realgdp,['Output/table_PDV_realgdp_' name_dam '_' names_taxes '.csv'])
            writetable(table_PDV_util,['Output/table_PDV_util_' name_dam '_' names_taxes '.csv'])
            writetable(table_BGP,['Output/table_BGP_' name_dam '_' names_taxes names_abat '.csv'])
        end
        
    end
    
    save(['Data/derived/results_' name_dam '_' names_taxes names_abat '.mat'],...
        'emiCO2_total_Warm', 'emiCO2_total_Warm_tax', ...
        'clean_total_Warm', 'clean_total_Warm_tax', ...
        'temp_global_Warm', 'temp_global_Warm_tax', ...
        'realgdp_w_Warm_tax', 'util_w_Warm_tax', '-v7.3')
    load(['Data/derived/results_' name_dam '_' names_taxes names_abat '.mat'])
    
    if length_taxCO2 == 1 || length_subclean == 1
        plots_taxsub_agg( ind_dam, ...
            emiCO2_total_Warm, emiCO2_total_Warm_tax, ...
            clean_total_Warm, clean_total_Warm_tax, ...
            temp_global_Warm, temp_global_Warm_tax, ...
            realgdp_w_Warm_tax, util_w_Warm_tax, ...
            taxCO2_vect, subclean_vect, names_taxes, names_abat );
    end
    
end

%% 17. Plots time series and maps --different values for eps

% Set plot specifications
T = 400;                % number of periods
nbins = 50;             % number of bins in histogram
ind_dam = 9;            % damage function level: baseline
ind_type = 1;           % damage function source: amenities and productivities
name_adap = '';         % baseline degree of adaptation
taxCO2_val = 0;         % no carbon taxes
subclean_val = 0;       % no clean subsidies
names_taxes = '';
name_abat = '';         % no abatement
taxCO2_val_alt = 2;     % carbon taxes of 200%
subclean_val_alt = 0.75;% clean energy subsidy of 75%
name_abat_alt = '_abat2100_100pp'; % abatement in 2100
maxCO2 = 19500;         % baseline fossil fuel deposit size
name_app = '_eps';
beta_vect = [beta;0.969];   % discount factor
n_beta = length(beta_vect);
name_abat_vect = {name_abat;name_abat_alt};
name_dam = name_dam_vect{ind_dam};

eps_vect = [0.5 1.6 3 6]; 
n_eps = length(eps_vect);
ind_eps_bench = 2; 
eps_cell = cell(n_eps,1);
for y=1:n_eps
    eps_cell{y} = ['$\epsilon$=' num2str(eps_vect(y))];
end

realgdp_w_eps = NaN(T,n_eps,2,n_beta);
util_w_eps = NaN(T,n_eps,2,n_beta);
PDV_realgdp_eps = NaN(n,n_eps,2,n_beta);
PDV_util_eps = NaN(n,n_eps,2,n_beta);
emiCO2_total_eps = NaN(T,n_eps,2,n_beta);
temp_global_eps = NaN(T,n_eps,2,n_beta);
clean_total_eps = NaN(T,n_eps,2,n_beta);
BGP_realgdp_Warm_eps = NaN(n_eps,1,2);
BGP_util_Warm_eps = NaN(n_eps,1,2);
PDV_realgdp_w_Warm_eps = NaN(n_eps,n_beta,2);
PDV_util_w_Warm_eps = NaN(n_eps,n_beta,2);
pop0_weight = pop0_dens.*H/lbar;

% No taxes and subsidies
for ind_eps=1:n_eps
    [ ~, ~, ...
        realgdp_w_eps(:,ind_eps,1,1), util_w_eps(:,ind_eps,1,1), ...
        PDV_realgdp_eps(:,ind_eps,1,1), PDV_util_eps(:,ind_eps,1,1), ...
        emiCO2_total_eps(:,ind_eps,1,1), ~, ...
        clean_total_eps(:,ind_eps,1,1), ~, ...
        temp_global_eps(:,ind_eps,1,1), ~, ...
        ~, ~, ~, ~, ~ ] = ...
        plots_central( nbins, ind_dam, ind_type, name_adap, ...
        taxCO2_val, subclean_val, name_abat, ...
        eps_vect(ind_eps), maxCO2, beta_vect(1), 0 );
end

save('Data/derived/results_eps.mat',...
    'realgdp_w_eps', 'util_w_eps', 'PDV_realgdp_eps', 'PDV_util_eps', ...
    'emiCO2_total_eps', 'temp_global_eps', 'clean_total_eps', '-v7.3')
load('Data/derived/results_eps.mat')

plots_append_agg( ind_dam, ...
    taxCO2_val, subclean_val, names_taxes, name_abat, ... 
    name_app, eps_vect, ind_eps_bench, ...
    realgdp_w_eps, util_w_eps, ...
    PDV_realgdp_eps, PDV_util_eps, ...
    emiCO2_total_eps, temp_global_eps, ...
    clean_total_eps );

% Taxes of 200%
names_taxes = '_tax200p_sub0p';
for ind_abat = 1:2
    name_abat_aux = name_abat_vect{ind_abat};
    
    for ind_beta = 1:length(beta_vect)
        for ind_eps=1:n_eps
            [ ~, ~, ...
                realgdp_w_eps(:,ind_eps,ind_abat,ind_beta), util_w_eps(:,ind_eps,ind_abat,ind_beta), ...
                PDV_realgdp_eps(:,ind_eps,ind_abat,ind_beta), PDV_util_eps(:,ind_eps,ind_abat,ind_beta), ...
                emiCO2_total_eps(:,ind_eps,ind_abat,ind_beta), ~, ...
                clean_total_eps(:,ind_eps,ind_abat,ind_beta), ~, ...
                temp_global_eps(:,ind_eps,ind_abat,ind_beta), ~, ...
                BGP_realgdp_Warm_eps(ind_eps,1,ind_abat), ~, ...
                BGP_util_Warm_eps(ind_eps,1,ind_abat), ~, ~ ] = ...
                plots_central( nbins, ind_dam, ind_type, name_adap, ...
                taxCO2_val_alt, subclean_val, name_abat_aux, ...
                eps_vect(ind_eps), maxCO2, beta_vect(ind_beta), 0 );
            PDV_realgdp_w_Warm_eps(ind_eps,ind_beta,ind_abat) = ...
                sum(pop0_weight.*PDV_realgdp_eps(:,ind_eps,ind_abat,ind_beta));
            PDV_util_w_Warm_eps(ind_eps,ind_beta,ind_abat) = ...
                sum(pop0_weight.*PDV_util_eps(:,ind_eps,ind_abat,ind_beta));
        end
    end
end

table_tax = table(eps_cell,round(100*(BGP_realgdp_Warm_eps(:,1,1)-1),3),round(PDV_realgdp_w_Warm_eps(:,:,1),3),round(100*(BGP_util_Warm_eps(:,1,1)-1),3),round(PDV_util_w_Warm_eps(:,:,1),3));
table_tax.Properties.VariableNames = table_prop;
table_abat = table(eps_cell,round(100*(BGP_realgdp_Warm_eps(:,1,2)-1),3),round(PDV_realgdp_w_Warm_eps(:,:,2),3),round(100*(BGP_util_Warm_eps(:,1,2)-1),3),round(PDV_util_w_Warm_eps(:,:,2),3));
table_abat.Properties.VariableNames = table_prop;
writetable(table_tax,['Output/table_eps_' name_dam '_tax200p_sub0p.csv'])
writetable(table_abat,['Output/table_eps_' name_dam '_tax200p_sub0p_abat2100_100pp.csv'])

save('Data/derived/results_tax200_eps.mat',...
    'realgdp_w_eps', 'util_w_eps', 'PDV_realgdp_eps', 'PDV_util_eps', ...
    'emiCO2_total_eps', 'temp_global_eps', 'clean_total_eps', ...
    'table_tax', 'table_abat', '-v7.3')
load('Data/derived/results_tax200_eps.mat')

plots_append_agg( ind_dam, ...
    taxCO2_val_alt, subclean_val, names_taxes, name_abat_alt, ... 
    name_app, eps_vect, ind_eps_bench, ...
    realgdp_w_eps, util_w_eps, ...
    PDV_realgdp_eps, PDV_util_eps, ...
    emiCO2_total_eps, temp_global_eps, ...
    clean_total_eps );

% Subsidies of 75%
names_taxes = '_tax0p_sub75p';
for ind_beta = 1:length(beta_vect)
    for ind_eps=1:n_eps
        [ ~, ~, ...
            realgdp_w_eps(:,ind_eps,1,ind_beta), util_w_eps(:,ind_eps,1,ind_beta), ...
            PDV_realgdp_eps(:,ind_eps,1,ind_beta), PDV_util_eps(:,ind_eps,1,ind_beta), ...
            emiCO2_total_eps(:,ind_eps,1,ind_beta), ~, ...
            clean_total_eps(:,ind_eps,1,ind_beta), ~, ...
            temp_global_eps(:,ind_eps,1,ind_beta), ~, ...
            BGP_realgdp_Warm_eps(ind_eps,1,1), ~, ...
            BGP_util_Warm_eps(ind_eps,1,1), ~, ~ ] = ...
            plots_central( nbins, ind_dam, ind_type, name_adap, ...
            taxCO2_val, subclean_val_alt, name_abat, ...
            eps_vect(ind_eps), maxCO2, beta_vect(ind_beta), 0 );
        PDV_realgdp_w_Warm_eps(ind_eps,ind_beta,1) = ...
            sum(pop0_weight.*PDV_realgdp_eps(:,ind_eps,1,ind_beta));
        PDV_util_w_Warm_eps(ind_eps,ind_beta,1) = ...
            sum(pop0_weight.*PDV_util_eps(:,ind_eps,1,ind_beta));
    end
end

table_tax = table(eps_cell,round(100*(BGP_realgdp_Warm_eps(:,1,1)-1),3),round(PDV_realgdp_w_Warm_eps(:,:,1),3),round(100*(BGP_util_Warm_eps(:,1,1)-1),3),round(PDV_util_w_Warm_eps(:,:,1),3));
table_tax.Properties.VariableNames = table_prop;
writetable(table_tax,['Output/table_eps_' name_dam '_tax0p_sub75p.csv'])

save('Data/derived/results_sub75_eps.mat',...
    'realgdp_w_eps', 'util_w_eps', 'PDV_realgdp_eps', 'PDV_util_eps', ...
    'emiCO2_total_eps', 'temp_global_eps', 'clean_total_eps', 'table_tax', '-v7.3')
load('Data/derived/results_sub75_eps.mat')

plots_append_agg( ind_dam, ...
    taxCO2_val, subclean_val_alt, names_taxes, name_abat, ... 
    name_app, eps_vect, ind_eps_bench, ...
    realgdp_w_eps, util_w_eps, ...
    PDV_realgdp_eps, PDV_util_eps, ...
    emiCO2_total_eps, temp_global_eps, ...
    clean_total_eps );

%% 18. Plots time series and maps --different values for maxCO2 

% Set plot specifications
T = 400;                % number of periods
nbins = 50;             % number of bins in histogram
ind_dam = 9;            % damage function level: baseline
ind_type = 1;           % damage function source: amenities and productivities
name_adap = '';         % baseline degree of adaptation
taxCO2_val = 0;         % no carbon taxes
subclean_val = 0;       % no clean subsidies
names_taxes = '';
name_abat = '';         % no abatement
taxCO2_val_alt = 2;     % carbon taxes of 200%
subclean_val_alt = 0.75;% clean energy subsidy of 75%
name_abat_alt = '_abat2100_100pp'; % abatement in 2100
eps = 1.6;              % baseline elasticity of substitution
name_app = '_maxCO2';
beta_vect = [beta;0.969];   % discount factor
n_beta = length(beta_vect);
name_abat_vect = {name_abat;name_abat_alt};
name_dam = name_dam_vect{ind_dam};

maxCO2_vect = [7900 19500 45300]; 
n_maxCO2 = length(maxCO2_vect);
ind_maxCO2_bench = 2; 
maxCO2_cell = cell(n_maxCO2,1);
for y=1:n_maxCO2
    maxCO2_cell{y} = ['$maxCumCO2$=' num2str(maxCO2_vect(y)) ' GtCO$_2$'];
end

realgdp_w_maxCO2 = NaN(T,n_maxCO2,2,n_beta);
util_w_maxCO2 = NaN(T,n_maxCO2,2,n_beta);
PDV_realgdp_maxCO2 = NaN(n,n_maxCO2,2,n_beta);
PDV_util_maxCO2 = NaN(n,n_maxCO2,2,n_beta);
emiCO2_total_maxCO2 = NaN(T,n_maxCO2,2,n_beta);
temp_global_maxCO2 = NaN(T,n_maxCO2,2,n_beta);
clean_total_maxCO2 = NaN(T,n_maxCO2,2,n_beta);
BGP_realgdp_Warm_maxCO2 = NaN(n_maxCO2,1,2);
BGP_util_Warm_maxCO2 = NaN(n_maxCO2,1,2);
PDV_realgdp_w_Warm_maxCO2 = NaN(n_maxCO2,n_beta,2);
PDV_util_w_Warm_maxCO2 = NaN(n_maxCO2,n_beta,2);
pop0_weight = pop0_dens.*H/lbar;

% No taxes and subsidies
for ind_maxCO2=1:n_maxCO2
    [ ~, ~, ...
        realgdp_w_maxCO2(:,ind_maxCO2,1,1), util_w_maxCO2(:,ind_maxCO2,1,1), ...
        PDV_realgdp_maxCO2(:,ind_maxCO2,1,1), PDV_util_maxCO2(:,ind_maxCO2,1,1), ...
        emiCO2_total_maxCO2(:,ind_maxCO2,1,1), ~, ...
        clean_total_maxCO2(:,ind_maxCO2,1,1), ~, ...
        temp_global_maxCO2(:,ind_maxCO2,1,1), ~, ...
        ~, ~, ~, ~, ~ ] = ...
        plots_central( nbins, ind_dam, ind_type, name_adap, ...
        taxCO2_val, subclean_val, name_abat, ...
        eps, maxCO2_vect(ind_maxCO2), beta_vect(1), 0 );
end

save('Data/derived/results_maxCO2.mat',...
    'realgdp_w_maxCO2', 'util_w_maxCO2', 'PDV_realgdp_maxCO2', 'PDV_util_maxCO2', ...
    'emiCO2_total_maxCO2', 'temp_global_maxCO2', 'clean_total_maxCO2', '-v7.3')
load('Data/derived/results_maxCO2.mat')

plots_append_agg( ind_dam, ...
    taxCO2_val, subclean_val, names_taxes, name_abat, ... 
    name_app, maxCO2_vect, ind_maxCO2_bench, ...
    realgdp_w_maxCO2, util_w_maxCO2, ...
    PDV_realgdp_maxCO2, PDV_util_maxCO2, ...
    emiCO2_total_maxCO2, temp_global_maxCO2, ...
    clean_total_maxCO2 );

% Taxes of 200%
names_taxes = '_tax200p_sub0p';
for ind_abat = 1:2
    name_abat_aux = name_abat_vect{ind_abat};
    
    for ind_beta = 1:length(beta_vect)
        for ind_maxCO2=1:n_maxCO2
            [ ~, ~, ...
                realgdp_w_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), util_w_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), ...
                PDV_realgdp_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), PDV_util_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), ...
                emiCO2_total_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), ~, ...
                clean_total_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), ~, ...
                temp_global_maxCO2(:,ind_maxCO2,ind_abat,ind_beta), ~, ...
                BGP_realgdp_Warm_maxCO2(ind_maxCO2,1,ind_abat), ~, ...
                BGP_util_Warm_maxCO2(ind_maxCO2,1,ind_abat), ~, ~ ] = ...
                plots_central( nbins, ind_dam, ind_type, name_adap, ...
                taxCO2_val_alt, subclean_val, name_abat_aux, ...
                eps, maxCO2_vect(ind_maxCO2), beta_vect(ind_beta), 0 );
            PDV_realgdp_w_Warm_maxCO2(ind_maxCO2,ind_beta,ind_abat) = ...
                sum(pop0_weight.*PDV_realgdp_maxCO2(:,ind_maxCO2,ind_abat,ind_beta));
            PDV_util_w_Warm_maxCO2(ind_maxCO2,ind_beta,ind_abat) = ...
                sum(pop0_weight.*PDV_util_maxCO2(:,ind_maxCO2,ind_abat,ind_beta));
        end
    end
end

table_tax = table(maxCO2_cell,round(100*(BGP_realgdp_Warm_maxCO2(:,1,1)-1),3),round(PDV_realgdp_w_Warm_maxCO2(:,:,1),3),round(100*(BGP_util_Warm_maxCO2(:,1,1)-1),3),round(PDV_util_w_Warm_maxCO2(:,:,1),3));
table_tax.Properties.VariableNames = table_prop;
table_abat = table(maxCO2_cell,round(100*(BGP_realgdp_Warm_maxCO2(:,1,2)-1),3),round(PDV_realgdp_w_Warm_maxCO2(:,:,2),3),round(100*(BGP_util_Warm_maxCO2(:,1,2)-1),3),round(PDV_util_w_Warm_maxCO2(:,:,2),3));
table_abat.Properties.VariableNames = table_prop;
writetable(table_tax,['Output/table_maxCO2_' name_dam '_tax200p_sub0p.csv'])
writetable(table_abat,['Output/table_maxCO2_' name_dam '_tax200p_sub0p_abat2100_100pp.csv'])

save('Data/derived/results_tax200_maxCO2.mat',...
    'realgdp_w_maxCO2', 'util_w_maxCO2', 'PDV_realgdp_maxCO2', 'PDV_util_maxCO2', ...
    'emiCO2_total_maxCO2', 'temp_global_maxCO2', 'clean_total_maxCO2', ...
    'table_tax', 'table_abat', '-v7.3')
load('Data/derived/results_tax200_maxCO2.mat')

plots_append_agg( ind_dam, ...
    taxCO2_val_alt, subclean_val, names_taxes, name_abat_alt, ... 
    name_app, maxCO2_vect, ind_maxCO2_bench, ...
    realgdp_w_maxCO2, util_w_maxCO2, ...
    PDV_realgdp_maxCO2, PDV_util_maxCO2, ...
    emiCO2_total_maxCO2, temp_global_maxCO2, ...
    clean_total_maxCO2 );

% Subsidies of 75%
names_taxes = '_tax0p_sub75p';
for ind_beta = 1:length(beta_vect)
    for ind_maxCO2=1:n_maxCO2
        [ ~, ~, ...
            realgdp_w_maxCO2(:,ind_maxCO2,1,ind_beta), util_w_maxCO2(:,ind_maxCO2,1,ind_beta), ...
            PDV_realgdp_maxCO2(:,ind_maxCO2,1,ind_beta), PDV_util_maxCO2(:,ind_maxCO2,1,ind_beta), ...
            emiCO2_total_maxCO2(:,ind_maxCO2,1,ind_beta), ~, ...
            clean_total_maxCO2(:,ind_maxCO2,1,ind_beta), ~, ...
            temp_global_maxCO2(:,ind_maxCO2,1,ind_beta), ~, ...
            BGP_realgdp_Warm_maxCO2(ind_maxCO2,1,1), ~, ...
            BGP_util_Warm_maxCO2(ind_maxCO2,1,1), ~, ~ ] = ...
            plots_central( nbins, ind_dam, ind_type, name_adap, ...
            taxCO2_val, subclean_val_alt, name_abat, ...
            eps, maxCO2_vect(ind_maxCO2), beta_vect(ind_beta), 0 );
        PDV_realgdp_w_Warm_maxCO2(ind_maxCO2,ind_beta,1) = ...
            sum(pop0_weight.*PDV_realgdp_maxCO2(:,ind_maxCO2,1,ind_beta));
        PDV_util_w_Warm_maxCO2(ind_maxCO2,ind_beta,1) = ...
            sum(pop0_weight.*PDV_util_maxCO2(:,ind_maxCO2,1,ind_beta));
    end
end

table_tax = table(maxCO2_cell,round(100*(BGP_realgdp_Warm_maxCO2(:,1,1)-1),3),round(PDV_realgdp_w_Warm_maxCO2(:,:,1),3),round(100*(BGP_util_Warm_maxCO2(:,1,1)-1),3),round(PDV_util_w_Warm_maxCO2(:,:,1),3));
table_tax.Properties.VariableNames = table_prop;
writetable(table_tax,['Output/table_maxCO2_' name_dam '_tax0p_sub75p.csv'])

save('Data/derived/results_sub75_maxCO2.mat',...
    'realgdp_w_maxCO2', 'util_w_maxCO2', 'PDV_realgdp_maxCO2', 'PDV_util_maxCO2', ...
    'emiCO2_total_maxCO2', 'temp_global_maxCO2', 'clean_total_maxCO2', 'table_tax', '-v7.3')
load('Data/derived/results_sub75_maxCO2.mat')

plots_append_agg( ind_dam, ...
    taxCO2_val, subclean_val_alt, names_taxes, name_abat, ... 
    name_app, maxCO2_vect, ind_maxCO2_bench, ...
    realgdp_w_maxCO2, util_w_maxCO2, ...
    PDV_realgdp_maxCO2, PDV_util_maxCO2, ...
    emiCO2_total_maxCO2, temp_global_maxCO2, ...
    clean_total_maxCO2 );
