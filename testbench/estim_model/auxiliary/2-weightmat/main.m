clear
clc
close all

length_ISO = 3;                                                 % 168
anni = 2;                                                       % 51 = 2000-1950+1
pop_data = [1 2 3 4 5 6]';                                      % 8568x1 NDATAx1    
pop_data_resh = reshape(pop_data,[anni  length_ISO]);           % 51 x 168
%{
  1     3     5
  2     4     6
%}
pop_tot_data = repmat(sum(pop_data_resh,2),length_ISO,1);       % 8568x1 NDATAx1    
%{
     9
    12
     9
    12
     9
    12
%}
weight_pop_data = pop_data./pop_tot_data;                       % 8568x1 NDATAx1    
%{
    0.111111111111111
   0.166666666666667
   0.333333333333333
   0.333333333333333
   0.555555555555556
   0.500000000000000
%}
diag(weight_pop_data)
%{
   0.111111111111111                   0                   0                   0                   0                   0
                   0   0.166666666666667                   0                   0                   0                   0
                   0                   0   0.333333333333333                   0                   0                   0
                   0                   0                   0   0.333333333333333                   0                   0
                   0                   0                   0                   0   0.555555555555556                   0
                   0                   0                   0                   0                   0   0.500000000000000
%}
linspace(1,1,(anni))'
%{
    1
     1
%}
ones(length_ISO,1)
%{
     1
     1
     1
%}
kron(linspace(1,1,(anni))',ones(length_ISO,1))
%{
    1
     1
     1
     1
     1
     1
%}
diag(kron(linspace(1,1,(anni))',ones(length_ISO,1)))
%{
     1     0     0     0     0     0
     0     1     0     0     0     0
     0     0     1     0     0     0
     0     0     0     1     0     0
     0     0     0     0     1     0
     0     0     0     0     0     1
%}
weight_pop_matrix = diag(weight_pop_data).*diag(kron(linspace(1,1,(anni))',ones(length_ISO,1)));        % NDATAxNDATA
%{
   0.111111111111111                   0                   0                   0                   0                   0
                   0   0.166666666666667                   0                   0                   0                   0
                   0                   0   0.333333333333333                   0                   0                   0
                   0                   0                   0   0.333333333333333                   0                   0
                   0                   0                   0                   0   0.555555555555556                   0
                   0                   0                   0                   0                   0   0.500000000000000
%}


%% CODICE MATLAB TO C
sum = zeros(anni,1);
offset = 1;
for t=1:anni
    offset = offset + (t-1);
    for i=1:length_ISO
        indice = (i-1)*anni+offset
        sum(t)=sum(t)+pop_data(indice);
    end
    for i=1:length_ISO
        indice = (i-1)*anni+offset;
        pop_data2(indice)=pop_data(indice)/sum(t);
    end
end

isequal(pop_data2',weight_pop_data);


%{
for i=1:length_ISO
    for t=1:anni

        pop_data2(i)=pop_data(i)/sum(t);
    end
%}
