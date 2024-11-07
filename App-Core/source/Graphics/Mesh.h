#pragma once
#include "Graphics/RendererInternal.h"
#include "Core/Base.h"

#include <vector>

namespace Graphics
{
    struct Mesh
    {
        u32 vertexCount = 0;
        VertexArray vertexArray;
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;

        std::vector<Vertex> vertices;
        std::vector<u32> indices;
    };

    Mesh LoadMesh(Vertex* vertices, u32 vertexCount, u32* indices, u32 indexCount);
    void LogMeshInfo(const Mesh& mesh);
    void UnloadMesh(Mesh& mesh);

}
