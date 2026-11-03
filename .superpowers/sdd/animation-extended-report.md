# P4 动画扩展报告

日期：2026-11-03

分支：`cry-wave1-animation`

状态：实现与 focused 验证完成；仅本地提交，不 push、不建 PR。

## 1. 交付内容

- `animation/morph.h/.c`：最多 32 个命名 target、65,536 顶点；权重严格为有限 `[0,1]`，检查 delta/base/计算结果有限性。空 target 集合复制 base，原位 xyz 求值可用。所有求值先完整验证再写出，失败不改输出。
- `animation/facial.h/.c`：最多 16 个命名 expression，每个 8 条命名 curve，每条 16 个关键帧。curve 以 morph 名称绑定，支持分段线性插值、端点保持、重复时间取后键；空 expression 输出零权重。缺失 target、非有限时间和非法关键帧均失败，求值失败不部分写输出。
- `animation/anim_compression.h/.c`：版本化 `BANM` v1 TRS 字节流，显式 little-endian、32 字节头、40 字节 channel 头、payload CRC32、16 位时间/标量/四元数量化。保留 loop/playing、path/interp 和零 keyframe channel；含事件的 clip 明确拒绝，避免静默丢数据。
- `morph` 的 64 字节 `SkinnedVertex` 适配器只替换 pos3，保留 normal/UV/joints/weights。测试把结果直接传给现有 `lod_skin_positions`，验证最终蒙皮坐标包含 morph，而非只保存权重。
- `animation.h/.c` 仅新增 `anim_ik_solve_unless_ragdoll`，既有函数签名和公共结构布局不变。布娃娃激活时返回 `false` 且 TRS 逐字节不变；释放后调用同一个真实 `anim_ik_solve`。未修改 ragdoll/physics。
- 三个新 TU 均加入 `engine` 静态库；正常构建已成功生成 `libengine.a`。

## 2. 容量、格式与误差合同

- Morph：32 targets、65,536 vertices、名称 32 字节含 NUL。
- Facial：16 expressions、8 curves/expression、16 keys/curve。
- Codec：128 joints、64 channels、256 keys/channel，字节流硬上限由 `ANIM_CODEC_MAX_BYTES` 给出；所有记录要求精确长度，截断、尾随、非法保留字段和未知标志均拒绝。
- 时间基础量化误差上界：`duration / (2 * 65535)`。
- Translation/scale 分量基础量化误差上界：`(channel_max - channel_min) / (2 * 65535)`。
- Rotation 解码后归一化，角度误差保守上界：`0.0001 rad`。
- 往返测试在手算公式上另加 `1e-6` f32 余量；rotation 用四元数夹角直接检查。
- 编解码、面部和 morph 热路径没有 `malloc/calloc/realloc/free` 调用。

## 3. RED→GREEN 证据

以下均先运行失败，再实现或补齐防护：

- Morph：缺少头文件编译 RED；最小 stub 后 `morph_evaluates_bounded_weight_sum` 在求值返回 `false` 处运行时 RED。随后空集合复制、非法权重、非有限/溢出原子性、初始化边界、非法名称及非有限 delta 均各自观察到运行时 RED 后转绿。
- 真实蒙皮：适配器缺失编译 RED；stub 后 `morphed_vertex_is_consumed_by_existing_skinner` 运行时 RED。实现后 base `(1,0,0)` 加半个 `(0,2,0)` morph，再经 x+3 蒙皮得到 `(4,1,0)`，并验证非位置属性不变。
- Facial：缺少头文件编译 RED；stub 后命名 expression/curve 中点求值运行时 RED。缺失 target 原子性、非法 curve 数据和重复绑定随后分别 RED→GREEN。
- Codec：缺少头文件编译 RED；stub 后完整 TRS 往返在 size 查询处运行时 RED。主路径转绿后，payload 损坏因未检查 CRC 而 RED；源非有限/乱序/零四元数因未预校验而 RED；带有效 CRC 的空通道 NaN min/max、倒置范围和倒序时间分别驱动解码语义防护转绿。
- IK/布娃娃互斥：新增符号缺失编译 RED；stub 后释放状态未执行 IK 运行时 RED。最终激活时不变、释放后与直接 IK 结果逐字节一致。
- 负源枚举回归 `codec_rejects_negative_source_enums_before_writing` 在当前 GCC ABI 首次运行即通过：现有无符号枚举范围比较已经拒绝，故不宣称该测试有独立 RED，也未为伪造 RED 修改生产代码。

## 4. 实际变异检查

变异在 `build-animation-mutants` 的符号链接源码副本中进行，最终源文件未被原地改写；每项必须编译成功、测试失败且出现预期测试名才算杀死。

| 变异 | 杀死它的测试 | 结果 |
| --- | --- | --- |
| 跳过 payload CRC 比较 | `codec_rejects_payload_corruption_without_touching_output` | killed |
| 删除时间有限性/顺序/范围校验 | `codec_rejects_invalid_source_before_writing` | killed |
| 删除编码容量检查 | `codec_reports_capacity_and_rejects_wrong_lengths` | killed |
| 量化级数从 65,535 降为 255 | `codec_round_trip_stays_within_explicit_bounds` | killed |
| 删除 morph 结果有限性检查 | `morph_rejects_nonfinite_or_overflowing_results_atomically` | killed |
| IK 闸门忽略 `ragdoll_active` | `ragdoll_blocks_ik_without_mutating_local_pose` | killed |

两个最初存活的有益尝试也保留记录：只删除 value 有限性检查时，后续 min/max 有限性检查仍拒绝；只删除 `isfinite(time)` 时，`time > duration` 仍拒绝 Inf。它们不被计为“杀死”，改用上面的完整时间校验变异获得有效证据。首个 IK 变异因缺少括号触发 `-Werror` 编译失败，也不计为行为证据；修正为可编译 mutant 后才得到 killed。

## 5. 最终验证

所有构建均使用 `-j3`，CTest 均带 `--output-on-failure`。最终 regex 覆盖：

`test_anim_morph`、`test_anim_facial`、`test_anim_compression`、`test_anim_pose_authority`、`test_animation`、`test_anim_locomotion`、`test_anim_aim`、`test_lod_skin`。

- Normal：8/8 通过；另构建 `engine` 成功。
- ASan+UBSan：8/8 通过，无 sanitizer 诊断。
- TSan：8/8 通过，无 sanitizer 诊断。

构建目录：

- `build-animation-normal`
- `build-animation-asan`
- `build-animation-tsan`
- `build-animation-mutants`（隔离变异证据）

## 6. 自审

- 检查了全部新增生产文件、公共声明、CMake 接入和最终差异；没有未解决的 Critical/Important。
- 编解码使用两遍 decode，编码在写缓冲前完成整个源校验；morph 与面部失败均保持输出不变。
- 字节访问使用显式 endian 读取或 `memcpy`，未引入 packed 指针对齐 UB。
- 未修改 `docs/Implementation_Status.md`、master、ragdoll/physics 或其他子项目。

## 7. 真实限制

- 这是有界 CPU morph→现有蒙皮输入路径，不是完整 CryAnimation 等价；没有实现 Cry 私有 CAF/DBA 或任意大动态资源。
- 未做 Vulkan/OpenGL 像素测试或 GPU morph 纹理；headless 证据覆盖真实 CPU skinner。调用方仍需把适配器输出上传到既有 vertex buffer。
- 未实现自动 glTF morph 导入；target delta 和顶点存储由调用方持有。
- v1 不压缩事件，含事件输入返回 `ANIM_CODEC_INVALID`；播放游标不属于资源格式。
- IK 互斥是动画侧真实求解闸门，不是布娃娃驱动。GameThread 所有者必须传入当前 `Ragdoll.active`；刚体姿态写回与物理集成仍由物理代理负责。


## 8. 评审修复第 1 轮（2026-11-03）

### 8.1 修复与独立 RED/GREEN

1. **Facial 重复时间**：新增 `facial_repeated_times_select_later_key`，同一曲线覆盖首、中、尾重复。修复前结果为 `5 passed, 1 failed`，首重复返回 0.1 而非后键 0.2；将首前判断从 `time <= times[0]` 改为严格 `<` 后 `6/6` 通过。
2. **Facial 有限时间溢出**：新增 `facial_extreme_finite_curve_uses_wide_interpolation`，在 `[-FLT_MAX, FLT_MAX]` 上以 `FLT_MAX/2` 求值。修复前 `isfinite(weight)` 失败，`6 passed, 1 failed`；span、分子和插值改用 double 后结果有限且为 0.75，`7/7` 通过。
3. **Header 完整性**：新增 `codec_rejects_every_stream_byte_corruption`，逐字节翻转整个流并要求输出不变。修复前 header flags 翻转被接受，`8 passed, 1 failed`。编码格式升为 v2，CRC 覆盖 header `[0,28)` 加 payload `[32,end)`，CRC 字段自身四字节排除；测试中的语义损坏修复器同步该规则后 `9/9` 通过。
4. **量化中间舍入**：`codec_uses_wide_quantization_at_half_step_boundaries` 先得到 `10 passed, 1 failed`。双精度归一化/仿射量化后，评审 time 反例精确解为 `16.186769485473633f`，scalar 反例精确解为 `-37.1595344543457f`。
5. **最终 f32 舍入误差界**：双精度量化使 `codec_published_bounds_include_final_f32_rounding` 单独 RED（`10 passed, 1 failed`）：一个 range=0.1 的合法值仍比基础半步界多约 `7.3e-12` 误差。公共界改为量化半步加 `M*2^-23+2^-149`，再 `nextafterf(...,+INFINITY)`；修复后 `11/11` 通过。该项不是放宽测试 epsilon，而是同时改变量化实现并给出保守数值上界。
6. **Morph 初始化原子性**：`morph_invalid_init_preserves_existing_object_bytes` 用 0xA5 sentinel 覆盖零顶点与超容量，修复前 `9 passed, 1 failed`；先验证再 memset 后 `10/10` 通过。
7. **枚举 ABI**：普通 GCC 的负枚举测试本来就通过，因此没有伪造普通 RED。在隔离副本将 `AnimPathType` 改成 signed-int ABI 后，`codec_rejects_negative_source_enums_before_writing` 真实失败；path/interp 改显式白名单后，同一 ABI 变体全套通过，随后恢复头文件链接并由普通构建复验。
8. **Minor 覆盖**：17-key 检查移到空 expression，避免曲线已满提前返回；新增事件拒绝且输出不变、零 channel 往返。最终单元数为 facial 8/8、codec 13/13、morph 10/10。

### 8.2 本轮可编译变异

以下均在 `build-animation-mutants` 隔离源码副本中成功编译，退出码 1，并由指定测试杀死：

| Mutant | 预期失败测试 |
| --- | --- |
| 首前判断恢复 `<=` | `facial_repeated_times_select_later_key` |
| facial span/分子恢复 f32 | `facial_extreme_finite_curve_uses_wide_interpolation` |
| CRC 排除受保护 header | `codec_rejects_every_stream_byte_corruption` |
| 量化乘法恢复 f32 | `codec_uses_wide_quantization_at_half_step_boundaries` |
| 删除最终舍入余量 | `codec_published_bounds_include_final_f32_rounding` |
| morph 初始化先 memset | `morph_invalid_init_preserves_existing_object_bytes` |
| 绕过 path/interp 白名单 | `codec_rejects_negative_source_enums_before_writing` |
| 绕过 facial keyframe 容量 | `facial_rejects_seventeenth_key_before_insertion` |

删除舍入余量的第一次写法因未使用参数触发 `-Werror`，不计为证据；改为可编译的 `fabs(magnitude)*0.0` 后才记录 killed。

### 8.3 最终命令与输出

Normal（同时成功构建 `engine`）：

```bash
cmake -S engine -B build-animation-normal -DENGINE_RHI_BACKEND=opengl -DENGINE_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-animation-normal --target engine test_anim_morph test_anim_facial test_anim_compression test_anim_pose_authority test_animation test_anim_locomotion test_anim_aim test_lod_skin -j3
ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_(morph|facial|compression|pose_authority|locomotion|aim)|test_animation|test_lod_skin)$'
```

输出：`100% tests passed, 0 tests failed out of 8`。

ASan+UBSan：

```bash
cmake -S engine -B build-animation-asan -DENGINE_RHI_BACKEND=opengl -DENGINE_BUILD_TESTS=ON -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-animation-asan --target test_anim_morph test_anim_facial test_anim_compression test_anim_pose_authority test_animation test_anim_locomotion test_anim_aim test_lod_skin -j3
ctest --test-dir build-animation-asan --output-on-failure -R '^(test_anim_(morph|facial|compression|pose_authority|locomotion|aim)|test_animation|test_lod_skin)$'
```

输出：`100% tests passed, 0 tests failed out of 8`，无 ASan/UBSan 诊断。

TSan：

```bash
cmake -S engine -B build-animation-tsan -DENGINE_RHI_BACKEND=opengl -DENGINE_BUILD_TESTS=ON -DENGINE_USE_TSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-animation-tsan --target test_anim_morph test_anim_facial test_anim_compression test_anim_pose_authority test_animation test_anim_locomotion test_anim_aim test_lod_skin -j3
ctest --test-dir build-animation-tsan --output-on-failure -R '^(test_anim_(morph|facial|compression|pose_authority|locomotion|aim)|test_animation|test_lod_skin)$'
```

输出：`100% tests passed, 0 tests failed out of 8`，无 TSan 诊断。

文档同步后及最终暂存前均执行 `git diff --check`。v2 不兼容 v1 的 CRC 语义是明确版本升级：旧流返回 `ANIM_CODEC_VERSION_UNSUPPORTED`，不会静默按新规则解释。其余行为边界、GameThread 所有权、固定容量和热路径不分配约束不变。
