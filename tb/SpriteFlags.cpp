#include "tb/SpriteFlags.h"

namespace tb
{

SpriteFlags::SpriteFlags()
{
    //
}

SpriteFlags::~SpriteFlags()
{
    //
}


size_t SpriteFlags::getCount()
{
    return m_spriteFlagBitset.count();
}

void SpriteFlags::setFlag(tb::SpriteFlag spriteFlag, bool value)
{
    m_spriteFlagBitset.set(magic_enum::enum_integer(spriteFlag), value);
}

void SpriteFlags::flipFlag(tb::SpriteFlag spriteFlag)
{
    m_spriteFlagBitset.flip(magic_enum::enum_integer(spriteFlag));
}

bool SpriteFlags::hasFlag(tb::SpriteFlag spriteFlag)
{
    return m_spriteFlagBitset.test(magic_enum::enum_integer(spriteFlag));
}

}
