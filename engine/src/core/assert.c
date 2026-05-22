#include <core/assert.h>
#include <stdio.h>
#include <stdlib.h>

void engine_assert_fail(const char *cond, const char *file,
                        int line, const char *func,
                        const char *msg) {
    const char *basename = file;
    for (const char *p = file; *p; p++) {
        if (*p == '/') basename = p + 1;
    }
    fprintf(stderr, "\033[31mASSERT FAILED\033[0m %s:%d in %s\n"
                    "  Condition: %s\n"
                    "  Message:   %s\n",
            basename, line, func, cond, msg ? msg : "(none)");
    abort();
}
