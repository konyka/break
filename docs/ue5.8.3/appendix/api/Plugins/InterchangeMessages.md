# Plugins / InterchangeMessages

- module root: `Plugins/Interchange/Runtime/Source/Messages`
- headers: 1; symbols: 21
- symbol kinds: class=8, macro=1, member=8, prototype=4
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCore

### `Plugins/Interchange/Runtime/Source/Messages/Public/Fbx/InterchangeFbxMessages.h` (Public)


#### class `UInterchangeResultMeshWarning`  
`class UInterchangeResultMeshWarning : public UInterchangeResultWarning`  
_L17-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultWarning`
- desc: Base class for FBX parser warnings
- L24 _public member_ `FString MeshName;` — `UPROPERTY()`

#### class `UInterchangeResultTextureDisplay`  
`class UInterchangeResultTextureDisplay : public UInterchangeResultDisplay_Generic`  
_L31-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultDisplay_Generic`
- desc: Base class for FBX parser warnings
- L38 _public member_ `FString TextureName;` — `UPROPERTY()`

#### class `UInterchangeResultTextureWarning`  
`class UInterchangeResultTextureWarning : public UInterchangeResultWarning`  
_L45-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultWarning`
- desc: Base class for FBX parser warnings
- L52 _public member_ `FString TextureName;` — `UPROPERTY()`

#### class `UInterchangeResultMeshError`  
`class UInterchangeResultMeshError : public UInterchangeResultError`  
_L59-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultError`
- desc: Base class for FBX parser errors
- L66 _public member_ `FString MeshName;` — `UPROPERTY()`

#### class `UInterchangeResultMeshWarning_Generic`  
`class UInterchangeResultMeshWarning_Generic : public UInterchangeResultMeshWarning`  
_L74-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultMeshWarning`
- desc: A generic class for FBX parser warnings, with no additional metadata, and where the text is specified by the user
- L79 _public prototype_ `virtual FText GetText() const override;`
- L82 _public member_ `FText Text;` — `UPROPERTY()`

#### class `UInterchangeResultMeshError_Generic`  
`class UInterchangeResultMeshError_Generic : public UInterchangeResultMeshError`  
_L90-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultMeshError`
- desc: A generic class for FBX parser errors, with no additional metadata, and where the text is specified by the user
- L95 _public prototype_ `virtual FText GetText() const override;`
- L98 _public member_ `FText Text;` — `UPROPERTY()`

#### class `UInterchangeResultMeshWarning_TooManyUVs`  
`class UInterchangeResultMeshWarning_TooManyUVs : public UInterchangeResultMeshWarning`  
_L106-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultMeshWarning`
- L111 _public prototype_ `virtual FText GetText() const override;`
- L114 _public member_ `int32 ExcessUVs;` — `UPROPERTY()`

#### class `UInterchangeResultTextureDisplay_TextureFileDoNotExist`  
`class UInterchangeResultTextureDisplay_TextureFileDoNotExist : public UInterchangeResultTextureDisplay`  
_L121-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultTextureDisplay`
- desc: A generic class for FBX parser warnings, with no additional metadata, and where the text is specified by the user
- L126 _public prototype_ `virtual FText GetText() const override;`
- L129 _public member_ `FString MaterialName;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEMESSAGES_API`
