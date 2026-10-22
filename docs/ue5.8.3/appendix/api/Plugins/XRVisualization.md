# Plugins / XRVisualization

- module root: `Plugins/Runtime/XR/XRVisualization/Source/XRVisualization`
- headers: 2; symbols: 17
- symbol kinds: class=2, delegate=1, member=5, prototype=9
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, EngineSettings, HeadMountedDisplay, ProceduralMeshComponent, RHI, RenderCore, XRBase

### `Plugins/Runtime/XR/XRVisualization/Source/XRVisualization/Private/XRVisualizationModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRVisual, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRVisual, Log, All);`

### `Plugins/Runtime/XR/XRVisualization/Source/XRVisualization/Public/XRVisualizationFunctionLibrary.h` (Public)


#### class `UXRVisualizationLoadHelper`  
`class UXRVisualizationLoadHelper : public UObject`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _private prototype_ `UXRVisualizationLoadHelper(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());` — UObject constructor that takes an optional ObjectInitializer
- L21 _public member_ `TObjectPtr<class UStaticMesh> GenericHMD;` — `UPROPERTY()`
- L23 _public member_ `TObjectPtr<class UStaticMesh> OculusControllerMesh;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<class UStaticMesh> ViveControllerMesh;` — `UPROPERTY()`
- L27 _public member_ `TObjectPtr<class UStaticMesh> STEMControllerMesh;` — `UPROPERTY()`

#### class `UXRVisualizationFunctionLibrary`  
`class UXRVisualizationFunctionLibrary : public UBlueprintFunctionLibrary`  
_L31-65_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L35 _private prototype_ `virtual ~UXRVisualizationFunctionLibrary();`
- L43 _public prototype_ `static void RenderHMD(const FXRHMDData& XRHMDData);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Renders HMD Visualization on a system that might not have that HMD as native
- L49 _public prototype_ `static void RenderMotionController2(const FXRMotionControllerState& XRControllerState);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Renders Motion Controller Visualization on a system that might not have that HMD as native
- L54 _public prototype_ `static void RenderHandTracking(const FXRHandTrackingState& XRHandTrackingState);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Renders Motion Controller Visualization on a system that might not have that HMD as native
- L57 _private prototype_ `void VerifyInitMeshes();`
- L59 _private prototype_ `static void RenderGenericMesh(const FName& ActorName, UStaticMesh* Mesh, FTransform& WorldTransform);`
- L61 _private prototype_ `static void RenderFinger(const FXRHandTrackingState& XRHandTrackingState, int32 FingerStart, int32 FingerEnd);`
- L64 _private member_ `TObjectPtr<UXRVisualizationLoadHelper> LoadHelper;` — `UPROPERTY()`
