#include <iostream>
#include <stdexcept>

#include "matrix.h"
#include "python_solvers.h"

#include "Python.h"

#define EPS 1e-12

#define ERROR_SUCCESS                               0
#define ERROR_FAILURE                              -1

void _assert(bool a)
{
    if (!a) throw std::runtime_error("Assertion failed.");
}

void test_solver1()
{
    CooMatrix A(4);
    A.add(0, 0, -1);
    A.add(1, 1, -1);
    A.add(2, 2, -1);
    A.add(3, 3, -1);
    A.add(0, 1, 2);
    A.add(1, 0, 2);
    A.add(1, 2, 2);
    A.add(2, 1, 2);
    A.add(2, 3, 2);
    A.add(3, 2, 2);

    double res[4] = {1., 1., 1., 1.};

    solve_linear_system(&A, res);
    _assert(fabs(res[0] - 0.2) < EPS);
    _assert(fabs(res[1] - 0.6) < EPS);
    _assert(fabs(res[2] - 0.6) < EPS);
    _assert(fabs(res[3] - 0.2) < EPS);
}

void test_solver2()
{
    CooMatrix A(4);
    A.add(0, 0, -1);
    A.add(1, 1, -1);
    A.add(2, 2, -1);
    A.add(3, 3, -1);
    A.add(0, 1, 2);
    A.add(1, 0, 2);
    A.add(1, 2, 2);
    A.add(2, 1, 2);
    A.add(2, 3, 2);
    A.add(3, 2, 2);

    double res[4] = {1., 1., 1., 1.};

    DenseMatrix B(&A);

    solve_linear_system_dense(&B, res);
    _assert(fabs(res[0] - 0.2) < EPS);
    _assert(fabs(res[1] - 0.6) < EPS);
    _assert(fabs(res[2] - 0.6) < EPS);
    _assert(fabs(res[3] - 0.2) < EPS);
}

void test_solver3()
{
    CooMatrix A(4);
    A.add(0, 0, -1);
    A.add(1, 1, -1);
    A.add(2, 2, -1);
    A.add(3, 3, -1);
    A.add(0, 1, 2);
    A.add(1, 0, 2);
    A.add(1, 2, 2);
    A.add(2, 1, 2);
    A.add(2, 3, 2);
    A.add(3, 2, 2);

    double res[4] = {1., 1., 1., 1.};

    solve_linear_system_numpy(&A, res);
    _assert(fabs(res[0] - 0.2) < EPS);
    _assert(fabs(res[1] - 0.6) < EPS);
    _assert(fabs(res[2] - 0.6) < EPS);
    _assert(fabs(res[3] - 0.2) < EPS);

    res = {1., 1., 1., 1.};
    solve_linear_system_scipy_umfpack(&A, res);
    _assert(fabs(res[0] - 0.2) < EPS);
    _assert(fabs(res[1] - 0.6) < EPS);
    _assert(fabs(res[2] - 0.6) < EPS);
    _assert(fabs(res[3] - 0.2) < EPS);

    res = {1., 1., 1., 1.};
    solve_linear_system_scipy_cg(&A, res);
    _assert(fabs(res[0] - 0.2) < EPS);
    _assert(fabs(res[1] - 0.6) < EPS);
    _assert(fabs(res[2] - 0.6) < EPS);
    _assert(fabs(res[3] - 0.2) < EPS);
}

int main(int argc, char* argv[])
{
    try {
        // This is a hack, this should be set somewhere else:
        putenv((char *)"PYTHONPATH=../..");
        Py_Initialize();
        PySys_SetArgv(argc, argv);

        test_solver1();
        test_solver2();
        test_solver3();

        return ERROR_SUCCESS;
    } catch(std::exception const &ex) {
        std::cout << "Exception raised: " << ex.what() << "\n";
        return ERROR_FAILURE;
    } catch(...) {
        std::cout << "Exception raised." << "\n";
        return ERROR_FAILURE;
    }
}
