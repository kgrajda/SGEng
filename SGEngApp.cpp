//===- SGEngApp.cpp ---------------------------------------------*- C++ -*-===//
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
#include "SGEngApp.h"

#include "Mesh.h"
#include "Model.h"
#include "examples/cubes.h"
#include "exceptions.h"
#include "model_loading.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <plog/Log.h>

namespace SGEng {

constexpr glm::vec3 cameraTarget = {0.f, 0.f, 0.f};
constexpr glm::vec3 up = {0.f, 1.f, 0.f};
constexpr auto radius = 2.f;
constexpr float fov = 45.f;
constexpr float aspect = 800.0f / 600.0f;
constexpr float near = 0.1f;
constexpr float far = 100.f;

constexpr glm::vec3 lightPosition = {-2.f, 3.f, -1.f};
constexpr float lightStrength = 5.f;
constexpr float lightDiffuseCoefficient = 1.f;
constexpr glm::vec3 lightDiffuseColor = {1.f, 1.f, 1.f};
constexpr float lightSpecularCoefficient = 1.f;
constexpr glm::vec3 lightSpecularColor = {1.f, 1.f, 1.f};
constexpr float lightAmbientCoefficient = 1.f;
constexpr glm::vec3 lightAmbientColor = {0.1f, 0.1f, 0.15f};

SGEngApp::SGEngApp(Context &ctx)
    : App(ctx),
      keyInput(ctx, {GLFW_KEY_ESCAPE, GLFW_KEY_SPACE, GLFW_KEY_W, GLFW_KEY_A,
                     GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_UP, GLFW_KEY_DOWN}),
      mouseInput(ctx, {GLFW_MOUSE_BUTTON_LEFT}) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "SGEngApp constructor...";
}

bool SGEngApp::onStartup() {
  PLOGV << "SGEngApp startup...";

  scene.shader.tryInitialize(*ctx.get().fileManager,
                             defaultBasicVertexShaderPath,
                             defaultBasicFragmentShaderPath);

  auto usageScope = scene.shader.scopedUsage();
  initializeUniforms();
  /*addExampleCubeUnoptimized();*/
  addTeapot();
  /*addSphere();*/

  return true;
}

bool SGEngApp::update(double ts, double td) {
  constexpr double interval = 5.0;
  if (ts - lastPrintTs > interval) {
    PLOGD << std::to_string(static_cast<int>(interval)) << " seconds passed";
    lastPrintTs += interval;
  }

  if (keyInput.isKeyDown(GLFW_KEY_ESCAPE)) {
    window.close();
    return false;
  }

  if (keyInput.isKeyClicked(GLFW_KEY_SPACE)) {
    if (scene.shader.isInitialized())
      scene.shader.tryReload(*ctx.get().fileManager);
    else
      scene.shader.tryReload(*ctx.get().fileManager,
                             defaultBasicVertexShaderPath,
                             defaultBasicFragmentShaderPath);
    resetUniforms();
  }

  if (mouseInput.isLeftButtonClicked()) {
    PLOGD << "Click";
  }

  auto usageScope = scene.shader.scopedUsage();

  glm::vec3 cameraDiff{0.f};
  constexpr float cameraMoveSpeed = 0.75f;
  constexpr float cameraRotationSpeed = 2.f;
  if (keyInput.isKeyDown(GLFW_KEY_W))
    cameraDiff -=
        cameraMoveSpeed * static_cast<float>(td) * scene.cameraPosition.get();
  if (keyInput.isKeyDown(GLFW_KEY_S))
    cameraDiff +=
        cameraMoveSpeed * static_cast<float>(td) * scene.cameraPosition.get();
  if (keyInput.isKeyDown(GLFW_KEY_A))
    cameraDiff += glm::normalize(glm::cross(scene.cameraPosition.get(), up)) *
                  cameraRotationSpeed * static_cast<float>(td);
  if (keyInput.isKeyDown(GLFW_KEY_D))
    cameraDiff -= glm::normalize(glm::cross(scene.cameraPosition.get(), up)) *
                  cameraRotationSpeed * static_cast<float>(td);
  scene.cameraPosition.set(scene.cameraPosition.get() + cameraDiff);

  if (scene.light.strength.get() >= 1.f && keyInput.isKeyClicked(GLFW_KEY_DOWN))
    scene.light.strength.set(scene.light.strength.get() - 1.f);
  if (keyInput.isKeyClicked(GLFW_KEY_UP))
    scene.light.strength.set(scene.light.strength.get() + 1.f);

  scene.viewMatrix = glm::lookAt(scene.cameraPosition.get(), cameraTarget, up);

  return true;
}

void SGEngApp::draw() { window.draw(scene); }

void SGEngApp::onDestroy() {}

void SGEngApp::initializeUniforms() {
  auto usageScope = scene.shader.scopedUsage();
  scene.initializeUniforms();
  scene.cameraPosition.set({0.f, 1.f, -radius});
  scene.light.position.set(lightPosition);
  scene.light.strength.set(lightStrength);
  scene.light.diffuseCoefficient.set(lightDiffuseCoefficient);
  scene.light.diffuseColor.set(lightDiffuseColor);
  scene.light.specularCoefficient.set(lightSpecularCoefficient);
  scene.light.specularColor.set(lightSpecularColor);
  scene.light.ambientCoefficient.set(lightAmbientCoefficient);
  scene.light.ambientColor.set(lightAmbientColor);
  scene.projectionMatrix = glm::perspective(fov, aspect, near, far);
  scene.viewMatrix = glm::lookAt(scene.cameraPosition.get(), cameraTarget, up);
}

void SGEngApp::addGeneratedCube() {
  constexpr Color objColor(Color::BasicColor::White);
  constexpr unsigned int shininess = 64;
  Mesh mesh = generateCube();
  mesh.initialize();

  Model model;
  model.meshes.push_back(std::move(mesh));
  auto usageScope = scene.shader.scopedUsage();
  model.initializeUniforms(scene.shader);
  model.material.color.set(objColor.vec3f());
  model.material.shininess.set(shininess);
  model.updateModelMatrix();

  scene.models.push_back(std::move(model));
}

void SGEngApp::addGeneratedOptimizedCube() {
  constexpr Color objColor(Color::BasicColor::White);
  constexpr unsigned int shininess = 64;
  Mesh mesh = generateOptimizedCube();
  mesh.initialize();

  Model model;
  model.meshes.push_back(std::move(mesh));
  auto usageScope = scene.shader.scopedUsage();
  model.initializeUniforms(scene.shader);
  model.material.color.set(objColor.vec3f());
  model.material.shininess.set(shininess);
  model.updateModelMatrix();

  scene.models.push_back(std::move(model));
}

void SGEngApp::addTeapot() {
  constexpr Color objColor(Color::BasicColor::White);
  constexpr unsigned int shininess = 64;
  constexpr vec3gl scale = {0.05f, 0.05f, 0.05f};
  Model model = loadModel(ctx.get().cfg.resourcesDirectory / "teapot.obj");
  for (auto &mesh : model.meshes) {
    mesh.enableFaceCulling = true;
    mesh.initialize();
  }
  auto usageScope = scene.shader.scopedUsage();
  model.initializeUniforms(scene.shader);
  model.material.color.set(objColor.vec3f());
  model.material.shininess.set(shininess);
  model.scale = scale;
  model.updateModelMatrix();

  scene.models.push_back(std::move(model));
}

void SGEngApp::addSphere() {
  constexpr Color objColor(Color::BasicColor::White);
  constexpr unsigned int shininess = 64;
  Model model = loadModel(ctx.get().cfg.resourcesDirectory / "sphere.obj");
  for (auto &mesh : model.meshes) {
    mesh.enableFaceCulling = true;
    mesh.initialize();
  }
  auto usageScope = scene.shader.scopedUsage();
  model.initializeUniforms(scene.shader);
  model.material.color.set(objColor.vec3f());
  model.material.shininess.set(shininess);
  model.updateModelMatrix();

  scene.models.push_back(std::move(model));
}

void SGEngApp::resetUniforms() { scene.resetUniforms(); }

} // namespace SGEng