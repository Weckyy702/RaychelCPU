#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

#include <thread>

namespace Raychel {

    void AsciiTarget::writeFramebuffer(const Texture<RenderResult>& framebuffer)
    {
        manager_.do_framebuffer_write(framebuffer);
    }

    void AsciiTarget::finishFramebufferWrite()
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(33ms); //~30fps
    }
} // namespace Raychel