#include <stdlib.h>

int main(void)
{
    void *volatile allocation = malloc(123u);
    (void)allocation;
    return 0;
}
