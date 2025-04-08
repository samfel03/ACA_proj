clear
clc
close all

datafolder='/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/EGGW Replication/Data';
data_trmult = load([datafolder,'/trmult_reduced.mat']);
trmult_reduced = data_trmult.trmult_reduced;

%% Check differences (eye-ball)
format long
trmult_reduced(212802)-9.94186765750552279732486754275407069e-22
trmult_reduced(107143)-2.62938115611165667230308192586088138e-20