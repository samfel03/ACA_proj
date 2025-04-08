
function [] = plots_dam_agg( ...
    amen_w_dam, prod_w_dam, ...
    realgdp_w_dam, util_w_dam, ...
    PDV_realgdp_dam, PDV_util_dam, beta )

// Function that generates the maps and figures of uncertainty of Section
// 4.4 and Appendix E.2.
// Inputs:
// 	amen_w_dam, prod_w_dam, realgdp_w_dam, util_w_dam: 
//   global amenities, productivities, real GDP and utility relative to no warming, 
//   for every level of the damage function
//   PDV_realgdp_dam, PDV_util_dam: local PDV of real GDP and utility 
//   relative to no warming, for every level of the damage function
//   beta: discount factor
            
global H0 pop0 lbar name_dam_long_vect...
    color_olive color_darkgreen color_darkcyan color_yellowgreen 

// Set numerical parameters
n_plots_kernel = [1 9 2];
n_dam = length(n_plots_kernel);
[T,~] = size(amen_w_dam);
multi = 1e-3; 
large_number = 1e4;

// Generate kernels
length_kernel_realgdp = NaN(n_dam,1);
length_kernel_util = NaN(n_dam,1);

f_realgdp = NaN(large_number,n_dam);
xi_realgdp = NaN(large_number,n_dam);

f_util = NaN(large_number,n_dam);
xi_util = NaN(large_number,n_dam);

for ind_dam=1:n_dam
    PDV_realgdp_rel_kron = repelem(PDV_realgdp_dam(:,n_plots_kernel(ind_dam)),round(multi*pop0(H0>0)));
    [f_realgdp_aux,xi_realgdp_aux] = ksdensity(PDV_realgdp_rel_kron,...
        'Function','pdf','Bandwidth',0.0025); 
    length_kernel_realgdp(ind_dam) = length(f_realgdp_aux);
    f_realgdp(1:length_kernel_realgdp(ind_dam),ind_dam) = f_realgdp_aux;
    xi_realgdp(1:length_kernel_realgdp(ind_dam),ind_dam) = xi_realgdp_aux;
    
    PDV_util_rel_kron = repelem(PDV_util_dam(:,n_plots_kernel(ind_dam)),round(multi*pop0(H0>0)));
    [f_util_aux,xi_util_aux] = ksdensity(PDV_util_rel_kron,...
        'Function','pdf','Bandwidth',0.005); 
    length_kernel_util(ind_dam) = length(f_util_aux);
    f_util(1:length_kernel_util(ind_dam),ind_dam) = f_util_aux;
    xi_util(1:length_kernel_util(ind_dam),ind_dam) = xi_util_aux;
end

// Define colors
if length(n_plots_kernel) == 3
    CM = [color_darkgreen; color_yellowgreen; color_olive];
else
    CM = parula(length(n_plots_kernel));
end

year_disp = 200;
disp(['In ' num2str(2000+year_disp) ', the global change in real GDP is: ' num2str(100*(realgdp_w_dam(year_disp,9)-1)) '//, [' num2str(100*(realgdp_w_dam(year_disp,1)-1)) '//,' num2str(100*(realgdp_w_dam(year_disp,2)-1)) '//]'])
disp(['In ' num2str(2000+year_disp) ', the global change in welfare is: ' num2str(100*(util_w_dam(year_disp,9)-1)) '//, [' num2str(100*(util_w_dam(year_disp,1)-1)) '//,' num2str(100*(util_w_dam(year_disp,2)-1)) '//]'])

pop0_sh = pop0(H0>0)/lbar;
disp(['In the worst-scenario, ' num2str(1e2*sum(pop0_sh(PDV_util_dam(:,1)>1))) ...
    '// of the population experiences welfare gains'])
disp(['In the best-scenario, ' num2str(1e2*sum(pop0_sh(PDV_util_dam(:,2)<1))) ...
    '// of the population experiences welfare losses'])

////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plot PDV realgdp and welfare

figure
ind_dam_aux = 0;
for ind_dam=1:n_dam 
    ind_ker = n_plots_kernel(ind_dam);
    ind_dam_aux = ind_dam_aux + 1;

    hold on
    plot(xi_realgdp(1:length_kernel_realgdp(ind_dam),ind_dam),...
        f_realgdp(1:length_kernel_realgdp(ind_dam),ind_dam),...
        'color',CM(ind_dam_aux,:),'LineWidth',2) 
	legendInfo{ind_dam_aux} = [name_dam_long_vect{ind_ker}];
end
legend(legendInfo,'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['PDV real GDP: relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_realgdp_kernel_dam_beta' num2str(1e3*beta) '.png'])

figure
ind_dam_aux = 0;
for ind_dam=1:n_dam 
    ind_ker = n_plots_kernel(ind_dam);
    ind_dam_aux = ind_dam_aux + 1;
 
    hold on
    plot(xi_util(1:length_kernel_util(ind_dam),ind_dam),...
        f_util(1:length_kernel_util(ind_dam),ind_dam),...
        'color',CM(ind_dam_aux,:),'LineWidth',2) 
	legendInfo{ind_dam_aux} = [name_dam_long_vect{ind_ker}];
end
legend(legendInfo,'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Welfare: relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_util_kernel_dam_beta' num2str(1e3*beta) '.png'])

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plot realgdp and welfare across damage scenarios

figure
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[realgdp_w_dam(:,1); flipud(realgdp_w_dam(:,2))],'FaceColor',color_darkgreen,'EdgeColor','none','facealpha',.10);
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[realgdp_w_dam(:,3); flipud(realgdp_w_dam(:,4))],'FaceColor',color_darkgreen,'EdgeColor','none','facealpha',.15);
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[realgdp_w_dam(:,5); flipud(realgdp_w_dam(:,6))],'FaceColor',color_darkgreen,'EdgeColor','none','facealpha',.20);
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[realgdp_w_dam(:,7); flipud(realgdp_w_dam(:,8))],'FaceColor',color_darkgreen,'EdgeColor','none','facealpha',.25);
hold on
plot(2001:2000+T,realgdp_w_dam(:,9),'color',color_darkgreen,'LineWidth',2) 
[~,h_legend] = legend('95// interval','90// interval','80// interval','60// interval',...
        'Location','northeast','FontSize',14);
PatchInLegend = findobj(h_legend,'type','patch');
set(gca,'FontSize',14)
set(gcf,'color','w')
set(PatchInLegend(1),'facealpha',1.5*0.10)
set(PatchInLegend(2),'facealpha',1.65*0.15)
set(PatchInLegend(3),'facealpha',1.8*0.20)
set(PatchInLegend(4),'facealpha',1.95*0.25)
title(['Real GDP: relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_area_dam.png'])

figure
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[util_w_dam(:,1); flipud(util_w_dam(:,2))],'FaceColor',color_darkcyan,'EdgeColor','none','facealpha',.10);
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[util_w_dam(:,3); flipud(util_w_dam(:,4))],'FaceColor',color_darkcyan,'EdgeColor','none','facealpha',.15);
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[util_w_dam(:,5); flipud(util_w_dam(:,6))],'FaceColor',color_darkcyan,'EdgeColor','none','facealpha',.20);
hold on
patch('XData',[2001:2000+T fliplr(2001:2000+T)], ...
    'YData',[util_w_dam(:,7); flipud(util_w_dam(:,8))],'FaceColor',color_darkcyan,'EdgeColor','none','facealpha',.25);
hold on
plot(2001:2000+T,util_w_dam(:,9),'color',color_darkcyan,'LineWidth',2) 
[~,h_legend] = legend('95// interval','90// interval','80// interval','60// interval',...
        'Location','northeast','FontSize',14);
PatchInLegend = findobj(h_legend,'type','patch');
ylim([0.78 1.03])
set(gca,'FontSize',14)
set(gcf,'color','w')
set(PatchInLegend(1),'facealpha',1.5*0.10)
set(PatchInLegend(2),'facealpha',1.65*0.15)
set(PatchInLegend(3),'facealpha',1.8*0.20)
set(PatchInLegend(4),'facealpha',1.95*0.25)
title(['Welfare: relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_area_dam.png'])

end

