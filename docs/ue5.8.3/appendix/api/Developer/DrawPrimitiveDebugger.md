# Developer / DrawPrimitiveDebugger

- module root: `Source/Developer/DrawPrimitiveDebugger`
- headers: 3; symbols: 168
- symbol kinds: class=5, delegate=1, function=7, macro=2, member=44, prototype=107, struct=1, typedef=1
- PrivateDependencyModuleNames: DeveloperSettings, InputCore, RHI, RenderCore, Renderer, Slate, SlateCore
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Developer/DrawPrimitiveDebugger/Private/SDrawPrimitiveDebugger.h` (Private)


#### class `SPrimitiveDebuggerDetailView`  
`class SPrimitiveDebuggerDetailView : public SCompoundWidget`  
_L24-118_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SPrimitiveDebuggerDetailView)`
- L29 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SDrawPrimitiveDebugger>, PrimitiveDebugger) SLATE_END_ARGS() virtual ~SPrimitiveDebuggerDetailView() override;` — The primitive we're currently focused on.
- L35 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L37 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L39 _public prototype_ `void UpdateSelection();`
- L40 _public prototype_ `void ReleaseSelection();`
- L44 _private member_ `TWeakPtr<SDrawPrimitiveDebugger> PrimitiveDebugger;`
- L45 _private member_ `TSharedPtr<SVerticalBox> DetailPropertiesWidget;`
- L46 _private member_ `TSharedPtr<SVerticalBox> MaterialsWidget;`
- L47 _private member_ `TSharedPtr<SVerticalBox> AdvancedOptionsWidget;`
- L48 _private member_ `TSharedPtr<SVerticalBox> SkeletalMeshDetailsWidget;`
- L50 _private member_ `bool bSelectionSupportsNanite = false;`
- L51 _private member_ `bool bSelectionIsNaniteEnabledThisFrame = false;`
- L53 _private member_ `FText SelectedActorName;`
- L54 _private member_ `FText SelectedActorPath;`
- L55 _private member_ `FText SelectedActorClassName;`
- L56 _private member_ `FText SelectedActorClassPath;`
- L57 _private member_ `FText SelectedPrimitiveType;`
- L59 _private member_ `TWeakObjectPtr<UStaticMeshComponent> SelectedAsStaticMesh = nullptr;`
- L60 _private member_ `TWeakObjectPtr<USkinnedMeshComponent> SelectedAsSkinnedMesh = nullptr;`
- L61 _private member_ `UClass* SelectedComponentType = nullptr;`
- L63 _private member_ `const FPrimitiveLODStats* CurrentLOD = nullptr;`
- L64 _private member_ `int32 PlayerIndex = 0;`
- L65 _private member_ `int32 ViewIndex = 0;`
- L67 _private prototype_ `FText GetSelectedPrimitiveName() const;`
- L68 _private prototype_ `FText GetSelectedPrimitiveType() const;`
- L69 _private prototype_ `FText GetSelectedActorName() const;`
- L70 _private prototype_ `FText GetSelectedActorToolTip() const;`
- L71 _private prototype_ `FText GetSelectedActorClassName() const;`
- L72 _private prototype_ `FText GetSelectedActorClassToolTip() const;`
- L73 _private prototype_ `FText GetSelectedPrimitiveNaniteEnabled() const;`
- L74 _private prototype_ `FText GetSelectedPrimitiveSupportsNanite() const;`
- L75 _private prototype_ `FText GetSelectedDrawCallCount() const;`
- L76 _private prototype_ `FText GetSelectedLocation() const;`
- L77 _private prototype_ `FText GetSelectedLOD() const;`
- L78 _private prototype_ `FText GetSelectedNumLODs() const;`
- L79 _private prototype_ `TOptional<int> GetSelectedLODValue() const;`
- L80 _private prototype_ `TOptional<int> GetSelectedForcedLODValue() const;`
- L81 _private prototype_ `TOptional<int> GetSelectedNumLODsValue() const;`
- L82 _private prototype_ `TOptional<int> GetSelectedForcedLODSliderMaxValue() const;`
- L83 _private prototype_ `FText GetSelectedTriangleCount() const;`
- L84 _private prototype_ `FText GetSelectedBoneCount() const;`
- L86 _private prototype_ `void GenerateDetailPanelEntry(const FText& Label, FText (SPrimitiveDebuggerDetailView::* ValueGetter)() const, EVisibility (SPrimitiveDebuggerDetailView::* VisibilityGetter)() const = nullptr, FText (SPrimitiveDebuggerDetailView::* TooltipGetter)() const = nullptr, bool bSupportHighlighting = false) const;`
- L92 _private prototype_ `TSharedRef<SVerticalBox> GetSelectedMaterialsWidget();`
- L93 _private prototype_ `TSharedRef<SVerticalBox> GetAdvancedOptionsWidget();`
- L95 _private prototype_ `EVisibility OptionVisibilityForceLOD() const;`
- L96 _private prototype_ `EVisibility OptionVisibilityForceDisableNanite() const;`
- L98 _private prototype_ `ECheckBoxState ForceLODState() const;`
- L99 _private prototype_ `bool IsForceLODIndexSliderEnabled() const;`
- L100 _private prototype_ `void OnToggleForceLOD(ECheckBoxState state);`
- L101 _private prototype_ `void HandleForceLOD(int ForcedLOD);`
- L103 _private prototype_ `ECheckBoxState ShowDebugBoundsState() const;`
- L104 _private prototype_ `void OnToggleDebugBounds(ECheckBoxState state);`
- L106 _private prototype_ `ECheckBoxState ForceDisableNaniteState() const;`
- L107 _private prototype_ `void OnToggleForceDisableNanite(ECheckBoxState state);`
- L109 _private prototype_ `EVisibility StaticMeshDataVisibility() const;`
- L110 _private prototype_ `EVisibility SkeletalMeshDataVisibility() const;`
- L111 _private prototype_ `ECheckBoxState ShowDebugBonesState() const;`
- L112 _private prototype_ `void OnToggleDebugBones(ECheckBoxState state);`
- L114 _private prototype_ `EVisibility NaniteDataVisibility() const;`
- L115 _private prototype_ `EVisibility NonNaniteDataVisibility() const;`
- L117 _private prototype_ `void CreateMaterialEntry(const UMaterialInterface* MI, int Index, bool bIsOverlay = false);`

#### class `SDrawPrimitiveDebugger`  
`class SDrawPrimitiveDebugger : public SCompoundWidget`  
_L120-235_
- inherits: `SCompoundWidget`
- L123 _public function_ `SLATE_BEGIN_ARGS(SDrawPrimitiveDebugger)`
- L129 _public prototype_ `virtual ~SDrawPrimitiveDebugger() override;`
- L132 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L134 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L136 _public prototype_ `FText GetFilterText() const;`
- L137 _public prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L138 _public prototype_ `void OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L140 _public prototype_ `TSharedRef<ITableRow> MakeRowWidget(FPrimitiveRowDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L141 _public prototype_ `void OnRowSelectionChanged(FPrimitiveRowDataPtr InNewSelection, ESelectInfo::Type InSelectInfo);`
- L142 _public prototype_ `void UpdateVisibleRows();`
- L143 _public prototype_ `void SortRows();`
- L144 _public prototype_ `void Refresh();`
- L145 _public prototype_ `void ClearAllEntries();`
- L146 _public prototype_ `void SetActiveWorld(UWorld* World);`
- L147 _public prototype_ `void RemoveEntry(FPrimitiveRowDataPtr Entry);`
- L148 _public prototype_ `void AddColumn(const FText& Name, const FName& ColumnId);`
- L150 _public prototype_ `void OnChangeEntryVisibility(ECheckBoxState state, FPrimitiveRowDataPtr Data);`
- L151 _public prototype_ `bool IsEntryVisible(FPrimitiveComponentId EntryId) const;`
- L152 _public prototype_ `bool IsEntryVisible(FPrimitiveRowDataPtr Data) const;`
- L153 _public prototype_ `void OnChangeEntryPinned(ECheckBoxState State, FPrimitiveRowDataPtr Data);`
- L154 _public prototype_ `bool IsEntryPinned(FPrimitiveComponentId EntryId) const;`
- L155 _public prototype_ `bool IsEntryPinned(FPrimitiveRowDataPtr Data) const;`
- L157 _public prototype_ `void SetForcedLODForEntry(FPrimitiveComponentId EntryId, int32 NewForcedLOD);`
- L158 _public prototype_ `void ResetForcedLODForEntry(FPrimitiveComponentId EntryId);`
- L159 _public prototype_ `bool DoesEntryHaveForcedLOD(FPrimitiveComponentId EntryId) const;`
- L160 _public prototype_ `void SetForceDisabledNaniteForEntry(FPrimitiveComponentId EntryId, bool bForceDisableNanite);`
- L162 _public prototype_ `void SetShowDebugBoundsForEntry(FPrimitiveComponentId EntryId, bool bShowDebugBounds);`
- L163 _public prototype_ `bool IsEntryShowingDebugBounds(FPrimitiveComponentId EntryId) const;`
- L164 _public prototype_ `void RedrawAllDebugBounds() const;`
- L165 _public prototype_ `void FlushAllDebugBounds();`
- L167 _public prototype_ `void SetShowDebugBonesForEntry(FPrimitiveComponentId EntryId, bool bShowDebugBones);`
- L168 _public prototype_ `bool IsEntryShowingDebugBones(FPrimitiveComponentId EntryId) const;`
- L169 _public prototype_ `void FlushAllDebugBones();`
- L171 _public prototype_ `void FlushDebugVisualizationsForEntry(FPrimitiveComponentId EntryId);`
- L172 _public prototype_ `void FlushAllDebugVisualizations();`
- L175 _public prototype_ `void ResetDebuggerChanges();` — Resets any changes made to the scene by the debugger and clears all debugger related debug visualizations.
- L177 _public prototype_ `bool CanCaptureSingleFrame() const;`
- L178 _public prototype_ `FReply OnRefreshClick();`
- L179 _public prototype_ `FReply OnSaveClick();`
- L180 _public prototype_ `ECheckBoxState IsLiveCaptureChecked() const;`
- L181 _public prototype_ `void OnToggleLiveCapture(ECheckBoxState State);`
- L182 _public prototype_ `FPrimitiveRowDataPtr GetCurrentSelection() const;`
- L183 _public prototype_ `FPrimitiveComponentId GetCurrentSelectionId() const;`
- L184 _public prototype_ `EVisibility DetailsPanelVisibility() const;`
- L216 _private member_ `TMap<FPrimitiveComponentId, FPrimitiveDebuggerEntry> Entries;`
- L219 _private member_ `TSharedPtr<SPrimitiveDebuggerDetailView> DetailView;`
- L220 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L221 _private member_ `TSharedPtr<SListView<FPrimitiveRowDataPtr>> Table;`
- L222 _private member_ `FText FilterText;`
- L223 _private member_ `TSharedPtr<SHeaderRow> ColumnHeader;`
- L224 _private member_ `TArray<FPrimitiveRowDataPtr> AvailableEntries;`
- L225 _private member_ `TArray<FPrimitiveRowDataPtr> VisibleEntries;`
- L226 _private member_ `TWeakObjectPtr<UWorld> ActiveWorld;`
- L227 _private member_ `FDelegateHandle ActorComponentsUnregisteredHandle;`
- L229 _private member_ `FPrimitiveDebuggerEntry* Selection = nullptr;`
- L232 _private member_ `TSet<FPrimitiveComponentId> EntriesShowingDebugBounds;` — We keep an extra list of primitives with debug bounds to avoid unnecessary cycles during Tick when updating bounds lines
- L234 _private prototype_ `void HandleActorCleanup(AActor* Actor);`

#### struct `SDrawPrimitiveDebugger::FPrimitiveDebuggerEntry`  
`struct FPrimitiveDebuggerEntry`  
_L188-214_
- L190 _public member_ `FPrimitiveRowDataPtr Data;`
- L192 _public member_ `uint8 bHidden : 1;`
- L193 _public member_ `uint8 bPinned : 1;`
- L194 _public member_ `uint8 bSelected : 1;`
- L195 _public member_ `uint8 bShowingDebugBounds : 1;`
- L196 _public member_ `uint8 bShowingDebugBones : 1;`
- L197 _public member_ `uint8 bHasForcedLOD : 1;`
- L198 _public member_ `uint8 bHasForceDisabledNanite : 1;`
- L199 _public member_ `uint8 bRetainDuringRefresh : 1;`
- L203 _public member_ `int32 DesiredForcedLOD;`
- L204 _public member_ `bool bDesiredForceDisabledNaniteState;`
- L206 _public prototype_ `FPrimitiveDebuggerEntry(const FPrimitiveRowDataPtr& Data = nullptr);`
- L207 _public prototype_ `FPrimitiveDebuggerEntry(const FViewDebugInfo::FPrimitiveInfo& Primitive);`
- L209 _public prototype_ `FPrimitiveDebuggerEntry(const FPrimitiveDebuggerEntry& Other) = default;`
- L210 _public prototype_ `FPrimitiveDebuggerEntry(FPrimitiveDebuggerEntry&& Other) noexcept = default;`
- L212 _public prototype_ `FPrimitiveDebuggerEntry& operator=(const FPrimitiveDebuggerEntry& RHS) = default;`
- L213 _public prototype_ `FPrimitiveDebuggerEntry& operator=(FPrimitiveDebuggerEntry&& RHS) = default;`

#### class `SDrawPrimitiveDebuggerListViewRow`  
`class SDrawPrimitiveDebuggerListViewRow : public SMultiColumnTableRow<FPrimitiveRowDataPtr>`  
_L241-267_
- inherits: `SMultiColumnTableRow<FPrimitiveRowDataPtr>`
- desc: A widget to represent a row in a Data Table Editor widget. This widget allows us to do things like right-click and take actions on a particular row of a Data Table.
- L245 _public function_ `SLATE_BEGIN_ARGS(SDrawPrimitiveDebuggerListViewRow)`
- L249 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SDrawPrimitiveDebugger>, DrawPrimitiveDebugger) SLATE_ARGUMENT(FPrimitiveRowDataPtr, RowDataPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — The owning object. This allows us access to the actual data table being edited as well as some other API functions.
- L256 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L260 _private prototype_ `TSharedRef<SWidget> MakeCellWidget(const int32 InRowIndex, const FName& InColumnId);`
- L262 _private prototype_ `ECheckBoxState IsVisible() const;`
- L263 _private prototype_ `ECheckBoxState IsPinned() const;`
- L265 _private member_ `FPrimitiveRowDataPtr RowDataPtr;`
- L266 _private member_ `TWeakPtr<SDrawPrimitiveDebugger> DrawPrimitiveDebugger;`

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef TSharedPtr<const FViewDebugInfo::FPrimitiveInfo> FPrimitiveRowDataPtr;`

### `Source/Developer/DrawPrimitiveDebugger/Public/DrawPrimitiveDebugger.h` (Public)


#### class `IDrawPrimitiveDebugger`  
`class IDrawPrimitiveDebugger : public IModuleInterface`  
_L18-77_
- inherits: `IModuleInterface`
- L28 _public function_ `static inline IDrawPrimitiveDebugger& Get()` — Singleton-like access to this module's interface. This is just for convenience! Beware of calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L46 _public prototype_ `virtual void CaptureSingleFrame() = 0;` — Instructs the renderer to capture a snapshot for the debugger on the next frame.
- L52 _public prototype_ `virtual bool IsLiveCaptureEnabled() const = 0;` — Is live data capture enabled for the debugger? This implies that the renderer will capture debug data each frame. @return True if live capture is enabled.
- L57 _public prototype_ `virtual void EnableLiveCapture() = 0;` — Enables capturing debug data each frame.
- L61 _public prototype_ `virtual void DisableLiveCapture() = 0;` — Disables capturing debug data each frame.
- L66 _public prototype_ `virtual void DiscardCaptureData() = 0;` — Discards the current snapshot data in memory and resets the debugger window.
- L71 _public prototype_ `virtual void OpenDebugWindow() = 0;` — Opens the graphics debugger window if it is available.
- L75 _public prototype_ `virtual void CloseDebugWindow() = 0;` — Closes the graphics debugger window if it is currently open.

#### Free symbols / members of external scopes

- L14 _macro_ `#define WITH_PRIMITIVE_DEBUGGER !UE_BUILD_SHIPPING && !UE_SERVER`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDrawPrimitiveDebugger, All, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDrawPrimitiveDebugger, All, All);`

### `Source/Developer/DrawPrimitiveDebugger/Public/DrawPrimitiveDebuggerConfig.h` (Public)


#### class `UDrawPrimitiveDebuggerUserSettings`  
`class UDrawPrimitiveDebuggerUserSettings : public UDeveloperSettings`  
_L12-28_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings, meta = (DisplayName = "Draw Primitive Debugger"))`
- inherits: `UDeveloperSettings`
- L16 _protected function_ `virtual FName GetCategoryName() const override`
- L20 _public function_ `static int32 GetFontSize()`
- L21 _public prototype_ `static void SetFontSize(const int32 InFontSize);`
- L27 _protected member_ `int32 FontSize = 10;` — `UPROPERTY(config, EditAnywhere, Category = DrawPrimitiveDebugger)` — Font Size used by Draw Primitive Debugger

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DRAWPRIMITIVEDEBUGGER_API`
