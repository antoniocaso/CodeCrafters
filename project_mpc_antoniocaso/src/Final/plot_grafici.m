% Cambia da plot_grafici solo per l'aggiunta della figura 12

function [] = plot_grafici(a,b,ny,nu,lambda,sizey,nu2,ny2)
a_new = [a];
b_new = [b];
nu_new = nu;
lambda_new = lambda;
sizey_new = sizey;
nu2_new = nu2;
ny2_new = ny2;

%%%% Generates a square H matrix for now
[H,P,Q] = mpc_predmat(a_new,b_new,ny);

[H2,P2,Q2] = mpc_predmat(a_new,b_new,ny2_new); 
HH=tril(ones(nu_new,nu_new));

%%%% mpc_law computes entire proposed trajectory
[Nk,Dk,Pr,S,X,Prlong] = mpc_law(H,P,Q,nu_new,lambda_new,1,sizey_new);

%%% Control trajectory for a step change in r
Duopt = Pr;
yfut=H(:,1:nu_new)*Duopt;    %%% prediction within J
yfut2=H2(:,1:nu_new)*Duopt;  %%% Longer range prediction
uopt=HH*Duopt;

% Nella figura 1 si vanno a plottare i grafici della simulazione a ciclo
% chiuso del modello di predizione.
figure(1); clf reset
ref = [zeros(1,25),ones(1,ny2)];
dist = [zeros(1,25+ny2)];
noise = [zeros(1,25+ny2)];

%%% Closed-loop simulation 
[y,u,Du,r] = mpc_simulate_noconstraints(b_new,a_new,nu_new,ny,lambda_new,1,ref,dist,noise);

a_new = [a];
b_new = [b];
nu_new = nu;
lambda_new = lambda;
sizey_new = sizey;
nu2_new = nu2;
ny2_new = ny2;

% Nella figura 2 si va a plottare l'uscita predetta all'istante k = 0 e gli
% input ad essa associata.
%%%% plotting predicition and u
figure(2); clf reset
v=0:ny;v2=0:ny2_new;
aa=plot(v2,[0;yfut2],'b',[0 1 1 ny2_new],[0 0 1 1],'r--',...
    [ny,ny],[0,1.5],'g:',[0:nu_new-1,ny2_new],[uopt;uopt(end)],'m');
set(aa,'linewidth',2);
c=legend('Output','set point','horizon','input');
set(c,'fontsize',18)
title(['n_y = ',num2str(ny),', n_u = ',num2str(nu_new),', \lambda = ',num2str(lambda_new)],'fontsize',18)

a_new = [a];
b_new = [b];
nu_new = nu;
lambda_new = lambda;
sizey_new = sizey;
nu2_new = nu2;
ny2_new = ny2;

% Nella figura 3 si va a fare il confronto tra il comportamento a ciclo
% aperto ed a ciclo chiuso del sistema
%%%% plotting OL vs CL
figure(3); clf reset
v=0:ny;v2=0:ny2_new;
a_plot=plot(v2,[0;yfut2],'b',[0 1 1 ny2_new],[0 0 1 1],'r--',...
    [ny,ny],[0,1.5],'g:',0:14,y(25:39),'y--');
xlim([0,15])
set(a_plot,'linewidth',2);
c=legend('open-loop','set point','horizon','closed-loop');
set(c,'fontsize',18)
title(['n_y = ',num2str(ny),' n_u = ',num2str(nu_new)],'fontsize',18)

a_new = [a];
b_new = [b];
nu_new = nu;
lambda_new = lambda;
sizey_new = sizey;
nu2_new = nu2;
ny2_new = ny2;

% In tale sezione si fanno delle computazioni in cui si effettuano varie
% predizioni sulla base di differenti valori di nu; i risultati di tale
% sezione vengono utilizzati per il plot delle figure 4 e 5.
%%%% mpc_law computes entire proposed trajectory for several different nu
% Nk=cell(1);Dk=Nk;Pr=Nk;
% Duopt=Nk;uopt=Nk;
% yfut=Nk;yfut2=Nk;
Nk=cell(1);Dk=Nk;Pr=Nk;
Duopt=Nk;uopt=Nk;
yfut=Nk;yfut2=Nk;
y=Nk; Du=Nk;

for nu_new=1:nu2_new;
    [Nk{nu_new},Dk{nu_new},Pr{nu_new},S,X,Prlong] = mpc_law(H,P,Q,nu_new,lambda_new,1,sizey_new);
    [y{nu_new},~,Du{nu_new},r] = mpc_simulate_noconstraints_without_plots(b_new,a_new,nu_new,ny,lambda_new,1,ref,dist,noise);
    HH=tril(ones(nu_new,nu_new));

    %%% Control trajectory for a step change in r
    Duopt{nu_new} = Pr{nu_new};
    yfut{nu_new}=H(:,1:nu_new)*Duopt{nu_new};    %%% prediction within J
    yfut2{nu_new}=H2(:,1:nu_new)*Duopt{nu_new};  %%% Longer range prediction
    uopt{nu_new}=HH*Duopt{nu_new};

    J(nu_new)=norm(r-y{nu_new},2)^2+lambda_new*norm(Du{nu_new},2)^2;
end

% Nella figura 4 si va a fare il confronto della predizione sulla base di
% differenti valori di nu
%%%% plotting
figure(4); clf reset
v=0:ny;v2=0:ny2_new;
plot([0,1,1,ny2_new],[0 0 1 1],'r--',[ny,ny],[0,1.5],'g:');hold on
for nu_new=1:nu2_new;
    k=(nu_new-1)/(nu2_new-1);
    plot(v2, [0; yfut2{nu_new}], 'linewidth', 2, 'color', [mod(nu_new*0.2, 1), mod(nu_new*0.5, 1), mod(nu_new*0.8, 1)]);

end
c=legend('set point','n_y','n_u=1','n_u=2','n_u=3','n_u=4','n_u=5','n_u=6','n_u=7','n_u=8','n_u=9','n_u=10');
set(c,'fontsize',18)
title(['Outputs with n_y = ',num2str(ny),' \lambda = ',num2str(lambda_new)],'fontsize',18)

% Nella figura 5 si mostrano i vari inputs che vengono definiti sulla base
% di differenti valori di nu
%%%% plotting the inputs
figure(5); clf reset
v=0:ny;v2=0:ny2_new;
plot([nu2_new-1,nu2_new-1],[0.6,2.0],'g:'); hold on
for nu_new=1:nu2_new;
    k=(nu_new-1)/(nu2_new-1);
    plot([0:nu_new-1,nu2_new+2],[uopt{nu_new};uopt{nu_new}(end)],'linewidth',2,'color',[k,0,1-k]);
end
c=legend('n_u(max)','n_u=1','n_u=2','n_u=3','n_u=4','n_u=5','n_u=6','n_u=7','n_u=8','n_u=9','n_u=10');
set(c,'fontsize',18)
title(['Inputs with n_y = ',num2str(ny),' \lambda = ',num2str(lambda_new)],'fontsize',18)

figure(6);
plot(1:nu2_new,J);
title('J vs nu','fontsize',18)
xlabel('n_u','fontsize',18);
ylabel('J','fontsize',18);

a_new = [a];
b_new = [b];
nu_new = nu;
lambda_new = lambda;
sizey_new = sizey;
nu2_new = nu2;
ny2_new = ny2;

% In tale sezione si fanno delle computazioni in cui si effettuano varie
% predizioni sulla base di differenti valori di lambda; i risultati di tale
% sezione vengono utilizzati per il plot delle figure 6 e 7.
%%%% mpc_law computes entire proposed trajectory for several different
%%%% lambda
lambda_new=[0.01,0.1,1,10,100];
Nk=cell(1);Dk=Nk;Pr=Nk;
Duopt=Nk;uopt=Nk;
yfut=Nk;yfut2=Nk;
y=Nk; Du=Nk;

for k=1:length(lambda_new);
    [Nk{k},Dk{k},Pr{k},S,X,Prlong] = mpc_law(H,P,Q,nu_new,lambda_new(k),1,sizey_new);
    [y{k},~,Du{k},r] = mpc_simulate_noconstraints_without_plots(b_new,a_new,nu_new,ny,lambda_new(k),1,ref,dist,noise);
    HH=tril(ones(nu_new,nu_new));

    %%% Control trajectory for a step change in r
    Duopt{k} = Pr{k};
    yfut{k}=H(:,1:nu_new)*Duopt{k};    %%% prediction within J
    yfut2{k}=H2(:,1:nu_new)*Duopt{k};  %%% Longer range prediction
    uopt{k}=HH*Duopt{k};
    J_lambda(k)=norm(r-y{k},2)^2+lambda_new(k)*norm(Du{k},2)^2;
end

% Nella figura 6 si va a fare il confronto della predizione sulla base di
% differenti valori di lambda
%%%% plotting 
figure(7); clf reset
v=0:ny;v2=0:ny2_new;
plot([0,1,1,ny2_new],[0 0 1 1],'r--',[ny,ny],[0,1.5],'g:');hold on
for k=1:length(lambda_new);
    kk=(k-1)/(length(lambda_new)-1);
    plot(v2,[0;yfut2{k}],'linewidth',2,'color',[kk,0,1-kk]);
end
c=legend('set point','n_y','\lambda=0.01','\lambda=0.1','\lambda=1','\lambda=10','\lambda=100');
set(c,'fontsize',18)
title(['Outputs with n_y = ',num2str(ny),' n_u = ',num2str(nu_new)],'fontsize',18)

% Nella figura 7 si mostrano i vari inputs che vengono definiti sulla base
% di differenti valori di lambda
%%%% plotting the inputs
figure(8); clf reset
v=0:ny;v2=0:ny2_new;
for k=1:length(lambda_new);
    kk=(k-1)/(length(lambda_new)-1);
    plot([0:nu_new-1,nu_new+2],[uopt{k};uopt{k}(end)],'linewidth',2,'color',[kk,0,1-kk]);
    hold on
end
c=legend('\lambda=0.01','\lambda=0.1','\lambda=1','\lambda=10','\lambda=100');
set(c,'fontsize',18)
title(['Inputs with n_y = ',num2str(ny),' n_u = ',num2str(nu_new)],'fontsize',18)

figure(9)
semilogx(lambda_new,J_lambda);
title('J vs \lambda','fontsize',18)
xlabel('\lambda','fontsize',18);
ylabel('J','fontsize',18);

a_new = [a];
b_new = [b];
nu_new = nu;
lambda_new = lambda;
sizey_new = sizey;
nu2_new = nu2;
ny2_new = ny2;

% In tale sezione si fanno delle computazioni in cui si effettuano varie
% predizioni sulla base di differenti valori di ny; i risultati di tale
% sezione vengono utilizzati per il plot delle figure 8 e 9.
ny_s=[nu_new, nu_new+5, nu_new+10, nu_new+20, nu_new+30];
Nk=cell(1);Dk=Nk;Pr=Nk;
Duopt=Nk;uopt=Nk;
yfut=Nk;yfut2=Nk;
y=Nk; Du=Nk;

for k=1:length(ny_s);
    [H,P,Q] = mpc_predmat(a_new,b_new,ny_s(k));   
    [H2,P2,Q2] = mpc_predmat(a_new,b_new,ny2_new);   
    
    [Nk{k},Dk{k},Pr{k},S,X,Prlong] = mpc_law(H,P,Q,nu_new,lambda_new,1,sizey_new);
    [y{k},~,Du{k},r] = mpc_simulate_noconstraints_without_plots(b_new,a_new,nu_new,ny_s(k),lambda_new,1,ref,dist,noise);
    HH=tril(ones(nu_new,nu_new));

    %%% Control trajectory for a step change in r
    Duopt{k} = Pr{k};
    yfut{k}=H(:,1:nu_new)*Duopt{k};    %%% prediction within J
    yfut2{k}=H2(:,1:nu_new)*Duopt{k};  %%% Longer range prediction
    uopt{k}=HH*Duopt{k};
    J_ny(k)=norm(r-y{k},2)^2+lambda_new*norm(Du{k},2)^2;
end

% Nella figura 10 si mostrano i vari inputs che vengono definiti sulla base
% di differenti valori di ny
figure(10); clf reset
lgd = cell(length(ny_s),1);
for k=1:length(ny_s)
    kk=(k-1)/(length(ny_s)-1);
    plot([0:nu_new-1,nu_new+2],[uopt{k};uopt{k}(end)],'linewidth',2,'color',[kk,0,1-kk]);
    lgd{k} = strcat('n_y=',num2str(ny_s(k)));
    hold on
end
c=legend(lgd);
set(c,'fontsize',18)
title(['Inputs with \lambda = ',num2str(lambda_new),', n_u = ',num2str(nu_new)],'fontsize',18)

% Nella figura 11 si va a fare il confronto della predizione sulla base di
% differenti valori di ny
figure(11); clf reset
ny_s=[nu_new, nu_new+5, nu_new+10, nu_new+20, nu_new+30];
plot([0 1 1 ny2_new],[0 0 1 1],'r--'); hold on
lgd = cell(length(ny_s),1);
lgd{1} = "set point";
for k=1:length(ny_s);
    [H,P,Q] = mpc_predmat(a_new,b_new,ny_s(k));   
    [H2,P2,Q2] = mpc_predmat(a_new,b_new,ny2_new);    
    
    %%%% mpc_law computes entire proposed trajectory
    [Nk,Dk,Pr,S,X,Prlong] = mpc_law(H,P,Q,nu_new,lambda_new,1,sizey_new);
    
    %%% Control trajectory for a step change in r
    Duopt = Pr;
    yfut2=H2(:,1:nu_new)*Duopt;  %%% Longer range prediction

    %%%% plotting predicition and u
    v2=0:ny2_new;
    
    kk=(k-1)/(length(ny_s)-1);
    plot(v2,[0;yfut2],'linewidth',2,'color',[kk,0,1-kk]);
    lgd{k+1} = strcat('n_y=',num2str(ny_s(k))) ;
    hold on
end
c=legend(lgd);
set(c,'fontsize',18)
title(['Outputs with n_u = ',num2str(nu_new),', \lambda = ',num2str(lambda_new)],'fontsize',18)

figure(12)
xlim([nu_new,nu_new+30])
plot(ny_s,J_ny);
title('J vs n_y','fontsize',18)
xlabel('n_y','fontsize',18);
ylabel('J','fontsize',18);

end