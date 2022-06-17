//===- exceptions.cpp -------------------------------------------*- C++ -*-===//
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
#include "exceptions.h"

#include "Shader.h"
#include <glad/gl.h>

namespace SGEng {

FileError::FileError(const std::string &msg, fs::path path)
    : std::runtime_error(msg), path{std::move(path)} {}

const fs::path &FileError::getPath() const noexcept { return path; }

FileDoesNotExistError::FileDoesNotExistError(const std::string &msg,
                                             fs::path path)
    : FileError(msg, std::move(path)){};

ConfigParseError::ConfigParseError(const std::string &msg, fs::path path)
    : std::runtime_error(msg), path{std::move(path)} {}

const fs::path &ConfigParseError::getPath() const noexcept { return path; }

GLFWInitializationError::GLFWInitializationError(const std::string &msg)
    : std::runtime_error(msg) {}

GLInitializationError::GLInitializationError(const std::string &msg)
    : std::runtime_error(msg) {}

WindowInitializationError::WindowInitializationError(const std::string &msg)
    : std::runtime_error(msg) {}

ShaderCompilationError::ShaderCompilationError(GLenum type, std::string infoLog)
    : type{type}, infoLog{std::move(infoLog)},
      std::runtime_error("[" + std::string(Shader::typeToStringView(type)) +
                         "] Compilation failed") {}

const std::string &ShaderCompilationError::getInfoLog() const noexcept {
  return infoLog;
}

ShaderLinkingError::ShaderLinkingError(std::string infoLog)
    : infoLog{std::move(infoLog)}, std::runtime_error(
                                       "Shader program linking failed") {}

const std::string &ShaderLinkingError::getInfoLog() const noexcept {
  return infoLog;
}

ModelLoadingError::ModelLoadingError(const std::string &msg, fs::path path,
                                     std::string info)
    : std::runtime_error(msg), path{std::move(path)}, info{std::move(info)} {}

const fs::path &ModelLoadingError::getPath() const noexcept { return path; }

const std::string &ModelLoadingError::getInfo() const noexcept { return info; }

} // namespace SGEng
