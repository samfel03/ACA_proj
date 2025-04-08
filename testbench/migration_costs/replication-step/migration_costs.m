%#codegen
function [m2_f] = migration_costs( m2_i,amen,prod,pop,price_energy,tol_m2 )

% Function that computes the migration costs, as displayed in 
% Supplementary Materials Section F.5
% Inputs:
%   m2_i: guess for the migration cost function
%   amen, prod, pop, price_emi: cell-level amenities, productivity, 
%   population to be matched andenergy price.
%   tol_m2: tolerance for the error
% Output:
%   m2_f: solution for the migration cost function
    
global theta;
global chi;
global mu;
global alpha;
global lambda;
global gamma1;
global ksi;
global Omega;
global trmult_reduced;
global H;

% Pre-computed quantities
denom = 1+2*theta;
denom2 = 1+theta;
squ = (alpha-1+(lambda+gamma1/ksi-(1-mu))*theta);

flatL = lambda - squ/denom;
flatR = 1 - lambda*theta+(1+theta)*squ/denom;

% Compute terms outside the integral of equation (91)
ML = amen .* ...
    prod.^(1/denom2) .* ...
    H.^(-Omega-1/denom2) .*...
    pop.^(-flatL*denom/denom2-Omega) .* ...
    price_energy.^(-theta*mu*(1-chi)/denom2); 

% Compute terms inside the integral of equation (91)
MR = amen.^(theta^2/denom) .* ...
    prod.^((1+theta)/denom) .*...
    H.^(theta*(1-theta*Omega)/denom) .*...
    pop.^(flatR-theta^2*Omega/denom) .* ...
    price_energy.^(-theta*(1+theta)*mu*(1-chi)/denom); 

error_m2 = 1 + tol_m2;
while error_m2 >= tol_m2 
    rhs = trmult_reduced*(MR.*m2_i.^(-theta^2/denom));
    m2_f = ML .* rhs.^(denom/(theta*denom2));
    error_m2 = sum((m2_f-m2_i).^2);
    m2_i = m2_f;
end

% Normalize m2 such that minimum equals one
m2_f = m2_i / min(m2_i);

end
