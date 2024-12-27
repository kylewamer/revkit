from revkit import truth_table, esop_from_pprm, esop_from_optimum_pkrm
import pytest

def test_pprm():
    tt = truth_table.from_expression("(a[bc])")
    esop_from_pprm(tt)

def test_pprm():
    tt = truth_table.from_expression("(a[bc])")
    esop_from_optimum_pkrm(tt)
