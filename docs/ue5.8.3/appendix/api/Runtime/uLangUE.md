# Runtime / uLangUE

- module root: `Source/Runtime/Solaris/uLangUE`
- headers: 3; symbols: 32
- symbol kinds: class=1, function=23, namespace=2, prototype=4, struct=1, typedef=1
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: uLangCore

### `Source/Runtime/Solaris/uLangUE/Public/SolarisLogging.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSolaris, Log, All);`

### `Source/Runtime/Solaris/uLangUE/Public/ULangUE.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace uLangUE`
- L8 _prototype_ `void Initialize();` (scope `uLangUE`)
- L9 _prototype_ `void DeInitialize();` (scope `uLangUE`)

### `Source/Runtime/Solaris/uLangUE/Public/ULangUEUtils.h` (Public)


#### class `FULangConversionUtils`  
`class FULangConversionUtils`  
_L15-141_
- L21 _public function_ `static inline uLang::CUTF8String FStringToULangStr(const FString& String)`
- L29 _public function_ `static inline uLang::CUTF8String FUtf8StringToULangStr(const FUtf8String& String)`
- L34 _public function_ `static inline uLang::CUTF8String TCharToULangStr(const TCHAR* Text)`
- L41 _public function_ `static inline uLang::CUTF8String FNameToULangStr(const FName& NameId)`
- L46 _public function_ `static inline uLang::CSymbol FNameToULangSymbol(const FName& NameId, uLang::CSymbolTable& uLangSymTable)`
- L51 _public function_ `static inline uLang::CSymbol TCharToULangSymbol(const TCHAR* Text, uLang::CSymbolTable& uLangSymTable)`
- L57 _public function_ `static inline uLang::CSymbol FStringToULangSymbol(const FString& String, uLang::CSymbolTable& uLangSymTable)`
- L66 _public function_ `static inline uLang::CUTF8StringView FUtf8StringViewToULangStringView(const FUtf8StringView& StringView)`
- L71 _public function_ `static inline uLang::CUTF8String FUtf8StringViewToULangString(const FUtf8StringView& StringView)`
- L78 _public function_ `static inline FString ULangStrToFString(const uLang::CUTF8String& ULangString)`
- L83 _public function_ `static inline FUtf8String ULangStrToFUtf8String(const uLang::CUTF8String& ULangString)`
- L89 _public prototype_ `template <typename CharType> static TString<CharType> ULangStrToTString(const uLang::CUTF8String& ULangString);`
- L92 _public function_ `template <> inline TString<TCHAR> ULangStrToTString<TCHAR>(const uLang::CUTF8String& ULangString)`
- L98 _public function_ `template <> inline TString<UTF8CHAR> ULangStrToTString<UTF8CHAR>(const uLang::CUTF8String& ULangString)`
- L103 _public function_ `static inline FName ULangStrToFName(const uLang::CUTF8String& ULangString)`
- L110 _public function_ `static inline FUtf8StringView ULangStringViewToFUtf8StringView(const uLang::CUTF8StringView& ULangStringView)`
- L115 _public function_ `static inline FUtf8StringView ULangStrToFUtf8StringView(const uLang::CUTF8String& ULangString)`
- L123 _public function_ `static inline FString UeToULangFunctionName(const FString& UEFunctionName)` — Converts a UE-style method name (UpperCamelCase) to uLang method name style (snake_case)
- L130 _public function_ `static inline FString UeToULangDataName(const FString& UEDataName)` — Converts a UE-style data member name (UpperCamelCase) to uLang data member name style (snake_case)
- L136 _public function_ `static inline FString UeToULangLocalVarName(const FString& UELocalVarName)` — Converts a UE-style local temporary variable / parameter name (UpperCamelCase) to uLang local temporary variable / parameter name style (snake_case)

#### struct `TuLangSymbolKeyFuncs`  
`template<typename ValueType> struct TuLangSymbolKeyFuncs : BaseKeyFuncs<TPair<uLang::CSymbol, ValueType>, uLang::CSymbol>`  
_L144-160_
- inherits: `BaseKeyFuncs<TPair<uLang::CSymbol,ValueType>,uLang::CSymbol>`
- L146 _public typedef_ `using Super = BaseKeyFuncs<TPair<uLang::CSymbol, ValueType>, uLang::CSymbol>;`
- L148 _public function_ `static inline const uLang::CSymbol& GetSetKey(typename Super::ElementInitType Element)`
- L152 _public function_ `static inline bool Matches(const uLang::CSymbol& A, const uLang::CSymbol& B)`
- L156 _public function_ `static inline uint32 GetKeyHash(const uLang::CSymbol& Key)`

#### Free symbols / members of external scopes

- L162 _namespace_ `namespace uLang`
- L168 _function_ `inline uint32 GetTypeHash(const STextPosition& TextPosition)` (scope `uLang`) — Helper function so STextPosition can be used in a TMap
