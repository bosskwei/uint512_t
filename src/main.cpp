#include "time.h"
#include <cmath>
#include <regex>
#include <string>
#include <cstring>
#include <algorithm>
#include <uint512_t/uint512_t.hpp>


/*
void test_constructor() {
  {
    std::string expect = "0x11111111222222223333333344444444";
    std::string output = uint512_t(expect).toString();
    output = std::regex_replace(output, std::regex("_"), "");
    if (output != expect) {
      std::cout << "expect: " << expect << std::endl;
      std::cout << "output: " << output << std::endl;
      throw std::runtime_error("check failed");
    }
  }
  {
    std::string expect = "0x4";
    std::string output = uint512_t(0x04).toString();
    output = std::regex_replace(output, std::regex("_"), "");
    if (output != expect) {
      std::cout << "expect: " << expect << std::endl;
      std::cout << "output: " << output << std::endl;
      throw std::runtime_error("check failed");
    }
  }
  {
    std::string expect = "0xF";
    std::string output = uint512_t("0x0F").toString();
    output = std::regex_replace(output, std::regex("_"), "");
    if (output != expect) {
      std::cout << "expect: " << expect << std::endl;
      std::cout << "output: " << output << std::endl;
      throw std::runtime_error("check failed");
    }
  }
  {
    std::string expect = "0x111ABCDEF0123456789";
    std::string output = uint512_t("0x00111ABCDEF0123456789").toString();
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
  auto assert = [](bool logic) {
    if (not logic) {
      throw std::runtime_error("assert failed");
    }
  };
  assert(uint512_t("0x1") < uint512_t("0x2"));
  assert(not (uint512_t("0x1") > uint512_t("0x2")));
  assert(uint512_t("0x1") <= uint512_t("0x2"));
  assert(not (uint512_t("0x1") >= uint512_t("0x2")));
  assert(uint512_t("0x1") <= uint512_t("0x1"));
  assert(uint512_t("0x0") <= uint512_t("0x0"));
  assert(uint512_t("0x1") >= uint512_t("0x0"));
  assert(uint512_t("0x01") == 1);
  assert(uint512_t(20000000) == 20000000);
  std::cout << "test_bitwise_ops() passed." << std::endl;
}

void test_add_and_sub() {
  auto assert = [](bool logic) {
    if (not logic) {
      throw std::runtime_error("assert failed");
    }
  };
  {
    uint512_t a = 110;
    a += 1;
    assert(a == 111);
  }
  {
    uint512_t a = 0xFFFFFFFFFFFFFFFF;
    a += 1;
    assert(a == uint512_t("0x100000000_00000000"));
  }
  std::cout << "test_add_and_sub() passed." << std::endl;
}
*/

int main() {
  test_constructor();
  test_bitwise_ops();
  test_add_and_sub();
  return 0;
}
