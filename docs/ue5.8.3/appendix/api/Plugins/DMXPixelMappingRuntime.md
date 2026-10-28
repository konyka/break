# Plugins / DMXPixelMappingRuntime

- module root: `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime`
- headers: 26; symbols: 664
- symbol kinds: class=25, delegate=7, enum=7, enumerator=34, function=73, member=208, namespace=15, prototype=286, struct=3, typedef=6
- PrivateDependencyModuleNames: DMXPixelMappingCore, DMXPixelMappingEditorWidgets, DMXProtocol, DMXRuntime, Engine, Slate, SlateCore, UMG, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DMXPixelMappingRenderer, DMXRuntime, RHI

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Internal/ColorSpace/DMXPixelMappingColorSpace_RGBCMY.h` (Internal)


#### enum `EDMXPixelMappingOutputColorSpace_RGBCMY`  
`enum class EDMXPixelMappingOutputColorSpace_RGBCMY : uint8`  
_L14-21_
- reflection: `UENUM(BlueprintType)`
- desc: The color space of the DMX output
- L16 _public enumerator_ `sRGB UMETA(DisplayName = "sRGB / Rec709")`
- L17 _public enumerator_ `Rec2020`
- L18 _public enumerator_ `P3DCI`
- L19 _public enumerator_ `P3D65`
- L20 _public enumerator_ `Plasa UMETA(DisplayName = "PLASA RGB - ANSI E1.54")`

#### enum `EDMXPixelMappingGamma_RGBCMY`  
`enum class EDMXPixelMappingGamma_RGBCMY : uint8`  
_L25-30_
- reflection: `UENUM(BlueprintType)`
- desc: The gamma mode of the DMX output
- L27 _public enumerator_ `Linear`
- L28 _public enumerator_ `AsOutputColorSpace`
- L29 _public enumerator_ `Custom`

#### enum `EDMXPixelMappingLuminanceType_RGBCMY`  
`enum class EDMXPixelMappingLuminanceType_RGBCMY : uint8`  
_L34-40_
- reflection: `UENUM(BlueprintType)`
- desc: Defines how the luminance channel (typically Dimmer) is generated
- L36 _public enumerator_ `FromColor`
- L37 _public enumerator_ `Constant`
- L38 _public enumerator_ `FromAlpha`
- L39 _public enumerator_ `None`

#### class `UDMXPixelMappingColorSpace_RGBCMY`  
`class UDMXPixelMappingColorSpace_RGBCMY : public UDMXPixelMappingColorSpace`  
_L43-145_
- reflection: `UCLASS(meta = (DisplayName = "RGB / CMY"))`
- inherits: `UDMXPixelMappingColorSpace`
- L50 _public prototype_ `UDMXPixelMappingColorSpace_RGBCMY();` — Constructor
- L53 _public prototype_ `virtual void SetRGBA(const FLinearColor& InColor) override;`
- L58 _public member_ `EDMXPixelMappingOutputColorSpace_RGBCMY PixelMappingOutputColorSpace = EDMXPixelMappingOutputColorSpace_RGBCMY::sRGB;` — `UPROPERTY(EditAnywhere, Category = "Color Space", Meta = (DisplayName = "Output Color Space"))` — The color space to use
- L62 _public member_ `EDMXPixelMappingGamma_RGBCMY OutputGamma = EDMXPixelMappingGamma_RGBCMY::AsOutputColorSpace;` — `UPROPERTY(EditAnywhere, Category = "Color Space")` — Applies Gamma correction to the output DMX Values
- L66 _public member_ `float CustomGamma = 2.2f;` — `UPROPERTY(EditAnywhere, Category = "Color Space", Meta = (UIMin = 0.0, UIMax = 4.0, EditCondition = "OutputGamma == EDMXPixelMappingGamma_RGBCMY::Custom", EditConditionHides))` — The custom Gamma, whereas OutColor = Pow(InColor, 1 / CustomGamma)
- L70 _public member_ `bool bSendCyan = false;` — `UPROPERTY(EditAnywhere, Category = "RGB")` — If set, converts Red to Cyan
- L74 _public member_ `bool bSendMagenta = false;` — `UPROPERTY(EditAnywhere, Category = "RGB")` — If set, converts Green to Magenta
- L78 _public member_ `bool bSendYellow = false;` — `UPROPERTY(EditAnywhere, Category = "RGB")` — If set, converts Blue to Yellow
- L82 _public member_ `FDMXAttributeName RedAttribute;` — `UPROPERTY(EditAnywhere, Category = "RGB")` — Attribute sent for Red
- L86 _public member_ `FDMXAttributeName GreenAttribute;` — `UPROPERTY(EditAnywhere, Category = "RGB")` — Attribute sent for Green
- L90 _public member_ `FDMXAttributeName BlueAttribute;` — `UPROPERTY(EditAnywhere, Category = "RGB")` — Attribute sent for Blue
- L94 _public member_ `EDMXPixelMappingLuminanceType_RGBCMY LuminanceType = EDMXPixelMappingLuminanceType_RGBCMY::FromColor;` — `UPROPERTY(EditAnywhere, Category = "Luminance")` — Adds a Dimmer Attribute
- L98 _public member_ `FDMXAttributeName LuminanceAttribute;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (EditConditionHides, EditCondition = "LuminanceType != EDMXPixelMappingLuminanceType_RGBCMY::None"))` — Attribute sent for the generated Luminance
- L102 _public member_ `float Luminance = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::Constant"))` — Luminance used when Luminance Type is set to 'Set Value'
- L106 _public member_ `float MinLuminance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromColor || LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromAlpha"))` — Min Luminance used when Luminance Type is set to 'From White' or 'From Alpha'
- L110 _public member_ `float MaxLuminance = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromColor || LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromAlpha"))` — Max Luminance used when Luminance Type is set to 'From White' or 'From Alpha'
- L114 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L115 _protected prototype_ `virtual void PostLoad() override;`
- L117 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L123 _private prototype_ `void UpdateColorSpaceAndTransform();` — Updates the ColorSpace and ColorSpaceTransform members
- L126 _private prototype_ `void EncodeGammaCorrection(EDMXPixelMappingOutputColorSpace_RGBCMY InPixelMappingOutputColorSpaceEnum, FLinearColor& InOutColor);` — Applies gamma correction according to the color space to the Color.
- L129 _private prototype_ `void EncodeGammaCorrection(float CustomGamma, FLinearColor& InOutColor);` — Applies a custom gamma correction to the Color. OutColor = Pow(InColor, CustomGamma)
- L132 _private prototype_ `float EncodeRec2020(float InValue) const;` — Encodes Rec2020 in a linear color
- L135 _private prototype_ `UE::Color::EColorSpace ConvertToOutputColorSpaceEnum(EDMXPixelMappingOutputColorSpace_RGBCMY InPixelMappingOutputColorSpaceEnum) const;` — Gets the EColorSpace enum given the current Output Color Space Enum
- L138 _private member_ `UE::Color::FColorSpace InputColorSpace;` — The input color space instance
- L141 _private member_ `UE::Color::FColorSpace OutputColorSpace;` — The output color space instance
- L144 _private member_ `TUniquePtr<UE::Color::FColorSpaceTransform> ColorSpaceTransform;` — The color space transform instance

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Internal/ColorSpace/DMXPixelMappingColorSpace_XYZ.h` (Internal)


#### class `UDMXPixelMappingColorSpace_XYZ`  
`class UDMXPixelMappingColorSpace_XYZ : public UDMXPixelMappingColorSpace`  
_L15-64_
- reflection: `UCLASS(meta = (DisplayName = "CIE 1931 XYZ"))`
- inherits: `UDMXPixelMappingColorSpace`
- L22 _public prototype_ `UDMXPixelMappingColorSpace_XYZ();` — Constructor
- L25 _public prototype_ `virtual void SetRGBA(const FLinearColor& InColor) override;`
- L33 _public member_ `float CustomGamma = 1.f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Color Space")` — Output gamma of the Luminance, computed in xyY space whereas Y = Pow(Y, 1 / OutputGamma). CIE 1931 XYZ is linear gamma so typically no gamma should be applied.
- L37 _public member_ `FDMXAttributeName XAttribute;` — `UPROPERTY(EditAnywhere, Category = "XYZ", Meta = (DisplayName = "X Attribute"))` — Attribute sent for X
- L41 _public member_ `FDMXAttributeName ZAttribute;` — `UPROPERTY(EditAnywhere, Category = "XYZ", Meta = (DisplayName = "Z Attribute"))` — Attribute sent for Z
- L45 _public member_ `FDMXAttributeName LuminanceAttribute;` — `UPROPERTY(EditAnywhere, Category = "XYZ")` — Attribute sent for Y
- L49 _public member_ `float MinLuminance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromWhite || LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromAlpha"))` — Min Luminance
- L53 _public member_ `float MaxLuminance = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromWhite || LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromAlpha"))` — Max Luminance
- L58 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L63 _private member_ `UE::Color::FColorSpace SRGBColorSpace;` — Cached sRGB color space, to avoid instantiating on each conversion

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Internal/ColorSpace/DMXPixelMappingColorSpace_xyY.h` (Internal)


#### class `UDMXPixelMappingColorSpace_xyY`  
`class UDMXPixelMappingColorSpace_xyY : public UDMXPixelMappingColorSpace`  
_L14-71_
- reflection: `UCLASS(meta = (DisplayName = "CIE 1931 xyY"))`
- inherits: `UDMXPixelMappingColorSpace`
- L21 _public prototype_ `UDMXPixelMappingColorSpace_xyY();` — Constructor
- L24 _public prototype_ `virtual void SetRGBA(const FLinearColor& InColor) override;`
- L32 _public member_ `float CustomGamma = 1.f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Color Space")` — Output gamma of the Y component in xyY space whereas Y = Pow(Y, 1 / CustomGamma). CIE 1931 xyY is linear gamma so typically no gamma should be applied.
- L36 _public member_ `FDMXAttributeName XAttribute;` — `UPROPERTY(EditAnywhere, Category = "XY", Meta = (DisplayName = "x Attribute"))` — Attribute sent for x
- L40 _public member_ `FDMXAttributeName YAttribute;` — `UPROPERTY(EditAnywhere, Category = "XY", Meta = (DisplayName = "y Attribute"))` — Attribute sent for y
- L48 _public member_ `float ColorSpaceRange = .8f;` — `UPROPERTY(EditAnywhere, Category = "XY", Meta = (ClampMin = 0.1, ClampMax = 2.0, UIMin = 0.1, UIMax = 1.0, DisplayName = "Color Space Range"))` — Sets the range of the xyY color space. A value of 1.0 corresponds to CIE 1931 xyY. Many hardware lights use a more narrow range, typically 0.8.
- L52 _public member_ `FDMXAttributeName LuminanceAttribute;` — `UPROPERTY(EditAnywhere, Category = "Luminance")` — Attribute sent for Y
- L56 _public member_ `float MinLuminance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromWhite || LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromAlpha"))` — Min Luminance
- L60 _public member_ `float MaxLuminance = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Luminance", Meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0, EditConditionHides, EditCondition = "LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromWhite || LuminanceType == EDMXPixelMappingLuminanceType_RGBCMY::FromAlpha"))` — Max Luminance
- L65 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _private member_ `UE::Color::FColorSpace SRGBColorSpace;` — Cached sRGB color space, to avoid instantiating on each conversion

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Internal/Components/DMXPixelMappingComponentGeometryCache.h` (Internal)


#### struct `FDMXPixelMappingComponentGeometryCache`  
`struct FDMXPixelMappingComponentGeometryCache`  
_L18-87_
- reflection: `USTRUCT()`
- desc: Caches pixel mapping component geometry. Useful for performance and to propagnonate changes incrementally to children. The outer îs expected to be a DMXPixelMappingOutputComponent or a derived class.
- L24 _public prototype_ `void Initialize(UDMXPixelMappingOutputComponent* InOwner, const FVector2D& InPosition, const FVector2D& InSize, double InRotation);` — Initializes the geometry cache
- L27 _public prototype_ `FVector2D SetPositionAbsolute(const FVector2D& NewPosition);` — Sets the absoulte position, returns the translation between new and previous position.
- L28 _public function_ `const FVector2D& GetPositionAbsolute() const`
- L31 _public prototype_ `FVector2D SetPositionRotatedAbsolute(const FVector2D& NewPositionRotated);` — Sets the absoulte position, rotated. Returns the translation between new and previous position.
- L32 _public prototype_ `FVector2D GetPositionRotatedAbsolute() const;`
- L39 _public prototype_ `void SetSizeAbsolute(const FVector2D& InNewSize, FVector2D& OutDeltaSize, FVector2D& OutDeltaPosition);` — Sets the absoulte size, outputs the delta size and delta position. Delta position occurs if the rectangle is rotated, as its pivot is in the center, not the top left edge. To keep it in rotated position, the position needs be updated.
- L42 _public prototype_ `void SetSizeAbsolute(const FVector2D& InNewSize);` — Sets the absolute size without outputting deltas
- L43 _public function_ `const FVector2D& GetSizeAbsolute() const`
- L46 _public prototype_ `double SetRotationAbsolute(double NewRotation);` — Sets the absoulte rotation, returns the delta to the previous rotation.
- L47 _public function_ `double GetRotationAbsolute() const`
- L50 _public prototype_ `void GetSinCos(double& OutSin, double& OutCos) const;` — Returns rotation as sin cos
- L53 _public prototype_ `void GetEdgesAbsolute(FVector2D& A, FVector2D& B, FVector2D& C, FVector2D& D) const;` — Returns the edges of the rectangle, absolute, rotated, clockwise order
- L56 _public prototype_ `void PropagonatePositionChangesToChildren(const FVector2D& Translation);` — Propagonates position changes to children.
- L59 _public prototype_ `void PropagonateSizeChangesToChildren(const FVector2D& DeltaSize, const FVector2D& DeltaPosition);` — Propagonates size changes to children.
- L62 _public prototype_ `void PropagonateRotationChangesToChildren(double DeltaRotation);` — Propagonates rotation changes to children.
- L67 _private member_ `FVector2D Position = FVector2D::ZeroVector;` — `UPROPERTY(Transient)` — Position before it was changed
- L71 _private member_ `FVector2D Size = FVector2D::ZeroVector;` — `UPROPERTY(Transient)` — Size before it was changed
- L75 _private member_ `double Rotation = 0.f;` — `UPROPERTY(Transient)` — Rotation before it was changed
- L79 _private member_ `double Sin = 0.f;` — `UPROPERTY(Transient)` — Cached Sine of Rotation. Preferable over non-reflected FQuat2D etc. for undo/redo purpose.
- L83 _private member_ `double Cos = 1.f;` — `UPROPERTY(Transient)` — Cached Cosine of Rotation. Preferable over non-reflected FQuat2D etc. for undo/redo purpose.
- L86 _private member_ `TWeakObjectPtr<UDMXPixelMappingOutputComponent> WeakOwner;` — The owner of this cache

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Internal/DMXPixelMappingActor.h` (Internal)


#### class `ADMXPixelMappingActor`  
`class ADMXPixelMappingActor : public AActor`  
_L15-89_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `AActor`
- desc: Actor class for DMX Pixel Mapping
- L22 _public prototype_ `ADMXPixelMappingActor();` — Constructor
- L25 _public prototype_ `void SetPixelMapping(UDMXPixelMapping* InPixelMapping);` — Sets the Pixel Mapping used in this actor
- L29 _public prototype_ `void StartSendingDMX();` — `UFUNCTION(BlueprintCallable, Category = "DMX Pixel Mapping")` — Starts sending DMX
- L33 _public prototype_ `void StopSendingDMX();` — `UFUNCTION(BlueprintCallable, Category = "DMX Pixel Mapping")` — Stop sending DMX.
- L37 _public prototype_ `void PauseSendingDMX();` — `UFUNCTION(BlueprintCallable, Category = "DMX Pixel Mapping")` — Pause sending DMX
- L41 _public prototype_ `bool IsSendingDMX() const;` — `UFUNCTION(BlueprintPure, Category = "DMX Pixel Mapping")` — Returns true if the asset is playing DMX
- L45 _public prototype_ `void SetStopMode(EDMXPixelMappingResetDMXMode ResetMode);` — `UFUNCTION(BlueprintCallable, Category = "DMX Pixel Mapping")` — Sets how the pixel mapping asset resets the channels it sends to when Stop Sending DMX is called
- L49 _protected prototype_ `virtual void PostLoad() override;`
- L50 _protected prototype_ `virtual void BeginPlay() override;`
- L51 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L53 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L60 _private prototype_ `void ApplySendDMXInEditorState();` — Applies the play in editor state. Enables send when auto activate is on, send DMX in editor is enabled and not currently playing
- L65 _private member_ `TObjectPtr<UDMXPixelMapping> PixelMapping;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Pixel Mapping")` — The pixel mapping used in this actor
- L73 _private member_ `bool bAutoActivate = true;` — `UPROPERTY(EditAnywhere, Category = "DMX Pixel Mapping")` — True if the pixel mapping actor auto activates. If Send DMX in Editor is disabled, starts to send DMX on begin play. If Send DMX in Editor is enabled, it will start to send DMX when the level is loaded in editor.
- L78 _private member_ `bool bSendDMXInEditor = false;` — `UPROPERTY(EditAnywhere, Category = "DMX Pixel Mapping", Meta = (DisplayName = "Send DMX in Editor"))` — True if the pixel mapping should send DMX data in editor
- L83 _private member_ `bool bIsPlayInWorld = false;` — True while the actor plays in a world
- L88 _private member_ `TObjectPtr<USceneComponent> RootSceneComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Actor", AdvancedDisplay, Meta = (AllowPrivateAccess = true))` — Scene component to make the actor easily visible in Editor

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Internal/DMXPixelMappingMainStreamObjectVersion.h` (Internal)


#### struct `FDMXPixelMappingMainStreamObjectVersion`  
`struct FDMXPixelMappingMainStreamObjectVersion`  
_L9-47_
- desc: Custom serialization version for changes to DMX Pixel Mapping Objects in the Main Stream
- L43 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L46 _private function_ `FDMXPixelMappingMainStreamObjectVersion()`

#### enum `FDMXPixelMappingMainStreamObjectVersion::Type`  
`enum Type`  
_L11-40_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 4.26
- L17 _public enumerator_ `ChangePixelMappingMatrixComponentToFixturePatchReference` — Update DMXPixelMappingMatrixComponent to no longer use a custom MatrixFixturePatchRef, but the default EntityFixturePatchRef one.
- L20 _public enumerator_ `UseWeakPtrForPixelMappingComponentParent` — Update DMXPixelMappingBaseComponent to store the parent as a weak ptr
- L23 _public enumerator_ `LockRendererComponentsThatUseTextureInDesigner` — Update DMXPixelMappingRendererComponent to lock those components that use a texture in designer to trigger the edit condition of the size property
- L26 _public enumerator_ `UseDMXPixelMappingColorSpace` — Update DMXPixelMappingFixtureGroupItemComponent and DMXPixelMappingMatrixCellComponent to use DMXPixelMappingColorSpace
- L29 _public enumerator_ `RendererComponentHoldsLayoutRect` — The renderer component now holds the layout rect, so its children can be layout out relative to the current texture size
- L32 _public enumerator_ `DMXOutputAppliesGammaCorrection` — 5.5: Color spaces now apply a gamma correction
- L35 _public enumerator_ `PerPixelMappingResetDMXMode` — 5.6: Each pixel mapping holds its own reset DMX mode
- L38 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L39 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Private/LayoutScripts/DMXPixelMappingLayoutScript_GridLayout.h` (Private)


#### class `UDMXPixelMappingLayoutScript_GridLayout`  
`class UDMXPixelMappingLayoutScript_GridLayout : public UDMXPixelMappingLayoutScript`  
_L18-70_
- reflection: `UCLASS(DisplayName = "Grid Layout", AutoExpandCategories = ("Layout Settings"))`
- inherits: `UDMXPixelMappingLayoutScript`
- desc: Arranges the components in a grid
- L27 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `virtual void Layout_Implementation(const TArray<FDMXPixelMappingLayoutToken>& InTokens, TArray<FDMXPixelMappingLayoutToken>& OutTokens);`
- L33 _public prototype_ `virtual void SetNumTokens(int32 NewNumTokens) override;`
- L38 _public member_ `int32 Columns = 1;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — Num Columns in the grid
- L42 _public member_ `int32 Rows = 1;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — Num Rows in the grid
- L46 _public member_ `float Padding = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings", Meta = (ClampMin = "0", UIMin = "0"))` — Padding of the cells
- L50 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — Horizontal text alignment
- L54 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — Vertical text alignment
- L58 _public member_ `EDMXPixelMappingDistribution Distribution = EDMXPixelMappingDistribution::TopLeftToRight;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — How cells are distributed, compared to their previous distribution
- L62 _private prototype_ `void ClampColumns();` — Clamps colums to rows given num tokens
- L65 _private prototype_ `void ClampRows();` — Clamps colums to rows given num tokens
- L69 _private member_ `bool bAutoSizeMode = true;` — `UPROPERTY()` — Auto-size is enabled when either horizontal or vertical aligmenet are set to fill

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Private/LayoutScripts/DMXPixelMappingLayoutScript_LayoutByMVR.h` (Private)


#### enum `EDMXPixelMappingMVRProjectionPlane`  
`enum class EDMXPixelMappingMVRProjectionPlane : uint8`  
_L20-28_
- reflection: `UENUM(BlueprintType)`
- desc: Defines which MVR coordinates are projected to a Pixel Mapping Layout
- L22 _public enumerator_ `XY`
- L23 _public enumerator_ `XZ`
- L24 _public enumerator_ `YZ`
- L25 _public enumerator_ `YX`
- L26 _public enumerator_ `ZX`
- L27 _public enumerator_ `ZY`

#### class `UDMXPixelMappingLayoutScript_LayoutByMVR`  
`class UDMXPixelMappingLayoutScript_LayoutByMVR : public UDMXPixelMappingLayoutScript`  
_L32-67_
- reflection: `UCLASS(DisplayName = "Layout by MVR", AutoExpandCategories = ("Layout Settings"))`
- inherits: `UDMXPixelMappingLayoutScript`
- desc: Arranges the components given their coordinates in the DMX Library's MVR specs
- L40 _public prototype_ `virtual void Layout_Implementation(const TArray<FDMXPixelMappingLayoutToken>& InTokens, TArray<FDMXPixelMappingLayoutToken>& OutTokens);`
- L45 _public member_ `EDMXPixelMappingMVRProjectionPlane ProjectionPlane;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — Which axis or axes are projected to the Pixel Mapping Layout
- L49 _public member_ `FMargin MarginCentimeters;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings")` — Margin of the MVR fixtures, in centimeters
- L53 _public member_ `float ComponentSizePixels = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Layout Settings", Meta = (ClampMin = "1", UIMin = "1"))` — Size each component should take, in pixels
- L57 _private prototype_ `TMap<const UDMXMVRFixtureNode*, FDMXPixelMappingLayoutToken> GetFixtureNodeToLayoutTokenMap(const TArray<FDMXPixelMappingLayoutToken>& InTokens) const;` — Returns a map of Fixture Nodes and the Layout Tokens they correspond to
- L60 _private prototype_ `UDMXLibrary* GetDMXLibrary(const TArray<FDMXPixelMappingLayoutToken>& InTokens) const;` — Returns the DMX Library the components of this script use
- L63 _private prototype_ `UDMXEntityFixturePatch* GetFixturePatch(const FDMXPixelMappingLayoutToken& Token) const;` — Returns the Fixture Patch of the Token, or nullptr if the token has no patch
- L66 _private prototype_ `FVector2D GetPosition2DFromTransform(const FTransform& Transform) const;` — Returns XY in 2D space from transform, depending on ProjectionAxes

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Private/Modulators/DMXModulator_PixelMappingFrameDelay.h` (Private)


#### class `UDMXModulator_PixelMappingFrameDelay`  
`class UDMXModulator_PixelMappingFrameDelay : public UDMXModulator`  
_L14-76_
- reflection: `UCLASS(NotBlueprintable, DisplayName = "DMX Modulator Constant Frame Delay", AutoExpandCategories = ("DMX"))`
- inherits: `UDMXModulator`
- desc: Delays the incoming singal by number of Delay Frames. Only useful for PixelMapping and constant frame rates.
- L22 _public prototype_ `virtual void Modulate_Implementation(UDMXEntityFixturePatch* FixturePatch, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues, TMap<FDMXAttributeName, float>& OutNormalizedAttributeValues) override;` — RGB to CMY implementation
- L25 _public prototype_ `virtual void ModulateMatrix_Implementation(UDMXEntityFixturePatch* FixturePatch, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues, TArray<FDMXNormalizedAttributeValueMap>& OutNormalizedMatrixAttributeValues) override;` — Matrix RGB to CMY implementation
- L29 _public member_ `int32 DelayFrames = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "120", UIMax = "120"))` — The time by which signals are delayed in Seconds
- L72 _public member_ `TArray<TSharedRef<FBufferElement>> Buffer;` — Buffer of data
- L75 _public member_ `TArray<TSharedRef<FMatrixBufferElement>> MatrixBuffer;` — Buffer of data

#### class `UDMXModulator_PixelMappingFrameDelay::FBufferElement`  
`class FBufferElement : public TSharedFromThis<FBufferElement>`  
_L32-49_
- inherits: `TSharedFromThis<FBufferElement>`
- desc: An element in the buffer for attribute values
- L36 _public function_ `FBufferElement()`
- L39 _public function_ `FBufferElement(int32 InWakeFrame, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues) : NormalizedAttributeValues(InNormalizedAttributeValues) , WakeFrame(InWakeFrame)`
- L45 _public member_ `TMap<FDMXAttributeName, float> NormalizedAttributeValues;` — Map of attribute values with timestamp
- L48 _public member_ `uint32 WakeFrame = 0;` — Time when values should be output

#### class `UDMXModulator_PixelMappingFrameDelay::FMatrixBufferElement`  
`class FMatrixBufferElement : public TSharedFromThis<FMatrixBufferElement>`  
_L52-69_
- inherits: `TSharedFromThis<FMatrixBufferElement>`
- desc: An element in the buffer for matrix attribute values
- L56 _public function_ `FMatrixBufferElement()`
- L59 _public function_ `FMatrixBufferElement(int32 InWakeFrame, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues) : NormalizedMatrixAttributeValues(InNormalizedMatrixAttributeValues) , WakeFrame(InWakeFrame)`
- L65 _public member_ `TArray<FDMXNormalizedAttributeValueMap> NormalizedMatrixAttributeValues;` — Map of matrix attribute values with timestamps
- L68 _public member_ `uint32 WakeFrame = 0;` — Time when values should be output

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Blueprint/DMXPixelMappingSubsystem.h` (Public)


#### class `UDMXPixelMappingSubsystem`  
`class UDMXPixelMappingSubsystem : public UEngineSubsystem`  
_L11-72_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L19 _public prototype_ `static UDMXPixelMappingSubsystem* GetDMXPixelMappingSubsystem_Pure();` — `UFUNCTION(BlueprintPure, Category = "DMX PixelMapping Subsystem", meta = (BlueprintInternalUseOnly = "true"))` — Get a DMX PixelMapping Subsystem, pure version
- L23 _public prototype_ `static UDMXPixelMappingSubsystem* GetDMXPixelMappingSubsystem_Callable();` — `UFUNCTION(BlueprintCallable, Category = "DMX PixelMapping Subsystem", meta = (BlueprintInternalUseOnly = "true"))` — Get a DMX PixelMapping Subsystem, callable version
- L27 _public prototype_ `UDMXPixelMapping* GetDMXPixelMapping(UDMXPixelMapping* InPixelMapping);` — `UFUNCTION(BlueprintPure, Category = "DMX|PixelMapping")` — Load Pixel Mapping asset
- L38 _public prototype_ `UDMXPixelMappingRendererComponent* GetRendererComponent(UDMXPixelMapping* InDMXPixelMapping, const FName& InComponentName);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "InComponentName"), Category = "DMX|PixelMapping")` — Get Renderer component. Only for K2 blueprint nodes @param			InDMXPixelMapping Pixel Mapping UObject Asset @param			InComponentName Name of looking renderer component @return Pointer to the component or nullptr
- L49 _public prototype_ `UDMXPixelMappingOutputDMXComponent* GetOutputDMXComponent(UDMXPixelMapping* InDMXPixelMapping, const FName& InComponentName);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "InComponentName"), Category = "DMX|PixelMapping")` — Get OutputDMX component. Only for K2 blueprint nodes @param			InDMXPixelMapping Pixel Mapping UObject Asset @param			InComponentName Name of looking OutputDMX component @return Pointer to the component or nullptr
- L60 _public prototype_ `UDMXPixelMappingFixtureGroupComponent* GetFixtureGroupComponent(UDMXPixelMapping* InDMXPixelMapping, const FName& InComponentName);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "InComponentName"), Category = "DMX|PixelMapping")` — Get FixtureGroup component. Only for K2 blueprint nodes @param			InDMXPixelMapping Pixel Mapping UObject Asset @param			InComponentName Name of looking FixtureGroup component @return Pointer to the component or nullptr
- L71 _public prototype_ `UDMXPixelMappingMatrixComponent* GetMatrixComponent(UDMXPixelMapping* InDMXPixelMapping, const FName& InComponentName);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "InComponentName"), Category = "DMX|PixelMapping")` — Get Matrix component. Only for K2 blueprint nodes @param			InDMXPixelMapping Pixel Mapping UObject Asset @param			InComponentName Name of looking Matrix component @return Pointer to the component or nullptr

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/ColorSpace/DMXPixelMappingColorSpace.h` (Public)


#### class `UDMXPixelMappingColorSpace`  
`class UDMXPixelMappingColorSpace : public UObject`  
_L16-65_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base class for Pixel Mapping Color Spaces. Note, implementations must be thread-safe.
- L27 _public prototype_ `virtual void SetRGBA(const FLinearColor& InColor) PURE_VIRTUAL(UDMXPixelMappingColorSpace::SetRGBA, return;);` — Sets the RGBA value to be converted to the implemented Color Space
- L30 _public prototype_ `void ResetToBlack();` — Resets the color to black, and any luminance to zero
- L33 _public function_ `const TMap<FDMXAttributeName, float>& GetAttributeNameToValueMap()` — Returns the Attribute Name to Value Map of the Color currently set
- L37 _public function_ `FDMXPixelMappingColorSpacePostEditChangePropertyDelegate& GetOnPostEditChangedProperty()` — Returns a delegate broadcast when a property changed. Useful to handle attribute name changes.
- L42 _public member_ `bool bUseWorkingColorSpaceForInput = true;` — `UPROPERTY(EditAnywhere, Category = "Color Space", Meta = (DisplayPriority = -1))` — When checked, uses Unreal Working Color Space for input conversion, otherwise, assumes the input is sRGB
- L47 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _protected prototype_ `void SetAttributeValue(const FDMXAttributeName& AttributeName, float Value);` — Sets an Attribute Value
- L55 _protected prototype_ `void ClearCachedAttributeValues();` — Clears cached Attribtues
- L59 _private member_ `TMap<FDMXAttributeName, float> AttributeNameToValueMap;` — Buffer holding results of the conversion
- L63 _private member_ `FDMXPixelMappingColorSpacePostEditChangePropertyDelegate OnPostEditChangeProperty;` — Event raised Post Edit Change Property

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXPixelMappingColorSpacePostEditChangePropertyDelegate, FPropertyChangedEvent& ) #endif`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingBaseComponent.h` (Public)


#### enum `EDMXPixelMappingResetDMXMode`  
`enum class EDMXPixelMappingResetDMXMode : uint8`  
_L19-24_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `SendDefaultValues UMETA(DisplayName = "Send Default Values")`
- L22 _public enumerator_ `SendZeroValues UMETA(DisplayName = "Send Zero Values")`
- L23 _public enumerator_ `DoNotSendValues UMETA(DisplayName = "Keep Last Mapped Values")`

#### class `UDMXPixelMappingBaseComponent`  
`class UDMXPixelMappingBaseComponent : public UObject`  
_L30-270_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Abstract)`
- inherits: `UObject`
- desc: Base class for all DMX Pixel Mapping components.
- L35 _private typedef_ `using TComponentPredicate = TFunctionRef<void(UDMXPixelMappingBaseComponent*)>;`
- L38 _private typedef_ `template <typename Type> using TComponentPredicateType = TFunctionRef<void(Type*)>;`
- L40 _private prototype_ `DECLARE_EVENT_TwoParams(UDMXPixelMappingBaseComponent, FDMXPixelMappingOnComponentAdded, UDMXPixelMapping* , UDMXPixelMappingBaseComponent* );`
- L41 _private prototype_ `DECLARE_EVENT_TwoParams(UDMXPixelMappingBaseComponent, FDMXPixelMappingOnComponentRemoved, UDMXPixelMapping* , UDMXPixelMappingBaseComponent* );`
- L42 _private prototype_ `DECLARE_EVENT_OneParam(UDMXPixelMappingBaseComponent, FDMXPixelMappingOnComponentRenamed, UDMXPixelMappingBaseComponent* );`
- L46 _public prototype_ `static FDMXPixelMappingOnComponentAdded& GetOnComponentAdded();` — Gets an Event broadcast when a component was added
- L49 _public prototype_ `static FDMXPixelMappingOnComponentRemoved& GetOnComponentRemoved();` — Gets an Event broadcast when a component was added
- L52 _public prototype_ `static FDMXPixelMappingOnComponentRenamed& GetOnComponentRenamed();` — Gets an Event broadcast this uobject was renamed. Note this is only raised after UObject::Rename, not after SetUserName.
- L55 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L56 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L58 _public prototype_ `virtual void PostEditUndo() override;`
- L67 _public function_ `virtual bool ValidateProperties()` — Should log properties that were changed in underlying fixture patch or fixture type @return		Returns true if properties are valid.
- L72 _public prototype_ `virtual const FName& GetNamePrefix();` — Helper function for generating UObject name, the child should implement their own logic for Prefix name generation.
- L79 _public prototype_ `int32 GetChildrenCount() const;` — Get the number of children components
- L82 _public prototype_ `UDMXPixelMappingBaseComponent* GetChildAt(int32 Index) const;` — Get the child component by the given index.
- L85 _public function_ `const TArray<UDMXPixelMappingBaseComponent*>& GetChildren() const` — Get all children to belong to this component
- L88 _public prototype_ `void GetChildComponentsRecursively(TArray<UDMXPixelMappingBaseComponent*>& Components);` — Gathers descendant child Components of a parent Component.
- L95 _public prototype_ `virtual void AddChild(UDMXPixelMappingBaseComponent* InComponent);` — Add a new child componet @param InComponent    Component instance object
- L98 _public prototype_ `virtual void RemoveChild(UDMXPixelMappingBaseComponent* InComponent);` — Remove the child component by the given component object.
- L101 _public prototype_ `void ClearChildren();` — Remove all children
- L104 _public function_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const` — Check if a Component can be moved under another one (used for copy/move/duplicate)
- L111 _public prototype_ `virtual FString GetUserFriendlyName() const;` — `UE_DEPRECATED(5.3, "Renamed GetUserName to be more explicit aobout the intent. The user name is displayed if set, otherwise the object name.")` — DEPRECATED 5.3
- L114 _public prototype_ `virtual FString GetUserName() const;` — Returns the name of the component. If user name is set returns the custom user name (see SetUserName)
- L117 _public prototype_ `virtual void SetUserName(const FString& NewName);` — Sets the custom user name. If set, GetUserName returns this name.
- L124 _public prototype_ `void ForEachChild(TFunctionRef<void(UDMXPixelMappingBaseComponent*)> Predicate, bool bIsRecursive);` — Loop through all child by given Predicate @param bIsRecursive		Should it loop recursively
- L132 _public function_ `template <typename TComponentClass> TComponentClass* GetFirstChildOfClass()` — Looking for the first child by given Class @return An instance of the templated Component
- L150 _public function_ `template <typename TComponentClass> void ForEachChildOfClass(TComponentPredicateType<TComponentClass> Predicate, bool bIsRecursive)` — Loop through all templated child class by given Predicate @param bIsRecursive		Should it loop recursively
- L161 _public prototype_ `UDMXPixelMapping* GetPixelMapping() const;` — Get Pixel Mapping asset UObject
- L164 _public prototype_ `const UDMXPixelMappingRootComponent* GetRootComponent() const;` — Get root component of the component tree
- L167 _public prototype_ `const UDMXPixelMappingRootComponent* GetRootComponentChecked() const;` — Get the root component and not allow a null option.
- L175 _public prototype_ `UDMXPixelMappingRendererComponent* GetRendererComponent();` — Get renderer component associated with current component It could be this component itself if this component is root component It could be parent component if that is pixel component It could be nullptr if that is Root component
- L183 _public function_ `virtual void ResetDMX(EDMXPixelMappingResetDMXMode ResetMode = EDMXPixelMappingResetDMXMode::SendDefaultValues)` — `UFUNCTION(BlueprintCallable, Category = "DMX|PixelMapping")` — Reset all sending DMX channels to 0 for this component and all children
- L187 _public function_ `virtual void SendDMX()` — `UFUNCTION(BlueprintCallable, Category = "DMX|PixelMapping")` — Send DMX values of this component and all children.
- L191 _public function_ `virtual void Render()` — `UFUNCTION(BlueprintCallable, Category = "DMX|PixelMapping")` — Renders this component and all children
- L195 _public function_ `virtual void RenderAndSendDMX()` — `UFUNCTION(BlueprintCallable, Category = "DMX|PixelMapping")` — Render downsample texture and send DMX for this component and all children
- L203 _public function_ `template <typename TComponentClass> static TComponentClass* GetFirstParentByClass(UDMXPixelMappingBaseComponent* InComponent)` — Recursively looking for the first parent by given Class @return An instance of the templated Component
- L221 _public prototype_ `static void ForComponentAndChildren(UDMXPixelMappingBaseComponent* Component, TComponentPredicate Predicate);` — Recursively loop through all child by given Component and Predicate
- L225 _public member_ `TArray<TObjectPtr<UDMXPixelMappingBaseComponent>> Children;` — `UPROPERTY()` — Array of children belong to this component
- L228 _public function_ `UDMXPixelMappingBaseComponent* GetParent() const` — Returns the parent. May be nullptr when the the component is creating or destroying
- L231 _public function_ `bool HasValidParent() const` — Returns the parent. May be nullptr when the the component is creating or destroying
- L235 _public function_ `void SetParent(const TWeakObjectPtr<UDMXPixelMappingBaseComponent>& NewParent)` — Set the components parent
- L239 _public member_ `TObjectPtr<UDMXPixelMappingBaseComponent> Parent_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Leads to entangled references. Use GetParent() or WeakParent instead."))` — Parent component
- L243 _public member_ `bool bExpanded = true;` — `UPROPERTY()`
- L248 _protected prototype_ `virtual void NotifyAddedToParent();` — Called when the component was added to a parent
- L251 _protected prototype_ `virtual void NotifyRemovedFromParent();` — Called when the component was added to a parent
- L255 _protected member_ `FString UserName;` — `UPROPERTY()` — Custom user name for the component. Should be used if set.
- L260 _private member_ `TWeakObjectPtr<UDMXPixelMappingBaseComponent> WeakParent;` — `UPROPERTY(NonTransactional)` — Parent component
- L263 _private member_ `static FDMXPixelMappingOnComponentAdded OnComponentAdded;` — Delegate Broadcast when a component was added
- L266 _private member_ `static FDMXPixelMappingOnComponentRemoved OnComponentRemoved;` — Delegate Broadcast when a component was removed
- L269 _private member_ `static FDMXPixelMappingOnComponentRenamed OnComponentRenamed;` — Delegate Broadcast when a component was renamed

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_STATS_GROUP(TEXT("DMXPixelMapping"), STATGROUP_DMXPIXELMAPPING, STA`
- L40 _delegate_ `DECLARE_EVENT_TwoParams(UDMXPixelMappingBaseComponent, FDMXPixelMappingOnComponentAdded, UDMXPixelMapping* , UDMXPixelMappingBaseComponent* );`
- L41 _delegate_ `DECLARE_EVENT_TwoParams(UDMXPixelMappingBaseComponent, FDMXPixelMappingOnComponentRemoved, UDMXPixelMapping* , UDMXPixelMappingBaseComponent* );`
- L42 _delegate_ `DECLARE_EVENT_OneParam(UDMXPixelMappingBaseComponent, FDMXPixelMappingOnComponentRenamed, UDMXPixelMappingBaseComponent* );`
- L136 _function_ `` (scope `UDMXPixelMappingBaseComponent::GetFirstChildOfClass`)
- L152 _function_ `ForEachChild([&Predicate](UDMXPixelMappingBaseComponent* InComponent) { if (TComponentClass* CastComponent = Cast<TComponentClass>(InComponent)) { Predicate(CastComponent); } }, bIsRecursive);` (scope `UDMXPixelMappingBaseComponent::ForEachChildOfClass`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingFixtureGroupComponent.h` (Public)


#### class `UDMXPixelMappingFixtureGroupComponent`  
`class UDMXPixelMappingFixtureGroupComponent : public UDMXPixelMappingOutputComponent`  
_L20-73_
- reflection: `UCLASS()`
- inherits: `UDMXPixelMappingOutputComponent`
- desc: Container component for Fixture Items
- L26 _public prototype_ `UDMXPixelMappingFixtureGroupComponent();` — Default Constructor
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _public prototype_ `virtual void PostEditUndo() override;`
- L36 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L37 _public prototype_ `virtual void AddChild(UDMXPixelMappingBaseComponent* InComponent) override;`
- L38 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;`
- L39 _public prototype_ `virtual void ResetDMX(EDMXPixelMappingResetDMXMode ResetMode = EDMXPixelMappingResetDMXMode::SendDefaultValues) override;`
- L40 _public prototype_ `virtual void SendDMX() override;`
- L41 _public prototype_ `virtual FString GetUserName() const override;`
- L45 _public prototype_ `virtual void SetPosition(const FVector2D& NewPosition) override;`
- L46 _public prototype_ `virtual void SetPositionRotated(FVector2D NewRotatedPosition) override;`
- L47 _public prototype_ `virtual void SetSize(const FVector2D& NewSize) override;`
- L48 _public prototype_ `virtual void SetRotation(double NewRotation) override;`
- L50 _public function_ `virtual bool IsExposedToTemplate()`
- L51 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L56 _public function_ `FSimpleMulticastDelegate& GetOnDMXLibraryChanged()` — Returns a delegate broadcasted when the DMX Library changed
- L59 _public prototype_ `virtual void QueueDownsample() override;` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L62 _public member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture List")`
- L66 _public member_ `TObjectPtr<UDMXPixelMappingLayoutScript> LayoutScript;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Layout")` — Layout script for the children of this component (hidden in customizations and displayed in its own panel).
- L70 _private member_ `FSimpleMulticastDelegate OnDMXLibraryChangedDelegate;` — Returns a delegate broadcasted when the DMX Library changed
- L72 _private member_ `static const FVector2D MinGroupSize;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingFixtureGroupItemComponent.h` (Public)


#### class `UDMXPixelMappingFixtureGroupItemComponent`  
`class UDMXPixelMappingFixtureGroupItemComponent : public UDMXPixelMappingOutputDMXComponent`  
_L28-153_
- reflection: `UCLASS(AutoExpandCategories = ("Output Settings"))`
- inherits: `UDMXPixelMappingOutputDMXComponent`
- desc: A component that holds a single Fixture Patch in the Pixel Mapping, and actually sends DMX.
- L35 _public prototype_ `UDMXPixelMappingFixtureGroupItemComponent();` — Default Constructor
- L39 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L40 _protected prototype_ `virtual void PostInitProperties() override;`
- L41 _protected prototype_ `virtual void PostLoad() override;`
- L42 _protected prototype_ `virtual void BeginDestroy() override;`
- L44 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L51 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L52 _public prototype_ `virtual void ResetDMX(EDMXPixelMappingResetDMXMode ResetMode = EDMXPixelMappingResetDMXMode::SendDefaultValues) override;`
- L53 _public prototype_ `virtual void SendDMX() override;`
- L54 _public prototype_ `virtual FString GetUserName() const override;`
- L59 _public prototype_ `virtual bool IsVisible() const override;`
- L61 _public prototype_ `virtual bool IsOverParent() const override;`
- L62 _public prototype_ `virtual void SetPosition(const FVector2D& NewPosition) override;`
- L63 _public prototype_ `virtual void SetSize(const FVector2D& NewSize) override;`
- L67 _public prototype_ `TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement> GetOrCreatePixelMapRenderElement();` — Returns the pixel map render element for the matrix cell
- L70 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;` — Check if a Component can be moved under another one (used for copy/move/duplicate)
- L73 _public member_ `int32 DownsamplePixelIndex;` — Index of the cell pixel in downsample target buffer
- L77 _private prototype_ `void UpdateRenderElement();` — Updates the rendered element
- L81 _private prototype_ `void OnColorSpacePostEditChangeProperties(FPropertyChangedEvent& PropertyChangedEvent);` — Called post edit change properties of the color space member
- L85 _private prototype_ `UDMXPixelMappingRendererComponent* GetRendererComponent() const;` — Helper that returns the renderer component this component belongs to
- L88 _private member_ `TSharedPtr<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement> PixelMapRenderElement;` — Pixel map render element for the matrix cell
- L97 _public prototype_ `virtual void QueueDownsample() override;` — `UE_DEPRECATED(5.3, "No longer in use. Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L99 _public function_ `virtual int32 GetDownsamplePixelIndex() const override` — `UE_DEPRECATED(5.3, "No longer in use. Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L105 _public prototype_ `virtual void RenderWithInputAndSendDMX() override;` — `UE_DEPRECATED(5.3, "Deprecated for performance reasons. Instead use 'Get DMX Pixel Mapping Renderer Component' and Render only once each tick.")`
- L111 _public prototype_ `TMap<FDMXAttributeName, float> CreateAttributeValues() const;` — `UE_DEPRECATED(5.2, "Instead use UDMXPixelMappingColorSpace::Update and UDMXPixelMappingColorSpace::GetAttributeNameToValueMap using the ColorSpace member of this class.")` — DEPRECATED 5.2
- L115 _public member_ `EDMXColorMode ColorMode_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L118 _public member_ `bool AttributeRExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L121 _public member_ `bool AttributeGExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L124 _public member_ `bool AttributeBExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L127 _public member_ `bool bMonochromeExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L130 _public member_ `bool AttributeRInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L133 _public member_ `bool AttributeGInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L136 _public member_ `bool AttributeBInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L139 _public member_ `bool bMonochromeInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L142 _public member_ `FDMXAttributeName AttributeR_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L145 _public member_ `FDMXAttributeName AttributeG_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L148 _public member_ `FDMXAttributeName AttributeB_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L151 _public member_ `FDMXAttributeName MonochromeIntensity_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L22 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L22 _namespace_ `namespace PixelMapRenderer` (scope `UE::DMXPixelMapping::Rendering`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingMatrixCellComponent.h` (Public)


#### class `UDMXPixelMappingMatrixCellComponent`  
`class UDMXPixelMappingMatrixCellComponent : public UDMXPixelMappingOutputComponent`  
_L25-87_
- reflection: `UCLASS()`
- inherits: `UDMXPixelMappingOutputComponent`
- desc: Matrix pixel component
- L35 _public prototype_ `UDMXPixelMappingMatrixCellComponent();` — Default Constructor
- L38 _public prototype_ `virtual void PostInitProperties() override;`
- L39 _public prototype_ `virtual void PostLoad() override;`
- L40 _public prototype_ `virtual void BeginDestroy() override;`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L47 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L48 _public prototype_ `virtual FString GetUserName() const override;`
- L52 _public prototype_ `virtual bool IsOverParent() const override;`
- L53 _public function_ `virtual int32 GetDownsamplePixelIndex() const override`
- L54 _public prototype_ `virtual void QueueDownsample() override;`
- L57 _public prototype_ `void SetCellCoordinate(FIntPoint InCellCoordinate);`
- L58 _public function_ `const FIntPoint& GetCellCoordinate()`
- L61 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;` — Check if a Component can be moved under another one (used for copy/move/duplicate)
- L64 _public prototype_ `TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement> GetOrCreatePixelMapRenderElement();` — Returns the pixel map render element for the matrix cell
- L67 _public prototype_ `FLinearColor GetPixelMapColor() const;` — Gets the color of this cell
- L70 _public member_ `int32 CellID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cell Settings")`
- L74 _private prototype_ `void UpdateRenderElement();` — Updates the rendered element. Automatically called on property changes
- L77 _private prototype_ `UDMXPixelMappingRendererComponent* GetRendererComponent() const;` — Helper that returns the renderer component this component belongs to
- L80 _private member_ `TSharedPtr<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement> PixelMapRenderElement;` — Pixel map render element for the matrix cell
- L83 _private member_ `FIntPoint CellCoordinate;` — `UPROPERTY()`
- L86 _private member_ `int32 DownsamplePixelIndex;` — Index of the cell pixel in downsample target buffer

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L15 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L15 _namespace_ `namespace PixelMapRenderer` (scope `UE::DMXPixelMapping::Rendering`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingMatrixComponent.h` (Public)


#### class `UDMXPixelMappingMatrixComponent`  
`class UDMXPixelMappingMatrixComponent : public UDMXPixelMappingOutputDMXComponent`  
_L23-174_
- reflection: `UCLASS()`
- inherits: `UDMXPixelMappingOutputDMXComponent`
- desc: DMX Matrix group component
- L28 _private prototype_ `DECLARE_EVENT_TwoParams(UDMXPixelMappingMatrixComponent, FDMXPixelMappingOnMatrixChanged, UDMXPixelMapping* , UDMXPixelMappingMatrixComponent* );`
- L31 _private typedef_ `using ChildCallback = TFunctionRef<void(UDMXPixelMappingMatrixCellComponent*)>;` — Helper callback for loop through all component child
- L35 _public prototype_ `UDMXPixelMappingMatrixComponent();` — Default Constructor
- L39 _public function_ `static FDMXPixelMappingOnMatrixChanged& GetOnMatrixChanged()` — `UE_DEPRECATED(5.4, "OnMatrixChanged is removed without replacement. This is handled internally and should not require external handling.")` — Gets an Event broadcast when a the matrix (and by that its num cells) changed
- L46 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L47 _public prototype_ `virtual void PostLoad() override;`
- L48 _public prototype_ `virtual void PostInitProperties() override;`
- L50 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L56 _public prototype_ `void LogInvalidProperties();` — Logs properties that were changed in underlying fixture patch or fixture type
- L60 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L61 _public prototype_ `virtual void ResetDMX(EDMXPixelMappingResetDMXMode ResetMode = EDMXPixelMappingResetDMXMode::SendDefaultValues) override;`
- L62 _public prototype_ `virtual void SendDMX() override;`
- L63 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;`
- L64 _public prototype_ `virtual FString GetUserName() const override;`
- L68 _public prototype_ `virtual void SetPosition(const FVector2D& NewPosition) override;`
- L69 _public prototype_ `virtual void SetPositionRotated(FVector2D NewRotatedPosition) override;`
- L70 _public prototype_ `virtual void SetSize(const FVector2D& NewSize) override;`
- L71 _public prototype_ `virtual void SetRotation(double NewRotation) override;`
- L73 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L75 _public prototype_ `virtual bool IsOverParent() const override;`
- L81 _public prototype_ `virtual void RenderWithInputAndSendDMX() override;` — `UE_DEPRECATED(5.3, "Deprecated for performance reasons. Instead use 'Get DMX Pixel Mapping Renderer Component' and Render only once each tick.")`
- L86 _public prototype_ `void HandleMatrixChanged();` — Handles changes in size or in matrix
- L89 _public prototype_ `virtual void QueueDownsample() override;` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L93 _protected prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when the fixture type in use changed
- L96 _protected prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when the fixture patch in use changed
- L100 _protected member_ `TArray<UDMXPixelMappingBaseComponent*> PreEditUndoMatrixCellChildren;` — Children available PreEditUndo, useful to hide all removed ones in post edit undo
- L106 _public member_ `FDMXEntityFixturePatchRef FixturePatchMatrixRef_DEPRECATED;` — `UPROPERTY()`
- L110 _public member_ `FIntPoint CoordinateGrid;` — `UPROPERTY()`
- L113 _public member_ `FVector2D CellSize;` — `UPROPERTY()`
- L116 _public member_ `EDMXPixelMappingDistribution Distribution;` — `UPROPERTY()`
- L120 _public member_ `bool bInvertCellsX = false;` — `UPROPERTY(EditAnywhere, Category = "Matrix")` — Inverts the cell ordering along the X-axis. Useful when the matrix is facing away from the screen.
- L124 _public member_ `bool bInvertCellsY = false;` — `UPROPERTY(EditAnywhere, Category = "Matrix")` — Inverts the cell ordering along the Y-axis. Useful when the matrix is facing away from the screen .
- L128 _public member_ `TObjectPtr<UDMXPixelMappingLayoutScript> LayoutScript;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Layout")` — Layout script for the children of this component (hidden in customizations and displayed in its own panel).
- L136 _public member_ `EDMXColorMode ColorMode_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L139 _public member_ `bool AttributeRExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L142 _public member_ `bool AttributeGExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L145 _public member_ `bool AttributeBExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L148 _public member_ `bool bMonochromeExpose_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L151 _public member_ `bool AttributeRInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L154 _public member_ `bool AttributeGInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L157 _public member_ `bool AttributeBInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L160 _public member_ `bool bMonochromeInvert_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L163 _public member_ `FDMXAttributeName AttributeR_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L166 _public member_ `FDMXAttributeName AttributeG_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L169 _public member_ `FDMXAttributeName AttributeB_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`
- L172 _public member_ `FDMXAttributeName MonochromeIntensity_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of DMXPixelMappingColorSpace. See ColorSpace member."))`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_EVENT_TwoParams(UDMXPixelMappingMatrixComponent, FDMXPixelMappingOnMatrixChanged, UDMXPixelMapping* , UDMXPixelMappingMatrixComponent* );`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingOutputComponent.h` (Public)


#### class `UDMXPixelMappingOutputComponent`  
`class UDMXPixelMappingOutputComponent : public UDMXPixelMappingBaseComponent`  
_L23-182_
- reflection: `UCLASS(Abstract)`
- inherits: `UDMXPixelMappingBaseComponent`
- desc: Base class for all Designer and configurable components
- L30 _public prototype_ `UDMXPixelMappingOutputComponent();` — Default Constructor
- L33 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void PostLoad() override;`
- L36 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;`
- L50 _public function_ `virtual bool IsExposedToTemplate()` — Whether component should be part of Palette view
- L53 _public prototype_ `virtual const FText GetPaletteCategory();` — Returns the text of palette category
- L56 _public prototype_ `virtual bool IsVisible() const;` — Whether component should be visible
- L59 _public function_ `virtual bool IsLockInDesigner() const` — Whether component can be re-sized or re-position at the editor
- L62 _public prototype_ `virtual void SetZOrder(int32 NewZOrder);` — Sets the ZOrder in the UI
- L65 _public function_ `virtual int32 GetZOrder() const` — Returns the UI ZOrder
- L68 _public prototype_ `virtual FLinearColor GetEditorColor() const;` — Returns an editor color for the widget
- L72 _public prototype_ `virtual bool IsOverParent() const;` — Returns true if the the component's over all its parents.
- L75 _public prototype_ `virtual bool IsOverPosition(const FVector2D& Position) const;` — Returns true if the component is over specified position
- L79 _public prototype_ `virtual bool OverlapsComponent(UDMXPixelMappingOutputComponent* Other) const;` — `UE_DEPRECATED(5.4, "Removed without replacement. GetEdges and test against other if this method is needed.")` — Returns true if the component overlaps the other
- L83 _public function_ `virtual int32 GetDownsamplePixelIndex() const` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")` — Get pixel index in downsample texture
- L87 _public function_ `virtual void QueueDownsample()` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")` — Queue rendering to downsample rendering target
- L90 _public prototype_ `FVector2D GetPosition() const;` — Returns the absolute position, without rotation
- L93 _public prototype_ `virtual void SetPosition(const FVector2D& NewPosition);` — Sets the absolute position of the component, without rotation.
- L96 _public prototype_ `FVector2D GetPositionRotated() const;` — Returns the absolute position with rotation.
- L99 _public prototype_ `virtual void SetPositionRotated(FVector2D NewRotatedPosition);` — Sets the the absolute position with rotation.
- L102 _public prototype_ `void GetEdges(FVector2D& A, FVector2D& B, FVector2D& C, FVector2D& D) const;` — Returns the edges of the component, absolute, rotated, clockwise order
- L105 _public prototype_ `FVector2D GetSize() const;` — Get the absolute size
- L108 _public prototype_ `virtual void SetSize(const FVector2D& NewSize);` — Sets the absolue size
- L111 _public prototype_ `double GetRotation() const;` — Gets the absolute rotation, in degrees
- L114 _public prototype_ `virtual void SetRotation(double NewRotation);` — Sets the absolute rotation, in degrees
- L117 _public prototype_ `void InvalidatePixelMapRenderer();` — Invalidates the pixel map, effectively causing the renderer component to aquire a new pixel map
- L120 _public prototype_ `UDMXPixelMappingRendererComponent* FindRendererComponent() const;` — Helper that returns render component if available
- L125 _public prototype_ `void ZOrderTopmost();` — Z-orders this component and its children topmost
- L132 _public member_ `int32 ZOrder = 1;` — `UPROPERTY()` — ZOrder in the UI
- L137 _public member_ `FLinearColor EditorColor = FLinearColor::Blue;` — `UE_DEPRECATED(5.4, "Should no longer be publicly accessed, instead call GetEditorColor.")` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Settings")` — The color displayed in editor
- L142 _public function_ `static FName GetLockInDesignerPropertyName()` — Property Name getters
- L143 _public function_ `static FName GetVisibleInDesignerPropertyName()`
- L144 _public function_ `static FName GetPositionXPropertyName()`
- L145 _public function_ `static FName GetPositionYPropertyName()`
- L146 _public function_ `static FName GetSizeXPropertyName()`
- L147 _public function_ `static FName GetSizeYPropertyName()`
- L148 _public function_ `static FName GetRotationPropertyName()`
- L153 _protected member_ `float PositionX = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Transform", Meta = (AllowPrivateAccess = true))`
- L156 _protected member_ `float PositionY = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Transform", Meta = (AllowPrivateAccess = true))`
- L160 _protected member_ `FVector2D EditorPositionWithRotation = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, Transient, Category = "Transform", Meta = (EditCondition = "!bLockInDesigner", DisplayName = "Position (with Rotation)"))`
- L164 _protected member_ `float SizeX = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform", Meta = (ClampMin = 0.0001, EditCondition = "!bLockInDesigner"))`
- L167 _protected member_ `float SizeY = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform", Meta = (ClampMin = 0.0001, EditCondition = "!bLockInDesigner"))`
- L170 _protected member_ `double Rotation = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform", Meta = (UIMin = -180, UIMax = 180, EditCondition = "!bLockInDesigner"))`
- L173 _protected member_ `FDMXPixelMappingComponentGeometryCache CachedGeometry;` — `UPROPERTY(Transient)`
- L177 _protected member_ `bool bLockInDesigner;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Editor Settings")`
- L180 _protected member_ `bool bVisibleInDesigner;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Editor Settings")`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L15 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L15 _namespace_ `namespace PixelMapRenderer` (scope `UE::DMXPixelMapping::Rendering`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingOutputDMXComponent.h` (Public)


#### class `UDMXPixelMappingOutputDMXComponent`  
`class UDMXPixelMappingOutputDMXComponent : public UDMXPixelMappingOutputComponent`  
_L18-69_
- reflection: `UCLASS(Abstract)`
- inherits: `UDMXPixelMappingOutputComponent`
- desc: Base class for components that contain a fixture patch to send DMX.
- L26 _public prototype_ `virtual FLinearColor GetEditorColor() const override;`
- L32 _public member_ `EDMXPixelBlendingQuality CellBlendingQuality = EDMXPixelBlendingQuality::High;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quality")` — The quality level to use when averaging colors during downsampling.
- L35 _public member_ `FDMXEntityFixturePatchRef FixturePatchRef;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fixture Patch", Meta = (ShowOnlyInnerProperties))`
- L40 _public member_ `bool bUsePatchColor = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Editor Settings", Meta = (AllowPrivateAccess = true))` — If set, the color of the patch is displayed, instead of a custom editor color
- L45 _public member_ `TSubclassOf<UDMXPixelMappingColorSpace> ColorSpaceClass;` — `UPROPERTY(Transient, EditAnywhere, NoClear, Category = "Color Space", Meta = (DisplayPriority = 2, DisplayName = "Output Mode", ShowDisplayNames))` — Sets which color space Pixel Mapping sends
- L49 _public member_ `TObjectPtr<UDMXPixelMappingColorSpace> ColorSpace;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Color Space")` — The Color Space currently in use
- L53 _public member_ `TArray<TSubclassOf<UDMXModulator>> ModulatorClasses;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient, Category = "Output Modulators", meta = (DisplayName = "Output Modulators"))` — Modulators applied to the output before sending DMX
- L57 _public member_ `TArray<TObjectPtr<UDMXModulator>> Modulators;` — `UPROPERTY()` — The actual modulator instances
- L62 _public prototype_ `virtual void RenderWithInputAndSendDMX() PURE_VIRTUAL(UDMXPixelMappingOutputDMXComponent::RenderWithInputAndSendDMX);` — `UE_DEPRECATED(5.3, "Deprecated for performance reasons. Instead use 'Get DMX Pixel Mapping Renderer Component' and Render only once each tick.")` — `UFUNCTION(BlueprintCallable, Category = "DMX|PixelMapping", Meta = (DeprecatedFunction, DeprecationMessage = "Deprecated for performance reasons. Instead use 'Get DMX Pixel Mapping Renderer Component' and Render only once each tick"))` — Render input texture for downsample texture, donwsample and send DMX for this component
- L65 _public function_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override` — Check if a Component can be moved under another one (used for copy/move/duplicate)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingRendererComponent.h` (Public)


#### enum `EDMXPixelMappingRendererPixelFormat`  
`enum class EDMXPixelMappingRendererPixelFormat : uint8`  
_L26-31_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Auto UMETA(ToolTip = "Use the format of the Input Texture, use 8-bit for Input Materials and UMG.")`
- L29 _public enumerator_ `RGBA8 UMETA(DisplayName = "Low Precision 8-bit (RGBA8)")`
- L30 _public enumerator_ `RGBA16F UMETA(DisplayName = "High Precision 16-bit (RGBA16F)")`

#### class `UDMXPixelMappingRendererComponent`  
`class UDMXPixelMappingRendererComponent : public UDMXPixelMappingOutputComponent`  
_L38-249_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDMXPixelMappingOutputComponent`
- desc: Component for rendering input texture.
- L45 _public prototype_ `UDMXPixelMappingRendererComponent();` — Default Constructor
- L49 _protected prototype_ `virtual void PostInitProperties() override;`
- L50 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L51 _protected prototype_ `virtual void PostLoad() override;`
- L53 _protected prototype_ `virtual void PostEditUndo() override;`
- L54 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L60 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L61 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;`
- L62 _public prototype_ `virtual void ResetDMX(EDMXPixelMappingResetDMXMode ResetMode = EDMXPixelMappingResetDMXMode::SendDefaultValues) override;`
- L63 _public prototype_ `virtual void SendDMX() override;`
- L64 _public prototype_ `virtual void Render() final;`
- L65 _public prototype_ `virtual void RenderAndSendDMX() final;`
- L66 _public prototype_ `virtual FString GetUserName() const override;`
- L70 _public function_ `UDMXPixelMappingPreprocessRenderer* GetPreprocessRenderer() const` — Returns the pixel mapping preprocess renderer
- L73 _public prototype_ `void UpdatePreprocessRenderer();` — Updates the preprocess renderer from the current render type and source texture
- L79 _public prototype_ `void InvalidatePixelMapRenderer();` — Invalidates the pixel map, effectively causing a rebuild of the mapping on the next Render call. Does not rebuild the renderer self. Use InitializeRenderer to rebuild the renderers.
- L82 _public prototype_ `UTexture* GetRenderedInputTexture() const;` — Gets the rendered input texture, or nullptr if no input texture is currently rendered
- L89 _public prototype_ `bool GetPixelMappingComponentModulators(FDMXEntityFixturePatchRef FixturePatchRef, TArray<UDMXModulator*>& DMXModulators);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Returns the Modulators of the component corresponding to the patch specified. Note, this node does a lookup on all fixture patches in use, hence may be slow and shouldn't be called on tick.
- L92 _public prototype_ `TArray<TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement>> GetPixelMapRenderElements() const;` — Returns a copy of the current pixel map render elements
- L96 _public member_ `EDMXPixelMappingRendererType RendererType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Render Settings")` — Selects the input type. It can be a Texture, a Material or a User Widget.
- L100 _public member_ `TObjectPtr<UTexture> InputTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Render Settings")` — The texture used for pixel mapping
- L104 _public member_ `TObjectPtr<UMaterialInterface> InputMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Render Settings", Meta = (DisplayName = "User Interface Material"))` — The material used for pixel mapping
- L108 _public member_ `TSubclassOf<UUserWidget> InputWidget;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Render Settings")` — The UMG widget used for pixel mapping
- L112 _public member_ `EDMXPixelMappingRendererPixelFormat PixelFormat = EDMXPixelMappingRendererPixelFormat::Auto;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Render Settings")` — The dynamic range of the renderer
- L116 _public member_ `float Brightness = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings", Meta = (ClampMin = "0", UIMin = "0", UIMax = "1", DisplayName = "Exposure"))` — The exposure of the pixel mapping renderer. This property affects the DMX output.
- L120 _public member_ `bool bChildrenFollowSize = true;` — `UPROPERTY(EditAnywhere, Category = "Layout")` — If true, children are positioned relative to the size of this renderer
- L124 _public member_ `TObjectPtr<UDMXPixelMappingLayoutScript> LayoutScript;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Layout")` — Layout script for the children of this component (hidden in customizations and displayed in its own panel).
- L128 _private prototype_ `void OnComponentAddedOrRemoved(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was added to or removed from the pixel mapping
- L131 _private prototype_ `void LetChildrenFollowSize();` — When bChildrenFollowSize is true, rearranges children relatively to the current size
- L134 _private prototype_ `EPixelFormat GetFormatFromDynamicRange() const;` — Returns the pixel format depending on the current dynamic range setting
- L137 _private prototype_ `UWorld* TryGetWorld() const;` — Tries to get any world. If with editor, returns the editor world, in game returns GWorld
- L140 _private member_ `TArray<TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement>> PixelMapRenderElements;` — Elements rendered during pixel mapping
- L144 _private member_ `TObjectPtr<UUserWidget> UserWidget;` — `UPROPERTY(Transient, DuplicateTransient)` — The user widget instance currently in use
- L147 _private member_ `bool bInvalidatePixelMap = true;` — True once the pixel map was built. Reset to false when the pixel map renderer is invalidated
- L151 _private member_ `TObjectPtr<UDMXPixelMappingPreprocessRenderer> PreprocessRenderer;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Filtering")` — Renderer responsible to preprocess the input texture / material / user widget
- L155 _private member_ `TObjectPtr<UDMXPixelMappingPixelMapRenderer> PixelMapRenderer;` — `UPROPERTY()` — Renderer responsible to pixel map
- L159 _private member_ `FVector2D LayoutRect;` — `UPROPERTY()` — The current rect in which children are laid out. Useful to compute UV position and size of children.
- L166 _public prototype_ `UWorld* GetWorld() const;` — `UE_DEPRECATED(5.3, "Since a pixel mapping asset doesn't have a clear world context, GetWorld() is no longer supported.")`
- L170 _public function_ `const TSharedPtr<IDMXPixelMappingRenderer>& GetRenderer()` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L175 _public prototype_ `void RenderEditorPreviewTexture();` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L178 _public prototype_ `UTextureRenderTarget2D* GetPreviewRenderTarget();` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L182 _public prototype_ `FIntPoint GetPixelPosition(int32 InIndex) const;` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L185 _public prototype_ `void CreateOrUpdateDownsampleBufferTarget();` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L189 _public prototype_ `void AddPixelToDownsampleSet(FDMXPixelMappingDownsamplePixelParamsV2&& InDownsamplePixelParam);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L193 _public prototype_ `int32 GetDownsamplePixelNum();` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L196 _public prototype_ `void SetDownsampleBuffer(TArray<FLinearColor>&& InDownsampleBuffer, FIntRect InRect);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L199 _public prototype_ `bool GetDownsampleBufferPixel(const int32 InDownsamplePixelIndex, FLinearColor& OutLinearColor);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L202 _public prototype_ `bool GetDownsampleBufferPixels(const int32 InDownsamplePixelIndexStart, const int32 InDownsamplePixelIndexEnd, TArray<FLinearColor>& OutLinearColors);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L205 _public prototype_ `bool ResetColorDownsampleBufferPixel(const int32 InDownsamplePixelIndex);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L208 _public prototype_ `bool ResetColorDownsampleBufferPixels(const int32 InDownsamplePixelIndexStart, const int32 InDownsamplePixelIndexEnd);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L211 _public prototype_ `void EmptyDownsampleBuffer();` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L215 _private prototype_ `int32 GetTotalDownsamplePixelCount();` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L218 _private prototype_ `bool IsPixelRangeValid(const int32 InDownsamplePixelIndexStart, const int32 InDownsamplePixelIndexEnd) const;` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L221 _private prototype_ `void ResizePreviewRenderTarget(uint32 InSizeX, uint32 InSizeY);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L224 _private prototype_ `UTextureRenderTarget2D* CreateRenderTarget(const FName& InBaseName);` — `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer to render the pixel map")`
- L227 _private member_ `TSharedPtr<IDMXPixelMappingRenderer> PixelMappingRenderer_DEPRECATED;`
- L231 _private member_ `TObjectPtr<UTextureRenderTarget2D> DownsampleBufferTarget_DEPRECATED;` — `UPROPERTY(Transient, DuplicateTransient)`
- L235 _private member_ `TObjectPtr<UTextureRenderTarget2D> PreviewRenderTarget_DEPRECATED;` — `UPROPERTY(Transient, DuplicateTransient)`
- L238 _private member_ `TArray<FLinearColor> DownsampleBuffer_DEPRECATED;`
- L239 _private member_ `int32 DownsamplePixelCount_DEPRECATED = 0;`
- L240 _private member_ `mutable FCriticalSection DownsampleBufferCS_DEPRECATED;`
- L242 _private member_ `TArray<FDMXPixelMappingDownsamplePixelParamsV2> DownsamplePixelParams_DEPRECATED;`
- L244 _private member_ `static const FLinearColor ClearTextureColor_DEPRECATED;`
- L245 _private member_ `bool bWasEverRendered_DEPRECATED = false;`
- L248 _public member_ `static const FIntPoint MaxDownsampleBufferTargetSize_DEPRECATED;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L22 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingRootComponent.h` (Public)


#### class `UDMXPixelMappingRootComponent`  
`class UDMXPixelMappingRootComponent : public UDMXPixelMappingBaseComponent`  
_L16-55_
- reflection: `UCLASS()`
- inherits: `UDMXPixelMappingBaseComponent`
- desc: Root component in the components tree
- L23 _protected prototype_ `virtual void PostLoad() override;`
- L24 _protected prototype_ `virtual void BeginDestroy() override;`
- L29 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L30 _public prototype_ `virtual void AddChild(UDMXPixelMappingBaseComponent* InComponent) override;`
- L31 _public prototype_ `virtual void RemoveChild(UDMXPixelMappingBaseComponent* InComponent) override;`
- L32 _public prototype_ `virtual void ResetDMX(EDMXPixelMappingResetDMXMode ResetMode = EDMXPixelMappingResetDMXMode::SendDefaultValues) override;`
- L33 _public prototype_ `virtual void SendDMX() override;`
- L34 _public prototype_ `virtual void Render() override;`
- L35 _public prototype_ `virtual void RenderAndSendDMX() override;`
- L36 _public prototype_ `virtual FString GetUserName() const override;`
- L40 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;` — Check if a Component can be moved under another one (used for copy/move/duplicate)
- L43 _public prototype_ `UDMXPixelMappingRendererComponent* FindRendererComponentByName(const FName& Name) const;` — Finds a renderer component by its name. Faster than UDMXPixelMappingBaseComponent::FindComponentByName
- L47 _private prototype_ `void OnComponentRenamed(UDMXPixelMappingBaseComponent* RenamedComponent);` — Called when a component in the PixelMapping was renamed
- L51 _private member_ `TMap<FName, TObjectPtr<UDMXPixelMappingRendererComponent>> CachedRendererComponentsByName;` — `UPROPERTY(Transient)` — Chached Renderer Component names and their actual object pointer. Useful to speed up access (see DMXPixelMappingSubsystem)
- L54 _private member_ `uint32 LastRenderedFrameNumber = 0;` — Holds the last rendered frame number, to avoid rendering multiple times in a single frame

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Components/DMXPixelMappingScreenComponent.h` (Public)


#### class `UDEPRECATED_DMXPixelMappingScreenComponent`  
`class UDEPRECATED_DMXPixelMappingScreenComponent : public UDMXPixelMappingOutputDMXComponent`  
_L25-154_
- reflection: `UE_DEPRECATED(5.5, "DMXScreenComponent is no longer supported in favor of a fully Fixture Patch based workflow.")`
- reflection: `UCLASS(Deprecated, meta = (DeprecationMessage = "Deprecated 5.5. DMXScreenComponent is no longer supported in favor of a fully Fixture Patch based workflow."))`
- inherits: `UDMXPixelMappingOutputDMXComponent`
- desc: DMX Screen component. Fully deprecated as of 5.5.
- L31 _public typedef_ `using ForEachPixelCallback = TFunctionRef<void(const int32 , const int32 , const int32 )>;`
- L35 _public prototype_ `UDEPRECATED_DMXPixelMappingScreenComponent();` — Default Constructor
- L39 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L44 _public prototype_ `virtual const FName& GetNamePrefix() override;`
- L45 _public prototype_ `virtual void SendDMX() override;`
- L50 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L51 _public function_ `virtual bool IsExposedToTemplate()`
- L56 _public prototype_ `virtual void QueueDownsample() override;`
- L60 _public prototype_ `virtual void RenderWithInputAndSendDMX() override;`
- L64 _public prototype_ `virtual bool CanBeMovedTo(const UDMXPixelMappingBaseComponent* Component) const override;` — Check if a Component can be moved under another one (used for copy/move/duplicate)
- L67 _public prototype_ `const FVector2D GetScreenPixelSize() const;` — Calculate screen size of the single pixel in screen component
- L70 _public prototype_ `void ForEachPixel(ForEachPixelCallback InCallback);` — Loop through X and Y pixels in screen component
- L74 _private prototype_ `void AddColorToSendBuffer(const FColor& Color, TArray<uint8>& OutDMXSendBuffer);` — Prepare the final color to send
- L79 _public member_ `bool bSendToAllOutputPorts;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Settings")` — If true, outputs to all DMX Output Ports
- L83 _public member_ `TArray<FDMXOutputPortReference> OutputPortReferences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Settings", Meta = (DisplayName = "DMX Output Ports", EditCondition = "!bSendToAllOutputPorts"))` — The port this render component outputs to
- L86 _public function_ `TSet<FDMXOutputPortSharedRef> GetOutputPorts() const` — Returns the output Ports of the renderer component
- L89 _public function_ `const TTuple<int32, int32> GetPixelDownsamplePositionRange() const` — Get range of the downsample pixel positions
- L93 _private prototype_ `UDMXPixelMappingRendererComponent* GetRendererComponent() const;` — Helper that returns the renderer component this component belongs to
- L97 _private member_ `TSet<FDMXOutputPortSharedRef> OutputPorts;` — The output port instances, generated from OutputPortReferences
- L101 _public member_ `int32 NumXCells;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mapping Settings", meta = (DisplayName = "X Cells", ClampMin = "1", ClampMax = "1000", UIMin = "1", UIMax = "100", DisplayPriority = "1"))`
- L104 _public member_ `int32 NumYCells;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mapping Settings", meta = (DisplayName = "Y Cells", ClampMin = "1", ClampMax = "1000", UIMin = "1", UIMax = "100", DisplayPriority = "1"))`
- L107 _public member_ `FDMXProtocolName ProtocolName_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Output Ports instead."))`
- L110 _public member_ `int32 LocalUniverse;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (ClampMin = "1", ClampMax = "100000", UIMin = "1", UIMax = "100000", DisplayPriority = "1"))`
- L113 _public member_ `int32 StartAddress;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (ClampMin = "1", ClampMax = "512", UIMin = "1", UIMax = "512", DisplayPriority = "1"))`
- L116 _public member_ `EDMXCellFormat PixelFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (DisplayName = "Color Space", DisplayPriority = "1"))`
- L119 _public member_ `EDMXPixelMappingDistribution Distribution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (DisplayPriority = "1"))`
- L122 _public member_ `bool bIgnoreAlphaChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (DisplayPriority = "1"))`
- L125 _public member_ `float PixelIntensity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1", DisplayPriority = "2"))`
- L128 _public member_ `float AlphaIntensity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1", DisplayPriority = "2"))`
- L132 _public member_ `bool bShowAddresses;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (DisplayPriority = "3"))`
- L135 _public member_ `bool bShowUniverse;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patch Settings", meta = (DisplayPriority = "3"))`
- L141 _private member_ `TSharedPtr<SDMXPixelMappingScreenComponentBox> ScreenComponentBox;` — Screen Component box used in the ComponentWidget
- L145 _private member_ `TTuple<int32, int32> PixelDownsamplePositionRange;` — Range of the downsample pixel positions
- L148 _private member_ `FSlateBrush Brush;`
- L150 _private member_ `bool bIsUpdateWidgetRequested;`
- L153 _private member_ `static const FVector2D MinGridSize;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/DMXPixelMapping.h` (Public)


#### class `UDMXPixelMapping`  
`class UDMXPixelMapping : public UObject , public FTickableGameObject`  
_L23-236_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject,FTickableGameObject`
- desc: DMX Pixel Mapping. Reads pixel colors of a Texture, Material or UMG widget and sends them as DMX.
- L27 _private typedef_ `using TComponentPredicate = TFunctionRef<void(UDMXPixelMappingBaseComponent*)>;`
- L30 _private typedef_ `template <typename Type> using TComponentPredicateType = TFunctionRef<void(Type*)>;`
- L35 _public prototype_ `UDMXPixelMapping();`
- L38 _public prototype_ `void StartSendingDMX();` — Starts to send DMX
- L41 _public prototype_ `void StopSendingDMX();` — Stops sending DMX
- L44 _public prototype_ `void PauseSendingDMX();` — Pauses sending DMX
- L47 _public function_ `bool IsSendingDMX() const` — Returns true if the pixel mapping is playing DMX. Note this returns false while it's paused
- L50 _public function_ `bool IsPaused() const` — Returns true if the pixel mapping is paused from playing DMX
- L53 _public function_ `void SetResetDMXMode(EDMXPixelMappingResetDMXMode InResetDMXMode)` — Sets how pixel mapping resets the channels it sends to when Stop Sending DMX is called.
- L56 _public function_ `EDMXPixelMappingResetDMXMode GetResetDMXMode() const` — Returns how the DMX channels used by pixel mapping are reset when playing the pixel mapping is stopped
- L59 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L60 _public prototype_ `virtual void PostLoad() override;`
- L65 _public function_ `UDMXPixelMappingRootComponent* GetRootComponent() const` — `UFUNCTION(BlueprintPure, Category = "DMX|PixelMapping")` — Get root component of the component tree
- L68 _public prototype_ `void CreateOrLoadObjects();` — Checks if nested objects are created, otherwise create them.
- L71 _public prototype_ `void PreloadWithChildren();` — Recurcevly preload all components in tree.
- L74 _public prototype_ `void DestroyInvalidComponents();` — Destroys invalid components. Useful when fixture type or fixture patch changed
- L77 _public prototype_ `UDMXPixelMappingBaseComponent* FindComponent(UDMXEntityFixturePatch* FixturePatch) const;` — Returns the first component that corresponds to the patch or null if none present
- L80 _public prototype_ `UDMXPixelMappingBaseComponent* FindComponent(const FName& Name) const;` — Find the component by name.
- L85 _public function_ `UDMXPixelMappingOutputComponent* FindComponent(TSharedPtr<SWidget> InWidget) const` — `UE_DEPRECATED(5.4, "Component widgets are no longer supported since 5.1. This function will always return nullptr.")` — Find the component by widget.
- L94 _public function_ `template <typename TComponentClass> TComponentClass* FindComponentOfClass(const FName& InName) const` — Looking for the first component of class by given name @param InName        The name to search @return				An instance of the templated Component
- L117 _public function_ `template <typename TComponentClass> void GetAllComponentsOfClass(TArray<TComponentClass*>& OutComponents) const` — Get all component by given class @param OutComponents        Found components
- L131 _public function_ `template <typename TComponentClass> void ForEachComponentOfClass(TComponentPredicateType<TComponentClass> Predicate) const` — Iterates through components by class with given Predicate callback
- L146 _public function_ `template <typename TComponentClass> void GetAllComponentsNamesOfClass(TArray<TSharedPtr<FName>>& InComponentNames) const` — Get array of FName pointers by given class @param OutComponents        Found components
- L160 _public prototype_ `void ForEachComponent(TComponentPredicate Predicate) const;` — Recursively Iterates through all compnents @param Predicate        Callback function
- L166 _public prototype_ `void RemoveComponent(UDMXPixelMappingBaseComponent* InComponent);` — Removes the Component from the hierarchy and all sub Components. @param InComponent        Component for remove
- L169 _public function_ `virtual bool IsTickableInEditor() const`
- L170 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L171 _public prototype_ `virtual bool IsTickable() const override;`
- L172 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L173 _public function_ `TStatId GetStatId() const`
- L182 _public member_ `TObjectPtr<UDMXPixelMappingRootComponent> RootComponent;` — `UPROPERTY()` — Holds the reference to root component
- L190 _public member_ `bool bGridSnappingEnabled = false;` — `UPROPERTY(NonTransactional)` — If true, grid snapping is enabled
- L194 _public member_ `int32 SnapGridColumns = 10;` — `UPROPERTY(NonTransactional)` — The number of columns in the grid
- L198 _public member_ `int32 SnapGridRows = 10;` — `UPROPERTY(NonTransactional)` — The number of rows in the grid
- L202 _public member_ `FLinearColor SnapGridColor;` — `UPROPERTY(NonTransactional)` — The color of the grid snapping grid
- L206 _public member_ `float ComponentLabelFontSize = 8.f;` — `UPROPERTY(NonTransactional)` — Font size for the component labels in the designer view
- L210 _public member_ `float DesignerExposure = 1.f;` — `UPROPERTY(NonTransactional)` — Exposure of the designer view
- L214 _public member_ `bool bNewComponentsUsePatchColor = true;` — `UPROPERTY(NonTransactional)` — If true, new components use the fixture patch color instead of the default pixel mapping color.
- L218 _public member_ `bool bEditorScaleChildrenWithParent = false;` — `UPROPERTY(Transient, NonTransactional)` — If true, editor is set to scale children with parent. This is forwarded from the editor module (DMXPixelMappingEditorSettings) to be accessible in the runtime module.
- L222 _public member_ `TObjectPtr<UTexture> ThumbnailImage;` — `UPROPERTY()` — Holds the Thumbnail image for this asset
- L227 _private member_ `bool bIsSendingDMX = false;` — True while the pixel mapping is sending DMX on tick
- L230 _private member_ `bool bIsPaused = false;` — True while the pixel mapping is paused
- L234 _private member_ `EDMXPixelMappingResetDMXMode ResetDMXMode;` — `UPROPERTY()` — Defines how DMX is reset when playback is stopped

#### Free symbols / members of external scopes

- L98 _function_ `ForEachComponent([&](UDMXPixelMappingBaseComponent* InComponent) { if (TComponentClass* CastComponent = Cast<TComponentClass>(InComponent)) { if (CastComponent->GetFName() == InName) { FoundComponent = CastComponent; return; } } });` (scope `UDMXPixelMapping::FindComponentOfClass`)
- L119 _function_ `ForEachComponent([&OutComponents](UDMXPixelMappingBaseComponent* InComponent) { if (TComponentClass* CastComponent = Cast<TComponentClass>(InComponent)) { OutComponents.Add(CastComponent); } });` (scope `UDMXPixelMapping::GetAllComponentsOfClass`)
- L133 _function_ `ForEachComponent([&Predicate](UDMXPixelMappingBaseComponent* InComponent) { if (TComponentClass* CastComponent = Cast<TComponentClass>(InComponent)) { Predicate(CastComponent); } });` (scope `UDMXPixelMapping::ForEachComponentOfClass`)
- L148 _function_ `ForEachComponent([&InComponentNames](UDMXPixelMappingBaseComponent* InComponent) { if (TComponentClass* CastComponent = Cast<TComponentClass>(InComponent)) { InComponentNames.Add(MakeShared<FName>(CastComponent->GetFName())); } });` (scope `UDMXPixelMapping::GetAllComponentsNamesOfClass`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/DMXPixelMappingRuntimeLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXPixelMappingRuntime, All, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXPixelMappingRuntime, All, All);`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/DMXPixelMappingRuntimeUtils.h` (Public)


#### class `FDMXPixelMappingRuntimeUtils`  
`class FDMXPixelMappingRuntimeUtils`  
_L17-31_
- L21 _public prototype_ `static void ConvertNormalizedAttributeValueToChannelValue(UDMXEntityFixturePatch* InFixturePatch, const FDMXAttributeName& InAttributeName, float InNormalizedValue, TMap<int32, uint8>& InOutChannelToValueMap);` — Adds a normalized attribute value to a DMX channel value map
- L25 _public prototype_ `static void HandleModulatorPropertyChange(UDMXPixelMappingBaseComponent* Component, FPropertyChangedChainEvent& PropertyChangedChainEvent, const TArray<TSubclassOf<UDMXModulator>>& ModulatorClasses, TArray<UDMXModulator*>& InOutModulators);` — Handles property changes for modulator classes in one place for Matrix and GroupItems, useless for other classes.
- L30 _private prototype_ `FDMXPixelMappingRuntimeUtils() = delete;` — No instances can be created

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/LayoutScripts/DMXPixelMappingLayoutScript.h` (Public)


#### struct `FDMXPixelMappingLayoutToken`  
`struct FDMXPixelMappingLayoutToken`  
_L18-56_
- reflection: `USTRUCT(BlueprintType)`
- desc: The position and size of a comoponent in a layout.
- L22 _public prototype_ `FDMXPixelMappingLayoutToken() = default;`
- L23 _public prototype_ `FDMXPixelMappingLayoutToken(TWeakObjectPtr<UDMXPixelMappingOutputComponent> OutputComponent);`
- L27 _public member_ `float PositionX = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layout Script")` — The position of the component on the X-Axis
- L31 _public member_ `float PositionY = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layout Script")` — The position of the component on the Y-Axis
- L35 _public member_ `float SizeX = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layout Script")` — The size of the component on the X-Axis
- L39 _public member_ `float SizeY = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layout Script")` — The size of the component on the Y-Axis
- L43 _public member_ `double RelativeRotation = 0.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layout Script")` — The rotation relative to the parent the component, applied after position
- L47 _public member_ `TWeakObjectPtr<UDMXPixelMappingOutputComponent> Component;` — `UPROPERTY(BlueprintReadWrite, Category = "Pixel Mapping Layout")` — The output component to which the token is applied
- L51 _public member_ `int32 FixtureID = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Layout Script")` — The Fixture ID of the Component's Fixture Patch, or 0 if the component has no Fixture Patch, or the Fixture ID is not set.
- L55 _private prototype_ `void InitializeFixtureID();` — Initializes the FixtureID member

#### class `UDMXPixelMappingLayoutScript`  
`class UDMXPixelMappingLayoutScript : public UObject`  
_L66-121_
- reflection: `UCLASS(BlueprintType, Blueprintable, EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: Allows scripting of Pixel Mapping Component Layouts. Override the Layout function to implement a layout. Note, layout scripts are applied in parent's unrotated space.
- L80 _public prototype_ `void Layout(const TArray<FDMXPixelMappingLayoutToken>& InTokens, TArray<FDMXPixelMappingLayoutToken>& OutTokens);` — `UFUNCTION(BlueprintNativeEvent, Category = "DMX")` — Lays out children of the selection according to OutTokens. Tokens that are not returned remain unchanged. Called when the script is loaded (unless set otherwise in editor) and when Properties were changed. @param InTokens		The child components of the current selection, as layout tokens. @param OutTokens		The layoyut of a component.
- L81 _public function_ `virtual void Layout_Implementation(const TArray<FDMXPixelMappingLayoutToken>& InTokens, TArray<FDMXPixelMappingLayoutToken>& OutTokens)`
- L84 _public function_ `virtual void SetNumTokens(int32 NewNumTokens)` — Sets the number of Tokens that will be passed when Layout is called
- L87 _public function_ `virtual void SetParentComponentPosition(const FVector2D NewPosition)` — Sets the position of the parent component where the components that are being layouted reside in.
- L90 _public function_ `virtual void SetParentComponentSize(const FVector2D& NewSize)` — Sets the size of the parent component where the components that are being layouted reside in.
- L93 _public function_ `virtual void SetParentComponentRotation(double NewRotation)` — Sets the size of the parent component where the components that are being layouted reside in.
- L96 _public function_ `virtual void SetTextureSize(const FVector2D& NewTextureSize)` — Sets the Texture Size
- L101 _protected member_ `int32 NumTokens = 0;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Layout Script")` — The number of tokens in the Layout.
- L105 _protected member_ `FVector2D ParentComponentPosition;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Layout Script")` — The position of the parent component where the components that are being layouted reside in.
- L109 _protected member_ `FVector2D ParentComponentSize;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Layout Script")` — The size of the parent component where the components that are being layouted reside in.
- L116 _protected member_ `double ParentRotation;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Layout Script")` — The rotation of the parent component where the components that are being layouted reside in. Note, the position property does not consider this rotation to ease calculations.
- L120 _protected member_ `FVector2D TextureSize;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Layout Script")` — The size of the texture this component is mapping.

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRuntime/Public/Templates/DMXPixelMappingComponentTemplate.h` (Public)


#### class `FDMXPixelMappingComponentTemplate`  
`class FDMXPixelMappingComponentTemplate : public TSharedFromThis<FDMXPixelMappingComponentTemplate>`  
_L20-60_
- inherits: `TSharedFromThis<FDMXPixelMappingComponentTemplate>`
- desc: The Component template represents a Component or a set of Components to create.
- L25 _public prototype_ `explicit FDMXPixelMappingComponentTemplate(TSubclassOf<UDMXPixelMappingBaseComponent> InComponentClass);` — Constructor for a template that can be specified by class
- L28 _public prototype_ `FDMXPixelMappingComponentTemplate(TSubclassOf<UDMXPixelMappingBaseComponent> InComponentClass, const FDMXEntityFixturePatchRef& InFixturePatchRef);` — Constructor for a group items template that can hold fixture patches
- L31 _public function_ `virtual ~FDMXPixelMappingComponentTemplate()` — Virtual Destructor
- L35 _public prototype_ `FText GetCategory() const;` — Gets the category for the Component
- L43 _public function_ `template <typename ComponentType> ComponentType* CreateComponent(UDMXPixelMappingRootComponent* InRootComponent)` — Creates an instance of the Component according to the class specified during construction. Returns nullptr if the ComponentType is not a ComponentType.
- L49 _public member_ `FText Name;` — The name of the Component template.
- L53 _private prototype_ `UDMXPixelMappingBaseComponent* CreateComponentInternal(UDMXPixelMappingRootComponent* InRootComponent);` — Internal create components without typecasting
- L56 _private member_ `TWeakObjectPtr<UClass> ComponentClass;` — The Component class that will be created by this template
- L59 _private member_ `FDMXEntityFixturePatchRef FixturePatchRef;` — Fixture Patch References, only for group item classes
