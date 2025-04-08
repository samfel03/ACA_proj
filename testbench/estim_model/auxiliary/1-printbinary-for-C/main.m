clear
clc
close all
A = [1.2,2.2;3.2,4.2;5.2,6.2;7.2,8.2]
fprintf("%lf %lf \n %lf %lf\n %lf %lf \n %lf %lf\n",A(1,1),A(1,2),A(2,1),A(2,2),A(3,1),A(3,2),A(4,1),A(4,2));
address = "A.bin";
%% Print 2D to C (in C format)
print_bin_2D_to_C(A,address);
[row,col]=size(A);
A2=read_bin_2D_from_C(address,row,col);
diff=sum(sum((A-A2),1),2);
assert(diff==0);

%{
%}