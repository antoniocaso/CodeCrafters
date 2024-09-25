function [] = plot_output_constraints(b,a,nu,ny,lambda,Dumax,umax,umin,ymax,ymin,ny2)
    ref = [zeros(1,25),ones(1,ny2)];
    dist=[zeros(1,ny2+25)];
    noise = [zeros(1,ny2+25)];
    mpc_simulate_outputconstraints(b,a,nu,ny,lambda,1,Dumax,umax,umin,ymax,ymin,ref,dist,noise);
end

