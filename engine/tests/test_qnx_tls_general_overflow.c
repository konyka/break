#include <stdlib.h>
#include <string.h>

static void *(*volatile indirect_memset)(void *, int, size_t) = memset;

int main(void)
{
    void *p = malloc(8);
    if (!p) return 2;
    indirect_memset(p, 0, 9);
    free(p);
    return 0;
}
