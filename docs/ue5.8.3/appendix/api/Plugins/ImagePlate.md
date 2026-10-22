# Plugins / ImagePlate

- module root: `Plugins/Experimental/ImagePlate/Source/ImagePlate`
- headers: 4; symbols: 75
- symbol kinds: class=5, function=7, macro=3, member=23, namespace=1, prototype=33, struct=3
- PrivateDependencyModuleNames: ImageCore, ImageWrapper, MediaAssets, RHI, RenderCore, SlateCore, TimeManagement
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/ImagePlate/Source/ImagePlate/Private/ImagePlateFrustumComponent.h` (Private)


#### class `UImagePlateFrustumComponent`  
`class UImagePlateFrustumComponent : public UPrimitiveComponent`  
_L13-24_
- reflection: `UCLASS(MinimalAPI, ClassGroup=Rendering, hidecategories=(Object,Activation,Collision,"Components|Activation",Physics), editinlinenew)`
- inherits: `UPrimitiveComponent`
- desc: A 2d material that will be rendered always facing the camera.
- L18 _public prototype_ `UImagePlateFrustumComponent(const FObjectInitializer& Init);`
- L21 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L22 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L23 _public function_ `virtual bool ShouldRecreateProxyOnUpdateTransform() const override`

### `Plugins/Experimental/ImagePlate/Source/ImagePlate/Public/ImagePlate.h` (Public)


#### class `AImagePlate`  
`class AImagePlate : public AActor`  
_L13-29_
- reflection: `UCLASS(MinimalAPI, ClassGroup=Rendering, hidecategories=(Object,Activation,Physics,Collision,Input,PhysicsVolume))`
- inherits: `AActor`
- L18 _public prototype_ `AImagePlate(const FObjectInitializer& Init);`
- L20 _public function_ `UImagePlateComponent* GetImagePlateComponent() const`
- L28 _protected member_ `TObjectPtr<UImagePlateComponent> ImagePlate;` — `UPROPERTY(Category=ImagePlate, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories="Mesh,Rendering,Physics,Components|StaticMesh"))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IMAGEPLATE_API`

### `Plugins/Experimental/ImagePlate/Source/ImagePlate/Public/ImagePlateComponent.h` (Public)


#### struct `FImagePlateParameters`  
`struct FImagePlateParameters`  
_L19-52_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public prototype_ `FImagePlateParameters();`
- L27 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category="Image Plate")` — The material that the image plate is rendered with.
- L31 _public member_ `FName TextureParameterName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category="Image Plate")` — Name of a texture parameter inside the material to patch the render target texture to
- L35 _public member_ `bool bFillScreen;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image Plate")` — Automatically size the plate based on the active camera's lens and filmback settings. Target Camera is found by looking for an active camera component from this component's actor, through its attached parents.
- L39 _public member_ `FVector2D FillScreenAmount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image Plate", meta=(EditCondition="bFillScreen", AllowPreserveRatio))` — The amount to fill the screen with when attached to a camera
- L43 _public member_ `FVector2D FixedSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image Plate", meta=(EditCondition="!bFillScreen"))` — The fixed size of the image plate
- L47 _public member_ `TObjectPtr<UTexture> RenderTexture;` — `UPROPERTY(transient, BlueprintReadOnly, Category="Image Plate")` — Transient texture that receives image frames
- L51 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — `UPROPERTY(transient)` — Transient MID to hold the material with the render texture patched in

#### class `UImagePlateComponent`  
`class UImagePlateComponent : public UPrimitiveComponent`  
_L58-149_
- reflection: `UCLASS(MinimalAPI, ClassGroup=Rendering, hidecategories=(Object,Activation,Collision,"Components|Activation",Physics), editinlinenew, meta=(BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- desc: A 2d plate that will be rendered always facing the camera.
- L63 _public prototype_ `UImagePlateComponent(const FObjectInitializer& Init);`
- L65 _public function_ `static inline FVector TransfromFromProjection(const FMatrix& Matrix, const FVector4& InVector)`
- L79 _public prototype_ `void SetImagePlate(FImagePlateParameters Plate);` — `UFUNCTION(BlueprintCallable, Category="Game|Image Plate")` — Add an image plate to this actor
- L83 _public function_ `FImagePlateParameters GetPlate() const` — `UFUNCTION(BlueprintCallable, Category="Game|Image Plate")` — Get this actor's image plates
- L90 _public prototype_ `void OnRenderTextureChanged();` — `UFUNCTION()` — Called by sequencer if a texture is changed
- L93 _public function_ `const FMatrix& GetCachedViewProjectionMatrix() const` — Access this component's cached view projection matrix. Only valid when the plate is set to fill screen
- L99 _public function_ `const FMatrix& GetCachedInvViewProjectionMatrix() const` — Access this component's cached inverse view projection matrix. Only valid when the plate is set to fill screen
- L105 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L106 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L107 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;`
- L108 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L109 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 Index) const override;`
- L110 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const override;`
- L111 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;`
- L112 _public prototype_ `virtual void OnRegister() override;`
- L114 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L115 _public prototype_ `virtual void PostEditUndo() override;`
- L120 _public prototype_ `static FStructProperty* GetImagePlateProperty();` — Access the property relating to this component's image plate
- L126 _public prototype_ `AActor* FindViewTarget() const;` — Finds a view target that this image plate is presenting to
- L130 _protected prototype_ `void UpdateMaterialParametersForMedia();`
- L132 _protected prototype_ `void UpdateTransformScale();`
- L138 _private member_ `FImagePlateParameters Plate;` — `UPROPERTY(EditAnywhere, Category="Image Plate", DisplayName="Image Plates", meta=(ShowOnlyInnerProperties))` — Array of image plates to render for this component
- L140 _private member_ `FMatrix ViewProjectionMatrix;`
- L141 _private member_ `FMatrix InvViewProjectionMatrix;`
- L143 _private member_ `bool bReenetrantTranformChange;`
- L147 _private member_ `TObjectPtr<UImagePlateFrustumComponent> EditorFrustum;` — `UPROPERTY(transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IMAGEPLATE_API`

### `Plugins/Experimental/ImagePlate/Source/ImagePlate/Public/ImagePlateFileSequence.h` (Public)


#### class `UImagePlateSettings`  
`class UImagePlateSettings : public UObject`  
_L22-30_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the ImagePlate plugin.
- L29 _public member_ `FString ProxyName;` — `UPROPERTY(GlobalConfig, EditAnywhere, config, Category=Settings)` — Specifies a sub-directory to append to any image plate file sequences

#### class `UImagePlateFileSequence`  
`class UImagePlateFileSequence : public UObject`  
_L34-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L39 _public prototype_ `UImagePlateFileSequence(const FObjectInitializer& Init);`
- L43 _public member_ `FDirectoryPath SequencePath;` — `UPROPERTY(EditAnywhere, Category="General", meta=(ContentDir))` — Path to the directory in which the image sequence resides
- L47 _public member_ `FString FileWildcard;` — `UPROPERTY(EditAnywhere, Category="General")` — Wildcard used to find images within the directory (ie *.exr)
- L51 _public member_ `float Framerate;` — `UPROPERTY(EditAnywhere, Category="General", meta=(ClampMin=0))` — Framerate at which to display the images
- L56 _public prototype_ `FImagePlateAsyncCache GetAsyncCache();` — Create a new image cache for this sequence

#### struct `FImagePlateSourceFrame`  
`struct FImagePlateSourceFrame`  
_L60-86_
- desc: Uncompressed source data for a single frame of a sequence
- L63 _public prototype_ `FImagePlateSourceFrame();` — Default constructor
- L65 _public prototype_ `FImagePlateSourceFrame(const TArray64<uint8>& InData, uint32 InWidth, uint32 InHeight, uint32 InBitDepth);` — Construction from an array of data, and a given width/height/bitdepth
- L68 _public prototype_ `bool IsValid() const;` — Check whether this source frame has valid data
- L71 _public prototype_ `TFuture<void> CopyTo(UTexture* DestinationTexture);` — Copy the contents of this frame to the specified texture
- L74 _public prototype_ `TSharedRef<FSlateTextureData, ESPMode::ThreadSafe> AsSlateTexture() const;` — Copy this source frame into a slate texture data format
- L79 _private prototype_ `bool EnsureTextureMetrics(UTexture* DestinationTexture) const;` — Ensure the specified texture metrics match this frame
- L82 _private member_ `uint32 Width, Height, BitDepth, Pitch;` — Metrics for the texture
- L82 _private member_ `uint32 Width, Height, BitDepth, Pitch;` — Metrics for the texture
- L82 _private member_ `uint32 Width, Height, BitDepth, Pitch;` — Metrics for the texture
- L82 _private member_ `uint32 Width, Height, BitDepth, Pitch;` — Metrics for the texture
- L85 _private member_ `TSharedPtr<uint8, ESPMode::ThreadSafe> Buffer;` — Threadsafe, shared data buffer. Shared so that this type can be copied around without incurring a copy-cost for large frames.

#### struct `FImagePlateAsyncCache`  
`struct FImagePlateAsyncCache`  
_L89-106_
- desc: A wrapper for an asynchronous cache of image frames
- L92 _public prototype_ `static FImagePlateAsyncCache MakeCache(const FString& InSequencePath, const FString& InWildcard, float Framerate);` — Make a new cache for the specified folder, wildcard and framerate
- L96 _public prototype_ `TSharedFuture<FImagePlateSourceFrame> RequestFrame(float Time, int32 LeadingPrecacheFrames, int32 TrailingPrecacheFrames);` — @todo: sequencer-timecode: frame accuracy
- L99 _public prototype_ `int32 Length() const;` — Get the length of the sequence in frames
- L102 _private function_ `FImagePlateAsyncCache()`
- L105 _private member_ `TSharedPtr<ImagePlateFrameCache::FImagePlateSequenceCache, ESPMode::ThreadSafe> Impl;` — Shared implementation

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API IMAGEPLATE_API`
- L16 _namespace_ `namespace ImagePlateFrameCache`
