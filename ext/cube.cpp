#include <pybind11/pybind11.h>
#include <kitty/cube.hpp>

namespace py = pybind11;

namespace revkit
{

void cube( py::module m )
{
  py::class_<kitty::cube> _cube( m, "cube", "Cube data structure" );
  _cube.def_property_readonly( "num_literals", &kitty::cube::num_literals, "Number of Literals" );
}
}
