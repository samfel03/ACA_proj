function X=read_bin_2D_from_C(address,row,col)
%READ 2D array for C
SIZE_vec=row*col;
fid = fopen(address, 'r');
Xvec2=fread(fid,SIZE_vec,'double');
fclose(fid);
Xprime=reshape(Xvec2,col,row);
X = Xprime';
end