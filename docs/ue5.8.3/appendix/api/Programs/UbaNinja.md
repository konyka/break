# Programs / UbaNinja

- module root: `Source/Programs/UnrealBuildAccelerator/Ninja`
- headers: 5; symbols: 257
- symbol kinds: class=3, function=26, macro=2, member=158, namespace=5, prototype=43, struct=18, typedef=1, variable=1

### `Source/Programs/UnrealBuildAccelerator/Ninja/Private/UbaNinjaChromiumWorkarounds.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L25 _function_ `inline bool ShouldForceRunLocally(const TString& description)` (scope `uba`) — Per-edge workarounds for known issues when building Chromium or AOSP through UbaNinja. Some edges must be forced to run locally: - A handful of files hit bugs in Wine when compiled on Windows remote helpers. - A few steps are heavy / transfer huge numbers of files and are simply faster locally. - v8_context_snapshot.bin needs glibc 2.38 but Epic's Horde farm runs AL2023. TODO: The list is matched against the edge description (e.g. "C++ color_data.cc"). Longer term this should move to either: (a) a well-known edge variable in the .ninja file (e.g. `uba_local = 1`) that GN / the generator can set, so fixes live at source, or (b) a sidecar file next to build.ninja listing output paths to force-local. Until then, entries should be added / removed here as new Wine bugs surface and are fixed.
- L84 _function_ `inline double GetPriorityWeight(const StringPool& stringPool, const NinjaBuildEdge& edge)` (scope `uba`) — Bias added to an edge's Kahn critical-path weight to sort it earlier in Pass 1. Critical/Expensive sit far above max real Kahn weight (~hundreds on AOSP) so tiering dominates; within a tier Kahn weight still orders. Keyed on raw rule name (no description-rewriting via CXX_COMPILER→C++); chromium-style rules with `__` need full pre-`__` prefix.
- L99 _function_ `` (scope `uba::GetPriorityWeight`)
- L107 _macro_ `#define UBA_RULE_IS(r) ruleIs(r, u32(sizeof(r) - 1))`
- L108 _macro_ `#define UBA_BASE_IS(b) baseIs(b, u32(sizeof(b) - 1))`

### `Source/Programs/UnrealBuildAccelerator/Ninja/Private/UbaNinjaDepsLog.h` (Private)


#### struct `uba::NinjaLogIndex`  
`struct NinjaLogIndex`  
_L26-57_
- desc: Parsed view of a previous run's .ninja_log (v5) and .ninja_deps (v4) files. All lookups are keyed by a StringKey = hash of the *absolute* path (lowercased on case-insensitive filesystems). That matches the keying used for the mtime cache, so the up-to-date check is a single hash-table find per query. Both ninja log files use char-based paths and so does this reader; we widen to tchar only when calling FixPath / ToStringKey. Load once on a single thread during startup; read freely after.
- L40 _public member_ `UnorderedMap<StringKey, LogEntry> logByOutputKey;`
- L41 _public member_ `UnorderedMap<StringKey, DepsEntry> depsByOutputKey;`
- L43 _public member_ `Vector<StringKey> flatDepKeys;` — referenced by DepsEntry.depOffset/depCount
- L48 _public member_ `Vector<tchar> flatDepPathBuf;` — tchar buffer holding absolute paths for each entry in flatDepKeys. flatDepPathOffsets[i]..[i]+len covers bytes in flatDepPathBuf for dep i. We keep the paths because phase 1 of the up-to-date check needs them to register parent directories for the stat pass.
- L49 _public member_ `Vector<u32> flatDepPathOffset;`
- L50 _public member_ `Vector<u32> flatDepPathLen;`
- L56 _public prototype_ `bool Load(Logger& logger, StringView ninjaDir, StringView workingDir);` — Parse .ninja_log and .ninja_deps from ninjaDir. Missing files are treated as "no prior build" and return true with empty maps — not an error. Paths in the log are stored relative to workingDir; we resolve them against workingDir to get absolute paths before hashing.

#### struct `uba::NinjaLogIndex::LogEntry`  
`struct LogEntry`  
_L28-32_
- L30 _public member_ `u64 outMtime = 0;` — mtime recorded in .ninja_log at end of last successful build
- L31 _public member_ `u64 cmdHash = 0;` — hash of the command used last time (low 64 bits of StringKey)

#### struct `uba::NinjaLogIndex::DepsEntry`  
`struct DepsEntry`  
_L33-38_
- L35 _public member_ `u64 outMtime = 0;` — mtime of the output when these deps were captured
- L36 _public member_ `u32 depOffset = 0;` — index into flatDepKeys
- L37 _public member_ `u32 depCount = 0;`

#### class `uba::NinjaDepsLog`  
`class NinjaDepsLog`  
_L69-140_
- desc: Writes .ninja_deps (v4) and .ninja_log (v5) files during a UbaNinja build. All public methods are thread-safe. Usage: NinjaDepsLog log; log.Init(workingDir, buildStartTime); // In process-finished callback (for each successful process): log.RecordResult(logger, handle); // After build completes: log.Save(logger, ninjaDir);
- L72 _public prototype_ `NinjaDepsLog();`
- L73 _public prototype_ `~NinjaDepsLog();`
- L77 _public prototype_ `void Init(StringView workingDir, u64 buildStartTime);` — Call before any RecordResult calls. workingDir must end with a path separator.
- L82 _public prototype_ `void RegisterOutputs(const ProcessHandle& handle);` — Add handle.GetTrackedOutputs() to cross-edge written-set. MUST be called synchronously from the exit callback before any async RecordResult dispatch — producer-before-consumer ordering relies on it.
- L88 _public prototype_ `void RegisterStaticOutput(StringView absPath);` — Register one statically-declared edge output (absolute path) into the cross-edge set. Called from EnqueueCommands BEFORE any edge runs, so the set is complete the moment RecordResult executes — independent of run order, cache state, or partial-build failures.
- L92 _public prototype_ `void FilterDepsForOutputs(Logger& logger);` — Walk kept deps records and drop dep_ids whose path is in m_outputKeys. Belt-and-braces for anything that slipped past the per-call filter.
- L103 _public prototype_ `void RecordResult(Logger& logger, const ProcessHandle& handle, const tchar* primaryOutputAbsPath = nullptr, bool restat = false, u64 cmdHashOverride = 0);` — Record deps + timing for a successful process (exit code == 0). primaryOutputAbsPath, when non-null, is the edge's declared primary output (use it to avoid keying off a sidecar like .pdb / .rc.res.d). restat=true (rule has restat=1 / phony_output): mtime stored as Now() so a no-op rerun doesn't dirty-mark the edge next run. cmdHashOverride, non-zero: stored verbatim; otherwise we hash si.arguments. Callers know the pre-Expand command; arguments here may be post-Expand (sh -c "..."), so the override avoids coupling the log format to Expand()'s transformations.
- L109 _public prototype_ `bool Save(Logger& logger, StringView ninjaDir);` — ninjaDir must end with a path separator.
- L113 _private prototype_ `u32 GetOrAddPath(StringView absPath);` — Returns the path ID; writes a path record to m_pathBuf if new.
- L116 _private prototype_ `void MakeRelative(StringBufferBase& out, StringView absPath) const;` — Strip m_workingDir prefix from absPath if present; otherwise copy as-is.
- L118 _private member_ `TString m_workingDir;` — trailing separator
- L122 _private member_ `ReaderWriterLock m_pathLock;` — Path records appended to m_pathBuf under write lock BEFORE id is inserted into m_pathIds — any reader observing the id sees the record.
- L123 _private member_ `UnorderedMap<TString, u32> m_pathIds;`
- L124 _private member_ `Vector<u8> m_pathBuf;`
- L125 _private member_ `u32 m_nextPathId = 0;`
- L127 _private member_ `ReaderWriterLock m_depsLock;`
- L128 _private member_ `Vector<u8> m_depsBuf;`
- L130 _private member_ `ReaderWriterLock m_logLock;`
- L131 _private member_ `Vector<u8> m_logBuf;`
- L136 _private member_ `ReaderWriterLock m_outputKeysLock;` — Absolute paths (lowercased on case-insensitive FS) of every file any edge in this build produces. RecordResult consults this to drop intermediate-artifact inputs (*.mojom-shared.h etc.).
- L137 _private member_ `UnorderedSet<TString> m_outputKeys;`
- L139 _private member_ `u64 m_buildStart = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Ninja/Public/UbaNinjaBuild.h` (Public)


#### struct `uba::NinjaExitPayload`  
`struct NinjaExitPayload`  
_L21-27_
- desc: Per-process payload attached via ProcessStartInfo::userData. Pass 2 heap-allocates; the caller-supplied exitedFunc owns and deletes it.
- L23 _public member_ `void* ctx = nullptr;` — NinjaParseState::exitContext
- L24 _public member_ `u64 cmdHash = 0;` — pre-rsp-substitution
- L25 _public member_ `bool restat = false;` — restat=1 or phony_output=1
- L26 _public member_ `TString primaryOut;` — abs path of edge.outputs[0]

#### struct `uba::NinjaParseState`  
`struct NinjaParseState`  
_L29-42_
- L31 _public member_ `Vector<u32> outputToEdge;`
- L32 _public member_ `Vector<u8> edgesToBuildFlags;`
- L33 _public member_ `Vector<u32> edgeToProcessIndex;`
- L34 _public member_ `Vector<u8> wantedOutputs;`
- L35 _public member_ `u32 phonyId = 0;`
- L36 _public member_ `bool wantAll = false;`
- L40 _public member_ `ProcessStartInfo::ExitedCallback* exitCallback = nullptr;` — Pass 2 wires exitCallback into ProcessStartInfo::exitedFunc and stores exitContext in each allocated NinjaExitPayload::ctx.
- L41 _public member_ `void* exitContext = nullptr;`

#### struct `uba::EnqueueCommandsContext`  
`struct EnqueueCommandsContext`  
_L53-88_
- L55 _public member_ `LoggerWithWriter& logger;`
- L56 _public member_ `NinjaParser& parser;`
- L57 _public member_ `Scheduler& scheduler;`
- L58 _public member_ `NinjaParseState& state;`
- L59 _public member_ `NinjaLogIndex& logIndex;`
- L61 _public member_ `StringView workingDir;`
- L63 _public member_ `bool rebuild;`
- L64 _public member_ `bool cleanOnly;`
- L65 _public member_ `bool noShowIncludes;`
- L66 _public member_ `bool checkUpToDate;`
- L68 _public member_ `bool verbose;`
- L69 _public member_ `bool dryRun;`
- L70 _public member_ `const tchar* yamlFile;`
- L72 _public member_ `u32 cacheBucketId;`
- L73 _public member_ `bool forceRemote;`
- L74 _public member_ `bool toolCommands;`
- L76 _public member_ `const tchar* ninjaFile;`
- L78 _public member_ `bool logIndexLoaded;`
- L80 _public member_ `u32 maxEdges = ~0u;`
- L81 _public member_ `u32 skipEdges = 0;`
- L83 _public member_ `const tchar* depsDumpFile = nullptr;`
- L87 _public member_ `class NinjaDepsLog* depsLog = nullptr;` — When set, every selected edge's outputs + implicitOutputs get registered into the cross-edge written-set at parse time.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`
- L17 _prototype_ `void ResolveNinjaDir(StringBufferBase& out, const tchar* ninjaFile, StringView workingDir);` (scope `uba`) — Absolute directory of the ninja file (trailing sep). Falls back to workingDir.
- L49 _prototype_ `bool ParseNinjaFile(LoggerWithWriter& logger, NinjaParser& parser, const tchar* ninjaFile, const Vector<TString>& specifiedTargets, NinjaParseState& outState, const tchar* buildRoot = nullptr);` (scope `uba`) — Phase 1: intern target IDs, register edge-parsed callback, parse the ninja file. Safe to run on a background thread. `buildRoot` is the anchor for relative paths inside the file (ninja's cwd-at-invocation / `-C dir`). Null defaults to the ninja file's own dir, only correct when those coincide (`-C out/Default` for chromium/llvm).
- L94 _prototype_ `bool EnqueueCommands(const EnqueueCommandsContext& context);` (scope `uba`) — Phase 2: BFS target selection, output cleaning, weight computation, scheduler enqueue. checkUpToDate=false: skip mtime check, enqueue every needed edge. verbose: print `[N/total] <command>` per edge (matches `ninja -v`). toolCommands: mimics `ninja -t commands` then returns without scheduling.

### `Source/Programs/UnrealBuildAccelerator/Ninja/Public/UbaNinjaParser.h` (Public)


#### struct `uba::NinjaPool`  
`struct NinjaPool`  
_L14-18_
- L16 _public member_ `u32 name = StringId_Empty;`
- L17 _public member_ `u32 depth = 0;`

#### struct `uba::NinjaRule`  
`struct NinjaRule`  
_L20-32_
- L22 _public member_ `u32 name = StringId_Empty;`
- L23 _public member_ `u32 command = StringId_Empty;`
- L24 _public member_ `u32 description = StringId_Empty;`
- L25 _public member_ `u32 depfile = StringId_Empty;`
- L26 _public member_ `u32 deps = StringId_Empty;` — "gcc", "msvc", or empty
- L27 _public member_ `u32 rspfile = StringId_Empty;`
- L28 _public member_ `u32 rspfile_content = StringId_Empty;`
- L29 _public member_ `u32 pool = StringId_Empty;`
- L30 _public member_ `bool restat = false;`
- L31 _public member_ `bool generator = false;`

#### struct `uba::TokenSpan`  
`struct TokenSpan`  
_L36-47_
- desc: Span into NinjaParser's bump-allocated u32 token arena. Arena never reallocates, so pointers are stable for the parser's lifetime.
- L38 _public member_ `const u32* tokens = nullptr;`
- L39 _public member_ `u32 count = 0;`
- L41 _public function_ `bool empty() const`
- L42 _public function_ `u32 size() const`
- L43 _public function_ `const u32& operator[](u32 i) const`
- L44 _public function_ `const u32* data() const`
- L45 _public function_ `const u32* begin() const`
- L46 _public function_ `const u32* end() const`

#### struct `uba::NinjaBuildEdge`  
`struct NinjaBuildEdge`  
_L49-70_
- L51 _public prototype_ `NinjaBuildEdge() = default;`
- L52 _public prototype_ `NinjaBuildEdge(NinjaBuildEdge&&) = default;`
- L55 _public member_ `TokenSpan outputs;` — Token lists back into NinjaParser's token arena and are filled sequentially per edge — each list is a contiguous arena range.
- L56 _public member_ `TokenSpan implicitOutputs;` — after `|` on output side
- L57 _public member_ `TokenSpan inputs;`
- L58 _public member_ `TokenSpan implicitDeps;` — after `|` on input side
- L59 _public member_ `TokenSpan orderOnlyDeps;` — after `||` on input side
- L62 _public member_ `TokenSpan validations;` — AOSP extension `|@ <paths>`: validations run as a side effect but don't block consumers. Stock ninja files never set this.
- L63 _public member_ `u32 ruleName = StringId_Empty;`
- L64 _public member_ `UnorderedMap<u32, u32> variables;` — edge-specific overrides (name id -> value id)
- L65 _public member_ `u32 edgeIndex = ~0u;`
- L66 _public member_ `u32 scopeId = 0;` — 0 = main/global, >0 = subninja
- L69 _public member_ `bool phonyOutput = false;` — AOSP extension: `phony_output = true` marks virtual outputs not on disk. Treated like restat for freshness; stat-existence skipped.

#### struct `uba::EdgeSpecialVars`  
`struct EdgeSpecialVars`  
_L75-80_
- desc: Pre-expanded $in / $out / $rspfile views for ExpandVariables. O(1) substitution, skips interning the expanded paths. data == nullptr means "not set; fall through to normal var lookup".
- L77 _public member_ `CharStringView in;`
- L78 _public member_ `CharStringView out;`
- L79 _public member_ `CharStringView rspfile;`

#### struct `uba::ParseOutputs`  
`struct ParseOutputs`  
_L89-95_
- desc: Output destinations for ParseRule/Build/Pool/Default. Phase 1: parser member vectors. Phase 2: thread-local, merged later.
- L91 _public member_ `Vector<NinjaBuildEdge>* edges = nullptr;`
- L92 _public member_ `Vector<NinjaRule>* rules = nullptr;`
- L93 _public member_ `Vector<NinjaPool>* pools = nullptr;`
- L94 _public member_ `Vector<u32>* defaults = nullptr;`

#### struct `uba::SubninjaWork`  
`struct SubninjaWork`  
_L97-102_
- L99 _public member_ `TString filename;`
- L100 _public member_ `u32 scopeId = 0;`
- L101 _public member_ `u32 parentScopeId = 0;`

#### struct `uba::SubninjaQueueRef`  
`struct SubninjaQueueRef`  
_L107-112_
- desc: Shared work-stealing queue for parallel parse. Workers pop under `lock`; nested subninjas re-push so idle workers can claim them. Phase 1 (single-threaded): lock + outstanding null; just push_back.
- L109 _public member_ `Vector<SubninjaWork>* queue = nullptr;`
- L110 _public member_ `Futex* lock = nullptr;`
- L111 _public member_ `std::atomic<u32>* outstanding = nullptr;`

#### class `uba::NinjaParser`  
`class NinjaParser`  
_L114-241_
- L117 _public prototype_ `NinjaParser(MemoryBlock& memoryBlock);`
- L118 _public prototype_ `~NinjaParser();`
- L124 _public prototype_ `bool Parse(Logger& logger, const tchar* filename, const tchar* buildRoot = nullptr);` — `buildRoot` anchors subninja/include resolution (ninja's cwd-at-invocation or `-C dir`). Null defaults to the file's own dir, only correct when they coincide (`-C out/Default` for chromium/llvm; wrong for Android `-f out/combined.ninja` from android root).
- L126 _public function_ `void SetEdgeParsedCallback(EdgeParsedCallback callback, void* userData)`
- L132 _public function_ `const Vector<NinjaRule>& GetRules() const`
- L133 _public function_ `const Vector<NinjaBuildEdge>& GetEdges() const`
- L134 _public function_ `const UnorderedMap<u32, u32>& GetVariables() const`
- L135 _public function_ `const Vector<u32>& GetDefaults() const`
- L136 _public function_ `const UnorderedMap<u32, u32>& GetRuleMap() const`
- L137 _public function_ `const Vector<NinjaPool>& GetPools() const`
- L138 _public function_ `const StringPool& GetStringPool() const`
- L141 _public prototype_ `void ExpandCommand(const NinjaBuildEdge& edge, Vector<char>& out, Vector<char>& tempBuffer);` — Expands directly into `out` (no per-call allocations).
- L142 _public prototype_ `void ExpandVariables(const char* str, u32 len, Vector<char>& out, const UnorderedMap<u32, u32>* edgeVars = nullptr, u32 scopeId = 0, u32 skipVarId = StringId_Empty, bool shellEscapeDollarSpace = false, const EdgeSpecialVars* specials = nullptr);`
- L144 _public function_ `u64 GetParseTimeMs() const`
- L145 _public function_ `u32 GetLineCount() const`
- L170 _private prototype_ `bool ParseFile(Logger& logger, const tchar* filename, u32 scopeId, ParseOutputs outputs, SubninjaQueueRef subninja, MemoryBlock* tokenArena = nullptr);`
- L173 _private prototype_ `bool ParseImpl(ParseContext& ctx);`
- L174 _private prototype_ `bool ParseRule(ParseContext& ctx, const char* line, u32 lineLen);`
- L175 _private prototype_ `bool ParseBuild(ParseContext& ctx, const char* line, u32 lineLen);`
- L176 _private prototype_ `bool ParseVariable(ParseContext& ctx, const char* line, u32 lineLen);`
- L177 _private prototype_ `bool ParseDefault(ParseContext& ctx, const char* line, u32 lineLen);`
- L178 _private prototype_ `bool ParsePool(ParseContext& ctx, const char* line, u32 lineLen);`
- L179 _private prototype_ `bool ParseInclude(ParseContext& ctx, const char* line, u32 lineLen);`
- L180 _private prototype_ `bool ParseSubninja(ParseContext& ctx, const char* line, u32 lineLen);`
- L183 _private prototype_ `u32 AllocateScopeId(u32 parentScopeId);` — Thread-safe (m_scopeAllocLock); returns 1-based scope id.
- L185 _private prototype_ `bool ReadLine(ParseContext& ctx, const char*& outLine, u32& outLen);`
- L186 _private prototype_ `bool ReadIndentedLines(ParseContext& ctx, UnorderedMap<u32, u32>& vars);`
- L187 _private prototype_ `void SkipWhitespace(const char*& p, const char* end);`
- L188 _private prototype_ `void SplitPaths(ParseContext& ctx, const char* str, u32 len, Vector<u32>& out);`
- L191 _private member_ `MemoryBlock& m_memoryBlock;` — Caller-owned shared MemoryBlock.
- L193 _private member_ `StringPool m_stringPool;`
- L197 _private member_ `MemoryBlock m_tokenArena;` — Bump arena for edge-token spans. 1 GB virtual reserve, pages commit lazily; never reallocates so TokenSpan pointers are stable.
- L199 _private member_ `Vector<NinjaRule> m_rules;`
- L200 _private member_ `Vector<NinjaBuildEdge> m_edges;`
- L201 _private member_ `Vector<NinjaPool> m_pools;`
- L202 _private member_ `UnorderedMap<u32, u32> m_globalVars;` — scope 0
- L206 _private member_ `Vector<UnorderedMap<u32, u32>> m_scopeVars;` — File-scoped vars per subninja (indexed by scopeId-1). Subninja scope reads parent vars but writes only its own. m_scopeParents[i] is the parent of scope i+1; ExpandVariables walks up the chain.
- L207 _private member_ `Vector<u32> m_scopeParents;`
- L208 _private member_ `Vector<u32> m_defaults;`
- L209 _private member_ `UnorderedMap<u32, u32> m_ruleMap;`
- L210 _private member_ `UnorderedMap<u32, u32> m_poolMap;`
- L213 _private member_ `Futex m_scopeAllocLock;` — Guards push_back to m_scopeVars / m_scopeParents in phase 2.
- L217 _private member_ `Vector<MemoryBlock*> m_workerArenas;` — Per-worker token arenas; owned because TokenSpan pointers in m_edges reference them and must outlive worker threads.
- L220 _private member_ `u32 m_commandId;` — Pre-interned ids for common variable names — skips per-call hash lookup.
- L221 _private member_ `u32 m_descriptionId;`
- L222 _private member_ `u32 m_depfileId;`
- L223 _private member_ `u32 m_depsId;`
- L224 _private member_ `u32 m_rspfileId;`
- L225 _private member_ `u32 m_rspfile_contentId;`
- L226 _private member_ `u32 m_poolId;`
- L227 _private member_ `u32 m_restatId;`
- L228 _private member_ `u32 m_generatorId;`
- L229 _private member_ `u32 m_depthId;`
- L230 _private member_ `u32 m_inId;`
- L231 _private member_ `u32 m_outId;`
- L232 _private member_ `u32 m_phonyOutputId;` — AOSP edge variable
- L234 _private member_ `EdgeParsedCallback m_edgeParsedCallback = nullptr;`
- L235 _private member_ `void* m_edgeCallbackUserData = nullptr;`
- L237 _private member_ `u64 m_parseTimeMs = 0;`
- L239 _private member_ `std::atomic<u32> m_lineCount { 0 };` — Atomic — phase 2 workers add concurrently.
- L240 _private member_ `u32 m_buildRootDirId = StringId_Empty;` — anchor for subninja relative paths

#### struct `uba::NinjaParser::ParseContext`  
`struct ParseContext`  
_L148-168_
- L150 _public member_ `Logger& logger;`
- L151 _public member_ `const char* data = nullptr;`
- L152 _public member_ `u64 size = 0;`
- L153 _public member_ `u64 pos = 0;`
- L154 _public member_ `u32 line = 1;`
- L155 _public member_ `u32 workingDirId = 0;`
- L156 _public member_ `u32 scopeId = 0;`
- L157 _public member_ `Vector<char> continuationBuf;`
- L159 _public member_ `Vector<char> tokenBuffer;` — Per-thread token assembly scratch for ParseBuild / SplitPaths.
- L161 _public member_ `ParseOutputs outputs;` — ParseRule/Build/Pool/Default outputs; merged from worker-local in phase 2.
- L163 _public member_ `SubninjaQueueRef subninja;` — Shared subninja queue. queue==nullptr means inline recurse (unused).
- L167 _public member_ `MemoryBlock* tokenArena = nullptr;` — Per-thread token arena. Phase 1: parser's m_tokenArena. Phase 2: per-worker arena from m_workerArenas, kept alive by parser so TokenSpan pointers in m_edges remain valid.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L85 _typedef_ `using EdgeParsedCallback = void(*)(void* userData, u32 edgeIndex, const NinjaBuildEdge& edge);` (scope `uba`) — Edge-parsed callback. In parallel-parse mode the callback fires during the post-parse merge, not during parse — but every edge is delivered before Parse() returns.

### `Source/Programs/UnrealBuildAccelerator/Ninja/Public/UbaNinjaStringPool.h` (Public)


#### struct `uba::CharStringView`  
`struct CharStringView`  
_L11-25_
- L13 _public member_ `const char* data = nullptr;`
- L14 _public member_ `u32 length = 0;`
- L16 _public prototype_ `CharStringView() = default;`
- L17 _public function_ `CharStringView(const char* str, u32 len) : data(str), length(len)`
- L19 _public function_ `bool operator==(const CharStringView& other) const`

#### class `uba::StringPool`  
`class StringPool`  
_L32-101_
- desc: 64 hash shards keyed by `hash & 63` (Swiss-table style + Futex per shard). IDs are dense (1..N) from a global counter; ID 0 = empty. m_strings is pre-sized once (Reserve / ctor) and never reallocated, so concurrent Intern + GetString are safe — Intern publishes the id only after the slot is written; per-shard mutex is the release barrier.
- L35 _public prototype_ `StringPool(MemoryBlock& memoryBlock);`
- L38 _public prototype_ `u32 Intern(const char* str, u32 length);` — Thread-safe; locks at most one shard mutex.
- L39 _public function_ `u32 Intern(const CharStringView& view)`
- L40 _public function_ `u32 InternThreadSafe(const char* str, u32 length)`
- L42 _public function_ `inline CharStringView GetString(u32 id) const`
- L51 _public function_ `inline const char* GetCStr(u32 id) const`
- L59 _public prototype_ `void Reserve(u32 capacity);` — MUST be called before any concurrent Intern — resizes m_strings.
- L62 _public function_ `inline u32 Size() const` — Number of interned strings (including ID 0).
- L64 _public member_ `static constexpr u32 ShardBits = 6;`
- L65 _public member_ `static constexpr u32 ShardCount = 1u << ShardBits;` — 64
- L66 _public member_ `static constexpr u32 ShardMask = ShardCount - 1;`
- L77 _private member_ `static constexpr u8 kEmpty = 0x80;` — Swiss Tables style: ctrl bytes + ids in parallel arrays.
- L78 _private member_ `static constexpr u8 kDeleted = 0xFF;`
- L89 _private member_ `MemoryBlock& m_memoryBlock;`
- L90 _private member_ `Shard m_shards[ShardCount];`
- L93 _private member_ `Vector<StringEntry> m_strings;` — Pre-sized; never grown under concurrent Intern. Index 0 = empty placeholder.
- L94 _private member_ `std::atomic<u32> m_nextId { 1 };`
- L96 _private prototype_ `static u32 HashString(const char* data, u32 length);`
- L98 _private prototype_ `void RehashShard(Shard& shard, u32 newSize);` — Non-static — read m_strings on grow. Caller holds the shard mutex.
- L99 _private prototype_ `u32 FindSlot(const Shard& shard, u32 hash, const char* str, u32 length) const;`
- L100 _private prototype_ `u32 InternImplLocked(Shard& shard, const char* str, u32 length, u32 hash);`

#### struct `uba::StringPool::StringEntry`  
`struct StringEntry`  
_L69-74_
- L71 _public member_ `const char* data;`
- L72 _public member_ `u32 length;`
- L73 _public member_ `u32 hash;`

#### struct `uba::StringPool::Shard`  
`struct Shard`  
_L80-87_
- L82 _public member_ `Vector<u8> ctrl;`
- L83 _public member_ `Vector<u32> ids;`
- L84 _public member_ `u32 hashMask = 0;`
- L85 _public member_ `u32 hashCount = 0;`
- L86 _public member_ `Futex mutex;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L103 _variable_ `static constexpr u32 StringId_Empty = 0;` (scope `uba`)
