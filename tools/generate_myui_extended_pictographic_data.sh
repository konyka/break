#!/bin/sh
set -eu

emoji_input=${1:-/usr/share/unicode/ucd/emoji/emoji-data.txt}
category_input=${2:-/usr/share/unicode/ucd/extracted/DerivedGeneralCategory.txt}
line_break_input=${3:-/usr/share/unicode/ucd/LineBreak.txt}
output=${4:-engine/src/myui/myr/generated/my_extended_pictographic_data.h}

for input in "$emoji_input" "$category_input" "$line_break_input"; do
  if [ ! -r "$input" ]; then
    echo "Unicode data file is not readable: $input" >&2
    exit 1
  fi
done

mkdir -p "$(dirname "$output")"
tmp="$output.tmp.$$"
trap 'rm -f "$tmp"' EXIT HUP INT TERM

perl - "$emoji_input" "$category_input" "$line_break_input" "$tmp" <<'PERL'
use strict;
use warnings;

my ($emoji_input, $category_input, $line_break_input, $output) = @ARGV;

sub read_property_ranges {
    my ($path, $wanted) = @_;
    open my $in, '<', $path or die "cannot read $path: $!\n";
    my @ranges;
    while (my $line = <$in>) {
        $line =~ s/#.*//;
        next unless $line =~ /;/;
        my ($range, $property) = split /;/, $line, 2;
        $range =~ s/\s+//g;
        $property =~ s/^\s+|\s+$//g;
        next unless $property eq $wanted;
        my ($lo, $hi) = $range =~ /^([0-9A-Fa-f]+)(?:\.\.([0-9A-Fa-f]+))?$/;
        die "invalid range $range in $path\n" unless defined $lo;
        $hi = $lo unless defined $hi;
        push @ranges, [hex($lo), hex($hi)];
    }
    close $in or die "cannot close $path: $!\n";
    return merge_ranges(\@ranges);
}

sub merge_ranges {
    my ($ranges) = @_;
    my @merged;
    for my $range (sort { $a->[0] <=> $b->[0] } @$ranges) {
        if (@merged && $range->[0] <= $merged[-1][1] + 1) {
            $merged[-1][1] = $range->[1] if $range->[1] > $merged[-1][1];
        } else {
            push @merged, [$range->[0], $range->[1]];
        }
    }
    return \@merged;
}

sub intersect_ranges {
    my ($left, $right) = @_;
    my @out;
    my ($i, $j) = (0, 0);
    while ($i < @$left && $j < @$right) {
        my $lo = $left->[$i][0] > $right->[$j][0]
            ? $left->[$i][0] : $right->[$j][0];
        my $hi = $left->[$i][1] < $right->[$j][1]
            ? $left->[$i][1] : $right->[$j][1];
        push @out, [$lo, $hi] if $lo <= $hi;
        if ($left->[$i][1] < $right->[$j][1]) { $i++; }
        else { $j++; }
    }
    return \@out;
}

sub subtract_ranges {
    my ($left, $right) = @_;
    my @out;
    my $j = 0;
    for my $range (@$left) {
        my $cursor = $range->[0];
        while ($j < @$right && $right->[$j][1] < $cursor) { $j++; }
        my $k = $j;
        while ($k < @$right && $right->[$k][0] <= $range->[1]) {
            push @out, [$cursor, $right->[$k][0] - 1]
                if $cursor < $right->[$k][0];
            $cursor = $right->[$k][1] + 1 if $right->[$k][1] + 1 > $cursor;
            last if $cursor > $range->[1];
            $k++;
        }
        push @out, [$cursor, $range->[1]] if $cursor <= $range->[1];
    }
    return \@out;
}

my $extended = read_property_ranges($emoji_input, 'Extended_Pictographic');
my $unassigned = read_property_ranges($category_input, 'Cn');
my $explicit_id = read_property_ranges($line_break_input, 'ID');
my $unassigned_extended = intersect_ranges($extended, $unassigned);
my $id_extended = intersect_ranges($unassigned_extended, $explicit_id);
my $xx_extended = subtract_ranges($unassigned_extended, $id_extended);

push @$xx_extended, [0xEFFFD, 0xEFFFD];
$xx_extended = merge_ranges($xx_extended);

open my $out, '>', $output or die "cannot write $output: $!\n";
print {$out} "/* Generated from Unicode 17 emoji/UCD data. Do not edit. */\n";
print {$out} "#ifndef MY_EXTENDED_PICTOGRAPHIC_DATA_H\n#define MY_EXTENDED_PICTOGRAPHIC_DATA_H\n\n";
print {$out} "#include <stdint.h>\n\n";
print {$out} "typedef struct my_extended_pictographic_range_t {\n";
print {$out} "  uint32_t first;\n  uint32_t last;\n";
print {$out} "} my_extended_pictographic_range_t;\n\n";
print {$out} "static const my_extended_pictographic_range_t MY_EXTENDED_PICTOGRAPHIC[] = {\n";
for my $range (@$extended) {
    printf {$out} "    {0x%Xu, 0x%Xu},\n", $range->[0], $range->[1];
}
print {$out} "};\n\n";
print {$out} "static const my_extended_pictographic_range_t MY_ID_EXTENDED_PICTOGRAPHIC_UNASSIGNED[] = {\n";
for my $range (@$id_extended) {
    printf {$out} "    {0x%Xu, 0x%Xu},\n", $range->[0], $range->[1];
}
print {$out} "};\n\n";
print {$out} "static const my_extended_pictographic_range_t MY_XX_EXTENDED_PICTOGRAPHIC_UNASSIGNED[] = {\n";
for my $range (@$xx_extended) {
    printf {$out} "    {0x%Xu, 0x%Xu},\n", $range->[0], $range->[1];
}
print {$out} "};\n\n#endif /* MY_EXTENDED_PICTOGRAPHIC_DATA_H */\n";
close $out or die "cannot close $output: $!\n";
PERL

mv "$tmp" "$output"
trap - EXIT HUP INT TERM
