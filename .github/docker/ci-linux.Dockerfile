# CI base image for the Linux lanes of .github/workflows/ci.yml.
#
# Why: the lanes used to `apt-get install` on every run. Azure's Ubuntu mirror
# intermittently stalls on the runners (R674-R682: 10 of the last 40 `CI` runs
# failed in "Install dependencies" on 2026-10-23), and the retry/cache logic
# around it only reduced the odds. Here apt runs once, at image build time, and
# the lanes just pull the finished image.
#
# Contents = the union of what the lanes install today, with the same pins
# (cmake=3.28.*, libvulkan-dev=1.3.275.*, libshaderc-dev=2023.8*, see
# engine/external/LOCKED_DEPENDENCIES.md). libssl-dev (noble: OpenSSL 3.0.x)
# is required by break_crypto / break_update / Snowflake TLS, all on by default
# (BREAK_ENABLE_CRYPTO); without it every Linux configure fails. Rebuilt by
# .github/workflows/ci-image.yml whenever this file changes.
#
# NOT in the image: wine / vkd3d (proton lane needs i386 multiarch and runs
# weekly), Windows / macOS tooling.
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# apt retries are cheap here: this runs once per image build, not per CI run.
RUN printf 'Acquire::Retries "5";\nAcquire::http::Timeout "30";\nAcquire::https::Timeout "30";\n' \
        > /etc/apt/apt.conf.d/80-ci-retries \
 && apt-get update \
 && apt-get install -y --no-install-recommends \
        ca-certificates curl git sudo xz-utils zstd python3 file procps make \
        build-essential gcc \
        clang lld llvm \
        clang-18 lld-18 llvm-18-tools \
        cmake=3.28.* ninja-build pkg-config \
        libx11-dev libxrandr-dev \
        libgl1-mesa-dev libgl1-mesa-dri libegl1-mesa-dev libgles2-mesa-dev \
        libfreetype6-dev \
        libssl-dev \
        libvulkan-dev=1.3.275.* libshaderc-dev=2023.8* \
        mesa-vulkan-drivers vulkan-validationlayers vulkan-tools \
        xvfb x11-utils \
        libwayland-dev wayland-protocols libxkbcommon-dev weston \
        fonts-noto-cjk \
 && rm -rf /var/lib/apt/lists/*

# actions/checkout leaves the workspace owned by the runner user while the job
# runs as root inside the container; git then refuses the repo ("dubious
# ownership"), which breaks `git archive` in tools/clean_room_build.sh.
RUN git config --system --add safe.directory '*'

# The lanes' `sudo` calls (sysctl for TSan, apt in the fallback path) expect a
# passwordless sudo; the container runs as root so this is a harmless no-op
# there, but keeps the same scripts working if the image is used as a user.
RUN echo 'ALL ALL=(ALL) NOPASSWD:ALL' > /etc/sudoers.d/ci && chmod 0440 /etc/sudoers.d/ci

LABEL org.opencontainers.image.source="https://github.com/konyka/break"
LABEL org.opencontainers.image.description="Pre-installed build/test dependencies for break CI Linux lanes"
