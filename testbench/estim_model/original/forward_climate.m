
function [ l, u, prod, realgdp, amen, ...
    emiCO2_ff, emiCO2_total, stockCO2, temp_global, temp_local, ...
    price_fossil, clean, price_clean, net_births ] = ...
    forward_climate( T, ind_clim, ind_dam, ind_exog, ...
    taxCO2, subclean, abat, val_adap )

% Function that simulates the world economy forward in time,
% as described in Supplementary Materials Section F.1
% Inputs:
%   T: number of periods for which the economy will be simulated
%   ind_clim: source of damages, so that a value of 0 indicates no damages, 
%   1 damages on bothamenities and productivities, 2 damages only on amenities, 
%   and 3 damages only on productivity
%   ind_dam: level of the damage function, 9 denotes the baseline estimate
%   ind_exog: dummy variable so that a value of 0 indicates endogenous 
%   CO2emissions, temperature and population and a value of 1 takes the 
%   exogenous values from the baseline scenario
%   taxCO2: path of proportional carbon taxes
%   subclean: path of proportional clean energy subsidies
%   abat: share of CO2 emissions abated
%   val_adap: vector of size 3×1 controlling the cost of trade, 
%   migration and innovation
% Outputs:
%   l, u, prod, realgdp, amen, emiCO2_ff, emiCO2_total, stockCO2, 
%   temp_global, temp_local, price_fossil, clean, price_clean, net_births: 
%   cell-level population, utility, productivity, real GDP, amenities, 
%   CO2 emissions from fossil fuel combustion, global CO2 emissions, 
%   global CO2 stock, global temperature, cell-level temperature, 
%   fossil fuel price, clean energy use, clean energy price and 
%   net births for T periods

global H a_norm prod0 n lbar lambda gamma2 eta mu ksi...
     alpha theta Omega trmult_reduced gamma1 nu...
     emi0_ff emi_no_ff emi0 chi cost_emi_param...
     a0 a1 a2 a3 b1 b2 b3 S0 S1 S2 S3 S_preind...
     forc_sens forc_noCO2 c1 c2 d1 d2 temp1 temp2...
     temp0_global temp0_local scaler_temp...
     theta_amen_scen theta_prod_scen name_dam_vect... 
     price_clean0_world zeta_clean0 zeta_fossil0 fossil_share epsilon

%% 1. Initialize output variables

l = zeros(n,T);
u = zeros(n,T);
prod = zeros(n,T);
phi = zeros(n,T);
realgdp = zeros(n,T);
realincome = zeros(n,T);
realgdp_w = zeros(T,1);
price_fossil = zeros(n,T);
price_clean = zeros(n,T);
price_energy = zeros(n,T);
price_energy_tilde = zeros(n,T);
varphi = zeros(n,T);
zeta_fossil = zeros(n,T);
zeta_clean = zeros(n,T);
clean = zeros(n,T);
cumCO2_ff = zeros(T,1);
emiCO2_ff_abat = zeros(n,T);
emiCO2_total = zeros(T,1);
stockCO2_layers = zeros(4,T);
forc = zeros(T,1);
temp_layers = zeros(2,T);
temp_local = zeros(n,T);
amen = zeros(n,T);
net_births = zeros(n,T);

if ind_exog == 0    % endogenous CO2 emissions, temperature and population
    emiCO2_ff = zeros(n,T);
    temp_global = zeros(T,1);
    lbar_time = zeros(T+1,1);
else                % exogenous CO2 emissions, temperature and population
    if ind_clim == 1
        data_Warm = load(['Data/derived/results_forward_Warm_' name_dam_vect{ind_dam} '.mat']);
        emiCO2_ff = data_Warm.emiCO2_ff_Warm;
        temp_global = data_Warm.temp_global_Warm;
        lbar_time = sum((data_Warm.l_Warm).*repmat(H,1,T),1);
    else
        data_noWarm = load(['Data/derived/results_forward_noWarm.mat']);
        emiCO2_ff = data_noWarm.emiCO2_ff_noWarm;
        temp_global = data_noWarm.temp_global_noWarm;
        lbar_time = sum((data_noWarm.l_noWarm).*repmat(H,1,T),1);
    end
end

%% 2. Initialize parameters and variables of initital period

% Read parameters
data_natal = load('Data/derived/natal_migr_Warm_med.mat');
m2 = data_natal.m2_i;
coeff_pop = data_natal.coeff_pop_i;
upsilon_fossil = data_natal.upsilon_fossil_i;
upsilon_clean = data_natal.upsilon_clean_i;

data_20 = load('Data/derived/results20_med.mat');
l0_model = data_20.l0_model;
realgdp0 = data_20.realgdp0_model;
realgdp0_w = sum(realgdp0.*l0_model.*H)/lbar;

% Update adaptation parameters
trmult_reduced_aux = trmult_reduced.^val_adap(1);
m2_aux = m2.^val_adap(2);
gamma1_aux = gamma1*val_adap(3);

% Update productivity and amenities
avgprod = mean(prod0);
const_phi = ((gamma1_aux/ksi)/(nu*(mu+gamma1_aux/ksi)))^(1/ksi);
const_energy = (1-chi)*mu/(mu+gamma1_aux/ksi);

phi0 = const_phi * l0_model.^(1/ksi);
prod(:,1) = eta * prod0.^gamma2 .* avgprod.^(1-gamma2) .* phi0.^(gamma1_aux*theta);
amen(:,1) = a_norm;

% Set CO2 stock, forcing and temperature
if ind_exog == 0
    stockCO2_layers(1,1) = S0 + a0*emi0;
    stockCO2_layers(2,1) = (exp(-1/b1))*S1 + a1*emi0;
    stockCO2_layers(3,1) = (exp(-1/b2))*S2 + a2*emi0;
    stockCO2_layers(4,1) = (exp(-1/b3))*S3 + a3*emi0;

    forc(1) = forc_sens*log(sum(stockCO2_layers(:,1))/S_preind)/log(2) + forc_noCO2(1);

    temp_layers(1,1) = (exp(-1/d1))*temp1 + (c1/d1)*forc(1);
    temp_layers(2,1) = (exp(-1/d2))*temp2 + (c2/d2)*forc(1);

    temp_global(1) = sum(temp_layers(:,1));
end
temp_local(:,1) = temp0_local + scaler_temp.*(temp_global(1)-temp0_global);
temp_local_aux = temp_local(:,1); 
Delta_temp = temp_local(:,1) - temp0_local;

% Set damage function level by confidence interval
if ind_clim ~= 0 
    theta_amen_min = theta_amen_scen(1,ind_dam);
    theta_amen_max = theta_amen_scen(2,ind_dam);
    theta_amen_center = theta_amen_scen(3,ind_dam);
    theta_amen_steep = theta_amen_scen(4,ind_dam);
    theta_amen_temp =@(temp) theta_amen_min + ...
        (theta_amen_max - theta_amen_min)./...
        (1+exp(theta_amen_steep*(temp - theta_amen_center)));
    
    theta_prod_min = theta_prod_scen(1,ind_dam);
    theta_prod_max = theta_prod_scen(2,ind_dam);
    theta_prod_center = theta_prod_scen(3,ind_dam);
    theta_prod_steep = theta_prod_scen(4,ind_dam);
	theta_prod_temp =@(temp) theta_prod_min + ...
        (theta_prod_max - theta_prod_min)./...
        (1+exp(theta_prod_steep*(temp - theta_prod_center)));
end

% Set damage function sources: amenities or productivities
if ind_clim == 1 % damages on both amenities and productivities
    amen(:,1) = (1+theta_amen_temp(temp_local_aux).*Delta_temp).*amen(:,1);
    prod(:,1) = (1+theta_prod_temp(temp_local_aux).*Delta_temp).*prod(:,1); 
elseif ind_clim == 2 % damages only on amenities
    amen(:,1) = (1+theta_amen_temp(temp_local_aux).*Delta_temp).*amen(:,1);
elseif ind_clim == 3 % damages only on productivities
    prod(:,1) = (1+theta_prod_temp(temp_local_aux).*Delta_temp).*prod(:,1); 
end

% Update population size 
if ind_exog == 0
    net_births0 = natal_fct(log(realgdp0),temp0_local,...
        log(realgdp0_w),coeff_pop); 
    pop_prev = H.*l0_model.*(1+net_births0);
    lbar_time(1) = round(sum(pop_prev));
end

% Define function for extraction cost function
costCO2_fct =@(cumCO2) ...
    cost_emi_param(1)./(cost_emi_param(2) + ...
    exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
    cost_emi_param(5)*(cost_emi_param(6)./(cumCO2-cost_emi_param(6))).^cost_emi_param(7);

% Precompute auxiliary variables
denom = 1+2*theta;
squ = (alpha-1+(lambda+gamma1_aux/ksi-(1-mu))*theta); % term in square brackets of flat_R and flat_L

flatL = lambda - squ/denom;
flatR = 1 - lambda*theta+(1+theta)*squ/denom;
flat = flatR - theta*flatL;

exp_uhatL = flatL/Omega + (1+theta)/denom;
exp_uhatR = flatR/Omega - theta^2/denom;

% Precompute auxiliary variables to equation (75)
FL_H_m2 = H.^((flatL-1/denom)/exp_uhatL) .* ...
    m2_aux.^(flatL/(Omega*exp_uhatL)); % outside the integral
FR_H_m2 = H.^(-flatR+theta/denom) .*...
    m2_aux.^(-flatR/Omega); % inside the integral

% Set guesses
uhat_i = ones(n,1); % guess for uhat
if ind_exog == 0
    emi_ff_i = emi0_ff; % guess for global CO2 emissions
end
realgdp_growth_i = 1.017; % guess for global realgdp growth

% Set numerical parameters
updatee = 1; % speed of update when iterating over CO2 emissions
updater = 1;

tol = 1e-2;   % tolerance for error when iterating over uhat
tol_e = 1e-2; % tolerance for error when iterating over CO2 emissions
tol_realgdp = 1e-2;

%% 3. Simulate the model

for t = 1:T
    
    % Compute previous period's energy productivity, global real GDP
    % and cummulative CO2 emissions
    if t==1
        zeta_fossil_prev = zeta_fossil0;
        zeta_clean_prev = zeta_clean0;
        realgdp_w_prev = realgdp0_w; 
        cumCO2_ff(t) = emi0_ff;
    else
        zeta_fossil_prev = zeta_fossil(:,t-1);
        zeta_clean_prev = zeta_clean(:,t-1);
        realgdp_w_prev = realgdp_w(t-1);
        cumCO2_ff_aux = cumCO2_ff(t-1) + sum(emiCO2_ff(:,t-1).*H);
        ind_cumCO2 = (cumCO2_ff_aux>=cost_emi_param(6)-0.5); 
        if ind_cumCO2 == 1 % avoid cumCO2_ff to be larger than maxCO2
            cumCO2_ff_aux = cost_emi_param(6)-0.5; 
        end
        cumCO2_ff(t) = cumCO2_ff_aux;
    end
    
    % Compute extraction cost
    costCO2_avg_i = costCO2_fct(cumCO2_ff(t));
    
    % Pre-compute auxiliary variables to equation (75)
    FL_aux = amen(:,t).^((1+theta)/(denom*exp_uhatL)) .* ...
        prod(:,t).^(1/(denom*exp_uhatL)) .* ...
        FL_H_m2; % outside the integral

    FR_aux = amen(:,t).^(theta^2/denom) .* ...
        prod(:,t).^((1+theta)/denom) .* ...
        FR_H_m2; % inside the integral

	error_realgdp = 1 + tol_realgdp;
    while error_realgdp > tol_realgdp
        
    % Update energy productivity, equation (10)
    zeta_fossil(:,t) = zeta_fossil_prev*(realgdp_growth_i)^(upsilon_fossil);
    zeta_clean(:,t) = zeta_clean_prev*(realgdp_growth_i)^(upsilon_clean);
        
    error_e = 1 + tol_e;
    while error_e > tol_e
        
    % Construct energy price, equations (44) and (46)
    price_fossil(:,t) = costCO2_avg_i./zeta_fossil(:,t);
    price_clean(:,t) = price_clean0_world./zeta_clean(:,t);
    price_energy(:,t) = ...
        (fossil_share^epsilon*(1+taxCO2(:,t)).^(1-epsilon).*price_fossil(:,t).^(1-epsilon) + ...
        (1-fossil_share)^epsilon*(1-subclean(:,t)).^(1-epsilon).*price_clean(:,t).^(1-epsilon)).^(1/(1-epsilon));
    price_energy_tilde(:,t) = ...
        (fossil_share^epsilon*(1+taxCO2(:,t)).^(-epsilon).*price_fossil(:,t).^(1-epsilon) + ...
        (1-fossil_share)^epsilon*(1-subclean(:,t)).^(-epsilon).*price_clean(:,t).^(1-epsilon)).^(1/(1-epsilon));
    varphi(:,t) = (mu*chi + gamma1_aux/ksi + mu*(1-chi)*(price_energy_tilde(:,t)./price_energy(:,t)).^(1-epsilon))/...
        (mu+gamma1_aux/ksi);
    
    % Precompute auxiliary variables to equation (75)
    FL = FL_aux .* ...
        price_energy(:,t).^(-theta*mu*(1-chi)/(denom*exp_uhatL)) .* ...
        varphi(:,t).^(theta*(mu+gamma1_aux/ksi)/(denom*exp_uhatL)); % outside the integral

    FR = FR_aux .* ...
        price_energy(:,t).^(-theta*(1+theta)*mu*(1-chi)/denom) .* ...
        varphi(:,t).^(theta*(1+theta)*(mu+gamma1_aux/ksi)/denom); % inside the integral

    % Iterate uhat, equation (75)
    error = tol + 1;
    while error >= tol
        integral = FR .* uhat_i.^exp_uhatR;
        rhs = trmult_reduced_aux*integral;
        uhat_f = FL .* rhs.^(1/(theta*exp_uhatL));
        error = sum((uhat_i - uhat_f).^2);
        uhat_i = uhat_f;
%         display(['t = ' num2str(t) '; error = ' num2str(error)])
    end
    
    % Solve for population, equation (3), and scale it to add up to lbar_time(t)
    l(:,t) = H.^(-1) .* uhat_i.^(1/Omega) .* m2_aux.^(-1/Omega);
    l(:,t) = l(:,t) / sum(H.*l(:,t)) * lbar_time(t);
    
	% Calculate innovation, equations (49) and (51)
    phi(:,t) = const_phi * (l(:,t)./varphi(:,t)).^(1/ksi);
    
    % Retrieve utility, equation (76)
    u(:,t) = uhat_i * ...
        (lbar_time(t)/sum(uhat_i.^(1/Omega).*m2_aux.^(-1/Omega)))^(flat/theta);
    
    % Calculate real income and real GDP per capita, equation (4) 
    realincome(:,t) = u(:,t) ./ amen(:,t) .* l(:,t).^lambda;
    realgdp(:,t) = (1 + (mu+gamma1_aux/ksi)*(varphi(:,t)-1)).*realincome(:,t);
    realgdp_w(t) = sum(realgdp(:,t).*H.*l(:,t))/sum(H.*l(:,t));

    % Update productivity, equation (6)
    if t < T
        avgprod = mean(prod(:,t));
        prod(:,t+1) = eta * prod(:,t).^gamma2 .* avgprod.^(1-gamma2) .* phi(:,t).^(gamma1_aux*theta);
    end
    
    % Calculate clean energy use, equation (53)
    clean(:,t) = const_energy*(1./varphi(:,t)).*(l(:,t)./price_energy(:,t)).*...
    	((1-fossil_share)*price_energy(:,t)./((1-subclean(:,t)).*price_clean(:,t))).^epsilon;

    % Calculate CO2 emissions, equation (52)
    if ind_exog == 0
    emiCO2_ff(:,t) = const_energy*(1./varphi(:,t)).*(l(:,t)./price_energy(:,t)).*...
        (fossil_share*price_energy(:,t)./((1+taxCO2(:,t)).*price_fossil(:,t))).^epsilon;   
    end
    
    % Update CO2 emissions by abatement 
    emiCO2_ff_abat(:,t) = (1-abat(:,t)).*emiCO2_ff(:,t);
    emi_ff_f = sum(emiCO2_ff(:,t).*H);
    emi_ff_f_abat = sum(emiCO2_ff_abat(:,t).*H);
    emiCO2_total(t) = emi_ff_f_abat + emi_no_ff(t);

	% Compare global CO2 emissions
    if ind_exog == 0
        error_e = abs(emi_ff_f - emi_ff_i);
        emi_ff_i = updatee*emi_ff_f + (1-updatee)*emi_ff_i;
        costCO2_avg_i = mean(costCO2_fct(cumCO2_ff(t) + linspace(0,emi_ff_i,1e2)));
    else
        error_e = 0;
    end
    display(['t = ' num2str(t) '; error_realgdp = ' num2str(error_realgdp) '; error_e = ' num2str(error_e)])

    end
    
    % Compare growth rate realgdp
    realgdp_growth_f = realgdp_w(t)/realgdp_w_prev;
    error_realgdp = abs(realgdp_growth_f-realgdp_growth_i);
    realgdp_growth_i = updater*realgdp_growth_f + (1-updater)*realgdp_growth_i;
    
    end
    
	% Set growth rate of previous period
    realgdp_growth_i = realgdp_growth_f;

    if t<T
        % Update CO2 stock, forcing and temperature, equations (15), (17), (37)-(41)
        if ind_exog == 0
        stockCO2_layers(1,t+1) = stockCO2_layers(1,t) + a0*emiCO2_total(t);
        stockCO2_layers(2,t+1) = (exp(-1/b1))*stockCO2_layers(2,t) + a1*emiCO2_total(t);
        stockCO2_layers(3,t+1) = (exp(-1/b2))*stockCO2_layers(3,t) + a2*emiCO2_total(t);
        stockCO2_layers(4,t+1) = (exp(-1/b3))*stockCO2_layers(4,t) + a3*emiCO2_total(t);
        
        forc(t+1) = forc_sens*log(sum(stockCO2_layers(:,t+1))/S_preind)/log(2) + forc_noCO2(t+1);
        
        temp_layers(1,t+1) = (exp(-1/d1))*temp_layers(1,t) + (c1/d1)*forc(t+1);
        temp_layers(2,t+1) = (exp(-1/d2))*temp_layers(2,t) + (c2/d2)*forc(t+1);

        temp_global(t+1) = sum(temp_layers(:,t+1));
        end
        temp_local(:,t+1) = temp0_local + scaler_temp.*(temp_global(t+1)-temp0_global);
        
        % Update local temperature
        if ind_clim ~= 0
            temp_local_aux = temp_local(:,t+1);
            Delta_temp = temp_local(:,t+1) - temp_local(:,t);
        end
        
        % Update damages on amenities and productivities, equations (2) and (6)
        if ind_clim == 1 % damages on both amenities and productivities
            amen(:,t+1) = (1+theta_amen_temp(temp_local_aux).*Delta_temp).*amen(:,t);
            prod(:,t+1) = (1+theta_prod_temp(temp_local_aux).*Delta_temp).*prod(:,t+1); 
        elseif ind_clim == 2 % damages only on amenities
            amen(:,t+1) = (1+theta_amen_temp(temp_local_aux).*Delta_temp).*amen(:,t);
        elseif ind_clim == 3 % damages only on productivities
            prod(:,t+1) = (1+theta_prod_temp(temp_local_aux).*Delta_temp).*prod(:,t+1); 
            amen(:,t+1) = amen(:,t);
        elseif ind_clim == 0 % no damages
            amen(:,t+1) = amen(:,t);
        end

        % Update global population
        if ind_exog == 0
            net_births(:,t) = natal_fct(log(realgdp(:,t)),temp_local_aux,log(realgdp_w(t)),coeff_pop); 
            pop_prev = (1+net_births(:,t)).*l(:,t).*H;
            lbar_time(t+1) = round(sum(pop_prev));
        end
        
    end
        
end

% Sum CO2 stock layers, equation (37)
stockCO2 = sum(stockCO2_layers)';

end
