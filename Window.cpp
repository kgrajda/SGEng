//===- Window.cpp -----------------------------------------------*- C++ -*-===//
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
#include "Window.h"

#include "App.h"
#include "Config.h"
#include "Renderer.h"
#include "exceptions.h"
#include <plog/Log.h>

namespace SGEng {

Window::Window(Context &ctx)
    : ctx{ctx}, width{ctx.cfg.windowWidth}, height{ctx.cfg.windowHeight},
      title{ctx.cfg.windowTitle}, backgroundColor{ctx.cfg.backgroundColor} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Window constructor...";
}

Window::Window(const Window &window)
    : ctx{window.ctx}, width{window.ctx.get().cfg.windowWidth},
      height{window.ctx.get().cfg.windowHeight},
      title{window.ctx.get().cfg.windowTitle},
      backgroundColor{window.ctx.get().cfg.backgroundColor} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Window copy constructor...";
}

Window &Window::operator=(const Window &window) {
  PLOGV_IF(LOG_ASSIGNMENTS) << "Window copy assignment...";
  ctx = window.ctx;
  resize(window.width, window.height);
  setTitle(window.title);
  setBackgroundColor(window.backgroundColor);
  return *this;
}

Window::Window(Window &&window) noexcept : ctx(window.ctx) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Window move constructor...";
  if (isInitialized()) {
    destroy();
  }
  this->backgroundColor = window.backgroundColor;
  this->width = window.width;
  this->height = window.height;
  this->title = std::move(window.title);
  this->window = std::move(window.window);
  this->_isInitialized = window._isInitialized;
  renderer.swap(window.renderer);
  window.backgroundColor = defaultBackgroundColor;
  window.width = defaultWindowWidth;
  window.height = defaultWindowHeight;
  window.title = defaultWindowTitle;
  window.window = nullptr;
  window._isInitialized = false;
}

Window &Window::operator=(Window &&window) noexcept {
  PLOGV_IF(LOG_ASSIGNMENTS) << "Window move assignment...";
  if (this != &window) {
    if (isInitialized()) {
      destroy();
    }
    this->backgroundColor = window.backgroundColor;
    this->width = window.width;
    this->height = window.height;
    this->title = std::move(window.title);
    this->window = std::move(window.window);
    this->_isInitialized = window._isInitialized;
    std::swap(this->ctx, window.ctx);
    renderer.swap(window.renderer);
    window.backgroundColor = defaultBackgroundColor;
    window.width = defaultWindowWidth;
    window.height = defaultWindowHeight;
    window.title = defaultWindowTitle;
    window.window = nullptr;
    window._isInitialized = false;

    makeContextCurrent();
  }
  return *this;
}

Window::~Window() {
  PLOGV_IF(LOG_DESTRUCTORS) << "Window destructor...";
  destroy();
  ctx.get().currentWindow = nullptr;
}

Window &Window::withConfig(const Config &config) {
  setTitle(config.windowTitle);
  resize(config.windowWidth, config.windowHeight);
  setBackgroundColor(config.backgroundColor);
  return *this;
}

void Window::initialize() {
  ctx.get().currentWindow = this;
  PLOGV << "Initializing window...";

  if (!ctx.get().isGLFWInitialized)
    throw WindowInitializationError("GLFW is not initialized");

  if (isInitialized())
    throw WindowInitializationError("Window is already initialized");

  if (width <= 0 || height <= 0)
    throw WindowInitializationError(
        "Invalid window dimensions: " + std::to_string(width) + " x " +
        std::to_string(height));

  window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                            title.data(), nullptr, nullptr);
  if (ctx.get().cfg.startWindowMaximized)
    glfwMaximizeWindow(window);
  glfwSetWindowUserPointer(window, reinterpret_cast<void *>(&ctx.get()));
  glfwSetWindowRefreshCallback(window, Window::windowRefreshCallback);
  glfwSetWindowSizeLimits(window, ctx.get().cfg.minWindowWidth,
                          ctx.get().cfg.minWindowHeight, GLFW_DONT_CARE,
                          GLFW_DONT_CARE);

  glfwGetWindowPos(window, &position.x, &position.y);

  _isInitialized = true;
  PLOGV_IF(window != nullptr) << "Window innitialized";
  PLOGV_IF(window == nullptr) << "Window innitialization failed";
}

void Window::makeContextCurrent() {
  glfwMakeContextCurrent(window);
  ctx.get().currentWindow = this;
  PLOGV << "Window context made current";
}

bool Window::isInitialized() const { return _isInitialized; }

unsigned int Window::getWidth() const { return width; }

unsigned int Window::getHeight() const { return height; }

glm::uvec2 Window::getDimensions() const { return {width, height}; }

void Window::resize(int width, int height) {
  if (width < defaultMinWindowWidth || height < defaultMinWindowHeight) {
    PLOGV << "Window size too small: " << width << "x" << height;
    return;
  }

  if (this->width != width || this->height != height) {
    this->width = width;
    this->height = height;
    if (isInitialized())
      glfwSetWindowSize(window, width, height);
    if (ctx.get().isGLInitialized) {
      renderer->setNeedsToResize();
    }
    PLOGV_IF(LOG_WINDOW_RESIZE) << "Window resized";
  }
}

const std::string &Window::getTitle() const { return title; }

void Window::setTitle(const std::string &title) {
  if (this->title != title) {
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
    PLOGV_IF(LOG_WINDOW_TITLE_CHANGE) << "Window title changed";
  }
}

Color Window::getBackgroundColor() const { return backgroundColor; }

void Window::setBackgroundColor(Color backgroundColor) {
  if (this->backgroundColor != backgroundColor) {
    this->backgroundColor = backgroundColor;
    PLOGV_IF(LOG_WINDOW_BACKGROUND_COLOR_CHANGE) << "Background color changed";
  }
}

glm::ivec2 Window::getPosition() const { return position; }

void Window::setPosition(glm::ivec2 position) {
  if (this->position != position) {
    glfwSetWindowPos(window, position.x, position.y);
    this->position = position;
  }
}

bool Window::isActive() const { return !shouldClose(); }

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

void Window::close() {
  glfwSetWindowShouldClose(window, true);
  PLOGV << "Window closed";
}

void Window::swapBuffers() const { glfwSwapBuffers(window); }

void Window::clearScreen() const {
  auto col = backgroundColor.vec4f();
  glClearColor(col.r, col.g, col.b, col.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::destroy() {
  if (isInitialized()) {
    glfwDestroyWindow(window);
    _isInitialized = false;
    PLOGV << "Window destroyed";
  }
}

void Window::draw(const Scene &scene) const {
  clearScreen();

  renderer->render(scene);

  swapBuffers();
}

void Window::update() {
  if (needsToChangeTitle) {
    setTitle(newTitle);
    needsToChangeTitle = false;
  }
}

void Window::setNeedsToChangeTitle(const std::string &title) {
  if (this->title != title) {
    newTitle = title;
    needsToChangeTitle = true;
  }
}

void Window::poll() { glfwPollEvents(); }

void Window::waitEvents() { glfwWaitEvents(); }

void Window::windowRefreshCallback(GLFWwindow *window) {
  PLOGV_IF(LOG_WINDOW_REFRESH) << "Window refresh...";
  auto ctx = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
  assert(ctx);
  if (ctx->currentWindow) {
    int width{0}, height{0};
    glfwGetFramebufferSize(window, &width, &height);

    if (width == 0 || height == 0)
      return;

    if (width != ctx->currentWindow->getWidth() ||
        height != ctx->currentWindow->getHeight()) {
      assert(ctx->app);
      ctx->currentWindow->resize(width, height);
    }
  }
}

const GLFWwindow *Window::getRawWindow() const { return window; }

GLFWwindow *Window::getRawWindow() { return window; }

const IRenderer *Window::getRenderer() const { return renderer.get(); }

IRenderer *Window::getRenderer() { return renderer.get(); }

void Window::createRenderer() {
  makeContextCurrent();
  if (!ctx.get().isGLInitialized)
    ctx.get().initializeGL();
  renderer = std::make_unique<Renderer>(ctx, *this);
}

} // namespace SGEng
