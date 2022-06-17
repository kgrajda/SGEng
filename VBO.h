//===- VBO.h ----------------------------------------------------*- C++ -*-===//
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

#include <glad/gl.h>

#if __cplusplus >= 202002L
#include <span>
#endif

namespace SGEng {

struct Vertex;

class VBO {
public:
  VBO() = default;
  VBO(const GLfloat *data, size_t size);
  VBO(const Vertex *vertices, size_t size);
  VBO(const VBO &vbo) = delete;
  VBO &operator=(const VBO &vbo) = delete;
  VBO(VBO &&vbo) noexcept;
  VBO &operator=(VBO &&vbo) noexcept;
  ~VBO();

  bool isInitialized() const;
  void initialize(const GLfloat *data, size_t size);
  void initialize(const Vertex *vertices, size_t size);
  VBO &initializedWith(const GLfloat *data, size_t size);
  VBO &initializedWith(const Vertex *vertices, size_t size);
  GLuint getId() const;
  void set(const GLfloat *data, size_t size);
  void set(const Vertex *vertices, size_t size);
  void tryDestroy();
  void destroy();

#if __cplusplus >= 202002L
  VBO(std::span<GLfloat> data);
  VBO(std::span<Vertex> vertices);
  void initialize(std::span<GLfloat> data);
  void initialize(std::span<Vertex> vertices);
  VBO &initializedWith(std::span<GLfloat> data);
  VBO &initializedWith(std::span<Vertex> vertices);
  void set(std::span<GLfloat> data);
  void set(std::span<Vertex> vertices);
#endif

private:
  GLuint id{0};
};

} // namespace SGEng