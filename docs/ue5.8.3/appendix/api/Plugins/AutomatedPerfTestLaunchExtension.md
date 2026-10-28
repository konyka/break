# Plugins / AutomatedPerfTestLaunchExtension

- module root: `Plugins/Performance/AutomatedPerfTestTools/Source/AutomatedPerfTestLaunchExtension`
- headers: 2; symbols: 39
- symbol kinds: class=3, enum=1, enumerator=6, function=3, member=2, prototype=23, typedef=1

### `Plugins/Performance/AutomatedPerfTestTools/Source/AutomatedPerfTestLaunchExtension/Private/AutomatedPerfTestLaunchExtension.h` (Private)


#### enum `EAutomatedPerfTestType`  
`enum class EAutomatedPerfTestType : uint8`  
_L9-17_
- L11 _public enumerator_ `Sequence`
- L12 _public enumerator_ `Replay`
- L13 _public enumerator_ `ProfileGo`
- L14 _public enumerator_ `StaticCamera`
- L15 _public enumerator_ `Material`
- L16 _public enumerator_ `MAX`

#### class `FAutomatedPerfTestLaunchExtensionInstance`  
`class FAutomatedPerfTestLaunchExtensionInstance : public ProjectLauncher::FAutomatedTestLaunchExtensionInstance`  
_L19-67_
- inherits: `ProjectLauncher::FAutomatedTestLaunchExtensionInstance`
- L21 _private typedef_ `using Super = ProjectLauncher::FAutomatedTestLaunchExtensionInstance;`
- L23 _public function_ `FAutomatedPerfTestLaunchExtensionInstance(FArgs& InArgs) : FAutomatedTestLaunchExtensionInstance(InArgs)`
- L24 _public prototype_ `virtual ~FAutomatedPerfTestLaunchExtensionInstance() = default;`
- L26 _public prototype_ `virtual void OnPropertyChanged() override;`
- L27 _public prototype_ `virtual void OnTestAdded(ILauncherProfileAutomatedTestRef AutomatedTest) override;`
- L29 _public prototype_ `virtual void CustomizeTree(ProjectLauncher::FLaunchProfileTreeData& ProfileTreeData) override;`
- L30 _public prototype_ `virtual void CustomizeUATCommandLine(FString& InOutCommandLine) override;`
- L33 _private prototype_ `void ExportProfileGoScenarios(const FString& Filename);`
- L35 _private prototype_ `void AddTestNodeOptions(ProjectLauncher::FLaunchProfileTreeNode& TreeNode);`
- L36 _private prototype_ `void AddSequenceTestNodeOptions(ProjectLauncher::FLaunchProfileTreeNode& TreeNode);`
- L37 _private prototype_ `void AddReplayTestNodeOptions(ProjectLauncher::FLaunchProfileTreeNode& TreeNode);`
- L38 _private prototype_ `void AddProfileGoTestNodeOptions(ProjectLauncher::FLaunchProfileTreeNode& TreeNode);`
- L39 _private prototype_ `void AddStaticCameraTestNodeOptions(ProjectLauncher::FLaunchProfileTreeNode& TreeNode);`
- L40 _private prototype_ `void AddMaterialTestNodeOptions(ProjectLauncher::FLaunchProfileTreeNode& TreeNode);`
- L42 _private prototype_ `void OnTestTypeSelectionChanged(EAutomatedPerfTestType Type);`
- L43 _private prototype_ `void SetTestType(EAutomatedPerfTestType Type);`
- L44 _private prototype_ `EAutomatedPerfTestType GetTestType() const;`
- L46 _private prototype_ `const ProjectLauncher::FProjectSettings GetProjectSettings() const;`
- L47 _private prototype_ `const FConfigSection* GetConfigSection(EAutomatedPerfTestType TestType) const;`
- L50 _private function_ `template<EAutomatedPerfTestType TestType> ProjectLauncher::FLaunchProfileTreeNode::FCallbacks GetTestTypeCallbacks()`
- L66 _private member_ `EAutomatedPerfTestType CurrentTestType = EAutomatedPerfTestType::Sequence;`

#### class `FAutomatedPerfTestLaunchExtension`  
`class FAutomatedPerfTestLaunchExtension : public ProjectLauncher::FAutomatedTestLaunchExtension`  
_L70-77_
- inherits: `ProjectLauncher::FAutomatedTestLaunchExtension`
- L73 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile(ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs) override;`
- L74 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L75 _public prototype_ `virtual FText GetDisplayName() const override;`
- L76 _public prototype_ `virtual void GetExtensionsMenuEntry(FExtensionsMenuEntry& MenuEntry) const override;`

#### Free symbols / members of external scopes

- L53 _function_ `` (scope `FAutomatedPerfTestLaunchExtensionInstance::GetTestTypeCallbacks`)

### `Plugins/Performance/AutomatedPerfTestTools/Source/AutomatedPerfTestLaunchExtension/Public/AutomatedPerfTestLaunchExtensionModule.h` (Public)


#### class `FAutomatedPerfTestLaunchExtensionModule`  
`class FAutomatedPerfTestLaunchExtensionModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `TArray<TSharedRef<ProjectLauncher::FLaunchExtension>> Extensions;`
