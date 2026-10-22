# Developer / HlslParser

- module root: `Source/Developer/HlslParser`
- headers: 6; symbols: 854
- symbol kinds: class=9, enum=16, enumerator=361, function=125, macro=2, member=139, namespace=14, prototype=134, struct=48, typedef=3, union=3
- PrivateDependencyModuleNames: Core

### `Source/Developer/HlslParser/Internal/HlslParserInternal.h` (Internal)


#### struct `UE::HlslParser::FScopedDeclarations`  
`struct FScopedDeclarations`  
_L12-21_
- desc: Structure to hold forward declarations for a specific scope/namespace chain for the HlslParser
- L14 _public function_ `FScopedDeclarations(TConstArrayView<FStringView> InScope, TConstArrayView<FStringView> InSymbols) : Scope(InScope) , Symbols(InSymbols)`
- L19 _public member_ `TConstArrayView<FStringView> Scope;`
- L20 _public member_ `TConstArrayView<FStringView> Symbols;`

#### enum `UE::HlslParser::EShaderParameterStorageClass`  
`enum class EShaderParameterStorageClass`  
_L45-49_
- desc: Shader input/output parameter storage classes. Naming adopted from SPIR-V nomenclature.
- L47 _public enumerator_ `Input`
- L48 _public enumerator_ `Output`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace HlslParser` (scope `UE`)
- L23 _prototype_ `extern bool RemoveUnusedOutputs( FString& InOutSourceCode, TConstArrayView<FStringView> InUsedOutputs, TConstArrayView<FStringView> InExceptions, TConstArrayView<FScopedDeclarations> InScopedDeclarations, FString& InOutEntryPoint, TArray<FString>& OutErrors );` (scope `UE::HlslParser`)
- L32 _prototype_ `extern bool RemoveUnusedOutputs(FString& InOutSourceCode, const TArray<FString>& InUsedOutputs, const TArray<FString>& InExceptions, FString& InOutEntryPoint, TArray<FString>& OutErrors);` (scope `UE::HlslParser`)
- L34 _prototype_ `extern bool RemoveUnusedInputs( FString& InOutSourceCode, TConstArrayView<FStringView> InUsedInputs, TConstArrayView<FScopedDeclarations> InScopedDeclarations, FString& InOutEntryPoint, TArray<FString>& OutErrors );` (scope `UE::HlslParser`)
- L42 _prototype_ `extern bool RemoveUnusedInputs(FString& InOutSourceCode, const TArray<FString>& InUsedInputs, FString& InOutEntryPoint, TArray<FString>& OutErrors);` (scope `UE::HlslParser`)
- L52 _prototype_ `extern bool FindEntryPointParameters( const FString& InSourceCode, const FString& InEntryPoint, EShaderParameterStorageClass ParameterStorageClass, TConstArrayView<FScopedDeclarations> InScopedDeclarations, TArray<FString>& OutParameterSemantics, TArray<FString>& OutErrors );` (scope `UE::HlslParser`) — Returns the semantic names of all individual entry point parameters (i.e. all structure fields are inlined)
- L62 _prototype_ `extern bool ForEachHlslIdentifier(const FString& InSourceCode, const FString& InFilename, const TFunction<bool(FStringView)>& InIdentifierCallback);` (scope `UE::HlslParser`) — Invokes the input callback for each identifier in the specified HLSL source code until the callback returns false.

### `Source/Developer/HlslParser/Private/HlslAST.h` (Private)


#### class `CrossCompiler::AST::FIdentifier`  
`class FIdentifier`  
_L34-100_
- desc: Wrapper for identifier strings. Provides an indirection that can be used for efficient symbol renaming, etc.
- L37 _private function_ `FIdentifier(const TCHAR* InString, int32 InLength) : StringView(InString, InLength)`
- L41 _private function_ `~FIdentifier()`
- L50 _public function_ `static FIdentifier* New(FLinearAllocator* Allocator, const TCHAR* InString, int32 InLength = -1)` — NOTE: All memory is owned by the liner allocator and is released when it is destroyed. No need to delete it explicitly.
- L61 _public function_ `static FIdentifier* New(FLinearAllocator* Allocator, FStringView InString)`
- L66 _public function_ `FStringView ToStringView() const`
- L71 _public function_ `FString ToString() const`
- L76 _public function_ `const TCHAR* GetData() const`
- L81 _public function_ `int32 Len() const`
- L86 _public function_ `bool Equals(FStringView Other) const`
- L91 _public function_ `void Rename(FLinearAllocator* Allocator, FStringView InString)`
- L99 _private member_ `FStringView StringView;`

#### struct `CrossCompiler::AST::FASTWriter`  
`struct FASTWriter`  
_L102-190_
- L104 _public member_ `FString& Output;`
- L105 _public member_ `int32 Indent = 0;`
- L106 _public member_ `int32 ExpressionScope = 0;`
- L108 _public function_ `FASTWriter(FString& FinalOutput) : Output(FinalOutput)`
- L114 _public function_ `FASTWriter(FASTWriter& IndentedWriter) : Output(IndentedWriter.Output)` — Construct from another to go back to unindented writing
- L119 _public prototype_ `void DoIndent();`
- L121 _public function_ `inline FASTWriter& operator << (const TCHAR* String)`
- L131 _public function_ `inline FASTWriter& operator << (const FIdentifier* Identifier)`
- L141 _public function_ `inline FASTWriter& operator << (const TCHAR Char)`
- L151 _public function_ `inline FASTWriter& operator << (uint32 N)`
- L170 _public function_ `inline FASTWriter& operator << (float F)`

#### union `CrossCompiler::AST::FASTWriter::operator <<::(anonymous)`  
``  
_L154-157_

#### struct `CrossCompiler::AST::FASTWriterIncrementScope`  
`struct FASTWriterIncrementScope`  
_L192-206_
- L194 _public member_ `FASTWriter& Writer;`
- L196 _public function_ `FASTWriterIncrementScope(FASTWriter& InWriter) : Writer(InWriter)`
- L202 _public function_ `~FASTWriterIncrementScope()`

#### struct `CrossCompiler::AST::FASTWriterSkipExpressionScope`  
`struct FASTWriterSkipExpressionScope`  
_L208-224_
- L210 _public member_ `FASTWriter& Writer;`
- L211 _public member_ `int32 OriginalScope = 0;`
- L213 _public function_ `FASTWriterSkipExpressionScope(FASTWriter& InWriter) : Writer(InWriter)`
- L220 _public function_ `~FASTWriterSkipExpressionScope()`

#### struct `CrossCompiler::AST::FASTWriterClearIndentScope`  
`struct FASTWriterClearIndentScope`  
_L226-242_
- L228 _public member_ `FASTWriter& Writer;`
- L229 _public member_ `int32 OriginalIndent = 0;`
- L231 _public function_ `FASTWriterClearIndentScope(FASTWriter& InWriter) : Writer(InWriter)`
- L238 _public function_ `~FASTWriterClearIndentScope()`

#### class `CrossCompiler::AST::FNode`  
`class FNode`  
_L244-300_
- L247 _public member_ `FSourceInfo SourceInfo;`
- L249 _public member_ `TLinearArray<FAttribute*> Attributes;`
- L251 _public prototype_ `virtual void Write(FASTWriter& Writer) const = 0;`
- L254 _public function_ `virtual FCBufferDeclaration* AsCBufferDeclaration()` — RTTI
- L255 _public function_ `virtual FDeclaratorList* AsDeclaratorList()`
- L256 _public function_ `virtual FDeclaration* AsDeclaration()`
- L257 _public function_ `virtual FFunctionDefinition* AsFunctionDefinition()`
- L258 _public function_ `virtual FParameterDeclarator* AsParameterDeclarator()`
- L259 _public function_ `virtual FUnaryExpression* AsUnaryExpression()`
- L260 _public function_ `virtual FJumpStatement* AsJumpStatement()`
- L261 _public function_ `virtual FSelectionStatement* AsSelectionStatement()`
- L262 _public function_ `virtual FSwitchStatement* AsSwitchStatement()`
- L263 _public function_ `virtual FIterationStatement* AsIterationStatement()`
- L264 _public function_ `virtual FCompoundStatement* AsCompoundStatement()`
- L265 _public function_ `virtual FExpressionStatement* AsExpressionStatement()`
- L268 _public function_ `virtual bool GetConstantIntValue(int32& OutValue) const` — Returns true if the expression can be evaluated to a constant int
- L272 _public function_ `static void* operator new(size_t Size, FLinearAllocator* Allocator)` — Callers of this ralloc-based new need not call delete. It's easier to just ralloc_free 'ctx' (or any of its ancestors).
- L284 _public function_ `static void operator delete(void* Pointer)` — If the user *does* call delete, that's OK, we will just ralloc_free in that case.
- L293 _public prototype_ `virtual ~FNode() = default;`
- L297 _protected prototype_ `FNode(FLinearAllocator* Allocator, const FSourceInfo& InInfo);` — FNode();
- L299 _protected prototype_ `void WriteAttributes(FASTWriter& Writer) const;`

#### enum `CrossCompiler::AST::EOperators`  
`enum class EOperators`  
_L305-360_
- desc: Operators for AST expression nodes.
- L307 _public enumerator_ `Assign`
- L308 _public enumerator_ `Plus`
- L309 _public enumerator_ `Minus` — Plus,         < Unary + operator.
- L310 _public enumerator_ `Add`
- L311 _public enumerator_ `Sub`
- L312 _public enumerator_ `Mul`
- L313 _public enumerator_ `Div`
- L314 _public enumerator_ `Mod`
- L315 _public enumerator_ `LShift`
- L316 _public enumerator_ `RShift`
- L317 _public enumerator_ `Less`
- L318 _public enumerator_ `Greater`
- L319 _public enumerator_ `LEqual`
- L320 _public enumerator_ `GEqual`
- L321 _public enumerator_ `Equal`
- L322 _public enumerator_ `NEqual`
- L323 _public enumerator_ `BitAnd`
- L324 _public enumerator_ `BitXor`
- L325 _public enumerator_ `BitOr`
- L326 _public enumerator_ `BitNeg` — ~
- L327 _public enumerator_ `LogicAnd`
- L328 _public enumerator_ `LogicXor`
- L329 _public enumerator_ `LogicOr`
- L330 _public enumerator_ `LogicNot` — !
- L332 _public enumerator_ `MulAssign`
- L333 _public enumerator_ `DivAssign`
- L334 _public enumerator_ `ModAssign`
- L335 _public enumerator_ `AddAssign`
- L336 _public enumerator_ `SubAssign`
- L337 _public enumerator_ `LSAssign`
- L338 _public enumerator_ `RSAssign`
- L339 _public enumerator_ `AndAssign`
- L340 _public enumerator_ `XorAssign`
- L341 _public enumerator_ `OrAssign`
- L343 _public enumerator_ `Conditional`
- L345 _public enumerator_ `PreInc`
- L346 _public enumerator_ `PreDec`
- L347 _public enumerator_ `PostInc`
- L348 _public enumerator_ `PostDec`
- L349 _public enumerator_ `FieldSelection`
- L350 _public enumerator_ `ArrayIndex`
- L352 _public enumerator_ `FunctionCall`
- L353 _public enumerator_ `ExpressionList`
- L355 _public enumerator_ `Identifier`
- L356 _public enumerator_ `Literal`
- L358 _public enumerator_ `TypeCast`
- L359 _public enumerator_ `SizeOf`

#### struct `CrossCompiler::AST::FPragma`  
`struct FPragma : public FNode`  
_L464-471_
- inherits: `FNode`
- L466 _public prototype_ `FPragma(FLinearAllocator* InAllocator, const TCHAR* InPragma, const FSourceInfo& InInfo);`
- L468 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L470 _public member_ `const TCHAR* Pragma;`

#### struct `CrossCompiler::AST::FExpression`  
`struct FExpression : public FNode`  
_L473-501_
- inherits: `FNode`
- L475 _public prototype_ `FExpression(FLinearAllocator* InAllocator, EOperators InOperator, const FSourceInfo& InInfo);`
- L476 _public prototype_ `FExpression(FLinearAllocator* InAllocator, EOperators InOperator, FExpression* E0, const FSourceInfo& InInfo);`
- L477 _public prototype_ `FExpression(FLinearAllocator* InAllocator, EOperators InOperator, FExpression* E0, FExpression* E1, const FSourceInfo& InInfo);`
- L478 _public prototype_ `FExpression(FLinearAllocator* InAllocator, EOperators InOperator, FExpression* E0, FExpression* E1, FExpression* E2, const FSourceInfo& InInfo);`
- L479 _public prototype_ `~FExpression();`
- L481 _public member_ `EOperators Operator;`
- L488 _public member_ `const FIdentifier* Identifier;`
- L490 _public member_ `TLinearArray<FExpression*> Expressions;`
- L492 _public prototype_ `void WriteOperator(FASTWriter& Writer) const;`
- L493 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L495 _public prototype_ `virtual bool GetConstantIntValue(int32& OutValue) const override;`
- L497 _public function_ `bool IsConstant() const`

#### union `CrossCompiler::AST::FExpression::(anonymous)`  
``  
_L484-487_

#### struct `CrossCompiler::AST::FUnaryExpression`  
`struct FUnaryExpression : public FExpression`  
_L503-509_
- inherits: `FExpression`
- L505 _public prototype_ `FUnaryExpression(FLinearAllocator* InAllocator, EOperators InOperator, FExpression* Expr, const FSourceInfo& InInfo);`
- L507 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L508 _public function_ `virtual FUnaryExpression* AsUnaryExpression() override`

#### struct `CrossCompiler::AST::FBinaryExpression`  
`struct FBinaryExpression : public FExpression`  
_L511-517_
- inherits: `FExpression`
- L513 _public prototype_ `FBinaryExpression(FLinearAllocator* InAllocator, EOperators InOperator, FExpression* E0, FExpression* E1, const FSourceInfo& InInfo);`
- L515 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L516 _public prototype_ `virtual bool GetConstantIntValue(int32& OutValue) const override;`

#### struct `CrossCompiler::AST::FFunctionExpression`  
`struct FFunctionExpression : public FExpression`  
_L519-526_
- inherits: `FExpression`
- L521 _public prototype_ `FFunctionExpression(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, FExpression* InCallee);`
- L523 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L525 _public member_ `FExpression* Callee;`

#### struct `CrossCompiler::AST::FExpressionList`  
`struct FExpressionList : public FExpression`  
_L528-543_
- inherits: `FExpression`
- L538 _public prototype_ `FExpressionList(FLinearAllocator* InAllocator, EType InType, const FSourceInfo& InInfo);`
- L540 _public member_ `EType Type = EType::FreeForm;`
- L542 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`

#### enum `CrossCompiler::AST::FExpressionList::EType`  
`enum class EType`  
_L530-536_
- L532 _public enumerator_ `FreeForm` — a, b, c
- L533 _public enumerator_ `Parenthesized` — ( a, b, c )
- L534 _public enumerator_ `Braced` — { a, b, c }
- L535 _public enumerator_ `Templated` — < a, b, c >

#### struct `CrossCompiler::AST::FCompoundStatement`  
`struct FCompoundStatement : public FNode`  
_L545-554_
- inherits: `FNode`
- L547 _public prototype_ `FCompoundStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L548 _public prototype_ `~FCompoundStatement();`
- L550 _public member_ `TLinearArray<FNode*> Statements;`
- L552 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L553 _public function_ `virtual FCompoundStatement* AsCompoundStatement() override`

#### struct `CrossCompiler::AST::FStaticAssertStatement`  
`struct FStaticAssertStatement : public FNode`  
_L556-566_
- inherits: `FNode`
- L558 _public prototype_ `FStaticAssertStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, const FString& InKeyword);`
- L559 _public prototype_ `~FStaticAssertStatement();`
- L561 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L563 _public member_ `const FString Keyword;` — Either "_Static_assert" (DXC) or "static_assert" (C++11 like compilers)
- L564 _public member_ `FExpression* Condition;`
- L565 _public member_ `FString Message;`

#### struct `CrossCompiler::AST::FC99PragmaStatement`  
`struct FC99PragmaStatement : public FNode`  
_L568-576_
- inherits: `FNode`
- L570 _public prototype_ `FC99PragmaStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, const FString& InArgument);`
- L571 _public prototype_ `~FC99PragmaStatement();`
- L573 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L575 _public member_ `FString Argument;`

#### struct `CrossCompiler::AST::FSemanticSpecifier`  
`struct FSemanticSpecifier : public FNode`  
_L578-596_
- inherits: `FNode`
- L587 _public prototype_ `FSemanticSpecifier(FLinearAllocator* InAllocator, ESpecType InType, const FSourceInfo& InInfo);`
- L588 _public prototype_ `FSemanticSpecifier(FLinearAllocator* InAllocator, const TCHAR* InSemantic, const FSourceInfo& InInfo);`
- L589 _public prototype_ `~FSemanticSpecifier();`
- L591 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L593 _public member_ `TLinearArray<FExpression*> Arguments;`
- L594 _public member_ `ESpecType Type;`
- L595 _public member_ `const TCHAR* Semantic;`

#### enum `CrossCompiler::AST::FSemanticSpecifier::ESpecType`  
`enum class ESpecType`  
_L580-585_
- L582 _public enumerator_ `Semantic`
- L583 _public enumerator_ `Register`
- L584 _public enumerator_ `PackOffset`

#### struct `CrossCompiler::AST::FDeclaration`  
`struct FDeclaration : public FNode`  
_L598-615_
- inherits: `FNode`
- L600 _public prototype_ `FDeclaration(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L601 _public prototype_ `~FDeclaration();`
- L603 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L604 _public function_ `virtual FDeclaration* AsDeclaration() override`
- L606 _public member_ `FIdentifier* Identifier;` — non-const to allow renaming
- L608 _public member_ `FSemanticSpecifier* Semantic;`
- L610 _public member_ `bool bIsArray;`
- L612 _public member_ `TLinearArray<FExpression*> ArraySize;`
- L614 _public member_ `FExpression* Initializer;`

#### struct `CrossCompiler::AST::FTypeQualifier`  
`struct FTypeQualifier`  
_L617-646_
- L639 _public member_ `const TCHAR* PrimitiveType = nullptr;`
- L640 _public member_ `const TCHAR* NoInterpolatorType = nullptr;`
- L641 _public member_ `const TCHAR* NoPerspectiveType = nullptr;`
- L643 _public prototype_ `FTypeQualifier();`
- L645 _public prototype_ `void Write(FASTWriter& Writer) const;`

#### union `CrossCompiler::AST::FTypeQualifier::(anonymous)`  
``  
_L620-637_

#### struct `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::(anonymous)`  
``  
_L622-635_

#### struct `CrossCompiler::AST::FStructSpecifier`  
`struct FStructSpecifier : public FNode`  
_L648-659_
- inherits: `FNode`
- L650 _public prototype_ `FStructSpecifier(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L651 _public prototype_ `~FStructSpecifier();`
- L653 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L655 _public member_ `const TCHAR* Name;`
- L656 _public member_ `const TCHAR* ParentName;`
- L657 _public member_ `TLinearArray<FNode*> Members;`
- L658 _public member_ `bool bForwardDeclaration;`

#### struct `CrossCompiler::AST::FCBufferDeclaration`  
`struct FCBufferDeclaration : public FNode`  
_L661-671_
- inherits: `FNode`
- L663 _public prototype_ `FCBufferDeclaration(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L664 _public prototype_ `~FCBufferDeclaration();`
- L666 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L667 _public function_ `virtual FCBufferDeclaration* AsCBufferDeclaration() override`
- L669 _public member_ `const TCHAR* Name;`
- L670 _public member_ `TLinearArray<FNode*> Declarations;`

#### struct `CrossCompiler::AST::FTypeSpecifier`  
`struct FTypeSpecifier : public FNode`  
_L673-691_
- inherits: `FNode`
- L675 _public prototype_ `FTypeSpecifier(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L676 _public prototype_ `~FTypeSpecifier();`
- L678 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L680 _public member_ `const TCHAR* TypeName;`
- L681 _public member_ `const TCHAR* InnerType;`
- L683 _public member_ `FStructSpecifier* Structure;`
- L685 _public member_ `int32 TextureMSNumSamples;`
- L687 _public member_ `int32 PatchSize;`
- L688 _public member_ `bool bPrecise = false;`
- L689 _public member_ `bool bIsArray;`
- L690 _public member_ `FExpression* ArraySize;`

#### struct `CrossCompiler::AST::FFullySpecifiedType`  
`struct FFullySpecifiedType : public FNode`  
_L693-702_
- inherits: `FNode`
- L695 _public prototype_ `FFullySpecifiedType(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L696 _public prototype_ `~FFullySpecifiedType();`
- L698 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L700 _public member_ `FTypeQualifier Qualifier;`
- L701 _public member_ `FTypeSpecifier* Specifier;`

#### struct `CrossCompiler::AST::FDeclaratorList`  
`struct FDeclaratorList : public FNode`  
_L704-718_
- inherits: `FNode`
- L706 _public prototype_ `FDeclaratorList(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L707 _public prototype_ `~FDeclaratorList();`
- L709 _public prototype_ `void WriteNoEOL(FASTWriter& Writer) const;`
- L711 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L712 _public function_ `virtual FDeclaratorList* AsDeclaratorList() override`
- L714 _public member_ `FFullySpecifiedType* Type;`
- L715 _public member_ `TLinearArray<FNode*> Declarations;`
- L717 _public member_ `bool bTypedef = false;`

#### struct `CrossCompiler::AST::FParameterDeclarator`  
`struct FParameterDeclarator : public FNode`  
_L720-737_
- inherits: `FNode`
- L722 _public prototype_ `FParameterDeclarator(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L723 _public prototype_ `~FParameterDeclarator();`
- L725 _public prototype_ `static FParameterDeclarator* CreateFromDeclaratorList(FDeclaratorList* List, FLinearAllocator* Allocator);`
- L727 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L728 _public function_ `virtual FParameterDeclarator* AsParameterDeclarator() override`
- L730 _public member_ `FFullySpecifiedType* Type;`
- L731 _public member_ `FIdentifier* Identifier;` — non-const to allow renaming
- L732 _public member_ `FSemanticSpecifier* Semantic;`
- L733 _public member_ `bool bIsArray;`
- L735 _public member_ `TLinearArray<FExpression*> ArraySize;`
- L736 _public member_ `FExpression* DefaultValue;`

#### struct `CrossCompiler::AST::FFunction`  
`struct FFunction : public FNode`  
_L739-758_
- inherits: `FNode`
- L741 _public prototype_ `FFunction(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L742 _public prototype_ `~FFunction();`
- L744 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L746 _public member_ `FFullySpecifiedType* ReturnType;`
- L747 _public member_ `const FIdentifier* ScopeIdentifier;`
- L748 _public member_ `const FIdentifier* Identifier;`
- L749 _public member_ `FSemanticSpecifier* ReturnSemantic;`
- L751 _public member_ `TLinearArray<FNode*> Parameters;`
- L753 _public member_ `bool bIsDefinition;`
- L754 _public member_ `bool bIsOperator;`
- L755 _public member_ `bool bIsStatic;`

#### struct `CrossCompiler::AST::FExpressionStatement`  
`struct FExpressionStatement : public FNode`  
_L760-769_
- inherits: `FNode`
- L762 _public prototype_ `FExpressionStatement(FLinearAllocator* InAllocator, FExpression* InExpr, const FSourceInfo& InInfo);`
- L763 _public prototype_ `~FExpressionStatement();`
- L765 _public member_ `FExpression* Expression;`
- L766 _public function_ `virtual FExpressionStatement* AsExpressionStatement() override`
- L768 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`

#### struct `CrossCompiler::AST::FCaseLabel`  
`struct FCaseLabel : public FNode`  
_L771-779_
- inherits: `FNode`
- L773 _public prototype_ `FCaseLabel(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, AST::FExpression* InExpression);`
- L774 _public prototype_ `~FCaseLabel();`
- L776 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L778 _public member_ `FExpression* TestExpression;`

#### struct `CrossCompiler::AST::FCaseLabelList`  
`struct FCaseLabelList : public FNode`  
_L781-789_
- inherits: `FNode`
- L783 _public prototype_ `FCaseLabelList(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L784 _public prototype_ `~FCaseLabelList();`
- L786 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L788 _public member_ `TLinearArray<FCaseLabel*> Labels;`

#### struct `CrossCompiler::AST::FCaseStatement`  
`struct FCaseStatement : public FNode`  
_L791-800_
- inherits: `FNode`
- L793 _public prototype_ `FCaseStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, FCaseLabelList* InLabels);`
- L794 _public prototype_ `~FCaseStatement();`
- L796 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L798 _public member_ `FCaseLabelList* Labels;`
- L799 _public member_ `TLinearArray<FNode*> Statements;`

#### struct `CrossCompiler::AST::FCaseStatementList`  
`struct FCaseStatementList : public FNode`  
_L802-810_
- inherits: `FNode`
- L804 _public prototype_ `FCaseStatementList(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L805 _public prototype_ `~FCaseStatementList();`
- L807 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L809 _public member_ `TLinearArray<FCaseStatement*> Cases;`

#### struct `CrossCompiler::AST::FSwitchBody`  
`struct FSwitchBody : public FNode`  
_L812-820_
- inherits: `FNode`
- L814 _public prototype_ `FSwitchBody(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L815 _public prototype_ `~FSwitchBody();`
- L817 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L819 _public member_ `FCaseStatementList* CaseList;`

#### struct `CrossCompiler::AST::FSelectionStatement`  
`struct FSelectionStatement : public FNode`  
_L822-834_
- inherits: `FNode`
- L824 _public prototype_ `FSelectionStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L825 _public prototype_ `~FSelectionStatement();`
- L827 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L828 _public function_ `virtual FSelectionStatement* AsSelectionStatement() override`
- L830 _public member_ `FExpression* Condition;`
- L832 _public member_ `FNode* ThenStatement;`
- L833 _public member_ `FNode* ElseStatement;`

#### struct `CrossCompiler::AST::FSwitchStatement`  
`struct FSwitchStatement : public FNode`  
_L836-846_
- inherits: `FNode`
- L838 _public prototype_ `FSwitchStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, FExpression* InCondition, FSwitchBody* InBody);`
- L839 _public prototype_ `~FSwitchStatement();`
- L841 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L842 _public function_ `virtual FSwitchStatement* AsSwitchStatement() override`
- L844 _public member_ `FExpression* Condition;`
- L845 _public member_ `FSwitchBody* Body;`

#### enum `CrossCompiler::AST::EIterationType`  
`enum class EIterationType`  
_L848-853_
- L850 _public enumerator_ `For`
- L851 _public enumerator_ `While`
- L852 _public enumerator_ `DoWhile`

#### struct `CrossCompiler::AST::FIterationStatement`  
`struct FIterationStatement : public FNode`  
_L855-870_
- inherits: `FNode`
- L857 _public prototype_ `FIterationStatement(FLinearAllocator* InAllocator, const FSourceInfo& InInfo, EIterationType InType);`
- L858 _public prototype_ `~FIterationStatement();`
- L860 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L861 _public function_ `virtual FIterationStatement* AsIterationStatement() override`
- L863 _public member_ `EIterationType Type;`
- L865 _public member_ `AST::FNode* InitStatement;`
- L866 _public member_ `AST::FNode* Condition;`
- L867 _public member_ `FExpression* RestExpression;`
- L869 _public member_ `AST::FNode* Body;`

#### enum `CrossCompiler::AST::EJumpType`  
`enum class EJumpType`  
_L872-878_
- L874 _public enumerator_ `Continue`
- L875 _public enumerator_ `Break`
- L876 _public enumerator_ `Return`

#### struct `CrossCompiler::AST::FJumpStatement`  
`struct FJumpStatement : public FNode`  
_L880-890_
- inherits: `FNode`
- L882 _public prototype_ `FJumpStatement(FLinearAllocator* InAllocator, EJumpType InType, const FSourceInfo& InInfo);`
- L883 _public prototype_ `~FJumpStatement();`
- L885 _public member_ `EJumpType Type;`
- L886 _public member_ `FExpression* OptionalExpression;`
- L888 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L889 _public function_ `virtual FJumpStatement* AsJumpStatement() override`

#### struct `CrossCompiler::AST::FFunctionDefinition`  
`struct FFunctionDefinition : public FNode`  
_L892-902_
- inherits: `FNode`
- L894 _public prototype_ `FFunctionDefinition(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L895 _public prototype_ `~FFunctionDefinition();`
- L897 _public member_ `FFunction* Prototype;`
- L898 _public member_ `FCompoundStatement* Body;`
- L900 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L901 _public function_ `virtual FFunctionDefinition* AsFunctionDefinition() override`

#### struct `CrossCompiler::AST::FAttributeArgument`  
`struct FAttributeArgument : public FNode`  
_L904-913_
- inherits: `FNode`
- L906 _public prototype_ `FAttributeArgument(FLinearAllocator* InAllocator, const FSourceInfo& InInfo);`
- L907 _public prototype_ `~FAttributeArgument();`
- L909 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L911 _public member_ `const TCHAR* StringArgument;`
- L912 _public member_ `FExpression* ExpressionArgument;`

#### struct `CrossCompiler::AST::FAttribute`  
`struct FAttribute : public FNode`  
_L915-924_
- inherits: `FNode`
- L917 _public prototype_ `FAttribute(FLinearAllocator* Allocator, const FSourceInfo& InInfo, const TCHAR* InName);`
- L918 _public prototype_ `~FAttribute();`
- L920 _public prototype_ `virtual void Write(FASTWriter& Writer) const override;`
- L922 _public member_ `const TCHAR* Name;`
- L923 _public member_ `TLinearArray<FAttributeArgument*> Arguments;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace CrossCompiler`
- L15 _namespace_ `namespace AST` (scope `CrossCompiler`)
- L155 _member_ `uint32 U;` (scope `CrossCompiler::AST::FASTWriter::operator <<::__anona7eac615010a`)
- L156 _member_ `int32 I;` (scope `CrossCompiler::AST::FASTWriter::operator <<::__anona7eac615010a`)
- L362 _function_ `inline EOperators TokenToASTOperator(EHlslToken Token)` (scope `CrossCompiler::AST`)
- L485 _member_ `ELiteralType LiteralType;` (scope `CrossCompiler::AST::FExpression::__anona7eac615020a`)
- L486 _member_ `struct FTypeSpecifier* TypeSpecifier;` (scope `CrossCompiler::AST::FExpression::__anona7eac615020a`)
- L623 _member_ `uint32 bIsStatic : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L624 _member_ `uint32 bConstant : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L625 _member_ `uint32 bIn : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L626 _member_ `uint32 bOut : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L627 _member_ `uint32 bRowMajor : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L628 _member_ `uint32 bShared : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L629 _member_ `uint32 bUniform : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L632 _member_ `uint32 bLinear : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`) — Interpolation modifiers
- L633 _member_ `uint32 bCentroid : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L634 _member_ `uint32 bSample : 1;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a::__anona7eac6150408`)
- L636 _member_ `uint32 Raw;` (scope `CrossCompiler::AST::FTypeQualifier::__anona7eac615030a`)
- L926 _function_ `static inline bool IsAssignmentOperator(EOperators Operator)` (scope `CrossCompiler::AST`)

### `Source/Developer/HlslParser/Private/HlslExpressionParser.inl` (Private)


#### struct `CrossCompiler::FSymbolScope`  
`struct FSymbolScope`  
_L28-174_
- L45 _public member_ `const EType ScopeType;` — Type tag is for debugging
- L47 _public member_ `FLinearAllocator* Allocator;`
- L48 _public member_ `FSymbolScope* Parent;`
- L49 _public member_ `const TCHAR* Name;`
- L51 _public member_ `TSet <FString> Symbols;`
- L52 _public member_ `TLinearArray<FSymbolScope> Children;`
- L66 _public member_ `TMap<FStringView, CrossCompiler::AST::FIdentifier*, FDefaultSetAllocator, FIdentifierKeyFuncs> Identifiers;`
- L68 _public function_ `FSymbolScope(FLinearAllocator* InAllocator, FSymbolScope* InParent, EType InScopeType) : ScopeType(InScopeType) , Allocator(InAllocator) , Parent(InParent) , Name(nullptr) , Children(InAllocator)`
- L76 _public prototype_ `~FSymbolScope() = default;`
- L78 _public function_ `FORCENOINLINE void Add(const FString& Type)`
- L83 _public function_ `FORCENOINLINE void Add(FStringView Type)`
- L88 _public function_ `FORCENOINLINE void Add(const TCHAR* Type)`
- L93 _public function_ `CrossCompiler::AST::FIdentifier* FindExistingIdentifier(uint32 IdentifierHash, FStringView Identifier, bool bSearchUpwards)`
- L109 _public function_ `CrossCompiler::AST::FIdentifier* FindOrAddIdentifier(FStringView IdentifierName)`
- L126 _public function_ `static bool FindType(const FSymbolScope* Scope, const FString& Type, bool bSearchUpwards = true)`
- L146 _public function_ `const FSymbolScope* FindNamespace(const TCHAR* Namespace) const`
- L159 _public function_ `static const FSymbolScope* FindGlobalNamespace(const TCHAR* Namespace, const FSymbolScope* Scope)`
- L164 _public function_ `const FSymbolScope* GetGlobalScope() const`

#### enum `CrossCompiler::FSymbolScope::EType`  
`enum class EType`  
_L30-42_
- L32 _public enumerator_ `Unknown`
- L33 _public enumerator_ `Global`
- L34 _public enumerator_ `Namespace`
- L35 _public enumerator_ `Statement`
- L36 _public enumerator_ `Do`
- L37 _public enumerator_ `While`
- L38 _public enumerator_ `For`
- L39 _public enumerator_ `If`
- L40 _public enumerator_ `ScopedDeclaration`
- L41 _public enumerator_ `Function`

#### struct `CrossCompiler::FSymbolScope::FIdentifierKeyFuncs`  
`struct FIdentifierKeyFuncs : public DefaultKeyFuncs<FStringView>`  
_L54-64_
- inherits: `DefaultKeyFuncs<FStringView>`
- L56 _public function_ `static FStringView GetSetKey(FStringView K)`
- L58 _public function_ `template <typename T> static FStringView GetSetKey(const TPair<FStringView, T>& P)`
- L59 _public function_ `static bool Matches(FStringView A, FStringView B)`
- L60 _public function_ `static uint32 GetKeyHash(FStringView Key)`

#### struct `CrossCompiler::FCreateSymbolScope`  
`struct FCreateSymbolScope`  
_L188-207_
- L192 _public member_ `FSymbolScope* Original;`
- L193 _public member_ `FSymbolScope** Current;`
- L195 _public function_ `FCreateSymbolScope(FLinearAllocator* InAllocator, FSymbolScope** InCurrent, FSymbolScope::EType ScopeType) : Current(InCurrent)`
- L203 _public function_ `~FCreateSymbolScope()`

#### enum `CrossCompiler::ETypeFlags`  
`enum ETypeFlags`  
_L258-266_
- L260 _public enumerator_ `ETF_VOID = 1 << 0`
- L261 _public enumerator_ `ETF_BUILTIN_NUMERIC = 1 << 1`
- L262 _public enumerator_ `ETF_SAMPLER_TEXTURE_BUFFER = 1 << 2`
- L263 _public enumerator_ `ETF_USER_TYPES = 1 << 3`
- L264 _public enumerator_ `ETF_ERROR_IF_NOT_USER_TYPE = 1 << 4`
- L265 _public enumerator_ `ETF_UNORM = 1 << 5`

#### enum `CrossCompiler::EExtraQualifiers`  
`enum EExtraQualifiers`  
_L268-273_
- L270 _public enumerator_ `EEQ_PRECISE = 1 << 0`
- L271 _public enumerator_ `EEQ_UNORM = 1 << 1`
- L272 _public enumerator_ `EEQ_SNORM = 1 << 2`

#### enum `CrossCompiler::EExpressionFlags`  
`enum EExpressionFlags`  
_L275-278_
- L277 _public enumerator_ `EEF_ALLOW_ASSIGNMENT = 1 << 0`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace CrossCompiler`
- L20 _prototype_ `EParseResult ParseResultError();` (scope `CrossCompiler`)
- L25 _prototype_ `EParseResult ComputeExpr(FHlslScanner& Scanner, int32 MinPrec, FSymbolScope* SymbolScope, int32 ExpressionFlags, FLinearAllocator* Allocator, AST::FExpression** OutExpression, AST::FExpression** OutTernaryExpression);` (scope `CrossCompiler`)
- L26 _prototype_ `EParseResult ParseExpressionList(EHlslToken EndListToken, FHlslScanner& Scanner, FSymbolScope* SymbolScope, EHlslToken NewStartListToken, FLinearAllocator* Allocator, AST::FExpression* OutExpression);` (scope `CrossCompiler`)
- L27 _prototype_ `EParseResult ParseExpression(FHlslScanner& Scanner, FSymbolScope* SymbolScope, int32 ExpressionFlags, FLinearAllocator* Allocator, AST::FExpression** OutExpression);` (scope `CrossCompiler`)
- L176 _function_ `inline AST::FIdentifier* FindOrAddIdentifier(FLinearAllocator* Allocator, FSymbolScope* SymbolScope, FStringView IdentifierName)` (scope `CrossCompiler`)
- L280 _function_ `EParseResult ParseGeneralTypeToken(const FHlslToken* Token, int32 TypeFlags, int32 ExtraQualifierFlags, FLinearAllocator* Allocator, AST::FTypeSpecifier** OutSpecifier)` (scope `CrossCompiler`)
- L533 _function_ `EParseResult ParseGeneralTypeFromToken(const FHlslToken* Token, int32 TypeFlags, int32 ExtraQualifierFlags, FSymbolScope* SymbolScope, FLinearAllocator* Allocator, AST::FTypeSpecifier** OutSpecifier)` (scope `CrossCompiler`)
- L567 _function_ `EParseResult ParseGeneralType(FHlslScanner& Scanner, int32 TypeFlags, FSymbolScope* SymbolScope, FLinearAllocator* Allocator, AST::FTypeSpecifier** OutSpecifier)` (scope `CrossCompiler`)
- L670 _function_ `EParseResult ParseFullType(FHlslScanner& Scanner, int32 TypeFlags, int32 TemplateTypeFlags, FSymbolScope* SymbolScope, FLinearAllocator* Allocator, AST::FFullySpecifiedType** OutFullySpecifiedType)` (scope `CrossCompiler`)
- L720 _function_ `EParseResult MatchUnaryOperator(FHlslScanner& Scanner, FSymbolScope* SymbolScope, FLinearAllocator* Allocator, AST::FExpression** OuterExpression, AST::FExpression** InnerExpression)` (scope `CrossCompiler`) — Unary!(Unary-(Unary+())) would have ! as Top, and + as Inner
- L777 _function_ `` (scope `CrossCompiler::MatchUnaryOperator`)
- L860 _function_ `EParseResult MatchSuffixOperator(FHlslScanner& Scanner, FSymbolScope* SymbolScope, int32 ExpressionFlags, FLinearAllocator* Allocator, AST::FExpression** InOutExpression, AST::FExpression** OutTernaryExpression)` (scope `CrossCompiler`)
- L1088 _function_ `EParseResult ComputeAtom(FHlslScanner& Scanner, FSymbolScope* SymbolScope, int32 ExpressionFlags, FLinearAllocator* Allocator, AST::FExpression** OutExpression, AST::FExpression** OutTernaryExpression)` (scope `CrossCompiler`)
- L1099 _function_ `` (scope `CrossCompiler::ComputeAtom`)
- L1271 _function_ `int32 GetPrecedence(const FHlslToken* Token)` (scope `CrossCompiler`)
- L1342 _function_ `bool IsTernaryOperator(const FHlslToken* Token)` (scope `CrossCompiler`)
- L1347 _function_ `bool IsBinaryOperator(const FHlslToken* Token)` (scope `CrossCompiler`)
- L1352 _function_ `bool IsAssignmentOperator(const FHlslToken* Token)` (scope `CrossCompiler`)
- L1379 _function_ `static inline bool IsSequenceOperator(const FHlslToken* Token)` (scope `CrossCompiler`)
- L1388 _function_ `bool IsRightAssociative(const FHlslToken* Token)` (scope `CrossCompiler`)
- L1395 _function_ `EParseResult ComputeExpr(FHlslScanner& Scanner, int32 MinPrec, FSymbolScope* SymbolScope, int32 ExpressionFlags, FLinearAllocator* Allocator, AST::FExpression** OutExpression, AST::FExpression** OutTernaryExpression)` (scope `CrossCompiler`) — Ternary is handled by popping out so it can right associate #todo-rco: Fix the case for right-associative assignment operators
- L1488 _function_ `EParseResult ParseExpression(FHlslScanner& Scanner, FSymbolScope* SymbolScope, int32 ExpressionFlags, FLinearAllocator* Allocator, AST::FExpression** OutExpression)` (scope `CrossCompiler`)
- L1494 _function_ `EParseResult ParseExpressionList2(FHlslScanner& Scanner, FSymbolScope* SymbolScope, FLinearAllocator* Allocator, AST::FExpressionList::EType ExpressionType, AST::FExpression** OutExpression)` (scope `CrossCompiler`)
- L1557 _function_ `EParseResult ParseExpressionList(EHlslToken EndListToken, FHlslScanner& Scanner, FSymbolScope* SymbolScope, EHlslToken NewStartListToken, FLinearAllocator* Allocator, AST::FExpression* OutExpression)` (scope `CrossCompiler`)
- L1617 _function_ `EParseResult ParseResultError()` (scope `CrossCompiler`)

### `Source/Developer/HlslParser/Private/HlslLexer.h` (Private)


#### enum `CrossCompiler::EHlslToken`  
`enum class EHlslToken`  
_L17-310_
- L20 _public enumerator_ `Invalid` — Control
- L21 _public enumerator_ `Pragma`
- L24 _public enumerator_ `Plus` — Math
- L25 _public enumerator_ `PlusEqual`
- L26 _public enumerator_ `Minus`
- L27 _public enumerator_ `MinusEqual`
- L28 _public enumerator_ `Times`
- L29 _public enumerator_ `TimesEqual`
- L30 _public enumerator_ `Div`
- L31 _public enumerator_ `DivEqual`
- L32 _public enumerator_ `Mod`
- L33 _public enumerator_ `ModEqual`
- L34 _public enumerator_ `LeftParenthesis`
- L35 _public enumerator_ `RightParenthesis`
- L38 _public enumerator_ `EqualEqual` — Logical
- L39 _public enumerator_ `NotEqual`
- L40 _public enumerator_ `Lower`
- L41 _public enumerator_ `LowerEqual`
- L42 _public enumerator_ `Greater`
- L43 _public enumerator_ `GreaterEqual`
- L44 _public enumerator_ `AndAnd`
- L45 _public enumerator_ `OrOr`
- L48 _public enumerator_ `LowerLower` — Bit
- L49 _public enumerator_ `LowerLowerEqual`
- L50 _public enumerator_ `GreaterGreater`
- L51 _public enumerator_ `GreaterGreaterEqual`
- L52 _public enumerator_ `And`
- L53 _public enumerator_ `AndEqual`
- L54 _public enumerator_ `Or`
- L55 _public enumerator_ `OrEqual`
- L56 _public enumerator_ `Xor`
- L57 _public enumerator_ `XorEqual`
- L58 _public enumerator_ `Not`
- L59 _public enumerator_ `Neg`
- L62 _public enumerator_ `Equal` — Statements
- L63 _public enumerator_ `LeftBrace`
- L64 _public enumerator_ `RightBrace`
- L65 _public enumerator_ `Semicolon`
- L66 _public enumerator_ `If`
- L67 _public enumerator_ `Else`
- L68 _public enumerator_ `For`
- L69 _public enumerator_ `While`
- L70 _public enumerator_ `Do`
- L71 _public enumerator_ `Return`
- L72 _public enumerator_ `Switch`
- L73 _public enumerator_ `Case`
- L74 _public enumerator_ `Break`
- L75 _public enumerator_ `Default`
- L76 _public enumerator_ `Continue`
- L77 _public enumerator_ `Goto`
- L80 _public enumerator_ `PlusPlus` — Unary
- L81 _public enumerator_ `MinusMinus`
- L84 _public enumerator_ `Void` — Types
- L85 _public enumerator_ `Const`
- L86 _public enumerator_ `Precise`
- L88 _public enumerator_ `Bool`
- L89 _public enumerator_ `Bool1`
- L90 _public enumerator_ `Bool2`
- L91 _public enumerator_ `Bool3`
- L92 _public enumerator_ `Bool4`
- L93 _public enumerator_ `Bool1x1`
- L94 _public enumerator_ `Bool2x1`
- L95 _public enumerator_ `Bool3x1`
- L96 _public enumerator_ `Bool4x1`
- L97 _public enumerator_ `Bool1x2`
- L98 _public enumerator_ `Bool2x2`
- L99 _public enumerator_ `Bool3x2`
- L100 _public enumerator_ `Bool4x2`
- L101 _public enumerator_ `Bool1x3`
- L102 _public enumerator_ `Bool2x3`
- L103 _public enumerator_ `Bool3x3`
- L104 _public enumerator_ `Bool4x3`
- L105 _public enumerator_ `Bool1x4`
- L106 _public enumerator_ `Bool2x4`
- L107 _public enumerator_ `Bool3x4`
- L108 _public enumerator_ `Bool4x4`
- L110 _public enumerator_ `Int`
- L111 _public enumerator_ `Int1`
- L112 _public enumerator_ `Int2`
- L113 _public enumerator_ `Int3`
- L114 _public enumerator_ `Int4`
- L115 _public enumerator_ `Int1x1`
- L116 _public enumerator_ `Int2x1`
- L117 _public enumerator_ `Int3x1`
- L118 _public enumerator_ `Int4x1`
- L119 _public enumerator_ `Int1x2`
- L120 _public enumerator_ `Int2x2`
- L121 _public enumerator_ `Int3x2`
- L122 _public enumerator_ `Int4x2`
- L123 _public enumerator_ `Int1x3`
- L124 _public enumerator_ `Int2x3`
- L125 _public enumerator_ `Int3x3`
- L126 _public enumerator_ `Int4x3`
- L127 _public enumerator_ `Int1x4`
- L128 _public enumerator_ `Int2x4`
- L129 _public enumerator_ `Int3x4`
- L130 _public enumerator_ `Int4x4`
- L132 _public enumerator_ `Uint`
- L133 _public enumerator_ `Uint1`
- L134 _public enumerator_ `Uint2`
- L135 _public enumerator_ `Uint3`
- L136 _public enumerator_ `Uint4`
- L137 _public enumerator_ `Uint1x1`
- L138 _public enumerator_ `Uint2x1`
- L139 _public enumerator_ `Uint3x1`
- L140 _public enumerator_ `Uint4x1`
- L141 _public enumerator_ `Uint1x2`
- L142 _public enumerator_ `Uint2x2`
- L143 _public enumerator_ `Uint3x2`
- L144 _public enumerator_ `Uint4x2`
- L145 _public enumerator_ `Uint1x3`
- L146 _public enumerator_ `Uint2x3`
- L147 _public enumerator_ `Uint3x3`
- L148 _public enumerator_ `Uint4x3`
- L149 _public enumerator_ `Uint1x4`
- L150 _public enumerator_ `Uint2x4`
- L151 _public enumerator_ `Uint3x4`
- L152 _public enumerator_ `Uint4x4`
- L154 _public enumerator_ `Uint64_t`
- L155 _public enumerator_ `Uint64_t1`
- L156 _public enumerator_ `Uint64_t2`
- L157 _public enumerator_ `Uint64_t3`
- L158 _public enumerator_ `Uint64_t4`
- L159 _public enumerator_ `Uint64_t1x1`
- L160 _public enumerator_ `Uint64_t2x1`
- L161 _public enumerator_ `Uint64_t3x1`
- L162 _public enumerator_ `Uint64_t4x1`
- L163 _public enumerator_ `Uint64_t1x2`
- L164 _public enumerator_ `Uint64_t2x2`
- L165 _public enumerator_ `Uint64_t3x2`
- L166 _public enumerator_ `Uint64_t4x2`
- L167 _public enumerator_ `Uint64_t1x3`
- L168 _public enumerator_ `Uint64_t2x3`
- L169 _public enumerator_ `Uint64_t3x3`
- L170 _public enumerator_ `Uint64_t4x3`
- L171 _public enumerator_ `Uint64_t1x4`
- L172 _public enumerator_ `Uint64_t2x4`
- L173 _public enumerator_ `Uint64_t3x4`
- L174 _public enumerator_ `Uint64_t4x4`
- L176 _public enumerator_ `Half`
- L177 _public enumerator_ `Half1`
- L178 _public enumerator_ `Half2`
- L179 _public enumerator_ `Half3`
- L180 _public enumerator_ `Half4`
- L181 _public enumerator_ `Half1x1`
- L182 _public enumerator_ `Half2x1`
- L183 _public enumerator_ `Half3x1`
- L184 _public enumerator_ `Half4x1`
- L185 _public enumerator_ `Half1x2`
- L186 _public enumerator_ `Half2x2`
- L187 _public enumerator_ `Half3x2`
- L188 _public enumerator_ `Half4x2`
- L189 _public enumerator_ `Half1x3`
- L190 _public enumerator_ `Half2x3`
- L191 _public enumerator_ `Half3x3`
- L192 _public enumerator_ `Half4x3`
- L193 _public enumerator_ `Half1x4`
- L194 _public enumerator_ `Half2x4`
- L195 _public enumerator_ `Half3x4`
- L196 _public enumerator_ `Half4x4`
- L198 _public enumerator_ `Min16Float`
- L199 _public enumerator_ `Min16Float1`
- L200 _public enumerator_ `Min16Float2`
- L201 _public enumerator_ `Min16Float3`
- L202 _public enumerator_ `Min16Float4`
- L203 _public enumerator_ `Min16Float1x1`
- L204 _public enumerator_ `Min16Float2x1`
- L205 _public enumerator_ `Min16Float3x1`
- L206 _public enumerator_ `Min16Float4x1`
- L207 _public enumerator_ `Min16Float1x2`
- L208 _public enumerator_ `Min16Float2x2`
- L209 _public enumerator_ `Min16Float3x2`
- L210 _public enumerator_ `Min16Float4x2`
- L211 _public enumerator_ `Min16Float1x3`
- L212 _public enumerator_ `Min16Float2x3`
- L213 _public enumerator_ `Min16Float3x3`
- L214 _public enumerator_ `Min16Float4x3`
- L215 _public enumerator_ `Min16Float1x4`
- L216 _public enumerator_ `Min16Float2x4`
- L217 _public enumerator_ `Min16Float3x4`
- L218 _public enumerator_ `Min16Float4x4`
- L220 _public enumerator_ `Float`
- L221 _public enumerator_ `Float1`
- L222 _public enumerator_ `Float2`
- L223 _public enumerator_ `Float3`
- L224 _public enumerator_ `Float4`
- L225 _public enumerator_ `Float1x1`
- L226 _public enumerator_ `Float2x1`
- L227 _public enumerator_ `Float3x1`
- L228 _public enumerator_ `Float4x1`
- L229 _public enumerator_ `Float1x2`
- L230 _public enumerator_ `Float2x2`
- L231 _public enumerator_ `Float3x2`
- L232 _public enumerator_ `Float4x2`
- L233 _public enumerator_ `Float1x3`
- L234 _public enumerator_ `Float2x3`
- L235 _public enumerator_ `Float3x3`
- L236 _public enumerator_ `Float4x3`
- L237 _public enumerator_ `Float1x4`
- L238 _public enumerator_ `Float2x4`
- L239 _public enumerator_ `Float3x4`
- L240 _public enumerator_ `Float4x4`
- L242 _public enumerator_ `Texture` — texture (SM3)
- L243 _public enumerator_ `Texture1D`
- L244 _public enumerator_ `Texture1DArray`
- L245 _public enumerator_ `Texture2D`
- L246 _public enumerator_ `Texture2DArray`
- L247 _public enumerator_ `Texture2DMS`
- L248 _public enumerator_ `Texture2DMSArray`
- L249 _public enumerator_ `Texture3D`
- L250 _public enumerator_ `TextureCube`
- L251 _public enumerator_ `TextureCubeArray`
- L253 _public enumerator_ `Sampler` — sampler (SM3)
- L254 _public enumerator_ `Sampler1D` — sampler1D (SM3)
- L255 _public enumerator_ `Sampler2D` — sampler2D (SM3)
- L256 _public enumerator_ `Sampler3D` — sampler3D (SM3)
- L257 _public enumerator_ `SamplerCube` — samplerCUBE (SM3)
- L258 _public enumerator_ `SamplerState`
- L259 _public enumerator_ `SamplerComparisonState`
- L261 _public enumerator_ `Buffer`
- L262 _public enumerator_ `AppendStructuredBuffer`
- L263 _public enumerator_ `ByteAddressBuffer`
- L264 _public enumerator_ `ConsumeStructuredBuffer`
- L265 _public enumerator_ `RWBuffer`
- L266 _public enumerator_ `RWByteAddressBuffer`
- L267 _public enumerator_ `RWStructuredBuffer`
- L268 _public enumerator_ `RWTexture1D`
- L269 _public enumerator_ `RWTexture1DArray`
- L270 _public enumerator_ `RWTexture2D`
- L271 _public enumerator_ `RWTexture2DArray`
- L272 _public enumerator_ `RasterizerOrderedTexture2D`
- L273 _public enumerator_ `RWTexture3D`
- L274 _public enumerator_ `StructuredBuffer`
- L275 _public enumerator_ `ConstantBuffer`
- L276 _public enumerator_ `RaytracingAccelerationStructure`
- L279 _public enumerator_ `In` — Modifiers
- L280 _public enumerator_ `Out`
- L281 _public enumerator_ `InOut`
- L282 _public enumerator_ `Static`
- L283 _public enumerator_ `Uniform`
- L286 _public enumerator_ `LeftSquareBracket` — Misc
- L287 _public enumerator_ `RightSquareBracket`
- L288 _public enumerator_ `Question`
- L289 _public enumerator_ `Colon`
- L290 _public enumerator_ `ColonColon`
- L291 _public enumerator_ `Comma`
- L292 _public enumerator_ `Dot`
- L293 _public enumerator_ `Struct`
- L294 _public enumerator_ `CBuffer`
- L295 _public enumerator_ `GroupShared`
- L296 _public enumerator_ `RowMajor`
- L297 _public enumerator_ `Register`
- L298 _public enumerator_ `Inline`
- L299 _public enumerator_ `Typedef`
- L300 _public enumerator_ `PackOffset`
- L301 _public enumerator_ `Namespace`
- L303 _public enumerator_ `Identifier`
- L304 _public enumerator_ `Operator` — HLSL2021
- L305 _public enumerator_ `Literal`
- L306 _public enumerator_ `BoolConstant`
- L307 _public enumerator_ `StringConstant` — C-style "string"
- L308 _public enumerator_ `StaticAssert` — _Static_assert (HLSL), static_assert (C++11)
- L309 _public enumerator_ `C99Pragma` — _Pragma (C99/C++11)

#### enum `CrossCompiler::ELiteralType`  
`enum class ELiteralType`  
_L312-324_
- L314 _public enumerator_ `Unknown = -1`
- L316 _public enumerator_ `Float` — All variations
- L317 _public enumerator_ `FloatSuffix` — All variations, ends with 'f'
- L318 _public enumerator_ `Integer` — Just digits
- L319 _public enumerator_ `IntegerSuffix` — has a 'u|U|l|L' suffix
- L320 _public enumerator_ `Hex` — has '0x' or '0X' prefix
- L321 _public enumerator_ `HexSuffix` — Hex + has a 'u|U|l|L' suffix
- L322 _public enumerator_ `Octal` — 0[0..7]+
- L323 _public enumerator_ `Bool` — true or false

#### struct `CrossCompiler::FHlslToken`  
`struct FHlslToken`  
_L343-366_
- L345 _public member_ `EHlslToken Token;`
- L346 _public member_ `ELiteralType LiteralType = ELiteralType::Unknown;`
- L347 _public member_ `FString String;` — yuriy-todo: allocate this from linear allocator or simply point to the input source code and use FStringView
- L348 _public member_ `FSourceInfo SourceInfo;`
- L350 _public function_ `explicit FHlslToken(FStringView Identifier) : Token(EHlslToken::Identifier), String(Identifier)`
- L351 _public function_ `explicit FHlslToken(EHlslToken InToken, FStringView Identifier) : Token(InToken), String(Identifier)`
- L352 _public function_ `explicit FHlslToken(FStringView InLiteral, ELiteralType InLiteralType) : Token(EHlslToken::Literal), LiteralType(InLiteralType), String(InLiteral)`
- L358 _public function_ `void DebugId()`

#### class `CrossCompiler::FHlslScanner`  
`class FHlslScanner`  
_L368-409_
- L371 _public prototype_ `FHlslScanner(FCompilerMessages& InCompilerMessages);`
- L372 _public prototype_ `virtual ~FHlslScanner();`
- L375 _public prototype_ `bool Lex(const FString& String, const FString& Filename);` — Processing
- L376 _public prototype_ `void Dump();`
- L379 _public function_ `uint32 GetCurrentTokenIndex() const` — Iterating after Processing
- L384 _public prototype_ `void SetCurrentTokenIndex(uint32 NewToken);`
- L386 _public prototype_ `bool HasMoreTokens() const;`
- L387 _public prototype_ `bool MatchToken(EHlslToken InToken);`
- L388 _public prototype_ `bool MatchIntegerLiteral();`
- L389 _public prototype_ `const FHlslToken* PeekToken(uint32 LookAhead = 0) const;`
- L390 _public prototype_ `const FHlslToken* GetCurrentToken() const;`
- L391 _public function_ `void Advance()`
- L393 _public prototype_ `void SourceError(const FString& Error);`
- L396 _private member_ `FCompilerMessages& CompilerMessages;`
- L398 _private member_ `TArray<FHlslToken> Tokens;`
- L399 _private prototype_ `void EmplaceToken(FHlslToken&& Token, const struct FTokenizer& Tokenizer);`
- L401 _private member_ `uint32 CurrentToken;`
- L404 _private member_ `TIndirectArray<FString> SourceFilenames;` — Tokens point their source filenames here
- L406 _private prototype_ `void Clear(const FString& Filename);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace CrossCompiler`
- L326 _function_ `static inline bool IsIntegerType(ELiteralType Type)` (scope `CrossCompiler`)

### `Source/Developer/HlslParser/Private/HlslParser.h` (Private)


#### enum `CrossCompiler::EParseResult`  
`enum class EParseResult`  
_L29-35_
- L31 _public enumerator_ `Matched`
- L32 _public enumerator_ `NotMatched`
- L33 _public enumerator_ `Ignore`
- L34 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace HlslParser` (scope `UE`)
- L19 _namespace_ `namespace CrossCompiler`
- L24 _namespace_ `namespace AST` (scope `CrossCompiler`)
- L37 _namespace_ `namespace Parser` (scope `CrossCompiler`)
- L39 _typedef_ `typedef void TCallback(void* CallbackData, CrossCompiler::FLinearAllocator* Allocator, CrossCompiler::TLinearArray<CrossCompiler::AST::FNode*>& ASTNodes);` (scope `CrossCompiler::Parser`)
- L42 _prototype_ `bool Parse(const FString& Input, const FString& Filename, FCompilerMessages& OutCompilerMessages, TConstArrayView<UE::HlslParser::FScopedDeclarations> InScopedDeclarations, TCallback* Callback, void* CallbackData = nullptr);` (scope `CrossCompiler::Parser`) — Returns true if successfully parsed
- L45 _prototype_ `bool Parse(const FString& Input, const FString& Filename, FCompilerMessages& OutCompilerMessages, TConstArrayView<UE::HlslParser::FScopedDeclarations> InScopedDeclarations, TFunction< void(CrossCompiler::FLinearAllocator* Allocator, CrossCompiler::TLinearArray<CrossCompiler::AST::FNode*>& ASTNodes)> Function);` (scope `CrossCompiler::Parser`) — Returns true if successfully parsed
- L48 _prototype_ `bool Parse(const FString& Input, const FString& Filename, FCompilerMessages& OutCompilerMessages, TConstArrayView<UE::HlslParser::FScopedDeclarations> InScopedDeclarations, CrossCompiler::FNodeContainer& OutContainer);` (scope `CrossCompiler::Parser`) — Returns true if successfully parsed
- L51 _prototype_ `void WriteNodesToString(void* OutFStringPointer, CrossCompiler::FLinearAllocator* Allocator, CrossCompiler::TLinearArray<CrossCompiler::AST::FNode*>& ASTNodes);` (scope `CrossCompiler::Parser`) — Sample callback to write out all nodes into a string; pass a valid pointer FString* as OutFStringPointer

### `Source/Developer/HlslParser/Private/HlslUtils.h` (Private)


#### struct `CrossCompiler::Memory::FPage`  
`struct FPage`  
_L25-46_
- L27 _public member_ `int8* Current;`
- L28 _public member_ `int8* Begin;`
- L29 _public member_ `int8* End;`
- L31 _public function_ `FPage(SIZE_T Size)`
- L39 _public function_ `~FPage()`
- L44 _public prototype_ `static FPage* AllocatePage(SIZE_T PageSize);`
- L45 _public prototype_ `static void FreePage(FPage* Page);`

#### enum `CrossCompiler::Memory::(anonymous)`  
``  
_L49-51_

#### struct `CrossCompiler::FLinearAllocator`  
`struct FLinearAllocator`  
_L54-121_
- L58 _public function_ `FLinearAllocator()`
- L64 _public function_ `~FLinearAllocator()`
- L72 _public function_ `inline void* Alloc(SIZE_T NumBytes)`
- L87 _public function_ `inline void* Alloc(SIZE_T NumBytes, SIZE_T Align)`
- L95 _public function_ `TCHAR* Strdup(const TCHAR* String, int32 Length = -1)`
- L115 _public function_ `inline TCHAR* Strdup(const FStringView String)`
- L120 _public member_ `TArray<Memory::FPage*, TInlineAllocator<8> > Pages;`

#### class `CrossCompiler::FLinearAllocatorPolicy`  
`class FLinearAllocatorPolicy`  
_L124-204_
- L127 _public typedef_ `using SizeType = int32;`
- L203 _public typedef_ `typedef ForElementType<FScriptContainerElement> ForAnyElementType;`

#### enum `CrossCompiler::FLinearAllocatorPolicy::(anonymous)`  
`enum`  
_L130-130_
- desc: Unreal allocator magic

#### enum `CrossCompiler::FLinearAllocatorPolicy::(anonymous)`  
`enum`  
_L131-131_

#### class `CrossCompiler::FLinearAllocatorPolicy::ForElementType`  
`template<typename ElementType> class ForElementType`  
_L134-201_
- L139 _public function_ `ForElementType() : LinearAllocator(nullptr), Data(nullptr)` — Default constructor.
- L145 _public function_ `ElementType* GetAllocation() const` — FContainerAllocatorInterface
- L149 _public function_ `void ResizeAllocation(SizeType CurrentNum, SizeType NewMax, SIZE_T NumBytesPerElement)`
- L167 _public function_ `SizeType CalculateSlackReserve(SizeType NewMax, SIZE_T NumBytesPerElement) const`
- L171 _public function_ `SizeType CalculateSlackShrink(SizeType NewMax, SizeType CurrentMax, SIZE_T NumBytesPerElement) const`
- L175 _public function_ `SizeType CalculateSlackGrow(SizeType NewMax, SizeType CurrentMax, SIZE_T NumBytesPerElement) const`
- L180 _public function_ `SIZE_T GetAllocatedSize(SizeType CurrentMax, SIZE_T NumBytesPerElement) const`
- L185 _public function_ `bool HasAllocation() const`
- L190 _public function_ `SizeType GetInitialCapacity() const`
- L195 _public member_ `FLinearAllocator* LinearAllocator;`
- L200 _private member_ `ElementType* Data;` — A pointer to the container's elements.

#### class `CrossCompiler::FLinearBitArrayAllocator`  
`class FLinearBitArrayAllocator : public TInlineAllocator<4, FLinearAllocatorPolicy>`  
_L206-209_
- inherits: `TInlineAllocator<4,FLinearAllocatorPolicy>`

#### class `CrossCompiler::FLinearSparseArrayAllocator`  
`class FLinearSparseArrayAllocator : public TSparseArrayAllocator<FLinearAllocatorPolicy, FLinearBitArrayAllocator>`  
_L211-214_
- inherits: `TSparseArrayAllocator<FLinearAllocatorPolicy,FLinearBitArrayAllocator>`

#### class `CrossCompiler::FLinearSetAllocator`  
`class FLinearSetAllocator : public TSetAllocator<FLinearSparseArrayAllocator, TInlineAllocator<1, FLinearAllocatorPolicy> >`  
_L216-219_
- inherits: `TSetAllocator<FLinearSparseArrayAllocator,TInlineAllocator<1,FLinearAllocatorPolicy>>`

#### class `CrossCompiler::TLinearArray`  
`template <typename TType> class TLinearArray : public TArray<TType, FLinearAllocatorPolicy>`  
_L222-229_
- inherits: `TArray<TType,FLinearAllocatorPolicy>`
- L225 _public function_ `TLinearArray(FLinearAllocator* Allocator)`

#### struct `CrossCompiler::FNodeContainer`  
`struct FNodeContainer`  
_L231-250_
- L235 _public function_ `FNodeContainer() : Nodes(&Allocator)`
- L241 _public function_ `template <typename T, typename... ArgsType> T* AllocNode(ArgsType&&... Args)`
- L248 _public member_ `FLinearAllocator Allocator;`
- L249 _public member_ `TLinearArray<CrossCompiler::AST::FNode*> Nodes;`

#### struct `CrossCompiler::FSourceInfo`  
`struct FSourceInfo`  
_L263-270_
- L265 _public member_ `FString* Filename;`
- L266 _public member_ `int32 Line;`
- L267 _public member_ `int32 Column;`
- L269 _public function_ `FSourceInfo() : Filename(nullptr), Line(0), Column(0)`

#### struct `CrossCompiler::FCompilerMessages`  
`struct FCompilerMessages`  
_L272-326_
- L286 _public member_ `TArray<FMessage> MessageList;`
- L288 _public function_ `inline void AddMessage(bool bIsError, const FString& Message)`
- L293 _public function_ `inline void SourceError(const FSourceInfo& SourceInfo, const TCHAR* String)`
- L305 _public function_ `inline void SourceError(const TCHAR* String)`
- L310 _public function_ `inline void SourceWarning(const FSourceInfo& SourceInfo, const TCHAR* String)`
- L322 _public function_ `inline void SourceWarning(const TCHAR* String)`

#### struct `CrossCompiler::FCompilerMessages::FMessage`  
`struct FMessage`  
_L274-285_
- L277 _public member_ `bool bIsError;` — FSourceInfo SourceInfo;
- L278 _public member_ `FString Message;`
- L280 _public function_ `FMessage(bool bInIsError, const FString& InMessage) : bIsError(bInIsError), Message(InMessage)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define USE_UNREAL_ALLOCATOR 0`
- L12 _macro_ `#define USE_PAGE_POOLING 0`
- L14 _namespace_ `namespace CrossCompiler`
- L16 _namespace_ `namespace AST` (scope `CrossCompiler`)
- L23 _namespace_ `namespace Memory` (scope `CrossCompiler`)
- L50 _enumerator_ `MinPageSize = 64 * 1024` (scope `CrossCompiler::Memory::__anon9fd9d25e0103`)
- L130 _enumerator_ `enum { NeedsElementType = false }; enum { RequireRangeCheck = true }; template<typename ElementType> class ForElementType { public:` (scope `CrossCompiler::FLinearAllocatorPolicy::__anon9fd9d25e0203`) — Unreal allocator magic
- L131 _enumerator_ `enum { RequireRangeCheck = true }; template<typename ElementType> class ForElementType { public:` (scope `CrossCompiler::FLinearAllocatorPolicy::__anon9fd9d25e0303`)
