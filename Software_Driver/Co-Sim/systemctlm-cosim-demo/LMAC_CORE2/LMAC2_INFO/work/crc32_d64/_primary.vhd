library verilog;
use verilog.vl_types.all;
entity crc32_d64 is
    port(
        data            : in     vl_logic_vector(63 downto 0);
        crc             : out    vl_logic_vector(31 downto 0)
    );
end crc32_d64;
