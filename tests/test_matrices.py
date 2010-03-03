from numpy import array

from _hermes_common import CooMatrix

eps = 1e-10

def test_coo1():
    m = CooMatrix(5)
    m.add(1, 3, 3.5)
    m.add(2, 3, 4.5)
    m.add(3, 4, 1.5)
    m.add(4, 2, 1.5)
    m.add(2, 3, 1)
    d1 = m.to_scipy_coo().todense()
    d2 = array([
        [0, 0, 0, 0, 0],
        [0, 0, 0, 3.5, 0],
        [0, 0, 0, 5.5, 0],
        [0, 0, 0, 0, 1.5],
        [0, 0, 1.5, 0, 0],
        ])
    assert (d1-d2 < eps).all()

def test_coo2():
    m = CooMatrix(5)
    m.add(1, 3, 3.5)
    m.add(2, 3, 4.5)
    m.add(3, 4, 1.5)
    m.add(0, 2, 1.5)
    m.add(2, 3, 1)
    d1 = m.to_scipy_coo().todense()
    d2 = array([
        [0, 0, 1.5, 0, 0],
        [0, 0, 0, 3.5, 0],
        [0, 0, 0, 5.5, 0],
        [0, 0, 0, 0, 1.5],
        [0, 0, 0, 0, 0],
        ])
    assert (d1-d2 < eps).all()
