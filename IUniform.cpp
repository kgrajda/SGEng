//===- IUniform.cpp ---------------------------------------------*- C++ -*-===//
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
#include "IUniform.h"

#include "Shader.h"

namespace SGEng {

IUniform::IUniform(const Shader &shader, std::string_view name) {
  initialize(shader, name);
}

bool IUniform::isInitialized() const { return location != -1; }

GLint IUniform::getLocation() { return location; }

void IUniform::initialize(const Shader &shader, std::string_view name) {
  location = shader.getUniformLocation(name).value_or(-1);
  location = glGetUniformLocation(shader.getId(), name.data());
}

} // namespace SGEng
