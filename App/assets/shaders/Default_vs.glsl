#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uvCoords;

out vec3 fragPosition;
out vec3 fragColor;
out vec2 fragUVCoords;

void main()
{
    fragPosition = position;
    fragColor = color;
    fragUVCoords = uvCoords;
    gl_Position = vec4(position, 1.f);
}
