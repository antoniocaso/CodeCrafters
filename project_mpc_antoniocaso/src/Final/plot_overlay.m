function [] = plot_overlay(b,a,nu,ny,lambda,Dumax,umax,umin,ny2)
    ref = [zeros(1,25),ones(1,ny2)];
    dist=[zeros(1,ny2+25)];
    noise = [zeros(1,ny2+25)];
    mpc_simulate_overlay(b,a,nu,ny,lambda,1,Dumax,umax,umin,ref,dist,noise);
end
