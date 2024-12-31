#pragma once

#include <caterpillar/stg_gate.hpp>
#include <easy/esop/esop.hpp>
#include <kitty/dynamic_truth_table.hpp>
#include <tweedledum/gates/mcmt_gate.hpp>
#include <tweedledum/networks/netlist.hpp>

namespace revkit
{

using truth_table_t = kitty::dynamic_truth_table;
using netlist_t = tweedledum::netlist<caterpillar::stg_gate>;
using gate_t = netlist_t::gate_type;
using esop_t = easy::esop::esop_t;
} // namespace revkit
