#!/bin/sh
set -eu

input=${1:-/usr/share/unicode/ucd/EastAsianWidth.txt}
output=${2:-engine/src/myui/myr/generated/my_east_asian_width_data.h}

if [ ! -r "$input" ]; then
  echo "EastAsianWidth.txt is not readable: $input" >&2
  exit 1
fi

version=$(sed -n 's/^# EastAsianWidth-\([0-9][0-9.]*\)\.txt$/\1/p' "$input" | head -n 1)
if [ "$version" != "17.0.0" ]; then
  echo "Unicode UCD 17.0.0 is required; found ${version:-unknown}" >&2
  exit 1
fi

mkdir -p "$(dirname "$output")"
tmp="$output.tmp.$$"
trap 'rm -f "$tmp"' EXIT HUP INT TERM

perl -Mstrict -M warnings - "$input" "$tmp" <<'PERL'
my ($input, $output) = @ARGV;
open my $in, '<', $input or die "cannot read $input: $!\n";
my @ranges;
while (<$in>) {
  s/#.*//;
  next unless /;/;
  my ($range, $property) = split /;/, $_, 2;
  $range =~ s/\s+//g;
  $property =~ s/\s+//g;
  next unless $property eq 'W' || $property eq 'F';
  my ($lo, $hi) = $range =~ /^([0-9A-Fa-f]+)(?:\.\.([0-9A-Fa-f]+))?$/;
  die "invalid range $range\n" unless defined $lo;
  $hi = $lo unless defined $hi;
  push @ranges, [hex($lo), hex($hi)];
}
close $in or die "cannot close $input: $!\n";
my @merged;
for my $range (sort { $a->[0] <=> $b->[0] } @ranges) {
  if (@merged && $range->[0] <= $merged[-1][1] + 1) {
    $merged[-1][1] = $range->[1] if $range->[1] > $merged[-1][1];
  } else {
    push @merged, $range;
  }
}
open my $out, '>', $output or die "cannot write $output: $!\n";
print $out "/**\n";
print $out " * \@file my_east_asian_width_data.h\n";
print $out " * \@brief GENERATED from Unicode UCD EastAsianWidth data. Do not edit.\n";
print $out " */\n";
print $out "#ifndef MY_EAST_ASIAN_WIDTH_DATA_H\n#define MY_EAST_ASIAN_WIDTH_DATA_H\n\n";
print $out "#include <stdint.h>\n\n";
print $out "#define MY_EAST_ASIAN_WIDTH_UCD_VERSION \"17.0.0\"\n\n";
print $out "typedef struct my_east_asian_width_range_t {\n";
print $out "  uint32_t first;\n  uint32_t last;\n";
print $out "} my_east_asian_width_range_t;\n\n";
print $out "static const my_east_asian_width_range_t MY_EAST_ASIAN_WIDTH_WIDE[] = {\n";
for my $range (@merged) {
  printf $out "    {0x%04Xu, 0x%04Xu},\n", @$range;
}
print $out "};\n\n#endif /* MY_EAST_ASIAN_WIDTH_DATA_H */\n";
close $out or die "cannot close $output: $!\n";
PERL

mv "$tmp" "$output"
trap - EXIT HUP INT TERM
