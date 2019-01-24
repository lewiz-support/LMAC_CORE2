library verilog;
use verilog.vl_types.all;
entity bsh32_dn_88 is
    port(
        shft            : in     vl_logic_vector(1 downto 0);
        din             : in     vl_logic_vector(87 downto 0);
        dout            : out    vl_logic_vector(87 downto 0)
    );
end bsh32_dn_88;
