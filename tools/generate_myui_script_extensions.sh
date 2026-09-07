#!/bin/sh
set -eu

input=${1:?usage: $0 ScriptExtensions.txt output.h}
output=${2:?usage: $0 ScriptExtensions.txt output.h}
version=$(awk 'NR == 1 { sub(/^# ScriptExtensions-/, ""); sub(/\.txt.*/, ""); print; exit }' "$input")

awk -v version="$version" '
function hex(s) { return "0x" s "u" }
function code(c, p) {
  p = index("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c); if (p) return p + 64
  p = index("abcdefghijklmnopqrstuvwxyz", c); if (p) return p + 96
  p = index("0123456789", c); if (p) return p + 48
  return 32
}
function tag(s, i, v) {
  v = 0
  for (i = 1; i <= 4; i++) v = v * 256 + code(substr(s, i, 1))
  return sprintf("0x%08Xu", v)
}
BEGIN {
  print "/* Generated from Unicode ScriptExtensions-" version ".txt. */"
  print "#ifndef MY_SCRIPT_EXTENSIONS_DATA_H"
  print "#define MY_SCRIPT_EXTENSIONS_DATA_H"
  print ""
  print "#include <stdint.h>"
  print ""
  print "typedef struct my_script_extension_range_t {"
  print "  uint32_t first;"
  print "  uint32_t last;"
  print "  uint16_t offset;"
  print "  uint16_t count;"
  print "} my_script_extension_range_t;"
  print ""
  print "static const uint32_t my_script_extension_tags[] = {"
  offset = 0
}
/^[0-9A-F]/ {
  line = $0
  sub(/#.*/, "", line)
  n = split(line, fields, ";")
  gsub(/[[:space:]]+/, " ", fields[1])
  sub(/^ /, "", fields[1])
  sub(/ $/, "", fields[1])
  range = fields[1]
  dots = index(range, "..")
  if (dots) {
    first = substr(range, 1, dots - 1)
    last = substr(range, dots + 2)
  } else {
    first = range
    last = range
  }
  scripts = fields[2]
  gsub(/^[[:space:]]+|[[:space:]]+$/, "", scripts)
  count = split(scripts, values, /[[:space:]]+/)
  for (i = 1; i <= count; i++) print "  " tag(values[i]) ","
  ranges[++range_count] = sprintf("  { %s, %s, %d, %d },", hex(first), hex(last), offset, count)
  offset += count
}
END {
  print "};"
  print ""
  print "static const my_script_extension_range_t my_script_extension_ranges[] = {"
  for (i = 1; i <= range_count; i++) print ranges[i]
  print "};"
  print ""
  print "#define MY_SCRIPT_EXTENSION_RANGE_COUNT (sizeof(my_script_extension_ranges) / sizeof(my_script_extension_ranges[0]))"
  print ""
  print "#endif"
}
' "$input" > "$output"
