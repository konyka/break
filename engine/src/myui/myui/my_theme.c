/**
 * @file my_theme.c
 * @brief Theme: style sheet + text loader + widget style resolution.
 */
#include "myui/my_theme.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"
#include "myui/my_widget.h"

/* ---------------- entries ---------------- */

my_theme_t* my_theme_create(const my_allocator_t* allocator) {
  my_theme_t* theme = (my_theme_t*)my_mem_calloc(allocator, 1, sizeof(my_theme_t));
  if (theme == NULL) {
    return NULL;
  }
  theme->allocator = allocator;
  theme->entries = my_darray_create(allocator, 0);
  if (theme->entries == NULL) {
    my_mem_free(allocator, theme);
    return NULL;
  }
  return theme;
}

void my_theme_destroy(my_theme_t* theme) {
  size_t i, n;
  if (theme == NULL) {
    return;
  }
  n = my_darray_size(theme->entries);
  for (i = 0; i < n; i++) {
    my_theme_entry_t* e = (my_theme_entry_t*)my_darray_get(theme->entries, i);
    my_style_reset(&e->style);
    my_mem_free(theme->allocator, e);
  }
  my_darray_destroy(theme->entries);
  my_mem_free(theme->allocator, theme);
}

static my_theme_entry_t* theme_find_entry(my_theme_t* theme, const char* type,
                                          const char* name,
                                          const char* style_class,
                                          const char* ancestor_type,
                                          bool ancestor_direct,
                                          bool create) {
  size_t i, n = my_darray_size(theme->entries);
  const char* nm = name != NULL ? name : "";
  const char* cl = style_class != NULL ? style_class : "";
  const char* an = ancestor_type != NULL ? ancestor_type : "";
  for (i = 0; i < n; i++) {
    my_theme_entry_t* e = (my_theme_entry_t*)my_darray_get(theme->entries, i);
    if (my_str_eq(e->widget_type, type) && my_str_eq(e->name, nm) &&
        my_str_eq(e->style_class, cl) && my_str_eq(e->ancestor_type, an) &&
        e->ancestor_direct == ancestor_direct) {
      return e;
    }
  }
  if (!create) {
    return NULL;
  }
  {
    my_theme_entry_t* e =
        (my_theme_entry_t*)my_mem_calloc(theme->allocator, 1, sizeof(my_theme_entry_t));
    if (e == NULL) {
      return NULL;
    }
    strncpy(e->widget_type, type, MY_THEME_TYPE_LEN - 1);
    strncpy(e->name, nm, MY_THEME_NAME_LEN - 1);
    strncpy(e->style_class, cl, MY_THEME_NAME_LEN - 1);
    strncpy(e->ancestor_type, an, MY_THEME_TYPE_LEN - 1);
    e->ancestor_direct = ancestor_direct;
    my_style_init(&e->style, theme->allocator);
    if (my_darray_push(theme->entries, e) != MY_RET_OK) {
      my_mem_free(theme->allocator, e);
      return NULL;
    }
    return e;
  }
}

static int32_t class_count(const char* classes) {
  int32_t count = 0;
  bool in_word = false;
  const char* p = classes != NULL ? classes : "";
  while (*p != '\0') {
    if (*p == ' ') {
      in_word = false;
    } else if (!in_word) {
      count++;
      in_word = true;
    }
    p++;
  }
  return count;
}

static int32_t selector_specificity(const char* widget_type, const char* name,
                                    const char* style_class,
                                    const char* ancestor_type) {
  int32_t score = 0;
  const char* dot;
  if (name != NULL && name[0] != '\0') {
    score += 10000;
  }
  score += class_count(style_class) * 100;
  if (widget_type != NULL && widget_type[0] != '\0') {
    score += 1;
  }
  if (ancestor_type != NULL && ancestor_type[0] != '\0') {
    score += 1;
    dot = strchr(ancestor_type, '.');
    if (dot != NULL) {
      score += class_count(dot + 1) * 100;
    }
  }
  return score;
}

static size_t theme_style_prop_index(const my_style_t* style,
                                     my_widget_state_t state,
                                     const char* key) {
  size_t i;
  if (style == NULL || key == NULL || state >= MY_STATE_COUNT) {
    return MY_STYLE_MAX_PROPS;
  }
  for (i = 0; i < style->counts[state]; i++) {
    if (strncmp(style->props[state][i].key, key, MY_STYLE_KEY_LEN) == 0) {
      return i;
    }
  }
  return MY_STYLE_MAX_PROPS;
}

my_ret_t my_theme_set_ex3(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const char* ancestor_type, bool ancestor_direct,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity) {
  my_theme_entry_t* e;
  my_ret_t ret;
  if (theme == NULL || widget_type == NULL || key == NULL || value == NULL ||
      strlen(widget_type) >= MY_THEME_TYPE_LEN ||
      (name != NULL && strlen(name) >= MY_THEME_NAME_LEN) ||
      (style_class != NULL && strlen(style_class) >= MY_THEME_NAME_LEN) ||
      (ancestor_type != NULL &&
       strlen(ancestor_type) >= MY_THEME_TYPE_LEN)) {
    return MY_RET_INVALID_PARAMS;
  }
  e = theme_find_entry(theme, widget_type, name, style_class, ancestor_type,
                       ancestor_direct, true);
  if (e == NULL) {
    return MY_RET_OOM;
  }
  ret = my_style_set(&e->style, state, key, value);
  if (ret != MY_RET_OK) {
    return ret;
  }
  {
    size_t index = theme_style_prop_index(&e->style, state, key);
    if (index >= MY_STYLE_MAX_PROPS) {
      return MY_RET_FAIL;
    }
    e->specificity[state][index] = specificity;
  }
  return MY_RET_OK;
}

my_ret_t my_theme_set_ex2(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const char* ancestor_type, bool ancestor_direct,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value) {
  return my_theme_set_ex3(
      theme, widget_type, name, style_class, ancestor_type, ancestor_direct,
      state, key, value,
      selector_specificity(widget_type, name, style_class, ancestor_type));
}

my_ret_t my_theme_set_ex(my_theme_t* theme, const char* widget_type,
                         const char* name, const char* style_class,
                         const char* ancestor_type, my_widget_state_t state,
                         const char* key, const my_value_t* value) {
  return my_theme_set_ex2(theme, widget_type, name, style_class, ancestor_type,
                          false, state, key, value);
}

my_ret_t my_theme_set(my_theme_t* theme, const char* widget_type, const char* name,
                      my_widget_state_t state, const char* key,
                      const my_value_t* value) {
  return my_theme_set_ex(theme, widget_type, name, NULL, NULL, state, key,
                         value);
}

my_ret_t my_theme_set_color(my_theme_t* theme, const char* widget_type,
                            const char* name, my_widget_state_t state,
                            const char* key, uint32_t rgba) {
  my_value_t v;
  my_value_init(&v, NULL);
  my_value_set_uint32(&v, rgba);
  return my_theme_set(theme, widget_type, name, state, key, &v);
}

my_ret_t my_theme_set_int(my_theme_t* theme, const char* widget_type,
                          const char* name, my_widget_state_t state,
                          const char* key, int32_t value) {
  my_value_t v;
  my_value_init(&v, NULL);
  my_value_set_int32(&v, value);
  return my_theme_set(theme, widget_type, name, state, key, &v);
}

const my_value_t* my_theme_get(const my_theme_t* theme, const char* widget_type,
                               const char* name, my_widget_state_t state,
                               const char* key) {
  const my_theme_entry_t* e;
  const my_value_t* v = NULL;
  if (theme == NULL || widget_type == NULL || key == NULL) {
    return NULL;
  }
  if (name != NULL && *name != '\0') {
    e = theme_find_entry((my_theme_t*)theme, widget_type, name, NULL, NULL,
                         false, false);
    if (e != NULL) {
      v = my_style_get(&e->style, state, key);
      if (v != NULL) {
        return v;
      }
    }
  }
  e = theme_find_entry((my_theme_t*)theme, widget_type, "", NULL, NULL, false,
                       false);
  if (e != NULL) {
    v = my_style_get(&e->style, state, key);
  }
  return v;
}

/* ---------------- CSS cascade lookup (M18a) ---------------- */

/** @brief Word-boundary match of `word` in the space-separated class
 * list. */
static bool class_word_match(const char* list, const char* word) {
  const char* p;
  size_t wl;
  if (list == NULL || word == NULL || word[0] == '\0') {
    return false;
  }
  p = list;
  wl = strlen(word);
  while (*p != '\0') {
    while (*p == ' ') {
      p++;
    }
    if (strncmp(p, word, wl) == 0 && (p[wl] == '\0' || p[wl] == ' ')) {
      return true;
    }
    while (*p != '\0' && *p != ' ') {
      p++;
    }
  }
  return false;
}

static bool class_set_match(const char* list, const char* required) {
  const char* p = required;
  char word[MY_THEME_NAME_LEN];
  size_t n;
  if (required == NULL || required[0] == '\0') {
    return true;
  }
  if (list == NULL || list[0] == '\0') {
    return false;
  }
  while (*p != '\0') {
    while (*p == ' ') {
      p++;
    }
    n = 0;
    while (p[n] != '\0' && p[n] != ' ') {
      if (n + 1 >= sizeof(word)) {
        return false;
      }
      word[n] = p[n];
      n++;
    }
    word[n] = '\0';
    if (n > 0 && !class_word_match(list, word)) {
      return false;
    }
    p += n;
  }
  return true;
}

/** @brief Entry matches at one cascade level (level 0 = id, 1 = class,
 * 2 = type). The descendant condition searches from `ancestor_anchor`
 * INCLUSIVE (a part's owner counts as its own ancestor anchor). */
static bool entry_matches_ex(const my_theme_entry_t* e, const char* type,
                             const char* name, const char* style_class,
                             const my_widget_t* ancestor_anchor, int level) {
  /* descendant condition first (cheap): needs an ancestor of the type
   * (entry stores "type" or "type.class" — class word-matched) */
  if (e->ancestor_type[0] != '\0') {
    const my_widget_t* a = ancestor_anchor;
    char atype[MY_THEME_TYPE_LEN];
    const char* aclass = NULL;
    const char* dot = strchr(e->ancestor_type, '.');
    bool found = false;
    if (dot != NULL) {
      size_t tl = (size_t)(dot - e->ancestor_type);
      if (tl >= sizeof(atype)) {
        tl = sizeof(atype) - 1;
      }
      memcpy(atype, e->ancestor_type, tl);
      atype[tl] = '\0';
      aclass = dot + 1;
    } else {
      snprintf(atype, sizeof(atype), "%s", e->ancestor_type);
    }
    while (a != NULL) {
      if (my_str_eq(a->widget_type, atype) &&
          (aclass == NULL || class_set_match(a->style_class, aclass))) {
        found = true;
        break;
      }
      if (e->ancestor_direct) {
        break;
      }
      a = a->parent;
    }
    if (!found) {
      return false;
    }
  }
  /* type condition ("" = any; NULL type param = no type constraint) */
  if (e->widget_type[0] != '\0' &&
      (type == NULL || !my_str_eq(e->widget_type, type))) {
    return false;
  }
  if (!class_set_match(style_class, e->style_class)) {
    return false;
  }
  switch (level) {
    case 0: /* #id */
      return e->name[0] != '\0' && name != NULL && my_str_eq(e->name, name);
    case 1: /* .class (word match in the class list) */
      if (e->style_class[0] == '\0' || e->name[0] != '\0' ||
          style_class == NULL) {
        return false;
      }
      return true;
    case 2: /* type-wide */
      return e->name[0] == '\0' && e->style_class[0] == '\0' &&
             e->widget_type[0] != '\0' && my_str_eq(e->widget_type, type);
    default: /* universal */
      return e->name[0] == '\0' && e->style_class[0] == '\0' &&
             e->widget_type[0] == '\0';
  }
}

static int32_t theme_property_specificity(const my_theme_entry_t* entry,
                                          my_widget_state_t state,
                                          const char* key) {
  my_widget_state_t value_state = state;
  size_t i;

  if (entry == NULL || key == NULL || state >= MY_STATE_COUNT) {
    return INT32_MIN;
  }
  for (;;) {
    for (i = 0; i < entry->style.counts[value_state]; i++) {
      if (strncmp(entry->style.props[value_state][i].key, key,
                  MY_STYLE_KEY_LEN) == 0) {
        return entry->specificity[value_state][i];
      }
    }
    if (value_state == MY_STATE_NORMAL) {
      break;
    }
    value_state = MY_STATE_NORMAL;
  }
  return INT32_MIN;
}

static int entry_cascade_level(const my_theme_entry_t* entry) {
  if (entry->name[0] != '\0') {
    return 0;
  }
  if (entry->style_class[0] != '\0') {
    return 1;
  }
  if (entry->widget_type[0] != '\0') {
    return 2;
  }
  return 3;
}

/** @brief Shared cascade scan. skip_type_wide excludes the level-2
 * (bare type) match — see my_theme_get_part. */
static const my_value_t* theme_cascade_ex(const my_theme_t* theme,
                                          const char* type, const char* name,
                                          const char* style_class,
                                          const my_widget_t* ancestor_anchor,
                                          my_widget_state_t state,
                                          const char* key,
                                          bool skip_type_wide) {
  size_t i, n;
  const my_value_t* best = NULL;
  int32_t best_specificity = INT32_MIN;
  if (theme == NULL || key == NULL) {
    return NULL;
  }
  n = my_darray_size(theme->entries);
  for (i = n; i-- > 0;) {
    const my_theme_entry_t* e =
        (const my_theme_entry_t*)my_darray_get(theme->entries, i);
    int level = entry_cascade_level(e);
    if (skip_type_wide && level == 2) {
      continue;
    }
    if (entry_matches_ex(e, type, name, style_class, ancestor_anchor, level)) {
      const my_value_t* value = my_style_get(&e->style, state, key);
      int32_t specificity = theme_property_specificity(e, state, key);
      if (value != NULL &&
          (specificity > best_specificity || best == NULL)) {
        best = value;
        best_specificity = specificity;
      }
    }
  }
  return best;
}

/** @brief Shared cascade scan. */
static const my_value_t* theme_cascade(const my_theme_t* theme,
                                       const char* type, const char* name,
                                       const char* style_class,
                                       const my_widget_t* ancestor_anchor,
                                       my_widget_state_t state,
                                       const char* key) {
  return theme_cascade_ex(theme, type, name, style_class, ancestor_anchor,
                          state, key, false);
}

const my_value_t* my_theme_get_for_widget(const my_theme_t* theme,
                                          const my_widget_t* widget,
                                          my_widget_state_t state,
                                          const char* key) {
  if (widget == NULL) {
    return NULL;
  }
  return theme_cascade(theme, widget->widget_type,
                       ((const my_object_t*)widget)->name,
                       widget->style_class, widget->parent, state, key);
}

const my_value_t* my_theme_get_part(const my_theme_t* theme,
                                    const my_widget_t* owner,
                                    const char* part_type,
                                    const char* part_class,
                                    my_widget_state_t state,
                                    const char* key) {
  /* M19b: virtual parts (node headers, sockets, links...) — the owner
   * widget itself anchors the descendant search (inclusive).
   * M23b: when the part borrows the OWNER'S OWN type with a class
   * (node_view.rubber_band / .minimap / .minimap_viewport), a bare
   * type rule for the owner (e.g. `node_view { background-color }`)
   * must NOT match — it styles the owner widget, not the overlay
   * part (the leak made the rubber band fill/minimap bg opaque).
   * Class-bearing queries keep levels 0/1; part types distinct from
   * the owner (node_link.selected etc.) keep the full cascade. */
  bool skip_type_wide = part_class != NULL && part_type != NULL &&
                        owner != NULL &&
                        my_str_eq(part_type, owner->widget_type);
  return theme_cascade_ex(theme, part_type, NULL, part_class, owner, state,
                          key, skip_type_wide);
}

/** @brief Part color lookup with theme climbing + fallback (used by
 * widgets painting virtual parts). */
uint32_t my_widget_part_color(my_widget_t* widget, const char* part_type,
                              const char* part_class, my_widget_state_t state,
                              const char* key, uint32_t fallback) {
  my_widget_t* w = widget;
  const my_value_t* v;
  while (w != NULL) {
    if (w->theme != NULL) {
      v = my_theme_get_part(w->theme, widget, part_type, part_class, state,
                            key);
      return v != NULL && v->type == MY_VALUE_UINT32
                 ? my_value_get_uint32(v)
                 : fallback;
    }
    w = w->parent;
  }
  return fallback;
}

/* ---------------- default theme ---------------- */

my_theme_t* my_theme_default_create(const my_allocator_t* allocator) {
  my_theme_t* t = my_theme_create(allocator);
  if (t == NULL) {
    return NULL;
  }
  my_theme_set_color(t, "window", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR, 0xF5F5F5FF);

  my_theme_set_color(t, "button", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR, 0xE0E0E0FF);
  my_theme_set_color(t, "button", NULL, MY_STATE_HOVER, MY_STYLE_BG_COLOR, 0xEEEEEEFF);
  my_theme_set_color(t, "button", NULL, MY_STATE_PRESSED, MY_STYLE_BG_COLOR, 0xBDBDBDFF);
  my_theme_set_color(t, "button", NULL, MY_STATE_DISABLED, MY_STYLE_BG_COLOR, 0xCFCFCFFF);
  my_theme_set_color(t, "button", NULL, MY_STATE_NORMAL, MY_STYLE_BORDER_COLOR, 0x9E9E9EFF);
  my_theme_set_color(t, "button", NULL, MY_STATE_NORMAL, MY_STYLE_FG_COLOR, 0x212121FF);
  my_theme_set_int(t, "button", NULL, MY_STATE_NORMAL, MY_STYLE_ROUND_RADIUS, 4);

  my_theme_set_color(t, "label", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR, 0xF5F5F5FF);
  my_theme_set_color(t, "label", NULL, MY_STATE_NORMAL, MY_STYLE_FG_COLOR, 0x212121FF);

  /* composite widgets (M13c) */
  my_theme_set_color(t, "dialog_content", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                     0xF5F5F5FF);
  my_theme_set_color(t, "menu_box", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                     0xFAFAFAFF);
  my_theme_set_color(t, "menu_box", NULL, MY_STATE_NORMAL, MY_STYLE_BORDER_COLOR,
                     0x9E9E9EFF);
  my_theme_set_color(t, "menu_item", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                     0xFAFAFAFF);
  my_theme_set_color(t, "menu_item", NULL, MY_STATE_HOVER, MY_STYLE_BG_COLOR,
                     0xE3F2FDFF);
  my_theme_set_color(t, "menu_item", NULL, MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                     0x212121FF);
  my_theme_set_color(t, "tooltip", NULL, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                     0x323232F2);
  my_theme_set_color(t, "tooltip", NULL, MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                     0xF5F5F5FF);
  my_theme_set_color(t, "tooltip", NULL, MY_STATE_NORMAL, MY_STYLE_BORDER_COLOR,
                     0x616161FF);
  return t;
}

/* ---------------- text loader ---------------- */

static my_ret_t parse_state(const char* s, size_t len, my_widget_state_t* out) {
  static const char* NAMES[] = {"normal", "hover", "pressed", "disabled"};
  size_t i;
  for (i = 0; i < 4; i++) {
    if (strlen(NAMES[i]) == len && strncmp(s, NAMES[i], len) == 0) {
      *out = (my_widget_state_t)i;
      return MY_RET_OK;
    }
  }
  return MY_RET_INVALID_PARAMS;
}

static my_ret_t parse_value(const char* s, my_value_t* out) {
  char* end = NULL;
  if (*s == '#') {
    unsigned long v = strtoul(s + 1, &end, 16);
    size_t digits = (size_t)(end - (s + 1));
    uint32_t rgba;
    if (end == s + 1 || *end != '\0' || (digits != 6 && digits != 8)) {
      return MY_RET_INVALID_PARAMS;
    }
    if (digits == 6) {
      rgba = ((uint32_t)v << 8) | 0xFFu; /* #RRGGBB -> opaque */
    } else {
      rgba = (uint32_t)v; /* #RRGGBBAA */
    }
    my_value_set_uint32(out, rgba);
    return MY_RET_OK;
  }
  {
    double d = strtod(s, &end);
    if (end == s || *end != '\0') {
      /* not numeric: store as string */
      return my_value_set_str(out, s);
    }
    if (strchr(s, '.') != NULL) {
      my_value_set_double(out, d);
    } else {
      my_value_set_int32(out, (int32_t)d);
    }
    return MY_RET_OK;
  }
}

static my_ret_t theme_load_line(my_theme_t* theme, const char* line, size_t len) {
  char buf[128];
  char* dot1;
  char* dot_last;
  char* eq;
  char* bracket;
  char type[MY_THEME_TYPE_LEN];
  char name[MY_THEME_NAME_LEN];
  const char* key;
  my_widget_state_t state = MY_STATE_NORMAL;
  bool all_states = false;
  my_value_t v;
  my_ret_t ret;

  if (len == 0 || len >= sizeof(buf)) {
    return len == 0 ? MY_RET_OK : MY_RET_INVALID_PARAMS;
  }
  memcpy(buf, line, len);
  buf[len] = '\0';

  eq = strchr(buf, '=');
  dot1 = strchr(buf, '.');
  dot_last = strrchr(buf, '.');
  if (eq == NULL || dot_last == NULL || dot_last > eq) {
    return MY_RET_INVALID_PARAMS;
  }
  *eq = '\0';
  key = dot_last + 1;
  *dot_last = '\0';
  if (*key == '\0') {
    return MY_RET_INVALID_PARAMS;
  }

  /* selector part before the last dot may still contain ".state" */
  bracket = strchr(buf, '[');
  if (bracket != NULL) {
    char* close = strchr(bracket, ']');
    if (close == NULL || close == bracket + 1 || close - bracket - 1 >= MY_THEME_NAME_LEN) {
      return MY_RET_INVALID_PARAMS;
    }
    memcpy(name, bracket + 1, (size_t)(close - bracket - 1));
    name[close - bracket - 1] = '\0';
    *bracket = '\0';
  } else {
    name[0] = '\0';
  }

  /* buf is now "type" or "type.state" (dot1 points into buf if present) */
  if (dot1 != NULL && dot1 < dot_last) {
    *dot1 = '\0';
    if (parse_state(dot1 + 1, strlen(dot1 + 1), &state) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
  } else {
    all_states = true;
  }
  if (strlen(buf) >= MY_THEME_TYPE_LEN || *buf == '\0') {
    return MY_RET_INVALID_PARAMS;
  }
  strncpy(type, buf, MY_THEME_TYPE_LEN - 1);
  type[MY_THEME_TYPE_LEN - 1] = '\0';

  my_value_init(&v, theme->allocator);
  ret = parse_value(eq + 1, &v);
  if (ret == MY_RET_OK) {
    if (all_states) {
      int i;
      for (i = 0; i < (int)MY_STATE_COUNT && ret == MY_RET_OK; i++) {
        ret = my_theme_set(theme, type, name, (my_widget_state_t)i, key, &v);
      }
    } else {
      ret = my_theme_set(theme, type, name, state, key, &v);
    }
  }
  my_value_reset(&v);
  return ret;
}

my_ret_t my_theme_load_str(my_theme_t* theme, const char* str) {
  const char* cur;
  if (theme == NULL || str == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  cur = str;
  while (*cur != '\0') {
    const char* eol = strchr(cur, '\n');
    size_t len = eol != NULL ? (size_t)(eol - cur) : strlen(cur);
    /* skip blank lines and ';' comments */
    while (len > 0 && (*cur == ' ' || *cur == '\t' || *cur == '\r')) {
      cur++;
      len--;
    }
    if (len > 0 && *cur != ';') {
      if (theme_load_line(theme, cur, len) != MY_RET_OK) {
        return MY_RET_INVALID_PARAMS;
      }
    }
    if (eol == NULL) {
      break;
    }
    cur = eol + 1;
  }
  return MY_RET_OK;
}

/* ---------------- widget style resolution (declared in my_widget.h) ---- */

my_ret_t my_widget_style_set(my_widget_t* widget, my_widget_state_t state,
                             const char* key, const my_value_t* value) {
  if (widget == NULL || key == NULL || value == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (widget->local_style == NULL) {
    widget->local_style =
        (my_style_t*)my_mem_calloc(((my_object_t*)widget)->allocator, 1,
                                   sizeof(my_style_t));
    if (widget->local_style == NULL) {
      return MY_RET_OOM;
    }
    my_style_init(widget->local_style, ((my_object_t*)widget)->allocator);
  }
  return my_style_set(widget->local_style, state, key, value);
}

const my_value_t* my_widget_style_get(my_widget_t* widget,
                                      my_widget_state_t state, const char* key) {
  my_widget_t* w;
  const my_value_t* v;
  if (widget == NULL || key == NULL) {
    return NULL;
  }
  if (widget->local_style != NULL) {
    v = my_style_get(widget->local_style, state, key);
    if (v != NULL) {
      return v;
    }
  }
  /* climb to the nearest themed ancestor */
  w = widget;
  while (w != NULL) {
    if (w->theme != NULL) {
      /* M18a: cascade lookup (#id > .class > type, descendants) —
       * reduces to the plain (type,name) chain for text-format-only
       * themes */
      return my_theme_get_for_widget(w->theme, widget, state, key);
    }
    w = w->parent;
  }
  return NULL;
}

uint32_t my_widget_style_get_color(my_widget_t* widget, my_widget_state_t state,
                                   const char* key, uint32_t fallback) {
  const my_value_t* v = my_widget_style_get(widget, state, key);
  return v != NULL && v->type == MY_VALUE_UINT32 ? my_value_get_uint32(v)
                                                 : fallback;
}

int32_t my_widget_style_get_int(my_widget_t* widget, my_widget_state_t state,
                                const char* key, int32_t fallback) {
  const my_value_t* v = my_widget_style_get(widget, state, key);
  if (v == NULL) {
    return fallback;
  }
  if (v->type == MY_VALUE_INT32) {
    return my_value_get_int32(v);
  }
  if (v->type == MY_VALUE_DOUBLE) {
    return (int32_t)my_value_get_double(v);
  }
  return fallback;
}

static void invalidate_tree(my_widget_t* widget) {
  size_t i, n;
  my_widget_invalidate(widget, NULL);
  n = my_widget_child_count(widget);
  for (i = 0; i < n; i++) {
    invalidate_tree(my_widget_get_child(widget, i));
  }
}

my_ret_t my_widget_apply_theme(my_widget_t* widget, my_theme_t* theme) {
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  widget->theme = theme;
  invalidate_tree(widget);
  return MY_RET_OK;
}
