# Plugins / DataLinkJsonEditor

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkJsonEditor`
- headers: 5; symbols: 55
- symbol kinds: class=3, delegate=2, function=3, member=15, namespace=4, prototype=26, struct=2
- PrivateDependencyModuleNames: AssetTools, BlueprintGraph, ContentBrowser, Core, CoreUObject, DataLinkEditor, Engine, JsonUtilities, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Json

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJsonEditor/Private/DataLinkJsonEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkJsonEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkJsonEditor, Log, All);`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJsonEditor/Private/DataLinkJsonEditorMenu.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DataLinkJsonEditor` (scope `UE`)
- L14 _prototype_ `void RegisterMenus();` (scope `UE::DataLinkJsonEditor`)
- L16 _prototype_ `void PopulateToolbar(UToolMenu* InToolMenu);` (scope `UE::DataLinkJsonEditor`)
- L18 _prototype_ `TConstStructView<FJsonObjectWrapper> GetPreviewOutputDataView(const IDataLinkEditorMenuContext& InMenuContext);` (scope `UE::DataLinkJsonEditor`)
- L20 _prototype_ `bool CanMakeStructsFromJson(const FToolMenuContext& InMenuContext);` (scope `UE::DataLinkJsonEditor`)
- L22 _prototype_ `void MakeStructsFromJson(const FToolMenuContext& InMenuContext);` (scope `UE::DataLinkJsonEditor`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJsonEditor/Private/DataLinkJsonEditorModule.h` (Private)


#### class `FDataLinkJsonEditorModule`  
`class FDataLinkJsonEditorModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FDelegateHandle OnToolMenusStartupHandle;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJsonEditor/Private/DataLinkJsonEditorStructGenerator.h` (Private)


#### struct `UE::DataLinkJsonEditor::FStructKey`  
`struct FStructKey`  
_L20-37_
- desc: Identifies a map of Name to Json Value to identify a struct that can be re-used
- L22 _public prototype_ `explicit FStructKey(FStructGenerator& InStructGenerator, const TMap<FJsonObject::FStringType, TSharedPtr<FJsonValue>>& InJsonEntries);`
- L24 _public function_ `bool operator==(const FStructKey& InOther) const`
- L35 _private member_ `uint32 Hash = 0;`
- L36 _private member_ `TMap<FString, FEdGraphPinType> JsonTypeMap;`

#### class `UE::DataLinkJsonEditor::FStructGenerator`  
`class FStructGenerator`  
_L40-72_
- desc: Generates as many structs as needed to create a hierarchy that matches the Json Object
- L52 _public prototype_ `static void GenerateFromJson(const FParams& InParams);`
- L55 _private prototype_ `bool FromJsonValue(const TSharedPtr<FJsonValue>& InJsonValue, FEdGraphPinType& OutPinType, const FString& InNameToUse);`
- L57 _private prototype_ `void AddVariable(UUserDefinedStruct* InStruct, const FString& InName, const TSharedPtr<FJsonValue>& InValue);`
- L59 _private prototype_ `UUserDefinedStruct* CreateEmptyStruct(const FString& InNameToUse);`
- L61 _private prototype_ `UUserDefinedStruct* GetOrCreateStruct(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InNameToUse);`
- L63 _private prototype_ `TArray<UObject*> GetGeneratedStructs() const;`
- L65 _private member_ `TMap<FStructKey, TObjectPtr<UUserDefinedStruct>> GeneratedStructs;`
- L67 _private member_ `TObjectPtr<UStructureFactory> StructureFactory = nullptr;`
- L69 _private member_ `FString BasePath;`
- L71 _private member_ `FString StructPrefix;`

#### struct `UE::DataLinkJsonEditor::FStructGenerator::FParams`  
`struct FParams`  
_L45-51_
- L47 _public member_ `TSharedPtr<FJsonObject> JsonObject;`
- L48 _public member_ `FString BasePath;`
- L49 _public member_ `FString StructPrefix;`
- L50 _public member_ `FString RootStructName;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DataLinkJsonEditor` (scope `UE`)
- L29 _function_ `friend uint32 GetTypeHash(const FStructKey& InKey)` (scope `UE::DataLinkJsonEditor`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJsonEditor/Private/Widgets/SDataLinkJsonEditorStructGeneratorConfig.h` (Private)


#### class `SDataLinkJsonEditorStructGeneratorConfig`  
`class SDataLinkJsonEditorStructGeneratorConfig : public SWindow`  
_L7-43_
- inherits: `SWindow`
- L10 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCommit, const SDataLinkJsonEditorStructGeneratorConfig&);`
- L12 _public function_ `SLATE_BEGIN_ARGS(SDataLinkJsonEditorStructGeneratorConfig)`
- L13 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FString, DefaultPath) SLATE_EVENT(FOnCommit, OnCommit) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `const FString& GetPath() const;`
- L21 _public prototype_ `const FString& GetPrefix() const;`
- L22 _public prototype_ `const FString& GetRootStructName() const;`
- L25 _private prototype_ `FReply OnCommit();`
- L26 _private prototype_ `FReply OnCancel();`
- L28 _private prototype_ `void OnPathChange(const FString& InNewPath);`
- L30 _private prototype_ `void OnPrefixChange(const FText& InNewPrefix);`
- L32 _private prototype_ `void OnRootStructNameChange(const FText& InNewRootName);`
- L34 _private prototype_ `bool ValidateConfiguration();`
- L36 _private member_ `FString Path;`
- L38 _private member_ `FString Prefix;`
- L40 _private member_ `FString RootStructName;`
- L42 _private member_ `FOnCommit OnCommitDelegate;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCommit, const SDataLinkJsonEditorStructGeneratorConfig&);`
