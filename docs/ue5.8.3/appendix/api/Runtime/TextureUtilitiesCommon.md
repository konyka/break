# Runtime / TextureUtilitiesCommon

- module root: `Source/Runtime/TextureUtilitiesCommon`
- headers: 6; symbols: 60
- symbol kinds: class=2, enum=2, enumerator=8, member=8, namespace=13, prototype=22, variable=5
- PrivateDependencyModuleNames: CoreUObject, ImageCore, Slate, SlateCore, TextureBuildUtilities
- PublicDependencyModuleNames: Core, DeveloperSettings, Engine

### `Source/Runtime/TextureUtilitiesCommon/Public/NormalMapIdentification.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace NormalMapIdentification` (scope `UE`)
- L25 _prototype_ `bool HandleAssetPostImport( UTexture* InTexture, const FImageView& InMipToAnalyze );` (scope `UE::NormalMapIdentification`) — Checks if the given mip view of the given texture looks like if contains normal map data, and if so updates the texture compression settings to be for a normal map. Additionally fires off a UI notification with a revert option, as this is a guess and could very well be wrong. This does not examine the entire mip but instead checks small chunks across the mip. This should be called when texture properties are safe to edit (i.e. between Pre/PostEditChange). @return true if the asset was identified as normal

### `Source/Runtime/TextureUtilitiesCommon/Public/TextureImportSettings.h` (Public)


#### enum `ETextureImportFloatingPointFormat`  
`enum class ETextureImportFloatingPointFormat : uint8`  
_L18-28_
- reflection: `UENUM()`
- desc: What CompressionSettings runtime format should imported floating point textures use
- L21 _public enumerator_ `HDR_F16 = 0` — Use "HDR" RGBA16F
- L23 _public enumerator_ `HDRCompressed_BC6` — Use "HDRCompressed" , BC6H
- L25 _public enumerator_ `HDR_F32_or_F16` — Use 32-bit float formats if the source is 32-bit, otherwise use 16-bit HDR
- L27 _public enumerator_ `PreviousDefault = HDR_F16 UMETA(Hidden)` — legacy behavior

#### enum `ETextureImportPNGInfill`  
`enum class ETextureImportPNGInfill : uint8`  
_L38-48_
- reflection: `UENUM()`
- desc: When should RGB colors be spread into neighboring fully transparent white pixels, replacing their RGB. By default, this is done OnlyOnBinaryTransparency, not on PNG's with non-binary-transparency alpha channels. The PNG format has two different ways of storing alpha, either as 1-bit binary transparency, or as full 8/16 bit alpha channels. Used to be set from the TextureImporter/FillPNGZeroAlpha config value.  Setting this option will supersede that.
- L41 _public enumerator_ `Default = 0` — Use the default behavior. For user settings, this means use project settings. For project settings, it's set from the TextureImporter/FillPNGZeroAlpha config value; default was OnlyOnBinaryTransparency.
- L43 _public enumerator_ `Never` — Never infill RGB, import the PNG exactly as it is stored in the file.
- L45 _public enumerator_ `OnlyOnBinaryTransparency` — Only infill RGB on binary transparency; this is the default behavior.
- L47 _public enumerator_ `Always` — Always infill RGB to fully transparent white pixels, even for non-binary alpha channels.

#### class `UTextureImportSettings`  
`class UTextureImportSettings : public UDeveloperSettings`  
_L51-111_
- reflection: `UCLASS(config=Editor, defaultconfig, meta=(DisplayName="Texture Import"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L60 _public member_ `int32 AutoVTSize = 4096;` — `UPROPERTY(config, EditAnywhere, Category=VirtualTextures, meta = ( DisplayName = "Auto Virtual Texturing Size", ToolTip = "Automatically enable the 'Virtual Texture Streaming' texture setting for textures larger than or equal to this size. Zero to disable. This setting will not affect existing textures in the project."))`
- L65 _public member_ `int32 AutoLimitDimension = 0;` — `UPROPERTY(config, EditAnywhere, Category=VirtualTextures, meta = ( DisplayName = "Auto resize large textures", ToolTip = "If not zero, textures over this size that are not VT will be resized to be equal to or less than this. Treated as pixel count limit for cubes and volumes. Must equal AutoVTSize if both are non-zero. This setting will not affect existing textures in the project."))`
- L70 _public member_ `bool bEnableNormalizeNormals = true;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta = ( DisplayName = "Turn on NormalizeNormals for normal maps", ToolTip = "NormalizeNormals makes more correct normals in mip maps; it is recommended, but can be turned off to maintain legacy behavior. This setting is applied to newly imported textures, it does not affect existing textures in the project."))`
- L75 _public member_ `bool bEnableFastMipFilter = true;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta = ( DisplayName = "Turn on fast mip generation filter", ToolTip = "Use the fast mip filter on new textures; it is recommended, but can be turned off to maintain legacy behavior. This setting is applied to newly imported textures, it does not affect existing textures in the project."))`
- L80 _public member_ `ETextureImportFloatingPointFormat CompressedFormatForFloatTextures = ETextureImportFloatingPointFormat::PreviousDefault;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta = ( DisplayName = "CompressionFormat to use for new float textures", ToolTip = "Optionally use HDRCompressed (BC6H), or 32-bit adaptively, instead of HDR (RGBA16F) for floating point textures. This setting is applied to newly imported textures, it does not affect existing textures in the project."))`
- L85 _public member_ `ETextureImportPNGInfill PNGInfill = ETextureImportPNGInfill::Default;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta = ( DisplayName = "When to infill RGB in transparent white PNG", ToolTip = "Default behavior is to infill only for binary transparency; this setting may change that to always or never. Will check TextureImporter/FillPNGZeroAlpha if this is not changed from Default. This setting is applied to newly imported textures, it does not affect existing textures in the project. This setting is project-global, prefer the per-user variant in Editor Preferences."))`
- L90 _public member_ `bool bDoAutomaticTextureSettingsForNonPow2Textures = true;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta = ( DisplayName = "Detect nonpow2 textures and set defaults", ToolTip = "Sets them to NoMipMaps and uncompressed UI compression. If this is off, artists must imported UI textures up correctly by hand."))`
- L94 _public prototype_ `virtual void PostInitProperties() override;`
- L97 _public prototype_ `ETextureImportPNGInfill GetPNGInfillMapDefault() const;` — Get the PNGInfill setting, with Default mapped to a concrete choice
- L101 _public prototype_ `int64 GetAutoLimitPixelCount() const;` — get AutoLimitDimension as a pixel count (squared), and with sanity checks applied zero means do not limit
- L104 _public prototype_ `bool IsImportAutoVTEnabled() const;` — IsImportAutoVTEnabled checks not just this config but also the project VT settings
- L107 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L116 _namespace_ `namespace UE`
- L116 _namespace_ `namespace TextureUtilitiesCommon` (scope `UE`)
- L122 _prototype_ `void ApplyDefaultsForNewlyImportedTextures(UTexture * Texture, bool bIsReimport);` (scope `UE::TextureUtilitiesCommon`) — Set default properties on Texture for newly imported textures, or reimports. Should be called after all texture properties are set, before PostEditChange()
- L128 _prototype_ `bool ShouldTextureBeVirtualByAutoImportSize(const UTexture * Texture);` (scope `UE::TextureUtilitiesCommon`) — Query if texture will be made VT automatically on import due to exceeding AutoVTSize or other conditions which require it to be VT only returns true if VT is enabled and auto-VT is enabled
- L134 _prototype_ `bool GetDefaultSRGB(TextureCompressionSettings TC, ETextureSourceFormat ImportImageFormat, bool ImportImageSRGB);` (scope `UE::TextureUtilitiesCommon`) — Get the default value for Texture->SRGB ImportImageSRGB is the SRGB setting of the imported image

### `Source/Runtime/TextureUtilitiesCommon/Public/TextureImportUserSettings.h` (Public)


#### class `UTextureImportUserSettings`  
`class UTextureImportUserSettings : public UDeveloperSettings`  
_L17-26_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta=(DisplayName="Texture Import"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L25 _public member_ `ETextureImportPNGInfill PNGInfill = ETextureImportPNGInfill::Default;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta = ( DisplayName = "When to infill RGB in transparent white PNG", ToolTip = "Whether to perform infill only for binary transparency, always, or never. If set to 'default', uses global project setting."))`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace TextureUtilitiesCommon` (scope `UE`)
- L33 _prototype_ `ETextureImportPNGInfill GetPNGInfillSetting();` (scope `UE::TextureUtilitiesCommon`) — Resolves PNG infill setting using, in order of preference, per-project user settings, project settings, and legacy config settings.

### `Source/Runtime/TextureUtilitiesCommon/Public/TextureImportUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TextureUtilitiesCommon` (scope `UE`)
- L16 _prototype_ `template<typename ImageClassType> bool AutoDetectAndChangeGrayScale(ImageClassType& Image);` (scope `UE::TextureUtilitiesCommon`) — Detect the existence of gray scale image in some formats and convert those to a gray scale equivalent image @return true if the image was converted
- L27 _prototype_ `void FillZeroAlphaPNGData(int32 SizeX, int32 SizeY, ETextureSourceFormat SourceFormat, uint8* SourceData, bool bDoOnComplexAlphaNotJustBinaryTransparency);` (scope `UE::TextureUtilitiesCommon`) — For PNG texture importing, this ensures that any pixels with an alpha value of zero have an RGB assigned to them from a neighboring pixel which has non-zero alpha. This is needed as PNG exporters tend to turn pixels that are RGBA = (x,x,x,0) to (1,1,1,0) and this produces artifacts when drawing the texture with bilinear filtering. @param TextureSource - The source texture @param SourceData - The source texture data
- L41 _prototype_ `bool IsImportResolutionValid(int64 Width, int64 Height, bool bAllowNonPowerOfTwo, FText* OutErrorMessage);` (scope `UE::TextureUtilitiesCommon`) — Tests if the given height and width specify a supported texture resolution to import; Can optionally check if the height/width are powers of two @param Width The width of an imported texture whose validity should be checked @param Height The height of an imported texture whose validity should be checked @param bAllowNonPowerOfTwo Whether or not non-power-of-two textures are allowed @param OutErrorMessage Optional output for an error message @return bool true if the given height/width represent a supported texture resolution, false if not NOTE: may open a dialog box to ask user if large non-VT import is wanted!

### `Source/Runtime/TextureUtilitiesCommon/Public/TextureSourceDataUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TextureUtilitiesCommon` (scope `UE`)
- L13 _namespace_ `namespace Experimental` (scope `UE::TextureUtilitiesCommon`)
- L19 _prototype_ `bool DownsizeTextureSourceData(UTexture* Texture, int32 TargetSourceSize, const ITargetPlatform* TargetPlatform);` (scope `UE::TextureUtilitiesCommon::Experimental`) — resize texture source to be <= TargetSourceSize x TargetSourceSize Halving (mip) steps are done (only Texture2D and TextureCube are supported at the moment) Note it does not trigger the post edit change after modifying the source texture
- L23 _prototype_ `bool ResizeTextureSourceDataToNearestPowerOfTwo(UTexture* Texture);` (scope `UE::TextureUtilitiesCommon::Experimental`) — Try to resize the texture source data to a power of two Note it does not trigger the post edit change after modifying the source texture
- L31 _prototype_ `bool DownsizeTextureSourceDataNearRenderingSize(UTexture* Texture, const ITargetPlatform* TargetPlatform, int32 AdditionalSourceSizeLimit = 16384);` (scope `UE::TextureUtilitiesCommon::Experimental`) — Try to resize the texture source data so that it is not larger than what is built for the specified platform eg. if the output build size is 1024 but the source size is 2048, the source will be reduced to 1024 Texture->LODBias is changed so that the output built size stays the same (only Texture2D and TextureCube are supported at the moment) AdditionalSourceSizeLimit can be used to apply an extra size limit on the source Note: This function DOES trigger the post edit change after modifying the source texture
- L36 _prototype_ `bool ChangeTextureSourceFormat(UTexture* Texture, ETextureSourceFormat NewFormat);` (scope `UE::TextureUtilitiesCommon::Experimental`) — ChangeTextureSourceFormat calls Pre/Post edit change beware that changing format may change the interpretation of the SRGB bool in Texture ChangeTextureSourceFormat supports mips and blocks (udim) but not layers
- L42 _prototype_ `bool CompressTextureSourceWithJPEG(UTexture* Texture,int32 Quality = 0);` (scope `UE::TextureUtilitiesCommon::Experimental`) — Replace TextureSource with JPEG compressed data returns true if change was made calls Pre/PostEditChange : Quality == 0 for default (85)

### `Source/Runtime/TextureUtilitiesCommon/Public/UDIMUtilities.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TextureUtilitiesCommon` (scope `UE`)
- L18 _variable_ `constexpr int32 UDIM_Max_X = 9;` (scope `UE::TextureUtilitiesCommon`)
- L19 _variable_ `constexpr int32 UDIM_Max_Y = 90;` (scope `UE::TextureUtilitiesCommon`)
- L20 _variable_ `constexpr int32 UDIM_Min_Index = 1001;` (scope `UE::TextureUtilitiesCommon`)
- L21 _variable_ `constexpr int32 UDIM_Max_Index = UDIM_Min_Index + UDIM_Max_X + UDIM_Max_Y * 10;` (scope `UE::TextureUtilitiesCommon`)
- L25 _variable_ `constexpr const TCHAR* DefaultUdimRegexPattern = TEXT(R"((.` (scope `UE::TextureUtilitiesCommon`) — this Regex is unnecessarily complex and broad UDIM must start with "10" then two digits, or "1100"
- L27 _prototype_ `uint32 ParseUDIMName(const FString& Name, const FString& UdimRegexPattern, FString& OutPrefixName, FString& OutPostfixName);` (scope `UE::TextureUtilitiesCommon`)
- L29 _prototype_ `int32 GetUDIMIndex(int32 BlockX, int32 BlockY);` (scope `UE::TextureUtilitiesCommon`)
- L35 _prototype_ `TMap<int32, FString> GetUDIMBlocksFromSourceFile(const FString& File, const FString& UdimRegexPattern, FString* OutFilenameWithoutUdimPatternAndExtension = nullptr);` (scope `UE::TextureUtilitiesCommon`) — Parse the file for the UDIM pattern If the pattern is found search in the folder of the file for the others blocks
- L37 _prototype_ `void ExtractUDIMCoordinates(int32 UDIMIndex, int32& OutBlockX, int32& OutBlockY);` (scope `UE::TextureUtilitiesCommon`)
