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

target_include_directories(myc PUBLIC ${CMAKE_SOURCE_DIR}/src)
