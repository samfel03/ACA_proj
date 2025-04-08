%% Compare C and Matlab Vectors
% Vectors List: Missing amen_sens and prod_sens
%readveclist = {'a_norm','C_vect','emi_no_ff','forc_noCO2','H','natal_data','pop5_dens','price_energy0','prod0','scaler_temp','u0','zeta_clean0','zeta_fossil0'};
readveclist = {'H','prod0','pop5_dens','u0','a_norm','C_vect','emi0_ff',...
               'emi_no_ff', 'emi0','fossil_share','chi','cost_emi_param','price_energy0',...
    'zeta_clean0', 'zeta_fossil0', 'S0', 'S1', 'S2', 'S3', 'forc_noCO2', ...
    'temp1', 'temp2', 'temp0_global','temp0_local', 'scaler_temp',  ...
    'natal_data', 'pop_data','natal0', 'natal20', 'clean_energy_data', 'emi_ff_data', 'emi_ff_data_tend'}; % 'price_clean0_world' excluded
for j=1:length(readveclist)
    var = readveclist{j};
    display(var);
    % Read Matlab Vector
    address = [outputfolder,'/',var,'.bin']; % set it as binary file
    fprintf("Reading variable %s in: %s2\n",address,var);
    fid = fopen(address, 'r');
    eval(strcat(var,'2=fread(fid, size(',var,'),''double'');')); % H2 = fread(fid, 1, 'double);
    fclose(fid);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
end
assert(sum(diff)==0); %% Vector of differences between variables is zero

%% Compare C and Matlab Matrixes
% Matrix List
readmatlist = {'trmult_reduced','temp_past','Delta_temp','theta_amen_scen','theta_prod_scen'};
for j=1:length(readmatlist)
    var = readmatlist{j};
    display(var);
    % Read Matlab Vector
    address = [outputfolder,'/',var,'.bin']; % set it as binary file
    eval(strcat('[row,col]=size(',var,');'));
    eval(strcat(var,'2=read_bin_2D_from_C(address,row,col);')); % H2 =read_bin_2D_from_C(address,row,col);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
    clearvars row col
end
assert(sum(diff)==0); %% Vector of differences between variables is zero

%% Eyballing trmult_reduced
disp('trmult_reduced')
trmult_reduced(1,12355)
trmult_reduced(17048,17048)
trmult_reduced(2,17048-6+1)
trmult_reduced(17048-12000+1,1201)

disp('temp_past')
temp_past(1,1)
temp_past(17048,51)
temp_past(14001,4)
temp_past(15651,48)

disp('Delta_temp')
Delta_temp(1,1)
Delta_temp(17048,50)
Delta_temp(11001,4)
Delta_temp(17001,48)

disp('theta_amen')
theta_amen_scen(1,1)
theta_amen_scen(4,4)
theta_amen_scen(2,8)
theta_amen_scen(4,9)


%{
trmult_reduced(12355,1)
trmult_reduced(17048,17048)
trmult_reduced(17049-6,2)
trmult_reduced(1200,17049-12000)
%}
