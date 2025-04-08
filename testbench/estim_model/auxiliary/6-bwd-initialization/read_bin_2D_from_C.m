function X=read_bin_2D_from_C(address,row,col)
%READ 2D array for C
SIZE_vec=row*col;
fid = fopen(address, 'r');
Xvec2=fread(fid,SIZE_vec,'double');
fclose(fid);
if(col>=row)
    Xprime=reshape(Xvec2,col,row);
    X = Xprime';
else
    X=reshape(Xvec2,row,col);
end
end