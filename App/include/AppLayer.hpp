#pragma once

#include "Layer.hpp"
#include "MyUI.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

// Forward declaration to avoid circular dependency
namespace core {
    class Application;
}

namespace app{
class AppLayer : public core::Layer {
    
public:
    virtual ~AppLayer() = default;

    AppLayer() {
        auto gui1 = userInterface.createContainer<myui::containers::Canvas>(*m_window);
        auto panel1 = gui1->CreateElement<myui::containers::VLayout>();
        panel1->setOffset({50, 50});
        panel1->CreateElement<myui::widgets::Label>();
        auto CloseButton = panel1->CreateElement<myui::widgets::Button>();
        panel1->CreateElement<myui::widgets::CheckBox>();

        core::Logger::get().info("This is a info message from AppLayer.");
        core::Logger::get().critical("This is a critical message from AppLayer.");

        CloseButton->setLabel("Close");
        CloseButton->setOnClick([](auto& element, auto& duration){
            core::Application::get()->shutdown();
        });
    }

    virtual void onEvent(const sf::Event& event, sf::RenderWindow& window) override {
        userInterface.handleEvent(event, window);
    }
    virtual void onUpdate(const float& dt) override {
        userInterface.update(dt);
    }
    virtual void onRender(sf::RenderTarget& target) override {
        userInterface.draw(target);
    }

private:
    myui::GUI userInterface;
    std::shared_ptr<sf::RenderWindow> m_window = core::Application::get()->getWindow();


};
}