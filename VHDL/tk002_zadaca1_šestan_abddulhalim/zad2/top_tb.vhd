library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity top_tb is
end top_tb;

architecture Behavioral of top_tb is
    component top
        port (
            clk   : in std_logic;
            reset : in std_logic;
            hash  : in std_logic_vector(127 downto 0);
            key1  : out std_logic_vector(127 downto 0);
            key2  : out std_logic_vector(127 downto 0);
            olock : out std_logic
        );
    end component;
    
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal hash, key1, key2 : std_logic_vector(127 downto 0);
    signal olock : std_logic;
    
    constant CLK_PERIOD : time := 10 ns;
begin
    uut: top port map (
        clk => clk,
        reset => reset,
        hash => hash,
        key1 => key1,
        key2 => key2,
        olock => olock
    );
    
    clk_process: process
    begin
        clk <= '0';
        wait for CLK_PERIOD/2;
        clk <= '1';
        wait for CLK_PERIOD/2;
    end process;
    
    stim_proc: process
        variable key11, key21, correct_hash : std_logic_vector(127 downto 0);
    begin
        reset <= '1';
        hash <= (others => '0');
        wait for CLK_PERIOD * 2;
        reset <= '0';
        wait for CLK_PERIOD;
        
        hash <= (others => '0');
        wait until rising_edge(clk);
        wait for 1 ns;

        assert olock = '0'
        report "Pogresan"
        severity error;
        
        key11 := std_logic_vector(rotate_left(unsigned(key1), 10));
        key21 := std_logic_vector(rotate_right(unsigned(key2), 37));
        correct_hash := key11 xor key21;
        
        hash <= correct_hash;
        wait until rising_edge(clk);
        wait for 1 ns;

        assert olock = '1'
        report "Tacan"
        severity error;
        
        wait;
    end process;
end Behavioral;