# Plugins / UAFLayeringEditor

- module root: `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor`
- headers: 6; symbols: 42
- symbol kinds: class=7, member=2, namespace=9, prototype=24
- PrivateDependencyModuleNames: AssetDefinition, EditorFramework, EditorInteractiveToolsFramework, InteractiveToolsFramework, RigVM, UAF, UAFAnimGraph, UAFEditor, UAFLayering, UAFLayeringUncookedOnly, UnrealEd
- PrivateIncludePathModuleNames: UAFEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, RigVMDeveloper, Slate, SlateCore, UAFUncookedOnly, WorkspaceEditor

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor/Internal/UAFLayerStackFactory.h` (Internal)


#### class `UUAFLayerStackFactory`  
`class UUAFLayerStackFactory : public UFactory`  
_L10-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `UUAFLayerStackFactory();`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor/Private/UAFLayerStackAssetDefinition.h` (Private)


#### class `UAssetDefinition_UAFLayerStack`  
`class UAssetDefinition_UAFLayerStack : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor/Private/UAFLayeringEditorMode.h` (Private)


#### class `UUAFLayeringEditorMode`  
`class UUAFLayeringEditorMode : public UEdMode`  
_L10-17_
- reflection: `UCLASS()`
- inherits: `UEdMode`
- L14 _public member_ `const static FEditorModeID EM_UAFLayeringMode;`
- L16 _public prototype_ `UUAFLayeringEditorMode();`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor/Private/UAFLayeringEditorModule.h` (Private)


#### class `UE::UAF::LayeringEditor::FUAFLayeringEditorModule`  
`class FUAFLayeringEditorModule : public IModuleInterface`  
_L12-23_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `TSharedRef<SWidget> MakeDocumentWidget(const UE::Workspace::FWorkspaceEditorContext& InContext);`
- L22 _private prototype_ `void GetBreadcrumbTrail(const UE::Workspace::FWorkspaceEditorContext& InContext, TArray<TSharedPtr<UE::Workspace::FWorkspaceBreadcrumb>>& OutBreadcrumbs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace LayeringEditor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor/Private/Workspace/LayerStackItemDetails.h` (Private)


#### class `UE::UAF::LayeringEditor::ULayerStackItemDetails`  
`class ULayerStackItemDetails : public UE::Workspace::IWorkspaceOutlinerItemDetails`  
_L9-14_
- inherits: `UE::Workspace::IWorkspaceOutlinerItemDetails`
- L12 _public prototype_ `virtual bool HandleSelected(const FToolMenuContext& ToolMenuContext) const override;`
- L13 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`

#### class `UE::UAF::LayeringEditor::ULayerStackLayerItemDetails`  
`class ULayerStackLayerItemDetails : public UE::Workspace::IWorkspaceOutlinerItemDetails`  
_L16-24_
- inherits: `UE::Workspace::IWorkspaceOutlinerItemDetails`
- L19 _public prototype_ `virtual bool IsExpandedByDefault() const override;`
- L20 _public prototype_ `virtual FString GetDisplayString(const FWorkspaceOutlinerItemExport& Export) const override;`
- L21 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`
- L22 _public prototype_ `virtual bool HandleSelected(const FToolMenuContext& ToolMenuContext) const override;`
- L23 _public prototype_ `virtual bool HandleDoubleClick(const FToolMenuContext& ToolMenuContext) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace LayeringEditor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringEditor/Private/Workspace/LayerStackViewportController.h` (Private)


#### class `UE::UAF::LayeringEditor::FLayerStackViewportController`  
`class FLayerStackViewportController : public Workspace::IWorkspaceViewportController`  
_L12-22_
- inherits: `Workspace::IWorkspaceViewportController`
- L15 _public prototype_ `virtual void OnEnter(const FViewportContext& InViewportContext) override;`
- L16 _public prototype_ `virtual void OnExit(FAdvancedPreviewScene* PreviewScene) override;`
- L19 _private prototype_ `void AddMeshToPreview(FAdvancedPreviewScene* PreviewScene, const TObjectPtr<const UUAFSystem> System, const TObjectPtr<const UUAFLayerStack> LayerStack, USkeletalMesh* InSkeletalMesh);`
- L21 _private member_ `TArray<AActor*> PreviewActors;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace LayeringEditor` (scope `UE::UAF`)
