//
// coordinator.cpp
//
#include "coordinator.hpp"

#include "sfml-util.hpp"

#include <SFML/System/Clock.hpp>

#include <iostream>

namespace snake2
{

    Coordinator::Coordinator()
        : m_config{}
        , m_renderStates{}
        , m_renderWindow{}
        , m_bloomWindowPtr{}
        , m_isRunning{ true }
    {}

    void Coordinator::run(const Config & t_config)
    {
        setup(t_config);
        loop();
        teardown();
    }

    void Coordinator::setup(const Config & t_config)
    {
        m_config = t_config;
        setupRenderWindow(m_config.video_mode);
        m_bloomWindowPtr = std::make_unique<util::BloomEffectHelper>(m_renderWindow);
        m_bloomWindowPtr->isEnabled(true);
        m_bloomWindowPtr->blurMultipassCount(3);
    }

    void Coordinator::loop()
    {
        sf::Clock frameClock;
        while (m_bloomWindowPtr->isOpen() && m_isRunning)
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
        }
    }

    void Coordinator::teardown()
    {
        m_bloomWindowPtr.reset();

        if (m_renderWindow.isOpen())
        {
            m_renderWindow.close();
        }
    }

    void Coordinator::handleEvents()
    {
        while (const auto eventOpt = m_renderWindow.pollEvent())
        {
            handleEvent(eventOpt.value());
        }
    }

    void Coordinator::handleEvent(const sf::Event & t_event)
    {
        if (t_event.is<sf::Event::Closed>())
        {
            m_isRunning = false;
            std::cout << "Stopping because window was closed externally.\n";
        }
        else if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_isRunning = false;
            }
        }
    }

    void Coordinator::update(const float) {}

    void Coordinator::draw()
    {
        m_bloomWindowPtr->clear(sf::Color::Black);
        // m_grid.draw(m_config, m_bloomWindowPtr->renderTarget(), m_renderStates);
        m_bloomWindowPtr->display();
    }

    void Coordinator::setupRenderWindow(sf::VideoMode & t_videoMode)
    {
        std::cout << "Attempting video mode " << t_videoMode << "...";

        if (!m_config.video_mode.isValid())
        {
            std::cout << "but that is not suported.  Valid video modes at "
                      << m_config.video_mode.bitsPerPixel << "bpp:\n"
                      << util::makeSupportedVideoModesString(m_config.video_mode.bitsPerPixel)
                      << '\n';

            t_videoMode = util::findHighestVideoMode(m_config.video_mode.bitsPerPixel);
            setupRenderWindow(t_videoMode);
            return;
        }

        m_renderWindow.create(t_videoMode, "CastleCrawl2", sf::State::Fullscreen);

        // sometimes the resolution of the window created does not match what was specified
        const unsigned actualWidth  = m_renderWindow.getSize().x;
        const unsigned actualHeight = m_renderWindow.getSize().y;
        if ((m_config.video_mode.size.x == actualWidth) &&
            (m_config.video_mode.size.y == actualHeight))
        {
            std::cout << "Success." << std::endl;
        }
        else
        {
            std::cout << "Failed" << ".  ";

            m_config.video_mode.size.x = actualWidth;
            m_config.video_mode.size.y = actualHeight;

            std::cout << "Using " << m_config.video_mode << " instead." << std::endl;
        }

        if (m_config.framerate_limit > 0)
        {
            m_renderWindow.setFramerateLimit(m_config.framerate_limit);
        }
    }

} // namespace snake2
