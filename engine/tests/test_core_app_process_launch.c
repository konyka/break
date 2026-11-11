#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32)
#include <windows.h>
#endif

int main(int argc, char **argv) {
    if (argc != 2 || argv[1][0] == '\0') return 2;
    errno = 0;
    int raw = system(argv[1]);
    int saved_errno = errno;
#if defined(_WIN32)
    unsigned long os_error = (unsigned long)GetLastError();
#else
    unsigned long os_error = 0;
#endif
    printf("CORE_APP_PROCESS_LAUNCH command=%s raw=%d os_error=%lu errno=%d\n",
           argv[1], raw, os_error, saved_errno);
    return raw == 0 ? 0 : 1;
}
