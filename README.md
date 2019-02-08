##

~~ 1. add and sub support ~~
~~ 2. atoi and python support ~~
~~ 3. cpp and python test cases ~~

1. mul and div support
2. refine constructor, and dict input
3. fine sub and support negative (with + - flag)
4. impl += -= *= /=
5. impl mod, mod_inverse, pow, [q, r = (a // b, x % y)]
6. if uint128_add impl cc flag, so that uint256_t could use it


Note:
1. uint128_t += uint128_t, uint128_t -= uint128_t
2. uint128_t = uint128_t +/- uint128_t


https://blog.quarkslab.com/turning-regular-code-into-atrocities-with-llvm.html
https://github.com/quarkslab/llvm-passes/tree/master/llvm-passes

/*
    uint64_t spill = 0;
    asm("mul %5             \n\t"  // rdx:rax = this->lo_ * value
        "mov %%rax, %0      \n\t"  // res.lo_ = rax
        "mov %%rbx, %%rax   \n\t"  // rax = this->hi_
        "mov %%rdx, %%rbx   \n\t"  // rbx = spill
        "mul %5             \n\t"  // rdx:rax = this->hi_ * value
        "add %%rbx, %%rax   \n\t"  // rax += spill
        "adc $0, %%rdx      \n\t"  // rdx += carry_bit
        : "=r"(lo), "=a"(hi), "=d"(spill)
        : "a"(lo), "b"(hi), "r"(value)
        : "cc");
*/
