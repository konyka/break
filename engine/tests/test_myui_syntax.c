#include "test_framework.h"

#include "myr/my_syntax.h"

typedef struct syntax_count_allocator_t {
  size_t alloc_calls;
  size_t realloc_calls;
} syntax_count_allocator_t;

static void* syntax_count_alloc(void* ctx, size_t size)
{
  syntax_count_allocator_t* state = (syntax_count_allocator_t*)ctx;
  void* result = malloc(size);
  if (result != NULL) state->alloc_calls++;
  return result;
}

static void* syntax_count_calloc(void* ctx, size_t count, size_t size)
{
  syntax_count_allocator_t* state = (syntax_count_allocator_t*)ctx;
  void* result = calloc(count, size);
  if (result != NULL) state->alloc_calls++;
  return result;
}

static void* syntax_count_realloc(void* ctx, void* ptr, size_t size)
{
  syntax_count_allocator_t* state = (syntax_count_allocator_t*)ctx;
  void* result = realloc(ptr, size);
  if (result != NULL) state->realloc_calls++;
  return result;
}

static void syntax_count_free(void* ctx, void* ptr)
{
  (void)ctx;
  free(ptr);
}

static my_allocator_t syntax_count_allocator = {
    .ctx = NULL,
    .alloc = syntax_count_alloc,
    .calloc = syntax_count_calloc,
    .realloc = syntax_count_realloc,
    .free = syntax_count_free};

TEST(syntax_edit_keeps_stable_suffix_ready)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);
  size_t count = 0;

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache, "int first;\nint second;\nint third;"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 2));

  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "long first;"), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 2));
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 2));
  ASSERT_NOT_NULL(my_syntax_cache_line_tokens(cache, 1, &count));
  ASSERT_TRUE(count > 0u);

  my_syntax_cache_destroy(cache);
}

TEST(syntax_edit_propagates_block_state_until_convergence)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);
  const my_syntax_token_t* tokens;
  size_t count = 0;

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache,
                                     "/*\ninside\n*/\nint value;"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 3));

  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "int header;"), MY_RET_OK);
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 2));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 3));

  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 2));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 3));

  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 3));
  tokens = my_syntax_cache_line_tokens(cache, 1, &count);
  ASSERT_NOT_NULL(tokens);
  ASSERT_TRUE(count > 0u);
  ASSERT_EQ(tokens[0].kind, MY_SYNTAX_TOKEN_IDENTIFIER);

  my_syntax_cache_destroy(cache);
}

TEST(syntax_state_propagation_stops_after_state_convergence)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache,
                                     "/*\ninside\n*/\nint value;\nint tail;"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "int header;"), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 4), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 2));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 3));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 4));

  my_syntax_cache_destroy(cache);
}

TEST(syntax_state_convergence_does_not_skip_later_source_edit)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache,
                                     "/*\ninside\n*/\nint value;\nint tail;"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "int header;"), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 4), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 3));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 4));
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 3, "/* changed"),
            MY_RET_OK);
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 3));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 4));
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 4));

  my_syntax_cache_destroy(cache);
}

TEST(syntax_stable_suffix_reuses_snapshot_without_allocation)
{
  syntax_count_allocator_t state = {0};
  syntax_count_allocator.ctx = &state;
  my_syntax_cache_t* cache =
      my_syntax_cache_create(&syntax_count_allocator, MY_SYNTAX_C_LIKE);
  size_t alloc_calls;
  size_t realloc_calls;

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache,
                                     "int first;\nint second;\nint tail;"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "long first;"), MY_RET_OK);
  alloc_calls = state.alloc_calls;
  realloc_calls = state.realloc_calls;
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_EQ(state.alloc_calls, alloc_calls);
  ASSERT_EQ(state.realloc_calls, realloc_calls);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 2));

  my_syntax_cache_destroy(cache);
}

TEST(syntax_comment_markers_inside_strings_do_not_propagate_state)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache,
                                     "const char* text = \"/*\";\n"
                                     "int tail;"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0,
                                         "const char* text = \"//\";"),
            MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));

  my_syntax_cache_destroy(cache);
}

TEST(syntax_yaml_edits_never_propagate_c_block_state)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_YAML);

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache, "key: value\nnext: item"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 8), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "key: changed"),
            MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 1));

  my_syntax_cache_destroy(cache);
}

TEST_MAIN_BEGIN()
  RUN_TEST(syntax_edit_keeps_stable_suffix_ready);
  RUN_TEST(syntax_edit_propagates_block_state_until_convergence);
  RUN_TEST(syntax_state_propagation_stops_after_state_convergence);
  RUN_TEST(syntax_state_convergence_does_not_skip_later_source_edit);
  RUN_TEST(syntax_stable_suffix_reuses_snapshot_without_allocation);
  RUN_TEST(syntax_comment_markers_inside_strings_do_not_propagate_state);
  RUN_TEST(syntax_yaml_edits_never_propagate_c_block_state);
TEST_MAIN_END()
