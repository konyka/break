# Plugins / UAFChooserEditor

- module root: `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor`
- headers: 9; symbols: 61
- symbol kinds: class=5, function=5, macro=1, member=4, namespace=15, prototype=30, struct=1
- PrivateDependencyModuleNames: AssetDefinition, BlueprintGraph, Chooser, ChooserEditor, CoreUObject, EditorFramework, EditorWidgets, Engine, GameplayInsights, GraphEditor, InputCore, Kismet, MessageLog, Persona, PropertyEditor, RewindDebuggerInterface, RigVM, RigVMDeveloper, RigVMEditor, Settings, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFAnimNode, UAFAnimNodeEditor, UAFChooser, UAFChooserUncookedOnly, UAFEditor, UAFUncookedOnly, UnrealEd, WorkspaceEditor
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/AnimNode/UAFAnimNodeWidget.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace UAF` (scope `UE`)
- L5 _namespace_ `namespace ChooserEditor` (scope `UE::UAF`)
- L7 _prototype_ `void RegisterChooserAnimNodeWidgets();` (scope `UE::UAF::ChooserEditor`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/ChooserOutlinerItemDetails.h` (Private)


#### class `UE::UAF::ChooserEditor::FChooserOutlinerItemDetails`  
`class FChooserOutlinerItemDetails : public Workspace::IWorkspaceOutlinerItemDetails`  
_L9-23_
- inherits: `Workspace::IWorkspaceOutlinerItemDetails`
- L12 _public prototype_ `virtual ~FChooserOutlinerItemDetails() override = default;`
- L14 _public prototype_ `virtual FString GetDisplayString(const FWorkspaceOutlinerItemExport& Export) const override;`
- L15 _public prototype_ `virtual FSlateColor GetItemColor(const FWorkspaceOutlinerItemExport& Export) const override;`
- L16 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`
- L17 _public prototype_ `virtual bool HandleDoubleClick(const FToolMenuContext& ToolMenuContext) const override;`
- L18 _public prototype_ `virtual bool CanDelete(const FWorkspaceOutlinerItemExport& Export) const override;`
- L19 _public prototype_ `virtual void Delete(TConstArrayView<FWorkspaceOutlinerItemExport> Exports) const override;`
- L20 _public prototype_ `virtual bool CanRename(const FWorkspaceOutlinerItemExport& Export) const override;`
- L21 _public prototype_ `virtual void Rename(const FWorkspaceOutlinerItemExport& Export, const FText& InName) const override;`
- L22 _public prototype_ `virtual bool ValidateName(const FWorkspaceOutlinerItemExport& Export, const FText& InName, FText& OutErrorMessage) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace ChooserEditor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFAnimationChooserInitializer.h` (Private)


#### struct `FUAFAnimationChooserInitializer`  
`struct FUAFAnimationChooserInitializer : public FChooserInitializer`  
_L10-18_
- reflection: `USTRUCT(DisplayName="UAF Animation Chooser", meta = (ToolTip="A ChooserTable for use with the ChooserPlayer UAF Trait.\nReturns any type of Asset which has a registered UAF Graph Factory."))`
- inherits: `FChooserInitializer`
- L13 _public prototype_ `virtual void InitializeSignature(UChooserSignature* Chooser) const override;`
- L14 _public prototype_ `virtual UClass* OverrideClass(UClass* Class) const override;`
- L17 _public member_ `TArray<TObjectPtr<UUAFSharedVariables>> SharedVariablesAssets;` — `UPROPERTY(EditAnywhere, Category = "Shared Variables")`

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFChooserEditorMode.h` (Private)


#### class `UUAFChooserEditorMode`  
`class UUAFChooserEditorMode : public UEdMode`  
_L15-28_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UEdMode`
- L19 _public member_ `const static FEditorModeID EM_UAFChooser;`
- L21 _public prototype_ `UUAFChooserEditorMode();`
- L23 _public prototype_ `virtual void Enter() override;`
- L24 _public prototype_ `virtual void Exit() override;`
- L25 _public prototype_ `virtual void CreateToolkit() override;`
- L26 _public prototype_ `virtual void BindCommands() override;`

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFChooserEditorModeToolkit.h` (Private)


#### class `FUAFChooserEditorModeToolkit`  
`class FUAFChooserEditorModeToolkit : public FModeToolkit`  
_L8-23_
- inherits: `FModeToolkit`
- L12 _public prototype_ `FUAFChooserEditorModeToolkit(UUAFChooserEditorMode* InEditorMode);`
- L15 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L16 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L18 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;`
- L19 _public prototype_ `virtual void ShutdownUI() override;`
- L22 _protected member_ `TWeakObjectPtr<UUAFChooserEditorMode> WeakEditorMode;`

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFChooserEditorModule.h` (Private)


#### class `UE::UAF::ChooserEditor::FModule`  
`class FModule : public IModuleInterface`  
_L12-19_
- inherits: `IModuleInterface`
- L15 _private prototype_ `virtual void StartupModule() override;`
- L16 _private prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `FTopLevelAssetPath ChooserClassPath;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace ChooserEditor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFChooserTableAssetDefinition.h` (Private)


#### class `UAssetDefinition_UAFAnimChooserTable`  
`class UAssetDefinition_UAFAnimChooserTable : public UAssetDefinitionDefault`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L19 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L20 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L24 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L29 _public function_ `virtual bool ShouldSaveExternalPackages() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AnimNextAssetDefinitions"`

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFGraphChooserWidget.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace UAF` (scope `UE`)
- L5 _namespace_ `namespace ChooserEditor` (scope `UE::UAF`)
- L7 _prototype_ `void RegisterChooserWidgets();` (scope `UE::UAF::ChooserEditor`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserEditor/Private/UAFVariableMenus.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace UAF` (scope `UE`)
- L5 _namespace_ `namespace ChooserEditor` (scope `UE::UAF`)
- L7 _prototype_ `void RegisterVariableMenus();` (scope `UE::UAF::ChooserEditor`)
