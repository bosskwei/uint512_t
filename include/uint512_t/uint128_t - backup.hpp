#pragma once
#include <array>
#include <memory>
#include <vector>
#include <numeric>
#include <cstdint>
#include <iostream>
#include <cinttypes>
#include <algorithm>


namespace {
template <typename... Args>
std::string stringFormat(const std::string &format, Args... args) {
  size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) +
                1; // Extra space for '\0'
  std::unique_ptr<char[]> buf(new char[size]);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(),
                     buf.get() + size - 1); // We don't want the '\0' inside
}

std::vector<std::string> split(const std::string &s, const std::string &sep) {
  std::vector<std::string> output;
  std::string::size_type prev_pos = 0, pos = 0;

  if (s.length() == 0) {
    return output;
  }

  while ((pos = s.find(sep, pos)) != std::string::npos) {
    std::string substring(s.substr(prev_pos, pos - prev_pos));
    output.push_back(substring);
    pos += sep.length();
    prev_pos = pos;
  }
  output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

  return output;
}
} // namespace

class uint128_t {
  const uint64_t MAX_UINT64 = 0xFFFFFFFFFFFFFFFF;

public:
  uint128_t() : hi_(0), lo_(0), isPositive_(true) {}
  uint128_t(uint64_t value) : hi_(0), lo_(value), isPositive_(true) {}
  uint128_t(uint64_t hi, uint64_t lo) : hi_(hi), lo_(lo), isPositive_(true) {}
  uint128_t(std::string value) : hi_(0), lo_(0), isPositive_(true) {
    bool isHex = false, isPositive = true;

    // split 0x and flag
    std::vector<std::string> split0x = split(value, "0x");
    switch (split0x.size()) {
    case 1: {
      isHex = false;
      value = split0x[0];
      if (value[0] == '+' or value[0] == '-') {
        isPositive = (value[0] == '-') ? false : true;
        value = value.replace(value.begin(), value.begin() + 1, "");
      }
      break;
    }
    case 2: {
      isHex = true;
      isPositive = (split0x[0] == "-") ? false : true;
      value = split0x[1];
      break;
    }
    default: {
      throw std::runtime_error("value is empty");
    }
    }

    // std::cout << "isHex: " << isHex << std::endl;
    // std::cout << "isPositive: " << isPositive << std::endl;
    // std::cout << value << std::endl;

    // check
    std::for_each(value.begin(), value.end(), [=](uint8_t ch) {
      if (isHex) {
        if ((ch < '0' or ch > 'F') or (ch > '9' and ch < 'A')) {
          throw std::runtime_error("illegal value");
        }
      } else {
        if (ch < '0' or ch > '9') {
          throw std::runtime_error("illegal value");
        }
      }
    });

    // parse string to hex list
    std::vector<uint32_t> hexList;
    if (isHex) {
      std::reverse(value.begin(), value.end());

      if (value.length() % 2 == 1) {
        value.push_back('0');
      }

      for (size_t i = 0; i < value.length(); i += 2) {
        uint8_t ch_0 = value[i], ch_1 = value[i + 1];
        ch_0 = (ch_0 >= 'A') ? (10 + ch_0 - 'A') : (ch_0 - '0');
        ch_1 = (ch_1 >= 'A') ? (10 + ch_1 - 'A') : (ch_1 - '0');
        hexList.push_back(16 * ch_1 + ch_0);
      }
    } else {
      hexList.push_back(0);

      for (const auto &ch_x : value) {
        for (auto &hex_x : hexList) {
          hex_x *= 10;
        }

        uint8_t dec_x = ch_x - '0';
        hexList[0] += dec_x;

        for (size_t i = 0; i < hexList.size(); i += 1) {
          if (hexList[i] >= 256) {
            hexList.push_back(0);
            hexList[i + 1] += hexList[i] / 256;
            hexList[i] = hexList[i] % 256;
          }
        }
      }

      while (hexList[hexList.size() - 1] == 0) {
        hexList.pop_back();
      }
    }

    // hexList now contains reverse-ordered byte value
    if (hexList.size() > 16) {
      throw std::runtime_error("value too much");
    }

    while (hexList.size() < 16) {
      hexList.push_back(0);
    }

    for (size_t i = 0, mul = 1; i < 8; i += 1, mul *= 256) {
      this->lo_ += mul * hexList[i];
    }
    for (size_t i = 8, mul = 1; i < 16; i += 1, mul *= 256) {
      this->hi_ += mul * hexList[i];
    }

    // negative value as complement
    if (not isPositive) {
      this->hi_ = MAX_UINT64 - this->hi_;
      this->lo_ = MAX_UINT64 - this->lo_ + 1;
      this->isPositive_ = false;
    }
  }

  std::string toString() const {
    return stringFormat("0x%" PRIx64 "%016" PRIx64 "", this->hi_, this->lo_);
  }

  uint128_t operator+(const uint64_t &value) const {
    uint128_t newVal(value);
    return this->operator+(newVal);
  }

  uint128_t operator+(const uint128_t &other) const {
    uint128_t res(this->hi_, this->lo_);
    asm("add %2, %0   \n\t"
        "adc %3, %1   \n\t"
        : "+r"(res.lo_), "+r"(res.hi_)
        : "r"(other.lo_), "r"(other.hi_)
        : "cc");
    return res;
  }

  uint128_t operator-(const uint64_t &value) const {
    uint128_t complement(MAX_UINT64, MAX_UINT64 - value + 1);
    return this->operator+(complement);
  }

  uint128_t operator-(const uint128_t &other) const {
    uint128_t complement(MAX_UINT64 - other.hi_, MAX_UINT64 - other.lo_ + 1);
    return this->operator+(complement);
  }

  uint128_t operator*(const uint64_t &value) const {
    // RDX:RAX ← RAX ∗ r/m64
    // Init: rax(lo), rbx(hi)
    // Final: rax(), rbx()
    uint128_t res;
    uint64_t flag;
    asm("mul %4             \n\t"  // rdx:rax = this->lo_ * value
        "mov %%rax, %0      \n\t"  // res.lo_ = rax
        "mov %%rbx, %%rax   \n\t"  // rax = this->hi_
        "mov %%rdx, %%rbx   \n\t"  // rbx = carry_bit
        "mul %4             \n\t"  // rdx:rax = this->hi_ * value
        "add %%rbx, %%rax   \n\t"  // rax += carry_bit
        : "=m"(res.lo_), "=a"(res.hi_)
        : "a"(this->lo_), "b"(this->hi_), "r"(value));
    return res;
  }

  friend std::ostream &operator<<(std::ostream &os, const uint128_t &obj) {
    return os << std::hex << "high = 0x" << obj.hi_ << ", low = 0x" << obj.lo_;
  }

private:
  uint64_t hi_, lo_;
  bool isPositive_;
};
