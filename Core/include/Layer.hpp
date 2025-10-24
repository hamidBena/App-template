#pragma once
#include "Logger.hpp"
#include "UUID.hpp"

namespace core{

class Layer {
public:
    virtual ~Layer() = default;

    virtual void onEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void onUpdate(const float& dt) = 0;
    virtual void onRender(sf::RenderTarget& target) = 0;

    virtual void onAttach() {
        Logger::get().info("Layer attached: " + m_id.toString());
    }
    virtual void onDetach() {
        Logger::get().info("Layer detached: " + m_id.toString());
    }

    UUID m_id;

};

}