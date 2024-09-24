%% Primo esercizio
s = tf('s');
P = 10*(s+1)/(s*(s+10));
H = 1;
kd = 1;
kP= 10;
kC= 1;
kG = kC*kP;
C = kC/s;
Cstar =1;
Cfull=C*Cstar;
G = Cfull*P;
F = Cfull*P*H;
bode(F)
% Per vedere effetto sull'uscita di un disturbo sin(0.1t)
Wd = P/(1+F);
[m,f] = bode(Wd, 0.1);
m = 20*log10(m) %-19 vuol dire che si ha un attenuamento di 19 dB

W = G/(1+F);
Wn = -W;
[m,f] = bode(Wn, 150);
m = 20*log10(m)
%% Sintesi controllore usando reti: esercizio 1.5
P = (s+10)/((s+1)*(s+20));
H=1;
kd=1;
r = 1;
kc = 10;
kp = 1;
C = 1/s;
Cstar = 1;
Cfull = Cstar*C;
F = Cfull*P*H;
W = (Cfull*P)/(1+F);
bode(F); %Bisogna alzare di 9 in Db, ovvero 2.8184
wn0 = 1;
zita0 = 0.5;
ta2 = -((log(0.1)*2)/(zita0*wn0));
bode(W)
%%
%Siccome non possiamo toccare il modulo, dobbiamo usare una rete
%anticipatrice che però anticipa solo il modulo
tau1 = 200;
alfa1 = 1/5.6;
tau11 = 6;
alfa11 = 1/2.1;
reteAnt1 = (1+tau1*s)/(1+tau1*alfa1*s);
reteRit11 = (1+tau11*alfa11*s)/(1+tau11*s);
F1 = Cfull*reteAnt1*reteRit11*P*H;
bode(F1)
Cfull1 = Cfull*reteAnt1*reteRit11;
%% Guadagnare 19 dB e 8 di fase
tau2 = 51/2;
alfa2 = 1/10;
reteAnt2 = (1+tau2*s)/(1+tau2*alfa2*s);
F2 = Cfull*reteAnt2*P*H;
bode(F2);

%% Guadagnare 40 dB e 16 di fase
tau3 = 68/8;
alfa3 = 1/10.6;
reteAnt3 = (1+tau3*s)/(1+tau3*alfa3*s);
reteAnt33 = reteAnt3*reteAnt3;
F3 = Cfull*reteAnt33*P*H;
bode(F3)

%% Esercizio 1.6, Guadagnare 20 dB e 35 di fase
P = 30/s;
H=1/3;
C=1/s;
F=C*P*H;
bode(F)
G = C*P;
tau1 = 16/10;
alfa1 = 1/13;
reteAnt1 = (1+tau1*s)/(1+tau1*alfa1*s);
F1 = Cfull*reteAnt1*P*H;
bode(F1)

deltaMax = 35*(3.14/180)/10
Wd = P/(1+F1);
W = G/(1+F1);
Wn = -W;
bode(W)
%% Esercizio 1.7
P = 600/s;
H=0.5;
C = 0.78/s;
F = C*P*H;
bode(F)
% +40 di fase e +22 di modulo
tau1 = 18/100;
alfa1 = 1/17;
reteAnt1 = (1+tau1*s)/(1+tau1*alfa1*s);
reteAnt11 = reteAnt1*reteAnt1;
F1 = Cfull*reteAnt1*P*H;
bode(F1)
W = C*P/(1+F1);
bode(W)
%% Esercizio lezione
P = 40/(s+1)^2;
H = 1/2;
C = 4*(s+1)/s;
F = C*P*H;
bode(F);
tau11 = 700/2;
alfa11 = 1/18;
reteRit11 = (1+tau11*alfa11*s)/(1+tau11*s);
F1 = C*reteRit11*P*H;
bode(F1)
%% Simulazione tempo discreto
z = tf('z');
G = 1/(z+0.5);
[y,t] = step(G);
stairs(t,y)
%stairs()
%%
P=zpk([],[-1 -1],40);
H=1/2;
C1p=zpk([],[0],2);
tau1=3/2;
alfa1=1/25;
ant=tf([tau1 1],[alfa1*tau1 1]); % rete anticipatrice 
[m,f]=bode(ant,2);
20*log10(m);
tau2=700/2;
alfa2=1/25;
rit=tf([alfa2*tau2 1],[tau2 1]); % rete ritardatrice
[m,f]=bode(rit,2);
20*log10(m);
C3p=C1p*rit*ant;
F3p=C3p*P*H;
nichols(F3p)

C3pd1 = c2d(C3p, 0.1, 'tustin');
C3pd2 = c2d(C3p, 0.4, 'tustin');
%% Lezione 8 Esercizio 1
P = (1+s)/s;
Cs = (1+s)/s;
Pd = c2d(P, 0.01, 'zoh');
Cd = c2d(Cs, 0.1, 'tustin');
%% Lezione 8 Esercizio 2
P = 40/(s+1)^2;
C = 1/s;
H = 0.5;
Td = 0.2;
F1=P*C*H
[m,f]=bode(F1,1)
20*log10(m)
f-1*0.2/2*180/pi % Questo termine porta in conto anche il ritardo dovuto a Td
alfa = 1/8;
tau = 1.4;
ant = (1+tau*s)/(1+s*tau*alfa);
Cfull = C*ant;
F2 = Cfull*P*H;
[m,f]=bode(F2,1)
Cfinale = Cfull*0.063;
F2 = Cfinale*P*H;
bode(F2)

Cd = c2d(Cfinale, 0.2, 'tustin');

%% Terzo esercizio
P = 200/(s+1);
H = 0.5;
C = 1/s;
F = C*P*H;
[m,f] = nichols(F, 90);

zero=(s/90+1)
[m,f]=bode(zero,90)
20*log10(m)

10^(38/20)
kI=10^(38/20)
F3=C*P*H*zero*kI
nichols(F3)
W3=F3/H/(1+F3)
%% 
P = 100/(s*s);
H=1;
C=1;
%%
P = (0.1*(1-2*s))/(s*(1+10*s)*(1+0.1*s));
H=1;
C = 1;
%% 
P = 10/(s+5);
H=1;
C=1/s;
Cd = c2d(C, 0.1, 'tustin');
Pd = c2d(P, 0.1);
%% 
P = 100/((1-0.1*s)*(1+0.17*s));
H=1;
C=1/s;
