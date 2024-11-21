#pragma once
#include "Core/Base.h"
#include <glm/glm.hpp>

namespace Graphics
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 uvCoords;
        glm::vec3 normal;
    };

    struct VertexArray
    {
        u32 id = 0;
        bool isInitialized = false;
        bool isSelected = false;

        void Bind();
        void Unbind();
        void StoreInAtrribList(u32 location, u32 numElements, u64 offset);
    };

    struct VertexBuffer
    {
        u32 id = 0;
        bool isInitialized = false;
        bool isSelected = false;

        void Bind();
        void Unbind();
        void SendData(float* data, u64 dataSize);
    };

    struct IndexBuffer
    {
        u32 id = 0;
        bool isInitialized = false;
        bool isSelected = false;

        void Bind();
        void Unbind();
        void SendData(u32* data, u64 dataSize);
    };

    VertexArray CreateVertexArray();
    void DeleteVertexArray(VertexArray& vao);

    VertexBuffer CreateVertexBuffer();
    void DeleteVertexBuffer(VertexBuffer& vbo);

    IndexBuffer CreateIndexBuffer();
    void DeleteIndexBuffer(IndexBuffer& ebo);
}
