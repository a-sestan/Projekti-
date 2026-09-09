library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity top is
    port (
        clk   : in std_logic;
        reset : in std_logic;
        hash  : in std_logic_vector(127 downto 0);
        key1  : out std_logic_vector(127 downto 0);
        key2  : out std_logic_vector(127 downto 0);
        olock : out std_logic
    );
end top;

architecture Behavioral of top is
    constant KEY1_INIT : std_logic_vector(127 downto 0) := x"4946594F5543414E5245414454484953";
    constant KEY2_INIT : std_logic_vector(127 downto 0) := x"414C4C495357454C4C57495448594F55";
    
    signal key1_reg, key2_reg : std_logic_vector(127 downto 0) := KEY1_INIT;
    signal new_key1, new_key2 : std_logic_vector(127 downto 0);
    signal olock_reg : std_logic := '0';
    
    signal key11, key21, ihash : std_logic_vector(127 downto 0);
begin
    key1 <= key1_reg;
    key2 <= key2_reg;
    olock <= olock_reg;
    
    key11 <= std_logic_vector(rotate_left(unsigned(key1_reg), 10));  
    key21 <= std_logic_vector(rotate_right(unsigned(key2_reg), 37)); 
    ihash <= key11 xor key21;
    
    new_key1 <= std_logic_vector(shift_right(unsigned(key1_reg), 57) xor unsigned(key2_reg));
    new_key2 <= std_logic_vector(shift_left(unsigned(key2_reg), 41) xor unsigned(key1_reg));
    
    process(clk, reset)
    begin
        if reset = '1' then
            key1_reg <= KEY1_INIT;
            key2_reg <= KEY2_INIT;
            olock_reg <= '0';
        elsif rising_edge(clk) then
            if hash = ihash then
                olock_reg <= '1';
            else
                olock_reg <= '0';
            end if;
            
            key1_reg <= new_key1;
            key2_reg <= new_key2;
        end if;
    end process;
end Behavioral;