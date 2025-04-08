%% Update Migration Costs
m2_f(1)
m2_f(end)
% Compute error_m2
error_m2
m2_i(1)
m2_i(end)
% Update variables of period 0
l0_model(1)
l0_model(end)
realgdp0_model(1)
realgdp0_model(end)
FL(1)
FL(end)
FR(1)
FR(end)
l0(1)
l0(end)
realgdp0(1)
realgdp0(end)

l20(1)
l20(end)
realgdp20(1)
realgdp20(end)

%% initial_period


%{
print m2_f[0]
print m2_f[17047]
print *error
print env->m2_i[0]
print env->m2_i[17047]
print env->l0_model[0]
print env->l0_model[17047]
print env->realgdp0_model[0]
print env->realgdp0_model[17047]
print FL[0]
print FL[17047]
print FR[0]
print FR[17047]
print env->l0_model[0]
print env->l0_model[17047]
print env->realgdp0_model[0]
print env->realgdp0_model[17047]
print env->realgdp0_w
%}