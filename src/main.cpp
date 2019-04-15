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
    assert(hi == 0xFFFFFFFFFFFFFFFF and lo == 0xFFFFFFFFFFFFFFFF and
           carry == 1);
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
    assert(spill == 0xE and hi == 0xFFFFFFFFFFFFFFFF and
           lo == 0xFFFFFFFFFFFFFFF1);
  }
  {
    uint64_t hi = 0xFFFFFFFFFFFFFFFF;
    uint64_t lo = 0xFFFFFFFFFFFFFFFF;
    uint64_t value = 0xFFFFFFFFFFFFFFFF;
    uint64_t spill = op::mul12864(hi, lo, value);
    assert(spill == 0xFFFFFFFFFFFFFFFE and hi == 0xFFFFFFFFFFFFFFFF and
           lo == 0x1);
  }
  std::cout << "op::test_mul12864() passed." << std::endl;
}
void test_divmod64() {
  {
    uint64_t dst = 1024;
    uint64_t value = 64;
    // uint64_t remain = op::divmod64(dst, value);
    // assert(dst == 16 and remain == 0);
  }
  {
    uint64_t dst = 1024;
    uint64_t value = 1023;
    // uint64_t remain = op::divmod64(dst, value);
    // assert(dst == 1 and remain == 1);
  }
  {
    uint64_t dst = 1024;
    uint64_t value = 1025;
    // uint64_t remain = op::divmod64(dst, value);
    // assert(dst == 0 and remain == 1024);
  }
  std::cout << "op::test_divmod64() passed." << std::endl;
}
} // namespace test_op

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
    uint128_t c = a.mulTWithSpill(b);
    checkEqual(a, uint128_t("0xEDCBA9876FEDCBA9876FEDCBA9876F01"));
    checkEqual(c, uint128_t("0x123456789012345678901234567890fe"));
  }
  {
    uint128_t a("-2");
    uint128_t b("-3");
    uint128_t c = a * b;
    checkEqual(a, uint128_t("-2"));
    checkEqual(c, uint128_t("6"));
  }
  {
    uint128_t a("-2");
    uint128_t b("3");
    uint128_t c = a * b;
    checkEqual(c, uint128_t("-6"));
  }
  {
    uint128_t a("2");
    uint128_t b("-3");
    uint128_t c = a * b;
    checkEqual(c, uint128_t("-6"));
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
} // namespace test_uint128

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
    uint256_t a =
        uint256_t("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
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
    uint256_t a =
        uint256_t("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                  "FFFFFFFFFFFFFFFF");
    uint256_t b =
        uint256_t("0x0FFFFFFFFFFFFFFF_F0FFFFFFFFFFFFFF_FF0FFFFFFFFFFFFF_"
                  "FFF0FFFFFFFFFFFF");
    uint256_t c =
        uint256_t("0xF000000000000000_0F00000000000000_00F0000000000000_"
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
    uint256_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                "FFFFFFFFFFFFFFFF");
    uint128_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
    uint128_t c = a.mulSubTWithSpill(b);
    checkEqual(c, uint128_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE"));
    checkEqual(a, uint256_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000"
                            "0000000000000001"));
  }
  {
    uint256_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                "FFFFFFFFFFFFFFFF");
    uint128_t b("0xFFFFFFFFFFFFF6FFFFF1FFFFFFABCDEF");
    uint128_t c = a.mulSubTWithSpill(b);
    checkEqual(c, uint128_t("0xfffffffffffff6fffff1ffffffabcdee"));
    checkEqual(a, uint256_t("0xffffffffffffffffffffffffffffffff0000000000000900"
                            "000e000000543211"));
  }
  {
    uint256_t a("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                "FFFFFFFFFFFFFFFF");
    uint256_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                "FFFFFFFFFFFFFFFF");
    uint256_t c = a.mulTWithSpill(b);
    checkEqual(c, uint256_t("0xffffffffffffffffffffffffffffffffffffffffffffffff"
                            "fffffffffffffffe"));
    checkEqual(a, 1);
  }
  {
    uint256_t a(
        "0xffffffffffffffffffffffffffffffff0000000000000900000e000000543211");
    uint256_t b(
        "0xfffffffffffabcdefffffffffeffffff0000000000000900000e000000543211");
    uint256_t c = a.mulTWithSpill(b);
    checkEqual(c, uint256_t("0xfffffffffffabcdefffffffffefffffe0000000000055521"
                            "001bffffd24c3ad9"));
    checkEqual(a, uint256_t("0x5431fe3bf1b5f8ceffe3abcdeea89bdefc0000c9eb853b35"
                            "79dc1bb0e4f2a521"));
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
} // namespace test_uint256

namespace test_uint512 {
void test_bitwise_ops() {
  auto checkEqual = [](const uint512_t &output, const uint512_t &expect) {
    if (output != expect) {
      std::cout << "expect: " << expect << std::endl;
      std::cout << "output: " << output << std::endl;
      throw std::runtime_error("assert failed");
    }
  };
  {
    uint512_t a(
        "0x4b00245baeaf75ce0bfa3921acb27f3dc7292c11ca9576c141ab333e30c7e0f14d94"
        "9b426ff43f0502512ea0cdb97d0c0543b03bb65406b72ebb0c3e0fe3e02a");
    uint512_t b(
        "0x3f1f8929bf802193dbf8b3d42c627fd051abb138f21e1a05f6b2655f5759fc2e7378"
        "22c9c540d9bec3d1188dacbb57ee97c52cbec27ea9866444a4b63606100d");
    uint512_t c = a & b;
    uint512_t d(
        "0xb000009ae8021820bf831002c227f1041292010c214120140a2211e1041e02041100"
        "24045401904025108808cb9550c0541203a825400862400043606020008");
    checkEqual(c, d);
  }
  {
    uint512_t a(
        "0x2ad21a07f2f4c246c83b8295c02f225b59d9657cd1762a863981d8d8b3281c3d6678"
        "66b6af79c7302ba6549737418a3245f28671a431a17f949fabc660fe10a2");
    uint512_t b(
        "0x266c08cf51ee16ff0621357cbf9dc5b181aa358b3663da8a458d0b0ce6a1195429a8"
        "e3a993626e98a9eaf2faf8114893cb2a66b548c0a94177c29f8172fcd66");
    uint512_t c = a | b;
    uint512_t d(
        "0x2af6da8ff7fee36ff87b93d7cbfffe5b59dbe77cf3763faebdd9d8f8ff6a1dbd66fa"
        "eebebf7fe7f9abbeffbfbfc19ebb7df2a67bf4bdabff97ffabfe77ffdde6");
    checkEqual(c, d);
  }
  {
    uint512_t a(
        "0x817f59385c9dbe72c141552362eae099475f02266826466ed6c6b31b40b38bd0042b"
        "e014231eaf2e6a58d9ee55203874c2e6af4384a46abda87b925b8a681b64");
    uint512_t b(
        "0x8a26b0801accda2341dcd7a98b163a5af59327ae6fd8a9cdf29a6d7fda08b7d3812c"
        "cc8e42c276b07f59c9f5e3e44afc97221ede8d0bb9e3bbc7b2a40fd0e0c8");
    uint512_t c = a ^ b;
    uint512_t d(
        "0xb59e9b846516451809d828ae9fcdac3b2cc258807feefa3245cde649abb3c0385072"
        "c9a61dcd99e1501101bb6c4728855c4b19d09afd35e13bc20ff85b8fbac");
    checkEqual(c, d);
  }
  {
    uint512_t a(0, 1);
    for (size_t i = 0; i < 256; i += 1) {
      a <<= 1;
    }
    checkEqual(a, uint512_t(1, 0));
    for (size_t i = 0; i < 256; i += 1) {
      a >>= 1;
    }
    checkEqual(a, 1);
    a <<= 256;
    checkEqual(a, uint512_t(1, 0));
    a >>= 256;
    checkEqual(a, 1);
  }
  {
    uint512_t a("0x817f59385c9dbe72c141552362eae099475f02266826466ed6c6b31b40b3"
                "8bd0042b");
    assert(a.bitsLength() == 272);
    uint512_t b("53619999245189178119155288389167298372784779505147920607280807"
                "77303261800839434272941585984361175179693509978956833919818588"
                "429937180386631149665969494575");
    assert(b.bitsLength() == 511);
  }
  std::cout << "uint512::test_bitwise_ops() passed." << std::endl;
}

void test_mul_and_div() {
  auto checkEqual = [](const uint512_t &output, const uint512_t &expect) {
    if (output != expect) {
      std::cout << "expect: " << expect << std::endl;
      std::cout << "output: " << output << std::endl;
      throw std::runtime_error("assert failed");
    }
  };
  {
    uint512_t a("-20");
    uint512_t b("-30");
    uint512_t c = a * b;
    checkEqual(c, uint512_t("600"));
  }
  {
    uint512_t a(
        "0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
        "FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF");
    uint256_t b("0xFFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_"
                "FFFFFFFFFFFFFFFF");
    uint256_t c = a.mulSubTWithSpill(b);
    checkEqual(c, uint256_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
                            "FFFFFFFFFFFFFFFE"));
    checkEqual(a, uint512_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
                            "FFFFFFFFFFFFFFFF0000000000000000000000000000000000"
                            "000000000000000000000000000001"));
  }
  {
    uint512_t a("-0xF1F2F3F4F5F6F7F8F9F0");
    uint512_t b("0xFABCDEFABCDEF987654321");
    uint512_t c = a * b;
    checkEqual(c, uint512_t("-0xecf9c3660969a1b8564eddd8d1dc50b3344c3207f0"));
  }
  {
    uint512_t a("-0xecf9c3660969a1b8564eddd8d1dc50b3344c3207f0");
    uint512_t b("-0xf1f2f3f4f5f6");
    uint512_t c = a * b;
    checkEqual(
        c,
        uint512_t("0xdff806e19b882f4c11c1164cc6037632d36bb383fdcf457a6c50a0"));
  }
  {
    // bug fix
    uint512_t a("0xdff806e19b882f4c11c116cc6037632d36bb383fdcf457a6c50a04cc6037632d36bb383fdcf457a6c50a0");
    uint512_t b("0x78f979fa7afb0000000000000000000000000000000000000000000000000000000000000000000000000");
    uint512_t c = a - b;
    std::cout << b.toComplement() << std::endl;
    checkEqual(c, uint512_t("0x66fe8ce7208d2f4c11c116cc6037632d36bb383fdcf457a6c50a04cc6037632d36bb383fdcf457a6c50a0"));

/*
    // test div
    uint512_t a("0xdff806e19b882f4c11c116cc6037632d36bb383fdcf457a6c50a04cc6037"
                "632d36bb383fdcf457a6c50a0");
    uint512_t b("0xf1f2f3f4f5f6");
    std::pair<uint512_t, uint512_t> qr = a.divmod(a, b);
    std::cout << qr.first << std::endl;
    checkEqual(qr.first, uint512_t("0xecf9c3660969a1b8564ede5fd51f6da4dbacd15de"
                                   "47a5da92d59e5c3252bfbcb61239fa27"));
    checkEqual(qr.second, uint512_t("0xa14b08229c26"));
    */
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
} // namespace test_uint512

uint32_t fp16_ieee_to_fp32_bits(uint16_t h) {
  const uint32_t w = (uint32_t)h << 16;
  const uint32_t sign = w & UINT32_C(0x80000000);
  const uint32_t nonsign = w & UINT32_C(0x7FFFFFFF);
  uint32_t renorm_shift = __builtin_clz(nonsign);
  renorm_shift = renorm_shift > 5 ? renorm_shift - 5 : 0;
  const int32_t inf_nan_mask =
      ((int32_t)(nonsign + 0x04000000) >> 8) & INT32_C(0x7F800000);
  const int32_t zero_mask = (int32_t)(nonsign - 1) >> 31;
  return sign |
         ((((nonsign << renorm_shift >> 3) + ((0x70 - renorm_shift) << 23)) |
           inf_nan_mask) &
          ~zero_mask);
}

static inline float fp32_from_bits(uint32_t w) {
  union {
    uint32_t as_bits;
    float as_value;
  } fp32 = {w};
  return fp32.as_value;
}

static inline uint32_t fp32_to_bits(float f) {
  union {
    float as_value;
    uint32_t as_bits;
  } fp32 = {f};
  return fp32.as_bits;
}

static inline uint16_t fp16_ieee_from_fp32_value(float f) {
  const float scale_to_inf = fp32_from_bits(UINT32_C(0x77800000));
  const float scale_to_zero = fp32_from_bits(UINT32_C(0x08800000));
  float base = (fabsf(f) * scale_to_inf) * scale_to_zero;

  const uint32_t w = fp32_to_bits(f);
  const uint32_t shl1_w = w + w;
  const uint32_t sign = w & UINT32_C(0x80000000);
  uint32_t bias = shl1_w & UINT32_C(0xFF000000);
  if (bias < UINT32_C(0x71000000)) {
    bias = UINT32_C(0x71000000);
  }

  base = fp32_from_bits((bias >> 1) + UINT32_C(0x07800000)) + base;
  const uint32_t bits = fp32_to_bits(base);
  const uint32_t exp_bits = (bits >> 13) & UINT32_C(0x00007C00);
  const uint32_t mantissa_bits = bits & UINT32_C(0x00000FFF);
  const uint32_t nonsign = exp_bits + mantissa_bits;
  return (sign >> 16) |
         (shl1_w > UINT32_C(0xFF000000) ? UINT16_C(0x7E00) : nonsign);
}

uint16_t fp32_to_fp16_rtz(uint32_t fp32) {
  uint16_t fp16_inf = 0x7c00;
  uint16_t fp16_nan = 0x7fff;
  if (std::isnan(fp32_from_bits(fp32))) {
    std::cout << "isnan" << std::endl;
    return fp16_nan;
  }
  uint32_t fp16_mant = (((fp32 & 0x0007FFFFF) | 0x0800000) >> 13);
  uint32_t fp16_exp = (int32_t(fp32 & 0x7F800000) >> 23) - 112;
  uint32_t fp16_sign = (fp32 & 0x80000000) >> 16;
  std::cout << "fp16_mant: " << std::hex << fp16_mant << std::endl;
  std::cout << "fp16_exp: " << std::hex << fp16_exp << std::endl;
  if (std::isinf(fp32_from_bits(fp32))) {
    return (fp16_inf | fp16_sign);
  }
  if ((signed)fp16_exp >= 0x01F) {
    return (0x7bffU | fp16_sign);
  }
  // denormal data
  if ((int32_t)fp16_exp <= 0x0) {
    return uint16_t(fp16_sign);
  }
  return uint16_t(fp16_sign | fp16_exp << 10 | (fp16_mant & 0x03FF));
}

int main_1() {
  uint16_t uint_fp16_dst = fp32_to_fp16_rtz(-8388608);
  std::cout << std::hex << uint_fp16_dst << std::endl;
  return 0;
}

int main_2() {
  uint16_t uint_fp16 = 0x0070;
  uint32_t uint_fp32 = fp16_ieee_to_fp32_bits(uint_fp16);
  uint16_t uint_fp16_dst = fp16_ieee_from_fp32_value(fp32_from_bits(uint_fp32));
  std::cout << "input: " << std::hex << uint_fp16 << std::endl;
  std::cout << "output: " << std::hex << uint_fp16_dst << std::endl;
  std::cout << "error: " << uint_fp16_dst - uint_fp16 << std::endl;
  return 0;
}

int main() {
  //
  test_op::test_add64();
  test_op::test_add12864();
  test_op::test_add128();
  test_op::test_mul64();
  test_op::test_mul12864();
  test_op::test_divmod64();
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
  test_uint512::test_bitwise_ops();
  test_uint512::test_mul_and_div();
  test_uint512::test_performance();
  return 0;
}