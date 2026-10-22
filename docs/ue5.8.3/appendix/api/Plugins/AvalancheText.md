# Plugins / AvalancheText

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheText`
- headers: 10; symbols: 211
- symbol kinds: class=10, enum=7, enumerator=23, function=17, macro=4, member=53, namespace=11, prototype=72, struct=10, typedef=4
- PrivateDependencyModuleNames: ActorModifierCore, Avalanche, UnrealEd
- PublicDependencyModuleNames: AvalancheCore, AvalancheMaterial, Core, CoreUObject, Engine, SlateCore, Text3D

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Private/AvaTextModule.h` (Private)


#### class `FAvaTextModule`  
`class FAvaTextModule : public IModuleInterface`  
_L8-21_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `void RegisterTextRendererDelegates();`
- L17 _public prototype_ `void UnregisterTextRendererDelegates();`
- L19 _public member_ `FDelegateHandle TextPreRendererUpdateHandle;`
- L20 _public member_ `FDelegateHandle TextPostRendererUpdateHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/AvaText3DComponent.h` (Public)


#### class `UAvaText3DComponent`  
`class UAvaText3DComponent : public UText3DComponent`  
_L14-91_
- reflection: `UCLASS(MinimalAPI , ClassGroup="Text3D" , PrioritizeCategories="Text Character Layout Geometry Material Rendering Transform" , HideCategories=(Replication,Collision,HLOD,Physics,Networking,Input,Actor,Cooking,LevelInstance,Streaming,DataLayers,WorldPartition))`
- inherits: `UText3DComponent`
- L23 _public prototype_ `UAvaText3DComponent();`
- L26 _public prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L33 _private member_ `FAvaFont MotionDesignFont_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use SetFont instead")` — `UPROPERTY()`
- L37 _private member_ `EAvaTextColoringStyle ColoringStyle_DEPRECATED = EAvaTextColoringStyle::Solid;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L41 _private member_ `FLinearColor Color_DEPRECATED = FLinearColor::White;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L45 _private member_ `FLinearColor ExtrudeColor_DEPRECATED = FLinearColor::Gray;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L49 _private member_ `FLinearColor BevelColor_DEPRECATED = FLinearColor::Gray;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L53 _private member_ `FAvaLinearGradientSettings GradientSettings_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L57 _private member_ `TObjectPtr<UTexture2D> MainTexture_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L61 _private member_ `FVector2D Tiling_DEPRECATED = FVector2D::One();` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L65 _private member_ `EAvaTextTranslucency TranslucencyStyle_DEPRECATED = EAvaTextTranslucency::None;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L69 _private member_ `float Opacity_DEPRECATED = 1.f;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L73 _private member_ `EAvaMaterialMaskOrientation MaskOrientation_DEPRECATED = EAvaMaterialMaskOrientation::LeftRight;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L77 _private member_ `float MaskSmoothness_DEPRECATED = 0.1f;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L81 _private member_ `float MaskOffset_DEPRECATED = 0.5f;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L85 _private member_ `float MaskRotation_DEPRECATED = 0.0f;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L89 _private member_ `bool bIsUnlit_DEPRECATED = true;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/AvaTextActor.h` (Public)


#### class `AAvaTextActor`  
`class AAvaTextActor : public AActor`  
_L16-44_
- reflection: `UCLASS(MinimalAPI, NotPlaceable, ClassGroup = (Text3D), DisplayName = "Motion Design Text", meta = (ComponentWrapperClass))`
- inherits: `AActor`
- desc: This actor is getting replaced by AText3DActor, do not use anymore
- L21 _public prototype_ `AAvaTextActor();`
- L23 _public function_ `UText3DComponent* GetText3DComponent() const`
- L28 _public prototype_ `FAvaColorChangeData GetColorData() const;`
- L29 _public prototype_ `void SetColorData(const FAvaColorChangeData& InColorData);`
- L33 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L39 _private member_ `TObjectPtr<UText3DComponent> Text3DComponent;` — `UPROPERTY(Category = "Text", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L43 _private member_ `TObjectPtr<UText3DCharacterTransform> Text3DCharacterTransform;` — `UE_DEPRECATED(5.6, "Use Transform Extension instead")` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/AvaTextDefs.h` (Public)


#### enum `EAvaTextColoringStyle`  
`enum class EAvaTextColoringStyle : uint8`  
_L9-16_
- reflection: `UENUM()`
- L11 _public enumerator_ `Invalid UMETA(Hidden)`
- L12 _public enumerator_ `Solid`
- L13 _public enumerator_ `Gradient`
- L14 _public enumerator_ `FromTexture`
- L15 _public enumerator_ `CustomMaterial`

#### enum `EAvaTextTranslucency`  
`enum class EAvaTextTranslucency : uint8`  
_L19-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `Invalid UMETA(Hidden)`
- L22 _public enumerator_ `None UMETA(DisplayName="Opaque")`
- L23 _public enumerator_ `Translucent`
- L24 _public enumerator_ `GradientMask`

#### enum `EAvaMaterialMaskOrientation`  
`enum class EAvaMaterialMaskOrientation : uint8`  
_L28-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `LeftRight UMETA(DisplayName = "Left to Right")`
- L31 _public enumerator_ `RightLeft UMETA(DisplayName = "Right to Left")`
- L32 _public enumerator_ `Custom`

#### enum `EAvaGradientDirection`  
`enum class EAvaGradientDirection : uint8`  
_L36-42_
- reflection: `UENUM()`
- L38 _public enumerator_ `None UMETA(Hidden)`
- L39 _public enumerator_ `Vertical`
- L40 _public enumerator_ `Horizontal`
- L41 _public enumerator_ `Custom`

#### struct `FAvaLinearGradientSettings`  
`struct FAvaLinearGradientSettings`  
_L45-77_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `EAvaGradientDirection Direction = EAvaGradientDirection::Vertical;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design")`
- L53 _public member_ `FLinearColor ColorA = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design")`
- L56 _public member_ `FLinearColor ColorB = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design")`
- L59 _public member_ `float Smoothness = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design", meta = (ClampMin = 0.0, ClampMax = 1.0))`
- L62 _public member_ `float Offset = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design", meta = (ClampMin = 0.0, ClampMax = 1.0))`
- L65 _public member_ `float Rotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design", meta = (ClampMin = 0.0, ClampMax = 1.0))`
- L67 _public function_ `bool operator==(const FAvaLinearGradientSettings& Other) const`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/Font/AvaFont.h` (Public)


#### struct `FAvaFont`  
`struct FAvaFont`  
_L12-220_
- reflection: `USTRUCT()`
- L22 _public prototype_ `static UFont* GetDefaultFont();` — Returns a default font (Roboto). The font will be loaded from asset if needed. In the unlikely case in which Roboto is not available, the first available font will be returned
- L31 _public prototype_ `static FString GenerateFontFormattedString(const FString& InFontName, const FString& InFontObjectPathName);` — Returns a formatted string representing a FAvaFont for the specified FontObjectPathName and FontName Useful e.g. when setting the value of multiple FAvaFonts using IPropertyHandle->SetPerObjectValues @param InFontName {The name of the font handled by UAvaFontObject} @param InFontObjectPathName {The path of the UAvaFontObject} @return {the formatted string}
- L40 _public prototype_ `static bool GenerateFontFormattedString(const UAvaFontObject* InFontObject, FString& OutFormattedString);` — Returns a formatted string representing a FAvaFont for the specified UAvaFontObject Useful e.g. when setting the value of multiple FAvaFonts using IPropertyHandle->SetPerObjectValues @param InFontObject {The UAvaFontObject used to generated the FAvaFont formatted string} @param OutFormattedString {will contain the formatted string} @return {true if successful}
- L48 _public prototype_ `static bool AreSameFont(const FAvaFont* InFontA, const FAvaFont* InFontB);` — Checks if the specified Ava Fonts are the same @param InFontA First font for comparison @param InFontB Second font for comparison @return true if Fonts are the same
- L51 _public prototype_ `FAvaFont();` — Default constructor: calling GetFont() right after the constructor will return the default font
- L54 _public prototype_ `FAvaFont(UAvaFontObject* InFontObject);` — this FAvaFont will be initialized using the provided UAvaFontObject
- L57 _public prototype_ `UFont* GetFont();` — Returns the currently stored font, or default font if none available. Preferred getter to just get the UFont and use it
- L60 _public prototype_ `FName GetFontName() const;` — Returns current font name, as FName
- L63 _public prototype_ `FString GetFontNameAsString() const;` — Returns current font name as FString
- L66 _public prototype_ `bool IsFavorite() const;` — Returns true if this FAvaFont is marked as favorite by the user
- L73 _public prototype_ `bool IsDefaultFont() const;` — Checks if this FAvaFont is referencing the default font. This will be happening also in fallback state. Use IsFallBackFont() if you explicitly need to know if this font is default because of a missing asset @return true if referenced font is the default one
- L81 _public prototype_ `bool IsFallbackFont() const;` — Checks if this FAvaFont is in fallback state. This happens when the font referenced by this FAvaFont is not available after de-serialization. This likely means that a UFont asset is missing. In fallback state, a FAvaFont will return the default font when GetFont() is called. @return true if this FAvaFont is in fallback state
- L84 _public prototype_ `bool IsMonospaced() const;` — Returns true if font is monospaced
- L87 _public prototype_ `bool IsBold() const;` — Returns true if font is bold
- L90 _public prototype_ `bool IsItalic() const;` — Returns true if font is italic
- L96 _public prototype_ `void SetFavorite(const bool bFavorite);` — Mark/unmark this font as favorite @param bFavorite {the flag to mark the font as favorite or not. True means favorite.}
- L101 _public prototype_ `void EnsureUsingCurrentVersion();` — Calling this function will null the now deprecated UFont CurrentFont reference, and use that UFont to initialize the currently used UAvaFontObject
- L107 _public function_ `const FString& GetMissingFontName() const` — In case this FAvaFont is in fallback state, this call can return the name of the missing font asset, if available. @return the name of the missing font asset.
- L113 _public prototype_ `bool HasValidFont() const;` — Checks if the currently referenced font asset is valid. Also internally checks if there's a composite font available within the UFont. @return true if font is valid
- L120 _public function_ `UAvaFontObject* GetFontObject() const` — Returns the currently stored UAvaFontObject. This is useful when dealing with font load/import. If only the current UFont is needed, use GetFont(). @return Current font object.
- L127 _public prototype_ `void SetFontObject(UAvaFontObject* InFontObject);` — Directly sets the current UAvaFontObject, and then updates this FAvaFont accordingly. If this FAvaFont is from past versions, the internal deprecated CurrentFont field will be set to nullptr. @param InFontObject {The FontObject which will be assigned to this FAvaFont}
- L130 _public prototype_ `EAvaFontSource GetFontSource() const;` — Returns current font source (System, Project or Invalid)
- L133 _public prototype_ `bool operator==(const FAvaFont& Other) const;` — Fonts are considered equal if they share the same font and font name
- L135 _public function_ `bool operator!=(const FAvaFont& Other) const`
- L144 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Called after serialization of FAvaFont. In case of missing font assets, the FAvaFont state will be marked as "FallbackFont"
- L177 _private prototype_ `static UAvaFontObject* GetDefaultAvaFontObject();` — Returns the default font object for Ava Fonts
- L180 _private prototype_ `static FAvaDefaultFontObjects& GetDefaultFontObjects();` — Returns a static FAvaDefaultFontObjects struct holding defaults values for fonts
- L183 _private prototype_ `static UFont* GetFontByName(const FString& InFontName);` — Search for a font asset based on a font name
- L186 _private prototype_ `void InitDefaults();` — Initializes default values
- L189 _private prototype_ `void RefreshName();` — Ensures the Font Name property is up to date with current font object
- L192 _private prototype_ `void RefreshAssetState();` — Refreshes asset state
- L195 _private prototype_ `void InitFromFont(UFont* InFont);` — Initialize this Avalanche Font using a UFont asset
- L202 _private member_ `TObjectPtr<UFont> CurrentFont_DEPRECATED;` — `UPROPERTY(Transient, meta=(DeprecatedProperty, DeprecationMessage="MotionDesignFontObject is the property currently handling the font."))` — Deprecated - used to reference the font used by FAvaFont. Older assets still have the font stored in this field. Calling GetFont() will move the font to the currently used MotionDesignFontObject property
- L206 _private member_ `TObjectPtr<UAvaFontObject> MotionDesignFontObject;` — `UPROPERTY()` — Stores the UAvaFontObject holding all the information about the font currently used by FAvaFont
- L210 _private member_ `FString FontName;` — `UPROPERTY()` — Updated when MotionDesignFontObject is set. Mainly used when loading FAvaFont, to help looking for a font in case the current font is null
- L213 _private member_ `EFontAssetState FontAssetState;` — The current font asset state, used internally to track the current state of FAvaFont with respect to its referenced font asset
- L216 _private member_ `bool bIsFavorite;` — FAvaFonts can be marked as favorites by the user
- L219 _private member_ `FString MissingFontName;` — When a font is missing and its name is available, it will be stored here. Old assets version cannot retrieve the name of the missing font

#### struct `FAvaFont::FAvaDefaultFontObjects`  
`struct FAvaDefaultFontObjects : public FGCObject`  
_L148-164_
- inherits: `FGCObject`
- desc: A struct to hold default values which we want to prevent from being GC'd
- L150 _public member_ `TObjectPtr<UFont> AvaDefaultFont;`
- L151 _public member_ `TObjectPtr<UAvaFontObject> AvaDefaultFontObject;`
- L154 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& OutCollector) override`
- L159 _public function_ `virtual FString GetReferencerName() const override`

#### enum `FAvaFont::EFontAssetState`  
`enum EFontAssetState`  
_L169-174_
- desc: Used to handle font state and possible loading issues
- L171 _public enumerator_ `DefaultFont` — Font is meant to be the default one
- L172 _public enumerator_ `SelectedFont` — Font is not the default one and has been explicitly set, either by serialization or UI
- L173 _public enumerator_ `FallbackFont` — Referenced font asset is missing

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaFont> : public TStructOpsTypeTraitsBase2<FAvaFont>`  
_L223-230_
- inherits: `TStructOpsTypeTraitsBase2<FAvaFont>`
- desc: We need to intercept FAvaFont serialization to detect if there's a missing font when loading

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L226-229_

#### Free symbols / members of external scopes

- L228 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon34dbe5e60103`) — void PostSerialize(const FArchive& Ar) in FAvaFont
- L232 _namespace_ `namespace UE`
- L232 _namespace_ `namespace Ava` (scope `UE`)
- L232 _namespace_ `namespace FontUtilities` (scope `UE::Ava`)
- L234 _prototype_ `void GetFontName(const UFont* InFont, FString& OutFontName);` (scope `UE::Ava::FontUtilities`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/Font/AvaFontObject.h` (Public)


#### enum `EAvaFontSource`  
`enum class EAvaFontSource : uint8`  
_L14-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `System = 0`
- L17 _public enumerator_ `Project = 1`
- L18 _public enumerator_ `Invalid = 2`

#### struct `FAvaSystemFontMetrics`  
`struct FAvaSystemFontMetrics`  
_L21-30_
- L23 _public member_ `TArray<int32> Charsets;` — this will become proper enum
- L25 _public member_ `bool bIsMonospaced;`
- L27 _public member_ `bool bIsBold;`
- L29 _public member_ `bool bIsItalic;`

#### struct `FSystemFontsRetrieveParams`  
`struct FSystemFontsRetrieveParams`  
_L32-54_
- L34 _public member_ `FString FontFamilyName;`
- L36 _public function_ `void AddFontFace(const FString& InFontFaceName, const FString& InFontFacePath)`
- L48 _public function_ `TConstArrayView<FString> GetFontFaceNames() const`
- L49 _public function_ `TConstArrayView<FString> GetFontFacePaths() const`
- L52 _private member_ `TArray<FString> FontFaceNames;`
- L53 _private member_ `TArray<FString> FontFacePaths;`

#### class `UAvaFontObject`  
`class UAvaFontObject : public UObject`  
_L57-117_
- reflection: `UCLASS()`
- inherits: `UObject`
- L63 _public member_ `TObjectPtr<UFont> Font = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L66 _private member_ `EAvaFontSource Source = EAvaFontSource::System;`
- L68 _private member_ `FAvaSystemFontMetrics Metrics;`
- L70 _private member_ `FSystemFontsRetrieveParams FontParameters;`
- L73 _public prototype_ `void InitProjectFont(UFont* InFont, const FString& InFontName);`
- L74 _public prototype_ `void InitSystemFont(const FSystemFontsRetrieveParams& FontParams, UFont* InFont);`
- L75 _public prototype_ `void Invalidate();`
- L76 _public prototype_ `void SwitchToProjectFont();`
- L77 _public prototype_ `void InitFromFontObject(const UAvaFontObject* Other);`
- L79 _public prototype_ `bool HasValidFont() const;`
- L81 _public function_ `const FString& GetFontName() const`
- L83 _public function_ `TObjectPtr<UFont> GetFont() const`
- L85 _public function_ `FAvaSystemFontMetrics GetMetrics() const`
- L87 _public function_ `void SetMetrics(const FAvaSystemFontMetrics& InMetrics)`
- L89 _public function_ `EAvaFontSource GetSource() const`
- L91 _public prototype_ `FString GetAlternateText() const;`
- L93 _public function_ `const FSystemFontsRetrieveParams& GetFontParameters() const`
- L95 _public prototype_ `bool IsMonospaced() const;`
- L96 _public prototype_ `bool IsBold() const;`
- L97 _public prototype_ `bool IsItalic() const;`
- L99 _public function_ `TArray<const UFontFace*> GetFontFaces() const`
- L116 _private member_ `FString FontName;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/MaterialBridge/AvaText3DComponentMaterialBridge.h` (Public)


#### struct `FAvaText3DComponentMaterialStateData`  
`struct FAvaText3DComponentMaterialStateData : public FAvaMaterialContainerState`  
_L13-19_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialContainerState`
- desc: Material state data for text3d components
- L18 _public member_ `TInstancedStruct<FAvaMaterialContainerState> MaterialExtensionStateData;` — `UPROPERTY()`

#### class `UE::Ava::FText3DComponentMaterialBridge`  
`class FText3DComponentMaterialBridge : public FMaterialBridge`  
_L25-39_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Text3D Components
- L28 _public typedef_ `using FContainerState = FAvaText3DComponentMaterialStateData;`
- L32 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L33 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L34 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L35 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L36 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L37 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHETEXT_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/MaterialBridge/AvaText3DDefaultExtensionMaterialBridge.h` (Public)


#### struct `FAvaText3DDefaultExtensionMaterialContainerState`  
`struct FAvaText3DDefaultExtensionMaterialContainerState : public FAvaText3DExtensionMaterialContainerState`  
_L12-18_
- reflection: `USTRUCT()`
- inherits: `FAvaText3DExtensionMaterialContainerState`
- desc: Material state data struct for the Default Text3D Material Extension
- L17 _public member_ `EText3DMaterialBlendMode BlendMode = EText3DMaterialBlendMode::Invalid;` — `UPROPERTY()`

#### class `UE::Ava::FText3DDefaultMaterialWriteSlot`  
`class FText3DDefaultMaterialWriteSlot : public FText3DMaterialWriteSlot`  
_L24-33_
- inherits: `FText3DMaterialWriteSlot`
- desc: Represents a slot for the Text3D default material extension for write
- L31 _protected prototype_ `virtual bool OnFeatureRequest(TConstStructView<FAvaMaterialBridgeFeature> InFeature) override;`

#### class `UE::Ava::FText3DDefaultExtensionMaterialBridge`  
`class FText3DDefaultExtensionMaterialBridge : public FText3DExtensionMaterialBridge`  
_L36-50_
- inherits: `FText3DExtensionMaterialBridge`
- desc: Material Bridge for the Default Text3D Material Extension
- L39 _public typedef_ `using Super = FText3DExtensionMaterialBridge;`
- L40 _public typedef_ `using FContainerState = FAvaText3DDefaultExtensionMaterialContainerState;`
- L44 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L45 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L46 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L47 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L48 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHETEXT_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/MaterialBridge/AvaText3DExtensionMaterialBridge.h` (Public)


#### struct `FAvaText3DExtensionMaterialData`  
`struct FAvaText3DExtensionMaterialData`  
_L17-31_
- reflection: `USTRUCT()`
- desc: State data for a material in Text3D material extensions
- L23 _public member_ `FName Tag = NAME_None;` — `UPROPERTY()` — Tag used to identify a material section, none = default
- L27 _public member_ `EText3DGroupType Group = EText3DGroupType::Front;` — `UPROPERTY()` — Group used to identify an entry in the material section
- L30 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY()`

#### struct `FAvaText3DExtensionMaterialContainerState`  
`struct FAvaText3DExtensionMaterialContainerState : public FAvaMaterialContainerState`  
_L35-41_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialContainerState`
- desc: Base material container state struct for Text3D material extensions
- L40 _public member_ `TArray<FAvaText3DExtensionMaterialData> MaterialData;` — `UPROPERTY()`

#### class `UE::Ava::FText3DMaterialWriteSlot`  
`class FText3DMaterialWriteSlot : public FMaterialBridgeWriteSlot`  
_L47-62_
- inherits: `FMaterialBridgeWriteSlot`
- desc: Represents a slot in Text3D material extension when accessing the slot with write access
- L50 _public prototype_ `explicit FText3DMaterialWriteSlot(TNotNull<UText3DMaterialExtensionBase*> InMaterialExtension, const UE::Text3D::Material::FMaterialParameters& InMaterialParameters);`
- L54 _protected prototype_ `virtual void OnMaterialChanged() override;`
- L58 _protected member_ `TNotNull<TObjectPtr<UText3DMaterialExtensionBase>> BaseMaterialExtension;` — The material extension that owns the slot
- L61 _protected member_ `UE::Text3D::Material::FMaterialParameters MaterialParameters;` — The material parameters identifying the slot

#### class `UE::Ava::FText3DExtensionMaterialBridge`  
`class FText3DExtensionMaterialBridge : public FMaterialBridge`  
_L65-80_
- inherits: `FMaterialBridge`
- desc: Base Material Bridge for Text3D material extensions
- L68 _public typedef_ `using FContainerState = FAvaText3DExtensionMaterialContainerState;`
- L72 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L73 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L74 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L75 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L76 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L77 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AVALANCHETEXT_API`
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheText/Public/MaterialBridge/AvaText3DManagedComponentMaterialBridge.h` (Public)


#### class `UE::Ava::FText3DManagedComponentMaterialBridge`  
`class FText3DManagedComponentMaterialBridge : public FMaterialBridge`  
_L16-23_
- inherits: `FMaterialBridge`
- desc: Material Bridge for components that are managed by the Text3D Slot accessing and material container state are not implemented by design as the material slot access for these is managed by the Text3D Component and its extensions. The Text3DComponent bridge should be used instead.
- L20 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L21 _protected prototype_ `virtual bool OnIsMaterialContainerSupported(FConstDataView InMaterialContainer) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHETEXT_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Ava` (scope `UE`)
