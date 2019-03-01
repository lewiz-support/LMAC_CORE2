library verilog;
use verilog.vl_types.all;
entity phy_emulator_10G is
    port(
        x_clk           : in     vl_logic;
        \reset_\        : in     vl_logic;
        fmac_speed      : in     vl_logic_vector(2 downto 0);
        rx_pkt_gen_sel  : in     vl_logic;
        xgmii_txd       : in     vl_logic_vector(63 downto 0);
        xgmii_txc       : in     vl_logic_vector(7 downto 0);
        xgmii_rxd       : out    vl_logic_vector(63 downto 0);
        xgmii_rxc       : out    vl_logic_vector(7 downto 0);
        test            : out    vl_logic
    );
end phy_emulator_10G;
