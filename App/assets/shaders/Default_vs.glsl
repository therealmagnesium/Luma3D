#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uvCoords;
layout (location = 3) in vec3 normal;

out vec3 fragPosition;
out vec3 fragColor;
out vec2 fragUVCoords;
out vec3 fragNormal;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matNormal;

void main()
{
    fragPosition = vec3(matModel * vec4(position, 1.f));
    fragColor = color;
    fragUVCoords = uvCoords;
    fragNormal = mat3(matNormal) * normal;

    gl_Position = matProjection * matView * matModel * vec4(fragPosition, 1.f);
}
