library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity top is
    port (
        fclk : in std_logic;
        insig : in std_logic;
        avrval : out unsigned(7 downto 0);
        perval : out unsigned(31 downto 0)
    );
end entity top;

architecture behavioral of top is

    signal insig_delayed : std_logic := '0';
    signal high_time_cnt : unsigned(31 downto 0) := (others => '0');
    signal low_time_cnt : unsigned(31 downto 0) := (others => '0');
    signal avrval_reg : unsigned(7 downto 0) := (others => '0');
    signal perval_reg : unsigned(31 downto 0) := (others => '0');

begin

    avrval <= avrval_reg;
    perval <= perval_reg;

    process(fclk)
        constant C_100 : unsigned(6 downto 0) := to_unsigned(100, 7);
        variable total_period_ext : unsigned(32 downto 0); 
        variable temp_calculation : unsigned(63 downto 0);
    begin
        if rising_edge(fclk) then
            insig_delayed <= insig;

            if insig_delayed = '1' and insig = '0' then
                
                total_period_ext := ('0' & high_time_cnt) + ('0' & low_time_cnt);

                if total_period_ext > 0 then

                    temp_calculation := resize(high_time_cnt * C_100, 64);
                    
                    avrval_reg <= resize(temp_calculation / resize(total_period_ext, 64), 8);

                    if total_period_ext(32) = '1' then
                        perval_reg <= (others => '1');
                    else
                        perval_reg <= resize(total_period_ext, 32);
                    end if;
                end if;

                high_time_cnt <= (others => '0');
                low_time_cnt <= to_unsigned(1, low_time_cnt'length);

            elsif insig = '1' then
                high_time_cnt <= high_time_cnt + 1;
            else 
                low_time_cnt <= low_time_cnt + 1;
            end if;

        end if;
    end process;

end architecture behavioral;