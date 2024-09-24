s = tf('s');
P=10/(s+5);
C=1/s;
H=1;
F=C*P*H;
[m,f]=bode(F,3)
20*log10(m)
f-3*0.05/2*180/pi % Questo termine porta in conto anche il ritardo dovuto a Td
alfa = 1/2;
tau = 1.4/3;
ant = (1+tau*s)/(1+s*tau*alfa);
Cfull = C*ant;
F2= Cfull*P*H;
Cd = c2d(Cfull, 0.05, 'tustin');
Pd = c2d(P, 0.05);
Fd = Cd*Pd*H;
G = Cd*Pd;
[y,t] = step(G);
stairs(y,t)