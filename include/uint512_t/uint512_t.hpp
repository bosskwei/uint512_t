#ifndef UINT512_T_H
#define UINT512_T_H

#include <array>
#include <regex>
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


template <typename T, typename Base>
class ext_base {
public:
  ext_base() = delete;
  explicit ext_base(Base hi, Base lo) : hi_(hi), lo_(lo) {}

  T &operator=(const T &other) {
    this->hi_ = other.hi_;
    this->lo_ = other.lo_;
    return *this;
  }

  friend bool operator==(const T &left, const T &right) {
    return left.hi_ == right.hi_ and left.lo_ == right.lo_;
  }

  friend bool operator!=(const T &left, const T &right) {
    return not (left == right);
  }

  friend bool operator>(const T &left, const T &right) {
    if (left.hi_ > right.hi_) {
      return true;
    } else if (left.hi_ < right.hi_) {
      return false;
    } else {
      return left.lo_ > right.lo_;
    }
  }

  friend bool operator>=(const T &left, const T &right) {
    return (left > right) or (left == right);
  }

  friend bool operator<(const T &left, const T &right) {
    if (left.hi_ > right.hi_) {
      return false;
    } else if (left.hi_ < right.hi_) {
      return true;
    } else {
      return left.lo_ < right.lo_;
    }
  }

  friend bool operator<=(const T &left, const T &right) {
    return (left < right) or (left == right);
  }

  friend std::ostream &operator<<(std::ostream &os, const T &object) {
    return os << object.toString();
  }

protected:
  Base hi_, lo_;
};


class uint128_t : public ext_base<uint128_t, uint64_t> {
  const size_t BYTES_UINT64 = 64 / 8;
  const size_t BYTES_UINT128 = 128 / 8;
  const uint64_t MAX_UINT64 = 0xFFFFFFFFFFFFFFFF;

public:
  uint128_t() : ext_base(0, 0) {}
  uint128_t(uint64_t value) : ext_base(0, value) {}
  uint128_t(uint64_t hi, uint64_t lo) : ext_base(hi, lo) {}
  explicit uint128_t(std::string value) : ext_base(0, 0) {
    bool isHex = false, isPositive = true;

    // 0xFFFF_FFFF
    value = std::regex_replace(value, std::regex("_"), "");

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

    // parse string to hex list like [1, 255, 200]
    std::vector<uint32_t> byteList;
    if (isHex) {
      std::reverse(value.begin(), value.end());

      // make aligned
      if (value.length() % 2 == 1) {
        value.push_back('0');
      }

      // [b'A', b'1', b'2'] to [10, 1, 2]
      for (size_t i = 0; i < value.length(); i += 2) {
        uint8_t ch_0 = value[i], ch_1 = value[i + 1];
        ch_0 = (ch_0 >= 'A') ? (10 + ch_0 - 'A') : (ch_0 - '0');
        ch_1 = (ch_1 >= 'A') ? (10 + ch_1 - 'A') : (ch_1 - '0');
        byteList.push_back(16 * ch_1 + ch_0);
      }
    } else {
      byteList.push_back(0);

      for (const auto &ch_x : value) {
        for (auto &hex_x : byteList) {
          hex_x *= 10;
        }

        uint8_t dec_x = ch_x - '0';
        byteList[0] += dec_x;

        for (size_t i = 0; i < byteList.size(); i += 1) {
          if (byteList[i] >= 256) {
            byteList.push_back(0);
            byteList[i + 1] += byteList[i] / 256;
            byteList[i] = byteList[i] % 256;
          }
        }
      }

      while (byteList[byteList.size() - 1] == 0) {
        byteList.pop_back();
      }
    }

    // byteList now contains reverse-ordered byte value
    if (byteList.size() > BYTES_UINT128) {
      throw std::runtime_error("value too much");
    }

    while (byteList.size() < BYTES_UINT128) {
      byteList.push_back(0);
    }

    // fill data by hex list
    for (size_t i = 0, mul = 1; i < BYTES_UINT128; i += 1) {
      if (i % BYTES_UINT64 == 0) {
        mul = 1;
      } else {
        mul *= 256;
      }
      size_t id = i / BYTES_UINT64;
      if (id == 0) {
        this->lo_ += mul * byteList[i];
      } else if (id == 1) {
        this->hi_ += mul * byteList[i];
      } else {
        throw std::runtime_error("should not come here");
      }
    }

    // negative value as complement
    if (not isPositive) {
      this->hi_ = MAX_UINT64 - this->hi_;
      this->lo_ = MAX_UINT64 - this->lo_ + 1;
    }
  }

  std::string toString() const {
    std::string hex;

    // build form A_B_C
    hex = stringFormat("%016" PRIX64 "%016" PRIX64 "", this->hi_, this->lo_);

    // remove duplicate "0"
    size_t fnz = 0;
    for(size_t i = 0; i < hex.size(); i += 1) {
      fnz = i;
      if (hex[i] != '0' and hex[i] != '_') {
        break;
      }
    }
    hex = "0x" + hex.substr(fnz, hex.size() - fnz);
    return hex;
  }

  uint128_t &operator+=(const uint128_t &other) {
    asm("add %2, %0   \n\t"
        "adc %3, %1   \n\t"
        : "+r"(this->lo_), "+r"(this->hi_)
        : "r"(other.lo_), "r"(other.hi_)
        : "cc");
    return *this;
  }

  uint128_t &operator-=(const uint128_t &other) {
    uint128_t complement(MAX_UINT64 - other.hi_, MAX_UINT64 - other.lo_ + 1);
    return this->operator+=(complement);
  }
};

class uint256_t : public ext_base<uint256_t, uint128_t> {
};

class uint512_t {
};

#endif
