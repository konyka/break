# Plugins / SceneStateEditor

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateEditor`
- headers: 5; symbols: 50
- symbol kinds: class=2, delegate=1, function=6, macro=3, member=11, namespace=5, prototype=19, struct=3
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, SceneState

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEditor/Private/SceneStateEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateEditor, Log, All);`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEditor/Private/SceneStateEditorModule.h` (Private)


#### class `FSceneStateEditorModule`  
`class FSceneStateEditorModule : public IModuleInterface`  
_L8-20_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void OnPostEngineInit();`
- L19 _private member_ `FDelegateHandle OnPostEngineInitHandle;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEditor/Public/SceneStateEditorUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENESTATEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L19 _prototype_ `FText GetStructTooltip(const UStruct& InStruct);` (scope `UE::SceneState::Editor`) — Returns the tooltip for a given struct. This is different from UStruct::GetTooltipText as it will return an empty text if there was no explicit Tooltip found @return the found tooltip, or empty if not the metadata was not present.

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEditor/Public/Tasks/SceneStateTaskDesc.h` (Public)


#### struct `FSceneStateTaskDescContext`  
`struct FSceneStateTaskDescContext`  
_L19-29_
- desc: Context to pass to the Task Desc objects to get information about the Task and Task Instance
- L22 _public member_ `TConstStructView<FSceneStateTask> Task;` — Data view of the task
- L25 _public member_ `TConstStructView<FSceneStateTaskInstance> TaskInstance;` — Data view of the task instance
- L28 _public member_ `TObjectPtr<const UObject> ContextObject;` — Context object (e.g. graph node) using the task desc

#### struct `FSceneStateTaskDescMutableContext`  
`struct FSceneStateTaskDescMutableContext`  
_L31-41_
- L34 _public member_ `TStructView<FSceneStateTask> Task;` — Data view of the task
- L37 _public member_ `TStructView<FSceneStateTaskInstance> TaskInstance;` — Data view of the task instance
- L40 _public member_ `TObjectPtr<UObject> ContextObject;` — Context object (e.g. graph node) using the task desc

#### struct `FSceneStateTaskDesc`  
`struct FSceneStateTaskDesc`  
_L45-115_
- reflection: `USTRUCT()`
- desc: Base struct describing a task and its instance for editor-only data and behavior
- L49 _public prototype_ `FSceneStateTaskDesc();`
- L51 _public prototype_ `virtual ~FSceneStateTaskDesc() = default;`
- L54 _public function_ `const UScriptStruct* GetSupportedTask() const` — Return the task type this task desc supports
- L60 _public prototype_ `FText GetDisplayName(const FSceneStateTaskDescContext& InContext) const;` — Gets the display name of the task
- L63 _public prototype_ `FText GetTooltip(const FSceneStateTaskDescContext& InContext) const;` — Gets the tooltip of the task
- L66 _public prototype_ `UObject* GetJumpTarget(const FSceneStateTaskDescContext& InContext) const;` — Gets the target object to go to on node double click
- L69 _public prototype_ `void NotifyStructIdsChanged(const FSceneStateTaskDescMutableContext& InContext, const UE::SceneState::FStructIdChange& InChange) const;` — Called when struct ids have been changed, to be handled by tasks individually
- L73 _public function_ `template<typename T UE_REQUIRES(std::is_base_of_v<FSceneStateTask, T>)> void SetSupportedTask()` — Set the task struct to support
- L80 _protected function_ `virtual bool OnGetDisplayName(const FSceneStateTaskDescContext& InContext, FText& OutDisplayName) const` — Gets the display name for the task
- L86 _protected function_ `virtual bool OnGetTooltip(const FSceneStateTaskDescContext& InContext, FText& OutDescription) const` — Gets the tooltip for the task
- L92 _protected function_ `virtual bool OnGetJumpTarget(const FSceneStateTaskDescContext& InContext, UObject*& OutJumpTarget) const` — Gets the target object to go to on node double click
- L98 _protected function_ `virtual void OnStructIdsChanged(const FSceneStateTaskDescMutableContext& InContext, const UE::SceneState::FStructIdChange& InChange) const` — Called when struct ids have been changed
- L104 _private prototype_ `bool IsValidContext(const FSceneStateTaskDescContext& InContext) const;` — Ensures the context is valid against the supported task
- L107 _private prototype_ `bool IsValidContext(const FSceneStateTaskDescMutableContext& InContext) const;` — Ensures the context is valid against the supported task
- L110 _private prototype_ `void SetSupportedTask(UScriptStruct* InSupportedTask);` — Set the task struct to support
- L114 _private member_ `TObjectPtr<const UScriptStruct> SupportedTask = nullptr;` — `UPROPERTY()` — The task struct to support

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEditor/Public/Tasks/SceneStateTaskDescRegistry.h` (Public)


#### class `FSceneStateTaskDescRegistry`  
`class FSceneStateTaskDescRegistry : public FGCObject`  
_L14-40_
- inherits: `FGCObject`
- desc: Registry holding editor-only task descs for each discovered task struct
- L17 _public member_ `static FSceneStateTaskDescRegistry GlobalRegistry;`
- L20 _public prototype_ `static const FSceneStateTaskDescRegistry& Get();` — Gets a const ref to the global registry
- L23 _public prototype_ `const FSceneStateTaskDesc& GetTaskDesc(const UScriptStruct* InTaskStruct) const;` — Gets the task desc for the given task struct
- L26 _public prototype_ `void CacheTaskDescs();` — Gathers all the available Tasks and stores it in this registry
- L30 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L31 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L36 _private member_ `TMap<TObjectKey<UScriptStruct>, TInstancedStruct<FSceneStateTaskDesc>> TaskDescs;` — Registered task structs to their task descs
- L39 _private member_ `TInstancedStruct<FSceneStateTaskDesc> DefaultTaskDesc;` — Default task desc to use

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENESTATEEDITOR_API`
