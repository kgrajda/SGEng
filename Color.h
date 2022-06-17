//===- Color.h --------------------------------------------------*- C++ -*-===//
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
#pragma once

#include <algorithm>
#include <exception>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string_view>
#include <utility>

namespace SGEng {

class ColorParseError : public std::exception {
public:
  ColorParseError(std::string &&msg, std::string &&colorHashCode);

  const char *what() const noexcept override;
  std::string getColorHashCode() const;

private:
  std::string _msg;
  std::string colorHashCode;
};

struct Color : public glm::u8vec4 {

  enum class BasicColor : uint32_t {
    Transparent = 0x00000000,
    White = 0xffffff,
    Black = 0x000000,
    Red = 0xff0000,
    Green = 0x00ff00,
    Blue = 0x0000ff,
    Gray = 0x7f7f7f,
    Yellow = 0xffff00,
    Magenta = 0xff00ff,
    Cyan = 0x00ffff,
    Orange = 0xffa500,
    Violet = 0x9400d3,
    Indigo = 0x4b0082,
    Pink = 0xee82ee,
  };

  enum class MaterialWhite : uint32_t {
    Primary = 0x6200ee,
    PrimaryVariant = 0x3700b3,
    Secondary = 0x03dac6,
    SecondaryVariant = 0x018786,
    Background = 0xffffff,
    Surface = 0xffffff,
    Error = 0xb00020,
    OnPrimary = 0xffffff,
    OnSecondary = 0x000000,
    OnBackground = 0x000000,
    OnSurface = 0x000000,
    OnError = 0xffffff,
  };

  enum class MaterialDark : uint32_t {
    Primary = 0xbb86fc,
    PrimaryVariant = 0x3700B3,
    Secondary = 0x03dac6,
    Background = 0x121212,
    Surface = 0x121212,
    Error = 0xcf6679,
    OnPrimary = 0x000000,
    OnSecondary = 0x000000,
    OnBackground = 0xffffff,
    OnSurface = 0xffffff,
    OnError = 0x000000,
  };

  constexpr Color(BasicColor color);
  constexpr Color(MaterialWhite color);
  constexpr Color(MaterialDark color);
  template <typename... T>
  constexpr Color(T &&...params) : glm::u8vec4{std::forward<T>(params)...} {}

  Color &setRGB(uint32_t rgb, uint8_t opacity = _maxByte);
  Color &setRGB(uint32_t rgb, float opacity);
  [[nodiscard]] std::string getHashCode() const;
  [[nodiscard]] constexpr glm::vec3 vec3f() const;
  [[nodiscard]] constexpr glm::vec4 vec4f() const;

  [[nodiscard]] explicit operator std::string() const;

  [[nodiscard]] constexpr static Color fromRGB(uint32_t rgb,
                                               uint8_t opacity = _maxByte);
  [[nodiscard]] constexpr static Color fromRGB(uint32_t rgb, float opacity);
  [[nodiscard]] constexpr static Color fromRGBA(uint8_t rgba);
  [[nodiscard]] static Color parse(std::string_view hashColorCode);

private:
  constexpr static uint32_t _rMaskRGBA{0xff000000U};
  constexpr static uint32_t _gMaskRGBA{0x00ff0000U};
  constexpr static uint32_t _bMaskRGBA{0x0000ff00U};
  constexpr static uint32_t _aMaskRGBA{0x000000ffU};
  constexpr static uint32_t _rMaskRGB{0xff0000U};
  constexpr static uint32_t _gMaskRGB{0x00ff00U};
  constexpr static uint32_t _bMaskRGB{0x0000ffU};
  constexpr static unsigned int _offset3B{24U};
  constexpr static unsigned int _offset2B{16U};
  constexpr static unsigned int _offset1B{8U};
  constexpr static uint8_t _maxByte{255U};
  constexpr static uint8_t _halfByte{0x0fU};
};

inline constexpr Color::Color(BasicColor color)
    : Color{Color::fromRGB(static_cast<uint32_t>(color))} {}

inline constexpr Color::Color(MaterialWhite color)
    : Color{Color::fromRGB(static_cast<uint32_t>(color))} {}

inline constexpr Color::Color(MaterialDark color)
    : Color{Color::fromRGB(static_cast<uint32_t>(color))} {}

inline constexpr Color Color::fromRGB(uint32_t rgb, uint8_t opacity) {
  return Color{
      (rgb & _rMaskRGB) >> _offset2B,
      (rgb & _gMaskRGB) >> _offset1B,
      rgb & _bMaskRGB,
      opacity,
  };
}

inline constexpr glm::vec3 Color::vec3f() const {
  return {static_cast<float>(x) / _maxByte, static_cast<float>(y) / _maxByte,
          static_cast<float>(z) / _maxByte};
}

inline constexpr glm::vec4 Color::vec4f() const {
  return {static_cast<float>(x) / _maxByte, static_cast<float>(y) / _maxByte,
          static_cast<float>(z) / _maxByte, static_cast<float>(w) / _maxByte};
}

} // namespace SGEng
