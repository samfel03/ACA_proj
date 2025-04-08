%%
long format



%% Debug 
l(1,t)
l(end,t)
realgdp(1,t)
realgdp(end,t)
ltilde1
ltilde
realgdp(1,t)
realgdp(end,t)

%{
print l_vec[0]
print l_vec[17047]
print realgdp[0]
print realgdp[17047]
print ltilde1
print ltilde
print sym_->realgdp_b[(t)*17048 + 0]
print sym_->realgdp_b[(t)*17048 + 17047]
%}

%% t=2
realgdp(1,1)
realgdp(2,1)


amen(1)
amen(end)
prod_next(1)
prod_next(end)

%{
print sym_->realgdp_b[(t)*17048 + 0]
print sym_->realgdp_b[(t)*17048 + 17047]
%}


%% 
realgdp(1:5,1)
realgdp(1:5,end)
