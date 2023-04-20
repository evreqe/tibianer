#pragma once

/*
#ifndef TIBIA_CONTAINER_HPP
#define TIBIA_CONTAINER_HPP

#include "tb/Tibia.hpp"
#include "tb/Utility.hpp"
#include "tb/Object.hpp"

namespace tb
{

class Container
{

public:

    bool isFull()
    {
        std::size_t objectsMax = tb::INVENTORY_OBJECTS_MAX;

        if (m_isDepot == true)
        {
            objectsMax = tb::INVENTORY_DEPOT_OBJECTS_MAX;
        }

        if (m_objectList.size() >= objectsMax)
        {
            return true;
        }

        return false;
    }

    tb::Object::List::iterator findObject(int id)
    {
        return std::find_if
        (
            m_objectList.begin(),
            m_objectList.end(),
            [&id](tb::Object::Ptr const& object)
            { 
                return object->getId() == id;
            }
        );
    }

    bool hasObject(int id)
    {
        auto findObjectIt = findObject(id);

        return findObjectIt != m_objectList.end();
    }

    int addObject(tb::Object::Ptr addObject)
    {
        bool foundGroupableObject = false;

        int groupableObjectsIndex = 0;

        std::size_t groupableObjectsSize = 1;

        tb::Object::List::iterator groupableObjectIt;

        if (addObject->getFlags().test(tb::SpriteFlags::groupable))
        {
            for (auto& containerObjectIt = m_objectList.begin(); containerObjectIt != m_objectList.end(); containerObjectIt++)
            {
                if (foundGroupableObject == true)
                {
                    break;
                }

                if (containerObjectIt->get()->getFlags().test(tb::SpriteFlags::groupable))
                {
                    groupableObjectsIndex = 0;

                    for (auto& groupableObjects : tb::groupedObjectsList)
                    {
                        if (foundGroupableObject == true)
                        {
                            break;
                        }

                        for (auto groupableObject : groupableObjects)
                        {
                            if (foundGroupableObject == true)
                            {
                                break;
                            }

                            if (groupableObject == containerObjectIt->get()->getId())
                            {
                                for (auto groupableObject : groupableObjects)
                                {
                                    if (groupableObject == addObject->getId())
                                    {
                                        groupableObjectIt = containerObjectIt;

                                        groupableObjectsSize = groupableObjects.size();

                                        foundGroupableObject = true;
                                        break;
                                    }
                                }
                            }
                        }

                        if (foundGroupableObject == false)
                        {
                            groupableObjectsIndex++;
                        }
                    }
                }
            }
        }

        if (addObject->getFlags().test(tb::SpriteFlags::stackable))
        {
            if (foundGroupableObject == true)
            {
                if ((groupableObjectIt->get()->getCount() + addObject->getCount()) > tb::OBJECT_COUNT_MAX)
                {
                    std::size_t objectsMax = tb::INVENTORY_OBJECTS_MAX;

                    if (m_isDepot == true)
                    {
                        objectsMax = tb::INVENTORY_DEPOT_OBJECTS_MAX;
                    }

                    if ((m_objectList.size() + 1) >= objectsMax)
                    {
                        return tb::ContainerAddObjectResult::objectsMax;
                    }

                    int remainderCount = (groupableObjectIt->get()->getCount() + addObject->getCount()) - tb::OBJECT_COUNT_MAX;

                    groupableObjectIt->get()->setCount(tb::OBJECT_COUNT_MAX);

                    groupableObjectIt->get()->setId
                    (
                        tb::groupedObjectsList
                            .at(groupableObjectsIndex)
                            .at(tb::Utility::getGroupableObjectIndexByCount(groupableObjectIt->get()->getCount(), groupableObjectsSize))
                    );

                    tb::Object::Ptr containerObject = std::make_shared<tb::Object>(*addObject);
                    containerObject->setId
                    (
                        tb::groupedObjectsList
                            .at(groupableObjectsIndex)
                            .at(tb::Utility::getGroupableObjectIndexByCount(remainderCount, groupableObjectsSize))
                    );
                    containerObject->setCount(remainderCount);
                    containerObject->setFlags(groupableObjectIt->get()->getFlags());

                    m_objectList.insert(m_objectList.begin(), containerObject);

                    return tb::ContainerAddObjectResult::success;
                }

                groupableObjectIt->get()->setCount(groupableObjectIt->get()->getCount() + addObject->getCount());

                groupableObjectIt->get()->setId
                (
                    tb::groupedObjectsList
                        .at(groupableObjectsIndex)
                        .at(tb::Utility::getGroupableObjectIndexByCount(groupableObjectIt->get()->getCount(), groupableObjectsSize))
                );

                return tb::ContainerAddObjectResult::success;
            }

            auto findObjectIt = findObject(addObject->getId());

            if (findObjectIt != m_objectList.end())
            {
                if ((findObjectIt->get()->getCount() + addObject->getCount()) > tb::OBJECT_COUNT_MAX)
                {
                    return tb::ContainerAddObjectResult::objectCountMax;
                }

                findObjectIt->get()->setCount(findObjectIt->get()->getCount() + addObject->getCount());

                return tb::ContainerAddObjectResult::success;
            }
        }

        std::size_t objectsMax = tb::INVENTORY_OBJECTS_MAX;

        if (m_isDepot == true)
        {
            objectsMax = tb::INVENTORY_DEPOT_OBJECTS_MAX;
        }

        if (m_objectList.size() == objectsMax)
        {
            return tb::ContainerAddObjectResult::objectsMax;
        }

        m_objectList.insert(m_objectList.begin(), addObject);

        return tb::ContainerAddObjectResult::success;
    }

    void removeObject(int index)
    {
        m_objectList.erase(m_objectList.begin() + index);
    }

    void removeObject(tb::Object::List::iterator objectIt)
    {
        m_objectList.erase(objectIt);
    }

    void removeObject(tb::Object::Ptr object)
    {
        auto objectIt = std::find(m_objectList.begin(), m_objectList.end(), object);

        if (objectIt != m_objectList.end())
        {
            m_objectList.erase(objectIt);
        }
    }

    void sortReverse()
    {
        std::reverse(m_objectList.begin(), m_objectList.end());
    }

    void sortById()
    {
        std::sort(m_objectList.begin(), m_objectList.end(), tb::Object::SortById_t());
    }

    void sortByCount()
    {
        sortById();
        std::stable_sort(m_objectList.begin(), m_objectList.end(), tb::Object::SortByCount_t());
    }

    bool setIsDepot(bool b)
    {
        m_isDepot = b;
    }

    bool isDepot()
    {
        return m_isDepot;
    }

    tb::Object::List* getObjectList()
    {
        return &m_objectList;
    }

private:

    bool m_isDepot;

    tb::Object::List m_objectList;

}; // class Container

} // namespace tb

#endif // TIBIA_CONTAINER_HPP
*/