//===- Context.h ------------------------------------------------*- C++ -*-===//
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
#include "FileManager.h"
#include "IFileManager.h"
#include "LoggerState.h"
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <plog/Init.h>

namespace SGEng {

class KeyInput;
class MouseInput;
class App;
class Window;

void defaultDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
                         GLsizei length, const GLchar *message,
                         const void *userParam);

struct Context {
  Context(bool setup = true);
  Context(const Context &ctx) = delete;
  Context &operator=(const Context &ctx) = delete;
  Context(Context &&ctx) noexcept = delete;
  Context &operator=(Context &&ctx) noexcept = delete;
  ~Context();

  LoggerState<> logger{};

  bool isGLFWInitialized{false};
  GLFWerrorfun glfwErrorCallback{nullptr};

  bool isGLInitialized{false};
  GLDEBUGPROC glDebugMessage{defaultDebugMessage};

  bool areKeyInputsInitialized{false};
  std::vector<KeyInput *> keyInputs;
  bool areMouseInputsInitialized{false};
  std::vector<MouseInput *> mouseInputs;

  Config cfg;
  Context &withConfig(const Config &config);
  void loadConfig(const fs::path &path = defaultConfigPath);

  std::unique_ptr<IFileManager> fileManager{std::make_unique<FileManager>()};

  App *app{nullptr}; // Needed for GLFW callbacks - especially for window
                     // refresh callback that needs to call App.performFrame()
                     // method.
  Window *currentWindow{nullptr}; // Window with current OpenGL context

  void setup();
  void terminate();
  void initializeGL();
  bool isInitialized();
};

} // namespace SGEng
