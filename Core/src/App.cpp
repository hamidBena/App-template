#include "App.hpp"

#include "Timer.hpp"
#include "Logger.hpp"

namespace core {

Application::Application() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    m_window = std::make_shared<sf::RenderWindow>(desktop, "My App", sf::Style::None);
    m_window->setFramerateLimit(120);
}

Application::~Application() {
    if (m_window) {
        m_window->close();
    }
}

Application* Application::get() {
    static Application instance;
    return &instance;
}

void Application::run() {
    sf::Clock clock;
    Timer appTimer("Application Run Time", true);
    while (m_window->isOpen()) {
        while (const std::optional event = m_window->pollEvent()) {
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                 event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
                m_window->close();
            }
            m_layerStack.dispatchEvent(*event, *m_window);
        }

        m_window->clear(sf::Color::Black);

        float dt = clock.restart().asSeconds();
        m_layerStack.onUpdate(dt);
        m_layerStack.onRender(*m_window);

        m_window->display();
        
        if(m_shutdown) {
            m_window->close();
        }
    }
}

std::shared_ptr<sf::RenderWindow> Application::getWindow() const {
    return m_window;
}

}