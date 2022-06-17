//===- Shader.h -------------------------------------------------*- C++ -*-===//
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

#include "IFileManager.h"
#include <filesystem>
#include <glad/gl.h>
#include <memory>

namespace SGEng {

namespace fs = std::filesystem;
using namespace std::string_view_literals;

class Shader;

class ScopedShaderUsage {
public:
  ScopedShaderUsage(const Shader &shader);
  ~ScopedShaderUsage();

private:
  std::reference_wrapper<const Shader> shader;
};

class Shader {
public:
  Shader();
  Shader(IFileManager &fileManager, const fs::path &vertexShaderPath,
         const fs::path &fragmentShaderPath);

  ~Shader();

  void initialize(IFileManager &fileManager, fs::path vertexShaderPath,
                  fs::path fragmentShaderPath);
  bool tryInitialize(IFileManager &fileManager, fs::path vertexShaderPath,
                     fs::path fragmentShaderPath);
  void use() const;
  void forget() const;
  std::shared_ptr<ScopedShaderUsage> scopedUsage() const;
  void tryDestroy();
  void destroy();
  GLuint getId() const;
  bool isInitialized() const;
  void reload(IFileManager &fileManager,
              std::optional<fs::path> vertexShaderPath = std::nullopt,
              std::optional<fs::path> fragmentShaderPath = std::nullopt);
  bool tryReload(IFileManager &fileManager,
                 std::optional<fs::path> vertexShaderPath = std::nullopt,
                 std::optional<fs::path> fragmentShaderPath = std::nullopt);
  std::optional<GLint> getUniformLocation(std::string_view name) const;

  constexpr static std::string_view typeToStringView(GLenum type);
  constexpr static std::string_view fileExtension(GLenum type);

private:
  GLuint id{0};
  bool _isInitialized{false};
  fs::path vertexShaderPath;
  fs::path fragmentShaderPath;
  mutable std::weak_ptr<ScopedShaderUsage> scopedUsagePtr;

  GLuint initializeShader(IFileManager &fileManager, const fs::path &path,
                          GLenum type);
};

inline constexpr std::string_view Shader::typeToStringView(GLenum type) {
  switch (type) {
  case GL_VERTEX_SHADER:
    return "Vertex Shader"sv;
  case GL_FRAGMENT_SHADER:
    return "Fragment Shader"sv;
  case GL_GEOMETRY_SHADER:
    return "Geometry Shader"sv;
  case GL_COMPUTE_SHADER:
    return "Compute Shader"sv;
  case GL_TESS_CONTROL_SHADER:
    return "Tesselation Control Shader"sv;
  case GL_TESS_EVALUATION_SHADER:
    return "Tesselation Evaluation Shader"sv;
  default:
    return "Unknown Shader"sv;
  }
}

inline constexpr std::string_view Shader::fileExtension(GLenum type) {
  switch (type) {
  case GL_VERTEX_SHADER:
    return "vert"sv;
  case GL_FRAGMENT_SHADER:
    return "frag"sv;
  case GL_GEOMETRY_SHADER:
    return "geom"sv;
  case GL_COMPUTE_SHADER:
    return "comp"sv;
  case GL_TESS_CONTROL_SHADER:
    return "tesc"sv;
  case GL_TESS_EVALUATION_SHADER:
    return "frag"sv;
  default:
    return "glsl"sv;
  }
}

} // namespace SGEng
