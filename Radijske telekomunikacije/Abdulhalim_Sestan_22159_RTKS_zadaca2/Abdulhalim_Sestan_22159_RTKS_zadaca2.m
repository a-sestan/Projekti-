clear all;
clc; 
close all;

f = 2.4e9;             
c = 3e8;                
lambda = c / f;        
eta = 0.6;             
D = [0.3, 0.6, 1.0];   
G_dipol = 2.15;       
HPBW_dipol = 78;       
Pt = 20;                
d_km = 1;               
f_MHz = 2400;           

G_linear = eta * (pi * D / lambda).^2;  
G_parabola = 10 * log10(G_linear);     
HPBW_parabola = 70 * lambda ./ D;       

D_kontinuirano = 0.1:0.01:1.5;         
G_kont_lin = eta * (pi * D_kontinuirano / lambda).^2;
G_kont_dBi = 10 * log10(G_kont_lin);

figure('Name', 'Zavisnost Dobitka od Prečnika');
plot(D_kontinuirano, G_kont_dBi, 'LineWidth', 2, 'Color', 'r');
hold on;
plot(D, G_parabola, 'ko', 'MarkerFaceColor', 'g', 'MarkerSize', 8); 
grid on;
title('Zavisnost dobitka parabolične antene od prečnika reflektora D');
xlabel('Prečnik reflektora D [m]');
ylabel('Dobitak antene G [dBi]');
legend('Kontinuirani proračun', 'Zadane vrijednosti (0.3m, 0.6m, 1.0m)', 'Location', 'SouthEast');

for i = 1:length(D)
    text(D(i), G_parabola(i) + 1, sprintf('%.1f dBi', G_parabola(i)), ...
        'HorizontalAlignment', 'center', 'FontWeight', 'bold');
end


figure('Name', 'Poređenje HPBW');
sve_HPBW = [HPBW_dipol, HPBW_parabola];
b1 = bar(sve_HPBW, 0.5, 'FaceColor', [0.2 0.6 0.8]);
grid on;
set(gca, 'XTickLabel', {'Dipol', 'Parabola 0.3m', 'Parabola 0.6m', 'Parabola 1.0m'});
title('Širina glavnog snopa (HPBW) za posmatrane antene');
ylabel('HPBW [°]');

xtips1 = b1.XEndPoints;
ytips1 = b1.YEndPoints;
labels1 = string(round(b1.YData, 1)) + "°"; % Prikaz sa stepenima
text(xtips1, ytips1, labels1, 'HorizontalAlignment', 'center', ...
    'VerticalAlignment', 'bottom', 'FontWeight', 'bold');


FSPL = 32.44 + 20*log10(d_km) + 20*log10(f_MHz); 
Pr_dipol = Pt + G_dipol + G_dipol - FSPL;        
Pr_parabole = Pt + G_parabola + G_parabola - FSPL;
sve_Snage = [Pr_dipol, Pr_parabole];

figure('Name', 'Budžet snage primatelja'); 
b2 = bar(sve_Snage, 0.5, 'FaceColor', [0.8 0.4 0.2]);
grid on;

set(gca, 'XTickLabel', {'Dipol-Dipol', 'Parabola 0.3m', 'Parabola 0.6m', 'Parabola 1.0m'});
xtickangle(15); 

title('Primljena snaga Pr na udaljenosti od 1 km');
ylabel('Pr [dBm]');

ylim([min(sve_Snage) - 10, 0]);

xtips2 = b2.XEndPoints;
ytips2 = b2.YEndPoints;
labels2 = string(round(b2.YData, 1)) + " dBm"; 

for i = 1:length(sve_Snage)
    text(xtips2(i), ytips2(i) - 1, labels2(i), ...
        'HorizontalAlignment', 'center', ...
        'VerticalAlignment', 'top', ... 
        'FontWeight', 'bold');
end