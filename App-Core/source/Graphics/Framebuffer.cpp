#include "Graphics/Framebuffer.h"
#include "Core/Base.h"

#include <glad/glad.h>

namespace Graphics
{
    Framebuffer CreateFramebuffer(u32 width, u32 height)
    {
        Framebuffer framebuffer;
        framebuffer.width = width;
        framebuffer.height = height;

        glGenFramebuffers(1, &framebuffer.id);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.id);

        glGenTextures(1, &framebuffer.colorAttachment);
        glBindTexture(GL_TEXTURE_2D, framebuffer.colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, framebuffer.width, framebuffer.height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                               framebuffer.colorAttachment, 0);

        glGenRenderbuffers(1, &framebuffer.depthAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, framebuffer.depthAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer.width,
                              framebuffer.height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                  framebuffer.depthAttachment);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return framebuffer;
    }

    void DeleteFramebuffer(Framebuffer& framebuffer)
    {
        glDeleteFramebuffers(1, &framebuffer.id);
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
