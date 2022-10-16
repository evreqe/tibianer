#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class SpriteFlags
{

public:

    SpriteFlags();
    ~SpriteFlags();

    size_t getCount();

    void setFlag(tb::SpriteFlag spriteFlag, bool value);
    void flipFlag(tb::SpriteFlag spriteFlag);
    bool hasFlag(tb::SpriteFlag spriteFlag);

private:

    tb::SpriteFlagBitset m_spriteFlagBitset;

};

}
