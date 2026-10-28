# Plugins / DynamicMaterialTextureSet

- module root: `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSet`
- headers: 4; symbols: 42
- symbol kinds: class=1, enum=2, enumerator=25, macro=1, member=3, prototype=9, struct=1
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject, Engine

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSet/Public/DMMaterialTexture.h` (Public)


#### struct `FDMMaterialTexture`  
`struct FDMMaterialTexture`  
_L13-22_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `TSoftObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Designer")`
- L21 _public member_ `EDMTextureChannelMask TextureChannel = EDMTextureChannelMask::RGBA;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSet/Public/DMTextureChannelMask.h` (Public)


#### enum `EDMTextureChannelMask`  
`enum class EDMTextureChannelMask : uint8`  
_L10-19_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L13 _public enumerator_ `Red = 1 << 0`
- L14 _public enumerator_ `Green = 1 << 1`
- L15 _public enumerator_ `Blue = 1 << 2`
- L16 _public enumerator_ `Alpha = 1 << 3`
- L17 _public enumerator_ `RGB = Red|Green|Blue`
- L18 _public enumerator_ `RGBA = Red|Green|Blue|Alpha`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSet/Public/DMTextureSet.h` (Public)


#### class `UDMTextureSet`  
`class UDMTextureSet : public UObject`  
_L18-86_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UObject`
- L23 _public prototype_ `UDMTextureSet();`
- L25 _public prototype_ `virtual ~UDMTextureSet() override = default;`
- L34 _public prototype_ `bool HasMaterialProperty(EDMTextureSetMaterialProperty InMaterialProperty) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Checks whether a given Material Property exists in the Texture Map. Does not check whether that a Texture is assigned to it. @param InMaterialProperty The Material Property to check. @return True if the property exists in the Texture Map.
- L39 _public prototype_ `const TMap<EDMTextureSetMaterialProperty, FDMMaterialTexture>& GetTextures() const;` — @return Gets the entire Texture Map.
- L47 _public prototype_ `bool HasMaterialTexture(EDMTextureSetMaterialProperty InMaterialProperty) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Checks whether a given Material Property has a Texture assigned to it. @param InMaterialProperty The Material Property to check. @return True if the Material Property has an assigned Texture.
- L57 _public prototype_ `bool GetMaterialTexture(EDMTextureSetMaterialProperty InMaterialProperty, FDMMaterialTexture& OutMaterialTexture) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Gets the Material Texture associated with a Material Property. Does not check whether a Texture is assigned to it. @param InMaterialProperty The Material Property to check. @param OutMaterialTexture The found Material Texture. @return True if the Material Property exists within the Texture Map.
- L65 _public prototype_ `const FDMMaterialTexture* GetMaterialTexture(EDMTextureSetMaterialProperty InMaterialProperty) const;` — Gets the Material Texture associated with a Material Property. Does not check whether a Texture is assigned to it. @param InMaterialProperty The Material Property to check. @return A pointer to the found Material Texture, if it exists, or nullptr.
- L73 _public prototype_ `void SetMaterialTexture(EDMTextureSetMaterialProperty InMaterialProperty, const FDMMaterialTexture& InMaterialTexture);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the Material Texture for a given Material Property. Can be used to unset Textures. @param InMaterialProperty The Material Property to check. @param InMaterialTexture The Material Texture to set on the given Material Property.
- L81 _public prototype_ `bool ContainsTexture(UTexture* InTexture) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Checks the Texture Map to see if a given Texture exists within it. @param InTexture The Texture to search for. @return True if the Texture exits in the Texture Map.
- L85 _protected member_ `TMap<EDMTextureSetMaterialProperty, FDMMaterialTexture> Textures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Designer", EditFixedSize, meta = (ReadOnlyKeys, AllowPrivateAccess))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DYNAMICMATERIALTEXTURESET_API`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSet/Public/DMTextureSetMaterialProperty.h` (Public)


#### enum `EDMTextureSetMaterialProperty`  
`enum class EDMTextureSetMaterialProperty : uint8`  
_L15-38_
- reflection: `UENUM(BlueprintType)`
- desc: Copying the values from EMaterialProperty to change required meta data, such as DisplayName and Hidden.
- L17 _public enumerator_ `BaseColor = EMaterialProperty::MP_BaseColor`
- L18 _public enumerator_ `Normal = EMaterialProperty::MP_Normal`
- L19 _public enumerator_ `Metallic = EMaterialProperty::MP_Metallic`
- L20 _public enumerator_ `Roughness = EMaterialProperty::MP_Roughness`
- L21 _public enumerator_ `AmbientOcclusion = EMaterialProperty::MP_AmbientOcclusion`
- L22 _public enumerator_ `Displacement = EMaterialProperty::MP_Displacement`
- L23 _public enumerator_ `Specular = EMaterialProperty::MP_Specular`
- L24 _public enumerator_ `SubsurfaceColor = EMaterialProperty::MP_SubsurfaceColor`
- L26 _public enumerator_ `EmissiveColor = EMaterialProperty::MP_EmissiveColor`
- L27 _public enumerator_ `Opacity = EMaterialProperty::MP_Opacity`
- L28 _public enumerator_ `OpacityMask = EMaterialProperty::MP_OpacityMask`
- L29 _public enumerator_ `Anisotropy = EMaterialProperty::MP_Anisotropy`
- L30 _public enumerator_ `Refraction = EMaterialProperty::MP_Refraction`
- L31 _public enumerator_ `Tangent = EMaterialProperty::MP_Tangent`
- L32 _public enumerator_ `WorldPositionOffset = EMaterialProperty::MP_WorldPositionOffset`
- L33 _public enumerator_ `PixelDepthOffset = EMaterialProperty::MP_PixelDepthOffset`
- L35 _public enumerator_ `SurfaceThickness = EMaterialProperty::MP_SurfaceThickness`
- L37 _public enumerator_ `None = EMaterialProperty::MP_MAX UMETA(Hidden)`
