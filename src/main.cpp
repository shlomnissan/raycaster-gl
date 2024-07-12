// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/mesh.hpp"
#include "core/pixels.hpp"
#include "core/plane.hpp"
#include "core/shader.hpp"
#include "core/window.hpp"

#include "shaders/headers/vertex.h"
#include "shaders/headers/fragment.h"

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))
#define STRIDE(stride) (sizeof(GLfloat) * stride)

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

    window.Start([&](const double delta){
        pixels.Clear();

        pixels.Line(100, 100, 300, 400, {.r = 210, .g = 143, .b = 80});

        pixels.Bind();
        screen.Draw(shader);
    });

    return 0;
}