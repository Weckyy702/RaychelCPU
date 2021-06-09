#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

#ifndef RAYCHEL_USE_NCURSES_FALLBACK
    #include <ncurses.h>
#endif

namespace Raychel {

    int getColorPaletteIndex(const color&);

    AsciiTarget::AsciiTarget(const vec2i& size, bool use_color) : RenderTarget(size), use_color_{use_color}
    {
        _init_ncurses();
    }

    AsciiTarget::AsciiTarget(const vec2i& size, bool use_color, const std::vector<char>& char_set)
        : RenderTarget(size), character_set_{char_set}, use_color_{use_color}
    {
        _init_ncurses();
    }

    void AsciiTarget::writeFramebuffer(const Texture<RenderResult>& framebuffer)
    {
        for (size_t j = 0U; j < size().y; j++) {
            for (size_t i = 0U; i < size().x; i++) {
                auto col = framebuffer.at(vec2i{size().x - 1 - i, j}).output;

                auto col_brightness = brightness(col);
                size_t character_index = static_cast<size_t>(col_brightness * (character_set_.size() - 1));

#ifndef RAYCHEL_USE_NCURSES_FALLBACK
                char c = character_set_.at(character_index);

                if (use_color_ && has_colors()) {
                    auto color_index = getColorPaletteIndex(col);
                    attron(COLOR_PAIR(color_index));
                    mvaddch(size().y - j, i, c);
                    attroff(COLOR_PAIR(color_index));
                } else {
                    mvaddch(size().y - j, size().x - i, c);
                }
            }
        }
        refresh();
#else
                std::cout.write(character_set_.data() + character_index, 1);
            }
            std::cout << std::endl;
        }
        std::cout.write("\x1b[2J\x1b[H", 8);
#endif
    }

    void AsciiTarget::finishFramebufferWrite()
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20ms); //~50fps
    }

    AsciiTarget::~AsciiTarget()
    {
#ifndef RAYCHEL_USE_NCURSES_FALLBACK
        clear();
        endwin();
#endif
    }

    void AsciiTarget::_init_ncurses() const
    {
#ifndef RAYCHEL_USE_NCURSES_FALLBACK
        initscr();
        cbreak();
        noecho();

        if (use_color_ && has_colors()) {
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            init_pair(2, COLOR_GREEN, COLOR_BLACK);
            init_pair(3, COLOR_BLUE, COLOR_BLACK);
        }

        clear();
#endif
    }

    int getColorPaletteIndex(const color& col)
    {
        if (col.r > col.g) {
            if (col.b > col.r) {
                return 3;
            }
            return 1;
        }
        if (col.b > col.g) {
            return 3;
        }
        if (col.b != 0) {
            return 2;
        }
        return 0;
    }

} // namespace Raychel