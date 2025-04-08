function [minimum,maximum,totSize] = stats_var(x)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
format long
%[row,col]=size(x)
minimum=min(x);
maximum=max(x);

%{
props = properties(x);
totSize = 0;
for ii=1:length(props)
    currentProperty = getfield(x, char(props(ii)));
    s = whos('currentProperty');
    totSize = totSize + s.bytes;
end
%}

end
