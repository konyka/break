#!/bin/sh
set -eu

input=${1:-/usr/share/unicode/ucd/UnicodeData.txt}
output=${2:-engine/src/myui/myr/generated/my_combining_marks_data.h}
readme=${3:-$(dirname "$input")/ReadMe.txt}
expected_version=17.0.0

if [ ! -r "$input" ]; then
  echo "UnicodeData.txt is not readable: $input" >&2
  exit 1
fi
if [ ! -r "$readme" ] || ! grep -Fq "Version $expected_version" "$readme"; then
  echo "Unicode UCD $expected_version is required; invalid ReadMe.txt: $readme" >&2
  exit 1
fi

mkdir -p "$(dirname "$output")"
perl - "$input" "$output" <<'PERL'
use strict;
use warnings;

my ($input, $output) = @ARGV;
open my $in, '<', $input or die "cannot read $input: $!\n";
my @points;
while (my $line = <$in>) {
    chomp $line;
    my @fields = split /;/, $line, -1;
    next unless @fields >= 3;
    next unless $fields[2] eq 'Mn' || $fields[2] eq 'Mc' || $fields[2] eq 'Me';
    push @points, hex($fields[0]);
}
close $in or die "cannot close $input: $!\n";

my @ranges;
for my $point (@points) {
    if (@ranges && $point == $ranges[-1][1] + 1) {
        $ranges[-1][1] = $point;
    } else {
        push @ranges, [$point, $point];
    }
}

open my $out, '>', $output or die "cannot write $output: $!\n";
print {$out} "/* Generated from UnicodeData.txt (Unicode UCD 17.0.0), categories Mn/Mc/Me. */\n";
print {$out} "#ifndef MY_COMBINING_MARKS_DATA_H\n#define MY_COMBINING_MARKS_DATA_H\n\n";
print {$out} "#define MY_COMBINING_MARKS_UCD_VERSION \"17.0.0\"\n\n";
print {$out} "#include <stdint.h>\n\n";
print {$out} "typedef struct my_combining_mark_range_t {\n";
print {$out} "  uint32_t first;\n  uint32_t last;\n";
print {$out} "} my_combining_mark_range_t;\n\n";
print {$out} "static const my_combining_mark_range_t MY_COMBINING_MARKS[] = {\n";
for my $range (@ranges) {
    printf {$out} "    {0x%Xu, 0x%Xu},\n", $range->[0], $range->[1];
}
print {$out} "};\n\n#endif /* MY_COMBINING_MARKS_DATA_H */\n";
close $out or die "cannot close $output: $!\n";
PERL
