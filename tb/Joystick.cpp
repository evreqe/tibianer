#include "tb/Joystick.h"

namespace tb
{

Joystick::Joystick()
{
    //
}

Joystick::~Joystick()
{
    //
}

bool Joystick::isConnected()
{
    return sf::Joystick::isConnected(m_index);
}

bool Joystick::isButtonPressed(unsigned int button)
{
    return sf::Joystick::isButtonPressed(m_index, button);
}

sf::Joystick::Identification Joystick::getIdentification()
{
    return sf::Joystick::getIdentification(m_index);
}

unsigned int Joystick::getButtonCount()
{
    return sf::Joystick::getButtonCount(m_index);
}

float Joystick::getAxisPosition(sf::Joystick::Axis axis)
{
    return sf::Joystick::getAxisPosition(m_index, axis);
}

void Joystick::updateProperties()
{
    sf::Joystick::Identification identification = getIdentification();

    m_properties.Name = identification.name.toAnsiString();
    m_properties.ProductID = identification.productId;
    m_properties.VendorID = identification.vendorId;

    m_properties.ButtonCount = getButtonCount();
}

void Joystick::updateState()
{
    for (unsigned int i = 0; i < sf::Joystick::ButtonCount; i++)
    {
        m_state.Button[i] = isButtonPressed(i);
    }

    m_state.AxisX    = getAxisPosition(sf::Joystick::Axis::X);
    m_state.AxisY    = getAxisPosition(sf::Joystick::Axis::Y);
    m_state.AxisZ    = getAxisPosition(sf::Joystick::Axis::Z);
    m_state.AxisR    = getAxisPosition(sf::Joystick::Axis::R);
    m_state.AxisU    = getAxisPosition(sf::Joystick::Axis::U);
    m_state.AxisV    = getAxisPosition(sf::Joystick::Axis::V);
    m_state.AxisPOVX = getAxisPosition(sf::Joystick::Axis::PovX);
    m_state.AxisPOVY = getAxisPosition(sf::Joystick::Axis::PovY);
}

Joystick::Properties_t* Joystick::getProperties()
{
    return &m_properties;
}

Joystick::State_t* Joystick::getState()
{
    return &m_state;
}

unsigned int Joystick::getIndex()
{
    return m_index;
}

void Joystick::setIndex(unsigned int index)
{
    m_index = index;
}

}
