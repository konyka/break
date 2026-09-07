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

enum {
  OPTION_MODE = 1u << 0,
  OPTION_CONVERTER = 1u << 1,
  OPTION_VALIDATOR = 1u << 2,
  OPTION_ARGS = 1u << 3,
  OPTION_ITEM_TEMPLATE = 1u << 4,
  OPTION_TO_PAGE = 1u << 5,
  OPTION_CLOSE_WINDOW = 1u << 6
};

static my_ret_t option_bit(const char* key, unsigned* bit) {
  if (my_str_eq(key, "Mode")) {
    *bit = OPTION_MODE;
  } else if (my_str_eq(key, "Converter")) {
    *bit = OPTION_CONVERTER;
  } else if (my_str_eq(key, "Validator")) {
    *bit = OPTION_VALIDATOR;
  } else if (my_str_eq(key, "Args")) {
    *bit = OPTION_ARGS;
  } else if (my_str_eq(key, "ItemTemplate")) {
    *bit = OPTION_ITEM_TEMPLATE;
  } else if (my_str_eq(key, "ToPage")) {
    *bit = OPTION_TO_PAGE;
  } else if (my_str_eq(key, "CloseWindow")) {
    *bit = OPTION_CLOSE_WINDOW;
  } else {
    return MY_RET_NOT_SUPPORTED;
  }
  return MY_RET_OK;
}

static char* matching_paren(char* open) {
  char* cursor = open + 1;
  int depth = 1;
  while (*cursor != '\0') {
    if (*cursor == '(') {
      depth++;
    } else if (*cursor == ')') {
      depth--;
      if (depth == 0) {
        return cursor;
      }
      if (depth < 0) {
        return NULL;
      }
    }
    cursor++;
  }
  return NULL;
}

/** @brief Parse one "Key=Value" option (value may carry "(args)"). */
static my_ret_t parse_option(my_binding_rule_t* rule, char* option,
                             unsigned* option_mask) {
  char* eq = strchr(option, '=');
  char* key;
  char* value;
  char* paren;
  unsigned bit;
  if (eq == NULL || eq == option) {
    return MY_RET_INVALID_PARAMS;
  }
  *eq = '\0';
  key = trim(option);
  value = trim(eq + 1);
  if (*key == '\0' || *value == '\0') {
    return MY_RET_INVALID_PARAMS;
  }

  if (option_bit(key, &bit) != MY_RET_OK) {
    if (my_str_eq(key, "Items") || my_str_eq(key, "Condition")) {
      return MY_RET_NOT_SUPPORTED;
    }
    return MY_RET_INVALID_PARAMS;
  }
  if ((*option_mask & bit) != 0u) {
    return MY_RET_INVALID_PARAMS;
  }

  paren = strchr(value, '(');
  if (my_str_eq(key, "Mode")) {
    if (paren != NULL) {
      return MY_RET_INVALID_PARAMS;
    }
    if (parse_mode(value, &rule->mode) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    *option_mask |= bit;
    return MY_RET_OK;
  }
  if (my_str_eq(key, "Converter")) {
    if (copy_field(rule->converter, sizeof(rule->converter), value,
                   strlen(value)) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    *option_mask |= bit;
    return MY_RET_OK;
  }
  if (my_str_eq(key, "Validator")) {
    if (paren != NULL) {
      char* close = matching_paren(paren);
      size_t name_len = (size_t)(paren - value);
      if (close == NULL || close[1] != '\0' || close == paren + 1) {
        return MY_RET_INVALID_PARAMS;
      }
      if (copy_field(rule->validator, sizeof(rule->validator), value, name_len) !=
          MY_RET_OK) {
        return MY_RET_INVALID_PARAMS;
      }
      if (copy_field(rule->validator_args, sizeof(rule->validator_args),
                     paren + 1, (size_t)(close - paren - 1)) != MY_RET_OK) {
        return MY_RET_INVALID_PARAMS;
      }
      *option_mask |= bit;
      return MY_RET_OK;
    }
    if (copy_field(rule->validator, sizeof(rule->validator), value,
                   strlen(value)) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    *option_mask |= bit;
    return MY_RET_OK;
  }
  if (my_str_eq(key, "Args")) {
    if (copy_field(rule->args, sizeof(rule->args), value, strlen(value)) !=
        MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    *option_mask |= bit;
    return MY_RET_OK;
  }
  if (my_str_eq(key, "ItemTemplate")) {
    if (copy_field(rule->item_template, sizeof(rule->item_template), value,
                   strlen(value)) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    *option_mask |= bit;
    return MY_RET_OK;
  }
  if (my_str_eq(key, "ToPage")) {
    if (copy_field(rule->to_page, sizeof(rule->to_page), value,
                   strlen(value)) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
    *option_mask |= bit;
    return MY_RET_OK;
  }
  if (my_str_eq(key, "CloseWindow")) {
    if (my_str_eq(value, "true")) {
      rule->close_window = true;
      *option_mask |= bit;
      return MY_RET_OK;
    }
    if (my_str_eq(value, "false")) {
      rule->close_window = false;
      *option_mask |= bit;
      return MY_RET_OK;
    }
    return MY_RET_INVALID_PARAMS;
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
  unsigned option_mask = 0u;

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
    if (strchr(expr, ',') != NULL || strchr(expr, '{') != NULL ||
        strchr(expr, '}') != NULL) {
      return MY_RET_INVALID_PARAMS;
    }
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
        if (depth < 0) {
          return MY_RET_INVALID_PARAMS;
        }
      }
      comma++;
    }
    if (depth != 0) {
      return MY_RET_INVALID_PARAMS;
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
            if (depth < 0) {
              return MY_RET_INVALID_PARAMS;
            }
          }
          following++;
        }
        if (depth != 0) {
          return MY_RET_INVALID_PARAMS;
        }
        if (*following == '\0') {
          following = NULL;
        } else {
          *following = '\0';
        }
        option = trim(next);
        if (*option == '\0') {
          return MY_RET_INVALID_PARAMS;
        }
        ret = parse_option(rule, option, &option_mask);
        if (ret != MY_RET_OK) {
          return ret;
        }
        comma = following;
      }
    }
  }
  return MY_RET_OK;
}
