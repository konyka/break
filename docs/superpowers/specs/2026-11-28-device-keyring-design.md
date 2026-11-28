# 设备密钥环：通用 `break_net` 服务端的逐设备密钥签发、轮换与吊销（设计）

状态：已实现（2026-11-28，提交 `a4210cc3..ba9966ee`，master）。原状态：设计，待评审。先设计后实现，实现采用 TDD。与本文的差异见各节「实现注记」。

## 1. 背景与问题

AUTH v2 认证（`docs/design/transport_security.md` §3/§4）只提供接缝：`BreakNetAuthKeyFn` 把 8 字节 `key_id` 映射为 32 字节 PSK，签发、存储、轮换、吊销都留给应用。

现状：

- **编辑器远程会话已有完整的密钥环**（`engine/apps/editor/editor_remote.{h,c}`，`docs/design/editor_remote.md`「Keyring」）：最多 8 个 key；`add_key`/`revoke_key`（吊销时关闭用该 key 认证的会话与传输）；`--remote-keyring-file` 加载；`reload_keyring` 按差异增删；按内容定时重读（`watch_keyring`），规避 mtime 一秒精度丢事件。
- **签发工具**：`break_keygen <keyring> <16 hex key id> <device psk file>`（`engine/tools/break_keygen.c`）生成随机 PSK，追加到密钥环文件（0600、`flock`、不跟随符号链接、单次 `write` 失败回滚），并把同一 PSK 写入设备文件。容量上限与编辑器一致（8 个 key、2047 字节）。
- **客户端**：`break_session_manager_set_client_key_id`（2026-11-28）让内置 CHALLENGE 助手发送指定的 `key_id`。
- **服务端限速**：`break_session_manager_set_identity_rate`（2026-11-28）按认证 `key_id` 共享额度。

缺口：密钥环只存在于编辑器内部（`EditorRemoteKey`、`g_editor_remote_auth` 都是 editor 私有静态），容量固定 8 个。core_app 或其他用 `break_session` 的服务端没有可复用的密钥环，只能自己写回调；8 个 key 也不够一个服务端的设备数。会话层也不知道某个 key 被吊销后哪些连接要关闭——编辑器靠自己的连接表记录 `auth_key_id` 做到这一点。

## 2. 目标与非目标

目标：

1. 一个与编辑器无关、`break_session` 服务端可直接使用的密钥环库 `break_keyring`：容量可配置（上限 4096），从文件加载，按差异重载，增删 key，常量时间比较，key 字节在移除与销毁时擦除。
2. 吊销立即生效：`break_session` 能关闭所有用某个 `key_id` 认证的会话。会话已保存认证 `key_id`（2026-11-28），只缺按 `key_id` 关闭的入口。
3. 文件格式与 `break_keygen` 保持一致，使现有签发工具无需改动即可为新库签发（容量上限除外，见 §5）。
4. 编辑器改为使用 `break_keyring`，删除重复实现，现有编辑器测试保持通过。

非目标（本设计不做）：

- 设备注册协议（设备用一次性码换取密钥）。签发后仍由运维把设备文件拷到设备上。
- 密钥托管、HSM、PSK 以外的凭证（证书、公钥认证）。
- 跨进程共享密钥环状态或分布式吊销列表；每个进程读自己的文件。
- 修改 AUTH v2 报文格式。

## 3. 方案比较

| 方案 | 做法 | 取舍 |
|---|---|---|
| A. 抽出通用密钥环库（推荐） | 把编辑器密钥环抽成 `engine/src/network/break_keyring.{h,c}`，加 `break_session_manager_close_key_id`；编辑器改用它 | 复用已有、经评审加固的逻辑与文件格式；一次消除重复；改动集中在 `break_net` 与编辑器两处 |
| B. 只在 core_app 里再写一份 | 复制编辑器逻辑到 core_app | 最快，但两份实现会分叉，修一处漏一处 |
| C. 先做注册协议 | 新增报文让设备在线领取密钥 | 能免去手工拷贝，但需要先有 A 的服务端密钥环，且协议设计（一次性码、信任根）本身需要单独决定 |

选 A。B 制造重复；C 依赖 A，可作为后续子项目。

## 4. 设计

### 4.1 `break_keyring`（`engine/src/network/break_keyring.{h,c}`）

纯 C11，不依赖 Snowflake，只依赖 `break_crypto`（擦除、可选的常量时间比较自写）。拥有者单线程使用，与 `break_session` 同在 Logic 线程。

```c
#define BREAK_KEYRING_MAX_KEYS 4096u

typedef struct BreakKeyring BreakKeyring;

/* capacity 1..BREAK_KEYRING_MAX_KEYS; NULL on a bad capacity or OOM. */
BreakKeyring *break_keyring_create(u32 capacity);
/* Wipes every key, then frees. NULL is a no-op. */
void break_keyring_destroy(BreakKeyring *ring);

/* Adds key_id -> psk. False for NULL, a duplicate key_id or a full ring. */
bool break_keyring_add(BreakKeyring *ring, const u8 key_id[8], const u8 psk[32]);
/* Removes and wipes a key. False when absent. */
bool break_keyring_remove(BreakKeyring *ring, const u8 key_id[8]);
u32 break_keyring_count(const BreakKeyring *ring);

/* BreakNetAuthKeyFn-compatible lookup: user is the ring. Compares key ids
 * in constant time over every slot (no early exit on a match). */
bool break_keyring_resolve(void *ring, const u8 key_id[8], u8 out_psk[32]);

/* Called once per key_id the reload removed or re-keyed, after it is gone
 * from lookups, so the caller can close that identity's sessions. key_id is
 * a copy that is wiped after the callback returns. */
typedef void (*BreakKeyringRevokedFn)(void *user, const u8 key_id[8]);

typedef enum BreakKeyringLoadResult {
    BREAK_KEYRING_LOAD_OK = 0,
    BREAK_KEYRING_LOAD_UNREADABLE,
    BREAK_KEYRING_LOAD_MALFORMED,   /* bad line, duplicate id, bad hex */
    BREAK_KEYRING_LOAD_TOO_LARGE,   /* more keys than capacity, or the file
                                     * is over BREAK_KEYRING_MAX_FILE_BYTES */
    BREAK_KEYRING_LOAD_EMPTY        /* no key line */
} BreakKeyringLoadResult;

/* Reads a keyring file and makes the ring equal to it: keys not listed, or
 * listed with a different secret, are removed (revoked is called for each);
 * new keys are added; unchanged keys stay. On any failure the ring is
 * unchanged and revoked is never called (all-or-nothing). */
BreakKeyringLoadResult break_keyring_load_file(BreakKeyring *ring, const char *path,
                                               BreakKeyringRevokedFn revoked,
                                               void *user);
/* Same as load_file on an in-memory buffer (len bytes, need not be NUL
 * terminated); used by callers that already read the file. */
BreakKeyringLoadResult break_keyring_load_text(BreakKeyring *ring, const char *text,
                                               usize len, BreakKeyringRevokedFn revoked,
                                               void *user);

/* Copies the i-th used key (0-based, insertion order) into id/psk; false
 * when i >= count. For callers that mirror the ring into their own store. */
bool break_keyring_key_at(const BreakKeyring *ring, u32 index, u8 key_id[8], u8 psk[32]);
```

实现注记（2026-11-28）：`break_keyring_load_text` 与 `break_keyring_key_at` 是实现时加入的，前者供已自行读取文件的调用方（编辑器）使用，后者供把环镜像到自有存储的调用方使用。头文件另定义 `BREAK_KEYRING_MAX_FILE_BYTES`（512 KiB）。吊销回调在 key 从查找中移除并擦除之后调用，收到 id 的本地副本（回调返回后擦除），而不是在擦除之前收到槽位内的 id；回调里可以 resolve，但不能 add/remove。`load_text` 对超过上限的 `len` 同样返回 `TOO_LARGE`；NULL 参数返回 `UNREADABLE`。`resolve` 用 `used` 掩码排除空槽，全零 id 不会命中空槽（`96e61d9d` 加测试钉住）。

文件格式（与 `break_keygen`、`--remote-keyring-file` 相同）：每行 `<16 hex key id> <64 hex psk>`，`#` 注释与空行跳过，`\r\n` 接受，key id 不重复。文件上限 `BREAK_KEYRING_MAX_FILE_BYTES` 定为 512 KiB（4096 行 × 每行 82 字节约 328 KiB，其余留给注释）。实现把整个文件读进堆上缓冲（不超过上限，超过则返回 `TOO_LARGE`），解析完毕后擦除并释放缓冲。

原子性：`load_file` 先把文件完整解析进临时表（堆上，大小为 capacity），全部合法才开始差异应用；差异应用本身不会失败（容量已在解析阶段检查），因此“失败不改变”成立。

存储：按插入顺序的定长数组 + 线性查找。4096 项 × 40 字节 = 160 KiB；每次认证一次线性常量时间扫描，4096 项约数十微秒，认证频率远低于消息频率，可接受。不引入哈希表（避免按 key_id 分支的时间侧信道）。

### 4.2 `break_session` 按 `key_id` 关闭会话

```c
/* Moves every authenticated session whose AUTH v2 key_id equals key_id to
 * CLOSING and returns how many. Logic thread. It does not close the
 * transport: the host must close the reactor connection of every CLOSING
 * session (as core_app's net_sync_sessions does). */
size_t break_session_manager_close_key_id(BreakSessionManager *manager,
                                          const u8 key_id[8]);
```

会话条目已有 `key_id`/`key_id_valid`。关闭后清除 `key_id_valid`，使同一会话不会被重复计数。函数只在 `BREAK_ENABLE_CRYPTO` 下声明。它只把会话置为 CLOSING，`break_session` 自身不调用 `break_net_reactor_close`；传输层关闭由宿主负责：宿主须为每个 CLOSING 会话关闭 reactor 连接（core_app 在 `core_app_net_transport.c` 的 `net_sync_sessions` → `net_close_slot` 中这样做；编辑器经自己的连接行关闭）。（2026-11-28 终审更正：原文写“沿用现有 CLOSING → reactor 关闭的路径”以及“未启用 BREAK_ENABLE_CRYPTO 时返回 0”，均不成立。）

### 4.3 组合用法（服务端）

```c
BreakKeyring *ring = break_keyring_create(1024u);
break_keyring_load_file(ring, path, NULL, NULL);          /* 启动 */
break_session_set_auth(break_keyring_resolve, ring);       /* 认证 */
/* 运行中：定时（按内容）重读 */
break_keyring_load_file(ring, path, on_revoked, manager);
/* on_revoked(manager, id) -> break_session_manager_close_key_id(manager, id) */
```

`close_key_id` 只把会话置为 CLOSING；宿主随后须为 CLOSING 会话关闭传输（如 core_app 的 `net_sync_sessions`），否则被吊销设备的连接仍然打开。环在 `break_session_set_auth(NULL, NULL)` 返回 true 之后才能销毁。定时重读的节奏由应用决定（编辑器沿用 `watch_keyring` 的 interval）。库不自带计时器与文件监视，避免引入平台依赖。

### 4.4 编辑器迁移

`editor_remote.c` 的 `EditorRemoteKey keys[8]`、`remote_auth_key`、`remote_keyring_file_read`、`reload_keyring` 中的差异逻辑改为调用 `break_keyring`。编辑器仍保留自己的连接表与 `auth_key_id`（它在会话层之外还要关闭传输行）。吊销回调调用现有的 `break_editor_remote_revoke_key`，它经编辑器自己的连接行关闭会话与传输，因此编辑器不调用 `break_session_manager_close_key_id`（2026-11-28 实现时更正；原文写的是两者同时调用）。外部 API（`add_key`/`revoke_key`/`key_count`/`reload_keyring`/`watch_keyring`）签名与行为不变；容量保持 8（编辑器场景不需要更多，且 `break_keygen` 的 2047 字节上限与之对应）。

实现注记（2026-11-28，`96a5cff5`）：启动解析与重载都先用编辑器自己的无缓冲读取函数（最多 2047 字节，第 2048 字节即拒绝整个文件）读入文本，再调用 `break_keyring_load_text`，而不是 `break_keyring_load_file`（后者接受到 512 KiB，会让重载接受启动时拒绝的文件）；编辑器的文件上限因此不变。重载时把当前 key 镜像进容量 8 的临时环，应用文件差异，吊销回调调用 `revoke_key`，再用 `key_at` 遍历并以 `add_key` 加入新 key。`EditorRemoteKey keys[8]` 与 `remote_auth_key` 保留未删。Snowflake 关闭的构建不链接 `break_net`，`editor` 与 `test_editor_shell` 直接编译 `break_keyring.c`。

### 4.5 `break_keygen`

增加可选参数 `--max-keys N`（默认 8，最大 4096）与对应的文件大小上限，使它能为通用服务端的密钥环签发。默认行为不变，现有 `test_break_keygen` 保持通过。

实现注记（2026-11-28，`ba9966ee`）：N 为严格十进制 1..4096，非法时在打开任何文件之前以退出码 2 退出；N 为 8 时环上限 2047 字节，其他 N 为 524287 字节（`BREAK_KEYRING_MAX_FILE_BYTES - 1`）。

## 5. 错误处理

- 文件不可读、格式错误、超容量、空文件：`load_file` 返回对应结果，环不变，不调用吊销回调。启动时由应用决定是否 fail-closed（建议：启动加载失败则拒绝启动认证）。
- 运行中重读失败：保留当前环（与编辑器现行为一致），应用记录一次告警。
- `add` 重复或满：返回 false，环不变。
- `resolve` 找不到：返回 false，`break_session` 按现有逻辑 fail-closed 关闭连接。
- 所有 key 字节在 `remove`、差异替换、`destroy`、解析缓冲释放前经 volatile 写擦除（沿用 `break_session_wipe` 的做法）。

## 6. 测试

`test_break_keyring`（新，纯库，不需 Snowflake）：

- add/remove/count、重复与满的拒绝、容量边界（1、4096、0 与 4097 拒绝）。
- `resolve`：命中返回正确 PSK、未命中返回 false 且不写出参。
- `load_file`：合法文件（含注释、空行、CRLF）；每种格式错误各一例（长度、分隔符、非十六进制、重复 id）；超容量；空文件；不可读路径。失败时环不变且回调未被调用。
- 差异重载：删除的 key 与换了 PSK 的 key 各触发一次回调、新 key 加入、未变 key 保持；回调在 key 从环中移除之后运行，收到 id 的副本。
- ASan 下确认无越界与泄漏。

`test_break_session`（扩展，真实 loopback AUTH v2）：

- 两个连接分别用两个 key 认证，`close_key_id` 其中一个只关闭对应连接并返回 1；再次调用返回 0。
- 用 `break_keyring_resolve` 作为 auth 回调的端到端：重载文件移除一个 key 后，该 key 的新认证失败、已有会话被关闭、另一个 key 的会话不受影响。

编辑器：现有 `test_editor_*` 中密钥环相关用例（`remote_tls_keyring_add_and_revoke`、`remote_tls_keyring_reload_revokes_removed_keys`、`remote_tls_cli_keyring_file_installs_all_keys` 等）不改动并保持通过，作为迁移的回归保护。

`test_break_keygen`：新增 `--max-keys` 的上限与越界用例，默认行为用例不变。

每处新逻辑配定向变异，确认测试会判红。常量时间比较无法从功能结果上观察，不作为功能测试项，由代码审查确认扫描遍历全部槽位且无早退。

## 7. 假设（本设计未经用户逐项确认的决定）

1. 范围选「通用 `break_net` 服务端密钥环」，不做设备注册协议（注册协议依赖本项，可作为后续子项目）。
2. 继续使用现有文本文件格式，不引入数据库或二进制格式。
3. 容量上限 4096，与 `break_identity_rate` 一致；编辑器保持 8。
4. 库不自带文件监视与计时器；定时重读由应用驱动。
5. 吊销通过「重载后文件中不再有该 key」或显式 `remove` 表达，不单独维护吊销列表文件。
6. 不处理多进程共享：每个服务端进程独立读取自己的密钥环文件。

## 8. 交付边界

完成后可声明：通用服务端可从文件加载逐设备 PSK、运行中按文件差异轮换与吊销、吊销立即关闭该身份的会话，编辑器使用同一实现。仍不可声明：设备在线注册、密钥托管、跨进程/分布式吊销、Windows 上的文件权限保证（与 `break_keygen` 相同，仅 POSIX）。
