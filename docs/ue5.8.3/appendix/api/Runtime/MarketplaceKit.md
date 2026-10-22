# Runtime / MarketplaceKit

- module root: `Source/Runtime/IOS/MarketplaceKit`
- headers: 3; symbols: 135
- symbol kinds: class=1, enum=1, enumerator=6, macro=80, member=8, prototype=21, typedef=18
- PrivateDependencyModuleNames: Core, Engine

### `Source/Runtime/IOS/MarketplaceKit/Private/MarketplaceKitWrapper.h` (Private)


#### Free symbols / members of external scopes

- L4 _macro_ `#define MARKETPLACEKITWRAPPER_SWIFT_H`
- L9 _macro_ `# define __has_include(x) 0`
- L12 _macro_ `# define __has_attribute(x) 0`
- L15 _macro_ `# define __has_feature(x) 0`
- L18 _macro_ `# define __has_warning(x) 0`
- L52 _macro_ `# define __ptrauth_swift_value_witness_function_pointer(x)`
- L55 _macro_ `# define __ptrauth_swift_class_method_pointer(x)`
- L63 _macro_ `# define SWIFT_TYPEDEFS 1`
- L67 _typedef_ `typedef unsigned char char8_t;`
- L68 _typedef_ `typedef uint_least16_t char16_t;`
- L69 _typedef_ `typedef uint_least32_t char32_t;`
- L71 _typedef_ `typedef float swift_float2 __attribute__((__ext_vector_type__(2)));`
- L72 _typedef_ `typedef float swift_float3 __attribute__((__ext_vector_type__(3)));`
- L73 _typedef_ `typedef float swift_float4 __attribute__((__ext_vector_type__(4)));`
- L74 _typedef_ `typedef double swift_double2 __attribute__((__ext_vector_type__(2)));`
- L75 _typedef_ `typedef double swift_double3 __attribute__((__ext_vector_type__(3)));`
- L76 _typedef_ `typedef double swift_double4 __attribute__((__ext_vector_type__(4)));`
- L77 _typedef_ `typedef int swift_int2 __attribute__((__ext_vector_type__(2)));`
- L78 _typedef_ `typedef int swift_int3 __attribute__((__ext_vector_type__(3)));`
- L79 _typedef_ `typedef int swift_int4 __attribute__((__ext_vector_type__(4)));`
- L80 _typedef_ `typedef unsigned int swift_uint2 __attribute__((__ext_vector_type__(2)));`
- L81 _typedef_ `typedef unsigned int swift_uint3 __attribute__((__ext_vector_type__(3)));`
- L82 _typedef_ `typedef unsigned int swift_uint4 __attribute__((__ext_vector_type__(4)));`
- L86 _macro_ `# define SWIFT_PASTE_HELPER(x, y) x##y`
- L87 _macro_ `# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)`
- L90 _macro_ `# define SWIFT_METATYPE(X) Class`
- L94 _macro_ `# define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__`
- L96 _macro_ `# define SWIFT_CLASS_PROPERTY(...)`
- L101 _macro_ `# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))`
- L103 _macro_ `# define SWIFT_RUNTIME_NAME(X)`
- L108 _macro_ `# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))`
- L110 _macro_ `# define SWIFT_COMPILE_NAME(X)`
- L115 _macro_ `# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))`
- L117 _macro_ `# define SWIFT_METHOD_FAMILY(X)`
- L122 _macro_ `# define SWIFT_NOESCAPE __attribute__((noescape))`
- L124 _macro_ `# define SWIFT_NOESCAPE`
- L129 _macro_ `# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))`
- L131 _macro_ `# define SWIFT_RELEASES_ARGUMENT`
- L136 _macro_ `# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))`
- L138 _macro_ `# define SWIFT_WARN_UNUSED_RESULT`
- L143 _macro_ `# define SWIFT_NORETURN __attribute__((noreturn))`
- L145 _macro_ `# define SWIFT_NORETURN`
- L149 _macro_ `# define SWIFT_CLASS_EXTRA`
- L152 _macro_ `# define SWIFT_PROTOCOL_EXTRA`
- L155 _macro_ `# define SWIFT_ENUM_EXTRA`
- L159 _macro_ `# define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA`
- L160 _macro_ `# define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA`
- L162 _macro_ `# define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA`
- L163 _macro_ `# define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA`
- L168 _macro_ `# define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))`
- L169 _macro_ `# define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)`
- L171 _macro_ `# define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)`
- L172 _macro_ `# define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)`
- L176 _macro_ `# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA`
- L177 _macro_ `# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA`
- L180 _macro_ `# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)`
- L184 _macro_ `# define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))`
- L186 _macro_ `# define OBJC_DESIGNATED_INITIALIZER`
- L191 _macro_ `# define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))`
- L193 _macro_ `# define SWIFT_ENUM_ATTR(_extensibility)`
- L198 _macro_ `# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type`
- L200 _macro_ `# define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type`
- L202 _macro_ `# define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)`
- L205 _macro_ `# define SWIFT_ENUM(_type, _name, _extensibility) _type _name; enum`
- L211 _macro_ `# define SWIFT_ENUM_TAG enum`
- L213 _macro_ `# define SWIFT_ENUM_TAG`
- L218 _macro_ `# define SWIFT_ENUM_FWD_DECL(_type, _name) enum _name : _type;`
- L220 _macro_ `# define SWIFT_ENUM_FWD_DECL(_type, _name) typedef _type _name;`
- L224 _macro_ `# define SWIFT_UNAVAILABLE __attribute__((unavailable))`
- L227 _macro_ `# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))`
- L230 _macro_ `# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))`
- L233 _macro_ `# define SWIFT_AVAILABILITY_DOMAIN(dom, ...) __attribute__((availability(domain: dom, __VA_ARGS__)))`
- L236 _macro_ `# define SWIFT_WEAK_IMPORT __attribute__((weak_import))`
- L239 _macro_ `# define SWIFT_DEPRECATED __attribute__((deprecated))`
- L242 _macro_ `# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))`
- L246 _macro_ `# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))`
- L248 _macro_ `# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)`
- L253 _macro_ `# define IBSegueAction`
- L258 _macro_ `# define SWIFT_EXTERN extern "C"`
- L260 _macro_ `# define SWIFT_EXTERN extern`
- L264 _macro_ `# define SWIFT_CALL __attribute__((swiftcall))`
- L267 _macro_ `# define SWIFT_INDIRECT_RESULT __attribute__((swift_indirect_result))`
- L270 _macro_ `# define SWIFT_CONTEXT __attribute__((swift_context))`
- L273 _macro_ `# define SWIFT_ERROR_RESULT __attribute__((swift_error_result))`
- L276 _macro_ `# define SWIFT_NOEXCEPT noexcept`
- L278 _macro_ `# define SWIFT_NOEXCEPT`
- L283 _macro_ `# define SWIFT_C_INLINE_THUNK inline __attribute__((always_inline)) __attribute__((nodebug))`
- L285 _macro_ `# define SWIFT_C_INLINE_THUNK inline __attribute__((always_inline))`
- L288 _macro_ `# define SWIFT_C_INLINE_THUNK inline`
- L293 _macro_ `# define SWIFT_IMPORT_STDLIB_SYMBOL __declspec(dllimport)`
- L297 _macro_ `# define SWIFT_IMPORT_STDLIB_SYMBOL`
- L301 _macro_ `# define _Nonnull`
- L302 _macro_ `# define _Nullable`
- L303 _macro_ `# define _Null_unspecified`
- L308 _macro_ `# define _Nullable_result _Nullable`
- L371 _typedef_ `typedef SWIFT_ENUM(NSInteger, AppDistributorType, closed) { AppDistributorTypeAppStore = 0, AppDistributorTypeTestFlight = 1, AppDistributorTypeMarketplace = 2, AppDistributorTypeWeb = 3, AppDistributorTypeOther = 4, AppDistributorTypeNotAvailable = 5, };`

### `Source/Runtime/IOS/MarketplaceKit/Private/MarketplaceKitWrapperAPI.h` (Private)


#### Free symbols / members of external scopes

- L17 _typedef_ `typedef void (*MKW_GetCurrentCallback)(long Type, const char* Name);` — Swift Int maps to long on arm64 (64-bit), Swift Bool maps to C bool
- L18 _typedef_ `typedef void (*MKW_BoolStringCallback)(bool Success, const char* Output);`
- L20 _prototype_ `extern void MKW_GetCurrent(MKW_GetCurrentCallback Callback) __attribute__((weak_import));`
- L21 _prototype_ `extern void MKW_RequestCTToken(MKW_BoolStringCallback Callback) __attribute__((weak_import));`
- L22 _prototype_ `extern void MKW_GetEligibilityRegion(MKW_BoolStringCallback Callback) __attribute__((weak_import));`

### `Source/Runtime/IOS/MarketplaceKit/Public/MarketplaceKit.h` (Public)


#### enum `EMarketplaceType`  
`enum class EMarketplaceType : int32`  
_L9-17_
- L11 _public enumerator_ `AppStore = 0`
- L12 _public enumerator_ `TestFlight = 1`
- L13 _public enumerator_ `Marketplace = 2`
- L14 _public enumerator_ `Web = 3`
- L15 _public enumerator_ `Other = 4`
- L16 _public enumerator_ `NotAvailable = 5`

#### class `FMarketplaceKitModule`  
`class FMarketplaceKitModule : public IModuleInterface`  
_L22-66_
- inherits: `IModuleInterface`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L29 _public prototype_ `void GetCurrentTypeAsync(TFunction<void(EMarketplaceType Type, const FString& Name)> Callback);`
- L30 _public prototype_ `static void RequestCTTokenAsync(TDelegate<void(bool Success, FString Output)> Callback);`
- L31 _public prototype_ `static FString GetEligibilityRegionStatic();`
- L34 _public prototype_ `void GetCurrentType(EMarketplaceType& OutType, FString& OutName);` — Returns the MarketplaceType, and BundleId
- L36 _public prototype_ `static EMarketplaceType GetCurrentTypeStatic();` — Returns the MarketplaceType
- L38 _public prototype_ `static FString GetMarketplaceBundleIdStatic();` — Returns the BundleId of the Marketplace, when MarketplaceType == Marketplace
- L40 _public prototype_ `FString GetCurrentTypeAsString();`
- L41 _public prototype_ `static FString GetCurrentTypeAsStringStatic();`
- L44 _public prototype_ `bool IsTestFlight();` — When installed from TestFlight, GetCurrentType etc above can return an emulated value for EMarketplaceType. If you _really_ need to know if you're running from TestFlight, this will tell you.
- L45 _public prototype_ `static bool IsTestFlightStatic();`
- L48 _private prototype_ `void GetEligibilityRegionAsync();`
- L51 _private member_ `bool bCachedTypeValid = false;`
- L52 _private member_ `EMarketplaceType CachedType = EMarketplaceType::NotAvailable;`
- L53 _private member_ `FString CachedName;`
- L55 _private member_ `EMarketplaceType TestFlightMarketplaceType = EMarketplaceType::TestFlight;`
- L56 _private member_ `FString TestFlightMarketplaceBundleId;`
- L58 _private member_ `FString TestOverrideEligibilityRegion;`
- L59 _private member_ `FString CachedEligibilityRegion;`
- L60 _private member_ `TAtomic<bool> bCachedEligibilityRegionInitialized = false;`
- L62 _private prototype_ `void CacheValue();`
- L65 _private prototype_ `void GetEffectiveType(EMarketplaceType& OutType, FString& OutName);` — Redirects TestFlight to an emulated Type/Name set by CVar for testing.

#### Free symbols / members of external scopes

- L19 _prototype_ `const FString LexToString(EMarketplaceType Value);`
- L20 _prototype_ `void LexFromString(EMarketplaceType& OutValue, const TCHAR* InValue);`
