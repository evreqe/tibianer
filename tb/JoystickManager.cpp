#include "common.h"

#include "tb/JoystickManager.h"

namespace tb
{

JoystickManager::JoystickManager()
{
    //
}

JoystickManager::~JoystickManager()
{
    //
}

unsigned int JoystickManager::getJoystickIndex()
{
    return m_joystickIndex;
}

void JoystickManager::setJoystickIndex(unsigned int index)
{
    m_joystickIndex = index;
}

tb::Joystick* JoystickManager::getJoystick()
{
    return &m_joystickList[m_joystickIndex];
}

tb::JoystickList* JoystickManager::getJoystickList()
{
    return &m_joystickList;
}

void JoystickManager::updateJoystickIndices()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; i++)
    {
        m_joystickList[i].setIndex(i);
    }
}

void JoystickManager::updateJoystickProperties()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; i++)
    {
        if (sf::Joystick::isConnected(i) == true)
        {
            m_joystickList[i].updateProperties();
        }
    }
}

void JoystickManager::updateJoystickStates()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; i++)
    {
        m_joystickList[i].updateState();
    }
}

void JoystickManager::handleEventJoystickConnected(const sf::Event::JoystickConnected* eventJoystickConnected)
{
    m_joystickIndex = eventJoystickConnected->joystickId;

    g_Log.write("Joystick Connected Index: {}\n", m_joystickIndex);

    updateJoystickProperties();

    tb::JoystickList* joystickList = g_JoystickManager.getJoystickList();

    tb::Joystick::Properties* joystickProperties = m_joystickList.at(m_joystickIndex).getProperties();

    g_Log.write("--> Name: {}\n", joystickProperties->Name);
    g_Log.write("--> Product ID: {}\n", joystickProperties->ProductID);
    g_Log.write("--> Vendor ID: {}\n", joystickProperties->VendorID);
    g_Log.write("--> Button Count: {}\n", joystickProperties->ButtonCount);
}

void JoystickManager::handleEventJoystickDisconnected(const sf::Event::JoystickDisconnected* eventJoystickDisconnected)
{
    unsigned int joystickIndex = eventJoystickDisconnected->joystickId;

    g_Log.write("Joystick Disconnected Index: {}\n", joystickIndex);

    updateJoystickProperties();

    tb::Joystick::Properties* joystickProperties = m_joystickList.at(joystickIndex).getProperties();

    g_Log.write("--> Name: {}\n", joystickProperties->Name);
    g_Log.write("--> Product ID: {}\n", joystickProperties->ProductID);
    g_Log.write("--> Vendor ID: {}\n", joystickProperties->VendorID);
    g_Log.write("--> Button Count: {}\n", joystickProperties->ButtonCount);
}

}