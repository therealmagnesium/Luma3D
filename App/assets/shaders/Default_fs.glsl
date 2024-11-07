#version 330 core
out vec4 finalColor;

in vec3 fragPosition;
in vec3 fragColor;

void main()
{
    finalColor = vec4(fragColor + vec3(0.3f), 1.f);
}
