//===- uniforms.cpp ---------------------------------------------*- C++ -*-===//
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
#include "uniforms.h"

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace SGEng {

Uniform1f::Uniform1f(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

GLfloat Uniform1f::get() const { return value; }

void Uniform1f::use() const { glUniform1f(location, value); }

void Uniform1f::set(GLfloat value) {
  if (isInitialized()) {
    this->value = value;
    glUniform1f(location, value);
  }
}

void Uniform1f::set(vec1gl value) { set(value.x); }

Uniform1f Uniform1f::with(GLfloat value) {
  set(value);
  return *this;
}

Uniform1f Uniform1f::with(vec1gl value) {
  set(value);
  return *this;
}

Uniform1f &Uniform1f::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform1f::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value), &value);
}

Uniform1f &Uniform1f::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform1i::Uniform1i(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

GLint Uniform1i::get() const { return value; }

void Uniform1i::set(GLint value) {
  if (isInitialized()) {
    this->value = value;
    glUniform1i(location, value);
  }
}

void Uniform1i::set(ivec1gl value) { set(value.x); }

Uniform1i Uniform1i::with(GLint value) {
  set(value);
  return *this;
}

Uniform1i Uniform1i::with(ivec1gl value) {
  set(value);
  return *this;
}

Uniform1i &Uniform1i::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform1i::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformiv(shader.getId(), location, sizeof(value), &value);
}

Uniform1i &Uniform1i::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform1u::Uniform1u(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

GLuint Uniform1u::get() const { return value; }

void Uniform1u::use() const { glUniform1ui(location, value); }

void Uniform1u::set(GLuint value) {
  if (isInitialized()) {
    this->value = value;
    glUniform1ui(location, value);
  }
}

void Uniform1u::set(uvec1gl value) { set(value.x); }

Uniform1u Uniform1u::with(GLuint value) {
  set(value);
  return *this;
}

Uniform1u Uniform1u::with(uvec1gl value) {
  set(value);
  return *this;
}

Uniform1u &Uniform1u::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform1u::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformuiv(shader.getId(), location, sizeof(value), &value);
}

Uniform1u &Uniform1u::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform2f::Uniform2f(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

vec2gl Uniform2f::get() const { return value; }

void Uniform2f::use() const { glUniform2f(location, value.x, value.y); }

void Uniform2f::set(GLfloat value1, GLfloat value2) { set({value1, value2}); }

void Uniform2f::set(vec2gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform2f(location, value.x, value.y);
  }
}

Uniform2f Uniform2f::with(GLfloat value1, GLfloat value2) {
  set(value1, value2);
  return *this;
}

Uniform2f Uniform2f::with(vec2gl value) {
  set(value);
  return *this;
}

Uniform2f &Uniform2f::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform2f::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

Uniform2f &Uniform2f::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

vec3gl Uniform3f::get() const { return value; }

void Uniform3f::use() const {
  glUniform3f(location, value.x, value.y, value.z);
}

void Uniform3f::set(GLfloat value1, GLfloat value2, GLfloat value3) {
  set({value1, value2, value3});
}

void Uniform3f::set(vec3gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform3f(location, value.x, value.y, value.z);
  }
}

Uniform3f Uniform3f::with(GLfloat value1, GLfloat value2, GLfloat value3) {
  set(value1, value2, value3);
  return *this;
}

Uniform3f Uniform3f::with(vec3gl value) {
  set(value);
  return *this;
}

Uniform3f &Uniform3f::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

Uniform3f::Uniform3f(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

void Uniform3f::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

Uniform3f &Uniform3f::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform4f::Uniform4f(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

vec4gl Uniform4f::get() const { return value; }

void Uniform4f::use() const {
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Uniform4f::set(GLfloat value1, GLfloat value2, GLfloat value3,
                    GLfloat value4) {
  set({value1, value2, value3, value4});
}

void Uniform4f::set(vec4gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform4f(location, value.x, value.y, value.z, value.w);
  }
}

Uniform4f Uniform4f::with(vec4gl value) {
  set(value);
  return *this;
}

Uniform4f Uniform4f::with(GLfloat value1, GLfloat value2, GLfloat value3,
                          GLfloat value4) {
  set(value1, value2, value3, value4);
  return *this;
}

Uniform4f &Uniform4f::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform4f::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

Uniform4f &Uniform4f::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform2i::Uniform2i(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

ivec2gl Uniform2i::get() const { return value; }

void Uniform2i::set(GLint value1, GLint value2) { set({value1, value2}); }

void Uniform2i::set(ivec2gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform2i(location, value.x, value.y);
  }
}

Uniform2i Uniform2i::with(GLint value1, GLint value2) {
  set(value1, value2);
  return *this;
}

Uniform2i Uniform2i::with(ivec2gl value) {
  set(value);
  return *this;
}

Uniform2i &Uniform2i::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform2i::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformiv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

Uniform2i &Uniform2i::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform3i::Uniform3i(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

ivec3gl Uniform3i::get() const { return value; }

void Uniform3i::set(GLint value1, GLint value2, GLint value3) {
  set({value1, value2, value3});
}

void Uniform3i::set(ivec3gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform3i(location, value.x, value.y, value.z);
  }
}

Uniform3i Uniform3i::with(GLint value1, GLint value2, GLint value3) {
  set(value1, value2, value3);
  return *this;
}

Uniform3i Uniform3i::with(ivec3gl value) {
  set(value);
  return *this;
}

Uniform3i &Uniform3i::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform3i::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformiv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

Uniform3i &Uniform3i::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform4i::Uniform4i(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

ivec4gl Uniform4i::get() const { return value; }

void Uniform4i::set(GLint value1, GLint value2, GLint value3, GLint value4) {
  set({value1, value2, value3, value4});
}

void Uniform4i::set(ivec4gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform4i(location, value.x, value.y, value.z, value.w);
  }
}

Uniform4i Uniform4i::with(GLint value1, GLint value2, GLint value3,
                          GLint value4) {
  set(value1, value2, value3, value4);
  return *this;
}

Uniform4i Uniform4i::with(ivec4gl value) {
  set(value);
  return *this;
}

Uniform4i &Uniform4i::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform4i::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformiv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

Uniform4i &Uniform4i::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform2u::Uniform2u(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

uvec2gl Uniform2u::get() const { return value; }

void Uniform2u::set(GLuint value1, GLuint value2) { set({value1, value2}); }

void Uniform2u::set(uvec2gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform2ui(location, value.x, value.y);
  }
}

Uniform2u Uniform2u::with(GLuint value1, GLuint value2) {
  set(value1, value2);
  return *this;
}

Uniform2u Uniform2u::with(uvec2gl value) {
  set(value);
  return *this;
}

Uniform2u &Uniform2u::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform2u::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformuiv(shader.getId(), location, sizeof(value),
                     glm::value_ptr(value));
}

Uniform2u &Uniform2u::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform3u::Uniform3u(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

uvec3gl Uniform3u::get() const { return value; }

void Uniform3u::set(GLuint value1, GLuint value2, GLuint value3) {
  set({value1, value2, value3});
}

void Uniform3u::set(uvec3gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform3ui(location, value.x, value.y, value.z);
  }
}

Uniform3u Uniform3u::with(GLuint value1, GLuint value2, GLuint value3) {
  set(value1, value2, value3);
  return *this;
}

Uniform3u Uniform3u::with(uvec3gl value) {
  set(value);
  return *this;
}

Uniform3u &Uniform3u::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform3u::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformuiv(shader.getId(), location, sizeof(value),
                     glm::value_ptr(value));
}

Uniform3u &Uniform3u::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

Uniform4u::Uniform4u(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

uvec4gl Uniform4u::get() const { return value; }

void Uniform4u::set(GLuint value1, GLuint value2, GLuint value3,
                    GLuint value4) {
  set({value1, value2, value3, value4});
}

void Uniform4u::set(uvec4gl value) {
  if (isInitialized()) {
    this->value = value;
    glUniform4ui(location, value.x, value.y, value.z, value.w);
  }
}

Uniform4u Uniform4u::with(GLuint value1, GLuint value2, GLuint value3,
                          GLuint value4) {
  set(value1, value2, value3, value4);
  return *this;
}

Uniform4u Uniform4u::with(uvec4gl value) {
  set(value);
  return *this;
}

Uniform4u &Uniform4u::initialized(const Shader &shader, std::string_view name) {
  initialize(shader, name);
  return *this;
}

void Uniform4u::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformuiv(shader.getId(), location, sizeof(value),
                     glm::value_ptr(value));
}

Uniform4u &Uniform4u::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

UniformMat2::UniformMat2(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

mat2gl UniformMat2::get() const { return value; }

void UniformMat2::set(const mat2gl &value, bool transpose) {
  if (isInitialized()) {
    if (transpose)
      this->value = glm::transpose(value);
    else
      this->value = value;
    glUniformMatrix2fv(location, 1, transpose, glm::value_ptr(value));
  }
}

UniformMat2 UniformMat2::with(const mat2gl &value, bool transpose) {
  set(value, transpose);
  return *this;
}

UniformMat2 &UniformMat2::initialized(const Shader &shader,
                                      std::string_view name) {
  initialize(shader, name);
  return *this;
}

void UniformMat2::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

UniformMat2 &UniformMat2::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

UniformMat3::UniformMat3(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

mat3gl UniformMat3::get() const { return value; }

void UniformMat3::set(const mat3gl &value, bool transpose) {
  if (isInitialized()) {
    if (transpose)
      this->value = glm::transpose(value);
    else
      this->value = value;
    glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(value));
  }
}

UniformMat3 UniformMat3::with(const mat3gl &value, bool transpose) {
  set(value, transpose);
  return *this;
}

UniformMat3 &UniformMat3::initialized(const Shader &shader,
                                      std::string_view name) {
  initialize(shader, name);
  return *this;
}

void UniformMat3::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

UniformMat3 &UniformMat3::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

UniformMat4::UniformMat4(const Shader &shader, std::string_view name)
    : IUniform(shader, name) {}

mat4gl UniformMat4::get() const { return value; }

void UniformMat4::use() const {
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void UniformMat4::set(const mat4gl &value, bool transpose) {
  if (isInitialized()) {
    if (transpose)
      this->value = glm::transpose(value);
    else
      this->value = value;
    glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value));
  }
}

UniformMat4 UniformMat4::with(const mat4gl &value, bool transpose) {
  set(value, transpose);
  return *this;
}

UniformMat4 &UniformMat4::initialized(const Shader &shader,
                                      std::string_view name) {
  initialize(shader, name);
  return *this;
}

void UniformMat4::sync(const Shader &shader) {
  if (isInitialized())
    glGetnUniformfv(shader.getId(), location, sizeof(value),
                    glm::value_ptr(value));
}

UniformMat4 &UniformMat4::synced(const Shader &shader) {
  sync(shader);
  return *this;
}

} // namespace SGEng
