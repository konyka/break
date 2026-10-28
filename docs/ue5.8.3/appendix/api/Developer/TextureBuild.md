# Developer / TextureBuild

- module root: `Source/Developer/TextureBuild`
- headers: 1; symbols: 25
- symbol kinds: class=4, function=12, namespace=2, prototype=7
- PrivateDependencyModuleNames: Core, DerivedDataCache, ImageCore, ImageWrapper, TextureBuildUtilities, TextureCompressor, TextureFormat
- PrivateIncludePathModuleNames: Engine

### `Source/Developer/TextureBuild/Public/TextureBuildFunction.h` (Public)


#### class `FTextureBuildFunction`  
`class FTextureBuildFunction : public UE::DerivedData::IBuildFunction`  
_L16-25_
- inherits: `UE::DerivedData::IBuildFunction`
- L19 _public prototype_ `virtual FGuid GetVersion() const final;`
- L20 _public prototype_ `virtual void Configure(UE::DerivedData::FBuildConfigContext& Context) const override;`
- L21 _public prototype_ `virtual void Build(UE::DerivedData::FBuildContext& Context) const override;`
- L24 _protected prototype_ `virtual void GetVersion(UE::DerivedData::FBuildVersionBuilder& Builder, ITextureFormat*& OutTextureFormatVersioning) const = 0;`

#### class `FGenericTextureTilingBuildFunction`  
`template <class ITextureTilerObject> class FGenericTextureTilingBuildFunction : public UE::DerivedData::IBuildFunction`  
_L41-58_
- inherits: `UE::DerivedData::IBuildFunction`
- desc: This build function expects an implementation of ITextureTiler as its template and looks a bit awkward because IBuildFunction is required to not have any state, so we can't put the instance of the ITextureTiler on our object - hence the odd statics.
- L43 _private function_ `virtual void Build(UE::DerivedData::FBuildContext& Context) const`
- L48 _private function_ `virtual void Configure(UE::DerivedData::FBuildConfigContext& Context) const`
- L52 _private function_ `virtual FGuid GetVersion() const final`
- L53 _private function_ `const UE::FUtf8SharedString& GetName() const final`

#### class `FGenericTextureDetileBuildFunction`  
`template <class ITextureTilerObject> class FGenericTextureDetileBuildFunction : public UE::DerivedData::IBuildFunction`  
_L63-80_
- inherits: `UE::DerivedData::IBuildFunction`
- L65 _private function_ `virtual void Build(UE::DerivedData::FBuildContext& Context) const`
- L70 _private function_ `virtual void Configure(UE::DerivedData::FBuildConfigContext& Context) const`
- L74 _private function_ `virtual FGuid GetVersion() const final`
- L75 _private function_ `const UE::FUtf8SharedString& GetName() const final`

#### class `FGenericTextureDecodeBuildFunction`  
`template <class ITextureFormatObject> class FGenericTextureDecodeBuildFunction : public UE::DerivedData::IBuildFunction`  
_L85-101_
- inherits: `UE::DerivedData::IBuildFunction`
- L87 _private function_ `virtual void Build(UE::DerivedData::FBuildContext& Context) const`
- L91 _private function_ `virtual void Configure(UE::DerivedData::FBuildConfigContext& Context) const`
- L95 _private function_ `virtual FGuid GetVersion() const final`
- L96 _private function_ `const UE::FUtf8SharedString& GetName() const final`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L31 _prototype_ `void GenericTextureTilingBuildFunction(UE::DerivedData::FBuildContext& Context, const ITextureTiler* Tiler, const UE::FUtf8SharedString& BuildFunctionName);` — This function does the meat of breaking out the inputs from the build context and handing them to the tiler, then packing them back up for the build process.
- L60 _prototype_ `void GenericTextureDetileBuildFunction(UE::DerivedData::FBuildContext& Context, const ITextureTiler* Tiler, const UE::FUtf8SharedString& BuildFunctionName);`
- L82 _prototype_ `void GenericTextureDecodeBuildFunction(UE::DerivedData::FBuildContext& Context, const UE::FUtf8SharedString& BuildFunctionName);`
