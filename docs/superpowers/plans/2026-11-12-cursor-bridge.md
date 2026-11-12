# cursor-bridge 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 构建 cursor-bridge——一个常驻本机的 Node.js 代理，把 Cursor 账号的模型集合以 OpenAI 兼容接口暴露给 Kimi Code CLI，支持浏览器登录、token 自动刷新、模型列表自动同步。

**Architecture:** 五个内部组件：token-store（读 Cursor 本地加密 token + 自有缓存）、auth（Cursor device-login 流程 + /oauth/token 刷新）、protobuf 运行时 + cursor-ai-client（Connect-RPC `aiserver.v1.AiService`，手工 protobuf 编解码）、server（`/v1/models`、`/v1/chat/completions`、`/api.json`）、cli（start/login/status）。OpenAI 请求翻译为 Cursor RPC，SSE 流式回传。

**Tech Stack:** Node.js ≥ 22（开发机为 v24，内置 `node:sqlite`、全局 `fetch`）、TypeScript strict 模式、vitest。除 devDependencies（typescript/tsx/vitest/@types/node）外零依赖，不用任何原生模块。

## Global Constraints

- 运行时零 npm 依赖；不引入原生/编译型依赖（node-gyp 一律禁止）。
- 服务只绑 `127.0.0.1`，默认端口 `42137`。
- Cursor 后端：`backendUrl = https://api2.cursor.sh`,`websiteUrl = https://cursor.com`,`clientId = KbZUR41cY7W6zRSdpSUJ7I7mLYBKOCmB`（从本机 Cursor 安装 `D:\Programs\Cursor` 的 bundle 中提取，已确认）。
- Cursor token 存储：`%APPDATA%\Cursor\User\globalStorage\state.vscdb` 的 `ItemTable` 表，key 为 `cursorAuth/accessToken` / `cursorAuth/refreshToken`;value 格式为 `cursor-safe-storage:v1:` + base64(DPAPI 密文)（Electron safeStorage，Windows 走 DPAPI CurrentUser）。
- 所有测试用 vitest；网络访问一律 mock `fetch`，禁止测试打真实外网。
- 项目根目录 `E:\work\cursor-bridge`，独立 git 仓库。
- 日志中禁止输出完整 token（最多前 8 字符 + 长度）。

## 已确认协议事实（探查结论，任务 1 负责补充剩余细节并固化到 docs/protocol.md）

1. 设备登录：浏览器打开 `https://cursor.com/loginDeepControl?challenge=<b64url(sha256(verifier))>&uuid=<uuid>&mode=<MODE>&supportsSelectedTeamLogin=true`;轮询 `GET https://api2.cursor.sh/auth/poll?uuid=..&verifier=..`,404 = 未就绪，200 JSON 含 `{authId, accessToken, refreshToken, selectedTeamId?}`。
2. 刷新：`POST https://api2.cursor.sh/oauth/token`,body `{"grant_type":"refresh_token","client_id","refresh_token"}`；响应 `{access_token,...}` 或 `{shouldLogout:true}`。
3. AI 对话：Connect-RPC server-streaming 方法 `aiserver.v1.AiService/StreamChatTryReallyHard`；模型列表：同服务 unary 方法 `AvailableModels`。protobuf 消息描述全部内嵌在 `D:\Programs\Cursor\resources\app\out\vs\workbench\workbench.desktop.main.js` 的 `S.makeMessageType("aiserver.v1.X",()=>[{no,name,kind,T},...])` 表中，可按正则整体提取。
4. 请求头 `x-cursor-checksum`:`base64(6 字节 big-endian floor(Date.now()/1e6)) + machineId`，若有 macMachineId 再拼 `/<macMachineId>`;machineId = state.vscdb `ItemTable` 的 `storage.serviceMachineId`。另有 `x-cursor-client-type` 等头（细节任务 1 提取）。
5. Kimi Code registry(api.json）格式已从本机 `kimi.exe` 内置解析器提取确认：
   - 顶层：providerId → `{ id, name, api: string(base_url), type, models: {...}, env?: string[] }`
   - `type` 枚举含 `openai`（本计划用）；`api` 是字符串 URL。
   - 模型：key → `{ id, name?, limit?: {context?, output?}, tool_call?: bool, reasoning?: bool, modalities?: {input?: string[], output?: string[]} }`。

---

### Task 1: 协议细节探查(spike)，固化 docs/protocol.md 与 fixtures

**Files:**
- Create: `docs/protocol.md`
- Create: `tests/fixtures/aiserver-messages.json`
- Create: `tests/fixtures/poll-response.json`

这是全计划唯一允许"先查后写"的任务。所有探查命令只读；唯一例外是 DPAPI 试解密，只打印 token 前 6 字符验证格式。

- [ ] **Step 1: 提取登录 mode 值与 checksum 辅助函数**

运行（在 `E:\work\cursor-bridge` 外任意目录，用 python):

```python
import re
src = open(r"D:\Programs\Cursor\resources\app\out\vs\workbench\workbench.desktop.main.js", encoding="utf-8", errors="replace").read()
# mode 变量：loginDeepControl URL 模板里的 mode=${Y}，回溯 Y 的赋值
m = re.search(r"mode=\$\{[A-Za-z0-9_$]+\}", src); print("MODE:", m.group(0))
i = src.find("cursor-safe-storage")  # 定位登录 URL 生成段附近
seg = src[i:i+200000]
for name in ["Y"]:
    mm = re.search(r"[,\s]"+name+r"=[\"'][a-zA-Z0-9_\-]+[\"']", seg)
    print("Y =", mm.group(0) if mm else "?")
# checksum 哈希与编码函数：x-cursor-checksum 前 4000 字符内找 DD_ 与 base64 定义
j = src.find('e.header.set("x-cursor-checksum"')
seg2 = src[max(0,j-6000):j]
for mm in re.finditer(r"[,\s;](DD_|i)=[^;]{1,120}", seg2):
    print(mm.group(0)[:140])
# 传输层 baseUrl：B5h=Map([[host, a8n]])，找 a8n 对象
for mm in re.finditer(r"[,\s]a8n=[a-zA-Z0-9_$]+", src):
    print("a8n alias:", mm.group(0))
    seg3 = src[mm.start():mm.start()+500]
    print(seg3.replace("\n"," ")[:400])
```

预期：得到 `mode` 字面值、`DD_`(sha256 hex 或 base64 一步）、编码函数 `i`、传输 `baseUrl`。把原始片段贴进 `docs/protocol.md` 的"待确认→已确认"小节。

- [ ] **Step 2: 提取全部 aiserver.v1 消息描述表**

```python
import re, json
src = open(r"D:\Programs\Cursor\resources\app\out\vs\workbench\workbench.desktop.main.js", encoding="utf-8", errors="replace").read()
pat = re.compile(r'[A-Za-z0-9_$]+=S\.makeMessageType\("aiserver\.v1\.([A-Za-z0-9_]+)",\(\)=>\[(.*?)\]\)')
out = {}
for m in pat.finditer(src):
    name, body = m.group(1), m.group(2)
    fields = re.findall(r'\{no:(\d+),name:"([A-Za-z0-9_]+)",kind:"([a-z]+)"(?:,T:([A-Za-z0-9_$]+))?(?:,repeated:!0)?\}', body)
    out[name] = [{"no": int(n), "name": fn, "kind": k, "T": t, "repeated": (f"no:{n},name:\"{fn}\"" in body and "repeated:!0" in body)} for n, fn, k, t in [ (a,b,c,d) for a,b,c,d in fields ]]
json.dump(out, open(r"E:\work\cursor-bridge\tests\fixtures\aiserver-messages.json","w"), indent=1)
print("messages:", len(out), "->", sorted(out)[:10])
```

预期提取 100+ 条消息描述。重点核对两条:`StreamChatTryReallyHard` 的请求类型（服务定义中 `I:Mit`，找到 `Mit=S.makeMessageType("aiserver.v1.<ReqName>",...)` 的真实消息名）与 `AvailableModels` 的 `I:$Yi` / `O:__d` 指向的消息。把这两个消息（及它们嵌套引用的消息，如 conversation/message 相关）的完整字段表写进 `docs/protocol.md`；全量 JSON 存 fixtures。

- [ ] **Step 3: 试解密本机 accessToken 验证 DPAPI 假设（只读，不泄露）**

```bash
python - <<'EOF'
import sqlite3, subprocess, base64
con = sqlite3.connect('file:C:/Users/Administrator/AppData/Roaming/Cursor/User/globalStorage/state.vscdb?mode=ro', uri=True)
v = con.execute("select value from ItemTable where key='cursorAuth/accessToken'").fetchone()[0]
b64 = v.split(':', 2)[2]
ps = f"""
Add-Type -AssemblyName System.Security
$bytes = [Convert]::FromBase64String('{b64}')
$plain = [Security.Cryptography.ProtectedData]::Unprotect($bytes, $null, 'CurrentUser')
[Console]::OutputEncoding = [Text.Encoding]::UTF8
[Console]::Out.Write([Text.Encoding]::UTF8.GetString($plain))
"""
r = subprocess.run(['powershell','-NoProfile','-NonInteractive','-Command',ps], capture_output=True)
tok = r.stdout.decode('utf-8','replace')
print('decrypt ok:', r.returncode==0 and len(tok)>100, 'len:', len(tok), 'head:', tok[:6])
EOF
```

预期：`decrypt ok: True len: ~600+ head: eyJ`(JWT)。若失败，回到 workbench 代码确认 safeStorage 后端（`cursor.storage.authTokenEncryptionAtRest=true` 已确认走 DPAPI)，修正 protocol.md。

- [ ] **Step 4: 固化 poll 响应样例 fixture**

`tests/fixtures/poll-response.json`:

```json
{
  "authId": "auth0|example",
  "accessToken": "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.example",
  "refreshToken": "example-refresh-token",
  "selectedTeamId": 0
}
```

- [ ] **Step 5: 提交**

```bash
git add docs/protocol.md tests/fixtures/
git commit -m "spike: pin down cursor backend protocol details"
```

---

### Task 2: 项目脚手架

**Files:**
- Create: `package.json`、`tsconfig.json`、`vitest.config.ts`、`.gitignore`、`src/`（空占位后删）

**Interfaces:**
- Produces: npm scripts(`build`/`test`/`start`/`login`/`status`)；后续任务全部在此结构上开发。

- [ ] **Step 1: 初始化并安装 devDependencies**

```bash
mkdir -p E:\work\cursor-bridge && cd /e/work/cursor-bridge
npm init -y
npm i -D typescript tsx vitest @types/node
npx tsc --init
```

`package.json` 改为：

```json
{
  "name": "cursor-bridge",
  "version": "0.1.0",
  "private": true,
  "type": "module",
  "scripts": {
    "start": "tsx src/cli.ts start",
    "login": "tsx src/cli.ts login",
    "status": "tsx src/cli.ts status",
    "test": "vitest run",
    "build": "tsc -p tsconfig.json"
  }
}
```

`.gitignore`:`node_modules/`、`dist/`、`*.log`。

`tsconfig.json` 关键项：`"strict": true`, `"target": "ES2022"`, `"module": "NodeNext"`, `"moduleResolution": "NodeNext"`, `"outDir": "dist"`, `"types": ["node"]`。

- [ ] **Step 2: 冒烟测试**

`tests/smoke.test.ts`:

```ts
import { test, expect } from "vitest";
test("env", () => {
  expect(typeof fetch).toBe("function");
  expect(process.versions.node.split(".")[0]).toBe("24");
});
```

Run: `npm test` → Expected: PASS(1 passed)。

- [ ] **Step 3: 提交**

```bash
git add -A && git commit -m "chore: scaffold cursor-bridge project"
```

---

### Task 3: token-store——读取 Cursor 本地 token 并 DPAPI 解密

**Files:**
- Create: `src/tokens/types.ts`
- Create: `src/tokens/decrypt.ts`
- Create: `src/tokens/cursor-store.ts`
- Create: `src/tokens/cache.ts`
- Test: `tests/tokens.test.ts`

**Interfaces:**
- Produces:
  - `interface CursorTokens { accessToken: string; refreshToken: string }`(types.ts)
  - `decryptCursorSafeValue(value: string): Promise<string>`(decrypt.ts)——去掉 `cursor-safe-storage:v1:` 前缀，base64 解码，PowerShell DPAPI 解密，返回 UTF-8 字符串。
  - `readCursorTokens(dbPath: string): Promise<CursorTokens | null>`(cursor-store.ts)——用 `node:sqlite` 只读打开，取两个 key，解密；任何一步失败返回 null（不 throw)。
  - `class CredentialCache { constructor(path: string); load(): CursorTokens | null; save(t: CursorTokens): void }`(cache.ts)——原子写（tmp + rename),JSON 格式 `{ version: 1, ...CursorTokens }`。

- [ ] **Step 1: 写失败测试**

`tests/tokens.test.ts` 要点：

```ts
import { test, expect, beforeAll } from "vitest";
import { DatabaseSync } from "node:sqlite";
import { mkdtempSync, readFileSync, existsSync } from "node:fs";
import { join } from "node:path";
import { tmpdir } from "node:os";
import { readCursorTokens } from "../src/tokens/cursor-store.js";
import { CredentialCache } from "../src/tokens/cache.js";

// DPAPI 加密方向不可在测试里做，decrypt 用依赖注入绕过：见 decrypt.ts 的 _setRunnerForTests

beforeAll(() => {
  // fixture db: 两条 ItemTable 记录，value 为 "cursor-safe-storage:v1:<b64>"
  dir = mkdtempSync(join(tmpdir(), "cb-"));
  dbPath = join(dir, "state.vscdb");
  const db = new DatabaseSync(dbPath);
  db.exec("create table ItemTable(key text primary key, value text)");
  db.prepare("insert into ItemTable values(?,?)").run("cursorAuth/accessToken", "cursor-safe-storage:v1:QUJD");
  db.prepare("insert into ItemTable values(?,?)").run("cursorAuth/refreshToken", "cursor-safe-storage:v1:REVG");
  db.close();
});

test("readCursorTokens decrypts both keys", async () => {
  const t = await readCursorTokens(dbPath);
  expect(t).toEqual({ accessToken: "tok-A", refreshToken: "tok-B" });
});

test("readCursorTokens returns null on missing db", async () => {
  expect(await readCursorTokens(join(dir, "nope.db"))).toBeNull();
});

test("cache round-trips atomically", () => {
  const p = join(dir, "cred.json");
  const c = new CredentialCache(p);
  expect(c.load()).toBeNull();
  c.save({ accessToken: "a", refreshToken: "b" });
  expect(c.load()).toEqual({ accessToken: "a", refreshToken: "b" });
  expect(JSON.parse(readFileSync(p, "utf8")).version).toBe(1);
});
```

Run: `npm test` → Expected: FAIL（模块不存在）。

- [ ] **Step 2: 实现**

`src/tokens/types.ts`:

```ts
export interface CursorTokens {
  accessToken: string;
  refreshToken: string;
}
```

`src/tokens/decrypt.ts`:

```ts
import { execFile } from "node:child_process";

const PREFIX = "cursor-safe-storage:v1:";
// 测试中替换为同步假实现；生产为 PowerShell DPAPI
let runner: (b64: string) => Promise<string> = powershellDpapi;

async function powershellDpapi(b64: string): Promise<string> {
  const script =
    "Add-Type -AssemblyName System.Security;" +
    "$p=[Convert]::FromBase64String($env:CB_B64);" +
    "$u=[Security.Cryptography.ProtectedData]::Unprotect($p,$null,'CurrentUser');" +
    "[Console]::OutputEncoding=[Text.Encoding]::UTF8;" +
    "[Console]::Out.Write([Text.Encoding]::UTF8.GetString($u))";
  return new Promise((resolve, reject) => {
    execFile("powershell", ["-NoProfile", "-NonInteractive", "-Command", script],
      { env: { ...process.env, CB_B64: b64 }, maxBuffer: 1 << 20, timeout: 15000 },
      (err, stdout) => (err ? reject(err) : resolve(stdout)));
  });
}

export function _setRunnerForTests(fn: typeof runner) { runner = fn; }

export async function decryptCursorSafeValue(value: string): Promise<string> {
  if (!value.startsWith(PREFIX)) throw new Error("not a cursor-safe value");
  return runner(value.slice(PREFIX.length));
}
```

`src/tokens/cursor-store.ts`:

```ts
import { DatabaseSync } from "node:sqlite";
import { decryptCursorSafeValue } from "./decrypt.js";
import type { CursorTokens } from "./types.js";

export async function readCursorTokens(dbPath: string): Promise<CursorTokens | null> {
  try {
    const db = new DatabaseSync(`file:${dbPath}?mode=ro`, { readOnly: true });
    const rowA = db.prepare("select value from ItemTable where key='cursorAuth/accessToken'").get() as { value: string } | undefined;
    const rowR = db.prepare("select value from ItemTable where key='cursorAuth/refreshToken'").get() as { value: string } | undefined;
    db.close();
    if (!rowA?.value || !rowR?.value) return null;
    return {
      accessToken: await decryptCursorSafeValue(rowA.value),
      refreshToken: await decryptCursorSafeValue(rowR.value),
    };
  } catch {
    return null;
  }
}
```

（`DatabaseSync` 构造签名以 Node 24 实际为准：若 `readOnly` 选项不可用，改用 URI `mode=ro`。)

`src/tokens/cache.ts`:

```ts
import { readFileSync, writeFileSync, renameSync, existsSync } from "node:fs";
import type { CursorTokens } from "./types.js";

export class CredentialCache {
  constructor(private path: string) {}
  load(): CursorTokens | null {
    try {
      if (!existsSync(this.path)) return null;
      const j = JSON.parse(readFileSync(this.path, "utf8"));
      return j.version === 1 && typeof j.accessToken === "string" && typeof j.refreshToken === "string"
        ? { accessToken: j.accessToken, refreshToken: j.refreshToken } : null;
    } catch { return null; }
  }
  save(t: CursorTokens): void {
    const tmp = this.path + ".tmp";
    writeFileSync(tmp, JSON.stringify({ version: 1, ...t }, null, 2));
    renameSync(tmp, this.path);
  }
}
```

测试里 `beforeAll` 中 `_setRunnerForTests(async (b64) => b64 === "QUJD" ? "tok-A" : "tok-B")`。

- [ ] **Step 3: 跑测试**

Run: `npm test` → Expected: PASS。

- [ ] **Step 4: 提交**

```bash
git add -A && git commit -m "feat: token store with DPAPI decryption"
```

---

### Task 4: auth——device 登录与 token 刷新

**Files:**
- Create: `src/auth/device-login.ts`
- Create: `src/auth/refresh.ts`
- Create: `src/auth/orchestrator.ts`
- Test: `tests/auth.test.ts`

**Interfaces:**
- Consumes: `CursorTokens`(Task 3)。
- Produces:
  - `startDeviceLogin(opts: { websiteUrl?: string; backendUrl?: string; openBrowser?: (url: string) => void }): { loginUrl: string; poll: () => Promise<CursorTokens> }`(device-login.ts)；内部：verifier = base64url(32 随机字节),challenge = base64url(sha256(verifier)),uuid = crypto.randomUUID();`poll()` 每 1s GET `${backendUrl}/auth/poll?uuid&verifier`,404 继续，200 按 fixture 解析，网络错误继续，最长 10 分钟抛 `DeviceLoginTimeoutError`。
  - `refreshTokens(refreshToken: string, opts?: { backendUrl?: string; clientId?: string }): Promise<CursorTokens>`(refresh.ts)；响应含 `shouldLogout:true` 抛 `AuthExpiredError`；成功返回 `{ accessToken: access_token, refreshToken: refresh_token ?? 原值 }`。
  - `class AuthOrchestrator { constructor(cache: CredentialCache, opts?: {backendUrl?, clientId?}); getValidTokens(): Promise<CursorTokens> }`(orchestrator.ts)——缓存有效（accessToken JWT `exp` 未过）直接返回；否则 refresh，失败抛 `AuthExpiredError`。
  - `class AuthExpiredError extends Error`、`class DeviceLoginTimeoutError extends Error`。

常量默认值（写入 `src/auth/constants.ts`):`DEFAULT_BACKEND_URL = "https://api2.cursor.sh"`,`DEFAULT_CLIENT_ID = "KbZUR41cY7W6zRSdpSUJ7I7mLYBKOCmB"`,`DEFAULT_WEBSITE_URL = "https://cursor.com"`。

- [ ] **Step 1: 写失败测试（mock fetch)**

`tests/auth.test.ts` 要点：

```ts
import { test, expect, vi, afterEach } from "vitest";
import { refreshTokens, AuthExpiredError } from "../src/auth/refresh.js";
import { startDeviceLogin } from "../src/auth/device-login.js";
import { AuthOrchestrator } from "../src/auth/orchestrator.js";
import { CredentialCache } from "../src/tokens/cache.js";
import { mkdtempSync } from "node:fs";
import { join } from "node:path";
import { tmpdir } from "node:os";

const backend = "https://api2.cursor.sh";

afterEach(() => vi.unstubAllGlobals());

test("refreshTokens exchanges token", async () => {
  vi.stubGlobal("fetch", vi.fn(async () => new Response(
    JSON.stringify({ access_token: "newA", refresh_token: "newR" }), { status: 200 })));
  const t = await refreshTokens("oldR");
  expect(t).toEqual({ accessToken: "newA", refreshToken: "newR" });
  const [url, init] = (fetch as any).mock.calls[0];
  expect(url).toBe(`${backend}/oauth/token`);
  expect(JSON.parse(init.body)).toMatchObject({ grant_type: "refresh_token", refresh_token: "oldR", client_id: expect.any(String) });
});

test("refreshTokens throws AuthExpiredError on shouldLogout", async () => {
  vi.stubGlobal("fetch", vi.fn(async () => new Response(JSON.stringify({ shouldLogout: true, error: "expired" }))));
  await expect(refreshTokens("oldR")).rejects.toBeInstanceOf(AuthExpiredError);
});

test("startDeviceLogin builds loginUrl and polls until tokens", async () => {
  const fetchMock = vi.fn()
    .mockResolvedValueOnce(new Response(null, { status: 404 }))
    .mockResolvedValueOnce(new Response(JSON.stringify({ authId: "x", accessToken: "A", refreshToken: "B" })));
  vi.stubGlobal("fetch", fetchMock);
  let opened = "";
  const s = startDeviceLogin({ openBrowser: (u) => { opened = u; } });
  expect(opened).toContain("https://cursor.com/loginDeepControl?challenge=");
  expect(opened).toContain("&supportsSelectedTeamLogin=true");
  const tokens = await s.poll();
  expect(tokens).toEqual({ accessToken: "A", refreshToken: "B" });
  const pollUrl = fetchMock.mock.calls[0][0] as string;
  expect(pollUrl).toMatch(new RegExp(`^${backend}/auth/poll\\?uuid=[0-9a-f-]{36}&verifier=[A-Za-z0-9_-]+$`));
});

test("orchestrator refreshes when cached access token expired", async () => {
  const dir = mkdtempSync(join(tmpdir(), "cb-"));
  const cache = new CredentialCache(join(dir, "c.json"));
  // exp 已过的 JWT: header.payload.sig,payload = {"exp": 1}
  const expired = "eyJhbGciOiJub25lIn0." + Buffer.from(JSON.stringify({ exp: 1 })).toString("base64url") + ".sig";
  cache.save({ accessToken: expired, refreshToken: "R" });
  vi.stubGlobal("fetch", vi.fn(async () => new Response(JSON.stringify({ access_token: "freshA", refresh_token: "freshR" }))));
  const o = new AuthOrchestrator(cache);
  expect((await o.getValidTokens()).accessToken).toBe("freshA");
  expect(cache.load()?.accessToken).toBe("freshA");
});
```

注意：orchestrator 判断过期的实现要拆出可测函数 `isJwtExpired(token: string, now?: number): boolean`(JWT payload 无 `exp` 时视为过期，强制 refresh)。

- [ ] **Step 2: 实现**

`src/auth/constants.ts`:

```ts
export const DEFAULT_BACKEND_URL = "https://api2.cursor.sh";
export const DEFAULT_CLIENT_ID = "KbZUR41cY7W6zRSdpSUJ7I7mLYBKOCmB";
export const DEFAULT_WEBSITE_URL = "https://cursor.com";
export const DEVICE_LOGIN_TIMEOUT_MS = 10 * 60 * 1000;
export const POLL_INTERVAL_MS = 1000;
```

`src/auth/refresh.ts`:

```ts
import { DEFAULT_BACKEND_URL, DEFAULT_CLIENT_ID } from "./constants.js";
import type { CursorTokens } from "../tokens/types.js";

export class AuthExpiredError extends Error {
  constructor(msg = "Cursor refresh token expired; run `cursor-bridge login`") { super(msg); this.name = "AuthExpiredError"; }
}

export async function refreshTokens(
  refreshToken: string,
  opts: { backendUrl?: string; clientId?: string; fetchImpl?: typeof fetch } = {}
): Promise<CursorTokens> {
  const backendUrl = opts.backendUrl ?? DEFAULT_BACKEND_URL;
  const fetchImpl = opts.fetchImpl ?? fetch;
  const res = await fetchImpl(`${backendUrl}/oauth/token`, {
    method: "POST",
    headers: { "content-type": "application/json" },
    body: JSON.stringify({ grant_type: "refresh_token", client_id: opts.clientId ?? DEFAULT_CLIENT_ID, refresh_token: refreshToken }),
  });
  const j = await res.json().catch(() => null);
  if (!j || typeof j !== "object") throw new Error(`token refresh: HTTP ${res.status} without JSON`);
  if ((j as any).shouldLogout === true) throw new AuthExpiredError(typeof (j as any).error === "string" ? (j as any).error : undefined);
  if (typeof (j as any).access_token !== "string" || (j as any).access_token.length === 0)
    throw new Error(`token refresh: HTTP ${res.status} without access_token`);
  return { accessToken: (j as any).access_token, refreshToken: typeof (j as any).refresh_token === "string" ? (j as any).refresh_token : refreshToken };
}
```

`src/auth/device-login.ts`:

```ts
import { randomBytes, createHash, randomUUID } from "node:crypto";
import { DEFAULT_BACKEND_URL, DEFAULT_WEBSITE_URL, DEVICE_LOGIN_TIMEOUT_MS, POLL_INTERVAL_MS } from "./constants.js";
import type { CursorTokens } from "../tokens/types.js";

export class DeviceLoginTimeoutError extends Error { constructor() { super("device login timed out"); this.name = "DeviceLoginTimeoutError"; } }

const b64url = (b: Buffer | Uint8Array) => Buffer.from(b).toString("base64url");

export function startDeviceLogin(opts: {
  backendUrl?: string; websiteUrl?: string; openBrowser?: (url: string) => void;
  fetchImpl?: typeof fetch; sleep?: (ms: number) => Promise<void>;
} = {}) {
  const backendUrl = opts.backendUrl ?? DEFAULT_BACKEND_URL;
  const websiteUrl = opts.websiteUrl ?? DEFAULT_WEBSITE_URL;
  const fetchImpl = opts.fetchImpl ?? fetch;
  const sleep = opts.sleep ?? ((ms: number) => new Promise<void>((r) => setTimeout(r, ms)));
  const verifier = b64url(randomBytes(32));
  const challenge = b64url(createHash("sha256").update(verifier).digest());
  const uuid = randomUUID();
  const loginUrl = `${websiteUrl}/loginDeepControl?challenge=${challenge}&uuid=${uuid}&mode=ide&supportsSelectedTeamLogin=true`;
  // mode 字面值以 Task 1 protocol.md 为准，此处默认 "ide"
  opts.openBrowser?.(loginUrl);
  const poll = async (): Promise<CursorTokens> => {
    const deadline = Date.now() + DEVICE_LOGIN_TIMEOUT_MS;
    while (Date.now() < deadline) {
      try {
        const res = await fetchImpl(`${backendUrl}/auth/poll?uuid=${uuid}&verifier=${verifier}`);
        if (res.status === 404) { await sleep(POLL_INTERVAL_MS); continue; }
        const j = await res.json();
        if (j && typeof j.accessToken === "string" && typeof j.refreshToken === "string")
          return { accessToken: j.accessToken, refreshToken: j.refreshToken };
      } catch { /* 网络抖动继续轮询 */ }
      await sleep(POLL_INTERVAL_MS);
    }
    throw new DeviceLoginTimeoutError();
  };
  return { loginUrl, poll };
}
```

（测试里通过 `sleep: async () => {}` 与注入 `fetchImpl` 避免真实等待；`vi.stubGlobal("fetch")` 时 `opts.fetchImpl ?? fetch` 取到 mock。)

`src/auth/orchestrator.ts`:

```ts
import { CredentialCache } from "../tokens/cache.js";
import { refreshTokens, AuthExpiredError } from "./refresh.js";
import type { CursorTokens } from "../tokens/types.js";

export function isJwtExpired(token: string, now: number = Date.now()): boolean {
  try {
    const payload = JSON.parse(Buffer.from(token.split(".")[1], "base64url").toString("utf8"));
    return typeof payload.exp !== "number" || payload.exp * 1000 <= now + 5 * 60 * 1000;
  } catch { return true; }
}

export class AuthOrchestrator {
  constructor(private cache: CredentialCache, private opts: { backendUrl?: string; clientId?: string } = {}) {}
  async getValidTokens(): Promise<CursorTokens> {
    const cached = this.cache.load();
    if (cached && !isJwtExpired(cached.accessToken)) return cached;
    if (!cached) throw new AuthExpiredError("no cached credentials; run `cursor-bridge login`");
    const fresh = await refreshTokens(cached.refreshToken, this.opts);
    this.cache.save(fresh);
    return fresh;
  }
}
```

- [ ] **Step 3: 跑测试**

Run: `npm test` → Expected: PASS。

- [ ] **Step 4: 提交**

```bash
git add -A && git commit -m "feat: device login and token refresh"
```

---

### Task 5: protobuf 运行时 + 消息描述代码生成

**Files:**
- Create: `src/pb/runtime.ts`（编码/解码）
- Create: `src/pb/descriptors.ts`（由 fixture 生成；含生成脚本 `scripts/gen-descriptors.mjs`)
- Test: `tests/pb.test.ts`

**Interfaces:**
- Consumes: `tests/fixtures/aiserver-messages.json`(Task 1)。
- Produces:
  - `type FieldDesc = { no: number; name: string; kind: "scalar"|"message"|"enum"; T?: string; repeated?: boolean }`
  - `type MsgDesc = { name: string; fields: FieldDesc[]; nested?: Record<string, MsgDesc> }`
  - `encodePb(desc: MsgDesc, value: Record<string, unknown>): Uint8Array`
  - `decodePb(desc: MsgDesc, bytes: Uint8Array): Record<string, unknown>`
  - 标量 T 映射（protobuf 类型号）：`9/string, 12/bytes, 8/bool, 3&5/int64(varint), 13/uint32(varint), 1&2/fixed64(8 字节 LE), 7/fixed32`。varint 用 BigInt 处理 64 位。
  - 解码只实现服务端响应与请求需要的 wire type 全集（varint/64bit/length-delimited/32bit)，未知字段跳过。

- [ ] **Step 1: 写失败测试**

`tests/pb.test.ts`:

```ts
import { test, expect } from "vitest";
import { encodePb, decodePb, type MsgDesc } from "../src/pb/runtime.js";

const msg: MsgDesc = {
  name: "Test",
  fields: [
    { no: 1, name: "name", kind: "scalar", T: "9" },
    { no: 2, name: "nums", kind: "scalar", T: "13", repeated: true },
    { no: 3, name: "flag", kind: "scalar", T: "8" },
    { no: 4, name: "big", kind: "scalar", T: "3" },
    { no: 5, name: "child", kind: "message" },
  ],
};
const child: MsgDesc = { name: "Child", fields: [{ no: 1, name: "v", kind: "scalar", T: "9" }] };

test("roundtrip", () => {
  const value = { name: "hi", nums: [1, 300, 7], flag: true, big: 2n ** 60n, child: { v: "x" } };
  const bytes = encodePb(msg, value, { Child: child });
  const back = decodePb(msg, bytes, { Child: child });
  expect(back.name).toBe("hi");
  expect(back.nums).toEqual([1, 300, 7]);
  expect(back.flag).toBe(true);
  expect(back.big).toBe(2n ** 60n);
  expect(back.child).toEqual({ v: "x" });
});

test("unknown fields are skipped", () => {
  const bytes = new Uint8Array([0x0a, 0x02, 0x68, 0x69, 0x30, 0x07]); // field1 "hi" + field6 varint 7
  const back = decodePb(msg, bytes, {});
  expect(back.name).toBe("hi");
  expect(back).not.toHaveProperty("nums");
});

test("golden vector from real cursor response", async () => {
  // Task 1 后从 protocol.md 附录抄一个真实的 StreamChat 响应帧 hex,断言解析出的文本
});
```

- [ ] **Step 2: 实现 runtime**

`src/pb/runtime.ts` 核心（手写，约 150 行）:

```ts
export type FieldDesc = { no: number; name: string; kind: "scalar" | "message" | "enum"; T?: string; repeated?: boolean };
export type MsgDesc = { name: string; fields: FieldDesc[] };
export type DescTable = Record<string, MsgDesc>;

export function encodePb(desc: MsgDesc, value: Record<string, any>, table: DescTable): Uint8Array { /* 按字段号升序写;length-delimited;嵌入消息递归 */ }
export function decodePb(desc: MsgDesc, bytes: Uint8Array, table: DescTable): Record<string, any> { /* 读 tag → wire type → 值;未知跳过 */ }
```

wire type 规则：标量 T ∈ {3,5,13,8} → varint;T ∈ {1} → 64bit;{9,12} 及 message → length-delimited;{7} → 32bit。message 字段的值是普通对象，编码时按字段名查 desc.fields 中 kind==="message" 的嵌套消息名（FieldDesc 增加 `msg?: string` 指向 table 键）。

- [ ] **Step 3: 生成 descriptors.ts**

`scripts/gen-descriptors.mjs`：读 `tests/fixtures/aiserver-messages.json`，只保留 `docs/protocol.md` 中标记为"必需"的消息（StreamChatTryReallyHard 请求/响应链 + AvailableModels 请求/响应链），输出 `src/pb/descriptors.ts`:

```ts
// 由 scripts/gen-descriptors.mjs 生成,勿手改
export const DESCRIPTORS = { ... } as const;
```

`package.json` 加 script:`"gen": "node scripts/gen-descriptors.mjs"`。

- [ ] **Step 4: 跑测试**

Run: `npm test` → Expected: PASS(golden 测试在 Task 1 有真实样例后填写）。

- [ ] **Step 5: 提交**

```bash
git add -A && git commit -m "feat: protobuf runtime and descriptor codegen"
```


---

### Task 6: cursor-ai-client——checksum、Connect 传输、模型列表与流式对话

**Files:**
- Create: `src/ai/checksum.ts`
- Create: `src/ai/connect.ts`（帧编解码 + POST 流式）
- Create: `src/ai/client.ts`
- Test: `tests/ai.test.ts`

**Interfaces:**
- Consumes: Task 4 `getValidTokens` 形式（client 构造收 `tokenProvider: () => Promise<string>`)、Task 5 `encodePb/decodePb/DESCRIPTORS`、Task 1 protocol.md 的字段映射。
- Produces:
  - `computeChecksum(machineId: string, macMachineId?: string, now?: number): string`
  - `async function* parseConnectStream(body: ReadableStream<Uint8Array>, msgName: string): AsyncGenerator<Record<string, unknown>>`——按 5 字节帧头（flags + u32 LE 长度）拆帧，flags & 0x02 为 trailer(JSON,含 endStream 错误）；其余帧按 `msgName` 解码。
  - `class CursorAiClient { constructor(opts: { backendUrl?: string; machineId: string; macMachineId?: string; tokenProvider: () => Promise<string>; fetchImpl?: typeof fetch }); listModels(): Promise<ModelInfo[]>; streamChat(req: StreamChatRequest): AsyncIterable<ChatEvent> }`
  - `type ModelInfo = { name: string }`（按 Task 1 提取的 AvailableModels 响应字段扩）;`type StreamChatRequest`/`type ChatEvent` 由 protocol.md 的字段表定义为 plain object，例如 `{ model: string; messages: Array<{role, content, toolCalls?}> }` → `{ type: "text"|"tool_call"|"done"|"error", ... }`。
  - 请求路径/头以 protocol.md 为准：`POST ${backendUrl}/aiserver.v1.AiService/StreamChatTryReallyHard`,`Content-Type: application/proto`,`Connect-Protocol-Version: 1`,`Authorization: Bearer <token>`,`x-cursor-checksum`,`x-cursor-client-type: ide`（若有差异按 protocol.md 改）。

- [ ] **Step 1: 写失败测试**

`tests/ai.test.ts` 要点：

```ts
import { test, expect, vi } from "vitest";
import { computeChecksum } from "../src/ai/checksum.js";
import { CursorAiClient } from "../src/ai/client.js";

test("checksum = b64(6-byte time) + machineId", () => {
  // floor(now/1e6) 手工算:选 now = 1_800_000_000_000 -> 1_800_000
  const c = computeChecksum("MID", undefined, 1_800_000_000_000);
  expect(c.startsWith("MID")).toBe(false);
  const timeB64 = Buffer.from([0x00, 0x00, 0x1b, 0x77, 0x40, 0x00]).toString("base64"); // 1800000 的 6 字节 big-endian
  expect(c).toBe(timeB64 + "MID");
  expect(computeChecksum("MID", "MAC", 1_800_000_000_000)).toBe(timeB64 + "MID/MAC");
});

function framed(...payloads: Uint8Array[]): ReadableStream<Uint8Array> {
  const enc = new TextEncoder();
  const chunks: Uint8Array[] = [];
  for (const p of payloads) {
    const head = new Uint8Array(5); head[0] = 0;
    new DataView(head.buffer).setUint32(1, p.length, true);
    chunks.push(head, p);
  }
  // trailer: flags=2, JSON {"endStream":true}
  const t = enc.encode(JSON.stringify({ endStream: true }));
  const head = new Uint8Array(5); head[0] = 2;
  new DataView(head.buffer).setUint32(1, t.length, true);
  chunks.push(head, t);
  let i = 0;
  return new ReadableStream({ pull(c) { if (i < chunks.length) c.enqueue(chunks[i++]); else c.close(); } });
}

test("streamChat posts framed connect request and yields decoded events", async () => {
  const enc = new TextEncoder();
  // 构造一个最小响应帧:以 Task 1 protocol.md 中 StreamChat 响应的第一个文本字段为准,
  // 这里用占位消息名断言 decodePb 被调用;真实字段填在 Step 2 后
  const fetchMock = vi.fn(async () => new Response(framed(enc.encode("fake-pb-bytes")), { status: 200 }));
  const client = new CursorAiClient({ machineId: "MID", tokenProvider: async () => "tok", fetchImpl: fetchMock as any });
  const [url, init] = (fetchMock as any).mock.calls[0];
  expect(url).toContain("/aiserver.v1.AiService/StreamChatTryReallyHard");
  expect(init.headers["Content-Type"]).toBe("application/proto");
  expect(init.headers["Authorization"]).toBe("Bearer tok");
  expect(init.headers["x-cursor-checksum"]).toContain("MID");
  const events = await collect(client.streamChat({ model: "claude-sonnet-4-6", messages: [{ role: "user", content: "hi" }] }));
  expect(events.length).toBeGreaterThan(0);
});
```

`collect` 为测试内辅助：`const out = []; for await (const e of iter) out.push(e); return out;`

- [ ] **Step 2: 实现**

`src/ai/checksum.ts`:

```ts
export function computeChecksum(machineId: string, macMachineId?: string, now: number = Date.now()): string {
  const x = Math.floor(now / 1e6);
  const a = new Uint8Array(6);
  for (let i = 5; i >= 0; i--) { a[i] = Number(x % 256n); }
  const time = Buffer.from(a).toString("base64");
  return macMachineId ? `${time}${machineId}/${macMachineId}` : `${time}${machineId}`;
}
```

(6 字节构造：把 floor(now/1e6) 按 big-endian 写入 6 字节，对齐 bundle 中 `x>>40&255...` 的顺序；测试用例锁定行为。)

`src/ai/connect.ts`:

```ts
export function encodeFrame(payload: Uint8Array, flags = 0): Uint8Array { /* 5 字节头 + payload */ }
export async function* parseConnectStream(
  body: ReadableStream<Uint8Array>, decode: (bytes: Uint8Array) => Record<string, unknown>
): AsyncGenerator<{ kind: "msg"; value: Record<string, unknown> } | { kind: "end"; error?: unknown }> {
  const reader = body.getReader();
  let buf = new Uint8Array(0);
  const concat = (a: Uint8Array, b: Uint8Array) => { const r = new Uint8Array(a.length + b.length); r.set(a); r.set(b, a.length); return r; };
  try {
    for (;;) {
      const { done, value } = await reader.read();
      if (done) break;
      buf = concat(buf, value);
      while (buf.length >= 5) {
        const flags = buf[0];
        const len = new DataView(buf.buffer, buf.byteOffset).getUint32(1, true);
        if (buf.length < 5 + len) break;
        const payload = buf.subarray(5, 5 + len);
        buf = buf.subarray(5 + len);
        if (flags & 0x02) {
          const j = JSON.parse(new TextDecoder().decode(payload));
          yield { kind: "end", error: j?.error };
        } else {
          yield { kind: "msg", value: decode(payload) };
        }
      }
    }
  } finally { reader.cancel().catch(() => {}); }
}
```

`src/ai/client.ts`（骨架，字段映射以 protocol.md 为准）:

```ts
import { encodePb, decodePb, DESCRIPTORS } from "../pb/runtime.js"; // DESCRIPTORS 从 ./pb/descriptors.js
import { computeChecksum } from "./checksum.js";
import { encodeFrame, parseConnectStream } from "./connect.js";
import { DEFAULT_BACKEND_URL } from "../auth/constants.js";

export class CursorAiClient {
  constructor(private opts: { backendUrl?: string; machineId: string; macMachineId?: string; tokenProvider: () => Promise<string>; fetchImpl?: typeof fetch }) {}

  private async post(method: string, reqMsg: string, reqValue: Record<string, any>, resMsg: string) {
    const backendUrl = this.opts.backendUrl ?? DEFAULT_BACKEND_URL;
    const fetchImpl = this.opts.fetchImpl ?? fetch;
    const token = await this.opts.tokenProvider();
    const payload = encodeFrame(encodePb((DESCRIPTORS as any)[reqMsg], reqValue, DESCRIPTORS));
    const res = await fetchImpl(`${backendUrl}/aiserver.v1.AiService/${method}`, {
      method: "POST",
      headers: {
        "Content-Type": "application/proto",
        "Connect-Protocol-Version": "1",
        Authorization: `Bearer ${token}`,
        "x-cursor-checksum": computeChecksum(this.opts.machineId, this.opts.macMachineId),
        "x-cursor-client-type": "ide",
      },
      body: payload,
    });
    if (!res.ok || !res.body) throw new Error(`AiService/${method}: HTTP ${res.status} ${await res.text().catch(() => "")}`.slice(0, 300));
    return parseConnectStream(res.body, (b) => decodePb((DESCRIPTORS as any)[resMsg], b, DESCRIPTORS));
  }

  async listModels(): Promise<Array<{ name: string }>> {
    const out: Array<{ name: string }> = [];
    for await (const ev of this.post("AvailableModels", /*req*/ (DESCRIPTORS as any).__REQ_MODELS__, {}, /*res*/ "__RES_MODELS__")) {
      if (ev.kind === "msg") out.push(...extractModelNames(ev.value)); // 按 protocol.md 响应字段
    }
    return out;
  }

  streamChat(req: { model: string; messages: Array<{ role: string; content: string }> }): AsyncIterable<any> {
    const self = this;
    return (async function* () {
      const rpcReq = toStreamChatRpc(req); // translate.ts:OpenAI 消息 → RPC 字段,按 protocol.md
      for await (const ev of self.post("StreamChatTryReallyHard", "__REQ_CHAT__", rpcReq, "__RES_CHAT__")) {
        if (ev.kind === "end") { if (ev.error) throw new Error(`stream ended with error: ${JSON.stringify(ev.error).slice(0, 300)}`); return; }
        yield* fromStreamChatRpcEvent(ev.value); // 产出 {type:"text",text}|{type:"done",...}
      }
    })();
  }
}
```

`src/pb/descriptors.ts` 顶部导出消息名常量(如 `export const REQ_MODELS = "aiserver.v1.StreamChatTryReallyHardRequest"`,真实值以 fixtures 为准),client.ts 从 `../pb/descriptors.js` 导入 `DESCRIPTORS` 与这些常量(`runtime.ts` 不导出 DESCRIPTORS)。

翻译层 `src/ai/translate.ts`:`toStreamChatRpc`(OpenAI messages→RPC；工具调用字段若 protocol.md 标记可选则 v1 先透传文本 + basic tool 结构）、`fromStreamChatRpcEvent`(RPC 事件→统一 ChatEvent)。纯函数，测试覆盖：给定 OpenAI 请求对象，断言 RPC 请求对象字段与 protocol.md 一致；给定 fixture 响应帧（Task 1 抓的真实 hex)，断言产出的 ChatEvent 序列。

- [ ] **Step 3: 跑测试**

Run: `npm test` → Expected: PASS。

- [ ] **Step 4: 提交**

```bash
git add -A && git commit -m "feat: cursor ai client (connect transport, checksum, streaming)"
```

---

### Task 7: server——OpenAI 兼容端点 + api.json registry

**Files:**
- Create: `src/server/models.ts`（模型列表缓存）
- Create: `src/server/chat.ts`（OpenAI ↔ client 翻译 + SSE)
- Create: `src/server/registry.ts`（api.json)
- Create: `src/server/app.ts`（http 服务组装）
- Test: `tests/server.test.ts`

**Interfaces:**
- Consumes: `CursorAiClient.listModels/streamChat`、`AuthOrchestrator`（经 tokenProvider)、registry 模型元数据类型 `RegistryModel`(Task 5 格式）。
- Produces:
  - `createBridgeServer(opts: { port: number; ai: CursorAiClient; modelCacheTtlMs?: number; getRegistryModels: () => Promise<RegistryModel[]>; apiKey?: string }): { listen(): Promise<{ port: number }>; close(): Promise<void> }`
  - `GET /v1/models` → `{ object: "list", data: [{ id, object: "model", created: 0, owned_by: "cursor" }] }`，缓存 TTL 默认 10 分钟；未知模型名触发一次即时刷新（命中缓存则 200，否则 404 上游错误透传）。
  - `POST /v1/chat/completions` — 请求体 OpenAI ChatCompletion 参数（`model/messages/stream/tools/temperature/max_tokens`)；响应 `stream:true` 时输出 SSE:`data: {chunk}\n\n` + `data: [DONE]`;`stream:false` 时聚合为完整 JSON。无 `stream` 字段默认 true（Kimi Code 全流式）。
  - `GET /api.json` → registry 文档（格式见 plan Global Constraints 第 5 条）:`providers.cursor = { id: "cursor", name: "Cursor (cursor-bridge)", api: "http://127.0.0.1:42137/v1", type: "openai", models: {...} }`。模型元数据：name 用模型 id;`tool_call: true`;reasoning 按模型名前缀（`claude-3-7|claude-4|o1|o3|gpt-5|gemini` → true);`limit.context` 按 protocol.md 的模型表（无则省略，不编造）。

`src/server/registry.ts` 额外导出 `toRegistryModels(modelNames: string[]): RegistryModel[]`(生成 Task 5 格式的模型条目:tool_call 恒 true,reasoning 按前缀 `claude-3-7|claude-4|o1|o3|gpt-5|gemini` 判定,name 用模型 id)。Task 8 的 cli.ts 从 `./server/models.js` 导入 `ModelCache`、从 `./auth/orchestrator.js` 额外导入 `isJwtExpired`。

- [ ] **Step 1: 写失败测试**

`tests/server.test.ts` 要点（起真实端口 0，用 mock ai client):

```ts
import { test, expect, afterAll } from "vitest";
import { createBridgeServer } from "../src/server/app.js";

function fakeAi(models: string[]) {
  return {
    listModels: async () => models.map((name) => ({ name })),
    streamChat: async function* () {
      yield { type: "text", text: "Hello" };
      yield { type: "done", usage: { prompt_tokens: 1, completion_tokens: 1 } };
    },
  } as any;
}

let srv: any; let base: string;
afterAll(async () => srv?.close());

test("GET /v1/models returns openai shape", async () => {
  srv = createBridgeServer({ port: 0, ai: fakeAi(["claude-sonnet-4-6"]), getRegistryModels: async () => [] });
  const { port } = await srv.listen(); base = `http://127.0.0.1:${port}`;
  const r = await fetch(`${base}/v1/models`);
  const j = await r.json();
  expect(j.object).toBe("list");
  expect(j.data[0]).toMatchObject({ id: "claude-sonnet-4-6", object: "model", owned_by: "cursor" });
});

test("POST /v1/chat/completions streams SSE chunks then [DONE]", async () => {
  const r = await fetch(`${base}/v1/chat/completions`, {
    method: "POST", headers: { "content-type": "application/json" },
    body: JSON.stringify({ model: "claude-sonnet-4-6", messages: [{ role: "user", content: "hi" }], stream: true }),
  });
  const text = await r.text();
  expect(text).toContain('"delta":{"role":"assistant"');
  expect(text).toContain("Hello");
  expect(text.trim().endsWith("data: [DONE]")).toBe(true);
});

test("GET /api.json matches kimi registry schema", async () => {
  const r = await fetch(`${base}/api.json`);
  const j = await r.json();
  const p = j.providers?.cursor ?? j.cursor; // 以 Task 1 确认的真实顶层结构为准
  expect(p.type).toBe("openai");
  expect(p.api).toContain("/v1");
  expect(p.models["claude-sonnet-4-6"].id).toBe("claude-sonnet-4-6");
});
```

注意：api.json 顶层结构以 kimi.exe 解析器确认为准——`toProviderEntry` 操作的是"顶层 provider 键 → entry 对象"，所以文档结构是 `{ "cursor": { id, name, api, type, models } }`（测试按此断言；若导入实测不符，以实测调整并回改 protocol.md)。

- [ ] **Step 2: 实现**

`src/server/app.ts` 用 `node:http`，路由手写（三个端点，不引框架）。SSE:`res.writeHead(200, {"content-type": "text/event-stream", "cache-control": "no-cache", connection: "keep-alive"})`,chunk 序列：`{id, object: "chat.completion.chunk", created, model, choices: [{index:0, delta: {role: "assistant", content}, finish_reason: null}]}`，终止帧 `finish_reason: "stop"` + `usage`。非流式：聚合文本与 usage，输出 `chat.completion` 完整对象。

模型缓存：`src/server/models.ts` 导出 `class ModelCache { constructor(ai, ttlMs=600_000); async get(): Promise<string[]>; async refresh(): Promise<void> }`——get 过期则调 `ai.listModels()` 缓存；chat 处理器遇到未知模型先 `refresh()` 再判断是否仍未知（未知 → 400 `{error: {message: "model not available on this Cursor account"}}`)。

- [ ] **Step 3: 跑测试**

Run: `npm test` → Expected: PASS。

- [ ] **Step 4: 提交**

```bash
git add -A && git commit -m "feat: openai-compatible server and api.json registry"
```

---

### Task 8: CLI 集成 + 端到端验证 + 文档

**Files:**
- Create: `src/cli.ts`
- Create: `src/bridge.ts`（组装：cache → orchestrator → ai client → server)
- Create: `README.md`
- Test: `tests/bridge.test.ts`（集成：假 ai client 走通 listen → /v1/models → /chat/completions)

**Interfaces:**
- Consumes: 全部前序任务。
- Produces: 命令 `start` / `login` / `status`。

- [ ] **Step 1: 集成测试**

`tests/bridge.test.ts`:

```ts
import { test, expect } from "vitest";
import { CredentialCache } from "../src/tokens/cache.js";
import { AuthOrchestrator } from "../src/auth/orchestrator.js";
import { mkdtempSync } from "node:fs";
import { join } from "node:path";
import { tmpdir } from "node:os";

test("bridge boots end-to-end with fake ai and valid cached token", async () => {
  const dir = mkdtempSync(join(tmpdir(), "cb-"));
  const future = "eyJhbGciOiJub25lIn0." + Buffer.from(JSON.stringify({ exp: Math.floor(Date.now() / 1000) + 3600 })).toString("base64url") + ".sig";
  const cache = new CredentialCache(join(dir, "c.json"));
  cache.save({ accessToken: future, refreshToken: "r" });
  const orchestrator = new AuthOrchestrator(cache);
  // machineId 从 state.vscdb 读:抽 getMachineId(dbPath) 工具函数,测试注入固定值
  const { createBridgeServer } = await import("../src/server/app.js");
  const srv = createBridgeServer({
    port: 0,
    ai: { listModels: async () => [{ name: "m1" }], streamChat: async function* () { yield { type: "text", text: "ok" }; yield { type: "done", usage: { prompt_tokens: 1, completion_tokens: 1 } }; } } as any,
    getRegistryModels: async () => [{ id: "m1", name: "m1", tool_call: true }],
  });
  const { port } = await srv.listen();
  const r = await fetch(`http://127.0.0.1:${port}/api.json`);
  expect((await r.json()).cursor.models.m1.tool_call).toBe(true);
  await srv.close();
});
```

- [ ] **Step 2: 实现 cli**

`src/cli.ts`:

```ts
import { CredentialCache } from "./tokens/cache.js";
import { AuthOrchestrator, AuthExpiredError } from "./auth/orchestrator.js";
import { startDeviceLogin } from "./auth/device-login.js";
import { readCursorTokens } from "./tokens/cursor-store.js";
import { CursorAiClient } from "./ai/client.js";
import { createBridgeServer } from "./server/app.js";
import { spawn } from "node:child_process";
import { homedir } from "node:os";
import { join } from "node:path";

const CACHE_PATH = join(homedir(), ".cursor-bridge", "credentials.json");
const CURSOR_DB = join(process.env.APPDATA ?? join(homedir(), "AppData/Roaming"), "Cursor/User/globalStorage/state.vscdb");
const [cmd] = process.argv.slice(2);

switch (cmd) {
  case "login": {
    // 1) 先试本地 Cursor 存储;2) 失败转 device login
    const fromStore = await readCursorTokens(CURSOR_DB);
    if (fromStore) { new CredentialCache(CACHE_PATH).save(fromStore); console.log("imported tokens from Cursor storage"); break; }
    const s = startDeviceLogin({ openBrowser: (u) => spawn("cmd", ["/c", "start", "", u], { detached: true, stdio: "ignore" }).unref() });
    console.log("open this URL to log in:\n" + s.loginUrl);
    const t = await s.poll();
    new CredentialCache(CACHE_PATH).save(t);
    console.log("login OK");
    break;
  }
  case "start": {
    const cache = new CredentialCache(CACHE_PATH);
    const orchestrator = new AuthOrchestrator(cache);
    const machineId = await getMachineId(CURSOR_DB); // ItemTable storage.serviceMachineId
    const ai = new CursorAiClient({ machineId, tokenProvider: async () => (await orchestrator.getValidTokens()).accessToken });
    const modelCache = new ModelCache(ai); // server/app 内部用;此处实例化并传入 getRegistryModels
    const srv = createBridgeServer({ port: 42137, ai, getRegistryModels: async () => toRegistryModels(await modelCache.get()) });
    await srv.listen();
    console.log("cursor-bridge listening on http://127.0.0.1:42137 (api.json: /api.json)");
    break;
  }
  case "status": {
    const c = new CredentialCache(CACHE_PATH).load();
    console.log(c ? `cached tokens present (access ${c.accessToken.slice(0, 8)}…, expires: ${isJwtExpired(c.accessToken) ? "expired" : "valid"})` : "no cached tokens; run login");
    break;
  }
  default:
    console.log("usage: cli.ts start|login|status");
}
```

`getMachineId(dbPath)` 放 `src/tokens/cursor-store.ts`（同文件加导出，复用 node:sqlite)。

- [ ] **Step 3: 跑全部测试 + 真机端到端**

Run: `npm test` → Expected: 全 PASS。

真机验证（按序执行，需要用户在场完成一次浏览器授权；若 Cursor 存储导入成功则跳过浏览器）:

```bash
npm run login
npm run start
```

然后在 Kimi Code TUI:`/provider` → `[ Add New Platform ]` → 粘贴 `http://127.0.0.1:42137/api.json` → 选择模型发送一条消息 → `/provider refresh` 确认同步。结果记录进 `docs/e2e.md`。

- [ ] **Step 4: README + 提交**

`README.md`：安装（Node ≥ 22)、三个命令、Kimi 接入三步、开机自启（`schtasks /create /tn cursor-bridge /tr "node E:\work\cursor-bridge\dist\cli.js start" /sc onlogon`)、风险声明（非官方接口、ToS、token 明文缓存）。

```bash
git add -A && git commit -m "feat: cli integration, e2e verified, docs"
```

---

## Self-Review 记录

- **Spec 覆盖**：规格各节 → 任务映射：登录/token 管理 → Task 3/4/8；模型同步（全部自动）→ Task 6 `listModels` + Task 7 缓存与 registry;Kimi 接入 → Task 7 `/api.json` + Task 8 真机验证；错误处理（401 提示重新 login、429/5xx 透传、解析失败日志）→ Task 4 `AuthExpiredError`、Task 6 `post()` 错误、Task 7 未知模型 400；测试 → 各任务 vitest + Task 8 端到端。无遗漏。
- **占位符扫描**：Task 6 中 `__REQ_MODELS__` 等占位常量由 Task 1 的 protocol.md 固化、`gen-descriptors.mjs` 生成，属"依赖 spike 结果的命名占位"，生成脚本与断言测试已给出，非开放式占位。
- **类型一致性**:`CursorTokens`/`CredentialCache`/`AuthOrchestrator`/`CursorAiClient`/`createBridgeServer` 签名在 Task 3–8 间一致；`ModelCache` 在 Task 7 定义、Task 8 引用，已对齐。
