//===- Shader.cpp -----------------------------------------------*- C++ -*-===//
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
#include "Shader.h"

#include "FileManager.h"
#include "exceptions.h"
#include <cassert>
#include <glm/glm.hpp>
#include <plog/Log.h>

namespace SGEng {

Shader::Shader() { PLOGV_IF(LOG_CONSTRUCTORS) << "Shader constructor 1..."; }

Shader::Shader(IFileManager &fileManager, const fs::path &vertexShaderPath,
               const fs::path &fragmentShaderPath) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Shader constructor 2...";
  initialize(fileManager, vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader() {
  PLOGV_IF(LOG_DESTRUCTORS) << "Shader destructor...";
  tryDestroy();
}

void Shader::initialize(IFileManager &fileManager, fs::path vertexShaderPath,
                        fs::path fragmentShaderPath) {
  PLOGV_IF(LOG_SHADERS) << "Initializing shader program...";
  GLuint vertexShader =
      initializeShader(fileManager, vertexShaderPath, GL_VERTEX_SHADER);
  GLuint fragmentShader =
      initializeShader(fileManager, fragmentShaderPath, GL_FRAGMENT_SHADER);

  GLuint newId = glCreateProgram();
  glAttachShader(newId, vertexShader);
  glAttachShader(newId, fragmentShader);
  glLinkProgram(newId);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLint success{GL_FALSE};
  glGetProgramiv(newId, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(newId, GL_INFO_LOG_LENGTH, &maxLength);
    std::string infoLog;
    infoLog.reserve(maxLength);
    glGetProgramInfoLog(newId, maxLength, nullptr, infoLog.data());
    glDeleteProgram(newId);
    throw ShaderLinkingError(std::move(infoLog));
  }

  tryDestroy();
  id = newId;
  this->vertexShaderPath = std::move(vertexShaderPath);
  this->fragmentShaderPath = std::move(fragmentShaderPath);
  _isInitialized = true;
  PLOGV_IF(LOG_SHADERS) << "Shader program initialized";
}

bool Shader::tryInitialize(IFileManager &fileManager, fs::path vertexShaderPath,
                           fs::path fragmentShaderPath) {
  try {
    initialize(fileManager, vertexShaderPath, fragmentShaderPath);
  } catch (const ShaderCompilationError &e) {
    PLOGE << e.what();
    std::string infoLog = e.getInfoLog();
    if (!infoLog.empty())
      PLOGE << "More info: " << e.getInfoLog();
    return false;
  } catch (const ShaderLinkingError &e) {
    PLOGE << e.what();
    std::string infoLog = e.getInfoLog();
    if (!infoLog.empty())
      PLOGE << "More info: " << e.getInfoLog();
    return false;
  }
  return true;
}

void Shader::use() const { glUseProgram(id); }

void Shader::forget() const { glUseProgram(0); }

std::shared_ptr<ScopedShaderUsage> Shader::scopedUsage() const {
  auto _scopedUsage = scopedUsagePtr.lock();
  if (_scopedUsage)
    return _scopedUsage; // Increment reference counter
  // Create new if no usage exists
  _scopedUsage = std::make_shared<ScopedShaderUsage>(*this);
  scopedUsagePtr = _scopedUsage;
  return std::move(_scopedUsage);
}

void Shader::tryDestroy() {
  if (isInitialized())
    destroy();
}

void Shader::destroy() {
  glDeleteProgram(id);
  _isInitialized = false;
  PLOGV_IF(LOG_SHADERS) << "Shader program destroyed";
}

GLuint Shader::getId() const { return id; }

bool Shader::isInitialized() const { return _isInitialized; }

void Shader::reload(IFileManager &fileManager,
                    std::optional<fs::path> vertexShaderPath,
                    std::optional<fs::path> fragmentShaderPath) {
  fs::path newVertexShaderPath =
      vertexShaderPath.value_or(this->vertexShaderPath);
  fs::path newFragmentShaderPath =
      fragmentShaderPath.value_or(this->fragmentShaderPath);

  initialize(fileManager, newVertexShaderPath, newFragmentShaderPath);
  PLOGI_IF(LOG_SHADERS_RELOAD) << "Shaders reloaded";
}

bool Shader::tryReload(IFileManager &fileManager,
                       std::optional<fs::path> vertexShaderPath,
                       std::optional<fs::path> fragmentShaderPath) {
  try {
    reload(fileManager, vertexShaderPath, fragmentShaderPath);
  } catch (const ShaderCompilationError &e) {
    PLOGE << e.what();
    std::string infoLog = e.getInfoLog();
    if (!infoLog.empty())
      PLOGE << "More info: " << e.getInfoLog();
    return false;
  } catch (const ShaderLinkingError &e) {
    PLOGE << e.what();
    std::string infoLog = e.getInfoLog();
    if (!infoLog.empty())
      PLOGE << "More info: " << e.getInfoLog();
    return false;
  }
  return true;
}

std::optional<GLint> Shader::getUniformLocation(std::string_view name) const {
  auto loc = glGetUniformLocation(id, name.data());
  if (loc != -1)
    return loc;
  return std::nullopt;
}

GLuint Shader::initializeShader(IFileManager &fileManager, const fs::path &path,
                                GLenum type) {
  std::string shaderSource = fileManager.loadTextFile(path);
  GLuint shaderId = glCreateShader(type);

  auto rawShaderSource = shaderSource.c_str();
  glShaderSource(shaderId, 1, &rawShaderSource, nullptr);
  glCompileShader(shaderId);

  GLint success{GL_FALSE};
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success); // error check
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
    std::string infoLog;
    infoLog.reserve(maxLength);
    glGetShaderInfoLog(shaderId, maxLength, nullptr, infoLog.data());
    glDeleteShader(shaderId);
    throw ShaderCompilationError(type, std::move(infoLog));
  }

  PLOGV_IF(LOG_SHADERS) << "Shader of type " << type
                        << " successfully compiled";
  return shaderId;
}

ScopedShaderUsage::ScopedShaderUsage(const Shader &shader) : shader{shader} {
  shader.use();
}

ScopedShaderUsage::~ScopedShaderUsage() { shader.get().forget(); }

} // namespace SGEng