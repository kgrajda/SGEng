//===- Renderer.cpp ---------------------------------------------*- C++ -*-===//
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
#include "Renderer.h"

#include "Config.h"
#include "Mesh.h"
#include "Model.h"
#include "Scene.h"
#include "constants.h"
#include "exceptions.h"
#include <GLFW/glfw3.h>
#include <plog/Log.h>

namespace SGEng {

Renderer::Renderer(Context &ctx, Window &window) : IRenderer(ctx, window) {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Renderer constructor...";
  if (!ctx.isGLInitialized)
    ctx.initializeGL();
}

Renderer::Renderer(const Renderer &renderer)
    : IRenderer(ctx, window), enabledFaceCulling{renderer.enabledFaceCulling} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Renderer copy constructor...";
}

Renderer &Renderer::operator=(const Renderer &renderer) {
  PLOGV_IF(LOG_ASSIGNMENTS) << "Renderer copy assignment...";
  ctx = renderer.ctx;
  window = renderer.window;
  enabledFaceCulling = renderer.enabledFaceCulling;
  return *this;
}

Renderer::Renderer(Renderer &&renderer) noexcept
    : IRenderer(ctx, window), enabledFaceCulling{renderer.enabledFaceCulling} {
  PLOGV_IF(LOG_CONSTRUCTORS) << "Renderer move constructor...";
  renderer.enabledFaceCulling = false;
}

Renderer &Renderer::operator=(Renderer &&renderer) noexcept {
  PLOGV_IF(LOG_ASSIGNMENTS) << "Renderer move assignment...";
  if (this != &renderer) {
    std::swap(this->ctx, renderer.ctx);
    std::swap(this->window, renderer.window);
    enabledFaceCulling = renderer.enabledFaceCulling;
    renderer.enabledFaceCulling = false;
  }
  return *this;
}

Renderer::~Renderer() { PLOGV << "Renderer destructor..."; }

void Renderer::drawElements(const Shader &shader, const VAO &vao,
                            GLsizei count) {
  vao.bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
  PLOGV_IF(LOG_DRAW) << "Elements drawn";
  vao.unbind();
}

void Renderer::update() { IRenderer::update(); }

void Renderer::render(const Scene &scene) {
  auto usageScope = scene.shader.scopedUsage();

  scene.cameraPosition.use();
  scene.light.strength.use();
  scene.light.position.use();
  scene.light.diffuseCoefficient.use();
  scene.light.ambientColor.use();
  scene.light.specularCoefficient.use();
  scene.light.specularColor.use();
  scene.light.ambientCoefficient.use();
  scene.light.ambientColor.use();

  for (auto &model : scene.models) {
    model.modelMatrix.use();
    model.material.color.use();
    model.material.shininess.use();
    scene.updateMVP(model.modelMatrix.get());
    scene.mvp.use();

    for (auto &mesh : model.meshes) {
      if (enabledFaceCulling != mesh.enableFaceCulling) {
        if (mesh.enableFaceCulling)
          glEnable(GL_CULL_FACE);
        else
          glDisable(GL_CULL_FACE);
        enabledFaceCulling = mesh.enableFaceCulling;
      }
      drawElements(scene.shader, mesh.vao,
                   static_cast<GLsizei>(mesh.indices.size()));
    }
  }
}

} // namespace SGEng