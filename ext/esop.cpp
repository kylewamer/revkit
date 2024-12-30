#include "types.hpp"
#include <easy/esop/constructors.hpp>
#include <easy/esop/esop_from_pkrm.hpp>
#include <easy/esop/esop_from_pprm.hpp>
#include <easy/esop/exact_synthesis.hpp>
#include <easy/esop/helliwell.hpp>
#include <kitty/cube.hpp>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace revkit
{

void esop( py::module m )

{
  using namespace py::literals;

  m.def( "esop_from_pprm", &easy::esop::esop_from_pprm<truth_table_t>, R"doc(
    Synthesizes a Positive Polarity Read-Muller (PPRM) expression (a special case of an ESOP form)
    using the algorithm described in [R. Drechsler, IEEE Trans. C 48(9), 1999, 987–990] and applies
    post-optimization to merge distance-1 cubes

    :param tt: Truth table

  )doc",
         "tt"_a );

  using stats_t = easy::esop::helliwell_maxsat_statistics; // struct to store SAT solver statistics
  using ps_t = easy::esop::helliwell_maxsat_params;        // struct to pass to SAT solver

  m.def(
      "esop_from_tt_maxsat_rc2", []( truth_table_t const& tt, std::function<int( const kitty::cube& )> cost_fn )
      {
    stats_t stats;
    ps_t ps;
    easy::esop::esop_from_tt<truth_table_t, easy::sat2::maxsat_rc2, easy::esop::helliwell_maxsat> synth(stats, ps);
   return synth.synthesize(tt, cost_fn); },
      R"doc(
    Computes ESOP representation using the maxsat_rc (relaxable cardinality constraints) MAX-SAT solver

    :param tt: Truth table
    :param cost_fn: Cost Function

  )doc",
      "tt"_a, "cost_fn"_a );

  m.def(
      "esop_from_tt_maxsat_uc", []( truth_table_t const& tt, std::function<int( const kitty::cube& )> cost_fn )
      {
    stats_t stats;
    ps_t ps;
    easy::esop::esop_from_tt<truth_table_t, easy::sat2::maxsat_uc, easy::esop::helliwell_maxsat> synth(stats, ps);
   return synth.synthesize(tt, cost_fn); },
      R"doc(
    Computes ESOP representation using maxsat_uc (unit clauses) MAX-SAT solver

    :param tt: Truth table
    :param cost_fn: Cost Function

  )doc",
      "tt"_a, "cost_fn"_a );

  m.def(
      "esop_from_tt_maxsat_linear", []( truth_table_t const& tt, std::function<int( const kitty::cube& )> cost_fn )
      {
    stats_t stats;
    ps_t ps;
    easy::esop::esop_from_tt<truth_table_t, easy::sat2::maxsat_linear, easy::esop::helliwell_maxsat> synth(stats, ps);
   return synth.synthesize(tt, cost_fn); },
      R"doc(
    Computes ESOP representation using maxsat_linear (linear search) MAX-SAT solver

    :param tt: Truth table
    :param cost_fn: Cost Function

  )doc",
      "tt"_a, "cost_fn"_a );

  m.def( "esop_from_optimum_pkrm", &easy::esop::esop_from_optimum_pkrm<truth_table_t>, R"doc(
    Computes ESOP representation using optimum Pseudo-Kronecker Read-Muller (PKRM).

    This algorithm first computes an ESOP using the algorithm described
    in [R. Drechsler, IEEE Trans. C 48(9), 1999, 987–990].

    The algorithm applies post-optimization to merge distance-1 cubes.

    :param tt Truth table:
)doc",
         "tt"_a );

  m.def(
      "print_esop_as_exprs", []( const esop_t& esop, const unsigned num_vars )
      { return easy::esop::print_esop_as_exprs( esop, num_vars ); },
      R"doc(
    Prints an ESOP as an expression.

    :param esop: ESOP
    :param num_vars: Number of variables

  )doc",
      "esop"_a, "num_vars"_a );

  m.def(
      "print_esop_as_cubes", []( const esop_t& esop, const unsigned num_vars )
      { return easy::esop::print_esop_as_cubes( esop, num_vars ); },
      R"doc(
    Prints an ESOP as a list of cubes.

    :param esop: ESOP
    :param num_vars: Number of variables

  )doc",
      "esop"_a, "num_vars"_a );

  m.def( "exact_esop", &easy::esop::exact_esop<truth_table_t>, R"doc(
    Synthesizes an exact ESOP form for a possibly incompletely-specified
    Boolean function using a formulation of Boolean learning.

    :param tt: Truth table

  )doc",
         "tt"_a );
}
} // namespace revkit
