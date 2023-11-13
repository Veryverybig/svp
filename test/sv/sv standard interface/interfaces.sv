interface cpu_mem_if;
    logic req;
    logic ack;
    logic[ 47:0] addr;
    logic[511:0] data;

    modport tx (
        output req, addr,
        input  ack, data
    );

    modport rx (
        input  req, addr,
        output ack, data
    );
endinterface