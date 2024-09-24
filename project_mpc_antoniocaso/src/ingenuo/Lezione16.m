% Computation of prediction matrices with state space model
% (A,B,C,D) represent the state space description of a MIMO discrete time system with 2 inputs and 2 outputs
%%
A=[0.9 -0.5; 0 0.8];
B=[1 1; -2 0];
C=[2 0.5; -1 1]; % Due per due, ho due variabili di uscita
D=zeros(2,2); %E' sempre nulla
% Se l'orizzonte di predizione è 4, cosa esce?
[H,P,L] = imgpc_predmat(A,B,C,D,4)
[Hx,Px] = imgpc_predmat(A,B,eye(2),D,4)
%%
% Prediction with state space model
% (A,B,C,D) represent the state space description of a SISO continuous time system
A=[0 1; 0 -2];
B=[0; 2];
C=[1 0];
D=0;
sys=ss(A,B,C,D)
sysd=c2d(sys,0.01) % sample-data version of the system with T=0.01
[Ad,Bd,Cd,Dd]=ssdata(sysd) % (Ad,Bd,Cd,Dd) represent the state space description of the sample-data version of the system with T=0.01
[H,P,L] = imgpc_predmat(Ad,Bd,Cd,Dd,5) % prediction matrices computation with ny=5
ym=P*[0 0]' + H*[1 1 1 1 1]' + L*0 % output prediction from initial state x=[0 0]' under constant input (u=1) without disturbance
[yp,t]=step(sysd,0:0.01:0.05) % output of the system (without disturbance), yp and ym are equal 
%%
% Prediction with transfer function (CARIMA)
G=zpk([],[0 -2],2) % notice that the tf is the same of the previous example
Gd=c2d(G,0.01) % sample-data version of the system with T=0.01
[num,den]=tfdata(Gd)
a=den{1}
b=num{1}(2:3) % be careful, the first element is assumed to be the coefficient of z^-1, the coefficient of z^0 is assumed equal to 0
[H,P,Q] = mpc_predmat(a,b,5) % Q is 5*3, indeed H,P and Q are computed by A(z)=a(z)(z-1) and b(z), so A(z) has order 3, the order of a(z) plus 1
% you can use also [H,P,Q] = mpc_predmat_toeplitz(a,b,5), but
% be sure that caha.m sia is present in the same dir
ym=H*[1 0 0 0 0]' + P*[0]'+ Q*[0 0 0]' % output prediction from initial state x=[0 0]' under constant input (u=1) without disturbance
% notice that u=1 is represented by [1 0 0 0 0]' since the prediction uses input increments, not input absolue values
[yp,t]=step(Gd,0:0.01:0.05) % output of the system, yp and ym are equal 