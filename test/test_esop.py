from revkit import truth_table, esop_from_pprm, esop_from_optimum_pkrm, exact_esop, esop_from_tt_maxsat, print_esop_as_exprs
import pytest

_num_vars = 3

@pytest.fixture
def truthtable():
    return truth_table.from_binary("10010110")

def test_esop_from_optimum_pkrm(truthtable):
    esop = esop_from_optimum_pkrm(truthtable)
    print_esop_as_exprs(esop, _num_vars)

def test_esop_from_pprm(truthtable):
    esop = esop_from_pprm(truthtable)
    print_esop_as_exprs(esop, _num_vars)

def test_exact_esop(truthtable):
    esops = exact_esop(truthtable)
    for esop in esops:
        print_esop_as_exprs(esop, _num_vars)

def test_esop_from_tt_maxsat(truthtable):
    esop = esop_from_tt_maxsat(truthtable)
    print_esop_as_exprs(esop, _num_vars)