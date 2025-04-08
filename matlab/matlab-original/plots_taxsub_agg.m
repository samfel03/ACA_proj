
function [] = ...
    plots_taxsub_agg( ind_dam, ...
    emiCO2_total_Warm, emiCO2_total_Warm_tax, ...
    clean_total_Warm, clean_total_Warm_tax, ...
    temp_global_Warm, temp_global_Warm_tax, ...
    realgdp_w_CC_tax_vect, util_w_CC_tax_vect, ...
    taxCO2_vect, subclean_vect, names_taxes, names_abat )

% Function that generates the maps and figures of carbon taxes, 
% abatement and clean energy subsidies of Section 6, Appendices E.4 and E.5 
% and Supplementary Materials Sections G.2, H.2 and J
% Inputs:
%   ind_dam: level of the damage function, 9 is the baseline
%   emiCO2_total_Warm, clean_total_Warm, temp_global_Warm: 
%   climate variables with no environmental policy
%   emiCO2_total_Warm_tax, clean_total_Warm_tax, temp_global_Warm_tax: 
%   climate variables with environmental policy
%   realgdp_w_Warm_tax, util_w_Warm_tax: global real GDP and 
%   utility relative to no environmental policy
%   taxCO2_vect, subclean_vect, names_taxes, names_abat: 
%   labels for carbon taxes, clean energy subsidies and abatement

global name_dam_vect tCO2_toe...
    emiCO2_RCP temp_preind temp_global_RCP...
    color_olive color_darkgreen color_darkcyan color_yellowgreen 

% Define variables
length_tax = length(taxCO2_vect);
length_sub = length(subclean_vect);
[T,~] = size(emiCO2_total_Warm);

% Set names
name_dam = name_dam_vect{ind_dam};

% Define colors
if length_tax*length_sub == 3
    CM = [color_olive; color_darkcyan; color_darkgreen];
else
    CM = parula(length_tax*length_sub);
end

% Define axis
if taxCO2_vect == 0
    if ind_dam == 9
        axis_realgdp = [1 1.22];
        axis_welfare = [1 1.12];
    elseif ind_dam == 1
        axis_realgdp = [1 1.22];
        axis_welfare = [1 1.12];
    end
    title_realgdp = ['Real GDP: relative to no clean subsidy'];
    title_welfare = ['Welfare: relative to no clean subsidy'];
elseif subclean_vect == 0
    if ind_dam == 9
        axis_realgdp = [0.9 1.05];
        axis_welfare = [0.93 1.035];
        if strcmp(names_abat,'') ~= 1
            axis_realgdp_abat = [0.92 1.08];
            axis_welfare_abat = [0.94 1.06];
        if strcmp(names_abat(end-2:end),'all') == 1
            axis_realgdp_abat = [0.92 1.12];
            axis_welfare_abat = [0.94 1.18];
        end
        else
            axis_realgdp = [0.9 1.05];
            axis_welfare = [0.93 1.035];
        end
    elseif ind_dam == 1
        axis_realgdp = [0.92 1.1066];
        axis_welfare = [0.94 1.08];
        if strcmp(names_abat,'') ~= 1
            axis_realgdp_abat = [0.92 1.125];
            axis_welfare_abat = [0.94 1.1];
        if strcmp(names_abat(end-2:end),'all') == 1
            axis_realgdp_abat = [0.92 1.12];
            axis_welfare_abat = [0.94 1.18];
        end
        else
            axis_realgdp = [0.9 1.05];
            axis_welfare = [0.94 1.03];
        end
    end
    if strcmp(names_abat(end-2:end),'all') == 1
    title_realgdp = ['Real GDP: relative to no carbon tax and no abatement'];
    title_welfare = ['Welfare: relative to no carbon tax and no abatement'];
    else
    title_realgdp = ['Real GDP: relative to no carbon tax'];
    title_welfare = ['Welfare: relative to no carbon tax'];
    end
else
    axis_realgdp = [0.9 1.22];
    axis_welfare = [0.94 1.132];
    title_realgdp = ['Real GDP: relative to no taxes'];
    title_welfare = ['Welfare: relative to no taxes'];
end

axis_temp = [0 9];
if strcmp(names_abat,'') ~= 1
    axis_temp_abat = [0 8];
end    

if strcmp(names_abat,'') == 1
    LineSt = '--';
else
    if strcmp(names_abat(end-2:end),'all') == 1
        LineSt = ':';
    else
        LineSt = '--';
    end
end

year_disp = [1 200];

%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot climate variables

for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        disp(['With a carbon tax of ' num2str(100*taxCO2_vect(ind_tax)) ...
            '% and a clean energy subsidy of ' num2str(100*subclean_vect(ind_sub)) '%:'])
        for y=1:length(year_disp)
            disp(['In ' num2str(2000+year_disp(y)) ', CO2 emissions change ' num2str(emiCO2_total_Warm_tax(year_disp(y),ind_tax,ind_sub,1)-emiCO2_total_Warm(year_disp(y))) ...
                ' GtCO2 (' num2str(100*(emiCO2_total_Warm_tax(year_disp(y),ind_tax,ind_sub,1)/emiCO2_total_Warm(year_disp(y))-1)) '%) relative to the baseline scenario'])
        end
        [max_emiCO2,argmax_emiCO2] = max(emiCO2_total_Warm_tax(1:T,ind_tax,ind_sub,1));
        disp(['CO2 emissions reach a peak of ' num2str(max_emiCO2) ...
            ' GtCO2 in the year ' num2str(2000+argmax_emiCO2)])  
    end
end

% CO2 Emissions
figure
hold on
plot(2001:2000+T,emiCO2_total_Warm(1:T,1),'color',color_yellowgreen,...
    'LineWidth',2) 
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,1),'k--',...
    2001:2000+T,emiCO2_RCP(1:T,2),'k:',...
    'LineWidth',2) 
legendInfo{1} = 'Model';
legendInfo{2} = 'IPCC (RCP 8.5)';
legendInfo{3} = 'IPCC (RCP 6.0)';
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        hold on
        plot(2001:2000+T,emiCO2_total_Warm_tax(1:T,ind_tax,ind_sub,1),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
legend(legendInfo,'FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
title('CO2 emissions (GtCO2/year)')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/emiCO2_' name_dam '_' names_taxes '.png'])

if strcmp(names_abat,'') ~= 1
figure
hold on
plot(2001:2000+T,emiCO2_total_Warm(1:T,1),'color',color_yellowgreen,...
    'LineWidth',2) 
hold on
plot(2001:2000+T,emiCO2_RCP(1:T,1),'k--',...
    2001:2000+T,emiCO2_RCP(1:T,2),'k:',...
    'LineWidth',2) 
legendInfo{1} = 'Model';
legendInfo{2} = 'IPCC (RCP 8.5)';
legendInfo{3} = 'IPCC (RCP 6.0)';
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        hold on
        plot(2001:2000+T,emiCO2_total_Warm_tax(1:T,ind_tax,ind_sub,1),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
hold on
plot(2001:2000+T,emiCO2_total_Warm(1:T,2),'color',color_yellowgreen,...
    'LineStyle','--','LineWidth',2) 
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        hold on
        plot(2001:2000+T,emiCO2_total_Warm_tax(1:T,ind_tax,ind_sub,2),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineStyle','--','LineWidth',2) 
    end
end
legend(legendInfo,'FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
title('CO2 emissions (GtCO2/year)')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/emiCO2_' name_dam '_' names_taxes names_abat '.png'])
end

for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        disp(['With a carbon tax of ' num2str(100*taxCO2_vect(ind_tax)) ...
            '% and a clean energy subsidy of ' num2str(100*subclean_vect(ind_sub)) '%:'])
        [max_temp,argmax_temp] = max(temp_global_Warm_tax(1:T,ind_tax,ind_sub,1));
        disp(['Temperature reaches a peak of ' num2str(max_temp-temp_preind) ...
            'ºC in the year ' num2str(2000+argmax_temp)])  
    end
end

% Global temperature
figure
hold on
plot(2001:2000+T,temp_global_Warm(1:T,1)-temp_preind,'color',color_yellowgreen,...
    'LineWidth',2)
hold on
plot(2001:2000+T,temp_global_RCP(1:T,1)-temp_preind,'k--',...
    2001:2000+T,temp_global_RCP(1:T,2)-temp_preind,'k:',...
    'LineWidth',2)
legendInfo{1} = 'Model';
legendInfo{2} = 'IPCC (RCP 8.5)';
legendInfo{3} = 'IPCC (RCP 6.0)';
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        hold on
        plot(2001:2000+T,temp_global_Warm_tax(1:T,ind_tax,ind_sub,1)-temp_preind,...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
legend(legendInfo,'Location','southeast','FontSize',14)
ylim(axis_temp)
set(gca,'FontSize',14)
set(gcf,'color','w')
title('Global temperature (C) relative to pre-industrial level')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/temp_global_' name_dam '_' names_taxes '.png'])

if strcmp(names_abat,'') ~= 1
figure
hold on
plot(2001:2000+T,temp_global_Warm(1:T,1)-temp_preind,'color',color_yellowgreen,...
    'LineWidth',2)
hold on
plot(2001:2000+T,temp_global_RCP(1:T,1)-temp_preind,'k--',...
    2001:2000+T,temp_global_RCP(1:T,2)-temp_preind,'k:',...
    'LineWidth',2)
legendInfo{1} = 'Model';
legendInfo{2} = 'IPCC (RCP 8.5)';
legendInfo{3} = 'IPCC (RCP 6.0)';
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        hold on
        plot(2001:2000+T,temp_global_Warm_tax(1:T,ind_tax,ind_sub,1)-temp_preind,...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{3+(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
hold on
plot(2001:2000+T,temp_global_Warm(1:T,2)-temp_preind,'color',color_yellowgreen,...
    'LineStyle','--','LineWidth',2)
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
        hold on
        plot(2001:2000+T,temp_global_Warm_tax(1:T,ind_tax,ind_sub,2)-temp_preind,...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineStyle','--','LineWidth',2) 
    end
end
if strcmp(names_abat,'_abat2200_100pp') == 1
legend(legendInfo,'Location','southeast','FontSize',14)
else
legend(legendInfo,'Location','east','FontSize',14)
end
ylim(axis_temp_abat)
set(gca,'FontSize',14)
set(gcf,'color','w')
title('Global temperature (C) relative to pre-industrial level')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/temp_global_' name_dam '_' names_taxes names_abat '.png'])
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot realgdp and welfare

% Plot for global damage function for realgdp
figure
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
    hold on
    plot(2001:2000+T,...
        realgdp_w_CC_tax_vect(:,ind_tax,ind_sub,1),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
if taxCO2_vect ~= 0 
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
end
legend(legendInfo{1:length_tax*length_sub},'Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(title_realgdp)
ylim(axis_realgdp)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_' name_dam '_' names_taxes '.png'])

if strcmp(names_abat,'') ~= 1
figure
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
    hold on
    plot(2001:2000+T,...
        realgdp_w_CC_tax_vect(:,ind_tax,ind_sub,1),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
    hold on
    plot(2001:2000+T,...
        realgdp_w_CC_tax_vect(:,ind_tax,ind_sub,2),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineStyle',LineSt,'LineWidth',2) 
    end
end
if taxCO2_vect ~= 0 
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
end
legend(legendInfo{1:length_tax*length_sub},'Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(title_realgdp)
ylim(axis_realgdp_abat)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/realgdp_' name_dam '_' names_taxes names_abat '.png'])
end

% Plot for global damage function for welfare
figure
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
    hold on
    plot(2001:2000+T,...
        util_w_CC_tax_vect(:,ind_tax,ind_sub,1),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
if taxCO2_vect ~= 0
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
end
legend(legendInfo{1:length_tax*length_sub},'Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(title_welfare)
ylim(axis_welfare)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_' name_dam '_' names_taxes '.png'])

if strcmp(names_abat,'') ~= 1
figure
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
    hold on
    plot(2001:2000+T,...
        util_w_CC_tax_vect(:,ind_tax,ind_sub,1),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineWidth',2) 
    if taxCO2_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, clean subsidy ' num2str(100*subclean_vect(ind_sub)) '%'];
    elseif subclean_vect == 0
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, carbon tax ' num2str(100*taxCO2_vect(ind_tax)) '%'];
    else
        legendInfo{(ind_sub-1)*length_tax+ind_tax} = ['Model, tax ' num2str(100*taxCO2_vect(ind_tax)) '%, sub ' num2str(100*subclean_vect(ind_sub)) '%'];
    end
    end
end
for ind_sub=1:length_sub
    for ind_tax=1:length_tax
    hold on
    plot(2001:2000+T,...
        util_w_CC_tax_vect(:,ind_tax,ind_sub,2),...
        'color',CM((ind_sub-1)*length_tax+ind_tax,:),'LineStyle',LineSt,'LineWidth',2) 
    end
end
if taxCO2_vect ~= 0
hold on
plot(2001:2000+T,ones(T,1),'k:','LineWidth',2) 
end
legend(legendInfo{1:length_tax*length_sub},'Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(title_welfare)
ylim(axis_welfare_abat)
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/util_' name_dam '_' names_taxes names_abat '.png'])
end

end
