# Plugins / BlueprintMaterialTextureNodes

- module root: `Plugins/Editor/BlueprintMaterialTextureNodes/Source/BlueprintMaterialTextureNodes`
- headers: 2; symbols: 18
- symbol kinds: class=2, macro=1, prototype=15
- PrivateDependencyModuleNames: Core, CoreUObject, ImageCore, RHI, UnrealEd
- PublicDependencyModuleNames: Engine

### `Plugins/Editor/BlueprintMaterialTextureNodes/Source/BlueprintMaterialTextureNodes/Public/BlueprintMaterialTextureNodes.h` (Public)


#### class `FBlueprintMaterialTextureNodesModule`  
`class FBlueprintMaterialTextureNodesModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/BlueprintMaterialTextureNodes/Source/BlueprintMaterialTextureNodes/Public/BlueprintMaterialTextureNodesBPLibrary.h` (Public)


#### class `UBlueprintMaterialTextureNodesBPLibrary`  
`class UBlueprintMaterialTextureNodesBPLibrary : public UBlueprintFunctionLibrary`  
_L34-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library class. Each function in it is expected to be static and represents blueprint node that can be called in any blueprint. When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable. BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins. BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins. DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu. Its lets you name the node using characters not allowed in C++ function names. CompactNodeTitle - the word(s) that appear on the node. Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. Good example is "Print String" node which you can find also by using keyword "log". Category -	the category your node will be under in the Blueprint drop-down menu. For more info on custom blueprint nodes visit documentation: https://docs.unrealengine.com/ProgrammingAndScripting/Blueprints/TechnicalGuide/ExtendingBlueprints
- L43 _private prototype_ `static FLinearColor Texture2D_SampleUV_EditorOnly(UTexture2D* Texture, FVector2D UV);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Texture2D Sample UV Editor Only", Keywords = "Read Texture UV"), Category = Rendering)` — Samples a texel from a Texture 2D with VectorDisplacement Compression
- L50 _private prototype_ `static TArray<FLinearColor> RenderTarget_SampleRectangle_EditorOnly(UTextureRenderTarget2D* InRenderTarget, FLinearColor InRect);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Render Target Sample Rectangle Editor Only", Keywords = "Sample Render Target Rectangle"), Category = Rendering)` — Samples an array of values from a Texture Render Target 2D. Currently only 4 channel formats are supported. Only works in the editor
- L57 _private prototype_ `static FLinearColor RenderTarget_SampleUV_EditorOnly(UTextureRenderTarget2D* InRenderTarget, FVector2D UV);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Render Target Sample UV Editor Only", Keywords = "Sample Render Target UV"), Category = Rendering)` — Samples a value from a Texture Render Target 2D. Currently only 4 channel formats are supported. Only works in the editor
- L65 _private prototype_ `static UMaterialInstanceConstant* CreateMIC_EditorOnly(UMaterialInterface* Material, FString Name = "MIC` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create MIC Editor Only", Keywords = "Create MIC", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Creates a new Material Instance Constant asset Only works in the editor
- L68 _private prototype_ `static void UpdateMIC(UMaterialInstanceConstant* MIC);` — `UFUNCTION()`
- L75 _private prototype_ `static bool SetMICScalarParam_EditorOnly(UMaterialInstanceConstant* Material, FString ParamName = "test", float Value = 0.` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Scalar Parameter Editor Only", Keywords = "Set MIC Scalar Parameter", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Sets a Scalar Parameter value in a Material Instance Constant Only works in the editor
- L82 _private prototype_ `static bool SetMICVectorParam_EditorOnly(UMaterialInstanceConstant* Material, FString ParamName, FLinearColor Value = FLinearColor(0, 0, 0, 0));` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Vector Parameter Editor Only", Keywords = "Set MIC Vector Parameter", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Sets a Vector Parameter value in a Material Instance Constant Only works in the editor
- L89 _private prototype_ `static bool SetMICTextureParam_EditorOnly(UMaterialInstanceConstant* Material, FString ParamName, UTexture2D* Texture = nullptr);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Texture Parameter Editor Only", Keywords = "Set MIC Texture Parameter", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Sets a Texture Parameter value in a Material Instance Constant Only works in the editor
- L96 _private prototype_ `static bool SetMICShadingModel_EditorOnly(UMaterialInstanceConstant* Material, TEnumAsByte<EMaterialShadingModel> ShadingModel = MSM_DefaultLit);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Shading Model Editor Only", Keywords = "Set MIC Shading Model", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overrides the Shading Model of a Material Instance Constant Only works in the editor
- L103 _private prototype_ `static bool SetMICBlendMode_EditorOnly(UMaterialInstanceConstant* Material, TEnumAsByte<EBlendMode> BlendMode = BLEND_Opaque);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Blend Mode Editor Only", Keywords = "Set MIC Blend Mode", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overrides the Blend Mode of a Material Instance Constant Only works in the editor
- L110 _private prototype_ `static bool SetMICTwoSided_EditorOnly(UMaterialInstanceConstant* Material, bool TwoSided = false);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Two Sided Editor Only", Keywords = "Set MIC Two Sided", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overrides the Two Sided setting of a Material Instance Constant Only works in the editor
- L117 _private prototype_ `static bool SetMICIsThinSurface_EditorOnly(UMaterialInstanceConstant* Material, bool bIsThinSurface = false);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC IsThinSurface Editor Only", Keywords = "Set MIC IsThinSurface", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overrides the IsThinSurface setting of a Material Instance Constant Only works in the editor
- L124 _private prototype_ `static bool SetMICDitheredLODTransition_EditorOnly(UMaterialInstanceConstant* Material, bool DitheredLODTransition = false);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set MIC Dithered LOD Editor Only", Keywords = "Set MIC Dithered LOD Transition", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overrides the Blend Mode of a Material Instance Constant Only works in the editor

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BLUEPRINTMATERIALTEXTURENODES_API`
