clean_model(1)
clean_model(end)
error_clean
slope_clean_model
slope_clean_tend
upsilon_clean_i

%{
print clean_model[0]
print clean_model[34]
print *error
print slope_model
print slope_tend
print env->upsilon_clean_i
%}

%% Debug forward climate (use usual)

%% Debug 
l20(1)
l20(end)
realgdp20(1)
realgdp20(end)
temp20(1)
temp20(end)
price_energy(1,5)
price_energy(end,5)
m2_i(1)
m2_i(end)

%{
print env->l20_model[0]
print env->l20_model[17047]
print env->realgdp20_model[0]
print env->realgdp20_model[17047]
print env->temp20_local[0]
print env->temp20_local[17047]
print price_energy[0]
print price_energy[17047]
print env->m2_i[0]
print env->m2_i[17047]
%}

