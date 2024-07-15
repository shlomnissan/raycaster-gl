// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/pixels.hpp"

#include "game/level.hpp"

auto main() -> int {
    auto level = Level {};

    auto pixels = Pixels {
        level.Cols() * Level::TILE_SIZE,
        level.Rows() * Level::TILE_SIZE,
        "Raycaster OpenGL"
    };

    pixels.Update([&](const double delta) {
        // TODO: impl.
    });

    pixels.Draw([&]() {
        level.DrawMinimap(pixels);
    });

    pixels.Run();

    return 0;
}