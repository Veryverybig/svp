Generate module wrapper based on interface definitions. Similar to the interface definition in SystemVerilog,
the signals can be listed in definition and two default modport are provided as `tx` and `rx`.
When generating the wrapper, the desired modport should be specified.

in default, the generated signals has interface name as prefix, but this can be avoided using interface name starts with `_`,
for example `_clk_rst`, `_cg`.
```
interface _clk_rst;
    logic clk;
    logic hard_rstn;
    logic soft_rstn;
    // ...
endinterface
```
This tool does not check if there are duplicated names which causes a compilation error.
