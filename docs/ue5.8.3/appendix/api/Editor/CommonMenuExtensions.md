# Editor / CommonMenuExtensions

- module root: `Source/Editor/CommonMenuExtensions`
- headers: 12; symbols: 271
- symbol kinds: class=12, enum=6, enumerator=19, function=21, macro=11, member=55, prototype=118, struct=11, typedef=18
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, Engine, InputCore, Slate, SlateCore, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicIncludePathModuleNames: 

### `Source/Editor/CommonMenuExtensions/Public/BufferVisualizationMenuCommands.h` (Public)


#### class `FBufferVisualizationMenuCommands`  
`class FBufferVisualizationMenuCommands : public TCommands<FBufferVisualizationMenuCommands>`  
_L21-63_
- inherits: `TCommands<FBufferVisualizationMenuCommands>`
- L36 _public typedef_ `typedef TMultiMap<FName, FBufferVisualizationRecord> TBufferVisualizationModeCommandMap;`
- L37 _public typedef_ `typedef TBufferVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L39 _public prototype_ `FBufferVisualizationMenuCommands();`
- L41 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L42 _public prototype_ `const FBufferVisualizationRecord& OverviewCommand() const;`
- L44 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L46 _public prototype_ `virtual void RegisterCommands() override;`
- L48 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L51 _private prototype_ `void BuildCommandMap();`
- L53 _private prototype_ `void CreateOverviewCommand();`
- L54 _private prototype_ `void CreateVisualizationCommands();`
- L56 _private prototype_ `void AddOverviewCommandToMenu(FMenuBuilder& Menu) const;`
- L57 _private prototype_ `void AddVisualizationCommandsToMenu(FMenuBuilder& menu) const;`
- L59 _private prototype_ `static void ChangeBufferVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L60 _private prototype_ `static bool IsBufferVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L62 _private member_ `TBufferVisualizationModeCommandMap CommandMap;`

#### struct `FBufferVisualizationMenuCommands::FBufferVisualizationRecord`  
`struct FBufferVisualizationRecord`  
_L24-34_
- L26 _public member_ `FName Name;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L29 _public function_ `FBufferVisualizationRecord() : Name(), Command()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/CommonMenuExtensionsModule.h` (Public)


#### class `FCommonMenuExtensionsModule`  
`class FCommonMenuExtensionsModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Editor/CommonMenuExtensions/Public/GroomVisualizationMenuCommands.h` (Public)


#### class `FGroomVisualizationMenuCommands`  
`class FGroomVisualizationMenuCommands : public TCommands<FGroomVisualizationMenuCommands>`  
_L25-68_
- inherits: `TCommands<FGroomVisualizationMenuCommands>`
- L35 _public typedef_ `typedef TMultiMap<FName, FGroomVisualizationRecord> TGroomVisualizationModeCommandMap;`
- L36 _public typedef_ `typedef TGroomVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L38 _public prototype_ `FGroomVisualizationMenuCommands();`
- L40 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L42 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L43 _public prototype_ `static void BuildVisualisationSubMenuForGroomEditor(FMenuBuilder& Menu);`
- L44 _public prototype_ `static FToolMenuEntry BuildVisualizationSubMenuItem(const TWeakPtr<SEditorViewport>& Viewport);`
- L45 _public prototype_ `static FToolMenuEntry BuildVisualizationSubMenuItemForGroomEditor(const TWeakPtr<SEditorViewport>& Viewport);`
- L47 _public prototype_ `virtual void RegisterCommands() override;`
- L49 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L51 _public function_ `inline bool IsPopulated() const`
- L57 _private prototype_ `void BuildCommandMap();`
- L58 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const EGroomViewMode Type) const;`
- L60 _private prototype_ `static void InternalBuildVisualisationSubMenu(FMenuBuilder& Menu, bool bIsGroomEditor);`
- L61 _private prototype_ `static void ChangeGroomVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L62 _private prototype_ `static bool IsGroomVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L64 _private prototype_ `static FToolMenuEntry InternalBuildVisualizationSubMenuItem(const TWeakPtr<SEditorViewport>& Viewport, bool bIsGroomEditor);`
- L67 _private member_ `TGroomVisualizationModeCommandMap CommandMap;`

#### struct `FGroomVisualizationMenuCommands::FGroomVisualizationRecord`  
`struct FGroomVisualizationRecord`  
_L28-33_
- L30 _public member_ `FName Name;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L32 _public member_ `EGroomViewMode Mode;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/LumenVisualizationMenuCommands.h` (Public)


#### class `FLumenVisualizationMenuCommands`  
`class FLumenVisualizationMenuCommands : public TCommands<FLumenVisualizationMenuCommands>`  
_L22-73_
- inherits: `TCommands<FLumenVisualizationMenuCommands>`
- L46 _public typedef_ `typedef TMultiMap<FName, FLumenVisualizationRecord> TLumenVisualizationModeCommandMap;`
- L47 _public typedef_ `typedef TLumenVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L49 _public prototype_ `FLumenVisualizationMenuCommands();`
- L51 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L53 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L55 _public prototype_ `virtual void RegisterCommands() override;`
- L57 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L59 _public function_ `inline bool IsPopulated() const`
- L65 _private prototype_ `void BuildCommandMap();`
- L66 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const FLumenVisualizationType Type) const;`
- L68 _private prototype_ `static void ChangeLumenVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L69 _private prototype_ `static bool IsLumenVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L72 _private member_ `TLumenVisualizationModeCommandMap CommandMap;`

#### enum `FLumenVisualizationMenuCommands::FLumenVisualizationType`  
`enum class FLumenVisualizationType : uint8`  
_L25-30_
- L27 _public enumerator_ `Overview`
- L28 _public enumerator_ `General`
- L29 _public enumerator_ `Performance`

#### struct `FLumenVisualizationMenuCommands::FLumenVisualizationRecord`  
`struct FLumenVisualizationRecord`  
_L32-44_
- L34 _public member_ `FName Name;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L36 _public member_ `FLumenVisualizationType Type;`
- L38 _public function_ `FLumenVisualizationRecord() : Name() , Command() , Type(FLumenVisualizationType::Overview)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/MegaLightsVisualizationMenuCommands.h` (Public)


#### class `FMegaLightsVisualizationMenuCommands`  
`class FMegaLightsVisualizationMenuCommands : public TCommands<FMegaLightsVisualizationMenuCommands>`  
_L23-76_
- inherits: `TCommands<FMegaLightsVisualizationMenuCommands>`
- L48 _public typedef_ `typedef TMultiMap<FName, FMegaLightsVisualizationRecord> TMegaLightsVisualizationModeCommandMap;`
- L49 _public typedef_ `typedef TMegaLightsVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L51 _public prototype_ `FMegaLightsVisualizationMenuCommands();`
- L53 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L55 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu, TWeakPtr<SLevelViewport> WeakViewport);`
- L57 _public prototype_ `virtual void RegisterCommands() override;`
- L59 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L61 _public function_ `inline bool IsPopulated() const`
- L67 _private prototype_ `void BuildCommandMap();`
- L68 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const EMegaLightsVisualizationType Type, TWeakPtr<SLevelViewport> WeakViewport) const;`
- L70 _private prototype_ `static void ChangeMegaLightsVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L71 _private prototype_ `static bool IsMegaLightsVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L74 _private member_ `TMegaLightsVisualizationModeCommandMap CommandMap;`
- L75 _private member_ `int32 TypeCommandCounts[int32(EMegaLightsVisualizationType::Count)];`

#### enum `FMegaLightsVisualizationMenuCommands::EMegaLightsVisualizationType`  
`enum class EMegaLightsVisualizationType : uint8`  
_L26-32_
- L28 _public enumerator_ `Overview`
- L29 _public enumerator_ `General`
- L30 _public enumerator_ `LightComplexity`
- L31 _public enumerator_ `Count`

#### struct `FMegaLightsVisualizationMenuCommands::FMegaLightsVisualizationRecord`  
`struct FMegaLightsVisualizationRecord`  
_L34-46_
- L36 _public member_ `FName Name;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L38 _public member_ `EMegaLightsVisualizationType Type;`
- L40 _public function_ `FMegaLightsVisualizationRecord() : Name() , Command() , Type(EMegaLightsVisualizationType::Overview)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/NaniteVisualizationMenuCommands.h` (Public)


#### class `FNaniteVisualizationMenuCommands`  
`class FNaniteVisualizationMenuCommands : public TCommands<FNaniteVisualizationMenuCommands>`  
_L22-73_
- inherits: `TCommands<FNaniteVisualizationMenuCommands>`
- L46 _public typedef_ `typedef TMultiMap<FName, FNaniteVisualizationRecord> TNaniteVisualizationModeCommandMap;`
- L47 _public typedef_ `typedef TNaniteVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L49 _public prototype_ `FNaniteVisualizationMenuCommands();`
- L51 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L53 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L55 _public prototype_ `virtual void RegisterCommands() override;`
- L57 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L59 _public function_ `inline bool IsPopulated() const`
- L65 _private prototype_ `void BuildCommandMap();`
- L66 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const FNaniteVisualizationType Type) const;`
- L68 _private prototype_ `static void ChangeNaniteVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L69 _private prototype_ `static bool IsNaniteVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L72 _private member_ `TNaniteVisualizationModeCommandMap CommandMap;`

#### enum `FNaniteVisualizationMenuCommands::FNaniteVisualizationType`  
`enum class FNaniteVisualizationType : uint8`  
_L25-30_
- L27 _public enumerator_ `Overview`
- L28 _public enumerator_ `Standard`
- L29 _public enumerator_ `Advanced`

#### struct `FNaniteVisualizationMenuCommands::FNaniteVisualizationRecord`  
`struct FNaniteVisualizationRecord`  
_L32-44_
- L34 _public member_ `FName Name;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L36 _public member_ `FNaniteVisualizationType Type;`
- L38 _public function_ `FNaniteVisualizationRecord() : Name() , Command() , Type(FNaniteVisualizationType::Overview)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/RayTracingDebugVisualizationMenuCommands.h` (Public)


#### class `FRayTracingDebugVisualizationMenuCommands`  
`class FRayTracingDebugVisualizationMenuCommands : public TCommands<FRayTracingDebugVisualizationMenuCommands>`  
_L20-80_
- inherits: `TCommands<FRayTracingDebugVisualizationMenuCommands>`
- L46 _public typedef_ `typedef TMultiMap<FName, FVisualizationRecord> TVisualizationModeCommandMap;`
- L47 _public typedef_ `typedef TVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L49 _public prototype_ `FRayTracingDebugVisualizationMenuCommands();`
- L51 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L53 _public prototype_ `static void BuildVisualisationSubMenu(UToolMenu* InMenu);`
- L55 _public prototype_ `virtual void RegisterCommands() override;`
- L57 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L59 _public function_ `inline bool IsPopulated() const`
- L65 _private prototype_ `void BuildCommandMap();`
- L67 _private prototype_ `bool AddCommandTypeToSection(FToolMenuSection& InSection, const FVisualizationType Type) const;`
- L68 _private prototype_ `bool AddLayersSection(UToolMenu& InMenu) const;`
- L69 _private prototype_ `bool AddOptionsSection(UToolMenu& InMenu) const;`
- L71 _private prototype_ `static void ChangeRayTracingDebugVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L72 _private prototype_ `static bool IsRayTracingDebugVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L74 _private member_ `TVisualizationModeCommandMap CommandMap;`
- L76 _private member_ `TSharedPtr<FUICommandInfo> ShowNearFieldCommand;`
- L77 _private member_ `TSharedPtr<FUICommandInfo> ShowFarFieldCommand;`
- L79 _private member_ `TSharedPtr<FUICommandInfo> ShowOpaqueOnlyCommand;`

#### enum `FRayTracingDebugVisualizationMenuCommands::FVisualizationType`  
`enum class FVisualizationType : uint8`  
_L23-30_
- L25 _public enumerator_ `Overview`
- L26 _public enumerator_ `Standard`
- L27 _public enumerator_ `Performance`
- L28 _public enumerator_ `Timing`
- L29 _public enumerator_ `Other`

#### struct `FRayTracingDebugVisualizationMenuCommands::FVisualizationRecord`  
`struct FVisualizationRecord`  
_L32-44_
- L34 _public member_ `FName Name;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L36 _public member_ `FVisualizationType Type;`
- L38 _public function_ `FVisualizationRecord() : Name() , Command() , Type(FVisualizationType::Overview)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/ShowFlagFilter.h` (Public)


#### class `FShowFlagFilter`  
`class FShowFlagFilter`  
_L15-98_
- L65 _public prototype_ `explicit FShowFlagFilter(EDefaultMode InDefaultMode);`
- L73 _public prototype_ `FShowFlagFilter& IncludeFlag(FEngineShowFlags::EShowFlag Flag);` — Operations (earlier = higher priority): - Include all explicitly included flags. - Exclude all explicitly excluded flags. - Include all flags in the include groups. - Exclude all flags in the exclude groups. - Include or exclude remaining flags depending on the default mode.
- L74 _public prototype_ `FShowFlagFilter& ExcludeFlag(FEngineShowFlags::EShowFlag Flag);`
- L75 _public prototype_ `FShowFlagFilter& IncludeGroup(EShowFlagGroup Group);`
- L76 _public prototype_ `FShowFlagFilter& ExcludeGroup(EShowFlagGroup Group);`
- L78 _public prototype_ `const FGroupedShowFlagIndices& GetFilteredIndices(bool bForceRebuild = false) const;`
- L81 _private prototype_ `bool ShouldIncludeFlag(const FShowFlagData& Flag) const;`
- L82 _private prototype_ `void RebuildIndexArray() const;`
- L84 _private member_ `EDefaultMode DefaultMode;`
- L88 _private member_ `TArray<EShowFlagGroup> IncludedGroups;` — These don't need to be maps/sets because the number of groups is small and we'll get cache benefit from the array.
- L89 _private member_ `TArray<EShowFlagGroup> ExcludedGroups;`
- L91 _private member_ `TSet<FEngineShowFlags::EShowFlag> IncludedFlags;`
- L92 _private member_ `TSet<FEngineShowFlags::EShowFlag> ExcludedFlags;`
- L96 _private member_ `mutable FGroupedShowFlagIndices AllowedFlagIndices;` — Flags that have passed the filtering. These are indices into the GetShowFlagMenuItems() array.
- L97 _private member_ `mutable bool bHaveFiltered;`

#### enum `FShowFlagFilter::EDefaultMode`  
`enum EDefaultMode`  
_L18-22_
- L20 _public enumerator_ `IncludeAllFlagsByDefault`
- L21 _public enumerator_ `ExcludeAllFlagsByDefault`

#### struct `FShowFlagFilter::FGroupedShowFlagIndices`  
`struct FGroupedShowFlagIndices`  
_L24-63_
- L26 _public function_ `inline FGroupedShowFlagIndices() : GroupedIndices`
- L31 _public function_ `inline TArray<uint32>& operator [](EShowFlagGroup Group)`
- L36 _public function_ `inline const TArray<uint32>& operator [](EShowFlagGroup Group) const`
- L41 _public function_ `inline void ClearAll()`
- L49 _public function_ `inline int32 TotalIndices() const`
- L62 _private member_ `TArray<uint32> GroupedIndices[SFG_Max];`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/ShowFlagMenuCommands.h` (Public)


#### class `FShowFlagMenuCommands`  
`class FShowFlagMenuCommands : public TCommands<FShowFlagMenuCommands>`  
_L29-84_
- inherits: `TCommands<FShowFlagMenuCommands>`
- L53 _public prototype_ `FShowFlagMenuCommands();`
- L55 _public prototype_ `virtual void RegisterCommands() override;`
- L57 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L58 _public prototype_ `void BuildShowFlagsMenu(UToolMenu* Menu, const FShowFlagFilter& Filter = FShowFlagFilter(FShowFlagFilter::IncludeAllFlagsByDefault)) const;`
- L60 _public prototype_ `void PopulateCommonShowFlagsSection( FToolMenuSection& Section, const FShowFlagFilter& Filter = FShowFlagFilter(FShowFlagFilter::IncludeAllFlagsByDefault) ) const;`
- L63 _public prototype_ `void PopulateAllShowFlagsSection( FToolMenuSection& Section, const FShowFlagFilter& Filter = FShowFlagFilter(FShowFlagFilter::IncludeAllFlagsByDefault) ) const;`
- L67 _public prototype_ `const TArray<FShowFlagCommand>& GetCommands() const;`
- L68 _public prototype_ `TSharedPtr<const FUICommandInfo> FindCommandForFlag(FEngineShowFlags::EShowFlag FlagIndex) const;`
- L71 _private prototype_ `static void StaticCreateShowFlagsSubMenu(UToolMenu* Menu, TArray<uint32> FlagIndices, int32 EntryOffset);`
- L72 _private prototype_ `static void ToggleShowFlag(TWeakPtr<FEditorViewportClient> WeakClient, FEngineShowFlags::EShowFlag EngineShowFlagIndex);`
- L73 _private prototype_ `static bool IsShowFlagEnabled(TWeakPtr<FEditorViewportClient> WeakClient, FEngineShowFlags::EShowFlag EngineShowFlagIndex);`
- L75 _private prototype_ `FSlateIcon GetShowFlagIcon(const FShowFlagData& Flag) const;`
- L77 _private prototype_ `void CreateShowFlagCommands();`
- L78 _private prototype_ `void UpdateCustomShowFlags() const;`
- L79 _private prototype_ `void CreateSubMenuIfRequired(FToolMenuSection& Section, const FShowFlagFilter& Filter, EShowFlagGroup Group, const FName SubMenuName, const FText& MenuLabel, const FText& ToolTip, const FName IconName) const;`
- L80 _private prototype_ `void CreateShowFlagsSubMenu(UToolMenu* Menu, TArray<uint32> MenuCommands, int32 EntryOffset) const;`
- L82 _private member_ `TArray<FShowFlagCommand> ShowFlagCommands;`
- L83 _private member_ `bool bCommandsInitialised;`

#### struct `FShowFlagMenuCommands::FShowFlagCommand`  
`struct FShowFlagCommand`  
_L32-51_
- L34 _public member_ `FEngineShowFlags::EShowFlag FlagIndex;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ShowMenuItem;`
- L36 _public member_ `FText LabelOverride;`
- L38 _public function_ `FShowFlagCommand(FEngineShowFlags::EShowFlag InFlagIndex, const TSharedPtr<FUICommandInfo>& InShowMenuItem, const FText& InLabelOverride) : FlagIndex(InFlagIndex), ShowMenuItem(InShowMenuItem), LabelOverride(InLabelOverride)`
- L45 _public function_ `FShowFlagCommand(FEngineShowFlags::EShowFlag InFlagIndex, const TSharedPtr<FUICommandInfo>& InShowMenuItem) : FlagIndex(InFlagIndex), ShowMenuItem(InShowMenuItem), LabelOverride()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/SubstrateVisualizationMenuCommands.h` (Public)


#### class `FSubstrateVisualizationMenuCommands`  
`class FSubstrateVisualizationMenuCommands : public TCommands<FSubstrateVisualizationMenuCommands>`  
_L23-60_
- inherits: `TCommands<FSubstrateVisualizationMenuCommands>`
- L33 _public typedef_ `typedef TMultiMap<FName, FSubstrateVisualizationRecord> TSubstrateVisualizationModeCommandMap;`
- L34 _public typedef_ `typedef TSubstrateVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L36 _public prototype_ `FSubstrateVisualizationMenuCommands();`
- L38 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L40 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L42 _public prototype_ `virtual void RegisterCommands() override;`
- L44 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L46 _public function_ `inline bool IsPopulated() const`
- L52 _private prototype_ `void BuildCommandMap();`
- L53 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const FSubstrateViewMode ViewMode) const;`
- L55 _private prototype_ `static void ChangeSubstrateVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L56 _private prototype_ `static bool IsSubstrateVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L59 _private member_ `TSubstrateVisualizationModeCommandMap CommandMap;`

#### struct `FSubstrateVisualizationMenuCommands::FSubstrateVisualizationRecord`  
`struct FSubstrateVisualizationRecord`  
_L26-31_
- L28 _public member_ `FName Name;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L30 _public member_ `FSubstrateViewMode ViewMode = FSubstrateViewMode::MaterialProperties;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/VirtualShadowMapVisualizationMenuCommands.h` (Public)


#### class `FVirtualShadowMapVisualizationMenuCommands`  
`class FVirtualShadowMapVisualizationMenuCommands : public TCommands<FVirtualShadowMapVisualizationMenuCommands>`  
_L22-76_
- inherits: `TCommands<FVirtualShadowMapVisualizationMenuCommands>`
- L46 _public typedef_ `typedef TMultiMap<FName, FVirtualShadowMapVisualizationRecord> TVirtualShadowMapVisualizationModeCommandMap;`
- L47 _public typedef_ `typedef TVirtualShadowMapVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L49 _public prototype_ `FVirtualShadowMapVisualizationMenuCommands();`
- L51 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L53 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L55 _public prototype_ `virtual void RegisterCommands() override;`
- L57 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L59 _public function_ `inline bool IsPopulated() const`
- L65 _private prototype_ `void BuildCommandMap();`
- L66 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const FVirtualShadowMapVisualizationType Type, bool bSeparatorBefore = false) const;`
- L68 _private prototype_ `static void ChangeVirtualShadowMapVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L69 _private prototype_ `static bool IsVirtualShadowMapVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L72 _private member_ `TVirtualShadowMapVisualizationModeCommandMap CommandMap;`
- L73 _private member_ `TSharedPtr<FUICommandInfo> ShowStatsCommand;`
- L74 _private member_ `TSharedPtr<FUICommandInfo> VisualizeNextLightCommand;`
- L75 _private member_ `TSharedPtr<FUICommandInfo> VisualizePrevLightCommand;`

#### enum `FVirtualShadowMapVisualizationMenuCommands::FVirtualShadowMapVisualizationType`  
`enum class FVirtualShadowMapVisualizationType : uint8`  
_L26-30_
- desc: Re-sort into categories for the menu
- L28 _public enumerator_ `Standard`
- L29 _public enumerator_ `Advanced`

#### struct `FVirtualShadowMapVisualizationMenuCommands::FVirtualShadowMapVisualizationRecord`  
`struct FVirtualShadowMapVisualizationRecord`  
_L32-44_
- L34 _public member_ `FName Name;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L36 _public member_ `FVirtualShadowMapVisualizationType Type;`
- L38 _public function_ `FVirtualShadowMapVisualizationRecord() : Name() , Command() , Type(FVirtualShadowMapVisualizationType::Standard)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`

### `Source/Editor/CommonMenuExtensions/Public/VirtualTextureVisualizationMenuCommands.h` (Public)


#### class `FVirtualTextureVisualizationMenuCommands`  
`class FVirtualTextureVisualizationMenuCommands : public TCommands<FVirtualTextureVisualizationMenuCommands>`  
_L21-58_
- inherits: `TCommands<FVirtualTextureVisualizationMenuCommands>`
- L31 _public typedef_ `typedef TMultiMap<FName, FVisualizationRecord> TVisualizationModeCommandMap;`
- L32 _public typedef_ `typedef TVisualizationModeCommandMap::TConstIterator TCommandConstIterator;`
- L34 _public prototype_ `FVirtualTextureVisualizationMenuCommands();`
- L36 _public prototype_ `TCommandConstIterator CreateCommandConstIterator() const;`
- L38 _public prototype_ `static void BuildVisualisationSubMenu(FMenuBuilder& Menu);`
- L40 _public prototype_ `virtual void RegisterCommands() override;`
- L42 _public prototype_ `void BindCommands(FUICommandList& CommandList, const TSharedPtr<FEditorViewportClient>& Client) const;`
- L44 _public function_ `inline bool IsPopulated() const`
- L50 _private prototype_ `void BuildCommandMap();`
- L51 _private prototype_ `bool AddCommandTypeToMenu(FMenuBuilder& Menu, const EVirtualTextureVisualizationMode ModeID) const;`
- L53 _private prototype_ `static void ChangeVisualizationMode(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L54 _private prototype_ `static bool IsVisualizationModeSelected(TWeakPtr<FEditorViewportClient> WeakClient, FName InName);`
- L57 _private member_ `TVisualizationModeCommandMap CommandMap;`

#### struct `FVirtualTextureVisualizationMenuCommands::FVisualizationRecord`  
`struct FVisualizationRecord`  
_L24-29_
- L26 _public member_ `FName Name;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> Command;`
- L28 _public member_ `EVirtualTextureVisualizationMode ModeID;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONMENUEXTENSIONS_API`
