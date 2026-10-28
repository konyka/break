#include <ecs/world_delta.h>

#ifdef BREAK_WORLD_DELTA_TESTING
static usize delta_test_fail_after_mutation;
static bool delta_test_fail_final_validation;

void break_world_delta_test_fail_after_mutation(usize mutation_count)
{
    delta_test_fail_after_mutation = mutation_count;
}

void break_world_delta_test_fail_final_validation(bool enabled)
{
    delta_test_fail_final_validation = enabled;
}

bool break_world_delta_test_mutation_fault(void)
{
    if (delta_test_fail_after_mutation == 0u) return false;
    --delta_test_fail_after_mutation;
    return delta_test_fail_after_mutation == 0u;
}

bool break_world_delta_test_final_validation_fault(void)
{
    return delta_test_fail_final_validation;
}
#endif
