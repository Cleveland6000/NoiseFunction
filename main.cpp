#include <iostream>
#include <chrono>
#include <string>
#include "PerlinNoise2D.hpp"

void print_noise_char(float n) {
    if (n < 0.2f) {
        std::cout << " ";
    } else if (n < 0.4f) {
        std::cout << ".";
    } else if (n < 0.6f) {
        std::cout << "-";
    } else if (n < 0.8f) {
        std::cout << "=";
    } else {
        std::cout << "#";
    }
}

void draw_noise_row(const PerlinNoise2D& perlin, int width, float y, float scale, float offsetX, float offsetY) {
    for (int i = 0; i < width; ++i) {
        float n = (perlin.noise(i * scale + offsetX, y * scale + offsetY) + 1.0f) * 0.5f;
        print_noise_char(n);
    }
    std::cout << std::endl;
}

void draw_noise_pattern(const PerlinNoise2D& perlin, int width, int height, float scale, float offsetX, float offsetY, const std::string& title) {
    std::cout << "\n--- " << title << " ---" << std::endl;
    for (int j = 0; j < height; ++j) {
        draw_noise_row(perlin, width, static_cast<float>(j), scale, offsetX, offsetY);
    }
}

int main() {
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    PerlinNoise2D perlin(seed);

    const int width = 50;
    const int height = 256;
    float scale = 1.0f;

    draw_noise_pattern(perlin, width, height, scale, 0.0f, 0.0f, "Original Pattern (0,0 to 49,255)");
    draw_noise_pattern(perlin, width, height, scale, 0.0f, 256.0f, "Repeated Pattern (0,256 to 49,511)");

    return 0;
}
