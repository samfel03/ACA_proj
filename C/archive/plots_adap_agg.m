
function [] = plots_adap_agg( ...
        amen_w_dam, amen_w_adap, prod_w_dam, prod_w_adap, ...
        realgdp_w_dam, realgdp_w_adap, util_w_dam, util_w_adap, ...
        lbar_w_dam, lbar_w_adap, ...
        PDV_realgdp_dam, PDV_realgdp_adap, ...
        PDV_util_dam, PDV_util_adap, ...
        names_adap, long_names_adap, beta )

// Function that generates the maps and figures of adaptation in trade, 
// migration and innovation of Section 5, Appendix E.3 and 
// Supplementary Materials Section I
// Inputs:
//   amen_w_dam, prod_w_dam, realgdp_w_dam, util_w_dam: 
//   global amenities, productivities, real GDP and utility relative 
//   to no warming
//   PDV_realgdp_dam, PDV_util_dam: local PDV of real GDP and 
//   utility relative to no warming
//   amen_w_adap, prod_w_adap, realgdp_w_adap, util_w_adap: 
//   global amenities, productivities, real GDP and utility relative 
//   to no warming, for different degrees of adaptation
//   PDV_realgdp_adap, PDV_util_adap: local PDV of real GDP and 
//   utility relative to no warming, for different degrees of adaptation.
//   names_adap, long_names_adap: labels for adaptation levels
//   beta: discount factor
            
global map color_olive color_darkgreen color_yellowgreen H0

// Set sizes
T = length(amen_w_dam);
length_adap = length(names_adap);

// Pre-allocate some matrices of size (lat x lon x years x length_adap)
PDV_realgdp_dam_grid = NaN(180,360);
PDV_realgdp_adap_grid = NaN(180,360,length_adap);
PDV_util_dam_grid = NaN(180,360);
PDV_util_adap_grid = NaN(180,360,length_adap);

PDV_realgdp_dam_grid(H0>0) = PDV_realgdp_dam;
PDV_util_dam_grid(H0>0) = PDV_util_dam;

for ind_adap=1:length_adap
    PDV_realgdp_grid_aux = NaN(180,360);
    PDV_realgdp_grid_aux(H0>0) = PDV_realgdp_adap(:,ind_adap);
    PDV_realgdp_adap_grid(:,:,ind_adap) = PDV_realgdp_grid_aux;

    PDV_util_grid_aux = NaN(180,360);
    PDV_util_grid_aux(H0>0) = PDV_util_adap(:,ind_adap);
    PDV_util_adap_grid(:,:,ind_adap) = PDV_util_grid_aux;
end

// Define colors
if length_adap == 4
    CM = [color_yellowgreen; color_olive; color_darkgreen];
else
    CM = parula(length_adap);
end

// Define axis
short_names_adap = cell(length_adap/2,1,1);
file_names_adap = cell(length_adap/2,1,1);
for ind_adap=1:length_adap/2
    names_adap_aux = long_names_adap{ind_adap};
    short_names_adap{ind_adap} = names_adap_aux(1:end-11);
    names_adap_aux = names_adap{ind_adap};
    file_names_adap{ind_adap} = names_adap_aux(5:end);
end

names_adap_aux = file_names_adap{1};
names_adap_aux = names_adap_aux(1:2);
if sum(names_adap_aux == 'Mi') == 2
    clim_DiD_welf = [0.97 1.03];
    clim_DiD_realgdp = [0.98 1.02];
    axis_welf = [0.855 1.0075];
    axis_realgdp = [0.92 1.005];
elseif sum(names_adap_aux == 'Tr') == 2
    clim_DiD_welf = [0.995 1.005];
    clim_DiD_realgdp = [0.995 1.005];
    axis_welf = [0.89 1.005];
    axis_realgdp = [0.94 1.0025];
elseif sum(names_adap_aux == 'In') == 2
    clim_DiD_welf = [0.92 1.08];
    clim_DiD_realgdp = [0.97 1.03];
    axis_welf = [0.89 1.005];
    axis_realgdp = [0.94 1.0025];
end

// Set numerical parameters
[map_lat,map_lon] = size(map);
aux_lon = linspace(-180,180,map_lon+1);
aux_lon = (aux_lon(1:end-1)+aux_lon(2:end))/2;
aux_lat = linspace(-90,90,map_lat+1); 
aux_lat = (aux_lat(1:end-1)+aux_lat(2:end))/2;
aux_kron = ones(map_lat/180);
year_disp = [100 150 200];

//// 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots for variables

for ind_adap=length_adap/2

for y=1:length(year_disp)
disp(['In ' num2str(2000+year_disp(y)) ' with ' short_names_adap{ind_adap} ...
    ', global population changes in ' ...
    num2str(1e-9*(lbar_w_adap(year_disp(y),ind_adap+length_adap/2)-lbar_w_dam(year_disp(y)))) ...
    ' billions relative to the baseline scenario'])
end
    
// DiD maps for PDV real GDP for different adaptation scenarios
figure
colormap(jet);
imagesc(aux_lon,aux_lat,map.*kron(PDV_realgdp_dam_grid./PDV_realgdp_adap_grid(:,:,ind_adap),aux_kron),...
	'AlphaData',~isnan(map.*kron(PDV_realgdp_dam_grid./PDV_realgdp_adap_grid(:,:,ind_adap),aux_kron)),clim_DiD_realgdp); 
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title(['PDV real GDP, DiD: baseline relative to no warming and ' short_names_adap{ind_adap}])
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.03;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_realgdp_DiD_' file_names_adap{ind_adap} '_beta' num2str(1e3*beta) '.png'])

// DiD maps for welfare for different adaptation scenarios
figure
colormap(jet);
imagesc(aux_lon,aux_lat,map.*kron(PDV_util_dam_grid./PDV_util_adap_grid(:,:,ind_adap),aux_kron),...
	'AlphaData',~isnan(map.*kron(PDV_util_dam_grid./PDV_util_adap_grid(:,:,ind_adap),aux_kron)),clim_DiD_welf);
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title(['Welfare, DiD: baseline relative to no warming and ' short_names_adap{ind_adap}])
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.03;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_util_DiD_' file_names_adap{ind_adap} '_beta' num2str(1e3*beta) '.png'])

end

// Plots for realgdp across adaptation scenarios
legendInfo = cell(length_adap+1,1);
figure
hold on
plot(2001:2000+T,realgdp_w_dam,'color',CM(1,:),'LineWidth',2) 
legendInfo{1} = 'Baseline';
for ind_adap=1:length_adap/2
    hold on
    plot(2001:2000+T,realgdp_w_adap(:,ind_adap),'color',CM(1+ind_adap,:),'LineWidth',2) 
    legendInfo{1+2*ind_adap-1} = long_names_adap{ind_adap};
    hold on
    plot(2001:2000+T,realgdp_w_adap(:,ind_adap+length_adap/2),'--','color',CM(1+ind_adap,:),'LineWidth',2) 
    legendInfo{1+2*ind_adap} = long_names_adap{ind_adap+length_adap/2};
end
legend(legendInfo,'FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
ylim(axis_realgdp)
title(['Real GDP: relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_adap_' names_adap_aux '.png'])

// Plots for welfare across adaptation scenarios
legendInfo = cell(length_adap+1,1);
figure
hold on
plot(2001:2000+T,util_w_dam,'color',CM(1,:),'LineWidth',2) 
legendInfo{1} = 'Baseline';
for ind_adap=1:length_adap/2
    hold on
    plot(2001:2000+T,util_w_adap(:,ind_adap),'color',CM(1+ind_adap,:),'LineWidth',2) 
    legendInfo{1+2*ind_adap-1} = long_names_adap{ind_adap};
    hold on
    plot(2001:2000+T,util_w_adap(:,ind_adap+length_adap/2),'--','color',CM(1+ind_adap,:),'LineWidth',2) 
    legendInfo{1+2*ind_adap} = long_names_adap{ind_adap+length_adap/2};
end
legend(legendInfo,'FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
ylim(axis_welf)
title(['Welfare: relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_adap_' names_adap_aux '.png'])

end