# UE 5.8.3 设计文档章节撰写规范(给撰写者)

源码根(下称 `$UE`):`/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release`
引擎目录(下称 `$E`):`$UE/Engine`
输出根:`/home/timeshift/opensource/break/docs/ue5.8.3/`
章节输出目录:`/home/timeshift/opensource/break/docs/ue5.8.3/design/`

## 0. 硬性原则

1. **一切以源码为准**。每个结论必须来自你亲自读过的源码(.h/.cpp/.Build.cs/.cs),禁止凭记忆或旧版本经验臆造。读不到、不确定的,写"未在源码中确认",不要编造。
2. **原型签名逐字抄自头文件**(去掉 `*_API` 导出宏即可),并标注 `路径:行号`(路径相对 `$E`)。不要改写参数名/类型。
3. 语言:中文。标识符、类型名、路径、代码保持原文。
4. 图一律使用 **Mermaid**(```mermaid 代码块):`classDiagram`、`sequenceDiagram`、`flowchart TD/LR`、`stateDiagram-v2`。语法要求:
   - 节点/类名只用字母数字下划线;含 `::`、`<>`、空格、中文的文字放进引号标签,如 `A["UObject::Serialize"]`。
   - classDiagram 里模板类写成 `class TArray~T~`;方法行不要出现 `{`、`}`、`<`、`>`(用 `~T~`),不要出现分号。
   - sequenceDiagram 参与者用 `participant GT as "Game Thread"` 形式;消息文本避免 `;` 与 `#`。
   - 每个图控制在 ≤ 40 个节点,过大就拆成多张。
5. 禁止写成"概述性套话"。每个小节要有具体类名/函数名/文件路径/数值(如线程优先级、队列名、枚举值)。
6. 完整穷举清单(每个头文件每个符号)**已由工具生成**在 `/home/timeshift/opensource/break/docs/ue5.8.3/appendix/api/<Tier>/<Module>.md`(Tier = Runtime/Developer/Editor/Programs/Plugins/Platforms;大模块分为 `.partNN.md`)。你的章节**不重复穷举**,而是:
   - 在"接口清单"中给出你所负责范围内**所有核心/公共入口接口**(类、关键方法、全局函数、委托、宏)的:原型、功能、参数/返回、线程约束、调用时机。可借助附录 grep 定位,例如 `grep -n "FRHICommandListImmediate" appendix/api/Runtime/RHI*.md`。
   - 在章节末尾"附录索引"中列出你覆盖的模块与对应附录文件相对路径。
7. 不要修改 `appendix/`、`tools/` 下任何文件;不要运行会改动 `$UE` 的命令。只在 `design/` 下创建你自己的章节文件。
8. 文件较大时先 Write 前 ~50 行骨架,再用 Edit 追加(用唯一占位符 `<!--CONT-->`,最后一块去掉占位符);单次写入内容 ≤ 50 行。
9. 完成后只回复:章节文件路径、行数、覆盖的模块、**已知缺口/不确定处**(诚实列出)。不要贴正文。

## 1. 章节固定结构

```
# <章节号> <标题>
## X.1 职责、边界与模块清单      (表格:模块名 | 路径 | Build.cs 中的 Public/Private 依赖 | 职责一句话)
## X.2 总体架构                  (分层/组件图 flowchart + 文字说明)
## X.3 类图                      (1~N 张 classDiagram,覆盖继承/组合/依赖;每类一行职责说明)
## X.4 数据字典                  (关键类型/结构/枚举:表格 字段|类型|含义|取值/约束|源码位置)
## X.5 接口清单                  (按类/子系统分组:原型 | 功能 | 参数与返回 | 线程/重入约束 | 位置)
## X.6 关键流程                  (flowchart:初始化/主路径/销毁/异常路径)
## X.7 时序图                    (sequenceDiagram:至少 3 条最关键的跨组件交互)
## X.8 线程模型与同步            (谁在哪个线程;队列/锁/原子/fence;跨线程数据所有权)
## X.9 配置与扩展点              (CVar、ini、委托、模块接口、插件扩展)
## X.10 已知限制/未确认项
## X.11 附录索引
```

## 2. 质量自检(交付前逐条过)

- 每张图的类名/函数名在源码里真实存在(grep 过)。
- 每个"线程约束"写清是 GameThread / RenderThread / RHIThread / 任意线程 / TaskGraph 工作线程,并给出判定依据(`check(IsInGameThread())`、`ENamedThreads::...`、`ENQUEUE_RENDER_COMMAND` 等)。
- 数据字典的字段来自真实头文件,不是推测。
- 章节里没有 TODO/TBD/"待补充"。拿不准就放进 X.10。
