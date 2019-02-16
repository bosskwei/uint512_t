#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <regex>
#include <string>
#include <uint512_t/uint512_t.hpp>

namespace test_op {
void test_add64() {
    {
        uint64_t dst = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 0;
        uint64_t carry = 1;
        op::add64(dst, value, carry);
        assert(dst == 0 and carry == 1);
    }
    {
        uint64_t dst = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 1;
        uint64_t carry = 0;
        op::add64(dst, value, carry);
        assert(dst == 0 and carry == 1);
    }
    {
        uint64_t dst = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 0xFFFFFFFFFFFFFFFF;
        uint64_t carry = 1;
        op::add64(dst, value, carry);
        assert(dst == 0xFFFFFFFFFFFFFFFF and carry == 1);
    }
    std::cout << "op::test_add64() passed." << std::endl;
}
void test_add12864() {
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 0;
        uint64_t carry = 1;
        op::add12864(hi, lo, value, carry);
        assert(hi == 0 and lo == 0 and carry == 1);
    }
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 1;
        uint64_t carry = 0;
        op::add12864(hi, lo, value, carry);
        assert(hi == 0 and lo == 0 and carry == 1);
    }
    std::cout << "op::test_add12864() passed." << std::endl;
}
void test_add128() {
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t vhi = 0x0;
        uint64_t vlo = 0x0;
        uint64_t carry = 1;
        op::add128(hi, lo, vhi, vlo, carry);
        assert(hi == 0 and lo == 0 and carry == 1);
    }
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t vhi = 0x0;
        uint64_t vlo = 0x1;
        uint64_t carry = 0;
        op::add128(hi, lo, vhi, vlo, carry);
        assert(hi == 0 and lo == 0 and carry == 1);
    }
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t vhi = 0xFFFFFFFFFFFFFFFF;
        uint64_t vlo = 0xFFFFFFFFFFFFFFFF;
        uint64_t carry = 1;
        op::add128(hi, lo, vhi, vlo, carry);
        assert(hi == 0xFFFFFFFFFFFFFFFF and lo == 0xFFFFFFFFFFFFFFFF and carry == 1);
    }
    std::cout << "op::test_add128() passed." << std::endl;
}
void test_mul64() {
    {
        uint64_t dst = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 0xFFFFFFFFFFFFFFFF;
        uint64_t spill = op::mul64(dst, value);
        assert(dst == 1 and spill == 0xfffffffffffffffe);
    }
    std::cout << "op::test_mul64() passed." << std::endl;
}
void test_mul12864() {
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 0xF;
        uint64_t spill = op::mul12864(hi, lo, value);
        assert(spill == 0xE and hi == 0xFFFFFFFFFFFFFFFF and lo == 0xFFFFFFFFFFFFFFF1);
    }
    {
        uint64_t hi = 0xFFFFFFFFFFFFFFFF;
        uint64_t lo = 0xFFFFFFFFFFFFFFFF;
        uint64_t value = 0xFFFFFFFFFFFFFFFF;
        uint64_t spill = op::mul12864(hi, lo, value);
        assert(spill == 0xFFFFFFFFFFFFFFFE and hi == 0xFFFFFFFFFFFFFFFF and lo == 0x1);
    }
    std::cout << "op::test_mul12864() passed." << std::endl;
}
}  // namespace test_op

namespace test_uint128 {
void test_constructor() {
    {
        std::string expect = "0x11111111222222223333333344444444";
        std::string output = uint128_t(expect).toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0x4";
        std::string output = uint128_t(0x04).toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0xF";
        std::string output = uint128_t("0x0F").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0x111ABCDEF0123456789";
        std::string output = uint128_t("0x00111ABCDEF0123456789").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0x0";
        std::string output = uint128_t("0x000000000000000000000").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0x0";
        std::string output = uint128_t("-0").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE";
        std::string output = uint128_t("-2").toString();
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    std::cout << "uint128::test_constructor() passed." << std::endl;
}

void test_bitwise_ops() {
    auto assertEx = [](size_t idx, bool logic) {
        if (not logic) {
            std::cout << "Check failed: " << idx << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    assertEx(1, uint128_t("0x1") < uint128_t("0x2"));
    assertEx(2, not(uint128_t("0x1") > uint128_t("0x2")));
    assertEx(3, uint128_t("0x1") <= uint128_t("0x2"));
    assertEx(4, not(uint128_t("0x1") >= uint128_t("0x2")));
    assertEx(5, uint128_t("0x1") <= uint128_t("0x1"));
    assertEx(6, uint128_t("0x0") <= uint128_t("0x0"));
    assertEx(7, uint128_t("0x1") >= uint128_t("0x0"));
    assertEx(8, uint128_t("0x01") == 1);
    assertEx(9, uint128_t(20000000) == 20000000);
    std::cout << "uint128::test_bitwise_ops() passed." << std::endl;
}

void test_add_and_sub() {
    auto checkEqual = [](const uint128_t &output, const uint128_t &expect) {
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    {
        uint128_t a = 110;
        a += 1;
        checkEqual(a, 111);
    }
    {
        uint128_t a = 0xFFFFFFFFFFFFFFFF;
        a += 1;
        checkEqual(a, uint128_t("0x1_00000000_00000000"));
    }
    {
        uint128_t a = 0x0;
        a -= 1;
        checkEqual(a, uint128_t("0xFFFFFFFF_FFFFFFFF_FFFFFFFF_FFFFFFFF"));
    }
    {
        uint128_t a = 0x12345;
        a -= 0;
        checkEqual(a, uint128_t(0x12345));
    }
    {
        uint128_t a = 0;
        while (a < 100) {
            a += 1;
        }
        checkEqual(a, 100);
    }
    {
        uint128_t a = 0xFFFFFFFFFFFFFFFF;
        a += 1;
        checkEqual(a, uint128_t("0x1_00000000_00000000"));
        a -= 1;
        a += 1;
        checkEqual(a, uint128_t("0x1_00000000_00000000"));
    }
    {
        uint128_t a = 10;
        for (size_t i = 0; i < 100; i += 1) {
            a -= 1;
        }
        for (size_t i = 0; i < 99; i += 1) {
            a += 1;
        }
        checkEqual(a, 9);
    }
    {
        uint128_t a = 0x1;
        while (a < uint128_t("0x99_00000000_00000000")) {
            a += uint128_t(1, 1);
        }
        checkEqual(a, uint128_t("0x99_00000000_0000009A"));
    }
    std::cout << "uint128::test_add_and_sub() passed." << std::endl;
}

void test_mul_and_div() {
    auto checkEqual = [](const uint128_t &output, const uint128_t &expect) {
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    {
        uint128_t a = 0x9;
        a *= 0xFFFFFFFF;
        checkEqual(a, uint128_t("0x8fffffff7"));
    }
    {
        uint128_t a(1, 2);
        a *= 2;
        checkEqual(a, uint128_t(2, 4));
    }
    {
        uint128_t a("0x1_FFFFFFFFFFFFFFFF");
        a *= 2;
        checkEqual(a, uint128_t("0x3fffffffffffffffe"));
    }
    {
        uint128_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint128_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        a *= b;
        checkEqual(a, 1);
    }
    {
        uint128_t a("0x123456789012345678901234567890FF");
        uint128_t b("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        a *= b;
        checkEqual(a, uint128_t("0xEDCBA9876FEDCBA9876FEDCBA9876F01"));
    }
    {
        uint128_t a("0x123456789012345678901234567890FF");
        uint128_t b("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        uint128_t c = a.mul128(b);
        checkEqual(a, uint128_t("0xEDCBA9876FEDCBA9876FEDCBA9876F01"));
        checkEqual(c, uint128_t("0x123456789012345678901234567890fe"));
    }
    std::cout << "uint128::test_mul_and_div() passed." << std::endl;
}

void test_performance() {
    {
        auto before = std::chrono::system_clock::now();
        for (uint64_t i = 0; i < 0xFFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint64_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint128_t i = 0; i < 0xFFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint128_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint64_t i = 0xFFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint64_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint128_t i = 0xFFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint128_t: " << diff.count() << std::endl;
    }
    std::cout << "uint128::test_performance() passed." << std::endl;
}
}  // namespace test_uint128

namespace test_uint256 {
void test_constructor() {
    {
        std::string expect = "0x1";
        std::string output = uint256_t("1").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect =
            "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
            "E";
        std::string output = uint256_t("-2").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    {
        std::string expect = "0x0";
        std::string output = uint256_t("-0x0").toString();
        output = std::regex_replace(output, std::regex("_"), "");
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("check failed");
        }
    }
    std::cout << "uint256::test_constructor() passed." << std::endl;
}

void test_bitwise_ops() {
    auto assertEx = [](size_t idx, bool logic) {
        if (not logic) {
            std::cout << "Check failed: " << idx << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    assertEx(1, uint128_t("0x1") < uint256_t("0x2"));
    assertEx(2, not(uint256_t("0x1") > uint256_t("0x2")));
    assertEx(3, uint256_t("0x1") <= uint256_t("0x2"));
    assertEx(4, not(uint256_t("0x1") >= uint256_t("0x2")));
    assertEx(5, uint256_t("0x1") <= uint256_t("0x1"));
    assertEx(6, uint256_t("0x0") <= uint256_t("0x0"));
    assertEx(7, uint256_t("0x1") >= uint128_t("0x0"));
    assertEx(7, uint256_t("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF") >=
                    uint256_t("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFE"));
    assertEx(8, uint256_t("0x01") == 1);
    assertEx(9, uint256_t(20000000) == 20000000);
    std::cout << "uint256::test_bitwise_ops() passed." << std::endl;
}

void test_add_and_sub() {
    auto checkEqual = [](const uint256_t &output, const uint256_t &expect) {
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    {
        uint256_t a = 110;
        a += 1;
        assert(a == 111);
    }
    {
        uint256_t a = 0xFFFFFFFFFFFFFFFF;
        a += 1;
        checkEqual(a, uint256_t("0x1_00000000_00000000"));
    }
    {
        uint256_t a = 0x0;
        a -= 1;
        checkEqual(a, uint256_t("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                                "FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF"));
    }
    {
        uint256_t a = 0x12345;
        a -= 0;
        checkEqual(a, uint256_t(0x12345));
    }
    {
        uint256_t a = 0;
        while (a < 100) {
            a += 1;
        }
        checkEqual(a, 100);
    }
    {
        uint256_t a = uint256_t(
            "0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
            "FFFFFFFFFFFFFFFF");
        a += 1;
        checkEqual(a, 0);
        a -= 1;
        a += 1;
        checkEqual(a, 0);
    }
    {
        uint256_t a = 10;
        for (size_t i = 0; i < 100; i += 1) {
            a -= 1;
        }
        for (size_t i = 0; i < 99; i += 1) {
            a += 1;
        }
        checkEqual(a, 9);
    }
    {
        uint256_t a = uint256_t(
            "0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
            "FFFFFFFFFFFFFFFF");
        uint256_t b = uint256_t(
            "0x0FFFFFFFFFFFFFFF_F0FFFFFFFFFFFFFF_FF0FFFFFFFFFFFFF_"
            "FFF0FFFFFFFFFFFF");
        uint256_t c = uint256_t(
            "0xF000000000000000_0F00000000000000_00F0000000000000_"
            "000F000000000000");
        checkEqual(a - b, c);
    }
    std::cout << "uint256::test_add_and_sub() passed." << std::endl;
}

void test_mul_and_div() {
    auto checkEqual = [](const uint256_t &output, const uint256_t &expect) {
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    {
        uint256_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint128_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint128_t c = a.mul128(b);
        checkEqual(c, uint128_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE"));
        checkEqual(a, uint256_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000000000000000000000000001"));
    }
    {
        uint256_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint128_t b("0xFFFFFFFFFFFFF6FFFFF1FFFFFFABCDEF");
        uint128_t c = a.mul128(b);
        checkEqual(c, uint128_t("0xfffffffffffff6fffff1ffffffabcdee"));
        checkEqual(a, uint256_t("0xffffffffffffffffffffffffffffffff0000000000000900000e000000543211"));
    }
    {
        uint256_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint256_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint256_t c = a.mul256(b);
        checkEqual(c, uint256_t("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe"));
        checkEqual(a, 1);
    }
    {
        uint256_t a("0xffffffffffffffffffffffffffffffff0000000000000900000e000000543211");
        uint256_t b("0xfffffffffffabcdefffffffffeffffff0000000000000900000e000000543211");
        uint256_t c = a.mul256(b);
        checkEqual(c, uint256_t("0xfffffffffffabcdefffffffffefffffe0000000000055521001bffffd24c3ad9"));
        checkEqual(a, uint256_t("0x5431fe3bf1b5f8ceffe3abcdeea89bdefc0000c9eb853b3579dc1bb0e4f2a521"));
    }
    std::cout << "uint256::test_mul_and_div() passed." << std::endl;
}

void test_performance() {
    {
        auto before = std::chrono::system_clock::now();
        for (uint64_t i = 0; i < 0xFFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint64_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint128_t i = 0; i < 0xFFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint128_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint256_t i = 0; i < 0xFFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint256_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint64_t i = 0xFFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint64_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint128_t i = 0xFFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint128_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint256_t i = 0xFFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint256_t: " << diff.count() << std::endl;
    }
    std::cout << "uint256::test_performance() passed." << std::endl;
}
}  // namespace test_uint256

namespace test_uint512 {
    void test_mul_and_div() {
    auto checkEqual = [](const uint512_t &output, const uint512_t &expect) {
        if (output != expect) {
            std::cout << "expect: " << expect << std::endl;
            std::cout << "output: " << output << std::endl;
            throw std::runtime_error("assert failed");
        }
    };
    {
        uint512_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint256_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
        uint256_t c = a.mul256(b);
        checkEqual(c, uint256_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE"));
        checkEqual(a, uint512_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000000000000000000000000000000000000001"));
    }
    std::cout << "uint512::test_mul_and_div() passed." << std::endl;
}

void test_performance() {
    {
        auto before = std::chrono::system_clock::now();
        for (uint64_t i = 0; i < 0xFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint64_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint128_t i = 0; i < 0xFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint128_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint256_t i = 0; i < 0xFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint256_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint512_t i = 0; i < 0xFFFFF; i += 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `+=` uint512_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint64_t i = 0xFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint64_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint128_t i = 0xFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint128_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint256_t i = 0xFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint256_t: " << diff.count() << std::endl;
    }
    {
        auto before = std::chrono::system_clock::now();
        for (uint512_t i = 0xFFFFF; i > 0; i -= 1) {
            ;
        }
        auto after = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = after - before;
        std::cout << "time `-=` uint512_t: " << diff.count() << std::endl;
    }
    std::cout << "uint512::test_performance() passed." << std::endl;
}
}

int main() {
    //
    test_op::test_add64();
    test_op::test_add12864();
    test_op::test_add128();
    test_op::test_mul64();
    test_op::test_mul12864();
    //
    test_uint128::test_constructor();
    test_uint128::test_bitwise_ops();
    test_uint128::test_add_and_sub();
    test_uint128::test_mul_and_div();
    //
    test_uint256::test_constructor();
    test_uint256::test_bitwise_ops();
    test_uint256::test_add_and_sub();
    test_uint256::test_mul_and_div();
    //
    test_uint512::test_mul_and_div();
    test_uint512::test_performance();
    return 0;
}
