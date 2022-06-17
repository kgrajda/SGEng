//===- VBO.cpp --------------------------------------------------*- C++ -*-===//
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
#include "VBO.h"

#include "Vertex.h"
#include "constants.h"
#include <plog/Log.h>
#include <utility>

namespace SGEng {

VBO::VBO(const GLfloat *data, size_t size) { initialize(data, size); }

VBO::VBO(const Vertex *vertices, size_t size) { initialize(vertices, size); }

VBO::VBO(VBO &&vbo) noexcept : id(vbo.id) { vbo.id = 0; }

VBO &VBO::operator=(VBO &&vbo) noexcept {
  if (this != &vbo) {
    tryDestroy();
    std::swap(id, vbo.id);
  }
  return *this;
}

VBO::~VBO() { tryDestroy(); }

bool VBO::isInitialized() const { return id != 0; }

void VBO::initialize(const GLfloat *data, size_t size) {
  tryDestroy();
  PLOGV_IF(LOG_BUFFERS) << "VBO initialization...";
  glCreateBuffers(1, &id);
  set(data, size);
}

void VBO::initialize(const Vertex *vertices, size_t size) {
  tryDestroy();
  PLOGV_IF(LOG_BUFFERS) << "VBO initialization...";
  glCreateBuffers(1, &id);
  set(vertices, size);
}

VBO &VBO::initializedWith(const GLfloat *data, size_t size) {
  initialize(data, size);
  return *this;
}

VBO &VBO::initializedWith(const Vertex *vertices, size_t size) {
  initialize(vertices, size);
  return *this;
}

GLuint VBO::getId() const { return id; }

void VBO::set(const GLfloat *data, size_t size) {
  glNamedBufferData(id, static_cast<GLsizeiptr>(size * sizeof(GLfloat)), data,
                    GL_STATIC_DRAW);
}

void VBO::set(const Vertex *vertices, size_t size) {
  glNamedBufferData(id, static_cast<GLsizeiptr>(size * sizeof(Vertex)),
                    vertices, GL_STATIC_DRAW);
}

void VBO::tryDestroy() {
  if (isInitialized())
    destroy();
}

void VBO::destroy() {
  glDeleteBuffers(1, &id);
  id = 0;
  PLOGV_IF(LOG_BUFFERS) << "VBO destroyed";
}

#if __cplusplus >= 202002L
VBO::VBO(std::span<GLfloat> data) { initialize(data); }

VBO::VBO(std::span<Vertex> vertices) { initialize(vertices); }

void VBO::initialize(std::span<GLfloat> data) {
  tryDestroy();
  PLOGV_IF(LOG_BUFFERS) << "VBO initialization...";
  glCreateBuffers(1, &id);
  set(data);
}

void VBO::initialize(std::span<Vertex> vertices) {
  tryDestroy();
  PLOGV_IF(LOG_BUFFERS) << "VBO initialization...";
  glCreateBuffers(1, &id);
  set(vertices);
}

VBO &VBO::initializedWith(std::span<GLfloat> data) {
  initialize(data);
  return *this;
}

VBO &VBO::initializedWith(std::span<Vertex> vertices) {
  initialize(vertices);
  return *this;
}

void VBO::set(std::span<GLfloat> data) {
  glNamedBufferData(id, static_cast<GLsizeiptr>(data.size_bytes()), data.data(),
                    GL_STATIC_DRAW);
}

void VBO::set(std::span<Vertex> vertices) {
  glNamedBufferData(id, static_cast<GLsizeiptr>(vertices.size_bytes()),
                    vertices.data(), GL_STATIC_DRAW);
}
#endif

} // namespace SGEng