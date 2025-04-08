function print_bin_2D(X,address)
%PRINT 2D array for C
fid = fopen(address, 'w');
fwrite(fid,X,'double');
fclose(fid);
size(X);
end