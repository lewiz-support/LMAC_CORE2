library verilog;
use verilog.vl_types.all;
entity fib2fmac_txctrl is
    generic(
        DATA_WIDTH      : integer := 64;
        BCNT_WIDTH      : integer := 32;
        WR_IDLE         : integer := 1;
        WR_CNT          : integer := 2;
        WR_DATA         : integer := 4;
        WR_DONE         : integer := 8
    );
    port(
        clk_fib         : in     vl_logic;
        \reset_\        : in     vl_logic;
        rdempty_wf      : in     vl_logic;
        rdempty_wcf     : in     vl_logic;
        dataout_wf      : in     vl_logic_vector;
        dataout_wcf     : in     vl_logic_vector;
        rden_wf         : out    vl_logic;
        rden_wcf        : out    vl_logic;
        fib_mac_usedw   : in     vl_logic_vector(12 downto 0);
        fib_mac_data    : out    vl_logic_vector;
        fib_mac_wr      : out    vl_logic;
        fib_mac_ipcs_data: out    vl_logic_vector;
        fib_mac_ipcs_wr : out    vl_logic;
        test            : out    vl_logic
    );
end fib2fmac_txctrl;
