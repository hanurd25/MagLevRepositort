function x_next = maglev_dynamics(x, u, dt)
    % System parameters
    m = 0.1;   % Mass of the levitating magnet (kg)
    g = 9.81;  % Gravity (m/s^2)
    k = 2.5;   % Electromagnetic force coefficient (N/A)

    % Extract states
    z = x(1);        % Vertical position
    vz = x(2);       % Vertical velocity
    theta = x(3);    % Tilt angle
    omega = x(4);    % Angular velocity

    % Compute forces
    F_em = k * u;  % Electromagnetic force
    F_net = F_em - m*g;

    % State update equations (Euler integration)
    z_next = z + dt * vz;
    vz_next = vz + dt * (F_net / m);
    theta_next = theta + dt * omega;
    omega_next = omega; % Assuming no external torque

    % Output next state
    x_next = [z_next; vz_next; theta_next; omega_next];
end
