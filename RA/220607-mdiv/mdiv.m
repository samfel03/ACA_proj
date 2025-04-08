clc
clearvars
close all

A_FILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\3-rcond\AINPUT";
B_FILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\3-rcond\BINPUT";
OUTPUT_FILE="C:\Users\Joongsan\source\repos\AleP83\CCE-C\testbench\estim_model\auxiliary\3-rcond\moutput";
run_cnt=10;
difference=zeros(1,10);
per_diff=zeros(1,10);
n=8;
stored_result=zeros(n,run_cnt);
for i = 0:run_cnt-1
    A=randn(n,n);
    b=randn(n,1);
    stored_result(:,i+1) = call_mdiv(A,b);
    print_bin_2D_to_C(A,A_FILE+num2str(i)+".bin");
    print_bin_2D_to_C(b,B_FILE+num2str(i)+".bin");
end

input('Wait!\n','s');

for i = 0:run_cnt-1
    fid = fopen(OUTPUT_FILE+num2str(i)+".bin", 'r');
    compare_value=fread(fid,n,'double')
    fclose(fid);
    
    x=stored_result(:,i+1)
    if(compare_value==x)
        difference(i+1)=0;
        per_diff(i+1)=0;
    else
        current=abs(compare_value-x);
        difference(i+1)=max(current);
        current=100*abs((compare_value-x)./x);
        per_diff(i+1)=max(current);
    end

end
disp('percentage difference result:')
max(per_diff)
disp('difference result:')
max(difference)