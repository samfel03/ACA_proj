function print_bin_2D_to_C(X,address)
%PRINT 2D array for C
fid = fopen(address, 'w');
Xprime = X';                  % Transpose Matrix (do not transpose since indexes are transposed for speed in C)
Xvec=reshape(X,[],1)';
fwrite(fid,Xvec,'double');
fclose(fid);

end