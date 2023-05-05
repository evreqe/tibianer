#include "tb/Light.h"

/*
        m_img = tb::Textures::InGame.copyToImage();

        float levels = 3.0f;

        float sr, sg, sb;
        sf::Uint8 dr, dg, db;

        for (unsigned int i = 0; i < m_img.getSize().x; ++i)
        {
            for (unsigned int j = 0; j < m_img.getSize().y; ++j)
            {
                auto pxl = m_img.getPixel(i, j);

                pxl.r *= 0.75f;
                pxl.g *= 0.75f;
                pxl.b *= 0.75f;

                sr = (float)(pxl.r) / 255.0f;
                sg = (float)(pxl.g) / 255.0f;
                sb = (float)(pxl.b) / 255.0f;

                dr = 255 * std::roundf(sr * levels) / levels;
                dg = 255 * std::roundf(sg * levels) / levels;
                db = 255 * std::roundf(sb * levels) / levels;

                m_img.setPixel(i, j, sf::Color(dr, dg, db));
            }
        }

        m_tex.loadFromImage(m_img);

        sf::Sprite spr;
        spr.setTexture(m_tex);

        m_renderWindow.draw(spr);

        tb::Sprite spr2;
        spr2.setID(4);

        m_renderWindow.draw(spr2);

        return;
*/

/*
    sf::Sprite sprInGame2;
    sprInGame2.setTexture(tb::Textures::InGame2);

    m_renderWindow.draw(sprInGame2);

    sf::RenderTexture rt;
    rt.create(416, 288);
    rt.clear(sf::Color::Transparent);

    sf::Sprite sprLight;
    sprLight.setTexture(tb::Textures::Light);
    sprLight.setPosition(128, 128);

    rt.draw(sprLight, sf::BlendAdd);

    sprLight.setPosition(0, 0);

    rt.draw(sprLight, sf::BlendAdd);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(416.0f, 288.0f));
    rect.setFillColor(sf::Color(255, 255, 255, 64));

    rt.draw(rect, sf::BlendAdd);

    rt.display();

    sf::Sprite sprRt;
    sprRt.setTexture(rt.getTexture());

    sf::BlendMode linearBurn = sf::BlendMultiply;
    //linearBurn.colorEquation = sf::BlendMode::Equation::Add;
    //linearBurn.alphaEquation = sf::BlendMode::Equation::Add;
    //linearBurn.colorSrcFactor = sf::BlendMode::Factor::One;
    //linearBurn.colorDstFactor = sf::BlendMode::Factor::SrcColor;
    //linearBurn.alphaSrcFactor = sf::BlendMode::Factor::One;
    //linearBurn.alphaDstFactor = sf::BlendMode::Factor::SrcColor;

    static uint32_t colorEquation = 2; // sf::BlendMode::Equation::Add;
    static uint32_t alphaEquation = 2; // sf::BlendMode::Equation::Add;
    static uint32_t colorSrcFactor = 3; // sf::BlendMode::Factor::One;
    static uint32_t colorDstFactor = 2; // sf::BlendMode::Factor::SrcColor;
    static uint32_t alphaSrcFactor = 8; // sf::BlendMode::Factor::One;
    static uint32_t alphaDstFactor = 8; // sf::BlendMode::Factor::SrcColor;

    bool isVisible = true;
    ImGui::Begin("Blend Mode##BlendModeWindow", &isVisible);

    if (ImGui::Button("Random##BlendModeRandom"))
    {
        colorEquation = tb::Utility::getRandomNumber(0, 2);
        alphaEquation = tb::Utility::getRandomNumber(0, 2);

        colorSrcFactor = tb::Utility::getRandomNumber(0, 9);
        colorDstFactor = tb::Utility::getRandomNumber(0, 9);
        alphaSrcFactor = tb::Utility::getRandomNumber(0, 9);
        alphaDstFactor = tb::Utility::getRandomNumber(0, 9);
    }

    ImGui::Separator();

    ImGui::TextUnformatted("colorEquation: %d", colorEquation);
    ImGui::TextUnformatted("alphaEquation: %d", alphaEquation);
    ImGui::TextUnformatted("colorSrcFactor: %d", colorSrcFactor);
    ImGui::TextUnformatted("colorDstFactor: %d", colorDstFactor);
    ImGui::TextUnformatted("alphaSrcFactor: %d", alphaSrcFactor);
    ImGui::TextUnformatted("alphaDstFactor: %d", alphaDstFactor);

    ImGui::Separator();

    if (ImGui::BeginTable("##BlendModeTable", 2, ImGuiTableFlags_BordersOuter))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("ColorEquationAdd##BlendModeColorEquationAdd")) { colorEquation = sf::BlendMode::Equation::Add; }
        if (ImGui::Button("ColorEquationSubtract##BlendModeColorEquationSubtract")) { colorEquation = sf::BlendMode::Equation::Subtract; }
        if (ImGui::Button("ColorEquationReverseSubtract##BlendModeColorEquationReverseSubtract")) { colorEquation = sf::BlendMode::Equation::ReverseSubtract; }

        ImGui::Separator();

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("AlphaEquationAdd##BlendModeAlphaEquationAdd")) { alphaEquation = sf::BlendMode::Equation::Add; }
        if (ImGui::Button("AlphaEquationSubtract##BlendModeAlphaEquationSubtract")) { alphaEquation = sf::BlendMode::Equation::Subtract; }
        if (ImGui::Button("AlphaEquationReverseSubtract##BlendModeAlphaEquationReverseSubtract")) { alphaEquation = sf::BlendMode::Equation::ReverseSubtract; }

        ImGui::Separator();

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("ColorSrcFactorDstAlpha##BlendModeColorSrcFactorDstAlpha")) { colorSrcFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("ColorSrcFactorDstColor##BlendModeColorSrcFactorDstColor")) { colorSrcFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("ColorSrcFactorOne##BlendModeColorSrcFactorOne")) { colorSrcFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("ColorSrcFactorOneMinusDstAlpha##BlendModeColorSrcFactorOneMinusDstAlpha")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("ColorSrcFactorOneMinusDstColor##BlendModeColorSrcFactorOneMinusDstColor")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("ColorSrcFactorOneMinusSrcAlpha##BlendModeColorSrcFactorOneMinusSrcAlpha")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("ColorSrcFactorOneMinusSrcColor##BlendModeColorSrcFactorOneMinusSrcColor")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("ColorSrcFactorSrcAlpha##BlendModeColorSrcFactorSrcAlpha")) { colorSrcFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("ColorSrcFactorSrcColor##BlendModeColorSrcFactorSrcColor")) { colorSrcFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("ColorSrcFactorZero##BlendModeColorSrcFactorZero")) { colorSrcFactor = sf::BlendMode::Factor::Zero; }

        ImGui::Separator();

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("ColorDstFactorDstAlpha##BlendModeColorDstFactorDstAlpha")) { colorDstFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("ColorDstFactorDstColor##BlendModeColorDstFactorDstColor")) { colorDstFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("ColorDstFactorOne##BlendModeColorDstFactorOne")) { colorDstFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("ColorDstFactorOneMinusDstAlpha##BlendModeColorDstFactorOneMinusDstAlpha")) { colorDstFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("ColorDstFactorOneMinusDstColor##BlendModeColorDstFactorOneMinusDstColor")) { colorDstFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("ColorDstFactorOneMinusSrcAlpha##BlendModeColorDstFactorOneMinusSrcAlpha")) { colorDstFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("ColorDstFactorOneMinusSrcColor##BlendModeColorDstFactorOneMinusSrcColor")) { colorDstFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("ColorDstFactorSrcAlpha##BlendModeColorDstFactorSrcAlpha")) { colorDstFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("ColorDstFactorSrcColor##BlendModeColorDstFactorSrcColor")) { colorDstFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("ColorDstFactorZero##BlendModeColorDstFactorZero")) { colorDstFactor = sf::BlendMode::Factor::Zero; }

        ImGui::Separator();

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("AlphaSrcFactorDstAlpha##BlendModeAlphaSrcFactorDstAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("AlphaSrcFactorDstColor##BlendModeAlphaSrcFactorDstColor")) { alphaSrcFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("AlphaSrcFactorOne##BlendModeAlphaSrcFactorOne")) { alphaSrcFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("AlphaSrcFactorOneMinusDstAlpha##BlendModeAlphaSrcFactorOneMinusDstAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("AlphaSrcFactorOneMinusDstColor##BlendModeAlphaSrcFactorOneMinusDstColor")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("AlphaSrcFactorOneMinusSrcAlpha##BlendModeAlphaSrcFactorOneMinusSrcAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("AlphaSrcFactorOneMinusSrcColor##BlendModeAlphaSrcFactorOneMinusSrcColor")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("AlphaSrcFactorSrcAlpha##BlendModeAlphaSrcFactorSrcAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("AlphaSrcFactorSrcColor##BlendModeAlphaSrcFactorSrcColor")) { alphaSrcFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("AlphaSrcFactorZero##BlendModeAlphaSrcFactorZero")) { alphaSrcFactor = sf::BlendMode::Factor::Zero; }

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("AlphaDstFactorDstAlpha##BlendModeAlphaDstFactorDstAlpha")) { alphaDstFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("AlphaDstFactorDstColor##BlendModeAlphaDstFactorDstColor")) { alphaDstFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("AlphaDstFactorOne##BlendModeAlphaDstFactorOne")) { alphaDstFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("AlphaDstFactorOneMinusDstAlpha##BlendModeAlphaDstFactorOneMinusDstAlpha")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("AlphaDstFactorOneMinusDstColor##BlendModeAlphaDstFactorOneMinusDstColor")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("AlphaDstFactorOneMinusSrcAlpha##BlendModeAlphaDstFactorOneMinusSrcAlpha")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("AlphaDstFactorOneMinusSrcColor##BlendModeAlphaDstFactorOneMinusSrcColor")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("AlphaDstFactorSrcAlpha##BlendModeAlphaDstFactorSrcAlpha")) { alphaDstFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("AlphaDstFactorSrcColor##BlendModeAlphaDstFactorSrcColor")) { alphaDstFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("AlphaDstFactorZero##BlendModeAlphaDstFactorZero")) { alphaDstFactor = sf::BlendMode::Factor::Zero; }

        ImGui::EndTable();
    }

    ImGui::End();

    linearBurn.colorEquation = (sf::BlendMode::Equation)colorEquation;
    linearBurn.alphaEquation = (sf::BlendMode::Equation)alphaEquation;
    linearBurn.colorSrcFactor = (sf::BlendMode::Factor)colorSrcFactor;
    linearBurn.colorDstFactor = (sf::BlendMode::Factor)colorDstFactor;
    linearBurn.alphaSrcFactor = (sf::BlendMode::Factor)alphaSrcFactor;
    linearBurn.alphaDstFactor = (sf::BlendMode::Factor)alphaDstFactor;

    // light.png
    // 2 2 3 2 8 8
    // 2 0 3 2 8 8

    // light2.png
    // 2 2 8 8 8 8
    // 2 2 5 8 8 8
    // 2 2 2 8 8 8

    m_renderWindow.draw(sprRt, linearBurn);

    return;
*/
