//===- LoggerState.h --------------------------------------------*- C++ -*-===//
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
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Logger.h>

namespace SGEng {

namespace fs = std::filesystem;

template <int instanceId = PLOG_DEFAULT_INSTANCE_ID> class LoggerState {
public:
  LoggerState(plog::Severity logLevel = defaultLogLevel,
              const fs::path &logPath = defaultLogPath) {
    if (!_appended)
      logger.addAppender(&consoleAppender).addAppender(&fileAppender);

    setLogLevel(logLevel);
    setLogFilePath(logPath);
  }

  plog::Severity getLogLevel() const { return logger.getMaxSeverity(); }

  void setLogLevel(plog::Severity logLevel) { logger.setMaxSeverity(logLevel); }

  void setLogFilePath(const fs::path &path) {
    fileAppender.setFileName(path.c_str());
  }

private:
  plog::Logger<instanceId> &logger{plog::init(defaultLogLevel)};

  // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
  static bool _appended;
  static plog::RollingFileAppender<plog::TxtFormatter> fileAppender;
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
};

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
template <int instanceId> bool LoggerState<instanceId>::_appended{false};

template <int instanceId>
plog::RollingFileAppender<plog::TxtFormatter>
    LoggerState<instanceId>::fileAppender{defaultLogPath.c_str()};

template <int instanceId>
plog::ColorConsoleAppender<plog::TxtFormatter>
    LoggerState<instanceId>::consoleAppender{};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

} // namespace SGEng