#include "tb/Entity.h"

namespace tb
{

Entity::Entity()
{
    Thing::setThingType(tb::ThingType::Entity);
}

const std::string& Entity::getName()
{
    return m_name;
}

void Entity::setName(const std::string& name)
{
    m_name = name;
}

}
