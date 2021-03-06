//===- cubes.h --------------------------------------------------*- C++ -*-===//
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

#include "../types.h"
#include <glad/gl.h>
#include <glm/vec3.hpp>

namespace SGEng {

struct Mesh;

Mesh generateCube(vec3gl center = {0.f, 0.f, 0.f},
                  vec3gl scale = {1.f, 1.f, 1.f}, float rotationAngle = 0.f,
                  vec3gl rotationAxis = {0.f, 1.f, 0.f});

Mesh generateOptimizedCube(vec3gl center = {0.f, 0.f, 0.f},
                           vec3gl scale = {1.f, 1.f, 1.f},
                           float rotationAngle = 0.f,
                           vec3gl rotationAxis = {0.f, 1.f, 0.f});
} // namespace SGEng
