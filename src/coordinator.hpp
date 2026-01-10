#ifndef COORDINATOR_HPP_INCLUDED
#define COORDINATOR_HPP_INCLUDED
//
// coordinator.hpp
//
#include "actors.hpp"
#include "bloom-shader.hpp"
#include "cell-anim.hpp"
#include "config.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-display.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "random.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <memory>

namespace snake2
{

    class Coordinator
    {
      public:
        Coordinator();
        void run(const Config & t_config);

      private:
        void setup(const Config & t_config);
        void loop();
        void teardown();

        void handleEvents();
        void handleEvent(const sf::Event & t_event);
        void update(const float t_elapsedTimeSec);
        void draw();

        void setupRenderWindow(sf::VideoMode & t_videoMode);

      private:
        Config m_config;
        sf::RenderStates m_renderStates;
        sf::RenderWindow m_renderWindow;
        std::unique_ptr<util::BloomEffectHelper> m_bloomWindowPtr;
        std::unique_ptr<FramerateDisplay> m_framerateDisplayUPtr;
        Layout m_layout;
        GridDisplay m_gridDisplay;
        Snake m_snake;
        Actors m_actors;
        util::Random m_random;
        CellAnimationManager m_cellAnimationManager;
        util::SoundPlayer m_soundPlayer;
        FontManager m_fontManager;
        StateManager m_stateManager;
        Context m_context;
    };

} // namespace snake2

#endif // COORDINATOR_HPP_INCLUDED
