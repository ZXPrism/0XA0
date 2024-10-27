#pragma once

#include <stdint.h>

namespace liba0 {

    enum class VGAColor : uint8_t {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GREY = 7,
        DARK_GREY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        LIGHT_BROWN = 14,
        WHITE = 15
    };

    constexpr uint32_t VGA_WIDTH = 80;
    constexpr uint32_t VGA_HEIGHT = 25;

    void VGAInitTerminal();
    void VGASetTextColor(VGAColor fgColor, VGAColor bgColor);
    void VGASetCursorPos(uint32_t row, uint32_t col);
    void VGAPutChar(char ch);

} // namespace liba0
