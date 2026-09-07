# myc — myui base library (allocator, containers, utf8 str, emitter, value, object).
add_library(myc STATIC
  my_mem.c
  my_darray.c
  my_str.c
  my_emitter.c
  my_value.c
  my_object.c
  myconf/my_conf.c
  myconf/my_conf_json.c
  myconf/my_conf_bson.c
  myconf/my_conf_toml.c
  myconf/my_conf_yaml.c
)

set(MYUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH
  "myui source root used by myui public headers")
set(MYUI_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH
  "engine source root used by myui public headers")
target_include_directories(myc PUBLIC ${MYUI_SOURCE_DIR} ${MYUI_ENGINE_SOURCE_DIR})
