# Editor / RewindDebuggerInterface

- module root: `Source/Editor/RewindDebuggerInterface`
- headers: 10; symbols: 247
- symbol kinds: class=11, enum=3, enumerator=8, function=90, macro=4, member=52, namespace=10, prototype=60, struct=9
- PrivateDependencyModuleNames: Slate, ToolWidgets
- PublicDependencyModuleNames: Core, CoreUObject, SlateCore

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebugger.h` (Public)


#### struct `FDebugObjectInfo`  
`struct FDebugObjectInfo`  
_L36-61_
- L38 _public prototype_ `FDebugObjectInfo() = default;`
- L39 _public function_ `FDebugObjectInfo(const RewindDebugger::FObjectId& Id, const FString& Name) : Id(Id) , ObjectName(Name) , bExpanded(true)`
- L47 _public function_ `uint64 GetUObjectId() const` — @return Part of the Id representing the UObject
- L52 _public member_ `RewindDebugger::FObjectId Id;`
- L53 _public member_ `FString ObjectName;`
- L54 _public member_ `TArray<TSharedPtr<FDebugObjectInfo>> Children;`
- L55 _public member_ `bool bExpanded = false;`
- L59 _public member_ `uint64 ObjectId = 0;` — `UE_DEPRECATED(5.7, "Use ObjectIdentifier instead")`

#### struct `FScrubTimeInformation`  
`struct FScrubTimeInformation`  
_L63-71_
- L66 _public member_ `double ElapsedTime = 0;` — Elapsed simulation/world time
- L68 _public member_ `double ProfileTime = 0;` — Profiling/Tracing time
- L70 _public member_ `int64 FrameIndex = 0;` — Scrub Frame Index

#### class `URewindDebuggerTrackContextMenuContext`  
`class URewindDebuggerTrackContextMenuContext : public UObject`  
_L74-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L78 _public member_ `TSharedPtr<FDebugObjectInfo> SelectedObject;`
- L79 _public member_ `TArray<FName> TypeHierarchy;`
- L80 _public member_ `TSharedPtr<RewindDebugger::FRewindDebuggerTrack> SelectedTrack;`

#### class `UComponentContextMenuContext`  
`class UE_DEPRECATED(5.7, "Use URewindDebuggerTrackContextMenuContext instead") UComponentContextMenuContext : public URewindDebuggerTrackContextMenuContext`  
_L83-85_
- inherits: `URewindDebuggerTrackContextMenuContext`

#### class `IRewindDebugger`  
`class IRewindDebugger`  
_L91-242_
- desc: IRewindDebugger Public interface to rewind debugger
- L94 _public prototype_ `IRewindDebugger();`
- L96 _public prototype_ `virtual ~IRewindDebugger();`
- L99 _public prototype_ `virtual bool CanStartRecording() const = 0;` — Whether the recording can be started.
- L102 _public prototype_ `virtual void StartRecording() const = 0;` — Start traces recording if not already started.
- L105 _public prototype_ `virtual double CurrentTraceTime() const = 0;` — @return the time the debugger is scrubbed to, in seconds since the capture started (or the recording duration while the game is running)
- L108 _public prototype_ `virtual double GetScrubTime() const = 0;` — @return the time the debugger is scrubbed to, in seconds since the recording started
- L111 _public prototype_ `virtual void SetScrubTime(double Time) = 0;` — Moves the scrub cursor to Time (seconds since the recording started), clamping to the recording range and disabling auto-scroll-with-recording.
- L114 _public prototype_ `virtual void CenterViewOnTime(double Time) = 0;` — Re-centers the visible view range on Time, preserving the current view width. Independent of the scrub cursor.
- L117 _public prototype_ `virtual const TRange<double>& GetCurrentTraceRange() const = 0;` — @return the current visible range in trace/profiler units (same units as CurrentTraceTime)
- L120 _public prototype_ `virtual const TRange<double>& GetCurrentViewRange() const = 0;` — @return the current visible range in Rewind Debugger recording time units
- L126 _public prototype_ `virtual TSharedPtr<UE::TraceBasedDebuggers::FSessionInfo> GetSelectedDebugSessionInfo() const = 0;` — Returns shared pointer to the selected debug session (PIE or remote). @return the currently selected debug session
- L134 _public prototype_ `virtual const TraceServices::IAnalysisSession* GetAnalysisSession() const = 0;` — Returns pointer to the current analysis sessions for immediate access. If the goal is to store in a variable for later access then GetAnalysisSessionAsShared should be used instead. @return the current analysis session @see GetAnalysisSessionAsShared
- L140 _public prototype_ `virtual TSharedPtr<const TraceServices::IAnalysisSession> GetAnalysisSessionAsShared() const = 0;` — Returns shared pointer to the current analysis sessions. @return the current analysis session
- L143 _public prototype_ `virtual uint64 GetRootObjectId() const = 0;` — @return insights id for the root object currently debugged
- L146 _public function_ `virtual uint64 GetTargetActorId() const final` — `UE_DEPRECATED(5.7, "Use GetRootObjectId instead")`
- L152 _public prototype_ `virtual TArray<TSharedPtr<FDebugObjectInfo>>& GetDebuggedObjects() = 0;` — @return list of all objects associated to the active tracks
- L155 _public function_ `virtual TArray<TSharedPtr<FDebugObjectInfo>>& GetDebugComponents() final` — `UE_DEPRECATED(5.7, "Use GetDebuggedObjects instead")`
- L165 _public prototype_ `virtual void SetObjectToDebug(RewindDebugger::FObjectId ObjectId) = 0;` — Sets the object to display tracks for. Method will do nothing uf the specified object is already part of the current object hierarchy. @param ObjectId The Id of the object to debug
- L168 _public prototype_ `virtual bool IsObjectCurrentlyDebugged(uint64 InObjectId) const = 0;` — @return Whether the given object id is one of the object currently debugged, or one of its children.
- L171 _public function_ `virtual bool IsContainedByDebugComponent(uint64 InObjectId) const final` — `UE_DEPRECATED(5.7, "Use IsObjectCurrentlyDebugged instead")`
- L177 _public prototype_ `virtual TSharedPtr<FDebugObjectInfo> GetSelectedObject() const = 0;` — @return the currently selected debug object
- L180 _public prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> GetSelectedTrack() const = 0;` — @return the currently selected track
- L183 _public prototype_ `virtual void SelectTrack(RewindDebugger::FObjectId ObjectId) = 0;` — Try selecting the track associated to a given object
- L186 _public prototype_ `virtual bool GetRootObjectPosition(FVector& OutPosition) const = 0;` — @return position of the root object being debugged (returns true if position is valid)
- L189 _public prototype_ `virtual void SetRootObjectPosition(const TOptional<FVector>& InPosition) = 0;` — Stores position of the root object being debugged
- L192 _public function_ `virtual bool GetTargetActorPosition(FVector& OutPosition) const final` — `UE_DEPRECATED(5.7, "Use GetRootObjectPosition instead")`
- L198 _public prototype_ `virtual UWorld* GetWorldToVisualize() const = 0;` — @return the world that the debugger is replaying in
- L201 _public prototype_ `virtual bool IsRecording() const = 0;` — @return whether the recording is active
- L205 _public function_ `virtual bool IsTraceFileLoaded() const final` — `UE_DEPRECATED(5.8, "Method is no longer used and will be removed.")` — @return whether a trace file is loaded from disk
- L211 _public prototype_ `virtual bool IsPIESimulating() const = 0;` — @return PIE is running and not paused
- L214 _public prototype_ `virtual double GetRecordingDuration() const = 0;` — @return the length of the current recording
- L217 _public prototype_ `virtual void OpenDetailsPanel() = 0;` — Opens the Rewind Debugger details panel tab
- L221 _public function_ `template <typename T> const FObjectInfo* FindTypedOuterInfo(TNotNull<const IGameplayProvider*> GameplayProvider, uint64 ObjectId) const` — @return the object information of the first object inheriting from the specified type in the outer chain of ObjectId
- L227 _public prototype_ `virtual const FObjectInfo* FindTypedOuterInfo(TNotNull<const UStruct*> Type, TNotNull<const IGameplayProvider*> GameplayProvider, uint64 ObjectId) const = 0;` — @return the object information of the first object inheriting from the specified type in the outer chain of ObjectId
- L230 _public function_ `virtual const FObjectInfo* FindOwningActorInfo(const IGameplayProvider* GameplayProvider, uint64 ObjectId) const final` — `UE_DEPRECATED(5.7, "Use FindTypedOuterInfo instead")`
- L235 _public prototype_ `virtual bool ShouldDisplayWorld(uint64 WorldId) = 0;`
- L238 _public prototype_ `static IRewindDebugger* Instance();` — @return the current IRewindDebugger instance
- L241 _protected member_ `static IRewindDebugger* InternalInstance;`

#### Free symbols / members of external scopes

- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRewindDebugger, Log, All);`
- L18 _namespace_ `namespace TraceServices`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L28 _namespace_ `namespace RewindDebugger`

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebuggerDoubleClickHandler.h` (Public)


#### class `IRewindDebuggerDoubleClickHandler`  
`class IRewindDebuggerDoubleClickHandler : public IModularFeature`  
_L12-22_
- inherits: `IModularFeature`
- desc: Interface class for adding custom double click handling to components
- L15 _public member_ `static const FName ModularFeatureName;`
- L18 _public prototype_ `virtual FName GetTargetTypeName() const = 0;` — returns the name of a type of UObject for which this menu extender will be called
- L21 _public prototype_ `virtual bool HandleDoubleClick(IRewindDebugger* IRewindDebugger) = 0;` — called when the selected component has been double clicked.  return true if something was opened

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API REWINDDEBUGGERINTERFACE_API`

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebuggerExtension.h` (Public)


#### class `IRewindDebuggerExtension`  
`class IRewindDebuggerExtension : public IModularFeature`  
_L18-63_
- inherits: `IModularFeature`
- desc: Interface class for extensions which add functionality to the rewind debugger. These will get updated on scrub/playback to handle things like updating the world state to match recorded data from that time for a particular system.
- L21 _public member_ `static const FName ModularFeatureName;`
- L24 _public function_ `virtual FString GetName()` — debugging name for this extension
- L30 _public function_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger)` — called while scrubbing, playing back, or paused
- L35 _public function_ `virtual void AnalysisSessionOpened(IRewindDebugger* RewindDebugger)` — called when opening an analysis session
- L40 _public function_ `virtual void AnalysisSessionClosed(IRewindDebugger* RewindDebugger)` — called when closing an analysis session
- L45 _public function_ `virtual void RecordingStarted(IRewindDebugger* RewindDebugger) final` — `UE_DEPRECATED(5.8, "Use AnalysisSessionOpened instead or implement an extension inheriting from IRewindDebuggerRuntimeExtension")`
- L50 _public function_ `virtual void RecordingStopped(IRewindDebugger* RewindDebugger) final` — `UE_DEPRECATED(5.8, "Use AnalysisSessionClosed instead or implement an extension inheriting from IRewindDebuggerRuntimeExtension")`
- L55 _public function_ `virtual void Clear(IRewindDebugger* RewindDebugger)` — called when recording is unloaded
- L60 _public function_ `virtual void OnTrackListChanged(IRewindDebugger* RewindDebugger)` — called when tracks get removed or added to the debugger

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API REWINDDEBUGGERINTERFACE_API`

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebuggerModule.h` (Public)


#### class `IRewindDebuggerModule`  
`class IRewindDebuggerModule : public IModuleInterface`  
_L12-29_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual FName GetMainTabName() const = 0;` — @return the name of the main RewindDebugger window that could be used to invoke the associated tab in the Editor.
- L19 _public prototype_ `virtual FName GetDetailsTabName() const = 0;` — @return the name of the RewindDebugger details window that could be used to invoke the associated tab in the Editor.
- L22 _public prototype_ `virtual FName GetMainToolbarName() const = 0;` — @return the name of the main toolbar in the RewindDebugger window that could be used to add new entries.
- L25 _public prototype_ `virtual FName GetPreviewMenuName() const = 0;` — @return the name of the Preview dropdown menu. Register menu extensions against it.
- L27 _public prototype_ `virtual TSharedRef<SDockTab> SpawnRewindDebuggerTab(const FSpawnTabArgs& SpawnTabArgs) = 0;`
- L28 _public prototype_ `virtual TSharedRef<SDockTab> SpawnRewindDebuggerDetailsTab(const FSpawnTabArgs& SpawnTabArgs) = 0;`

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebuggerTrackCreator.h` (Public)


#### struct `RewindDebugger::FRewindDebuggerTrackType`  
`struct FRewindDebuggerTrackType`  
_L24-28_
- L26 _public member_ `FName Name;`
- L27 _public member_ `FText DisplayName;`

#### class `RewindDebugger::IRewindDebuggerTrackCreator`  
`class IRewindDebuggerTrackCreator : public IModularFeature`  
_L33-155_
- inherits: `IModularFeature`
- desc: Interface class which creates tracks
- L36 _public member_ `static const FName ModularFeatureName;`
- L38 _public prototype_ `virtual ~IRewindDebuggerTrackCreator() = default;`
- L41 _public function_ `FName GetTargetTypeName() const` — @return name of the type of UObject this track creator can create tracks for
- L47 _public function_ `FName GetName() const` — @return identifying Name for this type of track
- L53 _public function_ `int32 GetSortOrderPriority() const` — @return integer representing the track priority.  Higher values will show higher in the track list (default is 0)
- L62 _public function_ `bool HasDebugInfo(const FObjectId& ObjectId) const` — Optional filter to prevent tracks from being listed if there is no data associated to the provided object identifier. @return Whether the track should be created to represent data associated to the provided object identifier.
- L68 _public function_ `bool HasDebugInfo(uint64 ObjectId) const` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L79 _public function_ `TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrack(const FObjectId& ObjectId) const` — Creates a track which will be shown in the timeline view and tree view, as a child track of the Object @return the created child track
- L85 _public function_ `TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrack(uint64 ObjectId) const` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L92 _public function_ `void GetTrackTypes(TArray<FRewindDebuggerTrackType>& Types) const`
- L98 _public function_ `bool IsCreatingPrimaryChildTrack() const` — @return Whether the track created will be used by its parent track to replace its representation and timeline values
- L106 _private function_ `virtual FName GetTargetTypeNameInternal() const` — get the UObject type name this Creator will create child tracks for
- L112 _private function_ `virtual FName GetNameInternal() const` — get the Name (unique identifier) for this Creator
- L118 _private function_ `virtual int32 GetSortOrderPriorityInternal() const` — An integer to override sort order for tracks created by this Creator (Higher priority will make tracks appear higher in the list)
- L124 _private function_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const` — Add track types that this Creator will create to the track type list
- L129 _private function_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const` — Returns true if this creator's track should be shown for this Object, false if there is no data and they should be hidden.
- L135 _private function_ `virtual bool HasDebugInfoInternal(uint64 InObjectId) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L140 _private function_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const`
- L146 _private function_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(uint64 InObjectId) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L151 _private function_ `virtual bool IsCreatingPrimaryChildTrackInternal() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L19 _namespace_ `namespace RewindDebugger`

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebuggerView.h` (Public)


#### class `IRewindDebuggerView`  
`class IRewindDebuggerView : public SCompoundWidget`  
_L9-20_
- inherits: `SCompoundWidget`
- desc: Interface class for views of recorded debug data
- L13 _public prototype_ `virtual FName GetName() const = 0;` — unique name for widget
- L16 _public prototype_ `virtual uint64 GetObjectId() const = 0;` — id of target object
- L19 _public prototype_ `virtual void SetTimeMarker(double InTimeMarker) = 0;` — called by the debugger when the scrubbing bar position changes

### `Source/Editor/RewindDebuggerInterface/Public/IRewindDebuggerViewCreator.h` (Public)


#### class `IRewindDebuggerViewCreator`  
`class IRewindDebuggerViewCreator : public IModularFeature`  
_L17-42_
- inherits: `IModularFeature`
- desc: Interface class which creates debug widgets
- L20 _public member_ `static const FName ModularFeatureName;`
- L23 _public prototype_ `virtual FName GetTargetTypeName() const = 0;` — returns the name of a type of UObject for which this debug view will be created
- L26 _public function_ `virtual bool HasDebugInfo(uint64 ObjectId) const` — optional additional filter, to prevent debug views from being listed if they have no data
- L32 _public prototype_ `virtual FName GetName() const = 0;` — returns a unique name for identifying this type of widget (same value returned by IRewindDebuggerView::GetName)
- L35 _public prototype_ `virtual FText GetTitle() const = 0;` — text for tab header
- L38 _public prototype_ `virtual FSlateIcon GetIcon() const = 0;` — icon for tab header
- L41 _public prototype_ `virtual TSharedPtr<IRewindDebuggerView> CreateDebugView(uint64 ObjectId, double CurrentTime, const TraceServices::IAnalysisSession& InAnalysisSession) const = 0;` — creates and returns a widget, which will be displayed in Rewind Debugger

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API REWINDDEBUGGERINTERFACE_API`
- L11 _namespace_ `namespace TraceServices`

### `Source/Editor/RewindDebuggerInterface/Public/RewindDebuggerTrack.h` (Public)


#### enum `RewindDebugger::ETrackHiddenFlags`  
`enum class ETrackHiddenFlags : uint8`  
_L21-27_
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `HiddenByCode = 1 << 0`
- L25 _public enumerator_ `HiddenByUI = 1 << 1`
- L26 _public enumerator_ `AnyFlag = 0xFF`

#### enum `RewindDebugger::EStepMode`  
`enum class EStepMode : uint8`  
_L30-34_
- L32 _public enumerator_ `Forward`
- L33 _public enumerator_ `Backward`

#### class `RewindDebugger::FRewindDebuggerTrack`  
`class FRewindDebuggerTrack`  
_L36-368_
- L48 _public function_ `FRewindDebuggerTrack()`
- L52 _public prototype_ `virtual ~FRewindDebuggerTrack() = default;`
- L54 _public function_ `bool GetIsExpanded() const`
- L59 _public function_ `void SetIsExpanded(const bool bIsExpanded)`
- L64 _public function_ `bool GetIsSelected() const`
- L69 _public function_ `void SetIsSelected(const bool bIsSelected)`
- L74 _public function_ `bool GetIsTreeHovered() const`
- L79 _public function_ `void SetIsTreeHovered(const bool bIsHovered)`
- L84 _public function_ `bool GetIsTrackHovered() const`
- L89 _public function_ `void SetIsTrackHovered(const bool bIsHovered)`
- L94 _public function_ `bool GetIsHovered() const`
- L100 _public function_ `bool Update()` — Update should do work to compute children etc. for the current time range.  Return true if children have changed.
- L106 _public function_ `TSharedPtr<SWidget> GetTimelineView()` — Get a widget to show in the timeline view for this track
- L112 _public function_ `TSharedPtr<SWidget> GetDetailsView()` — Get a widget to show in the details tab, when this track is selected
- L118 _public function_ `FName GetName() const` — unique name for track (must match creator name if track is created by an IRewindDebuggerViewCreator)
- L124 _public function_ `FSlateIcon GetIcon()` — icon to display in the tree view
- L130 _public function_ `FText GetDisplayName() const` — display name for track in Tree View
- L136 _public function_ `uint64 GetUObjectId() const` — insights main UObject id for an object associated with this track
- L142 _public function_ `uint64 GetObjectId() const` — `UE_DEPRECATED(5.7, "Use GetUObjectID instead.")`
- L148 _public function_ `FObjectId GetAssociatedObjectId() const` — insights object id for an object associated with this track
- L154 _public function_ `FText GetStepCommandTooltip(const EStepMode StepMode) const` — tracks can customize the tooltip for the step command
- L161 _public function_ `TOptional<double> GetStepFrameTime(const EStepMode StepMode, const double CurrentScrubTime) const` — tracks can return a different time for the step action; default the main recording frame time is used
- L169 _public function_ `TOptional<double> GetStepFrameTime(const EStepMode StepMode, const FScrubTimeInformation& CurrentScrubTime) const` — tracks can return a different time for the step action; default the main recording frame time is used
- L178 _public function_ `static EVisitResult Visit(TSharedPtr<FRewindDebuggerTrack> Track, TFunction<EVisitResult(TSharedPtr<FRewindDebuggerTrack> SubTrack)> IteratorFunction)` — Visit the current track along with its child hierarchy recursively to call provided function on each track until a call returns EVisitResult::Break
- L192 _private function_ `EVisitResult Visit(TFunction<EVisitResult(TSharedPtr<FRewindDebuggerTrack> SubTrack)> IteratorFunction)` — Visit the child hierarchy recursively to call provided function on each track until a call returns EVisitResult::Break
- L218 _public function_ `void IterateSubTracks(TFunction<void(TSharedPtr<FRewindDebuggerTrack> SubTrack)> IteratorFunction) const` — iterates over all sub-tracks of this track and call Iterator function
- L235 _public function_ `bool HasDebugData() const` — returns true for tracks that contain debug data (used for filtering out parts of the hierarchy with no useful information in them)
- L241 _public function_ `bool HandleDoubleClick()` — Called when a track is double-clicked.  Returns true if the track handled the double click
- L246 _public function_ `void SetHiddenFlag(const ETrackHiddenFlags Flag)`
- L251 _public function_ `void UnsetHiddenFlag(const ETrackHiddenFlags Flag)`
- L256 _public function_ `bool HasAnyFlags(const ETrackHiddenFlags Flags) const`
- L261 _public function_ `bool IsVisible() const`
- L267 _public function_ `void SetIsVisible(const bool bInIsVisible)` — `UE_DEPRECATED(5.7, "Use SetHiddenFlag/UnsetHiddenFlag instead.")`
- L280 _public function_ `virtual void BuildContextMenu(FToolMenuSection& InMenuSection)` — Called to generate context menu for the current selected track
- L284 _private function_ `virtual bool UpdateInternal()`
- L289 _private function_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal()`
- L294 _private function_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal()`
- L299 _private function_ `virtual FSlateIcon GetIconInternal()`
- L304 _private function_ `virtual FName GetNameInternal() const`
- L309 _private function_ `virtual FText GetDisplayNameInternal() const`
- L314 _private function_ `virtual uint64 GetObjectIdInternal() const`
- L319 _private function_ `virtual bool HasDebugDataInternal() const`
- L324 _private function_ `virtual FText GetStepCommandTooltipInternal(EStepMode) const`
- L330 _private function_ `virtual TOptional<double> GetStepFrameTimeInternal(EStepMode, const double) const final` — `UE_DEPRECATED(5.8, "Use overload taking a scrub time information struct instead.")`
- L335 _private function_ `virtual TOptional<double> GetStepFrameTimeInternal(EStepMode, const FScrubTimeInformation&) const`
- L341 _private function_ `virtual void IterateSubTracksInternal(TFunction<void(TSharedPtr<FRewindDebuggerTrack> SubTrack)> IteratorFunction) final` — `UE_DEPRECATED(5.7, "Implement and use GetChildrenInternal instead.")`
- L351 _private function_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const` — Method that derive classes can override to provide children tracks for methods like Visit and IterateSubTracks Caller of this method is expected to handle both the return value and the output parameter. @param OutTracks Optional parameter that can be used when the derived class can't provide a const view of the children @return An array view on the sub tracks
- L356 _private function_ `virtual bool HandleDoubleClickInternal()`
- L362 _private member_ `ETrackHiddenFlags HiddenFlags = ETrackHiddenFlags::None;`
- L364 _private member_ `bool bSelected : 1 = false;`
- L365 _private member_ `bool bTrackHovered : 1 = false;`
- L366 _private member_ `bool bTreeHovered : 1 = false;`
- L367 _private member_ `bool bExpanded : 1 = true;`

#### enum `RewindDebugger::FRewindDebuggerTrack::EVisitResult`  
`enum class EVisitResult : uint8`  
_L40-46_
- desc: Result returned from a visitor functor indicating to continue or to quit early
- L43 _public enumerator_ `Break` — Stop iterating through tracks and early exit
- L45 _public enumerator_ `Continue` — Continue to iterate through all tracks

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L19 _namespace_ `namespace RewindDebugger`
- L28 _prototype_ `ENUM_CLASS_FLAGS(ETrackHiddenFlags);` (scope `RewindDebugger`)

### `Source/Editor/RewindDebuggerInterface/Public/RewindDebuggerTypes.h` (Public)


#### struct `RewindDebugger::FObjectId`  
`struct FObjectId`  
_L15-67_
- desc: Struct representing an object (single UObject or a child element of a UObject) tracked by Unreal Insight traces. This struct is used to represent the data traced by UE::ObjectTrace::FObjectId
- L17 _public member_ `static constexpr uint64 InvalidId = 0;`
- L19 _public prototype_ `FObjectId() = default;`
- L21 _public function_ `explicit FObjectId(const uint64 MainId) : ObjectId(MainId)`
- L30 _public function_ `uint64 GetMainId() const` — Identifier associated to a UObject recorded using TRACE_OBJECT* macros. @return Identifier associated to a given UObject in traces.
- L38 _public function_ `bool IsSet() const` — @return Whether the current gameplay object identifier was set to represent a UObject, or one of its children.
- L43 _public prototype_ `bool operator==(const FObjectId& Other) const = default;`
- L45 _public function_ `bool operator<(const FObjectId& Other) const`
- L66 _private member_ `uint64 ObjectId = InvalidId;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace RewindDebugger`
- L50 _function_ `friend FString LexToString(const FObjectId& ObjectIdentifier)` (scope `RewindDebugger`)
- L60 _function_ `friend uint32 GetTypeHash(const FObjectId Identifier)` (scope `RewindDebugger`)

### `Source/Editor/RewindDebuggerInterface/Public/SEventTimelineView.h` (Public)


#### class `SEventTimelineView`  
`class SEventTimelineView : public SCompoundWidget`  
_L17-116_
- inherits: `SCompoundWidget`
- L68 _public function_ `SLATE_BEGIN_ARGS(SEventTimelineView) : _ViewRange(TRange<double>(0, 10)) , _DesiredSize(FVector2D(100.f, 20.f))`
- L74 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L77 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FTimelineEventData>, EventData);` — Data for events to render
- L80 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, DesiredSize);` — Desired widget size
- L82 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L94 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L95 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args , const FGeometry& AllottedGeometry , const FSlateRect& MyCullingRect , FSlateWindowElementList& OutDrawElements , int32 LayerId , const FWidgetStyle& InWidgetStyle , bool bParentEnabled) const override;`
- L103 _protected prototype_ `int32 PaintEvents(const FGeometry& AllottedGeometry , const FSlateRect& MyCullingRect , FSlateWindowElementList& OutDrawElements , int32 LayerId , const FWidgetStyle& InWidgetStyle , bool bParentEnabled) const;`
- L110 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L111 _protected member_ `TAttribute<TSharedPtr<FTimelineEventData>> EventData;`
- L112 _protected member_ `TAttribute<FVector2D> DesiredSize;`
- L114 _protected member_ `const FSlateBrush* EventBrush = nullptr;`
- L115 _protected member_ `const FSlateBrush* EventBorderBrush = nullptr;`

#### struct `SEventTimelineView::FTimelineEventData`  
`struct FTimelineEventData`  
_L20-66_
- L39 _public member_ `TArray<FEventPoint> EventPoints;`
- L40 _public member_ `TArray<FEventWindow> EventWindows;`
- L61 _public member_ `TArray<EventPoint> Points;` — `UE_DEPRECATED(5.8, "Use EventPoints instead")`
- L63 _public member_ `TArray<EventWindow> Windows;` — `UE_DEPRECATED(5.8, "Use EventWindows instead")`

#### struct `SEventTimelineView::FTimelineEventData::FEventPoint`  
`struct FEventPoint`  
_L22-28_
- L24 _public member_ `double Time;`
- L25 _public member_ `FText Type;`
- L26 _public member_ `FText Description;`
- L27 _public member_ `FLinearColor Color;`

#### struct `SEventTimelineView::FTimelineEventData::FEventWindow`  
`struct FEventWindow`  
_L30-37_
- L32 _public member_ `double TimeStart;`
- L33 _public member_ `double TimeEnd;`
- L34 _public member_ `FText Type;`
- L35 _public member_ `FText Description;`
- L36 _public member_ `FLinearColor Color;`

#### struct `SEventTimelineView::FTimelineEventData::EventPoint`  
`struct UE_DEPRECATED(5.8, "Use FEventPoint instead") EventPoint`  
_L44-50_
- L46 _public member_ `double Time;`
- L47 _public member_ `FText Type;`
- L48 _public member_ `FText Description;`
- L49 _public member_ `FLinearColor Color;`

#### struct `SEventTimelineView::FTimelineEventData::EventWindow`  
`struct UE_DEPRECATED(5.8, "Use FEventWindow instead") EventWindow`  
_L51-58_
- L53 _public member_ `double TimeStart;`
- L54 _public member_ `double TimeEnd;`
- L55 _public member_ `FText Type;`
- L56 _public member_ `FText Description;`
- L57 _public member_ `FLinearColor Color;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API REWINDDEBUGGERINTERFACE_API`
