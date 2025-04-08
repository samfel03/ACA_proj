function print_bin_2D_to_C(X,address)
%PRINT 2D array for C
fid = fopen(address, 'w');
[row,col]=size(X);    
if(col>=row)
    Xprime = X';                  % other matrixes
    Xvec=reshape(Xprime,[],1)';
else
    Xvec=reshape(X,1,[])';         % temp_past, Delta_temp
end
fwrite(fid,Xvec,'double');
fclose(fid);

end