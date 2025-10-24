#pragma once

namespace utils{
    sf::Color TempToColor(float value, float minVal, float maxVal) {
        // Clamp
        value = std::clamp(value, minVal, maxVal);

        // Normalize to [0,1]
        float normalized = (value - minVal) / (maxVal - minVal);

        // Split gradient around the midpoint (0 normalized ≈ cold, 1 ≈ hot)
        if (normalized < 0.5f) {
            // Cold side: blue → cyan → white
            float t = normalized / 0.5f; // 0 → 1 over cold range
            uint8_t r = static_cast<uint8_t>(0 * (1 - t) + 240 * t);
            uint8_t g = static_cast<uint8_t>(0 * (1 - t) + 255 * t);
            uint8_t b = 255;
            return sf::Color(r, g, b);
        } else {
            // Hot side: white → yellow → red
            float t = (normalized - 0.5f) / 0.5f;
            uint8_t r = 255;
            uint8_t g = static_cast<uint8_t>(255 * (1 - t));
            uint8_t b = static_cast<uint8_t>(240 * (1 - t));
            return sf::Color(r, g, b);
        }
    }
    
}
