#pragma once

#include "common.h"

namespace tb
{

class IMGUIWindow
{

public:

    IMGUIWindow();
    ~IMGUIWindow();

    bool* isVisible();
    void setVisible(bool b);
    void toggleVisible();

    void center();
    void centerOnAppearing();
    void centerOnFirstUseEver();

private:

    bool m_isVisible = false;

};

}
