clear
clc
close all

% Store utility and realgdp
% l = [fliplr(l_b(:,1:50)) l0_model];
% realgdp = [fliplr(realgdp_b(:,1:50)) realgdp0_model]; 
% temp = [fliplr(temp_b(:,1:50)) temp0_local]; % from 1950 to 2000

%REPLACE WITH FAKES.
NPOSLAND=17048;
length_C_vect=168;
T_back=50;
tol_nlls = 0;
tol_final_SSR = 1e-5;
coeff_pop_i = [-0.69;0;-5;-0.51;-0.25;-5;2.88;-0.67];
%size_deriv = 1e-5;%This is the original
size_deriv = 1.25;%This is the test value.
count_max = 50;
rng(1,"twister");
H=abs(randn(NPOSLAND,1));
C_vect=randi(length_C_vect,NPOSLAND,1);
l = abs(randn(NPOSLAND,T_back+1));
realgdp=abs(randn(NPOSLAND,T_back+1));
temp=abs(randn(NPOSLAND,T_back+1));


%WRITE THE FAKES.
PASS_HFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\hinput";
PASS_CFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\Cinput";
PASS_LFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\Linput";
PASS_RFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\Rinput";
PASS_TFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\Tinput";
print_bin_2D_to_C(H,PASS_HFILE+".bin");
print_bin_2D_to_C(C_vect,PASS_CFILE+".bin");
print_bin_2D_to_C(l',PASS_LFILE+".bin");
print_bin_2D_to_C(realgdp',PASS_RFILE+".bin");
print_bin_2D_to_C(temp',PASS_TFILE+".bin");


%FLIP THE FAKES.
l=fliplr(l);
realgdp=fliplr(realgdp);
temp=fliplr(temp);



%% 3. Perform NLLS on natality function

% Construct net births at country level
logrealgdp_c = zeros(length_C_vect,T_back+1);
temp_c = zeros(length_C_vect,T_back+1);
logrealgdp_w = zeros(T_back+1,1);%Fixed from zeros(length_C_vect,T_back+1)
for t=1:T_back+1
    logrealgdp_c(:,t) = log(accumarray(C_vect,H.*l(:,t).*realgdp(:,t))./accumarray(C_vect,H.*l(:,t)));
    temp_c(:,t) = accumarray(C_vect,H.*l(:,t).*temp(:,t))./accumarray(C_vect,H.*l(:,t));
    logrealgdp_w(t) = log(sum(H.*l(:,t).*realgdp(:,t))/sum(H.*l(:,t))); 
end

% Set numerical parameters
SSR_f = 1 + tol_final_SSR;
length_coeff_pop = length(coeff_pop_i);
error_nlls = 1 + tol_nlls;
count = 1;

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
    
    error_nlls=0;%debug code!
end

input('Wait!\n','s');

% COMPARE
RECEIVE_CFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\coutput";
diff=abs(deriv_i-transpose(read_bin_2D_from_C(RECEIVE_CFILE+".bin",length_coeff_pop,(T_back+1)*length_C_vect)));
disp('deriv_i')
max(max(diff))
max(max(abs(deriv_i)))