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

        static constexpr std::array<color, 8> ncurses_colors{
            color{0, 0, 0},
            color{1, 0, 0},
            color{0, 1, 0},
            color{1, 1, 0},
            color{0, 0, 1},
            color{1, 0, 1},
            color{0, 1, 1},
            color{1, 1, 1}};

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

        void output_character(size_t _x, size_t _y, char c, const color& col) const noexcept
        {
            RAYCHEL_ASSERT(_x < std::numeric_limits<int>::max());
            RAYCHEL_ASSERT(_y < std::numeric_limits<int>::max());

            const auto x = static_cast<int>(_x);
            const auto y = static_cast<int>(_y);

            if (use_color_) {
                //TODO: implement finding the correct color
                const auto ncurses_col = _find_closest_ncurses_col(col);
                attron(COLOR_PAIR(ncurses_col)); //NOLINT: we can't change what ncurses does
                mvaddch(y, x, c);
                attroff(COLOR_PAIR(ncurses_col)); //NOLINT: we can't change what ncurses does
            } else {
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

            for (NCURSES_COLOR_T i = 0; i < 8; i++) {

                if (distSq(vec3{col}, vec3{ncurses_colors.at(i)}) < min_dist) {
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

        for (size_t i = 0U; i < owner_size.x; i++) {
            for (size_t j = 0U; j < owner_size.y; j++) {
                auto col = framebuffer.at(vec2i{owner_size.x - 1 - i, j}).output;

                const auto col_brightness = brightness(col);
                const char c = get_char_from_brightness(col_brightness);

                impl_->output_character(owner_size.x - i, owner_size.y - j, c, col);
            }
        }
        refresh();
    }

} // namespace Raychel::details

#elif defined(_WIN32)

    #define NOMINMAX //Why Microsoft? WHY?!?
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

namespace Raychel::details {

    class ConsoleManager::Impl_
    {
    public:
        Impl_(bool use_color) : hConsole_{GetStdHandle(STD_OUTPUT_HANDLE)}, use_color_{use_color}
        {
            RAYCHEL_ASSERT(hConsole_ != NULL);
        }

        void output_character(char c, size_t _x, size_t _y, const color& col) const noexcept
        {
            RAYCHEL_ASSERT(_x < std::numeric_limits<SHORT>::max());
            RAYCHEL_ASSERT(_y < std::numeric_limits<SHORT>::max());

            const auto x = static_cast<SHORT>(_x);
            const auto y = static_cast<SHORT>(_y);

            SetConsoleCursorPosition(hConsole_, {x, y});

            if (use_color_) {
                const WORD console_color = _get_closest_console_color(col);

                SetConsoleTextAttribute(hConsole_, console_color);
            }
            WriteConsoleA(hConsole_, &c, 1, nullptr, NULL);
        }

        ~Impl_() noexcept
        {}

    private:
        WORD _get_closest_console_color(const color& col) const noexcept
        {
            WORD res = 0;

            if (col.r > 0.5f) {
                res |= FOREGROUND_RED;
            }
            if (col.g > 0.5f) {
                res |= FOREGROUND_GREEN;
            }
            if (col.b > 0.5f) {
                res |= FOREGROUND_BLUE;
            }

            return res;
        }

        const HANDLE hConsole_;
        const bool use_color_;
    };

    void ConsoleManager::do_framebuffer_write(const Texture<RenderResult>& framebuffer) noexcept
    {
        (void)framebuffer;
        const auto owner_size = owner_->size();
        for (size_t x = 0; x < owner_size.x; x++) {
            for (size_t y = 0; y < owner_size.y; y++) {
                const auto& col = framebuffer.at(vec2i{x, y}).output;

                const auto b = brightness(col);
                const char c = get_char_from_brightness(b);

                impl_->output_character(c, x, y, col);
            }
        }
    }

} // namespace Raychel::details

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

    char ConsoleManager::get_char_from_brightness(float brightness) const noexcept
    {
        const auto& owner_charset = owner_->character_set_;

        const auto character_index = static_cast<size_t>(brightness * static_cast<float>(owner_charset.size() - 1));
        return owner_charset.at(character_index);
    }

} // namespace Raychel::details