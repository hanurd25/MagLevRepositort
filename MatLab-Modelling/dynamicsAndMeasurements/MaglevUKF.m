classdef MaglevUKF
    properties
        UKF;            % Unscented Kalman Filter object
        State;          % Current estimated state
        ProcessNoise;   % Process noise covariance matrix
        MeasurementNoise; % Measurement noise covariance matrix
    end
    
    methods
        %% Constructor
        function obj = MaglevUKF()
            f = @(x, u) maglev_dynamics(x, u, 0.01); 
            
            % Define measurement function (Hall-effect sensor readings)
            h = @(x) maglev_measurement(x);
            
            % Initial state estimate: [z, dz, theta, dtheta]
            x0 = [0.05; 0; 0; 0];  
            
            % Create Unscented Kalman Filter object
            obj.UKF = unscentedKalmanFilter(f, h, x0);
            
            % Define process noise covariance (uncertainty in dynamics)
            obj.ProcessNoise = diag([1e-4, 1e-3, 1e-4, 1e-3]);  
            
            % Define measurement noise covariance (sensor noise)
            obj.MeasurementNoise = diag([0.01, 0.01]);  
            
            % Set UKF noise parameters
            obj.UKF.ProcessNoise = obj.ProcessNoise;
            obj.UKF.MeasurementNoise = obj.MeasurementNoise;
            
            % UKF Tuning parameters
            obj.UKF.Alpha = 1e-3;
            obj.UKF.Beta = 2;
            obj.UKF.Kappa = 0;
            
            % Initialize state
            obj.State = obj.UKF.State;
        end
        
        %% Prediction Step
        function obj = predictStep(obj, u)
            predict(obj.UKF, u);
            obj.State = obj.UKF.State;
        end
        
        %% Correction Step (Update State with Sensor Data)
        function obj = correctStep(obj, y_meas)
            correct(obj.UKF, y_meas);
            obj.State = obj.UKF.State;
        end
    end
end
