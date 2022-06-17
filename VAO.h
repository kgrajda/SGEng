//===- VAO.h ----------------------------------------------------*- C++ -*-===//
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

#include "utils.h"
#include <glad/gl.h>
#include <map>
#include <span>

namespace SGEng {

using DataLayout = std::map<GLuint, SubDataLayout>;

class VAO {
public:
  VAO(bool initialize = false);
  VAO(const VAO &vao) = delete;
  VAO &operator=(const VAO &vao) = delete;
  VAO(VAO &&vao) noexcept;
  VAO &operator=(VAO &&vao) noexcept;
  ~VAO();

  bool isInitialized() const;
  void initialize();
  GLuint getId() const;
  void linkVBO(GLuint vboId, const DataLayout &dataLayout,
               GLuint bindingIndex = 0);
  VAO &withVBO(GLuint vboId, const DataLayout &dataLayout,
               GLuint bindingIndex = 0);
  void linkEBO(GLuint eboId);
  VAO &withEBO(GLuint eboId);
  void bind() const;
  void unbind() const;
  void tryDestroy();
  void destroy();

  static VAO linkedWithVBO(GLuint vboId, const DataLayout &dataLayout,
                           GLuint bindingIndex = 0);
  static VAO linkedWithEBO(GLuint eboId);

private:
  GLuint id{0};
  DataLayout dataLayout;
};

} // namespace SGEng
