# Task 4 report — break_update (signed manifest + content-addressed store)

Plan: `docs/superpowers/plans/2026-10-24-stage5-security-foundations.md` Task 4. Commit stacked on `b7e6242f` (branch `sdd/stage5-security-foundations`).

## Delivered

- `engine/src/update/break_update.h` — 接口按计划 verbatim（15 个公开符号：manifest 10 + store 5，签名与行内注释逐字保留，含顶部格式注释块）；上方独立补充块文档化：无 oracle 错误纪律（parse NULL / verify false 不可区分）、canonical 执行细则（可打印 ASCII+LF、必须尾 LF、`: ` 单空格分隔、小写 hex、数字无前导零、base64 88 字符含 canonical pad bits、chunk 名严格递增且唯一）、1 MiB 上限使 65536 chunk 上限实际不可达（两者均强制——文档化）、客户端只验签（库内无签名入口）、store 纪律（put 名字=计算哈希、get verify-on-read、恰好按 stat 长度读关闭尺寸竞争窗、零长 chunk 语义）、OpenSSL OOM 不可注入声明。
- `engine/src/update/break_update.c` — 单 TU 实现。**两遍解析**：pass 1 在任何按攻击者计数分配内存之前完成全部结构/canonical 校验（键序固定 version/channel/platform/min-version、`chunk: <64小写hex> <u64十进制> <名>`、签名行必须为末行且覆盖其前全部字节）；pass 2 只填充已校验内容（不可能失败，仍防御性检查）。版本三元组 u32 溢出检查、size u64 溢出检查（`(UINT64_MAX-d)/10` 截断式）、chunk 名字符集 `[A-Za-z0-9._/-]` + 无前导 `/` + 无 `..` 子串 + ≤128B、channel/platform `[a-z0-9-]` 1..64B。base64 解码严格 canonical（恰好 86 数据字符 + `==`、末数据字符低 4 位必须为 0）。验签走 `break_crypto_ed25519_verify`，覆盖区间 = `text[0, sig_offset)`。compatible = channel 相等 AND platform 相等 AND 当前版本 ≥ min-version（三元组逐位词典序）。内部专用失败原因枚举 `UpdFailReason` 经 sink 消费、永不出 TU（计划"internal-only reason enum"约束的最小落地——公共 oracle 恰为"NULL = structure invalid"）。Store：`<root>/chunks/<sha256hex>`；open 时钉死长度上界（root + "/chunks/" + 64hex + NUL < `PLATFORM_FS_PATH_CAPACITY`）；put 先查 128 MiB 上限**再触碰数据**、哈希得名、经 PlatformAtomicWriter 写（fsync file → rename → fsync dir）；has 仅存在性（64 小写 hex 名校验 = 路径逃逸不可能）；get 按 stat 尺寸精确读 + 重哈希比对名（verify-on-read），任何不符 free 后 false；零长 chunk 合法（malloc(1) 可 free 指针 + len 0）。所有路径拼接用显式 memcpy 界检查（不用 snprintf——规避 `-Wformat-truncation` 在 -Werror 下的误报）。
- `engine/tests/test_break_update.c` — 19 个用例全绿：golden parse→accessor 全钉（version/min-version/channel/platform/3 chunk 的 name/hash/size、坏索引）→ verify true、错公钥 false；body 翻一个 hex 字符 → 结构有效 verify false；未签名（全零签名，canonical base64）→ parse OK verify false；截断矩阵（去尾 LF/签名行中部/签名行整行/body 中部/空）→ NULL；缺键 ×4/重复 channel/头键乱序/错 magic/空行 → NULL；name 矩阵（`..` 三种位置/前导 `/`/坏字符含空格 tab/空名/129B → NULL；128B 与嵌套路径接受钉）；chunk 列表（乱序/重复名 → NULL；零 chunk 合法）；字段严格性（version 前导零/u32 溢出/缺组件/多组件/非数字 → NULL，u32-max 接受钉；channel 大写/`_`/空/65B → NULL、64B 接受钉；hash 大写/63/65 字符 → NULL；size 前导零/u64 溢出/空 → NULL，**u64-max 接受钉**——128 MiB 是 store 限而非 manifest 语法限，文档化决策）；字节/布局（CR/0x7F/0x80/嵌入 NUL/双空格/tab 分隔/签名行后尾随垃圾 → NULL）；签名行严格性（87/89 字符、`=` 错位、非 base64 字符、缺 pad、非 canonical pad bits → NULL；canonical pad bits 改值 → parse OK 但 verify false 的区分钉）；>1 MiB → NULL；compatible 全矩阵（min 相等边界 true、更旧 false、channel/platform 不等 false、NULL 参数 false）；NULL 参数矩阵（含 void accessor 容忍 NULL）。Store：open 布局（建出 root+chunks 并经 platform_list_dir 实证、幂等重开、撞既有文件 NULL、NULL/空/超长 root NULL、destroy(NULL)）；put→has→get 往返字节等（11B + 2 MiB pattern，含文件尺寸钉与幂等重写）；外部翻 chunk 文件一字节 → get false（has 仍 true，钉"存在性≠完整性"）、外部截断 → 短读 false；零字节 chunk 往返（含 put(NULL,0)）；128 MiB+1 拒绝（检查先于数据访问，4 字节缓冲+超限声明安全——文档化测试形态）、put(NULL,5) false；name 字符集矩阵（大写/63/65/非hex/含斜杠/路径穿越/空/NULL → has/get 全 false）。
- `engine/tests/test_break_update_target_contract.cmake` — 形态仿 crypto 契约：① 目标在 `if(BREAK_ENABLE_CRYPTO)` 门控块内；② 源列表钉（`add_library(break_update STATIC src/update/break_update.c)`、全文件恰一处提及、engine 块不含 `src/update/`）；③ PUBLIC 链 break_crypto；④ engine/engine_demo/dxx_break/editor 单行链接禁链钉；⑤ nm 门：恰 15 个公开符号；⑥ 最小链接测试：`libbreak_update.a + libbreak_crypto.a + -lcrypto` + 内联编译 `platform_fs.c`（focused-test 先例），跑 manifest parse/verify-false/compatible + store put/has/get 往返。sanitizer 标志按 crypto 先例传播。
- `engine/CMakeLists.txt` — `break_update` 目标进既有门控块（`:320-345`，保持平铺无嵌套 if——crypto 契约的块提取依赖此形态，块注释已更新说明）；测试注册 + 契约 ctest（`:3971-4008`），标签 `headless;update;platform_contract`。
- **预授权清单外改动（显著标注）**：`engine/tests/test_platform_fs_write.c` 追加 `file_size_follows_symlinks` 用例（Task 3 审查 M2 遗留，控制器在 Task 4 派遣中预授权）——symlink→regular 报目标大小、dangling false、目录 false；POSIX-gated 注册；该文件既有行零改动。套件 10/10 绿。

## TDD 证据

- **RED**：先加测试 + 注册（链接尚不存在的 `break_update`，不加 target/契约）→ 编译通过、链接失败 exit 2：`/usr/bin/ld.bfd: 找不到 -lbreak_update`（cannot find -lbreak_update，Task 2 `cannot find -lbreak_crypto` 同形态）。日志 `/tmp/sdd_p5a_upd_red.log`。
- **GREEN**：补 `break_update.c` + 库 target + 契约注册 → 三树构建 exit 0，`test_break_update` **19/19** 通过。GREEN 过程中契约测试抓到一个真实语义点（非实现缺陷，见决策 2）：最小链接测试初版用全零公钥+全零签名断言 verify false，实际返回 **true**——OpenSSL 对 RFC 8032 验证方程做小序点接受（cofactorless），零键/零签名满足方程。修复方式：契约内嵌测试公钥（真实键 + 零签名 → false），并注释记录该性质。单元测试的"未签名"用例一直用真实公钥，不受影响。

## 三树 lanes（全部亲跑）

| 树 | 配置 | 结果 |
| --- | --- | --- |
| `build-sdd-p5a` | 默认 | 增量构建 exit 0（-Wall -Wextra -Werror -pedantic 无警告）；测试 19/19；`timeout -s KILL 60` 直跑 exit 0；全量构建 exit 0；契约 ctest 绿；**全量非图形套件 `ctest -LE 'graphics|fuzz'`：196 入选 = 195 通过 + 1 Windows-only skip（test_d3d12_dependency_gate），0 失败**（基线 194=193+1skip，本任务 +2：单测+契约，与简报一致）；`test_platform_fs_write` 10/10（含新 symlink 钉）；crypto 契约不受影响仍绿 |
| `build-sdd-p5a-asan` | ASan+UBSan | 目标增量构建 exit 0（`break_update.c.o` 含 17 个 `__asan` 引用实证插桩）；测试 ×3（`detect_leaks=1:halt_on_error=1` + `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`）全 19/19，零 sanitizer 报告（`/tmp/asan_p5a_upd_{1..3}.log`，grep 无 ERROR/LeakSanitizer/SUMMARY/runtime error）；ctest -R（单测+契约+fs_write）3/3 绿 |
| `build-sdd-p5a-tsan` | TSan | 同上（11 个 `__tsan` 引用）；测试 ×5（`halt_on_error=1` + `timeout -s KILL 60`）全 19/19，零 TSan 报告（`/tmp/tsan_p5a_upd_{1..5}.log`）；ctest -R 3/3 绿 |
| `build-sdd-p34-notests` | `ENGINE_BUILD_TESTS=OFF` | `libbreak_update.a` 构建 exit 0；全量构建 exit 0；测试目标如期缺席 |

## nm 门（libbreak_update.a，恰 15 个 T 符号，零 OpenSSL/break_crypto 再导出）

```
break_update_manifest_channel      break_update_manifest_parse        break_update_store_destroy
break_update_manifest_chunk_at     break_update_manifest_platform     break_update_store_get_chunk
break_update_manifest_chunk_count  break_update_manifest_verify       break_update_store_has_chunk
break_update_manifest_compatible   break_update_manifest_version      break_update_store_open
break_update_manifest_destroy      break_update_manifest_min_version  break_update_store_put_chunk
```

二进制反证：engine（archive）/engine_demo/dxx_break/editor 对 `break_update_*`/`break_crypto_*` 引用均为 0（nm 实测）。

## 测试密钥 provenance（测试专用，永非产品密钥）

2026-10-24 用系统 OpenSSL 3.5.9 CLI 一次性离线生成，scratch 目录 `/tmp/upd_t4_keygen`（不入库）：

```sh
openssl genpkey -algorithm ed25519 -out break_update_test_sk.pem
openssl pkey -in break_update_test_sk.pem -pubout -out break_update_test_pk.pem
openssl pkey -pubin -in break_update_test_pk.pem -outform DER | tail -c 32 | xxd -p -c 64
#   → 419d3071bda8be4a6cbab81a1822222f792ad811a880b9e7b198e8d17b2610e4 (嵌入为 TEST_PUBKEY_HEX)
# chunk 哈希 = sha256sum of printf 'break-update-test-chunk-{alpha,beta,gamma}'
openssl pkeyutl -sign -inkey break_update_test_sk.pem -rawin -in golden_body.bin | base64
#   → GOLDEN_MANIFEST 的 signature 行
openssl pkeyutl -verify -pubin -inkey break_update_test_pk.pem -rawin -in golden_body.bin -sigfile golden_sig.bin
#   → "Signature Verified Successfully"（独立 CLI 交叉验证）
```

**声明**：该密钥对仅为测试向量存在；私钥只在向量生成时使用一次、不以任何形式入库（仓库只嵌公钥 hex 与 golden manifest 文本）；它永非、也永不得成为产品签名密钥。产品密钥的生成/保管/轮换属 Phase B/C（威胁模型 §11 已登记）。生成后 scratch 目录已删除（`rm -rf /tmp/upd_t4_keygen`）。

## 计数口径说明

基线 194 = 193 pass + 1 skip（Task 3 后）。本任务新增 **2** 个 ctest（`test_break_update` + `test_break_update_target_contract`）→ **196 = 195 + 1 skip**，与简报"本任务 +2"一致。`test_platform_fs_write` 是既有 ctest（+1 内部用例，不加 ctest 计数）。

## 决策点

1. **零 chunk manifest 合法**：计划格式注释中 chunk 行为"..."（零次或多次重复）；零条目不违反任何 canonical 规则，parse 接受、count=0、chunk_at(0) false。已钉测试。
2. **全零 Ed25519 公钥接受性**（契约测试抓到的语义点）：OpenSSL 的 Ed25519 验签对全零公钥+全零签名返回成功（RFC 8032 验证方程的小序点/cofactorless 性质）。不影响安全姿态——真实使用中公钥是编译内置的可信常量、非攻击者控制；但"未签名路径"测试钉必须用真实公钥。契约最小链接测试已改为嵌入测试公钥并注释记录；单元测试的 unsigned 用例本就如此。
3. **65536 chunk 上限不可达**：最小 chunk 行 ~75B × 65537 ≈ 4.9 MiB > 1 MiB 总上限——计数上限作为纵深防御保留（先触发的一定是尺寸门），头文件与测试注释文档化，不伪造"已触发"声称。
4. **manifest 不钉 128 MiB chunk 上限**：计划 verbatim 的 size-dec 无上限（字段值 ≤64B 约束的是头部字段；20 位十进制天然满足），128 MiB 是 store put/get 侧上限。u64-max size 的 manifest parse 接受已钉测试（防止后续误改语义）。
5. **两遍解析**：pass 1 完整校验（含排序/唯一性）在任何按条目计数分配之前——满足"parse bounds enforced before any allocation sized by attacker-controlled numbers"；pass 2 不可能失败仍防御性检查 + 全量清理。
6. **put 恒重写**（不做 has-first 短路）：原子写覆盖语义已由 Task 3 保证，幂等；避免 TOCTOU 分叉路径。已钉幂等用例。
7. **get 的 TOCTOU 缓解**：按 stat 尺寸精确 fread（短读=false）+ verify-on-read 重哈希比对名——并发改写/截断不会交出错误字节。
8. **路径拼接用 memcpy 界检查**而非 snprintf：gcc `-Wformat-truncation` 在 -Werror 下对无界 %s 拼固定缓冲会误报；显式长度算术零警告且上界在 open 时一次性钉死。
9. **internal-only reason enum**：以 TU 内枚举 + sink 消费落地（调试器/grep 可见失败类别，公共 oracle 恰为 NULL），未新增任何公开 API。
10. **store_open 对 root 尾 `/` 宽容**：POSIX 折叠双斜杠，无害；长度上界检查不变。

## 给审查者的提示

- 头文件计划 verbatim 块逐字保留（含格式注释与全部行尾注释）；补充文档在其上方独立块，未改动 verbatim 行。
- golden manifest 覆盖区间实测：sig_offset=366（body 全长），验签经 break_crypto → OpenSSL EVP；向量经 openssl CLI 独立 verify 交叉验证。
- 契约 cmake 的禁链钉/源列表钉形态与 crypto 契约逐行对齐；最小链接测试额外内联编译 `platform_fs.c`（store 依赖 PAL，engine 保持其唯一生产归属）。
- 非 canonical pad-bits 钉（golden sig 第 85 字符 `w`→`x`）依赖该字符当前为 canonical 值；golden 再生成时需保持该断言（测试内有 `ASSERT_EQ(sig[85], 'w')` 前置钉）。
- Fuzz lane 未构建：按 house 口径记 `Not Run`。
- `git diff --check` 干净。

## 遗留风险

- 决策 2 的 OpenSSL 小序点接受性：若未来 Phase B/C 把验签公钥变为可配置/外部输入（非编译内置常量），需重估该性质（当前架构下不可达——无此类代码路径）。
- Win32 端无本 lane 验证：break_update.c 本身只用 C 标准库 + PAL（PAL 的 Win32 分支同 Task 3 已知 compile-only 状态）；首个 Windows lane 需跑测试套件。
- `fopen/fread` 的 store 读路径不做 fsync-后一致性假设之外的崩溃语义承诺（写侧耐久性由 PAL 原子提交保证；读侧 verify-on-read 兜底）。
- 测试 ASSERT 中途 bail 会在 /tmp 留残目录（house 先例 R444 形态，逐用例独立目录名 + 每进程 PID，不影响后续运行）。
