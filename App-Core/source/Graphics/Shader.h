#pragma once
#include "Core/Base.h"

namespace Graphics
{
    enum ShaderLocation
    {
        SHADER_LOC_MAP_DIFFUSE = 0,
        SHADER_LOC_MAP_SPECULAR,
        SHADER_LOC_COLOR_AMBIENT,
        SHADER_LOC_COLOR_DIFFUSE,
        SHADER_LOC_COLOR_SPECULAR,
        SHADER_LOC_VECTOR_VIEW,
        SHADER_LOC_MATRIX_MODEL,
        SHADER_LOC_MATRIX_VIEW,
        SHADER_LOC_MATRIX_PROJECTION,
        SHADER_LOC_MATRIX_NORMAL,
        SHADER_LOC_COUNT
    };

    struct Shader
    {
        u32 id;
        s32 uniformLocs[SHADER_LOC_COUNT];

        void Bind();
        void Unbind();

        void SetInt(s32 location, s32 val);
        void SetFloat(s32 location, float val);
        void SetVec2(s32 location, float* vec2);
        void SetVec3(s32 location, float* vec3);
        void SetVec4(s32 location, float* vec4);
        void SetMat4(s32 location, float* mat4);
    };

    Shader LoadShader(const char* vertexPath, const char* fragmentPath);
    s32 GetUniformLocation(const Shader& shader, const char* name);
    void UnloadShader(Shader& shader);
}
