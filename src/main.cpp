// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/mesh.hpp"
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

    auto plane = Plane {1.9, 1.9, 1, 1};
    auto mesh = Mesh { plane.vertices(), plane.indices() };

    window.Start([&](const double delta){
        mesh.Draw(shader);
    });

    return 0;
}