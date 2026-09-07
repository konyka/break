#!/bin/sh
set -eu

input=${1:-/usr/share/unicode/ucd/LineBreak.txt}
output=${2:-engine/src/myui/myr/my_line_break_data.h}

if [ ! -r "$input" ]; then
  echo "LineBreak.txt is not readable: $input" >&2
  exit 1
fi

version=$(sed -n 's/^# LineBreak-\([0-9][0-9.]*\)\.txt$/\1/p' "$input" | head -n 1)
if [ -z "$version" ]; then
  echo "cannot determine LineBreak UCD version: $input" >&2
  exit 1
fi
if [ "$version" != "17.0.0" ]; then
  echo "Unicode UCD 17.0.0 is required; found $version" >&2
  exit 1
fi

mkdir -p "$(dirname "$output")"
tmp="$output.tmp.$$"
trap 'rm -f "$tmp"' EXIT HUP INT TERM

perl -Mstrict -M warnings -e '
  my ($input, $output, $version) = @ARGV;
  open my $in, "<", $input or die "cannot read $input: $!\n";
  my @entries;
  my %map = (
    SP => "MY_LB_SP",
    BK => "MY_LB_BK", CR => "MY_LB_BK", LF => "MY_LB_BK", NL => "MY_LB_BK",
    HY => "MY_LB_HY", BA => "MY_LB_BA", BB => "MY_LB_BB", B2 => "MY_LB_B2",
    IN => "MY_LB_IN", CB => "MY_LB_CB",
    OP => "MY_LB_OP",
    NS => "MY_LB_NS",
    IS => "MY_LB_IS", SY => "MY_LB_SY", PO => "MY_LB_PO", PR => "MY_LB_PR",
    QU => "MY_LB_QU", HH => "MY_LB_HH",
    ZW => "MY_LB_ZW",
    AL => "MY_LB_AL", AI => "MY_LB_AI", AK => "MY_LB_AK", AP => "MY_LB_AP",
    AS => "MY_LB_AS", H2 => "MY_LB_AL", H3 => "MY_LB_AL", HL => "MY_LB_HL",
    CL => "MY_LB_CL", CP => "MY_LB_CP", EX => "MY_LB_EX",
    JL => "MY_LB_AL", JT => "MY_LB_AL", JV => "MY_LB_AL", NU => "MY_LB_NU",
    SA => "MY_LB_SA", CM => "MY_LB_CM", GL => "MY_LB_GL", WJ => "MY_LB_AL",
    ZWJ => "MY_LB_AL", RI => "MY_LB_AL", EB => "MY_LB_EB", EM => "MY_LB_EM",
    CJ => "MY_LB_CJ", SG => "MY_LB_AL", VF => "MY_LB_VF", VI => "MY_LB_VI",
  );
  while (<$in>) {
    next if /^\s*#/ || !/;/;
    s/#.*//;
    my ($range, $property) = split /;/, $_, 2;
    $range =~ s/\s+//g;
    $property =~ s/\s+//g;
    my ($lo, $hi) = $range =~ /^([0-9A-Fa-f]+)(?:\.\.([0-9A-Fa-f]+))?$/;
    die "invalid range: $range\n" unless defined $lo;
    $hi = $lo unless defined $hi;
    my $class = $map{$property} // "MY_LB_ID";
    next if $class eq "MY_LB_ID";
    push @entries, [hex($lo), hex($hi), $class];
  }
  close $in;
  my @merged;
  for my $entry (@entries) {
    if (@merged && $merged[-1][2] eq $entry->[2] &&
        $merged[-1][1] + 1 == $entry->[0]) {
      $merged[-1][1] = $entry->[1];
    } else {
      push @merged, $entry;
    }
  }
  open my $out, ">", $output or die "cannot write $output: $!\n";
  print $out "/**\n";
  print $out " * \@file my_line_break_data.h\n";
  print $out " * \@brief GENERATED from Unicode UCD LineBreak data. Do not edit.\n";
  print $out " * Simplified classes retain the conservative myui wrap contract.\n";
  print $out " */\n";
  print $out "#ifndef MY_LINE_BREAK_DATA_H\n#define MY_LINE_BREAK_DATA_H\n\n";
  print $out "#include <stdint.h>\n\n";
  print $out "#define MY_LINE_BREAK_UCD_VERSION \"$version\"\n\n";
  print $out "typedef struct my_lb_entry_t {\n  uint32_t lo, hi;\n  uint8_t cls;\n} my_lb_entry_t;\n\n";
  print $out "static const my_lb_entry_t MY_LINE_BREAKS[] = {\n";
  for my $entry (@merged) {
    printf $out "    {0x%04Xu, 0x%04Xu, %s},\n", @$entry;
  }
  print $out "};\n\n#endif /* MY_LINE_BREAK_DATA_H */\n";
  close $out;
' "$input" "$tmp" "$version"

mv "$tmp" "$output"
trap - EXIT HUP INT TERM
