# Plugins / TextureGraphInsightEditor

- module root: `Plugins/TextureGraph/Source/TextureGraphInsightEditor`
- headers: 3; symbols: 23
- symbol kinds: class=3, function=1, member=6, prototype=13
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, Blutility, Continuable, CoreUObject, DeveloperSettings, Engine, InputCore, Projects, Slate, SlateCore, StaticMeshEditor, TextureGraphEngine, TextureGraphInsight, ToolMenus, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/TextureGraph/Source/TextureGraphInsightEditor/Public/TextureGraphInsightEditor.h` (Public)


#### class `FTextureGraphInsightEditorModule`  
`class FTextureGraphInsightEditorModule : public IModuleInterface`  
_L10-33_
- inherits: `IModuleInterface`
- L12 _private member_ `FTickerDelegate _tickDelegate;`
- L13 _private member_ `FTSTicker::FDelegateHandle _tickDelegateHandle;`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `bool Tick(float DeltaTime);`
- L22 _public prototype_ `void PluginButtonClicked();` — This function will be bound to Command (by default it will bring up plugin window)
- L25 _private prototype_ `void RegisterMenus();`
- L26 _private prototype_ `TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);`
- L29 _private member_ `TSharedPtr<class FUICommandList> Commands;`
- L30 _private member_ `TSharedPtr<FTabManager > TabManager;`
- L31 _private member_ `TSharedPtr<FTabManager::FLayout > Layout;`

### `Plugins/TextureGraph/Source/TextureGraphInsightEditor/Public/TextureGraphInsightEditorCommands.h` (Public)


#### class `FTextureGraphInsightEditorCommands`  
`class FTextureGraphInsightEditorCommands : public TCommands<FTextureGraphInsightEditorCommands>`  
_L9-23_
- inherits: `TCommands<FTextureGraphInsightEditorCommands>`
- L13 _public function_ `FTextureGraphInsightEditorCommands() : TCommands<FTextureGraphInsightEditorCommands>(TEXT("TextureGraphInsightEditor"), NSLOCTEXT("Contexts", "TextureGraphInsightEditor", "TextureGraphInsightEditor Plugin"), NAME_None, FTextureGraphInsightEditorStyle::GetStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface

### `Plugins/TextureGraph/Source/TextureGraphInsightEditor/Public/TextureGraphInsightEditorStyle.h` (Public)


#### class `FTextureGraphInsightEditorStyle`  
`class FTextureGraphInsightEditorStyle`  
_L9-32_
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L21 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Shooter game
- L23 _public prototype_ `static FName GetStyleSetName();`
- L27 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L31 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`
