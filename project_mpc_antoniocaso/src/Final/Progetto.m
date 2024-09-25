%% Discretizzazione e definizione parametri
clear; close all;
G=zpk(-4,[-6 -10 -11],28)
rit=0;

fig=1;
figure(fig);
fig=fig+1;

step(G)
% Se serve si può cambiare in 0.7/10, l'importante è che rimanga minore di 0.773/10
Td=0.773/10;

Gd=c2d(G,Td,'zoh');
[num, den] = tfdata(Gd);
a=den{1};
b=[zeros(0,rit),num{1}(2:end)];
sizey=1;

%%%% Parametri della predizione
nu=20;
ny=30;
lambda=1;
%%%%

nu2=30;
ny2=60;

[H,P,Q] = mpc_predmat(a,b,ny);   
[H2,P2,Q2] = mpc_predmat(a,b,ny2);   
HH=tril(ones(nu,nu));

% mpc_law computes entire proposed trajectory
[~,~,Pr,S,X,Prlong] = mpc_law(H,P,Q,nu,lambda,1,sizey);

% Control trajectory for a step change in r, this will be used later
% to compare open and close loop aoutput
Duopt = Pr;
yfut=H(:,1:nu)*Duopt;    %%% prediction within J
yfut2=H2(:,1:nu)*Duopt;  %%% Longer range prediction
uopt=HH*Duopt;

%%% Set point, disturbance and noise
ref = [zeros(1,5),ones(1,55)];
dist=[zeros(1,60)]; 
noise = [zeros(1,60)];

% With noise and disturb starting at t=10
%dist=[zeros(1,10),ones(1,50)]; 
%noise = [zeros(1,10),ones(1,50)/4];

% Sinusoidal disturb
%dist=sin((1:60)/2);

%% Starting prediction
[y,u,~,r] = mpc_simulate_noconstraints(b,a,nu,ny,lambda,1,ref,dist,noise);

figure(fig); clf reset
fig=fig+1;

sgtitle(['n_y =',num2str(ny),', n_u =',num2str(nu),', \lambda = ',num2str(lambda)],'fontsize',18)
subplot(2,1,1);

% U vs Y
v=0:ny;
p1=plot(v,[0;yfut],'b',[0 1 1 ny],[0 0 1 1],'r--',...
    [ny,ny],[0,6],'g:',[0:nu-1,ny],[uopt;uopt(end)],'m');
l1=legend('Output','set point','horizon','input');
set(p1,'linewidth',1);
set(l1,'fontsize',18)
title('U vs Y','fontsize',18)

% OL vs CL
subplot(2,1,2);
v=0:ny2;
p2=plot(v,[0;yfut2],'b',[0 1 1 ny],[0 0 1 1],'r--',...
    [ny,ny],[0,1.5],'g:',0:ny2-12,y(6:ny2-6),'b--');
xlim([0,ny])
set(p2,'linewidth',1);
l2=legend('open-loop','set point','horizon','closed-loop');
set(l2,'fontsize',18)
title('Open loop vs close loop','fontsize',18)

disp(['Guadagno statico = ',num2str(dcgain(G))])

%% Plotting nu
nus=[5,7,10,15,20];
Nk=cell(1);Dk=Nk;Pr=Nk;
Duopt=Nk;uopt=Nk;
yfut=Nk;yfut2=Nk;
y=Nk; Du=Nk;
k=1; clear lgd; clear J;

for k=1:length(nus)
    [Nk{k},Dk{k},Pr{k},S,X,Prlong] = mpc_law(H,P,Q,nus(k),lambda,1,sizey);
    [y{k},~,Du{k},r] = mpc_simulate_noconstraints(b,a,nus(k),ny,lambda,1,ref,dist,noise);
    HH=tril(ones(nus(k),nus(k)));

    %%% Control trajectory for a step change in r
    Duopt{k} = Pr{k};
    yfut{k}=H(:,1:nus(k))*Duopt{k};    %%% prediction within J
    yfut2{k}=H2(:,1:nus(k))*Duopt{k};  %%% Longer range prediction
    uopt{k}=HH*Duopt{k};
    J(k)=norm(r-y{k},2)^2+lambda*norm(Du{k},2)^2;
    lgd{k} = strcat('n_u=',num2str(nus(k)));
end

figure(fig);  clf reset
fig=fig+1;

% Plotting the Y
subplot(2,3,[1,2]);
v=0:ny;v2=0:ny2;
plot([0,1,1,ny2],[0 0 1 1],'r--',[ny,ny],[0,1.5],'g:');hold on
for k=1:length(nus)
    c=(k-1)/(length(nus)-1);
    plot(v2,[0;yfut2{k}],'linewidth',1,'color',[c,0,1-c]);
end
title('System output','fontsize',18)
l1=legend(['set point','n_y',lgd]);
set(l1,'fontsize',18)
xlim([0,ny])

% Plotting the U
subplot(2,3,[4,5]);
v=0:ny;v2=0:ny2;
plot([1,1],[ 0 7 ],'r--',[ny,ny],[0,7],'g:');hold on
for k=1:length(nus)
    c=(k-1)/(length(nus)-1);
    plot([0:nus(k)-1,nus(end)+2],[uopt{k};uopt{k}(end)],'linewidth',1,'color',[c,0,1-c]);
end
title('System input','fontsize',18)
xlim([0,length(uopt{end})])

% Plotting the J
subplot(2,3,[3,6]);
plot(nus,J);
title('Runtime cost','fontsize',18)

sgtitle(['n_y =',num2str(ny),' \lambda = ',num2str(lambda)]);

%% Plotting ny
Nk=cell(1);
Duopt=Nk;uopt=Nk;
yfut=Nk;yfut2=Nk;
y=Nk; Du=Nk; 
clear J;clear lgd;

nu=10;
nys=[nu, nu+5, nu+10, nu+20];

% Varying ny
for k=1:length(nys)
    [Htemp,Ptemp,Qtemp] = mpc_predmat(a,b,nys(k));   
    [Nk,Dk,Pr,S,X,Prlong] = mpc_law(Htemp,Ptemp,Qtemp,nu,lambda,1,sizey);
    [y{k},~,Du{k},r] = mpc_simulate_noconstraints(b,a,nu,nys(k),lambda,1,ref,dist,noise);
    HH=tril(ones(nu,nu));

    %%% Control trajectory for a step change in r
    Duopt{k} = Pr;
    yfut{k}=H(:,1:nu)*Duopt{k};    %%% prediction within J
    yfut2{k}=H2(:,1:nu)*Duopt{k};  %%% Longer range prediction
    uopt{k}=HH*Duopt{k};
    J(k)=norm(r-y{k},2)^2+lambda*norm(Du{k},2)^2;
    lgd{k} = strcat('n_y=',num2str(nys(k)));
end

figure(fig);  clf reset
fig=fig+1;

% Ai grafici esce solo l'ultima linea
% Plotting the Y
subplot(2,3,[1,2]);
v=0:ny;v2=0:ny2;
plot([0,1,1,ny2],[0 0 1 1],'r--',[ny,ny],[0,1.5],'g:');hold on
for k=1:length(nys)
    c=(k-1)/(length(nys)-1);
    plot(v2,[0;yfut2{k}],'linewidth',1,'color',[c,0,1-c]);
end
c=legend(['set point','ny',lgd]);
set(c,'fontsize',18)
xlim([0,nys(end)])
title('System output','fontsize',18)

% Plotting the U
subplot(2,3,[4,5]);
v=0:ny;v2=0:10;
plot([1,1],[ 0 7 ],'r--',[ny,ny],[0,7],'g:');hold on
lgd = cell(length(nys),1);
for k=1:length(nys)
    c=(k-1)/(length(nys)-1);
    plot([0:nu-1,nu+2],[uopt{k};uopt{k}(end)],'linewidth',1,'color',[c,0,1-c]);
    %plot([0:nys(k)],[uopt{k};uopt{k}(end)],'linewidth',1,'color',[c,0,1-c]);
end
xlim([0,length(uopt{1})])
title('System input','fontsize',18)

% Plotting the J
subplot(2,3,[3,6]);
plot(nys,J);
title('Runtime cost','fontsize',18)
%xlim([0,size(nys)])

sgtitle(['n_u =',num2str(nu),' \lambda = ',num2str(lambda)]);

%% Plotting lambda
nu=20;
lambdas=[0.01,0.1,1,10,100];
Nk=cell(1);Dk=Nk;Pr=Nk;
Duopt=Nk;uopt=Nk;
yfut=Nk;yfut2=Nk;
y=Nk; Du=Nk;
clear J;clear lgd;

for k=1:length(lambdas);
    [Nk{k},Dk{k},Pr{k},S,X,Prlong] = mpc_law(H,P,Q,nu,lambdas(k),1,sizey);
    [y{k},~,Du{k},r] = mpc_simulate_noconstraints(b,a,nu,ny,lambdas(k),1,ref,dist,noise);
    HH=tril(ones(nu,nu));

    %%% Control trajectory for a step change in r
    Duopt{k} = Pr{k};
    yfut{k}=H(:,1:nu)*Duopt{k};    %%% prediction within J
    yfut2{k}=H2(:,1:nu)*Duopt{k};  %%% Longer range prediction
    uopt{k}=HH*Duopt{k};
    J(k)=norm(r-y{k},2)^2+lambdas(k)*norm(Du{k},2)^2;
    lgd{k} = strcat('\lambda=',num2str(lambdas(k)));
end

figure(fig);  clf reset
fig=fig+1;

% plotting y
subplot(2,3,[1,2]);
v=0:ny;v2=0:ny2;
plot([0,1,1,ny2],[0 0 1 1],'r--',[ny,ny],[0,1.5],'g:');hold on
for k=1:length(lambdas);
    kk=(k-1)/(length(lambdas)-1);
    plot(v,[0;yfut{k}],'linewidth',1,'color',[kk,0,1-kk]);
end
xlim([0,ny]);
c=legend(['set point','ny',lgd]);
set(c,'fontsize',18)
title('System output','fontsize',18)

% plotting U
subplot(2,3,[4,5]);
plot([1,1],[ 0 7 ],'r--',[ny,ny],[0,7],'g:');hold on
v=0:ny;v2=0:ny2;
for k=1:length(lambdas)
    kk=(k-1)/(length(lambdas)-1);
    plot([0:nu-1,nu+2],[uopt{k};uopt{k}(end)],'linewidth',1,'color',[kk,0,1-kk]);
end
xlim([0,length(uopt{1})]);
title('System input','fontsize',18)

% Plotting the J
subplot(2,3,[3,6]);
semilogx(lambdas,J);
title('Runtime cost','fontsize',18)

sgtitle(['n_y =',num2str(ny),' n_u = ',num2str(nu)]);


%% Sistema finale lambda 0.1
% Valori iniziali:
% ny_fin=20;  
% nu_fin=15;
% lambda_fin=0.1;
            
            %   parametri alternativi
ny_fin=19;  %   16
nu_fin=11;  %   14
lambda_fin=0.1;

ny2_fin=30;

[H,P,Q] = mpc_predmat(a,b,ny_fin);   
[H2,P2,Q2] = mpc_predmat(a,b,ny2_fin);   
HH=tril(ones(nu_fin,nu_fin));

% mpc_law computes entire proposed trajectory
[~,~,Pr,S,X,Prlong] = mpc_law(H,P,Q,nu_fin,lambda_fin,1,sizey);

% Control trajectory for a step change in r, this will be used later
% to compare open and close loop aoutput
Duopt = Pr;
yfut=H(:,1:nu_fin)*Duopt;    %%% prediction within J
yfut2=H2(:,1:nu_fin)*Duopt;  %%% Longer range prediction
uopt=HH*Duopt;
[y,u,Du,r] = mpc_simulate_noconstraints(b,a,nu_fin,ny_fin,lambda_fin,1,ref,dist,noise);

J=norm(r-y,2)^2+lambda_fin*norm(Du,2)^2;
disp(['J = ',num2str(J)]);

figure(fig); clf reset
fig=fig+1;

sgtitle(['n_y =',num2str(ny_fin),', n_u =',num2str(nu_fin),', \lambda = ',num2str(lambda_fin)],'fontsize',18)
subplot(2,1,1);

% U vs Y
v=0:ny_fin;
p1=plot(v,[0;yfut],'b',[0 1 1 ny_fin],[0 0 1 1],'r--',...
    [ny_fin,ny_fin],[0,1.5],'g:',[0:nu_fin-1,ny_fin],[uopt;uopt(end)],'m');
l1=legend('Output','set point','horizon','input');
set(p1,'linewidth',1);
set(l1,'fontsize',18)
title('U vs Y','fontsize',18)
xlim([0,ny_fin]);

% OL vs CL
subplot(2,1,2);
v=0:ny2_fin;
p2=plot(v,[0;yfut2],'b',[0 1 1 ny_fin],[0 0 1 1],'r--',...
    [ny_fin,ny_fin],[0,1.5],'g:',0:ny2_fin,y(6:6+ny2_fin),'b--');
xlim([0,ny_fin])
set(p2,'linewidth',1);
l2=legend('open-loop','set point','horizon','closed-loop');
set(l2,'fontsize',18)
title('Open loop vs close loop','fontsize',18)

%% Sistema finale lambda 0.01
% Valori iniziali:
% ny_fin=20;  
% nu_fin=10;
% lambda_fin=0.01;
            
ny_fin=30;  %15
nu_fin=3;   %8
lambda_fin=0.01;

ny2_fin=30;

[H,P,Q] = mpc_predmat(a,b,ny_fin);   
[H2,P2,Q2] = mpc_predmat(a,b,ny2_fin);   
HH=tril(ones(nu_fin,nu_fin));

% mpc_law computes entire proposed trajectory
[~,~,Pr,S,X,Prlong] = mpc_law(H,P,Q,nu_fin,lambda_fin,1,sizey);

% Control trajectory for a step change in r, this will be used later
% to compare open and close loop aoutput
Duopt = Pr;
yfut=H(:,1:nu_fin)*Duopt;    %%% prediction within J
yfut2=H2(:,1:nu_fin)*Duopt;  %%% Longer range prediction
uopt=HH*Duopt;
[y,u,Du,r] = mpc_simulate_noconstraints(b,a,nu_fin,ny_fin,lambda_fin,1,ref,dist,noise);

J=norm(r-y,2)^2+lambda_fin*norm(Du,2)^2;
disp(['J = ',num2str(J)]);

figure(fig); clf reset
fig=fig+1;

sgtitle(['n_y =',num2str(ny_fin),', n_u =',num2str(nu_fin),', \lambda = ',num2str(lambda_fin)],'fontsize',18)
subplot(2,1,1);

% U vs Y
v=0:ny_fin;
p1=plot(v,[0;yfut],'b',[0 1 1 ny_fin],[0 0 1 1],'r--',...
    [ny_fin,ny_fin],[0,1.5],'g:',[0:nu_fin-1,ny_fin],[uopt;uopt(end)],'m');
l1=legend('Output','set point','horizon','input');
set(p1,'linewidth',1);
set(l1,'fontsize',18)
title('U vs Y','fontsize',18)
xlim([0,ny_fin]);

% OL vs CL
subplot(2,1,2);
v=0:ny2_fin;
p2=plot(v,[0;yfut2],'b',[0 1 1 ny_fin],[0 0 1 1],'r--',...
    [ny_fin,ny_fin],[0,1.5],'g:',0:ny2_fin,y(6:6+ny2_fin),'b--');
xlim([0,ny_fin])
set(p2,'linewidth',1);
l2=legend('open-loop','set point','horizon','closed-loop');
set(l2,'fontsize',18)
title('Open loop vs close loop','fontsize',18);

%% Proposta di costraint
Dumax=0.5;  %% input rate limit
umax=6;   %% max input
umin=-2;
%ymax=1.2;
%ymin=-0.2;

%[y,u,Du,r] = mpc_simulate_outputconstraints(b,a,nu,ny,lambda,1,Dumax,umax,umin,ymax,ymin,ref,dist,noise);
[y,u,Du,r] = mpc_simulate_overlay(b,a,nu_fin,ny_fin,lambda_fin,1,Dumax,umax,umin,ref,dist,noise);

J=norm(r-y,2)^2+lambda_fin*norm(Du,2)^2;
disp(['J = ',num2str(J)]);
