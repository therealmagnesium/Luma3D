#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uvCoords;
layout (location = 3) in vec3 normal;

out vec3 fragPosition;
out vec3 fragColor;
out vec2 fragUVCoords;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragPosition = position;
    fragColor = color;
    fragUVCoords = uvCoords;
    fragNormal = normal;

    gl_Position = projection * view * model * vec4(position, 1.f);
}
