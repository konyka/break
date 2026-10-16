# clean_room_build.ps1 -Repo <path> -Work <path> [-Backend vulkan|opengl]
# 语义与 clean_room_build.sh 完全一致：0 = 绿; 77 = UNAVAILABLE; 其他非零 = 失败。
param([Parameter(Mandatory=$true)][string]$Repo,
      [Parameter(Mandatory=$true)][string]$Work,
      [string]$Backend = "vulkan")
$ErrorActionPreference = "Stop"
$lockJson = Join-Path $Repo "engine/external/locked_dependencies.json"
if (-not (Test-Path $lockJson)) { Write-Error "locked_dependencies.json missing"; exit 2 }
if (Select-String -Path $lockJson -Pattern '"latest"' -Quiet) { Write-Error "manifest contains 'latest'"; exit 2 }
$sdkDir = Join-Path $Repo "engine/external/VulkanSDK"
$sdkLib = Join-Path $sdkDir "Lib/vulkan-1.lib"
if (-not (Test-Path $sdkLib)) { Write-Output "UNAVAILABLE: vendored Vulkan SDK not present"; exit 77 }
$lock = Get-Content $lockJson -Raw -Encoding UTF8 | ConvertFrom-Json
$vkEntry = $lock.dependencies | Where-Object { $_.name -eq 'vulkan-sdk' }
if (-not $vkEntry -or -not $vkEntry.sha256) { Write-Error "vulkan-sdk entry missing sha256 in lock manifest"; exit 2 }
$expect = $vkEntry.sha256.ToLowerInvariant()
$actual = (Get-FileHash $sdkLib -Algorithm SHA256).Hash.ToLowerInvariant()
if ($actual -ne $expect) { Write-Error "vendored Vulkan SDK sha256 mismatch"; exit 2 }
# git archive 不含被 git ignore 的 vendored SDK；把锁定清单里这套 SDK 显式注入
# 干净导出的环境（Bin 目录同时提供 vulkan-1.dll / shaderc_shared.dll 运行时）。
$env:VULKAN_SDK = $sdkDir
$env:PATH = (Join-Path $sdkDir "Bin") + ";" + $env:PATH
if (Test-Path $Work) { Remove-Item -Recurse -Force $Work }
New-Item -ItemType Directory -Force $Work | Out-Null
git -C $Repo archive HEAD -o "$Work/src.tar"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
tar -xf "$Work/src.tar" -C $Work
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
# Materialize locked, gitignored artifacts into the export so the in-export
# contract tests verify the same vendored set as a developer tree.
foreach ($f in @("Lib/vulkan-1.lib", "Lib/shaderc_shared.lib",
                 "Bin/VkLayer_khronos_validation.json", "Bin/dxc.exe", "Bin/glslang.exe")) {
    $src = Join-Path $sdkDir $f
    if (-not (Test-Path $src)) { Write-Output "UNAVAILABLE: vendored VulkanSDK file missing: $f"; exit 77 }
    $dst = Join-Path $Work "engine/external/VulkanSDK/$f"
    New-Item -ItemType Directory -Force (Split-Path $dst) | Out-Null
    Copy-Item $src $dst
}
$agilitySrc = Join-Path $Repo "engine/external/d3d12"
if (Test-Path $agilitySrc) {
    Copy-Item -Recurse -Force $agilitySrc (Join-Path $Work "engine/external/")
}
cmake -S "$Work/engine" -B "$Work/build" -G Ninja -DCMAKE_BUILD_TYPE=Debug `
    -DENGINE_RHI_BACKEND=$Backend | Tee-Object "$Work/configure.log"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if ($Backend -eq "vulkan" -and (Select-String -Path "$Work/configure.log" -Pattern "found OpenGL" -Quiet)) {
    Write-Error "clean-room violation: OpenGL discovered in a vulkan-only configure"; exit 3
}
cmake --build "$Work/build" --parallel
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
ctest --test-dir "$Work/build" -LE "graphics|fuzz" --output-on-failure
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Write-Output "CLEAN-ROOM OK (backend=$Backend)"
