//===- Config.h -------------------------------------------------*- C++ -*-===//
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

#include "constants.h"
#include <filesystem>
#include <glm/vec4.hpp>
#include <plog/Severity.h>
#include <string>

namespace SGEng {

namespace fs = std::filesystem;

struct Config {
  Config &withWindowWidth(int windowWidth);
  Config &withWindowHeight(int windowHeight);
  Config &withWindowTitle(const std::string &windowTitle);
  Config &withBackgroundColor(glm::u8vec4 backgroundColor);
  Config &withLogLevel(plog::Severity logLevel);
  Config &withLogFilePath(const fs::path &path);
  Config &withShowFPS(bool showFPS);
  Config &withStartWindowMaximized(bool startWindowMaximized);
  Config &withResourcesDirectory(const fs::path &path);

  int windowWidth{defaultWindowWidth};
  int windowHeight{defaultWindowHeight};
  int minWindowWidth{defaultMinWindowWidth};
  int minWindowHeight{defaultMinWindowHeight};
  std::string windowTitle{defaultWindowTitle};
  glm::u8vec4 backgroundColor{defaultBackgroundColor};
  plog::Severity logLevel{defaultLogLevel};
  fs::path logFilePath{defaultLogPath};
  bool showFPS{defaultShowFPS};
  bool startWindowMaximized{defaultStartWindowMaximized};
  fs::path resourcesDirectory{defaultResourcesDirectory};
};

} // namespace SGEng