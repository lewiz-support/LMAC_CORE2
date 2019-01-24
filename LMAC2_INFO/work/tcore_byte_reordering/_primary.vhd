library verilog;
use verilog.vl_types.all;
entity tcore_byte_reordering is
    generic(
        LINK_FAIL       : integer := 1;
        LINK_RCVR       : integer := 2;
        LINK_GOOD       : integer := 4
    );
    port(
        clk250          : in     vl_logic;
        x_clk           : in     vl_logic;
        \reset_\        : in     vl_logic;
        fmac_rxd_en     : in     vl_logic;
        xaui_mode       : in     vl_logic;
        data_in         : in     vl_logic_vector(63 downto 0);
        ctrl_in         : in     vl_logic_vector(7 downto 0);
        data_out        : out    vl_logic_vector(63 downto 0);
        ctrl_out        : out    vl_logic_vector(7 downto 0);
        br_sof4         : out    vl_logic;
        RAW_FRAME_CNT   : out    vl_logic_vector(31 downto 0);
        BAD_FRAMESOF_CNT: out    vl_logic_vector(31 downto 0);
        init_done       : in     vl_logic;
        linkup          : out    vl_logic;
        rx_auto_clr_en  : in     vl_logic
    );
end tcore_byte_reordering;
