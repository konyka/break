#include "myui/echarts/my_echart_mvvm.h"
#include <string.h>
#include <stdio.h>
#include "myc/my_emitter.h"
struct my_echart_mvvm_binding_t { const my_allocator_t* allocator; my_binding_context_t* context; my_echart_adapter_t* adapter; char* property; uint32_t property_subscription; uint32_t bulk_subscription; };
static my_ret_t sync_binding(my_echart_mvvm_binding_t* b);
static void no_destroy(void* ctx) { (void)ctx; }
static void on_property(void* ctx, const char* event, void* data) { (void)event; (void)data; (void)sync_binding((my_echart_mvvm_binding_t*)ctx); }
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
  if (sync_binding(b) != MY_RET_OK) { my_mem_free(a,b->property); my_mem_free(a,b); return NULL; }
  my_view_model_t* vm = my_binding_context_get_view_model(c);
  if (vm != NULL) {
    char event_name[128];
    snprintf(event_name, sizeof(event_name), "prop:%s", p);
    b->property_subscription = my_emitter_on_owned(vm->emitter, event_name,
                                                    on_property, b, no_destroy);
    b->bulk_subscription = my_emitter_on_owned(vm->emitter, "props",
                                                on_property, b, no_destroy);
  }
  return b;
}
my_ret_t my_echart_mvvm_sync(my_echart_mvvm_binding_t* b) { return b ? sync_binding(b) : MY_RET_INVALID_PARAMS; }
void my_echart_mvvm_unbind_option(my_echart_mvvm_binding_t* b) { if (b) { my_view_model_t* vm=my_binding_context_get_view_model(b->context); if(vm){ if(b->property_subscription) my_emitter_off(vm->emitter,b->property_subscription); if(b->bulk_subscription) my_emitter_off(vm->emitter,b->bulk_subscription); } my_mem_free(b->allocator,b->property); my_mem_free(b->allocator,b); } }
