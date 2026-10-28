# Programs / UnrealPackageTool

- module root: `Source/Programs/UnrealPackageTool`
- headers: 1; symbols: 85
- symbol kinds: class=1, member=10, namespace=3, prototype=66, struct=4, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, CLI11, Core, CoreUObject, Projects, SQLiteCore
- PublicIncludePathModuleNames: Launch

### `Source/Programs/UnrealPackageTool/UnrealPackageTool.h` (Other)


#### struct `UE::PackageTool::FSharedParameters`  
`struct FSharedParameters`  
_L19-24_
- desc: Parameters shared between multiple execution modes
- L21 _public member_ `bool bJSON = false;`
- L23 _public prototype_ `FSharedParameters(CLI::App* InApp);`

#### struct `UE::PackageTool::FSubcommand`  
`struct FSubcommand`  
_L27-36_
- desc: Base class for a subcommand which should be registered as part of UnrealPackageTool to add argument parsing to CLI::App
- L29 _public prototype_ `FSubcommand();`
- L30 _public prototype_ `virtual ~FSubcommand();`
- L33 _public prototype_ `virtual void RegisterSubcommand(FSharedParameters* InShared, CLI::App*) = 0;`
- L35 _public member_ `FSubcommand* Next = nullptr;`

#### struct `UE::PackageTool::FArchiveStdOut`  
`struct FArchiveStdOut : public FArchive`  
_L43-54_
- inherits: `FArchive`
- desc: Utility archive for printing json/package info to stdout
- L45 _public member_ `int64 Pos = 0;`
- L47 _public prototype_ `~FArchiveStdOut();`
- L50 _public prototype_ `virtual void Serialize(void* Data, int64 Len) override;` — Both formatter types provide utf8 text
- L53 _public prototype_ `virtual int64 Tell() override;` — Required for correct formatting of JSON output

#### class `UE::PackageTool::FTextOutputFormatter`  
`class FTextOutputFormatter final : public FStructuredArchiveFormatter`  
_L59-137_
- inherits: `FStructuredArchiveFormatter`
- desc: Structured archive formatter to print column-aligned human readable data. Allows us to share driving code with JSON output The output of this formatter is not indended for parsing/machine consumption
- L61 _private typedef_ `using FBuffer = TUtf8StringBuilder<2048>;`
- L62 _private member_ `static const constexpr int32 IndentWidth = 4;`
- L63 _private member_ `static const constexpr int32 MaxStringLength = 256;`
- L71 _private member_ `FArchive& Ar;`
- L72 _private member_ `TArray<FStackEntry> Stack;`
- L74 _private prototype_ `int32 GetIndent();`
- L75 _private prototype_ `FBuffer& GetValueBuffer();`
- L77 _private prototype_ `void FlushBuffer(FBuffer& Buffer);`
- L78 _private prototype_ `static bool LooksLikeBinary(FStringView View);`
- L79 _private prototype_ `static bool CharNeedsEscaping(TCHAR C);`
- L80 _private prototype_ `static bool NeedsEscaping(FStringView View);`
- L81 _private prototype_ `static void WriteEscaped(FBuffer& Buffer, FStringView View);`
- L84 _public prototype_ `FTextOutputFormatter(FArchive& InAr);`
- L85 _public prototype_ `virtual ~FTextOutputFormatter();`
- L86 _public prototype_ `virtual FArchive& GetUnderlyingArchive() override;`
- L87 _public prototype_ `virtual bool HasDocumentTree() const override;`
- L89 _public prototype_ `virtual void EnterRecord() override;`
- L90 _public prototype_ `virtual void LeaveRecord() override;`
- L91 _public prototype_ `virtual void EnterField(FArchiveFieldName Name) override;`
- L92 _public prototype_ `virtual void LeaveField() override;`
- L93 _public prototype_ `virtual bool TryEnterField(FArchiveFieldName Name, bool bEnterWhenSaving) override;`
- L94 _public prototype_ `virtual void EnterArray(int32& NumElements) override;`
- L95 _public prototype_ `virtual void LeaveArray() override;`
- L96 _public prototype_ `virtual void EnterArrayElement() override;`
- L97 _public prototype_ `virtual void LeaveArrayElement() override;`
- L98 _public prototype_ `virtual void EnterStream() override;`
- L99 _public prototype_ `virtual void LeaveStream() override;`
- L100 _public prototype_ `virtual void EnterStreamElement() override;`
- L101 _public prototype_ `virtual void LeaveStreamElement() override;`
- L102 _public prototype_ `virtual void EnterMap(int32& NumElements) override;`
- L103 _public prototype_ `virtual void LeaveMap() override;`
- L104 _public prototype_ `virtual void EnterMapElement(FString& Name) override;`
- L105 _public prototype_ `virtual void LeaveMapElement() override;`
- L106 _public prototype_ `virtual void EnterAttributedValue() override;`
- L107 _public prototype_ `virtual void EnterAttribute(FArchiveFieldName AttributeName) override;`
- L108 _public prototype_ `virtual void EnterAttributedValueValue() override;`
- L109 _public prototype_ `virtual void LeaveAttribute() override;`
- L110 _public prototype_ `virtual void LeaveAttributedValue() override;`
- L111 _public prototype_ `virtual bool TryEnterAttribute(FArchiveFieldName AttributeName, bool bEnterWhenSaving) override;`
- L112 _public prototype_ `virtual bool TryEnterAttributedValueValue() override;`
- L113 _public prototype_ `virtual void Serialize(uint8& Value) override;`
- L114 _public prototype_ `virtual void Serialize(uint16& Value) override;`
- L115 _public prototype_ `virtual void Serialize(uint32& Value) override;`
- L116 _public prototype_ `virtual void Serialize(uint64& Value) override;`
- L117 _public prototype_ `virtual void Serialize(int8& Value) override;`
- L118 _public prototype_ `virtual void Serialize(int16& Value) override;`
- L119 _public prototype_ `virtual void Serialize(int32& Value) override;`
- L120 _public prototype_ `virtual void Serialize(int64& Value) override;`
- L121 _public prototype_ `virtual void Serialize(float& Value) override;`
- L122 _public prototype_ `virtual void Serialize(double& Value) override;`
- L123 _public prototype_ `virtual void Serialize(bool& Value) override;`
- L124 _public prototype_ `virtual void Serialize(UTF32CHAR& Value) override;`
- L125 _public prototype_ `virtual void Serialize(FString& Value) override;`
- L126 _public prototype_ `virtual void Serialize(FName& Value) override;`
- L127 _public prototype_ `virtual void Serialize(UObject*& Value) override;`
- L128 _public prototype_ `virtual void Serialize(FText& Value) override;`
- L129 _public prototype_ `virtual void Serialize(FWeakObjectPtr& Value) override;`
- L130 _public prototype_ `virtual void Serialize(FSoftObjectPtr& Value) override;`
- L131 _public prototype_ `virtual void Serialize(FSoftObjectPath& Value) override;`
- L132 _public prototype_ `virtual void Serialize(FLazyObjectPtr& Value) override;`
- L133 _public prototype_ `virtual void Serialize(FObjectPtr& Value) override;`
- L134 _public prototype_ `virtual void Serialize(TArray<uint8>& Value) override;`
- L135 _public prototype_ `virtual void Serialize(void* Data, uint64 DataSize) override;`

#### struct `UE::PackageTool::FTextOutputFormatter::FStackEntry`  
`struct FStackEntry`  
_L65-70_
- L67 _public member_ `int32 Indent = 0;`
- L68 _public member_ `TArray<TTuple<FString, FString>> MapEntries;`
- L69 _public member_ `TUniquePtr<FBuffer> ValueBuffer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace CLI`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PackageTool` (scope `UE`)
- L40 _prototype_ `FString ConvertPathParameter(const std::string& InParam);` (scope `UE::PackageTool`) — Convert a utf8 command line parameter to an FString path, treating relative paths as relative to the working directory rather than the engine base dir
