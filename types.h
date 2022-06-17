//===- types.h --------------------------------------------------*- C++ -*-===//
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
///
/// \file
/// Some common types used throughout the project.
///
//===----------------------------------------------------------------------===//
#pragma once

#include <glad/gl.h>
#include <glm/fwd.hpp>

namespace SGEng {

using vec1gl = glm::vec<1, GLfloat>;
using vec2gl = glm::vec<2, GLfloat>;
using vec3gl = glm::vec<3, GLfloat>;
using vec4gl = glm::vec<4, GLfloat>;
using ivec1gl = glm::vec<1, GLint>;
using ivec2gl = glm::vec<2, GLint>;
using ivec3gl = glm::vec<3, GLint>;
using ivec4gl = glm::vec<4, GLint>;
using uvec1gl = glm::vec<1, GLuint>;
using uvec2gl = glm::vec<2, GLuint>;
using uvec3gl = glm::vec<3, GLuint>;
using uvec4gl = glm::vec<4, GLuint>;
using mat2gl = glm::mat<2, 2, GLfloat>;
using mat3gl = glm::mat<3, 3, GLfloat>;
using mat4gl = glm::mat<4, 4, GLfloat>;

} // namespace SGEng