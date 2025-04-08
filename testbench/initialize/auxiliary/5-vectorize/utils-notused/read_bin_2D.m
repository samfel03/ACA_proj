function X=read_bin_2D(address,row,col)
%READ 2D array
fid = fopen(address, 'r');
X=fread(fid,[row,col],'double');
size(X);
end