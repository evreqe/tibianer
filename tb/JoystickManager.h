#pragma once

#include "common.h"

#include "tb/Log.h"

#include "tb/Joystick.h"

namespace tb
{

class JoystickManager
{

public:

    JoystickManager();
    ~JoystickManager();

    static JoystickManager& getInstance()
    {
        static JoystickManager instance;
        return instance;
    }

private:

    JoystickManager(const JoystickManager&) = delete;
    JoystickManager(JoystickManager&&) = delete;
    JoystickManager& operator=(const JoystickManager&) = delete;
    JoystickManager& operator=(JoystickManager&&) = delete;

public:

    unsigned int getJoystickIndex();
    void setJoystickIndex(unsigned int index);
    tb::Joystick* getJoystick();
    tb::JoystickList* getJoystickList();
    void updateJoystickIndices();
    void updateJoystickProperties();
    void updateJoystickStates();
    void handleEventJoystickConnected(const sf::Event::JoystickConnected* eventJoystickConnected);
    void handleEventJoystickDisconnected(const sf::Event::JoystickDisconnected* eventJoystickDisconnected);

private:

    unsigned int m_joystickIndex = 0;
    tb::JoystickList m_joystickList;

};

}

namespace
{
    inline tb::JoystickManager& g_JoystickManager = tb::JoystickManager::getInstance();
}
