#pragma once

#include "common.h"

#include "toml.hpp"

namespace tb::LibTOML
{

struct LoadFileResult
{
    bool Success = false;
    std::string Text;
};

LoadFileResult loadFile(toml::table& table, const std::string& fileName);

}
