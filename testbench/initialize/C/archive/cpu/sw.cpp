#include "sw.h"

extern "C"
{

	/**
	 * Update variables of period 0
	 * Function that estimates population, real GDP and utility of the initial period, consistent with the initial distribution
	 *  of amenities, productivities and migration costs
	 * Input:
	 * m2: migration cost function
	 // Output:
	 //   l0, u0, uhat0, realgdp0: solution for population, utility,
	  //   transformed utility and real GDP
	 */
	void model_initial_period(real *m2, real *l0_model, real *realgdp0_model)
	{
		// **** initalized in init_model_initial_period ****/
		// Precompute auxiliary variables to equation (75)
		FL_H_m2 = env->FL_H_m2_left.*m2.^ (env->FL_H_m2_left_exp);	 // outside the integral
		FR_H_m2 = env->FL_H_m2_right.*m2.^ (env->FL_H_m2_right_exp); // inside the integral

		FL = env->a_norm.^ (env->FL_left_exp).*env->prod0.^ (env->FL_prod0_exp).*env->price_energy0.^ (env->FL_price_energy0_exp).*FL_H_m2;	  // outside the integral
		FR = env->a_norm.^ (env->FR_a_norm_exp).*env->prod0.^ (env->FR_prod0_exp).*env->price_energy0.^ (env->FR_price_energy0_exp).*FR_H_m2; // inside the integral

		// Iterate uhat, equation (75)
		uhat_i = ones(n, 1); // guess on utility function
		error = TOLL_MODEL_INITIAL_PERIOD + 1;
		while (error >= TOLL_MODEL_INITIAL_PERIOD)
		{
			integral = FR.*uhat_i.^ exp_uhatR;
			rhs = trmult_reduced * integral;
			uhat_f = FL.*rhs.^ (env->uhat_f_exp);
			error = sum((uhat_i - uhat_f).^ 2);
			uhat_i = uhat_f;
		}

		// Retrieve utility and real GDP, equations (76) and (4)
		uhat0 = uhat_f;
		l0 = H.^ (-1).*uhat0.^ (1 / Omega).*m2.^ (-1 / Omega);
		l0 = l0 * lbar / sum(H.*l0);
		u0 = uhat_i * ...(lbar / sum(uhat0.^ (1 / Omega).*m2.^ (-1 / Omega))) ^ (flat / theta);
		realgdp0 = (u0./ a_norm).*l0.^ lambda;
	}
	void store_results_period20()
	{
		// Store results for period 20
		l20 = l(
			:, 20);
		realgdp20 = realgdp(
			:, 20);
		temp20 = temp_local(
			:, 20);
		save(['Data/derived/results20_' name_dam '.mat'], ... 'l0_model', 'realgdp0_model', 'l20', 'realgdp20', 'temp20', '-v7.3')
	}

	// Define function for cost of CO2 emissions
	void costC02_fun(real *cost_emi_param,real *cumCO2, real * costCO2_fct){

			costCO2_fct= cost_emi_param(1)./(cost_emi_param(2) + exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
    		cost_emi_param(5)*(cost_emi_param(6)./(cumCO2-cost_emi_param(6))).^cost_emi_param(7);

	}

	// Function that simulates the world economy backward in time,
	// as described in Supplementary Materials Section F.4
	// Inputs:
	//   T_BACK: number of periods for which the economy will be simulated
	//   ind_clim: source of damages, so that a value of 0 indicates no damages,
	//   1 damages on bothamenities and productivities, 2 damages only on amenities,
	//   and 3 damages only on productivity
	//   ind_dam: level of the damage function, so that 9 denotes the baseline estimate
	// Output:
	//   l, u, prod, realgdp, amen, emiCO2_ff, temp_past_out, price_fossil,
	//   clean, price_clean, net_births: cell-level population, utility,
	//   productivity, real GDP, amenities, CO2 emissions from fossil fuel
	//   combustion, temperature, fossil fuel price, clean energy use,
	//   clean energy price and net births for T_BACK periods
	*void backward_climate(env_t *env)
	{
		//// 1. Initialize output variables
		l = zeros(n, T_BACK);
		u = zeros(n, T_BACK);
		phi = zeros(n, T_BACK);
		prod = zeros(n, T_BACK);
		realgdp = zeros(n, T_BACK);
		amen = zeros(n, T_BACK);
		emiCO2_ff = zeros(n, T_BACK);
		clean = zeros(n, T_BACK);
		net_births = zeros(n, T_BACK);
		lbar_time = zeros(T_BACK, 1);
		realgdp_w = zeros(T_BACK, 1);
		zeta_fossil = zeros(n, T_BACK);
		zeta_clean = zeros(n, T_BACK);
		cumCO2 = zeros(T_BACK, 1);
		price_fossil = zeros(n, T_BACK);
		price_clean = zeros(n, T_BACK);
		price_energy = zeros(n, T_BACK);

		//// 2. Initialize parameters and variables of initital period
		// Read parameters
		data_natal = load('Data/derived/natal_migr_Warm_med.mat');
		m2 = data_natal.m2_i;
		coeff_pop = data_natal.coeff_pop_i;
		upsilon_fossil = data_natal.upsilon_fossil_i;
		upsilon_clean = data_natal.upsilon_clean_i;

		data_20 = load('Data/derived/results20_med.mat');
		l0_model = data_20.l0_model;
		realgdp0 = data_20.realgdp0_model;
		realgdp0_w = sum(realgdp0.*l0_model.*H) / lbar;

		// Set damages on amenities and productivities
		temp_past_out = temp_past;
		theta_amen_temp = zeros(n, T_BACK);
		theta_prod_temp = zeros(n, T_BACK);

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
		
		// Precompute auxiliary variables to equation (88)
		real exp_uhatL=env->BW_exp_uhatL;
		real exp_uhatR=env->BW_exp_uhatR;
		real denom = env->aux_denom;
		real BL_H_m2 = env->BL_H_m2_left .* m2.^(env->BL_H_m2_left_exp); // outside the integral
		real BR_H_m2 = env->BR_H_m2_right .*m2.^(env->BR_H_m2_right_exp); // inside the integral

		for(int t=0;t<T_BACK;t++){
			// Compute previous period's energy productivity, global real GDP
			// and cummulative CO2 emissions
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

			// Compute extraction cost
			real costCO2_avg_i;
			costC02_fun(env->cost_emi_param,env->cumCO2,&costCO2_avg_i)
    		
			 // Precompute auxiliary variables to equation (88)
			real BL_aux = amen(:,t).^((1+theta)/(denom*exp_uhatL)) .* ...
				prod_next.^(1/(gamma2*denom*exp_uhatL)) .* ...
				BL_H_m2; // outside the integral
		
			real BR_aux = amen(:,t).^(theta^2/denom) .* ...
				prod_next.^((1+theta)/(gamma2*denom)) .* ...
				BR_H_m2; // inside the integral

			real error_realgdp = 1. + BW_tol_realgdp;
    		while(error_realgdp > BW_tol_realgdp){


				// Update energy productivity, equation (9)
			    zeta_fossil(:,t) = zeta_fossil_next*(realgdp_growth_i)^(-upsilon_fossil);
    			zeta_clean(:,t) = zeta_clean_next*(realgdp_growth_i)^(-upsilon_clean);

				real error_e= 1. + BW_tol_e;
				while(error_e > BW_tol_e){


					// Construct energy price, equations (44) and (46)
					price_fossil(:,t) = costCO2_avg_i./zeta_fossil(:,t);
					price_clean(:,t) = price_clean0_world./zeta_clean(:,t);
					price_energy(:,t) = (fossil_share^epsilon*price_fossil(:,t).^(1-epsilon) + ...
						(1-fossil_share)^epsilon*price_clean(:,t).^(1-epsilon)).^(1/(1-epsilon)); 
					
					// Pre-compute auxiliary variables to equation (88)
					BL = BL_aux .* ...
						price_energy(:,t).^(-theta*mu*(1-chi)/(denom*exp_uhatL)); // outside the integral
					BR = BR_aux .* ...
						price_energy(:,t).^(-theta*(1+theta)*mu*(1-chi)/denom); // inside the integral
    	
					real error = 1. + BW_tol;
					while(error > BW_tol){
						 integral = BR .* uhat_i.^exp_uhatR;
						rhs = trmult_reduced*integral;
						uhat_f = BL .* rhs.^(1/(theta*exp_uhatL));
						error = sum((uhat_i - uhat_f).^2);
						uhat_i = uhat_f;
					}

					real error_l = 1. + BW_tol_l;
					while(error_l > BW_tol_l){

						// Solve for population, equation (3), and scale it to add up to ltilde
						l(:,t) = H.^(-1) .* uhat_i.^(1/Omega) .* m2.^(-1/Omega);
						l(:,t) = l(:,t) / sum(H.*l(:,t)) * ltilde;
								
						// Calculate innovation, equations (49) and (51)
						phi(:,t) = const_phi * l(:,t).^(1/ksi);

						// Back out productivity 
						prod(:,t) = phi(:,t).^(-theta*gamma1/gamma2) .* prod_next.^(1/gamma2);
						avgprod = mean(prod(:,t));
						prod(:,t) = avgprod^(gamma2-1) * prod(:,t);    
					
						// Retrieve utility, equation (90)
						u(:,t) = uhat_i * const_phi^(-gamma1/gamma2) * ...
							mean(prod(:,t))^((gamma2-1)/(gamma2*theta)) * ...
							(ltilde/sum(uhat_i.^(1/Omega).*m2.^(-1/Omega)))^(natural/theta);
						
						// Calculate real GDP per capita, equation (4)
						realgdp(:,t) = u(:,t) ./ amen(:,t) .* l(:,t).^lambda;
						realgdp_w(t) = sum(realgdp(:,t).*H.*l(:,t))/ltilde;
						
						// Calculate energy use, equations (52) and (53)
						emiCO2_ff(:,t) = const_energy*(l(:,t)./price_energy(:,t)).*...
							(fossil_share*price_energy(:,t)./price_fossil(:,t)).^epsilon;
						clean(:,t) = const_energy*(l(:,t)./price_energy(:,t)).*...
							((1-fossil_share)*price_energy(:,t)./price_clean(:,t)).^epsilon;
						
						// Update global population
						net_births(:,t) = natal_fct( log(realgdp(:,t)),temp_past(:,t),log(realgdp_w(t)),...
							coeff_pop );
						ltilde1 = ltilde + sum(net_births(:,t).*l(:,t).*H);

						// Compare global populations
						error_l = abs(lbar1 - ltilde1);
						ltilde = round((updatel*lbar1/ltilde1+(1-updatel))*ltilde);
						display(['t = -' num2str(t) '; error_realgdp = ' num2str(error_realgdp) '; error_e = ' num2str(error_e) '; error_l = ' num2str(error_l) ])
					
					}

					// Compare global emiCO2
					emi_ff_f = sum(emiCO2_ff(:,t).*H);
					error_e = abs(emi_ff_f - emi_ff_i);
					emi_ff_i = updatee*emi_ff_f + (1-updatee)*emi_ff_i;
					cumCO2(t) = cumCO2_next - emi_ff_f;
					costCO2_avg_i = mean(costCO2_fct(cumCO2_next - linspace(0,emi_ff_i,1e2)));


				}

				 // Compare growth rate realgdp
			    realgdp_growth_f = realgdp_w_next/realgdp_w(t);
    			error_realgdp = abs(realgdp_growth_f-realgdp_growth_i);
    			realgdp_growth_i = updater*realgdp_growth_f + (1-updater)*realgdp_growth_i;

			}

			 // Update lbar1
    		lbar_time(t) = ltilde;
    		lbar1 = ltilde;
		}






























	
	}

	/* Function that estimates the parameters of the natality rate function,
	 * the migration cost function and the elasticities of energy productivity
	 * growth to global real income growth.
	 */
	void runOncpu(env_t *env) //,vars_t *vars,const unsigned char *hw_agshock,const unsigned char *hw_idshock,out_t *out,int *hw_iter)
	{
		data_m2 = load('Data/derived/m2.mat');
		m2_i = data_m2.m2;
		// save(['Data/derived/natal_migr_Warm_' name_dam '.mat'], ... 'coeff_pop_i', 'm2_i', 'upsilon_fossil_i', 'upsilon_clean_i', '-v7.3')

		// Update variables of period 0
		model_initial_period(env->m2_i, env->l0_model, env->realgdp0_model)

			// Store results for period 20
			l20 = (1.01 ^ 20) * l0_model;
		realgdp20 = (1.02 ^ 20) * realgdp0_model;
		temp20 = temp0_local + 0.7 * scaler_temp;
		// save(['Data/derived/results20_' name_dam '.mat'], ... 'l0_model', 'realgdp0_model', 'l20', 'realgdp20', 'temp20', '-v7.3')

		// Arrange data
		length_ISO = length(year_data) / (2000 - 1950 + 1);
		pop_data_resh = reshape(pop_data, [2000 - 1950 + 1 length_ISO]);
		pop_tot_data = repmat(sum(pop_data_resh, 2), length_ISO, 1);
		weight_pop_data = pop_data./ pop_tot_data;
		// weight_pop_matrix = diag(weight_pop_data).*diag(kron(linspace(1,1,(2000-1950+1))',ones(length_ISO,1)));

		natal_data0 = natal_data(year_data == 2000);
		natal_data0_cell = NaN(n, 1);
		for
			i = 1 : length(unique(C_vect))
						natal_data0_cell(C_vect == i) = natal_data0(i);
		end

			// ********************************* LOOPS
			real error_clean = 1. + ((real)TOLL_CLEAN);
		while (error_clean > TOLL_CLEAN)
		{
			real error_fossil = 1. + ((real)TOLL_FOSSIL);
			while (error_fossil > TOLL_FOSSIL)
			{
				real error_m2 = 1 + ((real)TOLL_FOSSIL);
				while (error_m2 > TOLL_M2)
				{
					error_l = 1 + TOLL_L;
					while (error_l > TOLL_L)
					{
						// 2. Run model backwards, given m_2 and coeff_pop
						// Run model backwards
						backward_climate(env); // [ l_b,~,~,realgdp_b,~,emiCO2_b,temp_b,~,clean_b,~,~ ] = backward_climate( T_back,1,ind_dam );
						// Store utility and realgdp
						l = [fliplr(l_b(
							:, 1 : 50)) l0_model];
						realgdp = [fliplr(realgdp_b(
							:, 1 : 50)) realgdp0_model];
						temp = [fliplr(temp_b(
							:, 1 : 50)) temp0_local]; // from 1950 to 2000

						// 3. Perform NLLS on natality function
						// Construct net births at country level
						// Construct net births at country level
						logrealgdp_c = zeros(length_C_vect, T_back + 1);
						temp_c = zeros(length_C_vect, T_back + 1);
						logrealgdp_w = zeros(length_C_vect, T_back + 1);
							for
								t = 1 : T_back + 1 logrealgdp_c(
													 :, t) = log(accumarray(C_vect, H.*l(
																						   :, t).*
																						realgdp(
																							:, t))
																	 ./
																 accumarray(C_vect, H.*l(
																						   :, t)));
							temp_c(
								:, t) = accumarray(C_vect, H.*l(
																  :, t).*
															   temp(
																   :, t))
											./
										accumarray(C_vect, H.*l(
																  :, t));
							logrealgdp_w(t) = log(sum(H.*l(
															 :, t).*
													  realgdp(
														  :, t)) /
												  sum(H.*l(
															 :, t)));
							end
								// Set numerical parameters
								SSR_f = 1 + tol_final_SSR;
							length_coeff_pop = length(coeff_pop_i);
							error_nlls = 1 + tol_nlls;
							count = 1;

							while
								error_nlls > tol_nlls &&SSR_f > tol_final_SSR &&count < count_max

																							// Construct derivative
																							deriv_i = zeros(length_C_vect * (2000 - 1950 + 1), length_coeff_pop);

								for
									c = 1 : length_coeff_pop

												// Construct coeff_pop_p and coeff_pop_m
												coeff_pop_p = coeff_pop_i;
								coeff_pop_p(c) = coeff_pop_p(c) + size_deriv;
								coeff_pop_m = coeff_pop_i;
								coeff_pop_m(c) = coeff_pop_m(c) - size_deriv;

								// Construct net births at country level
								natal_model_aux_Cvect_p = zeros(length_C_vect, 2000 - 1950 + 1); // from 1950 to 2000
								natal_model_aux_Cvect_m = zeros(length_C_vect, 2000 - 1950 + 1); // from 1950 to 2000
									for
										t = 1 : T_back + 1 natal_model_aux_Cvect_p(
															 :, t) = natal_fct(logrealgdp_c(
																				   :, t),
																			   temp_c(
																				   :, t),
																			   logrealgdp_w(t), coeff_pop_p);
									natal_model_aux_Cvect_m(
										:, t) = natal_fct(logrealgdp_c(
															  :, t),
														  temp_c(
															  :, t),
														  logrealgdp_w(t), coeff_pop_m);
									end

                                    // Sort them according to ISO_code
                                    natal_model_p = reshape(natal_model_aux_Cvect_p',[],1);
                                    natal_model_m = reshape(natal_model_aux_Cvect_m',[],1);

                                    deriv_i(:,c) = (natal_model_p - natal_model_m)/(2*size_deriv);
                                end

                                // Construct net births at country level
                                natal_model_aux_Cvect_i = zeros(length_C_vect,2000-1950+1); // from 1950 to 2000
                                for t=1:T_back+1
                                    natal_model_aux_Cvect_i(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_i);
                                end

                                // Sort them according to ISO_code
                                natal_model_i = reshape(natal_model_aux_Cvect_i',[],1);

                                // Construct error and SSR
                                error_i = natal_data - natal_model_i;
                                SSR_i = error_i'*weight_pop_matrix*error_i;

                                // Regress errors on natal_model_i
                                rcond_ind = rcond(deriv_i'*weight_pop_matrix*deriv_i);
                                if rcond_ind < 1e-25
                                    coeff_reg = pinv(deriv_i'*weight_pop_matrix*deriv_i)*...
                                        (deriv_i'*weight_pop_matrix*error_i);
                                else
                                    coeff_reg = (deriv_i'*weight_pop_matrix*deriv_i)\...
                                        (deriv_i'*weight_pop_matrix*error_i);
                                end

                                // Set step
                                step = (1/2)^0;

                                while SSR_f > SSR_i && step > (1/2)^tol_step

                                    // Compute candidate for new coefficient
                                    coeff_pop_f = coeff_pop_i + step*coeff_reg;

                                    // Construct net births at country level
                                    natal_model_aux_Cvect_i = zeros(length_C_vect,2000-1950+1); // from 1950 to 2000
                                    natal_model_aux_Cvect_f = zeros(length_C_vect,2000-1950+1); // from 1950 to 2000
                                    for t=1:T_back+1
                                        natal_model_aux_Cvect_i(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_i);
                                        natal_model_aux_Cvect_f(:,t) = natal_fct(logrealgdp_c(:,t),temp_c(:,t),logrealgdp_w(t),coeff_pop_f);
                                    end

                                    // Sort them according to ISO_code
                                    natal_model_i = reshape(natal_model_aux_Cvect_i',[],1);
                                    natal_model_f = reshape(natal_model_aux_Cvect_f',[],1);

                                    // Construct errors and SSR
                                    error_i = natal_data - natal_model_i;
                                    error_f = natal_data - natal_model_f;
                                    SSR_i = error_i'*weight_pop_matrix*error_i;
                                    SSR_f = error_f'*weight_pop_matrix*error_f;

                                    display(['SSR_f = ' num2str(SSR_f)  '; SSR_i = ' num2str(SSR_i) '; step = ' num2str(step)])
                                    step = step/2;
                                    if step == (1/2)^tol_step
                                        coeff_pop_f = coeff_pop_i;
                                        count = count_max;
                                    end

                                end

                                // Compute error_nlls
                                aux_error_nlls = step*abs(coeff_pop_f) - scal_nlls*(abs(coeff_pop_i) + lev_nlls);
                                error_nlls = sum(aux_error_nlls > 0);

                                // Update estimates
                                coeff_pop_i = coeff_pop_f;
                                SSR_f = SSR_i + 1;
                                count = count + 1;

                            end

                            realgdp0_w_model = sum(realgdp0_model.*l0_model.*H)/lbar;
                            net_births0 = natal_fct(log(realgdp0_model),temp0_local,log(realgdp0_w_model),coeff_pop_i);

                            // Aggregate natality rates at country level
                            natal_model0_country_short = accumarray(C_vect,H.*l0_model.*net_births0)./accumarray(C_vect,H.*l0_model);
                            natal_model0_country = NaN(n,1);
                            for i=1:length(unique(C_vect))
                                natal_model0_country(C_vect==i) = natal_model0_country_short(i);
                            end

							//// 4. Run model forward to update l20, given natality parameters

                            // Run model forward
                            display([newline 'Run model forward' newline])
                            [ l, ~, prod, realgdp, amen, ~, ~, ~, ~, ...
                                temp_local, price_emi, ~, price_clean, ~ ] = ...
                                forward_climate( T, 1, ind_dam, 0, ...
                                zeros(n,T), zeros(n,T), zeros(n,T), ones(3,1) );

                            // Compute error_l
                            error_l = sqrt(sum((l20 - l(:,20)).^2));
                            display(['error_l = ' num2str(error_l)])

                            // Store results for period 20
                            l20 = l(:,20);
                            realgdp20 = realgdp(:,20);
                            temp20 = temp_local(:,20);
                            save(['Data/derived/results20_' name_dam '.mat'],...
                                'l0_model','realgdp0_model','l20','realgdp20','temp20','-v7.3')
					}

					//// 5. Update migration costs
					// Update migration costs
					display([newline 'Update migration costs' newline])
						price_energy = (fossil_share ^ epsilon * price_emi.^ (1 - epsilon) + ...(1 - fossil_share) ^ epsilon * price_clean.^ (1 - epsilon)).^ (1 / (1 - epsilon));
					[m2_f] = migration_costs(m2_i, amen(
													   :, 5),
											 prod(
												 :, 5),
											 pop5_dens, ... price_energy(
															:, 5),
											 tol_m2_inner);

					// Compute error_m2
					error_m2 = sqrt(sum((m2_i - m2_f).^ 2));
					display(['error_m2 = ' num2str(error_m2)])
						m2_i = update_m2 * m2_f + (1 - update_m2) * m2_i;
					m2_i = m2_i / min(m2_i);
					save(['Data/derived/natal_migr_Warm_' name_dam '.mat'], ... 'coeff_pop_i', 'm2_i', 'upsilon_fossil_i', 'upsilon_clean_i', '-v7.3')

						// Update variables of period 0
						[l0_model, ~, ~, realgdp0_model] = model_initial_period(m2_i);

					// Update variables of period 20
					display([newline 'Run model forward' newline])
						[l, ~, prod, realgdp, amen, ~, ~, ~, ~, ... temp_local, price_emi, ~, price_clean, ~] = ... forward_climate(T, 1, ind_dam, 0, ... zeros(n, T), zeros(n, T), zeros(n, T), ones(3, 1));

					// Store results for period 20
					l20 = l(
						:, 20);
					realgdp20 = realgdp(
						:, 20);
					temp20 = temp_local(
						:, 20);
					save(['Data/derived/results20_' name_dam '.mat'], ... 'l0_model', 'realgdp0_model', 'l20', 'realgdp20', 'temp20', '-v7.3')
				}

				//// 6. Update upsilon fossil

				// Compute error_upsilon fossil
				emi_ff_model = fliplr(sum(emiCO2_b.*repmat(H, 1, T_back)))'; error_fossil = sqrt(mean((emi_ff_model - emi_ff_data_tend).^ 2));

					slope_fossil_model = (emi_ff_model(1) - emi_ff_model(end)) / length(emi_ff_model);
				slope_fossil_tend = (emi_ff_data_tend(1) - emi_ff_data_tend(end)) / length(emi_ff_data_tend);

				upsilon_fossil_i = (update_upsilon_fossil + (1 - update_upsilon_fossil) * slope_fossil_tend / slope_fossil_model) * upsilon_fossil_i;

				display(['error_fossil = ' num2str(error_fossil) '; upsilon_fossil = ' num2str(upsilon_fossil_i)])
					save(['Data/derived/natal_migr_Warm_' name_dam '.mat'], ... 'coeff_pop_i', 'm2_i', 'upsilon_fossil_i', 'upsilon_clean_i', '-v7.3')

					// Update variables of period 20
					display([newline 'Run model forward' newline])
						[l, ~, prod, realgdp, amen, ~, ~, ~, ~, ... temp_local, price_emi, ~, price_clean, ~] = ... forward_climate(T, 1, ind_dam, 0, ... zeros(n, T), zeros(n, T), zeros(n, T), ones(3, 1));

				// Store results for period 20
				l20 = l(
					:, 20);
				realgdp20 = realgdp(
					:, 20);
				temp20 = temp_local(
					:, 20);
				save(['Data/derived/results20_' name_dam '.mat'], ... 'l0_model', 'realgdp0_model', 'l20', 'realgdp20', 'temp20', '-v7.3')

					// Update migration costs
					display([newline 'Update migration costs' newline])
						price_energy = (fossil_share ^ epsilon * price_emi.^ (1 - epsilon) + ...(1 - fossil_share) ^ epsilon * price_clean.^ (1 - epsilon)).^ (1 / (1 - epsilon));
				[m2_i] = migration_costs(m2_i, amen(
												   :, 5),
										 prod(
											 :, 5),
										 pop5_dens, ... price_energy(
														:, 5),
										 tol_m2_inner);
				save(['Data/derived/natal_migr_Warm_' name_dam '.mat'], ... 'coeff_pop_i', 'm2_i', 'upsilon_fossil_i', 'upsilon_clean_i', '-v7.3')
			}

			//// 7. Update upsilon clean

			// Compute error_upsilon clean
			clean_model = fliplr(sum(clean_b(
										 :, 16
										 : end).*
									 repmat(H, 1, T_back - 15)))'; error_clean = sqrt(mean((clean_model - tCO2_toe * clean_energy_data).^ 2)); slope_clean_model = (clean_model(1) - clean_model(end)) / length(clean_model); slope_clean_tend = (tCO2_toe * clean_energy_data(1) - tCO2_toe * clean_energy_data(end)) / length(clean_energy_data);
			upsilon_clean_i = (update_upsilon_clean + (1 - update_upsilon_clean) * slope_clean_tend / slope_clean_model) * upsilon_clean_i;
			display(['error_clean = ' num2str(error_clean) '; upsilon_clean = ' num2str(upsilon_clean_i)])
				save(['Data/derived/natal_migr_Warm_' name_dam '.mat'], ... 'coeff_pop_i', 'm2_i', 'upsilon_fossil_i', 'upsilon_clean_i', '-v7.3')

				// Update variables of period 20
				display([newline 'Run model forward' newline])
					[l, ~, prod, realgdp, amen, ~, ~, ~, ~, ... temp_local, price_emi, ~, price_clean, ~] = ... forward_climate(T, 1, ind_dam, 0, ... zeros(n, T), zeros(n, T), zeros(n, T), ones(3, 1));

			// Store results for period 20
			l20 = l(
				:, 20);
			realgdp20 = realgdp(
				:, 20);
			temp20 = temp_local(
				:, 20);
			save(['Data/derived/results20_' name_dam '.mat'], ... 'l0_model', 'realgdp0_model', 'l20', 'realgdp20', 'temp20', '-v7.3')

				// Update migration costs
				display([newline 'Update migration costs' newline])
					price_energy = (fossil_share ^ epsilon * price_emi.^ (1 - epsilon) + ...(1 - fossil_share) ^ epsilon * price_clean.^ (1 - epsilon)).^ (1 / (1 - epsilon));
			[m2_i] = migration_costs(m2_i, amen(
											   :, 5),
									 prod(
										 :, 5),
									 pop5_dens, ... price_energy(
													:, 5),
									 tol_m2_inner);
			save(['Data/derived/natal_migr_Warm_' name_dam '.mat'], ... 'coeff_pop_i', 'm2_i', 'upsilon_fossil_i', 'upsilon_clean_i', '-v7.3')
		}

		{
			if ((hw_main_iter >= num_iter) & (num_iter != 0))
			{
				break;
			}
			hw_main_iter++;

			curr_egm_iter = 0;
			hw_sim_egm(kmprime, st_kprimes, env, curr_egm_iter);
			hw_iter[hw_main_iter] = curr_egm_iter;

			real kcross_l[N_AGENTS];
			for (int is = 0; is < N_AGENTS; is++)
			{
				kcross_l[is] = st_kcross[is];
			}
			hw_sim_ast(kmts, hw_idshock, hw_agshock, env,
					   st_kprimes, kcross_l);

			sim_alm_coeff(kmts, vars->coeff, &metric_coeff, r2, hw_agshock);

			if (metric_coeff > TOLL_COEFF * 100)
			{
				// Replace the old with new capital distribution
				for (int j = 0; j < N_AGENTS; j++)
					st_kcross[j] = kcross_l[j];
			}
			printf("main loop iteration = %d\n", hw_main_iter);
		}

		hw_iter[0] = hw_main_iter;

		return;
	}
}