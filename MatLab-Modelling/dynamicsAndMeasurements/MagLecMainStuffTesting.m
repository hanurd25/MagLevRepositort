
%Step 2: Setup of the UKF
%MATLAB provides an unscentedKalmanFilter function to handle nonlinear estimation.

% Define state transition and measurement functions
f = @(x, u) maglev_dynamics(x, u, 0.01);  % 10ms time step
h = @(x) [x(1); x(3)];  % Sensor measures position and tilt

% Initialize UKF
x0 = [0.05; 0; 0; 0];  % Initial position and tilt
ukf = unscentedKalmanFilter(f, h, x0);

% Define process and measurement noise covariances
ukf.ProcessNoise = diag([1e-4, 1e-3, 1e-4, 1e-3]);  
ukf.MeasurementNoise = diag([0.01, 0.01]);  

% Set UKF tuning parameters
ukf.Alpha = 1e-3;
ukf.Beta = 2;
ukf.Kappa = 0;
Step 3: Load and Process Sensor Data
Assuming your magnetic field data (Hall-effect sensor readings) is in a CSV file:

matlab
Copy
Edit
% Load data from CSV file
data = readmatrix('magnetic_field_data.csv');
time = data(:,1);
Bx = data(:,2);
By = data(:,3);
Bz = data(:,4);

% Preprocess data (lowpass filter to reduce noise)
filtered_Bx = lowpass(Bx, 10, 1000);
filtered_By = lowpass(By, 10, 1000);
filtered_Bz = lowpass(Bz, 10, 1000);
If sensor noise is high, apply a moving average filter:

matlab
Copy
Edit
windowSize = 5;
filtered_Bx = movmean(Bx, windowSize);
filtered_By = movmean(By, windowSize);
filtered_Bz = movmean(Bz, windowSize);
Step 4: Run the UKF for State Estimation
We now apply the UKF to estimate the magnet's position and orientation.

matlab
Copy
Edit
% Initialize storage
N = length(time);
x_est = zeros(4, N);

for k = 1:N
    % Control inputs (assumed known or estimated)
    u = [0; 0];  % Replace with actual control inputs if available
    
    % Get magnetometer readings (x and z position estimates)
    y_meas = [filtered_Bx(k); filtered_Bz(k)];

    % Predict and correct step
    predict(ukf, u);
    correct(ukf, y_meas);

    % Store estimated state
    x_est(:, k) = ukf.State;
end
Step 5: Visualizing the Results
To evaluate the UKF’s performance, plot the estimated and measured position and tilt angle.

matlab
Copy
Edit
% Plot estimated position vs measured data
figure;
subplot(2,1,1);
plot(time, x_est(1,:), 'r', 'LineWidth', 2); hold on;
plot(time, filtered_Bx, 'b--');
xlabel('Time (s)'); ylabel('Z Position');
legend('Estimated Z', 'Measured Z');
title('UKF - Position Estimation');
grid on;

subplot(2,1,2);
plot(time, x_est(3,:), 'g', 'LineWidth', 2); hold on;
plot(time, filtered_Bz, 'k--');
xlabel('Time (s)'); ylabel('Tilt Angle');
legend('Estimated Theta', 'Measured Theta');
title('UKF - Tilt Estimation');
grid on;