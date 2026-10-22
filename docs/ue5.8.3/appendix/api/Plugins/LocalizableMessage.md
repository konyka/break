# Plugins / LocalizableMessage

- module root: `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage`
- headers: 6; symbols: 61
- symbol kinds: class=2, delegate=1, function=10, macro=2, member=14, namespace=3, prototype=20, struct=8, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicDependencyModuleNames: 

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage/Public/ILocalizableMessageModule.h` (Public)


#### class `ILocalizableMessageModule`  
`class ILocalizableMessageModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `static ILocalizableMessageModule& Get();`
- L16 _public prototype_ `virtual FLocalizableMessageProcessor& GetLocalizableMessageProcessor() = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LOCALIZABLEMESSAGE_API`

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage/Public/LocalizableMessage.h` (Public)


#### struct `FLocalizableMessageParameterEntry`  
`struct FLocalizableMessageParameterEntry`  
_L30-51_
- reflection: `USTRUCT()`
- L36 _public prototype_ `FLocalizableMessageParameterEntry();`
- L37 _public prototype_ `FLocalizableMessageParameterEntry(const FString& InKey, const FInstancedStruct& InValue);`
- L38 _public prototype_ `~FLocalizableMessageParameterEntry();`
- L40 _public prototype_ `bool operator==(const FLocalizableMessageParameterEntry& Other) const;`
- L41 _public function_ `bool operator!=(const FLocalizableMessageParameterEntry& Other) const`
- L47 _public member_ `FString Key;` — `UPROPERTY()`
- L50 _public member_ `FInstancedStruct Value;` — `UPROPERTY()`

#### struct `FLocalizableMessage`  
`struct FLocalizableMessage`  
_L54-87_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public prototype_ `FLocalizableMessage();`
- L59 _public prototype_ `~FLocalizableMessage();`
- L60 _public prototype_ `bool operator==(const FLocalizableMessage& Other) const;`
- L62 _public function_ `void Reset()`
- L69 _public function_ `bool operator!=(const FLocalizableMessage& Other) const`
- L74 _public function_ `bool IsEmpty() const`
- L80 _public member_ `FString Key;` — `UPROPERTY()`
- L83 _public member_ `FString DefaultText;` — `UPROPERTY()`
- L86 _public member_ `TArray<FLocalizableMessageParameterEntry> Substitutions;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LOCALIZABLEMESSAGE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LocalizableMessageTextInterop` (scope `UE`)
- L19 _prototype_ `bool TextIdToMessageKey(const FTextId& TextId, FString& OutMessageKey);` (scope `UE::LocalizableMessageTextInterop`) — Attempt to convert the given FText ID to a string that can be used as a FLocalizableMessage key. @return True if the conversion was possible, or false if it failed.
- L25 _prototype_ `bool MessageKeyToTextId(const FString& MessageKey, FTextId& OutTextId);` (scope `UE::LocalizableMessageTextInterop`) — Attempt to convert the given FLocalizableMessage key into a FText ID. @return True if the conversion was possible, or false if it failed.

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage/Public/LocalizableMessageBaseParameters.h` (Public)


#### struct `FLocalizableMessageParameterInt`  
`struct FLocalizableMessageParameterInt`  
_L11-19_
- reflection: `USTRUCT()`
- L18 _public member_ `int64 Value = 0;` — `UPROPERTY()`

#### struct `FLocalizableMessageParameterFloat`  
`struct FLocalizableMessageParameterFloat`  
_L22-30_
- reflection: `USTRUCT()`
- L29 _public member_ `double Value = 0;` — `UPROPERTY()`

#### struct `FLocalizableMessageParameterString`  
`struct FLocalizableMessageParameterString`  
_L33-41_
- reflection: `USTRUCT()`
- L40 _public member_ `FString Value;` — `UPROPERTY()`

#### struct `FLocalizableMessageParameterMessage`  
`struct FLocalizableMessageParameterMessage`  
_L44-52_
- reflection: `USTRUCT()`
- L51 _public member_ `FLocalizableMessage Value;` — `UPROPERTY()`

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage/Public/LocalizableMessageProcessor.h` (Public)


#### class `FLocalizableMessageProcessor`  
`class FLocalizableMessageProcessor`  
_L17-53_
- L29 _public prototype_ `FLocalizableMessageProcessor();`
- L30 _public prototype_ `~FLocalizableMessageProcessor();`
- L32 _public prototype_ `FText Localize(const FLocalizableMessage& Message, const FLocalizationContext& Context);`
- L35 _public function_ `template <typename UserType> void RegisterLocalizableType(const TFunction<FFormatArgumentValue(const UserType&, const FLocalizationContext&)>& LocalizeValueFunctor, FScopedRegistrations& ScopedRegistrations)`
- L47 _public prototype_ `void UnregisterLocalizableTypes(FScopedRegistrations& ScopedRegistrations);`
- L50 _private typedef_ `using LocalizeValueFnc = TFunction<FFormatArgumentValue(const FInstancedStruct&, const FLocalizationContext&)>;`
- L52 _private member_ `TMap<FName, LocalizeValueFnc> LocalizeValueMapping;`

#### struct `FLocalizableMessageProcessor::FScopedRegistrations`  
`struct FScopedRegistrations`  
_L21-27_
- L23 _public prototype_ `FScopedRegistrations() = default;`
- L24 _public function_ `~FScopedRegistrations()`
- L26 _public member_ `TArray<FName> Registrations;`

#### Free symbols / members of external scopes

- L38 _function_ `` (scope `FLocalizableMessageProcessor::RegisterLocalizableType`)
- L55 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocalizableMessageProcessor, Log, All);`
- L55 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocalizableMessageProcessor, Log, All);`

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage/Public/LocalizableMessageTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace LocalizableMessageTypes`
- L9 _prototype_ `void RegisterTypes();` (scope `LocalizableMessageTypes`)
- L10 _prototype_ `void UnregisterTypes();` (scope `LocalizableMessageTypes`)

### `Plugins/Experimental/LocalizableMessage/Source/LocalizableMessage/Public/LocalizationContext.h` (Public)


#### struct `FLocalizationContext`  
`struct FLocalizationContext`  
_L9-45_
- L11 _public prototype_ `FLocalizationContext() = default;`
- L12 _public function_ `explicit FLocalizationContext(const UObject* InWorldContext, FCulturePtr InLanguageOverride = nullptr, FCulturePtr InLocaleOverride = nullptr) : WorldContext(InWorldContext) , LanguageOverride(MoveTemp(InLanguageOverride)) , LocaleOverride(MoveTemp(InLocaleOverride))`
- L18 _public member_ `TWeakObjectPtr<const UObject> WorldContext = nullptr;`
- L20 _public function_ `FCulturePtr GetLanguageOverride() const`
- L25 _public function_ `FCulturePtr GetLocaleOverride() const`
- L38 _private member_ `FCulturePtr LanguageOverride;` — The current language (for localization) override (if any). @note Will also be used as the locale if LocaleOverride is null. @note UE doesn't currently support loading the localization data for multiple languages at the same time.
- L44 _private member_ `FCulturePtr LocaleOverride;` — The current locale (for internationalization) override (if any). @note Internationalization affects things like number, date, time, etc formatting.
