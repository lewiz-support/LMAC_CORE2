library verilog;
use verilog.vl_types.all;
entity g2x_ctrl is
    generic(
        GF_IDLE         : integer := 1;
        GF_RD_BCNT      : integer := 2;
        GF_BCNT_BUF     : integer := 4;
        GF_RD_DATA      : integer := 8;
        GF_DONE         : integer := 128
    );
    port(
        clk             : in     vl_logic;
        \reset_\        : in     vl_logic;
        mode_10G        : in     vl_logic;
        mode_5G         : in     vl_logic;
        mode_2p5G       : in     vl_logic;
        mode_1G         : in     vl_logic;
        gf_bcnt_empty   : in     vl_logic;
        data_in         : in     vl_logic_vector(63 downto 0);
        ctrl_in         : in     vl_logic_vector(7 downto 0);
        bcnt_in         : in     vl_logic_vector(15 downto 0);
        gige_bcnt_fifo_re: out    vl_logic;
        gige_data_fifo_re: out    vl_logic;
        data_out        : out    vl_logic_vector(63 downto 0);
        ctrl_out        : out    vl_logic_vector(7 downto 0);
        dbg             : out    vl_logic
    );
end g2x_ctrl;
