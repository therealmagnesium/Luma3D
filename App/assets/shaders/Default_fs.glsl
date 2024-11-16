#version 330 core
out vec4 finalColor;

in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragUVCoords;

uniform sampler2D texture0;

void main()
{
    vec3 texelColor = texture(texture0, fragUVCoords).xyz;
    finalColor = vec4(texelColor * fragColor, 1.f);
}
