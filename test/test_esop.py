from revkit import (
    truth_table,
    cube,
    esop_from_pprm,
    esop_from_optimum_pkrm,
    exact_esop,
    esop_from_tt_maxsat_uc,
    esop_from_tt_maxsat_rc2,
    esop_from_tt_maxsat_linear,
)
import pytest

_num_vars = 3


@pytest.fixture
def truthtable():
    return truth_table.from_binary("10010110")


@pytest.fixture
def expected_esop():
    return [cube("1--"), cube("-1-"), cube("--1")]


@pytest.fixture
def cost_function() -> int:
    def cost_fn(_cube: cube):
        return _cube.num_literals + 1

    return cost_fn


def test_esop_from_optimum_pkrm(truthtable, expected_esop):
    esop = esop_from_optimum_pkrm(truthtable)
    assert esop == expected_esop


def test_esop_from_pprm(truthtable, expected_esop):
    esop = esop_from_pprm(truthtable)
    assert esop == expected_esop


def test_exact_esop(truthtable):
    esops = exact_esop(truthtable)
    assert len(esops) == 10


def test_esop_from_tt_maxsat_rc2(truthtable, expected_esop, cost_function):
    esop = esop_from_tt_maxsat_rc2(truthtable, cost_function)
    assert esop == expected_esop


def test_esop_from_tt_maxsat_linear(truthtable, cost_function):
    esop = esop_from_tt_maxsat_linear(truthtable, cost_function)
    assert esop == [cube("1--"), cube("-10"), cube("-01")]


def test_esop_from_tt_maxsat_uc(truthtable, cost_function):
    esop = esop_from_tt_maxsat_uc(truthtable, cost_function)
    assert esop == [cube("--0"), cube("-0-"), cube("1--")]
