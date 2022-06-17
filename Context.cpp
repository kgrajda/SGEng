//===- Context.cpp ----------------------------------------------*- C++ -*-===//
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
#include "Context.h"

#include "FileManager.h"
#include "IFileManager.h"
#include "exceptions.h"
#include <plog/Log.h>

namespace SGEng {

void defaultDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
                         GLsizei length, const GLchar *message,
                         const void *userParam) {
  switch (severity) {
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    PLOGV << message;
    break;
  case GL_DEBUG_SEVERITY_LOW:
    PLOGD << message;
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    PLOGW << message;
    break;
  case GL_DEBUG_SEVERITY_HIGH:
    PLOGE << message;
    break;
  }
}

Context::Context(bool setup) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Context constructor...";
  if (setup)
    this->setup();
}

Context::~Context() {
  PLOGV_IF(LOG_DESTRUCTORS) << "Context destructor...";
  if (isGLFWInitialized)
    terminate();
}

Context &SGEng::Context::withConfig(const Config &config) {
  logger.setLogLevel(config.logLevel);
  cfg = config;
  return *this;
}

void Context::loadConfig(const fs::path &path) {
  PLOGV << "Loading config from file";
  try {
    cfg = fileManager->loadConfig(path);
    withConfig(cfg);
  } catch (const FileDoesNotExistError &err) {
    PLOGE << err.what() << "[" << err.getPath() << "]";
    PLOGW << "Config file not found.";
    withConfig(Config());
  } catch (const ConfigParseError &err) {
    PLOGE << err.what();
    PLOGW << "Config file corrupted.";
  }
}

void Context::setup() {
  PLOGV << "GLFW setup...";
  if (!isGLFWInitialized) {
    if (glfwInit() == GLFW_FALSE) {
      throw GLFWInitializationError("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG
    isGLFWInitialized = true;
    PLOGV << "GLFW setup complete";
  }
}

void Context::terminate() {
  PLOGV << "Terminating GLFW...";
  if (isGLFWInitialized) {
    glfwTerminate();
    isGLFWInitialized = false;
    PLOGV << "GLFW terminated";
  }
}

void Context::initializeGL() {
  PLOGV << "Initializing OpenGL...";
  if (!gladLoadGL(glfwGetProcAddress)) {
    throw GLInitializationError("Failed to initialize OpenGL context");
  };

#ifdef _DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugMessage, reinterpret_cast<void *>(this));
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                        GL_TRUE);
#endif // _DEBUG
  glViewport(0, 0, static_cast<int>(cfg.windowWidth),
             static_cast<int>(cfg.windowHeight));
  glEnable(GL_DEPTH_TEST);

  if (DISABLE_SWAP_INTERVAL)
    glfwSwapInterval(0);

  isGLInitialized = true;
  PLOGV << "OpenGL initialized";
}

bool Context::isInitialized() { return isGLInitialized; }

} // namespace SGEng
