//===- config_parsing.cpp ---------------------------------------*- C++ -*-===//
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
#include "config_parsing.h"

#include "Config.h"
#include "constants.h"
#include <plog/Log.h>

namespace SGEng {

Config parseConfig(const toml::table &tbl) {
  // Load background color (assume default if error)
  Color backgroundColor{defaultBackgroundColor};
  toml::optional<std::string> rawBackgroundColor =
      tbl["background_color"].value<std::string>();
  if (rawBackgroundColor.has_value()) {
    try {
      backgroundColor = Color::parse(rawBackgroundColor.value());
    } catch (const ColorParseError &err) {
      PLOGE << err.what();
    }
  }

  // Load log level (assume default if error)
  plog::Severity logLevel = defaultLogLevel;
  toml::optional<int> rawLogLevel = tbl["logLevel"].value<int>();
  if (rawLogLevel.has_value()) {
    if (rawLogLevel.value() >= static_cast<int>(plog::none) &&
        rawLogLevel.value() <= static_cast<int>(plog::verbose))
      logLevel = static_cast<plog::Severity>(rawLogLevel.value());
    else
      PLOGW << "Invalid logLevel specified in config, assuming default";
  }

  fs::path logFilePath = defaultLogPath;
  toml::optional<std::string> rawLogFilePath =
      tbl["lodFilePath"].value<std::string>();
  if (rawLogFilePath.has_value() &&
      fs::exists(fs::path(rawLogFilePath.value())))
    logFilePath = fs::path(rawLogFilePath.value());

  fs::path resourcesDirectory = defaultResourcesDirectory;
  toml::optional<std::string> rawResourcesDirectory =
      tbl["resourcesDirectory"].value<std::string>();
  if (rawResourcesDirectory.has_value() &&
      fs::exists(fs::path(rawResourcesDirectory.value())))
    resourcesDirectory = fs::path(rawResourcesDirectory.value());

  return Config()
      .withWindowWidth(tbl["window"]["width"].value_or(defaultWindowWidth))
      .withWindowHeight(tbl["window"]["height"].value_or(defaultWindowHeight))
      .withWindowTitle(tbl["window"]["title"].value_or<std::string>(
          defaultWindowTitle.data()))
      .withBackgroundColor(backgroundColor)
      .withLogLevel(logLevel)
      .withLogFilePath(logFilePath)
      .withShowFPS(tbl["showFPS"].value_or(false))
      .withStartWindowMaximized(
          tbl["window"]["startMaximized"].value_or(defaultStartWindowMaximized))
      .withResourcesDirectory(resourcesDirectory);
}

} // namespace SGEng
