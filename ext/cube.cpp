#include <kitty/cube.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace revkit
{

void cube( py::module m )
{
  py::class_<kitty::cube> _cube( m, "cube", "Cube data structure" );
  _cube.def( py::init<>(), "Constructs the empty cube" );
  _cube.def( py::init<const std::string&>(), "Constructs a cube from bits and mask" );
  _cube.def( "__eq__", &kitty::cube::operator== );
  _cube.def_property_readonly( "num_literals", &kitty::cube::num_literals, "Number of Literals" );
}
} // namespace revkit
