clear
clc
close all

%% 1. Set economic parameters
global theta alpha lambda gamma1 ksi mu Omega chi H trmult_reduced 

%% Initializations
theta = 6.5;            % variance productivity shocks
lambda = 0.32;          % congestion externalities
gamma1 = 0.319;         % elasticity of tomorrow's productivity relative to today's innovation
mu = 0.8;               % labor share in production
ksi = 125;              % elasticity of innovation costs relative to innovation
alpha = 0.06;           % agglomeration externalities
Omega = 0.5;            % variance taste shocks

%% Fake initializations
n=10;
chi = 4.;
trmult_reduced=ones(n,n);
H = ones(n,1);
m2_i=max(randn(n,1),0);
amen=max(randn(n,1),0);
prod=max(randn(n,1),0);
pop=max(randn(n,1),0);
price_energy=max(randn(n,1),0);
tol_m2=1e-6;
m2_f=ones(n,1);

%% Lunch function
m2_f=migration_costs(m2_i,amen,prod,pop,price_energy,tol_m2);

