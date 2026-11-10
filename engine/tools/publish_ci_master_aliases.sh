#!/usr/bin/env bash
set -euo pipefail

image=$1
expected_digest=$2
commit_sha=$3
inputs_hash=$4
source="$image@$expected_digest"
verified="$image:verified-$inputs_hash"
master="$image:$commit_sha"
latest="$image:latest"

if [[ ! "$expected_digest" =~ ^sha256:[0-9a-f]{64}$ ]]; then
    echo "invalid expected master image digest: $expected_digest" >&2
    exit 1
fi

docker pull "$source" >&2
source_id="$(docker image inspect "$source" --format '{{.Id}}')"
docker tag "$source" "$verified"
docker tag "$source" "$master"
docker tag "$source" "$latest"

for reference in "$verified" "$master" "$latest"; do
    alias_id="$(docker image inspect "$reference" --format '{{.Id}}')"
    if [ "$alias_id" != "$source_id" ]; then
        echo "master alias identity mismatch for $reference: $alias_id != $source_id" >&2
        exit 1
    fi
done

for reference in "$verified" "$master" "$latest"; do
    docker push "$reference" >&2
done
