//===- KeyInput.cpp ---------------------------------------------*- C++ -*-===//
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
#include "KeyInput.h"

#include "Context.h"
#include <plog/Log.h>

namespace SGEng {

using namespace std::string_literals;

KeyInput::KeyInput(Context &ctx, std::vector<int> keys) : ctx(ctx) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "KeyInput constructor...";
  for (auto key : keys) {
    this->keys[key] = {};
  }
  ctx.keyInputs.push_back(this);
}

KeyInput::KeyInput(const KeyInput &keyInput)
    : ctx(keyInput.ctx), keys(keyInput.keys) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "KeyInput copy constructor...";
  ctx.get().keyInputs.push_back(this);
}

KeyInput &KeyInput::operator=(const KeyInput &keyInput) {
  PLOGV_IF(LOG_ASSIGNMENTS) << "KeyInput copy assignment...";
  if (&ctx.get() != &keyInput.ctx.get()) {
    // Remove current key input from old context
    auto &_keyInputs = ctx.get().keyInputs;
    _keyInputs.erase(std::remove(_keyInputs.begin(), _keyInputs.end(), this),
                     _keyInputs.end());
    ctx = keyInput.ctx;
    // Put current key input in new context
    ctx.get().keyInputs.push_back(this);
  }
  keys = keyInput.keys;
  return *this;
}

KeyInput::KeyInput(KeyInput &&keyInput) noexcept
    : ctx(keyInput.ctx), keys(keyInput.keys) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "KeyInput move constructor...";
  ctx.get().keyInputs.push_back(this);
}

KeyInput &KeyInput::operator=(KeyInput &&keyInput) noexcept {
  PLOGV_IF(LOG_ASSIGNMENTS) << "KeyInput move assignment...";
  if (this != &keyInput) {
    if (&ctx.get() != &keyInput.ctx.get()) {
      // Remove current key input from old context
      auto &_keyInputs = ctx.get().keyInputs;
      _keyInputs.erase(
          std::remove(_keyInputs.begin(), _keyInputs.end(), &keyInput),
          _keyInputs.end());
      ctx = keyInput.ctx;
      // Put current key input in new context
      ctx.get().keyInputs.push_back(this);
    }
    keys = keyInput.keys;
    keyInput.keys.clear();
  }
  return *this;
}

KeyInput::~KeyInput() {
  auto &keyInputs = ctx.get().keyInputs;
  keyInputs.erase(std::remove(keyInputs.begin(), keyInputs.end(), this),
                  keyInputs.end());
}

bool KeyInput::isKeyDown(int key) const {
  auto it = keys.find(key);
  if (it != keys.end()) {
    return it->second.press;
  }
  return false;
}

bool KeyInput::isKeyClicked(int key) const {
  auto it = keys.find(key);
  if (it != keys.end() && it->second.press && !it->second.longPress) {
    it->second.longPress = true;
    return true;
  }
  return false;
}

void KeyInput::setup(Context &ctx, GLFWwindow *window) {
  glfwSetKeyCallback(window, callback);
  ctx.areKeyInputsInitialized = true;
  PLOGV << "Key Input setup complete";
}

void KeyInput::setKeyState(int key, bool isDown) {
  auto it = keys.find(key);
  if (it != keys.end()) {
    PLOGV_IF(LOG_KEY_PRESS)
        << "Key "s + std::to_string(key) + (isDown ? " pressed" : " released");
    it->second.longPress = isDown && it->second.press;
    it->second.press = isDown;
  }
}

void KeyInput::callback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  auto ctx = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
  assert(ctx);
  for (auto keyInput : ctx->keyInputs) {
    keyInput->setKeyState(key, action != GLFW_RELEASE);
  }
}

} // namespace SGEng