# Programs / GeometryProcessing

- module root: `Source/Programs/GeometryProcessing`
- headers: 2; symbols: 19
- symbol kinds: delegate=1, function=9, macro=1, namespace=2, prototype=5, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, DynamicMesh, GeometryAlgorithms, GeometryCore, MeshFileUtils, Projects
- PublicIncludePathModuleNames: Launch

### `Source/Programs/GeometryProcessing/Private/GeometryProcessing.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryProcessing, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryProcessing, Log, All);`

### `Source/Programs/GeometryProcessing/Private/Utils/CommandUtils.h` (Private)


#### struct `UE::CommandUtils::FAlgList`  
`struct FAlgList`  
_L81-85_
- desc: Struct to manage the list of known algorithms selectable with the -alg parameter
- L83 _public prototype_ `static bool Register(FString Name, TFunction<bool()> Alg);`
- L84 _public prototype_ `static bool Run();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CommandUtils` (scope `UE`)
- L15 _function_ `inline void Fail()` (scope `UE::CommandUtils`) — For errors that we can't continue through -- immediately exits the program
- L23 _function_ `template<typename T> T RequireParam(const TCHAR* Arg)` (scope `UE::CommandUtils`) — Read a required parameter from the command line, or exit if we cannot Note that parameters are not required to have a preceding dash, so must be specified if desired (e.g., RequireParam("-input") if you expect "-input inputvalue")
- L38 _function_ `template<typename T> T RequireParam(const char* Arg)` (scope `UE::CommandUtils`)
- L45 _function_ `template<typename T> bool RequestParam(const TCHAR* Arg, T& Value)` (scope `UE::CommandUtils`) — Request an optional parameter from the command line
- L50 _function_ `template<typename T> bool RequestParam(const char* Arg, T& Value)` (scope `UE::CommandUtils`)
- L57 _function_ `inline bool HasTag(const TCHAR* Tag)` (scope `UE::CommandUtils`) — Check whether a tag is on the command line Note the preceding "-" is implicit for this method, so HasTag("tag") will check for "-tag"
- L61 _function_ `inline bool HasTag(const char* Tag)` (scope `UE::CommandUtils`)
- L67 _prototype_ `UE::Geometry::FDynamicMesh3 RequireInputMesh(const TCHAR* InputArg = TEXT("-input"), const UE::MeshFileUtils::FLoadOBJSettings& Settings = UE::MeshFileUtils::FLoadOBJSettings(), bool bMustHaveFaces =` (scope `UE::CommandUtils`) — Reads an OBJ mesh from path specified by the input parameter
- L68 _function_ `inline UE::Geometry::FDynamicMesh3 RequireInputMesh(const char* InputArg, const UE::MeshFileUtils::FLoadOBJSettings& Settings = UE::MeshFileUtils::FLoadOBJSettings(), bool bMustHaveFaces = true)` (scope `UE::CommandUtils`)
- L74 _prototype_ `bool OutputResult(const UE::Geometry::FDynamicMesh3& Mesh, const TCHAR* OutputPathArg = TEXT("-output"), const UE::MeshFileUtils::FWriteOBJSettings& Settings = UE::MeshFileUtils::FWriteOBJSetti` (scope `UE::CommandUtils`) — Writes an OBJ mesh to the output parameter
- L75 _function_ `inline bool OutputResult(const UE::Geometry::FDynamicMesh3& Mesh, const char* OutputPathArg, const UE::MeshFileUtils::FWriteOBJSettings& Settings = UE::MeshFileUtils::FWriteOBJSettings())` (scope `UE::CommandUtils`)
- L90 _macro_ `#define DefineAlgorithm(Name) bool Alg_##Name(); static bool bAlgRegistered_##Name = UE::CommandUtils::FAlgList::Register(TEXT(#Name), &Alg_##Name); bool Alg_##Name()` — Macro to create an algorithm that will automatically register as an -alg parameter
