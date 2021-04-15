#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#ifndef _WIN32
    #include <ncurses.h>
#else
    #define RAYCHEL_USE_NCURSES_FALLBACK
#endif

#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

namespace Raychel {

    int getColorPaletteIndex(const color&);

    AsciiTarget::AsciiTarget(const vec2i& size, bool use_color)
        :RenderTarget(size), use_color_{use_color}
    {
        _init_ncurses();
    }

    AsciiTarget::AsciiTarget(const vec2i& size, bool use_color, const std::vector<char>& char_set)
        :RenderTarget(size), character_set_{char_set}, use_color_{use_color}
    {
        _init_ncurses();
    } 

    void AsciiTarget::writeFramebuffer(const Texture<RenderResult>& framebuffer)
    {
        for(size_t  i = 0; i < size().y; i++) {
            for(size_t j = 0; j < size().x; j++) {
                auto index_1D = (i * size().x) + j;

                auto col = framebuffer.at(index_1D).output;
                auto col_brightness = brightness(col);
                size_t character_index = static_cast<size_t>(col_brightness * (character_set_.size()-1));

        #ifndef RAYCHEL_USE_NCURSES_FALLBACK
                char c = character_set_.at(character_index);
                
                if(use_color_ && has_colors()) {
                    auto color_index = getColorPaletteIndex(col);
                    attron(COLOR_PAIR(color_index));
                    mvaddch(i, j, c);
                    attroff(COLOR_PAIR(color_index));
                } else {
                    mvaddch(i, j, c);
                }

                
            }
        }
        refresh();
        #else
            std::cout.write(character_set_.data()+character_index, 1);
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

            if(use_color_ && has_colors()) {
                start_color();
                init_pair(1, COLOR_RED, COLOR_BLACK);
                init_pair(2, COLOR_GREEN, COLOR_BLACK);
                init_pair(3, COLOR_BLUE, COLOR_BLACK);
            }

            clear();
        #endif
    }



    int getColorPaletteIndex(const color& col) {
        if(col.r > col.g) {
            if(col.b > col.r) {
                return 3;
            } else {
                return 1;
            }
        } else {
            if(col.b > col.g) {
                return 3;
            } else if(col.b != 0) {
                return 2;
            }
        }
        return 0;
    }

}