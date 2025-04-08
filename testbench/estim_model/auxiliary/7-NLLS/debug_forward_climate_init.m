% Initializations debug
format long
display('Debug Init')
temp_global(1)
temp_local(1,1)
temp_local(end,1)
amen(1,1)
amen(end,1)
prod(1,1)
prod(end,1)
flat
exp_uhatL
exp_uhatR
FL_H_m2(1)
FL_H_m2(end)
FR_H_m2(1)
FR_H_m2(end)
const_phi
const_energy
stockCO2_layers(1,1)
stockCO2_layers(2,1)
stockCO2_layers(3,1)
stockCO2_layers(4,1)
temp_layers(1,1)
temp_layers(2,1)
lbar_time(1)

%{ 
% Command line Xcode
print m2_aux[0]
print m2_aux[17047]
print temp_global
print temp_local[0]
print temp_local[17047]
print amen[0]
print amen[17047]
print prod[0]
print prod[17047]
print zeta_fossil[0]
print zeta_fossil[17047]
print zeta_clean[0]
print zeta_clean[17047]
print env->flat
print env->exp_uhatL
print env->exp_uhatR
print FL_H_m2[0]
print FL_H_m2[17047]
print FR_H_m2[0]
print FR_H_m2[17047]
print env->const_phi
print env->const_energy
print stockCO2_layers[0]
print stockCO2_layers[1]
print stockCO2_layers[2]
print stockCO2_layers[3]
print temp_layers[0]
print temp_layers[1]
print lbar_time
%}


%% First iteration t - Before while loops
zeta_fossil_prev(1)
zeta_fossil_prev(end)
zeta_clean_prev(1)
zeta_clean_prev(end)
realgdp_w_prev
cumCO2_ff(1)
costCO2_avg_i
FL_aux(1)
FL_aux(end)
FR_aux(1)
FR_aux(end)
%{ 
% Command line Xcode
print zeta_fossil[0]
print zeta_fossil[17047]
print zeta_clean[0]
print zeta_clean[17047]
print realgdp_w
print cumCO2_ff
print costCO2_avg_i
print FL_aux[0]
print FL_aux[17047]
print FR_aux[0]
print FR_aux[17047]
%}

%% First iteration t - Between realgdp and e_loop
zeta_fossil(1,1)
zeta_fossil(end,1)
zeta_clean(1,1)
zeta_clean(end,1)
%{ 
% Command line Xcode
print zeta_fossil[0]*RHS_zeta_fossil
print zeta_fossil[17047]*RHS_zeta_fossil
print zeta_clean[0]*RHS_zeta_clean
print zeta_clean[17047]*RHS_zeta_clean
%}

%% First iteration t - Between e_loop and Iterate uhat, equation (75)
price_energy(1,1)
price_energy(end,1)
varphi(1,1)
varphi(end,1)
FL(1)
FL(end)
FR(1)
FR(end)
%{ 
% Command line Xcode
print price_energy[0]
print price_energy[17047]
print varphi[0]
print varphi[17047]
print FL[0]
print FL[17047]
print FR[0]
print FR[17047]
%}
%% First iteration t - loop uhat, equation (75)
uhat_i(1)
uhat_i(end)
%{ 
% Command line Xcode
print uhat_i[0]
print uhat_i[17047]
%}
%% Update objects
l(1,1)
l(end,1)
phi(1,1)
phi(end,1)
(lbar_time(t)/sum(uhat_i.^(1/Omega).*m2_aux.^(-1/Omega)))^(flat/theta)
u(1,t)
u(end,t)
realgdp(1,1)
realgdp(end,1)
realgdp_w(1)
prod(1,2)
prod(end,2)
const_energy*(1./varphi(1,t)).*(l(1,t)./price_energy(1,t))
emiCO2_ff(1,1)
emiCO2_ff(end,1)
emi_ff_f
emi_ff_f_abat
emiCO2_total(1)
costCO2_avg_i
price_fossil(1,1)
emi_ff_f_abat
error_e
costCO2_avg_i
%{ 
% Command line Xcode
print l_vec[0]
print l_vec[17047]
print phi[0]
print phi[17047]
print u_i_scaler
print uhat_i[0]*u_i_scaler
print uhat_i[0]*u_i_scaler/amen[0] * ((double) pow(l_vec[0],env__lambda))
print uhat_i[17047]*u_i_scaler/amen[17047] * ((double) pow(l_vec[17047],env__lambda))
print realgdp[0]
print realgdp[17047]
print realgdp_w_next
print prod[0]
print prod[17047]
print emi_ff_f
print emi_ff_f_abat
print emiCO2_total
print costCO2_avg_i
print price_fossil_real
print emi_ff_f_abat
print error_e
print costCO2_avg_i
%}

%% 
stockCO2_layers(:,t+1)
temp_layers(:,t+1)
temp_global(t+1)
temp_local(1,t+1)
temp_local(end,t+1)
amen(1,t+1)
amen(end,t+1)
prod(1,t+1)
prod(end,t+1)
lbar_time(t+1)
realgdp(1,t)
realgdp(end,t)
%theta_amen_temp(temp_local_aux(1))
%theta_prod_temp(temp_local_aux(1))

%{
print stockCO2_layers[0]
print stockCO2_layers[1]
print stockCO2_layers[2]
print stockCO2_layers[3]
print temp_layers[0]
print temp_layers[1]
print temp_global
print temp_local[0]
print temp_local[17047]
print amen[0]
print amen[17047]
print prod[0]
print prod[17047]
print lbar_time
print realgdp[0]
print realgdp[17047]
print realgdp_w

//print Delta_temp
//print theta_amen_temp
//print theta_prod_temp
%}

