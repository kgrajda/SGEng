//===- Window.h -------------------------------------------------*- C++ -*-===//
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

#include "Color.h"
#include "Context.h"
#include "IRenderer.h"
#include "constants.h"
#include <GLFW/glfw3.h>
#include <exception>
#include <glm/vec2.hpp>
#include <string>

namespace SGEng {

struct Config;
struct Scene;

class Window {
public:
  Window(Context &ctx);
  Window(const Window &window);
  Window &operator=(const Window &window);
  Window(Window &&window) noexcept;
  Window &operator=(Window &&window) noexcept;
  virtual ~Window();

  Window &withConfig(const Config &config);
  void initialize();
  void makeContextCurrent();
  bool isInitialized() const;

  // Getters, Setters
  const GLFWwindow *getRawWindow() const;
  GLFWwindow *getRawWindow();
  const IRenderer *getRenderer() const;
  IRenderer *getRenderer();
  void createRenderer();
  unsigned int getWidth() const;
  unsigned int getHeight() const;
  glm::uvec2 getDimensions() const;
  void resize(int width, int height);
  const std::string &getTitle() const;
  void setTitle(const std::string &title);
  void setNeedsToChangeTitle(const std::string &title);
  Color getBackgroundColor() const;
  void setBackgroundColor(Color color);
  glm::ivec2 getPosition() const;
  void setPosition(glm::ivec2 position);

  bool isActive() const;
  bool shouldClose() const;
  void close();
  void destroy();
  void swapBuffers() const;
  void clearScreen() const;
  void draw(const Scene &scene) const;
  void update();

  static void poll();
  static void waitEvents();
  static void windowRefreshCallback(GLFWwindow *window);

private:
  std::reference_wrapper<Context> ctx;
  std::unique_ptr<IRenderer> renderer;
  bool _isInitialized{false};
  GLFWwindow *window{nullptr};
  glm::ivec2 position{};
  int width, height;
  std::string title;
  Color backgroundColor{defaultBackgroundColor};

  // Thread safety related members
  bool needsToChangeTitle{false};
  std::string newTitle;
};

} // namespace SGEng