
function natal_fct_val = natal_fct(logrealgdp,temp,logrealgdp_w,coeff_pop_d) 
        
// Function that computes the natality rate, as described in 
// Section 3.3 and Appendix C
// Inputs: 
// 	logrealgdp: cell-level logarithm of real GDP
//   temp: cell-level temperature
//   logrealgdp_w: logarithm of global average real GDP
//   coeff_pop_d: coefficients of the natality rate function
// Outputs: 
//   natal_fct_val: cell-level natality rates
        
global natal_param temp0_local lbar natal0 natal20 H

// Read data
data_20 = load('Data/derived/results20_med.mat');
l0 = data_20.l0_model;
realgdp0 = data_20.realgdp0_model;
l20 = data_20.l20;
realgdp20 = data_20.realgdp20;
temp20 = data_20.temp20;

logrealgdp0 = log(realgdp0);
realgdp0_w = sum(realgdp0.*l0.*H)/lbar;
logrealgdp0_w = log(realgdp0_w);
logrealgdp20 = log(realgdp20);
logrealgdp20_w = log(sum(realgdp20.*l20.*H)/sum(l20.*H));

pop0_sh = l0.*H/lbar;
pop20_sh = l20.*H/sum(l20.*H);

// Read numerical restrictions on natality functions
b0y_max = natal_param(1);
b1y_min = natal_param(2);
b1y_max = natal_param(3);
b2y_min  = natal_param(4);
b2y_max  = natal_param(5);
b2T_max = natal_param(6);
bsy_min = natal_param(7);
bsy_max = natal_param(8);
bsT_min = natal_param(9);
bsT_max = natal_param(10);

logi_b2T_fct =@(x) b2T_max./(1+exp(-x));
logi_b0y_fct =@(x) b0y_max./(1+exp(-x));
logi_b1y_fct = @(x) b1y_min + (b1y_max - b1y_min)./(1+exp(-x));
logi_b2y_fct = @(x) b2y_min + (b2y_max - b2y_min)./(1+exp(-x));
logi_bsy_fct = @(x) bsy_min + (bsy_max - bsy_min)./(1+exp(-x));
logi_bsT_fct = @(x) bsT_min + (bsT_max - bsT_min)./(1+exp(-x));

// Construct income component of natality rate function, equation (23)
natal_fct_logrealgdp =@(logrealgdp,coeff_pop_d) ...
	(logi_b0y_fct(coeff_pop_d(1)) + ...
    (logi_b2y_fct(coeff_pop_d(4))-logi_b0y_fct(coeff_pop_d(1)))*...
    exp(-logi_b1y_fct(coeff_pop_d(2))*(logrealgdp-logi_bsy_fct(coeff_pop_d(5))).^2)).*...
    (logrealgdp<logi_bsy_fct(coeff_pop_d(5))) + ...
    (0 + ...
    (logi_b2y_fct(coeff_pop_d(4))-0)*...
    exp(-exp(coeff_pop_d(3))*(logrealgdp-logi_bsy_fct(coeff_pop_d(5))).^2)).*...
    (logrealgdp>=logi_bsy_fct(coeff_pop_d(5)));

// Construct b0T, equation (31)
b0T = 2*natal0 - ...
    logi_b2T_fct(coeff_pop_d(7))*sum(exp(-exp(coeff_pop_d(6))*(temp0_local-logi_bsT_fct(coeff_pop_d(8))).^2).*pop0_sh) - ...
    2*sum(natal_fct_logrealgdp(logrealgdp0,coeff_pop_d).*pop0_sh);

// Construct bw, equation (33)
bw = log(-1+(b0T + ...
    sum(logi_b2T_fct(coeff_pop_d(7))*exp(-exp(coeff_pop_d(6))*(temp20-logi_bsT_fct(coeff_pop_d(8))).^2).*pop20_sh))./...
    (natal20 - sum(natal_fct_logrealgdp(logrealgdp20,coeff_pop_d).*pop20_sh)))/...
    (logrealgdp20_w-logrealgdp0_w);

// Construct numerator of temperature component of natality rate function,
// equation (24)
natal_fct_temp_num = b0T + ...
    logi_b2T_fct(coeff_pop_d(7))*exp(-exp(coeff_pop_d(6))*(temp-logi_bsT_fct(coeff_pop_d(8))).^2);

// Construct denominator of temperature component of natality rate function,
// equation (24)
natal_fct_temp_denom = (1+exp(bw*(logrealgdp_w-logrealgdp0_w)));

// Construct natality functions
natal_fct_val = ...
    real(natal_fct_temp_num ./ natal_fct_temp_denom + ...
    natal_fct_logrealgdp(logrealgdp,coeff_pop_d));

end
