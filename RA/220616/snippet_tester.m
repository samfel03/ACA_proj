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

input('Wait!\n','s');

% COMPARE
RECEIVE_CFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\coutput";
RECEIVE_TFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\toutput";
RECEIVE_WFILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\7-NLLS\Data\woutput";
diff=abs(logrealgdp_c-transpose(read_bin_2D_from_C(RECEIVE_CFILE+".bin",T_back+1,length_C_vect)));
disp('logrealgdp_c')
max(max(diff))
max(max(diff))/min(min(abs(logrealgdp_c)))
diff=abs(temp_c-transpose(read_bin_2D_from_C(RECEIVE_TFILE+".bin",T_back+1,length_C_vect)));
disp('temp_c')
max(max(diff))
max(max(diff))/min(min(abs(temp_c)))
diff=abs(logrealgdp_w-read_bin_2D_from_C(RECEIVE_WFILE+".bin",T_back+1,1));
disp('logrealgdp_w')
max(diff)
max(diff)/min(abs(logrealgdp_w))