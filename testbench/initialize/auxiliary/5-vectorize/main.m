clear
clc
close all
% Printing matrix for C: https://www.mathworks.com/matlabcentral/answers/332207-write-matrix-with-matlab-and-read-with-c 
% If you are writing and reading a 2D matrix, then be advised that:
% - MATLAB stores such data column-wise, 
% - whereas C stores such data row-wise. 
% That is, if you have a 2D C array like "double x[3][4]", then it will be stored in memory by rows. Whereas if a variable is size 3x4 in MATLAB, it will be stored in memory by columns.
% Bottom line is if you want to read the data in C by rows, you should write it out that way from MATLAB. 
% Fortunately this is easy to do. Simply transpose the matrix first, and then write that transposed matrix out to the file via the above code
rng(1);
A = [1.2,2.2;3.2,4.2;5.2,6.2;7.2,8.2]
fprintf("%lf %lf \n %lf %lf\n %lf %lf \n %lf %lf\n",A(1,1),A(1,2),A(2,1),A(2,2),A(3,1),A(3,2),A(4,1),A(4,2));
address = "A.bin";
%% Print 2D to C (in C format)
print_bin_2D_to_C(A,address);
[row,col]=size(A);
A2=read_bin_2D_from_C(address,row,col);
diff=sum(sum((A-A2),1),2);
assert(diff==0);
%% Print 2D (NOT USED)
%{
print_bin_2D(A,address);
[row,col]=size(A);
A2=read_bin_2D(address,row,col);
diff=sum(sum((A-A2),1),2);
assert(diff==0);
%}