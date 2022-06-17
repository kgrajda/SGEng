//===- FileManager.cpp ------------------------------------------*- C++ -*-===//
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
#include "FileManager.h"

#include "Config.h"
#include "config_parsing.h"
#include "exceptions.h"
#include <fstream>
#include <plog/Log.h>

namespace SGEng {

using namespace std::string_literals;

std::string FileManager::loadTextFile(const fs::path &path) {
  PLOGV_IF(LOG_FILE_OPERATIONS) << "Loading contents of " << path;
  std::ifstream fin(path);
  if (!fin.is_open()) {
    throw FileError{"File could not be opened", path};
  }

  std::string content;
  return content.assign((std::istreambuf_iterator<char>(fin)),
                        (std::istreambuf_iterator<char>()));
}

Config FileManager::loadConfig(const fs::path &configPath) {
  PLOGV_IF(LOG_FILE_OPERATIONS) << "Loading config...";

  if (!fs::exists(configPath))
    throw FileDoesNotExistError("Config file not found", configPath);

  toml::table tbl;
  try {
    tbl = toml::parse_file(configPath.string());
  } catch (const toml::parse_error &err) {
    throw ConfigParseError("Config parsing failed: "s + err.what(), configPath);
  }

  Config cfg = parseConfig(tbl);

  PLOGV_IF(LOG_FILE_OPERATIONS) << "Config loaded";
  PLOGI << "Log level: " << cfg.logLevel;

  return cfg;
}

} // namespace SGEng
