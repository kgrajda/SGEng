//===- cubes.cpp ------------------------------------------------*- C++ -*-===//
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
#include "cubes.h"

#include "../Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

namespace SGEng {

Mesh SGEng::generateCube(vec3gl center, vec3gl scale, float rotationAngle,
                         vec3gl rotationAxis) {
  Mesh mesh;
  constexpr GLfloat half = 0.5f;
  const mat4gl normalRotation =
      glm::rotate(mat4gl(1.f), rotationAngle, rotationAxis);
  const glm::vec3 normal1 =
      vec3gl(normalRotation * vec4gl{0.f, 0.f, -1.f, 0.f});
  const glm::vec3 normal2 =
      vec3gl(normalRotation * vec4gl{-1.f, 0.f, 0.f, 0.f});
  const glm::vec3 normal3 = vec3gl(normalRotation * vec4gl{0.f, 0.f, 1.f, 0.f});
  const glm::vec3 normal4 = vec3gl(normalRotation * vec4gl{1.f, 0.f, 0.f, 0.f});
  const glm::vec3 normal5 = vec3gl(normalRotation * vec4gl{0.f, 1.f, 0.f, 0.f});
  const glm::vec3 normal6 =
      vec3gl(normalRotation * vec4gl{0.f, -1.f, 0.f, 0.f});

  mat4gl matrix = glm::scale(mat4gl(1.f), scale);
  matrix = glm::rotate(matrix, rotationAngle, rotationAxis);
  matrix = glm::translate(matrix, center);

  Vertex lowerLeftCloser1{};
  lowerLeftCloser1.position = vec3gl(matrix * vec4gl{half, -half, -half, 1.f});
  lowerLeftCloser1.normal = normal1;
  Vertex lowerLeftCloser4 = lowerLeftCloser1;
  lowerLeftCloser4.normal = normal4;
  Vertex lowerLeftCloser6 = lowerLeftCloser4;
  lowerLeftCloser6.normal = normal6;

  Vertex lowerRightCloser1{};
  lowerRightCloser1.position =
      vec3gl(matrix * vec4gl{-half, -half, -half, 1.f});
  lowerRightCloser1.normal = normal1;
  Vertex lowerRightCloser2 = lowerRightCloser1;
  lowerRightCloser2.normal = normal2;
  Vertex lowerRightCloser6 = lowerRightCloser1;
  lowerRightCloser6.normal = normal6;

  Vertex lowerRightFurther2{};
  lowerRightFurther2.position =
      vec3gl(matrix * vec4gl{-half, -half, half, 1.f});
  lowerRightFurther2.normal = normal2;
  Vertex lowerRightFurther3 = lowerRightFurther2;
  lowerRightFurther3.normal = normal3;
  Vertex lowerRightFurther6 = lowerRightFurther2;
  lowerRightFurther6.normal = normal6;

  Vertex lowerLeftFurther3{};
  lowerLeftFurther3.position = vec3gl(matrix * vec4gl{half, -half, half, 1.f});
  lowerLeftFurther3.normal = normal3;
  Vertex lowerLeftFurther4 = lowerLeftFurther3;
  lowerLeftFurther4.normal = normal4;
  Vertex lowerLeftFurther6 = lowerLeftFurther3;
  lowerLeftFurther6.normal = normal6;

  Vertex upperLeftCloser1{};
  upperLeftCloser1.position = vec3gl(matrix * vec4gl{half, half, -half, 1.f});
  upperLeftCloser1.normal = normal1;
  Vertex upperLeftCloser4 = upperLeftCloser1;
  upperLeftCloser4.normal = normal4;
  Vertex upperLeftCloser5 = upperLeftCloser1;
  upperLeftCloser5.normal = normal5;

  Vertex upperRightCloser1{};
  upperRightCloser1.position = vec3gl(matrix * vec4gl{-half, half, -half, 1.f});
  upperRightCloser1.normal = normal1;
  Vertex upperRightCloser2 = upperRightCloser1;
  upperRightCloser2.normal = normal2;
  Vertex upperRightCloser5 = upperRightCloser1;
  upperRightCloser5.normal = normal5;

  Vertex upperRightFurther2{};
  upperRightFurther2.position = vec3gl(matrix * vec4gl{-half, half, half, 1.f});
  upperRightFurther2.normal = normal2;
  Vertex upperRightFurther3 = upperRightFurther2;
  upperRightFurther3.normal = normal3;
  Vertex upperRightFurther5 = upperRightFurther2;
  upperRightFurther5.normal = normal5;

  Vertex upperLeftFurther3{};
  upperLeftFurther3.position = vec3gl(matrix * vec4gl{half, half, half, 1.f});
  upperLeftFurther3.normal = normal3;
  Vertex upperLeftFurther4 = upperLeftFurther3;
  upperLeftFurther4.normal = normal4;
  Vertex upperLeftFurther5 = upperLeftFurther3;
  upperLeftFurther5.normal = normal5;

  mesh.vertices = {
      // 1
      upperLeftCloser1, lowerLeftCloser1, lowerRightCloser1, upperRightCloser1,
      // 2
      upperRightCloser2, lowerRightCloser2, lowerRightFurther2,
      upperRightFurther2,
      // 3
      upperRightFurther3, lowerRightFurther3, lowerLeftFurther3,
      upperLeftFurther3,
      // 4
      upperLeftFurther4, lowerLeftFurther4, lowerLeftCloser4, upperLeftCloser4,
      // 5
      upperLeftFurther5, upperLeftCloser5, upperRightCloser5,
      upperRightFurther5,
      // 6
      lowerLeftCloser6, lowerLeftFurther6, lowerRightFurther6,
      lowerRightCloser6};
  mesh.indices = {
      0,  1,  2,  2,  3,  0,  // NOLINT(cppcoreguidelines-avoid-*)
      4,  5,  6,  6,  7,  4,  // NOLINT(cppcoreguidelines-avoid-*)
      8,  9,  10, 10, 11, 8,  // NOLINT(cppcoreguidelines-avoid-*)
      12, 13, 14, 14, 15, 12, // NOLINT(cppcoreguidelines-avoid-*)
      16, 17, 18, 18, 19, 16, // NOLINT(cppcoreguidelines-avoid-*)
      20, 21, 22, 22, 23, 20, // NOLINT(cppcoreguidelines-avoid-*)
  };

  return mesh;
}

Mesh generateOptimizedCube(vec3gl center, vec3gl scale, float rotationAngle,
                           vec3gl rotationAxis) {
  Mesh mesh;
  constexpr GLfloat half = 0.5f;

  mat4gl matrix = glm::scale(mat4gl(1.f), scale);
  matrix = glm::rotate(matrix, rotationAngle, rotationAxis);
  const mat4gl normalMatrix = matrix;
  matrix = glm::translate(matrix, center);

  Vertex lowerLeftCloser{};
  constexpr vec4gl positionLLC = {half, -half, -half, 1.f};
  lowerLeftCloser.position = matrix * positionLLC;
  lowerLeftCloser.normal = glm::normalize(normalMatrix * positionLLC);

  Vertex lowerRightCloser{};
  constexpr vec4gl positionLRC = {-half, -half, -half, 1.f};
  lowerRightCloser.position = matrix * positionLRC;
  lowerRightCloser.normal = glm::normalize(normalMatrix * positionLRC);

  Vertex lowerRightFurther{};
  constexpr vec4gl positionLRF = {-half, -half, half, 1.f};
  lowerRightFurther.position = matrix * positionLRF;
  lowerRightFurther.normal = glm::normalize(normalMatrix * positionLRF);

  Vertex lowerLeftFurther{};
  constexpr vec4gl positionLLF = {half, -half, half, 1.f};
  lowerLeftFurther.position = matrix * positionLLF;
  lowerLeftFurther.normal = glm::normalize(normalMatrix * positionLLF);

  Vertex upperLeftCloser{};
  constexpr vec4gl positionULC = {half, half, -half, 1.f};
  upperLeftCloser.position = matrix * positionULC;
  upperLeftCloser.normal = glm::normalize(normalMatrix * positionULC);

  Vertex upperRightCloser{};
  constexpr vec4gl positionURC = {-half, half, -half, 1.f};
  upperRightCloser.position = matrix * positionURC;
  upperRightCloser.normal = glm::normalize(normalMatrix * positionURC);

  Vertex upperRightFurther{};
  constexpr vec4gl positionURF = {-half, half, half, 1.f};
  upperRightFurther.position = matrix * positionURF;
  upperRightFurther.normal = glm::normalize(normalMatrix * positionURF);

  Vertex upperLeftFurther{};
  constexpr vec4gl positionULF = {half, half, half, 1.f};
  upperLeftFurther.position = matrix * positionULF;
  upperLeftFurther.normal = glm::normalize(normalMatrix * positionULF);

  mesh.vertices = {lowerLeftCloser,   lowerRightCloser, lowerRightFurther,
                   lowerLeftFurther,  upperLeftCloser,  upperRightCloser,
                   upperRightFurther, upperLeftFurther};
  mesh.indices = {
      4, 0, 1, 5, 4, 1, // NOLINT(cppcoreguidelines-avoid-*)
      5, 1, 2, 6, 5, 2, // NOLINT(cppcoreguidelines-avoid-*)
      6, 2, 3, 7, 6, 3, // NOLINT(cppcoreguidelines-avoid-*)
      7, 3, 0, 4, 7, 0, // NOLINT(cppcoreguidelines-avoid-*)
      6, 7, 4, 5, 6, 4, // NOLINT(cppcoreguidelines-avoid-*)
      0, 2, 1, 3, 2, 0  // NOLINT(cppcoreguidelines-avoid-*)
  };

  return mesh;
}

} // namespace SGEng
