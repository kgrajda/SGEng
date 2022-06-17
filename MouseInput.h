//===- MouseInput.h ---------------------------------------------*- C++ -*-===//
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
#include <GLFW/glfw3.h>
#include <functional>
#include <map>
#include <vector>

namespace SGEng {

struct Context;

struct ButtonState {
  bool press = false;
  mutable bool longPress = false;
};

class MouseInput {
public:
  MouseInput(Context &ctx, std::vector<int> buttons);
  MouseInput(const MouseInput &keyInput);
  MouseInput &operator=(const MouseInput &mouseInput);
  MouseInput(MouseInput &&mouseInput) noexcept;
  MouseInput &operator=(MouseInput &&mouseInput) noexcept;
  virtual ~MouseInput();

  bool isButtonDown(int button) const;
  bool isLeftButtonDown() const;
  bool isRightButtonDown() const;
  bool isButtonClicked(int button) const;
  bool isLeftButtonClicked() const;
  bool isRightButtonClicked() const;

  static void setup(Context &ctx, GLFWwindow *window);

private:
  std::reference_wrapper<Context> ctx;
  std::map<int, ButtonState> buttons;

  void setButtonState(int button, bool isDown);

  static void callback(GLFWwindow *window, int button, int action, int mods);
};

} // namespace SGEng
