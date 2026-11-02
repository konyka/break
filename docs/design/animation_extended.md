# 动画扩展：Morph、面部曲线与量化动画

日期：2026-11-02  
分支：`cry-wave1-animation`

## 1. 目标与边界

本设计实现总设计 P4 中由动画代理负责的部分：

- 有界 morph target、权重求值，以及变形后的真实蒙皮顶点输入；
- 命名面部表情、命名曲线及确定性分段线性求值；
- 版本化 TRS 动画量化、解压、损坏输入校验及可证明的往返误差上界；
- C11、固定容量、求值/编解码热路径不分配，失败不留下部分输出。

布娃娃、刚体姿态写回、IK/布娃娃互斥由物理代理负责，本设计不修改 `ragdoll` 或 `physics`。不修改既有 `animation.h`、`skeleton.h` 的 API，也不把固定容量的参数与 TRS 实现称为完整 CryAnimation 等价。v1 编解码器只覆盖 `AnimClip` 的静态 TRS 数据与 loop/playing 标志；含事件的 clip 会明确拒绝，避免静默丢失事件，播放游标不作为资源数据保存。

## 2. 方案取舍

### 采用：独立模块与真实顶点布局适配

新增 `morph`、`facial`、`anim_compression` 三个独立 TU。morph 适配器直接读写引擎已有的 64 字节 `SkinnedVertex`（pos3、normal3、uv2、joints u32x4、weights f32x4），测试把适配器输出送入现有 `lod_skin_positions`。优点是边界清晰、无既有 ABI 改动，并验证“先 morph、后蒙皮”的实际数据流，而非只检查权重字段。

### 不采用：把所有状态并入 Skeleton

在 `Skeleton` 内嵌入 morph、面部和压缩字节会增加每个骨架的内存占用并改变公共布局，还会把资源编解码与每帧姿态计算耦合。只有确有运行时需要才应改 skeleton，本方案无需修改。

### 不采用：动态数组或通用资源框架

按顶点数/target 数动态分配能支持任意资产，但不符合本轮固定容量和热路径不分配约束，也会引入新的所有权与失败回滚问题。调用者提供输入、输出和压缩字节存储，模块不取得其所有权。

## 3. 数据模型与容量

### 3.1 Morph

`AnimMorphSet` 保存 1 至 65,536 个顶点的共同拓扑和最多 32 个 target。每个 target 有最长 31 字节的唯一非空名称及调用者持有的 `Vec3 position_deltas[vertex_count]`；名称或 target 容量超限、空指针、非有限 delta 均返回 `false`，不追加半成品。

权重数量必须等于 target 数，每个权重必须有限且在 `[0, 1]`。求值公式为：

```
out[v] = base[v] + sum(target[t].position_deltas[v] * weight[t])
```

base、权重、delta 或计算结果出现 NaN/Inf 时失败。实现先完整计算并检查所有结果，再执行第二遍写出，因此失败时输出逐字节不变。无 target 是合法情况，结果是 base 的拷贝；允许输入输出原位复用。

蒙皮适配器要求输出至少 `vertex_count * 64` 字节，只改每条记录的 pos3，保留 normal、UV、joint、weight。它消费和产生的正是资产加载器、GPU 蒙皮和 `lod_skin_positions` 使用的记录布局；测试用编译期布局断言防止两套定义漂移。

### 3.2 面部

`AnimFacialLibrary` 最多包含 16 个唯一命名 expression，每个 expression 最多 8 条唯一命名 curve，每条 curve 最多 16 个关键帧。curve 通过 morph target 名称绑定，而不是持久化不稳定指针。

每个关键帧含有限时间和 `[0, 1]` 内的有限权重；时间必须非递减。求值使用分段线性插值，重复时间取较晚关键帧，首帧前/末帧后保持端点。空 expression 输出全零权重。目标名不存在、expression 不存在、权重数组大小不等于 morph target 数、时间为非有限值时失败且输出不变。面部模块只生成权重，调用者可把它直接交给 morph 求值，不在热路径隐含分配临时权重数组。

## 4. 量化格式 v1

### 4.1 存储与版本

字节流全部按 little-endian 显式读写，不使用 packed struct 或别名强转。格式为：

- 32 字节头：magic `BANM`、version=1、header_size=32、total_size、joint_count、channel_count、duration f32、flags、payload_size、CRC32；
- 每 channel 40 字节：joint u16、path u8、interp u8、key_count u16、保留字段、min[4] f32、max[4] f32；
- 每关键帧：time u16，后跟 translation/scale 的 xyz 三个 u16 或 rotation 的 xyzw 四个 u16。

flags 仅定义 loop 与 playing 位，其余位必须为零。CRC32 覆盖全部 payload；解码还要求精确总长度、保留位为零、规范字段和全部通道记录边界正确，拒绝截断与尾随字节。版本不匹配返回 `ANIM_CODEC_VERSION`，其他损坏返回 `ANIM_CODEC_CORRUPT`，调用参数或源数据非法返回 `ANIM_CODEC_INVALID`，输出容量不足返回 `ANIM_CODEC_CAPACITY` 并报告所需大小。

`joint_count` 为 1 至 128；channel 最多 64，keyframe 最多 256。零 channel 和零 keyframe channel 均合法并往返保留。joint 必须小于 joint_count，path/interp 枚举必须有效。源 duration/time/value 必须有限，时间在 `[0, duration]` 内且非递减；四元数必须可有限归一化。含事件的源 clip 返回 `ANIM_CODEC_INVALID`。解码先验证整个流及所有将写出的有限值，再写 `AnimClip`，所以失败不修改调用者输出。

### 4.2 量化规则与误差上界

时间使用 clip duration 全局仿射量化到 `0..65535`。每个 translation/scale channel 按分量使用该 channel 的 min/max 仿射量化；零范围分量精确保留。rotation 先归一化，再将每个 `[-1,1]` 分量量化到 `0..65535`，解码后归一化。

对有限且可表示的输入，定义：

- 时间绝对误差上界：`duration / (2 * 65535)`，另加测试中的 f32 解码余量；
- translation/scale 每分量绝对误差上界：`(max - min) / (2 * 65535)`，另加 f32 解码余量；
- rotation 归一化后的角度误差上界：`0.0001 rad`。四个分量各有最大 `1/65535` 的量化扰动，最坏欧氏扰动为 `2/65535`，重归一化后的角度误差小于该保守上界。

公共辅助函数返回时间和仿射分量的基础量化误差界，文档与测试使用同一公式但不以被测实现计算测试期望。测试另加 `1e-6` 的浮点余量，不放宽量化器本身的合同。

## 5. 错误与线程约束

所有新增对象的可变状态仅由 GameThread 修改；输入资源与输出快照由调用者管理生命周期。模块不创建线程、不调用 RHI、不进行文件 I/O。所有循环都有上述固定上限，所有大小乘法在分配外的调用者缓冲区访问前检查溢出。求值、编码和解码不调用 `malloc/calloc/realloc/free`。

## 6. TDD 与验证

每个生产行为先有直接调用测试并观察预期 RED，再写最小实现：

1. morph 加权结果、空集合、容量、非法名称/权重/非有限值及失败原子性；
2. 64 字节顶点属性保留，并用真实 `lod_skin_positions` 验证 morph 后蒙皮位置；
3. 命名 expression/curve、端点/中点/重复时间、空 expression、容量及非法绑定；
4. codec v1 全 TRS/空通道往返与误差界，容量报告、源非有限值/越界 joint；
5. 对有效流逐字节翻转确认全部拒绝，另构造带有效 CRC 的非有限字段、越界 joint/path/channel 以穿透到语义校验；
6. 对损坏输入、非有限、容量和往返各做至少一项实际生产代码变异，确认相应测试杀死变异；
7. 普通、ASan+UBSan、TSan focused 构建均使用 `-j3`，运行新增测试和既有 `test_animation`、`test_lod_skin`；
8. 只读审查 Critical/Important 问题并修复，最后执行 `git diff --check`，写报告并提交本分支，不 push、不建 PR。

## 7. 非目标与剩余限制

- 不实现 Cry 私有 CAF/DBA 格式、运行时任意大资产、GPU morph 纹理或自动 glTF morph 导入；本轮交付的是明确有界的 CPU morph→现有蒙皮输入路径。
- 不修改资产加载器或渲染器全局生命周期；调用方需把适配器输出上传到其既有 vertex buffer。headless 测试证明真实 CPU 蒙皮消费，不声称 GPU 像素验证。
- v1 不压缩事件，含事件输入明确失败；后续格式必须升版本，不能静默改变 v1 语义。
