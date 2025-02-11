function params = loadMaglevParams()
    % Load parameters for the maglev system

    % Solenoids
    params.solenoids.x  = 0.02*[1,-1,0,0];
    params.solenoids.y  = 0.02*[0,0,1,-1];
    params.solenoids.r  = 0.0185/2*ones(1,4);
    params.solenoids.l  = 0.012*ones(1,4);
    params.solenoids.z  = params.solenoids.l/2;
    params.solenoids.nw = 480;

    % Permanent magnets
    params.permanent.x  = 0.028*[1,-1,1,-1];
    params.permanent.y  = 0.028*[1,1,-1,-1];
    params.permanent.r  = 0.01*ones(1,4);                                     
    params.permanent.l  = 0.009*ones(1,4);
    params.permanent.z  = params.permanent.l/2 + 0.0001;
    params.permanent.J  = 1.1; % North facing up

    % Levitating magnet
    params.magnet.r     = 0.025;                                              
    params.magnet.l     = 0.005;                                           
    params.magnet.J     = 1.0;                                           
    params.magnet.m     = 0.060;                                              
    params.magnet.I     = [
                            (params.magnet.m/12)*(3*params.magnet.r^2+params.magnet.l^2),...
                            (params.magnet.m/12)*(3*params.magnet.r^2+params.magnet.l^2),...
                            (1/2)*params.magnet.m*params.magnet.r^2
                          ];                
    params.magnet.n     = 100;                                                 

    % Sensors
    params.sensors.x  = [0];
    params.sensors.y  = [0];
    params.sensors.z  = [0];

    % Physical constants
    params.physical.g   = 9.81;  % Gravitational acceleration [m/s^2]
    params.physical.mu0 = 4*pi*1e-7;  % Permeability of free space
end