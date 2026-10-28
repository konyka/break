# Plugins / SceneStateGameplayEditor

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplayEditor`
- headers: 4; symbols: 32
- symbol kinds: class=4, member=2, namespace=12, prototype=14
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LevelEditor, SceneState, SceneStateBlueprint, SceneStateBlueprintEditor, SceneStateGameplay, Sequencer, SequencerCore, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplayEditor/Private/SceneStateActorFactory.h` (Private)


#### class `USceneStateActorFactory`  
`class USceneStateActorFactory : public UActorFactory`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L16 _public prototype_ `USceneStateActorFactory();`
- L19 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& InAssetData, FText& OutErrorMessage) override;`
- L20 _public prototype_ `virtual void PostSpawnActor(UObject* InAsset, AActor* InNewActor) override;`
- L24 _private prototype_ `TSubclassOf<USceneStateObject> GetSceneStateClass(UObject* InAsset) const;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplayEditor/Private/SceneStateGameplayContextEditor.h` (Private)


#### class `UE::SceneState::Editor::FGameplayContextEditor`  
`class FGameplayContextEditor : public IContextEditor`  
_L14-24_
- inherits: `IContextEditor`
- desc: Context editor for gameplay elements like Actors and Actor Components
- L18 _public prototype_ `virtual void GetContextClasses(TArray<TSubclassOf<UObject>>& OutContextClasses) const override;`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> CreateViewWidget(const FContextParams& InContextParams) const override;`
- L23 _public prototype_ `UGameViewportClient* CreateViewportClient(FWorldContext& InWorldContext) const;` — Creates the game viewport client for the given world context, or null if there's no valid game instance in that world

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplayEditor/Private/SceneStateGameplayEditorModule.h` (Private)


#### class `UE::SceneState::Editor::FGameplayEditorModule`  
`class FGameplayEditorModule : public IModuleInterface`  
_L17-26_
- inherits: `IModuleInterface`
- L20 _private prototype_ `virtual void StartupModule() override;`
- L21 _private prototype_ `virtual void ShutdownModule() override;`
- L24 _private member_ `TSharedPtr<FGameplayContextEditor> GameplayContextEditor;`
- L25 _private member_ `TSharedPtr<FSequencerSchema> SequencerSchema;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplayEditor/Private/SceneStateSequencerSchema.h` (Private)


#### class `UE::SceneState::Editor::FSequencerSchema`  
`class FSequencerSchema : public UE::Sequencer::IObjectSchema`  
_L15-25_
- inherits: `UE::Sequencer::IObjectSchema`
- L18 _private prototype_ `virtual UObject* GetParentObject(UObject* InObject) const override;`
- L19 _private prototype_ `virtual UE::Sequencer::FObjectSchemaRelevancy GetRelevancy(const UObject* InObject) const override;`
- L20 _private prototype_ `virtual TSharedPtr<FExtender> ExtendObjectBindingMenu(TSharedRef<FUICommandList> InCommandList, TWeakPtr<ISequencer> InSequencerWeak, TConstArrayView<UObject*> InContextSensitiveObjects) const override;`
- L23 _private prototype_ `static void OnAddTrackMenuExtension(FMenuBuilder& InMenuBuilder, TWeakPtr<ISequencer> InSequencerWeak, TArray<TWeakObjectPtr<USceneStateComponent>> InComponents);`
- L24 _private prototype_ `static void AddSceneStateComponents(TWeakPtr<ISequencer> InSequencerWeak, TArray<TWeakObjectPtr<USceneStateComponent>> InComponents);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)
