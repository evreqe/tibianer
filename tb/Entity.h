#pragma once

#include "common.h"

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

    using Ptr = std::shared_ptr<tb::Entity>;
    using List = std::vector<tb::Entity::Ptr>;

    const std::string& getName();
    void setName(const std::string& name);

private:

    std::string m_name = std::string();
};

}
