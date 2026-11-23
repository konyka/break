#include "test_framework.h"

int main(int argc, char **argv) {
    char path[128];
    if (argc > 1 && strcmp(argv[1], "tmp") == 0) {
        (void)test_tmp(path, sizeof(path), "x");
    } else {
        (void)test_tmp_root();
    }
    (void)g_test_count;
    (void)g_test_pass;
    (void)g_test_fail;
    return 0;
}
