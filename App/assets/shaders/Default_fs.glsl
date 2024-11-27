#version 330 core
out vec4 finalColor;

in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragUVCoords;
in vec3 fragNormal;

struct Material
{
    vec3 diffuse;
    vec3 specular;
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
uniform vec3 cameraPosition;

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
    vec3 diffuse = diffuseFactor * directionalLight.color * directionalLight.intensity;

    return diffuse;
}

vec3 CalculateSpecular(vec3 normal)
{
    vec3 lightDirection = normalize(-directionalLight.direction);
    vec3 viewDirection = normalize(cameraPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.f), 128.f);
    vec3 specular = specularFactor * material.specular * directionalLight.color * directionalLight.intensity;

    return specular;
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 objectColor = GetObjectColor();
    vec3 diffuse = CalculateDiffuse(normal);
    vec3 specular = CalculateSpecular(normal);
    vec3 result = objectColor * (0.7f + diffuse + specular);
    //vec3 result = vec3(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z);

    finalColor = vec4(result, 1.f);
}
