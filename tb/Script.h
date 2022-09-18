#ifndef TIBIA_SCRIPT_HPP
#define TIBIA_SCRIPT_HPP

#include <SFML/System.hpp>

#include "lua.hpp"

#include "tibia/Tibia.hpp"
#include "tibia/Utility.hpp"

namespace tibia
{

class Script
{

public:

    bool parseText(std::string text)
    {
        if (text.size() == 0)
        {
            return false;
        }

        std::vector<std::string> tokens;
        boost::split(tokens, text, boost::is_any_of(";"));

        if (tokens.size() == 0)
        {
            return false;
        }

        m_filename = tokens.at(0);

        if (tokens.size() > 1)
        {
            for (std::size_t i = 1; i < tokens.size(); i++)
            {
                if (tokens.at(i) == "objects_only")
                {
                    m_flags.set(tibia::ScriptFlags::objectsOnly);
                }
                else if (tokens.at(i) == "creatures_only")
                {
                    m_flags.set(tibia::ScriptFlags::creaturesOnly);
                }
                else if (tokens.at(i) == "player_only")
                {
                    m_flags.set(tibia::ScriptFlags::playerOnly);
                }
                else if (tokens.at(i) == "once_only")
                {
                    m_flags.set(tibia::ScriptFlags::onceOnly);
                }
            }
        }

        return true;
    }

    bool isDone()
    {
        return m_isDone;
    }

    void setIsDone(bool b)
    {
        m_isDone = b;
    }

    std::string getFilename()
    {
        return m_filename;
    }

    void setFilename(const std::string& filename)
    {
        m_filename = filename;
    }

    tibia::ScriptFlags_t getFlags()
    {
        return m_flags;
    }

    void setFlags(tibia::ScriptFlags_t flags)
    {
        m_flags = flags;
    }

    sf::Clock* getClock()
    {
        return &m_clock;
    }

    float getTime()
    {
        return m_time;
    }

    void setTime(float time)
    {
        m_time = time;
    }

private:

    bool m_isDone = false;

    std::string m_filename;

    tibia::ScriptFlags_t m_flags;

    sf::Clock m_clock;

    float m_time = 0.0f;

}; // class Script

} // namespace tibia

#endif // TIBIA_SCRIPT_HPP
