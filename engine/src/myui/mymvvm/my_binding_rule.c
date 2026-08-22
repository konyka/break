/**
 * @file my_binding_rule.c
 * @brief Binding rule string parser.
 */
#include "mymvvm/my_binding_rule.h"

#include <string.h>

#include "myc/my_str.h"

static my_ret_t copy_field(char* dst, size_t dst_size, const char* src,
                           size_t len) {
  if (len == 0 || len >= dst_size) {
    return MY_RET_INVALID_PARAMS;
  }
  memcpy(dst, src, len);
  dst[len] = '\0';
  return MY_RET_OK;
}

/** @brief Trim ASCII spaces in place (returns new start). */
static char* trim(char* s) {
  char* end;
  while (*s == ' ') {
    s++;
  }
  end = s + strlen(s);
  while (end > s && end[-1] == ' ') {
    *--end = '\0';
  }
  return s;
}

static my_ret_t parse_mode(const char* value, my_binding_mode_t* mode) {
  if (my_str_eq(value, "OneWay")) {
    *mode = MY_BINDING_ONE_WAY;
  } else if (my_str_eq(value, "TwoWay")) {
    *mode = MY_BINDING_TWO_WAY;
  } else if (my_str_eq(value, "Once")) {
    *mode = MY_BINDING_ONCE;
  } else {
    return MY_RET_INVALID_PARAMS;
  }
  return MY_RET_OK;
}

/** @brief Parse one "Key=Value" option (value may carry "(args)"). */
static my_ret_t parse_option(my_binding_rule_t* rule, char* option) {
  char* eq = strchr(option, '=');
  char* key;
  char* value;
  char* paren;
  if (eq == NULL || eq == option) {
    return MY_RET_INVALID_PARAMS;
  }
  *eq = '\0';
  key = trim(option);
  value = trim(eq + 1);
  if (*key == '\0' || *value == '\0') {
    return MY_RET_INVALID_PARAMS;
  }

  paren = strchr(value, '(');
  if (my_str_eq(key, "Mode")) {
    if (paren != NULL) {
      return MY_RET_INVALID_PARAMS;
    }
    return parse_mode(value, &rule->mode);
  }
  if (my_str_eq(key, "Converter")) {
    return copy_field(rule->converter, sizeof(rule->converter), value,
                      strlen(value));
  }
  if (my_str_eq(key, "Validator")) {
    if (paren != NULL) {
      char* close = strchr(paren, ')');
      size_t name_len = (size_t)(paren - value);
      if (close == NULL || close[1] != '\0' || close == paren + 1) {
        return MY_RET_INVALID_PARAMS;
      }
      if (copy_field(rule->validator, sizeof(rule->validator), value, name_len) !=
          MY_RET_OK) {
        return MY_RET_INVALID_PARAMS;
      }
      return copy_field(rule->validator_args, sizeof(rule->validator_args),
                        paren + 1, (size_t)(close - paren - 1));
    }
    return copy_field(rule->validator, sizeof(rule->validator), value,
                      strlen(value));
  }
  if (my_str_eq(key, "Args")) {
    return copy_field(rule->args, sizeof(rule->args), value, strlen(value));
  }
  if (my_str_eq(key, "ItemTemplate")) {
    return copy_field(rule->item_template, sizeof(rule->item_template), value,
                      strlen(value));
  }
  if (my_str_eq(key, "ToPage")) {
    return copy_field(rule->to_page, sizeof(rule->to_page), value,
                      strlen(value));
  }
  if (my_str_eq(key, "CloseWindow")) {
    if (my_str_eq(value, "true")) {
      rule->close_window = true;
      return MY_RET_OK;
    }
    if (my_str_eq(value, "false")) {
      rule->close_window = false;
      return MY_RET_OK;
    }
    return MY_RET_INVALID_PARAMS;
  }
  if (my_str_eq(key, "Items") || my_str_eq(key, "Condition")) {
    return MY_RET_NOT_SUPPORTED;
  }
  return MY_RET_INVALID_PARAMS;
}

my_ret_t my_binding_rule_parse(const char* str, my_binding_rule_t* rule) {
  char buf[256];
  char* open;
  char* close;
  char* body;
  char* prop_end;
  size_t len;
  my_ret_t ret = MY_RET_OK;

  if (str == NULL || rule == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(rule, 0, sizeof(*rule));
  rule->type = MY_RULE_DATA;
  rule->mode = MY_BINDING_ONE_WAY;

  len = strlen(str);
  if (len >= sizeof(buf)) {
    return MY_RET_INVALID_PARAMS;
  }
  memcpy(buf, str, len + 1);

  /* "v:<widget_prop>={<body>}" */
  if (buf[0] != 'v' || buf[1] != ':') {
    return MY_RET_INVALID_PARAMS;
  }
  prop_end = strchr(buf, '=');
  open = strchr(buf, '{');
  close = strrchr(buf, '}');
  if (prop_end == NULL || open == NULL || close == NULL || open < prop_end ||
      close < open || close[1] != '\0' || prop_end - buf - 2 <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (copy_field(rule->widget_prop, sizeof(rule->widget_prop), buf + 2,
                 (size_t)(prop_end - buf - 2)) != MY_RET_OK) {
    return MY_RET_INVALID_PARAMS;
  }

  *open = '\0';
  *close = '\0';
  body = open + 1;

  /* condition rule: body is "Condition=[!]prop" */
  if (strncmp(body, "Condition=", 10) == 0) {
    const char* expr = trim(body + 10);
    rule->type = MY_RULE_CONDITION;
    if (*expr == '!') {
      rule->condition_negate = true;
      expr++;
    }
    if (copy_field(rule->vm_prop, sizeof(rule->vm_prop), expr, strlen(expr)) !=
        MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    return MY_RET_OK;
  }

  /* items rule: widget_prop "items" */
  if (my_str_eq(rule->widget_prop, "items")) {
    rule->type = MY_RULE_ITEMS;
  } else if (strncmp(rule->widget_prop, "on_", 3) == 0) {
    rule->type = MY_RULE_COMMAND;
  }

  /* first token (up to a top-level ',') is the vm property/command name */
  {
    char* comma = body;
    int depth = 0;
    while (*comma != '\0' && !(*comma == ',' && depth == 0)) {
      if (*comma == '(') {
        depth++;
      } else if (*comma == ')') {
        depth--;
      }
      comma++;
    }
    {
      char* name;
      if (*comma == '\0') {
        comma = NULL;
      } else {
        *comma = '\0';
      }
      name = trim(body);
      if (strchr(name, '{') != NULL || strchr(name, '}') != NULL) {
        return MY_RET_INVALID_PARAMS;
      }
      if (copy_field(rule->vm_prop, sizeof(rule->vm_prop), name, strlen(name)) !=
          MY_RET_OK) {
        return MY_RET_INVALID_PARAMS;
      }
      /* remaining "K=V" options (commas inside parens don't split) */
      while (comma != NULL) {
        char* next = comma + 1;
        char* following = next;
        char* option;
        depth = 0;
        while (*following != '\0' && !(*following == ',' && depth == 0)) {
          if (*following == '(') {
            depth++;
          } else if (*following == ')') {
            depth--;
          }
          following++;
        }
        if (*following == '\0') {
          following = NULL;
        } else {
          *following = '\0';
        }
        option = trim(next);
        if (*option != '\0') {
          ret = parse_option(rule, option);
          if (ret != MY_RET_OK) {
            return ret;
          }
        }
        comma = following;
      }
    }
  }
  return MY_RET_OK;
}
