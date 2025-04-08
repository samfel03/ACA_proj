
function [ l0,u0,uhat0,realgdp0 ] = model_initial_period( m2 )

% Function that estimates population, real GDP and utility of 
% the initial period, consistent with the initial distribution 
% of amenities, productivities and migration costs
% Input: 
%   m2: migration cost function
% Output:
%   l0, u0, uhat0, realgdp0: solution for population, utility, 
%   transformed utility and real GDP

global H theta mu chi alpha lambda gamma1 ksi Omega ...
    prod0 price_energy0 n trmult_reduced lbar a_norm

% Compute parameters
tol = 1e-2;
denom = 1+2*theta;
squ = (alpha-1+(lambda+gamma1/ksi-(1-mu))*theta); % term in square brackets of flat_R and flat_L

flatL = lambda - squ/denom;
flatR = 1 - lambda*theta+(1+theta)*squ/denom;
flat = flatR - theta*flatL;

exp_uhatL = flatL/Omega + (1+theta)/denom;
exp_uhatR = flatR/Omega - theta^2/denom;

% Precompute auxiliary variables to equation (75)
FL_H_m2 = H.^((flatL-1/denom)/exp_uhatL) .* ...
    m2.^(flatL/(Omega*exp_uhatL)); % outside the integral
FR_H_m2 = H.^(-flatR+theta/denom) .*...
    m2.^(-flatR/Omega); % inside the integral

FL = a_norm.^((1+theta)/(denom*exp_uhatL)) .* ...
    prod0.^(1/(denom*exp_uhatL)).*...
    price_energy0.^(-theta*mu*(1-chi)/(denom*exp_uhatL)) .* ...
    FL_H_m2; % outside the integral

FR = a_norm.^(theta^2/denom) .* ...
    prod0.^((1+theta)/denom) .* ...
    price_energy0.^(-theta*(1+theta)*mu*(1-chi)/denom) .* ...
    FR_H_m2; % inside the integral

% Iterate uhat, equation (75)
uhat_i = ones(n,1);  % guess on utility function
error = tol + 1;
while error >= tol
    integral = FR .* uhat_i.^exp_uhatR;
    rhs = trmult_reduced*integral;    
    uhat_f = FL .* rhs.^(1/(theta*exp_uhatL));
    error = sum((uhat_i - uhat_f).^2);
    uhat_i = uhat_f;
%      display(['error_uhat = ' num2str(error)])
end

% Retrieve utility and real GDP, equations (76) and (4)
uhat0 = uhat_f;
l0 = H.^(-1) .* uhat0.^(1/Omega) .* m2.^(-1/Omega);
l0 = l0 * lbar / sum(H.*l0);
u0 = uhat_i * ...
    (lbar/sum(uhat0.^(1/Omega).*m2.^(-1/Omega)))^(flat/theta);
realgdp0 = (u0./a_norm).*l0.^lambda;

end
