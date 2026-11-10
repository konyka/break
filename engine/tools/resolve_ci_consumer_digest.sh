#!/usr/bin/env bash
set -euo pipefail

image=$1
verified_digest=${2:-}
publish_digest=${3:-}
override_digest=${4:-}

inspect_public_digest() {
    local reference=$1
    local digest
    if ! digest="$(docker buildx imagetools inspect "$reference" 2>/dev/null | awk '/^Digest:/ {print $2; exit}')"; then
        echo "failed to resolve immutable public digest: $reference" >&2
        return 1
    fi
    if [[ ! "$digest" =~ ^sha256:[0-9a-f]{64}$ ]]; then
        echo "failed to resolve immutable public digest: $reference" >&2
        return 1
    fi
    printf '%s' "$digest"
}

if [ -n "$verified_digest" ]; then
    selected="$image@$verified_digest"
elif [ -n "$publish_digest" ]; then
    selected="$image@$publish_digest"
elif [ -n "$override_digest" ]; then
    selected="$override_digest"
else
    if ! public_digest="$(inspect_public_digest "$image:latest")"; then
        exit 1
    fi
    selected="$image@$public_digest"
fi

if [[ ! "$selected" =~ ^ghcr\.io/.+@sha256:[0-9a-f]{64}$ ]]; then
    echo "no immutable consumer digest available; set a valid fallback override or publish the candidate" >&2
    exit 1
fi
printf '%s\n' "$selected"
