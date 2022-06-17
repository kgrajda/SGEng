//===- Color.cpp --------------------------------------------------*- C++ -*-===//
//
// MIT License
//
// Copyright (c) [2022] [Krzysztof Grajda]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//===----------------------------------------------------------------------===//
#include "Color.h"

#include <sstream>

namespace SGEng {

using namespace std::string_literals;

Color &Color::setRGB(uint32_t rgb, uint8_t opacity) {
  *this = Color::fromRGB(rgb, opacity);
  return *this;
}

Color &Color::setRGB(uint32_t rgb, float opacity) {
  *this = Color::fromRGB(rgb, opacity);
  return *this;
}

std::string Color::getHashCode() const {
  std::stringstream ss('#');
  ss << std::hex;
  if (r <= _halfByte)
    ss << '0';
  ss << static_cast<unsigned int>(r);
  if (g <= _halfByte)
    ss << '0';
  ss << static_cast<unsigned int>(g);
  if (b <= _halfByte)
    ss << '0';
  ss << static_cast<unsigned int>(b);
  if (a == 0U)
    return ss.str();
  if (a <= _halfByte)
    ss << '0';
  ss << static_cast<unsigned int>(a);
  return ss.str();
}

Color::operator std::string() const { return getHashCode(); }

constexpr Color Color::fromRGB(uint32_t rgb, float opacity) {
  return Color::fromRGB(rgb, static_cast<uint8_t>(opacity * _maxByte));
}

constexpr Color Color::fromRGBA(uint8_t rgba) {
  return Color{(rgba & _rMaskRGBA) >> _offset3B,
               (rgba & _gMaskRGBA) >> _offset2B,
               (rgba & _bMaskRGBA) >> _offset1B, rgba & _aMaskRGBA};
}

Color Color::parse(std::string_view hashColorCode) {
  constexpr size_t lengthOfRRGGBB = 6;
  constexpr size_t lengthOfHRRGGBB = 7;
  constexpr size_t lengthOfRRGGBBAA = 8;
  constexpr size_t lengthOfHRRGGBBAA = 9;

  if (hashColorCode.size() < lengthOfRRGGBB ||
      (hashColorCode[0] == '#' && hashColorCode.size() == lengthOfRRGGBB) ||
      (hashColorCode[0] == '#' && hashColorCode.size() == lengthOfRRGGBBAA) ||
      (hashColorCode[0] != '#' && hashColorCode.size() == lengthOfHRRGGBB) ||
      (hashColorCode[0] != '#' && hashColorCode.size() == lengthOfHRRGGBBAA) ||
      hashColorCode.size() > lengthOfHRRGGBBAA) {
    throw ColorParseError{"Invalid color hash code",
                          std::string{hashColorCode}};
  }

  int startIndex = 0;
  if (hashColorCode[0] == '#')
    startIndex = 1;

  Color color;
  constexpr size_t firstPlaceOffset = 0;
  constexpr size_t secondPlaceOffset = 2;
  constexpr size_t thirdPlaceOffset = 4;
  constexpr size_t fourthPlaceOffset = 6;

  {
    std::stringstream ss;
    unsigned int hex{0};
    ss << hashColorCode.substr(startIndex + firstPlaceOffset, 2);
    ss >> std::hex >> hex;
    color.r = hex;
  }
  {
    std::stringstream ss;
    unsigned int hex{0};
    ss << hashColorCode.substr(startIndex + secondPlaceOffset, 2);
    ss >> std::hex >> hex;
    color.g = hex;
  }
  {
    std::stringstream ss;
    unsigned int hex{0};
    ss << hashColorCode.substr(startIndex + thirdPlaceOffset, 2);
    ss >> std::hex >> hex;
    color.b = hex;
  }

  if (hashColorCode.size() >= lengthOfRRGGBBAA) {
    std::stringstream ss;
    unsigned int hex{0};
    ss << std::hex << hashColorCode.substr(startIndex + fourthPlaceOffset, 2);
    ss >> hex;
    color.a = hex;
  } else {
    color.a = _maxByte;
  }

  return color;
}

ColorParseError::ColorParseError(std::string &&msg, std::string &&colorHashCode)
    : _msg{msg}, colorHashCode{colorHashCode} {}

const char *ColorParseError::what() const noexcept { return _msg.data(); }

std::string ColorParseError::getColorHashCode() const { return colorHashCode; }

} // namespace SGEng
