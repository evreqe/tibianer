#include "common.h"

#include "tb/ResourceLoader.h"

namespace tb
{

ResourceLoader::ResourceLoader()
{
    //
}

ResourceLoader::~ResourceLoader()
{
    //
}

bool ResourceLoader::loadAll()
{
    g_Log.write("Loading textures\n");
    if (loadTextures() == false)
    {
        g_Log.write("ERROR: failed to load textures\n");
        return false;
    }

    g_Log.write("Loading fonts\n");
    if (loadFonts() == false)
    {
        g_Log.write("ERROR: failed to load fonts\n");
        return false;
    }

    g_Log.write("Loading bitmap fonts\n");
    if (loadBitmapFonts() == false)
    {
        g_Log.write("ERROR: failed to load bitmap fonts\n");
        return false;
    }

    g_Log.write("Loading cursors\n");
    if (loadCursors() == false)
    {
        g_Log.write("ERROR: failed to load cursors\n");
        return false;
    }

    g_Log.write("Loading sprites\n");
    if (loadSprites() == false)
    {
        g_Log.write("ERROR: failed to load sprites\n");
        return false;
    }

    g_Log.write("Loading animations\n");
    if (loadAnimations() == false)
    {
        g_Log.write("ERROR: failed to load animations\n");
        return false;
    }

    g_Log.write("Loading texture rects\n");
    if (loadTextureRects() == false)
    {
        g_Log.write("ERROR: failed to load texture rects\n");
        return false;
    }

    return true;
}

bool ResourceLoader::loadTextures()
{
    unsigned int maximumTextureSize = sf::Texture::getMaximumSize();

    if (maximumTextureSize < m_minimumTextureSizeRequiredToRun)
    {
        g_Log.write("ERROR: your computer supports a maximum texture size of {}\n", maximumTextureSize);
        g_Log.write("-----> this game requires at least {} texture size in order to run\n", m_minimumTextureSizeRequiredToRun);
        return false;
    }

    if (g_TextureData.isLoaded() == false)
    {
        g_Log.write("ERROR: texture data is not loaded\n");
        return false;
    }

    tb::TextureData::DataList* textureDataList = g_TextureData.getDataList();

    for (auto& textureData : *textureDataList)
    {
        bool isFound = false;

        for (auto& [textureName, textureObject] : tb::Resources::Textures::NameTable)
        {
            if (textureData.Name == textureName)
            {
                if (textureObject.loadFromFile(textureData.FileName, false, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(textureData.Width, textureData.Height))) == true)
                {
                    // tiled textures
                    if (textureData.Repeated == true)
                    {
                        textureObject.setRepeated(true);
                    }

                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded texture '{}' from file: {}\n", textureData.Name, textureData.FileName);
        }
        else
        {
            g_Log.write("ERROR: failed to load texture '{}' from file: {}\n", textureData.Name, textureData.FileName);
            return false;
        }
    }

    return true;
}

bool ResourceLoader::loadFonts()
{
    if (g_FontData.isLoaded() == false)
    {
        g_Log.write("ERROR: font data is not loaded\n");
        return false;
    }

    tb::FontData::DataList* fontDataList = g_FontData.getDataList();

    for (auto& fontData : *fontDataList)
    {
        bool isFound = false;

        for (auto& [fontName, fontObject] : tb::Resources::Fonts::NameTable)
        {
            if (fontData.Name == fontName)
            {
                if (fontObject.openFromFile(fontData.FileName) == true)
                {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded font '{}' from file: {}\n", fontData.Name, fontData.FileName);
        }
        else
        {
            g_Log.write("ERROR: failed to load font '{}' from file: {}\n", fontData.Name, fontData.FileName);
            return false;
        }
    }

    return true;
}

bool ResourceLoader::loadBitmapFonts()
{
    if (g_BitmapFontData.isLoaded() == false)
    {
        g_Log.write("ERROR: bitmap font data is not loaded\n");
        return false;
    }

    tb::BitmapFontData::DataList* bitmapFontDataList = g_BitmapFontData.getDataList();

    for (auto& bitmapFontData : *bitmapFontDataList)
    {
        bool isFound = false;

        for (auto& [bitmapFontName, bitmapFontObject] : tb::Resources::BitmapFonts::NameTable)
        {
            if (bitmapFontData.Name == bitmapFontName)
            {
                if
                (
                    bitmapFontObject.load
                    (
                        bitmapFontData.FileName,
                        sf::Vector2u(bitmapFontData.GlyphWidth, bitmapFontData.GlyphHeight),
                        bitmapFontData.CharacterSpace,
                        bitmapFontData.CharacterHeight,
                        &bitmapFontData.CharacterWidthList
                    ) == true
                )
                {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded bitmap font '{}' from file: {}\n", bitmapFontData.Name, bitmapFontData.FileName);
        }
        else
        {
            g_Log.write("ERROR: failed to load bitmap font '{}' from file: {}\n", bitmapFontData.Name, bitmapFontData.FileName);
            return false;
        }
    }

    return true;
}

bool ResourceLoader::loadCursors()
{
    if (g_CursorData.isLoaded() == false)
    {
        g_Log.write("ERROR: cursor data is not loaded\n");
        return false;
    }

    // system cursors
    for (auto& [cursorType, cursorObject] : tb::Resources::Cursors::System::TypeTable)
    {
        auto cursorResult = cursorObject.createFromSystem(cursorType);
        if (cursorResult.has_value() == false)
        {
            g_Log.write("ERROR: failed to create system cursors");
            return false;
        }
    }

    tb::CursorData::DataList* cursorDataList = g_CursorData.getDataList();

    // custom cursors
    for (auto& cursorData : *cursorDataList)
    {
        bool isFound = false;

        for (auto& [cursorName, cursorObject] : tb::Resources::Cursors::Custom::NameTable)
        {
            if (cursorData.Name == cursorName)
            {
                const std::uint8_t* cursorPixels = cursorData.Image.getPixelsPtr();

                sf::Vector2u cursorSize = sf::Vector2u(cursorData.Width, cursorData.Height);

                sf::Vector2u cursorHotSpot = sf::Vector2u(cursorData.HotSpotX, cursorData.HotSpotY);

                auto cursorResult = sf::Cursor::createFromPixels(cursorPixels, cursorSize, cursorHotSpot);
                if (cursorResult.has_value() == true)
                {
                    sf::Cursor& customCursor = *cursorResult;
                    cursorObject = std::move(customCursor);
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded cursor '{}' from file: {}\n", cursorData.Name, cursorData.FileName);
        }
        else
        {
            g_Log.write("ERROR: failed to load cursor '{}' from file: {}\n", cursorData.Name, cursorData.FileName);
            return false;
        }
    }

    return true;
}

bool ResourceLoader::loadSprites()
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: sprite data is not loaded\n");
        return false;
    }

    tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

    for (auto& [spriteName, spriteID] : tb::Resources::Sprites::NameTable)
    {
        bool isFound = false;

        for (auto& spriteData : *spriteDataList)
        {
            if (spriteData.Name == spriteName)
            {
                spriteID = spriteData.SpriteID;

                isFound = true;
                break;
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded sprite '{}' to sprite ID: {}\n", spriteName, spriteID);
        }
        else
        {
            g_Log.write("ERROR: failed to load sprite '{}' to sprite ID: {}\n", spriteName, spriteID);
            return false;
        }
    }

    return true;
}

bool ResourceLoader::loadAnimations()
{
    if (g_AnimationData.isLoaded() == false)
    {
        g_Log.write("ERROR: animation data is not loaded\n");
        return false;
    }

    tb::AnimationData::DataList* animationDataList = g_AnimationData.getDataList();

    for (auto& [animationName, animationIndex] : tb::Resources::Animations::NameTable)
    {
        bool isFound = false;

        for (auto& animationData : *animationDataList)
        {
            if (animationData.Name == animationName)
            {
                animationIndex = animationData.Index;

                isFound = true;
                break;
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded animation '{}' to index: {}\n", animationName, animationIndex);
        }
        else
        {
            g_Log.write("ERROR: failed to load animation '{}' to index: {}\n", animationName, animationIndex);
            return false;
        }
    }

    return true;
}

bool ResourceLoader::loadTextureRects()
{
    if (g_TextureRectData.isLoaded() == false)
    {
        g_Log.write("ERROR: texture rect data is not loaded\n");
        return false;
    }

    auto loadTextureRectsFromNameTableList = [](const std::vector<tb::Resources::TextureRects::NameTableType>& nameTableList) -> bool
    {
        for (auto& nameTable : nameTableList)
        {
            tb::TextureRectData::DataList* textureRectDataList = g_TextureRectData.getDataList();

            for (auto& [textureRectName, textureRect] : nameTable)
            {
                bool isFound = false;

                for (auto& textureRectData : *textureRectDataList)
                {
                    if (textureRectData.Name == textureRectName)
                    {
                        textureRect.position.x    = textureRectData.X;
                        textureRect.position.y    = textureRectData.Y;
                        textureRect.size.x        = textureRectData.Width;
                        textureRect.size.y        = textureRectData.Height;

                        isFound = true;
                        break;
                    }
                }

                if (isFound == true)
                {
                    g_Log.write("Loaded texture rect for '{}'\n", textureRectName);
                }
                else
                {
                    g_Log.write("ERROR: failed to load texture rect for '{}'\n", textureRectName);
                    return false;
                }
            }
        }

        return true;
    };

    bool loadedTextureRects = loadTextureRectsFromNameTableList(tb::Resources::TextureRects::NameTableList);
    if (loadedTextureRects == false)
    {
        return false;
    }

    return true;
}

}
