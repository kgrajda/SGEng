//===- model_loading.cpp ----------------------------------------*- C++ -*-===//
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
#include "model_loading.h"

#include "Mesh.h"
#include "Model.h"
#include "exceptions.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <span>

namespace SGEng {

Model loadModel(const fs::path &path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    throw ModelLoadingError("Could not load model", path,
                            importer.GetErrorString());
  }

  Model model;
  loadNode(*scene->mRootNode, *scene, model);

  return model;
}

void loadNode(aiNode &node, const aiScene &scene, Model &model) {
  auto meshIds = std::span(node.mMeshes, node.mNumMeshes);
  for (auto meshId : meshIds) {
    auto rawMesh = scene.mMeshes[meshId];
    model.meshes.push_back(loadMesh(*rawMesh, scene));
  }

  auto childrenNodes = std::span(node.mChildren, node.mNumChildren);
  for (auto childNode : childrenNodes) {
    loadNode(*childNode, scene, model);
  }
}

Mesh loadMesh(aiMesh &rawMesh, const aiScene &scene) {
  Mesh mesh;

  auto vertices = std::span(rawMesh.mVertices, rawMesh.mNumVertices);
  auto normals = std::span(rawMesh.mNormals, rawMesh.mNumVertices);
  std::transform(
      vertices.begin(), vertices.end(), normals.begin(),
      std::back_inserter(mesh.vertices),
      [](const auto &rawPosition, const auto &rawNormal) {
        return Vertex{.position = {rawPosition.x, rawPosition.y, rawPosition.z},
                      .normal = {rawNormal.x, rawNormal.y, rawNormal.z}};
      });

  /*for (unsigned int i = 0; i < rawMesh.mNumVertices; i++) {
    auto rawPosition = rawMesh.mVertices[i];
    auto rawNormal = rawMesh.mNormals[i];
    Vertex vertex{.position = {rawPosition.x, rawPosition.y, rawPosition.z},
                  .normal = {rawNormal.x, rawNormal.y, rawNormal.z}};
  }*/

  auto faces = std::span(rawMesh.mFaces, rawMesh.mNumFaces);
  for (auto face : faces) {
    auto indices = std::span(face.mIndices, face.mNumIndices);
    std::transform(indices.begin(), indices.end(),
                   std::back_inserter(mesh.indices),
                   [](auto index) { return index; });
  }

  return mesh;
}

} // namespace SGEng
