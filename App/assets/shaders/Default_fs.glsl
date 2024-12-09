#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragUVCoords;
in vec3 fragNormal;

const float PI = 3.14159265359;

struct Material
{
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseMap;

    float roughness;
    float metalic;
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
    if (length(texel) > 0.f)
        objectColor =  texel * material.diffuse;

    return objectColor;
}

/*
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
}*/

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 ApplyGammaCoorection(vec3 color)
{
    vec3 gammaCoorection = vec3(0.f);
    vec3 hdrColor = color / (color + vec3(1.f));
    gammaCoorection = pow(hdrColor, vec3(1.f/2.2f));
    
    return gammaCoorection;
}

void main()
{
    /*
    vec3 normal = normalize(fragNormal);
    vec3 objectColor = GetObjectColor();
    vec3 diffuse = CalculateDiffuse(normal);
    vec3 specular = CalculateSpecular(normal);
    vec3 result = objectColor * (0.7f + diffuse + specular);

    finalColor = vec4(result, 1.f);*/

    vec3 N = normalize(fragNormal);
    vec3 V = normalize(cameraPosition - fragPosition);
    vec3 L = normalize(-directionalLight.direction);
    vec3 H = normalize(V + L);
    vec3 albedo = pow(GetObjectColor(), vec3(2.2f));

    vec3 F0 = vec3(0.04f);
    F0 = mix(F0, albedo, material.metalic);

    float distance = length(-directionalLight.direction);
    float attenuation = 1.f / (distance * distance);
    vec3 radiance = directionalLight.color * attenuation;

    float NDF = DistributionGGX(N, H, material.roughness);
    float G = GeometrySmith(N, V, L, material.roughness);
    vec3 F = FresnelSchlick(max(dot(H, V), 0.f), F0);

    vec3 numerator = NDF * G * F;
    float denominator = 4.f * max(dot(N, V), 0.f) * max(dot(N, L), 0.f) + 0.0001f;
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = (vec3(1.f) - kS) * (1.f - material.metalic);

    float NdotL = max(dot(N, L), 0.f);
    vec3 Lo = directionalLight.intensity * (kD * albedo / PI + specular) * radiance * NdotL;
    vec3 ambient = vec3(0.5f) * albedo;

    vec3 result = Lo + ambient;
    result = ApplyGammaCoorection(result);

    finalColor = vec4(result, 1.f);
}
