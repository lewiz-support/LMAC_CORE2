library verilog;
use verilog.vl_types.all;
entity gige_tx_gmii is
    generic(
        IDLE            : integer := 1;
        GET_WAIT1       : integer := 2;
        GET_WAIT2       : integer := 4;
        TX_DAT          : integer := 8;
        TX_CRC          : integer := 16;
        WAIT_S          : integer := 32;
        DAT_I           : integer := 1;
        DAT_0           : integer := 2;
        DAT_1           : integer := 4;
        DAT_2           : integer := 8;
        DAT_3           : integer := 16;
        DAT_4           : integer := 32;
        DAT_5           : integer := 64;
        DAT_6           : integer := 128;
        DAT_7           : integer := 256
    );
    port(
        clk250          : in     vl_logic;
        clk125          : in     vl_logic;
        \rst_\          : in     vl_logic;
        rts             : in     vl_logic;
        rdata           : in     vl_logic_vector(63 downto 0);
        rbytes          : in     vl_logic_vector(15 downto 0);
        cts             : out    vl_logic;
        gmii_txd        : out    vl_logic_vector(7 downto 0);
        gmii_txc        : out    vl_logic;
        gmii_tx_en      : out    vl_logic;
        gmii_tx_vld     : out    vl_logic;
        FMAC_TX_PKT_CNT : out    vl_logic_vector(31 downto 0);
        FMAC_TX_BYTE_CNT: out    vl_logic_vector(31 downto 0);
        fmac_tx_clr_en  : in     vl_logic
    );
end gige_tx_gmii;
