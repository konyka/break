# Plugins / CustomizableObjectEditor

- module root: `Plugins/Mutable/Source/CustomizableObjectEditor`
- headers: 275; symbols: 6000
- symbol kinds: class=326, delegate=45, enum=41, enumerator=139, externvar=1, function=346, macro=109, member=1875, namespace=152, prototype=2824, struct=120, typedef=21, variable=1
- DynamicallyLoadedModuleNames: ClassViewer, MainFrame, SceneOutliner, WorkspaceMenuStructure
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimGraph, AnimGraphRuntime, AppFramework, ApplicationCore, AssetDefinition, AssetTools, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, ContentBrowser, Core, CoreUObject, CurveEditor, DeveloperToolSettings, EditorFramework, EditorWidgets, Engine, GameplayTags, GraphEditor, ImageCore, InputCore, Kismet, KismetWidgets, LevelEditor, MeshDescription, MutableRuntime, MutableTools, Persona, Projects, RHI, RawMesh, RenderCore, Slate, SlateCore, StructUtilsEditor, TargetPlatform, TextureBuildUtilities, TextureCompressor, ToolMenus, ToolWidgets, UMG, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, MeshUtilities, MessageLog, SkeletonEditor, WorkspaceMenuStructure
- PublicDependencyModuleNames: CustomizableObject, DerivedDataCache, MutableTools, PropertyEditor

### `Plugins/Mutable/Source/CustomizableObjectEditor/Internal/MuCOE/CompilationOptions.h` (Internal)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _prototype_ `FCompilationOptions GetCompilationOptions(const UCustomizableObject& Object);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Internal/MuCOE/CompileRequest.h` (Internal)


#### struct `FCompilationRequest`  
`struct FCompilationRequest`  
_L18-59_
- L20 _public prototype_ `FCompilationRequest(UCustomizableObject& CustomizableObject);`
- L22 _public prototype_ `UCustomizableObject* GetCustomizableObject();`
- L24 _public prototype_ `void SetDerivedDataCachePolicy(UE::DerivedData::ECachePolicy InCachePolicy);`
- L25 _public prototype_ `UE::DerivedData::ECachePolicy GetDerivedDataCachePolicy() const;`
- L27 _public prototype_ `void BuildDerivedDataCacheKey();`
- L28 _public prototype_ `UE::DerivedData::FCacheKey GetDerivedDataCacheKey() const;`
- L30 _public prototype_ `void SetCompilationState(ECompilationStatePrivate InState, ECompilationResultPrivate InResult);`
- L32 _public prototype_ `ECompilationStatePrivate GetCompilationState() const;`
- L33 _public prototype_ `ECompilationResultPrivate GetCompilationResult() const;`
- L35 _public prototype_ `bool operator==(const FCompilationRequest& Other) const;`
- L38 _private member_ `TWeakObjectPtr<UCustomizableObject> CustomizableObject;`
- L40 _private member_ `ECompilationStatePrivate State = ECompilationStatePrivate::None;`
- L41 _private member_ `ECompilationResultPrivate Result = ECompilationResultPrivate::Unknown;`
- L43 _private member_ `UE::DerivedData::ECachePolicy DDCPolicy = UE::DerivedData::ECachePolicy::None;`
- L44 _private member_ `UE::DerivedData::FCacheKey DDCKey;`
- L47 _public member_ `FCompilationOptions Options;`
- L49 _public member_ `TArray<FText> Warnings;`
- L50 _public member_ `TArray<FText> Errors;`
- L52 _public member_ `FCompileDelegate Callback;`
- L53 _public member_ `FCompileNativeDelegate CallbackNative;`
- L55 _public member_ `bool bAsync = true;`
- L56 _public member_ `bool bSkipIfCompiled = false;`
- L57 _public member_ `bool bSkipIfNotOutOfDate = false;`
- L58 _public member_ `bool bSilentCompilation = true;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Internal/MuCOE/CustomizableObjectBenchmarkingUtils.h` (Internal)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace CustomizableObjectBenchmarkingUtils`
- L23 _prototype_ `bool GenerateDeterministicSetOfInstances(UCustomizableObject& TargetCustomizableObject, const uint16 InstancesPerState, TSpscQueue<TStrongObjectPtr<UCustomizableObjectInstance>>& OutGeneratedInstances, uint32& OutSuccesfullyGeneratedInstanceCount);` (scope `CustomizableObjectBenchmarkingUtils`) — Generates a set of instances. If the CO does not change the instances generated from one run to the other will be equal. @param TargetCustomizableObject The customizable object used to generate the set of deterministic instances. @param InstancesPerState The target amount of instances we want generated for each state of the CO. Ex: If the CO has 2 states and we define 4 here we will get a total of 2 * 4 instances as output. @param OutGeneratedInstances Queue with the generated instances. Based on the amount of states and the value set in InstancesPerState @param OutSuccesfullyGeneratedInstanceCount The total of instances generated successfully [0 , InstancesPerState * COStateCount] @return
- L30 _prototype_ `int32 GetOptimizationLevelForBenchmarking();` (scope `CustomizableObjectBenchmarkingUtils`) — Returns the optimization level to be used in benchmarking runs @return Am integer value representing the optimization level that should be used for benchmarking runs

### `Plugins/Mutable/Source/CustomizableObjectEditor/Internal/MuCOE/CustomizableObjectInstanceBakingUtils.h` (Internal)


#### class `FResourceBakingData`  
`class FResourceBakingData`  
_L24-189_
- desc: Data required by an asset to be able to be baked during the runtime of the baking operation. It also serves as an interface to get the different substrings that form the actual baked package name to ease name manipulation once the baking operation has completed
- L28 _public function_ `FResourceBakingData(const FString& InPrefix, const FString& inUserGivenName, const FString& InRawResourceName, const FString& InComponentName, const FString& InAssetPath, bool bInRemoveRestrictedChars): Prefix(InPrefix), ResourceName(InRawResourceName), ComponentName(InComponentName), UserGivenName(inUserGivenName), AssetPath(InAssetPath), bReplaceRestrictedChars(bInRemoveRestrictedChars)`
- L43 _public prototype_ `bool Validate() const;` — Ensure that the data contained in this object is valid and well-formed @return true If it is ok, false otherwise
- L49 _public prototype_ `FString GetResourceComposedName();` — Generate and get the Composed Resource Name to be used when duplicating (baking) the object represented by this data structure @return The string composed like so : Prefix_ObjectName_ResourceName(_UniqueAssetSuffix)
- L55 _public prototype_ `FString GetResourceComposedFullPath();` — Get the complete path to be used when duplicating the package to decide where and how the package is named @return The AssetPath/ComposedResourceName
- L63 _public prototype_ `void MakeComposedResourceNameUnique(const TArray<UObject*>& InCachedResources);` — Given the ComposedName looks for it in the provided array and updates this object data so the next time the ComposedName is generated is unique @param InCachedResources Array of resources we want to make sure the new name does not collide with. @note This does not check the actual path of the objects, just the name as this is intended to be used during the runtime of the bake to prevent collisions within the same bake
- L68 _public prototype_ `void ComputePackageSaveResolutionType();` — Check if the file with the AssetPath + Composed name already exists, and based on that determines the save type to be performed
- L74 _public prototype_ `FString GetPrefixSection() const;` — Get the section of the ComposedResourceName that represents the prefix. @return The prefix string.
- L80 _public prototype_ `FString GetComponentNameSection() const;` — Get the section of the ComposedResourceName that represents the Component Name @return The Component name section.
- L86 _public prototype_ `FString GetUserGivenNameSection() const;` — Get the section of the ComposedResourceName that represents the User provided name @return The User given name section. It can be empty.
- L92 _public prototype_ `FString GetResourceNameSection() const;` — Get the section of the ComposedResourceName that represents the actual Resource Name. @return The Resource name section.
- L98 _public prototype_ `FString GetUniqueAssetNameSuffixSection() const;` — Get the section of the ComposedResourceName that represents the uniqueness suffix added to make the name unique. @return The suffix section.
- L108 _private prototype_ `int32 GetObjectWithNameIndex(const FString& InName, const TArray<UObject*>& Objects ) const;` — Given a collection of UObjects return the index of the one that matches the name provided @param InName The name of the object we are looking for @param Objects The collection of objects we want to check for an element with the given name @return The index of the element whose name matches the one provided or INDEX_NONE if the element could not be found
- L114 _private prototype_ `bool DoesPackageExist(const FString& InPackageFullName, const FString& InAssetName) const;` — Get the package our data points to. This is based on the AssetPath and the ComposedResourceName @return True if the asset is already at path
- L122 _private prototype_ `FString GetCachedComposedResourceName() const;` — Get the last generated Composed Resource Name. @note As the ComposedResourceName changes over time as we update the parts that form it this method is only safe to call once the asset has been baked as no more changes to the CachedComposedResourceName are to be expected @return The last generated ComposedResourceName.
- L130 _public member_ `FString Prefix;` — The prefix (type based) of the resource. It is expected to include a "_" at the end like "T_" or "SKM_".
- L135 _public member_ `FString ResourceName;` — The name of the object that it is being baked. This string is expected to be externally modified during the bake runtime
- L141 _public member_ `FString UniqueAssetNameValueSuffix;` — A suffix string used to make the name of the object Unique. Can be empty if no name collisions are found at the moment of bake
- L146 _public member_ `EPackageSaveResolutionType SaveResolutionType = EPackageSaveResolutionType::None;` — The type of saving operation was performed. Does not affect the behaviour of the bake, but it is useful info for the caller
- L154 _private member_ `const FString ComponentName;` — The component this object is part of.
- L160 _private member_ `const FString UserGivenName;` — The custom name given by the user to differentiate the objects of this bake from others. Can be empty.
- L165 _private member_ `const FString AssetPath;` — The path where to store the asset we are baking.
- L170 _private member_ `FString CachedComposedResourceName;` — Cached version of the ComposedResourceName. Useful for the const consultation of the ComposedResourceName.
- L175 _private member_ `bool bReplaceRestrictedChars = false;` — If true, restricted characters are stripped from the final composed resource name.
- L179 _private member_ `FString PrefixSection;`
- L181 _private member_ `FString ComponentNameSection;`
- L183 _private member_ `FString UserGivenNameSection;`
- L185 _private member_ `FString ResourceNameSection;`
- L187 _private member_ `FString UniqueAssetNameSuffixSection;`

#### Free symbols / members of external scopes

- L17 _prototype_ `void ScheduleCOCompilationForBaking(UCustomizableObjectInstance& InTargetInstance, const FCompileNativeDelegate& InCustomizableObjectCompilationDelegate, const bool bPerformPartialCompilation = false);` — Schedules the async compilation of a given Customizable object and, if a Customizable Object Instance is provided, tries to compile only the data required for that given COI. Use the delegate to know when the operation has completed. @param InTargetInstance The Customizable Object Instance generated from the provided COI that we want to use to limit the scope of the CO compilation. @param InCustomizableObjectCompilationDelegate Delegate invoked once the compilation has completed. @param bPerformPartialCompilation Instead of compiling all the data from the InTargetInstance Co just compile the data required for the provided instance. todo: UE-315780 Make this option true by default when the compilation warnings caused by it are resolved
- L198 _prototype_ `void ScheduleInstanceUpdateForBaking(UCustomizableObjectInstance& InInstance, FInstanceUpdateNativeDelegate& InInstanceUpdateDelegate);` — Schedules the async update of the target instance. It will clear previous update data. This method will also take care of setting and later resetting the state of the Customizable Object System. @param InInstance The instance we want to update so we can later bake it's resources. @param InInstanceUpdateDelegate Delegate to be called after the instance gets updated.
- L209 _prototype_ `bool BakeCustomizableObjectInstance( UCustomizableObjectInstance& InInstance, const FBakingConfiguration& Configuration, bool bIsUnattendedExecution, TMap<UPackage*,const FResourceBakingData>& OutSavedPackages);` — Serializes onto disk the resources used by the targeted Customizable Object Instance. The operation can be configured in the FInstanceBakingSettings settings object. @param InInstance The mutable COI instance whose resources we want to bake onto disk @param Configuration The baking configuration object with all the settings to be used for this baking operation. @param bIsUnattendedExecution Determines if we want to run this method and show prompts for user interaction or if we want to automatically chose the more sensible option (without the need of user interaction) @param OutSavedPackages A collection with the packages marked for save. @return True if the baking operation could be completed without issues and false otherwise
- L223 _prototype_ `bool BakeCustomizableObjectInstance( UCustomizableObjectInstance& InInstance, const FBakingConfiguration& Configuration, bool bIsUnattendedExecution);` — Serializes onto disk the resources used by the targeted Customizable Object Instance. The operation can be configured in the FInstanceBakingSettings settings object. @param InInstance The mutable COI instance whose resources we want to bake onto disk @param Configuration The baking configuration object with all the settings to be used for this baking operation. @param bIsUnattendedExecution Determines if we want to run this method and show prompts for user interaction or if we want to automatically chose the more sensible option (without the need of user interaction) @return True if the baking operation could be completed without issues and false otherwise

### `Plugins/Mutable/Source/CustomizableObjectEditor/Internal/MuCOE/CustomizableObjectSkeletalMeshThumbnailRenderer.h` (Internal)


#### class `UCustomizableObjectSkeletalMeshThumbnailRenderer`  
`class UCustomizableObjectSkeletalMeshThumbnailRenderer : public USkeletalMeshThumbnailRenderer`  
_L9-18_
- reflection: `UCLASS()`
- inherits: `USkeletalMeshThumbnailRenderer`
- L14 _public function_ `void EvictThumbnailScene(const UObject* Object)`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Internal/MuCOE/ICustomizableObjectEditorModulePrivate.h` (Internal)


#### class `ICustomizableObjectEditorModulePrivate`  
`class ICustomizableObjectEditorModulePrivate : public ICustomizableObjectEditorModule`  
_L12-32_
- inherits: `ICustomizableObjectEditorModule`
- desc: Interface only accessible from the Customizable Object Editor module. TODO Move to private. Currently can not be moved due to MutableValidation module.
- L15 _public function_ `static ICustomizableObjectEditorModulePrivate* Get()`
- L20 _public function_ `static ICustomizableObjectEditorModulePrivate& GetChecked()`
- L25 _public prototype_ `virtual void EnqueueCompileRequest(const TSharedRef<FCompilationRequest>& InCompilationRequest, bool bForceRequest = false) = 0;`
- L27 _public prototype_ `virtual const TMap<FName, FLinearColor>& GetExternalPinTypeColors() const = 0;`
- L29 _public prototype_ `virtual const TMap<FName, FText>& GetExternalPinFriendlyName() const = 0;`
- L31 _public prototype_ `virtual const TMap<FName, TStrongObjectPtr<const UScriptStruct>>& GetExternalPinTypes() const = 0;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/AssetDefinition_CustomizableObject.h` (Private)


#### class `UAssetDefinition_CustomizableObject`  
`class UAssetDefinition_CustomizableObject final : public UAssetDefinitionDefault`  
_L11-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override`
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L23 _public function_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L28 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L30 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L32 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/AssetDefinition_CustomizableObjectInstance.h` (Private)


#### class `UAssetDefinition_CustomizableObjectInstance`  
`class UAssetDefinition_CustomizableObjectInstance final : public UAssetDefinitionDefault`  
_L12-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override`
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public function_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override`
- L27 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L29 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L31 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L33 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CompilationMessageCache.h` (Private)


#### class `FCompilationMessageCache`  
`class FCompilationMessageCache`  
_L13-87_
- desc: Class designed to allow easy access to the logs produced during the compilation of a Customizable Object
- L16 _public prototype_ `FCompilationMessageCache();`
- L25 _public prototype_ `bool AddMessage(const FText& InMessage, const TArray<const UObject*>& InContext, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll);` — Method designed to serve as a way to add a new message to the collection of messages the compiler has produced as part of the compilation process. @param InMessage The message's text. @param InContext The UObject that is related with the InMessage provided. @param MessageSeverity Severity of the message. @return True if the message is new and had not been added before. If it returns false it means it has not been logged again.
- L33 _public prototype_ `void GetMessages(TArray<FText>& OutWarningMessages, TArray<FText>& OutErrorMessages) const;` — Provides the caller with separated arrays with all the warning and error messages. @param OutWarningMessages Array with messages that can be interpreted as Warnings. @param OutErrorMessages Array with messages that can be interpreted as errors. @note Performance warnings are considered warnings so they get returned
- L39 _public prototype_ `void ClearMessagesArray();` — Clear the array of logs
- L42 _public prototype_ `void ClearMessageCounters();` — Clear the counters that show how many errors and warnings the array contains
- L49 _public prototype_ `uint32 GetWarningCount(bool bIncludePerformanceWarnings) const;` — Provides with the amount of messages cached as warnings @param bIncludePerformanceWarnings If true the count will include performance and non performance related warnings. If false only standard warnings will be returned to the caller. @return Amount of warning messages cached.
- L54 _public prototype_ `uint32 GetErrorCount() const;` — Provides the caller with the amount of messages cached as errors @return Amount of error messages cached.
- L59 _public prototype_ `uint32 GetIgnoredCount() const;` — Provides the caller with the amount of messages ignored because they were too similar even if not identical. @return Amount of error messages ignored.
- L75 _private member_ `const uint32 MaxSpamMessages = 10;`
- L78 _private member_ `TArray<FLoggedMessage> LoggedMessages;` — Array with all the logged messages stored.
- L79 _private member_ `TArray<FLoggedMessage> IgnoredMessages;`
- L82 _private member_ `uint32 PerformanceWarningCount;` — Counters for the type of messages we have on LoggedMessages
- L83 _private member_ `uint32 WarningCount;`
- L84 _private member_ `uint32 ErrorCount;`
- L85 _private member_ `uint32 IgnoredCount;`
- L86 _private member_ `TArray<uint8> SpamBinCounts;`

#### struct `FCompilationMessageCache::FLoggedMessage`  
`struct FLoggedMessage`  
_L64-74_
- desc: List of all logged messages to ensure uniqueness
- L66 _public member_ `FText Message;`
- L67 _public member_ `TArray<const UObject*> Context;`
- L68 _public member_ `EMessageSeverity::Type Severity;`
- L70 _public function_ `bool operator==( const FLoggedMessage& o) const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableInstanceDetails.h` (Private)


#### class `FCustomizableInstanceDetails`  
`class FCustomizableInstanceDetails : public IDetailCustomization`  
_L32-215_
- inherits: `IDetailCustomization`
- L36 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L40 _public function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override` — Do not use. Add details customization in the other CustomizeDetails signature.
- L43 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;` — Customize details here.
- L47 _public prototype_ `void Refresh() const;` — Refresh the custom details.
- L53 _private prototype_ `void UpdateInstance();` — Updat the Instance if a parameter has been modified. Also creates a Delegate to refresh the UI if the Instance has been updated successfully.
- L56 _private prototype_ `void InstanceUpdated(UCustomizableObjectInstance* Instance) const;` — Callback to regenerate the details when the instance has finished an update
- L58 _private prototype_ `void ObjectCompiled();`
- L62 _private prototype_ `TSharedRef<SWidget> GenerateStateSelector();` — State Selector Generates The StateSelector Widget
- L63 _private prototype_ `void OnStateComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L66 _private prototype_ `void OnShowOnlyRuntimeSelectionChanged(ECheckBoxState InCheckboxState);` — Function to change the parameters view
- L67 _private prototype_ `void OnShowOnlyRelevantSelectionChanged(ECheckBoxState InCheckboxState);`
- L68 _private prototype_ `void OnUseUISectionsSelectionChanged(ECheckBoxState InCheckboxState);`
- L69 _private prototype_ `void OnUseUIThumbnailsSelectionChanged(ECheckBoxState InCheckboxState);`
- L73 _private prototype_ `bool GenerateParametersView(IDetailCategoryBuilder& MainCategory);` — Main parameter generation functions Returns true if parameters have been hidden due to runtime type
- L83 _private prototype_ `void SortParametersAndUISections(const UCustomizableObject& CustomizableObject, TArray<FParameterInfo>& ParametersToSort) const;` — Sort the contents of a Parameters Info array taking in consideration that the array should get sorted first by UI Section and then by parameter UI order or Param name. @note The result will be an array where the sections are in sequential order following an alphabetical ordering (A-Z) where each section contains its parameters in an incremental numerical order (ParamUIOrder int) or incremental lexical order (ParamName) @param CustomizableObject The customizable object the parameters are linked to. @param ParametersToSort The array of parameters we want to get sorted out.
- L85 _private prototype_ `void RecursivelyAddParamAndChildren(const UCustomizableObject& CustomizableObject, const int32 ParamIndexInObject, const FString ParentName, IDetailCategoryBuilder& DetailsCategory);`
- L86 _private prototype_ `void FillChildrenMap(int32 ParamIndexInObject);`
- L89 _private prototype_ `bool IsVisible(int32 ParamIndexInObject);` — Function to determine if a parameter widget should be generated
- L90 _private prototype_ `bool IsMultidimensionalProjector(int32 ParamIndexInObject);`
- L93 _private prototype_ `bool IsIntParameterFilteredOut(const UCustomizableObject& CustomizableObject, const FString& ParamName, const FString& ParamOption) const;` — @return true if the parameter doesn't match the current filter.
- L96 _private prototype_ `IDetailGroup* GenerateParameterSection(IDetailCategoryBuilder& DetailsCategory, const UCustomizableObject& CustomizableObject, const FString& ParamName);` — Main widget generation functions
- L97 _private prototype_ `void GenerateWidgetRow(FDetailWidgetRow& WidgetRow, const UCustomizableObject& CustomizableObject, const FString& ParamName, const int32 ParamIndexInObject);`
- L98 _private prototype_ `TSharedRef<SWidget> GenerateParameterWidget(const UCustomizableObject& CustomizableObject, const FString& ParamName, const int32 ParamIndexInObject);`
- L101 _private prototype_ `TSharedRef<SWidget> GenerateIntWidget(const UCustomizableObject& CustomizableObject, const FString& ParamName, const int32 ParamIndexInObject);` — Int FParameters Functions
- L102 _private prototype_ `void OnIntParameterComboBoxChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo, const FString ParamName);`
- L103 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetIntParameter(TSharedPtr<FString> OptionName, const FString ParameterName);`
- L106 _private prototype_ `TSharedRef<SWidget> GenerateFloatWidget(const UCustomizableObject& CustomizableObject, const FString& ParamName);` — Float FParameters Functions
- L107 _private prototype_ `float GetFloatParameterValue(const FString ParamName, int32 RangeIndex) const;`
- L108 _private prototype_ `void OnFloatParameterChanged(float Value, const FString ParamName, int32 RangeIndex);`
- L109 _private prototype_ `void OnFloatParameterSliderBegin(const FString ParamName, int32 RangeIndex);`
- L110 _private prototype_ `void OnFloatParameterSliderEnd(const FString ParamName, int32 RangeIndex);`
- L111 _private prototype_ `void OnFloatParameterCommited(float Value, ETextCommit::Type Type, const FString ParamName, int32 RangeIndex);` — Needed to have undo/redo
- L114 _private prototype_ `void OnTextureParameterSelected(const FAssetData& AssetData, const FString ParamName);` — Texture FParameters Functions
- L117 _private prototype_ `void OnSkeletalMeshParameterSelected(const FAssetData& AssetData, const FString ParamName);` — Skeletal Mesh FParameters Functions
- L120 _private prototype_ `void OnMaterialParameterSelected(const FAssetData& AssetData, const FString ParamName);` — Material FParameters Functions
- L123 _private prototype_ `TSharedRef<SWidget> GenerateColorWidget(const FString& ParamName);` — Color FParameters Functions
- L124 _private prototype_ `FLinearColor GetColorParameterValue(const FString ParamName) const;`
- L125 _private prototype_ `FReply OnColorBlockMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, const FString ParamName);`
- L126 _private prototype_ `void OnSetColorFromColorPicker(FLinearColor NewColor, const FString PickerParamName);`
- L129 _private prototype_ `TSharedRef<SWidget> GenerateTransformWidget(const FString& ParamName);` — Transform FParameters Functions
- L130 _private prototype_ `FTransform GetTransformParameterValue(const FString ParamName) const;`
- L131 _private prototype_ `void OnTransformParameterChanged(FTransform NewTransform, const FString ParamName);`
- L132 _private prototype_ `void OnTransformParameterCommitted(FTransform NewTransform, ETextCommit::Type Type, const FString ParamName);`
- L135 _private prototype_ `TSharedRef<SWidget> GenerateBoolWidget(const FString& ParamName);` — Bool FParameters Functions
- L136 _private prototype_ `ECheckBoxState GetBoolParameterValue(const FString ParamName) const;`
- L137 _private prototype_ `void OnBoolParameterChanged(ECheckBoxState InCheckboxState, const FString ParamName);`
- L140 _private prototype_ `TSharedRef<SWidget> GenerateSimpleProjector(const FString& ParamName);` — Projector FParameters Functions
- L141 _private prototype_ `TSharedRef<SWidget> GenerateMultidimensionalProjector(const UCustomizableObject& CustomizableObject, const FString& ParamName, const int32 ParamIndexInObject);`
- L142 _private prototype_ `TSharedPtr<ICustomizableObjectInstanceEditor> GetEditorChecked() const;`
- L143 _private prototype_ `FReply OnProjectorSelectChanged(const FString ParamName, const int32 RangeIndex) const;`
- L144 _private prototype_ `FReply OnProjectorCopyTransform(const FString ParamName, const int32 RangeIndex) const;`
- L145 _private prototype_ `FReply OnProjectorPasteTransform(const FString ParamName, const int32 RangeIndex);`
- L146 _private prototype_ `FReply OnProjectorResetTransform(const FString ParamName, const int32 RangeIndex);`
- L147 _private prototype_ `FReply OnProjectorLayerAdded(const FString ParamName);`
- L148 _private prototype_ `FReply OnProjectorLayerRemoved(const FString ParamName, const int32 RangeIndex);`
- L149 _private prototype_ `void OnProjectorTextureParameterComboBoxChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo, const FString ParamName, int32 RangeIndex);`
- L150 _private prototype_ `TSharedRef<SWidget> MakeTextureComboEntryWidget(TSharedPtr<FString> InItem) const;`
- L151 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetProjectorParameter(TSharedPtr<FString> InItem) const;`
- L154 _private prototype_ `void OnExternalTypeParameterChanged(const FPropertyChangedEvent& PropertyChangedEvent, TSharedPtr<FStructOnScope> StructOnScope, FString ParamName, const int32 RangeIndex);` — External Type FParmeter Functions
- L157 _private prototype_ `FReply OnCopyAllParameters();` — Parameter Functions
- L158 _private prototype_ `FReply OnPasteAllParameters();`
- L159 _private prototype_ `FReply OnResetAllParameters();`
- L160 _private prototype_ `void OnResetParameterButtonClicked(int32 ParameterIndex);`
- L163 _private prototype_ `void OnInstanceTransacted(const FTransactionObjectEvent& TransactionEvent);` — Transaction System
- L168 _private member_ `TWeakObjectPtr<UCustomizableObjectInstance> CustomInstance;` — Pointer to the Customizable Object Instance
- L171 _private member_ `TWeakPtr<IDetailLayoutBuilder> LayoutBuilder;` — Details builder pointer
- L174 _private member_ `TMap<FString, IDetailGroup*> GeneratedSections;` — Map to keep track of the generated parameter sections
- L177 _private member_ `TMap<FString, IDetailGroup*> ParentsGroups;` — Used to insert child params to a parent's expandable area
- L180 _private member_ `TArray< TSharedPtr<FString> > StateNames;` — Array with all the possible states for the states combo box
- L183 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> WeakEditor;` — Weak pointer of the open editor
- L186 _private member_ `TMultiMap<FString, int32> ParamChildren;` — Maps param name to children param indices, used to walk the params in order respecting parent/children relationships
- L189 _private member_ `TMap<int32, bool> ParamHasParent;` — Maps param index to bool telling if it has parent, same use as previous line
- L192 _private member_ `TArray<TSharedPtr<TArray<TSharedPtr<FString>>>> ProjectorTextureOptions;` — Array with all the possible multilayer projector texture options
- L195 _private member_ `TMap<int32, TSharedPtr<TArray<TSharedPtr<FString>>>> IntParameterOptions;` — Map from ParamIndexInObject to the param's int selector options
- L198 _private member_ `TMap<int32, TSharedPtr<TArray<TSharedPtr<FString>>>> ProjectorParameterPoseOptions;` — Map from ParamIndexInObject to the projector param pose options
- L201 _private member_ `bool bUpdatingSlider = false;` — True when a slider is being edited
- L204 _private member_ `float SliderStartValue = 0.0f;` — Float parameter value at the moment a slider drag started. Used to record the pre-drag state for undo.
- L207 _private member_ `TArray< TSharedPtr<class FDeferredCleanupSlateBrush> > DynamicBrushes;` — Array to store dynamic brushes. Needed because an image widget only stores a pointer to a Brush.
- L210 _private member_ `FGameplayTagContainer Filter;` — /  Editor gameplay tags filter and filter type. Used to filter int parameter options.
- L211 _private member_ `EGameplayContainerMatchType FilterType = EGameplayContainerMatchType::Any;`
- L214 _private member_ `const FString DefaultSectionName = FString(TEXT("Misc` — Section name used for parameters that do have an empty string for its section name.

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace ESelectInfo`
- L25 _namespace_ `namespace ETextCommit`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectCompileRunnable.h` (Private)


#### class `FCustomizableObjectCompileRunnable`  
`class FCustomizableObjectCompileRunnable : public FRunnable`  
_L24-85_
- inherits: `FRunnable`
- L50 _private member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::Node> MutableRoot;`
- L51 _private member_ `TArray<FError> ArrayErrors;`
- L53 _private prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FImage> LoadImageResourceReferenced(int32 ID);`
- L57 _public prototype_ `FCustomizableObjectCompileRunnable(UE::Mutable::Private::Ptr<UE::Mutable::Private::Node> Root, const TSharedRef<FCustomizableObjectCompiler>& InCompiler);`
- L60 _public prototype_ `uint32 Run() override;` — FRunnable interface
- L65 _public prototype_ `bool IsCompleted() const;`
- L68 _public prototype_ `const TArray<FError>& GetArrayErrors() const;`
- L70 _public member_ `TSharedPtr<UE::Mutable::Private::FModel, ESPMode::ThreadSafe> Model;`
- L72 _public member_ `TMap<UE::Mutable::Private::FOperation::ADDRESS, FInstancedStruct> ExternalOperations;`
- L74 _public member_ `FCompilationOptions Options;`
- L76 _public member_ `TWeakPtr<FCustomizableObjectCompiler> WeakCompiler;`
- L78 _public member_ `TArray<FMutableSourceTextureData> ReferencedTextures;`
- L79 _public member_ `TArray<FMutableSourceMeshData> ReferencedMeshes;`
- L81 _public member_ `FString ErrorMsg;`
- L84 _public member_ `std::atomic<bool> bThreadCompleted;` — Whether the thread has finished running

#### struct `FCustomizableObjectCompileRunnable::FErrorAttachedData`  
`struct FErrorAttachedData`  
_L28-31_
- L30 _public member_ `TArray<float> UnassignedUVs;`

#### struct `FCustomizableObjectCompileRunnable::FError`  
`struct FError`  
_L33-46_
- L35 _public member_ `EMessageSeverity::Type Severity = EMessageSeverity::Error;`
- L36 _public member_ `ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll;`
- L37 _public member_ `FText Message;`
- L38 _public member_ `TSharedPtr<FErrorAttachedData> AttachedData;`
- L40 _public member_ `TArray<const void*, TInlineAllocator<4>> Contexts;`
- L42 _public function_ `FError(const EMessageSeverity::Type InSeverity, const FText& InMessage, const TArray<const void*, TInlineAllocator<4>>& InContexts, const ELoggerSpamBin InSpamBin = ELoggerSpamBin::ShowAll ) : Severity(InSeverity), SpamBin(InSpamBin), Message(InMessage), Contexts(InContexts)`
- L44 _public function_ `FError(const EMessageSeverity::Type InSeverity, const FText& InMessage, const void* InContext, const TSharedPtr<FErrorAttachedData>& InAttachedData, const ELoggerSpamBin InSpamBin = ELoggerSpamBin::ShowAll) : Severity(InSeverity), SpamBin(InSpamBin), Message(InMessage), AttachedData(InAttachedData), Contexts`

#### class `FCustomizableObjectSaveDDRunnable`  
`class FCustomizableObjectSaveDDRunnable : public FRunnable`  
_L88-137_
- inherits: `FRunnable`
- L92 _public prototype_ `FCustomizableObjectSaveDDRunnable(const TSharedPtr<FCompilationRequest>& InRequest, TSharedPtr<UE::Mutable::Private::FMutableCachedPlatformData>& InPlatformData);`
- L95 _public prototype_ `uint32 Run() override;` — FRunnable interface
- L98 _public prototype_ `bool IsCompleted() const;`
- L101 _public prototype_ `const ITargetPlatform* GetTargetPlatform() const;`
- L105 _private prototype_ `void CachePlatformData();`
- L107 _private prototype_ `void StoreCachedPlatformDataInDDC(bool& bStoredSuccessfully);`
- L109 _private prototype_ `void StoreCachedPlatformDataToDisk();`
- L111 _private member_ `FCompilationOptions Options;`
- L113 _private member_ `FString CustomizableObjectName;`
- L114 _private member_ `FGuid CustomizableObjectId;`
- L116 _private member_ `MutableCompiledDataStreamHeader CustomizableObjectHeader;`
- L119 _private member_ `FString FullFileName;` — Used to save files to disk
- L121 _private member_ `UE::DerivedData::FCacheKey DDCKey;`
- L122 _private member_ `UE::DerivedData::ECachePolicy DefaultDDCPolicy;`
- L125 _private member_ `std::atomic<bool> bThreadCompleted = false;` — Whether the thread has finished running
- L129 _public member_ `TArray64<uint8> ModelData;`
- L130 _public member_ `TArray64<uint8> ModelResourcesData;`
- L133 _public member_ `TSharedPtr<UE::Mutable::Private::FMutableCachedPlatformData> PlatformData;` — Cached platform data
- L136 _public member_ `TArray<UE::Mutable::Private::FFile> BulkDataFilesDDC;` — DDC Helpers

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectCompiler.h` (Private)


#### class `FCustomizableObjectCompiler`  
`class FCustomizableObjectCompiler : public TSharedFromThis<FCustomizableObjectCompiler>, public FGCObject`  
_L39-181_
- inherits: `TSharedFromThis<FCustomizableObjectCompiler>,FGCObject`
- L43 _public prototype_ `void Tick(bool bBlocking);` — Check for pending compilation process. Returns true if an object has been updated.
- L45 _public prototype_ `int32 GetRemainingWork() const;`
- L47 _public prototype_ `int32 GetNumCompileRequests() const;`
- L50 _public prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::Node> Export(UCustomizableObject* Object, const FCompilationOptions& Options, TArray<TSoftObjectPtr<const UTexture>>& OutRuntimeReferencedTextures, TArray<FMutableSourceTextureData>& OutCompilerReferencedTextures, TArray<TSoftObjectPtr<const UStreamableRenderAsset>>& OutRuntimeReferencedMeshes, TArray<FMutableSourceMeshData>& OutCompilerReferencedMeshes);` — Generate the Mutable Graph from the Unreal Graph.
- L56 _public prototype_ `void CompilerLog(const FText& Message, const TArray<const UObject*>& UObject, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const bool bAddBaseObjectInfo = true, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll);`
- L57 _public prototype_ `void CompilerLog(const FText& Message, const UObject* Context = nullptr, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const bool bAddBaseObjectInfo = true, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll);`
- L58 _public prototype_ `void NotifyCompilationErrors() const;`
- L60 _public prototype_ `void FinishLoadingModelDataFromDDC();`
- L61 _public prototype_ `void FinishLoadingStreamableDataFromDDC();`
- L63 _public prototype_ `void FinishCompilationTask();`
- L64 _public prototype_ `void FinishSavingDerivedDataTask();`
- L66 _public prototype_ `void ForceFinishCompilation();`
- L67 _public prototype_ `void ClearCompileRequests();`
- L69 _public prototype_ `void AddCompileNotification(const FText& CompilationStep) const;`
- L70 _public prototype_ `static void RemoveCompileNotification();`
- L74 _public prototype_ `void EnqueueCompileRequest(const TSharedRef<FCompilationRequest>& CompileRequest, bool bForceRequests);` — Enqueue a new compile request. @param bForceRequests enqueue even if the request is already in the queue. See FCompilationRequest::operator==(...).
- L77 _public prototype_ `bool IsRequestQueued(const TSharedRef<FCompilationRequest>& InCompileRequest) const;` — Queued or in progress.
- L80 _public prototype_ `bool IsRequestQueued(const UCustomizableObject& Object) const;` — Queued or in progress.
- L83 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L84 _public function_ `virtual FString GetReferencerName() const override`
- L89 _public prototype_ `void AddGameThreadCompileTask(TFunction<void()>&& Task);`
- L92 _public member_ `TSharedPtr<FMutableCompilationContext> CompilationContext;`
- L97 _private member_ `FCompilationMessageCache CompilationLogsContainer;` — Object containing all error and warning logs raised during compilation.
- L99 _private prototype_ `void SetCompilationState(ECompilationStatePrivate State, ECompilationResultPrivate Result) const;`
- L104 _private prototype_ `void Compile(const TSharedRef<FCompilationRequest>& InCompileRequest);` — Load required assets and compile. Loads assets which reference Object's package asynchronously before calling ProcessChildObjectsRecursively.
- L106 _private prototype_ `void CompileInternal(bool bAsync = false);`
- L108 _private prototype_ `void CompleteRequest(ECompilationStatePrivate State, ECompilationResultPrivate Result);`
- L109 _private prototype_ `bool TryPopCompileRequest();`
- L112 _private prototype_ `bool TryLoadCompiledDataFromDDC(UCustomizableObject& CustomizableObject);` — Attempts to load the compiled data from DDC.
- L114 _private prototype_ `void PreloadReferencerAssets();`
- L115 _private prototype_ `void PreloadingReferencerAssetsCallback(bool bAsync);`
- L119 _private prototype_ `void UpdateCompilerLogData();` — Will output to Mutable Log the warning and error messages generated during the CO compilation and update the values of NumWarnings and NumErrors
- L125 _private prototype_ `void SaveCODerivedData();` — Launches the save derived data task in another thread after compiling a CO in the editor @param bShowNotification [in] whether to show the saving DD notification or not @return nothing
- L127 _private prototype_ `ECompilationResultPrivate GetCompilationResult() const;`
- L129 _private prototype_ `void ProcessCompileTasks();`
- L138 _private member_ `TSharedPtr<FDDCHeapMemory> DDCHeapMemory;`
- L141 _private member_ `TSharedPtr<UE::Tasks::FTaskEvent> LoadModelDataFromDDCEvent;` — Load compiled data from DDC completion events
- L142 _private member_ `TSharedPtr<UE::Tasks::FTaskEvent> LoadStreamableDataFromDDCEvent;`
- L145 _private member_ `TSharedPtr<FStreamableHandle> AsynchronousStreamableHandlePtr;` — Pointer to the Asynchronous Preloading process call back
- L148 _private member_ `TSharedPtr<FCustomizableObjectCompileRunnable> CompileTask;` — Compile task and thread.
- L149 _private member_ `TSharedPtr<FRunnableThread> CompileThread;`
- L152 _private member_ `TSharedPtr<FCustomizableObjectSaveDDRunnable> SaveDDTask;` — SaveDD task and thread.
- L153 _private member_ `TSharedPtr<FRunnableThread> SaveDDThread;`
- L156 _private member_ `TArray<TObjectPtr<UObject>> ArrayGCProtect;` — Array used to protect from garbage collection those COs loaded asynchronously
- L159 _private member_ `TSharedPtr<UE::Mutable::Private::FMutableCachedPlatformData> PlatformData;` — Cached Platform Data.
- L162 _private member_ `TObjectPtr<UCustomizableObject> CurrentObject = nullptr;` — Protected from GC with FCustomizableObjectCompiler::AddReferencedObjects
- L164 _private member_ `FCompilationOptions CurrentOptions;`
- L167 _private member_ `TSharedPtr<FCompilationRequest> CurrentRequest;` — Current Compilation request.
- L170 _private member_ `TArray<TSharedRef<FCompilationRequest>> CompileRequests;` — Pending requests.
- L172 _private member_ `uint32 NumCompilationRequests = 0;`
- L175 _private member_ `FProgressNotificationHandle CompileNotificationHandle;` — Compilation progress bar handle
- L178 _private member_ `double CompilationStartTime = 0;` — Compilation start time in seconds.
- L180 _private member_ `TQueue< TFunction<void()>, EQueueMode::Mpsc > PendingGameThreadCompileTasks;`

#### struct `FCustomizableObjectCompiler::FDDCHeapMemory`  
`struct FDDCHeapMemory`  
_L131-137_
- L133 _public member_ `FSharedBuffer ModelBytesDDC;`
- L134 _public member_ `FSharedBuffer ModelResourcesBytesDDC;`
- L135 _public member_ `FSharedBuffer ModelStreamablesBytesDDC;`
- L136 _public member_ `FSharedBuffer BulkDataFilesBytesDDC;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Mutable` (scope `UE`)
- L29 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L36 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeObject> GenerateMutableRoot(const UCustomizableObject* Object, FMutableGraphGenerationContext& GenerationContext);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectConnectionDrawingPolicy.h` (Private)


#### class `FCustomizableObjectConnectionDrawingPolicy`  
`class FCustomizableObjectConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L8-16_
- inherits: `FConnectionDrawingPolicy`
- L11 _public function_ `FCustomizableObjectConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements) : FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements)`
- L15 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectCookPackageSplitter.h` (Private)


#### class `FCustomizableObjectCookPackageSplitter`  
`class FCustomizableObjectCookPackageSplitter : public ICookPackageSplitter`  
_L9-26_
- inherits: `ICookPackageSplitter`
- desc: Handles splitting the streamable Data constants into their own packages
- L13 _public prototype_ `static bool ShouldSplit(UObject* SplitData);` — REGISTER_COOKPACKAGE_SPLITTER interface
- L14 _public prototype_ `static FString GetSplitterDebugName();`
- L15 _public prototype_ `static bool RequiresCachedCookedPlatformDataBeforeSplit();`
- L18 _public prototype_ `virtual void Initialize(UPackage* OwnerPackage, UObject* OwnerObject) override;` — ICookPackageSplitter interface
- L19 _public prototype_ `virtual FGenerationManifest ReportGenerationManifest(const UPackage* OwnerPackage, const UObject* OwnerObject) override;`
- L20 _public prototype_ `virtual bool PopulateGeneratorPackage(FPopulateContext& PopulateContext) override;`
- L21 _public prototype_ `virtual EGeneratedRequiresGenerator DoesGeneratedRequireGenerator() override;`
- L22 _public prototype_ `virtual bool UseInternalReferenceToAvoidGarbageCollect() override;`
- L23 _public prototype_ `virtual bool RequiresEmptyPackageBeforePopulate(const UPackage* Package) override;`
- L25 _public member_ `TStrongObjectPtr<const UCustomizableObject> StrongObject;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectCustomSettings.h` (Private)


#### class `SCustomizableObjectCustomSettings`  
`class SCustomizableObjectCustomSettings : public SVerticalBox`  
_L28-89_
- inherits: `SVerticalBox`
- desc: Custom slate that grants the user the ability of adding, moving and removing lights from the preview scene.
- L31 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectCustomSettings)`
- L32 _public prototype_ `SLATE_ARGUMENT(UCustomSettings*, PreviewSettings) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `void SetViewportLightsByAsset(const FAssetData& InAsset);`
- L40 _private prototype_ `TSharedRef<SWidget> GetLightComboButtonContent();`
- L41 _private prototype_ `void CloseLightComboButtonContent();`
- L42 _private prototype_ `FReply OnSaveViewportLightsAsset() const;`
- L43 _private prototype_ `FReply OnNewViewportLightsAsset() const;`
- L45 _private prototype_ `FReply OnPointLightAdded() const;`
- L46 _private prototype_ `FReply OnSpotLightAdded() const;`
- L47 _private prototype_ `FReply OnLightRemoved() const;`
- L48 _private prototype_ `FReply OnLightUnselected();`
- L49 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _private prototype_ `void OnListSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L53 _private prototype_ `TOptional<float> GetIntensityValue() const;` — LightProperties
- L54 _private prototype_ `void OnIntensityValueCommited(float Value, ETextCommit::Type CommitType);`
- L56 _private prototype_ `FLinearColor GetLightColorValue() const;`
- L57 _private prototype_ `FReply OnLightColorBlockMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L58 _private prototype_ `void OnSetLightColorFromColorPicker(FLinearColor InColor);`
- L60 _private prototype_ `TOptional<float> GetAttenuationRadius() const;`
- L61 _private prototype_ `void OnAttenuationRadiusValueCommited(float Value, ETextCommit::Type CommitType);`
- L63 _private prototype_ `TOptional<float> GetLightSourceRadius() const;`
- L64 _private prototype_ `void OnLightSourceRadiusValueCommited(float Value, ETextCommit::Type CommitType);`
- L66 _private prototype_ `TOptional<float> GetLightSourceLength() const;`
- L67 _private prototype_ `void OnLightSourceLengthValueCommited(float Value, ETextCommit::Type CommitType);`
- L69 _private prototype_ `TOptional<float> GetLightInnerConeAngle() const;`
- L70 _private prototype_ `void OnLightInnerConeAngleValueCommited(float Value, ETextCommit::Type CommitType);`
- L72 _private prototype_ `TOptional<float> GetLightOuterConeAngle() const;`
- L73 _private prototype_ `void OnLightOuterConeAngleValueCommited(float Value, ETextCommit::Type CommitType);`
- L75 _private prototype_ `TSharedPtr<ICustomizableObjectInstanceEditor> GetEditorChecked() const;`
- L77 _private member_ `TArray<TSharedPtr<FString>> LightNames;`
- L79 _private member_ `static const FString LightPackagePath;`
- L80 _private member_ `TSharedPtr<SEditableTextBox> LightsAssetNameInputText;`
- L82 _private member_ `TSharedPtr<SComboButton> LightComboButton;`
- L83 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> LightsListView;`
- L84 _private member_ `TSharedPtr<SExpandableArea> PointLightProperties;`
- L85 _private member_ `TSharedPtr<SExpandableArea> SpotLightProperties;`
- L87 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> WeakEditor;`
- L88 _private member_ `TWeakPtr<SCustomizableObjectEditorViewportTabBody> WeakViewport;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ESelectInfo`
- L13 _namespace_ `namespace ETextCommit`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectCustomSettingsDetails.h` (Private)


#### class `FCustomizableObjectCustomSettingsDetails`  
`class FCustomizableObjectCustomSettingsDetails : public IDetailCustomization`  
_L9-14_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L13 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectDetails.h` (Private)


#### class `FCustomizableObjectDetails`  
`class FCustomizableObjectDetails : public IDetailCustomization`  
_L12-23_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L22 _private member_ `class UCustomizableObject* CustomizableObject = nullptr;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditor.h` (Private)


#### class `FEditorLogger`  
`class FEditorLogger : public IMutableEditorLogger`  
_L54-67_
- inherits: `IMutableEditorLogger`
- L59 _public prototype_ `bool LogMessage(TSharedRef<FTokenizedMessage> Message) override;` — Logs message into the Message Log Listing
- L62 _public prototype_ `void ClearLogMessageList() override;` — Claer all the messages of the Message Log Listing
- L66 _public member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`

#### enum `EGizmoType`  
`enum class EGizmoType : uint8`  
_L70-79_
- L72 _public enumerator_ `Hidden`
- L73 _public enumerator_ `ProjectorParameter`
- L74 _public enumerator_ `NodeProjectorConstant`
- L75 _public enumerator_ `NodeProjectorParameter`
- L76 _public enumerator_ `ClipMorph`
- L77 _public enumerator_ `ClipMesh`
- L78 _public enumerator_ `Light`

#### class `UUpdateClassWrapper`  
`class UUpdateClassWrapper : public UObject`  
_L86-96_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Wrapper UObject class for the UCustomizableObjectInstance::FObjectInstanceUpdatedDelegate dynamic multicast delegate
- L93 _public prototype_ `void DelegatedCallback(UCustomizableObjectInstance* Instance);` — `UFUNCTION()` — Method to assign for the callback
- L95 _public member_ `FCreatePreviewInstanceFlagDelegate Delegate;`

#### class `FCustomizableObjectEditor`  
`class FCustomizableObjectEditor : public FCustomizableObjectGraphEditorToolkit, public ICustomizableObjectInstanceEditor, public FGCObject`  
_L102-355_
- inherits: `FCustomizableObjectGraphEditorToolkit,ICustomizableObjectInstanceEditor,FGCObject`
- desc: CustomizableObject Editor class
- L108 _public prototype_ `explicit FCustomizableObjectEditor(UCustomizableObject& ObjectToEdit);`
- L112 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L113 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L121 _public prototype_ `void InitCustomizableObjectEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost);` — Initialize a new Customizable Object editor. Called immediately after construction. Required due to being unable to use SharedThis in the constructor. See static Create(...) function.
- L124 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L125 _public function_ `virtual FString GetReferencerName() const override`
- L131 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L132 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L133 _public prototype_ `virtual FText GetToolkitName() const override;`
- L134 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L135 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L138 _public prototype_ `virtual void RefreshTool() override;` — ICustomizableObjectInstanceEditor interface
- L139 _public prototype_ `virtual TSharedPtr<SCustomizableObjectEditorViewportTabBody> GetViewport() override;`
- L140 _public prototype_ `virtual UCustomizableObjectInstance* GetPreviewInstance() override;`
- L141 _public prototype_ `virtual UProjectorParameter* GetProjectorParameter() override;`
- L142 _public prototype_ `virtual UCustomSettings* GetCustomSettings() override;`
- L143 _public prototype_ `virtual void HideGizmo() override;`
- L144 _public prototype_ `virtual void ShowGizmoProjectorNodeProjectorConstant(UCustomizableObjectNodeProjectorConstant& Node) override;`
- L145 _public prototype_ `virtual void HideGizmoProjectorNodeProjectorConstant() override;`
- L146 _public prototype_ `virtual void ShowGizmoProjectorNodeProjectorParameter(UCustomizableObjectNodeProjectorParameter& Node) override;`
- L147 _public prototype_ `virtual void HideGizmoProjectorNodeProjectorParameter() override;`
- L148 _public prototype_ `virtual void ShowGizmoProjectorParameter(const FString& ParamName, int32 RangeIndex = -1) override;`
- L149 _public prototype_ `virtual void HideGizmoProjectorParameter() override;`
- L150 _public prototype_ `virtual void ShowGizmoClipMorph(UCustomizableObjectNodeModifierClipMorph& Node) override;`
- L151 _public prototype_ `virtual void HideGizmoClipMorph(bool bClearGraphSelectionSet = true) override;`
- L152 _public prototype_ `virtual void ShowGizmoClipMesh(UCustomizableObjectNode& Node, FTransform* Transform, const UEdGraphPin& MeshPin) override;`
- L153 _public prototype_ `virtual void HideGizmoClipMesh() override;`
- L154 _public prototype_ `virtual void ShowGizmoLight(ULightComponent& SelectedLight) override;`
- L155 _public prototype_ `virtual void HideGizmoLight() override;`
- L156 _public prototype_ `virtual UCustomizableObjectEditorProperties* GetEditorProperties() override;`
- L157 _public prototype_ `virtual TSharedPtr< SCustomizableObjectEditorAdvancedPreviewSettings> GetAdvancedPreviewSettings() override;`
- L158 _public prototype_ `virtual bool ShowLightingSettings() override;`
- L159 _public prototype_ `virtual bool ShowProfileManagementOptions() override;`
- L160 _public prototype_ `virtual const UObject* GetObjectBeingEdited() override;`
- L161 _public prototype_ `virtual FEditorModeTools* GetEditorModeTools() override;`
- L164 _public prototype_ `UCustomizableObject* GetCustomizableObject();` — Returns the CO being edited in this editor
- L168 _public prototype_ `static bool GroupNodeIsLinkedToParentByName(UCustomizableObjectNodeObject* Node, UCustomizableObject* Test, const FString& ParentGroupName);` — Utility method: Test whether the CO Node Object given as parameter is linked to any of the CO Node Object Group nodes in the Test CO given as parameter
- L171 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L174 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;` — FNotifyHook interface
- L177 _public prototype_ `void DeleteSelectedNodes();` — Delegates
- L178 _public prototype_ `bool CanDeleteNodes() const;`
- L179 _public prototype_ `void DuplicateSelectedNodes();`
- L180 _public prototype_ `bool CanDuplicateSelectedNodes() const;`
- L183 _public prototype_ `virtual void OnSelectedGraphNodesChanged(const FGraphPanelSelectionSet& NewSelection) override;` — FCustomizableObjectGraphEditorToolkit interface
- L184 _public prototype_ `virtual void ReconstructAllChildNodes(UCustomizableObjectNode& StartNode, const UClass& NodeType) override;`
- L187 _public prototype_ `void OnUpdatePreviewInstance(UCustomizableObjectInstance* Instance);` — Callback to notify the editor when the PreviewInstance has been updated
- L189 _public prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::Node> DebuggerCompile(TSharedPtr<UE::Mutable::Private::FModel>& Model, TArray<TSoftObjectPtr<const UTexture>>& RuntimeTextures, TArray<FMutableSourceTextureData>& CompilerTextures, TArray<TSoftObjectPtr<const UStreamableRenderAsset>>& RuntimeMeshes, TArray<FMutableSourceMeshData>& CompilerMeshes) const;`
- L195 _public prototype_ `void GraphViewer() const;`
- L196 _public prototype_ `void CodeViewer() const;`
- L199 _public prototype_ `void UpdateCookDataDistributionId();` — Regenerate CookDataDistributionId to generate a new entry of cooked data distribution in the DDC next time the object is cooked.
- L202 _public prototype_ `void ClearGatheredReferences();` — Clear game asset references saved in the Customizable Object.
- L204 _public prototype_ `void InitLogList();`
- L207 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L208 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L209 _private prototype_ `TSharedRef<SDockTab> SpawnTab_InstanceProperties(const FSpawnTabArgs& Args);`
- L210 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Graph(const FSpawnTabArgs& Args);`
- L211 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AdvancedPreviewSettings(const FSpawnTabArgs& Args);`
- L212 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TextureAnalyzer(const FSpawnTabArgs& Args);`
- L213 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PerformanceAnalyzer(const FSpawnTabArgs& Args);`
- L214 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TagExplorer(const FSpawnTabArgs& Args);`
- L215 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Stats(const FSpawnTabArgs& Args);`
- L218 _private prototype_ `void BindCommands();` — Binds commands associated with the Static Mesh Editor.
- L221 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for the graph editor
- L227 _private prototype_ `void CompileObject(bool bOnlySelectedParameters, bool bGatherReferences);` — Compile the Customizable Object. @param bOnlySelectedParameters If true, compile only selected int parameters. @param bGatherReferences If true, also gather asset references and save them in the Customizable Object. Marks the objects as modified.
- L230 _private prototype_ `TSharedRef<SWidget> GenerateCompileOptionsMenuContent(TSharedRef<FUICommandList> InCommandList);` — Compile options menu callbacks
- L231 _private prototype_ `void ResetCompileOptions();`
- L232 _private member_ `TSharedPtr<STextComboBox> CompileOptimizationCombo;`
- L233 _private member_ `TArray< TSharedPtr<FString> > CompileOptimizationStrings;`
- L234 _private member_ `TSharedPtr<STextComboBox> CompileTextureCompressionCombo;`
- L235 _private member_ `TArray< TSharedPtr<FString> > CompileTextureCompressionStrings;`
- L236 _private member_ `TSharedPtr<SNumericDropDown<float>> EmbeddedDataLimitCombo;`
- L238 _private prototype_ `void OnChangeCompileOptimizationLevel(TSharedPtr<FString> NewSelection, ESelectInfo::Type);`
- L239 _private prototype_ `void OnChangeCompileTextureCompressionType(TSharedPtr<FString> NewSelection, ESelectInfo::Type);`
- L242 _private prototype_ `void SaveAsset_Execute() override;` — Save Customizable Object open in editor
- L245 _private prototype_ `void OnObjectPropertySelectionChanged(FProperty* InProperty);` — Callback when selection changes in the Property Tree.
- L248 _private prototype_ `void OnInstancePropertySelectionChanged(FProperty* InProperty);` — Callback when selection changes in the Property Tree.
- L251 _private prototype_ `void OnObjectModified(UObject* Object);` — Callback for the object modified event
- L254 _private prototype_ `void OpenTextureAnalyzerTab();` — Open the Texture Analyzer tab
- L257 _private prototype_ `void OpenPerformanceAnalyzerTab();` — Open the Performance Analyzer tab
- L259 _private prototype_ `void OnPostCompile();`
- L261 _private prototype_ `void OnChangeDebugPlatform(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L264 _public prototype_ `void OnCustomizableObjectStatusChanged(FCustomizableObjectStatus::EState PreviousState, FCustomizableObjectStatus::EState CurrentState);`
- L267 _public prototype_ `static UCustomizableObject* GetAbsoluteCOParent(const UCustomizableObjectNodeObject* const Root);` — Helpers to get the absolute parent of a Customizable Object
- L270 _public member_ `static const FName ViewportTabId;` — The tab ids for all the tabs used
- L271 _public member_ `static const FName DetailsTabId;`
- L272 _public member_ `static const FName InstancePropertiesTabId;`
- L273 _public member_ `static const FName GraphTabId;`
- L274 _public member_ `static const FName SystemPropertiesTabId;`
- L275 _public member_ `static const FName AdvancedPreviewSettingsTabId;`
- L276 _public member_ `static const FName TextureAnalyzerTabId;`
- L277 _public member_ `static const FName PerformanceAnalyzerTabId;`
- L278 _public member_ `static const FName TagExplorerTabId;`
- L279 _public member_ `static const FName ObjectDebuggerTabId;`
- L280 _public member_ `static const FName PopulationClassTagManagerTabId;`
- L281 _public member_ `static const FName StatsTabId;`
- L286 _private member_ `TObjectPtr<UCustomizableObject> CustomizableObject = nullptr;` — The currently viewed object.
- L287 _private member_ `TObjectPtr<UCustomizableObjectInstance> PreviewInstance = nullptr;`
- L290 _private member_ `TMap< FName, TWeakPtr<class SDockableTab> > SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L293 _private member_ `TSharedPtr<SCustomizableObjectEditorViewportTabBody> Viewport;` — Preview Viewport widget
- L294 _private member_ `TSharedPtr<FCustomizableObjectEditorViewportClient> ViewportClient;`
- L296 _private member_ `TSharedPtr<IDetailsView> CustomizableInstanceDetailsView;`
- L300 _private member_ `TSharedPtr<class IDetailsView> ObjectDetailsView;` — Property View for Customizable Object and Nodes.
- L303 _private member_ `TSharedPtr<class SCustomizableObjectNodePinViewer> NodePinViewer;` — Widget to select which node pins are visible.
- L306 _private member_ `TObjectPtr<UUpdateClassWrapper> HelperCallback;` — UObject class to be able to use the update callback
- L309 _private member_ `TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;` — Scene preview settings widget, upcast of CustomizableObjectEditorAdvancedPreviewSettings
- L312 _private member_ `TSharedPtr<class SCustomizableObjectEditorAdvancedPreviewSettings> CustomizableObjectEditorAdvancedPreviewSettings;` — Scene preview settings widget
- L315 _private member_ `TSharedPtr<class SCustomizableObjecEditorTextureAnalyzer> TextureAnalyzer;` — Texture Analyzer table widget which shows the information of the transient textures used in the customizable object instance
- L318 _private member_ `TSharedPtr<SCustomizableObjectEditorPerformanceAnalyzer> PerformanceAnalyzer;` — New performance analyzer widget
- L321 _private member_ `TSharedPtr<class SCustomizableObjectEditorTagExplorer> TagExplorer;` — Widget to explore all the tags related with the Customizable Object open in the editor
- L324 _private prototype_ `void ExtendToolbar();` — Adds the customizable Object Editor commands to the default toolbar
- L327 _private member_ `const FString DocumentationURL{ TEXT("https` — URL to open when pressing the documentation button generated by UE
- L329 _private member_ `TObjectPtr<UProjectorParameter> ProjectorParameter = nullptr;`
- L331 _private member_ `TObjectPtr<UCustomSettings> CustomSettings = nullptr;`
- L333 _private member_ `TObjectPtr<UCustomizableObjectEditorProperties> EditorProperties = nullptr;`
- L335 _private member_ `bool bRecursionGuard = false;`
- L337 _private member_ `EGizmoType GizmoType = EGizmoType::Hidden;`
- L339 _private member_ `TArray<TSharedPtr<FString>> TargetPlatformNames;`
- L340 _private member_ `TSharedPtr<FString> DebugTargetPlatformName;`
- L342 _private member_ `bool bDebugForceLargeLODBias = false;`
- L344 _private member_ `TSharedPtr<SWidget> StatsWidget;`
- L347 _private member_ `TStrongObjectPtr<UCONodeClipSkeletalMeshWithSkeletalMesh> PreviouslySelectedNodeWithPreview = nullptr;` — Pointer to the CLip Skeletal Mesh with Skeletal Mesh node that was being shown in the CO Editor
- L350 _private member_ `FDelegateHandle PreviewMeshChangedDelegateHandle;` — Handle for the callback performed when the PreviewMesh of the PreviouslySelectedNodeWithPreview is changed (or any of its related properties)
- L354 _protected prototype_ `virtual FString GetDocumentationLink() const override;` — @return the documentation location for this editor

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace ESelectInfo`
- L51 _delegate_ `DECLARE_DELEGATE(FCreatePreviewInstanceFlagDelegate);`
- L51 _prototype_ `DECLARE_DELEGATE(FCreatePreviewInstanceFlagDelegate);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorActions.h` (Private)


#### class `FCustomizableObjectEditorCommands`  
`class FCustomizableObjectEditorCommands : public TCommands<FCustomizableObjectEditorCommands>`  
_L12-35_
- inherits: `TCommands<FCustomizableObjectEditorCommands>`
- L15 _public prototype_ `FCustomizableObjectEditorCommands();`
- L17 _public member_ `TSharedPtr< FUICommandInfo > Compile;`
- L18 _public member_ `TSharedPtr< FUICommandInfo > CompileOnlySelected;`
- L19 _public member_ `TSharedPtr< FUICommandInfo > ResetCompileOptions;`
- L20 _public member_ `TSharedPtr< FUICommandInfo > GraphViewer;`
- L21 _public member_ `TSharedPtr< FUICommandInfo > CodeViewer;`
- L22 _public member_ `TSharedPtr< FUICommandInfo > UpdateCookDataDistributionId;`
- L24 _public member_ `TSharedPtr< FUICommandInfo > PerformanceAnalyzer;`
- L25 _public member_ `TSharedPtr< FUICommandInfo > ResetPerformanceReportOptions;`
- L26 _public member_ `TSharedPtr< FUICommandInfo > TextureAnalyzer;`
- L28 _public member_ `TSharedPtr< FUICommandInfo > CompileGatherReferences;`
- L29 _public member_ `TSharedPtr< FUICommandInfo > ClearGatheredReferences;`
- L34 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `FCustomizableObjectEditorViewportCommands`  
`class FCustomizableObjectEditorViewportCommands : public TCommands<FCustomizableObjectEditorViewportCommands>`  
_L41-71_
- inherits: `TCommands<FCustomizableObjectEditorViewportCommands>`
- L45 _public prototype_ `FCustomizableObjectEditorViewportCommands();`
- L47 _public member_ `TSharedPtr<FUICommandInfo> SetDrawUVs;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> SetShowSky;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> SetShowBounds;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> SetShowCollision;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> SetCameraLock;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> SaveThumbnail;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> BakeInstance;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> StateChangeShowData;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> StateChangeShowGeometryData;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> ShowDisplayInfo;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> EnableClothSimulation;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> DebugDrawPhysMeshWired;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> SetShowNormals;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> SetShowTangents;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> SetShowBinormals;`
- L65 _public member_ `TArray<TSharedPtr< FUICommandInfo >> PlaybackSpeedCommands;` — Command list for playback speed, indexed by EPlaybackSpeeds
- L70 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorLevelProfile.h` (Private)


#### class `LevelProfileManage`  
`class LevelProfileManage`  
_L10-38_
- L14 _public prototype_ `static bool ProfileNameExist(const TArray<FPreviewSceneProfile>& ArrayProfile, const FString& Name);` — Verify if given profile name alreday exists
- L17 _public prototype_ `static bool LoadProfileUObjectNames(const FString& AssetPath, TArray<FString>& ArrayDirectionalLight, TArray<FString>& ArrayPostProcess, TArray<FString>& ArraySkyLight);` — Once selected a ULevel asset, load all possible elements from this level so the user selects which ones to use for the profile
- L23 _public prototype_ `static bool LoadProfileUObjects(const FString& AssetPath, const FString DirectionalLightName, const FString PostProcessVolumeName, const FString SkyLightName, class ADirectionalLight*& DirectionalLight, class APostProcessVolume*& PostProcessVolume, class ASkyLight*& SkyLight);` — Once selected a ULevel asset, load all elements needed (directional light, post process volume and sky light AActors
- L32 _public prototype_ `static bool FillPreviewSceneProfile(const FString& ProfileName, const FString& ProfilePath, const FString& DirectionalLightName, const FString& PostProcessVolumeName, const FString& SkyLightName, FPreviewSceneProfile& PreviewSceneProfile);` — Fill the struct parameter PreviewSceneProfile with the information from the profile with name given

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorLogger.h` (Private)


#### enum `ELoggerCategory`  
`enum class ELoggerCategory`  
_L16-22_
- desc: Notification categories.
- L18 _public enumerator_ `General`
- L19 _public enumerator_ `GraphSearch`
- L20 _public enumerator_ `Compilation`
- L21 _public enumerator_ `COInstanceBaking`

#### enum `ELoggerSpamBin`  
`enum class ELoggerSpamBin : uint8`  
_L26-30_
- desc: Notification spam prevention bins. Each bin will only show a limited amount of messages of its type, after which it will simply state "and X more BINNAME warnings/errors"
- L28 _public enumerator_ `TagsNotFound = 0`
- L29 _public enumerator_ `ShowAll` — Notifications added to this bin will always be shown.

#### class `FLogParameters`  
`class FLogParameters`  
_L34-96_
- desc: Log parameters. Holds all parameters required to create a new CustomizableObjectEditorLogger log.
- L40 _public prototype_ `FLogParameters& SubText(const FText& SubText);` — Optional parameters setters
- L41 _public prototype_ `FLogParameters& SubText(FText&& SubText);`
- L43 _public prototype_ `FLogParameters& Category(ELoggerCategory Category);`
- L45 _public prototype_ `FLogParameters& Severity(EMessageSeverity::Type MessageSeverity);`
- L47 _public prototype_ `FLogParameters& Context(const TArray<const UObject*>& Context);`
- L49 _public prototype_ `FLogParameters& Context(const UObject& Context);`
- L51 _public prototype_ `FLogParameters& BaseObject(bool BaseObject = true);`
- L53 _public prototype_ `FLogParameters& CustomNotification(bool CustomNotification = true);`
- L55 _public prototype_ `FLogParameters& Notification(bool Notification = true);`
- L57 _public prototype_ `FLogParameters& FixNotification(bool FixNotification = true);`
- L59 _public prototype_ `FLogParameters& SpamBin(ELoggerSpamBin SpamBin);`
- L61 _public prototype_ `FLogParameters& CustomizableObject(UCustomizableObject* Object = nullptr);`
- L64 _public prototype_ `void Log();` — Actually display the log.
- L68 _private prototype_ `FLogParameters(FCustomizableObjectEditorLogger& Logger, const FText& Text);` — Constructor. Contains all required parameters.
- L69 _private prototype_ `FLogParameters(FCustomizableObjectEditorLogger& Logger, FText&& Text);`
- L71 _private member_ `FCustomizableObjectEditorLogger& Logger;`
- L74 _private member_ `const FText ParamText;` — Required parameters
- L77 _private member_ `TAttribute<FText> ParamSubText;` — Optional parameters
- L79 _private member_ `ELoggerCategory ParamCategory = ELoggerCategory::General;`
- L81 _private member_ `ELoggerSpamBin ParamSpamBin = ELoggerSpamBin::ShowAll;`
- L83 _private member_ `EMessageSeverity::Type ParamSeverity = EMessageSeverity::Info;`
- L85 _private member_ `TArray<const UObject*> ParamContext;`
- L87 _private member_ `bool bParamBaseObject = false;`
- L89 _private member_ `bool bParamCustomNotification = false;`
- L91 _private member_ `bool bParamNotification = true;`
- L93 _private member_ `bool bParamFixNotification = false;`
- L95 _private member_ `TWeakObjectPtr<UCustomizableObject> ParamCustomizableObject;`

#### class `FCustomizableObjectEditorLogger`  
`class FCustomizableObjectEditorLogger`  
_L103-136_
- desc: Customizable Object Editor Module Logger. Common log utilities. Avoids bombarding the user with many notifications. The Logger will only shows a notification per category. Any new notification will override the previous one.
- L107 _public prototype_ `static FLogParameters CreateLog(const FText& Text);` — Create a new log.
- L108 _public prototype_ `static FLogParameters CreateLog(FText&& Text);`
- L111 _public prototype_ `void Log(FLogParameters& LogParameters);` — Display the log. Equivalent to FLogParameters::Log().
- L114 _public prototype_ `static void DismissNotification(ELoggerCategory Category);` — Dismiss a fixed notification.
- L128 _private member_ `TMap<ELoggerCategory, FCategoryData> CategoriesData;` — Data for each category.
- L130 _private member_ `const static FName LOG_NAME;`
- L132 _private member_ `const static float NOTIFICATION_DURATION;`
- L135 _private prototype_ `void OpenMessageLog() const;` — Callback. Open the message log window.

#### struct `FCustomizableObjectEditorLogger::FCategoryData`  
`struct FCategoryData`  
_L118-125_
- desc: Category data.
- L121 _public member_ `TWeakPtr<SNotificationItem> Notification;` — Pointer to the last notification widget.
- L124 _public member_ `uint32 NumMessages = 0;` — Number of new messages throw to this category since the notification was shown.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorModule.h` (Private)


#### class `FCustomizableObjectEditorModule`  
`class FCustomizableObjectEditorModule : public ICustomizableObjectEditorModulePrivate, public FTickableCookObject`  
_L44-137_
- inherits: `ICustomizableObjectEditorModulePrivate,FTickableCookObject`
- desc: StaticMesh editor module
- L48 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L49 _public prototype_ `virtual void ShutdownModule() override;`
- L52 _public prototype_ `virtual FCustomizableObjectEditorLogger& GetLogger() override;` — ICustomizableObjectEditorModule interface
- L53 _public prototype_ `virtual bool IsCompilationOutOfDate(const UCustomizableObject& Object, bool bSkipIndirectReferences, TArray<FName>& OutOfDatePackages, TArray<FName>& OutAddedPackages, TArray<FName>& OutRemovedPackages, bool& bOutVersionDiff) const override;`
- L54 _public prototype_ `virtual void IsCompilationOutOfDate(const UCustomizableObject& Object, bool bSkipIndirectReferences, float MaxTime, const IsCompilationOutOfDateCallback& Callback) const override;`
- L55 _public prototype_ `virtual bool IsRootObject(const UCustomizableObject& Object) const override;`
- L56 _public prototype_ `virtual FString GetCurrentReleaseVersionForObject(const UCustomizableObject& Object) const override;`
- L57 _public prototype_ `virtual UCustomizableObject* GetRootObject(UCustomizableObject* ChildObject) const override;`
- L58 _public prototype_ `virtual const UCustomizableObject* GetRootObject(const UCustomizableObject* ChildObject) const override;`
- L59 _public prototype_ `virtual void GetAllObjectsInGraph(UCustomizableObject*, TSet<UCustomizableObject*>& OutRelated) const override;`
- L60 _public prototype_ `virtual void OnUpstreamCOsLoadedFixup(UCustomizableObject* Object, int32 CustomizableObjectCustomVersion) const override;`
- L61 _public prototype_ `virtual void BakeCustomizableObjectInstance(UCustomizableObjectInstance* InTargetInstance, const FBakingConfiguration& InBakingConfig) override;`
- L62 _public prototype_ `virtual void EvictSkeletalMeshThumbnailScene(USkeletalMesh* SkeletalMesh) const override;`
- L63 _public prototype_ `virtual USkeletalMesh* GetReferenceSkeletalMesh(const UCustomizableObject& Object, const FName& ComponentName) const override;`
- L64 _public prototype_ `virtual TMap<FName, FGuid> GetParticipatingObjects(const UCustomizableObject* Object, const FCompilationOptions* Options = nullptr) const override;`
- L65 _public prototype_ `virtual void BackwardsCompatibleFixup(UEdGraph& Graph, int32 CustomizableObjectCustomVersion) override;`
- L66 _public prototype_ `virtual void PostBackwardsCompatibleFixup(UEdGraph& Graph) override;`
- L67 _public prototype_ `virtual void CancelCompileRequests() override;`
- L68 _public prototype_ `virtual int32 GetNumCompileRequests() override;`
- L69 _public prototype_ `virtual bool IsCompiling(const UCustomizableObject& Object) const override;`
- L70 _public prototype_ `virtual void CompileCustomizableObject(UCustomizableObject& Object, const FCompileParams* Params, bool bSilent, bool bForce) override;`
- L71 _public prototype_ `virtual void Tick(bool bBlocking) override;`
- L72 _public prototype_ `virtual int32 GetRemainingWork() const override;`
- L73 _public prototype_ `virtual void BeginCacheForCookedPlatformData(UCustomizableObject& Object, const ITargetPlatform* TargetPlatform) override;`
- L74 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(UCustomizableObject& Object, const ITargetPlatform* TargetPlatform) override;`
- L75 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetCustomizableObjectEditorToolBarExtensibilityManager() override`
- L76 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetCustomizableObjectEditorMenuExtensibilityManager() override`
- L77 _public prototype_ `virtual void AddPendingLoad(UCustomizableObject* Object) override;`
- L80 _public prototype_ `virtual void EnqueueCompileRequest(const TSharedRef<FCompilationRequest>& InCompilationRequest, bool bForceRequest = false) override;` — ICustomizableObjectEditorModulePrivate interface
- L81 _public prototype_ `virtual const TMap<FName, FLinearColor>& GetExternalPinTypeColors() const override;`
- L82 _public prototype_ `virtual void RegisterExternalOperation(const UScriptStruct* Operation) override;`
- L83 _public prototype_ `virtual void UnregisterExternalOperation(const UScriptStruct* Operation) override;`
- L84 _public prototype_ `virtual const TMap<FName, TStrongObjectPtr<const UScriptStruct>>& GetExternalPinTypes() const override;`
- L85 _public prototype_ `virtual const TMap<FName, FText>& GetExternalPinFriendlyName() const override;`
- L88 _public function_ `virtual ETickableTickType GetTickableTickType() const override` — FTickableGameObject interface
- L89 _public prototype_ `virtual bool IsTickable() const override;`
- L90 _public prototype_ `virtual void Tick( float InDeltaTime ) override;`
- L91 _public prototype_ `virtual TStatId GetStatId() const override;`
- L94 _public prototype_ `virtual void TickCook(float DeltaTime, bool bCookCompete) override;` — FTickableCookObject interface
- L97 _private member_ `TSharedPtr<FExtensibilityManager> CustomizableObjectEditor_ToolBarExtensibilityManager;`
- L98 _private member_ `TSharedPtr<FExtensibilityManager> CustomizableObjectEditor_MenuExtensibilityManager;`
- L101 _private member_ `TArray<FName> RegisteredCustomDetails;` — List of registered custom details to remove later.
- L104 _private member_ `TMap<FName, uint32> RegisteredExternalType;` — How many times a pin type has been registered.
- L106 _private member_ `TMap<FName, FLinearColor> ExternalTypeTypePinColors;`
- L108 _private member_ `TMap<FName, FText> ExternalTypeFriendlyName;`
- L110 _private member_ `TMap<FName, TStrongObjectPtr<const UScriptStruct>> ExternalTypeCategories;`
- L112 _private prototype_ `virtual void OnUpstreamCOsLoaded(UCustomizableObject* Object) const;`
- L115 _private prototype_ `void RegisterCustomDetails(FPropertyEditorModule& PropertyModule, const UClass* Class, FOnGetDetailCustomizationInstance DetailLayoutDelegate);` — Register Custom details. Also adds them to RegisteredCustomDetails list.
- L117 _private member_ `FCustomizableObjectEditorLogger Logger;`
- L119 _private member_ `TSharedRef<FCustomizableObjectCompiler> Compiler = MakeShared<FCustomizableObjectCompiler>();`
- L122 _private member_ `IConsoleCommand* LaunchCOIECommand = nullptr;` — Command to look for Customizable Object Instance in the player pawn of the current world and open its Customizable Object Instance Editor
- L124 _private prototype_ `static void OpenCOIE(const TArray<FString>& Arguments);`
- L127 _private prototype_ `void RegisterFactory();` — Register the COI factory
- L129 _private prototype_ `bool HandleSettingsSaved();`
- L130 _private prototype_ `void RegisterSettings();`
- L133 _private member_ `TMap<TWeakObjectPtr<UCustomizableObject>, TArray<TSharedRef<FCompilationRequest>>> CookCompileRequests;` — Cook requests.
- L136 _private member_ `TSet<TStrongObjectPtr<UCustomizableObject>> ObjectsPendingLoad;` — List of CustomizableObjects pending to complete loading.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _prototype_ `void GetReferencingPackages(const UCustomizableObject& Object, TArray<FAssetData>& ObjectNames);` — Get a list of packages that are used by the compilation but are not directly referenced. List includes: - Child UCustomizableObjects: Have inverted references. - UDataTable: Data Tables used by Composite Data Tables are indirectly referenced by the UStruct and filtered by path.
- L35 _prototype_ `int32 ConvertOptimizationLevel(ECustomizableObjectOptimizationLevel OptimizationLevel);` — Convert the Optimization Level enum to the int32 internal format.
- L37 _prototype_ `TMap<FString, FString> GetCompileOnlySelectedParameters(const UCustomizableObjectInstance& Instance);`
- L39 _prototype_ `UE::DerivedData::ECachePolicy GetDerivedDataCachePolicyForEditor();`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorNodeContextCommands.h` (Private)


#### class `FCustomizableObjectEditorNodeContextCommands`  
`class FCustomizableObjectEditorNodeContextCommands : public TCommands<FCustomizableObjectEditorNodeContextCommands>`  
_L13-33_
- inherits: `TCommands<FCustomizableObjectEditorNodeContextCommands>`
- desc: Class containing commands for viewport menu actions
- L16 _public function_ `FCustomizableObjectEditorNodeContextCommands() : TCommands<FCustomizableObjectEditorNodeContextCommands> ( TEXT("CustomizableObjectEditorNodeContext"),`
- L28 _public member_ `TSharedPtr<FUICommandInfo> CreateComment;` — Create comment
- L32 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorPerformanceAnalyzer.h` (Private)


#### class `FInstanceUpdateDataElement`  
`class FInstanceUpdateDataElement`  
_L28-39_
- desc: Backend object that represents the update of one instance. Currently only represents the data for the initial generation of the instance update
- L32 _public member_ `TStrongObjectPtr<UCustomizableObjectInstance> Instance = nullptr;` — Instance whose data this object exposes
- L35 _public member_ `uint32 UpdateIndex = 0;` — Index to aid in the sorting of the FInstanceUpdateDataElement in the SListView that contains them
- L38 _public member_ `FInstanceUpdateStats UpdateStats;` — Container with all the perf data in relation to the instance this object represents

#### class `SInstanceUpdateDataRow`  
`class SInstanceUpdateDataRow : public SMultiColumnTableRow<TSharedPtr<FInstanceUpdateDataElement>>`  
_L45-59_
- inherits: `SMultiColumnTableRow<TSharedPtr<FInstanceUpdateDataElement>>`
- desc: Slate that exposes the perf data of one single instance update.
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<FInstanceUpdateDataElement>& Element, const TSharedPtr<FInstanceUpdateStatistics>& Statistics);`
- L52 _private member_ `TSharedPtr<FInstanceUpdateDataElement> InstanceUpdateElement;` — Backend object whose data we are drawing
- L53 _private member_ `TSharedPtr<FInstanceUpdateStatistics> InstanceUpdateStatistics;`
- L56 _private prototype_ `void OnInstanceNameNavigation() const;` — Method invoked when the hyperlink showing the name of the instance is clicked
- L58 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`

#### class `SCustomizableObjectEditorPerformanceAnalyzer`  
`class SCustomizableObjectEditorPerformanceAnalyzer : public SCompoundWidget, public FGCObject`  
_L66-173_
- inherits: `SCompoundWidget,FGCObject`
- desc: Slate that exposes perf data of a deterministic set of instances generated and then updated in the context of the editor. Will update the values of some CVARS that will, at the end, be restored.
- L69 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorPerformanceAnalyzer)`
- L70 _public prototype_ `SLATE_ARGUMENT(UCustomizableObject*,CustomizableObject) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L79 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L80 _private prototype_ `virtual FString GetReferencerName() const override;`
- L83 _private prototype_ `EVisibility GetVisibilityForBenchmarkingSettingsMessage() const;`
- L86 _private prototype_ `void OnTargetAmountOfInstancesValueChange(uint32 NewValue);` — Instance amount to generate and update controls
- L87 _private prototype_ `void OnTargetAmountOfInstancesValueCommited(uint32 NewValue, ETextCommit::Type CommitType);`
- L88 _private prototype_ `TOptional<uint32> OnTargetAmountOfInstancesValueRequested() const;`
- L91 _private prototype_ `FReply OnInstanceUpdateButtonClicked();` — Random Instances generation and Update button
- L92 _private prototype_ `bool IsInstanceUpdateButtonEnabled() const;`
- L93 _private prototype_ `FText GetGenerateInstancesButtonText() const;`
- L96 _private prototype_ `FReply OnInstanceUpdateAbortButtonClicked();` — Methods for the button that allows the user to cancel the execution of the test
- L97 _private prototype_ `EVisibility ShouldInstanceUpdateAbortButtonBeVisible() const;`
- L98 _private prototype_ `bool IsInstanceUpdateAbortButtonEnabled() const;`
- L99 _private prototype_ `FText GetStopUpdatesButtonText() const;`
- L102 _private prototype_ `void ClearPendingUpdatesQueue();` — Utility methods
- L105 _private prototype_ `void OnCustomizableObjectCompilationFinished();` — Compilation handling
- L106 _private prototype_ `void CacheCustomizableObjectModelData();`
- L112 _private prototype_ `void SetMutableBenchmarkingSystemState(const bool bNewState);` — Enable or disable the mutable benchmarking settings. @param bNewState Set it to true to enable the benchmarking configurations and false to disable them.
- L115 _private prototype_ `TSharedRef<ITableRow> OnGenerateInstanceUpdateRow(TSharedPtr<FInstanceUpdateDataElement> InstanceUpdateDataElement, const TSharedRef<STableViewBase>& TableViewBase);` — ListView methods
- L116 _private prototype_ `void OnInstanceUpdateListViewSort(EColumnSortPriority::Type ColumnPriority, const FName& ColumnId, EColumnSortMode::Type NewSortMode);`
- L117 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(FName ColumnName) const;`
- L124 _private prototype_ `void OnBenchmarkMeshUpdated(TSharedRef<FUpdateContextPrivate> UpdateContextPrivate, FInstanceUpdateStats UpdateStats);` — Callback invoked each time the LogBenchmarkUtil notifies us that an initial generation update (mesh Update) has been produced @param UpdateContextPrivate The context of the instance that got updated @param UpdateStats The Perf data of the instance that was updated.
- L127 _private prototype_ `void ScheduleNextInstanceUpdate();` — Grab the next available instance to be updated
- L130 _private prototype_ `bool AreUpdatesPending() const;` — Determines if there are updates to wait for. Checks not only the queue but also the current instnace being udpated
- L132 _private prototype_ `void ComputeStatistics();`
- L135 _private member_ `FDelegateHandle OnMeshUpdatePerfReportDelegateHandle;` — Delegate pointing to the LogBenchmarkUtil on Mesh Updated event
- L138 _private member_ `static bool bIsPerformanceAnalyzerRunning;` — Is this slate running? Used to determine if another instance of the slate is performing the test
- L141 _private member_ `uint32 InstancesToGeneratePerState = 24;` — The amount of instances per state we want to generate and then update
- L144 _private member_ `TObjectPtr<UCustomizableObjectSystem> System;` — Cached Customizable Object System object
- L147 _private member_ `TStrongObjectPtr<UCustomizableObject> CustomizableObject;` — CO whose data we are we reporting.
- L150 _private member_ `TSharedPtr<SListView<TSharedPtr<FInstanceUpdateDataElement>>> InstanceUpdatesListView;` — List view showing all the instance update data elements
- L153 _private member_ `TArray<TSharedPtr<FInstanceUpdateDataElement>> InstanceUpdateElements;` — Instance update elements (size == RandomInstancesToGenerate) at the time of the update request
- L155 _private member_ `TSharedPtr<FInstanceUpdateStatistics> InstanceUpdateStatistics = MakeShared<FInstanceUpdateStatistics>();`
- L158 _private member_ `FName CurrentSortColumn;` — The name of the last column the user wanted to sort
- L160 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::None;` — The sort type applied to the last column that got sorted
- L163 _private member_ `TSpscQueue<TStrongObjectPtr<UCustomizableObjectInstance>> InstancesToUpdate;` — Updating process variables
- L165 _private member_ `TStrongObjectPtr<UCustomizableObjectInstance> CurrentInstance = nullptr;` — Current instance being updated
- L168 _private member_ `uint32 UpdatedInstancesCount = 0;` — Control counters (UI)
- L169 _private member_ `uint32 TotalScheduledUpdates = 0;`
- L172 _private member_ `TSharedPtr<FCompilationOptions> LastCompilationOptions = nullptr;` — The compilation options the last time we compiled the CO

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorSettings.h` (Private)


#### class `UCustomizableObjectEditorSettings`  
`class UCustomizableObjectEditorSettings : public UObject`  
_L14-39_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: COE Module, Editor Settings.
- L21 _public member_ `bool bDisableMutableCompileInEditor;` — `UPROPERTY(config, EditAnywhere, Category = Compilation)` — If true, Mutable won't compile any COs in the Editor.
- L25 _public member_ `bool bEnableAutomaticCompilation = true;` — `UPROPERTY(config, EditAnywhere, Category = AutomaticCompilation)` — If true, Mutable will automatically compile, if needed, COs being used by Actors.
- L29 _public member_ `bool bCompileObjectsSynchronously = false;` — `UPROPERTY(config, EditAnywhere, Category = AutomaticCompilation)` — If true, AutomaticCompilation will happen synchronously.
- L32 _public member_ `bool bEnableDeveloperOptions = false;` — `UPROPERTY(config, EditAnywhere, Category = Developer)`
- L35 _public member_ `ECustomizableObjectDDCPolicy EditorDerivedDataCachePolicy = ECustomizableObjectDDCPolicy::Default;` — `UPROPERTY(config, EditAnywhere, Category = DerivedDataCache, DisplayName = "DDC policy for editor compilations")`
- L38 _public member_ `ECustomizableObjectDDCPolicy CookDerivedDataCachePolicy = ECustomizableObjectDDCPolicy::Default;` — `UPROPERTY(config, EditAnywhere, Category = DerivedDataCache, DisplayName = "DDC policy for cook compilations")`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorStyle.h` (Private)


#### class `FCustomizableObjectEditorStyle`  
`class FCustomizableObjectEditorStyle`  
_L10-35_
- desc: Manages the style which provides resources for niagara editor widgets.
- L15 _public prototype_ `static void Initialize();` — Creates and Registers the plugin SlateStyle
- L18 _public prototype_ `static void Shutdown();` — Unregisters the plugin SlateStyle
- L21 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for niagara editor widgets
- L23 _public prototype_ `static FName GetStyleSetName();`
- L24 _public prototype_ `static FString RelativePathToPluginPath(const FString& RelativePath, const ANSICHAR* Extension);`
- L30 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();` — Creates the plugin style
- L34 _private member_ `static TSharedPtr< class FSlateStyleSet > CustomizableObjectEditorStyleInstance;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorUtilities.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `bool CompareNames(const TSharedPtr<FString>& sp1, const TSharedPtr<FString>& sp2);`
- L12 _prototype_ `void ConditionalPostLoadReference(UObject& Object);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorViewportClient.h` (Private)


#### enum `EWidgetType`  
`enum class EWidgetType : uint8`  
_L59-66_
- L61 _public enumerator_ `Hidden`
- L62 _public enumerator_ `Projector`
- L63 _public enumerator_ `ClipMorph`
- L64 _public enumerator_ `ClipMesh`
- L65 _public enumerator_ `Light`

#### enum `EMutableAnimationPlaybackSpeeds::Type`  
`enum Type`  
_L71-83_
- L73 _public enumerator_ `OneTenth = 0`
- L74 _public enumerator_ `Quarter`
- L75 _public enumerator_ `Half`
- L76 _public enumerator_ `ThreeQuarters`
- L77 _public enumerator_ `Normal`
- L78 _public enumerator_ `Double`
- L79 _public enumerator_ `FiveTimes`
- L80 _public enumerator_ `TenTimes`
- L81 _public enumerator_ `Custom`
- L82 _public enumerator_ `NumPlaybackSpeeds`

#### class `FCustomizableObjectEditorViewportClient`  
`class FCustomizableObjectEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FCustomizableObjectEditorViewportClient>`  
_L90-456_
- inherits: `FEditorViewportClient,TSharedFromThis<FCustomizableObjectEditorViewportClient>`
- desc: Viewport which shows the scene with the generated Instance.
- L93 _public prototype_ `FCustomizableObjectEditorViewportClient(TWeakPtr<ICustomizableObjectInstanceEditor> InCustomizableObjectEditor, FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, const TSharedPtr<SEditorViewport>& EditorViewportWidget);`
- L94 _public prototype_ `~FCustomizableObjectEditorViewportClient();`
- L97 _public member_ `class UPersonaOptions* ConfigOption;` — persona config options
- L100 _public prototype_ `virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;` — FEditorViewportClient interface
- L101 _public prototype_ `virtual void Draw(FViewport* Viewport,FCanvas* Canvas) override;`
- L103 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L104 _public prototype_ `virtual bool InputWidgetDelta(FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override;`
- L105 _public prototype_ `virtual void TrackingStarted(const FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L106 _public prototype_ `virtual void TrackingStopped() override;`
- L107 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L108 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L109 _public prototype_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;`
- L110 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L111 _public prototype_ `virtual FMatrix GetWidgetCoordSystem() const override;`
- L112 _public prototype_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override;`
- L113 _public prototype_ `virtual void SetWidgetCoordSystemSpace(ECoordSystem NewCoordSystem) override;`
- L114 _public prototype_ `virtual void SetViewportType(ELevelViewportType InViewportType) override;`
- L117 _public prototype_ `void CreatePreviewActor(const TWeakObjectPtr<UCustomizableObjectInstance>& InInstance);`
- L119 _public prototype_ `TMap<FName, TWeakObjectPtr<UDebugSkelMeshComponent>>& GetPreviewMeshComponents();`
- L121 _public prototype_ `void SetPreviewAnimationAsset(UAnimationAsset* AnimAsset);`
- L130 _public prototype_ `void DrawUVs(FViewport* InViewport, FCanvas* InCanvas, int32 InTextYPos);` — Draws the UV overlay for the current LOD. @param	InViewport					The viewport to draw to @param	InCanvas					The canvas to draw to @param	InTextYPos					The Y-position to begin drawing the UV-Overlay at (due to text displayed above it).
- L136 _public prototype_ `void BakeInstance();` — Bake the instance currently present in the editor. Internally will schedule the compilation and later the update of the instance before baking its resources.
- L143 _private prototype_ `void OnCOForBakingCompilationEnd(const FCompileCallbackParams& InCompileCallbackParams);` — Callback executed after the Customizable Object instance for baking had it's customizable object compiled @param InCompileCallbackParams Data returned on compilation that includes the end state of the compilation
- L148 _private prototype_ `void OnInstanceForBakingUpdate(const FUpdateContext& Result);` — Callback executed after the instance in the editor gets updated for baking its contents.
- L152 _public prototype_ `void StateChangeShowGeometryData();` — Callback to show / hide instance geometry data
- L155 _public prototype_ `void SetDrawUVOverlay();` — Callback for toggling the UV overlay show flag.
- L158 _public prototype_ `bool IsSetDrawUVOverlayChecked() const;` — Callback for checking the UV overlay show flag.
- L161 _public prototype_ `void SetDrawUV(const FName ComponentName, const int32 LODIndex, const int32 SectionIndex, const int32 UVIndex);` — Specify which UV to draw. -1 values will not draw anything.
- L164 _public prototype_ `void UpdateShowGridFromButton();` — Callback for toggling the grid show flag.
- L170 _public prototype_ `void UpdateShowGrid(bool bKeepOldValue);` — Updates the visual state of the ShowGrid Button and CheckBox in the Preview Settings @param bKeepOldValue - If true, it will keep the visibility of the grid and floor, otherwise it will invert it
- L173 _public prototype_ `bool IsShowGridChecked() const;` — Callback for checking the grid show flag.
- L176 _public prototype_ `void UpdateShowSkyFromButton();` — Callback for toggling the sky show flag.
- L182 _public prototype_ `void UpdateShowSky(bool bKeepOldValue);` — Updates the visual state of the ShowSky Button and CheckBox in the Preview Settings @param bKeepOldValue - If true, it will keep the visibility of the sky end environment, otherwise it will invert it
- L185 _public prototype_ `bool IsShowSkyChecked() const;` — Callback for checking the sky show flag.
- L188 _public prototype_ `void SetShowBounds();` — Callback for toggling the bounds show flag.
- L191 _public prototype_ `void ShowGizmoClipMorph(UCustomizableObjectNodeModifierClipMorph& ClipPlainNode);` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L194 _public prototype_ `void HideGizmoClipMorph();` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L197 _public prototype_ `void ShowGizmoClipMesh(UCustomizableObjectNode& ClipMeshNode, FTransform* ClipMeshTransform, UObject& InClipMesh, int32 LODIndex, int32 SectionIndex, int32 MaterialSlotIndex);` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L201 _private prototype_ `void UpdateGizmoClipMeshTransform(const FTransform& InTransform);` — Do not call directly. Method invoked each time the transform value of the clipping mesh is modified from the node.
- L205 _public prototype_ `void HideGizmoClipMesh();` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L208 _public prototype_ `void ShowGizmoProjector( const FWidgetLocationDelegate& WidgetLocationDelegate, const FOnWidgetLocationChangedDelegate& OnWidgetLocationChangedDelegate, const FWidgetDirectionDelegate& WidgetDirectionDelegate, const FOnWidgetDirectionChangedDelegate& OnWidgetDirectionChangedDelegate, const FWidgetUpDelegate& WidgetUpDelegate, const FOnWidgetUpChangedDelegate& OnWidgetUpChangedDelegate, const FWidgetScaleDelegate& WidgetScaleDelegate, const FOnWidgetScaleChangedDelegate& OnWidgetScaleChangedDelegate, const FWidgetAngleDelegate& WidgetAngleDelegate, const FProjectorTypeDelegate& ProjectorTypeDelegate, const FWidgetColorDelegate& WidgetColorDelegate, const FWidgetTrackingStartedDelegate& WidgetTrackingStartedDelegate);` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L219 _public prototype_ `void HideGizmoProjector();` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L222 _public prototype_ `void ShowGizmoLight(ULightComponent& Light);` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L225 _public prototype_ `void HideGizmoLight();` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L228 _public prototype_ `void SetAnimation(UAnimationAsset* Animation);` — Play the animation.
- L231 _public prototype_ `void AddLightToScene(ULightComponent* AddedLight);` — Add Light Component to the scene.
- L234 _public prototype_ `void RemoveLightFromScene(ULightComponent* RemovedLight);` — Remove Light component from the scene.
- L237 _public prototype_ `void RemoveAllLightsFromScene();` — Remove all Light components from the scene.
- L240 _public prototype_ `void SetCustomizableObject(UCustomizableObject* CustomizableObjectParameter);` — Setter of CustomizableObject
- L243 _public prototype_ `void DrawShadowedString(FCanvas* Canvas, float StartX, float StartY, const FLinearColor& Color, float TextScale, FString String);` — Helper method to draw shadowed string on viewport
- L246 _public prototype_ `void ShowInstanceGeometryInformation(FCanvas* InCanvas);` — Show pero LOD geometric information of the instance
- L249 _public prototype_ `void SetAdvancedShowFlagsForScene(const bool bAdvancedShowFlags);` — Sets up the ShowFlag according to the current preview scene profile
- L252 _public prototype_ `void OnAssetViewerSettingsChanged(const FName& InPropertyName);` — Delegate for preview profile is changed (used for updating show flags)
- L255 _public prototype_ `void DrawCylinderArc(FPrimitiveDrawInterface* PDI, const FMatrix& CylToWorld, const FVector& Base, const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, float Radius, float HalfHeight, uint32 Sides, const FMaterialRenderProxy* MaterialRenderProxy, uint8 DepthPriority, FColor Color, float MaxAngle);` — Debug draw a partial cylinder, given by MaxAngle in [0, 2PI]
- L258 _public prototype_ `bool GetFloorVisibility();` — Getter of viewport's floor visibility
- L261 _public prototype_ `void SetFloorVisibility(bool Value);` — Setter of viewport's floor visibility
- L264 _public prototype_ `bool GetGridVisibility();` — Getter of viewport's grid visibility
- L267 _public prototype_ `bool GetEnvironmentMeshVisibility();` — Getter of viewport's environment visibility
- L270 _public prototype_ `void SetEnvironmentMeshVisibility(uint32 Value);` — Setter of viewport's environment visibility
- L273 _public prototype_ `bool IsOrbitalCameraActive() const;` — Returns camera mode
- L276 _public prototype_ `void SetCameraMode(bool Value);` — Sets camera mode
- L279 _public prototype_ `void SetShowBones();` — Sets the skeletal mesh bones visibility
- L282 _public prototype_ `bool IsShowingBones() const;` — Returns true if bones are visible in viewport
- L284 _public prototype_ `const TArray<ULightComponent*>& GetLightComponents() const;`
- L286 _public prototype_ `void OnShowDisplayInfo();`
- L288 _public prototype_ `bool IsShowingMeshInfo() const;`
- L290 _public prototype_ `void OnEnableClothSimulation();`
- L292 _public prototype_ `bool IsClothSimulationEnabled() const;`
- L294 _public prototype_ `void OnDebugDrawPhysMeshWired();`
- L296 _public prototype_ `bool IsDebugDrawPhysMeshWired() const;`
- L298 _public prototype_ `FText GetMeshInfoText() const;`
- L300 _public prototype_ `void ToggleShowNormals();`
- L302 _public prototype_ `bool IsSetShowNormalsChecked() const;`
- L304 _public prototype_ `void ToggleShowTangents();`
- L306 _public prototype_ `bool IsSetShowTangentsChecked() const;`
- L308 _public prototype_ `void ToggleShowBinormals();`
- L310 _public prototype_ `bool IsSetShowBinormalsChecked() const;`
- L312 _public prototype_ `void SetPlaybackSpeedMode(EMutableAnimationPlaybackSpeeds::Type InMode);`
- L314 _public prototype_ `void SetCustomAnimationSpeed(float Speed);`
- L316 _public prototype_ `float GetCustomAnimationSpeed() const;`
- L318 _public prototype_ `EMutableAnimationPlaybackSpeeds::Type GetPlaybackSpeedMode() const;`
- L322 _private prototype_ `void DrawMeshBones(const UDebugSkelMeshComponent* MeshComponent, FPrimitiveDrawInterface* PDI);` — Draws Mesh Bones in foreground (From: FAnimationViewportClient)
- L324 _private prototype_ `void SetWidgetType(EWidgetType Type);`
- L326 _private prototype_ `bool HandleBeginTransform();`
- L327 _private prototype_ `bool HandleEndTransform();`
- L329 _private prototype_ `void OnPreSetSkeletalMesh(const FPreSetSkeletalMeshParams& Params);`
- L331 _private prototype_ `void OnInstanceUpdate(UCustomizableObjectInstance* Instance);`
- L334 _private member_ `TStrongObjectPtr<AActor> Actor;` — Preview Actor. All preview components are attached to this actor.
- L335 _private member_ `TMap<FName, TWeakObjectPtr<UDebugSkelMeshComponent>> SkeletalMeshComponents;`
- L338 _private member_ `bool bManipulating = false;` — True if the widget is being dragged.
- L341 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> CustomizableObjectEditorPtr;` — Pointer back to the editor tool that owns us
- L344 _private member_ `bool bDrawUVs;` — Flags for various options in the editor.
- L345 _private member_ `bool bDrawSky;`
- L348 _private member_ `FName UVDrawComponentName = NAME_None;` — UV to draw
- L349 _private member_ `int32 UVDrawSectionIndex = 0;`
- L350 _private member_ `int32 UVDrawLODIndex = 0;`
- L351 _private member_ `int32 UVDrawUVIndex = 0;`
- L353 _private member_ `UCustomizableObjectNodeModifierClipMorph* ClipMorphNode;`
- L354 _private member_ `TStrongObjectPtr<UMaterial> ClipMorphMaterial;`
- L355 _private member_ `bool bClipMorphLocalStartOffset;`
- L356 _private member_ `FVector ClipMorphOrigin;`
- L357 _private member_ `FVector ClipMorphOffset;`
- L358 _private member_ `FVector ClipMorphLocalOffset;`
- L359 _private member_ `FVector ClipMorphNormal;`
- L360 _private member_ `FVector ClipMorphXAxis;`
- L361 _private member_ `FVector ClipMorphYAxis;`
- L362 _private member_ `float MorphLength;`
- L363 _private member_ `FBoxSphereBounds MorphBounds;`
- L364 _private member_ `TStrongObjectPtr<UObject> ClipMeshNode;`
- L365 _private member_ `TStrongObjectPtr<UObject> ClipMesh;`
- L366 _private member_ `FDelegateHandle TransformExternallyChangedDelegateHandle;`
- L367 _private member_ `FTransform* ClipMeshTransform = nullptr;`
- L368 _private member_ `TStrongObjectPtr<UMaterial> ClipMeshMaterial;`
- L369 _private member_ `UStaticMeshComponent* ClipMeshStaticMeshComp;`
- L370 _private member_ `USkeletalMeshComponent* ClipMeshSkeletalMeshComp;`
- L371 _private member_ `float Radius1;`
- L372 _private member_ `float Radius2;`
- L373 _private member_ `float RotationAngle;`
- L376 _private member_ `ULightComponent* SelectedLightComponent;` — Light being edited
- L379 _private member_ `TArray<ULightComponent*> LightComponents;` — Spawned light components.
- L382 _private member_ `bool bIsCameraSetup = false;` — true if the camera has already being setup.
- L385 _private member_ `bool bUpdated = false;` — true if if has been updated after changing the actor.
- L388 _private member_ `UCustomizableObject* CustomizableObject;` — Customizable object being used
- L391 _private member_ `bool StateChangeShowGeometryDataFlag;` — Flag to control whether to show / hide the instance geometry information data
- L394 _private member_ `TStrongObjectPtr<UMaterialInterface> TransparentPlaneMaterialXY;` — Material for cylinder arc solid render
- L397 _private member_ `bool bSetOrbitalOnPerspectiveMode;` — bool to return the Camera mode to Orbital when changing the Camera view to Perspective
- L400 _private member_ `bool bShowBones;` — Flag to control the bones visibility in the viewport
- L403 _private member_ `bool bShowDebugClothing = false;` — Draw wireframe physics mesh.
- L407 _private member_ `TStrongObjectPtr<UCustomizableObjectInstance> BakeTempInstance = nullptr;` — Temp Instance used in the bake process if a new instance is needed because mutable texture streaming is enabled so the viewport instance does not have the high quality mips in the texture's platform data
- L410 _private member_ `bool bIsProgressiveMipStreamingEnabled = false;` — Cache System configuration cached before performing the mandatory instance update for baking so we can restore it after the bake operation
- L411 _private member_ `bool bIsOnlyGenerateRequestedLODsEnabled = false;`
- L414 _private member_ `bool bShowDisplayInfo = false;` — Show detailed mesh info text.
- L417 _private member_ `bool bDisableClothSimulation = false;` — See USkeletalMeshComponent::bDisableClothSimulation.
- L420 _private member_ `bool bDrawNormals = false;` — See USkeletalMeshComponent::bDrawNormals.
- L423 _private member_ `bool bDrawTangents = false;` — See USkeletalMeshComponent::bDrawTangents.
- L426 _private member_ `bool bDrawBinormals = false;` — See USkeletalMeshComponent::bDrawBinormals.
- L429 _private member_ `FWidgetLocationDelegate WidgetLocationDelegate;` — The following delegates currently are only used by the EWidgetType::Projector
- L430 _private member_ `FOnWidgetLocationChangedDelegate OnWidgetLocationChangedDelegate;`
- L432 _private member_ `FWidgetLocationDelegate WidgetDirectionDelegate;`
- L433 _private member_ `FOnWidgetLocationChangedDelegate OnWidgetDirectionChangedDelegate;`
- L435 _private member_ `FWidgetLocationDelegate WidgetUpDelegate;`
- L436 _private member_ `FOnWidgetLocationChangedDelegate OnWidgetUpChangedDelegate;`
- L438 _private member_ `FWidgetLocationDelegate WidgetScaleDelegate;`
- L439 _private member_ `FOnWidgetLocationChangedDelegate OnWidgetScaleChangedDelegate;`
- L441 _private member_ `FWidgetAngleDelegate WidgetAngleDelegate;`
- L443 _private member_ `FProjectorTypeDelegate ProjectorTypeDelegate;`
- L445 _private member_ `FWidgetColorDelegate WidgetColorDelegate;`
- L447 _private member_ `FWidgetTrackingStartedDelegate WidgetTrackingStartedDelegate;`
- L449 _private member_ `EWidgetType WidgetType = EWidgetType::Hidden;`
- L452 _private member_ `EMutableAnimationPlaybackSpeeds::Type AnimationPlaybackSpeedMode = EMutableAnimationPlaybackSpeeds::Normal;` — Selected playback speed mode, used for deciding scale
- L455 _private member_ `float CustomAnimationSpeed = 1.0f;` — Custom Animation speed in the viewport. Transient setting.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EAnimationMode`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal(FVector, FWidgetLocationDelegate);`
- L36 _prototype_ `DECLARE_DELEGATE_RetVal(FVector, FWidgetLocationDelegate);`
- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetLocationChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(FVector, FWidgetDirectionDelegate);`
- L37 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetLocationChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(FVector, FWidgetDirectionDelegate);`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal(FVector, FWidgetDirectionDelegate);`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetDirectionChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(FVector, FWidgetUpDelegate);`
- L40 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetDirectionChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(FVector, FWidgetUpDelegate);`
- L42 _delegate_ `DECLARE_DELEGATE_RetVal(FVector, FWidgetUpDelegate);`
- L43 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetUpChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(FVector, FWidgetScaleDelegate);`
- L43 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetUpChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(FVector, FWidgetScaleDelegate);`
- L45 _delegate_ `DECLARE_DELEGATE_RetVal(FVector, FWidgetScaleDelegate);`
- L46 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetScaleChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(float, FWidgetAngleDelegate);`
- L46 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetScaleChangedDelegate, const FVector&) DECLARE_DELEGATE_RetVal(float, FWidgetAngleDelegate);`
- L48 _delegate_ `DECLARE_DELEGATE_RetVal(float, FWidgetAngleDelegate);`
- L50 _delegate_ `DECLARE_DELEGATE_RetVal(ECustomizableObjectProjectorType, FProjectorTypeDelegate);`
- L50 _prototype_ `DECLARE_DELEGATE_RetVal(ECustomizableObjectProjectorType, FProjectorTypeDelegate);`
- L52 _delegate_ `DECLARE_DELEGATE_RetVal(FColor, FWidgetColorDelegate);`
- L52 _prototype_ `DECLARE_DELEGATE_RetVal(FColor, FWidgetColorDelegate);`
- L54 _delegate_ `DECLARE_DELEGATE(FWidgetTrackingStartedDelegate);`
- L54 _prototype_ `DECLARE_DELEGATE(FWidgetTrackingStartedDelegate);`
- L69 _namespace_ `namespace EMutableAnimationPlaybackSpeeds`
- L85 _externvar_ `extern float Values[NumPlaybackSpeeds];` (scope `EMutableAnimationPlaybackSpeeds`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorViewportLODCommands.h` (Private)


#### class `FCustomizableObjectEditorViewportLODCommands`  
`class FCustomizableObjectEditorViewportLODCommands : public TCommands<FCustomizableObjectEditorViewportLODCommands>`  
_L13-60_
- inherits: `TCommands<FCustomizableObjectEditorViewportLODCommands>`
- desc: Class containing commands for persona viewport LOD actions
- L16 _public function_ `FCustomizableObjectEditorViewportLODCommands() : TCommands<FCustomizableObjectEditorViewportLODCommands> ( TEXT("COEditorViewportLODCommands"),`
- L28 _public member_ `TSharedPtr< FUICommandInfo > LODAuto;` — LOD Auto
- L31 _public member_ `TSharedPtr< FUICommandInfo > LOD0;` — LOD 0
- L34 _public member_ `TSharedPtr< FUICommandInfo > TranslateMode;` — Translate mode
- L37 _public member_ `TSharedPtr< FUICommandInfo > RotateMode;` — Rotate mode
- L40 _public member_ `TSharedPtr< FUICommandInfo > ScaleMode;` — Scale mode
- L43 _public member_ `TSharedPtr< FUICommandInfo > RotationGridSnap;` — Enables or disables snapping objects to a rotation grid
- L46 _public member_ `TSharedPtr< FUICommandInfo > HighResScreenshot;` — Opens the control panel for high resolution screenshots
- L49 _public member_ `TSharedPtr< FUICommandInfo > OrbitalCamera;` — Sets the camera mode to orbital camera
- L52 _public member_ `TSharedPtr< FUICommandInfo > FreeCamera;` — Sets the camera mode to free camera
- L55 _public member_ `TSharedPtr< FUICommandInfo > ShowBones;` — Shows/Hide the bones of the skeletal mesh
- L59 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorViewportLights.h` (Private)


#### struct `FViewportLightData`  
`struct FViewportLightData`  
_L7-38_
- reflection: `USTRUCT()`
- L12 _public member_ `bool bIsSpotLight = false;` — `UPROPERTY()`
- L15 _public member_ `FTransform Transform;` — `UPROPERTY()`
- L18 _public member_ `float Intensity = 0.0f;` — `UPROPERTY()`
- L21 _public member_ `FLinearColor Color = FLinearColor(EForceInit::ForceInit);` — `UPROPERTY()`
- L24 _public member_ `float AttenuationRadius = 0.0f;` — `UPROPERTY()`
- L27 _public member_ `float SourceRadius = 0.0f;` — `UPROPERTY()`
- L30 _public member_ `float SourceLength = 0.0f;` — `UPROPERTY()`
- L33 _public member_ `float InnerConeAngle = 0.0f;` — `UPROPERTY()`
- L36 _public member_ `float OuterConeAngle = 0.0f;` — `UPROPERTY()`

#### class `UCustomizableObjectEditorViewportLights`  
`class UCustomizableObjectEditorViewportLights : public UObject`  
_L41-49_
- reflection: `UCLASS()`
- inherits: `UObject`
- L48 _public member_ `TArray<FViewportLightData> LightsData;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorViewportMenuCommands.h` (Private)


#### class `FCustomizableObjectEditorViewportMenuCommands`  
`class FCustomizableObjectEditorViewportMenuCommands : public TCommands<FCustomizableObjectEditorViewportMenuCommands>`  
_L13-50_
- inherits: `TCommands<FCustomizableObjectEditorViewportMenuCommands>`
- desc: Class containing commands for viewport menu actions
- L16 _public function_ `FCustomizableObjectEditorViewportMenuCommands() : TCommands<FCustomizableObjectEditorViewportMenuCommands> ( TEXT("CustomizableObjectEditorViewportMenu"),`
- L34 _public member_ `TSharedPtr< FUICommandInfo > SetCPUSkinning;` — Show vertex normals
- L37 _public member_ `TSharedPtr< FUICommandInfo > SetShowNormals;` — Show vertex normals
- L40 _public member_ `TSharedPtr< FUICommandInfo > SetShowTangents;` — Show vertex tangents
- L43 _public member_ `TSharedPtr< FUICommandInfo > SetShowBinormals;` — Show vertex binormals
- L46 _public member_ `TSharedPtr< FUICommandInfo > AnimSetDrawUVs;` — Draw UV mapping to viewport
- L49 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditor_Deprecated.h` (Private)


#### struct `FCustomizableObjectNodeMaterialImage`  
`struct FCustomizableObjectNodeMaterialImage`  
_L18-36_
- reflection: `USTRUCT()`
- desc: UCONodeSkeletalMeshSection Deprecated, do not use!
- L23 _public member_ `FString Name;` — `UPROPERTY()`
- L26 _public member_ `int32 UVLayout = 0;` — `UPROPERTY()`
- L29 _public member_ `TObjectPtr<UTexture2D> ReferenceTexture = nullptr;` — `UPROPERTY()`
- L32 _public member_ `int32 LayerIndex = 0;` — `UPROPERTY()`
- L35 _public member_ `FString PinName;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeMaterialVector`  
`struct FCustomizableObjectNodeMaterialVector`  
_L40-52_
- reflection: `USTRUCT()`
- desc: Deprecated, do not use!
- L45 _public member_ `FString Name;` — `UPROPERTY()`
- L48 _public member_ `int32 LayerIndex = 0;` — `UPROPERTY()`
- L51 _public member_ `FString PinName;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeMaterialScalar`  
`struct FCustomizableObjectNodeMaterialScalar`  
_L56-68_
- reflection: `USTRUCT()`
- desc: Deprecated, do not use!
- L61 _public member_ `FString Name;` — `UPROPERTY()`
- L64 _public member_ `int32 LayerIndex = 0;` — `UPROPERTY()`
- L67 _public member_ `FString PinName;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeEditMaterialImage`  
`struct FCustomizableObjectNodeEditMaterialImage`  
_L76-82_
- reflection: `USTRUCT()`
- desc: UCONodeModifierEditSkeletalMeshSection Deprecated, do not use!
- L81 _public member_ `FString Name;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeExtendMaterialImage`  
`struct FCustomizableObjectNodeExtendMaterialImage`  
_L87-93_
- reflection: `USTRUCT()`
- desc: UCONodeModifierExtendSkeletalMeshSection Deprecated, do not use!
- L92 _public member_ `FString Name;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeSkeletalMeshMaterial`  
`struct FCustomizableObjectNodeSkeletalMeshMaterial`  
_L98-122_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectNodeSkeletalMesh Deprecated, do not use!
- L103 _public member_ `FString Name;` — `UPROPERTY()`
- L106 _public member_ `TObjectPtr<UEdGraphPin_Deprecated> MeshPin_DEPRECATED;` — `UPROPERTY()`
- L109 _public member_ `TArray<TObjectPtr<UEdGraphPin_Deprecated>> LayoutPins_DEPRECATED;` — `UPROPERTY()`
- L112 _public member_ `TArray<TObjectPtr<UEdGraphPin_Deprecated>> ImagePins_DEPRECATED;` — `UPROPERTY()`
- L115 _public member_ `FEdGraphPinReference MeshPinRef;` — `UPROPERTY()`
- L118 _public member_ `TArray<FEdGraphPinReference> LayoutPinsRef;` — `UPROPERTY()`
- L121 _public member_ `TArray<FEdGraphPinReference> ImagePinsRef;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeSkeletalMeshLOD`  
`struct FCustomizableObjectNodeSkeletalMeshLOD`  
_L126-132_
- reflection: `USTRUCT()`
- desc: Deprecated, do not use!
- L131 _public member_ `TArray<FCustomizableObjectNodeSkeletalMeshMaterial> Materials;` — `UPROPERTY()`

#### struct `FCustomizableObjectColorVariation`  
`struct FCustomizableObjectColorVariation`  
_L137-143_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectNodeColorVariation Deprecated, do not use!
- L142 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### struct `FCustomizableObjectFloatVariation`  
`struct FCustomizableObjectFloatVariation`  
_L148-154_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectFloatVariation Deprecated, do not use!
- L153 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### struct `FCustomizableObjectMaterialVariation`  
`struct FCustomizableObjectMaterialVariation`  
_L159-165_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectMaterialVariation Deprecated, do not use!
- L164 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### struct `FCustomizableObjectMeshVariation`  
`struct FCustomizableObjectMeshVariation`  
_L170-176_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectMeshVariation Deprecated, do not use!
- L175 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### struct `FComponentSettings`  
`struct FComponentSettings`  
_L182-188_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectNodeObject Deprecated, do not use!
- L187 _public member_ `FString ComponentName;` — `UPROPERTY()`

#### struct `FCustomizableObjectTextureVariation`  
`struct FCustomizableObjectTextureVariation`  
_L194-200_
- reflection: `USTRUCT()`
- desc: UCustomizableObjectNodeTextureVariation Deprecated, do not use!
- L199 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### Free symbols / members of external scopes

- L71 _variable_ `constexpr int32 UV_LAYOUT_DEFAULT = -2;` — Deprecated, do not use!

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectGraph.h` (Private)


#### class `UCustomizableObjectGraph`  
`class UCustomizableObjectGraph : public UEdGraph`  
_L14-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L19 _public prototype_ `UCustomizableObjectGraph();`
- L22 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L23 _public prototype_ `void PostRename(UObject * OldOuter, const FName OldName) override;`
- L25 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L28 _public prototype_ `void NotifyNodeIdChanged(const FGuid& OldGuid, const FGuid& NewGuid);` — Own Interface
- L30 _public prototype_ `FGuid RequestNotificationForNodeIdChange(const FGuid& OldGuid, const FGuid& NodeToNotifyGuid);`
- L32 _public prototype_ `void PostDuplicate(bool bDuplicateForPIE) override;`
- L35 _public prototype_ `void AddEssentialGraphNodes();` — Adds the necessary nodes for a CO to work
- L37 _public prototype_ `void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion);`
- L39 _public prototype_ `void PostBackwardsCompatibleFixup();`
- L41 _public prototype_ `bool IsMacro() const;`
- L46 _private member_ `TMap<FGuid, TSet<FGuid>> NodesToNotifyMap;` — Request Node Id Update Map
- L49 _private member_ `TMap<FGuid, FGuid> NotifiedNodeIdsMap;` — Guid map with the key beeing the old Guid and the Value the new one, filled after duplicating COs

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectIdentifierCustomization.h` (Private)


#### class `FCustomizableObjectIdentifierCustomization`  
`class FCustomizableObjectIdentifierCustomization : public IPropertyTypeCustomization`  
_L10-25_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _private member_ `TSharedPtr<IPropertyHandle> GuidUPropertyHandle;`
- L21 _private member_ `class UCustomizableObject* SelectedCustomizableObject = nullptr;`
- L23 _private prototype_ `FString OnGetObjectPath() const;`
- L24 _private prototype_ `void OnEventChanged(const FAssetData& InAssetData);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectInstanceBaker.h` (Private)


#### class `UCustomizableObjectInstanceBaker`  
`class UCustomizableObjectInstanceBaker : public UObject`  
_L35-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Utility class designed to allow tbe baking of the resources of a target Mutable Customizable Object instance onto disk. The actual baking operation does require some work done before the baking itself. - Compilation of the instance's Customizable Object : The mutable CO should be compiled to allow for the update of the instance. - Updating of the instance (async) : The mutable COInstance gets updated prior to the bake to make sure the instance resources to bake are the latest - Baking of the instance resources (sync) : The resources of the instance get baked onto disk. Once the whole operation gets completed a callback gets executed (OnBakeOperationCompletedCallback) that will provide the caller with the bake operation result (true for success and false for failure) and a list of asset paths that got saved onto disk. Since the update of the instance for baking requires of some static changes in the instance updating system so the parallel update of instances for baking is not allowed. This prohibition is enforced by the update methods that we call prior to the baking operation. No more than one update for baking can be run at the same time.
- L46 _public prototype_ `void BakeInstance(UCustomizableObjectInstance* InTargetInstance, const FBakingConfiguration& InBakingConfig, const TSharedPtr<const FOnBakerFinishedWork> InOnBakerFinishedWork = nullptr);` — Execute this method in order to bake the provided instance. It will schedule a special type of instance update before proceeding with the bake itself. @param InTargetInstance The instance we want to bake @param InBakingConfig Configuration structure that determines how the baking is going to be made @param InOnBakerFinishedWork Delegate used to determine if the baker has completed its operation. Does not provide any other data than that so we can perform some post-bake actions.
- L54 _private prototype_ `void OnCompilationEnd(const FCompileCallbackParams& InCompileCallbackParams);` — Callback executed once the compilation of the CO has finished. @param InCompileCallbackParams The compilation parameters that the compilation callback invocation provides to the caller.
- L59 _private prototype_ `void UpdateInstance();` — Takes care of updating and generating the instance resources so we can later bake them.
- L65 _private prototype_ `void OnInstanceUpdated(const FUpdateContext& Result) const;` — Callback executed when the instance finishes its update. It does not matter if it is successful or not @param Result The result returned by the instance updating operation once the operation is completed.
- L71 _private prototype_ `void Bake() const;` — Actual baking method. It will take care of baking the already updated instance and saving it's resources to disk. It will also log the paths to the generated packages.
- L79 _private prototype_ `void FinishBakingOperation(const bool bBakeWasSuccessful, TArray<FBakedResourceData>* InSavedPackagesData) const;` — Closes the baking operation by reporting the assets saved ans also , if bound, running the callback that reports that the baker has completed all the work that had to be done. @param bBakeWasSuccessful Was the baking operation successful or not? @param InSavedPackagesData Data from the baked packages. Can be null if no package was saved.
- L84 _private member_ `FBakingConfiguration Configuration;` — Cached configuration provided by the user
- L90 _private member_ `TObjectPtr<UCustomizableObjectInstance> InstanceToBake;` — `UPROPERTY()` — The instance we want to update and then bake
- L96 _private member_ `TSharedPtr<const FOnBakerFinishedWork> OnWorkFinished;` — Optional delegate used to report when the baker has completed it's work (and it is not running or making other systems run) It will be called after we have given the end user the data about the success state of the baking and also the resources saved.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L17 _delegate_ `DECLARE_DELEGATE(FOnBakerFinishedWork);`
- L17 _prototype_ `DECLARE_DELEGATE(FOnBakerFinishedWork);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectInstanceEditor.h` (Private)


#### class `UUpdateClassWrapperClass`  
`class UUpdateClassWrapperClass : public UObject`  
_L39-49_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Wrapper UObject class for the UCustomizableObjectInstance::FObjectInstanceUpdatedDelegate dynamic multicast delegate
- L46 _public prototype_ `void DelegatedCallback(UCustomizableObjectInstance* Instance);` — `UFUNCTION()` — Method to assign for the callback
- L48 _public member_ `FCreatePreviewInstanceFlagDelegate Delegate;`

#### class `UProjectorParameter`  
`class UProjectorParameter : public UObject`  
_L56-103_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Currently selected projector parameter and its position. Only used by Instance Parameters. Default values projector values modify the node directly.
- L61 _public prototype_ `UProjectorParameter();`
- L63 _public prototype_ `void SelectProjector(const FString& ParamName, int32 RangeIndex = -1);`
- L65 _public prototype_ `void UnselectProjector();`
- L67 _public prototype_ `bool IsProjectorSelected(const FString& InParamName, int32 InRangeIndex = -1) const;`
- L69 _public prototype_ `FVector GetPosition() const;`
- L71 _public prototype_ `void SetPosition(const FVector& Position);`
- L73 _public prototype_ `FVector GetDirection() const;`
- L75 _public prototype_ `void SetDirection(const FVector& Direction);`
- L77 _public prototype_ `FVector GetUp() const;`
- L79 _public prototype_ `void SetUp(const FVector& Up);`
- L81 _public prototype_ `FVector GetScale() const;`
- L83 _public prototype_ `void SetScale(const FVector& Scale);`
- L87 _private member_ `FString ParamName = {};` — `UPROPERTY()`
- L90 _private member_ `int32 RangeIndex = -1;` — `UPROPERTY()`
- L93 _private member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY()`
- L96 _private member_ `FVector Direction = FVector::ForwardVector;` — `UPROPERTY()`
- L99 _private member_ `FVector Up = FVector::UpVector;` — `UPROPERTY()`
- L102 _private member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY()`

#### class `UCustomSettings`  
`class UCustomSettings : public UObject`  
_L107-138_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L113 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L115 _public prototype_ `ULightComponent* GetSelectedLight() const;`
- L117 _public prototype_ `void SetSelectedLight(ULightComponent* Light);`
- L119 _public prototype_ `UCustomizableObjectEditorViewportLights* GetLightsPreset() const;`
- L121 _public prototype_ `void SetLightsPreset(UCustomizableObjectEditorViewportLights& LightsPreset);`
- L123 _public prototype_ `TWeakPtr<ICustomizableObjectInstanceEditor> GetEditor() const;`
- L125 _public prototype_ `void SetEditor(TSharedPtr<ICustomizableObjectInstanceEditor> Editor);`
- L128 _public member_ `TObjectPtr<UAnimationAsset> Animation;` — `UPROPERTY(Category = Animation, EditAnywhere)`
- L132 _private member_ `TObjectPtr<ULightComponent> SelectedLight = nullptr;` — `UPROPERTY()`
- L135 _private member_ `TObjectPtr<UCustomizableObjectEditorViewportLights> LightsPreset;` — `UPROPERTY()`
- L137 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> WeakEditor;`

#### struct `FCustomizableObjectGameplayTagsFilter`  
`struct FCustomizableObjectGameplayTagsFilter`  
_L141-153_
- reflection: `USTRUCT()`
- L148 _public member_ `FGameplayTagContainer GameplayTagsFilter;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "Tags"), Category = NoCategory)` — Filter Gameplay tags to match with.
- L152 _public member_ `EGameplayContainerMatchType GameplayTagsFilterType = EGameplayContainerMatchType::Any;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "Match type"), Category = NoCategory)` — Filter match type.

#### class `UCustomizableObjectEditorProperties`  
`class UCustomizableObjectEditorProperties : public UObject`  
_L156-167_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L166 _public member_ `FCustomizableObjectGameplayTagsFilter Filter;` — `UPROPERTY(meta = (DisplayName = "Gameplay Tags Filter"))` — Gameplay tags based parameter options filter. Tags may be added to the Editor Gameplay Tags container in the parameters metadata. Only applies to the options shown in drop downs. Child object parameters and data table rows.

#### class `FCustomizableObjectInstanceEditor`  
`class FCustomizableObjectInstanceEditor : public ICustomizableObjectInstanceEditor, public FAssetEditorToolkit, public FGCObject, public FTickableEditorObject`  
_L173-350_
- inherits: `ICustomizableObjectInstanceEditor,FAssetEditorToolkit,FGCObject,FTickableEditorObject`
- desc: CustomizableObject Editor class
- L180 _public prototype_ `FCustomizableObjectInstanceEditor();`
- L183 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L184 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L193 _public prototype_ `void InitCustomizableObjectInstanceEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCustomizableObjectInstance* ObjectToEdit );` — Edits the specified object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The object to edit
- L196 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FSerializableObject interface
- L197 _public function_ `virtual FString GetReferencerName() const override`
- L204 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L205 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L206 _public prototype_ `virtual FText GetToolkitName() const override;`
- L207 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L208 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L211 _public prototype_ `virtual FEditorModeTools* GetEditorModeTools() override;` — ICustomizableObjectInstanceEditor interface
- L212 _public prototype_ `virtual UCustomizableObjectInstance* GetPreviewInstance() override;`
- L213 _public prototype_ `virtual void RefreshTool() override;`
- L214 _public prototype_ `virtual TSharedPtr<SCustomizableObjectEditorViewportTabBody> GetViewport() override;`
- L215 _public prototype_ `virtual UProjectorParameter* GetProjectorParameter() override;`
- L216 _public prototype_ `virtual UCustomSettings* GetCustomSettings() override;`
- L217 _public prototype_ `virtual void HideGizmo() override;`
- L218 _public prototype_ `virtual void ShowGizmoProjectorParameter(const FString& ParamName, int32 RangeIndex) override;`
- L219 _public prototype_ `virtual void HideGizmoProjectorParameter() override;`
- L220 _public prototype_ `virtual UCustomizableObjectEditorProperties* GetEditorProperties() override;`
- L221 _public prototype_ `virtual TSharedPtr<SCustomizableObjectEditorAdvancedPreviewSettings> GetAdvancedPreviewSettings() override;`
- L222 _public prototype_ `virtual bool ShowLightingSettings() override;`
- L223 _public prototype_ `virtual bool ShowProfileManagementOptions() override;`
- L224 _public prototype_ `virtual const UObject* GetObjectBeingEdited() override;`
- L227 _public prototype_ `void OnUpdatePreviewInstance(UCustomizableObjectInstance* Instance);` — Callback to notify the editor when the PreviewInstance has been updated
- L230 _public prototype_ `virtual bool IsTickable(void) const override;` — FTickableGameObject interface
- L231 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L232 _public prototype_ `virtual TStatId GetStatId() const override;`
- L234 _public prototype_ `void OnCustomizableObjectStatusChanged(FCustomizableObjectStatus::EState PreviousState, FCustomizableObjectStatus::EState CurrentState);`
- L238 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L239 _private prototype_ `TSharedRef<SDockTab> SpawnTab_InstanceProperties(const FSpawnTabArgs& Args);`
- L240 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AdvancedPreviewSettings(const FSpawnTabArgs& Args);`
- L241 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TextureAnalyzer(const FSpawnTabArgs& Args);`
- L244 _private prototype_ `void BindCommands();` — Binds commands associated with the Static Mesh Editor.
- L247 _private prototype_ `void OnInstancePropertySelectionChanged(FProperty* InProperty);` — Callback when selection changes in the Property Tree.
- L250 _private prototype_ `void SaveAsset_Execute() override;` — Save Customizable Object Instance open in the editor
- L253 _private prototype_ `bool CanOpenOrShowParent();` — Says if the customizable Object can be shown or be opened in the editor
- L256 _private prototype_ `void ShowParentInContentBrowser();` — Show Customizable Object Instance's Parent In Content Browser
- L259 _private prototype_ `void OpenParentInEditor();` — Open Customizable Object Instance's Parent In Editor
- L262 _private prototype_ `void OpenTextureAnalyzerTab();` — Open the Texture Analyzer tab
- L266 _public prototype_ `static void HideGizmo(const TSharedPtr<ICustomizableObjectInstanceEditor>& Editor, const TSharedPtr<SCustomizableObjectEditorViewportTabBody>& Viewport, const TSharedPtr<IDetailsView>& InstanceDetailsView);` — Static to reuse code with FCustomizableObjectEditor.
- L271 _public prototype_ `static void ShowGizmoProjectorParameter( const FString& ParamName, int32 RangeIndex, const TSharedPtr<ICustomizableObjectInstanceEditor>& Editor, const TSharedPtr<SCustomizableObjectEditorViewportTabBody>& Viewport, const TSharedPtr<IDetailsView>& InstanceDetailsView, UProjectorParameter* ProjectorParameter, UCustomizableObjectInstance* Instance);` — Static to reuse code with FCustomizableObjectEditor.
- L277 _public prototype_ `static void HideGizmoProjectorParameter(const TSharedPtr<ICustomizableObjectInstanceEditor>& Editor, const TSharedPtr<SCustomizableObjectEditorViewportTabBody>& Viewport, const TSharedPtr<IDetailsView>& InstanceDetailsView);` — Static to reuse code with FCustomizableObjectEditor.
- L283 _private prototype_ `void OnPostCompile();`
- L286 _private member_ `TObjectPtr<UCustomizableObjectInstance> CustomizableObjectInstance;` — The currently viewed object.
- L289 _private member_ `TStrongObjectPtr<AActor> Actor;` — Preview Actor. All preview components are attached to this actor.
- L291 _private member_ `TArray<TWeakObjectPtr<UDebugSkelMeshComponent>> PreviewSkeletalMeshComponents;`
- L294 _private member_ `TMap<FName, TWeakPtr<SDockableTab>> SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L297 _private member_ `TSharedPtr<SCustomizableObjectEditorViewportTabBody> Viewport;` — Preview Viewport widget
- L298 _private member_ `TSharedPtr<IDetailsView> CustomizableInstanceDetailsView;`
- L302 _private member_ `TSharedPtr<SLevelOfDetailSettings> LevelOfDetailSettings;` — Level of Details Settings widget.
- L305 _private member_ `TSharedPtr<STextComboBox> UVChannelCombo;` — Widget for displaying the available UV Channels.
- L308 _private member_ `TArray<TSharedPtr<FString>> UVChannels;` — List of available UV Channels.
- L311 _private member_ `TSharedPtr<STextComboBox> LODLevelCombo;` — Widget for displaying the available LOD.
- L314 _private member_ `TArray<TSharedPtr<FString>> LODLevels;` — List of LODs.
- L317 _private member_ `static const FName ViewportTabId;` — The tab ids for all the tabs used
- L318 _private member_ `static const FName InstancePropertiesTabId;`
- L319 _private member_ `static const FName AdvancedPreviewSettingsTabId;`
- L320 _private member_ `static const FName TextureAnalyzerTabId;`
- L323 _private member_ `FDelegateHandle OnObjectModifiedHandle;` — Handle for the OnObjectModified event
- L326 _private member_ `TObjectPtr<UUpdateClassWrapperClass> HelperCallback;` — UObject class to be able to use the update callback
- L329 _private member_ `TSharedPtr<SCustomizableObjectEditorAdvancedPreviewSettings> AdvancedPreviewSettingsWidget;` — Scene preview settings widget
- L332 _private member_ `UPoseAsset* PoseAsset;` — Pose asset when doing drag and drop of an UPoseAsset to the viewport
- L335 _private member_ `TSharedPtr<SCustomizableObjecEditorTextureAnalyzer> TextureAnalyzer;` — Texture Analyzer table widget which shows the information of the transient textures used in the customizable object instance
- L339 _private member_ `bool bOnlyRuntimeParameters;` — Variables used to force the refresh of the details view widget. These are needed because sometimes the scrollbar of the window doesn't appear until we force the refresh
- L340 _private member_ `bool bOnlyRelevantParameters;`
- L342 _private member_ `TObjectPtr<UProjectorParameter> ProjectorParameter = nullptr;`
- L344 _private member_ `TObjectPtr<UCustomSettings> CustomSettings = nullptr;`
- L346 _private member_ `TObjectPtr<UCustomizableObjectEditorProperties> EditorProperties = nullptr;`
- L349 _private prototype_ `void ExtendToolbar();` — Adds the customizable Object Instance Editor commands to the default toolbar

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DELEGATE(FCreatePreviewInstanceFlagDelegate);`
- L32 _prototype_ `DECLARE_DELEGATE(FCreatePreviewInstanceFlagDelegate);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectInstanceEditorActions.h` (Private)


#### class `FCustomizableObjectInstanceEditorCommands`  
`class FCustomizableObjectInstanceEditorCommands : public TCommands<FCustomizableObjectInstanceEditorCommands>`  
_L12-36_
- inherits: `TCommands<FCustomizableObjectInstanceEditorCommands>`
- desc: Unreal StaticMesh editor actions
- L16 _public prototype_ `FCustomizableObjectInstanceEditorCommands();`
- L18 _public member_ `TSharedPtr< FUICommandInfo > SetDrawUVs;`
- L19 _public member_ `TSharedPtr< FUICommandInfo > SetShowGrid;`
- L20 _public member_ `TSharedPtr< FUICommandInfo > SetShowSky;`
- L21 _public member_ `TSharedPtr< FUICommandInfo > SetShowBounds;`
- L22 _public member_ `TSharedPtr< FUICommandInfo > SetShowCollision;`
- L23 _public member_ `TSharedPtr< FUICommandInfo > SetCameraLock;`
- L24 _public member_ `TSharedPtr< FUICommandInfo > SaveThumbnail;`
- L27 _public member_ `TSharedPtr< FUICommandInfo > ShowParentCO;` — Toolbar Commands
- L28 _public member_ `TSharedPtr< FUICommandInfo > EditParentCO;`
- L29 _public member_ `TSharedPtr< FUICommandInfo > TextureAnalyzer;`
- L34 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectLayout.h` (Private)


#### enum `ECustomizableObjectTextureLayoutPackingStrategy`  
`enum class ECustomizableObjectTextureLayoutPackingStrategy : uint8`  
_L13-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `Resizable = 0 UMETA(DisplayName = "Resizable Layout")` — The layout increases its size to fit all the blocks.
- L18 _public enumerator_ `Fixed = 1 UMETA(DisplayName = "Fixed Layout")` — The layout resizes the blocks to keep its size.
- L20 _public enumerator_ `Overlay = 2 UMETA(DisplayName = "Overlay Layout")` — The layout is not modified and blocks are ignored. Extend material nodes just add their layouts on top of the base one.

#### enum `ECustomizableObjectLayoutAutomaticBlocksStrategy`  
`enum class ECustomizableObjectLayoutAutomaticBlocksStrategy : uint8`  
_L26-34_
- reflection: `UENUM()`
- L29 _public enumerator_ `Rectangles = 0 UMETA(DisplayName = "Rectangles")` — Create rectangles on a grid splitting the UV space if possible
- L31 _public enumerator_ `UVIslands = 1 UMETA(DisplayName = "UV Islands")` — Detect UV islands and create blocks for them with masks
- L33 _public enumerator_ `Ignore = 2 UMETA(DisplayName = "Ignore")` — Don't create automatic blocks, and ignore UVs that don't have a manual block already. They get assigned to the first avilable block or ignored if none. This is the legacy behavior.

#### enum `ECustomizableObjectLayoutAutomaticBlocksMergeStrategy`  
`enum class ECustomizableObjectLayoutAutomaticBlocksMergeStrategy : uint8`  
_L39-47_
- reflection: `UENUM()`
- L42 _public enumerator_ `DontMerge = 0 UMETA(DisplayName = "Don't merge")` — Don't merge the blocks
- L44 _public enumerator_ `MergeChildBlocks = 1 UMETA(DisplayName = "Child blocks")` — Merge the block if a block is entirely included in another block

#### enum `ECustomizableObjectLayoutBlockReductionMethod`  
`enum class ECustomizableObjectLayoutBlockReductionMethod : uint8`  
_L52-58_
- reflection: `UENUM()`
- desc: Fixed Layout reduction methods
- L55 _public enumerator_ `Halve = 0 UMETA(DisplayName = "Reduce by Half")` — Layout blocks will be reduced by halves
- L57 _public enumerator_ `Unitary = 1 UMETA(DisplayName = "Reduce by Unit")` — Layout blocks will be reduced by a grid unit

#### struct `FCustomizableObjectLayoutBlock`  
`struct FCustomizableObjectLayoutBlock`  
_L61-105_
- reflection: `USTRUCT()`
- L65 _public function_ `FCustomizableObjectLayoutBlock(FIntPoint InMin = FIntPoint(0, 0), FIntPoint InMax = FIntPoint(1, 1))`
- L77 _public member_ `FIntPoint Min;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Top left coordinate.
- L81 _public member_ `FIntPoint Max;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Bottom right coordinate.
- L85 _public member_ `uint32 Priority;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Priority to be reduced. Only functional in fixed layouts.
- L89 _public member_ `FGuid Id;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — Unique unchangeable id used to reference this block from other nodes.
- L93 _public member_ `bool bReduceBothAxes = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Block will be reduced on both sizes at the same time on each reduction.
- L97 _public member_ `bool bReduceByTwo = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Block will be reduced by two in an Unitary Layout reduction.
- L101 _public member_ `TObjectPtr<class UTexture2D> Mask = nullptr;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Block mask to use to filter the UVs when assigning them to the block.
- L104 _public member_ `bool bIsAutomatic = false;` — Transient flag used in the UI to differentiate between manual and automatic blocks.

#### class `UCustomizableObjectLayout`  
`class UCustomizableObjectLayout : public UObject`  
_L108-197_
- reflection: `UCLASS()`
- inherits: `UObject`
- L114 _public prototype_ `UCustomizableObjectLayout();`
- L117 _public prototype_ `void SetLayout(int32 LODIndex, int32 MatIndex, int32 UVIndex);` — Sets the layout parameters
- L118 _public prototype_ `void SetGridSize(FIntPoint Size);`
- L119 _public prototype_ `void SetMaxGridSize(FIntPoint Size);`
- L120 _public prototype_ `void SetLayoutName(FString Name);`
- L121 _public prototype_ `void SetIgnoreVertexLayoutWarnings(bool bValue);`
- L122 _public prototype_ `void SetIgnoreWarningsLOD(int32 LODValue);`
- L124 _public function_ `int32 GetLOD() const`
- L125 _public function_ `int32 GetMaterial() const`
- L126 _public function_ `int32 GetUVChannel() const`
- L127 _public function_ `FString GetLayoutName() const`
- L128 _public prototype_ `TSoftObjectPtr<UStreamableRenderAsset> GetMesh() const;`
- L129 _public function_ `FIntPoint GetGridSize() const`
- L130 _public function_ `FIntPoint GetMaxGridSize() const`
- L131 _public function_ `bool GetIgnoreVertexLayoutWarnings() const`
- L132 _public function_ `int32 GetFirstLODToIgnoreWarnings() const`
- L134 _public prototype_ `void GetUVs(TArray<FVector2f>& UVs) const;`
- L137 _public prototype_ `int32 FindBlock(const FGuid& InId) const;` — Get a block index in the array from its id.Return - 1 if not found.
- L140 _public prototype_ `void GenerateAutomaticBlocksFromUVs();` — Generate all the transient UV layout automatic blocks with unassigned UVs.
- L143 _public prototype_ `void ConsolidateAutomaticBlocks();` — Convert the transient automatic blocks into real blocks.
- L147 _public member_ `TArray<FCustomizableObjectLayoutBlock> Blocks;` — `UPROPERTY()` — List of blocks manually defined in the layout.
- L151 _public member_ `TArray<FCustomizableObjectLayoutBlock> AutomaticBlocks;` — `UPROPERTY(Transient)` — List of blocks automatically defined (in the layout) for preview.
- L154 _public member_ `TArray< TArray<FVector2f> > UnassignedUVs;` — List of UVs to highlight in the layout because they have issues.
- L157 _public member_ `ECustomizableObjectTextureLayoutPackingStrategy PackingStrategy = ECustomizableObjectTextureLayoutPackingStrategy::Resizable;` — `UPROPERTY()`
- L160 _public member_ `ECustomizableObjectLayoutAutomaticBlocksStrategy AutomaticBlocksStrategy = ECustomizableObjectLayoutAutomaticBlocksStrategy::Rectangles;` — `UPROPERTY()`
- L163 _public member_ `ECustomizableObjectLayoutAutomaticBlocksMergeStrategy AutomaticBlocksMergeStrategy = ECustomizableObjectLayoutAutomaticBlocksMergeStrategy::MergeChildBlocks;` — `UPROPERTY()`
- L166 _public member_ `ECustomizableObjectLayoutBlockReductionMethod BlockReductionMethod = ECustomizableObjectLayoutBlockReductionMethod::Halve;` — `UPROPERTY()`
- L171 _private member_ `int32 LOD;` — `UPROPERTY()`
- L174 _private member_ `int32 Material;` — `UPROPERTY()`
- L177 _private member_ `int32 UVChannel;` — `UPROPERTY()`
- L180 _private member_ `FIntPoint GridSize;` — `UPROPERTY()`
- L184 _private member_ `FIntPoint MaxGridSize;` — `UPROPERTY()` — Maximum grid size the layout can grow to. Used with the fixed layout strategy.
- L187 _private member_ `FString LayoutName;` — `UPROPERTY()`
- L191 _private member_ `bool bIgnoreUnassignedVertexWarning = false;` — `UPROPERTY()` — If true, vertex warning messages will be ignored
- L195 _private member_ `int32 FirstLODToIgnore = 0;` — `UPROPERTY()` — First LOD from which unassigned vertices warning will be ignored

#### Free symbols / members of external scopes

- L23 _prototype_ `UE::Mutable::Private::EPackStrategy ConvertLayoutStrategy(const ECustomizableObjectTextureLayoutPackingStrategy LayoutPackStrategy);`
- L36 _prototype_ `UE::Mutable::Private::EAutoBlocksStrategy ConvertAutomaticBlocksStrategy(const ECustomizableObjectLayoutAutomaticBlocksStrategy LayoutPackStrategy);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/AssetDefinition_CustomizableObjectMacroLibrary.h` (Private)


#### class `UAssetDefinition_CustomizableObjectMacroLibrary`  
`class UAssetDefinition_CustomizableObjectMacroLibrary final : public UAssetDefinitionDefault`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Interface
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L23 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectGraphEditorToolkit.h` (Private)


#### class `FCustomizableObjectGraphEditorToolkit`  
`class FCustomizableObjectGraphEditorToolkit : public FAssetEditorToolkit, public FNotifyHook, public FSelfRegisteringEditorUndoClient`  
_L21-121_
- inherits: `FAssetEditorToolkit,FNotifyHook,FSelfRegisteringEditorUndoClient`
- desc: Public interface to Customizable Object Editor
- L26 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L27 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L32 _public prototype_ `void OnEnterText(const FText& NewText, ETextCommit::Type TextType);` — Searches a node that contains the inserted word
- L39 _public prototype_ `void FindProperty(const FProperty* Property, const void* InContainer, const FString& FindString, const UObject& Context, bool& bFound, UCustomizableObject* Object);` — Recursively find any property that its name or value contains the given string. @param Property Root property. @param Container Root property container (address of the property value). @param FindString String to find for. @param Context UObject Context where this string has been found. @param bFound Mark as true if any property has been found.
- L46 _public prototype_ `void LogSearchResult(const UObject& Context, const FString& Type, bool& bIsFirst, const FString& Result, UCustomizableObject* Object) const;` — Logs the search results of the search @param Context The UObject we have found to be related with the searched string. @param Type The type of relation with the searched word. It is a node, a value or maybe a variable? @param bIsFirst Is this the first time we encountered something during our search? @param Result The string containing the search word we are looking for in Node
- L49 _public prototype_ `void BindGraphCommands();` — Bind common graph commands
- L52 _public prototype_ `void SelectNode(const UEdGraphNode* Node);` — Graph Node Actions --------------------------
- L55 _public prototype_ `void SelectSingleNode(UCustomizableObjectNode& Node);` — Select only and this node only. Do nothing if already was only selected.
- L57 _public prototype_ `void DeleteSelectedNodes();`
- L58 _public prototype_ `bool CanDeleteNodes() const;`
- L60 _public prototype_ `void DuplicateSelectedNodes();`
- L61 _public prototype_ `bool CanDuplicateSelectedNodes() const;`
- L70 _public prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when a node's title is committed for a rename @param	NewText				New title text @param	CommitInfo			How text was committed @param	NodeBeingChanged	The node being changed
- L72 _public prototype_ `void CopySelectedNodes();`
- L73 _public prototype_ `bool CanCopyNodes() const;`
- L75 _public prototype_ `void PasteNodes();`
- L76 _public prototype_ `void PasteNodesHere(const FVector2D& Location);`
- L77 _public prototype_ `bool CanPasteNodes() const;`
- L79 _public prototype_ `void CutSelectedNodes();`
- L80 _public prototype_ `bool CanCutNodes() const;`
- L82 _public prototype_ `void OnRenameNode();`
- L83 _public prototype_ `bool CanRenameNodes() const;`
- L85 _public prototype_ `void CreateCommentBoxFromKey();`
- L86 _public prototype_ `UEdGraphNode* CreateCommentBox(const FVector2D& NodePos);`
- L88 _public prototype_ `void OnNodeDoubleClicked(UEdGraphNode* Node);`
- L91 _public prototype_ `void UndoGraphAction();` — Undo/Redo graph Actions
- L92 _public prototype_ `void RedoGraphAction();`
- L100 _public prototype_ `void CreateGraphEditorWidget(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents);` — Creates a new graph editor widget @param InGraph is the graph that will be represented in the graph editor. @param InEvents are custom events occurring in/on the graph.
- L103 _public prototype_ `virtual void OnSelectedGraphNodesChanged(const FGraphPanelSelectionSet& NewSelection) = 0;` — Graph Editor callbacks
- L108 _public prototype_ `virtual void ReconstructAllChildNodes(UCustomizableObjectNode& StartNode, const UClass& NodeType) = 0;` — Reconstructs all child the nodes that match the given type. @param StartNode Root node to start the graph traversal. This one also will be reconstructed. @param NodeType Node types to reconstruct.
- L110 _public prototype_ `virtual void UpdateGraphNodeProperties();`
- L115 _public member_ `TSharedPtr<SGraphEditor> GraphEditor;` — Pointer to the graph editor widget
- L120 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for the graph editor

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroDetails.h` (Private)


#### struct `FPinNameRowData`  
`struct FPinNameRowData`  
_L20-24_
- L22 _public member_ `FString PinFriendlyName;`
- L23 _public member_ `FName PinCategory;`

#### class `SCOMacroPinTypeSelector`  
`class SCOMacroPinTypeSelector : public SCompoundWidget`  
_L27-64_
- inherits: `SCompoundWidget`
- desc: Widget to edit the type of a macro's variable.
- L29 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnVariableRemoved, UCustomizableObjectNodeTunnel*);`
- L31 _private function_ `SLATE_BEGIN_ARGS(SCOMacroPinTypeSelector)`
- L32 _private prototype_ `SLATE_ARGUMENT(TObjectPtr<UCustomizableObjectMacroInputOutput>, Variable) SLATE_ARGUMENT(TObjectPtr<UCustomizableObjectNodeTunnel>, IONode) SLATE_EVENT(FOnVariableRemoved, OnVariableRemoved) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _private prototype_ `TSharedRef<SWidget> OnGenerateRow(TSharedPtr<FPinNameRowData> Option);` — Generates the widget of a List view row.
- L43 _private prototype_ `TSharedRef<SWidget> GenerateSelectedContent() const;` — Returns the name of the pin type of the variable.
- L46 _private prototype_ `void OnRemoveClicked();` — Callback of the remove variable button.
- L51 _private member_ `TObjectPtr<UCustomizableObjectMacroInputOutput> Variable;` — Pointer to the variablethas is being edited
- L54 _private member_ `TObjectPtr<UCustomizableObjectMacro> Macro;` — Pointer to the macro where the variable belongs.
- L57 _private member_ `TObjectPtr<UCustomizableObjectNodeTunnel> IONode;` — Pointer to the node that will expose this variable to the graph.
- L60 _private member_ `TArray<TSharedPtr<FPinNameRowData>> ComboBoxSource;` — Array that contains all the pin types showed in the list view widget.
- L63 _private member_ `FOnVariableRemoved OnVariableRemoved;` — Callback to indicate that a variable has been removed

#### class `FCustomizableObjectMacroDetails`  
`class FCustomizableObjectMacroDetails : public IDetailCustomization`  
_L68-107_
- inherits: `IDetailCustomization`
- desc: Details View of UCustomizableObjectMacros
- L72 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L76 _public function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override` — Do not use. Add details customization in the other CustomizeDetails signature.
- L77 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L82 _private prototype_ `void GenerateVariableList(IDetailCategoryBuilder& InputsCategory, UCustomizableObjectNodeTunnel* IONode, ECOMacroIOType VariableType);` — Creates a widget list to create and visualize macro variables.
- L85 _private prototype_ `TSharedRef<SWidget> GenerateCategoryButtonWidget(ECOMacroIOType VariableType, UCustomizableObjectNodeTunnel* IONode);` — Creates the button that allows to add new macro variables.
- L88 _private prototype_ `FText GetVariableName(UCustomizableObjectMacroInputOutput* Variable) const;` — Returns the name of the specified variable. Needed to update automatically the text if the name of the variable changes.
- L91 _private prototype_ `void OnVariableNameChanged(const FText& InNewText, UCustomizableObjectMacroInputOutput* Variable);` — Editable Text Box Callbacks
- L92 _private prototype_ `void OnVariableNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit, UCustomizableObjectMacroInputOutput* Variable, UCustomizableObjectNodeTunnel* IONode);`
- L95 _private prototype_ `void OnRemoveVariable(UCustomizableObjectNodeTunnel* IONode);` — Callback to comunicate the editor that the name of a variable has changes. Updates the variable List too.
- L98 _private prototype_ `FReply AddNewVariable(ECOMacroIOType VarType, UCustomizableObjectNodeTunnel* IONode);` — Adds a new variable to a Macro.
- L103 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilderPtr;` — Details builder pointer
- L106 _private member_ `TObjectPtr<UCustomizableObjectMacro> Macro;` — Pointer to the macro thas is being edited

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVariableRemoved, UCustomizableObjectNodeTunnel*);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroLibrary.h` (Private)


#### enum `ECOMacroIOType`  
`enum class ECOMacroIOType : uint8`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `COMVT_Input`
- L19 _public enumerator_ `COMVT_Output`

#### class `UCustomizableObjectMacroInputOutput`  
`class UCustomizableObjectMacroInputOutput : public UObject`  
_L23-44_
- reflection: `UCLASS()`
- inherits: `UObject`
- L31 _public member_ `FName Name;` — `UPROPERTY()` — Name of the variable and pin that represents it.
- L35 _public member_ `ECOMacroIOType Type = ECOMacroIOType::COMVT_Input;` — `UPROPERTY()` — Whether it is an input or output variable.
- L39 _public member_ `FName PinCategoryType;` — `UPROPERTY()` — Type of the variable and pin.
- L43 _public member_ `FGuid UniqueId;` — `UPROPERTY()` — Unique id that identifies this variable. Usefull for pin reconstruction and name repetitions.

#### class `UCustomizableObjectMacro`  
`class UCustomizableObjectMacro : public UObject`  
_L47-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L54 _public prototype_ `UCustomizableObjectMacroInputOutput* AddVariable(ECOMacroIOType VarType);` — Adds a new variable to the specified Macro.
- L57 _public prototype_ `void RemoveVariable(UCustomizableObjectMacroInputOutput* Variable);` — Removes a variable from the specified Macro.
- L60 _public prototype_ `UCustomizableObjectNodeTunnel* GetIONode(ECOMacroIOType Type) const;` — Returns the input or output node
- L66 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = Macro)` — Name of the Macro.
- L70 _public member_ `FString Description = "Ma` — `UPROPERTY(EditAnywhere, Category = Macro)` — Description of what this macro does.
- L74 _public member_ `TArray<TObjectPtr<UCustomizableObjectMacroInputOutput>> InputOutputs;` — `UPROPERTY()` — Container of all input and output variables of this Macro.
- L78 _public member_ `TObjectPtr<UEdGraph> Graph;` — `UPROPERTY()` — Graph of the Macro.

#### class `UCustomizableObjectMacroLibrary`  
`class UCustomizableObjectMacroLibrary : public UObject`  
_L85-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: A Macro Library is an asset that stores reusable mutable graphs.
- L91 _public function_ `UCustomizableObjectMacroLibrary()`
- L94 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L95 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L98 _public prototype_ `UCustomizableObjectMacro* AddMacro();` — Creates a new macro with the basic nodes and adds it to the library.
- L101 _public prototype_ `void RemoveMacro(UCustomizableObjectMacro* MacroToRemove);` — Removes the specified macro from the library.
- L107 _public member_ `TArray<TObjectPtr<UCustomizableObjectMacro>> Macros;` — `UPROPERTY()` — List of macros.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroLibraryEditor.h` (Private)


#### class `FCustomizableObjectMacroLibraryEditor`  
`class FCustomizableObjectMacroLibraryEditor : public FCustomizableObjectGraphEditorToolkit`  
_L13-81_
- inherits: `FCustomizableObjectGraphEditorToolkit`
- desc: Macro Library Editor.
- L17 _public prototype_ `void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);`
- L20 _public prototype_ `virtual ~FCustomizableObjectMacroLibraryEditor() = default;` — Destructor
- L23 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — IToolkit interface
- L24 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L25 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L26 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L27 _public prototype_ `virtual FText GetToolkitName() const override;`
- L28 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L29 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L32 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L33 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L38 _public prototype_ `void SetSelectedMacro(UCustomizableObjectMacro* NewSelection, bool bRefreshMacroSelection = false);` — Sets which macro is edited in the editor. @param NewSelection pointer to the new macro to select @param bRefreshMacroSelection force to refresh the selection of the Macros List. This is only needed if the selection is done by code and not by the user.
- L43 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);` — Tab Spawners
- L44 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MacroSelector(const FSpawnTabArgs& Args);`
- L45 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Graph(const FSpawnTabArgs& Args);`
- L49 _private prototype_ `virtual void OnSelectedGraphNodesChanged(const FGraphPanelSelectionSet& NewSelection) override;` — Graph Editor callbacks
- L50 _private prototype_ `virtual void ReconstructAllChildNodes(UCustomizableObjectNode& StartNode, const UClass& NodeType) override;`
- L53 _private prototype_ `void OnAddMacroButtonClicked();` — Macro List View callbacks
- L54 _private prototype_ `void OnRemoveMacroButtonClicked(UCustomizableObjectMacro* NewSelection);`
- L55 _private prototype_ `void OnMacroSelectionChanged(UCustomizableObjectMacro* NewSelection);`
- L60 _public member_ `static const FName DetailsTabId;` — Tab Ids
- L61 _public member_ `static const FName MacroSelectorTabId;`
- L62 _public member_ `static const FName GraphTabId;`
- L67 _private member_ `TObjectPtr<UCustomizableObjectMacroLibrary> MacroLibrary = nullptr;` — Macro Library being edited
- L70 _private member_ `TObjectPtr<UCustomizableObjectMacro> SelectedMacro;` — The currently viewed Macro Graph.
- L73 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Details view
- L76 _private member_ `TSharedPtr<SCustomizableObjectMacroLibraryList> MacroSelector;` — Macro List View widget
- L79 _private member_ `TSharedPtr<SDockTab> GraphTab;` — Pointer to the tab that contains the graph editor. Needed to refresh its content.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroLibraryEditorActions.h` (Private)
_(no declarations extracted)_

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroLibraryFactory.h` (Private)


#### class `UCustomizableObjectMacroLibraryFactory`  
`class UCustomizableObjectMacroLibraryFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UCustomizableObjectMacroLibraryFactory();`
- L19 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L20 _public prototype_ `virtual bool CanCreateNew() const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectNodeObjectGroupDetails.h` (Private)


#### class `FCustomizableObjectNodeObjectGroupDetails`  
`class FCustomizableObjectNodeObjectGroupDetails : public FCustomizableObjectNodeDetails`  
_L14-48_
- inherits: `FCustomizableObjectNodeDetails`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L24 _public prototype_ `void GenerateChildrenObjectNames();` — Fills the name options array
- L27 _public prototype_ `void OnSetDefaultValue(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Sets the selected default value
- L30 _public prototype_ `EVisibility DefaultValueSelectorVisibility() const;` — Determines the visibility of the default value selector
- L32 _public prototype_ `FText DefaultValueComboBoxTooltip() const;`
- L37 _private member_ `UCustomizableObjectNodeObjectGroup* NodeGroup = nullptr;` — Pointer to the original group node
- L40 _private member_ `TSharedPtr<STextComboBox> DefaultValueSelector;` — Combobox to select the defaul value of the node group
- L43 _private member_ `TArray< TSharedPtr<FString> > ChildrenNameOptions;` — Combobox options
- L46 _private member_ `TSharedPtr<FString> InitialNameOption;` — Initially selected option

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectPin.h` (Private)


#### Free symbols / members of external scopes

- L9 _prototype_ `bool IsPinOrphan(const UEdGraphPin &Pin);` — Returns true if the pin is orphan.
- L13 _prototype_ `void OrphanPin(UEdGraphPin& Pin);` — Allows to perform work when orphaning a pin.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectPreviewScene.h` (Private)


#### class `FCustomizableObjectPreviewScene`  
`class FCustomizableObjectPreviewScene : public FAdvancedPreviewScene`  
_L9-20_
- inherits: `FAdvancedPreviewScene`
- L13 _public prototype_ `FCustomizableObjectPreviewScene(ConstructionValues CVS, float InFloorOffset = 0.0f);` — Parameter constructor
- L16 _public prototype_ `virtual ~FCustomizableObjectPreviewScene();` — Destructor
- L19 _public prototype_ `UStaticMeshComponent* GetSkyComponent();` — Getter of SkyComponent

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectProjectSettings.h` (Private)


#### class `UCustomizableObjectProjectSettings`  
`class UCustomizableObjectProjectSettings : public UObject`  
_L10-15_
- reflection: `UCLASS(config = Mutable, defaultconfig)`
- inherits: `UObject`
- desc: COE Module, Project Settings.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectSchemaActions.h` (Private)


#### struct `FCustomizableObjectSchemaAction_NewNode`  
`struct FCustomizableObjectSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L15-52_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L21 _public member_ `TObjectPtr<class UEdGraphNode> NodeTemplate;` — `UPROPERTY()` — Template of node we want to create
- L24 _public function_ `FCustomizableObjectSchemaAction_NewNode() : FEdGraphSchemaAction() , NodeTemplate(NULL)`
- L29 _public function_ `FCustomizableObjectSchemaAction_NewNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping, const FText& InKeywords = FText(), int32 InSectionID = 0) : FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InKeywords, InSectionID) , NodeTemplate(NULL)`
- L36 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L37 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L38 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L41 _public prototype_ `static UEdGraphNode* CreateNode(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, class UEdGraphNode* InNodeTemplate);` — Reimplementaiton of EdGraphSchema::CreateNode(...). Performs the overlap calculation before calling AutowireNewNode(...). AutowireNewNode can induce a call to a ReconstrucNode() which removes pins required for the calculation.
- L45 _public function_ `template <typename NodeType> static NodeType* InstantSpawn(class UEdGraph* ParentGraph, NodeType* InTemplateNode, const UE::Slate::FDeprecateVector2DParameter& Location)`

#### struct `FCustomizableObjectSchemaAction_Paste`  
`struct FCustomizableObjectSchemaAction_Paste : public FEdGraphSchemaAction`  
_L57-77_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to paste clipboard contents into the graph
- L62 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L63 _public function_ `virtual FName GetTypeId() const override`
- L65 _public function_ `FCustomizableObjectSchemaAction_Paste() : FEdGraphSchemaAction()`
- L69 _public function_ `FCustomizableObjectSchemaAction_Paste(const FText& InNodeCategory, const FText& InMenuDesc, const FString& InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(InNodeCategory, InMenuDesc, FText::FromString(InToolTip), InGrouping)`
- L75 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/FMutableViewportClient.h` (Private)


#### class `FMutableMeshViewportClient`  
`class FMutableMeshViewportClient : public FEditorViewportClient`  
_L12-16_
- inherits: `FEditorViewportClient`
- desc: Super simple viewport client designed to work SMutableMeshViewport
- L15 _public prototype_ `FMutableMeshViewportClient(const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSource.h` (Private)


#### struct `FGeneratedImageProperties`  
`struct FGeneratedImageProperties`  
_L76-111_
- L79 _public member_ `FString TextureParameterName;` — Name in the Material.
- L82 _public member_ `int32 ImagePropertiesIndex = INDEX_NONE;` — Name in the UE::Mutable::Private::Surface.
- L84 _public member_ `TEnumAsByte<TextureCompressionSettings> CompressionSettings = TC_Default;`
- L86 _public member_ `TEnumAsByte<TextureFilter> Filter = TF_Bilinear;`
- L88 _public member_ `uint32 SRGB = 0;`
- L90 _public member_ `uint32 bFlipGreenChannel = 0;`
- L92 _public member_ `int32 LODBias = 0;`
- L94 _public member_ `TEnumAsByte<TextureMipGenSettings> MipGenSettings = TMGS_SimpleAverage;`
- L96 _public member_ `int32 MaxTextureSize = 0;`
- L98 _public member_ `TEnumAsByte<TextureGroup> LODGroup = TEnumAsByte<TextureGroup>(TMGS_FromTextureGroup);`
- L100 _public member_ `TEnumAsByte<TextureAddress> AddressX = TA_Clamp;`
- L101 _public member_ `TEnumAsByte<TextureAddress> AddressY = TA_Clamp;`
- L103 _public member_ `bool bIsPassThrough = false;`
- L106 _public member_ `int32 TextureSize = 0;` — ReferenceTexture source size.
- L109 _public member_ `int32 BaseLODBias = 0;` — TODO: Remove base LODBias added to root.

#### struct `FLayoutGenerationFlags`  
`struct FLayoutGenerationFlags`  
_L113-119_
- L115 _public prototype_ `bool operator==(const FLayoutGenerationFlags& Other) const = default;`
- L118 _public member_ `TArray<EPinMode> TexturePinModes;` — Texture pin mode per UV Channel

#### struct `FMorphNodeData`  
`struct FMorphNodeData`  
_L125-144_
- desc: Struct to store the necessary data to generate the morphs of a skeletal mesh This struct allows the stack morph nodes to use the same functions as the mesh morph nodes
- L128 _public member_ `UCustomizableObjectNode* OwningNode;` — Pointer to the node that owns this morph data
- L131 _public member_ `FName MorphTargetName;` — Name of the morph that will be applied
- L134 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeScalar> FactorNode;` — Pin to the node that generates the factor of the morph
- L137 _public member_ `const UEdGraphPin* MeshPin;` — Pin of the mesh where the morphs will ble applied
- L139 _public function_ `bool operator==(const FMorphNodeData& Other) const`

#### struct `FMaterialBreakParameter`  
`struct FMaterialBreakParameter`  
_L148-157_
- desc: Representation of the root of a Material Break node compilation branch.
- L151 _public member_ `UE::Mutable::Private::FParameterKey ParameterKey;` — Name and Layer Index of the material parameter.
- L154 _public member_ `FName ParameterType;` — The type of data this parameter relates to.
- L156 _public prototype_ `bool operator==(const FMaterialBreakParameter& OtherItem) const = default;`

#### class `FGeneratedKey`  
`class FGeneratedKey`  
_L161-201_
- desc: Key for the data stored for each processed unreal graph node.
- L166 _public prototype_ `FGeneratedKey(void* InFunctionAddress, const UEdGraphPin& InPin, const UCustomizableObjectNode& Node, FMutableGraphGenerationContext& GenerationContext, const bool UseMesh = false, bool bOnlyConnectedLOD = false, const bool bUseMaterialBreakStack = false);`
- L168 _public prototype_ `bool operator==(const FGeneratedKey& Other) const = default;`
- L171 _public member_ `void* FunctionAddress;` — Used to differentiate pins being cached from different functions (e.g. a PC_Color pin cached from GenerateMutableSourceImage and GenerateMutableSourceColor).
- L173 _public member_ `const UEdGraphPin* Pin;`
- L175 _public member_ `int32 LOD;`
- L176 _public member_ `int32 FromLOD;`
- L179 _public member_ `EMutableMeshConversionFlags Flags = EMutableMeshConversionFlags::None;` — Flag used to generate this mesh. Bit mask of EMutableMeshConversionFlags
- L182 _public member_ `FLayoutGenerationFlags LayoutFlags;` — UV Layout modes
- L184 _public member_ `UE::Mutable::Private::FComponentId CurrentMeshComponent = INDEX_NONE;`
- L187 _public member_ `bool bOnlyConnectedLOD = false;` — When caching a generated mesh, true if we force to generate the connected LOD when using Automatic LODs From Mesh.
- L190 _public member_ `TArray<const UCustomizableObjectNodeMacroInstance*> MacroContext;` — Pointer to control if this is a node inside a Mutable Macro.
- L195 _public member_ `TArray<FMaterialBreakParameter> MaterialBreakParameterStack;` — Stack of Material Break Parameters. It may contain one or multiple entries where the last one is the Material Break Parameter being processed while compiling the branches of the graph.
- L197 _public member_ `int32 ReferenceTextureSize = -1;`
- L200 _public member_ `FString ParameterName;` — Name of the parameter. A parameter node can be redefined if it is inside a macro and the name comes from outside the graph.

#### struct `FGeneratedParameterKey`  
`struct FGeneratedParameterKey`  
_L209-218_
- desc: Cache key of the generated parameter nodes
- L212 _public member_ `FGuid NodeId;` — ID of the node
- L215 _public member_ `FString ParameterName;` — Name of the parameter.
- L217 _public prototype_ `bool operator==(const FGeneratedParameterKey& Other) const = default;`

#### struct `FSourceExternalOptions`  
`struct FSourceExternalOptions`  
_L224-239_
- desc: Struct used for external options of the GenerateMutableSourceX functions.
- L227 _public member_ `FMutableSourceMeshData MeshOptions;` — GenerateMutableSourceMesh
- L228 _public member_ `bool bLinkedToExtendMaterial = false;`
- L229 _public member_ `bool bOnlyConnectedLOD = false;`
- L230 _public member_ `int8 CurrentLOD = 0;`
- L233 _public member_ `int32 ReferenceTextureSize = 0;` — GenerateMutableSourceImage
- L236 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeSurfaceNew> SurfaceNode = nullptr;` — GenerateMutableSourceMaterial
- L238 _public prototype_ `bool operator==(const FSourceExternalOptions& Other) const = default;`

#### struct `FGeneratedSourceExternalKey`  
`struct FGeneratedSourceExternalKey`  
_L242-249_
- L244 _public member_ `const UEdGraphPin* Pin = nullptr;`
- L246 _public member_ `FSourceExternalOptions Options;`
- L248 _public prototype_ `bool operator==(const FGeneratedSourceExternalKey& Other) const = default;`

#### struct `FSourceSkeletalMeshObjectOptions`  
`struct FSourceSkeletalMeshObjectOptions`  
_L255-260_
- L257 _public member_ `USkeletalMesh* ReferenceSkeletalMesh = nullptr;`
- L259 _public prototype_ `bool operator==(const FSourceSkeletalMeshObjectOptions& Other) const = default;`

#### struct `FSourceSkeletalMeshOptions`  
`struct FSourceSkeletalMeshOptions`  
_L266-273_
- L268 _public member_ `int32 NumLODs = 0;`
- L270 _public member_ `int32 FirstLODAvailable = 0;`
- L272 _public prototype_ `bool operator==(const FSourceSkeletalMeshOptions& Other) const = default;`

#### struct `FGeneratedSourceSkeletalMeshKey`  
`struct FGeneratedSourceSkeletalMeshKey`  
_L279-289_
- L281 _public member_ `const UEdGraphPin* Pin = nullptr;`
- L283 _public member_ `FSourceSkeletalMeshOptions Options;`
- L286 _public member_ `TArray<const UCustomizableObjectNodeMacroInstance*> MacroContext;` — Pointer to control if this is a node inside a Mutable Macro.
- L288 _public prototype_ `bool operator==(const FGeneratedSourceSkeletalMeshKey& Other) const = default;`

#### struct `FGeneratedSourceSkeletalMeshObjectKey`  
`struct FGeneratedSourceSkeletalMeshObjectKey`  
_L295-305_
- L297 _public member_ `const UEdGraphPin* Pin = nullptr;`
- L299 _public member_ `FSourceSkeletalMeshObjectOptions Options;`
- L302 _public member_ `TArray<const UCustomizableObjectNodeMacroInstance*> MacroContext;` — Pointer to control if this is a node inside a Mutable Macro.
- L304 _public prototype_ `bool operator==(const FGeneratedSourceSkeletalMeshObjectKey& Other) const = default;`

#### struct `FImageKey`  
`struct FImageKey`  
_L311-324_
- L313 _public function_ `FImageKey(const UEdGraphPin* InPin)`
- L318 _public function_ `bool operator==(const FImageKey& Other) const`
- L323 _public member_ `const UEdGraphPin* Pin;`

#### struct `FGeneratedImagePropertiesKey`  
`struct FGeneratedImagePropertiesKey`  
_L327-343_
- L329 _public function_ `FGeneratedImagePropertiesKey(const UCustomizableObjectNode* InMaterial, UE::Mutable::Private::FParameterKey InImageKey)`
- L335 _public function_ `bool operator==(const FGeneratedImagePropertiesKey& Other) const`
- L341 _public member_ `PTRINT MaterialReferenceId = 0;`
- L342 _public member_ `UE::Mutable::Private::FParameterKey ImageKey;`

#### struct `FMutableGraphMeshGenerationData`  
`struct FMutableGraphMeshGenerationData`  
_L346-366_
- desc: Structure storing results to propagate up when generating mutable mesh node expressions.
- L349 _public member_ `bool bHasVertexColors = false;` — Did we find any mesh with vertex colors in the expression?
- L350 _public member_ `bool bHasRealTimeMorphs = false;`
- L351 _public member_ `bool bHasClothing = false;`
- L354 _public member_ `int32 NumTexCoordChannels = 0;` — Maximum number of texture channels found in the expression.
- L357 _public member_ `int32 MaxNumBonesPerVertex = 0;` — Maximum number of bones per vertex found in the expression.
- L360 _public member_ `int32 MaxBoneIndexTypeSizeBytes = 0;` — Maximum size of the vertex bone index type in the expression.
- L362 _public member_ `int32 MaxNumTriangles = 0;`
- L363 _public member_ `int32 MinNumTriangles = TNumericLimits<int32>::Max();`
- L365 _public member_ `TArray<int32> SkinWeightProfilesSemanticIndices;`

#### struct `FGeneratedData`  
`struct FGeneratedData`  
_L370-387_
- desc: Data stored for each processed unreal graph node, stored in the cache.
- L372 _public function_ `FGeneratedData(const UEdGraphNode* InSource, const TArray<UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeModifier>>& InModifierNodes)`
- L378 _public function_ `FGeneratedData(const UEdGraphNode* InSource, UE::Mutable::Private::NodePtr InNode)`
- L384 _public member_ `const UEdGraphNode* Source;`
- L385 _public member_ `UE::Mutable::Private::NodePtr Node;`
- L386 _public member_ `TArray<UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeModifier>> ModifierNodes;`

#### struct `FGeneratedSourceExternalData`  
`struct FGeneratedSourceExternalData`  
_L390-393_
- L392 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeExternal> Node;`

#### struct `FGeneratedSourceSkeletalMeshData`  
`struct FGeneratedSourceSkeletalMeshData`  
_L396-399_
- L398 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeSkeletalMesh> Node;`

#### struct `FGeneratedSourceSkeletalMeshObjectData`  
`struct FGeneratedSourceSkeletalMeshObjectData`  
_L402-405_
- L404 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeSkeletalMeshObject> Node;`

#### struct `FPoseBoneData`  
`struct FPoseBoneData`  
_L423-427_
- L425 _public member_ `TArray<FName> ArrayBoneName;`
- L426 _public member_ `TArray<FTransform> ArrayTransform;`

#### struct `FGroupProjectorTempData`  
`struct FGroupProjectorTempData`  
_L429-443_
- L431 _public member_ `class UCustomizableObjectNodeGroupProjectorParameter* CustomizableObjectNodeGroupProjectorParameter;`
- L432 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeProjectorParameter> NodeProjectorParameterPtr;`
- L433 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage> NodeImagePtr;`
- L434 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeRange> NodeRange;`
- L435 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeScalarParameter> NodeOpacityParameter;`
- L437 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeScalarEnumParameter> PoseOptionsParameter;`
- L438 _public member_ `TArray<FPoseBoneData> PoseBoneDataArray;`
- L440 _public member_ `bool bAlternateResStateNameWarningDisplayed = false;` — Used to display this warning only once
- L442 _public member_ `int32 TextureSize = 512;`

#### struct `FGroupNodeIdsTempData`  
`struct FGroupNodeIdsTempData`  
_L446-462_
- L448 _public function_ `FGroupNodeIdsTempData(FGuid OldGuid, FGuid NewGuid = FGuid()) : OldGroupNodeId(OldGuid), NewGroupNodeId(NewGuid)`
- L455 _public member_ `FGuid OldGroupNodeId;`
- L456 _public member_ `FGuid NewGroupNodeId;`
- L458 _public function_ `bool operator==(const FGroupNodeIdsTempData& Other) const`

#### struct `FSkeletalMeshComponentInfo`  
`struct FSkeletalMeshComponentInfo`  
_L466-474_
- desc: Struct used to store info specific to each component during compilation
- L468 _public member_ `UE::Mutable::Private::FComponentId ComponentId = INDEX_NONE;`
- L471 _public member_ `TStrongObjectPtr<USkeletalMesh> RefSkeletalMesh;` — Each component must have a reference SkeletalMesh with a valid Skeleton
- L473 _public member_ `UCONodeComponentSkeletalMesh* Node = nullptr;`

#### struct `FGraphCycleKey`  
`struct FGraphCycleKey`  
_L482-497_
- desc: Graph cycle key. Pin is not enough since we can call multiple recursive functions with the same pin. Each function has to have an unique identifier.
- L486 _public prototype_ `FGraphCycleKey(const UEdGraphPin& Pin, const FString& Id, const UCustomizableObjectNodeMacroInstance* MacroContext);`
- L488 _public prototype_ `bool operator==(const FGraphCycleKey& Other) const;`
- L491 _public member_ `const UEdGraphPin& Pin;` — Valid pin.
- L494 _public member_ `FString Id;` — Unique id.
- L496 _public member_ `const UCustomizableObjectNodeMacroInstance* MacroContext;`

#### class `FGraphCycle`  
`class FGraphCycle`  
_L503-518_
- desc: Graph Cycle scope. Detect a cycle during the graph traversal.
- L506 _public prototype_ `explicit FGraphCycle(const FGraphCycleKey&& Key, FMutableGraphGenerationContext &Context);`
- L507 _public prototype_ `~FGraphCycle();`
- L510 _public prototype_ `bool FoundCycle() const;` — Return true if there is a cycle.
- L514 _private member_ `FGraphCycleKey Key;` — Graph traversal key.
- L517 _private member_ `FMutableGraphGenerationContext& Context;` — Generation context.

#### struct `FGeneratedGroupProjectorsKey`  
`struct FGeneratedGroupProjectorsKey`  
_L530-536_
- L532 _public member_ `UCustomizableObjectNodeGroupProjectorParameter* Node = nullptr;`
- L533 _public member_ `UE::Mutable::Private::FComponentId CurrentComponent;`
- L535 _public prototype_ `bool operator==(const FGeneratedGroupProjectorsKey&) const = default;`

#### struct `FMutableCompilationContext`  
`struct FMutableCompilationContext`  
_L546-589_
- desc: This structure stores the information that is used during the CustomizableObject compilation. This includes graph generation, core compilation and data storage. This context should have nothing to do with CO-level nodes. It should only be accessed from the game thread.
- L549 _public member_ `TStrongObjectPtr<const UCustomizableObject> RootObject;`
- L552 _public member_ `FCompilationOptions Options;` — Compilation options, including target platform.
- L555 _public member_ `TArray<FRealTimeMorphSelectionOverride> RealTimeMorphTargetsOverrides;` — Global morph selection overrides.
- L558 _public member_ `TArray<TSoftObjectPtr<UPhysicsAsset>> PhysicsAssets;` — Stores the physics assets gathered from the SkeletalMesh nodes during compilation, to be used in mesh generation in-game
- L560 _public member_ `TArray<FAnimBpOverridePhysicsAssetsInfo> AnimBpOverridePhysicsAssetsInfo;`
- L564 _public member_ `TArray<FSkeletalMeshComponentInfo> ComponentInfos;` — Only Mesh Components (no passthrough).
- L566 _public member_ `UE::Mutable::Private::FPassthroughObjectFactory PassthroughObjectFactory;`
- L571 _private member_ `TWeakPtr<FCustomizableObjectCompiler> WeakCompiler;` — Non-owned reference to the compiler object
- L575 _public prototype_ `FMutableCompilationContext(const UCustomizableObject* InRootObject, const TSharedPtr<FCustomizableObjectCompiler>& InCompiler, const FCompilationOptions& InOptions);`
- L578 _public prototype_ `FString GetObjectName() const;` — Return the name of the current customizable object, for logging purposes.
- L581 _public prototype_ `void Log(const FText& Message, const TArray<const UObject*>& UObject, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const bool bAddBaseObjectInfo = true, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll) const;` — Message logging
- L582 _public prototype_ `void Log(const FText& Message, const UObject* Context = nullptr, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const bool bAddBaseObjectInfo = true, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll) const;`
- L585 _public prototype_ `FSkeletalMeshComponentInfo* GetComponentInfo(const UCONodeComponentSkeletalMesh* NodeComponentMesh);` — Component access (for Mesh components only).
- L587 _public prototype_ `FSkeletalMeshComponentInfo* GetComponentInfo(UE::Mutable::Private::FComponentId ComponentName);`

#### struct `FGeneratedMutableDataTableKey`  
`struct FGeneratedMutableDataTableKey`  
_L592-607_
- L594 _public prototype_ `FGeneratedMutableDataTableKey(FString TableName, FName VersionColumn, const TArray<FTableNodeCompilationFilter>& CompilationFilterOptions);`
- L597 _public member_ `FString TableName;` — Name of the Data Table Asset
- L601 _public member_ `FName VersionColumn;` — Compilation Restrictions: Name of the column that determines de version control
- L604 _public member_ `TArray<FTableNodeCompilationFilter> CompilationFilterOptions;` — Compilation Filters
- L606 _public prototype_ `bool operator==(const FGeneratedMutableDataTableKey&) const = default;`

#### struct `FSharedSurfaceKey`  
`struct FSharedSurfaceKey`  
_L611-619_
- L613 _public prototype_ `FSharedSurfaceKey(const UCONodeSkeletalMeshSection* NodeMaterial, const TArray<const UCustomizableObjectNodeMacroInstance*>& CurrentMacroContext);`
- L615 _public prototype_ `bool operator==(const FSharedSurfaceKey& o) const = default;`
- L617 _public member_ `FGuid MaterialGuid;`
- L618 _public member_ `FGuid MacroContextGuid;`

#### struct `FMutableGraphGenerationContext`  
`struct FMutableGraphGenerationContext`  
_L627-930_
- desc: This structure stores the information that is used only during the graph generation stage of the CustomizableObject compilation. Data needed for node graph processing goes here.
- L629 _public prototype_ `FMutableGraphGenerationContext(const TSharedPtr<FMutableCompilationContext>& InCompilationContext);`
- L631 _public member_ `TSharedPtr<FMutableCompilationContext> CompilationContext;`
- L634 _public member_ `UCustomizableObjectNodeObject* Root = nullptr;` — Full hierarchy root.
- L637 _public member_ `TMap<FGeneratedKey, FGeneratedData> Generated;` — Cache of generated pins per LOD
- L638 _public member_ `TMap<FGeneratedSourceExternalKey, FGeneratedSourceExternalData> GeneratedSourceExternals;`
- L639 _public member_ `TMap<FGeneratedSourceSkeletalMeshKey, FGeneratedSourceSkeletalMeshData> GeneratedSourceSkeletalMesh;`
- L640 _public member_ `TMap<FGeneratedSourceSkeletalMeshObjectKey, FGeneratedSourceSkeletalMeshObjectData> GeneratedSourceSkeletalMeshObject;`
- L643 _public member_ `TSet<UCustomizableObjectNode*> GeneratedNodes;` — Set of all generated nodes.
- L662 _public member_ `TMap<FGeneratedMutableDataTableKey, FGeneratedDataTablesData> GeneratedTables;` — Cache of generated Node Tables
- L664 _public member_ `TMap<FGeneratedGroupProjectorsKey, FGroupProjectorTempData> GeneratedGroupProjectors;`
- L667 _public member_ `TMap<FGeneratedParameterKey, UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeScalarParameter>> GeneratedScalarParameters;` — Key is the Node Uid and the parameter name.
- L670 _public member_ `TMap<FGeneratedParameterKey, UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeScalarEnumParameter>> GeneratedEnumParameters;` — Key is the Node Uid and the parameter name.
- L673 _public member_ `TMap<FGeneratedParameterKey, UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImageObjectParameter>> GeneratedImageParameters;` — Key is the Node Uid and the parameter name.
- L676 _public member_ `TMap<FGeneratedParameterKey, UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeSkeletalMeshObjectParameter>> GeneratedSkeletalMeshParameters;` — Key is the Node Uid and the parameter name.
- L679 _public member_ `TMap<FGeneratedParameterKey, UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMaterialParameter>> GeneratedMaterialParameters;` — Key is the Node Uid and the parameter name.
- L694 _public member_ `TArray<FGeneratedCompositeDataTablesData> GeneratedCompositeDataTables;` — Cache of generated Composited Data Tables
- L698 _public member_ `TMap<FImageKey, UE::Mutable::Private::NodeImagePtr> GeneratedImages;` — Cache of generated images, because sometimes they are reused by LOD, we use this as a second level cache
- L723 _public member_ `TMap<FMutableSourceMeshData, FGeneratedReferencedMesh> CompileTimeMeshMap;` — Cache of runtime pass-through meshes and their IDs used in the core to identify them These meshes will become mutable meshes in the compiled model.
- L727 _public member_ `TMap<TSoftObjectPtr<UTexture2D>, FGeneratedReferencedTexture> RuntimeReferencedTextureMap;` — Cache of runtime images and their IDs used in the core to identify them. These textures will remain as external references even in optimized models.
- L731 _public member_ `TMap<TSoftObjectPtr<UTexture2D>, FGeneratedReferencedTexture> CompileTimeTextureMap;` — Cache of runtime pass-through images and their IDs used in the core to identify them These textures will become mutable images in the compiled model.
- L766 _public member_ `TArray<FGeneratedMeshData> GeneratedMeshes;`
- L780 _public member_ `TArray<FGeneratedTableImageData> GeneratedTableImages;`
- L784 _public member_ `TArray<EMutableMeshConversionFlags> MeshGenerationFlags;` — Stack of mesh generation flags. The last one is the currently valid. The value is a bit mask of EMutableMeshConversionFlags
- L787 _public member_ `TArray<FLayoutGenerationFlags> LayoutGenerationFlags;` — Stack of Layout generation flags. The last one is the currently valid.
- L791 _public member_ `TArray<TArray<UCustomizableObjectNodeGroupProjectorParameter*>> CurrentGroupProjectors;` — Stack of Group Projector nodes. Each time a Group Object node is visited, a set of Group Projector nodes get pushed When a Mesh Section node is found, it will compile all Group Projector nodes in the stack.
- L794 _public prototype_ `FString GetObjectName() const;` — Message logging
- L795 _public prototype_ `void Log(const FText& Message, const TArray<const UObject*>& Context, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const bool bAddBaseObjectInfo = true, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll) const;`
- L796 _public prototype_ `void Log(const FText& Message, const UObject* Context = nullptr, const EMessageSeverity::Type MessageSeverity = EMessageSeverity::Warning, const bool bAddBaseObjectInfo = true, const ELoggerSpamBin SpamBin = ELoggerSpamBin::ShowAll) const;`
- L799 _public prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> FindGeneratedMesh(const FGeneratedMeshData::FKey& Key);` — Find a mesh if already generated for a given source and flags.
- L802 _public prototype_ `const FGuid GetNodeIdUnique(const UCustomizableObjectNode* Node);` — Check if the Id of the node Node already exists, if it's new adds it to NodeIds array, otherwise, returns new Id
- L807 _public prototype_ `const FGuid GetNodeIdUnchecked(const UCustomizableObjectNode* Node);` — Same as GetNodeIdUnique but does not triggers any warning on repeated IDs. Use only if GetNodeIdUnique is used in another part of the code.
- L809 _public prototype_ `UObject* LoadObject(const FSoftObjectPtr& SoftObject);`
- L812 _public function_ `template<typename T> T* LoadObject(const TSoftObjectPtr<T>& SoftObject)`
- L818 _public function_ `template<typename T> UClass* LoadClass(const TSoftClassPtr<T>& SoftClass)`
- L827 _public prototype_ `FMaterialBreakParameter GetCurrentMaterialBreakParameter();` — Get the Current Material Break Parameter that roots the current CO node graph branch. @return The current Material Break Parameter. Will return a default object if there is no Material Break Parameter in the current compilation scope.
- L830 _public member_ `TArray<FName> ComponentNames;` — Only compiled components. All component types. Index is the ComponentId.
- L832 _public member_ `TArray<FMutableRefSkeletalMeshData> ReferenceSkeletalMeshesData;`
- L834 _public member_ `TMap<FGeneratedImagePropertiesKey, FGeneratedImageProperties> ImageProperties;`
- L835 _public member_ `TArray<const UCustomizableObjectNode*> NoNameNodeObjectArray;`
- L836 _public member_ `TMap<FString, FCustomizableObjectIdPair> GroupNodeMap;`
- L837 _public member_ `TMap<FString, FString> CustomizableObjectPathMap;`
- L838 _public member_ `TMap<FString, FMutableParameterData> ParameterUIDataMap;`
- L839 _public member_ `TMap<FString, FMutableStateData> StateUIDataMap;`
- L840 _public member_ `TMap<FIntegerParameterOptionKey, FIntegerParameterOptionDataTable> IntParameterOptionDataTable;`
- L844 _public member_ `TMap<FGuid, TArray<const UObject*>> NodeIdsMap;` — Used to aviod Nodes with duplicated ids
- L845 _public member_ `TMultiMap<const UCustomizableObject*, FGroupNodeIdsTempData> DuplicatedGroupNodeIds;`
- L847 _public member_ `uint8 FromLOD = 0;` — LOD to append to the CurrentLOD when using AutomaticLODs.
- L848 _public member_ `uint8 CurrentLOD = 0;`
- L849 _public member_ `UE::Mutable::Private::FComponentId CurrentSkeletalMeshComponent = INDEX_NONE;`
- L852 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMesh> ComponentMeshOverride;` — If this is set, we are generating materials for a "passthrough" component, with a fixed mesh.
- L854 _public member_ `const uint8 MaxNumLODs = 16;` — Ceiling. Core will discard unnecessary ones.
- L856 _public member_ `bool bPartialCompilation = false;`
- L859 _public member_ `TMultiMap<FGuid, UCustomizableObjectNodeObject*> GroupIdToExternalNodeMap;` — Stores external graph root nodes to be added to the specified group nodes
- L862 _public member_ `TMap<FGuid, FParamInfo> GuidToParamNameMap;` — Easily retrieve a parameter name from its node guid
- L867 _public member_ `TMap<FGraphCycleKey, const UCustomizableObject*> VisitedPins;` — Visited nodes during the DAC recursion traversal. It acts like stack, pushing pins when recursively exploring a new pin an popping it when exiting the recursion.
- L868 _public member_ `const UCustomizableObject* CustomizableObjectWithCycle = nullptr;`
- L871 _public member_ `TArray<TSoftClassPtr<UAnimInstance>> AnimBPAssets;` — Stores the anim BP assets gathered from the SkeletalMesh nodes during compilation, to be used in mesh generation in-game
- L876 _public member_ `TArray<int8> SocketPriorityStack;` — Used to propagate the socket priority defined in group nodes to their child skeletal mesh nodes It's a stack because group nodes are recursive
- L881 _public member_ `TArray<int8> BonePosePriorityStack;` — Used to propagate the BonePose priority defined in group nodes to their child skeletal mesh nodes It's a stack because group nodes are recursive
- L884 _public member_ `TMap<FString, FMutableParamNameSet> TableToParamNames;` — Stores what param names use a certain table as a table can be used from multiple table nodes, useful for partial compilations to restrict params
- L886 _public member_ `TArray<const UEdGraphNode*> LimitedParameters;`
- L887 _public member_ `int32 ParameterLimitationCount = 0;`
- L890 _public member_ `FString CurrentMaterialTableParameter;` — Current material parameter name to find the corresponding column in a mutable table
- L893 _public member_ `UE::Mutable::Private::ETableColumnType CurrentTableColumnType = UE::Mutable::Private::ETableColumnType::None;`
- L896 _public member_ `FString CurrentMaterialParameterId;` — Current material parameter id to find the corresponding column in a mutable table
- L899 _public member_ `TMap<FSharedSurfaceKey, FGuid> SurfaceGuids;` — Material to SharedSurfaceId
- L902 _public member_ `FExtensionDataCompilerInterface ExtensionDataCompilerInterface;` — Extension Data constants are collected here
- L905 _public member_ `TMap<UDataTable*,TMap<FName, TArray<UDataTable*>>> CompositeDataTableRowToOriginalDataTableMap;` — Map to relate a Composite Data Table Row and its original DataTable
- L908 _public member_ `TObjectPtr<UObject> RootVersionBridge;` — Version Bridge of the root object
- L911 _public member_ `TStrongObjectPtr<UMaterialInterface> CurrentReferencedMaterial;` — Index of the Referenced Material being generated
- L913 _public member_ `FGeneratedImageProperties* CurrentImageProperties = nullptr;`
- L917 _public member_ `TArray<const UCustomizableObjectNodeMacroInstance*> MacroNodesStack;` — This should be automatized (create a struct that each time that a Macro is stacked, it adds 1 to the count. it also substracts 1 each time we remove a Macro from the stack)
- L920 _public member_ `TMap<FString, TObjectPtr<UTexture>> TextureParameterDefaultValues;` — TODO GMT Get Default Values from Core. We only need compiled ones
- L921 _public member_ `TMap<FString, TObjectPtr<USkeletalMesh>> SkeletalMeshParameterDefaultValues;`
- L922 _public member_ `TMap<FString, TObjectPtr<UMaterialInterface>> MaterialParameterDefaultValues;`
- L923 _public member_ `TMap<FString, FInstancedStruct> ExternalTypeParameterDefaultValues;`
- L925 _public member_ `TMap<FString, TObjectPtr<const UScriptStruct>> ExternalTypeParameterTypes;`
- L929 _public member_ `TArray<FMaterialBreakParameter> MaterialBreakParameterStack;` — Name of the material break Node that is being compiled. NOTE: This is set when the material pin of a material break node is compiled and then it must be reset to empty.

#### struct `FMutableGraphGenerationContext::FGeneratedDataTablesData`  
`struct FGeneratedDataTablesData`  
_L648-659_
- desc: Struct that stores the relevant information of a data table generated during the compilation. e.g. all data tables must have the same compilation restrictions
- L651 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::FTable> GeneratedTable;` — Pointer to the generated mutable Table
- L654 _public member_ `const UCustomizableObjectNodeTable* ReferenceNode;` — Table Node used to fill this info
- L657 _public member_ `TArray<FName> RowNames;` — Stores the names of the rows that will be compiled
- L658 _public member_ `TArray<uint32> RowIds;`

#### struct `FMutableGraphGenerationContext::FGeneratedCompositeDataTablesData`  
`struct FGeneratedCompositeDataTablesData`  
_L681-691_
- L683 _public member_ `UScriptStruct* ParentStruct = nullptr;`
- L684 _public member_ `TArray<FName> FilterPaths;`
- L685 _public member_ `UCompositeDataTable* GeneratedDataTable = nullptr;`
- L687 _public function_ `bool operator==(const FGeneratedCompositeDataTablesData& Other) const`

#### struct `FMutableGraphGenerationContext::FGeneratedReferencedTexture`  
`struct FGeneratedReferencedTexture`  
_L701-705_
- desc: Data stored per-generated passthrough texture.
- L703 _public member_ `UE::Mutable::Private::PASSTHROUGH_ID ID;`

#### struct `FMutableGraphGenerationContext::FGeneratedReferencedMesh`  
`struct FGeneratedReferencedMesh`  
_L708-711_
- desc: Data stored per-generated passthrough mesh.
- L710 _public member_ `UE::Mutable::Private::PASSTHROUGH_ID ID;`

#### struct `FMutableGraphGenerationContext::FParamInfo`  
`struct FParamInfo`  
_L713-719_
- L715 _public member_ `FString ParamName;`
- L716 _public member_ `bool bIsToggle = false;`
- L718 _public function_ `FParamInfo(const FString& InParamName, bool bInIsToggle) : ParamName(InParamName), bIsToggle(bInIsToggle)`

#### struct `FMutableGraphGenerationContext::FGeneratedMeshData`  
`struct FGeneratedMeshData`  
_L734-765_
- desc: Mutable meshes already build for source UStaticMesh or USkeletalMesh.
- L761 _public member_ `FKey Key;`
- L764 _public member_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> Generated;` — Generated mesh.

#### struct `FMutableGraphGenerationContext::FGeneratedMeshData::FKey`  
`struct FKey`  
_L736-759_
- L739 _public member_ `TSoftObjectPtr<const UStreamableRenderAsset> Mesh;` — Source mesh data.
- L740 _public member_ `int32 LOD = 0;` — Mesh Data LOD (i.e., LOD where we are getting the vertices from)
- L741 _public member_ `int32 CurrentLOD = 0;` — Derived data LOD (i.e., LOD where we are generating the non-Core Data like morphs)
- L742 _public member_ `int32 FromLOD = 0;` — Connected data LOD
- L743 _public member_ `int32 MaterialIndex = 0;`
- L746 _public member_ `EMutableMeshConversionFlags Flags = EMutableMeshConversionFlags::None;` — Flag used to generate this mesh. Bit mask of EMutableMeshConversionFlags
- L752 _public member_ `const UCustomizableObjectNode* SkeletalMeshNode = nullptr;` — SkeletalMeshNode is needed to disambiguate realtime morph selection from different nodes. TODO: Consider using the actual selection.
- L754 _public member_ `FGameplayTagContainer GameplayTags;`
- L755 _public member_ `FName AnimBPSlotName;`
- L756 _public member_ `TSoftClassPtr<UAnimInstance> AnimInstance;`
- L758 _public prototype_ `bool operator==(const FKey& OtherKey) const = default;`

#### struct `FMutableGraphGenerationContext::FGeneratedTableImageData`  
`struct FGeneratedTableImageData`  
_L768-779_
- L770 _public member_ `FString PinName;`
- L771 _public member_ `FName PinType;`
- L772 _public member_ `const UE::Mutable::Private::Ptr<UE::Mutable::Private::FTable> Table;`
- L773 _public member_ `const UCustomizableObjectNodeTable* TableNode;`
- L775 _public function_ `bool operator==(const FGeneratedTableImageData& Other) const`

#### Free symbols / members of external scopes

- L204 _prototype_ `uint32 GetTypeHash(const FMaterialBreakParameter& Key);`
- L206 _prototype_ `uint32 GetTypeHash(const FGeneratedKey& Key);`
- L220 _prototype_ `uint32 GetTypeHash(const FGeneratedParameterKey& Key);`
- L252 _prototype_ `uint32 GetTypeHash(const FGeneratedSourceExternalKey& Key);`
- L263 _prototype_ `uint32 GetTypeHash(const FSourceSkeletalMeshObjectOptions& Key);`
- L276 _prototype_ `uint32 GetTypeHash(const FSourceSkeletalMeshOptions& Key);`
- L292 _prototype_ `uint32 GetTypeHash(const FGeneratedSourceSkeletalMeshKey& Key);`
- L308 _prototype_ `uint32 GetTypeHash(const FGeneratedSourceSkeletalMeshObjectKey& Key);`
- L408 _function_ `inline uint32 GetTypeHash(const FImageKey& Key)`
- L416 _function_ `inline uint32 GetTypeHash(const FGeneratedImagePropertiesKey& Key)`
- L521 _macro_ `#define RETURN_ON_CYCLE(Pin, GenerationContext) \` — Return the default value if there is a cycle.
- L538 _prototype_ `uint32 GetTypeHash(const FGeneratedGroupProjectorsKey& Key);`
- L609 _prototype_ `uint32 GetTypeHash(const FGeneratedMutableDataTableKey& Key);`
- L621 _prototype_ `uint32 GetTypeHash(const FSharedSurfaceKey& Key);`
- L933 _namespace_ `namespace GenerateMutableSourcePrivate`
- L936 _function_ `template<class HashableType, class HashDataSetType, class HashFuncType, class CompareFuncType> uint32 GenerateUniquePersistentHash(const HashableType& HashableData, const HashDataSetType& HashDataSet, HashFuncType&& HashFunc, CompareFuncType&& CompareFunc)` (scope `GenerateMutableSourcePrivate`)
- L989 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeObject> GenerateMutableSource(const class UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);`
- L992 _prototype_ `void PopulateReferenceSkeletalMeshesData(FMutableGraphGenerationContext& GenerationContext);` — Populate an array with all the information related to the reference skeletal meshes we might need in-game to generate instances
- L995 _prototype_ `void CheckNode(const UEdGraphPin& Pin, const FMutableGraphGenerationContext& GenerationContext);`
- L999 _prototype_ `UTexture2D* FindReferenceImage(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` — TODO FutureGMT Remove generation context dependency and move to GraphTraversal.
- L1002 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMeshApplyPose> CreateNodeMeshApplyPose(FMutableGraphGenerationContext& GenerationContext, UE::Mutable::Private::NodeMeshPtr InputMeshNode, const TArray<FName>& ArrayBoneName, const TArray<FTransform>& ArrayTransform);`
- L1005 _prototype_ `uint32 GetBaseTextureSize(const FMutableGraphGenerationContext& GenerationContext, const UCONodeSkeletalMeshSection* MeshSectionNode, const UE::Mutable::Private::FParameterKey& ImageKey);`
- L1009 _prototype_ `uint32 ComputeLODBiasForTexture(const FMutableGraphGenerationContext& GenerationContext, const UTexture2D& Texture, const UTexture2D* ReferenceTexture = nullptr, int32 MaxTextureSizeInGame = 0);` — Computes the LOD bias for a texture given the current mesh LOD and automatic LOD settings, the reference texture settings and whether it's being built for a server or not
- L1012 _prototype_ `int32 GetMaxTextureSize(const UTexture2D& ReferenceTexture, const UTextureLODSettings& LODSettings);` — Max texture size to set on the ImageProperties
- L1015 _prototype_ `int32 GetTextureSizeInGame(const UTexture2D& Texture, const UTextureLODSettings& LODSettings);` — Max texture size of the texture with per platform MaxTextureSize and LODBias applied.
- L1018 _prototype_ `void GetCookedTextureSize(const FMutableGraphGenerationContext& GenerationContext, const UTexture2D* Texture, uint32& OutTextureSizeX, uint32& OutTextureSizeY, bool bSkipCinematicMips);` — Compute the size Texture will have in-game on the TargetPlatform (cooked) using Source data only.
- L1021 _prototype_ `void GetLayoutBlockSizeInPixels(const FMutableGraphGenerationContext& GenerationContext, const UTexture2D* ReferenceTexture, const int32 NumBlocksX, const int32 NumBlocksY, uint16& BlockSizeX, uint16& BlockSizeY);` — Get the BlockSize in pixels in-game for an image with ReferenceTexture and NumBlocksX and NumBlocksY blocks.
- L1023 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FImage> GenerateImageConstant(UTexture*, FMutableGraphGenerationContext&, bool bIsReference);`
- L1024 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> GenerateMeshConstant(const FMutableSourceMeshData& Source, FMutableGraphGenerationContext&);`
- L1027 _prototype_ `UE::Mutable::Private::FImageDesc GenerateImageDescriptor(UTexture* Texture);` — Generates a mutable image descriptor from an unreal engine texture
- L1031 _prototype_ `UE::Tasks::FTask ConvertSkeletalMeshToMutable(TSharedRef<FMeshConversionContext> MeshConversionContext);` — Convert a mesh to Mutable format.
- L1038 _prototype_ `bool DoOptionsMatchEnum(const UCONodeSwitch& InEditorSwitchNode, const UE::Mutable::Private::NodeScalarEnumParameter& MutableScalarParameter);` — Compares the Amount and names of the options exposed in the provided Enum Parameter Node with the options set in this node. @param MutableScalarParameter The enum parameter node we want to compare the options against. @return true if the amount of options does match and false otherwise.
- L1040 _prototype_ `const FSkeletalMaterial* GetSkeletalMaterial(const USkeletalMesh* SkeletalMesh, uint8 LODIndex, uint8 SectionIndex);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceColor.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeColor> GenerateMutableSourceColor(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` — Convert a CustomizableObject Source Graph into a mutable source graph.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceComponent.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L17 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeComponent> GenerateMutableSourceComponent(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);`
- L20 _prototype_ `void FirstPass(UCONodeComponentSkeletalMesh& ComponentNode, FMutableGraphGenerationContext& GenerationContext);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceExternal.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeExternal> GenerateMutableSourceExternal(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext, const FSourceExternalOptions& Options);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceFloat.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeScalar> GenerateMutableSourceFloat(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` — Convert a CustomizableObject Source Graph into a mutable source graph.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceGroupProjector.h` (Private)


#### Free symbols / members of external scopes

- L20 _prototype_ `UE::Mutable::Private::NodeImagePtr GenerateMutableSourceGroupProjector(const int32 NodeLOD, const int32 ImageIndex, UE::Mutable::Private::NodeMeshPtr MeshNode, FMutableGraphGenerationContext& GenerationContext, UCONodeSkeletalMeshSection* TypedNodeMat, UCONodeModifierExtendSkeletalMeshSection* TypedNodeExt, bool& bIsGroupProjectorImage, UTexture2D*& GroupProjectionReferenceTexture);`
- L25 _prototype_ `TOptional<FGroupProjectorTempData> GenerateMutableGroupProjector(UCustomizableObjectNodeGroupProjectorParameter* ProjParamNode, FMutableGraphGenerationContext& GenerationContext);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceImage.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L23 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage> ResizeTextureByNumMips(const UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage>& Image, int32 MipsToSkip);`
- L26 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage> GenerateMutableSourceImage(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext, int32 ReferenceTextureSize);` — Convert a CustomizableObject Source Graph from an Image pin into a mutable source graph.
- L28 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImageObjectParameter> GenerateMutableSourceImageParameter(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);`
- L30 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImageFormat> GenerateMutableImageFormat( const UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage>& InSource, const UTexture2D* ReferenceTexture, const FMutableGraphGenerationContext& GenerationContext, const UCustomizableObjectNode* Node);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceLayout.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `extern UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeLayout> CreateDefaultLayout();`
- L13 _prototype_ `extern UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeLayout> CreateMutableLayoutNode(const UCustomizableObjectLayout*, bool bIgnoreLayoutWarnings);`
- L15 _prototype_ `extern UE::Mutable::Private::FSourceLayoutBlock ToMutable(const FCustomizableObjectLayoutBlock&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceMacro.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "CustomizableObjectEditor"`
- L14 _function_ `template<typename T, typename... ArgTypes> UE::Mutable::Private::Ptr<T> GenerateMutableSourceMacro(const UEdGraphPin& Pin, FMutableGraphGenerationContext& GenerationContext, UE::Mutable::Private::Ptr<T> (*GenerationFunction)(const UEdGraphPin*, FMutableGraphGenerationContext&, ArgTypes...), ArgTypes&&... Args)`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceMaterial.h` (Private)


#### struct `FGenerationMaterialOptions`  
`struct FGenerationMaterialOptions`  
_L20-27_
- desc: Add to this struct all the extra parameters that need to be passed to the GenerateMutableSourceMaterial function.
- L23 _public member_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeSurfaceNew> SurfaceNode = nullptr;` — Node surface. Only needed for MeshSection nodes.
- L26 _public member_ `int32 ReferenceTextureSize = 0;` — Size of the reference Texture Size

#### Free symbols / members of external scopes

- L17 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMaterialParameter> GenerateMutableSourceMaterialParameter(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` — Generates or retrieves an already generated Material Parameter based on the Pin and Generation Context provided. @param Pin Does represent the pin from the node we want to use as source for the generation or retrieval of the Mutable Material Parameter Node. @param GenerationContext The compilation context of the current compilation operation. @return A pointer to the generated/retrieved Mutable NodeMaterialParameter
- L30 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMaterial> GenerateMutableSourceMaterial( const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext, const FGenerationMaterialOptions& GenerationOptions);` — Convert a CustomizableObject Source Graph into a mutable source graph.
- L36 _prototype_ `FGeneratedImageProperties GenerateImageProperties(const UCustomizableObjectNode* Node, const UTexture2D* ReferenceTexture, const UE::Mutable::Private::FParameterKey& ImageKey, bool bIsPassthrough, FMutableGraphGenerationContext& GenerationContext);` — Generates an FGeneratedImageProperties from a Material Parameter and (if not null) its Reference Texture.
- L39 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage> GenerateMipMapAndFormatNodes( const UCustomizableObjectNode* Node, FMutableGraphGenerationContext& GenerationContext, UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeImage> ImageNode, UTexture2D* ReferenceTexture);` — Generate additional nodes to generate a texture with the correct format and size.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceMesh.h` (Private)


#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Mutable` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L39 _prototype_ `void GetLODAndSection(const FMutableCompilationContext& Context, const FMutableSourceMeshData& Source, const USkeletalMesh& SkeletalMesh, int32& OutLODIndex, int32& OutSectionIndex);` — Returns the corrected LOD and Section Index Do not confuse Section Index and Material Index, they are not the same. @param Context @param Source @param SkeletalMesh @param OutLODIndex Corrected Skeletal Mesh LOD Index. @param OutSectionIndex Corrected Skeletal Mesh Section Index. @return OutLODIndex and OutSectionIndex will return -1 if the section is not found in the currently compiling LOD.
- L50 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> ConvertSkeletalMeshToMutable(FMutableSourceMeshData& Source, int32 LODIndex, int32 SectionIndex, FMutableGraphGenerationContext& GenerationContext, const UCustomizableObjectNode* CurrentNode, bool bForceImmediateConversion = false );` — Converts an Unreal Skeletal Mesh to Mutable Mesh. @param Source. Mesh data required to generate the mutable mesh @param LODIndex LOD we are generating. Will be different from LODIndexConnected only when using Automatic LOD From Mesh. @param SectionIndex Section we are generating. Will be different from SectionIndexConnected only when using Automatic LOD From Mesh. @param GenerationContext @param CurrentNode The node being compiled, can be a skeletal mesh or a table node. @return Mutable Mesh. Nullptr if there has been an error. Empty mesh if the Skeletal Mesh does not contain the requested LOD + Section.
- L57 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> ConvertStaticMeshToMutable(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex, FMutableGraphGenerationContext& GenerationContext, const UCustomizableObjectNode* CurrentNode);`
- L69 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> GenerateMutableSkeletalMesh( FMutableSourceMeshData& Source, int32 LODIndexConnected, int32 SectionIndexConnected, FMutableGraphGenerationContext & GenerationContext, const UCustomizableObjectNode* CurrentNode, const bool bOnlyConnectedLOD);` — @param Source. Mesh data required to generate the mutable mesh @param LODIndexConnected LOD which the pin is connected to. @param SectionIndexConnected Section which the pin is connected to. @param GenerationContext @param CurrentNode The node being compiled, can be a skeletal mesh or a table node. @param bOnlyConnectedLOD @return Mutable Mesh. Nullptr if there has been an error. Empty mesh if the Skeletal Mesh does not contain the requested LOD + Section.
- L79 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> GenerateMutableStaticMesh( TSoftObjectPtr<UStreamableRenderAsset> Mesh, int32 LODIndex, int32 SectionIndex, FMutableGraphGenerationContext& GenerationContext, const UCustomizableObjectNode* CurrentNode);`
- L87 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> BuildMorphedMutableMesh(const UEdGraphPin* BaseSourcePin, const FString& MorphTargetName, FMutableGraphGenerationContext& GenerationContext, bool bOnlyConnectedLOD, const FName& RowName = "");`
- L99 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMesh> GenerateMutableSourceMesh(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext, const FMutableSourceMeshData& BaseMeshData, bool bLinkedToExtendMaterial, bool bOnlyConnectedLOD);` — Compiler recursive function. Mutable Node Mesh. @param Pin @param GenerationContext @param BaseMeshData @param bLinkedToExtendMaterial @param bOnlyConnectedLOD Corrected LOD and Section will unconditionally always be the connected ones. @return  Mutable Mesh Node.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceModifier.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _prototype_ `TArray<Ptr<NodeModifier>> GenerateMutableSourceModifier(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceProjector.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeProjector> GenerateMutableSourceProjector(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` — Convert a CustomizableObject Source Graph into a mutable source graph.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceSkeletalMesh.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L14 _prototype_ `Ptr<NodeSkeletalMesh> GenerateMutableSourceSkeletalMesh(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext, const FSourceSkeletalMeshOptions& Options);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceSkeletalMeshObject.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _prototype_ `Ptr<NodeSkeletalMeshObject> GenerateMutableSourceSkeletalMeshObject(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext, const FSourceSkeletalMeshObjectOptions& Options);` (scope `UE::Mutable::Private`)
- L20 _prototype_ `Ptr<NodeSkeletalMeshObjectParameter> GenerateMutableSourceSkeletalMeshObjectParameter(const UCustomizableObjectNodeSkeletalMeshParameter& Node, FMutableGraphGenerationContext& GenerationContext);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceSurface.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _prototype_ `extern UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeSurface> GenerateMutableSourceSurface(const UEdGraphPin* Pin, FMutableGraphGenerationContext & GenerationContext);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceTable.h` (Private)


#### Free symbols / members of external scopes

- L26 _prototype_ `bool GenerateTableColumn(const UCustomizableObjectNodeTable* TableNode, const UEdGraphPin* Pin, UE::Mutable::Private::Ptr<UE::Mutable::Private::FTable> MutableTable, const FString& DataTableColumnName, const FProperty* ColumnProperty, const FMutableSourceMeshData& BaseMeshData, FMutableGraphGenerationContext& GenerationContext);` — @param TableNode @param Pin @param MutableTable @param DataTableColumnName @param TableProperty @param BaseMeshData @param GenerationContext @return
- L44 _prototype_ `bool FillTableColumn(const UCustomizableObjectNodeTable* TableNode, UE::Mutable::Private::Ptr<UE::Mutable::Private::FTable> MutableTable, const FString& ColumnName, const FString& RowName, uint32 RowId, uint8* CellData, const FProperty* ColumnProperty, const FMutableSourceMeshData& BaseMeshData, FMutableGraphGenerationContext& GenerationContext);` — @param TableNode @param MutableTable @param ColumnName @param TableProperty @param RowName @param RowIdx @param CellData @param Property @param BaseMeshData @param GenerationContext @return
- L49 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::FTable> GenerateMutableSourceTable(const UDataTable* DataTable, const UCustomizableObjectNodeTable* TableNode, FMutableGraphGenerationContext& GenerationContext);`
- L52 _prototype_ `void GenerateTableParameterUIData(const UDataTable* DataTable, const UCustomizableObjectNodeTable* TableNode, FMutableGraphGenerationContext& GenerationContext);` — Generates a new FParameterUIData for a new table parameter. Also, adds the UIData to the parameters map.
- L55 _prototype_ `UDataTable* GetDataTable(const UCustomizableObjectNodeTable* TableNode, FMutableGraphGenerationContext& GenerationContext);` — Gets the data table needed during the compilation process
- L60 _prototype_ `TArray<FName> GetRowsToCompile(const UDataTable& DataTable, const UCustomizableObjectNodeTable& TableNode, FMutableGraphGenerationContext& GenerationContext, TArray<uint32>& OutRowIds);` — Gets all the rows of a data table that are going to be compiled. Some rows can be disabled with a bool column or an asset version system @OutRowIds Deterministic Ids for each row. Used to Add, Get, and Set cell data @return Array with all the names of the rows that are going to be compiled
- L63 _prototype_ `UDataTable* GenerateDataTableFromStruct(const UCustomizableObjectNodeTable* TableNode, FMutableGraphGenerationContext& GenerationContext);` — Generates a Data Table from the Data Tables referenced in a Script Struct
- L66 _prototype_ `bool GenerateNoneRow(const UCustomizableObjectNodeTable& TableNode, const UEdGraphPin* Pin, const FString& ColumnName, UE::Mutable::Private::Ptr<UE::Mutable::Private::FTable> MutableTable, FMutableGraphGenerationContext& GenerationContext);` — Generates and populates the "None" row for each column.
- L69 _prototype_ `void LogRowGenerationMessage(const UCustomizableObjectNodeTable* TableNode, const UDataTable* DataTable, FMutableGraphGenerationContext& GenerationContext, const FString& Message, const FString& RowName);` — This method adds the original Data Table(s) of the processed row at the end of the log message when the data table is a Composite Data table.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GenerateMutableSource/GenerateMutableSourceTransform.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeMatrix> GenerateMutableSourceTransform(const UEdGraphPin* Pin, FMutableGraphGenerationContext& GenerationContext);` — Convert a CustomizableObject Source Graph into a mutable source graph.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/GraphTraversal.h` (Private)


#### Free symbols / members of external scopes

- L25 _prototype_ `TArray<UEdGraphPin*> FollowPinArray(const UEdGraphPin& Pin, bool bIgnoreOrphan = false, bool* bOutCycleDetected = nullptr);` — Follow the given pin returning its connected pin. - Skips all orphan pins. - Follows External Pin and Reroute nodes. @param Pin Pin to follow. @param bIgnoreOrphan If true, it will not follow orphan pins. @param bOutCycleDetected If provided, it will set to true if a cycle has been found.
- L35 _prototype_ `TArray<UEdGraphPin*> FollowInputPinArray(const UEdGraphPin& Pin, bool* bOutCycleDetected = nullptr);` — Follow the given input pin returning the output connected pin. - Skips all orphan pins. - Follows External Pin nodes. @param Pin Pin to follow. @param bOutCycleDetected If provided, it will set to true if a cycle has been found. @return Connected pins.
- L38 _prototype_ `UEdGraphPin* FollowInputPin(const UEdGraphPin& Pin, bool* bOutCycleDetected = nullptr);` — Non-array version of FollowInputPinArray. The pin can only have one connected pin.
- L49 _prototype_ `TArray<UEdGraphPin*> FollowOutputPinArray(const UEdGraphPin& Pin, bool* bOutCycleDetected = nullptr);` — Follow the given input output returning the input connected pin. - Skips all orphan pins. - Follows External Pin nodes. - It will only follow External Pin nodes of loaded CO (i.e., Expose Pin nodes of CO which are NOT loaded will not be found)! @param Pin Pin to follow. @param bOutCycleDetected If provided, it will set to true if a cycle has been found. @return Connected pins.
- L52 _prototype_ `UEdGraphPin* FollowOutputPin(const UEdGraphPin& Pin, bool* CycleDetected = nullptr);` — Non-array version of FollowOutputPinArray. The pin can only have one connected pin.
- L56 _prototype_ `TArray<UEdGraphPin*> ReverseFollowPinArray(const UEdGraphPin& Pin, bool bIgnoreOrphan = false, bool* bOutCycleDetected = nullptr);` — See FollowPinArray. Given a pin, follow it in reverse (through the owning node instead of the linked pins).
- L59 _prototype_ `UCustomizableObjectNodeObject* GetRootNode(const UCustomizableObject* Object);` — Returns the root Object Node of the Customizable Object's graph
- L63 _prototype_ `bool GetParentsUntilRoot(const UCustomizableObject* Object, TArray<UCustomizableObjectNodeObject*>& ArrayNodeObject, TArray<const UCustomizableObject*>& ArrayCustomizableObject);` — Return in ArrayNodeObject the roots nodes in each Customizable Object graph until the whole root node is found (i.e. the one with parent = nullptr) return false if a cycle is found between Customizable Objects
- L66 _prototype_ `bool HasCandidateAsParent(UCustomizableObjectNodeObject* Node, UCustomizableObject* ParentCandidate);` — Returns true if the Candidate is parent of the current Customizable Object
- L73 _prototype_ `UCustomizableObject* GetFullGraphRootObject(const UCustomizableObjectNodeObject* Node, TArray<const UObject*>& VisitedObjects);` — Return the full graph Customizable Object root of the given node. @param Node The CO Node we want to get its root CO @param VisitedObjects List of objects used to record the search path already taken. It is used to determine if a cycle has been found. return The root CO. It can be null if a cycle has been found.
- L75 _namespace_ `namespace GraphTraversal`
- L80 _prototype_ `UCustomizableObject* GetObject(const UCustomizableObjectNode& Node);` (scope `GraphTraversal`) — Return Customizable Object of the given node. Returns null if the Node belongs to a Macro graph
- L87 _prototype_ `UCustomizableObject* GetRootObject(UCustomizableObject* ChildObject, TArray<const UObject*>* OutVisitedObjects = nullptr);` (scope `GraphTraversal`) — Provided a CO object it provides the root CO it is connected. In other words : it returns the root of the entire mutable graph. @param InObject Customizable object whose root CO we are asking for. @return The CO that is the root of the provided Customizable Object. It can be equal to InObject if the provided object does not have any parent.
- L88 _prototype_ `const UCustomizableObject* GetRootObject(const UCustomizableObject* ChildObject, TArray<const UObject*>* OutVisitedObjects = nullptr);` (scope `GraphTraversal`)
- L91 _prototype_ `UCustomizableObjectNodeObject* GetFullGraphRootNode(const UCustomizableObject* Object, TArray<const UCustomizableObject*>& VisitedObjects);` (scope `GraphTraversal`) — Return the full graph Customizable Object Node root of the node given as parameter
- L101 _prototype_ `void VisitNodes(UCustomizableObjectNode& StartNode, const TFunction<void(UCustomizableObjectNode&)>& VisitFunction, const TMultiMap<FGuid, UCustomizableObjectNodeObject*>* ObjectGroupMap = nullptr, TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr);` (scope `GraphTraversal`) — From the StartNode visit all connected nodes in the hierarchy. @param StartNode Node to start the visit. @param VisitFunction Called for each UCustomizableObjectNode node found. Order is not guaranteed. @param ObjectGroupMap Key is the Object Group node id, values are the attached Child Object nodes. Used to prune the traversal. @param MacroContext Keeps track of the macro context when going through macros
- L108 _prototype_ `const UEdGraphPin* FindIOPinSourceThroughMacroContext(const UEdGraphPin& Pin, TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr);` (scope `GraphTraversal`) — Returns a pin linked to the original pin. This function goes through Macro and Tunnel Nodes. @param Pin: Input/Output pin where the search starts. @param MacroContext: Copy of the current macro context.
- L112 _prototype_ `const UEdGraphPin* FindMeshBaseSource(const UEdGraphPin& Pin, const bool bOnlyLookForStaticMesh, TArray<const UCustomizableObjectNodeMacroInstance*> MacroContext = {});` — Given an output pin, return the output pin where the mesh is located.
- L116 _prototype_ `TMultiMap<FGuid, UCustomizableObjectNodeObject*> GetNodeGroupObjectNodeMapping(UCustomizableObject* Object);` — Return the mapping of Group Object Nodes to Child Object Nodes of the given hierarchy. @param Object Child or root Object to start the search from.
- L118 _namespace_ `namespace GraphTraversal`
- L121 _prototype_ `void GetAllObjectsInGraph(UCustomizableObject* Object, TSet<UCustomizableObject*>& OutObjects);` (scope `GraphTraversal`) — Returns all the Customizable Objects in a graph starting at the root object
- L125 _prototype_ `bool GetAllObjectsInGraphIncremental(UCustomizableObject* Object, TSet<UCustomizableObject*>& OutObjects);` (scope `GraphTraversal`) — Returns all the Customizable Objects in a graph starting at the root object. @return true if the full hierarchy could not be discovered due to UCustomizableObjects still async loading. Async loadings are called automatically.
- L128 _prototype_ `bool IsRootObject(const UCustomizableObject& Object);` (scope `GraphTraversal`) — Return ture if the given Customizable Object is Root Object (not a Child Object).
- L133 _prototype_ `void NodePinConnectionListChanged(const TArray<UEdGraphPin*>& Pins);` — For each given pin, call PinConnectionListChanged and NodeConnectionListChanged in the correct order. Order: For each node, first call all PinConnectionListChanged, then NodeConnectionListChanged.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/MutableMeshPreviewUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace MutableMeshPreviewUtils`
- L21 _prototype_ `USkeletalMesh* GenerateSkeletalMeshFromMutableMesh(const UE::Mutable::Private::FMesh*);` (scope `MutableMeshPreviewUtils`) — Method designed to provide a way of getting a USkeletalMesh based on the data found on a mutable mesh. @param InMutableMesh - The mutable mesh used as base for the generation of the USkeletalMesh @return - A new Skeletal mesh based on the provided data. It may be a nullptr if the conversion fails.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/MutableUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `TArray<FVector2f> GetUV(const USkeletalMesh& SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, const int32 UVIndex);` — Returns the mesh UV.
- L15 _prototype_ `TArray<FVector2f> GetUV(const UStaticMesh& StaticMesh, const int32 LODIndex, const int32 SectionIndex, const int32 UVIndex);` — Returns the mesh UV.
- L18 _prototype_ `bool HasNormalizedBounds(const FVector2f& Point);` — Returns if the given point is inside the 0-1 bounds.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeClipMeshWithMesh.h` (Private)


#### class `UCONodeClipMeshWithMesh`  
`class UCONodeClipMeshWithMesh : public UCustomizableObjectNode`  
_L20-61_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L32 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UCustomizableObjectNode interface
- L37 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L43 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = ClipMesh)` — Transform to apply to the clip mesh before clipping.
- L46 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = ClipMesh)`
- L49 _public member_ `FEdGraphPinReference BaseMeshPin;` — `UPROPERTY()`
- L52 _public member_ `FEdGraphPinReference ClipMeshPin;` — `UPROPERTY()`
- L55 _public member_ `FEdGraphPinReference OutputMeshPin;` — `UPROPERTY()`
- L60 _public member_ `OnTransformChanged TransformChangedDelegate;` — Delegate invoked each time the BoundingMeshTransform value gets modified

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeClipSkeletalMeshWithSkeletalMesh.h` (Private)


#### class `UCONodeClipSkeletalMeshWithSkeletalMesh`  
`class UCONodeClipSkeletalMeshWithSkeletalMesh : public UCustomizableObjectNode`  
_L21-75_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L28 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L29 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L30 _public prototype_ `virtual FText GetTooltipText() const override;`
- L33 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UCustomizableObjectNode interface
- L38 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L44 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = ClipMesh)` — Transform to apply to the clip mesh before clipping.
- L49 _public member_ `OnTransformChanged TransformChangedDelegate;` — Delegate invoked each time the MeshTransform value gets modified
- L52 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = ClipMesh)`
- L55 _public member_ `FEdGraphPinReference BaseSkeletalMeshPin;` — `UPROPERTY()`
- L58 _public member_ `FEdGraphPinReference ClipSkeletalMeshPin;` — `UPROPERTY()`
- L61 _public member_ `FEdGraphPinReference OutputSkeletalMeshPin;` — `UPROPERTY()`
- L64 _public member_ `TObjectPtr<USkeletalMesh> PreviewMesh;` — `UPROPERTY(EditAnywhere, Category= PreviewMesh)`
- L66 _public member_ `OnPreviewMeshChanged PreviewMeshChangedDelegate;`
- L70 _public member_ `uint32 PreviewMeshLOD = 0;` — `UPROPERTY(EditAnywhere, Category= PreviewMesh)` — Determines the LOD to be used when rendering the preview mesh.
- L74 _public member_ `int32 PreviewMeshSection = -1;` — `UPROPERTY(EditAnywhere, Category= PreviewMesh, meta=(ClampMin=-1))` — Determines the section to be used when rendering the preview mesh. A value of -1 will make the preview show all mesh sections

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(OnPreviewMeshChanged, UCustomizableObjectNode&, FTransform*, const UEdGraphPin&);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(OnPreviewMeshChanged, UCustomizableObjectNode&, FTransform*, const UEdGraphPin&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeComponentSkeletalMesh.h` (Private)


#### class `UCONodeComponentSkeletalMeshMaterialPinData`  
`class UCONodeComponentSkeletalMeshMaterialPinData : public UCustomizableObjectNodePinData`  
_L18-26_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodePinData`
- L25 _public member_ `FName TargetMaterialSlotName;` — `UPROPERTY(EditAnywhere, Category = NoCategory)`

#### class `UCONodeComponentSkeletalMeshPinRemapper`  
`class UCONodeComponentSkeletalMeshPinRemapper : public UCustomizableObjectNodeRemapPins`  
_L31-39_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPins`
- L36 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin, const uint32 OldPinInex, const uint32 NewPinIndex) const;`
- L38 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;`

#### enum `ECustomizableObjectSelectionOverride`  
`enum class ECustomizableObjectSelectionOverride : uint8`  
_L43-48_
- reflection: `UENUM()`
- L45 _public enumerator_ `NoOverride = 0 UMETA(DisplayName = "No Override")`
- L46 _public enumerator_ `Disable = 1 UMETA(DisplayName = "Disable" )`
- L47 _public enumerator_ `Enable = 2 UMETA(DisplayName = "Enable" )`

#### class `UCONodeComponentSkeletalMesh`  
`class UCONodeComponentSkeletalMesh : public UCustomizableObjectNodeComponent`  
_L55-113_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeComponent`
- L62 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UEdGraphNode interface
- L63 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L66 _public prototype_ `virtual bool IsSingleOutputNode() const override;` — UCustomizableObjectNode interface
- L68 _public prototype_ `virtual bool HasPinViewer() const override;`
- L69 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L70 _public prototype_ `virtual void AddPinFromUI() override;`
- L71 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L73 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L74 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L75 _public prototype_ `virtual bool ShouldPinViewerShowPinEditableName(const UEdGraphPin& Pin) const override;`
- L76 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L77 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L78 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L81 _public prototype_ `virtual TArray<FName> GetPinAllowedSubTypes(const UEdGraphPin& Pin) const override;` — Override / Overlay pin configuration
- L84 _public prototype_ `FEdGraphPinReference GetOverlayMaterialAssetPin() const;` — Own interface
- L87 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L90 _private prototype_ `UEdGraphPin* CreateMaterialSlotPin(const FName& PinSubCategory, UCONodeComponentSkeletalMeshMaterialPinData* InPinData);`
- L92 _private prototype_ `bool IsMaterialSlotPin(const UEdGraphPin& Pin) const;`
- L103 _public member_ `TObjectPtr<USkeletalMesh> ReferenceSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = ComponentMesh)` — All the Skeletal Meshes generated for this component will use the Reference Skeletal Mesh properties for everything Mutable doesn't create or modify. This includes data like LOD distances, Physics properties, Bounding Volumes, Base Skeleton, and more. The Reference Skeletal Mesh can be used as a placeholder mesh when there are too many actors or in situations of stress where the generation of the Skeletal Mesh might take a few seconds to complete.
- L106 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`
- L109 _public member_ `FEdGraphPinReference OverlayMaterialPin;` — `UPROPERTY()`
- L112 _public member_ `TArray<FEdGraphPinReference> MaterialSlotPins;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeExternalOperation.h` (Private)


#### class `UCONodeExternalOperation`  
`class UCONodeExternalOperation : public UCustomizableObjectNode`  
_L11-36_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L17 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L18 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L22 _public prototype_ `virtual bool IsLoaded() const override;`
- L25 _public member_ `FInstancedStruct OperationInstancedStruct;` — `UPROPERTY()`
- L28 _public member_ `TArray<FEdGraphPinReference> InputPins;` — `UPROPERTY()`
- L31 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`
- L35 _public member_ `FText CachedOperationName;` — `UPROPERTY()` — In case of the operation not being loaded, the node uses this cached name so we can at least show the user which operation it was.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeExternalOperationDetails.h` (Private)


#### class `FCONodeExternalOperationDetails`  
`class FCONodeExternalOperationDetails : public IDetailCustomization`  
_L12-23_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L19 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L22 _private member_ `TSharedPtr<IDetailLayoutBuilder> DetailBuilderPtr;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeExternalTypeParameter.h` (Private)


#### class `UCONodeExternalTypeParameter`  
`class UCONodeExternalTypeParameter : public UCustomizableObjectNodeParameter`  
_L15-40_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeParameter`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L24 _public prototype_ `virtual bool IsLoaded() const override;` — UCustomizableObjectNode interface
- L25 _public prototype_ `virtual bool IsAffectedByLOD() const override;`
- L28 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeParameter interface
- L29 _public prototype_ `virtual FText GetCategoryFriendlyName() const override;`
- L32 _public member_ `FInstancedStruct DefaultValue;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (MutableExternalType))`
- L36 _public member_ `mutable FName CachedType;` — `UPROPERTY()` — In case of the operation not being loaded, the node uses this cached name so we can at least show the user which type it was.
- L39 _public member_ `mutable FText CachedFriendlyName;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeMaterialBreak.h` (Private)


#### class `UCONodeMaterialBreakParameterPinData`  
`class UCONodeMaterialBreakParameterPinData : public UCustomizableObjectNodePinData`  
_L16-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- L25 _public member_ `int32 LayerIndex = -1;` — `UPROPERTY(EditAnywhere, Category = NoCategory)` — Layer index of this parameter inside a Layered Material. -1 if the material does not contain layers.
- L28 _public member_ `FName ParameterName;` — `UPROPERTY()`
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Handle change in the LayerIndex property @param PropertyChangedEvent The Property Change Event

#### class `UCONodeMaterialBreak`  
`class UCONodeMaterialBreak : public UCustomizableObjectNode`  
_L39-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L46 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L47 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L48 _public prototype_ `virtual FText GetTooltipText() const override;`
- L51 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L52 _public prototype_ `virtual TSharedPtr<IDetailsView> CustomizePinDetails(const UEdGraphPin& Pin) const override;`
- L53 _public prototype_ `virtual bool HasPinViewer() const override;`
- L54 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L55 _public prototype_ `virtual void AddPinFromUI() override;`
- L56 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L57 _public prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L58 _public prototype_ `virtual TArray<FName> GetAllowedPinViewerCreationTypes() const override;`
- L59 _public prototype_ `virtual TArray<FName> GetPinAllowedTypes(const UEdGraphPin& Pin) const override;`
- L62 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;` — UCustomizableObjectNode Interface : Editable area of the pin name management
- L63 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L64 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L65 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L68 _public prototype_ `FName GetPinParameterName(const UEdGraphPin& Pin) const;` — Own interface
- L69 _public prototype_ `int32 GetPinParameterLayerIndex(const UEdGraphPin& Pin) const;`
- L72 _public member_ `FEdGraphPinReference MaterialPinRef;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeMaterialConstant.h` (Private)


#### class `UCONodeMaterialConstant`  
`class UCONodeMaterialConstant : public UCustomizableObjectNode`  
_L14-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L21 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L25 _public member_ `TSoftObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Value of the Node.
- L28 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L30 _public prototype_ `virtual FText GetTooltipText() const override;`
- L33 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L36 _public member_ `FEdGraphPinReference MaterialPin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeMaterialModify.h` (Private)


#### enum `EMaterialModifyUVLayoutMode`  
`enum class EMaterialModifyUVLayoutMode`  
_L18-24_
- reflection: `UENUM()`
- desc: Image Pin, UV Layout Mode.
- L21 _public enumerator_ `Ignore` — Texture should not be transformed by any layout. These textures will not be reduced automatically for LODs.
- L23 _public enumerator_ `Index` — User specified UV Index.

#### class `UCONodeMaterialModifyParameterPinData`  
`class UCONodeMaterialModifyParameterPinData : public UCustomizableObjectNodePinData`  
_L29-58_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodePinData`
- desc: Base class for all Material Parameters.
- L38 _public member_ `int32 LayerIndex = -1;` — `UPROPERTY(EditAnywhere, Category = NoCategory)` — Layer index of this parameter inside a Layered Material. -1 if the material does not contain layers.
- L41 _public member_ `FName ParameterName;` — `UPROPERTY()`
- L47 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Handle change in the LayerIndex property @param PropertyChangedEvent The Property Change Event
- L50 _public function_ `virtual void Copy(const UCustomizableObjectNodePinData& Other) override`

#### class `UCONodeMaterialModifyTextureParamPinData`  
`class UCONodeMaterialModifyTextureParamPinData : public UCONodeMaterialModifyParameterPinData`  
_L65-97_
- reflection: `UCLASS()`
- inherits: `UCONodeMaterialModifyParameterPinData`
- desc: PinData object representing pins of the PC_Texture type.
- L71 _public function_ `virtual void Copy(const UCustomizableObjectNodePinData& Other) override`
- L83 _public member_ `constexpr static int32 UV_LAYOUT_IGNORE = -1;`
- L86 _public member_ `EMaterialModifyUVLayoutMode UVLayoutMode = EMaterialModifyUVLayoutMode::Ignore;` — `UPROPERTY(EditAnywhere, Category = NoCategory)`
- L90 _public member_ `int32 UVLayout = -2;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (EditCondition = "UVLayoutMode == EMaterialModifyUVLayoutMode::Index", EditConditionHides))` — Index of the UV channel that will be used with this image. It is necessary to apply the proper layout transformations to it.
- L96 _public member_ `TSoftObjectPtr<UTexture2D> ReferenceTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = NoCategory)` — Reference Texture used to decide the texture properties of the mutable-generated textures connected to this material. If null, it will try to be guessed at compile time from the graph.

#### class `UCONodeMaterialModifyPassthroughTextureParamPinData`  
`class UCONodeMaterialModifyPassthroughTextureParamPinData : public UCONodeMaterialModifyParameterPinData`  
_L103-106_
- reflection: `UCLASS()`
- inherits: `UCONodeMaterialModifyParameterPinData`
- desc: PinData object representing pins of the PC_PassthroughTexture type.

#### class `UCONodeMaterialModifyScalarParamPinData`  
`class UCONodeMaterialModifyScalarParamPinData : public UCONodeMaterialModifyParameterPinData`  
_L113-116_
- reflection: `UCLASS()`
- inherits: `UCONodeMaterialModifyParameterPinData`
- desc: PinData object representing pins of the PC_Float type.

#### class `UCONodeMaterialModifyColorParamPinData`  
`class UCONodeMaterialModifyColorParamPinData : public UCONodeMaterialModifyParameterPinData`  
_L123-126_
- reflection: `UCLASS()`
- inherits: `UCONodeMaterialModifyParameterPinData`
- desc: PinData object representing pins of the PC_Color type.

#### class `UCONodeMaterialModify`  
`class UCONodeMaterialModify : public UCustomizableObjectNode`  
_L130-176_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L137 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L138 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L139 _public prototype_ `virtual FText GetTooltipText() const override;`
- L143 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L144 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L148 _public prototype_ `virtual TSharedPtr<IDetailsView> CustomizePinDetails(const UEdGraphPin& Pin) const override;` — UCustomizableObjectNode interface
- L149 _public prototype_ `virtual bool HasPinViewer() const override;`
- L150 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L151 _public prototype_ `virtual void AddPinFromUI() override;`
- L152 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L153 _public prototype_ `virtual TArray<FName> GetAllowedPinViewerCreationTypes() const override;`
- L154 _public prototype_ `virtual TArray<FName> GetPinAllowedTypes(const UEdGraphPin& Pin) const override;`
- L157 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;` — Own Interface : Editable area of the pin name management
- L158 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L159 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L160 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L163 _public prototype_ `FName GetPinParameterName(const UEdGraphPin& Pin) const;` — Own interface
- L164 _public prototype_ `int32 GetPinParameterLayerIndex(const UEdGraphPin& Pin) const;`
- L165 _public prototype_ `TSoftObjectPtr<UTexture2D> GetTexturePinParameterReferenceTexture(const UEdGraphPin& Pin) const;`
- L166 _public prototype_ `int32 GetImagePinParameterUVIndex(const UEdGraphPin& Pin) const;`
- L167 _public prototype_ `void GetMaterialTextureParameterPins(TArray<FEdGraphPinReference>& OutTextureParameterPins) const;`
- L172 _public member_ `FLayoutSettings UVPackagingSettings[4];` — `UPROPERTY(Category="Layout Settings", EditAnywhere, DisplayName="UV Packaging Settings")` — Settings used to define the maximum number of blocks the Layouts will have.The number of blocks and the reference textures are used to define the final texture size of runtime generated textures.
- L175 _public member_ `FEdGraphPinReference MaterialPinRef;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeMaterialSwitch.h` (Private)


#### class `UCONodeMaterialSwitch`  
`class UCONodeMaterialSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodeSwitch interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeMaterialVariation.h` (Private)


#### class `UCONodeMaterialVariation`  
`class UCONodeMaterialVariation : public UCustomizableObjectNodeVariation`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L17 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeModifierEditSkeletalMeshSection.h` (Private)


#### class `UCustomizableObjectNodeEditMaterialPinEditImageData`  
`class UCustomizableObjectNodeEditMaterialPinEditImageData : public UCustomizableObjectNodePinData`  
_L25-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- desc: Additional data for the Parent Texture Parameter to edit pin.
- L33 _public member_ `FNodeMaterialParameterId ImageParamId;` — `UPROPERTY()` — Parameter FGuid + Layer Index
- L36 _public member_ `FEdGraphPinReference PinMask;` — `UPROPERTY()`
- L39 _public member_ `FGuid ImageId_DEPRECATED;` — `UPROPERTY()`

#### class `UCONodeModifierEditSkeletalMeshSection`  
`class UCONodeModifierEditSkeletalMeshSection : public UCustomizableObjectNodeModifierEditLayoutBlocks`  
_L44-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierEditLayoutBlocks`
- L52 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L53 _public prototype_ `virtual FText GetTooltipText() const override;`
- L56 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L57 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L58 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L59 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L60 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L61 _public prototype_ `virtual bool HasPinViewer() const override;`
- L66 _public prototype_ `virtual void SetLayoutIndex(const int32 LayoutIndex);`
- L71 _public prototype_ `const UEdGraphPin* GetUsedImageMaskPin(const FNodeMaterialParameterId& ImageId) const;` — Returns the Image mask pin of the given Image that will be edited. @returns Always returns a valid pin if EditsImage(const FGuid&) returns true.
- L77 _private member_ `TMap<FNodeMaterialParameterId, FEdGraphPinReference> PinsParameterMap_DEPRECATED;` — `UPROPERTY()` — Deprecated properties
- L80 _private member_ `TMap<FGuid, FEdGraphPinReference> PinsParameter_DEPRECATED;` — `UPROPERTY()`
- L83 _private member_ `TArray<FCustomizableObjectNodeEditMaterialImage> Images_DEPRECATED;` — `UPROPERTY()`
- L87 _private member_ `TArray<int32> Blocks_DEPRECATED;` — `UPROPERTY()` — Old layout blocks to patch. Now in parent class.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeModifierExtendSkeletalMeshSection.h` (Private)


#### class `UCONodeModifierExtendSkeletalMeshSection`  
`class UCONodeModifierExtendSkeletalMeshSection : public UCONodeModifierSkeletalMeshSection`  
_L25-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCONodeModifierSkeletalMeshSection`
- L33 _public member_ `TArray<FString> Tags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnableTags)` — Tags enabled when the modifier is applied. Also used to decide what modifiers get applied to the data added by this node.
- L37 _public member_ `uint32 FirstLOD = 0;` — `UPROPERTY(EditAnywhere, Category = LOD, meta = (ClampMin = 0, ClampMax = 255))` — First LOD where the modifier is applied to.
- L42 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L43 _public prototype_ `virtual FText GetTooltipText() const override;`
- L46 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L47 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L48 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L49 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L50 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L51 _public prototype_ `virtual TArray<FString> GetEnableTags(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) override;`
- L52 _public prototype_ `virtual TArray<FString>* GetEnableTagsArray() override;`
- L53 _public prototype_ `virtual FString GetInternalTagDisplayName() override;`
- L56 _public prototype_ `UEdGraphPin* AddMeshPin() const;` — Own interface
- L57 _public prototype_ `UEdGraphPin* GetEnableTagsPin() const;`
- L59 _public prototype_ `TArray<UCustomizableObjectLayout*> GetLayouts() const;`
- L66 _private member_ `TObjectPtr<UCustomizableObject> ParentMaterialObject_DEPRECATED = nullptr;` — `UPROPERTY()`
- L69 _private member_ `FGuid ParentMaterialNodeId_DEPRECATED;` — `UPROPERTY()`
- L73 _private member_ `TMap<FNodeMaterialParameterId, FEdGraphPinReference> PinsParameterMap_DEPRECATED;` — `UPROPERTY()`
- L76 _private member_ `TMap<FGuid, FEdGraphPinReference> PinsParameter_DEPRECATED;` — `UPROPERTY()`
- L79 _private member_ `TArray<FCustomizableObjectNodeExtendMaterialImage> Images_DEPRECATED;` — `UPROPERTY()`
- L82 _private member_ `FEdGraphPinReference EnableTagsPinRef;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeModifierSkeletalMeshMerge.h` (Private)


#### class `UCONodeModifierMutableSkeletalMeshMerge`  
`class UCONodeModifierMutableSkeletalMeshMerge : public UCustomizableObjectNode`  
_L12-61_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L18 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L20 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L23 _public prototype_ `virtual bool IsAffectedByLOD() const override;` — UCustomizableObjectNode interface
- L24 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L25 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L26 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L27 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L28 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L33 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L37 _public prototype_ `FName GetParentSkeletalMeshName(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;` — Own interface
- L38 _public prototype_ `void SetParentSkeletalMeshName(const FName& InSkeletalMeshName);`
- L39 _public prototype_ `UEdGraphPin* GetParentSkeletalMeshNamePin() const;`
- L43 _private member_ `FName ParentSkeletalMeshName;` — `UPROPERTY()`
- L47 _public member_ `int32 NumLODs_DEPRECATED = 1;` — `UPROPERTY()`
- L50 _public member_ `TArray<FEdGraphPinReference> LODPins_DEPRECATED;` — `UPROPERTY()`
- L53 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`
- L56 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`
- L60 _private member_ `FEdGraphPinReference ParentSkeletalMeshNamePin;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeModifierSkeletalMeshSection.h` (Private)


#### class `UCONodeModifierSkeletalMeshSection`  
`class UCONodeModifierSkeletalMeshSection : public UCustomizableObjectNodeModifierBase`  
_L16-57_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UCustomizableObjectNodeModifierBase`
- L28 _public member_ `TObjectPtr<UMaterialInterface> ReferenceMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Reference material that defines the structure of the data to be extended. The Sections modified with this modifier are supposed to have the same texture parameters, but don't need to have exactly the ReferenceMaterial set.
- L32 _public member_ `TMap<FNodeMaterialParameterId, FEdGraphPinReference> PinsParameterMap;` — `UPROPERTY()` — Relates a Parameter id (and layer if is a layered material) to a Pin. Only used to improve performance.
- L37 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `virtual bool IsNodeOutDatedAndNeedsRefresh() override;` — UCustomizableObjectNode interface
- L45 _public prototype_ `bool UsesImage(const FNodeMaterialParameterId& ImageId) const;`
- L48 _public prototype_ `const UEdGraphPin* GetUsedImagePin(const FNodeMaterialParameterId& ImageId) const;`
- L51 _public prototype_ `int32 GetNumParameters(const EMaterialParameterType Type) const;`
- L52 _public prototype_ `FNodeMaterialParameterId GetParameterId(const EMaterialParameterType Type, const int32 ParameterIndex) const;`
- L53 _public prototype_ `FName GetParameterName(const EMaterialParameterType Type, const int32 ParameterIndex) const;`
- L54 _public prototype_ `static int32 GetParameterLayerIndex(const UMaterialInterface* InMaterial, const EMaterialParameterType Type, const int32 ParameterIndex);`
- L55 _public prototype_ `int32 GetParameterLayerIndex(const EMaterialParameterType Type, const int32 ParameterIndex) const;`
- L56 _public prototype_ `FText GetParameterLayerName(const EMaterialParameterType Type, const int32 ParameterIndex) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeModifierTransformWithBone.h` (Private)


#### class `UCONodeModifierTransformWithBone`  
`class UCONodeModifierTransformWithBone : public UCustomizableObjectNodeModifierBase`  
_L18-49_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeModifierBase`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L29 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L32 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;` — UCustomizableObjectNodeModifierBase interface
- L37 _public member_ `FString BoneName;` — `UPROPERTY(EditAnywhere, Category = Transform)` — Root bone used to filter vertices based on skinning weights. Vertices skinned to this bone or below will be transformed.
- L42 _public member_ `float ThresholdFactor = 0.05f;` — `UPROPERTY(EditAnywhere, Category = Transform, meta = (ClampMin = 0.0f, ClampMax = 1.0f))` — Vertex influences under this threshold will not be considered when filtering vertices. Percentage of total skin weight [0.0 , 1.0].
- L45 _public member_ `FEdGraphPinReference TransformPin;` — `UPROPERTY()`
- L48 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeRemoveMesh.h` (Private)


#### class `UCONodeRemoveMesh`  
`class UCONodeRemoveMesh : public UCustomizableObjectNode`  
_L15-41_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L28 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L31 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = RemoveOptions)`
- L34 _public member_ `FEdGraphPinReference BaseMeshPin;` — `UPROPERTY()`
- L37 _public member_ `FEdGraphPinReference RemoveMeshPin;` — `UPROPERTY()`
- L40 _public member_ `FEdGraphPinReference OutputMeshPin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshBreak_V2.h` (Private)


#### class `UCONodeSkeletalMeshBreakPinData_V2`  
`class UCONodeSkeletalMeshBreakPinData_V2 : public UCustomizableObjectNodePinData`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- L17 _public member_ `FName TargetMaterialSlotName;` — `UPROPERTY(EditAnywhere, Category = NoCategory)`

#### class `UCONodeSkeletalMeshBreak_V2`  
`class UCONodeSkeletalMeshBreak_V2 : public UCustomizableObjectNode`  
_L22-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L29 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L32 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L33 _public prototype_ `virtual FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L36 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L37 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L38 _public prototype_ `virtual bool HasPinViewer() const override;`
- L39 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L40 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L41 _public prototype_ `virtual void AddPinFromUI() override;`
- L42 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L43 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L44 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L47 _public member_ `FEdGraphPinReference InputPassthroughMesh;` — `UPROPERTY()`
- L50 _public member_ `TArray<FEdGraphPinReference> OutputMaterialPins;` — `UPROPERTY()`
- L54 _private prototype_ `bool IsMaterialOutputPin(const UEdGraphPin& Pin) const;`
- L56 _private prototype_ `bool CreateMaterialOutputPin(UCONodeSkeletalMeshBreakPinData_V2* InPinData);`
- L60 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshMake_V2.h` (Private)


#### class `UCONodeSkeletalMeshMake_V2`  
`class UCONodeSkeletalMeshMake_V2 : public UCustomizableObjectNode`  
_L13-48_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L19 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode
- L20 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;` — UCustomizableObjectNode
- L24 _public prototype_ `virtual void AddPinFromUI() override;`
- L25 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L26 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L31 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode
- L32 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L36 _private function_ `FString GetNameForLODPin(const int32& InIndex) const`
- L44 _public member_ `TArray<FEdGraphPinReference> LODPins;` — `UPROPERTY()`
- L47 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshMerge.h` (Private)


#### class `UCONodeSkeletalMeshMerge`  
`class UCONodeSkeletalMeshMerge : public UCustomizableObjectNode`  
_L11-36_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L18 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L28 _public member_ `FEdGraphPinReference BaseSkeletalMeshPin;` — `UPROPERTY()`
- L31 _public member_ `FEdGraphPinReference ToAddSkeletalMeshPin;` — `UPROPERTY()`
- L34 _public member_ `FEdGraphPinReference SkeletalMeshOutputPin;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshModify.h` (Private)


#### class `UCONodeMutableSkeletalMeshModifySlotPinData`  
`class UCONodeMutableSkeletalMeshModifySlotPinData : public UCustomizableObjectNodePinData`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodePinData`
- desc: Base class for all skeletal mesh slot pins.
- L19 _public member_ `FName SlotName;` — `UPROPERTY()`

#### class `UCONodeSkeletalMeshModify`  
`class UCONodeSkeletalMeshModify : public UCustomizableObjectNode`  
_L24-58_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `virtual FText GetTooltipText() const override;`
- L35 _public prototype_ `virtual TSharedPtr<IDetailsView> CustomizePinDetails(const UEdGraphPin& Pin) const override;` — UCustomizableObjectNode interface
- L36 _public prototype_ `virtual bool HasPinViewer() const override;`
- L37 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L38 _public prototype_ `virtual void AddPinFromUI() override;`
- L39 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L40 _public prototype_ `virtual bool CanPinBeHidden(const UEdGraphPin& Pin) const override;`
- L43 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L44 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L48 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;` — Own Interface : Editable area of the pin name management
- L49 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L50 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L51 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L53 _public prototype_ `bool IsSlotPin(const UEdGraphPin& Pin) const;`
- L54 _public prototype_ `FName GetTargetSlotName(const UEdGraphPin& Pin) const;`
- L57 _public member_ `FEdGraphPinReference MutableSkeletalMeshPin;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshMorph.h` (Private)


#### class `UCONodeSkeletalMeshMorph`  
`class UCONodeSkeletalMeshMorph : public UCustomizableObjectNode`  
_L14-69_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L20 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L21 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;` — UCustomizableObjectNode interface
- L26 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L27 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L35 _public prototype_ `FName GetMorphTargetName(FMutableGraphGenerationContext& GenerationContext) const;` — Based on if something is connected to the input string pin for the Morph target name returns or the value from the connected string node or the value stored locally (used to store the value set when the target morph pin is not connected) @param GenerationContext The compilation generation context. @return The name of the target morph. May come from the locally stored value or the connected string node.
- L40 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L48 _public member_ `FEdGraphPinReference MeshPinReference;` — `UPROPERTY()` — Input skeletal mesh whose morph you want to interact with
- L54 _public member_ `FEdGraphPinReference MorphFactorPinReference;` — `UPROPERTY()` — The weight value to be applied onto the targetted morph
- L62 _private member_ `FString MorphTargetName;` — `UPROPERTY()` — The name of the morph target present in the provided skeletal mesh you want to interact with.
- L68 _private member_ `FEdGraphPinReference MorphTargetNamePinReference;` — `UPROPERTY()` — The name of the morph target you want to control

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshObjectBreak.h` (Private)


#### class `UCONodeSkeletalMeshObjectBreakPinData`  
`class UCONodeSkeletalMeshObjectBreakPinData : public UCustomizableObjectNodePinData`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- L17 _public member_ `FName TargetMaterialSlotName;` — `UPROPERTY(EditAnywhere, Category = NoCategory)`

#### class `UCONodeSkeletalMeshObjectBreak`  
`class UCONodeSkeletalMeshObjectBreak : public UCustomizableObjectNode`  
_L22-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L29 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L30 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L33 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L34 _public prototype_ `virtual FText GetTooltipText() const override;`
- L35 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L37 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L38 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L39 _public prototype_ `virtual bool HasPinViewer() const override;`
- L40 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L41 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L42 _public prototype_ `virtual void AddPinFromUI() override;`
- L43 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L44 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L45 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L48 _public member_ `FEdGraphPinReference InputPassthroughMesh;` — `UPROPERTY()`
- L51 _public member_ `TArray<FEdGraphPinReference> OutputMaterialPins;` — `UPROPERTY()`
- L55 _private prototype_ `bool IsMaterialOutputPin(const UEdGraphPin& Pin) const;`
- L57 _private prototype_ `bool CreateMaterialOutputPin(UCONodeSkeletalMeshObjectBreakPinData* InPinData);`
- L61 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshObjectMake.h` (Private)


#### class `UCONodeSkeletalMeshObjectMake`  
`class UCONodeSkeletalMeshObjectMake : public UCustomizableObjectNode`  
_L13-59_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L18 _public prototype_ `UCONodeSkeletalMeshObjectMake();`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode
- L26 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L27 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L28 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& InValue) override;`
- L29 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L36 _public prototype_ `const UCONodeSkeletalMeshMake_V2* GetConnectedMutableSkeletalMeshMakeNode(TArray<const UCustomizableObjectNodeMacroInstance*>& MacroContext) const;` — Get a pointer to the connected UCONodeMutableSkeletalMeshMake node. @param MacroContext The current macro stack @return A valid pointer if the node is connected, a null pointer otherwise.
- L38 _public prototype_ `FString GetSkeletalMeshName(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;`
- L41 _public member_ `uint16 NumLODs = 1;` — `UPROPERTY(EditAnywhere, Category=SkeletalMesh, meta = (ClampMin=1))`
- L44 _public member_ `FMutableLODSettings LODSettings;` — `UPROPERTY(EditAnywhere, Category = SkeletalMesh)`
- L48 _public member_ `FEdGraphPinReference MeshNamePin;` — `UPROPERTY()` — Name to use by the generated skeletal mesh object.
- L51 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`
- L54 _public member_ `FEdGraphPinReference PassthroughSkeletalMeshPin;` — `UPROPERTY()`
- L58 _private member_ `FString SkeletalMeshName = "De` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshReshape.h` (Private)


#### class `UCONodeSkeletalMeshReshape`  
`class UCONodeSkeletalMeshReshape : public UCustomizableObjectNode`  
_L15-82_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L34 _public member_ `FEdGraphPinReference BasePinReference;` — `UPROPERTY()` — Input skeletal mesh that will be reshaped.
- L38 _public member_ `FEdGraphPinReference BaseShapePinReference;` — `UPROPERTY()` — Input skeletal mesh describing the base shape used to sample the original geometry.
- L42 _public member_ `FEdGraphPinReference TargetShapePinReference;` — `UPROPERTY()` — Input skeletal mesh describing the destination shape for the reshape.
- L46 _public member_ `bool bReshapeVertices = true;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Enable the deformation of the vertices of the base mesh.
- L50 _public member_ `bool bRecomputeNormals = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (EditCondition = "bReshapeVertices"))` — Enable recompute normals after the reshape operation.
- L54 _public member_ `bool bApplyLaplacianSmoothing = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (EditCondition = "bReshapeVertices"))` — Enable laplacian smoothing to the result of the base mesh reshape.
- L58 _public member_ `bool bReshapePose = false;` — `UPROPERTY(EditAnywhere, Category = ReshapePose)` — Enable the deformation of the skeleton of the base mesh.
- L62 _public member_ `bool bReshapePhysics = false;` — `UPROPERTY(EditAnywhere, Category = ReshapePhysics)` — Enable the deformation of physics volumes of the base mesh.
- L65 _public member_ `FMeshReshapeColorUsage VertexColorUsage;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L69 _public member_ `EBoneDeformSelectionMethod SelectionMethod = EBoneDeformSelectionMethod::ONLY_SELECTED;` — `UPROPERTY(EditAnywhere, Category = ReshapePose, meta = (EditCondition = "bReshapePose"))` — Bone reshape selection method.
- L73 _public member_ `TArray<FName> BonesToDeform;` — `UPROPERTY(EditAnywhere, Category = ReshapePose, meta = (EditCondition = "bReshapePose"))` — Bones that participate in the skeleton reshape. Type the bone name as it appears in the source skeleton.
- L77 _public member_ `EBoneDeformSelectionMethod PhysicsSelectionMethod = EBoneDeformSelectionMethod::ONLY_SELECTED;` — `UPROPERTY(EditAnywhere, Category = ReshapePhysics, meta = (DisplayName = "Selection Method", EditCondition = "bReshapePhysics"))` — Physics body selection method.
- L81 _public member_ `TArray<FName> PhysicsBodiesToDeform;` — `UPROPERTY(EditAnywhere, Category = ReshapePhysics, meta = (EditCondition = "bReshapePhysics"))` — Bones whose physics bodies participate in the physics reshape. Type the bone name as it appears in the source skeleton.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshSection.h` (Private)


#### struct `FNodeMaterialParameterId`  
`struct FNodeMaterialParameterId`  
_L45-56_
- reflection: `USTRUCT()`
- desc: This struct helps us to identify a material parameter using its id and layer index in case of multimaterials When a multilayer material has the same material in multiple layer the parameter Id is not enough to identify a parameter we also need the its layer index.
- L50 _public member_ `FGuid ParameterId;` — `UPROPERTY()`
- L53 _public member_ `int32 LayerIndex = INDEX_NONE;` — `UPROPERTY()`
- L55 _public prototype_ `bool operator==(const FNodeMaterialParameterId& Other) const = default;`

#### class `UCustomizableObjectNodeMaterialRemapPinsByName`  
`class UCustomizableObjectNodeMaterialRemapPinsByName : public UCustomizableObjectNodeRemapPinsByName`  
_L72-81_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPinsByName`
- desc: Custom remap pins by name action. Remap pins by Texture Parameter Id.
- L76 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin) const override;`
- L78 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;`
- L80 _public prototype_ `bool HasSavedPinData(const UCustomizableObjectNode& Node, const UEdGraphPin &Pin) const;`

#### class `UCONodeSkeletalMeshSectionPinDataParameter`  
`class UCONodeSkeletalMeshSectionPinDataParameter : public UCustomizableObjectNodePinData`  
_L86-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- desc: Base class for all Material Parameters.
- L94 _public member_ `FNodeMaterialParameterId MaterialParameterId;` — `UPROPERTY()` — Parameter id + layer index
- L98 _public member_ `FGuid ParameterId_DEPRECATED;` — `UPROPERTY()` — Texture Parameter Id.
- L101 _public prototype_ `virtual bool IsDefault() const;` — Returns true if all properties are in its default state.

#### enum `ENodePinMode`  
`enum class ENodePinMode`  
_L107-111_
- reflection: `UENUM()`
- desc: Node pin mode. All pins set to EPinMode::Default will use this this mode.
- L109 _public enumerator_ `Mutable UMETA(ToolTip = "All Material Texture FParameters go through Mutable.")`
- L110 _public enumerator_ `Passthrough UMETA(DisplayName = "Object", ToolTip = "All Material Texture FParameters are not modified by Mutable.")`

#### enum `EPinMode`  
`enum class EPinMode`  
_L116-121_
- reflection: `UENUM()`
- desc: Image pin, pin mode.
- L118 _public enumerator_ `Default UMETA(DisplayName = "Node Defined", ToolTip = "Use node's \"Default Texture Parameter Mode\".")`
- L119 _public enumerator_ `Mutable UMETA(ToolTip = "The Material Texture FParameters goes through Mutable.")`
- L120 _public enumerator_ `Passthrough UMETA(DisplayName = "Object", ToolTip = "The Material Texture FParameters is not modified by Mutable.")`

#### enum `EUVLayoutMode`  
`enum class EUVLayoutMode`  
_L126-134_
- reflection: `UENUM()`
- desc: Image Pin, UV Layout Mode.
- L129 _public enumerator_ `FromMaterial` — Does not override the UV Index specified in the Material.
- L131 _public enumerator_ `Ignore` — Texture should not be transformed by any layout. These textures will not be reduced automatically for LODs.
- L133 _public enumerator_ `Index` — User specified UV Index.

#### class `UCONodeSkeletalMeshSection`  
`class UCONodeSkeletalMeshSection : public UCustomizableObjectNode`  
_L142-306_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L148 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L149 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L152 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L153 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L154 _public prototype_ `virtual FText GetTooltipText() const override;`
- L155 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L156 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L157 _public prototype_ `virtual void PostPasteNode() override;`
- L158 _public prototype_ `virtual bool CanConnect(const UEdGraphPin* InOwnedInputPin, const UEdGraphPin* InOutputPin, bool& bOutIsOtherNodeBlocklisted, bool& bOutArePinsCompatible) const override;`
- L161 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L162 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L163 _public prototype_ `virtual bool CanPinBeHidden(const UEdGraphPin& Pin) const override;`
- L164 _public prototype_ `virtual bool HasPinViewer() const override;`
- L165 _public prototype_ `virtual UCustomizableObjectNodeRemapPinsByName* CreateRemapPinsDefault() const override;`
- L166 _public function_ `virtual bool ProvidesCustomPinRelevancyTest() const override`
- L167 _public prototype_ `virtual bool IsPinRelevant(const UEdGraphPin* Pin) const override;`
- L168 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L169 _public prototype_ `virtual bool IsNodeOutDatedAndNeedsRefresh() override;`
- L170 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L171 _public prototype_ `virtual TSharedPtr<IDetailsView> CustomizePinDetails(const UEdGraphPin& Pin) const override;`
- L172 _public prototype_ `virtual TArray<FString> GetEnableTags(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) override;`
- L173 _public prototype_ `virtual TArray<FString>* GetEnableTagsArray() override;`
- L174 _public prototype_ `virtual FString GetInternalTagDisplayName() override;`
- L175 _public prototype_ `virtual TArray<UCustomizableObjectLayout*> GetLayouts() const;`
- L176 _public prototype_ `virtual UEdGraphPin* OutputPin() const;`
- L177 _public prototype_ `virtual UMaterialInterface* GetMaterial() const;`
- L178 _public prototype_ `virtual int32 GetNumParameters(EMaterialParameterType Type) const;`
- L179 _public prototype_ `virtual FNodeMaterialParameterId GetParameterId(EMaterialParameterType Type, int32 ParameterIndex) const;`
- L180 _public prototype_ `virtual FName GetParameterName(EMaterialParameterType Type, int32 ParameterIndex) const;`
- L181 _public prototype_ `virtual int32 GetParameterLayerIndex(EMaterialParameterType Type, int32 ParameterIndex) const;`
- L182 _public prototype_ `virtual FText GetParameterLayerName(EMaterialParameterType Type, int32 ParameterIndex) const;`
- L183 _public prototype_ `virtual bool HasParameter(const FNodeMaterialParameterId& ParameterId) const;`
- L184 _public prototype_ `virtual UEdGraphPin* GetParameterPin(EMaterialParameterType Type, int32 ParameterIndex) const;`
- L185 _public prototype_ `virtual UEdGraphPin* GetParameterPin(const FNodeMaterialParameterId& ParameterId) const;`
- L186 _public prototype_ `virtual bool IsImageMutableMode(int32 ImageIndex) const;`
- L187 _public prototype_ `virtual bool IsImageMutableMode(const UEdGraphPin& Pin) const;`
- L188 _public prototype_ `virtual UTexture2D* GetImageReferenceTexture(int32 ImageIndex) const;`
- L189 _public prototype_ `virtual UTexture2D* GetImageValue(int32 ImageIndex) const;`
- L190 _public prototype_ `virtual int32 GetImageUVLayout(int32 ImageIndex) const;`
- L191 _public prototype_ `virtual UEdGraphPin* GetMeshPin() const;`
- L192 _public prototype_ `virtual UEdGraphPin* GetMaterialAssetPin() const;`
- L193 _public prototype_ `virtual UEdGraphPin* GetEnableTagsPin() const;`
- L194 _public prototype_ `virtual bool RealMaterialDataHasChanged() const;`
- L195 _public prototype_ `virtual FPostImagePinModeChangedDelegate* GetPostImagePinModeChangedDelegate();`
- L199 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);`
- L201 _public prototype_ `static bool HasParameter(const UMaterialInterface* InMaterial, const FNodeMaterialParameterId& ParameterId);`
- L202 _public prototype_ `static int32 GetParameterLayerIndex(const UMaterialInterface* InMaterial, EMaterialParameterType Type, int32 ParameterIndex);`
- L206 _public member_ `int32 MaxLOD = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = AdvancedSettings)` — Max LOD to propagate this section to, when using automatic LODs.
- L209 _public member_ `TArray<FString> Tags;` — `UPROPERTY(EditAnywhere, Category = Tags)`
- L213 _private prototype_ `void SetImagePinMode(UEdGraphPin& Pin, EPinMode PinMode) const;` — Set the Pin Mode of a Texture Parameter Pin.
- L216 _private member_ `FPostImagePinModeChangedDelegate PostImagePinModeChangedDelegate;` — Delegate called when a Texture Parameter Pin Mode changes.
- L219 _private member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L222 _private member_ `ENodePinMode TextureParametersMode = ENodePinMode::Passthrough;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, DisplayName = "Default Texture Parameter Mode", Meta = (ToolTip = "All Mateiral Texture FParameters set to \"Node Defined\" will use this mode."))`
- L225 _private member_ `int32 MeshComponentIndex_DEPRECATED = 0;` — `UPROPERTY()`
- L228 _private member_ `FEdGraphPinReference InputMeshPin;` — `UPROPERTY()`
- L231 _private member_ `FEdGraphPinReference InputMaterialPin;` — `UPROPERTY()`
- L236 _public member_ `FName MeshComponentName_DEPRECATED;` — `UPROPERTY()` — Selects which Mesh component of the Instance this material belongs to
- L241 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> LastMeshNodeConnected;` — Last static or skeletal mesh connected. Used to remove the callback once disconnected.
- L244 _private member_ `static const TArray<EMaterialParameterType> ParameterTypes;` — List of material parameter types that are actually relevant to mutable.
- L249 _private member_ `TMap<FNodeMaterialParameterId, FEdGraphPinReference> PinsParameterMap;` — `UPROPERTY()` — Relates a Parameter id (key) (and layer if is a layered material) to a Pin (value). Only used to improve performance. If a deprecated pin and a non-deprecated pin have the same Parameter id, this the non-deprecated one prevails.
- L252 _private member_ `FEdGraphPinReference EnableTagsPinRef;` — `UPROPERTY()`
- L255 _private prototype_ `UCONodeSkeletalMeshSectionPinDataParameter* CreatePinData(EMaterialParameterType Type, int32 ParameterIndex);` — Create the pin data of the given parameter type.
- L258 _private prototype_ `void AllocateDefaultParameterPins(EMaterialParameterType Type);` — Allocate a pin for each parameter of the given type.
- L261 _private prototype_ `void SetDefaultMaterial();` — Set the default Material from the connected static or skeletal mesh.
- L264 _private prototype_ `FName GetPinName(EMaterialParameterType Type, int32 ParameterIndex) const;` — Format pin name.
- L267 _private prototype_ `static int32 GetExpressionTextureCoordinate(UMaterial* Material, const FGuid &ImageId);` — Returns the texture coordinate of the given Material Expression. Returns -1 if not found.
- L270 _private prototype_ `static FName NodePinModeToImagePinMode(ENodePinMode NodePinMode);` — Return the Pin Category given the node NodePinMode.
- L273 _private prototype_ `FName GetImagePinMode(EPinMode PinMode) const;` — Return the Pin Category given a PinMode.
- L276 _private prototype_ `FName GetImagePinMode(const UEdGraphPin& Pin) const;` — Return the Pin Category given a Pin.
- L279 _private prototype_ `int32 GetImageUVLayoutFromMaterial(int32 ImageIndex) const;` — Get the UV Layout Index defined in the Material.
- L286 _public member_ `FLayoutSettings UVPackagingSettings[4];` — `UPROPERTY(Category="Layout Settings", EditAnywhere, DisplayName="UV Packaging Settings")` — Settings used to define the maximum number of blocks the Layouts will have.The number of blocks and the reference textures are used to define the final texture size of runtime generated textures.
- L293 _private member_ `bool bDefaultPinModeMutable_DEPRECATED = false;` — `UPROPERTY()` — Set all pins to Mutable mode. Even so, each pin can override its behavior.
- L296 _private member_ `TArray<FCustomizableObjectNodeMaterialImage> Images_DEPRECATED;` — `UPROPERTY()`
- L299 _private member_ `TArray<FCustomizableObjectNodeMaterialVector> VectorParams_DEPRECATED;` — `UPROPERTY()`
- L302 _private member_ `TArray<FCustomizableObjectNodeMaterialScalar> ScalarParams_DEPRECATED;` — `UPROPERTY()`
- L305 _private member_ `TMap<FGuid, FEdGraphPinReference> PinsParameter_DEPRECATED;` — `UPROPERTY()`

#### class `UCONodeSkeletalMeshSectionPinDataImage`  
`class UCONodeSkeletalMeshSectionPinDataImage : public UCONodeSkeletalMeshSectionPinDataParameter`  
_L311-364_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCONodeSkeletalMeshSectionPinDataParameter`
- desc: Additional data for a Material Texture Parameter pin.
- L319 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L320 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L323 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodePinData interface
- L327 _public prototype_ `virtual void Copy(const UCustomizableObjectNodePinData& Other) override;` — Virtual function used to copy pin data when remapping pins.
- L330 _public prototype_ `virtual bool IsDefault() const override;` — UCustomizableObjectNodeMaterialPinParameter interface
- L334 _public prototype_ `void Init(UCONodeSkeletalMeshSection& InMeshSectionNode);` — Constructor parameters. Should always be called after a NewObject.
- L336 _public prototype_ `EPinMode GetPinMode() const;`
- L338 _public prototype_ `void SetPinMode(EPinMode InPinMode);`
- L343 _private member_ `EPinMode PinMode = EPinMode::Default;` — `UPROPERTY(EditAnywhere, Category = NoCategory, DisplayName = "Texture Parameter Mode")` — Image pin mode. If is not default, overrides the defined node behaviour.
- L346 _public member_ `constexpr static int32 UV_LAYOUT_IGNORE = -1;`
- L349 _public member_ `EUVLayoutMode UVLayoutMode = EUVLayoutMode::FromMaterial;` — `UPROPERTY(EditAnywhere, Category = NoCategory)`
- L353 _public member_ `int32 UVLayout = -2;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (EditCondition = "UVLayoutMode == EUVLayoutMode::Index", EditConditionHides))` — Index of the UV channel that will be used with this image. It is necessary to apply the proper layout transformations to it.
- L359 _public member_ `TObjectPtr<UTexture2D> ReferenceTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = NoCategory)` — Reference Texture used to decide the texture properties of the mutable-generated textures connected to this material. If null, it will try to be guessed at compile time from the graph.
- L363 _private member_ `TObjectPtr<UCONodeSkeletalMeshSection> NodeMaterial = nullptr;` — `UPROPERTY()`

#### class `UCONodeSkeletalMeshSectionPinDataVector`  
`class UCONodeSkeletalMeshSectionPinDataVector : public UCONodeSkeletalMeshSectionPinDataParameter`  
_L369-372_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCONodeSkeletalMeshSectionPinDataParameter`
- desc: Additional data for a Material Vector Parameter pin.

#### class `UCONodeSkeletalMeshSectionPinDataScalar`  
`class UCONodeSkeletalMeshSectionPinDataScalar : public UCONodeSkeletalMeshSectionPinDataParameter`  
_L377-380_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCONodeSkeletalMeshSectionPinDataParameter`
- desc: Additional data for a Material Float Parameter pin.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L18 _namespace_ `namespace ENodeTitleType`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPostImagePinModeChangedDelegate) USTRUCT() struct FNodeMaterialParameterId { GENERATED_BODY() UPROPERTY() FGuid ParameterId; UPROPERTY() int32 LayerIndex = INDEX_NONE; bool operator==(const FNodeMaterialParameterId& Other) const = default; };`
- L59 _function_ `inline uint32 GetTypeHash(const FNodeMaterialParameterId& Key)`
- L138 _prototype_ `FText EPinModeToText(EPinMode PinMode);` — Enum to FText.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshSectionInterface.h` (Private)


#### class `UCONodeSkeletalMeshSectionInterface`  
`class UCONodeSkeletalMeshSectionInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICONodeSkeletalMeshSectionInterface`  
`class ICONodeSkeletalMeshSectionInterface`  
_L19-31_
- L27 _public prototype_ `virtual TSoftObjectPtr<UMaterialInterface> GetMaterial() const PURE_VIRTUAL(UCustomizableObjectNodeMaterialInterface::GetMaterial, return {};);` — Returns the Unreal mesh (e.g., USkeletalMesh, UStaticMesh...).
- L30 _public prototype_ `virtual UEdGraphPin* GetMaterialPin() const PURE_VIRTUAL(UCustomizableObjectNodeMaterialInterface::GetMaterialPin, return {};);` — Returns the output Mesh pin associated to the given LODIndex and SectionIndex. Override.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshSectionSwitch.h` (Private)


#### class `UCONodeSkeletalMeshSectionSwitch`  
`class UCONodeSkeletalMeshSectionSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshSectionVariation.h` (Private)


#### enum `ECustomizableObjectNodeMaterialVariationType`  
`enum class ECustomizableObjectNodeMaterialVariationType : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Tag UMETA(DisplayName = "Tag")`
- L18 _public enumerator_ `State UMETA(DisplayName = "State")`

#### class `UCONodeSkeletalMeshSectionVariation`  
`class UCONodeSkeletalMeshSectionVariation : public UCustomizableObjectNodeVariation`  
_L23-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L29 _public member_ `ECustomizableObjectNodeMaterialVariationType Type = ECustomizableObjectNodeMaterialVariationType::Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L34 _private member_ `TArray<FCustomizableObjectMaterialVariation> Variations_DEPRECATED;` — `UPROPERTY()` — Deprecated properties
- L38 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L39 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L42 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface
- L43 _public prototype_ `virtual bool IsInputPinArray() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshTransformWithBone.h` (Private)


#### class `UCONodeSkeletalMeshTransformWithBone`  
`class UCONodeSkeletalMeshTransformWithBone : public UCustomizableObjectNode`  
_L17-48_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L33 _public member_ `FString BoneName;` — `UPROPERTY(EditAnywhere, Category = Transform)` — Root bone used to filter vertices based on skinning weights. Vertices skinned to this bone or below will be transformed.
- L38 _public member_ `float ThresholdFactor = 0.05f;` — `UPROPERTY(EditAnywhere, Category = Transform, meta = (ClampMin = 0.0f, ClampMax = 1.0f))` — Vertex influences under this threshold will not be considered when filtering vertices. Percentage of total skin weight [0.0 , 1.0].
- L41 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`
- L44 _public member_ `FEdGraphPinReference TransformPin;` — `UPROPERTY()`
- L47 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSkeletalMeshVariation.h` (Private)


#### class `UCONodeSkeletalMeshVariation`  
`class UCONodeSkeletalMeshVariation : public UCustomizableObjectNodeVariation`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeVariation`
- L17 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeSwitch.h` (Private)


#### class `UCONodeSwitch`  
`class UCONodeSwitch : public UCustomizableObjectNode`  
_L24-64_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `virtual FText GetTooltipText() const override;`
- L33 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L36 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L37 _public prototype_ `virtual void PostBackwardsCompatibleFixup() override;`
- L40 _public prototype_ `virtual FName GetCategory() const;` — Get the output pin category. Override.
- L43 _public prototype_ `virtual FString GetOutputPinName() const;` — Get the output pin name. Override.
- L48 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L53 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> LastNodeEnumParameterConnected;` — Last NodeEnumParameter connected. Used to remove the callback once disconnected.
- L57 _public member_ `FEdGraphPinReference SwitchParameterPinReference;` — `UPROPERTY()`
- L60 _public member_ `TArray<FEdGraphPinReference> SwitchPins;` — `UPROPERTY()`
- L63 _public member_ `FName PinType;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mutable` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L67 _prototype_ `const UCONodeSwitch* CastSwitch(const UEdGraphNode* Node, FName Type);`
- L68 _prototype_ `UCONodeSwitch* CastSwitch(UEdGraphNode* Node, FName Type);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeTransformInMesh.h` (Private)


#### class `UCONodeTransformInMesh`  
`class UCONodeTransformInMesh : public UCustomizableObjectNode`  
_L19-55_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L26 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L31 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _public prototype_ `virtual bool IsDeprecated() const override;`
- L37 _public member_ `FTransform BoundingMeshTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = BoundingMesh)` — Transform to apply to the bounding mesh before selecting for vertices to transform.
- L40 _public member_ `FEdGraphPinReference BaseMeshPin;` — `UPROPERTY()`
- L43 _public member_ `FEdGraphPinReference BoundingMeshPin;` — `UPROPERTY()`
- L46 _public member_ `FEdGraphPinReference TransformMeshPin;` — `UPROPERTY()`
- L49 _public member_ `FEdGraphPinReference OutputMeshPin;` — `UPROPERTY()`
- L54 _public member_ `OnTransformChanged TransformChangedDelegate;` — Delegate invoked each time the BoundingMeshTransform value gets modified

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CONodeTransformWithBone.h` (Private)


#### class `UCONodeTransformWithBone`  
`class UCONodeTransformWithBone : public UCustomizableObjectNode`  
_L20-57_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L28 _public prototype_ `virtual FText GetTooltipText() const override;`
- L31 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L32 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L37 _public member_ `FString BoneName;` — `UPROPERTY(EditAnywhere, Category = Transform)` — Root bone used to filter vertices based on skinning weights. Vertices skinned to this bone or below will be transformed.
- L42 _public member_ `float ThresholdFactor = 0.05f;` — `UPROPERTY(EditAnywhere, Category = Transform, meta = (ClampMin = 0.0f, ClampMax = 1.0f))` — Vertex influences under this threshold will not be considered when filtering vertices. Percentage of total skin weight [0.0 .. 1.0].
- L45 _public member_ `FEdGraphPinReference BaseMeshPin;` — `UPROPERTY()`
- L48 _public member_ `FEdGraphPinReference TransformPin;` — `UPROPERTY()`
- L51 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`
- L56 _public member_ `OnTransformChanged TransformChangedDelegate;` — Delegate invoked each time the BoundingMeshTransform value gets modified

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeAnimationPose.h` (Private)


#### class `UCustomizableObjectNodeAnimationPose`  
`class UCustomizableObjectNodeAnimationPose : public UCustomizableObjectNode`  
_L22-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L27 _public prototype_ `UCustomizableObjectNodeAnimationPose();`
- L30 _public member_ `TObjectPtr<UPoseAsset> PoseAsset;` — `UPROPERTY(EditAnywhere, Category=NoCategory)`
- L34 _public member_ `TObjectPtr<USkeletalMesh> ReferenceSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category=NoCategory)` — TODO Remove. Only used because poses are the diff from a Reference Skeleton. Once the pose is absolute remove this.
- L37 _public prototype_ `UEdGraphPin* GetInputMeshPin() const;`
- L38 _public prototype_ `UEdGraphPin* GetTablePosePin() const;`
- L39 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L40 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L44 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L45 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L48 _public prototype_ `static void StaticRetrievePoseInformation(UPoseAsset* PoseAsset, class USkeletalMesh* RefSkeletalMesh, TArray<FName>& OutArrayBoneName, TArray<FTransform>& OutArrayTransform);` — Retrieve the pose information from the PoseAsset

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorArithmeticOp.h` (Private)


#### enum `EColorArithmeticOperation`  
`enum class EColorArithmeticOperation : uint8`  
_L20-26_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `E_Add UMETA(DisplayName = "+")`
- L23 _public enumerator_ `E_Sub UMETA(DisplayName = "-")`
- L24 _public enumerator_ `E_Mul UMETA(DisplayName = "x")`
- L25 _public enumerator_ `E_Div UMETA(DisplayName = "/")`

#### class `UCustomizableObjectNodeColorArithmeticOp`  
`class UCustomizableObjectNodeColorArithmeticOp : public UCustomizableObjectNode`  
_L29-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L34 _public prototype_ `UCustomizableObjectNodeColorArithmeticOp();`
- L37 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L40 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L41 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L42 _public prototype_ `FText GetTooltipText() const override;`
- L43 _public function_ `bool ShouldOverridePinNames() const override`
- L46 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L49 _public function_ `UEdGraphPin* XPin() const` — First Operand
- L55 _public function_ `UEdGraphPin* YPin() const` — Second Operand
- L61 _public member_ `EColorArithmeticOperation Operation;` — `UPROPERTY(EditAnywhere, Category = ColorArithmeticOperation)`
- L64 _public function_ `virtual bool IsAffectedByLOD() const` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorConstant.h` (Private)


#### enum `ColorChannel`  
`enum class ColorChannel`  
_L25-31_
- L27 _public enumerator_ `RED`
- L28 _public enumerator_ `GREEN`
- L29 _public enumerator_ `BLUE`
- L30 _public enumerator_ `ALPHA`

#### class `SGraphNodeColorConstant`  
`class SGraphNodeColorConstant : public SCustomizableObjectNode`  
_L34-77_
- inherits: `SCustomizableObjectNode`
- desc: Class create color inputs in the NodeColorConstant
- L38 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeColorConstant)`
- L39 _public prototype_ `SLATE_END_ARGS();`
- L41 _public function_ `SGraphNodeColorConstant() : SCustomizableObjectNode()`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);` — Builds the SGraphNodeFloatConstant when needed
- L47 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;` — Overriden functions to build the SGraphNode widgets
- L48 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L49 _public function_ `virtual bool ShouldAllowCulling() const override`
- L52 _public prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Callbacks for the widget
- L53 _public prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;`
- L54 _public prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;`
- L59 _private prototype_ `void OnSpinBoxValueChanged(float Value, ColorChannel channel);` — Callback for the OnValueChanged of the SpinBox
- L62 _private prototype_ `void OnSpinBoxValueCommitted(float Value, ETextCommit::Type, ColorChannel channel);` — Callback for the OnValueCommited of the SpinBox
- L65 _private prototype_ `FReply OnColorPreviewClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Callback for the OnClicked of the ColorBox
- L70 _private member_ `UCustomizableObjectNodeColorConstant* NodeColorConstant = nullptr;` — Pointer to the NodeFloatconstant that owns this SGraphNode
- L73 _private member_ `FSpinBoxStyle WidgetStyle;` — Style for the SpinBox
- L76 _private member_ `TSharedPtr<SVerticalBox> ColorEditor;` — Pointer to store the color editors to manage the visibility

#### class `UCustomizableObjectNodeColorConstant`  
`class UCustomizableObjectNodeColorConstant : public UCustomizableObjectNode`  
_L80-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L86 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L87 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L88 _public prototype_ `virtual FText GetTooltipText() const override;`
- L92 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L93 _public function_ `virtual bool IsAffectedByLOD() const override`
- L94 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L97 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;` — Creates the SGraph Node widget for the Color Editor
- L100 _public member_ `FLinearColor Value = FLinearColor(1,1,1,1);` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, meta = (DontUpdateWhileEditing))`
- L103 _public member_ `bool bCollapsed = true;` — Determines if the Node is collapsed or not

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorFromFloats.h` (Private)


#### class `UCustomizableObjectNodeColorFromFloats`  
`class UCustomizableObjectNodeColorFromFloats : public UCustomizableObjectNode`  
_L20-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L25 _public prototype_ `UCustomizableObjectNodeColorFromFloats();`
- L28 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L31 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L32 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L33 _public prototype_ `FText GetTooltipText() const override;`
- L36 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L38 _public function_ `UEdGraphPin* RPin() const`
- L43 _public function_ `UEdGraphPin* GPin() const`
- L48 _public function_ `UEdGraphPin* BPin() const`
- L53 _public function_ `UEdGraphPin* APin() const`
- L59 _public function_ `virtual bool IsAffectedByLOD() const override` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorParameter.h` (Private)


#### class `UCustomizableObjectNodeColorParameter`  
`class UCustomizableObjectNodeColorParameter : public UCustomizableObjectNodeParameter`  
_L18-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter`
- L24 _public member_ `FLinearColor DefaultValue = FLinearColor(1, 1, 1, 1);` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, meta = (DontUpdateWhileEditing))`
- L27 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L30 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorSwitch.h` (Private)


#### class `UCustomizableObjectNodeColorSwitch`  
`class UCustomizableObjectNodeColorSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodeSwitch interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorToSRGB.h` (Private)


#### class `UCustomizableObjectNodeColorToSRGB`  
`class UCustomizableObjectNodeColorToSRGB : public UCustomizableObjectNode`  
_L17-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `FText GetTooltipText() const override;`
- L26 _public function_ `bool ShouldOverridePinNames() const override`
- L29 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L31 _public function_ `virtual bool IsAffectedByLOD() const`
- L34 _public prototype_ `UEdGraphPin* GetInputPin() const;` — Own interface
- L35 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L40 _private member_ `FEdGraphPinReference InputPin;` — `UPROPERTY()`
- L43 _private member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeColorVariation.h` (Private)


#### class `UCustomizableObjectNodeColorVariation`  
`class UCustomizableObjectNodeColorVariation : public UCustomizableObjectNodeVariation`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L22 _public member_ `TArray<FCustomizableObjectColorVariation> Variations_DEPRECATED;` — `UPROPERTY()` — Deprecated properties
- L25 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L28 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeComponent.h` (Private)


#### class `UCustomizableObjectNodeComponent`  
`class UCustomizableObjectNodeComponent : public UCustomizableObjectNode`  
_L16-50_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UCustomizableObjectNode`
- L22 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UEdGraphNode interface
- L23 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L25 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L28 _public prototype_ `virtual bool IsAffectedByLOD() const override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L30 _public prototype_ `virtual bool ShouldPinViewerShowPinEditableName(const UEdGraphPin& Pin) const override;`
- L31 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L32 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L33 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L36 _public prototype_ `FName GetComponentName(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;` — Own Interface
- L37 _public prototype_ `void SetComponentName(const FName& InComponentName);`
- L38 _public prototype_ `UEdGraphPin* GetComponentNamePin() const;`
- L42 _protected member_ `FName ComponentName = "De` — `UPROPERTY()` — TODO GMT Should be a FString due to FNames not being case sensitive at runtime
- L46 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`
- L49 _public member_ `FEdGraphPinReference ComponentNamePin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeComponentMesh.h` (Private)


#### class `UCustomizableObjectNodeComponentMesh`  
`class UCustomizableObjectNodeComponentMesh : public UCustomizableObjectNodeComponent`  
_L15-52_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeComponent`
- L21 _public prototype_ `UCustomizableObjectNodeComponentMesh();`
- L24 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UObject interface
- L33 _public member_ `TObjectPtr<USkeletalMesh> ReferenceSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = ComponentMesh)` — All the Skeletal Meshes generated for this component will use the Reference Skeletal Mesh properties for everything Mutable doesn't create or modify. This includes data like LOD distances, Physics properties, Bounding Volumes, Base Skeleton, and more. The Reference Skeletal Mesh can be used as a placeholder mesh when there are too many actors or in situations of stress where the generation of the Skeletal Mesh might take a few seconds to complete.
- L36 _public member_ `TSoftObjectPtr<UMaterialInterface> OverlayMaterial_DEPRECATED;` — `UPROPERTY()`
- L39 _public member_ `FMutableLODSettings LODSettings_DEPRECATED;` — `UPROPERTY()`
- L42 _public member_ `int32 NumLODs_DEPRECATED = 1;` — `UPROPERTY()`
- L45 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`
- L48 _public member_ `TArray<FEdGraphPinReference> LODPins_DEPRECATED;` — `UPROPERTY()`
- L51 _public member_ `FEdGraphPinReference OverlayMaterialPin;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeComponentPassthroughMesh.h` (Private)


#### class `UCustomizableObjectNodeComponentPassthroughMesh`  
`class UCustomizableObjectNodeComponentPassthroughMesh : public UCustomizableObjectNodeComponent`  
_L32-48_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeComponent`
- L38 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UObject interface.
- L41 _public member_ `FEdGraphPinReference SkeletalMeshPin;` — `UPROPERTY()`
- L44 _public member_ `FEdGraphPinReference OverlayMaterialPin;` — `UPROPERTY()`
- L47 _public member_ `TArray<FEdGraphPinReference> MaterialSlotPins;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeComponentSwitch.h` (Private)


#### class `UCustomizableObjectNodeComponentSwitch`  
`class UCustomizableObjectNodeComponentSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodeSwitch interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeComponentVariation.h` (Private)


#### enum `ECustomizableObjectNodeComponentVariationType`  
`enum class ECustomizableObjectNodeComponentVariationType : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Tag UMETA(DisplayName = "Tag")`
- L18 _public enumerator_ `State UMETA(DisplayName = "State")`

#### class `UCustomizableObjectNodeComponentVariation`  
`class UCustomizableObjectNodeComponentVariation : public UCustomizableObjectNodeVariation`  
_L23-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L33 _public prototype_ `virtual bool IsSingleOutputNode() const override;` — UCustomizableObjectNode interface
- L36 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface
- L37 _public prototype_ `virtual bool IsInputPinArray() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeCurve.h` (Private)


#### class `UCustomizableObjectNodeCurve`  
`class UCustomizableObjectNodeCurve : public UCustomizableObjectNode`  
_L22-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L27 _public prototype_ `UCustomizableObjectNodeCurve();`
- L30 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L31 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L34 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L36 _public prototype_ `FText GetTooltipText() const override;`
- L39 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L41 _public prototype_ `UEdGraphPin* InputPin() const;`
- L42 _public prototype_ `UEdGraphPin* CurvePins(int32 Index) const;`
- L43 _public prototype_ `int32 GetNumCurvePins() const;`
- L46 _public member_ `TObjectPtr<UCurveBase> CurveAsset;` — `UPROPERTY(EditAnywhere, Category = Curve)`
- L49 _public function_ `virtual bool IsAffectedByLOD() const override` — UCustomizableObjectNode interface
- L51 _public function_ `bool ProvidesCustomPinRelevancyTest() const override`
- L52 _public prototype_ `bool IsPinRelevant(const UEdGraphPin* Pin) const override;`
- L55 _public prototype_ `UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;` — Override the default behaivour of remap pins. Use remap pins by position by default.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeDetails.h` (Private)


#### class `FCustomizableObjectNodeDetails`  
`class FCustomizableObjectNodeDetails : public IDetailCustomization`  
_L13-32_
- inherits: `IDetailCustomization`
- desc: Base of all UCustomizableObjectNode details.
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L21 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L26 _protected prototype_ `void RefreshDetails();` — Force the refreshing of this details view. Only use if you are sure this will not pose a performance issue.
- L31 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilderPtr;` — Pointer to the DetailBuilder.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeEnumParameter.h` (Private)


#### struct `FCustomizableObjectNodeEnumValue`  
`struct FCustomizableObjectNodeEnumValue`  
_L19-28_
- reflection: `USTRUCT()`
- L24 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L27 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "Parameter UI Metadata"))`

#### class `UCustomizableObjectNodeEnumParameter`  
`class UCustomizableObjectNodeEnumParameter : public UCustomizableObjectNodeParameter`  
_L32-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter`
- L38 _public member_ `int32 DefaultIndex = 0;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L41 _public member_ `TArray<FCustomizableObjectNodeEnumValue> Values;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L45 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L48 _public prototype_ `virtual FText GetTooltipText() const override;`
- L49 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L52 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeExposePin.h` (Private)


#### class `UCustomizableObjectNodeExposePin`  
`class UCustomizableObjectNodeExposePin : public UCustomizableObjectNode`  
_L23-67_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- desc: Export Node.
- L29 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L30 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L31 _public prototype_ `virtual FText GetTooltipText() const override;`
- L32 _public function_ `virtual bool GetCanRenameNode() const override`
- L33 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L36 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L37 _public prototype_ `virtual bool CanConnect(const UEdGraphPin* InOwnedInputPin, const UEdGraphPin* InOutputPin, bool& bOutIsOtherNodeBlocklisted, bool& bOutArePinsCompatible) const override;`
- L38 _public prototype_ `virtual bool IsNodeSupportedInMacros() const override;`
- L39 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _public prototype_ `FString GetNodeName() const;` — Return the Expose Pin Node expose pin name.
- L47 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L53 _public member_ `FName PinType;` — `UPROPERTY()` — This is actually PinCategory
- L55 _public function_ `UEdGraphPin* InputPin() const`
- L62 _public member_ `FOnNameChangedDelegate OnNameChangedDelegate;` — Will be broadcast when the UPROPERTY Name changes.
- L66 _private member_ `FString Name = "De` — `UPROPERTY(Category = CustomizableObject, EditAnywhere)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNameChangedDelegate);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNameChangedDelegate);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeExtensionDataVariation.h` (Private)


#### struct `FCustomizableObjectExtensionDataVariation`  
`struct FCustomizableObjectExtensionDataVariation`  
_L13-19_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = "CustomizableObject")`

#### class `UCustomizableObjectNodeExtensionDataVariation`  
`class UCustomizableObjectNodeExtensionDataVariation : public UCustomizableObjectNode , public ICustomizableObjectExtensionNode`  
_L22-63_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UCustomizableObjectNode,ICustomizableObjectExtensionNode`
- L31 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L35 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L39 _public prototype_ `virtual bool IsAffectedByLOD() const override;`
- L40 _public prototype_ `virtual bool ShouldAddToContextMenu(FText& OutCategory) const override;`
- L41 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* InRemapPins) override;`
- L45 _public prototype_ `virtual UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeExtensionData> GenerateMutableNode(FExtensionDataCompilerInterface& InCompilerInterface) const override;`
- L48 _public prototype_ `virtual FName GetCategory() const PURE_VIRTUAL(GetCategory(), return FName();) virtual FName GetOutputPinName() const PURE_VIRTUAL(GetOutputPinName(), return FName();) FName GetDefaultPinName() const;`
- L52 _public prototype_ `FName GetVariationPinName(int32 InIndex) const;`
- L53 _public prototype_ `class UEdGraphPin* GetDefaultPin() const;`
- L54 _public prototype_ `class UEdGraphPin* GetVariationPin(int32 InIndex) const;`
- L56 _public prototype_ `int32 GetNumVariations() const;`
- L61 _public member_ `TArray<FCustomizableObjectExtensionDataVariation> Variations;` — `UPROPERTY(EditAnywhere, Category = "CustomizableObject")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeExternalPin.h` (Private)


#### class `UCustomizableObjectNodeExternalPin`  
`class UCustomizableObjectNodeExternalPin : public UCustomizableObjectNode`  
_L21-85_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- desc: Import Node.
- L27 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `virtual FText GetTooltipText() const override;`
- L35 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L36 _public prototype_ `virtual void PostBackwardsCompatibleFixup() override;`
- L37 _public prototype_ `virtual void BeginPostDuplicate(bool bDuplicateForPIE) override;`
- L38 _public prototype_ `virtual bool CanConnect(const UEdGraphPin* InOwnedInputPin, const UEdGraphPin* InOutputPin, bool& bOutIsOtherNodeBlocklisted, bool& bOutArePinsCompatible) const override;`
- L39 _public prototype_ `virtual void ReconstructNode(UCustomizableObjectNodeRemapPins* RemapPinsMode) override;`
- L40 _public prototype_ `virtual void UpdateReferencedNodeId(const FGuid& NewGuid) override;`
- L41 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L47 _public prototype_ `void SetExternalObjectNodeId(FGuid Guid);` — Set the linked Node Expose Pin node guid.
- L50 _public prototype_ `UEdGraphPin* GetExternalPin() const;` — Return the external pin. Can return nullptr.
- L53 _public prototype_ `UCustomizableObjectNodeExposePin* GetNodeExposePin() const;` — Return the linked Expose Pin node. Return nullptr if not set.
- L57 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L58 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L61 _private prototype_ `void PrePropagateConnectionChanged();`
- L62 _private prototype_ `void PropagateConnectionChanged();`
- L68 _public member_ `FName PinType;` — `UPROPERTY()` — This is actually PinCategory
- L72 _public member_ `TObjectPtr<UCustomizableObject> ExternalObject;` — `UPROPERTY()` — External Customizable Object which the linked Node Expose Pin belong to.
- L78 _private member_ `FGuid ExternalObjectNodeId;` — `UPROPERTY()` — Linked Node Expose Pin node guid.
- L80 _private member_ `FDelegateHandle OnNameChangedDelegateHandle;`
- L81 _private member_ `FDelegateHandle DestroyNodeDelegateHandle;`
- L84 _private member_ `TArray<UEdGraphPin*> PropagatePreviousPin;` — Connected pins (pins connected to the Export Node pin) before changing the import/export implicit connection.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeExternalPinDetails.h` (Private)


#### class `FCustomizableObjectNodeExternalPinDetails`  
`class FCustomizableObjectNodeExternalPinDetails : public FCustomizableObjectNodeDetails`  
_L16-34_
- inherits: `FCustomizableObjectNodeDetails`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L27 _private member_ `UCustomizableObjectNodeExternalPin* Node = nullptr;`
- L29 _private member_ `TArray<TSharedPtr<FString>> GroupNodeComboBoxOptions;`
- L31 _private prototype_ `void ParentObjectSelectionChanged(const FAssetData& AssetData);`
- L33 _private prototype_ `void OnGroupNodeComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeFloatArithmeticOp.h` (Private)


#### enum `EFloatArithmeticOperation`  
`enum class EFloatArithmeticOperation : uint8`  
_L20-26_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `E_Add UMETA(DisplayName = "+")`
- L23 _public enumerator_ `E_Sub UMETA(DisplayName = "-")`
- L24 _public enumerator_ `E_Mul UMETA(DisplayName = "x")`
- L25 _public enumerator_ `E_Div UMETA(DisplayName = "/")`

#### class `UCustomizableObjectNodeFloatArithmeticOp`  
`class UCustomizableObjectNodeFloatArithmeticOp : public UCustomizableObjectNode`  
_L29-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L34 _public prototype_ `UCustomizableObjectNodeFloatArithmeticOp();`
- L37 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L39 _public prototype_ `virtual FText GetTooltipText() const override;`
- L40 _public function_ `virtual bool ShouldOverridePinNames() const override`
- L43 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L46 _public function_ `UEdGraphPin* XPin() const` — First Operand
- L52 _public function_ `UEdGraphPin* YPin() const` — Second Operand
- L58 _public member_ `EFloatArithmeticOperation Operation;` — `UPROPERTY(EditAnywhere, Category = FloatArithmeticOperation)`
- L61 _public function_ `virtual bool IsAffectedByLOD() const override` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeFloatConstant.h` (Private)


#### class `SGraphNodeFloatConstant`  
`class SGraphNodeFloatConstant : public SCustomizableObjectNode`  
_L23-63_
- inherits: `SCustomizableObjectNode`
- desc: Class create an input float in the NodeFloatConstant
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeFloatConstant)`
- L29 _public prototype_ `SLATE_END_ARGS();`
- L31 _public function_ `SGraphNodeFloatConstant() : SCustomizableObjectNode()`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);` — Builds the SGraphNodeFloatConstant when needed
- L37 _public prototype_ `void UpdateGraphNode();` — Calls the needed functions to build the SGraphNode widgets
- L40 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;` — Overriden functions to build the SGraphNode widgets
- L41 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L42 _public function_ `virtual bool ShouldAllowCulling() const override`
- L45 _public prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Callbacks for the widget
- L46 _public prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;`
- L47 _public prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;`
- L52 _private prototype_ `void OnSpinBoxValueChanged(float Value);` — Callback for the OnValueChanged of the SpinBox
- L55 _private prototype_ `void OnSpinBoxValueCommitted(float Value, ETextCommit::Type);` — Callback for the OnValueCommited of the SpinBox
- L58 _private member_ `UCustomizableObjectNodeFloatConstant* NodeFloatConstant;` — Pointer to the NodeFloatconstant that owns this SGraphNode
- L61 _private member_ `FSpinBoxStyle WidgetStyle;` — Style for the SpinBox

#### class `UCustomizableObjectNodeFloatConstant`  
`class UCustomizableObjectNodeFloatConstant : public UCustomizableObjectNode`  
_L67-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L73 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L74 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L75 _public prototype_ `virtual FText GetTooltipText() const override;`
- L78 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L79 _public function_ `virtual bool IsAffectedByLOD() const override`
- L80 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L83 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;` — Creates the SGraph Node widget for the thumbnail
- L86 _public member_ `float Value = 1.0f;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (DontUpdateWhileEditing))`
- L89 _public member_ `bool bCollapsed = true;` — Determines if the Node is collapsed or not

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeFloatParameter.h` (Private)


#### struct `FCustomizableObjectNodeFloatDescription`  
`struct FCustomizableObjectNodeFloatDescription`  
_L22-28_
- reflection: `USTRUCT()`
- L27 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`

#### class `UCustomizableObjectNodeFloatParameter`  
`class UCustomizableObjectNodeFloatParameter : public UCustomizableObjectNodeParameter`  
_L32-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter`
- L38 _public member_ `float DefaultValue = 1.0f;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L41 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L44 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L47 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeFloatSwitch.h` (Private)


#### class `UCustomizableObjectNodeFloatSwitch`  
`class UCustomizableObjectNodeFloatSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodeSwitch interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeFloatVariation.h` (Private)


#### class `UCustomizableObjectNodeFloatVariation`  
`class UCustomizableObjectNodeFloatVariation : public UCustomizableObjectNodeVariation`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L22 _public member_ `TArray<FCustomizableObjectFloatVariation> Variations_DEPRECATED;` — `UPROPERTY()` — Deprecated properties
- L25 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L28 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeGroupProjectorParameter.h` (Private)


#### struct `FGroupProjectorParameterImage`  
`struct FGroupProjectorParameterImage`  
_L19-28_
- reflection: `USTRUCT()`
- L24 _public member_ `FString OptionName;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`
- L27 _public member_ `TObjectPtr<UTexture2D> OptionTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`

#### struct `FGroupProjectorParameterPose`  
`struct FGroupProjectorParameterPose`  
_L32-41_
- reflection: `USTRUCT()`
- L37 _public member_ `FString PoseName;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`
- L40 _public member_ `TObjectPtr<UPoseAsset> OptionPose = nullptr;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`

#### class `UCustomizableObjectNodeGroupProjectorParameter`  
`class UCustomizableObjectNodeGroupProjectorParameter : public UCustomizableObjectNodeProjectorParameter`  
_L45-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeProjectorParameter`
- L51 _public member_ `FString MaterialChannelNameToConnect;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup, Meta = (ToolTip = "Only used when connected to a Group node. Specifies which material channel in the Group node's child material nodes will be connected to the projection."))`
- L57 _public member_ `TObjectPtr<UTexture2D> ReferenceTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)` — Reference Texture used to decide the texture properties of the mutable-generated textures connected to this material. If null, it will try to be guessed at compile time from the graph.
- L61 _public member_ `TObjectPtr<USkeletalMesh> ReferenceSkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)` — TODO Remove. Only used because poses are the diff from a Reference Skeleton. Once the pose is absolute remove this.
- L64 _public member_ `int32 ProjectionTextureSize = 512;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`
- L67 _public member_ `int32 DropProjectionTextureAtLOD = -1;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup, Meta = (ToolTip = "Specifies at which LOD level the projection texture will not be used and possibly save memory. A negative value means they will never be dropped."))`
- L70 _public member_ `TArray<FGroupProjectorParameterImage> OptionTextures;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`
- L74 _public member_ `TArray<FGroupProjectorParameterPose> OptionPoses;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)`
- L78 _public member_ `FName DataTableTextureColumnName;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)` — Name of the column in the Option Images Data Table with the additional option images, (UTexture2D assets).
- L84 _public member_ `TObjectPtr<UDataTable> OptionTexturesDataTable = nullptr;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup)` — Table where additional option images besides Option Images are read. The elements in this table have priority over elements from Option Images in case of duplicity. Use the "Data Table Texture Column Name" property to specify the name of the column where textures are read in the table.
- L87 _public member_ `int32 UVLayout = 0;` — `UPROPERTY(EditAnywhere, Category = ProjectorGroup, Meta = (ClampMin = "0"))`
- L90 _public prototype_ `virtual FText GetTooltipText() const override;` — EdGraphNode interface.
- L93 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface.
- L96 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface
- L99 _public prototype_ `UEdGraphPin& OutputPin() const;` — Own interface
- L102 _public prototype_ `TArray<FGroupProjectorParameterImage> GetOptionTexturesFromTable() const;` — Return array with the sticker name and UTexture2D for projection
- L106 _public prototype_ `TArray<FGroupProjectorParameterImage> GetFinalOptionTexturesNoRepeat() const;` — Returns the final option images without repeated elements in the option names, the data table has preference over elements in the OptionTextures array

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeLayoutBlocks.h` (Private)


#### class `UCustomizableObjectNodeLayoutBlocks`  
`class UCustomizableObjectNodeLayoutBlocks : public UCustomizableObjectNode`  
_L24-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L29 _public prototype_ `UCustomizableObjectNodeLayoutBlocks();`
- L32 _public member_ `FIntPoint GridSize_DEPRECATED;` — `UPROPERTY()`
- L36 _public member_ `FIntPoint MaxGridSize_DEPRECATED;` — `UPROPERTY()` — Used with the fixed layout strategy.
- L39 _public member_ `TArray<FCustomizableObjectLayoutBlock> Blocks_DEPRECATED;` — `UPROPERTY()`
- L42 _public member_ `ECustomizableObjectTextureLayoutPackingStrategy PackingStrategy_DEPRECATED;` — `UPROPERTY()`
- L45 _public member_ `TObjectPtr<UCustomizableObjectLayout> Layout = nullptr;` — `UPROPERTY()`
- L48 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — EdGraphNode interface
- L51 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L13 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMacroInstance.h` (Private)


#### class `UCustomizableObjectNodeMacroInstancePinData`  
`class UCustomizableObjectNodeMacroInstancePinData : public UCustomizableObjectNodePinData`  
_L16-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- desc: Base class for all Macro Instance Pins.
- L24 _public member_ `FGuid VariableId;` — `UPROPERTY()` — Id of the variable associated to a Macro Instance node pin

#### class `UCustomizableObjectNodeMacroInstanceRemapPins`  
`class UCustomizableObjectNodeMacroInstanceRemapPins : public UCustomizableObjectNodeRemapPinsByName`  
_L30-40_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPinsByName`
- L36 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin) const override;` — Specific method to decide when two pins are equal
- L39 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;` — Method to use in the RemapPins step of the node reconstruction process

#### class `UCustomizableObjectNodeMacroInstance`  
`class UCustomizableObjectNodeMacroInstance : public UCustomizableObjectNode`  
_L45-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L52 _public member_ `TObjectPtr<UCustomizableObjectMacroLibrary> ParentMacroLibrary;` — `UPROPERTY(EditAnywhere, Category = MacroInstance)` — Macro Library where the macro to instantiate belongs.
- L56 _public member_ `TObjectPtr<UCustomizableObjectMacro> ParentMacro;` — `UPROPERTY(EditAnywhere, Category = MacroInstance)` — Macro that represent that instantiates the node.
- L61 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L62 _public prototype_ `virtual FText GetTooltipText() const override;`
- L63 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L64 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L65 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L66 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L67 _public prototype_ `virtual void JumpToDefinition() const override;`
- L70 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L71 _public prototype_ `virtual UCustomizableObjectNodeMacroInstanceRemapPins* CreateRemapPinsDefault() const override;`
- L72 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L76 _public prototype_ `UEdGraphPin* GetMacroTunnelPin(ECOMacroIOType IONodeType, const FName& PinName) const;` — Given a Macro pin, this function returns its I/O tunnel pin.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMacroInstanceDetails.h` (Private)


#### struct `FMacroSelectorItem`  
`struct FMacroSelectorItem`  
_L11-14_
- desc: Data container for the macro selector combobox
- L13 _public member_ `TObjectPtr<UCustomizableObjectMacro> Macro;`

#### class `FCustomizableObjectNodeMacroInstanceDetails`  
`class FCustomizableObjectNodeMacroInstanceDetails : public FCustomizableObjectNodeDetails`  
_L18-49_
- inherits: `FCustomizableObjectNodeDetails`
- desc: Details View of UCustomizableObjectNodeMacroInstance
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Do not use. Add details customization in the other CustomizeDetails signature.
- L29 _public prototype_ `TSharedPtr<FMacroSelectorItem> GenerateComboboxSource();` — Generates the soruce of the combobox used to select a Macro.
- L33 _private prototype_ `FText GetSelectedMacroName() const;`
- L36 _private prototype_ `void ResetSelectedParentMacro();` — Set the selected macro property to nullptr
- L41 _private member_ `TObjectPtr<UCustomizableObjectNodeMacroInstance> Node;` — Pointer to the Macro Instance Node.
- L44 _private member_ `TArray<TSharedPtr<FMacroSelectorItem>> ComboboxSource;` — Combobox Source array.
- L47 _private member_ `TSharedPtr<FMacroSelectorItem> SelectedSource;` — Current selected Macro in the Combobox.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMaterialParameter.h` (Private)


#### class `UCustomizableObjectNodeMaterialParameter`  
`class UCustomizableObjectNodeMaterialParameter : public UCustomizableObjectNodeParameter, public ICONodeSkeletalMeshSectionInterface`  
_L18-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter,ICONodeSkeletalMeshSectionInterface`
- L24 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface
- L27 _public prototype_ `virtual TSoftObjectPtr<UMaterialInterface> GetMaterial() const override;` — ICONodeSkeletalMeshSectionInterface interface
- L28 _public prototype_ `virtual UEdGraphPin* GetMaterialPin() const override;`
- L32 _public member_ `TSoftObjectPtr<UMaterialInterface> DefaultValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)` — Default value of the parameter.
- L35 _public member_ `TSoftObjectPtr<UMaterialInterface> ReferenceValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshInterface.h` (Private)


#### class `UCustomizableObjectNodeMeshInterface`  
`class UCustomizableObjectNodeMeshInterface : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICustomizableObjectNodeMeshInterface`  
`class ICustomizableObjectNodeMeshInterface`  
_L22-48_
- L29 _public prototype_ `virtual TArray<UCustomizableObjectLayout*> GetLayouts(const UEdGraphPin& OutPin) const PURE_VIRTUAL(UCustomizableObjectNodeMesh::GetLayouts, return {};);` — Returns the multiple Layouts of a given Mesh pin. A pin can have multiple Layouts since it can have multiple UVs. Override.
- L31 _public prototype_ `virtual UTexture2D* FindTextureForPin(const UEdGraphPin* Pin) const PURE_VIRTUAL(UCustomizableObjectNodeMesh::FindTextureForPin, return {};);`
- L34 _public prototype_ `virtual TSoftObjectPtr<UStreamableRenderAsset> GetMesh() const PURE_VIRTUAL(UCustomizableObjectNodeMesh::GetMesh, return {};);` — Returns the Unreal mesh (e.g., USkeletalMesh, UStaticMesh...).
- L37 _public prototype_ `virtual UEdGraphPin* GetMeshPin(int32 LOD, int32 SectionIndex) const PURE_VIRTUAL(UCustomizableObjectNodeMesh::GetMeshPin, return {};);` — Returns the output Mesh pin associated to the given LODIndex and SectionIndex. Override.
- L47 _public prototype_ `virtual void GetPinSection(const UEdGraphPin& Pin, int32& OutLODIndex, int32& OutSectionIndex) const PURE_VIRTUAL(UCustomizableObjectNodeMesh::GetPinSection, );` — Given a pin, return the Section and Layout index. Will always return a valid result. The result can be valid but out of sync with respect the Unreal mesh asset. In other words, the pin still represents a LOD 3 but the asset no longer has this third LOD. @param Pin In. Node's owning pin. @param LODIndex Out. @param SectionIndex Out.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshMorph.h` (Private)


#### class `UCustomizableObjectNodeMeshMorph`  
`class UCustomizableObjectNodeMeshMorph : public UCustomizableObjectNode`  
_L19-98_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual bool IsNodeOutDatedAndNeedsRefresh() override;` — UCustomizableObjectNode interface
- L31 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L32 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L33 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L34 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L35 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L36 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L40 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L45 _public prototype_ `class UCustomizableObjectNodeSkeletalMesh* GetSourceSkeletalMesh() const;` — Own interface
- L47 _public function_ `UEdGraphPin* MeshPin() const`
- L52 _public function_ `UEdGraphPin* FactorPin() const`
- L57 _public prototype_ `UEdGraphPin* MorphTargetNamePin() const;`
- L59 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L61 _public prototype_ `FName GetMorphTargetName(FMutableGraphGenerationContext& GenerationContext) const;`
- L65 _private member_ `FString MorphTargetName;` — `UPROPERTY()`
- L70 _public member_ `bool bReshapeSkeleton_DEPRECATED = false;` — `UPROPERTY()`
- L73 _public member_ `bool bReshapePhysicsVolumes_DEPRECATED = false;` — `UPROPERTY()`
- L76 _public member_ `EBoneDeformSelectionMethod SelectionMethod_DEPRECATED = EBoneDeformSelectionMethod::ONLY_SELECTED;` — `UPROPERTY()`
- L79 _public member_ `EBoneDeformSelectionMethod PhysicsSelectionMethod_DEPRECATED = EBoneDeformSelectionMethod::ONLY_SELECTED;` — `UPROPERTY()`
- L82 _public member_ `TArray<FMeshReshapeBoneReference> BonesToDeform_DEPRECATED;` — `UPROPERTY()`
- L85 _public member_ `TArray<FMeshReshapeBoneReference> PhysicsBodiesToDeform_DEPRECATED;` — `UPROPERTY()`
- L88 _public member_ `bool bDeformAllBones_DEPRECATED = false;` — `UPROPERTY()`
- L91 _public member_ `bool bDeformAllPhysicsBodies_DEPRECATED = false;` — `UPROPERTY()`
- L96 _private member_ `FEdGraphPinReference MorphTargetNamePinRef;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshMorphStackApplication.h` (Private)


#### class `UCustomizableObjectNodeMeshMorphStackApplication`  
`class UCustomizableObjectNodeMeshMorphStackApplication : public UCustomizableObjectNode`  
_L17-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TittleType)const override;` — EdGraphNode interface
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L33 _public prototype_ `TArray<FString> GetMorphList() const;` — Fills the list with all the morphs
- L36 _public prototype_ `UEdGraphPin* GetMeshPin() const;` — Returns the mesh pin.
- L39 _public prototype_ `UEdGraphPin* GetStackPin() const;` — Returns the stack pin.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshMorphStackDefinition.h` (Private)


#### class `UCONodeMeshMorphStackDefinitionPinData`  
`class UCONodeMeshMorphStackDefinitionPinData : public UCustomizableObjectNodePinData`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodePinData`
- L22 _public member_ `FName TargetMorphName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = NoCategory)`

#### class `UCustomizableObjectNodeMeshMorphStackDefinition`  
`class UCustomizableObjectNodeMeshMorphStackDefinition : public UCustomizableObjectNode`  
_L28-72_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L34 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TittleType)const override;` — EdGraphNode interface
- L35 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L36 _public prototype_ `virtual FText GetTooltipText() const override;`
- L39 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L40 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L41 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L42 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L43 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const override;`
- L44 _public prototype_ `virtual void AddPinFromUI() override;`
- L45 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const override;`
- L46 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin) override;`
- L47 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L49 _public prototype_ `FName GetMorphTargetName(const UEdGraphPin& Pin) const;`
- L54 _protected prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L55 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L59 _private prototype_ `bool IsMorphTargetPin(const UEdGraphPin& Pin) const;`
- L61 _private prototype_ `UEdGraphPin* CreateMorphTargetPin(UCONodeMeshMorphStackDefinitionPinData& InPinData);`
- L66 _public member_ `TArray<FEdGraphPinReference> MorphTargetPinReferences;` — `UPROPERTY()`
- L71 _private member_ `TArray<FString> MorphNames_DEPRECATED;` — `UPROPERTY()` — List with all the morphs of the linked skeletal mesh.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshReshape.h` (Private)


#### enum `EMeshReshapeVertexColorChannelUsage`  
`enum class EMeshReshapeVertexColorChannelUsage`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `RigidClusterId = 1`
- L23 _public enumerator_ `MaskWeight = 2`

#### struct `FMeshReshapeColorUsage`  
`struct FMeshReshapeColorUsage`  
_L27-42_
- reflection: `USTRUCT()`
- L32 _public member_ `EMeshReshapeVertexColorChannelUsage R = EMeshReshapeVertexColorChannelUsage::None;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L35 _public member_ `EMeshReshapeVertexColorChannelUsage G = EMeshReshapeVertexColorChannelUsage::None;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L38 _public member_ `EMeshReshapeVertexColorChannelUsage B = EMeshReshapeVertexColorChannelUsage::None;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L41 _public member_ `EMeshReshapeVertexColorChannelUsage A = EMeshReshapeVertexColorChannelUsage::None;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### class `UCustomizableObjectNodeMeshReshape`  
`class UCustomizableObjectNodeMeshReshape : public UCustomizableObjectNode`  
_L45-127_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L51 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L52 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L53 _public prototype_ `FText GetTooltipText() const override;`
- L56 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L57 _public prototype_ `FString GetRefreshMessage() const override;`
- L58 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L60 _public function_ `inline UEdGraphPin* BaseMeshPin() const`
- L65 _public function_ `inline UEdGraphPin* BaseShapePin() const`
- L70 _public function_ `inline UEdGraphPin* TargetShapePin() const`
- L77 _public member_ `bool bReshapeVertices = true;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Enable the deformation of the vertices of the base mesh.
- L81 _public member_ `bool bRecomputeNormals = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (EditCondition = "bReshapeVertices"))` — Enable recompute normals after the reshape operation.
- L85 _public member_ `bool bApplyLaplacianSmoothing = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (EditCondition = "bReshapeVertices"))` — Enable laplacian smoothing to the result of the base mesh reshape.
- L89 _public member_ `bool bReshapePose = false;` — `UPROPERTY(EditAnywhere, Category = ReshapePose)` — Enable the deformation of the skeleton of the base mesh.
- L93 _public member_ `bool bReshapePhysics = false;` — `UPROPERTY(EditAnywhere, Category = ReshapePhysics)` — Enable the deformation of physics volumes of the base mesh
- L96 _public member_ `bool bEnableRigidParts_DEPRECATED = false;` — `UPROPERTY()`
- L99 _public member_ `FMeshReshapeColorUsage VertexColorUsage;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L103 _public member_ `EBoneDeformSelectionMethod SelectionMethod;` — `UPROPERTY(EditAnywhere, Category = ReshapePose, meta = (EditCondition = "bReshapePose"))` — Bone Reshape Selection Method
- L107 _public member_ `TArray<FName> BonesToDeform_V2;` — `UPROPERTY(EditAnywhere, Category = ReshapePose, DisplayName = "Bones To Deform", meta = (EditCondition = "bReshapePose"))` — Array with selected bones that will be deformed
- L110 _public member_ `TArray<FMeshReshapeBoneReference> BonesToDeform_DEPRECATED;` — `UPROPERTY()`
- L113 _public member_ `EBoneDeformSelectionMethod PhysicsSelectionMethod;` — `UPROPERTY(EditAnywhere, Category = ReshapePhysics, meta = (DisplayName = "Selection Method", EditCondition = "bReshapePhysics"))`
- L117 _public member_ `TArray<FName> PhysicsBodiesToDeform_V2;` — `UPROPERTY(EditAnywhere, Category = ReshapePhysics, DisplayName = "Physics Bodies To Deform", meta = (EditCondition = "bReshapePhysics"))` — Array with bones with physics bodies that will be deformed
- L120 _public member_ `TArray<FMeshReshapeBoneReference> PhysicsBodiesToDeform_DEPRECATED;` — `UPROPERTY()`
- L123 _public member_ `bool bDeformAllBones_DEPRECATED = false;` — `UPROPERTY()`
- L126 _public member_ `bool bDeformAllPhysicsBodies_DEPRECATED = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshReshapeCommon.h` (Private)


#### enum `EBoneDeformSelectionMethod`  
`enum class EBoneDeformSelectionMethod : uint8`  
_L9-16_
- reflection: `UENUM()`
- L12 _public enumerator_ `ONLY_SELECTED = 0 UMETA(DisplayName = "Only Selected")` — Only selected bones will be deform
- L15 _public enumerator_ `ALL_BUT_SELECTED = 1 UMETA(DisplayName = "All But Selected")` — All bones will be deform except the selected ones

#### struct `FMeshReshapeBoneReference`  
`struct FMeshReshapeBoneReference`  
_L20-27_
- reflection: `USTRUCT()`
- L26 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Name of the bone that will be deformed

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshReshapeDetails.h` (Private)


#### class `FCustomizableObjectNodeMeshReshapeDetails`  
`class FCustomizableObjectNodeMeshReshapeDetails : public IDetailCustomization`  
_L12-28_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L21 _public prototype_ `void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshSectionDetails.h` (Private)


#### class `FCustomizableObjectNodeMeshSectionDetails`  
`class FCustomizableObjectNodeMeshSectionDetails : public FCustomizableObjectNodeDetails`  
_L20-52_
- inherits: `FCustomizableObjectNodeDetails`
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L32 _protected prototype_ `virtual void OnEnableTagsPropertyChanged();`
- L37 _private prototype_ `bool IsTagsPropertyWidgetEnabled() const;` — Disables/Enables the tags property widget.
- L40 _private prototype_ `FText TagsPropertyWidgetTooltip() const;` — Set the widget tooltip.
- L44 _private member_ `class UCONodeSkeletalMeshSection* Node = nullptr;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> TagsPropertyHandle;`
- L50 _private member_ `TSharedPtr<SMutableTagListWidget> TagListWidget;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshSwitch.h` (Private)


#### class `UCustomizableObjectNodeMeshSwitch`  
`class UCustomizableObjectNodeMeshSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodeSwitch interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeMeshVariation.h` (Private)


#### class `UCustomizableObjectNodeMeshVariation`  
`class UCustomizableObjectNodeMeshVariation : public UCustomizableObjectNodeVariation`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L22 _public member_ `TArray<FCustomizableObjectMeshVariation> Variations_DEPRECATED;` — `UPROPERTY()` — Deprecated properties
- L25 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L28 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierBase.h` (Private)


#### struct `FLegacyTag`  
`struct FLegacyTag`  
_L16-30_
- reflection: `USTRUCT()`
- L21 _public member_ `TSoftObjectPtr<UCustomizableObject> ParentObject;` — `UPROPERTY()`
- L24 _public member_ `FGuid ParentNode;` — `UPROPERTY()`
- L27 _public member_ `FString Tag;` — `UPROPERTY()`
- L29 _public prototype_ `bool operator==(const FLegacyTag&) const = default;`

#### class `UCustomizableObjectNodeModifierBase`  
`class UCustomizableObjectNodeModifierBase : public UCustomizableObjectNode`  
_L34-89_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UCustomizableObjectNode`
- L43 _public member_ `TArray<FString> RequiredTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier)` — Materials in all other objects that activate this tags will be affected by this modifier.
- L47 _public member_ `EMutableMultipleTagPolicy MultipleTagPolicy = EMutableMultipleTagPolicy::OnlyOneRequired;` — `UPROPERTY(EditAnywhere, Category = Modifier)` — Policy to use when multiple Target Mesh Section tags are set.
- L52 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — EdGraphNode interface
- L55 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L56 _public prototype_ `virtual void PostBackwardsCompatibleFixup() override;`
- L57 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L60 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const;` — Own interface
- L61 _public prototype_ `virtual UEdGraphPin* RequiredTagsPin() const;`
- L62 _public prototype_ `TArray<FString> GetNodeRequiredTags(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;`
- L65 _public prototype_ `bool IsApplicableTo(UCustomizableObjectNode* Candidate);` — Return true if the tags and policy in this node would make this node modify the given parameter node.
- L71 _public prototype_ `void GetPossiblyModifiedNodes(TArray<UCustomizableObjectNode*>&);` — Get the list of all nodes of this object that may be affected by this modifier. This is an approximate query: it includes all nodes that may be affected by this modifier but it may include nodes that will not be modified by this modifier because of other conditions.
- L74 _public prototype_ `static FString MakeNodeAutoTag(UEdGraphNode*);` — Generate a tag that is unique and stable for the given node.
- L82 _protected member_ `TArray<FLegacyTag> LegacyBackportsRequiredTags;` — `UPROPERTY()` — This is a list of tags autogenerated due to backwards compatibility upgrade. It must be removed when we remove the related backwards compatibility code.
- L87 _private member_ `FEdGraphPinReference RequiredTagsPinRef;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierBaseDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierBaseDetails`  
`class FCustomizableObjectNodeModifierBaseDetails : public FCustomizableObjectNodeDetails`  
_L20-53_
- inherits: `FCustomizableObjectNodeDetails`
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L32 _protected prototype_ `virtual void OnRequiredTagsPropertyChanged();` — Called when a required tags or policy property has changed, potentially changing the modified nodes.
- L37 _private prototype_ `bool IsTagsPropertyWidgetEnabled() const;` — Disables/Enables the tags property widget.
- L40 _private prototype_ `FText TagsPropertyWidgetTooltip() const;` — Set the widget tooltip.
- L44 _private member_ `class UCustomizableObjectNodeModifierBase* Node = nullptr;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> RequiredTagsPropertyHandle;`
- L48 _private member_ `TSharedPtr<IPropertyHandle> TagsPolicyPropertyHandle;`
- L51 _private member_ `TSharedPtr<SMutableTagListWidget> TagListWidget;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierClipDeform.h` (Private)


#### enum `EShapeBindingMethod`  
`enum class EShapeBindingMethod : uint32`  
_L17-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `ClosestProject = 0`
- L20 _public enumerator_ `ClosestToSurface = 1`
- L21 _public enumerator_ `NormalProject = 2`

#### class `UCustomizableObjectNodeModifierClipDeform`  
`class UCustomizableObjectNodeModifierClipDeform : public UCustomizableObjectNodeModifierBase`  
_L25-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierBase`
- L33 _public member_ `TArray<FString> Tags_DEPRECATED;` — `UPROPERTY()`
- L36 _public member_ `EShapeBindingMethod BindingMethod;` — `UPROPERTY(EditAnywhere, Category = MeshClipDeform)`
- L39 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = RemoveOptions)`
- L44 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L45 _public prototype_ `virtual FText GetTooltipText() const override;`
- L48 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L49 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L50 _public prototype_ `virtual bool IsExperimental() const override;`
- L55 _public prototype_ `UEdGraphPin* ClipShapePin() const;` — Input pins.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierClipMorph.h` (Private)


#### class `UCustomizableObjectNodeModifierClipMorph`  
`class UCustomizableObjectNodeModifierClipMorph : public UCustomizableObjectNodeModifierBase`  
_L22-124_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierBase`
- L28 _public member_ `TArray<FString> Tags_DEPRECATED;` — `UPROPERTY()`
- L30 _public member_ `uint32 ReferenceSkeletonIndex_DEPRECATED = 0;`
- L33 _public member_ `FName ReferenceSkeletonComponent;` — `UPROPERTY(EditAnywhere, Category = MeshToClipAndMorph)`
- L36 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = MeshToClipAndMorph)`
- L39 _public member_ `bool bInvertNormal;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName = "Invert normal direction", ToolTip = "Flag to invert the normal direction"))`
- L42 _public member_ `FVector StartOffset;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName="Morph Start Offset", ToolTip="Offset from the origin of the selected bone to the actual start of the morph."))`
- L45 _public member_ `bool bLocalStartOffset;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName = "Local Start Offset", ToolTip = "Toggles between a local or global start offset."))`
- L48 _public member_ `float B;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName="Morph length", ToolTip="The length from the morph start to the clip plane."))`
- L51 _public member_ `float Radius;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName="Ellipse Radius 1", ToolTip="First radius of the ellipse that the mesh is morphed into."))`
- L54 _public member_ `float Radius2;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName = "Ellipse Radius 2", ToolTip = "Second radius of the ellipse that the mesh is morphed into."))`
- L57 _public member_ `float RotationAngle;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName = "Ellipse Rotation", ToolTip = "Ellipse Rotation in degrees around the bone axis."))`
- L60 _public member_ `float Exponent;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName = "Morph Curve Control", ToolTip = "Controls the morph curve shape. A value of 1 is linear, less than 1 is concave and greater than 1 convex."))`
- L64 _public member_ `FVector Origin;` — `UPROPERTY()`
- L67 _public member_ `FVector Normal;` — `UPROPERTY()`
- L70 _public member_ `float MaxEffectRadius;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters, meta = (DisplayName = "Max Effect Radius", ToolTip = "The maximum distance from the origin of the widget where vertices will be affected. If negative, there will be no limit."))`
- L73 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = MeshClipParameters)`
- L78 _private member_ `bool bOldOffset_DEPRECATED;` — `UPROPERTY()`
- L82 _public prototype_ `UCustomizableObjectNodeModifierClipMorph();`
- L85 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L86 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L89 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L90 _public prototype_ `virtual FText GetTooltipText() const override;`
- L93 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L94 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L95 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L98 _public prototype_ `UEdGraphPin* GetOutputPin() const;` — Own interface
- L100 _public prototype_ `FVector GetOriginWithOffset() const;`
- L101 _public prototype_ `void FindLocalAxes(FVector& Right, FVector& Up, FVector& Forward) const;`
- L106 _public prototype_ `void ChangeStartOffsetTransform();` — Change StartOffset from World to Local of the other way around
- L111 _public prototype_ `void InvertNormals();` — Invert the normals of the Clipping plane
- L116 _public prototype_ `void UpdateOriginAndNormal();` — Update the origin and normal based on the BoneName property
- L123 _public prototype_ `TStrongObjectPtr<USkeletalMesh> GetReferenceSkeletalMesh() const;` — Get the reference skeletal mesh based on the ReferenceSkeletonComponent property @return The skeletal mesh component used as reference for the ReferenceSkeletonComponent property. Null if the ReferenceSkeletonComponent is not valid

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L13 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierClipMorphDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierClipMorphDetails`  
`class FCustomizableObjectNodeModifierClipMorphDetails : public FCustomizableObjectNodeModifierBaseDetails`  
_L18-71_
- inherits: `FCustomizableObjectNodeModifierBaseDetails`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L30 _private prototype_ `void CacheSkeletalMesh();` — Store the Skeletal Mesh of the current node for later access.
- L33 _private prototype_ `void CacheSkeletalMeshBoneNames();` — If a skeletal mesh has been cached this method will cache the name of the bones part of the skeleton of the cached skeletal mesh
- L36 _private prototype_ `void OnBoneNameReset();` — Method invoked each time the BoneName property gets reset from the UI
- L44 _private prototype_ `void OnBoneComboBoxSelectionChanged(TSharedPtr<FString> InSelectedBoneName, ESelectInfo::Type InSelectInfo, TSharedRef<IPropertyHandle> BoneProperty);` — Method invoked each time the selected boneName in the exposed combobox is changed by the user @param InSelectedBoneName The new selected bone name @param InSelectInfo The type of selection (combobox selection) @param BoneProperty The property to be updated with the string found in InSelection
- L47 _private prototype_ `void OnReferenceSkeletonComponentChanged();` — Method invoked each time the component name property gets its value updated
- L53 _private prototype_ `EVisibility ShouldBoneDropdownBeVisible() const;` — Determines if the bone dropdown should be visible or not @return The visibility state to use for the bone name dropdown.
- L56 _private member_ `TStrongObjectPtr<UCustomizableObjectNodeModifierClipMorph> Node = nullptr;` — The node whose data we are representing and updating
- L59 _private member_ `TSharedPtr<STextComboBox> BoneSelectionComboBox = nullptr;` — The combo box that we use to display a list of bone names for the current Skeletal mesh
- L61 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;`
- L64 _private member_ `TSharedPtr<FString> InitiallySelectedBone;` — The name of the bone we have initially selected
- L67 _private member_ `TArray<TSharedPtr<FString>> BoneComboOptions;` — The name of all bones we could select for the skeletal mesh skeleton of the current component
- L70 _private member_ `TStrongObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — The skeletal mesh of the component the node is modifying. It will be used to get an array of bones.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierClipWithMesh.h` (Private)


#### class `UCustomizableObjectNodeModifierClipWithMesh`  
`class UCustomizableObjectNodeModifierClipWithMesh : public UCustomizableObjectNodeModifierBase`  
_L22-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierBase`
- L29 _public member_ `TArray<FString> Tags_DEPRECATED;` — `UPROPERTY()`
- L34 _public member_ `TObjectPtr<UCustomizableObject> CustomizableObjectToClipWith_DEPRECATED = nullptr;` — `UPROPERTY()` — If assigned, then a material inside this CO will be clipped by this node. If several materials with the same name, all are considered (to cover all LOD levels)
- L38 _public member_ `TArray<FGuid> ArrayMaterialNodeToClipWithID_DEPRECATED;` — `UPROPERTY()` — Array with the Guids of the nodes with the same material inside the CustomizableObjectToClipWith CO (if any is assigned)
- L42 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = ClipMesh)` — Transform to apply to the clip mesh before clipping.
- L45 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = ClipMesh)`
- L50 _public member_ `OnTransformChanged TransformChangedDelegate;` — Delegate invoked each time the BoundingMeshTransform value gets modified
- L54 _public prototype_ `UCustomizableObjectNodeModifierClipWithMesh();`
- L57 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L58 _public prototype_ `virtual FText GetTooltipText() const override;`
- L61 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L62 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L63 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L66 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;` — Own interface
- L68 _public prototype_ `UEdGraphPin* GetClipMeshPin() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierClipWithUVMask.h` (Private)


#### class `UCustomizableObjectNodeModifierClipWithUVMask`  
`class UCustomizableObjectNodeModifierClipWithUVMask : public UCustomizableObjectNodeModifierBase`  
_L19-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierBase`
- L27 _public member_ `TArray<FString> Tags_DEPRECATED;` — `UPROPERTY()` — Materials in all other objects that activate this tags will be clipped with this UV mask.
- L31 _public member_ `int32 UVChannelForMask = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ClipOptions)` — UV channel index that will be used to get the UVs to apply the clipping mask to.
- L34 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = ClipOptions)`
- L39 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L40 _public prototype_ `virtual FText GetTooltipText() const override;`
- L43 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L44 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L45 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L51 _public prototype_ `UEdGraphPin* ClipMaskPin() const;` — Access to input pins.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierEditLayoutBlocks.h` (Private)


#### class `UCustomizableObjectNodeModifierEditLayoutBlocks`  
`class UCustomizableObjectNodeModifierEditLayoutBlocks : public UCustomizableObjectNodeModifierEditMeshSectionBase`  
_L14-34_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UCustomizableObjectNodeModifierEditMeshSectionBase`
- L19 _public prototype_ `UCustomizableObjectNodeModifierEditLayoutBlocks();`
- L25 _public member_ `TArray<FGuid> BlockIds_DEPRECATED;` — `UPROPERTY()` — Deprecated data from the time this node referred to other layout node blocks. Info is now in the Layout attribute.
- L32 _public member_ `TObjectPtr<UCustomizableObjectLayout> Layout = nullptr;` — `UPROPERTY()` — Layout defining the blocks to edit. It is a standalone layout, unrelated to whatever is connected to the UV channels of the mesh being edited. Some properties in the UCustomizableObjectLayout, like shrinking strategy or priorities will not be relevant.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierEditMeshSectionBase.h` (Private)


#### class `UCustomizableObjectNodeModifierEditMeshSectionBase`  
`class UCustomizableObjectNodeModifierEditMeshSectionBase : public UCONodeModifierSkeletalMeshSection`  
_L14-41_
- reflection: `UCLASS(Abstract)`
- inherits: `UCONodeModifierSkeletalMeshSection`
- L22 _public member_ `int ParentLayoutIndex = 0;` — `UPROPERTY()` — Layout index used when the modifier is based on UVs, or UV blocks.
- L28 _public member_ `TObjectPtr<UCustomizableObject> ParentMaterialObject_DEPRECATED = nullptr;` — `UPROPERTY()` — Deprecated properties from the time these nodes had hard parent node references. The data is now used to upgrade to newer versions, but will be removed in the future.
- L31 _public member_ `FGuid ParentMaterialNodeId_DEPRECATED;` — `UPROPERTY()`
- L34 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L39 _public prototype_ `UCustomizableObjectLayout* GetPossibleParentLayout();` — Scan all the related objects and find a candidate layout where this modifier can be applied.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierEditMeshSectionDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierEditMeshSectionDetails`  
`class FCustomizableObjectNodeModifierEditMeshSectionDetails : public FCustomizableObjectNodeModifierBaseDetails`  
_L16-42_
- inherits: `FCustomizableObjectNodeModifierBaseDetails`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L26 _public prototype_ `virtual void OnRequiredTagsPropertyChanged() override;` — FCustomizableObjectNodeModifierBaseDetails interface.
- L29 _private member_ `UCONodeModifierEditSkeletalMeshSection* Node;`
- L32 _private member_ `TSharedPtr<SCustomizableObjectLayoutEditor> LayoutBlocksEditor;` — Layout block editor widget
- L35 _private member_ `TArray<TSharedPtr<FString>> UVChannelOptions;` — List of available layout grid sizes.
- L38 _private prototype_ `void OnUVChannelChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Layout Options Callbacks
- L41 _private prototype_ `void OnPreUpdateLayout();` — Reset the layout in the widget to force a refresh.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierExtendMeshSectionDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierExtendMeshSectionDetails`  
`class FCustomizableObjectNodeModifierExtendMeshSectionDetails : public FCustomizableObjectNodeModifierBaseDetails`  
_L22-53_
- inherits: `FCustomizableObjectNodeModifierBaseDetails`
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L29 _public prototype_ `void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L34 _private prototype_ `bool IsTagsPropertyWidgetEnabled() const;` — Disables/Enables the tags property widget.
- L37 _private prototype_ `FText TagsPropertyWidgetTooltip() const;` — Set the widget tooltip.
- L41 _private member_ `class UCONodeModifierExtendSkeletalMeshSection* Node = nullptr;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> EnableTagsPropertyHandle;`
- L47 _private member_ `TSharedPtr<SMutableTagListWidget> EnableTagListWidget;`
- L50 _private prototype_ `virtual void OnEnableTagsPropertyChanged();`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierMorphMeshSection.h` (Private)


#### class `UCustomizableObjectNodeModifierMorphMeshSection`  
`class UCustomizableObjectNodeModifierMorphMeshSection: public UCustomizableObjectNodeModifierEditMeshSectionBase`  
_L17-55_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeModifierEditMeshSectionBase`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L30 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L31 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L33 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L34 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L35 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L37 _public prototype_ `FString GetMorphTargetName(FMutableGraphGenerationContext& GenerationContext) const;`
- L41 _private prototype_ `bool IsMorphTargetNamePin(const UEdGraphPin& Pin) const;`
- L46 _public member_ `FEdGraphPinReference FactorPinReference;` — `UPROPERTY()`
- L51 _private member_ `FString MorphTargetName;` — `UPROPERTY()`
- L54 _private member_ `FEdGraphPinReference MorphTargetNamePinRef;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierMorphMeshSectionDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierMorphMeshSectionDetails`  
`class FCustomizableObjectNodeModifierMorphMeshSectionDetails : public FCustomizableObjectNodeModifierBaseDetails`  
_L22-30_
- inherits: `FCustomizableObjectNodeModifierBaseDetails`
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L29 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierRemoveMesh.h` (Private)


#### class `UCustomizableObjectNodeModifierRemoveMesh`  
`class UCustomizableObjectNodeModifierRemoveMesh : public UCustomizableObjectNodeModifierEditMeshSectionBase`  
_L18-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierEditMeshSectionBase`
- L25 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = RemoveOptions)`
- L30 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L35 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin * Pin);`
- L37 _public function_ `UEdGraphPin* RemoveMeshPin() const`
- L42 _public prototype_ `bool IsSingleOutputNode() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierRemoveMeshBlocks.h` (Private)


#### class `UCustomizableObjectNodeModifierRemoveMeshBlocks`  
`class UCustomizableObjectNodeModifierRemoveMeshBlocks : public UCustomizableObjectNodeModifierEditLayoutBlocks`  
_L20-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeModifierEditLayoutBlocks`
- L27 _public member_ `TArray<int32> Blocks_DEPRECATED;` — `UPROPERTY()`
- L30 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — `UPROPERTY(EditAnywhere, Category = RemoveOptions)`
- L35 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _public prototype_ `virtual FText GetTooltipText() const override;`
- L39 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L40 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L41 _public prototype_ `virtual bool IsSingleOutputNode() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierRemoveMeshBlocksDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierRemoveMeshBlocksDetails`  
`class FCustomizableObjectNodeModifierRemoveMeshBlocksDetails : public FCustomizableObjectNodeModifierBaseDetails`  
_L16-43_
- inherits: `FCustomizableObjectNodeModifierBaseDetails`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L26 _public prototype_ `virtual void OnRequiredTagsPropertyChanged() override;` — FCustomizableObjectNodeModifierBaseDetails interface.
- L29 _private member_ `UCustomizableObjectNodeModifierRemoveMeshBlocks* Node;`
- L32 _private member_ `TSharedPtr<SCustomizableObjectLayoutEditor> LayoutBlocksEditor;` — Layout block editor widget
- L35 _private member_ `TArray<TSharedPtr< FString>> UVChannelOptions;` — List of available layout grid sizes.
- L38 _private prototype_ `void OnUVChannelChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Layout Options Callbacks
- L41 _private prototype_ `void OnPreUpdateLayout();` — Reset the layout in the widget to force a refresh.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierRemoveMeshDetails.h` (Private)


#### class `FCustomizableObjectNodeModifierRemoveMeshDetails`  
`class FCustomizableObjectNodeModifierRemoveMeshDetails : public FCustomizableObjectNodeModifierBaseDetails`  
_L10-19_
- inherits: `FCustomizableObjectNodeModifierBaseDetails`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeModifierTransformInMesh.h` (Private)


#### class `UCustomizableObjectNodeModifierTransformInMesh`  
`class UCustomizableObjectNodeModifierTransformInMesh : public UCustomizableObjectNodeModifierBase`  
_L19-55_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeModifierBase`
- L26 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L27 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L31 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;` — UCustomizableObjectNodeModifierBase interface
- L35 _public prototype_ `virtual bool IsDeprecated() const override;`
- L36 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L40 _public member_ `FTransform BoundingMeshTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = BoundingMesh)` — Transform to apply to the bounding mesh before selecting for vertices to transform.
- L43 _public member_ `FEdGraphPinReference BoundingMeshPin;` — `UPROPERTY()`
- L46 _public member_ `FEdGraphPinReference TransformMeshPin;` — `UPROPERTY()`
- L49 _public member_ `FEdGraphPinReference OutputPin;` — `UPROPERTY()`
- L54 _public member_ `OnTransformChanged TransformChangedDelegate;` — Delegate invoked each time the BoundingMeshTransform value gets modified

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnTransformChanged, const FTransform&);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeObject.h` (Private)


#### struct `FCustomizableObjectState`  
`struct FCustomizableObjectState`  
_L26-71_
- reflection: `USTRUCT()`
- L33 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L36 _public member_ `TArray<FString> RuntimeParameters;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (ShowParameterOptions))`
- L40 _public member_ `ETextureCompressionStrategy TextureCompressionStrategy = ETextureCompressionStrategy::None;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Special treatment of texture compression for this state.
- L44 _public member_ `bool bDisableMeshStreaming = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (EditCondition="!bLiveUpdateMode"))` — If this is enabled, Mesh streaming won't be used for this state, and all LODs will be generated when an instance is first updated.
- L48 _public member_ `bool bDisableTextureStreaming = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (EditCondition="!bLiveUpdateMode"))` — If this is enabled, texture streaming won't be used for this state, and full images will be generated when an instance is first updated.
- L52 _public member_ `bool bLiveUpdateMode = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — LiveUpdateMode will reuse instance temp. data between updates and speed up update times, but spend much more memory. Good for customization screens, not for actual gameplay modes.
- L55 _public member_ `bool bBuildOnlyFirstLOD = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L58 _public member_ `TMap<FString, FString> ForcedParameterValues;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L61 _public member_ `FMutableStateUIMetadata UIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "State UI Metadata"))`
- L66 _private member_ `FMutableParamUIMetadata StateUIMetadata_DEPRECATED;` — `UPROPERTY()` — Deprecated
- L70 _private member_ `bool bDontCompressRuntimeTextures_DEPRECATED = false;` — `UPROPERTY()` — This is now TextureCompressionStrategy.

#### struct `FSkeletalMeshMorphTargetOverride`  
`struct FSkeletalMeshMorphTargetOverride`  
_L74-83_
- reflection: `USTRUCT()`
- L79 _public member_ `FName SkeletalMeshName;` — `UPROPERTY(EditAnywhere, Category = RealTimeMorphTargets)`
- L82 _public member_ `ECustomizableObjectSelectionOverride SelectionOverride = ECustomizableObjectSelectionOverride::NoOverride;` — `UPROPERTY(EditAnywhere, Category = RealTimeMorphTargets)`

#### struct `FRealTimeMorphSelectionOverride`  
`struct FRealTimeMorphSelectionOverride`  
_L86-104_
- reflection: `USTRUCT()`
- L91 _public member_ `FName MorphName;` — `UPROPERTY(EditAnywhere, Category = RealTimeMorphTargets)`
- L94 _public member_ `ECustomizableObjectSelectionOverride SelectionOverride = ECustomizableObjectSelectionOverride::NoOverride;` — `UPROPERTY(EditAnywhere, Category = RealTimeMorphTargets)`
- L97 _public member_ `TArray<FSkeletalMeshMorphTargetOverride> SkeletalMeshes;` — `UPROPERTY(EditAnywhere, Category = RealTimeMorphTargets, meta=(TitleProperty=SkeletalMeshName))`
- L100 _public member_ `TArray<FName> SkeletalMeshesNames_DEPRECATED;` — `UPROPERTY()`
- L103 _public member_ `TArray<ECustomizableObjectSelectionOverride> Override_DEPRECATED;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeObject`  
`class UCustomizableObjectNodeObject : public UCustomizableObjectNode`  
_L107-218_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L112 _public prototype_ `UCustomizableObjectNodeObject();`
- L117 _protected member_ `FString ObjectName;` — `UPROPERTY()`
- L122 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "Parameter UI Metadata"))`
- L125 _public member_ `int32 NumLODs_DEPRECATED = 1;` — `UPROPERTY()`
- L128 _public member_ `int32 NumMeshComponents_DEPRECATED = 1;` — `UPROPERTY()`
- L131 _public member_ `TArray<FCustomizableObjectState> States;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject ,meta = (TitleProperty = "Name"))`
- L134 _public member_ `TObjectPtr<UCustomizableObject> ParentObject;` — `UPROPERTY(EditAnywhere, Category = AttachedToExternalObject)`
- L137 _public member_ `FGuid ParentObjectGroupId;` — `UPROPERTY(EditAnywhere, Category = AttachedToExternalObject)`
- L140 _public member_ `FGuid Identifier;` — `UPROPERTY()`
- L143 _public member_ `TArray<FRealTimeMorphSelectionOverride> RealTimeMorphSelectionOverrides;` — `UPROPERTY(EditAnywhere, Category = RealTimeMorphTargets, meta=(TitleProperty=MorphName, EditCondition="ParentObject==nullptr"))`
- L146 _public member_ `TArray<FComponentSettings> ComponentSettings_DEPRECATED;` — `UPROPERTY()`
- L150 _private member_ `FEdGraphPinReference NamePin;` — `UPROPERTY()`
- L154 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L157 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L158 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L159 _public prototype_ `virtual FText GetTooltipText() const override;`
- L160 _public prototype_ `virtual void PrepareForCopying() override;`
- L161 _public prototype_ `virtual void PostPasteNode() override;`
- L162 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L163 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L166 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L167 _public prototype_ `virtual void PostBackwardsCompatibleFixup() override;`
- L168 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L169 _public prototype_ `virtual bool IsNodeSupportedInMacros() const override;`
- L170 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L171 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L172 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L175 _public prototype_ `void SetParentObject(UCustomizableObject* CustomizableParentObject);` — Own Interface
- L176 _public prototype_ `void SetObjectName(const FString& Name);`
- L177 _public prototype_ `virtual FString GetObjectName(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;`
- L181 _public member_ `bool bIsBase;` — `UPROPERTY()` — Own interface
- L183 _public function_ `UEdGraphPin* ComponentsPin() const`
- L188 _public function_ `UEdGraphPin* ModifiersPin() const`
- L193 _public function_ `UEdGraphPin* ChildrenPin() const`
- L198 _public function_ `UEdGraphPin* OutputPin() const`
- L204 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L205 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L207 _public prototype_ `bool IsSingleOutputNode() const override;`
- L210 _public member_ `TArray<FString> ParameterNames;` — Array filled in the Details of the node to store all the parameter names of a CO graph (full tree)
- L213 _private member_ `static const FName ChildrenPinName;`
- L214 _private member_ `static const FName ComponentsPinName;`
- L215 _private member_ `static const FName ModifiersPinName;`
- L216 _private member_ `static const FName OutputPinName;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L14 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeObjectChild.h` (Private)


#### class `UCustomizableObjectNodeObjectChild`  
`class UCustomizableObjectNodeObjectChild : public UCustomizableObjectNodeObject`  
_L15-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeObject`
- L20 _public prototype_ `UCustomizableObjectNodeObjectChild();`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _public prototype_ `virtual void PrepareForCopying() override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L27 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L30 _public prototype_ `virtual bool IsNodeSupportedInMacros() const override;` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeObjectDetails.h` (Private)


#### class `FStatePropertyTypeIdentifier`  
`class FStatePropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L24-32_
- inherits: `IPropertyTypeIdentifier`
- desc: Class created to identify FStrings with metadata ShowParameterOptions. This allows us to change the default FString property widget for a ComboBox in the CustomizableObjectNodeObject details.
- L27 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `FCustomizableObjectStateParameterSelector`  
`class FCustomizableObjectStateParameterSelector : public IPropertyTypeCustomization`  
_L36-80_
- inherits: `IPropertyTypeCustomization`
- desc: Custom Widget for the property RuntimeParameters of the States(FCustomizableObjectState)
- L40 _public function_ `FCustomizableObjectStateParameterSelector()`
- L42 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L45 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L47 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L53 _private prototype_ `void GenerateParameterOptions(const FString& SelectedValue);` — Generates the option of the combobox
- L56 _private prototype_ `TSharedRef<SWidget> OnGenerateStateParameterSelectorComboBox(TSharedPtr<FString> InItem) const;` — Generates the Text widget of the combobox
- L59 _private prototype_ `void OnParameterNameSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Callback of OnSelectionChanged of the combobox
- L62 _private prototype_ `FText GetSelectedParameterName() const;` — Returns the name of the current selected parameter
- L65 _private prototype_ `void ResetSelectedParameterButtonClicked();` — Callback of the function OverrideResetToDefault
- L70 _private member_ `TArray<TSharedPtr<FString>> ParameterOptions;` — Array with all the possible parameter names
- L73 _private member_ `TWeakObjectPtr<UCustomizableObjectNodeObject> BaseObjectNode;` — Weak pointer to the Customizable Object that contains this property
- L76 _private member_ `TSharedPtr<FString> SelectedParameter;` — Pointer to the current selected parameter
- L79 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Runtime Parameter Name property of a State

#### class `FCustomizableObjectNodeObjectDetails`  
`class FCustomizableObjectNodeObjectDetails : public FCustomizableObjectNodeDetails`  
_L83-108_
- inherits: `FCustomizableObjectNodeDetails`
- L87 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L90 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L92 _public prototype_ `void ParentObjectSelectionChanged(const FAssetData& AssetData);`
- L96 _private member_ `TWeakObjectPtr<UCustomizableObjectNodeObject> BaseObjectNode;`
- L97 _private member_ `TArray< TSharedPtr<FString> > GroupNodeComboOptions;`
- L99 _private member_ `TArray< TSharedPtr<FString> > ParentComboOptions;`
- L100 _private member_ `TArray< class UCONodeSkeletalMeshSection* > ParentOptionNode;`
- L102 _private prototype_ `void OnGroupNodeComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo, TSharedRef<IPropertyHandle> ParentProperty);`
- L105 _private prototype_ `void OnStatesPropertyChanged();` — Refreshes the Details View when the states variable has been updated
- L107 _private prototype_ `void FillParameterNamesArray();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeObjectGroup.h` (Private)


#### class `UCustomizableObjectNodeObjectGroup`  
`class UCustomizableObjectNodeObjectGroup : public UCustomizableObjectNode`  
_L22-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L27 _public prototype_ `UCustomizableObjectNodeObjectGroup();`
- L30 _public member_ `ECustomizableObjectGroupType GroupType;` — `UPROPERTY(EditAnywhere, Category=GroupInfo, meta = (DisplayName = "Type"))`
- L33 _public member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, Category=GroupInfo)`
- L36 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "Parameter UI Metadata"))`
- L41 _public member_ `int8 BonePosePriority = 0;` — `UPROPERTY(EditAnywhere, Category = MeshPose)` — The pose defined in meshes deriving from this node will inherit this bone pose priority. Decides the bone pose to keep when two bones that have the same bone usage flags (E.g. EBoneUsageFlags::Skinning). The one with higher priority will be kept.
- L46 _public member_ `int8 SocketPriority = 0;` — `UPROPERTY(EditAnywhere, Category = MeshSockets)` — The sockets defined in meshes deriving from this node will inherit this socket priority. When in the generated merged mesh there are clashes with socket names, the one with higher priority will be kept and the other discarded.
- L49 _public member_ `FEdGraphPinReference NamePin;` — `UPROPERTY()`
- L52 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L53 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L56 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L57 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L58 _public prototype_ `virtual FText GetTooltipText() const override;`
- L59 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L60 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L63 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L64 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L65 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L66 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L67 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L68 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L71 _public prototype_ `UEdGraphPin* ObjectsPin() const;` — Own interface
- L72 _public prototype_ `UEdGraphPin* GroupProjectorsPin() const;`
- L73 _public prototype_ `UEdGraphPin* GroupPin() const;`
- L74 _public prototype_ `FString GetGroupName(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;`
- L75 _public prototype_ `void SetGroupName(const FString& Name);`
- L80 _private member_ `FString GroupName;` — `UPROPERTY(EditAnywhere, Category = GroupInfo, meta = (DisplayName = "Name"))`
- L82 _private member_ `FString LastGroupName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeParameter.h` (Private)


#### class `UCustomizableObjectNodeParameter`  
`class UCustomizableObjectNodeParameter : public UCustomizableObjectNode`  
_L18-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UCustomizableObjectNode`
- L24 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "Parameter UI Metadata"))`
- L27 _public member_ `FEdGraphPinReference NamePin;` — `UPROPERTY()`
- L32 _private member_ `FString ParameterName = "De` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L37 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L39 _public prototype_ `virtual FText GetTooltipText() const override;`
- L40 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L41 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L44 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L45 _public prototype_ `virtual bool IsAffectedByLOD() const override;`
- L46 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L47 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L48 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L49 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L53 _public prototype_ `virtual FName GetCategory() const PURE_VIRTUAL(UCustomizableObjectNodeParameter::GetCategory, return {}; );` — Return the pin category of this node.
- L54 _public prototype_ `virtual FText GetCategoryFriendlyName() const;`
- L55 _public prototype_ `virtual FString GetParameterName(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;`
- L56 _public prototype_ `virtual void SetParameterName(const FString& Name);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeParameterDetails.h` (Private)


#### class `FCustomizableObjectNodeParameterDetails`  
`class FCustomizableObjectNodeParameterDetails : public FCustomizableObjectNodeDetails`  
_L8-16_
- inherits: `FCustomizableObjectNodeDetails`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodePassThroughTextureSwitch.h` (Private)


#### class `UCustomizableObjectNodePassThroughTextureSwitch`  
`class UCustomizableObjectNodePassThroughTextureSwitch : public UCONodeSwitch`  
_L13-20_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- L19 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNodeSwitch interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodePassThroughTextureVariation.h` (Private)


#### class `UCustomizableObjectNodePassThroughTextureVariation`  
`class UCustomizableObjectNodePassThroughTextureVariation : public UCustomizableObjectNodeTextureVariation`  
_L13-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeTextureVariation`
- L19 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L22 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeProjectorConstant.h` (Private)


#### class `UCustomizableObjectNodeProjectorConstant`  
`class UCustomizableObjectNodeProjectorConstant : public UCustomizableObjectNode`  
_L20-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L25 _public prototype_ `UCustomizableObjectNodeProjectorConstant();`
- L29 _public member_ `FCustomizableObjectProjector Value;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta = (ShowOnlyInnerProperties))`
- L32 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "Parameter UI Metadata"))`
- L35 _public member_ `float ProjectionAngle;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, Meta = (DisplayName = "Projection Angle (degrees)"))`
- L38 _public member_ `uint32 ReferenceSkeletonIndex_DEPRECATED = 0;` — `UPROPERTY()`
- L41 _public member_ `FName ReferenceSkeletonComponent;` — `UPROPERTY(EditAnywhere, Category = ProjectorSnapToBone)`
- L44 _public member_ `FName ProjectorBone;` — `UPROPERTY(EditAnywhere, Category = ProjectorSnapToBone)`
- L47 _public member_ `FVector BoneComboBoxLocation;` — Temporary variable where to put the location information for bone combo box selection changes (in FCustomizableObjectNodeProjectorParameterDetails)
- L50 _public member_ `FVector BoneComboBoxForwardDirection;` — Temporary variable where to put the direction information for bone combo box selection changes (in FCustomizableObjectNodeProjectorParameterDetails)
- L53 _public member_ `FVector BoneComboBoxUpDirection;` — Temporary variable where to put the direction information for bone combo box selection changes (in FCustomizableObjectNodeProjectorParameterDetails)
- L56 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L59 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L60 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L61 _public prototype_ `virtual FText GetTooltipText() const override;`
- L64 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L65 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L69 _public prototype_ `ECustomizableObjectProjectorType GetProjectorType() const;`
- L71 _public prototype_ `FVector GetProjectorPosition() const;`
- L73 _public prototype_ `void SetProjectorPosition(const FVector& Position);`
- L75 _public prototype_ `FVector GetProjectorDirection() const;`
- L77 _public prototype_ `void SetProjectorDirection(const FVector& Direction);`
- L79 _public prototype_ `FVector GetProjectorUp() const;`
- L81 _public prototype_ `void SetProjectorUp(const FVector& Up);`
- L83 _public prototype_ `FVector GetProjectorScale() const;`
- L85 _public prototype_ `void SetProjectorScale(const FVector& Scale);`
- L87 _public prototype_ `float GetProjectorAngle() const;`
- L89 _public prototype_ `void SetProjectorAngle(float Angle);`
- L94 _private member_ `ECustomizableObjectProjectorType ProjectionType_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeProjectorParameter.h` (Private)


#### class `UCustomizableObjectNodeProjectorParameter`  
`class UCustomizableObjectNodeProjectorParameter : public UCustomizableObjectNodeParameter`  
_L20-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter`
- L26 _public member_ `FCustomizableObjectProjector DefaultValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, meta = (ShowOnlyInnerProperties))`
- L29 _public member_ `float ProjectionAngle = 360.0f;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, Meta = (DisplayName = "Projection Angle (degrees)"))`
- L32 _public member_ `uint32 ReferenceSkeletonIndex_DEPRECATED = 0;` — `UPROPERTY()`
- L35 _public member_ `FName ReferenceSkeletonComponent;` — `UPROPERTY(EditAnywhere, Category = ProjectorSnapToBone)`
- L38 _public member_ `FName ProjectorBone;` — `UPROPERTY(EditAnywhere, Category = ProjectorSnapToBone)`
- L41 _public member_ `FVector BoneComboBoxLocation = FVector::ZeroVector;` — Temporary variable where to put the location information for bone combo box selection changes (in FCustomizableObjectNodeProjectorParameterDetails)
- L44 _public member_ `FVector BoneComboBoxForwardDirection = FVector::ZeroVector;` — Temporary variable where to put the direction information for bone combo box selection changes (in FCustomizableObjectNodeProjectorParameterDetails)
- L47 _public member_ `FVector BoneComboBoxUpDirection = FVector::ZeroVector;` — Temporary variable where to put the direction information for bone combo box selection changes (in FCustomizableObjectNodeProjectorParameterDetails)
- L50 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L53 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L56 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface
- L60 _public prototype_ `ECustomizableObjectProjectorType GetProjectorType() const;`
- L62 _public prototype_ `FVector GetProjectorDefaultPosition() const;`
- L64 _public prototype_ `void SetProjectorDefaultPosition(const FVector& Position);`
- L66 _public prototype_ `FVector GetProjectorDefaultDirection() const;`
- L68 _public prototype_ `void SetProjectorDefaultDirection(const FVector& Direction);`
- L70 _public prototype_ `FVector GetProjectorDefaultUp() const;`
- L72 _public prototype_ `void SetProjectorDefaultUp(const FVector& Up);`
- L74 _public prototype_ `FVector GetProjectorDefaultScale() const;`
- L76 _public prototype_ `void SetProjectorDefaultScale(const FVector& Scale);`
- L78 _public prototype_ `float GetProjectorDefaultAngle() const;`
- L80 _public prototype_ `void SetProjectorDefaultAngle(float Angle);`
- L85 _private member_ `ECustomizableObjectProjectorType ProjectionType_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeProjectorParameterDetails.h` (Private)


#### class `FCustomizableObjectNodeProjectorParameterDetails`  
`class FCustomizableObjectNodeProjectorParameterDetails : public FCustomizableObjectNodeParameterDetails`  
_L16-52_
- inherits: `FCustomizableObjectNodeParameterDetails`
- L20 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L29 _private member_ `TSharedPtr<class STextComboBox> BoneSelectionComboBox = nullptr;` — The combo box that we use to display a list of bone names for the current Skeletal mesh
- L31 _private member_ `FName ProjectorBoneName;`
- L32 _private member_ `TSharedPtr<FString> BoneToSelect;`
- L33 _private member_ `TArray< TSharedPtr<FString> > BoneComboOptions;`
- L35 _private member_ `class UCustomizableObjectNodeProjectorConstant* NodeConstant = nullptr;`
- L36 _private member_ `class UCustomizableObjectNodeProjectorParameter* NodeParameter = nullptr;`
- L38 _private prototype_ `FReply OnProjectorCopyPressed() const;`
- L39 _private prototype_ `FReply OnProjectorPastePressed() const;`
- L41 _private member_ `class USkeletalMesh* SkeletalMesh = nullptr;`
- L44 _private prototype_ `void CaptureContextData();` — Cache the Skeletal Mesh of the component being pointed at and the Projector Parameter name of the node whose descriptor this class edits
- L47 _private prototype_ `void CacheSkeletalMeshBoneNames();` — Cache the names of the bones present in the cached Skeletal Mesh
- L49 _private prototype_ `void OnBoneComboBoxSelectionChanged(TSharedPtr<FString> InSelection, ESelectInfo::Type InSelectInfo, TSharedRef<IPropertyHandle> InBoneProperty);`
- L50 _private prototype_ `void OnReferenceSkeletonComponentChanged();`
- L51 _private prototype_ `EVisibility ShouldBoneDropdownBeVisible() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeReroute.h` (Private)


#### class `UCustomizableObjectNodeReroute`  
`class UCustomizableObjectNodeReroute : public UCustomizableObjectNode`  
_L12-48_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- desc: Code based on UK2Node_Knot.
- L18 _public prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L19 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L20 _public prototype_ `virtual bool ShouldOverridePinNames() const override;`
- L21 _public prototype_ `virtual FText GetPinNameOverride(const UEdGraphPin& Pin) const override;`
- L22 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L23 _public prototype_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override;`
- L24 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L25 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L26 _public prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L27 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L31 _public prototype_ `virtual void ReconstructNode(UCustomizableObjectNodeRemapPins* RemapPinsMode) override;`
- L32 _public prototype_ `virtual bool IsSingleOutputNode() const override;`
- L35 _public prototype_ `UEdGraphPin* GetInputPin() const;` — Own interface
- L37 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L41 _private prototype_ `void PropagatePinType();` — Code based on UK2Node_Knot::PropagatePinType.
- L44 _private prototype_ `void PropagatePinTypeFromDirection(bool bFromInput);` — Code based on UK2Node_Knot::PropagatePinTypeFromDirection.
- L47 _private member_ `bool bRecursionGuard = false;` — Code based on UK2Node_Knot. Recursion guard boolean to prevent PropagatePinType from hanging if there is a cycle of reroute nodes.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeSkeletalMesh.h` (Private)


#### class `SGraphNodeSkeletalMesh`  
`class SGraphNodeSkeletalMesh : public SCustomizableObjectNode`  
_L38-82_
- inherits: `SCustomizableObjectNode`
- desc: Class to render the Skeletal Mesh thumbnail of a CustomizableObjectNodeSkeletalMesh
- L42 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeSkeletalMesh)`
- L43 _public prototype_ `SLATE_END_ARGS();`
- L45 _public function_ `SGraphNodeSkeletalMesh() : SCustomizableObjectNode()`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);` — Builds the SGraphNodeSkeletalMesh when needed
- L51 _public prototype_ `void UpdateGraphNode();` — Calls the needed functions to build the SGraphNode widgets
- L54 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;` — Overriden functions to build the SGraphNode widgets
- L55 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L56 _public function_ `virtual bool ShouldAllowCulling() const override`
- L59 _public prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Callbacks for the widget
- L60 _public prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;`
- L61 _public prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;`
- L62 _public prototype_ `EVisibility ExpressionPreviewVisibility() const;`
- L65 _public member_ `TSharedPtr<ISinglePropertyView> SkeletalMeshSelector;` — Single property that only draws the combo box widget of the skeletal mesh
- L68 _public member_ `class UCustomizableObjectNodeSkeletalMesh* NodeSkeletalMesh;` — Pointer to the NodeSkeletalMesh that owns this SGraphNode
- L73 _private member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;` — Classes needed to get and render the thumbnail of the Skeletal Mesh
- L74 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`
- L77 _private member_ `float WidgetSize;` — This parameter defines the size of the thumbnail widget inside the Node
- L80 _private member_ `uint32 ThumbnailSize;` — This parameter defines the resolution of the thumbnail

#### class `UCustomizableObjectNodeSkeletalMeshRemapPinsBySection`  
`class UCustomizableObjectNodeSkeletalMeshRemapPinsBySection : public UCustomizableObjectNodeRemapPinsByNameDefaultPin`  
_L87-92_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPinsByNameDefaultPin`
- desc: Remap pins by pin PinData.
- L91 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin) const override;`

#### class `UCustomizableObjectNodeSkeletalMeshPinDataSection`  
`class UCustomizableObjectNodeSkeletalMeshPinDataSection : public UCustomizableObjectNodePinData`  
_L97-117_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodePinData`
- desc: PinData of a pin that belongs to a Skeletal Mesh Section.
- L102 _public prototype_ `void Init(int32 InLODIndex, int32 InSectionIndex);`
- L104 _public prototype_ `int32 GetLODIndex() const;`
- L106 _public prototype_ `int32 GetSectionIndex() const;`
- L109 _protected prototype_ `virtual bool Equals(const UCustomizableObjectNodePinData& Other) const override;`
- L113 _private member_ `int32 LODIndex = -1;` — `UPROPERTY()`
- L116 _private member_ `int32 SectionIndex = -1;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeSkeletalMeshPinDataMesh`  
`class UCustomizableObjectNodeSkeletalMeshPinDataMesh : public UCustomizableObjectNodeSkeletalMeshPinDataSection`  
_L122-137_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeSkeletalMeshPinDataSection`
- desc: PinData of a Mesh pin.
- L130 _public prototype_ `virtual void Copy(const UCustomizableObjectNodePinData& Other) override;` — Virtual function used to copy pin data when remapping pins.
- L132 _public prototype_ `void Init(int32 InLODIndex, int32 InSectionIndex, int32 NumTexCoords);`
- L136 _public member_ `TArray<TObjectPtr<UCustomizableObjectLayout>> Layouts;` — `UPROPERTY()` — Layouts related to this Mesh pin

#### class `UCustomizableObjectNodeSkeletalMeshPinDataImage`  
`class UCustomizableObjectNodeSkeletalMeshPinDataImage : public UCustomizableObjectNodeSkeletalMeshPinDataSection`  
_L142-157_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeSkeletalMeshPinDataSection`
- desc: PinData of a Image pin.
- L147 _public prototype_ `void Init(int32 InLODIndex, int32 InSectionIndex, FGuid InTextureParameterId);`
- L149 _public prototype_ `FGuid GetTextureParameterId() const;`
- L152 _protected prototype_ `virtual bool Equals(const UCustomizableObjectNodePinData& Other) const override;`
- L156 _private member_ `FGuid TextureParameterId;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeSkeletalMeshPinDataLayout`  
`class UCustomizableObjectNodeSkeletalMeshPinDataLayout : public UCustomizableObjectNodeSkeletalMeshPinDataSection`  
_L162-177_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeSkeletalMeshPinDataSection`
- desc: PinData of a Layout pin.
- L167 _public prototype_ `void Init(int32 InLODIndex, int32 InSectionIndex, int32 InUVIndex);`
- L169 _public prototype_ `int32 GetUVIndex() const;`
- L172 _protected prototype_ `virtual bool Equals(const UCustomizableObjectNodePinData& Other) const override;`
- L176 _private member_ `int32 UVIndex = -1;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeSkeletalMesh`  
`class UCustomizableObjectNodeSkeletalMesh : public UCustomizableObjectNode, public ICustomizableObjectNodeMeshInterface`  
_L182-277_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode,ICustomizableObjectNodeMeshInterface`
- L188 _public member_ `TSoftObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L192 _public member_ `FEdGraphPinReference DefaultPin;` — `UPROPERTY()` — Default pin when there is no mesh.
- L196 _public member_ `TArray<FString> UsedRealTimeMorphTargetNames;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Morphs
- L199 _public member_ `bool bUseAllRealTimeMorphs = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L204 _public member_ `TSoftClassPtr<UAnimInstance> AnimInstance;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — The anim instance that will be gathered by a Generated instance if it contains this skeletal mesh part, it will be grouped by component and AnimBlueprintSlot (the next UProperty).
- L207 _public member_ `int32 AnimBlueprintSlot_DEPRECATED;` — `UPROPERTY()`
- L211 _public member_ `FName AnimBlueprintSlotName;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — The anim slot associated with the AnimInstance
- L216 _public member_ `FGameplayTagContainer AnimationGameplayTags;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Animation tags that will be gathered by a Generated instance if it contains this skeletal mesh part, it will not be grouped by component or AnimBlueprintSlot
- L219 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L222 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L223 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L224 _public prototype_ `virtual FText GetTooltipText() const override;`
- L227 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L228 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L229 _public prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const override;`
- L230 _public prototype_ `virtual bool HasPinViewer() const override;`
- L233 _public prototype_ `virtual UTexture2D* FindTextureForPin(const UEdGraphPin* Pin) const override;` — UCustomizableObjectNodeMesh interface
- L234 _public prototype_ `virtual TArray<UCustomizableObjectLayout*> GetLayouts(const UEdGraphPin& MeshPin) const override;`
- L235 _public prototype_ `virtual TSoftObjectPtr<UStreamableRenderAsset> GetMesh() const override;`
- L236 _public prototype_ `virtual UEdGraphPin* GetMeshPin(int32 LOD, int32 SectionIndex) const override;`
- L237 _public prototype_ `virtual void GetPinSection(const UEdGraphPin& Pin, int32& OutLODIndex, int32& OutSectionIndex) const override;`
- L242 _public prototype_ `UMaterialInterface* GetMaterialFor(const UEdGraphPin* Pin) const;` — Returns the material associated to the given output pin.
- L243 _public prototype_ `FSkeletalMaterial* GetSkeletalMaterialFor(const UEdGraphPin& Pin) const;`
- L244 _public prototype_ `int32 GetSkeletalMaterialIndexFor(const UEdGraphPin& Pin) const;`
- L246 _public prototype_ `const FSkelMeshSection* GetSkeletalMeshSectionFor(const UEdGraphPin& Pin) const;`
- L249 _public function_ `virtual bool ProvidesCustomPinRelevancyTest() const override`
- L250 _public prototype_ `virtual bool IsPinRelevant(const UEdGraphPin* Pin) const override;`
- L252 _public prototype_ `virtual bool IsNodeOutDatedAndNeedsRefresh() override;`
- L253 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L256 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;` — Creates the SGraph Node widget for the thumbnail
- L259 _public member_ `bool bCollapsed = true;` — Determines if the Node is collapsed or not
- L262 _public member_ `TWeakPtr< SGraphNodeSkeletalMesh > GraphNodeSkeletalMesh;` — Pointer to the SGraphNode Skeletal Mesh
- L265 _private prototype_ `UMaterialInterface* GetMaterialInterfaceFor(const int32 LODIndex, const int32 MaterialIndex) const;`
- L266 _private prototype_ `FSkeletalMaterial* GetSkeletalMaterialFor(const int32 LODIndex, const int32 SectionIndex) const;`
- L267 _private prototype_ `int32 GetSkeletalMaterialIndexFor(const int32 LODIndex, const int32 SectionIndex) const;`
- L269 _private prototype_ `const FSkelMeshSection* GetSkeletalMeshSectionFor(const int32 LODIndex, const int32 SectionIndex) const;`
- L271 _private prototype_ `void LoadObjects();`
- L276 _private member_ `TArray<FCustomizableObjectNodeSkeletalMeshLOD> LODs_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L15 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeSkeletalMeshDetails.h` (Private)


#### class `FCustomizableObjectNodeSkeletalMeshDetails`  
`class FCustomizableObjectNodeSkeletalMeshDetails : public FCustomizableObjectNodeDetails`  
_L12-27_
- inherits: `FCustomizableObjectNodeDetails`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L23 _private prototype_ `void GenerateMeshSectionOptions(TArray<FLayoutEditorMeshSection>& OutMeshSections);`
- L26 _private member_ `class UCustomizableObjectNodeSkeletalMesh* Node;` — Pointer to the node represented in this details

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeSkeletalMeshParameter.h` (Private)


#### class `UCustomizableObjectNodeSkeletalMeshParameterPinDataSection`  
`class UCustomizableObjectNodeSkeletalMeshParameterPinDataSection : public UCustomizableObjectNodePinData`  
_L21-46_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodePinData`
- desc: PinData of a pin that belongs to a Skeletal Mesh Section.
- L26 _public prototype_ `void Init(int32 LODIndex, int32 InSectionIndex, int32 NumTexCoords);`
- L28 _public prototype_ `int32 GetLODIndex() const;`
- L30 _public prototype_ `int32 GetSectionIndex() const;`
- L34 _public member_ `TArray<TObjectPtr<UCustomizableObjectLayout>> Layouts;` — `UPROPERTY()` — Layouts related to this Mesh pin
- L38 _protected prototype_ `virtual bool Equals(const UCustomizableObjectNodePinData& Other) const override;`
- L42 _private member_ `int32 LODIndex = -1;` — `UPROPERTY()`
- L45 _private member_ `int32 SectionIndex = -1;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeSkeletalMeshParameter`  
`class UCustomizableObjectNodeSkeletalMeshParameter : public UCustomizableObjectNodeParameter, public ICustomizableObjectNodeMeshInterface`  
_L50-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter,ICustomizableObjectNodeMeshInterface`
- L56 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L59 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L60 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L61 _public prototype_ `virtual FText GetTooltipText() const override;`
- L62 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L65 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L66 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L67 _public prototype_ `virtual bool HasPinViewer() const override;`
- L68 _public prototype_ `virtual bool IsAffectedByLOD() const override;`
- L71 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeParameter interface
- L74 _public prototype_ `virtual UTexture2D* FindTextureForPin(const UEdGraphPin* Pin) const override;` — ICustomizableObjectNodeMeshInterface interface
- L75 _public prototype_ `virtual TArray<UCustomizableObjectLayout*> GetLayouts(const UEdGraphPin& MeshPin) const override;`
- L76 _public prototype_ `virtual TSoftObjectPtr<UStreamableRenderAsset> GetMesh() const override;`
- L77 _public prototype_ `virtual UEdGraphPin* GetMeshPin(int32 LOD, int32 SectionIndex) const override;`
- L78 _public prototype_ `virtual void GetPinSection(const UEdGraphPin& Pin, int32& OutLODIndex, int32& OutSectionIndex) const override;`
- L81 _public prototype_ `void GetPinSection(const UEdGraphPin& Pin, int32& OutSectionIndex) const;` — Own interface
- L82 _public prototype_ `UMaterialInterface* GetMaterialInterfaceFor(const int32 SectionIndex) const;`
- L83 _public prototype_ `FSkeletalMaterial* GetSkeletalMaterialFor(const int32 SectionIndex) const;`
- L84 _public prototype_ `int32 GetSkeletalMaterialIndexFor(const UEdGraphPin& Pin) const;`
- L85 _public prototype_ `int32 GetSkeletalMaterialIndexFor(const int32 SectionIndex) const;`
- L89 _public member_ `TSoftObjectPtr<USkeletalMesh> DefaultValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)` — Default value of the parameter.
- L92 _public member_ `TSoftObjectPtr<USkeletalMesh> ReferenceValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L95 _public member_ `FEdGraphPinReference MutableSkeletalMeshPin;` — `UPROPERTY()`
- L98 _public member_ `FEdGraphPinReference PassthroughPin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeSkeletalMeshParameterDetails.h` (Private)


#### class `FCustomizableObjectNodeSkeletalMeshParameterDetails`  
`class FCustomizableObjectNodeSkeletalMeshParameterDetails : public FCustomizableObjectNodeParameterDetails`  
_L13-28_
- inherits: `FCustomizableObjectNodeParameterDetails`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L24 _private prototype_ `void GenerateMeshSectionOptions(TArray<FLayoutEditorMeshSection>& OutMeshSections);`
- L27 _private member_ `class UCustomizableObjectNodeSkeletalMeshParameter* Node;` — Pointer to the node represented in this details

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeStaticMesh.h` (Private)


#### class `SGraphNodeStaticMesh`  
`class SGraphNodeStaticMesh : public SCustomizableObjectNode`  
_L31-77_
- inherits: `SCustomizableObjectNode`
- desc: Class to render the Static Mesh thumbnail of a CustomizableObjectNodeStaticMesh
- L35 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeStaticMesh)`
- L36 _public prototype_ `SLATE_END_ARGS();`
- L38 _public function_ `SGraphNodeStaticMesh() : SCustomizableObjectNode()`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);` — Builds the SGraphNodeStaticMesh when needed
- L44 _public prototype_ `void UpdateGraphNode();` — Calls the needed functions to build the SGraphNode widgets
- L47 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;` — Overriden functions to build the SGraphNode widgets
- L48 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L49 _public function_ `virtual bool ShouldAllowCulling() const override`
- L52 _public prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Callbacks for the widget
- L53 _public prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;`
- L54 _public prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;`
- L55 _public prototype_ `EVisibility ExpressionPreviewVisibility() const;`
- L60 _public member_ `TSharedPtr<class ISinglePropertyView> StaticMeshSelector;` — Single property that only draws the combo box widget of the static mesh
- L63 _public member_ `class UCustomizableObjectNodeStaticMesh* NodeStaticMesh = nullptr;` — Pointer to the NodeStaticMesh that owns this SGraphNode
- L68 _private member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;` — Classes needed to get and render the thumbnail of the Static Mesh
- L69 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`
- L72 _private member_ `float WidgetSize;` — This parameter defines the size of the thumbnail widget inside the Node
- L75 _private member_ `uint32 ThumbnailSize;` — This parameter defines the resolution of the thumbnail

#### struct `FCustomizableObjectNodeStaticMeshMaterial`  
`struct FCustomizableObjectNodeStaticMeshMaterial`  
_L81-105_
- reflection: `USTRUCT()`
- L86 _public member_ `FString Name;` — `UPROPERTY()`
- L89 _public member_ `TObjectPtr<UEdGraphPin_Deprecated> MeshPin_DEPRECATED;` — `UPROPERTY()`
- L92 _public member_ `TObjectPtr<UEdGraphPin_Deprecated> LayoutPin_DEPRECATED;` — `UPROPERTY()`
- L95 _public member_ `TArray< TObjectPtr<UEdGraphPin_Deprecated>> ImagePins_DEPRECATED;` — `UPROPERTY()`
- L98 _public member_ `FEdGraphPinReference MeshPinRef;` — `UPROPERTY()`
- L101 _public member_ `FEdGraphPinReference LayoutPinRef;` — `UPROPERTY()`
- L104 _public member_ `TArray<FEdGraphPinReference> ImagePinsRef;` — `UPROPERTY()`

#### struct `FCustomizableObjectNodeStaticMeshLOD`  
`struct FCustomizableObjectNodeStaticMeshLOD`  
_L109-115_
- reflection: `USTRUCT()`
- L114 _public member_ `TArray<FCustomizableObjectNodeStaticMeshMaterial> Materials;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeStaticMesh`  
`class UCustomizableObjectNodeStaticMesh : public UCustomizableObjectNode, public ICustomizableObjectNodeMeshInterface`  
_L119-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode,ICustomizableObjectNodeMeshInterface`
- L125 _public member_ `TSoftObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L129 _public member_ `TArray<FCustomizableObjectNodeStaticMeshLOD> LODs;` — `UPROPERTY()` — Images
- L133 _public member_ `FEdGraphPinReference DefaultPin;` — `UPROPERTY()` — Default pin when there is no mesh.
- L136 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L137 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L140 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L141 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L142 _public prototype_ `virtual FText GetTooltipText() const override;`
- L145 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L146 _public function_ `virtual bool ProvidesCustomPinRelevancyTest() const override`
- L147 _public prototype_ `virtual bool IsPinRelevant(const UEdGraphPin* Pin) const override;`
- L148 _public prototype_ `virtual UCustomizableObjectNodeRemapPinsByName* CreateRemapPinsByName() const override;`
- L149 _public prototype_ `virtual bool HasPinViewer() const override;`
- L150 _public prototype_ `virtual bool IsNodeOutDatedAndNeedsRefresh() override;`
- L151 _public prototype_ `virtual FString GetRefreshMessage() const override;`
- L152 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L155 _public prototype_ `virtual UTexture2D* FindTextureForPin(const UEdGraphPin* Pin) const override;` — UCustomizableObjectNodeMesh interface
- L156 _public prototype_ `virtual TArray<UCustomizableObjectLayout*> GetLayouts(const UEdGraphPin& OutPin) const override;`
- L157 _public prototype_ `virtual TSoftObjectPtr<UStreamableRenderAsset> GetMesh() const override;`
- L158 _public prototype_ `virtual UEdGraphPin* GetMeshPin(int32 LOD, int32 SectionIndex) const override;`
- L159 _public prototype_ `virtual void GetPinSection(const UEdGraphPin& Pin, int32& OutLODIndex, int32& OutSectionIndex) const override;`
- L162 _public prototype_ `UMaterialInterface* GetMaterialFor(const UEdGraphPin* Pin) const;` — Returns the material associated to the given output pin.
- L165 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;` — Creates the SGraph Node widget for the thumbnail
- L168 _public member_ `bool bCollapsed = true;` — Determines if the Node is collapsed or not
- L171 _public member_ `TWeakPtr< SGraphNodeStaticMesh > GraphNodeStaticMesh;` — Pointer to the SGraphNodeStaticMesh

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeStaticString.h` (Private)


#### class `UCustomizableObjectNodeStaticString`  
`class UCustomizableObjectNodeStaticString : public UCustomizableObjectNode`  
_L12-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L18 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L19 _public prototype_ `virtual FText GetTooltipText() const override;`
- L20 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L24 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L25 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L26 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L27 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L28 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy(const UEdGraphPin& Pin) const override;`
- L31 _public member_ `FString Value;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTable.h` (Private)


#### enum `ETableTextureType`  
`enum class ETableTextureType : uint8`  
_L33-37_
- reflection: `UENUM()`
- desc: Enum class for the different types of image pins
- L35 _public enumerator_ `PASSTHROUGH_TEXTURE = 0 UMETA(DisplayName = "Object")`
- L36 _public enumerator_ `MUTABLE_TEXTURE = 1 UMETA(DisplayName = "Mutable")`

#### enum `ETableMeshPinType`  
`enum class ETableMeshPinType : uint8`  
_L41-46_
- desc: Enum class for the different types of pin meshes
- L43 _public enumerator_ `NONE = 0`
- L44 _public enumerator_ `SKELETAL_MESH = 1`
- L45 _public enumerator_ `STATIC_MESH = 2`

#### enum `ETableDataGatheringSource`  
`enum class ETableDataGatheringSource : uint8`  
_L51-58_
- reflection: `UENUM()`
- desc: Enum to decide where the data comes from: Struct or Data Table
- L54 _public enumerator_ `ETDGM_DataTable = 0 UMETA(DisplayName = "Data Table")` — Gathers the information from a data table
- L57 _public enumerator_ `ETDGM_AssetRegistry = 1 UMETA(DisplayName = " Struct + Asset Registry")` — When compiling the CO, it uses the asset registry to gather and generate a data table. It uses all the data tables found in the specified paths that are references of the selected structure.

#### enum `ETableCompilationFilterOperationType`  
`enum class ETableCompilationFilterOperationType : uint8`  
_L61-68_
- reflection: `UENUM()`
- L64 _public enumerator_ `TCFOT_OR = 0 UMETA(DisplayName = "OR")` — At least one of the filters should be in the Data Table row
- L67 _public enumerator_ `TCFOT_AND = 1 UMETA(DisplayName = "AND")` — All filters should be in the Data Table row

#### struct `FTableNodeColumnData`  
`struct FTableNodeColumnData`  
_L72-87_
- reflection: `USTRUCT()`
- L78 _public member_ `FString AnimInstanceColumnName = "";` — `UPROPERTY()` — Anim Instance Column name related to this Mesh pin
- L82 _public member_ `FString AnimSlotColumnName = "";` — `UPROPERTY()` — Anim Slot Column name related to this Mesh pin
- L86 _public member_ `FString AnimTagColumnName = "";` — `UPROPERTY()` — Anim Tag Column name related to this Mesh pin

#### class `UCustomizableObjectNodeTableObjectPinData`  
`class UCustomizableObjectNodeTableObjectPinData : public UCustomizableObjectNodePinData`  
_L92-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- desc: Base class for all Table Pins.
- L100 _public member_ `FGuid StructColumnId;` — `UPROPERTY()` — Id of the property associated to a struct column
- L104 _public member_ `FString ColumnName_DEPRECATED = "";` — `UPROPERTY()` — Name of the data table column property related to the pin
- L108 _public member_ `FString ColumnPropertyName = "";` — `UPROPERTY()` — Unique Name of the struct property related to the pin. Used to data purposes: search struct porperty, set mutable column name...
- L112 _public member_ `FString ColumnDisplayName = "";` — `UPROPERTY()` — Name of the data table column related to the pin. Used for UI purposes.

#### class `UCustomizableObjectNodeTableImagePinData`  
`class UCustomizableObjectNodeTableImagePinData : public UCustomizableObjectNodeTableObjectPinData`  
_L118-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeTableObjectPinData`
- desc: Additional data for Image pins.
- L124 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UObject interface
- L125 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L126 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L129 _public member_ `ETableTextureType ImageMode = ETableTextureType::MUTABLE_TEXTURE;` — `UPROPERTY(EditAnywhere, Category = NoCategory, DisplayName = "Texture Parameter Mode")`
- L132 _public member_ `TObjectPtr<UCustomizableObjectNodeTable> NodeTable = nullptr;` — `UPROPERTY()`
- L137 _private member_ `bool bIsArrayTexture_DEPRECATED = false;` — `UPROPERTY()` — Replaced by the more general bIsNot2DTexture
- L141 _public member_ `bool bIsNotTexture2D = false;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeTableMeshPinData`  
`class UCustomizableObjectNodeTableMeshPinData : public UCustomizableObjectNodeTableObjectPinData`  
_L147-176_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeTableObjectPinData`
- desc: Additional data for Mesh pins.
- L155 _public member_ `FString AnimInstanceColumnName_DEPRECATED = "";` — `UPROPERTY()` — Anim Instance Column name related to this Mesh pin
- L159 _public member_ `FString AnimSlotColumnName_DEPRECATED = "";` — `UPROPERTY()` — Anim Slot Column name related to this Mesh pin
- L163 _public member_ `FString AnimTagColumnName_DEPRECATED = "";` — `UPROPERTY()` — Anim Tag Column name related to this Mesh pin
- L167 _public member_ `int32 LOD = 0;` — `UPROPERTY()` — LOD of the mesh related to this Mesh pin
- L171 _public member_ `int32 Material = 0;` — `UPROPERTY()` — Section Index (Surface Index) of the mesh related to this Mesh pin
- L175 _public member_ `TArray< TObjectPtr<UCustomizableObjectLayout> > Layouts;` — `UPROPERTY()` — Layouts related to this Mesh pin

#### class `UCustomizableObjectNodeTableRemapPins`  
`class UCustomizableObjectNodeTableRemapPins : public UCustomizableObjectNodeRemapPinsByName`  
_L180-190_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPinsByName`
- L186 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin) const override;` — Specific method to decide when two pins are equal
- L189 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;` — Method to use in the RemapPins step of the node reconstruction process

#### struct `FTableNodeCompilationFilter`  
`struct FTableNodeCompilationFilter`  
_L194-213_
- reflection: `USTRUCT()`
- L200 _public member_ `FName FilterColumn;` — `UPROPERTY(EditAnywhere, Category = CompilationRestrictions)` — Column of the Data Table that contains the compilation filters of each row
- L205 _public member_ `TArray<FString> Filters;` — `UPROPERTY(EditAnywhere, Category = CompilationRestrictions)` — Compilation filters required for this Table node represented in a string Supported types: Names, Strings, int, bools (true, false).
- L210 _public member_ `ETableCompilationFilterOperationType OperationType = ETableCompilationFilterOperationType::TCFOT_OR;` — `UPROPERTY(EditAnywhere, Category = CompilationRestrictions)` — Determines how Filters interact with the values of the Compilation Filter Column. Check the tooltip of each operation for more information.
- L212 _public prototype_ `bool operator==(const FTableNodeCompilationFilter&) const = default;`

#### class `UCustomizableObjectNodeTable`  
`class UCustomizableObjectNodeTable : public UCustomizableObjectNode`  
_L217-478_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L225 _public member_ `FString ParameterName = "De` — `UPROPERTY(EditAnywhere, Category = TableProperties)` — Name of the property parameter
- L229 _public member_ `bool bAddNoneOption;` — `UPROPERTY(EditAnywhere, Category = TableProperties)` — If true, adds a "None" parameter option
- L233 _public member_ `ETableDataGatheringSource TableDataGatheringMode = ETableDataGatheringSource::ETDGM_DataTable;` — `UPROPERTY(EditAnywhere, Category = TableProperties)` — Source where table gathers the data
- L237 _public member_ `TSoftObjectPtr<UDataTable> Table = nullptr;` — `UPROPERTY(EditAnywhere, Category = TableProperties, meta = (DontUpdateWhileEditing, EditCondition = "TableDataGatheringMode == ETableDataGatheringSource::ETDGM_DataTable", EditConditionHides))` — Pointer to the Data Table Asset represented in this node
- L241 _public member_ `TSoftObjectPtr<UScriptStruct> Structure = nullptr;` — `UPROPERTY(EditAnywhere, Category = TableProperties, meta = (DontUpdateWhileEditing, EditCondition = "TableDataGatheringMode == ETableDataGatheringSource::ETDGM_AssetRegistry", EditConditionHides))` — Pointer to the Struct Asset represented in this node
- L244 _public member_ `TArray<FName> FilterPaths;` — `UPROPERTY(EditAnywhere, Category = TableProperties, meta = (EditCondition = "TableDataGatheringMode == ETableDataGatheringSource::ETDGM_AssetRegistry", EditConditionHides))`
- L248 _public member_ `FName VersionColumn;` — `UPROPERTY(EditAnywhere, Category = CompilationRestrictions)` — Name of the column that contains the Version options.
- L252 _public member_ `FName DefaultRowName;` — `UPROPERTY(EditAnywhere, Category = TableProperties)` — Name of the row that will be used as default value.
- L255 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (DisplayName = "Parameter UI Metadata"))`
- L259 _public member_ `FName ParamUIMetadataColumn;` — `UPROPERTY(EditAnywhere, Category = UI)` — Name of the column that contains the MutableUIMetadata of the row options.
- L263 _public member_ `FName ThumbnailColumn;` — `UPROPERTY(EditAnywhere, Category = UI)` — Name of the column that contains the asset to use its thumbnails as option thumbnails.
- L266 _public member_ `bool bGatherTags = true;` — `UPROPERTY(EditAnywhere, Category = UI, meta = (Tooltip = "Given a row, add all tags found in GameplayTag columns to its Parameter UI Metadata"))`
- L270 _public member_ `TObjectPtr<USkeletalMesh> PoseReferenceMesh;` — `UPROPERTY(EditAnywhere, Category = TableProperties)` — TODO Remove. Only used because poses are the diff from a Reference Skeleton. Once the pose is absolute remove this.
- L274 _public member_ `TMap<FGuid, FTableNodeColumnData> ColumnDataMap_DEPRECATED;` — `UPROPERTY()` — Map to relate a Structure Column with its Data
- L280 _public member_ `TMap<FString, FTableNodeColumnData> PinColumnDataMap;` — `UPROPERTY()` — Map to relate a Structure Column with its Data Key: ColumnPropertyName variable of the PinData
- L286 _public member_ `bool bUseMaterialColor = false;` — `UPROPERTY(EditAnywhere, Category = TableProperties, meta = (DisplayAfter = "bAddNoneOption", EditCondition = "bAddNoneOption==true", EditConditionHides))` — If true, the "None" colors will use the color of the material parameter. If false, the "None" colors will be black. Note: if this option is true and the colors are used to generate textures, "None" option colors will be set to black.
- L289 _public member_ `TArray<FTableNodeCompilationFilter> CompilationFilterOptions;` — `UPROPERTY(EditAnywhere, Category = CompilationRestrictions)`
- L292 _public member_ `static const TArray<FFieldClass*> SupportedFilterTypes;` — Array with all the classes supported to be used as row filters
- L297 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;` — UObject interface
- L298 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L301 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L302 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L303 _public prototype_ `FText GetTooltipText() const override;`
- L304 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L305 _public function_ `virtual bool GetCanRenameNode() const override`
- L308 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L309 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L310 _public prototype_ `bool IsNodeOutDatedAndNeedsRefresh() override;`
- L311 _public prototype_ `FString GetRefreshMessage() const override;`
- L312 _public prototype_ `virtual bool ProvidesCustomPinRelevancyTest() const override;`
- L313 _public prototype_ `virtual bool IsPinRelevant(const UEdGraphPin* Pin) const override;`
- L314 _public prototype_ `UCustomizableObjectNodeTableRemapPins* CreateRemapPinsDefault() const;`
- L315 _public prototype_ `virtual bool HasPinViewer() const override;`
- L316 _public prototype_ `virtual TSharedPtr<IDetailsView> CustomizePinDetails(const UEdGraphPin& Pin) const override;`
- L319 _public prototype_ `virtual void RemapPinsData(const TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap) override;` — Allows to perform work when remapping the pin data.
- L323 _public prototype_ `UTexture2D* FindReferenceTextureParameter(const UEdGraphPin* Pin, FString ParameterImageName) const;` — Own interface Returns the reference Texture parameter from a Material
- L326 _public prototype_ `UStreamableRenderAsset* GetDefaultMeshForLayout(const UCustomizableObjectLayout* Layout) const;` — Methods to get the UVs of the skeletal mesh
- L329 _public prototype_ `TArray<UCustomizableObjectLayout*> GetLayouts(const UEdGraphPin* Pin) const;` — Methods to provide the Layouts to the Layout block editors
- L332 _public prototype_ `FString GetPinColumnName(const UEdGraphPin* Pin) const;` — Returns the name of the table column related to a pin
- L335 _public prototype_ `void GetPinLODAndSection(const UEdGraphPin* Pin, int32& LODIndex, int32& SectionIndex) const;` — Returns the LOD of the mesh associated to the input pin
- L338 _public prototype_ `void GetAnimationColumns(const FString& ColumnPropertyName, FString& AnimBPColumnName, FString& AnimSlotColumnName, FString& AnimTagColumnName) const;` — Get the anim blueprint and anim slot columns related to a mesh
- L341 _public function_ `template<class T> T* GetColumnDefaultAssetByType(FString ColumnPropertyName) const`
- L388 _public function_ `template<class T> T* GetColumnDefaultAssetByType(const UEdGraphPin* Pin) const`
- L403 _public prototype_ `FSoftObjectPtr GetSkeletalMeshAt(const UEdGraphPin* Pin, const UDataTable* DataTable, const FName& RowName) const;` — Generation Mutable Source Methods We should do this in a template!
- L404 _public prototype_ `TSoftClassPtr<UAnimInstance> GetAnimInstanceAt(const UEdGraphPin* Pin, const UDataTable* DataTable, const FName& RowName) const;`
- L407 _public prototype_ `ETableTextureType GetColumnImageMode(const FString& ColumnPropertyName) const;` — Returns the image mode of the column
- L410 _public prototype_ `ETableMeshPinType GetPinMeshType(const UEdGraphPin* Pin) const;` — Returns the mesh type of the Pin
- L413 _public prototype_ `FString GenerateSkeletalMeshMutableColumName(const FString& PinName, int32 LODIndex, int32 MaterialIndex) const;` — Functions to generate the names of a mutable table's column
- L414 _public prototype_ `FString GenerateStaticMeshMutableColumName(const FString& PinName, int32 MaterialIndex) const;`
- L417 _public prototype_ `const UScriptStruct* GetTableNodeStruct() const;` — Returns the struct pointer used to gather data
- L421 _public prototype_ `TArray<FString> GetColumnTitles() const;` — Get an array of all the column titles, using the friendly display name from the property
- L424 _public prototype_ `FProperty* FindTableProperty(const FName& PropertyName) const;` — Returns the property using its name.
- L427 _public prototype_ `FProperty* FindPinProperty(const UEdGraphPin& Pin) const;` — Returns the property linked to a pin
- L430 _public prototype_ `FProperty* FindColumnProperty(const FName& ColumnDisplayName) const;` — Returns the property linked to a column display name. Useful for properties that do not generate a pin.
- L433 _public prototype_ `TArray<FAssetData> GetParentTables() const;` — Return the list of UDataTable that will be used to compose the final UDataTable.
- L436 _public prototype_ `FSkeletalMaterial* GetDefaultSkeletalMaterialFor(const UEdGraphPin& MeshPin) const;` — Returns the skeletal material associated to the given skeletal mesh output pin.
- L439 _public prototype_ `int32 GetDefaultSkeletalMaterialIndexFor(const UEdGraphPin& MeshPin) const;` — Returns the index of the skeletal material associated to the given skeletal mesh output pin.
- L442 _public prototype_ `const FSkelMeshSection* GetDefaultSkeletalMeshSectionFor(const UEdGraphPin& MeshPin) const;` — Returns the SkeletalMesh section associated to the given skeletal mesh output pin.
- L445 _public prototype_ `TArray<FName> GetEnabledRows(const UDataTable& DataTable) const;`
- L448 _public prototype_ `static uint8* GetCellData(const FName& RowName, const UDataTable& DataTable, const FProperty& ColumnProperty);`
- L453 _private member_ `int32 NumProperties;` — `UPROPERTY()` — Number of properties to know when the node needs an update
- L455 _private member_ `FDelegateHandle OnTableChangedDelegateHandle;`
- L458 _private prototype_ `bool CheckPinUpdated(const FString& PinName, const FName& PinType) const;` — Checks if a pin already exists and if it has the same type as before the node refresh
- L462 _private member_ `bool bDisableCheckedRows_DEPRECATED = true;` — `UPROPERTY()` — If there is a bool column in the table, checked rows will not be compiled
- L466 _private member_ `FName CompilationFilterColumn_DEPRECATED;` — `UPROPERTY()` — Column of the Data Table that contains the compilation filters of each row
- L471 _private member_ `TArray<FString> CompilationFilters_DEPRECATED;` — `UPROPERTY()` — Compilation filters required for this Table node represented in a string Supported types: Names, Strings, int, bools (true, false).
- L476 _private member_ `ETableCompilationFilterOperationType FilterOperationType_DEPRECATED = ETableCompilationFilterOperationType::TCFOT_OR;` — `UPROPERTY()` — Determines how Filters interact with the values of the Compilation Filter Column. Check the tooltip of each operation for more information.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L15 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTableDetails.h` (Private)


#### enum `EAnimColumnType`  
`enum class EAnimColumnType`  
_L27-32_
- L29 _public enumerator_ `EACT_BluePrintColumn`
- L30 _public enumerator_ `EACT_SlotColumn`
- L31 _public enumerator_ `EACT_TagsColumn`

#### class `FCustomizableObjectNodeTableDetails`  
`class FCustomizableObjectNodeTableDetails : public FCustomizableObjectNodeDetails`  
_L36-178_
- inherits: `FCustomizableObjectNodeDetails`
- desc: Copy Material node details panel. Hides all properties from the inheret Material node.
- L40 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L44 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;` — Hides details copied from CustomizableObjectNodeMaterial.
- L50 _private prototype_ `void GenerateMeshColumnComboBoxOptions();` — Details ------------- Generates Mesh columns combobox options
- L51 _private prototype_ `void GenerateMeshSectionOptions(TArray<FLayoutEditorMeshSection>& OutMeshSections);`
- L54 _private prototype_ `void OnNodePinValueChanged();` — Function called when the table node has been refreshed
- L59 _private prototype_ `void GenerateAnimInstanceComboBoxOptions();` — Anim Category ------------- Generates Animation Instance combobox options
- L62 _private prototype_ `void OnAnimMeshColumnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callback for Layout ComboBox
- L65 _private prototype_ `void OnAnimInstanceComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callback for AnimInstance ComboBox
- L68 _private prototype_ `void OnAnimSlotComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callback for Anim Slot ComboBox
- L71 _private prototype_ `void OnAnimTagsComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callback for Anim Tags ComboBox
- L74 _private prototype_ `EVisibility AnimWidgetsVisibility() const;` — Set the visibility of the animation column selector widgets
- L77 _private prototype_ `void OnAnimMeshCustomRowResetButtonClicked();` — Callback to clear the mesh column to edit its animation properties
- L80 _private prototype_ `void OnAnimCustomRowResetButtonClicked(EAnimColumnType ColumnType);` — Callback to clear the animation combobox selections
- L87 _private prototype_ `TSharedPtr<FString> GenerateMutableMetaDataColumnComboBoxOptions();` — Generates MutableMetadata columns combobox options Returns the current selected option or a null pointer
- L91 _private prototype_ `TSharedPtr<FString> GenerateThumbnailColumnComboBoxOptions();` — Generates Thumbnail columns combobox options Returns the current selected option or a null pointer
- L94 _private prototype_ `void OnOpenMutableMetadataComboBox();` — Callbacks to regenerate the combobox options
- L95 _private prototype_ `void OnOpenThumbnailComboBox();`
- L98 _private prototype_ `void OnMutableMetaDataColumnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callbacks
- L99 _private prototype_ `void OnThumbnailColumnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L102 _private prototype_ `FSlateColor GetComboBoxTextColor(TArray<TSharedPtr<FString>>* CurrentOptions, const FName ColumnName) const;` — If the property selected in the combobox does not exist anymore, returns a red color.
- L105 _private prototype_ `void OnMutableMetaDataColumnComboBoxSelectionReset();` — OnComboBoxSelectionChanged Callbacks for ComboBox
- L106 _private prototype_ `void OnThumbnailColumnComboBoxSelectionReset();`
- L113 _private prototype_ `TSharedPtr<FString> GenerateVersionColumnComboBoxOptions();` — Generates MutableMetadata columns combobox options Returns the current selected option or a null pointer
- L116 _private prototype_ `void OnOpenVersionColumnComboBox();` — Callback to regenerate the combobox options
- L119 _private prototype_ `void OnVersionColumnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callback for Layout ComboBox
- L122 _private prototype_ `FSlateColor GetVersionColumnComboBoxTextColor(TArray<TSharedPtr<FString>>* CurrentOptions) const;` — Sets the combo box selection color
- L125 _private prototype_ `void OnVersionColumnComboBoxSelectionReset();` — OnComboBoxSelectionChanged Callback for Layout ComboBox
- L131 _private member_ `TWeakObjectPtr<UCustomizableObjectNodeTable> Node;` — Details ------------- Pointer to the node represented in this details
- L135 _private member_ `TSharedPtr<STextComboBox> AnimMeshColumnComboBox;` — Anim ------------- ComboBox widget to select a column from the NodeTable
- L138 _private member_ `TArray<TSharedPtr<FString>> AnimMeshColumnOptionNames;` — Array with the name of the table columns as combobox options
- L141 _private member_ `TSharedPtr<STextComboBox> AnimComboBox;` — ComboBox widget to select an Animation Instance column from the NodeTable
- L144 _private member_ `TArray<TSharedPtr<FString>> AnimOptionNames;` — Array with the name of the Animation Instance columns as combobox options
- L147 _private member_ `TSharedPtr<STextComboBox> AnimSlotComboBox;` — ComboBox widget to select an Animation Slot column from the NodeTable
- L150 _private member_ `TArray<TSharedPtr<FString>> AnimSlotOptionNames;` — Array with the name of the Animation Slot columns as combobox options
- L153 _private member_ `TSharedPtr<STextComboBox> AnimTagsComboBox;` — ComboBox widget to select an Animation Tags column from the NodeTable
- L156 _private member_ `TArray<TSharedPtr<FString>> AnimTagsOptionNames;` — Array with the name of the Animation Tags columns as combobox options
- L160 _private member_ `TArray<TSharedPtr<FString>> MutableMetaDataColumnsOptionNames;` — Mutable UI Metadata ------------- Array with the name of the MutableMetaData columns
- L162 _private member_ `TArray<TSharedPtr<FString>> ThumbnailColumnOptionNames;`
- L165 _private member_ `TSharedPtr<STextComboBox> MutableMetaDataComboBox;` — ComboBox widget to select a MutableMetaDatacolumn from the NodeTable
- L168 _private member_ `TSharedPtr<STextComboBox> ThumbnailComboBox;` — ComboBox widget to select a Thumbnail Column from the NodeTable
- L173 _private member_ `TArray<TSharedPtr<FString>> VersionColumnsOptionNames;` — Version Bridge ------------- Array with the name of the Version columns
- L176 _private member_ `TSharedPtr<STextComboBox> VersionColumnsComboBox;` — ComboBox widget to select a VersionColumn from the NodeTable

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTexture.h` (Private)


#### class `SGraphNodeTexture`  
`class SGraphNodeTexture : public SCustomizableObjectNode`  
_L23-57_
- inherits: `SCustomizableObjectNode`
- desc: Class to render the Texture thumbnail of a CustomizableObjectNodeTexture
- L26 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeTexture)`
- L27 _public prototype_ `SLATE_END_ARGS();`
- L29 _public function_ `SGraphNodeTexture() : SCustomizableObjectNode()`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);` — Builds the SGraphNodeTexture when needed
- L35 _public prototype_ `void UpdateGraphNode();` — Calls the needed functions to build the SGraphNode widgets
- L38 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;` — Overriden functions to build the SGraphNode widgets
- L39 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L40 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L41 _public function_ `virtual bool ShouldAllowCulling() const override`
- L44 _public prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Callbacks for the widget
- L45 _public prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;`
- L46 _public prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;`
- L47 _public prototype_ `EVisibility ExpressionPreviewVisibility() const;`
- L50 _public member_ `UCustomizableObjectNodeTextureBase* NodeTexture = nullptr;` — Pointer to the NodeTexture that owns this SGraphNode
- L53 _public member_ `TSharedPtr<class ISinglePropertyView> TextureSelector;` — Single property that only draws the combo box widget of the Texture
- L56 _public member_ `FSlateBrush TextureBrush;` — Brush to draw the texture to the widget

#### class `UCustomizableObjectNodeTextureBase`  
`class UCustomizableObjectNodeTextureBase : public UCustomizableObjectNode`  
_L61-74_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UCustomizableObjectNode`
- L67 _public member_ `bool bCollapsed = true;` — Determines if the Node is collapsed or not
- L70 _public prototype_ `TSharedPtr<SGraphNode> CreateVisualWidget() override;` — Creates the SGraph Node widget for the thumbnail
- L73 _public prototype_ `virtual TObjectPtr<UTexture> GetTexture() PURE_VIRTUAL(UCustomizableObjectNodeTextureBase::GetTexture, return {};);`

#### class `UCustomizableObjectNodeTexture`  
`class UCustomizableObjectNodeTexture : public UCustomizableObjectNodeTextureBase`  
_L78-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeTextureBase`
- L84 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L85 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L88 _public prototype_ `virtual TObjectPtr<UTexture> GetTexture() override;` — UCustomizableObjectNodeTextureBase interface
- L91 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L92 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L95 _public member_ `TObjectPtr<UTexture> Texture = nullptr;` — `UPROPERTY(EditAnywhere, Category = Texture)`
- L98 _public member_ `TObjectPtr<UTexture> PassThroughTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L101 _public member_ `FEdGraphPinReference TexturePin;` — `UPROPERTY()`
- L104 _public member_ `FEdGraphPinReference PassthroughTexturePin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureBinarise.h` (Private)


#### class `UCustomizableObjectNodeTextureBinarise`  
`class UCustomizableObjectNodeTextureBinarise : public UCustomizableObjectNode`  
_L17-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TittleType) const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L29 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L30 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L32 _public prototype_ `UEdGraphPin* GetBaseImagePin() const;`
- L34 _public function_ `UEdGraphPin* GetThresholdPin() const`
- L41 _private member_ `FEdGraphPinReference BaseImagePinReference;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureColorMap.h` (Private)


#### class `UCustomizableObjectNodeTextureColorMap`  
`class UCustomizableObjectNodeTextureColorMap : public UCustomizableObjectNode`  
_L19-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L25 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L31 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L33 _public function_ `UEdGraphPin* GetMapPin() const`
- L38 _public function_ `UEdGraphPin* GetBasePin() const`
- L43 _public function_ `UEdGraphPin* GetMaskPin() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureFromChannels.h` (Private)


#### class `UCustomizableObjectNodeTextureFromChannels`  
`class UCustomizableObjectNodeTextureFromChannels : public UCustomizableObjectNode`  
_L19-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L25 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L31 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L33 _public function_ `UEdGraphPin* RPin() const`
- L38 _public function_ `UEdGraphPin* GPin() const`
- L43 _public function_ `UEdGraphPin* BPin() const`
- L48 _public function_ `UEdGraphPin* APin() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureFromColor.h` (Private)


#### class `UCustomizableObjectNodeTextureFromColor`  
`class UCustomizableObjectNodeTextureFromColor : public UCustomizableObjectNode`  
_L17-36_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L32 _public member_ `FEdGraphPinReference ColorPin;` — `UPROPERTY()`
- L35 _public member_ `FEdGraphPinReference TexturePin;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureFromFloats.h` (Private)


#### class `UCustomizableObjectNodeTextureFromFloats`  
`class UCustomizableObjectNodeTextureFromFloats : public UCustomizableObjectNode`  
_L19-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L25 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L32 _public function_ `UEdGraphPin* RPin() const`
- L37 _public function_ `UEdGraphPin* GPin() const`
- L42 _public function_ `UEdGraphPin* BPin() const`
- L47 _public function_ `UEdGraphPin* APin() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureInterpolate.h` (Private)


#### class `UCustomizableObjectNodeTextureInterpolate`  
`class UCustomizableObjectNodeTextureInterpolate : public UCustomizableObjectNode`  
_L19-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L24 _public prototype_ `UCustomizableObjectNodeTextureInterpolate();`
- L27 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L30 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `FText GetTooltipText() const override;`
- L35 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L37 _public function_ `UEdGraphPin* FactorPin() const`
- L42 _public function_ `UEdGraphPin* Targets(int32 Index) const`
- L47 _public function_ `int32 GetNumTargets() const`
- L63 _public member_ `int32 NumTargets;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, meta = (ClampMin = 2))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureInvert.h` (Private)


#### class `UCustomizableObjectNodeTextureInvert`  
`class UCustomizableObjectNodeTextureInvert : public UCustomizableObjectNode`  
_L17-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TittleType) const override;` — EdGraphNode interface
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L32 _public prototype_ `UEdGraphPin* GetBaseImagePin() const;` — Own interface
- L36 _private member_ `FEdGraphPinReference BaseImagePinReference;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureLayer.h` (Private)


#### enum `ECustomizableObjectTextureLayerEffect`  
`enum ECustomizableObjectTextureLayerEffect : int`  
_L19-31_
- reflection: `UENUM()`
- L21 _public enumerator_ `COTLE_MODULATE = 0 UMETA(DisplayName = "MODULATE")`
- L22 _public enumerator_ `COTLE_MULTIPLY UMETA(DisplayName = "MULTIPLY")`
- L23 _public enumerator_ `COTLE_SOFTLIGHT UMETA(DisplayName = "SOFTLIGHT")`
- L24 _public enumerator_ `COTLE_HARDLIGHT UMETA(DisplayName = "HARDLIGHT")`
- L25 _public enumerator_ `COTLE_DODGE UMETA(DisplayName = "DODGE")`
- L26 _public enumerator_ `COTLE_BURN UMETA(DisplayName = "BURN")`
- L27 _public enumerator_ `COTLE_SCREEN UMETA(DisplayName = "SCREEN")`
- L28 _public enumerator_ `COTLE_OVERLAY UMETA(DisplayName = "OVERLAY")`
- L29 _public enumerator_ `COTLE_ALPHA_OVERLAY UMETA(DisplayName = "LIGHTEN")`
- L30 _public enumerator_ `COTLE_NORMAL_COMBINE UMETA(DisplayName = "BLEND NORMALS")`

#### struct `FCustomizableObjectTextureLayer`  
`struct FCustomizableObjectTextureLayer`  
_L35-52_
- reflection: `USTRUCT()`
- L39 _public function_ `FCustomizableObjectTextureLayer()`
- L45 _public member_ `TEnumAsByte<ECustomizableObjectTextureLayerEffect> Effect;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L48 _public member_ `FEdGraphPinReference LayerPin;` — `UPROPERTY()`
- L51 _public member_ `FEdGraphPinReference MaskPin;` — `UPROPERTY()`

#### class `UCustomizableObjectNodeTextureLayer`  
`class UCustomizableObjectNodeTextureLayer : public UCustomizableObjectNode`  
_L56-125_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNode`
- L61 _public prototype_ `UCustomizableObjectNodeTextureLayer();`
- L64 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L65 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L68 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L69 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L70 _public prototype_ `virtual FText GetTooltipText() const override;`
- L73 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L74 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L75 _public prototype_ `virtual TArray<FName> GetPinAllowedTypes(const UEdGraphPin& Pin) const override;`
- L77 _public function_ `UEdGraphPin* GetLayerPin(int32 Index) const`
- L87 _public function_ `UEdGraphPin* GetMaskPin(int32 Index) const`
- L98 _public function_ `int32 GetNumLayers() const`
- L116 _public member_ `FEdGraphPinReference BasePin;` — `UPROPERTY()`
- L120 _public member_ `TArray<FCustomizableObjectTextureLayer> Layers;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)`
- L124 _private member_ `FEdGraphPinReference OutputPinReference;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureParameter.h` (Private)


#### class `UCustomizableObjectNodeTextureParameter`  
`class UCustomizableObjectNodeTextureParameter : public UCustomizableObjectNodeParameter`  
_L19-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter`
- L26 _public member_ `TObjectPtr<UTexture2D> DefaultValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)` — Default value of the parameter.
- L30 _public member_ `TObjectPtr<UTexture2D> ReferenceValue;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject)` — Reference Texture where this parameter copies some properties from.
- L34 _public member_ `int32 TextureSizeX = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Set the width of the Texture when there is no texture reference.
- L38 _public member_ `int32 TextureSizeY = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Set the height of the Texture when there is no texture reference.
- L41 _public member_ `FEdGraphPinReference PassthroughPin;` — `UPROPERTY()`
- L44 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L45 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L48 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureProject.h` (Private)


#### enum `ETextureProjectSamplingMethod`  
`enum class ETextureProjectSamplingMethod`  
_L22-26_
- reflection: `UENUM()`
- L24 _public enumerator_ `Point`
- L25 _public enumerator_ `BiLinear`

#### enum `ETextureProjectMinFilterMethod`  
`enum class ETextureProjectMinFilterMethod`  
_L29-33_
- reflection: `UENUM()`
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `TotalAreaHeuristic`

#### class `UCustomizableObjectNodeTextureProject`  
`class UCustomizableObjectNodeTextureProject : public UCustomizableObjectNode`  
_L36-133_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L41 _public prototype_ `UCustomizableObjectNodeTextureProject();`
- L45 _public member_ `uint8 Layout = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Layout to use for the generated images.
- L51 _public member_ `bool bEnableTextureSeamCorrection = true;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — When this is enable, additional operations will happen to correct projections that go over a texture UV seam to prevent interpolation artifacts. This is not necessary if the projection is guaranteed to not go over a seam.
- L54 _public member_ `bool bEnableAngleFadeOutForRGB = true;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L57 _public member_ `bool bEnableAngleFadeOutForAlpha = true;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L60 _public member_ `ETextureProjectSamplingMethod SamplingMethod = ETextureProjectSamplingMethod::Point;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L63 _public member_ `ETextureProjectMinFilterMethod MinFilterMethod = ETextureProjectMinFilterMethod::None;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L67 _public member_ `uint32 TextureSizeX = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Set the width of the Texture. If greater than zero, it overrides the Reference Texture width.
- L71 _public member_ `uint32 TextureSizeY = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Set the height of the Texture. If greater than zero, it overrides the Reference Texture height.
- L74 _public member_ `uint32 Textures = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, meta=( ClampMin = 1))`
- L79 _public member_ `TObjectPtr<UTexture2D> ReferenceTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Reference Texture used to decide the texture properties of the mutable-generated textures connected to this material (e.g. LODBias, Size X,...). If null, mutable default texture properties will be applied.
- L82 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L83 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L86 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L87 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L88 _public prototype_ `FText GetTooltipText() const override;`
- L91 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L92 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L94 _public function_ `UEdGraphPin* MeshPin() const`
- L99 _public function_ `UEdGraphPin* MeshMaskPin() const`
- L104 _public function_ `UEdGraphPin* AngleFadeStartPin() const`
- L109 _public function_ `UEdGraphPin* AngleFadeEndPin() const`
- L114 _public function_ `UEdGraphPin* ProjectorPin() const`
- L119 _public prototype_ `UEdGraphPin* TexturePins(int32 Index) const;`
- L121 _public prototype_ `UEdGraphPin* OutputPins(int32 Index) const;`
- L123 _public prototype_ `int32 GetNumTextures() const;`
- L125 _public prototype_ `int32 GetNumOutputs() const;`
- L129 _private member_ `TArray<FEdGraphPinReference> TexturePinsReferences;` — `UPROPERTY()`
- L132 _private member_ `TArray<FEdGraphPinReference> OutputPinsReferences;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureSample.h` (Private)


#### class `UCustomizableObjectNodeTextureSample`  
`class UCustomizableObjectNodeTextureSample : public UCustomizableObjectNode`  
_L21-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L32 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L33 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L35 _public function_ `const UEdGraphPin* TexturePin() const`
- L41 _public function_ `const UEdGraphPin* XPin() const`
- L46 _public function_ `const UEdGraphPin* YPin() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureSaturate.h` (Private)


#### class `UCustomizableObjectNodeTextureSaturate`  
`class UCustomizableObjectNodeTextureSaturate : public UCustomizableObjectNode`  
_L17-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TittleType) const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L29 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L31 _public prototype_ `UEdGraphPin* GetBaseImagePin() const;`
- L32 _public prototype_ `UEdGraphPin* GetFactorPin() const;`
- L36 _private member_ `FEdGraphPinReference BaseImagePinReference;` — `UPROPERTY()`
- L39 _private member_ `FEdGraphPinReference FactorPinReference;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureSwitch.h` (Private)


#### class `UCustomizableObjectNodeTextureSwitch`  
`class UCustomizableObjectNodeTextureSwitch : public UCONodeSwitch`  
_L14-21_
- reflection: `UCLASS(NotPlaceable, HideDropdown)`
- inherits: `UCONodeSwitch`
- desc: DEPRECATED
- L20 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureToChannels.h` (Private)


#### class `UCustomizableObjectNodeTextureToChannels`  
`class UCustomizableObjectNodeTextureToChannels : public UCustomizableObjectNode`  
_L20-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L26 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L27 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L30 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `FText GetTooltipText() const override;`
- L35 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L36 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L38 _public prototype_ `UEdGraphPin* InputPin() const;`
- L40 _public function_ `UEdGraphPin* RPin() const`
- L45 _public function_ `UEdGraphPin* GPin() const`
- L50 _public function_ `UEdGraphPin* BPin() const`
- L55 _public function_ `UEdGraphPin* APin() const`
- L62 _private member_ `FEdGraphPinReference InputPinReference;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureTransform.h` (Private)


#### enum `ETextureTransformAddressMode`  
`enum class ETextureTransformAddressMode`  
_L17-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `Wrap`
- L20 _public enumerator_ `ClampToEdge`
- L21 _public enumerator_ `ClampToBlack`

#### class `UCustomizableObjectNodeTextureTransform`  
`class UCustomizableObjectNodeTextureTransform : public UCustomizableObjectNode`  
_L25-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L31 _public member_ `ETextureTransformAddressMode AddressMode = ETextureTransformAddressMode::Wrap;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`
- L36 _public member_ `bool bKeepAspectRatio = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — If true, the operation will keep the source aspect ratio regardless of the output image size
- L40 _public member_ `uint32 TextureSizeX = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Set the width of the Texture. If greater than zero, it overrides the Reference Texture width.
- L44 _public member_ `uint32 TextureSizeY = 0;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Set the height of the Texture. If greater than zero, it overrides the Reference Texture height.
- L49 _public member_ `TObjectPtr<UTexture2D> ReferenceTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Reference Texture used to decide the texture properties of the mutable-generated textures connected to this material (e.g. LODBias, Size X,...). If null, mutable default texture properties will be applied.
- L53 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TittleType) const override;`
- L54 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L55 _public prototype_ `virtual FText GetTooltipText() const override;`
- L59 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L60 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L62 _public prototype_ `UEdGraphPin* GetBaseImagePin() const;`
- L64 _public function_ `UEdGraphPin* GetOffsetXPin() const`
- L69 _public function_ `UEdGraphPin* GetOffsetYPin() const`
- L74 _public function_ `UEdGraphPin* GetScaleXPin() const`
- L79 _public function_ `UEdGraphPin* GetScaleYPin() const`
- L84 _public function_ `UEdGraphPin* GetRotationPin() const`
- L91 _private member_ `FEdGraphPinReference BaseImagePinReference;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTextureVariation.h` (Private)


#### class `UCustomizableObjectNodeTextureVariation`  
`class UCustomizableObjectNodeTextureVariation : public UCustomizableObjectNodeVariation`  
_L21-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeVariation`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `virtual FText GetTooltipText() const override;`
- L35 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L38 _public prototype_ `virtual FName GetCategory() const override;` — UCustomizableObjectNodeVariation interface
- L43 _private member_ `TArray<FCustomizableObjectTextureVariation> Variations_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTransformConstant.h` (Private)


#### class `SGraphNodeTransformConstant`  
`class SGraphNodeTransformConstant : public SCustomizableObjectNode`  
_L17-54_
- inherits: `SCustomizableObjectNode`
- desc: Class create color inputs in the NodeColorConstant
- L21 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeTransformConstant)`
- L22 _public prototype_ `SLATE_END_ARGS();`
- L24 _public prototype_ `SGraphNodeTransformConstant() = default;`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);` — Builds the SGraphNodeFloatConstant when needed
- L30 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;` — Overriden functions to build the SGraphNode widgets
- L31 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L32 _public function_ `virtual bool ShouldAllowCulling() const override`
- L35 _public prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Callbacks for the widget
- L36 _public prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;`
- L37 _public prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;`
- L42 _private prototype_ `void OnLocationChanged(double Value, ETextCommit::Type, EAxis::Type Axis);` — Callback for when the location part of the transform changes.
- L45 _private prototype_ `void OnRotationChanged(double Value, ETextCommit::Type, EAxis::Type Axis);` — Callback for when the rotation part of the transform changes.
- L48 _private prototype_ `void OnScaleChanged(double Value, ETextCommit::Type, EAxis::Type Axis);` — Callback for when the scale part of the transform changes.
- L52 _private member_ `UCustomizableObjectNodeTransformConstant* NodeTransformConstant = nullptr;` — Pointer to the transform constant node that owns this SGraphNode

#### class `UCustomizableObjectNodeTransformConstant`  
`class UCustomizableObjectNodeTransformConstant : public UCustomizableObjectNode`  
_L58-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L65 _public member_ `FTransform Value = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, meta = (DontUpdateWhileEditing))`
- L68 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L69 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L70 _public prototype_ `virtual FText GetTooltipText() const override;`
- L74 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L75 _public function_ `virtual bool IsAffectedByLOD() const override`
- L76 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L79 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;` — Creates the SGraph Node widget for the Color Editor
- L82 _public member_ `bool bCollapsed = true;` — Determines if the Node is collapsed or not

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTransformParameter.h` (Private)


#### class `UCustomizableObjectNodeTransformParameter`  
`class UCustomizableObjectNodeTransformParameter : public UCustomizableObjectNodeParameter`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodeParameter`
- L21 _public member_ `FTransform DefaultValue = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category=CustomizableObject, meta = (DontUpdateWhileEditing))`
- L24 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;`
- L27 _public prototype_ `virtual FName GetCategory() const override;` — CustomizableObjectNodeParameter interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeTunnel.h` (Private)


#### class `UCustomizableObjectNodeTunnelPinData`  
`class UCustomizableObjectNodeTunnelPinData : public UCustomizableObjectNodePinData`  
_L16-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNodePinData`
- desc: Base class for all Tunnel Pins.
- L24 _public member_ `FGuid VariableId;` — `UPROPERTY()` — Id of the variable associated to a tunnel node pin

#### class `UCustomizableObjectNodeTunnelRemapPins`  
`class UCustomizableObjectNodeTunnelRemapPins : public UCustomizableObjectNodeRemapPinsByName`  
_L30-40_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPinsByName`
- L36 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin) const override;` — Specific method to decide when two pins are equal
- L39 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;` — Method to use in the RemapPins step of the node reconstruction process

#### class `UCustomizableObjectNodeTunnel`  
`class UCustomizableObjectNodeTunnel : public UCustomizableObjectNode`  
_L45-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCustomizableObjectNode`
- L51 _public member_ `bool bIsInputNode = false;` — `UPROPERTY()` — Indicates if this node is an input or output node.
- L55 _public member_ `TObjectPtr<UCustomizableObjectMacro> ParentMacro;` — `UPROPERTY()` — Pointer to the macro where this node belongs.
- L62 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L63 _public prototype_ `virtual FText GetTooltipText() const override;`
- L64 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L65 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L66 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L70 _public prototype_ `void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;` — UCustomizableObjectNode interface
- L71 _public prototype_ `virtual UCustomizableObjectNodeTunnelRemapPins* CreateRemapPinsDefault() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/CustomizableObjectNodeVariation.h` (Private)


#### struct `FCustomizableObjectVariation`  
`struct FCustomizableObjectVariation`  
_L23-29_
- reflection: `USTRUCT()`
- L28 _public member_ `FString Tag;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)`

#### class `UCustomizableObjectNodeVariation`  
`class UCustomizableObjectNodeVariation : public UCustomizableObjectNode`  
_L33-88_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UCustomizableObjectNode`
- L39 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface.
- L42 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — EdGraphNode interface
- L43 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L44 _public prototype_ `virtual FText GetTooltipText() const override;`
- L47 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion) override;` — UCustomizableObjectNode interface
- L48 _public prototype_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins) override;`
- L49 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const override;`
- L50 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const override;`
- L51 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value) override;`
- L55 _public prototype_ `virtual FName GetCategory() const PURE_VIRTUAL(UCustomizableObjectNodeVariation::GetCategory, return {}; );` — Return the pin category of this node.
- L58 _public prototype_ `virtual bool IsInputPinArray() const;` — Return true if all inputs pins should be array.
- L61 _public prototype_ `int32 GetNumVariations() const;` — Return the number of variations (input pins excluding the Default Pin).
- L64 _public prototype_ `const FCustomizableObjectVariation& GetVariation(int32 Index) const;` — Get the variation at the given index.
- L67 _public prototype_ `FString GetVariationTag(int32 Index, TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr) const;` — Get the variation tag at the given index
- L70 _public prototype_ `UEdGraphPin* DefaultPin() const;` — Get the Default Input Pin.
- L73 _public prototype_ `UEdGraphPin* VariationPin(int32 Index) const;` — Get the Variation Input Pin.
- L76 _public prototype_ `UEdGraphPin* VariationTagPin(int32 Index) const;` — Get the Variation Tag Input Pin
- L79 _public member_ `TArray<FCustomizableObjectVariation> VariationsData;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — The variable name can not be Variations due issues with the UObject Serialization system
- L84 _protected member_ `TArray<FEdGraphPinReference> VariationsPins;` — `UPROPERTY()`
- L87 _protected member_ `TArray<FEdGraphPinReference> VariationTagPins;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L11 _namespace_ `namespace ENodeTitleType`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/ExternalTypeCustomization.h` (Private)


#### class `FExternalTypeTypeIdentifier`  
`class FExternalTypeTypeIdentifier : public IPropertyTypeIdentifier`  
_L11-15_
- inherits: `IPropertyTypeIdentifier`
- L14 _public prototype_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override;`

#### class `FExternalTypeCustomization`  
`class FExternalTypeCustomization : public FInstancedStructDetails`  
_L18-23_
- inherits: `FInstancedStructDetails`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/SCONodeSkeletalMeshSection.h` (Private)


#### class `SCONodeSkeletalMeshSection`  
`class SCONodeSkeletalMeshSection : public SCustomizableObjectNode`  
_L14-24_
- inherits: `SCustomizableObjectNode`
- desc: Custom widget for the Material node.
- L17 _public function_ `SLATE_BEGIN_ARGS(SCONodeSkeletalMeshSection)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs, UCONodeSkeletalMeshSection* InGraphNode);`
- L23 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/SCONodeSkeletalMeshSectionPinImage.h` (Private)


#### class `SCONodeSkeletalMeshSectionPinImage`  
`class SCONodeSkeletalMeshSectionPinImage : public SCustomizableObjectNodePin`  
_L14-26_
- inherits: `SCustomizableObjectNodePin`
- desc: Implements the "MUTABLE" and "PASSTHROUGH" text next to the pin name.
- L18 _public function_ `SLATE_BEGIN_ARGS(SCONodeSkeletalMeshSectionPinImage)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L25 _private prototype_ `FText GetPinTooltipText() const;` — Return pin tool tip.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/SCustomizableObjectNode.h` (Private)


#### class `SCustomizableObjectNode`  
`class SCustomizableObjectNode : public SGraphNode`  
_L12-29_
- inherits: `SGraphNode`
- L15 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectNode)`
- L16 _public prototype_ `SLATE_END_ARGS();`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);`
- L21 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface
- L22 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L23 _public prototype_ `virtual FSlateColor GetNodeTitleColor() const override;`
- L26 _protected prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L27 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L28 _protected prototype_ `virtual FReply OnAddPin() override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/SCustomizableObjectNodePin.h` (Private)


#### class `SCustomizableObjectNodePin`  
`class SCustomizableObjectNodePin : public SGraphPin`  
_L12-36_
- inherits: `SGraphPin`
- L16 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectNodePin)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — SGraphPin interface
- L23 _public prototype_ `virtual const FSlateBrush* GetPinIcon() const override;`
- L24 _public prototype_ `virtual FSlateColor GetPinColor() const override;`
- L27 _private prototype_ `FText GetNodeStringValue() const;`
- L29 _private prototype_ `void OnTextCommited(const FText& InValue, ETextCommit::Type InCommitInfo);`
- L31 _private prototype_ `EVisibility GetHideIfLinkedWidgetVisibility() const;`
- L34 _private member_ `const FSlateBrush* PassThroughImageConnected = nullptr;`
- L35 _private member_ `const FSlateBrush* PassThroughImageDisconnected = nullptr;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/SCustomizableObjectNodeReroute.h` (Private)


#### class `SCustomizableObjectNodeReroute`  
`class SCustomizableObjectNodeReroute : public SGraphNodeKnot`  
_L13-23_
- inherits: `SGraphNodeKnot`
- desc: To avoid multiple inheritance SCustomizableObjectNodeReroute does not inherit from SCustomizableObjectNode but reimplements its functionalities.
- L16 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeKnot)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode* InKnot);`
- L22 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Nodes/SCustomizableObjectNodeReroutePin.h` (Private)


#### class `SCustomizableObjectNodeReroutePin`  
`class SCustomizableObjectNodeReroutePin : public SGraphPinKnot`  
_L9-23_
- inherits: `SGraphPinKnot`
- desc: To avoid multiple inheritance SCustomizableObjectNodeReroutePin does not inherit from SCustomizableObjectNodePin but reimplements its functionalities.
- L12 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectNodeReroutePin)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L19 _protected prototype_ `virtual const FSlateBrush* GetPinIcon() const override;` — SGraphPin interface
- L21 _protected member_ `const FSlateBrush* PassThroughImageConnected = nullptr;`
- L22 _protected member_ `const FSlateBrush* PassThroughImageDisconnected = nullptr;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/PassthroughObjectFactory.h` (Private)


#### class `UE::Mutable::Private::FPassthroughObjectFactory`  
`class FPassthroughObjectFactory`  
_L9-22_
- L12 _public prototype_ `PASSTHROUGH_ID Add(UObject& Object, bool bDuplicate);`
- L14 _public prototype_ `TMap<PASSTHROUGH_ID, TSoftObjectPtr<UObject>>& GetAll();`
- L16 _public prototype_ `TArray<PASSTHROUGH_ID>& GetDuplicate();`
- L19 _private member_ `TMap<PASSTHROUGH_ID, TSoftObjectPtr<UObject>> PassthroughObjects;`
- L21 _private member_ `TArray<PASSTHROUGH_ID> DuplicateObjects;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/PinViewer/SPinViewer.h` (Private)


#### class `SPinViewer`  
`class SPinViewer : public SCompoundWidget`  
_L25-97_
- inherits: `SCompoundWidget`
- desc: Pin Viewer widget. Shows a list of pins a node contains. In addition, a pin can provide a custom details widget which will be shown as an expandable menu. This widget will work as long as pins are only created and destroyed during the node reconstruction.
- L30 _public function_ `SLATE_BEGIN_ARGS(SPinViewer)`
- L31 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectNode*, Node) SLATE_END_ARGS() static const FName COLUMN_NAME;`
- L35 _public member_ `static const FName COLUMN_TYPE;`
- L36 _public member_ `static const FName COLUMN_SUBTYPE;`
- L37 _public member_ `static const FName COLUMN_VISIBILITY;`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `void UpdateWidget();` — Regenerate the list contents and update the widget.
- L45 _public prototype_ `void OnGraphChanged(const FEdGraphEditAction& EdGraphEditAction);` — Callback executed each time a graph node does change.
- L48 _public prototype_ `TSharedRef<ITableRow> GenerateNodePinRow(TSharedPtr<FEdGraphPinReference> PinReference, const TSharedRef<STableViewBase>& OwnerTable);` — Callback to Generate a Node Material Pin row
- L51 _public prototype_ `void OnFilterTextChanged(const FText& SearchText);` — SearchBox callback.
- L54 _public prototype_ `FReply OnShowAllPressed() const;` — Buttons callbacks.
- L55 _public prototype_ `FReply OnHideAllPressed() const;`
- L59 _public prototype_ `void SortListView(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);` — Sets the sorting method to be applied
- L60 _public prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L63 _public prototype_ `static FText GetPinName(const UEdGraphPin& Pin);` — Get the pin name which is actually displayed.
- L66 _public prototype_ `void OnPinEditableNameChange(const UEdGraphPin& EdGraphPin, FText Text);` — Callback method invoked each time a pin of the node we keep a reference of does get the Editable Name changed.
- L70 _private prototype_ `void GeneratePinInfoList();` — Regenerate the list contents.
- L72 _private prototype_ `void PinsRemapped(const TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap);`
- L75 _private member_ `TStrongObjectPtr<UCustomizableObjectNode> Node = nullptr;` — Pointer to the Node
- L77 _private member_ `TStrongObjectPtr<UEdGraph> Graph = nullptr;`
- L80 _private member_ `TArray<TSharedPtr<FEdGraphPinReference>> PinReferences;` — ListView elements.
- L84 _private member_ `TMap<FGuid, EVisibility> AdditionalWidgetVisibility;` — Data structure used to save SPinViewerMultiColumnTableRow additional widget visibility state between reconstructs. Key is a pin id.
- L87 _private member_ `FName CurrentSortColumn = COLUMN_TYPE;` — Current column.
- L88 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::None;`
- L90 _private member_ `FString CurrentFilter;`
- L93 _private member_ `TSharedPtr<SListView<TSharedPtr<FEdGraphPinReference>>> ListView;` — Widget List of the Node Material Pins
- L96 _private member_ `TSharedPtr<class SScrollBox> Scrollbox;` — Scrollbox widget needed to fix some scrolling problems

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/PinViewer/SPinViewerDetailRowIndent.h` (Private)


#### class `SPinViewerDetailRowIndent`  
`class SPinViewerDetailRowIndent : public SCompoundWidget`  
_L19-31_
- inherits: `SCompoundWidget`
- desc: Pin Viewer custom details row left indent. Draws a shadow to differentiate the different indent levels. Copy of  SDetailRowIndent.h.
- L22 _public function_ `SLATE_BEGIN_ARGS(SPinViewerDetailRowIndent)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SWidget> Row);`
- L28 _private prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L30 _private member_ `TWeakPtr<SWidget> Row;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/PinViewer/SPinViewerListRow.h` (Private)


#### class `SPinViewerListRow`  
`class SPinViewerListRow : public SMutableExpandableTableRow<TSharedPtr<FEdGraphPinReference>>`  
_L16-56_
- inherits: `SMutableExpandableTableRow<TSharedPtr<FEdGraphPinReference>>`
- desc: Custom row for a SListView that allows to add custom widgets as a row element.
- L19 _public function_ `SLATE_BEGIN_ARGS(SPinViewerListRow)`
- L20 _public prototype_ `SLATE_ARGUMENT(SPinViewer*, PinViewer) SLATE_ARGUMENT(FEdGraphPinReference, PinReference) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SPinViewerMultiColumnTableRow interface
- L28 _public prototype_ `virtual TSharedPtr<SWidget> GenerateAdditionalWidgetForRow() override;`
- L29 _public prototype_ `virtual EVisibility GetAdditionalWidgetDefaultVisibility() const override;`
- L30 _public prototype_ `virtual void SetAdditionalWidgetVisibility(EVisibility Visibility) override;`
- L34 _public prototype_ `void OnPinVisibilityCheckStateChanged(ECheckBoxState NewRadioState);` — CheckBox callback.
- L37 _public prototype_ `ECheckBoxState IsVisibilityChecked() const;` — Returns the state of the check box in function of the visibility of the pin
- L39 _public prototype_ `void OnEditableNameCommited(const FText& NewPinEditableName, ETextCommit::Type Arg) const;`
- L40 _public prototype_ `FText GetEditableName() const;`
- L45 _private prototype_ `FName GetInitiallySelectedPinType() const;`
- L46 _private prototype_ `FName GetInitiallySelectedPinSubType() const;`
- L48 _private member_ `SPinViewer* PinViewer = nullptr;`
- L51 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> PinOwner;` — Weak pointer to the Customizable Object node that contains this property
- L54 _private member_ `FEdGraphPinReference PinReference;` — Pin representing this row.
- L55 _private member_ `FGuid PinId;` — Temporal performance fix. Avoids using the slow FEdPinReference hash function.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/PinViewer/SPinViewerPinDetails.h` (Private)


#### class `SPinViewerPinDetails`  
`class SPinViewerPinDetails : public SBorder`  
_L14-37_
- inherits: `SBorder`
- desc: Pin Viewer custom details multiple row style. Base class which allows a custom pin viewer details to have multiple properties.
- L17 _public function_ `SLATE_BEGIN_ARGS(SPinViewerPinDetails)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `TSharedPtr<SWidget> AddRow(const FText& Text, TSharedRef<SWidget> Widget, const FText* Tooltip = nullptr);` — Adds a new property row. @param Text Property title. @param Widget Property widget. @param Tooltip Optional property tooltip. @return Row widget.
- L33 _private member_ `TSharedPtr<SVerticalBox> VerticalBox;` — Vertical box which contains all rows.
- L36 _private prototype_ `FSlateColor GetBackgroundColor() const;` — Returns custom details background color.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/RemapPins/CustomizableObjectNodeRemapPinsByName.h` (Private)


#### class `UCustomizableObjectNodeRemapPinsByName`  
`class UCustomizableObjectNodeRemapPinsByName : public UCustomizableObjectNodeRemapPins`  
_L21-29_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPins`
- desc: Remap pins by name. Remap pins by the field Pin->PinName. Output pins and input pins get remapped independently. Use inheritance is a node requires a set of special rules when remapping by name.
- L26 _public prototype_ `virtual bool Equal(const UCustomizableObjectNode& Node, const UEdGraphPin& OldPin, const UEdGraphPin& NewPin) const;`
- L28 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/RemapPins/CustomizableObjectNodeRemapPinsByNameDefaultPin.h` (Private)


#### class `UCustomizableObjectNodeRemapPinsByNameDefaultPin`  
`class UCustomizableObjectNodeRemapPinsByNameDefaultPin : public UCustomizableObjectNodeRemapPinsByName`  
_L16-25_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPinsByName`
- desc: If a default pin is given, remap it to the first pin. Otherwise, remap pins by name as usual.
- L22 _public member_ `UEdGraphPin* DefaultPin = nullptr;` — Default pin to remap with.
- L24 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/RemapPins/CustomizableObjectNodeRemapPinsByPosition.h` (Private)


#### class `UCustomizableObjectNodeRemapPinsByPosition`  
`class UCustomizableObjectNodeRemapPinsByPosition : public UCustomizableObjectNodeRemapPins`  
_L21-27_
- reflection: `UCLASS()`
- inherits: `UCustomizableObjectNodeRemapPins`
- desc: Remap pins by position. Remap pins by their relative order. Output pins and input pins get remapped independently. Use inheritance is a node requires a set of special rules when remapping by position.
- L26 _public prototype_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan) override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectEditorAdvancedPreviewSettings.h` (Private)


#### class `SLevelSelectWindow`  
`class SLevelSelectWindow : public SWindow`  
_L21-57_
- inherits: `SWindow`
- desc: Simple window with a content browser filtered for ULevel assets to select a ULevel with a DirectionalLight, PostProcess and SkyLight elements to form a profile
- L24 _public function_ `SLATE_BEGIN_ARGS(SLevelSelectWindow)`
- L25 _public function_ `SLATE_ATTRIBUTE(TWeakPtr<ICustomizableObjectInstanceEditor>, CustomizableObjectEditor) SLATE_ATTRIBUTE(UAssetViewerSettings*, DefaultSettings) SLATE_END_ARGS() SLevelSelectWindow() : UserResponse(EAppReturnType::Cancel)`
- L34 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L39 _public prototype_ `void SetProfileAddedSuccessfully(bool Value);`
- L42 _private prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L45 _private prototype_ `void OnLevelAssetSelected(const FAssetData& AssetData);` — Callback for when the user selects an asset in the asset picker widget
- L47 _private member_ `EAppReturnType::Type UserResponse;`
- L48 _private member_ `FAssetData LevelAssetData;` — Current ULevel selected asset
- L50 _private member_ `TArray<FString> ArrayDirectionalLightName;`
- L51 _private member_ `TArray<FString> ArrayPostProcessName;`
- L52 _private member_ `TArray<FString> ArraySkyLightName;`
- L53 _private member_ `FString LevelAssetPath;`
- L54 _private member_ `bool ProfileAddedSuccessfully;`
- L55 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> CustomizableObjectEditor;`
- L56 _private member_ `UAssetViewerSettings* DefaultSettings;`

#### class `SUObjectSelecWindow`  
`class SUObjectSelecWindow : public SWindow`  
_L62-92_
- inherits: `SWindow`
- desc: In this window, all the directional light, post process volume and sky light elements of the selected / edited profile are shown in drop down lists
- L65 _public function_ `SLATE_BEGIN_ARGS(SUObjectSelecWindow)`
- L66 _public prototype_ `SLATE_ATTRIBUTE(FString, LevelAssetPath) SLATE_ATTRIBUTE(SLevelSelectWindow*, LevelSelectWindow) SLATE_ATTRIBUTE(TWeakPtr<ICustomizableObjectInstanceEditor>, CustomizableObjectEditor) SLATE_ATTRIBUTE(UAssetViewerSettings*, DefaultSettings) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L75 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L78 _private prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L80 _private member_ `EAppReturnType::Type UserResponse;`
- L81 _private member_ `TSharedPtr<SEditableTextBox> ProfileName;`
- L82 _private member_ `TSharedPtr<STextComboBox> DirectionalLight;`
- L83 _private member_ `TSharedPtr<STextComboBox> PostProcess;`
- L84 _private member_ `TSharedPtr<STextComboBox> SkyLight;`
- L85 _private member_ `FString LevelAssetPath;`
- L86 _private member_ `SLevelSelectWindow* LevelSelectWindow;` — Pointer to parent window, needed to close it if new profile added successfully
- L87 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> CustomizableObjectEditor;`
- L88 _private member_ `TArray<TSharedPtr<FString>> ArrayDirectionalLightName;`
- L89 _private member_ `TArray<TSharedPtr<FString>> ArrayPostProcessName;`
- L90 _private member_ `TArray<TSharedPtr<FString>> ArraySkyLightName;`
- L91 _private member_ `UAssetViewerSettings* DefaultSettings;`

#### class `SCustomizableObjectEditorAdvancedPreviewSettings`  
`class SCustomizableObjectEditorAdvancedPreviewSettings : public SAdvancedPreviewDetailsTab`  
_L97-119_
- inherits: `SAdvancedPreviewDetailsTab`
- desc: This widget extends the SAdvancedPreviewDetailsTab tab adding the profile management options at the bottom of the tab
- L101 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorAdvancedPreviewSettings)`
- L102 _public prototype_ `SLATE_ARGUMENT(UCustomSettings*, CustomSettings)` — From SAdvancedPreviewDetailsTab
- L108 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);`
- L110 _public prototype_ `FReply ShowAddProfileWindow();`
- L113 _public prototype_ `void AddProfileToEditor(const FPreviewSceneProfile& PreviewSceneProfile);` — Applies the preview scene profile to the LevelProfileProfile profile used to applyt this kind of profiles
- L116 _public prototype_ `void LoadProfileEnvironment();` — Load the environment map of each prodile in DefaultSettings::Profiles since default constructor loads a predetermined environment
- L118 _public member_ `TWeakPtr<ICustomizableObjectInstanceEditor> CustomizableObjectEditor;` — Pointer to editor instance

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectEditorTagExplorer.h` (Private)


#### class `STagExplorerTableRow`  
`class STagExplorerTableRow : public SMultiColumnTableRow<TWeakObjectPtr<UCustomizableObjectNode>>`  
_L22-39_
- inherits: `SMultiColumnTableRow<TWeakObjectPtr<UCustomizableObjectNode>>`
- L26 _public function_ `SLATE_BEGIN_ARGS(STagExplorerTableRow)`
- L27 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UCustomizableObjectNode>, CustomizableObjectNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L32 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L37 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> Node;` — The info about the widget that we are visualizing

#### class `SCustomizableObjectEditorTagExplorer`  
`class SCustomizableObjectEditorTagExplorer : public SCompoundWidget`  
_L42-110_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorTagExplorer)`
- L47 _public prototype_ `SLATE_ARGUMENT(FCustomizableObjectEditor*, CustomizableObjectEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _public member_ `static const FName COLUMN_OBJECT;`
- L53 _public member_ `static const FName COLUMN_TYPE;`
- L58 _private prototype_ `TSharedRef<SWidget> OnGetTagsMenuContent();` — Callback to fill the combobox options
- L61 _private prototype_ `void FillTagInformation(const UCustomizableObject& Object, TArray<FString>& Tags);` — Fills a list with all the tags found in the nodes of a graph
- L64 _private prototype_ `TSharedRef<SWidget> MakeComboButtonItemWidget(TSharedPtr<FString> StringItem);` — Generates the combobox with all the tags
- L67 _private prototype_ `FText GetCurrentItemLabel() const;` — Generates the text of the tags combobox
- L70 _private prototype_ `FReply CopyTagToClipboard();` — Copies the tag name to the clipboard
- L73 _private prototype_ `void OnComboBoxSelectionChanged(const FString NewValue);` — OnSelectionChanged callback of the tags combobox
- L76 _private prototype_ `TSharedRef<ITableRow> OnGenerateTableRow(TWeakObjectPtr<UCustomizableObjectNode> Node, const TSharedRef<STableViewBase>& OwnerTable);` — Tags table callbacks
- L77 _private prototype_ `void OnTagTableSelectionChanged(TWeakObjectPtr<UCustomizableObjectNode> Entry, ESelectInfo::Type SelectInfo) const;`
- L80 _private prototype_ `void SortListView(const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode);` — Sorts the content of the list view alphabetically
- L83 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnName) const;` — Returns the sorting mode of the specified column
- L88 _private member_ `FCustomizableObjectEditor* CustomizableObjectEditorPtr;` — Pointer back to the editor tool that owns us
- L91 _private member_ `TSharedPtr<SComboButton> TagComboBox;` — Combobox for the Customizable Object Tags
- L94 _private member_ `FString SelectedTag;` — Combobox Selection
- L97 _private member_ `TSharedPtr<SListView<TWeakObjectPtr<UCustomizableObjectNode>>> ListViewWidget;` — List views for the nodes that contain the same tag
- L100 _private member_ `TArray<TWeakObjectPtr<UCustomizableObjectNode>> Nodes;` — Arrays for each type of node that contains a tag
- L103 _private member_ `TMultiMap<FString, UCustomizableObjectNode*> NodeTags;` — Multimap to relate nodes with tags
- L106 _private member_ `FName CurrentSortColumn;` — Stores name of the column to sort
- L109 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::None;` — Stores the sorting mode of the selected column

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectEditorTextureAnalyzer.h` (Private)


#### class `UCustomizableObjectEditorTextureStats`  
`class UCustomizableObjectEditorTextureStats : public UObject`  
_L28-67_
- reflection: `UCLASS(Transient, MinimalAPI, meta = (DisplayName = "Texture Stats"))`
- inherits: `UObject`
- desc: Statistics for the Texture Analyzer
- L35 _public member_ `FString TextureName;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Texture", ColumnWidth = "40", NoResetToDefault))` — Texture - double click to open
- L39 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(meta = (NoResetToDefault))` — Used to open the texture in the editor
- L43 _public member_ `int32 ResolutionX;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Resolution X", ColumnWidth = "40", DisplayRight = "true", NoResetToDefault))` — Resolution of the texture
- L46 _public member_ `int32 ResolutionY;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Resolution Y", ColumnWidth = "40", DisplayRight = "true", NoResetToDefault))`
- L50 _public member_ `float Size;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Size Kb", ColumnWidth = "90", NoResetToDefault, Units = "Kb"))` — The memory used in KB
- L54 _public member_ `TEnumAsByte<EPixelFormat> Format;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "96", NoResetToDefault))` — The texture format, e.g. PF_DXT1
- L58 _public member_ `int32 LODBias;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "LOD Bias", ColumnWidth = "70", NoResetToDefault))` — LOD Bias for this texture. (Texture LODBias + Texture group)
- L62 _public member_ `FString IsStreamed;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Streamed", ColumnWidth = "70", NoResetToDefault))` — Says if the texture is being streamed
- L66 _public member_ `TEnumAsByte<TextureGroup> LODGroup;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Texture Group", ColumnWidth = "70", NoResetToDefault))` — The Level of detail group of the texture

#### class `SCustomizableObjecEditorTextureAnalyzer`  
`class SCustomizableObjecEditorTextureAnalyzer : public SCompoundWidget, public FGCObject`  
_L70-125_
- inherits: `SCompoundWidget,FGCObject`
- L74 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjecEditorTextureAnalyzer)`
- L75 _public prototype_ `SLATE_ARGUMENT(FCustomizableObjectEditor*,CustomizableObjectEditor) SLATE_ARGUMENT(FCustomizableObjectInstanceEditor*, CustomizableObjectInstanceEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L82 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L83 _public function_ `virtual FString GetReferencerName() const override`
- L88 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L91 _public prototype_ `FReply RefreshTextureAnalyzerTable();` — Force the Update of the Texture Analyzer Table information
- L93 _public prototype_ `FReply RefreshTextureAnalyzerTable(UCustomizableObjectInstance* PreviewInstance);` — Force the Update of the Texture Analyzer Table information and provides the instance to be analyzed
- L98 _private prototype_ `TSharedRef<SWidget> BuildTextureAnalyzerTable();` — Build the Texture Analyzer table with the information of the textures
- L101 _private prototype_ `void FillTextureAnalyzerTable(UCustomizableObjectInstance* PreviewInstance = nullptr);` — Generate the information of the Texture Analyzer Table
- L104 _private prototype_ `void OnTextureTableSelectionChanged(TSharedPtr<class IPropertyTableCell> Cell);` — Callback for a Texture Analyzer Table Cell selection
- L109 _public member_ `TSharedPtr<IPropertyTable> TextureAnalyzerTable;` — Texture Analyzer table widget which shows the information of the transient textures used in the customizable object instance
- L114 _private member_ `FCustomizableObjectEditor* CustomizableObjectEditor = nullptr;` — Pointer back to the editor tool that owns us
- L117 _private member_ `FCustomizableObjectInstanceEditor* CustomizableObjectInstanceEditor = nullptr;` — Pointer back to the editor tool that owns us
- L120 _private member_ `TSharedPtr< STextBlock > TotalSizeTextures;` — The sum of all the textures shown in the Texture Analyzer
- L123 _private member_ `TArray<TObjectPtr<UObject>> TabTextures;` — Array of Objects used in the Texture Analyzer Table

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectEditorTransformViewportToolbar.h` (Private)


#### class `SCustomizableObjectEditorTransformViewportToolbar`  
`class SCustomizableObjectEditorTransformViewportToolbar : public SViewportToolBar`  
_L7-27_
- inherits: `SViewportToolBar`
- L11 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorTransformViewportToolbar)`
- L12 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class SEditorViewport>, Viewport) SLATE_ARGUMENT(TSharedPtr<class SCustomizableObjectEditorViewportTabBody>, ViewportTapBody) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L20 _protected member_ `TWeakPtr<class SEditorViewport> Viewport;` — The editor viewport that we are in
- L23 _protected member_ `TWeakPtr<class SCustomizableObjectEditorViewportTabBody> ViewportTapBody;` — Viewport we are in - derived class
- L26 _protected member_ `TSharedPtr<class FUICommandList> UICommandList;` — Command list for the widgets to be added to the toolbar

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectEditorViewport.h` (Private)


#### class `SCustomizableObjectEditorViewport`  
`class SCustomizableObjectEditorViewport : public SEditorViewport`  
_L41-88_
- inherits: `SEditorViewport`
- L44 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorViewport)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FCustomizableObjectPreviewScene>& PreviewScene, const TWeakPtr<SCustomizableObjectEditorViewportTabBody>& TabBody, const TWeakPtr<ICustomizableObjectInstanceEditor>& Editor);`
- L53 _public prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L54 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L57 _public prototype_ `TSharedPtr<FSceneViewport>& GetSceneViewport();`
- L61 _private prototype_ `void OnUndoRedo();` — Handle undo/redo by refreshing the viewport
- L63 _private prototype_ `EVisibility GetShowCompileErrorOverlay() const;`
- L65 _private prototype_ `FText GetCompileErrorOverlayText() const;`
- L67 _private prototype_ `FText GetWarningText() const;`
- L69 _private prototype_ `EVisibility GetWarningTextVisibility() const;`
- L71 _private prototype_ `FText GetMeshInfoText() const;`
- L73 _private prototype_ `EVisibility GetMeshInfoTextVisibility() const;`
- L76 _private member_ `TSharedPtr<FCustomizableObjectEditorViewportClient> LevelViewportClient;` — Viewport client
- L79 _private member_ `TWeakPtr<SCustomizableObjectEditorViewportTabBody> TabBodyPtr;` — Pointer to the compound widget that owns this viewport widget
- L82 _private member_ `TWeakPtr<FCustomizableObjectPreviewScene> PreviewScenePtr;` — The preview scene that we are viewing
- L84 _private member_ `TWeakPtr<SCustomizableObjectViewportToolBar> ToolbarPtr;`
- L87 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> WeakEditor;` — Weak pointer of the open editor

#### class `SCustomizableObjectEditorViewportTabBody`  
`class SCustomizableObjectEditorViewportTabBody : public SCompoundWidget`  
_L94-296_
- inherits: `SCompoundWidget`
- desc: CustomizableObject Editor Preview viewport widget with toolbars, etc.
- L97 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorViewportTabBody)`
- L98 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<class ICustomizableObjectInstanceEditor>, CustomizableObjectEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L103 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L106 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L112 _public function_ `const TSharedPtr<FUICommandList>& GetCommandList() const` — @return The list of commands on the viewport that are bound to delegates
- L115 _public prototype_ `void ShowGizmoClipMorph(UCustomizableObjectNodeModifierClipMorph& ClipPlainNode) const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L118 _public prototype_ `void HideGizmoClipMorph() const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L121 _public prototype_ `void ShowGizmoClipMesh(UCustomizableObjectNode& Node, FTransform* Transform, UObject& ClipMesh, int32 LODIndex, int32 SectionIndex, int32 MaterialSlotIndex) const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L123 _public prototype_ `void SetTransformWidgetVisibility(const EVisibility NewVisibilityState) const;`
- L126 _public prototype_ `void HideGizmoClipMesh() const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L129 _public prototype_ `void ShowGizmoProjector( const FWidgetLocationDelegate& WidgetLocationDelegate, const FOnWidgetLocationChangedDelegate& OnWidgetLocationChangedDelegate, const FWidgetDirectionDelegate& WidgetDirectionDelegate, const FOnWidgetDirectionChangedDelegate& OnWidgetDirectionChangedDelegate, const FWidgetUpDelegate& WidgetUpDelegate, const FOnWidgetUpChangedDelegate& OnWidgetUpChangedDelegate, const FWidgetScaleDelegate& WidgetScaleDelegate, const FOnWidgetScaleChangedDelegate& OnWidgetScaleChangedDelegate, const FWidgetAngleDelegate& WidgetAngleDelegate, const FProjectorTypeDelegate& ProjectorTypeDelegate, const FWidgetColorDelegate& WidgetColorDelegate, const FWidgetTrackingStartedDelegate& WidgetTrackingStartedDelegate) const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L140 _public prototype_ `void HideGizmoProjector() const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L143 _public prototype_ `void ShowGizmoLight(ULightComponent& SelectedLight) const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L146 _public prototype_ `void HideGizmoLight() const;` — Do not call directly. Use ICustomizableObjectEditor functions instead.
- L149 _public prototype_ `void BindCommands();` — Binds commands associated with the viewport client.
- L150 _public prototype_ `TSharedRef<SWidget> BuildToolBar();`
- L152 _public prototype_ `TSharedRef<SWidget> GenerateUVMaterialOptionsMenuContent();`
- L155 _public prototype_ `TSharedRef<SWidget> ShowStateTestData();` — Callback to show / hide the state and runtime parameter test in the viewport
- L157 _public prototype_ `void CreatePreviewActor(const TWeakObjectPtr<UCustomizableObjectInstance>& InInstance);`
- L160 _public prototype_ `int32 GetLODModelCount() const;` — Function to get the number of LOD models associated with the preview skeletal mesh
- L163 _public prototype_ `bool IsLODModelSelected(int32 LODSelectionType) const;` — LOD model selection checking function
- L164 _public function_ `int32 GetLODSelection() const`
- L167 _public prototype_ `void ProjectorCheckboxStateChanged(UE::Widget::EWidgetMode Mode);` — Callback for when the projector checkbox changes
- L169 _public prototype_ `bool IsProjectorCheckboxState(UE::Widget::EWidgetMode Mode) const;`
- L172 _public prototype_ `void RotationGridSnapClicked();` — Called when the rotation grid snap is toggled off and on
- L175 _public prototype_ `bool RotationGridSnapIsChecked() const;` — Returns whether or not rotation grid snap is enabled
- L178 _public prototype_ `static void SetRotationGridSize(int32 InIndex, ERotationGridMode InGridMode);` — Sets the rotation grid size
- L181 _public prototype_ `static bool IsRotationGridSizeChecked(int32 GridSizeIndex, ERotationGridMode GridMode);` — Checks to see if the specified rotation grid angle is the current rotation grid angle
- L184 _public prototype_ `void OnSetLODModel(int32 LODSelectionType);` — Function to set LOD model selection
- L187 _public prototype_ `TSharedPtr<FCustomizableObjectPreviewScene> GetPreviewScene() const;` — Getter of PreviewScenePtr
- L189 _public prototype_ `TSharedPtr<FCustomizableObjectEditorViewportClient> GetViewportClient() const;`
- L192 _public member_ `TWeakPtr<ICustomizableObjectInstanceEditor> WeakEditor;` — Pointer back to the editor tool that owns us.
- L195 _public prototype_ `void SetViewportToolbarTransformWidget(TWeakPtr<class SWidget> TransformWidget);` — void SetEditorTransformViewportToolbar(TWeakPtr<class SCustomizableObjectEditorTransformViewportToolbar> EditorTransformViewportToolbarParam);
- L198 _public prototype_ `void SetCustomizableObject(UCustomizableObject* CustomizableObjectParameter);` — Setter of CustomizableObject
- L201 _public prototype_ `void OnTakeHighResScreenshot();` — Called to bring up the screenshot UI
- L204 _public prototype_ `void SetCameraMode(bool Value);` — Sets camera mode of the LevelViewportClient::bActivateOrbitalCamera
- L207 _public prototype_ `bool IsCameraModeActive(int Value);` — Returns whether or not the a camera mode is active (Orbital or Free)
- L211 _public prototype_ `void SetDrawDefaultUVMaterial();` — Sets the first material of the instance as the default section to draw in the UVs Overlay (when there is no material selected in the combobox) Param bIsCompilation: true if this function is called during a CO compilation, false when is called from an instance update
- L214 _public prototype_ `void SetShowBones();` — Sets the bones visibility
- L217 _public prototype_ `bool IsShowingBones();` — Returns true if the skeletal mesh bones are visible in the viewport
- L221 _private prototype_ `bool IsVisible() const;` — Determines the visibility of the viewport.
- L223 _private prototype_ `void OnSetPlaybackSpeed(int32 PlaybackSpeedMode);`
- L225 _private prototype_ `bool IsPlaybackSpeedSelected(int32 PlaybackSpeedMode);`
- L228 _private member_ `TSharedPtr<FCustomizableObjectPreviewScene> PreviewScenePtr;` — The scene for this viewport.
- L231 _private member_ `TSharedPtr<FCustomizableObjectEditorViewportClient> LevelViewportClient;` — Level viewport client
- L234 _private member_ `TSharedPtr<SCustomizableObjectEditorViewport> ViewportWidget;` — Viewport widget
- L235 _private member_ `TSharedPtr<SCustomizableObjectEditorToolBar> ViewportToolbar;`
- L238 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L241 _private member_ `EViewModeIndex CurrentViewMode = VMI_Lit;` — The currently selected view mode.
- L252 _private member_ `TArray<TSharedPtr<FString>> UVSectionOptionString;` — Selection for the section to filter when showing UVs
- L253 _private member_ `TArray<FSection> UVSectionOption;`
- L256 _private member_ `TSharedPtr<STextComboBox> UVSectionOptionCombo;` — Combo box for UV section selection
- L259 _private member_ `TArray<TSharedPtr<FString>> UVChannelOptionString;` — Selection for the channel to filter when showing UVs
- L262 _private member_ `TSharedPtr<STextComboBox> UVChannelOptionCombo;` — Combo box for UV channel selection
- L264 _private member_ `TSharedPtr<SMutableScrubPanel> ScrubPanel;`
- L267 _private prototype_ `void GenerateUVSectionOptions();` — Generates the Combobox options for each UV Channel
- L270 _private prototype_ `void GenerateUVChannelOptions();` — Generates the Combobox options for each UV Channel
- L273 _private member_ `TSharedPtr<FString> SelectedUVSection;` — Selected option of the UV Material ComboBox
- L276 _private member_ `TSharedPtr<FString> SelectedUVChannel;` — Selected option of the UV Channel ComboBox
- L279 _private member_ `TArray< TSharedPtr< FString > > MaterialNames;` — Options for the above combo.
- L282 _private prototype_ `void OnSectionChanged(TSharedPtr<FString> Selected, ESelectInfo::Type SelectInfo);` — Slate callbacks to manage the material combo
- L283 _private prototype_ `void OnUVChannelChanged(TSharedPtr<FString> Selected, ESelectInfo::Type SelectInfo);`
- L286 _private member_ `int32 LODSelection = 0;` — Current LOD selection
- L289 _private member_ `TWeakPtr<SWidget> ViewportToolbarTransformWidget;` — To be able to show and hide the constant projector RTS controls
- L292 _private member_ `bool AssetRegistryLoaded = false;` — Flag to know when the asset registry initial loading has completed, value set by the Customizable Object / Customizable Object Instance editor
- L295 _private member_ `TWeakPtr<SWindow> CustomizableObjectHighresScreenshot;` — Weak pointer to the high resolution screenshot dialog if it's open. Will become invalid if UI is closed whilst the viewport is open

#### struct `SCustomizableObjectEditorViewportTabBody::FSection`  
`struct FSection`  
_L244-249_
- desc: Section identifier.
- L246 _public member_ `FName ComponentName = NAME_None;`
- L247 _public member_ `int32 LODIndex = -1;`
- L248 _public member_ `int32 SectionIndex = -1;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace EAnimationMode`
- L15 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectEditorViewportToolBar.h` (Private)


#### class `SCustomizableObjectEditorViewportToolBar`  
`class SCustomizableObjectEditorViewportToolBar : public SViewportToolBar`  
_L22-127_
- inherits: `SViewportToolBar`
- desc: A level viewport toolbar widget that is placed in a viewport
- L25 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectEditorViewportToolBar)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class SCustomizableObjectEditorViewportTabBody> InViewport, TSharedPtr<class SEditorViewport> InRealViewport);`
- L36 _private prototype_ `TSharedRef<SWidget> GenerateViewMenu() const;` — Generates the toolbar view menu content @return The widget containing the view menu content
- L40 _private prototype_ `TSharedRef<SWidget> GenerateRTSButtons();` — Add the projector Rotation, traslation and scale buttons to viewport toolbar
- L47 _private prototype_ `TSharedRef<SWidget> GenerateLODMenu() const;` — Generates the toolbar LOD menu content @return The widget containing the LOD menu content based on LOD model count
- L54 _private prototype_ `FText GetLODMenuLabel() const;` — Returns the label for the "LOD" tool bar menu, which changes depending on the current LOD selection @return	Label to use for this LOD label
- L61 _private prototype_ `TSharedRef<SWidget> GenerateCharacterMenu() const;` — Generates the toolbar Character menu content @return The widget containing the view menu content
- L68 _private prototype_ `TSharedRef<SWidget> GenerateViewportTypeMenu() const;` — Generates the toolbar viewport type menu content @return The widget containing the viewport type menu content
- L75 _private prototype_ `TSharedRef<SWidget> GeneratePlaybackMenu() const;` — Generates the toolbar playback menu content @return The widget containing the playback menu content
- L82 _private prototype_ `TSharedRef<SWidget> GenerateViewportOptionsMenu() const;` — Generates the toolbar Options Mode menu content @return The widget containing the Options menu content
- L89 _private prototype_ `FText GetPlaybackMenuLabel() const;` — Returns the label for the Playback tool bar menu, which changes depending on the current playback speed @return	Label to use for this Menu
- L96 _private prototype_ `FText GetCameraMenuLabel() const;` — Returns the label for the Viewport type tool bar menu, which changes depending on the current selected type @return	Label to use for this Menu
- L97 _private prototype_ `const FSlateBrush* GetCameraMenuLabelIcon() const;`
- L100 _private prototype_ `float OnGetFOVValue() const;` — Called by the FOV slider in the perspective viewport to get the FOV value
- L102 _private prototype_ `void OnFOVValueChanged(float NewValue) const;` — Called when the FOV slider is adjusted in the perspective viewport
- L104 _private prototype_ `ECheckBoxState IsRotationGridSnapChecked() const;`
- L105 _private prototype_ `void HandleToggleRotationGridSnap(ECheckBoxState InState);`
- L106 _private prototype_ `FText GetRotationGridLabel() const;`
- L107 _private prototype_ `TSharedRef<SWidget> FillRotationGridSnapMenu();`
- L110 _private prototype_ `FReply OnMenuClicked();` — Callback for drop-down menu with FOV and high resolution screenshot options currently
- L113 _private prototype_ `TSharedRef<SWidget> GenerateOptionsMenu() const;` — Generates drop-down menu with FOV and high resolution screenshot options currently
- L116 _private prototype_ `TSharedRef<SWidget> GenerateFOVMenu() const;` — Generates widgets for viewport camera FOV control
- L119 _private member_ `TWeakPtr<SCustomizableObjectEditorViewportTabBody> Viewport;` — The viewport that we are in
- L121 _private member_ `TWeakPtr<ICustomizableObjectInstanceEditor> WeakEditor;`
- L124 _private member_ `TSharedPtr<SButton> CompileErrorLayout;` — Layout to show information about instance skeletal mesh update / CO asset data
- L126 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ETextCommit`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectHighresScreenshot.h` (Private)


#### class `SCustomizableObjectHighresScreenshot`  
`class SCustomizableObjectHighresScreenshot : public SCompoundWidget`  
_L14-192_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectHighresScreenshot)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L22 _public prototype_ `SCustomizableObjectHighresScreenshot();`
- L24 _public prototype_ `virtual ~SCustomizableObjectHighresScreenshot();`
- L26 _public function_ `void SetWindow( TSharedPtr<SWindow> InWindow )`
- L31 _public function_ `void SetCaptureRegion(const FIntRect& InCaptureRegion)`
- L41 _public function_ `FHighResScreenshotConfig& GetConfig()`
- L46 _public prototype_ `static TWeakPtr<class SWindow> OpenDialog( TSharedPtr<class FSceneViewport>& InSceneViewport, TSharedPtr<class FCustomizableObjectEditorViewportClient>& InLevelViewportClient, USkeletalMeshComponent* SkeletalMeshComponentParameter, TSharedPtr<class FCustomizableObjectPreviewScene> PreviewScenePtr);`
- L52 _public prototype_ `void SetSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponentParameter);`
- L54 _public member_ `TSharedPtr<class FCustomizableObjectPreviewScene> PreviewScenePtr;`
- L58 _private prototype_ `FReply OnCaptureClicked();`
- L60 _private prototype_ `bool IsSetCameraSafeAreaCaptureRegionEnabled() const;`
- L62 _private function_ `void OnResolutionMultiplierChanged( float NewValue, ETextCommit::Type CommitInfo )`
- L69 _private function_ `void OnResolutionMultiplierSliderChanged( float NewValue )`
- L75 _private prototype_ `void OnMaskEnabledChanged(ECheckBoxState NewValue);`
- L77 _private function_ `void OnHDREnabledChanged(ECheckBoxState NewValue)`
- L87 _private prototype_ `void OnShowFloorChanged(ECheckBoxState NewValue);`
- L89 _private function_ `void OnForce128BitRenderingChanged(ECheckBoxState NewValue)`
- L99 _private function_ `void OnBufferVisualizationDumpEnabledChanged(ECheckBoxState NewValue)`
- L107 _private function_ `EVisibility GetSpecifyCaptureRegionVisibility() const`
- L112 _private function_ `EVisibility GetCaptureRegionControlsVisibility() const`
- L117 _private function_ `void SetCaptureRegionControlsVisibility(bool bVisible)`
- L122 _private function_ `TOptional<float> GetResolutionMultiplier() const`
- L127 _private function_ `float GetResolutionMultiplierSlider() const`
- L132 _private function_ `ECheckBoxState GetMaskEnabled() const`
- L137 _private function_ `ECheckBoxState GetHDRCheckboxUIState() const`
- L142 _private prototype_ `ECheckBoxState GetShowFloorState() const;`
- L144 _private function_ `ECheckBoxState GetForce128BitRenderingCheckboxUIState() const`
- L149 _private function_ `ECheckBoxState GetBufferVisualizationDumpEnabled() const`
- L154 _private function_ `void SetHDRUIEnableState(bool bEnable)`
- L160 _private function_ `void SetForce128BitRenderingState(bool bEnable)`
- L166 _private prototype_ `void RestoreViewportValues();`
- L168 _private prototype_ `static void WindowClosedHandler(const TSharedRef<SWindow>& InWindow);`
- L170 _private member_ `TSharedPtr<SWindow> Window;`
- L171 _private member_ `TSharedPtr<SButton> CaptureRegionButton;`
- L172 _private member_ `TSharedPtr<SHorizontalBox> RegionCaptureActiveControlRoot;`
- L173 _private member_ `TSharedPtr<SCheckBox> HDRCheckBox;`
- L174 _private member_ `TSharedPtr<STextBlock> HDRLabel;`
- L175 _private member_ `TSharedPtr<SCheckBox> Force128BitRenderingCheckBox;`
- L176 _private member_ `TSharedPtr<STextBlock> Force128BitRenderingLabel;`
- L177 _private member_ `TSharedPtr<SCheckBox> ShowFloor;`
- L179 _private member_ `FHighResScreenshotConfig& Config;`
- L180 _private member_ `bool bCaptureRegionControlsVisible;`
- L182 _private member_ `static TWeakPtr<SWindow> CurrentWindow;`
- L183 _private member_ `static TWeakPtr<SCustomizableObjectHighresScreenshot> CurrentDialog;`
- L184 _private member_ `static bool bMaskVisualizationWasEnabled;`
- L186 _private member_ `TWeakPtr<class FCustomizableObjectEditorViewportClient> LevelViewportClient;`
- L187 _private member_ `int32 ExposureLogOffsetCached;`
- L188 _private member_ `bool ExposureLogFixedCached;`
- L189 _private member_ `bool FloorVisibilityCached;`
- L190 _private member_ `bool GridVisibilityCached;`
- L191 _private member_ `USkeletalMeshComponent* SkeletalMeshComponent;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectLayoutEditor.h` (Private)


#### struct `FLayoutEditorMeshSection`  
`struct FLayoutEditorMeshSection`  
_L31-35_
- L33 _public member_ `TSharedPtr<FString> MeshName;`
- L34 _public member_ `TArray<TWeakObjectPtr<UCustomizableObjectLayout>> Layouts;`

#### struct `FCustomizableObjectLayoutEditorDetailsBuilder`  
`struct FCustomizableObjectLayoutEditorDetailsBuilder`  
_L37-50_
- L39 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& Details);`
- L41 _public member_ `bool bShowLayoutSelector = false;`
- L42 _public member_ `bool bShowPackagingStrategy = false;`
- L43 _public member_ `bool bShowAutomaticGenerationSettings = false;`
- L44 _public member_ `bool bShowGridSize = false;`
- L45 _public member_ `bool bShowMaxGridSize = false;`
- L46 _public member_ `bool bShowReductionMethods = false;`
- L47 _public member_ `bool bShowWarningSettings = false;`
- L49 _public member_ `TSharedPtr<SCustomizableObjectLayoutEditor> LayoutEditor;`

#### class `SCustomizableObjectLayoutEditor`  
`class SCustomizableObjectLayoutEditor : public SCompoundWidget, public FGCObject`  
_L55-255_
- inherits: `SCompoundWidget,FGCObject`
- desc: CustomizableObject Editor Preview viewport widget
- L62 _public prototype_ `DECLARE_DELEGATE(FOnPreUpdateLayout);`
- L64 _public function_ `SLATE_BEGIN_ARGS( SCustomizableObjectLayoutEditor )`
- L65 _public function_ `SLATE_ATTRIBUTE(TArray<FLayoutEditorMeshSection>, MeshSections) SLATE_ARGUMENT_DEFAULT(UObject*, Node)`
- L67 _public prototype_ `SLATE_EVENT(FOnPreUpdateLayout, OnPreUpdateLayoutDelegate) SLATE_END_ARGS() SCustomizableObjectLayoutEditor();`
- L72 _public prototype_ `void Construct(const FArguments& InArgs);`
- L75 _public prototype_ `void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FSerializableObject interface
- L76 _public function_ `virtual FString GetReferencerName() const override`
- L84 _public prototype_ `void BindCommands();` — Binds commands associated with the viewport client.
- L86 _public prototype_ `void SetLayout(UCustomizableObjectLayout* Layout);`
- L91 _public prototype_ `void SetUVsOverride(UCustomizableObjectLayout* UVOverrideLayout);` — UVOverrideLayout parameter can be speicifed to show different UVs in the widget instead of the ones in Layout.
- L93 _public prototype_ `void UpdateLayout(UCustomizableObjectLayout* Layout);`
- L97 _private member_ `FOnPreUpdateLayout OnPreUpdateLayoutDelegate;`
- L99 _private member_ `TWeakObjectPtr<UObject> Node;`
- L101 _private member_ `TArray<FLayoutEditorMeshSection> MeshSections;`
- L102 _private member_ `TArray<TSharedPtr<FString>> MeshSectionNames;`
- L104 _private member_ `TArray<TSharedPtr<FString>> UVChannels;`
- L107 _private member_ `TObjectPtr<UCustomizableObjectLayout> CurrentLayout;` — Layout whose blocksa are being edited.
- L110 _private member_ `TObjectPtr<UCustomizableObjectLayout> UVOverrideLayout;` — If valid, layout use to show the UVs instead of CurrentLayout.
- L113 _private member_ `TArray<TSharedPtr<FString>> LayoutGridSizes;` — List of available layout grid sizes.
- L114 _private member_ `TArray<TSharedPtr<FString>> MaxLayoutGridSizes;`
- L116 _private member_ `TSharedPtr<FString> NothingSelectedString;`
- L123 _private member_ `TArray<TSharedPtr<FString>> AutoBlocksStrategies;`
- L124 _private member_ `TArray<FAutoBlocksStrategyOption> AutoBlocksStrategiesOptions;`
- L131 _private member_ `TArray<TSharedPtr<FString>> AutoBlocksMergeStrategies;`
- L132 _private member_ `TArray<FAutoBlocksMergeStrategyOption> AutoBlocksMergeStrategiesOptions;`
- L135 _private member_ `TArray<TSharedPtr<FString>> BlockReductionMethods;` — List of available block reduction methods.
- L136 _private member_ `TArray<FText> BlockReductionMethodsTooltips;`
- L144 _private member_ `TArray<TSharedPtr<FString>> LayoutPackingStrategies;`
- L145 _private member_ `TArray<FPackingStrategyOption> LayoutPackingStrategiesOptions;`
- L148 _private member_ `TSharedRef<FUICommandList> UICommandList;` — The list of UI Commands executable
- L152 _private member_ `TSharedPtr<STextComboBox> MeshSectionComboBox;` — Layout ------------- ComboBox widget to select a column from the NodeTable
- L153 _private member_ `TSharedPtr<STextComboBox> UVChannelComboBox;`
- L157 _private member_ `TSharedPtr<SSearchableComboBox> StrategyComboBox;` — ComboBox widget to select a Strategy from the Selected Layout. SSearchableComboBox allows us to set a custom tooltip per option.
- L159 _private member_ `TSharedPtr<SSearchableComboBox> AutoBlocksComboBox;`
- L160 _private member_ `TSharedPtr<SSearchableComboBox> AutoBlocksMergeComboBox;`
- L163 _private member_ `TSharedPtr<STextComboBox> GridSizeXComboBox;` — ComboBox widget to select a Grid Size from the Selected Layout
- L164 _private member_ `TSharedPtr<STextComboBox> GridSizeYComboBox;`
- L167 _private member_ `TSharedPtr<STextComboBox> MaxGridSizeComboBox;` — ComboBox widget to select a Max Grid Size from the Selected Layout
- L170 _private member_ `TSharedPtr<SSearchableComboBox> ReductionMethodComboBox;` — ComboBox widget to select a Reduction Method from the Selected Layout
- L173 _private member_ `TSharedPtr<SSpinBox<int32>> LODSelectorWidget;` — Widget to select at which LOD layout vertex warnings will start to be ignored
- L174 _private member_ `TSharedPtr<STextBlock> LODSelectorTextWidget;`
- L176 _private member_ `TSharedPtr<SCustomizableObjectLayoutGrid> LayoutGridWidget;`
- L181 _private prototype_ `ELayoutGridMode GetGridMode() const;`
- L182 _private prototype_ `FIntPoint GetGridSize() const;`
- L183 _private prototype_ `void OnBlockChanged(FGuid BlockId, FIntRect Block );`
- L184 _private prototype_ `TArray<FCustomizableObjectLayoutBlock> GetBlocks() const;`
- L187 _private prototype_ `TSharedRef<SWidget> BuildLayoutToolBar();` — Callbacks from the layout block editor.
- L189 _private prototype_ `void OnAddBlock();`
- L190 _private prototype_ `void OnAddBlockAt(const FIntPoint Min, const FIntPoint Max);`
- L191 _private prototype_ `void OnRemoveBlock();`
- L194 _private prototype_ `void OnMeshSectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L195 _private prototype_ `void OnUVChannelChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L196 _private prototype_ `void OnOpenGridSizeComboBox();`
- L197 _private prototype_ `void OnGridSizeChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, bool bIsGridSizeX);`
- L198 _private prototype_ `void OnMaxGridSizeChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L200 _private prototype_ `void OnAutoBlocksChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L201 _private prototype_ `void OnAutoBlocksMergeChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L202 _private prototype_ `void OnReductionMethodChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L203 _private prototype_ `void OnPackagingStrategyChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L205 _private prototype_ `void OnIgnoreErrorsCheckStateChanged(ECheckBoxState NewSelection);`
- L206 _private prototype_ `void OnIgnoreErrorsLODBoxValueChanged(int32 Value);`
- L208 _private prototype_ `void OnResetSelection();`
- L211 _private prototype_ `void OnConsolidateBlocks();` — Turn the automatic layout blocks into user-created blocks.
- L214 _private prototype_ `void OnSetBlockPriority(int32 InValue);` — Sets the block priority from the input text.
- L217 _private prototype_ `void OnSetBlockReductionSymmetry(bool bInValue);` — Sets the block reduction symmetry option.
- L220 _private prototype_ `void OnSetBlockReductionByTwo(bool bInValue);` — Sets the block reduction ReduceByTwo option.
- L223 _private prototype_ `void OnSetBlockMask(UTexture2D* InValue);` — Callback for block mask change.
- L225 _private prototype_ `UCustomizableObjectLayout* FindSelectedLayout(TSharedPtr<FString> MeshSection, TSharedPtr<FString> UVChannel);`
- L227 _private prototype_ `void FillLayoutComboBoxOptions();`
- L229 _private prototype_ `TSharedPtr<IToolTip> GenerateInfoToolTip() const;`
- L231 _private prototype_ `TSharedRef<SWidget> GenerateAutoBlocksComboBox(TSharedPtr<FString> InItem) const;`
- L232 _private prototype_ `FText GetAutoBlocksName() const;`
- L233 _private prototype_ `FText GetAutoBlocksTooltip() const;`
- L235 _private prototype_ `TSharedRef<SWidget> GenerateAutoBlocksMergeComboBox(TSharedPtr<FString> InItem) const;`
- L236 _private prototype_ `FText GetAutoBlocksMergeName() const;`
- L237 _private prototype_ `FText GetAutoBlocksMergeTooltip() const;`
- L239 _private prototype_ `TSharedRef<SWidget> GenerateReductionMethodComboBox(TSharedPtr<FString> InItem) const;`
- L240 _private prototype_ `FText GetLayoutReductionMethodName() const;`
- L241 _private prototype_ `FText GetLayoutReductionMethodTooltip() const;`
- L243 _private prototype_ `TSharedRef<SWidget> GenerateLayoutPackagingStrategyComboBox(TSharedPtr<FString> InItem) const;`
- L244 _private prototype_ `FText GetLayoutPackagingStrategyName() const;`
- L245 _private prototype_ `FText GetLayoutPackagingStrategyToolTip() const;`
- L247 _private prototype_ `EVisibility GridSizeVisibility() const;`
- L248 _private prototype_ `EVisibility LayoutOptionsVisibility() const;`
- L249 _private prototype_ `EVisibility AutoBlocksStrategyVisibility() const;`
- L250 _private prototype_ `EVisibility AutoBlocksMergeStrategyVisibility() const;`
- L251 _private prototype_ `EVisibility FixedStrategyOptionsVisibility() const;`
- L252 _private prototype_ `EVisibility WarningOptionsVisibility() const;`
- L254 _private member_ `const static int32 MaxPossibleGridSize = 128;`

#### struct `SCustomizableObjectLayoutEditor::FAutoBlocksStrategyOption`  
`struct FAutoBlocksStrategyOption`  
_L118-122_
- L120 _public member_ `ECustomizableObjectLayoutAutomaticBlocksStrategy Value;`
- L121 _public member_ `FText Tooltip;`

#### struct `SCustomizableObjectLayoutEditor::FAutoBlocksMergeStrategyOption`  
`struct FAutoBlocksMergeStrategyOption`  
_L126-130_
- L128 _public member_ `ECustomizableObjectLayoutAutomaticBlocksMergeStrategy Value;`
- L129 _public member_ `FText Tooltip;`

#### struct `SCustomizableObjectLayoutEditor::FPackingStrategyOption`  
`struct FPackingStrategyOption`  
_L139-143_
- desc: List of available layout packing strategies.
- L141 _public member_ `ECustomizableObjectTextureLayoutPackingStrategy Value;`
- L142 _public member_ `FText Tooltip;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`
- L62 _delegate_ `DECLARE_DELEGATE(FOnPreUpdateLayout);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectLayoutGrid.h` (Private)


#### struct `FRect2D`  
`struct FRect2D`  
_L22-26_
- L24 _public member_ `FVector2f Min;`
- L25 _public member_ `FVector2f Size;`

#### enum `(anonymous)`  
``  
_L29-33_

#### struct `FBlockWidgetData`  
`struct FBlockWidgetData`  
_L35-39_
- L37 _public member_ `FRect2D Rect;`
- L38 _public member_ `FRect2D HandleRect;`

#### enum `EFixedReductionOptions`  
`enum EFixedReductionOptions`  
_L42-46_
- L44 _public enumerator_ `EFRO_Symmetry`
- L45 _public enumerator_ `EFRO_RedyceByTwo`

#### class `SCustomizableObjectLayoutGrid`  
`class SCustomizableObjectLayoutGrid : public SCompoundWidget`  
_L49-253_
- inherits: `SCompoundWidget`
- L53 _public prototype_ `DECLARE_DELEGATE_TwoParams(FBlockChangedDelegate, FGuid , FIntRect );`
- L54 _public prototype_ `DECLARE_DELEGATE_OneParam(FBlockSelectionChangedDelegate, const TArray<FGuid>& );`
- L55 _public prototype_ `DECLARE_DELEGATE(FDeleteBlockDelegate);`
- L56 _public prototype_ `DECLARE_DELEGATE_TwoParams(FAddBlockAtDelegate, FIntPoint, FIntPoint);`
- L57 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetBlockPriority, int32);`
- L58 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetReduceBlockSymmetrically, bool);`
- L59 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetReduceBlockByTwo, bool);`
- L60 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetBlockMask, UTexture2D*);`
- L62 _public function_ `SLATE_BEGIN_ARGS( SCustomizableObjectLayoutGrid )`
- L64 _public prototype_ `SLATE_ATTRIBUTE(ELayoutGridMode, Mode) SLATE_ATTRIBUTE( FIntPoint, GridSize ) SLATE_ATTRIBUTE(TArray<FCustomizableObjectLayoutBlock>, Blocks) SLATE_ATTRIBUTE( TArray<FVector2f>, UVLayout ) SLATE_ARGUMENT( TArray<FVector2f>, UnassignedUVLayoutVertices ) SLATE_ARGUMENT( FColor, SelectionColor ) SLATE_EVENT( FBlockChangedDelegate, OnBlockChanged ) SLATE_EVENT( FBlockSelectionChangedDelegate, OnSelectionChanged ) SLATE_EVENT(FDeleteBlockDelegate, OnDeleteBlocks) SLATE_EVENT(FAddBlockAtDelegate, OnAddBlockAt) SLATE_EVENT(FSetBlockPriority, OnSetBlockPriority) SLATE_EVENT(FSetReduceBlockSymmetrically, OnSetReduceBlockSymmetrically) SLATE_EVENT(FSetReduceBlockByTwo, OnSetReduceBlockByTwo) SLATE_EVENT(FSetBlockMask, OnSetBlockMask) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L85 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidgetInterface
- L86 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L88 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L89 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L90 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L91 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L93 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L94 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L96 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L97 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L102 _public prototype_ `void SetSelectedBlock( FGuid block );` — Set the currently selected block
- L105 _public prototype_ `const TArray<FGuid>& GetSelectedBlocks() const;`
- L108 _public prototype_ `void DeleteSelectedBlocks();` — Calls the delegate to delete the selected blocks
- L111 _public prototype_ `void ResetView();` — Reset the view zoom and pan to show the unit UV space.
- L114 _public prototype_ `void GenerateNewBlock(FVector2D MousePosition);` — Generates a new block at mouse position
- L117 _public prototype_ `void DuplicateBlocks();` — Duplicates the selected blocks
- L120 _public prototype_ `void SetBlockSizeToMax();` — Sets the size of the selected blocks to the size of the Grid
- L122 _public prototype_ `void CalculateSelectionRect();`
- L124 _public member_ `FColor SelectionColor;`
- L127 _public prototype_ `void SetBlocks( const FIntPoint& GridSize, const TArray<FCustomizableObjectLayoutBlock>& Blocks);` — Set the grid and blocks to show in the widget.
- L146 _public member_ `FPointOfView PointOfView;` — Current point of view.
- L151 _private prototype_ `TOptional<int32> GetBlockPriorityValue() const;` — Gets the priority value of the selected blocks
- L154 _private prototype_ `void OnBlockPriorityChanged(int32 InValue);` — Callback when the priority of a block changes
- L157 _private prototype_ `void OnReduceBlockSymmetricallyChanged(ECheckBoxState InCheckboxState);` — Callback when symmetry block reduction option changes
- L160 _private prototype_ `void OnReduceBlockByTwoChanged(ECheckBoxState InCheckboxState);` — Callback when ReduceByTwo block reduction option changes
- L163 _private prototype_ `ECheckBoxState GetReductionMethodBoolValue(EFixedReductionOptions Option) const;` — Gets block reduction value of the selected blocks
- L165 _private prototype_ `bool MouseOnBlock(FGuid BlockId, FVector2D MousePosition, bool CheckResizeBlock = false) const;`
- L168 _private prototype_ `void CloseMenu();` — Callback for an asset selection popup menu close.
- L171 _private prototype_ `void OnMaskAssetSelected(const FAssetData& AssetData);` — Callback for an actual mask asset selection in the context menu.
- L173 _private prototype_ `UTexture2D* GetBlockMaskValue() const;`
- L178 _private member_ `FBlockChangedDelegate BlockChangedDelegate;` — A delegate to report block changes
- L179 _private member_ `FBlockSelectionChangedDelegate SelectionChangedDelegate;`
- L180 _private member_ `FDeleteBlockDelegate DeleteBlocksDelegate;`
- L181 _private member_ `FAddBlockAtDelegate AddBlockAtDelegate;`
- L182 _private member_ `FSetBlockPriority OnSetBlockPriority;`
- L183 _private member_ `FSetReduceBlockSymmetrically OnSetReduceBlockSymmetrically;`
- L184 _private member_ `FSetReduceBlockByTwo OnSetReduceBlockByTwo;`
- L185 _private member_ `FSetBlockMask OnSetBlockMask;`
- L188 _private member_ `TAttribute<FIntPoint> GridSize;` — Size of the grid in blocks
- L191 _private member_ `TAttribute< TArray<FCustomizableObjectLayoutBlock> > Blocks;` — Array with all the editable blocks of the layout
- L194 _private member_ `TAttribute< TArray<FVector2f> > UVLayout;` — Array with all the UVs to draw in the layout
- L197 _private member_ `TArray<FVector2f> UnassignedUVLayoutVertices;` — Array with all the unassigned UVs
- L200 _private member_ `TAttribute<ELayoutGridMode> Mode = ELGM_Show;` — Layout mode
- L202 _private member_ `float CellSize = 0.0f;`
- L205 _private member_ `TMap<FGuid,FBlockWidgetData> BlockRects;` — Map to relate Block ids with blocks data
- L208 _private member_ `TArray<FGuid> SelectedBlocks;` — Interaction status.
- L209 _private member_ `TArray<FGuid> PossibleSelectedBlocks;`
- L213 _private member_ `bool bHasDragged = false;` — Indicates when we have dragged the mouse after click
- L216 _private member_ `bool bIsDragging = false;` — Indicates when we are dragging the mouse
- L219 _private member_ `bool bIsResizing = false;` — Indicates when we are resizing a block
- L222 _private member_ `bool bIsResizeCursor = false;` — Indicates when we have to change the mouse cursor
- L225 _private member_ `bool bIsSelecting = false;` — Indicates when we are making a selection
- L228 _private member_ `bool bIsPadding = false;` — Indicates when we are padding
- L231 _private member_ `FVector2D DragStart;` — Position where the drag started
- L234 _private member_ `FVector2D DrawOrigin;` — Position where the layout grid starts to be drawn
- L237 _private member_ `FVector2D PaddingStart;` — Position where the padding started
- L240 _private member_ `FRect2D SelectionRect;` — Selection Rectangle
- L243 _private member_ `FVector2D InitSelectionRect;` — Position where the Selection Rectangle started
- L246 _private member_ `FVector2D CurrentMousePosition;` — Current mouse position
- L251 _private member_ `int32 CurrentDrawBuffer = 0;` — Custom Slate drawing element. Used to improve the UVs drawing performance. * This is multi-buffered because it is read and written simultaneously from the render and the game threads.
- L252 _private member_ `TSharedPtr<class FUVCanvasDrawer> UVCanvasDrawers[UE_MUTABLE_UI_DRAWBUFFERS];`

#### struct `SCustomizableObjectLayoutGrid::FPointOfView`  
`struct FPointOfView`  
_L129-143_
- L132 _public member_ `FVector2D PaddingAmount = FVector2D::Zero();` — Amount of padding since start dragging
- L135 _public member_ `int32 Zoom = 1;` — Level of zoom
- L138 _public function_ `double GetZoomFactor() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_MUTABLE_UI_DRAWBUFFERS 2`
- L30 _enumerator_ `ELGM_Show` (scope `__anon738f22270103`)
- L31 _enumerator_ `ELGM_Edit` (scope `__anon738f22270103`)
- L32 _enumerator_ `ELGM_ShowUVsOnly` (scope `__anon738f22270103`)
- L33 _typedef_ `ELGM_Show, ELGM_Edit, ELGM_ShowUVsOnly, } ELayoutGridMode;`
- L53 _delegate_ `DECLARE_DELEGATE_TwoParams(FBlockChangedDelegate, FGuid , FIntRect );`
- L54 _delegate_ `DECLARE_DELEGATE_OneParam(FBlockSelectionChangedDelegate, const TArray<FGuid>& );`
- L55 _delegate_ `DECLARE_DELEGATE(FDeleteBlockDelegate);`
- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(FAddBlockAtDelegate, FIntPoint, FIntPoint);`
- L57 _delegate_ `DECLARE_DELEGATE_OneParam(FSetBlockPriority, int32);`
- L58 _delegate_ `DECLARE_DELEGATE_OneParam(FSetReduceBlockSymmetrically, bool);`
- L59 _delegate_ `DECLARE_DELEGATE_OneParam(FSetReduceBlockByTwo, bool);`
- L60 _delegate_ `DECLARE_DELEGATE_OneParam(FSetBlockMask, UTexture2D*);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectNodeObjectRTMorphTargetOverride.h` (Private)


#### class `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SkeletalMeshListViewWidget_Internal::FItemInfo`  
`class FItemInfo`  
_L31-45_
- L39 _private member_ `FName MorphName;` — Keep the information needed to loacte the NodeObject Morph Entry. For robustness keep names so we don't depend on the order or life of the observed element.
- L40 _private member_ `FName SkeletalMeshName;`
- L42 _private prototype_ `FItemInfo( const FName& InMorphName, const FName& InSkeletalMeshName);`

#### class `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SkeletalMeshListViewWidget_Internal::SRowWidget`  
`class SRowWidget : public SMultiColumnTableRow< TSharedPtr<FItemInfo> >`  
_L47-67_
- inherits: `SMultiColumnTableRow<TSharedPtr<FItemInfo>>`
- L51 _private function_ `SLATE_BEGIN_ARGS(SRowWidget)`
- L52 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<FItemInfo>, Item) SLATE_ARGUMENT(TWeakPtr<MainWidgetType>, MainWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L57 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L59 _private prototype_ `void OnEnumSelectionChanged(int32 InEnumValue, ESelectInfo::Type);`
- L60 _private prototype_ `int32 OverrideCurrentValue() const;`
- L62 _private prototype_ `ECustomizableObjectSelectionOverride* GetItemEnumPtr(UCustomizableObjectNodeObject* Node) const;`
- L64 _private member_ `TSharedPtr<FItemInfo> Item;`
- L65 _private member_ `TWeakPtr<MainWidgetType> MainWidget;`

#### class `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SSkeletalMeshListViewWidget`  
`class SSkeletalMeshListViewWidget : public SCompoundWidget`  
_L71-96_
- inherits: `SCompoundWidget`
- L73 _private function_ `SLATE_BEGIN_ARGS(SSkeletalMeshListViewWidget)`
- L74 _private prototype_ `SLATE_ARGUMENT(FName, MorphName) SLATE_ARGUMENT(TWeakPtr<MainWidgetType>, MainWidget) SLATE_END_ARGS() ~SSkeletalMeshListViewWidget()= default;`
- L80 _private typedef_ `using ItemType = SkeletalMeshListViewWidget_Internal::FItemInfo;`
- L82 _private member_ `FName MorphName;`
- L83 _private member_ `TWeakPtr<MainWidgetType> MainWidget;`
- L85 _private member_ `TSharedPtr< SListView< TSharedPtr<ItemType> > > View;`
- L86 _private member_ `TArray< TSharedPtr<ItemType> > Items;`
- L88 _private prototype_ `void Construct(const FArguments& InArgs);`
- L90 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow( TSharedPtr<ItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L94 _private prototype_ `void UpdateWidget();`
- L95 _private prototype_ `void PopulateItems();`

#### class `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::FItemInfo`  
`class FItemInfo`  
_L103-111_
- L108 _private prototype_ `FItemInfo(const FName& InName);`
- L110 _private member_ `FName Name;`

#### class `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SRowWidget`  
`class SRowWidget : public SMultiColumnTableRow< TSharedPtr<FItemInfo> >`  
_L113-130_
- inherits: `SMultiColumnTableRow<TSharedPtr<FItemInfo>>`
- L116 _public function_ `SLATE_BEGIN_ARGS(SRowWidget)`
- L117 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FItemInfo>, Item) SLATE_ARGUMENT(TWeakPtr<MainWidgetType>, MainWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L123 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L125 _public prototype_ `void OnEnumSelectionChanged(int32 InEnumValue, ESelectInfo::Type);`
- L126 _public prototype_ `int32 SelectionCurrentValue() const;`
- L128 _private member_ `TSharedPtr<FItemInfo> Item;`
- L129 _private member_ `TWeakPtr<MainWidgetType> MainWidget;`

#### class `SCustomizableObjectNodeSkeletalMeshRTMorphTargetOverride`  
`class SCustomizableObjectNodeSkeletalMeshRTMorphTargetOverride : public SCompoundWidget, public FGCObject`  
_L134-197_
- inherits: `SCompoundWidget,FGCObject`
- L136 _private typedef_ `using ItemType = CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::FItemInfo;`
- L138 _private typedef_ `using ChildItemType = CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::FChildItemInfo;`
- L141 _private typedef_ `using RowWidgetType = CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SRowWidget;`
- L143 _private typedef_ `using ChildRowWidgetType = CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SChildRowWidget;`
- L146 _private typedef_ `using SSkeletalMeshListViewWidget = CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal::SSkeletalMeshListViewWidget;`
- L149 _private typedef_ `using ViewType = SListView<TSharedPtr<ItemType>>;`
- L159 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectNodeSkeletalMeshRTMorphTargetOverride)`
- L160 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectNodeObject*, Node) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L164 _public prototype_ `~SCustomizableObjectNodeSkeletalMeshRTMorphTargetOverride() = default;`
- L166 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L168 _public prototype_ `void UpdateWidget();`
- L169 _public prototype_ `void PopulateItems();`
- L171 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow( TSharedPtr<ItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L175 _public prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L176 _public prototype_ `void OnFilterTextCommitted(const FText& SearchText, ETextCommit::Type CommitInfo);`
- L178 _public function_ `virtual FString GetReferencerName() const override`
- L185 _private member_ `TObjectPtr<UCustomizableObjectNodeObject> Node = nullptr;` — Pointer to the Current selected Node SkeletalMesh
- L188 _private member_ `TArray< TSharedPtr<ItemType> > Items;` — Widget List of the SkeletalMesh MorphTargets
- L189 _private member_ `TSharedPtr< ViewType > View;`
- L192 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — SerachBox for the morphs List
- L195 _private member_ `FString SearchBoxFilter;` — Text filter of the Search Box

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal`
- L23 _typedef_ `using MainWidgetType = SCustomizableObjectNodeSkeletalMeshRTMorphTargetOverride;` (scope `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal`)
- L26 _namespace_ `namespace SkeletalMeshListViewWidget_Internal` (scope `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal`)
- L100 _typedef_ `using FChildItemInfo = SkeletalMeshListViewWidget_Internal::FItemInfo;` (scope `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal`)
- L101 _typedef_ `using SChildRowWidget = SkeletalMeshListViewWidget_Internal::SRowWidget;` (scope `CustomizableObjectNodeSkeletalMeshRTMorphTargetOverride_Internal`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectNodeSkeletalMeshRTMorphSelector.h` (Private)


#### class `CustomizableObjectNodeSkeletalMeshRTMorphSelector_Internal::FRowItemInfo`  
`class FRowItemInfo`  
_L19-27_
- L24 _private prototype_ `FRowItemInfo(const FName& InName);`
- L26 _private member_ `FName Name;`

#### class `CustomizableObjectNodeSkeletalMeshRTMorphSelector_Internal::SRowWidget`  
`class SRowWidget : public SMultiColumnTableRow< TSharedPtr<FRowItemInfo> >`  
_L29-49_
- inherits: `SMultiColumnTableRow<TSharedPtr<FRowItemInfo>>`
- L31 _private typedef_ `using OwnerWidgetType = SCustomizableObjectNodeSkeletalMeshRTMorphSelector;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SRowWidget)`
- L35 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FRowItemInfo>, Item) SLATE_ARGUMENT(TWeakPtr<OwnerWidgetType>, OwnerWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L41 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L43 _public prototype_ `void OnMorphSelectionCheckStateChanged(ECheckBoxState CheckBoxState);`
- L44 _public prototype_ `ECheckBoxState IsMorphSelected() const;`
- L47 _private member_ `TSharedPtr<FRowItemInfo> Item;`
- L48 _private member_ `TWeakPtr<OwnerWidgetType> OwnerWidget;`

#### class `SCustomizableObjectNodeSkeletalMeshRTMorphSelector`  
`class SCustomizableObjectNodeSkeletalMeshRTMorphSelector : public SCompoundWidget, public FGCObject`  
_L52-101_
- inherits: `SCompoundWidget,FGCObject`
- L55 _private typedef_ `using ItemType = CustomizableObjectNodeSkeletalMeshRTMorphSelector_Internal::FRowItemInfo;`
- L58 _private typedef_ `using ListViewType = SListView<TSharedPtr<ItemType>>;`
- L64 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectNodeSkeletalMeshRTMorphSelector)`
- L65 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectNodeSkeletalMesh*, Node) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L69 _public prototype_ `~SCustomizableObjectNodeSkeletalMeshRTMorphSelector() = default;`
- L71 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L73 _public prototype_ `void UpdateWidget();`
- L75 _public prototype_ `void GenerateMorphsInfoList();`
- L77 _public prototype_ `TSharedRef<ITableRow> GenerateRow( TSharedPtr<ItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L80 _public prototype_ `bool IsRuntimeMorphsListEnabled() const;`
- L82 _public prototype_ `ECheckBoxState IsSelectAllChecked() const;`
- L83 _public prototype_ `void OnSelectAllCheckStateChanged(ECheckBoxState CheckBoxState);`
- L85 _public prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L86 _public prototype_ `void OnFilterTextCommitted(const FText& SearchText, ETextCommit::Type CommitInfo);`
- L88 _public function_ `virtual FString GetReferencerName() const override`
- L94 _private member_ `TObjectPtr<UCustomizableObjectNodeSkeletalMesh> Node = nullptr;`
- L96 _private member_ `TArray< TSharedPtr<ItemType> > Items;`
- L97 _private member_ `TSharedPtr< ListViewType > ListWidget;`
- L99 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L100 _private member_ `FString SearchBoxFilter;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace CustomizableObjectNodeSkeletalMeshRTMorphSelector_Internal`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SCustomizableObjectSystemVersion.h` (Private)


#### class `SCustomizableObjectSystemVersion`  
`class SCustomizableObjectSystemVersion : public SCompoundWidget`  
_L12-31_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectSystemVersion)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L26 _public prototype_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableBoolViewer.h` (Private)


#### class `SMutableBoolViewer`  
`class SMutableBoolViewer : public SCompoundWidget`  
_L10-43_
- inherits: `SCompoundWidget`
- desc: Mutable viewer to show a representation of a bool variable held by mutable.
- L13 _public function_ `SLATE_BEGIN_ARGS(SMutableBoolViewer)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `void SetBool(const bool& bInBool);` — Set the Mutable Bool to be used for this widget
- L25 _private member_ `bool bBoolValue;` — The value being monitorized
- L28 _private member_ `const FSlateColor TrueValueColor{ FLinearColor{0,1,0,1} };` — Colors used to paint the TRUE or FALSE value text
- L29 _private member_ `const FSlateColor FalseValueColor{ FLinearColor{1,0,0,1} };`
- L35 _private prototype_ `FText GetValue() const;` — Callback method used by the UI to get the value in a format it can display (FText) @return The FText that could be either TRUE or FALSE depending on the value of bBoolValue
- L41 _private prototype_ `FSlateColor GetColorForValue() const;` — Callback that returns the color that the UI text should be using for TRUE or FALSE @return The FSlateColor to be used by the FText shown in the UI

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableCodeViewer.h` (Private)


#### class `SMutableCodeViewer`  
`class SMutableCodeViewer : public SCompoundWidget`  
_L52-848_
- inherits: `SCompoundWidget`
- desc: This widget shows the internal Mutable Code for debugging purposes. This is not the Unreal source graph in the UCustomizableObject, but the actual Mutable virtual machine graph.
- L56 _public function_ `SLATE_BEGIN_ARGS(SMutableCodeViewer)`
- L58 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUnrealMutableResourceProvider>, ExternalResourceProvider) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UCustomizableObject& InObject, UCustomizableObjectInstance& InInstance, const TSharedPtr<UE::Mutable::Private::FModel>& InMutableModel);`
- L65 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L68 _public prototype_ `void ClearSelectedTreeRow() const;` — Clear the selected operation of the tree view.
- L76 _public prototype_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> BuildImage(UE::Mutable::Private::FOperation::ADDRESS TargetOpAddress) const;` — Evaluates the graph starting at the TargetOPAddress and returns an FImage resulting from that @param TargetOpAddress The OP Address to use as the root to be computed. @return A pointer to the FImage generated. May be null if the operation does not evaluate to an FImage @note This method is experimental and should not be used as example
- L79 _private member_ `TStrongObjectPtr<UCustomizableObject> Object;`
- L80 _private member_ `TStrongObjectPtr<UCustomizableObjectInstance> Instance;`
- L83 _private member_ `TSharedPtr<UE::Mutable::Private::FModel> MutableModel;` — The Mutable Model that we are showing.
- L85 _private member_ `TSharedPtr<FUnrealMutableResourceProvider> ExternalResourceProvider;`
- L88 _private member_ `TArray<TSoftObjectPtr<const UTexture>> ReferencedTextures;` — Array of external referenced textures in MutableModel, indexed by id.
- L89 _private member_ `TArray<TSoftObjectPtr<const UStreamableRenderAsset>> ReferencedMeshes;`
- L92 _private member_ `UE::Mutable::Private::FOperation::ADDRESS SelectedOperationAddress = 0;` — Selected model operation for preview.
- L95 _private member_ `TSharedPtr<UE::Mutable::Private::FParameters> PreviewParameters;` — Mutable parameters used in the preview.
- L98 _private member_ `TSharedPtr<SMutableParametersWidget> ParametersWidget;` — Widget showing the parameters that affect the current preview.
- L101 _private member_ `TSharedPtr<SMutableConstantsWidget> ConstantsWidget;` — Widget showing the constants found on the mutable Model program
- L104 _private member_ `bool bIsPreviewPendingUpdate = false;` — If true, the parameters have changed and we need to update the preview.
- L107 _private member_ `TSharedPtr<SBorder> PreviewBorder;` — Widget container where different previews will be created.
- L114 _private member_ `TSharedPtr<SMutableLayoutViewer> PreviewLayoutViewer;` — Widget used to show the preview of layout operation results. Once created it is reused to preserve the settings.
- L117 _private member_ `TSharedPtr<SMutableImageViewer> PreviewImageViewer;` — Widget used to show the preview of image operation results. Once created it is reused to preserve the settings.
- L120 _private member_ `TSharedPtr<SMutableMeshViewer> PreviewMeshViewer;` — Widget used to show a preview of a mesh and the metadata it holds
- L123 _private member_ `TSharedPtr<SMutableMaterialViewer> PreviewMaterialViewer;` — Widget used to show a preview of a mutable FMaterial and the data it holds
- L126 _private member_ `TSharedPtr<SMutableBoolViewer> PreviewBoolViewer;` — Widget used to show a preview of a mutable bool value
- L129 _private member_ `TSharedPtr<SMutableIntViewer> PreviewIntViewer;` — Widget used to show a preview of a mutable int value
- L132 _private member_ `TSharedPtr<SMutableScalarViewer> PreviewScalarViewer;` — Widget used to show a preview of a mutable float value
- L135 _private member_ `TSharedPtr<SMutableStringViewer> PreviewStringViewer;` — Widget used to show a preview of a mutable string value
- L138 _private member_ `TSharedPtr<SMutableColorViewer> PreviewColorViewer;` — Widget used to show a preview of a mutable color value
- L141 _private member_ `TSharedPtr<SMutableProjectorViewer> PreviewProjectorViewer;` — Widget used to display the data held on the mutable projector objects
- L144 _private member_ `TSharedPtr<SMutableSkeletonViewer> PreviewSkeletonViewer;` — Widget used to display the data held on the mutable skeleton objects
- L147 _private member_ `TSharedPtr<SMutableCurveViewer> PreviewCurveViewer;` — Widget used to display the data held on the mutable curve objects
- L150 _private member_ `TSharedPtr<STreeView<TSharedPtr<FMutableCodeTreeElement>>> TreeView;` — Tree widget showing the code hierarchically.
- L153 _private member_ `TArray<TSharedPtr<FMutableCodeTreeElement>> RootNodes;` — Root nodes of the tree widget.
- L164 _private function_ `friend FORCEINLINE bool operator == (const FItemCacheKey& A, const FItemCacheKey& B)`
- L169 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FItemCacheKey& Key)`
- L185 _private member_ `TMap< FItemCacheKey, TSharedPtr<FMutableCodeTreeElement>> ItemCache;` — Map with all the generated elements of the tree. Unique and duplicated elements will be present on this list and also the children of the unique elements. @note The children of duplicated elements will only be present once, as children of the unique element they duplicate. This is to avoid having identical elements on the tree (witch would cause a crash) while also being pointless due to how we manage expansion of duplicated elements.
- L188 _private member_ `TMap< UE::Mutable::Private::FOperation::ADDRESS, TSharedPtr<FMutableCodeTreeElement>> MainItemPerOp;` — Main tree item for each op. An op can be represented with multiple tree nodes if it is reachable from different paths.
- L191 _private member_ `TArray<TSharedPtr<FMutableCodeTreeElement>> TreeElements;` — List with all the elements related to nodes displayed on the tree.
- L194 _private member_ `TMap< UE::Mutable::Private::FOperation::ADDRESS, TSharedPtr<FMutableCodeTreeElement>> ExpandedElements;` — Array with all the elements that have been manually expanded by the user
- L199 _private prototype_ `void GenerateAllTreeElements();` — Before any UI operation generate all the elements that may be navigable over the tree. No children of duplicated addresses will be generated.
- L202 _private prototype_ `void GenerateElement( const int32& InStateIndex, UE::Mutable::Private::FOperation::ADDRESS InParentAddress, const UE::Mutable::Private::FProgram& InProgram);` — Support GenerateAllTreeElements by generating the elements recursively
- L206 _private member_ `TArray<UE::Mutable::Private::FOperation::ADDRESS> RootNodeAddresses;` — The addresses of the root operations. Cached when this object gets loaded on the Construct method of this slate
- L209 _private prototype_ `void CacheRootNodeAddresses();` — Utility method that provides you with the addresses of the root nodes of the program
- L212 _private member_ `bool bIsElementHighlighted = false;` — Control boolean to know if there are any highlighted elements on the tree
- L215 _private member_ `UE::Mutable::Private::FOperation::ADDRESS HighlightedOperation{};` — Operation that is currently being highlighted
- L229 _private member_ `const TArray<FName> EntryLabelColoringPolicyNames { "BY_COST", "BY_DATATYPE", };`
- L236 _private member_ `EEntryLabelColoringPolicy EntryLabelColoringPolicy = EEntryLabelColoringPolicy::BY_DATATYPE;` — Determines what should be used to paint the labels
- L239 _private member_ `const TArray<UE::Mutable::Private::EOpType> VeryExpensiveOperationTypes { UE::Mutable::Private::EOpType::ME_BINDSHAPE, UE::Mutable::Private::EOpType::ME_MASKCLIPMESH, UE::Mutable::Private::EOpType::ME_MASKCLIPUVMASK, UE::Mutable::Private::EOpType::ME_FORMAT, UE::Mutable::Private::EOpType::ME_MASKDIFF, UE::Mutable::Private::EOpType::ME_DIFFERENCE, UE::Mutable::Private::EOpType::ME_EXTRACTLAYOUTBLOCK, UE::Mutable::Private::EOpType::IM_MAKEGROWMAP, };` — Collection with all very expensive to run operation types
- L252 _private member_ `const TArray<UE::Mutable::Private::EOpType> ExpensiveOperationTypes { UE::Mutable::Private::EOpType::IM_PIXELFORMAT, UE::Mutable::Private::EOpType::IM_SWIZZLE, UE::Mutable::Private::EOpType::ME_PROJECT, UE::Mutable::Private::EOpType::ME_TRANSFORMWITHMESH, };` — Collection with all expensive to run operation types
- L271 _private member_ `const TArray<FSlateColor> ColorPerComputationalCost { FSlateColor(FLinearColor(1,1,1,1)),` — Array holding the relation between each computational cost category and the color to be used to display elements related with it.
- L282 _private prototype_ `EOperationComputationalCost GetOperationTypeComputationalCost(UE::Mutable::Private::EOpType OperationType) const;` — Provided an operation type it returns the category representing how much costs to run an operation of this type @param OperationType The operation type you want to know the computational cost of @return The enum value representing the computational cost of the operation type provided.
- L284 _private prototype_ `FSlateColor GetOperationDataTypeColor(UE::Mutable::Private::EDataType DataType) const;`
- L287 _public prototype_ `FSlateColor GetOperationColor(const UE::Mutable::Private::EOpType OperationType) const;`
- L290 _private prototype_ `void OnLabelColorPolicyChange(FName PolicyName, ESelectInfo::Type Arg);`
- L291 _private prototype_ `TSharedRef<SWidget> OnLabelColorPolicyGenerateWidget(FName PolicyName);`
- L292 _private prototype_ `FText GetCurrentLabelColoringPolicyText() const;`
- L299 _private member_ `TSharedPtr<SComboBox<TSharedPtr<const FMutableOperationElement>>> TargetedTypeSelector;` — Slate object that provides the user a way of selecting what kind of operation it wants to navigate.
- L302 _private member_ `TArray<TSharedPtr<const FMutableOperationElement>> FoundModelOperationTypeElements;` — Data backend for the list displayed for the navigation type selection
- L305 _private member_ `TSharedPtr<const FMutableOperationElement> NoneOperationEntry;` — Navigation operation entry representing the NONE type
- L310 _private member_ `TSharedPtr<const FMutableOperationElement> ConstantBasedNavigationEntry;` — Navigation operation entry used to be able to set the UI to show we are performing a constant resource based navigation
- L313 _private member_ `TSharedPtr<const FMutableOperationElement> CurrentlySelectedOperationTypeElement;` — Currently selected element on the TargetedTypeSelector slate. Actively used by the ui
- L316 _private member_ `UE::Mutable::Private::EOpType OperationTypeToSearch = UE::Mutable::Private::EOpType::NONE;` — Operation type we are using to search for tree nodes. Driven primarily by the UI
- L320 _private member_ `TArray< TPair< UE::Mutable::Private::EOpType,uint32>> ModelOperationTypes;` — Operation types present on the currently set mutable model. The value of the TPair represents the amount of times operations using it have been found (not duplicates)
- L323 _private member_ `TArray<FString> ModelOperationTypeNames;` — Array with all the names for each of the operations available on mutable. Used by the UI
- L326 _private prototype_ `void GenerateNavigationOpTypeStrings();` — Stores a list of strings based on the possible types of operations mutable define to be used by the UI
- L329 _private prototype_ `void GenerateNavigationDropdownElements();` — Generate a list of elements that will be used as backend for the navigation type selection dropdown
- L335 _private prototype_ `void CacheOperationTypesPresentOnModel();` — Fills ModelOperationTypes with all the types present on the current model. It also makes sure we have a NONE operation and that the operations are sorted alphabetically. @note Method designed to be called once per model.
- L343 _private prototype_ `FText GetCurrentNavigationOpTypeText() const;` — Generate the text to be used by the navigation operation selector
- L346 _private prototype_ `FSlateColor GetCurrentNavigationOpTypeColor() const;` — Returns the color to be used by the text being currently displayed as selected on the operation selector
- L351 _private prototype_ `TSharedRef<SWidget> OnGenerateOpNavigationDropDownWidget(TSharedPtr<const FMutableOperationElement> InMutableOperationElement) const;` — Callback invoked by the ComboBox used for displaying and selecting operation types for navigation. it gets invoked each time the slate object requires to draw a line representing one of the elements set on FoundModelOperationTypeElements
- L356 _private prototype_ `void OnNavigationSelectedOperationChanged(TSharedPtr<const FMutableOperationElement, ESPMode::ThreadSafe> MutableOperationElement, ESelectInfo::Type Arg);` — Callback invoked each time the selected operation on our navigation slate changes. It can change due to UI interaction or also due to direct change by invoking the SetSelectedOption on the SComboBox TargetedTypeSelector
- L361 _private prototype_ `FText OnPrintNavigableObjectAddressesCount() const;` — Callback used to print on screen the amount of operations found on the tree that share the same operation type that the one currently selected on the navigation system.
- L364 _private prototype_ `bool CanInteractWithPreviousOperationButton() const;` — Method that tells the UI if the bottom to go to the previous element can be interacted
- L367 _private prototype_ `bool CanInteractWithNextOperationButton() const;` — Method that tells the UI if the bottom to go to the next element can be interacted
- L374 _private prototype_ `FReply OnGoToPreviousOperationButtonPressed();` — Used by the UI and internally does what is necessary to get to the previous element of the targeted search type. It is designed to work alongside GoToPreviousOperationAfterRefresh(...) @return A reply to tell if the UI action has been handled or not.
- L380 _private prototype_ `FReply OnGoToNextOperationButtonPressed();` — Used by the UI and internally does what is necessary to get to the next element of the targeted search type. It is designed to work alongside GoToNextOperationAfterRefresh(...) @return A reply to tell if the UI action has been handled or not.
- L386 _private prototype_ `void OnSelectedOperationTypeFromTree();` — Callback method used to allow the user to directly set the type of operation to be scanning directly by selecting a operation on the tree and using that operation type as the type to search for
- L393 _private member_ `bool bWasScrollToTargetRequested = false;` — Flag monitoring if we have requested a scroll operation to reach the targeted element
- L396 _private member_ `bool bWasUniqueExpansionInvokedForNavigation = false;` — Flag designed to tell the system when the expansion of unique elements have been performed as part of the navigation operation
- L403 _private member_ `TArray<TSharedPtr<FMutableCodeTreeElement>> NavigationElements;` — Array with all the elements of the type we are looking for (shared type of constant resource).
- L406 _private member_ `int64 NavigationIndex = -1;` — Operation types present on the currently set mutable model.
- L409 _private prototype_ `void SortElementsByTreeIndex(TArray<TSharedPtr<FMutableCodeTreeElement>>& InElementsArrayToSort);` — Sort the contents of NavigationElements to follow a sequential pattern using the indices of the elements from 0 to +n
- L413 _private member_ `TSharedPtr<FMutableCodeTreeElement> ToFocusElement;` — If the focus could not be performed directly then cache the target until it is in view and can therefore be focused. It will be valid if we are trying to focus something (it) and invalid if the focus operation has already been resolved.
- L418 _private prototype_ `void FocusViewOnNavigationTarget(TSharedPtr<FMutableCodeTreeElement> InTargetElement);` — Focus the current NavigationElement and places it into view. It also selects it so the previewer for the element gets invoked
- L547 _private prototype_ `void CacheAddressesOfOperationsOfType();` — Provided an Operation type store as navigation addresses all operations of the targeted navigation Op type @note The operations found get saved on the collection  NavigationOPAddresses.
- L556 _private prototype_ `void GetOperationsOfType(const UE::Mutable::Private::EOpType& TargetOperationType, FElementsSearchCache& InSearchPayload, const UE::Mutable::Private::FProgram& InProgram);` — Fills an array with all the addresses of operations that do have in common the same targeted operation type @param TargetOperationType The operation type used to discriminate what operation addresses we want to retrieve. processing them more than once. @param InSearchPayload A caching structure designed to hold the data that gets passed from one recursive call to the other. It also stores the found elements and other data. @param InProgram The mutable program holding the data to be searched over
- L576 _public prototype_ `void CacheAddressesRelatedWithConstantResource(const UE::Mutable::Private::EDataType ConstantDataType, const int32 IndexOnConstantsArray);` — Provided a constant resource data type and index on its constant array this method sets all the operations that make usage of said constant to be navigable by the navigation system. @note The output of this operation will be cached onto NavigationOPAddresses so we can navigate over them. @param ConstantDataType The constant data type to locate operations referencing it: It is required for the system to know what operations should be checked for the usage of the provided constant resource. For example, a type of UE::Mutable::Private::EDataType::DT_Curve will try to locate operations that we know operate with constant curves. @param IndexOnConstantsArray The index of the constant on its constants array. If it is, for example, a constant mesh this value represents the index of the constant inside constantMeshes array on UE::Mutable::Private::program.
- L589 _private prototype_ `void GetOperationsReferencingConstantResource(const UE::Mutable::Private::EDataType ConstantDataType, const int32 IndexOnConstantsArray, FElementsSearchCache& InSearchPayload, const UE::Mutable::Private::FProgram& InProgram);` — Provided a data type and the index of the constant object using said data type locate all operations that do directly make use of said constant resource. @param ConstantDataType The type of the resource we are providing an index of. @param IndexOnConstantsArray The index of the constant resource we want to know what operations are using it. @param InSearchPayload Cache object that will end up containing all the elements related with the provided constant resource @param InProgram The mutable program containing all the operations of the graph.
- L606 _private prototype_ `bool IsConstantResourceUsedByOperation(const int32 IndexOnConstantsArray, const UE::Mutable::Private::EDataType ConstantDataType, const UE::Mutable::Private::FOperation::ADDRESS OperationAddress, const UE::Mutable::Private::FProgram& InProgram) const;` — Provided an operation address this method tells us if that address is making use of our constant resource or not. It will take into account the datatype of the provided resource to discard or acknowledge the operation type of the provided operation address. @param IndexOnConstantsArray The index onto its respective constants array of the constant resource provided. We do not give a pointer to the constant resource but the index of it onto its hosting array. @param ConstantDataType The type of data we know the constant uses. It is used to check for ones or other operations since not all operations do access the same constant resources. @param OperationAddress The address of the operation currently being scanned for constant resources. @param InProgram The mutable program to use to check the type of operation that corresponds to that operation address. @return True if the operation at OperationAddress does make use of the provided constant resource. False otherwise
- L616 _private member_ `FString SearchString;` — Current text being used to perform a search by name. It gets updated each time the user changes the text in the SearchBox
- L621 _private member_ `bool bIsSearchStringRegularExpression = false;` — Flag that determines how to interpret the SearchString provided. If true it means it is a regular expression. If not it is just a fragment of text to seek for in the tree of operations.
- L624 _private member_ `FString LastSearchedString;` — Last search configuration -> Prevents recurrent searches with the same search parameters
- L625 _private member_ `bool bWasLastSearchRegEx = false;`
- L626 _private member_ `TSharedPtr<UE::Mutable::Private::FModel> LastSearchedModel;`
- L629 _private member_ `TArray<TSharedPtr<FMutableCodeTreeElement>> NameBasedNavigationElements;` — A collection with all the elements we have found to be related with the SearchString.
- L632 _private member_ `int32 StringNavigationIndex = -1;` — Index in the above array. Current navigation index for the navigation over elements related with the SearchString
- L637 _private prototype_ `void OnRegexToggleChanged(ECheckBoxState CheckBoxState);` — UI Callback that sets the backend flag to mirror the UI toggle. @param CheckBoxState The new state of the checkBox object being updated
- L642 _private prototype_ `void OnTreeStringSearch(SSearchBox::SearchDirection SearchDirection);` — Exposes arrows to allow navigation over the found elements and handles the navigation using those. @param SearchDirection The direction (up or down) being used to navigate the collection of tree elements
- L647 _private prototype_ `void OnTreeSearchTextChanged(const FText& InUpdatedText);` — Invoked each time the user changes the search text in the UI. NewText cached in SearchString variable @param InUpdatedText The new value set by the user for the TextBox used to provide the search string.
- L652 _private prototype_ `TOptional<SSearchBox::FSearchResultData> SearchResultsData() const;` — Get the search results for the current search. Used by the Ui to generate some context related elements. @return Data for external search results to be shown in the search box.
- L659 _private prototype_ `void OnTreeSearchTextCommitted(const FText& InUpdatedText, ETextCommit::Type TextCommitType);` — Invoked each time the user commits to the text provided. It also caches the text provided by the user @param InUpdatedText The current text being exposed in the UI textBox to be used for search. It is not being used since we rely in the value cached in the global variable "SearchString" @param TextCommitType Determines how the user did commit the search string.
- L662 _private prototype_ `void GoToNextOperation();` — Move the focus to the next element in the collection of related elements to the cached SearchString.
- L665 _private prototype_ `void GoToPreviousOperation();` — Move the focus to the previous element in the collection of related elements to the cached SearchString.
- L668 _private prototype_ `void GoToTargetOperation(const int32& InTargetIndex);` — Provided an index inside the NameBasedNavigationElements array change the focus to it.
- L671 _private prototype_ `void CacheOperationsMatchingStringPattern();` — Provided a search string and a search type a series of elements to be navigated over
- L679 _private prototype_ `void GetOperationsMatchingStringPattern(const FString& InStringPattern,const bool bIsRegularExpression, FElementsSearchCache& SearchPayload, const UE::Mutable::Private::FProgram& InProgram);` — Searches the item cache in search of a string pattern that can be treated as a regular string or as a Regular expression. @param InStringPattern The string to be searched over. It will get compared with the "Main Label" of the comparing operations. @param bIsRegularExpression True if the InStringPattern is ought to be treated as a regular expression, false otherwise. @param SearchPayload Structure containing the operations to be used as the origin of the search. This object will also contain the results of the search. @param InProgram MutableProgram used to allow the search of the children of the operations being currently processed.
- L686 _private prototype_ `FString GetOperationDescriptiveText(const FItemCacheKey& InItemCacheKey);` — Provided a ItemCacheKey this method returns the string that represents it. It will not take in consideration duplicated entries since those are not part of said ItemCache. @param InItemCacheKey The key representing the current operation being searched. @return The MainLabel used to display the provided operation.
- L694 _private prototype_ `TSharedRef<ITableRow> GenerateRowForNodeTree(TSharedPtr<FMutableCodeTreeElement> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Callback that generates a new Row object based on a Tree Node
- L701 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FMutableCodeTreeElement> InInfo, TArray< TSharedPtr<FMutableCodeTreeElement> >& OutChildren);` — Provided an element it is returned a list with all the immediate children it has @param InInfo - The MutableCodeElement whose children objects we are searching @param OutChildren - The children of the provided MutableCodeTreeElement
- L708 _private prototype_ `void OnExpansionChanged(TSharedPtr<FMutableCodeTreeElement> InInfo, bool bInExpanded);` — Callback invoked each time an element of the tree gets expanded or contracted @param InInfo - The MutableCodeElement to be contracted or expanded @param bInExpanded - Determines if the action is of contraction (false) or expansion (true).
- L717 _private prototype_ `void OnSelectionChanged(TSharedPtr<FMutableCodeTreeElement> InInfo, ESelectInfo::Type SelectInfo);` — Callback invoked each time the selected element changes used to generate the previews depending of the operation selected @param InInfo - The MutableCodeElement that has been selected. Can be null if unselected @param SelectInfo - Way in witch the selection changed
- L723 _private prototype_ `void OnRowReleased(const TSharedRef<ITableRow>& InTreeRow);` — Callback invoked when a tree row is getting removed @param InTreeRow - The tree row that is being removed from the tree view
- L726 _private prototype_ `TSharedPtr<SWidget> OnTreeContextMenuOpening();` — Callback invoked when whe press the right mouse button. Useful for adding context menu objects
- L728 _private prototype_ `void TreeExpandRecursive(TSharedPtr<FMutableCodeTreeElement> Info, bool bExpand );`
- L755 _private prototype_ `void TreeExpandElements(TArray<TSharedPtr<FMutableCodeTreeElement>>& InElementsToExpand, bool bForceExpandDuplicates = false, UE::Mutable::Private::EDataType FilteringDataType = UE::Mutable::Private::EDataType::None, TSharedPtr<FProcessedOperationsBuffer> InExpandedOperationsBuffer = nullptr);` — Expands the provided elements and all the children they have. @note It performs the operation by going to the deepest children and expanding from then upwards to the origin before proceeding to the next parent. This way we make sure that the expansion of the elements is following the order of left to right and top to bottom in a "Z" like pattern like the way the tree gets read by humans. @param InElementsToExpand - The root info objects where to start the expansion @param bForceExpandDuplicates - (Optional) Determines if the duplicated objects must be expanded. Used for certain situations where we want to expand them. By default they do not get expanded @param FilteringDataType - (Optional) determines what kind of operations should be expanded. By default no filtering is applied @param InExpandedOperationsBuffer (Optional) Object containing all the duplicated and original elements already processed during the subsequent recursive calls to this method.
- L762 _private prototype_ `void TreeExpandUnique();` — Expand only the unique elements (mot duplicates)
- L765 _private prototype_ `void TreeExpandInstance();` — Expand only the elements using as operation type Instance
- L768 _private prototype_ `void TreeExpandSelected();` — Grabs the selected element and expands all the elements inside the selected branch. Duplicates are ignored
- L774 _private prototype_ `void HighlightDuplicatesOfEntry(const TSharedPtr<FMutableCodeTreeElement>& InTargetElement);` — Highlights all tree elements that share the same operation as the element provided @param InTargetElement - The info object to be used as blueprint to search for similar objects and highlight them
- L777 _private prototype_ `void ClearHighlightedItems();` — Clear all the highlighted elements and set them to their default visual state
- L780 _private prototype_ `void OnPreviewParameterValueChanged( int32 ParamIndex );` — Called when any parameter value has changed, with the parameter index as argument.
- L789 _private member_ `bool bShouldRecalculateStates = false;` — FLag that determines if the expansion of elements should require the computation of the state of it's child elements. Useful to avoid unnecessary calls for state resting of movable branches like the children of operations that are repeated in the tree slate
- L800 _private prototype_ `void GetVisibleChildren(TSharedPtr<FMutableCodeTreeElement> InInfo, TSet<TSharedPtr<FMutableCodeTreeElement>>& OutChildren);` — Provided an element of the tree view return all the children of it (direct and indirect). The search will stop (depth) if a children is found to not be expanded. This way we avoid infinite searches (since we do not stop at duplicates). @note It DOES NOT check for visibility by asking the TreeView. It only gets the elements that could be seen in theory. @note This method will return expanded and not expanded children but only the expanded children will get it's children searched and therefore provided by this method. In conclusion, only the elements that could be seen by the view will get provide. @param InInfo The element whose children we want to grab. It can be expanded or not. @param OutChildren A collection of children elements. Only the elements that could be seen in the tree view (expanded and the root element of an unexpanded branch) wll get added to this collection.
- L808 _private member_ `int32 MipsToSkip = 0;`
- L811 _private member_ `bool bSelectedOperationIsImage = false;`
- L813 _private prototype_ `FReply UpdateParameters();`
- L816 _private prototype_ `EVisibility IsMipSkipVisible() const;` — Stores a list of strings based on the possible types of operations mutable define to be used by the UI
- L819 _private prototype_ `TOptional<int32> GetCurrentMipSkip() const;` — Stores a list of strings based on the possible types of operations mutable define to be used by the UI
- L822 _private prototype_ `void OnCurrentMipSkipChanged(int32 NewValue);`
- L829 _public prototype_ `void PreviewMutableImage (UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> InImagePtr);`
- L830 _public prototype_ `void PreviewMutableMesh (UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh> InMeshPtr);`
- L831 _public prototype_ `void PreviewMutableMaterial(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMaterial> InMaterialPtr);`
- L832 _public prototype_ `void PreviewMutableLayout(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FLayout> Layout);`
- L833 _public prototype_ `void PreviewMutableSkeleton(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FSkeleton> Skeleton);`
- L834 _public prototype_ `void PreviewMutablePhysics(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FPhysicsBody> Physics);`
- L835 _public prototype_ `void PreviewMutableString(const FString& InString);`
- L836 _public prototype_ `void PreviewMutableProjector(const UE::Mutable::Private::FProjector* Projector);`
- L837 _public prototype_ `void PreviewMutableMatrix(const FMatrix44f& Mat);`
- L838 _public prototype_ `void PreviewMutableShape(const UE::Mutable::Private::FShape* Shape);`
- L839 _public prototype_ `void PreviewMutableCurve(const FRichCurve& Curve);`
- L842 _private prototype_ `void PrepareStringViewer();`
- L843 _private prototype_ `void PrepareImageViewer();`
- L844 _private prototype_ `void PrepareMeshViewer();`
- L845 _private prototype_ `void PrepareMaterialViewer();`
- L846 _private prototype_ `void PrepareLayoutViewer();`
- L847 _private prototype_ `void PrepareProjectorViewer();`

#### struct `SMutableCodeViewer::FItemCacheKey`  
`struct FItemCacheKey`  
_L158-173_
- desc: Cache of tree elements matching the operations that have been generated so far. We store both the parent and the operation in the key, because a single operation may appear multiple times if it has different parents.
- L160 _public member_ `UE::Mutable::Private::FOperation::ADDRESS Parent=0;`
- L161 _public member_ `UE::Mutable::Private::FOperation::ADDRESS Child=0;`
- L162 _public member_ `uint32 ChildIndexInParent=0;`

#### enum `SMutableCodeViewer::EEntryLabelColoringPolicy`  
`enum class EEntryLabelColoringPolicy : int32`  
_L221-227_
- L223 _public enumerator_ `BY_COST = 0`
- L224 _public enumerator_ `BY_DATATYPE`
- L226 _public enumerator_ `COUNT`

#### enum `SMutableCodeViewer::EOperationComputationalCost`  
`enum class EOperationComputationalCost : uint8`  
_L261-266_
- desc: Enum designed to be able to notify the row generation of the type of operation being generated
- L263 _public enumerator_ `Standard = 0` — All other operation types
- L264 _public enumerator_ `Expensive = 1` — The ones located on ExpensiveOperationTypes
- L265 _public enumerator_ `VeryExpensive = 2` — The ones located on VeryExpensiveOperationTypes

#### struct `SMutableCodeViewer::FElementsSearchCache`  
`struct FElementsSearchCache`  
_L423-537_
- desc: Wrapper struct designed to be used as cache for all elements found during the navigation system search for elements of X Type or relation with a targeted constant resource. It is designed to be used and then destroyed once the search operation has been completed
- L426 _public member_ `TSet<UE::Mutable::Private::FOperation::ADDRESS> ProcessedAddresses;` — Set of addresses that have already been searched for relevant data
- L429 _public member_ `TArray<TSharedPtr<FMutableCodeTreeElement>> FoundElements;` — Collection of elements that have been found during the search. They may be related by OP_Type or used constant resource
- L436 _public member_ `TArray<FItemCacheKey> BatchData;` — Array containing all the next addresses to be processed. The child is the address itself to be later processed The parent is the parent address of the child. The ChildIndexInParent is the index (or child position) o the child address on Child as part of the child set of the parent address.
- L443 _public function_ `void SetupRootBatch(const TArray<UE::Mutable::Private::FOperation::ADDRESS>& InRootNodeAddresses)` — Generates the structures to be able to start the search of elements. It uses the root addresses as the start of the search operation. @param InRootNodeAddresses The addresses of the root operations of the operations tree
- L475 _public function_ `void AddToFoundElements(const UE::Mutable::Private::FOperation::ADDRESS OpAddress,const int32 IndexAsChildOfInputAddress, const TMap<FItemCacheKey, TSharedPtr<FMutableCodeTreeElement>>& InItemCache)` — Method to cache the provided mutable address as one of the addresses that are of the type we are looking for or maybe is related with the constant resource we are looking for operations related with. @param OpAddress The address to save as one related with a operation type or constant resource @param IndexAsChildOfInputAddress The index on BatchData that represents the parent of the provided operation address @param InItemCache Cache with all the elements of the tree. Here is where we search for the element based on the OpAddress and the parent and ChildIndexInParent provided thanks to IndexAsChildOfInputAddress
- L506 _public function_ `void CacheChildrenOfAddressIfNotProcessed(UE::Mutable::Private::FOperation::ADDRESS InParentAddress, const UE::Mutable::Private::FProgram& InProgram, TArray<FItemCacheKey>& OutFoundChildrenData)` — Caches the provided parent address to the Search payload so they can be later read and processed on another batch of the method tasked with finding related operations to operation type or constant resource. @param InParentAddress The parent address to search children of. @param InProgram The mutable program that will be used to perform the children search. @param OutFoundChildrenData Array with all the ItemCacheKeys that represent all the children found @note It will not add the children of any provided ParentAddress for the next batch if the parent address provided has already been processed and therefore whose children have already been searched or prepared for searching.

#### struct `SMutableCodeViewer::FProcessedOperationsBuffer`  
`struct FProcessedOperationsBuffer`  
_L733-740_
- desc: Temporal object designed to be used during the recursive operation of TreeExpandElements() and group strongly related data
- L736 _public member_ `TArray<UE::Mutable::Private::FOperation::ADDRESS> ExpandedOriginalOperations;` — Array with the operation addresses of all original (not duplicates) expanded operations.
- L739 _public member_ `TArray<UE::Mutable::Private::FOperation::ADDRESS> ExpandedDuplicatedOperations;` — Array with the operation addresses of all duplicated expanded operations.

#### class `FMutableOperationElement`  
`class FMutableOperationElement : public TSharedFromThis<FMutableOperationElement>`  
_L851-893_
- inherits: `TSharedFromThis<FMutableOperationElement>`
- desc: The data of a row on the operation type dropdown.
- L855 _public function_ `FMutableOperationElement(UE::Mutable::Private::EOpType InOperationType,FText OperationTypeName,uint32 OperationTypeInstanceCount)`
- L874 _public function_ `void SetEntryColorOverride(const FSlateColor& InEntryColorOverride)` — Set the color to be used by this entry so it gets used instead of the one defined by the coloring policy @param InEntryColorOverride The color to be used for this entry.
- L881 _public member_ `UE::Mutable::Private::EOpType OperationType;`
- L883 _public member_ `FText OperationTypeText;`
- L885 _public member_ `FSlateColor OperationTextOverrideColor;`
- L886 _public member_ `bool bEntryColorWasOverriden = false;`
- L889 _public function_ `EVisibility GetEntryVisibility() const` — Get the type of visibility a slate representing this objects should have.

#### class `FMutableCodeTreeElement`  
`class FMutableCodeTreeElement : public TSharedFromThis<FMutableCodeTreeElement>`  
_L898-969_
- inherits: `TSharedFromThis<FMutableCodeTreeElement>`
- desc: An row of the code tree in the SMutableCodeViewer.
- L901 _public prototype_ `FMutableCodeTreeElement(int32 InIndexOnTree, const int32& InMutableStateIndex, const TSharedPtr<UE::Mutable::Private::FModel, ESPMode::ThreadSafe>& InModel, UE::Mutable::Private::FOperation::ADDRESS InOperation, const FString& InCaption, TWeakPtr<SMutableCodeViewer> InCodeViewer, UE::Mutable::Private::EOpType InOperationType, const TSharedPtr<FMutableCodeTreeElement>* InDuplicatedOf = nullptr);`
- L903 _public prototype_ `void SetElementCurrentState(const int32& InStateIndex);`
- L905 _public prototype_ `void GenerateLabelText();`
- L907 _public prototype_ `int32 GetStateIndex() const;`
- L909 _public prototype_ `FSlateColor GetLabelColor() const;`
- L914 _public member_ `TSharedPtr<UE::Mutable::Private::FModel, ESPMode::ThreadSafe> MutableModel;` — Model this operation is part of
- L917 _public member_ `UE::Mutable::Private::FOperation::ADDRESS MutableOperation;` — Mutable Graph Node represented in this tree row.
- L920 _public member_ `TSharedPtr<FMutableCodeTreeElement> DuplicatedOf;` — If this tree element is a duplicated of another op, this is the op.
- L923 _public member_ `FString MainLabel;` — Label to be used to represent this operation in the tree
- L930 _public member_ `int32 IndexOnTree;` — The current position of this element on the tree view. Used for navigation
- L937 _public member_ `bool bIsStateConstant = false;` — If true means that it will not update when a runtime parameter on the state gets updated
- L940 _public member_ `bool bIsDynamicResource = false;` — If true then the mesh or image of this operation may change during the state update
- L947 _public member_ `bool bIsExpanded = false;` — Flag that reflects the expanded state of the element in the tree view. It is used in order to know when an element should or should not has it's set state index updated (and the data that comes with it). @note It does not mean the element can be seen at the moment in the view, just that, in case of expansion of a parent element then this could be part of the view (if inside view space).
- L949 _public member_ `bool bHasDuplicate = false;`
- L956 _private member_ `int32 CurrentMutableStateIndex = -1;` — Represents as part of what state this element is currently part of. Will change for elements that are children of duplicated elements (duplicated) since children of duplicated elements are still unique and therefore they can be present in more than one state (but can just appear in one state at any given time)
- L959 _private member_ `FString Caption;` — String representing additional data like the state this operation is from. It may be empty.
- L962 _private member_ `TWeakPtr<SMutableCodeViewer> HostCodeViewer;` — Code Viewer hosting the tree that uses this object. Will be used to evaluate the code to be displayed by the tree entry.
- L965 _private member_ `UE::Mutable::Private::EOpType OperationType;` — The type of the mutable operation.
- L968 _private member_ `FSlateColor ZeroOperationColor = FColor(FColorList::DimGrey);` — The color to be used by the row representing this object

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace ESelectInfo`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Mutable` (scope `UE`)
- L45 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace Mutable` (scope `UE`)
- L46 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L518 _function_ `` (scope `SMutableCodeViewer::FElementsSearchCache::CacheChildrenOfAddressIfNotProcessed`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableColorViewer.h` (Private)


#### class `SMutableColorViewer`  
`class SMutableColorViewer : public SCompoundWidget`  
_L10-38_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SMutableColorViewer)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `void SetColor(FVector4f Color);` — Set the Mutable Bool to be used for this widget
- L25 _private member_ `FVector4f Color = FVector4f(0,0,0,1);` — Color being displayed
- L28 _private member_ `TSharedPtr<SColorBlock> ColorPreview;` — Color box widget designed to serve as a preview of the color reported by mutable
- L31 _private prototype_ `FLinearColor GetColor() const;` — Callback method invoked by the ColorPreview slate to get a FLinearColor object to display.
- L34 _private prototype_ `FText GetRedValue() const;` — Retrieve the values of each color component for the UI Texts to be updated
- L35 _private prototype_ `FText GetGreenValue() const;`
- L36 _private prototype_ `FText GetBlueValue() const;`
- L37 _private prototype_ `FText GetAlphaValue() const;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableConstantsWidget.h` (Private)


#### struct `FMutableConstantElement`  
`struct FMutableConstantElement`  
_L27-31_
- desc: Base Structure to define the different elements used by the lists on this object
- L30 _public member_ `uint32 IndexOnSourceVector;` — The index of this element on the host vector.

#### struct `FMutableConstantImageElement`  
`struct FMutableConstantImageElement : public FMutableConstantElement`  
_L36-39_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant images found on the model
- L38 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> ImagePtr;`

#### struct `FMutableConstantMeshElement`  
`struct FMutableConstantMeshElement : public FMutableConstantElement`  
_L44-47_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant meshes found on the model
- L46 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh> MeshPtr;`

#### struct `FMutableConstantStringElement`  
`struct FMutableConstantStringElement : public FMutableConstantElement`  
_L52-55_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant strings found on the model
- L54 _public member_ `FString MutableString;`

#### struct `FMutableConstantLayoutElement`  
`struct FMutableConstantLayoutElement : public FMutableConstantElement`  
_L60-63_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant layouts found on the model
- L62 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FLayout> Layout;`

#### struct `FMutableConstantSkeletonElement`  
`struct FMutableConstantSkeletonElement : public FMutableConstantElement`  
_L68-71_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant skeletons found on the model
- L70 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FSkeleton> Skeleton;`

#### struct `FMutableConstantPhysicsElement`  
`struct FMutableConstantPhysicsElement : public FMutableConstantElement`  
_L76-79_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant skeletons found on the model
- L78 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FPhysicsBody> Physics;`

#### struct `FMutableConstantMaterialElement`  
`struct FMutableConstantMaterialElement : public FMutableConstantElement`  
_L84-87_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant materials found on the model
- L86 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMaterial> MutableMaterial;`

#### struct `FMutableConstantProjectorElement`  
`struct FMutableConstantProjectorElement : public FMutableConstantElement`  
_L92-95_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant projectors found on the model
- L94 _public member_ `const UE::Mutable::Private::FProjector* Projector = nullptr;`

#### struct `FMutableConstantMatrixElement`  
`struct FMutableConstantMatrixElement : public FMutableConstantElement`  
_L100-103_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant matrices found on the model
- L102 _public member_ `FMatrix44f Matrix;`

#### struct `FMutableConstantShapeElement`  
`struct FMutableConstantShapeElement : public FMutableConstantElement`  
_L108-111_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant shapes found on the model
- L110 _public member_ `const UE::Mutable::Private::FShape* Shape = nullptr;`

#### struct `FMutableConstantCurveElement`  
`struct FMutableConstantCurveElement : public FMutableConstantElement`  
_L116-119_
- inherits: `FMutableConstantElement`
- desc: Cache object used for the generation of the ui elements related to the constant curves found on the model
- L118 _public member_ `FRichCurve Curve;`

#### class `SMutableConstantsWidget`  
`class SMutableConstantsWidget : public SCompoundWidget`  
_L125-355_
- inherits: `SCompoundWidget`
- desc: Slate panel object designed to hold all the model constants
- L127 _private function_ `SLATE_BEGIN_ARGS(SMutableConstantsWidget)`
- L137 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<UE::Mutable::Private::FModel> InModel, TSharedPtr<SMutableCodeViewer> InMutableCodeViewerPtr);` — Builds the widget @param InArgs - Arguments provided when generating this slate object @param InMutableProgramPtr - Pointer to the UE::Mutable::Private::FProgram object that holds the constants data. @param  InMutableCodeViewerPtr - Pointer to the MutableCodeViewer tasked with the previewing of the constant values
- L144 _public prototype_ `void ClearSelectedConstantItems(UE::Mutable::Private::EDataType ExceptionDataType = UE::Mutable::Private::EDataType::None) const;` — It clears the selected element for all constant view slates (SListView and STileView) except the one that shows the data of the provided type @param ExceptionDataType The type of data of the slate container that we want to skip when clearing the selected elements. EX : We want to clear all selected elements but not the ones from the constant images. Provide as argument "UE::Mutable::Private::EDataType::Image" to clear all but the selected item/s of the Image type.
- L149 _private member_ `TSharedPtr<UE::Mutable::Private::FModel> MutableModel;` — Mutable object containing the constants data
- L152 _private member_ `TSharedPtr<SMutableCodeViewer> MutableCodeViewerPtr = nullptr;` — Slate capable of accessing the previewer object
- L158 _private prototype_ `void SetModel(const TSharedPtr<UE::Mutable::Private::FModel>& InModel);` — Sets the back end for the operation of this widget. Each time this is done the ui backend gets updated @param InProgram - Mutable program object holding all the constants data
- L164 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantMeshElement>>> ConstantMeshesSlate;`
- L165 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantStringElement>>> ConstantStringsSlate;`
- L166 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantLayoutElement>>> ConstantLayoutsSlate;`
- L167 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantProjectorElement>>> ConstantProjectorsSlate;`
- L168 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantMatrixElement>>> ConstantMatricesSlate;`
- L169 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantShapeElement>>> ConstantShapesSlate;`
- L170 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantCurveElement>>> ConstantCurvesSlate;`
- L171 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantSkeletonElement>>> ConstantSkeletonsSlate;`
- L172 _private member_ `TSharedPtr<STileView<TSharedPtr<FMutableConstantPhysicsElement>>> ConstantPhysicsSlate;`
- L178 _private member_ `TSharedPtr<SMutableMultiPageListView<TSharedPtr<FMutableConstantImageElement>>> ImageListViewHandler;`
- L179 _private member_ `TSharedPtr<TArray<TSharedPtr<FMutableConstantImageElement>>> ConstantImageElements;`
- L181 _private member_ `TSharedPtr<SMutableMultiPageListView<TSharedPtr<FMutableConstantMeshElement>>> MeshListViewHandler;`
- L182 _private member_ `TSharedPtr<TArray<TSharedPtr<FMutableConstantMeshElement>>> ConstantMeshElements;`
- L184 _private member_ `TSharedPtr<SMutableMultiPageListView<TSharedPtr<FMutableConstantMaterialElement>>> MaterialistViewHandler;`
- L185 _private member_ `TSharedPtr<TArray<TSharedPtr<FMutableConstantMaterialElement>>> ConstantMaterialElements;`
- L187 _private member_ `TArray<TSharedPtr<FMutableConstantStringElement>> ConstantStringElements;`
- L188 _private member_ `TArray<TSharedPtr<FMutableConstantLayoutElement>> ConstantLayoutElements;`
- L189 _private member_ `TArray<TSharedPtr<FMutableConstantProjectorElement>> ConstantProjectorElements;`
- L190 _private member_ `TArray<TSharedPtr<FMutableConstantMatrixElement>> ConstantMatrixElements;`
- L191 _private member_ `TArray<TSharedPtr<FMutableConstantShapeElement>> ConstantShapeElements;`
- L192 _private member_ `TArray<TSharedPtr<FMutableConstantCurveElement>> ConstantCurveElements;`
- L193 _private member_ `TArray<TSharedPtr<FMutableConstantSkeletonElement>> ConstantSkeletonElements;`
- L194 _private member_ `TArray<TSharedPtr<FMutableConstantPhysicsElement>> ConstantPhysicsElements;`
- L199 _private prototype_ `void LoadConstantElements();` — Load up all the elements with the data found on the UE::Mutable::Private::FProgram object onto TArrays after parsing the data found.
- L201 _private prototype_ `void LoadConstantStrings();`
- L202 _private prototype_ `void LoadConstantMeshes();`
- L203 _private prototype_ `void LoadConstantImages();`
- L204 _private prototype_ `void LoadConstantLayouts();`
- L205 _private prototype_ `void LoadConstantProjectors();`
- L206 _private prototype_ `void LoadConstantMatrices();`
- L207 _private prototype_ `void LoadConstantShapes();`
- L208 _private prototype_ `void LoadConstantCurves();`
- L209 _private prototype_ `void LoadConstantSkeletons();`
- L210 _private prototype_ `void LoadConstantPhysics();`
- L211 _private prototype_ `void LoadConstantMaterials();`
- L217 _private prototype_ `void OnSelectedStringChanged(TSharedPtr<FMutableConstantStringElement> MutableConstantStringElement, ESelectInfo::Type SelectionType) const;`
- L218 _private prototype_ `void OnSelectedImageChanged(TSharedPtr<FMutableConstantImageElement> MutableConstantImageElement, ESelectInfo::Type SelectionType) const;`
- L219 _private prototype_ `void OnSelectedMeshChanged(TSharedPtr<FMutableConstantMeshElement> MutableConstantMeshElement, ESelectInfo::Type SelectionType) const;`
- L220 _private prototype_ `void OnSelectedMaterialChanged(TSharedPtr<FMutableConstantMaterialElement> MutableConstantMaterialElement, ESelectInfo::Type SelectionType) const;`
- L221 _private prototype_ `void OnSelectedLayoutChanged(TSharedPtr<FMutableConstantLayoutElement> MutableConstantLayoutElement, ESelectInfo::Type SelectionType) const;`
- L222 _private prototype_ `void OnSelectedProjectorChanged(TSharedPtr<FMutableConstantProjectorElement> MutableConstantProjectorElement, ESelectInfo::Type SelectionType) const;`
- L223 _private prototype_ `void OnSelectedMatrixChanged(TSharedPtr<FMutableConstantMatrixElement> MutableConstantMatrixElement, ESelectInfo::Type SelectionType) const;`
- L224 _private prototype_ `void OnSelectedShapeChanged(TSharedPtr<FMutableConstantShapeElement> MutableConstantShapeElement, ESelectInfo::Type SelectionType) const;`
- L225 _private prototype_ `void OnSelectedCurveChanged(TSharedPtr<FMutableConstantCurveElement> MutableConstantCurveElement, ESelectInfo::Type SelectionType) const;`
- L226 _private prototype_ `void OnSelectedSkeletonChanged(TSharedPtr<FMutableConstantSkeletonElement> MutableConstantSkeletonElement, ESelectInfo::Type SelectionType) const;`
- L227 _private prototype_ `void OnSelectedPhysicsChanged(TSharedPtr<FMutableConstantPhysicsElement> MutableConstantPhysicsElement, ESelectInfo::Type SelectionType) const;`
- L233 _private prototype_ `TSharedRef<ITableRow> OnGenerateStringRow(TSharedPtr<FMutableConstantStringElement> MutableConstantStringElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L234 _private prototype_ `TSharedRef<ITableRow> OnGenerateImageRow(TSharedPtr<FMutableConstantImageElement> MutableConstantImageElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L235 _private prototype_ `TSharedRef<ITableRow> OnGenerateMeshRow(TSharedPtr<FMutableConstantMeshElement> MutableConstantMeshElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L236 _private prototype_ `TSharedRef<ITableRow> OnGenerateMaterialRow(TSharedPtr<FMutableConstantMaterialElement> MutableConstantMaterialElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L237 _private prototype_ `TSharedRef<ITableRow> OnGenerateLayoutRow(TSharedPtr<FMutableConstantLayoutElement> MutableConstantLayoutElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L238 _private prototype_ `TSharedRef<ITableRow> OnGenerateProjectorRow(TSharedPtr<FMutableConstantProjectorElement> MutableConstantProjectorElement, const TSharedRef<STableViewBase>& OwnerTable)const;`
- L239 _private prototype_ `TSharedRef<ITableRow> OnGenerateMatrixRow(TSharedPtr<FMutableConstantMatrixElement> MutableConstantMatrixElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L240 _private prototype_ `TSharedRef<ITableRow> OnGenerateShapeRow(TSharedPtr<FMutableConstantShapeElement> MutableConstantShapeElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L241 _private prototype_ `TSharedRef<ITableRow> OnGenerateCurveRow(TSharedPtr<FMutableConstantCurveElement> MutableConstantCurveElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L242 _private prototype_ `TSharedRef<ITableRow> OnGenerateSkeletonRow(TSharedPtr<FMutableConstantSkeletonElement> MutableConstantSkeletonElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L243 _private prototype_ `TSharedRef<ITableRow> OnGeneratePhysicsRow(TSharedPtr<FMutableConstantPhysicsElement> MutableConstantPhysicsElement, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L252 _private member_ `FName ImageConstantsLastSortedColumnID = "";` — Id of the last column the user decided to Sort. Usefully in order to interpolate ascending and descending sorting order
- L254 _private member_ `EColumnSortMode::Type ImageListSortMode = EColumnSortMode::Type::None;` — Variable holding what kind of sorting has been used on the last sorting operation
- L257 _private prototype_ `void OnImageTableSortRequested(EColumnSortPriority::Type ColumnSortPriority, const FName& ColumnID, EColumnSortMode::Type ColumnSortMode);` — Callback method designed to sort the list of images. It sorts ConstantImageElements
- L258 _private prototype_ `EColumnSortMode::Type GetImageListColumnSortMode(FName ColumnName) const;`
- L264 _private member_ `FName MeshConstantsLastSortedColumnID = "";`
- L265 _private member_ `EColumnSortMode::Type MeshListSortMode = EColumnSortMode::Type::None;`
- L267 _private prototype_ `void OnMeshTableSortRequested(EColumnSortPriority::Type ColumnSortPriority, const FName& ColumnID, EColumnSortMode::Type ColumnSortMode);`
- L268 _private prototype_ `EColumnSortMode::Type GetMeshListColumnSortMode(FName ColumnName) const;`
- L274 _private member_ `FName MaterialConstantsLastSortedColumnID = "";`
- L275 _private member_ `EColumnSortMode::Type MaterialListSortMode = EColumnSortMode::Type::None;`
- L277 _private prototype_ `void OnMaterialsTableSortRequested(EColumnSortPriority::Type ColumnSortPriority, const FName& ColumnID, EColumnSortMode::Type ColumnSortMode);`
- L278 _private prototype_ `EColumnSortMode::Type GetMaterialListColumnSortMode(FName ColumnName) const;`
- L286 _private member_ `TSharedPtr<SExpandableArea> StringsExpandableArea;` — Pointers to all expandable areas part of this slate
- L287 _private member_ `TSharedPtr<SExpandableArea> ImagesExpandableArea;`
- L288 _private member_ `TSharedPtr<SExpandableArea> MeshesExpandableArea;`
- L289 _private member_ `TSharedPtr<SExpandableArea> LayoutsExpandableArea;`
- L290 _private member_ `TSharedPtr<SExpandableArea> ProjectorsExpandableArea;`
- L291 _private member_ `TSharedPtr<SExpandableArea> MatricesExpandableArea;`
- L292 _private member_ `TSharedPtr<SExpandableArea> ShapesExpandableArea;`
- L293 _private member_ `TSharedPtr<SExpandableArea> CurvesExpandableArea;`
- L294 _private member_ `TSharedPtr<SExpandableArea> SkeletonsExpandableArea;`
- L295 _private member_ `TSharedPtr<SExpandableArea> PhysicsExpandableArea;`
- L296 _private member_ `TSharedPtr<SExpandableArea> MaterialsExpandableArea;`
- L299 _private member_ `TArray<TSharedPtr<SExpandableArea>> ExpandableAreas;` — Array with all expandable areas set on this object. Used for dynamic expansion/contraction
- L305 _private prototype_ `void OnStringsRegionExpansionChanged(bool bExpanded);`
- L306 _private prototype_ `void OnImagesRegionExpansionChanged(bool bExpanded);`
- L307 _private prototype_ `void OnMeshesRegionExpansionChanged(bool bExpanded);`
- L308 _private prototype_ `void OnLayoutsRegionExpansionChanged(bool bExpanded);`
- L309 _private prototype_ `void OnProjectorsRegionExpansionChanged(bool bExpanded);`
- L310 _private prototype_ `void OnMatricesRegionExpansionChanged(bool bExpanded);`
- L311 _private prototype_ `void OnShapesRegionExpansionChanged(bool bExpanded);`
- L312 _private prototype_ `void OnCurvesRegionExpansionChanged(bool bExpanded);`
- L313 _private prototype_ `void OnSkeletonsRegionExpansionChanged(bool bExpanded);`
- L314 _private prototype_ `void OnPhysicsRegionExpansionChanged(bool bExpanded);`
- L315 _private prototype_ `void OnMaterialsRegionExpansionChanged(bool bExpanded);`
- L320 _private prototype_ `void ContractExpandableAreas(const TSharedPtr<SExpandableArea>& InException);` — Method called each time one expandable area changes expansion state @param InException - Pointer to the expandable area that will not be contracted while all the others will
- L327 _private member_ `FText ConstantStringsFormattedSize;` — Sizes decomposed on GB, MB, KB and B
- L328 _private member_ `FText ConstantImagesFormattedSize;`
- L329 _private member_ `FText ConstantMeshesFormattedSize;`
- L330 _private member_ `FText ConstantLayoutsFormattedSize;`
- L331 _private member_ `FText ConstantProjectorsFormattedSize;`
- L332 _private member_ `FText ConstantMatricesFormattedSize;`
- L333 _private member_ `FText ConstantShapesFormattedSize;`
- L334 _private member_ `FText ConstantCurvesFormattedSize;`
- L335 _private member_ `FText ConstantSkeletonsFormattedSize;`
- L336 _private member_ `FText ConstantPhysicsFormattedSize;`
- L337 _private member_ `FText ConstantMaterialsFormattedSize;`
- L343 _private prototype_ `FText OnDrawStringsAreaTitle() const;`
- L344 _private prototype_ `FText OnDrawImagesAreaTitle() const;`
- L345 _private prototype_ `FText OnDrawMeshesAreaTitle() const;`
- L346 _private prototype_ `FText OnDrawLayoutsAreaTitle() const;`
- L347 _private prototype_ `FText OnDrawProjectorsAreaTitle() const;`
- L348 _private prototype_ `FText OnDrawMatricesAreaTitle() const;`
- L349 _private prototype_ `FText OnDrawShapesAreaTitle() const;`
- L350 _private prototype_ `FText OnDrawCurvesAreaTitle() const;`
- L351 _private prototype_ `FText OnDrawSkeletonsAreaTitle() const;`
- L352 _private prototype_ `FText OnDrawPhysicsAreaTitle() const;`
- L353 _private prototype_ `FText OnDrawMaterialsAreaTitle() const;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Mutable` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mutable` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Mutable` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableConstrainedBox.h` (Private)


#### class `SMutableConstrainedBox`  
`class SMutableConstrainedBox : public SCompoundWidget`  
_L10-28_
- inherits: `SCompoundWidget`
- desc: Helper class to force a widget to fill in a space. Copied from SConstrainedBox.h
- L13 _public function_ `SLATE_BEGIN_ARGS(SMutableConstrainedBox) : _MinWidth() , _MaxWidth()`
- L17 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(TOptional<float>, MinWidth) SLATE_ATTRIBUTE(TOptional<float>, MaxWidth) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L26 _private member_ `TAttribute< TOptional<float> > MinWidth;`
- L27 _private member_ `TAttribute< TOptional<float> > MaxWidth;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableCurveViewer.h` (Private)


#### class `FMutablePreviewerCurveModel`  
`class FMutablePreviewerCurveModel : public FCurveModel`  
_L27-92_
- inherits: `FCurveModel`
- desc: Custom curve model designed to be able to work with our mutable curve. The overriding of the FCurveModel methods is mandatory. @note Methods with // are methods whose operation is not required for our usage case at the moment. Refer to FCurveModel class to know more about them and the rest of methods that have been overriden.
- L31 _private member_ `TArray< FKeyHandle> KeyHandles;` — Cache the handles being added onto curve. Allows us to access them externally to the RichCurve
- L34 _private member_ `FRichCurve RichCurve;` — The curve object that will manage all the keys (time and value)
- L38 _public function_ `virtual const void* GetCurve() const override`
- L43 _public function_ `virtual void Modify() override`
- L46 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;` — Based on DrawCurve from RichCurveEditorModel.cpp
- L50 _public prototype_ `void RefineCurvePoints(const FRichCurve& InRichCurve, double TimeThreshold, float ValueThreshold, TArray<TTuple<double, double>>& InOutPoints) const;` — Based on RefineCurvePoints from RichCurveEditorModel.cpp
- L52 _public function_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override`
- L55 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L58 _public function_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override`
- L60 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L63 _public function_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override`
- L66 _public function_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override`
- L69 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L71 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L73 _public function_ `virtual int32 GetNumKeys() const override`
- L78 _public prototype_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override;`
- L81 _public function_ `virtual bool Evaluate(double InTime, double& OutValue) const override`
- L86 _public function_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override`
- L89 _public function_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType) override`

#### struct `FMutableCurveElement`  
`struct FMutableCurveElement`  
_L97-108_
- desc: Defines an element representing a keyframe of the mutable curve. Used by a ListView
- L99 _public function_ `FMutableCurveElement(const int32 InIndex,const FRichCurveKey& InCurveKeyFrame) : KeyFrameIndex(InIndex), CurveKeyFrame(InCurveKeyFrame)`
- L106 _public member_ `const int32 KeyFrameIndex;`
- L107 _public member_ `const FRichCurveKey& CurveKeyFrame;`

#### class `SMutableCurveViewer`  
`class SMutableCurveViewer final : public SCompoundWidget`  
_L114-177_
- inherits: `SCompoundWidget`
- desc: Object designed to be used as a way to inspect the data present on a Mutable Curve (UE::Mutable::Private::Curve)
- L116 _private function_ `SLATE_BEGIN_ARGS(SMutableCurveViewer)`
- L117 _private prototype_ `SLATE_ARGUMENT(FRichCurve, MutableCurve) ;`
- L125 _public prototype_ `void Construct(const FArguments& InArgs);` — Builds this slate with the assistance of the provided arguments @param InArgs - Input arguments used to provide this slate with the data required to operate
- L132 _public prototype_ `void SetCurve(const FRichCurve& InMutableCurve);` — Sets the curve object to be used as source for the data to be displayed in this slate @param InMutableCurve - Reference to a mutable curve object to be set as origin for the data displayed on this slate object
- L137 _private member_ `FRichCurve MutableCurve;` — Mutable curve to read the data from. It is the origin for all the data displayed on this slate object
- L146 _private member_ `TSharedPtr<FCurveEditor> CurveEditor = nullptr;` — Object designed to contain the curve to be displayed onto the SCurveEditorPanel. It serves as proxy to the curve being worked on and allows interaction with it.
- L149 _private member_ `TSharedPtr<SCurveEditorPanel> CurveEditorPanel = nullptr;` — Slate object with the visual representation of the curve held by FCurveEditor.
- L152 _private prototype_ `void SetupMutableCurveGraph() const;` — Loads the data found on the mutable curve onto our FMutablePreviewerCurveModel to be displayed
- L159 _private member_ `TSharedPtr<SListView<TSharedPtr<FMutableCurveElement>>> CurveListView;` — List View showing all the data found on the mutable curve
- L162 _private member_ `TArray<TSharedPtr<FMutableCurveElement>> CurveElements;` — Array with all the curve keyframes as Curve elements for the Table to be able to display them
- L167 _private prototype_ `void SetupMutableCurveListView();` — Store all the keyframe data found on the mutable curve onto the array of Curve Elements so the list view can properly display it.
- L176 _private prototype_ `TSharedRef<ITableRow> OnGenerateCurveTableRow(TSharedPtr<FMutableCurveElement> InElement, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback method invoked for each element on CurveElements. It generates for each of them a new slate object to represent each MutableCurveElement @param InElement - Element to process @param OwnerTable - The table object where it will be loaded onto (not explicitly in this method) @return The slate object representing InElement.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableGraphViewer.h` (Private)


#### class `SMutableGraphViewer`  
`class SMutableGraphViewer : public SCompoundWidget, public FGCObject`  
_L26-99_
- inherits: `SCompoundWidget,FGCObject`
- desc: This widget shows the internal Mutable Graph for debugging purposes. This is not the Unreal source graph in the UCustomizableObject, but an intermediate step of the compilation process.
- L33 _public function_ `SLATE_BEGIN_ARGS(SMutableGraphViewer)` — SWidget interface
- L35 _public prototype_ `SLATE_ARGUMENT(TArray<TSoftObjectPtr<const UTexture>>, ReferencedRuntimeTextures) SLATE_ARGUMENT(TArray<FMutableSourceTextureData>, ReferencedCompileTextures) SLATE_ARGUMENT(TArray<TSoftObjectPtr<const UStreamableRenderAsset>>, ReferencedRuntimeMeshes) SLATE_ARGUMENT(TArray<FMutableSourceMeshData>, ReferencedCompileMeshes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UE::Mutable::Private::NodePtr& InRootNode);`
- L45 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L46 _public prototype_ `virtual FString GetReferencerName() const override;`
- L50 _private member_ `UE::Mutable::Private::NodePtr RootNode;` — The Mutable Graph to show, represented by its root.
- L53 _private member_ `TArray<TSoftObjectPtr<const UTexture>> ReferencedRuntimeTextures;` — Array of external referenced textures in MutableModel, indexed by id.
- L54 _private member_ `TArray<FMutableSourceTextureData> ReferencedCompileTextures;`
- L57 _private member_ `TSharedRef<FCustomizableObjectCompiler> Compiler = MakeShared<FCustomizableObjectCompiler>();` — Object compiler.
- L60 _private member_ `TArray<TSharedPtr<FMutableGraphTreeElement>> RootNodes;` — Root nodes of the tree widget.
- L63 _private member_ `TSharedPtr<STreeView<TSharedPtr<FMutableGraphTreeElement>>> TreeView;` — Tree showing the graph.
- L74 _private function_ `friend FORCEINLINE bool operator == (const FItemCacheKey& A, const FItemCacheKey& B)`
- L79 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FItemCacheKey& Key)`
- L84 _private member_ `TMap< FItemCacheKey, TSharedPtr<FMutableGraphTreeElement>> ItemCache;`
- L87 _private member_ `TMap< const UE::Mutable::Private::Node*, TSharedPtr<FMutableGraphTreeElement>> MainItemPerNode;` — Main tree item for each node. A graph node can be representes with multiple tree ndoes if it is reachable from different paths.
- L90 _private prototype_ `void RebuildTree();`
- L93 _private prototype_ `TSharedRef<ITableRow> GenerateRowForNodeTree(TSharedPtr<FMutableGraphTreeElement> InTreeNode, const TSharedRef<STableViewBase>& InOwnerTable);` — Callbacks from the tree widget.
- L94 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FMutableGraphTreeElement> InInfo, TArray< TSharedPtr<FMutableGraphTreeElement> >& OutChildren);`
- L95 _private prototype_ `TSharedPtr<SWidget> OnTreeContextMenuOpening();`
- L96 _private prototype_ `void TreeExpandRecursive(TSharedPtr<FMutableGraphTreeElement> Info, bool bExpand);`
- L97 _private prototype_ `void TreeExpandUnique();`

#### struct `SMutableGraphViewer::FItemCacheKey`  
`struct FItemCacheKey`  
_L68-83_
- desc: Cache of tree elements matching the graph nodes that have been generated so far. We store both the parent and the node in the key, because a single node may appear multiple times if it has different parents.
- L70 _public member_ `const UE::Mutable::Private::Node* Parent = nullptr;`
- L71 _public member_ `const UE::Mutable::Private::Node* Child = nullptr;`
- L72 _public member_ `uint32 ChildIndexInParent = 0;`

#### class `FMutableGraphTreeElement`  
`class FMutableGraphTreeElement : public TSharedFromThis<FMutableGraphTreeElement>`  
_L103-126_
- inherits: `TSharedFromThis<FMutableGraphTreeElement>`
- desc: An row of the code tree in the SMutableGraphViewer.
- L106 _public function_ `FMutableGraphTreeElement(const UE::Mutable::Private::NodePtr& InNode, TSharedPtr<FMutableGraphTreeElement>* InDuplicatedOf=nullptr, const FString& InPrefix=FString() )`
- L119 _public member_ `UE::Mutable::Private::NodePtr MutableNode;` — Mutable Graph Node represented in this tree row.
- L122 _public member_ `TSharedPtr<FMutableGraphTreeElement> DuplicatedOf;` — If this tree element is a duplicated of another node, this is the node.
- L125 _public member_ `FString Prefix;` — Optional label prefix

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableImageViewer.h` (Private)


#### enum `EMutableImageChannels`  
`enum class EMutableImageChannels : uint8`  
_L20-28_
- desc: Describes different modes to show an image.
- L22 _public enumerator_ `RGBA`
- L23 _public enumerator_ `RGB`
- L24 _public enumerator_ `R`
- L25 _public enumerator_ `G`
- L26 _public enumerator_ `B`
- L27 _public enumerator_ `A`

#### class `SSimpleTextureViewer`  
`class SSimpleTextureViewer : public SCompoundWidget, public FGCObject`  
_L32-70_
- inherits: `SCompoundWidget,FGCObject`
- desc: Simple widget that shows a UTexture.
- L36 _public function_ `SLATE_BEGIN_ARGS(SSimpleTextureViewer)`
- L37 _public function_ `SLATE_ATTRIBUTE(FIntPoint, GridSize) SLATE_ARGUMENT_DEFAULT(UTexture*, Texture)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L44 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidgetInterface
- L45 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L48 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L49 _public prototype_ `virtual FString GetReferencerName() const override;`
- L54 _public prototype_ `void SetTexture(UTexture* InTexture);` — Set the image to show in the widget.
- L57 _public member_ `EMutableImageChannels ImageChannels = EMutableImageChannels::RGBA;`
- L62 _private member_ `TObjectPtr<UTexture> Texture;` — Reference to the texture.
- L65 _private member_ `TSharedPtr<FSlateBrush> TextureBrush;` — Brush used to render the image.
- L68 _private member_ `TAttribute<FIntPoint> GridSize;` — Size of the underlying rendered grid.

#### class `SMutableImageViewer`  
`class SMutableImageViewer : public SCompoundWidget`  
_L74-119_
- inherits: `SCompoundWidget`
- desc: Widget showing a Mutable image, with its properties.
- L79 _public function_ `SLATE_BEGIN_ARGS(SMutableImageViewer)`
- L80 _public prototype_ `SLATE_ATTRIBUTE(FIntPoint, GridSize) SLATE_ARGUMENT(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage>, Image) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L87 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L92 _public prototype_ `void SetImage(const UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage>& Image, int32 VisibleLOD );` — Set the image to show in the widget.
- L97 _private member_ `TSharedPtr<SSimpleTextureViewer> TextureViewer;` — Brush used to render the image.
- L100 _private member_ `TAttribute<FIntPoint> GridSize;` — Size of the underlying rendered grid.
- L103 _private member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> MutableImage;`
- L106 _private member_ `int32 CurrentVisibleLOD=0;` — Mipmap shown in the widget. 0 is the biggest one.
- L109 _private member_ `bool bIsPendingUpdate = false;` — Is true, the image or the visible LOD have changed and we need to update.
- L112 _private prototype_ `FText GetImageDescriptionLabel() const;` — User interface callbacks
- L113 _private prototype_ `TOptional<int32> GetCurrentImageLOD() const;`
- L114 _private prototype_ `TOptional<int32> GetImageLODMaxValue() const;`
- L115 _private prototype_ `EVisibility IsLODSelectionVisible() const;`
- L116 _private prototype_ `void OnCurrentLODChanged(int32 NewValue);`
- L117 _private prototype_ `EMutableImageChannels GetImageChannels() const;`
- L118 _private prototype_ `void SetImageChannels(EMutableImageChannels);`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableIntViewer.h` (Private)


#### class `SMutableIntViewer`  
`class SMutableIntViewer : public SCompoundWidget`  
_L10-32_
- inherits: `SCompoundWidget`
- desc: Mutable viewer to show a representation of an int variable held by mutable.
- L13 _public function_ `SLATE_BEGIN_ARGS(SMutableIntViewer)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `void SetInt(const int32& InInt);` — Set the Mutable Bool to be used for this widget
- L25 _private member_ `int32 IntValue;` — The value that is being displayed by the UI
- L31 _private prototype_ `FText GetValue() const;` — Callback for udpating the widget UI @return The value stored on IntValue as a FText

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableLayoutViewer.h` (Private)


#### class `SMutableLayoutViewer`  
`class SMutableLayoutViewer : public SCompoundWidget`  
_L13-46_
- inherits: `SCompoundWidget`
- desc: Widget showing a Mutable layout, with its properties.
- L18 _public function_ `SLATE_BEGIN_ARGS(SMutableLayoutViewer)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(FIntPoint, GridSize) SLATE_ARGUMENT(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FLayout>, Layout) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L31 _public prototype_ `void SetLayout(const UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FLayout>& Image );` — Set the image to show in the widget.
- L36 _private member_ `TSharedPtr<SCustomizableObjectLayoutGrid> LayoutViewer;` — Brush used to render the layout.
- L39 _private member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FLayout> MutableLayout;` — Mutable Layout object being previewed
- L42 _private member_ `bool bIsPendingUpdate = false;` — Is true, the image or the visible LOD have changed and we need to update.
- L45 _private prototype_ `FText GetLayoutDescriptionLabel() const;` — User interface callbacks

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableMaterialViewer.h` (Private)


#### struct `FMutableMaterialParameterListElement`  
`struct FMutableMaterialParameterListElement`  
_L12-17_
- desc: Base for all parameter types
- L14 _public member_ `FName ParameterName;`
- L15 _public member_ `int32 Index = -1;`
- L16 _public member_ `int32 LayerIndex = -1;`

#### struct `FMutableMaterialImageParameterElement`  
`struct FMutableMaterialImageParameterElement : public FMutableMaterialParameterListElement`  
_L20-23_
- inherits: `FMutableMaterialParameterListElement`
- L22 _public member_ `UE::Mutable::Private::FMaterial::FImageParameterData Value;` — !

#### struct `FMutableMaterialColorParameterElement`  
`struct FMutableMaterialColorParameterElement : public FMutableMaterialParameterListElement`  
_L26-29_
- inherits: `FMutableMaterialParameterListElement`
- L28 _public member_ `FVector4f Value;`

#### struct `FMutableMaterialScalarParameterElement`  
`struct FMutableMaterialScalarParameterElement : public FMutableMaterialParameterListElement`  
_L32-35_
- inherits: `FMutableMaterialParameterListElement`
- L34 _public member_ `float Value;`

#### class `SMutableMaterialViewer`  
`class SMutableMaterialViewer : public SCompoundWidget`  
_L41-90_
- inherits: `SCompoundWidget`
- desc: Widget designed to show the statistical data from a Mutable FMaterial
- L44 _public function_ `SLATE_BEGIN_ARGS(SMutableMaterialViewer)`
- L45 _public function_ `SLATE_ARGUMENT_DEFAULT(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMaterial>, Material)`
- L46 _public function_ `SLATE_ARGUMENT_DEFAULT(TWeakPtr<SMutableCodeViewer>, HostCodeViewer)`
- L47 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L53 _public prototype_ `void SetMaterial(const UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMaterial>& InMaterial);` — Set the Mutable Material to be used for this widget
- L57 _private prototype_ `TSharedRef<SWidget> GeneratePassthroughMaterialWidget();`
- L64 _private prototype_ `void OnMaterialNavigation() const;` — Callback method called when the material link is pressed. Will open the editor for the provided material
- L66 _private prototype_ `FText GetImageParametersCountAsText() const;`
- L67 _private prototype_ `FText GetColorParametersCountAsText() const;`
- L68 _private prototype_ `FText GetScalarParametersCountAsText() const;`
- L70 _private prototype_ `TSharedRef<ITableRow> OnGenerateImageParameterRow(TSharedPtr<FMutableMaterialImageParameterElement> MutableMaterialImageParameterElement, const TSharedRef<STableViewBase>& Shared) const;`
- L71 _private prototype_ `TSharedRef<ITableRow> OnGenerateColorParameterRow(TSharedPtr<FMutableMaterialColorParameterElement> MutableMaterialColorParameterElement, const TSharedRef<STableViewBase>& Shared) const;`
- L72 _private prototype_ `TSharedRef<ITableRow> OnGenerateScalarParameterRow(TSharedPtr<FMutableMaterialScalarParameterElement> MutableMaterialScalarParameterElement, const TSharedRef<STableViewBase>& Shared) const;`
- L75 _private member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMaterial> HostedMaterial;` — The material we are showing some data of
- L77 _private member_ `TWeakPtr<SMutableCodeViewer> MutableCodeViewer;`
- L79 _private member_ `TSharedPtr<SBox> PreviewContainer;`
- L82 _private member_ `TArray<TSharedPtr<FMutableMaterialImageParameterElement>> ImageParameters;` — Backend of the parameter list views. Extracted from the provided Hosted Material
- L83 _private member_ `TArray<TSharedPtr<FMutableMaterialColorParameterElement>> ColorParameters;`
- L84 _private member_ `TArray<TSharedPtr<FMutableMaterialScalarParameterElement>> ScalarParameters;`
- L87 _private member_ `TSharedPtr<SListView<TSharedPtr<FMutableMaterialImageParameterElement>>> ImageParameterListView;` — Lists
- L88 _private member_ `TSharedPtr<SListView<TSharedPtr<FMutableMaterialColorParameterElement>>> ColorParameterListView;`
- L89 _private member_ `TSharedPtr<SListView<TSharedPtr<FMutableMaterialScalarParameterElement>>> ScalarParameterListView;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableMeshViewer.h` (Private)


#### struct `FBufferChannelElement`  
`struct FBufferChannelElement`  
_L26-32_
- desc: Container designed to hold the buffer channel data of a mutable mesh buffer to be later used by the UI
- L28 _public member_ `FText SemanticIndex;`
- L29 _public member_ `FText BufferSemantic;`
- L30 _public member_ `FText BufferFormat;`
- L31 _public member_ `FText BufferComponentCount;`

#### struct `FBufferElement`  
`struct FBufferElement`  
_L36-43_
- desc: Element representing a mutable buffer. It contains an array with all the elements representing the channels the mutable buffer is made of.
- L39 _public member_ `FText BufferIndex;` — The index of the buffer on the origin mutable buffer set
- L42 _public member_ `TSharedPtr<TArray<TSharedPtr<FBufferChannelElement>>> BufferChannels;` — An array of BufferChannels that represent the relative mutable channels on the mutable buffer

#### class `SMutableMeshViewer`  
`class SMutableMeshViewer : public SCompoundWidget`  
_L46-168_
- inherits: `SCompoundWidget`
- desc: Widget designed to show the statistical data from a Mutable FMesh
- L49 _public function_ `SLATE_BEGIN_ARGS(SMutableMeshViewer)`
- L50 _public function_ `SLATE_ARGUMENT_DEFAULT(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh>, Mesh)`
- L51 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L57 _public prototype_ `void SetMesh(const UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh>& InMesh);` — Set the Mutable Mesh to be used for this widget
- L64 _public prototype_ `TSharedRef<SWidget> GenerateBufferChannelsListView( const TSharedPtr<TArray<TSharedPtr<FBufferChannelElement>>>& InBufferChannelElements);` — Generate a new SListView for all the ChannelElements provided. @param InBufferChannelElements - List with all the elements that will be ued to fill InHostListView @return A SListView containing all the channel elements as UI elements.
- L70 _private member_ `TSharedPtr<SMutableSkeletonViewer> MutableSkeletonViewer;` — Slate whose task is to display the skeleton found on this mesh as a slate tree view
- L72 _private prototype_ `TSharedRef<ITableRow> GenerateTagRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L75 _private member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh> MutableMesh = nullptr;` — Data backend for the widget. It represents the mesh that is being "displayed"
- L78 _private member_ `TSharedPtr<SSplitter> SpaceSplitter;` — Splitter used to separate the two sides of the slate (tables and viewport)
- L81 _private member_ `TSharedPtr<SScrollBox> DataSpaceSlate;` — Slate object containing all the buffer tables alongside with the bone tree
- L84 _private member_ `TSharedPtr<SMutableMeshViewport> MeshViewport;` — Viewport object to preview the current mesh inside an actual Unreal scene
- L91 _private member_ `TSharedPtr<SListView<TSharedPtr<FBufferElement>>> VertexBuffersSlateView;`
- L92 _private member_ `TSharedPtr<SListView<TSharedPtr<FBufferElement>>> IndexBuffersSlateView;`
- L95 _private member_ `TSharedPtr<SCustomizableObjectLayoutGrid> LayoutGridWidget;` — Widget to show the UVs
- L100 _private prototype_ `TSharedRef<SWidget> GenerateViewportSlates();` — Generates all slate objects related with the Mesh Viewport Slate
- L103 _private prototype_ `TSharedRef<SWidget> GenerateDataTableSlates();` — Generates the tables showing the buffer data on the mesh alongside with the bone tree found on the mutable mesh
- L106 _private prototype_ `void OnMeshChanged();` — Method called each time the mesh selected changes so the UI gets updated reliably
- L109 _private prototype_ `FIntPoint GetGridSize() const;` — UV widget callbacks.
- L110 _private prototype_ `TArray<FCustomizableObjectLayoutBlock> GetBlocks() const;`
- L111 _private prototype_ `TArray<FVector2f> GetUVs() const;`
- L116 _private prototype_ `FText GetVertexCount() const;` — Generic UI callbacks used by the Widget
- L117 _private prototype_ `FText GetFaceCount() const;`
- L118 _private prototype_ `FText GetBoneCount() const;`
- L119 _private prototype_ `FText GetMeshIdPrefix() const;`
- L120 _private prototype_ `FText GetMeshFlags() const;`
- L126 _private member_ `TArray<TSharedPtr<FBufferElement>> VertexBuffers;`
- L127 _private member_ `TArray<TSharedPtr<FBufferElement>> IndexBuffers;`
- L135 _private prototype_ `void FillTargetBufferSetDataArray(const UE::Mutable::Private::FMeshBufferSet& InMuMeshBufferSetPtr, TArray<TSharedPtr<FBufferElement>>& OutBuffersDataArray, TSharedPtr<SListView<TSharedPtr<FBufferElement>>>& InHostListView);` — Fills the provided TArray with the buffer definitions generated from the mutable buffers found on the provided mutable buffer set @param InMuMeshBufferSetPtr - Mutable buffer set pointer pointing to the buffer set witch buffer data is wanted to be saved on the provided TArray @param OutBuffersDataArray - TArray witch will contain the parsed data from the provided mutable buffer set converted onto FBufferElements @param InHostListView - The slate list using the previously referenced array as data backend.
- L147 _private prototype_ `TSharedRef<SWidget> GenerateBuffersListView(TSharedPtr<SListView<TSharedPtr<FBufferElement>>>& OutHostListView, const TArray<TSharedPtr<FBufferElement>>& InBufferElements, const FText& InBufferSetTypeName);` — Provided an array of buffer elements and the type of buffer it generates a new SListView for said buffer elements @param InBufferElements - The FBufferElement objects to be used as backend for the SListView @param InBufferSetTypeName - The name of the buffer set you are generating. Some examples are "Vertex", "index" or "Face" @param OutHostListView - THe SListView generated. @return - A shared reference to the SListView generated. Required by this slate operation.
- L156 _private prototype_ `TSharedRef<ITableRow> OnGenerateBufferRow(TSharedPtr<FBufferElement, ESPMode::ThreadSafe> InBuffer, const TSharedRef<STableViewBase, ESPMode::ThreadSafe>& OwnerTable);` — Callback method invoked each time a new row of the SListView containing the buffer elements needs to be built @param InBuffer - The buffer element being used to build the new row. @param OwnerTable - The table that is going to get the new row added into it. @return The new row object as the base interface used for all the table rows
- L165 _private prototype_ `TSharedRef<ITableRow> OnGenerateBufferChannelRow(TSharedPtr<FBufferChannelElement> InBufferChannel, const TSharedRef<STableViewBase>& OwnerTable);` — Callback Method responsible of generating each row of the buffer channel lists based on the channel definition provided. @param InBufferChannel - The mesh Buffer channel definition that is being used as blueprint for the actual UI row @param OwnerTable - The parent UI element that is going to be expanded with the new row object @return The new row object as the base interface used for all the table rows

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mutable` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableMeshViewport.h` (Private)


#### class `SMutableMeshViewport`  
`class SMutableMeshViewport : public SEditorViewport , public FGCObject`  
_L22-87_
- inherits: `SEditorViewport,FGCObject`
- desc: Object with the objective of showing a preview of a selected mutable mesh. It is designed to have few dependencies as possible
- L24 _private function_ `SLATE_BEGIN_ARGS(SMutableMeshViewport)`
- L25 _private function_ `SLATE_ARGUMENT_DEFAULT(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh>, Mesh)`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);` — Builds the widget
- L35 _public prototype_ `void SetMesh(const UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh>& InMesh);` — Set the Mutable Mesh to be used for this widget @param InMesh - The mutable mesh to be displayed
- L38 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L39 _public function_ `virtual FString GetReferencerName() const override`
- L45 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L50 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface (called by SEditorViewport::Construct)
- L55 _private member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh> MutableMesh = nullptr;` — The mutable mesh being displayed
- L62 _private member_ `TSharedPtr<FAdvancedPreviewScene> PreviewScene = nullptr;` — The preview scene that we are viewing
- L65 _private member_ `TSharedPtr<FMutableMeshViewportClient> ViewportClient = nullptr;` — Editor viewport client
- L68 _private prototype_ `void ClearViewport() const;` — Restores the default state for the viewport
- L71 _private prototype_ `void SendMeshToViewport();` — Adds the required content to the viewport
- L74 _private prototype_ `void RefreshViewportContents();` — Clears or displays a mesh depending on the presence of a mutable mesh on MutableMesh
- L81 _private member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;` — Mutable mesh converted into a Unreal mesh object
- L86 _private prototype_ `bool GenerateUnrealMesh();` — Generates a new USkeletalMesh from the MutableMesh set on this object @return - If the operation was able to be processed or not

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableProjectorViewer.h` (Private)


#### class `SMutableProjectorViewer`  
`class SMutableProjectorViewer final : public SCompoundWidget`  
_L11-82_
- inherits: `SCompoundWidget`
- L13 _private function_ `SLATE_BEGIN_ARGS(SMutableProjectorViewer)`
- L14 _private prototype_ `SLATE_ARGUMENT(UE::Mutable::Private::FProjector,MutableProjector);`
- L23 _public prototype_ `void Construct(const FArguments& InArgs);` — Builds this slate with the assistance of the provided arguments @param InArgs - Input arguments used to provide this slate with the data required to operate
- L29 _public prototype_ `void SetProjector(const UE::Mutable::Private::FProjector& InMutableProjector);` — Sets the projector object whose data we want to inspect @param InMutableProjector - Projector we desire to inspect. It is the origin of the data shown on the UI
- L34 _private member_ `UE::Mutable::Private::FProjector MutableProjector;` — The mutable projector witch data is being exposed on the UI
- L40 _private prototype_ `TOptional<float> GetProjectorPositionComponent(int32 VectorComponentIndex) const;` — Get the float corresponding to the position of the projector on the targeted component index @param VectorComponentIndex - Determines if you get the X, Y or Z value from the vector (0,1 and 2) @return The value corresponding to the index provided.
- L46 _private prototype_ `TOptional<float> GetProjectorDirectionComponent(int32 VectorComponentIndex) const;` — Get the float corresponding to the direction vector of the projector on the targeted component index @param VectorComponentIndex - Determines if you get the X, Y or Z value from the vector (0,1 and 2) @return The value corresponding to the index provided.
- L52 _private prototype_ `TOptional<float> GetProjectorScaleComponent(int32 VectorComponentIndex) const;` — Get the float corresponding to the scale vector of the projector on the targeted component index @param VectorComponentIndex - Determines if you get the X, Y or Z value from the vector (0,1 and 2) @return The value corresponding to the index provided.
- L58 _private prototype_ `TOptional<float> GetProjectorUpComponent(int32 VectorComponentIndex) const;` — Get the float corresponding to the up vector of the projector on the targeted component index @param VectorComponentIndex - Determines if you get the X, Y or Z value from the vector (0,1 and 2) @return The value corresponding to the index provided.
- L63 _private prototype_ `float GetProjectorAngle() const;` — Get the angle of the projector object @return The angle of the projector. 0 if no projector is set.
- L69 _private prototype_ `FText GetProjectorAngleAsText() const;` — Gets the angle of the projector so a STextBlock is able to display it @return The angle as an FText
- L75 _private prototype_ `UE::Mutable::Private::EProjectorType GetProjectorType() const;` — It accesses the set projector and returns the type of it. @return - The projector type.
- L81 _private prototype_ `FText GetProjectorTypeAsText() const;` — Provides the UI with the mutable type in a format it can display on an STextBlock @return - The projector type as an FText

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableScalarViewer.h` (Private)


#### class `SMutableScalarViewer`  
`class SMutableScalarViewer : public SCompoundWidget`  
_L11-33_
- inherits: `SCompoundWidget`
- desc: Mutable viewer to show a representation of an scalar variable held by mutable.
- L14 _public function_ `SLATE_BEGIN_ARGS(SMutableScalarViewer)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetScalar(const float& InFloat);` — Set the Mutable Bool to be used for this widget
- L26 _private member_ `float ScalarValue;` — The value being displayed by the widget's UI
- L32 _private prototype_ `FText GetValue() const;` — Callback used by the widget to get the value to display on the UI @return The variable ScalarValue as an FText

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableScrubPanel.h` (Private)


#### class `SMutableScrubPanel`  
`class SMutableScrubPanel : public SCompoundWidget`  
_L23-92_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SMutableScrubPanel) : _LockedSequence()`
- L27 _public prototype_ `SLATE_ARGUMENT(UAnimSequenceBase*, LockedSequence) SLATE_ARGUMENT(bool, bDisplayAnimScrubBarEditing) SLATE_EVENT(FOnSetInputViewRange, OnSetInputViewRange) SLATE_ARGUMENT(bool, bAllowZoom) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FCustomizableObjectEditorViewportClient>& InPreviewScene);`
- L36 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L39 _private prototype_ `float GetViewMinInput() const;`
- L41 _private prototype_ `float GetViewMaxInput() const;`
- L43 _private prototype_ `FReply OnClick_Forward_Step();`
- L45 _private prototype_ `FReply OnClick_Forward_End();`
- L47 _private prototype_ `FReply OnClick_Backward_Step();`
- L49 _private prototype_ `FReply OnClick_Backward_End();`
- L51 _private prototype_ `FReply OnClick_Forward();`
- L53 _private prototype_ `FReply OnClick_Backward();`
- L55 _private prototype_ `FReply OnClick_ToggleLoop();`
- L57 _private prototype_ `void OnValueChanged(float NewValue);`
- L59 _private prototype_ `void OnReZeroAnimSequence(int32 FrameIndex);`
- L61 _private prototype_ `void OnBeginSliderMovement();`
- L63 _private prototype_ `void OnEndSliderMovement(float NewValue);`
- L65 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L67 _private prototype_ `bool IsLoopStatusOn() const;`
- L69 _private prototype_ `bool IsRealtimeStreamingMode() const;`
- L71 _private prototype_ `float GetScrubValue() const;`
- L73 _private prototype_ `UAnimSingleNodeInstance* GetPreviewInstance(UDebugSkelMeshComponent* PreviewMeshComponent) const;`
- L75 _private member_ `TSharedPtr<SScrubControlPanel> ScrubControlPanel;`
- L77 _private prototype_ `uint32 GetNumberOfKeys() const;`
- L79 _private prototype_ `float GetSequenceLength() const;`
- L81 _private prototype_ `bool GetAnimBlueprintDebugData(UAnimInstance*& Instance, FAnimBlueprintDebugData*& DebugInfo) const;`
- L83 _private prototype_ `TSharedRef<FCustomizableObjectEditorViewportClient> GetPreviewScene() const;`
- L85 _private prototype_ `bool GetDisplayDrag() const;`
- L87 _private member_ `TWeakPtr<FCustomizableObjectEditorViewportClient> PreviewScenePtr;`
- L89 _private member_ `FOnSetInputViewRange OnSetInputViewRange;`
- L91 _private member_ `bool bSliderBeingDragged = false;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableSearchComboBox.h` (Private)


#### class `SMutableSearchComboBox`  
`class SMutableSearchComboBox : public SComboButton`  
_L19-146_
- inherits: `SComboButton`
- L31 _public typedef_ `typedef STreeView< TSharedRef<FFilteredOption> > SComboTreeType;` — Type of list used for showing menu options.
- L34 _public typedef_ `typedef typename TSlateDelegates< TSharedRef<FString> >::FOnGenerateWidget FOnGenerateWidget;` — Delegate type used to generate widgets that represent Options
- L36 _public function_ `SLATE_BEGIN_ARGS(SMutableSearchComboBox) : _Content() , _ComboBoxStyle(&FAppStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox")) , _ButtonStyle(nullptr) , _ItemStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row")) , _ContentPadding(_ComboBoxStyle->ContentPadding) , _ForegroundColor(FSlateColor::UseStyle()) , _OptionsSource() , _OnSelectionChanged() , _MenuButtonBrush(nullptr) , _Method() , _AllowAddNewOptions(false) , _MaxListHeight(450.0f) , _SearchVisibility()`
- L53 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FSlateColor, ForegroundColor) SLATE_ARGUMENT(const TArray< TSharedRef<FFilteredOption> >*, OptionsSource) SLATE_EVENT(FOnTextChanged, OnSelectionChanged) SLATE_ARGUMENT(const FSlateBrush*, MenuButtonBrush) SLATE_ARGUMENT(TOptional<EPopupMethod>, Method) SLATE_ARGUMENT(bool, AllowAddNewOptions) SLATE_ARGUMENT(float, MaxListHeight) SLATE_ATTRIBUTE(EVisibility, SearchVisibility) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this button's content (optional)
- L92 _public prototype_ `void RefreshOptions();` — Requests a list refresh after updating options
- L97 _private prototype_ `TSharedRef<ITableRow> GenerateMenuItemRow(TSharedRef<FFilteredOption> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row for the InItem in the combo box's list (passed in as OwnerTable). Do this by calling the user-specified OnGenerateWidget
- L100 _private prototype_ `void OnGetChildren(TSharedRef<FFilteredOption> InItem, TArray<TSharedRef<FFilteredOption>>& OutChildren);`
- L103 _private prototype_ `void OnMenuOpenChanged(bool bOpen);` — Called if the menu is closed
- L106 _private prototype_ `void OnSelectionChanged_Internal(TSharedPtr<FFilteredOption> ProposedSelection, ESelectInfo::Type SelectInfo);` — Invoked when the selection in the list changes
- L109 _private prototype_ `void OnSearchTextChanged(const FText& ChangedText);` — Invoked when the search text changes
- L112 _private prototype_ `void OnSearchTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Sets the current selection to the first valid match when user presses enter in the filter box
- L114 _private prototype_ `FReply OnKeyDownHandler(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L117 _private member_ `const FTableRowStyle* ItemStyle;` — The item style to use.
- L120 _private member_ `FMargin MenuRowPadding;` — The padding around each menu row
- L124 _private member_ `FOnTextChanged OnSelectionChanged;` — Delegate that is invoked when the selected item in the combo box changes
- L126 _private member_ `TSharedPtr<SEditableTextBox> SearchField;` — The search field used for the combox box's contents
- L128 _private member_ `TSharedPtr< SComboTreeType > ComboTreeView;` — The ListView that we pop up; visualized the available options.
- L130 _private member_ `TSharedPtr< SScrollBar > CustomScrollbar;` — The Scrollbar used in the ListView.
- L133 _private member_ `FText SearchText;` — Updated whenever search text is changed
- L136 _private member_ `const TArray< TSharedRef<FFilteredOption> >* OptionsSource;` — Source data for this combo box
- L139 _private member_ `TArray< TSharedRef<FFilteredOption> > FilteredOptionsSource;` — Filtered list that is actually displayed
- L140 _private member_ `TArray< TSharedRef<FFilteredOption> > FilteredRootOptionsSource;`
- L143 _private member_ `FComboButtonStyle OurComboButtonStyle;` — Copied to replace the image.
- L145 _private member_ `bool bAllowAddNewOptions = false;`

#### struct `SMutableSearchComboBox::FFilteredOption`  
`struct FFilteredOption`  
_L22-28_
- L24 _public member_ `FString ActualOption;`
- L25 _public member_ `FString DisplayOption;`
- L27 _public member_ `TSharedPtr<FFilteredOption> Parent;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableSkeletonViewer.h` (Private)


#### struct `FBoneDefinition`  
`struct FBoneDefinition`  
_L14-21_
- desc: Container with the information required to generate the tree of bones
- L16 _public member_ `FName ParentBoneName = FName("");`
- L17 _public member_ `int32 ParentBoneIndex = INDEX_NONE;`
- L19 _public member_ `FName BoneName = FName("");`
- L20 _public member_ `int32 BoneIndex = INDEX_NONE;`

#### class `SMutableSkeletonViewer`  
`class SMutableSkeletonViewer : public SCompoundWidget`  
_L24-72_
- inherits: `SCompoundWidget`
- desc: Object responsible of showing with a tree view slate the bones present on the provided mutable skeleton
- L26 _private function_ `SLATE_BEGIN_ARGS(SMutableSkeletonViewer)`
- L27 _private function_ `SLATE_ARGUMENT_DEFAULT(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FSkeleton>, Skeleton)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);` — Builds the widget
- L35 _public prototype_ `void SetSkeleton(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FSkeleton> InSkeleton);` — Sets the mutable skeleton object to be inspected
- L41 _private member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FSkeleton> Skeleton;` — The mutable skeleton whose data is being inspected
- L44 _private member_ `TArray<TSharedPtr<FBoneDefinition>> RootBones;` — Bones data: Bone definitions used to generate the bone tree structure
- L45 _private member_ `TArray<TSharedPtr< FBoneDefinition>> ChildBones;`
- L48 _private member_ `TSharedPtr<STreeView<TSharedPtr<FBoneDefinition>>> BoneTree;` — UI Tree showing the bone data
- L51 _private prototype_ `void FillBoneDefinitionArrays();` — Fills the bone TArrays that hold the root and child bone definitions
- L59 _private prototype_ `TSharedRef<ITableRow> OnGenerateBoneTreeRow(TSharedPtr<FBoneDefinition> InBone, const TSharedRef<STableViewBase>& OwnerTable) const;` — Method responsible of generating each row for the tree of bones @param InBone - The mesh bone definition that is being used as blueprint for the actual UI row @param OwnerTable - The parent UI element that is going to be expanded with the new row object @return The new row object as the base interface used for all the table rows
- L67 _private prototype_ `void OnGetChildrenFromBoneDefinition(TSharedPtr<FBoneDefinition> InBone, TArray<TSharedPtr<FBoneDefinition>>& OutChildrenBones);` — Fills the parameter OutChildrenBones with all the child bones from a selected Bone @param InBone - The mesh bone definition that is being used as blueprint for the actual UI row @param OutChildrenBones - An array that end up holding all the bone definitions that are children of the InBone. It can end up being empty if no children bones are found for the InBone provided.
- L70 _private prototype_ `void ExpandFullBoneTree();` — Sets all rows of the tree as expanded

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableStringViewer.h` (Private)


#### class `SMutableStringViewer`  
`class SMutableStringViewer : public SCompoundWidget`  
_L10-33_
- inherits: `SCompoundWidget`
- desc: Widget designed to display the value of a string.
- L13 _public function_ `SLATE_BEGIN_ARGS(SMutableStringViewer)`
- L14 _public prototype_ `SLATE_ATTRIBUTE(FText, DefaultText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetString(const FText& InString);` — Set the Mutable Bool to be used for this widget
- L26 _private member_ `FText StringValue;` — The value to be shown by the widget's UI
- L32 _private prototype_ `FText GetValue() const;` — Callback used by the widget to get the value to display on the UI @return The variable StringValue as an FText

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableTagListWidget.h` (Private)


#### class `SMutableTagComboBox`  
`class SMutableTagComboBox : public SMutableSearchComboBox`  
_L25-59_
- inherits: `SMutableSearchComboBox`
- L29 _public function_ `SLATE_BEGIN_ARGS(SMutableTagComboBox) : _Node(nullptr) , _AllowInternalTags(true)`
- L34 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(UCustomizableObjectNode*, Node) SLATE_ARGUMENT(const FSlateBrush*, MenuButtonBrush) SLATE_ARGUMENT(bool, AllowInternalTags) SLATE_EVENT(FOnTextChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this button's content (optional)
- L46 _public prototype_ `void RefreshOptions();`
- L50 _private member_ `class UCustomizableObjectNode* Node = nullptr;`
- L52 _private member_ `TArray< TSharedRef<SMutableSearchComboBox::FFilteredOption> > TagComboOptionsSource;`
- L54 _private member_ `bool bAllowInternalTags = true;`
- L57 _private prototype_ `TSharedPtr<SMutableSearchComboBox::FFilteredOption> AddNodeHierarchyOptions(UEdGraphNode* Node, TMap<UEdGraphNode*, TSharedPtr<SMutableSearchComboBox::FFilteredOption>>& AddedOptions);`

#### class `SMutableTagListWidget`  
`class SMutableTagListWidget : public SCompoundWidget`  
_L63-111_
- inherits: `SCompoundWidget`
- L67 _public function_ `SLATE_BEGIN_ARGS(SMutableTagListWidget) : _Node(nullptr) , _TagArray(nullptr) , _AllowInternalTags(true)`
- L73 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectNode*, Node) SLATE_ARGUMENT(TArray<FString>*, TagArray) SLATE_ARGUMENT(FText, EmptyListText) SLATE_ARGUMENT(bool, AllowInternalTags) SLATE_EVENT(FSimpleDelegate, OnTagListChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L86 _public member_ `FSimpleDelegate OnTagListChangedDelegate;`
- L89 _public prototype_ `void RefreshOptions();`
- L93 _private member_ `class UCustomizableObjectNode* Node = nullptr;`
- L94 _private member_ `TArray<FString>* TagArray = nullptr;`
- L95 _private member_ `FText EmptyListText;`
- L97 _private member_ `TSharedPtr<SMutableTagComboBox> TagCombo;`
- L98 _private prototype_ `void OnTagComboBoxSelectionChanged(const FText& NewText);`
- L105 _private member_ `TSharedPtr<SListView<TSharedPtr<FTagUIData>>> TagListWidget;`
- L106 _private member_ `TArray< TSharedPtr<FTagUIData> > CurrentTagsSource;`
- L109 _private prototype_ `TSharedRef<ITableRow> GenerateTagListItemRow(TSharedPtr<FTagUIData> InItem, const TSharedRef<STableViewBase>& OwnerTable);`

#### struct `SMutableTagListWidget::FTagUIData`  
`struct FTagUIData`  
_L100-104_
- L102 _public member_ `FString Tag;`
- L103 _public member_ `FString DisplayName;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ESelectInfo`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SMutableTextComboBox.h` (Private)


#### class `SMutableTextComboBox`  
`template<typename OptionType> class SMutableTextComboBox : public SComboBox<OptionType>`  
_L9-77_
- inherits: `SComboBox<OptionType>`
- desc: Typed SComboBox with a translator to FText.
- L12 _public typedef_ `typedef typename SComboBox<OptionType>::FOnSelectionChanged FOnSelectionChanged;`
- L13 _public typedef_ `typedef typename SComboBox<OptionType>::NullableOptionType NullableOptionType;`
- L15 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FTranslateDelegate, OptionType);`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMutableTextComboBox<OptionType>)`
- L19 _public function_ `SLATE_ARGUMENT(const TArray<OptionType>*, Options) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_ARGUMENT(NullableOptionType, InitiallySelectedItem)` — Super arguments.
- L48 _private member_ `FTranslateDelegate Translate;` — Translate delegate.
- L51 _private function_ `FText GetText(OptionType Option) const` — If the translate delegate is bounded, returns call it and get the FText.
- L64 _private function_ `FText GetSelectedItemText() const` — Get the the text if there is a selected item.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FTranslateDelegate, OptionType);`
- L37 _function_ `` (scope `SMutableTextComboBox::SLATE_ARGUMENT`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/SStandAloneAssetPicker.h` (Private)


#### class `SStandAloneAssetPicker`  
`class SStandAloneAssetPicker : public SCompoundWidget`  
_L12-45_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SStandAloneAssetPicker)`
- L16 _public prototype_ `SLATE_EVENT(FOnGetAllowedClasses, OnGetAllowedClasses) SLATE_EVENT(FOnAssetSelected, OnAssetSelected) SLATE_ARGUMENT(TObjectPtr<UObject>, InitialAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `FReply OnClicked();`
- L26 _private prototype_ `TSharedRef<SWidget> OnGenerateAssetPicker();`
- L28 _private prototype_ `void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);`
- L29 _private prototype_ `void OnAssetEnterPressedFromPicker(const TArray<struct FAssetData>& AssetData);`
- L31 _private prototype_ `void RefreshThumbnail();`
- L36 _private member_ `TSharedPtr<SMenuAnchor> AssetPickerAnchor;` — Menu anchor for opening and closing the asset picker
- L38 _private member_ `FOnGetAllowedClasses OnGetAllowedClasses;`
- L39 _private member_ `FOnAssetSelected OnAssetSelected;`
- L40 _private member_ `TObjectPtr<UObject> CurrentAsset;`
- L42 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`
- L43 _private member_ `TSharedPtr<SWidget> ThumbnailWidget;`
- L44 _private member_ `TSharedPtr<SBox> ThumbnailContainer;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/UnrealBakeHelpers.h` (Private)


#### class `FUnrealBakeHelpers`  
`class FUnrealBakeHelpers`  
_L25-130_
- L29 _public prototype_ `static UObject* BakeHelper_DuplicateAsset(UObject* Object, TMap<UObject*, UObject*>* ReplacementMap, const bool bGenerateConstantMaterialInstances, FResourceBakingData& InOutPackageData);`
- L37 _public prototype_ `static UTexture2D* BakeHelper_CreateAssetTexture(UTexture2D* SourceTexture, const UTexture* OrgTex, TMap<UObject*, UObject*>* ReplacementMap, FResourceBakingData& InOutPackageData);` — Duplicates a texture asset. Duplicates Mutable and non Mutable textures. @param OrgTex Original source texture from which a Mutable texture has been generated. Only required when SrcTex is a Mutable texture.
- L41 _public function_ `template<typename MaterialType> static void CopyAllMaterialParameters(MaterialType& DestMaterial, UMaterialInterface& OriginMaterial, const TMap<int32, UTexture*>& TextureReplacementMap)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/UnrealEditorPortabilityHelpers.h` (Private)


#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_MUTABLE_GET_BRUSH FAppStyle::GetBrush`
- L28 _macro_ `#define UE_MUTABLE_GET_FLOAT FAppStyle::GetFloat`
- L29 _macro_ `#define UE_MUTABLE_GET_MARGIN FAppStyle::GetMargin`
- L30 _macro_ `#define UE_MUTABLE_GET_FONTSTYLE FAppStyle::GetFontStyle`
- L31 _macro_ `#define UE_MUTABLE_GET_WIDGETSTYLE FAppStyle::GetWidgetStyle`
- L32 _macro_ `#define UE_MUTABLE_GET_COLOR FAppStyle::GetColor`
- L33 _macro_ `#define UE_MUTABLE_GET_SLATECOLOR FAppStyle::GetSlateColor`
- L37 _macro_ `#define UE_MUTABLE_GET_BRUSH FAppStyle::Get().GetBrush`
- L38 _macro_ `#define UE_MUTABLE_GET_FLOAT FAppStyle::Get().GetFloat`
- L39 _macro_ `#define UE_MUTABLE_GET_MARGIN FAppStyle::Get().GetMargin`
- L40 _macro_ `#define UE_MUTABLE_GET_FONTSTYLE FAppStyle::Get().GetFontStyle`
- L41 _macro_ `#define UE_MUTABLE_GET_WIDGETSTYLE FAppStyle::Get().GetWidgetStyle`
- L42 _macro_ `#define UE_MUTABLE_GET_COLOR FAppStyle::Get().GetColor`
- L43 _macro_ `#define UE_MUTABLE_GET_SLATECOLOR FAppStyle::Get().GetSlateColor`
- L48 _function_ `inline FString Helper_GetPinName(const UEdGraphPin* Pin)`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/CustomizableObjectNodeTableCompilationFilterEditor.h` (Private)


#### class `FCustomizableObjectNodeTableCompilationFilterEditor`  
`class FCustomizableObjectNodeTableCompilationFilterEditor : public IPropertyTypeCustomization`  
_L11-51_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L17 _public prototype_ `void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L18 _public prototype_ `void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _private member_ `TWeakObjectPtr<UCustomizableObjectNodeTable> Node;` — Pointer to the node represented in this details
- L25 _private member_ `TSharedPtr<IPropertyHandle> ColumnPropertyHandle;`
- L28 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandlePtr;` — Pinter to the structure instance, useful to get the array index of the property
- L31 _private member_ `TArray<TSharedPtr<FString>> CompilationFilterColumnOptionNames;` — Array with the name of the Version columns
- L34 _private member_ `TSharedPtr<STextComboBox> CompilationFilterColumnComboBox;` — ComboBox widget to select a VersionColumn from the NodeTable
- L38 _private prototype_ `TSharedPtr<FString> GenerateCompilationFilterColumnComboBoxOptions();` — Generates MutableMetadata columns combobox options Returns the current selected option or a null pointer
- L41 _private prototype_ `void OnOpenCompilationFilterColumnComboBox();` — Callback to regenerate the combobox options
- L44 _private prototype_ `void OnCompilationFilterColumnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — OnComboBoxSelectionChanged Callback for Layout ComboBox
- L47 _private prototype_ `FSlateColor GetCompilationFilterColumnComboBoxTextColor() const;` — Sets the combo box selection color
- L50 _private prototype_ `void OnCompilationFilterColumnComboBoxSelectionReset();` — OnComboBoxSelectionChanged Callback for Layout ComboBox

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/CustomizableObjectVariationCustomization.h` (Private)


#### class `FCustomizableObjectVariationCustomization`  
`class FCustomizableObjectVariationCustomization : public IPropertyTypeCustomization`  
_L16-37_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public function_ `void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L28 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> BaseObjectNode;` — Weak pointer to the Customizable Object node that contains this property
- L31 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Runtime Parameter Name property of a State
- L32 _private member_ `TSharedPtr<IPropertyHandle> TagPropertyHandle;`
- L35 _private prototype_ `void ResetSelectedParameterButtonClicked();` — Callback of the function OverrideResetToDefault

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/MutableExpanderArrow.h` (Private)


#### class `SMutableExpanderArrow`  
`class SMutableExpanderArrow final : public SExpanderArrow`  
_L10-30_
- inherits: `SExpanderArrow`
- desc: Custom expander arrow object where the lines drawn will be colored using a circular coloring pattern based on the depth of the element to be drawn.
- L13 _public function_ `SLATE_BEGIN_ARGS( SMutableExpanderArrow )`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedPtr<class ITableRow>& TableRow );`
- L20 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L29 _private prototype_ `FLinearColor GetLevelColor(const int32 Level) const;` — Provided a level value this method will return the color to be used to paint it. @param Level The level whose draw color we want to know @return The color to use during the drawing of the provided level index

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/MutableMultiPageListView.h` (Private)


#### class `SMutableMultiPageListView`  
`template <typename ItemType> class SMutableMultiPageListView final : public SCompoundWidget`  
_L20-122_
- inherits: `SCompoundWidget`
- desc: Slate containing a list view designed to contain high amounts of elements. Will separate the elements in pages so the parent UI element drawing them can get the listview to fit without triggering any hard limit in the size of the containing slate object. This class was created out of the necessity of having lists with hundreds of elements (mutable constant images for example). @tparam ItemType The type of item the list view is holding
- L24 _public function_ `SLATE_BEGIN_ARGS(SMutableMultiPageListView<ItemType>) : _HostedListView(nullptr) , _ElementsToSeparateInPages(nullptr)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SListView<ItemType>>, HostedListView) SLATE_ARGUMENT(TSharedPtr<const TArray<ItemType>>, ElementsToSeparateInPages) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The list view we want to manipulate
- L45 _private prototype_ `EVisibility GetPageNavigationBoxVisibility() const;` — Get the visibility state set for the navigation buttons box. If there is no need for the box existence it will then be collapsed @return The visibility state to use in the navigation panel
- L51 _private prototype_ `FReply OnBackButtonClicked();` — Changes the page to the previous one @return the reply status to know if the operation was handled or not.
- L57 _private prototype_ `FReply OnForwardButtonClicked();` — Changes the page to the next one @return the reply status to know if the operation was handled or not.
- L63 _private prototype_ `FReply OnFullBackButtonClicked();` — Sets the page to the first one @return the reply status to know if the operation was handled or not.
- L69 _private prototype_ `FReply OnFullForwardButtonClicked();` — Sets the page to the last one @return the reply status to know if the operation was handled or not.
- L75 _private prototype_ `bool ShouldBackButtonBeEnabled() const;` — Controls if the back button should or should not be enabled @return True if it should, false otherwise.
- L81 _private prototype_ `bool ShouldNextButtonBeEnabled() const;` — Controls if the forward button should or should not be enabled @return True if it should, false otherwise.
- L87 _private prototype_ `FText OnDrawCurrentPageText() const;` — Handles the drawing of the current / total pages UI text. @return The text representing the currently displayed page
- L92 _public prototype_ `void RegeneratePage();` — Compute the elements to display for the current page
- L95 _public prototype_ `void ClearSelection();` — Clear the selected item from the handled list view
- L103 _private member_ `const uint32 ElementsPerPage = 24;` — Amount of elements an array segment can hold. The lowest the more stable the UI drawing gets (avoids crash due to oversize slate Y size)
- L106 _private member_ `uint32 CurrentSegmentIndex = 0;` — The index of the current page/segment. Will increase and decrease using the UI
- L112 _private member_ `uint32 TotalAmountOfPages = 0;` — The computed total amount of segments. It is based in the amount of elements provided in the AllElements array and the value set in ElementsPerPage
- L115 _private member_ `TArray<ItemType> CurrentSegmentElements;` — Elements being displayed in the current page
- L118 _private member_ `TSharedPtr<SListView<ItemType>> HostedListView;` — List view handled by this slate.
- L121 _private member_ `TSharedPtr<const TArray<ItemType>> AllElements;` — Array with all the elements to manage from the provided ListView
- L127 _function_ `template <typename ItemType> void SMutableMultiPageListView<ItemType>::Construct(const FArguments& InArgs)`
- L221 _function_ `template <typename ItemType> EVisibility SMutableMultiPageListView<ItemType>::GetPageNavigationBoxVisibility() const`
- L228 _function_ `template <typename ItemType> FReply SMutableMultiPageListView<ItemType>::OnBackButtonClicked()`
- L240 _function_ `template <typename ItemType> FReply SMutableMultiPageListView<ItemType>::OnForwardButtonClicked()`
- L252 _function_ `template <typename ItemType> FReply SMutableMultiPageListView<ItemType>::OnFullBackButtonClicked()`
- L264 _function_ `template <typename ItemType> FReply SMutableMultiPageListView<ItemType>::OnFullForwardButtonClicked()`
- L276 _function_ `template <typename ItemType> bool SMutableMultiPageListView<ItemType>::ShouldBackButtonBeEnabled() const`
- L283 _function_ `template <typename ItemType> bool SMutableMultiPageListView<ItemType>::ShouldNextButtonBeEnabled() const`
- L290 _function_ `template <typename ItemType> FText SMutableMultiPageListView<ItemType>::OnDrawCurrentPageText() const`
- L301 _function_ `template <typename ItemType> void SMutableMultiPageListView<ItemType>::RegeneratePage()`
- L324 _function_ `template <typename ItemType> void SMutableMultiPageListView<ItemType>::ClearSelection()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "CustomizableObjectEditor"`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/SCustomizableObjectMacroLibraryList.h` (Private)


#### struct `FMacroTreeEntry`  
`struct FMacroTreeEntry`  
_L10-13_
- L12 _public member_ `TWeakObjectPtr<UCustomizableObjectMacro> Macro;`

#### class `SCustomizableObjectMacroLibraryList`  
`class SCustomizableObjectMacroLibraryList : public SCompoundWidget`  
_L15-56_
- inherits: `SCompoundWidget`
- L19 _public function_ `DECLARE_DELEGATE_OneParam(FOnSelectMacroDelegate, UCustomizableObjectMacro*) DECLARE_DELEGATE_OneParam(FOnRemoveMacroDelegate, UCustomizableObjectMacro*) SLATE_BEGIN_ARGS(SCustomizableObjectMacroLibraryList)`
- L23 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<UCustomizableObjectMacroLibrary>, MacroLibrary) SLATE_ARGUMENT(FOnAddMacroButtonClickedDelegate, OnAddMacroButtonClicked) SLATE_ARGUMENT(FOnSelectMacroDelegate, OnSelectMacro) SLATE_ARGUMENT(FOnRemoveMacroDelegate, OnRemoveMacro) SLATE_END_ARGS()`
- L33 _public prototype_ `void GenerateRowView();` — Generates and Updates the List View widget and its source.
- L36 _public prototype_ `void OnRemoveCurrentMacro(UCustomizableObjectMacro* MacroToDelete);` — Callback to regenerate the List View when a Macro has been removed. It is also used to comunicate the Macro Library editor.
- L39 _public prototype_ `void SetSelectedMacro(const UCustomizableObjectMacro& MacroToSelect);` — Set the Selected Macro
- L44 _private member_ `TObjectPtr<UCustomizableObjectMacroLibrary> MacroLibrary;` — Pointer to the Macro Library that contains the macros.
- L47 _private member_ `TSharedPtr<SListView<TSharedPtr<FMacroTreeEntry>>> ListView;` — Pointer to the List View widget. Needed to refresh it when something changes.
- L50 _private member_ `TArray<TSharedPtr<FMacroTreeEntry>> ListViewSource;` — Array that contains all the macros of the Library in a format for the List View
- L53 _private member_ `FOnAddMacroButtonClickedDelegate OnAddMacroButtonClicked;` — List view action callbacks
- L54 _private member_ `FOnSelectMacroDelegate OnSelectMacro;`
- L55 _private member_ `FOnRemoveMacroDelegate OnRemoveMacro;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE(FOnAddMacroButtonClickedDelegate) DECLARE_DELEGATE_OneParam(FOnSelectMacroDelegate, UCustomizableObjectMacro*) DECLARE_DELEGATE_OneParam(FOnRemoveMacroDelegate, UCustomizableObjectMacro*) SLATE_BEGIN_ARGS(SCustomizableObjectMacroLibraryList) {} SLATE_ARGUMENT(TObjectPtr<UCustomizableObjectMacroLibrary>, MacroLibrary) SLATE_ARGUMENT(FOnAddMacroButtonClickedDelegate, OnAddMacroButtonClicked) SLATE_ARGUMENT(FOnSelectMacroDelegate, OnSelectMacro) SLATE_ARGUMENT(FOnRemoveMacroDelegate, OnRemoveMacro) SLATE_END_ARGS()`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectMacroDelegate, UCustomizableObjectMacro*) DECLARE_DELEGATE_OneParam(FOnRemoveMacroDelegate, UCustomizableObjectMacro*) SLATE_BEGIN_ARGS(SCustomizableObjectMacroLibraryList) {} SLATE_ARGUMENT(TObjectPtr<UCustomizableObjectMacroLibrary>, MacroLibrary) SLATE_ARGUMENT(FOnAddMacroButtonClickedDelegate, OnAddMacroButtonClicked) SLATE_ARGUMENT(FOnSelectMacroDelegate, OnSelectMacro) SLATE_ARGUMENT(FOnRemoveMacroDelegate, OnRemoveMacro) SLATE_END_ARGS()`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRemoveMacroDelegate, UCustomizableObjectMacro*) SLATE_BEGIN_ARGS(SCustomizableObjectMacroLibraryList) {} SLATE_ARGUMENT(TObjectPtr<UCustomizableObjectMacroLibrary>, MacroLibrary) SLATE_ARGUMENT(FOnAddMacroButtonClickedDelegate, OnAddMacroButtonClicked) SLATE_ARGUMENT(FOnSelectMacroDelegate, OnSelectMacro) SLATE_ARGUMENT(FOnRemoveMacroDelegate, OnRemoveMacro) SLATE_END_ARGS()`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/SMutableExpandableTableRow.h` (Private)


#### class `SMutableExpandableTableRow`  
`template<typename ItemType> class SMutableExpandableTableRow : public STableRow<ItemType>`  
_L23-341_
- inherits: `STableRow<ItemType>`
- desc: Pin Viewer custom row. Allows a row to have expandable custom details. The following code is copy of SMultiColumnTableRow with slight modifications.
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& InColumnName ) = 0;` — Users of SMultiColumnTableRow would usually some piece of data associated with it. The type of this data is ItemType; it's the stuff that your TableView (i.e. List or Tree) is visualizing. The ColumnName tells you which column of the TableView we need to make a widget for. Make a widget and return it. @param ColumnName    A unique ID for a column in this TableView; see SHeaderRow::FColumn for more info. @return a widget to represent the contents of a cell in this row of a TableView.
- L39 _public function_ `virtual TSharedPtr<SWidget> GenerateAdditionalWidgetForRow()` — Add pin custom pin custom details panel. Override if required.
- L45 _public function_ `virtual EVisibility GetAdditionalWidgetDefaultVisibility() const` — Returns the default visibility of the additional widget. Override if required.
- L51 _public function_ `virtual void SetAdditionalWidgetVisibility(const EVisibility InVisibility)` — Set the visibility to the additional widget.
- L60 _public typedef_ `typedef SMultiColumnTableRow< ItemType > FSuperRowType;` — Use this to construct the superclass; e.g. FSuperRowType::Construct( FTableRowArgs(), OwnerTableView )
- L63 _public typedef_ `typedef typename STableRow<ItemType>::FArguments FTableRowArgs;` — Use this to construct the superclass; e.g. FSuperRowType::Construct( FTableRowArgs(), OwnerTableView )
- L66 _protected function_ `void Construct(const FTableRowArgs& InArgs, const TSharedRef<STableViewBase>& OwnerTableView)`
- L151 _protected function_ `virtual void ConstructChildren( ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent ) override`
- L163 _protected function_ `void GenerateColumns( const TSharedRef<SHeaderRow>& InColumnHeaders )`
- L264 _protected function_ `void ClearCellCache()`
- L269 _protected function_ `const TSharedRef<SWidget>* GetWidgetFromColumnId(const FName& ColumnId) const`
- L275 _protected function_ `FSlateColor GetBackgroundColor() const` — Returns custom background color.
- L281 _protected function_ `EVisibility GetExpanderVisibility() const` — Returns visible if there is an additional widget.
- L287 _protected function_ `FReply OnExpanderClicked()` — Collapse or show the additional details.
- L299 _protected function_ `const FSlateBrush* GetExpanderImage() const` — Returns the expander image depending on the additional details visibility state.
- L333 _private member_ `TSharedPtr<SHorizontalBox> Box;`
- L334 _private member_ `TMap< FName, TSharedRef< SWidget > > ColumnIdToSlotContents;`
- L337 _private member_ `TSharedPtr<SWidget> AdditionalWidget;` — Pin Viewer row additional widget.
- L340 _private member_ `TSharedPtr<SButton> ExpanderArrow;` — Expand button.

#### Free symbols / members of external scopes

- L17 _prototype_ `FSlateColor GetRowBackgroundColor(const int32 IndentLevel, const bool IsHovered);` — Get the background color of the Pin Viewer elements. @param IndentLevel Element indent level. Returns different colors to distinguish between them. Copy of PropertyEditorConstants.cpp
- L229 _function_ `` (scope `SMutableExpandableTableRow::GenerateColumns`)

### `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/Widgets/SMutablePinTypeSelector.h` (Private)


#### class `SMutablePinTypeSelector`  
`class SMutablePinTypeSelector : public SCompoundWidget`  
_L19-43_
- inherits: `SCompoundWidget`
- desc: Slate that exposes a dropdown that takes care of exposing the pin category and allowing the end user to change it. It will call the refresh of the node to apply that change.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMutablePinTypeSelector)`
- L23 _public prototype_ `SLATE_ARGUMENT(FEdGraphPinReference, PinReference) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `FName GetInitiallySelectedPinType() const;`
- L31 _private prototype_ `bool ShouldVariableTypePropertyBeEnabled() const;`
- L32 _private prototype_ `FText GetToolTipText() const;`
- L33 _private prototype_ `TSharedRef<SWidget> OnGenerateVariableTypeRow(FName Type);`
- L34 _private prototype_ `void OnTypeDropdownSelectionChange(FName NewTypeName, ESelectInfo::Type Arg) const;`
- L35 _private prototype_ `TSharedRef<SWidget> GenerateCurrentSelectedTypeWidget();`
- L37 _private member_ `FEdGraphPinReference PinReference;`
- L39 _private member_ `TArray<FName> AllowedPinTypes;`
- L42 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> PinOwner;` — Weak pointer to the Customizable Object node that contains the pin

#### class `SMutablePinSubTypeSelector`  
`class SMutablePinSubTypeSelector : public SCompoundWidget`  
_L50-72_
- inherits: `SCompoundWidget`
- desc: Slate that exposes a dropdown that takes care of exposing the pin subcategory and allowing the end user to change it. It will call the refresh of the node to apply that change.
- L53 _public function_ `SLATE_BEGIN_ARGS(SMutablePinSubTypeSelector)`
- L54 _public prototype_ `SLATE_ARGUMENT(FEdGraphPinReference, PinReference) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L61 _private prototype_ `FName GetInitiallySelectedPinSubType() const;`
- L62 _private prototype_ `TSharedRef<SWidget> OnGenerateVariableSubtypeRow(FName Subtype);`
- L63 _private prototype_ `void OnTypeDropdownSelectionChange(FName NewSubTypeName, ESelectInfo::Type Arg) const;`
- L64 _private prototype_ `TSharedRef<SWidget> GenerateCurrentSelectedTypeWidget();`
- L66 _private member_ `FEdGraphPinReference PinReference;`
- L68 _private member_ `TArray<FName> AllowedPinSubtypes;`
- L71 _private member_ `TWeakObjectPtr<UCustomizableObjectNode> PinOwner;` — Weak pointer to the Customizable Object node that contains the pin

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/CustomizableObjectEditorFunctionLibrary.h` (Public)


#### enum `ECustomizableObjectCompilationState`  
`enum class ECustomizableObjectCompilationState : uint8`  
_L14-20_
- reflection: `UENUM()`
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `InProgress`
- L18 _public enumerator_ `Completed`
- L19 _public enumerator_ `Failed`

#### struct `FNewCustomizableObjectParameters`  
`struct FNewCustomizableObjectParameters`  
_L24-43_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `FString PackagePath;` — `UPROPERTY(BlueprintReadWrite, Category = NewCustomizableObjectParameters)` — Must not end with slash. For example "/Game"
- L34 _public member_ `FString AssetName;` — `UPROPERTY(BlueprintReadWrite, Category = NewCustomizableObjectParameters)` — For example "SampleAssetName"
- L38 _public member_ `TObjectPtr<UCustomizableObject> ParentObject;` — `UPROPERTY(BlueprintReadWrite, Category = NewCustomizableObjectParameters)` — Parent to attach the child Customizable Object to.
- L42 _public member_ `FString ParentGroupNode;` — `UPROPERTY(BlueprintReadWrite, Category = NewCustomizableObjectParameters)` — Group to attach the child Customizable Object to. Only used if ParentObject is provided.

#### class `UCustomizableObjectEditorFunctionLibrary`  
`class UCustomizableObjectEditorFunctionLibrary : public UBlueprintFunctionLibrary`  
_L51-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Functions we want to be able to call on CustomizableObjects at edit time - could be exposed to cook as well.
- L66 _public prototype_ `static ECustomizableObjectCompilationState CompileCustomizableObjectSynchronously( UCustomizableObject* CustomizableObject, ECustomizableObjectOptimizationLevel OptimizationLevel = ECustomizableObjectOptimizationLevel::None, ECustomizableObjectTextureCompression TextureCompression = ECustomizableObjectTextureCompression::Fast, bool bGatherReferences = false);` — `UFUNCTION(BlueprintCallable, Category = "CustomizableObject")` — DEPRECATED. Use UCustomizableObject::Compile instead. Synchronously compiles the provided CustomizableObject, LogMutable will contain intermittent updates on progress. @param CustomizableObject	The CustomizableObject to compile @return	The final ECustomizableObjectCompilationState - typically Completed or Failed
- L74 _public prototype_ `static UCustomizableObject* NewCustomizableObject(const FNewCustomizableObjectParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = "CustomizableObject")` — Create a new Customizable Object inside a package.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/CustomizableObjectFactory.h` (Public)


#### class `UCustomizableObjectFactory`  
`class UCustomizableObjectFactory : public UFactory`  
_L27-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L31 _private prototype_ `UCustomizableObjectFactory();`
- L35 _public prototype_ `virtual bool DoesSupportClass(UClass * Class) override;`
- L36 _public prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L37 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`
- L12 _namespace_ `namespace ETextCommit`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/CustomizableObjectInstanceFactory.h` (Public)


#### class `UCustomizableObjectInstanceFactory`  
`class UCustomizableObjectInstanceFactory : public UActorFactory`  
_L15-25_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L21 _protected prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;` — UActorFactory interface
- L22 _protected prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L23 _protected prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L24 _protected prototype_ `virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/CustomizableObjectVersionBridge.h` (Public)


#### class `UCustomizableObjectVersionBridgeInterface`  
`class UCustomizableObjectVersionBridgeInterface : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `ICustomizableObjectVersionBridgeInterface`  
`class ICustomizableObjectVersionBridgeInterface`  
_L15-49_
- L31 _public function_ `virtual bool IsVersionStructIncludedInCurrentRelease(const FInstancedStruct& VersionStruct) const` — Checks whether the version encoded in VersionStruct is older or equal to the CurrentRelease, meaning that all Mutable child Customizable Objects marked with this version that return true should be compiled and packaged. The VersionStruct will encode the game-specific version struct, and should be accessed from the game-specific implementation of this interface in the the VersionBridge property in the CustomizableObject with the VersionStruct.GetPtr<GameSpecificVersionType>() method. The VersionStruct in child CustomizableObjects must be of the GameSpecificVersionType type. @param VersionStruct Struct encoding the version of the Mutable table row @return True if the table row is included in the current release
- L43 _public function_ `virtual bool IsVersionPropertyIncludedInCurrentRelease(const FProperty& VersionProperty, const uint8* CellData) const` — Checks whether the version encoded in VersionProperty/CellData is older or equal to the CurrentRelease, meaning that all Mutable table rows marked with this version that return true should be compiled and packaged. The VersionProperty/CellData will encode the game-specific version struct, and should be accessed from the game-specific implementation of this interface in the the VersionBridge property in the CustomizableObject by casting CellData to the GameSpecificVersionType. The Version column in Mutable data table must be of the GameSpecificVersionType type. @param VersionProperty Property of the column encoding the version of the Mutable table row. Useful for type checking. @param CellData pointer to the GameSpecificVersionType struct encoding the version of the Mutable table row @return True if the table row is included in the current release
- L48 _public function_ `virtual FString GetCurrentVersionAsString() const` — Get the version as string to include it when building the derived data cache key. @return current version as string.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/EdGraphSchema_CustomizableObject.h` (Public)


#### class `UEdGraphSchema_CustomizableObject`  
`class UEdGraphSchema_CustomizableObject : public UEdGraphSchema`  
_L24-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L30 _public member_ `static const FName PC_Object;` — Allowable PinType.PinCategory values
- L31 _public member_ `static const FName PC_Component;`
- L32 _public member_ `static const FName PC_MeshSection;`
- L33 _public member_ `static const FName PC_Modifier;`
- L34 _public member_ `static const FName PC_Mesh;`
- L35 _public member_ `static const FName PC_SkeletalMesh;`
- L36 _public member_ `static const FName PC_SkeletalMesh_Passthrough;`
- L37 _public member_ `static const FName PC_SkeletalMesh_Object;`
- L38 _public member_ `static const FName PC_Texture;`
- L39 _public member_ `static const FName PC_Texture_Passthrough;`
- L40 _public member_ `static const FName PC_Texture_Object;`
- L41 _public member_ `static const FName PC_Projector;`
- L42 _public member_ `static const FName PC_GroupProjector;`
- L43 _public member_ `static const FName PC_Color;`
- L44 _public member_ `static const FName PC_Float;`
- L45 _public member_ `static const FName PC_Bool;`
- L46 _public member_ `static const FName PC_Enum;`
- L47 _public member_ `static const FName PC_Stack;`
- L48 _public member_ `static const FName PC_Material;`
- L49 _public member_ `static const FName PC_Wildcard;`
- L50 _public member_ `static const FName PC_PoseAsset;`
- L51 _public member_ `static const FName PC_Transform;`
- L52 _public member_ `static const FName PC_String;`
- L53 _public member_ `static const FName PC_StaticMesh;`
- L55 _public member_ `static const FName PSC_Material_Override;`
- L56 _public member_ `static const FName PSC_Material_Overlay;`
- L58 _public member_ `static const TArray<FName> SupportedMacroPinTypes;`
- L61 _public member_ `static const FText NC_Experimental;` — Node categories
- L62 _public member_ `static const FText NC_Material;`
- L65 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;` — EdGraphSchema interface
- L66 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L67 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L68 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L69 _public prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L70 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L71 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L72 _public prototype_ `virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L73 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L74 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L75 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L76 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L77 _public prototype_ `virtual FPinConnectionResponse MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove, bool bNotifyLinkedNodes) const override;`
- L78 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;`
- L81 _public prototype_ `static FLinearColor GetPinTypeColor(const FName& PinType);` — Own interface
- L82 _public prototype_ `static FName GetPinCategoryName(const FName& PinCategory);`
- L83 _public prototype_ `static FName GetPinCategoryName(const UScriptStruct* Type);`
- L84 _public prototype_ `static FName GetPinSubCategoryName(const FName& PinSubCategory);`
- L85 _public prototype_ `static FText GetPinFriendlyName(const FName& PinCategory);`
- L86 _public prototype_ `static FText GetPinCategoryFriendlyName(const FName& PinCategory);`
- L87 _public prototype_ `static FText GetPinSubCategoryFriendlyName(const FName& PinSubcategory);`
- L88 _public prototype_ `static bool IsPassthrough(const FName& PinCategory);`
- L89 _public prototype_ `static bool IsTypeNative(const UScriptStruct* Type);`
- L90 _public prototype_ `static FText GetSubCategoryTooltipText(FName PinSubType);`
- L93 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/ExtensionDataCompilerInterface.h` (Public)


#### class `FExtensionDataCompilerInterface`  
`class FExtensionDataCompilerInterface`  
_L19-37_
- desc: An object that gets passed around during Customizable Object compilation to help set up Extension Data.
- L22 _public prototype_ `FExtensionDataCompilerInterface(FMutableGraphGenerationContext& InGenerationContext);`
- L26 _public prototype_ `UE::Mutable::Private::PASSTHROUGH_ID MakeExtensionData(UObject& ExtensionData, bool bDuplicate);` — Register a new Extension Data. @param bDuplicate if true, object will be duplicated during cook.
- L31 _public prototype_ `void AddGeneratedNode(const UCustomizableObjectNode* InNode);` — Adds a node to the Generation Context list of generated nodes. This function is meant to be called from classes that implement ICustomizableObjectExtensionNode::GenerateMutableNode for any generated nodes so they are registered against the Mutable compiler
- L34 _public prototype_ `void CompilerLog(const FText& InLogText, const UCustomizableObjectNode* InNode);` — Adds a compiler log message to be displayed at the end of the compilation process
- L36 _public member_ `FMutableGraphGenerationContext& GenerationContext;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/ICustomizableObjectExtensionNode.h` (Public)


#### class `UCustomizableObjectExtensionNode`  
`class UCustomizableObjectExtensionNode : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Customizable Object graph nodes that output FExtensionData should implement this interface

#### class `ICustomizableObjectExtensionNode`  
`class ICustomizableObjectExtensionNode`  
_L19-26_
- L25 _public prototype_ `virtual UE::Mutable::Private::Ptr<UE::Mutable::Private::NodeExtensionData> GenerateMutableNode(FExtensionDataCompilerInterface& CompilerInterface) const = 0;` — Generate a UE::Mutable::Private::Node that produces FExtensionData

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/ICustomizableObjectInstanceEditor.h` (Public)


#### class `ICustomizableObjectInstanceEditor`  
`class ICustomizableObjectInstanceEditor`  
_L26-109_
- desc: Public interface to Customizable Object Instance Editor
- L29 _public prototype_ `virtual UCustomizableObjectInstance* GetPreviewInstance() = 0;`
- L32 _public prototype_ `virtual TSharedPtr<SCustomizableObjectEditorViewportTabBody> GetViewport() = 0;` — Refreshes the Customizable Object Instance Editor's viewport.
- L35 _public prototype_ `virtual void RefreshTool() = 0;` — Refreshes everything in the Customizable Object Instance Editor.
- L38 _public prototype_ `virtual UProjectorParameter* GetProjectorParameter() = 0;` — Return the selected projector in the viewport/editor.
- L40 _public prototype_ `virtual UCustomSettings* GetCustomSettings() = 0;`
- L44 _public prototype_ `virtual void HideGizmo() = 0;` — Hide the currently selected gizmo. Notice that only a single gizmo can be shown at the same time. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L48 _public function_ `virtual void ShowGizmoProjectorNodeProjectorConstant(UCustomizableObjectNodeProjectorConstant& Node)` — Show the default projector value gizmo of the given NodeProjectorConstant. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L52 _public function_ `virtual void HideGizmoProjectorNodeProjectorConstant()` — Hide the default projector value gizmo of the given NodeProjectorConstant. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L56 _public function_ `virtual void ShowGizmoProjectorNodeProjectorParameter(UCustomizableObjectNodeProjectorParameter& Node)` — Show the default projector value gizmo of the given NodeProjectorParameter. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L60 _public function_ `virtual void HideGizmoProjectorNodeProjectorParameter()` — Hide the default projector value gizmo of the given NodeProjectorParameter. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L64 _public prototype_ `virtual void ShowGizmoProjectorParameter(const FString& ParamName, int32 RangeIndex = -1) = 0;` — Show the projector value gizmo of the given parameter. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L68 _public prototype_ `virtual void HideGizmoProjectorParameter() = 0;` — Hide the projector value gizmo of the given parameter. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L72 _public function_ `virtual void ShowGizmoClipMorph(UCustomizableObjectNodeModifierClipMorph& ClipPlainNode)` — Show the clip morph plane gizmo of the NodeClipMorph. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L77 _public function_ `virtual void HideGizmoClipMorph(bool bClearGraphSelectionSet = true)` — Hide the clip morph plane gizmo of the NodeClipMorph. @param bClearGraphSelectionSet If set to true will deselect all nodes in the graph.
- L80 _public function_ `virtual void ShowGizmoClipMesh(UCustomizableObjectNode& Node, FTransform* Transform, const UEdGraphPin& MeshPin)` — Show the clipping mesh gizmo from a node that uses a transformable bounding mesh.
- L84 _public function_ `virtual void HideGizmoClipMesh()` — Hide the clipping mesh gizmo from the NodeMeshClipWithMesh. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L88 _public function_ `virtual void ShowGizmoLight(ULightComponent& SelectedLight)` — Show the light gizmo of the light. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L92 _public function_ `virtual void HideGizmoLight()` — Hide the light gizmo of the light. Synchronizes all editor widgets so that the selection and the widgets is always consistent.
- L95 _public prototype_ `virtual UCustomizableObjectEditorProperties* GetEditorProperties() = 0;` — @return Editor properties.
- L97 _public prototype_ `virtual TSharedPtr<SCustomizableObjectEditorAdvancedPreviewSettings> GetAdvancedPreviewSettings() = 0;`
- L99 _public prototype_ `virtual bool ShowLightingSettings() = 0;`
- L101 _public prototype_ `virtual bool ShowProfileManagementOptions() = 0;`
- L103 _public prototype_ `virtual const UObject* GetObjectBeingEdited() = 0;`
- L108 _public function_ `virtual FEditorModeTools* GetEditorModeTools()` — Returns the editor's ModeTools for use by viewport clients. Editors that inherit from FAssetEditorToolkit should return their EditorModeManager. Returns nullptr by default, which causes viewport clients to create their own.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/ICustomizableObjectPopulationModule.h` (Public)


#### class `ICustomizableObjectPopulationModule`  
`class ICustomizableObjectPopulationModule : public IModuleInterface`  
_L12-42_
- inherits: `IModuleInterface`
- desc: The public interface of the CustomizableObject module
- L22 _public function_ `static inline ICustomizableObjectPopulationModule& Get()` — Singleton-like access to ICustomizableObjectPopulationModule @return Returns CustomizableObjectModule singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L38 _public prototype_ `virtual FString GetPluginVersion() const = 0;` — Return a string representing the plugin version.
- L41 _public function_ `virtual void RecompilePopulations(UCustomizableObject* Object)` — Recompiles all the populations referenced in the Customizabled Object

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/Nodes/CustomizableObjectNode.h` (Public)


#### enum `EAddPinNodeButtonLocation`  
`enum class EAddPinNodeButtonLocation : uint8`  
_L30-40_
- desc: Determines where the "Add Pin" button should be added within the node.
- L33 _public enumerator_ `NONE = 0` — No "Add Pin" option will be added to the node UI.
- L36 _public enumerator_ `INPUT` — An option to add pins on the INPUT side of the node will be added.
- L39 _public enumerator_ `OUTPUT` — An option to add pins on the OUTPUT side of the node will be added.

#### enum `EEditablePinNameBoxVisibilityPolicy`  
`enum class EEditablePinNameBoxVisibilityPolicy : uint8`  
_L46-53_
- desc: Determines the visibility behaviour for the editable pin name text boxes
- L49 _public enumerator_ `HIDE_IF_LINKED = 0` — Default behaviour : Any linked pin will have it's editable textbox hidden.
- L52 _public enumerator_ `ALWAYS_VISIBLE` — Always show the text box.

#### enum `ESizeOptions`  
`enum class ESizeOptions : uint8`  
_L58-67_
- reflection: `UENUM()`
- L60 _public enumerator_ `Value_2 = 2 UMETA(DisplayName="2")`
- L61 _public enumerator_ `Value_4 = 4 UMETA(DisplayName="4")`
- L62 _public enumerator_ `Value_8 = 8 UMETA(DisplayName="8")`
- L63 _public enumerator_ `Value_16 = 16 UMETA(DisplayName="16")`
- L64 _public enumerator_ `Value_32 = 32 UMETA(DisplayName="32")`
- L65 _public enumerator_ `Value_64 = 64 UMETA(DisplayName="64")`
- L66 _public enumerator_ `Value_128 = 128 UMETA(DisplayName="128")`

#### struct `FLayoutSettings`  
`struct FLayoutSettings`  
_L71-80_
- reflection: `USTRUCT()`
- L76 _public member_ `ESizeOptions MaxGridSizeX = ESizeOptions::Value_4;` — `UPROPERTY(EditAnywhere, Category= NoCategory)`
- L79 _public member_ `ESizeOptions MaxGridSizeY = ESizeOptions::Value_4;` — `UPROPERTY(EditAnywhere, Category= NoCategory)`

#### class `UCustomizableObjectNodePinData`  
`class UCustomizableObjectNodePinData : public UObject`  
_L85-107_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Abstract base class for all pin data.
- L90 _public prototype_ `UCustomizableObjectNodePinData();`
- L93 _public prototype_ `bool operator==(const UCustomizableObjectNodePinData& Other) const;` — False if inherited types are different.
- L95 _public prototype_ `virtual bool operator!=(const UCustomizableObjectNodePinData& Other) const;`
- L98 _public function_ `virtual void Copy(const UCustomizableObjectNodePinData& Other)` — Virtual function used to copy pin data when remapping pins.
- L102 _public function_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion)` — Add backwards compatible code here. When called, it is guaranteed that all nodes in this graph will have executed the PostLoad function.
- L106 _protected prototype_ `virtual bool Equals(const UCustomizableObjectNodePinData& Other) const;` — Virtual function used to perform comparision between different UCustomizableObjectNodePinData inherited types.

#### class `UCustomizableObjectNode`  
`class UCustomizableObjectNode : public UEdGraphNode`  
_L135-452_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UEdGraphNode`
- desc: Base class of all Customizable Object nodes. The Customizable Object node system is build on top of the following premises. To avoid breaking this system, these premise must be hold! PREMISES: 1. A node can only be modified when a node is reconstructed (i.e., inside the ReconstructNode, AllocateDefaultPins functions). Exceptionally, a pin can also be created inside the BeginConstruct. We consider that a node has been modified if one of the following things happen: - Creation, destruction and modification of pins. - Modification of any data that would modify any pin.
- L141 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L142 _public prototype_ `virtual void PostLoad() override;` — Do work at PostBackwardsCompatibleFixup.
- L145 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;` — UEdGraphNode interface
- L146 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L147 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L148 _public prototype_ `virtual void DestroyNode() override;`
- L149 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L150 _public prototype_ `virtual bool GetCanRenameNode() const override;`
- L153 _public prototype_ `virtual void AllocateDefaultPins() override final;` — Allocates the default pins using the empty remap pins action. Usually called from CreateNode.
- L156 _public prototype_ `virtual void ReconstructNode() override final;` — Reconstructs the node using its default remap pins action.
- L157 _public prototype_ `virtual void PostInitProperties() override;`
- L161 _public function_ `virtual void BeginConstruct()` — Called at the beginning of the node lifecycle.
- L165 _public prototype_ `virtual void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion);` — Add backwards compatible code here. When called, it is guaranteed that all nodes in this graph will have executed the PostLoad function.
- L173 _public prototype_ `void FixupReconstructPins(UCustomizableObjectNodeRemapPins* RemapPinsAction, TFunction<void(UCustomizableObjectNode*, UCustomizableObjectNodeRemapPins*)> AllocateDefaultPins);` — Reconstructs the node pins using the provided AllocateDefaultPins function. Safe to call in BackwardsCompatibleFixup. Notice that this function will not call the node AllocateDefaultPins function nor the ReconstructNode overrides. Since this function is used BackwardsCompatibleFixup, it should not have major changes (or they will break existing fixups). If changes are needed, duplicate this function so old fixups remain unchanged.
- L178 _public function_ `virtual void PostBackwardsCompatibleFixup()` — Add post load work here. When called, it is guaranteed that all nodes in this graph will have executed the BackwardsCompatibleFixup function. Notice that no compatibility code should go here. Use BackwardsCompatibleFixup instead.
- L182 _public prototype_ `virtual bool CustomRemovePin(UEdGraphPin& Pin);` — Virtual implementation of RemovePin. Allows to do work before removing a pin. Use this function instead of RemovePin. RemovePin does not remove possible attached PinData.
- L190 _public prototype_ `virtual bool ShouldAddToContextMenu(FText& OutCategory) const;` — Subclasses should override this to return true and set OutCategory if this node should be auto-added to the right-click context menu in the graph editor. Some nodes are added manually in the graph editor code and don't need to do this.
- L192 _public function_ `virtual bool IsNodeOutDatedAndNeedsRefresh()`
- L193 _public function_ `virtual FString GetRefreshMessage() const`
- L194 _public prototype_ `void SetRefreshNodeWarning();`
- L195 _public prototype_ `void RemoveWarnings();`
- L198 _public function_ `virtual void UpdateReferencedNodeId(const FGuid& NewGuid)` — Used to replace Ids of referenced nodes by their new ids after duplicating the CustomizableObject.
- L200 _public prototype_ `TSharedPtr<FCustomizableObjectGraphEditorToolkit> GetGraphEditor() const;`
- L202 _public function_ `virtual bool ProvidesCustomPinRelevancyTest() const` — Override and return true if IsPinRelevant is overridden.
- L203 _public function_ `virtual bool IsPinRelevant(const UEdGraphPin*) const` — Override if default pins allocated with AllocateDefaultPins do not provide enough information.
- L219 _public prototype_ `virtual bool CanConnect(const UEdGraphPin* InOwnedInputPin, const UEdGraphPin* InOutputPin, bool& bOutIsOtherNodeBlocklisted, bool& bOutArePinsCompatible) const;` — Check if two pins can be connected. @param	InOwnedInputPin	Input pin which belongs to this node. @param	InOutputPin		Output pin which belongs to another node. If the node connects to iself, it could belong to this node. @param	bOutIsOtherNodeBlocklisted		Is the other node of a type we are not allowed to connect? @param	bOutArePinsCompatible		Does InOutputPin pin share the same type as the InOwnedInputPin? @return	True if the pin types match and if the other node is not one of the Blocklisted types.
- L222 _public prototype_ `virtual bool IsAffectedByLOD() const;` — Used during compilation process to cache the node for all LODs, or generate it specifically for each of them.
- L225 _public prototype_ `virtual TArray<FString> GetEnableTags(TArray<const UCustomizableObjectNodeMacroInstance*>* MacroContext = nullptr);` — Return an array of tags that this node will enable and apply to its data. This tags can come from the node details or string nodes linked to the "Enable tags" pin.
- L228 _public prototype_ `virtual TArray<FString>* GetEnableTagsArray();` — Return an array with all tags defined in the node's details panel. Null if none, or of it doesn't apply.
- L234 _public prototype_ `FString GetInternalTag() const;` — Return the unique internal tag that can identify this node across all objects. Internal tags are automatically added to some nodes that can be then referred to from other nodes. They are usually shown differently in the UI, to represent them as tags that will be defined in a single node.
- L237 _public prototype_ `static FGuid GetInternalTagNodeId(const FString& Tag);` — Return a valid GUID if a tag represents an internal tag.
- L238 _public prototype_ `static bool IsInternalTag(const FString& Tag);`
- L241 _public prototype_ `bool FindNodeForInternalTag(const FString& Tag, UCustomizableObjectNode*& OutNode, UCustomizableObject*& OutObject);` — Find the object and node that a given tag refers to, if it belongs to the same CO hierarchy that this node.
- L244 _public prototype_ `virtual FString GetInternalTagDisplayName();` — Return a non-unique, non-persistent UI-ready text to represent the interna tag of this node. It includes some node information for the user to identify the tag.
- L249 _public prototype_ `FString GetTagDisplayName(const FString& Tag);` — Return a UI-ready text to represent the given tag. For most cases this is just the tag, but if it is an internal tag of any node related to this one (in the same CO hierarchy) a more descriptive (non-persitent) name is build with node information.
- L252 _public prototype_ `class UCustomizableObjectGraph* GetCustomizableObjectGraph() const;` — Get the CustomizableObject graph that owns this node
- L255 _public prototype_ `virtual bool IsSingleOutputNode() const;` — If returns true, only a single link can go out of every output pin. False by default.
- L258 _public prototype_ `UEdGraphPin* CustomCreatePin( EEdGraphPinDirection Direction, const FName& Category, UCustomizableObjectNodePinData* PinData = nullptr);` — Wrapper of the pin creation method. Will use the PinName and PinFriendlyName returned by the "UEdGraphSchema_CustomizableObject"
- L261 _public prototype_ `UEdGraphPin* CustomCreatePin(EEdGraphPinDirection Direction, const FName& Category, const FName& Name, const FText& FriendlyName, UCustomizableObjectNodePinData* PinData = nullptr);` — Wrapper of the pin creation method, to cope with multiple Unreal Engine versions
- L263 _public function_ `virtual void AddAttachedErrorData(const FAttachedErrorDataView& )`
- L264 _public function_ `virtual void ResetAttachedErrorData()`
- L271 _public prototype_ `virtual bool ShouldBreakExistingConnections(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — When creating a new connection, break all previous connections. This method can be overridden. @return false by default.
- L273 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L276 _public function_ `virtual void BeginPostDuplicate(bool bDuplicateForPIE)` — Custom post duplicate function. Called at the beginning of duplication, before the nodes have their Guid updated.
- L279 _public prototype_ `TArray<UEdGraphPin*> GetAllNonOrphanPins() const;` — Gets all non orphan pins this node owns.
- L282 _public prototype_ `TArray<UEdGraphPin*> GetAllOrphanPins() const;` — Gets all orphan pins this node owns.
- L289 _public prototype_ `virtual void ReconstructNode(UCustomizableObjectNodeRemapPins* RemapPinsMode);` — Specialization of ReconstructNode UEdGraphNode function. @param RemapPinsMode pointer to a remap pins action. Remap pins action which will be used once the node has been reconstructed. Can be null.
- L292 _public prototype_ `void SetPinHidden(UEdGraphPin& InPin, bool bHidden);` — Set a pin to be hidden or not.
- L298 _public prototype_ `void SetPinHidden(const TArray<UEdGraphPin*>& Pins, bool bHidden);` — Set an array of pins to be hidden or not. @param Pins Input pins. All pins must be non null.
- L301 _public prototype_ `virtual bool CanPinBeHidden(const UEdGraphPin& Pin) const;` — Return true if a pin can be hidden.
- L304 _public prototype_ `virtual bool CanRenamePin(const UEdGraphPin& Pin) const;` — Determines if a pin can be renamed or not which determines if the pin will spawn with a TextBox slate at the side of the pin.
- L307 _public prototype_ `virtual EEditablePinNameBoxVisibilityPolicy GetEditablePinNameVisibilityPolicy (const UEdGraphPin& Pin) const;` — Determines the policy to use when drawing the pin slate.
- L310 _public prototype_ `virtual bool ShouldPinViewerShowPinEditableName(const UEdGraphPin& Pin) const;` — Determines if the Pin Viewer is allowed to include the Pin Editable Name as part of the PinName string shown.
- L312 _public prototype_ `virtual FText GetPinEditableName(const UEdGraphPin& Pin) const;`
- L314 _public prototype_ `virtual void SetPinEditableName(const UEdGraphPin& Pin, const FText& Value);`
- L316 _public prototype_ `virtual FLinearColor GetPinColor(const UEdGraphPin &Pin) const;`
- L319 _public prototype_ `virtual bool HasPinViewer() const;` — @return true if the details should spawn a Pin Viewer.
- L322 _public prototype_ `virtual EAddPinNodeButtonLocation GetAddPinButtonNodeSide() const;` — Determines to which side the "Add Pin" button should be added to
- L328 _public prototype_ `virtual void AddPinFromUI();` — Will request the generation of a new pin and, if successful, will notify the graph of the change. @note Method called when the Add Pins button is pressed.
- L335 _public prototype_ `virtual bool CanPinBeRemoved(const UEdGraphPin& Pin) const;` — Determines if a pin of this node can or can not be removed. Override this method to handle the removal of your node pins. @return True if the pin can be removed, false otherwise.
- L338 _public prototype_ `virtual TSharedPtr<IDetailsView> CustomizePinDetails(const UEdGraphPin& Pin) const;` — Returns pin custom details. Override if required.
- L341 _public prototype_ `UEdGraphPin* GetPin(const UCustomizableObjectNodePinData& PinData);` — Given the pin data, returns its associated pin.
- L344 _public prototype_ `UCustomizableObjectNodePinData* GetPinData(const UEdGraphPin &Pin) const;` — See GetPinData(const FEdGraphPinReference&).
- L350 _public function_ `template<typename T> T& GetPinData(const UEdGraphPin& Pin) const` — Given a pin which has attached data, get the typed pin data. @param Pin Pin which has attached data. @return Pin data already typed.
- L356 _public prototype_ `virtual bool IsNodeSupportedInMacros() const;` — Returns true if this node can be added to a COMacro Graph
- L359 _public prototype_ `bool IsInMacro() const;` — Returns true if this node is inside a Macro Graph
- L362 _public prototype_ `virtual TArray<FName> GetAllowedPinViewerCreationTypes() const;` — Returns an array with all the PC_Types that can be created from the pin viewer
- L369 _public prototype_ `virtual TArray<FName> GetPinAllowedTypes(const UEdGraphPin& Pin) const;` — Get the types the provided pin can changed to. @param Pin The pin you whant to know the types it can be changed to. @return A list of pin category names.
- L371 _public prototype_ `virtual TArray<FName> GetPinAllowedSubTypes(const UEdGraphPin& Pin) const;`
- L373 _public prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L375 _public member_ `FPostEditChangePropertyDelegate PostEditChangePropertyDelegate;`
- L377 _public member_ `FPostReconstructNodeDelegate PostReconstructNodeDelegate;`
- L379 _public member_ `FNodeConnectionListChangedDelegate NodeConnectionListChangedDelegate;`
- L381 _public member_ `FPinConnectionListChangedDelegate PinConnectionListChangedDelegate;`
- L383 _public member_ `FPostEditablePinNameChangedDelegate PinEditableNameChangedDelegate;`
- L385 _public member_ `FDestroyNodeDelegate DestroyNodeDelegate;`
- L387 _public member_ `FRemapPinsDelegate RemapPinsDelegate;`
- L397 _protected function_ `virtual void AllocateDefaultPins(UCustomizableObjectNodeRemapPins* RemapPins)` — Specialization of AllocateDefaultPins UEdGraphNode function. Override. Given the node context (this), create all the required pins. @param RemapPins remap pins action. Use this object to save any information required to later perform the remap pins action. Can be null.
- L404 _protected prototype_ `virtual UCustomizableObjectNodeRemapPins* CreateRemapPinsDefault() const;` — Creates and returns the node default node remap pins action. By default all nodes remap by name. Override if a node requires a different default remap pins action.
- L411 _protected prototype_ `virtual UCustomizableObjectNodeRemapPinsByName* CreateRemapPinsByName() const;` — Creates and returns a remap pins by name action. Override a if a node requires an specialized remap pins by name.
- L418 _protected prototype_ `virtual UCustomizableObjectNodeRemapPinsByPosition* CreateRemapPinsByPosition() const;` — Creates and returns a remap pins by position action. Override a if a node requires an specialized remap pins by position.
- L422 _protected prototype_ `virtual void RemapPin(UEdGraphPin& NewPin, const UEdGraphPin& OldPin);` — Allows to perform work when remapping a pin. Copies pin data from old pin to new pin. Keeps the id of the new pin.
- L425 _protected prototype_ `virtual void RemapPins(const TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap);` — Allows to perform work when remapping a pin.
- L428 _protected prototype_ `virtual void RemapPinsData(const TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap);` — Allows to perform work when remapping the pin data.
- L431 _protected prototype_ `void AddPinData(const UEdGraphPin& Pin, UCustomizableObjectNodePinData& PinData);` — Attach data to a given pin.
- L435 _public prototype_ `virtual bool IsExperimental() const;` — Return true to mark this node as experimental.
- L438 _public prototype_ `virtual bool IsDeprecated() const override;` — Return true to mark this node as deprecated. Deprecated nodes emit a compile-time warning.
- L440 _public prototype_ `virtual bool IsLoaded() const;`
- L447 _private member_ `TMap<FGuid, TObjectPtr<UCustomizableObjectNodePinData>> PinsDataId;` — `UPROPERTY()` — Data attached to a given pin. Not all pins contain data. Data must be eliminated once the pins is removed. This is done automatically on CustomRemovePin. Do not use RemovePin since it will not remove the data.
- L451 _private member_ `TMap<FEdGraphPinReference, TObjectPtr<UCustomizableObjectNodePinData>> PinsData_DEPRECATED;` — `UPROPERTY()` — Deprecated properties in favour of PinsDataId

#### struct `UCustomizableObjectNode::FAttachedErrorDataView`  
`struct FAttachedErrorDataView`  
_L205-208_
- L207 _public member_ `TArrayView<const float> UnassignedUVs;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CUSTOMIZABLEOBJECTEDITOR_API`
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPostEditChangePropertyDelegate, UObject*, FPropertyChangedEvent&);`
- L109 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPostEditChangePropertyDelegate, UObject*, FPropertyChangedEvent&);`
- L111 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPostReconstructNodeDelegate);`
- L111 _prototype_ `DECLARE_MULTICAST_DELEGATE(FPostReconstructNodeDelegate);`
- L113 _delegate_ `DECLARE_MULTICAST_DELEGATE(FNodeConnectionListChangedDelegate);`
- L113 _prototype_ `DECLARE_MULTICAST_DELEGATE(FNodeConnectionListChangedDelegate);`
- L115 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPinConnectionListChangedDelegate, UEdGraphPin*);`
- L115 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPinConnectionListChangedDelegate, UEdGraphPin*);`
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPostEditablePinNameChangedDelegate, const UEdGraphPin&, const FText NewContent);`
- L117 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPostEditablePinNameChangedDelegate, const UEdGraphPin&, const FText NewContent);`
- L119 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDestroyNodeDelegate);`
- L119 _prototype_ `DECLARE_MULTICAST_DELEGATE(FDestroyNodeDelegate);`
- L121 _typedef_ `using FRemapPinsDelegateParameter = TMap<UEdGraphPin*, UEdGraphPin*>;` — Required for the delegate macro.
- L122 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRemapPinsDelegate, const FRemapPinsDelegateParameter&);`
- L122 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRemapPinsDelegate, const FRemapPinsDelegateParameter&);`
- L463 _function_ `template<class FNodeType> FNodeType* GetCustomizableObjectExternalNode(UCustomizableObject* Object, const FGuid& NodeGuid)` — Return the specified node located in another Customizable Object graph. @param Customizable Object object to look for the node. If nulltpr, it returns nullptr. @param NodeGuid node guid. If invalid, it returns nullptr. Return nullptr if not found.

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/Nodes/CustomizableObjectNodeExtensionDataConstant.h` (Public)


#### class `UCustomizableObjectNodeExtensionDataConstant`  
`class UCustomizableObjectNodeExtensionDataConstant : public UCustomizableObjectNode`  
_L15-21_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UCustomizableObjectNode`
- desc: A base class for nodes that output a constant FExtensionData. This is typically used to import an Unreal asset into the Customizable Object graph.
- L20 _public function_ `virtual bool IsAffectedByLOD() const override`

### `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/RemapPins/CustomizableObjectNodeRemapPins.h` (Public)


#### class `UCustomizableObjectNodeRemapPins`  
`class UCustomizableObjectNodeRemapPins : public UObject`  
_L19-36_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Remap pins action interface. Do not implement any functions or members directly, use inheritance. As an example, see UCustomizableObjectNodeRemapPinsByName class. If data needs to be passed between ReconstructNode and AllocateDefaultPins, use the derived class context to save it.
- L35 _public function_ `virtual void RemapPins(const UCustomizableObjectNode& Node, const TArray<UEdGraphPin*>& OldPins, const TArray<UEdGraphPin*>& NewPins, TMap<UEdGraphPin*, UEdGraphPin*>& PinsToRemap, TArray<UEdGraphPin*>& PinsToOrphan)` — Remap existing connections from old pins to new pins. Use MovePersistentDataFromOldPin from this file to copy the links from the old node to the new node. @param OldPins Old pins which are no longer present in the node. @param NewPins Current node pins. @param PinsToRemap Out parameter. Remapping pairs. Key is the old pin while value is the new pin. From pin has to be a pin from the NewPins, while FromPin has to be a pin from OldPins. @param PinsToOrphan Out Parameter. List of pins which will be marked as orphaned. Only pins from OldPins must be added.
