//===- EBO.h ----------------------------------------------------*- C++ -*-===//
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

class EBO {
public:
  EBO() = default;
  EBO(const GLuint *indices, size_t size);
  EBO(const EBO &ebo) = delete;
  EBO &operator=(const EBO &ebo) = delete;
  EBO(EBO &&ebo) noexcept;
  EBO &operator=(EBO &&ebo) noexcept;
  ~EBO() noexcept;

  bool isInitialized() const;
  void initialize(const GLuint *indices, size_t size);
  EBO &initializedWith(const GLuint *indices, size_t size);
  GLuint getId() const;
  void set(const GLuint *indices, size_t size);
  void tryDestroy();
  void destroy();

#if __cplusplus >= 202002L
  EBO(std::span<GLuint> indices);
  void initialize(std::span<GLuint> indices);
  EBO &initializeWith(std::span<GLuint> indices);
  void set(std::span<GLuint> indices);
#endif

private:
  GLuint id{0};
};

} // namespace SGEng
