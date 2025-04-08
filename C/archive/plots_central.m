    
function [ amen_w_ratio, prod_w_ratio, ...
    realgdp_w_ratio, util_w_ratio, ...
    PDV_realgdp_ratio, PDV_util_ratio, ...
    emiCO2_total_factual, emiCO2_total_counterfact, ...
    clean_total_factual, clean_total_counterfact, ...
    temp_global_factual, temp_global_counterfact, ...
    BGP_realgdp_w_factual, BGP_realgdp_w_counterfact, ...
    BGP_util_w_factual, BGP_util_w_counterfact, lbar_total_factual ] = ...
    plots_central( nbins, ind_dam, ind_type, name_adap, ...
    taxCO2_val, subclean_val, name_abat, ...
    eps, maxCO2, beta, ind_plot )

// Function that generates the maps and figures of the baseline 
// scenario of Function that generates the maps and figures of Sections 4 and 6, 
// Appendix E.1 and Supplementary Materials Sections G.1-G.3, H.1 and J.1.
// Inputs:
//	nbins: number of bins of the histograms
//	ind_dam: level of the damage function, with values from 1 to 9
//	ind_type: source of damages, 0 indicates no damages, 1 damages on both 
//   amenities and productivities, 2  damages only on amenities, 
//   and 3 damages only on productivities
//	name_adap: degree of adaptation
//	taxCO2_val: value of taxes on CO2
//	subclean_val: value of subsidies on clean energy
//	name_abat: level of abatement
//	eps: elasticity of substitution between fossil fuels and clean energy
//	maxCO2: total stock of CO2 available in the ground
//	beta: value of the discount factor
//	ind_plot: dummy variable so that when 1 plots all the maps and figures
// Outputs:
//   amen_w_ratio, prod_w_ratio, realgdp_w_ratio, util_w_ratio: 
//   global amenities, productivity, real GDP and utility relative 
//   to the counterfactual scenario, for every period of the simulation
//   PDV_realgdp_ratio, PDV_util_ratio: cell-level PDV of real GDP 
//   and welfare relative to the counterfactual scenario
//   emiCO2_total_factual, emiCO2_total_counterfact, clean_total_factual, 
//   clean_total_counterfact, temp_global_factual, temp_global_counterfact: 
//   global CO2 emissions, temperature and clean energy use in the 
//   factual and counterfactual scenarios
//   BGP_realgdp_w_factual, BGP_realgdp_w_counterfact, BGP_util_w_factual, 
//   BGP_util_w_counterfact: Balanced Growth Path (BGP) growth rate of 
//   real GDP and utility in the factual and counterfactual scenarios
//   lbar_total_factual: global population in the factual scenario

global temp0_local H H0 n pop0_dens prod0 a_norm lambda C_vect...
    tCO2_toe fossil0_cell clean0_cell...
    emiCO2_RCP stockCO2_RCP temp_preind temp_global_RCP...
    lbar pop_low95 pop_low80 pop_med pop_high95 pop_high80 map ... 
    name_dam_vect color_darkcyan color_darkgreen color_yellowgreen color_olive...
	name_type_vect name_long_type_vect name_maps_type_vect...
    price_fossil0 price_clean0 price_clean0_world conv_usd areal...
    zeta_fossil0 zeta_clean0 fossil_share epsilon...
    emi0_ff emi_no_ff mu chi gamma1 ksi cost_emi_param

// Set names
name_dam = name_dam_vect{ind_dam};
name_type = name_type_vect{ind_type};
name_long_type = name_long_type_vect{ind_type};
name_maps_type = name_maps_type_vect{ind_type};
name_app = '';
if maxCO2 ~= 19500
    name_app = ['_maxCO2' num2str(maxCO2)];
end
if eps ~= 1.6
    name_app = ['_eps' num2str(eps)];
end

// Load forward results
if taxCO2_val == 0 && subclean_val == 0 

factual = load(['Data/derived/results_forward_' name_type '_' name_dam name_adap name_app '.mat']);
l_factual = factual.l_Warm;
util_factual = factual.u_Warm;
prod_factual = factual.prod_Warm;
realgdp_factual = factual.realgdp_Warm;
amen_factual = factual.amen_Warm;
emiCO2_total_factual = factual.emiCO2_total_Warm;
temp_global_factual = factual.temp_global_Warm;
if ind_plot == 1 && ind_dam == 9 && ind_type == 1
stockCO2_factual = factual.stockCO2_Warm;
temp_local_factual = factual.temp_local_Warm;
emiCO2_factual = factual.emiCO2_ff_Warm;
clean_factual = factual.clean_Warm;
net_births_factual = factual.net_births_Warm;
end

counterfact = load(['Data/derived/results_forward_noWarm' name_adap name_app '.mat']);
l_counterfact = counterfact.l_noWarm;
util_counterfact = counterfact.u_noWarm;
prod_counterfact = counterfact.prod_noWarm;
realgdp_counterfact = counterfact.realgdp_noWarm;
amen_counterfact = counterfact.amen_noWarm;
emiCO2_total_counterfact = counterfact.emiCO2_total_noWarm;
temp_global_counterfact = counterfact.temp_global_noWarm;
if ind_plot == 1
stockCO2_counterfact = counterfact.stockCO2_noWarm;
temp_local_counterfact = counterfact.temp_local_noWarm;
emiCO2_counterfact = counterfact.emiCO2_ff_noWarm;
clean_counterfact = counterfact.clean_noWarm;
end

else
    
if strcmp(name_abat,'') == 1 
factual = load(['Data/derived/results_forward_' name_type '_' name_dam '_tax' num2str(100*taxCO2_val) '_sub' num2str(100*subclean_val) name_abat name_app '.mat']);    
else
if strcmp(name_abat(end-2:end),'all') == 1
factual = load(['Data/derived/results_forward_' name_type '_' name_dam '_tax' num2str(100*taxCO2_val) '_sub' num2str(100*subclean_val) name_abat(1:end-4) name_app '.mat']);
else
factual = load(['Data/derived/results_forward_' name_type '_' name_dam '_tax' num2str(100*taxCO2_val) '_sub' num2str(100*subclean_val) name_abat name_app '.mat']);    
end
end
l_factual = factual.l_Warm;
util_factual = factual.u_Warm;
prod_factual = factual.prod_Warm;
realgdp_factual = factual.realgdp_Warm;
amen_factual = factual.amen_Warm;
emiCO2_total_factual = factual.emiCO2_total_Warm;
temp_global_factual = factual.temp_global_Warm;
if ind_plot == 1 && ind_dam == 9 && ind_type == 1
stockCO2_factual = factual.stockCO2_Warm;
temp_local_factual = factual.temp_local_Warm;
emiCO2_factual = factual.emiCO2_ff_Warm;
clean_factual = factual.clean_Warm;
end

if strcmp(name_abat,'') == 1 
counterfact = load(['Data/derived/results_forward_' name_type '_' name_dam name_abat name_app '.mat']);    
else
if strcmp(name_abat(end-2:end),'all') == 1
counterfact = load(['Data/derived/results_forward_' name_type '_' name_dam name_app '.mat']);
else
counterfact = load(['Data/derived/results_forward_' name_type '_' name_dam name_abat name_app '.mat']);    
end
end
l_counterfact = counterfact.l_Warm;
util_counterfact = counterfact.u_Warm;
prod_counterfact = counterfact.prod_Warm;
realgdp_counterfact = counterfact.realgdp_Warm;
amen_counterfact = counterfact.amen_Warm;
if strcmp(name_abat,'') == 1 
emiCO2_total_counterfact = counterfact.emiCO2_total_Warm;
temp_global_counterfact = counterfact.temp_global_Warm;
else
if strcmp(name_abat(end-2:end),'all') == 1
counterfact_aux = load(['Data/derived/results_forward_' name_type '_' name_dam name_abat(1:end-4) name_app '.mat']);
emiCO2_total_counterfact = counterfact_aux.emiCO2_total_Warm;
temp_global_counterfact = counterfact_aux.temp_global_Warm;
else
emiCO2_total_counterfact = counterfact.emiCO2_total_Warm;
temp_global_counterfact = counterfact.temp_global_Warm;
end
end
if ind_plot == 1 && ind_dam == 9 && ind_type == 1
stockCO2_counterfact = counterfact.stockCO2_Warm;
temp_local_counterfact = counterfact.temp_local_Warm;
emiCO2_counterfact = counterfact.emiCO2_ff_Warm;
clean_counterfact = counterfact.clean_Warm;
end

end

T = length(temp_global_factual);
HT = repmat(H,1,T);
pop_sh = cat(3,l_factual.*HT./repmat(sum(l_factual.*HT),n,1),l_counterfact.*HT./repmat(sum(l_counterfact.*HT),n,1));
pop0_sh = pop0_dens.*H/lbar;
beta_matrix = beta.^repmat(0:1:T-1,n,1);

if ind_plot == 1 && ind_dam == 9 && ind_type == 1
    clean_total_factual = sum(clean_factual.*HT)';
    clean_total_counterfact = sum(clean_counterfact.*HT)';
else
    clean_total_factual = zeros(T,1);
    clean_total_counterfact = zeros(T,1);
end

lbar_total_factual = sum(l_factual.*HT)';
lbar_total_counterfact = sum(l_counterfact.*HT)';

data20 = load('Data/derived/results20_med.mat');
l0 = data20.l0_model;
realgdp0 = data20.realgdp0_model;
u0 = a_norm.*realgdp0.*l0.^(-lambda);

oecd_list = [7 8 13 27 31 33 36 40 42 50 54 55 58 60 69 70 74 75 ...
    76 78 86 90 100 108 109 113 121 122 133 134 137 138 ...
    146 147 156 160 161];
ssa_list = [3 15 19 23 24 26 28 29 30 34 35 37 41 48 49 145 51 56 57 59 64 ...
    65 81 88 89 92 93 96 98 99 104 106 111 112 125 128 130 131 136 143 150 ...
    152 157 168 214];
se_asia_list = [11 21 25 71 72 85 94 105 117 120 132 151 166];

// Arrange matrices
pop_matrix = cat(3,l_factual,l_counterfact);
util_matrix = cat(3,util_factual,util_counterfact);
prod_matrix = cat(3,prod_factual,prod_counterfact);
realgdp_matrix = cat(3,realgdp_factual,realgdp_counterfact);
amen_matrix = cat(3,amen_factual,amen_counterfact);
if ind_plot == 1 && ind_dam == 9 && ind_type == 1
temp_local_matrix = cat(3,temp_local_factual,temp_local_counterfact);
emiCO2_matrix = cat(3,emiCO2_factual,emiCO2_counterfact);
clean_matrix = cat(3,clean_factual,clean_counterfact);
end

// Pre-allocate some matrices of size (lat x lon x years x Warm/noWarm)
PDV_realgdp_matrix = NaN(n,2);
PDV_util_matrix = NaN(n,2);
PDV_realgdp_grid = NaN(180,360,2);
PDV_util_grid = NaN(180,360,2);
BGP_realgdp_w = NaN(2,1);
BGP_util_w = NaN(2,1);

if ind_plot == 1
temp_local_grid = NaN(180,360,T+1,2); 
amen_grid = NaN(180,360,T+1,2);
prod_grid = NaN(180,360,T+1,2);
util_grid = NaN(180,360,T+1,2);
realgdp_grid = NaN(180,360,T+1,2);
pop_grid = NaN(180,360,T+1,2);
emiCO2_grid = NaN(180,360,T+1,2);
clean_grid = NaN(180,360,T+1,2);

hist_amen = NaN(nbins,T+1);
interv_amen = NaN(nbins,T+1);
std_amen = NaN(T+1,1);

hist_prod = NaN(nbins,T+1);
interv_prod = NaN(nbins,T+1);
std_prod = NaN(T+1,1);

hist_realgdp = NaN(nbins,T+1);
interv_realgdp = NaN(nbins,T+1);
std_realgdp = NaN(T+1,1);

hist_util = NaN(nbins,T+1);
interv_util = NaN(nbins,T+1);
std_util = NaN(T+1,1);

// Arrange data in grid format
if ind_dam == 9 && ind_type == 1
temp_local_aux = temp_local_grid(:,:,1);
temp_local_aux(H0>0) = temp0_local;
temp_local_grid(:,:,1,:) = repmat(temp_local_aux,1,1,1,2);
end

amen_aux = amen_grid(:,:,1);
amen_aux(H0>0) = a_norm;
amen_grid(:,:,1,:) = repmat(amen_aux,1,1,1,2);

[hist_amen(:,1), interv_amen(:,1)] = ...
    histwc(ones(n,1), pop0_sh, nbins);
std_amen(1) = sqrt(sum(pop0_sh.*((ones(n,1)-sum(ones(n,1).*pop0_sh)).^2)));

prod_aux = prod_grid(:,:,1);
prod_aux(H0>0) = prod0;
prod_grid(:,:,1,:) = repmat(prod_aux,1,1,1,2);

[hist_prod(:,1), interv_prod(:,1)] = ...
    histwc(ones(n,1), pop0_sh, nbins);
std_prod(1) = sqrt(sum(pop0_sh.*((ones(n,1)-sum(ones(n,1).*pop0_sh)).^2)));

realgdp_aux = realgdp_grid(:,:,1);
realgdp_aux(H0>0) = realgdp0;
realgdp_grid(:,:,1,:) = repmat(realgdp_aux,1,1,1,2);

[hist_realgdp(:,1), interv_realgdp(:,1)] = ...
    histwc(ones(n,1), pop0_sh, nbins);
std_realgdp(1) = sqrt(sum(pop0_sh.*((ones(n,1)-sum(ones(n,1).*pop0_sh)).^2)));

util_aux = util_grid(:,:,1);
util_aux(H0>0) = u0; 
util_grid(:,:,1,:) = repmat(util_aux,1,1,1,2);

[hist_util(:,1), interv_util(:,1)] = ...
    histwc(ones(n,1), pop0_sh, nbins);
std_util(1) = sqrt(sum(pop0_sh.*((ones(n,1)-sum(ones(n,1).*pop0_sh)).^2)));
 
pop_aux = pop_grid(:,:,1);
pop_aux(H0>0) = pop0_sh;
pop_grid(:,:,1,:) = repmat(pop_aux,1,1,1,2);

if ind_dam == 9 && ind_type == 1
emiCO2_aux = NaN(180,360);
emiCO2_aux(H0>0) = tCO2_toe*fossil0_cell;
emiCO2_grid(:,:,1,:) = repmat(emiCO2_aux,1,1,1,2);

clean_aux = NaN(180,360);
clean_aux(H0>0) = tCO2_toe*clean0_cell;
clean_grid(:,:,1,:) = repmat(clean_aux,1,1,1,2);
end

for t=2:T+1 
    for i=1:2
        
    if ind_dam == 9 && ind_type == 1
    temp_local_aux = temp_local_grid(:,:,t,i);
    temp_local_aux(H0>0) = temp_local_matrix(:,t-1,i);
    temp_local_grid(:,:,t,i) = temp_local_aux;
    end
    
    amen_aux = amen_grid(:,:,t,i);
    amen_aux(H0>0) = amen_matrix(:,t-1,i);
    amen_grid(:,:,t,i) = amen_aux;
    
    amen_ratio_aux = amen_matrix(:,t-1,1)./amen_matrix(:,t-1,2);
    [hist_amen(:,t), interv_amen(:,t)] = ...
        histwc(amen_ratio_aux, pop_sh(:,t-1), nbins);
    std_amen(t) = sqrt(sum(pop_sh(:,t-1).*((amen_ratio_aux-sum(amen_ratio_aux.*pop_sh(:,t-1))).^2)));
    
    prod_aux = prod_grid(:,:,t,i);
    prod_aux(H0>0) = prod_matrix(:,t-1,i);
    prod_grid(:,:,t,i) = prod_aux;
    
    prod_ratio_aux = prod_matrix(:,t-1,1)./prod_matrix(:,t-1,2);
    [hist_prod(:,t), interv_prod(:,t)] = ...
        histwc(prod_ratio_aux, pop_sh(:,t-1), nbins);
	std_prod(t) = sqrt(sum(pop_sh(:,t-1).*((prod_ratio_aux-sum(prod_ratio_aux.*pop_sh(:,t-1))).^2)));

    util_aux = util_grid(:,:,t,i);
    util_aux(H0>0) = util_matrix(:,t-1,i);
    util_grid(:,:,t,i) = util_aux;

    util_ratio_aux = util_matrix(:,t-1,1)./util_matrix(:,t-1,2);
    [hist_util(:,t), interv_util(:,t)] = ...
        histwc(util_matrix(:,t-1,1)./util_matrix(:,t-1,2), pop_sh(:,t-1), nbins);
	std_util(t) = sqrt(sum(pop_sh(:,t-1).*((util_ratio_aux-sum(util_ratio_aux.*pop_sh(:,t-1))).^2)));

    realgdp_aux = realgdp_grid(:,:,t,i);
    realgdp_aux(H0>0) = realgdp_matrix(:,t-1,i);
    realgdp_grid(:,:,t,i) = realgdp_aux;
 
    realgdp_ratio_aux = realgdp_matrix(:,t-1,1)./realgdp_matrix(:,t-1,2);
    [hist_realgdp(:,t), interv_realgdp(:,t)] = ...
        histwc(realgdp_matrix(:,t-1,1)./realgdp_matrix(:,t-1,2), pop_sh(:,t-1), nbins);
	std_realgdp(t) = sqrt(sum(pop_sh(:,t-1).*((realgdp_ratio_aux-sum(realgdp_ratio_aux.*pop_sh(:,t-1))).^2)));

    pop_aux = pop_grid(:,:,t,i);
    pop_aux(H0>0) = pop_matrix(:,t-1,i);
    pop_grid(:,:,t,i) = pop_aux;
 
    if ind_dam == 9 && ind_type == 1
    emiCO2_aux = emiCO2_grid(:,:,t,i);
    emiCO2_aux(H0>0) = emiCO2_matrix(:,t-1,i);
    emiCO2_grid(:,:,t,i) = emiCO2_aux;
 
    clean_aux = clean_grid(:,:,t,i);
    clean_aux(H0>0) = clean_matrix(:,t-1,i);
    clean_grid(:,:,t,i) = clean_aux;
    end
    end 
end
end

// Construct ratio of variables with warming relative to no warming 
amen_w_ratio = sum(pop_sh(:,:,1).*amen_matrix(:,:,1)./amen_matrix(:,:,2));
prod_w_ratio = sum(pop_sh(:,:,1).*prod_matrix(:,:,1)./prod_matrix(:,:,2));
realgdp_w_ratio = sum(pop_sh(:,:,1).*realgdp_matrix(:,:,1)./realgdp_matrix(:,:,2));
util_w_ratio = sum(pop_sh(:,:,1).*util_matrix(:,:,1)./util_matrix(:,:,2));

// Construct PDV of real GDP and utility
for i=1:2
    PDV_realgdp_matrix(:,i) = sum(beta_matrix.*realgdp_matrix(:,:,i),2);
    realgdp_w = sum(pop_sh(:,:,i).*realgdp_matrix(:,:,i));
    BGP_realgdp_w(i) = realgdp_w(T)./realgdp_w(T-1);
    index_last_PDV_realgdp = (beta*BGP_realgdp_w(i) < 1);    
    arg_last_PDV_realgdp = (beta^T*realgdp_matrix(:,T,i).*BGP_realgdp_w(i)) ./...
            (1-beta*BGP_realgdp_w(i));
    PDV_realgdp_matrix(:,i) = PDV_realgdp_matrix(:,i) + arg_last_PDV_realgdp;
    if index_last_PDV_realgdp == 0
        PDV_realgdp_matrix(:,i) = NaN;
    end
    PDV_realgdp_grid_aux = NaN(180,360); 
    PDV_realgdp_grid_aux(H0>0) = PDV_realgdp_matrix(:,i);
    PDV_realgdp_grid(:,:,i) = PDV_realgdp_grid_aux;

    PDV_util_matrix(:,i) = sum(beta_matrix.*util_matrix(:,:,i),2);
    util_w = sum(pop_sh(:,:,i).*util_matrix(:,:,i));
    BGP_util_w(i) = util_w(T)./util_w(T-1);
    index_last_PDV_util = (beta*BGP_util_w(i) < 1);    
    arg_last_PDV_util = (beta^T*util_matrix(:,T,i).*BGP_util_w(i)) ./...
            (1-beta*BGP_util_w(i));
    PDV_util_matrix(:,i) = PDV_util_matrix(:,i) + arg_last_PDV_util;
    if index_last_PDV_util == 0
        PDV_util_matrix(:,i) = NaN;
    end
    PDV_util_grid_aux = NaN(180,360); 
    PDV_util_grid_aux(H0>0) = PDV_util_matrix(:,i);
    PDV_util_grid(:,:,i) = PDV_util_grid_aux;
end
BGP_realgdp_w_factual = BGP_realgdp_w(1);
BGP_realgdp_w_counterfact = BGP_realgdp_w(2);
BGP_util_w_factual = BGP_util_w(1);
BGP_util_w_counterfact = BGP_util_w(2);

// Construct ratio of variables with warming relative to no warming 
PDV_realgdp_ratio = PDV_realgdp_matrix(:,1)./PDV_realgdp_matrix(:,2);
PDV_realgdp_w_ratio = sum(pop0_sh.*PDV_realgdp_ratio);
[hist_PDV_realgdp, interv_PDV_realgdp] = ...
    histwc(PDV_realgdp_ratio, pop0_sh, nbins);
std_PDV_realgdp = sqrt(sum(pop0_sh.*((PDV_realgdp_ratio-PDV_realgdp_w_ratio).^2)));

PDV_util_ratio = PDV_util_matrix(:,1)./PDV_util_matrix(:,2);
PDV_util_w_ratio = sum(pop0_sh.*PDV_util_ratio);
[hist_PDV_util, interv_PDV_util] = ...
    histwc(PDV_util_ratio, pop0_sh, nbins);
std_PDV_util = sqrt(sum(pop0_sh.*((PDV_util_ratio-PDV_util_w_ratio).^2)));

if ind_plot ~= 0 || taxCO2_val ~= 0 || subclean_val ~= 0

// Set numerical parameters
[map_lat,map_lon] = size(map);
aux_lon = linspace(-180,180,map_lon+1);
aux_lon = (aux_lon(1:end-1)+aux_lon(2:end))/2;
aux_lat = linspace(-90,90,map_lat+1); 
aux_lat = (aux_lat(1:end-1)+aux_lat(2:end))/2;
aux_kron = ones(map_lat/180);

share_land = H./sum(H);
year_disp = [50 100 200];
thresh_hot = 20;
thresh_cold = -30;
CM = [color_yellowgreen; color_olive; color_darkcyan; color_darkgreen];

// // Generate kernels
// multi = 1e-3; 
// large_number = 1e4;
// vect_year = [1 100 200 300];
// n_year = length(vect_year);
// legend_year = cell(4,1);
// length_kernel_realgdp = NaN(4,1);
// length_kernel_util = NaN(4,1);
// 
// f_realgdp = NaN(large_number,4);
// xi_realgdp = NaN(large_number,4);
// 
// f_util = NaN(large_number,4);
// xi_util = NaN(large_number,4);
// 
// for ind_year=1:n_year
//     legend_year{ind_year} = ['year ' num2str(2000+vect_year(ind_year))];
//     
//     realgdp_rel_kron = repelem(realgdp_matrix(:,vect_year(ind_year),1)./realgdp_matrix(:,vect_year(ind_year),2),...
//         round(multi*pop_matrix(:,vect_year(ind_year),1).*H));
//     [f_realgdp_aux,xi_realgdp_aux] = ksdensity(realgdp_rel_kron,...
//         'Function','pdf','Bandwidth',0.00025); 
//     length_kernel_realgdp(ind_year) = length(f_realgdp_aux);
//     f_realgdp(1:length_kernel_realgdp(ind_year),ind_year) = f_realgdp_aux;
//     xi_realgdp(1:length_kernel_realgdp(ind_year),ind_year) = xi_realgdp_aux;
//     
//     util_rel_kron = repelem(util_matrix(:,vect_year(ind_year),1)./util_matrix(:,vect_year(ind_year),2),...
//         round(multi*pop_matrix(:,vect_year(ind_year),1).*H));
//     [f_util_aux,xi_util_aux] = ksdensity(util_rel_kron,...
//         'Function','pdf','Bandwidth',0.00025); 
//     length_kernel_util(ind_year) = length(f_util_aux);
//     f_util(1:length_kernel_util(ind_year),ind_year) = f_util_aux;
//     xi_util(1:length_kernel_util(ind_year),ind_year) = xi_util_aux;
// end
// 
// data_natal = load('Data/derived/natal_migr_Warm_med.mat');
// upsilon_fossil = data_natal.upsilon_fossil_i;
// upsilon_clean = data_natal.upsilon_clean_i;
// 
// costCO2_fct =@(cumCO2) ...
//     cost_emi_param(1)./(cost_emi_param(2) + ...
//     exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
//     cost_emi_param(5)*(cost_emi_param(6)./(cumCO2-cost_emi_param(6))).^cost_emi_param(7);
// costCO2_avg_factual = mean(costCO2_fct(emi0_ff + linspace(0,emiCO2_total_factual(1)-emi_no_ff(1),1e2)));
// costCO2_avg_counterfact = mean(costCO2_fct(emi0_ff + linspace(0,emiCO2_total_counterfact(1)-emi_no_ff(1),1e2)));
// 
// price_fossil0_grid = NaN(180,360);
// price_fossil0_grid(H0>0) = price_fossil0;
// 
// price_clean0_grid = NaN(180,360);
// price_clean0_grid(H0>0) = price_clean0;
// 
// realgdp_growth_factual = sum(pop_sh(:,1,1).*realgdp_matrix(:,1,1))/sum(pop0_sh.*realgdp0);
// realgdp_growth_counterfact = sum(pop_sh(:,1,2).*realgdp_matrix(:,1,2))/sum(pop0_sh.*realgdp0);
// 
// zeta_fossil1_factual = zeta_fossil0*realgdp_growth_factual^upsilon_fossil;
// zeta_fossil1_counterfact = zeta_fossil0*realgdp_growth_counterfact^upsilon_fossil;
// 
// zeta_clean1_factual = zeta_clean0*realgdp_growth_factual^upsilon_clean;
// zeta_clean1_counterfact = zeta_clean0*realgdp_growth_counterfact^upsilon_clean;
// 
// price_fossil1_factual = costCO2_avg_factual./zeta_fossil1_factual;
// price_fossil1_counterfact = costCO2_avg_counterfact./zeta_fossil1_counterfact;
// 
// price_clean1_factual = price_clean0_world./zeta_clean1_factual;
// price_clean1_counterfact = price_clean0_world./zeta_clean1_counterfact;
// 
// price_energy1_factual = ...
//     (fossil_share^epsilon*(1+taxCO2_val)^(1-epsilon).*price_fossil1_factual.^(1-epsilon) + ...
//     (1-fossil_share)^epsilon*(1-subclean_val)^(1-epsilon).*price_clean1_factual.^(1-epsilon)).^(1/(1-epsilon));
// price_energy1_counterfact = ...
//     (fossil_share^epsilon.*price_fossil1_counterfact.^(1-epsilon) + ...
//     (1-fossil_share)^epsilon.*price_clean1_counterfact.^(1-epsilon)).^(1/(1-epsilon));
// price_energy1_grid = NaN(180,360);
// price_energy1_grid(H0>0) = price_energy1_factual./price_energy1_counterfact;
// 
// price_energy1_tilde = ...
//     (fossil_share^epsilon*(1+taxCO2_val).^(-epsilon).*price_fossil1_factual.^(1-epsilon) + ...
//     (1-fossil_share)^epsilon*(1-subclean_val).^(-epsilon).*price_clean1_factual.^(1-epsilon)).^(1/(1-epsilon));
// varphi1 = (mu*chi + gamma1/ksi + mu*(1-chi)*(price_energy1_tilde./price_energy1_factual).^(1-epsilon))/...
//         (mu+gamma1/ksi);
// const_energy = (1-chi)*mu/(mu+gamma1/ksi);
// 
// fossil1_factual = const_energy*(1./varphi1).*(pop_matrix(:,1,1)./price_energy1_factual).* ...
//     (fossil_share*price_energy1_factual./((1+taxCO2_val).*price_fossil1_factual)).^epsilon;
// fossil1_counterfact = const_energy*(pop_matrix(:,1,2)./price_energy1_counterfact) .* ...
//     (fossil_share*price_energy1_counterfact./price_fossil1_counterfact).^epsilon;
// fossil1_grid = NaN(180,360);
// fossil1_grid(H0>0) = fossil1_factual./fossil1_counterfact;
// 
// clean1_factual = const_energy*(1./varphi1).*(pop_matrix(:,1,1)./price_energy1_factual).* ...
//     ((1-fossil_share)*price_energy1_factual./((1-subclean_val).*price_clean1_factual)).^epsilon;
// clean1_counterfact = const_energy*(pop_matrix(:,1,2)./price_energy1_counterfact) .* ...
//     ((1-fossil_share)*price_energy1_counterfact./price_clean1_counterfact).^epsilon;
// clean1_grid = NaN(180,360);
// clean1_grid(H0>0) = clean1_factual./clean1_counterfact;
// 
// energy1_factual = (fossil_share*fossil1_factual.^((epsilon-1)/epsilon) + ...
//     (1-fossil_share)*clean1_factual.^((epsilon-1)/epsilon)).^(epsilon/(epsilon-1));
// energy1_counterfact = (fossil_share*fossil1_counterfact.^((epsilon-1)/epsilon) + ...
//     (1-fossil_share)*clean1_counterfact.^((epsilon-1)/epsilon)).^(epsilon/(epsilon-1));
// energy1_grid = NaN(180,360);
// energy1_grid(H0>0) = energy1_factual./energy1_counterfact;
// 
// disp_years_tax = [1 100 200];
// pop_grid = NaN(180,360,T+1,2);
// realgdp_grid = NaN(180,360,T+1,2);
// util_grid = NaN(180,360,T+1,2);
// for t=disp_years_tax
//     for i=1:2
//         pop_aux = pop_grid(:,:,t,i);
//         pop_aux(H0>0) = pop_matrix(:,t,i);
//         pop_grid(:,:,t,i) = pop_aux;
//         
//         realgdp_aux = realgdp_grid(:,:,t,i);
//         realgdp_aux(H0>0) = realgdp_matrix(:,t,i);
//         realgdp_grid(:,:,t,i) = realgdp_aux;
// 
//         util_aux = util_grid(:,:,t,i);
//         util_aux(H0>0) = util_matrix(:,t,i);
//         util_grid(:,:,t,i) = util_aux;        
//     end
// end

// Define plot titles and axis limits
if strcmp(name_abat,'') == 1
    title_abat = '';
elseif strcmp(name_abat,'_abat2100_100pp') == 1 && strcmp(name_abat,'_abat2100_100pp_all') == 1
    title_abat = ' and abat 2100';
elseif strcmp(name_abat,'_abat2200_100pp') == 1
    title_abat = ' and abat 2200';
else 
    title_abat = '';
end

if ind_dam == 1
    name_dam_long = 'worst-scenario';
else
    if ind_type == 1
    name_dam_long = 'baseline';
    else
        name_dam_long = name_maps_type;
    end
end

name_pol = ['_tax' num2str(100*taxCO2_val) 'p_sub' num2str(100*subclean_val) 'p' name_abat];
if taxCO2_val == 0 && subclean_val == 0
    title_realgdp = ['PDV real GDP: ' name_dam_long ' relative to no warming'];
    title_welfare = ['Welfare: ' name_dam_long ' relative to no warming'];
    title_name = '';
	clim_welfare = [0.85 1.15];
    clim_realgdp = [0.93 1.07];
    name_pol = '';
elseif taxCO2_val == 0 && subclean_val ~= 0
    title_realgdp = ['PDV real GDP, clean subsidy ' num2str(100*subclean_val) '//' title_abat ': relative to no clean subsidy'];
    title_welfare = ['Welfare, clean subsidy ' num2str(100*subclean_val) '//' title_abat ': relative to no clean subsidy'];
    title_name = [', clean subsidy ' num2str(100*subclean_val) '//: relative to no clean subsidy'];
    if subclean_val == 0.75
    clim_realgdp = [1.02 1.15];
    clim_welfare = [1.025 1.065];
    else
    clim_realgdp = [1 1.15];
    clim_welfare = [1 1.065];
    end
    legend_pop1 = ['Model, no clean subsidy'];
    legend_pop2 = ['Model, clean subsidy ' num2str(100*subclean_val) '//'];
elseif taxCO2_val ~= 0 && subclean_val == 0
    title_realgdp = ['PDV real GDP, carbon tax ' num2str(100*taxCO2_val) '//' title_abat ': relative to no carbon tax'];
    title_welfare = ['Welfare, carbon tax ' num2str(100*taxCO2_val) '//' title_abat ': relative to no carbon tax'];
    title_name = [', carbon tax ' num2str(100*taxCO2_val) '//' title_abat ': relative to no carbon tax'];
    if strcmp(name_abat,'') == 1
    clim_realgdp = [0.93 1.015];
    clim_welfare = [0.93 1.02];
    else 
    clim_realgdp = [0.93 1.03];
    clim_welfare = [0.93 1.05];
    end
    legend_pop1 = ['Model, no carbon tax'];
    legend_pop2 = ['Model, carbon tax ' num2str(100*taxCO2_val) '//'];
else
    title_realgdp = ['PDV real GDP, carbon tax ' num2str(100*taxCO2_val) '//, clean subsidy ' num2str(100*subclean_val) '//' title_abat ', relative to no taxes'];
    title_welfare = ['Welfare, carbon tax ' num2str(100*taxCO2_val) '//, clean subsidy ' num2str(100*subclean_val) '//' title_abat ', relative to no taxes'];
    title_name = [', carbon tax ' num2str(100*taxCO2_val) '//, clean subsidy ' num2str(100*subclean_val) '//' title_abat ': relative to no taxes'];
    clim_realgdp = [0.93 1.15];
    clim_welfare = [0.93 1.065];
    legend_pop1 = ['Model, no carbon tax and no clean subsidy'];
    legend_pop2 = ['Model, carbon tax ' num2str(100*taxCO2_val) '// and clean subsidy ' num2str(100*subclean_val) '//'];
end

end

////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for global climate variables

if ind_plot == 1 && ind_type == 1   
if ind_dam == 9
   
[max_emiCO2,argmax_emiCO2] = max(emiCO2_total_factual(1:T));
disp(['CO2 emissions reach a peak of ' num2str(max_emiCO2) ...
    ' GtCO2 in the year ' num2str(2000+argmax_emiCO2)])    
    
// CO2 Emissions
figure
hold on
plot(2001:2000+T,emiCO2_total_factual(1:T),'color',color_yellowgreen,...
    'LineWidth',2) 
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,1),'k--',...
    'LineWidth',2) 
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,2),'k:',...
    'LineWidth',2) 
legend('Model','IPCC (RCP 8.5)','IPCC (RCP 6.0)','Location','northeast','FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
title(['CO2 emissions (GtCO2/year)'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/emiCO2_' name_long_type name_dam name_adap '.png'])

// CO2 Stock
figure
hold on
plot(2001:2000+T,stockCO2_factual(1:T),'color',color_yellowgreen,...
    'LineWidth',2)
hold on
plot(2001:2000+T,stockCO2_RCP(1:T,1),'k--',...
    'LineWidth',2)
hold on
plot(2001:2000+T,stockCO2_RCP(1:T,2),'k:',...
    'LineWidth',2)
legend('Model','IPCC (RCP 8.5)','IPCC (RCP 6.0)','Location','southeast','FontSize',14) 
ylim([2500 12000])
set(gca,'FontSize',14)
set(gcf,'color','w')
title(['CO2 stock (GtCO2)'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/stockCO2_' name_long_type name_dam name_adap '.png'])

for y=1:length(year_disp)
disp(['In ' num2str(2000+year_disp(y)) ', global temperature rises ' ...
    num2str(temp_global_factual(year_disp(y))-temp_preind) 'ºC relative to its pre-industrial level'])
end

// Global temperature
figure
hold on
plot(2001:2000+T,temp_global_factual(1:T)-temp_preind,'color',color_yellowgreen,...
    'LineWidth',2) 
hold on
plot(2001:2000+T,temp_global_RCP(1:T,1)-temp_preind,'k--',...
    'LineWidth',2) 
hold on
plot(2001:2000+T,temp_global_RCP(1:T,2)-temp_preind,'k:',...
    'LineWidth',2) 
legend('Model','IPCC (RCP 8.5)','IPCC (RCP 6.0)','Location','southeast','FontSize',14)
ylim([1 9])
set(gca,'FontSize',14)
set(gcf,'color','w')
title(['Global temperature (C) relative to pre-industrial level'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/temp_global_' name_long_type name_dam name_adap '.png'])

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for local CO2 emissions and clean energy use

// Levels of CO2 emissions
for t=[1]
    figure
    colormap(jet);
    imagesc(aux_lon,aux_lat,map.*kron(log(emiCO2_grid(:,:,t,1)),aux_kron),...
        'AlphaData',~isnan(map.*kron(log(emiCO2_grid(:,:,t,1)),aux_kron)),[-30 0]);
    colorbar('eastoutside');
    set(gcf,'color','w');
    set(gca,'color',[1 1 1],'FontSize',14)
    set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
    set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
    title(['Log CO2 emissions (GtCO2 per land), ' num2str(1999+t) ''])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/emiCO2_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

// Levels of clean energy
for t=[1]
    figure
    colormap(jet);
    imagesc(aux_lon,aux_lat,...
        map.*kron(log(clean_grid(:,:,t,1)),aux_kron),...
        'AlphaData',~isnan(map.*kron(log(clean_grid(:,:,t,1)),aux_kron)),[-30 0]);
    colorbar('eastoutside');
    set(gcf,'color','w');
    set(gca,'color',[1 1 1],'FontSize',14)
    set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
    set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
    title(['Log clean energy (GtCO2 per land), ' num2str(1999+t) ''])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/clean_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

// figure
// colormap(jet);
// imagesc(aux_lon,aux_lat,map.*kron(log((1/conv_usd)*price_fossil0_grid),aux_kron),...
//     'AlphaData',~isnan(map.*kron(log((1/conv_usd)*price_fossil0_grid),aux_kron)),[0 20]);
// colorbar('eastoutside');
// set(gcf,'color','w');
// set(gca,'color',[1 1 1],'FontSize',14)
// set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
// set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
// title(['Log fossil fuel price (usd/GtCO2), 2000'])
// ax = gca;
// ax.YTickLabel = flipud(ax.YTickLabel);
// outerpos = ax.OuterPosition;
// ti = ax.TightInset;
// left = outerpos(1) + ti(1);
// bottom = outerpos(2) + ti(2);
// ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
// ax_height = outerpos(4) - ti(2) - ti(4);
// ax.Position = [left bottom ax_width ax_height];
// saveas(gcf,['Maps and Figures/price_fossil_2000_med.png'])
// 
// figure
// colormap(jet);
// imagesc(aux_lon,aux_lat,map.*kron(log((1/conv_usd)*price_clean0_grid),aux_kron),...
//     'AlphaData',~isnan(map.*kron(log((1/conv_usd)*price_clean0_grid),aux_kron)),[0 20]);
// colorbar('eastoutside');
// set(gcf,'color','w');
// set(gca,'color',[1 1 1],'FontSize',14)
// set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
// set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
// title(['Log clean energy price (usd/GtCO2), 2000'])
// ax = gca;
// ax.YTickLabel = flipud(ax.YTickLabel);
// outerpos = ax.OuterPosition;
// ti = ax.TightInset;
// left = outerpos(1) + ti(1);
// bottom = outerpos(2) + ti(2);
// ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
// ax_height = outerpos(4) - ti(2) - ti(4);
// ax.Position = [left bottom ax_width ax_height];
// saveas(gcf,['Maps and Figures/price_clean_2000_med.png'])

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for local temperature

disp(['In 2000, ' num2str(1e2*sum(share_land(temp0_local>thresh_hot))) ...
    '// of land surface experienced temperatures higher than ' ...
    num2str(thresh_hot) 'ºC'])
for y=1:length(year_disp)
disp(['In ' num2str(2000+year_disp(y)) ', ' ...
    num2str(1e2*sum(share_land(temp_local_factual(:,year_disp(y))>thresh_hot))) ...
    '// of land surface experienced temperatures higher than ' ...
    num2str(thresh_hot) 'ºC'])
end
disp(['In 2000, ' num2str(1e2*sum(share_land(temp0_local<thresh_cold))) ...
    '// of land surface experienced temperatures lower than ' ...
    num2str(thresh_cold) 'ºC'])
for y=1:length(year_disp)
disp(['In ' num2str(2000+year_disp(y)) ', ' ...
    num2str(1e2*sum(share_land(temp_local_factual(:,year_disp(y))<thresh_cold))) ...
    '// of land surface experienced temperatures lower than ' ...
    num2str(thresh_cold) 'ºC'])
end

// Levels of local temperature
for t=[1 201]
    figure
    colormap(jet);
    imagesc(aux_lon,aux_lat,...
    	map.*kron(temp_local_grid(:,:,t,1),aux_kron),...
        'AlphaData',~isnan(map.*kron(temp_local_grid(:,:,t,1),aux_kron)),[-40 30]); 
    colorbar('eastoutside');
    set(gcf,'color','w');
    set(gca,'color',[1 1 1],'FontSize',14)
    set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
    set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
    title(['January-July temperature (C), ' num2str(1999+t) ''])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/temp_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for amenities

// Evolution of amenities
for t=[201]
    figure
    colormap(jet);
	imagesc(aux_lon,aux_lat,...
    	map.*kron(amen_grid(:,:,t,1)./amen_grid(:,:,t,2),aux_kron),...
        'AlphaData',~isnan(map.*kron(amen_grid(:,:,t,1)./amen_grid(:,:,t,2),aux_kron)),[0.6 1.4]); 
    colorbar('eastoutside');
    set(gcf,'color','w');
    set(gca,'color',[1 1 1],'FontSize',14)
    set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
    set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
    title(['Amenities ' num2str(1999+t) ': ' name_dam_long ' relative to no warming'])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/amen_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

// Histogram of amenities
for t=[201]
    figure
    hold on
    xline(amen_w_ratio(t-1),'k--','LineWidth',2.5)
    hold on
    plot(NaN,NaN,'w')
    hold on
    bar(interv_amen(:,t),hist_amen(:,t),'FaceColor',color_darkcyan)
    legend(['Average = ' num2str(round(amen_w_ratio(t-1),3))],...
        ['Std dev = ' num2str(round(std_amen(t-1),3))],...
        'Location','northeast','FontSize',14)
    set(gcf,'color','w');
    set(gca,'FontSize',14)
    title(['Amenities ' num2str(1999+t) ': ' name_dam_long ' relative to no warming'])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/amen_hist_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for productivities

// Evolution of producitivities
for t=[201]
    figure
    colormap(jet);
    imagesc(aux_lon,aux_lat,...
        map.*kron(prod_grid(:,:,t,1)./prod_grid(:,:,t,2),aux_kron),...
        'AlphaData',~isnan(map.*kron(prod_grid(:,:,t,1)./prod_grid(:,:,t,2),aux_kron)),[0 2]);
    colorbar('eastoutside');
    set(gcf,'color','w');
    set(gca,'color',[1 1 1],'FontSize',14)
    set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
    set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
    title(['Productivities ' num2str(1999+t) ': ' name_dam_long ' relative to no warming'])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/prod_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

// Histogram of productivities
for t=[201]
    figure
    hold on
    xline(prod_w_ratio(t-1),'k--','LineWidth',2.5)
    hold on
    plot(NaN,NaN,'w')
    hold on
    bar(interv_prod(:,t),hist_prod(:,t),'FaceColor',color_darkgreen)
    legend(['Average = ' num2str(round(prod_w_ratio(t-1),3))],...
        ['Std dev = ' num2str(round(std_prod(t-1),3))],...
        'Location','northeast','FontSize',14)
    set(gcf,'color','w');
    set(gca,'FontSize',14)
    title(['Productivities ' num2str(1999+t) ': ' name_dam_long ' relative to no warming'])
    ax = gca;
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/prod_hist_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for population

[max_pop,argmax_pop] = max(lbar_total_factual(1:T));
disp(['Global population reaches a peak of ' num2str(1e-9*max_pop) ' billions in the year ' num2str(2000+argmax_pop)])    

for y=1:length(year_disp)
disp(['In ' num2str(2000+year_disp(y)) ', global warming changes world population by ' ...
    num2str(1e-6*(lbar_total_factual(year_disp(y))-lbar_total_counterfact(year_disp(y)))) ...
    ' millions'])
end

figure
hold on
plot(2000:2000+T,[lbar;lbar_total_factual],'color',color_yellowgreen,...
    'LineWidth',2)
hold on
plot(2000:2000+T,[lbar;lbar_total_counterfact],'color',color_darkgreen,...
    'LineWidth',2)
hold on
plot(2000:2100,(10^3)*pop_low95-(10^3)*pop_low95(1)+lbar,'k:',...
    2000:2100,(10^3)*pop_low80-(10^3)*pop_low80(1)+lbar,'k--',...
    2000:2100,(10^3)*pop_med-(10^3)*pop_med(1)+lbar,'k',...
    2000:2100,(10^3)*pop_high95-(10^3)*pop_high95(1)+lbar,'k:',...
    2000:2100,(10^3)*pop_high80-(10^3)*pop_high80(1)+lbar,'k--','LineWidth',2) 
title(['Global population'])
legend('Model, warming','Model, no warming',...
    '95// interval UN','80// interval UN','median UN','Location','southeast','FontSize',14) 
set(gca,'FontSize',14)
set(gcf,'color','w')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/pop_' name_long_type name_dam name_adap '.png'])

for y=1:length(year_disp)

pop_diff = 0.5*sum(abs(pop_matrix(:,year_disp(y),1).*H-pop_matrix(:,year_disp(y),2).*H));
disp(['In ' num2str(2000+year_disp(y)) ', ' num2str(1e-6*pop_diff) ...
    ' millions of persons (' num2str(1e2*pop_diff./lbar_total_factual(year_disp(y))) ...
    '// of global population) reside in a different location'])
disp(['In ' num2str(2000+year_disp(y)) ', largest increase (decrease) in '...
    'population density: ' num2str(100*(max(pop_matrix(:,year_disp(y),1)./pop_matrix(:,year_disp(y),2))-1)) ...
    '// (' num2str(100*(min(pop_matrix(:,year_disp(y),1)./pop_matrix(:,year_disp(y),2))-1)) '//)'])
end

// Evolution of population density
for t=[201]
    figure
    colormap(jet);
    imagesc(aux_lon,aux_lat,...
        map.*kron(pop_grid(:,:,t,1)./pop_grid(:,:,t,2),aux_kron),...
        'AlphaData',~isnan(map.*kron(pop_grid(:,:,t)./pop_grid(:,:,t,2),aux_kron)),[0.3 1.7]);
    colorbar('eastoutside');
    set(gcf,'color','w');
    set(gca,'color',[1 1 1],'FontSize',14)
    set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
    set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
    title(['Population density ' num2str(1999+t) ': ' name_dam_long ' relative to no warming'])
    ax = gca;
    ax.YTickLabel = flipud(ax.YTickLabel);
    outerpos = ax.OuterPosition;
    ti = ax.TightInset;
    left = outerpos(1) + ti(1);
    bottom = outerpos(2) + ti(2);
    ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
    ax_height = outerpos(4) - ti(2) - ti(4);
    ax.Position = [left bottom ax_width ax_height];
    saveas(gcf,['Maps and Figures/pop_' num2str(1999+t) '_' name_long_type name_dam name_adap '.png'])
end

end

if strcmp(name_abat,'') == 1 && strcmp(name_app,'') == 1
if ind_plot ~= 0 || (taxCO2_val ~= 0 && beta == 0.965) || (subclean_val ~= 0 && beta == 0.965)
    
//     // Energy prices
//     figure
//     colormap(jet);
//     imagesc(aux_lon,aux_lat,...
//         map.*kron(log(price_fossil0_grid./price_clean0_grid),aux_kron),...
//         'AlphaData',~isnan(map.*kron(log(price_fossil0_grid./price_clean0_grid),aux_kron)));
//     colorbar('eastoutside');
//     set(gcf,'color','w');
//     set(gca,'color',[1 1 1],'FontSize',14)
//     set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//     set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//     title(['Log Price CO2 - Log Price clean energy, 2000'])
//     ax = gca;
//     ax.YTickLabel = flipud(ax.YTickLabel);
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset;
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/log_price_energy.png'])
//     
//     figure
//     colormap(jet);
//     imagesc(aux_lon,aux_lat,...
//         map.*kron(price_energy1_grid,aux_kron),...
//         'AlphaData',~isnan(map.*kron(price_energy1_grid,aux_kron)));
//     colorbar('eastoutside');
//     set(gcf,'color','w');
//     set(gca,'color',[1 1 1],'FontSize',14)
//     set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//     set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//     title(['Price energy, 2001' title_name])
//     ax = gca;
//     ax.YTickLabel = flipud(ax.YTickLabel);
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset;
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/price_energy_2001_' name_dam name_pol '.png'])
//     
//     // CO2 emissions
//     figure
//     colormap(jet);
//     imagesc(aux_lon,aux_lat,...
//         map.*kron(fossil1_grid,aux_kron),...
//         'AlphaData',~isnan(map.*kron(fossil1_grid,aux_kron)));
//     colorbar('eastoutside');
//     set(gcf,'color','w');
//     set(gca,'color',[1 1 1],'FontSize',14)
//     set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//     set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//     title(['CO2 emissions, 2001' title_name])
//     ax = gca;
//     ax.YTickLabel = flipud(ax.YTickLabel);
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset;
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.035;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/emiCO2_2001_' name_dam name_pol '.png'])
// 
// 	// Clean energy
//     figure
//     colormap(jet);
//     imagesc(aux_lon,aux_lat,...
//         map.*kron(clean1_grid,aux_kron),...
//         'AlphaData',~isnan(map.*kron(clean1_grid,aux_kron)));
//     colorbar('eastoutside');
//     set(gcf,'color','w');
//     set(gca,'color',[1 1 1],'FontSize',14)
//     set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//     set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//     title(['Clean energy, 2001' title_name])
//     ax = gca;
//     ax.YTickLabel = flipud(ax.YTickLabel);
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset;
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.035;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/clean_2001_' name_dam name_pol '.png'])
// 
// 	// Total energy
//     figure
//     colormap(jet);
//     imagesc(aux_lon,aux_lat,...
//         map.*kron(energy1_grid,aux_kron),...
//         'AlphaData',~isnan(map.*kron(energy1_grid,aux_kron)));
//     colorbar('eastoutside');
//     set(gcf,'color','w');
//     set(gca,'color',[1 1 1],'FontSize',14)
//     set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//     set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//     title(['Total energy, 2001' title_name])
//     ax = gca;
//     ax.YTickLabel = flipud(ax.YTickLabel);
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset;
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.035;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/energy_2001_' name_dam name_pol '.png'])
// 
//     // Population
//     figure
//     hold on
//     plot(2000:2000+T,[lbar;lbar_total_counterfact],'color',color_yellowgreen,...
//         'LineWidth',2)
//     hold on
//     plot(2000:2000+T,[lbar;lbar_total_factual],'color',color_darkgreen,...
//         'LineWidth',2)
//     hold on
//     plot(2000:2100,(10^3)*pop_low95-(10^3)*pop_low95(1)+lbar,'k:',...
//         2000:2100,(10^3)*pop_low80-(10^3)*pop_low80(1)+lbar,'k--',...
//         2000:2100,(10^3)*pop_med-(10^3)*pop_med(1)+lbar,'k',...
//         2000:2100,(10^3)*pop_high95-(10^3)*pop_high95(1)+lbar,'k:',...
//         2000:2100,(10^3)*pop_high80-(10^3)*pop_high80(1)+lbar,'k--','LineWidth',2) 
//     title(['Global population'])
//     legend(legend_pop1,legend_pop2,...
//         '95// interval UN','80// interval UN','median UN','Location','southeast','FontSize',14) 
//     set(gca,'FontSize',14)
//     set(gcf,'color','w')
//     ax = gca;
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset; 
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/pop_' name_long_type name_dam name_adap name_pol '.png'])
// 
//     // Kernels real GDP
//     figure
//     for ind_year=1:n_year
//         hold on
//         plot(xi_realgdp(1:length_kernel_realgdp(ind_year),ind_year),...
//             f_realgdp(1:length_kernel_realgdp(ind_year),ind_year),...
//             'color',CM(ind_year,:),'LineWidth',2) 
//     end
//     legend(legend_year,'Location','northeast','FontSize',14)
//     set(gcf,'color','w');
//     set(gca,'FontSize',14)
//     title(['Real GDP' title_name])
//     ax = gca;
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset; 
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/kernel_years_realgdp_' name_dam name_pol '.png'])
// 
//     // Kernels welfare
//     figure
//     for ind_year=1:n_year
//         hold on
//         plot(xi_util(1:length_kernel_util(ind_year),ind_year),...
//             f_util(1:length_kernel_util(ind_year),ind_year),...
//             'color',CM(ind_year,:),'LineWidth',2) 
//     end
//     legend(legend_year,'Location','northeast','FontSize',14)
//     set(gcf,'color','w');
//     set(gca,'FontSize',14)
//     title(['Welfare' title_name])
//     ax = gca;
//     outerpos = ax.OuterPosition;
//     ti = ax.TightInset; 
//     left = outerpos(1) + ti(1);
//     bottom = outerpos(2) + ti(2);
//     ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
//     ax_height = outerpos(4) - ti(2) - ti(4);
//     ax.Position = [left bottom ax_width ax_height];
//     saveas(gcf,['Maps and Figures/kernel_years_util_' name_dam name_pol '.png'])
// 
//     for t=disp_years_tax
// 
//         // Evolution of population
//         figure
//         colormap(jet);
//         imagesc(aux_lon,aux_lat,...
//             map.*kron(pop_grid(:,:,t,1)./pop_grid(:,:,t,2),aux_kron),...
//             'AlphaData',~isnan(map.*kron(pop_grid(:,:,t,1)./pop_grid(:,:,t,2),aux_kron)));
//         colorbar('eastoutside');
//         set(gcf,'color','w');
//         set(gca,'color',[1 1 1],'FontSize',14)
//         set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//         set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//         title(['Population ' num2str(2000+t) title_name])
//         ax = gca;
//         ax.YTickLabel = flipud(ax.YTickLabel);
//         outerpos = ax.OuterPosition;
//         ti = ax.TightInset;
//         left = outerpos(1) + ti(1);
//         bottom = outerpos(2) + ti(2);
//         ax_width = outerpos(3) - ti(1) - ti(3) - 0.042;
//         ax_height = outerpos(4) - ti(2) - ti(4);
//         ax.Position = [left bottom ax_width ax_height];
//         saveas(gcf,['Maps and Figures/pop_' num2str(2000+t) '_' name_long_type name_dam name_adap name_pol '.png'])
// 
//         // Evolution of real GDP
//         figure
//         colormap(jet);
//         imagesc(aux_lon,aux_lat,...
//             map.*kron(realgdp_grid(:,:,t,1)./realgdp_grid(:,:,t,2),aux_kron),...
//             'AlphaData',~isnan(map.*kron(realgdp_grid(:,:,t,1)./realgdp_grid(:,:,t,2),aux_kron)));
//         colorbar('eastoutside');
//         set(gcf,'color','w');
//         set(gca,'color',[1 1 1],'FontSize',14)
//         set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//         set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//         title(['Real GDP ' num2str(2000+t) title_name])
//         ax = gca;
//         ax.YTickLabel = flipud(ax.YTickLabel);
//         outerpos = ax.OuterPosition;
//         ti = ax.TightInset;
//         left = outerpos(1) + ti(1);
//         bottom = outerpos(2) + ti(2);
//         ax_width = outerpos(3) - ti(1) - ti(3) - 0.042;
//         ax_height = outerpos(4) - ti(2) - ti(4);
//         ax.Position = [left bottom ax_width ax_height];
//         saveas(gcf,['Maps and Figures/realgdp_' num2str(2000+t) '_' name_long_type name_dam name_adap name_pol '.png'])
// 
//         // Evolution of welfare
//         figure
//         colormap(jet);
//         imagesc(aux_lon,aux_lat,...
//             map.*kron(util_grid(:,:,t,1)./util_grid(:,:,t,2),aux_kron),...
//             'AlphaData',~isnan(map.*kron(util_grid(:,:,t,1)./util_grid(:,:,t,2),aux_kron)));
//         colorbar('eastoutside');
//         set(gcf,'color','w');
//         set(gca,'color',[1 1 1],'FontSize',14)
//         set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])
//         set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])
//         title(['Welfare ' num2str(2000+t) title_name])
//         ax = gca;
//         ax.YTickLabel = flipud(ax.YTickLabel);
//         outerpos = ax.OuterPosition;
//         ti = ax.TightInset;
//         left = outerpos(1) + ti(1);
//         bottom = outerpos(2) + ti(2);
//         ax_width = outerpos(3) - ti(1) - ti(3) - 0.042;
//         ax_height = outerpos(4) - ti(2) - ti(4);
//         ax.Position = [left bottom ax_width ax_height];
//         saveas(gcf,['Maps and Figures/util_' num2str(2000+t) '_' name_long_type name_dam name_adap name_pol '.png'])
//     end    

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for PDV real GDP

if taxCO2_val == 0 && subclean_val == 0
[min_realgdp,argmin_realgdp] = min(realgdp_w_ratio(1:T));
disp(['Global real GDP losses reach a peak of ' num2str(1e2*(1-min_realgdp)) '// in the year ' num2str(2000+argmin_realgdp) ', with damage function ' name_dam name_maps_type])    
end

figure
colormap(jet);
imagesc(aux_lon,aux_lat,map.*kron(PDV_realgdp_grid(:,:,1)./PDV_realgdp_grid(:,:,2),aux_kron),...
	'AlphaData',~isnan(map.*kron(PDV_realgdp_grid(:,:,1)./PDV_realgdp_grid(:,:,2),aux_kron)),clim_realgdp); 
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title(title_realgdp)
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_realgdp_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.png'])

figure
if taxCO2_val == 0 && subclean_val == 0
hold on
xline(PDV_realgdp_w_ratio,'k--','LineWidth',2.5)
hold on
plot(NaN,NaN,'w')
end
hold on
bar(interv_PDV_realgdp,hist_PDV_realgdp,'FaceColor',color_darkgreen)
if taxCO2_val == 0 && subclean_val == 0
legend(['Average = ' num2str(round(PDV_realgdp_w_ratio,3))],...
    ['Std dev = ' num2str(round(std_PDV_realgdp,3))],...
    'Location','northeast','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(title_realgdp)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_realgdp_hist_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.png'])

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for welfare

if taxCO2_val == 0 && subclean_val == 0
[min_util,argmin_util] = min(util_w_ratio(1:T));
disp(['Global welfare losses reach a peak of ' num2str(1e2*(1-min_util)) '// in the year ' num2str(2000+argmin_util) ', with damage function ' name_dam name_maps_type])
end

figure
colormap(jet);
imagesc(aux_lon,aux_lat,map.*kron(PDV_util_grid(:,:,1)./PDV_util_grid(:,:,2),aux_kron),...
	'AlphaData',~isnan(map.*kron(PDV_util_grid(:,:,1)./PDV_util_grid(:,:,2),aux_kron)),clim_welfare); 
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title(title_welfare)
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
if subclean_val == 0
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
else
ax_width = outerpos(3) - ti(1) - ti(3) - 0.035;
end
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_util_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.png'])

figure
if taxCO2_val == 0 && subclean_val == 0
hold on
xline(PDV_util_w_ratio,'k--','LineWidth',2.5)
hold on
plot(NaN,NaN,'w')
end
hold on
bar(interv_PDV_util,hist_PDV_util,'FaceColor',color_darkcyan)
if taxCO2_val == 0 && subclean_val == 0
legend(['Average = ' num2str(round(PDV_util_w_ratio,3))],...
    ['Std dev = ' num2str(round(std_PDV_util,3))],...
    'Location','northeast','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(title_welfare)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_util_hist_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.png'])

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Correlation with real income per capita in 2000

x = log(realgdp0);
y = PDV_util_matrix(:,1)./PDV_util_matrix(:,2);
[~,xord]= sort(x);

// Weighted regression
Xreg = [ones(max(size(realgdp0)),1)' ; x']' ;
bhat =  (pop0_sh.*Xreg) \ (pop0_sh.*y) ;

// Predictions
yhat = Xreg * bhat;
slope_str = ['WLS ' ...
    'Slope: ' num2str( round(bhat(2),3) ) ...
    newline 'Correlation: ' num2str(round(corr(x,y),2)) ];
row = [oecd_list ssa_list 32 se_asia_list];

scatterweights = 2e5*pop0_sh;

figure;
hold on;
p_ind = scatter( x( ismember(C_vect,se_asia_list)), y( ismember(C_vect,se_asia_list)), scatterweights(ismember(C_vect,se_asia_list)), 'm' , 'filled', 'MarkerFaceAlpha',0.25);
p_chn = scatter( x( ismember(C_vect,32)), y( ismember(C_vect,32)), scatterweights(ismember(C_vect,32)), 'r' , 'filled', 'MarkerFaceAlpha',0.25);
p_row = scatter( x(~ismember(C_vect,row)), y(~ismember(C_vect,row)), scatterweights(~ismember(C_vect,row)) , [154 205 50]./255 , 'filled', 'MarkerFaceAlpha',0.25);
p_ssa = scatter( x( ismember(C_vect,ssa_list)), y( ismember(C_vect,ssa_list)), scatterweights(ismember(C_vect,ssa_list)), [0.9 0.7 0.1] , 'filled', 'MarkerFaceAlpha',0.25);
p_oecd = scatter( x( ismember(C_vect,oecd_list)), y( ismember(C_vect,oecd_list)),  scatterweights(ismember(C_vect,oecd_list)), 'c' , 'filled', 'MarkerFaceAlpha',0.25);
p_line = plot(x(xord),yhat(xord) ,'k--','LineWidth',2.5);

figvec = [p_chn p_oecd p_ind p_ssa p_row p_line];

bubsizes = quantile(scatterweights,[0.20 0.65 0.75 0.98]);
bubsizes = ceil(bubsizes);

bubnums = quantile(lbar*pop0_sh,[0.20 0.65 0.75 0.98]);
bubnums = ceil(bubnums/1000);

legentry=cell(size(bubsizes,2)+6,1);
legentry{1} = 'China';
legentry{2} = 'OECD';
legentry{3} = 'South East Asia';
legentry{4} = 'Sub Saharan Africa';
legentry{5} = 'Rest of the World';
legentry{6} = slope_str;

for ind = 1:numel(bubsizes)   
    bubleg(ind) = plot(nan,nan,'Marker','o','MarkerEdgeColor','k',...
        'MarkerSize',bubsizes(ind),'LineStyle','none','LineWidth',1.5);   
    figvec = [figvec bubleg(ind)];
    legentry{ind+6} = num2str(bubnums(ind));
end
legentry{7} = [legentry{7} 'k persons'];
legend(figvec,legentry,'Location','northwest','FontSize',10,'NumColumns',6); 

xlabel('Log real GDP per capita, year 2000'); 
ylabel(title_welfare);
set(gcf,'color','w');
set(gca,'FontSize',14)
title('Welfare losses from warming and real GDP per capita in 2000')
hold off
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/cor_welf_inc2000_countries_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.png'] )
set(gcf,'PaperSize',[8 6])
saveas(gcf,['Maps and Figures/cor_welf_inc2000_countries_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.pdf'] )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Correlation with welfare per capita in 2000

x = log( util_factual(:,1) );
y = PDV_util_matrix(:,1)./PDV_util_matrix(:,2);
[~,xord]= sort(x);

// Weighted regression
Xreg = [ones(max(size(realgdp0)),1)' ; x']' ;
bhat =  (pop0_sh.*Xreg) \ (pop0_sh.*y) ;

// Predictions
yhat = Xreg * bhat;
slope_str = ['WLS ' ...
    'Slope: ' num2str( round(bhat(2),3) ) ...
    newline 'Correlation: ' num2str(round(corr(x,y),2)) ];
row = [oecd_list ssa_list 32 se_asia_list];

scatterweights = 2e5*pop0_sh;

figure;
hold on;
p_ind = scatter( x( ismember(C_vect,se_asia_list)), y( ismember(C_vect,se_asia_list)), scatterweights(ismember(C_vect,se_asia_list)), 'm' , 'filled', 'MarkerFaceAlpha',0.25);
p_chn = scatter( x( ismember(C_vect,32)), y( ismember(C_vect,32)), scatterweights(ismember(C_vect,32)), 'r' , 'filled', 'MarkerFaceAlpha',0.25);
p_row = scatter( x(~ismember(C_vect,row)), y(~ismember(C_vect,row)), scatterweights(~ismember(C_vect,row)) , [154 205 50]./255 , 'filled', 'MarkerFaceAlpha',0.25);
p_ssa = scatter( x( ismember(C_vect,ssa_list)), y( ismember(C_vect,ssa_list)), scatterweights(ismember(C_vect,ssa_list)), [0.9 0.7 0.1] , 'filled', 'MarkerFaceAlpha',0.25);
p_oecd = scatter( x( ismember(C_vect,oecd_list)), y( ismember(C_vect,oecd_list)),  scatterweights(ismember(C_vect,oecd_list)), 'c' , 'filled', 'MarkerFaceAlpha',0.25);
p_line = plot(x(xord),yhat(xord) ,'k--','LineWidth',2.5);

figvec = [p_chn p_oecd p_ind p_ssa p_row p_line];

bubsizes = quantile(scatterweights,[0.20 0.65 0.75 0.98]);
bubsizes = ceil(bubsizes);

bubnums = quantile(lbar*pop0_sh,[0.20 0.65 0.75 0.98]);
bubnums = ceil(bubnums/1000);

legentry=cell(size(bubsizes,2)+6,1);
legentry{1} = 'China';
legentry{2} = 'OECD';
legentry{3} = 'South East Asia';
legentry{4} = 'Sub Saharan Africa';
legentry{5} = 'Rest of the World';
legentry{6} = slope_str;

for ind = 1:numel(bubsizes)   
    bubleg(ind) = plot(nan,nan,'Marker','o','MarkerEdgeColor','k',...
        'MarkerSize',bubsizes(ind),'LineStyle','none','LineWidth',1.5);   
    figvec = [figvec bubleg(ind)];
    legentry{ind+6} = num2str(bubnums(ind));
end
legentry{7} = [legentry{7} 'k persons'];
legend(figvec,legentry,'Location','northwest','FontSize',10,'NumColumns',6); 

xlabel('Log welfare per capita, year 2000 (model implied)'); 
ylabel(title_welfare);
set(gcf,'color','w');
set(gca,'FontSize',14)
title('Welfare losses from warming and welfare per capita in 2000')
hold off
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/cor_welf_welf2000_countries_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.png'] )
set(gcf,'PaperSize',[8 6])
saveas(gcf,['Maps and Figures/cor_welf_welf2000_countries_' name_long_type name_dam name_adap name_pol '_beta' num2str(1e3*beta) '.pdf'] )

end
end

end
