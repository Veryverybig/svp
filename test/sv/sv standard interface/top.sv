module top;

cpu_mem_if i_cpu_mem_if();

cpu m_cpu(
    .cpu_mem (i_cpu_mem_if.tx)
);

mem m_mem(
    .cpu_mem (i_cpu_mem_if.rx)
);


endmodule