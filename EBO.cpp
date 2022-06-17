//===- EBO.cpp --------------------------------------------------*- C++ -*-===//
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
#include "EBO.h"

#include "constants.h"
#include <plog/Log.h>
#include <utility>

namespace SGEng {

EBO::EBO(const GLuint *indices, size_t size) { initialize(indices, size); }

EBO::EBO(EBO &&ebo) noexcept : id(ebo.id) { ebo.id = 0; }

EBO &EBO::operator=(EBO &&ebo) noexcept {
  if (this != &ebo) {
    tryDestroy();
    std::swap(id, ebo.id);
  }
  return *this;
}

EBO::~EBO() { tryDestroy(); }

bool EBO::isInitialized() const { return id != 0; }

void EBO::initialize(const GLuint *indices, size_t size) {
  tryDestroy();
  PLOGV_IF(LOG_BUFFERS) << "EBO initialization...";
  glCreateBuffers(1, &id);
  set(indices, size);
}

EBO &EBO::initializedWith(const GLuint *indices, size_t size) {
  initialize(indices, size);
  return *this;
}

GLuint EBO::getId() const { return id; }

void EBO::set(const GLuint *indices, size_t size) {
  glNamedBufferData(id, static_cast<GLsizeiptr>(size * sizeof(GLuint)), indices,
                    GL_STATIC_DRAW);
}

void EBO::tryDestroy() {
  if (isInitialized())
    destroy();
}

void EBO::destroy() {
  glDeleteBuffers(1, &id);
  id = 0;
  PLOGV_IF(LOG_BUFFERS) << "EBO destroyed";
}

#if __cplusplus >= 202002L
EBO::EBO(std::span<GLuint> indices) { initialize(indices); }

void EBO::initialize(std::span<GLuint> indices) {
  tryDestroy();
  PLOGV_IF(LOG_BUFFERS) << "EBO initialization...";
  glCreateBuffers(1, &id);
  set(indices);
}

EBO &EBO::initializeWith(std::span<GLuint> indices) {
  initialize(indices);
  return *this;
}
void EBO::set(std::span<GLuint> indices) {
  glNamedBufferData(id, static_cast<GLsizeiptr>(indices.size_bytes()),
                    indices.data(), GL_STATIC_DRAW);
}
#endif

} // namespace SGEng
