%% Debug
printveclist  = {'coeff_pop_i'}; 
for j=1:length(printveclist)
    var = printveclist{j};
    display(var);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PRINT FILES AS BINARY (LIKE MAT FILES)
    % Lossless printing in fast binary files: https://www.mathworks.com/matlabcentral/answers/62037-how-can-i-export-data-from-matlab-to-a-txt-file-without-loosing-precision
    address = [debugfolder,'/',var,'.bin']; % set it as binary file
    fprintf("Printing variable %s in: %s\n",var,address);
    fid = fopen(address, 'w');
    eval(strcat('fwrite(fid,', var,', ''double'');'));
    fclose(fid);
end
