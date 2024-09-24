%% Valutare le prestazioni del sistema di controllo.
% In termini di abbattimento del disturbo, rumore e banda del sistema a CC.
s = tf('s');
P = 40/(s+1)^2
H = 0.5
C = (4+4*s)/(s)
G = C*P;
F = G*H;
W = (G)/(1+F);
Wd = P/(1+F);
Wn = -W;
Wp = F/(1+F);
bode(Wd)
hold on
bode(Wn)
hold on
bode(F)
hold on
bode(W)
% Piu basse sono le frequenze, maggiore è la F e minore è la Wd quindi
% maggiormente distrutti sono i disturbi. Poi alla pulsazione di 20 rad/s
% si vede che il sistema abbatte i disturbi di 20 dB. Per il rumore, a 43
% rad/s vale -20 dB, ovvero i rumori sono abbattuti di 20 dB. 
% Facendo la W(0) si trova il valore che la W assume a jw = 0, ovvero a
% meno infinito... a questo valore ci togli 3 dB, e quello è il valore in
% dB della w3... ora per capire DOVE si ottengono quel valore di dB
% semplicemente usi il diagramma di Bode della W. 
%% Sintesi controllore
% Dato lo stesso P di prima, trovare H e C tali da avere yd = 2 quando r =
% 1. Poi, quando yd = 2t l'errore sia minore di 0.1. Che il sistema 
% respinga a regime un disturbo a gradino ( errore nullo ), e bisogna
% sempre tenere in conto la qualità del controllore in termini di risposta
% al gradino a CC e margini di stabilità, ma questo in genere è giusto un
% requisito per dire "fallo essere bello oltre che ballare", ma è molto
% soggettivo quindi preoccupatene poco.
P = 40/(s+1)^2;
r = 1;
yd = 2;
kd = yd/r;
H = 1/kd;
% Ci serve UN polo nell'origine e gestire il kG per avere errore minore di
% 0.1.
soglia = (r * kd^2)/0.1;
kG = 60;
C = 1/s;
Cstar = (s+1);
Cfull = C * Cstar;
G = Cfull*P;
F = G*H;
W = G/(1+F);
bode(F)
%% Parte del plotting con roba importata da Simulink
subplot(2,1,1)
plot(out.t, out.y)
subplot(2,1,2)
plot(out.t, out.u)
%% Nyquist
nyquist(F)