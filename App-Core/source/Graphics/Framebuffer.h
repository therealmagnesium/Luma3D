#pragma once
#include "Core/Base.h"

namespace Graphics
{
    struct Framebuffer
    {
        u32 id = 0;
        u32 width = 0;
        u32 height = 0;
        u32 colorAttachment = 0;
        u32 depthAttachment = 0;

        void Bind();
        void Unbind();
    };

    Framebuffer CreateFramebuffer(u32 width, u32 height);
    void DeleteFramebuffer(Framebuffer& framebuffer);
}
