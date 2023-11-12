interface mem_req;
    tx logic       valid;
    rx logic       ready;
    tx logic[31:0] data0;
    tx logic[31:0] data1;
    tx logic[31:0] data2;
    tx logic[31:0] data3;
endinterface

interface _clk_rst;
    logic clk;
    logic rstn;
    logic rstn;
endinterface