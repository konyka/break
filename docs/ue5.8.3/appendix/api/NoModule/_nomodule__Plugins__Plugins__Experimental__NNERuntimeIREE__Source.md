# NoModule / _nomodule__Plugins__Plugins__Experimental__NNERuntimeIREE__Source

- module root: `.`
- headers: 5; symbols: 123
- symbol kinds: class=7, enum=1, enumerator=4, function=43, macro=8, member=17, namespace=8, prototype=26, struct=2, typedef=7

### `Plugins/Experimental/NNERuntimeIREE/Source/ExternalBuild/Include/Clang/alloca.h` (Other)


#### Free symbols / members of external scopes

- L9 _prototype_ `void *alloca(size_t);`
- L11 _macro_ `#define alloca __builtin_alloca`

### `Plugins/Experimental/NNERuntimeIREE/Source/ExternalBuild/Source/Iree/Compiler/Plugins/Target/UnrealShader/SPIRVToHLSL.h` (Other)


#### struct `mlir::iree_compiler::HLSLShader`  
`struct HLSLShader`  
_L15-18_
- L16 _public member_ `std::string source;`
- L17 _public member_ `std::string metadata;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace mlir`
- L13 _namespace_ `namespace iree_compiler` (scope `mlir`)
- L23 _prototype_ `std::optional<std::pair<HLSLShader, std::string>> crossCompileSPIRVToHLSL(llvm::ArrayRef<uint32_t> spvBinary, StringRef entryPoint, bool useStructuredBuffers = false);` (scope `mlir::iree_compiler`) — Cross compiles SPIR-V into HLSL source code for the compute shader with |entryPoint| and returns the HLSL source and the new entry point name. Returns std::nullopt on failure.

### `Plugins/Experimental/NNERuntimeIREE/Source/ExternalBuild/Source/Iree/Compiler/Plugins/Target/UnrealShader/UnrealShaderTargetUtils.h` (Other)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace mlir`
- L8 _namespace_ `namespace iree_compiler` (scope `mlir`)
- L8 _namespace_ `namespace IREE` (scope `mlir::iree_compiler`)
- L8 _namespace_ `namespace GPU` (scope `mlir::iree_compiler::IREE`)
- L8 _namespace_ `namespace UnrealShaderTargetUtils` (scope `mlir::iree_compiler::IREE::GPU`)
- L14 _prototype_ `TargetAttr getTargetDetails(llvm::StringRef target, MLIRContext *context);` (scope `mlir::iree_compiler::IREE::GPU::UnrealShaderTargetUtils`) — Returns a TargetAttr to describe the details of the given |target|, which can be a product name like "rtx3090"/"mali-g710"/"adreno", a microarchitecture name like "ampere"/"valhall", or "apple" for Apple/Metal GPUs. Returns a null TargetAttr if the given |target| is not recognized.

### `Plugins/Experimental/NNERuntimeIREE/Source/ExternalBuild/Source/NNEMlirTools/NNERuntimeIREE/Include/NNEMlirTools.h` (Other)


#### enum `(anonymous)`  
`typedef enum`  
_L35-40_
- desc: Success / error codes returned through NNEMlirStatus.

#### struct `NNEMlirApi`  
`typedef struct NNEMlirApi`  
_L53-89_
- desc: Function table
- L54 _public member_ `uint32_t AbiVersion;` — Must equal NNEMLIR_ABI_VERSION
- L55 _public member_ `uint32_t StructSize;` — sizeof(NNEMlirApi)
- L58 _public member_ `const char* (NNEMLIR_CALL *StatusToString) (NNEMlirStatus);` — Status helpers
- L59 _public prototype_ `NNEMlirStatusCode (NNEMLIR_CALL *GetStatusCode) (NNEMlirStatus);`
- L62 _public prototype_ `NNEMlirContext (NNEMLIR_CALL *CreateContext) (void);` — Context & parsing
- L63 _public prototype_ `NNEMlirStatus (NNEMLIR_CALL *ParseModuleFromBuffer) (NNEMlirContext,const char* ,size_t ,NNEMlirModule*);`
- L64 _public prototype_ `NNEMlirStatus (NNEMLIR_CALL *ParseModuleFromFile) (NNEMlirContext,const char* ,NNEMlirModule*);`
- L67 _public prototype_ `size_t (NNEMLIR_CALL *GetPublicFunctionCount)(NNEMlirModule);` — Module-level introspection
- L68 _public prototype_ `NNEMlirFunction (NNEMLIR_CALL *GetPublicFunction) (NNEMlirModule,size_t);`
- L71 _public member_ `const char* (NNEMLIR_CALL *GetFunctionName) (NNEMlirFunction);` — Function-level introspection
- L72 _public prototype_ `size_t (NNEMLIR_CALL *GetInputCount) (NNEMlirFunction);`
- L73 _public prototype_ `size_t (NNEMLIR_CALL *GetResultCount) (NNEMlirFunction);`
- L74 _public prototype_ `NNEMlirValue (NNEMLIR_CALL *GetInputValue) (NNEMlirFunction,size_t);`
- L75 _public prototype_ `NNEMlirValue (NNEMLIR_CALL *GetResultValue) (NNEMlirFunction,size_t);`
- L78 _public member_ `const char* (NNEMLIR_CALL *GetValueName) (NNEMlirValue);` — Value-level introspection
- L79 _public member_ `const char* (NNEMLIR_CALL *GetValueTypeText) (NNEMlirValue);` — E.g. "tensor<4x16xf32>".
- L80 _public member_ `const char* (NNEMLIR_CALL *GetElementTypeText) (NNEMlirValue);` — Element type only, e.g. "f32".
- L81 _public prototype_ `size_t (NNEMLIR_CALL *GetShape) (NNEMlirValue,int64_t*,size_t);`
- L84 _public member_ `void (NNEMLIR_CALL *ReleaseStatus) (NNEMlirStatus);` — Release opaque handles
- L85 _public member_ `void (NNEMLIR_CALL *ReleaseContext) (NNEMlirContext);`
- L86 _public member_ `void (NNEMLIR_CALL *ReleaseModule) (NNEMlirModule);`
- L87 _public member_ `void (NNEMLIR_CALL *ReleaseFunction) (NNEMlirFunction);`
- L88 _public member_ `void (NNEMLIR_CALL *ReleaseValue) (NNEMlirValue);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define NNEMLIR_API __declspec(dllexport)`
- L18 _macro_ `#define NNEMLIR_CALL __cdecl`
- L20 _macro_ `#define NNEMLIR_API __attribute__((visibility("default")))`
- L21 _macro_ `#define NNEMLIR_CALL`
- L26 _macro_ `#define NNEMLIR_API`
- L36 _enumerator_ `NNEMLIR_SUCCESS = 0` (scope `__anon577ead9c0103`) — Operation completed successfully.
- L37 _enumerator_ `NNEMLIR_ERR_PARSE_FAILED = 1` (scope `__anon577ead9c0103`) — Parsing of file/buffer failed.
- L38 _enumerator_ `NNEMLIR_ERR_BAD_ARGUMENT = 2` (scope `__anon577ead9c0103`) — Operation received invalid argument.
- L39 _enumerator_ `NNEMLIR_ERR_INTERNAL = 0x7FFF` (scope `__anon577ead9c0103`) — Unexpected internal failure.
- L40 _typedef_ `} NNEMlirStatusCode;`
- L43 _typedef_ `struct NNEMlirStatus_s;` — Opaque handles
- L44 _typedef_ `struct NNEMlirContext_s;` — Context, contains MLIRContext with registered dialects.
- L45 _typedef_ `struct NNEMlirModule_s;` — Parsed MLIR module.
- L46 _typedef_ `struct NNEMlirFunction_s;` — (Public) function within a module.
- L47 _typedef_ `struct NNEMlirValue_s;` — Function argument or result.
- L50 _macro_ `#define NNEMLIR_ABI_VERSION 1u` — ABI version
- L89 _typedef_ `} NNEMlirApi;`
- L93 _prototype_ `const NNEMlirApi* NNEMLIR_CALL NNEMlirGetInterface(uint32_t MinVersion);` — Returns a pointer to the global NNEMlirApi or nullptr if the requested minimum ABI version is newer than the implementation.

### `Plugins/Experimental/NNERuntimeIREE/Source/ExternalBuild/Source/NNEMlirTools/NNERuntimeIREE/Include/NNEMlirTools_cxx_api.h` (Other)


#### class `NNEMlirTools::Api`  
`class Api`  
_L41-76_
- desc: Api manages the NNEMlirApi object, which by design has to be manullay initialized. We don't want to link againt the library.
- L43 _public function_ `static const Api& Instance()`
- L54 _public function_ `static void Initialize(const NNEMlirApi* Ptr)`
- L64 _public function_ `const NNEMlirApi* operator->() const`
- L67 _private member_ `static const NNEMlirApi* ApiPtr;`
- L69 _private function_ `Api()`
- L74 _private prototype_ `Api(const Api&) = delete;` — Not copyable
- L75 _private prototype_ `Api& operator=(const Api&) = delete;`
- L78 _member_ `inline const NNEMlirApi* Api::ApiPtr = nullptr;`

#### class `NNEMlirTools::UniqueHandle`  
`template<class T> class UniqueHandle`  
_L89-135_
- desc: Owning pointer holder for the underlying C Objects that is move-only. Similar to std::unique_ptr.
- L92 _public prototype_ `UniqueHandle() noexcept = default;`
- L93 _public function_ `explicit UniqueHandle(T Hdl) noexcept : Handle(Hdl)`
- L95 _public function_ `~UniqueHandle() noexcept`
- L100 _public function_ `UniqueHandle(UniqueHandle&& Other) noexcept : Handle(std::exchange(Other.Handle, T{}))`
- L102 _public function_ `UniqueHandle& operator=(UniqueHandle&& Other) noexcept`
- L111 _public function_ `void Reset(T NewHandle = T{}) noexcept`
- L121 _public function_ `T Release() noexcept`
- L127 _public prototype_ `UniqueHandle(const UniqueHandle&) = delete;` — Move only
- L128 _public prototype_ `UniqueHandle& operator=(const UniqueHandle&) = delete;`
- L130 _public function_ `T Get() const noexcept`
- L131 _public function_ `explicit operator bool() const noexcept`
- L134 _private member_ `T Handle{};`

#### class `NNEMlirTools::Status`  
`class Status : public UniqueHandle<NNEMlirStatus>`  
_L141-160_
- inherits: `UniqueHandle<NNEMlirStatus>`
- desc: Status that is set on success/error and might contain a message.
- L144 _public function_ `Status(NNEMlirStatus Sts) noexcept : UniqueHandle<NNEMlirStatus>(Sts)`
- L150 _public function_ `explicit operator bool() const` — True on success or false on error
- L156 _public function_ `std::string GetMessage() const` — Get message (might be only set on error)

#### class `NNEMlirTools::Context`  
`class Context : public UniqueHandle<NNEMlirContext>`  
_L163-173_
- inherits: `UniqueHandle<NNEMlirContext>`
- desc: Context that holds the registered dialects
- L166 _public function_ `Context() : UniqueHandle<NNEMlirContext>(Api::Instance()->CreateContext())`

#### class `NNEMlirTools::Module`  
`class Module : public UniqueHandle<NNEMlirModule>`  
_L176-219_
- inherits: `UniqueHandle<NNEMlirModule>`
- desc: Module obtained from parsing a MLIR file or buffer
- L179 _public function_ `static Module ParseFromFile(const Context& Ctx, const char* Path)`
- L191 _public function_ `static Module ParseFromBuffer(const Context& Ctx, const char* Data, size_t Length)` — Parse MLIR from buffer (not null terminated) and return Module
- L203 _public function_ `size_t GetFunctionCount() const` — Return public function count
- L209 _public prototype_ `Function GetFunction(size_t Index) const;` — Retrieve a public function by index
- L212 _public prototype_ `std::vector<Function> GetFunctions() const;` — Get a vector containing all public functions
- L215 _private function_ `Module(NNEMlirModule Mod) noexcept : UniqueHandle<NNEMlirModule>(Mod)`
- L328 _function_ `inline Function Module::GetFunction(size_t Index) const`
- L337 _function_ `inline std::vector<Function> Module::GetFunctions() const`

#### class `NNEMlirTools::Function`  
`class Function : public UniqueHandle<NNEMlirFunction>`  
_L222-262_
- inherits: `UniqueHandle<NNEMlirFunction>`
- desc: Function in a module
- L226 _public function_ `std::string GetName() const` — Get the name of the function
- L233 _public function_ `size_t GetInputCount() const` — Get the input argument count
- L239 _public prototype_ `Value GetInput(size_t Index) const;` — Get an input argument by index
- L242 _public prototype_ `std::vector<Value> GetInputs() const;` — Get a vector with the input arguments
- L245 _public function_ `size_t GetResultCount() const` — Get the result count
- L251 _public prototype_ `Value GetResult(size_t Index) const;` — Get a result by index
- L254 _public prototype_ `std::vector<Value> GetResults() const;` — Get a vector with the results
- L258 _private function_ `explicit Function(NNEMlirFunction Fn) : UniqueHandle<NNEMlirFunction>(Fn)`
- L351 _function_ `inline Value Function::GetInput(size_t Index) const`
- L361 _function_ `inline std::vector<Value> Function::GetInputs() const`
- L375 _function_ `inline Value Function::GetResult(size_t Index) const`
- L385 _function_ `inline std::vector<Value> Function::GetResults() const`

#### class `NNEMlirTools::Value`  
`class Value : public UniqueHandle<NNEMlirValue>`  
_L265-326_
- inherits: `UniqueHandle<NNEMlirValue>`
- desc: Argument or result of a function
- L269 _public function_ `std::string GetElementType() const` — Get the element type string, e.g. "f32"
- L275 _public function_ `std::string GetShapeTypeText() const` — Get the shape type text, e.g. "4x16xf32"
- L292 _public function_ `std::string GetName() const` — Get the name (empty for results)
- L298 _public function_ `size_t GetRank() const` — Get the rank
- L304 _public function_ `std::vector<int64_t> GetShape() const` — Get the shape
- L316 _public function_ `size_t GetShape(int64_t* ShapeArray, size_t Capacity) const` — Fill in the shape
- L322 _private function_ `explicit Value(NNEMlirValue Val) : UniqueHandle<NNEMlirValue>(Val)`

#### Free symbols / members of external scopes

- L22 _macro_ `#define NNEMLIR_CXX_API_THROW(Message) \`
- L33 _namespace_ `namespace NNEMlirTools`
- L35 _function_ `[[noreturn]] inline void ThrowError(const std::string& Message)` (scope `NNEMlirTools`)
- L81 _function_ `inline void Release(NNEMlirStatus Sts)` (scope `NNEMlirTools`) — Overloaded Release methods, not possible with C API
- L82 _function_ `inline void Release(NNEMlirContext Ctx)` (scope `NNEMlirTools`)
- L83 _function_ `inline void Release(NNEMlirModule Mod)` (scope `NNEMlirTools`)
- L84 _function_ `inline void Release(NNEMlirFunction Func)` (scope `NNEMlirTools`)
- L85 _function_ `inline void Release(NNEMlirValue Val)` (scope `NNEMlirTools`)
