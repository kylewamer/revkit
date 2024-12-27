#include <pybind11/pybind11.h>

#include <tweedledum/algorithms/decomposition/dt.hpp>

#include "types.hpp"

namespace py = pybind11;

namespace revkit
{

void qubit( py::module m );
void gate( py::module m );
void netlist( py::module m );
void truth_table( py::module m );
void esop( py::module m);
void decomposition( py::module m );
void synthesis( py::module m );
void cube( py::module m);
}

PYBIND11_MODULE( _revkit, m )
{
  revkit::qubit( m );
  revkit::gate( m );
  revkit::netlist( m );
  revkit::truth_table( m );
  revkit::esop( m );
  revkit::decomposition( m );
  revkit::synthesis( m );
  revkit::cube( m );
}
