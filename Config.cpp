//===- Config.cpp -----------------------------------------------*- C++ -*-===//
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
#include "Config.h"

#include "FileManager.h"
#include <plog/Log.h>

namespace SGEng {

Config &Config::withWindowWidth(int windowWidth) {
  this->windowWidth = windowWidth;
  return *this;
}

Config &Config::withWindowHeight(int windowHeight) {
  this->windowHeight = windowHeight;
  return *this;
}

Config &Config::withWindowTitle(const std::string &windowTitle) {
  this->windowTitle = windowTitle;
  return *this;
}

Config &Config::withBackgroundColor(glm::u8vec4 backgroundColor) {
  this->backgroundColor = backgroundColor;
  return *this;
}

Config &Config::withLogLevel(plog::Severity logLevel) {
  this->logLevel = logLevel;
  return *this;
}

Config &Config::withLogFilePath(const fs::path &path) {
  logFilePath = path;
  return *this;
}

Config &Config::withShowFPS(bool showFPS) {
  this->showFPS = showFPS;
  return *this;
}

Config &Config::withStartWindowMaximized(bool startWindowMaximized) {
  this->startWindowMaximized = startWindowMaximized;
  return *this;
}

Config &Config::withResourcesDirectory(const fs::path &path) {
  resourcesDirectory = path;
  return *this;
}

} // namespace SGEng
