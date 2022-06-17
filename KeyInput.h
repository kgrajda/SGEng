//===- KeyInput.h -----------------------------------------------*- C++ -*-===//
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

struct KeyState {
  bool press = false;
  mutable bool longPress = false;
};

class KeyInput {
public:
  KeyInput(Context &ctx, std::vector<int> keys);
  KeyInput(const KeyInput &keyInput);
  KeyInput &operator=(const KeyInput &keyInput);
  KeyInput(KeyInput &&keyInput) noexcept;
  KeyInput &operator=(KeyInput &&keyInput) noexcept;
  virtual ~KeyInput();

  bool isKeyDown(int key) const;
  bool isKeyClicked(int key) const;

  static void setup(Context &ctx, GLFWwindow *window);

private:
  std::reference_wrapper<Context> ctx;
  std::map<int, KeyState> keys;

  void setKeyState(int key, bool isDown);

  static void callback(GLFWwindow *window, int key, int scancode, int action,
                       int mods);
};

} // namespace SGEng