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
        const auto write_time_ms = Logger::getTimer("Ascii_render_time").count();
        if(write_time_ms != -1) {
            const auto sleep_time = std::max<decltype(write_time_ms)>(0, 33-write_time_ms);

            RAYCHEL_LOG("Sleeping for ", sleep_time, "ms");

            std::this_thread::sleep_for(std::chrono::milliseconds{sleep_time}); //~30fps
        }
        Logger::startTimer("Ascii_render_time");
    }
} // namespace Raychel