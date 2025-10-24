#pragma once
#include <vector>
#include "../utils/GeneralUtils.hpp"

class Heat {
    public:
    std::vector<float> temperatures;
    std::vector<float> temperatures2;
    std::vector<uint8_t> colors;
    size_t width;
    size_t height;

    float total_energy=0.f;

    public:
    Heat(size_t width, size_t height) : temperatures(width * height, 0.f), temperatures2(width * height, 0.f), colors(width * height * 4), width(width), height(height) {}

    void update(const float& dt){
        simulateHeat(temperatures, temperatures2, width, height, 10.1f, dt);
        std::swap(temperatures, temperatures2);
        updateColor();

        temperatures[0] = 40.f; // heat source
        temperatures[width/2 + width * width/2] = -200.f; // cold sink
    }

    private:

    void simulateHeat( const std::vector<float>& cur, std::vector<float>& next, int w, int h, float diffusion, float dt, float dx = 1.0f ) {
        next = cur; // start from current

        float coef = diffusion * dt / (dx * dx);

        auto sample = [&](int x, int y) -> float {
            // clamp coordinates — mirrors edges (zero-flux)
            x = std::clamp(x, 0, w - 1);
            y = std::clamp(y, 0, h - 1);
            return cur[y * w + x];
        };
        total_energy = 0.f;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                float c = sample(x, y);
                float up = sample(x, y - 1);
                float down = sample(x, y + 1);
                float left = sample(x - 1, y);
                float right = sample(x + 1, y);

                // discrete Laplacian
                float lap = (up + down + left + right - 4.0f * c);

                next[y * w + x] = c + coef * lap;
                total_energy += next[y * w + x];
            }
        }
    }

    void updateColor(){
        float minTemp = *std::min_element(temperatures.begin(), temperatures.end());
        float maxTemp = *std::max_element(temperatures.begin(), temperatures.end());

        minTemp = -5;
        maxTemp = 5;
        for (size_t i = 0; i < temperatures.size(); ++i) {
            sf::Color color = utils::TempToColor(temperatures[i], minTemp, maxTemp);
            colors[i*4] = color.r;
            colors[i*4+1] = color.g;
            colors[i*4+2] = color.b;
            colors[i*4+3] = 150;
        }
    }

};