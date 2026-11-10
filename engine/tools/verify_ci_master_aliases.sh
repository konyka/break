#!/usr/bin/env bash
set -euo pipefail

image=$1
expected_digest=$2
commit_sha=$3
inputs_hash=${4:-}

references=("$commit_sha" latest)
if [ -n "$inputs_hash" ]; then
    references+=("verified-$inputs_hash")
fi

for reference in "${references[@]}"; do
    if ! actual_digest="$(docker buildx imagetools inspect "$image:$reference" 2>/dev/null | awk '/^Digest:/ {print $2; exit}')"; then
        echo "failed to inspect master image alias: $reference" >&2
        exit 1
    fi
    if [ "$actual_digest" != "$expected_digest" ]; then
        echo "master alias digest mismatch for $reference: $actual_digest != $expected_digest" >&2
        exit 1
    fi
done
