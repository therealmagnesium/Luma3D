#pragma once
#include "Graphics/RendererInternal.h"
#include "Graphics/Texture.h"

#include "Core/Base.h"

#include <vector>

namespace Graphics
{
    struct Mesh
    {
        VertexArray vertexArray;
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;

        std::vector<Vertex> vertices;
        std::vector<u32> indices;

        u32 materialIndex = 0;
    };

    Mesh LoadMesh(Vertex* vertices, u32 vertexCount, u32* indices, u32 indexCount,
                  u32 materialIndex);
    void LogMeshInfo(const Mesh& mesh);
    void UnloadMesh(Mesh& mesh);

}
