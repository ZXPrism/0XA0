#include "stdio.h"

#include "liba0/drv/vga.h"
#include "liba0/string/string.h"

namespace liba0 {

    void print(const char *text) {
        int len = strlen(text);
        for (int i = 0; i < len; i++) {
            VGAPutChar(text[i]);
        }
    }

} // namespace liba0
