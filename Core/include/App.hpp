#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "LayerStack.hpp"

namespace core{

class Application {
public:
    Application();
    ~Application();

    // Singleton access
    static Application* get();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

    std::shared_ptr<sf::RenderWindow> getWindow() const;
    LayerStack& getLayerStack() { return m_layerStack; }

    void shutdown() {m_shutdown = true;}    //sets the shutdown flag to true to queue it to the end of the frame


private:
    std::shared_ptr<sf::RenderWindow> m_window;
    LayerStack m_layerStack;

    bool m_shutdown = false;

    void close() {  // Close the app
        if (m_window) {
            m_window->close();
        }
        m_layerStack.onDetach();
    }

};

}