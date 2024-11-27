#version 330 core
layout (location = 0) in vec3 position;

out vec3 fragCoords;

uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
    fragCoords = position;
    vec4 screenPos = matProjection * matView * vec4(position, 1.f);
    gl_Position = screenPos.xyww;
}
