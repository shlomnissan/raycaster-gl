// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/pixels.hpp"

constexpr auto WIDTH = 800;
constexpr auto HEIGHT = 600;

auto main() -> int {
    auto pixels = Pixels {WIDTH, HEIGHT, "Raycaster in OpenGL"};
    pixels.SetStroke({0, 255, 0});
    pixels.SetFill({255, 0, 0});

    auto x_pos = 0.0, speed = 100.0;

    pixels.Update([&](const double delta) {
        if (x_pos > WIDTH - 100) {
            speed *= -1;
            x_pos = WIDTH - 100;
        }
        if (x_pos < 0) {
            speed *= -1;
            x_pos = 0;
        }
        x_pos += speed * delta;
    });

    pixels.Draw([&]() {
        pixels.Rect(x_pos, 100, 100, 100);
    });

    pixels.Run();

    return 0;
}