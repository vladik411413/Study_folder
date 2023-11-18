import pytest
from Alexandrov_3 import SqlConnect


def test_func():
    db = SqlConnect('sqlite_python.db')
    assert db.request("SELECT COUNT(1) FROM sqlite_master")[0][0] == 2

"""
============================= test session starts =============================
collecting ... collected 1 item

test.py::test_func FAILED                                                [100%]
test.py:4 (test_func)
3 != 2

Expected :2
Actual   :3
<Click to see difference>

def test_func():
        db = SqlConnect('sqlite_python.db')
>       assert db.request("SELECT COUNT(1) FROM sqlite_master")[0][0] == 2
E       assert 3 == 2

test.py:7: AssertionError


============================== 1 failed in 0.08s ==============================
"""