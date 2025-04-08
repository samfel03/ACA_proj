%% Study trmult_reduced

% Stats
tr_.NPOSLAND=17048;
tr_.max = max(max(trmult_reduced,[],2),[],1);
tr_.min = min(min(trmult_reduced,[],2),[],1);
tr_.min_max = min(max(trmult_reduced,[],2),[],1); 
tr_.N = sum(trmult_reduced>0,'all');
tr_.N_greater_min_max = sum(trmult_reduced>tr_.min_max,'all');
tr_.sh_greater_min_max = tr_.N_greater_min_max/tr_.N;
tr_.threshold = 1e-11;                                          % *****************
tr_.N_threshold= sum(trmult_reduced>tr_.threshold,'all');
tr_.average_links=tr_.N_threshold/tr_.NPOSLAND;
tr_.sh_threshold = tr_.N_threshold/tr_.N;
tr_.sh_threshold = tr_.N_threshold/tr_.N;
tr_.MB_N_threshold=tr_.N_threshold*8/1000000;

assert(tr_.N==tr_.NPOSLAND*tr_.NPOSLAND); % All positive
tr_



sum(trmult_reduced>1e-15,'all')-sum(trmult_reduced(end,:)>1e-15)
