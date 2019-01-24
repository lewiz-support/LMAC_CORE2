library verilog;
use verilog.vl_types.all;
entity crc32_d8s is
    port(
        data            : in     vl_logic_vector(7 downto 0);
        seed            : in     vl_logic_vector(31 downto 0);
        crc             : out    vl_logic_vector(31 downto 0)
    );
end crc32_d8s;
