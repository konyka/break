# 崩溃符号化、聚类与上传（服务端半侧）

状态：2026-10-30 交付参考实现。这是**参考服务端和库**，不是生产服务。客户端半侧（捕获、spool、脱敏、上传接缝）见 `crash_reporting.md`。

## 1. 范围

交付的东西，全部在 Linux x86-64 上实测：

| 部分 | 文件 | 作用 |
|---|---|---|
| 符号读取与帧恢复 | `engine/src/crash/break_crash_symbolize.{h,c}` | 读 ELF 与 Mach-O 符号表，沿保存的 RBP 链从记录的栈窗口恢复调用栈 |
| 聚类与回归统计 | `engine/src/crash/break_crash_cluster.{h,c}` | 签名、按构建计数、已修复与回归标记，规范文本文件 |
| HTTP 上传适配器 | `engine/src/crash/break_crash_upload_http.{h,c}` | 实现 `BreakCrashUploadFn`，经 `break_http` POST |
| 参考收集服务 | `engine/tools/break_crash_server.c` | TLS 接收 `POST /crash`，符号化，计数 |
| 运维工具 | `engine/tools/break_crash_report.c` | 打印统计、登记构建、标记已修复 |
| 端到端 | `engine/tests/break_crash_e2e.c` + `test_break_crash_e2e.cmake` | 真实崩溃到统计报告 |

三个库都不链接进 `engine`、`engine_demo`、`dxx_break`、`editor`，`break_crash` 归档里也没有网络符号。契约测试 `test_break_crash_server_target_contract` 钉住这几点，并钉住三个库各自的导出符号清单（无测试钩子、无"不校验"开关）。

## 2. 符号读取

输入是客户端上传的记录加上构建时留下的未剥离二进制。符号库的目录布局是 `<root>/<build-id>/<module>`。记录和 ELF 文件都按不可信输入处理。

- 只读 64 位小端 x86-64（`EM_X86_64`）与 arm64（`EM_AARCH64`）ELF，其他 `e_machine` 仍拒绝。有 `.symtab` 用它，被剥离的文件退到 `.dynsym`。
- 所有偏移、大小做溢出安全的范围检查；任何一个区段声称的字节在文件之外，整个文件拒绝（返回 NULL，不崩溃）。文件超过 256 MiB 拒绝。符号表项大小必须等于 `Elf64_Sym`。符号名偏移必须落在字符串表内，字符串表末尾强制补 NUL。
- 符号查找要求地址落在 `[start, start+size)` 内；函数间的填充和最后一个函数之后都不解析。嵌套或别名符号向前走有界步数（64）。
- Mach-O（2026-11-17）：`break_macho_symbols_open` 读单架构 64 位小端 Mach-O（x86_64、arm64；EXECUTE、DYLIB、BUNDLE、DSYM）的 `LC_SYMTAB`，返回同一个 `BreakElfSymbols`。`break_crash_symbols_open` 按文件 magic 选 ELF 或 Mach-O，符号库用它，所以 `<root>/<build-id>/<module>` 里两种格式都可以放。规则：
  - 拒绝 32 位、大端、其他 CPU 和其他文件类型（含 OBJECT）。
  - 通用（fat）文件（2026-11-17）：大端头 `0xcafebabe`（20 字节条目）或 `0xcafebabf`（32 字节条目），条目数 1..32（`0xcafebabe` 也是 Java class 文件的 magic，那里此位置是 45 以上的版本号）。每个条目都先检查：slice 在文件内、位于条目表之后、与其他 slice 不重叠、CPU 不重复；选中的 slice 按它声明的大小当作单架构文件解析，且其 CPU 必须等于条目的 CPU。`break_macho_symbols_open_cpu(path, cpu)` 取指定 CPU（只接受 x86_64、arm64）；`break_macho_symbols_open` 与符号库保留 x86_64 默认 slice 选择；这不表示帧恢复只走 x86-64，调用方可用 `break_macho_symbols_open_cpu` 显式选择 arm64 slice；单架构文件仍按原样打开。
  - load command：`ncmds` ≤ 4096；每条 `cmdsize` ≥ 8、是 8 的倍数、不超出 `sizeofcmds`；`LC_SEGMENT_64` 的 `cmdsize` 必须等于 72 + 80 × nsects；section 的 `addr + size` 不回绕；`LC_SYMTAB` 最多一条，大小 24，符号表和字符串表都在文件内；`LC_UUID` 大小 24。没有 `__TEXT` 段的文件拒绝。
  - 保留的符号：不是 stab，类型为 `N_SECT`，`n_sect`（跨段从 1 计数）指向带 `S_ATTR_PURE_INSTRUCTIONS` 或 `S_ATTR_SOME_INSTRUCTIONS` 的 section，值落在该 section 内且不低于 `__TEXT` 的 vmaddr，名字在字符串表内且非空。去掉一个前导 `_`。
  - Mach-O 不存符号大小：一个符号延伸到下一个更高地址的符号或所在 section 的末尾，取较近者。同地址的别名大小相同。
  - 地址相对 `__TEXT` 的 vmaddr 存储，即相对镜像头的加载地址；`is_exec` 为 false，记录里的模块偏移直接查。构建 id 是 `LC_UUID` 的 32 位小写十六进制，没有时为空串。
- 构建 id 与模块名在拼路径前重新校验：构建 id 为 `[0-9a-z-]{1,64}`，模块名是一个可打印、不含 `/` 和 `\`、不是 `.` 或 `..`、不超过 255 字节的路径分量。记录里的值不可能指向符号根之外。
- 地址换算：`ET_EXEC`（固定地址可执行文件）的符号是绝对虚拟地址，用 `pc` 查；`ET_DYN`（共享库、PIE）的符号相对于加载偏移，用 `pc - bias` 查。这里首次实现时犯过错：没有区分两者，非 PIE 可执行文件的第 0 帧解析不出来；真实崩溃子进程的测试抓到，现在 PIE 与非 PIE 各有一个真实崩溃用例。
- 只缓存成功加载的符号文件（8 项轮转）。早先版本也缓存"没找到"，长期运行的服务会因此在符号文件迟到后永远解析不出该构建的崩溃；`symbols_uploaded_after_a_miss_are_found_by_the_same_open_store` 先红后绿。

## 3. 帧恢复

第 0 帧是记录里的 `rip`。其后沿保存的 RBP 链：`[rbp]` 是调用者的 rbp，`[rbp+8]` 是返回地址，两个字都必须完整落在记录的栈窗口内（窗口从崩溃时的 rsp 开始，最多 4 KiB）。

- 链必须严格向高地址增长；指回自己或更低的地址就停。伪造的链不能成环。
- 返回地址为 0、读出窗口、或达到 32 帧上限就停。
- 返回地址用 `pc-1` 查符号（避免把以 call 结尾的函数归到下一个函数），但帧里报告的是返回地址本身。
- 帧所属的模块由记录的模块表决定；模块表里没有、或符号库里没有对应文件的帧，保留模块名和偏移，不编造符号。

**诚实的局限**：这是帧指针展开，不是 DWARF CFI。不带帧指针编译的代码（常见的 `-O2` 发布版、大多数系统库）只会得到很短、甚至错误的链。第 0 帧可信，其后的帧是推测，文档化为局限，不在数据里标记。

## 4. 签名与聚类

签名是 `SHA-256` 对以下文本的摘要：固定前缀、信号编号、前三帧。已解析的帧写模块名加符号名；未解析但有模块的帧写模块名加模块内偏移；连模块都没有的写占位符。**不含** pid、tid、地址、构建 id，所以同一缺陷在不同进程、不同 ASLR 布局、不同构建里落在同一个簇。依赖偏移的未解析帧只在同一构建内聚类。

- 信号编号必须在 1..64，否则服务端以 400 拒绝。
- 帧的字段边界不会混淆：`("a","bc")` 与 `("ab","c")` 得到不同签名（有测试）。
- 前三帧之外的帧不影响签名。

统计保存在一个规范文本文件里（`break-crash-stats v1`），用 `PlatformAtomicWriter` 原子替换。解析器只接受序列化器逐字节会产生的文本：重新序列化比较，任何偏差都拒绝。因此：

- 打开一个不能解析的文件返回 NULL，**不会**当作空库重置；服务端对此答 500，运维工具拒绝修改。
- 签名按字典序严格递增；最后出现的构建不得早于首次出现的构建；所有构建下标必须在构建列表之内。
- 有界：4096 个签名（满了淘汰计数最低的），1024 个构建，4096 个记住的记录哈希。
- 读改写用 `<stats>.lock` 上的 `flock` 互斥，服务和运维工具共用。

**重复与回归**：服务端对规范化后的记录字节取 SHA-256，已记住的哈希不重复计数。客户端的 spool 是至少一次投递，应答丢失后会重试，所以这一条是必要的。构建按**登记顺序**排序（即发布顺序）。对一个签名调用 `mark_fixed(签名, 构建 B)` 之后：来自 B 或更早构建的报告照常计数但不算回归（旧客户端在修复发布后还会继续崩溃）；来自 B 之后登记的构建的报告把簇置为回归，且只在翻转那一次报告。对已有更晚构建报告过的签名标记修复，会立即置为回归。再次标记到更晚的构建会清除回归标记。

**淘汰的代价**：满 4096 个签名时淘汰计数最低的簇，其计数和修复记录一并丢失；被淘汰的签名再出现会从 1 开始、不再有修复标记。记住的记录哈希只保留最近 4096 个，更早的重复上传会被再次计数。

## 5. 上传与收集服务

客户端：`break_crash_upload_http` 向 `<base_url>/crash` POST，`Content-Type: application/x-break-crash`，只有 HTTP 200 算成功；其余一切（连接或 TLS 失败、超时、4xx/5xx、重定向、异常成帧、超过 256 字节的应答）都返回 false，由 spool 的重试规则处理（第 5 次失败丢弃）。记录大于 64 KiB、基础地址以 `/` 结尾、`https` 没有 CA 文件、明文 `http` 指向非回环地址，都在连接之前被拒绝。它是单独的库，`break_crash` 不依赖它。

服务端 `break_crash_server`：

| 状态 | 条件 |
|---|---|
| 200 | 已计数（`ok count=N regression=0/1`）或已计数过（`duplicate`） |
| 400 | 头格式错误、`chunked`、重复的 `Content-Length`/`Content-Type`、空体、不是一条完整规范记录、信号编号越界 |
| 404 / 405 | 路径不是 `/crash` / 方法不是 POST |
| 409 | 记录的构建没有登记 |
| 411 / 413 / 415 | 无长度 / 体超过 64 KiB / 内容类型不对 |
| 500 | 统计文件无法加锁、读取或写入（不会被覆盖或置空） |

每个请求（握手加请求加应答）总时限 10 秒。拒绝应答前会先读掉客户端声明的请求体（上限 1 MiB）——早先版本在读完之前就应答，客户端写入被连接复位打断，看到的是 TLS 错误而不是 413。其余没有特殊处理：串行服务，没有认证，没有按客户端的限速，没有保存记录本身，没有保留策略。符号缺失的记录仍然计数，帧按模块加偏移聚类。

运维工具：`report`、`register-build <id>`、`mark-fixed <签名或至少 8 位前缀> <id>`。前缀不唯一或不存在时拒绝。

## 6. 测试

| 测试 | 例数 | 内容 |
|---|---|---|
| `test_break_crash_symbolize` | 45 | 对 `nm` 逐函数核对；x86-64/AArch64 ELF 机器类型；损坏 ELF 逐字段；剥离的 so；真实崩溃（非 PIE 与 PIE）的完整调用链；手工构造记录的链走查、伪造链、32 帧上限、窗口边界；符号根之外的名字；迟到的符号文件；Mach-O（20 项，见下） |
| `test_break_crash_cluster` | 26 | 签名稳定性与敏感性；计数、重复、未登记构建；回归的全部时序；规范文本往返、每个前缀与单字节改动、结构性谎言；写入中途失败（`RLIMIT_FSIZE` 子进程）旧文件不变；界限与淘汰；恶意符号名；前缀解析；进程间锁 |
| `test_break_crash_upload_http` | 8 | 伪造收集端：成功、各种状态、成帧错误、无应答、本地拒绝不接触在线服务、spool 重试 |
| `test_break_crash_e2e` | 11 个场景 | 见下 |
| `test_break_crash_server_target_contract` | 1 | 归档导出清单、禁链、`break_crash` 无网络符号、TLS 规则留在源码里 |

端到端场景：真实 SIGSEGV 的记录被符号化（第一帧 `leaf`）；第二个进程的同一缺陷并入同一个簇；重复上传不重复计数；九种被拒请求各得正确状态且统计不变；修复后旧构建崩溃计数但不回归、更晚构建崩溃标记回归、再标记清除回归；报告工具的各种拒绝；应答丢失（`--drop-response`）后记录留在 pending、重试只计一次；服务端不在线、没有 CA 文件时记录留在 pending；被拒绝的记录重试 5 次后丢弃、统计不变；损坏的统计文件答 500 且不被覆盖（报告工具同样拒绝改写）；不可写的统计文件答 500 且文件不变，之后重试成功计一次（以 root 运行时跳过此场景）。

Mach-O 用例在测试里逐字节构造镜像，不需要 Apple SDK：dylib 与 `__TEXT` 在 0x100000000 的可执行文件得到相同的相对地址；同地址别名、局部符号、`__stubs`；undefined、abs、stab（含低位像 `N_SECT` 的 `N_BNSYM`）、数据 section、越界 section 号、空名、越界字符串下标都跳过；UUID；arm64 接受，错误 CPU、文件类型、32 位、大端、fat 拒绝；每一个截断长度拒绝；15 项结构破坏逐一拒绝；3000 轮随机破坏 load command 不崩溃；`ncmds` 恰为 4096 接受、4097 拒绝；未知 load command 也必须 8 字节对齐；低于 `__TEXT` 的代码符号跳过；符号库与 `break_crash_symbolize_address` 经记录解析；分派器两种格式都能打开、各自的读取器拒绝对方格式。另有一项真实工具链用例：本机有 `clang`、`ld64.lld`、`llvm-nm` 时，分别生成 x86_64 dylib、arm64 dylib、x86_64 可执行文件，逐函数与 `llvm-nm` 核对；缺工具时打印 skipped 后返回。

通用文件用例（6 项）：手工拼成的 arm64 + x86_64 通用文件（arm64 在前，两个 slice 靠 UUID 末字节区分），两种 magic 下取任一 CPU，默认取 x86_64，符号库经通用文件解析；单架构文件请求另一个 CPU 返回 NULL；只含 arm64 的通用文件没有默认 slice；条目数 0、33、52、`0xffffffff` 拒绝，恰好 32 个接受；slice 越界、伸进条目表、互相重叠、CPU 重复、条目与 slice 的 CPU 不符、64 位条目偏移高位、长度越界都拒绝；slice 短一个字节时该 slice 拒绝、另一个照常；每一个截断长度拒绝；请求 CPU 0 或不支持的 CPU 返回 NULL。真实工具链：`llvm-lipo -create` 合成 x86_64 + arm64 dylib，按架构与 `llvm-nm --arch` 逐函数核对，并核对两个 slice 的 UUID。

**变异检查**（去掉规则，对应测试必须变红；每次变异前先确认构建没有报错，避免旧二进制造成假通过）：
- 符号读取：包含性检查、区段范围、文件大小上限、符号名偏移、`entsize`、ELF 类别、`.dynsym` 回退（7 项，全部变红；其中区段范围与符号名偏移两项的变异表现为段错误）。
- 帧恢复：严格增长检查、`ret==0`、`pc-1`、ET_EXEC 换算、窗口剩余长度 `len - off < 8`、构建 id 长度/字符集/路径分隔符/`.`/`..` 校验（均变红）。**有两处不是普通构建里的回归测试**：窗口读边界的 `off > len` 前置检查，去掉后普通构建仍全绿（越界读落在其他已映射内存里），只有 ASan 树报堆越界读；`addr < base` 与它互为冗余（去掉后 `off` 回绕为巨大值，仍被 `off > len` 拦下），没有任何测试能单独区分。这两条应当被视为纵深防御，而不是被测试钉住的规则。早先的 `rbp < rsp` 检查同样冗余，已经删除，用例 `0x7feffff0` 等由 `read_word` 覆盖。
- 聚类：19 项，其中 16 项变红、3 项为等价变异（见下）（签名取两帧、丢模块、去重、回归比较、淘汰方向、规范复查、符号名清洗、`mark_fixed` 清标记、`flock`、记住哈希的淘汰方向、有序性检查、最后构建追踪、未登记构建、构建 id 校验、大写十六进制、…）+ 前缀解析 3 项。
- 适配器 7 项（状态、基础地址、大小上限、内容类型、空记录、传输错误、上限的差一）；服务端与工具 11 项（统计被覆盖、未登记构建、保存失败、内容类型、大小上限、顶部符号、路径、锁、信号编号、报告工具覆盖损坏文件、去重）。其中适配器的"忽略传输错误"在端到端里不变红（它另外会让状态检查失败，但端到端里服务端总是应答），由适配器单元测试抓到；服务端的"忽略保存失败"只被端到端的"不可写统计文件"场景抓到，所以以 root 运行时这一项没有保护。
- Mach-O 读取：29 项。首轮 7 项存活，补测试后 `ncmds` 上限、对齐、stab、`__TEXT` 下界被捕获。其余三项：去掉“剩余命令字节不足 8”的检查，普通构建仍全绿，只有 ASan 构建报堆越界读（与上面窗口读边界的情形相同，算纵深防御）；去掉 `n_sect` 上界检查是等价变异，section 表预先清零，超界的 section 不是代码 section；别名跳过条件是等价变异，去掉后别名之一大小为 0，但查找从后往前找到另一个同地址符号，结果不变。
- 通用文件：17 项。首轮 4 项存活，补“32 个接受、33 个拒绝”与“请求 CPU 0”两项后条目上限和 CPU 检查被捕获。去掉“条目表超出文件”的检查，普通构建全绿，ASan 构建报堆越界读，属纵深防御；去掉“条目数为 0”的检查是等价变异，0 个条目时找不到任何 slice，同样返回 NULL。
- 契约：向 `engine` 链接行加库、多导出一个函数、导出名带 `insecure`，三者均使契约测试变红。

**等价变异（分析，不是测试）**：聚类中三个变异在改动后测试仍全绿，逐一分析后确认是被其他检查覆盖的冗余防线，而不是漏测：计数溢出检查（回绕后规范复查会拒绝）、首次构建下标范围检查（"最后构建 ≥ 首次构建且 < 构建数"蕴含它）、`save` 忽略写失败（原子写入器写失败后进入粘性失败态，`commit` 本身返回 false）。这三条我没有用测试单独钉住。

**修复过程中暴露的问题**：（1）上文的 ET_EXEC 换算；（2）负缓存；（3）413 前未读请求体；（4）ASan+UBSan 树里端到端测试的崩溃子进程拿不到记录。**原因是 UBSan 的空指针检查**：它在 `break_crash` 处理器运行之前就报告并结束了进程。我最初把原因写成"处理器复制栈窗口时碰到 ASan 红区"，那是没验证的猜测，后来用变体构建和探针证伪（见下）。只要故障点那一个函数不带 UBSan 检查就足够，记录正常产生；当前代码仍把整条故障路径都标为不带插桩，这比必要的多，但无害。探针：在带栈数组的 ASan 插桩帧里 `raise(SIGSEGV)`，ASan 单独与 ASan+UBSan 两种构建下处理器都写出了记录，没有红区报告。**因此没有证据表明 ASan 构建的应用里栈窗口会被红区拦下**。

### Linux arm64 QEMU 运行（2026-11-20）

CI 的 `lane-cross-aarch64-linux` 配置 `CMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/`。崩溃切片最初构建九个目标后统一执行下面的命令；当前选择与外层守护（2026-11-20 起为 `timeout 600`）以 `docs/Build_Guide.md` 1.5 节为准：

```sh
BREAK_TEST_NM=aarch64-linux-gnu-nm \
BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^test_break_crash'
```

选择恰好七项：六个 `crash` 标签测试（`test_break_crash`、其目标契约、符号化、聚类、HTTP 上传、e2e）以及 `test_break_crash_server_target_contract`。可执行目标由 CMake 自动加 QEMU；宿主 CMake 驱动的契约显式接收 `CMAKE_NM`，现场链接检查与 e2e 的 server/report/client 接收同一目标运行器。符号化测试内部新编译的崩溃 fixture 仍由 `BREAK_TEST_RUNNER` 显式启动。宿主工具和 `nm` 本身不由 QEMU 执行，也不修改宿主 binfmt；e2e 的 shell 启动逐个转义运行器参数，保留含空格或单引号的路径。

37 项崩溃用例覆盖记录、有界 spool、真实 SIGSEGV/SIGABRT、context blob、恢复上传和脱敏；45 项符号化覆盖真实 AArch64 ELF、非 PIE/PIE 调用链与既有 Mach-O 规则；26 项聚类覆盖签名、去重、回归、持久化与进程锁；8 项上传覆盖真实 loopback TLS、状态/成帧错误和重试。两项归档契约保留精确导出清单及禁链检查，e2e 保留真实崩溃到 TLS 收集、聚类、回归报告和拒绝/重试的 11 个场景。`--no-tests=error` 防止空选择，失败与超时不被重试或屏蔽。

AArch64 GCC 可对叶子函数省略 `x29` 帧，即使命令带 `-fno-omit-frame-pointer`。符号化 fixture 在故障前调用不可内联的 `prepare_leaf`，确保故障函数建立帧；没有降低调用链断言。没有帧指针且未记录 `x30` 时仍可能得到短链，这是既有限制，不能据此声称支持 DWARF CFI 或无帧指针展开。

e2e 的不可写统计文件场景依赖权限：root 容器明确报告跳过，非 root runner 实际执行。精简 QEMU 环境缺少 clang/lld/llvm 工具时，两个真实 LLVM Mach-O 子检查按既有条件 skipped，合成 Mach-O 用例照常执行。这属于七项崩溃测试的模拟 Linux arm64 证据，不是全量 arm64 `ctest`、GPU 或物理设备证据。

## 7. 没有做的

- minidump / PE 格式、Windows SEH/VEH（`_WIN32` 仍是编译期 stub）；Windows 与 macOS lane 未运行（新库只在 `UNIX AND NOT APPLE` 下构建，服务与工具只在 POSIX 下构建）。Mach-O 只读符号表。2026-11-20：AAPCS64 与 x86-64 帧记录同为 `[fp]`/`[fp+8]` 布局，信号处理器在 Linux arm64 下读 `pc`/`sp`/`x29`。后续 CI 统一执行七项崩溃相关 CTest，包括真实 AArch64 ELF、聚类、TLS 上传、两项契约与 e2e；物理设备验证仍未完成，没有验证 macOS 客户端生成的真实崩溃记录。
- DWARF CFI 展开；内联帧；无帧指针代码的可靠调用栈。
- 生产服务：认证上传者、按客户端限速、记录本身的存储与保留、符号库管理与发布流程、统计的数据库、仪表板、告警。
- GPU/RHI/网络/输入摘要的自动采集（仍由应用经 context-blob 接缝接入）。
- 引擎、演示、编辑器均未链接上传适配器；没有哪个发布二进制会真的上传崩溃记录。
- 本机没有验证 IPv6 回环、真实公网证书链、长时间运行与高并发。服务一次只处理一个连接。

## 8. core_app context-blob 接入的符号化边界（2026-11-22）

`core_app --crash-context DIR` 已把应用摘要接入客户端 context-blob，但没有改变本节前述记录格式、ELF/Mach-O 读取、帧恢复或聚类算法。blob 仍由 `[rhi]`、`[net]`、`[input]` 三个 section 组成，严格 allowlist 为：

```text
[rhi]
backend=<record|auto|vulkan|opengl 或实际后端>
gpu=<pending|none|经过 BreakCrashSummary 清理的设备名>
[net]
live=<true|false>
seen=<u64>
dropped=<u64>
[input]
tick=<u32>
keys=<u32>
pads=<u32>
touches=<u32>
gestures=<u32>
touch_status=<u32>
haptic_status=<u32>
```

这些字段只提供本地诊断上下文，不参与 PC/bias 换算、RBP 链恢复或签名计算，也不能被解释为新的符号表、minidump 或 DWARF CFI 能力。原始按键码、文本、坐标、输入设备名、触摸来源 ID、网络地址、连接 key、session id、PSK 和数据包内容仍不在允许范围内。

运行时默认 OFF；未传选项时不安装处理器、不建 spool、不发布。启用后的顺序是 start → `gpu=pending` 的初始快照 → `runtime_running` 后 tick 0 → 每个完整 tick 末尾发布 → stop 清 blob 并卸载。详细隐私、CLI 和生命周期契约见 `crash_reporting.md` §11。

当前真实 full-process 证据仅为原生 Linux SIGABRT：第 2 帧 abort 后验证 `tick=1 backend=record gpu=none keys=1` 及所有规定零字段；`runtime_running` 前 abort 验证 `gpu=pending tick=0 keys=0`；正常成功和运行时失败均验证 stop 与零 pending 记录。Windows 仍是 start=false stub，非 Linux full-process 不具备原生 preload 时返回 77；不得从格式化工件、Mach-O 符号读取或服务端测试推断 Windows/macOS 客户端捕获成功。

`core_app` 不链接 `break_crash_upload_http`，本子项目没有上传接线，也没有新增生产收集服务。当前已执行为 focused 7/7、diagnostics 7/7，以及 compat/NM/config 3 pass + 3 expected skip；完整图形、平台、sanitizer/fuzz 和远端 CI 验收仍待后续执行，没有可提前登记的 run-id。

### 8.1 最终验收与捕获边界补充（2026-11-23）

本节追加于前述“完整验证待执行”的时点记录之后，不改变记录格式或符号化算法。

- `acc3c5d2` 已完成 Vulkan 470/470、OpenGL 468/468（各 4 项条件 skip）、ASan+UBSan 非图形 443/443（4 项条件 skip）、fuzz 14/14、TSan 相关 8/8 和两种根契约各 1/1。rebase 到 `33cc4be4` 后的 `321cf4f9` 已完成 Vulkan/OpenGL 资源交集各 3/3、core_app focused 7/7、ASan 资源/崩溃交集 7/7 + fuzz 14/14、TSan 资源与并发交集 9/9 及两种根契约各 1/1；追加文档冲突保留双方内容且无冲突标记。
- ASan 真实 full-process 使用 `libasan.so.8` 已通过；`libtsan.so.2` 是真实 TSan runtime。ASCII 或空 ASan/TSan runtime 均在创建工作目录/进程前返回 77，UBSan 不需要额外 runtime。sigaction 懒解析与 helper 去插桩只修复测试基础设施，`core_app` 保持插桩。TSan full-process 在本机 Fedora GCC 16/glibc 2.44 仍因 Lua longjmp CHECK 退出 66，等待 Ubuntu CI，未记为 skip 或通过。
- macOS ARM64 在中间 `0ddd` 的全量为 Metal 435/435、MoltenVK 438/438，各 5 项条件 skip（含 crash_context）；MoltenVK 是在修正 Homebrew 顶层 include 符号链接导致的 staging 失败后取得，不能抹成首轮全绿。最终两套资源/diagnostics/lifecycle 交集各 7/7（crash_context 明确 skip）、graphics/gpu 各 6/6。Mach-O 符号读取和这些测试仍不证明 Windows/macOS 客户端捕获。
- Windows 实机、主 CI、windows-d3d12、QUIC（本次由 `engine/CMakeLists.txt` 触发）和 Proton 仍待后续结果，无 run-id 或成功预记；Windows install=false stub 不变。

#### Windows 实机补充（`321cf4f9`）

Windows 实机待办现已执行：Windows Clang 成功构建 D3D12 树，完整非图形 CTest 为 **425 项、4 失败、5 项条件 skip**，不是全套通过。diagnostics **7/7**（POSIX 用例只是占位，install=false stub 不是捕获证据）、runtime **65/65**；crash_build OFF、nested 契约通过，target、crash_context 按平台 skip；VFS、async loader、Runtime IO 分别通过。

`test_locked_dependencies` 在补齐与 CI 一致的 `ENGINE_LOCKED_DEPS_ALLOW_ABSENT=1` 后通过，首轮缺环境失败保留。平台 runtime 为 **20/26**，远程桌面窗口样式、最大化、全屏恢复失败；D3D12 UAV 交换链创建返回 `0x887a0022`，WARP 亦失败，warp_runtime 条件 skip，不声称 GPU 或交互桌面通过。

`test_scene_serial` 为 **121/122**，失败点是 `failed_load_keeps_previous_scene` 的 `scene_load_binary(wd,&dst,pa)`。scene 实现和测试从 `0ddd`、rebase base 到当前均未变化，因此不是本分支改动引入；根因未关闭，列为独立既有/平台问题，不声称环境原因已证明，待 Windows CI 交叉核验。

主 CI、windows-d3d12、QUIC（`engine/CMakeLists.txt` 变更会触发）和 Proton 仍待，不预写 run-id 或成功。Windows/macOS 客户端捕获仍不能由格式化、符号读取或占位测试推断。

#### 远端验收收据（`7fdcdfe318f43ce4f8620f0e455be795bb66e87b`）

[主 CI 45101195431](https://github.com/konyka/break/actions/runs/45101195431) 共 27 个矩阵作业，24 success、3 conditional skipped、0 failure；arm64 job `137452184436` 的 QEMU 选择套件 276/276，含 VFS、async loader、Runtime IO、core_app runtime。Ubuntu 24.04 TSan job `137452533153` 的 Configure/Build/Test (headless suite) 全成功；由于没有逐项 crash-context/BCR 日志，只记录 TSan headless suite 通过，不声称独立 SIGABRT/BCR artifact，Fedora longjmp 边界不变。

[windows-d3d12 45101195116](https://github.com/konyka/break/actions/runs/45101195116) 成功，Headless+contract、WARP floor、push-constant gate、Agility deployment、artifact upload 均成功；托管 Windows Clang 也成功。本机 scene_serial 单例失败仍未定位，本机全套不称通过。[QUIC 45101195104](https://github.com/konyka/break/actions/runs/45101195104) 虽 conclusion=success，但未配置 `SNOWFLAKE_READ_TOKEN`，UNAVAILABLE、No test ran，四个场景未执行，不能写成测试通过。[Proton 45102712864](https://github.com/konyka/break/actions/runs/45102712864) 成功，上游 run-id=`45101195116`、artifact ID `14785842612`，device/pipeline contract 均 77，仅兼容通道，不是 GPU 或原生 D3D12 通过。

本收据文档提交后的主 CI、windows-d3d12、Proton 仍须实际核验，不预写成功或 run-id；上述 run 均只属于 `7fdcdfe318f43ce4f8620f0e455be795bb66e87b`。
