%% Traccia Predizione

s = tf("s");
G = (180*(s+4))/((s+5)*(s+9)*(s+17));

step(G)

% Dal plot si evince che il sistema è di tipologia sottosmorzata misto
% sovrasmorzato.

Gd = c2d(G,0.67/10,"zoh") %Settling time = 1.3s

[num, den] = tfdata(Gd);
a= den{1}
b = [num{1}(2:end)]
sizey=1;


%% Inizio tarando i parametri con valori molto alti per poi andare a scendere

ny=40;
nu=20;
lambda=1;
Wy=1;
ny2=50;
nu2=9;


plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)


%Dalla figura 1 si evince che, nonostante l'overtuning, il numero di
%campioni affinchè il sistema vada a regime è superiore a 10, quindi si
%opta per una riduzione di lampda affinchè il sistema diventi più rapido

%% Scelgo il valore di lampda

lambda = 0.1;



plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)

%Notiamo adesso che lampda risulta essere sufficientemente bassa per
%ottenere un raggiungimento del regime in 10 campioni esatti. Adesso posso
%andare ad abbassare i vari parametri per ottenere un sistema ottimo ed
%efficiente


%% Inizio ad abbassare nu
% 6 campioni 
nu = 10;

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)

%%
lambda = 0.3;
nu = 10;

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)

%%

nu = 6;   %Trovato nu

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)


%% Inizio ad abbassare ny

ny = 20;

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)

%%

ny = 15;  

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)


%%

ny = 12;  

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)

%%

ny = 10;  %Trovato ny
nu= 6;

plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)












%% Grafico na


plot_ff(b,a,nu,ny,lambda)

%% Vincoli solo su ingressi

Dumax = inf;
umax = inf;
umin = -inf;


plot_overlay(b,a,nu,ny,lambda,Dumax,umax,umin,ny2)

%% Vincoli totali


ymax = inf;
ymin = -inf;

plot_output_constraints(b,a,nu,ny,lambda,Dumax,umax,umin,ymax,ymin,ny2)

