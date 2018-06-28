library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all; 

entity multiplier is
    Port ( in_a : in  STD_LOGIC_VECTOR (31 downto 0);
           in_b : in  STD_LOGIC_VECTOR (31 downto 0);
           m_out : out  STD_LOGIC_VECTOR (31 downto 0));
end multiplier;

architecture Default_behavior of multiplier is

begin
	process(in_a,in_b)
		variable in_a_mantissa : STD_LOGIC_VECTOR (22 downto 0);
		variable in_a_exponent : STD_LOGIC_VECTOR (7 downto 0);
		variable in_a_sign : STD_LOGIC;
		variable in_b_mantissa : STD_LOGIC_VECTOR (22 downto 0);
		variable in_b_exponent : STD_LOGIC_VECTOR (7 downto 0);
		variable in_b_sign : STD_LOGIC;
		variable m_out_mantissa : STD_LOGIC_VECTOR (22 downto 0);
		variable m_out_exponent : STD_LOGIC_VECTOR (7 downto 0);
		variable m_out_sign : STD_LOGIC;
		variable mantissa_carry : STD_LOGIC;
		variable mantissa_result : STD_LOGIC_VECTOR (47 downto 0);
		variable exponent_sum : STD_LOGIC_VECTOR (8 downto 0);
   begin
		in_a_mantissa := x(22 downto 0);
		in_a_exponent := x(30 downto 23);
		in_a_sign := x(31);
		in_b_mantissa := y(22 downto 0);
		in_b_exponent := y(30 downto 23);
		in_b_sign := y(31);
		
		mantissa_result := ('1' & in_a_mantissa) * ('1' & in_b_mantissa);
		
		if (mantissa_result(47)='1') then 
			m_out_mantissa := aux2(46 downto 24) + aux2(23);
			mantissa_carry := '1';
		else
			m_out_mantissa := aux2(45 downto 23) + aux2(22);
			mantissa_carry := '0';
		end if;
		
		exponent_sum := ('0' & in_a_exponent) + ('0' & in_b_exponent) + mantissa_carry - 127;
		
		if (exponent_sum(8)='1') then -- Indica que houve overflow/underflow
			if (exponent_sum(7)='0') then -- overflow
				m_out_exponent := "11111111";
				m_out_mantissa := (others => '0');
				m_out_sign := in_a_sign xor in_b_sign;
			else 									-- underflow
				m_out_exponent := (others => '0');
				m_out_mantissa := (others => '0');
				m_out_sign := '0';
			end if;
		else -- Ocorreu tudo conforme esperado
			m_out_exponent := exponent_sum(7 downto 0);
			m_out_sign := in_a_sign xor in_b_sign;
		end if;
		

		m_out(22 downto 0) <= m_out_mantissa;
		m_out(30 downto 23) <= m_out_exponent;
		m_out(31) <= m_out_sign;

   end process;
end Default_behavior;