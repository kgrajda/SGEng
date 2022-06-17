//===- App.h ----------------------------------------------------*- C++ -*-===//
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

#include "Config.h"
#include "Context.h"
#include "Window.h"

namespace SGEng {

class App {
public:
  App(Context &ctx, bool initialize = true);
  virtual ~App();

  virtual bool onStartup() = 0;
  virtual bool update(double ts, double td) = 0;
  virtual void draw() = 0;
  virtual void onDestroy() = 0;

  App &withConfig(const Config &config);
  void initialize();
  bool isInitialized() const;
  void destroy();
  void run();
  void performFrame(bool poll = true);

  Window &getWindow();
  const Window &getWindow() const;

protected:
  // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)
  Window window;
  std::reference_wrapper<Context> ctx;
  // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
private:
  bool _isInitialized{false};
  bool _startupCalled{false};
  double _countResetTimestamp{0.0};
  double _lastTimestamp{0.0};
  double _currentTimestamp{0.0};
  unsigned int _frameCount{0};

  void mainLoop();
};

} // namespace SGEng
