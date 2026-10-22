# Plugins / AvalancheMRQEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor`
- headers: 5; symbols: 21
- symbol kinds: class=4, function=1, member=5, prototype=9, struct=2
- PrivateDependencyModuleNames: Avalanche, AvalancheMRQ, AvalancheMedia, AvalancheMediaEditor, AvalancheSequence, AvalancheSequencer, Core, CoreUObject, DeveloperSettings, Engine, MovieRenderPipelineCore, MovieRenderPipelineEditor, MovieRenderPipelineRenderPasses, RemoteControl, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor/Private/AvaMRQEditorCommands.h` (Private)


#### class `FAvaMRQEditorCommands`  
`class FAvaMRQEditorCommands : public TCommands<FAvaMRQEditorCommands>`  
_L7-17_
- inherits: `TCommands<FAvaMRQEditorCommands>`
- L10 _public prototype_ `FAvaMRQEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> RenderSelectedPages;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor/Private/AvaMRQEditorModule.h` (Private)


#### struct `FAvaMRQRundownContext`  
`struct FAvaMRQRundownContext`  
_L17-20_
- L19 _public member_ `TArray<TWeakPtr<const FAvaRundownEditor>, TInlineAllocator<1>> RundownEditors;`

#### class `FAvaMRQEditorModule`  
`class FAvaMRQEditorModule : public IModuleInterface`  
_L22-36_
- inherits: `IModuleInterface`
- L25 _private prototype_ `virtual void StartupModule() override;`
- L26 _private prototype_ `virtual void ShutdownModule() override;`
- L29 _private prototype_ `static TSharedRef<FExtender> ExtendRundownToolbar(const TSharedRef<FUICommandList> InCommandList, const TArray<UObject*> InObjects);`
- L31 _private prototype_ `static TSharedRef<FUICommandList> CreateRundownActions(TSharedRef<FAvaMRQRundownContext> InContext);`
- L33 _private member_ `TWeakPtr<FExtensibilityManager> RundownToolbarExtensibilityWeak;`
- L35 _private member_ `FDelegateHandle RundownToolbarExtenderHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor/Private/AvaMRQEditorRundownUtils.h` (Private)


#### struct `FAvaMRQEditorRundownUtils`  
`struct FAvaMRQEditorRundownUtils`  
_L10-13_
- L12 _public prototype_ `static void RenderSelectedPages(TConstArrayView<TWeakPtr<const FAvaRundownEditor>> InRundownEditors);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor/Private/AvaMRQEditorSettings.h` (Private)


#### class `UAvaMRQEditorSettings`  
`class UAvaMRQEditorSettings : public UDeveloperSettings`  
_L12-21_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Movie Render Queue"))`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `UAvaMRQEditorSettings();`
- L20 _public member_ `TSoftObjectPtr<UMoviePipelinePrimaryConfig> PresetConfig;` — `UPROPERTY(Config, EditAnywhere, Category="Motion Design")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor/Private/AvaMRQEditorStyle.h` (Private)


#### class `FAvaMRQEditorStyle`  
`class FAvaMRQEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaMRQEditorStyle& Get()`
- L16 _public prototype_ `FAvaMRQEditorStyle();`
