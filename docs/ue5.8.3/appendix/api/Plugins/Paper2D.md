# Plugins / Paper2D

- module root: `Plugins/2D/Paper2D/Source/Paper2D`
- headers: 37; symbols: 983
- symbol kinds: class=33, delegate=4, enum=9, enumerator=54, externvar=3, function=146, macro=25, member=309, namespace=7, prototype=368, struct=22, typedef=3
- PrivateDependencyModuleNames: EditorFramework, Renderer, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, NavigationSystem, RHI, RenderCore, Slate, SlateCore

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/IntMargin.h` (Public)


#### struct `FIntMargin`  
`struct FIntMargin`  
_L11-126_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes the space around a 2D area on an integer grid.
- L17 _public member_ `int32 Left;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — Holds the margin to the left.
- L21 _public member_ `int32 Top;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — Holds the margin to the top.
- L25 _public member_ `int32 Right;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — Holds the margin to the right.
- L29 _public member_ `int32 Bottom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — Holds the margin to the bottom.
- L38 _public function_ `FIntMargin( ) : Left(0) , Top(0) , Right(0) , Bottom(0)` — Default constructor. The default margin size is zero on all four sides..
- L46 _public function_ `FIntMargin(int32 UniformMargin) : Left(UniformMargin) , Top(UniformMargin) , Right(UniformMargin) , Bottom(UniformMargin)` — Construct a Margin with uniform space on all sides
- L54 _public function_ `FIntMargin(int32 Horizontal, int32 Vertical) : Left(Horizontal) , Top(Vertical) , Right(Horizontal) , Bottom(Vertical)` — Construct a Margin where Horizontal describes Left and Right spacing while Vertical describes Top and Bottom spacing
- L62 _public function_ `FIntMargin(int32 InLeft, int32 InTop, int32 InRight, int32 InBottom) : Left(InLeft) , Top(InTop) , Right(InRight) , Bottom(InBottom)` — Construct a Margin where the spacing on each side is individually specified.
- L77 _public function_ `FIntMargin operator+(const FIntMargin& InDelta) const` — Adds another margin to this margin. @param Other The margin to add. @return A margin that represents this margin plus the other margin.
- L88 _public function_ `FIntMargin operator-(const FIntMargin& Other) const` — Subtracts another margin from this margin. @param Other The margin to subtract. @return A margin that represents this margin minus the other margin.
- L99 _public function_ `bool operator==(const FIntMargin& Other) const` — Compares this margin with another for equality. @param Other The other margin. @return true if the two margins are equal, false otherwise.
- L110 _public function_ `bool operator!=(const FIntMargin& Other) const` — Compares this margin with another for inequality. @param Other The other margin. @return true if the two margins are not equal, false otherwise.
- L122 _public function_ `FIntPoint GetDesiredSize() const` — Gets the margin's total size. @return Cumulative margin size.

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperCharacter.h` (Public)


#### class `APaperCharacter`  
`class APaperCharacter : public ACharacter`  
_L15-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ACharacter`
- desc: APaperCharacter behaves like ACharacter, but uses a UPaperFlipbookComponent instead of a USkeletalMeshComponent as a visual representation Note: The variable named Mesh will not be set up on this actor!
- L20 _private member_ `static FName SpriteComponentName;` — Name of the Sprite component
- L25 _private member_ `TObjectPtr<class UPaperFlipbookComponent> Sprite;` — `UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))` — The main skeletal mesh associated with this Character (optional sub-object).
- L28 _public prototype_ `virtual void PostInitializeComponents() override;`
- L31 _public function_ `FORCEINLINE class UPaperFlipbookComponent* GetSprite() const` — Returns Sprite subobject

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbook.h` (Public)


#### struct `FPaperFlipbookKeyFrame`  
`struct FPaperFlipbookKeyFrame`  
_L16-32_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<UPaperSprite> Sprite;` — `UPROPERTY(Category=Sprite, EditAnywhere)`
- L25 _public member_ `int32 FrameRun;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta=(ClampMin=1))`
- L27 _public function_ `FPaperFlipbookKeyFrame() : Sprite(nullptr) , FrameRun(1)`

#### enum `EFlipbookCollisionMode::Type`  
`enum Type : int`  
_L37-47_
- L40 _public enumerator_ `NoCollision` — The flipbook has no collision
- L43 _public enumerator_ `FirstFrameCollision` — The flipbook has non-animated collision based on the first frame of the animation
- L46 _public enumerator_ `EachFrameCollision` — The flipbook changes collision each frame based on the animation (Note: This setting is not recommended and is very expensive, recreating the physics state every frame)

#### class `UPaperFlipbook`  
`class UPaperFlipbook : public UObject`  
_L54-158_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayThumbnail = "true"))`
- inherits: `UObject`
- desc: Contains an animation sequence of sprite frames
- L61 _protected member_ `float FramesPerSecond;` — `UPROPERTY(Category=Sprite, EditAnywhere, BlueprintReadOnly, meta=(ClampMin=0, ClampMax=1000))` — The nominal frame rate to play this flipbook animation back at
- L65 _protected member_ `TArray<FPaperFlipbookKeyFrame> KeyFrames;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — The set of key frames for this flipbook animation (each one has a duration and a sprite to display)
- L69 _protected member_ `TObjectPtr<UMaterialInterface> DefaultMaterial;` — `UPROPERTY(Category=Sprite, EditAnywhere, BlueprintReadOnly)` — The material to use on a flipbook player instance if not overridden
- L73 _protected member_ `TEnumAsByte<EFlipbookCollisionMode::Type> CollisionSource;` — `UPROPERTY(Category=Sprite, EditAnywhere, BlueprintReadOnly)` — Collision source
- L77 _public function_ `TEnumAsByte<EFlipbookCollisionMode::Type> GetCollisionSource() const` — Returns the collision source of this flipbook animation (if any)
- L80 _public prototype_ `float GetFramesPerSecond() const;` — Returns the nominal frame rate to play this flipbook animation back at
- L84 _public prototype_ `int32 GetNumFrames() const;` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the total number of frames
- L88 _public prototype_ `float GetTotalDuration() const;` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the total duration in seconds
- L93 _public prototype_ `int32 GetKeyFrameIndexAtTime(float Time, bool bClampToEnds = false) const;` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the keyframe index that covers the specified time (in seconds), or INDEX_NONE if none exists. When bClampToEnds is true, it will choose the first or last keyframe if the time is out of range.
- L98 _public prototype_ `UPaperSprite* GetSpriteAtTime(float Time, bool bClampToEnds = false) const;` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the sprite at the specified time (in seconds), or nullptr if none exists. When bClampToEnds is true, it will choose the first or last sprite if the time is out of range.
- L102 _public prototype_ `UPaperSprite* GetSpriteAtFrame(int32 FrameIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the sprite at the specified keyframe index, or nullptr if none exists
- L105 _public prototype_ `FBoxSphereBounds GetRenderBounds() const;` — Returns the render bounds of this sprite
- L109 _public function_ `int32 GetNumKeyFrames() const` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the number of key frames
- L116 _public function_ `bool IsValidKeyFrameIndex(int32 Index) const` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Is the specified Index within the valid range of key frames?
- L122 _public function_ `const FPaperFlipbookKeyFrame& GetKeyFrameChecked(int32 Index) const` — Returns the key frame at the specified index, make sure the index is valid before use
- L128 _public prototype_ `bool FindSocket(FName SocketName, int32 KeyFrameIndex, FTransform& OutLocalTransform);` — Search for a socket at the specified frame
- L131 _public prototype_ `bool HasAnySockets() const;` — Returns true if the flipbook has any sockets
- L134 _public prototype_ `bool DoesSocketExist(FName SocketName) const;` — Returns true if the flipbook has a specific named socket
- L137 _public prototype_ `void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const;` — Returns a list of all of the sockets
- L140 _public function_ `UMaterialInterface* GetDefaultMaterial() const` — Return the default material for this flipbook
- L143 _public prototype_ `void InvalidateCachedData();` — Rebuilds cached data about the animation (such as total number of frames that the keyframes span, etc...)
- L146 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L147 _public prototype_ `virtual void PostLoad() override;`
- L149 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L154 _public prototype_ `bool ContainsSprite(UPaperSprite* SpriteAsset) const;` — Returns true if the flipbook asset contains the specified sprite asset in any frames

#### class `FScopedFlipbookMutator`  
`class FScopedFlipbookMutator`  
_L162-193_
- desc: Helper class to edit properties of a UPaperFlipbook while ensuring that cached data remains up to date
- L165 _public member_ `float& FramesPerSecond;`
- L166 _public member_ `TArray<FPaperFlipbookKeyFrame>& KeyFrames;`
- L169 _private member_ `UPaperFlipbook* SourceFlipbook;`
- L172 _public function_ `FScopedFlipbookMutator(UPaperFlipbook* InFlipbook) : FramesPerSecond(InFlipbook->FramesPerSecond) , KeyFrames(InFlipbook->KeyFrames) , SourceFlipbook(InFlipbook)`
- L179 _public function_ `~FScopedFlipbookMutator()`
- L184 _public function_ `void InvalidateCachedData()`
- L189 _public function_ `UPaperFlipbook* GetSourceFlipbook() const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PAPER2D_API`
- L35 _namespace_ `namespace EFlipbookCollisionMode`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookActor.h` (Public)


#### class `APaperFlipbookActor`  
`class APaperFlipbookActor : public AActor`  
_L19-37_
- reflection: `UCLASS(MinimalAPI, ComponentWrapperClass)`
- inherits: `AActor`
- desc: An instance of a UPaperFlipbook in a level. This actor is created when you drag a flipbook asset from the content browser into the level, and it is just a thin wrapper around a UPaperFlipbookComponent that actually references the asset.
- L25 _private member_ `TObjectPtr<class UPaperFlipbookComponent> RenderComponent;` — `UPROPERTY(Category=Sprite, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories="Sprite,Rendering,Physics,Components|Flipbook", AllowPrivateAccess="true"))`
- L31 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L36 _public function_ `FORCEINLINE class UPaperFlipbookComponent* GetRenderComponent() const` — Returns RenderComponent subobject

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookComponent.h` (Public)


#### class `UPaperFlipbookComponent`  
`class UPaperFlipbookComponent : public UMeshComponent`  
_L24-216_
- reflection: `UCLASS(MinimalAPI, ShowCategories=(Mobility, ComponentReplication), ClassGroup=Paper2D, meta=(BlueprintSpawnableComponent))`
- inherits: `UMeshComponent`
- L31 _protected member_ `TObjectPtr<UPaperFlipbook> SourceFlipbook;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta=(DisplayThumbnail = "true"), ReplicatedUsing=OnRep_SourceFlipbook)` — Flipbook currently being played
- L35 _protected member_ `TObjectPtr<UMaterialInterface> Material_DEPRECATED;` — `UPROPERTY()` — DEPRECATED in 4.5: The material override for this flipbook component (if any); replaced by the Materials array inherited from UMeshComponent
- L39 _protected member_ `float PlayRate;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Current play rate of the flipbook
- L43 _protected member_ `uint32 bLooping:1;` — `UPROPERTY()` — Whether the flipbook should loop when it reaches the end, or stop
- L47 _protected member_ `uint32 bReversePlayback:1;` — `UPROPERTY()` — If playback should move the current position backwards instead of forwards
- L51 _protected member_ `uint32 bPlaying:1;` — `UPROPERTY()` — Are we currently playing (moving Position)
- L55 _protected member_ `float AccumulatedTime;` — `UPROPERTY()` — Current position in the timeline
- L59 _protected member_ `int32 CachedFrameIndex;` — `UPROPERTY()` — Last frame index calculated
- L63 _protected member_ `FLinearColor SpriteColor;` — `UPROPERTY(BlueprintReadOnly, Interp, Category=Sprite)` — Vertex color to apply to the frames
- L67 _protected member_ `TObjectPtr<UBodySetup> CachedBodySetup;` — `UPROPERTY(Transient)` — The cached body setup
- L72 _public member_ `FFlipbookFinishedPlaySignature OnFinishedPlaying;` — `UPROPERTY(BlueprintAssignable)` — Event called whenever a non-looping flipbook finishes playing (either reaching the beginning or the end, depending on the play direction)
- L77 _public prototype_ `virtual bool SetFlipbook(class UPaperFlipbook* NewFlipbook);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Change the flipbook used by this instance (will reset the play time to 0 if it is a new flipbook).
- L81 _public prototype_ `virtual UPaperFlipbook* GetFlipbook();` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Gets the flipbook used by this instance.
- L85 _public function_ `FLinearColor GetSpriteColor() const` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Returns the current color of the sprite
- L89 _public prototype_ `void SetSpriteColor(FLinearColor NewColor);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Set color of the sprite
- L93 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Start playback of flipbook
- L97 _public prototype_ `void PlayFromStart();` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Start playback of flipbook from the start
- L101 _public prototype_ `void Reverse();` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Start playback of flipbook in reverse
- L105 _public prototype_ `void ReverseFromEnd();` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Start playback of flipbook in reverse from the end
- L109 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Stop playback of flipbook
- L113 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get whether this flipbook is playing or not.
- L117 _public prototype_ `bool IsReversing() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get whether we are reversing or not
- L121 _public prototype_ `void SetPlaybackPositionInFrames(int32 NewFramePosition, bool bFireEvents);` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Jump to a position in the flipbook (expressed in frames). If bFireEvents is true, event functions will fire, otherwise they will not.
- L125 _public prototype_ `int32 GetPlaybackPositionInFrames() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get the current playback position (in frames) of the flipbook
- L129 _public prototype_ `void SetPlaybackPosition(float NewPosition, bool bFireEvents);` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Jump to a position in the flipbook (expressed in seconds). If bFireEvents is true, event functions will fire, otherwise they will not.
- L133 _public prototype_ `float GetPlaybackPosition() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get the current playback position (in seconds) of the flipbook
- L137 _public prototype_ `void SetLooping(bool bNewLooping);` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — true means we should loop, false means we should not.
- L141 _public prototype_ `bool IsLooping() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get whether we are looping or not
- L145 _public prototype_ `void SetPlayRate(float NewRate);` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Sets the new play rate for this flipbook
- L149 _public prototype_ `float GetPlayRate() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get the current play rate for this flipbook
- L153 _public prototype_ `void SetNewTime(float NewTime);` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Set the new playback position time to use
- L157 _public prototype_ `float GetFlipbookLength() const;` — `UFUNCTION(BlueprintCallable, Category="Components|Flipbook")` — Get length of the flipbook (in seconds)
- L161 _public prototype_ `int32 GetFlipbookLengthInFrames() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|Flipbook")` — Get length of the flipbook (in frames)
- L165 _public prototype_ `float GetFlipbookFramerate() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|Flipbook")` — Get the nominal framerate that the flipbook will be played back at (ignoring PlayRate), in frames per second
- L169 _protected prototype_ `void OnRep_SourceFlipbook(class UPaperFlipbook* OldFlipbook);` — `UFUNCTION()`
- L171 _protected prototype_ `void CalculateCurrentFrame();`
- L172 _protected prototype_ `UPaperSprite* GetSpriteAtCachedIndex() const;`
- L174 _protected prototype_ `void TickFlipbook(float DeltaTime);`
- L175 _protected prototype_ `void FlipbookChangedPhysicsState();`
- L179 _private function_ `void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override` — disable parallel add to scene for paper2d
- L186 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L187 _public prototype_ `virtual void PostLoad() override;`
- L191 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — UActorComponent interface
- L192 _public prototype_ `virtual void SendRenderDynamicData_Concurrent() override;`
- L193 _public prototype_ `virtual const UObject* AdditionalStatObject() const override;`
- L195 _public prototype_ `virtual void CheckForErrors() override;`
- L200 _public prototype_ `virtual bool HasAnySockets() const override;` — USceneComponent interface
- L201 _public prototype_ `virtual bool DoesSocketExist(FName InSocketName) const override;`
- L202 _public prototype_ `virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;`
- L203 _public prototype_ `virtual void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const override;`
- L207 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L208 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L209 _public prototype_ `virtual void GetUsedTextures(TArray<UTexture*>& OutTextures, EMaterialQualityLevel::Type QualityLevel) override;`
- L210 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L211 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L212 _public prototype_ `virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingTextures) const override;`
- L213 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L214 _public prototype_ `virtual UBodySetup* GetBodySetup() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFlipbookFinishedPlaySignature);` — Event for a non-looping flipbook finishing play
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFlipbookFinishedPlaySignature);` — Event for a non-looping flipbook finishing play

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperGroupedSpriteActor.h` (Public)


#### class `APaperGroupedSpriteActor`  
`class APaperGroupedSpriteActor : public AActor`  
_L19-36_
- reflection: `UCLASS(MinimalAPI, ComponentWrapperClass)`
- inherits: `AActor`
- desc: A group of sprites that will be rendered and culled as a single unit This actor is created when you Merge several sprite components together. it is just a thin wrapper around a UPaperGroupedSpriteComponent.
- L25 _private member_ `TObjectPtr<UPaperGroupedSpriteComponent> RenderComponent;` — `UPROPERTY(Category=Sprite, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories = "Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess="true"))`
- L30 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L35 _public function_ `FORCEINLINE UPaperGroupedSpriteComponent* GetRenderComponent() const` — Returns RenderComponent subobject

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperGroupedSpriteComponent.h` (Public)


#### struct `FSpriteInstanceData`  
`struct FSpriteInstanceData`  
_L19-49_
- reflection: `USTRUCT()`
- L25 _public member_ `FMatrix Transform;` — `UPROPERTY(EditAnywhere, Category=Instances)`
- L28 _public member_ `TObjectPtr<UPaperSprite> SourceSprite;` — `UPROPERTY(EditAnywhere, Category=Instances)`
- L31 _public member_ `FColor VertexColor;` — `UPROPERTY(EditAnywhere, Category=Instances)`
- L34 _public member_ `int32 MaterialIndex;` — `UPROPERTY(EditAnywhere, Category=Instances)`
- L36 _public function_ `bool IsValidInstance() const`
- L42 _public function_ `FSpriteInstanceData() : Transform(FMatrix::Identity) , SourceSprite(nullptr) , VertexColor(FColor::White) , MaterialIndex(INDEX_NONE)`

#### class `UPaperGroupedSpriteComponent`  
`class UPaperGroupedSpriteComponent : public UMeshComponent`  
_L58-186_
- reflection: `UCLASS(MinimalAPI, ShowCategories=(Mobility), ClassGroup=Paper2D, meta=(BlueprintSpawnableComponent), EarlyAccessPreview)`
- inherits: `UMeshComponent`
- L65 _protected member_ `TArray<TObjectPtr<UMaterialInterface>> InstanceMaterials;` — `UPROPERTY()` — Array of materials used by the instances
- L69 _protected member_ `TArray<FSpriteInstanceData> PerInstanceSpriteData;` — `UPROPERTY(EditAnywhere, DisplayName="Instances", Category=Instances, meta=(MakeEditWidget=true))` — Array of instances
- L72 _protected member_ `TArray<FBodyInstance*> InstanceBodies;` — Physics representation of the instance bodies
- L78 _public prototype_ `int32 AddInstance(const FTransform& Transform, UPaperSprite* Sprite, bool bWorldSpace = false, FLinearColor Color = FLinearColor::White);` — `UFUNCTION(BlueprintCallable, Category="Components|Sprite")` — Add an instance to this component. Transform can be given either in the local space of this component or world space.
- L80 _public prototype_ `virtual int32 AddInstanceWithMaterial(const FTransform& Transform, UPaperSprite* Sprite, UMaterialInterface* MaterialOverride = nullptr, bool bWorldSpace = false, FLinearColor Color = FLinearColor::White);`
- L84 _public prototype_ `bool GetInstanceTransform(int32 InstanceIndex, FTransform& OutInstanceTransform, bool bWorldSpace = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Components|Sprite")` — Get the transform for the instance specified. Instance is returned in local space of this component unless bWorldSpace is set.  Returns True on success.
- L86 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;`
- L90 _public prototype_ `virtual bool UpdateInstanceTransform(int32 InstanceIndex, const FTransform& NewInstanceTransform, bool bWorldSpace=false, bool bMarkRenderStateDirty=true, bool bTeleport=false);` — `UFUNCTION(BlueprintCallable, Category = "Components|Sprite")` — Update the transform for the instance specified. Instance is given in local space of this component unless bWorldSpace is set.  Returns True on success.
- L94 _public prototype_ `virtual bool UpdateInstanceColor(int32 InstanceIndex, FLinearColor NewInstanceColor, bool bMarkRenderStateDirty = true);` — `UFUNCTION(BlueprintCallable, Category = "Components|Sprite")` — Update the color for the instance specified. Returns True on success.
- L98 _public prototype_ `virtual bool RemoveInstance(int32 InstanceIndex);` — `UFUNCTION(BlueprintCallable, Category = "Components|Sprite")` — Remove the instance specified. Returns True on success.
- L102 _public prototype_ `virtual void ClearInstances();` — `UFUNCTION(BlueprintCallable, Category="Components|Sprite")` — Clear all instances being rendered by this component
- L106 _public prototype_ `int32 GetInstanceCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|Sprite")` — Get the number of instances in this component
- L110 _public prototype_ `void SortInstancesAlongAxis(FVector WorldSpaceSortAxis);` — `UFUNCTION(BlueprintCallable, Category = "Components|Sprite")` — Sort all instances by their world space position along the specified axis
- L113 _public prototype_ `virtual bool ShouldCreatePhysicsState() const override;` — UActorComponent interface
- L115 _protected prototype_ `virtual void OnCreatePhysicsState() override;`
- L116 _protected prototype_ `virtual void OnDestroyPhysicsState() override;`
- L118 _public prototype_ `virtual const UObject* AdditionalStatObject() const override;`
- L120 _public prototype_ `virtual void CheckForErrors() override;`
- L125 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L126 _public prototype_ `virtual bool CanEditSimulatePhysics() override;`
- L127 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& BoundTransform) const override;`
- L128 _public prototype_ `virtual void GetUsedTextures(TArray<UTexture*>& OutTextures, EMaterialQualityLevel::Type QualityLevel) override;`
- L129 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L130 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L131 _public prototype_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L132 _public prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L137 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L138 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L139 _public prototype_ `virtual void PostEditUndo() override;`
- L144 _public prototype_ `bool ContainsSprite(UPaperSprite* SpriteAsset) const;` — Returns true if this component references the specified sprite asset
- L147 _public prototype_ `void GetReferencedSpriteAssets(TArray<UObject*>& InOutObjects) const;` — Adds all referenced sprite assets to the specified list
- L150 _public prototype_ `void GetNavigationPerInstanceTransforms(const FBox& AreaBox, TArray<FTransform>& OutInstanceTransforms) const;` — Handles request from navigation system to gather instance transforms in a specific area box
- L152 _public function_ `const TArray<FSpriteInstanceData>& GetPerInstanceSpriteData() const`
- L162 _protected prototype_ `void ReleasePerInstanceRenderData();` — Transfers ownership of instance render data to a render thread instance render data will be released in scene proxy dtor or on render thread task
- L165 _protected prototype_ `void CreateAllInstanceBodies();` — Creates body instances for all instances owned by this component
- L168 _protected prototype_ `void ClearAllInstanceBodies();` — Terminate all body instances owned by this component
- L171 _protected prototype_ `void SetupNewInstanceData(FSpriteInstanceData& InOutNewInstanceData, int32 InInstanceIndex, const FTransform& InInstanceTransform, UPaperSprite* InSprite, UMaterialInterface* MaterialOverride, const FColor& InColor);` — Sets up new instance data to sensible defaults, creates physics counterparts if possible
- L174 _protected prototype_ `FBodyInstance* InitInstanceBody(int32 InstanceIndex, const FSpriteInstanceData& InstanceData, FPhysScene* PhysScene);` — Creates a body instance for the specified instance data if that sprite has defined collision
- L177 _protected prototype_ `void RebuildInstances();` — Invalidates the render and collision state
- L180 _protected prototype_ `void RebuildMaterialList();` — Creates the material list from the instances
- L183 _protected prototype_ `int32 UpdateMaterialList(UPaperSprite* Sprite, UMaterialInterface* MaterialOverride);` — Adds to the material list from a single sprite

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperRuntimeSettings.h` (Public)


#### class `UPaperRuntimeSettings`  
`class UPaperRuntimeSettings : public UObject`  
_L11-26_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Paper2D plugin.
- L17 _private member_ `bool bEnableSpriteAtlasGroups;` — `UPROPERTY(EditAnywhere, config, Category=Experimental)` — Enables experimental *incomplete and unsupported* texture atlas groups that sprites can be assigned to
- L21 _private member_ `bool bEnableTerrainSplineEditing;` — `UPROPERTY(EditAnywhere, config, Category=Experimental, meta=(ConfigRestartRequired=true))` — Enables experimental *incomplete and unsupported* 2D terrain spline editing. Note: You need to restart the editor when enabling this setting for the change to fully take effect.
- L25 _private member_ `bool bResizeSpriteDataToMatchTextures;` — `UPROPERTY(EditAnywhere, config, Category=Settings)` — Enables automatic resizing of various sprite data that is authored in texture space if the source texture gets resized (sockets, the pivot, render and collision geometry, etc...)

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h` (Public)


#### struct `FPaperSpriteSocket`  
`struct FPaperSpriteSocket`  
_L20-31_
- reflection: `USTRUCT(BlueprintType)`
- desc: @TODO: Should have some nice UI and enforce unique names, etc...
- L26 _public member_ `FTransform LocalTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Sockets)` — Transform in pivot space (*not* texture space)
- L30 _public member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Sockets)` — Name of the socket

#### class `UPaperSprite`  
`class UPaperSprite : public UObject, public IInterface_CollisionDataProvider, public ISlateTextureAtlasInterface`  
_L45-347_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(DisplayThumbnail = "true"))`
- inherits: `UObject,IInterface_CollisionDataProvider,ISlateTextureAtlasInterface`
- L54 _protected member_ `FVector2D OriginInSourceImageBeforeTrimming;` — `UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay, meta=(EditCondition="bTrimmedInSourceImage"))` — Origin within SourceImage, prior to atlasing
- L58 _protected member_ `FVector2D SourceImageDimensionBeforeTrimming;` — `UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay, meta=(EditCondition="bTrimmedInSourceImage"))` — Dimensions of SourceImage
- L62 _protected member_ `bool bTrimmedInSourceImage;` — `UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay)` — This texture is trimmed, consider the values above
- L66 _protected member_ `bool bRotatedInSourceImage;` — `UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay)` — This texture is rotated in the atlas
- L71 _protected member_ `FVector2D SourceTextureDimension;` — `UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay)` — Dimension of the texture when this sprite was created Used when the sprite is resized at some point
- L77 _protected member_ `FVector2D SourceUV;` — `UPROPERTY(Category=Sprite, EditAnywhere, AssetRegistrySearchable)` — Position within SourceTexture (in pixels)
- L81 _protected member_ `FVector2D SourceDimension;` — `UPROPERTY(Category=Sprite, EditAnywhere, AssetRegistrySearchable)` — Dimensions within SourceTexture (in pixels)
- L85 _protected member_ `TSoftObjectPtr<UTexture2D> SourceTexture;` — `UPROPERTY(Category=Sprite, EditAnywhere, AssetRegistrySearchable)` — The source texture that the sprite comes from
- L88 _protected member_ `mutable TObjectPtr<UTexture2D> SourceTextureCacheNeverSerialized;` — `UPROPERTY(Transient)`
- L93 _protected member_ `TArray<TObjectPtr<UTexture>> AdditionalSourceTextures;` — `UPROPERTY(Category=Sprite, EditAnywhere, AssetRegistrySearchable, meta=(DisplayName="Additional Textures"))` — Additional source textures for other slots
- L97 _protected member_ `FVector2D BakedSourceUV;` — `UPROPERTY()` — Position within BakedSourceTexture (in pixels)
- L101 _protected member_ `FVector2D BakedSourceDimension;` — `UPROPERTY()` — Dimensions within BakedSourceTexture (in pixels)
- L104 _protected member_ `TObjectPtr<UTexture2D> BakedSourceTexture;` — `UPROPERTY()`
- L108 _protected member_ `TObjectPtr<UMaterialInterface> DefaultMaterial;` — `UPROPERTY(Category=Sprite, EditAnywhere, BlueprintReadOnly)` — The material to use on a sprite instance if not overridden (this is the default material when only one is being used, and is the translucent/masked material for Diced render geometry, slot 0)
- L112 _protected member_ `TObjectPtr<UMaterialInterface> AlternateMaterial;` — `UPROPERTY(Category=Rendering, EditAnywhere, BlueprintReadOnly)` — The alternate material to use on a sprite instance if not overridden (this is only used for Diced render geometry, and will be the opaque material in that case, slot 1)
- L116 _protected member_ `TArray<FPaperSpriteSocket> Sockets;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — List of sockets on this sprite
- L120 _protected member_ `TEnumAsByte<ESpriteCollisionMode::Type> SpriteCollisionDomain;` — `UPROPERTY(Category=Collision, EditAnywhere)` — Collision domain (no collision, 2D, or 3D)
- L124 _protected member_ `float PixelsPerUnrealUnit;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta = (DisplayName = "Pixels per unit"))` — The scaling factor between pixels and Unreal units (cm) (e.g., 0.64 would make a 64 pixel wide sprite take up 100 cm)
- L129 _public member_ `TObjectPtr<class UBodySetup> BodySetup;` — `UPROPERTY(EditAnywhere, Category=NeverShown)` — Baked physics data.
- L136 _protected member_ `TEnumAsByte<ESpritePivotMode::Type> PivotMode;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Pivot mode
- L140 _protected member_ `FVector2D CustomPivotPoint;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Custom pivot point (relative to the sprite rectangle)
- L144 _protected member_ `bool bSnapPivotToPixelGrid;` — `UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay)` — Should the pivot be snapped to a pixel boundary?
- L148 _protected member_ `FSpriteGeometryCollection CollisionGeometry;` — `UPROPERTY(Category=Collision, EditAnywhere)` — Custom collision geometry polygons (in texture space)
- L152 _protected member_ `float CollisionThickness;` — `UPROPERTY(Category=Collision, EditAnywhere)` — The extrusion thickness of collision geometry when using a 3D collision domain
- L156 _protected member_ `FSpriteGeometryCollection RenderGeometry;` — `UPROPERTY(Category=Rendering, EditAnywhere)` — Custom render geometry polygons (in texture space)
- L160 _protected member_ `TObjectPtr<class UPaperSpriteAtlas> AtlasGroup;` — `UPROPERTY(Category=Sprite, EditAnywhere, AssetRegistrySearchable)` — Spritesheet group that this sprite belongs to
- L164 _protected member_ `TSoftObjectPtr<class UPaperSpriteAtlas> PreviousAtlasGroup;` — The previous spritesheet group this belonged to To make sure we remove ourselves from it if changed or nulled out
- L171 _public member_ `int32 AlternateMaterialSplitIndex;` — `UPROPERTY()` — The point at which the alternate material takes over in the baked render data (or INDEX_NONE)
- L178 _public member_ `TArray<FVector4> BakedRenderData;` — `UPROPERTY()` — Baked render data (triangle vertices, stored as XY UV tuples) XY is the XZ position in world space, relative to the pivot UV is normalized (0..1) There should always be a multiple of three elements in this array
- L183 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L184 _public prototype_ `virtual void PostLoad() override;`
- L186 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L187 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L192 _public prototype_ `virtual FSlateAtlasData GetSlateAtlasData() const override;` — ISlateTextureAtlasInterface interface
- L196 _public prototype_ `FVector2D ConvertTextureSpaceToPivotSpace(FVector2D Input) const;`
- L197 _public prototype_ `FVector2D ConvertPivotSpaceToTextureSpace(FVector2D Input) const;`
- L198 _public prototype_ `FVector ConvertTextureSpaceToPivotSpace(FVector Input) const;`
- L199 _public prototype_ `FVector ConvertPivotSpaceToTextureSpace(FVector Input) const;`
- L200 _public prototype_ `FVector2D ConvertWorldSpaceToTextureSpace(const FVector& WorldPoint) const;`
- L201 _public prototype_ `FVector2D ConvertWorldSpaceDeltaToTextureSpace(const FVector& WorldDelta, bool bIgnoreRotation = false) const;`
- L204 _public prototype_ `FVector ConvertTextureSpaceToWorldSpace(const FVector2D& SourcePoint) const;` — World space WRT the sprite editor *only*
- L205 _public prototype_ `FTransform GetPivotToWorld() const;`
- L208 _public prototype_ `FVector2D GetRawPivotPosition() const;` — Returns the raw pivot position (ignoring pixel snapping)
- L211 _public prototype_ `FVector2D GetPivotPosition() const;` — Returns the current pivot position in texture space
- L214 _public function_ `float GetCollisionThickness() const` — Returns the extrusion thickness of collision geometry when using a 3D collision domain
- L220 _public function_ `ESpriteCollisionMode::Type GetSpriteCollisionDomain() const` — Returns the collision domain (no collision, 2D, or 3D)
- L226 _public prototype_ `void RescaleSpriteData(UTexture2D* Texture);` — Rescale properties to handle source texture size change
- L227 _public prototype_ `bool NeedRescaleSpriteData();`
- L230 _public prototype_ `void RebuildData();` — This is a generic "rebuild all" function that calls RebuildCollisionData() and then RebuildRenderData().
- L231 _public prototype_ `void RebuildCollisionData();`
- L232 _public prototype_ `void RebuildRenderData();`
- L234 _public prototype_ `void ExtractSourceRegionFromTexturePoint(const FVector2D& Point);`
- L238 _public prototype_ `void FindTextureBoundingBox(float AlphaThreshold, FVector2D& OutBoxPosition, FVector2D& OutBoxSize);` — Evaluates the SourceUV/SourceDimensons rectangle, finding the tightest bounds that still include all pixels with alpha above AlphaThreshold. The output box position is the top left corner of the box, not the center.
- L240 _public prototype_ `static void FindContours(const FIntPoint& ScanPos, const FIntPoint& ScanSize, float AlphaThreshold, float Detail, UTexture2D* Texture, TArray< TArray<FIntPoint> >& OutPoints);`
- L241 _public prototype_ `static void ExtractRectsFromTexture(UTexture2D* Texture, TArray<FIntRect>& OutRects);`
- L242 _public prototype_ `void BuildGeometryFromContours(FSpriteGeometryCollection& GeomOwner);`
- L244 _public prototype_ `void CreatePolygonFromBoundingBox(FSpriteGeometryCollection& GeomOwner, bool bUseTightBounds);`
- L247 _public prototype_ `void InitializeSprite(const FSpriteAssetInitParameters& InitParams, bool bRebuildData = true);` — Reinitializes this sprite (NOTE: Does not register existing components in the world)
- L249 _public prototype_ `void SetTrim(bool bTrimmed, const FVector2D& OriginInSourceImage, const FVector2D& SourceImageDimension, bool bRebuildData = true);`
- L250 _public prototype_ `void SetRotated(bool bRotated, bool bRebuildData = true);`
- L251 _public prototype_ `void SetPivotMode(ESpritePivotMode::Type PivotMode, FVector2D CustomTextureSpacePivot, bool bRebuildData = true);`
- L254 _public function_ `FVector2D GetOriginInSourceImageBeforeTrimming() const` — Returns the Origin within SourceImage, prior to atlasing
- L257 _public function_ `FVector2D GetSourceImageDimensionBeforeTrimming() const` — Returns the Dimensions of SourceImage prior to trimming
- L262 _public function_ `bool IsTrimmedInSourceImage() const` — Returns true if this sprite is trimmed from the original texture, meaning that the source image dimensions and origin in the source image may not be the same as the final results for the sprite (empty alpha=0 pixels were trimmed from the exterior region)
- L265 _public function_ `bool IsRotatedInSourceImage() const` — This texture is rotated in the atlas
- L267 _public function_ `ESpritePivotMode::Type GetPivotMode(FVector2D& OutCustomTextureSpacePivot) const`
- L269 _public function_ `FVector2D GetSourceUV() const`
- L270 _public function_ `FVector2D GetSourceSize() const`
- L271 _public prototype_ `UTexture2D* GetSourceTexture() const;`
- L273 _public function_ `const UPaperSpriteAtlas* GetAtlasGroup() const`
- L278 _public prototype_ `void OnObjectReimported(UTexture2D* InObject);` — Called when an object is re-imported in the editor
- L284 _public prototype_ `void ValidateSocketNames();` — Make sure all socket names are valid All duplicate / empty names will be made unique
- L287 _public prototype_ `void RemoveSocket(FName SocketName);` — Removes the specified socket
- L291 _public function_ `float GetPixelsPerUnrealUnit() const` — Return the scaling factor between pixels and Unreal units (cm)
- L294 _public function_ `float GetUnrealUnitsPerPixel() const` — Return the scaling factor between Unreal units (cm) and pixels
- L297 _public prototype_ `UTexture2D* GetBakedTexture() const;` — Returns the texture this should be rendered with
- L300 _public prototype_ `void GetBakedAdditionalSourceTextures(FAdditionalSpriteTextureArray& OutTextureList) const;` — Returns the list of additional source textures this should be rendered with
- L303 _public function_ `UMaterialInterface* GetDefaultMaterial() const` — Return the default material for this sprite
- L306 _public function_ `UMaterialInterface* GetAlternateMaterial() const` — Return the alternate material for this sprite
- L309 _public prototype_ `UMaterialInterface* GetMaterial(int32 MaterialIndex) const;` — Returns either the default material (index 0) or alternate material (index 1)
- L312 _public prototype_ `int32 GetNumMaterials() const;` — Returns the number of materials (1 or 2, depending on if there is alternate geometry)
- L315 _public prototype_ `FBoxSphereBounds GetRenderBounds() const;` — Returns the render bounds of this sprite
- L318 _public prototype_ `FPaperSpriteSocket* FindSocket(FName SocketName);` — Search for a socket (note: do not cache this pointer; it's unsafe if the Socket array is edited)
- L321 _public function_ `bool HasAnySockets() const` — Returns true if the sprite has any sockets
- L324 _public prototype_ `void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const;` — Returns a list of all of the sockets
- L327 _public prototype_ `virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;` — IInterface_CollisionDataProvider interface
- L328 _public prototype_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;`
- L332 _public prototype_ `static FName GetSourceTextureMemberName();`
- L336 _protected prototype_ `void RefreshBakedData();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PAPER2D_API`
- L33 _typedef_ `typedef TArray<class UTexture*, TInlineAllocator<4>> FAdditionalSpriteTextureArray;`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteActor.h` (Public)


#### class `APaperSpriteActor`  
`class APaperSpriteActor : public AActor`  
_L19-36_
- reflection: `UCLASS(MinimalAPI, ComponentWrapperClass, meta = (ChildCanTick))`
- inherits: `AActor`
- desc: An instance of a UPaperSprite in a level. This actor is created when you drag a sprite asset from the content browser into the level, and it is just a thin wrapper around a UPaperSpriteComponent that actually references the asset.
- L25 _private member_ `TObjectPtr<class UPaperSpriteComponent> RenderComponent;` — `UPROPERTY(Category=Sprite, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories="Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess="true"))`
- L30 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L35 _public function_ `FORCEINLINE class UPaperSpriteComponent* GetRenderComponent() const` — Returns RenderComponent subobject

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteAtlas.h` (Public)


#### struct `FPaperSpriteAtlasSlot`  
`struct FPaperSpriteAtlasSlot`  
_L12-35_
- reflection: `USTRUCT()`
- L17 _public member_ `TSoftObjectPtr<class UPaperSprite> SpriteRef;` — `UPROPERTY()`
- L20 _public member_ `int32 AtlasIndex = 0;` — `UPROPERTY()`
- L23 _public member_ `int32 X = 0;` — `UPROPERTY()`
- L26 _public member_ `int32 Y = 0;` — `UPROPERTY()`
- L29 _public member_ `int32 Width = 0;` — `UPROPERTY()`
- L32 _public member_ `int32 Height = 0;` — `UPROPERTY()`
- L34 _public function_ `bool IsValid()`

#### enum `EPaperSpriteAtlasPadding`  
`enum class EPaperSpriteAtlasPadding : uint8`  
_L38-46_
- reflection: `UENUM()`
- L41 _public enumerator_ `DilateBorder` — Dilate the texture to pad the atlas.
- L43 _public enumerator_ `PadWithZero` — Padding border filled with zeros.

#### class `UPaperSpriteAtlas`  
`class UPaperSpriteAtlas : public UObject`  
_L52-129_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental, meta=(DisplayThumbnail = "true"))`
- inherits: `UObject`
- desc: Groups together a set of sprites that will try to share the same texture atlas (allowing them to be combined into a single draw call)
- L59 _private member_ `FString AtlasDescription;` — `UPROPERTY(EditAnywhere, Category=General)` — Description of this atlas, which shows up in the content browser tooltip
- L63 _private member_ `int32 MaxWidth;` — `UPROPERTY(EditAnywhere, Category = General)` — Maximum atlas page width (single pages might be smaller)
- L67 _private member_ `int32 MaxHeight;` — `UPROPERTY(EditAnywhere, Category = General)` — Maximum atlas page height (single pages might be smaller)
- L71 _private member_ `int32 MipCount;` — `UPROPERTY(EditAnywhere, Category = General)` — Maximum atlas page height (single pages might be smaller)
- L75 _private member_ `EPaperSpriteAtlasPadding PaddingType;` — `UPROPERTY(EditAnywhere, Category = General)` — The type of padding performed on this atlas
- L79 _private member_ `int32 Padding;` — `UPROPERTY(EditAnywhere, Category = General)` — The number of pixels of padding
- L83 _private member_ `TEnumAsByte<TextureCompressionSettings> CompressionSettings;` — `UPROPERTY(EditAnywhere, Category=AtlasTexture)` — Compression settings to use on atlas texture
- L87 _private member_ `TEnumAsByte<TextureFilter> Filter;` — `UPROPERTY(EditAnywhere, Category=AtlasTexture)` — Texture filtering mode when sampling these textures
- L91 _private member_ `TArray<TObjectPtr<UTexture>> GeneratedTextures;` — `UPROPERTY(VisibleAnywhere, Category=AtlasTexture)` — List of generated atlas textures
- L95 _private member_ `FGuid AtlasGUID;` — `UPROPERTY(VisibleAnywhere, Category=General)` — The GUID of the atlas group, used to match up sprites that belong to this group even thru atlas renames
- L99 _private member_ `bool bRebuildAtlas;` — `UPROPERTY(EditAnywhere, Category=General)` — Slots in the atlas
- L103 _private member_ `TArray<FPaperSpriteAtlasSlot> AtlasSlots;` — `UPROPERTY()` — Slots in the atlas
- L107 _private member_ `int32 NumIncrementalBuilds;` — `UPROPERTY()` — Track the number of incremental builds
- L111 _private member_ `int32 BuiltWidth;` — `UPROPERTY()` — Values used when building this atlas
- L114 _private member_ `int32 BuiltHeight;` — `UPROPERTY()`
- L117 _private member_ `int32 BuiltPadding;` — `UPROPERTY()`
- L124 _public prototype_ `virtual void PostInitProperties() override;`
- L125 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L127 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteBlueprintLibrary.h` (Public)


#### class `UPaperSpriteBlueprintLibrary`  
`class UPaperSpriteBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L16-23_
- reflection: `UCLASS(meta=(ScriptName="PaperSpriteLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L22 _public prototype_ `static FSlateBrush MakeBrushFromSprite(UPaperSprite* Sprite, int32 Width, int32 Height);` — `UFUNCTION(BlueprintPure, Category="Widget|Brush")`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h` (Public)


#### class `UPaperSpriteComponent`  
`class UPaperSpriteComponent : public UMeshComponent`  
_L29-106_
- reflection: `UCLASS(MinimalAPI, ShowCategories=(Mobility), ClassGroup=Paper2D, meta=(BlueprintSpawnableComponent))`
- inherits: `UMeshComponent`
- L36 _protected member_ `TObjectPtr<UPaperSprite> SourceSprite;` — `UPROPERTY(Category=Sprite, EditAnywhere, BlueprintReadOnly, meta=(DisplayThumbnail = "true"))` — The sprite asset used by this component
- L40 _protected member_ `TObjectPtr<UMaterialInterface> MaterialOverride_DEPRECATED;` — `UPROPERTY()` — DEPRECATED in 4.4: The material override for this sprite component (if any); replaced by the Materials array inherited from UMeshComponent
- L44 _protected member_ `FLinearColor SpriteColor;` — `UPROPERTY(BlueprintReadOnly, Interp, Category=Sprite)` — The color of the sprite (passed to the sprite material as a vertex color)
- L49 _public prototype_ `virtual bool SetSprite(class UPaperSprite* NewSprite);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Change the PaperSprite used by this instance.
- L53 _public prototype_ `virtual UPaperSprite* GetSprite();` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Gets the PaperSprite used by this instance.
- L56 _public function_ `FLinearColor GetSpriteColor() const` — Returns the current color of the sprite
- L60 _public prototype_ `void SetSpriteColor(FLinearColor NewColor);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Set color of the sprite
- L63 _public prototype_ `FLinearColor GetWireframeColor() const;` — Returns the wireframe color to use for this component.
- L68 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L71 _public prototype_ `virtual void PostLoad() override;`
- L75 _public prototype_ `virtual void SendRenderDynamicData_Concurrent() override;` — UActorComponent interface
- L76 _public prototype_ `virtual const UObject* AdditionalStatObject() const override;`
- L78 _public prototype_ `virtual void CheckForErrors() override;`
- L83 _public prototype_ `virtual bool HasAnySockets() const override;` — USceneComponent interface
- L84 _public prototype_ `virtual bool DoesSocketExist(FName InSocketName) const override;`
- L85 _public prototype_ `virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;`
- L86 _public prototype_ `virtual void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const override;`
- L90 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L91 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L92 _public prototype_ `virtual class UBodySetup* GetBodySetup() override;`
- L93 _public prototype_ `virtual void GetUsedTextures(TArray<UTexture*>& OutTextures, EMaterialQualityLevel::Type QualityLevel) override;`
- L94 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L95 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L96 _public prototype_ `virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const override;`
- L97 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L101 _public prototype_ `void SetTransientTextureOverride(const UTexture* TextureToModifyOverrideFor, UTexture* OverrideTexture);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTerrainActor.h` (Public)


#### class `APaperTerrainActor`  
`class APaperTerrainActor : public AActor`  
_L19-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental)`
- inherits: `AActor`
- L25 _private member_ `TObjectPtr<class USceneComponent> DummyRoot;` — `UPROPERTY()`
- L28 _private member_ `TObjectPtr<class UPaperTerrainSplineComponent> SplineComponent;` — `UPROPERTY()`
- L31 _private member_ `TObjectPtr<class UPaperTerrainComponent> RenderComponent;` — `UPROPERTY(Category=Sprite, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories="Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess="true"))`
- L36 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L41 _public function_ `FORCEINLINE class USceneComponent* GetDummyRoot() const` — Returns DummyRoot subobject
- L43 _public function_ `FORCEINLINE class UPaperTerrainSplineComponent* GetSplineComponent() const` — Returns SplineComponent subobject
- L45 _public function_ `FORCEINLINE class UPaperTerrainComponent* GetRenderComponent() const` — Returns RenderComponent subobject

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTerrainComponent.h` (Public)


#### struct `FPaperTerrainSpriteGeometry`  
`struct FPaperTerrainSpriteGeometry`  
_L19-24_
- L21 _public member_ `TArray<FSpriteDrawCallRecord> Records;`
- L22 _public member_ `UMaterialInterface* Material;`
- L23 _public member_ `int32 DrawOrder;`

#### struct `FTerrainSpriteStamp`  
`struct FTerrainSpriteStamp`  
_L26-35_
- L28 _public member_ `const UPaperSprite* Sprite;`
- L29 _public member_ `float NominalWidth;`
- L30 _public member_ `float Time;`
- L31 _public member_ `float Scale;`
- L32 _public member_ `bool bCanStretch;`
- L34 _public prototype_ `FTerrainSpriteStamp(const UPaperSprite* InSprite, float InTime, bool bIsEndCap);`

#### struct `FTerrainSegment`  
`struct FTerrainSegment`  
_L37-46_
- L39 _public member_ `float StartTime;`
- L40 _public member_ `float EndTime;`
- L41 _public member_ `const FPaperTerrainMaterialRule* Rule;`
- L42 _public member_ `TArray<FTerrainSpriteStamp> Stamps;`
- L44 _public prototype_ `FTerrainSegment();`
- L45 _public prototype_ `void RepositionStampsToFillSpace();`

#### class `UPaperTerrainComponent`  
`class UPaperTerrainComponent : public UPrimitiveComponent`  
_L54-139_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental)`
- inherits: `UPrimitiveComponent`
- L61 _public member_ `TObjectPtr<class UPaperTerrainMaterial> TerrainMaterial;` — `UPROPERTY(Category=Sprite, EditAnywhere, BlueprintReadOnly)` — The terrain material to apply to this component (set of rules for which sprites are used on different surfaces or the interior)
- L64 _public member_ `bool bClosedSpline;` — `UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly)`
- L67 _public member_ `bool bFilledSpline;` — `UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bClosedSpline"))`
- L70 _public member_ `TObjectPtr<class UPaperTerrainSplineComponent> AssociatedSpline;` — `UPROPERTY()`
- L74 _public member_ `int32 RandomSeed;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Random seed used for choosing which spline meshes to use.
- L78 _public member_ `float SegmentOverlapAmount;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — The overlap amount between segments
- L83 _protected member_ `FLinearColor TerrainColor;` — `UPROPERTY(Category=Sprite, BlueprintReadOnly, Interp)` — The color of the terrain (passed to the sprite material as a vertex color)
- L87 _protected member_ `int32 ReparamStepsPerSegment;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta=(ClampMin=4, UIMin=4), AdvancedDisplay)` — Number of steps per spline segment to place in the reparameterization table
- L91 _protected member_ `TEnumAsByte<ESpriteCollisionMode::Type> SpriteCollisionDomain;` — `UPROPERTY(Category=Collision, EditAnywhere)` — Collision domain (no collision, 2D (experimental), or 3D)
- L95 _protected member_ `float CollisionThickness;` — `UPROPERTY(Category=Collision, EditAnywhere)` — The extrusion thickness of collision geometry when using a 3D collision domain
- L99 _public prototype_ `virtual const UObject* AdditionalStatObject() const override;` — UObject interface
- L100 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L101 _public prototype_ `virtual void PostLoad() override;`
- L103 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface
- L109 _public prototype_ `virtual void OnUnregister() override;`
- L113 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L114 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L115 _public prototype_ `virtual UBodySetup* GetBodySetup() override;`
- L120 _public prototype_ `void SetTerrainColor(FLinearColor NewColor);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Set color of the terrain
- L123 _protected prototype_ `void SpawnSegments(const TArray<FTerrainSegment>& TerrainSegments, bool bGenerateSegmentColliders);`
- L125 _protected prototype_ `void GenerateFillRenderDataFromPolygon(const class UPaperSprite* NewSprite, FSpriteDrawCallRecord& FillDrawCall, const FVector2D& TextureSize, const TArray<FVector2D>& TriangulatedPolygonVertices);`
- L126 _protected prototype_ `void GenerateCollisionDataFromPolygon(const TArray<FVector2D>& SplinePolyVertices2D, const TArray<float>& TerrainOffsets, const TArray<FVector2D>& TriangulatedPolygonVertices);`
- L127 _protected prototype_ `void InsertConvexCollisionDataFromPolygon(const TArray<FVector2D>& ClosedPolyVertices2D);`
- L128 _protected prototype_ `void ConstrainSplinePointsToXZ();`
- L130 _protected prototype_ `void OnSplineEdited();`
- L134 _protected member_ `TObjectPtr<class UBodySetup> CachedBodySetup;` — `UPROPERTY(Transient, DuplicateTransient)` — Description of collision
- L136 _protected member_ `TArray<FPaperTerrainSpriteGeometry> GeneratedSpriteGeometry;`
- L138 _protected prototype_ `FTransform GetTransformAtDistance(float InDistance) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`
- L11 _namespace_ `namespace ESpriteCollisionMode`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTerrainMaterial.h` (Public)


#### struct `FPaperTerrainMaterialRule`  
`struct FPaperTerrainMaterialRule`  
_L14-66_
- reflection: `USTRUCT(BlueprintType)`
- desc: Rule for a single section of a terrain material
- L20 _public member_ `TObjectPtr<class UPaperSprite> StartCap;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta=(DisplayThumbnail="true"))` — The sprite to use at the 'left' (closest to spline start) edge of the terrain segment
- L24 _public member_ `TArray<TObjectPtr<class UPaperSprite>> Body;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta=(DisplayThumbnail="true"))` — A set of sprites to randomly choose to fill up the interior space between the caps in a terrain segment
- L28 _public member_ `TObjectPtr<class UPaperSprite> EndCap;` — `UPROPERTY(Category=Sprite, EditAnywhere, meta=(DisplayThumbnail="true"))` — The sprite to use at the 'right' (closest to spline end) edge of the terrain segment
- L32 _public member_ `float MinimumAngle;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Minimum slope angle (in degrees) to apply this rule
- L36 _public member_ `float MaximumAngle;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Maximum slope angle (in degrees) to apply this rule
- L40 _public member_ `bool bEnableCollision;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — If true, collision is enabled for sections matching this rule
- L44 _public member_ `float CollisionOffset;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — How much should the collision be lofted from the spline (positive values go out from the spline, negative values go in to the spline)
- L48 _public member_ `int32 DrawOrder;` — `UPROPERTY(Category=Sprite, EditAnywhere)` — Specify a draw order for different materials in a spline. Smaller draw orders are drawn first, negative values are allowed.
- L53 _public member_ `FText Description;` — `UPROPERTY(Category = Sprite, EditAnywhere)` — Readable description for the rule (unused anywhere, just for clarity when editing the material)
- L56 _public function_ `FPaperTerrainMaterialRule() : StartCap(nullptr) , EndCap(nullptr) , MinimumAngle(0.0f) , MaximumAngle(360.0f) , bEnableCollision(true) , CollisionOffset(0.0f) , DrawOrder(0)`

#### class `UPaperTerrainMaterial`  
`class UPaperTerrainMaterial : public UDataAsset`  
_L75-91_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L80 _private member_ `TArray<FPaperTerrainMaterialRule> Rules;` — `UPROPERTY(Category=Sprite, EditAnywhere)`
- L84 _private member_ `TObjectPtr<class UPaperSprite> InteriorFill;` — `UPROPERTY(Category = Sprite, EditAnywhere, meta=(DisplayThumbnail="true"))` — The sprite to use for an interior region fill
- L88 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTerrainSplineComponent.h` (Public)


#### class `UPaperTerrainSplineComponent`  
`class UPaperTerrainSplineComponent : public USplineComponent`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental)`
- inherits: `USplineComponent`
- desc: @TODO: Document
- L19 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _public member_ `FSimpleDelegate OnSplineEdited;` — Triggered when the spline is edited

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTileLayer.h` (Public)


#### enum `EPaperTileFlags`  
`enum class EPaperTileFlags : uint32`  
_L15-22_
- desc: Flags used in the packed tile index
- L17 _public enumerator_ `FlipHorizontal = (1U << 31)`
- L18 _public enumerator_ `FlipVertical = (1U << 30)`
- L19 _public enumerator_ `FlipDiagonal = (1U << 29)`
- L21 _public enumerator_ `TileIndexMask = ~(7U << 29)`

#### struct `FPaperTileInfo`  
`struct FPaperTileInfo`  
_L26-108_
- reflection: `USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/Paper2D.TileMapBlueprintLibrary.BreakTile", HasNativeMake="/Script/Paper2D.TileMapBlueprintLibrary.MakeTile"))`
- desc: This is the contents of a tile map cell
- L32 _public member_ `TObjectPtr<UPaperTileSet> TileSet;` — `UPROPERTY(EditAnywhere, Category=Sprite)` — The tile set that this tile comes from
- L36 _public member_ `int32 PackedTileIndex;` — `UPROPERTY(EditAnywhere, Category=Sprite)` — This is the index of the current tile within the tile set
- L38 _public function_ `FPaperTileInfo() : TileSet(nullptr) , PackedTileIndex(INDEX_NONE)`
- L44 _public function_ `inline bool operator==(const FPaperTileInfo& Other) const`
- L49 _public function_ `inline bool operator!=(const FPaperTileInfo& Other) const`
- L54 _public function_ `bool IsValid() const`
- L59 _public function_ `inline int32 GetFlagsAsIndex() const`
- L64 _public function_ `inline void SetFlagsAsIndex(uint8 NewFlags)`
- L71 _public function_ `inline int32 GetTileIndex() const`
- L76 _public function_ `inline bool HasFlag(EPaperTileFlags Flag) const`
- L81 _public function_ `inline void ToggleFlag(EPaperTileFlags Flag)`
- L89 _public function_ `inline void SetFlagValue(EPaperTileFlags Flag, bool bValue)`

#### class `UPaperTileLayer`  
`class UPaperTileLayer : public UObject`  
_L112-276_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This class represents a single layer in a tile map.  All layers in the map must have the size dimensions.
- L118 _private member_ `FText LayerName;` — `UPROPERTY(BlueprintReadOnly, Category=Sprite)` — Name of the layer
- L123 _private member_ `int32 LayerWidth;` — `UPROPERTY(BlueprintReadOnly, Category=Sprite, meta=(AllowPrivateAccess="true"))` — Width of the layer (in tiles)
- L127 _private member_ `int32 LayerHeight;` — `UPROPERTY(BlueprintReadOnly, Category=Sprite, meta=(AllowPrivateAccess="true"))` — Height of the layer (in tiles)
- L132 _private member_ `uint32 bHiddenInEditor:1;` — `UPROPERTY(EditAnywhere, Category=Sprite, meta=(AllowPrivateAccess="true"))` — Is this layer currently hidden in the editor?
- L137 _private member_ `uint32 bHiddenInGame:1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(AllowPrivateAccess="true"))` — Should this layer be hidden in the game?
- L142 _private member_ `uint32 bLayerCollides:1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(AllowPrivateAccess="true"))` — Should this layer generate collision? Note: This only has an effect if the owning tile map has collision enabled
- L146 _private member_ `uint32 bOverrideCollisionThickness:1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — Should this layer use a custom thickness for generated collision instead of the thickness setting in the tile map?
- L150 _private member_ `uint32 bOverrideCollisionOffset:1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — Should this layer use a custom offset for generated collision instead of the layer drawing offset?
- L154 _private member_ `float CollisionThicknessOverride;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(EditCondition=bOverrideCollisionThickness, AllowPrivateAccess="true"))` — The override thickness of the collision for this layer (when bOverrideCollisionThickness is set)
- L159 _private member_ `float CollisionOffsetOverride;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(EditCondition=bOverrideCollisionOffset, AllowPrivateAccess="true"))` — The override offset of the collision for this layer (when bOverrideCollisionOffset is set) Note: This is measured in Unreal Units (cm) from the center of the tile map component, not from the previous layer.
- L163 _private member_ `FLinearColor LayerColor;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sprite, meta=(AllowPrivateAccess="true"))` — The color of this layer (multiplied with the tile map color and passed to the material as a vertex color)
- L167 _private member_ `int32 AllocatedWidth;` — `UPROPERTY()` — The allocated width of the tile data (used to handle resizing without data loss)
- L171 _private member_ `int32 AllocatedHeight;` — `UPROPERTY()` — The allocated height of the tile data (used to handle resizing without data loss)
- L175 _private member_ `TArray<FPaperTileInfo> AllocatedCells;` — `UPROPERTY()` — The allocated tile data
- L178 _private member_ `TObjectPtr<UPaperTileSet> TileSet_DEPRECATED;` — `UPROPERTY()`
- L181 _private member_ `TArray<int32> AllocatedGrid_DEPRECATED;` — `UPROPERTY()`
- L184 _public prototype_ `void ConvertToTileSetPerCell();`
- L188 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L193 _public prototype_ `UPaperTileMap* GetTileMap() const;` — Returns the parent tile map
- L196 _public prototype_ `int32 GetLayerIndex() const;` — Returns the index of this layer in the parent tile map
- L199 _public prototype_ `bool InBounds(int32 X, int32 Y) const;` — Returns whether the specified coordinates are in bounds for the layer
- L202 _public prototype_ `FPaperTileInfo GetCell(int32 X, int32 Y) const;` — Returns the tile information about the specified cell
- L205 _public prototype_ `void SetCell(int32 X, int32 Y, const FPaperTileInfo& NewValue);` — Sets the tile information about the specified cell
- L208 _public prototype_ `void DestructiveAllocateMap(int32 NewWidth, int32 NewHeight);` — Reallocates the map.  This is a destructive operation that does not copy data across!
- L211 _public prototype_ `void ResizeMap(int32 NewWidth, int32 NewHeight);` — Reallocates the map.  This tries to preserve contents.
- L214 _public prototype_ `void AugmentBodySetup(UBodySetup* ShapeBodySetup, float RenderSeparation);` — Adds collision to the specified body setup
- L217 _public prototype_ `FLinearColor GetLayerColor() const;` — Gets the layer-specific color multiplier
- L220 _public prototype_ `void SetLayerColor(FLinearColor NewColor);` — Sets the layer-specific color multiplier (Note: does not invalidate any components using this layer!)
- L224 _public prototype_ `bool UsesTileSet(UPaperTileSet* TileSet) const;` — Checks to see if this layer uses the specified tile set Note: This is a slow operation, it scans each tile!
- L228 _public function_ `bool ShouldRenderInEditor() const` — Should this layer be drawn (in the editor)?
- L231 _public function_ `void SetShouldRenderInEditor(bool bShouldRender)` — Set whether this layer should be drawn (in the editor)
- L235 _public function_ `bool ShouldRenderInGame() const` — Should this layer be drawn (in game)?
- L238 _public function_ `int32 GetLayerWidth() const` — Returns the width of the layer (in tiles)
- L241 _public function_ `int32 GetLayerHeight() const` — Returns the height of the layer (in tiles)
- L244 _public prototype_ `static FTransform GetTileTransform(int32 FlagIndex);` — Returns the transform for the given packed flag index (0..7)
- L247 _public prototype_ `int32 GetNumOccupiedCells() const;` — Returns the number of occupied cells in the layer
- L250 _public function_ `const FPaperTileInfo* PRIVATE_GetAllocatedCells() const` — Returns the raw pointer to the allocated cells, only for use when rendering the tile map and should never be held onto
- L255 _public function_ `void SetLayerCollides(bool bShouldCollide)`
- L259 _public function_ `bool GetLayerCollides() const` — Should this layer generate collision? Note: This only has an effect if the owning tile map has collision enabled
- L261 _public function_ `void SetLayerCollisionThickness(bool bShouldOverride, float OverrideValue)`
- L267 _public function_ `void SetLayerCollisionOffset(bool bShouldOverride, float OverrideValue)`
- L274 _protected prototype_ `void ReallocateAndCopyMap();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`
- L104 _function_ `friend uint32 GetTypeHash(const FPaperTileInfo& PaperTileInfo)`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTileMap.h` (Public)


#### enum `ETileMapProjectionMode::Type`  
`enum Type : int`  
_L21-34_
- L24 _public enumerator_ `Orthogonal` — Square tile layout
- L27 _public enumerator_ `IsometricDiamond` — Square tile layout Orthogonal, Isometric tile layout (shaped like a diamond)
- L30 _public enumerator_ `IsometricStaggered` — Isometric tile layout (roughly in a square with alternating rows staggered).  Warning: Not fully supported yet.
- L33 _public enumerator_ `HexagonalStaggered` — Hexagonal tile layout (roughly in a square with alternating rows staggered).  Warning: Not fully supported yet.

#### class `UPaperTileMap`  
`class UPaperTileMap : public UObject`  
_L39-245_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A tile map is a 2D grid with a defined width and height (in tiles).  There can be multiple layers, each of which can specify which tile should appear in each cell of the map for that layer.
- L45 _private member_ `int32 MapWidth;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly, meta=(UIMin=1, ClampMin=1, ClampMax=1024))` — Width of map (in tiles)
- L49 _private member_ `int32 MapHeight;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly, meta=(UIMin=1, ClampMin=1, ClampMax=1024))` — Height of map (in tiles)
- L53 _private member_ `int32 TileWidth;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly, meta=(UIMin=1, ClampMin=1))` — Width of one tile (in pixels)
- L57 _private member_ `int32 TileHeight;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly, meta=(UIMin=1, ClampMin=1))` — Height of one tile (in pixels)
- L61 _private member_ `float PixelsPerUnrealUnit;` — `UPROPERTY(Category = Setup, EditAnywhere)` — The scaling factor between pixels and Unreal units (cm) (e.g., 0.64 would make a 64 pixel wide tile take up 100 cm)
- L65 _private member_ `float SeparationPerTileX;` — `UPROPERTY(Category=Setup, EditAnywhere, AdvancedDisplay)` — The Z-separation incurred as you travel in X (not strictly applied, batched tiles will be put at the same Z level)
- L69 _private member_ `float SeparationPerTileY;` — `UPROPERTY(Category=Setup, EditAnywhere, AdvancedDisplay)` — The Z-separation incurred as you travel in Y (not strictly applied, batched tiles will be put at the same Z level)
- L73 _private member_ `float SeparationPerLayer;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly)` — The Z-separation between each layer of the tile map
- L77 _private member_ `TSoftObjectPtr<UPaperTileSet> SelectedTileSet;` — `UPROPERTY()` — Last tile set that was selected when editing the tile map
- L81 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly)` — The material to use on a tile map instance if not overridden
- L85 _private member_ `TArray<TObjectPtr<UPaperTileLayer>> TileLayers;` — `UPROPERTY(Instanced, Category=Sprite, BlueprintReadOnly, EditAnywhere)` — The list of layers
- L90 _protected member_ `float CollisionThickness;` — `UPROPERTY(Category=Collision, EditAnywhere, BlueprintReadOnly)` — The extrusion thickness of collision geometry when using a 3D collision domain
- L94 _protected member_ `TEnumAsByte<ESpriteCollisionMode::Type> SpriteCollisionDomain;` — `UPROPERTY(Category=Collision, EditAnywhere, BlueprintReadOnly)` — Collision domain (no collision, 2D, or 3D)
- L99 _public member_ `TEnumAsByte<ETileMapProjectionMode::Type> ProjectionMode;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly)` — Tile map type
- L104 _public member_ `int32 HexSideLength;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(UIMin=0, ClampMin=0))` — The vertical height of the sides of the hex cell for a tile. Note: This value should already be included as part of the TileHeight, and is purely cosmetic; it only affects how the tile cursor preview is drawn.
- L108 _public member_ `TObjectPtr<UBodySetup> BodySetup;` — `UPROPERTY()` — Baked physics data.
- L114 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(Category=ImportSettings, VisibleAnywhere, Instanced)` — Importing data and options used for this tile map
- L118 _public member_ `int32 SelectedLayerIndex;` — `UPROPERTY()` — The currently selected layer index
- L122 _public member_ `FLinearColor BackgroundColor;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(HideAlphaChannel))` — The background color displayed in the tile map editor
- L126 _public member_ `FLinearColor TileGridColor;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(HideAlphaChannel))` — The color of the tile grid
- L130 _public member_ `FLinearColor MultiTileGridColor;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(HideAlphaChannel))` — The color of the multi tile grid
- L134 _public member_ `int32 MultiTileGridWidth;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(ClampMin=0))` — Number of tiles the multi tile grid spans horizontally. 0 removes vertical lines
- L138 _public member_ `int32 MultiTileGridHeight;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(ClampMin=0))` — Number of tiles the multi tile grid spans vertically. 0 removes horizontal lines
- L142 _public member_ `int32 MultiTileGridOffsetX;` — `UPROPERTY(Category=Setup, EditAnywhere)` — Number of tiles the multi tile grid is shifted to the right
- L146 _public member_ `int32 MultiTileGridOffsetY;` — `UPROPERTY(Category=Setup, EditAnywhere)` — Number of tiles the multi tile grid is shifted downwards
- L150 _public member_ `FLinearColor LayerGridColor;` — `UPROPERTY(Category=Setup, EditAnywhere, meta=(HideAlphaChannel))` — The color of the layer grid
- L155 _public member_ `int32 LayerNameIndex;` — `UPROPERTY()` — The naming index to start at when trying to create a new layer
- L159 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L160 _public prototype_ `virtual void PostInitProperties() override;`
- L161 _public prototype_ `virtual void PostLoad() override;`
- L163 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L164 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L165 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L166 _public prototype_ `void ValidateSelectedLayerIndex();`
- L169 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L174 _public prototype_ `void GetTileCoordinatesFromLocalSpacePosition(const FVector& Position, int32& OutTileX, int32& OutTileY) const;` — Returns the tile coordinates of the specified local space position
- L177 _public prototype_ `FVector GetTilePositionInLocalSpace(float TileX, float TileY, int32 LayerIndex = 0) const;` — Returns the top left corner of the specified tile in local space
- L180 _public prototype_ `FVector GetTileCenterInLocalSpace(float TileX, float TileY, int32 LayerIndex = 0) const;` — Returns the center of the specified tile in local space
- L183 _public prototype_ `void GetTilePolygon(int32 TileX, int32 TileY, int32 LayerIndex, TArray<FVector>& LocalSpacePoints) const;` — Returns the polygon for the specified tile (will be 4 or 6 vertices as a rectangle, diamond, or hexagon)
- L185 _public prototype_ `void GetTileToLocalParameters(FVector& OutCornerPosition, FVector& OutStepX, FVector& OutStepY, FVector& OutOffsetYFactor) const;`
- L186 _public prototype_ `void GetLocalToTileParameters(FVector& OutCornerPosition, FVector& OutStepX, FVector& OutStepY, FVector& OutOffsetYFactor) const;`
- L189 _public function_ `float GetCollisionThickness() const` — Returns the extrusion thickness of collision geometry when using a 3D collision domain
- L195 _public function_ `ESpriteCollisionMode::Type GetSpriteCollisionDomain() const` — Returns the collision domain (no collision, 2D, or 3D)
- L201 _public prototype_ `void SetCollisionThickness(float Thickness = 50.0f);` — Sets the collision thickness
- L204 _public prototype_ `void SetCollisionDomain(ESpriteCollisionMode::Type Domain);` — Sets the collision domain
- L206 _public prototype_ `FBoxSphereBounds GetRenderBounds() const;`
- L209 _public prototype_ `UPaperTileLayer* AddNewLayer(int32 InsertionIndex = INDEX_NONE);` — Creates and adds a new layer and returns it
- L212 _public prototype_ `void AddExistingLayer(UPaperTileLayer* NewLayer, int32 InsertionIndex = INDEX_NONE);` — Handles adding an existing layer that does *not* belong to any existing tile map
- L215 _public prototype_ `static FText GenerateNewLayerName(UPaperTileMap* TileMap);` — Creates a reasonable new layer name
- L218 _public prototype_ `bool IsLayerNameInUse(const FText& LayerName) const;` — Returns true if the specified name is already in use as a layer name
- L221 _public prototype_ `void ResizeMap(int32 NewWidth, int32 NewHeight, bool bForceResize = true);` — Resize the tile map and all layers
- L224 _public function_ `float GetPixelsPerUnrealUnit() const` — Return the scaling factor between pixels and Unreal units (cm)
- L227 _public function_ `float GetUnrealUnitsPerPixel() const` — Return the scaling factor between Unreal units (cm) and pixels
- L231 _public prototype_ `void InitializeNewEmptyTileMap(UPaperTileSet* DefaultTileSetAsset = nullptr);` — Called when a fresh tile map has been created (by factory or otherwise) Adds a default layer and pulls the PixelsPerUnrealUnit from the project settings
- L234 _public prototype_ `UPaperTileMap* CloneTileMap(UObject* OuterForClone);` — Creates a clone of this tile map in the specified outer
- L238 _public prototype_ `bool UsesTileSet(UPaperTileSet* TileSet) const;` — Checks to see if this tile map uses the specified tile set Note: This is a slow operation, it scans each tile of each layer!
- L241 _public prototype_ `void RebuildCollision();` — Rebuild collision and recreate the body setup
- L244 _protected prototype_ `virtual void UpdateBodySetup();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PAPER2D_API`
- L9 _namespace_ `namespace ESpriteCollisionMode`
- L19 _namespace_ `namespace ETileMapProjectionMode`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTileMapActor.h` (Public)


#### class `APaperTileMapActor`  
`class APaperTileMapActor : public AActor`  
_L20-37_
- reflection: `UCLASS(MinimalAPI, ComponentWrapperClass)`
- inherits: `AActor`
- desc: An instance of a UPaperTileMap in a level. This actor is created when you drag a tile map asset from the content browser into the level, and it is just a thin wrapper around a UPaperTileMapComponent that actually references the asset.
- L26 _private member_ `TObjectPtr<class UPaperTileMapComponent> RenderComponent;` — `UPROPERTY(Category=TileMapActor, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories="Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess="true"))`
- L31 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L36 _public function_ `FORCEINLINE class UPaperTileMapComponent* GetRenderComponent() const` — Returns RenderComponent subobject

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTileMapComponent.h` (Public)


#### class `UPaperTileMapComponent`  
`class UPaperTileMapComponent : public UMeshComponent`  
_L38-239_
- reflection: `UCLASS(MinimalAPI, hideCategories=Object, ClassGroup=Paper2D, EarlyAccessPreview, meta=(BlueprintSpawnableComponent))`
- inherits: `UMeshComponent`
- L44 _private member_ `int32 MapWidth_DEPRECATED;` — `UPROPERTY()`
- L47 _private member_ `int32 MapHeight_DEPRECATED;` — `UPROPERTY()`
- L50 _private member_ `int32 TileWidth_DEPRECATED;` — `UPROPERTY()`
- L53 _private member_ `int32 TileHeight_DEPRECATED;` — `UPROPERTY()`
- L56 _private member_ `TObjectPtr<class UPaperTileSet> DefaultLayerTileSet_DEPRECATED;` — `UPROPERTY()`
- L59 _private member_ `TObjectPtr<UMaterialInterface> Material_DEPRECATED;` — `UPROPERTY()`
- L62 _private member_ `TArray<TObjectPtr<UPaperTileLayer>> TileLayers_DEPRECATED;` — `UPROPERTY()`
- L66 _private member_ `FLinearColor TileMapColor;` — `UPROPERTY(EditAnywhere, Category=Materials)` — The color of the tile map (multiplied with the per-layer color and passed to the material as a vertex color)
- L70 _private member_ `int32 UseSingleLayerIndex;` — `UPROPERTY(EditAnywhere, Category=Rendering, meta=(EditCondition=bUseSingleLayer))` — The index of the single layer to use if enabled
- L74 _private member_ `bool bUseSingleLayer;` — `UPROPERTY(EditAnywhere, Category=Rendering, meta=(InlineEditConditionToggle))` — Should we draw a single layer?
- L78 _private member_ `int32 NumBatches;` — The number of batches required to render this tile map
- L81 _private member_ `int32 NumTriangles;` — The number of triangles rendered in this tile map
- L87 _public member_ `TObjectPtr<class UPaperTileMap> TileMap;` — `UPROPERTY(Category=Setup, EditAnywhere, BlueprintReadOnly)` — The tile map used by this component
- L92 _public member_ `bool bShowPerTileGridWhenSelected;` — `UPROPERTY(Category=Rendering, EditAnywhere)` — Should this component show a tile grid when the component is selected?
- L96 _public member_ `bool bShowPerLayerGridWhenSelected;` — `UPROPERTY(Category=Rendering, EditAnywhere)` — Should this component show an outline around each layer when the component is selected?
- L100 _public member_ `bool bShowOutlineWhenUnselected;` — `UPROPERTY(Category=Rendering, EditAnywhere)` — Should this component show an outline around the first layer when the component is not selected?
- L104 _public member_ `bool bShowPerTileGridWhenUnselected;` — `UPROPERTY(Category=Rendering, EditAnywhere)` — Should this component show a tile grid when the component is not selected?
- L108 _public member_ `bool bShowPerLayerGridWhenUnselected;` — `UPROPERTY(Category=Rendering, EditAnywhere)` — Should this component show an outline around each layer when the component is not selected?
- L114 _protected prototype_ `void RebuildRenderData(TArray<FSpriteRenderSection>& Sections, TArray<FDynamicMeshVertex>& Vertices);`
- L118 _public prototype_ `virtual void PostInitProperties() override;` — UObject interface
- L119 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L120 _public prototype_ `virtual void PostLoad() override;`
- L122 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L127 _public prototype_ `virtual const UObject* AdditionalStatObject() const override;` — UActorComponent interface
- L131 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L132 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L133 _public prototype_ `virtual class UBodySetup* GetBodySetup() override;`
- L134 _public prototype_ `virtual void GetUsedTextures(TArray<UTexture*>& OutTextures, EMaterialQualityLevel::Type QualityLevel) override;`
- L135 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L136 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L140 _public prototype_ `void CreateNewOwnedTileMap();` — Creates a new tile map internally, replacing the TileMap reference (or dropping the previous owned one)
- L152 _public prototype_ `void CreateNewTileMap(int32 MapWidth = 4, int32 MapHeight = 4, int32 TileWidth = 32, int32 TileHeight = 32, float PixelsPerUnrealUnit = 1.0f, bool bCreateLayer = true);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Creates a new tile map of the specified size, replacing the TileMap reference (or dropping the previous owned one) @param MapWidth Width of the map (in tiles) @param MapHeight Height of the map (in tiles) @param TileWidth Width of one tile (in pixels) @param TileHeight Height of one tile (in pixels) @param bCreateLayer Should an empty layer be created?
- L156 _public prototype_ `bool OwnsTileMap() const;` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Does this component own the tile map (is it instanced instead of being an asset reference)?
- L160 _public prototype_ `virtual bool SetTileMap(UPaperTileMap* NewTileMap);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Change the PaperTileMap used by this instance.
- L164 _public prototype_ `void GetMapSize(int32& MapWidth, int32& MapHeight, int32& NumLayers);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Returns the size of the tile map
- L168 _public prototype_ `FPaperTileInfo GetTile(int32 X, int32 Y, int32 Layer) const;` — `UFUNCTION(BlueprintPure, Category="Sprite", meta=(Layer="0"))` — Returns the contents of a specified tile cell
- L173 _public prototype_ `void SetTile(int32 X, int32 Y, int32 Layer, FPaperTileInfo NewValue);` — `UFUNCTION(BlueprintCallable, Category="Sprite", meta=(Layer="0"))` — Modifies the contents of a specified tile cell (Note: This will only work on components that own their own tile map (OwnsTileMap returns true), you cannot modify standalone tile map assets) Note: Does not update collision by default, call RebuildCollision after all edits have been done in a frame if necessary
- L177 _public prototype_ `void ResizeMap(int32 NewWidthInTiles, int32 NewHeightInTiles);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Resizes the tile map (Note: This will only work on components that own their own tile map (OwnsTileMap returns true), you cannot modify standalone tile map assets)
- L182 _public prototype_ `UPaperTileLayer* AddNewLayer();` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Creates and adds a new layer to the tile map Note: This will only work on components that own their own tile map (OwnsTileMap returns true), you cannot modify standalone tile map assets
- L186 _public prototype_ `FLinearColor GetTileMapColor() const;` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Gets the tile map global color multiplier (multiplied with the per-layer color and passed to the material as a vertex color)
- L190 _public prototype_ `void SetTileMapColor(FLinearColor NewColor);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Sets the tile map global color multiplier (multiplied with the per-layer color and passed to the material as a vertex color)
- L194 _public prototype_ `FLinearColor GetLayerColor(int32 Layer = 0) const;` — `UFUNCTION(BlueprintPure, Category = "Sprite")` — Gets the per-layer color multiplier for a specific layer (multiplied with the tile map color and passed to the material as a vertex color)
- L199 _public prototype_ `void SetLayerColor(FLinearColor NewColor, int32 Layer = 0);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Sets the per-layer color multiplier for a specific layer (multiplied with the tile map color and passed to the material as a vertex color) Note: This will only work on components that own their own tile map (OwnsTileMap returns true), you cannot modify standalone tile map assets
- L202 _public prototype_ `FLinearColor GetWireframeColor() const;` — Returns the wireframe color to use for this component.
- L207 _public prototype_ `void MakeTileMapEditable();` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Makes the tile map asset pointed to by this component editable.  Nothing happens if it was already instanced, but if the tile map is an asset reference, it is cloned to make a unique instance.
- L211 _public prototype_ `FVector GetTileCornerPosition(int32 TileX, int32 TileY, int32 LayerIndex = 0, bool bWorldSpace = false) const;` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Returns the position of the top left corner of the specified tile
- L215 _public prototype_ `FVector GetTileCenterPosition(int32 TileX, int32 TileY, int32 LayerIndex = 0, bool bWorldSpace = false) const;` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Returns the position of the center of the specified tile
- L219 _public prototype_ `void GetTilePolygon(int32 TileX, int32 TileY, TArray<FVector>& Points, int32 LayerIndex = 0, bool bWorldSpace = false) const;` — `UFUNCTION(BlueprintPure, Category="Sprite")` — Returns the polygon for the specified tile (will be 4 or 6 vertices as a rectangle, diamond, or hexagon)
- L224 _public prototype_ `void SetDefaultCollisionThickness(float Thickness, bool bRebuildCollision = true);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Sets the default thickness for any layers that don't override the collision thickness Note: This will only work on components that own their own tile map (OwnsTileMap returns true), you cannot modify standalone tile map assets
- L229 _public prototype_ `void SetLayerCollision(int32 Layer = 0, bool bHasCollision = true, bool bOverrideThickness = true, float CustomThickness = 50.0f, bool bOverrideOffset = false, float CustomOffset = 0.0f, bool bRebuildCollision = true);` — `UFUNCTION(BlueprintCallable, Category="Sprite")` — Sets the collision thickness for a specific layer Note: This will only work on components that own their own tile map (OwnsTileMap returns true), you cannot modify standalone tile map assets
- L233 _public prototype_ `void RebuildCollision();` — `UFUNCTION(BlueprintCallable, Category = "Sprite")` — Rebuilds collision for the tile map
- L237 _public prototype_ `void GetRenderingStats(int32& OutNumTriangles, int32& OutNumBatches) const;` — Returns the rendering stats for this component

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperTileSet.h` (Public)


#### struct `FPaperTileMetadata`  
`struct FPaperTileMetadata`  
_L16-55_
- reflection: `USTRUCT(BlueprintType, meta=(ShowOnlyInnerProperties))`
- desc: Information about a single tile in a tile set
- L23 _public member_ `FName UserDataName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Sprite)` — A tag that can be used for grouping and categorizing (consider using it as the index into a UDataTable asset).
- L27 _public member_ `FSpriteGeometryCollection CollisionData;` — `UPROPERTY(EditAnywhere, Category=Sprite)` — Collision data for the tile
- L32 _public member_ `uint8 TerrainMembership[4];` — `UPROPERTY()` — Indexes into the Terrains array of the owning tile set, in counterclockwise order starting from top-left 0xFF indicates no membership.
- L35 _public function_ `FPaperTileMetadata()`
- L45 _public function_ `bool HasCollision() const` — Does this tile have collision information?
- L51 _public function_ `bool HasMetaData() const` — Does this tile have user-specified metadata?

#### struct `FPaperTileSetTerrain`  
`struct FPaperTileSetTerrain`  
_L59-69_
- reflection: `USTRUCT()`
- desc: Information about a terrain type
- L65 _public member_ `FString TerrainName;` — `UPROPERTY(EditAnywhere, Category=Sprite)`
- L68 _public member_ `int32 CenterTileIndex = 0;` — `UPROPERTY()`

#### class `UPaperTileSet`  
`class UPaperTileSet : public UObject`  
_L77-303_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A tile set is a collection of tiles pulled from a texture that can be used to fill out a tile map. @see UPaperTileMap, UPaperTileMapComponent
- L84 _private member_ `FIntPoint TileSize;` — `UPROPERTY(Category=TileSet, BlueprintReadOnly, EditAnywhere, meta=(UIMin=1, ClampMin=1, AllowPrivateAccess="true"))` — The width and height of a single tile (in pixels)
- L88 _private member_ `TObjectPtr<UTexture2D> TileSheet;` — `UPROPERTY(Category=TileSet, BlueprintReadOnly, EditAnywhere, meta=(DisplayName="Tile Sheet Texture", AllowPrivateAccess="true"))` — The tile sheet texture associated with this tile set
- L92 _private member_ `TArray<TObjectPtr<UTexture>> AdditionalSourceTextures;` — `UPROPERTY(Category = TileSet, EditAnywhere, AssetRegistrySearchable, meta = (DisplayName = "Additional Textures"))` — Additional source textures for other slots
- L96 _private member_ `FIntMargin BorderMargin;` — `UPROPERTY(Category=TileSet, BlueprintReadOnly, EditAnywhere, meta=(UIMin=0, ClampMin=0, AllowPrivateAccess="true"))` — The amount of padding around the border of the tile sheet (in pixels)
- L100 _private member_ `FIntPoint PerTileSpacing;` — `UPROPERTY(Category=TileSet, BlueprintReadOnly, EditAnywhere, meta=(UIMin=0, ClampMin=0, DisplayName="Per-Tile Spacing", AllowPrivateAccess="true"))` — The amount of padding between tiles in the tile sheet (in pixels)
- L104 _private member_ `FIntPoint DrawingOffset;` — `UPROPERTY(Category=TileSet, BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"))` — The drawing offset for tiles from this set (in pixels)
- L109 _private member_ `FLinearColor BackgroundColor;` — `UPROPERTY(Category=TileSet, EditAnywhere, meta=(HideAlphaChannel), meta=(AllowPrivateAccess="true"))` — The background color displayed in the tile set viewer
- L114 _private member_ `int32 WidthInTiles;` — `UPROPERTY()` — Cached width of this tile set (in tiles)
- L118 _private member_ `int32 HeightInTiles;` — `UPROPERTY()` — Cached height of this tile set (in tiles)
- L122 _private member_ `int32 AllocatedWidth;` — `UPROPERTY()` — Allocated width of the per-tile data
- L126 _private member_ `int32 AllocatedHeight;` — `UPROPERTY()` — Allocated height of the per-tile data
- L130 _private member_ `TArray<FPaperTileMetadata> PerTileData;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category=Sprite)` — Per-tile information
- L134 _private member_ `TArray<FPaperTileSetTerrain> Terrains;` — `UPROPERTY()` — Terrain information
- L140 _protected prototype_ `void DestructiveAllocateTileData(int32 NewWidth, int32 NewHeight);` — Reallocates the PerTileData array to the specified size. Note: This is a destructive operation!
- L143 _protected prototype_ `void ReallocateAndCopyTileData();` — Reallocates the per-tile data to match the current (WidthInTiles, HeightInTiles) size, copying over what it can
- L148 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L149 _public prototype_ `virtual void PostLoad() override;`
- L151 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L157 _public prototype_ `int32 GetTileCount() const;` — Returns the number of tiles in this tile set
- L160 _public prototype_ `int32 GetTileCountX() const;` — Returns the number of tiles per row in this tile set
- L163 _public prototype_ `int32 GetTileCountY() const;` — Returns the number of tiles per column in this tile set
- L166 _public prototype_ `FPaperTileMetadata* GetMutableTileMetadata(int32 TileIndex);` — Returns editable tile metadata for the specified tile index
- L169 _public prototype_ `const FPaperTileMetadata* GetTileMetadata(int32 TileIndex) const;` — Returns the tile metadata for the specified tile index
- L172 _public prototype_ `FName GetTileUserData(int32 TileIndex) const;` — Returns the user data name for the specified tile, or NAME_None if there is no user-specified data
- L175 _public prototype_ `bool GetTileUV(int32 TileIndex, FVector2D& Out_TileUV) const;` — Returns the texture-space coordinates of the top left corner of the specified tile index
- L178 _public prototype_ `FIntPoint GetTileUVFromTileXY(const FIntPoint& TileXY) const;` — Returns the texture-space coordinates of the top left corner of the tile at (TileXY.X, TileXY.Y)
- L181 _public prototype_ `FIntPoint GetTileXYFromTextureUV(const FVector2D& TextureUV, bool bRoundUp) const;` — Converts the texture-space coordinates into tile coordinates
- L184 _public prototype_ `bool AddTerrainDescription(FPaperTileSetTerrain NewTerrain);` — Adds a new terrain to this tile set (returns false if the maximum number of terrains has already been reached)
- L187 _public function_ `int32 GetNumTerrains() const` — Returns the number of terrains this tile set has
- L192 _public function_ `FPaperTileSetTerrain GetTerrain(int32 Index) const`
- L195 _public prototype_ `int32 GetTerrainMembership(const FPaperTileInfo& TileInfo) const;` — Returns the terrain type this tile is a member of, or INDEX_NONE if it is not part of a terrain
- L198 _public function_ `static FName GetPerTilePropertyName()`
- L203 _public function_ `inline void SetTileSize(FIntPoint NewSize)` — Sets the size of a tile (in pixels) Note: Does not trigger a rebuild of any tile map components using this tile set
- L209 _public function_ `inline FIntPoint GetTileSize() const` — Returns the size of a tile (in pixels)
- L216 _public function_ `inline void SetTileSheetTexture(UTexture2D* NewTileSheet)` — Sets the tile sheet texture associated with this tile set Note: Does not trigger a rebuild of any tile map components using this tile set
- L222 _public function_ `inline UTexture2D* GetTileSheetTexture() const` — Returns the tile sheet texture associated with this tile set
- L227 _public function_ `inline TArray<UTexture*> GetAdditionalTextures() const`
- L233 _public function_ `inline FIntPoint GetTileSheetAuthoredSize() const` — Returns the imported size of the tile sheet texture (in pixels)
- L239 _public function_ `inline FIntMargin GetMargin() const` — Returns the amount of padding around the border of the tile sheet (in pixels)
- L246 _public function_ `inline void SetMargin(FIntMargin NewMargin)` — Sets the amount of padding around the border of the tile sheet (in pixels) Note: Does not trigger a rebuild of any tile map components using this tile set
- L252 _public function_ `inline FIntPoint GetPerTileSpacing() const` — Returns the amount of padding between tiles in the tile sheet (in pixels)
- L259 _public function_ `inline void SetPerTileSpacing(FIntPoint NewSpacing)` — Sets the amount of padding between tiles in the tile sheet (in pixels) Note: Does not trigger a rebuild of any tile map components using this tile set
- L265 _public function_ `inline FIntPoint GetDrawingOffset() const` — Returns the drawing offset for tiles from this set (in pixels)
- L272 _public function_ `inline void SetDrawingOffset(FIntPoint NewDrawingOffset)` — Sets the drawing offset for tiles from this set (in pixels) Note: Does not trigger a rebuild of any tile map components using this tile set
- L279 _public function_ `inline FLinearColor GetBackgroundColor() const` — Returns the background color displayed in the tile set viewer
- L285 _public function_ `inline void SetBackgroundColor(FLinearColor NewColor)` — Returns the background color displayed in the tile set viewer
- L293 _private member_ `int32 TileWidth_DEPRECATED;` — `UPROPERTY()`
- L296 _private member_ `int32 TileHeight_DEPRECATED;` — `UPROPERTY()`
- L299 _private member_ `int32 Margin_DEPRECATED;` — `UPROPERTY()`
- L302 _private member_ `int32 Spacing_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/SpriteDrawCall.h` (Public)


#### struct `FSpriteDrawCallRecord`  
`struct FSpriteDrawCallRecord`  
_L12-45_
- reflection: `USTRUCT()`
- L18 _public member_ `FVector Destination;` — `UPROPERTY()`
- L21 _public member_ `TObjectPtr<UTexture> BaseTexture;` — `UPROPERTY()`
- L23 _public member_ `FAdditionalSpriteTextureArray AdditionalTextures;`
- L26 _public member_ `FColor Color;` — `UPROPERTY()`
- L30 _public member_ `TArray< FVector4, TInlineAllocator<6> > RenderVerts;` — @TODO: The rest of this struct doesn't need to be properties either, but has to be due to serialization for now Render triangle list (stored as loose vertices)
- L32 _public prototype_ `void BuildFromSprite(const class UPaperSprite* Sprite);`
- L34 _public function_ `FSpriteDrawCallRecord() : Destination(ForceInitToZero) , BaseTexture(nullptr) , Color(FColor::White)`
- L41 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/SpriteEditorOnlyTypes.h` (Public)


#### enum `ESpriteCollisionMode::Type`  
`enum Type : int`  
_L16-25_
- L19 _public enumerator_ `None` — Should this have no collison and not participate in physics?
- L21 _public enumerator_ `Use2DPhysics UMETA(Hidden, DisplayName = "Use 2D Physics (Deprecated)")`
- L24 _public enumerator_ `Use3DPhysics UMETA(DisplayName = "Use 3D Physics")` — Should this have 3D collision geometry and participate in the 3D physics world?

#### enum `ESpriteShapeType`  
`enum class ESpriteShapeType : uint8`  
_L30-40_
- reflection: `UENUM()`
- desc: The type of a shape in a sprite geometry structure
- L33 _public enumerator_ `Box` — Box/Rectangular prism (size defined by BoxSize)
- L36 _public enumerator_ `Circle` — Circle/Sphere (major axis is defined by BoxSize.X, minor axis by BoxSize.Y)
- L39 _public enumerator_ `Polygon` — Custom closed polygon

#### struct `FSpriteGeometryShape`  
`struct FSpriteGeometryShape`  
_L44-141_
- reflection: `USTRUCT()`
- desc: A single piece of geometry (e.g., a polygon which may be convex or concave, a box, or a circle)
- L48 _public function_ `FSpriteGeometryShape() : ShapeType(ESpriteShapeType::Box) , BoxSize(ForceInitToZero) , BoxPosition(ForceInitToZero) , Rotation(0.0f) , bNegativeWinding(false)`
- L60 _public member_ `ESpriteShapeType ShapeType;` — `UPROPERTY(Category=Physics, VisibleAnywhere)` — The type of this piece of geometry
- L64 _public member_ `TArray<FVector2D> Vertices;` — `UPROPERTY(Category=Physics, EditAnywhere)` — Vertices for the polygon (valid for Box and Polygon, but empty for Circle)
- L69 _public member_ `FVector2D BoxSize;` — `UPROPERTY(Category=Physics, VisibleAnywhere)` — Size of the box or major/minor dimensions of the circle Note: Only valid when GeometryType is Box or Circle
- L73 _public member_ `FVector2D BoxPosition;` — `UPROPERTY(Category=Physics, VisibleAnywhere)` — Center of the box or circle, acts as the pivot point for polygons (but may not be at the center of them)
- L77 _public member_ `float Rotation;` — `UPROPERTY(Category=Physics, VisibleAnywhere)` — Rotation of the shape (in degrees)
- L81 _public member_ `bool bNegativeWinding;` — `UPROPERTY(Category=Physics, VisibleAnywhere)` — For Polygon geometry, this tells us if the winding should be negative (CW) regardless of the order in Vertices
- L85 _public function_ `bool IsShapeValid() const` — Is this shape valid (e.g., at least 3 vertices for a polygon)?
- L90 _public function_ `FVector2D ConvertTextureSpaceToShapeSpace(const FVector2D& TextureSpacePoint) const`
- L95 _public function_ `FVector2D ConvertShapeSpaceToTextureSpace(const FVector2D& ShapeSpacePoint) const`
- L101 _public function_ `FVector2D GetPolygonCentroid() const` — Returns the polygon centroid in texture space
- L120 _public function_ `void GetTextureSpaceVertices(TArray<FVector2D>& InOutVertices) const`
- L130 _public function_ `void SetNewPivot(const FVector2D& NewPosInTextureSpace)` — Sets a new pivot and adjusts all vertices to be relative to it

#### enum `ESpritePolygonMode::Type`  
`enum Type : int`  
_L148-164_
- L151 _public enumerator_ `SourceBoundingBox` — Use the bounding box of the source sprite (no optimization)
- L154 _public enumerator_ `TightBoundingBox` — Tighten the bounding box around the sprite to exclude fully transparent areas (the default)
- L157 _public enumerator_ `ShrinkWrapped` — Shrink-wrapped geometry
- L160 _public enumerator_ `FullyCustom` — Fully custom geometry; edited by hand
- L163 _public enumerator_ `Diced` — Diced (split up into smaller squares, including only non-empty ones in the final geometry).  This option is only supported for Render geometry and will be ignored for Collision geometry.

#### struct `FSpriteGeometryCollection`  
`struct FSpriteGeometryCollection`  
_L168-230_
- reflection: `USTRUCT()`
- L174 _public member_ `TArray<FSpriteGeometryShape> Shapes;` — `UPROPERTY(Category=PolygonData, EditAnywhere, AdvancedDisplay)` — List of shapes
- L178 _public member_ `TEnumAsByte<ESpritePolygonMode::Type> GeometryType;` — `UPROPERTY(Category=PolygonData, EditAnywhere)` — The geometry type (automatic / manual)
- L182 _public member_ `int32 PixelsPerSubdivisionX;` — `UPROPERTY(Category=PolygonData, EditAnywhere)` — Size of a single subdivision (in pixels) in X (for Diced mode)
- L186 _public member_ `int32 PixelsPerSubdivisionY;` — `UPROPERTY(Category=PolygonData, EditAnywhere)` — Size of a single subdivision (in pixels) in Y (for Diced mode)
- L190 _public member_ `bool bAvoidVertexMerging;` — `UPROPERTY(Category=PolygonData, EditAnywhere, AdvancedDisplay)` — Experimental: Hint to the triangulation routine that extra vertices should be preserved
- L194 _public member_ `float AlphaThreshold;` — `UPROPERTY(Category=PolygonData, EditAnywhere, AdvancedDisplay)` — Alpha threshold for a transparent pixel (range 0..1, anything equal or below this value will be considered unimportant)
- L198 _public member_ `float DetailAmount;` — `UPROPERTY(Category = PolygonData, EditAnywhere, AdvancedDisplay)` — Amount to detail to consider when shrink-wrapping (range 0..1, 0 = low detail, 1 = high detail)
- L202 _public member_ `float SimplifyEpsilon;` — `UPROPERTY(Category=PolygonData, EditAnywhere, AdvancedDisplay)` — This is the threshold below which multiple vertices will be merged together when doing shrink-wrapping.  Higher values result in fewer vertices.
- L205 _public function_ `FSpriteGeometryCollection() : GeometryType(ESpritePolygonMode::TightBoundingBox) , PixelsPerSubdivisionX(32) , PixelsPerSubdivisionY(32) , bAvoidVertexMerging(false) , AlphaThreshold(0.0f) , DetailAmount(0.5f) , SimplifyEpsilon(2.0f)`
- L216 _public prototype_ `void AddRectangleShape(FVector2D Position, FVector2D Size);`
- L217 _public prototype_ `void AddCircleShape(FVector2D Position, FVector2D Size);`
- L220 _public prototype_ `void Reset();` — Empties this geometry collection, resetting the GeometryType to TightBoundingBox
- L224 _public prototype_ `bool ConditionGeometry();` — Conditions this geometry collection (turning Polygons back to Boxes if they meet the definition of a box, etc...) Returns true if something was modified
- L229 _public prototype_ `void Triangulate(TArray<FVector2D>& Target, bool bIncludeBoxes) const;` — Takes all polygon shapes and generates a list of triangles from them. Output will contain a multiple of 3 points, each set is one triangle. Always ignores circles, but can include or ignore boxes based on bIncludeBoxes.

#### struct `FSpriteGeometryCollisionBuilderBase`  
`struct FSpriteGeometryCollisionBuilderBase`  
_L233-254_
- desc: A helper class for converting one or more FSpriteGeometryCollection objects into a UBodySetup object
- L236 _protected member_ `class UBodySetup* MyBodySetup;`
- L237 _protected member_ `float UnrealUnitsPerPixel;`
- L238 _protected member_ `float CollisionThickness;`
- L239 _protected member_ `float ZOffsetAmount;`
- L240 _protected member_ `ESpriteCollisionMode::Type CollisionDomain;`
- L243 _public prototype_ `FSpriteGeometryCollisionBuilderBase(class UBodySetup* InBodySetup);`
- L245 _public prototype_ `virtual void ProcessGeometry(const FSpriteGeometryCollection& InGeometry);`
- L246 _public prototype_ `virtual void Finalize();`
- L248 _protected prototype_ `void AddBoxCollisionShapesToBodySetup(const FSpriteGeometryCollection& InGeometry);`
- L249 _protected prototype_ `void AddPolygonCollisionShapesToBodySetup(const FSpriteGeometryCollection& InGeometry);`
- L250 _protected prototype_ `void AddCircleCollisionShapesToBodySetup(const FSpriteGeometryCollection& InGeometry);`
- L252 _protected prototype_ `virtual FVector2D ConvertTextureSpaceToPivotSpace(const FVector2D& Input) const;`
- L253 _protected prototype_ `virtual FVector2D ConvertTextureSpaceToPivotSpaceNoTranslation(const FVector2D& Input) const;`

#### struct `FSpriteAssetInitParameters`  
`struct FSpriteAssetInitParameters`  
_L257-317_
- reflection: `USTRUCT()`
- L261 _public function_ `FSpriteAssetInitParameters() : Texture(nullptr) , Offset(ForceInitToZero) , Dimension(ForceInitToZero) , bOverridePixelsPerUnrealUnit(false) , PixelsPerUnrealUnit(1.0f) , DefaultMaterialOverride(nullptr) , AlternateMaterialOverride(nullptr)`
- L273 _public function_ `void SetTextureAndFill(UTexture2D* InTexture)` — Set the texture and the offset/dimension to fully match the specified texture
- L288 _public function_ `void SetPixelsPerUnrealUnit(float NewPixelsPerUU)`
- L295 _public member_ `UTexture2D* Texture;` — The texture to use
- L298 _public member_ `TArray<UTexture*> AdditionalTextures;` — Additional textures to use
- L301 _public member_ `FIntPoint Offset;` — The offset within the texture (in pixels)
- L304 _public member_ `FIntPoint Dimension;` — The dimension of the subregion within the texture (in pixels)
- L307 _public member_ `bool bOverridePixelsPerUnrealUnit;` — Should we apply the PixelsPerUnrealUnit, or leave the value as it was
- L310 _public member_ `float PixelsPerUnrealUnit;` — The scaling factor between pixels and Unreal units (cm) to use (e.g., 0.64 would make a 64 pixel wide sprite take up 100 cm)
- L313 _public member_ `UMaterialInterface* DefaultMaterialOverride;` — The material to override the default value with, if set
- L316 _public member_ `UMaterialInterface* AlternateMaterialOverride;` — The material to override the alternate (opaque) value with, if set

#### enum `ESpritePivotMode::Type`  
`enum Type : int`  
_L322-334_
- L324 _public enumerator_ `Top_Left`
- L325 _public enumerator_ `Top_Center`
- L326 _public enumerator_ `Top_Right`
- L327 _public enumerator_ `Center_Left`
- L328 _public enumerator_ `Center_Center`
- L329 _public enumerator_ `Center_Right`
- L330 _public enumerator_ `Bottom_Left`
- L331 _public enumerator_ `Bottom_Center`
- L332 _public enumerator_ `Bottom_Right`
- L333 _public enumerator_ `Custom`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`
- L14 _namespace_ `namespace ESpriteCollisionMode`
- L146 _namespace_ `namespace ESpritePolygonMode`
- L320 _namespace_ `namespace ESpritePivotMode`

### `Plugins/2D/Paper2D/Source/Paper2D/Classes/TileMapBlueprintLibrary.h` (Public)


#### class `UTileMapBlueprintLibrary`  
`class UTileMapBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L18-38_
- reflection: `UCLASS(meta=(ScriptName="TileMapLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: A collection of utility methods for working with tile map components @see UPaperTileMap, UPaperTileMapComponent
- L25 _public prototype_ `static FName GetTileUserData(FPaperTileInfo Tile);` — `UFUNCTION(BlueprintPure, Category=Sprite)` — Returns the user data name for the specified tile, or NAME_None if there is no user-specified data
- L29 _public prototype_ `static FTransform GetTileTransform(FPaperTileInfo Tile);` — `UFUNCTION(BlueprintPure, Category=Sprite)` — Returns the transform for a tile
- L33 _public prototype_ `static void BreakTile(FPaperTileInfo Tile, int32& TileIndex, UPaperTileSet*& TileSet, bool& bFlipH, bool& bFlipV, bool& bFlipD);` — `UFUNCTION(BlueprintPure, Category=Sprite, meta=(AdvancedDisplay=2))` — Breaks out the information for a tile
- L37 _public prototype_ `static FPaperTileInfo MakeTile(int32 TileIndex, UPaperTileSet* TileSet, bool bFlipH, bool bFlipV, bool bFlipD);` — `UFUNCTION(BlueprintPure, Category=Sprite, meta=(AdvancedDisplay=2))` — Creates a tile from the specified information

### `Plugins/2D/Paper2D/Source/Paper2D/Private/BitmapUtils.h` (Private)


#### struct `FBitmap`  
`struct FBitmap : public FAlphaBitmap`  
_L13-214_
- inherits: `FAlphaBitmap`
- L15 _public function_ `FBitmap(UTexture2D* SourceTexture, int32 AlphaThreshold, uint8 DefaultValue = 0) : FAlphaBitmap(SourceTexture, DefaultValue)`
- L22 _public function_ `FBitmap(int Width, int Height, int DefaultValue = 0) : FAlphaBitmap(Width, Height, DefaultValue)` — Create an empty bitmap
- L29 _public function_ `void FloodFill(FBitmap& MaskBitmap, int StartX, int StartY)` — Performs a flood fill on the target bitmap, with the boundary defined by the current bitmap.
- L62 _public function_ `bool HasOverlappingIsland(FBitmap& MaskBitmap, const FIntPoint& Origin, const FIntPoint& Dimension, FIntPoint& OutFill)` — Walk the border pixels to find any intersecting islands we haven't already filled in the mask bitmap
- L108 _public function_ `bool HasConnectedRect(const int X, const int Y, bool Extend, FIntPoint& OutOrigin, FIntPoint& OutDimension)` — Finds the rect of the contour of the shape clicked on, extended by rectangles to support separated but intersecting islands.
- L153 _public function_ `void ExtractRects(TArray<FIntRect>& OutRects)` — Detects all valid rects in this bitmap

### `Plugins/2D/Paper2D/Source/Paper2D/Private/GroupedSpriteSceneProxy.h` (Private)


#### class `FGroupedSpriteSceneProxy`  
`class FGroupedSpriteSceneProxy final : public FPaperRenderSceneProxy`  
_L17-43_
- inherits: `FPaperRenderSceneProxy`
- L20 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L22 _public prototype_ `FGroupedSpriteSceneProxy(UPaperGroupedSpriteComponent* InComponent);`
- L26 _protected prototype_ `virtual void DebugDrawCollision(const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector, bool bDrawSolid) const override;` — FPaperRenderSceneProxy interface
- L30 _private member_ `const UPaperGroupedSpriteComponent* MyComponent;`
- L33 _private member_ `TSharedPtr<FPerInstanceRenderData, ESPMode::ThreadSafe> PerInstanceRenderData;` — Per instance render data, could be shared with component
- L36 _private member_ `int32 NumInstances;` — Number of instances
- L38 _private member_ `TArray<FMatrix> BodySetupTransforms;`
- L39 _private member_ `TArray<TWeakObjectPtr<UBodySetup>> BodySetups;`
- L42 _private prototype_ `FSpriteRenderSection& FindOrAddSection(FSpriteDrawCallRecord& InBatch, UMaterialInterface* InMaterial);`

### `Plugins/2D/Paper2D/Source/Paper2D/Private/Paper2DPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaper2D, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaper2D, Verbose, All);`

### `Plugins/2D/Paper2D/Source/Paper2D/Private/PaperCustomVersion.h` (Private)


#### struct `FPaperCustomVersion`  
`struct FPaperCustomVersion`  
_L9-78_
- desc: Custom serialization version for all packages containing Paper2D asset types
- L74 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L77 _private function_ `FPaperCustomVersion()`

#### enum `FPaperCustomVersion::Type`  
`enum Type`  
_L11-71_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `FixedNegativeVolume = 1` — Fixed negative volume in UPaperSprite 3D aggregate geometry (caused collision issues)
- L20 _public enumerator_ `RemovedBodyInstance2D = 2` — Removed FBodyInstance2D and moved 2D physics support into Engine (requires regenerating 2D agg geom)
- L23 _public enumerator_ `MovedTileMapDataToSeparateClass = 3` — Moved tile map data out of the component into UPaperTileMap
- L26 _public enumerator_ `MarkSpriteBodySetupToUseSimpleAsComplex = 4` — Marked sprite UBodySetup to use simple as complex, allowing 3D raycasts to succeed
- L29 _public enumerator_ `AddPixelsPerUnrealUnit = 5` — Added PixelsPerUnrealUnit to move away from a 1:1 relationship between pixels and uu
- L32 _public enumerator_ `FixTypoIn3DConvexHullCollisionGeneration = 6` — Fixed typo in convex hull generation code for 3D custom collision
- L35 _public enumerator_ `AddTransactionalToClasses = 7` — Fixed undo issues in several asset types due to missing RF_Transactional flag
- L38 _public enumerator_ `ConvertPaperSpriteComponentToBeMeshComponent = 8` — Converted UPaperSpriteComponent to be derived from UMeshComponent
- L41 _public enumerator_ `AddPivotSnapToPixelGrid = 9` — Added the option to snap pivots to a pixel grid
- L44 _public enumerator_ `ConvertPaperFlipbookComponentToBeMeshComponent = 10` — Converted UPaperFlipbookComponent to be derived from UMeshComponent
- L47 _public enumerator_ `AddDefaultCollisionProfileInSpriteAsset = 11` — Add default BodyInstance setup in the sprite asset
- L50 _public enumerator_ `AddSourceTextureSize = 12` — Add source texture size
- L53 _public enumerator_ `FixIncorrectCollisionOnSourceRotatedSprites = 13` — Fix incorrect collision geometry generation when sprites were rotated in the source texture
- L56 _public enumerator_ `RefactorPolygonStorageToSupportShapes = 14` — Refactor sprite render/collision polygon storage to allow more flexible geometry shapes
- L59 _public enumerator_ `AllowNonUniformPaddingInTileSets = 15` — Change Tile Set margin and padding to allow non-uniform values (also converts TileWidth/TileHeight into TileSize and makes members private)
- L62 _public enumerator_ `FixTangentGenerationForFrontFace = 16` — Fixed the tangent generation for sprites, tile maps, etc... being incorrect for the front face
- L66 _public enumerator_ `FixVertexColorSpace = 17` — Converted Paper2D vertex colors to be treated as linear space instead of sRGB space, and the color picker now matches the result on screen rather than sprites appearing far brighter than they should (note: they are still sent down as a FColor so they have limited precision)
- L69 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L70 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/2D/Paper2D/Source/Paper2D/Private/PaperFlipbookSceneProxy.h` (Private)


#### class `FPaperFlipbookSceneProxy`  
`class FPaperFlipbookSceneProxy final : public FPaperRenderSceneProxy_SpriteBase`  
_L10-16_
- inherits: `FPaperRenderSceneProxy_SpriteBase`
- L13 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L15 _public prototype_ `FPaperFlipbookSceneProxy(const class UPaperFlipbookComponent* InComponent);`

### `Plugins/2D/Paper2D/Source/Paper2D/Private/PaperRenderSceneProxy.h` (Private)


#### struct `FPaperSpriteTangents`  
`struct FPaperSpriteTangents`  
_L33-39_
- desc: A Paper2D sprite vertex.
- L35 _public prototype_ `static void SetTangentsFromPaperAxes();`
- L37 _public member_ `static FPackedNormal PackedNormalX;`
- L38 _public member_ `static FPackedNormal PackedNormalZ;`

#### struct `FSpriteRenderSection`  
`struct FSpriteRenderSection`  
_L44-119_
- L46 _public member_ `UMaterialInterface* Material;`
- L47 _public member_ `UTexture* BaseTexture;`
- L48 _public member_ `FAdditionalSpriteTextureArray AdditionalTextures;`
- L50 _public member_ `int32 VertexOffset;`
- L51 _public member_ `int32 NumVertices;`
- L53 _public function_ `FSpriteRenderSection() : Material(nullptr) , BaseTexture(nullptr) , VertexOffset(INDEX_NONE) , NumVertices(0)`
- L61 _public function_ `class FTexture* GetBaseTextureResource() const`
- L66 _public function_ `bool IsValid() const`
- L72 _public function_ `template <typename VerticesArrayAllocator> void AddVerticesFromDrawCallRecord(const FSpriteDrawCallRecord& Record, int32 StartIndexWithinRecord, int32 NumVertsToCopy, TArray<FDynamicMeshVertex, VerticesArrayAllocator>& Vertices)`
- L103 _public function_ `template <typename VerticesArrayAllocator> inline void AddVertex(float X, float Y, float U, float V, const FVector& Origin, const FColor& Color, TArray<FDynamicMeshVertex, VerticesArrayAllocator>& Vertices)`
- L112 _public function_ `template <typename VerticesArrayAllocator> inline void AddVertex(float X, float Y, float U, float V, const FVector& Origin, const FColor& Color, const FPackedNormal& TangentX, const FPackedNormal& TangentZ, TArray<FDynamicMeshVertex, VerticesArrayAllocator>& Vertices)`

#### class `FPaperRenderSceneProxy`  
`class FPaperRenderSceneProxy : public FPrimitiveSceneProxy`  
_L124-191_
- inherits: `FPrimitiveSceneProxy`
- L127 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L129 _public prototype_ `FPaperRenderSceneProxy(const UPrimitiveComponent* InComponent);`
- L130 _public prototype_ `~FPaperRenderSceneProxy();`
- L133 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;` — FPrimitiveSceneProxy interface.
- L134 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L135 _public prototype_ `virtual uint32 GetMemoryFootprint() const override;`
- L136 _public prototype_ `virtual bool CanBeOccluded() const override;`
- L137 _public prototype_ `virtual bool IsUsingDistanceCullFade() const override;`
- L138 _public prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;`
- L141 _public prototype_ `void SetBodySetup_RenderThread(UBodySetup* NewSetup);`
- L144 _public prototype_ `void SetTransientTextureOverride_RenderThread(const UTexture* InTextureToModifyOverrideFor, UTexture* InOverrideTexture);`
- L148 _protected prototype_ `virtual void GetDynamicMeshElementsForView(const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector) const;`
- L150 _protected prototype_ `bool GetMeshElement(FMeshElementCollector& Collector, int32 SectionIndex, uint8 DepthPriorityGroup, bool bIsSelected, FMeshBatch& OutMeshBatch) const;`
- L152 _protected prototype_ `void GetNewBatchMeshes(const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector) const;`
- L153 _protected prototype_ `void GetNewBatchMeshesPrebuilt(const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector) const;`
- L155 _protected prototype_ `bool IsCollisionView(const FEngineShowFlags& EngineShowFlags, bool& bDrawSimpleCollision, bool& bDrawComplexCollision) const;`
- L157 _protected prototype_ `virtual void DebugDrawCollision(const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector, bool bDrawSolid) const;`
- L158 _protected prototype_ `virtual void DebugDrawBodySetup(const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector, UBodySetup* BodySetup, const FMatrix& GeomTransform, const FLinearColor& CollisionColor, bool bDrawSolid) const;`
- L161 _protected prototype_ `void RecreateCachedRenderData(FRHICommandListBase& RHICmdList);` — Call this if you modify BatchedSections or Vertices after the proxy has already been created
- L163 _protected prototype_ `FSpriteTextureOverrideRenderProxy* GetCachedMaterialProxyForSection(FMeshElementCollector& Collector, int32 SectionIndex, FMaterialRenderProxy* ParentMaterialProxy) const;`
- L166 _protected member_ `TArray<FSpriteRenderSection> BatchedSections;`
- L167 _protected member_ `TArray<FDynamicMeshVertex> Vertices;`
- L169 _protected member_ `mutable UE::FMutex MaterialTextureOverrideProxiesMutex;`
- L170 _protected member_ `mutable TArray<FSpriteTextureOverrideRenderProxy*> MaterialTextureOverrideProxies;`
- L172 _protected member_ `FPaperSpriteVertexBuffer VertexBuffer;`
- L173 _protected member_ `FPaperSpriteVertexFactory VertexFactory;`
- L176 _protected member_ `AActor* Owner;`
- L177 _protected member_ `UBodySetup* MyBodySetup;`
- L179 _protected member_ `uint8 bDrawTwoSided:1;`
- L180 _protected member_ `uint8 bCastShadow:1;`
- L181 _protected member_ `uint8 bSpritesUseVertexBufferPath:1;`
- L184 _protected member_ `FMaterialRelevance MaterialRelevance;` — The view relevance for the associated material
- L187 _protected member_ `FCollisionResponseContainer CollisionResponse;` — The Collision Response of the component being proxied
- L190 _protected prototype_ `UE_EXPAND_IF_WITH_EDITOR(FPaperRenderSceneProxyTextureOverrideMap TextureOverrideList);` — The texture override list

#### class `FPaperRenderSceneProxy_SpriteBase`  
`class FPaperRenderSceneProxy_SpriteBase : public FPaperRenderSceneProxy`  
_L196-206_
- inherits: `FPaperRenderSceneProxy`
- L199 _public prototype_ `FPaperRenderSceneProxy_SpriteBase(const UMeshComponent* InComponent);`
- L201 _public prototype_ `void SetSprite_RenderThread(const FSpriteDrawCallRecord& NewDynamicData, int32 SplitIndex);`
- L204 _public member_ `UMaterialInterface* Material;`
- L205 _public member_ `UMaterialInterface* AlternateMaterial;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PAPER2D_API`
- L25 _typedef_ `typedef TMap<const UTexture*, const UTexture*> FPaperRenderSceneProxyTextureOverrideMap;`
- L27 _macro_ `#define UE_EXPAND_IF_WITH_EDITOR(...) __VA_ARGS__`
- L29 _macro_ `#define UE_EXPAND_IF_WITH_EDITOR(...)`

### `Plugins/2D/Paper2D/Source/Paper2D/Private/PaperSpriteSceneProxy.h` (Private)


#### class `FPaperSpriteSceneProxy`  
`class FPaperSpriteSceneProxy final : public FPaperRenderSceneProxy_SpriteBase`  
_L14-27_
- inherits: `FPaperRenderSceneProxy_SpriteBase`
- L17 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L19 _public prototype_ `FPaperSpriteSceneProxy(UPaperSpriteComponent* InComponent);`
- L22 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;` — FPrimitiveSceneProxy interface
- L26 _protected member_ `const UBodySetup* BodySetup;`

### `Plugins/2D/Paper2D/Source/Paper2D/Private/PaperSpriteVertexBuffer.h` (Private)


#### class `FPaperSpriteVertexBuffer`  
`class FPaperSpriteVertexBuffer : public FVertexBuffer`  
_L18-78_
- inherits: `FVertexBuffer`
- desc: By default this buffer is static, but can be configured to be dynamic prior to initialization.
- L23 _public member_ `FVertexBuffer PositionBuffer;` — Buffers
- L24 _public member_ `FVertexBuffer TangentBuffer;`
- L25 _public member_ `FVertexBuffer TexCoordBuffer;`
- L26 _public member_ `FVertexBuffer ColorBuffer;`
- L27 _public member_ `FIndexBuffer IndexBuffer;`
- L30 _public member_ `FShaderResourceViewRHIRef TangentBufferSRV;` — SRVs for Manual Fetch on platforms that support it
- L31 _public member_ `FShaderResourceViewRHIRef TexCoordBufferSRV;`
- L32 _public member_ `FShaderResourceViewRHIRef ColorBufferSRV;`
- L33 _public member_ `FShaderResourceViewRHIRef PositionBufferSRV;`
- L36 _public member_ `TArray<FPaperSpriteVertex> Vertices;` — Vertex data
- L39 _public function_ `FPaperSpriteVertexBuffer() : bDynamicUsage(true) , NumAllocatedVertices(0)` — Ctor
- L45 _public prototype_ `void SetDynamicUsage(bool bInDynamicUsage);` — Marks this buffer as dynamic, so it gets initialized as so.
- L48 _public prototype_ `void CreateBuffers(FRHICommandListBase& RHICmdList, int32 NumVertices);` — Initializes the buffers with the given number of vertices to accommodate.
- L51 _public prototype_ `void ReleaseBuffers();` — Clear all the buffers currently being used.
- L54 _public prototype_ `void CommitVertexData(FRHICommandListBase& RHICmdList);` — Moves all the PaperVertex data onto the RHI buffers.
- L57 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface
- L58 _public prototype_ `virtual void ReleaseRHI() override;`
- L59 _public prototype_ `virtual void InitResource(FRHICommandListBase& RHICmdList) override;`
- L60 _public prototype_ `virtual void ReleaseResource() override;`
- L64 _public function_ `FORCEINLINE bool CommitRequiresBufferRecreation() const` — True if generating a commit would require a reallocation of the buffers.
- L67 _public function_ `FORCEINLINE bool IsInitialized() const` — Checks if the buffer has been initialized.
- L70 _public function_ `FORCEINLINE const FIndexBuffer* GetIndexPtr() const` — Obtain the index buffer initialized for this buffer.
- L74 _private member_ `bool bDynamicUsage;` — Indicates if this buffer will be configured for dynamic usage.
- L77 _private member_ `int32 NumAllocatedVertices;` — Amount of vertices allocated on the vertex buffer.

#### class `FPaperSpriteVertexFactory`  
`class FPaperSpriteVertexFactory : public FLocalVertexFactory`  
_L84-95_
- inherits: `FLocalVertexFactory`
- L87 _public prototype_ `FPaperSpriteVertexFactory(ERHIFeatureLevel::Type FeatureLevel);`
- L90 _public prototype_ `void Init(FRHICommandListBase& RHICmdList, const FPaperSpriteVertexBuffer* VertexBuffer);` — Initializes this factory with a given vertex buffer.
- L94 _private member_ `const FPaperSpriteVertexBuffer* VertexBuffer;` — Vertex buffer used to initialize this factory.

#### Free symbols / members of external scopes

- L12 _typedef_ `using FPaperSpriteVertex = FDynamicMeshVertex;` — A Paper2D sprite vertex.

### `Plugins/2D/Paper2D/Source/Paper2D/Private/PaperTileMapRenderSceneProxy.h` (Private)


#### class `FPaperTileMapRenderSceneProxy`  
`class FPaperTileMapRenderSceneProxy final : public FPaperRenderSceneProxy`  
_L15-56_
- inherits: `FPaperRenderSceneProxy`
- L18 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L21 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;` — FPrimitiveSceneProxy interface.
- L25 _public prototype_ `static FPaperTileMapRenderSceneProxy* CreateTileMapProxy(const UPaperTileMapComponent* InComponent, TArray<FSpriteRenderSection>*& OutSections, TArray<FDynamicMeshVertex>*& OutVertices);` — Construct a tile map scene proxy
- L28 _public prototype_ `void FinishConstruction_GameThread();` — Call this once the tile map sections/vertices are finished
- L31 _protected prototype_ `FPaperTileMapRenderSceneProxy(const UPaperTileMapComponent* InComponent);`
- L33 _protected prototype_ `void DrawBoundsForLayer(FPrimitiveDrawInterface* PDI, const FLinearColor& Color, int32 LayerIndex) const;`
- L34 _protected prototype_ `void DrawNormalGridLines(FPrimitiveDrawInterface* PDI, const FLinearColor& PerTileColor, const FLinearColor& MultiTileColor, int32 MultiTileGridWidth, int32 MultiTileGridHeight, int32 MultiTileGridOffsetX, int32 MultiTileGridOffsetY, int32 LayerIndex) const;`
- L35 _protected prototype_ `void DrawStaggeredGridLines(FPrimitiveDrawInterface* PDI, const FLinearColor& PerTileColor, const FLinearColor& MultiTileColor, int32 MultiTileGridWidth, int32 MultiTileGridHeight, int32 MultiTileGridOffsetX, int32 MultiTileGridOffsetY, int32 LayerIndex) const;`
- L36 _protected prototype_ `void DrawHexagonalGridLines(FPrimitiveDrawInterface* PDI, const FLinearColor& PerTileColor, const FLinearColor& MultiTileColor, int32 MultiTileGridWidth, int32 MultiTileGridHeight, int32 MultiTileGridOffsetX, int32 MultiTileGridOffsetY, int32 LayerIndex) const;`
- L41 _protected member_ `bool bShowPerTileGridWhenSelected;`
- L42 _protected member_ `bool bShowPerTileGridWhenUnselected;`
- L43 _protected member_ `bool bShowPerLayerGridWhenSelected;`
- L44 _protected member_ `bool bShowPerLayerGridWhenUnselected;`
- L45 _protected member_ `bool bShowOutlineWhenUnselected;`
- L49 _protected member_ `const UPaperTileMap* TileMap;` — @TODO: Not thread safe
- L52 _protected member_ `const int32 OnlyLayerIndex;` — The only layer to draw, or INDEX_NONE if the filter is unset
- L55 _protected member_ `const float WireDepthBias;` — Slight depth bias so that the wireframe grid overlay doesn't z-fight with the tiles themselves

### `Plugins/2D/Paper2D/Source/Paper2D/Public/AlphaBitmap.h` (Public)


#### struct `FAlphaBitmap`  
`struct FAlphaBitmap`  
_L10-363_
- L12 _public function_ `FAlphaBitmap(UTexture* SourceTexture, uint8 InDefaultValue = 0) : Width(0) , Height(0) , DefaultValue(InDefaultValue)`
- L20 _public function_ `void ExtractFromTexture(UTexture* SourceTexture)`
- L74 _public function_ `FAlphaBitmap(int InWidth, int InHeight, int InDefaultValue = 0) : Width(InWidth) , Height(InHeight) , DefaultValue(InDefaultValue)` — Create an empty bitmap
- L83 _public function_ `bool IsValid() const`
- L88 _public function_ `uint8 GetPixel(int X, int Y) const`
- L100 _public function_ `void SetPixel(int X, int Y, uint8 Value)`
- L108 _public function_ `void ClearToDefaultValue()`
- L117 _public function_ `bool IsColumnEqual(int X, int Y0, int Y1, int Target) const`
- L129 _public function_ `bool IsRowEqual(int X0, int X1, int Y, int Target) const`
- L142 _public function_ `bool IsRegionEqual(int32 X0, int32 Y0, int32 X1, int32 Y1, int32 Target) const` — Is the rectangle empty (X0..X1, Y0..Y1 inclusive)
- L152 _public function_ `bool IsColumnEmpty(int X, int Y0, int Y1) const`
- L157 _public function_ `bool IsRowEmpty(int X0, int X1, int Y) const`
- L163 _public function_ `bool IsRegionEmpty(int32 X0, int32 Y0, int32 X1, int32 Y1)` — Is the rectangle empty (X0..X1, Y0..Y1 inclusive)
- L169 _public function_ `void GetTightBounds(FIntPoint& OutOrigin, FIntPoint& OutDimension) const` — Returns the tight bounding box around pixels that are not 0
- L179 _public function_ `void TightenBounds(FIntPoint& InOutOrigin, FIntPoint& InOutDimension) const` — Returns the tight bounding box around pixels that are not 0
- L210 _public function_ `void DrawRectOutline(int StartX, int StartY, int InWidth, int InHeight)` — Sets pixels to 1 marking the rectangle outline
- L228 _public function_ `void FillRect(int StartX, int StartY, int InWidth, int InHeight)`
- L244 _public function_ `bool FoundClosestValidPoint(int StartX, int StartY, const int MaxAllowedSearchDistance, FIntPoint& OutHitPoint) const` — Wind through the bitmap from StartX, StartY to find the closest hit point
- L298 _public function_ `void ThresholdImage(int32 AlphaThreshold)`
- L314 _public function_ `void ThresholdImageBothWays(int32 LowAlphaThreshold, int32 HighAlphaThreshold)` — Flushes values smaller or equal to LowAlphaThreshold to 0, and values greater or equal to HighAlphaThreshold to 255
- L330 _public function_ `void AnalyzeImage(int32 StartX, int32 StartY, int32 InWidth, int32 InHeight, bool& bOutHasZeros, bool& bOutHasIntermediateValues) const` — Checks the image to determine if it is suitable for opaque, masked or translucent rendering
- L359 _public member_ `TArray<uint8> RawData;`
- L360 _public member_ `int32 Width;`
- L361 _public member_ `int32 Height;`
- L362 _public member_ `uint8 DefaultValue;`

### `Plugins/2D/Paper2D/Source/Paper2D/Public/MaterialExpressionSpriteTextureSampler.h` (Public)


#### class `UMaterialExpressionSpriteTextureSampler`  
`class UMaterialExpressionSpriteTextureSampler : public UMaterialExpressionTextureSampleParameter2D`  
_L14-39_
- reflection: `UCLASS(MinimalAPI, hideCategories=(MaterialExpressionTextureSampleParameter, MaterialExpressionSpriteTextureSampler))`
- inherits: `UMaterialExpressionTextureSampleParameter2D`
- desc: This is a texture sampler 2D with a special automatically defined parameter name. The texture specified here will be replaced by the SourceTexture or an AdditionalSourceTextures entry of a Paper2D sprite if this material is used on a sprite.
- L20 _private member_ `bool bSampleAdditionalTextures;` — `UPROPERTY(EditAnywhere, Category=Paper2D)` — Is this a sampler for the default SourceTexture or the AdditionalSourceTextures list?
- L24 _private member_ `int32 AdditionalSlotIndex;` — `UPROPERTY(EditAnywhere, Category=Paper2D, meta=(EditCondition=bSampleAdditionalTextures))` — This is the slot index into the AdditionalSourceTextures array
- L28 _private member_ `FText SlotDisplayName;` — `UPROPERTY(EditAnywhere, Category=Paper2D)` — Friendly label for the texture slot, displayed in the Sprite Editor if not empty
- L32 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L33 _private prototype_ `virtual FText GetKeywords() const override;`
- L34 _private prototype_ `virtual bool CanRenameNode() const override;`
- L35 _private prototype_ `virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override;`
- L36 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2D_API`

### `Plugins/2D/Paper2D/Source/Paper2D/Public/Paper2DModule.h` (Public)


#### class `IPaper2DModuleInterface`  
`class IPaper2DModuleInterface : public IModuleInterface`  
_L16-18_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L11 _macro_ `#define PAPER2D_MODULE_NAME "Paper2D"`
- L27 _externvar_ `extern FVector PaperAxisX;` — The 3D vector that corresponds to the sprite X axis
- L30 _externvar_ `extern FVector PaperAxisY;` — The 3D vector that corresponds to the sprite Y axis
- L33 _externvar_ `extern FVector PaperAxisZ;` — The 3D vector that corresponds to the sprite Z axis
- L38 _delegate_ `DECLARE_STATS_GROUP(TEXT("Paper2D"), STATGROUP_Paper2D, STATCAT_Adv`
- L39 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SetSprite (RT)"), STAT_PaperRender_SetSpriteRT, STATGROUP_Paper2D,`
