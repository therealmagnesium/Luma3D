#version 330 core
out vec4 finalColor;

in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragUVCoords;
in vec3 fragNormal;

struct Material
{
    vec3 diffuse;
    sampler2D diffuseMap;
};

uniform Material material;

vec3 GetObjectColor()
{
    vec3 objectColor = material.diffuse;
    vec3 texel = texture(material.diffuseMap, fragUVCoords).xyz;
    if (texel.x > 0.f || texel.y > 0.f || texel.z > 0.f)
        objectColor =  texel * material.diffuse;

    return objectColor;

}

void main()
{
    vec3 objectColor = GetObjectColor();
    finalColor = vec4(objectColor, 1.f);
}
