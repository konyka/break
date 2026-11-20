#include <stdlib.h>

static void *(*volatile indirect_malloc)(size_t) = malloc;

int main(void)
{
    (void)indirect_malloc(123);
    return 0;
}
