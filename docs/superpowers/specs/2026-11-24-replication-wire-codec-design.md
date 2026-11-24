# 复制分片 wire codec 设计（2026-11-24）

## 目标与边界

`BreakReplicationFragment` 含有指针和 `size_t`，不能直接作为跨端 packed struct 发送。本子项目提供独立、无分配的 canonical wire codec，供后续 session bridge 使用。

本项只新增 `break_replication_wire.{h,c}` 及 focused 测试，编入现有 `break_replication_core`。不注册消息 ID、不接 reactor/session、不修改 aspect 发送上限，也不宣称完成真实网络接线。

## 方案比较

- **采用：显式小端字段 + borrowed decode。** 编码逐字节写，解码返回指向输入缓冲的 fragment data，避免对齐、ABI、`size_t` 宽度和额外分配问题。
- packed wire struct。布局受编译器对齐和宿主整数宽度影响，且指针字段不能跨进程使用，不采用。
- 复用 aspect varint 编码。aspect 格式面向对象记录，不能表达 fragment 的固定安全边界；另写通用 varint 会增加规范与模糊解码面，不采用。

## Wire 格式

每条消息 payload 恰好为 40 字节头加非空 fragment data：

```text
offset  size  field
0       4     magic = "BRFG"
4       2     wire_version = 1 (little-endian)
6       2     header_bytes = 40 (little-endian)
8       8     delta_id (little-endian)
16      8     base_id (little-endian)
24      4     fragment_index (little-endian)
28      4     fragment_count (little-endian)
32      4     checksum (little-endian)
36      4     fragment_bytes (little-endian)
40      ...   fragment data
```

- 整个 wire payload 不超过 `BREAK_NET_MAX_PAYLOAD_SIZE`（64 KiB），所以数据片最多 **65496** 字节。
- 网络 `delta_id` 必须非零；内存 API 对 delta 0 的既有行为不变。`base_id` 与 checksum 的完整 32/64 位值都允许。
- `fragment_count` 为 1..1048576，`fragment_index < fragment_count`。bridge 后续应设置更小的网络准入上限，不能把这个内部绝对上限当生产配置。
- `fragment_bytes` 必须等于实际剩余长度；空数据、截断、尾随、错误 magic/version/header 都拒绝。
- decode 只验证结构，不重新计算 FNV-1a；checksum/base/high-water 由重组池继续校验。输出的 data 指针借用输入，调用者必须保证输入生命周期。

## 公共接口

```c
#define BREAK_REPLICATION_WIRE_VERSION 1u
#define BREAK_REPLICATION_WIRE_HEADER_SIZE 40u
#define BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT 1048576u
#define BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE \
    (BREAK_NET_MAX_PAYLOAD_SIZE - BREAK_REPLICATION_WIRE_HEADER_SIZE)

BreakReplicationFragmentResult break_replication_wire_encoded_size(
    const BreakReplicationFragment *fragment, size_t *out_size);
BreakReplicationFragmentResult break_replication_wire_encode(
    const BreakReplicationFragment *fragment,
    uint8_t *out, size_t capacity, size_t *out_size);
BreakReplicationFragmentResult break_replication_wire_decode(
    const void *data, size_t size, BreakReplicationFragment *out_fragment);
```

- 复用 `BreakReplicationFragmentResult`，不新增结果枚举。非法参数/结构为 `INVALID`，超上限或输出容量不足为 `OVER_LIMIT`；这些路径不分配，所以 `OUT_OF_MEMORY` 不会出现。
- 三个 API 都在入口把可写输出清零；`encoded_size` 可单独查询所需容量。encode 在校验或容量失败时不写输出缓冲。
- decode 失败时 `out_fragment` 全零；成功时所有标量按显式小端读取，不进行未对齐整数指针转换。

## TDD 与验收

新建 `test_break_replication_wire`：

1. 对已知 fragment 逐字节比对 canonical 编码，decode 后字段和 borrowed data 完全一致。
2. 多组 payload 经现有 fragmenter 后逐片 encode/decode，再经 pool 重组，内容一致；最大 65496 数据片成功，65497 拒绝。
3. encode/encoded_size 拒绝 NULL、空数据、delta 0、count 0/超限、index 越界、输出容量差一；失败输出和缓冲不变。
4. decode 拒绝 NULL、每一个截断长度、尾随字节、错误 magic/version/header、空数据、delta 0、index/count 错误、声明长度不符和超上限。
5. 定向变异覆盖错误端序、magic/header、容量差一、接受尾随、delta 0、borrowed 指针偏移和 count 校验。

先确认新目标/接口编译 RED，再实现到 GREEN。运行完整 Vulkan/OpenGL、项目选项 ASan+UBSan/TSan focused，追加状态/设计/缺口文档，独立评审后推送并核验远端。

## 后续边界

下一独立子项目才能注册 `0x4009` 并做 session bridge；aspect 接入前必须把发送 fragment_size 收窄到 65496，并为完成队列、每连接和全 manager 预算另设限制。本 codec 本身不是认证、可靠传输或 World delta 协议。
