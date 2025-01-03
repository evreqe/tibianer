#pragma once

// modules do not work LOL
//import std;

// SFML exception bug
#pragma warning(disable: 4275)

#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <stdfloat>

#include <algorithm>
#include <array>
#include <bitset>
#include <charconv>
#include <chrono>
#include <concepts>
#include <execution>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <future>
#include <list>
#include <map>
#include <memory>
#include <numbers>
#include <numeric>
#include <optional>
#include <random>
#include <ranges>
#include <source_location>
#include <span>
#include <string>
#include <string_view>
#include <sstream>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#undef FMT_UNICODE
#define FMT_UNICODE 0
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"
#include "fmt/compile.h"
#include "fmt/std.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

#include "imgui-SFML.h"

#include "toml.hpp"

#include "magic_enum.hpp"
using namespace magic_enum::bitwise_operators;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
