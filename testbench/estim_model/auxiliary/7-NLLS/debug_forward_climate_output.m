%% Debug
printmatlist = {'l','prod','realgdp','amen','temp_local','price_emi','price_clean'};
for j=1:length(printmatlist)
    var = printmatlist{j};
    display(var);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PRINT FILES AS BINARY (LIKE MAT FILES)
    % Lossless printing in fast binary files: https://www.mathworks.com/matlabcentral/answers/62037-how-can-i-export-data-from-matlab-to-a-txt-file-without-loosing-precision
    address = [debugfolder,'/',var,'.bin']; % set it as binary file
    eval(strcat('print_bin_2D_to_C(',var,',address);'));
end