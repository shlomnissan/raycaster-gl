#version 410 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoords;

out vec2 TexCoords;

void main() {
    TexCoords = aTextureCoords;
    gl_Position = vec4(aPosition, 1.0);
}