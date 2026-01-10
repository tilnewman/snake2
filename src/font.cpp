// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// font.cpp
//
#include "font.hpp"

#include "config.hpp"
#include "sfml-util.hpp"

namespace snake2
{

    FontManager::FontManager()
        : m_font{}
    {}

    void FontManager::setup(const Config & t_config)
    {
        if (!m_font.openFromFile((t_config.media_path / "font" / "bpdots-unicase-square" /
                                  "bpdots-unicase-square.otf")
                                     .string()))
        {
            throw std::runtime_error("Error: Failed to open font!");
        }

        setupFontExtents(t_config);
    }

    sf::Text FontManager::makeText(
        const FontSize t_size, const std::string & t_text, const sf::Color & t_color) const
    {
        sf::Text text(m_font);
        text.setCharacterSize(extent(t_size).char_size);
        text.setFillColor(t_color);
        text.setString(t_text);

        util::setOriginToPosition(text);

        return text;
    }

    void FontManager::setupFontExtents(const Config & t_config)
    {
        // these values are based on default MacBook Pros resolution and are close enough to others
        const float standardRes = std::sqrt(3840.f * 2400.0f);

        const float currentRes =
            std::sqrt(static_cast<float>(t_config.video_mode.size.x * t_config.video_mode.size.y));

        const float ratioRes = (currentRes / standardRes);

        sf::Text text(m_font);
        const std::string widthStr{ "M" };
        const std::string heightStr{ "|g" };

        m_fontExtentHuge.char_size     = static_cast<unsigned>(200.0f * ratioRes);
        text                           = makeText(FontSize::Huge, widthStr);
        m_fontExtentHuge.letter_size.x = text.getGlobalBounds().size.x;
        text                           = makeText(FontSize::Huge, heightStr);
        m_fontExtentHuge.letter_size.y = text.getGlobalBounds().size.y;

        m_fontExtentLarge.char_size     = static_cast<unsigned>(90.0f * ratioRes);
        text                            = makeText(FontSize::Large, widthStr);
        m_fontExtentLarge.letter_size.x = text.getGlobalBounds().size.x;
        text                            = makeText(FontSize::Large, heightStr);
        m_fontExtentLarge.letter_size.y = text.getGlobalBounds().size.y;

        m_fontExtentMedium.char_size     = static_cast<unsigned>(60.0f * ratioRes);
        text                             = makeText(FontSize::Medium, widthStr);
        m_fontExtentMedium.letter_size.x = text.getGlobalBounds().size.x;
        text                             = makeText(FontSize::Medium, heightStr);
        m_fontExtentMedium.letter_size.y = text.getGlobalBounds().size.y;

        m_fontExtentSmall.char_size     = static_cast<unsigned>(40.0f * ratioRes);
        text                            = makeText(FontSize::Small, widthStr);
        m_fontExtentSmall.letter_size.x = text.getGlobalBounds().size.x;
        text                            = makeText(FontSize::Small, heightStr);
        m_fontExtentSmall.letter_size.y = text.getGlobalBounds().size.y;
    }

} // namespace snake2
