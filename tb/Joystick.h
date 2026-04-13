#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"

namespace tb
{

class Joystick
{

public:

    Joystick();
    ~Joystick();

    struct Properties
    {
        std::string Name;
        unsigned int VendorID = 0;
        unsigned int ProductID = 0;

        unsigned int ButtonCount = 0;
    };

    struct State
    {
        bool Button[sf::Joystick::ButtonCount];
        
        float AxisX = 0.0f;
        float AxisY = 0.0f;
        float AxisZ = 0.0f;
        float AxisR = 0.0f;
        float AxisU = 0.0f;
        float AxisV = 0.0f;
        float AxisPOVX = 0.0f;
        float AxisPOVY = 0.0f;
    };

    Properties* getProperties();
    State* getState();

    bool isConnected();
    bool isButtonPressed(unsigned int button);
    sf::Joystick::Identification getIdentification();
    unsigned int getButtonCount();
    float getAxisPosition(sf::Joystick::Axis axis);

    void updateProperties();
    void updateState();

    unsigned int getIndex();
    void setIndex(unsigned int index);

private:

    Properties m_properties;
    State m_state;

    unsigned int m_index = 0;

};

using JoystickList = std::array<tb::Joystick, sf::Joystick::Count>;

}
