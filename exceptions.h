//===- exceptions.h ---------------------------------------------*- C++ -*-===//
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

#include <filesystem>
#include <glad/gl.h>
#include <string>

namespace SGEng {

namespace fs = std::filesystem;

class FileError : public std::runtime_error {
public:
  FileError(const std::string &msg, fs::path path);

  const fs::path &getPath() const noexcept;

private:
  std::string _msg;
  fs::path path;
};

class FileDoesNotExistError : public FileError {
public:
  FileDoesNotExistError(const std::string &msg, fs::path path);
};

class ConfigParseError : public std::runtime_error {
public:
  ConfigParseError(const std::string &msg, fs::path path);

  const fs::path &getPath() const noexcept;

private:
  std::string _msg;
  fs::path path;
};

class GLFWInitializationError : public std::runtime_error {
public:
  GLFWInitializationError(const std::string &msg);
};

class GLInitializationError : public std::runtime_error {
public:
  GLInitializationError(const std::string &msg);
};

class WindowInitializationError : public std::runtime_error {
public:
  WindowInitializationError(const std::string &msg);
};

class ShaderCompilationError : public std::runtime_error {
public:
  ShaderCompilationError(GLenum type, std::string infoLog);

  const std::string &getInfoLog() const noexcept;

private:
  GLenum type;
  std::string infoLog;
};

class ShaderLinkingError : public std::runtime_error {
public:
  ShaderLinkingError(std::string infoLog);

  const std::string &getInfoLog() const noexcept;

private:
  std::string infoLog;
};

class ModelLoadingError : public std::runtime_error {
public:
  ModelLoadingError(const std::string &msg, fs::path path, std::string info);

  const fs::path &getPath() const noexcept;
  const std::string &getInfo() const noexcept;

private:
  fs::path path;
  std::string info;
};

} // namespace SGEng
