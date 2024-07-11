// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    auto ratio = static_cast<float>(width) / static_cast<float>(height);
    shader.SetMat4("Projection", glm::perspective(45.0f, ratio, 0.1f, 100.0f));

    window.Start([&](const double delta){
        // TODO: game loop
    });

    return 0;
}