//===- MouseInput.cpp -------------------------------------------*- C++ -*-===//
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
#include "MouseInput.h"

#include "Context.h"
#include <plog/Log.h>

namespace SGEng {

using namespace std::string_literals;

MouseInput::MouseInput(Context &ctx, std::vector<int> buttons) : ctx{ctx} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "MouseInput constructor...";
  for (auto button : buttons) {
    this->buttons[button] = {};
  }
  ctx.mouseInputs.push_back(this);
}

MouseInput::MouseInput(const MouseInput &mouseInput)
    : ctx{mouseInput.ctx}, buttons{mouseInput.buttons} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "MouseInput copy constructor...";
  ctx.get().mouseInputs.push_back(this);
}

MouseInput &MouseInput::operator=(const MouseInput &mouseInput) {
  PLOGV_IF(LOG_ASSIGNMENTS) << "MouseInput copy assignment...";
  if (&ctx.get() != &mouseInput.ctx.get()) {
    // Remove current mouse input from old context
    auto &_mouseInputs = ctx.get().mouseInputs;
    _mouseInputs.erase(
        std::remove(_mouseInputs.begin(), _mouseInputs.end(), this),
        _mouseInputs.end());
    ctx = mouseInput.ctx;
    // Put current mouse input in new context
    ctx.get().mouseInputs.push_back(this);
  }
  buttons = mouseInput.buttons;
  return *this;
}

MouseInput::MouseInput(MouseInput &&mouseInput) noexcept
    : ctx{mouseInput.ctx}, buttons{mouseInput.buttons} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "MouseInput move constructor...";
  ctx.get().mouseInputs.push_back(this);
}

MouseInput &MouseInput::operator=(MouseInput &&mouseInput) noexcept {
  PLOGV_IF(LOG_ASSIGNMENTS) << "MouseInput move assignment...";
  if (this != &mouseInput) {
    if (&ctx.get() != &mouseInput.ctx.get()) {
      // Remove current mouse input from old context
      auto &_mouseInputs = ctx.get().mouseInputs;
      _mouseInputs.erase(
          std::remove(_mouseInputs.begin(), _mouseInputs.end(), &mouseInput),
          _mouseInputs.end());
      ctx = mouseInput.ctx;
      // Put current mouse input in new context
      ctx.get().mouseInputs.push_back(this);
    }
    buttons = mouseInput.buttons;
    mouseInput.buttons.clear();
  }
  return *this;
}

MouseInput::~MouseInput() {
  auto &mouseInputs = ctx.get().mouseInputs;
  mouseInputs.erase(std::remove(mouseInputs.begin(), mouseInputs.end(), this),
                    mouseInputs.end());
}

bool MouseInput::isButtonDown(int button) const {
  auto it = buttons.find(button);
  if (it != buttons.end()) {
    return it->second.press;
  }
  return false;
}

bool MouseInput::isLeftButtonDown() const {
  return isButtonDown(GLFW_MOUSE_BUTTON_LEFT);
}

bool MouseInput::isRightButtonDown() const {
  return isButtonDown(GLFW_MOUSE_BUTTON_RIGHT);
}

bool MouseInput::isButtonClicked(int button) const {
  auto it = buttons.find(button);
  if (it != buttons.end() && it->second.press && !it->second.longPress) {
    it->second.longPress = true;
    return true;
  }
  return false;
}

bool MouseInput::isLeftButtonClicked() const {
  return isButtonClicked(GLFW_MOUSE_BUTTON_LEFT);
}

bool MouseInput::isRightButtonClicked() const {
  return isButtonClicked(GLFW_MOUSE_BUTTON_RIGHT);
}

void MouseInput::setup(Context &ctx, GLFWwindow *window) {
  glfwSetMouseButtonCallback(window, callback);
  ctx.areMouseInputsInitialized = true;
  PLOGV << "Mouse Input setup complete";
}

void MouseInput::setButtonState(int button, bool isDown) {
  auto it = buttons.find(button);
  if (it != buttons.end()) {
    PLOGV_IF(LOG_KEY_PRESS) << "Button "s + std::to_string(button) +
                                   (isDown ? " pressed" : " released");
    it->second.longPress = isDown && it->second.press;
    it->second.press = isDown;
  }
}

void MouseInput::callback(GLFWwindow *window, int button, int action,
                          int mods) {
  auto ctx = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
  assert(ctx);
  for (auto mouseInput : ctx->mouseInputs) {
    mouseInput->setButtonState(button, action != GLFW_RELEASE);
  }
}

} // namespace SGEng
