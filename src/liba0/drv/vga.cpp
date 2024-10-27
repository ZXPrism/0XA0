#include "vga.h"

#include <stdint.h>

namespace liba0 {

    constexpr uint32_t _VGA_BASE = 0xB8000;

    uint32_t _VGAColor;
    uint32_t _VGACursorPosRow, _VGACursorPosCol;

    void _VGAPutEntry(char ch, uint32_t row, uint32_t col, uint32_t color) {
        uint16_t *vgaBuffer = reinterpret_cast<uint16_t *>(_VGA_BASE);
        uint32_t index = VGA_WIDTH * row + col;

        vgaBuffer[index] = static_cast<uint16_t>(color << 8 | ch);
    }

    uint32_t _VGAMakeColor(VGAColor fgColor, VGAColor bgColor) {
        return static_cast<uint32_t>(bgColor) << 4 |
               static_cast<uint32_t>(fgColor);
    }

    void VGAInitTerminal() {
        _VGAColor = _VGAMakeColor(VGAColor::WHITE, VGAColor::BLACK);
        _VGACursorPosRow = 0;
        _VGACursorPosCol = 0;

        uint16_t *vgaBuffer = reinterpret_cast<uint16_t *>(_VGA_BASE);

        for (uint32_t row = 0, index = 0; row < VGA_WIDTH; row++) {
            for (uint32_t col = 0; col < VGA_HEIGHT; col++) {
                vgaBuffer[index++] = ' ';
            }
        }
    }

    void VGASetTextColor(VGAColor fgColor, VGAColor bgColor) {
        _VGAColor = _VGAMakeColor(fgColor, bgColor);
    }

    void VGASetCursorPos(uint32_t row, uint32_t col) {
        _VGACursorPosRow = row;
        _VGACursorPosCol = col;
    }

    void VGAPutChar(char ch) {
        if (ch == '\n') {
            _VGACursorPosRow = (_VGACursorPosRow + 1) % VGA_HEIGHT;
            _VGACursorPosCol = 0;
        } else {
            _VGAPutEntry(ch, _VGACursorPosRow, _VGACursorPosCol, _VGAColor);
            _VGACursorPosCol = (_VGACursorPosCol + 1) % VGA_WIDTH;
            if (_VGACursorPosCol == 0) {
                _VGACursorPosRow = (_VGACursorPosRow + 1) % VGA_HEIGHT;
            }
        }
    }

} // namespace liba0
