# Plugins / AlembicHairTranslatorModule

- module root: `Plugins/Importers/AlembicHairImporter/Source/AlembicHairTranslator`
- headers: 2; symbols: 15
- symbol kinds: class=2, member=1, prototype=12
- PrivateDependencyModuleNames: AlembicLib, Core, CoreUObject, Engine, HairStrandsCore, HairStrandsEditor, Imath

### `Plugins/Importers/AlembicHairImporter/Source/AlembicHairTranslator/Private/AlembicHairTranslator.h` (Private)


#### class `FAlembicHairTranslator`  
`class FAlembicHairTranslator : public IGroomTranslator`  
_L10-28_
- inherits: `IGroomTranslator`
- L13 _public prototype_ `FAlembicHairTranslator();`
- L14 _public prototype_ `virtual ~FAlembicHairTranslator();`
- L16 _public prototype_ `virtual bool Translate(const FString& FilePath, FHairDescription& OutHairDescription, const FGroomConversionSettings& ConversionSettings) override;`
- L17 _public prototype_ `virtual bool CanTranslate(const FString& FilePath) override;`
- L18 _public prototype_ `virtual bool IsFileExtensionSupported(const FString& FileExtension) const override;`
- L19 _public prototype_ `virtual FString GetSupportedFormat() const override;`
- L21 _public prototype_ `virtual bool Translate(const FString& FilePath, FHairDescription& OutHairDescription, const struct FGroomConversionSettings& ConversionSettings, FGroomAnimationInfo* OutAnimInfo) override;`
- L22 _public prototype_ `virtual bool BeginTranslation(const FString& FilePath) override;`
- L23 _public prototype_ `virtual bool Translate(float FrameTime, FHairDescription& OutHairDescription, const struct FGroomConversionSettings& ConversionSettings) override;`
- L24 _public prototype_ `virtual void EndTranslation() override;`
- L27 _private member_ `class FAbcPimpl* Abc;`

### `Plugins/Importers/AlembicHairImporter/Source/AlembicHairTranslator/Private/AlembicHairTranslatorModule.h` (Private)


#### class `FAlembicHairTranslatorModule`  
`class FAlembicHairTranslatorModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`
