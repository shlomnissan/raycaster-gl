// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/mesh.hpp"
#include "core/pixels.hpp"
#include "core/plane.hpp"
#include "core/shader.hpp"
#include "core/window.hpp"

#include "shaders/headers/vertex.h"
#include "shaders/headers/fragment.h"

auto main() -> int {
    constexpr auto width = 800;
    constexpr auto height = 600;
    auto window = Window {width, height, "Raycaster in OpenGL"};
    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex},
        {ShaderType::kFragmentShader, _SHADER_fragment}
    }};

    auto plane = Plane {2, 2, 1, 1};
    auto screen = Mesh { plane.vertices(), plane.indices() };
    auto pixels = Pixels {width, height};

    pixels.SetStroke({0, 255, 0});
    pixels.SetFill({255, 0, 0});

    auto dx = 20, vx = 1;

    window.Start([&](const double delta){
        pixels.Clear();

        pixels.Rect(dx, 100, 100, 100);

        if (dx + 100 >= width - 20) vx = -1;
        if (dx <= 20) vx = 1;
        dx += vx;

        pixels.Bind();
        screen.Draw(shader);
    });

    return 0;
}