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


https://blog.quarkslab.com/turning-regular-code-into-atrocities-with-llvm.html
https://github.com/quarkslab/llvm-passes/tree/master/llvm-passes

https://people.eecs.berkeley.edu/~fateman/282/F%20Wright%20notes/week5.pdf
https://www.researchgate.net/publication/221588714_Practical_Divide-and-Conquer_Algorithms_for_Polynomial_Arithmetic
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.47.565&rep=rep1&type=pdf
https://gmplib.org/manual/Divide-and-Conquer-Division.html

https://github.com/alexandrebk/divide-and-conquer-algorithm
https://gist.github.com/rvandervort/4695740
https://github.com/gnosis/solidity-arithmetic/blob/master/contracts/Arithmetic.sol

# important:
https://gist.github.com/tbuktu/1576025/9880f88da186fa2165eddb8bfb9734ce590b6aff
https://github.com/golang/go/issues/21960




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
