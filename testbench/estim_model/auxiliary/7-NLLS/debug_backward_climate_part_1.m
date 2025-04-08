global outputfolder

%% Compare C and Matlab Vectors
l20_model = l20;
realgdp20_model= realgdp20;
temp20_local=temp20;

readveclist = {'l0_model','realgdp0_model','l20_model','realgdp20_model','temp20_local'}; % ,'weight_pop_matrix'
for j=1:length(readveclist)
    var = readveclist{j};
    display(var);
    % Read Matlab Vector
    address = [outputfolder,'/bwd_',var,'.bin']; % set it as binary file
    fprintf("Reading variable %s in: %s2\n",address,var);
    fid = fopen(address, 'r');
    eval(strcat(var,'2=fread(fid, size(',var,'),''double'');')); % H2 = fread(fid, 1, 'double);
    fclose(fid);
    eval(strcat('diff_',var,' = ',var,'-',var,'2;'));
    eval(strcat('diff(',(num2str(j)),')=max(max(diff_',var,',[],2),[],1);'));
    eval(strcat('diff_sum(',(num2str(j)),')=sum(diff_',var,');'));
end

fprintf("\n Differences across all variables: %.19f",sum(diff,'all')); %% Vector of differences between variables is zero
clearvars l20_model realgdp20_model temp20_local diff

