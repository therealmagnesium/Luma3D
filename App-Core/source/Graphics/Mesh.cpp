#include "Graphics/Mesh.h"
#include "Graphics/RendererInternal.h"

#include "Core/Base.h"
#include "Core/Log.h"

#include <stddef.h>

namespace Graphics
{
    Mesh LoadMesh(Vertex* vertices, u32 vertexCount, u32* indices, u32 indexCount,
                  u32 materialIndex)
    {
        Mesh mesh;
        mesh.vertexArray = CreateVertexArray();
        mesh.vertexBuffer = CreateVertexBuffer();
        mesh.indexBuffer = CreateIndexBuffer();
        mesh.vertices.resize(vertexCount);
        mesh.indices.resize(indexCount);

        for (u32 i = 0; i < mesh.vertices.size(); i++)
            mesh.vertices[i] = vertices[i];

        for (u32 i = 0; i < mesh.indices.size(); i++)
            mesh.indices[i] = indices[i];

        mesh.materialIndex = materialIndex;

        mesh.vertexArray.Bind();

        mesh.vertexBuffer.Bind();
        mesh.vertexBuffer.SendData((float*)vertices, vertexCount * sizeof(Vertex));

        mesh.indexBuffer.Bind();
        mesh.indexBuffer.SendData(indices, indexCount * sizeof(u32));

        mesh.vertexArray.StoreInAtrribList(0, 3, offsetof(Vertex, position));
        mesh.vertexArray.StoreInAtrribList(1, 3, offsetof(Vertex, color));
        mesh.vertexArray.StoreInAtrribList(2, 2, offsetof(Vertex, uvCoords));
        mesh.vertexArray.StoreInAtrribList(3, 3, offsetof(Vertex, normal));

        mesh.vertexBuffer.Unbind();
        mesh.indexBuffer.Unbind();
        mesh.vertexArray.Unbind();

        return mesh;
    }

    void LogMeshInfo(const Mesh& mesh)
    {
        INFO("=======Mesh info=======");
        INFO("Mesh vertex count : %d", mesh.vertices.size());
        INFO("Mesh index count  : %d", mesh.indices.size());
        INFO("Mesh VAO ID       : %d", mesh.vertexArray.id);
        INFO("Mesh VBO ID       : %d", mesh.vertexBuffer.id);
        INFO("Mesh EBO ID       : %d", mesh.indexBuffer.id);
    }

    void UnloadMesh(Mesh& mesh)
    {
        mesh.vertices = std::vector<Vertex>();
        mesh.indices = std::vector<u32>();

        DeleteVertexArray(mesh.vertexArray);
        DeleteVertexBuffer(mesh.vertexBuffer);
        DeleteIndexBuffer(mesh.indexBuffer);
    }

}
