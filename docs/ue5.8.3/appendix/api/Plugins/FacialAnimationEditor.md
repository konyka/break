# Plugins / FacialAnimationEditor

- module root: `Plugins/Editor/FacialAnimation/Source/FacialAnimationEditor`
- headers: 4; symbols: 24
- symbol kinds: class=3, function=1, member=9, prototype=10, struct=1
- PrivateDependencyModuleNames: AudioEditor, Core, CoreUObject, DesktopPlatform, EditorFramework, Engine, FacialAnimation, InputCore, Persona, PropertyEditor, Slate, SlateCore, TargetPlatform, UnrealEd, WorkspaceMenuStructure

### `Plugins/Editor/FacialAnimation/Source/FacialAnimationEditor/Private/FacialAnimationBulkImporterSettings.h` (Private)


#### class `UFacialAnimationBulkImporterSettings`  
`class UFacialAnimationBulkImporterSettings : public UObject`  
_L8-27_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, Experimental, MinimalAPI)`
- inherits: `UObject`
- L14 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L18 _public member_ `FDirectoryPath SourceImportPath;` — `UPROPERTY(Config, EditAnywhere, Category = "Directories")` — The path to import files from
- L22 _public member_ `FDirectoryPath TargetImportPath;` — `UPROPERTY(Config, EditAnywhere, Category = "Directories", meta=(ContentDir))` — The path to import files to
- L26 _public member_ `FString CurveNodeName;` — `UPROPERTY(Config, EditAnywhere, Category = "Settings")` — Node in the FBX scene that contains the curves we are interested in

### `Plugins/Editor/FacialAnimation/Source/FacialAnimationEditor/Private/FacialAnimationEditorModule.h` (Private)


#### class `FFacialAnimationEditorModule`  
`class FFacialAnimationEditorModule : public IModuleInterface`  
_L8-25_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void HandleModulesChanged(FName InModuleName, EModuleChangeReason InModuleChangeReason);` — Handle modules being loaded/unloaded
- L21 _private member_ `FDelegateHandle OnModulesChangedDelegate;` — Delegate for hooking into module loading
- L24 _private member_ `FDelegateHandle OnPreviewSceneCreatedDelegate;` — Delegate for hooking into preview scene creation

### `Plugins/Editor/FacialAnimation/Source/FacialAnimationEditor/Private/SFacialAnimationBulkImporter.h` (Private)


#### class `SFacialAnimationBulkImporter`  
`class SFacialAnimationBulkImporter : public SCompoundWidget`  
_L7-21_
- inherits: `SCompoundWidget`
- L10 _public function_ `SLATE_BEGIN_ARGS(SFacialAnimationBulkImporter)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L18 _private prototype_ `bool IsImportButtonEnabled() const;`
- L20 _private prototype_ `FReply HandleImportClicked();`

### `Plugins/Editor/FacialAnimation/Source/FacialAnimationEditor/Public/FacialAnimationImportItem.h` (Public)


#### struct `FFacialAnimationImportItem`  
`struct FFacialAnimationImportItem`  
_L7-20_
- L9 _public prototype_ `bool Import();`
- L12 _private prototype_ `class USoundWave* ImportSoundWave(const FString& InSoundWavePackageName, const FString& InSoundWaveAssetName, const FString& InWavFilename) const;`
- L13 _private prototype_ `bool ImportCurvesEmbeddedInSoundWave();`
- L16 _public member_ `FString FbxFile;`
- L17 _public member_ `FString WaveFile;`
- L18 _public member_ `FString TargetPackageName;`
- L19 _public member_ `FString TargetAssetName;`
