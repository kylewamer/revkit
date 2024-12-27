#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <kitty/cube.hpp>
#include <easy/esop/esop_from_pkrm.hpp>
#include <easy/esop/esop_from_pprm.hpp>
#include <easy/esop/exact_synthesis.hpp>
#include <easy/esop/constructors.hpp>
#include <easy/esop/helliwell.hpp>
#include "types.hpp"

namespace py = pybind11;

namespace revkit
{

void esop( py::module m )

{
  using namespace py::literals;

  m.def( "esop_from_pprm", &easy::esop::esop_from_pprm<truth_table_t>, R"doc(
    Computes ESOP representation using PPRM

    :param tt: Truth table

  )doc", "tt"_a );
// How can I pass my own cost_function to this algorithm?
// What about different maxsat algorithms -- should I create one function for each that exposes them?
// linting for c++?
  m.def( "esop_from_tt_maxsat", [](truth_table_t const& tt){
    easy::esop::helliwell_maxsat_statistics stats; // struct to store SAT solver statistics
    easy::esop::helliwell_maxsat_params ps;        // struct to pass to SAT solver
    auto cost_fn = [](const kitty::cube& cube) -> int {return cube.num_literals()+1;};
    easy::esop::esop_from_tt<truth_table_t, easy::sat2::maxsat_rc2, easy::esop::helliwell_maxsat> synth(stats, ps);
   return synth.synthesize(tt, cost_fn);
  }
, R"doc(
    Computes ESOP representation using SAT solver

    :param tt: Truth table

  )doc", "tt"_a );

  m.def( "esop_from_optimum_pkrm", &easy::esop::esop_from_optimum_pkrm<truth_table_t>, R"doc(
    Computes ESOP representation using optimum PKRM
    Pseudo-Kronecker Read-Muller (PKRM)

    This algorithm first computes an ESOP using the algorithm described
    in [R. Drechsler, IEEE Trans. C 48(9), 1999, 987–990].

    The algorithm applies post-optimization to merge distance-1 cubes.
    
    :param tt Truth table:
)doc", "tt"_a );

  m.def( "print_esop_as_exprs", [](const esop_t& esop, const unsigned num_vars){
    return easy::esop::print_esop_as_exprs(esop, num_vars);}, R"doc(
    Print ESOP as an expression.
    Positive Polarity Read-Muller (PPRM)

    :param esop: ESOP
    :param num_vars: Number of variables

  )doc", "esop"_a, "num_vars"_a);

  m.def( "exact_esop", &easy::esop::exact_esop<truth_table_t>, R"doc(
    Synthesizes an exact ESOP form for a possibly incompletely-specified
    Boolean function using a formulating of Boolean learning.

    :param tt: Truth table

  )doc", "tt"_a );
}
}
