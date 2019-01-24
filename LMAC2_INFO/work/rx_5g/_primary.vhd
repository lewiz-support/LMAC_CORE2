library verilog;
use verilog.vl_types.all;
entity rx_5g is
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
        linkup_1g       : out    vl_logic;
        linkup_5g       : out    vl_logic
    );
end rx_5g;
