#pragma once
#include "Layer.hpp"
#include <vector>
#include <memory>

namespace core{

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() {onDetach();}

        template<typename T, typename... Args>
        requires std::is_base_of_v<Layer, T>
        UUID pushLayer(Args&&... args) {
            std::shared_ptr<T> layer = std::make_shared<T>(std::forward<Args>(args)...);
            layer->onAttach();
            m_layers.emplace_back(layer);
            return layer->m_id;
        }
        void popLayer(const UUID& id) {
            auto layer = getLayer(id);
            if (!layer) return;

            layer->onDetach();
            m_layers.erase(std::remove(m_layers.begin(), m_layers.end(), layer), m_layers.end());
            layer.reset();
        }

        void onUpdate(const float& dt) {
            for (auto& layer : m_layers) {
                layer->onUpdate(dt);
            }
        }

        virtual void dispatchEvent(const sf::Event& event, sf::RenderWindow& window) {
            for (auto& layer : m_layers) {
                layer->onEvent(event, window);
            }
        }

        void onRender(sf::RenderTarget& target) {
            for (auto& layer : m_layers) {
                layer->onRender(target);
            }
        }

        std::shared_ptr<Layer> getLayer(const UUID& id) {
            for (auto& layer : m_layers) {
                if (layer->m_id == id) {
                    return layer;
                }
            }
            return nullptr;
        }

        void onDetach() {
            for (auto& layer : m_layers) {
                layer->onDetach();
            }
            m_layers.clear();
        }


    private:
        std::vector<std::shared_ptr<Layer>> m_layers;

    };
}
