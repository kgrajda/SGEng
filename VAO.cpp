//===- VAO.cpp --------------------------------------------------*- C++ -*-===//
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
#include "VAO.h"

#include "constants.h"
#include <plog/Log.h>

namespace SGEng {

VAO::VAO(bool initialize) {
  if (initialize)
    this->initialize();
}

VAO::VAO(VAO &&vao) noexcept
    : id{vao.id}, dataLayout{std::move(vao.dataLayout)} {
  vao.id = 0;
  vao.dataLayout.clear();
}

VAO &VAO::operator=(VAO &&vao) noexcept {
  if (this != &vao) {
    tryDestroy();
    id = vao.id;
    dataLayout = std::move(vao.dataLayout);
    vao.id = 0;
    vao.dataLayout.clear();
  }
  return *this;
}

VAO::~VAO() { tryDestroy(); }

bool VAO::isInitialized() const { return id != 0; }

void VAO::initialize() {
  PLOGV_IF(LOG_VAO) << "VAO initialization...";
  glCreateVertexArrays(1, &id);
}

GLuint VAO::getId() const { return id; }

void VAO::linkVBO(GLuint vboId, const DataLayout &dataLayout,
                  GLuint bindingIndex) {
  if (!isInitialized())
    initialize();
  PLOGV_IF(LOG_BUFFER_LINKING) << "Linking VBO to VAO...";
  this->dataLayout = dataLayout;
  size_t accumulatedSize{0};
  for (const auto &[layoutIndex, subDataLayout] : dataLayout) {
    glEnableVertexArrayAttrib(id, layoutIndex);
    glVertexArrayAttribBinding(id, layoutIndex, bindingIndex);
    glVertexArrayAttribFormat(
        id, layoutIndex, static_cast<GLint>(subDataLayout.length), GL_FLOAT,
        GL_FALSE, static_cast<GLuint>(subDataLayout.offset));
    accumulatedSize += subDataLayout.length;
  }
  glVertexArrayVertexBuffer(
      id, bindingIndex, vboId, 0,
      static_cast<GLsizei>(accumulatedSize * sizeof(GLfloat)));
}

VAO &VAO::withVBO(GLuint vboId, const DataLayout &dataLayout,
                  GLuint bindingIndex) {
  linkVBO(vboId, dataLayout, bindingIndex);
  return *this;
}

void VAO::linkEBO(GLuint eboId) {
  if (!isInitialized())
    initialize();
  PLOGV_IF(LOG_BUFFER_LINKING) << "Linking EBO to VAO...";
  glVertexArrayElementBuffer(id, eboId);
}

VAO &VAO::withEBO(GLuint eboId) {
  linkEBO(eboId);
  return *this;
}

void VAO::bind() const { glBindVertexArray(id); }

void VAO::unbind() const { glBindVertexArray(0); }

void VAO::tryDestroy() {
  if (isInitialized())
    destroy();
}

void VAO::destroy() {
  glDeleteVertexArrays(1, &id);
  id = 0;
  PLOGV_IF(LOG_VAO) << "VAO destroyed";
}

VAO VAO::linkedWithVBO(GLuint vboId, const DataLayout &dataLayout,
                       GLuint bindingIndex) {
  VAO vao(true);
  return std::move(vao.withVBO(vboId, dataLayout, bindingIndex));
}

VAO VAO::linkedWithEBO(GLuint eboId) { return std::move(VAO().withEBO(eboId)); }

} // namespace SGEng