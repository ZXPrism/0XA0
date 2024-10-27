#include "string.h"

namespace liba0 {

    int strlen(const char *s) {
        int res = 0;
        while (s[res]) {
            ++res;
        }
        return res;
    }

} // namespace liba0
