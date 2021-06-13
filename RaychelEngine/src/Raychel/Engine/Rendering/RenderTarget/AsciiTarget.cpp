#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

#ifndef RAYCHEL_USE_NCURSES_FALLBACK
    #include <ncurses.h>
#endif

namespace Raychel {

    void AsciiTarget::writeFramebuffer(const Texture<RenderResult>& framebuffer)
    {
        manager_.do_framebuffer_write(framebuffer);
    }

    void AsciiTarget::finishFramebufferWrite()
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(41ms); //~24fps
    }
} // namespace Raychel