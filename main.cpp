#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cmath>

#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <ranges>
#include <source_location>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/replace_if.hpp>
#include <boost/range/algorithm/remove_if.hpp>

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/ini_parser.hpp>

#include "boost_zlib.hpp"
#include "boost_base64.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "pugixml.hpp"

#include "toml++/toml.h"

#include <windows.h>

#include "resource.h"

#include "utility.h"

#include "tb/Utility.h"
#include "tb/Game.h"

tb::Game game;

int main()
{
    game.run();
}
