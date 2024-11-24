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

struct DirectionalLight
{
    float intensity;
    vec3 color;
    vec3 direction;
};

uniform Material material;
uniform DirectionalLight directionalLight;

vec3 GetObjectColor()
{
    vec3 objectColor = material.diffuse;
    vec3 texel = texture(material.diffuseMap, fragUVCoords).xyz;
    if (texel.x > 0.f || texel.y > 0.f || texel.z > 0.f)
        objectColor =  texel * material.diffuse;

    return objectColor;

}

vec3 CalculateDiffuse(vec3 normal)
{
    vec3 lightDirection = normalize(-directionalLight.direction);
    float diffuseFactor = max(dot(normal, lightDirection), 0.f);
    return diffuseFactor * directionalLight.color * directionalLight.intensity;
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 objectColor = GetObjectColor();
    vec3 diffuse = CalculateDiffuse(normal);
    vec3 result = objectColor * (0.3f + diffuse);

    finalColor = vec4(result, 1.f);
}
