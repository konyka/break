#!/usr/bin/env bash
set -euo pipefail

image=$1
inputs_hash=$2
candidate="$image:candidate-$inputs_hash"
verified="$image:verified-$inputs_hash"

candidate_id="$(docker image inspect "$candidate" --format '{{.Id}}')"
docker tag "$candidate" "$verified"
verified_id="$(docker image inspect "$verified" --format '{{.Id}}')"
if [ "$candidate_id" != "$verified_id" ]; then
    echo "candidate identity mismatch: $candidate_id != $verified_id" >&2
    exit 1
fi

docker push "$verified"
if ! registry_digest="$(docker buildx imagetools inspect "$verified" 2>/dev/null | awk '/^Digest:/ {print $2; exit}')"; then
    echo "failed to inspect published candidate digest: $verified" >&2
    exit 1
fi
if [[ ! "$registry_digest" =~ ^sha256:[0-9a-f]{64}$ ]]; then
    echo "failed to inspect published candidate digest: $verified" >&2
    exit 1
fi
printf '%s\n' "$registry_digest"
