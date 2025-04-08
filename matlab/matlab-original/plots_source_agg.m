
function [] = plots_source_agg( ...
    amen_w_source, prod_w_source, ...
    realgdp_w_source, util_w_source, ...
    PDV_realgdp_source, PDV_util_source, ...
    beta )

% Function that generates the maps and figures of Appendix E.2
% Inputs:
%   amen_w_source, prod_w_source, realgdp_w_source, util_w_source: 
%   global amenities, productivities, real GDP and utility relative to no warming, 
%   for every damage source (only amenities, only productivities and both)
%   PDV_realgdp_source, PDV_util_source: local PDV of real GDP and 
%   utility relative to no warming, for every damage source 
%   (only amenities, only productivities and both)
%   beta: discount factor
            
global H0 pop0 color_olive color_darkgreen color_yellowgreen

% Set numerical parameters
n_plots_kernel = [3 2 1];
n_source = length(n_plots_kernel);
[T,~] = size(amen_w_source);
multi = 1e-3; 
large_number = 1e4;

% Generate kernels
length_kernel_realgdp = NaN(n_source,1);
length_kernel_util = NaN(n_source,1);

f_realgdp = NaN(large_number,n_source);
xi_realgdp = NaN(large_number,n_source);

f_util = NaN(large_number,n_source);
xi_util = NaN(large_number,n_source);

for ind_source=1:n_source
    PDV_realgdp_rel_kron = repelem(PDV_realgdp_source(:,n_plots_kernel(ind_source)),round(multi*pop0(H0>0)));
    [f_realgdp_aux,xi_realgdp_aux] = ksdensity(PDV_realgdp_rel_kron,...
        'Function','pdf','Bandwidth',0.0025); 
    length_kernel_realgdp(ind_source) = length(f_realgdp_aux);
    f_realgdp(1:length_kernel_realgdp(ind_source),ind_source) = f_realgdp_aux;
    xi_realgdp(1:length_kernel_realgdp(ind_source),ind_source) = xi_realgdp_aux;
    
    PDV_util_rel_kron = repelem(PDV_util_source(:,n_plots_kernel(ind_source)),round(multi*pop0(H0>0)));
    [f_util_aux,xi_util_aux] = ksdensity(PDV_util_rel_kron,...
        'Function','pdf','Bandwidth',0.005); 
    length_kernel_util(ind_source) = length(f_util_aux);
    f_util(1:length_kernel_util(ind_source),ind_source) = f_util_aux;
    xi_util(1:length_kernel_util(ind_source),ind_source) = xi_util_aux;
end

% Define colors
if length(n_plots_kernel) == 3
    CM = [color_darkgreen; color_olive; color_yellowgreen];
else
    CM = parula(length(n_plots_kernel));
    CMmiddle = CM((length(n_plots_kernel)+1)/2,:);
    CM(2,:) = CM(3,:);
    CM(3,:) = CMmiddle;
end

name_source_long = {'Baseline' 'Only Amenities' 'Only Productivity'};

%%

% Kernels for PDV realgdp distributions
figure
ind_source_aux = 0;
for ind_source=1:n_source
    ind_ker = n_plots_kernel(ind_source);
    ind_source_aux = ind_source_aux + 1;

    hold on
    plot(xi_realgdp(1:length_kernel_realgdp(ind_source),ind_source),...
        f_realgdp(1:length_kernel_realgdp(ind_source),ind_source),...
        'color',CM(ind_source_aux,:),'LineWidth',2) 
	legendInfo{ind_source_aux} = [name_source_long{ind_ker}];
end
legend(legendInfo,'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['PDV real GDP: baseline relative to no warming'])
% xlim([0.88 1.1])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_realgdp_kernel_source_beta' num2str(1e3*beta) '.png'])

% Kernels for welfare distributions
figure
ind_source_aux = 0;
for ind_source=1:n_source
    ind_ker = n_plots_kernel(ind_source);
    ind_source_aux = ind_source_aux + 1;
 
    hold on
    plot(xi_util(1:length_kernel_util(ind_source),ind_source),...
        f_util(1:length_kernel_util(ind_source),ind_source),...
        'color',CM(ind_source_aux,:),'LineWidth',2) 
	legendInfo{ind_source_aux} = [name_source_long{ind_ker}];
end
legend(legendInfo,'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Welfare: baseline relative to no warming'])
% xlim([0.8 1.3])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_util_kernel_source_beta' num2str(1e3*beta) '.png'])

% Plots for realgdp across damage scenarios
figure
ind_source_aux = 0;
for ind_source=1:n_source
    ind_ker = n_plots_kernel(ind_source);
    ind_source_aux = ind_source_aux + 1;

	hold on
    plot(2001:2000+T,realgdp_w_source(:,ind_ker),...
    'color',CM(ind_source_aux,:),'LineWidth',2) 
	legendInfo{ind_source_aux} = [name_source_long{ind_ker}];
end
legend(legendInfo,'Location','east','FontSize',14) 
set(gcf,'color','w');
set(gca,'FontSize',14)
ylim([0.94 1.005])
title(['Real GDP: baseline relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_source.png'])
 
% Plots for utilities across damage scenarios
figure
ind_source_aux = 0;
for ind_source=1:n_source
    ind_ker = n_plots_kernel(ind_source);
    ind_source_aux = ind_source_aux + 1;

	hold on
    plot(2001:2000+T,util_w_source(:,ind_ker),...
    'color',CM(ind_source_aux,:),'LineWidth',2) 
	legendInfo{ind_source_aux} = [name_source_long{ind_ker}];
end
legend(legendInfo,'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
ylim([0.89 1])
title(['Welfare: baseline relative to no warming'])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_source.png'])
 
end
