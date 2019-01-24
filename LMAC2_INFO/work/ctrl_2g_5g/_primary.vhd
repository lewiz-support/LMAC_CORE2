library verilog;
use verilog.vl_types.all;
entity ctrl_2g_5g is
    generic(
        LINK_FAIL       : integer := 1;
        LINK_RCVR       : integer := 2;
        LINK_GOOD       : integer := 4
    );
    port(
        clk             : in     vl_logic;
        \reset_\        : in     vl_logic;
        mode_10G        : in     vl_logic;
        mode_5G         : in     vl_logic;
        mode_2p5G       : in     vl_logic;
        mode_1G         : in     vl_logic;
        data_in         : in     vl_logic_vector(63 downto 0);
        ctrl_in         : in     vl_logic_vector(7 downto 0);
        data_out        : out    vl_logic_vector(63 downto 0);
        ctrl_out        : out    vl_logic_vector(7 downto 0);
        we_5g           : out    vl_logic;
        x_byte_cnt      : out    vl_logic_vector(15 downto 0);
        x_bcnt_we       : out    vl_logic;
        linkup_5g       : out    vl_logic
    );
end ctrl_2g_5g;
