#pragma once

#include "common.h"

#include "toml.hpp"

namespace tb
{

namespace LibToml
{

struct LoadFileResult
{
    bool Success = false;
    std::string Text;
};

LoadFileResult loadFile(toml::table& table, const std::string& fileName);

}

}
