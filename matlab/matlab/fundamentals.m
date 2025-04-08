
clear 
clc

datafolder = '../../../EGGW Replication/Data';
addpath(datafolder);
%addpath([datafolder,'')
%addpath([datafolder,'/derived')
%%
% Computes the cell-level distribution of amenities and productivity 
% for the years 1990, 1995, 2000 and 2005 based on population, wages 
% and energy data, following the procedure of Supplementary Material 
% Section F.2.
start1=tic;
% Define parameters
lambda = 0.32;     % congestion externalities
gamma1 = 0.319;    % elasticity of tomorrow's productivity w.r.t. today's innovation
gamma2 = 0.99246;  % elasticity of tomorrow's productivity w.r.t. today's productivity
eta = 1;           % parameter driving scale of technology diffusion
mu = 0.8;          % labor share in production
nu = 0.15;         % intercept parameter in innovation cost function   
ksi = 125;         % elasticity of innovation costs w.r.t. innovation
sigma = 4;         % elasticity of substitution
alpha = 0.06;      % elasticity of productivity w.r.t. local population
theta = 6.5;       % trade elasticity
epsilon = 1.6;     % elasticity of substitution between fossil fuels and clean energy
Omega = 0.5;       % taste dispersion
psi_util = 0.045;  % wellbeing parameter

% Load trade costs, land share, population, wages and national demarcations
load([datafolder,'/trmult_reduced.mat'])
load([datafolder,'/H0_areal.mat']) %load('Data/H0_norm.mat')
load([datafolder,'/pop_Gecon.mat'])
load([datafolder,'/wage_Gecon.mat'])
C = csvread([datafolder,'/C.csv']); % national demarcations

% Arrange cells and national demarcations
H = H0(H0>0); % cells with positive land
n = length(H); % number of cells with positive land
C_vect = C(H0>0);
length_C_vect = length(unique(C_vect)); % number of national demarcations

% For each period, transform population and wage from grids of size 180x360 
% to columns of size nx1, where n=17048 is the number of cells with positive land
pop_cell = NaN(n,4);
wage_cell = NaN(n,4);
for t=1:4
    pop_aux = pop(:,:,t);
    pop_cell(:,t) = pop_aux(H0>0);
    wage_aux = wage(:,:,t);
    wage_cell(:,t) = wage_aux(H0>0);
end
wbar = mean(wage_cell(:,3));

% Set energy parameters
tCO2_toe = 2.8466; % conversion factor: GtCO2 per Gtoe
fossil0 = 25.284967/tCO2_toe; % 25.284967 GtCO2 expressed in Gtoe
clean0 = 1.3179; % 1.3179 Gtoe

% Normalize energy prices
GDP0 = sum(wage_cell(:,3).*pop_cell(:,3)); 
price_fossil0_world = 72.99*10^9*tCO2_toe; % 72.99 usd/tCO2 expressed in usd/Gtoe
price_clean0_world = 1.15*76.34*10^9; % 1.15*76.34 usd/toe expressed in usd/Gtoe

% Construct energy parameters
fossil_share = (1+(price_clean0_world/price_fossil0_world)*(clean0/fossil0)^(1/epsilon))^(-1);
price_energy0_world = (fossil_share^epsilon*price_fossil0_world^(1-epsilon) + (1-fossil_share)^epsilon*price_clean0_world^(1-epsilon))^(1/(1-epsilon));
energy0 = (fossil_share*fossil0^((epsilon-1)/epsilon) + (1-fossil_share)*clean0^((epsilon-1)/epsilon))^(epsilon/(epsilon-1));
energy_share = price_energy0_world*energy0*(mu+gamma1/ksi)/GDP0;
chi = 1-energy_share/mu;

% Construct energy use at cell level
load([datafolder,'/CO2_EDGAR.mat']) % cell level CO2 emissions
fossil_country = csvread([datafolder,'/CO2_country.csv']); % country level CO2 emissions in GtCO2
clean_country = csvread([datafolder,'/clean_country.csv']); % country level clean energy use in GtCO2

fossil_cell = zeros(n,4);
clean_cell = zeros(n,4);

for t=1:4
    CO2_EDGAR_cell = CO2_EDGAR(:,:,t);
    CO2_EDGAR_cell = CO2_EDGAR_cell(H0>0);
    for i=1:length_C_vect
        fossil_cell(C_vect==i,t) = CO2_EDGAR_cell(C_vect==i)*fossil_country(i,t)/sum(CO2_EDGAR_cell(C_vect==i));
        clean_cell(C_vect==i,t) = CO2_EDGAR_cell(C_vect==i)*clean_country(i,t)/sum(CO2_EDGAR_cell(C_vect==i));
    end
end

% Compute quantity and price of energy composite
energy_cell = (fossil_share*fossil_cell.^((epsilon-1)/epsilon) + ...
    (1-fossil_share)*clean_cell.^((epsilon-1)/epsilon)).^(epsilon/(epsilon-1));
price_fossil_cell = ((mu*(1-chi)*fossil_share)/(mu+gamma1/ksi))* ...
    ((pop_cell./H)./energy_cell).*(energy_cell./fossil_cell).^(1/epsilon);
price_clean_cell = ((mu*(1-chi)*(1-fossil_share))/(mu+gamma1/ksi))* ...
    ((pop_cell./H)./energy_cell).* (energy_cell./clean_cell).^(1/epsilon);
price_energy_cell = (fossil_share^epsilon*price_fossil_cell.^(1-epsilon) + ...
    (1-fossil_share)^epsilon*price_clean_cell.^(1-epsilon)).^(1/(1-epsilon)); 

% Precompute constants used in the algorithm
denom = 1+2*theta;
squ = alpha-1+(lambda+gamma1/ksi-(1-mu))*theta; % term in square brackets of flat_R and flat_L
flatL = lambda - squ/denom;
flatR = 1 - lambda*theta+(1+theta)*squ/denom;
const_N = wbar^((1+2*theta)/theta);

% Set matrices that will be filled in  
amen_util_H0 = ones(n,4);
prod_H0 = ones(n,4);
realgdp_H0 = zeros(n,4);

% Set numerical parameters
tol_outer = 1e-12; 
tol_inner1 = 1e-15; 
tol_inner2 = 1e-15; 
updatea = 1/2;
updatel = 1/2;
amen_util_i = ones(n,1); % guess of distribution of amenities to utilities in period 0

for i=1:4
    
    pop0 = pop_cell(:,i); % distribution of population in period 0
    w0 = wage_cell(:,i);  % distribution of wages in period 0
    price_energy0 = price_energy_cell(:,i); % distribution of energy prices in period 0
    
    % Define vectors
    step = 0.4;         % epsilon0 in Supplementary Material F.2
    lbar = sum(pop0);   % total population
    
    % Transform population into population per unit of land
    pop0 = pop0 ./ H;
    l_i = pop0;
    
    % Precomputed quantities of equation (75)
    NL = const_N * w0.^(-1) .* pop0.^lambda;
    NR = w0.^(1+theta) .* pop0.^(1-lambda*theta) .* H;
    
    error_outer = 1 + tol_outer;
    while (error_outer >= tol_outer)
        
        step = step/2;
        
        % Solve for ratio of amenities to utilities, equation (75)
        error_inner1 = 1 + tol_inner1; 
        while (error_inner1 >= tol_inner1)
            rhsN = trmult_reduced*(NR.*amen_util_i.^(theta-step));
            amen_util_f = NL .* rhsN.^(-1/theta);
            error_inner1 = sum((amen_util_f-amen_util_i).^2);
            disp(['iteration = ' num2str(i) '; error_outer = ' num2str(error_outer) '; error_inner1 = ' num2str(error_inner1)])
            amen_util_i = updatea*amen_util_f + (1-updatea)*amen_util_i;
        end
        
        % Retrieve productivity, equation (78)
        prod = wbar^(-(1+2*theta)) .* amen_util_i.^theta .* H .* w0.^(1+2*theta) .*...
            pop0.^(-squ) .* price_energy0.^(theta*(1-chi)*mu);
        
        % Given ratio of amenities to utilities and productivity, 
        % solve for population, equation (67)
        LL = amen_util_i.^((1+theta)/(flatL*denom)) .*...
            prod.^(1/(flatL*denom)) .*...
            H.^(-1/(flatL*denom)) .*...
            price_energy0.^(-theta*(1-chi)*mu/(flatL*denom));
        LR = amen_util_i.^((theta^2)/denom) .*...
            prod.^((1+theta)/denom) .*...
            H.^(theta/denom) .*...
            price_energy0.^(-theta*(1+theta)*(1-chi)*mu/denom);
        
        error_inner2 = 1 + tol_inner2; 
        while (error_inner2 >= tol_inner2)
            rhsL = trmult_reduced*(LR.*l_i.^flatR);
            l_f =  LL.*rhsL.^(1/(flatL*theta));
            error_inner2 = sum(((H.*l_i - H.*l_f) / sum(H.*l_f)*lbar ).^2);
            disp(['iteration = ' num2str(i) '; error_outer = ' num2str(error_outer) '; error_inner2 = ' num2str(error_inner2)])            
            l_i = updatel*l_f + (1-updatel)*l_i;
        end
        
        l_i = l_i / sum(H.*l_f) * lbar;	% rescale L so that H*L sum to lbar
        error_outer = sum((H.*l_i - H.*pop0).^2);	
    end
    
    amen_util_H0(:,i) = amen_util_i;
    prod_H0(:,i) = prod;
    realgdp_H0(:,i) = amen_util_i.^(-1).*pop0.^lambda; 
    
end

% Save raito of amenities to utilities, productivities and real GDP
save([datafolder,'/derived/amen_util.mat'],'amen_util_H0','-v7.3');
save([datafolder,'/derived/prod.mat'],'prod_H0','-v7.3');
save([datafolder,'/derived/realgdp.mat'],'realgdp_H0','-v7.3');
Time1=toc(start1);
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Compute migration costs that rationalize population in 2001
start2=tic;
load([datafolder,'/derived/amen_util.mat'])
load([datafolder,'/derived/prod.mat'])
data_table = readtable([datafolder,'/HDI_GDPpc.csv']);

HDI0 = table2array(data_table(1:n,4));
u0 = exp(HDI0.^3./psi_util);
a = amen_util_H0(:,3);
a_norm = a.*u0;

pop1 = (4/5)*pop_cell(:,3)./H+(1/5)*pop_cell(:,4)./H;

avgprod = mean(prod_H0(:,3));
prod1 = eta * prod_H0(:,3).^gamma2 .* avgprod.^(1-gamma2) .* ...
    (gamma1/(nu*(gamma1+mu*ksi)) * pop_cell(:,3)./H).^(gamma1*theta/ksi);

price_energy1 = price_energy_cell(:,3);

% Pre-computed quantities of equation (91)
denom = 1+2*theta;
denom2 = 1+theta;
squ = (alpha-1+(lambda+gamma1/ksi-(1-mu))*theta);

flatL = lambda - squ/denom;
flatR = 1 - lambda*theta+(1+theta)*squ/denom;

% Compute terms outside the integral of equation (91)
ML = a_norm .* ...
    prod1.^(1/denom2) .* ...
    H.^(-Omega-1/denom2) .*...
    pop1.^(-flatL*denom/denom2-Omega) .* ...
    price_energy1.^(-theta*mu*(1-chi)/denom2); 

% Compute terms inside the integral of equation (91)
MR = a_norm.^(theta^2/denom) .* ...
    prod1.^((1+theta)/denom) .*...
    H.^(theta*(1-theta*Omega)/denom) .*...
    pop1.^(flatR-theta^2*Omega/denom) .* ...
    price_energy1.^(-theta*(1+theta)*mu*(1-chi)/denom); 

m2_i = ones(n,1);
tol_m2 = 1e-9;
error_m2 = 1 + tol_m2;
while error_m2 >= tol_m2 
    rhs = trmult_reduced*(MR.*m2_i.^(-theta^2/denom));
    m2_f = ML .* rhs.^(denom/(theta*denom2));
    error_m2 = sum((m2_f-m2_i).^2);
    disp(['error_m2 = ' num2str(error_m2)])
    m2_i = m2_f;
end

% Normalize m2 such that minimum equals one
m2 = m2_i / min(m2_i);
save([datafolder,'/derived/m2.mat'],'m2','-v7.3');
Time2=toc(start2);
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Run model forward 
% (without climate damages and with exogenous population levels and energy prices)
start3=tic;
% Load data
load([datafolder,'/derived/amen_util.mat'])
load([datafolder,'/derived/prod.mat'])
load([datafolder,'/derived/realgdp.mat'])
load([datafolder,'/derived/m2.mat'])

% Exogenous energy prices
price_fossil = zeros(17048,16);
price_clean = zeros(17048,16);
for i=1:17048
    price_fossil(i,:) = interp1(1990:5:2005,price_fossil_cell(i,:),1990:1:2005);
    price_clean(i,:) = interp1(1990:5:2005,price_clean_cell(i,:),1990:1:2005);
end

% Calculate utility
data_table = readtable([datafolder,'/HDI_GDPpc.csv']);
year_table = table2array(data_table(:,1));
HDI_table = table2array(data_table(:,4));
HDI0 = HDI_table(year_table==2000);
u0 = exp(HDI0.^3./psi_util);
a = amen_util_H0(:,1);
a_norm = a.*u0;
prod0 = prod_H0(:,1);
realgdp0 = realgdp_H0(:,1);
popdens = pop_cell(:,1)./H;
lbar_time = interp1(1990:5:2005,sum(pop_cell),1990:1:2005);
lbar_time = lbar_time(2:end);
price_energy = (fossil_share^epsilon*price_fossil.^(1-epsilon) + ...
    (1-fossil_share)^epsilon*price_clean.^(1-epsilon)).^(1/(1-epsilon));
price_energy = price_energy(:,2:end);

% Define number of periods 
T = 2005 - 1990;

% Initialize output variables
l = zeros(n,T);
u = zeros(n,T);
phi = zeros(n,T);
prod = zeros(n,T);

% Simulate the model

% Update productivity from period 0 to period 1 levels according to
% equation (6), assuming Lambda^a = 0 and Lambda^b = 0
avgprod = sum(sum(prod0)) / n;
const_phi = ((gamma1/ksi)/(nu*(mu+gamma1/ksi))).^(1/ksi);
phi0 = const_phi * popdens.^(1/ksi);
prod(:,1) = eta * prod0.^gamma2 .* avgprod.^(1-gamma2) .* phi0.^(gamma1*theta);
amen = repmat(a_norm,1,T);

% Precompute some matrices
denom = 1+2*theta;
squ = (alpha-1+(lambda+gamma1/ksi-(1-mu))*theta);

khi_outer = lambda - squ / denom;
khi_inner = (1-lambda*theta+(1+theta)*squ/denom);

exp_uhat_inner = (khi_inner/Omega - theta^2/denom);
exp_uhat_outer = khi_outer/Omega + (1+theta)/denom;
H_m2_F2 = H.^(-khi_inner+theta/denom) .*...
    m2.^(-khi_inner/Omega); % inside the integral
H_m2_F1 = H.^((khi_outer-1/denom)/exp_uhat_outer) .* ...
    m2.^(khi_outer/(Omega*exp_uhat_outer)); % outside the integral

% Guess for uhat
uhat_loop = ones(n,1); 
tol = 1e-2;

% Outer loop
for t = 1:T    
    
    % Pre-compute auxiliary variables to equation (75)
    F2 = amen(:,t).^(theta^2/denom) .* ...
        prod(:,t).^((1+theta)/denom) .* ...
        price_energy(:,t).^(-theta*(1+theta)*mu*(1-chi)/denom) .* ...
        H_m2_F2; % inside the integral
    F2(isnan(F2)) = 0;

    F1 = amen(:,t).^((1+theta)/(denom*exp_uhat_outer)) .* ...
        prod(:,t).^(1/(denom*exp_uhat_outer)) .* ...
        price_energy(:,t).^(-theta*mu*(1-chi)/(denom*exp_uhat_outer)) .* ...
        H_m2_F1; % outside the integral
    F1(H == 0) = 0;

    % Iterate uhat, equation (75)
    error = tol + 1;
    while error >= tol
        uhat_old = uhat_loop;
        input_integral_inner = F2 .* uhat_loop.^exp_uhat_inner;
        input_integral_inner(uhat_loop == 0) = 0;

        rhs = trmult_reduced*input_integral_inner;

        uhat_loop = F1 .* rhs.^(1/(theta*exp_uhat_outer));
        error = sum((uhat_loop - uhat_old).^2);
        display(['t = ' num2str(t) '; error_uhat = ' num2str(error)]) 
    end
    
    % Solve for population, equation (3), and scale it to add up to lbar_time(t)
    l(:,t) = H.^(-1) .* uhat_loop.^(1/Omega) .* m2.^(-1/Omega);
    l(:,t) = l(:,t) / sum(H.*l(:,t)) * lbar_time(t);
    
    % Calculate innovation, equations (49) and (51)
    phi(:,t) = const_phi * l(:,t).^(1/ksi);

    % Update productivity, equation (6)
    if (t < T)
        avgprod = sum(prod(:,t)) / n;
        prod(:,t+1) = eta * prod(:,t).^gamma2 .* avgprod.^(1-gamma2) .* phi(:,t).^(gamma1*theta);
    end
    
end

% Save results
phi_summ_1990 = phi(:,[5 10 15]);
save([datafolder,'/derived/prod_model_1990.mat'],'phi_summ_1990','-v7.3');
Time3=toc(start3);
%%
start4=tic;
% Load trade costs, land share, population, wages, subnational
% demarcations, real GDP, ratio of amenities to utilities and
% productivity
load([datafolder,'/H0_areal.mat'])
load([datafolder,'/pop_Gecon.mat']) 
load([datafolder,'/wage_Gecon.mat']) 
load([datafolder,'/derived/realgdp.mat'])
load([datafolder,'/derived/amen_util.mat'])
load([datafolder,'/derived/prod.mat'])
% areal_grid = csvread('Data/areal.csv'); % load size of each cell
% dataH0 = load('Data/H0.mat');
% H0_share = dataH0.H0;

data_table = readtable([datafolder,'/HDI_GDPpc.csv']);
year_table = table2array(data_table(:,1));
HDI_table = table2array(data_table(:,4));
HDI = HDI_table(year_table==1990 | year_table==1995 | year_table==2000 | year_table==2005);
u_HDI = exp(HDI.^3./psi_util);

HDI0 = HDI_table(year_table==2000);
unique_HDI0 = unique(HDI0);
length_unique_HDI = length(unique_HDI0);
subcountry = zeros(17048,1);
for i=1:length_unique_HDI
    index = (HDI0 == unique_HDI0(i));
    subcountry(index) = i;
end
subcountry = repmat(subcountry,4,1);

year = kron((1990:5:2005)',ones(17048,1));
aux_lat = repmat((89.5:-1:-89.5)',1,360);
lat = repmat(aux_lat(H0>0),4,1); 
aux_lon = repmat((-179.5:1:179.5),180,1);
lon = repmat(aux_lon(H0>0),4,1);
% areal = repmat(areal_grid(H0>0),4,1);
amen_aux = reshape(amen_util_H0,[17048*4 1]);
amen_HDI = u_HDI.*reshape(amen_util_H0,[17048*4 1]);
prod = reshape(prod_H0,[17048*4 1]);
realgdp_y = reshape(realgdp_H0,[17048*4 1]);
phi_1990 = num2cell([NaN(17048*1,1);reshape(phi_summ_1990,[17048*3 1])]);
phi_1990(cellfun(@isnan,phi_1990)) = {[]};
pop_x = zeros(17048,4);
wage_x = zeros(17048,4);
realgdp_x = zeros(17048,4);
size_cell_x = repmat(H0(H0>0),4,1);
% H0_share_x = repmat(H0_share(H0_share>0),4,1);

size_grid = 2;
length_size_grid = length(size_grid);
grid = NaN(180,360,length_size_grid);

for i=1:length_size_grid
    aux_grid = kron(reshape(1:(180*360)/(size_grid(i)^2),...
        [180/size_grid(i) 360/size_grid(i)]),...
        ones(size_grid(i),size_grid(i)));
    aux_grid(H0==0) = NaN;
    grid(:,:,i) = aux_grid;
end

grid_2c = grid(:,:,1);
grid_2c = repmat(grid_2c(H0>0),4,1);

for y=1:4
    aux_pop = pop(:,:,y);
    pop_x(:,y) = aux_pop(H0>0);
    aux_wage = wage(:,:,y);
    wage_x(:,y) = aux_wage(H0>0);
    realgdp_x(:,y) = realgdp_H0(:,y);
end
pop_x = reshape(pop_x,[17048*4 1]);
wage_x = reshape(wage_x,[17048*4 1]);
realgdp_x = reshape(realgdp_x,[17048*4 1]);

table_amen_prod = table(year,lat,lon,amen_HDI,prod,phi_1990,...
    grid_2c,subcountry,pop_x,wage_x,realgdp_x,size_cell_x);
writetable(table_amen_prod,[datafolder,'/derived/amen_prod.csv']) 
Time4=toc(start4);
%% Profiling
fprintf('\nT1 %f T2 %f T3 %f T4 %f = %f\n',Time1,Time2,Time3,Time4,Time1+Time2+Time3+Time4);
