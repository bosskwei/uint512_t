#ifndef UINT128_T_H
#define UINT128_T_H

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

class uint512_t {
  static const size_t SIZE_DATA = 8;
  const uint64_t MAX_UINT64 = 0xFFFFFFFFFFFFFFFF;
  const size_t BYTES_UINT64 = 64 / 8;
  const size_t BYTES_UINT512 = 512 / 8;
  const size_t HEXLEN_UINT64 = 64 / 4;
  const size_t HEXLEN_UINT512 = 512 / 4;

public:
  uint512_t() : data_{0, 0, 0, 0, 0, 0, 0, 0} {}
  uint512_t(const uint64_t &value) : data_{value, 0, 0, 0, 0, 0, 0, 0} {}
  explicit uint512_t(std::string value) : data_{0, 0, 0, 0, 0, 0, 0, 0} {
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

    // parse string to hex list
    std::vector<uint32_t> hexList;
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
    if (hexList.size() > HEXLEN_UINT512) {
      throw std::runtime_error("value too much");
    }

    while (hexList.size() < HEXLEN_UINT512) {
      hexList.push_back(0);
    }

    // fill data by hex list
    for (size_t i = 0, mul = 1; i < HEXLEN_UINT512; i += 1) {
      if (i % SIZE_DATA == 0) {
        mul = 1;
      } else {
        mul *= 256;
      }
      size_t id = i / BYTES_UINT64;
      this->data_[id] += mul * hexList[i];
    }

    // negative value as complement
    if (not isPositive) {
      for (size_t i = 0; i < SIZE_DATA; i += 1) {
        if (i) {
          this->data_[i] = MAX_UINT64 - this->data_[i];
        } else { // i ==0, lowest bits
          this->data_[i] = MAX_UINT64 - this->data_[i] + 1;
        }
      }
    }
  }

  std::string toString() const {
    std::string hex;

    // build form A_B_C
    for (size_t i = 0; i < SIZE_DATA; i+= 1) {
      hex = stringFormat("%016" PRIX64 "_", this->data_[i]) + hex;
    }
    hex = hex.substr(0, hex.size() - 1);

    // remove duplicate "0"
    size_t fnz = 0;
    for(size_t i = 0; i < hex.size(); i += 1) {
      if (hex[i] != '0' and hex[i] != '_') {
        fnz = i;
        break;
      }
    }
    hex = "0x" + hex.substr(fnz, hex.size() - fnz);
    return hex;
  }

  uint512_t &operator=(const uint512_t &other) {
    for (size_t i = 0; i < SIZE_DATA; i += 1) {
      this->data_[i] = other.data_[i];
    }
    return *this;
  }

  uint512_t &operator+=(const uint512_t &other) {
    asm("add %8, %0   \n\t"
        "adc %9, %1   \n\t"
        "adc %10, %2   \n\t"
        "adc %11, %3   \n\t"
        "adc %12, %4   \n\t"
        "adc %13, %5   \n\t"
        "adc %14, %6   \n\t"
        "adc %15, %7   \n\t"
        : "+r"(this->data_[0]), "+r"(this->data_[1]), "+r"(this->data_[2]), "+r"(this->data_[3]),
          "+r"(this->data_[4]), "+r"(this->data_[5]), "+r"(this->data_[6]), "+r"(this->data_[7])
        : "r"(other.data_[0]), "r"(other.data_[1]), "r"(other.data_[2]), "r"(other.data_[3]),
          "r"(other.data_[4]), "r"(other.data_[5]), "r"(other.data_[6]), "r"(other.data_[7])
        : "cc");
    return *this;
  }

  uint512_t &operator-=(const uint64_t &other) {
    // uint128_t complement(MAX_UINT64, MAX_UINT64 - value + 1);
    // return this->operator+(complement);
  }

  friend bool operator==(const uint512_t &left, const uint512_t &right) {
    for (size_t i = 0; i < SIZE_DATA; i += 1) {
      if (left.data_[i] != right.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator>(const uint512_t &left, const uint512_t &right) {
    for (size_t i = 0; i < SIZE_DATA; i += 1) {
      if (left.data_[i] < right.data_[i]) {
        return false;
      } else if (left.data_[i] != 0 and left.data_[i] == right.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator>=(const uint512_t &left, const uint512_t &right) {
    for (size_t i = 0; i < SIZE_DATA; i += 1) {
      if (left.data_[i] < right.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator<(const uint512_t &left, const uint512_t &right) {
    for (size_t i = 0; i < SIZE_DATA; i += 1) {
      if (left.data_[i] > right.data_[i]) {
        return false;
      } else if (left.data_[i] != 0 and left.data_[i] == right.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator<=(const uint512_t &left, const uint512_t &right) {
    for (size_t i = 0; i < SIZE_DATA; i += 1) {
      if (left.data_[i] > right.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const uint512_t &obj) {
    return os << obj.toString();
  }

private:
  // little-endian:
  // uint64_t(0x12345678) -> [0x78, 0x56, 0x34, 0x12]
  // uint512_t(0x2222222211111111) -> [data_[0] = 0x11111111l, data_[1] = 0x22222222]
  uint64_t data_[SIZE_DATA];
};

#endif
