//===- uniforms.h -----------------------------------------------*- C++ -*-===//
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

#include "IUniform.h"
#include "types.h"
#include <glm/glm.hpp>

namespace SGEng {

class Uniform1f : public IUniform {
public:
  Uniform1f() = default;
  Uniform1f(const Shader &shader, std::string_view name);

  GLfloat get() const;
  void use() const;
  void set(GLfloat value);
  void set(vec1gl value);
  Uniform1f with(GLfloat value);
  Uniform1f with(vec1gl value);

  Uniform1f &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform1f &synced(const Shader &shader) override;

private:
  GLfloat value{};
};

class Uniform2f : public IUniform {
public:
  Uniform2f() = default;
  Uniform2f(const Shader &shader, std::string_view name);

  vec2gl get() const;
  void use() const;
  void set(GLfloat value1, GLfloat value2);
  void set(vec2gl value);
  Uniform2f with(GLfloat value1, GLfloat value2);
  Uniform2f with(vec2gl value);

  Uniform2f &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform2f &synced(const Shader &shader) override;

private:
  vec2gl value{};
};

class Uniform3f : public IUniform {
public:
  Uniform3f() = default;
  Uniform3f(const Shader &shader, std::string_view name);

  vec3gl get() const;
  void use() const;
  void set(GLfloat value1, GLfloat value2, GLfloat value3);
  void set(vec3gl value);
  Uniform3f with(GLfloat value1, GLfloat value2, GLfloat value3);
  Uniform3f with(vec3gl value);

  Uniform3f &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform3f &synced(const Shader &shader) override;

private:
  vec3gl value{};
};

class Uniform4f : public IUniform {
public:
  Uniform4f() = default;
  Uniform4f(const Shader &shader, std::string_view name);

  vec4gl get() const;
  void use() const;
  void set(GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
  void set(vec4gl value);
  Uniform4f with(vec4gl value);
  Uniform4f with(GLfloat value1, GLfloat value2, GLfloat value3,
                 GLfloat value4);

  Uniform4f &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform4f &synced(const Shader &shader) override;

private:
  vec4gl value{};
};

class Uniform1i : public IUniform {
public:
  Uniform1i() = default;
  Uniform1i(const Shader &shader, std::string_view name);

  GLint get() const;
  void set(GLint value);
  void set(ivec1gl value);
  Uniform1i with(GLint value);
  Uniform1i with(ivec1gl value);

  Uniform1i &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform1i &synced(const Shader &shader) override;

private:
  GLint value{};
};

class Uniform2i : public IUniform {
public:
  Uniform2i() = default;
  Uniform2i(const Shader &shader, std::string_view name);

  ivec2gl get() const;
  void set(GLint value1, GLint value2);
  void set(ivec2gl value);
  Uniform2i with(GLint value1, GLint value2);
  Uniform2i with(ivec2gl value);

  Uniform2i &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform2i &synced(const Shader &shader) override;

private:
  ivec2gl value{};
};

class Uniform3i : public IUniform {
public:
  Uniform3i() = default;
  Uniform3i(const Shader &shader, std::string_view name);

  ivec3gl get() const;
  void set(GLint value1, GLint value2, GLint value3);
  void set(ivec3gl value);
  Uniform3i with(GLint value1, GLint value2, GLint value3);
  Uniform3i with(ivec3gl value);

  Uniform3i &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform3i &synced(const Shader &shader) override;

private:
  ivec3gl value{};
};

class Uniform4i : public IUniform {
public:
  Uniform4i() = default;
  Uniform4i(const Shader &shader, std::string_view name);

  ivec4gl get() const;
  void set(GLint value1, GLint value2, GLint value3, GLint value4);
  void set(ivec4gl value);
  Uniform4i with(GLint value1, GLint value2, GLint value3, GLint value4);
  Uniform4i with(ivec4gl value);

  Uniform4i &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform4i &synced(const Shader &shader) override;

private:
  ivec4gl value{};
};

class Uniform1u : public IUniform {
public:
  Uniform1u() = default;
  Uniform1u(const Shader &shader, std::string_view name);

  GLuint get() const;
  void use() const;
  void set(GLuint value);
  void set(uvec1gl value);
  Uniform1u with(GLuint value);
  Uniform1u with(uvec1gl value);

  Uniform1u &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform1u &synced(const Shader &shader) override;

private:
  GLuint value{};
};

class Uniform2u : public IUniform {
public:
  Uniform2u() = default;
  Uniform2u(const Shader &shader, std::string_view name);

  uvec2gl get() const;
  void set(GLuint value1, GLuint value2);
  void set(uvec2gl value);
  Uniform2u with(GLuint value1, GLuint value2);
  Uniform2u with(uvec2gl value);

  Uniform2u &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform2u &synced(const Shader &shader) override;

private:
  uvec2gl value{};
};

class Uniform3u : public IUniform {
public:
  Uniform3u() = default;
  Uniform3u(const Shader &shader, std::string_view name);

  uvec3gl get() const;
  void set(GLuint value1, GLuint value2, GLuint value3);
  void set(uvec3gl value);
  Uniform3u with(GLuint value1, GLuint value2, GLuint value3);
  Uniform3u with(uvec3gl value);

  Uniform3u &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform3u &synced(const Shader &shader) override;

private:
  uvec3gl value{};
};

class Uniform4u : public IUniform {
public:
  Uniform4u() = default;
  Uniform4u(const Shader &shader, std::string_view name);

  uvec4gl get() const;
  void set(GLuint value1, GLuint value2, GLuint value3, GLuint value4);
  void set(uvec4gl value);
  Uniform4u with(GLuint value1, GLuint value2, GLuint value3, GLuint value4);
  Uniform4u with(uvec4gl value);

  Uniform4u &initialized(const Shader &shader, std::string_view name) override;
  void sync(const Shader &shader) override;
  Uniform4u &synced(const Shader &shader) override;

private:
  uvec4gl value{};
};

class UniformMat2 : public IUniform {
public:
  UniformMat2() = default;
  UniformMat2(const Shader &shader, std::string_view name);

  mat2gl get() const;
  void set(const mat2gl &value, bool transpose = false);
  UniformMat2 with(const mat2gl &value, bool transpose = false);

  UniformMat2 &initialized(const Shader &shader,
                           std::string_view name) override;
  void sync(const Shader &shader) override;
  UniformMat2 &synced(const Shader &shader) override;

private:
  mat2gl value{};
};

class UniformMat3 : public IUniform {
public:
  UniformMat3() = default;
  UniformMat3(const Shader &shader, std::string_view name);

  mat3gl get() const;
  void set(const mat3gl &value, bool transpose = false);
  UniformMat3 with(const mat3gl &value, bool transpose = false);

  UniformMat3 &initialized(const Shader &shader,
                           std::string_view name) override;
  void sync(const Shader &shader) override;
  UniformMat3 &synced(const Shader &shader) override;

private:
  mat3gl value{};
};

class UniformMat4 : public IUniform {
public:
  UniformMat4() = default;
  UniformMat4(const Shader &shader, std::string_view name);

  mat4gl get() const;
  void use() const;
  void set(const mat4gl &value, bool transpose = false);
  UniformMat4 with(const mat4gl &value, bool transpose = false);

  UniformMat4 &initialized(const Shader &shader,
                           std::string_view name) override;
  void sync(const Shader &shader) override;
  UniformMat4 &synced(const Shader &shader) override;

private:
  mat4gl value{};
};

} // namespace SGEng
