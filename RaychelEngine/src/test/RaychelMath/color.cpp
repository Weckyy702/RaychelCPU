#define RAYCHEL_NO_LOGGER
#include "Raychel/Core/RaychelMath/color.h"
#include "Raychel/Core/RaychelMath/Impl/colorImpl.inl"

using Raychel::colorImp, Raychel::brightness;
using color = colorImp<double>;


constexpr colorImp<float> get_color() noexcept
{
    color c{1, 0, 1};
    c *= 2.0;
    c *= color{1, 0.1, 2};
    c += color{0, 1, 0};

    if (c == color{2, 1, 4}) {
        const auto b = brightness(c);
        c.r = c.g = c.b = b;
    } else {
        const auto b = 12;
        c.r *= b;
    }

    return c.to<float>();
}

int main(int /*unused*/, char** /*unused*/) {
    //all of these would be ill-formed without constexpr colors :^)
    constexpr auto c = get_color();
    constexpr size_t l = brightness(c);
    std::array<char, l> arr{};

    std::cout << c << ", " << arr.size() << '\n';

    return 0;
}