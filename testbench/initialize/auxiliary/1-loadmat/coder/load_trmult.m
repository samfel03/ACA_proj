function trmult_reduced = load_trmult(temp)
%Load trmult_reduced 
%   load bilateral costs
%fprintf("In function. ")
%display(filename);
filename= '/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/EGGW Replication/Data/trmult_reduced.mat';
data_trmult = load(filename);
trmult_reduced = data_trmult.trmult_reduced;
end