

#include "../include/MPC.hpp"
#include <iostream>
#include <osqp.h>

MPC::MPC(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B, const Eigen::MatrixXd& C,
         const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R, int Np, int Nc)
        : A_(A), B_(B), C_(C), Q_(Q), R_(R), Np_(Np), Nc_(Nc) {
    // Precompute matrices for the QP problem
    // Formulate Hessian (H_) and gradient (f_) matrices
    // Construct constraints (A_eq_, b_eq_)
    // Example for H_: H = B.T * Q * B + R
    Eigen::MatrixXd Phi = Eigen::MatrixXd::Zero(A.rows() * Np, A.cols());
    Eigen::MatrixXd Gamma = Eigen::MatrixXd::Zero(A.rows() * Np, B.cols() * Nc);

    // Populate Phi and Gamma
    Eigen::MatrixXd Ak = Eigen::MatrixXd::Identity(A.rows(), A.cols());
    for (int i = 0; i < Np; ++i) {
        Phi.block(i * A.rows(), 0, A.rows(), A.cols()) = Ak;
        Ak *= A;
        for (int j = 0; j < Nc; ++j) {
            if (i >= j) {
                Gamma.block(i * A.rows(), j * B.cols(), A.rows(), B.cols()) = Ak * B;
            }
        }
    }

    H_ = Gamma.transpose() * Q_.replicate(Np_, Np_) * Gamma + R_.replicate(Nc_, Nc_);
    f_ = Eigen::VectorXd::Zero(H_.rows());
}

MPC::~MPC() {}

/*
Eigen::VectorXd MPC::computeControl(const Eigen::VectorXd& x0, const Eigen::VectorXd& ref) {
    // Compute equality constraints
    b_eq_ = Eigen::VectorXd::Zero(A_eq_.rows());
    b_eq_.segment(0, x0.size()) = A_ * x0;

    // Solve QP problem using OSQP
    OSQPWorkspace* work;
    OSQPSettings* settings;
    OSQPData* data;

    // Set up QP problem here
    // ...

    // Solve QP
    // ...

    // Return optimal control input
    Eigen::VectorXd u_opt = Eigen::VectorXd::Zero(Nc_ * B_.cols());
    return u_opt;
}*/

Eigen::VectorXd MPC::computeControl(const Eigen::VectorXd& x0, const Eigen::VectorXd& ref) {
    // Equality constraints: A_eq u = b_eq
    b_eq_ = Phi_ * x0; // Compute based on initial state

    // Set OSQP problem data
    OSQPSettings *settings = (OSQPSettings *)c_malloc(sizeof(OSQPSettings));
    OSQPData *data = (OSQPData *)c_malloc(sizeof(OSQPData));

    if (!settings || !data) {
        std::cerr << "Failed to allocate OSQP settings or data." << std::endl;
        return Eigen::VectorXd::Zero(Nc_ * B_.cols());
    }

    // Populate data for OSQP
    data->n = H_.rows(); // Number of variables
    data->m = A_eq_.rows() + A_ineq_.rows(); // Number of constraints

    // Hessian matrix (objective)
    data->P = csc_matrix(H_.rows(), H_.cols(), H_.nonZeros(), H_.valuePtr(), H_.innerIndexPtr(), H_.outerIndexPtr());

    // Linear term in objective
    data->q = f_.data();

    // Constraint matrices
    data->A = csc_matrix(A_eq_.rows() + A_ineq_.rows(), H_.cols(),
                         A_eq_.nonZeros() + A_ineq_.nonZeros(),
                         A_eq_.valuePtr(), A_eq_.innerIndexPtr(), A_eq_.outerIndexPtr());

    // Constraint bounds
    data->l = Eigen::VectorXd::Zero(data->m).data(); // Lower bounds
    data->u = Eigen::VectorXd::Zero(data->m).data(); // Upper bounds

    // Settings
    osqp_set_default_settings(settings);
    settings->alpha = 1.0; // Relaxation parameter

    // Workspace
    OSQPWorkspace *work = osqp_setup(data, settings);

    // Solve problem
    osqp_solve(work);

    // Extract solution
    Eigen::VectorXd u_opt = Eigen::Map<Eigen::VectorXd>(work->solution->x, Nc_ * B_.cols());

    // Cleanup
    osqp_cleanup(work);
    c_free(data);
    c_free(settings);

    return u_opt;
}
