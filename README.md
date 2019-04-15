##

~~1. add and sub support~~  
~~2. atoi and python support~~  
~~3. cpp and python test cases~~  
~~1. mul and div support~~  
~~2. fine sub and support negative (with + - flag)~~  
~~1. refine mulT and mulSubT~~  
~~3. impl += -= *= /=~~  
~~2. impl mul with negative~~ 



~~1. impl (test) << and >>~~
~~2. impl get bits~~
3. pass all test

3. impl div
    0x03FF / 2 = 0x01FF
    [03, FF] -> [00, 03, 3F, FF]

4. impl mod with negative
5. python wrapper test
6. impl mod, mod_inverse, pow, [q, r = (a // b, x % y)]
7. remove some virtual function
8. impl wrapper for python and test


Note:
1. uint128_t += uint128_t, uint128_t -= uint128_t
2. uint128_t = uint128_t +/- uint128_t
3. uint128 *= uint128
4. uint128 = uint128 * uint128


R := N
D := D << n            -- R and D need twice the word width of N and Q
for i = n − 1 .. 0 do  -- for example 31..0 for 32 bits
  if R >= 0 then
    q[i] := +1
    R := 2 * R − D
  else
    q[i] := −1
    R := 2 * R + D
  end if
end
 
-- Note: N=Numerator, D=Denominator, n=#bits, R=Partial remainder, q(i)=bit #i of quotient.
