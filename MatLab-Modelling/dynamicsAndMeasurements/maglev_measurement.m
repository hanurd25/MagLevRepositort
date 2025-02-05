function y = maglev_measurement(x)
    % Measurement function - Magnetic field sensing
    Bz = x(1);   % Assuming Bz directly relates to z-position
                 %Bald assumption really but we can scale it this way
    Bx = x(3);   % Assuming Bx relates to tilt angle
    y = [Bz; Bx]; % Magnetic field readings
end
