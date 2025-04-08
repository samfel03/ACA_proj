
function [ l, u, prod, realgdp, amen, emiCO2_ff, temp_past_out, ...
    price_fossil, clean, price_clean, net_births ] = ...
    backward_climate( T, ind_clim, ind_dam )

% Function that simulates the world economy backward in time,
% as described in Supplementary Materials Section F.4
% Inputs:
%   T: number of periods for which the economy will be simulated
%   ind_clim: source of damages, so that a value of 0 indicates no damages,
%   1 damages on bothamenities and productivities, 2 damages only on amenities,
%   and 3 damages only on productivity
%   ind_dam: level of the damage function, so that 9 denotes the baseline estimate
% Output:
%   l, u, prod, realgdp, amen, emiCO2_ff, temp_past_out, price_fossil,
%   clean, price_clean, net_births: cell-level population, utility,
%   productivity, real GDP, amenities, CO2 emissions from fossil fuel
%   combustion, temperature, fossil fuel price, clean energy use,
%   clean energy price and net births for T periods
global datafolder
global H prod0 trmult_reduced n alpha theta a_norm ...
    Omega chi lambda ksi mu gamma1 gamma2 lbar nu ...
    theta_amen_scen theta_prod_scen ...
    emi0_ff cost_emi_param ...
    price_clean0_world zeta_clean0 zeta_fossil0 fossil_share ...
    epsilon natal0 temp_past Delta_temp

%% 1. Initialize output variables

l = zeros(n,T);
u = zeros(n,T);
phi = zeros(n,T);
prod = zeros(n,T);
realgdp = zeros(n,T);
amen = zeros(n,T);
emiCO2_ff = zeros(n,T);
clean = zeros(n,T);
net_births = zeros(n,T);
lbar_time = zeros(T,1);
realgdp_w = zeros(T,1);
zeta_fossil = zeros(n,T);
zeta_clean = zeros(n,T);
cumCO2 = zeros(T,1);
price_fossil = zeros(n,T);
price_clean = zeros(n,T);
price_energy = zeros(n,T);

%% 2. Initialize parameters and variables of initital period

% Read parameters
data_natal = load([datafolder,'/derived/natal_migr_Warm_med.mat']);
m2 = data_natal.m2_i;
coeff_pop = data_natal.coeff_pop_i;
upsilon_fossil = data_natal.upsilon_fossil_i;
upsilon_clean = data_natal.upsilon_clean_i;

data_20 = load([datafolder,'/derived/results20_med.mat']);
l0_model = data_20.l0_model;
realgdp0 = data_20.realgdp0_model;
realgdp0_w = sum(realgdp0.*l0_model.*H)/lbar;

% Set damages on amenities and productivities
temp_past_out = temp_past;                                  % ******** DEVELOP: NOT USED
theta_amen_temp = zeros(n,T);
theta_prod_temp = zeros(n,T);

if ind_clim == 1
    theta_amen_min = theta_amen_scen(1,ind_dam);
    theta_amen_max = theta_amen_scen(2,ind_dam);
    theta_amen_center = theta_amen_scen(3,ind_dam);
    theta_amen_steep = theta_amen_scen(4,ind_dam);

    theta_prod_min = theta_prod_scen(1,ind_dam);
    theta_prod_max = theta_prod_scen(2,ind_dam);
    theta_prod_center = theta_prod_scen(3,ind_dam);
    theta_prod_steep = theta_prod_scen(4,ind_dam);
    for t=1:T
        theta_amen_temp(:,t) = theta_amen_min + ...
            (theta_amen_max - theta_amen_min)./...
            (1+exp(theta_amen_steep*(temp_past(:,t) - theta_amen_center)));
        theta_prod_temp(:,t) = theta_prod_min + ...
            (theta_prod_max - theta_prod_min)./...
            (1+exp(theta_prod_steep*(temp_past(:,t) - theta_prod_center)));
    end
end

% Define function for cost of CO2 emissions
costCO2_fct =@(cumCO2) ...
    cost_emi_param(1)./(cost_emi_param(2) + exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
    cost_emi_param(5)*(cost_emi_param(6)./(cumCO2-cost_emi_param(6))).^cost_emi_param(7);

% Precompute auxiliary variables
const_phi = ((gamma1/ksi)/(nu*(mu+gamma1/ksi)))^(1/ksi);
const_energy = (1-chi)*mu/(mu+gamma1/ksi);

denom = 1+2*theta;
squ_b = (alpha-1+(lambda+gamma1/ksi-(1-mu)-gamma1/(ksi*gamma2))*theta); % term in square brackets of natural_R and natural_L

naturalL = lambda - squ_b/denom;
naturalR = 1 - lambda*theta+(1+theta)*squ_b/denom;
natural = naturalR - theta*naturalL;

exp_uhatL = naturalL/Omega + (1+theta)/denom;
exp_uhatR = naturalR/Omega - theta^2/denom;

% Precompute auxiliary variables to equation (88)
BL_H_m2 = H.^((naturalL-1/denom)/exp_uhatL) .* ...
    m2.^(naturalL/(Omega*exp_uhatL)); % outside the integral
BR_H_m2 = H.^(-naturalR+theta/denom) .*...
    m2.^(-naturalR/Omega); % inside the integral

% Set guesses
uhat_i = ones(n,1); % guess for uhat
ltilde = round(lbar/(1+natal0)); % guess for global population
lbar1 = lbar;
emi_ff_i = emi0_ff; % guess for global CO2 emissions
realgdp_growth_i = 1.017; % guess for global realgdp growth

% Set numerical parameters
updatel = 1; % speed of update when iterating over l
updatee = 1;
updater = 1;

tol = 1e-2;   % tolerance for error when iterating over uhat
tol_l = 1e+1; % tolerance for error when iterating over l
tol_e = 1e-3;
tol_realgdp = 1e-2;

%% 3. Simulate the model backwards

for t = 1:T

    % Compute previous period's energy productivity, global real GDP
    % and cummulative CO2 emissions
    if t==1
        prod_next = prod0./(1+theta_prod_temp(:,t).*Delta_temp(:,t));
        amen(:,t) = a_norm./(1+theta_amen_temp(:,t).*Delta_temp(:,t));
        zeta_fossil_next = zeta_fossil0;
        zeta_clean_next = zeta_clean0;
        realgdp_w_next = realgdp0_w;
        cumCO2_next = 0;
    else
        prod_next = prod(:,t-1)./(1+theta_prod_temp(:,t).*Delta_temp(:,t));
        amen(:,t) = amen(:,t-1)./(1+theta_amen_temp(:,t).*Delta_temp(:,t));
        zeta_fossil_next = zeta_fossil(:,t-1);
        zeta_clean_next = zeta_clean(:,t-1);
        realgdp_w_next = realgdp_w(t-1);
        cumCO2_next = cumCO2(t-1);
    end

    % Compute extraction cost
    costCO2_avg_i = costCO2_fct(cumCO2_next);

    % Precompute auxiliary variables to equation (88)
    BL_aux = amen(:,t).^((1+theta)/(denom*exp_uhatL)) .* ...
        prod_next.^(1/(gamma2*denom*exp_uhatL)) .* ...
        BL_H_m2; % outside the integral

    BR_aux = amen(:,t).^(theta^2/denom) .* ...
        prod_next.^((1+theta)/(gamma2*denom)) .* ...
        BR_H_m2; % inside the integral

    error_realgdp = 1 + tol_realgdp;
    while error_realgdp > tol_realgdp

        % Update energy productivity, equation (9)
        zeta_fossil(:,t) = zeta_fossil_next*(realgdp_growth_i)^(-upsilon_fossil);
        zeta_clean(:,t) = zeta_clean_next*(realgdp_growth_i)^(-upsilon_clean);

        error_e = 1 + tol_e;
        while error_e > tol_e

            % Construct energy price, equations (44) and (46)
            price_fossil(:,t) = costCO2_avg_i./zeta_fossil(:,t);
            price_clean(:,t) = price_clean0_world./zeta_clean(:,t);
            price_energy(:,t) = (fossil_share^epsilon*price_fossil(:,t).^(1-epsilon) + ...
                (1-fossil_share)^epsilon*price_clean(:,t).^(1-epsilon)).^(1/(1-epsilon));

            % Pre-compute auxiliary variables to equation (88)
            BL = BL_aux .* ...
                price_energy(:,t).^(-theta*mu*(1-chi)/(denom*exp_uhatL)); % outside the integral
            BR = BR_aux .* ...
                price_energy(:,t).^(-theta*(1+theta)*mu*(1-chi)/denom); % inside the integral

            % Iterate uhat, equation (88)
            error = tol + 1;
            %{
            while error >= tol
                integral = BR .* uhat_i.^exp_uhatR;
                rhs = trmult_reduced*integral;
                uhat_f = BL .* rhs.^(1/(theta*exp_uhatL));
                error = sum((uhat_i - uhat_f).^2);
                uhat_i = uhat_f;
                %display(['t = ' num2str(-t) '; error_realgdp = ' num2str(error_realgdp) '; error_e = ' num2str(error_e) '; error_uhat = ' num2str(error)])
            end
            %}
            uhat_i = (0:n-1)' + 700000;

            error_l = tol_l + 1;
            while error_l > tol_l

                % Solve for population, equation (3), and scale it to add up to ltilde
                % DEVELOP: PREALLOCATED SINCE IT DOES NOT DEPEND ON THE NEXT LOOP IF NOT FOR LTILDE (we can divide by old and multiply by new each time
                l(:,t) = H.^(-1) .* uhat_i.^(1/Omega) .* m2.^(-1/Omega);
                l(:,t) = l(:,t) / sum(H.*l(:,t)) * ltilde;

                % Calculate innovation, equations (49) and (51)
                phi(:,t) = const_phi * l(:,t).^(1/ksi);

                % Back out productivity
                prod(:,t) = phi(:,t).^(-theta*gamma1/gamma2) .* prod_next.^(1/gamma2);
                avgprod = mean(prod(:,t));
                prod(:,t) = avgprod^(gamma2-1) * prod(:,t);

                % Retrieve utility, equation (90)                               % ******** DEVELOP: check mean(prod): could be a typo
                u(:,t) = uhat_i * const_phi^(-gamma1/gamma2) * ...
                    mean(prod(:,t))^((gamma2-1)/(gamma2*theta)) * ...
                    (ltilde/sum(uhat_i.^(1/Omega).*m2.^(-1/Omega)))^(natural/theta);

                % Calculate real GDP per capita, equation (4)
                realgdp(:,t) = u(:,t) ./ amen(:,t) .* l(:,t).^lambda;
                realgdp_w(t) = sum(realgdp(:,t).*H.*l(:,t))/ltilde;

                % Calculate energy use, equations (52) and (53)                 ******** DEVELOP: MOVE TO NEXT LOOP SINCE THEY ARE NOT NECESSARY TO UPDATE LTILDE
                emiCO2_ff(:,t) = const_energy*(l(:,t)./price_energy(:,t)).*...
                    (fossil_share*price_energy(:,t)./price_fossil(:,t)).^epsilon;
                clean(:,t) = const_energy*(l(:,t)./price_energy(:,t)).*...
                    ((1-fossil_share)*price_energy(:,t)./price_clean(:,t)).^epsilon;

                % Update global population
                net_births(:,t) = natal_fct( log(realgdp(:,t)),temp_past(:,t),log(realgdp_w(t)),...
                    coeff_pop );
                ltilde1 = ltilde + sum(net_births(:,t).*l(:,t).*H);

                % Compare global populations
                error_l = abs(lbar1 - ltilde1);
                ltilde = round((updatel*lbar1/ltilde1+(1-updatel))*ltilde);
                display(['t = -' num2str(t) '; error_realgdp = ' num2str(error_realgdp) '; error_e = ' num2str(error_e) '; error_l = ' num2str(error_l) ])
            end

            % Compare global emiCO2
        	emi_ff_f = sum(emiCO2_ff(:,t).*H);
            error_e = abs(emi_ff_f - emi_ff_i);
            emi_ff_i = updatee*emi_ff_f + (1-updatee)*emi_ff_i;
        	cumCO2(t) = cumCO2_next - emi_ff_f;
            costCO2_avg_i = mean(costCO2_fct(cumCO2_next - linspace(0,emi_ff_i,1e2)));

        end

        % Compare growth rate realgdp
        realgdp_growth_f = realgdp_w_next/realgdp_w(t);
        error_realgdp = abs(realgdp_growth_f-realgdp_growth_i);
        realgdp_growth_i = updater*realgdp_growth_f + (1-updater)*realgdp_growth_i;

    end

    % Update lbar1
    lbar_time(t) = ltilde;
    lbar1 = ltilde;

end

end
