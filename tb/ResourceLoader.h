#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Resources.h"
#include "tb/Log.h"

#include "tb/TextureData.h"
#include "tb/FontData.h"
#include "tb/BitmapFontData.h"
#include "tb/CursorData.h"
#include "tb/SpriteData.h"
#include "tb/AnimationData.h"
#include "tb/TextureRectData.h"

namespace tb
{

class ResourceLoader
{

public:

    ResourceLoader();
    ~ResourceLoader();

    static ResourceLoader& getInstance()
    {
        static ResourceLoader instance;
        return instance;
    }

private:

    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader(ResourceLoader&&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;
    ResourceLoader& operator=(ResourceLoader&&) = delete;

public:

    bool loadAll();

    bool loadTextures();
    bool loadFonts();
    bool loadBitmapFonts();
    bool loadCursors();
    bool loadSprites();
    bool loadAnimations();
    bool loadTextureRects();

private:

    const unsigned int m_minimumTextureSizeRequiredToRun = 2048;

};

}

namespace
{
    inline tb::ResourceLoader& g_ResourceLoader = tb::ResourceLoader::getInstance();
}
