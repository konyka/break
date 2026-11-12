# cursor-bridge 设计文档

日期：2026-11-12
状态：待审阅

## 背景与目标

用户已在 Cursor 编辑器中登录付费账号，希望在 Kimi Code CLI 里直接使用 Cursor 账号可用的模型集合（Claude、GPT、Gemini 等），并要求通过"登录"方式完成接入，模型列表随 Cursor 账号自动同步。

Kimi Code CLI 的接入点（已对照官方文档确认）：

- 支持 `openai` 类型的自定义 provider，可自定义 `base_url` 与 `api_key`；
- `/provider` 支持导入 custom registry（`api.json`），自动创建 provider / models 条目，并可用 `/provider refresh` 同步上游模型增减；
- 不支持任何自定义 OAuth 流程，provider 只能配静态 key —— 因此 token 的获取与刷新必须由代理完成。

结论：需要一个常驻本地代理，把 Cursor 后端包装成 OpenAI 兼容接口 + Kimi registry。

## 方案取舍

| 方案 | 说明 | 取舍 |
| --- | --- | --- |
| A. 常驻本地代理（选定） | Node+TS 服务，OAuth 登录 + token 自动刷新 + OpenAI 兼容端点 + api.json registry | 一次配置长期可用，模型自动同步；多一个常驻进程 |
| B. 一次性导出工具 | 从 Cursor 存储导出 token，生成 config.toml 片段 | 无常驻进程，但 token 过期需手动重跑，模型列表静态，不满足"全部自动同步" |
| C. 现成开源工具 | 直接用 cursor2api / claude-code-router 等 | 用户明确选择自研代理 |

## 总体架构

独立 Node.js + TypeScript 工程，默认目录 `E:\work\cursor-bridge`（不混入引擎仓库）。启动方式 `npx tsx src/main.ts` 或构建后 `node dist/main.js`。

组件划分，各组件单一职责、通过明确接口通信、可独立测试：

- **token-store**：读写 Cursor 本地凭据与自有缓存。数据源为 Cursor 的 `state.vscdb`（SQLite，存储 Auth0 accessToken / refreshToken）。向上层提供 `getValidToken()`，内部处理过期检查与刷新、原子写回。
- **auth**：OAuth 登录流程。refreshToken 失效时，启动临时 localhost 回调服务，打开浏览器走 Cursor 的 Auth0 授权页（客户端参数从 Cursor 安装目录提取），code 换 token。
- **cursor-api-client**：与 Cursor 后端（`api2.cursor.sh` 一类内部接口）通信。三个调用：刷新 token、拉取账号可用模型列表、发起对话补全（SSE 流式透传）。对上屏蔽 Cursor 的请求/响应格式差异。
- **server**：常驻 HTTP 服务，默认绑 `127.0.0.1:42137`（仅本机可达）。
- **cli 入口**：`start`（常驻服务）、`login`（强制重新登录）、`status`（账号、token 有效期、模型数）。

## 登录与 token 管理

首次接入：`cursor-bridge login`

1. 读取 `%APPDATA%\Cursor\User\globalStorage\state.vscdb`，取出 Auth0 accessToken / refreshToken；
2. refreshToken 有效 → 缓存成功，提示可 `start`；
3. refreshToken 失效 → 启动临时 localhost 回调端口，打开浏览器走 Cursor Auth0 授权页，用户授权后回调拿 code 换 token。

存储与刷新：

- token 缓存于 `%USERPROFILE%\.cursor-bridge\credentials.json`，文件 ACL 收紧到当前用户。refreshToken 以明文存放的风险在本节明确接受，后续可升级为 Windows Credential Manager。
- 每次请求前 `getValidToken()` 检查过期时间，提前 5 分钟用 refreshToken 轮换；Auth0 刷新会下发新 refreshToken，必须原子写回（临时文件 + rename）。

错误处理：

- refresh 失效（`invalid_grant` / 401）→ 服务端点返回 401，错误信息明确提示"请重新运行 cursor-bridge login"；
- Cursor 后端 429 / 5xx → 原样透传状态码与错误体；
- Cursor 接口格式变化导致解析失败 → 500 + 本地日志记录原始响应前 200 字节，便于适配。

## 模型同步与 Kimi Code 接入

模型列表：

- `/v1/models` 调 Cursor 模型接口，按账号实际可见性返回；
- 缓存策略：启动拉取 + 每 10 分钟后台刷新 + 收到未知 model 请求时按需刷新一次；
- Cursor 模型 id（如 `claude-4-sonnet`、`gpt-5`）原样暴露；thinking / vision / tool-use 能力由 Kimi Code 按模型名前缀自动匹配，代理侧不声明能力。

registry 端点：

- `GET /api.json` 输出 Kimi Code custom registry 格式，描述 provider（类型 openai，base_url `http://127.0.0.1:42137/v1`）与模型清单；
- Kimi 官方文档只描述了 registry 导入行为，未给出完整字段规范。实现第一步：抓 `/provider` 导入流程的真实 registry 结构，封装为适配层；格式以 Kimi 实际解析为准，Kimi 升级格式时只动适配层。

Kimi 侧接入步骤（一次配置）：

1. `cursor-bridge start`（可注册 Windows 任务计划自启）；
2. Kimi TUI `/provider` → `[ Add New Platform ]` → 粘贴 `http://127.0.0.1:42137/api.json`；
3. CLI 自动创建 provider 与模型条目，选择默认模型；
4. 之后 Cursor 侧模型增减，在 Kimi 里 `/provider refresh` 同步。

## 测试与验证

单元测试（vitest）：

- token-store：临时 SQLite fixture 验证解析与原子写回；
- auth：mock 授权响应，验证 code 换 token 与 refreshToken 轮换保存；
- cursor-api-client：mock fetch，验证模型列表解析与错误码映射；
- server：真实 HTTP 实例，验证 `/v1/models` 缓存行为、`/chat/completions` 流式 SSE 逐帧透传、401 时返回可操作错误提示。

端到端验证（交付标准）：

1. 服务运行后，在 Kimi TUI 通过 `/provider` 导入 `api.json`，模型列表出现；
2. 用 Cursor 账号下某个模型在 Kimi 里发一条真实对话成功；
3. `/provider refresh` 能看到模型列表同步。

## 风险与假设

风险：

- Cursor 后端为未公开接口，格式可能变化或增加校验（社区通用做法，无官方保障）。缓解：cursor-api-client 适配层隔离 + 解析失败详细日志；
- 非官方方式使用 Cursor 会话可能违反其服务条款，个人自用风险较低但存在账号风险，由用户自行决定是否接受；
- token 本地明文缓存，依赖文件 ACL 保护。

假设：

- 本机已安装并登录 Cursor 编辑器（Windows）；
- Node.js ≥ 20 可用；
- Kimi Code 当前版本支持 custom registry 导入（已对官方文档确认）；
- 项目目录 `E:\work\cursor-bridge`。
