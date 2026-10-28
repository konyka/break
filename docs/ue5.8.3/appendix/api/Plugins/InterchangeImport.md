# Plugins / InterchangeImport

- module root: `Plugins/Interchange/Runtime/Source/Import`
- headers: 131; symbols: 1548
- symbol kinds: class=131, delegate=3, enum=8, enumerator=35, externvar=1, function=72, macro=58, member=380, namespace=78, prototype=691, struct=40, typedef=8, variable=43
- PrivateDependencyModuleNames: AssetRegistry, AudioMixer, BSPUtils, CinematicCamera, ClothingSystemRuntimeCommon, GLTFCore, GeometryCache, HairStrandsEditor, IESFile, ImageCore, ImageWrapper, InterchangeCommonParser, InterchangeFbxParser, InterchangeMessages, Json, MaterialEditor, RHI, RenderCore, SkeletalMeshUtilitiesCommon, TextureUtilitiesCommon, UnrealEd, VariantManager, VariantManagerContent
- PublicDependencyModuleNames: ClothingSystemRuntimeCommon, Core, CoreUObject, Engine, HairStrandsCore, InterchangeCommon, InterchangeCore, InterchangeDispatcher, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes, LevelSequence, MaterialX, MeshDescription, MovieScene, MovieSceneTracks, SkeletalMeshDescription, StaticMeshDescription

### `Plugins/Interchange/Runtime/Source/Import/Private/Animation/InterchangeLevelSequenceHelper.h` (Private)


#### struct `UE::Interchange::Private::FInterchangePropertyTracksHelper`  
`struct FInterchangePropertyTracksHelper`  
_L49-94_
- L51 _public prototype_ `static FInterchangePropertyTracksHelper& GetInstance();`
- L53 _public prototype_ `UMovieSceneSection* GetSection(UMovieScene* MovieScene, const UInterchangeAnimationTrackNode& AnimationTrackNode, const FGuid& ObjectBinding, EInterchangePropertyTracks Property) const;`
- L56 _private prototype_ `FInterchangePropertyTracksHelper();`
- L93 _private member_ `TMap<EInterchangePropertyTracks, FInterchangeProperty> PropertyTracks;`

#### struct `UE::Interchange::Private::FInterchangePropertyTracksHelper::FInterchangeProperty`  
`struct FInterchangeProperty`  
_L58-91_
- L60 _public function_ `FInterchangeProperty(FString&& ClassType, FString&& Path, FString&& Name) : ClassType`
- L66 _public function_ `FInterchangeProperty(FString&& ClassType, FString&& Path, FString&& Name, UEnum* EnumClass) : ClassType`
- L73 _public function_ `FInterchangeProperty(FString&& ClassType, FString&& Path, FString&& Name, int32 NumChannelsUsed) : ClassType`
- L80 _public function_ `FInterchangeProperty(FString && ClassType, FString && Path, FString && Name, UClass * ObjectPropertyClass) : ClassType`
- L87 _public member_ `FString ClassType;` — Float, Double, Byte, etc. Basically the class name of the UMovieSceneTrack
- L88 _public member_ `FString Path;`
- L89 _public member_ `FName Name;`
- L90 _public member_ `TVariant<UEnum*, int32, UClass*> VariantProperty;` — These are mutually exclusive, we can only have one of a kind (Either an Enum, or Number of channels used for a Vector, or an Object Path)

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L21 _function_ `template<typename T> TSubclassOf<T> FindObjectClass(const TCHAR* ClassName)` (scope `UE::Interchange::Private`) — Finds a UObject class by name. @param ClassName		The name of the class to look for (ie:UClass*->GetName()). @return				A sub class of UObject or nullptr.

### `Plugins/Interchange/Runtime/Source/Import/Private/Audio/Formats/InterchangeAudioFormatsPrivate.h` (Private)


#### struct `UE::Interchange::Audio::FAudioFormatCVarNames`  
`struct FAudioFormatCVarNames`  
_L13-23_
- L16 _public prototype_ `static const FString& GetAudioFormatCVarName_AIF();`
- L17 _public prototype_ `static const FString& GetAudioFormatCVarName_AIFF();`
- L18 _public prototype_ `static const FString& GetAudioFormatCVarName_OGG();`
- L19 _public prototype_ `static const FString& GetAudioFormatCVarName_FLAC();`
- L20 _public prototype_ `static const FString& GetAudioFormatCVarName_OPUS();`
- L21 _public prototype_ `static const FString& GetAudioFormatCVarName_MP3();`
- L22 _public prototype_ `static const FString& GetAudioFormatCVarName_WAV();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define WITH_SNDFILE_IO 0`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace Audio` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Import/Private/Gltf/InterchangeGltfPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GLTF`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Interchange` (scope `UE`)
- L22 _namespace_ `namespace Gltf` (scope `UE::Interchange`)
- L22 _namespace_ `namespace Private` (scope `UE::Interchange::Gltf`)
- L24 _variable_ `static float GltfUnitConversionMultiplier = 100.f;` (scope `UE::Interchange::Gltf::Private`)
- L27 _prototype_ `bool GetTransformAnimationPayloadData(const FString& PayLoadKey, const GLTF::FAsset& GltfAsset, FAnimationPayloadData& OutPayloadData);` (scope `UE::Interchange::Gltf::Private`) — Animation related functions
- L28 _prototype_ `bool GetMorphTargetAnimationPayloadData(const FString& PayLoadKey, const GLTF::FAsset& GltfAsset, FAnimationPayloadData& OutPayloadData);` (scope `UE::Interchange::Gltf::Private`)
- L29 _prototype_ `void GetT0Transform(const GLTF::FAnimation& GltfAnimation, const GLTF::FNode& AnimatedNode, const TArray<int32>& ChannelIndices, FTransform& OutTransform);` (scope `UE::Interchange::Gltf::Private`)
- L30 _prototype_ `bool GetBakedAnimationTransformPayloadData(const FString& PayLoadKey, const GLTF::FAsset& GltfAsset, FAnimationPayloadData& PayloadData);` (scope `UE::Interchange::Gltf::Private`)
- L34 _prototype_ `int32 GetRootNodeIndex(const GLTF::FAsset& GltfAsset, const TArray<int32>& NodeIndices);` (scope `UE::Interchange::Gltf::Private`) — Mesh related functions
- L36 _prototype_ `bool GetSkeletalMeshDescriptionForPayLoadKey(const GLTF::FAsset& GltfAsset, const FString& PayLoadKey, const FTransform& MeshGlobalTransform, FMeshDescription& MeshDescription, TArray<FString>* OutJointUniqueNames);` (scope `UE::Interchange::Gltf::Private`)
- L39 _prototype_ `bool GetStaticMeshPayloadDataForPayLoadKey(const GLTF::FAsset& GltfAsset, const FString& PayLoadKey, const FTransform& MeshGlobalTransform , FMeshDescription& MeshDescription);` (scope `UE::Interchange::Gltf::Private`)
- L44 _prototype_ `void HandleGLTFAnimations(UInterchangeBaseNodeContainer& NodeContainer, TArray<GLTF::FAnimation> Animations, const TArray<GLTF::FNode>& GLTFNodes, const TArray<GLTF::FSkinInfo>& GLTFSkins, const TMap<const GLTF::FNode*, FString>& GLTFNodeToInterchangeUidMap);` (scope `UE::Interchange::Gltf::Private`) — Process/Handle GLTF Animations:

### `Plugins/Interchange/Runtime/Source/Import/Private/InterchangeImportLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeImport, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeImport, Log, All);`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionAppend3Vector.h` (Private)


#### class `UMaterialExpressionMaterialXAppend3Vector`  
`class UMaterialExpressionMaterialXAppend3Vector : public UMaterialExpression`  
_L13-32_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that allows combining 3 channels together to create a vector with more channel than the original
- L18 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L21 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L24 _private member_ `FExpressionInput C;` — `UPROPERTY()`
- L28 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L29 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionAppend4Vector.h` (Private)


#### class `UMaterialExpressionMaterialXAppend4Vector`  
`class UMaterialExpressionMaterialXAppend4Vector : public UMaterialExpression`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that allows combining 4 channels together to create a vector with more channel than the original
- L20 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L23 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L26 _private member_ `FExpressionInput C;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput D;` — `UPROPERTY()`
- L33 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L34 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionBurn.h` (Private)


#### class `UMaterialExpressionMaterialXBurn`  
`class UMaterialExpressionMaterialXBurn : public UMaterialExpression`  
_L17-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: 1-(1-B)/A Result: Lerp(B, 1-(1-B)/A, Alpha)
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L25 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L32 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionContrast.h` (Private)


#### class `UMaterialExpressionMaterialXContrast`  
`class UMaterialExpressionMaterialXContrast : public UMaterialExpression`  
_L13-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that increases or decreases contrast of a float/color value using a linear slope multiplier.
- L18 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L21 _private member_ `FExpressionInput Amount;` — `UPROPERTY()`
- L24 _private member_ `FExpressionInput Pivot;` — `UPROPERTY()`
- L28 _private member_ `float ConstAmount = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionContrast, meta = (OverridingInputProperty = "Amount"))` — only used if Amount is not hooked up
- L32 _private member_ `float ConstPivot= 0.5f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionContrast, meta = (OverridingInputProperty = "Pivot"))` — only used if Pivot is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionDifference.h` (Private)


#### class `UMaterialExpressionMaterialXDifference`  
`class UMaterialExpressionMaterialXDifference : public UMaterialExpression`  
_L17-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: abs(B - A) Result: Lerp(B, abs(B - A), Alpha)
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L25 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L32 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionDisjointOver.h` (Private)


#### class `UMaterialExpressionMaterialXDisjointOver`  
`class UMaterialExpressionMaterialXDisjointOver : public UMaterialExpression`  
_L22-45_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Merge nodes take two 4-channel (color4) inputs and use the built-in alpha channel(s) to control the compositing of the A and B inputs. "A" and "B" refer to the non-alpha channels of the A and B inputs respectively, and "a" and "b" refer to the alpha channels of the A and B inputs. Merge nodes are only defined for float4 inputs Merge nodes support an optional float input Alpha , which can be used to mix the original B value with the result of the blend operation. Operation: A + B        if a + b <= 1; A + B(1-a)/b if a + b > 1 Result: Lerp(B, Op, Alpha)
- L27 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L30 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L33 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L37 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L41 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L42 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionDodge.h` (Private)


#### class `UMaterialExpressionMaterialXDodge`  
`class UMaterialExpressionMaterialXDodge: public UMaterialExpression`  
_L17-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: B/(1-A) Result: Lerp(B, B/(1-A), Alpha)
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L25 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L32 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionFractal.h` (Private)


#### class `UMaterialExpressionMaterialXFractal`  
`class UMaterialExpressionMaterialXFractal : public UMaterialExpression`  
_L15-81_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- L21 _private member_ `FExpressionInput Position;` — `UPROPERTY()` — The 3D position at which the noise is evaluated. By default the vector is in local space
- L25 _private member_ `FExpressionInput Amplitude;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAmplitude' if not specified"))` — Center-to-peak amplitude of the noise (peak-to-peak amplitude is 2x this value).
- L29 _private member_ `float ConstAmplitude = 1;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionFractal, meta = (OverridingInputProperty = "Amplitude"))` — only used if Amplitude is not hooked up
- L33 _private member_ `FExpressionInput Octaves;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstOctaves' if not specified"))` — The number of octaves of noise to be summed.
- L37 _private member_ `int32 ConstOctaves = 3;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionFractal, meta = (OverridingInputProperty = "Octaves"))` — only used if Octaves is not hooked up
- L41 _private member_ `FExpressionInput Lacunarity;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstLacunarity' if not specified"))` — The exponential scale between successive octaves of noise.
- L45 _private member_ `float ConstLacunarity = 2;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionFractal, meta = (OverridingInputProperty = "Lacunarity"))` — only used if Lacunarity is not hooked up
- L49 _private member_ `FExpressionInput Diminish;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstDiminish' if not specified"))` — The rate at which noise amplitude is diminished for each octave. Should be between 0.0 and 1.0
- L53 _private member_ `float ConstDiminish = 0.5;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionFractal, meta = (OverridingInputProperty = "Diminish"))` — only used if Diminish is not hooked up
- L56 _private member_ `float Scale_DEPRECATED = 1.f;` — `UPROPERTY()`
- L59 _private member_ `bool bTurbulence_DEPRECATED = false;` — `UPROPERTY()`
- L62 _private member_ `int32 Levels_DEPRECATED = 6;` — `UPROPERTY()`
- L65 _private member_ `float OutputMin_DEPRECATED = 0.f;` — `UPROPERTY()`
- L68 _private member_ `float OutputMax_DEPRECATED = 1.f;` — `UPROPERTY()`
- L72 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L73 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L74 _private prototype_ `virtual FName GetInputName(int32 InputIndex) const override;`
- L75 _private prototype_ `virtual void GetConnectorToolTip(int32 InputIndex, int32 OutputIndex, TArray<FString>& OutToolTip) override;`
- L78 _private member_ `bool bFractal2dType = false;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionIn.h` (Private)


#### class `UMaterialExpressionMaterialXIn`  
`class UMaterialExpressionMaterialXIn: public UMaterialExpression`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Merge nodes take two 4-channel (color4) inputs and use the built-in alpha channel(s) to control the compositing of the A and B inputs. "A" and "B" refer to the non-alpha channels of the A and B inputs respectively, and "a" and "b" refer to the alpha channels of the A and B inputs. Merge nodes are only defined for float4 inputs Merge nodes support an optional float input Alpha , which can be used to mix the original B value with the result of the blend operation. Operation: Ab Result: Lerp(B, Ab, Alpha)
- L26 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L32 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L36 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L40 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L41 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionLuminance.h` (Private)


#### enum `EMaterialXLuminanceMode`  
`enum class EMaterialXLuminanceMode : uint8`  
_L15-22_
- reflection: `UENUM()`
- L17 _public enumerator_ `ACEScg`
- L18 _public enumerator_ `Rec709`
- L19 _public enumerator_ `Rec2020`
- L20 _public enumerator_ `Rec2100 = Rec2020`
- L21 _public enumerator_ `Custom`

#### class `UMaterialExpressionMaterialXLuminance`  
`class UMaterialExpressionMaterialXLuminance : public UMaterialExpression`  
_L25-45_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- L30 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L33 _private member_ `FLinearColor LuminanceFactors;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLuminance, Meta = (ShowAsInputPin = "Advanced"))` — Color component factors for converting a color to greyscale.
- L36 _private member_ `EMaterialXLuminanceMode LuminanceMode;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLuminance, Meta = (ShowAsInputPin = "Advanced"))`
- L40 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L41 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L42 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionMask.h` (Private)


#### class `UMaterialExpressionMaterialXMask`  
`class UMaterialExpressionMaterialXMask : public UMaterialExpression`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Merge nodes take two 4-channel (color4) inputs and use the built-in alpha channel(s) to control the compositing of the A and B inputs. "A" and "B" refer to the non-alpha channels of the A and B inputs respectively, and "a" and "b" refer to the alpha channels of the A and B inputs. Merge nodes are only defined for float4 inputs Merge nodes support an optional float input Alpha , which can be used to mix the original B value with the result of the blend operation. Operation: B*a Result: Lerp(B, B*a, Alpha)
- L26 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L32 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L36 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L40 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L41 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionMatte.h` (Private)


#### class `UMaterialExpressionMaterialXMatte`  
`class UMaterialExpressionMaterialXMatte : public UMaterialExpression`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Merge nodes take two 4-channel (color4) inputs and use the built-in alpha channel(s) to control the compositing of the A and B inputs. "A" and "B" refer to the non-alpha channels of the A and B inputs respectively, and "a" and "b" refer to the alpha channels of the A and B inputs. Merge nodes are only defined for float4 inputs Merge nodes support an optional float input Alpha , which can be used to mix the original B value with the result of the blend operation. Operation: A*a + B*(1-a) Result: Lerp(B, A*a + B*(1-a), Alpha)
- L26 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L32 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L36 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L40 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L41 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionMinus.h` (Private)


#### class `UMaterialExpressionMaterialXMinus`  
`class UMaterialExpressionMaterialXMinus : public UMaterialExpression`  
_L17-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: B - A Result: Lerp(B, B - A, Alpha)
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L25 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L32 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionMod.h` (Private)


#### class `UMaterialExpressionMaterialXMod`  
`class UMaterialExpressionMaterialXMod : public UMaterialExpression`  
_L15-36_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: The remaining fraction after dividing an incoming input by a value and subtracting the integer portion. Unlike UE FMod or Modulo expressions, Mod always returns a non-negative result, matching the interpretation of the GLSL and OSL mod() function (not fmod()). This is computed as x - y * floor(x/y).
- L20 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L23 _private member_ `FExpressionInput B;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstB' if not specified"))`
- L27 _private member_ `float ConstB = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "B"))` — only used if B is not hooked up
- L31 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L32 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L33 _private prototype_ `virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionOut.h` (Private)


#### class `UMaterialExpressionMaterialXOut`  
`class UMaterialExpressionMaterialXOut : public UMaterialExpression`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Merge nodes take two 4-channel (color4) inputs and use the built-in alpha channel(s) to control the compositing of the A and B inputs. "A" and "B" refer to the non-alpha channels of the A and B inputs respectively, and "a" and "b" refer to the alpha channels of the A and B inputs. Merge nodes are only defined for float4 inputs Merge nodes support an optional float input Alpha , which can be used to mix the original B value with the result of the blend operation. Operation: A(1-b) Result: Lerp(B, A(1-b), Alpha)
- L26 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L32 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L36 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L40 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L41 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionOver.h` (Private)


#### class `UMaterialExpressionMaterialXOver`  
`class UMaterialExpressionMaterialXOver : public UMaterialExpression`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Merge nodes take two 4-channel (color4) inputs and use the built-in alpha channel(s) to control the compositing of the A and B inputs. "A" and "B" refer to the non-alpha channels of the A and B inputs respectively, and "a" and "b" refer to the alpha channels of the A and B inputs. Merge nodes are only defined for float4 inputs Merge nodes support an optional float input Alpha , which can be used to mix the original B value with the result of the blend operation. Operation: A + B(1-a) Result: Lerp(B, A + B(1-a), Alpha)
- L26 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L32 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L36 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L40 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L41 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionOverlay.h` (Private)


#### class `UMaterialExpressionMaterialXOverlay`  
`class UMaterialExpressionMaterialXOverlay : public UMaterialExpression`  
_L18-41_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: 2*A*B         if B < 0.5 1-2(1-A)(1-B) if B >= 0.5 Result: Lerp(B, Op, Alpha)
- L23 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L26 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L29 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L33 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L37 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L38 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionPlace2D.h` (Private)


#### class `UMaterialExpressionMaterialXPlace2D`  
`class UE_DEPRECATED(5.5, "UMaterialExpressionMaterialXPlace2D is now deprecated, please use Material Function MX_Place2D") UMaterialExpressionMaterialXPlace2D : public UMaterialExpression`  
_L17-61_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Transform incoming UV texture coordinates from one 2D frame of reference to another. operationorder (integer enum): the order in which to perform the transform operations. "0" or "SRT" performs -pivot, scale, rotate, translate, +pivot as per the original implementation matching the behavior of certain DCC packages, and "1" or "TRS" performs -pivot, translate, rotate, scale, +pivot which does not introduce texture shear. Default is 0 "SRT" for backward compatibility.
- L22 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L27 _private member_ `FExpressionInput Pivot;` — `UPROPERTY()` — The pivot coordinate for scale and rotate: this is subtracted from u,v before applying scale/rotate, then added back after. Default is (0,0).
- L33 _private member_ `FExpressionInput Scale;` — `UPROPERTY()` — Divide the u,v coord (after subtracting pivot ) by this, so a scale (2,2) makes the texture image appear twice as big. Negative values can be used to flip or flop the texture space. Default is (1,1).
- L39 _private member_ `FExpressionInput Offset;` — `UPROPERTY()` — Subtract this amount from the scaled/rotated/“pivot added back” UV coordinate; since U0,V0 is typically the lower left corner, a positive offset moves the texture image up and right. Default is (0,0).
- L44 _private member_ `FExpressionInput RotationAngle;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstRotationAngle' if not specified"))` — Rotate u,v coord (after subtracting pivot) by this amount in degrees, so a positive value rotates UV coords counter-clockwise, and the image clockwise.
- L48 _private member_ `float ConstRotationAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpression, meta = (OverridingInputProperty = "RotationAngle"))` — only used if RotationAngle is not hooked up
- L52 _private member_ `uint8 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = MaterialExpression, meta = (OverridingInputProperty = "Coordinates"))` — only used if Coordinates is not hooked up
- L56 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L57 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L58 _private prototype_ `virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionPlus.h` (Private)


#### class `UMaterialExpressionMaterialXPlus`  
`class UMaterialExpressionMaterialXPlus : public UMaterialExpression`  
_L17-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: A + B Result: Lerp(B, A + B, Alpha)
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L25 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L32 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionPremult.h` (Private)


#### class `UMaterialExpressionMaterialXPremult`  
`class UMaterialExpressionMaterialXPremult : public UMaterialExpression`  
_L14-27_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Multiply the RGB channels of the input by the Alpha channel of the input. Input must be of type float4
- L19 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L23 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L24 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionRamp4.h` (Private)


#### class `UMaterialExpressionMaterialXRamp4`  
`class UMaterialExpressionMaterialXRamp4: public UMaterialExpression`  
_L13-47_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that computes a 4-corner bilinear value ramp..
- L18 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()` — The value at the top-left (U0V1) corner
- L26 _private member_ `FExpressionInput B;` — `UPROPERTY()` — The value at the top-right (U1V1) corner
- L30 _private member_ `FExpressionInput C;` — `UPROPERTY()` — The value at the bottom-left (U0V0) corner
- L34 _private member_ `FExpressionInput D;` — `UPROPERTY()` — The value at the bottom-right (U1V0) corner
- L38 _private member_ `uint8 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = MaterialExpression, meta = (OverridingInputProperty = "Coordinates"))` — only used if Coordinates is not hooked up
- L42 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L43 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L44 _private prototype_ `virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionRampLeftRight.h` (Private)


#### class `UMaterialExpressionMaterialXRampLeftRight`  
`class UMaterialExpressionMaterialXRampLeftRight : public UMaterialExpression`  
_L13-36_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that computes a left-to-right bilinear value ramp.
- L18 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L21 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L24 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `uint8 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionTextureSample, meta = (OverridingInputProperty = "Coordinates"))` — only used if Coordinates is not hooked up
- L32 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L33 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionRampTopBottom.h` (Private)


#### class `UMaterialExpressionMaterialXRampTopBottom`  
`class UMaterialExpressionMaterialXRampTopBottom : public UMaterialExpression`  
_L13-36_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that computes a top-to-bottom bilinear value ramp.
- L18 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L21 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L24 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `uint8 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionTextureSample, meta = (OverridingInputProperty = "Coordinates"))` — only used if Coordinates is not hooked up
- L32 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L33 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionRange.h` (Private)


#### class `UMaterialExpressionMaterialXRange`  
`class UMaterialExpressionMaterialXRange : public UMaterialExpression`  
_L14-64_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that Remap a value from one range to another, optionally applying a gamma correction in the middle, and optionally clamping output values.
- L19 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L22 _private member_ `FExpressionInput InputLow;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Low value for input range. Defaults to 'ConstInputLowDefault' if not specified"))`
- L25 _private member_ `FExpressionInput InputHigh;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "High value for input range. Defaults to 'ConstInputHighDefault' if not specified"))`
- L28 _private member_ `FExpressionInput TargetLow;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Low value for target range. Defaults to 'ConstTargetLowDefault' if not specified"))`
- L31 _private member_ `FExpressionInput TargetHigh;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "High value for target range. Defaults to 'ConstTargetHighDefault' if not specified"))`
- L34 _private member_ `FExpressionInput Gamma;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Inverse exponent applied to Input after first transforming from InputLow..InputHigh to 0..1, gamma values greater than 1.0 make midtones brighter. Defaults to 'ConstGamma' if not specified"))`
- L37 _private member_ `FExpressionInput Clamp;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "If true, the output is clamped to the range TargetLow..TargetHigh. Defaults to 'ConstClamp' if not specified"))`
- L40 _private member_ `float ConstInputLow;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionRange, meta = (OverridingInputProperty = "InputLow"))`
- L43 _private member_ `float ConstInputHigh;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionRange, meta = (OverridingInputProperty = "InputHigh"))`
- L46 _private member_ `float ConstTargetLow;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionRange, meta = (OverridingInputProperty = "TargetLow"))`
- L49 _private member_ `float ConstTargetHigh;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionRange, meta = (OverridingInputProperty = "TargetHigh"))`
- L52 _private member_ `float ConstGamma;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionRange, meta = (OverridingInputProperty = "Gamma"))`
- L55 _private member_ `bool bConstClamp;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionRange, meta = (OverridingInputProperty = "Clamp"))`
- L59 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L60 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionRemap.h` (Private)


#### class `UMaterialExpressionMaterialXRemap`  
`class UMaterialExpressionMaterialXRemap : public UMaterialExpression`  
_L13-51_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that Remap a value from one range to another.
- L18 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L21 _private member_ `FExpressionInput InputLow;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'MinDefault1' if not specified"))`
- L24 _private member_ `FExpressionInput InputHigh;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'MaxDefault1' if not specified"))`
- L27 _private member_ `FExpressionInput TargetLow;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'MinDefault2' if not specified"))`
- L30 _private member_ `FExpressionInput TargetHigh;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'MaxDefault1' if not specified"))`
- L33 _private member_ `float InputLowDefault;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionClamp, meta = (OverridingInputProperty = "InputLow"))`
- L36 _private member_ `float InputHighDefault;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionClamp, meta = (OverridingInputProperty = "InputHigh"))`
- L39 _private member_ `float TargetLowDefault;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionClamp, meta = (OverridingInputProperty = "TargetLow"))`
- L42 _private member_ `float TargetHighDefault;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionClamp, meta = (OverridingInputProperty = "TargetHigh"))`
- L46 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L47 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionRotate2D.h` (Private)


#### class `UMaterialExpressionMaterialXRotate2D`  
`class UE_DEPRECATED(5.5, "UMaterialExpressionMaterialXRotate2D is now deprecated, please use UMaterialExpressionRotator") UMaterialExpressionMaterialXRotate2D : public UMaterialExpression`  
_L12-35_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that rotates a vector2 value about the origin in 2D.
- L17 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L22 _private member_ `FExpressionInput RotationAngle;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "RotationAngle in degrees. Defaults to 'ConstRotationAngle' if not specified"))` — The amount to rotate, specified in degrees, with positive values rotating the incoming vector counterclockwise.
- L26 _private member_ `float ConstRotationAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionAngle, meta = (OverridingInputProperty = "RotationAngle"))` — only used if RotationAngle is not hooked up
- L30 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L31 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L32 _private prototype_ `virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionScreen.h` (Private)


#### class `UMaterialExpressionMaterialXScreen`  
`class UMaterialExpressionMaterialXScreen : public UMaterialExpression`  
_L17-40_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Blend nodes take two 1-4 channel inputs and apply the same operator to all channels. Blend nodes support an optional float input mix , which can be used to mix the original B value with the result of the blend operation. Operation: 1-(1-A)(1-B) Result: Lerp(B, 1-(1-F)(1-B), Alpha)
- L22 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L25 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L28 _private member_ `FExpressionInput Alpha;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstAlpha' if not specified"))`
- L32 _private member_ `float ConstAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLinearInterpolate, meta = (OverridingInputProperty = "Alpha"))` — only used if Alpha is not hooked up
- L36 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L37 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionSplitLeftRight.h` (Private)


#### class `UMaterialExpressionMaterialXSplitLeftRight`  
`class UMaterialExpressionMaterialXSplitLeftRight : public UMaterialExpression`  
_L13-43_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that computes a left-right split matte, split at a specified u value.
- L18 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L21 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L24 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L27 _private member_ `FExpressionInput Center;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCenter' if not specified"))`
- L31 _private member_ `float ConstCenter;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionMultiply, meta = (OverridingInputProperty = "Center"))` — only used if A is not hooked up
- L35 _private member_ `uint8 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionTextureSample, meta = (OverridingInputProperty = "Coordinates"))` — only used if Coordinates is not hooked up
- L39 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L40 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionSplitTopBottom.h` (Private)


#### class `UMaterialExpressionMaterialXSplitTopBottom`  
`class UMaterialExpressionMaterialXSplitTopBottom : public UMaterialExpression`  
_L13-43_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: A material expression that computes a top-bottom split matte, split at a specified v value.
- L18 _private member_ `FExpressionInput Coordinates;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCoordinate' if not specified"))`
- L21 _private member_ `FExpressionInput A;` — `UPROPERTY()`
- L24 _private member_ `FExpressionInput B;` — `UPROPERTY()`
- L27 _private member_ `FExpressionInput Center;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstCenter' if not specified"))`
- L31 _private member_ `float ConstCenter;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionMultiply, meta = (OverridingInputProperty = "Center"))` — only used if A is not hooked up
- L35 _private member_ `uint8 ConstCoordinate;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionTextureSample, meta = (OverridingInputProperty = "Coordinates"))` — only used if Coordinates is not hooked up
- L39 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L40 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialExpressions/MaterialExpressionUnpremult.h` (Private)


#### class `UMaterialExpressionMaterialXUnpremult`  
`class UMaterialExpressionMaterialXUnpremult : public UMaterialExpression`  
_L15-28_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, MinimalAPI, meta = (Private))`
- inherits: `UMaterialExpression`
- desc: Divide the RGB channels of the input by the Alpha channel of the input. If the Alpha value is zero, the original color4 input value is passed through unchanged. Input must be of type float4
- L20 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L24 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L25 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXDirectionalLightShader.h` (Private)


#### class `FMaterialXDirectionalLightShader`  
`class FMaterialXDirectionalLightShader : public FMaterialXLightShaderAbstract`  
_L9-25_
- inherits: `FMaterialXLightShaderAbstract`
- L16 _protected prototype_ `FMaterialXDirectionalLightShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L20 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L22 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr PointLightShaderNode) override;`
- L24 _public prototype_ `static void GetDirection(MaterialX::InputPtr DirectionInput, FTransform& Transform);`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXDisplacementShader.h` (Private)


#### class `FMaterialXDisplacementShader`  
`class FMaterialXDisplacementShader : public FMaterialXSurfaceShaderAbstract`  
_L10-24_
- inherits: `FMaterialXSurfaceShaderAbstract`
- desc: Handles <displacement> node from the pbrlib, we derive the class from FMaterialXSurfaceShaderAbstract to avoid issue when we StaticCast in the SurfaceMaterial, and because we also need a shader graph
- L17 _protected prototype_ `FMaterialXDisplacementShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L23 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr DisplacementNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXGltfPbr.h` (Private)


#### class `FMaterialXGltfPbr`  
`class FMaterialXGltfPbr : public FMaterialXSurfaceShaderAbstract`  
_L9-23_
- inherits: `FMaterialXSurfaceShaderAbstract`
- L14 _private prototype_ `FMaterialXGltfPbr(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L18 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L20 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr GltfPbrNode) override;`
- L22 _public prototype_ `virtual MaterialX::InputPtr GetInputNormal(MaterialX::NodePtr GltfPbrNode, const char*& InputNormal) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXMixShader.h` (Private)


#### class `FMaterialXMixShader`  
`class FMaterialXMixShader : public FMaterialXSurfaceShaderAbstract`  
_L8-22_
- inherits: `FMaterialXSurfaceShaderAbstract`
- L15 _protected prototype_ `FMaterialXMixShader(UInterchangeBaseNodeContainer & BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr MixNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXOpenPBRSurfaceShader.h` (Private)


#### class `FMaterialXOpenPBRSurfaceShader`  
`class FMaterialXOpenPBRSurfaceShader : public FMaterialXSurfaceShaderAbstract`  
_L8-24_
- inherits: `FMaterialXSurfaceShaderAbstract`
- L15 _protected prototype_ `FMaterialXOpenPBRSurfaceShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr OpenPBRSurfaceNode) override;`
- L23 _public prototype_ `virtual MaterialX::InputPtr GetInputNormal(MaterialX::NodePtr OpenPbrSurfaceShaderNode, const char*& InputNormal) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXPointLightShader.h` (Private)


#### class `FMaterialXPointLightShader`  
`class FMaterialXPointLightShader : public FMaterialXLightShaderAbstract`  
_L8-30_
- inherits: `FMaterialXLightShaderAbstract`
- L15 _protected prototype_ `FMaterialXPointLightShader(UInterchangeBaseNodeContainer & BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr PointLightShaderNode) override;`
- L23 _public prototype_ `static float GetDecayRate(MaterialX::InputPtr DecayRateInput);`
- L25 _public prototype_ `static void GetPosition(MaterialX::InputPtr PositionInput, FTransform& Transform);`
- L27 _public prototype_ `void SetDecayRate();`
- L29 _public prototype_ `void SetPosition();`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXSpotLightShader.h` (Private)


#### class `FMaterialXSpotLightShader`  
`class FMaterialXSpotLightShader : public FMaterialXPointLightShader`  
_L8-26_
- inherits: `FMaterialXPointLightShader`
- L15 _protected prototype_ `FMaterialXSpotLightShader(UInterchangeBaseNodeContainer & BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr SpotLightShaderNode) override;`
- L23 _public prototype_ `void SetInnerAngle();`
- L25 _public prototype_ `void SetOuterAngle();`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXStandardSurfaceShader.h` (Private)


#### class `FMaterialXStandardSurfaceShader`  
`class FMaterialXStandardSurfaceShader : public FMaterialXSurfaceShaderAbstract`  
_L8-24_
- inherits: `FMaterialXSurfaceShaderAbstract`
- L15 _protected prototype_ `FMaterialXStandardSurfaceShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr StandardSurfaceNode) override;`
- L23 _public prototype_ `virtual MaterialX::InputPtr GetInputNormal(MaterialX::NodePtr StandardSurfaceNode, const char*& InputNormal) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXSurfaceMaterial.h` (Private)


#### class `FMaterialXSurfaceMaterial`  
`class FMaterialXSurfaceMaterial : public FMaterialXBase`  
_L8-22_
- inherits: `FMaterialXBase`
- L15 _protected prototype_ `FMaterialXSurfaceMaterial(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr SurfaceMaterialNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXSurfaceShader.h` (Private)


#### class `FMaterialXSurfaceShader`  
`class FMaterialXSurfaceShader : public FMaterialXSurfaceShaderAbstract`  
_L10-24_
- inherits: `FMaterialXSurfaceShaderAbstract`
- desc: Handles <surface> node from the pbrlib, acts more or less as a generic surface shader
- L17 _protected prototype_ `FMaterialXSurfaceShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L23 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr SurfaceNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXSurfaceUnlitShader.h` (Private)


#### class `FMaterialXSurfaceUnlitShader`  
`class FMaterialXSurfaceUnlitShader : public FMaterialXSurfaceShaderAbstract`  
_L8-22_
- inherits: `FMaterialXSurfaceShaderAbstract`
- L15 _protected prototype_ `FMaterialXSurfaceUnlitShader(UInterchangeBaseNodeContainer & BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr SurfaceUnlitNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXUsdPreviewSurfaceShader.h` (Private)


#### class `FMaterialXUsdPreviewSurfaceShader`  
`class FMaterialXUsdPreviewSurfaceShader : public FMaterialXSurfaceShaderAbstract`  
_L9-25_
- inherits: `FMaterialXSurfaceShaderAbstract`
- L16 _protected prototype_ `FMaterialXUsdPreviewSurfaceShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L20 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L22 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr UsdPreviewSurfaceNode) override;`
- L24 _public prototype_ `virtual MaterialX::InputPtr GetInputNormal(MaterialX::NodePtr UsdPreviewSurfaceNode, const char*& InputNormal) const override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXVolumeMaterial.h` (Private)


#### class `FMaterialXVolumeMaterial`  
`class FMaterialXVolumeMaterial : public FMaterialXBase`  
_L8-22_
- inherits: `FMaterialXBase`
- L15 _protected prototype_ `FMaterialXVolumeMaterial(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L19 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr VolumeMaterialNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/MaterialX/MaterialXUtils/MaterialXVolumeShader.h` (Private)


#### class `FMaterialXVolumeShader`  
`class FMaterialXVolumeShader : public FMaterialXSurfaceShaderAbstract`  
_L10-24_
- inherits: `FMaterialXSurfaceShaderAbstract`
- desc: Handles <volume> node from the pbrlib, acts more or less as a generic volume shader
- L17 _protected prototype_ `FMaterialXVolumeShader(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L21 _public prototype_ `static TSharedRef<FMaterialXBase> MakeInstance(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L23 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr SurfaceNode) override;`

### `Plugins/Interchange/Runtime/Source/Import/Private/Texture/TextureTranslatorUtilities.h` (Private)


#### class `UE::Interchange::FTextureTranslatorUtilities`  
`class FTextureTranslatorUtilities`  
_L18-39_
- L21 _public prototype_ `static bool Generic2DTextureTranslate(const UInterchangeSourceData* SourceData, UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L23 _public prototype_ `static bool GenericTextureCubeTranslate(const UInterchangeSourceData* SourceData, UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L25 _public prototype_ `static bool GenericTextureCubeArrayTranslate(const UInterchangeSourceData* SourceData, UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L27 _public prototype_ `static bool GenericTexture2DArrayTranslate(const UInterchangeSourceData* SourceData, UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L29 _public prototype_ `static bool GenericVolumeTextureTranslate(const UInterchangeSourceData* SourceData, UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L31 _public prototype_ `static bool GenericTextureLightProfileTranslate(const UInterchangeSourceData* SourceData, UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L33 _public prototype_ `static bool IsTranslatorValid(const UInterchangeTranslatorBase& TextureTranslator, const TCHAR* Format);`
- L35 _public prototype_ `static bool LoadSourceBuffer(const UInterchangeTranslatorBase& TextureTranslator, const TCHAR* Format, TArray64<uint8>& SourceDataBuffer);`
- L37 _public prototype_ `static void LogError(const UInterchangeTranslatorBase& TextureTranslator, FText&& ErrorText);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Animation/InterchangeAnimSequenceFactory.h` (Public)


#### class `UInterchangeAnimSequenceFactory`  
`class UInterchangeAnimSequenceFactory : public UInterchangeFactoryBase`  
_L20-91_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L28 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L29 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L31 _public prototype_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks) override;`
- L33 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L35 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L37 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L39 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L40 _public prototype_ `virtual void BuildObject_GameThread(const FSetupObjectParams& Arguments, bool& OutPostEditchangeCalled) override;`
- L42 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L43 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L44 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L45 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L46 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L62 _private prototype_ `bool IsBoneTrackAnimationValid(const UInterchangeAnimSequenceFactoryNode* AnimSequenceFactoryNode, const FImportAssetObjectParams& Arguments);`
- L65 _private member_ `TObjectPtr<UAnimSequence> AnimSequence = nullptr;` — The imported AnimSequence
- L68 _private member_ `FBoneTrackData BoneTrackData;` — Bone track animations payload data
- L71 _private member_ `FMorphTargetData MorphTargetData;` — Morph target curves payload data
- L74 _private member_ `TMap< TTuple<FString, FInterchangeAnimationPayLoadKey>, UE::Interchange::FAnimationPayloadQuery> BoneAnimationPayloadQueries;` — Animation queries
- L77 _private member_ `TMap< TTuple<FString, FInterchangeAnimationPayLoadKey>, UE::Interchange::FAnimationPayloadData> BoneAnimationPayloadResults;` — Animation queries results

#### struct `UInterchangeAnimSequenceFactory::FBoneTrackData`  
`struct FBoneTrackData`  
_L48-53_
- L50 _public member_ `TMap<const UInterchangeSceneNode*, UE::Interchange::FAnimationPayloadData> PreProcessedAnimationPayloads;`
- L51 _public member_ `double MergedRangeStart = 0.0;`
- L52 _public member_ `double MergedRangeEnd = 0.0;`

#### struct `UInterchangeAnimSequenceFactory::FMorphTargetData`  
`struct FMorphTargetData`  
_L55-59_
- L57 _public member_ `TMap<FString, UE::Interchange::FAnimationPayloadData> CurvesPayloads;`
- L58 _public member_ `TMap<FString, FString> CurveNodeNamePerPayloadKey;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L79 _function_ `friend bool operator==(const TTuple<FString, FInterchangeAnimationPayLoadKey>& A, const TTuple<FString, FInterchangeAnimationPayLoadKey>& B)`
- L84 _function_ `friend uint32 GetTypeHash(const TTuple<FString, FInterchangeAnimationPayLoadKey>& Tupple)`

### `Plugins/Interchange/Runtime/Source/Import/Public/Animation/InterchangeAnimationPayloadInterface.h` (Public)


#### class `UInterchangeAnimationPayloadInterface`  
`class UInterchangeAnimationPayloadInterface : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeAnimationPayloadInterface`  
`class IInterchangeAnimationPayloadInterface`  
_L24-48_
- desc: Animation payload interface. Derive from this interface if your payload can import skeletal mesh
- L34 _public function_ `virtual bool PreferGroupingBoneAnimationQueriesTogether() const` — Return true if the translator want to import all bone animations in one query, false otherwise. @Note - The fbx translator use the fbx sdk which cache the global transform but dirty the cache every time we evaluate at a different time. The goal is to evaluate all bones at the same time.
- L47 _public prototype_ `virtual TArray<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQuery) const = 0;` — Get animation payload data for the specified payload key. It return an array of FRichCurve (Rich curve are float curve we can interpolate) or array of "Step" curve or an array of Baked Transformations, depending on Type @param PayloadQueries - A PayloadQuery contains all the necessary data for a Query to be processed (Including SceneNodeUID, PayloadKey, TimeDescription). @return - The resulting PayloadData.

### `Plugins/Interchange/Runtime/Source/Import/Public/Animation/InterchangeLevelSequenceFactory.h` (Public)


#### class `UInterchangeLevelSequenceFactory`  
`class UInterchangeLevelSequenceFactory : public UInterchangeFactoryBase`  
_L15-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L23 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L24 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L25 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L26 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L32 _private member_ `const UInterchangeTranslatorBase* Translator = nullptr;`
- L34 _private prototype_ `UObject* ImportObjectSourceData(const FImportAssetObjectParams& Arguments);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslatorBase.h` (Public)


#### class `UInterchangeAudioTranslatorBase`  
`class UInterchangeAudioTranslatorBase : public UInterchangeTranslatorBase , public IInterchangeAudioPayloadInterface`  
_L13-31_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UInterchangeTranslatorBase,IInterchangeAudioPayloadInterface`
- L21 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;` — Begin UInterchangeTranslatorBase API
- L22 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L23 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;`
- L26 _protected prototype_ `virtual UInterchangeAudioSoundWaveNode* Translate_Internal(UInterchangeBaseNodeContainer& BaseNodeContainer) const;`
- L29 _protected prototype_ `void LogError(FText&& ErrorText) const;`
- L30 _protected prototype_ `void LogWarning(FText&& WarningText) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_AIF.h` (Public)


#### class `UInterchangeAudioTranslator_AIF`  
`class UInterchangeAudioTranslator_AIF : public UInterchangeAudioTranslatorBase`  
_L10-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L14 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_AIFF.h` (Public)


#### class `UInterchangeAudioTranslator_AIFF`  
`class UInterchangeAudioTranslator_AIFF : public UInterchangeAudioTranslatorBase`  
_L10-15_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L14 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_FLAC.h` (Public)


#### class `UInterchangeAudioTranslator_FLAC`  
`class UInterchangeAudioTranslator_FLAC : public UInterchangeAudioTranslatorBase`  
_L10-16_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_MP3.h` (Public)


#### class `UInterchangeAudioTranslator_MP3`  
`class UInterchangeAudioTranslator_MP3 : public UInterchangeAudioTranslatorBase`  
_L10-16_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_OGG.h` (Public)


#### class `UInterchangeAudioTranslator_OGG`  
`class UInterchangeAudioTranslator_OGG : public UInterchangeAudioTranslatorBase`  
_L10-16_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_OPUS.h` (Public)


#### class `UInterchangeAudioTranslator_OPUS`  
`class UInterchangeAudioTranslator_OPUS : public UInterchangeAudioTranslatorBase`  
_L10-16_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/Formats/InterchangeAudioTranslator_WAV.h` (Public)


#### class `UInterchangeAudioTranslator_WAV`  
`class UInterchangeAudioTranslator_WAV : public UInterchangeAudioTranslatorBase`  
_L10-16_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeAudioTranslatorBase`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/InterchangeAudioPayloadData.h` (Public)


#### struct `UE::Interchange::FSoundWaveFactoryInfo`  
`struct FSoundWaveFactoryInfo`  
_L11-19_
- L13 _public member_ `int32 ChannelCount = 0;`
- L14 _public member_ `int32 SizeOfSample = 0;`
- L15 _public member_ `int32 NumSamples = 0;`
- L16 _public member_ `int32 NumFrames = 0;`
- L17 _public member_ `int32 SamplesPerSec = 0;`
- L18 _public member_ `int32 SampleDataOffset = -1;`

#### struct `UE::Interchange::FInterchangeAudioPayloadData`  
`struct FInterchangeAudioPayloadData`  
_L21-26_
- L23 _public member_ `FSoundWaveFactoryInfo FactoryInfo;`
- L24 _public member_ `FWaveModInfo WaveModInfo;`
- L25 _public member_ `TArray<uint8> Buffer;`

#### struct `FInterchangeAudioPayloadDataUtils`  
`struct FInterchangeAudioPayloadDataUtils`  
_L29-33_
- L32 _public prototype_ `static TOptional<UE::Interchange::FInterchangeAudioPayloadData> GetAudioPayloadFromSourceFileKey(const FString& PayloadSourceFileKey);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/InterchangeAudioPayloadInterface.h` (Public)


#### class `UInterchangeAudioPayloadInterface`  
`class UInterchangeAudioPayloadInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeAudioPayloadInterface`  
`class IInterchangeAudioPayloadInterface`  
_L22-37_
- desc: Audio Payload interface. Derive from it if your payload can import Audio
- L33 _public function_ `virtual TOptional< UE::Interchange::FInterchangeAudioPayloadData > GetAudioPayloadData(const FString& PayloadSourceFileKey) const` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the import sound wave data, this maybe converted data if the format is other than '.wav'. The TOptional will not be set if there is an error.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Audio/InterchangeAudioSoundWaveFactory.h` (Public)


#### class `UInterchangeAudioSoundWaveFactory`  
`class UInterchangeAudioSoundWaveFactory : public UInterchangeFactoryBase`  
_L16-48_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L22 _public prototype_ `virtual UClass* GetFactoryClass() const override;` — UInterchangeFactoryBase interface
- L23 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L24 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L25 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L26 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L28 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L29 _public prototype_ `virtual void FinalizeObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L32 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;` — To allow reimporting
- L33 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L34 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L35 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L36 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L39 _private prototype_ `void SetUpSoundWaveFromPayload(const FImportAssetObjectParams& Arguments, USoundWave*& SoundWaveAsset, const UE::Interchange::FInterchangeAudioPayloadData& AudioPayloadData, FImportAssetResult& ImportAssetResult);`
- L40 _private prototype_ `bool SetUpMultichannelSoundWave(const FImportAssetObjectParams& Arguments, USoundWave*& SoundWaveAsset, const UE::Interchange::FInterchangeAudioPayloadData& AudioPayloadData, FImportAssetResult& ImportAssetResult);`
- L42 _private prototype_ `void StopComponentsUsingImportedSound(USoundWave* SoundWaveAsset);`
- L44 _private prototype_ `void LogError(const FImportAssetObjectParams& Arguments, FImportAssetResult& ImportAssetResult, const FText& ErrorText);`
- L47 _private member_ `TArray<TObjectPtr<UAudioComponent>> ComponentsToRestart;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Fbx/InterchangeFbxTranslator.h` (Public)


#### enum `EInterchangeCoordinateSystemPolicy`  
`enum class EInterchangeCoordinateSystemPolicy : uint8`  
_L25-30_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `MatchUpForwardAxes UMETA(DisplayName = "Match Up and Forward Axes", Tooltip = "The Up and Front axes in the FBX are mapped to the Up and Forward axes in UEFN.\nAfter import, the model will have the same apparent orientation in UEFN as itn oes in the FBX")`
- L28 _public enumerator_ `MatchUpAxis UMETA(DisplayName = "Match Up Axis", Tooltip = "The Up axis in the FBX is mapped to the Up axis in UEFN.\nAfter import, the model will have the same apparent vertical axis in UEFN as it does in the FBX, but its Forward and Left orientations may not match the FBX.")`
- L29 _public enumerator_ `KeepXYZAxes UMETA(DisplayName = "Keep XYZ Axes", Tooltip = "The X, Y, and Z axes in the FBX are mapped directly to UEFN's internal X, Y, and Z axes, only flipping the Y axis to change from right - handed to left - handed coordinates.\nThis applies the least change to the data, but is least likely to match UEFN's Left, Up, and Forward axis conventions.")`

#### class `UInterchangeFbxTranslatorSettings`  
`class UInterchangeFbxTranslatorSettings : public UInterchangeTranslatorSettings`  
_L34-78_
- reflection: `UCLASS(BlueprintType, editinlinenew, MinimalAPI)`
- inherits: `UInterchangeTranslatorSettings`
- L40 _public member_ `EInterchangeCoordinateSystemPolicy CoordinateSystemPolicy = EInterchangeCoordinateSystemPolicy::MatchUpForwardAxes;` — `UPROPERTY(EditAnywhere, Transient, Category = "FBX Translator", meta = (EditCondition = "bUsingLUFCoordinateSystem", EditConditionHides, ToolTip = "Select strategy to map FBX coordinates system to UE coordinates system"))`
- L44 _public member_ `bool bConvertScene = true;` — `UPROPERTY(EditAnywhere, Category = "FBX Translator", meta = (EditCondition = "!bUsingLUFCoordinateSystem", EditConditionHides))` — Whether to convert FBX scene axis system to Unreal axis system.
- L48 _public member_ `bool bForceFrontXAxis = false;` — `UPROPERTY(EditAnywhere, Category = "FBX Translator", meta = (EditCondition = "bConvertScene && !bUsingLUFCoordinateSystem", EditConditionHides))` — Whether to force the front axis to be align with X instead of -Y default.
- L52 _public member_ `bool bConvertSceneUnit = true;` — `UPROPERTY(EditAnywhere, Category = "FBX Translator")` — Whether to convert the scene from FBX unit to UE unit (centimeter).
- L56 _public member_ `bool bKeepFbxNamespace = false;` — `UPROPERTY(EditAnywhere, Category = "FBX Translator")` — Whether to keep the name space from FBX name.
- L60 _public member_ `bool bConsiderClusterBeforePoseForMeshBindPose = false;` — `UPROPERTY(EditAnywhere, Category = "FBX Translator")` — Whether to first consider Fbx Clusters instead of FbxPoses for Bind Pose Calculations.
- L64 _public member_ `bool bUseUfbxParser = false;` — `UPROPERTY(EditAnywhere, Category = "FBX Translator", meta = (EditCondition = "bDisplayUfbxParser", EditConditionHides, DisplayName="Use uFBX Translator (Experimental)", Tooltip = "If enabled, the ufbx SDK is used instead of the FBX SDK."))` — Whether to use the uFBX parser.
- L68 _public member_ `bool bUsingLUFCoordinateSystem;` — `UPROPERTY(Transient, VisibleDefaultsOnly, Category = InternalOnly, meta = (EditCondition = "false", EditConditionHides))` — Use to enable or not the UEFN UI
- L72 _public member_ `bool bDisplayUfbxParser = true;` — `UPROPERTY(Transient, VisibleDefaultsOnly, Category = InternalOnly, meta = (EditCondition = "false", EditConditionHides))` — Use to enable or not the UEFN UI
- L74 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L76 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UInterchangeFbxTranslator`  
`class UInterchangeFbxTranslator : public UInterchangeTranslatorBase , public IInterchangeTexturePayloadInterface , public IInterchangeMeshPayloadInterface , public IInterchangeAnimationPayloadInterface`  
_L81-186_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface,IInterchangeMeshPayloadInterface,IInterchangeAnimationPayloadInterface`
- L88 _public prototype_ `UInterchangeFbxTranslator();`
- L90 _public prototype_ `static void CleanUpTemporaryFolder();`
- L93 _public prototype_ `virtual bool IsThreadSafe() const override;` — Begin UInterchangeTranslatorBase API
- L94 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;`
- L95 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L96 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L97 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;`
- L98 _public prototype_ `virtual void ReleaseSource() override;`
- L99 _public prototype_ `virtual void ImportFinish() override;`
- L100 _public prototype_ `virtual UInterchangeTranslatorSettings* GetSettings() const override;`
- L101 _public prototype_ `virtual void SetSettings(const UInterchangeTranslatorSettings* InterchangeTranslatorSettings) override;`
- L116 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param InSourceData - The source data containing the data to translate @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the imported data. The TOptional will not be set if there is an error.
- L133 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform) const override` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param SourceData - The source data containing the data to translate @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the imported data. The TOptional will not be set if there is an error.
- L140 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const override;`
- L146 _public function_ `virtual bool PreferGroupingBoneAnimationQueriesTogether() const override`
- L151 _public prototype_ `virtual TArray<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries) const override;`
- L155 _private prototype_ `FString CreateLoadFbxFileCommand(const FString& FbxFilePath, const bool bConvertScene, const bool bForceFrontXAxis, const bool bConvertSceneUnit, const bool bKeepFbxNamespace, const bool bConsiderClusterBeforePoseForMeshBindPose) const;`
- L157 _private prototype_ `FString CreateFetchMeshPayloadFbxCommand(const FString& FbxPayloadKey, const FTransform& MeshGlobalTransform) const;`
- L159 _private prototype_ `FString CreateFetchPayloadFbxCommand(const FString& FbxPayloadKey) const;`
- L161 _private prototype_ `FString CreateFetchAnimationBakeTransformPayloadFbxCommand(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries) const;`
- L167 _private member_ `mutable TUniquePtr<UE::Interchange::FInterchangeDispatcher> Dispatcher;` — Dispatcher is mutable since it is create during the Translate operation We do not want to allocate the dispatcher and start the InterchangeWorker process in the constructor because Archetype, CDO and registered translators will never translate a source.
- L170 _private member_ `mutable TObjectPtr<UInterchangeFbxTranslatorSettings> CacheFbxTranslatorSettings = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`
- L174 _private member_ `bool bUseWorkerImport = false;` — If true this translator will use the dispatcher (InterchangeWorker program) to translate and return payloads. If false, this translator will not use the dispatcher
- L176 _private member_ `mutable UE::Interchange::FInterchangeFbxParser FbxParser;`
- L178 _private member_ `FString ResultFolder;`
- L179 _private member_ `mutable uint64 StartTime = 0;`
- L180 _private member_ `mutable FString FileName;`
- L182 _private member_ `mutable uint64 MeshPayloadTime = 0;` — #interchange_debug
- L183 _private member_ `mutable uint64 MeshMeshCount = 0;`
- L184 _private member_ `mutable uint64 MeshTriangleCount = 0;`
- L185 _private member_ `mutable uint64 MeshVertexCount = 0;`

### `Plugins/Interchange/Runtime/Source/Import/Public/Gltf/InterchangeGLTFMaterial.h` (Public)


#### enum `UE::Interchange::GLTFMaterials::EShadingModel`  
`enum EShadingModel : uint8`  
_L163-172_
- L165 _public enumerator_ `DEFAULT = 0` — MetalRoughness
- L166 _public enumerator_ `UNLIT`
- L167 _public enumerator_ `CLEARCOAT`
- L168 _public enumerator_ `SHEEN`
- L169 _public enumerator_ `TRANSMISSION`
- L170 _public enumerator_ `SPECULARGLOSSINESS`
- L171 _public enumerator_ `SHADINGMODELCOUNT`

#### enum `UE::Interchange::GLTFMaterials::EAlphaMode`  
`enum EAlphaMode : uint8`  
_L174-179_
- L176 _public enumerator_ `Opaque = 0`
- L177 _public enumerator_ `Mask`
- L178 _public enumerator_ `Blend`

#### struct `UE::Interchange::GLTFMaterials::FGLTFMaterialInformation`  
`struct FGLTFMaterialInformation`  
_L181-195_
- L183 _public member_ `FString MaterialFunctionPath;`
- L184 _public member_ `FString MaterialPath;`
- L185 _public member_ `TArray<FString> MaterialFunctionOutputs;`
- L187 _public function_ `FGLTFMaterialInformation(const FString& InMaterialFunctionPath, const FString& InMaterialPath, const TArray<FString>& InMaterialFunctionOutputs) : MaterialFunctionPath(InMaterialFunctionPath) , MaterialPath(InMaterialPath) , MaterialFunctionOutputs(InMaterialFunctionOutputs)`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GLTF`
- L13 _externvar_ `extern const FString InterchangeGltfMaterialAttributeIdentifier;`
- L17 _macro_ `#define INTERCHANGE_GLTF_STRINGIFY(x) #x` — OffsetScale for MaterialInstances Offset_X Offset_Y Scale_X Scale_Y for Materials
- L18 _macro_ `#define DECLARE_INTERCHANGE_GLTF_MI_MAP(MapName) inline const FString MapName##Texture = TEXT(INTERCHANGE_GLTF_STRINGIFY(MapName ## Texture)); \`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Interchange` (scope `UE`)
- L28 _namespace_ `namespace GLTFMaterials` (scope `UE::Interchange`)
- L31 _namespace_ `namespace Inputs` (scope `UE::Interchange::GLTFMaterials`)
- L34 _namespace_ `namespace PostFix` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L36 _variable_ `inline const FString Color_RGB = TEXT("_RG` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L37 _variable_ `inline const FString Color_A = TEXT("_A"` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L39 _variable_ `inline const FString TexCoord = TEXT("_Te` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L41 _variable_ `inline const FString OffsetX = TEXT("_Of` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L42 _variable_ `inline const FString OffsetY = TEXT("_Of` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L43 _variable_ `inline const FString ScaleX = TEXT("_Sc` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L44 _variable_ `inline const FString ScaleY = TEXT("_Sc` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L46 _variable_ `inline const FString OffsetScale = TEXT("_Of` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L48 _variable_ `inline const FString Rotation = TEXT("_Ro` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L50 _variable_ `inline const FString TilingMethod = TEXT("_Ti` (scope `UE::Interchange::GLTFMaterials::Inputs::PostFix`)
- L54 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(BaseColor) inline const FString BaseColorFactor = TEXT("Bas` (scope `UE::Interchange::GLTFMaterials::Inputs`) — MetalRoughness specific:
- L56 _variable_ `inline const FString BaseColorFactor_RGB = BaseColorFactor + PostFix::Color_RGB;` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Connection to inputs from BaseColorFactor.RGB
- L57 _variable_ `inline const FString BaseColorFactor_A = BaseColorFactor + PostFix::Color_A;` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Connection to inputs from BaseColorFactor.A
- L59 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(MetallicRoughness) inline const FString MetallicFactor = TEXT("Met` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L61 _variable_ `inline const FString RoughnessFactor = TEXT("Rou` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L63 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Specular) inline const FString SpecularFactor = TEXT("Spe` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L66 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(SpecularColor) inline const FString SpecularColorFactor = TEXT("Spe` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L70 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Diffuse) inline const FString DiffuseFactor = TEXT("Dif` (scope `UE::Interchange::GLTFMaterials::Inputs`) — SpecularGlossiness specific
- L72 _variable_ `inline const FString DiffuseFactor_RGB = DiffuseFactor + PostFix::Color_RGB;` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Connection to inputs from BaseColorFactor.RGB
- L73 _variable_ `inline const FString DiffuseFactor_A = DiffuseFactor + PostFix::Color_A;` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Connection to inputs from BaseColorFactor.A
- L75 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(SpecularGlossiness) inline const FString SpecFactor = TEXT("Spe` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L77 _variable_ `inline const FString GlossinessFactor = TEXT("Glo` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L81 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Normal) inline const FString NormalScale = TEXT("Nor` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Generic:
- L84 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Emissive) inline const FString EmissiveFactor = TEXT("Emi` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L86 _variable_ `inline const FString EmissiveStrength = TEXT("Emi` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L88 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Occlusion) inline const FString OcclusionStrength = TEXT("Occ` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L91 _variable_ `inline const FString IOR = TEXT("IOR` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L93 _variable_ `inline const FString AlphaCutoff = TEXT("Alp` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L94 _variable_ `inline const FString AlphaMode = TEXT("Alp` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L97 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(ClearCoat) inline const FString ClearCoatFactor = TEXT("Cle` (scope `UE::Interchange::GLTFMaterials::Inputs`) — ClearCoat specific:
- L100 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(ClearCoatRoughness) inline const FString ClearCoatRoughnessFactor = TEXT("Cle` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L103 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(ClearCoatNormal) inline const FString ClearCoatNormalScale = TEXT("Cle` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L108 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(SheenColor) inline const FString SheenColorFactor = TEXT("She` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Sheen specific:
- L111 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(SheenRoughness) inline const FString SheenRoughnessFactor = TEXT("She` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L116 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Transmission) inline const FString TransmissionFactor = TEXT("Tra` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Transmission specific:
- L121 _variable_ `inline const FString IridescenceIOR = TEXT("Iri` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Iridescence specific:
- L123 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Iridescence) inline const FString IridescenceFactor = TEXT("Iri` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L126 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(IridescenceThickness) inline const FString IridescenceThicknessMinimum = TEXT("Iri` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L128 _variable_ `inline const FString IridescenceThicknessMaximum = TEXT("Iri` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L132 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Anisotropy);` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Anisotropy Specific:
- L133 _variable_ `inline const FString AnisotropyStrength = TEXT("Ani` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L134 _variable_ `inline const FString AnisotropyRotation = TEXT("Ani` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L137 _prototype_ `DECLARE_INTERCHANGE_GLTF_MI_MAP(Thickness);` (scope `UE::Interchange::GLTFMaterials::Inputs`) — Volume Specific:
- L138 _variable_ `inline const FString ThicknessFactor = TEXT("Thi` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L139 _variable_ `inline const FString AttenuationDistance = TEXT("Att` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L140 _variable_ `inline const FString AttenuationColor = TEXT("Att` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L142 _namespace_ `namespace Configuration` (scope `UE::Interchange::GLTFMaterials::Inputs`)
- L146 _variable_ `inline const FString bHasBaseColorTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`) — For StaticSwitch optimizations: Note: only usable in Editor, the Default values are true so that Runtime will still use the complete graph (without optimization).
- L147 _variable_ `inline const FString bHasMetallicRoughnessTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L148 _variable_ `inline const FString bHasDiffuseSpecGlossTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L149 _variable_ `inline const FString bHasEmissiveTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L150 _variable_ `inline const FString bHasNormalTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L151 _variable_ `inline const FString bHasOcclusionTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L152 _variable_ `inline const FString bHasSpecularTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L153 _variable_ `inline const FString bHasSpecularColorTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L154 _variable_ `inline const FString bHasClearCoatTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L155 _variable_ `inline const FString bHasSheenTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L156 _variable_ `inline const FString bHasTransmissionTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L157 _variable_ `inline const FString bHasIridescence = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L158 _variable_ `inline const FString bHasAnisotropyTextureAndOrRotation = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`) — AnistropyRotation can affect the Tangents so we check
- L159 _variable_ `inline const FString bHasThicknessTexture = TEXT("bHa` (scope `UE::Interchange::GLTFMaterials::Inputs::Configuration`)
- L197 _variable_ `static const TMap<EShadingModel, FGLTFMaterialInformation> ShadingModelToMaterialInformation = { {EShadingModel::DEFAULT, FGLTFMaterialInformation( TEXT("/InterchangeAssets/gltf/MaterialBodies/MF_Default_Body.MF_Default_Body"), TEXT("/InterchangeAssets/gltf/M_Default.M_Default"), TArray<FString>{ TEXT("BaseColor"), TEXT("Metallic"), TEXT("Specular"), TEXT("Roughness"), TEXT("EmissiveColor"), TEXT("Opacity"), TEXT("OpacityMask"), TEXT("Normal"), TEXT("Occlusion")}) }, {EShadingModel::UNLIT, FGLTFMaterialInformation( TEXT("/InterchangeAssets/gltf/MaterialBodies/MF_Unlit_Body.MF_Unlit_Body"), TEXT("/InterchangeAssets/gltf/M_Unlit.M_Unlit"), TArray<FString>{ TEXT("UnlitColor"), TEXT("Opacity"), TEXT("OpacityMask")}) }, {EShadingModel::CLEARCOAT, FGLTFMaterialInformation( TEXT("/InterchangeAssets/gltf/MaterialBodies/MF_ClearCoat_Body.MF_ClearCoat_Body"), TEXT("/InterchangeAssets/gltf/M_ClearCoat.M_ClearCoat"), TArray<FString>{ TEXT("ClearCoatNormal"), TEXT("BaseColor"), TEXT("Metallic"), TEXT("Specular"), TEXT("Roughness"), TEXT("EmissiveColor"), TEXT("Opacity"), TEXT("OpacityMask"),` (scope `UE::Interchange::GLTFMaterials`)
- L293 _function_ `inline TArray<FString> GetRequiredMaterialFunctionPaths()` (scope `UE::Interchange::GLTFMaterials`)
- L303 _function_ `inline TMap<FString, EShadingModel> GetMaterialFunctionPathsToShadingModels()` (scope `UE::Interchange::GLTFMaterials`)
- L313 _function_ `inline TMap<FString, EShadingModel> GetMaterialPathsToShadingModels()` (scope `UE::Interchange::GLTFMaterials`)
- L323 _prototype_ `void HandleGltfMaterial(UInterchangeBaseNodeContainer& NodeContainer, const GLTF::FMaterial& GltfMaterial, const TArray<GLTF::FTexture>& Textures, UInterchangeShaderGraphNode* ShaderGraphNode);` (scope `UE::Interchange::GLTFMaterials`)
- L325 _prototype_ `bool AreRequiredPackagesLoaded();` (scope `UE::Interchange::GLTFMaterials`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Gltf/InterchangeGltfTranslator.h` (Public)


#### class `UInterchangeGLTFTranslator`  
`class UInterchangeGLTFTranslator : public UInterchangeTranslatorBase , public IInterchangeMeshPayloadInterface , public IInterchangeTexturePayloadInterface , public IInterchangeAnimationPayloadInterface , public IInterchangeVariantSetPayloadInterface , public IInterchangeTextureLightProfilePayloadInterface`  
_L26-97_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeMeshPayloadInterface,IInterchangeTexturePayloadInterface,IInterchangeAnimationPayloadInterface,IInterchangeVariantSetPayloadInterface,IInterchangeTextureLightProfilePayloadInterface`
- desc: glTF translator class support import of texture, material, static mesh, skeletal mesh,
- L36 _public prototype_ `UInterchangeGLTFTranslator();`
- L39 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;` — Begin UInterchangeTranslatorBase API
- L40 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L41 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L42 _public prototype_ `virtual bool Translate( UInterchangeBaseNodeContainer& BaseNodeContainer ) const override;`
- L47 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform) const override` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")` — IInterchangeStaticMeshPayloadInterface Begin
- L55 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const;`
- L61 _public prototype_ `virtual TOptional< UE::Interchange::FImportImage > GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;`
- L66 _public prototype_ `TOptional<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const UE::Interchange::FAnimationPayloadQuery& PayloadQuery) const;` — IInterchangeAnimationPayloadInterface Begin
- L67 _public prototype_ `virtual TArray<UE::Interchange::FAnimationPayloadData> GetAnimationPayloadData(const TArray<UE::Interchange::FAnimationPayloadQuery>& PayloadQueries) const override;`
- L71 _public prototype_ `virtual TOptional<UE::Interchange::FVariantSetPayloadData> GetVariantSetPayloadData(const FString& PayloadKey) const override;` — IInterchangeVariantSetPayloadInterface Begin
- L75 _public prototype_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — IInterchangeTextureLightProfilePayloadInterface Begin
- L79 _protected typedef_ `using FNodeUidMap = TMap<const GLTF::FNode*, FString>;`
- L81 _protected prototype_ `void HandleGltfSkeletons( UInterchangeBaseNodeContainer& NodeContainer, const FString& SceneNodeUid, const TArray<int32>& SkinnedMeshNodes, TSet<int>& UnusedMeshIndices ) const;`
- L82 _protected prototype_ `void HandleGltfNode( UInterchangeBaseNodeContainer& NodeContainer, const GLTF::FNode& GltfNode, const FString& ParentNodeUid, const int32 NodeIndex, bool &bHasVariants, TArray<int32>& SkinnedMeshNodes, TSet<int>& UnusedMeshIndices, const TMap<int32, FTransform>& T0Transforms, const FString& SceneNodeUid) const;`
- L84 _protected prototype_ `void HandleGltfVariants(UInterchangeBaseNodeContainer& NodeContainer, const FString& FileName) const;`
- L85 _protected prototype_ `UInterchangeMeshNode* HandleGltfMesh(UInterchangeBaseNodeContainer& NodeContainer, const GLTF::FMesh& GltfMesh, int MeshIndex, TSet<int>& UnusedMeshIndices, const FString& SkeletalName = "" , const FString& SkeletalId = "") const;`
- L88 _protected prototype_ `bool GetVariantSetPayloadData(UE::Interchange::FVariantSetPayloadData& PayloadData) const;`
- L91 _private prototype_ `void SetTextureSRGB(UInterchangeBaseNodeContainer& NodeContainer, const GLTF::FTextureMap& TextureMap, bool bSRGB) const;`
- L93 _private member_ `GLTF::FAsset GltfAsset;`
- L94 _private member_ `mutable FNodeUidMap NodeUidMap;`
- L96 _private member_ `bool bRenderSettingsClearCoatEnableSecondNormal = false;`

### `Plugins/Interchange/Runtime/Source/Import/Public/Groom/InterchangeGroomBindingFactory.h` (Public)


#### class `UInterchangeGroomBindingFactory`  
`class UInterchangeGroomBindingFactory : public UInterchangeFactoryBase`  
_L12-23_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L18 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L19 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L20 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Groom/InterchangeGroomCacheFactory.h` (Public)


#### class `UInterchangeGroomCacheFactory`  
`class UInterchangeGroomCacheFactory : public UInterchangeFactoryBase`  
_L13-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L19 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L20 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L21 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L22 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L23 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L24 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L25 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L26 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L27 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Groom/InterchangeGroomFactory.h` (Public)


#### class `UInterchangeGroomFactory`  
`class UInterchangeGroomFactory : public UInterchangeFactoryBase`  
_L14-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L20 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L21 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L22 _public prototype_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks) override;`
- L23 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L24 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L25 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L26 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L27 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L28 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L29 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L33 _private member_ `TOptional<UE::Interchange::FGroomPayloadData> GroomPayload;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Groom/InterchangeGroomPayloadData.h` (Public)


#### struct `UE::Interchange::FGroomPayloadData`  
`struct FGroomPayloadData`  
_L9-12_
- L11 _public member_ `FHairDescription HairDescription;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Groom/InterchangeGroomPayloadInterface.h` (Public)


#### class `UInterchangeGroomPayloadInterface`  
`class UInterchangeGroomPayloadInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeGroomPayloadInterface`  
`class IInterchangeGroomPayloadInterface`  
_L21-30_
- desc: Payload interface for groom data
- L26 _public function_ `virtual TOptional<UE::Interchange::FGroomPayloadData> GetGroomPayloadData(const FInterchangeGroomPayloadKey& PayloadKey) const`

### `Plugins/Interchange/Runtime/Source/Import/Public/InterchangeAssetUserData.h` (Public)


#### class `UInterchangeAssetUserData`  
`class UInterchangeAssetUserData : public UAssetUserData`  
_L12-19_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (ScriptName = "InterchangeUserData", DisplayName = "Interchange User Data"))`
- inherits: `UAssetUserData`
- desc: Asset user data that can be used with Interchange on Actors and other objects
- L18 _public member_ `TMap<FString, FString> MetaData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Interchange User Data", meta = (ScriptName = "Metadata", DisplayName = "Metadata"))`

#### class `UInterchangeLevelAssetUserData`  
`class UInterchangeLevelAssetUserData : public UAssetUserData`  
_L23-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (ScriptName = "InterchangeLevelUserData", DisplayName = "Interchange Level User Data"))`
- inherits: `UAssetUserData`
- desc: Asset user data that can be used with Interchange on Levels. This will reside in the world settings of the ULevel
- L29 _public member_ `TArray<FString> SceneImportPaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Interchange User Data", meta = (ScriptName = "SceneImportPaths", DisplayName = "Scene Import Paths"))`

### `Plugins/Interchange/Runtime/Source/Import/Public/InterchangeGenericPayloadData.h` (Public)


#### class `UInterchangeGenericPayloadData`  
`class UInterchangeGenericPayloadData : public UObject`  
_L14-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for generic payload data. This is meant to be derived, in order to provide custom payload data without having to specialize the translators to implement another payload interface. See UInterchangeGenericPayloadInterface.

### `Plugins/Interchange/Runtime/Source/Import/Public/InterchangeGenericPayloadInterface.h` (Public)


#### class `UInterchangeGenericPayloadInterface`  
`class UInterchangeGenericPayloadInterface : public UInterface`  
_L25-28_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Payload interface implemented by translators that want to allow user code to provide different payload types to Interchange. The USD translator uses this mechanism: A user plugin may implement a schema handler that can provide custom payload data, and also register a factory that can handle it. Without a mechanism such as this however, there would be no way of getting that payload data from the schema handler to the factory, as the translator would need to be also modified with a custom payload interface. Instead, the USD translator already implements this interface, and the schema handler can provide a payload data class that derives UInterchangeGenericPayloadData, while the factory can try casting its received UInterchangeGenericPayloadData to the derived type.

#### class `IInterchangeGenericPayloadInterface`  
`class IInterchangeGenericPayloadInterface`  
_L30-39_
- L35 _public function_ `virtual TObjectPtr<UInterchangeGenericPayloadData> GetGenericPayloadData(const FString& PayloadKey) const`

### `Plugins/Interchange/Runtime/Source/Import/Public/InterchangeImportModule.h` (Public)


#### class `IInterchangeImportModule`  
`class IInterchangeImportModule : public IModuleInterface`  
_L12-51_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IInterchangeImportModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L43 _public function_ `virtual bool IsSubstrateEnabled() const` — Checks to see if Substrate support is enabled both in the Project Settings and for Interchange @return True if Substrate is enabled
- L50 _public function_ `virtual bool IsSubstrateAdaptiveGBufferEnabled() const` — Checks to see if Substrate Adaptive GBuffer is enabled in the Project Settings @return True if Adaptive GBuffer is enabled

### `Plugins/Interchange/Runtime/Source/Import/Public/InterchangeSkeletonHelper.h` (Public)


#### struct `UE::Interchange::Private::FJointInfo`  
`struct FJointInfo`  
_L22-27_
- L24 _public member_ `FString Name;`
- L25 _public member_ `int32 ParentIndex;` — 0 if this is the root bone.
- L26 _public member_ `FTransform LocalTransform;` — local transform

#### struct `UE::Interchange::Private::FSkeletonHelper`  
`struct FSkeletonHelper`  
_L29-77_
- L32 _public prototype_ `static bool IsValidSocket(const UInterchangeBaseNodeContainer* NodeContainer, const UInterchangeSceneNode* Node);`
- L34 _public prototype_ `static bool ProcessImportMeshSkeleton(TObjectPtr<UInterchangeResultsContainer> Results , const USkeleton* SkeletonAsset , FReferenceSkeleton& RefSkeleton , const UInterchangeBaseNodeContainer* NodeContainer , const FString& RootJointNodeId , TArray<SkeletalMeshImportData::FBone>& RefBonesBinary , const bool bUseTimeZeroAsBindPose , bool& bOutDiffPose , bool bImportSockets);`
- L44 _public prototype_ `static bool IsCompatibleSkeleton(const USkeleton* Skeleton , const FString RootJoinUid , const UInterchangeBaseNodeContainer* BaseNodeContainer , bool bConvertStaticToSkeletalActive , bool bCheckForIdenticalSkeleton , bool bImportSockets);`
- L50 _public prototype_ `static void RecursiveAddSkeletonMetaDataValues(UInterchangeBaseNodeContainer* NodeContainer, UInterchangeBaseNode* DestinationNode, const FString& JointUid);`
- L52 _public prototype_ `static void RecursiveBoneHasBindPose(const UInterchangeBaseNodeContainer* NodeContainer, const FString& JointNodeId, bool& bHasBoneWithoutBindPose);`
- L54 _public prototype_ `static void RecursiveAddBones(const UInterchangeBaseNodeContainer* NodeContainer , const FString& JointNodeId , TArray <FJointInfo>& JointInfos , int32 ParentIndex , TArray<SkeletalMeshImportData::FBone>& RefBonesBinary , TSet<FName>& UsedBoneNames , const bool bUseTimeZeroAsBindPose , bool& bOutDiffPose , TArray<FString>& OutBoneNotBindNames , bool bImportSockets);`
- L66 _private prototype_ `static FName SkeletalLodGetBoneName(const TArray<FMeshBoneInfo>& SkeletalLodRawInfos, int32 BoneIndex);`
- L67 _private prototype_ `static int32 SkeletalLodFindBoneIndex(const TArray<FMeshBoneInfo>& SkeletalLodRawInfos, FName BoneName);`
- L68 _private prototype_ `static int32 SkeletalLodGetParentIndex(const TArray<FMeshBoneInfo>& SkeletalLodRawInfos, int32 BoneIndex);`
- L69 _private prototype_ `static bool DoesParentChainMatch(int32 StartBoneIndex, const FReferenceSkeleton& SkeletonRef, const TArray<FMeshBoneInfo>& SkeletalLodRawInfos);`
- L71 _private prototype_ `static void RecursiveBuildSkeletalSkeleton(const FString JoinToAddUid , const int32 ParentIndex , const UInterchangeBaseNodeContainer* BaseNodeContainer , TArray<FMeshBoneInfo>& SkeletalLodRawInfos , bool bConvertStaticToSkeletalActive , bool bImportSockets);`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Interchange` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Import/Public/InterchangeTranslatorHelper.h` (Public)


#### struct `UE::Interchange::Private::FScopedTranslator`  
`struct FScopedTranslator`  
_L15-37_
- L18 _public prototype_ `FScopedTranslator(const FString& PayLoadKey, UInterchangeResultsContainer* Results, TObjectPtr<UInterchangeAnalyticsHandlerBase> AnalyticsHandler);`
- L19 _public prototype_ `~FScopedTranslator();`
- L22 _public function_ `template <class T> const T* GetPayLoadInterface() const`
- L33 _private prototype_ `bool IsValid() const;`
- L35 _private member_ `TObjectPtr<UInterchangeTranslatorBase> SourceTranslator = nullptr;`
- L36 _private member_ `TObjectPtr<UInterchangeSourceData> PayloadSourceData = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Material/InterchangeMaterialFactory.h` (Public)


#### class `UE::Interchange::Materials::HashUtils::FInterchangeMaterialInstanceOverridesAPI`  
`class FInterchangeMaterialInstanceOverridesAPI`  
_L25-63_
- L31 _public prototype_ `static FString MakeOverrideParameterName(UE::Interchange::EAttributeTypes AttributeType, int32 Hash, bool Prefix = true);` — Generates Attribute Key String from the AttributeType and Hash
- L36 _public prototype_ `static FString MakeOverrideParameterName(const FString& DisplayLabel);` — Generates Attribute Key String from the DisplayLable
- L41 _public prototype_ `static FString MakeExpressionNameString();` — Generates Attribute Key for Expression Name
- L46 _public prototype_ `static bool GetOverrideParameterName(const UE::Interchange::FAttributeKey& AttributeKey, FString& OverrideParameterName);` — Retrieves the Parameter Name from AttributeKey
- L51 _public prototype_ `static bool HasMaterialExpressionNameOverride(const UInterchangeBaseNode* BaseNode);` — Checks if the Node has a MaterialExpressionName override
- L56 _public prototype_ `static void GatherLeafInputs(const UInterchangeBaseNode* BaseNode, TArray<UE::Interchange::FAttributeKey>& OutLeafInputAttributeKeys);` — Retrieves the Attribute Keys of the Leaf Inputs.
- L59 _private member_ `static const TCHAR* ExpressionNameAttributeKey;`
- L60 _private member_ `static const TCHAR* OverrideParameterPrefix;`
- L61 _private member_ `static const TCHAR* OverrideParameterSeparator;`
- L62 _private member_ `static const TCHAR* OverrideHashSeparator;`

#### class `UInterchangeMaterialFactory`  
`class UInterchangeMaterialFactory : public UInterchangeFactoryBase`  
_L67-98_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L75 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L76 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L77 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L78 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L79 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L80 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L81 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L82 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L83 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L84 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L90 _private prototype_ `void SetupMaterial(UMaterial* Material, const FImportAssetObjectParams& Arguments, const UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode);`
- L93 _private prototype_ `void SetupMaterialInstance(UMaterialInstance& MaterialInstance, const UInterchangeBaseNodeContainer& NodeContainer, const UInterchangeMaterialInstanceFactoryNode& FactoryNode, bool bResetInstance);`
- L94 _private prototype_ `void SetupReimportedMaterialInstance(UMaterialInstance& MaterialInstance, const UInterchangeBaseNodeContainer& NodeContainer, const UInterchangeMaterialInstanceFactoryNode& FactoryNode, const UInterchangeMaterialInstanceFactoryNode& PreviousFactoryNode);`
- L97 _private member_ `bool bSkipImport = false;` — If we import without a pure material translator, we should not override an existing material and we must skip the import. See the implementation of BeginImportAssetObject_GameThread function.

#### class `UInterchangeMaterialFunctionFactory`  
`class UInterchangeMaterialFunctionFactory : public UInterchangeFactoryBase`  
_L101-123_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L109 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L110 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L111 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L112 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L113 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L120 _private prototype_ `void SetupMaterial(class UMaterialFunction* Material, const FImportAssetObjectParams& Arguments, const class UInterchangeMaterialFunctionFactoryNode* MaterialFactoryNode);`
- L122 _private member_ `bool bSkipImport = false;`

#### class `FInterchangeImportMaterialAsyncHelper`  
`class FInterchangeImportMaterialAsyncHelper`  
_L130-151_
- desc: This class intends to avoid a race condition when importing several material functions at once, for example when importing the MaterialX file standard_surface_chess_set Only one instance of a material function can update it
- L132 _private prototype_ `FInterchangeImportMaterialAsyncHelper() = default;`
- L136 _public prototype_ `FInterchangeImportMaterialAsyncHelper(const FInterchangeImportMaterialAsyncHelper&) = delete;`
- L137 _public prototype_ `FInterchangeImportMaterialAsyncHelper& operator=(const FInterchangeImportMaterialAsyncHelper&) = delete;`
- L139 _public prototype_ `static FInterchangeImportMaterialAsyncHelper& GetInstance();`
- L142 _public prototype_ `void UpdateFromFunctionResource(UMaterialExpressionMaterialFunctionCall* MaterialFunctionCall);`
- L144 _public prototype_ `void UpdateFromFunctionResource(UMaterialFunctionInterface* MaterialFunction);`
- L149 _private member_ `FCriticalSection UpdatedMaterialFunctionCallsLock;`
- L150 _private member_ `FCriticalSection UpdatedMaterialFunctionsLock;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Interchange` (scope `UE`)
- L23 _namespace_ `namespace Materials` (scope `UE::Interchange`)
- L23 _namespace_ `namespace HashUtils` (scope `UE::Interchange::Materials`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Material/InterchangeMaterialNodesHelper.h` (Public)


#### struct `UE::Interchange::Materials::Private::FMaterialNodesHelper`  
`struct FMaterialNodesHelper`  
_L11-16_
- L14 _public prototype_ `static bool SetupScalarParameter(UInterchangeBaseNodeContainer& BaseNodeContainer, UInterchangeShaderGraphNode* ShaderGraphNode, const FString& InputName, const float& AttributeValue);`
- L15 _public prototype_ `static bool SetupVectorParameter(UInterchangeBaseNodeContainer& BaseNodeContainer, UInterchangeShaderGraphNode* ShaderGraphNode, const FString& InputName, const FLinearColor& AttributeValue);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Interchange` (scope `UE`)
- L9 _namespace_ `namespace Materials` (scope `UE::Interchange`)
- L9 _namespace_ `namespace Private` (scope `UE::Interchange::Materials`)

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/InterchangeMaterialXTranslator.h` (Public)


#### class `UInterchangeMaterialXTranslator`  
`class UInterchangeMaterialXTranslator : public UInterchangeTranslatorBase , public IInterchangeTexturePayloadInterface , public IInterchangeBlockedTexturePayloadInterface`  
_L17-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface,IInterchangeBlockedTexturePayloadInterface`
- L28 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;`
- L30 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L32 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L40 _public prototype_ `virtual bool Translate( UInterchangeBaseNodeContainer& BaseNodeContainer ) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The container where to add the translated Interchange nodes. @return true if the translator can translate the source data, false otherwise.
- L44 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;`
- L45 _public prototype_ `static TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeResultsContainer* InResults, TObjectPtr<UInterchangeAnalyticsHandlerBase> InAnalyticsHandler);`
- L48 _public prototype_ `virtual TOptional<UE::Interchange::FImportBlockedImage> GetBlockedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;`
- L49 _public prototype_ `static TOptional<UE::Interchange::FImportBlockedImage> GetBlockedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath, UInterchangeResultsContainer* InResults, TObjectPtr<UInterchangeAnalyticsHandlerBase> InAnalyticsHandler);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/MaterialExpressions/MaterialExpressionSwizzle.h` (Public)


#### class `UMaterialExpressionMaterialXSwizzle`  
`UMaterialExpressionMaterialXSwizzle : public UMaterialExpression`  
_L11-28_
- reflection: `UCLASS()`
- reflection: `UE_DEPRECATED(5.7, "UMaterialExpressionMaterialXSwizzle is now deprecated since <swizzle> node has been removed from MaterialX 1.39.3. Please use UMaterialExpressionComponent instead.")`
- inherits: `UMaterialExpression`
- L16 _private member_ `FExpressionInput Input;` — `UPROPERTY()`
- L19 _private member_ `FString Channels;` — `UPROPERTY(EditAnywhere, Category = Swizzle, Meta = (ShowAsInputPin = "Advanced"))`
- L23 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L24 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L25 _private prototype_ `void GetExpressionToolTip(TArray<FString>& OutToolTip) override;`

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/MaterialExpressions/MaterialExpressionTextureSampleParameterBlur.h` (Public)


#### enum `EMaterialXTextureSampleBlurFilter`  
`enum class EMaterialXTextureSampleBlurFilter : uint8`  
_L8-12_
- reflection: `UENUM()`
- L10 _public enumerator_ `Box`
- L11 _public enumerator_ `Gaussian`

#### enum `EMAterialXTextureSampleBlurKernel`  
`enum class EMAterialXTextureSampleBlurKernel`  
_L15-21_
- reflection: `UENUM()`
- L17 _public enumerator_ `Kernel1 UMETA(DisplayName = "1x1", ToolTip="No Blur")`
- L18 _public enumerator_ `Kernel3 UMETA(DisplayName = "3x3")`
- L19 _public enumerator_ `Kernel5 UMETA(DisplayName = "5x5")`
- L20 _public enumerator_ `Kernel7 UMETA(DisplayName = "7x7")`

#### class `UMaterialExpressionMaterialXTextureSampleParameterBlur`  
`class UMaterialExpressionMaterialXTextureSampleParameterBlur: public UMaterialExpressionTextureSampleParameter2D`  
_L24-56_
- reflection: `UCLASS(MinimalAPI, collapsecategories, hidecategories = Object, meta = (Private))`
- inherits: `UMaterialExpressionTextureSampleParameter2D`
- L30 _private member_ `EMAterialXTextureSampleBlurKernel KernelSize = EMAterialXTextureSampleBlurKernel::Kernel1;` — `UPROPERTY(EditAnywhere, Category = Filtering, Meta = (ShowAsInputPin = "Advanced"))` — The size of the blur kernel, relative to 0-1 UV space.
- L34 _private member_ `float FilterSize = 1.f;` — `UPROPERTY(EditAnywhere, Category = Filtering, Meta = (ShowAsInputPin = "Advanced"))` — Size of the filter when we sample a texture coordinate
- L38 _private member_ `float FilterOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = Filtering, Meta = (ShowAsInputPin = "Advanced"))` — Offset of the filter when we sample a texture coordinate
- L42 _private member_ `EMaterialXTextureSampleBlurFilter Filter = EMaterialXTextureSampleBlurFilter::Gaussian;` — `UPROPERTY(EditAnywhere, Category = Filtering, Meta = (ShowAsInputPin = "Advanced"))` — Filter to use when we blur a Texture: Gaussian or Box Linear filter
- L46 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L47 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L54 _private prototype_ `const float* GetKernel(int32& FilterWidth) const;`

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/MaterialXUtils/MaterialXBase.h` (Public)


#### class `FMaterialXBase`  
`class FMaterialXBase : public TSharedFromThis<FMaterialXBase>`  
_L42-182_
- inherits: `TSharedFromThis<FMaterialXBase>`
- L46 _protected prototype_ `FMaterialXBase(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L52 _public prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr Node) = 0;`
- L54 _public prototype_ `virtual ~FMaterialXBase() = default;`
- L61 _public prototype_ `static void UpdateDocumentRecursively(MaterialX::GraphElementPtr Graph);` — Update a MaterialX Document recursively by either initializing nodes (like <tiledimage>) or updating some nodes (e.g: math nodes with neutral elements) @param Graph - The graph to update and all of its sub graphs
- L67 _public prototype_ `void SetNodeDefinition(const char* NodeDefinition);` — Set the node definition of a shader, useful when a shader has multiple definition per types and when we know the type only at the top level during a surfacematerial for example and not a construction-time. Make sure that the pointer don't cease to exist, no allocation is performed here, use the definition in MaterialXDefinitions
- L70 _public prototype_ `void SetTranslator(const UInterchangeTranslatorBase* InTranslator);` — Set the translator, only used for logging messages
- L72 _public prototype_ `void CollectAnalytics(TArray<FAnalyticsEventAttribute>& OutAnalyticsAttributes);`
- L80 _protected typedef_ `using FInputToCopy = TPair<const char*, MaterialX::InputPtr>;` — @param const char * - New name of the Input to copy @param MaterialX::InputPtr - Input to copy
- L86 _protected typedef_ `using FAttributeValue = TPair<const char*, const char*>;` — @param const char * - Attribute @param const char * - Value
- L91 _protected typedef_ `using FAttributeValueArray = TArray<FAttributeValue>;` — @param TArray<FAttributeValueType> - Array of attribute/value
- L96 _protected typedef_ `using FInputToCreate = TPair<const char*, FAttributeValueArray>;` — @param TArray<FAttributeValueType> - Array of attribute/value
- L105 _protected prototype_ `static void AddTexCoordToTiledImageNodes(MaterialX::ElementPtr Graph);` — Add a texcoord input to the tiledimage nodes if the input is missing, and connect it to a texcoord node in the nodegraph This function should be called before the subgraphs substitution to avoid missing UVs input on a texture See for example standard_surface_brick_procedural where the tiledimage nodes have no texcoord input @param Node - The nodegraph to retrieve the different tiledimage nodes
- L114 _protected prototype_ `static void ConvertNeutralNodesToDot(MaterialX::ElementPtr NodeGraph);` — Convert math nodes (add, sub, div, mul) that have a neutral input, to the MaterialX <dot> node which is simply the identity or a noop This allows us to optimize the final shader by avoiding unnecessary operation on a material (for example a*1 = a) This function should be called after the subgraphs substitution in order to search for all the nodes even in the subgraphs @param NodeGraph - The node graph to retrieve the different math nodes
- L117 _protected prototype_ `static void ConvertGeomPropValueNodesToTexCoord(MaterialX::GraphElementPtr Graph);` — Convert <geompropvalue> nodes that are vector2 with the exact input geomprop named "st" as <texcoord> nodes
- L131 _protected prototype_ `static MaterialX::NodePtr CreateNode(MaterialX::ElementPtr NodeGraph, const char* NodeName, const char* Category, const TArray<FInputToCopy>& InputsToCopy, const TArray<FInputToCreate>& InputsToCreate);` — Helper function that create a MaterialX node, useful to insert a node between 2 nodes especially when an operation cannot be done in one pass If the node already exists in the graph, this one is returned @param NodeGraph - The node graph to insert the new node into @param NodeName - The name of the node @param Category - The category of the node to create @param InputsToCopy - The inputs from another node/nodegraph to copy in the new node, can be empty @param InputsToCreate - The inputs to create from scratch and insert in the new node, can be empty @return The newly created node
- L142 _protected prototype_ `static FString GetColorSpace(MaterialX::ElementPtr Element);` — Return the innermost color space of an element in the current scope, if it has none, it will take the one from its parents @param Element - the Element to retrieve the color space from (can be anything, an input, a node, a nodegraph, etc.) @return a color space or an empty string
- L155 _protected prototype_ `MaterialX::InputPtr GetInput(MaterialX::NodePtr Node, const char* InputName);` — Retrieve the input from a surfaceshader node, or take the default input from the library, this function should only be called after testing the MaterialX libraries have been successfully imported, meaning the node definition of the surfaceshader should always be valid @param StandardSurface - the <standard_surface> node @param InputName - the input name to retrieve @return the input from the given name
- L164 _protected prototype_ `FLinearColor GetLinearColor(MaterialX::InputPtr Input) const;` — Helper function that returns a linear color after a color space conversion, the function makes no assumption on the input, and it should have a value of Color3-4 type @param Input - The input that has a Color3-4 value in it @return The linear color after color space conversion
- L168 _protected member_ `UInterchangeBaseNodeContainer& NodeContainer;`
- L171 _protected member_ `const UInterchangeTranslatorBase* Translator;` — Used for logging from either MaterialX or USD translator
- L174 _protected member_ `TArray<FAnalyticsEventAttribute> AnalyticsAttributes;` — To avoid locking Analytics helper in the translator for each add, at the end of the translat,  every attribute will be concatenated
- L177 _protected member_ `const char* NodeDefinition;` — It's up to the derive class to initialize it with the proper node definition
- L179 _protected member_ `bool bIsSubstrateEnabled;`
- L181 _protected member_ `bool bIsSubstrateAdaptiveGBufferEnabled;`

#### enum `FMaterialXBase::EMaterialXLog`  
`enum class EMaterialXLog`  
_L50-50_
- L50 _public enumerator_ `enum class EMaterialXLog{Error, Warning}; virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr Node) = 0; virtual ~FMaterialXBase() = default; /** * Update a MaterialX Document recursively by either initializing nodes (like <tiledimage>) or updating some nodes (e.g: math nodes with neutral elements)`
- L50 _public enumerator_ `enum class EMaterialXLog{Error, Warning}; virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr Node) = 0; virtual ~FMaterialXBase() = default; /** * Update a MaterialX Document recursively by either initializing nodes (like <tiledimage>) or updating some nodes (e.g: math nodes with neutral elements)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)
- L15 _namespace_ `namespace MaterialX` (scope `UE::Interchange`)
- L15 _namespace_ `namespace Private` (scope `UE::Interchange::MaterialX`)
- L17 _function_ `static inline FText FormatFText(const FText& Text)` (scope `UE::Interchange::MaterialX::Private`)
- L23 _function_ `template<typename... Args> FText FormatFText(const FText& Text, Args&&... args)` (scope `UE::Interchange::MaterialX::Private`)
- L29 _macro_ `#define MTLX_LOG(Key, Format, ...) \`

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/MaterialXUtils/MaterialXLightShaderAbstract.h` (Public)


#### class `FMaterialXLightShaderAbstract`  
`class FMaterialXLightShaderAbstract : public FMaterialXBase`  
_L12-26_
- inherits: `FMaterialXBase`
- L16 _protected prototype_ `FMaterialXLightShaderAbstract(UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L18 _protected prototype_ `virtual void PreTranslate();`
- L20 _protected prototype_ `virtual void PostTranslate();`
- L22 _protected member_ `FTransform Transform;`
- L23 _protected member_ `MaterialX::NodePtr LightShaderNode;`
- L24 _protected member_ `UInterchangeSceneNode* SceneNode;`
- L25 _protected member_ `UInterchangeBaseLightNode* LightNode;`

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/MaterialXUtils/MaterialXManager.h` (Public)


#### class `FMaterialXManager`  
`class FMaterialXManager`  
_L30-178_
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FMaterialXBase>, FOnGetMaterialXInstance, UInterchangeBaseNodeContainer&);`
- L36 _public prototype_ `static FMaterialXManager& GetInstance();`
- L46 _public prototype_ `bool Translate(const FString& Filename, UInterchangeBaseNodeContainer& BaseNodeContainer, const UInterchangeTranslatorBase* Translator = nullptr);` — Translate a MaterialX file @param Filename - Name of the MaterialX file to translate @param BaseNodeContainer - Node Container @param Translator - The Translator if this function is called from a Translaotr, used to log errors, otherwise the errors are logged in the default output @return true if the file has been successfully translated
- L49 _public prototype_ `bool Translate(MaterialX::DocumentPtr Document, UInterchangeBaseNodeContainer& BaseNodeContainer, const UInterchangeTranslatorBase* Translator = nullptr);` — Translate a MaterialX Document
- L52 _public prototype_ `const FString* FindMatchingInput(const FString& CategoryKey, const FString& InputKey, const FString& NodeGroup = {}, const FString& Type = {}) const;` — Find a corresponding Material Expression Input given a (Category [NodeGroup] [Type], Input) pair
- L55 _public prototype_ `const FString* FindMaterialExpressionInput(const FString& InputKey) const;` — Find a stored Material Expression Input
- L58 _public prototype_ `const FString* FindMatchingMaterialExpression(const FString& CategoryKey, const FString& NodeGroup = {}, const FString& Type= {}) const;` — Find a matching Material Expression given a MaterialX category [nodegroup] [type]
- L61 _public prototype_ `bool FindMatchingMaterialFunction(const FString& CategoryKey, const FString*& MaterialFunctionPath, uint8& EnumType, uint8& EnumValue) const;` — Find a matching Material Function given a MaterialX category
- L63 _public prototype_ `TSharedPtr<FMaterialXBase> GetShaderTranslator(const FString& CategoryShader, UInterchangeBaseNodeContainer& NodeContainer);`
- L65 _public prototype_ `void RegisterMaterialXInstance(const FString& CategoryShader, FOnGetMaterialXInstance MaterialXInstanceDelegate);`
- L67 _public prototype_ `bool IsSubstrateEnabled() const;`
- L69 _public prototype_ `bool IsSubstrateAdaptiveGBufferEnabled() const;`
- L72 _public prototype_ `bool FilterNodeGraph(MaterialX::NodePtr Node) const;` — Return true if the node category should be filtered out during the flattening of the subgraphs
- L75 _public prototype_ `void RemoveInputs(MaterialX::NodePtr Node) const;` — Remove the inputs of a node with no match in UE Material Expressions
- L78 _public prototype_ `FString FindOrAddTextureNodeUid(const FString& TexturePath);` — Find or Add a Texture Node UID, if not found it creates a hash of the path
- L85 _public prototype_ `void AddInputsFromNodeDef(MaterialX::NodePtr Node) const;` — Add all the inputs from the nodedef in case the node doesn't have them all (we don't have a 1:1 match on the default values otherwise) For exemple 'min' defaults to (0, 0) whereas UE to (0, 1) We don't want to add every node, since we don't a have perfect match for each input
- L87 _public prototype_ `FMaterialXManager(const FMaterialXManager&) = delete;`
- L88 _public prototype_ `FMaterialXManager& operator=(const FMaterialXManager&) = delete;`
- L90 _public member_ `static const TCHAR TexturePayloadSeparator;`
- L98 _private typedef_ `using FMaterialXMaterialFunction = TVariant<FString, EInterchangeMaterialXShaders, EInterchangeMaterialXBSDF, EInterchangeMaterialXEDF, EInterchangeMaterialXVDF>;` — FString: Material Function path Enums: data-driven BSDF nodes
- L119 _private function_ `friend inline uint32 GetTypeHash(const FKeyExpression& Key)`
- L129 _private prototype_ `FMaterialXManager();`
- L132 _private prototype_ `const TCHAR* ExpressionInput(const TCHAR* Input);` — Helper function that returns the input as a string by also adding it in the MaterialExpressionInputs container
- L136 _private prototype_ `const TCHAR* MaterialFunctionPackage(const TCHAR* Input);` — Helper function that returns the material function package path as a string by also adding it in the MaterialFunctionsToLoad container, in order to centralize material functions that need to be loaded in the Game Thread by AreMaterialFunctionPackagesLoaded function
- L139 _private member_ `TSet<FString> MaterialExpressionInputs;` — The different inputs of material expression that we may encounter, the MaterialX Document is modified consequently regarding those
- L142 _private member_ `TSet<FString> MaterialFunctionsToLoad;` — List of material functions packages to load in the Game Thread.
- L145 _private member_ `TMap<TPair<FKeyExpression, FString>, FString> MatchingInputNames;` — Given a MaterialX node (category (optionally a nodegroup) - input), return the UE/Interchange input name.
- L148 _private member_ `TMap<FKeyExpression, FString> MatchingMaterialExpressions;` — Given a MaterialX node category, optionally with a node group, return the UE material expression class name
- L151 _private member_ `TMap<FString, FOnGetMaterialXInstance> MaterialXContainerDelegates;` — Container of a MaterialX document, to translate the different nodes based on their category
- L154 _private member_ `TMap<FString, FMaterialXMaterialFunction> MatchingMaterialFunctions;` — Given a MaterialX node category, return the UE material function, used for BSDF nodes
- L162 _private member_ `TMap<FString, FString> TextureNodeUids;` — Mapping between texture fullpath and their UID used to allow same name textures with different path, but avoid duplicating textures across different materials in the same file (for example the chess_set) The map is reset after each translate
- L165 _private member_ `std::unordered_set<std::string> CategoriesToSkip;` — Categories of nodes to skip during the phase of flattening the subgraphs. Basically if a node has a nodegraph it will be processed as is instead of its nodegraph
- L168 _private member_ `std::unordered_set<std::string> NodeDefsCategories;` — Categories of nodes to add the default inputs from the nodedefs if they are not present on the node
- L171 _private member_ `std::unordered_map<std::string, std::vector<std::string>> NodeInputsToRemove;` — Inputs of the nodes category to remove because there's no equivalent in UE Material Expression, to avoid creating a floating Scalar/Vector parameter
- L173 _private member_ `bool bIsSubstrateEnabled;`
- L175 _private member_ `bool bIsSubstrateAdaptiveGBufferEnabled;`

#### struct `FMaterialXManager::FKeyExpression`  
`struct FKeyExpression`  
_L100-127_
- L103 _public function_ `template<typename CategoryString> FKeyExpression(CategoryString&& Category) : Category`
- L108 _public function_ `template<typename CategoryString, typename NodeGroupString, typename TypeString> FKeyExpression(CategoryString&& Category, NodeGroupString&& NodeGroup, TypeString&& Type) : Category`
- L114 _public function_ `[[nodiscard]] inline bool operator==(const FKeyExpression& Rhs) const`
- L124 _public member_ `FString Category;`
- L125 _public member_ `FString NodeGroup;` — node group is optional, some nodes in MaterialX have different material expressions in UE depending on the nodegroup
- L126 _public member_ `FString Type;` — Type is optional, some nodes in MaterialX have different material expressions in UE depending on the type

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Interchange` (scope `UE`)
- L22 _namespace_ `namespace MaterialX` (scope `UE::Interchange`)
- L25 _prototype_ `bool AreMaterialFunctionPackagesLoaded();` (scope `UE::Interchange::MaterialX`) — Load necessary material functions, this function can only be called in the Game Thread
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FMaterialXBase>, FOnGetMaterialXInstance, UInterchangeBaseNodeContainer&);`

### `Plugins/Interchange/Runtime/Source/Import/Public/MaterialX/MaterialXUtils/MaterialXSurfaceShaderAbstract.h` (Public)


#### class `FMaterialXSurfaceShaderAbstract`  
`class FMaterialXSurfaceShaderAbstract : public FMaterialXBase`  
_L15-639_
- inherits: `FMaterialXBase`
- L24 _public prototype_ `virtual MaterialX::InputPtr GetInputNormal(MaterialX::NodePtr Node, const char*& InputNormal) const;` — Get the normal input of a surfaceshader, used to plug it in the displacementshader @param SurfaceShaderNode - The surfaceshader that we return the input from @return the input of the normal
- L28 _protected member_ `static FString EmptyString;`
- L31 _protected member_ `static FString DefaultOutput;` — MaterialX states the default output name of the different nodes is 'out'.
- L53 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnConnectNodeOutputToInput, const FConnectNode&);`
- L55 _protected prototype_ `FMaterialXSurfaceShaderAbstract(UInterchangeBaseNodeContainer & BaseNodeContainer);`
- L67 _protected prototype_ `bool AddAttribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, int32 OutputIndex = 0, bool bBoolAsScalar = false);` — Add an attribute to a shader node from the given MaterialX input. Only floats and linear colors are supported. @param Input - The MaterialX input to retrieve and add the value from. Must be of type float/color/vector. @param InputChannelName - The name of the shader node's input to add the attribute. @param ShaderNode - The shader node to which we want to add the attribute. @param bBoolAsScalar - Create a scalar instead of a static bool parameter when applicable. @return true if the attribute was successfully added.
- L79 _protected prototype_ `bool AddAttributeFromValueOrInterface(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, int32 OutputIndex = 0, bool bBoolAsScalar = false);` — Add an attribute to a shader node from the given MaterialX input if that input has either a value or an interface name. @param Input - The MaterialX input to retrieve and add the value from. Must be of type float/color/vector. @param InputChannelName - The name of the shader node's input to add the attribute. @param ShaderNode - The shader node to which we want to add the attribute. @param bBoolAsScalar - Create a scalar instead of a static bool parameter when applicable. @return true if the attribute was successfully added.
- L92 _protected prototype_ `bool AddBooleanAttribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, bool bAsScalar = false);` — Add a bool attribute to a shader node only if its value taken from the input is not equal to its default value. Return false if the attribute does not exist or if we cannot add it @param Input - The MaterialX input to retrieve and add the value from, must be of type bool @param InputChannelName - The name of the shader node's input to add the attribute @param ShaderNode - The shader node to which we want to add the attribute @param DefaultValue - the default value to test the input against @param bAsScalar - Create a scalar value instead of a static bool parameter @return true if the attribute was successfully added
- L104 _protected prototype_ `bool AddFloatAttribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, float DefaultValue = std::numeric_limits<float>::max());` — Add a float attribute to a shader node only if its value taken from the input is not equal to its default value. Return false if the attribute does not exist or if we cannot add it @param Input - The MaterialX input to retrieve and add the value from. Must be of type float. @param InputChannelName - The name of the shader node's input to add the attribute. @param ShaderNode - The shader node to which we want to add the attribute. @param DefaultValue - the default value to test the input against. @return true if the attribute was successfully added.
- L116 _protected prototype_ `bool AddIntegerAttribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, int DefaultValue = std::numeric_limits<int>::max());` — Add an integer attribute to a shader node only if its value taken from the input is not equal to its default value. Return false if the attribute does not exist or if we cannot add it @param Input - The MaterialX input to retrieve and add the value from. Must be of type float. @param InputChannelName - The name of the shader node's input to add the attribute. @param ShaderNode - The shader node to which we want to add the attribute. @param DefaultValue - the default value to test the input against. @return true if the attribute was successfully added.
- L128 _protected prototype_ `bool AddLinearColorAttribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, const FLinearColor& DefaultValue = FLinearColor{std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()}, int32 OutputIndex = 0);` — Add an FLinearColor attribute to a shader node only if its value taken from the input is not equal to its default value. Return false if the attribute does not exist or if we cannot add it. @param Input - The MaterialX input to retrieve and add the value from. Must be of type color. @param InputChannelName - The name of the shader node's input to add the attribute. @param ShaderNode - The shader node to which we want to add the attribute. @param DefaultValue - the default value to test the input against. @return true if the attribute was successfully added.
- L140 _protected prototype_ `bool AddVectorAttribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, const FVector4f& DefaultValue = FVector4f{ std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() }, int32 OutputIndex = 0);` — Add an FLinearColor attribute to a shader node only if its value taken from the input is not equal to its default value. Return false if the attribute does not exist or if we cannot add it. @param Input - The MaterialX input to retrieve and add the value from. Must be of type vector. @param InputChannelName - The name of the shader node's input to add the attribute. @param ShaderNode - The shader node to which we want to add the attribute. @param DefaultValue - the default value to test the input against. @return true if the attribute was successfully added.
- L141 _protected prototype_ `bool AddVector2Attribute(MaterialX::InputPtr Input, const FString& InputChannelName, UInterchangeShaderNode* ShaderNode, const FVector2f& DefaultValue = FVector2f{ std::numeric_limits<float>::max(), std::numeric_limits<float>::max()}, int32 OutputIndex = 0);`
- L153 _protected function_ `template<typename T> bool ConnectNodeOutputToInput(const char* InputName, UInterchangeShaderNode* ShaderNode, const FString& InputShaderName, T DefaultValue, bool bIsTangentSpaceInput = false)` — Connect an output either from a node name or a node graph from a MaterialX input to the shader node. @param InputName - The name of the input of the SurfaceShaderNode to retrieve @param ShaderNode - The Interchange shader node to connect the MaterialX's node or node graph to @param InputShaderName - The name of the input of the shader node to connect to @param DefaultValue - The default value of the MaterialX input @param bIsTangentSpaceInput - Set the tangent space along the path of an input @param bUseDefaultValue - Usually we want to avoid creating default values on direct inputs of shaders (StandardSurface, OpenPBR), but some shaders (UsdPreviewSurface) we need to decide that at run-time
- L199 _protected prototype_ `bool ConnectNodeGraphOutputToInput(MaterialX::InputPtr InputToNodeGraph, UInterchangeShaderNode* ShaderNode, const FString& ParentInputName);` — Connect an ouput in the NodeGraph to the ShaderGraph. @param InputToNodeGraph - The input from the standard surface to retrieve the output in the NodeGraph. @param ShaderNode - The Interchange shader node to connect the MaterialX's node graph to. @param ParentInputName - The name of the input of the shader node that we want the node graph to be connected to. @return true if the given input is attached to one of the outputs of a node graph.
- L211 _protected prototype_ `bool ConnectMatchingNodeOutputToInput(const FConnectNode& Connect);` — Create and connect the output of a MaterialX node that has already a matching in UE to a shader node. If not, search for a registered delegate. @param Node - The MaterialX node of a given type used to create the appropriate shader node. @param ParentShaderNode - The shader node to connect to. @param InputChannelName - The input of the ParentShaderNode to connect to. @return true if a shader node has been successfully created and is connected to the given input.
- L222 _protected prototype_ `void ConnectNodeCategoryOutputToInput(const MaterialX::Edge& Edge, UInterchangeShaderNode* ParentShaderNode, const FString& InputChannelName, const FString& OutputName = TEXT("out"` — Create and connect manually the output of a MaterialX node to a shader node. @param Edge - The MaterialX edge that has the current node, its parent and the input bridge between the two. @param ParentShaderNode - The shader node to connect to. @param InputChannelName - The input of the ParentShaderNode to connect to. @return true if a shader node has been successfully created and is connected to the given input.
- L233 _protected prototype_ `bool ConnectNodeNameOutputToInput(MaterialX::InputPtr Input, UInterchangeShaderNode* ShaderNode, const FString& ParentInputName);` — Create and connect a node name directly connected from an input to a shader node. @param Node - The MaterialX node of a given type used to create the appropriate shader node. @param ParentShaderNode - The shader node to connect to. @param InputChannelName - The input of the ParentShaderNode to connect to. @return true if a shader node has been successfully created and is connected to the given input.
- L238 _protected prototype_ `void ConnectConstantInputToOutput(const FConnectNode& Connect);` — <constant>
- L241 _protected prototype_ `void ConnectExtractInputToOutput(const FConnectNode& Connect);` — <extract>
- L244 _protected prototype_ `void ConnectDotInputToOutput(const FConnectNode& Connect);` — <dot>
- L247 _protected prototype_ `void ConnectTransformPositionInputToOutput(const FConnectNode& Connect);` — <transformpoint>
- L250 _protected prototype_ `void ConnectTransformVectorInputToOutput(const FConnectNode& Connect);` — <transformvector>
- L253 _protected prototype_ `void ConnectRotate2DInputToOutput(const FConnectNode& Connect);` — <rotate2d>
- L256 _protected prototype_ `void ConnectImageInputToOutput(const FConnectNode& Connect);` — <image>
- L259 _protected prototype_ `void ConnectIfGreaterInputToOutput(const FConnectNode& Connect);` — <ifgreater>
- L262 _protected prototype_ `void ConnectIfGreaterEqInputToOutput(const FConnectNode& Connect);` — <ifgreatereq>
- L265 _protected prototype_ `void ConnectIfEqualInputToOutput(const FConnectNode& Connect);` — <ifequal>
- L268 _protected prototype_ `void ConnectOutsideInputToOutput(const FConnectNode& Connect);` — <outside>
- L271 _protected prototype_ `void ConnectPositionInputToOutput(const FConnectNode& Connect);` — <position>
- L274 _protected prototype_ `void ConnectNormalInputToOutput(const FConnectNode& Connect);` — <normal>
- L277 _protected prototype_ `void ConnectTangentInputToOutput(const FConnectNode& Connect);` — <tangent>
- L280 _protected prototype_ `void ConnectBitangentInputToOutput(const FConnectNode& Connect);` — <bitangent>
- L283 _protected prototype_ `void ConnectTimeInputToOutput(const FConnectNode& Connect);` — <time>
- L286 _protected prototype_ `void ConnectNoise2DInputToOutput(const FConnectNode& Connect);` — <noise2d>
- L289 _protected prototype_ `void ConnectCellNoise2DInputToOutput(const FConnectNode& Connect);` — <cellnoise2d>
- L292 _protected prototype_ `void ConnectWorleyNoise2DInputToOutput(const FConnectNode& Connect);` — <worleynoise2d>
- L295 _protected prototype_ `void ConnectNoise3DInputToOutput(const FConnectNode& Connect);` — <noise3d>
- L298 _protected prototype_ `void ConnectCellNoise3DInputToOutput(const FConnectNode& Connect);` — <cellnoise3d>
- L301 _protected prototype_ `void ConnectWorleyNoise3DInputToOutput(const FConnectNode& Connect);` — <worleynoise3d>
- L304 _protected prototype_ `void ConnectHeightToNormalInputToOutput(const FConnectNode& Connect);` — <heighttonormal>
- L307 _protected prototype_ `void ConnectBlurInputToOutput(const FConnectNode& Connect);` — <blur>
- L310 _protected prototype_ `void ConnectTexCoordInputToOutput(const FConnectNode& Connect);` — <texcoord>
- L313 _protected prototype_ `void ConnectSwitchInputToOutput(const FConnectNode& Connect);` — <switch>
- L316 _protected prototype_ `void ConnectNormalMapInputToOutput(const FConnectNode& Connect);` — <normalmap>
- L319 _protected prototype_ `void ConnectRefractInputToOutput(const FConnectNode& Connect);` — <refract>
- L322 _protected prototype_ `void ConnectViewDirectionInputToOutput(const FConnectNode& Connect);` — <viewdirection>
- L325 _protected prototype_ `void ConnectAndInputToOutput(const FConnectNode& Connect);` — <and>
- L328 _protected prototype_ `void ConnectOrInputToOutput(const FConnectNode& Connect);` — <or>
- L331 _protected prototype_ `void ConnectXorInputToOutput(const FConnectNode& Connect);` — <xor>
- L334 _protected prototype_ `void ConnectNotInputToOutput(const FConnectNode& Connect);` — <not>
- L337 _protected prototype_ `void ConnectSparseVolumeInputToOutput(const FConnectNode& Connect);` — <sparse_volume> is define in Engine/Binaries/ThirdParty/MaterialX/libraries/Interchange
- L340 _protected prototype_ `void ConnectLuminanceInputToOutput(const FConnectNode& Connect);` — <luminance>
- L343 _protected prototype_ `void ConnectHexTiledInputToOutput(const FConnectNode& Connect);` — <hextiledimage> <hextilednormalmap>
- L346 _protected prototype_ `void ConnectLatLongImageInputToOutput(const FConnectNode& Connect);` — <latlongimage>
- L349 _protected prototype_ `void ConnectFractalInputToOutput(const FConnectNode& Connect);` — <fractal2d/3d>
- L354 _protected prototype_ `bool ConnectSubsurfaceTransmissionToSurfaceShader(UInterchangeShaderNode* OpenPbrStandarSurfaceShaderNode, EInterchangeMaterialXShaders SurfaceShaderType , const FName& BaseWeight, const FName& BaseColor , const FName& TransmissionWeight, const FName& TransmissionColor, const FName& TransmissionDepth, const FName& TransmissionDispersionAbbeNumber, const FName& TransmissionDispersionScale, const FName& TransmissionScatter, const FName& TransmissionScatterAnisotropy , const FName& SubsurfaceWeight, const FName& SubsurfaceColor, const FName& SubsurfaceRadiusScale , const FName & FrontMaterialOpaque, const FName & FrontMaterialTranslucent);` — Function used only by both Standard Surface and OpenPBR to have both Subsurface and Transmission
- L369 _protected prototype_ `UInterchangeShaderNode* CreateMaskShaderNode(uint8 RGBA, MaterialX::ElementPtr Element, const FString& NodeName, const FString& OutputName = TEXT("out"` — Create a ComponentMask shader node. @param RGBA - The mask component. For example: 0b1011 -> Only RBA are toggled @param Element - The element that we take the whole hierarchy from to ensure the uniqueness of the name @param NodeName - the name of the shader node. @param OutputName - the name of the output of the MaterialX node. The default name is 'out' as stated by the standard library. @return The ComponentMask node.
- L381 _protected prototype_ `UInterchangeShaderNode* CreateShaderNode(MaterialX::ElementPtr Element, const FString& NodeName, const FString& ShaderType, const FString& OutputName = TEXT("out"` — Helper function to create an InterchangeShaderNode. @param Element - The element that we take the whole hierarchy from to ensure the uniqueness of the name @param NodeName - The name of the shader node. @param ShaderType - The type of shader node we want to create. @param OutputName - The output name of the MaterialX node. The default name is 'out' as stated by the standard library. @return The shader node that was created.
- L392 _protected prototype_ `UInterchangeFunctionCallShaderNode* CreateFunctionCallShaderNode(MaterialX::ElementPtr Element, const FString& NodeName, const FString& FunctionPath, const FString& OutputName = TEXT("out"` — Helper function to create an InterchangeFunctionCallShaderNode. @param NodeName - The name of the shader node. @param FunctionPath - The path to the Material Function we want to create. @param OutputName - The output name of the MaterialX node. The default name is 'out' as stated by the standard library. @return The shader node that was created.
- L393 _protected prototype_ `UInterchangeFunctionCallShaderNode* CreateFunctionCallShaderNode(MaterialX::ElementPtr Element, const FString& NodeName, uint8 EnumType, uint8 EnumValue, const FString& OutputName = TEXT("out"`
- L403 _protected function_ `template<typename TextureTypeNode> UInterchangeTextureNode* CreateTextureNode(MaterialX::NodePtr Node) const` — Helper function to create an InterchangeTextureNode. @param Node - The MaterialX node. This should be of the category <image>. No test is done on it. @return The texture node that was created.
- L527 _protected prototype_ `const FString& GetMatchedInputName(MaterialX::NodePtr Node, MaterialX::InputPtr Input) const;` — Get the UE corresponding name of a MaterialX Node category and input for a material. @param Input - MaterialX input. @return The matched name of the Node/Input, or an empty string.
- L536 _protected prototype_ `FString GetInputName(MaterialX::InputPtr Input) const;` — Get the input name. Use this function instead of getName() because this returns the name that will be used by UE inputs even if a renaming has occurred. @param Input - The input to retrieve the name from. @return The input name.
- L546 _protected prototype_ `FString GetFilePrefix(MaterialX::ElementPtr Element) const;` — Return the innermost file prefix of an element in the current scope. If it has none, it will take the one from its parents. @param Element - the Element to retrieve the file prefix from. This can be anything: an input, a node, a nodegraph, and so on. @return a file prefix or an empty string.
- L555 _protected prototype_ `FLinearColor GetVector(MaterialX::InputPtr Input) const;` — Helper function that returns a vector. The function makes no assumption on the input, and it should have a value of vectorN type. @param Input - The input that has a vectorN value in it. @return The vector.
- L564 _protected prototype_ `FString GetAttributeParentName(MaterialX::NodePtr Node, MaterialX::InputPtr ConnectedInput) const;` — Retrieve the Interchange parent name of a MaterialX node. Useful when a node is a combination of several nodes connected to different inputs, such as Noise3D. @param Node - The node whose parent name is retrieved. @param ConnectedInput - The connected input to the Node, may be null, may happen at the top of a graph when there's upstream/downstream connection @return The node of the parent.
- L572 _protected prototype_ `FString GetUniqueName(MaterialX::ElementPtr Element) const;` — Ensure that we put in the node container the unique name, 2 nodes in a same file may have the same name as long as their parent's name is different, we just traverse the whole hierarchy to have a unique name @param Element - An Element that may be an Input a node or a nodegraph @return The unique name of the Element taking the whole hierarchy into account
- L574 _protected prototype_ `virtual void RegisterConnectNodeOutputToInputDelegates();`
- L581 _protected prototype_ `void SetMatchingInputsNames(MaterialX::NodePtr Node) const;` — Set the matching inputs names of a node to correspond to the one used by UE. The matching name is stored under the attribute UE::NewName. @param Node - Look up to all inputs of Node and set the matching name attribute.
- L589 _protected prototype_ `void SetAttributeNewName(MaterialX::InputPtr Input, const char* NewName) const;` — Add the input new name under the attribute UE::NewName. @param Input - The input to add the proper attribute. @param NewName - the new name of the input.
- L597 _protected prototype_ `UInterchangeShaderNode* Translate(EInterchangeMaterialXShaders ShaderType);` — This function should be called first by the Translate method of derived class, SurfaceShaderNode should initialized first by the derived class @param ShaderType - the type of ShaderGraphNode to create @return The shader node created, usually a function call shader node
- L605 _protected prototype_ `UInterchangeShaderNode* Translate(UInterchangeShaderNode* ShaderNode);` — This function should be called first by the Translate method of derived class, SurfaceShaderNode should initialized first by the derived class @param ShaderNode - the shader node that was created, can be either a shader node or a function call shader node @return The shader node created with all inputs connected to it
- L607 _protected prototype_ `virtual UInterchangeBaseNode* Translate(MaterialX::NodePtr ShaderNode) override = 0;`
- L611 _private prototype_ `UInterchangeShaderNode* ConnectGeometryInputToOutput(const FConnectNode& Connect, const FString& ShaderType, const FString& TransformShaderType, const FString& TransformInput, const FString& TransformSourceType, int32 TransformSource, const FString& TransformType, int32 TransformSDestination, bool bIsVector = true);`
- L612 _private prototype_ `UInterchangeShaderNode* ConnectNoise2DInputToOutput(const FConnectNode& Connect, const FString& ShaderType, EVectorNoiseFunction NoiseFunction, uint8 Mask);`
- L613 _private prototype_ `void ConnectLogicalInputToOutput(const FConnectNode& Connect, const FString& LogicalMaterialFunction);`
- L620 _protected typedef_ `using FNodeOutput = TPair<FString, FString>;` — @param Get<0>: node @param Get<1>: output
- L623 _protected member_ `TMap<FNodeOutput, UInterchangeShaderNode*> ShaderNodes;` — Store the shader nodes only when we create the shader graph node
- L626 _protected member_ `TMap<FString, FOnConnectNodeOutputToInput> MatchingConnectNodeDelegates;` — Matching MaterialX category and Connect function
- L629 _protected member_ `MaterialX::NodePtr SurfaceShaderNode;` — The surface shader node processed during the Translate, up to the derived class to initialize it
- L632 _protected member_ `UInterchangeShaderGraphNode* ShaderGraphNode;` — Initialized by the material shader (e.g: surfacematerial), the derived class should only set the ShaderType
- L635 _protected member_ `FString SurfaceMaterialName;` — Here for log purpose, it makes the logs easier to read especially when several materials are imported at once
- L638 _protected member_ `bool bTangentSpaceInput;` — Used for texture compression and transform to tangent space nodes coming from inputs such as coat_normal

#### struct `FMaterialXSurfaceShaderAbstract::FConnectNode`  
`struct FConnectNode`  
_L36-51_
- L39 _public member_ `MaterialX::NodePtr UpstreamNode;` — The MaterialX node of a given type used to create the appropriate shader node.
- L42 _public member_ `UInterchangeShaderNode* ParentShaderNode;` — The shader node to connect to.
- L45 _public member_ `FString InputChannelName;` — The input of the ParentShaderNode to connect to.
- L50 _public member_ `FString OutputName{ DefaultOutput };` — The output name of the MaterialX node that we need to connect to. This is the active output (e.g: the output given by an input connecting 2 nodes) The default name is 'out' as stated by the standard library. (not necessarily always the case though)

#### Free symbols / members of external scopes

- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnConnectNodeOutputToInput, const FConnectNode&);`
- L480 _function_ `` (scope `FMaterialXSurfaceShaderAbstract::CreateTextureNode`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeGeometryCacheFactory.h` (Public)


#### class `UInterchangeGeometryCacheFactory`  
`class UInterchangeGeometryCacheFactory : public UInterchangeFactoryBase`  
_L16-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L24 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L25 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L26 _public prototype_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks) override;`
- L27 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L28 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L29 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L30 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L31 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L32 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L33 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L34 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L35 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L41 _private member_ `TArray<TObjectPtr<UGeometryCacheTrack>> Tracks;`
- L42 _private member_ `TPimplPtr<class FGeometryCacheComponentResetAsset> ResetAssetOnReimport;`
- L45 _private member_ `TMap<FString, UE::Interchange::FAnimationPayloadData> TransformAnimationPayloadResults;` — Animation queries results

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeMeshHelper.h` (Public)


#### class `UE::Interchange::Private::MeshHelper::FInterchangeNaniteAssemblyBuilder`  
`class FInterchangeNaniteAssemblyBuilder`  
_L157-184_
- desc: Nanite assembly builder helper for static and skeletal meshes.
- L160 _public prototype_ `~FInterchangeNaniteAssemblyBuilder();`
- L165 _public prototype_ `static FInterchangeNaniteAssemblyBuilder Create(USkeletalMesh* SkeletalMesh, const UInterchangeMeshFactoryNode* MeshFactoryNode, const UInterchangeBaseNodeContainer* NodeContainer);` — Create a builder for the given skeletal mesh. The given mesh factory node must hold the mesh part dependency information.
- L170 _public prototype_ `static FInterchangeNaniteAssemblyBuilder Create(UStaticMesh* StaticMesh, const UInterchangeMeshFactoryNode* MeshFactoryNode, const UInterchangeBaseNodeContainer* NodeContainer);` — Create a builder for the given static mesh. The given mesh factory node must hold the mesh part dependency information.
- L176 _public prototype_ `void AddDescription(const TOptional<UE::Interchange::FNaniteAssemblyDescription>& Description);` — Add the given FNaniteAssemblyDescription data to the builder. This can be called more than once in order to merge multiple descriptions into a single skeletal/static mesh assembly.
- L182 _private member_ `TUniquePtr<ImplBase> Impl;`
- L183 _private prototype_ `explicit FInterchangeNaniteAssemblyBuilder(TUniquePtr<ImplBase> Impl);`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Interchange` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Interchange` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L32 _namespace_ `namespace MeshHelper` (scope `UE::Interchange::Private`)
- L36 _prototype_ `bool AddConvexGeomFromVertices( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const FMeshDescription& MeshDescription, FKAggregateGeom& AggGeom );` (scope `UE::Interchange::Private::MeshHelper`)
- L42 _prototype_ `bool DecomposeConvexMesh( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const FMeshDescription& MeshDescription, UBodySetup* BodySetup );` (scope `UE::Interchange::Private::MeshHelper`)
- L48 _prototype_ `bool AddBoxGeomFromTris( const FMeshDescription& MeshDescription, FKAggregateGeom& AggGeom, bool bForcePrimitiveGeneration = true );` (scope `UE::Interchange::Private::MeshHelper`)
- L54 _prototype_ `bool AddSphereGeomFromVertices( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const FMeshDescription& MeshDescription, FKAggregateGeom& AggGeom, bool bForcePrimitiveGeneration = true );` (scope `UE::Interchange::Private::MeshHelper`)
- L61 _prototype_ `bool AddCapsuleGeomFromVertices( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const FMeshDescription& MeshDescription, FKAggregateGeom& AggGeom );` (scope `UE::Interchange::Private::MeshHelper`)
- L67 _prototype_ `bool ImportBoxCollision( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const TMap<FInterchangeMeshPayLoadKey, FMeshPayload>& BoxCollisionPayloads, UStaticMesh* StaticMesh, bool bForcePrimitiveGeneration = true );` (scope `UE::Interchange::Private::MeshHelper`)
- L74 _prototype_ `bool ImportCapsuleCollision( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const TMap<FInterchangeMeshPayLoadKey, FMeshPayload>& CapsuleCollisionPayloads, UStaticMesh* StaticMesh );` (scope `UE::Interchange::Private::MeshHelper`)
- L80 _prototype_ `bool ImportSphereCollision( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const TMap<FInterchangeMeshPayLoadKey, FMeshPayload>& SphereCollisionPayloads, UStaticMesh* StaticMesh, bool bForcePrimitiveGeneration = true );` (scope `UE::Interchange::Private::MeshHelper`)
- L87 _prototype_ `bool ImportConvexCollision( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, const TMap<FInterchangeMeshPayLoadKey, FMeshPayload>& ConvexCollisionPayloads, UStaticMesh* StaticMesh, const UInterchangeStaticMeshLodDataNode* LodDataNode );` (scope `UE::Interchange::Private::MeshHelper`)
- L94 _prototype_ `bool ImportSockets( const UInterchangeFactoryBase::FImportAssetObjectParams& Arguments, UStaticMesh* StaticMesh, const UInterchangeStaticMeshFactoryNode* FactoryNode );` (scope `UE::Interchange::Private::MeshHelper`)
- L100 _prototype_ `void RemapPolygonGroups( const FMeshDescription& SourceMesh, FMeshDescription& TargetMesh, PolygonGroupMap& RemapPolygonGroup );` (scope `UE::Interchange::Private::MeshHelper`)
- L107 _prototype_ `void AddSceneNodeGeometricAndPivotToGlobalTransform(FTransform& GlobalTransform, const UInterchangeSceneNode* SceneNode, const bool bBakeMeshes, const bool bBakePivotMeshes);` (scope `UE::Interchange::Private::MeshHelper`) — return the result of the global transform with the geometric and pivot transform of the scene node.
- L124 _prototype_ `void SkeletalMeshFactorySetupAssetMaterialArray(TArray<FSkeletalMaterial>& ExistMaterials , TMap<FString, FString> ImportedSlotMaterialDependencies , const UInterchangeBaseNodeContainer* NodeContainer , const bool bIsReimport);` (scope `UE::Interchange::Private::MeshHelper`)
- L129 _prototype_ `void StaticMeshFactorySetupAssetMaterialArray(TArray<FStaticMaterial>& ExistMaterials , TMap<FString, FString> ImportedSlotMaterialDependencies , const UInterchangeBaseNodeContainer* NodeContainer , const bool bIsReimport);` (scope `UE::Interchange::Private::MeshHelper`)
- L134 _prototype_ `void GeometryCacheFactorySetupAssetMaterialArray(TArray<TObjectPtr<UMaterialInterface>>& ExistMaterials , TArray<FName>& MaterialSlotNames , TMap<FString, FString> ImportedSlotMaterialDependencies , const UInterchangeBaseNodeContainer* NodeContainer , const bool bIsReimport);` (scope `UE::Interchange::Private::MeshHelper`)
- L140 _prototype_ `void CopyMorphTargetsMeshDescriptionToSkeletalMeshDescription(TArray<FString>& SkeletonMorphCurveMetadataNames , const TMap<FString, TOptional<UE::Interchange::FMeshPayloadData>>& LodMorphTargetMeshDescriptions , FMeshDescription& DestinationMeshDescription , const bool bMergeMorphTargetWithSameName);` (scope `UE::Interchange::Private::MeshHelper`)
- L146 _prototype_ `void RemapSkeletalMeshVertexColorToMeshDescription(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, FMeshDescription& MeshDescription);` (scope `UE::Interchange::Private::MeshHelper`)
- L150 _prototype_ `EInterchangeMeshCollision GetMeshCollisionFromName(const FString& Name);` (scope `UE::Interchange::Private::MeshHelper`) — Checks name for UBX_, UCX_, MCDCX_, USP_, UCP_ prefixes.
- L153 _prototype_ `bool HasPotentialMeshCollisionPrefix(const FString& Name);` (scope `UE::Interchange::Private::MeshHelper`) — Checks if Name has any of the prefixes mentioned in GetMeshCollisionFromName, without the '_', this primarily used for checking for typos.

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeMeshPayload.h` (Public)


#### struct `UE::Interchange::FNaniteAssemblyDescription`  
`struct FNaniteAssemblyDescription`  
_L14-42_
- L24 _public member_ `TArray<FTransform> Transforms;` — Assembly Transforms
- L27 _public member_ `TArray<int32> PartIndices;` — Assembly Part Indices, must be the same length as Transforms
- L30 _public member_ `TArray<TArray<FString>> PartUids;` — List of interchange mesh uids, or, UE asset paths per index
- L35 _public member_ `TArray<FBoneInfluence> BoneInfluences;` — For SkeletalMesh assemblies there should one or more influences per transform. For StaticMesh assemblies this should be empty.
- L38 _public member_ `TArray<int32> NumInfluencesPerInstance;` — Number of bone influences per instance
- L41 _public prototype_ `bool IsValid(FString* OutReason = nullptr) const;` — Check that the above arrays have been authored correctly

#### struct `UE::Interchange::FNaniteAssemblyDescription::FBoneInfluence`  
`struct FBoneInfluence`  
_L16-21_
- L18 _public member_ `uint32 BoneIndex = INDEX_NONE;`
- L20 _public member_ `float BoneWeight = 1.0f;`

#### struct `UE::Interchange::FMeshPayloadData`  
`struct FMeshPayloadData`  
_L44-64_
- L48 _public member_ `FMeshDescription MeshDescription;` — Currently the skeletalmesh payload data is editor only, we have to move to something available at runtime
- L52 _public member_ `TArray<FString> JointNames;` — This map the indice use in the meshdescription to the bone name, so we can use this information to remap properly the skinning when we merge the meshdescription
- L57 _public member_ `int32 VertexOffset;` — We don't have to store GlobalTransform here anymore, since The Mesh node parent bake transform was pass to the payload request. The vertex offset of the morph target in case we combine mesh node together
- L59 _public member_ `FString MorphTargetName;` — The name of the morph target
- L63 _public member_ `TOptional<FNaniteAssemblyDescription> NaniteAssemblyDescription;` — Optional Nanite Assembly data that should be attached to this skeletal or static mesh.

#### struct `UE::Interchange::FMeshPayload`  
`struct FMeshPayload`  
_L66-71_
- L68 _public member_ `FString MeshName;`
- L69 _public member_ `TOptional<UE::Interchange::FMeshPayloadData> PayloadData;`
- L70 _public member_ `FTransform Transform = FTransform::Identity;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeMeshPayloadInterface.h` (Public)


#### class `UInterchangeMeshPayloadInterface`  
`class UInterchangeMeshPayloadInterface : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeMeshPayloadInterface`  
`class IInterchangeMeshPayloadInterface`  
_L27-50_
- desc: Static mesh payload interface. Derive from this interface if your payload can import static mesh
- L33 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform) const` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")`
- L49 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const = 0;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve a particular payload contained into the specified source data. @param PayloadAttributes - Attributes passed by pipelines to the Translators @return a PayloadData containing the the data ask with the key.

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeOBJTranslator.h` (Public)


#### class `UInterchangeOBJTranslator`  
`class UInterchangeOBJTranslator : public UInterchangeTranslatorBase, public IInterchangeMeshPayloadInterface, public IInterchangeTexturePayloadInterface`  
_L20-83_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeMeshPayloadInterface,IInterchangeTexturePayloadInterface`
- L28 _public prototype_ `UInterchangeOBJTranslator();`
- L29 _public prototype_ `virtual ~UInterchangeOBJTranslator();`
- L32 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L33 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override;`
- L34 _public prototype_ `virtual EInterchangeTranslatorType GetTranslatorType() const override;`
- L42 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L55 _public function_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const FTransform& MeshGlobalTransform) const override` — `UE_DEPRECATED(5.6, "Deprecated. Use GetMeshPayloadData(const FInterchangeMeshPayLoadKey&) instead.")` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the the data ask with the key.
- L63 _public prototype_ `virtual TOptional<UE::Interchange::FMeshPayloadData> GetMeshPayloadData(const FInterchangeMeshPayLoadKey& PayLoadKey, const UE::Interchange::FAttributeStorage& PayloadAttributes) const override;`
- L78 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param InSourceData - The source data containing the data to translate @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the imported data. The TOptional will not be set if there is an error.
- L82 _private member_ `TPimplPtr<FObjData> ObjDataPtr;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangePhysicsAssetFactory.h` (Public)


#### class `UInterchangePhysicsAssetFactory`  
`class UInterchangePhysicsAssetFactory : public UInterchangeFactoryBase`  
_L15-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L23 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L24 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L25 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L26 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeSkeletalMeshFactory.h` (Public)


#### class `FScopedSkeletalMeshReimportUtility`  
`class FScopedSkeletalMeshReimportUtility : public FSkinnedMeshComponentRecreateRenderStateContext`  
_L30-41_
- inherits: `FSkinnedMeshComponentRecreateRenderStateContext`
- desc: Utility class used on reimport only to: - Call PostEditchange at the end of the reimport which will reallocate the render resource - Used to recreate all skinned mesh components for a given skinned asset via FSkinnedMeshComponentRecreateRenderStateContext. - Lock the skeletal mesh's properties while it is updated
- L33 _public prototype_ `FScopedSkeletalMeshReimportUtility(USkeletalMesh* InSkeletalMesh);`
- L34 _public prototype_ `~FScopedSkeletalMeshReimportUtility();`
- L38 _private member_ `TUniquePtr<FScopedSkeletalMeshPostEditChange> ScopedPostEditChange;`
- L40 _private member_ `FEvent* LockPropertiesEvent = nullptr;`

#### struct `UE::Interchange::FMeshNodeContext`  
`struct FMeshNodeContext`  
_L46-70_
- desc: Get the mesh node context for each MeshUids
- L48 _public member_ `const UInterchangeMeshNode* MeshNode = nullptr;`
- L50 _public member_ `FTransform SceneGlobalTransform;`
- L52 _public member_ `FTransform GeometricTransform;` — If MeshNodes was resolved from a UInterchangeSceneNode it can have a non-identity GeometricTransform, which is needed for T0 re-skin calculations.
- L59 _public member_ `FString SceneNodeName;` — SceneNodeName is needed to identify the bone targeting given Mesh for Rigid to Rigged conversions. It's also used for the GeometryParts. This is the instancing UInterchangeSceneNode's name.
- L61 _public member_ `FInterchangeMeshPayLoadKey TranslatorPayloadKey;`
- L64 _public prototype_ `FInterchangeMeshPayLoadKey GetTranslatorAndTransformPayloadKey() const;` — Return a new key with the translator key merge with the transform
- L66 _public prototype_ `FInterchangeMeshPayLoadKey GetMorphTargetAndTransformPayloadKey(const FInterchangeMeshPayLoadKey& MorphTargetKey) const;`
- L69 _public prototype_ `FString GetUniqueId() const;` — Return the translator key merge with the transform

#### class `UInterchangeSkeletalMeshFactory`  
`class UInterchangeSkeletalMeshFactory : public UInterchangeFactoryBase`  
_L74-152_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L112 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L113 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L114 _public prototype_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks) override;`
- L115 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L116 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L117 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L118 _public prototype_ `virtual void Cancel() override;`
- L119 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L120 _public prototype_ `virtual void BuildObject_GameThread(const FSetupObjectParams& Arguments, bool& OutPostEditchangeCalled) override;`
- L121 _public prototype_ `virtual void FinalizeObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L122 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L123 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L124 _public prototype_ `virtual bool SetReimportSourceIndex(const UObject* Object, int32 SourceIndex) const override;`
- L125 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L126 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L127 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L145 _private member_ `TUniquePtr<FScopedSkeletalMeshReimportUtility> ScopedReimportUtility;`
- L147 _private member_ `TMap<int32, FLodPayloads> PayloadsPerLodIndex;`
- L149 _private member_ `FImportAssetObjectData ImportAssetObjectData;`
- L151 _private member_ `TArray<FNaniteAssemblyData> NaniteAssemblyData;`

#### struct `UInterchangeSkeletalMeshFactory::FImportAssetObjectLODData`  
`struct FImportAssetObjectLODData`  
_L78-92_
- L80 _public member_ `int32 LodIndex = INDEX_NONE;`
- L81 _public member_ `TArray<FName> ExistingOriginalPerSectionMaterialImportName;`
- L83 _public member_ `TArray<SkeletalMeshImportData::FMaterial> ImportedMaterials;`
- L84 _public member_ `TArray<SkeletalMeshImportData::FBone> RefBonesBinary;`
- L86 _public member_ `TArray<UE::Interchange::FMeshNodeContext> MeshNodeContexts;`
- L87 _public member_ `bool bUseTimeZeroAsBindPose = false;`
- L88 _public member_ `bool bDiffPose = false;`
- L91 _public member_ `TArray<FString> SkeletonMorphCurveMetadataNames;` — Store Morphtarget name, we want to add skeleton curve meta data ingame thread (FinalizeObject_GameThread)

#### struct `UInterchangeSkeletalMeshFactory::FImportAssetObjectData`  
`struct FImportAssetObjectData`  
_L94-108_
- L96 _public member_ `bool bIsReImport = false;`
- L97 _public member_ `USkeleton* SkeletonReference = nullptr;`
- L98 _public member_ `bool bApplyGeometryOnly = false;`
- L99 _public member_ `TArray<FImportAssetObjectLODData> LodDatas;`
- L101 _public member_ `TArray<FSkinWeightProfileInfo> ExistingSkinWeightProfileInfos;`
- L102 _public member_ `TArray<ClothingAssetUtils::FClothingAssetMeshBinding> ExistingClothingBindings;`
- L104 _public member_ `TArray<FMeshDescription> ExistingAlternateMeshDescriptionPerLOD;`
- L107 _public prototype_ `bool IsValid() const;`

#### struct `UInterchangeSkeletalMeshFactory::FLodPayloads`  
`struct FLodPayloads`  
_L132-136_
- L134 _public member_ `TMap<FInterchangeMeshPayLoadKey, TOptional<UE::Interchange::FMeshPayloadData>> MeshPayloadPerKey;`
- L135 _public member_ `TMap<FInterchangeMeshPayLoadKey, TOptional<UE::Interchange::FMeshPayloadData>> MorphPayloadPerKey;`

#### struct `UInterchangeSkeletalMeshFactory::FNaniteAssemblyData`  
`struct FNaniteAssemblyData`  
_L138-142_
- L140 _public member_ `UE::Interchange::FNaniteAssemblyDescription Description;`
- L141 _public member_ `TArray<FString> JointNames;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeSkeletonFactory.h` (Public)


#### class `UInterchangeSkeletonFactory`  
`class UInterchangeSkeletonFactory : public UInterchangeFactoryBase`  
_L15-31_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L23 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L24 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L25 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L27 _public prototype_ `virtual UObject* GetObjectToReimport(UObject* ReimportObject, const UInterchangeFactoryBaseNode& FactoryNode, const FString& PackageName, const FString& AssetName, const FString& SubPathString) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Mesh/InterchangeStaticMeshFactory.h` (Public)


#### class `UInterchangeStaticMeshFactory`  
`class UInterchangeStaticMeshFactory : public UInterchangeFactoryBase`  
_L27-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L35 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L36 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L37 _public prototype_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks) override;`
- L38 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L39 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L40 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L41 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L42 _public prototype_ `virtual void BuildObject_GameThread(const FSetupObjectParams& Arguments, bool& OutPostEditchangeCalled) override;`
- L43 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L44 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L45 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L46 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L47 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L62 _private member_ `TMap<int32, FLodPayloads> PayloadsPerLodIndex;`
- L64 _private prototype_ `void CommitMeshDescriptions(UStaticMesh& StaticMesh);`
- L65 _private prototype_ `void BuildFromMeshDescriptions(UStaticMesh& StaticMesh);`
- L68 _private prototype_ `void SetupSourceModelsSettings(UStaticMesh& StaticMesh, const TArray<FMeshDescription>& LodMeshDescriptions, bool bAutoComputeLODScreenSizes, const TArray<float>& LodScreenSizes, int32 PreviousLodCount, int32 FinalLodCount, bool bIsAReimport);`
- L79 _private member_ `FImportAssetObjectData ImportAssetObjectData;`

#### struct `UInterchangeStaticMeshFactory::FLodPayloads`  
`struct FLodPayloads`  
_L53-60_
- L55 _public member_ `TMap<FInterchangeMeshPayLoadKey, UE::Interchange::FMeshPayload> MeshPayloadPerKey;`
- L56 _public member_ `TMap<FInterchangeMeshPayLoadKey, UE::Interchange::FMeshPayload> CollisionBoxPayloadPerKey;`
- L57 _public member_ `TMap<FInterchangeMeshPayLoadKey, UE::Interchange::FMeshPayload> CollisionCapsulePayloadPerKey;`
- L58 _public member_ `TMap<FInterchangeMeshPayLoadKey, UE::Interchange::FMeshPayload> CollisionSpherePayloadPerKey;`
- L59 _public member_ `TMap<FInterchangeMeshPayLoadKey, UE::Interchange::FMeshPayload> CollisionConvexPayloadPerKey;`

#### struct `UInterchangeStaticMeshFactory::FImportAssetObjectData`  
`struct FImportAssetObjectData`  
_L70-78_
- L72 _public member_ `TArray<FMeshDescription> LodMeshDescriptions;`
- L73 _public member_ `EInterchangeMeshCollision Collision = EInterchangeMeshCollision::None;`
- L74 _public member_ `FKAggregateGeom AggregateGeom;`
- L75 _public member_ `bool bIsAppGame = false;`
- L76 _public member_ `bool bImportedCustomCollision = false;`
- L77 _public member_ `bool bImportCollision = false;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeActorFactory.h` (Public)


#### class `UInterchangeActorFactory`  
`class UInterchangeActorFactory : public UInterchangeFactoryBase`  
_L21-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L29 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L32 _protected prototype_ `virtual void ExecuteResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject) override;`
- L34 _protected prototype_ `virtual UObject* ImportSceneObject_GameThread(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams) override;`
- L39 _protected prototype_ `void ProcessTags(UInterchangeActorFactoryNode* FactoryNode, AActor* SpawnedActor);`
- L40 _protected prototype_ `void ProcessLayerNames(UInterchangeActorFactoryNode* FactoryNode, AActor* SpawnedActor);`
- L42 _protected prototype_ `void AddUniqueLayersToWorld(UWorld* World, const TSet<FString>& LayerNames);`
- L51 _protected prototype_ `virtual UObject* ProcessActor(AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params);` — Method called in UInterchangeActorFactory::ImportSceneObject_GameThread to allow child class to complete the creation of the actor. This method is expected to return the UOBject to apply the factory node's custom attributes to.
- L58 _protected prototype_ `virtual void ApplyAllCustomAttributesToObject(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams, AActor& SpawnedActor, UObject* ObjectToUpdate);` — Method used to apply all the custom attributes to the Actor or its sub components. Base class method will simply use ActorHelper to apply all the custom attributes to the object.
- L61 _protected function_ `template <typename T> void LogMessage(const FImportSceneObjectsParams& Params, const FText& Message, const FString& ActorLabel)`
- L68 _protected function_ `template <typename T> void FillMessage(const FImportSceneObjectsParams& Params, const FText& Message, const FString& ActorLabel, T& Result)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeActorHelper.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Interchange` (scope `UE`)
- L21 _namespace_ `namespace ActorHelper` (scope `UE::Interchange`)
- L26 _prototype_ `AActor* GetSpawnedParentActor(const UInterchangeBaseNodeContainer* NodeContainer, const UInterchangeActorFactoryNode* FactoryNode);` (scope `UE::Interchange::ActorHelper`) — Returns the parent actor of the actor described by the FactoryNode using the node hierarchy.
- L32 _prototype_ `AActor* SpawnFactoryActor(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams, FText& OutReason);` (scope `UE::Interchange::ActorHelper`) — Spawns and return a AAActor using the given SceneObjectsParam. The actor's parent will be determine by the node hierarchy and its type by the factory node's ObjectClass.
- L33 _prototype_ `AActor* SpawnFactoryActor(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams);` (scope `UE::Interchange::ActorHelper`)
- L38 _prototype_ `const UInterchangeFactoryBaseNode* FindAssetInstanceFactoryNode(const UInterchangeBaseNodeContainer* NodeContainer, const UInterchangeFactoryBaseNode* ActorFactoryNode);` (scope `UE::Interchange::ActorHelper`) — Returns the factory node of the asset instanced by ActorFactoryNode.
- L46 _prototype_ `void ApplySlotMaterialDependencies(const UInterchangeBaseNodeContainer& NodeContainer, const UInterchangeMeshActorFactoryNode& ActorFactoryNode, UMeshComponent& MeshComponent, const UInterchangeMeshActorFactoryNode* PreviousActorFactoryNode = nullptr);` (scope `UE::Interchange::ActorHelper`) — Applies material slot dependencies stored in ActorFactoryNode to MeshComponent. In case of a reimport, PreviousActorFactoryNode is used to determine which slots should be updated according to the requested import strategy associated with ActorFactoryNode, i.e. do nothing, apply imported slots, apply imported slots while preserving changes made after the last import or reimport.
- L52 _prototype_ `void ApplyAllCustomAttributes(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams, UObject& ObjectToUpdate);` (scope `UE::Interchange::ActorHelper`) — Applies custom attributes from to ObjectToUpdate based on content of CreateSceneObjectsParams Reimport policies will be applied if applicable
- L57 _prototype_ `void AddInterchangeAssetUserDataToActor(AActor* Actor, const UInterchangeSceneImportAsset* SceneImportAsset, const UInterchangeFactoryBaseNode* FactoryNode);` (scope `UE::Interchange::ActorHelper`) — Adds metadata to Actor via UInterchangeAssetUserData
- L62 _prototype_ `void AddInterchangeLevelAssetUserDataToWorld(UWorld* World, const UInterchangeSceneImportAsset* SceneImportAsset);` (scope `UE::Interchange::ActorHelper`) — Adds metadata to Actor via UInterchangeAssetUserData

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeCameraActorFactory.h` (Public)


#### class `UInterchangeCineCameraActorFactory`  
`class UInterchangeCineCameraActorFactory : public UInterchangeActorFactory`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L23 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L31 _public prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`
- L33 _public prototype_ `virtual void ApplyAllCustomAttributesToObject(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams, AActor& SpawnedActor, UObject* ObjectToUpdate) override;`

#### class `UInterchangeCameraActorFactory`  
`class UInterchangeCameraActorFactory : public UInterchangeActorFactory`  
_L40-61_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L48 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L56 _public prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`
- L58 _public prototype_ `virtual void ApplyAllCustomAttributesToObject(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams, AActor& SpawnedActor, UObject* ObjectToUpdate) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeDecalActorFactory.h` (Public)


#### class `UInterchangeDecalActorFactory`  
`class UInterchangeDecalActorFactory : public UInterchangeActorFactory`  
_L14-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L22 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L30 _public prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeGeometryCacheActorFactory.h` (Public)


#### class `UInterchangeGeometryCacheActorFactory`  
`class UInterchangeGeometryCacheActorFactory : public UInterchangeActorFactory`  
_L21-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L29 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L31 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L33 _public prototype_ `virtual UObject* ImportSceneObject_GameThread(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams) override;`
- L42 _protected prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`
- L45 _protected prototype_ `virtual void ExecuteResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject) override;`
- L52 _private prototype_ `void ApplyGeometryCacheToComponent(const UInterchangeFactoryBaseNode* MeshNode, UGeometryCacheComponent* GeometryCacheComponent, const UInterchangeBaseNodeContainer& NodeContainer, const UInterchangeMeshActorFactoryNode* MeshFactoryNode);` — Helper function to assign a static mesh to its component while checking for other settings like navigation bounds and material dependencies.
- L56 _private member_ `const UInterchangeFactoryBaseNode* PreviousFactoryNode = nullptr;` — Cache the previous factory node passed in the FImportSceneObjectsParams struct PreviousFactoryNode will be used to respect requested reimport's strategy when updating material slots

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeHeterogeneousVolumeActorFactory.h` (Public)


#### class `UInterchangeHeterogeneousVolumeActorFactory`  
`class UInterchangeHeterogeneousVolumeActorFactory : public UInterchangeActorFactory`  
_L12-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L20 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L29 _protected prototype_ `virtual UObject* ProcessActor( class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeLevelFactory.h` (Public)


#### class `UInterchangeLevelFactory`  
`class UInterchangeLevelFactory : public UInterchangeFactoryBase`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental)`
- inherits: `UInterchangeFactoryBase`
- L23 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L24 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L25 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L26 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L28 _public prototype_ `virtual UObject* GetObjectToReimport(UObject* ReimportObject, const UInterchangeFactoryBaseNode& FactoryNode, const FString& PackageName, const FString& AssetName, const FString& SubPathString) override;` — For a level reimport, returns the level created on the previous import if found

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeLevelInstanceActorFactory.h` (Public)


#### class `UInterchangeLevelInstanceActorFactory`  
`class UInterchangeLevelInstanceActorFactory : public UInterchangeActorFactory`  
_L19-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L27 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L28 _public prototype_ `virtual UObject* ImportSceneObject_GameThread(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams) override;`
- L30 _public prototype_ `virtual UObject* GetObjectToReimport(UObject* ReimportObject, const UInterchangeFactoryBaseNode& FactoryNode, const FString& PackageName, const FString& AssetName, const FString& SubPathString) override;` — For a level reimport, returns the LevelInstance actor created on the previous import if found

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeLightActorFactory.h` (Public)


#### class `UInterchangeLightActorFactory`  
`class UInterchangeLightActorFactory : public UInterchangeActorFactory`  
_L12-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L20 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L29 _protected prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeSceneImportAssetFactory.h` (Public)


#### class `UInterchangeSceneImportAssetFactory`  
`class UInterchangeSceneImportAssetFactory : public UInterchangeFactoryBase`  
_L15-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L23 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L25 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L27 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L28 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L29 _public prototype_ `virtual void FinalizeObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L30 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L31 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L32 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L33 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L34 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeSceneVariantSetsFactory.h` (Public)


#### class `UInterchangeSceneVariantSetsFactory`  
`class UInterchangeSceneVariantSetsFactory : public UInterchangeFactoryBase`  
_L20-40_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L28 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L29 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L31 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L32 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L38 _private prototype_ `UObject* ImportObjectSourceData(const FImportAssetObjectParams& Arguments, ULevelVariantSets* LevelVariantSets);`
- L39 _private member_ `const UInterchangeTranslatorBase* Translator = nullptr;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeSkeletalMeshActorFactory.h` (Public)


#### class `UInterchangeSkeletalMeshActorFactory`  
`class UInterchangeSkeletalMeshActorFactory : public UInterchangeActorFactory`  
_L19-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L27 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L29 _public function_ `virtual UObject* ImportSceneObject_GameThread(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams) override`
- L36 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L45 _protected prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`
- L47 _protected prototype_ `virtual void ExecuteResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject) override;`
- L53 _protected member_ `const UInterchangeFactoryBaseNode* PreviousFactoryNode = nullptr;` — Cache the previous factory node passed in the FImportSceneObjectsParams struct PreviousFactoryNode will be used to respect requested reimport's strategy when updating material slots

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeSkyLightActorFactory.h` (Public)


#### class `UInterchangeSkyLightActorFactory`  
`class UInterchangeSkyLightActorFactory : public UInterchangeActorFactory`  
_L12-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L17 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L18 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L21 _protected prototype_ `virtual UObject* ProcessActor( class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeStaticMeshActorFactory.h` (Public)


#### class `UInterchangeStaticMeshActorFactory`  
`class UInterchangeStaticMeshActorFactory : public UInterchangeActorFactory`  
_L21-62_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactory`
- L29 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L31 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L33 _public function_ `virtual UObject* ImportSceneObject_GameThread(const UInterchangeFactoryBase::FImportSceneObjectsParams& CreateSceneObjectsParams) override`
- L47 _protected prototype_ `virtual UObject* ProcessActor(class AActor& SpawnedActor, const UInterchangeActorFactoryNode& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer, const FImportSceneObjectsParams& Params) override;`
- L50 _protected prototype_ `virtual void ExecuteResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject) override;`
- L57 _private prototype_ `void ApplyStaticMeshToComponent(const UInterchangeFactoryBaseNode* MeshNode, UStaticMeshComponent* StaticMeshComponent, const UInterchangeBaseNodeContainer& NodeContainer, const UInterchangeMeshActorFactoryNode* MeshFactoryNode);` — Helper function to assign a static mesh to its component while checking for other settings like navigation bounds and material dependencies.
- L61 _private member_ `const UInterchangeFactoryBaseNode* PreviousFactoryNode = nullptr;` — Cache the previous factory node passed in the FImportSceneObjectsParams struct PreviousFactoryNode will be used to respect requested reimport's strategy when updating material slots

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Scene/InterchangeVariantSetPayloadInterface.h` (Public)


#### enum `UE::Interchange::EVariantPropertyCaptureCategory`  
`enum class EVariantPropertyCaptureCategory : uint16`  
_L16-27_
- L18 _public enumerator_ `Undefined = 0x0000`
- L19 _public enumerator_ `Generic = 0x0001`
- L20 _public enumerator_ `RelativeLocation = 0x0002`
- L21 _public enumerator_ `RelativeRotation = 0x0004`
- L22 _public enumerator_ `RelativeScale3D = 0x0008`
- L23 _public enumerator_ `Visibility = 0x0010`
- L24 _public enumerator_ `Material = 0x0020`
- L25 _public enumerator_ `Color = 0x0040`
- L26 _public enumerator_ `Option = 0x0080`

#### struct `UE::Interchange::FVariantPropertyCaptureData`  
`struct FVariantPropertyCaptureData`  
_L30-36_
- L32 _public member_ `FString PropertyPath;`
- L33 _public member_ `EVariantPropertyCaptureCategory Category = EVariantPropertyCaptureCategory::Undefined;`
- L34 _public member_ `TOptional<TArray<uint8>> Buffer;`
- L35 _public member_ `TOptional<FString> ObjectUid;`

#### struct `UE::Interchange::FVariantBinding`  
`struct FVariantBinding`  
_L38-42_
- L40 _public member_ `FString TargetUid;`
- L41 _public member_ `TArray<FVariantPropertyCaptureData> Captures;`

#### struct `UE::Interchange::FVariant`  
`struct FVariant`  
_L44-48_
- L46 _public member_ `FString DisplayText;`
- L47 _public member_ `TArray<FVariantBinding> Bindings;`

#### struct `UE::Interchange::FVariantSetPayloadData`  
`struct FVariantSetPayloadData`  
_L50-53_
- L52 _public member_ `TArray<FVariant> Variants;`

#### class `UInterchangeVariantSetPayloadInterface`  
`class UInterchangeVariantSetPayloadInterface : public UInterface`  
_L57-60_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeVariantSetPayloadInterface`  
`class IInterchangeVariantSetPayloadInterface`  
_L65-78_
- desc: VariantSet payload interface. Derive from this interface if your payload can import Variant's data
- L77 _public prototype_ `virtual TOptional<UE::Interchange::FVariantSetPayloadData> GetVariantSetPayloadData(const FString& PayloadKey) const = 0;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @return a PayloadData containing the the data ask with the key.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/SpecularProfile/InterchangeSpecularProfileFactory.h` (Public)


#### class `UInterchangeSpecularProfileFactory`  
`class UInterchangeSpecularProfileFactory : public UInterchangeFactoryBase`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L18 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L19 _public prototype_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override;`
- L20 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeBlockedTexturePayloadData.h` (Public)


#### struct `UE::Interchange::FImportBlockedImage`  
`struct FImportBlockedImage`  
_L18-44_
- desc: Also known as a UDIMs texture
- L20 _public member_ `FUniqueBuffer RawData;`
- L21 _public member_ `TArray<FTextureSourceBlock> BlocksData;`
- L23 _public member_ `ETextureSourceFormat Format = TSF_Invalid;`
- L24 _public member_ `TextureCompressionSettings CompressionSettings = TC_Default;`
- L25 _public member_ `bool bSRGB = true;`
- L26 _public member_ `TOptional<TextureMipGenSettings> MipGenSettings;`
- L27 _public member_ `TOptional<FTextureCreatorApplicationMetadata> TextureCreatorApplicationMetadata;`
- L29 _public prototype_ `int64 ComputeBufferSize() const;`
- L30 _public prototype_ `bool IsValid() const;`
- L33 _public prototype_ `bool InitDataSharedAmongBlocks(const FImportImage& Image);`
- L38 _public prototype_ `bool InitBlockFromImage(int32 BlockX, int32 BlockY, const FImportImage& Image);` — Everything except the RawData and BlocksData must be initialized before calling this function
- L43 _public prototype_ `bool MigrateDataFromImagesToRawData(TArray<FImportImage>& Images);` — Everything except the RawData must be initialized before calling this function

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeBlockedTexturePayloadInterface.h` (Public)


#### class `UInterchangeBlockedTexturePayloadInterface`  
`class UInterchangeBlockedTexturePayloadInterface : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeBlockedTexturePayloadInterface`  
`class IInterchangeBlockedTexturePayloadInterface`  
_L25-46_
- desc: Blocked Texture payload interface (Also know as UDIM(s)). Derive from it if your payload can import blocked/UDIMs texture
- L31 _public function_ `virtual TOptional<UE::Interchange::FImportBlockedImage> GetBlockedTexturePayloadData(const UInterchangeSourceData* PayloadSourceData, const FString& PayloadKey)` — `UE_DEPRECATED(5.3, "Deprecated. Use GetBlockedTexturePayloadData(const FString&, TOptional<FString>&) instead.")`
- L45 _public function_ `virtual TOptional<UE::Interchange::FImportBlockedImage> GetBlockedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @param AlternateTexturePath - When applicable, set to the path of the file actually loaded to create the FImportImage. @return a PayloadData containing the import blocked image data. The TOptional will not be set if there is an error.

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeDDSTranslator.h` (Public)


#### class `UInterchangeDDSTranslator`  
`class UInterchangeDDSTranslator : public UInterchangeTranslatorBase, public IInterchangeTexturePayloadInterface, public IInterchangeSlicedTexturePayloadInterface`  
_L20-69_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface,IInterchangeSlicedTexturePayloadInterface`
- L25 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L26 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L31 _public prototype_ `virtual bool CanImportSourceData(const UInterchangeSourceData* InSourceData) const override;` — return true if the translator can translate the specified source data.
- L39 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L51 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L66 _public prototype_ `virtual TOptional<UE::Interchange::FImportSlicedImage> GetSlicedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeIESTranslator.h` (Public)


#### class `UInterchangeIESTranslator`  
`class UInterchangeIESTranslator : public UInterchangeTranslatorBase, public IInterchangeTextureLightProfilePayloadInterface`  
_L18-50_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTextureLightProfilePayloadInterface`
- L23 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L24 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L32 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L45 _public prototype_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import light profile data. The TOptional will not be set if there is an error.
- L47 _public prototype_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const uint8* Buffer, uint32 BufferLength) const override;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeImageWrapperTranslator.h` (Public)


#### class `UInterchangeImageWrapperTranslator`  
`class UInterchangeImageWrapperTranslator : public UInterchangeTranslatorBase, public IInterchangeTexturePayloadInterface`  
_L22-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface`
- desc: A translator for most of the image wrapper supported formats
- L26 _public prototype_ `UInterchangeImageWrapperTranslator();`
- L28 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L30 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L38 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L50 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L54 _public prototype_ `TOptional<UE::Interchange::FImportImage> GetTexturePayloadDataFromBuffer(const TArray64<uint8>& SourceDataBuffer) const;`
- L57 _private member_ `ETextureImportPNGInfill PNGInfill;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeJPGTranslator.h` (Public)


#### class `UInterchangeJPGTranslator`  
`class UInterchangeJPGTranslator : public UInterchangeTranslatorBase, public IInterchangeTexturePayloadInterface`  
_L18-63_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface`
- L23 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L24 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L32 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L44 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L46 _public prototype_ `virtual bool SupportCompressedTexturePayloadData() const override;`
- L56 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetCompressedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L62 _private prototype_ `TOptional<UE::Interchange::FImportImage> GetTexturePayloadImplementation(TArray64<uint8>&& SourceDataBuffer, bool bShouldImportRaw) const;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangePSDTranslator.h` (Public)


#### class `UInterchangePSDTranslator`  
`class UInterchangePSDTranslator : public UInterchangeTranslatorBase, public IInterchangeTexturePayloadInterface`  
_L18-47_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface`
- L23 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L24 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L32 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L44 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeSlicedTexturePayloadData.h` (Public)


#### struct `UE::Interchange::FImportSlicedImage`  
`struct FImportSlicedImage : public FImportImage`  
_L14-29_
- inherits: `FImportImage`
- L16 _public member_ `int32 NumSlice = 0;`
- L17 _public member_ `bool bIsVolume = false;`
- L19 _public prototype_ `void Init(int32 InSizeX, int32 InSizeY, int32 InNumSlice, int32 InNumMips, ETextureSourceFormat InFormat, bool InSRGB);`
- L20 _public prototype_ `void InitVolume(int32 InSizeX, int32 InSizeY, int32 InNumSlice, int32 InNumMips, ETextureSourceFormat InFormat, bool InSRGB);`
- L22 _public prototype_ `const uint8* GetMipData(int32 InMipIndex, int32 InSliceIndex = INDEX_NONE) const;`
- L23 _public prototype_ `uint8* GetMipData(int32 InMipIndex, int32 InSliceIndex = INDEX_NONE);`
- L25 _public prototype_ `virtual int64 GetMipSize(int32 InMipIndex) const override;`
- L26 _public prototype_ `virtual int64 ComputeBufferSize() const override;`
- L28 _public prototype_ `virtual bool IsValid() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeSlicedTexturePayloadInterface.h` (Public)


#### class `UInterchangeSlicedTexturePayloadInterface`  
`class UInterchangeSlicedTexturePayloadInterface : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeSlicedTexturePayloadInterface`  
`class IInterchangeSlicedTexturePayloadInterface`  
_L23-44_
- desc: Texture payload interface. Derive from it if your payload can import texture
- L29 _public function_ `virtual TOptional<UE::Interchange::FImportSlicedImage> GetSlicedTexturePayloadData(const UInterchangeSourceData* SourceData, const FString& PayloadKey) const` — `UE_DEPRECATED(5.3, "Deprecated. Use GetSlicedTexturePayloadData(const FString&, TOptional<FString>&) instead.")`
- L43 _public prototype_ `virtual TOptional<UE::Interchange::FImportSlicedImage> GetSlicedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const PURE_VIRTUAL(IInterchangeSlicedTexturePayloadInterface::GetSlicedTexturePayloadData, return{};);` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @param AlternateTexturePath - When applicable, set to the path of the file actually loaded to create the FImportImage. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeTextureFactory.h` (Public)


#### struct `UE::Interchange::Private::InterchangeTextureFactory::FProcessedPayload`  
`struct FProcessedPayload`  
_L32-47_
- L34 _public prototype_ `FProcessedPayload() = default;`
- L35 _public prototype_ `FProcessedPayload(FProcessedPayload&&) = default;`
- L36 _public prototype_ `FProcessedPayload& operator=(FProcessedPayload&&) = default;`
- L38 _public prototype_ `FProcessedPayload(const FProcessedPayload&) = delete;`
- L39 _public prototype_ `FProcessedPayload& operator=(const FProcessedPayload&) = delete;`
- L41 _public prototype_ `FProcessedPayload& operator=(UE::Interchange::Private::InterchangeTextureFactory::FTexturePayloadVariant&& InPayloadVariant);`
- L43 _public prototype_ `bool IsValid() const;`
- L45 _public member_ `UE::Interchange::Private::InterchangeTextureFactory::FTexturePayloadVariant SettingsFromPayload;`
- L46 _public member_ `UE::Serialization::FEditorBulkData::FSharedBufferWithID PayloadAndId;`

#### class `UInterchangeTextureFactory`  
`class UInterchangeTextureFactory : public UInterchangeFactoryBase`  
_L51-93_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L59 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L60 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L61 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L62 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L63 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L64 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L65 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L66 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L67 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L68 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L69 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L78 _private prototype_ `void CheckForInvalidResolutions(UE::Interchange::Private::InterchangeTextureFactory::FTexturePayloadVariant& InPayloadVariant, const UInterchangeSourceData* SourceData, const UInterchangeTextureFactoryNode* TextureFactoryNode);` — Check for any invalid resolutions and remove those from the payload
- L80 _private member_ `UE::Interchange::Private::InterchangeTextureFactory::FProcessedPayload ProcessedPayload;`
- L81 _private member_ `TOptional<FString> AlternateTexturePath;`
- L85 _private member_ `TArray<FAssetImportInfo::FSourceFile> SourceFiles;` — The data for the source files will be stored here during the import
- L89 _private member_ `bool bSkipImport = false;` — If we import without a pure texture translator, we should not override an existing texture and we must skip the import. See the implementation of BeginImportAssetObject_GameThread function.
- L92 _private member_ `bool bCreatedAsset = false;` — This is set to true if the factory itself called NewObject and created the texture asset referenced by the factory node

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Interchange` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L24 _namespace_ `namespace InterchangeTextureFactory` (scope `UE::Interchange::Private`)
- L26 _typedef_ `using FTexturePayloadVariant = TVariant<FEmptyVariantState , TOptional<FImportImage> , TOptional<FImportBlockedImage> , TOptional<FImportSlicedImage> , TOptional<FImportLightProfile>>;` (scope `UE::Interchange::Private::InterchangeTextureFactory`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeTextureLightProfilePayloadData.h` (Public)


#### struct `UE::Interchange::FImportLightProfile`  
`struct FImportLightProfile : public FImportImage`  
_L9-16_
- inherits: `FImportImage`
- L11 _public member_ `float Brightness = 0.0f;`
- L13 _public member_ `float TextureMultiplier = 0.0f;`
- L15 _public member_ `TArray64<uint8> SourceDataBuffer;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeTextureLightProfilePayloadInterface.h` (Public)


#### class `UInterchangeTextureLightProfilePayloadInterface`  
`class UInterchangeTextureLightProfilePayloadInterface : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeTextureLightProfilePayloadInterface`  
`class IInterchangeTextureLightProfilePayloadInterface`  
_L23-49_
- desc: Texture payload interface. Derive from it if your payload can import texture
- L29 _public function_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const UInterchangeSourceData* SourceData, const FString& PayloadKey) const` — `UE_DEPRECATED(5.3, "Deprecated. Use GetLightProfilePayloadData(const FString&, TOptional<FString>&) instead.")`
- L43 _public prototype_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const PURE_VIRTUAL(IInterchangeTextureLightProfilePayloadInterface::GetLightProfilePayloadData, return{};);` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @param AlternateTexturePath - When applicable, set to the path of the file actually loaded to create the FImportImage. @return a PayloadData containing the import light profile data. The TOptional will not be set if there is an error.
- L48 _public function_ `virtual TOptional<UE::Interchange::FImportLightProfile> GetLightProfilePayloadData(const uint8* Buffer, uint32 BufferLength) const` — IESTranslator uses this, but we also expose it here in case otrher translators want to use directly.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeTexturePayloadData.h` (Public)


#### struct `UE::Interchange::FTextureCreatorApplicationMetadata`  
`struct FTextureCreatorApplicationMetadata`  
_L16-21_
- L18 _public member_ `FString ApplicationVendor;`
- L19 _public member_ `FString ApplicationName;`
- L20 _public member_ `FString ApplicationVersion;`

#### struct `UE::Interchange::FImportImage`  
`struct FImportImage`  
_L23-55_
- L25 _public prototype_ `virtual ~FImportImage() = default;`
- L26 _public prototype_ `FImportImage() = default;`
- L27 _public prototype_ `FImportImage(FImportImage&&) = default;`
- L28 _public prototype_ `FImportImage& operator=(FImportImage&&) = default;`
- L30 _public prototype_ `FImportImage(const FImportImage&) = delete;`
- L31 _public prototype_ `FImportImage& operator=(const FImportImage&) = delete;`
- L33 _public member_ `FUniqueBuffer RawData;`
- L36 _public member_ `ETextureSourceCompressionFormat RawDataCompressionFormat = TSCF_None;` — Which compression format (if any) that is applied to RawData
- L38 _public member_ `ETextureSourceFormat Format = TSF_Invalid;`
- L39 _public member_ `TextureCompressionSettings CompressionSettings = TC_Default;`
- L40 _public member_ `int32 NumMips = 0;`
- L41 _public member_ `int32 SizeX = 0;`
- L42 _public member_ `int32 SizeY = 0;`
- L43 _public member_ `bool bSRGB = true;`
- L44 _public member_ `TOptional<TextureMipGenSettings> MipGenSettings;`
- L45 _public member_ `TOptional<FTextureCreatorApplicationMetadata> TextureCreatorApplicationMetadata;`
- L47 _public prototype_ `void Init2DWithParams(int32 InSizeX, int32 InSizeY, ETextureSourceFormat InFormat, bool bInSRGB, bool bShouldAllocateRawData = true);`
- L48 _public prototype_ `void Init2DWithParams(int32 InSizeX, int32 InSizeY, int32 InNumMips, ETextureSourceFormat InFormat, bool bInSRGB, bool bShouldAllocateRawData = true);`
- L50 _public prototype_ `virtual int64 GetMipSize(int32 InMipIndex) const;`
- L51 _public prototype_ `virtual int64 ComputeBufferSize() const;`
- L53 _public prototype_ `TArrayView64<uint8> GetArrayViewOfRawData();`
- L54 _public prototype_ `virtual bool IsValid() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeTexturePayloadInterface.h` (Public)


#### class `UInterchangeTexturePayloadInterface`  
`class UInterchangeTexturePayloadInterface : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeTexturePayloadInterface`  
`class IInterchangeTexturePayloadInterface`  
_L23-66_
- desc: Texture payload interface. Derive from it if your payload can import texture
- L29 _public function_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const UInterchangeSourceData* PayloadSourceData, const FString& PayloadKey) const` — `UE_DEPRECATED(5.3, "Deprecated. Use GetTexturePayloadData(const FString&, TOptional<FString>&) instead.")`
- L43 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const PURE_VIRTUAL(IInterchangeTexturePayloadInterface::GetTexturePayloadData, return{};);` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @param AlternateTexturePath - When applicable, set to the path of the file actually loaded to create the FImportImage. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L48 _public function_ `virtual bool SupportCompressedTexturePayloadData() const` — Does this translator support the request for a compressed source data?
- L51 _public function_ `virtual TOptional<UE::Interchange::FImportImage> GetCompressedTexturePayloadData(const UInterchangeSourceData* PayloadSourceData, const FString& PayloadKey)` — `UE_DEPRECATED(5.3, "Deprecated. Use GetCompressedTexturePayloadData(const FString&, TOptional<FString>&) instead.")`
- L65 _public function_ `virtual TOptional<UE::Interchange::FImportImage> GetCompressedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - The key to retrieve the a particular payload contain into the specified source data. @param AlternateTexturePath - When applicable, set to the path of the file actually loaded to create the FImportImage. @return a PayloadData containing the import image data with image data being the original file format generally. The TOptional will not be set if there is an error.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Texture/InterchangeUEJPEGTranslator.h` (Public)


#### class `UInterchangeUEJPEGTranslator`  
`class UInterchangeUEJPEGTranslator : public UInterchangeTranslatorBase, public IInterchangeTexturePayloadInterface`  
_L18-63_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTranslatorBase,IInterchangeTexturePayloadInterface`
- L23 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const override;`
- L24 _public function_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const override`
- L32 _public prototype_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const override;` — Translate the associated source data into a node hold by the specified nodes container. @param BaseNodeContainer - The unreal objects descriptions container where to put the translated source data. @return true if the translator can translate the source data, false otherwise.
- L44 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L46 _public prototype_ `virtual bool SupportCompressedTexturePayloadData() const override;`
- L56 _public prototype_ `virtual TOptional<UE::Interchange::FImportImage> GetCompressedTexturePayloadData(const FString& PayloadKey, TOptional<FString>& AlternateTexturePath) const override;` — Once the translation is done, the import process need a way to retrieve payload data. This payload will be use by the factories to create the asset. @param PayloadKey - Unused. The translator uses its SourceData property to extract the payload. @param AlternateTexturePath - Unused. The translator uses its SourceData property to extract the payload. @return a PayloadData containing the import image data. The TOptional will not be set if there is an error.
- L62 _private prototype_ `TOptional<UE::Interchange::FImportImage> GetTexturePayloadImplementation(TArray64<uint8>&& SourceDataBuffer, bool bShouldImportRaw) const;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEIMPORT_API`

### `Plugins/Interchange/Runtime/Source/Import/Public/Volume/InterchangeSparseVolumeTextureFactory.h` (Public)


#### struct `FVolumePayload`  
`struct FVolumePayload`  
_L25-30_
- L27 _public member_ `FString VolumeNodeUid;`
- L28 _public member_ `TArray<int32> PayloadFrameIndices;`
- L29 _public member_ `TOptional<UE::Interchange::FVolumePayloadData> PayloadData;`

#### class `UInterchangeSparseVolumeTextureFactory`  
`class UInterchangeSparseVolumeTextureFactory : public UInterchangeFactoryBase`  
_L33-71_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L39 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L40 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L44 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L45 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments) override;`
- L46 _public prototype_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L47 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L48 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L49 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L50 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L51 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L52 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L56 _private prototype_ `bool HasValidPayloads() const;`
- L62 _private member_ `TArray<FAssetImportInfo::FSourceFile> SourceFiles;` — The data for the source files will be collecetd here during the import during an async task, and later be added to AssetImportData
- L66 _private member_ `TArray<FVolumePayload> ProcessedPayloads;` — Where we retain the processed payloads between the different factory interface function calls
- L70 _private member_ `bool bSkipImport = false;` — We turn this to true when we run into an existing asset that we shouldn't overwrite/modify (e.g. when reimporting some other asset type, like reimporting a material and finding an existing SVT that it wants to use)

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API INTERCHANGEIMPORT_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Volume/InterchangeVolumePayloadData.h` (Public)


#### struct `UE::Interchange::FVolumePayloadData`  
`struct FVolumePayloadData`  
_L11-24_
- desc: Contains everything we need to use as source data for a SparseVolumeTexture asset
- L13 _public prototype_ `virtual ~FVolumePayloadData() = default;`
- L14 _public prototype_ `FVolumePayloadData() = default;`
- L15 _public prototype_ `FVolumePayloadData(FVolumePayloadData&&) = default;`
- L16 _public prototype_ `FVolumePayloadData& operator=(FVolumePayloadData&&) = default;`
- L18 _public prototype_ `FVolumePayloadData(const FVolumePayloadData&) = delete;`
- L19 _public prototype_ `FVolumePayloadData& operator=(const FVolumePayloadData&) = delete;`
- L22 _public member_ `UE::SVT::FTextureData TextureData;`
- L23 _public member_ `FTransform Transform;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Volume/InterchangeVolumePayloadInterface.h` (Public)


#### class `UInterchangeVolumePayloadInterface`  
`class UInterchangeVolumePayloadInterface : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IInterchangeVolumePayloadInterface`  
`class IInterchangeVolumePayloadInterface`  
_L23-32_
- desc: Payload interface for volume data (e.g. OpenVDB)
- L28 _public function_ `virtual TOptional<UE::Interchange::FVolumePayloadData> GetVolumePayloadData(const UE::Interchange::FVolumePayloadKey& PayloadKey) const`

### `Plugins/Interchange/Runtime/Source/Import/Public/Volume/InterchangeVolumePayloadKey.h` (Public)


#### struct `UE::Interchange::FVolumePayloadKey`  
`struct FVolumePayloadKey`  
_L11-16_
- desc: Contains everything we need to query a factory for some FVolumePayloadData
- L13 _public member_ `FString FileName;`
- L14 _public member_ `Volume::FAssignmentInfo AssignmentInfo;`
- L15 _public member_ `FIntVector3 VolumeBoundsMin;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Import/Public/Volume/InterchangeVolumeTranslatorSettings.h` (Public)


#### class `UInterchangeVolumeTranslatorSettings`  
`class UInterchangeVolumeTranslatorSettings : public UInterchangeTranslatorSettings`  
_L11-32_
- reflection: `UCLASS(BlueprintType, editinlinenew, MinimalAPI)`
- inherits: `UInterchangeTranslatorSettings`
- L23 _public member_ `bool bTranslateAdjacentNumberedFiles = true;` — `UPROPERTY(EditAnywhere, Category = "OpenVDB Translator")` — Whether we should search the same folder of the translated file for other .vdb files whose file names differ from it only by a numbered suffix (e.g. "Tornado_0001.vdb, Tornado_0002.vdb, etc.), and translate those too. This is useful if you intend on importing an animated SparseVolumeTexture.
- L31 _public member_ `FString AnimationID;` — `UPROPERTY()` — Identifier set on the generated volume nodes (via SetCustomAnimationID) if they are part of an animation, to identify said animation. Volume nodes that share the same AnimationID belong to the same volume animation. This can be left empty to have an ID automatically generated, or can be set to something to force it to that value.
