#include <iostream>
#include <stdexcept>

#include "matrix.h"

#define ERROR_SUCCESS                               0
#define ERROR_FAILURE                              -1

void _assert(bool a)
{
    if (!a) throw std::runtime_error("Assertion failed.");
}

void test_vector1()
{
    AVector m(3);
    _assert(m.get_size() == 3);
    m.add(0, 3.5);
    m.add(1, 4.5);
    m.add(2, 1.5);
    m.add(1, 1);
    m.add(0, 2.5);
    m.print();
}

void test_vector2()
{
    AVector m(5, true);
    m.add(1, cplx(2.3, 3.5));
    m.add(2, cplx(1.2, 4.5));
    m.add(3, cplx(2, 1.5));
    m.add(4, cplx(4.3, 1.5));
    m.add(2, cplx(4.1, 1));
    m.print();
}

/*
#include "python_api.h"

void test_matrix5()
{
    DenseMatrix m(3);
    m.add(0, 2, 3.5);
    m.add(1, 2, 4.5);
    m.add(2, 1, 1.5);
    m.add(1, 2, 1);
    m.add(0, 0, 2.5);
    printf("Dense Matrix\n");

    Python p;
    p.push("m", c2py_DenseMatrix(&m));
    p.exec("print m");
    p.exec("d = m.to_numpy()");
    p.exec("print d");
    p.exec("eps = 1e-10");
    p.exec("assert abs(d[0, 0]-2.5) < eps");
    p.exec("assert abs(d[0, 2]-3.5) < eps");
    p.exec("assert abs(d[1, 2]-5.5) < eps");
    p.exec("assert abs(d[2, 1]-1.5) < eps");
    p.exec("assert abs(d[0, 1]-0.0) < eps");
}
*/

int main(int argc, char* argv[])
{
    try {
        test_vector1();
        test_vector2();

        return ERROR_SUCCESS;
    } catch(std::exception const &ex) {
        std::cout << "Exception raised: " << ex.what() << "\n";
        return ERROR_FAILURE;
    } catch(...) {
        std::cout << "Exception raised." << "\n";
        return ERROR_FAILURE;
    }
}
