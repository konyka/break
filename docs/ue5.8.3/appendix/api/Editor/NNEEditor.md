# Editor / NNEEditor

- module root: `Source/Editor/NNEEditor`
- headers: 6; symbols: 80
- symbol kinds: class=4, enum=1, enumerator=2, function=4, macro=5, member=15, namespace=14, prototype=32, struct=2, typedef=1
- PrivateDependencyModuleNames: AssetTools, DeveloperSettings, NNE, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Editor/NNEEditor/Private/NNEEditorModelDataActions.h` (Private)


#### class `UE::NNEEditor::Private::FModelDataAssetTypeActions`  
`class FModelDataAssetTypeActions : public FAssetTypeActions_Base`  
_L12-22_
- inherits: `FAssetTypeActions_Base`
- L16 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L17 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L18 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L19 _public prototype_ `virtual uint32 GetCategories() override;`
- L20 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEEditor` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNEEditor`)

### `Source/Editor/NNEEditor/Private/NNEEditorModelDataEditorToolkit.h` (Private)


#### class `UNNEEditorEmptySelectionModels`  
`class UNNEEditorEmptySelectionModels : public UObject`  
_L15-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public member_ `TArray<int> ModelIndices;` — `UPROPERTY()`

#### class `UE::NNEEditor::Private::FModelDataEditorToolkit`  
`class FModelDataEditorToolkit : public FAssetEditorToolkit`  
_L25-78_
- inherits: `FAssetEditorToolkit`
- L28 _public prototype_ `void InitEditor(const TArray<UNNEModelData*>& InModels);`
- L31 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — FAssetEditorToolkit interface
- L32 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L33 _public function_ `virtual FName GetToolkitFName() const override`
- L34 _public function_ `virtual FText GetBaseToolkitName() const override`
- L35 _public prototype_ `virtual FText GetToolkitName() const override;`
- L36 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L37 _public function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L38 _public function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L39 _public prototype_ `virtual void OnClose() override;`
- L59 _private member_ `static constexpr int AllCheckBoxIndex = -1;`
- L61 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs&);`
- L62 _private prototype_ `void ReloadSettings();`
- L63 _private prototype_ `void ClearSettings();`
- L64 _private prototype_ `void OnRuntimePropertyChanged(const FPropertyChangedEvent& Property) const;`
- L65 _private prototype_ `EVisibility GetErrorMessageVisibility() const;`
- L66 _private prototype_ `FText GetAreaErrorMessageText(const int RuntimeIndex) const;`
- L67 _private prototype_ `bool GetAreaIsExpandable(const int RuntimeIndex) const;`
- L68 _private prototype_ `FString ButtonIndexToRuntimeName(const int ButtonIndex) const;`
- L69 _private prototype_ `ECheckBoxState GetCheckBoxState(const int ButtonIndex) const;`
- L70 _private prototype_ `void SetCheckBoxState(const ECheckBoxState NewState, const int Index);`
- L72 _private member_ `TArray<UNNEModelData*> Models;`
- L73 _private member_ `TArray<FString> AllRuntimeNames;`
- L74 _private member_ `TArray<FRuntimeArea> Runtimes;`
- L75 _private member_ `TMap<uint32, const FSettingsIndex> SettingsIDToIndex;`
- L76 _private member_ `UNNEEditorEmptySelectionModels* EmptySelectionModels;`
- L77 _private member_ `FDelegateHandle PostUndoRedoHandle;`

#### struct `UE::NNEEditor::Private::FModelDataEditorToolkit::FSettingsIndex`  
`struct FSettingsIndex`  
_L44-49_
- L46 _public member_ `const FString RuntimeName;`
- L47 _public member_ `const int32 ModelIndex;`
- L48 _public member_ `UObject* Settings;`

#### struct `UE::NNEEditor::Private::FModelDataEditorToolkit::FRuntimeArea`  
`struct FRuntimeArea`  
_L51-57_
- L53 _public member_ `const FString Name;`
- L54 _public member_ `const TSharedRef<IDetailsView> DetailsView;`
- L55 _public member_ `bool IsVisible;`
- L56 _public member_ `FText ErrorMessage;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace NNEEditor` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::NNEEditor`)

### `Source/Editor/NNEEditor/Private/NNEEditorModelDataFactory.h` (Private)


#### class `UNNEModelDataFactory`  
`class UNNEModelDataFactory : public UFactory`  
_L18-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- desc: Class for importing and creating new UNNEModelData assets. The currently supported format is .onnx. The factory is invoked when a file of this format is dragged to the editor's content browser.
- L23 _public prototype_ `UNNEModelDataFactory(const FObjectInitializer& ObjectInitializer);`
- L27 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L28 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NNEEDITOR_API`

### `Source/Editor/NNEEditor/Private/NNEEditorOnnxFileLoaderHelper.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEEditor` (scope `UE`)
- L8 _namespace_ `namespace Internal` (scope `UE::NNEEditor`)
- L8 _namespace_ `namespace OnnxFileLoaderHelper` (scope `UE::NNEEditor::Internal`)
- L10 _prototype_ `bool InitUNNEModelDataFromFile(UNNEModelData& ModelData, int64& ModelFileSize, const FString& Filename);` (scope `UE::NNEEditor::Internal::OnnxFileLoaderHelper`)

### `Source/Editor/NNEEditor/Private/NNEEditorOnnxModelInspector.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace NNEEditor` (scope `UE`)
- L6 _namespace_ `namespace Private` (scope `UE::NNEEditor`)
- L6 _namespace_ `namespace OnnxModelInspectorHelper` (scope `UE::NNEEditor::Private`)
- L8 _prototype_ `void SetupSharedLibFunctionPointer(void* SharedLibHandle);` (scope `UE::NNEEditor::Private::OnnxModelInspectorHelper`)
- L9 _prototype_ `void ClearSharedLibFunctionPointer();` (scope `UE::NNEEditor::Private::OnnxModelInspectorHelper`)
- L10 _prototype_ `bool IsSharedLibFunctionPointerSetup();` (scope `UE::NNEEditor::Private::OnnxModelInspectorHelper`)
- L11 _prototype_ `bool GetExternalDataFilePaths(TConstArrayView<uint8> ONNXData, TSet<FString>& ExternalDataFilePaths);` (scope `UE::NNEEditor::Private::OnnxModelInspectorHelper`)

### `Source/Editor/NNEEditor/Private/NNEEditorOnnxTools.h` (Private)


#### enum `NNEEditorOnnxTools_Status`  
`enum class NNEEditorOnnxTools_Status : uint8`  
_L26-30_
- L28 _public enumerator_ `Ok = 0`
- L29 _public enumerator_ `Fail_CannotParseAsModelProto`

#### Free symbols / members of external scopes

- L8 _macro_ `#define NNEEDITORONNXTOOLS_API __declspec(dllexport)` — Microsoft
- L11 _macro_ `#define NNEEDITORONNXTOOLS_API __attribute__((visibility("default")))` — GCC
- L13 _macro_ `#define NNEEDITORONNXTOOLS_API unsupported_platform`
- L16 _macro_ `#define NNEEDITORONNXTOOLS_API`
- L21 _typedef_ `typedef uint8_t uint8;`
- L37 _prototype_ `NNEEditorOnnxTools_Status NNEEditorOnnxTools_CreateExternalDataDescriptor(const void* InData, const int Size, NNEEditorOnnxTools_ExternalDataDescriptor** Descriptor);`
- L39 _prototype_ `void NNEEditorOnnxTools_ReleaseExternalDataDescriptor(NNEEditorOnnxTools_ExternalDataDescriptor** Descriptor);`
- L41 _prototype_ `const char* NNEEditorOnnxTools_GetNextExternalDataPath(NNEEditorOnnxTools_ExternalDataDescriptor* Descriptor);`
