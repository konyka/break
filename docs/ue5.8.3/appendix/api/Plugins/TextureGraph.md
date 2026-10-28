# Plugins / TextureGraph

- module root: `Plugins/TextureGraph/Source/TextureGraph`
- headers: 71; symbols: 1926
- symbol kinds: class=100, delegate=10, enum=14, enumerator=73, function=430, macro=75, member=470, namespace=2, prototype=660, struct=40, typedef=26, variable=26
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, ImageCore, MutableRuntime, RHI, RenderCore, Renderer, TextureGraphEngine
- PublicIncludePathModuleNames: TextureGraphEngine

### `Plugins/TextureGraph/Source/TextureGraph/Public/Blueprint/TG_AsyncExportTask.h` (Public)


#### class `UTG_AsyncExportTask`  
`class UTG_AsyncExportTask : public UTG_AsyncRenderTaskBase`  
_L21-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_AsyncRenderTaskBase`
- L27 _public prototype_ `static UTG_AsyncExportTask* TG_AsyncExportTask(UTextureGraphBase* TextureGraph, const bool OverwriteTextures, const bool bSave, const bool bExportAll, const bool bDisableCache = false);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph" , meta=(DisplayName="Texture Graph Export (Async)", BlueprintInternalUseOnly = "true"))`
- L29 _public prototype_ `virtual void Activate() override;`
- L30 _public prototype_ `virtual const TArray<UTextureRenderTarget2D*>& ActivateBlocking(JobBatchPtr Batch);`
- L32 _public prototype_ `virtual void FinishDestroy() override;`
- L35 _public member_ `FTSExportTaskDelegate OnDone;` — `UPROPERTY(BlueprintAssignable, Category = "TextureGraph")`
- L39 _private member_ `bool bBlobberCachingState;`
- L41 _private prototype_ `void OnExportDone();` — `UFUNCTION()`
- L42 _private member_ `bool bOverwriteTextures = true;`
- L43 _private member_ `bool bSave = false;`
- L44 _private member_ `bool bExportAll = false;`
- L45 _private member_ `FExportSettings TargetExportSettings;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTSExportTaskDelegate);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTSExportTaskDelegate);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Blueprint/TG_AsyncRenderTask.h` (Public)


#### class `UTG_AsyncRenderTaskBase`  
`class UTG_AsyncRenderTaskBase : public UTG_AsyncTask`  
_L22-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_AsyncTask`
- L27 _public prototype_ `virtual const TArray<UTextureRenderTarget2D*>& ActivateBlocking(JobBatchPtr Batch);`
- L28 _public prototype_ `virtual void FinishDestroy() override;`
- L29 _public prototype_ `virtual void SetReadyToDestroy() override;`
- L31 _public prototype_ `void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool CleanupResources);`
- L34 _protected prototype_ `AsyncBool FinalizeAllOutputBlobs();`
- L35 _protected prototype_ `JobBatchPtr PrepareActivate(JobBatchPtr Batch, bool bIsAsync);`
- L36 _protected prototype_ `void GatherAllOutputBlobs();`
- L37 _protected prototype_ `void GatherAllRenderTargets();`
- L38 _protected prototype_ `AsyncBool GetRenderTextures();`
- L40 _protected member_ `TArray<UTextureRenderTarget2D*> OutputRts;`
- L41 _protected member_ `TArray<BlobPtr> OutputBlobs;`
- L42 _protected member_ `UTextureGraphBase* OriginalTextureGraphPtr;`
- L43 _protected member_ `UTextureGraphBase* TextureGraphPtr;`
- L44 _protected member_ `bool bShouldDestroyOnRenderComplete = true;`
- L45 _protected member_ `bool bRenderComplete = false;`

#### class `UTG_AsyncRenderTask`  
`class UTG_AsyncRenderTask : public UTG_AsyncRenderTaskBase`  
_L50-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_AsyncRenderTaskBase`
- L56 _public prototype_ `static UTG_AsyncRenderTask* TG_AsyncRenderTask(UTextureGraphBase* InTextureGraph);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph" , meta=(DisplayName="Texture Graph Render (Async)" , BlueprintInternalUseOnly = "true"))`
- L58 _public prototype_ `virtual void Activate() override;`
- L61 _public member_ `FTSRenderTaskDelegate OnDone;` — `UPROPERTY(BlueprintAssignable, Category = "TextureGraph")`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTSRenderTaskDelegate, const TArray<UTextureRenderTarget2D*>&, OutputRts);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTSRenderTaskDelegate, const TArray<UTextureRenderTarget2D*>&, OutputRts);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Blueprint/TG_AsyncTask.h` (Public)


#### class `UTG_AsyncTask`  
`class UTG_AsyncTask : public UBlueprintAsyncActionBase`  
_L17-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L23 _public prototype_ `virtual void Activate() override;`
- L29 _public prototype_ `virtual void RegisterWithTGAsyncTaskManger();` — Call to register this task with a AsyncTaskManager, it will not be destroyed until SetReadyToDestroy is called This allows having an action stay alive until SetReadyToDestroy is manually called, allowing it to be used inside loops or if the calling BP goes away
- L32 _public prototype_ `virtual void SetReadyToDestroy() override;` — Call when the action is completely done, this makes the action free to delete, and will unregister it with the game instance and AsyncTaskManager

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Blueprint/TG_AsyncTaskManager.h` (Public)


#### class `FTG_AsyncTaskManager`  
`class FTG_AsyncTaskManager`  
_L13-48_
- L16 _private function_ `FTG_AsyncTaskManager()` — Private constructor to enforce singleton pattern.
- L17 _private member_ `TArray<UTG_AsyncTask*> Tasks;`
- L19 _public function_ `static FTG_AsyncTaskManager& GetInstance()`
- L25 _public function_ `void RegisterTask(UTG_AsyncTask* Task)`
- L37 _public function_ `void UnRegisterTask(UTG_AsyncTask* Task)`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Blueprint/TG_BlueprintFunctionLibrary.h` (Public)


#### class `UTG_BlueprintFunctionLibrary`  
`class UTG_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-93_
- reflection: `UCLASS(meta=(ScriptName="TextureScreptingLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L27 _public prototype_ `static void SetTextureParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, UTexture* ParameterValue);` — `UFUNCTION(BlueprintCallable, Category="TextureGraph", meta=(Keywords="SetTextureParameterValue", WorldContext="WorldContextObject"))` — Sets a Texture parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L31 _public prototype_ `static UTexture* GetTextureParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName);` — `UFUNCTION(BlueprintCallable, Category="TextureGraph", meta=(Keywords="GetTextureParameterValue", WorldContext="WorldContextObject"))` — Gets a texture parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L35 _public prototype_ `static void SetScalarParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, float ParameterValue);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "SetScalarParameterValue", WorldContext = "WorldContextObject"))` — Sets a scalar parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L39 _public prototype_ `static float GetScalarParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "GetScalarParameterValue", WorldContext = "WorldContextObject"))` — Gets a scalar parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L43 _public prototype_ `static void SetBoolParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, bool ParameterValue);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "SetBoolParameterValue", WorldContext = "WorldContextObject"))` — Sets a boolean parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L47 _public prototype_ `static bool GetBoolParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "GetBoolParameterValue", WorldContext = "WorldContextObject"))` — Gets a string parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L51 _public prototype_ `static void SetStringParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, FString ParameterValue);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "SetBoolParameterValue", WorldContext = "WorldContextObject"))` — Sets a string parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L55 _public prototype_ `static FString GetStringParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "GetBoolParameterValue", WorldContext = "WorldContextObject"))` — Gets a String parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L59 _public prototype_ `static void SetVectorParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, FVector4f ParameterValue);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "SetVectorParameterValue", WorldContext = "WorldContextObject"))` — Sets a Vector parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L63 _public prototype_ `static FVector4f GetVectorParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "GetVectorParameterValue", WorldContext = "WorldContextObject"))` — Gets a Vector parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L67 _public prototype_ `static void SetColorParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, FLinearColor ParameterValue);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "SetColorParameterValue", WorldContext = "WorldContextObject"))` — Sets a color parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L71 _public prototype_ `static FLinearColor GetColorParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "GetColorParameterValue", WorldContext = "WorldContextObject"))` — Gets a color parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L75 _public prototype_ `static void SetSettingsParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName, int Width,int Height, FName FileName = "None", FName Path = "None", ETG_TextureFormat Format = ETG_TextureFormat::BGRA8 , ETG_TexturePresetType TextureType = ETG_TexturePresetType::None, TextureGroup LODTextureGroup = TextureGroup::TEXTUREGROUP_World, TextureCompressionSettings Compression = TextureCompressionSettings::TC_Default, bool SRGB = false);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "SetSettingsParameterValue", WorldContext = "WorldContextObject"))` — Sets a FTG_OutputSettings parameter value on the TextureGraph instance. Logs if ParameterName is invalid.
- L81 _public prototype_ `static FTG_OutputSettings GetSettingsParameterValue(UObject* WorldContextObject, UTextureGraph* TextureGraph, FName ParameterName , int& Width, int& Height);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "GetOutputSettingsParameterValue", WorldContext = "WorldContextObject"))` — Gets a FTG_OutputSettings parameter value from the TextureGraph instance. Logs if ParameterName is invalid.
- L85 _public prototype_ `static const TArray<UTextureRenderTarget2D*>& RenderTextureGraph(UObject* WorldContextObject, UTextureGraphBase* InTextureGraph);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "RenderTextureGraph", WorldContext = "WorldContextObject"))` — Render the texture graph and return an array of texture render targets.
- L89 _public prototype_ `static void ExportTextureGraph(UObject* WorldContextObject, UTextureGraphBase* InTextureGraph, bool bOverwriteTextures = true, bool bSave = false, bool bExportAll = false);` — `UFUNCTION(BlueprintCallable, Category = "TextureGraph", meta = (Keywords = "ExportTextureGraph", WorldContext = "WorldContextObject"))` — Export texture graph.
- L91 _public prototype_ `static void AddParamWarning(FName ParamName, UObject* ObjectPtr, FString FunctionName);`
- L92 _public prototype_ `static void AddError(UObject* ObjectPtr, FString FunctionName, FString Error);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Adjustment/TG_Expression_NormalFromHeightMap.h` (Public)


#### class `UTG_Expression_NormalFromHeightMap`  
`class UTG_Expression_NormalFromHeightMap : public UTG_Expression`  
_L15-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L22 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;`
- L26 _public member_ `float Offset = 0.002f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0.001", ClampMin = "0.001", UIMax = "0.1", ClampMax = "0.1"))` — Normals from height are generated by taking nearby points from the texture having some offset. Using smaller offset values means we are getting samples closer to the surface from the texture.
- L30 _public member_ `float Strength = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "2", ClampMax = "2"))` — Strength of the normals
- L34 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to be converted to Normal from height map
- L38 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image which is a single channel grayscale version of the input image
- L40 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L41 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Arrays/TG_Expression_Array.h` (Public)


#### class `UTG_Expression_Array4`  
`class UTG_Expression_Array4 : public UTG_Expression`  
_L13-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L18 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Arrays);`
- L19 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L23 _public member_ `FTG_Variant Input1;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — Texture at the first index of the output texture array
- L27 _public member_ `FTG_Variant Input2;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — Texture at the second index of the output texture array
- L31 _public member_ `FTG_Variant Input3;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — Texture at the third index of the output texture array
- L35 _public member_ `FTG_Variant Input4;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — Texture at the fourth index of the output texture array
- L39 _public member_ `FTG_VariantArray Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = "", HideInnerPropertiesInNode))` — All the input textures organized into an array
- L41 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L42 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Arrays/TG_Expression_ArrayGrid.h` (Public)


#### class `UTG_Expression_ArrayGrid`  
`class UTG_Expression_ArrayGrid : public UTG_Expression`  
_L13-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L18 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Arrays);`
- L19 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L23 _public member_ `FTG_VariantArray Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "", HideInnerPropertiesInNode))` — The input texture array. Must be an array object of type textures
- L27 _public member_ `int32 Rows = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The number of rows in the output grid. 0 or Negative values mean automatically distribute
- L31 _public member_ `int32 Columns = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The number of colums in the output grid. 0 or Negative values mean automatically distribute
- L35 _public member_ `FLinearColor BackgroundColor = FLinearColor::Transparent;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The background color to use for the output texture
- L39 _public member_ `FTG_Texture Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — A single output texture
- L41 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L42 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Arrays/TG_Expression_ArrayOps.h` (Public)


#### class `UTG_Expression_ArrayConcat`  
`class UTG_Expression_ArrayConcat : public UTG_Expression`  
_L16-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L21 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Arrays);`
- L22 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L26 _public member_ `FTG_VariantArray Input1;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Input-1"))` — The first array as part of the concatenation process
- L30 _public member_ `int32 StartIndex = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Input-1 Out Index"))` — The index at which Input1 array is going to start. Input 2 is going occupy the rest of the places within the array
- L34 _public member_ `FTG_VariantArray Input2;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Input-2"))` — The second array as part of the concatenation process
- L38 _public member_ `FTG_VariantArray Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = "", HideInnerPropertiesInNode))` — Concatenated array
- L40 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L41 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_ArraySplit`  
`class UTG_Expression_ArraySplit: public UTG_Expression`  
_L48-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L53 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Arrays);`
- L54 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L58 _public member_ `FTG_VariantArray Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "", MinValue))` — The array to slice
- L62 _public member_ `int32 StartIndex = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The starting index of the slicing operation. 0-indexed meaning that 0 indicates the first element of the input array
- L66 _public member_ `int32 EndIndex = -1;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The ending index of the slicing operation (non-inclusive). Negative values mean the end of the array.
- L70 _public member_ `bool bSplice = false;` — `UPROPERTY(meta = (TGType = "TG_Setting", PinDisplayName = "Splice"))` — The ending index of the slicing operation (non-inclusive). Negative values mean the end of the array.
- L74 _public member_ `FTG_VariantArray Sliced;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = "Sliced", HideInnerPropertiesInNode))` — Sliced part of the array
- L78 _public member_ `FTG_VariantArray Spliced;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = "Spliced", HideInnerPropertiesInNode))` — Spliced part of thea array
- L80 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L81 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Channel/TG_Expression_ChannelCombiner.h` (Public)


#### class `UTG_Expression_ChannelCombiner`  
`class UTG_Expression_ChannelCombiner : public UTG_Expression`  
_L15-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Channel);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `FTG_Texture Red;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "R"))` — The image that will end up in the red channel of the output image
- L29 _public member_ `FTG_Texture Green;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "G"))` — The image that will end up in the green channel of the output image
- L33 _public member_ `FTG_Texture Blue;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "B"))` — The image that will end up in the blue channel of the output image
- L37 _public member_ `FTG_Texture Alpha;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "A"))` — The image that will end up in the alpha channel of the output image
- L41 _public member_ `FTG_Texture Output = FTG_Texture::GetBlack();` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = "RGBA"))` — The output image that combines the red, green, blue and alpha images into a single one
- L43 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L44 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Channel/TG_Expression_ChannelSplitter.h` (Public)


#### class `UTG_Expression_ChannelSplitter`  
`class UTG_Expression_ChannelSplitter : public UTG_Expression`  
_L15-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Channel);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "RGBA"))` — The input texture
- L29 _public member_ `FTG_Texture Red = FTG_Texture::GetBlack();` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = "R", HideInnerPropertiesInNode))` — Red channel of the input
- L33 _public member_ `FTG_Texture Green = FTG_Texture::GetBlack();` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = "G", HideInnerPropertiesInNode))` — Green channel of the input
- L37 _public member_ `FTG_Texture Blue = FTG_Texture::GetBlack();` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = "B", HideInnerPropertiesInNode))` — Blue channel of the input
- L41 _public member_ `FTG_Texture Alpha = FTG_Texture::GetBlack();` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = "A", HideInnerPropertiesInNode))` — Alpha channel of the input
- L43 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L44 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Channel/TG_Expression_ChannelSwizzle.h` (Public)


#### class `UTG_Expression_ChannelSwizzle`  
`class UTG_Expression_ChannelSwizzle : public UTG_Expression`  
_L16-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L21 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Channel);`
- L22 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L26 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input texture
- L30 _public member_ `EColorChannel RedChannel = EColorChannel::Red;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Red"))` — The output in the red channel
- L34 _public member_ `EColorChannel GreenChannel = EColorChannel::Green;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Green"))` — The output in the Green channel
- L38 _public member_ `EColorChannel BlueChannel = EColorChannel::Blue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Blue"))` — The output in the Blue channel
- L42 _public member_ `EColorChannel AlphaChannel = EColorChannel::Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Alpha"))` — The output in the Alpha channel
- L46 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output texture after swizzle operation
- L49 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L50 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Color/TG_Expression_ColorCorrection.h` (Public)


#### class `UTG_Expression_ColorCorrection`  
`class UTG_Expression_ColorCorrection : public UTG_Expression`  
_L14-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L19 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L20 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L24 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to be color corrected
- L28 _public member_ `float Brightness = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1", ClampMax = "1"))` — Adjusts the overall lightness or darkness of an image. Increasing brightness makes it brighter, while decreasing brightness makes it darker.
- L32 _public member_ `float Contrast = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "10", ClampMax = "10"))` — Modifies the difference between light and dark areas within an image. Increasing contrast makes light areas lighter and dark areas darker, while decreasing contrast reduces this difference, resulting in a more uniform appearance.
- L36 _public member_ `float Gamma = 0.5f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "10", ClampMax = "10"))` — Gamma can be used to manipulate the curve
- L40 _public member_ `float Saturation = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "10", ClampMax = "10"))` — Saturation is how intense and pure a color appears.
- L44 _public member_ `float Temperature = 6500.0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "1000", ClampMin = "1000", UIMax = "20000", ClampMax = "20000"))` — The temperature adjustment for the image
- L48 _public member_ `float TemperatureStrength = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The strength of the temperature application. It just gives more control over mixing the original image with the temperature applied image
- L52 _public member_ `float TemperatureBrightnessNormalization = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — How to normalize the original brightness of the image with the new brigthness (after temperature adjustment)
- L56 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image
- L58 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L59 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Color/TG_Expression_Grayscale.h` (Public)


#### class `UTG_Expression_Grayscale`  
`class UTG_Expression_Grayscale : public UTG_Expression`  
_L15-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to be converted to grayscale
- L29 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image which is a single channel grayscale version of the input image
- L31 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L32 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Color/TG_Expression_HSV.h` (Public)


#### class `UTG_Expression_RGB2HSV`  
`class UTG_Expression_RGB2HSV : public UTG_Expression_OneInput`  
_L19-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L24 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L25 _public function_ `virtual FText GetTooltipText() const override`
- L26 _public function_ `virtual FName GetCategory() const override`
- L30 _protected function_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override` — This is unsupported because it only makes sense on a vector input
- L31 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const Value, size_t Count);`
- L32 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_HSV2RGB`  
`class UTG_Expression_HSV2RGB : public UTG_Expression_OneInput`  
_L39-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L44 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L45 _public function_ `virtual FText GetTooltipText() const override`
- L46 _public function_ `virtual FName GetCategory() const override`
- L50 _protected function_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override` — This is unsupported because it only makes sense on a vector input
- L51 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const Value, size_t Count);`
- L52 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_HSV`  
`class UTG_Expression_HSV : public UTG_Expression_OneInput`  
_L59-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L67 _public member_ `float Hue = 1.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", PinDisplayName = "Hue (Normalized)", DisplayName = "Hue (Normalized)"))` — Defines the basic color tone, such as red, green, or blue, without considering brightness or intensity. Adjusting the hue changes the overall color appearance while maintaining its saturation and brightness. The normalized hue. Please divide your [0, 359] hue values by 359 for this input
- L71 _public member_ `float Saturation = 1.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — Controls the intensity of the color. Higher values represent more vivid colors, while lower values produce muted tones.
- L75 _public member_ `float Value = 1.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — Specifies the brightness or darkness of the color. Higher values correspond to brighter colors, while lower values result in darker shades.
- L77 _public function_ `virtual FText GetTooltipText() const override`
- L78 _public function_ `virtual FName GetCategory() const override`
- L82 _protected function_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const ValuePtr, size_t Count) override` — This is unsupported because it only makes sense on a vector input
- L83 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const ValuePtr, size_t Count);`
- L84 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Color/TG_Expression_Premult.h` (Public)


#### class `UTG_Expression_Premult`  
`class UTG_Expression_Premult : public UTG_Expression`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L21 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L22 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L26 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to be used
- L30 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the image with the premultiplied alpha
- L32 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L33 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/CommandChange/TG_PinConnectionChange.h` (Public)


#### class `FTG_PinConnectionChange`  
`class FTG_PinConnectionChange : public FCommandChange`  
_L18-35_
- inherits: `FCommandChange`
- desc: This class helps to Undo the pin connection correctly as the Blob is not serialized so if the expression property is not connected and is holding a reference of blob it is not rest when undoing the connection
- L21 _public prototype_ `static void StoreChange(UTG_Graph* InGraph, UTG_Node& NodeFrom, FTG_Name& PinFromName);`
- L22 _public prototype_ `FTG_PinConnectionChange(UTG_Graph* InGraph, UTG_Node& NodeFrom, FTG_Name& PinFromName);`
- L24 _public function_ `virtual FString ToString() const override`
- L29 _public function_ `virtual void Apply(UObject* Object) override`
- L30 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L33 _private member_ `UTG_Graph* Graph;`
- L34 _private member_ `UTG_Pin* PinTo;`

#### class `FTG_PinConnectionBreakChange`  
`class FTG_PinConnectionBreakChange : public FCommandChange`  
_L40-57_
- inherits: `FCommandChange`
- desc: This class helps to Redo the pin connection Break correctly as the Blob is not serialized so if the expression property is not connected and is holding a reference of blob it is not rest when redoing the connection
- L43 _public prototype_ `static void StoreChange(UTG_Graph* InGraph, UTG_Node& NodeFrom, FTG_Name& PinFromName);`
- L44 _public prototype_ `FTG_PinConnectionBreakChange(UTG_Graph* InGraph, UTG_Node& NodeFrom, FTG_Name& PinFromName);`
- L46 _public function_ `virtual FString ToString() const override`
- L51 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L52 _public function_ `virtual void Revert(UObject* Object) override`
- L55 _private member_ `UTG_Graph* Graph;`
- L56 _private member_ `UTG_Pin* PinTo;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_Blur.h` (Public)


#### enum `EBlurType`  
`enum class EBlurType : uint8`  
_L13-18_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Gaussian = 0 UMETA(DisplayName = "Gaussian")`
- L16 _public enumerator_ `Directional = 1 UMETA(DisplayName = "Directional")`
- L17 _public enumerator_ `Radial = 2 UMETA(DisplayName = "Radial")`

#### class `UTG_Expression_Blur`  
`class UTG_Expression_Blur : public UTG_Expression`  
_L21-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L26 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Filter);`
- L30 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;` — Used to implement EditCondition logic for both Node UI and Details View
- L35 _public member_ `int32 Radius = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 100, EditConditionHides))` — Controls how much an texture is blurred
- L39 _public member_ `float Angle = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = -180, ClampMax = 180,EditConditionHides))` — Adjusting the angle changes the direction at which the blur effect is applied."
- L43 _public member_ `float Strength = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 1, EditConditionHides))` — Determines how intense the blurring effect is applied. Higher values result in stronger blur, while lower values produce a milder effect.
- L47 _public member_ `EBlurType BlurType = EBlurType::Gaussian;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", RegenPinsOnChange))` — Style of blurring applied to a texture.
- L51 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output texture having blurred effect
- L55 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The input texture to apply the blur effect
- L57 _public function_ `virtual FText GetTooltipText() const override`
- L58 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_Brightness.h` (Public)


#### class `UTG_Expression_Brightness`  
`class UTG_Expression_Brightness : public UTG_Expression`  
_L19-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L24 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L25 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L29 _public member_ `float Brightness = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1", ClampMax = "1"))` — Adjusts the overall lightness or darkness of an image. Increasing brightness makes it brighter, while decreasing brightness makes it darker.
- L33 _public member_ `float Contrast = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "10", ClampMax = "10"))` — Modifies the difference between light and dark areas within an image. Increasing contrast makes light areas lighter and dark areas darker, while decreasing contrast reduces this difference, resulting in a more uniform appearance.
- L37 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input texture to adjust the brightness/contrast for
- L41 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image
- L42 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L43 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_EdgeDetect.h` (Public)


#### class `UTG_Expression_EdgeDetect`  
`class UTG_Expression_EdgeDetect : public UTG_Expression`  
_L13-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L18 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Filter);`
- L22 _public member_ `float Thickness = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0.1, ClampMax = 30, UIMin = 0.1, UIMax = 1, EditConditionHides))` — What is the thickness of the edge
- L26 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output texture having blurred effect
- L30 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The input texture to apply the blur effect
- L32 _public function_ `virtual FText GetTooltipText() const override`
- L33 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_ErodeDilate.h` (Public)


#### enum `EErodeOrDilate`  
`enum class EErodeOrDilate : uint8`  
_L19-23_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Erode = 0 UMETA(DisplayName = "Erode")`
- L22 _public enumerator_ `Dilate = 1 UMETA(DisplayName = "Dilate")`

#### enum `EErodeDilateKernelType`  
`enum class EErodeDilateKernelType : uint8`  
_L29-34_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `Box = 0 UMETA(DisplayName = "Box")`
- L32 _public enumerator_ `Circular = 1 UMETA(DisplayName = "Circular")`
- L33 _public enumerator_ `Diamond = 2 UMETA(DisplayName = "Diamond")`

#### class `UTG_Expression_ErodeDilate`  
`class UTG_Expression_ErodeDilate : public UTG_Expression`  
_L40-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L45 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Filter);`
- L46 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L50 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to
- L62 _public member_ `int32 Size = 2;` — `UPROPERTY(meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 64, UIMin = 0, UIMax = 64))` — The size of the kernel to use
- L66 _public member_ `EErodeDilateKernelType Kernel = EErodeDilateKernelType::Box;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The type of the kernel to use
- L70 _public member_ `EErodeOrDilate Type = EErodeOrDilate::Erode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — Whether to erode or dilate
- L74 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image which is a single channel grayscale version of the input image
- L76 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L77 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_Levels.h` (Public)


#### enum `ELevelsExpressionType`  
`enum class ELevelsExpressionType : uint8`  
_L17-21_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `LowMidHigh = 0 UMETA(DisplayName = "Manual")`
- L20 _public enumerator_ `AutoLowHigh UMETA(DisplayName = "Auto Levels")`

#### struct `FTG_LevelsSettings`  
`struct FTG_LevelsSettings`  
_L26-69_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public member_ `float Low = 0;` — `UPROPERTY(EditAnywhere, Category = "Levels", meta = (PinDisplayName = "Low", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The Low value of the Levels adjustment, any pixel under that value is set to black. Default is 0.
- L37 _public member_ `float Mid = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Levels", meta = (PinDisplayName = "Mid", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The mid value of the Levels adjustment, must be in the range [Min, Max] and the Default is 0.5. The mid value determine where the smoothing curve applying the midpoint filter is crossing 0.5.
- L41 _public member_ `float High = 1;` — `UPROPERTY(EditAnywhere, Category = "Levels", meta = (PinDisplayName = "High", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The High value of the Levels adjustment, any pixel above that value is set to white. Default is 1.
- L43 _public prototype_ `bool SetLow(float InValue);`
- L44 _public prototype_ `bool SetMid(float InValue);`
- L45 _public prototype_ `bool SetHigh(float InValue);`
- L48 _public prototype_ `float EvalRange(float Val) const;` — Eval Low-High range mapping on value
- L50 _public prototype_ `float EvalRangeInv(float Val) const;` — Eval reverse Low-High range mapping on value
- L53 _public prototype_ `float EvalMidExponent() const;` — Evaluate the MidExponent of the power curve applying the midpoint filter
- L54 _public prototype_ `bool SetMidFromMidExponent(float InExponent);`
- L56 _public function_ `void InitFromString(const FString& StrVal)`
- L61 _public function_ `FString ToString() const`

#### class `UTG_Expression_Levels`  
`class UTG_Expression_Levels : public UTG_Expression`  
_L76-143_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L80 _private member_ `FTG_LevelsSettings Levels;`
- L82 _private member_ `TSharedPtr<FLevels> LevelsControl;`
- L85 _public prototype_ `virtual void PostLoad() override;`
- L87 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L90 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;` — Used to implement EditCondition logic for both Node UI and Details View
- L95 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L96 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L99 _public member_ `ELevelsExpressionType LevelsExpressionType = ELevelsExpressionType::LowMidHigh;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Type", PinNotConnectable = true, RegenPinsOnChange))`
- L103 _public member_ `FTG_Texture Input;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to adjust the levels for
- L107 _public member_ `float LowValue = 0;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Low", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", EditConditionHides, MD_ScalarEditor))` — The Low value of the Levels adjustment, any pixel under that value is set to black. Default is 0.
- L108 _public prototype_ `void SetLowValue(float InValue);`
- L113 _public member_ `float MidValue = 0.5f;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Mid", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", EditConditionHides, MD_ScalarEditor))` — The mid value of the Levels adjustment, must be in the range [Min, Max] and the Default is 0.5. The mid value determine where the smoothing curve applying the midpoint filter is crossing 0.5.
- L114 _public prototype_ `void SetMidValue(float InValue);`
- L118 _public member_ `float HighValue = 1;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "High", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", EditConditionHides, MD_ScalarEditor))` — The High value of the Levels adjustment, any pixel above that value is set to white. Default is 1.
- L119 _public prototype_ `void SetHighValue(float InValue);`
- L123 _public member_ `float OutLowValue = 0;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Out Low", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", EditConditionHides, MD_ScalarEditor))` — The black point of the output. Moving this will remap the dark point to this value. Default is 0
- L124 _public prototype_ `void SetOutLowValue(float InValue);`
- L128 _public member_ `float OutHighValue = 1;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Out High", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", EditConditionHides, MD_ScalarEditor))` — The white point of the output. Moving this will remap the white point to this value. Default is 1
- L129 _public prototype_ `void SetOutHighValue(float InValue);`
- L133 _public member_ `float MidAutoLevels = 0.5;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Mid Auto Levels", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", EditConditionHides, MD_ScalarEditor))` — The High value of the Levels adjustment, any pixel above that value is set to white. Default is 1.
- L138 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image filtered result of the Levels operator
- L140 _public function_ `virtual FText GetTooltipText() const override`
- L142 _public function_ `bool IsAutoLevel() const`

#### class `UTG_Expression_HistogramScan`  
`class UTG_Expression_HistogramScan : public UTG_Expression`  
_L149-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L153 _private member_ `TSharedPtr<FLevels> LevelsControl;`
- L157 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L158 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L162 _public member_ `FTG_Texture Input;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", PinDisplayName = "", MD_HistogramLuminance))` — The input image to adjust the levels for
- L166 _public member_ `float Position = 0.5f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", MD_ScalarEditor))` — Drives the position of the histogram of the input image
- L170 _public member_ `float Contrast = 0.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", MD_ScalarEditor))` — Drives the contrast of the histogram of the input image
- L174 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image filtered result of the Levels operator
- L176 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_HistogramRange`  
`class UTG_Expression_HistogramRange : public UTG_Expression`  
_L184-213_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L188 _private member_ `TSharedPtr<FLevels> LevelsControl;`
- L192 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L193 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L197 _public member_ `FTG_Texture Input;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", PinDisplayName = "", MD_HistogramLuminance))` — The input image to adjust the levels for
- L201 _public member_ `float Position = 0.5f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", MD_ScalarEditor))` — Drives the center of the levels out
- L205 _public member_ `float Range = 1.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", MD_ScalarEditor))` — Drives the range of the levels out
- L209 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image filtered result of the Levels operator
- L211 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L71 _prototype_ `void FTG_LevelsSettings_VarPropertySerialize(FTG_Var::VarPropertySerialInfo&);`
- L72 _prototype_ `template <> FString TG_Var_LogValue(FTG_LevelsSettings& Value);`
- L73 _prototype_ `template <> FString TG_Var_LogValue(FTG_LevelsSettings& Value);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_Threshold.h` (Public)


#### class `UTG_Expression_Threshold`  
`class UTG_Expression_Threshold : public UTG_Expression`  
_L15-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Adjustment);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `FTG_Texture Input;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", PinDisplayName = "", MD_HistogramLuminance))` — The input image to adjust the levels for
- L29 _public member_ `float Threshold;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", PinDisplayName = "Threshold", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1", MD_ScalarEditor))` — The min value to be used. Can be an image (Defaults to 0/black)
- L33 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output image which is a single channel grayscale version of the input image
- L35 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Filter/TG_Expression_Warp.h` (Public)


#### class `UTG_Expression_Warp`  
`class UTG_Expression_Warp : public UTG_Expression`  
_L17-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L22 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Filter);`
- L26 _public member_ `TEnumAsByte<EWarp::Type> Type = EWarp::Directional;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", RegenPinsOnChange))` — The type of warp that we want on the input image
- L30 _public member_ `float Intensity = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0.0, ClampMax = 20, UIMin = 0.0, UIMax = 1, EditConditionHides))` — What is the intensity of the warp. Warp of 1 is 10% (1/10th) of the width of the input image
- L34 _public member_ `float Angle = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0.0, ClampMax = 360, UIMin = 0.0, UIMax = 360, EditConditionHides))` — Angle of the directional warp 0 - 360 degrees
- L38 _public member_ `float PhaseU = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = -1, ClampMax = 1, UIMin = -1, UIMax = 1, EditConditionHides))` — Phase X for the Sine wave warp (for U coordinate in UV space)
- L42 _public member_ `float PhaseV = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = -1, ClampMax = 1, UIMin = -1, UIMax = 1, EditConditionHides))` — Phase Y for the Sine wave warp (for V coordinate in UV space)
- L46 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The input texture to apply the warp
- L50 _public member_ `FTG_Texture Mask;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The mask used for the warp effect
- L54 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output texture having blurred effect
- L59 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;` — Used to implement EditCondition logic for both Node UI and Details View
- L62 _public function_ `virtual FText GetTooltipText() const override`
- L63 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Bool.h` (Public)


#### class `UTG_Expression_Bool`  
`class UTG_Expression_Bool : public UTG_Expression_InputParam`  
_L12-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L15 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L19 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L22 _public member_ `bool Bool = false;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_InputParam", PinDisplayName = ""))`
- L26 _public member_ `bool ValueOut = false;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the color value
- L28 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L29 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L30 _public prototype_ `virtual FName GetTitleName() const override;`
- L31 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Color.h` (Public)


#### class `UTG_Expression_Color`  
`class UTG_Expression_Color : public UTG_Expression_InputParam`  
_L14-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L17 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `FLinearColor Color = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_InputParam", PinDisplayName = ""))` — The color value
- L29 _public member_ `FLinearColor ValueOut = FLinearColor::Black;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the color value
- L32 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L33 _public prototype_ `virtual FName GetTitleName() const override;`
- L34 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L36 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Graph.h` (Public)


#### class `UTG_Expression_Graph`  
`class UTG_Expression_Graph : public UTG_Expression`  
_L20-36_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UTG_Expression`
- L24 _public prototype_ `TG_DECLARE_DYNAMIC_EXPRESSION(TG_Category::Input);`
- L25 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L29 _protected member_ `mutable TArray<FTG_Id> InParamIds;`
- L30 _protected member_ `mutable TArray<FTG_Id> OutParamIds;`
- L32 _protected function_ `virtual UTG_Graph* GetGraph() const`
- L33 _protected prototype_ `void NotifyGraphChanged();`
- L35 _protected prototype_ `virtual void SetupAndEvaluate(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_TextureGraph`  
`class UTG_Expression_TextureGraph : public UTG_Expression_Graph`  
_L43-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Graph`
- L48 _public prototype_ `UTG_Expression_TextureGraph();`
- L49 _public prototype_ `virtual ~UTG_Expression_TextureGraph();`
- L55 _protected member_ `TWeakObjectPtr<UTextureGraph> PreEditTextureGraph;` — Only in editor mode, in the case the TextureGraph is assigned from Details panel we need to remember the previous version
- L57 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L58 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L59 _public prototype_ `virtual void PostEditUndo() override;`
- L62 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L63 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;`
- L66 _public member_ `TObjectPtr<UTextureGraph> TextureGraph;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The TextureGraph to use for the sub-graph
- L68 _public prototype_ `void SetTextureGraph(UTextureGraph* InTextureGraph);`
- L70 _public prototype_ `virtual bool CanHandleAsset(UObject* Asset) override;`
- L71 _public prototype_ `virtual void SetAsset(UObject* Asset) override;`
- L74 _protected prototype_ `virtual void Initialize() override;`
- L75 _protected prototype_ `virtual void CopyVarGeneric(const FTG_Argument& Arg, FTG_Var* InVar, bool CopyVarToArg) override;`
- L77 _protected prototype_ `virtual UTG_Graph* GetGraph() const override;`
- L79 _protected prototype_ `void OnTextureGraphPreSave(UObject* Object, FObjectPreSaveContext SaveContext);`
- L82 _private member_ `TObjectPtr<UTG_Graph> RuntimeGraph;` — `UPROPERTY(Transient)` — The runtime graph instance to use for the sub-graph
- L84 _private member_ `FDelegateHandle PreSaveHandle;` — delegate handle for global ObjectPreSave event
- L86 _private prototype_ `bool CheckDependencies(const UTextureGraph* InTextureGraph) const;`
- L87 _private prototype_ `void SetTextureGraphInternal(UTextureGraph* InTextureGraph);`
- L91 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_InputParam.h` (Public)


#### class `UTG_Expression_InputParam`  
`class UTG_Expression_InputParam : public UTG_Expression`  
_L14-35_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTG_Expression`
- L20 _protected prototype_ `virtual FTG_SignaturePtr BuildInputParameterSignature() const;` — these 2 methods need to be implemented to provide concrete signatures for derived InputParam expression classes
- L21 _protected prototype_ `virtual FTG_SignaturePtr BuildInputConstantSignature() const;`
- L22 _protected function_ `virtual bool ShouldShowSettings() const override`
- L26 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _public member_ `bool bIsConstant = false;` — `UPROPERTY(Setter)` — Node can be converted from Param to Constant
- L32 _public prototype_ `void SetbIsConstant(bool InIsConstant);`
- L33 _public prototype_ `void ToggleIsConstant();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L38 _macro_ `#define TG_DECLARE_INPUT_PARAM_EXPRESSION(Category) \`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Material.h` (Public)


#### class `UTG_Expression_Material`  
`class UTG_Expression_Material : public UTG_Expression_MaterialBase`  
_L19-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_MaterialBase`
- L24 _public prototype_ `UTG_Expression_Material();`
- L25 _public prototype_ `virtual ~UTG_Expression_Material();`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual void PostEditUndo() override;`
- L31 _public prototype_ `virtual void PostLoad() override;`
- L36 _public member_ `TObjectPtr<UMaterialInterface> Material_DEPRECATED;` — `UE_DEPRECATED(5.6, "Material field has been deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the InputMaterial to specify the Material asset referenced"))`
- L41 _public member_ `FTG_Material InputMaterial;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_InputParam", DisplayName = "Material", PinDisplayName = "Material"))` — The input material referenced by this Material node
- L42 _public prototype_ `void SetInputMaterial(const FTG_Material& InMaterial);`
- L46 _public member_ `FName RenderedAttribute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", GetOptions = "GetRenderAttributeOptions"))` — The Material attribute identifier among all the attributes of the material that is rendered in the output
- L47 _public prototype_ `void SetRenderedAttribute(FName InRenderedAttribute);`
- L51 _public prototype_ `TArray<FName> GetRenderAttributeOptions() const;` — `UFUNCTION(CallInEditor)` — THe list of Rendered attribute options available
- L56 _public member_ `int32 NumWarmupFrames = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 32, PinDisplayName = "Num Warmup Frames"))` — When Material references VT, can specify the number of warmup frames. Default value is 0 meaning that the CVar <TG.VirtualTexture.NumWarmupFrames> is used instead
- L57 _public function_ `virtual int32 GetNumVirtualTextureWarmupFrames() const override`
- L59 _public prototype_ `virtual bool CanHandleAsset(UObject* Asset) override;`
- L60 _public prototype_ `virtual void SetAsset(UObject* Asset) override;`
- L61 _public function_ `virtual FText GetTooltipText() const override`
- L66 _protected member_ `TObjectPtr<UMaterialInterface> MaterialCopy = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)` — Transient and per instance Data, recreated on every new instance from the reference material
- L70 _protected prototype_ `virtual void SetMaterialInternal(UMaterialInterface* InMaterial) override;` — As the "Material" or the "InputMaterial" properties change we update the current active "MaterialCopy" and pass on internally as the active "GetMaterial()"
- L75 _protected member_ `FName TitleName = TEXT("Mat` — `UPROPERTY()` — Title name is still used mostly for legacy but not exposed anymore in the details. This is changed on the node itself and then call SetTitleName and rename the InnputMaterial Alias name
- L77 _protected prototype_ `virtual void Initialize() override;`
- L81 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L82 _public prototype_ `virtual FName GetTitleName() const override;`
- L84 _public function_ `virtual FName GetCategory() const override`
- L87 _protected function_ `virtual TObjectPtr<UMaterialInterface> GetMaterial() const override`
- L88 _protected prototype_ `virtual EDrawMaterialAttributeTarget GetRenderedAttributeId() override;`
- L91 _protected member_ `FDelegateHandle PreSaveHandle;`
- L92 _protected prototype_ `void OnReferencedObjectPreSave(UObject* Object, FObjectPreSaveContext SaveContext);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L16 _typedef_ `typedef std::weak_ptr<class Job> JobPtrW;`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_MaterialFunction.h` (Public)


#### class `UTG_Expression_MaterialFunction`  
`class UTG_Expression_MaterialFunction : public UTG_Expression_MaterialBase`  
_L17-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_MaterialBase`
- L22 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L23 _public prototype_ `virtual void PostEditUndo() override;`
- L28 _public member_ `TObjectPtr<UMaterialFunctionInterface> MaterialFunction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category = NoCategory, meta = (TGType = "TG_Setting", TGPinNotConnectable))` — The material function to employ for rendering
- L29 _public prototype_ `void SetMaterialFunction(UMaterialFunctionInterface* InMaterialFunction);`
- L34 _public member_ `int32 NumWarmupFrames = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 32, PinDisplayName = "Num Warmup Frames"))` — When MaterialFunction references VT, can specify the number of warmup frames. Default value is 0 meaning that the CVar <TG.VirtualTexture.NumWarmupFrames> is used instead
- L35 _public function_ `virtual int32 GetNumVirtualTextureWarmupFrames() const override`
- L37 _public prototype_ `virtual bool CanHandleAsset(UObject* Asset) override;`
- L38 _public prototype_ `virtual void SetAsset(UObject* Asset) override;`
- L40 _public function_ `virtual FText GetTooltipText() const override`
- L43 _protected prototype_ `virtual void Initialize() override;`
- L45 _protected prototype_ `UMaterialInterface* CreateMaterialReference();`
- L46 _protected member_ `TObjectPtr<UMaterialInterface> ReferenceMaterial = nullptr;`
- L47 _protected function_ `virtual TObjectPtr<UMaterialInterface> GetMaterial() const`
- L48 _protected function_ `virtual EDrawMaterialAttributeTarget GetRenderedAttributeId()`
- L51 _private prototype_ `void SetMaterialFunctionInternal(UMaterialFunctionInterface* InMaterialFunction);`
- L55 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L56 _public prototype_ `virtual bool CanRenameTitle() const override;`
- L58 _public function_ `virtual FName GetCategory() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_OutputSettings.h` (Public)


#### class `UTG_Expression_OutputSettings`  
`class UTG_Expression_OutputSettings : public UTG_Expression`  
_L15-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Input);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L23 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;`
- L27 _public member_ `FTG_OutputSettings Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node
- L31 _public member_ `FTG_OutputSettings Input;` — `UPROPERTY(meta = (TGType = "TG_Input", HideChildProperties))` — Input is the one that recieves the Settings from another node
- L35 _public member_ `FTG_OutputSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_InputParam", PinDisplayName = ""))` — Settings will overwrite the Input values from another node
- L37 _public member_ `class ULayerChannel* Channel;`
- L38 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L39 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L40 _public prototype_ `virtual FName GetTitleName() const override;`
- L41 _public function_ `virtual FText GetTooltipText() const override`
- L44 _private member_ `FTG_OutputSettings PreviousInput;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Scalar.h` (Public)


#### class `UTG_Expression_Scalar`  
`class UTG_Expression_Scalar : public UTG_Expression_InputParam`  
_L14-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L17 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `float Scalar = 1.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_InputParam", PinDisplayName = ""))` — The floating point constant
- L29 _public member_ `float ValueOut = 1.0f;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the floating point constant
- L31 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L32 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L33 _public prototype_ `virtual FName GetTitleName() const override;`
- L34 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_String.h` (Public)


#### class `UTG_Expression_String`  
`class UTG_Expression_String : public UTG_Expression_InputParam`  
_L12-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L15 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L19 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L23 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_InputParam", PinDisplayName = ""))` — The string constant
- L27 _public member_ `FString ValueOut;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the string constant
- L29 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L30 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L31 _public prototype_ `virtual FName GetTitleName() const override;`
- L32 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Texture.h` (Public)


#### class `UTG_Expression_Texture`  
`class UTG_Expression_Texture : public UTG_Expression_InputParam`  
_L16-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L19 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L23 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;`
- L26 _public prototype_ `void SetSourceInternal();`
- L30 _public member_ `FTG_Texture Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = "", HideInnerPropertiesInNode))` — The output of the node, which is the loaded texture asset
- L31 _public member_ `FString OutputPath;`
- L35 _public member_ `TObjectPtr<UTexture> Source;` — `UPROPERTY(EditAnywhere, Setter, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Input", TGPinNotConnectable))` — The source asset to be used to generate the Output
- L39 _public member_ `FTG_Texture Texture;` — `UPROPERTY(EditAnywhere, Setter, Category = NoCategory, meta = (TGType = "TG_InputParam"))` — The input texture that was loaded from the asset
- L41 _public prototype_ `void SetSource(UTexture* InSource);`
- L42 _public prototype_ `void SetTextureInternal();`
- L43 _public prototype_ `void SetTexture(const FTG_Texture& InTexture);`
- L46 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _public member_ `class ULayerChannel* Channel;`
- L49 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L50 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L51 _public prototype_ `virtual FName GetTitleName() const override;`
- L52 _public function_ `virtual FText GetTooltipText() const override`
- L53 _public function_ `virtual bool IgnoreInputTextureOnUndo() const override`
- L55 _public prototype_ `virtual void SetAsset(UObject* Asset) override;`
- L56 _public prototype_ `virtual bool CanHandleAsset(UObject* Asset) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_TextureDescriptor.h` (Public)


#### class `UTG_Expression_TextureDescriptor`  
`class UTG_Expression_TextureDescriptor : public UTG_Expression_InputParam`  
_L12-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L15 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L19 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L23 _public member_ `int32 Width = (int32)EResolution::Resolution2048;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input"))` — The width of the texture. 0 and negative values mean "Auto"
- L27 _public member_ `int32 Height = (int32)EResolution::Resolution2048;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input"))` — The height of the texture. 0 and negative values mean "Auto"
- L31 _public member_ `bool bIsSRGB = false;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", PinDisplayName = "sRGB"))` — The height of the texture. 0 and negative values mean "Auto"
- L35 _public member_ `ETG_TextureFormat Format = ETG_TextureFormat::Auto;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The height of the texture. 0 and negative values mean "Auto"
- L39 _public member_ `FTG_TextureDescriptor Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the color value
- L41 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L42 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_TexturePath.h` (Public)


#### class `UTG_Expression_TexturePath`  
`class UTG_Expression_TexturePath : public UTG_Expression_InputParam`  
_L16-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L19 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L24 _protected prototype_ `virtual FTG_SignaturePtr BuildInputConstantSignature() const override;` — Special case for TexturePath Constant signature, we want to keep the Path Input connectable in that case so do this in the override version of BuildInputConstantSignature()
- L28 _protected prototype_ `bool ValidateInputPath(FString& ValidatedPath) const;` — Validate the input path, returning the actual path to use empty if the input path is NOT valid
- L30 _protected prototype_ `void ReportError(MixUpdateCyclePtr Cycle);`
- L31 _protected prototype_ `static TiledBlobPtr LoadStaticImage(FTG_EvaluationContext* InContext, const FString& Filename, BufferDescriptor* DesiredDesc);`
- L34 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L35 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;`
- L39 _public member_ `FTG_VariantArray Output;` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = "", HideInnerPropertiesInNode))` — All the output textures from this node. Note that it outputs an array of textures.
- L40 _public member_ `FString OutputPath;`
- L44 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_InputParam", NoResetToDefault))` — Input file path of the texture. If the path is a directory then all files from that directory are loaded
- L46 _public member_ `class ULayerChannel* Channel;`
- L47 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L48 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L49 _public prototype_ `virtual FName GetTitleName() const override;`
- L50 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Input/TG_Expression_Vector.h` (Public)


#### class `UTG_Expression_Vector`  
`class UTG_Expression_Vector : public UTG_Expression_InputParam`  
_L14-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_InputParam`
- L17 _private prototype_ `TG_DECLARE_INPUT_PARAM_EXPRESSION(TG_Category::Input);`
- L21 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `FVector4f Vector = FVector4f(0);` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_InputParam", PinDisplayName = ""))` — The 4 dimensional vector X, Y, Z and W.
- L29 _public member_ `FVector4f ValueOut = FVector4f(0);` — `UPROPERTY(meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the color value
- L31 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L32 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L33 _public prototype_ `virtual FName GetTitleName() const override;`
- L34 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_Blend.h` (Public)


#### class `UTG_Expression_Blend`  
`class UTG_Expression_Blend : public UTG_Expression`  
_L16-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Maths) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L25 _public member_ `TEnumAsByte<EBlendModes::Type> BlendMode = EBlendModes::Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — Blend mode determine how inputs texture mix together.
- L29 _public member_ `float Opacity = 1.0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The opacity to be used in conjunction with the mask. The final blend value = 'Mask[RedChannel] * Opacity'
- L33 _public member_ `bool bIgnoreAlpha = true;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Ignore Alpha"))` — If true, it will ignore the alpha channel blending and keep the background alpha.
- L36 _public member_ `bool bClamp = true;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Clamp"))`
- L39 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))`
- L43 _public member_ `FTG_Texture Foreground;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The first input (Foreground) to the blend function
- L47 _public member_ `FTG_Texture Background;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The second input (Background) to the blend function
- L51 _public member_ `FTG_Texture Mask;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The mask used to calculate the final blend value which is, 'Mask[RedChannel] * Opacity'. Default value is white.
- L54 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_Clamp.h` (Public)


#### class `UTG_Expression_Clamp`  
`class UTG_Expression_Clamp : public UTG_Expression_Variant`  
_L18-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L25 _public member_ `FTG_Variant Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to clamp
- L29 _public member_ `FTG_Variant MinValue = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Min"))` — The desired min value (defaults to 0/black)
- L33 _public member_ `FTG_Variant MaxValue = 1;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Max"))` — The desired max value (defaults to 1/white)
- L35 _public function_ `virtual FText GetTooltipText() const override`
- L36 _public function_ `virtual FName GetCategory() const override`
- L39 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L40 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L41 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L42 _protected function_ `virtual bool ErrorCheckInputTextures() const`

#### class `UTG_Expression_SmoothStep`  
`class UTG_Expression_SmoothStep : public UTG_Expression_Variant`  
_L49-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L57 _public member_ `FTG_Variant Input = 0;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The angle in radians to run the trigonometric function on
- L60 _public member_ `FTG_Variant Min = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", UIMin = "0", UIMax = "100"))`
- L63 _public member_ `FTG_Variant Max = 1;` — `UPROPERTY(meta = (TGType = "TG_Input", UIMin = "0", UIMax = "100"))`
- L65 _public function_ `virtual FText GetTooltipText() const override`
- L66 _public function_ `virtual FName GetCategory() const override`
- L69 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L70 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L71 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L72 _protected function_ `virtual bool ErrorCheckInputTextures() const`

#### class `UTG_Expression_Min`  
`class UTG_Expression_Min : public UTG_Expression_Variant`  
_L79-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L86 _public member_ `FTG_Variant Input1;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "A"))` — The first input for Output = min(Input1, Input2)
- L90 _public member_ `FTG_Variant Input2;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "B"))` — The second input for Output = min(Input1, Input2)
- L92 _public function_ `virtual FText GetTooltipText() const override`
- L93 _public function_ `virtual FName GetCategory() const override`
- L96 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L97 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L98 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Max`  
`class UTG_Expression_Max : public UTG_Expression_Variant`  
_L105-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L112 _public member_ `FTG_Variant Input1;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "A"))` — The first input for Output = max(Input1, Input2)
- L116 _public member_ `FTG_Variant Input2;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "B"))` — The second input for Output = max(Input1, Input2)
- L118 _public function_ `virtual FText GetTooltipText() const override`
- L119 _public function_ `virtual FName GetCategory() const override`
- L122 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L123 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L124 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_IfThenElse.h` (Public)


#### class `UTG_Expression_IfThenElse`  
`class UTG_Expression_IfThenElse : public UTG_Expression_Variant`  
_L19-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L26 _public member_ `FTG_Variant LHS;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "A"))` — The LHS value for the comparison (LHS <operator> RHS)
- L30 _public member_ `TEnumAsByte<EIfThenElseOperator> Operator = EIfThenElseOperator::GT;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The type of operator in LHS <operator> RHS
- L34 _public member_ `FTG_Variant RHS;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "B"))` — The RHS value for the comparison (LHS <operator> RHS)
- L38 _public member_ `FTG_Variant Then;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The value to return if the comparison is successful if (<true>) <Then> else <Else>
- L42 _public member_ `FTG_Variant Else;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The value to return if the comparison is unsuccessful if (<false>) <Then> else <Else>
- L46 _public member_ `TEnumAsByte<EIfThenElseType> ComparisonType = EIfThenElseType::IndividualComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The type of comparison to use. Individual = IndividualComponent of the components are individually passed through the comparison. AllComponents = All components must succeed check to trigger the Then part of the statement. Magnitude = Grayscale value of the color is used in comparison
- L48 _public function_ `virtual FText GetTooltipText() const override`
- L49 _public function_ `virtual FName GetCategory() const override`
- L52 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L53 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L54 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const Value, size_t Count);`
- L55 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_Invert.h` (Public)


#### class `UTG_Expression_Invert`  
`class UTG_Expression_Invert : public UTG_Expression`  
_L19-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L24 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Maths);`
- L25 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L30 _public member_ `float MaxValue = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1", PinDisplayName = "Max"))` — The max value to use. This is used as MaxValue - Input for every pixel in every channel to calculate the output NB: Hiding this property for the time being as requested
- L34 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input texture to be inverted
- L38 _public member_ `bool IncludeAlpha = false;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", PinNotConnectable = true))` — Whether to invert the Alpha channel as well?
- L42 _public member_ `bool Clamp = false;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", PinNotConnectable = true))` — Saturate/clamp values in the [0, 1] range or not
- L46 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The inverted output. This is calculated as MaxValue - Input for every pixel in every channel
- L48 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_Maths_OneInput.h` (Public)


#### class `UTG_Expression_Trigonometry`  
`class UTG_Expression_Trigonometry : public UTG_Expression_Variant`  
_L18-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L23 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L24 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L25 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L30 _public member_ `FTG_Variant Angle;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The angle in radians to run the trigonometric function on
- L34 _public member_ `ETrigFunction Function = ETrigFunction::Sin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", RegenPinsOnChange))` — What trigonometric function to apply at the angle
- L36 _public function_ `virtual FText GetTooltipText() const override`
- L37 _public function_ `virtual FName GetCategory() const override`

#### class `UTG_Expression_OneInput`  
`class UTG_Expression_OneInput : public UTG_Expression_Variant`  
_L44-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTG_Expression_Variant`
- L49 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L54 _public member_ `FTG_Variant Input;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The input to the node
- L56 _public function_ `virtual FName GetCategory() const override`

#### class `UTG_Expression_Abs`  
`class UTG_Expression_Abs : public UTG_Expression_OneInput`  
_L63-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L68 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L69 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L72 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Sqrt`  
`class UTG_Expression_Sqrt : public UTG_Expression_OneInput`  
_L79-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L84 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L85 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L88 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Square`  
`class UTG_Expression_Square : public UTG_Expression_OneInput`  
_L95-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L100 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L101 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L104 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Cube`  
`class UTG_Expression_Cube : public UTG_Expression_OneInput`  
_L111-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L116 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L117 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L120 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Cbrt`  
`class UTG_Expression_Cbrt : public UTG_Expression_OneInput`  
_L127-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L132 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L133 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L136 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Exp`  
`class UTG_Expression_Exp : public UTG_Expression_OneInput`  
_L143-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L148 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L149 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L152 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Log2`  
`class UTG_Expression_Log2 : public UTG_Expression_OneInput`  
_L159-169_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L164 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L165 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L168 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Log10`  
`class UTG_Expression_Log10 : public UTG_Expression_OneInput`  
_L175-185_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L180 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L181 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L184 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Log`  
`class UTG_Expression_Log : public UTG_Expression_OneInput`  
_L191-201_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L196 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L197 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L200 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Floor`  
`class UTG_Expression_Floor : public UTG_Expression_OneInput`  
_L207-217_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L212 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L213 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L216 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Ceil`  
`class UTG_Expression_Ceil : public UTG_Expression_OneInput`  
_L223-233_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L228 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L229 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L232 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Round`  
`class UTG_Expression_Round : public UTG_Expression_OneInput`  
_L239-249_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_OneInput`
- L244 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L245 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L248 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_Maths_ThreeInputs.h` (Public)


#### class `UTG_Expression_MAD`  
`class UTG_Expression_MAD : public UTG_Expression_Variant`  
_L17-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L24 _public member_ `FTG_Variant Input1 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "A"))` — First input to the MAD operation [Input1 * Input2 + Input3]
- L28 _public member_ `FTG_Variant Input2 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "B"))` — Second input to the MAD operation [Input1 * Input2 + Input3]
- L32 _public member_ `FTG_Variant Input3 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "C"))` — Third input to the MAD operation [Input1 * Input2 + Input3]
- L35 _public function_ `virtual FName GetCategory() const override`
- L36 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L37 _public function_ `virtual FText GetTooltipText() const override`
- L40 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L41 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L42 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`

#### class `UTG_Expression_Lerp`  
`class UTG_Expression_Lerp : public UTG_Expression_Variant`  
_L49-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L56 _public member_ `FTG_Variant Input1 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "X"))` — First input to lerp
- L60 _public member_ `FTG_Variant Input2 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Y"))` — Second input to lerp
- L64 _public member_ `FTG_Variant LerpValue = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "S"))` — A value that linearly interpolates between X and Y. This can be an image or a Scalar node connected for easier control
- L67 _public function_ `virtual FText GetTooltipText() const override`
- L68 _public function_ `virtual FName GetCategory() const override`
- L71 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L72 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L73 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Maths/TG_Expression_Maths_TwoInputs.h` (Public)


#### class `UTG_Expression_BasicMath_Op`  
`class UTG_Expression_BasicMath_Op : public UTG_Expression_Variant`  
_L17-34_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTG_Expression_Variant`
- L24 _public member_ `FTG_Variant Input1 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "A"))` — First input to the math operation [Input1 <operation> Input2]
- L28 _public member_ `FTG_Variant Input2 = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "B"))` — Second input to the math operation [Input1 <operation> Input2]
- L30 _public function_ `virtual FName GetCategory() const override`
- L33 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`

#### class `UTG_Expression_Multiply`  
`class UTG_Expression_Multiply : public UTG_Expression_BasicMath_Op`  
_L40-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L45 _public function_ `virtual FText GetTooltipText() const override`
- L48 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L49 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Divide`  
`class UTG_Expression_Divide : public UTG_Expression_BasicMath_Op`  
_L56-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L61 _public function_ `virtual FText GetTooltipText() const override`
- L64 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L65 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Add`  
`class UTG_Expression_Add : public UTG_Expression_BasicMath_Op`  
_L72-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L77 _public function_ `virtual FText GetTooltipText() const override`
- L80 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L81 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Subtract`  
`class UTG_Expression_Subtract : public UTG_Expression_BasicMath_Op`  
_L88-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L93 _public function_ `virtual FText GetTooltipText() const override`
- L96 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L97 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Dot`  
`class UTG_Expression_Dot : public UTG_Expression_BasicMath_Op`  
_L104-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L109 _public function_ `virtual FText GetTooltipText() const override`
- L112 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L113 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const Value, size_t Count) override;`
- L114 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`
- L116 _protected prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L118 _protected prototype_ `virtual FTG_Variant::EType EvalExpressionCommonOutputVariantType() const override;` — specify the logic to decide the output variant type

#### class `UTG_Expression_Cross`  
`class UTG_Expression_Cross : public UTG_Expression_BasicMath_Op`  
_L125-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L130 _public function_ `virtual FText GetTooltipText() const override`
- L133 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L134 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const Value, size_t Count) override;`
- L135 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Step`  
`class UTG_Expression_Step : public UTG_Expression_BasicMath_Op`  
_L142-152_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_BasicMath_Op`
- L147 _public function_ `virtual FText GetTooltipText() const override`
- L150 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L151 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### class `UTG_Expression_Pow`  
`class UTG_Expression_Pow : public UTG_Expression_Variant`  
_L158-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression_Variant`
- L164 _private member_ `FTG_Variant Base = 0;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The base of the power function
- L168 _private member_ `FTG_Variant Exponent = 1;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The exponent
- L171 _public function_ `virtual FText GetTooltipText() const override`
- L172 _public function_ `virtual FName GetCategory() const override`
- L175 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs() override`
- L176 _protected prototype_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count) override;`
- L177 _protected prototype_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Output/TG_Expression_Output.h` (Public)


#### class `UTG_Expression_Output`  
`class UTG_Expression_Output : public UTG_Expression`  
_L16-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L21 _public prototype_ `TG_DECLARE_VARIANT_EXPRESSION(TG_Category::Output);`
- L22 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L24 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;`
- L28 _public member_ `FTG_Variant Source = 0;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The final generated output
- L32 _public member_ `FTG_Variant Output = 0;` — `UPROPERTY(meta = (TGType = "TG_OutputParam", PinDisplayName = ""))` — The final generated output value
- L36 _public member_ `FTG_OutputSettings OutputSettings;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", CollapsableChildProperties,ShowOnlyInnerProperties, FullyExpand, NoResetToDefault, PinDisplayName = "Settings"))` — When we will work on Node UI for FOutputSettings we will set the category as TG_Setting
- L39 _public member_ `bool bShouldExport = true;` — `UE_DEPRECATED(5.6, "Use OutputSettings.bShouldExport instead")`
- L41 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L42 _public prototype_ `virtual void SetTitleName(FName NewName) override;`
- L43 _public prototype_ `virtual FName GetTitleName() const override;`
- L44 _public function_ `virtual FText GetTooltipText() const override`
- L45 _public function_ `virtual bool ShouldShowSettings() const`
- L47 _public prototype_ `void UpdateBufferDescriptorValues();`
- L48 _public prototype_ `void InitializeOutputSettings();`
- L50 _public prototype_ `void SetShouldExport(bool InShouldExport);`
- L52 _public function_ `bool GetShouldExport() const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Procedural/TG_Expression_Gradient.h` (Public)


#### class `UTG_Expression_Gradient`  
`class UTG_Expression_Gradient : public UTG_Expression`  
_L17-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L22 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Procedural) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L28 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;` — Used to implement EditCondition logic for both Node UI and Details View
- L34 _public member_ `EGradientType Type = EGradientType::GT_Linear_1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", RegenPinsOnChange))` — The type of the gradient function
- L38 _public member_ `EGradientInterpolation Interpolation = EGradientInterpolation::GTI_Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", EditConditionHides))` — Type of interpolation to use
- L42 _public member_ `EGradientRotation Rotation = EGradientRotation::GTR_0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", EditConditionHides))` — Rotation of the gradient
- L46 _public member_ `EGradientRotationLimited RotationLimited = EGradientRotationLimited::GTRL_0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Rotation", EditConditionHides, PinDisplayName = "Rotation"))` — Rotation of the gradient
- L50 _public member_ `FVector2f Center = { 0.5f, 0.5f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Input", EditConditionHides, UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The center of the radial gradient
- L54 _public member_ `float Radius = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Input", EditConditionHides, UIMin = "0.001", ClampMin = "0.001", UIMax = "1", ClampMax = "1"))` — The center of the radial gradient
- L58 _public member_ `FVector2f Point1 = { 0.25f, 0.25f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Input", EditConditionHides, UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — First point of the line for axial gradients
- L62 _public member_ `FVector2f Point2 = { 0.75f, 0.75f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Input", EditConditionHides, UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — Second point of the line for axial gradients
- L66 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The generated gradient texture
- L68 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Procedural/TG_Expression_Noise.h` (Public)


#### enum `ENoiseType`  
`enum ENoiseType : int`  
_L16-23_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `NOISETYPE_Simplex = 0 UMETA(DisplayName = "Simplex")`
- L19 _public enumerator_ `NOISETYPE_Perlin UMETA(DisplayName = "Perlin")`
- L20 _public enumerator_ `NOISETYPE_Worley1 UMETA(DisplayName = "Worley1")`
- L21 _public enumerator_ `NOISETYPE_Worley2 UMETA(DisplayName = "Worley2")`
- L22 _public enumerator_ `NOISETYPE_Worley3 UMETA(DisplayName = "Worley3")`

#### class `UTG_Expression_Noise`  
`class UTG_Expression_Noise : public UTG_Expression`  
_L26-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L30 _private member_ `static constexpr int DefaultSize = 1024;`
- L32 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Procedural) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L38 _public member_ `TEnumAsByte<ENoiseType> NoiseType = NOISETYPE_Simplex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The type of the noise function
- L42 _public member_ `int32 Seed = 75;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-100", ClampMin = "-100", UIMax = "100", ClampMax = "100"))` — A value used to initialize or "seed" a random number generator when generating procedural noise. Changing the noise seed produces different patterns or variations in the generated noise.
- L46 _public member_ `float Amplitude = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "10", ClampMax = "10"))` — The magnitude or strength of the variations introduced by procedural noise. Adjusting this parameter can control the intensity or impact of procedural noise on textures or effects.
- L50 _public member_ `float Frequency = 5;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "20", ClampMax = "20"))` — Determines how quickly or slowly the patterns change within the generated noise
- L54 _public member_ `int32 Octaves = 1;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "10", ClampMax = "10"))` — The number of levels of details that you want from the noise signal
- L58 _public member_ `float Lacunarity = 2;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "1.5", ClampMin = "1.5", UIMax = "3.5", ClampMax = "3.5"))` — Number that determines how much detail is added to or removed from the noise signal (adjusts frequency)
- L62 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting"))` — Number that determines how much each octave contributes to the overall shape of the noise signal (adjusts amplitude)
- L66 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The generated noise texture
- L68 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Procedural/TG_Expression_Pattern.h` (Public)


#### enum `EPatternType`  
`enum EPatternType : int`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Square = 0 UMETA(DisplayName = "Square")`
- L20 _public enumerator_ `Circle UMETA(DisplayName = "Circle")`
- L21 _public enumerator_ `Checker UMETA(DisplayName = "Checker")`
- L22 _public enumerator_ `Gradient UMETA(DisplayName = "Gradient")`

#### struct `FPatternMaskPlacement_TS`  
`struct FPatternMaskPlacement_TS`  
_L26-70_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public member_ `int32 RepeatX = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "1", ClampMin = "1", UIMax = "24", ClampMax = "24"))` — The number of repetitions along the X-axis
- L36 _public member_ `int32 RepeatY = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "1", ClampMin = "1", UIMax = "24", ClampMax = "24"))` — The number of repetitions along the Y-axis
- L40 _public member_ `float SpacingX = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The spacing between each pattern along X-axis
- L44 _public member_ `float SpacingY = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — The spacing between each pattern along Y-axis
- L48 _public member_ `float Offset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1", ClampMax = "1"))` — The offset offset of the pattern
- L52 _public member_ `bool OffsetHorizontal = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — Whether it's a horizontal or a vertical offset
- L54 _public function_ `Vector2 Repeat() const`
- L55 _public function_ `Vector2 Spacing() const`
- L56 _public function_ `Vector2 OffsetValue() const`
- L58 _public function_ `void InitFromString(const FString& StrVal)`
- L64 _public function_ `FString ToString() const`

#### struct `FPatternMaskJitter_TS`  
`struct FPatternMaskJitter_TS`  
_L73-144_
- reflection: `USTRUCT(BlueprintType)`
- L79 _public member_ `float BrightnessAmount = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — Jitter brightness amount
- L83 _public member_ `float BrightnessThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — Jitter brightness threshold
- L87 _public member_ `int32 BrightnessSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "100", ClampMax = "100" ))` — Seed to control the brightness randomness. 0 means no randomness
- L91 _public member_ `float SizeAmount = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — Size of the jitter
- L95 _public member_ `float SizeThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — Size threshold
- L99 _public member_ `int32 SizeSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "100", ClampMax = "100" ))` — Seed to control the size randomness. 0 means no randomness
- L103 _public member_ `float TiltXAmount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1.0", ClampMax = "1.0" ))` — Amount of tilt along the X-axis
- L107 _public member_ `float TiltYAmount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1.0", ClampMax = "1.0" ))` — Amount of tilt along the Y-axis
- L111 _public member_ `float TiltThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — Tilt threshold
- L115 _public member_ `int32 TiltSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "100", ClampMax = "100" ))` — Seed to control the tilt randomness. 0 means no randomness
- L119 _public member_ `float AngleXAmount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1.0", ClampMax = "1.0" ))` — Amount of angle along the X-axis
- L123 _public member_ `float AngleYAmount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1.0", ClampMax = "1.0" ))` — Amount of angle along the Y-axis
- L127 _public member_ `int32 AngleSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "100", ClampMax = "100" ))` — Seed to control the angle randomness. 0 means no randomness
- L129 _public function_ `Vector2 Angle() const`
- L130 _public function_ `Vector2 Tilt() const`
- L132 _public function_ `void InitFromString(const FString& StrVal)`
- L138 _public function_ `FString ToString() const`

#### struct `FPatternMaskBevel_TS`  
`struct FPatternMaskBevel_TS`  
_L147-171_
- reflection: `USTRUCT(BlueprintType)`
- L153 _public member_ `float Bevel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — The bevel value
- L157 _public member_ `float BevelCurve = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1.0", ClampMax = "1.0" ))` — The bevel curve
- L159 _public function_ `void InitFromString(const FString& StrVal)`
- L165 _public function_ `FString ToString() const`

#### struct `FPatternMaskCutout_TS`  
`struct FPatternMaskCutout_TS`  
_L174-198_
- reflection: `USTRUCT(BlueprintType)`
- L180 _public member_ `float CutoffThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1.0", ClampMax = "1.0" ))` — The cutoff value
- L184 _public member_ `float CutoffSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "100", ClampMax = "100" ))` — The seed to control the cutoff randomness. 0 means no randomness
- L186 _public function_ `void InitFromString(const FString& StrVal)`
- L192 _public function_ `FString ToString() const`

#### struct `FGradientDir_TS`  
`struct FGradientDir_TS`  
_L201-227_
- reflection: `USTRUCT(BlueprintType)`
- L207 _public member_ `float X = 90;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "90", ClampMax = "90" ))` — Gradient value along X-axis in degrees [0, 90]
- L211 _public member_ `float Y = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-180", ClampMin = "-180", UIMax = "180", ClampMax = "180" ))` — Gradient value along Y-axis in degrees [-180, 180]
- L213 _public function_ `Vector2 Value() const`
- L215 _public function_ `void InitFromString(const FString& StrVal)`
- L221 _public function_ `FString ToString() const`

#### class `UTG_Expression_Pattern`  
`class UTG_Expression_Pattern : public UTG_Expression`  
_L230-269_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L234 _private member_ `static constexpr int DefaultSize = 1024;`
- L236 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Procedural) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L242 _public member_ `TEnumAsByte<EPatternType> PatternType = EPatternType::Square;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting"))` — The type of pattern
- L246 _public member_ `FPatternMaskPlacement_TS Placement;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, Meta = (TGType = "TG_Setting", HideNodeUI))` — Placement
- L250 _public member_ `FPatternMaskJitter_TS Jitter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, Meta = (TGType = "TG_Setting", HideNodeUI))` — Jitter
- L254 _public member_ `FPatternMaskBevel_TS Bevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, Meta = (TGType = "TG_Setting", HideNodeUI))` — Bevel
- L258 _public member_ `FPatternMaskCutout_TS Cutout;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, Meta = (TGType = "TG_Setting", HideNodeUI))` — Cut out
- L262 _public member_ `FGradientDir_TS GradientDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, Meta = (TGType = "TG_Setting", HideNodeUI))` — Gradient direction
- L266 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output generated by the pattern
- L268 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Procedural/TG_Expression_Shape.h` (Public)


#### enum `EShapeType`  
`enum class EShapeType : uint8`  
_L16-26_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Circle = 0 UMETA(DisplayName = "Circle")`
- L19 _public enumerator_ `Segment UMETA(DisplayName = "Segment")`
- L20 _public enumerator_ `Rectangle UMETA(DisplayName = "Rectangle")`
- L21 _public enumerator_ `Triangle UMETA(DisplayName = "Triangle")`
- L22 _public enumerator_ `Ellipse UMETA(DisplayName = "Ellipse")`
- L23 _public enumerator_ `Pentagon = 5 UMETA(DisplayName = "Pentagon")`
- L24 _public enumerator_ `Hexagon UMETA(DisplayName = "Hexagon")`
- L25 _public enumerator_ `Polygon UMETA(DisplayName = "Polygon")`

#### class `UTG_Expression_Shape`  
`class UTG_Expression_Shape : public UTG_Expression`  
_L29-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L33 _private member_ `static constexpr int DefaultSize = 1024;`
- L35 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Procedural) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L41 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;` — Used to implement EditCondition logic for both Node UI and Details View
- L46 _public member_ `EShapeType ShapeType = EShapeType::Circle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", RegenPinsOnChange))` — Select the geometric primitive shape to generate
- L50 _public member_ `int32 PolygonNumSides = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 7, ClampMax = 32, EditConditionHides))` — The number of sides of the Polygon (only relevant when using the <Polygon> type)
- L54 _public member_ `float Width = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax =1))` — Width representing the relative size of the shape in the generated texture. For Circle/Triangle/Pentagon hexagon and Polygon it is the radius of the shape relative to the uv domain of the generated texture
- L58 _public member_ `float Height = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 1, EditConditionHides))` — Height representing the relative size of the shape in the generate texture. Height is used in Rectangle and ellipse.
- L62 _public member_ `float Orientation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-180", ClampMin = "-180", UIMax = "180", ClampMax = "180", Delta = "1", Units = "Degrees", EditConditionHides))` — Orientation is the 2D rotation of the shape around the center
- L66 _public member_ `float Rounding = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 1, EditConditionHides))` — Rounding is about the 2D footprint of the shape generated, 0 means the perfect shape, 1 means the most rounded version of the shape
- L70 _public member_ `float BevelWidth = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 1))` — Bevel width is the distance from the outline of the shape on which the bevelling function is applied to the generated mask
- L74 _public member_ `float BevelCurve = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = -1, ClampMax = 1))` — Bevel curve is controlling the shape of bevelling varying from concave to linear to convex
- L78 _public member_ `float ShowSDF = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoCategory, meta = (TGType = "TG_Setting", ClampMin = 0, ClampMax = 1))` — Signed distance function the mathematical function defining the distance to the edge of the shape
- L82 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output generated by the pattern
- L84 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Procedural/TG_Expression_Transform.h` (Public)


#### class `UTG_Expression_Transform`  
`class UTG_Expression_Transform : public UTG_Expression`  
_L19-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L24 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Procedural);`
- L25 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L29 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output"))` — Output image
- L33 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input"))` — The Input image to transform
- L37 _public member_ `bool WrapMode = true;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Wrap Mapping"))` — Filter mode is wrap or clamped
- L41 _public member_ `bool MirrorX = false;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Mirror X"))` — Filter mode is wrap or clamped
- L45 _public member_ `bool MirrorY = false;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Mirror Y"))` — Filter mode is wrap or clamped
- L49 _public member_ `FVector2f Coverage = { 1, 1 };` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))` — The coverage of the transform in range [0, 1]. Defaults to 1,1
- L53 _public member_ `FVector2f Offset = { 0, 0 };` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1.0", ClampMin = "-1.0", UIMax = "1.0", ClampMax = "1.0"))` — The translation offset along xy in range [0, 1]. Defaults to 0
- L57 _public member_ `FVector2f Pivot = { 0.5, 0.5 };` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0", Multiple = "0.01"))` — The pivot XY coord in range [0, 1]. Defaults to 0.5
- L61 _public member_ `float Rotation = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-180", ClampMin = "-180", UIMax = "180", ClampMax = "180", Delta = "1", Units="Degrees"))` — The XY rotation expressed in degrees
- L68 _public member_ `float Zoom = 100.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "100", ClampMax = "100000", Multiple = "1", Delta = "1", Units="Percent"))` — Uniform scaling of the image within the tiled cell. Value is a percentage, default value is 100% meaning the image fully fill the cell: Zoom out with value in the range [0,100] Zoom in with value above 100%
- L72 _public member_ `float StretchToFit = 1.0f;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Stretch to fit", UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0", Multiple = "0.01"))` — Keep the AspectRatio of the source image (0) or stretch to fit the cell rectangle (1)
- L76 _public member_ `FVector2f Repeat = { 1, 1 };` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "1.0", ClampMin = "0.01", UIMax = "32", ClampMax = "32", Delta = "1"))` — The repetitions along rotated X & Y axes. Defaults to 1
- L80 _public member_ `FLinearColor FillColor = { 0, 0, 0, 0 };` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting"))` — Filling color for non texture source
- L84 _public member_ `bool StaggerHorizontally = true;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", DisplayName = "Stagger Horizontally"))` — Staggering is horizontal ? or false for vertical
- L88 _public member_ `float StaggerOffset = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "-1", ClampMin = "-1", UIMax = "1", ClampMax = "1", Multiple = "0.005"))` — The staggering offset from one row to the next
- L92 _public member_ `FVector2f Stride = { 0, 0 };` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "31", ClampMax = "31", Delta = "1"))` — The skipping offset from one tile to the next
- L96 _public member_ `float ShowDebugGrid = 0;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", UIMin = "0", ClampMin = "0", UIMax = "1", ClampMax = "1"))` — [DEBUG ONLY OPTION] Output blended with the debugging grid showing the transformation applied. This option WILL NOT get applied while exporting!
- L98 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/TG_Expression.h` (Public)


#### class `TG_Category`  
`class TG_Category`  
_L19-34_
- L22 _public member_ `static const FName Default;`
- L23 _public member_ `static const FName Output;`
- L24 _public member_ `static const FName Input;`
- L25 _public member_ `static const FName Adjustment;`
- L26 _public member_ `static const FName Channel;`
- L27 _public member_ `static const FName DevOnly;`
- L28 _public member_ `static const FName Procedural;`
- L29 _public member_ `static const FName Maths;`
- L30 _public member_ `static const FName Utilities;`
- L31 _public member_ `static const FName Filter;`
- L32 _public member_ `static const FName Arrays;`
- L33 _public member_ `static const FName Custom;`

#### class `UTG_Expression`  
`class UTG_Expression : public UObject`  
_L37-180_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UObject`
- L44 _protected member_ `int32 InstanceExpressionClassVersion = 0;` — `UPROPERTY()` — UTG_Expression classes have a per instance expression class version number recovered from serialization
- L48 _protected function_ `virtual int32 GetExpressionClassVersion() const` — Method returning this Expression class version that can be overwritten in a sub class requiring to support version change
- L49 _protected function_ `virtual bool ShouldShowSettings() const`
- L54 _public member_ `FTG_TextureDescriptor BaseOutputSettings;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Setting", CollapsableChildProperties, ShowOnlyInnerProperties, FullyExpand, NoResetToDefault, PinDisplayName = "Settings", EditConditionHides))` — When we will work on Node UI for FOutputSettings we will set the category as TG_Setting
- L57 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Override serialization to save Class Serialization version
- L60 _public prototype_ `virtual FTG_Name GetDefaultName() const;`
- L61 _public function_ `virtual FName GetCategory() const`
- L62 _public function_ `virtual FTG_SignaturePtr GetSignature() const`
- L63 _public function_ `virtual FText GetTooltipText() const`
- L65 _public function_ `virtual void SetTitleName(FName NewName)`
- L66 _public function_ `virtual FName GetTitleName() const`
- L67 _public prototype_ `virtual bool CanRenameTitle() const;`
- L69 _public function_ `virtual bool CanHandleAsset(UObject* Asset)`
- L70 _public function_ `virtual void SetAsset(UObject* Asset)`
- L73 _public function_ `virtual void Evaluate(FTG_EvaluationContext* InContext)` — This is THE evaluation call to overwrite
- L76 _public prototype_ `void PropertyChangeTriggered(FProperty* Property, EPropertyChangeType::Type ChangeType);`
- L77 _public prototype_ `virtual bool CanEditChange( const FProperty* InProperty ) const override;`
- L81 _public function_ `virtual bool Validate(MixUpdateCyclePtr Cycle)` — Validate internal checks, warnings and errors
- L84 _public prototype_ `void ValidateGenerateConformer(UTG_Pin* InPin);` — Validate that the expression conforms to a conformant function (e.g. Clamp etc.)
- L87 _public prototype_ `virtual UTG_Node* GetParentNode() const final;` — Expression notifies its parent node on key events
- L96 _protected function_ `virtual void Initialize()` — Initialize the expression in cascade from the node allowing it to re create transient data This is called in the PostLoad of the Graph
- L102 _protected prototype_ `virtual void SetupAndEvaluate(FTG_EvaluationContext* InContext);` — Called first from the Graph::Evaluate/Traverse which then call the Evaluate function. This is where the Var values are copied over to the matching Expression's properties This is NOT the function you want to derive, unless you know exactly what you are doing. Instead overwrite the Execute function.
- L104 _protected prototype_ `virtual void CopyVarToExpressionArgument(const FTG_Argument& Arg, FTG_Var* InVar);`
- L105 _protected prototype_ `virtual void CopyVarFromExpressionArgument(const FTG_Argument& Arg, FTG_Var* InVar);`
- L106 _protected function_ `virtual void CopyVarGeneric(const FTG_Argument& Arg, FTG_Var* InVar, bool CopyVarToArg)`
- L110 _protected prototype_ `virtual void LogEvaluation(FTG_EvaluationContext* InContext);` — Log the actual values for vars and the expression evaluation Called from SetupAndEvaluate call if Context ask for it
- L112 _protected prototype_ `virtual FTG_Signature::FInit GetSignatureInitArgsFromClass() const final;`
- L116 _protected prototype_ `virtual FTG_SignaturePtr BuildSignatureFromClass() const final;` — Build the signature of the expression by collecting the FTG_ExpressionXXX UProperties of the class
- L119 _protected function_ `virtual FTG_SignaturePtr BuildSignatureDynamically() const` — Build Signature in derived classes dynamically
- L126 _public prototype_ `virtual void NotifyExpressionChanged(const FPropertyChangedEvent& PropertyChangedEvent) const final;` — If some state has changed in the expression that affects its representation triggered when a property has changed and needs to be copied over to its corresponding Var NB: required to be public for calling from TG_Variant customization
- L131 _protected prototype_ `virtual void NotifySignatureChanged() const;` — If the signature changes and the node need to regenerate its own signature. Only concrete implementation for Dynamic Expression
- L136 _protected function_ `virtual bool ResetCommonInputVariantType(FTG_Variant::EType InType = FTG_Variant::EType::Invalid) const` — Variant expression API: specialized when using the macro TG_DECLARE_VARIANT_EXPRESSION: When input connection are changing, the graph / node calls ResetCommonInputVariantType in order for the expression to reeval its CommonInputVariant type as well as it s signature if it changes
- L137 _protected function_ `virtual void NotifyCommonInputVariantTypeChanged(FTG_Variant::EType NewType = FTG_Variant::EType::Invalid) const final`
- L141 _protected function_ `virtual FTG_Variant::EType GetCommonInputVariantType() const`
- L150 _protected prototype_ `virtual FTG_Variant::EType EvalExpressionCommonInputVariantType() const;` — Variant expression API: Eval the common input variant type used by the expression (only if it is variant) by looking at the various input pins connected or default types and come up with a "common input" type used for how to interpret all the input variants Default implementation: The common variant type is found as the type that superseeds all the variant input arguments currently fed from other nodes This call can be modified in a specific class to get a different behavior.
- L156 _protected prototype_ `virtual FTG_Variant::EType EvalExpressionCommonOutputVariantType() const;` — Variant expression API: Similarly, this call eval the common output variant type used by the expression (only if it is variant) Default implementation: the common output variant is the same as the common input variant. this call can be modified in a specific class to get a differnet behavior, see Expression_Dot for an example.
- L158 _protected function_ `virtual bool IgnoreInputTextureOnUndo() const`
- L162 _protected function_ `template<typename T> bool FeedbackPinValue(const FName& InPinName, const T& InValue)` — In some cases, evaluation or change in the Expression needs to be feedback to the matching pin's value This is not needed for the standard flow of evaluation but is sometime required for coupled member.
- L177 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L178 _protected prototype_ `virtual void PostEditUndo() override;`

#### class `UTG_Expression_Null`  
`class UTG_Expression_Null : public UTG_Expression`  
_L229-235_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UTG_Expression`
- L234 _protected prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Default);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTSExpressionChanged, UTG_Expression*);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTSExpressionChanged, UTG_Expression*);`
- L184 _macro_ `#define TG_DECLARE_EXPRESSION(Category) \`
- L188 _macro_ `#define TG_DECLARE_DYNAMIC_EXPRESSION(Category) \`
- L195 _macro_ `#define TG_DECLARE_VARIANT_EXPRESSION(Category) \`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/TG_Expression_MaterialBase.h` (Public)


#### enum `EDrawMaterialAttributeTarget`  
`enum class EDrawMaterialAttributeTarget : uint8`  
_L19-34_
- reflection: `UENUM(BlueprintType)`
- desc: Describe the possible attributes extracted from a MAterial during a DrawMaterial call this is used as high level data.
- L21 _public enumerator_ `BaseColor = 0`
- L22 _public enumerator_ `Metallic`
- L23 _public enumerator_ `Specular`
- L24 _public enumerator_ `Roughness`
- L25 _public enumerator_ `Anisotropy`
- L26 _public enumerator_ `Emissive`
- L27 _public enumerator_ `Opacity`
- L28 _public enumerator_ `OpacityMask`
- L29 _public enumerator_ `Normal`
- L30 _public enumerator_ `Tangent`
- L33 _public enumerator_ `Count UMETA(Hidden)` — Always has to be the last

#### class `UTG_Expression_MaterialBase`  
`class UTG_Expression_MaterialBase : public UTG_Expression`  
_L39-122_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UTG_Expression`
- L44 _public prototype_ `TG_DECLARE_DYNAMIC_EXPRESSION(TG_Category::Default)`
- L56 _public member_ `FTG_Texture Output;` — `UPROPERTY(meta = (TGType = "TG_Output"))` — The output of the material expressed as a texture
- L58 _public member_ `mutable TArray<FTG_Texture> Outputs;`
- L60 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L63 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle) override;` — Validate internal checks, warnings and errors
- L66 _public function_ `const TArray<EDrawMaterialAttributeTarget>& GetAvailableMaterialAttributeIds() const` — Access the list of attributes available for rendering from the current Material
- L67 _public function_ `const TArray<FName>& GetAvailableMaterialAttributeNames() const`
- L69 _public prototype_ `static FName CPPTypeNameFromMaterialParamType(EMaterialParameterType InMatType);`
- L72 _public function_ `virtual int32 GetNumVirtualTextureWarmupFrames() const` — 0 will fallback to CVar <TG.VirtualTexture.NumWarmupFrames> value.
- L78 _protected member_ `FMaterialInstanceStaticSwitchPermutationMap MaterialPermutations;` — `UPROPERTY(Transient)` — A local Material Instance Constant is recreated from the reference material assigned through SetMaterialInternal All static switches permutations are cached in this map and only created on demand
- L81 _protected member_ `` — The set of material properties available for rendering
- L82 _protected member_ `TArray<FName> AvailableMaterialAttributeNames;` — same with the attribute names
- L83 _protected member_ `mutable TArray<FName> MatAttributesOutputArgNames;` — Their argument names (because they may have to be different from the true attribute material name)
- L97 _protected member_ `mutable TArray<FArgToMaterialParamInfo> ArgToMatParams;` — mutable because it is populated in the BuildSignatureDynamically()
- L101 _protected prototype_ `virtual void Initialize() override;`
- L103 _protected prototype_ `void GenerateMaterialAttributeOptions();` — Based on the current Material, list of material attributes available
- L106 _protected prototype_ `UMaterialInstanceConstant* GetEvaluationMaterialInstanceConstant(FTG_EvaluationContext* InContext);` — During evaluation, pick the MIC from the input static switch(es) combination
- L108 _protected prototype_ `TiledBlobPtr CreateRenderMaterialJob(FTG_EvaluationContext* InContext, const FString& InName, const FString& InMaterialPath, const BufferDescriptor& InDescriptor, EDrawMaterialAttributeTarget InDrawMaterialAttributeTarget);`
- L109 _protected prototype_ `TiledBlobPtr CreateRenderMaterialJob(FTG_EvaluationContext* InContext, const RenderMaterial_BPPtr& InRenderMaterial, const BufferDescriptor& InDescriptor, EDrawMaterialAttributeTarget InDrawMaterialAttributeTarget);`
- L110 _protected prototype_ `void LinkMaterialParameters(FTG_EvaluationContext* InContext, JobUPtr& InMaterialJob, const UMaterialInterface* InMaterial, BufferDescriptor InDescriptor);`
- L112 _protected prototype_ `virtual void CopyVarGeneric(const FTG_Argument& Arg, FTG_Var* InVar, bool CopyVarToArg);`
- L113 _protected prototype_ `virtual void SetMaterialInternal(UMaterialInterface* InMaterial);`
- L115 _protected function_ `virtual EDrawMaterialAttributeTarget GetRenderedAttributeId()`
- L116 _protected function_ `virtual TObjectPtr<UMaterialInterface> GetMaterial() const`
- L119 _private prototype_ `void AddSignatureParam(const TArray<FMaterialParameterInfo>& OutParameterInfo, const TArray<FGuid>& OutParameterIds, EMaterialParameterType MatType, FTG_Signature::FInit& SignatureInit) const;`
- L121 _private prototype_ `static EDrawMaterialAttributeTarget ConvertEMaterialPropertyToEDrawMaterialAttributeTarget(EMaterialProperty InMaterialProperty);`

#### struct `UTG_Expression_MaterialBase::FArgToMaterialParamInfo`  
`struct FArgToMaterialParamInfo`  
_L86-96_
- desc: Arg to Material Param Info array records the map of arg name to the corresponding Material Param
- L88 _public member_ `FName ArgName;`
- L89 _public member_ `FName MatParamName;`
- L90 _public member_ `FGuid MatParamGuid;`
- L91 _public member_ `EMaterialParameterType MatType = EMaterialParameterType::None;`
- L93 _public member_ `FMaterialParameterValue Value;`
- L95 _public function_ `bool operator== (const FName& InArgName) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L13 _typedef_ `typedef std::shared_ptr<RenderMaterial_BP> RenderMaterial_BPPtr;`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/TG_Expression_Variant.h` (Public)


#### class `UTG_Expression_Variant`  
`class UTG_Expression_Variant : public UTG_Expression`  
_L22-61_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTG_Expression`
- L29 _protected function_ `virtual float EvaluateScalar_WithValue(FTG_EvaluationContext* InContext, const float* const Value, size_t Count)` — Most of the time these are the two functions that expressions will need to implement. These are for scalar and texture handling respectively
- L30 _protected function_ `virtual FTG_Texture EvaluateTexture(FTG_EvaluationContext* InContext)`
- L35 _protected function_ `virtual std::vector<FTG_Variant> GetEvaluateArgs()` — If you use the basic structure of variant expression then you'll need to implement this correctly. There are plenty of examples. This simplifies a lot of error checking and most of the error checking gets handled in the base class
- L40 _protected prototype_ `virtual FVector4f EvaluateVector_WithValue(FTG_EvaluationContext* InContext, const FVector4f* const Value, size_t Count);` — Evaluate vector only needs to be implemented if there vector handling isn't just a component-wise scalar handling. In our current implementation for instance Dot and cross product is a good example where special vector handling is required
- L45 _protected function_ `virtual bool ErrorCheckInputTextures() const` — Only override this if you don't want use the base class error handling (which is quite strict out of the box). Clamp expression is one which does it's own error checking and avoids using the strict handling of the base class
- L50 _protected prototype_ `virtual float EvaluateScalar(FTG_EvaluationContext* InContext);` — This only need to be overridden if want to have your own variant implementation along with the EvaluateTexture(...) method defined above. Most of the time overriding these will not be required.
- L51 _protected prototype_ `virtual FVector4f EvaluateVector(FTG_EvaluationContext* InContext);`
- L52 _protected prototype_ `virtual FLinearColor EvaluateColor(FTG_EvaluationContext* InContext);`
- L55 _public prototype_ `TG_DECLARE_VARIANT_EXPRESSION(TG_Category::Default);`
- L58 _public member_ `FTG_Variant Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))`
- L60 _public prototype_ `virtual void Evaluate(FTG_EvaluationContext* InContext) override;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Utilities/TG_Expression_MaterialID.h` (Public)


#### class `UTG_Expression_MaterialID`  
`class UTG_Expression_MaterialID : public UTG_Expression`  
_L16-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L20 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Utilities) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L24 _public member_ `FTG_Texture MaterialIDMap;` — `UPROPERTY(meta = (TGType = "TG_Input"))`
- L28 _public member_ `TArray<FMaterialIDMaskInfo> MaterialIDMaskInfos;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = NoCategory, meta = (TGType = "TG_Input", NoResetToDefault, TGPinNotConnectable = "true"))` — List of available colors extracted from the input texture. Selected colors will be shown as white in the output texture.
- L31 _public member_ `FMaterialIDCollection MaterialIDInfoCollection;` — `UPROPERTY()`
- L34 _public member_ `TArray<FLinearColor> ActiveColors;` — `UPROPERTY(Transient)`
- L37 _public member_ `int32 ActiveColorsCount;` — `UPROPERTY(Transient)`
- L41 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output of the node, which is the loaded texture asset
- L44 _protected prototype_ `virtual void Initialize() override;`
- L47 _private prototype_ `void UpdateActiveColors();`
- L51 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L54 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L55 _public function_ `virtual FText GetTooltipText() const override`
- L56 _public prototype_ `void SetMaterialIdMask(int32 Id, bool bEnable);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/Expressions/Utilities/TG_Expression_Utils.h` (Public)


#### class `UTG_Expression_Utils_MakeVector4`  
`class UTG_Expression_Utils_MakeVector4 : public UTG_Expression`  
_L57-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L61 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Utilities) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L65 _public member_ `float X = 0;` — `UPROPERTY(meta = (TGType = "TG_Input"))`
- L68 _public member_ `float Y = 0;` — `UPROPERTY(meta = (TGType = "TG_Input"))`
- L71 _public member_ `float Z = 0;` — `UPROPERTY(meta = (TGType = "TG_Input"))`
- L74 _public member_ `float W = 0;` — `UPROPERTY(meta = (TGType = "TG_Input"))`
- L78 _public member_ `FVector4f Output;` — `UPROPERTY(meta = (TGType = "TG_Output"))` — The height of the texture
- L81 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L82 _public function_ `virtual FText GetTooltipText() const override`

#### class `UTG_Expression_Utils_Resize`  
`class UTG_Expression_Utils_Resize : public UTG_Expression`  
_L87-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTG_Expression`
- L91 _public prototype_ `TG_DECLARE_EXPRESSION(TG_Category::Utilities) virtual void Evaluate(FTG_EvaluationContext* InContext) override;`
- L96 _public member_ `FTG_Texture Input;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = ""))` — The input image to resize
- L100 _public member_ `bool bMaintainAspectRatio = true;` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Maintain Aspect Ratio"))` — Whether to maintain aspect ratio for the output
- L104 _public member_ `FLinearColor BackgroundColor = FLinearColor(0, 0, 0, 0);` — `UPROPERTY(meta = (TGType = "TG_Input", PinDisplayName = "Background Color"))` — The background color to use for the output texture
- L108 _public member_ `FTG_Texture Output;` — `UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Output", PinDisplayName = ""))` — The output texture which should be resized to the desired dimensions
- L111 _public function_ `virtual FTG_Name GetDefaultName() const override`
- L112 _public function_ `virtual FText GetTooltipText() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_CustomVersion.h` (Public)


#### struct `FTG_CustomVersion`  
`struct FTG_CustomVersion`  
_L8-34_
- desc: Custom serialization version for Texture Graph asset config
- L30 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L33 _private function_ `FTG_CustomVersion()`

#### enum `FTG_CustomVersion::Type`  
`enum Type`  
_L10-27_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L16 _public enumerator_ `TGTextureAddedTexturePath` — Added TexturePath to FTG_Texture
- L19 _public enumerator_ `TGExpressionAddedBaseOutputSettings` — Added BaseOutputSettings to TG_Expression
- L22 _public enumerator_ `TGTextureDescAdded_bSRGB` — Added bSRGB to FTG_TextureDescriptor
- L25 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L26 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Graph.h` (Public)


#### struct `FTG_GraphTraversal`  
`struct FTG_GraphTraversal`  
_L19-29_
- desc: Graph Traversal A Graph internal struct populated at runtime used to Traverse it. This data is built by the Graph itself.
- L21 _public member_ `FTG_Ids InPins;`
- L22 _public member_ `FTG_Ids OutPins;`
- L24 _public member_ `FTG_Ids TraverseOrder;`
- L26 _public member_ `int32 InNodesCount = 0;` — number of starting nodes in the traverse order
- L27 _public member_ `int32 OutNodesCount = 0;` — number of ending nodes in the traverse order
- L28 _public member_ `int32 NodeWavesCount = 0;` — number of waves to go through the graph

#### class `UTG_Graph`  
`class UTG_Graph : public UObject`  
_L44-361_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L53 _private prototype_ `void SetupNode(UTG_Node* Node);` — Inner setup node, used when a new node is created in this graph The node is initialized, assigned a uuid in the graph The node pins are created from the expression signature Notifiers are installed
- L59 _private prototype_ `void RegenerateNode(UTG_Node* InNode);` — Inner recreate node, used when the node's signature has changed, All the existing pins of the node are killed The new signature is obtained from the Expression the new pins are created
- L62 _private prototype_ `void AllocateNodePins(UTG_Node* Node);` — Inner allocate node pins, used when a node is setup or when a node is regenerated
- L64 _private prototype_ `void KillNodePins(UTG_Node* Node);` — Inner kill node pins, used when a node is removed or when a node is regenerated
- L67 _private prototype_ `FTG_Id AllocatePin(UTG_Node* Node, const FTG_Argument& SourceArg, int32 PinIdx = -1);` — Inner allocate pin
- L69 _private prototype_ `void KillPin(FTG_Id InPin);` — Inner kill pin
- L74 _private member_ `TArray<TObjectPtr<UTG_Node>> Nodes;` — `UPROPERTY()` — The array of nodes indexed by their uuid.NodeIdx() An element can be null if the node has been removed during the authoring
- L77 _private member_ `FString Name = TEXT("non` — `UPROPERTY()`
- L80 _private member_ `TMap<FName, FTG_Id> Params;` — `UPROPERTY(EditAnywhere, Transient, Category = "TextureGraphParams")` — The Parameter pins in the graph
- L82 _private prototype_ `void NotifyGraphChanged(UTG_Node* InNode = nullptr, bool bIsTweaking = false);`
- L84 _private prototype_ `void NotifyNodePostEvaluate(UTG_Node* InNode, const FTG_EvaluationContext* InContext);`
- L86 _private function_ `bool IsValidNode(FTG_Id NodeId) const`
- L87 _private function_ `bool IsValidPin(FTG_Id PinId) const`
- L92 _protected prototype_ `void OnNodeChanged(UTG_Node* InNode, bool Tweaking);`
- L93 _protected prototype_ `void OnNodeSignatureChanged(UTG_Node* InNode);`
- L94 _protected prototype_ `void OnNodePinChanged(FTG_Id InPinId, UTG_Node* InNode);`
- L95 _protected prototype_ `void OnNodeAdded(UTG_Node* InNode);`
- L96 _protected prototype_ `void OnNodeRemoved(UTG_Node* InNode,FName InName);`
- L97 _protected prototype_ `void OnNodeRenamed(UTG_Node* InNode,FName OldName);`
- L100 _protected prototype_ `bool RenameParam(FName OldName, FName NewName);` — Rename existing param
- L104 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L107 _protected prototype_ `virtual void PostEditUndo() override;` — Override PostEditUndo method of UObject
- L111 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;` — Overwrite the modify to also mark the transient states as dirty
- L120 _public prototype_ `virtual void Construct(FString InName);` — Construct the Graph, can only be done once before "using" the graph
- L123 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Override Serialize method of UObject
- L127 _public prototype_ `virtual void PostLoad() override;` — Override the PostLoad method of UObject to finalize the un-serialization and fill in the runtime fields of the graph sub objects
- L130 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — Override PreSave method of UObject
- L140 _public prototype_ `UTG_Node* CreateExpressionNode(const UClass* ExpressionClass);` — Create a node from an Expression Class A new Expression instance is created along with the Node instance The Node is setup with its input and output pins reflecting the Signature of the Expression.
- L146 _public prototype_ `UTG_Node* CreateExpressionNode(UTG_Expression* NewExpression);` — Create a node from an initialized Expression A new Node instance is created which uses initialized expression The Node is setup with its input and output pins reflecting the Signature of the Expression.
- L155 _public prototype_ `void RemoveNode(UTG_Node* InNode);` — Remove the node The node is destroyed, its Uuid becomes invalid The associated Expression is dereferenced and potentially GCed All the associated Pins are destroyed As a consequence, each pin's associated connection Edge(s) are destroyed associated Var is dereferenced and potentially GCed
- L158 _public prototype_ `void AddPostPasteNode(UTG_Node* NewNode);` — Accessed from TG_EdGraphNode after a paste of a new node
- L162 _public prototype_ `bool Connect(UTG_Node& NodeFrom, FTG_Name& PinFrom, UTG_Node& NodeTo, FTG_Name& PinTo);` — Connect a output pin from a node to the specified input pin of the to node Return true if the edge is created or false if couldn't create the edge
- L165 _public prototype_ `static bool ConnectionCausesLoop(const UTG_Pin* PinFrom, const UTG_Pin* PinTo);` — Check that the connection from PinFrom to PInTO doesn't create a loop
- L171 _public prototype_ `static bool ArePinsCompatible(const UTG_Pin* PinFrom, const UTG_Pin* PinTo, FName& ConverterKey);` — Are 2 Pins compatible ? This function check that the 2 pins can be connected to each other in terms of their argument types A non empty ConverterKey is also returned if required to achieve a conversion of the pin A to the pin B The converterKey is then used during the evaluation to find the proper Converter
- L174 _public prototype_ `void RemovePinEdges(UTG_Node& InNode, FTG_Name& InPin);` — Remove all the edges connected to the specified Pin
- L177 _public prototype_ `void RemoveEdge(UTG_Node& NodeFrom, FTG_Name& PinFrom, UTG_Node& NodeTo, FTG_Name& PinTo);` — Remove a particular edge
- L180 _public prototype_ `void Reset();` — Reset the graph empty, destroy any nodes or associated resources
- L184 _public prototype_ `void AppendParamsSignature(FTG_Arguments& InOutArguments, TArray<FTG_Id>& InParams, TArray<FTG_Id>& OutParams) const;` — Create a Signature from the current graph topology declaring the current Params as Arguments The signature list the input and output pins of the graph
- L191 _public function_ `UTG_Node* GetNode(FTG_Id NodeId)` — Access a Node from Id
- L192 _public function_ `const UTG_Node* GetNode(FTG_Id NodeId) const`
- L195 _public function_ `UTG_Pin* GetPin(FTG_Id PinId)` — Access a Pin from Id
- L196 _public function_ `const UTG_Pin* GetPin(FTG_Id PinId) const`
- L199 _public function_ `UTG_Node* GetNodeFromPinId(FTG_Id PinId)` — Access the Node owning a Pin from the Pin Id
- L202 _public function_ `FTG_Var* GetVar(FTG_Id VarId)` — Access a Var from Id (the Id of a Var is similar to the Id of the Pin that owns it
- L208 _public function_ `FTG_Ids GetParamIds() const`
- L209 _public function_ `TArray<FName> GetParamNames() const`
- L211 _public prototype_ `FName GetParamName(const FTG_Id& InParamId) const;`
- L213 _public prototype_ `FTG_Ids GetInputParamIds() const;`
- L214 _public prototype_ `FTG_Ids GetOutputParamIds() const;`
- L217 _public function_ `FTG_Id FindParamPinId(const FName& InName) const` — Find a param pin from its name
- L218 _public function_ `const UTG_Pin* FindParamPin(const FName& InName) const`
- L219 _public function_ `UTG_Pin* FindParamPin(const FName& InName)`
- L222 _public prototype_ `int GetOutputParamTextures(TArray<FName>& OutNames, FTG_Ids& OutPinIds) const;` — Get the names and ids of the output params which are Textures
- L225 _public prototype_ `void ForEachNodes(std::function<void(const UTG_Node* , uint32 )> visitor) const;` — Iterate through all the VALID nodes
- L228 _public prototype_ `void ForEachPins(std::function<void(const UTG_Pin* , uint32 , uint32 )> visitor) const;` — Iterate through all the VALID pins
- L231 _public prototype_ `void ForEachVars(std::function<void(const FTG_Var* , uint32 , uint32 )> visitor) const;` — Iterate through all the VALID vars
- L234 _public prototype_ `void ForEachParams(std::function<void(const UTG_Pin* , uint32 )> visitor) const;` — Iterate through all the VALID Param pins
- L237 _public prototype_ `void ForEachEdges(std::function<void(const UTG_Pin* , const UTG_Pin* )> visitor) const;` — Iterate through all the VALID edges
- L240 _public prototype_ `void ForEachOutputSettings( std::function<void(const FTG_OutputSettings& )> visitor);` — Iterate through all the output settings
- L250 _public prototype_ `bool GetOutputParamValue(const FName& InName, FTG_Variant& OutVariant) const;` — Get the nammed <InName> output param value as FTG_Variant if it exists. The value is collected in the <OutVariant> parameter if found. return true if the correct nammed & typed param was found, false otherwise
- L254 _public prototype_ `int GetAllOutputParamValues(TArray<FTG_Variant>& OutVariants, TArray<FName>* OutNames = nullptr) const;` — Get all the output param's value as FTG_Variant along with their names optionally
- L257 _public prototype_ `FTG_VarMap GetInputParamsVarMap();` — Get a map of input parameter vars from the graph
- L260 _public prototype_ `void SetInputParamsFromVarMap(FTG_VarMap InMap);` — Apply an override map of input parameter vars to the graph
- L263 _public prototype_ `void CollectOutputSettings(TMap<FTG_Id, FTG_OutputSettings>& OutExportSettingsMap) const;` — get a map of output settings from the graph
- L266 _public prototype_ `void SetOutputSettings(const TMap<FTG_Id, FTG_OutputSettings>& OutputSettingsMap);` — Apply an override map of output settings to the graph
- L275 _public prototype_ `TArray<FTG_Id> GatherSourceNodes(const UTG_Node* Node) const;` — Useful function to navigate the Node Collect all the DIRECT nodes whose output pins which are connected to the input pins of this node
- L279 _public prototype_ `TArray<FTG_Id> GatherAllSourceNodes(const UTG_Node* Node) const;` — Useful function to navigate the Nodes Collect all the nodes which are connecting directly or indirectly into the specified node
- L284 _public prototype_ `bool Validate(MixUpdateCyclePtr Cycle);` — Validate internal checks, warnings and errors, Returns true if Graph is valid and has no validation errors
- L287 _public prototype_ `const FTG_GraphTraversal& GetTraversal() const;` — Access the traversal  (update it if needed)
- L293 _public typedef_ `using NodeVisitor = void (*) (UTG_Node*, int32, int32);` — Traversal Visitor function type Node visited Index of the node in the traverse order Subgraph level we are currently visiting
- L294 _public typedef_ `using NodeVisitorFunction = std::function<void (UTG_Node*, int32, int32)>;`
- L297 _public prototype_ `void Traverse(NodeVisitorFunction visitor, int32 graph_depth = 0) const;` — Traverse!
- L303 _public prototype_ `void Evaluate(FTG_EvaluationContext* InContext);` — Evaluate the graph Traverse every nodes in the traversal order and call the node's expression evaluate method A configured evaluation context with a valid Cycle is required Evaluation is concretely implemented in FTG_Evaluation struct
- L306 _public function_ `const TArray<TObjectPtr<UObject>>& GetExtraEditorNodes() const`
- L307 _public prototype_ `void SetExtraEditorNodes(const TArray<TObjectPtr<const UObject>>& InNodes);`
- L312 _protected prototype_ `void GatherOuterNodes(const TArray<FTG_Ids>& sourceNodesPerNode, TSet<FTG_Id>& nodeReservoirA, TSet<FTG_Id>& nodeReservoirB) const;` — Utility functions used to establish the traversal order
- L313 _protected prototype_ `void EvalInOutPins() const;`
- L314 _protected prototype_ `void EvalTraverseOrder() const;`
- L319 _protected member_ `TArray<TObjectPtr<UObject>> ExtraEditorNodes;` — `UPROPERTY()` — Extra data to hold information that is useful only in editor (like comments)
- L326 _protected member_ `mutable bool bIsGraphTraversalDirty = true;` — `UPROPERTY(Transient)` — Pure data struct evaluated at runtime when traversal is required And a dirty flag
- L327 _protected member_ `mutable FTG_GraphTraversal Traversal;`
- L332 _public member_ `FOnTGNodeSignatureChanged OnNodeSignatureChangedDelegate;`
- L333 _public member_ `FOnTextureGraphChanged OnGraphChangedDelegate;`
- L334 _public member_ `FOnNodeEvaluation OnNodePostEvaluateDelegate;`
- L335 _public member_ `FOnTGNodeAdded OnTGNodeAddedDelegate;`
- L336 _public member_ `FOnTGNodeRemoved OnTGNodeRemovedDelegate;`
- L337 _public member_ `FOnTGNodeRenamed OnTGNodeRenamedDelegate;`
- L343 _public prototype_ `void Log() const;` — Log the graph description to the log output buffer
- L345 _public member_ `static constexpr int32 LogHeaderWidth = 32;` — width in number of chars for any header token during logging
- L346 _public prototype_ `FString LogNodes(FString InTab = TEXT("")) const;`
- L347 _public prototype_ `FString LogParams(FString InTab = TEXT("")) const;`
- L348 _public prototype_ `FString LogTraversal(FString InTab = TEXT("")) const;`
- L349 _public prototype_ `FString LogVars(FString InTab = TEXT("")) const;`
- L350 _public prototype_ `static FString LogCall(const TArray<FTG_Id>& PinInputs, const TArray<FTG_Id>& PinOutputs, int32 InputLogWidth = 10);`
- L358 _public member_ `int IsRuntime = 0;` — 0 = DiskVersion, 1 = Runtime copy made by TG_Editor, 2 = Runtime copy made by TG_Expression_Graph

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTGNodeSignatureChanged, UTG_Node*);`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTGNodeSignatureChanged, UTG_Node*);`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTextureGraphChanged, UTG_Graph*, UTG_Node*, bool);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTextureGraphChanged, UTG_Graph*, UTG_Node*, bool);`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeEvaluation, UTG_Node*, const FTG_EvaluationContext*);`
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeEvaluation, UTG_Node*, const FTG_EvaluationContext*);`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTGNodeAdded, UTG_Node*);`
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTGNodeAdded, UTG_Node*);`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTGNodeRemoved, UTG_Node*,FName);`
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTGNodeRemoved, UTG_Node*,FName);`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTGNodeRenamed, UTG_Node*, FName);`
- L39 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTGNodeRenamed, UTG_Node*, FName);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_GraphEvaluation.h` (Public)


#### struct `FVarArgument`  
`struct FVarArgument`  
_L14-35_
- reflection: `USTRUCT()`
- L19 _public member_ `FTG_Var Var;` — `UPROPERTY()`
- L22 _public member_ `FTG_Argument Argument;` — `UPROPERTY()`
- L25 _public function_ `bool Serialize(FArchive& Ar)` — Custom Serialize method for FVarArgument

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FVarArgument> : public TStructOpsTypeTraitsBase2<FVarArgument>`  
_L37-43_
- inherits: `TStructOpsTypeTraitsBase2<FVarArgument>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L40-42_

#### struct `FTG_OutputVarMap`  
`struct FTG_OutputVarMap`  
_L45-83_
- L53 _public member_ `TMap<FName, FOutputVarArgument> VarArguments;`
- L55 _public function_ `FTG_Var* GetVar(FName Name)`
- L67 _public function_ `const FTG_Argument* GetVarArgument(FName Name)`
- L79 _public function_ `void Empty()`

#### struct `FTG_OutputVarMap::FOutputVarArgument`  
`struct FOutputVarArgument`  
_L47-51_
- L49 _public member_ `FTG_Var* Var;`
- L50 _public member_ `FTG_Argument Argument;`

#### struct `FTG_VarMap`  
`struct FTG_VarMap`  
_L86-121_
- reflection: `USTRUCT()`
- L91 _public member_ `TMap<FName, FVarArgument> VarArguments;` — `UPROPERTY()`
- L93 _public function_ `FTG_Var* GetVar(FName Name)`
- L105 _public function_ `const FTG_Argument* GetVarArgument(FName Name)`
- L117 _public function_ `void Empty()`

#### struct `FTG_EvaluationContext`  
`struct FTG_EvaluationContext`  
_L124-153_
- L127 _public member_ `MixUpdateCyclePtr Cycle;` — The cycle used to call in the concrete TextureGraph engine system
- L131 _public member_ `FTG_VarMap Inputs;` — in and out buckets of vars passed as the arguments to the expression evaluate call For each node/expression, these are populated in the traverse/evaluate call in TG_Graph
- L132 _public member_ `FTG_OutputVarMap Outputs;`
- L136 _public member_ `TArray<FTG_Id> ConnectedInputParamIds;` — These are the Ids of the Vars connected as Param to an upper Graph These are persistent in the scope of a graph evaluation
- L137 _public member_ `TArray<FTG_Id> ConnectedOutputParamIds;`
- L139 _public member_ `UTG_Graph* Graph = nullptr;`
- L140 _public member_ `UTG_Node* CurrentNode = nullptr;`
- L142 _public member_ `int32 GraphDepth = 0;`
- L144 _public member_ `int32 TargetId = 0;`
- L147 _public member_ `bool bDoLog = true;` — For debug, let's log the evaluation call sequence while it happens
- L149 _public function_ `FORCEINLINE bool IsTweaking() const`

#### struct `FTG_Evaluation`  
`struct FTG_Evaluation`  
_L157-199_
- L159 _public member_ `static const FString GVectorToTextureAutoConv_Name;`
- L160 _public member_ `static const FString GColorToTextureAutoConv_Name;`
- L161 _public member_ `static const FString GFloatToTextureAutoConv_Name;`
- L163 _public prototype_ `static void EvaluateGraph(UTG_Graph* InGraph, FTG_EvaluationContext* Context);`
- L164 _public prototype_ `static void EvaluateNodeArray(UTG_Node* InNode, const TArray<TObjectPtr<UTG_Pin>>& ArrayInputs, const TArray<TObjectPtr<UTG_Pin>>& NonArrayPins, int MaxCount, FTG_EvaluationContext* Context);`
- L166 _public prototype_ `static void EvaluateNode(UTG_Node* InNode, FTG_EvaluationContext* Context);`
- L168 _public prototype_ `static void TransferVarToPin(UTG_Pin* InPin, FTG_EvaluationContext* Context, int Index);`
- L169 _public prototype_ `static int FilterArrayInputs(FTG_EvaluationContext* InContext, const TArray<TObjectPtr<UTG_Pin>>& InPins, TArray<TObjectPtr<UTG_Pin>>& ArrayPins, TArray<TObjectPtr<UTG_Pin>>& NonArrayPins);`
- L180 _public typedef_ `typedef TFunction<void(VarConverterInfo& Info)> VarConverter;`
- L182 _public typedef_ `typedef TMap <FName, VarConverter> ConverterMap;`
- L183 _public member_ `static ConverterMap DefaultConverters;`
- L184 _public prototype_ `static FName MakeConvertKey(FName From, FName To);`
- L185 _public prototype_ `static FName MakeConvertKey(const FTG_Argument& ArgFrom, const FTG_Argument& ArgTo);`
- L195 _public typedef_ `typedef TFunction<bool(VarConformerInfo& Info)> VarConformer;`
- L197 _public prototype_ `static bool AreArgumentsCompatible(const FTG_Argument& ArgFrom, const FTG_Argument& ArgTo, FName& ConverterKey);`

#### struct `FTG_Evaluation::VarConverterInfo`  
`struct VarConverterInfo`  
_L173-179_
- desc: Converter used to introduce transformation from one var to another var when the arguments are compatible but require to be converted
- L175 _public member_ `FTG_Var* InVar = nullptr;`
- L176 _public member_ `FTG_Var* OutVar = nullptr;`
- L177 _public member_ `int Index = -1;`
- L178 _public member_ `FTG_EvaluationContext* Context = nullptr;`

#### struct `FTG_Evaluation::VarConformerInfo`  
`struct VarConformerInfo`  
_L188-194_
- desc: Conformer functors used to conform pin values
- L190 _public member_ `FTG_Var* InVar = nullptr;`
- L191 _public member_ `FTG_Var* OutVar = nullptr;`
- L192 _public member_ `int Index = -1;`
- L193 _public member_ `FTG_EvaluationContext* Context = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L41 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonbb3886730103`) — Enables the use of a custom Serialize method

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Hash.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `FTG_Hash TG_Hash(FTG_Hash H);`
- L9 _prototype_ `FTG_Hash TG_HashName(FTG_Name& Name);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_HelperFunctions.h` (Public)


#### class `FTG_HelperFunctions`  
`class FTG_HelperFunctions`  
_L16-53_
- L20 _public prototype_ `static void InitTargets(UTextureGraphBase* InTextureGraph);`
- L21 _public prototype_ `static TArray<BlobPtr> GetTexturedOutputs(const UTG_Node* Node, FTG_EvaluationContext* TextureConversionContext = nullptr);`
- L23 _public prototype_ `static void EnsureOutputIsTexture(MixUpdateCyclePtr Cycle, UTG_Node* OutputNode);`
- L25 _public prototype_ `static JobBatchPtr InitExportBatch(UTextureGraphBase* InTextureGraph, FString ExportPath, FString AssetName, FExportSettings& TargetExportSettings, bool OverrideExportPath, bool OverwriteTextures, bool ExportAllOutputs, bool bSave);`
- L26 _public prototype_ `static AsyncInt ExportAsync(UTextureGraphBase* InTextureGraph, FString ExportPath, FString AssetName, FExportSettings& TargetExportSettings, bool OverrideExportPath, bool OverwriteTextures = true, bool ExportAllOutputs = false, bool bSave = true);`
- L28 _public prototype_ `static JobBatchPtr InitRenderBatch(UTextureGraphBase* InTextureGraph, JobBatchPtr ExistingBatch = nullptr);`
- L29 _public prototype_ `static AsyncBool RenderAsync(UTextureGraphBase* InTextureGraph, JobBatchPtr ExistingBatch = nullptr);`
- L32 _public function_ `template <typename T_Type> static TArray<T_Type> GetOutputsOfType(const UTG_Node* Node)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Material.h` (Public)


#### struct `FTG_Material`  
`struct FTG_Material`  
_L12-52_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY(Transient, EditAnywhere, Category = "Material", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))`
- L20 _public prototype_ `FTG_Material() = default;`
- L21 _public prototype_ `FTG_Material(const FTG_Material& InSrc) = default;`
- L22 _public prototype_ `FTG_Material& operator = (const FTG_Material& RHS) = default;`
- L26 _public prototype_ `bool IsValid() const;` — Check that the referenced asset is valid. If true, the GetMaterial call will NOT return nullptr
- L30 _public prototype_ `UMaterialInterface* GetMaterial() const;` — Access the referenced Material asset return a valid MaterialInterface object or null if the reference is invalid.
- L33 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);` — Assign the referenced asset from an actual UMaterialInsterface* live object
- L35 _public prototype_ `bool Serialize(FArchive& Ar);`
- L37 _public prototype_ `bool operator==(const FTG_Material& RHS) const = default;`
- L38 _public prototype_ `void ResetTexturePath();`
- L40 _public function_ `void InitFromString(const FString& StrVal)`
- L45 _public function_ `FString ToString() const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTG_Material> : public TStructOpsTypeTraitsBase2<FTG_Material>`  
_L56-65_
- inherits: `TStructOpsTypeTraitsBase2<FTG_Material>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L60-64_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L61 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anoncf9a36b80103`)
- L62 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anoncf9a36b80103`)
- L63 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncf9a36b80103`)

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Node.h` (Public)


#### struct `FTG_NodeEditorData`  
`struct FTG_NodeEditorData`  
_L18-35_
- reflection: `USTRUCT()`
- L23 _public member_ `int32 PosX = 0;` — `UPROPERTY()`
- L25 _public member_ `int32 PosY = 0;` — `UPROPERTY()`
- L28 _public member_ `FString NodeComment;` — `UPROPERTY()`
- L31 _public member_ `bool bCommentBubblePinned = false;` — `UPROPERTY()`
- L34 _public member_ `bool bCommentBubbleVisible = false;` — `UPROPERTY()`

#### class `UTG_Node`  
`class UTG_Node : public UObject`  
_L44-226_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: A Node in the graph Created from the graph Expose the Input and Output pins UTG_Node is created from a UTG_Graph
- L49 _private member_ `TSharedPtr<FTG_Signature> Signature;`
- L53 _private member_ `TObjectPtr<UTG_Expression> Expression = nullptr;` — `UPROPERTY()` — Note: This property is assigned at construction of the node in the Construct call
- L57 _private member_ `FTG_Id Id;` — `UPROPERTY(Transient, TextExportTransient)` — Assigned by Graph and restored postLoad
- L60 _private prototype_ `void Construct(UTG_Expression* InExpression);`
- L67 _private prototype_ `void Initialize(FTG_Id Id);` — Initialize the node after being created from the graph or unserialized This is when the Graph assign itself and the Id to the node The expression member must be valid: - assigned with the Construct call above for a brand new node - or recovered from serialization
- L71 _private prototype_ `FTG_Arguments GetPinArguments() const;` — Evaluate the arguments array deduced from the current array of Pins and the arguments This is used to compare the validity of the PIn's against the Expression signature
- L75 _private prototype_ `bool CheckPinSignatureAgainstExpression() const;` — Check that the node signature deduced from the pin's array is the same as the signature from the Expression return false if it is not the case, true otherwise
- L80 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Override Serialize method of UObject
- L83 _public prototype_ `UTG_Graph* GetGraph() const;` — The Graph in which this node exists
- L86 _public function_ `UTG_Expression* GetExpression() const` — The expression owned by this node
- L89 _public function_ `FTG_Id GetId() const` — Get the Uuid for this node
- L92 _public prototype_ `virtual bool Validate(MixUpdateCyclePtr Cycle);` — Validate internal checks, warnings and errors
- L95 _public prototype_ `FTG_Name GetNodeName() const;` — Node name is the title name of the inner expression
- L101 _public prototype_ `const FTG_Signature& GetSignature() const;`
- L103 _public function_ `bool HasInputs() const`
- L104 _public function_ `bool HasOutputs() const`
- L105 _public function_ `bool HasPrivates() const`
- L107 _public function_ `bool IsParam() const`
- L108 _public function_ `bool IsInputParam() const`
- L109 _public function_ `bool IsOutputParam() const`
- L117 _public member_ `TArray<TObjectPtr<UTG_Pin>> Pins;` — `UPROPERTY()`
- L120 _public prototype_ `int32 ForEachInputPins(std::function<void(const UTG_Pin* , uint32 )> visitor) const;` — Iterate through all the Input OR Output pins in this node, return the number traversed
- L121 _public prototype_ `int32 ForEachOutputPins(std::function<void(const UTG_Pin* , uint32 )> visitor) const;`
- L124 _public prototype_ `int32 GetInputPins(TArray<const UTG_Pin*>& OutPins) const;` — Collect the input / output pins
- L125 _public prototype_ `int32 GetOutputPins(TArray<const UTG_Pin*>& OutPins) const;`
- L126 _public prototype_ `int32 GetInputPins(TArray<UTG_Pin*>& OutPins) const;`
- L127 _public prototype_ `int32 GetOutputPins(TArray<UTG_Pin*>& OutPins) const;`
- L130 _public prototype_ `FTG_Id GetInputPinIdAt(FTG_Index inIndex) const;` — Get pin Id from index in each scope
- L131 _public prototype_ `FTG_Id GetOutputPinIdAt(FTG_Index outIndex) const;`
- L132 _public prototype_ `FTG_Id GetPrivatePinIdAt(FTG_Index privateIndex) const;`
- L134 _public prototype_ `TArray<FTG_Id> GetInputPinIds() const;`
- L135 _public prototype_ `TArray<FTG_Id> GetOutputPinIds() const;`
- L136 _public prototype_ `TArray<FTG_Id> GetPrivatePinIds() const;`
- L139 _public prototype_ `FTG_Id GetPinId(FName Name) const;` — Get/Find the Pin Id for Pins of this Node from its Argument Name
- L140 _public prototype_ `FTG_Id GetInputPinID(FTG_Name& Name) const;`
- L141 _public prototype_ `FTG_Id GetOutputPinID(FTG_Name& Name) const;`
- L142 _public prototype_ `FTG_Id GetPrivatePinID(FTG_Name& Name) const;`
- L144 _public prototype_ `UTG_Pin* GetInputPinAt(FTG_Index inIndex) const;`
- L145 _public prototype_ `UTG_Pin* GetOutputPinAt(FTG_Index outIndex) const;`
- L146 _public prototype_ `UTG_Pin* GetPrivatePinAt(FTG_Index privateIndex) const;`
- L148 _public prototype_ `UTG_Pin* GetPin(FName Name) const;`
- L149 _public prototype_ `UTG_Pin* GetInputPin(FTG_Name& name) const;`
- L150 _public prototype_ `UTG_Pin* GetOutputPin(FTG_Name& name) const;`
- L151 _public prototype_ `UTG_Pin* GetPrivatePin(FTG_Name& name) const;`
- L153 _public prototype_ `UTG_Pin* GetPin(FTG_Id pinID) const;`
- L155 _public prototype_ `TArray<FTG_Id> GetInputVarIds() const;`
- L156 _public prototype_ `TArray<FTG_Id> GetOutputVarIds() const;`
- L165 _public prototype_ `int GetAllOutputValues(TArray<FTG_Variant>& OutVariants, TArray<FName>* OutNames = nullptr) const;` — Get all the output's values which are compatible with FTG_Variant along with their names optionally
- L169 _public prototype_ `int GetAllOutputValues(TArray<FTG_Texture>& OutTextures, TArray<FName>* OutNames = nullptr) const;` — Get all the output's values which are compatible with FTG_Texture along with their names optionally
- L173 _public prototype_ `FTG_Variant::EType GetExpressionCommonInputVariantType() const;` — Get the current common input variant type of the expression only valid for expression with FTG_Variant arguments
- L175 _public prototype_ `void OnPinConnectionUndo(FTG_Id InPinId);`
- L182 _protected prototype_ `TArray<FName> GetPinAliasNames(uint8 AccessFilter = 0) const;` — Return the array of alias name of all the pins Can be filtered based on the argument access type bitfield Default is not filtered, aka AccessFilter is 0
- L191 _protected prototype_ `FName ValidateGeneratePinAliasName(FName CandidateName, const FTG_Id& PinId) const;` — Check that a candidate Pin's alias name is unique in the Node's Pins And in the Graph's Param Pins if it is a Param. If not edit it to propose a unique name that could work return the CandidateName as is or the modified version This is meant to be used from within the Pin::SetAliasName call or when a new pin is allocated to make sure its default alias name doesn't collide in the scope of the node or of the graph if it is a param
- L194 _protected prototype_ `void ValidateGenerateConformer(UTG_Pin* NewPin);` — Validate that the node conforms to a conformant function coming from the Expression
- L197 _protected prototype_ `void NotifyGraphOfNodeChange(bool bIsTweaking);` — Trigger notification to the graph that the node pin's value (default input or output) has changed
- L202 _protected prototype_ `void OnExpressionChangedWithoutVar(const FPropertyChangedEvent& PropertyChangedEvent);`
- L203 _protected prototype_ `void OnSignatureChanged();`
- L204 _protected prototype_ `void OnPinRenamed(FTG_Id InPinId, FName OldName);`
- L206 _protected prototype_ `void OnPinConnectionChanged(FTG_Id InPinId, FTG_Id OldPinId, FTG_Id NewPinId);`
- L209 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L210 _protected prototype_ `virtual void PostEditUndo() override;`
- L211 _protected prototype_ `void OnPostUndo();`
- L214 _protected member_ `TSet<FName> WarningStack;`
- L220 _public member_ `FTG_NodeEditorData EditorData;` — `UPROPERTY()`
- L224 _public prototype_ `FString LogHead() const;` — Logging Utilities
- L225 _public prototype_ `FString LogPins(FString Tab) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L228 _typedef_ `using FTG_Nodes = TArray<UTG_Node*>;`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_OutputSettings.h` (Public)


#### struct `FOutputExpressionInfo`  
`struct FOutputExpressionInfo`  
_L17-31_
- reflection: `USTRUCT()`
- L23 _public member_ `FName OutputName;` — `UPROPERTY()`
- L25 _public member_ `FTG_Id OutputNodeID;`
- L27 _public function_ `bool operator==(const FOutputExpressionInfo& Other) const`

#### class `UTG_ExportSettings`  
`class UTG_ExportSettings : public UObject`  
_L34-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L40 _public member_ `TArray<FOutputExpressionInfo> OutputExpressionsInfos;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = NoCategory, meta = (HideItemCount, NoResetToDefault, EditFixedOrder, ShowOnlyInnerProperties, FullyExpand))`

#### struct `FTG_OutputSettings`  
`struct FTG_OutputSettings`  
_L44-118_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `FName BaseName;` — `UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Basic", DisplayName = "File Name", Meta = (NoResetToDefault))` — Export name of the textured asset.
- L53 _public member_ `FName OutputName;` — `UPROPERTY()`
- L57 _public member_ `FName FolderPath;` — `UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Basic", DisplayName = "Path", Meta = (NoResetToDefault))` — Export path for the textured asset.
- L61 _public member_ `EResolution Width = EResolution::Auto;` — `UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Advanced", Meta = (NoResetToDefault))` — Width of the texture in pixels. Auto means system will detect automatically based on other images
- L65 _public member_ `EResolution Height = EResolution::Auto;` — `UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Advanced", Meta = (NoResetToDefault))` — Height of the texture in pixels. Auto means system will detect automatically based on other images
- L69 _public member_ `ETG_TextureFormat TextureFormat = ETG_TextureFormat::BGRA8;` — `UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Advanced", DisplayName = "Texture Format", Meta = (NoResetToDefault))` — List of available texture formats. Auto means system will detect automatically based on the input
- L73 _public member_ `ETG_TexturePresetType TexturePresetType = ETG_TexturePresetType::None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced", DisplayName = "Texture Type", Meta = (NoResetToDefault))` — List of available texture presets available for export.
- L85 _public member_ `bool bSRGB = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced", DisplayName = "sRGB", Meta = (NoResetToDefault, EditCondition = "TexturePresetType == ETG_TexturePresetType::None"))` — Adjust the color space of exporting textured asset. Can be in Linear or Gamma color space.
- L88 _public member_ `bool bShouldExport = true;` — `UPROPERTY()`
- L90 _public function_ `FString GetFullOutputName()`
- L93 _public function_ `bool operator==(const FTG_OutputSettings& Other) const`
- L98 _public prototype_ `void Initialize(FString PathName, FName InName = "Out`
- L100 _public function_ `void InitFromString(const FString& StrVal)`
- L106 _public function_ `FString ToString() const`
- L113 _public prototype_ `void Set(int InWidth, int InHeight, FName Name = "None", FName Path = "None", ETG_TextureFormat Format = ETG_TextureFormat::BGRA8, ETG_TexturePresetType InTextureType = ETG_TexturePresetType::None, TextureCompressionSettings InCompression = TextureCompressionSettings::TC_Default, TextureGroup InLodGroup = TextureGroup::TEXTUREGROUP_World, bool InbSRGB = false);`
- L116 _public prototype_ `void OnSetTexturePresetType(ETG_TexturePresetType Type);`
- L117 _public prototype_ `bool Validate(FString& OutErrors) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Pin.h` (Public)


#### class `UTG_Pin`  
`class UTG_Pin : public UObject`  
_L31-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Pin is a struct referencing: the Node where it belongs and the ArgumentHash to the corresponding Argument in the Signature The Edge(s) connecting to this pin, aka the other pinId to which this pin is connected. The Var containing the default value for this pin Pins are stored in the Graph. Created when instancing a Node.
- L38 _private prototype_ `void Construct(FTG_Id InId, const FTG_Argument& InArgument);` — Only accessible by UTG_Graph when allocating a new Pin.
- L41 _private prototype_ `void InitSelfVar();` — Initialize the self var with the matching expression argument
- L43 _private prototype_ `void ResetSelfVarDefault();`
- L46 _private prototype_ `void RemapId(FTG_Id InId);` — Used when remapping a pin to a different id, update the sefl Var if as well
- L52 _private prototype_ `void RemoveAllEdges();` — Should be protected, Used by TG_Graph when updating connections These have NO side effects, they just update the Pin members.
- L53 _private prototype_ `void RemoveEdge(FTG_Id OtherPinId);`
- L54 _private prototype_ `void AddEdge(FTG_Id OtherPinId);`
- L55 _private prototype_ `void RemapEdgeId(FTG_Id OldId, FTG_Id NewId);`
- L57 _private prototype_ `void InstallInputVarConverterKey(FName ConverterKey);`
- L58 _private prototype_ `void RemoveInputVarConverterKey();`
- L62 _private member_ `FTG_Id Id;` — `UPROPERTY()` — Id member is assigned by TG_Graph at creation, potentially modified during a remap
- L65 _private member_ `FTG_Argument Argument;` — `UPROPERTY()` — The argument copied from the signature of the node
- L68 _private member_ `FName AliasName;` — `UPROPERTY(Setter, Getter)` — The Alias name for this pin that can be customized and overwrite the Argument name
- L71 _private member_ `TArray<FTG_Id> Edges;` — `UPROPERTY()` — The edge array contains the Pin Id of the other side of the connection
- L78 _private member_ `FTG_Var SelfVar;` — `UPROPERTY()` — SelfVar is the Var owned by this pin containing the value. For an input pin, SelfVar is containing the value of the pin without any connection For an output pin, SelfVar is The var shared across all the connections with the other pins. For a setting pin SelfVar is not valid, the value is accessed directly through the UProperty in the Expression
- L83 _private member_ `FName InputVarConverterKey;` — `UPROPERTY()` — Input var ConverterKey is indicating that the Pin is fed from a Pin/Var which is compatible BUT requires a conversion during evaluation.
- L89 _private member_ `FTG_Var ConvertedVar;` — `UPROPERTY(Transient)` — When an InputVarConverterKey is installed, then we host the result of the conversion as var value here this member is not saved and updated on every evaluation It is only useful during the evaluation to capture the value passed in and converted from a connected pin
- L92 _protected prototype_ `void NotifyPinSelfVarChanged(bool bIsTweaking = false);`
- L95 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L99 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Override serialization for conditional serialization of SelfVar
- L101 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L104 _public function_ `bool IsValid() const`
- L106 _public prototype_ `UTG_Node* GetNodePtr() const;`
- L107 _public prototype_ `FTG_Id GetNodeId() const;`
- L109 _public function_ `FTG_Id GetId() const`
- L111 _public function_ `FTG_Argument GetArgument() const`
- L112 _public function_ `FTG_Name GetArgumentName() const`
- L114 _public function_ `FName GetAliasName() const`
- L115 _public prototype_ `void SetAliasName(FName InAliasName);` — Assign the alias name and notify the graph for change
- L116 _public function_ `bool HasAliasName() const`
- L118 _public function_ `FTG_ArgumentType GetArgumentType() const`
- L119 _public function_ `bool IsInput() const`
- L120 _public function_ `bool IsOutput() const`
- L121 _public function_ `bool IsParam() const`
- L122 _public function_ `bool IsSetting() const`
- L123 _public function_ `bool IsPrivate() const`
- L124 _public function_ `bool IsNotConnectable() const`
- L126 _public function_ `FName GetArgumentCPPTypeName() const`
- L128 _public function_ `const TArray<FTG_Id>& GetEdges() const`
- L129 _public function_ `bool IsConnected() const`
- L134 _public function_ `bool IsValidSelfVar() const` — Access the SelfVar of the Pin containing the currrent default value for the pin if an output pin, SelfVar contains the current result value produced by the node's expression by last evaluation if an input pin, SelfVar contains the current 'default' value of the pin used as expression input IF the pin is not connected.
- L135 _public function_ `const FTG_Var* GetSelfVar() const`
- L136 _public function_ `FTG_Var* EditSelfVar()`
- L137 _public function_ `FTG_Id GetSelfVarId() const` — SelfVarID is the same as this pin's id
- L144 _public function_ `FTG_Id GetVarId() const` — GetVarId returns the Id of the current valid Var for this Pin. if an output pin, it is SelfVar Id aka this pin Id if an input pin: if NOT connected, it is SelfVar ID if connected, it is the SelfVar Id of the Connected Pin
- L148 _public function_ `bool ConnectionNeedsConversion() const` — In the case the pin is an input, and is connected and the feeding pin var needs a conversion This implies that during the evaluation, the feeding Var is Converted into the SelfVar which is then input in the expression
- L149 _public function_ `FName GetInputVarConverterKey() const`
- L153 _public function_ `FTG_Var* EditConvertedVar()` — EditConvertedVar returns the internal Var used to input its value in the pin's expression AFTER conversion Should only be accessed by the Graph Evaluation
- L155 _public prototype_ `FString LogHead() const;`
- L156 _public prototype_ `FString Log(FString Tab) const;`
- L157 _public prototype_ `FString LogTooltip() const;`
- L161 _public prototype_ `FProperty* GetExpressionProperty() const;` — Access the FProperty associated to this pin in the Expression::Class of the node A valid FProperty is returned if it exists, null otherwise
- L163 _public member_ `FTG_Evaluation::VarConformer ConformerFunctor;`
- L164 _public function_ `bool NeedsConformance() const`
- L167 _public prototype_ `static FTG_Hash Hash(const UTG_Pin& Pin);` — Hashing
- L168 _public function_ `FTG_Hash Hash() const`
- L172 _public function_ `bool IsArgScalar() const` — Check the type of the argument's Var expected to be contained in the Pin's Var
- L173 _public function_ `bool IsArgBool() const`
- L174 _public function_ `bool IsArgString() const`
- L175 _public function_ `bool IsArgColor() const`
- L176 _public function_ `bool IsArgVector() const`
- L177 _public function_ `bool IsArgArray() const`
- L178 _public function_ `bool IsArgTextureArray() const`
- L179 _public function_ `bool IsArgTexture() const`
- L180 _public function_ `bool IsArgVariant() const`
- L181 _public function_ `bool IsArgObject(UClass* InClass) const`
- L188 _public prototype_ `bool GetValue(float& OutValue) const;` — Scalar getter only on a scalar argument
- L191 _public prototype_ `bool GetValue(bool& OutValue) const;` — bool getter only on a boolean argument
- L194 _public prototype_ `bool GetValue(FString& OutValue) const;` — String getter only on a FString argument
- L197 _public prototype_ `bool GetValue(FLinearColor& OutValue) const;` — Color or Vector getter only on a vector or color argument
- L198 _public prototype_ `bool GetValue(FVector4f& OutValue) const;`
- L201 _public prototype_ `bool GetValue(FTG_Texture& OutValue) const;` — Texture value getter only on a Texture argument
- L204 _public prototype_ `bool GetValue(FTG_VariantArray& OutValue) const;` — Texture value getter only on a Texture argument
- L208 _public prototype_ `bool GetValue(FTG_Variant& OutValue) const;` — Variant value getter only if a Variant argument OR if the argument is one of the supported type by Variant (Scalar/Color/Vector/Texture) After getting the value, the next step is to check the type contained in the variant.
- L219 _public prototype_ `FString GetEvaluatedVarValue() const;` — Useful for the UI: access the current value of this pin as passed to the evaluation if it is an input or received from the evaluation if it is an output if output pin: the selfVar else if input pin: if NOT connected: the selfVar else if connected with a conversion: the convertedVar else if connected without conversion: the Var from the connected pin This is MEANT TO BE USED for UI purpose !!!!
- L224 _public prototype_ `void FromString(const FString& InValueStr, bool bIsTweaking = false);` — Set the self var value from string Used by UI to assign pin default value This is the same as the selfvar setter
- L228 _public prototype_ `bool SetValue(float Value);` — Setters for Scalar, Color, Vector, bool and String  arguments These check that the arg is of the correct type
- L229 _public function_ `bool SetValue(double Value)`
- L230 _public function_ `bool SetValue(uint32 Value)`
- L231 _public function_ `bool SetValue(int32 Value)`
- L232 _public prototype_ `bool SetValue(bool bValue);`
- L233 _public prototype_ `bool SetValue(FString Value);` — FName pin is assigned by the templated version, not FString
- L234 _public prototype_ `bool SetValue(const FLinearColor& Value);`
- L235 _public prototype_ `bool SetValue(const FVector4f& Value);`
- L237 _public prototype_ `bool SetValue(const float* Value, size_t Count);`
- L238 _public function_ `bool SetValue(FTG_Texture&)` — this is not a possible case
- L239 _public function_ `bool SetValue(FTG_VariantArray&)` — this is not a possible case
- L240 _public prototype_ `bool SetValue(const FTG_TextureDescriptor& Value);`
- L245 _public function_ `template <typename T> bool SetValue(const T& Value)` — Template version of the setter works correctly as long as the selfvar contains exactly the specified type Use with care

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Signature.h` (Public)


#### enum `ETG_Access`  
`enum class ETG_Access : uint8`  
_L17-39_
- reflection: `UENUM()`
- desc: Pin access either a in(put) or out(put) or ?
- L19 _public enumerator_ `In = 0` — A regular Input access (read only in the expression)
- L20 _public enumerator_ `Out = 1` — A regular Output access (write only in the expression)
- L21 _public enumerator_ `InParam = 2` — An Input access also exported as a Param of the Graph
- L22 _public enumerator_ `OutParam = 3` — An Output access also exported as a Param of the Graph
- L23 _public enumerator_ `InSetting = 4` — A Setting is a regular input field of the expression, there is a default value that persists serialization
- L24 _public enumerator_ `OutSetting = 5` — A Setting is a regular output field of the expression, there is a default value that persists serialization
- L25 _public enumerator_ `InParamSetting = 6` — A Setting is a regular input field of the expression, also exported as a Param of the Graph
- L26 _public enumerator_ `OutParamSetting = 7` — A Setting is a regular output field of the expression, also exported as a Param of the Graph
- L27 _public enumerator_ `Private = 8` — A private field is a regular UProperty of the expression not exposed for connection
- L29 _public enumerator_ `OutputBitMask = 0x01` — the bit mask for just the IsOutput flag (or not aka is Input)
- L30 _public enumerator_ `ParamBitMask = 0x02` — the bit mask for just the Param flag
- L31 _public enumerator_ `SettingBitMask = 0x04` — the bit mask for just the Setting flag
- L32 _public enumerator_ `PrivateBitMask = 0x08` — the bit mask for just the PrivateField flag
- L34 _public enumerator_ `AccessBitMask = 0x0F` — The bit mask for ALL the flags defining the Access
- L36 _public enumerator_ `PersistentSelfVarFlag = 0x10` — the bit mask for just the Persistent Selfvar qualifier flag
- L37 _public enumerator_ `NotConnectableFlag = 0x20` — The bit mask for the Not Connectable qualifier flag
- L38 _public enumerator_ `EnumFlag = 0x40` — the bit mask for telling whether an argument is an enum or not

#### struct `FTG_ArgumentType`  
`struct FTG_ArgumentType`  
_L46-116_
- reflection: `USTRUCT()`
- desc: Descriptor struct of an argument core desc all the typing information for a pin EXCEPT its name
- L50 _public function_ `FTG_ArgumentType()`
- L51 _public function_ `FTG_ArgumentType(ETG_Access InAccess) : Flags(static_cast<uint8>(InAccess))`
- L52 _public function_ `FTG_ArgumentType(ETG_Access InAccess, uint8 Flags) : Flags(static_cast<uint8>(InAccess) | Flags)`
- L55 _public member_ `uint32 Flags = static_cast<uint8>(ETG_Access::In);` — `UPROPERTY()`
- L57 _public function_ `ETG_Access GetAccess() const`
- L58 _public function_ `bool IsInput() const`
- L59 _public function_ `bool IsOutput() const`
- L60 _public function_ `bool IsParam() const`
- L61 _public function_ `bool IsSetting() const`
- L62 _public function_ `bool IsPrivate() const`
- L63 _public function_ `bool MatchAccessFilter(uint8 InFilter) const`
- L65 _public function_ `bool IsPersistentSelfVar() const`
- L66 _public function_ `void SetPersistentSelfVar()`
- L68 _public function_ `bool IsNotConnectable() const`
- L69 _public function_ `bool IsEnum() const`
- L70 _public function_ `void SetNotConnectable()`
- L73 _public function_ `FTG_ArgumentType Unparamed() const`
- L87 _public function_ `FString ToString() const`

#### struct `FTG_Argument`  
`struct FTG_Argument`  
_L125-183_
- reflection: `USTRUCT()`
- desc: Argument of a signature: Combining a Name with an Argument type makes a unique Argument where the name is combined for hashing with the rest of the argument type fields
- L130 _public member_ `FName Name;` — `UPROPERTY()`
- L133 _public member_ `FName CPPTypeName;` — `UPROPERTY()`
- L136 _public member_ `FTG_ArgumentType ArgumentType;` — `UPROPERTY()`
- L139 _public member_ `TMap<FName, FString> MetaDataMap;` — `UPROPERTY()` — We can add any additional information required here.
- L141 _public function_ `FTG_Name GetName() const`
- L143 _public function_ `FTG_ArgumentType GetType() const`
- L144 _public function_ `bool IsInput() const`
- L145 _public function_ `bool IsOutput() const`
- L146 _public function_ `bool IsParam() const`
- L147 _public function_ `bool IsSetting() const`
- L148 _public function_ `bool IsPrivate() const`
- L150 _public function_ `bool IsPersistentSelfVar() const`
- L151 _public function_ `void SetPersistentSelfVar()`
- L153 _public function_ `bool IsNotConnectable() const`
- L154 _public function_ `void SetNotConnectable()`
- L156 _public function_ `FName GetCPPTypeName() const`
- L158 _public prototype_ `bool IsScalar() const;` — float or int
- L159 _public prototype_ `bool IsBool() const;` — boolean
- L160 _public prototype_ `bool IsString() const;` — string  but NOT FName
- L161 _public prototype_ `bool IsColor() const;` — FlinearColor
- L162 _public prototype_ `bool IsVector() const;` — FLinearColor or ...
- L163 _public prototype_ `bool IsTexture() const;` — FTG_Texture or ...
- L164 _public prototype_ `bool IsArray() const;` — FTG_TextureArray or ...
- L165 _public prototype_ `bool IsVariant() const;` — FTG_Variant
- L166 _public prototype_ `bool IsObject(UClass* InClass) const;` — check that the Argument is a UObject and of baseType InClass
- L167 _public prototype_ `bool GetMetaData(const FName KeyToFind, FString& OutValue);`
- L170 _public prototype_ `static FTG_Hash Hash(const FTG_Argument& Argument);` — Hashing
- L171 _public function_ `FTG_Hash Hash() const`
- L173 _public member_ `const static FTG_Argument Invalid;`
- L180 _public function_ `bool operator== (const FName& InArgName)` — Comparison operator against the Arg Name, useful for FindByKey on TArray of Arguments

#### struct `FTG_ArgumentSet`  
`struct FTG_ArgumentSet`  
_L193-220_
- desc: Argument Set: A container for several Arguments which is searchable and hashable The arguments all have an index (their position in the set). All the argument names in the set MUST be different. THe hashes of each arguments are also different as a consequence.
- L197 _public member_ `FTG_Arguments Arguments;`
- L201 _public function_ `const FTG_Argument& Get(FTG_Index Index) const` — Access the Argument at the Index in the set. const FTG_Argument& operator[] (const FTG_Index& Index) const
- L210 _public prototype_ `FTG_Index FindName(FTG_Name& Name) const;` — Find the Index of an argument at a particular name. Return INVALID_INDEX if not found
- L214 _public prototype_ `FTG_Index FindHash(FTG_Hash Hash) const;` — Find the Index of a argument at a particular hash. Return INVALID_INDEX if not found
- L217 _public prototype_ `static FTG_Hash Hash(const FTG_ArgumentSet& Set);` — Hashing
- L218 _public function_ `FTG_Hash Hash() const`

#### struct `FTG_Signature`  
`struct FTG_Signature`  
_L225-315_
- reflection: `USTRUCT()`
- desc: The Signature describe a full function signature a name + collection of arguments
- L235 _protected member_ `FTG_Name Name;`
- L236 _protected member_ `FTG_ArgumentSet InArgs;`
- L237 _protected member_ `FTG_ArgumentSet OutArgs;`
- L238 _protected member_ `FTG_ArgumentSet PrivateArgs;`
- L239 _protected member_ `bool bIsParam = false;`
- L243 _public prototype_ `FTG_Signature(const FInit& Init);`
- L244 _public function_ `FTG_Signature()`
- L249 _public prototype_ `FTG_Signature(const FTG_Signature& Other) = default;` — Added an defaulted copy constructor here because Clang 16 expects either both or neither copy constructor and copy assignment operator to be implemented.  But it's pretty weird for a type to do nothing on copy.  UStructs need an assignment operator so this would be surprising behavior.
- L250 _public function_ `FTG_Signature& operator= (const FTG_Signature& type)`
- L255 _public function_ `FTG_Name GetName() const`
- L259 _public function_ `const FTG_Arguments& GetInArguments() const` — Accessor to the argument set container's array One can get a particular Argument retrieved from the Index
- L260 _public function_ `const FTG_Arguments& GetOutArguments() const`
- L261 _public function_ `const FTG_Arguments& GetPrivateArguments() const`
- L264 _public function_ `FORCEINLINE int32 GetNumArguments() const` — Arguments accessed by linear index
- L267 _public prototype_ `const FTG_Argument& GetArgument(int32 ArgIdx);`
- L269 _public function_ `FTG_Arguments GetArguments() const`
- L276 _public function_ `FTG_Index FindInputArgument(FTG_Name& InName) const` — Find the Index of an input argument at a particular name. Return INVALID_INDEX if not found
- L280 _public function_ `FTG_Index FindOutputArgument(FTG_Name& InName) const` — Find the Index of an output argument at a particular name. Return INVALID_INDEX if not found
- L284 _public function_ `FTG_Index FindPrivateArgument(FTG_Name& InName) const` — Find the Index of a Private argument at a particular name. Return INVALID_ID if not found
- L286 _public function_ `bool HasInputs() const`
- L287 _public function_ `bool HasOutputs() const`
- L288 _public function_ `bool HasPrivates() const`
- L290 _public function_ `bool IsParam() const`
- L291 _public function_ `bool IsInputParam() const` — Input PARAM has Output
- L292 _public function_ `bool IsOutputParam() const` — Output PARAM has Input
- L299 _public typedef_ `using IndexAccessArray = TArray<IndexAccess>;`
- L301 _public prototype_ `IndexAccess FindArgumentIndexFromName(FTG_Name& InName) const;`
- L302 _public prototype_ `const FTG_Argument& FindArgumentFromName(FTG_Name& InName) const;`
- L305 _public prototype_ `static FTG_Hash Hash(const FTG_Signature& Type);` — Hashing
- L306 _public function_ `FTG_Hash Hash() const`
- L308 _public prototype_ `const FTG_Argument& FindArgumentFromHash(FTG_Hash Hash) const;`
- L309 _public prototype_ `IndexAccess FindArgumentIndexFromHash(FTG_Hash Hash) const;`
- L314 _public prototype_ `static FTG_Indices GenerateMappingArgIdxTable(const FTG_Signature& FromSignature, const FTG_Signature& ToSignature);` — Generate a mapping table of the argument indices which is an array of index elements The element at poisiton i indicate the mapping argument index in the FromSignature corresponding to index i in the ToSignature if the ToSignature argument doesn't have an equivalent, then INVALID_INDEX is at this element

#### struct `FTG_Signature::FInit`  
`struct FInit`  
_L229-232_
- L230 _public member_ `FTG_Name Name;`
- L231 _public member_ `FTG_Arguments Arguments;`

#### struct `FTG_Signature::IndexAccess`  
`struct IndexAccess`  
_L294-298_
- L296 _public member_ `FTG_Index Index = FTG_Id::INVALID_INDEX;`
- L297 _public member_ `ETG_Access Access = ETG_Access::In;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L41 _macro_ `#define AccessToUint8(AccessEnum) static_cast<uint8>(ETG_Access::AccessEnum)`
- L113 _function_ `friend bool operator== (const FTG_ArgumentType& lhs, const FTG_ArgumentType& rhs)`
- L117 _typedef_ `using FTG_ArgumentTypes = TArray<FTG_ArgumentType>;`
- L175 _function_ `friend bool operator== (const FTG_Argument& lhs, const FTG_Argument& rhs)`
- L184 _typedef_ `using FTG_Arguments = TArray<FTG_Argument>;`
- L186 _prototype_ `TArray<FName> TG_MakeArrayOfArgumentNames(const FTG_Arguments& InArguments);`
- L316 _typedef_ `using FTG_SignaturePtr = TSharedPtr< FTG_Signature >;`
- L319 _macro_ `#define TG_STR1(x) #x`
- L320 _macro_ `#define TG_STR(x) TG_STR1(x)`
- L321 _macro_ `#define TG_ARGUMENT_IN(name, t) { TEXT(TG_STR(name)), { ETG_Access::In }}`
- L322 _macro_ `#define TG_ARGUMENT_OUT(name, t) { TEXT(TG_STR(name)), { ETG_Access::Out }}`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_SystemTypes.h` (Public)


#### struct `FTG_Id`  
`struct FTG_Id`  
_L18-106_
- reflection: `USTRUCT()`
- L22 _public member_ `static constexpr FTG_Index INVALID_INDEX = -1;`
- L24 _public member_ `static const FTG_Id INVALID;`
- L27 _public member_ `uint32 _IndexRaw = 0xFFFFFFFF;` — `UPROPERTY()` — The saved value for the FTG_Id is a single uint32 containing the 2 sub indices as in16 packed.
- L29 _public function_ `uint32 IndexRaw()const`
- L31 _public function_ `int16 NodeIdx() const` — the main index for the node stored in the 4 top bytes of _IndexRaw
- L35 _public function_ `int16 PinIdx() const` — the secondary index for the pin in the node stored in the 4 lower bytes of _IndexRaw
- L40 _public function_ `FTG_Id()`
- L42 _public function_ `FTG_Id(int32 InNodeId, int32 InPinId = INVALID_INDEX) : _IndexRaw ( ((InNodeId << 16) & 0xFFFF0000) | (InPinId & 0x0000FFFF) )`
- L47 _public function_ `FORCEINLINE bool IsValid() const`
- L52 _public function_ `FORCEINLINE bool IsNodeId() const`
- L57 _public function_ `FORCEINLINE bool IsPinId() const`
- L62 _public function_ `FORCEINLINE bool operator==(const FTG_Id& Other) const`
- L67 _public function_ `FORCEINLINE bool operator!=(const FTG_Id& Other) const`
- L72 _public function_ `FORCEINLINE bool operator>=(const FTG_Id& Other) const`
- L77 _public function_ `FORCEINLINE bool operator>(const FTG_Id& Other) const`
- L82 _public function_ `FORCEINLINE bool operator<=(const FTG_Id& Other) const`
- L87 _public function_ `FORCEINLINE bool operator<(const FTG_Id& Other) const`
- L92 _public function_ `FORCEINLINE FString ToString() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraph, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraph, Log, All);`
- L13 _typedef_ `using FTG_Index = int32;`
- L14 _typedef_ `using FTG_Indices = TArray<FTG_Index>;`
- L16 _typedef_ `using ErrorReportMap = TMap<int32, TArray<struct FTextureGraphErrorReport>>;`
- L102 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FTG_Id& InID)` — Specialize the UE function GetTypeHash for the type FTG_Id Implemented in TG_Hash.cpp
- L109 _typedef_ `using FTG_Ids = TArray<FTG_Id>;`
- L112 _typedef_ `using FTG_Name = const FName;`
- L116 _prototype_ `FName TG_MakeNameUniqueInCollection(FName CandidateName, const TArray<FName>& Collection, FName RecursionPreFix = TEXT("_"), int32 RecursionCount = 0)` — Util function to validate that a name is unique in a collection and make a new candidate name if not It returns a FName equal to the Candidate if unique in the collection or a proposed edited candidate name which is unique
- L119 _typedef_ `using FTG_Hash = uint64;`
- L121 _namespace_ `namespace TG_TypeUtils`
- L123 _variable_ `const FString TEnumAsBytePrefix = TEXT("TEn` (scope `TG_TypeUtils`)
- L125 _variable_ `const FString BoolType = TEXT("boo` (scope `TG_TypeUtils`)
- L126 _variable_ `const FString FloatType = TEXT("flo` (scope `TG_TypeUtils`)
- L127 _variable_ `const FString DoubleType = TEXT("dou` (scope `TG_TypeUtils`)
- L128 _variable_ `const FString Int32Type = TEXT("int` (scope `TG_TypeUtils`)
- L129 _variable_ `const FString Int64Type = TEXT("int` (scope `TG_TypeUtils`)
- L130 _variable_ `const FString UInt8Type = TEXT("uin` (scope `TG_TypeUtils`)
- L131 _variable_ `const FString FNameType = TEXT("FNa` (scope `TG_TypeUtils`)
- L132 _variable_ `const FString FStringType = TEXT("FSt` (scope `TG_TypeUtils`)
- L133 _variable_ `const FString BoolArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L134 _variable_ `const FString FloatArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L135 _variable_ `const FString DoubleArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L136 _variable_ `const FString Int32ArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L137 _variable_ `const FString UInt8ArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L138 _variable_ `const FString FNameArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L139 _variable_ `const FString FStringArrayType = TEXT("TAr` (scope `TG_TypeUtils`)
- L141 _variable_ `const FName BoolTypeName = *BoolType;` (scope `TG_TypeUtils`)
- L142 _variable_ `const FName FloatTypeName = *FloatType;` (scope `TG_TypeUtils`)
- L143 _variable_ `const FName DoubleTypeName = *DoubleType;` (scope `TG_TypeUtils`)
- L144 _variable_ `const FName Int32TypeName = *Int32Type;` (scope `TG_TypeUtils`)
- L145 _variable_ `const FName Int64TypeName = *Int64Type;` (scope `TG_TypeUtils`)
- L146 _variable_ `const FName UInt8TypeName = *UInt8Type;` (scope `TG_TypeUtils`)
- L147 _variable_ `const FName FNameTypeName = *FNameType;` (scope `TG_TypeUtils`)
- L150 _namespace_ `namespace TG_MetadataSpecifiers`
- L153 _variable_ `const FName MD_HistogramLuminance = TEXT("MD_` (scope `TG_MetadataSpecifiers`) — Assign to a FTG_Texture UProperty to represent its luminance histogram in the detail view
- L156 _variable_ `const FName MD_ScalarEditor = TEXT("MD_` (scope `TG_MetadataSpecifiers`) — Assign to a float UProperty to go through the widget customizer
- L159 _variable_ `const FName MD_LevelsSettings = TEXT("MD_` (scope `TG_MetadataSpecifiers`) — Assign to Levels Settings FVector UProperty to go through the widget customizer

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Texture.h` (Public)


#### struct `FTG_TextureDescriptor`  
`struct FTG_TextureDescriptor`  
_L15-97_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public function_ `FTG_TextureDescriptor()`
- L22 _public function_ `FTG_TextureDescriptor(BufferDescriptor Desc)`
- L33 _public member_ `EResolution Width = EResolution::Auto;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced", Meta = (NoResetToDefault))` — Width of the texture in pixels. Auto means system will detect automatically based on other images
- L37 _public member_ `EResolution Height = EResolution::Auto;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced", Meta = (NoResetToDefault))` — Height of the texture in pixels. Auto means system will detect automatically based on other images
- L42 _public member_ `ETSBufferChannels NumChannels_DEPRECATED = ETSBufferChannels::Auto;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Texture Format instead"))` — How many items of type BufferFormat per point
- L45 _public member_ `ETSBufferFormat Format_DEPRECATED = ETSBufferFormat::Auto;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Texture Format instead"))` — What is the type of each item in the buffer
- L51 _public member_ `ETG_TextureFormat TextureFormat = ETG_TextureFormat::Auto;` — `UPROPERTY(EditAnywhere, Category = "TextureDescriptor", DisplayName = "Texture Format")` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced", DisplayName = "Texture Format", Meta = (NoResetToDefault))`
- L54 _public member_ `bool bIsSRGB = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced", DisplayName = "sRGB", Meta = (NoResetToDefault))`
- L56 _public function_ `bool operator==(const FTG_TextureDescriptor& RHS) const`
- L63 _public function_ `FORCEINLINE BufferDescriptor ToBufferDescriptor() const`
- L79 _public function_ `FORCEINLINE operator BufferDescriptor() const`
- L80 _public function_ `FORCEINLINE bool IsDefault() const`
- L85 _public function_ `void InitFromString(const FString& StrVal)`
- L91 _public function_ `FString ToString() const`

#### struct `FTG_Texture`  
`struct FTG_Texture`  
_L100-145_
- reflection: `USTRUCT()`
- L105 _public member_ `TiledBlobPtr RasterBlob = nullptr;`
- L108 _public member_ `FString TexturePath;` — `UPROPERTY(EditAnywhere, Category = "TextureDescriptor")`
- L111 _public member_ `FTG_TextureDescriptor Descriptor;` — `UPROPERTY(EditAnywhere, Category = "TextureDescriptor")`
- L113 _public prototype_ `FTG_Texture() = default;`
- L114 _public function_ `FTG_Texture(TiledBlobPtr RHS) : RasterBlob(RHS)`
- L116 _public function_ `operator TiledBlobPtr()`
- L117 _public function_ `operator TiledBlobRef()`
- L118 _public function_ `operator bool() const`
- L120 _public function_ `FTG_Texture& operator = (TiledBlobRef RHS)`
- L121 _public function_ `FTG_Texture& operator = (TiledBlobPtr RHS)`
- L122 _public prototype_ `bool operator == (const FTG_Texture& RHS) const;`
- L123 _public function_ `FORCEINLINE TiledBlob* operator -> () const`
- L124 _public prototype_ `void ResetTexturePath();`
- L129 _public function_ `static FTG_Texture GetBlack()`
- L130 _public function_ `static FTG_Texture GetWhite()`
- L131 _public function_ `static FTG_Texture GetGray()`
- L132 _public function_ `static FTG_Texture GetRed()`
- L133 _public function_ `static FTG_Texture GetGreen()`
- L134 _public function_ `static FTG_Texture GetBlue()`
- L135 _public function_ `static FTG_Texture GetYellow()`
- L136 _public function_ `static FTG_Texture GetMagenta()`
- L137 _public function_ `static FTG_Texture GetWhiteMask()`
- L138 _public function_ `static FTG_Texture GetBlackMask()`
- L144 _public function_ `FORCEINLINE BufferDescriptor GetBufferDescriptor() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEXTUREGRAPH_API`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Var.h` (Public)


#### struct `FTG_Var`  
`struct FTG_Var`  
_L30-219_
- reflection: `USTRUCT()`
- L49 _public typedef_ `typedef void (*VarPropertySerializer) (VarPropertySerialInfo&) ;` — typedef std::function<void(VarPropertySerialInfo&)>		VarPropertySerializer;
- L50 _public typedef_ `typedef TMap<FName, VarPropertySerializer> VarPropertySerializerMap;`
- L51 _public member_ `static VarPropertySerializerMap DefaultPropertySerializers;`
- L52 _public prototype_ `static void RegisterDefaultSerializers();`
- L53 _public prototype_ `static void RegisterVarPropertySerializer(FName CPPTypeName, VarPropertySerializer Serializer);`
- L54 _public prototype_ `static void UnregisterVarPropertySerializer(FName CPPTypeName);`
- L56 _public prototype_ `bool CopyGeneric(UTG_Expression* Owner, const FTG_Argument& Arg, bool CopyVarToProperty, int Index = -1);`
- L64 _public typedef_ `typedef TFunction<void(VarArchiveSerialInfo&)> VarArchiveSerializer;`
- L65 _public typedef_ `typedef TMap<FName, VarArchiveSerializer> VarArchiveSerializerMap;`
- L66 _public member_ `static VarArchiveSerializerMap DefaultArchiveSerializers;`
- L71 _public prototype_ `void Serialize(FArchive& Ar, FTG_Id PinId, const FTG_Argument& Argument);` — Serialize the var value Called from the Pin serialize()
- L74 _public member_ `FTG_Id PinId;` — `UPROPERTY(Transient)`
- L79 _public function_ `template <typename T_ValueType> static void FGeneric_Struct_Serializer(FTG_Var::VarPropertySerialInfo& Info)`
- L105 _public prototype_ `FTG_Var();`
- L106 _public prototype_ `FTG_Var(FTG_Id InPinUuid);`
- L107 _public prototype_ `FTG_Var(const FTG_Var& InVar);`
- L109 _public function_ `FTG_Var& operator = (const FTG_Var& InVar)`
- L111 _public function_ `void ShareData(const FTG_Var& InVar)`
- L116 _public function_ `FTG_Id GetId() const`
- L119 _public function_ `bool IsValid() const` — Check that the Var is valid meaning that it is correctly allocated in the Graph and reference its Pin Owner
- L122 _public function_ `bool IsEmpty() const` — Check if the Var has No Data allocated
- L123 _public function_ `bool IsArray() const`
- L124 _public function_ `void SetArray()`
- L126 _public function_ `FString LogValue() const`
- L128 _public function_ `void SetValueFromStr(FString StrVal)`
- L132 _public prototype_ `void CopyTo(UTG_Expression* Owner, FTG_Argument& Arg, int Index = -1);` — Manage data Arg provide the type name and rely on the VarAllocator map to create the concrete cpp type If Owner is provided then Var can be initialized from the matching owner's property if found
- L133 _public prototype_ `void CopyFrom(UTG_Expression* Owner, FTG_Argument& Arg, int Index = -1);`
- L135 _public prototype_ `void CopyTo(FTG_Var* InVar);`
- L136 _public prototype_ `void CopyFrom(FTG_Var* InVar);`
- L139 _public function_ `void Reset()` — Manage the Var Data with the knowledge of the Type
- L140 _public function_ `template <class T> void ResetAs() const`
- L141 _public function_ `template <class T> void ResetAs() const`
- L148 _public function_ `template <class T> T& GetAsWithDefault(T& Default)`
- L155 _public function_ `template <class T> void SetAs(const T& InValue)`
- L162 _public function_ `template <class T> T& EditAs()`
- L169 _public prototype_ `FString LogHead() const;`
- L218 _private member_ `mutable TSharedPtr<FConcept> Concept;`

#### struct `FTG_Var::VarPropertySerialInfo`  
`struct VarPropertySerialInfo`  
_L38-47_
- desc: Map of per type serializer for the var allowing to copy the value in the Var to a matching UObject's FProperty
- L40 _public member_ `FTG_Var* Var = nullptr;`
- L41 _public member_ `UObject* Owner = nullptr;`
- L42 _public member_ `FTG_Argument Arg;`
- L43 _public member_ `int32 Index = 0;`
- L44 _public member_ `bool CopyVarToProperty = false;`
- L46 _public function_ `FORCEINLINE int32 ClampedIndex() const`

#### struct `FTG_Var::VarArchiveSerialInfo`  
`struct VarArchiveSerialInfo`  
_L59-63_
- desc: Map of per type serializer for the var to/from an Archive
- L61 _public member_ `FTG_Var* Var = nullptr;`
- L62 _public member_ `FArchive& Ar;`

#### struct `FTG_Var::FConcept`  
`struct FConcept`  
_L173-182_
- L175 _public prototype_ `virtual ~FConcept() = default;`
- L177 _public prototype_ `virtual FString LogValue() = 0;`
- L178 _public prototype_ `virtual void SetValueFromString(const FString& String) = 0;`
- L179 _public prototype_ `virtual TSharedPtr<FConcept> Clone() = 0;`
- L180 _public prototype_ `virtual void SetArray() = 0;`
- L181 _public prototype_ `virtual bool IsArray() const = 0;`

#### struct `FTG_Var::FModel`  
`template <class T> struct FModel : public FConcept`  
_L185-216_
- inherits: `FConcept`
- L187 _public member_ `T Value;`
- L188 _public member_ `bool bIsArray = false;`
- L190 _public function_ `FString LogValue() override`
- L195 _public function_ `void SetValueFromString(const FString& StrValue) override`
- L200 _public function_ `TSharedPtr<FConcept> Clone() override`
- L208 _public function_ `virtual void SetArray()`
- L212 _public function_ `virtual bool IsArray() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L16 _function_ `template <typename T> void TG_Var_SetValueFromString(T& Value, const FString& StrVal)`
- L23 _function_ `template <typename T> FString TG_Var_LogValue(T& Value)`
- L221 _prototype_ `template <> FString TG_Var_LogValue(bool& Value);`
- L225 _prototype_ `template <> FString TG_Var_LogValue(int& Value);`
- L226 _prototype_ `template <> FString TG_Var_LogValue(float& Value);`
- L227 _prototype_ `template <> FString TG_Var_LogValue(uint8& Value);`
- L228 _prototype_ `template <> FString TG_Var_LogValue(FLinearColor& Value);`
- L229 _prototype_ `template <> FString TG_Var_LogValue(FVector4f& Value);`
- L230 _prototype_ `template <> FString TG_Var_LogValue(FVector2f& Value);`
- L231 _prototype_ `template <> FString TG_Var_LogValue(FName& Value);`
- L232 _prototype_ `template <> FString TG_Var_LogValue(FString& Value);`
- L233 _prototype_ `template <> FString TG_Var_LogValue(TObjectPtr<UObject>& Value);`
- L234 _prototype_ `template <> FString TG_Var_LogValue(struct FTG_Texture& Value);`
- L235 _prototype_ `template <> FString TG_Var_LogValue(struct FTG_Scalar& Value);`
- L236 _prototype_ `template <> FString TG_Var_LogValue(struct FTG_OutputSettings& Value);`
- L239 _prototype_ `template <> void TG_Var_SetValueFromString(int& Value, const FString& StrVal);`
- L243 _prototype_ `template <> void TG_Var_SetValueFromString(bool& Value, const FString& StrVal);`
- L245 _prototype_ `template <> void TG_Var_SetValueFromString(FLinearColor& Value, const FString& StrVal);`
- L249 _prototype_ `template <> void TG_Var_SetValueFromString(FVector4f& Value, const FString& StrVal);`
- L252 _prototype_ `template <> void TG_Var_SetValueFromString(struct FTG_Scalar& Value, const FString& StrVal);` — template <> UE_API void TG_Var_SetValueFromString(struct FTG_Texture& Value, const FString& StrVal);
- L256 _prototype_ `template <> void TG_Var_SetValueFromString(struct FTG_OutputSettings& Value, const FString& StrVal);`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TG_Variant.h` (Public)


#### enum `ETG_VariantType`  
`enum class ETG_VariantType : int8`  
_L19-26_
- reflection: `UENUM()`
- desc: Types of the variant are organized in increasing complexity, so a compatible type for 2 variants is always the highest
- L21 _public enumerator_ `Invalid = -1 UMETA(DisplayName = "Invalid")`
- L22 _public enumerator_ `Scalar = FTG_VariantInnerData::IndexOfType<float>() UMETA(DisplayName = "Scalar")`
- L23 _public enumerator_ `Color = FTG_VariantInnerData::IndexOfType<FLinearColor>() UMETA(DisplayName = "Color")`
- L24 _public enumerator_ `Vector = FTG_VariantInnerData::IndexOfType<FVector4f>() UMETA(DisplayName = "Vector")`
- L25 _public enumerator_ `Texture = FTG_VariantInnerData::IndexOfType<FTG_Texture>() UMETA(DisplayName = "Texture")`

#### struct `FTG_Variant`  
`struct FTG_Variant`  
_L33-173_
- reflection: `USTRUCT()`
- L38 _public typedef_ `using Variant = FTG_VariantInnerData;`
- L39 _public typedef_ `using EType = ETG_VariantType;`
- L41 _public prototype_ `FTG_Variant();`
- L42 _public prototype_ `FTG_Variant(const FTG_Variant& RHS);`
- L43 _public prototype_ `FTG_Variant(float RHS);`
- L44 _public prototype_ `FTG_Variant(FVector4f RHS);`
- L45 _public prototype_ `FTG_Variant(FLinearColor RHS);`
- L46 _public prototype_ `FTG_Variant(FTG_Texture RHS);`
- L48 _public prototype_ `FTG_Variant& operator = (const FTG_Variant& RHS);`
- L49 _public prototype_ `FTG_Variant& operator = (const float RHS);`
- L50 _public prototype_ `FTG_Variant& operator = (const FVector4f RHS);`
- L51 _public prototype_ `FTG_Variant& operator = (const FLinearColor RHS);`
- L52 _public prototype_ `FTG_Variant& operator = (const FTG_Texture RHS);`
- L53 _public prototype_ `bool operator == (const FTG_Variant& RHS) const;`
- L56 _public function_ `static FName GetNameFromType(ETG_VariantType InType)` — Retrieve the FName corresponding to a variant type
- L75 _public function_ `static FName GetArgNameFromType(ETG_VariantType InType)` — Retrieve the FName associated to a varaint type used for Arg cpoptypename
- L93 _public function_ `static ETG_VariantType GetTypeFromName(const FName& InTypeName)` — Retrieve the variant type value matching a FName Return Scalar if couldn't find a match
- L112 _public function_ `static bool IsScalar(EType InType)` — Predicates
- L113 _public function_ `static bool IsColor(EType InType)`
- L114 _public function_ `static bool IsVector(EType InType)`
- L115 _public function_ `static bool IsTexture(EType InType)`
- L116 _public function_ `static bool IsInvalid(EType InType)`
- L119 _public function_ `static EType WhichCommonType(EType T0, EType T1)` — Find the common type between 2
- L130 _public prototype_ `bool Serialize( FArchive& Ar );`
- L135 _public member_ `Variant Data;` — The concrete data
- L138 _public function_ `EType GetType() const` — Get the Type of the Variant, Scalar by default
- L143 _public prototype_ `bool ResetTypeAs(EType InType);` — Reset the Variant to the specified type, If the type is changed, the value is reset to 0 return true if the type as mutated
- L147 _public function_ `bool IsScalar() const` — Helper predicates to narrow down the type of the variant
- L148 _public function_ `bool IsColor() const`
- L149 _public function_ `bool IsVector() const`
- L150 _public function_ `bool IsTexture() const`
- L153 _public prototype_ `operator bool() const;`
- L157 _public prototype_ `const float& GetScalar() const;` — Getter and Editor The getter methods are valid ONLY if the type matches
- L158 _public prototype_ `const FLinearColor& GetColor() const;`
- L159 _public prototype_ `const FVector4f& GetVector() const;`
- L160 _public prototype_ `const FTG_Texture& GetTexture() const;`
- L161 _public prototype_ `FTG_Texture& GetTexture();`
- L163 _public prototype_ `FLinearColor GetColor(FLinearColor Default = FLinearColor::Black);`
- L164 _public prototype_ `FVector4f GetVector(FVector4f Default = FVector4f { 0, 0, 0, 0 });`
- L165 _public prototype_ `FTG_Texture GetTexture(FTG_EvaluationContext* InContext, FTG_Texture Default = { TextureHelper::GBlack }, const BufferDescriptor* DesiredDesc = nullptr);`
- L169 _public prototype_ `float& EditScalar();` — The editor methods are calling ResetTypeAs(expectedType) and thus the Variant will mutate to the expected type and assigned 0
- L170 _public prototype_ `FLinearColor& EditColor();`
- L171 _public prototype_ `FVector4f& EditVector();`
- L172 _public prototype_ `FTG_Texture& EditTexture();`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTG_Variant> : public TStructOpsTypeTraitsBase2<FTG_Variant>`  
_L176-185_
- inherits: `TStructOpsTypeTraitsBase2<FTG_Variant>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L180-184_

#### struct `FTG_VariantArray`  
`struct FTG_VariantArray`  
_L191-249_
- reflection: `USTRUCT()`
- L196 _private member_ `TArray<FTG_Variant> Array;` — An array of textures
- L197 _private member_ `int ViewIndex = 0;`
- L201 _public prototype_ `void SetNum(int Count);`
- L202 _public prototype_ `void Set(int Index, const FTG_Variant& Var);`
- L203 _public prototype_ `void Set(int Index, const FTG_Texture& Tex);`
- L204 _public prototype_ `void CopyFrom(const FTG_VariantArray& RHS);`
- L205 _public prototype_ `void SetViewIndex(int Index);`
- L207 _public function_ `FORCEINLINE bool IsTexture()`
- L212 _public function_ `FORCEINLINE int Num() const`
- L217 _public function_ `FORCEINLINE FTG_Variant& Get(int Index)`
- L223 _public function_ `FORCEINLINE const FTG_Variant& Get(int Index) const`
- L229 _public function_ `FORCEINLINE const TArray<FTG_Variant>& GetArray() const`
- L234 _public function_ `FORCEINLINE FTG_Texture* GetViewTexturePtr()`
- L242 _public function_ `FORCEINLINE FTG_Texture GetViewTexture() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L13 _typedef_ `using FTG_VariantInnerData = TVariant<float, FLinearColor, FVector4f, FTG_Texture>;` — Inner data type of the variant relies on the TVariant
- L27 _prototype_ `ENUM_RANGE_BY_FIRST_AND_LAST(ETG_VariantType, ETG_VariantType::Scalar, ETG_VariantType::Texture);`
- L126 _function_ `friend FArchive& operator<<(FArchive& Ar, FTG_Variant& D)`
- L181 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon759434be0103`)
- L182 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon759434be0103`)
- L183 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon759434be0103`)

### `Plugins/TextureGraph/Source/TextureGraph/Public/TextureGraph.h` (Public)


#### class `UTextureGraphBase`  
`class UTextureGraphBase : public UMixInterface`  
_L16-55_
- reflection: `UCLASS(abstract, BlueprintType, MinimalAPI)`
- inherits: `UMixInterface`
- L22 _protected prototype_ `EResolution GetMaxWidth();`
- L24 _protected prototype_ `EResolution GetMaxHeight();`
- L26 _protected prototype_ `int32 GetMaxBufferChannels();`
- L28 _protected prototype_ `BufferFormat GetMaxBufferFormat();`
- L31 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — Override Serialize method of UObject
- L34 _protected prototype_ `virtual void PostLoad() override;` — Override the PostLoad method of UObject to allocate settings
- L37 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — Override PreSave method of UObject
- L38 _protected prototype_ `void PostMeshLoad() override;`
- L41 _public function_ `virtual const UTG_Graph* Graph() const`
- L42 _public function_ `virtual UTG_Graph* Graph()`
- L45 _public prototype_ `virtual void Construct(FString Name);` — Construct the script giving it its name Initialize to a default one output script
- L47 _public prototype_ `void InvalidateAll() override;`
- L48 _public prototype_ `void Update(MixUpdateCyclePtr InCycle) override;`
- L49 _public function_ `virtual void Initialize()`
- L51 _public prototype_ `void TriggerUpdate(bool Tweaking);`
- L52 _public prototype_ `void FlushInvalidations();`
- L53 _public prototype_ `void UpdateGlobalTGSettings();`
- L54 _public prototype_ `void Log() const;`

#### class `UTextureGraph`  
`class UTextureGraph: public UTextureGraphBase`  
_L58-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UTextureGraphBase`
- L64 _public member_ `TObjectPtr<class UTG_Graph> TextureGraph;` — `UPROPERTY()`
- L67 _protected prototype_ `void GatherAllDependentGraphs(TArray<UTextureGraph*>& DependentGraphs) const;`
- L69 _protected prototype_ `bool CheckRecursiveDependency(const UTextureGraph* InTextureGraph) const;`
- L72 _public prototype_ `virtual void Construct(FString Name) override;`
- L73 _public function_ `virtual const UTG_Graph* Graph() const`
- L74 _public function_ `virtual UTG_Graph* Graph()`
- L75 _public prototype_ `bool IsDependentOn(const UTextureGraph* TextureGraph) const;`
- L76 _public prototype_ `bool HasCyclicDependency() const;`

#### class `UTextureGraphInstance`  
`class UTextureGraphInstance: public UTextureGraphBase`  
_L80-114_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UTextureGraphBase`
- L87 _private member_ `TObjectPtr<UTG_Graph> RuntimeGraph;` — `UPROPERTY(transient)` — The runtime graph instance to use for the sub-graph
- L91 _public member_ `FTG_VarMap InputParams;` — `UPROPERTY()`
- L94 _public member_ `TMap<FTG_Id, FTG_OutputSettings> OutputSettingsMap;` — `UPROPERTY()`
- L98 _public member_ `TObjectPtr<UTextureGraphBase> ParentTextureGraph;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TextureGraphInstance, AssetRegistrySearchable)` — Parent Texture Graph.
- L100 _public prototype_ `virtual void Construct(FString Name) override;`
- L102 _public prototype_ `void CopyParamsToRuntimeGraph();`
- L103 _public prototype_ `bool CheckOutputSettingsMatch(const TObjectPtr<UTextureGraphBase>& Parent) const;`
- L104 _public prototype_ `void UpdateOutputSettingsFromGraph();`
- L106 _public prototype_ `void SetParent(const TObjectPtr<UTextureGraphBase>& Parent);`
- L109 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — Override PreSave method of UObject
- L111 _public function_ `virtual const UTG_Graph* Graph() const override`
- L112 _public prototype_ `virtual UTG_Graph* Graph() override;`
- L113 _public prototype_ `virtual void Initialize() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREGRAPH_API`
- L13 _typedef_ `using ErrorReportMap = TMap<int32, TArray<FTextureGraphErrorReport>>;`

### `Plugins/TextureGraph/Source/TextureGraph/Public/TextureGraphModule.h` (Public)


#### class `FTextureGraphModule`  
`class FTextureGraphModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `void ShutdownModule() override;`
