global outputfolder debugfolder

%% Save Matlab Files for Debugging 
save('/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/estim_model/auxiliary/7-NLLS/data/bwd_output.mat','l_b','realgdp_b','emiCO2_b','temp_b','clean_b','-v7.3');
    
isequal(temp_b,temp_past)

%% Compare with C (on Hold)
readmatlist = {'l_b','realgdp_b','emiCO2_b','clean_b'};
for j=1:length(readmatlist)
    var = readmatlist{j};
    display(var);
    % Read Matlab Vector
    address = [outputfolder,'/bwd_sym_',var,'.bin']; % set it as binary file
    eval(strcat('[row,col]=size(',var,');'));
    eval(strcat(var,'2=read_bin_2D_from_C(address,row,col);')); % H2 =read_bin_2D_from_C(address,row,col);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
    clearvars row col
end
diff
clearvars diff

%% Debug
printmatlist = {'l_b','realgdp_b','emiCO2_b','clean_b'};
for j=1:length(printmatlist)
    var = printmatlist{j};
    display(var);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PRINT FILES AS BINARY (LIKE MAT FILES)
    % Lossless printing in fast binary files: https://www.mathworks.com/matlabcentral/answers/62037-how-can-i-export-data-from-matlab-to-a-txt-file-without-loosing-precision
    address = [debugfolder,'/',var,'.bin']; % set it as binary file
    eval(strcat('print_bin_2D_to_C(',var,',address);'));
end
