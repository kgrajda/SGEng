//===- Scene.cpp ------------------------------------------------*- C++ -*-===//
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
#include "Scene.h"

#include "Model.h"

namespace SGEng {

void Scene::initializeUniforms() {
  auto usageScope = shader.scopedUsage();
  cameraPosition.initialize(shader, "camera_pos");
  mvp.initialize(shader, "mvp");
  light.position.initialize(shader, "light.position");
  light.strength.initialize(shader, "light.strength");
  light.diffuseCoefficient.initialize(shader, "light.diffuse_coefficient");
  light.diffuseColor.initialize(shader, "light.diffuse_color");
  light.specularCoefficient.initialize(shader, "light.specular_coefficient");
  light.specularColor.initialize(shader, "light.specular_color");
  light.ambientCoefficient.initialize(shader, "light.ambient_coefficient");
  light.ambientColor.initialize(shader, "light.ambient_color");
}

void Scene::resetUniforms() {
  auto currentCameraPosition = cameraPosition.get();
  auto currentMVP = mvp.get();
  auto currentLightPosition = light.position.get();
  auto currentLightStrength = light.strength.get();
  auto currentLightDiffuseCoefficient = light.diffuseCoefficient.get();
  auto currentLightDiffuseColor = light.diffuseColor.get();
  auto currentLightSpecularCoefficient = light.specularCoefficient.get();
  auto currentLightSpecularColor = light.specularColor.get();
  auto currentLightAmbientCoefficient = light.ambientCoefficient.get();
  auto currentLightAmbientColor = light.ambientColor.get();

  initializeUniforms();
  cameraPosition.set(currentCameraPosition);
  mvp.set(currentMVP);
  light.position.set(currentLightPosition);
  light.strength.set(currentLightStrength);
  light.diffuseCoefficient.set(currentLightDiffuseCoefficient);
  light.diffuseColor.set(currentLightDiffuseColor);
  light.specularCoefficient.set(currentLightSpecularCoefficient);
  light.specularColor.set(currentLightSpecularColor);
  light.ambientCoefficient.set(currentLightAmbientCoefficient);
  light.ambientColor.set(currentLightAmbientColor);

  for (auto &model : models) {
    model.resetUniforms(shader);
  }
}

void Scene::updateMVP(mat4gl modelMatrix) const {
  mvp.set(projectionMatrix * viewMatrix * modelMatrix);
}

} // namespace SGEng
