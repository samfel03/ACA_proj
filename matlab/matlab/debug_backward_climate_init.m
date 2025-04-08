global outputfolder

%% Compare C and Matlab Vectors
readveclist = {'m2'}; % 'price_clean0_world' excluded
for j=1:length(readveclist)
    var = readveclist{j};
    display(var);
    % Read Matlab Vector
    address = [outputfolder,'/bwd_',var,'_i.bin']; % set it as binary file
    fprintf("Reading variable %s in: %s2\n",address,var);
    fid = fopen(address, 'r');
    eval(strcat(var,'2=fread(fid, size(',var,'),''double'');')); % H2 = fread(fid, 1, 'double);
    fclose(fid);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
end
assert(sum(diff)==0); %% Vector of differences between variables is zero

%% Compare C and Matlab Matrixes
% Matrix List
readmatlist = {'temp_past','theta_amen_temp'};
for j=1:length(readmatlist)
    var = readmatlist{j};
    display(var);
    % Read Matlab Vector
    address = [outputfolder,'/bwd_',var,'.bin']; % set it as binary file
    eval(strcat('[row,col]=size(',var,');'));
    eval(strcat(var,'2=read_bin_2D_from_C(address,row,col);')); % H2 =read_bin_2D_from_C(address,row,col);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
    clearvars row col
end
assert(sum(abs(diff))<1e-10); %% Vector of differences between variables is zero