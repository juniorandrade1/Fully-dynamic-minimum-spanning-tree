# Incremental Fully Dynamic MST

C++ code and dataset about incremental fully dynamic minimum spanning tree.

The code that uses Demaine et. al reduction from partial retroactivity to full retroactivity + Sleator and Tarjan link-cut tree data structure can be find inside the `/codes` path.

## Usage and input description

The inputs are given through `stdin` using the following format:

- 3 integers `n` `m` `q`, the number of vertices on graph, the number of initial vertices on graph, and the number of retroactive operations
- `m` lines containing 3 integers `x_i` `y_i` `w_i`, representing a bidirectional edge between `x_i` and `y_i` with cost `w_i`
- `q` lines contaning the retroactive operations. Each line will contain a integer `op` representing the operation performed. If `op = 0`, a query operation is requested, so, a integer `t` follows, representing the minimum spanning tree query in the version of time `t^th` of `G`. Otherwise, there will be four integers `x_i` `y_i` `w_i` `t_i`, representing an bidirectional edge inserction between `x_i` and `y_i` with cost `w_i`at time `t_i`.
 
Each query operation, i.e. retroactive operation with `op = 0` will output the minimum spanning tree on graph `G` at time `t` through `stdout`.



License
----

MIT
