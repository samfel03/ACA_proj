clear
clc
close all


% Generate Random Matrix
n = 8568;
X= ones(n,n);
% Compute Rcond in Matlab
Y = call_rcond(X);

% Print Random Matrix to C using print_bin_2D_to_C

% Comput rcond in C

% Verify they are equivalent


