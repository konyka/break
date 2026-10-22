# Plugins / UAFStateTreeEditor

- module root: `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor`
- headers: 7; symbols: 59
- symbol kinds: class=7, function=7, macro=1, member=6, namespace=11, prototype=27
- PrivateDependencyModuleNames: AssetDefinition, EditorFramework, EditorInteractiveToolsFramework, InteractiveToolsFramework, MessageLog, PropertyEditor, RigVM, StructUtilsEditor, ToolMenus, UAF, UAFAnimGraph, UAFAnimNode, UAFAnimNodeEditor, UAFStateTree, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, PropertyBindingUtils, RigVMDeveloper, Slate, SlateCore, StateTreeEditorModule, StateTreeModule, UAFEditor, UAFStateTreeUncookedOnly, UAFUncookedOnly, WorkspaceEditor

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Internal/AnimNextStateTreeFactory.h` (Internal)


#### class `UAnimNextStateTreeFactory`  
`class UAnimNextStateTreeFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `UAnimNextStateTreeFactory();`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L18 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Private/AnimNextStateTreeAssetDefinition.h` (Private)


#### class `UAssetDefinition_AnimNextStateTree`  
`class UAssetDefinition_AnimNextStateTree : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public function_ `virtual bool ShouldSaveExternalPackages() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AnimNextAssetDefinitions"`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Private/AnimNextStateTreeEditorHost.h` (Private)


#### class `FAnimNextStateTreeEditorHost`  
`class FAnimNextStateTreeEditorHost : public IStateTreeEditorHost`  
_L15-40_
- inherits: `IStateTreeEditorHost`
- L18 _public prototype_ `void Init(const TWeakPtr<UE::Workspace::IWorkspaceEditor>& InWeakWorkspaceEditor);`
- L21 _public prototype_ `virtual UStateTree* GetStateTree() const override;` — IStateTreeEditorHost overrides
- L22 _public prototype_ `virtual FName GetCompilerLogName() const override;`
- L23 _public prototype_ `virtual FName GetCompilerTabName() const override;`
- L24 _public prototype_ `virtual bool ShouldShowCompileButton() const override;`
- L25 _public prototype_ `virtual bool CanToolkitSpawnWorkspaceTab() const override;`
- L26 _public prototype_ `virtual FSimpleMulticastDelegate& OnStateTreeChanged() override;`
- L27 _public prototype_ `virtual TSharedPtr<IDetailsView> GetAssetDetailsView() override;`
- L28 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() override;`
- L29 _public prototype_ `virtual TSharedPtr<UE::StateTreeEditor::FWorkspaceTabHost> GetTabHost() const override;`
- L32 _protected prototype_ `void OnWorkspaceFocusedDocumentChanged(const UE::Workspace::FWorkspaceDocument& InDocument) const;`
- L34 _protected member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WeakWorkspaceEditor;`
- L35 _protected member_ `FSimpleMulticastDelegate OnStateTreeChangedDelegate;`
- L36 _protected member_ `TSharedPtr<UE::StateTreeEditor::FWorkspaceTabHost> TabHost;`
- L39 _protected member_ `mutable TWeakObjectPtr<UAnimNextStateTree> WeakLastStateTree;` — Last state tree, cached to avoid changing debugger & losing context more than needed

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Private/AnimNextStateTreeEditorModule.h` (Private)


#### class `UE::UAF::StateTree::FAnimNextStateTreeEditorModule`  
`class FAnimNextStateTreeEditorModule : public IAnimNextStateTreeEditorModule`  
_L10-18_
- inherits: `IAnimNextStateTreeEditorModule`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FTopLevelAssetPath StateTreeClassPath;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Private/StateTreeAssetCompilationHandler.h` (Private)


#### class `UE::UAF::StateTree::FStateTreeAssetCompilationHandler`  
`class FStateTreeAssetCompilationHandler : public UE::UAF::Editor::FAssetCompilationHandler`  
_L15-37_
- inherits: `UE::UAF::Editor::FAssetCompilationHandler`
- L18 _public prototype_ `explicit FStateTreeAssetCompilationHandler(UObject* InObject);`
- L21 _public prototype_ `void Initialize();` — Non-constructor setup (e.g. binding SP delegates)
- L25 _private prototype_ `virtual void Compile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, UObject* InAsset) override;` — IAssetCompilationHandler interface
- L26 _private prototype_ `virtual UE::UAF::Editor::ECompileStatus GetCompileStatus(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, const UObject* InAsset) const override;`
- L28 _private prototype_ `void UpdateCachedInfo();`
- L30 _private prototype_ `void HandleAssetChanged();`
- L31 _private prototype_ `void HandleStatesChanged(const TSet<UStateTreeState*>& , const FPropertyChangedEvent& );`
- L32 _private prototype_ `void HandleStateAdded(UStateTreeState* , UStateTreeState* );`
- L33 _private prototype_ `void HandleStatesRemoved(const TSet<UStateTreeState*>& );`
- L34 _private prototype_ `void HandleStatesMoved(const TSet<UStateTreeState*>& , const TSet<UStateTreeState*>& );`
- L36 _private member_ `TWeakObjectPtr<UStateTree> CachedStateTree;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Public/IAnimNextStateTreeEditorModule.h` (Public)


#### class `UE::UAF::StateTree::IAnimNextStateTreeEditorModule`  
`class IAnimNextStateTreeEditorModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeEditor/Public/UAFStateTreeEditorSchema.h` (Public)


#### class `UUAFStateTreeEditorSchema`  
`class UUAFStateTreeEditorSchema : public UStateTreeEditorSchema`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UStateTreeEditorSchema`
- L14 _private function_ `virtual EStateTreeTransitionEditingRules GetTransitionEditingRules(TNotNull<UStateTreeEditorData*> StateTree) const override`
