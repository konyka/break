#include "rule_engine/backward_machine_context.h"
#include "test_framework.h"
#include <stdlib.h>

static size_t freed_count;

static void *test_alloc(void *context, size_t size) {
    (void)context;
    return malloc(size);
}

static void *test_realloc(void *context, void *memory, size_t size) {
    (void)context;
    return realloc(memory, size);
}

static void test_free(void *context, void *memory) {
    (void)context;
    free(memory);
    ++freed_count;
}

static re_allocator_impl_t test_allocator(void) {
    re_allocator_impl_t allocator;
    allocator.api.context = NULL;
    allocator.api.alloc = test_alloc;
    allocator.api.realloc = test_realloc;
    allocator.api.free = test_free;
    return allocator;
}

TEST(context_assigns_stable_ids_and_resets_frames) {
    re_allocator_impl_t allocator = test_allocator();
    re_backward_machine_context_t context;
    re_backward_machine_frame_id_t first;
    re_backward_machine_frame_id_t second;
    ASSERT_EQ(re_backward_machine_context_init(&context, &allocator), RE_STATUS_OK);
    ASSERT_EQ(re_backward_machine_context_push(&context, RE_BACKWARD_FRAME_GOAL_SELECT,
                                               RE_BACKWARD_MACHINE_FRAME_ID_INVALID,
                                               RE_BACKWARD_FRAME_BORROWED, &first), RE_STATUS_OK);
    ASSERT_EQ(re_backward_machine_context_push(&context, RE_BACKWARD_FRAME_RETURN, first,
                                               RE_BACKWARD_FRAME_OWNS_ENVIRONMENT, &second), RE_STATUS_OK);
    ASSERT_EQ(first, 0u);
    ASSERT_EQ(second, 1u);
    ASSERT_EQ(re_backward_machine_context_frame(&context, second)->parent_id, first);
    re_backward_machine_context_reset(&context);
    ASSERT_EQ(context.frame_count, 0u);
    ASSERT_EQ(re_backward_machine_context_push(&context, RE_BACKWARD_FRAME_GOAL_SELECT,
                                               RE_BACKWARD_MACHINE_FRAME_ID_INVALID,
                                               RE_BACKWARD_FRAME_BORROWED, &second), RE_STATUS_OK);
    ASSERT_EQ(second, 2u);
    ASSERT_TRUE(re_backward_machine_context_frame(&context, first) == NULL);
    re_backward_machine_context_destroy(&context);
}

TEST(frame_init_and_reset_preserve_explicit_lifecycle_contract) {
    re_backward_machine_frame_t frame;
    re_backward_machine_frame_init(&frame, RE_BACKWARD_FRAME_CONDITION_CONTINUE, 7u,
                                   RE_BACKWARD_FRAME_OWNS_ENVIRONMENT);
    ASSERT_EQ(frame.state, RE_BACKWARD_FRAME_CONDITION_CONTINUE);
    ASSERT_EQ(frame.parent_id, 7u);
    ASSERT_EQ(frame.ownership, RE_BACKWARD_FRAME_OWNS_ENVIRONMENT);
    re_backward_machine_frame_reset(&frame);
    ASSERT_EQ(frame.id, RE_BACKWARD_MACHINE_FRAME_ID_INVALID);
    ASSERT_EQ(frame.parent_id, RE_BACKWARD_MACHINE_FRAME_ID_INVALID);
}

TEST(environment_transfer_moves_storage_and_trace_cleanup_restores_checkpoint) {
    re_allocator_impl_t allocator = test_allocator();
    re_backward_machine_context_t context;
    re_backward_machine_environment_t source = {(void *)1, 2u, 4u};
    re_backward_machine_environment_t destination = {NULL, 0u, 0u};
    ASSERT_EQ(re_backward_machine_context_init(&context, &allocator), RE_STATUS_OK);
    ASSERT_EQ(re_backward_machine_environment_transfer(&destination, &source), RE_STATUS_OK);
    ASSERT_EQ(destination.items, (void *)1);
    ASSERT_EQ(source.items, NULL);
    context.trace.count = 3u;
    ASSERT_EQ(re_backward_machine_trace_checkpoint(&context), 3u);
    re_backward_machine_trace_cleanup(&context, 1u);
    ASSERT_EQ(context.trace.count, 1u);
    re_backward_machine_context_destroy(&context);
}

TEST(context_reset_releases_owned_environment_storage) {
    re_allocator_impl_t allocator = test_allocator();
    re_backward_machine_context_t context;
    re_backward_machine_frame_id_t id;
    re_backward_machine_frame_t *frame;
    void *items;
    freed_count = 0u;
    ASSERT_EQ(re_backward_machine_context_init(&context, &allocator), RE_STATUS_OK);
    ASSERT_EQ(re_backward_machine_context_push(&context, RE_BACKWARD_FRAME_RETURN,
                                               RE_BACKWARD_MACHINE_FRAME_ID_INVALID,
                                               RE_BACKWARD_FRAME_OWNS_ENVIRONMENT, &id), RE_STATUS_OK);
    frame = re_backward_machine_context_frame(&context, id);
    items = calloc(1u, sizeof(re_backward_machine_binding_t));
    ASSERT_NOT_NULL(items);
    frame->environment.items = items;
    frame->environment.count = 1u;
    frame->environment.capacity = 1u;
    re_backward_machine_context_reset(&context);
    ASSERT_EQ(freed_count, 1u);
    re_backward_machine_context_destroy(&context);
    ASSERT_EQ(freed_count, 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(context_assigns_stable_ids_and_resets_frames);
    RUN_TEST(frame_init_and_reset_preserve_explicit_lifecycle_contract);
    RUN_TEST(environment_transfer_moves_storage_and_trace_cleanup_restores_checkpoint);
    RUN_TEST(context_reset_releases_owned_environment_storage);
TEST_MAIN_END()
