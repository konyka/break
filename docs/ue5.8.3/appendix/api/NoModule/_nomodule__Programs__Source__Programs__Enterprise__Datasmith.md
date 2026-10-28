# NoModule / _nomodule__Programs__Source__Programs__Enterprise__Datasmith

- module root: `.`
- headers: 4; symbols: 28
- symbol kinds: class=1, function=9, macro=2, member=6, namespace=1, prototype=7, struct=2

### `Source/Programs/Enterprise/Datasmith/DatasmithSDKSample/MeshUtils.h` (Other)


#### Free symbols / members of external scopes

- L6 _function_ `static void CreateSimpleBox(FDatasmithMesh& Mesh)`
- L120 _function_ `static void CreateSimplePyramid(FDatasmithMesh& Mesh)`

### `Source/Programs/Enterprise/Datasmith/DatasmithSDKSample/Scenes/shared.h` (Other)


#### struct `SampleUtils::FGridLayout`  
`struct FGridLayout`  
_L12-29_
- desc: a little helper struct to layout stuff in a grid pattern fashion
- L14 _public function_ `FGridLayout(FVector Offset=FVector::ZeroVector, FVector Stride=FVector(100.)) : Stride(Stride) , Offset(Offset)`
- L19 _public function_ `void NextItem()`
- L20 _public function_ `void NextLine()`
- L21 _public function_ `FVector GetCurrentVector()`
- L24 _private member_ `int32 XIndex = 0, YIndex = 0;`
- L24 _private member_ `int32 XIndex = 0, YIndex = 0;`
- L25 _private member_ `FVector Offset;`
- L26 _private member_ `FVector Stride;`
- L27 _private member_ `double XStride = 100.0;`
- L28 _private member_ `double YStride = 100.0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SampleUtils`

### `Source/Programs/Enterprise/Datasmith/DatasmithSDKSample/ScenesManager.h` (Other)


#### struct `ISampleScene`  
`struct ISampleScene`  
_L20-33_
- L23 _public prototype_ `virtual FString GetName() const = 0;` — a simple name to identify that scene
- L26 _public function_ `virtual FString GetDescription() const` — a longer, optionnal description
- L29 _public function_ `virtual TArray<FString> GetTags() const` — list the themes used in this scene (eg. Instancing, LOD, Collision, etc.)
- L32 _public function_ `virtual TSharedPtr<IDatasmithScene> Export()` — export a udatasmith scene

#### class `FScenesManager`  
`class FScenesManager`  
_L43-52_
- L47 _public prototype_ `static void Register(TSharedPtr<ISampleScene> SampleScene);` — Register a new scene. Prefer the REGISTER_SCENE macro
- L49 _public prototype_ `static const TArray<TSharedPtr<ISampleScene>>& GetAllScenes();`
- L51 _public prototype_ `static TSharedPtr<ISampleScene> GetScene(const FString& Name);`

#### Free symbols / members of external scopes

- L11 _prototype_ `const FString& GetExportPath();`
- L12 _prototype_ `void SetExportPath(const FString& Path);`
- L17 _prototype_ `void SetupSharedSceneProperties(TSharedRef<IDatasmithScene> DatasmithScene);` — For this sample application, some parameters are shared by all the scene. To avoid repetition, this is setup there.
- L36 _macro_ `#define REGISTER_SCENE(Type) \`

### `Source/Programs/Enterprise/Datasmith/DatasmithSDKSample/pch.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define PCH_H`
