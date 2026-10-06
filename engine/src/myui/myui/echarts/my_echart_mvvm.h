#ifndef MY_ECHART_MVVM_H
#define MY_ECHART_MVVM_H
#include "my_echart_adapter.h"
#include "mymvvm/my_binding_context.h"
typedef struct my_echart_mvvm_binding_t my_echart_mvvm_binding_t;
my_echart_mvvm_binding_t* my_echart_mvvm_bind_option(const my_allocator_t*, my_binding_context_t*, my_echart_adapter_t*, const char*);
void my_echart_mvvm_unbind_option(my_echart_mvvm_binding_t*);
my_ret_t my_echart_mvvm_sync(my_echart_mvvm_binding_t*);
#endif
