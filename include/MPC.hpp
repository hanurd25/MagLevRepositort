
#ifndef MAGLEVCONTROL_MPC_HPP
#define MAGLEVCONTROL_MPC_HPP

#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <sstream>


class MPC {
public:
    MPC(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B, const Eigen::MatrixXd& C,
        const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R, int Np, int Nc);

    ~MPC();

    Eigen::VectorXd computeControl(const Eigen::VectorXd& x0, const Eigen::VectorXd& ref);

private:
    // System matrices
    Eigen::MatrixXd A_, B_, C_;
    Eigen::MatrixXd Q_, R_;

    // Prediction and control horizons
    int Np_, Nc_;

    // Precomputed matrices for optimization
    Eigen::MatrixXd H_; // Hessian matrix
    Eigen::VectorXd f_; // Gradient vector

    // Constraints
    Eigen::MatrixXd A_eq_; // Equality constraint matrix
    Eigen::VectorXd b_eq_; // Equality constraint vector
};


#endif //MAGLEVCONTROL_MPC_HPP
