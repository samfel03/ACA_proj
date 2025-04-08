clear
clc
close all

%trmult_reduced = [3,2,1;7,8,9];
%save '/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/initialize/auxiliary/1-loadmat/test/tmrult_reduced.mat' trmult_reduced
data_trmult = load('/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/EGGW Replication/Data/trmult_reduced.mat');
trmult_reduced = data_trmult.trmult_reduced;
save('/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/initialize/auxiliary/1-loadmat/test/tmrult_reduced.txt', 'trmult_reduced', '-ascii');