#pragma once

#include <string>
#include <string_view>
#include <format>

namespace tb::LibFMT
{

template<typename... Args>
static std::string DynamicFormat(std::string_view fmt, Args&&... args)
{
    return std::vformat(fmt, std::make_format_args(args...));
}

}
