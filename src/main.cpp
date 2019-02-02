#include "time.h"
#include <cmath>
#include <regex>
#include <string>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <uint512_t/uint512_t.hpp>


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
  std::cout << "test_constructor() passed." << std::endl;
}

void test_bitwise_ops() {
  auto assert = [](size_t idx, bool logic) {
    if (not logic) {
      std::cout << "Check failed: " << idx << std::endl;
      throw std::runtime_error("assert failed");
    }
  };
  assert(1, uint128_t("0x1") < uint128_t("0x2"));
  assert(2, not (uint128_t("0x1") > uint128_t("0x2")));
  assert(3, uint128_t("0x1") <= uint128_t("0x2"));
  assert(4, not (uint128_t("0x1") >= uint128_t("0x2")));
  assert(5, uint128_t("0x1") <= uint128_t("0x1"));
  assert(6, uint128_t("0x0") <= uint128_t("0x0"));
  assert(7, uint128_t("0x1") >= uint128_t("0x0"));
  assert(8, uint128_t("0x01") == 1);
  assert(9, uint128_t(20000000) == 20000000);
  std::cout << "test_bitwise_ops() passed." << std::endl;
}

void test_add_and_sub() {
  auto assert = [](bool logic) {
    if (not logic) {
      throw std::runtime_error("assert failed");
    }
  };
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
    assert(a == 111);
  }
  {
    uint128_t a = 0xFFFFFFFFFFFFFFFF;
    a += 1;
    checkEqual(a, uint128_t("0x100000000_00000000"));
  }
  {
    uint128_t a = 0x0;
    a -= 1;
    checkEqual(a, uint128_t("0xFFFFFFFF_FFFFFFFF_FFFFFFFF_FFFFFFFF"));
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
  std::cout << "test_add_and_sub() passed." << std::endl;
}

void test_performance() {
  {
    auto before = std::chrono::system_clock::now();
    for (uint64_t i = 0; i < 0xFFFFFF; i += 1) {
      ;
    }
    auto after = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = after - before;
    std::cout << "time inc uint64_t: " << diff.count() << std::endl;
  }
  {
    auto before = std::chrono::system_clock::now();
    for (uint128_t i = 0; i < 0xFFFFFF; i += 1) {
      ;
    }
    auto after = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = after - before;
    std::cout << "time inc uint128_t: " << diff.count() << std::endl;
  }
  std::cout << "test_performance() passed." << std::endl;
}
}


int main() {
  test_uint128::test_constructor();
  test_uint128::test_bitwise_ops();
  test_uint128::test_add_and_sub();
  test_uint128::test_performance();
  return 0;
}
