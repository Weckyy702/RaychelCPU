#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

#ifndef RAYCHEL_USE_NCURSES_FALLBACK
//we have ncurses, yay :)

    #include <ncurses.h>

namespace Raychel::details {

    class ConsoleManager::Impl_
    {
    private:
        enum ncurses_color : NCURSES_COLOR_T {
            black = COLOR_BLACK,
            red = COLOR_RED,
            green = COLOR_GREEN,
            yellow = COLOR_YELLOW,
            blue = COLOR_BLUE,
            magenta = COLOR_MAGENTA,
            cyan = COLOR_CYAN,
            white = COLOR_WHITE,
        };

        static constexpr std::array<color, 8> ncurses_colors {
            color{0, 0, 0},
            color{1, 0, 0},
            color{0, 1, 0},
            color{1, 1, 0},
            color{0, 0, 1},
            color{1, 0, 1},
            color{0, 1, 1},
            color{1, 1, 1}
        };

        static constexpr ncurses_color bg_color = black;

    public:
        explicit Impl_(bool use_color) noexcept
        {
            initscr();
            cbreak();
            noecho();

            //this needs to happen here and not in the initializer list, because the console is not initilized at that point
            use_color_ = use_color && has_colors();

            _init_colors_if_necessary();
        }

        RAYCHEL_MAKE_NONCOPY_NONMOVE(Impl_);

        ~Impl_() noexcept
        {
            clear();
            endwin();
        }

        void output_character(size_t x, size_t y, char c, const color& col) const noexcept
        {
            if (use_color_) {
                //TODO: implement finding the correct color
                const auto ncurses_col = _find_closest_ncurses_col(col);
                attron(COLOR_PAIR(ncurses_col)); //NOLINT: we can't change what ncurses does
                mvaddch(y, x, c);
                attroff(COLOR_PAIR(ncurses_col)); //NOLINT: we can't change what ncurses does
            } else {
                (void)col;
                mvaddch(y, x, c);
            }
        }

    private:
        void _init_colors_if_necessary() const
        {
            if (use_color_) {
                RAYCHEL_LOG("Initializing color output mode\n");
                start_color();
                _init_ncurses_color_pairs();
            }
        }

        void _init_ncurses_color_pairs() const noexcept
        {
            _init_color(black);
            _init_color(white);
            _init_color(red);
            _init_color(green);
            _init_color(blue);
            _init_color(yellow);
            _init_color(cyan);
            _init_color(magenta);
        }

        //NOLINTNEXTLINE(readability-convert-member-functions-to-static): these shouldn't be static
        void _init_color(ncurses_color color) const noexcept
        {
            //kind of confusing that the color indices are also the colors themselves, but who cares
            init_pair(color, color, bg_color);
            //black is represented by a dot, black would make it invisible
        }

        [[nodiscard]] static ncurses_color _find_closest_ncurses_col(const color& col) noexcept
        {
            ncurses_color res = black;
            float min_dist = 1000;
            for(NCURSES_COLOR_T i = 0; i < 8; i++) {
                if(distSq(vec3{col}, vec3{ncurses_colors.at(i)}) < min_dist) {
                    min_dist = distSq(vec3{col}, vec3{ncurses_colors.at(i)});

                    res = static_cast<ncurses_color>(i); //OOF, this hurts :( TODO: make this good
                }
            }
            return res;
        }

        bool use_color_{false};
    };

    void ConsoleManager::do_framebuffer_write(const Texture<RenderResult>& framebuffer) noexcept
    {
        const auto owner_size = owner_->size();
        const auto& owner_charset = owner_->character_set_;

        for (size_t i = 0U; i < owner_size.x; i++) {
            for (size_t j = 0U; j < owner_size.y; j++) {
                auto col = framebuffer.at(vec2i{owner_size.x - 1 - i, j}).output;

                const auto col_brightness = brightness(col);
                const auto character_index = static_cast<size_t>(col_brightness * static_cast<float>(owner_charset.size() - 1));
                const char c = owner_charset.at(character_index);

                impl_->output_character(owner_size.x - i, owner_size.y - j, c, col);
            }
        }
        refresh();
    }

} // namespace Raychel::details

#elif defined(_WIN32)

//TODO: implement

#elif defined(RAYCHEL_USE_NCURSES_FALLBACK)

//TODO: implement

#else
    #error "Unknown operating system"
#endif

namespace Raychel::details {

    ConsoleManager::ConsoleManager(const AsciiTarget* _owner) : owner_{_owner}
    {
        impl_ = new Impl_(_owner->use_color_);
    }

    ConsoleManager::~ConsoleManager() noexcept
    {
        delete impl_;
    }

} // namespace Raychel::details