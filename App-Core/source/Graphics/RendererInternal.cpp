#include "Graphics/RendererInternal.h"
#include "Core/Log.h"
#include <glad/glad.h>

namespace Graphics
{
    VertexArray CreateVertexArray()
    {
        VertexArray vao;
        glGenVertexArrays(1, &vao.id);
        vao.isInitialized = true;

        return vao;
    }

    void DeleteVertexArray(VertexArray& vao)
    {
        glDeleteVertexArrays(1, &vao.id);
        vao.isInitialized = false;
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(id);
        isSelected = true;
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
        isSelected = false;
    }

    void VertexArray::StoreInAtrribList(u32 location, u32 numElements, u64 offset)
    {
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, numElements, GL_FLOAT, false, sizeof(Vertex), (void*)offset);
    }

    VertexBuffer CreateVertexBuffer()
    {
        VertexBuffer vbo;
        glGenBuffers(1, &vbo.id);
        vbo.isInitialized = true;

        return vbo;
    }

    void DeleteVertexBuffer(VertexBuffer& vbo)
    {
        glDeleteBuffers(1, &vbo.id);
        vbo.isInitialized = false;
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SendData(float* data, u64 dataSize)
    {
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }

    IndexBuffer CreateIndexBuffer()
    {
        IndexBuffer ebo;
        glGenBuffers(1, &ebo.id);
        ebo.isInitialized = true;

        return ebo;
    }

    void DeleteIndexBuffer(IndexBuffer& ebo)
    {
        glDeleteBuffers(1, &ebo.id);
        ebo.isInitialized = false;
    }

    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::SendData(u32* data, u64 dataSize)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    }
}
