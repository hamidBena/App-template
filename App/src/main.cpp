#include "App.hpp"

#include "AppLayer.hpp"

#include <iostream>

int main() {
    auto* app = core::Application::get();

    auto appLayerId = app->getLayerStack().pushLayer<app::AppLayer>();
    app->getLayerStack().popLayer(appLayerId);
    app->getLayerStack().pushLayer<app::AppLayer>();

    app->run();
}