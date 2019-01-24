library verilog;
use verilog.vl_types.all;
entity gigerx_fifo256x8 is
    generic(
        WIDTH           : integer := 8;
        DEPTH           : integer := 256;
        PTR             : integer := 8
    );
    port(
        aclr            : in     vl_logic;
        wrclk           : in     vl_logic;
        wrreq           : in     vl_logic;
        data            : in     vl_logic_vector;
        full            : out    vl_logic;
        rdclk           : in     vl_logic;
        rdreq           : in     vl_logic;
        q               : out    vl_logic_vector;
        empty           : out    vl_logic;
        usedw           : out    vl_logic_vector
    );
end gigerx_fifo256x8;
