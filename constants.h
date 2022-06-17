//===- Constants.h ----------------------------------------------*- C++ -*-===//
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
/// Global constants used throughout the project.
///
//===----------------------------------------------------------------------===//
#pragma once

#include "Color.h"
#include <filesystem>
#include <glm/vec4.hpp>
#include <plog/Severity.h>
#include <string_view>

namespace SGEng {

namespace fs = std::filesystem;

const fs::path defaultConfigDirectory = fs::path("config/");
const fs::path defaultConfigPath = defaultConfigDirectory / "config.toml";

const fs::path defaultShaderDirectory = fs::path("shaders/");
const fs::path defaultBasicVertexShaderPath =
    defaultShaderDirectory / "basic" / "basic.vert";
const fs::path defaultBasicFragmentShaderPath =
    defaultShaderDirectory / "basic" / "basic.frag";
const fs::path defaultLogPath = fs::path("log.txt");
const fs::path defaultResourcesDirectory = fs::path("resources/");

constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;

constexpr bool DISABLE_SWAP_INTERVAL{true};

#ifdef _DEBUG
constexpr plog::Severity defaultLogLevel = plog::debug;
constexpr bool defaultShowFPS{true};
#else
constexpr plog::Severity defaultLogLevel = plog::info;
constexpr bool defaultShowFPS{false};
#endif
constexpr std::string_view defaultWindowTitle = "SGEng";
constexpr int defaultWindowWidth{800};
constexpr int defaultWindowHeight{800};
constexpr int defaultMinWindowWidth{640};
constexpr int defaultMinWindowHeight{480};
constexpr Color defaultBackgroundColor(Color::MaterialDark::Background);
constexpr bool defaultStartWindowMaximized{false};

constexpr bool LOG_FILE_OPERATIONS{false};
constexpr bool LOG_DRAW{false};
constexpr bool LOG_KEY_PRESS{false};
constexpr bool LOG_WINDOW_REFRESH{false};
constexpr bool LOG_WINDOW_RESIZE{false};
constexpr bool LOG_WINDOW_TITLE_CHANGE{false};
constexpr bool LOG_WINDOW_BACKGROUND_COLOR_CHANGE{false};
constexpr bool LOG_CONSTRUCTORS{false};
constexpr bool LOG_ASSIGNMENTS{false};
constexpr bool LOG_DESTRUCTORS{false};
constexpr bool LOG_BUFFER_LINKING{false};
constexpr bool LOG_BUFFERS{false};
constexpr bool LOG_VAO{false};
constexpr bool LOG_SHADERS{false};
constexpr bool LOG_SHADERS_RELOAD{true};
constexpr bool LOG_FPS{true};

static_assert((OPENGL_MAJOR > 4) ||
                  (OPENGL_MAJOR == 4 &&
                   OPENGL_MINOR >=
                       5), // NOLINT(cppcoreguidelines-avoid-magic-numbers)
              "OpenGL version unsupported");

} // namespace SGEng