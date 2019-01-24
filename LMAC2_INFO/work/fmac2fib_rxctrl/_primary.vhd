library verilog;
use verilog.vl_types.all;
entity fmac2fib_rxctrl is
    generic(
        DATA_WIDTH      : integer := 64;
        BCNT_WIDTH      : integer := 32;
        BR_IDLE         : integer := 1;
        BR_CHECKRX      : integer := 2;
        BR_READCNT      : integer := 4;
        BR_RDDATA       : integer := 8;
        BR_DONE         : integer := 16
    );
    port(
        clk_fib         : in     vl_logic;
        \reset_\        : in     vl_logic;
        wren_rf         : out    vl_logic;
        wren_rcf        : out    vl_logic;
        datain_rf       : out    vl_logic_vector;
        datain_rcf      : out    vl_logic_vector;
        wrempty_rf      : in     vl_logic;
        wrempty_rcf     : in     vl_logic;
        fib_rx_mac_data_empty: in     vl_logic;
        fib_rx_mac_pkt_data: in     vl_logic_vector;
        fib_rx_mac_ipcs_empty: in     vl_logic;
        fib_rx_mac_ipcs_data: in     vl_logic_vector;
        fib_rx_mac_rdcycle: out    vl_logic;
        fib_rx_mac_rd   : out    vl_logic;
        fib_rx_mac_ipcs_rd: out    vl_logic;
        test            : out    vl_logic
    );
end fmac2fib_rxctrl;
