# Plugins / ShaderAuditCore

- module root: `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore`
- headers: 18; symbols: 538
- symbol kinds: class=18, delegate=6, enum=6, enumerator=28, function=46, member=228, namespace=5, prototype=182, struct=17, typedef=1, variable=1
- PrivateDependencyModuleNames: ApplicationCore, DesktopPlatform, InputCore, RHI, RenderCore, Slate, SlateCore, ToolWidgets, TreeMap, xxhash
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/NasSHKScanner.h` (Private)


#### struct `FNasSHKEntry`  
`struct FNasSHKEntry`  
_L14-47_
- desc: Parsed representation of a NAS SHK filename. Filename format: {Branch}-{Project}-{CL}-{TargetType}-{LibraryName}-{FormatName}.shk Example: ++Project+Release-1.00-GameName-12345678-WindowsClient-GameName-PCD3D_SM6.shk
- L17 _public member_ `FString FullPath;` — Full path to the SHK file (on NAS or local cache).
- L20 _public member_ `FString Branch;` — Branch name, e.g. "++Project+Release-1.00".
- L23 _public member_ `int32 CL = 0;` — Changelist number.
- L26 _public member_ `FString TargetType;` — Target type, e.g. "WindowsClient".
- L29 _public member_ `FString LibraryName;` — Library name, e.g. "GameName".
- L32 _public member_ `FString FormatName;` — Shader format, e.g. "PCD3D_SM6", "SF_METAL".
- L35 _public member_ `bool bIsCached = false;` — True if this entry was found in the local cache (not the NAS).
- L46 _public prototype_ `static bool Parse(const FString& Filename, FNasSHKEntry& OutEntry);` — Try to parse a NAS SHK filename into its components. Parses right-to-left: FormatName and LibraryName are the last two tokens, CL is the rightmost pure-integer token (digits only, len >= 5), TargetType spans between CL and LibraryName, Branch is everything before Project. @param Filename   Just the filename (no directory), e.g. "++Project+Release-1.00-GameName-12345678-WindowsClient-GameName-PCD3D_SM6.shk" @param OutEntry   Populated on success. @return true if parsed successfully.

#### struct `FNasBuildGroup`  
`struct FNasBuildGroup`  
_L55-110_
- desc: A group of SHK entries sharing the same Branch + CL. Represents one build's worth of shader data across all platforms/formats. Each unique format (TargetType|FormatName) has a FSessionFileInventory populated with SHK paths and sizes at scan time (bytecode discovered on expand).
- L57 _public member_ `FString Branch;`
- L58 _public member_ `int32 CL = 0;`
- L61 _public function_ `static FString MakeGroupKey(const FString& InBranch, int32 InCL)` — Build the canonical map key: "Branch|CL".
- L67 _public function_ `FString GetGroupKey() const` — Convenience: key for this instance.
- L70 _public function_ `static FString MakeFormatKey(const FString& InTargetType, const FString& InFormatName, bool bIsCached)` — Build a format key with source suffix: "TargetType|FormatName|Local" or "TargetType|FormatName|NAS".
- L76 _public function_ `static bool IsFormatCached(const FString& FormatKey)` — True if the format key indicates a locally cached entry ("|Local" suffix).
- L82 _public function_ `static FString GetBaseFormatKey(const FString& FormatKey)` — Strip the source suffix to get the base format key: "TargetType|FormatName".
- L97 _public member_ `TMap<FString, FSessionFileInventory> Formats;` — Per-format inventories. Key = "TargetType|FormatName|Local" or "TargetType|FormatName|NAS". Populated at scan time with SHKFiles + SHKTotalBytes. BytecodeFiles populated later when the group is expanded.
- L100 _public prototype_ `int32 GetNumCachedFormats() const;` — Number of formats in this group that are locally cached. Compare with GetNumFormats() for full status.
- L103 _public prototype_ `int32 GetNumFormats() const;` — Number of unique base formats (ignoring Local/NAS source).
- L109 _public prototype_ `TMap<FString, FString> ResolveBestFormats() const;` — Resolve the best format key per base key (Local preferred over NAS). Returns a map of BaseKey -> best full FormatKey.

#### struct `FNasScanResult`  
`struct FNasScanResult`  
_L113-129_
- desc: Result of a NAS scan operation.
- L116 _public member_ `TArray<FNasBuildGroup> Groups;` — All discovered build groups, sorted by CL descending (newest first).
- L119 _public member_ `TArray<FString> Branches;` — Unique branch names found.
- L122 _public member_ `FString ErrorMessage;` — Error message if the scan failed. Empty on success.
- L125 _public member_ `int32 FilesScanned = 0;` — Total files visited during scan (including skipped/unparseable ones).
- L128 _public member_ `int32 FilesMatched = 0;` — Files that matched the branch prefix and were successfully parsed.

#### class `FNasSHKScanner`  
`class FNasSHKScanner`  
_L135-197_
- desc: Scans NAS and local cache directories for SHK files, parses filenames, and groups them by Branch + CL.
- L142 _public prototype_ `static FString GetNasLocationFromConfig();` — Read the SHKFilesLocation from engine config. [/Script/Engine.ShaderCompilerStats] SHKFilesLocation=... (DefaultGame.ini)
- L148 _public prototype_ `static FString GetBuildRootFromConfig();` — Read the build root path from ShaderAudit.ini. [NASBrowser] BuildRoot=... (e.g. \\server\share\Builds\Project)
- L152 _public prototype_ `static FString GetDefaultCacheDir();` — Returns {Project}/Saved/ShaderAuditCache/
- L155 _public prototype_ `static FString GetRelativeCacheSubDir(const FNasSHKEntry& Entry);` — Returns the relative cache subdirectory: {Branch}-CL-{CL}/{TargetType}/Metadata
- L166 _public prototype_ `static FNasScanResult ScanDirectory( const FString& Directory, bool bIsCached, TFunction<void(const FNasScanResult&)> OnProgress = nullptr, const std::atomic<bool>* bCancelFlag = nullptr);` — Scan a directory for .shk files, parse them, and group by Branch+CL. Uses IterateDirectory for streaming enumeration. @param Directory       The directory to scan. @param bIsCached       If true, marks all entries as cached. @param OnProgress      Called periodically with incremental results (may be called from any thread). @return Grouped scan results.
- L180 _public prototype_ `static FNasScanResult ScanLocalCache(const FString& CacheDir);` — Scan a local cache directory recursively for ShaderStableInfo-*.shk files. Extracts Branch/CL/TargetType from the directory path structure: {CacheDir}/{Branch}-CL-{CL}/{TargetType}/Metadata/PipelineCaches/ShaderStableInfo-{Lib}-{Format}.shk @param CacheDir   Root cache directory to scan recursively. @return Grouped scan results with bIsCached=true.
- L190 _public prototype_ `static void ScanAsync( const FString& NasDir, const FString& CacheDir, TFunction<void(FNasScanResult)> OnLocalComplete, TFunction<void(FNasScanResult)> OnNasProgress, TFunction<void(FNasScanResult)> OnNasComplete, TSharedPtr<std::atomic<bool>> CancelToken = nullptr);` — Launch async scans of both local cache and NAS directories. Uses branch prefix filtering and posts incremental NAS results to the game thread. @param OnLocalComplete   Called on game thread when local scan finishes. @param OnNasProgress     Called on game thread as NAS entries are discovered (incremental). @param OnNasComplete     Called on game thread when NAS scan finishes.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/ShaderStatsModel.h` (Private)


#### class `IShaderTableModel`  
`class IShaderTableModel`  
_L10-18_
- L13 _public function_ `virtual ~IShaderTableModel()`
- L15 _public prototype_ `virtual TConstArrayView<FName> GetRows() const = 0;`
- L16 _public prototype_ `virtual TConstArrayView<FName> GetColumns() const = 0;`
- L17 _public prototype_ `virtual TSharedRef<SWidget> GetCellWidget(FName Row, FName Column) const = 0;`

#### class `FMaterialDomainByShaderFrequencyModel`  
`class FMaterialDomainByShaderFrequencyModel : public IShaderTableModel`  
_L21-36_
- inherits: `IShaderTableModel`
- L24 _public prototype_ `FMaterialDomainByShaderFrequencyModel(TSharedPtr<FShaderAuditSession> InSession);`
- L26 _public prototype_ `TConstArrayView<FName> GetRows() const override;`
- L27 _public prototype_ `TConstArrayView<FName> GetColumns() const override;`
- L28 _public prototype_ `TSharedRef<SWidget> GetCellWidget(FName Row, FName Column) const override;`
- L31 _private member_ `TSharedPtr<FShaderAuditSession> Session;`
- L32 _private member_ `TArray<FName> MaterialDomains;`
- L33 _private member_ `TArray<FName> ShaderFrequencies;`
- L34 _private member_ `TMap<FName, TMap<FName, int32>> Counts;` — [Domain][Frequency] -> count
- L35 _private member_ `TMap<FName, TMap<FName, uint64>> Sizes;` — [Domain][Frequency] -> bytes

#### class `FVertexFactoryByShaderFrequencyModel`  
`class FVertexFactoryByShaderFrequencyModel : public IShaderTableModel`  
_L38-53_
- inherits: `IShaderTableModel`
- L41 _public prototype_ `FVertexFactoryByShaderFrequencyModel(TSharedPtr<FShaderAuditSession> InSession);`
- L43 _public prototype_ `TConstArrayView<FName> GetRows() const override;`
- L44 _public prototype_ `TConstArrayView<FName> GetColumns() const override;`
- L45 _public prototype_ `TSharedRef<SWidget> GetCellWidget(FName Row, FName Column) const override;`
- L48 _private member_ `TSharedPtr<FShaderAuditSession> Session;`
- L49 _private member_ `TArray<FName> VertexFactories;`
- L50 _private member_ `TArray<FName> ShaderFrequencies;`
- L51 _private member_ `TMap<FName, TMap<FName, int32>> Counts;` — [VFType][Frequency] -> count
- L52 _private member_ `TMap<FName, TMap<FName, uint64>> Sizes;` — [VFType][Frequency] -> bytes

#### class `FVertexFactoryByShaderTypeModel`  
`class FVertexFactoryByShaderTypeModel : public IShaderTableModel`  
_L55-70_
- inherits: `IShaderTableModel`
- L58 _public prototype_ `FVertexFactoryByShaderTypeModel(TSharedPtr<FShaderAuditSession> InSession);`
- L60 _public prototype_ `TConstArrayView<FName> GetRows() const override;`
- L61 _public prototype_ `TConstArrayView<FName> GetColumns() const override;`
- L62 _public prototype_ `TSharedRef<SWidget> GetCellWidget(FName Row, FName Column) const override;`
- L65 _private member_ `TSharedPtr<FShaderAuditSession> Session;`
- L66 _private member_ `TArray<FName> ComboList;` — "VFType / ShaderType" combined names
- L67 _private member_ `TArray<FName> Columns;`
- L68 _private member_ `TMap<FName, int32> CountPerCombo;`
- L69 _private member_ `TMap<FName, uint64> SizePerCombo;`

#### class `FMaterialStatModel`  
`class FMaterialStatModel : public IShaderTableModel`  
_L72-88_
- inherits: `IShaderTableModel`
- L75 _public prototype_ `FMaterialStatModel(TSharedPtr<FShaderAuditSession> InSession);`
- L77 _public prototype_ `TConstArrayView<FName> GetRows() const override;`
- L78 _public prototype_ `TConstArrayView<FName> GetColumns() const override;`
- L79 _public prototype_ `TSharedRef<SWidget> GetCellWidget(FName Row, FName Column) const override;`
- L82 _private member_ `TSharedPtr<FShaderAuditSession> Session;`
- L83 _private member_ `TArray<FName> MaterialList;`
- L84 _private member_ `TArray<FName> Columns;`
- L85 _private member_ `TMap<FName, int32> ShaderCountPerMaterial;`
- L86 _private member_ `TMap<FName, uint64> SizePerMaterial;`
- L87 _private member_ `TMap<FName, FName> MaterialDisplayNames;` — full-path key -> leaf-name label

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/Widgets/SInspectShaderSessionWidget.h` (Private)


#### class `SInspectShaderSessionWidget`  
`class SInspectShaderSessionWidget : public SCompoundWidget`  
_L10-23_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SInspectShaderSessionWidget)`
- L14 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FShaderAuditSession>, Session) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L18 _public prototype_ `void SetSession(TSharedPtr<FShaderAuditSession> InSession);`
- L21 _private prototype_ `void RebuildFromSession();`
- L22 _private member_ `TSharedPtr<FShaderAuditSession> Session;`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/Widgets/SNasSHKBrowserPanel.h` (Private)


#### struct `FNasBrowserItem`  
`struct FNasBrowserItem`  
_L22-66_
- desc: A row item in the browser list. Can be either a group header (CL level) or a format entry (child of a group).
- L26 _public member_ `EType Type = EType::GroupHeader;`
- L29 _public member_ `TSharedPtr<FNasBuildGroup> Group;` — The build group data.
- L32 _public member_ `FString FormatKey;` — For FormatEntry: the unique format identity (TargetType|FormatName).
- L35 _public function_ `const FSessionFileInventory* GetInventory() const` — Get the inventory for this format entry. Returns nullptr for headers or if not found.
- L45 _public function_ `bool IsCached() const` — Is this format cached (local paths)? Derived from format key suffix.
- L50 _public function_ `static TSharedPtr<FNasBrowserItem> MakeGroupHeader(TSharedPtr<FNasBuildGroup> InGroup)`
- L58 _public function_ `static TSharedPtr<FNasBrowserItem> MakeFormatEntry(TSharedPtr<FNasBuildGroup> InGroup, const FString& InFormatKey)`

#### enum `FNasBrowserItem::EType`  
`enum class EType : uint8`  
_L24-24_
- L24 _public enumerator_ `enum class EType : uint8 { GroupHeader, FormatEntry }; EType Type = EType::GroupHeader; TSharedPtr<FNasBuildGroup> Group;`
- L24 _public enumerator_ `enum class EType : uint8 { GroupHeader, FormatEntry }; EType Type = EType::GroupHeader; TSharedPtr<FNasBuildGroup> Group;`

#### enum `EScanFlags`  
`enum class EScanFlags : uint8`  
_L69-78_
- desc: Bit flags controlling which sources StartScan() queries.
- L71 _public enumerator_ `None = 0`
- L73 _public enumerator_ `Local = 1 << 0` — Scan the local cache directory.
- L75 _public enumerator_ `NAS = 1 << 1` — Scan the remote NAS directory.
- L77 _public enumerator_ `All = Local | NAS` — Scan everything.

#### class `SNasSHKBrowserPanel`  
`class SNasSHKBrowserPanel : public SCompoundWidget`  
_L101-232_
- inherits: `SCompoundWidget`
- desc: Browser panel for discovering SHK files on NAS and local cache. Layout: Local: /path/to/cache NAS:   \\server\share\path          [Refresh] Branch: [dropdown]           [Clear Cache] [Browse...] | CL       | Formats              | Status     | | 53150985 | v  3 formats         | Cached [X] |  <- group header, click to expand |          |   PCD3D_SM6          | [x] Cached |  <- format entry with checkbox |          |   PCD3D_ES31         | [x] NAS    | | 53150111 | >  2 formats         | NAS        |  <- collapsed [Scanning NAS... =========>   ]   (progress bar) [Cancel]                            [Load]
- L104 _public function_ `SLATE_BEGIN_ARGS(SNasSHKBrowserPanel)`
- L105 _public prototype_ `SLATE_EVENT(FOnSessionsLoaded, OnSessionsLoaded) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L112 _public function_ `bool IsFormatPending(const FString& GroupKey, const FString& FormatKey) const` — True if bytecode discovery is in progress for this group+format.
- L121 _private prototype_ `void StartScan(EScanFlags Flags = EScanFlags::All);` — --- Scanning ---
- L122 _private prototype_ `void CancelScan();`
- L124 _private prototype_ `void ResetScanState();` — Clear all scan state (groups, branches, expansion, pending). Call before StartScan for a full refresh.
- L130 _private prototype_ `void RefreshLocalCache(const FString& GroupKey = FString());` — Refresh local cache state. Removes cached formats from the specified scope, then kicks a local-only scan via StartScan(EScanFlags::Local). On completion, re-fires bytecode discovery for expanded groups in scope.
- L131 _private prototype_ `void OnLocalScanComplete(FNasScanResult Result);`
- L132 _private prototype_ `void OnNasScanProgress(FNasScanResult PartialResult);`
- L133 _private prototype_ `void OnNasScanComplete(FNasScanResult Result);`
- L138 _private prototype_ `void MergeScanResult(const FNasScanResult& InResult);` — Merge a scan result into the live Groups array. Scanner data is always generation 0 and can never beat enriched data (gen >= 1 from Gather).
- L146 _private prototype_ `bool TryMergeInventory(const FString& GroupKey, const FString& FormatKey, FSessionFileInventory&& Inventory, int32 Generation);` — Try to store an inventory if its generation is high enough. Higher generation always wins. Returns true if stored. Both MergeScanResult (scanner data) and ToggleGroupExpanded (Gather data) use this single entry point so merge logic is centralized.
- L148 _private prototype_ `void RebuildFilteredItems();`
- L149 _private prototype_ `void UpdateBranchList();`
- L150 _private prototype_ `void UpdateStatusText();`
- L153 _private prototype_ `void ToggleGroupExpanded(const FString& GroupKey);` — --- Expand/collapse ---
- L156 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FNasBrowserItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — --- UI callbacks ---
- L157 _private prototype_ `void OnBranchSelected(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);`
- L158 _private prototype_ `void OnLoadEntry(const FString& GroupKey, const FString& FormatKey);`
- L159 _private prototype_ `void OnClearAllCache();`
- L160 _private prototype_ `void OnClearCachedEntry(const FString& Branch, int32 CL, const FString& TargetType);`
- L161 _private prototype_ `void OnBrowseLocal();`
- L163 _private prototype_ `void ConfirmAndClearCache(const FText& Message, TFunction<void()> OnConfirmed, const FString& GroupKeyToRefresh = FString());` — Show confirmation dialog, then execute the clear operation and rescan.
- L166 _private member_ `FString NasDir;` — --- Data ---
- L167 _private member_ `FString CacheDir;`
- L168 _private member_ `FOnSessionsLoaded OnSessionsLoaded;`
- L171 _private member_ `TMap<FString, TSharedPtr<FNasBuildGroup>> Groups;` — Single authoritative map of build groups, keyed by FNasBuildGroup::MakeGroupKey().
- L172 _private member_ `TArray<FString> Branches;`
- L173 _private member_ `bool bNasScanComplete = false;`
- L176 _private member_ `TSharedPtr<std::atomic<bool>> ScanCancelToken;` — Cancellation token for async NAS scan.
- L179 _private member_ `FString CurrentBranchName;` — Branch filter.
- L180 _private member_ `TArray<TSharedPtr<FString>> BranchOptions;`
- L181 _private member_ `TSharedPtr<FString> SelectedBranch;`
- L184 _private member_ `TArray<TSharedPtr<FNasBrowserItem>> DisplayItems;` — Expanded items for the list view.
- L187 _private member_ `TSet<FString> ExpandedGroups;` — Which groups are expanded (keyed by "Branch|CL").
- L199 _private member_ `TMap<FString, int32> FormatStates;` — Per-inventory generation counter with pending flag. Keyed by MakePendingKey(GroupKey, FormatKey). absent/0 = untouched, generation 0 (scanner data) < 0     = Gather in flight (pending); abs(value) = generation > 0     = Gather complete (enriched); value = generation Generation is monotonic: higher abs(value) always wins in TryMergeInventory. Scanner data uses the snapshot generation (typically 0), so it can never beat enriched data (generation >= 1).
- L202 _private function_ `static FString MakePendingKey(const FString& GroupKey, const FString& FormatKey)` — Build a unique pending key from group key and format key.
- L208 _private member_ `FString BuildRoot;` — Build root path for bytecode queries.
- L213 _private member_ `TStaticArray<uint32, NumScanSources> ScanGeneration{};` — Per-source generation counters. Bumped by StartScan() for the sources being scanned, and by ResetScanState() for all sources. Captured in callback lambdas to reject stale callbacks that were already queued on GT before cancellation.
- L217 _private function_ `static int32 ScanFlagIndex(EScanFlags Flag)` — Map a single EScanFlags bit to an array index (0 = Local, 1 = NAS). Flag must be exactly one bit — not None, not a combination.
- L227 _private member_ `TSharedPtr<SListView<TSharedPtr<FNasBrowserItem>>> ListView;` — --- Widgets ---
- L228 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> BranchCombo;`
- L229 _private member_ `TSharedPtr<class STextBlock> NasStatusText;`
- L230 _private member_ `TSharedPtr<class SProgressBar> LocalProgressBar;`
- L231 _private member_ `TSharedPtr<class SProgressBar> NasProgressBar;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE(FOnSessionsLoaded);` — Delegate fired after the panel loads sessions (per-row Load or Browse). The caller should refresh its session UI (e.g. spawn new session tabs).
- L15 _prototype_ `DECLARE_DELEGATE(FOnSessionsLoaded);` — Delegate fired after the panel loads sessions (per-row Load or Browse). The caller should refresh its session UI (e.g. spawn new session tabs).
- L79 _prototype_ `ENUM_CLASS_FLAGS(EScanFlags);`
- L80 _variable_ `static constexpr int32 NumScanSources = FMath::CountBits(static_cast<uint32>(EScanFlags::All));`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/Widgets/SSHKEntryListWidget.h` (Private)


#### class `SSHKEntryListWidget`  
`class SSHKEntryListWidget : public SCompoundWidget`  
_L19-84_
- inherits: `SCompoundWidget`
- desc: Raw SHK entry list -- an spreadsheet view of all StableShaderKeyAndValue entries. Uses SListView for virtualized rendering (only visible rows get widgets). Filtering is powered by FShaderFilterNode / BuildVisibleShaders. Ctrl+C copies selected rows as comma-separated text.
- L22 _public function_ `SLATE_BEGIN_ARGS(SSHKEntryListWidget)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `void SetSession(TSharedPtr<FShaderAuditSession> InSession);` — Set (or change) the active session. Rebuilds the entry list.
- L32 _private prototype_ `void ApplyFilters();` — Rebuild VisibleEntryIndices from ActiveFilters, then refresh the list.
- L35 _private prototype_ `void RebuildFilterTags();` — Rebuild the filter tag pills in the tag bar.
- L38 _private prototype_ `void OnFilterCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when the user presses Enter in the filter box.
- L41 _private prototype_ `void RemoveFilter(int32 Index);` — Remove a filter by index.
- L44 _private prototype_ `void CopySelectedRows();` — Copy selected rows to clipboard as comma-separated text.
- L47 _private prototype_ `bool HasSelection() const;` — True if at least one row is selected.
- L50 _private prototype_ `FString FormatEntryAsCSV(int32 EntryIndex) const;` — Format a single SHK entry as a comma-separated row string.
- L53 _private prototype_ `TSharedRef<class ITableRow> OnGenerateRow(TSharedPtr<int32> Item, const TSharedRef<class STableViewBase>& OwnerTable);` — Row generator callback for SListView.
- L56 _private prototype_ `void GetFilterSuggestions(const FString& Text, TArray<FString>& OutSuggestions);` — Populate autocomplete suggestions for the filter text box.
- L59 _private member_ `TSharedPtr<FShaderAuditSession> Session;` — --- Data ---
- L62 _private member_ `TArray<FName> ColumnIds;` — Column IDs parsed from FStableShaderKeyAndValue::HeaderLine().
- L65 _private member_ `TArray<TSharedPtr<int32>> AllEntryIndices;` — All entry indices (pre-allocated once on SetSession).
- L68 _private member_ `TArray<TSharedPtr<int32>> VisibleEntryIndices;` — Indices into Session->StableShaderKeyAndValueArray for visible (filtered) entries.
- L71 _private member_ `TSharedPtr<SListView<TSharedPtr<int32>>> ListView;` — The list view widget.
- L74 _private member_ `TSharedPtr<class STextBlock> StatusText;` — Status text: "Showing X of Y entries".
- L77 _private member_ `TArray<FShaderFilterNode> ActiveFilters;` — --- Filters ---
- L78 _private member_ `TArray<FString> ActiveFilterStrings;`
- L79 _private member_ `TSharedPtr<class SWrapBox> FilterTagBox;`
- L80 _private member_ `TSharedPtr<class SSearchBox> HashSearchBox;`
- L83 _private member_ `TSharedPtr<class FUICommandList> CommandList;` — Command list for keyboard shortcuts (Ctrl+C).

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/Widgets/SShaderAuditOverviewCard.h` (Private)


#### class `SShaderAuditOverviewCard`  
`class SShaderAuditOverviewCard : public SCompoundWidget`  
_L10-18_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SShaderAuditOverviewCard)`
- L14 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FShaderAuditSession>, Session) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Private/Widgets/SShaderStatSpreadsheet.h` (Private)


#### class `SShaderStatSpreadsheet`  
`class SShaderStatSpreadsheet : public SCompoundWidget`  
_L12-27_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SShaderStatSpreadsheet)`
- L16 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IShaderTableModel>, Model) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _private member_ `TArray<TSharedPtr<FName>> Items;`
- L23 _private member_ `TSharedPtr<IShaderTableModel> Model;`
- L24 _private member_ `TArray<FName> ColumnIds;`
- L26 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FName> InItem, const TSharedRef<STableViewBase>& OwnerTable);`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/IShaderAuditExtension.h` (Public)


#### struct `FShaderAuditExtensionContribution`  
`struct FShaderAuditExtensionContribution`  
_L16-27_
- desc: A single contribution an extension makes to the session view UI. An extension may return multiple contributions (e.g. a toolbar button AND a view tab).
- L20 _public member_ `FText ViewTabLabel;` — If non-empty, a view tab button with this label is added to the toolbar and a corresponding slot is created in the view switcher.
- L23 _public member_ `TFunction<TSharedRef<SWidget>(TSharedPtr<FShaderAuditSession>)> CreateViewWidget;` — Factory for the view tab widget. Required when ViewTabLabel is set.
- L26 _public member_ `TFunction<TSharedRef<SWidget>(TSharedPtr<FShaderAuditSession>)> CreateToolbarWidget;` — Factory for a widget appended to the toolbar. May be null.

#### class `IShaderAuditExtension`  
`class IShaderAuditExtension : public IModularFeature`  
_L42-63_
- inherits: `IModularFeature`
- desc: Extension point for the ShaderAudit session view. Modules implement this interface and register via IModularFeatures to contribute toolbar widgets, view tabs, and session lifecycle behavior to ShaderAudit -- without any compile-time dependency from ShaderAudit to the extension module. Registration: IModularFeatures::Get().RegisterModularFeature(IShaderAuditExtension::FeatureName, this); The session view discovers all registered extensions and integrates their contributions. Late registration (after the view is already constructed) is supported.
- L45 _public member_ `static inline const FName FeatureName = TEXT("Sha`
- L47 _public prototype_ `virtual ~IShaderAuditExtension() = default;`
- L50 _public prototype_ `virtual FName GetExtensionId() const = 0;` — Unique identifier for this extension (used as key in ExtensionData maps).
- L53 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Human-readable name shown in UI (e.g. tooltips).
- L56 _public prototype_ `virtual TArray<FShaderAuditExtensionContribution> GetContributions() const = 0;` — Return the UI contributions this extension makes to each session view.
- L59 _public function_ `virtual void OnSessionLoaded(TSharedPtr<FShaderAuditSession> Session)` — Called when a session finishes loading. Use to auto-attach data, kick off background work, etc.
- L62 _public function_ `virtual void OnSessionClosed(int32 SessionId)` — Called when a session is about to be closed. Clean up any external state.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/ShaderAuditCore.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogShaderAudit, Log, All);`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/ShaderAuditProgress.h` (Public)


#### class `FScopedProgressTask`  
`class FScopedProgressTask`  
_L19-135_
- desc: RAII progress reporter that works in both editor and standalone. Editor: FScopedSlowTask (modal dialog with cancel). Standalone: modal SWindow with SProgressBar.
- L22 _public function_ `FScopedProgressTask(float InTotalWork, const FText& InDescription, bool bInSilent = false) : TotalWork(FMath::Max(InTotalWork, 1.f)) , CompletedWork(0.f) , Description(InDescription) , bCancelRequested(false) , bSilent(bInSilent)`
- L87 _public function_ `~FScopedProgressTask()`
- L96 _public function_ `void EnterProgressFrame(float Work = 1.f, const FText& Text = FText())`
- L116 _public function_ `bool ShouldCancel() const`
- L126 _private member_ `float TotalWork;`
- L127 _private member_ `float CompletedWork;`
- L128 _private member_ `FText Description;`
- L129 _private member_ `bool bCancelRequested;`
- L130 _private member_ `bool bSilent;`
- L131 _private member_ `TUniquePtr<FScopedSlowTask> SlowTask;`
- L132 _private member_ `TSharedPtr<SWindow> ProgressWindow;`
- L133 _private member_ `TSharedPtr<SProgressBar> ProgressBar;`
- L134 _private member_ `TSharedPtr<STextBlock> StatusText;`

#### Free symbols / members of external scopes

- L76 _function_ `` (scope `FScopedProgressTask::FScopedProgressTask`)

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/ShaderAuditSession.h` (Public)


#### enum `EShaderFilterField`  
`enum class EShaderFilterField : uint8`  
_L18-34_
- desc: Fields available for filtering.
- L21 _public enumerator_ `AssetName` — Asset-level (from pre-parsed index)
- L22 _public enumerator_ `AssetPath` — full object path
- L23 _public enumerator_ `AssetClass` — e.g. "MaterialInstanceConstant", "Material"
- L26 _public enumerator_ `ShaderType` — Shader-level (from FStableShaderKeyAndValue)
- L27 _public enumerator_ `VFType`
- L28 _public enumerator_ `Permutation`
- L29 _public enumerator_ `Hash`
- L32 _public enumerator_ `RefCount` — Derived (from UniqueShaders / BytecodeDatabase)
- L33 _public enumerator_ `Size` — uncompressed bytecode size in bytes

#### enum `EShaderFilterOp`  
`enum class EShaderFilterOp : uint8`  
_L37-46_
- desc: Comparison operators.
- L39 _public enumerator_ `Equal` — ==
- L40 _public enumerator_ `NotEqual` — !=
- L41 _public enumerator_ `LessThan` — <
- L42 _public enumerator_ `GreaterThan` — >
- L43 _public enumerator_ `LessEqual` — <=
- L44 _public enumerator_ `GreaterEqual` — >=
- L45 _public enumerator_ `Contains` — substring match

#### struct `FShaderFilterNode`  
`struct FShaderFilterNode`  
_L53-74_
- desc: A filter expression tree node. Leaf nodes hold a single field/op/value clause. Interior nodes combine children with And/Or/Not.
- L57 _public member_ `EType Type = EType::Clause;`
- L60 _public member_ `EShaderFilterField Field = EShaderFilterField::AssetName;` — Clause data (only when Type == Clause)
- L61 _public member_ `EShaderFilterOp Op = EShaderFilterOp::Equal;`
- L62 _public member_ `FString Value;`
- L65 _public member_ `TArray<FShaderFilterNode> Children;` — Children (And/Or: 2+, Not: 1)
- L68 _public prototype_ `static bool Parse(const FString& Expression, FShaderFilterNode& OutRoot, FString& OutError);` — Parse a filter expression string. Returns false on syntax error.
- L71 _public prototype_ `bool Evaluate( int32 Idx, const struct FShaderAuditSession& Session) const;` — Evaluate this node against a single shader entry.

#### enum `FShaderFilterNode::EType`  
`enum class EType : uint8`  
_L55-55_
- L55 _public enumerator_ `enum class EType : uint8 { Clause, And, Or, Not }; EType Type = EType::Clause; EShaderFilterField Field = EShaderFilterField::AssetName; EShaderFilterOp Op = EShaderFilterOp::Equal; FString Value;`
- L55 _public enumerator_ `enum class EType : uint8 { Clause, And, Or, Not }; EType Type = EType::Clause; EShaderFilterField Field = EShaderFilterField::AssetName; EShaderFilterOp Op = EShaderFilterOp::Equal; FString Value;`
- L55 _public enumerator_ `enum class EType : uint8 { Clause, And, Or, Not }; EType Type = EType::Clause; EShaderFilterField Field = EShaderFilterField::AssetName; EShaderFilterOp Op = EShaderFilterOp::Equal; FString Value;`
- L55 _public enumerator_ `enum class EType : uint8 { Clause, And, Or, Not }; EType Type = EType::Clause; EShaderFilterField Field = EShaderFilterField::AssetName; EShaderFilterOp Op = EShaderFilterOp::Equal; FString Value;`

#### struct `FShaderAuditSession`  
`struct FShaderAuditSession`  
_L114-289_
- desc: A loaded SHK session -- the core data unit shared between the editor plugin and the standalone ShaderAuditViewer. Contains the raw SHK data, the analyzed model for the spreadsheet views, and an optional shader database for bytecode metadata.
- L117 _public member_ `int32 SessionId = AllocateSessionId();` — Unique session ID, assigned at construction.
- L122 _public prototype_ `static TArray<TSharedPtr<FShaderAuditSession>>& GetSessions();` — The global session list. Both editor subsystem and standalone viewer use this.
- L125 _public prototype_ `static TSharedPtr<FShaderAuditSession> FindSession(int32 Id);` — Find a session by its unique ID. Returns null if not found.
- L128 _public prototype_ `static bool CloseSession(int32 Id);` — Remove a session by ID. Returns true if found and removed.
- L131 _private prototype_ `static int32 AllocateSessionId();`
- L135 _public member_ `FString Filename;` — The source SHK file path.
- L138 _public member_ `FString SessionName;` — Session name parsed from the SHK filename convention (e.g. "PCD3D_SM6"). Empty if filename didn't match the pattern.
- L141 _public member_ `TArray<FStableShaderKeyAndValue> StableShaderKeyAndValueArray;` — Raw shader entries loaded from the SHK file.
- L144 _public member_ `TSharedPtr<FShaderBytecodeDatabase> BytecodeDatabase;` — Optional shader database linking OutputHash -> bytecode metadata from .ushaderbytecode files.
- L149 _public prototype_ `bool HasBytecodeDatabase() const;` — Returns true if a bytecode database is loaded for this session.
- L152 _public prototype_ `int32 GetBytecodeArchiveCount() const;` — Number of .ushaderbytecode archive files loaded.
- L155 _public prototype_ `FString GetBytecodeArchiveDirectory() const;` — Directory containing the first loaded bytecode archive, or empty.
- L161 _public prototype_ `bool GetShaderBytecodeInfo(const FShaderHash& Hash, uint8& OutFrequency, uint32& OutCompressedSize, uint32& OutUncompressedSize) const;` — Look up per-shader bytecode metadata by OutputHash. Returns false if no bytecode database is loaded or the hash is unknown.
- L168 _public prototype_ `int32 ReadAllCompressedShaderBlobs(TMap<FShaderHash, TArray<uint8>>& OutBlobs, std::atomic<int32>* OutArchivesDone = nullptr) const;` — Read all compressed shader blobs from disk in archive-sequential order. Returns the number of blobs read. OutBlobs maps OutputHash -> compressed bytes. Optional OutArchivesDone atomic is incremented as each archive file completes (for progress).
- L179 _public member_ `TMap<FName, TSharedPtr<FExtensionData>> ExtensionData;` — Opaque per-extension data attached to this session. Keyed by the owning module's FName.
- L183 _public function_ `template<typename T> T* GetExtensionData(FName Key) const` — Retrieve typed extension data. Returns null if not set.
- L191 _public function_ `template<typename T> void SetExtensionData(FName Key, TSharedPtr<T> Data)` — Store typed extension data. Replaces any previous value for this key.
- L200 _public member_ `TArray<int32> EntryMaterialIndex;` — Per-entry: which material index this SHK entry belongs to.
- L204 _public prototype_ `static void InitFromFullName(const FString& FullName, FString& OutPath, FString& OutClassName);`
- L214 _public member_ `TArray<FUniqueMaterial> UniqueMaterials;`
- L224 _public member_ `TArray<FMaterialPackage> MaterialPackages;`
- L226 _public member_ `int32 NumMaterialParents = 0;`
- L238 _public member_ `TArray<FUniqueShader> UniqueShaders;`
- L241 _public member_ `TMap<FShaderHash, int32> ShaderHashToIndex;` — OutputHash -> unique shader ID. The one hash->index map.
- L244 _public function_ `const FStableShaderKeyAndValue& GetShaderEntry(int32 UniqueShaderID) const` — Access the SHK entry for a unique shader.
- L252 _public function_ `int32 GetHashRefCount(const FShaderHash& Hash) const` — Number of distinct materials that reference this hash.
- L261 _public prototype_ `void BuildIndex();` — Build the indexes from StableShaderKeyAndValueArray. Called once after loading.
- L264 _public function_ `bool HasMaterialHierarchy() const` — Has a material parent map been populated (from any source)?
- L266 _public prototype_ `void SetupMaterialParents(const TMap<FString, FString>& ParentMap);`
- L277 _public prototype_ `static bool DetectSubObject(const FString& Path, FString& OutOuterPackage, FString& OutOuterLeafName, FString& OutSubObjectLeaf);` — Detect sub-object materials produced by FCompactFullName::AppendString flattening. Returns true if Path has consecutive duplicate path components (e.g. MI_Name/MI_Name/), which indicates the Package/Object boundary with sub-objects after it. @param OutOuterPackage   The outer asset's package path (e.g. "/Game/Wraps/MI_Wrap_Denim") @param OutOuterLeafName  The outer asset's leaf name (e.g. "MI_Wrap_Denim") @param OutSubObjectLeaf  The sub-object leaf name after the last '.' (e.g. "CharacterOpaque")
- L280 _public prototype_ `FString BuildHierarchyPath(int32 MaterialIndex) const;` — Build a hierarchy path string for a material by walking its parent chain.
- L288 _public prototype_ `static TArray<TSharedPtr<FShaderAuditSession>> LoadFromInventory(const struct FSessionFileInventory& Inventory);` — Load from a pre-gathered inventory -- the primary loading entry point. Handles everything: caching (if network paths), parallel SHK loading, shader archive import (from Inventory.BytecodeFiles), index building. No directory scanning is performed -- all file paths come from the inventory.

#### struct `FShaderAuditSession::FExtensionData`  
`struct FExtensionData`  
_L173-176_
- desc: Base for extension-owned per-session data. Must be inherited so the virtual destructor cleans up properly.
- L175 _public prototype_ `virtual ~FExtensionData() = default;`

#### struct `FShaderAuditSession::FUniqueMaterial`  
`struct FUniqueMaterial`  
_L206-212_
- L208 _public member_ `FString Path;`
- L209 _public member_ `FString ClassName;`
- L210 _public member_ `int32 PackageIndex = INDEX_NONE;` — -> MaterialPackages[], INDEX_NONE if unresolved
- L211 _public member_ `TArray<int32> ShaderIndices;` — SHK entry indices for this material

#### struct `FShaderAuditSession::FMaterialPackage`  
`struct FMaterialPackage`  
_L218-222_
- L220 _public member_ `FString PackagePath;`
- L221 _public member_ `int32 ParentIndex = INDEX_NONE;` — -> MaterialPackages[], INDEX_NONE for roots

#### struct `FShaderAuditSession::FUniqueShader`  
`struct FUniqueShader`  
_L229-236_
- desc: Per-unique-shader data. Index = unique shader ID.
- L231 _public member_ `int32 FirstEntryIdx = INDEX_NONE;` — -> StableShaderKeyAndValueArray
- L232 _public member_ `TArray<int32> MaterialIndices;` — which materials reference this shader
- L233 _public member_ `uint32 CompressedSize = 0;` — on-disk size from BytecodeDatabase
- L234 _public member_ `uint32 UncompressedSize = 0;` — decompressed size from BytecodeDatabase
- L235 _public member_ `uint16 ArchiveCount = 0;` — number of .ushaderbytecode archives containing this shader

#### struct `FSessionFileInventory`  
`struct FSessionFileInventory`  
_L302-375_
- desc: Inventory of all files associated with a session Used to present caching options to the user before copying.
- L305 _public member_ `FString SessionName;` — Parsed session name (e.g. "PCD3D_SM6").
- L313 _public member_ `FString CacheSubDir;` — Relative cache subdirectory, constructed by Gather(). e.g. "{Branch}-CL-{CL}/{TargetType}/Metadata" Used by ShowCacheSessionDialog to build the full cache path. Empty if the build hierarchy could not be determined.
- L316 _public member_ `TArray<FString> SHKFiles;` — SHK files (full paths).
- L317 _public member_ `int64 SHKTotalBytes = 0;`
- L320 _public member_ `TArray<FString> BytecodeFiles;` — Shader bytecode archives in ../ShaderLibrarySource/ (full paths).
- L321 _public member_ `int64 BytecodeTotalBytes = -1;` — -1 = never attempted, 0 = attempted but none found, >0 = has bytecode
- L324 _public member_ `TMap<FString, FFileStatData> FileStats;` — Per-file stat data (full path -> FFileStatData). Populated during scan and Gather().
- L332 _public member_ `TMap<FString, FString> DestFilenames;` — Optional source->dest filename remapping for caching. When manifest files need to be cached as ShaderStableInfo-* names. Key = source path (in SHKFiles), Value = desired dest filename (just the filename, not path). If a source path is not in this map, CacheSessionFiles uses the source filename as-is.
- L335 _public function_ `FDateTime GetMostRecentTime() const` — Most recent modification time across all files in FileStats.
- L360 _public prototype_ `static FSessionFileInventory Gather( const TArrayView<const FString>& FilesToLoad, bool bShowProgress = true, const TMap<FString, FFileStatData>* PrecomputedStats = nullptr);` — Discover all session-related files from a list of SHK paths. The first path is used to derive the session name and directory. All paths are used as the SHK file list (stat'd for sizes unless pre-computed). Bytecode files are discovered relative to the derived build metadata directory (BuildRoot + CacheSubDir for manifest paths, or by walking up the directory hierarchy for non-manifest paths). For manifest paths (NAS naming convention), resolves to real build paths when the build directory exists, or uses them directly otherwise. @param FilesToLoad       SHK file paths (full sibling list). @param bShowProgress     If true, show a progress dialog. @param PrecomputedStats Optional map of path->stat data. Skips stat for paths found here.
- L374 _public prototype_ `static TArray<FString> FindSHKSiblings(const FString& SHKPath, bool bShowProgress = false);` — Find all SHK siblings of a given SHK file. Enumerates the directory for files matching the same session name suffix. E.g. for ShaderStableInfo-Game-PCD3D_SM6.shk, finds all *-PCD3D_SM6.shk siblings. Returns the full list including the input file itself. If the session name cannot be parsed, returns just the input path. @param bShowProgress  If true, show a progress dialog during directory enumeration (useful for NAS paths).

#### struct `FSessionCacheOptions`  
`struct FSessionCacheOptions`  
_L378-382_
- desc: Which file categories to include when caching.
- L380 _public member_ `bool bIncludeSHK = true;`
- L381 _public member_ `bool bIncludeBytecode = false;`

#### Free symbols / members of external scopes

- L77 _prototype_ `TArray<FStringView> TokenizeFilterExpression(const FString& Input);` — Tokenize a filter expression into individual tokens (views into the input string).
- L80 _prototype_ `bool ParseFilterFieldName(FStringView Name, EShaderFilterField& OutField);` — Map a field name string (e.g. "asset.class") to its enum value.
- L83 _prototype_ `bool ParseFilterOp(FStringView OpStr, EShaderFilterOp& OutOp);` — Map an operator string (e.g. "==") to its enum value.
- L89 _prototype_ `void BuildVisibleShaders( const FShaderAuditSession& Session, const TArray<FShaderFilterNode>& Filters, int32 MaxRefCount, TBitArray<>& OutVisible);` — Build a TBitArray from a list of filter nodes (AND'd together) plus a refcount cap. Entries passing all filters have their bit set to true.
- L100 _prototype_ `void GetShaderFilterSuggestions( const FString& Text, const FShaderAuditSession* Session, TArray<FString>& OutSuggestions);` — Populate filter autocompletion suggestions for a filter expression text box. Suggests field names, operators, values from session data, and logic operators. Session may be null (only field/operator suggestions will be offered).
- L296 _prototype_ `bool IsNetworkPath(const FString& Path);` — Returns true if the given path resides on a network/remote drive.
- L394 _prototype_ `FSessionFileInventory CacheSessionFiles( const FSessionFileInventory& Inventory, const FString& DestDir, const FSessionCacheOptions& Options);` — Copy selected session files from the inventory to a local directory. Shows progress via FScopedProgressTask. Files already present with matching size are skipped. @param Inventory       Gathered file inventory @param DestDir         Local directory to copy into (preserves subfolder structure) @param Options         Which categories to copy @return Paths to the local copies (same structure as inventory, but local)
- L407 _prototype_ `bool ShowCacheSessionDialog( const FSessionFileInventory& Inventory, FSessionCacheOptions& OutOptions, FString& OutCacheDir);` — Show a modal dialog letting the user choose which file categories to cache and where to cache them. Returns true if the user clicked Cache, false on Cancel. @param Inventory       Gathered file inventory (displayed to the user) @param OutOptions      Populated with the user's category selections @param OutCacheDir     Populated with the chosen cache directory
- L418 _prototype_ `bool ClearCachedSessionDir(const FString& DirToDelete);` — Delete cached shader files (.shk, .ushaderbytecode) under the given directory. Removes only known file types, then prunes empty directories bottom-up. Can be used to clear a specific CL dir or the entire cache root. @return true if any files were deleted.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/ShaderAuditTypes.h` (Public)


#### struct `FShaderFolderNode`  
`struct FShaderFolderNode`  
_L16-35_
- desc: A node in the shader cost hierarchy. Folders and assets share this structure.
- L18 _public member_ `FString Name;`
- L19 _public member_ `FString FullPath;` — "/" for root, "/Game/MyContent" for folders, "/Game/MyContent/Foo.Bar" for assets
- L20 _public member_ `FString TooltipText;` — Shown on hover (e.g. real UE package path in hierarchy mode)
- L21 _public member_ `FString EditorPath;` — Non-empty for generated sub-object nodes and their authored proxy folder.
- L25 _public member_ `FString ClassName;` — Loadable UE object path of the source authored MIC (e.g. "/Game/.../Meatball_Parts.Meatball_Parts"). Use this for MaterialValidation / ResolveMaterialPath instead of FullPath.
- L26 _public member_ `bool bIsAsset = false;`
- L27 _public member_ `int32 MaterialIndex = INDEX_NONE;` — Index into FShaderAuditSession::UniqueMaterials (-1 for folders)
- L28 _public member_ `int32 ShaderCount = 0;` — For assets: direct count. For folders: sum of all descendants.
- L29 _public member_ `float Cost = 0.f;` — For assets: sum(1/refcount). For folders: sum of all descendants.
- L31 _public member_ `TArray<TSharedPtr<FShaderFolderNode>> Children;`
- L32 _public member_ `TWeakPtr<FShaderFolderNode> Parent;`
- L34 _public function_ `bool operator==(const FShaderFolderNode& Other) const`

#### struct `FShaderDetailRow`  
`struct FShaderDetailRow`  
_L38-54_
- desc: A row in the detail panel (top-N assets or per-shader breakdown)
- L40 _public member_ `FString Label;`
- L41 _public member_ `FString ClassName;`
- L42 _public member_ `int32 ShaderCount = 0;`
- L43 _public member_ `float Cost = 0.f;` — Shaders / RefCount
- L44 _public member_ `FString AssetPath;` — Display path for tooltips (empty for shader detail rows)
- L45 _public member_ `int32 MaterialIndex = INDEX_NONE;` — For navigation to asset node (INDEX_NONE for shader rows)
- L46 _public member_ `FName ShaderType;`
- L47 _public member_ `FName VFType;`
- L48 _public member_ `FName TargetFrequency;`
- L49 _public member_ `FName PermutationId;`
- L50 _public member_ `FString HashString;`
- L51 _public member_ `int32 RefCount = 0;`
- L52 _public member_ `int32 Size = 0;` — Shader code size in bytes (0 = unknown)
- L53 _public member_ `bool bSizeWeighted = false;` — true when costs are in bytes (BytecodeDatabase attached)

#### Free symbols / members of external scopes

- L58 _prototype_ `TArray<TSharedPtr<FShaderDetailRow>> BuildMaterialDetailRows( const FShaderAuditSession& Session, int32 MaterialIndex, const TBitArray<>* VisibleShaders);` — Build detail rows for a material's shaders. Shared between Slate detail panel and MCP. Filters by VisibleShaders bitarray, sorts by size descending then refcount ascending.
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace ShaderAudit` (scope `UE`)
- L63 _namespace_ `namespace Utils` (scope `UE::ShaderAudit`)
- L66 _function_ `inline FString FormatBytes(uint64 Bytes)` (scope `UE::ShaderAudit::Utils`) — Format a byte count as human-readable (B / KB / MB / GB).
- L88 _function_ `inline FString FormatCost(float Cost, bool bSizeWeighted)` (scope `UE::ShaderAudit::Utils`) — Format a cost value for display. When a BytecodeDatabase is attached, costs are size-weighted (bytes) and should be shown as KB/MB. Otherwise they are simple refcount-weighted counts shown as plain numbers.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/ShaderAuditViews.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ShaderAudit` (scope `UE`)
- L24 _prototype_ `TSharedRef<FShaderFolderNode> BuildFolderTree( const FShaderAuditSession& Session, const TBitArray<>* VisibleShaders, TMap<FString, TSharedPtr<FShaderFolderNode>>& OutNodeMap);` (scope `UE::ShaderAudit`) — Build a FShaderFolderNode hierarchy from the session, optionally filtered by a bit array. Assets with no visible shaders are excluded. Cost/ShaderCount reflect only visible shaders. @param Session			The session to build from @param VisibleShaders	Optional: one bit per entry, null = all visible @param OutNodeMap		Output: maps FullPath -> node for fast lookup @return Root folder node
- L39 _prototype_ `TSharedRef<FShaderFolderNode> BuildMaterialHierarchyTree( const FShaderAuditSession& Session, const TBitArray<>* VisibleShaders, TMap<FString, TSharedPtr<FShaderFolderNode>>& OutNodeMap);` (scope `UE::ShaderAudit`) — Build a FShaderFolderNode hierarchy based on the material parent chain. Base Materials are roots, MIC children nest underneath. Assets without a parent chain (NiagaraScript, etc.) go under an "Other" root, grouped by folder path. Requires MaterialPackages to be populated. @param Session			The session to build from @param VisibleShaders	Optional: one bit per entry, null = all visible @param OutNodeMap		Output: maps FullPath -> node for fast lookup @return Root node (virtual root containing hierarchy roots + Other)
- L48 _prototype_ `TSharedRef<FTreeMapNodeData> BuildTreeMapView( const TSharedRef<FShaderFolderNode>& Root, int32 MaxDepth, bool bSizeWeighted = false);` (scope `UE::ShaderAudit`) — Build a throwaway FTreeMapNodeData tree from a FShaderFolderNode subtree. Reads Cost directly from FShaderFolderNode.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/ShaderBytecodeDatabase.h` (Public)


#### struct `FShaderBytecodeInfo`  
`struct FShaderBytecodeInfo`  
_L14-24_
- desc: Lightweight per-shader metadata extracted from .ushaderbytecode headers. No bytecode is loaded -- just size and location info for on-demand access.
- L16 _public member_ `uint32 CompressedSize = 0;` — On-disk (compressed) size in bytes
- L17 _public member_ `uint32 UncompressedSize = 0;` — Full size after decompression (includes SRT + code + optional)
- L18 _public member_ `uint8 Frequency = 0;` — EShaderFrequency value
- L21 _public member_ `uint16 ArchiveIndex = 0;` — Where to find the bytecode on disk if we need to load it later
- L22 _public member_ `uint64 OffsetInArchive = 0;` — Byte offset into the code blob within the archive file
- L23 _public member_ `uint16 ArchiveCount = 1;` — Number of archives containing this shader (for duplication tracking)

#### struct `FShaderArchiveSource`  
`struct FShaderArchiveSource`  
_L30-34_
- desc: Bookkeeping for a single .ushaderbytecode file so we can go back and read bytecodes on demand without keeping the whole file in memory.
- L32 _public member_ `FString FilePath;`
- L33 _public member_ `uint64 CodeBlobFileOffset = 0;` — Byte position in the file where the code blob starts

#### class `FShaderBytecodeDatabase`  
`class FShaderBytecodeDatabase`  
_L51-86_
- desc: A database that maps OutputHash -> shader metadata (and optionally bytecode). Designed for two-phase use: 1. Import: Load .ushaderbytecode headers (fast, small memory footprint). This gives size/frequency per shader. 2. (Future) On-demand bytecode: Load individual shader bytecodes for disassembly, clustering, diffing. The OutputHash is the common key between .shk files (FStableShaderKeyAndValue::OutputHash) and .ushaderbytecode files (FSerializedShaderArchive::ShaderHashes[i]). Thread safety: Import methods are not thread-safe. Call from game thread only. After import, Find() is safe for concurrent reads.
- L55 _public prototype_ `int32 ImportDirectory(const FString& DirectoryPath);` — Load headers from all .ushaderbytecode files in a directory. Returns number of files loaded.
- L58 _public prototype_ `int32 ImportShaderArchive(const FString& FilePath);` — Load a single .ushaderbytecode file's header. Returns number of new shaders added.
- L61 _public prototype_ `const FShaderBytecodeInfo* Find(const FShaderHash& Hash) const;` — Look up a shader by OutputHash. Returns nullptr if not found.
- L64 _public function_ `int32 Num() const` — Total number of unique shaders in the database.
- L67 _public function_ `int32 NumArchives() const` — Total number of loaded archive files.
- L70 _public prototype_ `void Reset();` — Clear all data.
- L77 _public prototype_ `int32 ReadAllCompressedBlobs(TMap<FShaderHash, TArray<uint8>>& OutBlobs, std::atomic<int32>* OutArchivesDone = nullptr) const;` — Read all compressed shader blobs from disk in archive-sequential order. Opens each archive file exactly once, reads entries sorted by offset for optimal I/O. The returned blobs are still compressed.
- L80 _public function_ `const TArray<FShaderArchiveSource>& GetArchives() const` — Access to the archive sources (for on-demand bytecode loading).
- L84 _private member_ `TArray<FShaderArchiveSource> Archives;`
- L85 _private member_ `TMap<FShaderHash, FShaderBytecodeInfo> Entries;`

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/Widgets/SMaterialDiffTable.h` (Public)


#### class `SMaterialDiffTable`  
`class SMaterialDiffTable : public SCompoundWidget`  
_L20-71_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SMaterialDiffTable)`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FShaderAuditSession>, SessionA) SLATE_ARGUMENT(TSharedPtr<FShaderAuditSession>, SessionB) SLATE_EVENT(FOnNavigateToShaderAsset, OnNavigateToAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `void DiffSessions(TSharedPtr<FShaderAuditSession> InSessionA, TSharedPtr<FShaderAuditSession> InSessionB);`
- L35 _private member_ `TArray<FMaterialDiffNodePtr> Items;`
- L36 _private member_ `TArray<FMaterialDiffNodePtr> FilteredItems;`
- L37 _private member_ `TSharedPtr<FShaderAuditSession> SessionA;`
- L38 _private member_ `TSharedPtr<FShaderAuditSession> SessionB;`
- L40 _private member_ `TSharedPtr<SListView<FMaterialDiffNodePtr>> ListView;`
- L43 _private member_ `FOnNavigateToShaderAsset OnNavigateToAssetHook;` — --- Editor hooks (bound by caller via Slate args) ---
- L44 _private member_ `TSharedPtr<STextBlock> SummaryText;`
- L47 _private member_ `bool bShowNew = true;` — Status filter toggles
- L48 _private member_ `bool bShowRemoved = true;`
- L49 _private member_ `bool bShowChanged = true;`
- L50 _private member_ `bool bShowSame = false;`
- L53 _private member_ `FName SortColumn;` — Column sorting
- L54 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`
- L55 _private prototype_ `void OnSortColumnHeader(EColumnSortPriority::Type Priority, const FName& Column, EColumnSortMode::Type NewSortMode);`
- L56 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName Column) const;`
- L59 _private member_ `TSharedPtr<STextBlock> HeaderB1Text;` — Dynamic header text for numeric columns
- L60 _private member_ `TSharedPtr<STextBlock> HeaderB2Text;`
- L61 _private member_ `TSharedPtr<STextBlock> HeaderDeltaText;`
- L63 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FMaterialDiffNodePtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L64 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L65 _private prototype_ `void RefreshFilteredItems();`
- L66 _private prototype_ `void ExportFilteredItemsToCSV();`
- L67 _private prototype_ `void ApplyRegressionPreset();`
- L69 _private member_ `FText FilterText;`
- L70 _private member_ `int32 MinDeltaThreshold = 0;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using FMaterialDiffNodePtr = TSharedPtr<FMaterialDiffNode>;`
- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNavigateToShaderAsset, const FString& , bool );` — Caller-supplied hook to navigate to an asset (typically: focus content browser, or open the asset editor when bCtrlDown is true). Unbound -> click does nothing.
- L18 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnNavigateToShaderAsset, const FString& , bool );` — Caller-supplied hook to navigate to an asset (typically: focus content browser, or open the asset editor when bCtrlDown is true). Unbound -> click does nothing.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/Widgets/SShaderAuditWidget.h` (Public)


#### class `SShaderAuditWidget`  
`class SShaderAuditWidget : public SCompoundWidget`  
_L24-78_
- inherits: `SCompoundWidget`
- desc: Top-level widget for the Shader Audit tab/window. Hosts a local FTabManager for document tabs (session views, diffs). Works in both the editor plugin and the standalone ShaderAuditViewer.
- L27 _public function_ `SLATE_BEGIN_ARGS(SShaderAuditWidget)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FOnSessionsChanged>, OnSessionsChangedEvent)` — Optional: subscribe to this delegate to auto-refresh when sessions change.
- L46 _public prototype_ `void SpawnSessionTab(TSharedPtr<FShaderAuditSession> Session);` — Spawn a session inspect tab (deduplicates by full SHK path).
- L49 _public prototype_ `void SpawnDiffTab(TSharedPtr<FShaderAuditSession> SessionA, TSharedPtr<FShaderAuditSession> SessionB);` — Spawn a diff tab comparing two sessions.
- L52 _public prototype_ `void ShowDiffPicker();` — Show a popup to pick two sessions and diff them.
- L55 _public prototype_ `void ShowBrowserTab();` — Show (or focus) the embedded SHK browser tab.
- L58 _private member_ `TSharedPtr<FOnSessionsChanged> SessionsChangedEvent;`
- L59 _private member_ `FDelegateHandle SessionsChangedHandle;`
- L60 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L61 _private member_ `TSharedPtr<SDockTab> HostTab;`
- L64 _private member_ `FOnExtendShaderAssetContextMenu OnExtendAssetContextMenuHook;` — --- Editor hooks captured from Slate args, forwarded to child widgets ---
- L65 _private member_ `FOnOpenShaderAssetInContentBrowser OnOpenAssetInContentBrowserHook;`
- L66 _private member_ `FOnNavigateToShaderAsset OnNavigateToAssetHook;`
- L67 _private member_ `FOnFetchMaterialHierarchy OnFetchMaterialHierarchyHook;`
- L70 _private member_ `TMap<int32, TWeakPtr<SDockTab>> OpenSessionTabs;` — Track open session tabs to avoid duplicates (key = SessionId)
- L73 _private member_ `TWeakPtr<SDockTab> BrowserTab;` — Browser tab
- L74 _private prototype_ `void SpawnBrowserTab();`
- L77 _private prototype_ `void HandleSessionsChanged();`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSessionsChanged);` — Simple multicast event for "sessions changed" notification.
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSessionsChanged);` — Simple multicast event for "sessions changed" notification.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/Widgets/SShaderCostTreeMap.h` (Public)


#### class `SShaderCostTreeMap`  
`class SShaderCostTreeMap : public SCompoundWidget`  
_L33-185_
- inherits: `SCompoundWidget`
- desc: Interactive shader cost treemap with folder navigation and detail panel. Layout: Left = folder tree, Right-top = detail panel, Right-bottom = STreeMap treemap. Data model: FShaderFolderNode tree is the stable, persistent hierarchy. FTreeMapNodeData trees are throwaway views rebuilt on every navigation.
- L36 _public function_ `SLATE_BEGIN_ARGS(SShaderCostTreeMap)`
- L40 _public prototype_ `SLATE_EVENT(FOnExtendShaderAssetContextMenu, OnExtendAssetContextMenu) SLATE_EVENT(FOnOpenShaderAssetInContentBrowser, OnOpenAssetInContentBrowser) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Optional hook: invoked when building the right-click context menu for a material asset. Lets the editor add entries (e.g., "Find Similar Instances") without the widget itself depending on editor-only modules.
- L50 _public prototype_ `void SetSession(TSharedPtr<FShaderAuditSession> InSession);` — Set the session to visualize. Call after loading an SHK file.
- L53 _public prototype_ `void ClearData();` — Clear all data
- L56 _public function_ `const FString& GetCurrentPath() const` — Current navigation path (e.g. "/Game/Characters"). "/" = root.
- L59 _public function_ `const TBitArray<>& GetVisibleShaders() const` — Current visibility bit array. One bit per StableShaderKeyAndValueArray entry.
- L62 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget overrides
- L65 _public prototype_ `void RebuildFromFilters();` — Rebuild the folder/hierarchy tree from current filters.
- L67 _public prototype_ `bool IsMaterialHierarchyMode() const;`
- L71 _private prototype_ `TSharedRef<SWidget> MakeToolbar();` — Layout builders (in SShaderCostTreeMap_Construct.cpp)
- L72 _private prototype_ `TSharedRef<SWidget> MakeFilterBar();`
- L73 _private prototype_ `TSharedRef<SWidget> MakeFilterTagBar();`
- L74 _private prototype_ `TSharedRef<SWidget> MakePathBar();`
- L75 _private prototype_ `TSharedRef<SWidget> MakeContentArea();`
- L78 _private member_ `TSharedPtr<FShaderAuditSession> Session;` — --- Data ---
- L79 _private member_ `TBitArray<> VisibleShaders;` — One bit per StableShaderKeyAndValueArray entry (all true = no filter)
- L80 _private member_ `TSharedPtr<FShaderFolderNode> RootFolderData;` — Cached folder tree (rebuilt when filters change)
- L81 _private member_ `TMap<FString, TSharedPtr<FShaderFolderNode>> FolderNodeMap;`
- L82 _private member_ `TSharedPtr<FTreeMapNodeData> RootTreeMapNode;`
- L85 _private member_ `int32 MaxRefCount = 1;` — --- State ---
- L86 _private member_ `int32 MaxTreeDepth = 3;` — depth limit, clamped to [1,20] by UI (GetDepthLabel handles 0 defensively)
- L92 _private member_ `ETreeMapMode TreeMapMode = ETreeMapMode::FolderTree;`
- L94 _private member_ `bool bIsNavigating = false;` — Guard against re-entrant navigation
- L97 _private member_ `TArray<FString> NavigationHistory = { TEXT("/") }` — --- History ---
- L98 _private member_ `int32 HistoryIndex = 0;`
- L99 _private member_ `bool bIsHistoryNavigation = false;`
- L102 _private member_ `TArray<TSharedPtr<FShaderFolderNode>> SidebarRootNodes;` — --- Folder Tree (sidebar) ---
- L103 _private member_ `TSharedPtr<STreeView<TSharedPtr<FShaderFolderNode>>> FolderTreeWidget;`
- L105 _private prototype_ `void RebuildFolderTree();`
- L106 _private prototype_ `TSharedRef<class ITableRow> OnGenerateFolderRow(TSharedPtr<FShaderFolderNode> Item, const TSharedRef<class STableViewBase>& OwnerTable);`
- L107 _private prototype_ `void OnGetFolderChildren(TSharedPtr<FShaderFolderNode> Item, TArray<TSharedPtr<FShaderFolderNode>>& OutChildren);`
- L108 _private prototype_ `void OnFolderSelectionChanged(TSharedPtr<FShaderFolderNode> Item, ESelectInfo::Type SelectInfo);`
- L111 _private member_ `TSharedPtr<STreeMap> TreeMapWidget;` — --- Treemap ---
- L113 _private prototype_ `void RebuildTreeMap();`
- L114 _private prototype_ `void OnTreeMapNodeDoubleClicked(FTreeMapNodeData& NodeData, const FPointerEvent& MouseEvent);`
- L115 _private prototype_ `void OnTreeMapNodeRightClicked(FTreeMapNodeData& NodeData, const FPointerEvent& MouseEvent);`
- L116 _private prototype_ `void OnTreeMapWheelNavigate(const FString& TargetPath);`
- L119 _private member_ `TArray<TSharedPtr<FShaderDetailRow>> DetailRows;` — --- Detail Panel ---
- L120 _private member_ `TSharedPtr<class SWidgetSwitcher> DetailSwitcher;`
- L121 _private function_ `FText GetDetailTitle() const`
- L122 _private member_ `FText DetailTitle;`
- L125 _private member_ `TSharedPtr<SListView<TSharedPtr<FShaderDetailRow> > > FolderDetailListWidget;` — Folder detail (slot 0): plain STextBlock rows -- Name, Class, Shaders, Cost
- L126 _private member_ `TSharedPtr<SHeaderRow> FolderDetailHeaderRow;`
- L127 _private prototype_ `TSharedRef<class ITableRow> OnGenerateFolderDetailRow(TSharedPtr<FShaderDetailRow> Item, const TSharedRef<class STableViewBase>& OwnerTable);`
- L130 _private member_ `TSharedPtr<SListView<TSharedPtr<FShaderDetailRow> > > ShaderDetailListWidget;` — Shader detail (slot 1): selectable SEditableText rows -- ShaderType, VFType, Perm, Hash, RefCount, Size
- L131 _private member_ `TSharedPtr<SHeaderRow> ShaderDetailHeaderRow;`
- L132 _private prototype_ `TSharedRef<class ITableRow> OnGenerateShaderDetailRow(TSharedPtr<FShaderDetailRow> Item, const TSharedRef<class STableViewBase>& OwnerTable);`
- L134 _private prototype_ `void RefreshDetailPanel(const FString& CurrentPath);`
- L135 _private prototype_ `void ShowFolderDetail(const FString& FolderPath);`
- L136 _private prototype_ `void ShowAssetDetail(int32 MaterialIndex);`
- L137 _private prototype_ `void OnDetailRowDoubleClicked(TSharedPtr<FShaderDetailRow> Item);`
- L138 _private prototype_ `void OpenAssetInContentBrowser(const FString& AssetPath);`
- L141 _private member_ `FOnExtendShaderAssetContextMenu OnExtendAssetContextMenuHook;` — --- Editor hooks (bound by caller via Slate args) ---
- L142 _private member_ `FOnOpenShaderAssetInContentBrowser OnOpenAssetInContentBrowserHook;`
- L147 _private prototype_ `TSharedPtr<SWidget> BuildAssetContextMenu(const TSharedPtr<FShaderFolderNode>& Node);` — Build the right-click context menu for a material asset node. Used by both the treemap right-click handler and the folder tree context menu. Returns null if the node has neither a valid MaterialIndex nor an EditorPath.
- L150 _private prototype_ `void NavigateTo(const FString& Path);` — --- Navigation ---
- L151 _private prototype_ `void ExpandFolderTreeTo(const FString& FolderPath);`
- L154 _private member_ `TSharedPtr<SBreadcrumbTrail<FString>> BreadcrumbTrail;` — --- Breadcrumb / Path Edit ---
- L155 _private member_ `TSharedPtr<class SWidgetSwitcher> PathSwitcher;`
- L156 _private member_ `TSharedPtr<class SEditableTextBox> PathEditBox;`
- L157 _private prototype_ `void RebuildBreadcrumb();`
- L158 _private prototype_ `void OnBreadcrumbClicked(const FString& Path);`
- L159 _private prototype_ `void StartPathEdit();`
- L160 _private prototype_ `void OnPathEditCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L163 _private member_ `TArray<FShaderFilterNode> ActiveFilters;` — --- Filters ---
- L164 _private member_ `TArray<FString> ActiveFilterStrings;`
- L165 _private member_ `TSharedPtr<class SWrapBox> FilterTagBox;`
- L166 _private member_ `TSharedPtr<class SSearchBox> HashSearchBox;`
- L167 _private prototype_ `void OnFilterCommitted(const FText& Text, ETextCommit::Type CommitType);`
- L168 _private prototype_ `void RemoveFilter(int32 Index);`
- L169 _private prototype_ `void ApplyFilters();`
- L170 _private prototype_ `void RebuildFilterTags();`
- L171 _private prototype_ `void GetFilterSuggestions(const FString& Text, TArray<FString>& OutSuggestions);`
- L174 _private function_ `TOptional<int32> GetRefCountValue() const` — --- Refcount ---
- L175 _private prototype_ `void OnRefCountCommitted(int32 NewValue, ETextCommit::Type CommitType);`
- L176 _private prototype_ `FText GetRefCountLabel() const;`
- L177 _private prototype_ `FText GetStatsLabel() const;`
- L178 _private member_ `FText CachedStatsLabel;`
- L179 _private prototype_ `void UpdateCachedStats();`
- L182 _private function_ `TOptional<int32> GetDepthValue() const` — --- Depth ---
- L183 _private prototype_ `void OnDepthCommitted(int32 NewValue, ETextCommit::Type CommitType);`
- L184 _private prototype_ `FText GetDepthLabel() const;`

#### enum `SShaderCostTreeMap::ETreeMapMode`  
`enum class ETreeMapMode : uint8`  
_L87-91_
- L89 _public enumerator_ `FolderTree`
- L90 _public enumerator_ `MaterialHierarchy`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnExtendShaderAssetContextMenu, FMenuBuilder& , const FString& );` — Caller-supplied hook to add extra entries to a material asset's right-click context menu. If unbound, the menu just contains the widget's built-in entries (e.g., copy hash).
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnExtendShaderAssetContextMenu, FMenuBuilder& , const FString& );` — Caller-supplied hook to add extra entries to a material asset's right-click context menu. If unbound, the menu just contains the widget's built-in entries (e.g., copy hash).
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOpenShaderAssetInContentBrowser, const FString& );` — Caller-supplied hook to "open this asset in the content browser" (or equivalent navigation). If unbound, the widget logs a notice and does nothing -- standalone mode.
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOpenShaderAssetInContentBrowser, const FString& );` — Caller-supplied hook to "open this asset in the content browser" (or equivalent navigation). If unbound, the widget logs a notice and does nothing -- standalone mode.

### `Plugins/Developer/ShaderToolkit/Source/ShaderAuditCore/Public/Widgets/SShaderSessionView.h` (Public)


#### class `SShaderSessionView`  
`class SShaderSessionView : public SCompoundWidget`  
_L19-54_
- inherits: `SCompoundWidget`
- desc: Session document view -- toolbar (view toggle) over a widget switcher containing spreadsheet, raw SHK, cost treemap, and extension-contributed views.
- L22 _public function_ `SLATE_BEGIN_ARGS(SShaderSessionView)`
- L23 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FShaderAuditSession>, Session) SLATE_EVENT(FOnExtendShaderAssetContextMenu, OnExtendAssetContextMenu) SLATE_EVENT(FOnOpenShaderAssetInContentBrowser, OnOpenAssetInContentBrowser) /** If bound, a "Fetch Material Hie`
- L38 _private member_ `TSharedPtr<FShaderAuditSession> Session;`
- L39 _private member_ `TSharedPtr<class SInspectShaderSessionWidget> InspectWidget;`
- L40 _private member_ `TSharedPtr<class SShaderCostTreeMap> CostTreeMapWidget;`
- L41 _private member_ `TSharedPtr<class SSHKEntryListWidget> RawSHKWidget;`
- L42 _private member_ `TSharedPtr<class SWidgetSwitcher> ViewSwitcher;`
- L45 _private member_ `int32 NextExtensionViewIndex = 3;` — Next widget index to assign when adding extension views.
- L47 _private prototype_ `void AddExtensionContributions(class IShaderAuditExtension& Extension);`
- L48 _private prototype_ `void OnModularFeatureRegistered(const FName& Type, class IModularFeature* Feature);`
- L49 _private prototype_ `void OnModularFeatureUnregistered(const FName& Type, class IModularFeature* Feature);`
- L51 _private member_ `TSharedPtr<class SHorizontalBox> ToolbarBox;`
- L53 _private member_ `FOnFetchMaterialHierarchy OnFetchMaterialHierarchyHook;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFetchMaterialHierarchy, TSharedPtr<FShaderAuditSession> );` — Caller-supplied hook to populate a session's material parent map (typically: walk the editor's Asset Registry). Unbound -> the "Fetch Material Hierarchy" button is hidden.
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFetchMaterialHierarchy, TSharedPtr<FShaderAuditSession> );` — Caller-supplied hook to populate a session's material parent map (typically: walk the editor's Asset Registry). Unbound -> the "Fetch Material Hierarchy" button is hidden.
