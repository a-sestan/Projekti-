library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity top_tb is
end entity top_tb;

architecture test of top_tb is
    constant CLK_PERIOD : time := 1 ns; 

    signal fclk : std_logic := '0';
    signal insig : std_logic := '0';
    signal avrval: unsigned(7 downto 0);
    signal perval: unsigned(31 downto 0);

begin
    
    DUT: entity work.top
        port map (
            fclk => fclk,
            insig => insig,
            avrval => avrval,
            perval => perval
        );

    clk_process: process
    begin
        fclk <= '0';
        wait for CLK_PERIOD / 2;
        fclk <= '1';
        wait for CLK_PERIOD / 2;
    end process clk_process;

    stimulus_process: process
    begin
        
        insig <= '0';
        wait for 20 ns;

        insig <= '1';
        wait for 20 ns;
        insig <= '0';
        wait for 20 ns;

        insig <= '1';
        wait for 60 ns;
        insig <= '0';
        wait for 10 ns;
        
        insig <= '1';
        wait for 30 ns;
        insig <= '0';
        wait for 20 ns;

        wait;
    end process stimulus_process;

end architecture test;