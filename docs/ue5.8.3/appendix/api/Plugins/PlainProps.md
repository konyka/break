# Plugins / PlainProps

- module root: `Plugins/Experimental/PlainProps/Source`
- headers: 37; symbols: 3455
- symbol kinds: class=96, enum=28, enumerator=117, externvar=1, function=1114, macro=38, member=884, namespace=48, prototype=519, struct=344, typedef=161, union=20, variable=85
- PrivateDependencyModuleNames: Core, CorePreciseFP

### `Plugins/Experimental/PlainProps/Source/Internal/PlainPropsInternalPrivateMemberPtr.h` (Internal)


#### Free symbols / members of external scopes

- L8 _macro_ `#define PP_DEFINE_PRIVATE_MEMBER_NAMESPACE_BEGIN(Namespace) \`
- L23 _macro_ `#define PP_DEFINE_PRIVATE_MEMBER_NAMESPACE_END() \`
- L26 _macro_ `#define PP_DEFINE_PRIVATE_MEMBER_PTR(Class, Member, Type) \`

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalBind.h` (Private)


#### struct `PlainProps::FMemberBinderBase`  
`struct FMemberBinderBase`  
_L11-55_
- L13 _public function_ `FMemberBinderBase(FSchemaBinding& InSchema) : Schema(InSchema) , MemberIt(Schema.Members) , RangeTypeIt(const_cast<FMemberBindType*>(Schema.GetInnerRangeTypes())) , OffsetIt(const_cast<uint32*>(Schema.GetOffsets())) , RangeBindingIt(const_cast<FRangeBinding*>(Schema.GetRangeBindings()))`
- L21 _public function_ `~FMemberBinderBase()`
- L29 _public function_ `void AddMember(FMemberBindType Type, uint32 Offset)`
- L35 _public function_ `void AddRange(TConstArrayView<FRangeBinding> Ranges, FMemberBindType InnermostType, uint32 Offset)`
- L50 _public member_ `FSchemaBinding& Schema;`
- L51 _public member_ `FMemberBindType* MemberIt;`
- L52 _public member_ `FMemberBindType* RangeTypeIt;`
- L53 _public member_ `uint32* OffsetIt;`
- L54 _public member_ `FRangeBinding* RangeBindingIt;`

#### struct `PlainProps::FInnerIds`  
`struct FInnerIds`  
_L73-88_
- desc: FSchemaId -> FInnerId lookup, see IndexAllRuntimeIds
- L75 _public member_ `TConstArrayView<FInnerId> Ids;`
- L77 _public function_ `FInnerId operator[](FSchemaId Schema) const`
- L78 _public function_ `FEnumId operator[](FEnumSchemaId Schema) const`
- L79 _public function_ `FDeclId operator[](FStructSchemaId Schema) const`
- L80 _public function_ `FOptionalInnerId operator[](FOptionalSchemaId Schema) const`
- L81 _public function_ `FOptionalEnumId operator[](FOptionalEnumSchemaId Schema) const`
- L82 _public function_ `FOptionalDeclId operator[](FOptionalStructSchemaId Schema) const`
- L84 _public function_ `int32 Num() const`
- L85 _public function_ `TConstArrayView<FDeclId> GetDeclIds(uint32 NumStructs) const`
- L86 _public function_ `TConstArrayView<FStructId> GetStructIds(uint32 NumStructs) const`
- L87 _public function_ `TConstArrayView<FEnumId> GetEnumIds(uint32 NumEnums) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PlainProps`
- L60 _function_ `[[nodiscard]] inline FMemberType ToMemberType(FMemberBindType In)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalBuild.h` (Private)


#### struct `PlainProps::FBuiltStruct`  
`struct FBuiltStruct`  
_L12-18_
- L14 _public prototype_ `~FBuiltStruct() = delete;` — Allocated in FScratchAllocator
- L16 _public member_ `uint16 NumMembers;`
- L17 _public member_ `FBuiltMember Members[0];`

#### struct `PlainProps::FBuiltRange`  
`struct FBuiltRange`  
_L20-33_
- L22 _public prototype_ `~FBuiltRange() = delete;` — Allocated in FScratchAllocator
- L24 _public prototype_ `[[nodiscard]] static FBuiltRange* Create(FScratchAllocator& Scratch, uint64 NumItems, SIZE_T ItemSize);`
- L25 _public prototype_ `[[nodiscard]] static FBuiltRange* Create(FScratchAllocator& Scratch, uint64 NumItems, SIZE_T ItemSize, const void* Items);`
- L26 _public function_ `[[nodiscard]] static FBuiltRange* CreateIf(FScratchAllocator& Scratch, uint64 NumItems, SIZE_T ItemSize, const void* Items)`
- L28 _public member_ `uint64 Num;`
- L29 _public member_ `uint8 Data[0];`
- L31 _public function_ `TConstArrayView64<const FBuiltRange*> AsRanges() const`
- L32 _public function_ `TConstArrayView64<const FBuiltStruct*> AsStructs() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalDiff.h` (Private)


#### struct `PlainProps::FItemRangeReader`  
`struct FItemRangeReader`  
_L83-118_
- desc: Helps diff ranges
- L85 _public function_ `explicit FItemRangeReader(const void* Range, const IItemRangeBinding& Binding) : Ctx`
- L91 _public member_ `FSaveRangeContext Ctx;`
- L92 _public member_ `const uint8* SliceIt = nullptr;`
- L93 _public member_ `uint64 SliceNum = 0;`
- L95 _public function_ `void ReadItems(const IItemRangeBinding& Binding)`
- L102 _public function_ `void RefillItems(const IItemRangeBinding& Binding)`
- L111 _public function_ `const uint8* GrabItems(uint64 Num, uint32 Stride)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L12 _function_ `inline const uint8* At(const void* Ptr, SIZE_T Offset)` (scope `PlainProps`)
- L19 _function_ `template<class RangeTypeA, class RangeTypeB> bool DiffItems(RangeTypeA&& A, RangeTypeB&& B, uint64& OutIdx)` (scope `PlainProps`) — Works with FBoolRangeView, which lack GetData(), TRangeView, TArrayView, std::initializer_list and T[]
- L40 _function_ `inline int64 DiffLeaf(const uint8* A, const uint8* B, FUnpackedLeafBindType Leaf)` (scope `PlainProps`)
- L74 _function_ `inline ELeafWidth GetItemWidth(FLeafBindType Leaf)` (scope `PlainProps`)
- L121 _function_ `template<class ContextType> inline bool DiffItemSlice(const uint8* A, const uint8* B, uint64 Num, uint32 Stride, ContextType&, SIZE_T LeafSize)` (scope `PlainProps`)
- L127 _function_ `template<typename ItemType, class ContextType> bool DiffItemSlice(const uint8* A, const uint8* B, uint64 Num, uint32 Stride, ContextType& Ctx, ItemType&& Member)` (scope `PlainProps`)
- L142 _function_ `template<class T, class ContextType> bool DiffItemRange(const void* RangeA, const void* RangeB, const IItemRangeBinding& Binding, ContextType& OuterCtx, T&& ItemSchema)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalFormat.h` (Private)


#### struct `PlainProps::FSchemaBatch`  
`struct FSchemaBatch`  
_L12-42_
- L14 _public member_ `uint32 NumNestedScopes;`
- L15 _public member_ `uint32 NestedScopesOffset;`
- L16 _public member_ `uint32 NumParametricTypes;`
- L17 _public member_ `uint32 NumSchemas;`
- L18 _public member_ `uint32 NumStructSchemas;`
- L19 _public member_ `uint32 SchemaOffsets[0];`
- L21 _public function_ `TConstArrayView<uint32> GetSchemaOffsets() const`
- L26 _public function_ `TConstArrayView<FNestedScope> GetNestedScopes() const`
- L31 _public function_ `TConstArrayView<FParametricType> GetParametricTypes() const`
- L36 _public function_ `const FType* GetFirstParameter() const`
- L41 _public prototype_ `void ValidateBounds(uint64 NumBytes) const;`

#### enum `PlainProps::ESuper`  
`enum class ESuper : uint8`  
_L59-59_
- desc: Direct super schema id is always written to enable inheritance analysis No		No inheritance Unused	Super member missing, due to all instances being empty Used		Super member exists, but IsDynamic or with a static non-direct ancestor id Reused	Super member exists, with the static id of the direct super struct
- L59 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; inline bool UsesSuper(ESuper Inheritance) { return Inheritance == ESuper::Used || Inheritance == ESuper::Reused; } inline bool SkipDeclaredSuperSchema(ESuper Inheritance) { return Inheritance == ESuper::Unused || Inheritance == ESuper::Used; } struct FStructSchema { FType Type;` — Direct super schema id is always written to enable inheritance analysis No		No inheritance Unused	Super member missing, due to all instances being empty Used		Super member exists, but IsDynamic or with a static non-direct ancestor id Reused	Super member exists, with the static id of the direct super struct
- L59 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; inline bool UsesSuper(ESuper Inheritance) { return Inheritance == ESuper::Used || Inheritance == ESuper::Reused; } inline bool SkipDeclaredSuperSchema(ESuper Inheritance) { return Inheritance == ESuper::Unused || Inheritance == ESuper::Used; } struct FStructSchema { FType Type;` — Direct super schema id is always written to enable inheritance analysis No		No inheritance Unused	Super member missing, due to all instances being empty Used		Super member exists, but IsDynamic or with a static non-direct ancestor id Reused	Super member exists, with the static id of the direct super struct
- L59 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; inline bool UsesSuper(ESuper Inheritance) { return Inheritance == ESuper::Used || Inheritance == ESuper::Reused; } inline bool SkipDeclaredSuperSchema(ESuper Inheritance) { return Inheritance == ESuper::Unused || Inheritance == ESuper::Used; } struct FStructSchema { FType Type;` — Direct super schema id is always written to enable inheritance analysis No		No inheritance Unused	Super member missing, due to all instances being empty Used		Super member exists, but IsDynamic or with a static non-direct ancestor id Reused	Super member exists, with the static id of the direct super struct
- L59 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; inline bool UsesSuper(ESuper Inheritance) { return Inheritance == ESuper::Used || Inheritance == ESuper::Reused; } inline bool SkipDeclaredSuperSchema(ESuper Inheritance) { return Inheritance == ESuper::Unused || Inheritance == ESuper::Used; } struct FStructSchema { FType Type;` — Direct super schema id is always written to enable inheritance analysis No		No inheritance Unused	Super member missing, due to all instances being empty Used		Super member exists, but IsDynamic or with a static non-direct ancestor id Reused	Super member exists, with the static id of the direct super struct

#### struct `PlainProps::FStructSchema`  
`struct FStructSchema`  
_L64-102_
- L66 _public member_ `FType Type;`
- L67 _public member_ `uint16 Version;`
- L68 _public member_ `uint16 NumMembers;`
- L69 _public member_ `uint16 NumRangeTypes;`
- L70 _public member_ `uint16 NumInnerSchemas;`
- L71 _public member_ `ESuper Inheritance : 2;`
- L72 _public member_ `uint8 IsDense : 1;`
- L73 _public member_ `FMemberType Footer[0];`
- L75 _public function_ `inline uint32 NumNames() const`
- L76 _public function_ `TConstArrayView<FMemberType> GetMemberTypes() const`
- L77 _public function_ `TConstArrayView<FMemberType> GetRangeTypes() const`
- L78 _public function_ `TConstArrayView<FMemberId> GetMemberNames() const`
- L79 _public function_ `TArrayView<FMemberId> EditMemberNames()`
- L80 _public function_ `const FSchemaId* GetInnerSchemas() const`
- L81 _public function_ `FOptionalStructSchemaId GetSuper() const`
- L83 _public function_ `static const FMemberType* GetMemberTypes(const FMemberType* Footer)`
- L88 _public function_ `static const FMemberType* GetRangeTypes(const FMemberType* Footer, uint32 NumMembers)`
- L93 _public function_ `static const FMemberId* GetMemberNames(const FMemberType* Footer, uint32 NumMembers, uint32 NumRangeTypes)`
- L98 _public function_ `static const FSchemaId* GetInnerSchemas(const FMemberType* Footer, uint32 NumMembers, uint32 NumRangeTypes, uint32 NumNames)`

#### struct `PlainProps::FEnumSchema`  
`struct FEnumSchema`  
_L125-133_
- L127 _public member_ `FType Type;`
- L128 _public member_ `uint8 FlagMode : 1;`
- L129 _public member_ `uint8 ExplicitConstants : 1;` — 0,1,2,3,4.. or 1,2,4,8..
- L130 _public member_ `ELeafWidth Width;`
- L131 _public member_ `uint16 Num;`
- L132 _public member_ `FNameId Footer[0];`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlainProps`
- L45 _prototype_ `static_assert(offsetof(FSchemaBatch, NumNestedScopes) == 0, "Add` (scope `PlainProps`)
- L46 _prototype_ `static_assert(offsetof(FSchemaBatch, NestedScopesOffset) == 4, "Add` (scope `PlainProps`)
- L47 _prototype_ `static_assert(offsetof(FSchemaBatch, NumParametricTypes) == 8, "Add` (scope `PlainProps`)
- L48 _prototype_ `static_assert(offsetof(FSchemaBatch, NumSchemas) == 12, "Add` (scope `PlainProps`)
- L49 _prototype_ `static_assert(offsetof(FSchemaBatch, NumStructSchemas) == 16, "Add` (scope `PlainProps`)
- L61 _function_ `inline bool UsesSuper(ESuper Inheritance)` (scope `PlainProps`)
- L62 _function_ `inline bool SkipDeclaredSuperSchema(ESuper Inheritance)` (scope `PlainProps`)
- L105 _prototype_ `static_assert(offsetof(FStructSchema, Type) == 0, "Add` (scope `PlainProps`)
- L106 _prototype_ `static_assert(offsetof(FType, Scope) == 0, "Add` (scope `PlainProps`)
- L107 _prototype_ `static_assert(offsetof(FType, Name) == 4, "Add` (scope `PlainProps`)
- L108 _prototype_ `static_assert(offsetof(FStructSchema, Version) == 8, "Add` (scope `PlainProps`)
- L109 _prototype_ `static_assert(offsetof(FStructSchema, NumMembers) == 10, "Add` (scope `PlainProps`)
- L110 _prototype_ `static_assert(offsetof(FStructSchema, NumRangeTypes) == 12, "Add` (scope `PlainProps`)
- L111 _prototype_ `static_assert(offsetof(FStructSchema, NumInnerSchemas) == 14, "Add` (scope `PlainProps`)
- L112 _prototype_ `static_assert(offsetof(FStructSchema, Footer) == 17, "Add` (scope `PlainProps`)
- L114 _function_ `inline uint32 CalculateSize(const FStructSchema& In)` (scope `PlainProps`)
- L136 _prototype_ `static_assert(offsetof(FEnumSchema, Type) == 0, "Add` (scope `PlainProps`)
- L137 _prototype_ `static_assert(offsetof(FEnumSchema, Width) == 9, "Add` (scope `PlainProps`)
- L138 _prototype_ `static_assert(offsetof(FEnumSchema, Num) == 10, "Add` (scope `PlainProps`)
- L139 _prototype_ `static_assert(offsetof(FEnumSchema, Footer) == 12, "Add` (scope `PlainProps`)
- L141 _function_ `inline uint32 CalculateSize(const FEnumSchema& In)` (scope `PlainProps`)
- L147 _function_ `template<typename T> TConstArrayView<T> GetConstants(const FEnumSchema& In) requires (UnsignedIntegral<T> || Enumeration<T>)` (scope `PlainProps`)
- L154 _function_ `inline bool IsEnum(FMemberType Type)` (scope `PlainProps`)
- L159 _function_ `inline bool IsStructOrEnum(FMemberType Type)` (scope `PlainProps`)
- L164 _function_ `inline bool IsSuper(FMemberType Type)` (scope `PlainProps`)
- L169 _function_ `inline constexpr uint64 GetLeafRangeSize(uint64 Num, FUnpackedLeafType Leaf)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalParse.h` (Private)


#### enum `PlainProps::EToken`  
`enum class EToken : uint8`  
_L27-39_
- L29 _public enumerator_ `Invalid`
- L30 _public enumerator_ `BeginDocument`
- L31 _public enumerator_ `EndDocument`
- L32 _public enumerator_ `BeginStruct`
- L33 _public enumerator_ `EndStruct`
- L34 _public enumerator_ `BeginRange`
- L35 _public enumerator_ `EndRange`
- L36 _public enumerator_ `LeafId`
- L37 _public enumerator_ `LeafValue`
- L38 _public enumerator_ `Leaf`

#### struct `PlainProps::FToken`  
`struct FToken`  
_L41-62_
- L43 _public prototype_ `FToken() = default;`
- L45 _public function_ `FToken(EToken InToken, uint16 InDepth) : Token(InToken), Depth(InDepth)`
- L47 _public function_ `FToken(EToken InToken, uint16 InDepth, FUtf8StringView InView) : Str(InView.GetData()), Len(InView.Len()), Token(InToken), Depth(InDepth)`
- L51 _public function_ `inline FUtf8StringView Value() const`
- L53 _public function_ `inline bool operator==(FToken O) const`
- L58 _public member_ `const UTF8CHAR* Str = nullptr;`
- L59 _public member_ `int32 Len = 0;`
- L60 _public member_ `EToken Token = EToken::Invalid;`
- L61 _public member_ `uint16 Depth = 0;`

#### struct `PlainProps::FParsedMemberSchema`  
`struct FParsedMemberSchema`  
_L66-71_
- L68 _public member_ `FMemberType Type;`
- L69 _public member_ `FOptionalInnerId InnerSchema;`
- L70 _public member_ `TArray<FMemberType> InnerRangeTypes;`

#### struct `PlainProps::FParsedStructSchema`  
`struct FParsedStructSchema`  
_L73-81_
- L75 _public member_ `FDeclId Id;`
- L76 _public member_ `uint16 Version = 0;`
- L77 _public member_ `FOptionalDeclId DeclaredSuper;`
- L78 _public member_ `FOptionalDeclId UsedSuper;`
- L79 _public member_ `TConstArrayView<FMemberId> MemberNames;` — FStructDeclaration.MemberOrder
- L80 _public member_ `TArray<FParsedMemberSchema> MemberSchemas;` — Same size as declared member names

#### struct `PlainProps::FParsedEnumSchema`  
`struct FParsedEnumSchema`  
_L83-88_
- L85 _public member_ `FEnumId Id;`
- L86 _public member_ `ELeafWidth Width;`
- L87 _public member_ `TConstArrayView<FEnumerator> Enumerators;` — FEnumDeclaration.Enumerators

#### struct `PlainProps::FParsedSchemas`  
`struct FParsedSchemas`  
_L92-96_
- L94 _public member_ `TArray<FParsedStructSchema> Structs;` — Same size as number of parsed and declared structs
- L95 _public member_ `TArray<FParsedEnumSchema> Enums;` — Same size as number of parsed and declared enums

#### class `PlainProps::FSensitiveUtf8View`  
`class FSensitiveUtf8View : public FUtf8StringView`  
_L99-120_
- inherits: `FUtf8StringView`
- L102 _public function_ `FSensitiveUtf8View(FUtf8StringView View) : FUtf8StringView(View)`

#### class `PlainProps::FTextIndexer`  
`class FTextIndexer : public TIdIndexer<FSensitiveUtf8View>`  
_L122-154_
- inherits: `TIdIndexer<FSensitiveUtf8View>`
- L125 _public function_ `FOptionalMemberId GetMemberId(FUtf8StringView Name)`
- L135 _public function_ `FOptionalDeclId GetStructId(FType Type) const`
- L145 _public function_ `FOptionalEnumId GetEnumId(FType Type) const`

#### struct `PlainProps::FTypeTokens`  
`struct FTypeTokens`  
_L158-163_
- L160 _public member_ `FUtf8StringView Typename;`
- L161 _public member_ `TArray<FUtf8StringView> Scopes;`
- L162 _public member_ `TArray<FTypeTokens> Parameters;`

#### struct `PlainProps::FParseDeclarations`  
`struct FParseDeclarations final : IDeclarations`  
_L173-186_
- inherits: `IDeclarations`
- L175 _public function_ `explicit FParseDeclarations(FDebugIds Dbg) : Enums(Dbg)`
- L177 _public function_ `const FEnumDeclaration& Get(FEnumId Id)`
- L178 _public function_ `const FStructDeclaration& Get(FDeclId Id)`
- L180 _public prototype_ `virtual FDeclId Lower(FBindId Id) const override final;`
- L181 _public function_ `virtual const FEnumDeclaration* Find(FEnumId Id) const override`
- L182 _public prototype_ `virtual const FStructDeclaration* Find(FStructId Id) const override;`
- L184 _public member_ `FEnumDeclarations Enums;`
- L185 _public member_ `FStructDeclarations Structs;`

#### class `PlainProps::FBatchParser`  
`class FBatchParser`  
_L188-215_
- L191 _public function_ `FBatchParser(FMarkupTokenizer& InTokenizer, FScratchAllocator& InScratch) : Tokenizer(InTokenizer), Scratch(InScratch), Types(FDebugIds(Names))`
- L195 _public prototype_ `void Parse(TArray64<uint8>& Out);`
- L198 _private prototype_ `void Tokenize();`
- L199 _private prototype_ `void ParseAll();`
- L200 _private prototype_ `void ParseStructSchemas(TConstArrayView64<FToken> TokensView);`
- L201 _private prototype_ `void ParseEnumSchemas(TConstArrayView64<FToken> TokensView);`
- L202 _private prototype_ `void ParseObjects(TConstArrayView64<FToken> TokensView);`
- L203 _private prototype_ `void Write(TArray64<uint8>& Out);`
- L205 _private member_ `FMarkupTokenizer& Tokenizer;`
- L206 _private member_ `FScratchAllocator& Scratch;`
- L207 _private member_ `FTextIndexer Names;`
- L208 _private member_ `FParseDeclarations Types;`
- L209 _private member_ `TArray<TTuple<FStructId, FBuiltStruct*>> Objects;`
- L210 _private member_ `FParsedSchemas Schemas;`
- L211 _private member_ `TArray64<FToken> Tokens;`
- L212 _private member_ `int64 EnumsIdx = -1;`
- L213 _private member_ `int64 StructsIdx = -1;`
- L214 _private member_ `int64 ObjectsIdx = -1;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace PlainProps`
- L104 _function_ `friend inline bool operator==(FSensitiveUtf8View Lhs, FSensitiveUtf8View Rhs)` (scope `PlainProps`)
- L108 _function_ `friend inline uint32 GetTypeHash(FSensitiveUtf8View View)` (scope `PlainProps`)
- L112 _function_ `friend inline bool operator!=(FSensitiveUtf8View Lhs, FSensitiveUtf8View Rhs)` (scope `PlainProps`)
- L116 _function_ `friend inline bool operator<(FSensitiveUtf8View Lhs, FSensitiveUtf8View Rhs)` (scope `PlainProps`)
- L165 _prototype_ `TOptional<FTypeTokens> TokenizeType(FUtf8StringView String);` (scope `PlainProps`)
- L167 _prototype_ `FType MakeType(const FTypeTokens& TypeTokens, FTextIndexer& Names);` (scope `PlainProps`)
- L171 _typedef_ `using FStructDeclarations = TArray<FStructDeclarationPtr>;` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalPrint.h` (Private)


#### struct `PlainProps::FMarkupBuilderDeleter`  
`struct FMarkupBuilderDeleter`  
_L26-29_
- L28 _public prototype_ `void operator()(FMarkupBuilder* Ptr) const;`

#### class `PlainProps::FBatchPrinter`  
`class FBatchPrinter`  
_L38-56_
- L41 _public prototype_ `FBatchPrinter(FMarkupBuilder& InMarkupBuilder, const FBatchIds& InIds);`
- L42 _public prototype_ `~FBatchPrinter();`
- L44 _public prototype_ `void PrintSchemas();`
- L45 _public prototype_ `void PrintObjects(TConstArrayView<FStructView> Structs);`
- L48 _private prototype_ `void PrintStructSchema(const FStructSchema& Struct, FSchemaBatchId BatchId);`
- L49 _private prototype_ `void PrintEnumSchema(const FEnumSchema& Enum);`
- L52 _private prototype_ `template<typename IntType> void PrintEnumConstants(TConstArrayView<FNameId> EnumNames, TConstArrayView<IntType> Constants, bool bFlagMode);`
- L54 _private member_ `FMarkupBuilder& MarkupBuilder;`
- L55 _private member_ `const FBatchIds& Ids;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PlainProps`
- L19 _function_ `inline TStringBuilderWithBuffer<TCHAR, 128> Print(FUtf8StringView View)` (scope `PlainProps`)
- L30 _typedef_ `using FYamlBuilderPtr = TUniquePtr<FMarkupBuilder, FMarkupBuilderDeleter>;` (scope `PlainProps`)
- L31 _typedef_ `using FJsonBuilderPtr = TUniquePtr<FMarkupBuilder, FMarkupBuilderDeleter>;` (scope `PlainProps`)
- L33 _prototype_ `[[nodiscard]] FYamlBuilderPtr MakeYamlBuilder(FUtf8StringBuilderBase& StringBuilder);` (scope `PlainProps`)
- L34 _prototype_ `[[nodiscard]] FJsonBuilderPtr MakeJsonBuilder(FUtf8StringBuilderBase& StringBuilder);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalRead.h` (Private)


#### struct `PlainProps::TSchemaIterator`  
`template<class T> struct TSchemaIterator`  
_L73-81_
- L75 _public member_ `uintptr_t Base;`
- L76 _public member_ `const uint32* OffsetIt;`
- L78 _public function_ `void operator++()`
- L79 _public function_ `bool operator!=(TSchemaIterator O) const`
- L80 _public function_ `T& operator*() const`

#### struct `PlainProps::TSchemaRange`  
`template<class T> struct TSchemaRange`  
_L84-104_
- L86 _public member_ `static constexpr bool bStructSchema = std::is_convertible_v<T, FStructSchema>;`
- L88 _public function_ `TSchemaRange(std::conditional_t<std::is_const_v<T>, const FSchemaBatch&, FSchemaBatch&> Batch) : Base(reinterpret_cast<uintptr_t>(&Batch)) , Offsets(Batch.SchemaOffsets + (bStructSchema ? 0 : Batch.NumStructSchemas), bStructSchema ? Batch.NumStructSchemas : Batch.NumSchemas - Batch.NumStructSchemas)`
- L95 _public function_ `TSchemaIterator<T> begin() const`
- L96 _public function_ `TSchemaIterator<T> end() const`
- L97 _public function_ `T& First() const`
- L98 _public function_ `T& Last() const`
- L99 _public function_ `T& operator[](uint32 Idx) const`
- L100 _public function_ `int32 Num() const`
- L102 _public member_ `uintptr_t Base;`
- L103 _public member_ `TConstArrayView<uint32> Offsets;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlainProps`
- L13 _function_ `inline FUnpackedLeafType GetType(FLeafRangeView Range)` (scope `PlainProps`)
- L14 _function_ `inline const uint8* GetValues(FLeafRangeView Range)` (scope `PlainProps`)
- L15 _function_ `inline FRangeSchema GetSchema(FRangeView Range)` (scope `PlainProps`)
- L16 _function_ `inline FMemoryView GetValues(FRangeView Range)` (scope `PlainProps`)
- L18 _function_ `inline FOptionalEnumSchemaId GetEnumSchemaId(FLeafRangeView Range)` (scope `PlainProps`)
- L24 _function_ `template<typename MemberType, typename IndexType> TConstArrayView<MemberType> GrabInnerRangeTypes(TConstArrayView<MemberType> InnerRangeTypes, IndexType& InOutIdx)` (scope `PlainProps`)
- L34 _function_ `inline uint64 GrabRangeNum(ESizeType MaxSize, FByteReader& ByteIt, FBitCacheReader& BitIt)` (scope `PlainProps`)
- L52 _function_ `inline FMemoryView GrabRangeValues(uint64 Num, FMemberType InnerType, FByteReader& ByteIt)` (scope `PlainProps`)
- L63 _function_ `inline FMemberType GetInnermostType(FRangeSchema Schema)` (scope `PlainProps`)
- L106 _function_ `inline TSchemaRange<FEnumSchema> GetEnumSchemas(FSchemaBatch& Batch)` (scope `PlainProps`)
- L107 _function_ `inline TSchemaRange<const FEnumSchema> GetEnumSchemas(const FSchemaBatch& Batch)` (scope `PlainProps`)
- L108 _function_ `inline TSchemaRange<FStructSchema> GetStructSchemas(FSchemaBatch& Batch)` (scope `PlainProps`)
- L109 _function_ `inline TSchemaRange<const FStructSchema> GetStructSchemas(const FSchemaBatch& Batch)` (scope `PlainProps`)
- L113 _prototype_ `const FSchemaBatch& GetReadSchemas(FSchemaBatchId Batch);` (scope `PlainProps`)
- L115 _function_ `inline const FStructSchema& ResolveStructSchema(const FSchemaBatch& Batch, FSchemaId Id)` (scope `PlainProps`)
- L121 _function_ `inline const FEnumSchema& ResolveEnumSchema(const FSchemaBatch& Batch, FSchemaId Id)` (scope `PlainProps`)
- L127 _function_ `inline FNestedScope ResolveNestedScope(const FSchemaBatch& Batch, FNestedScopeId Id)` (scope `PlainProps`)
- L132 _function_ `inline FParametricTypeView ResolveParametricType(const FSchemaBatch& Batch, FParametricTypeId Id)` (scope `PlainProps`)
- L140 _function_ `inline FMemoryView GetSchemaData(const FSchemaBatch& Batch)` (scope `PlainProps`)
- L155 _function_ `template<typename T> auto GetEnd(T&& Container)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalTest.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L15 _prototype_ `[[nodiscard]] FSchemaBatchId ParseYamlBatch(TArray64<uint8>& OutData, TArray<FStructView>& OutObjects, FUtf8StringView YamlView);` (scope `PlainProps`)
- L16 _prototype_ `[[nodiscard]] FSchemaBatchId ParseJsonBatch(TArray64<uint8>& OutData, TArray<FStructView>& OutObjects, FUtf8StringView JsonView);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalText.h` (Private)


#### struct `PlainProps::FLiterals`  
`struct FLiterals`  
_L11-55_
- L15 _public member_ `FAnsiStringView Structs = "St`
- L16 _public member_ `FAnsiStringView Enums = "En`
- L17 _public member_ `FAnsiStringView Objects = "Ob`
- L19 _public member_ `FAnsiStringView Version = "Ve`
- L20 _public member_ `FAnsiStringView DeclaredSuper = "Su`
- L21 _public member_ `FAnsiStringView Width = "Wi`
- L22 _public member_ `FAnsiStringView FlagMode = "Fl`
- L23 _public member_ `FAnsiStringView Constants = "Co`
- L24 _public member_ `FAnsiStringView Members = "Me`
- L26 _public member_ `FAnsiStringView True = "tr`
- L27 _public member_ `FAnsiStringView False = "fa`
- L29 _public member_ `FAnsiStringView Super = "__`
- L30 _public member_ `FAnsiStringView Dynamic = "__`
- L32 _public member_ `FAnsiStringView UnsetFlagEnum = "!U`
- L34 _public member_ `FAnsiStringView Oob = "ER`
- L36 _public member_ `FAnsiStringView Kinds[3] = { ("Leaf"), ("Struct"`
- L38 _public member_ `FAnsiStringView Ranges[9] = { ("Uni"), ("i8"), ("u8"), ("i16"), ("u16"), ("i32"), ("u`
- L41 _public member_ `FAnsiStringView RangeTypes[9] = { ("(Uni)"), ("(i8)"), ("(u8)"), ("(i16)"), ("(u16)"), ("`
- L44 _public member_ `FAnsiStringView Leaves[8][4] = { {("bool"), ("ERR!b16"), ("ERR!b32"), ("ERR!b64")}, {("i8"), ("i16"), ("i32"), ("i64")}, {("u8"), ("u16"), ("u32"), ("u64")}, {("ERR!fp8"), ("ERR!fp16"), ("float"), ("double")}, {("hex8"), ("hex16"), ("hex32"), ("hex64")}, {("enum8"), ("enum16"), ("enum32"), ("enum64")}, {("utf8"), ("utf16"), ("utf32"), ("ERR!utf64")}, {Oob, Oob, Oob, Oob}};`
- L54 _public member_ `FAnsiStringView Widths[4] = { ("u8"), ("u16"), ("u32"),`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PlainProps`
- L56 _externvar_ `extern const FLiterals GLiterals;` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Private/PlainPropsInternalUpgrade.h` (Private)


#### struct `PlainProps::Upgrade::FEnumeratorIndexer`  
`struct FEnumeratorIndexer : private TSet<FNameId>`  
_L27-34_
- inherits: `TSet<FNameId>`
- L29 _public function_ `FEnumeratorIndexer()`
- L30 _public function_ `FEnumeratorIndexer(TSet<FNameId>&& DeclaredOrder) : TSet<FNameId>(MoveTemp(DeclaredOrder))`
- L32 _public function_ `FEnumeratorId Index(FNameId Member)`
- L33 _public function_ `FNameId Resolve(FEnumeratorId Parameter) const`

#### struct `PlainProps::Upgrade::FParameterIndexer`  
`struct FParameterIndexer : private FParameterIdSet`  
_L37-49_
- inherits: `FParameterIdSet`
- L39 _public function_ `FParameterIndexer()`
- L40 _public function_ `FParameterIndexer(FParameterIdSet&& DeclaredOrder) : FParameterIdSet(MoveTemp(DeclaredOrder))`
- L42 _public function_ `FParameterId Index(FMemberId Member)`
- L43 _public function_ `FParameterId Index(FOptionalMemberId Member)`
- L44 _public function_ `FParameterId IndexSuper()`
- L47 _public function_ `FOptionalMemberId Resolve(FParameterId Parameter) const` — FParameterId		Reindex(FOptionalMemberId Member) const;
- L48 _public function_ `uint32 Num() const`

#### class `PlainProps::Upgrade::FLooseIndexers`  
`class FLooseIndexers`  
_L51-67_
- L54 _public function_ `FLooseIndexers(const IDeclarations& Types) : Declarations(Types)`
- L56 _public prototype_ `FEnumeratorIndexer& Get(FEnumId Id);`
- L57 _public prototype_ `FParameterIndexer& Get(FDeclId Id);`
- L58 _public function_ `const FEnumeratorIndexer& Get(FEnumId Id) const`
- L59 _public function_ `const FParameterIndexer& Get(FDeclId Id) const`
- L64 _private member_ `TMap<FDeclId, TUniquePtr<FParameterIndexer>> Structs;`
- L65 _private member_ `TMap<FEnumId, TUniquePtr<FEnumeratorIndexer>> Enums;`
- L66 _private member_ `const IDeclarations& Declarations;`

#### struct `PlainProps::Upgrade::FLooseParameter`  
`struct FLooseParameter`  
_L71-75_
- L73 _public member_ `FParameterId Name;`
- L74 _public member_ `FLooseType Type;`

#### struct `PlainProps::Upgrade::FOutParameter`  
`struct FOutParameter`  
_L80-86_
- L82 _public member_ `FParameterId Name;`
- L83 _public member_ `uint8 NumInners = 0;` — Named struct members or enumerators/flags
- L84 _public member_ `uint8 RecompIdx = 0;` — Only for enums with NumInners > 0
- L85 _public member_ `FLooseType Type;`

#### struct `PlainProps::Upgrade::FLooseSchema`  
`struct FLooseSchema`  
_L90-97_
- L92 _public member_ `uint16 Version = 0;`
- L93 _public member_ `uint16 NumMembers = 0;`
- L94 _public member_ `FLooseParameter Members[0];` — Including super
- L96 _public function_ `TConstArrayView<FLooseParameter> GetMembers() const`

#### enum `PlainProps::Upgrade::ELooseState`  
`enum class ELooseState : uint8`  
_L102-102_
- desc: FLooseMetadata::IsSet, IsFullyUpgraded and !!InnermostSchema
- L102 _public enumerator_ `enum class ELooseState : uint8 { Unset, Source, Loose, UpgradedLoose }; struct FStructMember { FDeclId Id; FOptionalStructSchemaId Schema; FParameterId Name;` — FLooseMetadata::IsSet, IsFullyUpgraded and !!InnermostSchema
- L102 _public enumerator_ `enum class ELooseState : uint8 { Unset, Source, Loose, UpgradedLoose }; struct FStructMember { FDeclId Id; FOptionalStructSchemaId Schema; FParameterId Name;` — FLooseMetadata::IsSet, IsFullyUpgraded and !!InnermostSchema
- L102 _public enumerator_ `enum class ELooseState : uint8 { Unset, Source, Loose, UpgradedLoose }; struct FStructMember { FDeclId Id; FOptionalStructSchemaId Schema; FParameterId Name;` — FLooseMetadata::IsSet, IsFullyUpgraded and !!InnermostSchema
- L102 _public enumerator_ `enum class ELooseState : uint8 { Unset, Source, Loose, UpgradedLoose }; struct FStructMember { FDeclId Id; FOptionalStructSchemaId Schema; FParameterId Name;` — FLooseMetadata::IsSet, IsFullyUpgraded and !!InnermostSchema

#### struct `PlainProps::Upgrade::FStructMember`  
`struct FStructMember`  
_L105-115_
- desc: Struct-specific loose member
- L107 _public member_ `FDeclId Id;`
- L108 _public member_ `FOptionalStructSchemaId Schema;` — @invariant !!Schema == (State == ELooseState::Source)
- L109 _public member_ `FParameterId Name;`
- L110 _public member_ `uint16 Version;`
- L111 _public member_ `ELooseState State;`
- L112 _public member_ `EMismatch Mismatch;`
- L113 _public member_ `uint64 Num;` — Num loose members or FByteReader::CheckableBytes (0 in shipping config)
- L114 _public member_ `FStructData Data;`

#### struct `PlainProps::Upgrade::FEnumMember`  
`struct FEnumMember`  
_L118-128_
- desc: Enum-specific loose member
- L120 _public member_ `FEnumId Id;`
- L121 _public member_ `FOptionalEnumSchemaId Schema;`
- L122 _public member_ `FParameterId Name;`
- L123 _public member_ `uint16 Version;`
- L124 _public member_ `ELooseState State;`
- L125 _public member_ `uint8 FlagMode : 1;`
- L126 _public member_ `uint16 Num;`
- L127 _public member_ `FEnumData Data;`

#### struct `PlainProps::Upgrade::FRangeMember`  
`struct FRangeMember`  
_L131-136_
- desc: Range-specific loose member
- L133 _public member_ `FLooseType Type;`
- L134 _public member_ `FLooseMetadata Meta;`
- L135 _public member_ `FRangeData Data;`

#### struct `PlainProps::Upgrade::FLooseStruct`  
`struct FLooseStruct`  
_L141-147_
- desc: Nameless loosened struct
- L143 _public member_ `FDeclId Id;`
- L144 _public member_ `uint16 Version;`
- L145 _public member_ `uint16 Num;`
- L146 _public member_ `FLooseMember* Members;`

#### class `PlainProps::Upgrade::FEnumLooseners`  
`class FEnumLooseners`  
_L151-160_
- L153 _private member_ `const FEnumTransformation* Data;`
- L154 _private member_ `uint32 NumStructs;`
- L155 _private member_ `uint32 NumSchemas;`
- L158 _public prototype_ `FEnumLooseners(TConstArrayView<FEnumTransformation> Xforms, uint32 InNumStructs);`
- L159 _public prototype_ `const FEnumLoosener& operator[](FEnumSchemaId Id) const;`

#### class `PlainProps::Upgrade::FLooseMemberReader`  
`class FLooseMemberReader : protected FMemberReader`  
_L165-181_
- inherits: `FMemberReader`
- desc: Source struct reader producing loose members
- L168 _public prototype_ `FLooseMemberReader(const FLooseSchema& LooseSchema, FStructView Source, FEnumLooseners InLooseners, FScratchAllocator& InScratch);`
- L171 _public prototype_ `FLooseParameter Peek() const;` — @pre HasMore()
- L172 _public prototype_ `FLooseValue Grab();` — @pre HasMore()
- L175 _private member_ `const FLooseParameter* Parameters;`
- L176 _private member_ `FScratchAllocator& Scratch;`
- L177 _private member_ `FEnumLooseners Looseners;`
- L179 _private prototype_ `FRangeMember ToLooseRange(FParameterId Name, FLooseType Type, FRangeView Range);`
- L180 _private prototype_ `FLooseNestedRange* LoosenRanges(FNestedRangeView Range);`

#### class `PlainProps::Upgrade::FOptionalVersion`  
`class FOptionalVersion`  
_L185-195_
- L187 _private member_ `uint16 No = 0xFFFF;`
- L189 _public prototype_ `FOptionalVersion() = default;`
- L190 _public function_ `FOptionalVersion(FNullOpt)`
- L191 _public function_ `FOptionalVersion(uint16 Version) : No(Version)`
- L193 _public function_ `explicit operator bool() const`
- L194 _public function_ `uint16 Get() const`

#### struct `PlainProps::Upgrade::FMiniSlice`  
`struct FMiniSlice`  
_L200-206_
- desc: Small index range, max 255 items of a max 16.7M item range
- L202 _public function_ `FMiniSlice(uint32 I, uint32 N) : Idx(I), Num(N)`
- L204 _public member_ `uint32 Idx : 24;`
- L205 _public member_ `uint32 Num : 8;`

#### struct `PlainProps::Upgrade::FOp`  
`struct FOp`  
_L209-218_
- desc: Compiled op and metadata
- L211 _public member_ `Op Function;`
- L212 _public member_ `FMiniSlice Outputs;`
- L213 _public member_ `uint8 NumOptionalInputs;`
- L214 _public member_ `uint8 NumRequiredInputs;`
- L215 _public member_ `uint16 OptionalInputIdx;`
- L217 _public function_ `int32 NumInputs() const`

#### union `PlainProps::Upgrade::FMatchIdx`  
`union FMatchIdx`  
_L220-224_
- L222 _public member_ `uint16 Op;`
- L223 _public member_ `uint16 Decomp;`

#### struct `PlainProps::Upgrade::FMemberMatch`  
`struct FMemberMatch`  
_L226-236_
- L228 _public member_ `FLooseType Type;` — With Innermost.IsDecomposed == 0
- L229 _public member_ `FMatchIdx Idx;`
- L230 _public member_ `uint8 InputIdx;`
- L231 _public member_ `uint8 Recipient;` — 0 = this, 1 = Outer, 2 = Outer->Outer, ...
- L233 _public function_ `bool Decomposes() const`
- L235 _public member_ `static constexpr uint8 DecomposeRecipient = 0xFF;`

#### struct `PlainProps::Upgrade::FStructUpgrades`  
`struct FStructUpgrades`  
_L239-249_
- desc: Compiled upgrades for all versions of a particular struct
- L243 _public member_ `FDeclId Id;`
- L244 _public member_ `FDeclId FinalId;` — Potentially renamed struct name
- L245 _public member_ `uint16 FinalVersion;` — Potentially renamed struct version
- L246 _public member_ `uint16 FirstVersion;` — First Relevant version
- L247 _public member_ `uint16 NumVersions;` — Versions are contiguous but can start at >0
- L248 _public member_ `const FVersionUpgrades* Versions[0];` — Indexed by Version - FirstVersion

#### struct `PlainProps::Upgrade::FVersionUpgrades`  
`struct FVersionUpgrades`  
_L252-275_
- desc: Compiled upgrades for a particular struct version and set of overrides
- L256 _public member_ `uint32 OutputsOffset;` — Using offsets at the end to access Outputs faster
- L257 _public member_ `uint32 NumNames;` — Declared and renamed members, duplicated across versions for simplicity
- L258 _public member_ `uint32 NumMatches;`
- L259 _public member_ `uint16 NumOps;`
- L260 _public member_ `uint16 NumDecompositions;` — Struct / enum inputs with named members / enumerators / flags
- L261 _public member_ `uint16 NumRecompositions;` — Enum outputs with named enumerators / flags
- L262 _public member_ `uint16 NumOptionalInputs;` — Total optional inputs, enables type-checking missing optional inputs
- L263 _public member_ `FOptionalVersion NextVersion;` — Next version for this OR renamed struct
- L264 _public member_ `FMiniSlice NameMatches[0];` — #NumNames
- L267 _public function_ `template<class T> const T& At(uint32 Offset) const`
- L269 _public function_ `const FMemberMatch* GetMatches() const`
- L270 _public function_ `const FOp* GetOps() const`
- L271 _public function_ `const uint32* GetDecompOffsets() const`
- L272 _public function_ `const FLooseParameter* GetOptionalInputs() const`
- L273 _public function_ `const uint16* GetRecompJumps() const`
- L274 _public function_ `const FOutParameter* GetOutputs() const`

#### struct `PlainProps::Upgrade::FFlatEnumLoosener`  
`struct FFlatEnumLoosener`  
_L280-284_
- desc: Source constant -> loose value
- L283 _public member_ `TMap<uint64, FEnumeratorId> ConstantNames;` — todo: either track and destroy loosener or change to hashtable w/o internal allocation (e.g. null/footer container allocator, some fixed hash map) or sorted array lookup

#### struct `PlainProps::Upgrade::FFlagEnumLoosener`  
`struct FFlagEnumLoosener`  
_L287-290_
- desc: Source flag -> loose value
- L289 _public member_ `TStaticArray<FEnumeratorId, 64> FlagNames{FEnumeratorId{}};`

#### class `PlainProps::Upgrade::FEnumLoosener`  
`class FEnumLoosener`  
_L293-316_
- desc: Helps convert source enums to loose or indicate that declaration matches source schema
- L295 _private member_ `static constexpr uint64 NeededBit = 1;`
- L296 _private member_ `static constexpr uint64 FlagBit = 2;`
- L297 _private member_ `static constexpr uint64 PtrMask = ~(FlagBit | NeededBit);`
- L298 _private member_ `uint64 Ptr = 0;`
- L300 _private function_ `FEnumLoosener(const void* Loosener, uint64 Flags) : Ptr(Flags | reinterpret_cast<uint64>(Loosener))`
- L302 _public function_ `FEnumLoosener()`
- L303 _public function_ `FEnumLoosener(FEnumLoosener&& O) : Ptr(O.Ptr)`
- L304 _public prototype_ `FEnumLoosener(const FEnumLoosener&) = delete;`
- L305 _public function_ `FEnumLoosener(bool bNeeded, FFlatEnumLoosener* Flat UE_LIFETIMEBOUND) : FEnumLoosener(Flat, bNeeded * NeededBit)`
- L306 _public function_ `FEnumLoosener(bool bNeeded, const FFlagEnumLoosener& Flag UE_LIFETIMEBOUND) : FEnumLoosener(&Flag, bNeeded * NeededBit | FlagBit)`
- L307 _public prototype_ `~FEnumLoosener();`
- L308 _public function_ `FEnumLoosener& operator=(FEnumLoosener&& O)`
- L309 _public prototype_ `FEnumLoosener& operator=(const FEnumLoosener&) = delete;`
- L311 _public function_ `bool Exists() const`
- L312 _public function_ `bool Needed() const`
- L313 _public function_ `bool IsFlag() const`
- L314 _public function_ `const FFlagEnumLoosener& AsFlag() const`
- L315 _public function_ `const FFlatEnumLoosener& AsFlat() const`

#### struct `PlainProps::Upgrade::FEnumFastener`  
`struct FEnumFastener`  
_L319-322_
- desc: Loose values -> built value conversion
- L321 _public member_ `const FEnumDeclaration* Decl = nullptr;` — null if loose FEnumeratorId indices match declared constants/flags

#### struct `PlainProps::Upgrade::FEnumTransformation`  
`struct FEnumTransformation`  
_L325-330_
- desc: Cached info for upgrading an enum
- L327 _public member_ `FEnumLoosener Source;`
- L329 _public member_ `FEnumFastener Loose;` — const FEnumUpgrades*		Upgrades; // todo

#### struct `PlainProps::Upgrade::FTransformation`  
`struct FTransformation`  
_L333-338_
- desc: Cached info for upgrading a struct
- L335 _public member_ `mutable const FLooseSchema* SourceSchema = nullptr;`
- L336 _public member_ `const FStructUpgrades* Upgrades = nullptr;`
- L337 _public member_ `const FLooseSchema* TargetSchema = nullptr;`

#### struct `PlainProps::Upgrade::FSourceSchemas`  
`struct FSourceSchemas`  
_L341-348_
- desc: Cached derived schema metadata from a source batch
- L343 _public member_ `uint32 NumStructs = 0;`
- L344 _public member_ `const FSchemaBatch* Batch = nullptr;`
- L345 _public member_ `FInnerIds RuntimeIds;`
- L346 _public member_ `TArray<uint16> StructVersions;`
- L347 _public member_ `TBitArray<> EnumFlagModes;`

#### struct `PlainProps::Upgrade::FTransformations`  
`struct FTransformations`  
_L351-363_
- desc: Cached info for upgrading all structs and enums in a source batch
- L353 _public member_ `TArray<FTransformation> Structs;`
- L354 _public member_ `TSet<FDeclId> StructLookup;` — If we start removing, switch to TSparseSet for FSetElementId stability
- L355 _public member_ `TArray<FEnumTransformation> Enums;`
- L356 _public member_ `TSet<FEnumId> EnumLookup;` — If we start removing, switch to TSparseSet for FSetElementId stability
- L357 _public member_ `FSourceSchemas Schemas;`
- L359 _public function_ `const FTransformation& operator[](FStructSchemaId Id) const`
- L360 _public function_ `const FTransformation& operator[](FDeclId Id) const` — TArrayView::RangeCheck checks invalid FSetElementId
- L361 _public function_ `const FEnumTransformation& operator[](FEnumSchemaId Id) const`
- L362 _public function_ `const FEnumTransformation& operator[](FEnumId Id) const` — TArrayView::RangeCheck checks invalid FSetElementId

#### struct `PlainProps::Upgrade::FStructDecomposition`  
`struct FStructDecomposition`  
_L370-377_
- desc: Help access input struct members in FStructMemberNames order and upgrade/loosen them first
- L372 _public member_ `FDeclId Id;`
- L373 _public member_ `uint16 Version;`
- L374 _public member_ `TSet<FParameterId> InputOrder;` — empty for declared order (iota)
- L375 _public member_ `const FStructUpgrades* Upgrades = nullptr;`
- L376 _public member_ `FLooseSchemaPtr InputSchema;`

#### struct `PlainProps::Upgrade::FEnumDecomposition`  
`struct FEnumDecomposition`  
_L380-384_
- desc: Help access input enum enumerators in FEnumMembers order
- L383 _public member_ `TSet<FEnumeratorId> InputOrder;` — const FEnumUpgrades*		Upgrades = nullptr;		// todo

#### class `PlainProps::Upgrade::FOutputStack`  
`class FOutputStack`  
_L389-400_
- desc: Home for all outputs
- L391 _private member_ `FOut* const Data;`
- L392 _private member_ `int32 Num = 0;`
- L393 _private member_ `FScratchAllocator& Scratch;` — Convenience
- L395 _public prototype_ `FOutputStack(FScratchAllocator& InScratch);`
- L396 _public function_ `~FOutputStack()`
- L398 _public prototype_ `FOuts Push(TConstArrayView<FOutParameter> Params);`
- L399 _public prototype_ `void Pop(int32 InNum);`

#### struct `PlainProps::Upgrade::FOutputScope`  
`struct FOutputScope`  
_L402-409_
- L404 _public prototype_ `FOutputScope(FOutputStack& InStack, TConstArrayView<FOutParameter> Params);`
- L405 _public function_ `~FOutputScope()`
- L407 _public member_ `FOutputStack& Stack;`
- L408 _public member_ `const FOuts Outputs;`

#### class `PlainProps::Upgrade::FDebugPrinter`  
`class FDebugPrinter : public FDebugIds`  
_L412-422_
- inherits: `FDebugIds`
- desc: Helps print some loose types on top of the FDebugIds API
- L414 _private member_ `const FLooseIndexers& LooseIds;`
- L416 _public function_ `FDebugPrinter(const FIds& Ids, FLooseIndexers& Loose) : FDebugIds(Ids), LooseIds(Loose)`
- L419 _public prototype_ `FString Print(FLooseType Type) const;`
- L420 _public function_ `FString Print(FDeclId Id, FParameterId Name) const`
- L421 _public function_ `FString Print(FEnumId Id, FEnumeratorId Name) const`

#### struct `PlainProps::Upgrade::FBatchContext`  
`struct FBatchContext`  
_L425-437_
- desc: Context for upgrading a source batch
- L428 _public member_ `const FTransformations& Transformations;` — todo: add loose transformations for redirected and rename to source transformations
- L429 _public member_ `FScratchAllocator& Scratch;`
- L430 _public member_ `const FIdIndexerBase& Ids;`
- L431 _public member_ `FLooseIndexers& LooseIds;` — RenameMembers can index new names
- L432 _public member_ `const FLooseType Obsolete;`
- L433 _public member_ `const FSchemaBatchId Batch;`
- L434 _public member_ `FOutputStack OutputStack;`
- L435 _public member_ `FContext OpCtx;`
- L436 _public member_ `FDebugPrinter Debug;`

#### struct `PlainProps::Upgrade::FInputDependencies`  
`struct FInputDependencies`  
_L440-445_
- desc: Home for FIn of "polyary" (>1 inputs) ops
- L442 _public member_ `int32 MissingRequired;`
- L443 _public member_ `int32 MissingOptional;`
- L444 _public member_ `FIn Inputs[0];`

#### struct `PlainProps::Upgrade::FOuter`  
`struct FOuter`  
_L448-451_
- desc: Owner of an instance upgrader that might overload and steal inputs
- L450 _public member_ `FInstanceUpgrader* Instance = nullptr;`

#### class `PlainProps::Upgrade::FInstanceUpgrader`  
`class FInstanceUpgrader`  
_L454-507_
- desc: Upgrades a single struct instance
- L458 _private member_ `FBatchContext& Ctx;`
- L459 _private member_ `const FStructUpgrades& Struct;`
- L460 _private member_ `const FVersionUpgrades* Current = nullptr;`
- L461 _private member_ `FOuter Outer;`
- L462 _private member_ `const uint32 NumNames;`
- L463 _private member_ `FOptionalVersion Limit;` — Unimplemented
- L464 _private member_ `bool bUntypedOutcome = false;` — Obsolete types and intermediate versions lack known schema
- L465 _private member_ `uint16 FirstPartialOpIdx = 0xFFFF;` — First "polyary" (>1 inputs) op idx, Flush() opt
- L466 _private member_ `uint8* NameToScanIndices;` — #NumNames - note: wont fly all the way, should support loop around + track used matches
- L467 _private member_ `TArrayView<FInputDependencies*> PartialInputs;` — #Max(NumOps) for versions with polyary ops
- L468 _private member_ `TArrayView<FLooseMember> Outcome;` — #NumNames, initialized by Expect()
- L469 _private member_ `TArray<FLooseMember> Mismatches;`
- L471 _private prototype_ `void Expect(const FLooseSchema* Target);`
- L472 _private prototype_ `void Feed(FLooseMemberReader&& SourceMembers);`
- L473 _private prototype_ `void Feed(TConstArrayView<FLooseMember> LooseMembers);`
- L474 _private prototype_ `void Give(FLooseType Type, FLooseValue Value);`
- L475 _private prototype_ `void Give(FLooseType Type, FLooseValue Value, FMatchHelper Helper);`
- L476 _private prototype_ `FLooseValue Decompose(FLooseType Type, FLooseValue Value, uint16 DecompIdx);`
- L477 _private prototype_ `void Decompose(FLooseType Type, FLooseNestedRange Range, const void* Decomp);`
- L478 _private prototype_ `FLooseValue Decompose(FLooseType Type, FLooseValue Value, const FEnumDecomposition& Decomp);`
- L479 _private prototype_ `FLooseValue Decompose(FEnumMember Input, const FEnumDecomposition& Decomp);`
- L480 _private prototype_ `FLooseValue Decompose(FStructMember Input, const FStructDecomposition& Decomp);`
- L481 _private prototype_ `TArrayView<FLooseMember> Decompose(FStructView Input, const FStructDecomposition& Decomp, FParameterId Name, EMismatch& OutMismatch);`
- L482 _private prototype_ `FEnumIndexData Reorder(FEnumeratorData Input, const TSet<FEnumeratorId>& Order, bool bFlagMode);`
- L483 _private prototype_ `FEnumIndexData Reorder(FEnumeratorId Flat, const TSet<FEnumeratorId>& Order);`
- L484 _private prototype_ `FEnumIndexData Reorder(FEnumeratorIdSet Flags, const TSet<FEnumeratorId>& Order);`
- L485 _private prototype_ `void Input(FMemberMatch Match, FLooseValue Value);`
- L486 _private prototype_ `void Stash(FLooseType Type, FLooseValue Value);`
- L487 _private prototype_ `void Run(FOp Op, const FIn* Inputs, uint8 Recipient);`
- L488 _private prototype_ `FOuter Resolve(uint8 Recipient);`
- L489 _private prototype_ `void Recompose(TArrayView<FOut> Outputs, TConstArrayView<FOutParameter> Expected);`
- L490 _private prototype_ `FEnumeratorData Recompose(FEnumIndexData In, TConstArrayView<FEnumeratorId> Order, FInnermostEnumType Type);`
- L491 _private prototype_ `void Recompose(FRangeData Out, uint64 Num, uint8 Depth, TConstArrayView<FEnumeratorId> Order, FInnermostEnumType Type);`
- L492 _private prototype_ `void Flush();`
- L493 _private prototype_ `FLooseStruct Finish(EMismatch& OutMismatch);`
- L495 _private prototype_ `FString Print(FParameterId Parameter) const;`
- L496 _private prototype_ `FString Print(FLooseType Type) const;`
- L497 _private function_ `template<class T> FString Print(T Item) const`
- L500 _public prototype_ `FInstanceUpgrader(FBatchContext& Ctx, const FStructUpgrades& Upgrades, uint16 Version);`
- L502 _public prototype_ `FLooseStruct Upgrade(FStructView Source, const FLooseSchema& From, const FLooseSchema* To, EMismatch& OutMismatch);`
- L503 _public prototype_ `FLooseStruct Upgrade(FLooseStruct In, const FLooseSchema* To, EMismatch& OutMismatch);`
- L504 _public prototype_ `FStructMember Upgrade(FStructMember In, const FLooseSchema* To, FOuter InOuter = {});`
- L506 _public prototype_ `void Reuse();` — Todo: Optimization for upgrading range-of-structs

#### struct `PlainProps::Upgrade::FSchemaCache`  
`struct FSchemaCache`  
_L511-515_
- L513 _public prototype_ `const FLooseSchema* Obtain(FDeclId Id, const IDeclarations& Types, FParameterIndexer& ParamIds);`
- L514 _public member_ `TMap<FDeclId, FLooseSchemaPtr> Cache;`

#### struct `PlainProps::Upgrade::TDestroyOnly`  
`template <typename T> struct TDestroyOnly`  
_L520-529_
- L522 _public function_ `void operator()(T* Ptr) const`

#### struct `PlainProps::Upgrade::FHistory`  
`struct FHistory`  
_L539-557_
- L541 _public member_ `const IDeclarations& Latest;`
- L542 _public member_ `mutable FSchemaCache LatestSchemas;`
- L543 _public member_ `FLiteralIndexerBase& Ids;`
- L544 _public member_ `mutable FLooseIndexers LooseIds;`
- L545 _public member_ `FScratchAllocator CommitScratch;`
- L546 _public member_ `TArray<FOpsPtr> CommitQueue;`
- L547 _public member_ `TMap<FDeclId, FStructUpgradesPtr> CompiledUpgrades;`
- L549 _public prototype_ `void Compile();`
- L550 _public prototype_ `void Erase(FStructId Id);`
- L553 _private prototype_ `void CompileStruct(TArrayView<FOpsPtr> AllOps);`
- L554 _private prototype_ `void Link(TConstArrayView<FOpsPtr> Committed);`
- L555 _private prototype_ `void Link(FDeclId Compiled);`
- L556 _private prototype_ `void Link(FStructDecomposition& Dependency);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace PlainProps`
- L14 _namespace_ `namespace Upgrade` (scope `PlainProps`)
- L36 _typedef_ `using FParameterIdSet = TSet<FOptionalMemberId>;` (scope `PlainProps::Upgrade`)
- L367 _typedef_ `using FLooseSchemaPtr = TUniquePtr<FLooseSchema>;` (scope `PlainProps::Upgrade`)
- L532 _typedef_ `template<class T> using TScratchPtr = TUniquePtr<T, TDestroyOnly<T>>;` (scope `PlainProps::Upgrade`)
- L536 _typedef_ `using FOpsPtr = TScratchPtr<FOps>;` (scope `PlainProps::Upgrade`)
- L537 _typedef_ `using FStructUpgradesPtr = TUniquePtr<FStructUpgrades>;` (scope `PlainProps::Upgrade`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsBind.h` (Public)


#### enum `PlainProps::ELeafBindType`  
`enum class ELeafBindType : uint8`  
_L36-36_
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`
- L36 _public enumerator_ `enum class ELeafBindType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode, BitfieldBool }; inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type) { return static_cast<ELeafBindType>(static_cast<uint8>(Type)); } inline static constexpr ELeafType ToLeafType(ELeafBindType Type)`

#### struct `PlainProps::FBasicLeafBindType`  
`struct FBasicLeafBindType`  
_L48-54_
- L50 _public member_ `EMemberKind _ : 2;`
- L51 _public member_ `ELeafBindType __ : 3;`
- L52 _public member_ `ELeafWidth Width : 2;`
- L53 _public member_ `uint8 _Pad : 1;`

#### struct `PlainProps::FBitfieldBoolBindType`  
`struct FBitfieldBoolBindType`  
_L56-61_
- L58 _public member_ `EMemberKind _ : 2;`
- L59 _public member_ `ELeafBindType __ : 3;`
- L60 _public member_ `uint8 Idx : 3;`

#### union `PlainProps::FLeafBindType`  
`union FLeafBindType`  
_L63-79_
- L65 _public function_ `constexpr explicit FLeafBindType(ELeafBindType BasicType, ELeafWidth Width) : Basic({EMemberKind::Leaf, BasicType, Width})`
- L66 _public function_ `constexpr explicit FLeafBindType(FUnpackedLeafType In) : Basic({EMemberKind::Leaf, ToLeafBindType(In.Type), In.Width})`
- L67 _public function_ `constexpr explicit FLeafBindType(FLeafType In) : FLeafBindType(FUnpackedLeafType(In))`
- L68 _public function_ `constexpr explicit FLeafBindType(FBitfieldBoolBindType In) : Bitfield({EMemberKind::Leaf, ELeafBindType::BitfieldBool, In.Idx})`
- L69 _public function_ `constexpr explicit FLeafBindType(uint8 BitfieldIdx) : Bitfield({EMemberKind::Leaf, ELeafBindType::BitfieldBool, BitfieldIdx})`
- L76 _public member_ `} Bind;`
- L77 _public member_ `FBasicLeafBindType Basic;`
- L78 _public member_ `FBitfieldBoolBindType Bitfield;`

#### struct `PlainProps::FLeafBindType::(anonymous)`  
``  
_L72-76_

#### struct `PlainProps::FRangeBindType`  
`struct FRangeBindType : FRangeType`  
_L91-91_
- inherits: `FRangeType`

#### struct `PlainProps::FStructBindType`  
`struct FStructBindType : FStructType`  
_L93-93_
- inherits: `FStructType`

#### union `PlainProps::FMemberBindType`  
`union FMemberBindType`  
_L95-122_
- L97 _public function_ `constexpr explicit FMemberBindType(FLeafType In) : Leaf(In)`
- L98 _public function_ `constexpr explicit FMemberBindType(FUnpackedLeafType In) : Leaf(In)`
- L99 _public function_ `constexpr explicit FMemberBindType(FLeafBindType In) : Leaf(In)`
- L100 _public function_ `constexpr explicit FMemberBindType(FBitfieldBoolBindType In) : Leaf(In)`
- L101 _public function_ `constexpr explicit FMemberBindType(FRangeType In) : Range(In)`
- L102 _public function_ `constexpr explicit FMemberBindType(ESizeType MaxSize) : Range({EMemberKind::Range, MaxSize})`
- L103 _public function_ `constexpr explicit FMemberBindType(FStructType In) : Struct(In)`
- L105 _public function_ `bool IsLeaf() const`
- L106 _public function_ `bool IsRange() const`
- L107 _public function_ `bool IsStruct() const`
- L108 _public function_ `EMemberKind GetKind() const`
- L110 _public function_ `FLeafBindType AsLeaf() const`
- L111 _public function_ `FRangeBindType AsRange() const`
- L112 _public function_ `FStructBindType AsStruct() const`
- L113 _public function_ `uint8 AsByte() const`
- L118 _private member_ `EMemberKind Kind : 2;`
- L119 _private member_ `FLeafBindType Leaf;`
- L120 _private member_ `FRangeBindType Range;`
- L121 _private member_ `FStructBindType Struct;`

#### struct `PlainProps::FSchemaBinding`  
`struct alignas( 8) FSchemaBinding`  
_L129-143_
- desc: Members are loaded in saved FStructSchema order, not current offset order unless upgrade layer reorders
- L131 _public member_ `FDeclId DeclId;`
- L132 _public member_ `uint16 NumMembers;`
- L133 _public member_ `uint16 NumInnerIds;`
- L134 _public member_ `uint16 NumInnerRanges;`
- L135 _public member_ `FMemberBindType Members[0];`
- L137 _public function_ `const FMemberBindType* GetInnerRangeTypes() const`
- L138 _public function_ `const uint32* GetOffsets() const`
- L139 _public function_ `const FInnerId* GetInnerIds() const`
- L140 _public function_ `const FRangeBinding* GetRangeBindings() const`
- L141 _public prototype_ `uint32 CalculateSize() const;`
- L142 _public function_ `bool HasSuper() const`

#### struct `PlainProps::FUnpackedLeafBindType`  
`struct FUnpackedLeafBindType`  
_L147-173_
- L149 _public member_ `ELeafBindType Type;`
- L156 _public function_ `constexpr FUnpackedLeafBindType(FLeafBindType In) : Type(In.Bind.Type)`
- L169 _public function_ `FMemberBindType Pack() const`

#### union `PlainProps::FUnpackedLeafBindType::(anonymous)`  
``  
_L151-154_

#### struct `PlainProps::FLeafMemberBinding`  
`struct FLeafMemberBinding`  
_L192-197_
- L194 _public member_ `FUnpackedLeafBindType Leaf;`
- L195 _public member_ `FOptionalEnumId Enum;`
- L196 _public member_ `SIZE_T Offset;`

#### struct `PlainProps::FRangeMemberBinding`  
`struct FRangeMemberBinding`  
_L199-206_
- L201 _public member_ `const FMemberBindType* InnerTypes;`
- L202 _public member_ `const FRangeBinding* RangeBindings;`
- L203 _public member_ `uint16 NumRanges;` — At least 1, >1 for nested ranges
- L204 _public member_ `FOptionalInnerId InnermostId;`
- L205 _public member_ `SIZE_T Offset;`

#### struct `PlainProps::FStructMemberBinding`  
`struct FStructMemberBinding`  
_L208-213_
- L210 _public member_ `FStructType Type;`
- L211 _public member_ `FBindId Id;`
- L212 _public member_ `SIZE_T Offset;`

#### struct `PlainProps::FBothStructId`  
`struct FBothStructId`  
_L219-225_
- L221 _public member_ `FBindId BindId;`
- L222 _public member_ `FDeclId DeclId;`
- L224 _public function_ `bool IsLowered() const`

#### struct `PlainProps::FDualStructId`  
`struct FDualStructId : FStructId`  
_L228-234_
- inherits: `FStructId`
- desc: FStructId statically known to share FBindId and FDeclId, i.e. not lowered
- L230 _public function_ `explicit FDualStructId(FStructId In) : FStructId(In)`
- L232 _public function_ `operator FBindId() const`
- L233 _public function_ `operator FDeclId() const`

#### struct `PlainProps::FInnerStruct`  
`struct FInnerStruct`  
_L239-243_
- desc: Helps raise lowered FDeclId by seeing which FBindId a particular named member has
- L241 _public member_ `FMemberId Name;` — Of outer Range or Struct
- L242 _public member_ `FBindId Id;`

#### enum `PlainProps::ECustomLoadMethod`  
`enum ECustomLoadMethod`  
_L245-245_
- L245 _public enumerator_ `enum ECustomLoadMethod { Construct, Assign };`
- L245 _public enumerator_ `enum ECustomLoadMethod { Construct, Assign };`

#### struct `PlainProps::ICustomBinding`  
`struct ICustomBinding`  
_L254-267_
- desc: Load/save a struct with custom code to handle: * reference types * private members * non-default constructible types * custom delta semantics * other runtime representations than struct/class, e.g. serialize database * optimizations of very common structs
- L256 _public function_ `virtual ~ICustomBinding()`
- L257 _public prototype_ `virtual void SaveCustom(FMemberBuilder& Dst, const void* Src, FBaseline Base, const FSaveContext& Ctx) = 0;`
- L258 _public prototype_ `virtual void LoadCustom(void* Dst, FStructLoadView Src, ECustomLoadMethod Method) const = 0;`
- L259 _public prototype_ `virtual bool DiffCustom(const void* StructA, const void* StructB, const FBindContext& Ctx) const = 0;`
- L262 _public function_ `virtual void PlanCustom(FMemcpyLoadPlan& Out) const` — Overload to load via a single memcpy call instead of LoadCustom, Out.Offset is 0 by default
- L265 _public prototype_ `virtual bool DiffCustom(const void* StructA, const void* StructB, FDiffContext& Ctx) const;` — Overload to track the first or all diffing members, see FDiffTree

#### struct `PlainProps::FInnersHandle`  
`struct FInnersHandle`  
_L269-273_
- L271 _public member_ `uint32 Num = 0;`
- L272 _public member_ `uint32 Idx = 0;`

#### struct `PlainProps::FIdWindow`  
`struct FIdWindow`  
_L275-279_
- L277 _public member_ `uint32 Min = 0;`
- L278 _public member_ `uint32 Num = 0;`

#### struct `PlainProps::FCustomBindingMap`  
`struct FCustomBindingMap`  
_L282-298_
- desc: Slightly optimized map from FStructId to ICustomBinding/FStructDeclaration/FInnersHandle
- L285 _public prototype_ `explicit FCustomBindingMap(FDebugIds Dbg);`
- L286 _public prototype_ `~FCustomBindingMap();`
- L288 _public prototype_ `void Bind(FBindId Id, ICustomBinding& Binding, FStructDeclarationPtr&& Declaration, FInnersHandle LoweredInners);`
- L289 _public prototype_ `FCustomBindingHandle Find(FBindId Id) const;`
- L290 _public prototype_ `void Drop(FBindId Id);`
- L292 _public member_ `FIdWindow Window;`
- L293 _public member_ `TSparseSet<FBindId> Keys;` — Need FSetElementId stability when dropping
- L294 _public member_ `ICustomBinding** Values = nullptr;`
- L295 _public member_ `uint32 MaxValues = 0;`
- L296 _public member_ `TArray<FStructDeclarationPtr> Declarations;` — Consider switch to TSparseArray or TMap
- L297 _public member_ `FDebugIds Debug;`

#### class `PlainProps::FCustomBindings`  
`class FCustomBindings`  
_L300-321_
- L304 _public prototype_ `void BindStruct(FBindId Id, ICustomBinding& Binding, FStructDeclarationPtr&& Declaration, TConstArrayView<FInnerStruct> LoweredInners);` — @param Binding must outlive this or call DropStruct()
- L305 _public prototype_ `void BindStruct(FBindId Id, ICustomBinding& Binding, const FStructSpec& DeclSpec, TConstArrayView<FInnerStruct> LoweredInners);`
- L306 _public prototype_ `const ICustomBinding* FindStruct(FBindId Id) const;`
- L307 _public prototype_ `const ICustomBinding* FindStruct(FBindId Id, TConstArrayView<FInnerStruct>& OutLoweredInners) const;`
- L308 _public prototype_ `const ICustomBinding* FindStruct(FBindId Id, const FStructDeclaration*& OutDeclaration) const;`
- L309 _public prototype_ `ICustomBinding* FindStructToSave(FBindId Id, const FStructDeclaration*& OutDeclaration) const;`
- L310 _public prototype_ `const FStructDeclaration* FindDeclaration(FBindId Id) const;`
- L311 _public prototype_ `void DropStruct(FBindId Id);`
- L313 _public prototype_ `virtual FCustomBindingHandle Find(FBindId Id) const = 0;`
- L315 _protected prototype_ `FCustomBindings(TArray<FInnerStruct>& Inners, FDebugIds Dbg);`
- L316 _protected prototype_ `FCustomBindings(const FCustomBindings* Under);`
- L317 _protected prototype_ `~FCustomBindings();`
- L319 _protected member_ `FCustomBindingMap Map;`
- L320 _protected member_ `TArray<FInnerStruct>& BottomInners;`

#### class `PlainProps::FCustomBindingsBottom`  
`class FCustomBindingsBottom final : public FCustomBindings`  
_L323-329_
- inherits: `FCustomBindings`
- L325 _private member_ `mutable TArray<FInnerStruct> AllInners;`
- L326 _private prototype_ `virtual FCustomBindingHandle Find(FBindId Id) const override;`
- L328 _public function_ `explicit FCustomBindingsBottom(FDebugIds Dbg) : FCustomBindings( AllInners, Dbg)`

#### class `PlainProps::FCustomBindingsOverlay`  
`class FCustomBindingsOverlay final : public FCustomBindings`  
_L331-337_
- inherits: `FCustomBindings`
- L333 _private member_ `const FCustomBindings& Underlay;`
- L334 _private prototype_ `virtual FCustomBindingHandle Find(FBindId Id) const override;`
- L336 _public function_ `explicit FCustomBindingsOverlay(const FCustomBindings& Under) : FCustomBindings(&Under), Underlay(Under)`

#### class `PlainProps::FConstructionRequest`  
`class FConstructionRequest`  
_L342-360_
- desc: Request from loading layer to IItemRangeBinding to allocate and construct items
- L346 _private member_ `void* const Range = nullptr;`
- L347 _private member_ `const uint64 Num = 0;`
- L348 _private member_ `uint64 Index = 0;`
- L350 _private function_ `FConstructionRequest(void* InRange, uint64 InNum) : Range(InRange), Num(InNum)`
- L354 _public function_ `template<typename T> T& GetRange() const`
- L355 _public function_ `uint64 NumTotal() const`
- L356 _public function_ `uint64 NumMore() const`
- L357 _public function_ `uint64 GetIndex() const`
- L358 _public function_ `bool IsFirstCall() const`
- L359 _public function_ `bool IsFinalCall() const`

#### class `PlainProps::FConstructedItems`  
`class FConstructedItems`  
_L366-413_
- desc: Response from IItemRangeBinding with contiguous items ready to be loaded Non-contiguous containers provide one items one by one or use FLoadRangeContext::Scratch or a temp allocation to avoid that
- L370 _public function_ `void RequestFinalCall()` — E.g. allow hash table to rehash after all items are loaded
- L372 _public function_ `void SetUnconstructed()`
- L376 _public function_ `template<typename ItemType> void Set(ItemType* Items, uint64 NumItems)` — Non-contiguous items must be set individually
- L381 _public function_ `void Set(void* Items, uint64 NumItems, uint32 ItemSize)`
- L389 _public function_ `void UpdateNum(uint64 NumItems)`
- L396 _public function_ `template<typename ItemType> TArrayView<ItemType> Get()`
- L401 _public function_ `inline uint8* GetData()`
- L402 _public function_ `inline uint8* GetDataEnd()`
- L406 _private member_ `uint8* Data = nullptr;`
- L407 _private member_ `uint64 Num = 0;`
- L408 _private member_ `uint32 Size = 0;`
- L409 _private member_ `bool bNeedFinalize = false;`
- L410 _private member_ `bool bUnconstructed = false;`
- L412 _private function_ `uint64 NumBytes() const`

#### struct `PlainProps::FLoadRangeContext`  
`struct FLoadRangeContext`  
_L415-420_
- L417 _public member_ `FConstructionRequest Request;` — Request to construct items to be loaded
- L418 _public member_ `FConstructedItems Items;` — Response from IItemRangeBinding
- L419 _public member_ `uint64 Scratch[64];` — Scratch memory for IItemRangeBinding

#### struct `PlainProps::FGetItemsRequest`  
`struct FGetItemsRequest`  
_L423-432_
- desc: todo: switch to class
- L426 _public function_ `template<typename T> const T& GetRange() const`
- L428 _public function_ `bool IsFirstCall() const`
- L430 _public member_ `const void* Range = nullptr;`
- L431 _public member_ `uint64 NumRead = 0;`

#### struct `PlainProps::FExistingItemSlice`  
`struct FExistingItemSlice`  
_L434-446_
- L436 _public member_ `const void* Data = nullptr;`
- L437 _public member_ `uint64 Num = 0;`
- L439 _public function_ `explicit operator bool() const`
- L441 _public function_ `const uint8* At(uint64 Idx, uint32 Stride) const`

#### struct `PlainProps::FExistingItems`  
`struct FExistingItems`  
_L448-466_
- L450 _public member_ `uint64 NumTotal = 0;`
- L451 _public member_ `uint32 Stride = 0;`
- L452 _public member_ `FExistingItemSlice Slice;`
- L454 _public function_ `void SetAll(const void* Items, uint64 Num, uint32 InStride)`
- L462 _public function_ `template<typename ItemType> void SetAll(const ItemType* Items, uint64 Num)`

#### struct `PlainProps::FSaveRangeContext`  
`struct FSaveRangeContext`  
_L468-473_
- L470 _public member_ `FGetItemsRequest Request;` — Request to get items to be saved
- L471 _public member_ `FExistingItems Items;` — Response from IRangeBinding
- L472 _public member_ `uint64 Scratch[8];` — Scratch memory for IRangeBinding

#### struct `PlainProps::IItemRangeBinding`  
`struct alignas(16) IItemRangeBinding`  
_L475-483_
- L477 _public prototype_ `virtual void ReadItems(FSaveRangeContext& Ctx) const = 0;`
- L478 _public prototype_ `virtual void MakeItems(FLoadRangeContext& Ctx) const = 0;`
- L481 _public function_ `explicit IItemRangeBinding(FConcreteTypenameId RangeBindName) : BindName(RangeBindName)` — Try living without virtual destructor and trivially destructible members
- L482 _public member_ `const FConcreteTypenameId BindName;`

#### class `PlainProps::FLeafRangeAllocator`  
`class FLeafRangeAllocator`  
_L488-515_
- desc: Possible save opt: Use paged linear allocator that only allocates on page exhaustion
- L490 _private member_ `FScratchAllocator& Scratch;`
- L491 _private member_ `FBuiltRange* Range = nullptr;`
- L492 _private member_ `const FUnpackedLeafType Expected;`
- L494 _private prototype_ `void* Allocate(uint64 Num, SIZE_T LeafSize);`
- L497 _public function_ `FLeafRangeAllocator(FScratchAllocator& InScratch, FUnpackedLeafType InExpected) : Scratch(InScratch), Expected(InExpected)`
- L500 _public function_ `template<LeafType T, typename SizeType> T* AllocateRange(SizeType Num)`
- L507 _public function_ `template<typename SizeType> void* AllocateNonEmptyRange(SizeType Num, ELeafWidth Width)`
- L514 _public function_ `FBuiltRange* GetAllocatedRange()`

#### struct `PlainProps::ILeafRangeBinding`  
`struct alignas(16) ILeafRangeBinding`  
_L519-533_
- desc: Specialized binding for transcoding leaf ranges
- L521 _public prototype_ `virtual void SaveLeaves(const void* Range, FLeafRangeAllocator& Out) const = 0;`
- L522 _public prototype_ `virtual void LoadLeaves(void* Range, FLeafRangeLoadView Leaves) const = 0;`
- L523 _public prototype_ `virtual bool DiffLeaves(const void* RangeA, const void* RangeB) const = 0;`
- L525 _public function_ `explicit ILeafRangeBinding(FConcreteTypenameId RangeBindName) : BindName(RangeBindName)`
- L526 _public member_ `const FConcreteTypenameId BindName;`
- L529 _public function_ `template<typename SizeType> static bool Diff(SizeType NumA, SizeType NumB, const void* A, const void* B, SIZE_T ItemSize)`

#### class `PlainProps::FRangeBinding`  
`class FRangeBinding`  
_L537-554_
- L539 _private member_ `static constexpr uint64 SizeMask = 0b1111;`
- L540 _private member_ `static constexpr uint64 LeafMask = uint64(1) << FPlatformMemory::KernelAddressBit;`
- L541 _private member_ `static constexpr uint64 BindMask = ~(SizeMask | LeafMask);`
- L542 _private member_ `uint64 Handle;`
- L545 _public prototype_ `FRangeBinding(const IItemRangeBinding& Binding, ESizeType SizeType);`
- L546 _public prototype_ `FRangeBinding(const ILeafRangeBinding& Binding, ESizeType SizeType);`
- L548 _public function_ `bool IsLeafBinding() const`
- L549 _public function_ `const IItemRangeBinding& AsItemBinding() const`
- L550 _public function_ `const ILeafRangeBinding& AsLeafBinding() const`
- L551 _public function_ `ESizeType GetSizeType() const`
- L552 _public function_ `FConcreteTypenameId GetBindName() const`
- L553 _public function_ `inline bool operator==(FRangeBinding O) const`

#### struct `PlainProps::FBothType`  
`struct FBothType`  
_L558-564_
- L560 _public member_ `FType BindType;`
- L561 _public member_ `FType DeclType;`
- L563 _public function_ `bool IsLowered() const`

#### struct `PlainProps::FMemberBinding`  
`struct FMemberBinding`  
_L568-582_
- L570 _public function_ `explicit FMemberBinding(uint64 InOffset = 0) : Offset(InOffset) , InnermostType(FLeafBindType(ELeafBindType::Bool, ELeafWidth::B8))`
- L575 _public member_ `uint64 Offset;`
- L576 _public member_ `FMemberBindType InnermostType;` — Always Leaf or Struct
- L577 _public member_ `FOptionalInnerId InnermostId;` — Enum or struct bind id
- L578 _public member_ `TConstArrayView<FRangeBinding> RangeBindings;` — Non-empty -> Range
- L581 _public prototype_ `FBothType IndexParameterName(FIdIndexerBase& Ids) const;` — @pre InnermostId isn't type-erased / lowered

#### class `PlainProps::FSchemaBindings`  
`class FSchemaBindings`  
_L584-611_
- L588 _public prototype_ `explicit FSchemaBindings(FDebugIds In);`
- L589 _public prototype_ `~FSchemaBindings();`
- L591 _public prototype_ `void BindStruct(FBindId Id, TConstArrayView<FMemberBinding> Members, FStructSpec Decl);`
- L592 _public prototype_ `void BindStruct(FBindId Id, TConstArrayView<FMemberBinding> Members, FStructDeclarationPtr&& Decl);`
- L593 _public prototype_ `const FSchemaBinding* FindStruct(FBindId Id) const;`
- L594 _public prototype_ `const FSchemaBinding* FindStruct(FBindId Id, const FStructDeclaration*& OutDeclaration) const;`
- L595 _public prototype_ `const FSchemaBinding& GetStruct(FBindId Id) const;`
- L596 _public prototype_ `const FSchemaBinding& GetStruct(FBindId Id, const FStructDeclaration*& OutDecl) const;`
- L597 _public prototype_ `void DropStruct(FBindId Id);`
- L599 _public prototype_ `FDeclId Lower(FBindId Id) const;`
- L600 _public prototype_ `const FStructDeclaration& GetDeclaration(FBindId Id) const;`
- L601 _public prototype_ `const FStructDeclaration* FindDeclaration(FBindId Id) const;`
- L602 _public function_ `FDebugIds GetDebug() const`
- L605 _private member_ `TArray<FStructDeclarationPtr> Declarations;`
- L606 _private member_ `TArray<TUniquePtr<FSchemaBinding>> Bindings;`
- L607 _private member_ `FDebugIds Debug;`
- L609 _private prototype_ `FSchemaBinding* Bind(FBindId Id, TConstArrayView<FMemberBinding> Members, FDeclId DeclId);`
- L610 _private prototype_ `FStructDeclarationPtr& At(FDeclId Id);`

#### struct `PlainProps::IDefaultStructs`  
`struct IDefaultStructs`  
_L616-619_
- desc: Lookup default instances when delta-saving struct ranges
- L618 _public prototype_ `virtual const void* Get(FBindId Id) = 0;`

#### struct `PlainProps::FBindContext`  
`struct FBindContext`  
_L623-629_
- L625 _public member_ `const FSchemaBindings& Schemas;`
- L626 _public member_ `FCustomBindings& Customs;`
- L628 _public prototype_ `const FStructDeclaration& GetDeclaration(FBindId Id) const;`

#### struct `PlainProps::FBindDeclarations`  
`struct FBindDeclarations final : IDeclarations`  
_L631-642_
- inherits: `IDeclarations`
- L633 _public function_ `FBindDeclarations(const FEnumDeclarations& E, const FCustomBindings& C, const FSchemaBindings& S) : Enums(E), Customs(C), Schemas(S)`
- L635 _public member_ `const FEnumDeclarations& Enums;`
- L636 _public member_ `const FCustomBindings& Customs;`
- L637 _public member_ `const FSchemaBindings& Schemas;`
- L639 _public prototype_ `virtual const FEnumDeclaration* Find(FEnumId Id) const override;`
- L640 _public prototype_ `virtual const FStructDeclaration* Find(FStructId Id) const override;`
- L641 _public prototype_ `virtual FDeclId Lower(FBindId Id) const override;`

#### struct `PlainProps::FIdBinding`  
`struct FIdBinding`  
_L652-678_
- desc: Save -> load ids for ESchemaFormat::StableNames
- L654 _public member_ `TConstArrayView<FNameId> Names;`
- L655 _public member_ `TConstArrayView<FNestedScopeId> NestedScopes;`
- L656 _public member_ `TConstArrayView<FParametricTypeId> ParametricTypes;`
- L657 _public member_ `TConstArrayView<FInnerId> Schemas;`
- L659 _public function_ `FNameId Remap(FNameId Old) const`
- L660 _public function_ `FMemberId Remap(FMemberId Old) const`
- L661 _public function_ `FFlatScopeId Remap(FFlatScopeId Old) const`
- L662 _public function_ `FNestedScopeId Remap(FNestedScopeId Old) const`
- L663 _public function_ `FScopeId Remap(FScopeId Old) const`
- L664 _public function_ `FConcreteTypenameId Remap(FConcreteTypenameId Old) const`
- L665 _public function_ `FParametricTypeId Remap(FParametricTypeId Old) const`
- L666 _public function_ `FTypenameId Remap(FTypenameId Old) const`
- L667 _public function_ `FType Remap(FType Old) const`
- L670 _public function_ `template<typename T> TOptionalId<T> Remap(TOptionalId<T> Old) const`
- L672 _public function_ `TConstArrayView<FStructId> GetStructIds(int32 NumStructs) const`

#### struct `PlainProps::FIdTranslatorBase`  
`struct FIdTranslatorBase`  
_L680-684_
- L682 _public prototype_ `static uint32 CalculateTranslationSize(int32 NumSavedNames, const FSchemaBatch& Batch);`
- L683 _public prototype_ `static FIdBinding TranslateIds(FMutableMemoryView To, FIdIndexerBase& Indexer, TConstArrayView<FNameId> TranslatedNames, const FSchemaBatch& From);`

#### struct `PlainProps::FIdTranslator`  
`struct FIdTranslator : FIdTranslatorBase`  
_L687-708_
- inherits: `FIdTranslatorBase`
- desc: Maps saved ids -> runtime load ids for ESchemaFormat::StableNames
- L690 _public function_ `template<class NameType> FIdTranslator(TIdIndexer<NameType>& Indexer, TConstArrayView<NameType> SavedNames, const FSchemaBatch& Batch)`
- L706 _public member_ `FIdBinding Translation;`
- L707 _public member_ `TArray<uint8, TInlineAllocator<1024>> Allocator;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlainProps`
- L38 _function_ `inline static constexpr ELeafBindType ToLeafBindType(ELeafType Type)` (scope `PlainProps`)
- L43 _function_ `inline static constexpr ELeafType ToLeafType(ELeafBindType Type)` (scope `PlainProps`)
- L73 _member_ `EMemberKind _ : 2;` (scope `PlainProps::FLeafBindType::__anon00aa43840108`)
- L74 _member_ `ELeafBindType Type : 3;` (scope `PlainProps::FLeafBindType::__anon00aa43840108`)
- L75 _member_ `uint8 _Pad : 3;` (scope `PlainProps::FLeafBindType::__anon00aa43840108`)
- L81 _function_ `inline static constexpr FLeafType ToLeafType(FLeafBindType Leaf)` (scope `PlainProps`)
- L115 _function_ `friend inline bool operator==(FMemberBindType A, FMemberBindType B)` (scope `PlainProps`)
- L116 _function_ `friend inline uint32 GetTypeHash(FMemberBindType In)` (scope `PlainProps`)
- L152 _member_ `ELeafWidth Width;` (scope `PlainProps::FUnpackedLeafBindType::__anon00aa4384020a`)
- L153 _member_ `uint8 BitfieldIdx;` (scope `PlainProps::FUnpackedLeafBindType::__anon00aa4384020a`)
- L175 _function_ `inline static constexpr FUnpackedLeafType ToUnpackedLeafType(FUnpackedLeafBindType Leaf)` (scope `PlainProps`)
- L186 _function_ `inline FUnpackedLeafType UnpackNonBitfield(FLeafBindType Packed)` (scope `PlainProps`) — @pre Type != ELeafBindType::BitfieldBool
- L215 _prototype_ `FRangeMemberBinding GetInnerRange(FRangeMemberBinding In);` (scope `PlainProps`) — @pre In.NumRanges > 1
- L647 _prototype_ `[[nodiscard]] TArray<FStructId> IndexStructRuntimeIds(const FSchemaBatch& Schemas, FIdIndexerBase& Indexer);` (scope `PlainProps`) — Save -> load struct ids for ESchemaFormat::InMemoryNames, alternative to side-channel with ExtractRuntimeIds()
- L648 _prototype_ `[[nodiscard]] TArray<FInnerId> IndexAllRuntimeIds(const FSchemaBatch& Schemas, FIdIndexerBase& Indexer);` (scope `PlainProps`)
- L649 _prototype_ `[[nodiscard]] TConstArrayView<FStructId> GetStructRuntimeIds(TConstArrayView<FInnerId> AllIds, uint32 NumStructSchemas);` (scope `PlainProps`)
- L710 _prototype_ `FSchemaBatch* CreateTranslatedSchemas(const FSchemaBatch& Schemas, FIdBinding NewIds);` (scope `PlainProps`)
- L711 _prototype_ `void DestroyTranslatedSchemas(const FSchemaBatch* Schemas);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsBindCtti.h` (Public)


#### struct `PlainProps::TRangeBind`  
`template<typename T> struct TRangeBind`  
_L21-21_
- L21 _public typedef_ `template<typename T> struct TRangeBind{ using Type = void; };`

#### struct `PlainProps::TCustomBind`  
`template<typename T> struct TCustomBind`  
_L27-27_
- L27 _public typedef_ `template<typename T> struct TCustomBind { using Type = void; };`

#### struct `PlainProps::TExternallyBound`  
`template<typename T, class Runtime> struct TExternallyBound : std::false_type`  
_L30-30_
- inherits: `std::false_type`

#### struct `PlainProps::TCustomDeltaBind`  
`template<class T> struct TCustomDeltaBind`  
_L33-33_
- L33 _public typedef_ `template<class T> struct TCustomDeltaBind { using Type = void; };`

#### struct `PlainProps::TOccupancyOf`  
`template<typename T> struct TOccupancyOf`  
_L42-45_
- L44 _public member_ `static constexpr EMemberPresence Value = EMemberPresence::AllowSparse;`

#### struct `PlainProps::FRequireAll`  
`struct FRequireAll`  
_L47-50_
- L49 _public member_ `static constexpr EMemberPresence Value = EMemberPresence::RequireAll;`

#### struct `PlainProps::TInit`  
`template<class Ids> struct TInit`  
_L231-231_
- desc: Works around C++'s lack of templated nullary constructors

#### struct `PlainProps::FCustomInit`  
`struct FCustomInit`  
_L235-253_
- L238 _public prototype_ `FCustomInit() = default;`
- L240 _public member_ `InnerStructArray LoweredInners;`
- L243 _public function_ `void RegisterInnerStruct(FBothStructId InnerId, TConstArrayView<FMemberId> Names)` — Only needed for inner structs that might get type-erased/lowered

#### struct `PlainProps::TCustomInit`  
`template<class Ids> struct TCustomInit : FCustomInit, TInit<Ids>`  
_L257-258_
- inherits: `FCustomInit,TInit<Ids>`
- desc: Helps custom binding constructors create ids and register types that might get type-erased

#### struct `PlainProps::TCustomSpecifier`  
`template<class Ids, uint32 N> struct TCustomSpecifier : TCustomInit<Ids>`  
_L263-283_
- inherits: `TCustomInit<Ids>`
- desc: Constructor API for static custom bindings to create ids, register type-erased inner structs and specify member types, inheritance and version
- L265 _public member_ `FOptionalDeclId Super;`
- L266 _public member_ `uint16 Version = 0;`
- L267 _public member_ `FMemberSpec Members[N];`
- L270 _public function_ `template <typename... Ts> void SetMembers(Ts&&... Specs) requires (N == sizeof...(Specs))`
- L276 _public function_ `void FillMembers(FMemberSpec Same)`

#### struct `PlainProps::TDependent`  
`template<typename> struct TDependent`  
_L289-293_
- desc: Workaround for clang requiring the definition, make it dependent on any other type
- L291 _public typedef_ `using Baseline = FBaseline;`
- L292 _public typedef_ `using StructLoadView = FStructLoadView;`

#### struct `PlainProps::TScopedStructBinding`  
`template<class T, class Runtime, typename CustomBinding = CustomBind<T>> struct TScopedStructBinding : FBothStructId, CustomBinding`  
_L297-367_
- inherits: `FBothStructId,CustomBinding`
- desc: Scoped custom binding for native type
- L299 _public typedef_ `using Ids = typename Runtime::Ids;`
- L300 _public typedef_ `using Typename = TCustomTypename<CustomBinding>::Type;`
- L301 _public member_ `static constexpr uint32 N = sizeof(CustomBinding::MemberIds) / sizeof(CustomBinding::MemberIds[0]);`
- L308 _public function_ `explicit TScopedStructBinding(FDualStructId Dual) : TScopedStructBinding(FBothStructId{Dual, Dual})`
- L312 _public function_ `explicit TScopedStructBinding(FBothStructId Both) : TScopedStructBinding(Both, TCustomSpecifier<Ids, N>())`
- L316 _public function_ `TScopedStructBinding(FBothStructId Both, TCustomSpecifier<Ids, N>&& Init) : FBothStructId(Both) , CustomBinding( Init)`
- L327 _public function_ `~TScopedStructBinding()`
- L332 _public function_ `virtual void SaveCustom(FMemberBuilder& Dst, const void* Src, TDependent<Ids>::Baseline Base, const FSaveContext& Ctx) override`
- L338 _public function_ `virtual void LoadCustom(void* Dst, TDependent<Ids>::StructLoadView Src, ECustomLoadMethod Method) const override`
- L350 _public function_ `virtual bool DiffCustom(const void* A, const void* B, const FBindContext& Ctx) const override`
- L355 _public function_ `virtual bool DiffCustom(const void* A, const void* B, FDiffContext& Ctx) const override`
- L360 _public function_ `virtual void PlanCustom(FMemcpyLoadPlan& Out) const override`
- L374 _public typedef_ `using Typename = TTypename<T>;`

#### struct `PlainProps::TScopedStructBinding`  
`template<class T, class Runtime> struct TScopedStructBinding<T, Runtime, void> : FBothStructId`  
_L371-390_
- inherits: `FBothStructId`
- desc: Specialization for schemabound structs
- L299 _public typedef_ `using Ids = typename Runtime::Ids;`
- L300 _public typedef_ `using Typename = TCustomTypename<CustomBinding>::Type;`
- L301 _public member_ `static constexpr uint32 N = sizeof(CustomBinding::MemberIds) / sizeof(CustomBinding::MemberIds[0]);`
- L308 _public function_ `explicit TScopedStructBinding(FDualStructId Dual) : TScopedStructBinding(FBothStructId{Dual, Dual})`
- L312 _public function_ `explicit TScopedStructBinding(FBothStructId Both) : TScopedStructBinding(Both, TCustomSpecifier<Ids, N>())`
- L316 _public function_ `TScopedStructBinding(FBothStructId Both, TCustomSpecifier<Ids, N>&& Init) : FBothStructId(Both) , CustomBinding( Init)`
- L327 _public function_ `~TScopedStructBinding()`
- L332 _public function_ `virtual void SaveCustom(FMemberBuilder& Dst, const void* Src, TDependent<Ids>::Baseline Base, const FSaveContext& Ctx) override`
- L338 _public function_ `virtual void LoadCustom(void* Dst, TDependent<Ids>::StructLoadView Src, ECustomLoadMethod Method) const override`
- L350 _public function_ `virtual bool DiffCustom(const void* A, const void* B, const FBindContext& Ctx) const override`
- L355 _public function_ `virtual bool DiffCustom(const void* A, const void* B, FDiffContext& Ctx) const override`
- L360 _public function_ `virtual void PlanCustom(FMemcpyLoadPlan& Out) const override`
- L374 _public typedef_ `using Typename = TTypename<T>;`

#### struct `PlainProps::TScopedEnumDeclaration`  
`template<Enumeration Enum, EEnumMode Mode, class Runtime> struct TScopedEnumDeclaration`  
_L393-400_
- L395 _public typedef_ `using Ids = typename Runtime::Ids;`
- L397 _public member_ `FEnumId Id;`
- L398 _public function_ `TScopedEnumDeclaration() : Id(DeclareNativeEnum<Enum, Mode, Ids>(Runtime::GetEnums(), LeafWidth<sizeof(Enum)>))`
- L399 _public function_ `~TScopedEnumDeclaration()`

#### struct `PlainProps::TInnermostType`  
`template<typename RangeBinding, uint32 NestLevel> struct TInnermostType`  
_L460-464_
- L462 _public typedef_ `using InnerType = typename RangeBinding::ItemType;`
- L463 _public typedef_ `using Type = TInnermostType<RangeBind<InnerType>, NestLevel - 1>::Type;`
- L469 _public typedef_ `using Type = typename RangeBinding::ItemType;`

#### struct `PlainProps::TInnermostType`  
`template<typename RangeBinding> struct TInnermostType<RangeBinding, 1>`  
_L467-470_
- L462 _public typedef_ `using InnerType = typename RangeBinding::ItemType;`
- L463 _public typedef_ `using Type = TInnermostType<RangeBind<InnerType>, NestLevel - 1>::Type;`
- L469 _public typedef_ `using Type = typename RangeBinding::ItemType;`

#### struct `PlainProps::GetRangeBindings::FOnce`  
`struct FOnce`  
_L475-483_
- L477 _public function_ `FOnce(FAnsiStringView RangeBindName) : Instance(Ids::IndexTypename(RangeBindName)) , Binding(Instance, RangeSizeOf(typename RangeBinding::SizeType{}))`
- L481 _public member_ `RangeBinding Instance;`
- L482 _public member_ `FRangeBinding Binding;`

#### struct `PlainProps::GetRangeBindings::FNestedOnce`  
`struct FNestedOnce : FOnce`  
_L495-504_
- inherits: `FOnce`
- L497 _public function_ `FNestedOnce() : FOnce(ToAnsiView(InnerRangeBinding::BindName))`
- L503 _public member_ `uint8 NestedBindings[sizeof(FRangeBinding) * (N - 1)] = {};`

#### struct `PlainProps::FAuxMember`  
`struct FAuxMember`  
_L628-633_
- L630 _public member_ `FMemberId Name;`
- L631 _public member_ `FMemberBinding Binding;`
- L632 _public member_ `FMemberSpec Spec;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlainProps`
- L16 _function_ `inline FAnsiStringView ToAnsiView(std::string_view Str)` (scope `PlainProps`)
- L24 _typedef_ `template<typename T> using RangeBind = typename TRangeBind<T>::Type;` (scope `PlainProps`)
- L36 _typedef_ `template<typename T> using CustomBind = typename TCustomBind<T>::Type;` (scope `PlainProps`)
- L39 _typedef_ `template<typename T> using CustomDeltaBind = typename TCustomDeltaBind<T>::Type;` (scope `PlainProps`)
- L55 _function_ `template<class Ids, class Typename> FScopeId GetOuterScope()` (scope `PlainProps`)
- L61 _function_ `template<class Ids, class Typename> FScopeId IndexScope()` (scope `PlainProps`)
- L69 _function_ `template<class Ids, class Typename> FScopeId IndexScope() requires (Typename::Namespace.size() > 0)` (scope `PlainProps`)
- L77 _function_ `template<ETypename Kind, class Typename> constexpr std::string_view SelectStructName()` (scope `PlainProps`)
- L90 _function_ `template<class Ids, ETypename Kind, class Typename> FType IndexStructName()` (scope `PlainProps`)
- L108 _variable_ `FBothStructId Out;` (scope `PlainProps`)
- L114 _variable_ `FType BindName = IndexStructName<Ids, ETypename::Bind, Typename>();` (scope `PlainProps`)
- L129 _function_ `template<class Ids, typename Struct> FDeclId GetStructDeclId()` (scope `PlainProps`) — Cached by function static
- L137 _function_ `template<class Ids, typename Struct> FBindId GetStructBindId()` (scope `PlainProps`) — Cached by function static
- L145 _function_ `template<class Ids, typename Struct> FBothStructId GetStructBothId()` (scope `PlainProps`) — Cached by function static
- L153 _function_ `template<class Ids, typename Struct> FDualStructId GetStructDualId()` (scope `PlainProps`) — Cached by function static
- L160 _function_ `template<class Ids, Enumeration Enum> FType IndexEnumName()` (scope `PlainProps`)
- L162 _typedef_ `using Typename = TTypename<Enum>;` (scope `PlainProps::IndexEnumName`)
- L168 _function_ `template<class Ids, Enumeration Enum> FEnumId GetEnumId()` (scope `PlainProps`) — Cached by function static
- L175 _function_ `template<class Ids, Arithmetic T> FType IndexArithmeticName()` (scope `PlainProps`)
- L182 _function_ `template<class Ids, ETypename, Arithmetic Leaf> FType IndexParameterName()` (scope `PlainProps`)
- L188 _function_ `template<class Ids, ETypename, Enumeration Enum> FType IndexParameterName()` (scope `PlainProps`)
- L194 _function_ `template<class Ids, ETypename Kind, typename T> FType IndexParameterName()` (scope `PlainProps`)
- L196 _typedef_ `using RangeBinding = RangeBind<T>;` (scope `PlainProps::IndexParameterName`)
- L213 _typedef_ `using Typename = TTypename<T>;` (scope `PlainProps::IndexParameterName`)
- L221 _function_ `template<class Ids, ETypename Kind, typename... Ts> FType IndexParametricType(FType TemplatedType, const std::tuple<Ts...>*)` (scope `PlainProps`)
- L233 _typedef_ `using InnerStructArray = TArray<FInnerStruct, TInlineAllocator<8>>;` (scope `PlainProps`)
- L302 _prototype_ `static constexpr bool bFastLoad = requires(FMemcpyLoadPlan& O)` (scope `PlainProps::TScopedStructBinding::CustomBinding`)
- L383 _prototype_ `BindNativeStruct<CttiOf<T>, Runtime>( Runtime::GetSchemas(), Both, TOccupancyOf<T>::Value);` (scope `PlainProps::TScopedStructBinding::Runtime`)
- L403 _function_ `template<class Struct, typename CustomBinding, class Runtime> FBothStructId BindCustomStructOnce()` (scope `PlainProps`)
- L411 _variable_ `inline constexpr FMemberBindType DefaultStructBindType = FMemberBindType(FStructType{EMemberKind::Struct, 0, 0});` (scope `PlainProps`)
- L412 _variable_ `inline constexpr FMemberBindType SuperStructBindType = FMemberBindType(FStructType{EMemberKind::Struct, 0, 1});` (scope `PlainProps`)
- L414 _function_ `inline FMemberBindType BindInnerStruct(FOptionalInnerId& OutBindId, FMemberSpec& OutSpec, FBothStructId Both)` (scope `PlainProps`)
- L421 _function_ `inline FMemberBindType BindInnerLeaf(FOptionalInnerId& OutId, FMemberSpec& OutSpec, FUnpackedLeafType Leaf, FOptionalEnumId Id)` (scope `PlainProps`)
- L429 _function_ `template<typename Struct, class Ids> FMemberBindType BindInnermostType(FOptionalInnerId& OutBindId, FMemberSpec& OutSpec)` (scope `PlainProps`)
- L435 _function_ `template<Arithmetic Type, class Ids> FMemberBindType BindInnermostType(FOptionalInnerId& OutId, FMemberSpec& OutSpec)` (scope `PlainProps`)
- L441 _function_ `template<Enumeration Enum, class Ids> FMemberBindType BindInnermostType(FOptionalInnerId& OutId, FMemberSpec& OutSpec)` (scope `PlainProps`)
- L447 _function_ `template<typename RangeBinding> constexpr uint32 CountRangeBindings()` (scope `PlainProps`)
- L449 _typedef_ `using InnerBinding = RangeBind<typename RangeBinding::ItemType>;` (scope `PlainProps::CountRangeBindings`)
- L454 _function_ `template<> constexpr uint32 CountRangeBindings<void>()` (scope `PlainProps`)
- L473 _function_ `template<typename RangeBinding, typename Ids, uint32 N> TConstArrayView<FRangeBinding> GetRangeBindings() requires (N > 0)` (scope `PlainProps`)
- L492 _typedef_ `using InnerType = typename RangeBinding::ItemType;` (scope `PlainProps::GetRangeBindings`)
- L493 _typedef_ `using InnerRangeBinding = RangeBind<InnerType>;` (scope `PlainProps::GetRangeBindings`)
- L514 _function_ `template<LeafType Type, class Runtime> FMemberBinding BindMember(uint64 Offset, FMemberSpec& OutSpec)` (scope `PlainProps`)
- L522 _function_ `template<typename Type, class Runtime> FMemberBinding BindMember(uint64 Offset, FMemberSpec& OutSpec)` (scope `PlainProps`)
- L524 _typedef_ `using Ids = typename Runtime::Ids;` (scope `PlainProps::BindMember`)
- L525 _typedef_ `using CustomBinding = typename Runtime::template CustomBindings<Type>::Type;` (scope `PlainProps::BindMember`)
- L533 _typedef_ `using Typename = typename TCustomTypename<CustomBinding>::Type;` (scope `PlainProps::BindMember`)
- L545 _typedef_ `using RangeBinding = RangeBind<Type>;` (scope `PlainProps::BindMember`)
- L549 _typedef_ `using InnermostType = typename TInnermostType<RangeBinding, NumRangeBindings>::Type;` (scope `PlainProps::BindMember`)
- L572 _function_ `template<Enumeration Enum, EEnumMode Mode, class Ids> FEnumId DeclareNativeEnum(FEnumDeclarations& Out, ELeafWidth Width)` (scope `PlainProps`)
- L574 _typedef_ `using Ctti = CttiOf<Enum>;` (scope `PlainProps::DeclareNativeEnum`)
- L576 _typedef_ `using UnsignedUnderlyingType = std::make_unsigned_t<std::underlying_type_t<typename Ctti::Type>>;` (scope `PlainProps::DeclareNativeEnum`) — Never sign extend negative enum constant values of width B8, B16 and B32
- L594 _function_ `template<class Ctti, class Runtime> void BindNativeStruct(FSchemaBindings& Out, FBothStructId Both, EMemberPresence Occupancy)` (scope `PlainProps`)
- L596 _typedef_ `using Ids = Runtime::Ids;` (scope `PlainProps::BindNativeStruct`)
- L597 _typedef_ `using SuperType = typename Ctti::Super;` (scope `PlainProps::BindNativeStruct`)
- L636 _function_ `template<class Ctti, class Runtime> TStaticArray<FAuxMember, Ctti::NumVars> BindAuxMembers()` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsBuild.h` (Public)


#### class `PlainProps::FScratchAllocator`  
`class FScratchAllocator`  
_L24-88_
- desc: Single-threaded scratch allocator for intermediate built representation
- L32 _private member_ `static constexpr uint32 PageSize = 65536;`
- L33 _private member_ `static constexpr uint32 DataSize = PageSize - offsetof(FPage, Data);`
- L35 _private member_ `uint8* Cursor = nullptr;`
- L36 _private member_ `uint8* PageEnd = nullptr;`
- L37 _private member_ `FPage* LastPage = nullptr;`
- L39 _private prototype_ `uint8* AllocateInNewPage(SIZE_T Size, uint32 Alignment);`
- L43 _public prototype_ `FScratchAllocator() = default;`
- L44 _public function_ `~FScratchAllocator()`
- L46 _public function_ `inline void* Allocate(SIZE_T Size, uint32 Alignment)`
- L58 _public function_ `inline void* AllocateZeroed(SIZE_T Size, uint32 Alignment)`
- L66 _public function_ `template<typename T, typename... Ts> inline T* AllocateArray(uint64 Num, Ts... ConstructorParams)`
- L77 _public function_ `template<typename T> inline T* CloneArray(uint64 Num, const T* In)`
- L87 _public prototype_ `void Reset();`

#### struct `PlainProps::FScratchAllocator::FPage`  
`struct FPage`  
_L26-30_
- L28 _public member_ `FPage* PrevPage;`
- L29 _public member_ `uint8 Data[0];`

#### struct `PlainProps::FMemberSchema`  
`struct FMemberSchema`  
_L92-117_
- L94 _public member_ `FMemberType Type;`
- L95 _public member_ `FMemberType InnerRangeType;`
- L96 _public member_ `uint16 NumInnerRanges;`
- L97 _public member_ `FOptionalInnerId InnerSchema;`
- L98 _public member_ `const FMemberType* NestedRangeTypes;`
- L100 _public function_ `TConstArrayView<FMemberType> GetInnerRangeTypes() const`
- L105 _public function_ `FMemberType GetInnermostType() const`
- L110 _public prototype_ `[[nodiscard]] FMemberType& EditInnermostType(FScratchAllocator& Scratch);`
- L112 _public function_ `void CheckInvariants()`

#### struct `PlainProps::FTypedRange`  
`struct FTypedRange`  
_L154-158_
- L156 _public member_ `FMemberSchema Schema;`
- L157 _public member_ `FBuiltRange* Values = nullptr;`

#### union `PlainProps::FBuiltValue`  
`union FBuiltValue`  
_L273-278_
- L275 _public member_ `uint64 Leaf;`
- L276 _public member_ `FBuiltStruct* Struct;`
- L277 _public member_ `FBuiltRange* Range;`

#### struct `PlainProps::FTypedValue`  
`struct FTypedValue`  
_L280-284_
- L282 _public member_ `FMemberSchema Schema;`
- L283 _public member_ `FBuiltValue Value;`

#### struct `PlainProps::FBuiltMember`  
`struct FBuiltMember`  
_L286-298_
- L288 _public function_ `FBuiltMember(FMemberId InName, FTypedValue In) : FBuiltMember(InName, In.Schema, In.Value)`
- L289 _public function_ `FBuiltMember(FOptionalMemberId N, FMemberSchema S, FBuiltValue V) : Name(N), Schema(MoveTemp(S)), Value(V)`
- L290 _public prototype_ `FBuiltMember(FMemberId Name, FUnpackedLeafType Leaf, FOptionalEnumId Id, uint64 Value);`
- L291 _public prototype_ `FBuiltMember(FMemberId Name, FTypedRange Range);`
- L292 _public prototype_ `FBuiltMember(FMemberId Name, FStructId Id, FBuiltStruct* Value);`
- L293 _public prototype_ `static FBuiltMember MakeSuper(FStructId Id, FBuiltStruct* Value);`
- L295 _public member_ `FOptionalMemberId Name;`
- L296 _public member_ `FMemberSchema Schema;`
- L297 _public member_ `FBuiltValue Value;`

#### class `PlainProps::FMemberBuilder`  
`class FMemberBuilder`  
_L303-355_
- desc: Builds an ordered list of properties to be saved
- L307 _public function_ `template<Arithmetic T> void Add(FMemberId Name, T Value)`
- L313 _public function_ `template<Enumeration T> void AddEnum(FMemberId Name, FEnumId Id, T Value)`
- L319 _public function_ `template<UnsignedIntegral T> void AddEnum(FMemberId Name, FEnumId Id, T Value)`
- L325 _public function_ `template<UnsignedIntegral T> void AddHex(FMemberId Name, T Value)`
- L330 _public function_ `void AddLeaf(FMemberId Name, FUnpackedLeafType Leaf, FOptionalEnumId Enum, uint64 Value)`
- L331 _public function_ `void AddRange(FMemberId Name, FTypedRange Range)`
- L333 _public function_ `void AddStruct(FMemberId Name, FStructId Id, FBuiltStruct* Struct)` — Add already built nested struct, must not be null
- L334 _public function_ `void Add(FMemberId Name, FTypedValue TypedValue)`
- L337 _public prototype_ `void AddSuperStruct(FStructId SuperSchema, FBuiltStruct* SuperStruct);` — Add already built super struct, must not be null and must be the first member added
- L340 _public prototype_ `void BuildSuperStruct(FScratchAllocator& Scratch, const FStructDeclaration& Super, const FDebugIds& Debug);` — Build members into a single nested super struct member, no-op if no non-super members has been added
- L342 _public prototype_ `[[nodiscard]] FBuiltStruct* BuildAndReset(FScratchAllocator& Scratch, const FStructDeclaration& Declared, const FDebugIds& Debug);`
- L344 _public function_ `bool IsEmpty() const`
- L347 _private typedef_ `using FBuiltMemberArray = TArray<FBuiltMember, TInlineAllocator<16>>;`
- L349 _private member_ `FBuiltMemberArray Members;`

#### struct `PlainProps::FDenseMemberBuilder`  
`struct FDenseMemberBuilder`  
_L358-373_
- desc: Rough API draft
- L360 _public member_ `FScratchAllocator& Scratch;`
- L361 _public member_ `const FDebugIds& Debug;`
- L364 _public function_ `template<typename T, typename... Ts> [[nodiscard]] FBuiltStruct* BuildHomogeneous(const FStructDeclaration& Declaration, T Head, Ts... Tail) const`
- L372 _private prototype_ `[[nodiscard]] FBuiltStruct* BuildHomo(const FStructDeclaration& Declaration, FMemberType Leaf, TConstArrayView<FBuiltValue> Values) const;`

#### class `PlainProps::FStructRangeBuilder`  
`class FStructRangeBuilder`  
_L376-397_
- desc: Helper class for building struct ranges
- L379 _public function_ `FStructRangeBuilder(uint64 Num, ESizeType InSizeType) : SizeType(InSizeType)`
- L386 _public function_ `template<typename IntType> explicit FStructRangeBuilder(IntType Num) : FStructRangeBuilder(static_cast<uint64>(Num), RangeSizeOf(Num))`
- L390 _public function_ `FMemberBuilder& operator[](uint64 Idx)`
- L392 _public prototype_ `FTypedRange BuildAndReset(FScratchAllocator& Scratch, const FStructDeclaration& Declared, const FDebugIds& Debug);`
- L395 _private member_ `TArray64<FMemberBuilder> Structs;`
- L396 _private member_ `ESizeType SizeType;`

#### class `PlainProps::FNestedRangeBuilder`  
`class FNestedRangeBuilder`  
_L401-423_
- desc: Helper class for building nested ranges
- L404 _public function_ `FNestedRangeBuilder(FMemberSchema InSchema, int64 InitialReserve) : Schema(InSchema)`
- L410 _public prototype_ `~FNestedRangeBuilder();`
- L412 _public function_ `void Add(FTypedRange Range)`
- L418 _public prototype_ `[[nodiscard]] FTypedRange BuildAndReset(FScratchAllocator& Scratch, ESizeType SizeType);`
- L421 _private member_ `TArray64<FBuiltRange*> Ranges;`
- L422 _private member_ `FMemberSchema Schema;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlainProps`
- L119 _function_ `inline bool operator==(FMemberSchema A, FMemberSchema B)` (scope `PlainProps`)
- L131 _function_ `template<Arithmetic T> inline T Normalize(T Value)` (scope `PlainProps`)
- L132 _function_ `inline float Normalize(float Value)` (scope `PlainProps`) — todo
- L133 _function_ `inline double Normalize(double Value)` (scope `PlainProps`) — todo
- L137 _function_ `inline uint64 ValueCast(bool Value)` (scope `PlainProps`)
- L138 _function_ `inline uint64 ValueCast(int8 Value)` (scope `PlainProps`)
- L139 _function_ `inline uint64 ValueCast(int16 Value)` (scope `PlainProps`)
- L140 _function_ `inline uint64 ValueCast(int32 Value)` (scope `PlainProps`)
- L141 _function_ `inline uint64 ValueCast(int64 Value)` (scope `PlainProps`)
- L142 _function_ `inline uint64 ValueCast(uint8 Value)` (scope `PlainProps`)
- L143 _function_ `inline uint64 ValueCast(uint16 Value)` (scope `PlainProps`)
- L144 _function_ `inline uint64 ValueCast(uint32 Value)` (scope `PlainProps`)
- L145 _function_ `inline uint64 ValueCast(uint64 Value)` (scope `PlainProps`)
- L146 _prototype_ `uint64 ValueCast(float Value);` (scope `PlainProps`)
- L147 _prototype_ `uint64 ValueCast(double Value);` (scope `PlainProps`)
- L148 _function_ `inline uint64 ValueCast(char8_t Value)` (scope `PlainProps`)
- L149 _function_ `inline uint64 ValueCast(char16_t Value)` (scope `PlainProps`)
- L150 _function_ `inline uint64 ValueCast(char32_t Value)` (scope `PlainProps`)
- L161 _function_ `template<Arithmetic T> FMemberSchema MakeLeafRangeSchema(ESizeType MaxSize)` (scope `PlainProps`)
- L167 _function_ `template<Arithmetic T, typename SizeType> FMemberSchema MakeLeafRangeSchema()` (scope `PlainProps`)
- L173 _function_ `template<UnsignedIntegral T> FMemberSchema MakeHexRangeSchema(ESizeType MaxSize)` (scope `PlainProps`)
- L179 _function_ `template<Enumeration T> FMemberSchema MakeEnumRangeSchema(FEnumId Id, ESizeType MaxSize)` (scope `PlainProps`)
- L185 _function_ `template<Enumeration T, typename SizeType> FMemberSchema MakeEnumRangeSchema(FEnumId Id)` (scope `PlainProps`)
- L191 _function_ `template<UnsignedIntegral T> FMemberSchema MakeEnumRangeSchema(FEnumId Id, ESizeType MaxSize)` (scope `PlainProps`)
- L196 _variable_ `inline constexpr FMemberType DefaultStructType = FMemberType(FStructType{EMemberKind::Struct, 0, 0});` (scope `PlainProps`)
- L197 _variable_ `inline constexpr FMemberType SuperStructType = FMemberType(FStructType{EMemberKind::Struct, 0, 1});` (scope `PlainProps`)
- L198 _variable_ `inline constexpr FMemberType DynamicStructType = FMemberType(FStructType{EMemberKind::Struct, 1, 0});` (scope `PlainProps`)
- L201 _function_ `inline FMemberSchema MakeStructRangeSchema(ESizeType SizeType, FStructId Id)` (scope `PlainProps`)
- L206 _function_ `inline FMemberSchema MakeDynamicStructRangeSchema(ESizeType SizeType)` (scope `PlainProps`)
- L211 _prototype_ `FMemberSchema MakeNestedRangeSchema(FScratchAllocator& Scratch, ESizeType SizeType, FMemberSchema InnerRangeSchema);` (scope `PlainProps`)
- L215 _prototype_ `[[nodiscard]] FBuiltRange* CloneLeaves(FScratchAllocator& Scratch, uint64 Num, const void* Data, SIZE_T LeafSize);` (scope `PlainProps`)
- L218 _function_ `template<Arithmetic T> [[nodiscard]] FTypedRange BuildLeafRange(FScratchAllocator& Scratch, ESizeType SizeType, const T* Values, uint64 Num)` (scope `PlainProps`)
- L225 _function_ `template<Arithmetic T, typename SizeType> [[nodiscard]] FTypedRange BuildLeafRange(FScratchAllocator& Scratch, const T* Values, SizeType Num)` (scope `PlainProps`)
- L231 _function_ `template<Arithmetic T> [[nodiscard]] FTypedRange BuildLeafRange(FScratchAllocator& Scratch, ESizeType SizeType, TConstArrayView<T> Values)` (scope `PlainProps`)
- L237 _function_ `template<Arithmetic T, typename SizeType> [[nodiscard]] FTypedRange BuildLeafRange(FScratchAllocator& Scratch, TConstArrayView<T, SizeType> Values)` (scope `PlainProps`)
- L243 _function_ `template<UnsignedIntegral T, typename SizeType> [[nodiscard]] FTypedRange BuildHexRange(FScratchAllocator& Scratch, TConstArrayView<T, SizeType> Values)` (scope `PlainProps`)
- L249 _function_ `template<UnsignedIntegral T> [[nodiscard]] FTypedRange BuildHexRange(FScratchAllocator& Scratch, ESizeType SizeType, TConstArrayView<T> Values)` (scope `PlainProps`)
- L255 _function_ `template<Enumeration T, typename SizeType> [[nodiscard]] FTypedRange BuildEnumRange(FScratchAllocator& Scratch, FEnumId Enum, TConstArrayView<T, SizeType> Values)` (scope `PlainProps`)
- L261 _function_ `template<UnsignedIntegral T> [[nodiscard]] FTypedRange BuildEnumRange(FScratchAllocator& Scratch, FEnumId Enum, ESizeType SizeType, TConstArrayView<T> Values)` (scope `PlainProps`)
- L266 _function_ `[[nodiscard]] inline FTypedRange MakeStructRange(FStructId Id, ESizeType SizeType, FBuiltRange* Values )` (scope `PlainProps`)
- L428 _function_ `inline void* operator new(std::size_t Size, PlainProps::FScratchAllocator& Scratch)`
- L433 _function_ `inline void* operator new(std::size_t Size, std::align_val_t Align, PlainProps::FScratchAllocator& Scratch)`

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsBuildSchema.h` (Public)


#### struct `PlainProps::FBuiltStructSchema`  
`struct FBuiltStructSchema`  
_L18-26_
- L20 _public member_ `FType Type;`
- L21 _public member_ `FStructId Id;`
- L22 _public member_ `FOptionalStructId Super;`
- L23 _public member_ `bool bDense = false;`
- L24 _public member_ `TArray<FMemberId> MemberNames;`
- L25 _public member_ `TArray<const FMemberSchema*> MemberSchemas;`

#### struct `PlainProps::FBuiltEnumSchema`  
`struct FBuiltEnumSchema`  
_L28-36_
- L30 _public member_ `FType Type;`
- L31 _public member_ `FEnumId Id;`
- L32 _public member_ `EEnumMode Mode = EEnumMode::Flat;`
- L33 _public member_ `ELeafWidth Width = ELeafWidth::B8;`
- L34 _public member_ `TArray<FNameId> Names;`
- L35 _public member_ `TArray<uint64> Constants;`

#### struct `PlainProps::FBuiltSchemas`  
`struct FBuiltSchemas`  
_L38-42_
- L40 _public member_ `TArray<FBuiltStructSchema> Structs;` — Same size as number of declared structs
- L41 _public member_ `TArray<FBuiltEnumSchema> Enums;` — Same size as number of declared enums

#### class `PlainProps::FSchemasBuilder`  
`class FSchemasBuilder`  
_L44-73_
- L48 _public prototype_ `FSchemasBuilder(const FIds& Names, const IDeclarations& Types, FScratchAllocator& InScratch, ESchemaFormat InFormat);`
- L49 _public prototype_ `~FSchemasBuilder();`
- L51 _public prototype_ `FEnumSchemaBuilder& NoteEnum(FEnumId Id);`
- L52 _public prototype_ `FStructSchemaBuilder& NoteStruct(FStructId Id);`
- L53 _public prototype_ `void NoteStructAndMembers(FStructId Id, const FBuiltStruct& Struct);`
- L54 _public prototype_ `FBuiltSchemas Build();`
- L56 _public function_ `FScratchAllocator& GetScratch() const`
- L57 _public function_ `const FIds& GetIds() const`
- L58 _public function_ `FDebugIds GetDebug() const`
- L61 _private member_ `const IDeclarations& Declarations;`
- L62 _private member_ `TSet<FStructId> StructIndices;`
- L63 _private member_ `TSet<FEnumId> EnumIndices;`
- L64 _private member_ `const FIds& Ids;`
- L65 _private member_ `ESchemaFormat Format;`
- L66 _private member_ `TPagedArray<FStructSchemaBuilder, 4096> Structs;` — TPagedArray for stable references
- L67 _private member_ `TPagedArray<FEnumSchemaBuilder, 4096> Enums;` — TPagedArray for stable references
- L68 _private member_ `FScratchAllocator& Scratch;`
- L69 _private member_ `FDebugIds Debug;`
- L70 _private member_ `bool bBuilt = false;`
- L72 _private prototype_ `void NoteInheritanceChains();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PlainProps`
- L76 _prototype_ `[[nodiscard]] TArray<FStructId> ExtractRuntimeIds(const FBuiltSchemas& In);` (scope `PlainProps`) — Extract runtime ids to side-channel for loading to avoid reindexing with IndexRuntimeIds()

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsCtti.h` (Public)


#### struct `PlainProps::TCttiOf`  
`template<typename T> struct TCttiOf`  
_L13-13_
- L13 _public typedef_ `template<typename T> struct TCttiOf { using Type = decltype(CttiOfPtr((T*)nullptr)); };`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlainProps`
- L14 _typedef_ `template<typename T> struct TCttiOf { using Type = decltype(CttiOfPtr((T*)nullptr)); };` (scope `PlainProps`)
- L16 _namespace_ `namespace Private` (scope `PlainProps`)
- L19 _function_ `template<class Ctti> constexpr bool ValidateEnumFlags()` (scope `PlainProps::Private`)
- L21 _typedef_ `using EnumType = Ctti::Type;` (scope `PlainProps::Private::ValidateEnumFlags`)
- L22 _typedef_ `using UnsignedUnderlyingType = std::make_unsigned_t<std::underlying_type_t<EnumType>>;` (scope `PlainProps::Private::ValidateEnumFlags`)
- L37 _macro_ `#define _PP_EXPAND(X) X`
- L39 _macro_ `#define _PP_NUM_ARGS_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16, N, ...) N`
- L40 _macro_ `#define _PP_NUM_ARGS(...) _PP_NUM_ARGS_(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)`
- L42 _macro_ `#define _PP_REFLECT_1( N, MACRO, NS, T, M) MACRO(N-1, NS, T, M)`
- L43 _macro_ `#define _PP_REFLECT_2( N, MACRO, NS, T, M, ...) MACRO(N-2, NS, T, M) _PP_REFLECT_1(N, MACRO, NS, T, __VA_ARGS__)`
- L44 _macro_ `#define _PP_REFLECT_3( N, MACRO, NS, T, M, ...) MACRO(N-3, NS, T, M) _PP_REFLECT_2(N, MACRO, NS, T, __VA_ARGS__)`
- L45 _macro_ `#define _PP_REFLECT_4( N, MACRO, NS, T, M, ...) MACRO(N-4, NS, T, M) _PP_REFLECT_3(N, MACRO, NS, T, __VA_ARGS__)`
- L46 _macro_ `#define _PP_REFLECT_5( N, MACRO, NS, T, M, ...) MACRO(N-5, NS, T, M) _PP_REFLECT_4(N, MACRO, NS, T, __VA_ARGS__)`
- L47 _macro_ `#define _PP_REFLECT_6( N, MACRO, NS, T, M, ...) MACRO(N-6, NS, T, M) _PP_REFLECT_5(N, MACRO, NS, T, __VA_ARGS__)`
- L48 _macro_ `#define _PP_REFLECT_7( N, MACRO, NS, T, M, ...) MACRO(N-7, NS, T, M) _PP_REFLECT_6(N, MACRO, NS, T, __VA_ARGS__)`
- L49 _macro_ `#define _PP_REFLECT_8( N, MACRO, NS, T, M, ...) MACRO(N-8, NS, T, M) _PP_REFLECT_7(N, MACRO, NS, T, __VA_ARGS__)`
- L50 _macro_ `#define _PP_REFLECT_9( N, MACRO, NS, T, M, ...) MACRO(N-9, NS, T, M) _PP_REFLECT_8(N, MACRO, NS, T, __VA_ARGS__)`
- L51 _macro_ `#define _PP_REFLECT_10(N, MACRO, NS, T, M, ...) MACRO(N-10, NS, T, M) _PP_REFLECT_9(N, MACRO, NS, T, __VA_ARGS__)`
- L52 _macro_ `#define _PP_REFLECT_11(N, MACRO, NS, T, M, ...) MACRO(N-11, NS, T, M) _PP_REFLECT_10(N, MACRO, NS, T, __VA_ARGS__)`
- L53 _macro_ `#define _PP_REFLECT_12(N, MACRO, NS, T, M, ...) MACRO(N-12, NS, T, M) _PP_REFLECT_11(N, MACRO, NS, T, __VA_ARGS__)`
- L54 _macro_ `#define _PP_REFLECT_13(N, MACRO, NS, T, M, ...) MACRO(N-13, NS, T, M) _PP_REFLECT_12(N, MACRO, NS, T, __VA_ARGS__)`
- L55 _macro_ `#define _PP_REFLECT_14(N, MACRO, NS, T, M, ...) MACRO(N-14, NS, T, M) _PP_REFLECT_13(N, MACRO, NS, T, __VA_ARGS__)`
- L56 _macro_ `#define _PP_REFLECT_15(N, MACRO, NS, T, M, ...) MACRO(N-15, NS, T, M) _PP_REFLECT_14(N, MACRO, NS, T, __VA_ARGS__)`
- L57 _macro_ `#define _PP_REFLECT_16(N, MACRO, NS, T, M, ...) MACRO(N-16, NS, T, M) _PP_REFLECT_15(N, MACRO, NS, T, __VA_ARGS__)`
- L58 _macro_ `#define _PP_REFLECT_THINGS(N, MACRO, ...) _PP_EXPAND(_PP_REFLECT_##N(N, MACRO, __VA_ARGS__))`
- L60 _macro_ `#define _PP_REFLECT_ENUM_INNER(NS, T, S, ...) struct T##_Ctti \`
- L74 _macro_ `#define _PP_REFLECT_STRUCT(N, NS, T, S, ...) PP_REFLECT_STRUCT_ONLY(N, NS, T, S) _PP_EXPAND(_PP_REFLECT_THINGS(N, PP_REFLECT_MEMBER, NS, T, __VA_ARGS__))`
- L75 _macro_ `#define _PP_REFLECT_STRUCT_TEMPLATE(N, NS, T, S, ...) PP_REFLECT_STRUCT_TEMPLATE_ONLY(N, NS, T, S) _PP_EXPAND(_PP_REFLECT_THINGS(N, PP_REFLECT_TEMPLATE_MEMBER, NS, T, __VA_ARGS__))`
- L79 _macro_ `#define PP_REFLECT_ENUM(NS, T, ...) _PP_REFLECT_ENUM_INNER(NS, T, #__VA_ARGS__, __VA_ARGS__)`
- L80 _macro_ `#define PP_REFLECT_FLAG_ENUM(NS, T, ...) _PP_REFLECT_ENUM_INNER(NS, T, #__VA_ARGS__, __VA_ARGS__); static_assert(::PlainProps::Private::ValidateEnumFlags<T##_Ctti>(), "Flag enum " #T " must use one bit per enumerator")`
- L81 _macro_ `#define PP_REFLECT_STRUCT(NS, T, S, ...) _PP_REFLECT_STRUCT(_PP_NUM_ARGS(__VA_ARGS__), NS, T, S, __VA_ARGS__)`
- L82 _macro_ `#define PP_REFLECT_STRUCT_TEMPLATE(NS, T, S, ...) _PP_REFLECT_STRUCT_TEMPLATE(_PP_NUM_ARGS(__VA_ARGS__), NS, T, S, __VA_ARGS__)`
- L83 _macro_ `#define PP_NAME_STRUCT(NS, T) struct T##_Ctti { inline static constexpr char Name[] = #T; using Type = NS :: T; inline static constexpr char Namespace[] = #NS; }; T##_Ctti CttiOfPtr(T*);`
- L84 _macro_ `#define PP_NAME_STRUCT_TEMPLATE(NS, T) template<class... Ts> struct T##_Ctti { inline static constexpr char Name[] = #T; using Type = NS :: T<Ts...>; using TemplateArgs = std::tuple<Ts...>; inline static constexpr char Namespace[] = #NS; };`
- L88 _macro_ `#define PP_REFLECT_STRUCT_ONLY(N, NS, T, S) struct T##_Ctti { inline static constexpr char Name[] = #T; using Type = NS :: T; using Super = S; static constexpr int NumVars = N; template<int> struct Var; inline static constexpr char Namespac`
- L89 _macro_ `#define PP_REFLECT_STRUCT_TEMPLATE_ONLY(N, NS, T, S) template<class... Ts> struct T##_Ctti { inline static constexpr char Name[] = #T; using Type = NS :: T<Ts...>; using Super = S; using TemplateArgs = std::tuple<Ts...>; static constexpr in`
- L90 _macro_ `#define PP_REFLECT_MEMBER(N, NS, T, M) template<> struct T##_Ctti::Var<N> { inline static constexpr char Name[] = #M; using Type = decltype(NS :: T :: M); static constexpr std::size_t Offset = offsetof(NS :: T, M); static constexpr auto Poi`
- L91 _macro_ `#define PP_REFLECT_BIT_MEMBER(N, NS, T, M, BYTEOFFSET, BITOFFSET) template<> struct T##_Ctti::Var<N> { inline static constexpr char Name[] = #M; using Type = decltype(NS :: T :: M); static constexpr std::size_t Offset = BYTEOFFSET; static c`
- L92 _macro_ `#define PP_REFLECT_TEMPLATE_MEMBER(N, NS, T, M) template<class... Ts> template <int _> struct T##_Ctti<Ts...>::Var_<N, _> { inline static constexpr char Name[] = #M; using Type = decltype(NS :: T<Ts...> :: M); static constexpr std::size_t O`
- L93 _macro_ `#define PP_REFLECT_TEMPLATE_BIT_MEMBER todo`
- L99 _function_ `template <class Ctti, typename Fn> static constexpr void ForEachVar(Fn&& Visitor)` (scope `PlainProps`) — E.g. ForEachVar<CttiOf<MyClass>>([]<class Var>() { printf(Var::Name); });
- L124 _member_ `template<class Ctti> concept Templated = requires { typename Ctti::TemplateArgs; };` (scope `PlainProps::Ctti`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsDeclare.h` (Public)


#### struct `PlainProps::FEnumerator`  
`struct FEnumerator`  
_L19-25_
- L21 _public member_ `FNameId Name;`
- L22 _public member_ `uint64 Constant;`

#### enum `PlainProps::EEnumMode`  
`enum class EEnumMode : uint8`  
_L27-27_
- L27 _public enumerator_ `enum class EEnumMode : uint8 { Flat, Flag }; struct FEnumDeclaration { FType Type; EEnumMode Mode; ELeafWidth Width; uint16 NumEnumerators;`
- L27 _public enumerator_ `enum class EEnumMode : uint8 { Flat, Flag }; struct FEnumDeclaration { FType Type; EEnumMode Mode; ELeafWidth Width; uint16 NumEnumerators;`

#### struct `PlainProps::FEnumDeclaration`  
`struct FEnumDeclaration`  
_L29-38_
- L31 _public member_ `FType Type;` — Could be removed
- L32 _public member_ `EEnumMode Mode;`
- L33 _public member_ `ELeafWidth Width;`
- L34 _public member_ `uint16 NumEnumerators;`
- L35 _public member_ `FEnumerator Enumerators[0];` — Constants must be unique, no aliases allowed
- L37 _public function_ `TConstArrayView<FEnumerator> GetEnumerators() const`

#### enum `PlainProps::EEnumAliases`  
`enum class EEnumAliases`  
_L44-44_
- desc: Enum values are stored as integers. Aliased enum values are illegal, including composite flags. Aliases can be automatically removed on declaration or detected and fail hard.
- L44 _public enumerator_ `enum class EEnumAliases { Strip, Fail }; class FEnumDeclarations { public: UE_NONCOPYABLE(FEnumDeclarations); explicit FEnumDeclarations(FDebugIds In) : Debug(In) {}` — Enum values are stored as integers. Aliased enum values are illegal, including composite flags. Aliases can be automatically removed on declaration or detected and fail hard.
- L44 _public enumerator_ `enum class EEnumAliases { Strip, Fail }; class FEnumDeclarations { public: UE_NONCOPYABLE(FEnumDeclarations); explicit FEnumDeclarations(FDebugIds In) : Debug(In) {}` — Enum values are stored as integers. Aliased enum values are illegal, including composite flags. Aliases can be automatically removed on declaration or detected and fail hard.

#### class `PlainProps::FEnumDeclarations`  
`class FEnumDeclarations`  
_L46-68_
- L50 _public function_ `explicit FEnumDeclarations(FDebugIds In) : Debug(In)`
- L52 _public prototype_ `const FEnumDeclaration& Declare(FEnumId Id, FType Type, EEnumMode Mode, ELeafWidth Width, TConstArrayView<FEnumerator> Enumerators, EEnumAliases Policy);`
- L53 _public function_ `void Drop(FEnumId Id)`
- L54 _public function_ `const FEnumDeclaration& Get(FEnumId Id) const`
- L55 _public function_ `const FEnumDeclaration* Find(FEnumId Id) const`
- L57 _public function_ `FDebugIds GetDebug() const`
- L60 _protected member_ `TArray<TUniquePtr<FEnumDeclaration>> Declarations;`
- L61 _protected member_ `FDebugIds Debug;`
- L64 _protected prototype_ `void Check(FEnumId Id) const;`
- L66 _protected function_ `void Check(FEnumId) const`

#### enum `PlainProps::EMemberPresence`  
`enum class EMemberPresence : uint8`  
_L72-72_
- L72 _public enumerator_ `enum class EMemberPresence : uint8 { RequireAll, AllowSparse }; struct FStructDeclaration { mutable std::atomic<int32> RefCount = {}; FDeclId Id; FOptionalDeclId Super; uint16 Version;`
- L72 _public enumerator_ `enum class EMemberPresence : uint8 { RequireAll, AllowSparse }; struct FStructDeclaration { mutable std::atomic<int32> RefCount = {}; FDeclId Id; FOptionalDeclId Super; uint16 Version;`

#### struct `PlainProps::FStructDeclaration`  
`struct FStructDeclaration`  
_L74-96_
- L76 _public member_ `mutable std::atomic<int32> RefCount = {};`
- L77 _public member_ `FDeclId Id;` — Could be removed, might allow declaration dedup among templated types
- L78 _public member_ `FOptionalDeclId Super;`
- L79 _public member_ `uint16 Version;`
- L80 _public member_ `uint16 NumMembers;`
- L81 _public member_ `uint16 NumInnerRanges;`
- L82 _public member_ `uint16 NumInnerIds;`
- L83 _public member_ `EMemberPresence Occupancy;`
- L84 _public member_ `FMemberId MemberNames[0];`
- L86 _public function_ `const FInnerId* GetInnerIds() const`
- L87 _public function_ `const FMemberType* GetTypes() const`
- L88 _public function_ `const FMemberType* GetInnerRangeTypes() const`
- L89 _public function_ `TConstArrayView<FMemberId> GetMemberOrder() const`
- L90 _public prototype_ `uint32 CalculateSize() const;`
- L92 _public function_ `void AddRef() const`
- L93 _public prototype_ `bool Release() const;`
- L95 _public member_ `inline static constexpr uint16 MaxMembers = 0xFFFF;`

#### struct `PlainProps::IDeclarations`  
`struct IDeclarations`  
_L106-115_
- L108 _public function_ `virtual ~IDeclarations()`
- L109 _public prototype_ `virtual FDeclId Lower(FBindId BindId) const = 0;`
- L110 _public prototype_ `virtual const FEnumDeclaration* Find(FEnumId Id) const = 0;`
- L111 _public prototype_ `virtual const FStructDeclaration* Find(FStructId Id) const = 0;`
- L113 _public prototype_ `const FEnumDeclaration& Get(FEnumId Id) const;`
- L114 _public prototype_ `const FStructDeclaration& Get(FStructId Id) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlainProps`
- L100 _typedef_ `using FStructDeclarationPtr = ::TRefCountPtr<const FStructDeclaration>;` (scope `PlainProps`)
- L102 _prototype_ `FStructDeclarationPtr Declare(FStructSpec Spec);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsDiff.h` (Public)


#### union `PlainProps::FDiffMetadata`  
`union FDiffMetadata`  
_L10-15_
- L12 _public member_ `FOptionalEnumId Leaf;`
- L13 _public member_ `FRangeBinding Range;`
- L14 _public member_ `FBindId Struct;`

#### struct `PlainProps::FDiffNode`  
`struct FDiffNode`  
_L18-26_
- desc: Currently lacking range indices
- L20 _public member_ `FMemberBindType Type;`
- L21 _public member_ `FOptionalMemberId Name;`
- L22 _public member_ `FDiffMetadata Meta;`
- L23 _public member_ `const void* A;`
- L24 _public member_ `const void* B;`
- L25 _public member_ `int32 PrecedingSibling = INDEX_NONE;` — Index of the previous sibling of the node in the tree chain.

#### struct `PlainProps::FDiffTree`  
`struct FDiffTree : public TArray<FDiffNode, TInlineAllocator<16>>`  
_L30-30_
- inherits: `TArray<FDiffNode,TInlineAllocator<16>>`
- desc: Flat tree of nodes. Nodes are linked via the index to a previous sibling. A tree can contain multiple diff paths.

#### enum `PlainProps::EDiffGather`  
`enum EDiffGather`  
_L32-32_
- L32 _public enumerator_ `enum EDiffGather { First, All }; struct FDiffContext : FBindContext { EDiffGather GatherMode = EDiffGather::First; FDiffTree Diffs; int32 LastSibling = INDEX_NONE;`
- L32 _public enumerator_ `enum EDiffGather { First, All }; struct FDiffContext : FBindContext { EDiffGather GatherMode = EDiffGather::First; FDiffTree Diffs; int32 LastSibling = INDEX_NONE;`

#### struct `PlainProps::FDiffContext`  
`struct FDiffContext : FBindContext`  
_L35-43_
- inherits: `FBindContext`
- desc: Tracks diff path for diff tools unlike the const FBindContext& overloads for delta saving
- L37 _public member_ `EDiffGather GatherMode = EDiffGather::First;`
- L38 _public member_ `FDiffTree Diffs;`
- L39 _public member_ `int32 LastSibling = INDEX_NONE;`
- L41 _public prototype_ `int32 AddDiff(FDiffNode&& Node);`
- L42 _public prototype_ `void Reset();`

#### struct `PlainProps::FReadDiffNode`  
`struct FReadDiffNode`  
_L75-81_
- L77 _public member_ `FMemberType Type;`
- L78 _public member_ `FOptionalStructSchemaId Struct;`
- L79 _public member_ `FOptionalMemberId Name;`
- L80 _public member_ `uint64 RangeIdx = ~uint64(0);`

#### struct `PlainProps::FReadDiffPath`  
`struct FReadDiffPath : public TArray<FReadDiffNode, TInlineAllocator<16>>`  
_L83-83_
- inherits: `TArray<FReadDiffNode,TInlineAllocator<16>>`

#### struct `PlainProps::FDiffPath`  
`struct FDiffPath : public TArray<FDiffNode>`  
_L93-96_
- inherits: `TArray<FDiffNode>`
- desc: Struct for converting diff results to a less efficient but easier to process structure. Nodes in the path are stored in forward order. Sibling links are invalidated.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlainProps`
- L45 _function_ `inline bool StopOnFirstDiff(const FDiffContext& Ctx)` (scope `PlainProps`)
- L50 _function_ `inline bool StopOnFirstDiff(const FBindContext& Ctx)` (scope `PlainProps`)
- L60 _prototype_ `[[nodiscard]] bool DiffStructs(const void* A, const void* B, FBindId Id, const FBindContext& Ctx);` (scope `PlainProps`)
- L61 _prototype_ `[[nodiscard]] bool DiffStructs(const void* A, const void* B, FBindId Id, FDiffContext& Ctx);` (scope `PlainProps`)
- L63 _prototype_ `[[nodiscard]] bool DiffLeaves(float A, float B);` (scope `PlainProps`)
- L64 _prototype_ `[[nodiscard]] bool DiffLeaves(double A, double B);` (scope `PlainProps`)
- L65 _function_ `template<Arithmetic T> bool DiffLeaves(T A, T B)` (scope `PlainProps`)
- L67 _prototype_ `[[nodiscard]] bool DiffRanges(const void* A, const void* B, const IItemRangeBinding& Binding, FUnpackedLeafType ItemType);` (scope `PlainProps`)
- L68 _prototype_ `[[nodiscard]] bool DiffRanges(const void* A, const void* B, const IItemRangeBinding& Binding, FBindId ItemType, const FBindContext& Ctx);` (scope `PlainProps`)
- L69 _prototype_ `[[nodiscard]] bool DiffRanges(const void* A, const void* B, const IItemRangeBinding& Binding, FBindId ItemType, FDiffContext& Ctx);` (scope `PlainProps`)
- L70 _prototype_ `[[nodiscard]] bool DiffRanges(const void* A, const void* B, const IItemRangeBinding& Binding, FRangeMemberBinding ItemType, const FBindContext& Ctx);` (scope `PlainProps`)
- L71 _prototype_ `[[nodiscard]] bool DiffRanges(const void* A, const void* B, const IItemRangeBinding& Binding, FRangeMemberBinding ItemType, FDiffContext& Ctx);` (scope `PlainProps`)
- L85 _prototype_ `bool DiffStruct(FStructView A, FStructView B, FReadDiffPath& Out);` (scope `PlainProps`)
- L86 _prototype_ `bool DiffSchemas(FSchemaBatchId A, FSchemaBatchId B);` (scope `PlainProps`)
- L98 _prototype_ `bool operator==(const FDiffPath& A, const FDiffPath& B);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsIndex.h` (Public)


#### class `PlainProps::FNestedScopeIndexer`  
`class FNestedScopeIndexer`  
_L12-24_
- L15 _public prototype_ `FNestedScopeId Index(FNestedScope Scope);`
- L16 _public function_ `FNestedScopeId Index(FScopeId Outer, FFlatScopeId Inner)`
- L17 _public prototype_ `FNestedScope Resolve(FNestedScopeId Id) const;`
- L18 _public function_ `int32 Num() const`
- L20 _public function_ `auto begin() const`
- L21 _public function_ `auto end() const`
- L23 _private member_ `TSet<FNestedScope> Scopes;`

#### class `PlainProps::FParametricTypeIndexer`  
`class FParametricTypeIndexer`  
_L28-46_
- L31 _public prototype_ `~FParametricTypeIndexer();`
- L33 _public prototype_ `FParametricTypeId Index(FParametricTypeView View);`
- L35 _public prototype_ `FParametricTypeView Resolve(FParametricTypeId Id) const;` — @return View invalidated by calling Index() (switch Parameters to TPagedArray to avoid)
- L36 _public function_ `FParametricType At(int32 Idx) const`
- L37 _public function_ `int32 Num() const`
- L38 _public function_ `TConstArrayView<FParametricType> GetAllTypes() const`
- L39 _public function_ `TConstArrayView<FType> GetAllParameters() const`
- L42 _private member_ `uint32 NumSlots = 0;`
- L43 _private member_ `uint32* Slots = nullptr;`
- L44 _private member_ `TArray<FParametricType> Types;`
- L45 _private member_ `TArray<FType> Parameters;`

#### class `PlainProps::FIdIndexerBase`  
`class FIdIndexerBase : public FIds`  
_L51-93_
- inherits: `FIds`
- desc: Allows indexes higher level ids from existing parts
- L54 _public prototype_ `FScopeId NestFlatScope(FScopeId Outer, FFlatScopeId Inner);`
- L55 _public prototype_ `FScopeId NestReversedScopes(TConstArrayView<FFlatScopeId> Inners);`
- L56 _public prototype_ `FParametricTypeId MakeParametricTypeId(FOptionalConcreteTypenameId Name, TConstArrayView<FType> Params);`
- L57 _public prototype_ `FType MakeParametricType(FType Type, TConstArrayView<FType> Params);`
- L58 _public prototype_ `FType MakeAnonymousParametricType(TConstArrayView<FType> Params);`
- L59 _public function_ `FType MakeLeafParameter(FUnpackedLeafType Leaf)`
- L60 _public function_ `FType MakeRangeParameter(ESizeType SizeType)`
- L62 _public prototype_ `FEnumId IndexEnum(FType Type);`
- L63 _public prototype_ `FStructId IndexStruct(FType Type);`
- L64 _public function_ `FDeclId IndexDeclId(FType Type)`
- L65 _public function_ `FBindId IndexBindId(FType Type)`
- L67 _public function_ `virtual uint32 NumNestedScopes() const override final`
- L68 _public function_ `virtual uint32 NumParametricTypes() const override final`
- L69 _public function_ `virtual uint32 NumEnums() const override final`
- L70 _public function_ `virtual uint32 NumStructs() const override final`
- L72 _public function_ `virtual FNestedScope Resolve(FNestedScopeId Id) const override final`
- L73 _public function_ `virtual FParametricTypeView Resolve(FParametricTypeId Id) const override final`
- L74 _public prototype_ `virtual FType Resolve(FEnumId Id) const override final;`
- L75 _public prototype_ `virtual FType Resolve(FStructId Id) const override final;`
- L77 _public function_ `const FNestedScopeIndexer& GetNestedScopes() const`
- L78 _public function_ `const FParametricTypeIndexer& GetParametricTypes() const`
- L80 _protected member_ `FNestedScopeIndexer NestedScopes;`
- L81 _protected member_ `FParametricTypeIndexer ParametricTypes;`
- L82 _protected member_ `TSet<FType> Enums;`
- L83 _protected member_ `TSet<FType> Structs;`
- L84 _protected member_ `FConcreteTypenameId Leaves[8][4];`
- L85 _protected member_ `FConcreteTypenameId Ranges[9];`
- L87 _protected prototype_ `void InitParameterNames();`
- L88 _protected function_ `FConcreteTypenameId InitParameterName(FAnsiStringView Name)`
- L92 _private prototype_ `virtual FNameId IndexLiteral(FAnsiStringView Name) = 0;`

#### class `PlainProps::FLiteralIndexerBase`  
`class FLiteralIndexerBase : public FIdIndexerBase`  
_L96-104_
- inherits: `FIdIndexerBase`
- desc: Also allows indexing new names from string literals
- L100 _public function_ `virtual FScopeId IndexScopeLiteral(FAnsiStringView Scope)` — Override to split scope into parts, default implementation assumes a single flat scope
- L101 _public function_ `FConcreteTypenameId IndexTypenameLiteral(FAnsiStringView Type)`
- L102 _public function_ `FMemberId IndexMemberLiteral(FAnsiStringView Member)`
- L103 _public function_ `FNameId IndexEnumeratorLiteral(FAnsiStringView Flag)`

#### class `PlainProps::TIdIndexer`  
`template<class NameT> class TIdIndexer : public FLiteralIndexerBase`  
_L111-138_
- inherits: `FLiteralIndexerBase`
- desc: Indexes FNameId from unique NameT instances or NameT-constructible types
- L116 _public function_ `TIdIndexer()`
- L118 _public function_ `template<int N> FNameId MakeName(const char (&Name)[N])`
- L120 _public function_ `template<int N> FNameId MakeName(const char (&Name)[N])`
- L121 _public function_ `template<int N> FNameId MakeName(const char (&Name)[N])`
- L122 _public function_ `template<typename T> FNameId MakeName(T&& Name)`
- L123 _public function_ `template<typename T> FMemberId NameMember(T&& Name)`
- L124 _public function_ `template<typename T> FConcreteTypenameId NameType(T&& Name)`
- L125 _public function_ `template<typename T> FFlatScopeId NameScope(T&& Name)`
- L126 _public function_ `template<typename T> FScopeId MakeScope(T&& Name)`
- L128 _public function_ `NameT ResolveName(FNameId Id) const`
- L129 _public function_ `virtual uint32 NumNames() const override final`
- L131 _public function_ `FConcreteTypenameId IndexRangeBindName(FAnsiStringView Str)`
- L134 _protected member_ `TSet<NameT> Names;`
- L136 _protected function_ `virtual void AppendString(FUtf8Builder& Out, FNameId Id) const override final`
- L137 _protected function_ `virtual FNameId IndexLiteral(FAnsiStringView Name) override final`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L107 _prototype_ `template<class NameType> void AppendString(FUtf8StringBuilderBase& Out, const NameType& Str);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsLoad.h` (Public)


#### struct `PlainProps::FLoadBatchDeleter`  
`struct FLoadBatchDeleter`  
_L17-20_
- L19 _public prototype_ `void operator()(FLoadBatch* Ptr) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlainProps`
- L21 _typedef_ `using FLoadBatchPtr = TUniquePtr<FLoadBatch, FLoadBatchDeleter>;` (scope `PlainProps`)
- L24 _prototype_ `[[nodiscard]] FLoadBatchPtr CreateLoadPlans(FSchemaBatchId BatchId,const FCustomBindings& Customs, const FSchemaBindings& Schemas, TConstArrayView<FStructId> RuntimeIds, ESchemaFormat Format);` (scope `PlainProps`)
- L25 _prototype_ `void UpdateLoadPlans(FLoadBatch& Batch, const FCustomBindings& Customs, const FSchemaBindings& Schemas, TConstArrayView<FStructId> RuntimeIds);` (scope `PlainProps`)
- L26 _prototype_ `bool HasLoadPlan(FStructSchemaId LoadId, const FLoadBatch& Batch);` (scope `PlainProps`)
- L27 _prototype_ `void LoadStruct(void* Dst, FByteReader Src, FStructSchemaId LoadId, const FLoadBatch& Batch);` (scope `PlainProps`)
- L28 _prototype_ `void ConstructAndLoadStruct(void* Dst, FByteReader Src, FStructSchemaId LoadId, const FLoadBatch& Batch);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsLoadMember.h` (Public)


#### struct `PlainProps::FMemcpyLoadPlan`  
`struct FMemcpyLoadPlan`  
_L16-20_
- L18 _public member_ `uint32 Size = 0;`
- L19 _public member_ `uint32 Offset = 0;`

#### struct `PlainProps::FSchemaLoadHandle`  
`struct FSchemaLoadHandle`  
_L22-31_
- L24 _public member_ `FStructSchemaId LoadId;`
- L25 _public member_ `const FLoadBatch& Batch;`
- L30 _public prototype_ `void GetInnerLoadIds(TArrayView<FOptionalSchemaId> Out) const;` — Experimental API to help bypass FMemberLoader overhead for dense struct ranges @pre Out.Num() must equal number of members

#### struct `PlainProps::FStructLoadView`  
`struct FStructLoadView`  
_L34-38_
- desc: Usable via FMemberLoader or [ConstructAnd]LoadStruct()
- L36 _public member_ `FSchemaLoadHandle Schema;`
- L37 _public member_ `FByteReader Values;`

#### struct `PlainProps::FRangeLoadSchema`  
`struct FRangeLoadSchema`  
_L63-69_
- L65 _public member_ `FMemberType ItemType;`
- L66 _public member_ `FOptionalSchemaId InnermostId;`
- L67 _public member_ `const FMemberType* NestedItemTypes;` — For nested ranges, can be out-of-bounds otherwise
- L68 _public member_ `const FLoadBatch& Batch;`

#### class `PlainProps::FRangeLoadView`  
`class FRangeLoadView`  
_L74-95_
- L77 _public function_ `FRangeLoadView(FRangeLoadSchema S, uint64 N, FMemoryView V) : Schema(S), NumItems(N), Values(V)`
- L79 _public function_ `uint64 Num() const`
- L80 _public function_ `bool IsEmpty() const`
- L81 _public function_ `bool IsLeafRange() const`
- L82 _public function_ `bool IsStructRange() const`
- L83 _public function_ `bool IsNestedRange() const`
- L85 _public prototype_ `FLeafRangeLoadView AsLeaves() const;` — @pre IsLeafRange()
- L86 _public prototype_ `FStructRangeLoadView AsStructs() const;` — @pre IsStructRange()
- L87 _public prototype_ `FNestedRangeLoadView AsRanges() const;` — @pre IsNestedRange()
- L92 _private member_ `FRangeLoadSchema Schema;`
- L93 _private member_ `uint64 NumItems;`
- L94 _private member_ `FMemoryView Values;`
- L160 _function_ `inline FLeafRangeLoadView FRangeLoadView::AsLeaves() const`

#### class `PlainProps::FLeafRangeLoadView`  
`class FLeafRangeLoadView`  
_L105-158_
- desc: Hides internal representation to enable future format changes, e.g. store zeroes or 1.0f in some compact fashion or var int encodings
- L107 _private member_ `const void* Data;`
- L108 _private member_ `uint64 NumItems;`
- L109 _private member_ `FUnpackedLeafType Leaf;`
- L112 _public function_ `FLeafRangeLoadView(const void* InData, uint64 InNum, FUnpackedLeafType InLeaf) : Data(InData) , NumItems(InNum) , Leaf(InLeaf)`
- L118 _public function_ `uint64 Num() const`
- L121 _public function_ `template<typename T> auto As() const`
- L128 _public function_ `template<> auto As<bool>() const`
- L135 _public function_ `template<typename T> auto AsBitCast() const requires (std::is_unsigned_v<T>)`
- L150 _public function_ `template<ELeafType Type, ELeafWidth Width> auto AsBitCast() const`

#### class `PlainProps::FNestedRangeLoadIterator`  
`class FNestedRangeLoadIterator`  
_L165-181_
- L168 _private member_ `FRangeLoadSchema Schema;`
- L169 _private member_ `FByteReader ByteIt;`
- L170 _private member_ `FBitCacheReader BitIt;`
- L173 _public function_ `FNestedRangeLoadIterator(const FRangeLoadSchema& InSchema, FMemoryView Data) : Schema(InSchema) , ByteIt(Data)`
- L178 _public prototype_ `FRangeLoadView operator*() const;`
- L179 _public function_ `bool operator!=(const FNestedRangeLoadIterator& Rhs) const`
- L180 _public prototype_ `void operator++();`

#### class `PlainProps::FStructRangeLoadIterator`  
`class FStructRangeLoadIterator`  
_L183-198_
- L186 _private member_ `FSchemaLoadHandle Schema;`
- L187 _private member_ `FByteReader ByteIt;`
- L190 _public function_ `FStructRangeLoadIterator(const FSchemaLoadHandle& InSchema, FMemoryView Data) : Schema(InSchema) , ByteIt(Data)`
- L195 _public function_ `FStructLoadView operator*() const`
- L196 _public function_ `bool operator!=(const FStructRangeLoadIterator& Rhs) const`
- L197 _public function_ `void operator++()`

#### class `PlainProps::FMemberLoader`  
`class FMemberLoader`  
_L202-222_
- L205 _public prototype_ `explicit FMemberLoader(FStructLoadView Struct);`
- L207 _public function_ `bool HasMore() const`
- L208 _public function_ `bool HasSuper() const`
- L210 _public function_ `FOptionalMemberId PeekName() const`
- L211 _public function_ `FMemberId PeekNameUnchecked() const`
- L212 _public function_ `EMemberKind PeekKind() const`
- L213 _public function_ `FMemberType PeekType() const`
- L215 _public function_ `FLeafView GrabLeaf()`
- L216 _public prototype_ `FRangeLoadView GrabRange();` — @pre PeekKind() == EMemberKind::Range
- L217 _public prototype_ `FStructLoadView GrabStruct();` — @pre PeekKind() == EMemberKind::Struct
- L219 _private member_ `FMemberReader Reader;`
- L220 _private member_ `const FStructSchemaId* LoadIdIt;`
- L221 _private member_ `const FLoadBatch& Batch;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PlainProps`
- L40 _prototype_ `void LoadStruct(void* Dst, FStructLoadView Src);` (scope `PlainProps`)
- L41 _prototype_ `void ConstructAndLoadStruct(void* Dst, FStructLoadView Src);` (scope `PlainProps`)
- L44 _prototype_ `void LoadSoleStruct(void* Dst, FStructLoadView Src);` (scope `PlainProps`) — Load single struct member faster than LoadStruct(Dst, FMemberLoader(Src).GrabStruct())
- L48 _prototype_ `template<LeafType T> inline void LoadSole(void* Dst, FStructLoadView Src);` (scope `PlainProps`) — Load single leaf member faster than FMemberLoader(Src).GrabLeaf().As<T>()
- L51 _prototype_ `template<> inline void LoadSole<bool>(void* Dst, FStructLoadView Src);` (scope `PlainProps`)
- L54 _function_ `template<LeafType T> inline T LoadSole(FStructLoadView Src)` (scope `PlainProps`)
- L71 _typedef_ `using FStructRangeLoadView = TStructuralRangeView<FStructRangeLoadIterator>;` (scope `PlainProps`)
- L72 _typedef_ `using FNestedRangeLoadView = TStructuralRangeView<FNestedRangeLoadIterator>;` (scope `PlainProps`)
- L97 _prototype_ `void LoadRange(void* Dst, FRangeLoadView Src, TConstArrayView<FRangeBinding> InnerBindings);` (scope `PlainProps`)
- L99 _prototype_ `void LoadRange(void* Dst, FByteReader& SrcBytes, FBitCacheReader& SrcBits, ESizeType MaxSize, FRangeLoadSchema Schema, TConstArrayView<FRangeBinding> InnerBindings);` (scope `PlainProps`) — Experimental low-level API bypassing FMemberLoader, internal use only
- L161 _function_ `inline FLeafRangeLoadView FLeafRangeView::AsLoadView() const` (scope `PlainProps::FLeafRangeView`)
- L225 _function_ `inline void TryLoadSuper(void* Dst, FMemberLoader& Src)` (scope `PlainProps`) — Grab and load super if it exists, call before grabbing from Src
- L236 _function_ `template<LeafType T> void LoadSole(void* Dst, FStructLoadView Src)` (scope `PlainProps`)
- L244 _function_ `template<> inline void LoadSole<bool>(void* Dst, FStructLoadView Src)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsLooseTypes.h` (Public)


#### enum `PlainProps::EInnermostKind`  
`enum class EInnermostKind : uint8`  
_L17-17_
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`
- L17 _public enumerator_ `enum class EInnermostKind : uint8 { Struct, Enum, Bool, S8, S16, S32, S64, U8, U16, U32, U64, F32, F64, UTF8, UTF16, UTF32 }; struct FInnermostStructType { EInnermostKind _ : 5; uint8 IsDynamic : 1; uint8 IsSuper : 1; uint8 IsDecomposed : 1;`

#### struct `PlainProps::FInnermostStructType`  
`struct FInnermostStructType`  
_L19-25_
- L21 _public member_ `EInnermostKind _ : 5;`
- L22 _public member_ `uint8 IsDynamic : 1;`
- L23 _public member_ `uint8 IsSuper : 1;`
- L24 _public member_ `uint8 IsDecomposed : 1;`

#### struct `PlainProps::FInnermostEnumType`  
`struct FInnermostEnumType`  
_L27-33_
- L29 _public member_ `EInnermostKind _ : 5;`
- L30 _public member_ `uint8 FlagMode : 1;`
- L31 _public member_ `uint8 Unused : 1;`
- L32 _public member_ `uint8 IsDecomposed : 1;`

#### union `PlainProps::FInnermostType`  
`union FInnermostType`  
_L35-40_
- L37 _public member_ `EInnermostKind Kind : 5;`
- L38 _public member_ `FInnermostStructType Struct;`
- L39 _public member_ `FInnermostEnumType Enum;`

#### struct `PlainProps::FLooseType`  
`struct FLooseType`  
_L96-116_
- L98 _public member_ `uint8 OptionalParameter : 1 = 0;`
- L99 _public member_ `uint8 NumRanges : LooseRangeBits + 1 = 0;`
- L100 _public member_ `FInnermostType InnermostType = InnermostStaticStruct;`
- L101 _public member_ `uint16 InnermostVersion = 0;`
- L102 _public member_ `FOptionalInnerId InnermostId;`
- L104 _public function_ `bool IsRange() const`
- L105 _public function_ `bool IsStruct() const`
- L106 _public function_ `bool IsLeaf() const`
- L107 _public function_ `bool IsEnum() const`
- L108 _public function_ `bool InnermostIsStruct() const`
- L109 _public function_ `bool InnermostIsEnum() const`
- L111 _public function_ `bool Compare(FLooseType O) const`
- L112 _public function_ `bool CompareAll(FLooseType O) const`
- L113 _public function_ `FLooseType WithoutMetadata() const`
- L115 _private function_ `uint64 AsInt() const`

#### struct `PlainProps::FParameterId`  
`struct FParameterId`  
_L124-130_
- desc: Per struct-indexed member id - allows TArray<T> lookup instead of TMap<FMemberId, T>
- L126 _public member_ `uint16 Idx = 0xFFFF;`
- L128 _public function_ `bool operator==(FParameterId O) const`

#### struct `PlainProps::FEnumeratorId`  
`struct FEnumeratorId`  
_L133-139_
- desc: Per enum-indexed enumerator name
- L135 _public member_ `uint16 Idx = 0xFFFF;`
- L137 _public function_ `bool operator==(FEnumeratorId O) const`

#### struct `PlainProps::FEnumeratorIdSet`  
`struct FEnumeratorIdSet`  
_L142-145_
- desc: Set of FEnumeratorId, each matching an enum flag name
- L144 _public member_ `uint64 Bits = 0;` — <= 64 FEnumeratorId flag names are inlined

#### union `PlainProps::FEnumeratorData`  
`union FEnumeratorData`  
_L147-151_
- L149 _public member_ `FEnumeratorId Flat = {};` — Loose enumerator name (without integer value)
- L150 _public member_ `FEnumeratorIdSet Flags;` — Loose set of enumerator flag names without integer value

#### struct `PlainProps::FEnumeratorIndex`  
`struct FEnumeratorIndex`  
_L154-157_
- desc: Temporary format used to access individual named enumerators during Op execution
- L156 _public member_ `uint16 Index = 0xFFFF;`

#### struct `PlainProps::FEnumeratorIndexSet`  
`struct FEnumeratorIndexSet`  
_L160-163_
- desc: Temporary format used to access individual named enum flags during Op execution
- L162 _public member_ `uint64 Bits = 0;`

#### union `PlainProps::FEnumIndexData`  
`union FEnumIndexData`  
_L166-170_
- desc: Temporary format used to access individual enum members during Op execution
- L168 _public member_ `FEnumeratorIndex Flat = {};` — Enumerator index from NameEnumerators order
- L169 _public member_ `FEnumeratorIndexSet Flags;` — Bitset of flag indices from NameFlags order

#### union `PlainProps::FEnumLooseData`  
`union FEnumLooseData`  
_L172-176_
- L174 _public member_ `FEnumeratorData Enumerator = {};` — FEnumeratorId::Idx order from FEnumeratorIndexer
- L175 _public member_ `FEnumIndexData Decomposed;` — Index order from NameEnumerators/NameFlags

#### union `PlainProps::FEnumData`  
`union FEnumData`  
_L178-182_
- L180 _public member_ `uint64 Source = 0;` — Integer source value matching the innermost enum schema
- L181 _public member_ `FEnumLooseData Loose;`

#### union `PlainProps::FEnumRange`  
`union FEnumRange`  
_L186-190_
- L188 _public member_ `const void* Source = nullptr;` — Integers source values matching the innermost enum schema
- L189 _public member_ `FEnumLooseData* Loose;`

#### union `PlainProps::FStructRange`  
`union FStructRange`  
_L192-196_
- L194 _public member_ `const void* Source = nullptr;` — Skippable slice of the FIRST source FStructView, not the range of structs
- L195 _public member_ `FLooseValue* Loose;`

#### union `PlainProps::FArithmeticRange`  
`union FArithmeticRange`  
_L198-202_
- L200 _public member_ `const void* Source = nullptr;`
- L201 _public member_ `void* Loose;`

#### union `PlainProps::FRangeData`  
`union FRangeData`  
_L204-210_
- L206 _public member_ `FArithmeticRange Arithmetics = {};`
- L207 _public member_ `FEnumRange Enums;`
- L208 _public member_ `FStructRange Structs;`
- L209 _public member_ `FLooseNestedRange* Ranges;`

#### struct `PlainProps::FLooseNestedRange`  
`struct FLooseNestedRange`  
_L212-216_
- L214 _public member_ `uint64 Num = 0;`
- L215 _public member_ `FRangeData Data;`

#### union `PlainProps::FStructData`  
`union FStructData`  
_L220-224_
- L222 _public member_ `const uint8* Source = nullptr;` — Skippable slice from a source FStructView
- L223 _public member_ `FLooseMember* Loose;`

#### union `PlainProps::FLooseData`  
`union FLooseData`  
_L228-234_
- L230 _public member_ `uint64 Arithmetic = 0;`
- L231 _public member_ `FEnumData Enum;`
- L232 _public member_ `FRangeData Range;`
- L233 _public member_ `FStructData Struct;`

#### enum `PlainProps::EMismatch`  
`enum class EMismatch : uint8`  
_L238-238_
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`
- L238 _public enumerator_ `enum class EMismatch : uint8 { No, Inners, Inputs, Type, Duplicate, Surplus, Missing }; struct FLooseMetadata { uint8 IsSet = 0; uint8 IsSourceRange : 1 = 0; uint8 IsFullyUpgraded : 1 = 0; EMismatch Mismatch : 6 = EMismatch::No;`

#### struct `PlainProps::FLooseMetadata`  
`struct FLooseMetadata`  
_L240-249_
- L242 _public member_ `uint8 IsSet = 0;`
- L243 _public member_ `uint8 IsSourceRange : 1 = 0;`
- L244 _public member_ `uint8 IsFullyUpgraded : 1 = 0;`
- L245 _public member_ `EMismatch Mismatch : 6 = EMismatch::No;` — Only need 4 bits currently but want all bits initialized
- L246 _public member_ `FParameterId Name;`
- L247 _public member_ `FOptionalSchemaId InnermostSchema;` — Set if innermost is source struct/enum
- L248 _public member_ `uint64 Num = 0;` — Range items, loose struct members or inner members / enumerators during op execution

#### struct `PlainProps::FLooseValue`  
`struct FLooseValue`  
_L251-260_
- L253 _public member_ `FLooseMetadata Meta;`
- L254 _public member_ `FLooseData Data;`
- L256 _public function_ `explicit operator bool() const`
- L257 _public function_ `bool IsMismatch() const`
- L258 _public prototype_ `void SetNamed(FLooseValue In);` — Assign but keep name
- L259 _public prototype_ `void SetFirstMismatch(EMismatch Mismatch);`
- L262 _function_ `inline void FLooseValue::SetNamed(FLooseValue In)`
- L268 _function_ `inline void FLooseValue::SetFirstMismatch(EMismatch Mismatch)`

#### class `PlainProps::FLooseMember`  
`class FLooseMember`  
_L279-300_
- desc: Typed and named optional value
- L282 _public function_ `FLooseMember(FLooseType T, FLooseValue V) : Type(T), Value(V)`
- L284 _public function_ `explicit operator bool() const`
- L285 _public function_ `bool IsMismatch() const`
- L286 _public function_ `bool IsOptional() const`
- L287 _public function_ `FLooseType GetType() const`
- L288 _public function_ `FLooseValue GetValue() const`
- L289 _public function_ `FParameterId GetName() const`
- L290 _public function_ `void Rename(FParameterId Name)`
- L291 _public function_ `void SetTypechecked(FLooseValue V)`
- L292 _public function_ `FLooseValue& EditTypechecked()`
- L293 _public prototype_ `void RecordDynamicType(FLooseType T);`
- L294 _public function_ `void MarkEnumRecomposed()`
- L295 _public function_ `void MarkStructRecomposed()`
- L298 _protected member_ `FLooseType Type;`
- L299 _protected member_ `FLooseValue Value;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L42 _function_ `inline const bool operator==(FInnermostType A, FInnermostType B)` (scope `PlainProps`)
- L44 _variable_ `inline static constexpr FInnermostType InnermostFlatEnum = { .Enum = { ._ = EInnermostKind::Enum, .FlagMode = 0 } };` (scope `PlainProps`)
- L45 _variable_ `inline static constexpr FInnermostType InnermostFlagEnum = { .Enum = { ._ = EInnermostKind::Enum, .FlagMode = 1 } };` (scope `PlainProps`)
- L46 _variable_ `inline static constexpr FInnermostType InnermostStaticStruct = { .Struct = { ._ = EInnermostKind::Struct, .IsDynamic = 0 } };` (scope `PlainProps`)
- L47 _variable_ `inline static constexpr FInnermostType InnermostDynamicStruct = { .Struct = { ._ = EInnermostKind::Struct, .IsDynamic = 1 } };` (scope `PlainProps`)
- L50 _function_ `template<typename T> constexpr FInnermostType IllegalInnermost()` (scope `PlainProps`)
- L57 _variable_ `template<Arithmetic T> inline constexpr FInnermostType ReflectInnermost = IllegalInnermost<T>();` (scope `PlainProps`)
- L59 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<bool> = { .Kind = EInnermostKind::Bool };` (scope `PlainProps`)
- L63 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<int8> = { .Kind = EInnermostKind::S8 };` (scope `PlainProps`)
- L64 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<int16> = { .Kind = EInnermostKind::S16 };` (scope `PlainProps`)
- L65 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<int32> = { .Kind = EInnermostKind::S32 };` (scope `PlainProps`)
- L66 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<int64> = { .Kind = EInnermostKind::S64 };` (scope `PlainProps`)
- L67 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<uint8> = { .Kind = EInnermostKind::U8 };` (scope `PlainProps`)
- L68 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<uint16> = { .Kind = EInnermostKind::U16 };` (scope `PlainProps`)
- L69 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<uint32> = { .Kind = EInnermostKind::U32 };` (scope `PlainProps`)
- L70 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<uint64> = { .Kind = EInnermostKind::U64 };` (scope `PlainProps`)
- L71 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<float> = { .Kind = EInnermostKind::F32 };` (scope `PlainProps`)
- L72 _variable_ `template<> inline constexpr FInnermostType ReflectInnermost<double> = { .Kind = EInnermostKind::F64 };` (scope `PlainProps`)
- L82 _function_ `template<Arithmetic T> uint64 ValueCast(T Value)` (scope `PlainProps`)
- L86 _function_ `template<Arithmetic T> T ArithmeticCast(uint64 Value)` (scope `PlainProps`)
- L93 _variable_ `static constexpr uint32 LooseRangeBits = 6;` (scope `PlainProps`)
- L94 _variable_ `static constexpr uint8 MaxRangeNesting = (uint8(1) << LooseRangeBits) - 1;` (scope `PlainProps`) — Todo: Enforce on build side too
- L119 _variable_ `template<Arithmetic T> inline constexpr FLooseType ReflectLoose = { 0, 0, ReflectInnermost<T>, 0, NoId };` (scope `PlainProps`)
- L129 _function_ `friend uint32 GetTypeHash(FParameterId Id)` (scope `PlainProps`)
- L138 _function_ `friend uint32 GetTypeHash(FEnumeratorId Id)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsModule.h` (Public)


#### class `FPlainPropsModule`  
`class FPlainPropsModule final : public IModuleInterface`  
_L7-7_
- inherits: `IModuleInterface`

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsParse.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PlainProps`
- L11 _function_ `template<typename T> TOptional<T> Parse(FUtf8StringView String)` (scope `PlainProps`)
- L16 _prototype_ `template<> TOptional<ESizeType> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L19 _prototype_ `template<> TOptional<FUnpackedLeafType> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L21 _prototype_ `template<> TOptional<bool> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L25 _prototype_ `template<> TOptional<int8> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L26 _prototype_ `template<> TOptional<int16> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L27 _prototype_ `template<> TOptional<int32> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L28 _prototype_ `template<> TOptional<int64> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L29 _prototype_ `template<> TOptional<uint8> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L30 _prototype_ `template<> TOptional<uint16> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L31 _prototype_ `template<> TOptional<uint32> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L32 _prototype_ `template<> TOptional<uint64> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L33 _prototype_ `template<> TOptional<float> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L34 _prototype_ `template<> TOptional<double> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L35 _prototype_ `template<> TOptional<char> Parse(FUtf8StringView String);` (scope `PlainProps`)
- L37 _function_ `template<typename T> TOptional<T> ParseHex(FUtf8StringView String)` (scope `PlainProps`)
- L41 _prototype_ `template<> TOptional<uint8> ParseHex(FUtf8StringView String);` (scope `PlainProps`)
- L48 _prototype_ `void ParseYamlBatch(TArray64<uint8>& OutBinary, FUtf8StringView Yaml);` (scope `PlainProps`)
- L49 _prototype_ `void ParseJsonBatch(TArray64<uint8>& OutBinary, FUtf8StringView Json);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsPrint.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PlainProps`
- L18 _prototype_ `FAnsiStringView ToString(ELeafWidth Width);` (scope `PlainProps`)
- L19 _prototype_ `FAnsiStringView ToString(EMemberKind Kind);` (scope `PlainProps`)
- L20 _prototype_ `FAnsiStringView ToString(ESizeType Width);` (scope `PlainProps`)
- L21 _prototype_ `FAnsiStringView ToString(ESchemaFormat Format);` (scope `PlainProps`)
- L22 _prototype_ `FAnsiStringView ToString(FMemberType Member);` (scope `PlainProps`)
- L23 _prototype_ `FAnsiStringView ToString(FStructType Struct);` (scope `PlainProps`)
- L24 _prototype_ `FAnsiStringView ToString(FUnpackedLeafType Leaf);` (scope `PlainProps`)
- L25 _prototype_ `FAnsiStringView ToString(FRangeType Range);` (scope `PlainProps`)
- L29 _function_ `template<typename T> inline void Print(FUtf8Builder& Out, T Value)` (scope `PlainProps`)
- L34 _prototype_ `template<> void Print(FUtf8Builder& Out, ESizeType Value);` (scope `PlainProps`)
- L37 _prototype_ `template<> void Print(FUtf8Builder& Out, bool Value);` (scope `PlainProps`)
- L41 _prototype_ `template<> void Print(FUtf8Builder& Out, int8 Value);` (scope `PlainProps`)
- L42 _prototype_ `template<> void Print(FUtf8Builder& Out, int16 Value);` (scope `PlainProps`)
- L43 _prototype_ `template<> void Print(FUtf8Builder& Out, int32 Value);` (scope `PlainProps`)
- L44 _prototype_ `template<> void Print(FUtf8Builder& Out, int64 Value);` (scope `PlainProps`)
- L45 _prototype_ `template<> void Print(FUtf8Builder& Out, uint8 Value);` (scope `PlainProps`)
- L46 _prototype_ `template<> void Print(FUtf8Builder& Out, uint16 Value);` (scope `PlainProps`)
- L47 _prototype_ `template<> void Print(FUtf8Builder& Out, uint32 Value);` (scope `PlainProps`)
- L48 _prototype_ `template<> void Print(FUtf8Builder& Out, uint64 Value);` (scope `PlainProps`)
- L49 _prototype_ `template<> void Print(FUtf8Builder& Out, float Value);` (scope `PlainProps`)
- L50 _prototype_ `template<> void Print(FUtf8Builder& Out, double Value);` (scope `PlainProps`)
- L52 _function_ `template<typename T> inline void PrintHex(FUtf8Builder& Out, T Value)` (scope `PlainProps`)
- L56 _prototype_ `template<> void PrintHex(FUtf8Builder& Out, uint8 Value);` (scope `PlainProps`)
- L63 _prototype_ `void PrintMemberSchema(FUtf8Builder& Out, const FIds& Ids, FMemberSchema Member);` (scope `PlainProps`)
- L64 _prototype_ `void PrintYamlBatch(FUtf8Builder& Out, const FBatchIds& Ids, TConstArrayView<FStructView> Objects);` (scope `PlainProps`)
- L65 _prototype_ `void PrintJsonBatch(FUtf8Builder& Out, const FBatchIds& Ids, TConstArrayView<FStructView> Objects);` (scope `PlainProps`)
- L66 _prototype_ `void PrintDiff(FUtf8Builder& Out, const FIds& Ids, const FDiffPath& Diff);` (scope `PlainProps`)
- L67 _prototype_ `void PrintDiff(FUtf8Builder& Out, const FBatchIds& Ids, const FReadDiffPath& Diff);` (scope `PlainProps`)
- L68 _prototype_ `void PrintDiffs(FUtf8Builder& Out, const FIds& Ids, TConstArrayView<FDiffPath> Diffs);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsRead.h` (Public)


#### class `PlainProps::FSchemaBatchId`  
`class FSchemaBatchId`  
_L23-27_
- desc: Represents a batch currently being read from
- L26 _private member_ `uint16 Idx = 0;`

#### class `PlainProps::FByteReader`  
`class FByteReader`  
_L42-144_
- L44 _private member_ `const uint8* It = nullptr;`
- L46 _private member_ `const uint8* End = nullptr;`
- L49 _public prototype_ `FByteReader() = default;`
- L50 _public function_ `explicit FByteReader(FMemoryView View) : FByteReader(static_cast<const uint8*>(View.GetData()), View.GetSize())`
- L51 _public function_ `FByteReader(const uint8* Data, uint64 NumBytes) : FByteReader(Data, Data + NumBytes)`
- L52 _public function_ `FByteReader(const uint8* InBegin, const uint8* InEnd) : It(InBegin) #if DO_CHECK , End(InEnd) #endif`
- L59 _public function_ `[[nodiscard]] inline const uint8* GrabBytes(uint64 NumBytes)`
- L69 _public function_ `[[nodiscard]] inline FMemoryView GrabSlice(uint64 NumBytes)`
- L74 _public function_ `[[nodiscard]] inline FMemoryView GrabSkippableSlice()`
- L79 _public function_ `[[nodiscard]] inline uint8 GrabByte()`
- L85 _public function_ `template<typename T> [[nodiscard]] inline T Grab()`
- L90 _public function_ `[[nodiscard]] FORCEINLINE uint64 GrabVarIntU()`
- L104 _public function_ `[[nodiscard]] const uint8* Peek() const`
- L106 _public function_ `[[nodiscard]] FMemoryView PeekSkippableSlice() const`
- L109 _public function_ `template<typename T> void SkipAlignmentPadding()`
- L117 _public function_ `void CheckEmpty() const`
- L123 _public function_ `void CheckNonEmpty() const`
- L129 _public function_ `void CheckSize(int64 ExpectedSize) const`
- L136 _public function_ `uint64 CheckableSize() const`

#### class `PlainProps::FBitCacheReader`  
`class FBitCacheReader`  
_L147-183_
- desc: Helper that consumes 8 bits from the byte value stream
- L149 _private member_ `uint8 Bits = 0;`
- L150 _private member_ `uint8 BitIt = 0;`
- L152 _public function_ `[[nodiscard]] FORCEINLINE bool GrabNext(FByteReader& Bytes)`
- L165 _public function_ `FORCENOINLINE void Skip(uint32 Num, FByteReader& Bytes)`

#### struct `PlainProps::FStructSchemaHandle`  
`struct FStructSchemaHandle`  
_L187-193_
- L189 _public member_ `FStructSchemaId Id;`
- L190 _public member_ `FSchemaBatchId Batch;`
- L192 _public function_ `const FStructSchema& Resolve() const`

#### struct `PlainProps::FStructView`  
`struct FStructView`  
_L195-199_
- L197 _public member_ `FStructSchemaHandle Schema;`
- L198 _public member_ `FByteReader Values;`

#### union `PlainProps::FMemberValue`  
`union FMemberValue`  
_L203-207_
- L205 _public member_ `const uint8* Ptr;` — From byte stream
- L206 _public member_ `bool bValue;` — From bit cache

#### struct `PlainProps::FLeafView`  
`struct FLeafView`  
_L209-255_
- L211 _public member_ `FUnpackedLeafType Leaf;`
- L212 _public member_ `FSchemaBatchId Batch;`
- L213 _public member_ `FOptionalEnumSchemaId Enum;`
- L214 _public member_ `FMemberValue Value;`
- L216 _public function_ `FORCEINLINE bool AsBool() const`
- L217 _public function_ `FORCEINLINE int8 AsS8() const`
- L218 _public function_ `FORCEINLINE uint8 AsU8() const`
- L219 _public function_ `FORCEINLINE int16 AsS16() const`
- L220 _public function_ `FORCEINLINE uint16 AsU16() const`
- L221 _public function_ `FORCEINLINE int32 AsS32() const`
- L222 _public function_ `FORCEINLINE uint32 AsU32() const`
- L223 _public function_ `FORCEINLINE int64 AsS64() const`
- L224 _public function_ `FORCEINLINE uint64 AsU64() const`
- L225 _public function_ `FORCEINLINE double AsDouble() const`
- L226 _public function_ `FORCEINLINE float AsFloat() const`
- L227 _public function_ `FORCEINLINE uint8 AsHex8() const`
- L228 _public function_ `FORCEINLINE uint16 AsHex16() const`
- L229 _public function_ `FORCEINLINE uint32 AsHex32() const`
- L230 _public function_ `FORCEINLINE uint64 AsHex64() const`
- L231 _public function_ `FORCEINLINE char8_t AsChar8() const`
- L232 _public function_ `FORCEINLINE char16_t AsChar16() const`
- L233 _public function_ `FORCEINLINE char32_t AsChar32() const`
- L236 _public function_ `template<Arithmetic T> FORCEINLINE T AsUnderlyingValue() const`
- L249 _public function_ `template<> FORCEINLINE bool As() const`

#### struct `PlainProps::FRangeSchema`  
`struct FRangeSchema`  
_L307-313_
- L309 _public member_ `FMemberType ItemType;`
- L310 _public member_ `FSchemaBatchId Batch;` — Needed to resolve inner schema
- L311 _public member_ `FOptionalSchemaId InnermostSchema;`
- L312 _public member_ `const FMemberType* NestedItemTypes;` — For nested ranges, can be out-of-bounds otherwise

#### class `PlainProps::FRangeView`  
`class FRangeView`  
_L315-338_
- L318 _public function_ `uint64 Num() const`
- L319 _public function_ `bool IsEmpty() const`
- L320 _public function_ `FMemberType GetItemType() const`
- L321 _public function_ `bool IsLeafRange() const`
- L322 _public function_ `bool IsStructRange() const`
- L323 _public function_ `bool IsNestedRange() const`
- L325 _public prototype_ `FLeafRangeView AsLeaves() const;` — @pre IsLeafRange()
- L326 _public prototype_ `FStructRangeView AsStructs() const;` — @pre IsStructRange()
- L327 _public prototype_ `FNestedRangeView AsRanges() const;` — @pre IsNestedRange()
- L335 _private member_ `FRangeSchema Schema;`
- L336 _private member_ `uint64 NumItems;`
- L337 _private member_ `FMemoryView Values;`

#### class `PlainProps::FBoolRangeIterator`  
`class FBoolRangeIterator`  
_L342-381_
- L345 _public function_ `FBoolRangeIterator(const uint8* Data, uint64 Idx) : Byte(Data + Idx / 8) , Mask(1u << (Idx % 8))`
- L350 _public function_ `bool operator*() const`
- L355 _public function_ `FBoolRangeIterator& operator++()`
- L366 _public function_ `FBoolRangeIterator operator++(int)`
- L373 _public function_ `bool operator!=(FBoolRangeIterator Rhs)`
- L379 _private member_ `const uint8* Byte;`
- L380 _private member_ `uint32 Mask;`

#### class `PlainProps::FBoolRangeView`  
`class FBoolRangeView`  
_L383-402_
- L386 _public function_ `FBoolRangeView(const void* Bits, uint64 Num) : Data(static_cast<const uint8*>(Bits)) , NumBits(Num)`
- L391 _public function_ `inline uint64 Num() const`
- L392 _public function_ `inline bool operator[](uint64 Idx) const`
- L393 _public prototype_ `inline void Copy(void* Dst, uint64 NumBytes) const;`
- L394 _public function_ `inline FBoolRangeIterator begin() const`
- L395 _public function_ `inline FBoolRangeIterator end() const`
- L398 _private member_ `const uint8* Data;`
- L399 _private member_ `uint64 NumBits;`
- L449 _function_ `inline void FBoolRangeView::Copy(void* Dst, uint64 NumBytes) const`

#### class `PlainProps::TRangeView`  
`template<typename T> class TRangeView`  
_L407-426_
- L410 _public function_ `TRangeView(const T* InData, uint64 InNum) : Data(InData) , NumItems(InNum)`
- L415 _public function_ `inline uint64 Num() const`
- L416 _public function_ `inline T operator[](uint64 Idx) const`
- L417 _public prototype_ `inline void Copy(void* Dst, uint64 NumBytes) const;`
- L418 _public function_ `inline const T* begin() const`
- L419 _public function_ `inline const T* end() const`
- L421 _private member_ `const T* Data;`
- L422 _private member_ `uint64 NumItems;`
- L460 _function_ `template<typename T> inline void TRangeView<T>::Copy(void* Dst, uint64 NumBytes) const`

#### class `PlainProps::FLeafRangeView`  
`class FLeafRangeView`  
_L471-542_
- L474 _public function_ `FLeafRangeView(FUnpackedLeafType Leaf, FSchemaBatchId InBatch, FOptionalEnumSchemaId InEnum, uint64 Num, const uint8* Data) : Type(Leaf.Type) , Width(Leaf.Width) , Batch(InBatch) , Enum(InEnum) , NumItems(Num) , Values(Data)`
- L483 _public function_ `uint64 Num() const`
- L491 _public function_ `template<typename T, FUnpackedLeafType ExpectedLeaf = ReflectLeaf<T>> auto As() const`
- L497 _public function_ `template<> auto As<bool>() const`
- L499 _public function_ `FBoolRangeView AsBools() const`
- L506 _public function_ `template<Arithmetic T> auto AsUnderlyingValues() const`
- L511 _public function_ `TRangeView< int8> AsS8s() const`
- L512 _public function_ `TRangeView<uint8> AsU8s() const`
- L513 _public function_ `TRangeView< int16> AsS16s() const`
- L514 _public function_ `TRangeView<uint16> AsU16s() const`
- L515 _public function_ `TRangeView< int32> AsS32s() const`
- L516 _public function_ `TRangeView<uint32> AsU32s() const`
- L517 _public function_ `TRangeView< int64> AsS64s() const`
- L518 _public function_ `TRangeView<uint64> AsU64s() const`
- L519 _public function_ `TRangeView<float> AsFloats() const`
- L520 _public function_ `TRangeView<double> AsDoubles() const`
- L521 _public function_ `TRangeView<uint8> AsHex8s() const`
- L522 _public function_ `TRangeView<uint16> AsHex16s() const`
- L523 _public function_ `TRangeView<uint32> AsHex32s() const`
- L524 _public function_ `TRangeView<uint64> AsHex64s() const`
- L525 _public function_ `TRangeView<char8_t> AsUtf8() const`
- L526 _public function_ `TRangeView<char16_t> AsUtf16() const`
- L527 _public function_ `TRangeView<char32_t> AsUtf32() const`
- L529 _public prototype_ `FLeafRangeLoadView AsLoadView() const;`
- L532 _private member_ `ELeafType Type;`
- L533 _private member_ `ELeafWidth Width;`
- L534 _private member_ `FSchemaBatchId Batch;`
- L535 _private member_ `FOptionalEnumSchemaId Enum;`
- L536 _private member_ `uint64 NumItems;`
- L537 _private member_ `const uint8* Values;`

#### class `PlainProps::FNestedRangeIterator`  
`class FNestedRangeIterator`  
_L546-562_
- L549 _private member_ `FRangeSchema Schema;`
- L550 _private member_ `FByteReader ByteIt;`
- L551 _private member_ `FBitCacheReader BitIt;`
- L554 _public function_ `FNestedRangeIterator(const FRangeSchema& InSchema, FMemoryView Data) : Schema(InSchema) , ByteIt(Data)`
- L559 _public prototype_ `FRangeView operator*() const;`
- L560 _public function_ `bool operator!=(const FNestedRangeIterator& Rhs) const`
- L561 _public prototype_ `void operator++();`

#### class `PlainProps::FStructRangeIterator`  
`class FStructRangeIterator`  
_L564-579_
- L567 _private member_ `FStructSchemaHandle Schema;`
- L568 _private member_ `FByteReader ByteIt;`
- L571 _public function_ `FStructRangeIterator(const FStructSchemaHandle& InSchema, FMemoryView Data) : Schema(InSchema) , ByteIt(Data)`
- L576 _public function_ `FStructView operator*() const`
- L577 _public function_ `bool operator!=(const FStructRangeIterator& Rhs) const`
- L578 _public function_ `void operator++()`

#### class `PlainProps::TStructuralRangeView`  
`template<typename IteratorType> class TStructuralRangeView`  
_L582-598_
- L585 _public typedef_ `using SchemaType = decltype(IteratorType::Schema);`
- L586 _public function_ `TStructuralRangeView(uint64 N, FMemoryView D, SchemaType S) : NumItems(N), Data(D), Schema(S)`
- L588 _public function_ `uint64 Num() const`
- L589 _public function_ `const SchemaType& GetSchema() const`
- L590 _public function_ `IteratorType begin() const`
- L591 _public function_ `IteratorType end() const`
- L595 _private member_ `uint64 NumItems;`
- L596 _private member_ `FMemoryView Data;`
- L597 _private member_ `SchemaType Schema;`

#### class `PlainProps::FMemberReader`  
`class FMemberReader`  
_L626-698_
- desc: Iterates over struct members
- L629 _public function_ `explicit FMemberReader(FStructView Struct) : FMemberReader(Struct.Schema.Resolve(), Struct.Values, Struct.Schema.Batch)`
- L630 _public prototype_ `FMemberReader(const FStructSchema& Schema, FByteReader Values, FSchemaBatchId InBatch);`
- L632 _public function_ `bool HasMore() const`
- L633 _public function_ `bool HasSuper() const`
- L635 _public prototype_ `FOptionalMemberId PeekName() const;` — @pre HasMore()
- L636 _public prototype_ `FMemberId PeekNameUnchecked() const;` — @pre HasMore() && !HasSuper()
- L637 _public prototype_ `EMemberKind PeekKind() const;` — @pre HasMore()
- L638 _public prototype_ `FMemberType PeekType() const;` — @pre HasMore()
- L640 _public prototype_ `FLeafView GrabLeaf();` — @pre PeekKind() == EMemberKind::Leaf
- L641 _public prototype_ `FRangeView GrabRange();` — @pre PeekKind() == EMemberKind::Range
- L642 _public prototype_ `FStructView GrabStruct();` — @pre PeekKind() == EMemberKind::Struct
- L645 _public prototype_ `void SkipMember();` — @pre HasMore()
- L650 _public prototype_ `template<Arithmetic T> void GrabLeaves(T* Out, uint32 N);` — Experimental @pre Has N more contiguous members of the expected leaf type
- L655 _public prototype_ `template<Enumeration T> void GrabEnums(T* Out, uint32 N);` — Experimental @pre Has N more contiguous members of the expected leaf type
- L658 _protected member_ `const FMemberType* Footer;`
- L659 _protected member_ `const FSchemaBatchId Batch;` — Needed to resolve schemas
- L660 _protected member_ `const bool IsSparse : 1;`
- L661 _protected member_ `const bool UsesSuper : 1;`
- L662 _protected member_ `const uint32 NumMembers;`
- L663 _protected member_ `const uint32 NumRangeTypes;` — Number of ranges and nested ranges
- L665 _protected member_ `uint32 MemberIdx = 0;`
- L666 _protected member_ `uint32 RangeTypeIdx = 0;` — Types of [nested] ranges
- L667 _protected member_ `uint32 InnerSchemaIdx = 0;` — Types of static structs and enums
- L668 _protected member_ `FBitCacheReader Bits;`
- L669 _protected member_ `FByteReader ValueIt;`
- L672 _protected member_ `const uint32 NumInnerSchemas;` — Number of static structs and enums
- L675 _protected prototype_ `const FMemberType* GetMemberTypes() const;`
- L676 _protected prototype_ `const FMemberType* GetRangeTypes() const;`
- L677 _protected prototype_ `const FSchemaId* GetInnerSchemas() const;`
- L678 _protected prototype_ `const FMemberId* GetMemberNames() const;`
- L680 _protected prototype_ `void AdvanceToNextMember();`
- L681 _protected prototype_ `void AdvanceToLaterMember(uint32 Num);`
- L682 _protected prototype_ `void SkipMissingSparseMembers();`
- L683 _protected prototype_ `void SkipSchema(FMemberType InnermostType);`
- L685 _protected typedef_ `using FMemberTypeRange = TConstArrayView<FMemberType>;`
- L687 _protected prototype_ `FMemberTypeRange GrabRangeTypes();`
- L688 _protected prototype_ `FSchemaId GrabInnerSchema();`
- L689 _protected prototype_ `FStructSchemaId GrabStructSchema(FStructType Type);`
- L690 _protected prototype_ `FOptionalSchemaId GrabRangeSchema(FMemberType InnermostType);`
- L691 _protected function_ `inline FEnumSchemaId GrabEnumSchema()`
- L692 _protected function_ `inline bool GrabBit()`
- L693 _protected function_ `inline uint64 GrabSkipLength()`
- L695 _protected prototype_ `void GrabBools(void* Out, uint32 Num);`
- L696 _protected prototype_ `void GrabEnums(void* Out, uint32 Num, SIZE_T NumBytes);`
- L697 _protected prototype_ `void GrabLeaves(void* Out, uint32 Num, SIZE_T NumBytes);`
- L701 _function_ `template<Arithmetic T> void FMemberReader::GrabLeaves(T* Out, uint32 N)`
- L717 _function_ `template<Enumeration T> void FMemberReader::GrabEnums(T* Out, uint32 N)`

#### class `PlainProps::FFlatMemberReader`  
`class FFlatMemberReader`  
_L729-759_
- desc: Hides the inheritance chain and iterates over super members first
- L732 _public prototype_ `FFlatMemberReader(FStructView Struct);`
- L734 _public function_ `bool HasMore() const`
- L736 _public function_ `FMemberId PeekName() const`
- L737 _public function_ `EMemberKind PeekKind() const`
- L738 _public function_ `FType PeekOwner() const`
- L740 _public function_ `FLeafView GrabLeaf()`
- L741 _public function_ `FRangeView GrabRange()`
- L742 _public function_ `FStructView GrabStruct()`
- L750 _private member_ `TArray<FReader, TInlineAllocator<8>> Lineage;`
- L751 _private member_ `FReader* It = nullptr;`
- L754 _private function_ `template<class ViewType> ViewType Grabbed(ViewType Out)`

#### struct `PlainProps::FFlatMemberReader::FReader`  
`struct FReader : public FMemberReader`  
_L745-749_
- inherits: `FMemberReader`
- L747 _public prototype_ `FReader(FStructView Struct);`
- L748 _public member_ `FType Owner;`

#### class `PlainProps::FBatchIds`  
`class FBatchIds : public FIdsBase`  
_L764-785_
- inherits: `FIdsBase`
- desc: Serialized id resolver
- L770 _public prototype_ `FBatchIds(FSchemaBatchId Batch);`
- L772 _public prototype_ `virtual uint32 NumEnums() const;`
- L773 _public prototype_ `virtual uint32 NumStructs() const;`
- L774 _public prototype_ `virtual FType Resolve(FEnumSchemaId Id) const;`
- L775 _public prototype_ `virtual FType Resolve(FStructSchemaId Id) const;`
- L777 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FEnumSchemaId Enum) const;`
- L778 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FStructSchemaId Struct) const;`
- L780 _public function_ `const FSchemaBatch& GetSchemas() const`
- L781 _public function_ `FSchemaBatchId GetBatchId() const`
- L783 _protected member_ `const FSchemaBatch& Schemas;`
- L784 _protected member_ `FSchemaBatchId BatchId;`

#### class `PlainProps::FMemoryBatchIds`  
`class FMemoryBatchIds final : public FBatchIds`  
_L788-806_
- inherits: `FBatchIds`
- desc: Serialized id resolver for ESchemaFormat::InMemoryNames
- L794 _public function_ `FMemoryBatchIds(FSchemaBatchId Batch, const FIdsBase& InNames) : FBatchIds(Batch), Names(InNames)`
- L796 _public function_ `virtual uint32 NumNames() const override`
- L797 _public function_ `virtual uint32 NumNestedScopes() const override`
- L798 _public function_ `virtual uint32 NumParametricTypes() const override`
- L799 _public function_ `virtual FNestedScope Resolve(FNestedScopeId Id) const override`
- L800 _public function_ `virtual FParametricTypeView Resolve(FParametricTypeId Id) const override`
- L802 _public function_ `virtual void AppendString(FUtf8Builder& Out, FNameId Name) const override`
- L805 _private member_ `const FIdsBase& Names;`

#### class `PlainProps::FStableBatchIds`  
`class FStableBatchIds : public FBatchIds`  
_L809-819_
- inherits: `FBatchIds`
- desc: Serialized id resolver for ESchemaFormat::StableNames
- L815 _public prototype_ `virtual uint32 NumNestedScopes() const override final;`
- L816 _public prototype_ `virtual uint32 NumParametricTypes() const override final;`
- L817 _public prototype_ `virtual FNestedScope Resolve(FNestedScopeId Id) const override final;`
- L818 _public prototype_ `virtual FParametricTypeView Resolve(FParametricTypeId Id) const override final;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PlainProps`
- L30 _prototype_ `const FSchemaBatch* ValidateSchemas(FMemoryView Schemas);` (scope `PlainProps`) — @param Schemas must outlive read batch
- L31 _prototype_ `FSchemaBatchId MountReadSchemas(const FSchemaBatch* Schemas);` (scope `PlainProps`)
- L32 _prototype_ `const FSchemaBatch* UnmountReadSchemas(FSchemaBatchId Batch);` (scope `PlainProps`)
- L34 _prototype_ `uint32 NumStructSchemas(FSchemaBatchId Batch);` (scope `PlainProps`)
- L35 _prototype_ `const FStructSchema& ResolveStructSchema(FSchemaBatchId Batch, FStructSchemaId Id);` (scope `PlainProps`)
- L36 _prototype_ `const FEnumSchema& ResolveEnumSchema(FSchemaBatchId Batch, FEnumSchemaId Id);` (scope `PlainProps`)
- L37 _prototype_ `FNestedScope ResolveUntranslatedNestedScope(FSchemaBatchId Batch, FNestedScopeId Id);` (scope `PlainProps`)
- L38 _prototype_ `FParametricTypeView ResolveUntranslatedParametricType(FSchemaBatchId Batch, FParametricTypeId Id);` (scope `PlainProps`)
- L304 _typedef_ `using FStructRangeView = TStructuralRangeView<FStructRangeIterator>;` (scope `PlainProps`)
- L305 _typedef_ `using FNestedRangeView = TStructuralRangeView<FNestedRangeIterator>;` (scope `PlainProps`)
- L401 _function_ `friend inline uint64 GetNum(const FBoolRangeView& Range)` (scope `PlainProps`)
- L424 _function_ `friend inline uint64 GetNum(const TRangeView& Range)` (scope `PlainProps`)
- L425 _function_ `friend inline const T* GetData(const TRangeView& Range)` (scope `PlainProps`)
- L430 _function_ `template<class RangeTypeA, class RangeTypeB> bool EqualItems(RangeTypeA&& A, RangeTypeB&& B)` (scope `PlainProps`) — Works with FBoolRangeView, which lack GetData(), TRangeView, TArrayView, std::intializer_list and T[]

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsSave.h` (Public)


#### struct `PlainProps::FSaveContext`  
`struct FSaveContext : FBindContext`  
_L12-16_
- inherits: `FBindContext`
- L14 _public member_ `FScratchAllocator& Scratch;`
- L15 _public member_ `IDefaultStructs* Defaults = nullptr;`

#### struct `PlainProps::FDefaultLink`  
`struct FDefaultLink`  
_L27-31_
- desc: FBaseline helper
- L29 _public function_ `FDefaultLink(const void* Default) : Ptr(reinterpret_cast<uint64>(Default))`
- L30 _public member_ `uint64 Ptr;`

#### class `PlainProps::FBaseline`  
`class FBaseline`  
_L39-52_
- desc: A default pointer or a short chain of super default pointers, where last default is shared by all remaining supers Optimized for normal case where default is the most derived type being saved. Handles default being some super class, via nullptr(s) first and default last. Can also help multiple inheritance impacting super offsets.
- L42 _public function_ `FBaseline(const void* Default) : Ptr(reinterpret_cast<uint64>(Default))`
- L43 _public prototype_ `FBaseline(FDefaultLink* Chain UE_LIFETIMEBOUND, int32 Num);`
- L45 _public prototype_ `const void* Get() const;` — Get default instance for current type
- L46 _public prototype_ `FBaseline Super() const;` — Get baseline for super type
- L49 _private member_ `static constexpr uint64 TagBit = uint64(1) << FPlatformMemory::KernelAddressBit;`
- L50 _private member_ `uint64 Ptr = 0;`
- L51 _private function_ `FBaseline(uint64 In) : Ptr(In)`
- L69 _function_ `inline const void* FBaseline::Get() const`
- L76 _function_ `inline FBaseline FBaseline::Super() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlainProps`
- L19 _function_ `template<typename Runtime> FSaveContext MakeSaveContext(FScratchAllocator& Scratch)` (scope `PlainProps`)
- L56 _prototype_ `[[nodiscard]] FBuiltStruct* SaveStruct(const void* Struct, FBindId BindId, const FSaveContext& Context);` (scope `PlainProps`)
- L57 _prototype_ `[[nodiscard]] FBuiltStruct* SaveStructDelta(const void* Struct, FBaseline Base, FBindId BindId, const FSaveContext& Context);` (scope `PlainProps`)
- L58 _prototype_ `[[nodiscard]] FBuiltStruct* SaveStructDeltaIfDiff(const void* Struct, FBaseline Base, FBindId BindId, const FSaveContext& Context);` (scope `PlainProps`)
- L59 _prototype_ `[[nodiscard]] FBuiltRange* SaveRange(const void* Range, FRangeMemberBinding Member, const FSaveContext& Ctx);` (scope `PlainProps`)
- L60 _prototype_ `[[nodiscard]] FBuiltRange* SaveLeafRange(const void* Range, const ILeafRangeBinding& Binding, FUnpackedLeafType Leaf, const FSaveContext& Ctx);` (scope `PlainProps`)
- L61 _prototype_ `[[nodiscard]] FBuiltRange* SaveStructRange(TConstArrayView<FBuiltStruct*> Structs, const FSaveContext& Ctx);` (scope `PlainProps`)
- L63 _prototype_ `void SaveSuper(FMemberBuilder& Out, const void* Super, FBindId SuperId, const FSaveContext& Ctx);` (scope `PlainProps`)
- L65 _prototype_ `void SaveSuperDelta(FMemberBuilder& Out, const void* Super, FBaseline SuperBase, FBindId SuperId, const FSaveContext& Ctx);` (scope `PlainProps`) — Save Super if any members differ from SuperBase

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsSaveMember.h` (Public)


#### struct `PlainProps::TStructSerializer`  
`template<typename T> struct TStructSerializer : FBothStructId`  
_L32-88_
- inherits: `FBothStructId`
- desc: TMemberSerializer helper
- L34 _public member_ `static constexpr EMemberKind Kind = EMemberKind::Struct;`
- L40 _public prototype_ `Init.RegisterInnerStruct(Both, Names);`
- L43 _public function_ `FMemberSpec SpecMember() const`
- L45 _public function_ `FTypedValue SaveMember(const T& Value, const FSaveContext& Ctx) const`
- L51 _public function_ `void LoadMember(T& Dst, FMemberLoader& Src) const`
- L56 _public function_ `void ConstructAndLoadMember(void* Dst, FMemberLoader& Src) const`
- L70 _public function_ `template<class ContextType> bool DiffMember(const T& A, const T& B, FMemberId Name, ContextType& Ctx) const`
- L77 _public typedef_ `using BuiltItemType = FBuiltStruct*;`
- L79 _public function_ `FBuiltStruct* SaveItem(const T& Value, const FSaveContext& Ctx) const`
- L84 _public function_ `FMemberSchema MakeMemberRangeSchema(ESizeType MaxSize) const`

#### union `PlainProps::FMemberBindTypeInitializer`  
`union FMemberBindTypeInitializer`  
_L110-115_
- desc: TRangeSerializer constructor helper, FMemberBindType isn't default-constructible
- L112 _public function_ `FMemberBindTypeInitializer() : Unused()`
- L113 _public member_ `uint8_t Unused;`
- L114 _public member_ `FMemberBindType Value;`

#### struct `PlainProps::TRangeSerializer`  
`template<typename T, typename RangeBinding> struct TRangeSerializer`  
_L119-251_
- desc: TMemberSerializer helper
- L121 _public member_ `static constexpr EMemberKind Kind = EMemberKind::Range;`
- L122 _public member_ `static constexpr bool bLeafRange = std::is_base_of_v<ILeafRangeBinding, RangeBinding>;`
- L123 _public member_ `static constexpr uint16 NumRanges = CountRangeBindings<RangeBinding>();`
- L124 _public member_ `static constexpr uint16 NumTypes = NumRanges + 1;`
- L126 _public member_ `FRangeBinding const* const Bindings = nullptr;`
- L127 _public member_ `FOptionalInnerId InnermostId;`
- L128 _public member_ `FOptionalInnerId InnermostSpecId;`
- L129 _public member_ `FMemberBindTypeInitializer BindTypes[NumTypes];`
- L130 _public member_ `FMemberType Types[NumTypes];`
- L133 _public function_ `template<class Ids> TRangeSerializer(TCustomInit<Ids>& Init, TConstArrayView<FMemberId> Names) : Bindings(GetRangeBindings<RangeBinding, Ids, NumRanges>().GetData())`
- L158 _public function_ `FMemberSpec SpecMember() const`
- L163 _public function_ `void LoadMember(T& Dst, FMemberLoader& Src) const`
- L168 _public function_ `void ConstructAndLoadMember(void* Dst, FMemberLoader& Src) const`
- L174 _public function_ `FTypedValue SaveMember(const T& Value, const FSaveContext& Ctx) const`
- L180 _public function_ `template<typename ContextType> bool DiffItems(const void* A, const void* B, const IItemRangeBinding& Binding, ContextType& Ctx) const`
- L196 _public function_ `inline FDiffMetadata MakeDiffMetadata() const`
- L213 _public function_ `template<typename ContextType> bool DiffMember(const T& A, const T& B, FMemberId Name, ContextType& Ctx) const`
- L220 _public function_ `FMemberSchema MakeMemberSchema() const`
- L225 _public function_ `FRangeMemberBinding MakeInnerRangeBinding() const`
- L232 _public typedef_ `using BuiltItemType = FBuiltRange*;`
- L234 _public function_ `FMemberSchema MakeMemberRangeSchema(ESizeType MaxSize) const`
- L239 _public function_ `FBuiltRange* SaveItem(const T& Item, const FSaveContext& Ctx) const`

#### struct `PlainProps::TLeafSerializer`  
`template<typename T> struct TLeafSerializer`  
_L257-279_
- desc: TMemberSerializer helper
- L259 _public function_ `static void LoadMember(T& Dst, FMemberLoader& Src)`
- L264 _public function_ `static void ConstructAndLoadMember(void* Dst, FMemberLoader& Src)`
- L269 _public function_ `static FTypedValue SaveLeaf(FMemberType Type, FOptionalInnerId Id, T Value)`
- L276 _public typedef_ `using BuiltItemType = T;`
- L278 _public function_ `static T SaveItem(T Value, const FSaveContext&)`

#### struct `PlainProps::TArithmeticSerializer`  
`template<Arithmetic T> struct TArithmeticSerializer : TLeafSerializer<T>`  
_L283-314_
- inherits: `TLeafSerializer<T>`
- desc: TMemberSerializer helper
- L285 _public member_ `static constexpr FMemberType MemberType = ReflectArithmetic<T>.Pack();`
- L286 _public member_ `static constexpr FMemberBindType MemberBindType{ReflectArithmetic<T>};`
- L289 _public function_ `template<class Ids> TArithmeticSerializer(TCustomInit<Ids>&, TConstArrayView<FMemberId>)`
- L292 _public function_ `static FMemberSpec SpecMember()`
- L297 _public function_ `static FTypedValue SaveMember(T Value, const FSaveContext&)`
- L303 _public function_ `template<class ContextType> inline static bool DiffMember(const T& A, const T& B, FMemberId Name, ContextType& Ctx)`
- L310 _public function_ `FMemberSchema MakeMemberRangeSchema(ESizeType MaxSize) const`

#### struct `PlainProps::TEnumSerializer`  
`template<Enumeration T> struct TEnumSerializer : TLeafSerializer<T>`  
_L318-352_
- inherits: `TLeafSerializer<T>`
- desc: TMemberSerializer helper
- L320 _public member_ `static constexpr FMemberType MemberType = ReflectEnum<T>.Pack();`
- L321 _public member_ `static constexpr FMemberBindType MemberBindType = ReflectEnum<T>;`
- L323 _public member_ `const FEnumId Id;`
- L326 _public function_ `template<class Ids> TEnumSerializer(TCustomInit<Ids>&, TConstArrayView<FMemberId>) : Id(GetEnumId<Ids, T>())`
- L330 _public function_ `FMemberSpec SpecMember() const`
- L335 _public function_ `FTypedValue SaveMember(T Value, const FSaveContext& Ctx) const`
- L341 _public function_ `template<class ContextType> inline bool DiffMember(const T& A, const T& B, FMemberId Name, ContextType& Ctx) const`
- L348 _public function_ `FMemberSchema MakeMemberRangeSchema(ESizeType MaxSize) const`

#### struct `PlainProps::TSelectSerializer`  
`template<typename T> struct TSelectSerializer`  
_L357-363_
- L359 _public typedef_ `using CustomBinding = CustomBind<T>;`
- L360 _public typedef_ `using RangeBinding = RangeBind<T>;`
- L361 _public member_ `static constexpr bool bRange = std::is_void_v<CustomBinding> && !std::is_void_v<RangeBinding>;`
- L362 _public typedef_ `using Type = std::conditional_t<bRange, TRangeSerializer<T, RangeBinding>, TStructSerializer<T>>;`
- L368 _public typedef_ `using Type = TArithmeticSerializer<T>;`
- L374 _public typedef_ `using Type = TEnumSerializer<T>;`

#### struct `PlainProps::TSelectSerializer`  
`template<Arithmetic T> struct TSelectSerializer<T>`  
_L366-369_
- L359 _public typedef_ `using CustomBinding = CustomBind<T>;`
- L360 _public typedef_ `using RangeBinding = RangeBind<T>;`
- L361 _public member_ `static constexpr bool bRange = std::is_void_v<CustomBinding> && !std::is_void_v<RangeBinding>;`
- L362 _public typedef_ `using Type = std::conditional_t<bRange, TRangeSerializer<T, RangeBinding>, TStructSerializer<T>>;`
- L368 _public typedef_ `using Type = TArithmeticSerializer<T>;`
- L374 _public typedef_ `using Type = TEnumSerializer<T>;`

#### struct `PlainProps::TSelectSerializer`  
`template<Enumeration T> struct TSelectSerializer<T>`  
_L372-375_
- L359 _public typedef_ `using CustomBinding = CustomBind<T>;`
- L360 _public typedef_ `using RangeBinding = RangeBind<T>;`
- L361 _public member_ `static constexpr bool bRange = std::is_void_v<CustomBinding> && !std::is_void_v<RangeBinding>;`
- L362 _public typedef_ `using Type = std::conditional_t<bRange, TRangeSerializer<T, RangeBinding>, TStructSerializer<T>>;`
- L368 _public typedef_ `using Type = TArithmeticSerializer<T>;`
- L374 _public typedef_ `using Type = TEnumSerializer<T>;`

#### class `PlainProps::FRangeSaverBase`  
`class FRangeSaverBase`  
_L384-413_
- desc: Helps hide FBuiltRange internals
- L387 _public prototype_ `FRangeSaverBase(FScratchAllocator& Scratch, uint64 Num, SIZE_T ItemSize);`
- L391 _protected function_ `template<typename BuiltItemType> inline void AddBuiltItem(BuiltItemType Item)`
- L400 _protected function_ `[[nodiscard]] FTypedRange Finalize(FMemberSchema RangeSchema)`
- L408 _protected member_ `FBuiltRange* Range;`
- L409 _protected member_ `uint8* It;`
- L411 _protected member_ `const uint8* End;`

#### class `PlainProps::TRangeSaver`  
`template<typename T> class TRangeSaver : public FRangeSaverBase`  
_L417-443_
- inherits: `FRangeSaverBase`
- desc: Saves a range of T without a range binding
- L420 _public typedef_ `using FMemberSerializer = TMemberSerializer<T>;`
- L421 _public typedef_ `using BuiltItemType = typename FMemberSerializer::BuiltItemType;`
- L422 _public member_ `static constexpr SIZE_T ItemSize = sizeof(BuiltItemType);`
- L424 _public function_ `TRangeSaver(const FSaveContext& InCtx, uint64 Num, const FMemberSerializer& InSchema) : FRangeSaverBase(InCtx.Scratch, Num, sizeof(BuiltItemType)) , Schema(InSchema) , Ctx(InCtx)`
- L430 _public function_ `void AddItem(const T& Item)`
- L435 _public function_ `[[nodiscard]] FTypedRange Finalize(ESizeType MaxSize)`
- L441 _private member_ `const FMemberSerializer& Schema;`
- L442 _private member_ `const FSaveContext& Ctx;`

#### class `PlainProps::TLeafRangeSaver`  
`template<Arithmetic LeafType> class TLeafRangeSaver : public FRangeSaverBase`  
_L446-452_
- inherits: `FRangeSaverBase`
- L449 _public function_ `TLeafRangeSaver(FScratchAllocator& Scratch, uint64 Num) : FRangeSaverBase(Scratch, Num, sizeof(LeafType))`
- L450 _public function_ `inline void AddItem(LeafType Item)`

#### class `PlainProps::FNestedRangeSaver`  
`class FNestedRangeSaver : public FRangeSaverBase`  
_L454-460_
- inherits: `FRangeSaverBase`
- L457 _public function_ `FNestedRangeSaver(FScratchAllocator& Scratch, uint64 Num) : FRangeSaverBase(Scratch, Num, sizeof(FBuiltRange*))`
- L458 _public function_ `inline void AddItem(const FBuiltRange* Item)`

#### class `PlainProps::FStructRangeSaver`  
`class FStructRangeSaver : public FRangeSaverBase`  
_L462-468_
- inherits: `FRangeSaverBase`
- L465 _public function_ `FStructRangeSaver(FScratchAllocator& Scratch, uint64 Num) : FRangeSaverBase(Scratch, Num, sizeof(FBuiltStruct*))`
- L466 _public function_ `inline void AddItem(const FBuiltStruct* Item)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PlainProps`
- L15 _function_ `inline bool Track(bool bDiff, const FBindContext&, FMemberBindType, FMemberId, FDiffMetadata, const void*, const void*)` (scope `PlainProps`)
- L20 _function_ `inline bool Track(bool bDiff, FDiffContext& Ctx, FMemberBindType Type, FMemberId Name, FDiffMetadata Meta, const void* A, const void* B)` (scope `PlainProps`)
- L93 _function_ `template<typename T> inline constexpr FMemberType ReflectInnermostType()` (scope `PlainProps`)
- L99 _function_ `template<Arithmetic T> inline constexpr FMemberType ReflectInnermostType()` (scope `PlainProps`)
- L104 _function_ `template<Enumeration T> inline constexpr FMemberType ReflectInnermostType()` (scope `PlainProps`)
- L143 _typedef_ `using InnermostType = typename TInnermostType<RangeBinding, NumRanges>::Type;` (scope `PlainProps::TRangeSerializer::TRangeSerializer`)
- L379 _typedef_ `template<typename T> using TMemberSerializer = typename TSelectSerializer<T>::Type;` (scope `PlainProps`) — Helps templated custom bindings save generic members
- L472 _prototype_ `void SaveMember(FMemberBuilder& Out, const void* Struct, FMemberId Name, const FSaveContext& Ctx, FLeafMemberBinding Member);` (scope `PlainProps`)
- L473 _prototype_ `void SaveMember(FMemberBuilder& Out, const void* Struct, FMemberId Name, const FSaveContext& Ctx, FRangeMemberBinding Member);` (scope `PlainProps`)
- L474 _prototype_ `void SaveMember(FMemberBuilder& Out, const void* Struct, FMemberId Name, const FSaveContext& Ctx, FStructMemberBinding Member);` (scope `PlainProps`)
- L478 _prototype_ `[[nodiscard]] FMemberSchema CreateRangeSchema(FScratchAllocator& Scratch, FRangeMemberBinding Member);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsSpecify.h` (Public)


#### enum `PlainProps::ESpecBool`  
`enum ESpecBool`  
_L12-12_
- L12 _public enumerator_ `enum ESpecBool { SpecBool }; enum ESpecIntS { SpecS8, SpecS16, SpecS32, SpecS64 }; enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct };`

#### enum `PlainProps::ESpecIntS`  
`enum ESpecIntS`  
_L13-13_
- desc: Values match ELeafWidth
- L13 _public enumerator_ `enum ESpecIntS { SpecS8, SpecS16, SpecS32, SpecS64 }; enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView` — Values match ELeafWidth
- L13 _public enumerator_ `enum ESpecIntS { SpecS8, SpecS16, SpecS32, SpecS64 }; enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView` — Values match ELeafWidth
- L13 _public enumerator_ `enum ESpecIntS { SpecS8, SpecS16, SpecS32, SpecS64 }; enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView` — Values match ELeafWidth
- L13 _public enumerator_ `enum ESpecIntS { SpecS8, SpecS16, SpecS32, SpecS64 }; enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView` — Values match ELeafWidth

#### enum `PlainProps::ESpecIntU`  
`enum ESpecIntU`  
_L14-14_
- desc: Values match ELeafWidth
- L14 _public enumerator_ `enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView {` — Values match ELeafWidth
- L14 _public enumerator_ `enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView {` — Values match ELeafWidth
- L14 _public enumerator_ `enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView {` — Values match ELeafWidth
- L14 _public enumerator_ `enum ESpecIntU { SpecU8, SpecU16, SpecU32, SpecU64 }; enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView {` — Values match ELeafWidth

#### enum `PlainProps::ESpecHex`  
`enum ESpecHex`  
_L15-15_
- desc: Values match ELeafWidth
- L15 _public enumerator_ `enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType;` — Values match ELeafWidth
- L15 _public enumerator_ `enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType;` — Values match ELeafWidth
- L15 _public enumerator_ `enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType;` — Values match ELeafWidth
- L15 _public enumerator_ `enum ESpecHex { SpecHex8, SpecHex16, SpecHex32, SpecHex64 }; enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType;` — Values match ELeafWidth

#### enum `PlainProps::ESpecChar`  
`enum ESpecChar`  
_L16-16_
- desc: Values match ELeafWidth
- L16 _public enumerator_ `enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType; FOptionalInnerId InnermostId;` — Values match ELeafWidth
- L16 _public enumerator_ `enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType; FOptionalInnerId InnermostId;` — Values match ELeafWidth
- L16 _public enumerator_ `enum ESpecChar { SpecUtf8, SpecUtf16, SpecUtf32 }; enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType; FOptionalInnerId InnermostId;` — Values match ELeafWidth

#### enum `PlainProps::ESpecFloat`  
`enum ESpecFloat`  
_L17-17_
- desc: Values match ELeafWidth
- L17 _public enumerator_ `enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType; FOptionalInnerId InnermostId; TConstArrayView<ESizeType> Ranges;` — Values match ELeafWidth
- L17 _public enumerator_ `enum ESpecFloat { SpecF32 = 2, SpecF64 = 3 }; enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType; FOptionalInnerId InnermostId; TConstArrayView<ESizeType> Ranges;` — Values match ELeafWidth

#### enum `PlainProps::ESpecDynamicStruct`  
`enum ESpecDynamicStruct`  
_L18-18_
- L18 _public enumerator_ `enum ESpecDynamicStruct { SpecDynamicStruct }; struct FMemberSpecView { FMemberType InnermostType; FOptionalInnerId InnermostId; TConstArrayView<ESizeType> Ranges; };`

#### struct `PlainProps::FMemberSpecView`  
`struct FMemberSpecView`  
_L20-25_
- L22 _public member_ `FMemberType InnermostType;`
- L23 _public member_ `FOptionalInnerId InnermostId;`
- L24 _public member_ `TConstArrayView<ESizeType> Ranges;`

#### class `PlainProps::FMemberSpec`  
`class FMemberSpec`  
_L28-68_
- desc: Specifies the type of a member before declaring it
- L31 _public function_ `FMemberSpec() : bSpecified(false)`
- L34 _public function_ `FMemberSpec(FMemberType Type, FOptionalInnerId Id) : InnermostType(Type), InnermostId(Id)` — @pre !Type.IsRange()
- L36 _public function_ `FMemberSpec(FUnpackedLeafType Leaf, FOptionalEnumId Id) : FMemberSpec(FMemberType(Leaf.Pack()), FOptionalInnerId(Id))`
- L37 _public function_ `FMemberSpec(ELeafType Type, ELeafWidth Width, FOptionalEnumId Id) : FMemberSpec({Type, Width}, Id)`
- L38 _public function_ `FMemberSpec(ESpecBool) : FMemberSpec(ELeafType::Bool, ELeafWidth::B8, NoId)`
- L39 _public function_ `FMemberSpec(ESpecIntS In) : FMemberSpec(ELeafType::IntS, static_cast<ELeafWidth>(In), NoId)`
- L40 _public function_ `FMemberSpec(ESpecIntU In) : FMemberSpec(ELeafType::IntU, static_cast<ELeafWidth>(In), NoId)`
- L41 _public function_ `FMemberSpec(ESpecHex In) : FMemberSpec(ELeafType::Hex, static_cast<ELeafWidth>(In), NoId)`
- L42 _public function_ `FMemberSpec(ESpecChar In) : FMemberSpec(ELeafType::Unicode, static_cast<ELeafWidth>(In), NoId)`
- L43 _public function_ `FMemberSpec(ESpecFloat In) : FMemberSpec(ELeafType::Float, static_cast<ELeafWidth>(In), NoId)`
- L46 _public function_ `template<typename T> requires (std::is_convertible_v<T, FDeclId>) FMemberSpec(T Id) : FMemberSpec(FStructType{EMemberKind::Struct, 0, 0}, FInnerId(FDeclId(Id)))`
- L47 _public function_ `FMemberSpec(ESpecDynamicStruct) : FMemberSpec(FStructType{EMemberKind::Struct, 1, 0}, NoId)`
- L49 _public prototype_ `FMemberSpec(ESizeType MaxSize, FMemberSpec Inner);`
- L50 _public prototype_ `FMemberSpec(TConstArrayView<FMemberType> Members, FOptionalInnerId InInnermostId);`
- L51 _public prototype_ `FMemberSpec(FMemberType Type, TConstArrayView<FMemberType> InnerRangeTypes, FOptionalInnerId InInnermostId);`
- L53 _public function_ `void RangeWrap(ESizeType MaxSize)`
- L54 _public function_ `void RangeWrap(FMemberType Range)`
- L56 _public prototype_ `operator FMemberSpecView() const UE_LIFETIMEBOUND;`
- L57 _public function_ `explicit operator bool() const`
- L60 _private typedef_ `using RangeSizeArray = TArray<ESizeType, TInlineAllocator<8>>;`
- L62 _private member_ `bool bSpecified = true;`
- L63 _private member_ `FMemberType InnermostType;`
- L64 _private member_ `FOptionalInnerId InnermostId;`
- L65 _private member_ `RangeSizeArray Ranges;`
- L67 _private function_ `FMemberSpec(FStructType Type, FOptionalInnerId Id) : InnermostType(Type), InnermostId(Id)`
- L70 _function_ `inline FMemberSpec::operator FMemberSpecView() const`

#### struct `PlainProps::FStructSpec`  
`struct FStructSpec`  
_L93-101_
- desc: Struct declaration input
- L95 _public member_ `FDeclId Id;`
- L96 _public member_ `FOptionalDeclId Super;`
- L97 _public member_ `uint16 Version = 0;`
- L98 _public member_ `EMemberPresence Occupancy;`
- L99 _public member_ `TConstArrayView<FMemberId> MemberNames;`
- L100 _public member_ `TConstArrayView<FMemberSpec> MemberTypes;`

#### struct `PlainProps::FSoleMemberSpec`  
`struct FSoleMemberSpec`  
_L106-122_
- desc: Helps specify single member structs
- L108 _public function_ `FSoleMemberSpec(FDeclId InId, FMemberId Name, FMemberSpec Spec, FOptionalDeclId InSuper = NoId, uint16 Ver = 0) : Id(InId), Super(InSuper), Version(Ver), MemberName(Name), MemberType(Spec)`
- L112 _public member_ `FDeclId Id;`
- L113 _public member_ `FOptionalDeclId Super;`
- L114 _public member_ `uint16 Version;`
- L115 _public member_ `FMemberId MemberName;`
- L116 _public member_ `FMemberSpec MemberType;`
- L118 _public function_ `operator FStructSpec() const UE_LIFETIMEBOUND`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L79 _function_ `template<Arithmetic T> inline FMemberSpec Specify()` (scope `PlainProps`)
- L85 _function_ `template<Enumeration T> inline FMemberSpec Specify(FEnumId Id)` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsStringUtil.h` (Public)


#### struct `PlainProps::Private::TConcat`  
`template <const std::string_view&... Strs> struct TConcat`  
_L22-36_
- L24 _public member_ `inline static constexpr std::size_t Len = (Strs.size() + ... + 0);`
- L26 _public member_ `static constexpr std::array<char, Len + 1> Chars = []() { std::array<char, Len + 1> Out; char* OutIt = Out.data(); (Append(OutIt, Strs), ...); *OutIt = '\0'; return Out; }();`
- L27 _public function_ ``
- L35 _public member_ `inline static constexpr std::string_view Value{Chars.data(), Len};`

#### struct `PlainProps::Private::THexString`  
`template<uint64 N> struct THexString`  
_L39-58_
- L41 _public function_ `inline static constexpr char At(uint32 Idx)`
- L47 _public member_ `static constexpr char Chars[16] = { At(15), At(14), At(13), At(12), At(11), At(10), At(9), At(8), At(7), At(6), At(5), At(4), At(3), At(2), At(1), At(0) };`
- L49 _public function_ `inline static constexpr uint32 CalcLen()`
- L56 _public member_ `inline static constexpr uint32 Len = CalcLen();`
- L57 _public member_ `inline static constexpr std::string_view Value{Chars + 16 - Len, Len};`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlainProps`
- L10 _namespace_ `namespace Private` (scope `PlainProps`)
- L13 _function_ `inline constexpr void Append(char*& ToIt, std::string_view From)` (scope `PlainProps::Private`)
- L60 _function_ `inline constexpr std::string_view TrimWhitespace(std::string_view Str)` (scope `PlainProps::Private`)
- L70 _function_ `inline constexpr std::size_t CountTokens(std::string_view Str, char Delimiter)` (scope `PlainProps::Private`) — Returns number of delimiter separated tokens, includes empty tokens. Returns zero for empty or whitespace only Str.
- L80 _function_ `template <std::size_t N> inline constexpr std::array<std::string_view, N> ParseTokensImpl(std::string_view Str, char Delimiter)` (scope `PlainProps::Private`) — Returns array of delimiter separated and whitespace stripped tokens, includes empty tokens. Returns empty array for empty or whitespace only Str.
- L98 _variable_ `template <const std::string_view& Str> inline constexpr auto ParseArgs = ParseTokensImpl<Private::CountTokens(Str, ',')>(Str, ',');` (scope `PlainProps::Private`) — Returns array of comma separated and whitespace stripped tokens, includes empty tokens. Returns empty array for empty or whitespace only Str. Can be used for a string view based on #__VA__ARGS.
- L102 _namespace_ `namespace PlainProps`
- L106 _variable_ `template <const std::string_view&... Strs> inline constexpr std::string_view Concat = Private::TConcat<Strs...>::Value;` (scope `PlainProps`)
- L109 _variable_ `template <uint64 N> inline constexpr std::string_view HexString = Private::THexString<N>::Value;` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsTypename.h` (Public)


#### enum `PlainProps::ETypename`  
`enum class ETypename`  
_L21-25_
- desc: A declared struct can be bound to multiple runtime implementations. ETypename indicates which typename is intended. This enum is also used to type-erase ranges, e.g. in UE FString, TArray<char8_t>, TArray<char, TInlineAllocator<64>> all map to a UTF8 range and the runtime can change data structures without impacting saved format. This can be used for both schema bindings and custom bindings. E.g. weak and strong reference class can be saved identically if the strong / weak semantics is considered a runtime detail. Typed references can be type-erased into an untyped reference. When there is only a single runtime memory representation the Bind name and Decl name is usually the same
- L23 _public enumerator_ `Decl` — Declared type name, saved to disk / schemas
- L24 _public enumerator_ `Bind` — Bound type name, in-memory id that uniquely identifies a binding. Often same as Decl.

#### struct `PlainProps::TTypename`  
`template<typename T> struct TTypename`  
_L35-39_
- desc: Trait that defines DeclName, BindName and template Parameters that's part of the typename Also defines RangeBindName, used when otherwise nameless ranges are captured in Parameters, e.g. UE TPair<int, FString> need a different bind name than TPair<int, TArray<char8_t>> At least one of DeclName, BindName or RangeBindName should exist and be a constexpr std::string_view Template parameters are captured as using Parameters = std::tuple<T>;
- L37 _public member_ `inline static constexpr std::string_view DeclName = CttiOf<T>::Name;`
- L38 _public member_ `inline static constexpr std::string_view Namespace = CttiOf<T>::Namespace;`
- L92 _public member_ `inline static constexpr FUnpackedLeafType Leaf = ReflectArithmetic<T>;`
- L93 _public member_ `inline static constexpr std::string_view DeclName = ArithmeticName<Leaf.Type, Leaf.Width>;`
- L94 _public member_ `inline static constexpr std::string_view Namespace;`

#### struct `PlainProps::FOmitTypename`  
`struct FOmitTypename`  
_L56-56_
- L56 _public member_ `struct FOmitTypename { inline static constexpr std::string_view Value{}; };`

#### struct `PlainProps::TTypename`  
`template<Arithmetic T> struct TTypename<T>`  
_L90-95_
- L37 _public member_ `inline static constexpr std::string_view DeclName = CttiOf<T>::Name;`
- L38 _public member_ `inline static constexpr std::string_view Namespace = CttiOf<T>::Namespace;`
- L92 _public member_ `inline static constexpr FUnpackedLeafType Leaf = ReflectArithmetic<T>;`
- L93 _public member_ `inline static constexpr std::string_view DeclName = ArithmeticName<Leaf.Type, Leaf.Width>;`
- L94 _public member_ `inline static constexpr std::string_view Namespace;`

#### struct `PlainProps::TCustomTypename`  
`template<class CustomBinding> struct TCustomTypename`  
_L103-106_
- L105 _public typedef_ `using Type = TTypename<typename CustomBinding::Type>;`
- L111 _public typedef_ `using Type = CustomBinding::FCustomTypename;`

#### struct `PlainProps::TCustomTypename`  
`template<WithCustomTypename CustomBinding> struct TCustomTypename<CustomBinding>`  
_L109-112_
- L105 _public typedef_ `using Type = TTypename<typename CustomBinding::Type>;`
- L111 _public typedef_ `using Type = CustomBinding::FCustomTypename;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PlainProps`
- L42 _member_ `template<class Typename> concept ParametricName = requires { typename Typename::Parameters; };` (scope `PlainProps::Typename`)
- L54 _variable_ `template<typename T> constexpr std::string_view ShortTypename = TShortTypename<T>::Value;` (scope `PlainProps`)
- L61 _function_ `template<ELeafType Type, ELeafWidth Width> constexpr std::string_view IllegalArithmetic()` (scope `PlainProps`)
- L68 _variable_ `template<ELeafType Type, ELeafWidth Width> constexpr std::string_view ArithmeticName = IllegalArithmetic<Type, Width>();` (scope `PlainProps`)
- L70 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Bool, ELeafWidth::B8> = "bo` (scope `PlainProps`)
- L74 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntS, ELeafWidth::B8> = "i8` (scope `PlainProps`)
- L75 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntS, ELeafWidth::B16> = "i1` (scope `PlainProps`)
- L76 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntS, ELeafWidth::B32> = "i3` (scope `PlainProps`)
- L77 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntS, ELeafWidth::B64> = "i6` (scope `PlainProps`)
- L78 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntU, ELeafWidth::B8> = "u8` (scope `PlainProps`)
- L79 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntU, ELeafWidth::B16> = "u1` (scope `PlainProps`)
- L80 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntU, ELeafWidth::B32> = "u3` (scope `PlainProps`)
- L81 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::IntU, ELeafWidth::B64> = "u6` (scope `PlainProps`)
- L82 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Float, ELeafWidth::B32> = "f3` (scope `PlainProps`)
- L83 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Float, ELeafWidth::B64> = "f6` (scope `PlainProps`)
- L84 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Hex, ELeafWidth::B8> = "he` (scope `PlainProps`)
- L85 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Hex, ELeafWidth::B16> = "he` (scope `PlainProps`)
- L86 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Hex, ELeafWidth::B32> = "he` (scope `PlainProps`)
- L87 _variable_ `template<> inline constexpr std::string_view ArithmeticName<ELeafType::Hex, ELeafWidth::B64> = "he` (scope `PlainProps`)
- L100 _member_ `template<class CustomBinding> concept WithCustomTypename = requires { typename CustomBinding::FCustomTypename; };` (scope `PlainProps::CustomBinding`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsTypes.h` (Public)


#### enum `PlainProps::EMemberKind`  
`enum class EMemberKind : uint8`  
_L15-15_
- L15 _public enumerator_ `enum class EMemberKind : uint8 { Leaf, Struct, Range }; enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width);`
- L15 _public enumerator_ `enum class EMemberKind : uint8 { Leaf, Struct, Range }; enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width);`
- L15 _public enumerator_ `enum class EMemberKind : uint8 { Leaf, Struct, Range }; enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width);`

#### enum `PlainProps::ELeafType`  
`enum class ELeafType : uint8`  
_L16-16_
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L16 _public enumerator_ `enum class ELeafType : uint8 { Bool, IntS, IntU, Float, Hex, Enum, Unicode }; enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`

#### enum `PlainProps::ELeafWidth`  
`enum class ELeafWidth : uint8`  
_L17-17_
- L17 _public enumerator_ `enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L17 _public enumerator_ `enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L17 _public enumerator_ `enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`
- L17 _public enumerator_ `enum class ELeafWidth : uint8 { B8, B16, B32, B64 }; enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); }`

#### enum `PlainProps::ESizeType`  
`enum class ESizeType : uint8`  
_L18-18_
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`
- L18 _public enumerator_ `enum class ESizeType : uint8 { Uni, S8, U8, S16, U16, S32, U32, S64, U64 }; inline constexpr SIZE_T SizeOf(ELeafWidth Width) { return SIZE_T(1) << static_cast<uint32>(Width); } inline ELeafWidth WidthOf(SIZE_T Size)`

#### struct `PlainProps::FLeafType`  
`struct FLeafType`  
_L58-64_
- L60 _public member_ `EMemberKind _ : 2;`
- L61 _public member_ `ELeafWidth Width : 2;`
- L62 _public member_ `ELeafType Type : 3;`
- L63 _public member_ `uint8 _Pad : 1;`

#### struct `PlainProps::FRangeType`  
`struct FRangeType`  
_L66-71_
- L68 _public member_ `EMemberKind _ : 2;`
- L69 _public member_ `ESizeType MaxSize : 4;`
- L70 _public member_ `uint8 _Pad : 2;`

#### struct `PlainProps::FStructType`  
`struct FStructType`  
_L73-80_
- L75 _public member_ `EMemberKind _ : 2;`
- L76 _public member_ `uint8 IsDynamic : 1;` — Which schema stored in value stream, different instances in same batch have different types
- L77 _public member_ `uint8 IsSuper : 1;` — Inherited members from some super struct, can only appear as first member
- L79 _public member_ `uint8 _Pad : 4;` — uint8			IsDense : 1;	// Potential optimization to avoid accessing schema

#### union `PlainProps::FMemberType`  
`union FMemberType`  
_L82-107_
- L84 _public prototype_ `FMemberType() = default;` — Uninitialized
- L85 _public function_ `constexpr explicit FMemberType(FLeafType InLeaf) : Leaf(InLeaf)`
- L86 _public function_ `constexpr explicit FMemberType(ELeafType Type, ELeafWidth Width) : Leaf({EMemberKind::Leaf, Width, Type})`
- L87 _public function_ `constexpr explicit FMemberType(FRangeType InRange) : Range(InRange)`
- L88 _public function_ `constexpr explicit FMemberType(ESizeType MaxSize) : Range({EMemberKind::Range, MaxSize})`
- L89 _public function_ `constexpr explicit FMemberType(FStructType InStruct) : Struct(InStruct)`
- L91 _public function_ `bool IsLeaf() const`
- L92 _public function_ `bool IsRange() const`
- L93 _public function_ `bool IsStruct() const`
- L94 _public function_ `EMemberKind GetKind() const`
- L96 _public function_ `FLeafType AsLeaf() const`
- L97 _public function_ `FRangeType AsRange() const`
- L98 _public function_ `FStructType AsStruct() const`
- L99 _public function_ `uint8 AsByte() const`
- L103 _private member_ `EMemberKind Kind : 2;`
- L104 _private member_ `FLeafType Leaf;`
- L105 _private member_ `FRangeType Range;`
- L106 _private member_ `FStructType Struct;`

#### struct `PlainProps::FNameId`  
`struct FNameId`  
_L111-117_
- L113 _public member_ `uint32 Idx = ~0u;`
- L115 _public function_ `bool operator==(FNameId O) const`

#### struct `PlainProps::FMemberId`  
`struct FMemberId`  
_L119-125_
- L121 _public member_ `FNameId Id;`
- L123 _public function_ `bool operator==(FMemberId O) const`

#### struct `PlainProps::FEnumId`  
`struct FEnumId`  
_L130-135_
- desc: Runtime id for an enum FType
- L132 _public member_ `uint32 Idx = ~0u;`

#### struct `PlainProps::FStructId`  
`struct FStructId`  
_L138-143_
- desc: Runtime id for a struct FType, i.e. a class or struct
- L140 _public member_ `uint32 Idx = ~0u;`

#### struct `PlainProps::FDeclId`  
`struct FDeclId : FStructId`  
_L148-148_
- inherits: `FStructId`
- desc: Abstract FStructId used in declarations and stable schemas Might type-erase runtime details such as container allocator

#### struct `PlainProps::FBindId`  
`struct FBindId : FStructId`  
_L154-154_
- inherits: `FStructId`
- desc: Concrete FStructId used in bindings and in-memory schemas Uniquely ids a runtime class/struct. Usually same as FDeclId, but might type-erase runtime details.

#### struct `PlainProps::FInnerId`  
`struct FInnerId`  
_L161-176_
- desc: Either a runtime FStructId or FEnumId of a member
- L163 _public member_ `uint32 Idx = ~0u;`
- L165 _public function_ `explicit FInnerId(FEnumId In) : Idx(In.Idx)`
- L166 _public function_ `explicit FInnerId(FStructId In) : Idx(In.Idx)`
- L168 _public function_ `FEnumId AsEnum() const`
- L169 _public function_ `FStructId AsStruct() const`
- L170 _public function_ `FDeclId AsStructDeclId() const`
- L171 _public function_ `FBindId AsStructBindId() const`
- L175 _public function_ `explicit FInnerId(uint32 InIdx) : Idx(InIdx)`

#### struct `PlainProps::FSchemaId`  
`struct FSchemaId`  
_L181-187_
- desc: Serialized schema id of a runtime FInnerId
- L183 _public member_ `uint32 Idx = ~0u;`
- L185 _public function_ `bool operator==(FSchemaId O) const`

#### struct `PlainProps::FStructSchemaId`  
`struct FStructSchemaId : FSchemaId`  
_L190-190_
- inherits: `FSchemaId`
- desc: Serialized struct id of a runtime FStructId

#### struct `PlainProps::FEnumSchemaId`  
`struct FEnumSchemaId : FSchemaId`  
_L194-194_
- inherits: `FSchemaId`
- desc: Serialized enum id of a runtime FEnumId

#### struct `PlainProps::FNoId`  
`struct FNoId`  
_L199-199_

#### struct `PlainProps::FNestedScopeId`  
`struct FNestedScopeId`  
_L204-204_
- L204 _public member_ `struct FNestedScopeId { uint32 Idx; };`

#### struct `PlainProps::FFlatScopeId`  
`struct FFlatScopeId`  
_L205-205_
- L205 _public member_ `struct FFlatScopeId { FNameId Name; };`

#### class `PlainProps::FScopeId`  
`class FScopeId`  
_L207-225_
- L209 _private member_ `static constexpr uint32 NestedBit = 0x80000000u;`
- L210 _private member_ `static constexpr uint32 Unscoped = ~0u;`
- L212 _private member_ `uint32 Handle;`
- L214 _public function_ `FScopeId(FNoId) : Handle(Unscoped)`
- L215 _public function_ `explicit FScopeId(FFlatScopeId Flat) : Handle(Flat.Name.Idx)`
- L216 _public function_ `explicit FScopeId(FNestedScopeId Nested) : Handle(Nested.Idx | NestedBit)`
- L218 _public function_ `explicit operator bool() const`
- L219 _public function_ `bool IsFlat() const`
- L220 _public function_ `bool IsNested() const`
- L221 _public function_ `FFlatScopeId AsFlat() const`
- L222 _public function_ `FNestedScopeId AsNested() const`
- L223 _public function_ `uint32 AsInt() const`
- L224 _public function_ `bool operator==(FScopeId O) const`

#### struct `PlainProps::FConcreteTypenameId`  
`struct FConcreteTypenameId`  
_L229-233_
- L231 _public member_ `FNameId Id;`
- L232 _public function_ `bool operator==(FConcreteTypenameId O) const`

#### struct `PlainProps::FBaseTypenameId`  
`struct FBaseTypenameId`  
_L235-250_
- L237 _public function_ `FBaseTypenameId(uint8 InNumParameters, uint32 InIdx) : NumParameters(InNumParameters) , Idx(InIdx)`
- L244 _public member_ `uint32 NumParameters : 8;`
- L245 _public member_ `uint32 Idx : 24;`
- L247 _public function_ `uint32 AsInt() const`
- L248 _public function_ `static FBaseTypenameId FromInt(uint32 Int)`
- L249 _public function_ `bool operator==(FBaseTypenameId O) const`

#### struct `PlainProps::FParametricTypeId`  
`struct FParametricTypeId : FBaseTypenameId`  
_L252-256_
- inherits: `FBaseTypenameId`
- L255 _public function_ `static FParametricTypeId FromInt(uint32 Int)`

#### struct `PlainProps::FTypenameId`  
`struct FTypenameId : FBaseTypenameId`  
_L258-267_
- inherits: `FBaseTypenameId`
- L260 _public function_ `explicit FTypenameId(FParametricTypeId Parametric) : FBaseTypenameId(Parametric)`
- L261 _public function_ `explicit FTypenameId(FConcreteTypenameId Concrete) : FBaseTypenameId(0, Concrete.Id.Idx)`
- L263 _public function_ `bool IsConcrete() const`
- L264 _public function_ `bool IsParametric() const`
- L265 _public function_ `FConcreteTypenameId AsConcrete() const`
- L266 _public function_ `FParametricTypeId AsParametric() const`

#### struct `PlainProps::FType`  
`struct FType`  
_L271-278_
- L273 _public member_ `FScopeId Scope;`
- L274 _public member_ `FTypenameId Name;`
- L276 _public function_ `bool operator==(FType O) const`

#### class `PlainProps::FOptionalId`  
`class FOptionalId`  
_L300-307_
- L303 _protected member_ `uint32 Idx = ~0u;`
- L305 _public function_ `explicit operator bool() const`

#### class `PlainProps::TOptionalId`  
`template<class T> class TOptionalId : public FOptionalId`  
_L310-346_
- inherits: `FOptionalId`
- L313 _public prototype_ `constexpr TOptionalId() = default;`
- L314 _public function_ `constexpr TOptionalId(FNoId)`
- L317 _public function_ `template<typename U> constexpr TOptionalId(U Id) requires (std::is_convertible_v<U, T>)`
- L323 _public function_ `template<typename U> constexpr explicit TOptionalId(TOptionalId<U> In) requires (std::is_constructible_v<T,U>) : FOptionalId(static_cast<const FOptionalId&>(In))`
- L328 _public function_ `template<class U> explicit operator TOptionalId<U>() const requires(std::is_convertible_v<U, T> || std::is_convertible_v<T, U>)`
- L333 _public function_ `T Get() const`
- L339 _public function_ `T GetOr(T Fallback) const`

#### struct `PlainProps::FNestedScope`  
`struct FNestedScope`  
_L381-388_
- desc: Resolved FNestedScopeId
- L383 _public member_ `FScopeId Outer;` — @invariant !!Outer
- L384 _public member_ `FFlatScopeId Inner;`
- L386 _public function_ `bool operator==(FNestedScope O) const`

#### struct `PlainProps::FParameterIndexRange`  
`struct FParameterIndexRange : FBaseTypenameId`  
_L390-390_
- inherits: `FBaseTypenameId`

#### struct `PlainProps::FParametricType`  
`struct FParametricType`  
_L393-399_
- desc: Name-resolved FParametricTypeId
- L395 _public member_ `FOptionalConcreteTypenameId Name;`
- L396 _public member_ `FParameterIndexRange Parameters;`
- L398 _public function_ `bool operator==(FParametricType O) const`

#### struct `PlainProps::FParametricTypeView`  
`struct FParametricTypeView`  
_L402-414_
- desc: Fully resolved FParametricTypeId
- L404 _public function_ `FParametricTypeView(FConcreteTypenameId InName, uint8 NumParams, const FType* Params) : Name(InName), NumParameters(NumParams), Parameters(Params)`
- L405 _public function_ `FParametricTypeView(FOptionalConcreteTypenameId InName, uint8 NumParams, const FType* Params) : Name(InName), NumParameters(NumParams), Parameters(Params)`
- L406 _public prototype_ `FParametricTypeView(FConcreteTypenameId InName, TConstArrayView<FType> Params);`
- L407 _public prototype_ `FParametricTypeView(FOptionalConcreteTypenameId InName, TConstArrayView<FType> Params);`
- L409 _public member_ `FOptionalConcreteTypenameId Name;`
- L410 _public member_ `uint8 NumParameters;`
- L411 _public member_ `const FType* Parameters;`
- L413 _public function_ `TConstArrayView<FType> GetParameters() const`

#### struct `PlainProps::FUnpackedLeafType`  
`struct FUnpackedLeafType`  
_L433-444_
- L435 _public member_ `ELeafType Type;`
- L436 _public member_ `ELeafWidth Width;`
- L438 _public function_ `inline constexpr FUnpackedLeafType(ELeafType InType, ELeafWidth InWidth) : Type(InType), Width(InWidth)`
- L439 _public function_ `inline constexpr FUnpackedLeafType(FLeafType In) : Type(In.Type), Width(In.Width)`
- L441 _public function_ `inline uint16 AsInt() const`
- L442 _public function_ `inline bool operator==(FUnpackedLeafType O) const`
- L443 _public function_ `inline constexpr FMemberType Pack() const`

#### enum `PlainProps::ESchemaFormat`  
`enum class ESchemaFormat`  
_L506-506_
- L506 _public enumerator_ `enum class ESchemaFormat { StableNames, InMemoryNames }; using FUtf8Builder = FUtf8StringBuilderBase; class FIdsBase`
- L506 _public enumerator_ `enum class ESchemaFormat { StableNames, InMemoryNames }; using FUtf8Builder = FUtf8StringBuilderBase; class FIdsBase`

#### class `PlainProps::FIdsBase`  
`class FIdsBase`  
_L513-531_
- desc: Resolves structured ids and converts ids to strings
- L516 _public function_ `virtual ~FIdsBase()`
- L518 _public prototype_ `virtual uint32 NumNames() const = 0;`
- L519 _public prototype_ `virtual uint32 NumNestedScopes() const = 0;`
- L520 _public prototype_ `virtual uint32 NumParametricTypes() const = 0;`
- L522 _public prototype_ `virtual FNestedScope Resolve(FNestedScopeId Id) const = 0;`
- L523 _public prototype_ `virtual FParametricTypeView Resolve(FParametricTypeId Id) const = 0;`
- L525 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FNameId Name) const = 0;`
- L526 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FMemberId Name) const;`
- L527 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FOptionalMemberId Name) const;`
- L528 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FScopeId Scope) const;`
- L529 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FTypenameId Typename) const;`
- L530 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FType Type) const;`

#### class `PlainProps::FIds`  
`class FIds : public FIdsBase`  
_L534-547_
- inherits: `FIdsBase`
- desc: Runtime id resolver
- L540 _public prototype_ `virtual uint32 NumEnums() const = 0;`
- L541 _public prototype_ `virtual uint32 NumStructs() const = 0;`
- L542 _public prototype_ `virtual FType Resolve(FEnumId Id) const = 0;`
- L543 _public prototype_ `virtual FType Resolve(FStructId Id) const = 0;`
- L545 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FEnumId Enum) const;`
- L546 _public prototype_ `virtual void AppendString(FUtf8Builder& Out, FStructId Struct) const;`

#### class `PlainProps::FDebugIds`  
`class FDebugIds`  
_L550-569_
- desc: Helps format log messages
- L553 _public function_ `explicit FDebugIds(const FIds& InIds) : Ids(InIds)`
- L555 _public prototype_ `FString Print(FNameId Name) const;`
- L556 _public prototype_ `FString Print(FMemberId Name) const;`
- L557 _public prototype_ `FString Print(FOptionalMemberId Name) const;`
- L558 _public prototype_ `FString Print(FScopeId Scope) const;`
- L559 _public prototype_ `FString Print(FTypenameId Typename) const;`
- L560 _public prototype_ `FString Print(FConcreteTypenameId Typename) const;`
- L561 _public prototype_ `FString Print(FParametricTypeId Typename) const;`
- L562 _public prototype_ `FString Print(FType Type) const;`
- L563 _public prototype_ `FString Print(FEnumId Enum) const;`
- L564 _public prototype_ `FString Print(FStructId Struct) const;`
- L565 _public prototype_ `FString Print(const struct FMemberSchema& Schema) const;`
- L568 _private member_ `const FIds& Ids;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PlainProps`
- L20 _function_ `inline constexpr SIZE_T SizeOf(ELeafWidth Width)` (scope `PlainProps`)
- L25 _function_ `inline ELeafWidth WidthOf(SIZE_T Size)` (scope `PlainProps`)
- L31 _function_ `inline SIZE_T SizeOf(ESizeType Width)` (scope `PlainProps`)
- L37 _function_ `inline constexpr uint64 Max(ESizeType Width)` (scope `PlainProps`)
- L44 _function_ `template<SIZE_T Size> constexpr ELeafWidth IllegalLeafWidth()` (scope `PlainProps`)
- L50 _variable_ `template<SIZE_T Size> constexpr ELeafWidth LeafWidth = IllegalLeafWidth<Size>();` (scope `PlainProps`)
- L54 _variable_ `template<> inline constexpr ELeafWidth LeafWidth<1> = ELeafWidth::B8;` (scope `PlainProps`)
- L101 _function_ `friend inline bool operator==(FMemberType A, FMemberType B)` (scope `PlainProps`)
- L116 _function_ `friend uint32 GetTypeHash(FNameId Id)` (scope `PlainProps`)
- L124 _function_ `friend uint32 GetTypeHash(FMemberId Member)` (scope `PlainProps`)
- L133 _function_ `friend uint32 GetTypeHash(FEnumId In)` (scope `PlainProps`)
- L141 _function_ `friend uint32 GetTypeHash(FStructId In)` (scope `PlainProps`)
- L157 _function_ `inline FDeclId LowerCast(FBindId Id)` (scope `PlainProps`) — Static FBindId -> FDeclId cast once you've checked the bind id isnt type-erased
- L158 _function_ `inline FBindId UpCast(FDeclId Id)` (scope `PlainProps`)
- L173 _function_ `friend uint32 GetTypeHash(FInnerId In)` (scope `PlainProps`)
- L186 _function_ `friend uint32 GetTypeHash(FSchemaId Schema)` (scope `PlainProps`)
- L191 _function_ `static void KeepDebugInfo(FStructSchemaId*)` (scope `PlainProps`)
- L195 _function_ `static void KeepDebugInfo(FEnumSchemaId*)` (scope `PlainProps`)
- L200 _variable_ `inline constexpr FNoId NoId;` (scope `PlainProps`)
- L277 _function_ `friend uint32 GetTypeHash(FType Type)` (scope `PlainProps`)
- L283 _function_ `template<class IdType> uint32 ToIdx(IdType Id)` (scope `PlainProps`)
- L287 _function_ `inline uint32 ToIdx(FMemberId Name)` (scope `PlainProps`)
- L288 _function_ `inline uint32 ToIdx(FParametricTypeId Id)` (scope `PlainProps`)
- L289 _function_ `inline uint32 ToIdx(FConcreteTypenameId Name)` (scope `PlainProps`)
- L292 _function_ `template<class IdType> IdType FromIdx(uint32 Idx)` (scope `PlainProps`)
- L296 _function_ `template<> inline FMemberId FromIdx(uint32 Idx)` (scope `PlainProps`)
- L306 _function_ `friend uint32 GetTypeHash(FOptionalId Id)` (scope `PlainProps`)
- L344 _function_ `friend bool operator==(TOptionalId A, TOptionalId B)` (scope `PlainProps`)
- L345 _function_ `friend bool operator!=(TOptionalId A, TOptionalId B)` (scope `PlainProps`)
- L348 _typedef_ `using FOptionalNameId = TOptionalId<FNameId>;` (scope `PlainProps`)
- L349 _typedef_ `using FOptionalMemberId = TOptionalId<FMemberId>;` (scope `PlainProps`)
- L350 _typedef_ `using FOptionalEnumId = TOptionalId<FEnumId>;` (scope `PlainProps`)
- L351 _typedef_ `using FOptionalStructId = TOptionalId<FStructId>;` (scope `PlainProps`)
- L352 _typedef_ `using FOptionalDeclId = TOptionalId<FDeclId>;` (scope `PlainProps`)
- L353 _typedef_ `using FOptionalBindId = TOptionalId<FBindId>;` (scope `PlainProps`)
- L354 _typedef_ `using FOptionalInnerId = TOptionalId<FInnerId>;` (scope `PlainProps`)
- L355 _typedef_ `using FOptionalSchemaId = TOptionalId<FSchemaId>;` (scope `PlainProps`)
- L356 _typedef_ `using FOptionalStructSchemaId = TOptionalId<FStructSchemaId>;` (scope `PlainProps`)
- L357 _typedef_ `using FOptionalEnumSchemaId = TOptionalId<FEnumSchemaId>;` (scope `PlainProps`)
- L358 _typedef_ `using FOptionalNestedScopeId = TOptionalId<FNestedScopeId>;` (scope `PlainProps`)
- L359 _typedef_ `using FOptionalParametricTypeId = TOptionalId<FParametricTypeId>;` (scope `PlainProps`)
- L360 _typedef_ `using FOptionalConcreteTypenameId = TOptionalId<FConcreteTypenameId>;` (scope `PlainProps`)
- L363 _function_ `template<class IdType> inline constexpr TOptionalId<IdType> ToOptional(IdType Id)` (scope `PlainProps`)
- L365 _function_ `inline FOptionalInnerId ToOptionalInner(FOptionalEnumId In)` (scope `PlainProps`)
- L366 _function_ `inline FOptionalInnerId ToOptionalInner(FOptionalStructId In)` (scope `PlainProps`)
- L367 _function_ `inline FOptionalInnerId ToOptionalInner(FOptionalDeclId In)` (scope `PlainProps`)
- L368 _function_ `inline FOptionalEnumId ToOptionalEnum(FOptionalInnerId In)` (scope `PlainProps`)
- L369 _function_ `inline FOptionalStructId ToOptionalStruct(FOptionalInnerId In)` (scope `PlainProps`)
- L370 _function_ `inline FOptionalStructId ToOptionalStruct(FOptionalDeclId In)` (scope `PlainProps`)
- L371 _function_ `inline FOptionalStructId ToOptionalStruct(FOptionalBindId In)` (scope `PlainProps`)
- L372 _function_ `inline FOptionalDeclId ToOptionalDeclId(FOptionalInnerId In)` (scope `PlainProps`)
- L373 _function_ `inline FOptionalSchemaId ToOptionalSchema(FOptionalStructSchemaId In)` (scope `PlainProps`)
- L374 _function_ `inline FOptionalSchemaId ToOptionalSchema(FOptionalEnumSchemaId In)` (scope `PlainProps`)
- L375 _function_ `inline FOptionalEnumSchemaId ToOptionalEnum(FOptionalSchemaId In)` (scope `PlainProps`)
- L376 _function_ `inline FOptionalStructSchemaId ToOptionalStruct(FOptionalSchemaId In)` (scope `PlainProps`)
- L387 _function_ `friend uint32 GetTypeHash(FNestedScope Scope)` (scope `PlainProps`)
- L447 _variable_ `template<Enumeration T> inline constexpr FUnpackedLeafType ReflectEnum = { ELeafType::Enum, LeafWidth<sizeof(T)> };` (scope `PlainProps`)
- L450 _function_ `template<typename T> constexpr FUnpackedLeafType IllegalLeaf()` (scope `PlainProps`)
- L457 _variable_ `template<Arithmetic T> inline constexpr FUnpackedLeafType ReflectArithmetic = IllegalLeaf<T>;` (scope `PlainProps`)
- L459 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<bool> = { ELeafType::Bool, ELeafWidth::B8 };` (scope `PlainProps`)
- L463 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<int8> = { ELeafType::IntS, ELeafWidth::B8 };` (scope `PlainProps`)
- L464 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<int16> = { ELeafType::IntS, ELeafWidth::B16 };` (scope `PlainProps`)
- L465 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<int32> = { ELeafType::IntS, ELeafWidth::B32 };` (scope `PlainProps`)
- L466 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<int64> = { ELeafType::IntS, ELeafWidth::B64 };` (scope `PlainProps`)
- L467 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<uint8> = { ELeafType::IntU, ELeafWidth::B8 };` (scope `PlainProps`)
- L468 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<uint16> = { ELeafType::IntU, ELeafWidth::B16 };` (scope `PlainProps`)
- L469 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<uint32> = { ELeafType::IntU, ELeafWidth::B32 };` (scope `PlainProps`)
- L470 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<uint64> = { ELeafType::IntU, ELeafWidth::B64 };` (scope `PlainProps`)
- L471 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<float> = { ELeafType::Float, ELeafWidth::B32 };` (scope `PlainProps`)
- L472 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<double> = { ELeafType::Float, ELeafWidth::B64 };` (scope `PlainProps`)
- L473 _variable_ `template<> inline constexpr FUnpackedLeafType ReflectArithmetic<char> = { ELeafType::Unicode, ELeafWidth::B8 };` (scope `PlainProps`)
- L476 _function_ `template<Arithmetic T> inline constexpr FUnpackedLeafType MakeLeafType()` (scope `PlainProps`)
- L479 _function_ `template<Enumeration T> inline constexpr FUnpackedLeafType MakeLeafType()` (scope `PlainProps`)
- L482 _variable_ `template<typename T> inline constexpr FUnpackedLeafType ReflectLeaf = MakeLeafType<T>();` (scope `PlainProps`)
- L486 _function_ `inline constexpr ESizeType RangeSizeOf(bool)` (scope `PlainProps`)
- L487 _function_ `inline constexpr ESizeType RangeSizeOf(int8)` (scope `PlainProps`)
- L488 _function_ `inline constexpr ESizeType RangeSizeOf(int16)` (scope `PlainProps`)
- L489 _function_ `inline constexpr ESizeType RangeSizeOf(int32)` (scope `PlainProps`)
- L490 _function_ `inline constexpr ESizeType RangeSizeOf(int64)` (scope `PlainProps`)
- L491 _function_ `inline constexpr ESizeType RangeSizeOf(uint8)` (scope `PlainProps`)
- L492 _function_ `inline constexpr ESizeType RangeSizeOf(uint16)` (scope `PlainProps`)
- L493 _function_ `inline constexpr ESizeType RangeSizeOf(uint32)` (scope `PlainProps`)
- L494 _function_ `inline constexpr ESizeType RangeSizeOf(uint64)` (scope `PlainProps`)
- L499 _function_ `template<typename T> const T* AlignPtr(const void* Ptr)` (scope `PlainProps`)
- L510 _typedef_ `using FUtf8Builder = FUtf8StringBuilderBase;` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsUeCoreBindings.h` (Public)


#### struct `TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer<PlainProps::TRangeView<T>>`  
_L35-38_
- L37 _public member_ `static inline constexpr bool Value = true;`

#### class `PlainProps::UE::FSensitiveName`  
`class FSensitiveName`  
_L43-89_
- L47 _public typedef_ `using IntType = uint32;`
- L51 _public prototype_ `inline explicit FSensitiveName(FName Name);`
- L52 _public function_ `inline explicit FSensitiveName(FAnsiStringView Name) : FSensitiveName(FName(Name))`
- L53 _public function_ `inline FName ToName() const`
- L54 _public function_ `inline void AppendString(FUtf8StringBuilderBase& Out) const`
- L55 _public prototype_ `inline IntType ToUnstableInt() const;`
- L56 _public function_ `inline static FSensitiveName FromUnstableInt(IntType UnstableInt)`
- L57 _public function_ `[[nodiscard]] inline bool operator==(FSensitiveName Other) const`
- L58 _public function_ `[[nodiscard]] inline bool operator!=(FSensitiveName Other) const`
- L62 _private prototype_ `inline explicit FSensitiveName(IntType);`
- L65 _private member_ `static constexpr uint32 DifferentIdsFlag = 1u << 31;`
- L66 _private member_ `static constexpr uint32 DisplayIdMask = ~DifferentIdsFlag;`
- L67 _private member_ `uint32 Value;` — DisplayId + DifferentIdsFlag
- L68 _private function_ `inline bool SameIds() const`
- L69 _private function_ `inline FNameEntryId GetDisplayId() const`
- L70 _private function_ `inline FNameEntryId GetComparisonId() const`
- L71 _private function_ `inline uint32 GetUnstableValue() const` — ToUnstableInt() helper
- L73 _private member_ `FNameEntryId DisplayId;`
- L80 _private function_ `inline uint32 GetNumber() const` — ToName() helper
- L81 _private prototype_ `static uint32 InitValue(FName Name);` — Constructor helper for WITH_CASE_PRESERVING_NAME
- L82 _private prototype_ `static FNameEntryId InitDisplayId(FName Name);` — Constructor helper for !WITH_CASE_PRESERVING_NAME
- L84 _private member_ `int32 Number;`
- L86 _private prototype_ `inline static uint32 InitValue(FName Name);` — Constructor helper for WITH_CASE_PRESERVING_NAME
- L87 _private prototype_ `inline static FNameEntryId InitDisplayId(FName Name);` — Constructor helper for !WITH_CASE_PRESERVING_NAME
- L91 _function_ `FSensitiveName::FSensitiveName(FName Name) #if WITH_CASE_PRESERVING_NAME : Value(InitValue(Name)) #else : DisplayId(InitDisplayId(Name)) #endif #if !UE_FNAME_OUTLINE_NUMBER , Number(Name.GetNumber()) #endif`
- L102 _function_ `FSensitiveName::FSensitiveName(IntType UnstableInt) #if WITH_CASE_PRESERVING_NAME : Value(static_cast<uint32>(UnstableInt)) #else : DisplayId(FNameEntryId::FromUnstableInt(static_cast<uint32>(UnstableInt))) #endif #if !UE_FNAME_OUTLINE_NUMBER , Number(static_cast<uint32>(UnstableInt >> 32)) #endif`
- L113 _function_ `FSensitiveName::IntType FSensitiveName::ToUnstableInt() const`
- L124 _function_ `uint32 FSensitiveName::InitValue(FName Name)`
- L129 _function_ `FNameEntryId FSensitiveName::InitDisplayId(FName Name)`

#### class `PlainProps::UE::FNumeralGenerator`  
`class FNumeralGenerator`  
_L137-157_
- desc: Temporary implementation for numeral structs
- L139 _private member_ `TIdIndexer<FSensitiveName>& Indexer;`
- L140 _private member_ `TArray<FMemberId> Cache;` — 0, 1, 2, ..
- L142 _private prototype_ `FMemberId Grow(int32 Max);`
- L145 _public function_ `FNumeralGenerator(TIdIndexer<FSensitiveName>& InIndexer) : Indexer(InIndexer)`
- L147 _public function_ `inline FMemberId Make(uint16 Numeral)`
- L152 _public function_ `TConstArrayView<FMemberId> MakeRange(uint16 Numerals)`

#### struct `PlainProps::UE::TArrayBinding`  
`template <typename T, class Allocator> struct TArrayBinding : IItemRangeBinding`  
_L242-271_
- inherits: `IItemRangeBinding`
- L244 _public typedef_ `using SizeType = int32;`
- L245 _public typedef_ `using ItemType = T;`
- L246 _public typedef_ `using ArrayType = TArray<T, Allocator>;`
- L248 _public member_ `inline static constexpr std::string_view BindName = TTypename<ArrayType>::RangeBindName;`
- L250 _public function_ `virtual void MakeItems(FLoadRangeContext& Ctx) const override`
- L266 _public function_ `virtual void ReadItems(FSaveRangeContext& Ctx) const override`

#### struct `PlainProps::UE::TStringBinding`  
`template<class StringType> struct TStringBinding : ILeafRangeBinding`  
_L276-362_
- inherits: `ILeafRangeBinding`
- L278 _public typedef_ `using SizeType = int32;`
- L279 _public typedef_ `using ItemType = char8_t;`
- L280 _public typedef_ `using CharType = typename StringType::ElementType;`
- L282 _public member_ `inline static constexpr std::string_view BindName = TTypename<StringType>::RangeBindName;`
- L284 _public function_ `virtual void SaveLeaves(const void* Range, FLeafRangeAllocator& Out) const override`
- L316 _public function_ `virtual void LoadLeaves(void* Range, FLeafRangeLoadView Items) const override`
- L355 _public function_ `virtual bool DiffLeaves(const void* RangeA, const void* RangeB) const override`

#### struct `PlainProps::UE::TUniquePtrBinding`  
`template <typename T> struct TUniquePtrBinding : IItemRangeBinding`  
_L367-405_
- inherits: `IItemRangeBinding`
- L369 _public typedef_ `using SizeType = bool;`
- L370 _public typedef_ `using ItemType = T;`
- L372 _public member_ `inline static constexpr std::string_view BindName = "Un`
- L374 _public function_ `virtual void MakeItems(FLoadRangeContext& Ctx) const override`
- L400 _public function_ `virtual void ReadItems(FSaveRangeContext& Ctx) const override`

#### struct `PlainProps::UE::TOptionalBinding`  
`template <typename T> struct TOptionalBinding : IItemRangeBinding`  
_L410-450_
- inherits: `IItemRangeBinding`
- L412 _public typedef_ `using SizeType = bool;`
- L413 _public typedef_ `using ItemType = T;`
- L415 _public member_ `inline static constexpr std::string_view BindName = "Op`
- L417 _public function_ `virtual void MakeItems(FLoadRangeContext& Ctx) const override`
- L444 _public function_ `virtual void ReadItems(FSaveRangeContext& Ctx) const override`

#### struct `PlainProps::UE::TSetBinding`  
`template <typename T, typename KeyFuncs, typename SetAllocator> struct TSetBinding : IItemRangeBinding`  
_L455-579_
- inherits: `IItemRangeBinding`
- L457 _public typedef_ `using SizeType = int32;`
- L458 _public typedef_ `using ItemType = T;`
- L459 _public typedef_ `using SetType = TSet<T, KeyFuncs, SetAllocator>;`
- L461 _public member_ `inline static constexpr std::string_view BindName = TTypename<SetType>::RangeBindName;`
- L463 _public function_ `virtual void MakeItems(FLoadRangeContext& Ctx) const override`
- L529 _public function_ `virtual void ReadItems(FSaveRangeContext& Ctx) const override`
- L571 _public function_ `static FExistingItemSlice GetContiguousSlice(int32 Idx, const TSparseArray<TSparseSetElement<T>>& Elems)`

#### struct `PlainProps::UE::TPairBinding`  
`template <typename K, typename V> struct TPairBinding : ICustomBinding`  
_L585-630_
- inherits: `ICustomBinding`
- desc: Only used for non-default constructible pairs
- L587 _public typedef_ `using Type = TPair<K,V>;`
- L590 _public function_ `template<class Ids> TPairBinding(TCustomSpecifier<Ids, 2>& Spec) : MemberIds`
- L598 _public function_ `inline void Save(FMemberBuilder& Dst, const TPair<K,V>& Src, const Type* Default, const FSaveContext& Ctx) const`
- L604 _public function_ `inline void Load(TPair<K,V>& Dst, FStructLoadView Src, ECustomLoadMethod Method) const`
- L621 _public function_ `template<typename ContextType> bool Diff(const TPair<K,V>& A, const TPair<K,V>& B, ContextType& Ctx) const`
- L627 _public member_ `const FMemberId MemberIds[2];`
- L628 _public member_ `const TMemberSerializer<K> Key;`
- L629 _public member_ `const TMemberSerializer<V> Value;`

#### struct `PlainProps::UE::TMapBinding`  
`template <typename K, typename V, typename SetAllocator, typename KeyFuncs> struct TMapBinding : public TSetBinding<TPair<K, V>, KeyFuncs, SetAllocator>`  
_L635-641_
- inherits: `TSetBinding<TPair<K,V>,KeyFuncs,SetAllocator>`
- L637 _public typedef_ `using MapType = TMap<K, V, SetAllocator, KeyFuncs>;`
- L638 _public typedef_ `using Super = TSetBinding<TPair<K, V>, KeyFuncs, SetAllocator>;`
- L640 _public member_ `inline static constexpr std::string_view BindName = TTypename<MapType>::RangeBindName;`

#### struct `PlainProps::UE::TAuxEnumAsByteBinding`  
`template <Enumeration E> struct TAuxEnumAsByteBinding : ICustomBinding`  
_L646-673_
- inherits: `ICustomBinding`
- L648 _public typedef_ `using Type = TEnumAsByte<E>;`
- L650 _public member_ `const FMemberId MemberIds[1];`
- L651 _public member_ `const FEnumId EnumId;`
- L654 _public function_ `template<class Ids> TAuxEnumAsByteBinding(TCustomSpecifier<Ids, 1>& Spec) : MemberIds`
- L661 _public function_ `void Save(FMemberBuilder& Dst, const TEnumAsByte<E>& Src, const TEnumAsByte<E>* Default, const FSaveContext& Ctx) const`
- L666 _public function_ `void Load(TEnumAsByte<E>& Dst, FStructLoadView Src, ECustomLoadMethod Method) const`
- L672 _public function_ `static bool Diff(TEnumAsByte<E> A, TEnumAsByte<E> B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FTransformBinding`  
`struct FTransformBinding : ICustomBinding`  
_L678-702_
- inherits: `ICustomBinding`
- desc: TODO: Consider macroifying parts of this, e.g PP_CUSTOM_BIND(PLAINPROPS_API, FTransform, Transform, Translate, Rotate, Scale)
- L680 _public typedef_ `using Type = FTransform;`
- L683 _public member_ `const FMemberId MemberIds[3];`
- L684 _public member_ `const FDualStructId VectorId;`
- L685 _public member_ `const FDualStructId QuatId;`
- L686 _public member_ `mutable FStructDeclarationPtr VectorDeclaration;`
- L687 _public member_ `mutable FStructDeclarationPtr QuatDeclaration;`
- L690 _public function_ `template<class Ids> FTransformBinding(TCustomSpecifier<Ids, 3>& Spec) : MemberIds`
- L698 _public prototype_ `void Save(FMemberBuilder& Dst, const FTransform& Src, const FTransform* Default, const FSaveContext& Context) const;`
- L699 _public prototype_ `void Load(FTransform& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L700 _public prototype_ `bool Diff(const FTransform& A, const FTransform& B, FDiffContext& Ctx) const;`
- L701 _public function_ `inline static bool Diff(const FTransform& A, const FTransform& B, const FBindContext&)`

#### enum `PlainProps::UE::FTransformBinding::EMember`  
`enum class EMember : uint8`  
_L681-681_
- L681 _public enumerator_ `enum class EMember : uint8 { Translate, Rotate, Scale }; const FMemberId MemberIds[3]; const FDualStructId VectorId; const FDualStructId QuatId; mutable FStructDeclarationPtr VectorDeclaration; mutable FStructDeclarationPtr QuatDeclaration;`
- L681 _public enumerator_ `enum class EMember : uint8 { Translate, Rotate, Scale }; const FMemberId MemberIds[3]; const FDualStructId VectorId; const FDualStructId QuatId; mutable FStructDeclarationPtr VectorDeclaration; mutable FStructDeclarationPtr QuatDeclaration;`
- L681 _public enumerator_ `enum class EMember : uint8 { Translate, Rotate, Scale }; const FMemberId MemberIds[3]; const FDualStructId VectorId; const FDualStructId QuatId; mutable FStructDeclarationPtr VectorDeclaration; mutable FStructDeclarationPtr QuatDeclaration;`

#### struct `PlainProps::UE::FGuidBinding`  
`struct FGuidBinding : ICustomBinding`  
_L706-721_
- inherits: `ICustomBinding`
- L708 _public typedef_ `using Type = FGuid;`
- L709 _public member_ `const FMemberId MemberIds[4];`
- L712 _public function_ `template<class Ids> FGuidBinding(TCustomSpecifier<Ids, 4>& Spec) : MemberIds`
- L718 _public prototype_ `void Save(FMemberBuilder& Dst, const FGuid& Src, const FGuid* Default, const FSaveContext&) const;`
- L719 _public function_ `inline static void Plan(FMemcpyLoadPlan& Out)`
- L720 _public function_ `inline static bool Diff(FGuid A, FGuid B, const FBindContext&)`

#### struct `PlainProps::UE::FColorBinding`  
`struct FColorBinding : ICustomBinding`  
_L725-740_
- inherits: `ICustomBinding`
- L727 _public typedef_ `using Type = FColor;`
- L728 _public member_ `const FMemberId MemberIds[4];`
- L731 _public function_ `template<class Ids> FColorBinding(TCustomSpecifier<Ids, 4>& Spec) : MemberIds`
- L737 _public prototype_ `void Save(FMemberBuilder& Dst, const FColor& Src, const FColor* Default, const FSaveContext&) const;`
- L738 _public function_ `inline static void Plan(FMemcpyLoadPlan& Out)`
- L739 _public function_ `inline static bool Diff(FColor A, FColor B, const FBindContext&)`

#### struct `PlainProps::UE::FLinearColorBinding`  
`struct FLinearColorBinding : ICustomBinding`  
_L744-759_
- inherits: `ICustomBinding`
- L746 _public typedef_ `using Type = FLinearColor;`
- L747 _public member_ `const FMemberId MemberIds[4];`
- L750 _public function_ `template<class Ids> FLinearColorBinding(TCustomSpecifier<Ids, 4>& Spec) : MemberIds`
- L756 _public prototype_ `void Save(FMemberBuilder& Dst, const FLinearColor& Src, const FLinearColor* Default, const FSaveContext&) const;`
- L757 _public function_ `inline static void Plan(FMemcpyLoadPlan& Out)`
- L758 _public function_ `inline static bool Diff(FLinearColor A, FLinearColor B, const FBindContext&)`

#### struct `PlainProps::UE::FBaseDeltaBinding`  
`struct FBaseDeltaBinding`  
_L763-781_
- L766 _public member_ `FMemberId MemberIds[2];`
- L767 _public function_ `FMemberId DelId() const`
- L768 _public function_ `FMemberId AddId() const`
- L771 _public function_ `template<class Ids> FBaseDeltaBinding(TInit<Ids>) : MemberIds`
- L776 _public function_ `template<class Ids> static FBaseDeltaBinding Cache()`

#### enum `PlainProps::UE::FBaseDeltaBinding::EOp`  
`enum class EOp`  
_L765-765_
- L765 _public enumerator_ `enum class EOp { Del, Add }; FMemberId MemberIds[2]; FMemberId DelId() const { return MemberIds[(uint32)EOp::Del]; } FMemberId AddId() const { return MemberIds[(uint32)EOp::Add]; } template<class Ids> FBaseDeltaBinding(TInit<Ids>) : MemberIds{Ids::IndexMember("Del"), Ids::IndexMember("Add")}`
- L765 _public enumerator_ `enum class EOp { Del, Add }; FMemberId MemberIds[2]; FMemberId DelId() const { return MemberIds[(uint32)EOp::Del]; } FMemberId AddId() const { return MemberIds[(uint32)EOp::Add]; } template<class Ids> FBaseDeltaBinding(TInit<Ids>) : MemberIds{Ids::IndexMember("Del"), Ids::IndexMember("Add")}`

#### struct `PlainProps::UE::TBaseDeltaBinding`  
`template <typename SetType, typename KeyType> struct TBaseDeltaBinding : ICustomBinding, FBaseDeltaBinding`  
_L784-1020_
- inherits: `ICustomBinding,FBaseDeltaBinding`
- L786 _public typedef_ `using Type = SetType;`
- L787 _public typedef_ `using ElemType = typename SetType::ElementType;`
- L788 _public member_ `static constexpr ESizeType MaxSize = ESizeType::S32;`
- L789 _public member_ `static constexpr bool bIsSet = std::is_same_v<KeyType, ElemType>;`
- L791 _public member_ `const TMemberSerializer<ElemType> Elems;`
- L794 _public function_ `template<class Ids> TBaseDeltaBinding(TCustomInit<Ids>& Init) : FBaseDeltaBinding(FBaseDeltaBinding::Cache<Ids>()) , Elems(Init, bIsSet ? MakeArrayView(MemberIds) : MakeArrayView({AddId()}))`
- L800 _public function_ `template<typename KeyOrElemType> static const KeyOrElemType& Get(const ElemType& Elem)`
- L813 _public function_ `inline void SaveDelta(FMemberBuilder& Dst, const SetType& Src, const SetType* Default, const FSaveContext& Ctx, const TMemberSerializer<KeyType>& Keys) const` — Todo: Reimplement with Assign/Remove/Insert like SaveSetDelta in PlainPropsUObjectBindings.cpp
- L851 _public function_ `template<typename ItemType> FTypedRange SaveAll(const SetType& Set, const TMemberSerializer<ItemType>& Schema, const FSaveContext& Ctx) const`
- L864 _public function_ `template<typename ItemType> FTypedRange SaveSome(const SetType& Set, const TBitArray<>& Subset, const TMemberSerializer<ItemType>& Schema, const FSaveContext& Ctx) const`
- L878 _public function_ `inline void LoadDelta(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method, const TMemberSerializer<KeyType>& Keys) const`
- L902 _public function_ `template<EOp Op, typename T> void ApplyItems(SetType& Out, FRangeLoadView Items, const TMemberSerializer<T>& Schema) const`
- L926 _public function_ `template<EOp Op, typename T> void ApplyLeaves(SetType& Out, FLeafRangeLoadView Items) const requires (Op == EOp::Add && !std::is_same_v<T, bool>)`
- L932 _public function_ `template<EOp Op, typename T> void ApplyLeaves(SetType& Out, FLeafRangeLoadView Items) const`
- L941 _public function_ `template<EOp Op, typename T> void ApplyRanges(SetType& Out, FNestedRangeLoadView Items, const TMemberSerializer<T>& Schema) const`
- L955 _public function_ `template<EOp Op, typename T> void ApplyStructs(SetType& Out, FStructRangeLoadView Items) const`
- L978 _public function_ `template<EOp Op, typename T> void ApplyItem(SetType& Out, T&& Item) const`
- L990 _public function_ `inline static bool ContainsValue(const Type& Set, const ElemType& Elem)`
- L1003 _public function_ `inline static bool Diff(const Type& As, const Type& Bs, const FBindContext&)`

#### struct `PlainProps::UE::TSetDeltaBinding`  
`template <typename T, typename KeyFuncs, typename SetAllocator> struct TSetDeltaBinding : TBaseDeltaBinding<TSet<T, KeyFuncs, SetAllocator>, T>`  
_L1023-1052_
- inherits: `TBaseDeltaBinding<TSet<T,KeyFuncs,SetAllocator>,T>`
- L1025 _public typedef_ `using SetType = TSet<T, KeyFuncs, SetAllocator>;`
- L1026 _public typedef_ `using Super = TBaseDeltaBinding<SetType, T>;`
- L1037 _public function_ `template<class Ids> TSetDeltaBinding(TCustomSpecifier<Ids, 2>& Spec) : Super(Spec)`
- L1043 _public function_ `inline void Save(FMemberBuilder& Dst, const SetType& Src, const SetType* Default, const FSaveContext& Ctx) const`
- L1048 _public function_ `inline void Load(SetType& Dst, FStructLoadView Src, ECustomLoadMethod Method) const`

#### struct `PlainProps::UE::TSetDeltaBinding::FCustomTypename`  
`struct FCustomTypename`  
_L1028-1034_
- L1030 _public member_ `inline static constexpr std::string_view DeclName = "Se`
- L1031 _public member_ `inline static constexpr std::string_view BindName = Concat<DeclName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1032 _public member_ `inline static constexpr std::string_view Namespace;`
- L1033 _public typedef_ `using Parameters = std::tuple<T>;`

#### struct `PlainProps::UE::TMapDeltaBinding`  
`template <typename K, typename V, typename SetAllocator, typename KeyFuncs> struct TMapDeltaBinding : TBaseDeltaBinding<TMap<K, V, SetAllocator, KeyFuncs>, K>`  
_L1055-1088_
- inherits: `TBaseDeltaBinding<TMap<K,V,SetAllocator,KeyFuncs>,K>`
- L1057 _public typedef_ `using MapType = TMap<K, V, SetAllocator, KeyFuncs>;`
- L1058 _public typedef_ `using Super = TBaseDeltaBinding<MapType, K>;`
- L1068 _public member_ `const TMemberSerializer<K> Keys;`
- L1071 _public function_ `template<class Ids> TMapDeltaBinding(TCustomSpecifier<Ids, 2>& Spec) : Super(Spec) , Keys(Spec, {FBaseDeltaBinding::DelId()})`
- L1079 _public function_ `inline void Save(FMemberBuilder& Dst, const MapType& Src, const MapType* Default, const FSaveContext& Ctx) const`
- L1084 _public function_ `inline void Load(MapType& Dst, FStructLoadView Src, ECustomLoadMethod Method) const`

#### struct `PlainProps::UE::TMapDeltaBinding::FCustomTypename`  
`struct FCustomTypename`  
_L1060-1066_
- L1062 _public member_ `inline static constexpr std::string_view DeclName = "Ma`
- L1063 _public member_ `inline static constexpr std::string_view BindName = Concat<DeclName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1064 _public member_ `inline static constexpr std::string_view Namespace;`
- L1065 _public typedef_ `using Parameters = std::tuple<K, V>;`

#### struct `PlainProps::UE::TVariantMemberSerializer`  
`template <typename T, typename... Ts> struct TVariantMemberSerializer`  
_L1091-1113_
- L1093 _public typedef_ `using Type = TVariant<Ts...>;`
- L1094 _public typedef_ `using TSerializers = std::tuple<TMemberSerializer<Ts>...>;`
- L1096 _public function_ `static FTypedValue SaveMember(const Type& Src, const TSerializers& Serializers, const FSaveContext& Ctx)`
- L1101 _public function_ `static void LoadMember(Type& Dst, const TSerializers& Serializers, FMemberLoader& Members)`
- L1108 _public function_ `template<typename ContextType> static bool DiffMember(const Type& A, const Type& B, const TSerializers& Serializers, FMemberId MemberId, ContextType& Ctx)`

#### struct `PlainProps::UE::TVariantMemberFunctions`  
`template <typename... Ts> struct TVariantMemberFunctions`  
_L1116-1125_
- L1118 _public typedef_ `using Type = TVariant<Ts...>;`
- L1119 _public typedef_ `using TSerializers = std::tuple<TMemberSerializer<Ts>...>;`
- L1121 _public member_ `FTypedValue(*SaveMember)(const Type&, const TSerializers&, const FSaveContext&);`
- L1122 _public member_ `void(*LoadMember)(Type&, const TSerializers&, FMemberLoader&);`
- L1123 _public member_ `bool(*DiffMember)(const Type&, const Type&, const TSerializers&, FMemberId, const FBindContext&);`
- L1124 _public member_ `bool(*DiffAndTrackMember)(const Type&, const Type&, const TSerializers&, FMemberId, FDiffContext&);`

#### struct `PlainProps::UE::TVariantBinding`  
`template <typename... Ts> struct TVariantBinding : ICustomBinding`  
_L1128-1193_
- inherits: `ICustomBinding`
- L1130 _public typedef_ `using Type = TVariant<Ts...>;`
- L1131 _public typedef_ `using TSerializers = std::tuple<TMemberSerializer<Ts>...>;`
- L1132 _public member_ `static constexpr uint32 N = sizeof...(Ts);`
- L1134 _public member_ `const FMemberId MemberIds[N];`
- L1135 _public member_ `const TSerializers Serializers;`
- L1136 _public member_ `static constexpr TVariantMemberFunctions<Ts...> Functions[N] = {{ &TVariantMemberSerializer<Ts,Ts...>::SaveMember, &TVariantMemberSerializer<Ts,Ts...>::LoadMember, &TVariantMemberSerializer<Ts,Ts...>::DiffMember, &TVariantMemberSerializer<Ts,Ts...>::DiffMember}...};`
- L1143 _public function_ `template<class Ids> TVariantBinding(TCustomSpecifier<Ids, N>& Spec) : MemberIds`
- L1150 _public function_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const`
- L1158 _public function_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const`
- L1172 _public function_ `bool Diff(const Type& A, const Type& B, const FBindContext& Ctx) const`
- L1183 _public function_ `bool Diff(const Type& A, const Type& B, FDiffContext& Ctx) const`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FName>`  
_L1202-1202_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FName>`  
_L1203-1203_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FName>`  
_L1204-1204_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FName>`  
_L1205-1205_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FText>`  
_L1206-1206_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FIntPoint>`  
_L1207-1207_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FQuat>`  
_L1208-1208_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FTransform>`  
_L1209-1209_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FVector>`  
_L1210-1210_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FVector4>`  
_L1211-1211_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FGuid>`  
_L1212-1212_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FColor>`  
_L1213-1213_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FLinearColor>`  
_L1214-1214_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <> struct TTypename<FEmptyVariantState>`  
_L1215-1215_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <typename K, typename V> struct TTypename<TPair<K,V>>`  
_L1219-1223_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <Enumeration E> struct TTypename<TEnumAsByte<E>>`  
_L1226-1230_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <typename... Ts> struct TTypename<TVariant<Ts...>>`  
_L1233-1237_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template<typename T, typename Allocator> struct TTypename<TArray<T, Allocator>>`  
_L1244-1247_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TShortTypename`  
`template<> struct TShortTypename<FDefaultAllocator> : FOmitTypename`  
_L1250-1250_
- inherits: `FOmitTypename`
- L1262 _public member_ `inline static constexpr std::string_view Value = Concat<InlineAllocatorPrefix, HexString<N>>;`

#### struct `PlainProps::TShortTypename`  
`template<> struct TShortTypename<FDefaultSetAllocator> : FOmitTypename`  
_L1252-1252_
- inherits: `FOmitTypename`
- L1262 _public member_ `inline static constexpr std::string_view Value = Concat<InlineAllocatorPrefix, HexString<N>>;`

#### struct `PlainProps::TShortTypename`  
`template<typename T> struct TShortTypename<DefaultKeyFuncs<T, false>> : FOmitTypename`  
_L1254-1254_
- inherits: `FOmitTypename`
- L1262 _public member_ `inline static constexpr std::string_view Value = Concat<InlineAllocatorPrefix, HexString<N>>;`

#### struct `PlainProps::TShortTypename`  
`template<typename K, typename V> struct TShortTypename<TDefaultMapHashableKeyFuncs<K, V, false>> : FOmitTypename`  
_L1256-1256_
- inherits: `FOmitTypename`
- L1262 _public member_ `inline static constexpr std::string_view Value = Concat<InlineAllocatorPrefix, HexString<N>>;`

#### struct `PlainProps::TShortTypename`  
`template<int N> struct TShortTypename<TInlineAllocator<N>>`  
_L1260-1263_
- L1262 _public member_ `inline static constexpr std::string_view Value = Concat<InlineAllocatorPrefix, HexString<N>>;`

#### struct `PlainProps::TShortTypename`  
`template<int N> struct TShortTypename<TInlineSetAllocator<N>> : TShortTypename<TInlineAllocator<N>>`  
_L1266-1266_
- inherits: `TShortTypename<TInlineAllocator<N>>`
- L1262 _public member_ `inline static constexpr std::string_view Value = Concat<InlineAllocatorPrefix, HexString<N>>;`

#### struct `PlainProps::TTypename`  
`template <typename T, typename KeyFuncs, typename SetAllocator> struct TTypename<TSet<T, KeyFuncs, SetAllocator>>`  
_L1269-1272_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TTypename`  
`template <typename K, typename V, typename SetAllocator, typename KeyFuncs> struct TTypename<TMap<K, V, SetAllocator, KeyFuncs>>`  
_L1275-1278_
- L1202 _public member_ `template <> struct TTypename<FName> { inline static constexpr std::string_view DeclName = "Name"`
- L1206 _public member_ `template <> struct TTypename<FText> { inline static constexpr std::string_view DeclName = "Text"`
- L1207 _public member_ `template <> struct TTypename<FIntPoint> { inline static constexpr std::string_view DeclName = "IntPo`
- L1208 _public member_ `template <> struct TTypename<FQuat> { inline static constexpr std::string_view DeclName = "Quat"`
- L1209 _public member_ `template <> struct TTypename<FTransform> { inline static constexpr std::string_view DeclName = "Trans`
- L1210 _public member_ `template <> struct TTypename<FVector> { inline static constexpr std::string_view DeclName = "Vecto`
- L1211 _public member_ `template <> struct TTypename<FVector4> { inline static constexpr std::string_view DeclName = "Vecto`
- L1212 _public member_ `template <> struct TTypename<FGuid> { inline static constexpr std::string_view DeclName = "Guid"`
- L1213 _public member_ `template <> struct TTypename<FColor> { inline static constexpr std::string_view DeclName = "Color`
- L1214 _public member_ `template <> struct TTypename<FLinearColor> { inline static constexpr std::string_view DeclName = "Linea`
- L1215 _public member_ `template <> struct TTypename<FEmptyVariantState> { inline static constexpr std::string_view DeclName = "Empty`
- L1221 _public member_ `inline static constexpr std::string_view DeclName = "Pa`
- L1222 _public typedef_ `using Parameters = std::tuple<K, V>;`
- L1228 _public member_ `inline static constexpr std::string_view DeclName = "En`
- L1229 _public typedef_ `using Parameters = std::tuple<E>;`
- L1235 _public member_ `inline static constexpr std::string_view DeclName = "Va`
- L1236 _public typedef_ `using Parameters = std::tuple<Ts...>;`
- L1246 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeArrayName, ShortTypename<Allocator>>;`
- L1271 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeSetName, ShortTypename<KeyFuncs>, ShortTypename<SetAllocator>>;`
- L1277 _public member_ `inline static constexpr std::string_view RangeBindName = Concat<UeMapName, ShortTypename<SetAllocator>, ShortTypename<KeyFuncs>>;`

#### struct `PlainProps::TRangeBind`  
`template<typename T, typename Allocator> struct TRangeBind<TArray<T, Allocator>>`  
_L1284-1287_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TRangeBind`  
`template<> struct TRangeBind<FString>`  
_L1289-1289_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TRangeBind`  
`template<> struct TRangeBind<FString>`  
_L1290-1290_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TRangeBind`  
`template<> struct TRangeBind<FString>`  
_L1291-1291_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TRangeBind`  
`template<> struct TRangeBind<FString>`  
_L1292-1292_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TRangeBind`  
`template<typename T> struct TRangeBind<TUniquePtr<T>>`  
_L1295-1298_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TRangeBind`  
`template <typename T, typename KeyFuncs, typename SetAllocator> struct TRangeBind<TSet<T, KeyFuncs, SetAllocator>>`  
_L1301-1304_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TCustomDeltaBind`  
`template <typename T, typename KeyFuncs, typename SetAllocator> struct TCustomDeltaBind<TSet<T, KeyFuncs, SetAllocator>>`  
_L1307-1310_
- L1309 _public typedef_ `using Type = UE::TSetDeltaBinding<T, KeyFuncs, SetAllocator>;`
- L1321 _public typedef_ `using Type = UE::TMapDeltaBinding<K, V, SetAllocator, KeyFuncs>;`

#### struct `PlainProps::TRangeBind`  
`template <typename K, typename V, typename SetAllocator, typename KeyFuncs> struct TRangeBind<TMap<K, V, SetAllocator, KeyFuncs>>`  
_L1313-1316_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TCustomDeltaBind`  
`template <typename K, typename V, typename SetAllocator, typename KeyFuncs> struct TCustomDeltaBind<TMap<K, V, SetAllocator, KeyFuncs>>`  
_L1319-1322_
- L1309 _public typedef_ `using Type = UE::TSetDeltaBinding<T, KeyFuncs, SetAllocator>;`
- L1321 _public typedef_ `using Type = UE::TMapDeltaBinding<K, V, SetAllocator, KeyFuncs>;`

#### struct `PlainProps::TRangeBind`  
`template<typename T> struct TRangeBind<TOptional<T>>`  
_L1325-1328_
- L1286 _public typedef_ `using Type = UE::TArrayBinding<T, Allocator>;`
- L1289 _public typedef_ `template<> struct TRangeBind<FString> { using Type = UE::TStringBinding<FString>; };`
- L1297 _public typedef_ `using Type = UE::TUniquePtrBinding<T>;`
- L1303 _public typedef_ `using Type = UE::TSetBinding<T, KeyFuncs, SetAllocator>;`
- L1315 _public typedef_ `using Type = UE::TMapBinding<K, V, SetAllocator, KeyFuncs>;`
- L1327 _public typedef_ `using Type = UE::TOptionalBinding<T>;`

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FQuat> : FRequireAll`  
_L1330-1330_
- inherits: `FRequireAll`

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FQuat> : FRequireAll`  
_L1331-1331_
- inherits: `FRequireAll`

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FQuat> : FRequireAll`  
_L1332-1332_
- inherits: `FRequireAll`

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FQuat> : FRequireAll`  
_L1333-1333_
- inherits: `FRequireAll`

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FVector> : FRequireAll`  
_L1334-1334_
- inherits: `FRequireAll`

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FIntPoint> : FRequireAll`  
_L1335-1335_
- inherits: `FRequireAll`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FTransform>`  
_L1337-1337_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FTransform>`  
_L1338-1338_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FTransform>`  
_L1339-1339_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FTransform>`  
_L1340-1340_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### struct `PlainProps::TOccupancyOf`  
`template<typename K, typename V> struct TOccupancyOf<TPair<K, V>> : FRequireAll`  
_L1344-1344_
- inherits: `FRequireAll`

#### struct `PlainProps::TCustomBind`  
`template<typename K, typename V> requires (!std::is_default_constructible_v<TPair<K,V>>) struct TCustomBind<TPair<K, V>>`  
_L1347-1350_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### struct `PlainProps::TOccupancyOf`  
`template<Enumeration E> struct TOccupancyOf<TEnumAsByte<E>> : FRequireAll`  
_L1353-1353_
- inherits: `FRequireAll`

#### struct `PlainProps::TCustomBind`  
`template<Enumeration E> requires (requires { CttiOfPtr((E*)nullptr); }) struct TCustomBind<TEnumAsByte<E>>`  
_L1356-1359_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### struct `PlainProps::TCustomBind`  
`template<typename... Ts> struct TCustomBind<TVariant<Ts...>>`  
_L1362-1365_
- L1337 _public typedef_ `template<> struct TCustomBind<FTransform> { using Type = UE::FTransformBinding; };`
- L1349 _public typedef_ `using Type = UE::TPairBinding<K, V>;`
- L1358 _public typedef_ `using Type = UE::TAuxEnumAsByteBinding<E>;`
- L1364 _public typedef_ `using Type = UE::TVariantBinding<Ts...>;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Verse`
- L21 _typedef_ `using FVerseString = Verse::FNativeString;`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Math` (scope `UE`)
- L40 _namespace_ `namespace PlainProps`
- L40 _namespace_ `namespace UE` (scope `PlainProps`)
- L59 _function_ `[[nodiscard]] friend inline uint32 GetTypeHash(FSensitiveName Name)` (scope `PlainProps::UE`)
- L238 _namespace_ `namespace PlainProps`
- L238 _namespace_ `namespace UE` (scope `PlainProps`)
- L1195 _prototype_ `FEnumId DeclarePixelFormat();` (scope `PlainProps::UE`)
- L1199 _namespace_ `namespace PlainProps`
- L1239 _variable_ `inline static constexpr std::string_view UeArrayName = "Ar` (scope `PlainProps`)
- L1240 _variable_ `inline static constexpr std::string_view UeSetName = "Se` (scope `PlainProps`)
- L1241 _variable_ `inline static constexpr std::string_view UeMapName = "Ma` (scope `PlainProps`)
- L1258 _variable_ `inline constexpr std::string_view InlineAllocatorPrefix = "In` (scope `PlainProps`)
- L1281 _prototype_ `template<> void AppendString(FUtf8StringBuilderBase& Out, const UE::FSensitiveName& Name);` (scope `PlainProps`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsUpgrade.h` (Public)


#### enum `PlainProps::Upgrade::EAccess`  
`enum class EAccess : uint8`  
_L77-77_
- desc: todo: could allow leaving taken members too. could have another flag to leave old member
- L77 _public enumerator_ `enum class EAccess : uint8 { WholeValue, AllMembers, SomeMembers }; struct FInnermostHandle { FOptionalInnerId Id; uint16 Version; uint8 Slice; EAccess Access;` — todo: could allow leaving taken members too. could have another flag to leave old member
- L77 _public enumerator_ `enum class EAccess : uint8 { WholeValue, AllMembers, SomeMembers }; struct FInnermostHandle { FOptionalInnerId Id; uint16 Version; uint8 Slice; EAccess Access;` — todo: could allow leaving taken members too. could have another flag to leave old member
- L77 _public enumerator_ `enum class EAccess : uint8 { WholeValue, AllMembers, SomeMembers }; struct FInnermostHandle { FOptionalInnerId Id; uint16 Version; uint8 Slice; EAccess Access;` — todo: could allow leaving taken members too. could have another flag to leave old member

#### struct `PlainProps::Upgrade::FInnermostHandle`  
`struct FInnermostHandle`  
_L79-85_
- L81 _public member_ `FOptionalInnerId Id;`
- L82 _public member_ `uint16 Version;`
- L83 _public member_ `uint8 Slice;`
- L84 _public member_ `EAccess Access;`

#### struct `PlainProps::Upgrade::FParameter`  
`struct FParameter`  
_L87-98_
- L89 _public member_ `const char* Name;`
- L90 _public member_ `uint32 NameLen;`
- L91 _public member_ `uint8 NumRanges;`
- L92 _public member_ `bool bOptional;`
- L93 _public member_ `FInnermostType InnermostType;`
- L94 _public member_ `FInnermostHandle InnermostHandle;`
- L96 _public function_ `constexpr FParameter operator~()`
- L97 _public function_ `constexpr FParameter Range(uint8 Num = 1)`

#### struct `PlainProps::Upgrade::FMemberLiteral`  
`struct FMemberLiteral`  
_L170-179_
- L172 _public member_ `const char* Str;`
- L173 _public member_ `std::size_t Len;`
- L175 _public function_ `inline constexpr FParameter MakeParam(uint8 NumRanges, FInnermostType InnermostType, FInnermostHandle InnermostHandle) const`

#### struct `PlainProps::Upgrade::FOpaqueEnum`  
`struct FOpaqueEnum`  
_L183-187_
- L185 _public member_ `FEnumId Id;`
- L186 _public member_ `bool bFlagMode;`

#### struct `PlainProps::Upgrade::FEnumeratorNames`  
`struct FEnumeratorNames`  
_L189-193_
- L191 _public member_ `FEnumId Id;`
- L192 _public member_ `uint8 Slice;`

#### struct `PlainProps::Upgrade::FEnumFlagNames`  
`struct FEnumFlagNames`  
_L195-199_
- L197 _public member_ `FEnumId Id;`
- L198 _public member_ `uint8 Slice;`

#### struct `PlainProps::Upgrade::FEnumLiteral`  
`struct FEnumLiteral : FMemberLiteral`  
_L201-219_
- inherits: `FMemberLiteral`
- L203 _public member_ `uint8 NumRanges = 0;`
- L205 _public function_ `inline FParameter operator()(FOpaqueEnum Enum) const`
- L210 _public function_ `inline FParameter operator()(FEnumeratorNames Enumerators, EAccess Access = EAccess::AllMembers) const`
- L215 _public function_ `inline FParameter operator()(FEnumFlagNames Flags, EAccess Access = EAccess::AllMembers) const`

#### struct `PlainProps::Upgrade::FStructMemberNames`  
`struct FStructMemberNames`  
_L225-229_
- L227 _public member_ `FStructId Id;`
- L228 _public member_ `uint8 Slice;`

#### struct `PlainProps::Upgrade::FStructLiteral`  
`struct FStructLiteral : FMemberLiteral`  
_L231-249_
- inherits: `FMemberLiteral`
- L233 _public member_ `uint8 NumRanges = 0;`
- L235 _public function_ `inline FParameter operator()(FStructId Id, uint16 Version = 0) const`
- L240 _public function_ `inline FParameter operator()(FStructMemberNames Members, uint16 Version = 0, EAccess Access = EAccess::AllMembers) const`
- L245 _public function_ `inline FParameter Any() const`

#### class `PlainProps::Upgrade::FContext`  
`class FContext`  
_L266-272_
- desc: Will allow logging errors/warnings, wont provide any global access to outside world Might also be used to allocate new out ranges during op execution
- L269 _private member_ `FScratchAllocator& Scratch;`
- L271 _public function_ `explicit FContext(FScratchAllocator& In) : Scratch(In)`

#### struct `PlainProps::Upgrade::FItems`  
`struct FItems`  
_L276-281_
- L278 _public member_ `FLooseType Type;`
- L279 _public member_ `FLooseNestedRange Value;`
- L280 _public member_ `uint16 NumNamed;`

#### struct `PlainProps::Upgrade::TInItems`  
`template<typename T, uint8 N = 1> struct TInItems : protected FItems`  
_L284-294_
- inherits: `FItems`
- L286 _public function_ `TInItems(FItems Items) : FItems(Items)`
- L287 _public typedef_ `using Iterator = TInIt<T, N>::Type;`
- L290 _public function_ `uint64 Num() const`
- L291 _public function_ `auto&& operator[](uint64 Idx) const`
- L292 _public function_ `Iterator begin() const`
- L293 _public function_ `Iterator end() const`

#### struct `PlainProps::Upgrade::FOutItems`  
`struct FOutItems : FItems`  
_L296-299_
- inherits: `FItems`
- L298 _public member_ `FLooseMember& Owner;` — Only needed to RecordDynamicType

#### struct `PlainProps::Upgrade::TOutItems`  
`template<typename T, uint8 N = 1> struct TOutItems : protected FOutItems`  
_L302-312_
- inherits: `FOutItems`
- L304 _public function_ `TOutItems(FOutItems Items) : FOutItems(Items)`
- L305 _public typedef_ `using Iterator = TOutIt<T,N>::Type;`
- L306 _public typedef_ `using DerefType = decltype(**((Iterator*)nullptr));`
- L308 _public function_ `uint64 Num() const`
- L309 _public function_ `DerefType operator[](uint64 Idx)`
- L310 _public function_ `Iterator begin() const`
- L311 _public function_ `Iterator end() const`
- L907 _public function_ `template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>` — Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L908 _public function_ ``

#### class `PlainProps::Upgrade::TFiller`  
`template<typename T, uint8 N = 1> class TFiller : protected TOutItems<T, N>`  
_L316-345_
- inherits: `TOutItems<T,N>`
- desc: Helps fill TOutItems and check that all items are assigned
- L318 _private typedef_ `using Super = TOutItems<T, N>;`
- L319 _private member_ `uint64 Pos = 0;`
- L322 _public function_ `TFiller(Super Items) : Super(Items)`
- L323 _public function_ `~TFiller()`
- L326 _public function_ `template<typename InT> TFiller& operator<<(InT InItem)`
- L333 _public function_ `template<typename InT> TFiller& operator<<(TInItems<InT, N> Items)`

#### struct `PlainProps::Upgrade::FInRange`  
`struct FInRange`  
_L349-356_
- L351 _public member_ `FLooseType Type;`
- L352 _public member_ `FLooseValue Value;`
- L353 _public member_ `uint16 NumNamed;`
- L355 _public function_ `FItems Items() const`

#### struct `PlainProps::Upgrade::TInRange`  
`template<typename T, uint8 N = 1> struct TInRange : protected FInRange`  
_L366-372_
- inherits: `FInRange`
- L369 _public function_ `TInRange(FLooseMember I, uint16 NumNamed) : FInRange({I.GetType(), I.GetValue(), NumNamed})`
- L370 _public function_ `uint64 Num() const`
- L371 _public function_ `TInItems<T, N> Items() const`

#### struct `PlainProps::Upgrade::TOptionalInRange`  
`template<typename T, uint8 N = 1> struct TOptionalInRange : protected FInRange`  
_L375-382_
- inherits: `FInRange`
- L378 _public function_ `TOptionalInRange(FLooseMember I, uint16 NumNamed) : FInRange({I.GetType(), I.GetValue(), NumNamed})`
- L379 _public function_ `explicit operator bool()`
- L380 _public function_ `uint64 Num() const`
- L381 _public function_ `TInItems<T, N> Items() const`

#### struct `PlainProps::Upgrade::FOutRange`  
`struct FOutRange`  
_L386-409_
- L388 _public member_ `FLooseMember& Out;`
- L389 _public member_ `const uint16 NumNamed;`
- L391 _public function_ `FOutRange(FLooseMember& O, uint16 N) : Out(O), NumNamed(N)`
- L393 _public prototype_ `void Set(const FInRange& In);`
- L394 _public prototype_ `void Set(FLooseNestedRange Value);`
- L395 _public prototype_ `FRangeData NewNested(uint64 Num, FContext Ctx) const;`
- L396 _public prototype_ `FRangeData NewStructs(uint64 Num, FContext Ctx) const;`
- L397 _public prototype_ `FRangeData NewMembers(uint64 Num, FContext Ctx) const;`
- L398 _public prototype_ `FRangeData NewEnums(uint64 Num, FContext Ctx) const;`
- L399 _public prototype_ `FRangeData NewEnumerators(uint64 Num, FContext Ctx) const;`
- L400 _public prototype_ `FRangeData NewFlags(uint64 Num, FContext Ctx) const;`
- L401 _public prototype_ `FRangeData NewBools(uint64 Num, FContext Ctx) const;`
- L402 _public prototype_ `FRangeData NewArithmetics(uint64 Num, FContext Ctx, uint32 SizeOf) const;`
- L403 _public prototype_ `template<typename T> FRangeData NewItems(uint64 Num, FContext Ctx) const;`
- L404 _public function_ `template<typename T> FRangeData NewItems(uint64 Num, FContext Ctx) const;`
- L412 _function_ `template<typename T> FRangeData FOutRange::NewItems(uint64 Num, FContext Ctx) const`

#### struct `PlainProps::Upgrade::TOutRange`  
`template<typename T, uint8 N> struct TOutRange : protected FOutRange`  
_L426-434_
- inherits: `FOutRange`
- L428 _public function_ `TOutRange(FLooseMember& O, uint16 NumNamed) : FOutRange(O, NumNamed)`
- L430 _public function_ `void operator=(const TInRange<T, N>& In)`
- L431 _public function_ `void operator=(TInItems<T, N> Items)`
- L432 _public function_ `TOutItems<T, N> New(uint64 Num, FContext Ctx) requires (N>1)`
- L433 _public function_ `TOutItems<T, N> New(uint64 Num, FContext Ctx) requires (N==1)`

#### class `PlainProps::Upgrade::FIn`  
`class FIn : protected FLooseMember`  
_L438-500_
- inherits: `FLooseMember`
- L442 _public function_ `FIn(const FLooseMember& In) : FLooseMember(In.GetType(), In.GetValue())`
- L445 _public function_ `bool Bool() const`
- L446 _public function_ `int32 S32() const`
- L447 _public function_ `uint32 U32() const`
- L448 _public function_ `uint64 U64() const`
- L449 _public function_ `float F32() const`
- L450 _public function_ `char8_t Char() const`
- L451 _public function_ `char8_t C8() const`
- L453 _public prototype_ `FInStruct Struct() const;`
- L454 _public prototype_ `FInAny StructAny() const;`
- L455 _public prototype_ `FInMembers StructMembers() const;`
- L457 _public prototype_ `FInEnum Enum() const;`
- L458 _public prototype_ `FInEnumerator Enumerator() const;`
- L459 _public prototype_ `FInFlags EnumFlags() const;`
- L462 _public function_ `template<typename T, uint8 N = 1> TInRange<T, N> Range(uint16 NumNamed = 0) const`
- L463 _public function_ `TInRange<bool> Bools() const`
- L464 _public function_ `TInRange<uint8> U8s() const`
- L465 _public function_ `TInRange<int32> S32s() const`
- L466 _public function_ `TInRange<float> F32s() const`
- L467 _public function_ `TInRange<char8_t> C8s() const`
- L468 _public function_ `TInRange<char8_t> Str() const`
- L469 _public function_ `TInRange<FInStruct> Structs() const`
- L470 _public function_ `TInRange<FInMembers> StructsMembers(uint16 NumNamed) const`
- L471 _public function_ `TInRange<FInEnum> Enums() const`
- L472 _public function_ `TInRange<FInEnumerator> Enumerators(uint16 NumNamed) const`
- L473 _public function_ `TInRange<FInFlags> EnumsFlags(uint16 NumNamed) const`
- L475 _public function_ `TOptional<bool> OptBool() const`
- L476 _public function_ `TOptional<int32> OptS32() const`
- L477 _public function_ `TOptional<uint32> OptU32() const`
- L478 _public function_ `TOptional<uint64> OptU64() const`
- L479 _public function_ `TOptional<float> OptF32() const`
- L480 _public prototype_ `FInStruct OptStruct() const;`
- L484 _private function_ `template<Arithmetic T> T As() const`
- L492 _private function_ `template<Arithmetic T> TOptional<T> AsOpt() const`

#### struct `PlainProps::Upgrade::FInStruct`  
`struct FInStruct : protected FLooseMember`  
_L503-507_
- inherits: `FLooseMember`
- desc: Opaque struct value, assignable to a type-matching FOutStruct

#### struct `PlainProps::Upgrade::FInAny`  
`struct FInAny : protected FLooseMember`  
_L509-513_
- inherits: `FLooseMember`

#### struct `PlainProps::Upgrade::FInMembers`  
`struct FInMembers : protected FLooseMember`  
_L515-521_
- inherits: `FLooseMember`
- L520 _public function_ `FIn operator[](uint32 Idx) const`

#### class `PlainProps::Upgrade::FInEnum`  
`class FInEnum`  
_L524-531_
- desc: Opaque enum value, assignable to a type-matching FOutEnum
- L527 _private member_ `FLooseType Type;`
- L528 _private member_ `FEnumeratorData Value;`
- L530 _public function_ `FInEnum(FLooseType T, FEnumeratorData V) : Type(T), Value(V)`

#### class `PlainProps::Upgrade::FInEnumerator`  
`class FInEnumerator`  
_L537-543_
- desc: Enum value represented as enumerator index in NameEnumerators() order * Conceptually a string * Not assignable to FOutEnumerator, which might use different NameEnumerators() indices * Not convertible to FInEnum nor assignable to FOutEnum either
- L539 _private member_ `FEnumeratorIndex Name;`
- L541 _public function_ `explicit FInEnumerator(FEnumeratorIndex N, uint16 Max) : Name(N)`
- L542 _public function_ `uint16 GetIndex() const`

#### class `PlainProps::Upgrade::FInFlags`  
`class FInFlags`  
_L548-556_
- desc: Bitset of enumerator indices in NameEnumFlags() order * Conceptually a string set * Not assignable to FOutEnumerator, which might use different NameEnumerators() indices
- L550 _private member_ `FEnumeratorIndexSet Flags;`
- L551 _private member_ `const uint32 Max;`
- L553 _public function_ `explicit FInFlags(FEnumeratorIndexSet InFlags, uint32 NumNamedFlags) : Flags(InFlags), Max(NumNamedFlags)`
- L554 _public prototype_ `uint64 GetIndices() const;`
- L555 _public prototype_ `bool IsSet(uint32 Index) const;`

#### class `PlainProps::Upgrade::TOut`  
`template <Arithmetic T> class TOut`  
_L561-583_
- L563 _private member_ `FLooseValue& Out;`
- L565 _public function_ `TOut(FLooseType Type, FLooseValue& Value UE_LIFETIMEBOUND) : Out(Value)`
- L571 _public function_ `void operator=(T In)`
- L578 _public function_ `void operator=(TOptional<T> In)`

#### class `PlainProps::Upgrade::FOut`  
`class FOut : protected FLooseMember`  
_L585-628_
- inherits: `FLooseMember`
- L588 _public prototype_ `FOut(FOut&&) = default;`
- L589 _public prototype_ `FOut(const FOut&) = delete;`
- L590 _public prototype_ `FOut(FOutParameter Parameter);`
- L591 _public prototype_ `FOut(FOutParameter Parameter, FOut* StructMembers);`
- L592 _public prototype_ `FOut& operator=(FOut&&) = default;`
- L593 _public prototype_ `FOut& operator=(const FOut&) = delete;`
- L595 _public function_ `TOut<bool> Bool()`
- L596 _public function_ `TOut<int32> S32()`
- L597 _public function_ `TOut<uint32> U32()`
- L598 _public function_ `TOut<uint64> U64()`
- L599 _public function_ `TOut<float> F32()`
- L600 _public function_ `TOut<char8_t> Char()`
- L601 _public function_ `TOut<char8_t> C8()`
- L603 _public prototype_ `FOutStruct Struct();`
- L604 _public prototype_ `FOutAny StructAny();`
- L605 _public prototype_ `FOutMembers StructMembers();`
- L607 _public prototype_ `FOutEnum Enum();`
- L608 _public prototype_ `FOutEnumerator Enumerator();`
- L609 _public prototype_ `FOutFlags EnumFlags();`
- L612 _public function_ `template<typename T, uint8 N = 1> TOutRange<T, N> Range(uint16 NumNamed = 0)`
- L614 _public function_ `TOutRange<FOutBoolItem> Bools()`
- L615 _public function_ `TOutRange<uint8> U8s()`
- L616 _public function_ `TOutRange<int32> S32s()`
- L617 _public function_ `TOutRange<float> F32s()`
- L618 _public function_ `TOutRange<char8_t> C8s()`
- L619 _public function_ `TOutRange<char8_t> Str()`
- L620 _public function_ `TOutRange<FOutStruct> Structs()`
- L621 _public function_ `TOutRange<FOutAny> StructsAny()`
- L622 _public function_ `TOutRange<FOutMembers> StructsMembers(uint16 NumNamed)`
- L623 _public function_ `TOutRange<FOutEnumItem> Enums()`
- L624 _public function_ `TOutRange<FOutEnumeratorItem> Enumerators(uint16 NumNamed)`
- L625 _public function_ `TOutRange<FOutFlagsItem> EnumsFlags(uint16 NumNamed)`

#### struct `PlainProps::Upgrade::FOutMember`  
`struct FOutMember`  
_L630-634_
- L632 _public member_ `const FLooseType Type;`
- L633 _public member_ `FLooseValue& Value;`

#### struct `PlainProps::Upgrade::FOutStruct`  
`struct FOutStruct : protected FOutMember`  
_L636-640_
- inherits: `FOutMember`
- L638 _public function_ `FOutStruct(FLooseType Type, FLooseValue& Out) : FOutMember`
- L639 _public prototype_ `void operator=(FInStruct In);`

#### class `PlainProps::Upgrade::FOutAny`  
`class FOutAny : protected FOutMember`  
_L642-648_
- inherits: `FOutMember`
- L644 _private member_ `FLooseMember& Owner;`
- L646 _public function_ `FOutAny(FLooseType Type, FLooseValue& Out, FLooseMember& InOwner) : FOutMember`
- L647 _public prototype_ `void operator=(FInStruct In);`

#### struct `PlainProps::Upgrade::FOutMembers`  
`struct FOutMembers : protected FOutMember`  
_L650-654_
- inherits: `FOutMember`
- L652 _public function_ `FOutMembers(FLooseType Type, FLooseValue& Out) : FOutMember`
- L653 _public function_ `FOut& operator[](uint32 Idx)`

#### struct `PlainProps::Upgrade::FOutEnum`  
`struct FOutEnum : protected FOutMember`  
_L656-660_
- inherits: `FOutMember`
- L658 _public function_ `FOutEnum(FLooseType Type, FLooseValue& Out) : FOutMember`
- L659 _public prototype_ `void operator=(FInEnum In);`

#### struct `PlainProps::Upgrade::FOutEnumerator`  
`struct FOutEnumerator : protected FOutMember`  
_L662-666_
- inherits: `FOutMember`
- L664 _public function_ `FOutEnumerator(FLooseType Type, FLooseValue& Out) : FOutMember`
- L665 _public prototype_ `void operator=(uint16 Index);`

#### class `PlainProps::Upgrade::FOutFlag`  
`class FOutFlag`  
_L668-676_
- L670 _private member_ `FLooseValue& Out;`
- L671 _private member_ `const uint32 Idx;`
- L673 _public function_ `FOutFlag(FLooseValue& O, uint32 I) : Out(O), Idx(I)`
- L674 _public prototype_ `void operator=(bool bValue);`
- L675 _public prototype_ `void operator=(TOptional<bool> bValue);`

#### struct `PlainProps::Upgrade::FOutFlags`  
`struct FOutFlags : protected FOutMember`  
_L678-685_
- inherits: `FOutMember`
- L680 _public function_ `FOutFlags(FLooseType Type, FLooseValue& Out) : FOutMember`
- L682 _public function_ `FOutFlag operator[](uint32 Idx)` — @param Index in NameFlags order
- L684 _public prototype_ `void operator=(uint64 Indices);` — @param Indices bitset in NameFlags order

#### class `PlainProps::Upgrade::FOutBoolItem`  
`class FOutBoolItem`  
_L689-696_
- L691 _private member_ `uint8& Out;`
- L692 _private member_ `const uint8 Mask;`
- L694 _public function_ `FOutBoolItem(uint8& Byte, uint8 InMask) : Out(Byte), Mask(InMask)`
- L695 _public prototype_ `void operator=(bool bValue);`

#### class `PlainProps::Upgrade::FOutEnumItem`  
`class FOutEnumItem`  
_L698-705_
- L700 _private member_ `FEnumeratorData& Out;`
- L701 _private member_ `const FLooseType Type;`
- L703 _public function_ `FOutEnumItem(FLooseType T, FEnumeratorData& D) : Out(D), Type(T)`
- L704 _public prototype_ `void operator=(FInEnum In);`

#### class `PlainProps::Upgrade::FOutEnumeratorItem`  
`class FOutEnumeratorItem`  
_L707-714_
- L709 _private member_ `FEnumeratorIndex& Out;`
- L710 _private member_ `const uint32 Max;`
- L712 _public function_ `FOutEnumeratorItem(FEnumeratorIndex& Name, uint32 InMax) : Out(Name), Max(InMax)`
- L713 _public prototype_ `void operator=(uint16 Index);`

#### class `PlainProps::Upgrade::FOutFlagItem`  
`class FOutFlagItem`  
_L716-723_
- L718 _private member_ `FEnumeratorIndexSet& Out;`
- L719 _private member_ `const uint32 Idx;`
- L721 _public function_ `FOutFlagItem(FEnumeratorIndexSet& O, uint32 InIdx) : Out(O), Idx(InIdx)`
- L722 _public prototype_ `void operator=(bool bValue);`

#### class `PlainProps::Upgrade::FOutFlagsItem`  
`class FOutFlagsItem`  
_L725-735_
- L727 _private member_ `FEnumeratorIndexSet& Out;`
- L728 _private member_ `const uint32 Max;`
- L730 _public function_ `FOutFlagsItem(FEnumeratorIndexSet& Flags, uint32 InMax) : Out(Flags), Max(InMax)`
- L732 _public function_ `FOutFlagItem operator[](uint32 Index)` — @param Index in NameFlags order
- L734 _public prototype_ `void operator=(uint64 Indices);` — @param Indices bitset in NameFlags order

#### struct `PlainProps::Upgrade::FInBoolIt`  
`struct FInBoolIt : public FBoolRangeIterator`  
_L739-742_
- inherits: `FBoolRangeIterator`
- L741 _public function_ `FInBoolIt(FItems Items, uint64 Idx) : FBoolRangeIterator(static_cast<const uint8*>(Items.Value.Data.Arithmetics.Source), Idx)`

#### class `PlainProps::Upgrade::FOutBoolIt`  
`class FOutBoolIt`  
_L744-759_
- L746 _private member_ `uint8* Byte;`
- L747 _private member_ `uint8 Mask;`
- L748 _private prototype_ `void Increment();`
- L750 _public function_ `FOutBoolIt(FItems Items, uint64 Idx) : Byte(static_cast<uint8*>(Items.Value.Data.Arithmetics.Loose) + Idx / 8) , Mask(1u << (Idx % 8))`
- L755 _public function_ `FOutBoolItem operator*() const`
- L756 _public prototype_ `bool operator==(const FOutBoolIt& Rhs) const = default;`
- L757 _public prototype_ `bool operator!=(const FOutBoolIt& Rhs) const = default;`
- L758 _public function_ `FOutBoolIt& operator++()`

#### class `PlainProps::Upgrade::TInArithmeticIt`  
`template<Arithmetic T> class TInArithmeticIt`  
_L762-770_
- L764 _private member_ `const T* Ptr;`
- L766 _public function_ `TInArithmeticIt(FItems Items, uint64 Idx) : Ptr(static_cast<const T*>(Items.Value.Data.Arithmetics.Source) + Idx)`
- L767 _public function_ `T operator*()`
- L768 _public function_ `TInArithmeticIt& operator++()`
- L769 _public function_ `bool operator!=(TInArithmeticIt O) const`

#### class `PlainProps::Upgrade::TOutArithmeticIt`  
`template<Arithmetic T> class TOutArithmeticIt`  
_L773-781_
- L775 _private member_ `T* Ptr;`
- L777 _public function_ `TOutArithmeticIt(FItems Items, uint64 Idx) : Ptr(static_cast<T*>(Items.Value.Data.Arithmetics.Loose) + Idx)`
- L778 _public function_ `T& operator*()`
- L779 _public function_ `TOutArithmeticIt& operator++()`
- L780 _public function_ `bool operator!=(TOutArithmeticIt O) const`

#### class `PlainProps::Upgrade::TItemIt`  
`template<typename ValueType> class TItemIt`  
_L784-795_
- L787 _public function_ `TItemIt& operator++()`
- L788 _public function_ `bool operator!=(TItemIt O) const`
- L790 _protected function_ `TItemIt(FItems Items, ValueType* Value) : Type(Items.Type), NumNamed(Items.NumNamed), It(Value)`
- L792 _protected member_ `const FLooseType Type;`
- L793 _protected member_ `uint16 NumNamed;`
- L794 _protected member_ `ValueType* It;`

#### struct `PlainProps::Upgrade::FInStructIt`  
`struct FInStructIt : TItemIt<const FLooseValue>`  
_L797-801_
- inherits: `TItemIt<constFLooseValue>`
- L799 _public function_ `FInStructIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Structs.Loose + Idx)`
- L800 _public function_ `FInStruct operator*() const`

#### struct `PlainProps::Upgrade::FOutStructIt`  
`struct FOutStructIt : TItemIt<FLooseValue>`  
_L803-807_
- inherits: `TItemIt<FLooseValue>`
- L805 _public function_ `FOutStructIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Structs.Loose + Idx)`
- L806 _public function_ `FOutStruct operator*() const`

#### struct `PlainProps::Upgrade::FInAnyIt`  
`struct FInAnyIt : TItemIt<const FLooseValue>`  
_L809-813_
- inherits: `TItemIt<constFLooseValue>`
- L811 _public function_ `FInAnyIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Structs.Loose + Idx)`
- L812 _public function_ `FInAny operator*() const`

#### struct `PlainProps::Upgrade::FOutAnyIt`  
`struct FOutAnyIt : TItemIt<FLooseValue>`  
_L815-821_
- inherits: `TItemIt<FLooseValue>`
- L817 _public function_ `FOutAnyIt(FOutItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Structs.Loose + Idx), Owner(Items.Owner)`
- L818 _public function_ `FOutAny operator*() const`
- L820 _private member_ `FLooseMember& Owner;`

#### struct `PlainProps::Upgrade::FInMemberIt`  
`struct FInMemberIt : TItemIt<const FLooseValue>`  
_L823-827_
- inherits: `TItemIt<constFLooseValue>`
- L825 _public function_ `FInMemberIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Structs.Loose + Idx)`
- L826 _public function_ `FInMembers operator*() const`

#### struct `PlainProps::Upgrade::FOutMemberIt`  
`struct FOutMemberIt : TItemIt<FLooseValue>`  
_L829-833_
- inherits: `TItemIt<FLooseValue>`
- L831 _public function_ `FOutMemberIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Structs.Loose + Idx)`
- L832 _public function_ `FOutMembers operator*() const`

#### struct `PlainProps::Upgrade::FInEnumIt`  
`struct FInEnumIt : TItemIt<const FEnumLooseData>`  
_L835-839_
- inherits: `TItemIt<constFEnumLooseData>`
- L837 _public function_ `FInEnumIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Enums.Loose + Idx)`
- L838 _public function_ `FInEnum operator*() const`

#### struct `PlainProps::Upgrade::FOutEnumIt`  
`struct FOutEnumIt : TItemIt<FEnumLooseData>`  
_L841-845_
- inherits: `TItemIt<FEnumLooseData>`
- L843 _public function_ `FOutEnumIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Enums.Loose + Idx)`
- L844 _public function_ `FOutEnumItem operator*() const`

#### struct `PlainProps::Upgrade::FInEnumeratorIt`  
`struct FInEnumeratorIt : TItemIt<const FEnumLooseData>`  
_L847-851_
- inherits: `TItemIt<constFEnumLooseData>`
- L849 _public function_ `FInEnumeratorIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Enums.Loose + Idx)`
- L850 _public function_ `FInEnumerator operator*() const`

#### struct `PlainProps::Upgrade::FOutEnumeratorIt`  
`struct FOutEnumeratorIt : TItemIt<FEnumLooseData>`  
_L853-857_
- inherits: `TItemIt<FEnumLooseData>`
- L855 _public function_ `FOutEnumeratorIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Enums.Loose + Idx)`
- L856 _public function_ `FOutEnumeratorItem operator*() const`

#### struct `PlainProps::Upgrade::FInFlagsIt`  
`struct FInFlagsIt : TItemIt<const FEnumLooseData>`  
_L859-863_
- inherits: `TItemIt<constFEnumLooseData>`
- L861 _public function_ `FInFlagsIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Enums.Loose + Idx)`
- L862 _public function_ `FInFlags operator*() const`

#### struct `PlainProps::Upgrade::FOutFlagsIt`  
`struct FOutFlagsIt : TItemIt<FEnumLooseData>`  
_L865-869_
- inherits: `TItemIt<FEnumLooseData>`
- L867 _public function_ `FOutFlagsIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Enums.Loose + Idx)`
- L868 _public function_ `FOutFlagsItem operator*() const`

#### struct `PlainProps::Upgrade::TInNestedRangeIt`  
`template<typename T, uint8 N> struct TInNestedRangeIt : TItemIt<const FLooseNestedRange>`  
_L872-876_
- inherits: `TItemIt<constFLooseNestedRange>`
- L874 _public function_ `TInNestedRangeIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Ranges + Idx)`
- L875 _public function_ `TInItems<T, N-1> operator*() const`

#### struct `PlainProps::Upgrade::TOutNestedRangeIt`  
`template<typename T, uint8 N> struct TOutNestedRangeIt : TItemIt<FLooseNestedRange>`  
_L879-883_
- inherits: `TItemIt<FLooseNestedRange>`
- L881 _public function_ `TOutNestedRangeIt(FItems Items, uint64 Idx) : TItemIt(Items, Items.Value.Data.Ranges + Idx)`
- L882 _public function_ `TOutItems<T, N-1> operator*() const`

#### struct `PlainProps::Upgrade::TInIt`  
`template<typename T, uint8 N> requires(N==1) struct TInIt<T,N>`  
_L885-885_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<typename T, uint8 N> requires(N==1) struct TInIt<T,N>`  
_L886-886_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<typename T, uint8 N> requires(N==1) struct TInIt<T,N>`  
_L887-887_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<typename T, uint8 N> requires(N==1) struct TInIt<T,N>`  
_L888-888_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N>`  
_L889-889_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<typename T, uint8 N> requires(N>1) struct TInIt<T,N>`  
_L890-890_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N>`  
_L891-891_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<Arithmetic T> struct TInIt<T,1>`  
_L892-892_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<Arithmetic T> struct TOutIt<T,1>`  
_L893-893_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<> struct TInIt<bool,1>`  
_L894-894_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<> struct TOutIt<FOutBoolItem,1>`  
_L895-895_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<> struct TInIt<FInStruct,1>`  
_L896-896_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<> struct TOutIt<FOutStruct,1>`  
_L897-897_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<> struct TInIt<FInAny,1>`  
_L898-898_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<> struct TOutIt<FOutAny,1>`  
_L899-899_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<> struct TInIt<FInMembers,1>`  
_L900-900_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<> struct TOutIt<FInMembers,1>`  
_L901-901_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<> struct TInIt<FInEnum,1>`  
_L902-902_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TInIt`  
`template<> struct TOutIt<FOutEnumItem,1>`  
_L903-903_
- L887 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L889 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TOutIt<T,N> { static_assert(!sizeof(T), "Illega`
- L891 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TOutIt<T,N> { using Type = TOutNestedRangeIt<T,N>; };`
- L893 _public typedef_ `template<Arithmetic T> struct TOutIt<T,1> { using Type = TOutArithmeticIt<T>; };`
- L895 _public typedef_ `template<> struct TOutIt<FOutBoolItem,1> { using Type = FOutBoolIt; };`
- L897 _public typedef_ `template<> struct TOutIt<FOutStruct,1> { using Type = FOutStructIt; };`
- L899 _public typedef_ `template<> struct TOutIt<FOutAny,1> { using Type = FOutAnyIt; };`
- L901 _public typedef_ `template<> struct TOutIt<FInMembers,1> { using Type = FOutMemberIt; };`
- L903 _public typedef_ `template<> struct TOutIt<FOutEnumItem,1> { using Type = FOutEnumIt; };`

#### struct `PlainProps::Upgrade::TOutIt`  
`template<> struct TInIt<FInEnumerator,1>`  
_L904-904_
- L888 _public typedef_ `template<typename T, uint8 N> requires(N==1) struct TInIt<T,N> { static_assert(!sizeof(T), "Illega`
- L890 _public typedef_ `template<typename T, uint8 N> requires(N>1) struct TInIt<T,N> { using Type = TInNestedRangeIt<T,N>; };`
- L892 _public typedef_ `template<Arithmetic T> struct TInIt<T,1> { using Type = TInArithmeticIt<T>; };`
- L894 _public typedef_ `template<> struct TInIt<bool,1> { using Type = FInBoolIt; };`
- L896 _public typedef_ `template<> struct TInIt<FInStruct,1> { using Type = FInStructIt; };`
- L898 _public typedef_ `template<> struct TInIt<FInAny,1> { using Type = FInAnyIt; };`
- L900 _public typedef_ `template<> struct TInIt<FInMembers,1> { using Type = FInMemberIt; };`
- L902 _public typedef_ `template<> struct TInIt<FInEnum,1> { using Type = FInEnumIt; };`
- L904 _public typedef_ `template<> struct TInIt<FInEnumerator,1> { using Type = FInEnumeratorIt; };`

#### struct `PlainProps::Upgrade::TOutItems`  
`template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>`  
_L907-907_
- inherits: `TOutItems<FOutBoolItem>`
- desc: Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L304 _public function_ `TOutItems(FOutItems Items) : FOutItems(Items)`
- L305 _public typedef_ `using Iterator = TOutIt<T,N>::Type;`
- L306 _public typedef_ `using DerefType = decltype(**((Iterator*)nullptr));`
- L308 _public function_ `uint64 Num() const`
- L309 _public function_ `DerefType operator[](uint64 Idx)`
- L310 _public function_ `Iterator begin() const`
- L311 _public function_ `Iterator end() const`
- L907 _public function_ `template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>` — Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L908 _public function_ ``

#### struct `PlainProps::Upgrade::TOutItems`  
``  
_L908-908_
- inherits: `TOutItems<FOutEnumItem>`
- L304 _public function_ `TOutItems(FOutItems Items) : FOutItems(Items)`
- L305 _public typedef_ `using Iterator = TOutIt<T,N>::Type;`
- L306 _public typedef_ `using DerefType = decltype(**((Iterator*)nullptr));`
- L308 _public function_ `uint64 Num() const`
- L309 _public function_ `DerefType operator[](uint64 Idx)`
- L310 _public function_ `Iterator begin() const`
- L311 _public function_ `Iterator end() const`
- L907 _public function_ `template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>` — Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L908 _public function_ ``

#### struct `PlainProps::Upgrade::TOutItems`  
``  
_L909-909_
- inherits: `TOutItems<FOutEnumeratorItem>`
- L304 _public function_ `TOutItems(FOutItems Items) : FOutItems(Items)`
- L305 _public typedef_ `using Iterator = TOutIt<T,N>::Type;`
- L306 _public typedef_ `using DerefType = decltype(**((Iterator*)nullptr));`
- L308 _public function_ `uint64 Num() const`
- L309 _public function_ `DerefType operator[](uint64 Idx)`
- L310 _public function_ `Iterator begin() const`
- L311 _public function_ `Iterator end() const`
- L907 _public function_ `template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>` — Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L908 _public function_ ``

#### struct `PlainProps::Upgrade::TOutItems`  
`template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>`  
_L910-910_
- inherits: `TOutItems<FOutFlagsItem>`
- desc: Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L304 _public function_ `TOutItems(FOutItems Items) : FOutItems(Items)`
- L305 _public typedef_ `using Iterator = TOutIt<T,N>::Type;`
- L306 _public typedef_ `using DerefType = decltype(**((Iterator*)nullptr));`
- L308 _public function_ `uint64 Num() const`
- L309 _public function_ `DerefType operator[](uint64 Idx)`
- L310 _public function_ `Iterator begin() const`
- L311 _public function_ `Iterator end() const`
- L907 _public function_ `template<> struct TOutItems<bool> : TOutItems<FOutBoolItem>` — Remap TOutItems/TFiller<Xyz> ->  TOutItems/TFiller<XyzItem> to enable e.g. TOutItems<FOutEnum> instead of TOutItems<FOutEnumItem>
- L908 _public function_ ``

#### struct `PlainProps::Upgrade::TFiller`  
`template<> struct TOutItems<FOutEnum> : TOutItems<FOutEnumItem>`  
_L911-911_
- inherits: `TFiller<FOutBoolItem>`
- L318 _private typedef_ `using Super = TOutItems<T, N>;`
- L319 _private member_ `uint64 Pos = 0;`
- L322 _public function_ `TFiller(Super Items) : Super(Items)`
- L323 _public function_ `~TFiller()`
- L326 _public function_ `template<typename InT> TFiller& operator<<(InT InItem)`
- L333 _public function_ `template<typename InT> TFiller& operator<<(TInItems<InT, N> Items)`

#### struct `PlainProps::Upgrade::TFiller`  
`template<> struct TOutItems<FOutEnumerator> : TOutItems<FOutEnumeratorItem>`  
_L912-912_
- inherits: `TFiller<FOutEnumItem>`
- L318 _private typedef_ `using Super = TOutItems<T, N>;`
- L319 _private member_ `uint64 Pos = 0;`
- L322 _public function_ `TFiller(Super Items) : Super(Items)`
- L323 _public function_ `~TFiller()`
- L326 _public function_ `template<typename InT> TFiller& operator<<(InT InItem)`
- L333 _public function_ `template<typename InT> TFiller& operator<<(TInItems<InT, N> Items)`

#### struct `PlainProps::Upgrade::TFiller`  
`template<> struct TOutItems<FOutFlags> : TOutItems<FOutFlagsItem>`  
_L913-913_
- inherits: `TFiller<FOutEnumeratorItem>`
- L318 _private typedef_ `using Super = TOutItems<T, N>;`
- L319 _private member_ `uint64 Pos = 0;`
- L322 _public function_ `TFiller(Super Items) : Super(Items)`
- L323 _public function_ `~TFiller()`
- L326 _public function_ `template<typename InT> TFiller& operator<<(InT InItem)`
- L333 _public function_ `template<typename InT> TFiller& operator<<(TInItems<InT, N> Items)`

#### struct `PlainProps::Upgrade::TFiller`  
`template<> struct TFiller<bool> : TFiller<FOutBoolItem>`  
_L914-914_
- inherits: `TFiller<FOutFlagsItem>`
- L318 _private typedef_ `using Super = TOutItems<T, N>;`
- L319 _private member_ `uint64 Pos = 0;`
- L322 _public function_ `TFiller(Super Items) : Super(Items)`
- L323 _public function_ `~TFiller()`
- L326 _public function_ `template<typename InT> TFiller& operator<<(InT InItem)`
- L333 _public function_ `template<typename InT> TFiller& operator<<(TInItems<InT, N> Items)`

#### struct `PlainProps::Upgrade::FTypename`  
`struct FTypename`  
_L919-923_
- desc: Unindexed typename
- L921 _public member_ `const char* Scope;`
- L922 _public member_ `const char* Name;`

#### struct `PlainProps::Upgrade::IOps`  
`struct IOps`  
_L926-954_
- desc: All upgrade ops for a particular version of a particular struct
- L928 _public function_ `virtual ~IOps()`
- L930 _public function_ `inline FOpaqueEnum NameFlatEnum(FTypename Enum)`
- L931 _public function_ `inline FOpaqueEnum NameFlagEnum(FTypename Enum)`
- L932 _public prototype_ `virtual FEnumId NameEnum(FTypename Enum) = 0;`
- L933 _public prototype_ `virtual FEnumeratorNames NameEnumerators(FEnumId Enum, std::initializer_list<const char*> Enumerators) = 0;`
- L934 _public function_ `inline FEnumeratorNames NameEnumerators(FTypename Enum, std::initializer_list<const char*> Enumerators)`
- L935 _public prototype_ `virtual FEnumFlagNames NameFlags(FEnumId Enum, std::initializer_list<const char*> Flags) = 0;`
- L936 _public function_ `inline FEnumFlagNames NameFlags(FTypename Enum, std::initializer_list<const char*> Flags)`
- L937 _public prototype_ `virtual FStructId NameStruct(FTypename Struct) = 0;`
- L938 _public prototype_ `virtual FStructMemberNames NameMembers(FStructId Struct, TConstArrayView<FParameter> Members) = 0;`
- L939 _public function_ `inline FStructMemberNames NameMembers(FTypename Struct, TConstArrayView<FParameter> Members)`
- L941 _public prototype_ `virtual void Add(TConstArrayView<FParameter> Ins, TConstArrayView<FParameter> Outs, Op Upgrade) = 0;`
- L946 _public prototype_ `Add(MakeArrayView(Ins), MakeArrayView(Outs), Upgrade);`
- L950 _public prototype_ `virtual void Bump(uint16 NextVersion) = 0;` — Only one version bump or rename is allowed and must happen last
- L953 _public prototype_ `virtual void Rename(FTypename Redirect, uint16 ToVersion) = 0;` — Only one version bump or rename is allowed and must happen last

#### class `PlainProps::Upgrade::FChronicles`  
`class FChronicles`  
_L958-970_
- L960 _private member_ `FHistory& History;`
- L961 _private member_ `FStructId Owner;`
- L962 _private member_ `uint16 PriorVersion = 0xFFFF;`
- L963 _private member_ `bool bFinalVersion = false;`
- L966 _public function_ `FChronicles(FHistory& Out, FStructId InOwner) : History(Out), Owner(InOwner)`
- L968 _public prototype_ `IOps* CreateVersion(FTypename Name, uint16 Version);`
- L969 _public prototype_ `void CommitVersion(IOps* Version);`

#### class `PlainProps::Upgrade::FChronicler`  
`class FChronicler`  
_L974-1013_
- desc: Records relevant ops for a particular struct version in its destructor Helps compile out irrelevant literals and ops
- L977 _public function_ `FORCEINLINE FChronicler(FChronicles Out, const char* Scope, const char* Name, uint16 Ver = 0) : Name`
- L978 _public function_ `FORCEINLINE ~FChronicler()`
- L987 _public function_ `template<auto Release> FORCEINLINE void In(AddOps Add)`
- L997 _public function_ `template<auto Release> FORCEINLINE void Rename(FTypename To, uint16 ToVersion = 0)`
- L1006 _public function_ `FTypename GetName() const`
- L1009 _private member_ `const FTypename Name;`
- L1010 _private member_ `const uint16 Version;`
- L1011 _private member_ `FChronicles Chronicles;`
- L1012 _private member_ `IOps* Out = nullptr;`

#### class `PlainProps::Upgrade::FEnumChronicler`  
`class FEnumChronicler`  
_L1016-1017_
- desc: todo

#### class `PlainProps::Upgrade::TChroniclesOf`  
`template <typename T> class TChroniclesOf : public FChronicles`  
_L1023-1023_
- inherits: `FChronicles`
- desc: Enables overloading void Record(TChroniclesOf<FMyStruct> Out)

#### struct `PlainProps::Upgrade::FHistoryDeleter`  
`struct FHistoryDeleter`  
_L1032-1035_
- L1034 _public prototype_ `void operator()(FHistory* Ptr) const;`

#### struct `PlainProps::Upgrade::FUpgradedInstance`  
`struct FUpgradedInstance`  
_L1045-1050_
- L1047 _public member_ `FDeclId Type;`
- L1048 _public member_ `TConstArrayView<FLooseMember> Loose;` — Owned by scratch, empty if no upgraders ran
- L1049 _public member_ `const FBuiltStruct* Fixed;` — Owned by scratch, null if Loose has any mismatches

#### class `PlainProps::Upgrade::FBatchUpgrader`  
`class FBatchUpgrader`  
_L1052-1067_
- L1055 _public prototype_ `FBatchUpgrader(const FSchemaBatch& InBatch UE_LIFETIMEBOUND, TConstArrayView<FInnerId> InRuntimeIds UE_LIFETIMEBOUND, FIdIndexerBase& Ids);`
- L1058 _public prototype_ `bool MatchSchemas(const IDeclarations& Types);` — @param Types must return declarations that outlive this
- L1061 _public prototype_ `TArray<FUpgradedInstance> Upgrade(TConstArrayView<FStructView> Structs, FHistory& Upgrades, FScratchAllocator& Scratch);` — todo: add unknown members api and error handler
- L1063 _private member_ `const FSchemaBatch& Batch;`
- L1064 _private member_ `TConstArrayView<FInnerId> RuntimeIds;`
- L1065 _private member_ `TBitArray<> MatchingSchemas;`
- L1066 _private member_ `TArray<const FStructDeclaration*> Declarations;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlainProps`
- L29 _namespace_ `namespace Upgrade` (scope `PlainProps`)
- L61 _typedef_ `using FIns = TConstArrayView<FIn>;` (scope `PlainProps::Upgrade`)
- L62 _typedef_ `using FOuts = TArrayView<FOut>;` (scope `PlainProps::Upgrade`)
- L63 _typedef_ `using Op = void (*)(FIns, FOuts, FContext);` (scope `PlainProps::Upgrade`)
- L64 _typedef_ `using AddOps = void (*)(IOps& Out);` (scope `PlainProps::Upgrade`)
- L70 _variable_ `template<Enumeration ReleaseEnum> inline constexpr ReleaseEnum OldestRelevant = {};` (scope `PlainProps::Upgrade`) — Mechanism for compiling out old upgrade code and literals
- L73 _variable_ `template<auto Release> inline constexpr bool Relevant = Release >= OldestRelevant<decltype(Release)>;` (scope `PlainProps::Upgrade`)
- L101 _function_ `template<Arithmetic T> constexpr FParameter MakeParam(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L108 _variable_ `inline constexpr FInnermostType InnermostDecomposedStruct = {.Struct{._ = EInnermostKind::Struct, .IsDecomposed = 1}};` (scope `PlainProps::Upgrade`)
- L109 _variable_ `inline constexpr FInnermostType InnermostDecomposedFlatEnum = {.Enum{._ = EInnermostKind::Enum, .FlagMode = 0, .IsDecomposed = 1}};` (scope `PlainProps::Upgrade`)
- L110 _variable_ `inline constexpr FInnermostType InnermostDecomposedFlagEnum = {.Enum{._ = EInnermostKind::Enum, .FlagMode = 1, .IsDecomposed = 1}};` (scope `PlainProps::Upgrade`)
- L113 _function_ `template<class T> constexpr FInnermostType IllegalItem()` (scope `PlainProps::Upgrade`)
- L119 _variable_ `template<class T> inline constexpr FInnermostType ReflectItem = IllegalItem<T>();` (scope `PlainProps::Upgrade`)
- L123 _variable_ `template<Arithmetic T> inline constexpr FInnermostType ReflectItem<T> = ReflectInnermost<T>;` (scope `PlainProps::Upgrade`)
- L124 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FOutBoolItem> = ReflectInnermost<bool>;` (scope `PlainProps::Upgrade`)
- L125 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FInStruct> = InnermostStaticStruct;` (scope `PlainProps::Upgrade`)
- L126 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FOutStruct> = InnermostStaticStruct;` (scope `PlainProps::Upgrade`)
- L127 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FInAny> = InnermostDynamicStruct;` (scope `PlainProps::Upgrade`)
- L128 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FOutAny> = InnermostDynamicStruct;` (scope `PlainProps::Upgrade`) — Note that FlagMode is unknown
- L129 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FInMembers> = InnermostDecomposedStruct;` (scope `PlainProps::Upgrade`) — Note that FlagMode is unknown
- L130 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FOutMembers> = InnermostDecomposedStruct;` (scope `PlainProps::Upgrade`)
- L131 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FInEnum> = InnermostFlatEnum;` (scope `PlainProps::Upgrade`)
- L132 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FOutEnumItem> = InnermostFlatEnum;` (scope `PlainProps::Upgrade`)
- L133 _variable_ `template<> inline constexpr FInnermostType ReflectItem<FInEnumerator> = InnermostDecomposedFlatEnum;` (scope `PlainProps::Upgrade`)
- L137 _function_ `constexpr FParameter operator ""_Bool(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L138 _function_ `constexpr FParameter operator ""_B1(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L139 _function_ `constexpr FParameter operator ""_S8(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L140 _function_ `constexpr FParameter operator ""_U8(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L141 _function_ `constexpr FParameter operator ""_S16(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L142 _function_ `constexpr FParameter operator ""_U16(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L143 _function_ `constexpr FParameter operator ""_S32(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L144 _function_ `constexpr FParameter operator ""_U32(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L145 _function_ `constexpr FParameter operator ""_U64(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L146 _function_ `constexpr FParameter operator ""_F32(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L147 _function_ `constexpr FParameter operator ""_F64(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L148 _function_ `constexpr FParameter operator ""_Char(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L149 _function_ `constexpr FParameter operator ""_C8(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L150 _function_ `constexpr FParameter operator ""_C16(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L151 _function_ `constexpr FParameter operator ""_C32(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L152 _function_ `constexpr FParameter operator ""_Bools(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L153 _function_ `constexpr FParameter operator ""_B1s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L154 _function_ `constexpr FParameter operator ""_S8s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L155 _function_ `constexpr FParameter operator ""_U8s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L156 _function_ `constexpr FParameter operator ""_S16s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L157 _function_ `constexpr FParameter operator ""_U16s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L158 _function_ `constexpr FParameter operator ""_S32s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L159 _function_ `constexpr FParameter operator ""_U32s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L160 _function_ `constexpr FParameter operator ""_U64s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L161 _function_ `constexpr FParameter operator ""_F32s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L162 _function_ `constexpr FParameter operator ""_F64s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L163 _function_ `constexpr FParameter operator ""_Str(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L164 _function_ `constexpr FParameter operator ""_C8s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L165 _function_ `constexpr FParameter operator ""_C16s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L166 _function_ `constexpr FParameter operator ""_C32s(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L220 _function_ `inline constexpr FEnumLiteral operator ""_Enum(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L221 _function_ `inline constexpr FEnumLiteral operator ""_Enums(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L250 _function_ `inline constexpr FStructLiteral operator ""_Struct(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L251 _function_ `inline constexpr FStructLiteral operator ""_Structs(const char* Name, std::size_t Len)` (scope `PlainProps::Upgrade`)
- L255 _function_ `inline FLooseType ItemOf(FLooseType Type)` (scope `PlainProps::Upgrade`)
- L359 _prototype_ `void CheckRangeType(FLooseType Type, uint16 NumNamed, FInnermostType InnermostType, uint8 NumRanges);` (scope `PlainProps::Upgrade`)
- L361 _function_ `inline void CheckRangeType(FLooseType Type, uint16 NumNamed, FInnermostType InnermostType, uint8 NumRanges)` (scope `PlainProps::Upgrade`)
- L1026 _function_ `template<typename T> void Record(TChroniclesOf<T>)` (scope `PlainProps::Upgrade`)
- L1028 _prototype_ `void EraseChroniclesOf(FHistory& History, FStructId Owner);` (scope `PlainProps::Upgrade`)
- L1036 _typedef_ `using FHistoryPtr = TUniquePtr<FHistory, FHistoryDeleter>;` (scope `PlainProps::Upgrade`)
- L1038 _prototype_ `FHistoryPtr MakeHistory(IDeclarations& Latest, FLiteralIndexerBase& Ids);` (scope `PlainProps::Upgrade`)
- L1039 _prototype_ `FMemberId ResolveName(const FLooseMember& Member, const FHistory& History);` (scope `PlainProps::Upgrade`)
- L1040 _prototype_ `FNameId ResolveEnumerator(const FLooseMember& FlatEnum, const FHistory& History);` (scope `PlainProps::Upgrade`)
- L1041 _prototype_ `TArray<FNameId> ResolveFlags(const FLooseMember& FlagEnum, const FHistory& History);` (scope `PlainProps::Upgrade`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsVisitMember.h` (Public)


#### class `PlainProps::FMemberVisitor`  
`class FMemberVisitor`  
_L11-44_
- desc: Iterates over member bindings
- L14 _public prototype_ `explicit FMemberVisitor(const FSchemaBinding& InSchema);`
- L16 _public function_ `bool HasMore() const`
- L17 _public function_ `uint16 GetIndex() const`
- L19 _public prototype_ `EMemberKind PeekKind() const;` — @pre HasMore()
- L20 _public prototype_ `FMemberBindType PeekType() const;` — @pre HasMore()
- L21 _public prototype_ `uint32 PeekOffset() const;` — @pre HasMore()
- L23 _public prototype_ `FLeafMemberBinding GrabLeaf();` — @pre PeekKind() == EMemberKind::Leaf
- L24 _public prototype_ `FRangeMemberBinding GrabRange();` — @pre PeekKind() == EMemberKind::Range
- L25 _public prototype_ `FStructMemberBinding GrabStruct();` — @pre PeekKind() == EMemberKind::Struct
- L26 _public prototype_ `FBindId GrabSuper();` — @pre First grab and has declared super
- L27 _public prototype_ `void SkipMember();`
- L30 _protected member_ `const FSchemaBinding& Schema;`
- L31 _protected member_ `const uint16 NumMembers;`
- L32 _protected member_ `uint16 MemberIdx = 0;`
- L33 _protected member_ `uint16 InnerRangeIdx = 0;` — Types of [nested] ranges
- L34 _protected member_ `uint16 InnerIdIdx = 0;` — Types of static structs and enums
- L36 _protected typedef_ `using FMemberBindTypeRange = TConstArrayView<FMemberBindType>;`
- L38 _protected prototype_ `uint64 GrabMemberOffset();`
- L39 _protected prototype_ `FMemberBindTypeRange GrabInnerTypes();`
- L40 _protected prototype_ `FInnerId GrabInnerId();`
- L41 _protected prototype_ `FBindId GrabStructSchema(FStructType Type);`
- L42 _protected prototype_ `FOptionalInnerId GrabRangeSchema(FMemberType InnermostType);`
- L43 _protected function_ `FEnumId GrabEnumSchema()`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlainProps`

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsVisualize.h` (Public)


#### struct `PlainProps::DbgVis::FBuiltStruct`  
`struct FBuiltStruct`  
_L19-23_
- L21 _public member_ `uint16 NumMembers;`
- L22 _public member_ `FBuiltMember Members[0];`

#### struct `PlainProps::DbgVis::FBuiltRange`  
`struct FBuiltRange`  
_L25-29_
- L27 _public member_ `uint64 Num;`
- L28 _public member_ `uint8 Data[0];`

#### struct `PlainProps::DbgVis::FSchemaBatch`  
`struct FSchemaBatch`  
_L34-42_
- L36 _public member_ `uint32 NumNestedScopes;`
- L37 _public member_ `uint32 NestedScopesOffset;`
- L38 _public member_ `uint32 NumParametricTypes;`
- L39 _public member_ `uint32 NumSchemas;`
- L40 _public member_ `uint32 NumStructSchemas;`
- L41 _public member_ `uint32 SchemaOffsets[0];`

#### enum `PlainProps::DbgVis::ESuper`  
`enum class ESuper : uint8`  
_L44-44_
- L44 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; struct FStructSchema { FType Type; uint16 Version; uint16 NumMembers; uint16 NumRangeTypes;`
- L44 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; struct FStructSchema { FType Type; uint16 Version; uint16 NumMembers; uint16 NumRangeTypes;`
- L44 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; struct FStructSchema { FType Type; uint16 Version; uint16 NumMembers; uint16 NumRangeTypes;`
- L44 _public enumerator_ `enum class ESuper : uint8 { No, Unused, Used, Reused }; struct FStructSchema { FType Type; uint16 Version; uint16 NumMembers; uint16 NumRangeTypes;`

#### struct `PlainProps::DbgVis::FStructSchema`  
`struct FStructSchema`  
_L46-56_
- L48 _public member_ `FType Type;`
- L49 _public member_ `uint16 Version;`
- L50 _public member_ `uint16 NumMembers;`
- L51 _public member_ `uint16 NumRangeTypes;`
- L52 _public member_ `uint16 NumInnerSchemas;`
- L53 _public member_ `ESuper Inheritance : 2;`
- L54 _public member_ `uint8 IsDense : 1;`
- L55 _public member_ `FMemberType Footer[0];`

#### struct `PlainProps::DbgVis::FEnumSchema`  
`struct FEnumSchema`  
_L58-66_
- L60 _public member_ `FType Type;`
- L61 _public member_ `uint8 FlagMode : 1;`
- L62 _public member_ `uint8 ExplicitConstants : 1;`
- L63 _public member_ `ELeafWidth Width;`
- L64 _public member_ `uint16 Num;`
- L65 _public member_ `FNameId Footer[0];`

#### struct `PlainProps::DbgVis::FLoadStructPlan`  
`struct FLoadStructPlan`  
_L71-74_
- L73 _public member_ `uint64 Handle;`

#### struct `PlainProps::DbgVis::FLateLoadPlans`  
`struct FLateLoadPlans`  
_L76-80_
- L78 _public member_ `FLateLoadPlans* Next;`
- L79 _public member_ `uint8 Data[0];`

#### struct `PlainProps::DbgVis::FLoadBatch`  
`struct FLoadBatch`  
_L82-90_
- L84 _public member_ `FSchemaBatchId BatchId;`
- L85 _public member_ `uint32 NumReadSchemas;`
- L86 _public member_ `uint32 NumPlans;`
- L87 _public member_ `uint32 MaxPlans;`
- L88 _public member_ `FLateLoadPlans* LatePlans;`
- L89 _public member_ `FLoadStructPlan Plans[0];`

#### struct `PlainProps::DbgVis::FIdVisualizer`  
`struct FIdVisualizer`  
_L94-107_
- L96 _public member_ `const FIdIndexerBase* Indexer;`
- L97 _public member_ `const char* NameType;`
- L99 _public function_ `static void KeepDebugInfo(DbgVis::FBuiltStruct*)`
- L100 _public function_ `static void KeepDebugInfo(DbgVis::FBuiltRange*)`
- L101 _public function_ `static void KeepDebugInfo(DbgVis::ESuper)`
- L102 _public function_ `static void KeepDebugInfo(DbgVis::FSchemaBatch*)`
- L103 _public function_ `static void KeepDebugInfo(DbgVis::FStructSchema*)`
- L104 _public function_ `static void KeepDebugInfo(DbgVis::FEnumSchema*)`
- L105 _public function_ `static void KeepDebugInfo(DbgVis::FLoadStructPlan*)`
- L106 _public function_ `static void KeepDebugInfo(DbgVis::FLoadBatch*)`

#### class `PlainProps::DbgVis::FIdScope`  
`class FIdScope`  
_L109-130_
- L115 _public function_ `template<typename NameT> FIdScope(const TIdIndexer<NameT>& Indexer, const char NameType[8] = nullptr) : Current` — NameType must be a unique static string identifer for NameT, it is used by natvis in a strncmp(str1,str2,N) expression to select the correct typed name indexer, N <= 8
- L122 _public prototype_ `~FIdScope();`
- L125 _private prototype_ `void AssignDebuggingState();`
- L127 _private member_ `inline static FIdVisualizer* Global = nullptr;`
- L128 _private member_ `FIdVisualizer Current;`
- L129 _private member_ `FIdVisualizer* Previous;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlainProps`
- L14 _namespace_ `namespace DbgVis` (scope `PlainProps`)
- L132 _prototype_ `void AssignReadSchemasDebuggingState(FSchemaBatch** Slots);` (scope `PlainProps::DbgVis`)

### `Plugins/Experimental/PlainProps/Source/Public/PlainPropsWrite.h` (Public)


#### class `PlainProps::FWriter`  
`class FWriter`  
_L22-38_
- L25 _public prototype_ `FWriter(const FIdIndexerBase& AllIds, const IDeclarations& Declarations, const FBuiltSchemas& InSchemas, ESchemaFormat Format);`
- L26 _public prototype_ `~FWriter();`
- L28 _public prototype_ `TConstArrayView<FNameId> GetUsedNames() const;`
- L29 _public prototype_ `FOptionalStructSchemaId GetWriteId(FStructId BuiltId) const;`
- L31 _public prototype_ `void WriteSchemas(TArray64<uint8>& Out) const;`
- L32 _public prototype_ `FStructSchemaId WriteMembers(TArray64<uint8>& Out, FStructId BuiltId, const FBuiltStruct& Struct) const;`
- L35 _private member_ `const FBuiltSchemas& Schemas;`
- L36 _private member_ `FDebugIds Debug;`
- L37 _private member_ `TUniquePtr<FWriteIds> NewIds;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PlainProps`
- L42 _function_ `inline void WriteData(TArray64<uint8>& Out, const void* Data, int64 Size)` (scope `PlainProps`)
- L48 _function_ `template<::UE::CContiguousRange ArrayType> void WriteArray(TArray64<uint8>& Out, const ArrayType& In)` (scope `PlainProps`)
- L54 _function_ `template<typename T> void WriteAlignmentPadding(TArray64<uint8>& Out)` (scope `PlainProps`)
- L60 _function_ `template<typename T> void WriteAlignedArray(TArray64<uint8>& Out, TArrayView<T> In)` (scope `PlainProps`)
- L67 _function_ `template<typename T> inline void WriteInt(TArray64<uint8>& Out, T Number) requires (std::is_integral_v<T> && !!PLATFORM_LITTLE_ENDIAN)` (scope `PlainProps`)
- L72 _prototype_ `uint64 WriteSkippableSlice(TArray64<uint8>& Out, TConstArrayView64<uint8> Slice);` (scope `PlainProps`)
