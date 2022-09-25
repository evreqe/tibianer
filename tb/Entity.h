#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Thing.h"

namespace tb
{

class Entity : public tb::Thing
{

public:

    Entity();
    ~Entity();

    typedef std::shared_ptr<tb::Entity> Ptr;
    typedef std::vector<tb::Entity::Ptr> List;

    const std::string& getName();
    void setName(const std::string& name);

private:

    std::string m_name = std::string();
};

}
