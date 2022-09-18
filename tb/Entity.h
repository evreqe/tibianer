#pragma once

#include <cstdint>

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Thing.h"

namespace tb
{

class Entity : public tb::Thing
{

public:

    typedef std::shared_ptr<tb::Entity> Ptr;
    typedef std::vector<tb::Entity::Ptr> List;

    Entity();

    const std::string& getName();
    void setName(const std::string& name);

private:

    std::string m_name = std::string();
};

}
