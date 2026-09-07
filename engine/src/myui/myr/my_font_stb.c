/**
 * @file my_font_stb.c
 * @brief stb_truetype font backend with an LRU glyph cache.
 */
#include "myr/my_font.h"
#include "myr/my_ui_metrics.h"

#ifdef MYUI_FONT_STB

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "core/platform_thread.h"
#include <stb_truetype.h>

#define MY_FONT_STB_DEFAULT_CACHE 256

typedef struct my_font_stb_t my_font_stb_t;

typedef struct glyph_cache_entry_t {
  uint32_t codepoint;
  int32_t size;
  uint8_t* bitmap; /**< owned, w*h bytes (NULL for blank) */
  int32_t w, h, bearing_x, bearing_y, advance;
  uint64_t last_used;
  size_t references;
  bool occupied;
  bool cached;
  const my_allocator_t* allocator;
  PlatformMutex* mutex;
  my_font_stb_t* owner;
  struct glyph_cache_entry_t* next_overflow;
} glyph_cache_entry_t;

struct my_font_stb_t {
  my_font_t base;
  const my_allocator_t* allocator;
  uint8_t* ttf_data; /**< owned; stbtt_fontinfo points into it */
  stbtt_fontinfo info;
  glyph_cache_entry_t* cache;
  size_t cache_capacity;
  uint64_t tick;
  size_t hits;
  size_t misses;
  glyph_cache_entry_t* overflow_entries;
  size_t overflow_count;
  size_t lease_count;
  bool destroy_requested;
  PlatformMutex mutex;
};

static uint16_t stb_read_u16_be(const uint8_t* data) {
  return (uint16_t)(((uint16_t)data[0] << 8) | data[1]);
}

static uint32_t stb_read_u32_be(const uint8_t* data) {
  return ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) |
         ((uint32_t)data[2] << 8) | (uint32_t)data[3];
}

static bool stb_is_sfnt_tag(const uint8_t* data) {
  return (data[0] == '1' && data[1] == 0 && data[2] == 0 && data[3] == 0) ||
         (memcmp(data, "typ1", 4u) == 0) ||
         (memcmp(data, "OTTO", 4u) == 0) ||
         (data[0] == 0 && data[1] == 1 && data[2] == 0 && data[3] == 0) ||
         (memcmp(data, "true", 4u) == 0);
}

typedef struct stb_table_view_t {
  size_t offset;
  size_t length;
  bool present;
} stb_table_view_t;

static bool stb_table_find(const uint8_t* data, size_t data_size,
                           size_t font_offset, uint16_t table_count,
                           const char tag[4], stb_table_view_t* view) {
  uint16_t table_index;
  if (view == NULL) return false;
  view->offset = 0u;
  view->length = 0u;
  view->present = false;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = font_offset + 12u + (size_t)table_index * 16u;
    if (memcmp(data + record, tag, 4u) == 0) {
      view->offset = (size_t)stb_read_u32_be(data + record + 8u);
      view->length = (size_t)stb_read_u32_be(data + record + 12u);
      view->present = true;
      return view->offset <= data_size &&
             view->length <= data_size - view->offset;
    }
  }
  return true;
}

static bool stb_validate_cmap_subtable(const uint8_t* data, size_t length,
                                       size_t subtable_offset,
                                       bool* supported) {
  uint16_t format;
  size_t subtable_length;
  if (supported == NULL || subtable_offset > length ||
      length - subtable_offset < 2u) {
    return false;
  }
  *supported = false;
  format = stb_read_u16_be(data + subtable_offset);
  if (format == 0u || format == 4u || format == 6u) {
    if (length - subtable_offset < 4u) return false;
    subtable_length = (size_t)stb_read_u16_be(data + subtable_offset + 2u);
    if (subtable_length < (format == 4u ? 16u :
                           (format == 6u ? 10u : 6u)) ||
        subtable_length > length - subtable_offset) {
      return false;
    }
    if (format == 4u) {
      uint16_t segment_count;
      uint16_t expected_power = 1u;
      uint16_t expected_selector = 0u;
      uint16_t previous_end = 0u;
      size_t start_codes;
      size_t id_range_offsets;
      size_t glyph_index_array;
      uint16_t segment_index;
      if (subtable_length < 8u) return false;
      segment_count = (uint16_t)(stb_read_u16_be(
          data + subtable_offset + 6u) / 2u);
      if (segment_count == 0u ||
          (size_t)segment_count > (subtable_length - 16u) / 8u) {
        return false;
      }
      while (expected_power <= segment_count / 2u) {
        expected_power = (uint16_t)(expected_power * 2u);
        expected_selector++;
      }
      if (stb_read_u16_be(data + subtable_offset + 8u) !=
              (uint16_t)(expected_power * 2u) ||
          stb_read_u16_be(data + subtable_offset + 10u) != expected_selector ||
          stb_read_u16_be(data + subtable_offset + 12u) !=
              (uint16_t)(segment_count * 2u - expected_power * 2u)) {
        return false;
      }
      start_codes = 16u + (size_t)segment_count * 2u;
      id_range_offsets = 14u + (size_t)segment_count * 6u + 2u;
      glyph_index_array = 16u + (size_t)segment_count * 8u;
      for (segment_index = 0u; segment_index < segment_count; segment_index++) {
        uint16_t start = stb_read_u16_be(
            data + subtable_offset + start_codes + 2u * segment_index);
        uint16_t end = stb_read_u16_be(
            data + subtable_offset + 14u + 2u * segment_index);
        uint16_t range_offset = stb_read_u16_be(
            data + subtable_offset + id_range_offsets + 2u * segment_index);
        if (start > end || (segment_index != 0u && end <= previous_end)) {
          return false;
        }
        if (range_offset != 0u) {
          size_t target = id_range_offsets + 2u * segment_index +
                          (size_t)range_offset;
          size_t glyph_count = (size_t)end - (size_t)start + 1u;
          if (target < glyph_index_array || target > subtable_length ||
              glyph_count > (subtable_length - target) / 2u) {
            return false;
          }
        }
        previous_end = end;
      }
    } else if (format == 6u) {
      uint16_t glyph_count;
      if (subtable_length < 10u) return false;
      glyph_count = stb_read_u16_be(data + subtable_offset + 8u);
      if ((size_t)glyph_count > (subtable_length - 10u) / 2u) {
        return false;
      }
    }
    *supported = true;
    return true;
  }
  if (format == 12u || format == 13u) {
    uint32_t declared_length;
    uint32_t group_count;
    if (length - subtable_offset < 16u) return false;
    declared_length = stb_read_u32_be(data + subtable_offset + 4u);
    group_count = stb_read_u32_be(data + subtable_offset + 12u);
    if ((uint64_t)declared_length < 16u ||
        (uint64_t)declared_length > (uint64_t)(length - subtable_offset) ||
        (uint64_t)group_count >
            ((uint64_t)declared_length - 16u) / 12u) {
      return false;
    }
    *supported = true;
    return true;
  }
  return true;
}

static bool stb_validate_cmap(const uint8_t* data, size_t offset,
                              size_t length) {
  uint16_t record_count;
  uint16_t record_index;
  bool supported_map = false;
  if (length < 4u) return false;
  record_count = stb_read_u16_be(data + offset + 2u);
  if ((size_t)record_count > (length - 4u) / 8u) return false;
  for (record_index = 0u; record_index < record_count; record_index++) {
    size_t record = offset + 4u + (size_t)record_index * 8u;
    uint32_t relative_offset = stb_read_u32_be(data + record + 4u);
    size_t subtable_offset;
    bool subtable_supported = false;
    if ((uint64_t)relative_offset > (uint64_t)(length - 2u)) return false;
    subtable_offset = (size_t)relative_offset;
    if (!stb_validate_cmap_subtable(data + offset, length, subtable_offset,
                                    &subtable_supported)) {
      return false;
    }
    {
      uint16_t platform = stb_read_u16_be(data + record);
      uint16_t encoding = stb_read_u16_be(data + record + 2u);
      bool stb_selects_subtable =
          platform == 0u ||
          (platform == 3u && (encoding == 0u || encoding == 1u ||
                              encoding == 10u));
      if (stb_selects_subtable && !subtable_supported) return false;
      if (stb_selects_subtable) {
        supported_map = true;
      }
    }
  }
  return supported_map;
}

static bool stb_validate_compound_component(
    const uint8_t* data, size_t length, size_t* cursor, uint16_t* flags,
    uint16_t* component, bool* more) {
  size_t advance = 4u;
  if (data == NULL || cursor == NULL || flags == NULL || component == NULL ||
      more == NULL || *cursor > length || length - *cursor < advance) {
    return false;
  }
  *flags = stb_read_u16_be(data + *cursor);
  *component = stb_read_u16_be(data + *cursor + 2u);
  advance += (*flags & 1u) != 0u ? 4u : 2u;
  if ((*flags & (1u << 3)) != 0u) {
    advance += 2u;
  } else if ((*flags & (1u << 6)) != 0u) {
    advance += 4u;
  } else if ((*flags & (1u << 7)) != 0u) {
    advance += 8u;
  }
  if (advance > length - *cursor) return false;
  *cursor += advance;
  *more = (*flags & (1u << 5)) != 0u;
  return true;
}

static bool stb_validate_compound_glyph(const uint8_t* data, size_t length,
                                        uint16_t glyph_count) {
  size_t cursor = 10u;
  bool more = true;
  uint16_t last_flags = 0u;
  if (length < cursor + 4u) return false;
  while (more) {
    uint16_t flags;
    uint16_t component;
    if (!stb_validate_compound_component(data, length, &cursor, &flags,
                                          &component, &more) ||
        (uint32_t)component >= (uint32_t)glyph_count || (flags & 2u) == 0u) {
      return false;
    }
    last_flags = flags;
  }
  if ((last_flags & (1u << 8)) != 0u) {
    uint16_t instruction_length;
    if (cursor > length || length - cursor < 2u) return false;
    instruction_length = stb_read_u16_be(data + cursor);
    if ((size_t)instruction_length > length - cursor - 2u) return false;
  }
  return true;
}

static bool stb_simple_flags_end(const uint8_t* data, size_t length,
                                 size_t flags_offset, size_t point_count,
                                 size_t* coordinates_offset);
static bool stb_simple_coordinates_end(const uint8_t* data, size_t length,
                                       size_t flags_offset, size_t point_count,
                                       size_t coordinates_offset, bool x_axis,
                                       size_t* end_offset);

static bool stb_validate_cff_index(const uint8_t* data, size_t length,
                                   size_t offset, size_t* end_offset,
                                   uint16_t* count_out) {
  uint16_t count;
  uint8_t off_size;
  size_t cursor;
  size_t offset_bytes;
  size_t offsets_start;
  size_t data_start;
  uint32_t previous = 0u;
  uint32_t index;

  if (data == NULL || end_offset == NULL || offset > length ||
      length - offset < 2u)
    return false;
  count = stb_read_u16_be(data + offset);
  cursor = offset + 2u;
  if (count_out != NULL) *count_out = count;
  if (count == 0u) {
    *end_offset = cursor;
    return true;
  }
  if (length - cursor < 1u) return false;
  off_size = data[cursor++];
  if (off_size < 1u || off_size > 4u) return false;
  offset_bytes = ((size_t)count + 1u) * (size_t)off_size;
  if (offset_bytes > length - cursor) return false;
  offsets_start = cursor;
  data_start = offsets_start + offset_bytes;
  for (index = 0u; index <= (uint32_t)count; index++) {
    size_t value_offset = offsets_start + (size_t)index * off_size;
    uint32_t value = 0u;
    uint8_t byte_index;
    for (byte_index = 0u; byte_index < off_size; byte_index++)
      value = (value << 8) | data[value_offset + byte_index];
    if (value == 0u || (index != 0u && value < previous)) return false;
    previous = value;
  }
  if ((uint64_t)(previous - 1u) > (uint64_t)(length - data_start))
    return false;
  *end_offset = data_start + (size_t)(previous - 1u);
  return true;
}

static bool stb_cff_index_object(const uint8_t* data, size_t length,
                                 size_t offset, uint16_t object_index,
                                 const uint8_t** object,
                                 size_t* object_length) {
  uint16_t count;
  uint8_t off_size;
  size_t cursor;
  size_t offset_bytes;
  size_t offsets_start;
  size_t data_start;
  uint32_t first_offset = 0u;
  uint32_t second_offset = 0u;
  uint8_t byte_index;

  if (object == NULL || object_length == NULL ||
      !stb_validate_cff_index(data, length, offset, &cursor, &count) ||
      count == 0u || object_index >= count || offset > length ||
      length - offset < 3u)
    return false;
  count = stb_read_u16_be(data + offset);
  cursor = offset + 2u;
  off_size = data[cursor++];
  offset_bytes = ((size_t)count + 1u) * (size_t)off_size;
  if (offset_bytes > length - cursor) return false;
  offsets_start = cursor;
  data_start = offsets_start + offset_bytes;
  {
    size_t first_offset_start =
        offsets_start + (size_t)object_index * off_size;
    size_t second_offset_start = first_offset_start + off_size;
    for (byte_index = 0u; byte_index < off_size; byte_index++) {
      first_offset =
          (first_offset << 8) | data[first_offset_start + byte_index];
      second_offset = (second_offset << 8) |
                      data[second_offset_start + byte_index];
    }
  }
  if (first_offset == 0u || second_offset < first_offset ||
      (uint64_t)(second_offset - 1u) >
          (uint64_t)(length - data_start))
    return false;
  *object = data + data_start + (size_t)(first_offset - 1u);
  *object_length = (size_t)(second_offset - first_offset);
  return true;
}

typedef struct stb_cff_top_dict_t {
  bool has_charstrings;
  uint32_t charstrings;
  bool has_fdarray;
  uint32_t fdarray;
  bool has_fdselect;
  uint32_t fdselect;
  bool has_private;
  uint32_t private_size;
  uint32_t private_offset;
  bool has_subrs;
  uint32_t subrs;
} stb_cff_top_dict_t;

static bool stb_cff_read_dict_number(const uint8_t* data, size_t length,
                                     size_t* cursor, int64_t* value) {
  uint8_t first;

  if (data == NULL || cursor == NULL || value == NULL || *cursor >= length)
    return false;
  first = data[(*cursor)++];
  if (first >= 32u && first <= 246u) {
    *value = (int64_t)first - 139;
    return true;
  }
  if (first >= 247u && first <= 250u) {
    uint8_t second;
    if (*cursor >= length) return false;
    second = data[(*cursor)++];
    *value = (int64_t)(first - 247u) * 256 + second + 108;
    return true;
  }
  if (first >= 251u && first <= 254u) {
    uint8_t second;
    if (*cursor >= length) return false;
    second = data[(*cursor)++];
    *value = -((int64_t)(first - 251u) * 256 + second + 108);
    return true;
  }
  if (first == 28u) {
    uint16_t encoded;
    if (length - *cursor < 2u) return false;
    encoded = stb_read_u16_be(data + *cursor);
    *cursor += 2u;
    *value = (int64_t)(int16_t)encoded;
    return true;
  }
  if (first == 29u) {
    uint32_t encoded;
    if (length - *cursor < 4u) return false;
    encoded = stb_read_u32_be(data + *cursor);
    *cursor += 4u;
    *value = (int64_t)(int32_t)encoded;
    return true;
  }
  if (first == 30u) {
    bool terminated = false;
    while (*cursor < length) {
      uint8_t nibbles = data[(*cursor)++];
      if ((nibbles & 0x0fu) == 0x0fu || (nibbles >> 4) == 0x0fu) {
        terminated = true;
        break;
      }
    }
    *value = 0;
    return terminated;
  }
  return false;
}

static bool stb_cff_dict_operands_valid(uint16_t op, size_t count,
                                        bool top_level) {
  if (top_level) {
    switch (op) {
      case 0u:
      case 1u:
      case 2u:
      case 3u:
      case 4u:
      case 13u:
      case 15u:
      case 16u:
      case 17u:
        return count == 1u;
      case 14u:
        return count != 0u;
      case 5u:
        return count == 4u;
      case 18u:
        return count == 2u;
      default:
        break;
    }
    if (op >= 0x100u) {
      switch (op & 0xffu) {
        case 0u:
        case 1u:
        case 2u:
        case 3u:
        case 4u:
        case 5u:
        case 6u:
        case 8u:
        case 20u:
        case 21u:
        case 22u:
        case 31u:
        case 32u:
        case 33u:
        case 34u:
        case 35u:
        case 36u:
        case 37u:
        case 38u:
          return count == 1u;
        case 7u:
          return count == 6u;
        case 30u:
          return count == 3u;
        default:
          break;
      }
    }
    return true;
  }

  switch (op) {
    case 6u:
    case 7u:
    case 8u:
    case 9u:
      return count >= 2u && (count & 1u) == 0u;
    case 10u:
    case 11u:
    case 19u:
    case 20u:
    case 21u:
      return count == 1u;
    default:
      break;
  }
  if (op >= 0x100u) {
    switch (op & 0xffu) {
      case 9u:
      case 10u:
      case 11u:
      case 14u:
      case 17u:
      case 18u:
      case 19u:
        return count == 1u;
      case 12u:
      case 13u:
        return count >= 2u && (count & 1u) == 0u;
      default:
        break;
    }
  }
  return true;
}

static bool stb_parse_cff_dict(const uint8_t* data, size_t length,
                               bool top_level, stb_cff_top_dict_t* top_dict) {
  int64_t operands[48];
  size_t operand_count = 0u;
  size_t cursor = 0u;

  if (data == NULL || top_dict == NULL) return false;
  memset(top_dict, 0, sizeof(*top_dict));
  while (cursor < length) {
    uint8_t first = data[cursor];
    int64_t value;
    uint16_t op;
    if (first == 28u || first == 29u || first == 30u || first == 255u ||
        first >= 32u) {
      if (operand_count >= sizeof(operands) / sizeof(operands[0]) ||
          !stb_cff_read_dict_number(data, length, &cursor, &value))
        return false;
      operands[operand_count++] = value;
      continue;
    }
    if (first > 21u && first != 12u) return false;
    cursor++;
    op = first;
    if (first == 12u) {
      if (cursor >= length) return false;
      op = (uint16_t)(0x100u | data[cursor++]);
    }
    if (!stb_cff_dict_operands_valid(op, operand_count, top_level)) {
      return false;
    }
    if (op == 17u) {
      if (operand_count != 1u || operands[0] <= 0 ||
          operands[0] > (int64_t)UINT32_MAX || !top_level)
        return false;
      top_dict->has_charstrings = true;
      top_dict->charstrings = (uint32_t)operands[0];
    } else if (op == 18u) {
      if (operand_count != 2u || operands[0] <= 0 ||
          operands[0] > (int64_t)UINT32_MAX || operands[1] <= 0 ||
          operands[1] > (int64_t)UINT32_MAX)
        return false;
      top_dict->has_private = true;
      top_dict->private_size = (uint32_t)operands[0];
      top_dict->private_offset = (uint32_t)operands[1];
    } else if (op == (uint16_t)(0x100u | 36u)) {
      if (operand_count != 1u || operands[0] <= 0 ||
          operands[0] > (int64_t)UINT32_MAX)
        return false;
      if (!top_level) return false;
      top_dict->has_fdarray = true;
      top_dict->fdarray = (uint32_t)operands[0];
    } else if (op == (uint16_t)(0x100u | 37u)) {
      if (operand_count != 1u || operands[0] <= 0 ||
          operands[0] > (int64_t)UINT32_MAX)
        return false;
      if (!top_level) return false;
      top_dict->has_fdselect = true;
      top_dict->fdselect = (uint32_t)operands[0];
    } else if (op == 19u) {
      if (operand_count != 1u || operands[0] <= 0 ||
          operands[0] > (int64_t)UINT32_MAX || top_level)
        return false;
      top_dict->has_subrs = true;
      top_dict->subrs = (uint32_t)operands[0];
      top_dict->fdselect = (uint32_t)operands[0];
    }
    operand_count = 0u;
  }
  return operand_count == 0u && (!top_level || top_dict->has_charstrings);
}

static bool stb_validate_cff_charstring(const uint8_t* data, size_t length,
                                        bool enforce_stack,
                                        bool reject_reserved);

static bool stb_validate_cff_charstring_index(const uint8_t* data,
                                              size_t length, uint32_t offset,
                                              uint16_t* count_out,
                                              bool enforce_stack,
                                              bool reject_reserved) {
  uint16_t count;
  uint16_t index;
  size_t end;

  if (!stb_validate_cff_index(data, length, offset, &end, &count))
    return false;
  for (index = 0u; index < count; index++) {
    const uint8_t* object;
    size_t object_length;
    if (!stb_cff_index_object(data, length, offset, index, &object,
                              &object_length) ||
        object_length == 0u ||
        !stb_validate_cff_charstring(object, object_length, enforce_stack,
                                     reject_reserved)) {
      return false;
    }
  }
  if (count_out != NULL) *count_out = count;
  return true;
}

static bool stb_validate_cff_private_data(
    const uint8_t* data, size_t length, const stb_cff_top_dict_t* dict) {
  stb_cff_top_dict_t private_dict;

  if (data == NULL || dict == NULL) return false;
  if (!dict->has_private) return true;
  if ((uint64_t)dict->private_offset >= (uint64_t)length ||
      (uint64_t)dict->private_size >
          (uint64_t)(length - dict->private_offset) ||
      !stb_parse_cff_dict(data + dict->private_offset, dict->private_size,
                          false, &private_dict)) {
    return false;
  }
  if (private_dict.has_subrs) {
    uint64_t subrs_offset = (uint64_t)dict->private_offset +
                            (uint64_t)private_dict.subrs;
    if (subrs_offset >= (uint64_t)length ||
        !stb_validate_cff_charstring_index(data, length, (size_t)subrs_offset,
                                            NULL, false, false)) {
      return false;
    }
  }
  return true;
}

static bool stb_validate_cff_charstring(const uint8_t* data, size_t length,
                                        bool enforce_stack,
                                        bool reject_reserved) {
  size_t cursor = 0u;
  size_t stack_depth = 0u;
  size_t hint_count = 0u;
  bool stack_known = true;
  bool hint_count_known = true;

  if (data == NULL || length == 0u) return false;
  if (!enforce_stack) {
    while (cursor < length) {
      uint8_t first = data[cursor++];
      if (first == 12u) {
        if (cursor >= length) return false;
        cursor++;
      } else if (first == 28u) {
        if (length - cursor < 2u) return false;
        cursor += 2u;
      } else if (first >= 247u && first <= 254u) {
        if (cursor >= length) return false;
        cursor++;
      } else if (first == 255u) {
        if (length - cursor < 4u) return false;
        cursor += 4u;
      }
    }
    return true;
  }
  while (cursor < length) {
    uint8_t first = data[cursor++];
    if (first == 28u || first >= 32u) {
      if (first >= 247u && first <= 254u) {
        if (cursor >= length) return false;
        cursor++;
      } else if (first == 28u) {
        if (length - cursor < 2u) return false;
        cursor += 2u;
      } else if (first == 255u) {
        if (length - cursor < 4u) return false;
        cursor += 4u;
      }
      if (++stack_depth > 48u) return false;
      continue;
    }
    if (first == 12u) {
      uint8_t second;
      size_t minimum_operands = 0u;
      if (cursor >= length) return false;
      second = data[cursor++];
      if (second > 37u) return false;
      if (second == 34u) {
        minimum_operands = 7u;
      } else if (second == 35u) {
        minimum_operands = 13u;
      } else if (second == 36u) {
        minimum_operands = 9u;
      } else if (second == 37u) {
        minimum_operands = 11u;
      }
      if (enforce_stack && stack_known && stack_depth < minimum_operands)
        return false;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 1u || first == 3u || first == 18u || first == 23u) {
      size_t stem_operands = stack_depth;
      if (enforce_stack && stack_known && stem_operands == 0u) return false;
      if (stack_known) {
        if ((stem_operands & 1u) != 0u) stem_operands--;
        if (hint_count > SIZE_MAX - stem_operands / 2u)
          return false;
        hint_count += stem_operands / 2u;
      } else {
        hint_count_known = false;
      }
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 19u || first == 20u) {
      size_t mask_bytes;
      if (!hint_count_known) return true;
      if (stack_known && stack_depth != 0u) {
        if ((stack_depth & 1u) != 0u) stack_depth--;
        if (hint_count > SIZE_MAX - stack_depth / 2u)
          return false;
        hint_count += stack_depth / 2u;
      }
      if (hint_count > SIZE_MAX - 7u) return false;
      mask_bytes = (hint_count + 7u) / 8u;
      if (mask_bytes > length - cursor) return false;
      cursor += mask_bytes;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 10u || first == 29u) {
      if (enforce_stack && stack_known && stack_depth == 0u) return false;
      if (enforce_stack && stack_known) stack_depth--;
      if (enforce_stack) {
        stack_known = false;
        hint_count_known = false;
      }
      continue;
    }
    if (reject_reserved &&
        (first == 0u || first == 2u || first == 9u || first == 13u ||
         (first >= 15u && first <= 17u)))
      return false;
    if (!reject_reserved &&
        (first == 0u || first == 2u || first == 9u || first == 13u ||
         (first >= 15u && first <= 17u)))
      continue;
    if (first == 4u || first == 22u) {
      if (enforce_stack && stack_known && stack_depth < 1u) return false;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 5u || first == 21u) {
      if (enforce_stack && stack_known && stack_depth < 2u) return false;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 6u || first == 7u || first == 26u || first == 27u ||
        first == 30u || first == 31u) {
      if (enforce_stack && stack_known &&
          stack_depth < (first == 6u || first == 7u ? 1u : 4u))
        return false;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 8u) {
      if (enforce_stack && stack_known && stack_depth < 6u) return false;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 24u || first == 25u) {
      if (enforce_stack && stack_known && stack_depth < 8u) return false;
      stack_depth = 0u;
      stack_known = true;
      continue;
    }
    if (first == 11u || first == 14u) {
      stack_depth = 0u;
      continue;
    }
    return false;
  }
  return true;
}

static bool stb_validate_cff_fontdicts(const uint8_t* data, size_t length,
                                       uint32_t offset, uint16_t* count_out) {
  uint16_t count;
  uint16_t index;
  size_t end;

  if (!stb_validate_cff_index(data, length, offset, &end, &count) ||
      count == 0u) {
    return false;
  }
  for (index = 0u; index < count; index++) {
    const uint8_t* object;
    size_t object_length;
    stb_cff_top_dict_t font_dict;
    if (!stb_cff_index_object(data, length, offset, index, &object,
                              &object_length) ||
        object_length == 0u ||
        !stb_parse_cff_dict(object, object_length, false, &font_dict) ||
        !stb_validate_cff_private_data(data, length, &font_dict)) {
      return false;
    }
  }
  if (count_out != NULL) *count_out = count;
  return true;
}

static bool stb_validate_cff_fdselect(const uint8_t* data, size_t length,
                                      uint32_t offset, uint16_t glyph_count,
                                      uint16_t fd_count) {
  uint8_t format;
  if ((uint64_t)offset >= (uint64_t)length) return false;
  format = data[offset];
  if (format == 0u) {
    uint16_t glyph;
    if (length - (size_t)offset - 1u < (size_t)glyph_count) return false;
    for (glyph = 0u; glyph < glyph_count; glyph++)
      if (data[offset + 1u + glyph] >= fd_count) return false;
    return true;
  }
  if (format == 3u) {
    uint16_t range_count;
    uint16_t start;
    uint16_t range;
    size_t required;
    if (length - (size_t)offset < 5u) return false;
    range_count = stb_read_u16_be(data + offset + 1u);
    required = 5u + (size_t)range_count * 3u;
    if (required > length - (size_t)offset ||
        stb_read_u16_be(data + offset + 3u) != 0u)
      return false;
    start = 0u;
    for (range = 0u; range < range_count; range++) {
      size_t record = (size_t)offset + 5u + (size_t)range * 3u;
      uint8_t fd = data[record];
      uint16_t end = stb_read_u16_be(data + record + 1u);
      if (fd >= fd_count || end <= start || end > glyph_count) return false;
      start = end;
    }
    return range_count != 0u && start == glyph_count;
  }
  return false;
}

static bool stb_validate_cff_charstrings(const uint8_t* data, size_t length,
                                         uint32_t offset,
                                         uint16_t glyph_count) {
  uint16_t charstring_count;
  if (!stb_validate_cff_charstring_index(data, length, offset,
                                         &charstring_count, true, true) ||
      charstring_count != glyph_count)
    return false;
  return true;
}

static bool stb_validate_cff(const uint8_t* data, size_t length,
                             uint16_t glyph_count) {
  size_t cursor;
  size_t top_index_offset;
  size_t global_subr_offset;
  size_t next;
  uint16_t top_count = 0u;
  uint16_t fd_count = 0u;
  const uint8_t* top_object;
  size_t top_object_length;
  stb_cff_top_dict_t top_dict;

  if (data == NULL || length < 4u || data[2] < 4u ||
      (size_t)data[2] > length)
    return false;
  cursor = (size_t)data[2];
  if (!stb_validate_cff_index(data, length, cursor, &next, NULL)) return false;
  top_index_offset = next;
  if (!stb_validate_cff_index(data, length, top_index_offset, &next,
                              &top_count) ||
      top_count == 0u ||
      !stb_cff_index_object(data, length, top_index_offset, 0u, &top_object,
                                  &top_object_length) ||
      !stb_validate_cff_index(data, length, next, &next, NULL))
    return false;
  global_subr_offset = next;
  if (!stb_validate_cff_charstring_index(data, length, global_subr_offset,
                                         NULL, false, false))
    return false;
  if (!stb_parse_cff_dict(top_object, top_object_length, true, &top_dict)) {
    return false;
  }
  if ((uint64_t)top_dict.charstrings >= (uint64_t)length) {
    return false;
  }
  if (!stb_validate_cff_charstrings(data, length, top_dict.charstrings,
                                    glyph_count)) {
    return false;
  }
  if (!stb_validate_cff_private_data(data, length, &top_dict)) {
    return false;
  }
  if (top_dict.has_fdarray != top_dict.has_fdselect ||
      (top_dict.has_fdarray &&
       ((uint64_t)top_dict.fdarray >= (uint64_t)length ||
        !stb_validate_cff_fontdicts(data, length, top_dict.fdarray,
                                    &fd_count) ||
        !stb_validate_cff_fdselect(data, length, top_dict.fdselect,
                                   glyph_count, fd_count))))
    return false;
  return true;
}

static bool stb_validate_simple_glyph(const uint8_t* data, size_t length) {
  uint16_t contour_count;
  uint16_t contour_index;
  uint16_t previous_end = 0u;
  size_t instruction_offset;
  size_t flags_offset;
  size_t coordinates_offset;
  size_t x_end;
  size_t point_count;
  uint16_t instruction_length;

  if (length < 10u) return false;
  contour_count = stb_read_u16_be(data);
  if (contour_count == 0u) return true;
  if (contour_count >= 0x8000u || length < 12u ||
      (size_t)contour_count > (length - 12u) / 2u) {
    return false;
  }
  for (contour_index = 0u; contour_index < contour_count; contour_index++) {
    uint16_t end_point = stb_read_u16_be(data + 10u + 2u * contour_index);
    if (contour_index != 0u && end_point <= previous_end) {
      return false;
    }
    previous_end = end_point;
  }
  point_count = (size_t)previous_end + 1u;
  instruction_offset = 10u + (size_t)contour_count * 2u;
  instruction_length = stb_read_u16_be(data + instruction_offset);
  if ((size_t)instruction_length > length - instruction_offset - 2u)
    return false;
  flags_offset = instruction_offset + 2u + (size_t)instruction_length;
  if (!stb_simple_flags_end(data, length, flags_offset, point_count,
                            &coordinates_offset) ||
      !stb_simple_coordinates_end(data, length, flags_offset, point_count,
                                   coordinates_offset, true, &x_end) ||
      !stb_simple_coordinates_end(data, length, flags_offset, point_count,
                                   x_end, false, NULL)) {
    return false;
  }
  return true;
}

static bool stb_simple_flags_end(const uint8_t* data, size_t length,
                                 size_t flags_offset, size_t point_count,
                                 size_t* coordinates_offset) {
  size_t cursor = flags_offset;
  size_t point = 0u;
  uint8_t repeat = 0u;
  uint8_t flags = 0u;
  while (point < point_count) {
    if (repeat == 0u) {
      if (cursor >= length) return false;
      flags = data[cursor++];
      if ((flags & 0xc0u) != 0u) return false;
      if ((flags & 8u) != 0u) {
        if (cursor >= length) return false;
        repeat = data[cursor++];
        if ((size_t)repeat >= point_count - point) return false;
      }
    } else {
      --repeat;
    }
    ++point;
  }
  if (coordinates_offset != NULL) *coordinates_offset = cursor;
  return true;
}

static bool stb_simple_coordinates_end(const uint8_t* data, size_t length,
                                       size_t flags_offset, size_t point_count,
                                       size_t coordinates_offset, bool x_axis,
                                       size_t* end_offset) {
  size_t flags_cursor = flags_offset;
  size_t coordinate_cursor = coordinates_offset;
  size_t point = 0u;
  uint8_t repeat = 0u;
  uint8_t flags = 0u;
  while (point < point_count) {
    if (repeat == 0u) {
      if (flags_cursor >= coordinates_offset) return false;
      flags = data[flags_cursor++];
      if ((flags & 0xc0u) != 0u) return false;
      if ((flags & 8u) != 0u) {
        if (flags_cursor >= coordinates_offset) return false;
        repeat = data[flags_cursor++];
        if ((size_t)repeat >= point_count - point) return false;
      }
    } else {
      --repeat;
    }
    if (x_axis ? (flags & 2u) != 0u : (flags & 4u) != 0u) {
      if (coordinate_cursor >= length) return false;
      ++coordinate_cursor;
    } else if (x_axis ? (flags & 16u) == 0u : (flags & 32u) == 0u) {
      if (coordinate_cursor > length || length - coordinate_cursor < 2u)
        return false;
      coordinate_cursor += 2u;
    }
    ++point;
  }
  if (end_offset != NULL) *end_offset = coordinate_cursor;
  return true;
}

static uint32_t stb_loca_offset(const uint8_t* data, size_t loca_offset,
                                size_t entry_size, uint16_t glyph_index) {
  size_t entry = loca_offset + (size_t)glyph_index * entry_size;
  return entry_size == 2u ? (uint32_t)stb_read_u16_be(data + entry) * 2u
                          : stb_read_u32_be(data + entry);
}

typedef struct stb_compound_frame_t {
  uint16_t node;
  uint32_t start;
  uint32_t end;
  size_t cursor;
  bool more;
} stb_compound_frame_t;

static bool stb_validate_compound_graph(
    const uint8_t* data, size_t glyf_offset, size_t glyf_length,
    size_t loca_offset, size_t loca_entry_size, uint16_t glyph_count,
    const my_allocator_t* allocator) {
  uint8_t* state = NULL;
  stb_compound_frame_t* stack = NULL;
  size_t root;
  bool valid = false;

  state = (uint8_t*)my_mem_calloc(allocator, glyph_count, sizeof(*state));
  stack = (stb_compound_frame_t*)my_mem_alloc(
      allocator, (size_t)glyph_count * sizeof(*stack));
  if (state == NULL || stack == NULL) goto cleanup;
  for (root = 0u; root < (size_t)glyph_count; root++) {
    size_t top = 0u;
    uint32_t root_start = stb_loca_offset(data, loca_offset, loca_entry_size,
                                          (uint16_t)root);
    uint32_t root_end = stb_loca_offset(data, loca_offset, loca_entry_size,
                                        (uint16_t)root + 1u);
    if (state[root] != 0u) continue;
    if (root_end <= root_start) {
      state[root] = 2u;
      continue;
    }
    if ((uint64_t)root_end > (uint64_t)glyf_length) goto cleanup;
    if (stb_read_u16_be(data + glyf_offset + root_start) < 0x8000u) {
      state[root] = 2u;
      continue;
    }
    state[root] = 1u;
    stack[top].node = (uint16_t)root;
    stack[top].start = root_start;
    stack[top].end = root_end;
    stack[top].cursor = 10u;
    stack[top].more = true;
    top++;
    while (top != 0u) {
      stb_compound_frame_t* frame = &stack[top - 1u];
      uint16_t node = frame->node;
      uint32_t start = frame->start;
      uint32_t end = frame->end;
      size_t length = (size_t)(end - start);
      uint16_t flags;
      uint16_t component;
      bool more;
      if (end <= start || (uint64_t)end > (uint64_t)glyf_length) goto cleanup;
      if (stb_read_u16_be(data + glyf_offset + start) < 0x8000u) {
        state[node] = 2u;
        --top;
        continue;
      }
      if (!frame->more) {
        state[node] = 2u;
        --top;
        continue;
      }
      if (frame->cursor >= length) goto cleanup;
      if (!stb_validate_compound_component(
              data + glyf_offset + start, length, &frame->cursor, &flags,
              &component, &more) || component >= glyph_count)
        goto cleanup;
      frame->more = more;
      if (state[component] == 1u) goto cleanup;
      if (state[component] == 0u) {
        uint32_t child_start = stb_loca_offset(data, loca_offset,
                                               loca_entry_size, component);
        uint32_t child_end = stb_loca_offset(
            data, loca_offset, loca_entry_size, (uint16_t)(component + 1u));
        if (top >= (size_t)glyph_count || child_end <= child_start ||
            (uint64_t)child_end > (uint64_t)glyf_length)
          goto cleanup;
        state[component] = 1u;
        stack[top].node = component;
        stack[top].start = child_start;
        stack[top].end = child_end;
        stack[top].cursor = 10u;
        stack[top].more = true;
        top++;
        continue;
      }
      if (!more) {
        state[node] = 2u;
        --top;
      }
    }
  }
  valid = true;

cleanup:
  my_mem_free(allocator, stack);
  my_mem_free(allocator, state);
  return valid;
}

/* Validate the container and the fixed-width data consumed during init and
 * ordinary TrueType metric/glyph lookup. Deeper outline semantics remain
 * stb_truetype's responsibility, but no required table may escape payload. */
static bool stb_validate_sfnt(const uint8_t* data, size_t data_size,
                              size_t font_offset,
                              const my_allocator_t* allocator) {
  size_t directory_size;
  uint16_t table_count;
  uint16_t table_index;
  stb_table_view_t cmap = {0};
  stb_table_view_t head = {0};
  stb_table_view_t hhea = {0};
  stb_table_view_t hmtx = {0};
  stb_table_view_t maxp = {0};
  stb_table_view_t loca = {0};
  stb_table_view_t glyf = {0};
  stb_table_view_t cff = {0};
  uint16_t glyph_count;
  uint16_t long_metric_count;
  size_t required_hmtx;
  size_t loca_index;

  if (font_offset > data_size || data_size - font_offset < 12u ||
      !stb_is_sfnt_tag(data + font_offset)) {
    return false;
  }
  table_count = stb_read_u16_be(data + font_offset + 4u);
  if ((size_t)table_count > (data_size - font_offset - 12u) / 16u) {
    return false;
  }
  directory_size = 12u + (size_t)table_count * 16u;
  if (directory_size > data_size - font_offset) return false;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = font_offset + 12u + (size_t)table_index * 16u;
    uint32_t table_offset = stb_read_u32_be(data + record + 8u);
    uint32_t table_size = stb_read_u32_be(data + record + 12u);
    if ((uint64_t)table_offset > (uint64_t)data_size ||
        (uint64_t)table_size > (uint64_t)data_size - table_offset) {
      return false;
    }
  }
  if (!stb_table_find(data, data_size, font_offset, table_count, "cmap",
                      &cmap) ||
      !stb_table_find(data, data_size, font_offset, table_count, "head",
                      &head) ||
      !stb_table_find(data, data_size, font_offset, table_count, "hhea",
                      &hhea) ||
      !stb_table_find(data, data_size, font_offset, table_count, "hmtx",
                      &hmtx) ||
      !stb_table_find(data, data_size, font_offset, table_count, "maxp",
                      &maxp) ||
      !stb_table_find(data, data_size, font_offset, table_count, "loca",
                      &loca) ||
      !stb_table_find(data, data_size, font_offset, table_count, "glyf",
                      &glyf) ||
      !stb_table_find(data, data_size, font_offset, table_count, "CFF ",
                      &cff)) {
    return false;
  }
  if (!cmap.present || cmap.length < 4u ||
      !stb_validate_cmap(data, cmap.offset, cmap.length) ||
      !head.present || head.length < 54u ||
      !hhea.present || hhea.length < 36u ||
      !hmtx.present || !maxp.present || maxp.length < 6u) {
    return false;
  }
  glyph_count = stb_read_u16_be(data + maxp.offset + 4u);
  long_metric_count = stb_read_u16_be(data + hhea.offset + 34u);
  if (glyph_count == 0u || long_metric_count == 0u ||
      long_metric_count > glyph_count) {
    return false;
  }
  required_hmtx = (size_t)long_metric_count * 4u +
                  (size_t)(glyph_count - long_metric_count) * 2u;
  if (hmtx.length < required_hmtx) return false;
  if (glyf.present) {
    size_t loca_entry_size;
    uint32_t previous_offset = 0u;
    if (!loca.present) return false;
    if (stb_read_u16_be(data + head.offset + 50u) > 1u) return false;
    loca_entry_size = stb_read_u16_be(data + head.offset + 50u) == 0u ? 2u : 4u;
    if ((size_t)(glyph_count + 1u) > loca.length / loca_entry_size) return false;
    for (loca_index = 0u; loca_index <= (size_t)glyph_count; loca_index++) {
      size_t entry = loca.offset + loca_index * loca_entry_size;
      uint32_t current_offset = loca_entry_size == 2u
                                     ? (uint32_t)stb_read_u16_be(data + entry) * 2u
                                     : stb_read_u32_be(data + entry);
      if (current_offset < previous_offset ||
          (uint64_t)current_offset > (uint64_t)glyf.length) {
        return false;
      }
      if (current_offset > previous_offset && current_offset - previous_offset < 10u) {
        return false;
      }
      if (current_offset > previous_offset) {
        const uint8_t* glyph_data = data + glyf.offset + previous_offset;
        size_t glyph_length = (size_t)(current_offset - previous_offset);
        if (stb_read_u16_be(glyph_data) >= 0x8000u) {
          if (!stb_validate_compound_glyph(glyph_data, glyph_length,
                                           glyph_count)) {
            return false;
          }
        } else if (!stb_validate_simple_glyph(glyph_data, glyph_length)) {
          return false;
        }
      }
      previous_offset = current_offset;
    }
    if (!stb_validate_compound_graph(data, glyf.offset, glyf.length,
                                     loca.offset, loca_entry_size, glyph_count,
                                     allocator)) {
      return false;
    }
  } else if (!cff.present ||
             !stb_validate_cff(data + cff.offset, cff.length, glyph_count)) {
    return false;
  }
  return true;
}

static bool stb_select_face(const uint8_t* data, size_t data_size,
                            int32_t face_index, size_t* font_offset,
                            const my_allocator_t* allocator) {
  uint32_t face_count;
  uint32_t selected_offset;

  if (data_size < 4u || font_offset == NULL) return false;
  if (stb_is_sfnt_tag(data)) {
    if (face_index != 0) return false;
    *font_offset = 0u;
    return stb_validate_sfnt(data, data_size, 0u, allocator);
  }
  if (data_size < 12u || memcmp(data, "ttcf", 4u) != 0 ||
      (stb_read_u32_be(data + 4u) != 0x00010000u &&
       stb_read_u32_be(data + 4u) != 0x00020000u)) {
    return false;
  }
  face_count = stb_read_u32_be(data + 8u);
  if (face_index < 0 || (uint32_t)face_index >= face_count ||
      face_count > (uint32_t)((data_size - 12u) / 4u)) {
    return false;
  }
  selected_offset = stb_read_u32_be(data + 12u + (size_t)face_index * 4u);
  if ((uint64_t)selected_offset >= (uint64_t)data_size ||
      !stb_validate_sfnt(data, data_size, (size_t)selected_offset, allocator)) {
    return false;
  }
  *font_offset = (size_t)selected_offset;
  return true;
}

static float stb_scale(my_font_stb_t* f, int32_t size) {
  return stbtt_ScaleForPixelHeight(&f->info, (float)size);
}

static bool stb_measure_text_length(const char* text, size_t* length_out) {
  size_t length;
  if (text == NULL || length_out == NULL) return false;
  for (length = 0u; length <= MY_FONT_SHAPE_MAX_BYTES; length++) {
    if (text[length] == '\0') {
      *length_out = length;
      return true;
    }
  }
  return false;
}

/* ---------------- vtable ---------------- */

static my_ret_t stb_measure(my_font_t* font, const char* text, int32_t size,
                            int32_t* w, int32_t* h) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  const char* p = text;
  float scale;
  double width = 0.0;
  size_t text_length = 0u;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!stb_measure_text_length(text, &text_length)) {
    return MY_RET_INVALID_PARAMS;
  }
  (void)text_length;
  platform_mutex_lock(&f->mutex);
  scale = stb_scale(f, size);
  while (*p != '\0') {
    uint32_t cp = my_utf8_next(&p);
    int adv, lsb;
    if (my_font_is_variation_selector(cp)) continue;
    stbtt_GetCodepointHMetrics(&f->info, (int)cp, &adv, &lsb);
    width += (double)adv * (double)scale;
  }
  if (w != NULL) {
    *w = width >= (double)INT32_MAX
             ? INT32_MAX
             : (width <= 0.0 ? 0 : (int32_t)(width + 0.5));
  }
  if (h != NULL) {
    int ascent, descent, gap;
    stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
    *h = (int32_t)((float)(ascent - descent + gap) * scale + 0.5f);
  }
  platform_mutex_unlock(&f->mutex);
  return MY_RET_OK;
}

static glyph_cache_entry_t* cache_lookup(my_font_stb_t* f, uint32_t cp,
                                         int32_t size) {
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    glyph_cache_entry_t* e = &f->cache[i];
    if (e->occupied && e->codepoint == cp && e->size == size) {
      e->last_used = ++f->tick;
      f->hits++;
      return e;
    }
  }
  f->misses++;
  my_ui_metrics_record_atlas_miss();
  return NULL;
}

static glyph_cache_entry_t* cache_slot(my_font_stb_t* f) {
  size_t i;
  glyph_cache_entry_t* lru = &f->cache[0];
  bool found = false;
  for (i = 0; i < f->cache_capacity; i++) {
    if (!f->cache[i].occupied) {
      return &f->cache[i];
    }
    if (f->cache[i].references == 0u &&
        (!found || f->cache[i].last_used < lru->last_used)) {
      lru = &f->cache[i];
      found = true;
    }
  }
  if (!found) return NULL;
  my_mem_free(f->allocator, lru->bitmap); /* evict LRU */
  lru->bitmap = NULL;
  return lru;
}

static void stb_finalize(my_font_stb_t* f);

static void stb_release_glyph(void* lease) {
  glyph_cache_entry_t* entry = (glyph_cache_entry_t*)lease;
  glyph_cache_entry_t** link;
  my_font_stb_t* owner;
  const my_allocator_t* allocator;
  bool finalize = false;
  bool free_entry = false;
  if (entry == NULL || entry->owner == NULL) return;
  owner = entry->owner;
  allocator = entry->allocator;
  platform_mutex_lock(&owner->mutex);
  if (entry->references == 0u) {
    platform_mutex_unlock(&owner->mutex);
    return;
  }
  entry->references--;
  if (owner->lease_count != 0u) owner->lease_count--;
  if (!entry->cached && entry->references == 0u) {
    link = &owner->overflow_entries;
    while (*link != NULL && *link != entry) link = &(*link)->next_overflow;
    if (*link == entry) {
      *link = entry->next_overflow;
      free_entry = true;
      if (owner->overflow_count != 0u) owner->overflow_count--;
    }
  }
  if (owner->destroy_requested && owner->lease_count == 0u) {
    finalize = true;
  }
  platform_mutex_unlock(&owner->mutex);
  if (free_entry) {
    my_mem_free(allocator, entry->bitmap);
    my_mem_free(allocator, entry);
  }
  if (finalize) stb_finalize(owner);
}

static my_ret_t stb_get_glyph(my_font_t* font, uint32_t codepoint, int32_t size,
                              my_glyph_t* glyph) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  glyph_cache_entry_t* e;
  int adv, lsb;
  float scale;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_font_is_variation_selector(codepoint)) {
    memset(glyph, 0, sizeof(*glyph));
    return MY_RET_OK;
  }
  platform_mutex_lock(&f->mutex);
  if (f->destroy_requested) {
    platform_mutex_unlock(&f->mutex);
    return MY_RET_FAIL;
  }
  if (f->lease_count == SIZE_MAX) {
    platform_mutex_unlock(&f->mutex);
    return MY_RET_OOM;
  }
  e = cache_lookup(f, codepoint, size);
  if (e == NULL) {
    int bw, bh, xoff, yoff;
    uint8_t* bm;
    uint8_t* bitmap = NULL;
    size_t bytes = 0u;
    scale = stb_scale(f, size);
    bm = stbtt_GetCodepointBitmap(&f->info, scale, scale, (int)codepoint, &bw,
                                  &bh, &xoff, &yoff);
    if (bm != NULL && bw > 0 && bh > 0) {
      if ((size_t)bw > SIZE_MAX / (size_t)bh) {
        stbtt_FreeBitmap(bm, NULL);
        platform_mutex_unlock(&f->mutex);
        return MY_RET_OOM;
      }
      bytes = (size_t)bw * (size_t)bh;
      bitmap = (uint8_t*)my_mem_alloc(f->allocator, bytes);
      if (bitmap == NULL) {
        stbtt_FreeBitmap(bm, NULL);
        platform_mutex_unlock(&f->mutex);
        return MY_RET_OOM;
      }
      memcpy(bitmap, bm, bytes);
    }
    stbtt_FreeBitmap(bm, NULL);

    e = cache_slot(f);
    if (e == NULL) {
      if (f->overflow_count >= f->cache_capacity ||
          f->overflow_count >= MY_FONT_MAX_GLYPH_OVERFLOW_ENTRIES) {
        my_mem_free(f->allocator, bitmap);
        platform_mutex_unlock(&f->mutex);
        return MY_RET_OOM;
      }
      e = (glyph_cache_entry_t*)my_mem_calloc(f->allocator, 1u, sizeof(*e));
      if (e == NULL) {
        my_mem_free(f->allocator, bitmap);
        platform_mutex_unlock(&f->mutex);
        return MY_RET_OOM;
      }
      e->cached = false;
      e->allocator = f->allocator;
      e->mutex = &f->mutex;
      e->owner = f;
      e->next_overflow = f->overflow_entries;
      f->overflow_entries = e;
      f->overflow_count++;
    } else {
      e->cached = true;
      e->allocator = f->allocator;
      e->mutex = &f->mutex;
      e->owner = f;
    }
    e->occupied = true;
    e->codepoint = codepoint;
    e->size = size;
    e->w = bw;
    e->h = bh;
    e->bearing_x = xoff;
    e->bearing_y = -yoff; /* stb yoff is baseline-relative top, negative up */
    stbtt_GetCodepointHMetrics(&f->info, (int)codepoint, &adv, &lsb);
    e->advance = (int32_t)((float)adv * scale + 0.5f);
    e->bitmap = bitmap;
    e->last_used = ++f->tick;
  }
  if (e->references == SIZE_MAX) {
    platform_mutex_unlock(&f->mutex);
    return MY_RET_OOM;
  }
  e->references++;
  f->lease_count++;
  glyph->bitmap = e->bitmap;
  glyph->w = e->w;
  glyph->h = e->h;
  glyph->bearing_x = e->bearing_x;
  glyph->bearing_y = e->bearing_y;
  glyph->advance = e->advance;
  glyph->lease = e;
  glyph->release_lease = stb_release_glyph;
  platform_mutex_unlock(&f->mutex);
  return MY_RET_OK;
}

static int32_t stb_ascent(my_font_t* font, int32_t size) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  int ascent, descent, gap;
  int32_t result;
  platform_mutex_lock(&f->mutex);
  stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
  result = (int32_t)((float)ascent * stb_scale(f, size) + 0.5f);
  platform_mutex_unlock(&f->mutex);
  return result;
}

static int32_t stb_descent(my_font_t* font, int32_t size) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  int ascent, descent, gap;
  int32_t result;
  platform_mutex_lock(&f->mutex);
  stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
  result = (int32_t)((float)descent * stb_scale(f, size) - 0.5f);
  platform_mutex_unlock(&f->mutex);
  return result;
}

static int32_t stb_line_height(my_font_t* font, int32_t size) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  int ascent, descent, gap;
  int32_t result;
  platform_mutex_lock(&f->mutex);
  stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
  result = (int32_t)((float)(ascent - descent + gap) * stb_scale(f, size) +
                     0.5f);
  platform_mutex_unlock(&f->mutex);
  return result;
}

static void stb_finalize(my_font_stb_t* f) {
  glyph_cache_entry_t* overflow;
  glyph_cache_entry_t* next;
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    my_mem_free(f->allocator, f->cache[i].bitmap);
  }
  overflow = f->overflow_entries;
  while (overflow != NULL) {
    next = overflow->next_overflow;
    my_mem_free(f->allocator, overflow->bitmap);
    my_mem_free(f->allocator, overflow);
    overflow = next;
  }
  my_mem_free(f->allocator, f->cache);
  my_mem_free(f->allocator, f->ttf_data);
  platform_mutex_destroy(&f->mutex);
  my_mem_free(f->allocator, f);
}

static void stb_destroy(my_font_t* font) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  bool finalize = false;
  if (f == NULL) return;
  platform_mutex_lock(&f->mutex);
  if (!f->destroy_requested) {
    f->destroy_requested = true;
    finalize = f->lease_count == 0u;
  }
  platform_mutex_unlock(&f->mutex);
  if (finalize) stb_finalize(f);
}

static bool stb_has_glyph(my_font_t* font, uint32_t codepoint) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  bool result;
  if (my_font_is_variation_selector(codepoint)) return false;
  platform_mutex_lock(&f->mutex);
  result = stbtt_FindGlyphIndex(&f->info, (int)codepoint) != 0;
  platform_mutex_unlock(&f->mutex);
  return result;
}

static const my_font_vtable_t s_stb_vtable = {stb_measure, stb_get_glyph,
                                              stb_ascent, stb_descent,
                                              stb_line_height, stb_destroy,
                                              stb_has_glyph, NULL, NULL, NULL,
                                              NULL, NULL};

my_font_t* my_font_stb_create_ex(const my_allocator_t* allocator,
                                 const char* path, int32_t face_index,
                                 size_t cache_capacity) {
  my_font_stb_t* f;
  FILE* file;
  long size;
  if (path == NULL || face_index < 0) {
    return NULL;
  }
  file = fopen(path, "rb");
  if (file == NULL) {
    return NULL;
  }
  f = (my_font_stb_t*)my_mem_calloc(allocator, 1, sizeof(my_font_stb_t));
  if (f == NULL) {
    fclose(file);
    return NULL;
  }
  platform_mutex_init(&f->mutex);
  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    platform_mutex_destroy(&f->mutex);
    my_mem_free(allocator, f);
    return NULL;
  }
  size = ftell(file);
  if (size <= 0 || (uint64_t)size > (uint64_t)MY_FONT_STB_MAX_FILE_BYTES ||
      fseek(file, 0, SEEK_SET) != 0) {
    fclose(file);
    platform_mutex_destroy(&f->mutex);
    my_mem_free(allocator, f);
    return NULL;
  }
  f->ttf_data = (uint8_t*)my_mem_alloc(allocator, (size_t)size);
  if (f->ttf_data == NULL || fread(f->ttf_data, 1, (size_t)size, file) != (size_t)size) {
    fclose(file);
    my_mem_free(allocator, f->ttf_data);
    platform_mutex_destroy(&f->mutex);
    my_mem_free(allocator, f);
    return NULL;
  }
  fclose(file);
  {
    size_t offset;
    if (!stb_select_face(f->ttf_data, (size_t)size, face_index, &offset,
                         allocator) ||
        offset > (size_t)INT_MAX ||
        !stbtt_InitFont(&f->info, f->ttf_data, (int)offset)) {
      my_mem_free(allocator, f->ttf_data);
      platform_mutex_destroy(&f->mutex);
      my_mem_free(allocator, f);
      return NULL;
    }
  }
  f->base.vtable = &s_stb_vtable;
  f->allocator = allocator;
  f->cache_capacity = cache_capacity > 0 ? cache_capacity
                                         : MY_FONT_STB_DEFAULT_CACHE;
  f->cache = (glyph_cache_entry_t*)my_mem_calloc(allocator, f->cache_capacity,
                                                 sizeof(glyph_cache_entry_t));
  if (f->cache == NULL) {
    my_mem_free(allocator, f->ttf_data);
    platform_mutex_destroy(&f->mutex);
    my_mem_free(allocator, f);
    return NULL;
  }
  return (my_font_t*)f;
}

my_font_t* my_font_stb_create(const my_allocator_t* allocator, const char* path,
                              size_t cache_capacity) {
  return my_font_stb_create_ex(allocator, path, 0, cache_capacity);
}

#else /* !MYUI_FONT_STB */

my_font_t* my_font_stb_create_ex(const my_allocator_t* allocator,
                                 const char* path, int32_t face_index,
                                 size_t cache_capacity) {
  (void)allocator;
  (void)path;
  (void)face_index;
  (void)cache_capacity;
  return NULL;
}

my_font_t* my_font_stb_create(const my_allocator_t* allocator, const char* path,
                              size_t cache_capacity) {
  return my_font_stb_create_ex(allocator, path, 0, cache_capacity);
}

#endif /* MYUI_FONT_STB */

size_t my_font_stb_cache_hits(my_font_t* font) {
#ifdef MYUI_FONT_STB
  my_font_stb_t* f = (my_font_stb_t*)font;
  size_t result = 0u;
  if (f == NULL || f->base.vtable != &s_stb_vtable) return 0u;
  platform_mutex_lock(&f->mutex);
  result = f->hits;
  platform_mutex_unlock(&f->mutex);
  return result;
#else
  (void)font;
  return 0;
#endif
}

size_t my_font_stb_cache_misses(my_font_t* font) {
#ifdef MYUI_FONT_STB
  my_font_stb_t* f = (my_font_stb_t*)font;
  size_t result = 0u;
  if (f == NULL || f->base.vtable != &s_stb_vtable) return 0u;
  platform_mutex_lock(&f->mutex);
  result = f->misses;
  platform_mutex_unlock(&f->mutex);
  return result;
#else
  (void)font;
  return 0;
#endif
}
