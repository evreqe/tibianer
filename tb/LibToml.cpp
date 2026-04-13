#include "tb/LibTOML.h"

namespace tb::LibTOML
{

LoadFileResult loadFile(toml::table& table, const std::string& fileName)
{
    LoadFileResult result;

    if (std::filesystem::exists(fileName) == false)
    {
        result.Text = std::format("ERROR: file does not exist: {}\n", fileName);
        result.Success = false;
        return result;
    }

    table.clear();

    try
    {
        table = toml::parse_file(fileName);
    }
    catch (const toml::parse_error& parseError)
    {
        result.Text = std::format("ERROR: failed to load TOML data from file: {}\nDescription: {}\nLine: {}\nColumn: {}\n", fileName, parseError.description(), parseError.source().begin.line, parseError.source().begin.column);
        result.Success = false;
        return result;
    }

    result.Text = std::format("Loaded TOML data from file: {}\n", fileName);
    result.Success = true;
    return result;
}

}
