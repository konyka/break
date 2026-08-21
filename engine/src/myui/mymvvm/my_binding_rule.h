/**
 * @file my_binding_rule.h
 * @brief Binding rule: parsed form of a declarative binding string.
 *
 * Syntax (subset of awtk-mvvm):
 *   v:text={name}                             data, OneWay
 *   v:text={name, Mode=TwoWay}                data, bidirectional
 *   v:text={temp, Converter=upper}            data with converter
 *   v:value={age, Validator=range(0,150)}     data with validator
 *   v:on_click={save}                         command
 *   v:on_click={save, Args=btn1}              command with args
 *   v:on_click={close, CloseWindow=true}      command + close window
 * Items/condition rules are recognized but return MY_RET_NOT_SUPPORTED
 * for now (M4b).
 */
#ifndef MY_BINDING_RULE_H
#define MY_BINDING_RULE_H

#include "myc/my_error.h"
#include "myc/my_types.h"

#define MY_RULE_PROP_LEN 32
#define MY_RULE_NAME_LEN 48
#define MY_RULE_ARGS_LEN 64

/** @brief Binding rule kind. */
typedef enum my_binding_rule_type_t {
  MY_RULE_DATA = 0,
  MY_RULE_COMMAND,
  MY_RULE_ITEMS,
  MY_RULE_CONDITION
} my_binding_rule_type_t;

/** @brief Data binding update mode. */
typedef enum my_binding_mode_t {
  MY_BINDING_ONE_WAY = 0, /**< model -> view, live */
  MY_BINDING_TWO_WAY,     /**< both directions */
  MY_BINDING_ONCE         /**< model -> view, once at bind time */
} my_binding_mode_t;

/** @brief Parsed binding rule. */
typedef struct my_binding_rule_t {
  my_binding_rule_type_t type;
  char widget_prop[MY_RULE_PROP_LEN]; /**< e.g. "text", "on_click" */
  char vm_prop[MY_RULE_NAME_LEN];     /**< property or command name */
  my_binding_mode_t mode;
  char converter[MY_RULE_PROP_LEN];     /**< empty = none */
  char validator[MY_RULE_PROP_LEN];   /**< empty = none */
  char validator_args[MY_RULE_ARGS_LEN]; /**< e.g. "0,150" */
  char args[MY_RULE_ARGS_LEN];        /**< command args; "{prop}" is
                                           substituted from the vm at exec */
  bool close_window;
  char item_template[MY_RULE_PROP_LEN]; /**< items rules: template name */
  char to_page[MY_RULE_PROP_LEN];     /**< command rules: navigator target */
  bool condition_negate;              /**< condition rules: leading '!' */
} my_binding_rule_t;

/**
 * @brief Parse a binding rule string.
 * @return MY_RET_OK, MY_RET_INVALID_PARAMS (malformed), or
 * MY_RET_NOT_SUPPORTED (items/condition rules).
 */
my_ret_t my_binding_rule_parse(const char* str, my_binding_rule_t* rule);

#endif /* MY_BINDING_RULE_H */
