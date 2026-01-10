//
// coordinator.cpp
//
#include "coordinator.hpp"

#include "sfml-defaults.hpp"
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
        , m_framerateDisplayUPtr{}
        , m_layout{}
        , m_gridDisplay{}
        , m_snake{}
        , m_actors{}
        , m_random{}
        , m_cellAnimationManager{}
        , m_soundPlayer{ m_random }
        , m_fontManager{}
        , m_context{ m_config,     m_layout, m_gridDisplay,          m_random,
                     m_snake,      m_actors, m_cellAnimationManager, m_soundPlayer,
                     m_fontManager }
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
        m_renderWindow.setMouseCursorVisible(false);

        m_bloomWindowPtr = std::make_unique<util::BloomEffectHelper>(m_renderWindow);
        m_bloomWindowPtr->isEnabled(true);
        m_bloomWindowPtr->blurMultipassCount(5);

        util::SfmlDefaults::instance().setup();
        m_layout.setup(m_config);
        m_fontManager.setup(m_config);
        m_framerateDisplayUPtr = std::make_unique<FramerateDisplay>();
        m_framerateDisplayUPtr->setup(m_context);
        m_gridDisplay.setup(m_context);
        m_snake.setup(m_context);
        m_actors.setup(m_context);
        m_cellAnimationManager.setup(m_context);

        m_soundPlayer.setMediaPath((m_config.media_path / "sfx").string());
        m_soundPlayer.loadAll();

        // TODO remove after testing
        for (int x{ 0 }; x < static_cast<int>(m_layout.cellCount().x); ++x)
        {
            m_actors.add(m_context, Actor::Wall, { x, 0 });

            m_actors.add(
                m_context, Actor::Wall, { x, static_cast<int>(m_layout.cellCount().y - 1u) });
        }
        for (int counter{ 0 }; counter < 6; ++counter)
        {
            const GridPosVec_t freePositions{ m_actors.findFreePositions(m_context) };
            m_actors.add(m_context, Actor::Food, m_random.from(freePositions));
        }
        for (int counter{ 0 }; counter < 6; ++counter)
        {
            const GridPosVec_t freePositions{ m_actors.findFreePositions(m_context) };
            m_actors.add(m_context, Actor::Shrink, m_random.from(freePositions));
        }
        for (int counter{ 0 }; counter < 6; ++counter)
        {
            const GridPosVec_t freePositions{ m_actors.findFreePositions(m_context) };
            m_actors.add(m_context, Actor::Slow, m_random.from(freePositions));
        }
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
            std::cout << "Exiting because window was closed externally.\n";
            return;
        }
        else if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_isRunning = false;
                return;
            }
        }

        m_actors.handleEvent(m_context, t_event);
        m_snake.handleEvent(m_context, t_event);
    }

    void Coordinator::update(const float t_elapsedTimeSec)
    {
        m_actors.update(m_context, t_elapsedTimeSec);
        m_snake.update(m_context, t_elapsedTimeSec);
        m_cellAnimationManager.update(m_context, t_elapsedTimeSec);
        m_framerateDisplayUPtr->update(m_context, t_elapsedTimeSec);
    }

    void Coordinator::draw()
    {
        m_bloomWindowPtr->clear(sf::Color::Black);

        m_bloomWindowPtr->renderTarget().draw(m_gridDisplay, m_renderStates);
        m_actors.draw(m_context, m_bloomWindowPtr->renderTarget(), m_renderStates);
        m_snake.draw(m_context, m_bloomWindowPtr->renderTarget(), m_renderStates);
        m_cellAnimationManager.draw(m_bloomWindowPtr->renderTarget(), m_renderStates);
        m_framerateDisplayUPtr->draw(m_bloomWindowPtr->renderTarget(), m_renderStates);

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

        m_renderWindow.create(t_videoMode, "Snake2", sf::State::Fullscreen);

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
