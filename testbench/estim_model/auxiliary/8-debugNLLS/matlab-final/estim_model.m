
function [] = estim_model( coeff_pop_i,upsilon_fossil_i,upsilon_clean_i,...
    ind_dam,update_vect,tol_vect )

% Function that estimates the parameters of the natality rate function,
% the migration cost function and the elasticities of energy productivity
% growth to global real income growth.
% Inputs:
%   coeff_pop_i: guess for coefficients on the natality rate function.
%   upsilon_fossil_i: guess for the elasticity of fossil fuel
%   productivity growth to global real GDP growth.
%   upsilon_clean_i: guess for the elasticity of clean energy
%   productivity growth to global real GDP growth.
%   ind_dam: level of the damage function, 9 is the benchmark.
%   update_vect: speed of parameters’ update.
%   tol_vect: tolerance of errors in the iteration.
global datafolder
global H H0 a_norm prod0 pop5_dens n theta ...
    eta gamma2 gamma1 nu ksi mu scaler_temp...
    theta_amen_scen theta_prod_scen pop5 lbar...
    emi_ff_data_tend...
    C_vect length_C_vect...
    clean_energy_data fossil_share epsilon tCO2_toe price_energy0 ...
    temp0_local_long temp0_local Delta_temp1 temp_past Delta_temp...
    natal_data country_data year_data pop_data name_dam_vect amen_util0

%% 1. Load data and arrange net births data

% Numerical parameters
T_back = 50;       % number of periods to run backward the model
T = 20;            % number of periods to run forward the model
update_m2 = update_vect(1);
update_upsilon_fossil = update_vect(2);
update_upsilon_clean = update_vect(3);
name_dam = name_dam_vect{ind_dam};

% Set tolerance of errors
tol_clean = tol_vect(1);
tol_fossil = tol_vect(2);
tol_m2 = tol_vect(3);
tol_l = tol_vect(4);
tol_nlls = tol_vect(5);
tol_final_SSR = tol_vect(6);
tol_m2_inner = tol_vect(7);
tol_step = tol_vect(8);

% Set numerical parameters for the estimation of the natality function
size_deriv = 1e-5;
scal_nlls = 1e-5;
lev_nlls = 1e-3;
count_max = 50;

% Load guess for migration costs
data_m2 = load([datafolder,'/derived/m2.mat']);
m2_i = data_m2.m2;
save([datafolder '/derived/natal_migr_Warm_' name_dam '.mat'],...
    'coeff_pop_i','m2_i','upsilon_fossil_i','upsilon_clean_i','-v7.3')

% Update variables of period 0
[ l0_model,~,~,realgdp0_model ] = model_initial_period(m2_i);

% Store results for period 20
l20 = (1.01^20)*l0_model;
realgdp20 = (1.02^20)*realgdp0_model;
temp20 = temp0_local + 0.7*scaler_temp;
save([datafolder '/derived/results20_' name_dam '.mat'],...
    'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3')

% weight_fossil = linspace(0.5,2,T_back)';
% weight_clean = linspace(0.5,2,T_back-15)';

% Arrange data
length_ISO = length(year_data)/(2000-1950+1);
pop_data_resh = reshape(pop_data,[2000-1950+1 length_ISO]);
pop_tot_data = repmat(sum(pop_data_resh,2),length_ISO,1);
weight_pop_data = pop_data./pop_tot_data;
weight_pop_matrix = diag(weight_pop_data).*diag(kron(linspace(1,1,(2000-1950+1))',ones(length_ISO,1)));
% weight_pop_matrix = weight_pop_matrix/sum(weight_pop_matrix,'all');
% isdiag(weight_pop_matrix): YES it is

% ******** DEVELOP: THIS IS NOT USED
%%{
natal_data0 = natal_data(year_data == 2000);
natal_data0_cell = NaN(n,1);
for i=1:length(unique(C_vect))
    natal_data0_cell(C_vect==i) = natal_data0(i);
end
%%}

error_clean = 1 + tol_clean;
while error_clean > tol_clean

    error_fossil = 1 + tol_fossil;
    while error_fossil > tol_fossil

        error_m2 = 1 + tol_m2;
        while error_m2 > tol_m2

            error_l = 1 + tol_l;
            while error_l > tol_l

                %% 2. Run model backwards, given m_2 and coeff_pop

                % Run model backwards
                display([newline 'Run model backwards' newline])
                [ l_b,~,~,realgdp_b,~,emiCO2_b,temp_b,~,clean_b,~,~ ] = ...
                    backward_climate( T_back,1,ind_dam );
                
                % Store utility and realgdp
                l = [fliplr(l_b(:,1:50)) l0_model];
                realgdp = [fliplr(realgdp_b(:,1:50)) realgdp0_model];
                temp = [fliplr(temp_b(:,1:50)) temp0_local]; % from 1950 to 2000

                %% 3. Perform NLLS on natality function

                % Construct net births at country level
                logrealgdp_c = zeros(length_C_vect,T_back+1);
                temp_c = zeros(length_C_vect,T_back+1);
                logrealgdp_w = zeros(length_C_vect,T_back+1);   % ******** DEVELOP: MISTAKE HERE: world gdp only function of time
                for t=1:T_back+1
                    logrealgdp_c(:,t) = log(accumarray(C_vect,H.*l(:,t).*realgdp(:,t))./accumarray(C_vect,H.*l(:,t)));
                    temp_c(:,t) = accumarray(C_vect,H.*l(:,t).*temp(:,t))./accumarray(C_vect,H.*l(:,t));
                    logrealgdp_w(t) = log(sum(H.*l(:,t).*realgdp(:,t))/sum(H.*l(:,t)));                         % ******** DEVELOP: MISTAKE HERE
                end

                % Set numerical parameters
                SSR_f = 1 + tol_final_SSR;
                length_coeff_pop = length(coeff_pop_i);
                error_nlls = 1 + tol_nlls;
                count = 1;

                display([newline 'Update natality function' newline])
                iter_NLLS = 0;
                while error_nlls > tol_nlls && SSR_f > tol_final_SSR && count < count_max

                    % Construct derivative
                    deriv_i = zeros(length_C_vect*(2000-1950+1),length_coeff_pop);

                    for c=1:length_coeff_pop

                        % Construct coeff_pop_p and coeff_pop_m
                        coeff_pop_p = coeff_pop_i;
                        coeff_pop_p(c) = coeff_pop_p(c) + size_deriv;
                        coeff_pop_m = coeff_pop_i;
                        coeff_pop_m(c) = coeff_pop_m(c) - size_deriv;

                        % Construct net births at country level
                        natal_model_aux_Cvect_p = zeros(length_C_vect,2000-1950+1); % from 1950 to 2000
                        natal_model_aux_Cvect_m = zeros(length_C_vect,2000-1950+1); % from 1950 to 2000
                        for t=1:T_back+1
                            natal_model_aux_Cvect_p(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_p);
                            natal_model_aux_Cvect_m(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_m);
                        end

                        % Sort them according to ISO_code
                        natal_model_p = reshape(natal_model_aux_Cvect_p',[],1);
                        natal_model_m = reshape(natal_model_aux_Cvect_m',[],1);

                        deriv_i(:,c) = (natal_model_p - natal_model_m)/(2*size_deriv);
                    end

                    % Construct net births at country level
                    natal_model_aux_Cvect_i = zeros(length_C_vect,2000-1950+1); % from 1950 to 2000
                    for t=1:T_back+1
                        natal_model_aux_Cvect_i(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_i);
                    end

                    % Sort them according to ISO_code
                    natal_model_i = reshape(natal_model_aux_Cvect_i',[],1);

                    % Construct error and SSR
                    error_i = natal_data - natal_model_i;
                    SSR_i = error_i'*weight_pop_matrix*error_i;

                    % Regress errors on natal_model_i
                    rcond_ind = rcond(deriv_i'*weight_pop_matrix*deriv_i);
                    if rcond_ind < 1e-25
                        coeff_reg = pinv(deriv_i'*weight_pop_matrix*deriv_i)*...
                            (deriv_i'*weight_pop_matrix*error_i);
                    else
                        coeff_reg = (deriv_i'*weight_pop_matrix*deriv_i)\...
                            (deriv_i'*weight_pop_matrix*error_i);
                    end

                    % Set step
                    step = (1/2)^0;

                    while SSR_f > SSR_i && step > (1/2)^tol_step

                        % Compute candidate for new coefficient
                        coeff_pop_f = coeff_pop_i + step*coeff_reg;

                        % Construct net births at country level
                        natal_model_aux_Cvect_i = zeros(length_C_vect,2000-1950+1); % from 1950 to 2000
                        natal_model_aux_Cvect_f = zeros(length_C_vect,2000-1950+1); % from 1950 to 2000
                        for t=1:T_back+1
                            natal_model_aux_Cvect_i(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_i);
                            natal_model_aux_Cvect_f(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_f);
                        end

                        % Sort them according to ISO_code
                        natal_model_i = reshape(natal_model_aux_Cvect_i',[],1);
                        natal_model_f = reshape(natal_model_aux_Cvect_f',[],1);

                        % Construct errors and SSR
                        error_i = natal_data - natal_model_i;
                        error_f = natal_data - natal_model_f;
                        SSR_i = error_i'*weight_pop_matrix*error_i;
                        SSR_f = error_f'*weight_pop_matrix*error_f;

                        %display(['SSR_f = ' num2str(SSR_f)  '; SSR_i = ' num2str(SSR_i) '; step = ' num2str(step)])
                        iter_NLLS = iter_NLLS+1;
                        display(['count = ',num2str(iter_NLLS),' SSR_f = ' num2str(SSR_f)  '; SSR_i = ' num2str(SSR_i) '; step = ' num2str(step)])
                        step = step/2;
                        if step == (1/2)^tol_step
                            coeff_pop_f = coeff_pop_i;
                            count = count_max;
                        end

                    end

                    % Compute error_nlls
                    aux_error_nlls = step*abs(coeff_pop_f) - scal_nlls*(abs(coeff_pop_i) + lev_nlls);
                    error_nlls = sum(aux_error_nlls > 0);

                    % Update estimates
                    coeff_pop_i = coeff_pop_f;
                    SSR_f = SSR_i + 1;
                    count = count + 1;

                end

                realgdp0_w_model = sum(realgdp0_model.*l0_model.*H)/lbar;
                net_births0 = natal_fct(log(realgdp0_model),temp0_local,log(realgdp0_w_model),coeff_pop_i);

                % Aggregate natality rates at country level
                natal_model0_country_short = accumarray(C_vect,H.*l0_model.*net_births0)./accumarray(C_vect,H.*l0_model);
                natal_model0_country = NaN(n,1);
                for i=1:length(unique(C_vect))
                    natal_model0_country(C_vect==i) = natal_model0_country_short(i);
                end

                %% 4. Run model forward to update l20, given natality parameters

                % Run model forward
                display([newline 'Run model forward' newline])
                [ l, ~, prod, realgdp, amen, ~, ~, ~, ~, ...
                    temp_local, price_emi, ~, price_clean, ~ ] = ...
                    forward_climate( T, 1, ind_dam, 0, ...
                    zeros(n,T), zeros(n,T), zeros(n,T), ones(3,1) );

                % Compute error_l
                error_l = sqrt(sum((l20 - l(:,20)).^2));
                display(['error_l = ' num2str(error_l)])

                % Store results for period 20
                l20 = l(:,20);
                realgdp20 = realgdp(:,20);
                temp20 = temp_local(:,20);
                save([datafolder '/derived/results20_' name_dam '.mat'],...
                    'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3')

            end

            %% 5. Update migration costs

            % Update migration costs
            display([newline 'Update migration costs' newline])
            price_energy = (fossil_share^epsilon*price_emi.^(1-epsilon) + ...
                (1-fossil_share)^epsilon*price_clean.^(1-epsilon)).^(1/(1-epsilon));
            [m2_f] = migration_costs(m2_i,amen(:,5),prod(:,5),pop5_dens,...
                price_energy(:,5),tol_m2_inner);

            % Compute error_m2
            error_m2 = sqrt(sum((m2_i - m2_f).^2));
            display(['error_m2 = ' num2str(error_m2)])
            m2_i = update_m2*m2_f + (1-update_m2)*m2_i;
            m2_i = m2_i/min(m2_i);
            save([datafolder '/derived/natal_migr_Warm_' name_dam '.mat'],...
                'coeff_pop_i','m2_i','upsilon_fossil_i','upsilon_clean_i','-v7.3')

            % Update variables of period 0
            [ l0_model,~,~,realgdp0_model ] = model_initial_period(m2_i);

            % ********************** DEVELOP: MISTAKE?
            % 
            %            model_initial_period initializes l0_model/realgdp0_model but they are not used in forward climate
            % 
            save([datafolder '/derived/results20_' name_dam '.mat'],'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3');           % DEVELOP: created by ALE
            % ********************** DEVELOP: MISTAKE?

            % Update variables of period 20
            display([newline 'Run model forward' newline ])
            [ l, ~, prod, realgdp, amen, ~, ~, ~, ~, ...
                temp_local, price_emi, ~, price_clean, ~ ] = ...
                forward_climate( T, 1, ind_dam, 0, ...
                zeros(n,T), zeros(n,T), zeros(n,T), ones(3,1) );

            % Store results for period 20
            l20 = l(:,20);
            realgdp20 = realgdp(:,20);
            temp20 = temp_local(:,20);
            save([datafolder '/derived/results20_' name_dam '.mat'],...
                'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3')

        end

        %% 6. Update upsilon fossil

        % Compute error_upsilon fossil
        emi_ff_model = fliplr(sum(emiCO2_b.*repmat(H,1,T_back)))';
        error_fossil = sqrt(mean((emi_ff_model - emi_ff_data_tend).^2));
        % error_fossil = sqrt(mean(weight_fossil.*(emi_ff_model - emi_ff_data_tend).^2));

        slope_fossil_model = (emi_ff_model(1)-emi_ff_model(end))/length(emi_ff_model);
        slope_fossil_tend = (emi_ff_data_tend(1)-emi_ff_data_tend(end))/length(emi_ff_data_tend);

        upsilon_fossil_i = (update_upsilon_fossil + (1-update_upsilon_fossil)*slope_fossil_tend/slope_fossil_model)*upsilon_fossil_i;
        % upsilon_fossil_i = (update_upsilon_fossil + (1-update_upsilon_fossil)*sum(emi_ff_model)/sum(emi_ff_data_tend))*upsilon_fossil_i;
        % upsilon_fossil_i = (update_upsilon_fossil + (1-update_upsilon_fossil)*sum(weight_fossil.*emi_ff_model)/sum(weight_fossil.*emi_ff_data_tend))*upsilon_fossil_i;

        display(['error_fossil = ' num2str(error_fossil) '; upsilon_fossil = ' num2str(upsilon_fossil_i)])
        save([datafolder '/derived/natal_migr_Warm_' name_dam '.mat'],...
            'coeff_pop_i','m2_i','upsilon_fossil_i','upsilon_clean_i','-v7.3')

        % Update variables of period 20
        display([newline 'Run model forward' newline])
        [ l, ~, prod, realgdp, amen, ~, ~, ~, ~, ...
            temp_local, price_emi, ~, price_clean, ~ ] = ...
            forward_climate( T, 1, ind_dam, 0, ...
            zeros(n,T), zeros(n,T), zeros(n,T), ones(3,1) );

        % Store results for period 20
        l20 = l(:,20);
        realgdp20 = realgdp(:,20);
        temp20 = temp_local(:,20);
        save([datafolder '/derived/results20_' name_dam '.mat'],...
            'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3')

        % Update migration costs
        display([newline 'Update migration costs' newline])
        price_energy = (fossil_share^epsilon*price_emi.^(1-epsilon) + ...
            (1-fossil_share)^epsilon*price_clean.^(1-epsilon)).^(1/(1-epsilon));
        [m2_i] = migration_costs(m2_i,amen(:,5),prod(:,5),pop5_dens,...
            price_energy(:,5),tol_m2_inner);
        save([datafolder '/derived/natal_migr_Warm_' name_dam '.mat'],...
            'coeff_pop_i','m2_i','upsilon_fossil_i','upsilon_clean_i','-v7.3')

    end

    %% 7. Update upsilon clean

    % Compute error_upsilon clean
    clean_model = fliplr(sum(clean_b(:,16:end).*repmat(H,1,T_back-15)))';
    error_clean = sqrt(mean((clean_model - tCO2_toe*clean_energy_data).^2));
    % error_clean = sqrt(mean(weight_clean.*(clean_model - tCO2_toe*clean_energy_data).^2));

    slope_clean_model = (clean_model(1)-clean_model(end))/length(clean_model);
    slope_clean_tend = (tCO2_toe*clean_energy_data(1)-tCO2_toe*clean_energy_data(end))/length(clean_energy_data);

    upsilon_clean_i = (update_upsilon_clean + (1-update_upsilon_clean)*slope_clean_tend/slope_clean_model)*upsilon_clean_i;
    % upsilon_clean_i = (update_upsilon_clean + (1-update_upsilon_clean)*sum(clean_model)/sum(tCO2_toe*clean_energy_data))*upsilon_clean_i;
    % upsilon_clean_i = (update_upsilon_clean + (1-update_upsilon_clean)*sum(weight_clean.*clean_model)/sum(weight_clean.*tCO2_toe.*clean_energy_data))*upsilon_clean_i;

    display(['error_clean = ' num2str(error_clean) '; upsilon_clean = ' num2str(upsilon_clean_i)])
    save([datafolder '/derived/natal_migr_Warm_' name_dam '.mat'],...
        'coeff_pop_i','m2_i','upsilon_fossil_i','upsilon_clean_i','-v7.3')

    % Update variables of period 20
    display([newline 'Run model forward' newline])
    [ l, ~, prod, realgdp, amen, ~, ~, ~, ~, ...
        temp_local, price_emi, ~, price_clean, ~ ] = ...
        forward_climate( T, 1, ind_dam, 0, ...
        zeros(n,T), zeros(n,T), zeros(n,T), ones(3,1) );

    % Store results for period 20
    l20 = l(:,20);
    realgdp20 = realgdp(:,20);
    temp20 = temp_local(:,20);
    save([datafolder '/derived/results20_' name_dam '.mat'],...
        'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3')

    % Update migration costs
    display([newline 'Update migration costs' newline])
    price_energy = (fossil_share^epsilon*price_emi.^(1-epsilon) + ...
        (1-fossil_share)^epsilon*price_clean.^(1-epsilon)).^(1/(1-epsilon));
    [m2_i] = migration_costs(m2_i,amen(:,5),prod(:,5),pop5_dens,...
        price_energy(:,5),tol_m2_inner);
    save([datafolder '/derived/natal_migr_Warm_' name_dam '.mat'],...
        'coeff_pop_i','m2_i','upsilon_fossil_i','upsilon_clean_i','-v7.3')

end

end
