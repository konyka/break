# Runtime / Analytics

- module root: `Source/Runtime/Analytics/Analytics`
- headers: 11; symbols: 379
- symbol kinds: class=12, delegate=1, enum=5, enumerator=26, function=91, macro=1, member=36, namespace=2, prototype=200, struct=4, typedef=1
- PublicDependencyModuleNames: Core

### `Source/Runtime/Analytics/Analytics/Public/Analytics.h` (Public)


#### class `FAnalytics`  
`class FAnalytics : public IModuleInterface`  
_L37-201_
- inherits: `IModuleInterface`
- desc: The public interface for interacting with analytics. The basic usage is to call CreateAnalyticsProvider and supply a configuration delegate. Specific analytics providers may choose to provide strongly-typed factory methods for configuration, in which case you are free to call that directly if you know exactly what provider you will be using. This class merely facilitates loosely bound provider configuration so the provider itself can be configured purely via config. BuildType methods exist as a common way for an analytics provider to configure itself for debug/development/playtest/release scenarios. Again, you can choose to ignore this info and provide a generic configuration delegate that does anything it wants. To create an analytics provider using all the system defaults, simply call the static GetDefaultConfiguredProvider().
- L43 _public prototype_ `FAnalytics();`
- L44 _public prototype_ `virtual ~FAnalytics();`
- L52 _public function_ `static inline FAnalytics& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L62 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L77 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FName& ProviderModuleName, const FAnalyticsProviderConfigurationDelegate& GetConfigValue);` — Factory function to create a specific analytics provider by providing the string name of the provider module, which will be dynamically loaded. @param ProviderModuleName	The name of the module that contains the specific provider. It must be the primary module interface. @param GetConfigvalue	Delegate used to configure the provider. The provider will call this delegate once for each key it requires for configuration. @returns		the analytics provider instance that was created. Could be NULL if initialization failed.
- L79 _public prototype_ `virtual TSharedPtr<IAnalyticsTracer> CreateAnalyticsTracer();`
- L86 _public function_ `virtual TSharedPtr<IAnalyticsProvider> GetDefaultConfiguredProvider()` — Creates an instance of the default configured analytics provider. Default is determined by GetDefaultProviderModuleName and a default constructed ConfigFromIni instance. This implementation is kept in the header file to illustrate how providers are created using configuration delegates.
- L191 _public prototype_ `virtual FString GetConfigValueFromIni(const FString& IniName, const FString& SectionName, const FString& KeyName, bool bIsRequired);` — Helper for reading configuration values from an INI file (which will be a common scenario). This is exposed here so we're not exporting more classes from the module. It's merely a helper for ConfigFromIni struct above.
- L196 _public prototype_ `virtual void WriteConfigValueToIni(const FString& IniName, const FString& SectionName, const FString& KeyName, const FString& Value);` — Helper for writing configuration values from to an INI file (which will be a common scenario).
- L199 _private prototype_ `virtual void StartupModule() override;`
- L200 _private prototype_ `virtual void ShutdownModule() override;`

#### struct `FAnalytics::ConfigFromIni`  
`struct ConfigFromIni`  
_L106-185_
- desc: A common way of configuring is from Inis, so this class supports that notion directly by providing a configuration class with a method suitable to be used as an FAnalyticsProviderConfigurationDelegate that reads values from the specified ini and section (based on the BuildType). Also provides a default location to store a provider name, accessed via GetDefaultProviderModuleName().
- L116 _public function_ `ConfigFromIni() :IniName(GEngineIni)` — Create a config using the default values: IniName - GEngineIni SectionName (Development) = AnalyticsDevelopment SectionName (Debug) = AnalyticsDebug SectionName (Test) = AnalyticsTest SectionName (Release) = Analytics
- L123 _public function_ `explicit ConfigFromIni(EAnalyticsBuildType InBuildType) :IniName(GEngineIni)` — Create a config AS IF the BuildType matches the one passed in.
- L130 _public function_ `ConfigFromIni(const FString& InIniName, const FString& InSectionName) :IniName(InIniName) ,SectionName(InSectionName)` — Create a config, specifying the Ini name and a single section name for all build types.
- L137 _public function_ `ConfigFromIni(const FString& InIniName, const FString& SectionNameDevelopment, const FString& SectionNameDebug, const FString& SectionNameTest, const FString& SectionNameRelease) :IniName(InIniName)` — Create a config, specifying the Ini name and the section name for each build type.
- L151 _public function_ `FString GetValue(const FString& KeyName, bool bIsRequired) const` — Method that can be bound to an FAnalyticsProviderConfigurationDelegate.
- L162 _public function_ `static FName GetDefaultProviderModuleName()` — Reads the ProviderModuleName key from the Analytics section of GEngineIni, which is the default, preferred location to look for the analytics provider name. This is purely optional, and you can store that information anywhere you want or merely hardcode the provider module.
- L170 _public function_ `void SetSectionNameByBuildType(EAnalyticsBuildType InBuildType)` — Allows setting the INI section name based on the build type passed in. Allows access to the default section values when the application chooses the build type itself.
- L182 _public member_ `FString IniName;` — Ini file name to find the config values.
- L184 _public member_ `FString SectionName;` — Section name in the Ini file in which to find the keys. The KeyNames should match the field name in the Config object.

#### Free symbols / members of external scopes

- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnalytics, Display, All);`

### `Source/Runtime/Analytics/Analytics/Public/AnalyticsBuildType.h` (Public)


#### enum `EAnalyticsBuildType`  
`enum class EAnalyticsBuildType : uint8`  
_L8-29_
- desc: Defines the different build types from an analytics perspective. Used to determine how to configure the provider.
- L14 _public enumerator_ `Development` — Analytics go into a "slush" account that isn't meant to be representative. This is the default mode.
- L19 _public enumerator_ `Test` — Test mode for playtests and other runs where the data collected will be semi-representative of actual gameplay. Should be routed to a test, or "representative data" account. Use -TESTANALYTICS command line to trigger this mode.
- L24 _public enumerator_ `Debug` — Debug mode where analytics should go to the Swrve debug console. Used for feature development and QA testing, since the events are visible on the debug console immediately. Use -DEBUGANALYTICS command line to trigger this mode (overrides -TESTANALYTICS).
- L28 _public enumerator_ `Release` — BuildType that should be used by the shipping game. UE_BUILD_SHIPPING builds use this mode (or can use -RELEASEANALYTICS cmdline to force it).

#### Free symbols / members of external scopes

- L32 _prototype_ `EAnalyticsBuildType GetAnalyticsBuildType();` — Get the analytics build type. Generally used to determine the keys to use to configure an analytics provider.
- L35 _prototype_ `const TCHAR* AnalyticsBuildTypeToString(EAnalyticsBuildType Type);` — Convert an EAnalyticsBuildType to string.

### `Source/Runtime/Analytics/Analytics/Public/AnalyticsConversion.h` (Public)


#### Free symbols / members of external scopes

- L11 _function_ `template <typename T> inline decltype(auto) AnalyticsConversionToString(const T& Value)` — Lexical conversion. Allow any type that we have a Lex for. Can't use universal references here because it then eats all non-perfect matches for the array and TMap conversions below, which we want to use a custom, analytics specific implementation for.
- L16 _function_ `inline FString AnalyticsConversionToString(FString&& Value)` — Make sure we have a direct implementation for moving FStrings as we definitely don't want to copy them as the above const-ref template will cause.
- L20 _function_ `inline FString AnalyticsConversionToString(const FString& Value)`
- L25 _function_ `inline FString AnalyticsConversionToString(FStringView Value)`
- L30 _macro_ `#define ANALYTICS_MAX_FLOAT_VALUE_BEFORE_EXPONENTIAL_NOTATION (1.0e+15F)`
- L32 _function_ `inline FString AnalyticsConversionToString(float Value)`
- L51 _function_ `inline FString AnalyticsConversionToString(double Value)`
- L73 _function_ `template <typename T, typename AllocatorType> FString AnalyticsConversionToString(const TArray<T, AllocatorType>& ValueArray)` — Array conversion. Creates comma-separated list.
- L89 _function_ `template <typename T> FString AnalyticsConversionToString(const TArrayView<T>& ValueArray)` — Array conversion. Creates comma-separated list.
- L105 _function_ `template<typename KeyType, typename ValueType, typename Allocator, typename KeyFuncs> FString AnalyticsConversionToString(const TMap<KeyType, ValueType, Allocator, KeyFuncs>& ValueMap)` — Map conversion. Creates comma-separated list. Creates comma-separated list with colon-separated key:value pairs.
- L122 _namespace_ `namespace AnalyticsConversion`
- L125 _function_ `template <typename T> inline decltype(auto) ToString(T&& Value)` (scope `AnalyticsConversion`)

### `Source/Runtime/Analytics/Analytics/Public/AnalyticsEventAttribute.h` (Public)


#### struct `FJsonNull`  
`struct FJsonNull`  
_L8-10_

#### struct `FJsonFragment`  
`struct FJsonFragment`  
_L17-24_
- L22 _public function_ `explicit FJsonFragment(FString&& StringRef) : FragmentString(MoveTemp(StringRef))` — Stores a JSON string, which is assumed to be correct JSON. If an empty string is passed, it will become "null" in LexToString.
- L23 _public member_ `FString FragmentString;`

#### struct `FAnalyticsEventAttribute`  
`struct FAnalyticsEventAttribute`  
_L47-123_
- desc: Struct to hold key/value pairs that will be sent as attributes along with analytics events. All values are actually strings, but we provide a convenient constructor that relies on ToStringForAnalytics() to convert common types.
- L50 _public member_ `const FString AttrName;` — `UE_DEPRECATED(4.26, "This property has been deprecated, use GetName() instead")`
- L53 _public member_ `const FString AttrValueString;` — `UE_DEPRECATED(4.26, "This property has been deprecated, use GetValue() instead")`
- L55 _public member_ `const double AttrValueNumber;` — `UE_DEPRECATED(4.26, "This property has been deprecated, use GetValue() instead. You cannot recover the original non-string value anymore")`
- L57 _public member_ `const bool AttrValueBool;` — `UE_DEPRECATED(4.26, "This property has been deprecated, use GetValue() instead. You cannot recover the original non-string value anymore")`
- L68 _public member_ `const AttrTypeEnum AttrType;` — `UE_DEPRECATED(4.26, "This property has been deprecated, use IsJsonFragment or GetValue instead")`
- L71 _public prototype_ `template <typename ValueType> FAnalyticsEventAttribute(FString InName, ValueType&& InValue);`
- L73 _public prototype_ `const FString& GetName() const;`
- L74 _public prototype_ `const FString& GetValue() const;`
- L75 _public prototype_ `bool IsJsonFragment() const;`
- L79 _public prototype_ `template<typename ValueType> void SetValue(ValueType&& InValue);` — Allow setting value for any type that supports LexToString
- L82 _public prototype_ `FAnalyticsEventAttribute();` — Default ctor since we declare a custom ctor.
- L83 _public prototype_ `~FAnalyticsEventAttribute();`
- L86 _public prototype_ `FAnalyticsEventAttribute(const FAnalyticsEventAttribute& RHS);` — Reinstate the default copy ctor because that one still works fine.
- L89 _public prototype_ `FAnalyticsEventAttribute(FAnalyticsEventAttribute&& RHS);` — Hack to allow copy ctor using an rvalue-ref. This class only "sort of" acts like an immutable class because the const members prevents assignment, which was not intended when this code was changed.
- L92 _public prototype_ `FAnalyticsEventAttribute& operator=(const FAnalyticsEventAttribute& RHS);` — Hack to allow assignment. This class only "sort of" acts like an immutable class because the const members prevents assignment, which was not intended when this code was changed.
- L95 _public prototype_ `FAnalyticsEventAttribute& operator=(FAnalyticsEventAttribute&& RHS);` — Hack to allow assignment. This class only "sort of" acts like an immutable class because the const members prevents assignment, which was not intended when this code was changed.
- L98 _public prototype_ `FAnalyticsEventAttribute& operator+=(const FAnalyticsEventAttribute& RHS);` — ALlow aggregation of attributes
- L101 _public prototype_ `FAnalyticsEventAttribute& operator+(const FAnalyticsEventAttribute& RHS);` — ALlow aggregation of attributes
- L105 _public prototype_ `FString ToString() const;` — `UE_DEPRECATED(4.26, "This property has been deprecated, use GetValue() instead")` — If you need the old AttrValue behavior (i.e. stringify everything), call this function instead.
- L109 _public prototype_ `void SwitchToJsonFragment();` — `UE_DEPRECATED(4.26, "This property is used to support the deprecated APIs, construct Json values using FJsonFragment instead")` — Legacy support for old RecordEventJson API. Don't call this directly.
- L111 _public function_ `static bool IsValidAttributeName(const FString& InName)`
- L117 _private function_ `FString& CheckName(FString& InName)`
- L131 _function_ `inline FAnalyticsEventAttribute::FAnalyticsEventAttribute() : AttrName() , AttrValueString() , AttrValueNumber(0) , AttrValueBool(false) , AttrType(AttrTypeEnum::String)`
- L141 _prototype_ `inline FAnalyticsEventAttribute::~FAnalyticsEventAttribute() = default;`
- L143 _prototype_ `inline FAnalyticsEventAttribute::FAnalyticsEventAttribute(const FAnalyticsEventAttribute& RHS) = default;`
- L145 _function_ `inline FAnalyticsEventAttribute::FAnalyticsEventAttribute(FAnalyticsEventAttribute&& RHS) : AttrName(MoveTemp(const_cast<FString&>(RHS.AttrName))) , AttrValueString(MoveTemp(const_cast<FString&>(RHS.AttrValueString)))`
- L156 _function_ `template <typename ValueType> inline FAnalyticsEventAttribute::FAnalyticsEventAttribute(FString InName, ValueType&& InValue) : AttrName(MoveTemp(CheckName(InName))) , AttrValueString(AnalyticsConversionToString(Forward<ValueType>(InValue))) , AttrValueNumber(0) , AttrValueBool(false) , AttrType(TIsArithmetic<typename TDecay<ValueType>::Type>::Value || std::is_same_v<typename TDecay<ValueType>::Type, FJsonNull> || std::is_same_v<typename TDecay<ValueType>::Type, FJsonFragment> ? AttrTypeEnum::JsonFragment : AttrTypeEnum::String)`
- L167 _function_ `inline FAnalyticsEventAttribute& FAnalyticsEventAttribute::operator=(const FAnalyticsEventAttribute& RHS)`
- L182 _function_ `inline FAnalyticsEventAttribute& FAnalyticsEventAttribute::operator+=(const FAnalyticsEventAttribute& RHS)`
- L187 _function_ `inline FAnalyticsEventAttribute& FAnalyticsEventAttribute::operator+(const FAnalyticsEventAttribute& RHS)`
- L198 _function_ `inline FAnalyticsEventAttribute& FAnalyticsEventAttribute::operator=(FAnalyticsEventAttribute&& RHS)`
- L214 _function_ `inline FString FAnalyticsEventAttribute::ToString() const`
- L219 _function_ `inline const FString& FAnalyticsEventAttribute::GetName() const`
- L224 _function_ `inline const FString& FAnalyticsEventAttribute::GetValue() const`
- L229 _function_ `inline bool FAnalyticsEventAttribute::IsJsonFragment() const`
- L235 _function_ `template<typename ValueType> inline void FAnalyticsEventAttribute::SetValue(ValueType&& InValue)`
- L241 _function_ `inline void FAnalyticsEventAttribute::SwitchToJsonFragment()`

#### enum `FAnalyticsEventAttribute::AttrTypeEnum`  
`enum class AttrTypeEnum`  
_L59-66_
- L61 _public enumerator_ `String`
- L62 _public enumerator_ `Number`
- L63 _public enumerator_ `Boolean`
- L64 _public enumerator_ `Null`
- L65 _public enumerator_ `JsonFragment`

#### Free symbols / members of external scopes

- L12 _function_ `inline const TCHAR* LexToString(FJsonNull)`
- L26 _function_ `inline const TCHAR* LexToString(const FJsonFragment& Fragment)`
- L33 _function_ `inline FString LexToString(FJsonFragment&& Fragment)`
- L249 _namespace_ `namespace ImplMakeAnalyticsEventAttributeArray`
- L254 _function_ `template <typename Allocator, typename KeyType, typename ValueType> FORCENOINLINE void AddElement(TArray<FAnalyticsEventAttribute, Allocator>& Attrs, const KeyType& Key, const ValueType& Value)` (scope `ImplMakeAnalyticsEventAttributeArray`) — AddElement actually adds an element to the attributes array and is flagged no-inline so the array insert/value conversion code is generated once per type combination.
- L261 _function_ `template <typename Allocator> FORCEINLINE void MakeArray(TArray<FAnalyticsEventAttribute, Allocator>& Attrs)` (scope `ImplMakeAnalyticsEventAttributeArray`)
- L267 _function_ `template <typename Allocator, typename KeyType, typename ValueType, typename... RemainingArgTypes> FORCEINLINE void MakeArray(TArray<FAnalyticsEventAttribute, Allocator>& Attrs, KeyType&& Key, ValueType&& Value, RemainingArgTypes&& ...RemainingArgs)` (scope `ImplMakeAnalyticsEventAttributeArray`) — MakeArray is just a helper whose only purpose is to generate a sequence of AddElement calls and is meant to be always inlined.
- L280 _function_ `template <typename Allocator = FDefaultAllocator, typename...ArgTypes> inline TArray<FAnalyticsEventAttribute, Allocator> MakeAnalyticsEventAttributeArray(ArgTypes&&...Args)` — Helper to create an array of attributes using a single expression. Reserves the necessary space in advance. There must be an even number of arguments, one for each key/value pair.
- L290 _function_ `template <typename Allocator = FDefaultAllocator, typename...ArgTypes> inline TArray<FAnalyticsEventAttribute, Allocator>& AppendAnalyticsEventAttributeArray(TArray<FAnalyticsEventAttribute, Allocator>& Attrs, ArgTypes&&...Args)` — Helper to append to an array of attributes using a single expression. Reserves the necessary space in advance. There must be an even number of arguments, one for each key/value pair.

### `Source/Runtime/Analytics/Analytics/Public/AnalyticsPropertyStore.h` (Public)


#### class `FAnalyticsPropertyStore`  
`class FAnalyticsPropertyStore : public IAnalyticsPropertyStore`  
_L36-191_
- inherits: `IAnalyticsPropertyStore`
- desc: Implements a fast key/value database to store the metrics gathered to create the session summary event. The store is buffered in memory until it is flushed to disk by calling Flush(). It is not designed to handle millions of key/value pairs, but rather a small subset that fits in memory. The implementation reserve disk space ahead of time and can usually perform in-place update. Setting or getting intrinsic types (int32, uint32, int64, uint64, float, double, bool as well as FDateTime) doesn't allocate memory. The string time is often updated in place if enough capacity was reserved. All store operations are thread safe and atomic from the caller perspective.
- L40 _public prototype_ `FAnalyticsPropertyStore();` — Create an empty store.
- L41 _public prototype_ `virtual ~FAnalyticsPropertyStore();`
- L43 _public prototype_ `FAnalyticsPropertyStore(const FAnalyticsPropertyStore&) = delete;`
- L44 _public prototype_ `FAnalyticsPropertyStore(FAnalyticsPropertyStore&&) = delete;`
- L45 _public prototype_ `FAnalyticsPropertyStore& operator=(const FAnalyticsPropertyStore&) = delete;`
- L46 _public prototype_ `FAnalyticsPropertyStore& operator=(FAnalyticsPropertyStore&&) = delete;`
- L54 _public prototype_ `bool Create(const FString& Pathname, uint32 CapacityHint = 4 * 1024);` — Create a new store, creating the file of the specified capacity and resetting the current state. @param Pathname The path to the file to create. @param CapacityHint The desired file capacity. The implementation has a minimum and maximum capacity to reserve. @param true if the file was created and the store created, false otherwise.
- L61 _public prototype_ `bool Load(const FString& Pathname);` — Load the specified file in memory, resetting the current state. @param Pathname The path to the file to open. @return true if the file was loaded successuflly, false if the file doesn't exist, the file format/version is invalid or if the file is corrupted (failed checksum).
- L64 _public function_ `bool IsValid() const` — Returns true is the store was successfully created or loaded.
- L67 _public prototype_ `virtual uint32 Num() const override;`
- L68 _public prototype_ `virtual bool Contains(const FString& Key) const override;`
- L69 _public prototype_ `virtual bool Remove(const FString& Key) override;`
- L70 _public prototype_ `virtual void RemoveAll() override;`
- L71 _public prototype_ `virtual EStatusCode Set(const FString& Key, int32 Value) override;`
- L72 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint32 Value) override;`
- L73 _public prototype_ `virtual EStatusCode Set(const FString& Key, int64 Value) override;`
- L74 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint64 Value) override;`
- L75 _public prototype_ `virtual EStatusCode Set(const FString& Key, float Value) override;`
- L76 _public prototype_ `virtual EStatusCode Set(const FString& Key, double Value) override;`
- L77 _public prototype_ `virtual EStatusCode Set(const FString& Key, bool Value) override;`
- L78 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FString& Value, uint32 CharCountCapacityHint = 0) override;`
- L79 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FDateTime& Value) override;`
- L80 _public prototype_ `virtual EStatusCode Set(const FString& Key, int32 Value, const TFunction<bool(const int32* , const int32& )>& ConditionFn) override;`
- L81 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint32 Value, const TFunction<bool(const uint32* , const uint32& )>& ConditionFn) override;`
- L82 _public prototype_ `virtual EStatusCode Set(const FString& Key, int64 Value, const TFunction<bool(const int64* , const int64& )>& ConditionFn) override;`
- L83 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint64 Value, const TFunction<bool(const uint64* , const uint64& )>& ConditionFn) override;`
- L84 _public prototype_ `virtual EStatusCode Set(const FString& Key, float Value, const TFunction<bool(const float* , const float& )>& ConditionFn) override;`
- L85 _public prototype_ `virtual EStatusCode Set(const FString& Key, double Value, const TFunction<bool(const double* , const double& )>& ConditionFn) override;`
- L86 _public prototype_ `virtual EStatusCode Set(const FString& Key, bool Value, const TFunction<bool(const bool* , const bool& )>& ConditionFn) override;`
- L87 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FString& Value, const TFunction<bool(const FString* , const FString& )>& ConditionFn) override;`
- L88 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FDateTime& Value, const TFunction<bool(const FDateTime* , const FDateTime& )>& ConditionFn) override;`
- L89 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(int32&)>& UpdateFn) override;`
- L90 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(uint32&)>& UpdateFn) override;`
- L91 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(int64&)>& UpdateFn) override;`
- L92 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(uint64&)>& UpdateFn) override;`
- L93 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(float&)>& UpdateFn) override;`
- L94 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(double&)>& UpdateFn) override;`
- L95 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(bool&)>& UpdateFn) override;`
- L96 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(FString&)>& UpdateFn) override;`
- L97 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(FDateTime&)>& UpdateFn) override;`
- L98 _public prototype_ `virtual EStatusCode Get(const FString& Key, int32& OutValue) const override;`
- L99 _public prototype_ `virtual EStatusCode Get(const FString& Key, uint32& OutValue) const override;`
- L100 _public prototype_ `virtual EStatusCode Get(const FString& Key, int64& OutValue) const override;`
- L101 _public prototype_ `virtual EStatusCode Get(const FString& Key, uint64& OutValue) const override;`
- L102 _public prototype_ `virtual EStatusCode Get(const FString& Key, float& OutValue) const override;`
- L103 _public prototype_ `virtual EStatusCode Get(const FString& Key, double& OutValue) const override;`
- L104 _public prototype_ `virtual EStatusCode Get(const FString& Key, bool& OutValue) const override;`
- L105 _public prototype_ `virtual EStatusCode Get(const FString& Key, FString& OutValue) const override;`
- L106 _public prototype_ `virtual EStatusCode Get(const FString& Key, FDateTime& OutValue) const override;`
- L107 _public prototype_ `virtual void VisitAll(const TFunction<void(FAnalyticsEventAttribute&&)>& VisitFn) const override;`
- L122 _public prototype_ `virtual bool Flush(bool bAsync = false, const FTimespan& Timeout = FTimespan::MaxValue()) override;` — Flushes cached values to disk. Only one thread can flush at a time, causing possible latency if a flush is alreary happenning. @param bAsync Whether the data in flushed in a background thread or in the calling thread. @param Timeout Maximum time to wait before the flush starts (synchronous) or get scheduled (asynchronous). FTimespan::Zero() means no waiting. @return True if the flush was executed (synchronous) or scheduled (asynchronous), false if the operation timed out. @code Store.Flush(); // Flush in the calling thread, block until all threads has finished flushing. Store.Flush(false, FTimespan::Zero()); // Flush in the calling thread if possible, return immediatedly if another thread is already flushing. Store.Flush(true, FTimespan::Zero()); // Flush in a backgroud thread if no other thread is flushing, return immediatedly if another flushing task is running. Store.Flush(true);  // Flush in a background thread, might block if a thread is already flushing. (It doesn't queue several tasks). @endcode
- L156 _private prototype_ `EStatusCode SetFixedSizeValueInternal(const FString& Key, ETypeCode TypeCode, const uint8* Value, uint32 Size);`
- L157 _private prototype_ `EStatusCode GetFixedSizeValueInternal(const FString& Key, ETypeCode TypeCode, uint8* OutValue, uint32 Size) const;`
- L158 _private prototype_ `EStatusCode SetStringValueInternal(const FString& Key, const FString& Value, uint32 CharCountCapacityHint = 0);`
- L159 _private prototype_ `EStatusCode GetStringValueInternal(const FString& Key, FString& OutValue) const;`
- L160 _private prototype_ `EStatusCode SetDateTimeValueInternal(const FString& Key, const FDateTime& Value);`
- L161 _private prototype_ `EStatusCode GetDateTimeValueInternal(const FString& Key, FDateTime& OutValue) const;`
- L162 _private prototype_ `void Defragment();`
- L163 _private function_ `bool IsFixedSize(ETypeCode Type) const`
- L164 _private function_ `bool IsDead(ETypeCode Type) const`
- L165 _private function_ `ETypeCode RawType(ETypeCode Type) const`
- L166 _private prototype_ `void FlushInternal(const TArray<uint8>& Data);`
- L167 _private prototype_ `void Reset();`
- L170 _private function_ `template<typename T> IAnalyticsPropertyStore::EStatusCode SetFixedSizeValueInternal(const FString& Key, ETypeCode TypeCode, T Value)`
- L176 _private function_ `template<typename T> EStatusCode GetFixedSizeValueInternal(const FString& Key, ETypeCode TypeCode, T& OutValue) const`
- L182 _private member_ `mutable FTransactionallySafeCriticalSection StoreLock;`
- L183 _private member_ `TArray<uint8> StorageBuf;`
- L184 _private member_ `FMemoryWriter StorageWriter;`
- L185 _private member_ `mutable FMemoryReader StorageReader;`
- L186 _private member_ `TMap<FString, uint32> NameOffsetMap;`
- L187 _private member_ `TUniquePtr<IFileHandle> FileHandle;`
- L188 _private member_ `bool bFragmented = false;`
- L189 _private member_ `TUniquePtr<FAsyncTask<FFlushWorker>> FlushTask;`
- L190 _private member_ `TArray<uint8> AsyncFlushDataCopy;`

#### enum `FAnalyticsPropertyStore::ETypeCode`  
`enum class ETypeCode : uint8`  
_L125-138_
- L127 _public enumerator_ `I32 = 0x00`
- L128 _public enumerator_ `U32 = 0x01`
- L129 _public enumerator_ `I64 = 0x02`
- L130 _public enumerator_ `U64 = 0x03`
- L131 _public enumerator_ `Flt = 0x04`
- L132 _public enumerator_ `Dbl = 0x05`
- L133 _public enumerator_ `Bool = 0x06`
- L134 _public enumerator_ `Date = 0x07`
- L135 _public enumerator_ `Str = 0x08`
- L136 _public enumerator_ `RawMask = 0x0F` — To extract the raw types above from the meta data below
- L137 _public enumerator_ `Dead = 0x80` — Type for record that were moved or deleted.

#### class `FAnalyticsPropertyStore::FFlushWorker`  
`class FFlushWorker : public FNonAbandonableTask`  
_L142-152_
- inherits: `FNonAbandonableTask`
- desc: Helper task to persist the properties to disk in the background.
- L145 _public prototype_ `FFlushWorker(FAnalyticsPropertyStore& InStore);`
- L146 _public prototype_ `void DoWork();`
- L147 _public function_ `TStatId GetStatId() const`
- L148 _public function_ `static const TCHAR* Name()`
- L150 _private member_ `FAnalyticsPropertyStore& Store;`
- L151 _private member_ `TArray<uint8> Data;`

#### Free symbols / members of external scopes

- L193 _prototype_ `ENUM_CLASS_FLAGS(FAnalyticsPropertyStore::ETypeCode);`

### `Source/Runtime/Analytics/Analytics/Public/AnalyticsProviderConfigurationDelegate.h` (Public)


#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FAnalyticsProviderConfigurationDelegate, const FString&, bool);` — Analytics providers must be configured when created. This delegate provides a generic way to supply this config when creating a provider from this abstract factory function. This delegate will be called by the specific analytics provider for each configuration value it requires. The first param is the confguration name, the second parameter is a bool that is true if the value is required. It is up to the specific provider to define what configuration keys it requires. Some providers may provide more typesafe ways of constructing them when the code knows exactly which provider it will be using.
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FAnalyticsProviderConfigurationDelegate, const FString&, bool);` — Analytics providers must be configured when created. This delegate provides a generic way to supply this config when creating a provider from this abstract factory function. This delegate will be called by the specific analytics provider for each configuration value it requires. The first param is the confguration name, the second parameter is a bool that is true if the value is required. It is up to the specific provider to define what configuration keys it requires. Some providers may provide more typesafe ways of constructing them when the code knows exactly which provider it will be using.

### `Source/Runtime/Analytics/Analytics/Public/AnalyticsTracer.h` (Public)


#### class `FAnalyticsSpan`  
`class FAnalyticsSpan : public IAnalyticsSpan`  
_L12-46_
- inherits: `IAnalyticsSpan`
- desc: Implementation of an IAnalyticsSpan interface
- L16 _public function_ `FAnalyticsSpan(FName SpanName): IAnalyticsSpan(SpanName), Name(SpanName)`
- L17 _public prototype_ `~FAnalyticsSpan()= default;`
- L20 _public prototype_ `virtual void SetProvider(TSharedPtr<IAnalyticsProvider> AnalyticsProvider) override;` — Public IAnalyticsSpan implementation
- L21 _public prototype_ `virtual void Start(const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});`
- L22 _public prototype_ `virtual void End(const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) override;`
- L23 _public prototype_ `virtual void AddAttributes(const TArray<FAnalyticsEventAttribute>& AdditionalAttributes) override;`
- L24 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) override;`
- L25 _public prototype_ `virtual const FName& GetName() const override;`
- L26 _public prototype_ `virtual const TArray<FAnalyticsEventAttribute>& GetAttributes() const override;`
- L27 _public prototype_ `virtual void SetStackDepth(uint32 Depth) override;`
- L28 _public prototype_ `virtual uint32 GetStackDepth() const override;`
- L29 _public prototype_ `virtual double GetElapsedTime() override;`
- L30 _public prototype_ `virtual double GetDuration() const override;`
- L31 _public prototype_ `virtual bool GetIsActive() const override;`
- L32 _public prototype_ `virtual FGuid GetId() const override;`
- L36 _private member_ `FName Name = "No`
- L37 _private member_ `FGuid Guid = FGuid();`
- L38 _private member_ `FDateTime StartTime = 0;`
- L39 _private member_ `FDateTime EndTime = 0;`
- L40 _private member_ `FThreadId ThreadId = 0;`
- L41 _private member_ `uint32 StackDepth = 0;`
- L42 _private member_ `double Duration = 0;`
- L43 _private member_ `bool IsActive = false;`
- L44 _private member_ `TSharedPtr<IAnalyticsProvider> AnalyticsProvider;`
- L45 _private member_ `TArray<FAnalyticsEventAttribute> Attributes;`

#### class `FAnalyticsTracer`  
`class FAnalyticsTracer : public IAnalyticsTracer`  
_L51-82_
- inherits: `IAnalyticsTracer`
- desc: Implementation of an IAnalyticsTracer interface
- L55 _public function_ `FAnalyticsTracer()`
- L56 _public prototype_ `~FAnalyticsTracer()= default;`
- L59 _public prototype_ `virtual void StartSession() override;` — Public IAnalyticsTracer implementation
- L60 _public prototype_ `virtual void EndSession() override;`
- L61 _public prototype_ `virtual void SetProvider(TSharedPtr<IAnalyticsProvider> AnalyticsProvider) override;`
- L62 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> StartSpan(const FName Name, TSharedPtr<IAnalyticsSpan> ParentSpan, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) override;`
- L63 _public prototype_ `virtual bool EndSpan(TSharedPtr<IAnalyticsSpan> Span, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) override;`
- L64 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> GetCurrentSpan() const override;`
- L65 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> GetSessionSpan() const override;`
- L66 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> GetSpan(const FName Name) override;`
- L70 _private prototype_ `bool StartSpanInternal(TSharedPtr<IAnalyticsSpan> Span, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes);`
- L71 _private prototype_ `bool EndSpanInternal(TSharedPtr<IAnalyticsSpan> Span, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes);`
- L72 _private prototype_ `TSharedPtr<IAnalyticsSpan> GetSpanInternal(const FName Name);`
- L73 _private prototype_ `void BeginRegion(TSharedPtr<IAnalyticsSpan> Span);`
- L74 _private prototype_ `void EndRegion(TSharedPtr<IAnalyticsSpan> Span);`
- L76 _private member_ `TSharedPtr<IAnalyticsProvider> AnalyticsProvider;` — The Analytics provider we will send our span events to
- L77 _private member_ `TSharedPtr<IAnalyticsSpan> SessionSpan;` — The root span, this will always be present in an active session
- L78 _private member_ `TArray<TSharedPtr<IAnalyticsSpan>> ActiveSpanStack;` — Stack of active spans as WeakPtrs
- L79 _private member_ `TMap<FGuid, TArray<TWeakPtr<IAnalyticsSpan>>> SpanHeirarchy;` — List of child spans per parent span
- L80 _private member_ `TMap<FName, FGuid> RegionNames;` — Temprorary fix for duplicate span names in regions
- L81 _private member_ `FCriticalSection CriticalSection;`

#### Free symbols / members of external scopes

- L7 _typedef_ `using FThreadId = uint32;`

### `Source/Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsPropertyStore.h` (Public)


#### class `IAnalyticsPropertyStore`  
`class IAnalyticsPropertyStore`  
_L13-145_
- desc: Implements a fast type safe key/value database to store analytics properties collected during a session.
- L30 _public prototype_ `virtual ~IAnalyticsPropertyStore() = default;`
- L35 _public prototype_ `virtual uint32 Num() const = 0;` — Returns the number of elements in the store.
- L40 _public prototype_ `virtual bool Contains(const FString& Key) const = 0;` — Returns true if the store contains the specified key.
- L46 _public prototype_ `virtual bool Remove(const FString& Key) = 0;` — Removes the specified key from the store. @return true if the key was removed.
- L51 _public prototype_ `virtual void RemoveAll() = 0;` — Removes all existing keys from the store.
- L60 _public prototype_ `virtual EStatusCode Set(const FString& Key, int32 Value) = 0;` — Adds or updates the specified key/value pair. If the key doesn't exist, the key/value pair is added. If the key already exists, the value is updated if the stored value and the specified value types match. @param Key The property name to add or update. @param Value The property value to add or update. @return EStatusCode::Success if the key was added or updated, EStatusCode::BadType if the value type did not match the current value type.
- L61 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint32 Value) = 0;`
- L62 _public prototype_ `virtual EStatusCode Set(const FString& Key, int64 Value) = 0;`
- L63 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint64 Value) = 0;`
- L64 _public prototype_ `virtual EStatusCode Set(const FString& Key, float Value) = 0;`
- L65 _public prototype_ `virtual EStatusCode Set(const FString& Key, double Value) = 0;`
- L66 _public prototype_ `virtual EStatusCode Set(const FString& Key, bool Value) = 0;`
- L67 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FString& Value, uint32 CharCountCapacityHint = 0) = 0;`
- L68 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FDateTime& Value) = 0;`
- L83 _public prototype_ `virtual EStatusCode Set(const FString& Key, int32 Value, const TFunction<bool(const int32* , const int32& )>& ConditionFn) = 0;` — Conditionnnaly adds or updates the specified key/value pair. The operation is atomic from the caller perspective. The function reads the actual value (if it exists), invoke the ConditionFn callback and write the value back if the condition function returns true. If the key doesn't exist, the actual value passed back to the condition function is null. If the condition function returns true, the proposed value is set, otherwise, the operation is declined and the store remains unchanged. @param Key The name of the property to add or update. @param Value The value proposed. This value is passed as the second parameter to the ConditionFn callback. @param ConditionFn Function invoked back with the actual value and the proposed value to let the caller decide whether the proposed value should be set or not. If the callback function returns true, the proposed value is added/updated, otherwise, nothing changes. @return One of the following code - EStatusCode::Success if the entire operation succeeded. - EStatusCode::BadType if the key/value pair exists, but the proposed value did not match the actual value type. - EStatusCode::Declined if the callback ConditionFn returned false and the operation was declined.
- L84 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint32 Value, const TFunction<bool(const uint32* , const uint32& )>& ConditionFn) = 0;`
- L85 _public prototype_ `virtual EStatusCode Set(const FString& Key, int64 Value, const TFunction<bool(const int64* , const int64& )>& ConditionFn) = 0;`
- L86 _public prototype_ `virtual EStatusCode Set(const FString& Key, uint64 Value, const TFunction<bool(const uint64* , const uint64& )>& ConditionFn) = 0;`
- L87 _public prototype_ `virtual EStatusCode Set(const FString& Key, float Value, const TFunction<bool(const float* , const float& )>& ConditionFn) = 0;`
- L88 _public prototype_ `virtual EStatusCode Set(const FString& Key, double Value, const TFunction<bool(const double* , const double& )>& ConditionFn) = 0;`
- L89 _public prototype_ `virtual EStatusCode Set(const FString& Key, bool Value, const TFunction<bool(const bool* , const bool& )>& ConditionFn) = 0;`
- L90 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FString& Value, const TFunction<bool(const FString* , const FString& )>& ConditionFn) = 0;`
- L91 _public prototype_ `virtual EStatusCode Set(const FString& Key, const FDateTime& Value, const TFunction<bool(const FDateTime* , const FDateTime& )>& ConditionFn) = 0;`
- L103 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(int32& )>& UpdateFn) = 0;` — Updates an exiting value. The operation is atomic from the caller perspective. The function reads the actual value and invoke UpdateFn callback with the actual value. The callback can update the actual value or decline the operation. If the key is not found, the callback is not invoked. @param Key The name of the key to update. @param UpdateFn The function to invoke, passing the actual value. @return One of the following code - EStatusCode::Success if the entire operation succeeded. - EStatusCode::BadType if the key/value pair exists, but the proposed value did not match the actual value type. - EStatusCode::Declined if the callback UpdateFn returned false and the operation was declined.
- L104 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(uint32& )>& UpdateFn) = 0;`
- L105 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(int64& )>& UpdateFn) = 0;`
- L106 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(uint64& )>& UpdateFn) = 0;`
- L107 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(float& )>& UpdateFn) = 0;`
- L108 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(double& )>& UpdateFn) = 0;`
- L109 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(bool& )>& UpdateFn) = 0;`
- L110 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(FString& )>& UpdateFn) = 0;`
- L111 _public prototype_ `virtual EStatusCode Update(const FString& Key, const TFunction<bool(FDateTime& )>& UpdateFn) = 0;`
- L122 _public prototype_ `virtual EStatusCode Get(const FString& Key, int32& OutValue) const = 0;` — Reads the specified key value from the store. @param Key The name of the property to read. @param OutValue The value of the property if the function returns EStatusCode::Success, left unchanged otherwise. @return One of the following code - EStatusCode::Success if the value was read succeessfully. - EStatusCode::BadType if the key/value pair exists, but the type used did not match the actual value type. - EStatusCode::NotFound if the key/value could not be found.
- L123 _public prototype_ `virtual EStatusCode Get(const FString& Key, uint32& OutValue) const = 0;`
- L124 _public prototype_ `virtual EStatusCode Get(const FString& Key, int64& OutValue) const = 0;`
- L125 _public prototype_ `virtual EStatusCode Get(const FString& Key, uint64& OutValue) const = 0;`
- L126 _public prototype_ `virtual EStatusCode Get(const FString& Key, float& OutValue) const = 0;`
- L127 _public prototype_ `virtual EStatusCode Get(const FString& Key, double& OutValue) const = 0;`
- L128 _public prototype_ `virtual EStatusCode Get(const FString& Key, bool& OutValue) const = 0;`
- L129 _public prototype_ `virtual EStatusCode Get(const FString& Key, FString& OutValue) const = 0;`
- L130 _public prototype_ `virtual EStatusCode Get(const FString& Key, FDateTime& OutValue)const = 0;`
- L136 _public prototype_ `virtual void VisitAll(const TFunction<void(FAnalyticsEventAttribute&&)>& VisitFn) const = 0;` — Iterates the keys currently stored and invokes the visitor function for each key, converting the value to its string representation. @param VisitFn The callback invoked for each key/value pair visited.
- L144 _public prototype_ `virtual bool Flush(bool bAsync = false, const FTimespan& Timeout = FTimespan::MaxValue()) = 0;` — Flushes cached values to persistent storage. @param bAsync Whether the data in flushed in a background thread or in the calling thread. @param Timeout Maximum time to wait before the flush starts (synchronous) or get scheduled (asynchronous). FTimespan::Zero() means no waiting. @return True if the flush was executed (synchronous) or scheduled (asynchronous), false if the operation timed out.

#### enum `IAnalyticsPropertyStore::EStatusCode`  
`enum class EStatusCode : uint32`  
_L17-27_
- desc: The list of store operation outcome.
- L20 _public enumerator_ `Success` — The operation terminated sucessfully.
- L22 _public enumerator_ `NotFound` — The operation failed because the key could not be found.
- L24 _public enumerator_ `BadType` — The operation failed because the key value provided did not match the currently stored value.
- L26 _public enumerator_ `Declined` — A conditional operation failed because it was declined by the caller (during a callback).

#### class `TAnalyticsProperty`  
`template<typename T> class TAnalyticsProperty`  
_L158-169_
- desc: Utility class to remember the key value type and let the compiler implicitly convert type or fail if such conversion is not possible. Usage: @code static const TAnalyticsProperty<uint32> MyProperty = TEXT("MyProperty"); IAnalyticsPropertyStore* MyStore = ...; MyProperty.SetValue(MyStore,  10); // Ok. MyProperty.SetValue(MyStore, TEXT("No")); // Compile error, not convertible. @endcode
- L161 _public function_ `TAnalyticsProperty(const TCHAR* InKey) : Key(InKey)`
- L163 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const T& Value) const`
- L164 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const T& Value, const TFunction<bool(const T*, const T&)>& ConditionFn) const`
- L165 _public function_ `IAnalyticsPropertyStore::EStatusCode Get(IAnalyticsPropertyStore* Store, T& OutValue) const`
- L166 _public function_ `IAnalyticsPropertyStore::EStatusCode Update(IAnalyticsPropertyStore* Store, const TFunction<bool(T& InOutValue)>& UpdateFn) const`
- L168 _public member_ `const FString Key;`
- L178 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const FString& Value, uint32 CharCountCapacityHint = 0) const`
- L179 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const FString& Value, const TFunction<bool(const FString*, const FString&)>& ConditionFn) const`
- L180 _public function_ `IAnalyticsPropertyStore::EStatusCode Get(IAnalyticsPropertyStore* Store, FString& OutValue) const`
- L181 _public function_ `IAnalyticsPropertyStore::EStatusCode Update(IAnalyticsPropertyStore* Store, const TFunction<bool(FString& InOutValue)>& UpdateFn) const`

#### class `TAnalyticsProperty`  
`template<> class TAnalyticsProperty<FString>`  
_L173-184_
- desc: Specialization for FString because the caller can specifies a capacity when adding a string.
- L161 _public function_ `TAnalyticsProperty(const TCHAR* InKey) : Key(InKey)`
- L163 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const T& Value) const`
- L164 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const T& Value, const TFunction<bool(const T*, const T&)>& ConditionFn) const`
- L165 _public function_ `IAnalyticsPropertyStore::EStatusCode Get(IAnalyticsPropertyStore* Store, T& OutValue) const`
- L166 _public function_ `IAnalyticsPropertyStore::EStatusCode Update(IAnalyticsPropertyStore* Store, const TFunction<bool(T& InOutValue)>& UpdateFn) const`
- L168 _public member_ `const FString Key;`
- L178 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const FString& Value, uint32 CharCountCapacityHint = 0) const`
- L179 _public function_ `IAnalyticsPropertyStore::EStatusCode Set(IAnalyticsPropertyStore* Store, const FString& Value, const TFunction<bool(const FString*, const FString&)>& ConditionFn) const`
- L180 _public function_ `IAnalyticsPropertyStore::EStatusCode Get(IAnalyticsPropertyStore* Store, FString& OutValue) const`
- L181 _public function_ `IAnalyticsPropertyStore::EStatusCode Update(IAnalyticsPropertyStore* Store, const TFunction<bool(FString& InOutValue)>& UpdateFn) const`

### `Source/Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProvider.h` (Public)


#### enum `EAnalyticsRecordEventMode`  
`enum class EAnalyticsRecordEventMode : uint8`  
_L15-19_
- desc: Enum describing the supported record event modes @enum Cached use the existing system where the events are cached and flushed when possible @enum Immediate use the new system where events are immediately flushed to a HTTP request
- L17 _public enumerator_ `Cached`
- L18 _public enumerator_ `Immediate`

#### class `IAnalyticsProvider`  
`class IAnalyticsProvider`  
_L51-476_
- desc: Generic interface for an analytics provider. Other modules can define more and register them with this module. See FAnalytics for details. Easiest way to use this is like so: // MakeAnalyticsEventAttributeArray is a convenient way to efficiently make an array of attributes // Since it returns an unnamed temporary, the compiler automatically selects the move-aware version. AnalyticsProvider->RecordEvent(TEXT("MyEvent"), MakeAnalyticsEventAttributeArray("Attr1", "Value1", ... )); or: TArray<FAnalyticEventAttribute> Attrs; Attrs.Add(...); AnalyticsProvider->RecordEvent(TEXT("MyEvent"), Attrs); Several APIs build off the pure virtual ones. The following pure virtuals must be implemented by a derived class. virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) virtual void EndSession() virtual FString GetSessionID() const virtual bool SetSessionID(const FString& InSessionID) virtual void FlushEvents() virtual void SetUserID(const FString& InUserID) virtual FString GetUserID() const virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) There are several other methods to record specific types of events. They were added for legacy reasons to support specific third party implementations. Derived classes generally do not have to worry about them.
- L65 _public function_ `bool StartSession()` — Starts a session. It's technically legal to send events without starting a session. The use case is for backends and dedicated servers to send events on behalf of a user without technically affecting the session length of the local player. Local players log in and start/end the session, but remote players simply call SetUserID and start sending events, which is legal and analytics providers should gracefully handle this. Repeated calls to this method will be ignored. @returns true if the session started successfully.
- L75 _public prototype_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) = 0;` — Starts a session. See parameterless-version for contract details. @param Attributes attributes of the session. Arbitrary set of key/value pairs that will be sent with the StartSession event that this should also trigger.
- L82 _public function_ `bool StartSession(const FAnalyticsEventAttribute& Attribute)` — Overload for StartSession that takes a single attribute @param Attribute attribute name and value
- L93 _public function_ `bool StartSession(const FString& ParamName, const FString& ParamValue)` — Overload for StartSession that takes a single name/value pair @param ParamName attribute name @param ParamValue attribute value
- L101 _public prototype_ `virtual void EndSession() = 0;` — Ends the session. Usually no need to call explicitly, as the provider should do this for you when the instance is destroyed.
- L106 _public prototype_ `virtual FString GetSessionID() const = 0;` — Gets the opaque session identifier string for the provider.
- L114 _public prototype_ `virtual bool SetSessionID(const FString& InSessionID) = 0;` — Sets the session ID of the analytics session. This is not something you normally have to do, except for circumstances where you need to send events on behalf of another user (like a dedicated server sending events for the connected clients).
- L122 _public prototype_ `virtual void FlushEvents() = 0;` — Flush any cached events to the analytics provider. Note that not all providers support explicitly sending any cached events. In which case this method does nothing.
- L130 _public prototype_ `virtual void SetUserID(const FString& InUserID) = 0;` — Set the UserID for use with analytics. Some providers require a unique ID to be provided when supplying events, and some providers create their own. If you are using a provider that requires you to supply the ID, use this method to set it.
- L136 _public prototype_ `virtual FString GetUserID() const = 0;` — Gset the current UserID. Use -ANALYTICSUSERID=<Name> command line to force the provider to use a specific UserID for this run.
- L144 _public prototype_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes) = 0;` — Sets an array of attributes that will automatically be appended to any event that is sent. Logical effect is like adding them to all events before calling RecordEvent. Practically, it is implemented much more efficiently from a storage and allocation perspective.
- L149 _public prototype_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const = 0;` — @return the current array of default attributes.
- L156 _public prototype_ `virtual int32 GetDefaultEventAttributeCount() const = 0;` — Used with GetDefaultAttribute to iterate over the default attributes. @return the number of default attributes are currently being applied.
- L164 _public prototype_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int AttributeIndex) const = 0;` — Used with GetDefaultEventAttributeCount to iterate over the default attributes. Range checking is not done, similar to TArray. Use GetDefaultAttributeCount() first! @return one attribute of the default attributes so we don't have to copy the entire attribute array.
- L169 _public function_ `virtual void SetBuildInfo(const FString& InBuildInfo)` — Sets a user defined string as the build information/version for the session
- L177 _public function_ `virtual void SetGender(const FString& InGender)` — Sets the gender the game believes the user is as part of the session
- L185 _public function_ `virtual void SetLocation(const FString& InLocation)` — Sets the location the game believes the user is playing in as part of the session
- L193 _public function_ `virtual void SetAge(const int32 InAge)` — Sets the location the game believes the user is playing in as part of the session
- L204 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) = 0;` — Records a named event with an array of attributes @param EventName name of the event @param Attributes array of attribute name/value pairs
- L213 _public function_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes, EAnalyticsRecordEventMode Mode)` — RecordEvent overload to allow platforms to support events that are immediately sent @param EventName name of the event @param Attributes array of attribute name/value pairs @param Mode the record event mode, Cached or Immediate @see EAnalyticsRecordEventMode
- L223 _public function_ `void RecordEvent(const FString& EventName)` — Overload for RecordEvent that takes no parameters @param EventName name of the event
- L234 _public function_ `void RecordEvent(const FString& EventName, const FAnalyticsEventAttribute& Attribute)` — Overload for RecordEvent that takes a single attribute @param EventName name of the event @param Attribute attribute name and value
- L246 _public function_ `void RecordEvent(const FString& EventName, const FString& ParamName, const FString& ParamValue)` — Overload for RecordEvent that takes a single name/value pair @param EventName name of the event @param ParamName attribute name @param ParamValue attribute value
- L262 _public function_ `virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity)` — Record an in-game purchase of a an item. Note that not all providers support item purchase events. In this case this method is equivalent to sending a regular event with name "Item Purchase". @param ItemId - the ID of the item, should be registered with the provider first. @param Currency - the currency of the purchase (ie, Gold, Coins, etc), should be registered with the provider first. @param PerItemCost - the cost of one item in the currency given. @param ItemQuantity - the number of Items purchased.
- L280 _public function_ `virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& EventAttrs)` — Record an in-game purchase of a an item. Note that not all providers support item purchase events. In this case this method is equivalent to sending a regular event with name "Item Purchase". @param ItemId - the ID of the item, should be registered with the provider first. @param ItemQuantity - the number of Items purchased. @param EventAttrs - a list of key/value pairs to assign to this event
- L297 _public function_ `void RecordItemPurchase(const FString& ItemId, int ItemQuantity)` — Record an in-game purchase of a an item. Note that not all providers support item purchase events. In this case this method is equivalent to sending a regular event with name "Item Purchase". @param ItemId - the ID of the item, should be registered with the provider first. @param ItemQuantity - the number of Items purchased.
- L314 _public function_ `virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider)` — Record a purchase of in-game currency using real-world money. Note that not all providers support currency events. In this case this method is equivalent to sending a regular event with name "Currency Purchase". @param GameCurrencyType - type of in game currency purchased, should be registered with the provider first. @param GameCurrencyAmount - amount of in game currency purchased. @param RealCurrencyType - real-world currency type (like a 3-character ISO 4217 currency code, but provider dependent). @param RealMoneyCost - cost of the currency in real world money, expressed in RealCurrencyType units. @param PaymentProvider - Provider who brokered the transaction. Generally arbitrary, but examples are PayPal, Facebook Credits, App Store, etc.
- L333 _public function_ `virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs)` — Record a purchase of in-game currency using real-world money. Note that not all providers support currency events. In this case this method is equivalent to sending a regular event with name "Currency Purchase". @param GameCurrencyType - type of in game currency purchased, should be registered with the provider first. @param GameCurrencyAmount - amount of in game currency purchased. @param EventAttrs - a list of key/value pairs to assign to this event
- L350 _public function_ `virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount)` — Record an in-game purchase of a an item. Note that not all providers support item purchase events. In this case this method is equivalent to sending a regular event with name "Item Purchase". @param ItemId - the ID of the item, should be registered with the provider first. @param ItemQuantity - the number of Items purchased.
- L364 _public function_ `virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount)` — Record a gift of in-game currency from the game itself. Note that not all providers support currency events. In this case this method is equivalent to sending a regular event with name "Currency Given". @param GameCurrencyType - type of in game currency given, should be registered with the provider first. @param GameCurrencyAmount - amount of in game currency given.
- L379 _public function_ `virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs)` — Record a gift of in-game currency from the game itself. Note that not all providers support currency events. In this case this method is equivalent to sending a regular event with name "Currency Given". @param GameCurrencyType - type of in game currency given, should be registered with the provider first. @param GameCurrencyAmount - amount of in game currency given. @param EventAttrs - a list of key/value pairs to assign to this event
- L396 _public function_ `virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& EventAttrs)` — Records an error that has happened in the game Note that not all providers support all events. In this case this method is equivalent to sending a regular event with name "Game Error". @param Error - the error string to record @param EventAttrs - a list of key/value pairs to assign to this event
- L411 _public function_ `virtual void RecordError(const FString& Error)` — Records an error that has happened in the game Note that not all providers support all events. In this case this method is equivalent to sending a regular event with name "Game Error". @param Error - the error string to record
- L424 _public function_ `virtual void RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs)` — Record a player progression event that has happened in the game Note that not all providers support all events. In this case this method is equivalent to sending a regular event with name "Progression". @param Error - the error string to record
- L450 _public function_ `virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy)` — Record a player progression event that has happened in the game Note that not all providers support all events. In this case this method is equivalent to sending a regular event with name "Progression". @param Error - the error string to record
- L465 _public function_ `virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs)` — Record a player progression event that has happened in the game Note that not all providers support all events. In this case this method is equivalent to sending a regular event with name "Progression". @param Error - the error string to record
- L472 _public prototype_ `virtual ~IAnalyticsProvider() = default;`

#### Free symbols / members of external scopes

- L21 _prototype_ `const TCHAR* LexToString(EAnalyticsRecordEventMode Mode);`

### `Source/Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProviderModule.h` (Public)


#### class `IAnalyticsProviderModule`  
`class IAnalyticsProviderModule : public IModuleInterface`  
_L12-16_
- inherits: `IModuleInterface`
- desc: Generic interface for an analytics provider. Other modules can define more and register them with this module.
- L15 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const = 0;`

### `Source/Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsTracer.h` (Public)


#### class `IAnalyticsSpan`  
`class IAnalyticsSpan : FNoncopyable`  
_L20-65_
- inherits: `FNoncopyable`
- desc: IAnalyticsSpan Interface Inspired by OpenTelemety model for Tracer/Span. A span should be used to measure long running actions. It can be thought of as hierarchical timer object. A span capture event state within an array of EventAattributes and emit them with every event sent from this span A span can only be started via a IAnalyticsTracer interface, but can be Ended on demand Spans are arranged hierarchically and the expected behavior is for the parent span to end the spans of its children on during it's own End call Elapsed time should be calculated on each call, but on when the span is active Will send telemetry events via the IAnalyticsProvider
- L24 _public function_ `IAnalyticsSpan(const FName Name)`
- L25 _public prototype_ `virtual ~IAnalyticsSpan() = default;`
- L28 _public prototype_ `virtual void SetProvider(TSharedPtr<IAnalyticsProvider> AnalyticsProvider) = 0;` — Sets the analytics provider for the tracer
- L31 _public prototype_ `virtual void Start(const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) = 0;` — Start this span
- L34 _public prototype_ `virtual void End(const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) = 0;` — End this span
- L37 _public prototype_ `virtual void AddAttributes(const TArray<FAnalyticsEventAttribute>& AdditionalAttributes) = 0;` — Append attributes to this span context
- L40 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) = 0;` — Record an event from this span, appends the attributes for the span context
- L43 _public prototype_ `virtual const FName& GetName() const = 0;` — Get the internal name for the span
- L46 _public prototype_ `virtual const TArray<FAnalyticsEventAttribute>& GetAttributes()const = 0;` — Get context attributes for the span
- L49 _public prototype_ `virtual void SetStackDepth(uint32 Depth)=0;` — Set the scope depth for the span
- L52 _public prototype_ `virtual uint32 GetStackDepth() const = 0;` — Get the scope depth for the span
- L55 _public prototype_ `virtual double GetDuration() const = 0;` — Get the span duration in seconds
- L58 _public prototype_ `virtual double GetElapsedTime() = 0;` — Get the elapsed time for the span in seconds
- L61 _public prototype_ `virtual bool GetIsActive() const = 0;` — Is the span active?
- L64 _public prototype_ `virtual FGuid GetId() const = 0;` — Get unique Id?

#### class `IAnalyticsTracer`  
`class IAnalyticsTracer : FNoncopyable`  
_L76-119_
- inherits: `FNoncopyable`
- desc: IAnalyticsTracer Interface Inspired by OpenTelemety model for Tracer/Span. A tracer manages and create spans. It is not permitted to create or start a span outside of the owning tracer object. By default, new spans are added as a child of the last added span but can be added to a child of a specified parent for clarity The tracer has a valid SessionSpan object which is the root of the span hierarchy which is expected to be valid between the StartSession and EndSession calls. Spans are hierarchical and are not expected to overlap, even though the API or implementation might well allow that.
- L79 _public function_ `IAnalyticsTracer()`
- L80 _public prototype_ `virtual ~IAnalyticsTracer() = default;`
- L83 _public prototype_ `virtual void StartSession() =0;` — Starts a new session, creates and Starts the SessionSpan object
- L86 _public prototype_ `virtual void EndSession() = 0;` — Ends the running session and Ends the SessionSpan object
- L89 _public prototype_ `virtual void SetProvider(TSharedPtr<IAnalyticsProvider> AnalyticsProvider) =0;` — Sets the analytics provider for the tracer
- L92 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> StartSpan(const FName Name, TSharedPtr<IAnalyticsSpan> ParentSpan=TSharedPtr<IAnalyticsSpan>(), const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) = 0;` — Start a new span specifying an optional parent. EndSpan is called recursively on children. Parent attributes are passed onto children
- L95 _public prototype_ `virtual bool EndSpan(TSharedPtr<IAnalyticsSpan>, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {}) = 0;` — End an existing span
- L98 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> GetCurrentSpan() const = 0;` — Get the currently active span
- L101 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> GetSessionSpan() const = 0;` — Get the session span, this will always be valid for an active session
- L104 _public prototype_ `virtual TSharedPtr<IAnalyticsSpan> GetSpan(const FName Name) = 0;` — Get an active span by name, non active spans will not be available
- L107 _public function_ `TSharedPtr<IAnalyticsSpan> StartSpan(const FName Name, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {})` — Start a new span without a parent
- L113 _public function_ `bool EndSpan(const FName Name, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {})` — End an existing span by name
