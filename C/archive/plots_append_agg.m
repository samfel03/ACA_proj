
function [] = plots_append_agg( ind_dam, ...
    taxCO2_val, subclean_val, names_taxes, names_abat, ... 
    name_app, app_vector, ind_app_bench, ...
    realgdp_w_app, util_w_app, ...
    PDV_realgdp_app, PDV_util_app, ...
    emiCO2_total_app, temp_global_app, clean_total_app )
 
// Function that generates the maps and figures for different elasticities 
// of substitution between fossil fuels and clean energy and sizes of 
// carbon deposits of Supplementary Materials Sections G.4 and G.5.
// Inputs:
//   ind_dam: level of the damage function, 9 is the baseline.
//   taxCO2_val, subclean_val, names_taxes, names_abat: 
//   labels for carbon taxes, clean energy subsidies and abatement.
//   name_app, app_vect, ind_app_bench: labels for values of 
//   elasticities of energy substitution or sizes of fossil fuel deposits.
//   realgdp_w_app, util_w_app: global real GDP and utility relative 
//   to no warming.
//   PDV_realgdp_app, PDV_util_app: local PDV of rela GDP and 
//   utility relative to no warming.
//   emiCO2_total_app, temp_global_app, clean_total_app: 
//   total CO2 emissions, temperature and clean energy use.
            
global map pop0 H0 tCO2_toe conv_usd emi_no_ff cost_emi_param...
    emiCO2_RCP temp_global_RCP name_dam_vect temp_preind...
    color_greenyellow color_yellowgreen color_darkgreen color_darkcyan
 
// Set names
name_dam = name_dam_vect{ind_dam};
n_app = length(app_vector);
[T,~] = size(realgdp_w_app);

// Generate kernels
multi = 1e-3; 
large_number = 1e4;

length_kernel_realgdp = NaN(n_app,1);
length_kernel_util = NaN(n_app,1);
 
f_realgdp = NaN(large_number,n_app);
xi_realgdp = NaN(large_number,n_app);
 
f_util = NaN(large_number,n_app);
xi_util = NaN(large_number,n_app);
 
PDV_realgdp_app_grid = NaN(180,360,n_app);
PDV_util_app_grid = NaN(180,360,n_app);
 
for ind_app=1:n_app
    PDV_realgdp_app_kron = repelem(PDV_realgdp_app(:,ind_app,1),round(multi*pop0(H0>0)));
    [f_realgdp_aux,xi_realgdp_aux] = ksdensity(PDV_realgdp_app_kron,...
        'Function','pdf','Bandwidth',0.0025); 
    length_kernel_realgdp(ind_app) = length(f_realgdp_aux);
    f_realgdp(1:length_kernel_realgdp(ind_app),ind_app) = f_realgdp_aux;
    xi_realgdp(1:length_kernel_realgdp(ind_app),ind_app) = xi_realgdp_aux;
    
    PDV_util_app_kron = repelem(PDV_util_app(:,ind_app,1),round(multi*pop0(H0>0)));
    [f_util_aux,xi_util_aux] = ksdensity(PDV_util_app_kron,...
        'Function','pdf','Bandwidth',0.0035); 
    length_kernel_util(ind_app) = length(f_util_aux);
    f_util(1:length_kernel_util(ind_app),ind_app) = f_util_aux;
    xi_util(1:length_kernel_util(ind_app),ind_app) = xi_util_aux;
    
    PDV_realgdp_app_grid_aux = NaN(180,360);
    PDV_realgdp_app_grid_aux(H0>0) = PDV_realgdp_app(:,ind_app,1);
    PDV_realgdp_app_grid(:,:,ind_app) = PDV_realgdp_app_grid_aux;
 
    PDV_util_app_grid_aux = NaN(180,360);
    PDV_util_app_grid_aux(H0>0) = PDV_util_app(:,ind_app,1);
    PDV_util_app_grid(:,:,ind_app) = PDV_util_app_grid_aux;
end

// Construct extraction functions
if n_app == 3
cost_CO2_data = csvread('Data/CO2_cost.csv');
costCO2_fct_lala =@(cumCO2,maxCO2_val) ...
    cost_emi_param(1)./(cost_emi_param(2) + exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
    cost_emi_param(5)*(maxCO2_val./(cumCO2-maxCO2_val)).^cost_emi_param(7);
costCO2_fct_arg = repmat((0:100:45000)',1,n_app);
costCO2_fct_val = NaN(length(costCO2_fct_arg),n_app);
costCO2_fct_time = NaN(T,n_app);
cumCO2_CC = cumsum(emiCO2_total_app-repmat(emi_no_ff(1:T),1,n_app),1);
name_app_lat = 'maxCO2';
for ind_app=1:n_app
    costCO2_fct_val(:,ind_app) = costCO2_fct_lala(costCO2_fct_arg(:,ind_app),app_vector(ind_app));
    costCO2_fct_val(costCO2_fct_arg(:,ind_app)>=app_vector(ind_app),ind_app) = NaN;
    costCO2_fct_arg(costCO2_fct_arg(:,ind_app)>=app_vector(ind_app),ind_app) = NaN;
    costCO2_fct_time(:,ind_app) = costCO2_fct_lala(cumCO2_CC(:,ind_app),app_vector(ind_app));
end
else
name_app_lat = '\epsilon';    
end

// Define colors
if n_app == 3
    CM = [color_greenyellow; color_yellowgreen; color_darkgreen];
    clim_realgdp = [0.95 1.05];
    clim_welfare = [0.95 1.05];
    if taxCO2_val == 0 && subclean_val == 0
        clim_realgdp = [0.94 1.06];
        clim_welfare = [0.9 1.1];
        ylim_realgdp = [0.88 1.01];
        ylim_welfare = [0.78 1];
    elseif taxCO2_val ~= 0
        clim_realgdp = [0.998 1.01];
        clim_welfare = [0.98 1.02];
        ylim_realgdp = [0.92 1.1];
        ylim_welfare = [0.93 1.09];
    elseif subclean_val ~= 0
        clim_realgdp = [1.002 1.012];
        clim_welfare = [1.002 1.006];
        ylim_realgdp = [1 1.22];
        ylim_welfare = [1 1.12];
    end
elseif n_app == 4
    CM = [color_greenyellow; color_yellowgreen; color_darkcyan; color_darkgreen];
    if taxCO2_val == 0 && subclean_val == 0
        clim_realgdp = [0.97 1.03];
        clim_welfare = [0.95 1.05];
        ylim_realgdp = [0.935 1];
        ylim_welfare = [0.885 1];
    elseif taxCO2_val ~= 0
        clim_realgdp = [0.95 1.01];
        clim_welfare = [0.95 1.05];
        ylim_realgdp = [0.92 1.08];
        ylim_welfare = [0.93 1.07];
    elseif subclean_val ~= 0
        clim_realgdp = [0.82 1.02];
        clim_welfare = [0.88 1.02];
        ylim_realgdp = [0.95 1.3];
        ylim_welfare = [0.95 1.25];
    end
else
    CM = parula(n_app);
end

// Define title names
if taxCO2_val == 0 && subclean_val == 0
    title_DiD_name = 'baseline relative to no warming';
    title_DiD_sh_name = title_DiD_name;
    title_clim_name = '';
elseif taxCO2_val ~= 0
    title_DiD_name = ['carbon tax ' num2str(100*taxCO2_val) '// relative to no tax'];
    title_DiD_sh_name = title_DiD_name;
    if strcmp(name_app,'_maxCO2') == 1
    title_DiD_sh_name = ['tax ' num2str(100*taxCO2_val) '// relative to no tax'];
    end
    title_clim_name = [': carbon tax ' num2str(100*taxCO2_val) '//'];
elseif subclean_val ~= 0
    title_DiD_name = ['clean subsidy ' num2str(100*subclean_val) '// relative to no subsidy'];
    title_DiD_sh_name = title_DiD_name;
    if strcmp(name_app,'_maxCO2') == 1
    title_DiD_sh_name = ['sub ' num2str(100*subclean_val) '// relative to no sub'];
    end
    title_clim_name = [': clean subsidy ' num2str(100*subclean_val) '//'];
end

// Set numerical parameters
[map_lat,map_lon] = size(map);
aux_lon = linspace(-180,180,map_lon+1);
aux_lon = (aux_lon(1:end-1)+aux_lon(2:end))/2;
aux_lat = linspace(-90,90,map_lat+1); 
aux_lat = (aux_lat(1:end-1)+aux_lat(2:end))/2;
aux_kron = ones(map_lat/180);

////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plots

// CO2 emissions
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,emiCO2_total_app(1:T,ind_app,1),'color',CM(ind_app,:),...
        'LineWidth',2) 
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,1),'k--',...
    'LineWidth',2) 
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,2),'k:',...
    'LineWidth',2) 
legendInfo{n_app+1} = ['IPCC (RCP 8.5)'];
legendInfo{n_app+2} = ['IPCC (RCP 6.0)'];
legend(legendInfo{1:n_app+2},'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['CO2 emissions (GtCO2/year)' title_clim_name])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/emiCO2_' name_dam names_taxes name_app '.png'])

if strcmp(names_abat,'') ~= 1
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,emiCO2_total_app(1:T,ind_app,1),'color',CM(ind_app,:),...
        'LineWidth',2) 
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,1),'k--',...
    'LineWidth',2) 
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,2),'k:',...
    'LineWidth',2) 
legendInfo{n_app+1} = ['IPCC (RCP 8.5)'];
legendInfo{n_app+2} = ['IPCC (RCP 6.0)'];
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,emiCO2_total_app(1:T,ind_app,2),'color',CM(ind_app,:),...
        'LineStyle','--','LineWidth',2) 
end    
legend(legendInfo{1:n_app+2},'Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['CO2 emissions (GtCO2/year)' title_clim_name])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/emiCO2_' name_dam names_taxes names_abat name_app '.png'])
end
 
// Global temperature
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,temp_global_app(1:T,ind_app,1)-temp_preind,'color',CM(ind_app,:),...
        'LineWidth',2) 
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
hold on
plot(2001:2000+T,temp_global_RCP(1:T,1)-temp_preind,'k--',...
    'LineWidth',2) 
hold on
plot(2001:2000+T,temp_global_RCP(1:T,2)-temp_preind,'k:',...
    'LineWidth',2) 
legendInfo{n_app+1} = ['IPCC (RCP 8.5)'];
legendInfo{n_app+2} = ['IPCC (RCP 6.0)'];
if taxCO2_val ~= 0 && strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app+2},'Location','southwest','FontSize',14)
elseif subclean_val ~= 0 && strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app+2},'Location','southeast','FontSize',14)
elseif strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app+2},'Location','southeast','FontSize',14)
else
legend(legendInfo{1:n_app+2},'Location','northwest','FontSize',13.2)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Global temperature (C) relative to pre-industrial level' title_clim_name])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/temp_global_' name_dam names_taxes name_app '.png'])
 
if strcmp(names_abat,'') ~= 1
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,temp_global_app(1:T,ind_app,1)-temp_preind,'color',CM(ind_app,:),...
        'LineWidth',2) 
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
hold on
plot(2001:2000+T,temp_global_RCP(1:T,1)-temp_preind,'k--',...
    'LineWidth',2) 
hold on
plot(2001:2000+T,temp_global_RCP(1:T,2)-temp_preind,'k:',...
    'LineWidth',2) 
legendInfo{n_app+1} = ['IPCC (RCP 8.5)'];
legendInfo{n_app+2} = ['IPCC (RCP 6.0)'];
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,temp_global_app(1:T,ind_app,2)-temp_preind,'color',CM(ind_app,:),...
        'LineStyle','--','LineWidth',2) 
end    
if taxCO2_val ~= 0 && strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app+2},'Location','southwest','FontSize',14)
elseif subclean_val ~= 0 && strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app+2},'Location','southeast','FontSize',14)
elseif strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app+2},'Location','southeast','FontSize',14)
else
legend(legendInfo{1:n_app+2},'Location','northwest','FontSize',13.2)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Global temperature (C) relative to pre-industrial level' title_clim_name])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/temp_global_' name_dam names_taxes names_abat name_app '.png'])
end

// Kernels for real GDP distributions
figure
for ind_app=1:n_app
    hold on
    plot(xi_realgdp(1:length_kernel_realgdp(ind_app),ind_app),...
        f_realgdp(1:length_kernel_realgdp(ind_app),ind_app),...
        'color',CM(ind_app,:),'LineWidth',2) 
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
if strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
else
legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['PDV real GDP: ' title_DiD_name])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/kernel_realgdp_' name_dam names_taxes name_app '.png'])
 
// Kernels for welfare distributions
figure
for ind_app=1:n_app
    hold on
    plot(xi_util(1:length_kernel_util(ind_app),ind_app),...
        f_util(1:length_kernel_util(ind_app),ind_app),...
        'color',CM(ind_app,:),'LineWidth',2) 
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
if strcmp(name_app,'_eps') == 1
legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
else
legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Welfare: ' title_DiD_name])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/kernel_util_' name_dam names_taxes name_app '.png'])
 
// Plot for global damage function for real GDP
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,realgdp_w_app(1:T,ind_app,1),...
        'color',CM(ind_app,:),'LineWidth',2)
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
if taxCO2_val ~= 0  
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
legend(legendInfo{1:n_app},'Location','southeast','FontSize',14)   
elseif subclean_val ~= 0
    if strcmp(name_app,'_maxCO2') == 1 
    legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
    else
    legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
    end
else
legend(legendInfo{1:n_app},'Location','southwest','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Real GDP: ' title_DiD_name])
ylim(ylim_realgdp)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_' name_dam names_taxes name_app '.png'])

if strcmp(names_abat,'') ~= 1
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,realgdp_w_app(1:T,ind_app,1),...
        'color',CM(ind_app,:),'LineWidth',2)
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,realgdp_w_app(1:T,ind_app,2),...
        'color',CM(ind_app,:),'LineStyle','--','LineWidth',2) 
end    
if taxCO2_val ~= 0
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
legend(legendInfo{1:n_app},'Location','southeast','FontSize',14)  
elseif subclean_val ~= 0
    if strcmp(name_app,'_maxCO2') == 1 
    legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
    else
    legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
    end
else
legend(legendInfo{1:n_app},'Location','southwest','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Real GDP: ' title_DiD_name])
ylim(ylim_realgdp)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_' name_dam names_taxes names_abat name_app '.png'])
end

// Plot for global damage function for welfare
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,util_w_app(1:T,ind_app,1),...
        'color',CM(ind_app,:),'LineWidth',2)
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
if taxCO2_val ~= 0
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
legend(legendInfo{1:n_app},'Location','southeast','FontSize',14) 
elseif subclean_val ~= 0
    if strcmp(name_app,'_maxCO2') == 1 
    legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
    else
    legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
    end
else
legend(legendInfo{1:n_app},'Location','southwest','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Welfare: ' title_DiD_name])
ylim(ylim_welfare)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_' name_dam names_taxes name_app '.png'])
 
if strcmp(names_abat,'') ~= 1
figure
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,util_w_app(1:T,ind_app,1),...
        'color',CM(ind_app,:),'LineWidth',2)
    legendInfo{ind_app} = ['Model, ' name_app_lat '=' num2str(app_vector(ind_app))];
end
for ind_app=1:n_app
    hold on
    plot(2001:2000+T,util_w_app(1:T,ind_app,2),...
        'color',CM(ind_app,:),'LineStyle','--','LineWidth',2) 
end    
if taxCO2_val ~= 0
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
legend(legendInfo{1:n_app},'Location','southeast','FontSize',14)
elseif subclean_val ~= 0
    if strcmp(name_app,'_maxCO2') == 1 
    legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
    else
    legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
    end
else
legend(legendInfo{1:n_app},'Location','southwest','FontSize',14)
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Welfare: ' title_DiD_name])
ylim(ylim_welfare)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_' name_dam names_taxes names_abat name_app '.png'])
end
 
// Map for Diff-in-Diff PDV real GDP
figure
colormap(jet);
imagesc(aux_lon,aux_lat,...
	map.*kron(PDV_realgdp_app_grid(:,:,ind_app_bench)./PDV_realgdp_app_grid(:,:,n_app),aux_kron),...
    'AlphaData',~isnan(map.*kron(PDV_realgdp_app_grid(:,:,ind_app_bench)./PDV_realgdp_app_grid(:,:,n_app),aux_kron)),clim_realgdp); //[0.95 1.05],[0.85 1.15]
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title(['PDV real GDP DiD: ' title_DiD_sh_name ' and ' name_app_lat '=' num2str(app_vector(n_app))])
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.035;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_realgdp_' name_dam names_taxes name_app '.png'])

// Maps for Diff-in-Diff welfare 
figure
colormap(jet);
imagesc(aux_lon,aux_lat,...
	map.*kron(PDV_util_app_grid(:,:,ind_app_bench)./PDV_util_app_grid(:,:,n_app),aux_kron),...
    'AlphaData',~isnan(map.*kron(PDV_util_app_grid(:,:,ind_app_bench)./PDV_util_app_grid(:,:,n_app),aux_kron)),clim_welfare); //[0.92 1.08],[0.85 1.15]
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title(['Welfare DiD: ' title_DiD_sh_name ' and ' name_app_lat '=' num2str(app_vector(n_app))])
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.04;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/PDV_util_' name_dam names_taxes name_app '.png'])

if strcmp(name_app,'_maxCO2') == 1 && taxCO2_val == 0 && subclean_val == 0

// Extraction cost function
figure
for ind_app=1:n_app
    hold on
    semilogy(costCO2_fct_arg(:,ind_app),(1/conv_usd)*costCO2_fct_val(:,ind_app),'color',CM(ind_app,:),...
        'LineWidth',2)
    legendInfo{ind_app} = ['Model, maxCumCO2 = ' num2str(app_vector(ind_app))];
end
legend(legendInfo{1:n_app},'Location','northeast','FontSize',14)
ylim([0 1e6]) 
title('Extraction cost function')
xlabel(['Cumulative emissions (GtCO2)'])
ylabel(['usd/tCO_2'])
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
saveas(gcf,['Maps and Figures/extraction_cost_maxCO2.png'])

// Extraction cost function
figure
for ind_app=1:n_app
    hold on
    semilogy(2001:2000+T,(1/conv_usd)*costCO2_fct_time(:,ind_app),'color',CM(ind_app,:),...
        'LineWidth',2)
    legendInfo{ind_app} = ['Model, maxCumCO2 = ' num2str(app_vector(ind_app))];
end
legend(legendInfo{1:n_app},'Location','northwest','FontSize',14)
ylim([0 1e6]) 
title('Extraction cost over time')
ylabel(['usd/tCO_2'])
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
saveas(gcf,['Maps and Figures/extraction_cost_time_maxCO2.png'])

end

end
