function [ret] = natal_fct(logrealgdp_c,temp_c,logrealgdp_w,coeff_pop)
%NATAL_FCT 이 함수의 요약 설명 위치
%   자세한 설명 위치

length_C_vect=168;
ret = zeros(length_C_vect,1);

for i=1:length_C_vect

ret(i)=logrealgdp_c(i)+i-1+logrealgdp_w+coeff_pop(rem(i-1,8)+1);


disp(logrealgdp_c(i)+i-1+logrealgdp_w)
disp(coeff_pop(rem(i-1,8)+1))
end