# Plugins / MultiUserReplicationEditor

- module root: `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor`
- headers: 11; symbols: 82
- symbol kinds: class=9, delegate=1, function=13, member=15, namespace=8, prototype=34, struct=2
- PrivateDependencyModuleNames: AssetDefinition, AssetRegistry, Concert, ConcertClient, ConcertSharedSlate, ConcertTransport, InputCore, Projects, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: ConcertClientSharedSlate, ConcertSharedSlate, ConcertSyncCore, Core, CoreUObject, Engine

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Internal/Assets/MultiUserReplicationClientPreset.h` (Internal)


#### struct `FMultiUserReplicationClientPreset`  
`struct FMultiUserReplicationClientPreset`  
_L14-48_
- reflection: `USTRUCT()`
- desc: Stores info about a client's content in a preset.
- L20 _public member_ `FConcertObjectReplicationMap ReplicationMap;` — `UPROPERTY()` — The objects this stream will modify.
- L24 _public member_ `FConcertStreamFrequencySettings FrequencySettings;` — `UPROPERTY()` — The frequency setting the stream has.
- L33 _public member_ `FConcertReplicationRemappingData ActorLabelRemappingData;` — `UPROPERTY()` — For each FSoftObjectPath in ReplicationMap that references an actor this saves its actor label. When the preset is applied, potentially in a new world or different session, this allows rebinding the original FSoftObjectPaths to FSoftObjectPaths that now point to different objects but that share the same actor label and share the same subobject hierarchy.
- L37 _public member_ `FString DisplayName;` — `UPROPERTY()` — The FConcertClientInfo::DisplayName of the client.
- L40 _public member_ `FString DeviceName;` — `UPROPERTY()` — The FConcertClientInfo::DeviceName of the client.
- L42 _public prototype_ `FMultiUserReplicationClientPreset() = default;`
- L44 _public function_ `FMultiUserReplicationClientPreset(const FString& DisplayName, const FString& DeviceName) : DisplayName(DisplayName) , DeviceName(DeviceName)`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Internal/Assets/MultiUserReplicationSessionPreset.h` (Internal)


#### struct `FMultiUserMuteSessionContent`  
`struct FMultiUserMuteSessionContent`  
_L14-34_
- reflection: `USTRUCT()`
- L20 _public member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> MutedObjects;` — `UPROPERTY()` — The argument to put into FConcertReplication_ChangeMuteState_Request::ObjectsToMute.
- L24 _public member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> UnmutedObjects;` — `UPROPERTY()` — The argument to put into FConcertReplication_ChangeMuteState_Request::ObjectsToUnmute.
- L26 _public prototype_ `FMultiUserMuteSessionContent() = default;`
- L27 _public function_ `FMultiUserMuteSessionContent( TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> MutedObjects, TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> UnmutedObjects ) : MutedObjects(MoveTemp(MutedObjects)) , UnmutedObjects(MoveTemp(UnmutedObjects))`

#### class `UMultiUserReplicationSessionPreset`  
`class UMultiUserReplicationSessionPreset : public UObject`  
_L38-72_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Stores per-client replication settings so it can be loaded by a user to quickly set up a session.
- L46 _public prototype_ `const FMultiUserReplicationClientPreset* GetClientContent(const FConcertClientInfo& ClientInfo) const;` — @return The client preset that matches ClientInfo.DisplayName. If there are multiple, returns the one that matches ClientInfo.DeviceName, as well.
- L48 _public prototype_ `const FMultiUserReplicationClientPreset* GetExactClientContent(const FConcertClientInfo& ClientInfo) const;` — @return The client preset that matches both the display and device name.
- L51 _public function_ `bool ContainsClient(const FConcertClientInfo& ClientInfo) const` — @return Whether a client that matches ClientInfo.DisplayName.
- L53 _public function_ `bool ContainsExactClient(const FConcertClientInfo& ClientInfo) const` — @return Whether a client that matches both the display and device name is saved in this preset.
- L56 _public prototype_ `FMultiUserReplicationClientPreset* AddClientIfUnique(const FConcertClientInfo& ClientInfo, const FGuid& StreamId);` — Adds a client to the preset if it's not already present.
- L58 _public function_ `const TArray<FMultiUserReplicationClientPreset>& GetClientPresets() const`
- L62 _public function_ `const FMultiUserMuteSessionContent& GetMuteContent() const`
- L63 _public function_ `void SetMuteContent(FMultiUserMuteSessionContent Content)`
- L68 _private member_ `TArray<FMultiUserReplicationClientPreset> ClientPresets;` — `UPROPERTY()`
- L71 _private member_ `FMultiUserMuteSessionContent MuteContent;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Internal/Assets/MultiUserReplicationStream.h` (Internal)


#### class `UMultiUserReplicationStream`  
`class UMultiUserReplicationStream : public UObject`  
_L12-38_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Wraps FConcertObjectReplicationMap so its edition can be transacted in the editor and saved in presets.
- L19 _public member_ `FGuid StreamId;` — `UPROPERTY()` — The ID of the stream. Set to 0 for CDO to avoid issues with delta serialization.
- L23 _public member_ `FConcertObjectReplicationMap ReplicationMap;` — `UPROPERTY()` — The objects this stream will modify.
- L25 _public prototype_ `UMultiUserReplicationStream();`
- L28 _public prototype_ `FConcertReplicationStream GenerateDescription() const;` — Util that generates the description of this stream for network requests.
- L31 _public function_ `TAttribute<FConcertObjectReplicationMap*> MakeReplicationMapGetterAttribute()` — Util that returns ReplicationMap.

#### Free symbols / members of external scopes

- L34 _function_ `` (scope `UMultiUserReplicationStream::MakeReplicationMapGetterAttribute`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Internal/IMultiUserReplicationEditorModule.h` (Internal)


#### class `UE::MultiUserReplicationEditor::IMultiUserReplicationEditorModule`  
`class IMultiUserReplicationEditorModule : public IModuleInterface`  
_L14-40_
- inherits: `IModuleInterface`
- L24 _public function_ `static inline IMultiUserReplicationEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserReplicationEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/Assets/AssetDefinition_ReplicationSessionPreset.h` (Private)


#### class `UAssetDefinition_ReplicationSessionPreset`  
`class UAssetDefinition_ReplicationSessionPreset : public UAssetDefinitionDefault`  
_L12-37_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L28 _protected function_ `virtual bool CanRegisterStatically() const override`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/Assets/ReplicationSessionPresetFactory.h` (Private)


#### class `UReplicationSessionPresetFactory`  
`class UReplicationSessionPresetFactory : public UFactory`  
_L10-20_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual bool CanCreateNew() const override;`
- L16 _private prototype_ `virtual FText GetDisplayName() const override;`
- L17 _private prototype_ `virtual bool ConfigureProperties() override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/LogMultiUserReplicationEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMultiUserReplicationEditor, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMultiUserReplicationEditor, All, All);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/MultiUserReplicationEditorModule.h` (Private)


#### class `UE::MultiUserReplicationEditor::FMultiUserReplicationEditorModule`  
`class FMultiUserReplicationEditorModule : public IMultiUserReplicationEditorModule`  
_L9-17_
- inherits: `IMultiUserReplicationEditorModule`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserReplicationEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/MultiUserReplicationEditorStyle.h` (Private)


#### class `UE::MultiUserReplicationEditor::FMultiUserReplicationEditorStyle`  
`class FMultiUserReplicationEditorStyle`  
_L12-27_
- L16 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Shutdown();`
- L20 _public prototype_ `static const ISlateStyle& Get();`
- L21 _public prototype_ `static FName GetStyleSetName();`
- L25 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`
- L26 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserReplicationEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/StreamEditor/ReplicationSessionPresetEditor.h` (Private)


#### class `UReplicationSessionPresetEditor`  
`class UReplicationSessionPresetEditor : public UAssetEditor`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetEditor`
- L17 _public prototype_ `void SetObjectToEdit(UObject* InObject);`
- L22 _protected prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjectsToEdit) override;`
- L23 _protected prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L29 _private member_ `TObjectPtr<UObject> ObjectToEdit;` — `UPROPERTY(Transient)`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserReplicationEditor/Private/StreamEditor/ReplicationSessionPresetEditorToolkit.h` (Private)


#### class `UE::MultiUserReplicationEditor::FReplicationSessionPresetEditorToolkit`  
`class FReplicationSessionPresetEditorToolkit : public FBaseAssetToolkit`  
_L14-38_
- inherits: `FBaseAssetToolkit`
- L18 _public member_ `static const FName ContentTabId;`
- L20 _public prototype_ `FReplicationSessionPresetEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L23 _public prototype_ `virtual void CreateWidgets();`
- L24 _public prototype_ `virtual void SetEditingObject(UObject* InObject) override;`
- L25 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L26 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L27 _public function_ `virtual FName GetToolkitFName() const override`
- L33 _private member_ `TSharedPtr<SReplicationStreamEditor> RootWidget;` — Root widget editing the asset
- L35 _private prototype_ `UMultiUserReplicationSessionPreset* GetEditedStreamAsset() const;`
- L37 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Content(const FSpawnTabArgs& SpawnTabArgs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserReplicationEditor` (scope `UE`)
