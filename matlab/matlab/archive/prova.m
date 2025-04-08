tic
start=tic;
for i=1:1000
display(i);
end 
var=toc(start);

start2= tic;
for i=1:1000
display(i);
end 
var2 = toc(start2);
var3 = toc(start)
fprintf("%f, %f, %f",var,var2,var3);

