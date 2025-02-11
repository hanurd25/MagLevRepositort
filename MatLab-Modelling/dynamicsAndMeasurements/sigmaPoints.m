function [X, Wm, Wc] = sigmaPoints(x, P, lambda, gamma, alpha, beta)
    L = numel(x);
    S = chol(P, 'lower');
    X = [x, x + gamma * S, x - gamma * S];
    Wm = [lambda/(L+lambda), repmat(1/(2*(L+lambda)), 1, 2*L)];
    Wc = Wm;
    Wc(1) = Wc(1) + (1 - alpha^2 + beta);
end
