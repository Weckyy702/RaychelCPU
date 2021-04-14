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

    AsciiTarget::AsciiTarget(const vec2i& size)
        :RenderTarget(size)
    {
        _init_ncurses();
    }

    AsciiTarget::AsciiTarget(const vec2i& size, const std::vector<char>& char_set)
        :RenderTarget(size), character_set_{char_set}
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
                mvaddch(i, j, c);
                
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
        #endif
    }

}