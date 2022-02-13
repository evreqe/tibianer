#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"
#include "tb/Thing.hpp"

namespace tb
{

class Entity : public tb::Thing
{

public:

    typedef std::shared_ptr<tb::Entity> Ptr;
    typedef std::vector<tb::Entity::Ptr> List;

    Entity()
    {
        setIsEntity(true);
    }

    const std::string& getName() const
    {
        return m_name;
    }

    void setName(const std::string& name)
    {
        m_name = name;
    }

private:

    std::string m_name = std::string();
};

}
