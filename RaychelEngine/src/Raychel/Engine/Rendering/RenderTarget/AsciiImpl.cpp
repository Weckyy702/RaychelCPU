#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

#ifndef RAYCHEL_USE_NCURSES_FALLBACK
//we have ncurses, yay :)

    #include <ncurses.h>

namespace Raychel::details {

    struct ConsoleManager::Impl_
    {
        Impl_() noexcept
        {
            initscr();
            cbreak();
            noecho();
            //TODO: implement color handling
        }

        RAYCHEL_MAKE_DEFAULT_COPY(Impl_);
        RAYCHEL_MAKE_DEFAULT_MOVE(Impl_);

        ~Impl_() noexcept
        {
            clear();
            endwin();
        }
    };

    void ConsoleManager::do_framebuffer_write(const Texture<RenderResult>& framebuffer) noexcept
    {
        const auto owner_size = owner_->size();
        const auto& owner_charset = owner_->character_set_;

        for (size_t j = 0U; j < owner_size.y; j++) {
            for (size_t i = 0U; i < owner_size.x; i++) {
                auto col = framebuffer.at(vec2i{owner_size.x - 1 - i, j}).output;

                const auto col_brightness = brightness(col);
                const auto character_index = static_cast<size_t>(col_brightness * static_cast<float>(owner_charset.size() - 1));
                const char c = owner_charset.at(character_index);

                mvaddch(owner_size.y - j, owner_size.x - i, c);
            }
        }
        refresh();
    }

} // namespace Raychel::details

#elif defined(_WIN32)

//TODO: implement

#else
    #error "Unknown operating system"
#endif

namespace Raychel::details {

    ConsoleManager::ConsoleManager(const AsciiTarget* _owner) : owner_{_owner}
    {
        impl_ = new Impl_();
    }

    ConsoleManager::~ConsoleManager() noexcept
    {
        delete impl_;
    }

} // namespace Raychel::details