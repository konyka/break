/**
 * @file my_object.c
 * @brief Reference-counted base object.
 */
#include "myc/my_object.h"

#include "myc/my_str.h"

my_object_t* my_object_create(const my_allocator_t* allocator, const char* name) {
  my_object_t* obj = (my_object_t*)my_mem_calloc(allocator, 1, sizeof(my_object_t));
  if (obj == NULL) {
    return NULL;
  }
  obj->ref_count = 1;
  obj->destroy = my_object_destroy;
  obj->allocator = allocator;
  if (name != NULL) {
    obj->name = my_strdup(allocator, name);
    if (obj->name == NULL) {
      my_mem_free(allocator, obj);
      return NULL;
    }
  }
  return obj;
}

my_object_t* my_object_ref(my_object_t* obj) {
  if (obj != NULL) {
    obj->ref_count++;
  }
  return obj;
}

void my_object_unref(my_object_t* obj) {
  if (obj == NULL) {
    return;
  }
  if (--obj->ref_count <= 0 && obj->destroy != NULL) {
    obj->destroy(obj);
  }
}

void my_object_destroy(my_object_t* obj) {
  if (obj == NULL) {
    return;
  }
  my_mem_free(obj->allocator, obj->name);
  my_mem_free(obj->allocator, obj);
}
