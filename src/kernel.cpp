#include "liba0/drv/vga.h"
#include "liba0/io/stdio.h"

extern "C" void kernel_main() {
    liba0::VGAInitTerminal();
    liba0::VGASetTextColor(liba0::VGAColor::LIGHT_GREEN,
                           liba0::VGAColor::BLACK);
    liba0::print("Hello, World!!\nLalala");
}
