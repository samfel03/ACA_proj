
function [] = initialize(ind_RCP,maxCO2,eps)

% Function that loads the data and generates the global variables of the model.
% Inputs:
%   indRCP: RCP scenario for the CO2 emissions from non-fossil fuel combustion 
%   and the forcing from non-CO2sources; can take the value of 8.5, 6.0, 4.5 or 2.6; 
%   8.5 is the baseline.
%   maxCO2: total stock of CO2 available in the ground; 19500 is the baseline.
%   eps: elasticity of substitution between fossil fuels and clean energy;
%   1.6 is the baseline.

%% 0. Declare global variables
global datafolder
global H H0 amen_util0 C_vect prod0 pop0 pop0_dens pop1_dens pop5_dens u0 ...
     price_energy0 trmult_reduced n beta ...
     name_type_vect name_long_type_vect name_maps_type_vect ...
     alpha theta Omega HDI0 ...
     emi0_cell emi0 emi0_ff emi0_no_ff emi_no_ff emi_ff_data_tend chi cost_emi_param...
     a0 a1 a2 a3 b1 b2 b3 S0 S1 S2 S3 S_preind temp_preind...
     forc_sens forc_noCO2 c1 c2 d1 d2 temp1 temp2...
     temp0_global temp0_local_long temp0_local scaler_temp Delta_temp1...
     theta_amen_scen theta_prod_scen... 
     lbar lambda gamma1 gamma2 eta mu nu ksi...
     pop_low95 pop_low80 pop_med pop_high80 pop_high95...
     pop_low95_hist pop_low80_hist pop_med_hist pop_high80_hist pop_high95_hist...
     emi_ff_data forc_data length_C_vect...
     emiCO2_RCP stockCO2_RCP forc_RCP temp_global_RCP...
     price_clean0_world price_clean0 price_fossil0 zeta_clean0 zeta_fossil0 fossil_share...
     clean0_cell fossil0_cell epsilon clean_energy_data tCO2_toe map...
     color_olive color_darkgreen color_darkcyan color_yellowgreen color_greenyellow ...
     natal_param conv_usd table_prop...
     name_dam_vect name_dam_long_vect cost_CO2_data a_norm...
     natal_data country_data year_data pop_data temp_past Delta_temp max_cumCO2 natal0 natal20...

if ind_RCP == 8.5 || ind_RCP == 6.0 || ind_RCP == 4.5 || ind_RCP == 2.6 || maxCO2 > 0 || eps > 0

%% 1. Set economic parameters

lbar = 5.9174e+09;      % total population
lambda = 0.32;          % congestion externalities
gamma1 = 0.319;         % elasticity of tomorrow's productivity relative to today's innovation
gamma2 = 0.99246;       % elasticity of tomorrow's productivity relative to today's productivity
eta = 1;                % parameter driving scale of technology diffusion
mu = 0.8;               % labor share in production
nu = 0.15;              % intercept parameter in innovation cost function   
ksi = 125;              % elasticity of innovation costs relative to innovation
sigma = 4;              % elasticity of substitution
psi_util = 0.045;       % wellbeing parameter
beta = 0.965;           % discount factor for present discounted values
alpha = 0.06;           % agglomeration externalities
theta = 6.5;            % variance productivity shocks
Omega = 0.5;            % variance taste shocks
max_cumCO2 = maxCO2;    % total stock of CO2 in the ground
epsilon = eps;          % elasticity of substitution between fossil fuels and clean energy
tCO2_toe = 2.8466;      % conversion factor: GtCO2 per Gtoe
price_fossil0_world = 72.99*10^9; % price of fossil fuels in usd/GtCO2
price_clean0_world = 1.15*76.34*10^9/tCO2_toe; % price of clean energy in usd/GtCO2

%% 2. Load initial land, amenities, productivities, population and wages

data_H0 = load([datafolder,'/H0_areal.mat']); 
H0 = data_H0.H0;
H = H0(H0>0);
n = length(H);                      % number of cells with positive land
%%
data_amen_util_H0 = load([datafolder,'/derived/amen_util.mat']); 
amen_util_H0 = data_amen_util_H0.amen_util_H0;
amen_util0 = amen_util_H0(:,3);     % ratio of amenities to utility in 2000

data_prod_H0 = load([datafolder,'/derived/prod.mat']);
prod_H0 = data_prod_H0.prod_H0;
prod0 = prod_H0(:,3);               % productivities in 2000

data_pop = load([datafolder,'/pop_Gecon.mat']);
pop_aux = data_pop.pop;
pop0 = pop_aux(:,:,3);              % population in 2000 
pop0_dens = pop0(H0>0)./H0(H0>0);
pop5 = pop_aux(:,:,4);              % population in 2005
pop5_dens = pop5(H0>0)./H0(H0>0);
pop1_dens = (4/5)*pop0_dens + (4/5)*pop5_dens;

data_wage = load([datafolder,'/wage_Gecon.mat']);
wage_aux = data_wage.wage;
w0 = wage_aux(:,:,3);               % wage in 2000
w0 = w0(H0>0);

%% 3. Load and shape utility levels and HDI

data_HDI_GDPpc = readtable([datafolder,'/HDI_GDPpc.csv']);
data_HDI0 = table2array(data_HDI_GDPpc(1:n,4));

HDI0 = zeros(180,360);              % Human Development Index in 2000
HDI0(H0>0) = data_HDI0;
u0 = exp(HDI0(H0>0).^3./psi_util);  % utility in 2000
a_norm = amen_util0.*u0;            % amenities in 2000

%% 4. Load trmult 

% Bilateral trade cost on Earth cells at t=0 only
data_trmult = load([datafolder,'/trmult_reduced.mat']);
trmult_reduced = data_trmult.trmult_reduced;

%% 5. Load countries indices

C = csvread([datafolder,'/C.csv']);    % national demarcations
C_vect = C(H0>0);
length_C_vect = length(unique(C_vect));

%% 6. Construct CO2 emissions and clean energy use 

% Global CO2 emissions from fossil fuels from 2000 to 2600, by IPCC
emi_ff_RCP = csvread([datafolder,'/CO2_ff.csv']);
emi_ff = emi_ff_RCP(:,5-floor(ind_RCP/2));
emi0_ff = emi_ff(1,1);

% Global CO2 emissions from non fossil fuels from 2000 to 2600, by IPCC
emi_no_ff_RCP = csvread([datafolder,'/CO2_noff_smooth.csv']);
emi_no_ff = emi_no_ff_RCP(:,5-floor(ind_RCP/2));
emi0_no_ff = emi_no_ff(1);
emi_no_ff = emi_no_ff(2:end);

emi0 = emi0_ff + emi0_no_ff;        % total CO2 emissions for 2000

% CO2 emissions at cell level for 2000
data_emi = load([datafolder,'/CO2_EDGAR.mat']); % cell level CO2 emissions
emi_cell = data_emi.CO2_EDGAR;
emi_cell = emi_cell(:,:,3);
emi0_cell = emi_cell(H0>0);

% CO2 emissions and clean energy at the country level for 2000
emi0_ff_country = csvread([datafolder,'/CO2_country.csv']);
emi0_ff_country = emi0_ff_country(:,3);
emi0_ff_cell = zeros(n,1);

clean0_country = csvread([datafolder,'/clean_country.csv']);
clean0_country = clean0_country(:,3);
clean0_cell = zeros(n,1);

% Match CO2 emissions and clean energy at the country level for 2000
for i=1:length_C_vect
     emi0_ff_cell(C_vect==i) = emi0_cell(C_vect==i)*emi0_ff_country(i)/sum(emi0_cell(C_vect==i));
    clean0_cell(C_vect==i) = emi0_cell(C_vect==i)*clean0_country(i)/sum(emi0_cell(C_vect==i));
end

emi0_ff_cell = emi0_ff_cell*emi0_ff/sum(emi0_ff_cell);
emi0_ff_cell = emi0_ff_cell./H;
clean0_cell = clean0_cell./H;

%% 7. Construct energy parameters in technology

% Define global use of fossil fuels and clean energy
clean0 = sum(clean0_cell.*H); 
fossil0 = emi0_ff; 

% Construct share of fossil fuels in energy composite
fossil_share = (1+(price_clean0_world/price_fossil0_world)*(clean0/fossil0)^(1/epsilon))^(-1);

% Construct share of energy in production, equations (7) and (44)
price_energy0_world = ...
    (fossil_share^epsilon*price_fossil0_world^(1-epsilon) + ...
    (1-fossil_share)^epsilon*price_clean0_world^(1-epsilon))^(1/(1-epsilon));
energy0 = ...
    (fossil_share*fossil0^((epsilon-1)/epsilon) + ...
    (1-fossil_share)*clean0^((epsilon-1)/epsilon))^(epsilon/(epsilon-1));
GDP0 = sum(w0.*pop0_dens.*H); 
energy_share = price_energy0_world*energy0*(mu+gamma1/ksi)/GDP0;
chi = 1-energy_share/mu;

%% 8. Construct extraction cost function

% Read cost extraction data
cost_CO2_data = csvread([datafolder,'/CO2_cost.csv']);

% Define cost extraction function
costCO2_fct_aux =@(cost_emi_param_aux,cumCO2) ...
    cost_emi_param_aux(1)./(cost_emi_param_aux(2) + exp(-cost_emi_param_aux(3)*(cumCO2-cost_emi_param_aux(4)))) - ...
    (cost_emi_param_aux(5)*19500./(cumCO2-19500)).^3;

% Find parameters that better fit the data
options = optimoptions('lsqcurvefit','Display','none');
cost_emi_param_i = [2 1 1e-4 5000 1];
cost_emi_param_f = lsqcurvefit(costCO2_fct_aux,cost_emi_param_i,...
    cost_CO2_data(:,2),cost_CO2_data(:,1),[1 0 0 0 0],[Inf Inf 5*1e-4 Inf Inf],...
    options);

% Redefine extraction cost function
cost_emi_param_f(5) = cost_emi_param_f(5)^3;
cost_emi_param = [cost_emi_param_f maxCO2 3];

% Define normalization relative to Princeton wage
GDPpc0 = GDP0/(w0(3199)*lbar); 
cost_emi_param([1 5]) = cost_emi_param([1 5])/GDPpc0; % usdP/GtCO2
price_clean0_world = price_clean0_world/GDPpc0; % usdP/GtCO2
conv_usd = 1/GDPpc0;

costCO2_fct =@(cumCO2) ...
    cost_emi_param(1)./(cost_emi_param(2) + exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
    cost_emi_param(5)*(cost_emi_param(6)./(cumCO2-cost_emi_param(6))).^cost_emi_param(7);

%% 9. Construct energy productivity

% Construct energy use at the cell level, equation (7)
fossil0_cell = emi0_ff_cell;
energy0_cell = (fossil_share*fossil0_cell.^((epsilon-1)/epsilon) + ...
    (1-fossil_share)*clean0_cell.^((epsilon-1)/epsilon)).^(epsilon/(epsilon-1));

% Construct energy price at the cell level by source, equations (52), (53)
% and (44)
const_energy = (1-chi)*mu/(mu+gamma1/ksi);
price_clean0 = const_energy*(1-fossil_share)*...
    (pop0_dens./energy0_cell).*(energy0_cell./clean0_cell).^(1/epsilon);
price_fossil0 = const_energy*fossil_share*...
    (pop0_dens./energy0_cell).*(energy0_cell./fossil0_cell).^(1/epsilon);
price_energy0 = (fossil_share^epsilon*price_fossil0.^(1-epsilon) + ...
    (1-fossil_share)^epsilon*price_clean0.^(1-epsilon)).^(1/(1-epsilon)); 

% Construct initial energy productivities
zeta_clean0 = price_clean0_world./price_clean0; 
zeta_fossil0 = costCO2_fct(0)./price_fossil0; 

%% 10. Set carbon circulation parameters

% Set parameters regarding depreciation of CO2 in the atmosphere
a0 = 0.2173;        % share of CO2 emissions remaining in the atmosphere forever
a1 = 0.2240;        % share of CO2 emissions associated with the timescale b1
a2 = 0.2824;
a3 = 0.2763;

b1 = 394.4;
b2 = 36.54;
b3 = 4.304;

S_preind = 2200;    % CO2 stock in pre-industrial era

% Read total CO2 emissions from 1999 to 1945
emiCO2_data = flipud(csvread([datafolder,'/CO2_hist.csv'])); 
length_emi_data = length(emiCO2_data);

% Initialize CO2 stock layers, equations (38) and (39)
S0 = a0*sum(emiCO2_data) + S_preind; 
S1 = a1*sum(exp(-(0:1:length_emi_data-1)'/b1).*emiCO2_data);
S2 = a2*sum(exp(-(0:1:length_emi_data-1)'/b2).*emiCO2_data);
S3 = a3*sum(exp(-(0:1:length_emi_data-1)'/b3).*emiCO2_data);

%% 11. Set forcing parameters

forc_sens = 5.35;   % forcing sensitivity

% Read non CO2 radiative forcing
forc_noCO2_RCP = csvread([datafolder,'/Forcing_noCO2_smooth.csv']);
forc_noCO2 = forc_noCO2_RCP(:,5-floor(ind_RCP/2));

%% 12. Set global temperature parameters

% Set global temperature parameters
c1 = 0.631;         % temperature evolution parameters
c2 = 0.429;

d1 = 8.4;
d2 = 409.5;

temp_preind = 8.1;  % temperature in pre-industrial era

% Read forcing from 2000 to 1825
forc_data = flipud(csvread([datafolder,'/Forcing_hist.csv'])); 
length_forc_data = length(forc_data);

% Initialize temperature layers, equation (41)
temp1 = (c1/d1)*sum(exp(-(0:1:length_forc_data-1)'/d1).*forc_data);
temp2 = (c2/d2)*sum(exp(-(0:1:length_forc_data-1)'/d2).*forc_data) + temp_preind;
temp0_global = temp1 + temp2;

%% 13. Load local January-July temperature from 1950 to 2000 

data_temp = load([datafolder,'/temp.mat']);
temp0_local_long = data_temp.temp0_local_10y;
temp0_local = data_temp.temp0_local_10y_mean;
Delta_temp1 = data_temp.Delta_temp1;
temp_past = data_temp.temp_10y_past;
Delta_temp = data_temp.Delta_temp;

%% 14. Load temperature scaler 

% Read temperature scaler computed in temp_downscaling.do
scaler_table = readtable([datafolder,'/derived/scaler_temp.csv']);
lat_scaler = table2array(scaler_table(:,1));
lon_scaler = table2array(scaler_table(:,2));
scaler_data = table2array(scaler_table(:,5));
length_scaler = length(lon_scaler);

% Arrange temperature scaler in a grid
scaler_grid = NaN(180,360);
for i=1:length_scaler
    scaler_grid(90.5-lat_scaler(i),lon_scaler(i)+180.5,:) = ...
        scaler_data(i);
end
scaler_grid(H0 == 0) = NaN;

% Interpolate missing data
scaler_grid_long = [scaler_grid(:,341:360) scaler_grid scaler_grid(:,1:20)];
H0_long = [H0(:,341:360) H0 H0(:,1:20)];
for i=1:11 % iterations
    for k=1:5 % radiius of surronding cells
        indi_scaler = (H0_long>0 & isnan(scaler_grid_long));
        [lat_scaler,lon_scaler] = find(indi_scaler==1);
        cent_scaler = (lon_scaler > 20) & (lon_scaler < 381);
        lat_scaler = lat_scaler(cent_scaler);
        lon_scaler = lon_scaler(cent_scaler);
        
        length_scaler = length(lat_scaler);
        for j=1:length_scaler % missing data
            scaler_grid_long(lat_scaler(j),lon_scaler(j)) = nanmean(scaler_grid_long(...
                lat_scaler(j)-i:lat_scaler(j)+i,...
                lon_scaler(j)-i:lon_scaler(j)+i),'all');
        end        
    end
end

scaler_temp = scaler_grid_long(:,21:380);
scaler_temp = scaler_temp(H0>0);

%% 15. Load damage functions
%{
% Read coefficients from damage function estimated in damage_function.do
theta_amen_logi_vect = readtable([datafolder,'/derived/amen_coeff_10y_1h_20b_550d.csv']);
theta_amen_logi_vect = table2array(theta_amen_logi_vect);
theta_prod_logi_vect = readtable([datafolder,'/derived/prod_coeff_10y_1h_20b_550d.csv']);
theta_prod_logi_vect = table2array(theta_prod_logi_vect);

theta_amen_scen = theta_amen_logi_vect(:,1:9); 
theta_prod_scen = theta_prod_logi_vect(:,1:9);

theta_amen_min = theta_amen_scen(1,9);
theta_amen_max = theta_amen_scen(2,9);
theta_amen_center = theta_amen_scen(3,9);
theta_amen_steep = theta_amen_scen(4,9);
theta_amen_temp =@(temp) theta_amen_min + ...
    (theta_amen_max - theta_amen_min)./...
    (1+exp(theta_amen_steep*(temp - theta_amen_center)));

theta_prod_min = theta_prod_scen(1,9);
theta_prod_max = theta_prod_scen(2,9);
theta_prod_center = theta_prod_scen(3,9);
theta_prod_steep = theta_prod_scen(4,9);
theta_prod_temp =@(temp) theta_prod_min + ...
    (theta_prod_max - theta_prod_min)./...
    (1+exp(theta_prod_steep*(temp - theta_prod_center)));

% Display results for damage function estimates
temp_cold = -37.79;
temp_hot = 25.77;
disp(['In the coldest bin of the Earth, ' num2str(temp_cold) 'ºC, '...
    'a temperature increase in 1ºC changes local amenities by ' ...
    num2str(100*theta_amen_temp(temp_cold)) '% and local productivities by ' ...
    num2str(100*theta_prod_temp(temp_cold)) '% '])
disp(['In the hottest bin of the Earth, ' num2str(temp_hot) 'ºC, '...
    'a temperature increase in 1ºC changes local amenities by ' ...
    num2str(100*theta_amen_temp(temp_hot)) '% and local productivities by ' ...
    num2str(100*theta_prod_temp(temp_hot)) '% '])
disp(['The optimal temperature for amenities is ' num2str(fzero(theta_amen_temp,0)) 'ºC ' ...
    'and for productivities is ' num2str(fzero(theta_prod_temp,0)) 'ºC '])
%}
%% 16. Load historical population 

% Read net birth historical data
birth_death = csvread([datafolder,'/birth_death_pop.csv']);
country_data = birth_death(:,1);
year_data = birth_death(:,2);
natal_data = birth_death(:,3);
pop_data = birth_death(:,4);

% Define natality rates of 2000 and 2020
natal0 = sum(natal_data(year_data==2000).*pop_data(year_data==2000))/...
    sum(pop_data(year_data==2000)); 
natal20 = sum(natal_data(year_data==2020).*pop_data(year_data==2020))/...
    sum(pop_data(year_data==2020)); 

% Keep data for years < 2001
natal_data = natal_data(year_data < 2001);
country_data = country_data(year_data < 2001);
pop_data = pop_data(year_data < 2001);
year_data = year_data(year_data < 2001);

%% 17. Load population predictions (UN)

% Read UN population projections
pop_hist = csvread([datafolder,'/pop_uncert.csv']);

pop_low95 = pop_hist(1,51:end);
pop_low80 = pop_hist(2,51:end);
pop_med = pop_hist(3,51:end);
pop_high80 = pop_hist(4,51:end);
pop_high95 = pop_hist(5,51:end);

pop_low95_hist = pop_hist(1,:);
pop_low80_hist = pop_hist(2,:);
pop_med_hist = pop_hist(3,:);
pop_high80_hist = pop_hist(4,:);
pop_high95_hist = pop_hist(5,:);

%% 18. Construct climate predictions (IPCC)

emi_ff_RCP = csvread([datafolder,'/CO2_ff.csv']);
emi_no_ff_RCP = csvread([datafolder,'/CO2_noff_smooth.csv']);
emiCO2_RCP = emi_ff_RCP + emi_no_ff_RCP;

stockCO2_layers_RCP = zeros(4,600,4);
forc_RCP = zeros(600,4);
temp_layers_RCP = zeros(2,600,4);

% Construct CO2 stock, forcing and temperature, using data on CO2 emissions
% and non-CO2 forcing, equations (15) and (37)-(41)
for i=1:4
    stockCO2_layers_RCP(1,1,i) = S0 + a0*emiCO2_RCP(1,i);
    stockCO2_layers_RCP(2,1,i) = (exp(-1/b1))*S1 + a1*emiCO2_RCP(1,i);
    stockCO2_layers_RCP(3,1,i) = (exp(-1/b2))*S2 + a2*emiCO2_RCP(1,i);
    stockCO2_layers_RCP(4,1,i) = (exp(-1/b3))*S3 + a3*emiCO2_RCP(1,i);
    
    forc_RCP(1,i) = forc_sens*log(sum(stockCO2_layers_RCP(:,1,i))/S_preind) + forc_noCO2_RCP(1,i);
    
    temp_layers_RCP(1,1,i) = (exp(-1/d1))*temp1 + (c1/d1)*forc_RCP(1,i);
    temp_layers_RCP(2,1,i) = (exp(-1/d2))*temp2 + (c2/d2)*forc_RCP(1,i);
    
    for t=1:600-1
        stockCO2_layers_RCP(1,t+1,i) = stockCO2_layers_RCP(1,t,i) + a0*emiCO2_RCP(t+1,i);
        stockCO2_layers_RCP(2,t+1,i) = (exp(-1/b1))*stockCO2_layers_RCP(2,t,i) + a1*emiCO2_RCP(t+1,i);
        stockCO2_layers_RCP(3,t+1,i) = (exp(-1/b2))*stockCO2_layers_RCP(3,t,i) + a2*emiCO2_RCP(t+1,i);
        stockCO2_layers_RCP(4,t+1,i) = (exp(-1/b3))*stockCO2_layers_RCP(4,t,i) + a3*emiCO2_RCP(t+1,i);
        
        forc_RCP(t+1,i) = forc_sens*log(sum(stockCO2_layers_RCP(:,t+1,i))/S_preind)/log(2) + forc_noCO2_RCP(t+1,i);
        
        temp_layers_RCP(1,t+1,i) = (exp(-1/d1))*temp_layers_RCP(1,t,i) + (c1/d1)*forc_RCP(t+1,i);
        temp_layers_RCP(2,t+1,i) = (exp(-1/d2))*temp_layers_RCP(2,t,i) + (c2/d2)*forc_RCP(t+1,i);
    end

end
stockCO2_RCP = permute(sum(stockCO2_layers_RCP,1),[2 3 1]);
temp_global_RCP = permute(sum(temp_layers_RCP,1),[2 3 1]);

%% 19. Load historic CO2 emissions

% Historical clean energy use
clean_energy_data = csvread([datafolder,'/clean_energy_hist.csv']);
clean_energy_data = clean_energy_data(1:end-1); % from 1965 to 1999

% Historical fossil fuel CO2 emission and its trend
emi_ff_all = csvread([datafolder,'/CO2_hist_ff.csv']);
emi_ff_data = emi_ff_all(:,1); 
emi_ff_data_tend = emi_ff_all(:,2);

%% 20. Load gridded map

map_data = load([datafolder,'/map_grid.mat']);
map = map_data.map;     % map of size 2700x5400 for a better resolution of plots

%% 21. Set numerical restrictions on natality functions

b0y_max = 0.045;
b1y_min = 0.01;
b1y_max = 0.03;
b2y_min = -0.00090; 
b2y_max = -0.00050;
b2T_max = 0.015;
bsy_min = 0;
bsy_max = 8;
bsT_min = 14;
bsT_max = 22; 
natal_param = [b0y_max b1y_min b1y_max b2y_min b2y_max ...
    b2T_max bsy_min bsy_max bsT_min bsT_max]';

%% 22. Define colors and variable names for plots

color_olive = [128 128 0]/255;
color_darkgreen = [0 100 0]/255;
color_darkcyan = [0 139 139]/255;
color_yellowgreen = [154 205 50]/255;
color_greenyellow = [173 255 47]/255;

name_type_vect = {'Warm', 'WarmAm', 'WarmPr'};
name_long_type_vect = {'', 'onlyAm_', 'onlyPr_'};
name_maps_type_vect = {'', 'effect only on amenities', 'effect only on productivity'};

name_dam_vect = {'low95' 'high95' 'low90' 'high90' 'low80' 'high80' 'low60' 'high60' 'med'};
name_dam_long_vect = {'Low 95%' 'High 95%' 'Low 90%' 'High 90%' 'Low 80%' 'High 80%' 'Low 60%' 'High 60%' 'Baseline'};

table_prop = {' ' 'BGP Real GDP' 'PDV Real GDP' 'BGP Welfare' 'PDV Welfare'};

else
    
if ind_RCP ~= 8.5 && ind_RCP ~= 6.0 && ind_RCP ~= 4.5 && ind_RCP ~= 2.6
disp('Non-existent RCP scenario, consider RCP scenario 8.5, 6.0, 4.5 or 2.6')
elseif maxCO2 <= 0
disp('Negative maximum stock of CO2 in the ground, consider strictly positive values')    
elseif eps < 0
disp('Negative elasticity of substitution between fossil fuels and clean energy, consider positive values')    
end

end

end
