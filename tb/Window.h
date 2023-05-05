#pragma once

#include "common.h"

namespace tb
{

class Window
{

public:

    Window();
    ~Window();

    bool* getIsVisible();
    void setIsVisible(bool b);
    void toggleIsVisible();

    void center();
    void centerOnAppearing();
    void centerOnFirstUseEver();

private:

    bool m_isVisible = false;

};

}
