
function [] = plots_backward( ind_dam )

% Function that generates the maps and figures of the natality function, 
% historical population and energy use of Section 3.3 and Appendix B.1 and C
% Input:
% 	ind_dam: level of the damage function, with values from 1 to 9, 
%   9 is the baseline

global emi_ff_data emi_ff_data_tend clean_energy_data scaler_temp...
    map H0 H n C_vect length_C_vect temp0_local...
    lbar pop_med_hist tCO2_toe name_dam_vect...
    natal_data pop_data year_data cost_CO2_data cost_emi_param conv_usd...
    color_olive color_darkgreen color_yellowgreen natal_param HDI0

% Assign names
name_dam = name_dam_vect{ind_dam};

% Load parameters
data_n = load('Data/derived/natal_migr_Warm_med.mat');
coeff_pop = data_n.coeff_pop_i;
m2 = data_n.m2_i;

% Load backward solution
data_b = load(['Data/derived/results_backward_Warm_' name_dam '.mat']);
l_Warm_b = data_b.l_Warm_b;
emiCO2_ff_Warm_b = data_b.emiCO2_ff_Warm_b;
clean_Warm_b = data_b.clean_Warm_b;
realgdp_Warm_b = data_b.realgdp_Warm_b;
temp_local_Warm_b = data_b.temp_local_Warm_b;
net_births_Warm_b = data_b.net_births_Warm_b;

data_20 = load('Data/derived/results20_med.mat');
l0_model = data_20.l0_model;
realgdp0_model = data_20.realgdp0_model;
realgdp0_w_model = sum(realgdp0_model.*l0_model.*H)/lbar;

% Global CO2 emi, clean energy, pop
[~,T_back] = size(emiCO2_ff_Warm_b);
emi_ff_model = sum(fliplr(emiCO2_ff_Warm_b).*repmat(H,1,T_back))';
clean_model = sum(fliplr(clean_Warm_b).*repmat(H,1,T_back))';
l_model = sum(fliplr(l_Warm_b).*repmat(H,1,T_back))';

% Create natality rates for year 2000 at the cell level from model
natal_model0_cell = natal_fct(log(realgdp0_model),temp0_local,log(realgdp0_w_model),...
	coeff_pop);

% Create natality rates for year 2000 at the country level from model
natal_model0_country_short = ...
    accumarray(C_vect,H.*l0_model.*natal_model0_cell) ./ ...
    accumarray(C_vect,H.*l0_model);
natal_model0_country = NaN(n,1);
for i=1:length_C_vect
    natal_model0_country(C_vect==i) = natal_model0_country_short(i);
end

% Create natality rates for year 2000 at the country level from data
natal_data0 = natal_data(year_data == 2000);
natal_data0_cell = NaN(n,1);
for i=1:length_C_vect
    natal_data0_cell(C_vect==i) = natal_data0(i);
end

% Arrange historical global population
pop_past_model = [l_model; lbar]; % 1950-2000
pop_growth_past_model = pop_past_model(2:end)./pop_past_model(1:end-1)-1;

pop_past_data = (10^3)*pop_med_hist(1:51);
pop_growth_past_data = pop_past_data(2:end)./pop_past_data(1:end-1)-1; % 1950-2000

% Construct net births at country level
natal_data_past = natal_data(year_data < 2000);
pop_data_past = pop_data(year_data < 2000);
year_data_past = year_data(year_data < 2000);

logrealgdp_c = zeros(length_C_vect,T_back);
temp_c = zeros(length_C_vect,T_back);
logrealgdp_w = zeros(T_back,1);
temp_w = zeros(T_back,1);
natal_model_c = zeros(length_C_vect,T_back);
natal_data_c = zeros(length_C_vect,T_back);
natal_data_w = zeros(T_back,1);
pop_data_c = zeros(length_C_vect,T_back);
pop_data_w = zeros(T_back,1);
for t=1:T_back 
    logrealgdp_c(:,t) = log(accumarray(C_vect,H.*l_Warm_b(:,t).*realgdp_Warm_b(:,t))./accumarray(C_vect,H.*l_Warm_b(:,t)));
    temp_c(:,t) = accumarray(C_vect,H.*l_Warm_b(:,t).*temp_local_Warm_b(:,t))./accumarray(C_vect,H.*l_Warm_b(:,t));
    logrealgdp_w(t) = log(sum(H.*l_Warm_b(:,t).*realgdp_Warm_b(:,t))/sum(H.*l_Warm_b(:,t)));
    temp_w(t) = sum(H.*l_Warm_b(:,t).*temp_local_Warm_b(:,t))./sum(H.*l_Warm_b(:,t));
    natal_model_c(:,t) = sum(H.*l_Warm_b(:,t).*net_births_Warm_b(:,t))./sum(H.*l_Warm_b(:,t));
    natal_data_c(:,t) = natal_data_past((t+1949==year_data_past));
    natal_data_w(t) = sum(natal_data_past((t+1949==year_data_past)).*pop_data_past((t+1949==year_data_past)))./sum(pop_data_past((t+1949==year_data_past)));
    pop_data_c(:,t) = pop_data_past(t+1949==year_data_past);
    pop_data_w(t) = sum(pop_data_past(t+1949==year_data_past));
end
pop_data_c(pop_data_c == 0) = 1;

% Set dots for countries
names_dots = {'US','Zambia','World'}; 
Cvect_dots = [161 112];  
years_dots = [1 T_back]; 

% Fill in vectors
logrealgdp_val = -7:0.1:10; %-7:0.1:7
temp_val = -20:0.1:40; %linspace(0,1,20); % 

% Read numerical restrictions on natality functions
b0y_max = natal_param(1);
b1y_min = natal_param(2);
b1y_max = natal_param(3);
b2y_min  = natal_param(4);
b2y_max  = natal_param(5);
bsy_min = natal_param(7);
bsy_max = natal_param(8);

logi_b0y_fct =@(x) b0y_max./(1+exp(-x));
logi_b1y_fct = @(x) b1y_min + (b1y_max - b1y_min)./(1+exp(-x));
logi_b2y_fct = @(x) b2y_min + (b2y_max - b2y_min)./(1+exp(-x));
logi_bsy_fct = @(x) bsy_min + (bsy_max - bsy_min)./(1+exp(-x));

% Construct income component of natality rate function, equation (28)
natal_fct_logrealgdp =@(logrealgdp,coeff_pop_d) ...
	(logi_b0y_fct(coeff_pop_d(1)) + ...
    (logi_b2y_fct(coeff_pop_d(4))-logi_b0y_fct(coeff_pop_d(1)))*...
    exp(-logi_b1y_fct(coeff_pop_d(2))*(logrealgdp-logi_bsy_fct(coeff_pop_d(5))).^2)).*...
    (logrealgdp<logi_bsy_fct(coeff_pop_d(5))) + ...
    (0 + ...
    (logi_b2y_fct(coeff_pop_d(4))-0)*...
    exp(-exp(coeff_pop_d(3))*(logrealgdp-logi_bsy_fct(coeff_pop_d(5))).^2)).*...
    (logrealgdp>=logi_bsy_fct(coeff_pop_d(5)));

natal_logrealgdp_dots = zeros(length(names_dots),length(years_dots));
natal_temp_dots = zeros(length(names_dots),length(years_dots));
for t=1:length(years_dots)
    for c=1:length(Cvect_dots)
        natal_logrealgdp_dots(c,t) = natal_fct_logrealgdp(logrealgdp_c(Cvect_dots(c),years_dots(t)),coeff_pop);        
        natal_temp_dots(c,t) = ...
            natal_fct(logrealgdp_c(Cvect_dots(c),years_dots(t)),temp_c(Cvect_dots(c),years_dots(t)),logrealgdp_w(years_dots(t)),coeff_pop) - ...
            natal_fct_logrealgdp(logrealgdp_c(Cvect_dots(c),years_dots(t)),coeff_pop);  
    end
	natal_logrealgdp_dots(end,t) = natal_fct_logrealgdp(logrealgdp_w(years_dots(t)),coeff_pop);        
	natal_temp_dots(end,t) = ...
            natal_fct(logrealgdp_w(years_dots(t)),temp_w(years_dots(t)),logrealgdp_w(years_dots(t)),coeff_pop) - ...
            natal_fct_logrealgdp(logrealgdp_w(years_dots(t)),coeff_pop);      
end

% Construct temperature component of natality rate function
natal_fct_temp_val_1999 = ...
    natal_fct(logrealgdp_w(1),temp_val,logrealgdp_w(1),coeff_pop) - ...
    natal_fct_logrealgdp(logrealgdp_w(1),coeff_pop);

natal_fct_temp_val_1975 = ...
    natal_fct(logrealgdp_w(25),temp_val,logrealgdp_w(25),coeff_pop) - ...
    natal_fct_logrealgdp(logrealgdp_w(25),coeff_pop);

natal_fct_temp_val_1950 = ...
    natal_fct(logrealgdp_w(end),temp_val,logrealgdp_w(end),coeff_pop) - ...
    natal_fct_logrealgdp(logrealgdp_w(end),coeff_pop);
    
% Transform variables from vectors to map grids
m2_grid = NaN(180,360);
m2_grid(H0>0) = m2;

natal0_data_grid = NaN(180,360);
natal0_data_grid(H0>0) = natal_data0_cell;

natal0_model_grid = NaN(180,360);
natal0_model_grid(H0>0) = natal_model0_cell;

temp_scaler_grid = NaN(180,360);
temp_scaler_grid(H0>0) = scaler_temp;

HDI0_grid = NaN(180,360);
HDI0_grid(H0>0) = HDI0(H0>0);

% Set numerical parameters for scatters
dx1 = 0.25;
dx2 = 1;
[map_lat,map_lon] = size(map);
aux_lon = linspace(-180,180,map_lon+1);
aux_lon = (aux_lon(1:end-1)+aux_lon(2:end))/2;
aux_lat = linspace(-90,90,map_lat+1); 
aux_lat = (aux_lat(1:end-1)+aux_lat(2:end))/2;
aux_kron = ones(map_lat/180);

% Read cost extraction data
costCO2_fct =@(cumCO2) ...
    cost_emi_param(1)./(cost_emi_param(2) + exp(-cost_emi_param(3)*(cumCO2-cost_emi_param(4)))) - ...
    cost_emi_param(5)*(cost_emi_param(6)./(cumCO2-cost_emi_param(6))).^cost_emi_param(7);

% Define colors
CM = [color_darkgreen; color_olive; color_yellowgreen];

%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot temperature scaler, extraction cost, migration costs, 
% historical population, CO2 emissions and clean energy use

% Plot temperature scaler
figure
colormap(jet);
imagesc(aux_lon,aux_lat,...
    map.*kron(temp_scaler_grid,aux_kron),...
    'AlphaData',~isnan(map.*kron(temp_scaler_grid,aux_kron)),[0.4 2.2]);
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title('Temperature scaler (C)')
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,'Maps and Figures/temp_scaler.png')

% Plot HDI
figure
colormap(jet);
imagesc(aux_lon,aux_lat,...
    map.*kron(HDI0_grid,aux_kron),...
    'AlphaData',~isnan(map.*kron(HDI0_grid,aux_kron)),[0 1]);
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title('Human Development Index, 2000')
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,'Maps and Figures/HDI0.png')

% Plot extraction cost function
figure
hold on
scatter(cost_CO2_data(:,2),cost_CO2_data(:,1),[],color_yellowgreen,'filled')
xlim([0 12500])
hold on
plot(0:100:12500,(1/conv_usd)*costCO2_fct(0:100:12500),'k','LineWidth',2)
hold on
scatter(NaN,NaN,'w')
hold on
scatter(NaN,NaN,'w')
xlim([0 12500])
ylim([0 550])
xlabel(['Cumulative emissions (GtCO_2)'])
ylabel(['usd/tCO_2'])
set(gca,'FontSize',14)
set(gcf,'color','w')
title('Extraction cost function')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset; 
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.025;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/extraction_cost.png'])

% Plot migration costs    
figure
colormap(jet);
    imagesc(aux_lon,aux_lat,map.*kron(log(m2_grid),aux_kron),...
        'AlphaData',~isnan(map.*kron(log(m2_grid),aux_kron))); 
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title('Migration costs, m_2(\cdot)')
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/m2_' name_dam '.png'])

% Plot total CO2 emissions
figure
hold on
plot(1999-T_back+1:1999,emi_ff_model(1:T_back),'color',color_yellowgreen,...
    'LineWidth',2) 
hold on
plot(1999-T_back+1:1999,emi_ff_data(1:T_back),'k',...
    1999-T_back+1:1999,emi_ff_data_tend(1:T_back),'k--',...
    'LineWidth',2) 
legend('Model','Data','Data, trend','Location','northwest','FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
ylim([5 25])
title('CO2 emissions (GtCO2/year)')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/emiCO2_past_' name_dam '.png'])

% Plot total clean energy
figure
hold on
plot(1999-T_back+1:1999,clean_model(1:T_back)/tCO2_toe,'color',color_yellowgreen,...
    'LineWidth',2) 
hold on
plot(1965:1999,clean_energy_data,'k',...
    'LineWidth',2) 
legend('Model','Data','Location','northwest','FontSize',14)
set(gca,'FontSize',14)
set(gcf,'color','w')
title('Clean energy (Gtoe/year)')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/clean_past_' name_dam '.png'])

% Plot natality function (data, country)
figure
colormap(jet);
    imagesc(aux_lon,aux_lat,map.*kron(100*natal0_data_grid,aux_kron),...
        'AlphaData',~isnan(map.*kron(100*natal0_data_grid,aux_kron)),[-1 5]); 
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title('Natality, data')
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/natal0_data_' name_dam '.png'])

% Plot natality function (model, cell)
figure
colormap(jet);
    imagesc(aux_lon,aux_lat,map.*kron(100*natal0_model_grid,aux_kron),...
        'AlphaData',~isnan(map.*kron(100*natal0_model_grid,aux_kron)),[-1 5]); 
colorbar('eastoutside');
set(gcf,'color','w');
set(gca,'color',[1 1 1],'FontSize',14)
set(gca,'Xtick',[-150 -100 -50 0 50 100 150],'XTickLabel',[-150 -100 -50 0 50 100 150])    
set(gca,'Ytick',[-80 -60 -40 -20 0 20 40 60 80],'YTickLabel',[-80 -60 -40 -20 0 20 40 60 80])    
title('Natality, model')
ax = gca;
ax.YTickLabel = flipud(ax.YTickLabel);
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/natal0_model_' name_dam '.png'])

% Plot past global population
figure
hold on
plot(1950:2000,pop_past_model,'color',color_yellowgreen,'LineWidth',2);
hold on
plot(1950:2000,pop_past_data-(10^3)*pop_med_hist(51)+lbar,'k','LineWidth',2);
legend('Model','Data','Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title('Global population')
ylim([2*10^9 6.5*10^9])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/global_pop_' name_dam '.png'])

% Plot past global population growth rate
figure
hold on
plot(1951:2000,100*pop_growth_past_model,'color',color_yellowgreen,'LineWidth',2);
hold on
plot(1951:2000,100*pop_growth_past_data,'k','LineWidth',2);
legend('Model','Data','Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title('Global natality rate')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/global_pop_growth_' name_dam '.png'])

% Plot natality rates on realgdp with dots
figure
hold on
plot(logrealgdp_val,100*natal_fct_logrealgdp(logrealgdp_val,coeff_pop),'k','LineWidth',2);
for t=1:length(years_dots)
    for c=1:length(Cvect_dots)
        hold on
        scatter(logrealgdp_c(Cvect_dots(c),years_dots(t)),100*natal_logrealgdp_dots(c,t), ...
            50,'MarkerEdgeColor',CM(c,:),'MarkerFaceColor',CM(c,:))
        hold on
        text(logrealgdp_c(Cvect_dots(c),years_dots(t))+dx1,100*natal_logrealgdp_dots(c,t), ...
            [names_dots{c} ' ' num2str(2000-years_dots(t))], ...
            'Color',CM(c,:),'Fontsize',14) 
    end
    hold on
    scatter(logrealgdp_w(years_dots(t)),100*natal_logrealgdp_dots(end,t), ...
            50,'MarkerEdgeColor',CM(length(Cvect_dots)+1,:),'MarkerFaceColor',CM(length(Cvect_dots)+1,:))
    hold on
    text(logrealgdp_w(years_dots(t))+dx1,100*natal_logrealgdp_dots(end,t), ...
        [names_dots{end} ' ' num2str(2000-years_dots(t))], ...
            'Color',CM(length(Cvect_dots)+1,:),'Fontsize',14) 
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title('Natality rate function on log real GDP')
xlabel('Log real GDP')
ylabel('Natality rate (%), \eta^y(\cdot)')
xlim([min(logrealgdp_val) max(logrealgdp_val)])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/natal_fct_realgdp_dots_' name_dam '.png'])

% Plot natality rates on temperature with dots
figure
hold on
plot(temp_val,100*natal_fct_temp_val_1999,'k','LineWidth',2);
hold on
plot(temp_val,100*natal_fct_temp_val_1950,'k--','LineWidth',2);
for t=1:length(years_dots)
    for c=1:length(Cvect_dots)
        hold on
        scatter(temp_c(Cvect_dots(c),years_dots(t)),100*natal_temp_dots(c,t), ...
            50,'MarkerEdgeColor',CM(c,:),'MarkerFaceColor',CM(c,:))
        hold on
        text(temp_c(Cvect_dots(c),years_dots(t))+dx2,100*natal_temp_dots(c,t), ...
            [names_dots{c} ' ' num2str(2000-years_dots(t))], ...
            'Color',CM(c,:),'Fontsize',14) 
    end
    hold on
    scatter(temp_w(years_dots(t)),100*natal_temp_dots(end,t), ...
            50,'MarkerEdgeColor',CM(length(Cvect_dots)+1,:),'MarkerFaceColor',CM(length(Cvect_dots)+1,:))
    hold on
    text(temp_w(years_dots(t))+dx2,100*natal_temp_dots(end,t), ...
        [names_dots{end} ' ' num2str(2000-years_dots(t))], ...
            'Color',CM(length(Cvect_dots)+1,:),'Fontsize',14) 
end
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Natality rate function on January-July temperature'])
xlabel('January-July temperature')
ylabel('Natality rate (%), \eta^T(\cdot)')
xlim([min(temp_val) max(temp_val)])
ylim([0.4 1.6])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/natal_fct_temp_dots_' name_dam '.png'])

% Plot natality rates on realgdp and scatter plot 
mean_temp = mean( 100*natal_fct_temp_val_1975 );
figure
hold on
plot(logrealgdp_val,100*natal_fct_logrealgdp(logrealgdp_val,coeff_pop)+mean_temp,'k','LineWidth',4);
hold on
scatter(reshape(logrealgdp_c,[],1),reshape(100*natal_data_c,[],1),reshape(1e-10*pop_data_c,[],1),color_yellowgreen);
legend('Model, \eta^y(\cdot)','Data','Location','northeast','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title('Natality rate function on log real GDP')
xlabel('Log real GDP')
ylabel('Natality rate (%)')
xlim([min(logrealgdp_val) max(logrealgdp_val)])
ylim([-1 4])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/natal_fct_realgdp_scatter_' name_dam '.png'])
 
% Plot natality rates on temperature and scatter plot 
mean_inc = mean( 100*natal_fct_logrealgdp(logrealgdp_val,coeff_pop) );
figure
hold on
plot(temp_val,100*natal_fct_temp_val_1975+mean_inc,'k','LineWidth',4);
hold on
scatter(reshape(temp_c,[],1),reshape(100*natal_data_c,[],1),reshape(1e-10*pop_data_c,[],1),color_yellowgreen);
legend('Model, \eta^T_{1975}(\cdot)','Data','Location','northwest','FontSize',14)
set(gcf,'color','w');
set(gca,'FontSize',14)
title(['Natality rate function on January-July temperature'])
xlabel('January-July temperature')
ylabel('Natality rate (%)')
xlim([min(temp_val) max(temp_val)])
ylim([-1 4])
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3) - 0.01;
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];
saveas(gcf,['Maps and Figures/natal_fct_temp_scatter_' name_dam '.png'])

end
