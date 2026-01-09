//
// layout.cpp
//
#include "layout.hpp"

#include "sfml-util.hpp"

#include <cmath>

namespace snake2
{

    Layout::Layout()
        : m_screenRect{}
        , m_topRect{}
        , m_bottomRect{}
        , m_gridRect{}
    {}

    void Layout::setup(const Config & t_config)
    {
        // divide the screen into top and bottom regions
        m_screenRect.position = { 0.0f, 0.0f };
        m_screenRect.size     = sf::Vector2f{ t_config.video_mode.size };

        m_topRect.position = m_screenRect.position;
        m_topRect.size.x   = m_screenRect.size.x;
        m_topRect.size.y   = std::floor(m_screenRect.size.y * t_config.top_region_height_ratio);

        m_bottomRect.position = { m_screenRect.position.x, (util::bottom(m_topRect) + 2.0f) };

        m_bottomRect.size     = { m_screenRect.size.x,
                                  (m_screenRect.size.y - m_bottomRect.position.y) };
    }

} // namespace snake2
