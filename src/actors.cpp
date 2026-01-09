//
// actors.cpp
//
#include "actors.hpp"

#include "context.hpp"
#include "layout.hpp"

namespace snake2
{

    Actors::Actors()
        : m_actors{}
    {}

    void Actors::setup(const Context & t_context)
    {
        m_actors.reserve(t_context.layout.cellCount().x * t_context.layout.cellCount().y);
    }

    void
        Actors::addActor(const Context & t_context, const Actor t_type, const GridPos_t & t_gridPos)
    {
        m_actors.push_back(makeActor(t_context, t_type, t_gridPos));
    }

    void Actors::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        for (auto & actorUPtr : m_actors)
        {
            actorUPtr->handleEvent(t_context, t_event);
        }
    }

    void Actors::update(const Context & t_context, const float t_elpasedTimeSec)
    {
        for (auto & actorUPtr : m_actors)
        {
            actorUPtr->update(t_context, t_elpasedTimeSec);
        }
    }

    void Actors::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        for (const auto & actorUPtr : m_actors)
        {
            actorUPtr->draw(t_context, t_target, t_states);
        }
    }

    std::unique_ptr<IActor> Actors::makeActor(
        const Context & t_context, const Actor t_type, const GridPos_t & t_gridPos)
    {
        // clang-format off
        switch (t_type)
        {
            case Actor::Food: { return std::make_unique<Food>(t_context, t_gridPos); }
            case Actor::Wall: { return std::make_unique<Wall>(t_context, t_gridPos); }
            default:
            {
                throw std::runtime_error("makeActor() failed because given unknown Actor t_type!");
            }
        }
        // clang-format on
    }

} // namespace snake2
