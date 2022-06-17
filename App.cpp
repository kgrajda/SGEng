//===- App.cpp --------------------------------------------------*- C++ -*-===//
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
#include "App.h"

#include "FileManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "Renderer.h"
#include <array>
#include <plog/Log.h>
#include <thread>

namespace SGEng {

App::App(Context &ctx, bool initialize) : ctx(ctx), window(ctx) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "App constructor...";
  ctx.app = this;
  if (!ctx.isGLFWInitialized)
    ctx.setup();
  if (initialize)
    this->initialize();
}

App::~App() {
  PLOGV_IF(LOG_DESTRUCTORS) << "App destructor...";
  ctx.get().app = nullptr;
}

App &App::withConfig(const Config &config) {
  window.resize(config.windowWidth, config.windowHeight);
  return *this;
}

void App::initialize() {
  PLOGV << "Initializing app...";
  Context &ctx = this->ctx.get();
  assert(ctx.fileManager);
  if (!ctx.isGLFWInitialized)
    ctx.setup();
  window.initialize();
  if (!ctx.areKeyInputsInitialized)
    KeyInput::setup(ctx, window.getRawWindow());
  if (!ctx.areMouseInputsInitialized)
    MouseInput::setup(ctx, window.getRawWindow());

  _isInitialized = true;
  PLOGV << "App initialized";
}

bool App::isInitialized() const { return _isInitialized; }

void App::destroy() {
  onDestroy();
  PLOGV << "App destroyed";
}

void App::run() {
  std::jthread thr = std::jthread([this] { this->mainLoop(); });

  while (window.isActive()) {
    window.waitEvents();
    window.update();
  }
}

void App::performFrame(bool poll) {
  _lastTimestamp = _currentTimestamp;
  _currentTimestamp = glfwGetTime();
  _frameCount++;

  if (_currentTimestamp - _countResetTimestamp > 1.0) {
    PLOGD_IF(LOG_FPS) << "FPS: " << _frameCount;
    if (ctx.get().cfg.showFPS)
      window.setNeedsToChangeTitle(ctx.get().cfg.windowTitle + " - " +
                                   std::to_string(_frameCount));
    _countResetTimestamp += 1.0;
    _frameCount = 0;
  }

  if (window.getRenderer())
    window.getRenderer()->update();

  if (update(_currentTimestamp, _currentTimestamp - _lastTimestamp)) [[likely]]
    draw();
}

Window &App::getWindow() { return window; }

const Window &App::getWindow() const { return window; }

void App::mainLoop() {
  assert(window.isInitialized());
  assert(window.isActive());
  window.createRenderer();
  assert(window.getRenderer());

  if (!_startupCalled) {
    bool doContinue = onStartup();
    _startupCalled = true;
    if (!doContinue)
      return;
  }

  _countResetTimestamp = glfwGetTime();

  while (window.isActive()) {
    performFrame();
  }

  destroy();
}

} // namespace SGEng
