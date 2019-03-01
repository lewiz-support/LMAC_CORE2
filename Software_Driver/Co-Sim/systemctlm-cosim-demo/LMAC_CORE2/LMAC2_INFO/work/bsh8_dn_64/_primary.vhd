library verilog;
use verilog.vl_types.all;
entity bsh8_dn_64 is
    port(
        shft            : in     vl_logic_vector(2 downto 0);
        din             : in     vl_logic_vector(63 downto 0);
        dout            : out    vl_logic_vector(63 downto 0)
    );
end bsh8_dn_64;
