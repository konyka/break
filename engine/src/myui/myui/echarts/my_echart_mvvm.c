#include "myui/echarts/my_echart_mvvm.h"
#include <string.h>
struct my_echart_mvvm_binding_t { const my_allocator_t* allocator; my_binding_context_t* context; my_echart_adapter_t* adapter; char* property; };
static my_ret_t sync_binding(my_echart_mvvm_binding_t* b) {
  my_view_model_t* vm = my_binding_context_get_view_model(b->context); my_value_t value; my_ret_t r;
  if (vm == NULL) return MY_RET_INVALID_PARAMS;
  my_value_init(&value, NULL);
  r = my_view_model_get_prop(vm, b->property, &value);
  if (r == MY_RET_OK && my_value_type(&value) == MY_VALUE_POINTER) r = my_echart_adapter_apply(b->adapter, my_value_get_pointer(&value));
  else if (r == MY_RET_OK) r = MY_RET_INVALID_PARAMS;
  my_value_reset(&value); return r;
}
my_echart_mvvm_binding_t* my_echart_mvvm_bind_option(const my_allocator_t* a, my_binding_context_t* c, my_echart_adapter_t* x, const char* p) {
  my_echart_mvvm_binding_t* b; if (!c || !x || !p || !*p) return NULL;
  b = my_mem_calloc(a, 1, sizeof(*b)); if (!b) return NULL; b->allocator=a; b->context=c; b->adapter=x;
  b->property=my_mem_alloc(a, strlen(p)+1); if (!b->property) { my_mem_free(a,b); return NULL; } strcpy(b->property,p);
  if (sync_binding(b) != MY_RET_OK) { my_mem_free(a,b->property); my_mem_free(a,b); return NULL; } return b;
}
my_ret_t my_echart_mvvm_sync(my_echart_mvvm_binding_t* b) { return b ? sync_binding(b) : MY_RET_INVALID_PARAMS; }
void my_echart_mvvm_unbind_option(my_echart_mvvm_binding_t* b) { if (b) { my_mem_free(b->allocator,b->property); my_mem_free(b->allocator,b); } }
