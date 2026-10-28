# Runtime / DataflowEngine

- module root: `Source/Runtime/Dataflow/Engine`
- headers: 29; symbols: 906
- symbol kinds: class=19, delegate=10, enum=6, enumerator=17, function=102, macro=7, member=197, namespace=55, prototype=442, struct=41, typedef=10
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, DataflowCore, Engine, GeometryCore, ImageCore, SlateCore

### `Source/Runtime/Dataflow/Engine/Private/Dataflow/DataflowAssetPathNodes.h` (Private)


#### struct `FDataflowGetAssetPathNode`  
`struct FDataflowGetAssetPathNode : public FDataflowNode`  
_L17-37_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get the path from an asset If no asset is specified via the input or in the properties the asset bound to the dataflow will be used
- L28 _public member_ `FString Path;` — `UPROPERTY(meta = (DataflowOutput))`
- L30 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L33 _public prototype_ `FDataflowGetAssetPathNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L35 _public prototype_ `virtual bool SupportsAssetProperty(UObject* InAsset) const override;`
- L36 _public prototype_ `virtual void SetAssetProperty(UObject* InAsset) override;`

#### enum `EDataflowPathReplaceMethod`  
`enum class EDataflowPathReplaceMethod: uint8`  
_L42-47_
- reflection: `UENUM()`
- L44 _public enumerator_ `Anywhere`
- L45 _public enumerator_ `Beginning`
- L46 _public enumerator_ `End`

#### struct `FDataflowPathReplaceRule`  
`struct FDataflowPathReplaceRule`  
_L50-73_
- reflection: `USTRUCT()`
- L57 _public member_ `EDataflowPathReplaceMethod Method = EDataflowPathReplaceMethod::Anywhere;` — `UPROPERTY(EditAnywhere, Category = Rule)` — Method to use to find the From string
- L61 _public member_ `FString From;` — `UPROPERTY(EditAnywhere, Category = Rule)` — String to find and replace
- L65 _public member_ `FString To;` — `UPROPERTY(EditAnywhere, Category = Rule)` — String to use as a replacement
- L68 _public member_ `bool bIgnoreCase = true;` — `UPROPERTY(EditAnywhere, Category = Rule)`
- L72 _public member_ `bool bInsertIfNoFound = false;` — `UPROPERTY(EditAnywhere, Category = Rule, meta = (EditCondition = "Method == EDataflowPathReplaceMethod::Beginning || EDataflowPathReplaceMethod::End"))` — if true insert the string even if not found ( only for Beginning and End methods )

#### struct `FDataflowPathReplaceNode`  
`struct FDataflowPathReplaceNode : public FDataflowNode`  
_L80-110_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Replace part of a path The path is assumed to have the form  Path/Names ( Path can have multiple / and folders and Names can have multiple names seperated by a .)
- L88 _private member_ `FString Path;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Path))` — Path to modify and return
- L95 _private member_ `TArray<FDataflowPathReplaceRule> PathRules;` — `UPROPERTY(EditAnywhere, Category = Rules, meta = (TitleProperty = "'{From}' -> '{To}' [{Method}]"))` — Rules to apply to the folder part of the path Note that Rules are applied in order
- L102 _private member_ `TArray<FDataflowPathReplaceRule> NameRules;` — `UPROPERTY(EditAnywhere, Category = Rules, meta=(TitleProperty = "'{From}' -> '{To}' [{Method}]"))` — Rules to apply to the name part of the path Note that Rules are applied in order
- L104 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L106 _private prototype_ `FString ApplyRule(const FString& InString, const FDataflowPathReplaceRule& Rule) const;`
- L109 _public prototype_ `FDataflowPathReplaceNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L114 _namespace_ `namespace UE`
- L114 _namespace_ `namespace Dataflow` (scope `UE`)
- L116 _prototype_ `void RegisterAssetPathNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Private/Dataflow/DataflowCompiler.h` (Private)


#### struct `UE::Dataflow::FCompilerParameters`  
`struct FCompilerParameters`  
_L27-32_
- desc: Dataflow compiler takes a UDataflowGraph and build a representation of the graph execution and stores it into compiled graph objects the compiled graph are only valid for the topology of the graph at the time of compilation
- L30 _public member_ `bool bRemoveDeadEnds = true;`
- L31 _public member_ `TWeakObjectPtr<const UDataflow> DataflowObjectToCompile;`

#### struct `UE::Dataflow::FCompilerMessage`  
`struct FCompilerMessage`  
_L34-40_
- L36 _public member_ `EMessageSeverity::Type Severity = EMessageSeverity::Info;`
- L37 _public member_ `FGuid Node;`
- L38 _public member_ `FGuid Output;`
- L39 _public member_ `FText Text;`

#### struct `UE::Dataflow::FCompilerResults`  
`struct FCompilerResults`  
_L42-74_
- L45 _public prototype_ `bool Succedded() const;`
- L46 _public prototype_ `bool Failed() const;`
- L48 _public prototype_ `void AddMessage(EMessageSeverity::Type InSeverity, const FGuid& InNode, const FGuid& InOutput, const FText& Text);`
- L50 _public function_ `void AddCompiledGraph(const UObject* GraphObject, TSharedRef<FCompiledGraph> CompiledGraph)`
- L56 _public function_ `TSharedPtr<const FCompiledGraph> GetCompiledGraph(const UObject* GraphObject) const`
- L62 _public function_ `const TMap<const UObject*, TSharedRef<FCompiledGraph>> GetCompiledGraphs() const`
- L64 _public function_ `double GetCompilationTimeMs() const`
- L69 _private member_ `double CompilationTimeMs = 0;`
- L70 _private member_ `int32 NumErrors = 0;`
- L71 _private member_ `int32 NumWarnings = 0;`
- L72 _private member_ `TArray<FCompilerMessage> Messages;`
- L73 _private member_ `TMap<const UObject*, TSharedRef<FCompiledGraph>> CompiledGraphs;`

#### struct `UE::Dataflow::FCompiler`  
`struct FCompiler`  
_L76-85_
- L79 _public prototype_ `static bool Compile(const FCompilerParameters& Params, FCompilerResults& Results);`
- L81 _public prototype_ `static bool CompileGraph(const UEdGraph& GraphObject, const FCompilerParameters& Params, FCompilerResults& Results);`
- L82 _public prototype_ `static void FindStartNodes(const UEdGraph& GraphObject, TArray<FConstNodeRef>& OutStartNodes);`
- L83 _public prototype_ `static void FindDownstreamNodes(const FConstNodeRef& Node, TArray<FConstNodeRef>& OutDownstreamNodes);`
- L84 _public prototype_ `static void FindUpstreamNodes(const FConstNodeRef& Node, TArray<FConstNodeRef>& OutUpstreamNodes);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Dataflow` (scope `UE`)
- L21 _typedef_ `using FConstNodeRef = TSharedRef<const FDataflowNode>;` (scope `UE::Dataflow`)
- L22 _typedef_ `using FConstNodePtr = TSharedPtr<const FDataflowNode>;` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Private/Dataflow/DataflowEngineLogPrivate.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Dataflow/Engine/Private/Dataflow/DataflowSkeletonNodes.h` (Private)


#### struct `FMergeSkeletonsDataflowNode`  
`struct FMergeSkeletonsDataflowNode : public FDataflowNode`  
_L14-40_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Merges an array of skeletons into a single skeleton
- L26 _public member_ `FVector SharedRootPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Skeleton, meta = (DataflowInput))` — World-space position of the shared root bone added to the merged skeleton
- L30 _public member_ `bool bPreserveBoneNames = true;` — `UPROPERTY(EditAnywhere, Category = Skeleton, meta = (DataflowInput))` — Whether to attempt to preserve the names of the bones from the input skeleton. Otherwise, bones will be simply numbered.
- L34 _public member_ `FDataflowSkeleton MergedSkeleton;` — `UPROPERTY(meta = (DataflowOutput))` — The merged skeleton
- L36 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L39 _public prototype_ `FMergeSkeletonsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Dataflow` (scope `UE`)
- L46 _prototype_ `void RegisterSkeletonNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Private/Dataflow/DataflowTextureAssetNodes.h` (Private)


#### struct `FDataflowTextureTerminalNode`  
`struct FDataflowTextureTerminalNode : public FDataflowTerminalNode`  
_L16-33_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: terminal node to a save a dependent 2D texture
- L26 _public member_ `TObjectPtr<UTexture2D> TextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TextureAsset"))`
- L28 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L29 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L32 _public prototype_ `FDataflowTextureTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowTexture2DTerminalNode`  
`struct FDataflowTexture2DTerminalNode : public FDataflowTerminalNode`  
_L40-63_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node to a save a dependent 2D texture The terminal node will create an asset if it does not exists yet
- L48 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowInput))` — Image data to store in the texture
- L52 _private member_ `FString AssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the texture asset to create or update
- L56 _private member_ `TObjectPtr<UTexture2D> TextureAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Texture asset matching AssetPath and updated with the image data
- L58 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L59 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L62 _public prototype_ `FDataflowTexture2DTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowGetTextureAssetNode`  
`struct FDataflowGetTextureAssetNode : public FDataflowNode`  
_L69-85_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowNode`
- desc: Get a texture asset
- L76 _private member_ `TObjectPtr<UTexture2D> TextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowOutput))`
- L78 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L81 _public prototype_ `FDataflowGetTextureAssetNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L83 _public prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L84 _public prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`

#### struct `FDataflowGetTextureAssetFromPathNode`  
`struct FDataflowGetTextureAssetFromPathNode : public FDataflowNode`  
_L91-110_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowNode`
- desc: Get a texture asset from a path
- L98 _private member_ `FString TexturePath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))`
- L101 _private member_ `TObjectPtr<UTexture2D> TextureAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))`
- L103 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L106 _public prototype_ `FDataflowGetTextureAssetFromPathNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L108 _public prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L109 _public prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`

#### struct `FDataflowTextureToImageNode`  
`struct FDataflowTextureToImageNode : public FDataflowNode`  
_L116-136_
- reflection: `USTRUCT(Meta = (Experimental))`
- inherits: `FDataflowNode`
- desc: Import a texture asset as an image. Texture must have CPU availability.
- L123 _public prototype_ `FDataflowTextureToImageNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L128 _private member_ `TObjectPtr<UTexture2D> TextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta = (DataflowInput))`
- L131 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowOutput))`
- L134 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowImageToTextureNode`  
`struct FDataflowImageToTextureNode : public FDataflowNode`  
_L143-162_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowNode`
- desc: Create a transient texture asset from an image
- L150 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L153 _private member_ `FName TextureName;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta = (DataflowInput))`
- L156 _private member_ `TObjectPtr<UTexture2D> TransientTexture = nullptr;` — `UPROPERTY(meta = (DataflowOutput))`
- L158 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L161 _public prototype_ `FDataflowImageToTextureNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L166 _namespace_ `namespace UE`
- L166 _namespace_ `namespace Dataflow` (scope `UE`)
- L168 _prototype_ `void RegisterTextureAssetNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowAttachment.h` (Public)


#### class `UDataflowAttachment`  
`class UDataflowAttachment : public UAssetUserData, public IDataflowContentOwner, public IDataflowInstanceInterface`  
_L23-59_
- reflection: `UCLASS(MinimalApi, Abstract)`
- inherits: `UAssetUserData,IDataflowContentOwner,IDataflowInstanceInterface`
- desc: Generic dataflow instance attachment implemented as a user asset data object so it can be embedded inside any asset that is a user-data container. This allows assets in modules that do not, or cannot know about dataflow (e.g. Engine module assets) to contain a dataflow attachment. Using a modular feature implementation this data can be grabbed as an asset opens and a plugin specific implementation can be used for the asset editor (see FDataflowPhysicsAssetEditorOverride)
- L29 _public prototype_ `UDataflowAttachment();`
- L32 _public prototype_ `void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override PURE_VIRTUAL( UDataflowAttachment::WriteDataflowContent, );` — IDataflowContentOwner
- L33 _public prototype_ `void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override PURE_VIRTUAL( UDataflowAttachment::ReadDataflowContent, );`
- L37 _public prototype_ `const FDataflowInstance& GetDataflowInstance() const override;` — IDataflowInstanceInterface
- L38 _public prototype_ `FDataflowInstance& GetDataflowInstance() override;`
- L42 _public prototype_ `virtual void PostLoad() override;` — UObject
- L46 _public prototype_ `virtual FString GetPreviewActorPath() const;` — Provides trhe path to the preview actor to be used in the corresponding Dataflow editor
- L52 _private member_ `FDataflowInstance Instance;` — `UPROPERTY()` — Dataflow instance for the attachment when editing.
- L57 _protected prototype_ `TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override PURE_VIRTUAL( UDataflowAttachment::CreateDataflowContent, return nullptr; );` — IDataflowContentOwner

#### struct `FDataflowAttachmentFactory`  
`struct FDataflowAttachmentFactory`  
_L63-76_
- L66 _public prototype_ `static FDataflowAttachmentFactory& Get();`
- L68 _public typedef_ `using FCreateAttachmentFunction = TFunction<UDataflowAttachment*(UObject*)>;`
- L70 _public prototype_ `void Register(FName ClassName, FCreateAttachmentFunction CreateFunction);`
- L72 _public prototype_ `UDataflowAttachment* Create(UObject* Owner);`
- L75 _private member_ `TMap<FName, FCreateAttachmentFunction> CreateFunctionsByName;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWENGINE_API`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowBlueprintLibrary.h` (Public)


#### struct `FDataflowVariable`  
`struct FDataflowVariable`  
_L13-31_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `FName VariableName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dataflow")`
- L23 _public member_ `EPropertyBagPropertyType Type = EPropertyBagPropertyType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dataflow")`
- L26 _public member_ `EPropertyBagContainerType ContainerType = EPropertyBagContainerType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dataflow")`
- L29 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dataflow")`

#### class `UDataflowBlueprintLibrary`  
`class UDataflowBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L35-122_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L44 _public prototype_ `static void EvaluateTerminalNodeByName(UDataflow* Dataflow, FName TerminalNodeName, UObject* ResultAsset);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Find a specific terminal node by name evaluate it using a specific UObject
- L55 _public prototype_ `static bool EvaluateDataflow(UDataflow* Dataflow, UObject* AssetToUpdate);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — s Evaluate a dataflow for a sepcific asset This will evaluate all the terminal nodes and generate any dependent asset if necessary This is synchronous operation, so large dataflow may block the game thread for a while when calling it @param Dataflow Dataflow asset to evaluate @param AssetToUpdate Asset to update from the Dataflow ( if a terminal exists for this type of asset ) @return true if the evaluate executed with no errors
- L62 _public prototype_ `static bool RegenerateAssetFromDataflow(UObject* AssetToRegenerate, bool bRegenerateDependentAssets = false);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Regenerate an asset using its corresponding dataflow @return true if the asset was regenerated
- L69 _public prototype_ `static bool OverrideDataflowVariableBool(UObject* Asset, FName VariableName, bool VariableValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override a Boolean dataflow variable for a specific asset @return true if the override was successful
- L76 _public prototype_ `static bool OverrideDataflowVariableBoolArray(UObject* Asset, FName VariableName, const TArray<bool>& VariableArrayValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override an Boolean Array dataflow variable for a specific asset @return true if the override was successful
- L83 _public prototype_ `static bool OverrideDataflowVariableInt(UObject* Asset, FName VariableName, int64 VariableValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override an Integer dataflow variable for a specific asset @return true if the override was successful
- L90 _public prototype_ `static bool OverrideDataflowVariableIntArray(UObject* Asset, FName VariableName, const TArray<int32>& VariableArrayValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override an Integer Array dataflow variable for a specific asset @return true if the override was successful
- L97 _public prototype_ `static bool OverrideDataflowVariableFloat(UObject* Asset, FName VariableName, float VariableValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override a Float dataflow variable for a specific asset @return true if the override was successful
- L104 _public prototype_ `static bool OverrideDataflowVariableFloatArray(UObject* Asset, FName VariableName, const TArray<float>& VariableArrayValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override a Float Array dataflow variable for a specific asset @return true if the override was successful
- L111 _public prototype_ `static bool OverrideDataflowVariableObject(UObject* Asset, FName VariableName, UObject* VariableValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override an Unreal Object dataflow variable for a specific asset @return true if the override was successful
- L118 _public prototype_ `static bool OverrideDataflowVariableObjectArray(UObject* Asset, FName VariableName, const TArray<UObject*>& VariableArrayValue);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))` — Override an Unreal Object Array dataflow variable for a specific asset @return true if the override was successful
- L121 _public prototype_ `static TArray<FDataflowVariable> GetDataflowVariableList(UObject* Asset);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow", meta = (Keywords = "Dataflow graph"))`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowColorRamp.h` (Public)


#### struct `FDataflowColorCurveOwner`  
`struct UE_DEPRECATED(5.8, "FDataflowColorCurveOwner is deprecated, use the FLinearColorRamp instead") FDataflowColorCurveOwner : public FCurveOwnerInterface`  
_L13-42_
- inherits: `FCurveOwnerInterface`
- L16 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorCurveChanged, TArray<FRichCurve*> );`
- L19 _public prototype_ `void SetColorAtTime(float Time, const FLinearColor& Color, bool bOnlyRBG);`
- L21 _public prototype_ `bool IsEmpty() const;`
- L24 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;`
- L25 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L26 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L27 _public prototype_ `virtual void ModifyOwner() override;`
- L28 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L29 _public prototype_ `virtual void MakeTransactional() override;`
- L30 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L31 _public prototype_ `virtual bool IsLinearColorCurve() const override;`
- L32 _public prototype_ `virtual FLinearColor GetLinearColorValue(float InTime) const override;`
- L33 _public prototype_ `virtual bool HasAnyAlphaKeys() const override;`
- L34 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L35 _public prototype_ `virtual FLinearColor GetCurveColor(FRichCurveEditInfo CurveInfo) const override;`
- L38 _public member_ `FOnColorCurveChanged OnColorCurveChangedDelegate;`
- L41 _private member_ `FRichCurve RichCurves[4];`

#### struct `FDataflowColorRamp`  
`struct UE_DEPRECATED(5.8, "FDataflowColorRamp is deprecated, use the FLinearColorRamp instead") FDataflowColorRamp`  
_L45-52_
- reflection: `USTRUCT()`
- L50 _public member_ `FDataflowColorCurveOwner ColorRamp;`

#### struct `FDataflowLinearColorRamp`  
`struct UE_DEPRECATED(5.8, "FDataflowLinearColorRamp is deprecated, use the FLinearColorRamp instead") FDataflowLinearColorRamp #if CPP : public FCurveOwnerInterface #endif`  
_L55-89_
- reflection: `USTRUCT()`
- inherits: `FCurveOwnerInterface`
- L63 _public prototype_ `void SetColorAtTime(float Time, const FLinearColor& Color, bool bOnlyRBG);`
- L64 _public prototype_ `bool IsEmpty() const;`
- L65 _public prototype_ `void Reset();`
- L66 _public prototype_ `void SetFrom(const FDataflowLinearColorRamp& Other);`
- L68 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorCurveChanged, TArray<FRichCurve*> );`
- L69 _public member_ `FOnColorCurveChanged OnColorCurveChangedDelegate;`
- L72 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;`
- L73 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L74 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L75 _public prototype_ `virtual void ModifyOwner() override;`
- L76 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L77 _public prototype_ `virtual void MakeTransactional() override;`
- L78 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L79 _public prototype_ `virtual bool IsLinearColorCurve() const override;`
- L80 _public prototype_ `virtual FLinearColor GetLinearColorValue(float InTime) const override;`
- L81 _public prototype_ `virtual bool HasAnyAlphaKeys() const override;`
- L82 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L83 _public prototype_ `virtual FLinearColor GetCurveColor(FRichCurveEditInfo CurveInfo) const override;`
- L88 _private member_ `FRichCurve RichCurves[4];` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAFLOWENGINE_API`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorCurveChanged, TArray<FRichCurve*> );`
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorCurveChanged, TArray<FRichCurve*> );`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowContent.h` (Public)


#### class `UDataflowContentOwner`  
`class UDataflowContentOwner : public UInterface`  
_L31-34_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IDataflowContentOwner`  
`class IDataflowContentOwner`  
_L39-70_
- desc: Dataflow interface for any content owner
- L46 _public prototype_ `TObjectPtr<UDataflowBaseContent> BuildDataflowContent();` — Function to build the dataflow content
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnContentOwnerChanged);` — Notification when owner changed
- L52 _public member_ `FOnContentOwnerChanged OnContentOwnerChanged;` — Delegate member to be called in the invalidate
- L55 _public function_ `void InvalidateDataflowContents() const` — Invalidate all the dataflow contents
- L61 _public prototype_ `virtual void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const = 0;` — Interface to update a dataflow content instance from that owner
- L64 _public prototype_ `virtual void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) = 0;` — Interface to update a dataflow content instance from that owner
- L69 _protected prototype_ `virtual TObjectPtr<UDataflowBaseContent> CreateDataflowContent() = 0;` — Interface to create a dataflow content instance from that owner

#### class `UDataflowBaseContent`  
`class UDataflowBaseContent : public UDataflowContextObject`  
_L76-188_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowContextObject`
- desc: Dataflow content owning dataflow asset that that will be used to evaluate the graph
- L81 _public prototype_ `UDataflowBaseContent();`
- L82 _public prototype_ `~UDataflowBaseContent();`
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContentDataChanged, TObjectPtr<AActor>& SimulationActor);` — Notification when content data changed
- L88 _public member_ `FOnContentDataChanged OnContentDataChanged;` — Delegate member to be called when data is changed
- L94 _public function_ `bool IsConstructionDirty() const` — Dirty - State Invalidation Check if non-graph specific data has been changed, this usually requires a re-render
- L95 _public prototype_ `void SetConstructionDirty(bool InDirty);`
- L97 _public function_ `bool IsSimulationDirty() const`
- L98 _public prototype_ `void SetSimulationDirty(bool InDirty);`
- L104 _public prototype_ `void SetLastModifiedTimestamp(UE::Dataflow::FTimestamp InTimestamp, bool bMakeDirty =true);` — LastModifiedTimestamp - State Invalidation Dataflow timestamp accessors can be used to see if the EvaluationContext has been invalidated.
- L105 _public function_ `const UE::Dataflow::FTimestamp& GetLastModifiedTimestamp() const`
- L111 _public prototype_ `virtual void SetDataflowContext(const TSharedPtr<UE::Dataflow::FEngineContext>& InContext) override;` — Context - Dataflow Evaluation State Dataflow context stores the evaluated state of the graph.
- L114 _public prototype_ `void UpdateContentDatas();` — Rebuild the owner dependent datas
- L117 _public function_ `virtual void AddContentObjects(FReferenceCollector& Collector)` — Collect reference objects for GC
- L120 _public prototype_ `virtual void SetActorProperties(TObjectPtr<AActor>& PreviewActor) const;` — Set all the preview actor exposed properties
- L123 _public prototype_ `void SetDataflowOwner(const TObjectPtr<UObject>& InOwner);` — Data flow owner accessors (through the context)
- L124 _public prototype_ `TObjectPtr<UObject> GetDataflowOwner() const;`
- L127 _public prototype_ `virtual void SetDataflowAsset(const TObjectPtr<UDataflow>& InAsset) override;` — Data flow asset accessors (through the context)
- L130 _public function_ `void SetDataflowTerminal(const FString& InPath)` — Data flow terminal accessors
- L131 _public function_ `const FString& GetDataflowTerminal() const`
- L134 _public function_ `void SetTerminalAsset(const TObjectPtr<UObject>& InAsset)` — Terminal asset accessors
- L135 _public function_ `const TObjectPtr<UObject>& GetTerminalAsset() const`
- L138 _public function_ `void SetPreviewClass(const TSubclassOf<AActor>& InPreviewClass)` — Preview class accessors
- L139 _public function_ `const TSubclassOf<AActor>& GetPreviewClass() const`
- L142 _public prototype_ `virtual void Serialize(FArchive& Ar);` — Content Serialization
- L145 _public function_ `bool IsSaved() const` — Context cache saving
- L146 _public function_ `void SetIsSaved(bool bInSaved)`
- L149 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L152 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L159 _protected member_ `FString DataflowTerminal;` — `UPROPERTY(Transient, SkipSerialization)` — Data flow terminal path for evaluation
- L163 _protected member_ `TObjectPtr<UObject> TerminalAsset = nullptr;` — `UPROPERTY(Transient, SkipSerialization)` — Data flow terminal path for evaluation
- L166 _protected member_ `UE::Dataflow::FTimestamp LastModifiedTimestamp = UE::Dataflow::FTimestamp::Invalid;` — Last data flow evaluated node time stamp
- L170 _protected member_ `bool bIsConstructionDirty = true;` — `UPROPERTY()` — Dirty flag to trigger rendering. Do we need that? since when accessing the member by non const ref we will not dirty it
- L174 _protected member_ `bool bIsSimulationDirty = true;` — `UPROPERTY()` — Dirty flag to reset the simulation if necessary
- L177 _protected member_ `bool bIsSaved = false;` — Saved as a cached context. Will be automatically saved to a cache directory if true. Use the pvar p.Dataflow.Editor.ContextCaching to enable. [def:false]
- L180 _protected member_ `TSubclassOf<AActor> PreviewClass;` — Preview actor class that could be used to visualize the result
- L183 _protected prototype_ `static void OverrideActorProperty(const TObjectPtr<AActor>& PreviewActor, TObjectPtr<UObject> PropertyValue, const FName& PropertyName);` — override actor properties from BP
- L187 _protected prototype_ `template<typename StructType> static void OverrideStructProperty(const TObjectPtr<AActor>& PreviewActor, const StructType& PropertyValue, const FName& PropertyName);` — override struct properties from BP
- L191 _function_ `template<typename StructType> void UDataflowBaseContent::OverrideStructProperty(const TObjectPtr<AActor>& PreviewActor, const StructType& PropertyValue, const FName& PropertyName)`

#### class `UDataflowSkeletalContent`  
`class UDataflowSkeletalContent : public UDataflowBaseContent`  
_L215-268_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowBaseContent`
- desc: Dataflow content owning dataflow and skelmesh assets that that will be used to evaluate the graph
- L220 _public prototype_ `UDataflowSkeletalContent();`
- L221 _public prototype_ `virtual ~UDataflowSkeletalContent() override= default;`
- L224 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L225 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L229 _public prototype_ `virtual void AddContentObjects(FReferenceCollector& Collector) override;` — Collect reference objects for GC
- L232 _public prototype_ `void SetSkeletalMesh(const TObjectPtr<USkeletalMesh>& InMesh, const bool bHideAsset = false);` — Data flow skeletal mesh accessors
- L233 _public function_ `const TObjectPtr<USkeletalMesh>& GetSkeletalMesh() const`
- L236 _public prototype_ `void SetAnimationAsset(const TObjectPtr<UAnimationAsset>& InAnimation, const bool bHideAsset = false);` — Data flow animation asset accessors
- L237 _public function_ `const TObjectPtr<UAnimationAsset>& GetAnimationAsset() const`
- L240 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L243 _public prototype_ `virtual void SetActorProperties(TObjectPtr<AActor>& PreviewActor) const override;` — Set all the preview actor exposed properties
- L248 _protected prototype_ `bool ShouldFilterAnimation(const FAssetData& AssetData) const;` — `UFUNCTION()`
- L253 _protected member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)` — Data flow skeletal mesh
- L257 _protected member_ `bool bListCompatibleAnimationsOnly = true;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)` — Enable animation filtering
- L261 _protected member_ `TObjectPtr<UAnimationAsset> AnimationAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization, meta = (GetAssetFilter = "ShouldFilterAnimation"))` — Animation asset to be used to preview simulation
- L264 _protected member_ `bool bHideSkeletalMesh = false;` — Boolean to control if the skeletal mesh could be edited or not
- L267 _protected member_ `bool bHideAnimationAsset = false;` — Boolean to control if the animation asset could be edited or not

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWENGINE_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DataflowContextHelpers` (scope `UE`)
- L27 _prototype_ `template<class T> TObjectPtr<T> CreateNewDataflowContent(const TObjectPtr<UObject>& ContentOwner);` (scope `UE::DataflowContextHelpers`) — Return a new(or saved) content that can store the execution state of the graph.
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnContentOwnerChanged);` — Notification when owner changed
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContentDataChanged, TObjectPtr<AActor>& SimulationActor);` — Notification when content data changed

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowContextObject.h` (Public)


#### class `UDataflowContextObject`  
`class UDataflowContextObject : public UObject`  
_L26-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L32 _public function_ `void SetSelectedNode(TObjectPtr<UDataflowEdNode> InSelectedNode)` — Selection Collection Access
- L33 _public function_ `TObjectPtr<UDataflowEdNode> GetSelectedNode() const`
- L37 _public function_ `template<typename NodeType> NodeType* GetSelectedNodeOfType() const` — Get a single selected node of the specified type. Return nullptr if the specified node is not selected, or if multiple nodes are selected
- L47 _public function_ `void SetRenderCollection(const TSharedPtr<FManagedArrayCollection>& InCollection)` — Render Collection used to generate the DynamicMesh3D from the selected node
- L48 _public function_ `TSharedPtr<const FManagedArrayCollection> GetRenderCollection() const`
- L51 _public function_ `void SetConstructionViewMode(const UE::Dataflow::IDataflowConstructionViewMode* InMode)` — ViewMode Access
- L52 _public function_ `const UE::Dataflow::IDataflowConstructionViewMode* GetConstructionViewMode() const`
- L58 _public function_ `virtual void SetDataflowContext(const TSharedPtr<UE::Dataflow::FEngineContext>& InDataflowContext)` — Context - Dataflow Evaluation State Dataflow context stores the evaluated state of the graph.
- L59 _public function_ `const TSharedPtr<UE::Dataflow::FEngineContext>& GetDataflowContext() const`
- L60 _public function_ `TSharedPtr<UE::Dataflow::FEngineContext>& GetDataflowContext()`
- L63 _public function_ `virtual void SetDataflowAsset(const TObjectPtr<UDataflow>& InAsset)` — Dataflow Asset
- L64 _public function_ `TObjectPtr<UDataflow> GetDataflowAsset() const`
- L66 _public function_ `TSharedPtr<UE::Dataflow::IDataflowEvaluator> GetDataflowEvalutor() const`
- L69 _public function_ `void SetSelectedCollection(TSharedPtr<const FManagedArrayCollection> InSelectedCollection, bool bInUsingInputCollection)` — Collection passing through the currently selected node and a flag indicating whether it's on a node input or output
- L74 _public function_ `const TSharedPtr<const FManagedArrayCollection> GetSelectedCollection() const`
- L75 _public function_ `bool IsUsingInputCollection() const`
- L77 _public prototype_ `void EvaluateGraph(UE::Dataflow::FOnPostEvaluationFunction OnPostEvaluation);`
- L80 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L85 _protected member_ `TSharedPtr<FManagedArrayCollection> RenderCollection = nullptr;` — Render collection to be used
- L89 _protected member_ `TObjectPtr<UDataflowEdNode> SelectedNode = nullptr;` — `UPROPERTY(Transient, SkipSerialization)` — Node that is selected in the graph
- L92 _protected member_ `const UE::Dataflow::IDataflowConstructionViewMode* ConstructionViewMode = nullptr;` — Construction view mode for the context object @todo(michael) : is it only for construction or for simulation as well
- L95 _protected member_ `TSharedPtr<UE::Dataflow::FEngineContext> DataflowContext = nullptr;` — Engine context (data flow owner/asset) to be used for dataflow evaluation
- L98 _protected member_ `TSharedPtr<UE::Dataflow::IDataflowEvaluator> DataflowEvaluator = nullptr;` — EValuator being used to evaluate the graph
- L102 _protected member_ `TObjectPtr<UDataflow> DataflowGraph = nullptr;` — `UPROPERTY(Transient, SkipSerialization)` — Dataflow graph for evaluation
- L105 _protected member_ `TSharedPtr<const FManagedArrayCollection> SelectedCollection = nullptr;` — Managed Array Collection passing through the currently selected node
- L108 _protected member_ `bool bUsingInputCollection = false;` — Whether the Collection is taken from a node Input (i.e. it's in the the state before node execution)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAFLOWENGINE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Dataflow` (scope `UE`)
- L18 _typedef_ `template<class Base> class TEngineContext;` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowDebugDraw.h` (Public)


#### class `FDataflowDebugDraw`  
`class FDataflowDebugDraw : public IDataflowDebugDrawInterface`  
_L18-76_
- inherits: `IDataflowDebugDrawInterface`
- L22 _public prototype_ `FDataflowDebugDraw(class FDataflowDebugRenderSceneProxy* DebugRenderSceneProxy, IDataflowDebugDrawInterface::FDataflowElementsType& DataflowElements);`
- L24 _public prototype_ `virtual ~FDataflowDebugDraw() = default;`
- L28 _private prototype_ `virtual void SetColor(const FLinearColor& InColor) override;`
- L29 _private prototype_ `virtual void SetPointSize(float Size) override;`
- L30 _private prototype_ `virtual void SetLineWidth(double Width) override;`
- L31 _private prototype_ `virtual void SetWireframe(bool bInWireframe) override;`
- L32 _private prototype_ `virtual void SetShaded(bool bInShaded) override;`
- L33 _private prototype_ `virtual void SetTranslucent(bool bInShadedTranslucent) override;`
- L34 _private prototype_ `virtual void SetForegroundPriority() override;`
- L35 _private prototype_ `virtual void SetWorldPriority() override;`
- L36 _private prototype_ `virtual void ResetAllState() override;`
- L38 _private prototype_ `virtual void ReservePoints(int32 NumAdditionalPoints) override;`
- L39 _private prototype_ `virtual void DrawObject(const TRefCountPtr<IDataflowDebugDrawObject>& Object) override;`
- L40 _private prototype_ `virtual void DrawPoint(const FVector& Position) override;`
- L41 _private prototype_ `virtual void DrawLine(const FVector& Start, const FVector& End) const override;`
- L42 _private prototype_ `virtual void DrawMesh(const IDebugDrawMesh& Mesh) const override;`
- L44 _private prototype_ `virtual void DrawBox(const FVector& Extents, const FQuat& Rotation, const FVector& Center, double UniformScale) const override;`
- L45 _private prototype_ `virtual void DrawSphere(const FVector& Center, double Radius) const override;`
- L46 _private prototype_ `virtual void DrawCapsule(const FVector& Center, const double& Radius, const double& HalfHeight, const FVector& XAxis, const FVector& YAxis, const FVector &ZAxis) const override;`
- L47 _private prototype_ `virtual void DrawText3d(const FString& String, const FVector& Location) const override;`
- L49 _private prototype_ `virtual void DrawOverlayText(const FString& InString) override;`
- L50 _private prototype_ `virtual FString GetOverlayText() const override;`
- L53 _private function_ `virtual IDataflowDebugDrawInterface::FDataflowElementsType& ModifyDataflowElements()` — Dataflow elements non const accessor
- L56 _private function_ `virtual const IDataflowDebugDrawInterface::FDataflowElementsType& GetDataflowElements() const` — Dataflow elements const accessor
- L59 _private member_ `class FDataflowDebugRenderSceneProxy* DebugRenderSceneProxy = nullptr;` — Scene proxy coming from the dataflow debug draw component
- L62 _private member_ `IDataflowDebugDrawInterface::FDataflowElementsType& DataflowElements;` — List of dataflow elements to filled by the debug draw
- L64 _private member_ `FLinearColor Color = FLinearColor::White;`
- L65 _private member_ `double LineWidth = 1.0;`
- L66 _private member_ `float PointSize = 5.0;`
- L67 _private member_ `bool bWireframe = true;`
- L68 _private member_ `bool bShaded = false;`
- L69 _private member_ `bool bTranslucent = false;`
- L70 _private member_ `ESceneDepthPriorityGroup PriorityGroup = SDPG_World;`
- L72 _private member_ `FLinearColor ColorWithTranslucency = FLinearColor::White;`
- L73 _private member_ `FDebugRenderSceneProxy::EDrawType DrawType = FDebugRenderSceneProxy::EDrawType::Invalid;`
- L75 _private member_ `TArray<FString> OverlayStrings;`

#### enum `EDataflowDebugDrawRenderType`  
`enum class EDataflowDebugDrawRenderType : uint8`  
_L79-83_
- reflection: `UENUM(BlueprintType)`
- L81 _public enumerator_ `Wireframe UMETA(DisplayName = "Wireframe")`
- L82 _public enumerator_ `Shaded UMETA(DisplayName = "Shaded")`

#### struct `FDataflowNodeDebugDrawSettings`  
`struct FDataflowNodeDebugDrawSettings`  
_L89-106_
- reflection: `USTRUCT()`
- desc: DebugDraw basic common settings
- L94 _public member_ `EDataflowDebugDrawRenderType RenderType = EDataflowDebugDrawRenderType::Wireframe;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")`
- L97 _public member_ `bool bTranslucent = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (EditCondition = "RenderType==EDataflowDebugDrawRenderType::Shaded", EditConditionHides))`
- L100 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")`
- L103 _public member_ `float LineWidthMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0.1", ClampMax = "10.0"))`
- L105 _public prototype_ `void SetDebugDrawSettings(IDataflowDebugDrawInterface& DataflowRenderingInterface) const;`

#### enum `EDataflowSphereCoveringColorMethod`  
`enum class EDataflowSphereCoveringColorMethod : uint8`  
_L112-117_
- reflection: `UENUM(BlueprintType)`
- desc: SphereCovering DebugDraw basic common settings
- L114 _public enumerator_ `Single UMETA(DisplayName = "Single Color")`
- L115 _public enumerator_ `ColorByRadius UMETA(DisplayName = "Color by Radius")`
- L116 _public enumerator_ `Random UMETA(DisplayName = "Random Colors")`

#### struct `FDataflowNodeSphereCoveringDebugDrawSettings`  
`struct FDataflowNodeSphereCoveringDebugDrawSettings`  
_L120-152_
- reflection: `USTRUCT()`
- L126 _public member_ `bool bDisplaySphereCovering = false;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering")` — Display sphere covering
- L129 _public member_ `EDataflowDebugDrawRenderType RenderType = EDataflowDebugDrawRenderType::Wireframe;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering")`
- L132 _public member_ `bool bTranslucent = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (EditCondition = "RenderType==EDataflowDebugDrawRenderType::Shaded", EditConditionHides))`
- L135 _public member_ `float LineWidthMultiplier = .25f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ClampMin = "0.1", ClampMax = "10.0"))`
- L138 _public member_ `EDataflowSphereCoveringColorMethod ColorMethod = EDataflowSphereCoveringColorMethod::Single;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering")`
- L141 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (EditCondition = "ColorMethod == EDataflowSphereCoveringColorMethod::Single", EditConditionHides))`
- L145 _public member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ClampMin = "0", EditCondition = "ColorMethod == EDataflowSphereCoveringColorMethod::Random", EditConditionHides))` — Random seed
- L148 _public member_ `FLinearColor ColorA = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (EditCondition = "ColorMethod == EDataflowSphereCoveringColorMethod::ColorByRadius", EditConditionHides))`
- L151 _public member_ `FLinearColor ColorB = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (EditCondition = "ColorMethod == EDataflowSphereCoveringColorMethod::ColorByRadius", EditConditionHides))`

#### Free symbols / members of external scopes

- L154 _function_ `static void SetWireframeRender(IDataflowDebugDrawInterface& DataflowRenderingInterface)`
- L160 _function_ `static void SetShadedRender(IDataflowDebugDrawInterface& DataflowRenderingInterface)`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowDebugDrawComponent.h` (Public)


#### class `UDataflowDebugDrawComponent`  
`class UDataflowDebugDrawComponent : public UDebugDrawComponent`  
_L12-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDebugDrawComponent`
- L17 _private prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L18 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

#### class `FDataflowDebugRenderSceneProxy`  
`class FDataflowDebugRenderSceneProxy final : public FDebugRenderSceneProxy`  
_L21-58_
- inherits: `FDebugRenderSceneProxy`
- L25 _public prototype_ `FDataflowDebugRenderSceneProxy(const UPrimitiveComponent* InComponent);`
- L28 _public prototype_ `void ClearAll();` — Remove all primitives stored on this proxy
- L39 _public prototype_ `void AddPoint(const FDebugPoint& Point);` — Add point to the scene proxy
- L42 _public prototype_ `void AddObject(const TRefCountPtr<IDataflowDebugDrawObject>& Object);` — Add dataflow object to the scene proxy
- L45 _public prototype_ `void ReservePoints(int32 NumAdditionalPoints);` — Reserve the number of points to add
- L50 _private member_ `TArray<FDebugPoint> Points;`
- L53 _private member_ `TArray<TRefCountPtr<IDataflowDebugDrawObject>> Objects;` — List of user provided dataflow objects to draw
- L56 _private prototype_ `virtual void GetDynamicMeshElementsForView(const FSceneView* View, const int32 ViewIndex, const FSceneViewFamily& ViewFamily, const uint32 VisibilityMap, FMeshElementCollector& Collector, FMaterialCache& DefaultMaterialCache, FMaterialCache& SolidMeshMaterialCache) const override;`
- L57 _private prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`

#### struct `FDataflowDebugRenderSceneProxy::FDebugPoint`  
`struct FDebugPoint`  
_L30-36_
- L32 _public member_ `FVector Position;`
- L33 _public member_ `float Size = 0;`
- L34 _public member_ `FLinearColor Color = FLinearColor::White;`
- L35 _public member_ `ESceneDepthPriorityGroup Priority = ESceneDepthPriorityGroup::SDPG_World;`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowDebugDrawObject.h` (Public)


#### struct `FDataflowDebugDrawBaseObject`  
`struct FDataflowDebugDrawBaseObject : public IDataflowDebugDrawObject`  
_L17-52_
- inherits: `IDataflowDebugDrawObject`
- desc: Dataflow object debug draw parent class
- L19 _public typedef_ `using Super = IDataflowDebugDrawObject;`
- L21 _public function_ `static FName StaticType()`
- L23 _public function_ `FDataflowDebugDrawBaseObject(IDataflowDebugDrawInterface::FDataflowElementsType& InDataflowElements) : IDataflowDebugDrawObject(), DataflowElements(InDataflowElements)`
- L28 _public prototype_ `virtual void PopulateDataflowElements() = 0;` — Populate dataflow elements
- L31 _public prototype_ `virtual void DrawDataflowElements(FPrimitiveDrawInterface* PDI) = 0;` — Debug draw dataflow element
- L34 _public prototype_ `virtual FBox ComputeBoundingBox() const = 0;` — Compute teh dataflow elements bounding box
- L37 _public function_ `virtual bool IsA(FName InType) const override` — Check of the object type
- L45 _protected member_ `IDataflowDebugDrawInterface::FDataflowElementsType& DataflowElements;` — List of dataflow elements the debug draw object is going to populate and render
- L48 _protected member_ `int32 ElementsOffset = 0;` — Elements offset in the global array
- L51 _protected member_ `int32 ElementsSize = 0;` — Elements size in the global array

#### struct `HDataflowElementHitProxy`  
`struct HDataflowElementHitProxy : public HHitProxy`  
_L64-83_
- inherits: `HHitProxy`
- desc: Dataflow hit proxy for viewport selection
- L68 _public function_ `HDataflowElementHitProxy(int32 InElementIndex, FName InElementName) : HHitProxy(HPP_Foreground) , ElementIndex(InElementIndex) , ElementName(InElementName)`
- L75 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L79 _public member_ `int32 ElementIndex;` — Element index to retrieve the matching dataflow element
- L82 _public member_ `FName ElementName;` — Element name to retrieve the matching dataflow element

#### struct `FDataflowProxyElement`  
`struct FDataflowProxyElement : public FDataflowBaseElement`  
_L87-107_
- reflection: `USTRUCT()`
- inherits: `FDataflowBaseElement`
- desc: Proxy dataflow scene element that contains a ref to HDataflowElementHitProxy
- L91 _public function_ `FDataflowProxyElement()`
- L93 _public function_ `FDataflowProxyElement(const FString& InElementName, FDataflowBaseElement* InParentElement, const FBox& InBoundingBox, const bool bInIsConstruction) : FDataflowBaseElement(InElementName, InParentElement, InBoundingBox, bInIsConstruction ), ElementProxy(nullptr)`
- L97 _public member_ `TRefCountPtr<HHitProxy> ElementProxy = nullptr;` — Element proxy used for selection
- L99 _public function_ `static FName StaticType()`
- L102 _public function_ `virtual bool IsA(FName InType) const override` — Check of the element type

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATAFLOWENGINE_API`
- L55 _function_ `template<typename ObjectType, typename... Args> TRefCountPtr<ObjectType> MakeDebugDrawObject(Args&& ... args)`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowDynamicConnections.h` (Public)


#### struct `FDataflowDynamicConnections`  
`struct FDataflowDynamicConnections`  
_L18-60_
- reflection: `USTRUCT()`
- desc: Dynamic connection object allow a node to add dynamic inputs or outputs backed by a strongly typed properties via a property bag
- L29 _public prototype_ `FDataflowDynamicConnections();`
- L30 _public prototype_ `FDataflowDynamicConnections(UE::Dataflow::FPin::EDirection PInDirection, IOwnerInterface* OwnerInterface, UDataflow* DataflowAsset);`
- L32 _public prototype_ `void Refresh();`
- L35 _private typedef_ `using FConnectionReference = UE::Dataflow::TConnectionReference<FDataflowAllTypes>;`
- L36 _private prototype_ `FConnectionReference GetConnectionReference(int32 Index) const;`
- L38 _private prototype_ `bool IsSupportedType(const FPropertyBagPropertyDesc& PropertyDesc);`
- L39 _private prototype_ `FDataflowConnection* CreateConnection(FConnectionReference Connectionreference);`
- L40 _private prototype_ `TArray<FDataflowConnection*> GetDynamicConnections() const;`
- L41 _private prototype_ `void ClearDynamicConnections();`
- L43 _private prototype_ `bool SetConnectionTypeFromPropertyDesc(FDataflowConnection& Connection, const FPropertyBagPropertyDesc& PropertyDesc);`
- L44 _private prototype_ `FName GetCppTypeFromPropertyDesc(const FPropertyBagPropertyDesc& PropertyDesc);`
- L45 _private prototype_ `FDataflowConnection* AddNewConnectionFromPropertyDesc(const FPropertyBagPropertyDesc& PropertyDesc);`
- L49 _private member_ `TArray<FDataflowAllTypes> DynamicProperties;` — `UPROPERTY()`
- L51 _private member_ `TMap<FName, FGuid> ConnectionNameToPropertyId;`
- L53 _private member_ `UE::Dataflow::FPin::EDirection PinDirection = UE::Dataflow::FPin::EDirection::NONE;`
- L54 _private member_ `IOwnerInterface* OwnerInterface;`
- L55 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;`
- L59 _private member_ `bool bIsRefreshing = false;` — used to prevent re-entrance of the refresh function this happens if subgraph  includes a node to itself and am output pin is connected to another node

#### struct `FDataflowDynamicConnections::IOwnerInterface`  
`struct IOwnerInterface`  
_L22-26_
- L24 _public prototype_ `virtual FDataflowNode* GetOwner(const FDataflowDynamicConnections* Caller) = 0;`
- L25 _public prototype_ `virtual const FInstancedPropertyBag& GetPropertyBag(const FDataflowDynamicConnections* Caller) = 0;`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowEdNode.h` (Public)


#### class `UDataflowEdNode`  
`class UDataflowEdNode : public UEdGraphNode`  
_L26-161_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L30 _private member_ `FGuid DataflowNodeGuid;`
- L31 _private member_ `TSharedPtr<UE::Dataflow::FGraph> DataflowGraph;`
- L34 _public function_ `virtual ~UDataflowEdNode()`
- L38 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L41 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L43 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L44 _public prototype_ `virtual bool ShowPaletteIconOnNode() const override;`
- L45 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L46 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L47 _public prototype_ `virtual FText GetTooltipText() const override;`
- L48 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L49 _public prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L50 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L51 _public prototype_ `virtual void OnPinRemoved(UEdGraphPin* InRemovedPin) override;`
- L52 _public prototype_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override;`
- L53 _public prototype_ `virtual void PostEditUndo() override;`
- L54 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L59 _public prototype_ `void Serialize(FArchive& Ar) override;` — UObject interface
- L62 _public function_ `bool IsBound() const`
- L64 _public function_ `TSharedPtr<UE::Dataflow::FGraph> GetDataflowGraph()`
- L65 _public function_ `TSharedPtr<const UE::Dataflow::FGraph> GetDataflowGraph() const`
- L66 _public function_ `void SetDataflowGraph(TSharedPtr<UE::Dataflow::FGraph> InDataflowGraph)`
- L68 _public prototype_ `void UpdatePinsFromDataflowNode();`
- L69 _public prototype_ `void UpdatePinsConnectionsFromDataflowNode();`
- L70 _public prototype_ `void UpdatePinsDefaultValuesFromNode();`
- L72 _public function_ `FGuid GetDataflowNodeGuid() const`
- L73 _public prototype_ `void SetDataflowNodeGuid(FGuid InGuid);`
- L75 _public prototype_ `TSharedPtr<FDataflowNode> GetDataflowNode();`
- L76 _public prototype_ `TSharedPtr<const FDataflowNode> GetDataflowNode() const;`
- L79 _public prototype_ `void AddOptionPin();` — Add a new option pin if the underlying Dataflow node AddPin member is overriden.
- L81 _public prototype_ `void RemoveOptionPin();` — Remove an option pin if the underlying Dataflow node RemovePin member is overriden.
- L83 _public prototype_ `bool PinIsCompatibleWithType(const UEdGraphPin& Pin, const FEdGraphPinType& PinType) const;`
- L87 _public prototype_ `void HideAllInputPins();` — Pin hiding
- L88 _public prototype_ `void ShowAllInputPins();`
- L89 _public prototype_ `void ToggleHideInputPin(FName PinName);`
- L90 _public prototype_ `bool CanToggleHideInputPin(FName PinName) const;`
- L91 _public prototype_ `bool IsInputPinShown(FName PinName) const;`
- L97 _public prototype_ `void SetShouldRenderNode(bool bInRender);` — Node Rendering
- L98 _public function_ `bool ShouldRenderNode() const`
- L100 _public prototype_ `void SetShouldWireframeRenderNode(bool bInRender);`
- L101 _public function_ `bool ShouldWireframeRenderNode() const`
- L103 _public prototype_ `void SetCanEnableWireframeRenderNode(bool bInCanEnable);`
- L104 _public prototype_ `bool CanEnableWireframeRenderNode() const;`
- L106 _public prototype_ `TArray<UE::Dataflow::FRenderingParameter> GetRenderParameters() const;`
- L108 _public prototype_ `void RegisterDelegateHandle();`
- L109 _public prototype_ `void UnRegisterDelegateHandle();`
- L111 _public prototype_ `bool HasAnyWatchedConnection() const;`
- L112 _public prototype_ `bool IsConnectionWatched(const FDataflowConnection& Connection) const;`
- L113 _public prototype_ `void WatchConnection(const FDataflowConnection& Connection, bool Value);`
- L115 _public prototype_ `bool IsPinWatched(const UEdGraphPin* Pin) const;`
- L116 _public prototype_ `void WatchPin(const UEdGraphPin* Pin, bool bWatch);`
- L118 _public prototype_ `static FDataflowConnection* GetConnectionFromPin(const UEdGraphPin* Pin);`
- L119 _public prototype_ `static TSharedPtr<FDataflowNode> GetDataflowNodeFromEdNode(UEdGraphNode* EdNode);`
- L120 _public prototype_ `static TSharedPtr<const FDataflowNode> GetDataflowNodeFromEdNode(const UEdGraphNode* EdNode);`
- L123 _public prototype_ `static bool SupportsEditablePinType(const UEdGraphPin& Pin);`
- L125 _public prototype_ `static TSharedPtr<UE::Dataflow::FGraph> GetDataflowGraphFromPin(const UEdGraphPin& Pin);`
- L126 _public prototype_ `static TSharedPtr<const FDataflowNode> GetDataflowNodeFromPin(const UEdGraphPin& Pin);`
- L127 _public prototype_ `static const FDataflowInput* GetDataflowInputFromPin(const UEdGraphPin& Pin);`
- L128 _public prototype_ `static const FDataflowOutput* GetDataflowOutputFromPin(const UEdGraphPin& Pin);`
- L129 _public prototype_ `static bool CanConnectPins(const UEdGraphPin& OutputPin, const UEdGraphPin& InputPin);`
- L130 _public prototype_ `static bool CanConvertPins(const UEdGraphPin& OutputPin, const UEdGraphPin& InputPin);`
- L132 _public prototype_ `static FSlateIcon GetIconFromNode(const FDataflowNode& Node);`
- L138 _private prototype_ `UEdGraphPin* CreateEdPin(const UE::Dataflow::FPin& Pin);`
- L141 _private prototype_ `void ScheduleNodeInvalidation();`
- L144 _private member_ `bool bEditablePinReentranceGuard = false;` — used to avoid update loops setting and editing the editable pins
- L147 _private member_ `bool bRenderInAssetEditor = false;` — `UPROPERTY(Transient)`
- L150 _private member_ `bool bRenderWireframeInAssetEditor = false;` — `UPROPERTY(Transient)`
- L153 _private member_ `bool bCanEnableRenderWireframe = true;` — `UPROPERTY(Transient)`
- L156 _private member_ `TArray<FGuid> WatchedConnections;` — Store Guids from connection being watched (display values of corresponding output)
- L158 _private prototype_ `void RemoveSpacesInAllPinTypes();`
- L160 _private member_ `FDelegateHandle OnNodeInvalidatedDelegateHandle;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Dataflow` (scope `UE`)
- L23 _namespace_ `namespace GeometryCollection`
- L23 _namespace_ `namespace Facades` (scope `GeometryCollection`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowEngine.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowEngineTypes.h` (Public)


#### struct `FStringValuePair`  
`struct FStringValuePair`  
_L12-25_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `FString Key;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L20 _public member_ `FString Value;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L22 _public function_ `bool operator ==(const FStringValuePair& Other) const`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowEngineUtil.h` (Public)


#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API DATAFLOWENGINE_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Dataflow` (scope `UE`)
- L34 _namespace_ `namespace Reflection` (scope `UE::Dataflow`)
- L37 _function_ `template<class T> const T* FindObjectPtrProperty(const UObject* Owner, FName Name)` (scope `UE::Dataflow::Reflection`)
- L59 _function_ `template<class T> const T FindOverrideProperty(const UObject* Owner, FName PropertyName, FName ArrayKey, const T& Default = T())` (scope `UE::Dataflow::Reflection`)
- L87 _namespace_ `namespace Animation` (scope `UE::Dataflow`)
- L89 _prototype_ `void GlobalTransforms(const FReferenceSkeleton&, TArray<FTransform>& GlobalTransforms);` (scope `UE::Dataflow::Animation`)
- L92 _namespace_ `namespace Color` (scope `UE::Dataflow`)
- L94 _prototype_ `FLinearColor GetRandomColor(const int32 RandomSeed, int32 Idx);` (scope `UE::Dataflow::Color`)
- L97 _namespace_ `namespace Type` (scope `UE::Dataflow`)
- L99 _prototype_ `FPropertyBagPropertyDesc GetPropertyBagPropertyDescFromDataflowType(const FName Name, const FName Type);` (scope `UE::Dataflow::Type`)
- L100 _prototype_ `FPropertyBagPropertyDesc GetPropertyBagPropertyDescFromDataflowConnection(const FDataflowConnection& Connection);` (scope `UE::Dataflow::Type`)
- L101 _prototype_ `FName MakeUniqueNameForPropertyBag(FName OriginalName, const FInstancedPropertyBag& PropertyBag);` (scope `UE::Dataflow::Type`)
- L104 _namespace_ `namespace RenderGeometry` (scope `UE::Dataflow`)
- L106 _prototype_ `UStaticMesh* GetDataflowBox();` (scope `UE::Dataflow::RenderGeometry`)
- L107 _prototype_ `UStaticMesh* GetDataflowSphere();` (scope `UE::Dataflow::RenderGeometry`)
- L108 _prototype_ `UStaticMesh* GetDataflowPlane();` (scope `UE::Dataflow::RenderGeometry`)
- L111 _namespace_ `namespace RenderMaterial` (scope `UE::Dataflow`)
- L113 _prototype_ `UMaterialInterface* GetDataflowColorMaterial(const bool bTwoSided = false);` (scope `UE::Dataflow::RenderMaterial`)
- L114 _prototype_ `UMaterialInterface* GetDataflowColorWireframeMaterial(const bool bTwoSided = false);` (scope `UE::Dataflow::RenderMaterial`)
- L115 _prototype_ `UMaterialInterface* GetDataflowCheckerBoardMaterial(const bool bUseVertexColor = false);` (scope `UE::Dataflow::RenderMaterial`)
- L116 _prototype_ `UMaterialInterface* GetDataflowVertexColorMaterial();` (scope `UE::Dataflow::RenderMaterial`)
- L117 _prototype_ `UMaterialInterface* GetDataflowPointsMaterial();` (scope `UE::Dataflow::RenderMaterial`)
- L118 _prototype_ `UMaterialInterface* GetDataflowLinesMaterial();` (scope `UE::Dataflow::RenderMaterial`)
- L121 _namespace_ `namespace Mesh` (scope `UE::Dataflow`)
- L125 _function_ `template <typename T> T InterpolateAttribute(const FVector& InVertexA, const FVector& InVertexB, const FVector& InVertexC, const FVector& InPointInTriangle, const T& InAttributeAtVertexA, const T& InAttributeAtVertexB, const T& InAttributeAtVertexC, const T& InDefaultValue)` (scope `UE::Dataflow::Mesh`) — Barycentric interpolation of a vertex attribute
- L154 _prototype_ `bool GetMeshVertices(const UE::Geometry::FDynamicMesh3* InMeshPtr, TArray<FVector3f>& OutVertices);` (scope `UE::Dataflow::Mesh`)
- L156 _prototype_ `bool GetMeshVertexNormals(const UE::Geometry::FDynamicMesh3* InMeshPtr, TArray<FVector3f>& OutVertexNormals);` (scope `UE::Dataflow::Mesh`)
- L158 _prototype_ `bool GetMeshUVs(const UE::Geometry::FDynamicMesh3* InDynMeshPtr, TArray<FVector2f>& OutUVs, const int32 InUVLayer);` (scope `UE::Dataflow::Mesh`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowInstance.h` (Public)


#### struct `FDataflowVariableOverrides`  
`struct FDataflowVariableOverrides`  
_L58-203_
- reflection: `USTRUCT()`
- desc: This wraps the variable overrides This is also separate from FDataflowInstance to allow for customization to display override checkboxes in front of each  variable property ( see DataflowDetails.h )
- L62 _public prototype_ `FDataflowVariableOverrides(FDataflowInstance* InOwner = nullptr);`
- L66 _public prototype_ `FDataflowVariableOverrides(const FDataflowVariableOverrides& Other) = delete;` — prevent the copy constructor to avoid having a copy with the same owner use the assignment operator instead on a newly created FDataflowVariableOverrides with the right owner to copy its content over
- L68 _public prototype_ `FDataflowVariableOverrides& operator=(const FDataflowVariableOverrides& Other);`
- L71 _public prototype_ `void RemoveAllVariables();` — Remove all variables
- L74 _public prototype_ `void SyncVariables();` — Sync variables with from the original dataflow asset
- L77 _public prototype_ `bool HasVariable(FName VariableName) const;` — check if a specific variable exists
- L79 _public prototype_ `bool IsVariableOverridden(FName VariableName) const;`
- L81 _public prototype_ `const FInstancedPropertyBag& GetVariables() const;`
- L83 _public prototype_ `FInstancedPropertyBag& GetVariables();`
- L85 _public prototype_ `static FName GetVariablePropertyName();`
- L88 _public prototype_ `bool OverrideVariableBool(FName VariableName, bool bValue);` — override a dataflow boolean variable for this asset
- L91 _public prototype_ `bool OverrideVariableBoolArray(FName VariableName, const TArray<bool>& Values);` — override a dataflow boolean array variable for this asset
- L94 _public prototype_ `bool OverrideVariableInt(FName VariableName, int64 Value);` — override a dataflow integer variable for this asset
- L97 _public prototype_ `bool OverrideVariableInt32Array(FName VariableName, const TArray<int32>& Values);` — override a dataflow integer array variable for this asset
- L100 _public prototype_ `bool OverrideVariableInt64Array(FName VariableName, const TArray<int64>& Values);` — override a dataflow integer array variable for this asset
- L103 _public prototype_ `bool OverrideVariableFloat(FName VariableName, float Value);` — override a dataflow float variable for this asset
- L106 _public prototype_ `bool OverrideVariableFloatArray(FName VariableName, const TArray<float>& Values);` — override a dataflow float array variable for this asset
- L109 _public prototype_ `bool OverrideVariableObject(FName VariableName, const UObject* Value);` — override a dataflow UObject variable for this asset
- L112 _public prototype_ `bool OverrideVariableObjectArray(FName VariableName, const TArray<TObjectPtr<UObject>>& Values);` — override a dataflow UObject array variable for this asset
- L115 _public prototype_ `bool OverrideVariableObjectArray(FName VariableName, const TArray<UObject*>& Values);` — override a dataflow UObject array variable for this asset
- L118 _public prototype_ `bool OverrideVariableName(FName VariableName, FName Value);` — override a dataflow FName variable for this asset
- L121 _public prototype_ `bool OverrideVariableName(FName VariableName, const TArray<FName>& Values);` — override a dataflow FName variable for this asset
- L124 _public prototype_ `bool OverrideVariableString(FName VariableName, FString Value);` — override a dataflow String variable for this asset
- L127 _public prototype_ `bool OverrideVariableString(FName VariableName, const TArray<FString>& Values);` — override a dataflow String variable for this asset
- L130 _public function_ `template <typename T> bool OverrideVariableStruct(FName VariableName, const T& Value)`
- L144 _public function_ `template <typename T> bool OverrideVariableStructArray(FName VariableName, const TArray<T>& Values)`
- L158 _public prototype_ `void OnOwnerPostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L159 _public prototype_ `void OnDataflowVariablesChanged(const UDataflow* DataflowAsset, FName VariableName);`
- L165 _private prototype_ `const FInstancedPropertyBag* GetDefaultVariablesFromAsset() const;`
- L167 _private prototype_ `FInstancedPropertyBag& GetOverridenVariables();`
- L170 _private prototype_ `bool IsVariableOverridden(const FGuid PropertyID) const;` — @return true if the property of specified ID is overridden.
- L173 _private prototype_ `void SetVariableOverridden(const FGuid PropertyID, const bool bIsOverridden);` — Sets the override status of specified property by ID.
- L175 _private prototype_ `void RemoveOverridenVariablesNotInDataflowAsset();`
- L178 _private prototype_ `void SetVariableOverrideAndNotify(const FGuid& PropertyID, bool bOverrideState);`
- L181 _private function_ `template<typename T, typename TWriteElementFunction> bool OverrideVariableArrayAndNotify(FInstancedPropertyBag& InVariables, FName InVariableName, const TArray<T>& InValues, const TWriteElementFunction& InWriteElementFunction)`
- L196 _private member_ `FInstancedPropertyBag Variables;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (FixedLayout, ShowOnlyInnerProperties))` — Variables to override
- L200 _private member_ `TArray<FGuid> OverriddenVariableGuids;` — `UPROPERTY()` — Array of overridden variable GUIDs. Non-overridden properties will inherit the values from the DataflowAsset default parameters.
- L202 _private member_ `FDataflowInstance* Owner = nullptr;`

#### struct `FDataflowInstance`  
`struct FDataflowInstance`  
_L209-313_
- reflection: `USTRUCT()`
- desc: This structure is to be embedded in any asset that need generation from a dataflow
- L213 _public prototype_ `explicit FDataflowInstance(UObject* InOwner = nullptr, UDataflow* InDataflowAsset = nullptr, FName InTerminalNodeName = NAME_None);`
- L214 _public prototype_ `FDataflowInstance& operator=(const FDataflowInstance& Other);`
- L219 _public prototype_ `FDataflowInstance(const FDataflowInstance& Other) = delete;` — Delete these to avoid complications with Bind/UnbindEditorDelegates. They can be implemented if needed.
- L220 _public prototype_ `FDataflowInstance(FDataflowInstance&& Other) = delete;`
- L222 _public prototype_ `~FDataflowInstance();`
- L225 _public prototype_ `void SetDataflowAsset(UDataflow* DataflowAsset);`
- L227 _public prototype_ `UDataflow* GetDataflowAsset() const;`
- L229 _public prototype_ `void SetDataflowTerminal(FName TerminalNodeName);`
- L231 _public prototype_ `FName GetDataflowTerminal() const;`
- L233 _public prototype_ `const FInstancedPropertyBag& GetVariables() const;`
- L235 _public prototype_ `FInstancedPropertyBag& GetVariables();`
- L238 _public prototype_ `static FName GetDataflowTerminalPropertyName();` — Get the dataflow terminal member property name
- L241 _public prototype_ `static FName GetDataflowAssetPropertyName();` — Get the dataflow asset member property name
- L244 _public prototype_ `static FName GetVariableOverridesPropertyName();` — Get the variable overrides member property name
- L246 _public prototype_ `const FDataflowVariableOverrides& GetVariableOverrides() const;`
- L248 _public prototype_ `FDataflowVariableOverrides& GetVariableOverrides();`
- L250 _public prototype_ `void SyncVariables();`
- L254 _public function_ `FInstancedPropertyBag& GetPreviewBlueprintVariableOverrides()` — Get the preview blueprint variable values for this asset.
- L259 _public function_ `const FInstancedPropertyBag& GetPreviewBlueprintVariableOverrides() const` — Get the preview blueprint variable values for this asset. Const version.
- L269 _public prototype_ `bool UpdateOwnerAsset(bool bUpdateDependentAssets = false) const;` — Update the asset by re-evaluating the dataflow return true if the dataflow has been properly evaluated and the asset updated
- L272 _public prototype_ `void PostLoad();` — Call as part of the PostLoad of any UObject containing a FDataflowInstance member
- L275 _public prototype_ `TSharedPtr<FStructOnScope> MakeStructOnScope() const;`
- L283 _private member_ `TObjectPtr<UDataflow> DataflowAsset;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Dataflow asset to use
- L287 _private member_ `FName DataflowTerminal;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — name of the terminal node to use when generating the asset
- L291 _private member_ `FDataflowVariableOverrides VariableOverrides;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta=(ShowOnlyInnerProperties))` — Dataflow variables to override
- L296 _private member_ `FInstancedPropertyBag PreviewBlueprintVariableOverrides;` — `UPROPERTY()` — Preview blueprint variables to override
- L303 _private prototype_ `void BindEditorDelegates();`
- L304 _private prototype_ `void UnbindEditorDelegates();`
- L305 _private prototype_ `void OnOwnerPostEditChangeProperty(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L307 _private member_ `FDelegateHandle OnOwnerPropertyChangedHandle;`
- L312 _private member_ `TObjectPtr<UObject> Owner = nullptr;` — `UPROPERTY()` — Owning Object

#### class `UDataflowInstanceInterface`  
`class UDataflowInstanceInterface : public UInterface`  
_L316-319_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IDataflowInstanceInterface`  
`class IDataflowInstanceInterface`  
_L324-331_
- desc: Interface to use on asset class that are generated using a data flow
- L329 _public prototype_ `virtual const FDataflowInstance& GetDataflowInstance() const = 0;`
- L330 _public prototype_ `virtual FDataflowInstance& GetDataflowInstance() = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Dataflow` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Dataflow` (scope `UE`)
- L19 _namespace_ `namespace InstanceUtils` (scope `UE::Dataflow`)
- L19 _namespace_ `namespace Private` (scope `UE::Dataflow::InstanceUtils`)
- L23 _function_ `template<typename T, typename TWriteElementFunction> bool OverrideVariableArray(FInstancedPropertyBag& Variables, FName VariableName, const TArray<T>& Values, const TWriteElementFunction& WriteElementFunction, FGuid& OutGuid)` (scope `UE::Dataflow::InstanceUtils::Private`) — need to be in the header to be used by the templated structure override methods
- L149 _function_ `` (scope `FDataflowVariableOverrides::OverrideVariableStructArray`)
- L333 _namespace_ `namespace UE`
- L333 _namespace_ `namespace Dataflow` (scope `UE`)
- L333 _namespace_ `namespace InstanceUtils` (scope `UE::Dataflow`)
- L336 _prototype_ `bool HasValidDataflowAsset(UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Weather or not a dataflow asset is assigned to an UObject
- L339 _prototype_ `UDataflow* GetDataflowAssetFromObject(UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Get the Dataflow asset from a UObject if available
- L342 _prototype_ `const UDataflow* GetDataflowAssetFromObject(const UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Get the Dataflow asset from a UObject if available (const version)
- L345 _prototype_ `IDataflowInstanceInterface* GetDataflowInterfaceFromObject(UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Get the Dataflow instance interface from a UObject
- L348 _prototype_ `UDataflowAttachment* GetDataflowAttachmentFromObject(const UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Get the Dataflow attachment from a UObject
- L351 _prototype_ `const IDataflowInstanceInterface* GetDataflowInterfaceFromObject(const UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Get the Dataflow instance interface from a const UObject
- L358 _prototype_ `bool SetDataflowAssetOnObject(UDataflow* DataflowAsset, UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Set a Dataflow asset/object on a specific object The object type must be compatible with dataflow Returns true if the dataflow object was set successfuly
- L361 _prototype_ `FName GetTerminalNodeNameFromObject(UObject* Obj);` (scope `UE::Dataflow::InstanceUtils`) — Get the terminal node name from a UObject if available
- L364 _prototype_ `TArray<FName> GetTerminalNodeNames(const UDataflow* DataflowAsset);` (scope `UE::Dataflow::InstanceUtils`) — get the list of terminal node names for a specific data flow asset
- L367 _prototype_ `void GetAssetRegistryTags(const UObject* BoundAsset, FAssetRegistryTagsContext& Context);` (scope `UE::Dataflow::InstanceUtils`) — Register tags for an asset using Dataflow

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowMesh.h` (Public)


#### class `UDataflowMesh`  
`class UDataflowMesh : public UObject`  
_L17-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Containter for storing mesh and material information in Dataflow graph
- L23 _public prototype_ `const UE::Geometry::FDynamicMesh3* GetDynamicMesh() const;`
- L24 _public prototype_ `const UE::Geometry::FDynamicMesh3& GetDynamicMeshRef() const;`
- L26 _public prototype_ `const TArray<TObjectPtr<UMaterialInterface>>& GetMaterials() const;`
- L29 _public function_ `template<typename MeshType> void SetDynamicMesh(MeshType&& InMesh)`
- L42 _public function_ `template<typename MaterialArrayType> void SetMaterials(MaterialArrayType&& InMaterials)`
- L48 _public function_ `template<typename MaterialArrayType> void AddMaterials(MaterialArrayType&& InMaterials)`
- L55 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> DynamicMesh;`
- L58 _protected member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY()`
- L60 _protected prototype_ `virtual void Serialize(FArchive& Archive) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAFLOWENGINE_API`

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowObject.h` (Public)


#### enum `UE::Dataflow::ESubGraphChangedReason`  
`enum class ESubGraphChangedReason: uint8`  
_L35-43_
- L37 _public enumerator_ `Created`
- L38 _public enumerator_ `Pasted` — Like Created, but emitted from the paste-from-clipboard path. Listeners should refresh views but should NOT auto-open the subgraph in a tab (the user pasted into a different graph).
- L39 _public enumerator_ `Renamed`
- L40 _public enumerator_ `Deleting`
- L41 _public enumerator_ `Deleted`
- L42 _public enumerator_ `ChangedType`

#### struct `FDataflowAssetDelegates`  
`struct FDataflowAssetDelegates`  
_L46-66_
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVariablesChanged, const UDataflow*, FName);` — Called when variables are edited ( add, remove, changetype , setvalue )
- L50 _public member_ `static FOnVariablesChanged OnVariablesChanged;`
- L52 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVariablesOverrideStateChanged, const UDataflow*, FName, bool);`
- L53 _public member_ `static FOnVariablesOverrideStateChanged OnVariablesOverrideStateChanged;`
- L56 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSubGraphsChanged, const UDataflow*, const FGuid&, UE::Dataflow::ESubGraphChangedReason);` — Called when sub-graphs are edited ( add, remove )
- L57 _public member_ `static FOnSubGraphsChanged OnSubGraphsChanged;`
- L59 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeInvalidated, UDataflow&, FDataflowNode&);`
- L60 _public member_ `static FOnNodeInvalidated OnNodeInvalidated;`
- L63 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowPostEditUndo, UDataflow&);`
- L64 _public member_ `static FOnDataflowPostEditUndo OnDataflowPostEditUndo;`

#### class `FDataflowAssetEdit`  
`class FDataflowAssetEdit`  
_L75-92_
- desc: FDataflowAssetEdit Structured RestCollection access where the scope of the object controls serialization back into the dynamic collection
- L78 _public typedef_ `typedef TFunctionRef<void()> FPostEditFunctionCallback;`
- L84 _public prototype_ `FDataflowAssetEdit(UDataflow *InAsset, FPostEditFunctionCallback InCallable);` — @param UDataflow				The "FAsset" to edit
- L85 _public prototype_ `~FDataflowAssetEdit();`
- L87 _public prototype_ `UE::Dataflow::FGraph* GetGraph();`
- L90 _private member_ `FPostEditFunctionCallback PostEditCallback;`
- L91 _private member_ `UDataflow* Asset;`

#### enum `EDataflowType`  
`enum class EDataflowType : uint8`  
_L96-103_
- reflection: `UENUM()`
- desc: Data flow types
- L99 _public enumerator_ `Construction` — the dataflow will be used to build assets
- L102 _public enumerator_ `Simulation` — The dataflow will be used to define the simulation evolution

#### class `UDataflow`  
`class UDataflow : public UEdGraph, public IMeshDeformerProducer, public IDataflowGraphInterface`  
_L112-320_
- reflection: `UCLASS(BlueprintType, customconstructor, MinimalAPI)`
- inherits: `UEdGraph,IMeshDeformerProducer,IDataflowGraphInterface`
- desc: UDataflow (UObject) UObject wrapper for the UE::Dataflow::FGraph
- L116 _private member_ `UE::Dataflow::FTimestamp LastModifiedRenderTarget = UE::Dataflow::FTimestamp::Invalid;`
- L117 _private member_ `TArray< TObjectPtr<const UDataflowEdNode> > RenderTargets;` — Not Serialized
- L118 _private member_ `TArray< TObjectPtr<const UDataflowEdNode> > WireframeRenderTargets;` — Not Serialized
- L119 _private member_ `TSharedPtr<UE::Dataflow::FGraph, ESPMode::ThreadSafe> Dataflow;`
- L120 _private prototype_ `void PostEditCallback();`
- L123 _public prototype_ `UDataflow(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L129 _public prototype_ `void EvaluateTerminalNodeByName(FName NodeName, UObject* Asset);` — `UE_DEPRECATED(5.1, "Use Blueprint library version of the function")` — Find all the node of a speific type and evaluate them using a specific UObject
- L131 _public function_ `virtual bool IsEditorOnly() const`
- L134 _public member_ `static const FString SimulationTag;` — Simulation tag to use in the node registry
- L137 _public prototype_ `virtual void BeginDestroy() override;`
- L141 _public function_ `virtual FMeshDeformerBeginDestroyEvent& OnBeginDestroy() override`
- L145 _public function_ `virtual TSharedPtr<UE::Dataflow::FGraph> GetDataflowGraph() const override`
- L151 _public member_ `bool bActive = true;` — `UE_DEPRECATED(5.8, "bActive property is deprecated as it is no longer used")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bActive property is deprecated as it is no longer used"))`
- L155 _public member_ `TArray<TObjectPtr<UObject>> Targets;` — `UE_DEPRECATED(5.8, "Targets property is deprecated as it is no longer used")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Targets property is deprecated as it is no longer used"))`
- L158 _public member_ `TObjectPtr<UMaterial> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Render")`
- L161 _public member_ `EDataflowType Type = EDataflowType::Construction;` — `UPROPERTY(EditAnywhere, Category = "Evaluation",meta=(EditConditionHides))`
- L169 _public member_ `FInstancedPropertyBag Variables;` — `UPROPERTY()` — Dataflow variables Variables are used by the graph to parametrized the graph They can can default values and can be overriden on a per asset basis ( see Dataflow Instance )
- L178 _public member_ `TObjectPtr<UObject> ReferenceAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Reference)` — Reference asset to use for this Dataflow The reference asset is used when opening the dataflow asset editor If the dataflow is shared among multiple assets, and the reference asset is set, only this asset will be able to change the dataflow (for the other the dataflow graph will be read-only and only evaluation and overrides will be available)
- L182 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — UObject Interface
- L185 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L186 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L187 _public prototype_ `virtual void PostEditUndo() override;`
- L189 _public prototype_ `virtual void PostLoad() override;`
- L192 _public prototype_ `void Serialize(FArchive& Ar);`
- L195 _public function_ `TSharedPtr<const UE::Dataflow::FGraph, ESPMode::ThreadSafe> GetDataflow() const` — Accessors for internal geometry collection
- L196 _public function_ `TSharedPtr<UE::Dataflow::FGraph, ESPMode::ThreadSafe> GetDataflow()`
- L199 _public function_ `FDataflowAssetEdit EditDataflow() const` — Editing the collection should only be through the edit object.
- L205 _public prototype_ `TObjectPtr<const UDataflowEdNode> FindEdNodeByDataflowNodeGuid(const FGuid& Guid) const;`
- L206 _public prototype_ `TObjectPtr<UDataflowEdNode> FindEdNodeByDataflowNodeGuid(const FGuid& Guid);`
- L211 _public prototype_ `void AddRenderTarget(TObjectPtr<const UDataflowEdNode>);` — Render Targets
- L212 _public prototype_ `void RemoveRenderTarget(TObjectPtr<const UDataflowEdNode>);`
- L213 _public function_ `const TArray< TObjectPtr<const UDataflowEdNode> >& GetRenderTargets() const`
- L215 _public prototype_ `void AddWireframeRenderTarget(TObjectPtr<const UDataflowEdNode>);`
- L216 _public prototype_ `void RemoveWireframeRenderTarget(TObjectPtr<const UDataflowEdNode>);`
- L217 _public function_ `const TArray< TObjectPtr<const UDataflowEdNode> >& GetWireframeRenderTargets() const`
- L219 _public function_ `const UE::Dataflow::FTimestamp& GetRenderingTimestamp() const`
- L224 _public prototype_ `static UDataflow* GetDataflowAssetFromEdGraph(UEdGraph* EdGraph);` — Find the Dataflow asset from a sepcific graph/subgraph
- L225 _public prototype_ `static const UDataflow* GetDataflowAssetFromEdGraph(const UEdGraph* EdGraph);`
- L228 _public prototype_ `const UDataflowSubGraph* FindSubGraphByName(FName Name) const;` — Find a SubGraph by name
- L229 _public prototype_ `UDataflowSubGraph* FindSubGraphByName(FName Name);`
- L232 _public prototype_ `const UDataflowSubGraph* FindSubGraphByGuid(const FGuid& SubGraphGuid) const;` — Find a SubGraph by its guid
- L233 _public prototype_ `UDataflowSubGraph* FindSubGraphByGuid(const FGuid& SubGraphGuid);`
- L236 _public prototype_ `void AddSubGraph(UDataflowSubGraph* SubGraph);` — Add a SubGraph to the asset
- L237 _public prototype_ `void RemoveSubGraph(UDataflowSubGraph* SubGraph);`
- L239 _public prototype_ `const TArray<TObjectPtr<UDataflowSubGraph>>& GetSubGraphs() const;`
- L245 _public prototype_ `void RefreshEdNode(TObjectPtr<UDataflowEdNode> EdNode);` — Make sure EdNode gets refreshed from its dataflow node This is useful when connections are changed
- L246 _public prototype_ `void RefreshEdNodeByGuid(const FGuid NodeGuid);`
- L252 _public prototype_ `TSharedPtr<const UE::Dataflow::FCompiledGraph> CompileGraphIfNeeded();` — Compile the dataflow graph if it has not been compiled since last change to the graph returns a shared pointer to the compiled graph
- L266 _public member_ `FDataflowPreviewCacheParams PreviewCacheParams;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Cachie params used in this asset
- L270 _public member_ `TSoftObjectPtr<UObject> PreviewCacheAsset = nullptr;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Cache asset used in this asset
- L274 _public member_ `TSubclassOf<AActor> PreviewBlueprintClass;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Caching blueprint actor class to spawn
- L278 _public member_ `FTransform PreviewBlueprintTransform = FTransform::Identity;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Caching blueprint actor transform to spawn
- L282 _public member_ `TSoftObjectPtr<UObject> PreviewGeometryCacheAsset = nullptr;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Geometry cache asset used to extract skeletal mesh results from simulation
- L286 _public member_ `TSoftObjectPtr<UObject> PreviewEmbeddedSkeletalMesh = nullptr;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — SkeletalMesh interpolated from simulation
- L290 _public member_ `TSoftObjectPtr<UObject> PreviewEmbeddedStaticMesh = nullptr;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Static Mesh interpolated from simulation
- L295 _public function_ `bool IsPerNodeTransactionSerializationEnabled() const` — Used to disable per-node serialization when serializing a transaction
- L299 _private member_ `bool bEnablePerNodeTransactionSerialization = true;` — Used to disable per-node serialization when serializing a transaction
- L308 _private member_ `TArray<TObjectPtr<UDataflowSubGraph>> DataflowSubGraphs;` — `UPROPERTY()` — List of Dataflow SubGraphs In editor they also exists in the SubGraphs parent class property
- L311 _private member_ `FGuid LastCompiledTopologyGUID;` — Stores the topology GUID used fro the most recent compilation (see CompiledGraphs)
- L314 _private member_ `TMap<const UObject*, TSharedRef<UE::Dataflow::FCompiledGraph>> CompiledGraphs;` — Contained the most recent compiled dataflow graph (see GetGraphTopologyGuid )
- L319 _private member_ `FMeshDeformerBeginDestroyEvent BeginDestroyEvent;` — Broadcasts a notification just before the dataflow is destroyed.

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Dataflow` (scope `UE`)
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVariablesChanged, const UDataflow*, FName);` — Called when variables are edited ( add, remove, changetype , setvalue )
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVariablesOverrideStateChanged, const UDataflow*, FName, bool);`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSubGraphsChanged, const UDataflow*, const FGuid&, UE::Dataflow::ESubGraphChangedReason);` — Called when sub-graphs are edited ( add, remove )
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeInvalidated, UDataflow&, FDataflowNode&);`
- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowPostEditUndo, UDataflow&);`
- L202 _function_ `return FDataflowAssetEdit(ThisNC, [ThisNC]() {ThisNC->PostEditCallback(); });` (scope `UDataflow::EditDataflow`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowObjectInterface.h` (Public)


#### class `UE::Dataflow::TEngineContext`  
`template<class Base = FContextSingle> class TEngineContext : public Base`  
_L22-83_
- inherits: `Base`
- L25 _public prototype_ `DATAFLOW_CONTEXT_INTERNAL(Base, TEngineContext);`
- L27 _public function_ `explicit TEngineContext(const TObjectPtr<UObject>& InOwner) : Base() , Owner(InOwner)`
- L32 _public member_ `TObjectPtr<UObject> Owner = nullptr;`
- L38 _public function_ `UObject* GetBoundAsset() const` — return the asset bound to this context This may be the owner but in the case of the use of Dataflow attachement this may be the Outer of the Owner
- L43 _public prototype_ `virtual ~TEngineContext() = default;`
- L45 _public function_ `int32 GetKeys(TSet<FContextCacheKey>& InKeys) const`
- L47 _public function_ `const TUniquePtr<FContextCacheElementBase>* GetBaseData(FContextCacheKey Key) const`
- L49 _public function_ `virtual void Serialize(FArchive& Ar)`
- L57 _public function_ `template <typename T UE_REQUIRES(std::is_base_of_v<IDataflowEvaluator, T>)> TSharedPtr<IDataflowEvaluator> EvaluateGraph(FOnPostEvaluationFunction OnPostEvaluation)` — Evaluate the dataflow graph attached to the owner of this context and update the owner accordingly Returns an evaluator that can be used to query the progress of the evaluation Note that the evaluator is not kept by this context and needs to be kept by the caller
- L74 _public function_ `template <typename T UE_REQUIRES(std::is_base_of_v<IDataflowEvaluator, T>)> TSharedPtr<IDataflowEvaluator> EvaluateGraph(UDataflow* DataflowObject, FOnPostEvaluationFunction OnPostEvaluation)` — Evaluate an external dataflow graph and update the owner of this context with it Returns an evaluator that can be used to query the progress of the evaluation Note that the evaluator is not kept by this context and needs to be kept by the caller

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L15 _prototype_ `void UpdateAssetFromTerminalNodes(FContext& Context, UObject* Asset, bool bUseAllTerminals);` (scope `UE::Dataflow::Private`)
- L16 _prototype_ `bool EvaluateGraphInternal(TSharedRef<IDataflowEvaluator> Evaluator, UObject* Owner, FOnPostEvaluationFunction OnPostEvaluation);` (scope `UE::Dataflow::Private`)
- L17 _prototype_ `bool EvaluateGraphInternal(TSharedRef<IDataflowEvaluator> Evaluator, UDataflow* DataflowObject, UObject* ObjectToUpdate, FOnPostEvaluationFunction OnPostEvaluation);` (scope `UE::Dataflow::Private`)
- L18 _prototype_ `UObject* FindBoundAsset(UObject* Object);` (scope `UE::Dataflow::Private`)
- L85 _typedef_ `typedef TEngineContext<FContextSingle> FEngineContext;` (scope `UE::Dataflow`)
- L86 _typedef_ `typedef TEngineContext<FContextThreaded> FEngineContextThreaded;` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowOverlay.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)
- L11 _namespace_ `namespace Overlay` (scope `UE::Dataflow`)
- L13 _prototype_ `FString BuildOverlayNodeInfoString(const FDataflowNode* InNode);` (scope `UE::Dataflow::Overlay`)
- L14 _prototype_ `FString BuildOverlaySelectionEvaluateResultString(FDataflowSelection& InSelection);` (scope `UE::Dataflow::Overlay`)
- L15 _prototype_ `FString BuildOverlayCollectionInfoString(const FManagedArrayCollection& InCollection);` (scope `UE::Dataflow::Overlay`)
- L16 _prototype_ `FString BuildOverlayBoundsInfoString(const FManagedArrayCollection& InCollection);` (scope `UE::Dataflow::Overlay`)
- L17 _prototype_ `FString BuildOverlayMemInfoString(const FDataflowNode* InNode);` (scope `UE::Dataflow::Overlay`)
- L18 _prototype_ `FString BuildOverlayFinalString(const TArray<FString>& InStringArr);` (scope `UE::Dataflow::Overlay`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowPreview.h` (Public)


#### struct `FDataflowPreviewCacheParams`  
`struct FDataflowPreviewCacheParams`  
_L16-55_
- reflection: `USTRUCT()`
- L23 _public member_ `int32 FrameRate = 30;` — `UPROPERTY(EditAnywhere, Category="Caching")` — Number of sampling frames per second for caching
- L27 _public member_ `int32 SubframeRate = 1;` — `UPROPERTY(EditAnywhere, meta = (EditCondition = "bCanEditSubframeRate", ClampMin = "1"), Category = "Caching")` — Number of subframes per frame for timeline clamping
- L29 _public member_ `bool bCanEditSubframeRate = false;` — `UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle), Category = "Caching")`
- L33 _public member_ `FVector2f TimeRange = FVector2f(0.0f, 5.0f);` — `UPROPERTY(EditAnywhere, Category="Caching")` — Time range of the simulation
- L37 _public member_ `bool bRestartSimulation = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Caching")` — If enabled, the simulation will restart on Time Range without modifying anything outside of Time Range
- L41 _public member_ `FVector2f RestartTimeRange = FVector2f(0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "Caching", meta = (EditCondition = "bRestartSimulation"))` — Time range of the restarted simulation
- L45 _public member_ `bool bEnableAsyncCaching = false;` — `UPROPERTY()` — Control whether the async caching feature is available or not
- L52 _public member_ `bool bAsyncCaching = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Caching", meta = (EditCondition = "bEnableAsyncCaching", HideEditConditionToggle))` — When enabled runs the caching proces on an async thread (allowing the UI to remain responsive) This option will be disabled if the asset associated with the graph does not support asynchronous caching

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowSkeletalMeshAttachment.h` (Public)


#### class `UDataflowSkeletalMeshAttachment`  
`class UDataflowSkeletalMeshAttachment : public UDataflowAttachment`  
_L9-31_
- reflection: `UCLASS()`
- inherits: `UDataflowAttachment`
- L16 _public prototype_ `void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override;` — IDataflowContentOwner
- L17 _public prototype_ `void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override;`
- L23 _protected prototype_ `TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override;` — IDataflowContentOwner
- L27 _protected prototype_ `FString GetPreviewActorPath() const override;` — UDataflowAttachment

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowSkeleton.h` (Public)


#### struct `FDataflowSkeleton`  
`struct FDataflowSkeleton`  
_L18-35_
- reflection: `USTRUCT()`
- desc: Represents skeletons for dataflow
- L23 _public prototype_ `const FReferenceSkeleton& GetRefSkeleton() const;` — read-only access to the underlying skeleton object
- L25 _public prototype_ `FReferenceSkeletonModifier ModifySkeleton();`
- L27 _public prototype_ `void Empty();`
- L29 _public prototype_ `void Copy(const FReferenceSkeleton& ToCopy);`
- L31 _public prototype_ `bool Serialize(FArchive& Ar);`
- L34 _private member_ `FReferenceSkeleton RefSkeleton;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataflowSkeleton> : public TStructOpsTypeTraitsBase2<FDataflowSkeleton>`  
_L37-43_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowSkeleton>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L40-42_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L41 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anondde1f80b0103`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowSubGraph.h` (Public)


#### struct `FDataflowSubGraphDelegates`  
`struct FDataflowSubGraphDelegates`  
_L19-24_
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowSubGraphLoaded, const UDataflowSubGraph&);` — Called when variables are edited ( add, remove, changetype , setvalue )
- L23 _public member_ `static FOnDataflowSubGraphLoaded OnSubGraphLoaded;`

#### class `UDataflowSubGraph`  
`class UDataflowSubGraph : public UEdGraph`  
_L27-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L32 _public prototype_ `FDataflowSubGraphInputNode* GetInputNode() const;`
- L33 _public prototype_ `FDataflowSubGraphOutputNode* GetOutputNode() const;`
- L35 _public prototype_ `bool IsForEachSubGraph() const;`
- L36 _public prototype_ `void SetForEachSubGraph(bool bValue);`
- L38 _public function_ `bool IsLoaded() const`
- L39 _public function_ `const FGuid& GetSubGraphGuid() const`
- L42 _private prototype_ `virtual void PostLoad() override;`
- L44 _private prototype_ `virtual void PostEditUndo() override;`
- L53 _private function_ `void SetSubGraphGuid(const FGuid& InGuid)`
- L60 _private member_ `FGuid SubGraphGuid;` — `UPROPERTY()` — Guid that uniquely identify this SubGraph this allow to identify the SubGraph across renames for example
- L63 _private member_ `bool bIsForEach = false;` — `UPROPERTY()`
- L65 _private member_ `bool bIsLoaded : 1 = false;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowSubGraphLoaded, const UDataflowSubGraph&);` — Called when variables are edited ( add, remove, changetype , setvalue )

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowSubGraphNodes.h` (Public)


#### struct `UE::Dataflow::ISubGraphContextCallback`  
`struct ISubGraphContextCallback`  
_L22-25_
- L24 _public prototype_ `virtual void EvaluateParentContext(UE::Dataflow::FContext& Context, UE::Dataflow::FContext& SubGraphContext, const FDataflowOutput& SubGraphOutput) const = 0;`

#### struct `FDataflowSubGraphInputNode`  
`struct FDataflowSubGraphInputNode : public FDataflowNode #if CPP , public FDataflowDynamicConnections::IOwnerInterface #endif`  
_L34-67_
- reflection: `USTRUCT(meta=(Icon="GraphEditor.Function_16x"))`
- inherits: `FDataflowNode,FDataflowDynamicConnections::IOwnerInterface`
- desc: This node represent the inputs of a dataflow subgraph
- L45 _public prototype_ `FDataflowSubGraphInputNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L48 _public function_ `virtual FDataflowNode* GetOwner(const FDataflowDynamicConnections* Caller) override` — Begin IOwnerInterface
- L49 _public function_ `virtual const FInstancedPropertyBag& GetPropertyBag(const FDataflowDynamicConnections* Caller) override`
- L52 _public prototype_ `void AddConnectionsTo(TArrayView<FDataflowConnection*> Connections);`
- L55 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L56 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L57 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L59 _private prototype_ `virtual bool SupportsDropConnectionOnNode(FName TypeName, UE::Dataflow::FPin::EDirection Direction) const override;`
- L60 _private prototype_ `virtual const FDataflowConnection* OnDropConnectionOnNode(const FDataflowConnection& DroppedConnection) override;`
- L63 _private member_ `FDataflowDynamicConnections DynamicConnections;` — `UPROPERTY()`
- L66 _private member_ `FInstancedPropertyBag PropertyBag;` — `UPROPERTY(EditAnyWhere, Category = Inputs, Meta = (DisplayName = "Inputs"))`

#### struct `FDataflowSubGraphOutputNode`  
`struct FDataflowSubGraphOutputNode : public FDataflowNode #if CPP , public FDataflowDynamicConnections::IOwnerInterface #endif`  
_L74-117_
- reflection: `USTRUCT(meta = (Icon = "GraphEditor.Function_16x"))`
- inherits: `FDataflowNode,FDataflowDynamicConnections::IOwnerInterface`
- desc: This node represent the Outputs of a dataflow subgraph
- L85 _public prototype_ `FDataflowSubGraphOutputNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L89 _public function_ `virtual FDataflowNode* GetOwner(const FDataflowDynamicConnections* Caller) override` — Begin IOwnerInterface
- L90 _public function_ `virtual const FInstancedPropertyBag& GetPropertyBag(const FDataflowDynamicConnections* Caller) override`
- L93 _public prototype_ `void AddConnectionsTo(TArrayView<FDataflowConnection*> Connections);`
- L97 _private function_ `virtual bool IsTerminal() const override` — Subgraph output nodes are considered terminal
- L102 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L103 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L104 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L106 _private prototype_ `virtual bool SupportsDropConnectionOnNode(FName TypeName, UE::Dataflow::FPin::EDirection Direction) const override;`
- L107 _private prototype_ `virtual const FDataflowConnection* OnDropConnectionOnNode(const FDataflowConnection& DroppedConnection) override;`
- L110 _private function_ `virtual bool MakeConnectedPropertiesReadOnly() const override` — we want the user to be able to change the type of the properties in the property bag or rename them
- L113 _private member_ `FDataflowDynamicConnections DynamicConnections;` — `UPROPERTY()`
- L116 _private member_ `FInstancedPropertyBag PropertyBag;` — `UPROPERTY(EditAnyWhere, Category = Inputs, Meta = (DisplayName = "Inputs"))`

#### struct `FDataflowSubGraphGetCurrentIndexNode`  
`struct FDataflowSubGraphGetCurrentIndexNode : public FDataflowNode`  
_L125-140_
- reflection: `USTRUCT(meta = (Icon = "GraphEditor.Function_16x"))`
- inherits: `FDataflowNode`
- desc: Get the current index in a subgraph This is to be used in subgraph when iterating over an array
- L133 _public prototype_ `FDataflowSubGraphGetCurrentIndexNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L136 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L139 _private member_ `int32 Index = 0;` — `UPROPERTY(Meta = (DataflowOutput))`

#### struct `FDataflowCallSubGraphNode`  
`struct FDataflowCallSubGraphNode : public FDataflowNode #if CPP , public FDataflowDynamicConnections::IOwnerInterface , public UE::Dataflow::ISubGraphContextCallback #endif`  
_L146-211_
- reflection: `USTRUCT(meta = (Icon = "GraphEditor.Function_16x"))`
- inherits: `FDataflowNode,FDataflowDynamicConnections::IOwnerInterface,UE::Dataflow::ISubGraphContextCallback`
- desc: Call a subgraph
- L158 _public prototype_ `FDataflowCallSubGraphNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L161 _public prototype_ `void SetSubGraphGuid(const FGuid& Guid);`
- L162 _public function_ `const FGuid& GetSubGraphGuid() const`
- L164 _public prototype_ `void RefreshSubGraphName();`
- L167 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L168 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L171 _private prototype_ `virtual void EvaluateParentContext(UE::Dataflow::FContext& Context, UE::Dataflow::FContext& SubGraphContext, const FDataflowOutput& SubGraphOutput) const override;` — Begin ISubGraphContextCallback
- L175 _private function_ `virtual FDataflowNode* GetOwner(const FDataflowDynamicConnections* Caller) override` — Begin IOwnerInterface
- L176 _private prototype_ `virtual const FInstancedPropertyBag& GetPropertyBag(const FDataflowDynamicConnections* Caller) override;`
- L180 _private prototype_ `void UnregisterHandlers(UDataflowSubGraph* SubGraph);`
- L181 _private prototype_ `void RegisterHandlers(UDataflowSubGraph* SubGraph);`
- L182 _private prototype_ `void OnSubGraphChanged(const struct FEdGraphEditAction& InAction);`
- L183 _private prototype_ `void OnSomeSubGraphsChanged(const UDataflow* InDataflowAsset, const FGuid& InSubGraphGuid, UE::Dataflow::ESubGraphChangedReason InReason);`
- L184 _private prototype_ `void OnSubGraphLoaded(const UDataflowSubGraph& InSubGraph);`
- L186 _private prototype_ `void SyncInputsPropertyBagWithSubGraph();`
- L187 _private prototype_ `void SyncOutputsPropertyBagWithSubGraph();`
- L189 _private prototype_ `bool IsValid() const;`
- L192 _private member_ `FGuid SubGraphGuid;` — `UPROPERTY()`
- L195 _private member_ `FName SubGraphName;` — `UPROPERTY(VisibleAnyWhere, Category = Subgraph)`
- L198 _private member_ `FDataflowDynamicConnections DynamicInputs;` — `UPROPERTY()`
- L201 _private member_ `FInstancedPropertyBag InputsPropertyBag;` — `UPROPERTY()`
- L204 _private member_ `FDataflowDynamicConnections DynamicOutputs;` — `UPROPERTY()`
- L207 _private member_ `FInstancedPropertyBag OutputsPropertyBag;` — `UPROPERTY()`
- L209 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;`
- L210 _private member_ `FDelegateHandle OnGraphChangedHandle;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Dataflow` (scope `UE`)
- L213 _namespace_ `namespace UE`
- L213 _namespace_ `namespace Dataflow` (scope `UE`)
- L215 _prototype_ `void RegisterSubGraphNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Engine/Public/Dataflow/DataflowVariableNodes.h` (Public)


#### struct `FGetDataflowVariableNode`  
`struct FGetDataflowVariableNode : public FDataflowNode`  
_L15-85_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L22 _public prototype_ `~FGetDataflowVariableNode();`
- L24 _public prototype_ `void SetVariable(UDataflow* DataflowAsset, FName VariableName);`
- L25 _public prototype_ `bool TryAddVariableToDataflowAsset(UDataflow& DataflowAsset);`
- L27 _public function_ `FName GetVariableName() const`
- L31 _private member_ `FDataflowAnyType Value;` — `UPROPERTY(meta=(DataflowOutput))`
- L34 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;` — Called when UPROPERTY members of the dataflow node have been changed in the editor
- L37 _private prototype_ `virtual void PostSerialize(const FArchive& Ar);` — Override this method to provide custom post-serialization for this node. This method will be called after Serialize. It is also called after copy-paste with ArchiveState IsLoading.
- L39 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L41 _private prototype_ `static void EvaluateBool(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L42 _private prototype_ `static void EvaluateByte(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L43 _private prototype_ `static void EvaluateInt32(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L44 _private prototype_ `static void EvaluateInt64(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L45 _private prototype_ `static void EvaluateFloat(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L46 _private prototype_ `static void EvaluateDouble(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L47 _private prototype_ `static void EvaluateName(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L48 _private prototype_ `static void EvaluateString(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L49 _private prototype_ `static void EvaluateText(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L50 _private prototype_ `static void EvaluateObject(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L51 _private prototype_ `static void EvaluateStruct(const FGetDataflowVariableNode& Node, const FInstancedPropertyBag& Variables, UE::Dataflow::FContext& Context, const FDataflowOutput& Out);`
- L53 _private prototype_ `void UpdateOutputTypes(const FPropertyBagPropertyDesc& Desc);`
- L54 _private prototype_ `void ChangeOutputType(FDataflowOutput* Output, FName NewType);`
- L58 _private member_ `FInstancedPropertyBag VariablePropertyBag;` — `UPROPERTY(EditAnywhere, Category = "Default Value", meta = (FixedLayout, ShowOnlyInnerProperties))`
- L61 _private member_ `FName VariableName;` — `UPROPERTY(VisibleAnywhere, Category = Variable)`
- L65 _private member_ `FString Category;` — `UPROPERTY(EditAnywhere, Category = Variable)` — Category the variable should be displayed under
- L69 _private member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category = Variable)` — Decsription of this variable, the description will show in the tooltip of overrides
- L71 _private prototype_ `void RegisterHandlers();`
- L72 _private prototype_ `void UnregisterHandlers();`
- L74 _private typedef_ `using FStaticEvaluationFunctionPtr = void(*)(const FGetDataflowVariableNode&, const FInstancedPropertyBag&, UE::Dataflow::FContext&, const FDataflowOutput&);`
- L75 _private member_ `FStaticEvaluationFunctionPtr EvaluateFunction = nullptr;`
- L77 _private member_ `EPropertyBagContainerType ContainerType = EPropertyBagContainerType::None;`
- L79 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L80 _private prototype_ `void NotifyAssetVariablesChanged(UDataflow* DataflowAsset);`
- L81 _private prototype_ `void SetVariableMetaData(FName MetaDataName, const FString& Value);`
- L83 _private member_ `TWeakObjectPtr<UDataflow> WeakDataflowPtr;`

#### Free symbols / members of external scopes

- L87 _namespace_ `namespace UE`
- L87 _namespace_ `namespace Dataflow` (scope `UE`)
- L89 _prototype_ `void RegisterVariableNodes();` (scope `UE::Dataflow`)
