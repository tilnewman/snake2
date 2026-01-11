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
        , m_layout{}
        , m_gridDisplay{}
        , m_snake{}
        , m_actors{}
        , m_random{}
        , m_cellAnimationManager{}
        , m_textAnimationManager{}
        , m_soundPlayer{ m_random }
        , m_fontManager{}
        , m_stateManager{}
        , m_context{ m_config,      m_layout,      m_gridDisplay,          m_random,
                     m_snake,       m_actors,      m_cellAnimationManager, m_textAnimationManager,
                     m_soundPlayer, m_fontManager, m_stateManager }
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
        m_gridDisplay.setup(m_context);
        m_snake.setup(m_context);
        m_actors.setup(m_context);
        m_cellAnimationManager.setup(m_context);

        m_soundPlayer.setMediaPath((m_config.media_path / "sfx").string());
        m_soundPlayer.loadAll();

        m_stateManager.setPending(State::Splash);
    }

    void Coordinator::loop()
    {
        sf::Clock frameClock;
        while (m_bloomWindowPtr->isOpen() && (m_stateManager.current().type() != State::Quit))
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
            m_stateManager.changeIfPending(m_context);
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
            m_stateManager.setPending(State::Quit);
            std::cout << "Exiting because window was closed externally.\n";
        }
        else
        {
            m_stateManager.current().handleEvent(m_context, t_event);
        }
    }

    void Coordinator::update(const float t_elapsedTimeSec)
    {
        m_stateManager.current().update(m_context, t_elapsedTimeSec);
    }

    void Coordinator::draw()
    {
        m_bloomWindowPtr->clear(sf::Color::Black);
        m_stateManager.current().draw(m_context, m_bloomWindowPtr->renderTarget(), m_renderStates);
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
