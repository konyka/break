# Plugins / PropertyAnimatorCore

- module root: `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore`
- headers: 40; symbols: 885
- symbol kinds: class=33, delegate=4, enum=11, enumerator=38, function=137, member=115, prototype=512, struct=35
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, DeveloperSettings, Engine, Json, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, MovieScene

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Logs/PropertyAnimatorCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPropertyAnimatorCore, Log, All)`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Presets/PropertyAnimatorCoreJsonPresetArchive.h` (Private)


#### struct `FPropertyAnimatorCorePresetJsonArchiveImplementation`  
`struct FPropertyAnimatorCorePresetJsonArchiveImplementation : FPropertyAnimatorCorePresetArchiveImplementation`  
_L12-31_
- inherits: `FPropertyAnimatorCorePresetArchiveImplementation`
- L14 _public member_ `static inline const FName Type = TEXT("JSO`
- L16 _public prototype_ `static TSharedPtr<FPropertyAnimatorCorePresetJsonArchiveImplementation> Get();`
- L19 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetObjectArchive> CreateObject() override;`
- L20 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArrayArchive> CreateArray() override;`
- L21 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(bool bInValue) override;`
- L22 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(const FString& InValue) override;`
- L23 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(uint64 InValue) override;`
- L24 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(int64 InValue) override;`
- L25 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(double InValue) override;`
- L26 _public function_ `virtual FName GetImplementationType() const override`
- L30 _private member_ `static TSharedPtr<FPropertyAnimatorCorePresetJsonArchiveImplementation> Instance;`

#### struct `FPropertyAnimatorCorePresetJsonObjectArchive`  
`struct FPropertyAnimatorCorePresetJsonObjectArchive : FPropertyAnimatorCorePresetObjectArchive`  
_L33-68_
- inherits: `FPropertyAnimatorCorePresetObjectArchive`
- L35 _public prototype_ `FPropertyAnimatorCorePresetJsonObjectArchive();`
- L36 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonObjectArchive(TSharedRef<FJsonObject> InJsonObject);`
- L39 _public prototype_ `virtual bool Remove(const FString& InKey) override;`
- L40 _public prototype_ `virtual void Clear() override;`
- L42 _public prototype_ `virtual bool Set(const FString& InKey, TSharedRef<FPropertyAnimatorCorePresetArchive> InValue) override;`
- L43 _public prototype_ `virtual bool Set(const FString& InKey, bool bInValue) override;`
- L44 _public prototype_ `virtual bool Set(const FString& InKey, uint64 InValue) override;`
- L45 _public prototype_ `virtual bool Set(const FString& InKey, int64 InValue) override;`
- L46 _public prototype_ `virtual bool Set(const FString& InKey, double InValue) override;`
- L47 _public prototype_ `virtual bool Set(const FString& InKey, const FString& InValue) override;`
- L49 _public prototype_ `virtual bool Get(const FString& InKey, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L50 _public prototype_ `virtual bool Get(const FString& InKey, bool& bOutValue) const override;`
- L51 _public prototype_ `virtual bool Get(const FString& InKey, uint64& OutValue) const override;`
- L52 _public prototype_ `virtual bool Get(const FString& InKey, int64& OutValue) const override;`
- L53 _public prototype_ `virtual bool Get(const FString& InKey, double& OutValue) const override;`
- L54 _public prototype_ `virtual bool Get(const FString& InKey, FString& OutValue) const override;`
- L56 _public prototype_ `virtual bool ToString(FString& OutString) const override;`
- L57 _public prototype_ `virtual bool FromString(const FString& InString) override;`
- L58 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArchiveImplementation> GetImplementation() const override;`
- L61 _public function_ `TSharedPtr<FJsonObject> GetJsonObject() const`
- L67 _protected member_ `TSharedPtr<FJsonObject> JsonObject;`

#### struct `FPropertyAnimatorCorePresetJsonArrayArchive`  
`struct FPropertyAnimatorCorePresetJsonArrayArchive : FPropertyAnimatorCorePresetArrayArchive`  
_L70-100_
- inherits: `FPropertyAnimatorCorePresetArrayArchive`
- L72 _public prototype_ `FPropertyAnimatorCorePresetJsonArrayArchive() = default;`
- L73 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonArrayArchive(const TArray<TSharedPtr<FJsonValue>>& InJsonArray);`
- L76 _public prototype_ `virtual bool Get(int32 InIndex, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L77 _public prototype_ `virtual int32 Num() const override;`
- L78 _public prototype_ `virtual bool Remove(int32 InIndex) override;`
- L79 _public prototype_ `virtual void Clear() override;`
- L81 _public prototype_ `virtual bool Add(TSharedRef<FPropertyAnimatorCorePresetArchive> InValue) override;`
- L82 _public prototype_ `virtual bool Add(bool bInValue) override;`
- L83 _public prototype_ `virtual bool Add(uint64 InValue) override;`
- L84 _public prototype_ `virtual bool Add(int64 InValue) override;`
- L85 _public prototype_ `virtual bool Add(double InValue) override;`
- L86 _public prototype_ `virtual bool Add(const FString& InValue) override;`
- L88 _public prototype_ `virtual bool ToString(FString& OutString) const override;`
- L89 _public prototype_ `virtual bool FromString(const FString& InString) override;`
- L90 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArchiveImplementation> GetImplementation() const override;`
- L93 _public function_ `const TArray<TSharedPtr<FJsonValue>>& GetJsonValues() const`
- L99 _protected member_ `TArray<TSharedPtr<FJsonValue>> JsonValues;`

#### struct `FPropertyAnimatorCorePresetJsonValueArchive`  
`struct FPropertyAnimatorCorePresetJsonValueArchive : FPropertyAnimatorCorePresetValueArchive`  
_L102-129_
- inherits: `FPropertyAnimatorCorePresetValueArchive`
- L104 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonValueArchive(bool bInValue);`
- L105 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonValueArchive(uint64 InValue);`
- L106 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonValueArchive(int64 InValue);`
- L107 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonValueArchive(double InValue);`
- L108 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonValueArchive(const FString& InValue);`
- L109 _public prototype_ `explicit FPropertyAnimatorCorePresetJsonValueArchive(TSharedRef<FJsonValue> InJsonValue);`
- L112 _public prototype_ `virtual bool Get(double& OutValue) const override;`
- L113 _public prototype_ `virtual bool Get(bool& bOutValue) const override;`
- L114 _public prototype_ `virtual bool Get(FString& OutValue) const override;`
- L115 _public prototype_ `virtual bool Get(uint64& OutValue) const override;`
- L116 _public prototype_ `virtual bool Get(int64& OutValue) const override;`
- L117 _public prototype_ `virtual bool ToString(FString& OutString) const override;`
- L118 _public prototype_ `virtual bool FromString(const FString& InString) override;`
- L119 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArchiveImplementation> GetImplementation() const override;`
- L122 _public function_ `TSharedPtr<FJsonValue> GetJsonValue() const`
- L128 _protected member_ `TSharedPtr<FJsonValue> JsonValue;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Converters/PropertyAnimatorCoreFloatToBoolConverter.h` (Private)


#### class `UPropertyAnimatorCoreFloatToBoolConverter`  
`class UPropertyAnimatorCoreFloatToBoolConverter : public UPropertyAnimatorCoreConverterBase`  
_L9-19_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreConverterBase`
- L15 _public prototype_ `virtual bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const override;`
- L16 _public prototype_ `virtual bool Convert(const FPropertyBagPropertyDesc& InFromProperty, const FInstancedPropertyBag& InFromBag, const FPropertyBagPropertyDesc& InToProperty, FInstancedPropertyBag& InToBag, const TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase>& InRule) override;`
- L17 _public prototype_ `virtual UScriptStruct* GetConversionRuleStruct() const override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Converters/PropertyAnimatorCoreFloatToDoubleConverter.h` (Private)


#### class `UPropertyAnimatorCoreFloatToDoubleConverter`  
`class UPropertyAnimatorCoreFloatToDoubleConverter : public UPropertyAnimatorCoreConverterBase`  
_L9-19_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreConverterBase`
- L15 _public prototype_ `virtual bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const override;`
- L16 _public prototype_ `virtual bool Convert(const FPropertyBagPropertyDesc& InFromProperty, const FInstancedPropertyBag& InFromBag, const FPropertyBagPropertyDesc& InToProperty, FInstancedPropertyBag& InToBag, const TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase>& InRule) override;`
- L17 _public prototype_ `virtual UScriptStruct* GetConversionRuleStruct() const override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Converters/PropertyAnimatorCoreFloatToIntConverter.h` (Private)


#### class `UPropertyAnimatorCoreFloatToIntConverter`  
`class UPropertyAnimatorCoreFloatToIntConverter : public UPropertyAnimatorCoreConverterBase`  
_L9-19_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreConverterBase`
- L15 _public prototype_ `virtual bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const override;`
- L16 _public prototype_ `virtual bool Convert(const FPropertyBagPropertyDesc& InFromProperty, const FInstancedPropertyBag& InFromBag, const FPropertyBagPropertyDesc& InToProperty, FInstancedPropertyBag& InToBag, const TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase>& InRule) override;`
- L17 _public prototype_ `virtual UScriptStruct* GetConversionRuleStruct() const override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Converters/PropertyAnimatorCoreStringToTextConverter.h` (Private)


#### class `UPropertyAnimatorCoreStringToTextConverter`  
`class UPropertyAnimatorCoreStringToTextConverter : public UPropertyAnimatorCoreConverterBase`  
_L9-19_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreConverterBase`
- L15 _public prototype_ `virtual bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const override;`
- L16 _public prototype_ `virtual bool Convert(const FPropertyBagPropertyDesc& InFromProperty, const FInstancedPropertyBag& InFromBag, const FPropertyBagPropertyDesc& InToProperty, FInstancedPropertyBag& InToBag, const TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase>& InRule) override;`
- L17 _public prototype_ `virtual UScriptStruct* GetConversionRuleStruct() const override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Converters/PropertyAnimatorCoreTextToStringConverter.h` (Private)


#### class `UPropertyAnimatorCoreTextToStringConverter`  
`class UPropertyAnimatorCoreTextToStringConverter : public UPropertyAnimatorCoreConverterBase`  
_L9-19_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreConverterBase`
- L15 _public prototype_ `virtual bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const override;`
- L16 _public prototype_ `virtual bool Convert(const FPropertyBagPropertyDesc& InFromProperty, const FInstancedPropertyBag& InFromBag, const FPropertyBagPropertyDesc& InToProperty, FInstancedPropertyBag& InToBag, const TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase>& InRule) override;`
- L17 _public prototype_ `virtual UScriptStruct* GetConversionRuleStruct() const override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreBoolHandler.h` (Private)


#### class `UPropertyAnimatorCoreBoolHandler`  
`class UPropertyAnimatorCoreBoolHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-21_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any boolean property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreDoubleHandler.h` (Private)


#### class `UPropertyAnimatorCoreDoubleHandler`  
`class UPropertyAnimatorCoreDoubleHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-28_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any double property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool IsAdditiveSupported() const override;`
- L20 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L21 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L22 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L23 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L24 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L25 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L26 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreFloatHandler.h` (Private)


#### class `UPropertyAnimatorCoreFloatHandler`  
`class UPropertyAnimatorCoreFloatHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-28_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any float property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool IsAdditiveSupported() const override;`
- L20 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L21 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag&InValueB, FInstancedPropertyBag& OutValue) override;`
- L22 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L23 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L24 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L25 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L26 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreIntHandler.h` (Private)


#### class `UPropertyAnimatorCoreIntHandler`  
`class UPropertyAnimatorCoreIntHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-28_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any int property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool IsAdditiveSupported() const override;`
- L20 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L21 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag&InValueB, FInstancedPropertyBag& OutValue) override;`
- L22 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L23 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L24 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L25 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L26 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreRotatorHandler.h` (Private)


#### class `UPropertyAnimatorCoreRotatorHandler`  
`class UPropertyAnimatorCoreRotatorHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-28_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any rotator property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool IsAdditiveSupported() const override;`
- L20 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L21 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag&InValueB, FInstancedPropertyBag& OutValue) override;`
- L22 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L23 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L24 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L25 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L26 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreStringHandler.h` (Private)


#### class `UPropertyAnimatorCoreStringHandler`  
`class UPropertyAnimatorCoreStringHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-21_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any string property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreTextHandler.h` (Private)


#### class `UPropertyAnimatorCoreTextHandler`  
`class UPropertyAnimatorCoreTextHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-21_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any text property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Properties/Handlers/PropertyAnimatorCoreVectorHandler.h` (Private)


#### class `UPropertyAnimatorCoreVectorHandler`  
`class UPropertyAnimatorCoreVectorHandler : public UPropertyAnimatorCoreHandlerBase`  
_L10-28_
- reflection: `UCLASS(Transient)`
- inherits: `UPropertyAnimatorCoreHandlerBase`
- desc: Handles any vector 3d property values, get and set handler
- L16 _public prototype_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const override;`
- L17 _public prototype_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`
- L18 _public prototype_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L19 _public prototype_ `virtual bool IsAdditiveSupported() const override;`
- L20 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L21 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L22 _public prototype_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L23 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue) override;`
- L24 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue) override;`
- L25 _public prototype_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue) override;`
- L26 _public prototype_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue) override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Sequencer/MovieSceneAnimatorEvalTemplate.h` (Private)


#### struct `FMovieSceneAnimatorEvalTemplate`  
`struct FMovieSceneAnimatorEvalTemplate : public FMovieSceneEvalTemplate`  
_L11-36_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L15 _public prototype_ `FMovieSceneAnimatorEvalTemplate() = default;`
- L17 _public function_ `explicit FMovieSceneAnimatorEvalTemplate(const FMovieSceneAnimatorSectionData& InSectionData) : SectionData(InSectionData)`
- L22 _public function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L27 _public function_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& InOperand, const FMovieSceneContext& InContext, const FPersistentEvaluationData& InPersistentData, FMovieSceneExecutionTokens& InExecutionTokens) const override`
- L35 _private member_ `FMovieSceneAnimatorSectionData SectionData;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Sequencer/MovieSceneAnimatorExecutionToken.h` (Private)


#### struct `FMovieSceneAnimatorPreAnimatedTokenProducer`  
`struct FMovieSceneAnimatorPreAnimatedTokenProducer : IMovieScenePreAnimatedTokenProducer`  
_L11-43_
- inherits: `IMovieScenePreAnimatedTokenProducer`
- desc: Used to restore state back to previous when outside section
- L13 _public function_ `FMovieSceneAnimatorPreAnimatedTokenProducer()`
- L17 _public function_ `virtual IMovieScenePreAnimatedTokenPtr CacheExistingState(UObject& InObject) const override`
- L39 _public function_ `static FMovieSceneAnimTypeID GetAnimTypeID()`

#### struct `FMovieSceneAnimatorPreAnimatedTokenProducer::CacheExistingState::FMovieSceneAnimatorPreAnimatedToken`  
`struct FMovieSceneAnimatorPreAnimatedToken : IMovieScenePreAnimatedToken`  
_L19-33_
- inherits: `IMovieScenePreAnimatedToken`
- L21 _public function_ `FMovieSceneAnimatorPreAnimatedToken()`
- L25 _public function_ `virtual void RestoreState(UObject& InObject, const UE::MovieScene::FRestoreStateParams& InParams) override`

#### struct `FMovieSceneAnimatorExecutionToken`  
`struct FMovieSceneAnimatorExecutionToken : IMovieSceneExecutionToken`  
_L46-152_
- inherits: `IMovieSceneExecutionToken`
- desc: Used to evaluate active section
- L48 _public function_ `FMovieSceneAnimatorExecutionToken(const FMovieSceneAnimatorSectionData& InSectionData) : SectionData(InSectionData)`
- L53 _public function_ `virtual void Execute(const FMovieSceneContext& InContext, const FMovieSceneEvaluationOperand& InOperand, FPersistentEvaluationData& InPersistentData, IMovieScenePlayer& InPlayer) override`
- L151 _private member_ `FMovieSceneAnimatorSectionData SectionData;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Settings/PropertyAnimatorCoreSettings.h` (Private)


#### class `UPropertyAnimatorCoreSettings`  
`class UPropertyAnimatorCoreSettings : public UDeveloperSettings`  
_L10-28_
- reflection: `UCLASS(Config=Engine, meta=(DisplayName="Property Animator Core"))`
- inherits: `UDeveloperSettings`
- desc: Settings for motion design PropertyAnimatorCore plugin
- L15 _public prototype_ `static UPropertyAnimatorCoreSettings* Get();`
- L17 _public prototype_ `UPropertyAnimatorCoreSettings();`
- L19 _public prototype_ `FName GetDefaultTimeSourceName() const;`
- L23 _protected prototype_ `TArray<FName> GetTimeSourceNames() const;` — `UFUNCTION()`
- L27 _protected member_ `FName DefaultTimeSourceName = NAME_None;` — `UPROPERTY(Config, EditAnywhere, Category="Animator", meta=(GetOptions="GetTimeSourceNames"))` — The default time source applied on animator by default

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Animators/PropertyAnimatorCoreBase.h` (Public)


#### enum `EPropertyAnimatorPropertySupport`  
`enum class EPropertyAnimatorPropertySupport : uint8`  
_L16-22_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `Incomplete = 1 << 0`
- L20 _public enumerator_ `Complete = 1 << 1`
- L21 _public enumerator_ `All = Incomplete | Complete`

#### struct `FPropertyAnimatorCoreMetadata`  
`struct FPropertyAnimatorCoreMetadata`  
_L24-30_
- L26 _public member_ `FName Name = NAME_None;`
- L27 _public member_ `FText DisplayName = FText::GetEmpty();`
- L28 _public member_ `FText Description = FText::GetEmpty();`
- L29 _public member_ `FName Category = TEXT("Def`

#### enum `EPropertyAnimatorCoreUpdateEvent`  
`enum class EPropertyAnimatorCoreUpdateEvent : uint8`  
_L32-39_
- L34 _public enumerator_ `User`
- L35 _public enumerator_ `Undo`
- L36 _public enumerator_ `Load`
- L37 _public enumerator_ `Duplicate`
- L38 _public enumerator_ `Destroyed`

#### class `UPropertyAnimatorCoreBase`  
`class UPropertyAnimatorCoreBase : public UObject, public IPropertyAnimatorCorePresetable`  
_L43-406_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, AutoExpandCategories=("Animator"))`
- inherits: `UObject,IPropertyAnimatorCorePresetable`
- desc: Abstract base class for any Animator, holds a set of linked properties
- L51 _public member_ `static constexpr const TCHAR* TimeElapsedParameterName = TEXT("Tim`
- L52 _public member_ `static constexpr const TCHAR* MagnitudeParameterName = TEXT("Mag`
- L53 _public member_ `static constexpr const TCHAR* FrequencyParameterName = TEXT("Fre`
- L54 _public member_ `static constexpr const TCHAR* AlphaParameterName = TEXT("Alp`
- L56 _public function_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAnimatorUpdated, UPropertyAnimatorCoreComponent* , UPropertyAnimatorCoreBase* , EPropertyAnimatorCoreUpdateEvent ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimatorPropertyUpdated, UPropertyAnimatorCoreBase* , const FPropertyAnimatorCoreData& ) static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorAdded()`
- L64 _public function_ `static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorRemoved()`
- L69 _public function_ `static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorRenamed()`
- L74 _public function_ `static FOnAnimatorPropertyUpdated::RegistrationType& OnPropertyAnimatorPropertyLinked()`
- L79 _public function_ `static FOnAnimatorPropertyUpdated::RegistrationType& OnPropertyAnimatorPropertyUnlinked()`
- L85 _public prototype_ `static FName GetAnimatorEnabledPropertyName();`
- L86 _public prototype_ `static FName GetLinkedPropertiesPropertyName();`
- L89 _public prototype_ `UPropertyAnimatorCoreBase();`
- L91 _public prototype_ `AActor* GetAnimatorActor() const;`
- L93 _public prototype_ `UPropertyAnimatorCoreComponent* GetAnimatorComponent() const;`
- L96 _public prototype_ `void SetAnimatorEnabled(bool bInIsEnabled);` — Set the state of this animator
- L97 _public function_ `bool GetAnimatorEnabled() const`
- L102 _public prototype_ `void SetOverrideTimeSource(bool bInOverride);`
- L103 _public function_ `bool GetOverrideTimeSource() const`
- L109 _public prototype_ `void SetTimeSourceName(FName InTimeSourceName);` — Set the time source name to use
- L110 _public function_ `FName GetTimeSourceName() const`
- L116 _public prototype_ `UPropertyAnimatorCoreTimeSourceBase* GetActiveTimeSource() const;` — Get the active time source
- L119 _public prototype_ `void SetAnimatorDisplayName(FName InName);` — Set the display name of this animator
- L121 _public function_ `FName GetAnimatorDisplayName() const`
- L127 _public prototype_ `TSharedRef<const FPropertyAnimatorCoreMetadata> GetAnimatorMetadata() const;` — Gets the animator metadata
- L130 _public prototype_ `TSet<FPropertyAnimatorCoreData> GetLinkedProperties() const;` — Get all linked properties within this animator
- L133 _public prototype_ `int32 GetLinkedPropertiesCount() const;` — Get linked properties count within this animator
- L136 _public prototype_ `UPropertyAnimatorCoreContext* LinkProperty(const FPropertyAnimatorCoreData& InLinkProperty);` — Link property to this Animator to be able to drive it
- L139 _public prototype_ `bool UnlinkProperty(const FPropertyAnimatorCoreData& InUnlinkProperty);` — Unlink property from this Animator
- L142 _public prototype_ `bool IsPropertyLinked(const FPropertyAnimatorCoreData& InPropertyData) const;` — Checks if this Animator is controlling this property
- L145 _public prototype_ `bool IsPropertiesLinked(const TSet<FPropertyAnimatorCoreData>& InProperties) const;` — Checks if this animator is controlling all properties
- L148 _public prototype_ `TSet<FPropertyAnimatorCoreData> GetInnerPropertiesLinked(const FPropertyAnimatorCoreData& InPropertyData) const;` — Returns all inner properties that are controlled by this Animator linked to member property
- L154 _public prototype_ `bool GetPropertiesSupported(const FPropertyAnimatorCoreData& InPropertyData, TSet<FPropertyAnimatorCoreData>& OutProperties, uint8 InSearchDepth = 1, EPropertyAnimatorPropertySupport InSupportExpected = EPropertyAnimatorPropertySupport::All) const;` — Checks recursively for properties that are supported by this Animator, calls IsPropertySupported to check Stops when the InSearchDepth has been reached otherwise continues to gather supported properties
- L157 _public prototype_ `EPropertyAnimatorPropertySupport GetPropertySupport(const FPropertyAnimatorCoreData& InPropertyData) const;` — Retrieves the support level of a property
- L160 _public prototype_ `bool HasPropertySupport(const FPropertyAnimatorCoreData& InPropertyData, EPropertyAnimatorPropertySupport InSupportExpected = EPropertyAnimatorPropertySupport::All) const;` — Checks if a property support is available
- L163 _public function_ `virtual EPropertyAnimatorPropertySupport IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const` — Override this to check if a property is supported by this animator
- L169 _public function_ `virtual bool IsTimeSourceSupported(UPropertyAnimatorCoreTimeSourceBase* InTimeSource) const` — Checks whether a time source is supported on this animator
- L175 _public prototype_ `UPropertyAnimatorCoreContext* GetLinkedPropertyContext(const FPropertyAnimatorCoreData& InProperty) const;` — Get the context for the linked property
- L177 _public function_ `TConstArrayView<UPropertyAnimatorCoreContext*> GetLinkedPropertiesContext() const`
- L185 _public function_ `InContextClass* GetLinkedPropertyContext(const FPropertyAnimatorCoreData& InProperty) const`
- L193 _public function_ `bool ForEachLinkedProperty(TFunctionRef<bool(InContextClass*, const FPropertyAnimatorCoreData&)> InFunction, bool bInResolve = true) const`
- L228 _public prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L229 _public prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L234 _protected prototype_ `virtual void PostCDOContruct() override;`
- L235 _protected prototype_ `virtual void BeginDestroy() override;`
- L236 _protected prototype_ `virtual void PostLoad() override;`
- L237 _protected prototype_ `virtual void PostEditImport() override;`
- L238 _protected prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& InDupParams) override;`
- L239 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type InDuplicateMode) override;`
- L241 _protected prototype_ `virtual void PreEditUndo() override;`
- L242 _protected prototype_ `virtual void PostEditUndo() override;`
- L243 _protected prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;`
- L244 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L249 _protected prototype_ `void UpdateAnimatorDisplayName();` — Update display name based on linked properties
- L252 _protected function_ `void EvaluateEachLinkedProperty( TFunctionRef<bool( UPropertyAnimatorCoreContext* , const FPropertyAnimatorCoreData& , FInstancedPropertyBag& , int32 InRangeIndex , int32 InRangeMax)> InFunction )` — Used to evaluate linked properties, assign the result in the property bag and return true on success to update property value
- L291 _protected function_ `virtual void OnAnimatorDisplayNameChanged()`
- L293 _protected prototype_ `virtual void OnAnimatorAdded(EPropertyAnimatorCoreUpdateEvent InType);`
- L294 _protected prototype_ `virtual void OnAnimatorRemoved(EPropertyAnimatorCoreUpdateEvent InType);`
- L296 _protected prototype_ `virtual void OnAnimatorEnabled(EPropertyAnimatorCoreUpdateEvent InType);`
- L297 _protected prototype_ `virtual void OnAnimatorDisabled(EPropertyAnimatorCoreUpdateEvent InType);`
- L299 _protected function_ `virtual void OnAnimatorRegistered(FPropertyAnimatorCoreMetadata& InMetadata)`
- L301 _protected function_ `virtual void OnTimeSourceChanged()`
- L304 _protected prototype_ `virtual TSubclassOf<UPropertyAnimatorCoreContext> GetPropertyContextClass(const FPropertyAnimatorCoreData& InProperty);` — Returns the property context class to use
- L306 _protected function_ `virtual void OnPropertyLinked(UPropertyAnimatorCoreContext* InLinkedProperty, EPropertyAnimatorPropertySupport InSupport)`
- L307 _protected function_ `virtual void OnPropertyUnlinked(UPropertyAnimatorCoreContext* InUnlinkedProperty)`
- L310 _protected function_ `virtual void EvaluateProperties(FInstancedPropertyBag& InParameters)` — Apply animators effect on linked properties
- L314 _private member_ `static FOnAnimatorUpdated OnAnimatorAddedDelegate;` — Called when a Animator is created
- L317 _private member_ `static FOnAnimatorUpdated OnAnimatorRemovedDelegate;` — Called when a Animator is removed
- L320 _private member_ `static FOnAnimatorUpdated OnAnimatorRenamedDelegate;` — Called when a Animator is renamed
- L323 _private member_ `static FOnAnimatorPropertyUpdated OnAnimatorPropertyLinkedDelegate;` — Called when a property is linked to a Animator
- L326 _private member_ `static FOnAnimatorPropertyUpdated OnAnimatorPropertyUnlinkedDelegate;` — Called when a property is unlinked to a Animator
- L329 _private prototype_ `void RestoreProperties();` — Restore modified properties to original state
- L332 _private prototype_ `void SaveProperties();` — Allocate and saves properties in the property bag
- L335 _private prototype_ `void EvaluateAnimator(FInstancedPropertyBag& InParameters);` — Called by the component to evaluate this animator
- L337 _private prototype_ `void OnObjectReplaced(const TMap<UObject*, UObject*>& InReplacementMap);`
- L341 _private prototype_ `void OnPreSaveWorld(UWorld* InWorld, FObjectPreSaveContext InContext);` — Needed to restore properties and stop animation before world is saved
- L344 _private prototype_ `void OnPreBeginPIE(bool bInSimulating);` — Needed to restore properties and reset animation before PIE is started
- L347 _private prototype_ `void OnAnimatorEnabledChanged(EPropertyAnimatorCoreUpdateEvent InType);`
- L349 _private prototype_ `void CleanLinkedProperties();`
- L351 _private prototype_ `void OnTimeSourceNameChanged();`
- L354 _private prototype_ `void OnTimeSourceEnterIdleState();` — Called when time source enters idle/invalid state
- L357 _private prototype_ `void ResolvePropertiesOwner(AActor* InNewOwner = nullptr);` — Called after an action that causes the owner to change
- L359 _private prototype_ `UPropertyAnimatorCoreTimeSourceBase* FindOrAddTimeSource(FName InTimeSourceName);`
- L362 _private prototype_ `TArray<FName> GetTimeSourceNames() const;` — `UFUNCTION()`
- L366 _private member_ `bool bAnimatorEnabled = true;` — `UPROPERTY(EditInstanceOnly, Getter="GetAnimatorEnabled", Setter="SetAnimatorEnabled", Category="Animator", meta=(DisplayPriority="0", AllowPrivateAccess="true"))` — Enable control of properties linked to this Animator
- L370 _private member_ `FName AnimatorDisplayName;` — `UPROPERTY(VisibleInstanceOnly, Category="Animator", meta=(EditCondition="false", EditConditionHides))` — Display name as title property for component array, hide it but must be visible to editor for array title property
- L374 _private member_ `TArray<TObjectPtr<UPropertyAnimatorCoreContext>> LinkedProperties;` — `UPROPERTY(EditInstanceOnly, NoClear, Export, Instanced, EditFixedSize, Category="Animator", meta=(EditFixedOrder))` — Context for properties linked to this Animator
- L378 _private member_ `bool bOverrideTimeSource = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetOverrideTimeSource", Getter="GetOverrideTimeSource", Category="Animator", meta=(InlineEditConditionToggle))` — Use the global time source or override it on this animator
- L382 _private member_ `FName TimeSourceName = NAME_None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(GetOptions="GetTimeSourceNames", EditCondition="bOverrideTimeSource", NoResetToDefault))` — The time source to use
- L386 _private member_ `TObjectPtr<UPropertyAnimatorCoreTimeSourceBase> ActiveTimeSource;` — `UPROPERTY(VisibleInstanceOnly, Instanced, Transient, DuplicateTransient, Category="Animator", meta=(EditCondition="bOverrideTimeSource", EditConditionHides, HideEditConditionToggle))` — Active time source with its options, determined by its name
- L391 _private member_ `TMap<FName, TObjectPtr<UPropertyAnimatorCoreTimeSourceBase>> TimeSourcesInstances;` — `UE_DEPRECATED(5.5, "Use TimeSources instead")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use TimeSources instead"))` — The cached time source used by this Animator
- L395 _private member_ `TArray<TObjectPtr<UPropertyAnimatorCoreTimeSourceBase>> TimeSources;` — `UPROPERTY()` — Cached time sources used by this animator
- L399 _private member_ `FInstancedPropertyBag EvaluatedPropertyValues;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Evaluated property container, reset on every update round
- L402 _private member_ `bool bEvaluatingProperties = false;` — Are we evaluating properties currently
- L405 _private member_ `TSharedPtr<FPropertyAnimatorCoreMetadata> Metadata;` — Animator metadata, same for all instances of this class

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAnimatorUpdated, UPropertyAnimatorCoreComponent* , UPropertyAnimatorCoreBase* , EPropertyAnimatorCoreUpdateEvent ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimatorPropertyUpdated, UPropertyAnimatorCoreBase* , const FPropertyAnimatorCoreData& ) static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorAdded() { return OnAnimatorAddedDelegate; } static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorRemoved() { return OnAnimatorRemovedDelegate; } static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorRenamed() { return OnAnimatorRenamedDelegate; } static FOnAnimatorPropertyUpdated::RegistrationType& OnPropertyAnimatorPropertyLinked() { return OnAnimatorPropertyLinkedDelegate; } static FOnAnimatorPropertyUpdated::RegistrationType& OnPropertyAnimatorPropertyUnlinked() { return OnAnimatorPropertyUnlinkedDelegate; } #if WITH_EDITOR static FName GetAnimatorEnabledPropertyName();`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimatorPropertyUpdated, UPropertyAnimatorCoreBase* , const FPropertyAnimatorCoreData& ) static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorAdded() { return OnAnimatorAddedDelegate; } static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorRemoved() { return OnAnimatorRemovedDelegate; } static FOnAnimatorUpdated::RegistrationType& OnPropertyAnimatorRenamed() { return OnAnimatorRenamedDelegate; } static FOnAnimatorPropertyUpdated::RegistrationType& OnPropertyAnimatorPropertyLinked() { return OnAnimatorPropertyLinkedDelegate; } static FOnAnimatorPropertyUpdated::RegistrationType& OnPropertyAnimatorPropertyUnlinked() { return OnAnimatorPropertyUnlinkedDelegate; } #if WITH_EDITOR static FName GetAnimatorEnabledPropertyName();`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Components/PropertyAnimatorCoreComponent.h` (Public)


#### class `UPropertyAnimatorCoreComponent`  
`class UPropertyAnimatorCoreComponent : public UActorComponent`  
_L11-162_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(Custom), AutoExpandCategories=("Animator"), HideCategories=("Activation", "Cooking", "AssetUserData", "Collision", "Tags", "ComponentReplication", "Navigation", "Variable", "Replication"), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: A container for controllers that holds properties in this actor
- L19 _public prototype_ `static UPropertyAnimatorCoreComponent* FindOrAdd(AActor* InActor);` — Create an instance of this component class and adds it to an actor
- L22 _public prototype_ `static FName GetAnimatorsEnabledPropertyName();`
- L23 _public prototype_ `static FName GetPropertyAnimatorsPropertyName();`
- L26 _public prototype_ `UPropertyAnimatorCoreComponent();`
- L28 _public prototype_ `void SetAnimators(const TArray<TObjectPtr<UPropertyAnimatorCoreBase>>& InAnimators);`
- L29 _public function_ `TConstArrayView<TObjectPtr<UPropertyAnimatorCoreBase>> GetAnimators() const`
- L34 _public function_ `int32 GetAnimatorsCount() const`
- L40 _public prototype_ `void SetAnimatorsEnabled(bool bInEnabled);` — Set the state of all animators in this component
- L41 _public function_ `bool GetAnimatorsEnabled() const`
- L47 _public prototype_ `void SetAnimatorsMagnitude(float InMagnitude);` — Set the magnitude for all animators in this component
- L48 _public function_ `float GetAnimatorsMagnitude() const`
- L53 _public prototype_ `void SetAnimatorsTimeSourceName(FName InTimeSourceName);`
- L54 _public function_ `FName GetAnimatorsTimeSourceName() const`
- L59 _public function_ `UPropertyAnimatorCoreTimeSourceBase* GetAnimatorsActiveTimeSource() const`
- L65 _public prototype_ `void ForEachAnimator(TFunctionRef<bool(UPropertyAnimatorCoreBase*)> InFunction) const;` — Process a function for each controller, stops when false is returned otherwise continue until the end
- L68 _public prototype_ `bool ShouldAnimate() const;` — Checks if this component animators should be active
- L71 _protected prototype_ `static FName GetAnimatorName(const UPropertyAnimatorCoreBase* InAnimator);`
- L74 _protected prototype_ `virtual void OnComponentCreated() override;`
- L75 _protected prototype_ `virtual void OnComponentDestroyed(bool bInDestroyingHierarchy) override;`
- L76 _protected prototype_ `virtual void TickComponent(float InDeltaTime, ELevelTick InTickType, FActorComponentTickFunction* InTickFunction) override;`
- L80 _protected prototype_ `virtual void PostLoad() override;`
- L81 _protected prototype_ `virtual void PostEditImport() override;`
- L82 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type InMode) override;`
- L84 _protected prototype_ `virtual void PreEditUndo() override;`
- L85 _protected prototype_ `virtual void PostEditUndo() override;`
- L86 _protected prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L87 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L93 _protected function_ `template<typename InAnimatorClass = UPropertyAnimatorCoreBase, typename = typename TEnableIf<TIsDerivedFrom<InAnimatorClass, UPropertyAnimatorCoreBase>::Value>::Type> InAnimatorClass* AddAnimator()` — Adds a new controller and returns it casted
- L100 _protected prototype_ `UPropertyAnimatorCoreBase* AddAnimator(const UClass* InAnimatorClass);` — Adds a new animator of that class
- L103 _protected prototype_ `UPropertyAnimatorCoreBase* CloneAnimator(UPropertyAnimatorCoreBase* InAnimator);` — Clones an existing animator
- L106 _protected prototype_ `bool RemoveAnimator(UPropertyAnimatorCoreBase* InAnimator);` — Removes an existing animator
- L109 _protected prototype_ `void OnAnimatorsSetEnabled(const UWorld* InWorld, bool bInEnabled, bool bInTransact);` — Change global state for animators
- L112 _protected prototype_ `void OnAnimatorsChanged(EPropertyAnimatorCoreUpdateEvent InType);` — Callback when PropertyAnimators changed
- L115 _protected prototype_ `void OnAnimatorsEnabledChanged(EPropertyAnimatorCoreUpdateEvent InType);` — Callback when global enabled state is changed
- L118 _protected prototype_ `void OnTimeSourceNameChanged();` — Callback when global time source name is changed
- L121 _protected prototype_ `bool EvaluateAnimators();` — Evaluate only specified animators
- L124 _protected prototype_ `UPropertyAnimatorCoreTimeSourceBase* FindOrAddTimeSource(FName InTimeSourceName);` — Finds a cached time source with this name or creates a new one
- L127 _protected prototype_ `TArray<FName> GetTimeSourceNames() const;` — `UFUNCTION()`
- L131 _protected member_ `TArray<TObjectPtr<UPropertyAnimatorCoreBase>> PropertyAnimators;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Export, Instanced, Setter="SetAnimators", Category="Animator", meta=(TitleProperty="AnimatorDisplayName"))` — Animators linked to this actor, they contain only properties within this actor
- L135 _protected member_ `bool bAnimatorsEnabled = true;` — `UPROPERTY(EditInstanceOnly, Getter="GetAnimatorsEnabled", Setter="SetAnimatorsEnabled", Category="Animator", meta=(DisplayPriority="0", AllowPrivateAccess="true"))` — Global state for all animators controlled by this component
- L139 _protected member_ `float AnimatorsMagnitude = 1.f;` — `UPROPERTY(EditInstanceOnly, Getter, Setter, DisplayName="Global Magnitude", Category="Animator", meta=(ClampMin="0", ClampMax="1", UIMin="0", UIMax="1", AllowPrivateAccess="true"))` — Global magnitude for all animators controlled by this component
- L143 _protected member_ `FName AnimatorsTimeSourceName = NAME_None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Global Time Source Name", Category="Animator", meta=(GetOptions="GetTimeSourceNames", NoResetToDefault))` — The global time source to use, can be overriden in animator
- L147 _protected member_ `TObjectPtr<UPropertyAnimatorCoreTimeSourceBase> ActiveAnimatorsTimeSource;` — `UPROPERTY(VisibleInstanceOnly, Instanced, Transient, DuplicateTransient, Category="Animator")` — Active time source with its options, determined by its name
- L153 _private member_ `TSet<TObjectPtr<UPropertyAnimatorCoreBase>> Animators;` — `UE_DEPRECATED(5.5, "Moved to PropertyAnimators")` — `UPROPERTY()` — Deprecated property set, will be migrated to PropertyAnimators property on load
- L157 _private member_ `TArray<TObjectPtr<UPropertyAnimatorCoreBase>> PropertyAnimatorsInternal;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient, NonTransactional)` — Transient copy of property animators when changes are detected to see the diff only
- L161 _private member_ `TArray<TObjectPtr<UPropertyAnimatorCoreTimeSourceBase>> TimeSources;` — `UPROPERTY()` — Cached time sources used by this animator component

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Presets/PropertyAnimatorCoreAnimatorPreset.h` (Public)


#### class `UPropertyAnimatorCoreAnimatorPreset`  
`class UPropertyAnimatorCoreAnimatorPreset : public UPropertyAnimatorCorePresetBase`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyAnimatorCorePresetBase`
- desc: Animator preset class used to import/export animator data
- L22 _public prototype_ `virtual bool IsPresetApplied(const UPropertyAnimatorCoreBase* InAnimator) const override;`
- L23 _public prototype_ `virtual bool IsPresetSupported(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator) const override;`
- L24 _public prototype_ `virtual bool ApplyPreset(UPropertyAnimatorCoreBase* InAnimator) override;`
- L25 _public prototype_ `virtual bool UnapplyPreset(UPropertyAnimatorCoreBase* InAnimator) override;`
- L26 _public prototype_ `virtual void CreatePreset(FName InName, const TArray<IPropertyAnimatorCorePresetable*>& InPresetableItem) override;`
- L27 _public prototype_ `virtual bool LoadPreset() override;`
- L30 _public prototype_ `UPropertyAnimatorCoreBase* GetAnimatorTemplate() const;`
- L35 _protected member_ `TSubclassOf<UPropertyAnimatorCoreBase> TargetAnimatorClass;` — `UPROPERTY(Transient)` — Animator class to target for this preset
- L37 _protected member_ `TSharedPtr<FPropertyAnimatorCorePresetArchive> AnimatorPreset;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Presets/PropertyAnimatorCorePresetArchive.h` (Public)


#### enum `EPropertyAnimatorCorePresetArchiveType`  
`enum class EPropertyAnimatorCorePresetArchiveType : uint8`  
_L15-23_
- desc: Enumerates all possible value type stored in archive
- L18 _public enumerator_ `Object` — Used for struct, object, maps
- L20 _public enumerator_ `Array` — Used for array, set
- L22 _public enumerator_ `Value` — Used for primitive types like number, string, bool

#### struct `FPropertyAnimatorCorePresetArchiveImplementation`  
`struct FPropertyAnimatorCorePresetArchiveImplementation : TSharedFromThis<FPropertyAnimatorCorePresetArchiveImplementation>`  
_L26-38_
- inherits: `TSharedFromThis<FPropertyAnimatorCorePresetArchiveImplementation>`
- desc: Represents a custom implementation to create value in the implementation format, should be a singleton
- L28 _public prototype_ `virtual ~FPropertyAnimatorCorePresetArchiveImplementation() = default;`
- L30 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetObjectArchive> CreateObject() = 0;`
- L31 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArrayArchive> CreateArray() = 0;`
- L32 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(bool bInValue) = 0;`
- L33 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(uint64 InValue) = 0;`
- L34 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(int64 InValue) = 0;`
- L35 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(double InValue) = 0;`
- L36 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetValueArchive> CreateValue(const FString& InValue) = 0;`
- L37 _public prototype_ `virtual FName GetImplementationType() const = 0;`

#### struct `FPropertyAnimatorCorePresetArchive`  
`struct FPropertyAnimatorCorePresetArchive : TSharedFromThis<FPropertyAnimatorCorePresetArchive>`  
_L41-63_
- inherits: `TSharedFromThis<FPropertyAnimatorCorePresetArchive>`
- desc: Represents an abstract archive for preset system, underlying implementation can vary
- L43 _public prototype_ `virtual ~FPropertyAnimatorCorePresetArchive() = default;`
- L45 _public prototype_ `bool IsObject() const;`
- L46 _public prototype_ `bool IsArray() const;`
- L47 _public prototype_ `bool IsValue() const;`
- L48 _public prototype_ `EPropertyAnimatorCorePresetArchiveType GetType() const;`
- L50 _public function_ `virtual TSharedPtr<const FPropertyAnimatorCorePresetObjectArchive> AsObject() const`
- L51 _public function_ `virtual TSharedPtr<const FPropertyAnimatorCorePresetArrayArchive> AsArray() const`
- L52 _public function_ `virtual TSharedPtr<const FPropertyAnimatorCorePresetValueArchive> AsValue() const`
- L54 _public function_ `virtual TSharedPtr<FPropertyAnimatorCorePresetObjectArchive> AsMutableObject()`
- L55 _public function_ `virtual TSharedPtr<FPropertyAnimatorCorePresetArrayArchive> AsMutableArray()`
- L56 _public function_ `virtual TSharedPtr<FPropertyAnimatorCorePresetValueArchive> AsMutableValue()`
- L58 _public prototype_ `virtual bool FromString(const FString& InString) = 0;`
- L59 _public prototype_ `virtual bool ToString(FString& OutString) const = 0;`
- L61 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArchiveImplementation> GetImplementation() const = 0;`
- L62 _public prototype_ `FName GetImplementationType() const;`

#### struct `FPropertyAnimatorCorePresetObjectArchive`  
`struct FPropertyAnimatorCorePresetObjectArchive : FPropertyAnimatorCorePresetArchive`  
_L66-90_
- inherits: `FPropertyAnimatorCorePresetArchive`
- desc: Represents an abstract object archive for preset system, underlying implementation can vary
- L69 _public prototype_ `virtual TSharedPtr<const FPropertyAnimatorCorePresetObjectArchive> AsObject() const override;`
- L70 _public prototype_ `virtual TSharedPtr<FPropertyAnimatorCorePresetObjectArchive> AsMutableObject() override;`
- L73 _public prototype_ `bool Has(const FString& InKey, TOptional<EPropertyAnimatorCorePresetArchiveType> InType = {}) const;`
- L74 _public prototype_ `virtual bool Remove(const FString& InKey) = 0;`
- L75 _public prototype_ `virtual void Clear() = 0;`
- L77 _public prototype_ `virtual bool Set(const FString& InKey, TSharedRef<FPropertyAnimatorCorePresetArchive> InValue) = 0;`
- L78 _public prototype_ `virtual bool Set(const FString& InKey, bool bInValue) = 0;`
- L79 _public prototype_ `virtual bool Set(const FString& InKey, uint64 InValue) = 0;`
- L80 _public prototype_ `virtual bool Set(const FString& InKey, int64 InValue) = 0;`
- L81 _public prototype_ `virtual bool Set(const FString& InKey, double InValue) = 0;`
- L82 _public prototype_ `virtual bool Set(const FString& InKey, const FString& InValue) = 0;`
- L84 _public prototype_ `virtual bool Get(const FString& InKey, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const = 0;`
- L85 _public prototype_ `virtual bool Get(const FString& InKey, bool& bOutValue) const = 0;`
- L86 _public prototype_ `virtual bool Get(const FString& InKey, uint64& OutValue) const = 0;`
- L87 _public prototype_ `virtual bool Get(const FString& InKey, int64& OutValue) const = 0;`
- L88 _public prototype_ `virtual bool Get(const FString& InKey, double& OutValue) const = 0;`
- L89 _public prototype_ `virtual bool Get(const FString& InKey, FString& OutValue) const = 0;`

#### struct `FPropertyAnimatorCorePresetArrayArchive`  
`struct FPropertyAnimatorCorePresetArrayArchive : FPropertyAnimatorCorePresetArchive`  
_L93-111_
- inherits: `FPropertyAnimatorCorePresetArchive`
- desc: Represents an abstract array archive for preset system, underlying implementation can vary
- L96 _public prototype_ `virtual TSharedPtr<const FPropertyAnimatorCorePresetArrayArchive> AsArray() const override;`
- L97 _public prototype_ `virtual TSharedPtr<FPropertyAnimatorCorePresetArrayArchive> AsMutableArray() override;`
- L100 _public prototype_ `virtual bool Get(int32 InIndex, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const = 0;`
- L101 _public prototype_ `virtual int32 Num() const = 0;`
- L102 _public prototype_ `virtual bool Remove(int32 InIndex) = 0;`
- L103 _public prototype_ `virtual void Clear() = 0;`
- L105 _public prototype_ `virtual bool Add(TSharedRef<FPropertyAnimatorCorePresetArchive> InValue) = 0;`
- L106 _public prototype_ `virtual bool Add(bool bInValue) = 0;`
- L107 _public prototype_ `virtual bool Add(uint64 InValue) = 0;`
- L108 _public prototype_ `virtual bool Add(int64 InValue) = 0;`
- L109 _public prototype_ `virtual bool Add(double InValue) = 0;`
- L110 _public prototype_ `virtual bool Add(const FString& InValue) = 0;`

#### struct `FPropertyAnimatorCorePresetValueArchive`  
`struct FPropertyAnimatorCorePresetValueArchive : FPropertyAnimatorCorePresetArchive`  
_L114-126_
- inherits: `FPropertyAnimatorCorePresetArchive`
- desc: Represents an abstract value (primitive) archive for preset system, underlying implementation can vary
- L117 _public prototype_ `virtual TSharedPtr<const FPropertyAnimatorCorePresetValueArchive> AsValue() const override;`
- L118 _public prototype_ `virtual TSharedPtr<FPropertyAnimatorCorePresetValueArchive> AsMutableValue() override;`
- L121 _public prototype_ `virtual bool Get(bool& bOutValue) const = 0;`
- L122 _public prototype_ `virtual bool Get(uint64& OutValue) const = 0;`
- L123 _public prototype_ `virtual bool Get(int64& OutValue) const = 0;`
- L124 _public prototype_ `virtual bool Get(double& OutValue) const = 0;`
- L125 _public prototype_ `virtual bool Get(FString& OutValue) const = 0;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Presets/PropertyAnimatorCorePresetBase.h` (Public)


#### class `UPropertyAnimatorCorePresetBase`  
`class UPropertyAnimatorCorePresetBase : public UObject`  
_L18-88_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- desc: Abstract Base class to define preset for animators with custom properties and options Will get registered automatically by the subsystem Should remain transient and stateless
- L23 _public function_ `UPropertyAnimatorCorePresetBase() : UPropertyAnimatorCorePresetBase(NAME_None)`
- L27 _public function_ `UPropertyAnimatorCorePresetBase(FName InPresetName) : PresetName(InPresetName)`
- L31 _public function_ `FName GetPresetName() const`
- L36 _public prototype_ `FText GetPresetDisplayName() const;`
- L39 _public prototype_ `virtual bool IsPresetSupported(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator) const PURE_VIRTUAL(UPropertyAnimatorCorePresetBase::IsPresetSupported, return false; );` — Checks if the preset is supported on that actor and animator
- L42 _public prototype_ `virtual bool IsPresetApplied(const UPropertyAnimatorCoreBase* InAnimator) const PURE_VIRTUAL(UPropertyAnimatorCorePresetBase::IsPresetApplied, return false; );` — Checks if the preset is applied to this animator
- L45 _public prototype_ `virtual bool ApplyPreset(UPropertyAnimatorCoreBase* InAnimator) PURE_VIRTUAL(UPropertyAnimatorCorePresetBase::ApplyPreset, return false; );` — Applies this preset on the newly created animator
- L48 _public prototype_ `virtual bool UnapplyPreset(UPropertyAnimatorCoreBase* InAnimator) PURE_VIRTUAL(UPropertyAnimatorCorePresetBase::UnapplyPreset, return false; );` — Un applies this preset on an animator
- L51 _public prototype_ `virtual void CreatePreset(FName InName, const TArray<IPropertyAnimatorCorePresetable*>& InPresetableItem);` — Called once to create this preset out of supported items
- L54 _public function_ `virtual bool LoadPreset()` — Called once before registering preset to load it, if load fails then preset is not registered
- L60 _public function_ `virtual void OnPresetRegistered()` — Called when this preset is registered by the subsystem
- L63 _public function_ `virtual void OnPresetUnregistered()` — Called when this preset is unregistered by the subsystem
- L66 _public prototype_ `virtual TSharedRef<FPropertyAnimatorCorePresetArchiveImplementation> GetArchiveImplementation() const;` — Which implementation to use for archive
- L71 _protected member_ `FName PresetName;` — `UPROPERTY(VisibleInstanceOnly, Category="Animator")` — Name used to identify this preset
- L75 _protected member_ `FText PresetDisplayName = FText::GetEmpty();` — `UPROPERTY(VisibleInstanceOnly, Category="Animator")` — Name used to display this preset to the user
- L79 _protected member_ `int32 PresetVersion = INDEX_NONE;` — `UPROPERTY(VisibleInstanceOnly, Category="Animator")` — Version of this preset for diffs
- L83 _protected member_ `FName PresetFormat;` — `UPROPERTY(VisibleInstanceOnly, Category="Animator")` — Format used for the preset content
- L87 _protected member_ `FString PresetContent;` — `UPROPERTY(VisibleInstanceOnly, Category="Animator")` — Preset stringify content

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Presets/PropertyAnimatorCorePresetable.h` (Public)


#### class `UPropertyAnimatorCorePresetable`  
`class UPropertyAnimatorCorePresetable : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPropertyAnimatorCorePresetable`  
`class IPropertyAnimatorCorePresetable`  
_L20-30_
- desc: Preset interface for animator system
- L26 _public prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) = 0;` — Import a specific preset
- L29 _public prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const = 0;` — Export a specific preset

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Presets/PropertyAnimatorCorePropertyPreset.h` (Public)


#### class `UPropertyAnimatorCorePropertyPreset`  
`class UPropertyAnimatorCorePropertyPreset : public UPropertyAnimatorCorePresetBase`  
_L17-48_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyAnimatorCorePresetBase`
- desc: Property preset class used to import/export properties on supported animators
- L23 _public prototype_ `virtual bool IsPresetSupported(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator) const override;`
- L24 _public prototype_ `virtual bool IsPresetApplied(const UPropertyAnimatorCoreBase* InAnimator) const override;`
- L25 _public prototype_ `virtual bool ApplyPreset(UPropertyAnimatorCoreBase* InAnimator) override;`
- L26 _public prototype_ `virtual bool UnapplyPreset(UPropertyAnimatorCoreBase* InAnimator) override;`
- L27 _public prototype_ `virtual void CreatePreset(FName InName, const TArray<IPropertyAnimatorCorePresetable*>& InPresetableItems) override;`
- L28 _public prototype_ `virtual bool LoadPreset() override;`
- L32 _public prototype_ `virtual void OnPresetApplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties);` — Called when this preset is applied on the animator
- L35 _public function_ `virtual void OnPresetUnapplied(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties)` — Called when this preset is unapplied on the animator
- L38 _public prototype_ `virtual void GetPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const;` — Get the preset properties for that actor
- L41 _public prototype_ `virtual void GetSupportedPresetProperties(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutProperties) const;` — Get the preset properties for that actor but only supported ones for that animator
- L44 _public prototype_ `virtual void GetAppliedPresetProperties(const UPropertyAnimatorCoreBase* InAnimator, TSet<FPropertyAnimatorCoreData>& OutSupportedProperties, TSet<FPropertyAnimatorCoreData>& OutAppliedProperties);` — Gets the supported and applied properties for an animator
- L47 _protected member_ `TMap<FString, TSharedRef<FPropertyAnimatorCorePresetArchive>> PropertyPresets;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Properties/Converters/PropertyAnimatorCoreConverterBase.h` (Public)


#### class `UPropertyAnimatorCoreConverterBase`  
`class UPropertyAnimatorCoreConverterBase : public UObject`  
_L19-41_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient)`
- inherits: `UObject`
- desc: Abstract base class, Children are used to convert from a type to another with optional rules, Should remain transient and stateless
- L25 _public function_ `virtual bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const` — Checks if this converter support the conversion
- L31 _public function_ `virtual bool Convert(const FPropertyBagPropertyDesc& InFromProperty, const FInstancedPropertyBag& InFromBag, const FPropertyBagPropertyDesc& InToProperty, FInstancedPropertyBag& InToBag, const TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase>& InRule)` — Converts from input bag to output bag with optional rules, returns true on success
- L37 _public function_ `virtual UScriptStruct* GetConversionRuleStruct() const` — Returns a struct descriptor for optional rules supported by this converter

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Properties/Converters/PropertyAnimatorCoreConverterTraits.h` (Public)


#### struct `FPropertyAnimatorCoreConverterRuleBase`  
`struct FPropertyAnimatorCoreConverterRuleBase`  
_L9-12_
- reflection: `USTRUCT()`
- desc: Base struct for converter rules

#### struct `TValueConverterTraits`  
`template<typename InFromType, typename InToType, typename InRuleType = void> struct TValueConverterTraits`  
_L16-29_
- desc: Helper to define a converter from a type to another along an optional struct for rules
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### enum `EBoolConverterComparison`  
`enum class EBoolConverterComparison : uint8`  
_L32-40_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `Equal`
- L35 _public enumerator_ `NotEqual`
- L36 _public enumerator_ `Greater`
- L37 _public enumerator_ `Less`
- L38 _public enumerator_ `GreaterEqual`
- L39 _public enumerator_ `LessEqual`

#### struct `FBoolConverterCondition`  
`struct FBoolConverterCondition`  
_L43-59_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public function_ `FBoolConverterCondition()`
- L48 _public function_ `explicit FBoolConverterCondition(EBoolConverterComparison InComparison, double InThreshold) : Comparison(InComparison) , Threshold(InThreshold)`
- L54 _public member_ `EBoolConverterComparison Comparison = EBoolConverterComparison::NotEqual;` — `UPROPERTY(EditInstanceOnly, Category="Converter")`
- L57 _public member_ `double Threshold = 0;` — `UPROPERTY(EditInstanceOnly, Category="Converter")`

#### struct `FBoolConverterRule`  
`struct FBoolConverterRule : public FPropertyAnimatorCoreConverterRuleBase`  
_L62-74_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPropertyAnimatorCoreConverterRuleBase`
- L66 _public function_ `FBoolConverterRule()`
- L73 _public member_ `TArray<FBoolConverterCondition> TrueConditions;` — `UPROPERTY(EditInstanceOnly, Category="Converter")`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<float, bool, FBoolConverterRule>`  
_L77-124_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<bool, float>`  
_L127-139_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<double, bool, FBoolConverterRule>`  
_L142-189_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<bool, double>`  
_L192-204_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<double, float>`  
_L207-219_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<float, double>`  
_L222-234_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### enum `EInt32ConverterMethod`  
`enum class EInt32ConverterMethod : uint8`  
_L237-242_
- reflection: `UENUM(BlueprintType)`
- L239 _public enumerator_ `Round`
- L240 _public enumerator_ `Floor`
- L241 _public enumerator_ `Ceil`

#### struct `FInt32ConverterRule`  
`struct FInt32ConverterRule : public FPropertyAnimatorCoreConverterRuleBase`  
_L245-251_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPropertyAnimatorCoreConverterRuleBase`
- L250 _public member_ `EInt32ConverterMethod Method = EInt32ConverterMethod::Round;` — `UPROPERTY(EditInstanceOnly, Category="Converter")`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<float, int32, FInt32ConverterRule>`  
_L254-278_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<int32, float>`  
_L281-293_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<double, int32, FInt32ConverterRule>`  
_L296-324_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<int32, double>`  
_L327-339_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<FString, FText>`  
_L342-354_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

#### struct `TValueConverterTraits`  
`template<> struct TValueConverterTraits<FText, FString>`  
_L357-369_
- L18 _public function_ `static bool Convert(const InFromType& InFrom, InToType& OutTo, const InRuleType* InRule = nullptr)`
- L25 _public function_ `static UScriptStruct* GetRuleStruct()`
- L79 _public function_ `static bool Convert(const float& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L129 _public function_ `static bool Convert(const bool& InFrom, float& OutTo, const void* InRule = nullptr)`
- L144 _public function_ `static bool Convert(const double& InFrom, bool& OutTo, const FBoolConverterRule* InRule = nullptr)`
- L194 _public function_ `static bool Convert(const bool& InFrom, double& OutTo, const void* InRule = nullptr)`
- L209 _public function_ `static bool Convert(const double& InFrom, float& OutTo, const void* InRule = nullptr)`
- L224 _public function_ `static bool Convert(const float& InFrom, double& OutTo, const void* InRule = nullptr)`
- L256 _public function_ `static bool Convert(const float& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L283 _public function_ `static bool Convert(const int32& InFrom, float& OutTo, const void* InRule = nullptr)`
- L298 _public function_ `static bool Convert(const double& InFrom, int32& OutTo, const FInt32ConverterRule* InRule)`
- L329 _public function_ `static bool Convert(const int32& InFrom, double& OutTo, const void* InRule = nullptr)`
- L344 _public function_ `static bool Convert(const FString& InFrom, FText& OutTo, const void* InRule = nullptr)`
- L359 _public function_ `static bool Convert(const FText& InFrom, FString& OutTo, const void* InRule = nullptr)`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Properties/Handlers/PropertyAnimatorCoreHandlerBase.h` (Public)


#### class `UPropertyAnimatorCoreHandlerBase`  
`class UPropertyAnimatorCoreHandlerBase : public UObject`  
_L16-84_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient)`
- inherits: `UObject`
- desc: Abstract base class, Children are used to get and set value for property type, Should remain transient and stateless
- L22 _public function_ `virtual bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData) const` — Checks whether this handlers supports the property
- L28 _public function_ `virtual bool GetValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue)` — Retrieves the value from this property within owner, value will be in the property bag
- L34 _public function_ `virtual bool SetValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue)` — Sets the value to this property within owner, value is in the property bag
- L40 _public function_ `virtual bool IsAdditiveSupported() const` — Whether Add and Subtract operations can be performed on the property value
- L46 _public function_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue)` — Adds the value to this property within owner, delta value is in the property bag
- L52 _public function_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue)` — Subtract the value to this property within owner, delta value is in the property bag
- L58 _public function_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue)` — Adds ValueA to ValueB and stores the result in OutValue
- L64 _public function_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValueA, const FInstancedPropertyBag& InValueB, FInstancedPropertyBag& OutValue)` — Subtracts ValueB from ValueA and stores the result in OutValue
- L69 _public function_ `virtual bool AddValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue)`
- L74 _public function_ `virtual bool SubtractValue(const FPropertyAnimatorCoreData& InPropertyData, const FInstancedPropertyBag& InValue, FInstancedPropertyBag& OutValue)`
- L80 _public function_ `virtual bool GetDefaultValue(const FPropertyAnimatorCoreData& InPropertyData, FInstancedPropertyBag& OutValue)` — Get the default value for this property, init to zero

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Properties/PropertyAnimatorCoreContext.h` (Public)


#### enum `EPropertyAnimatorCoreMode`  
`enum class EPropertyAnimatorCoreMode : uint8`  
_L21-27_
- reflection: `UENUM(BlueprintType)`
- desc: Mode supported for properties value
- L24 _public enumerator_ `Absolute` — Set the property value directly
- L26 _public enumerator_ `Additive` — Add value on the existing property value

#### class `UPropertyAnimatorCoreContext`  
`class UPropertyAnimatorCoreContext : public UObject, public IPropertyAnimatorCorePresetable`  
_L31-215_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IPropertyAnimatorCorePresetable`
- desc: Context for properties linked to an animator
- L39 _public prototype_ `static FName GetAnimatedPropertyName();`
- L41 _public function_ `const FPropertyAnimatorCoreData& GetAnimatedProperty() const`
- L46 _public prototype_ `UPropertyAnimatorCoreBase* GetAnimator() const;`
- L49 _public prototype_ `UPropertyAnimatorCoreHandlerBase* GetHandler() const;` — Get the handler responsible for this property type
- L52 _public prototype_ `UPropertyAnimatorCoreResolver* GetResolver() const;` — Get the active resolver for this property if any
- L54 _public prototype_ `void SetAnimated(bool bInAnimated);`
- L55 _public function_ `bool IsAnimated() const`
- L60 _public prototype_ `void SetMagnitude(float InMagnitude);`
- L61 _public function_ `float GetMagnitude() const`
- L66 _public prototype_ `void SetTimeOffset(double InOffset);`
- L67 _public function_ `double GetTimeOffset() const`
- L72 _public prototype_ `void SetMode(EPropertyAnimatorCoreMode InMode);`
- L73 _public function_ `EPropertyAnimatorCoreMode GetMode() const`
- L78 _public prototype_ `void SetConverterClass(const TSubclassOf<UPropertyAnimatorCoreConverterBase>& InConverterClass);`
- L79 _public function_ `TSubclassOf<UPropertyAnimatorCoreConverterBase> GetConverterClass() const`
- L87 _public function_ `InRuleType* GetConverterRule()`
- L93 _public prototype_ `bool ResolvePropertyOwner(AActor* InNewOwner);` — Called when the owner has changed and we want to update the animated property
- L96 _public function_ `virtual bool EvaluateProperty(const FPropertyAnimatorCoreData& InProperty, const FInstancedPropertyBag& InAnimatorResult, FInstancedPropertyBag& OutEvaluatedValues)` — Evaluates a property within this context based on animator result
- L102 _public prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L103 _public prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L108 _protected prototype_ `virtual void PostLoad() override;`
- L110 _protected prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;`
- L111 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L116 _protected prototype_ `virtual void OnAnimatedPropertyLinked();` — Called once, when the property is linked to this context
- L119 _protected function_ `virtual void OnAnimatedPropertyOwnerUpdated(UObject* InPreviousOwner, UObject* InNewOwner)` — Called when the animated property owner is updated
- L122 _private prototype_ `void ConstructInternal(const FPropertyAnimatorCoreData& InProperty);`
- L123 _private prototype_ `void SetAnimatedPropertyOwner(UObject* InNewOwner);`
- L125 _private prototype_ `void* GetConverterRulePtr(const UScriptStruct* InStruct);`
- L127 _private prototype_ `void CheckEditConditions();`
- L128 _private prototype_ `void CheckEditMagnitude();`
- L129 _private prototype_ `void CheckEditTimeOffset();`
- L130 _private prototype_ `void CheckEditMode();`
- L131 _private prototype_ `void CheckEditConverterRule();`
- L132 _private prototype_ `void CheckEditResolver();`
- L134 _private prototype_ `void OnAnimatedChanged();`
- L135 _private prototype_ `void OnModeChanged();`
- L138 _private prototype_ `void CommitEvaluationResult(const FPropertyAnimatorCoreData& InResolvedProperty, FInstancedPropertyBag& InEvaluatedValues);` — Sets the evaluation result for the resolved property
- L141 _private prototype_ `TArray<FPropertyAnimatorCoreData> ResolveProperty(bool bInForEvaluation) const;` — Use this to resolve virtual linked property
- L144 _private prototype_ `void Restore();` — Restore property based on mode
- L147 _private prototype_ `void Save();` — Allocate and save properties
- L149 _private prototype_ `bool IsResolvable() const;`
- L150 _private prototype_ `bool IsConverted() const;`
- L154 _private member_ `bool bAnimated = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetAnimated", Getter="IsAnimated", Category="Animator", meta=(AllowPrivateAccess="true"))` — Animation is enabled for this property
- L158 _private member_ `bool bEditMagnitude = true;` — `UPROPERTY(Transient)` — Edit condition for Magnitude
- L162 _private member_ `bool bEditTimeOffset = true;` — `UPROPERTY(Transient)` — Edit condition for TimeOffset
- L166 _private member_ `bool bEditMode = true;` — `UPROPERTY(Transient)` — Edit condition for modes
- L170 _private member_ `bool bEditConverterRule = false;` — `UPROPERTY(Transient)` — Edit condition for converter rule
- L174 _private member_ `bool bEditResolver = true;` — `UPROPERTY(Transient)` — Edit condition for property resolver
- L178 _private member_ `float Magnitude = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(ClampMin="0.0", ClampMax="1.0", HideEditConditionToggle, EditCondition="bEditMagnitude", EditConditionHides, AllowPrivateAccess="true"))` — Magnitude of the effect on this property
- L182 _private member_ `double TimeOffset = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(Units=Seconds, HideEditConditionToggle, EditCondition="bEditTimeOffset", EditConditionHides, AllowPrivateAccess="true"))` — Time offset to evaluate this property
- L186 _private member_ `EPropertyAnimatorCoreMode Mode = EPropertyAnimatorCoreMode::Absolute;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(HideEditConditionToggle, EditCondition="bEditMode", EditConditionHides, AllowPrivateAccess="true"))` — Current mode used for this property
- L190 _private member_ `TInstancedStruct<FPropertyAnimatorCoreConverterRuleBase> ConverterRule;` — `UPROPERTY(EditInstanceOnly, Category="Animator", NoClear, meta=(HideEditConditionToggle, EditCondition="bEditConverterRule", EditConditionHides, AllowPrivateAccess="true"))` — If a converter is used, rules may be used to convert the property
- L194 _private member_ `TObjectPtr<UPropertyAnimatorCoreResolver> Resolver;` — `UPROPERTY(VisibleInstanceOnly, NoClear, Export, Instanced, DisplayName="Range", Category="Animator", meta=(EditCondition="bEditResolver", EditConditionHides, HideEditConditionToggle, AllowPrivateAccess="true"))` — Custom resolver for the property
- L198 _private member_ `FInstancedPropertyBag OriginalPropertyValues;` — `UPROPERTY(NonTransactional)` — Store original property values for resolved properties
- L202 _private member_ `FInstancedPropertyBag DeltaPropertyValues;` — `UPROPERTY(NonTransactional)` — Store delta property values for resolved properties
- L206 _private member_ `TSubclassOf<UPropertyAnimatorCoreConverterBase> ConverterClass;` — `UPROPERTY()` — Converter class used for this property
- L210 _private member_ `TWeakObjectPtr<UPropertyAnimatorCoreHandlerBase> HandlerWeak;` — `UPROPERTY(Transient)` — Used to access property value and update it
- L214 _private member_ `FPropertyAnimatorCoreData AnimatedProperty;` — `UPROPERTY()` — Animated property linked to this options

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Properties/PropertyAnimatorCoreData.h` (Public)


#### struct `FPropertyAnimatorCoreData`  
`struct FPropertyAnimatorCoreData`  
_L23-276_
- reflection: `USTRUCT(BlueprintType)`
- desc: Serializable struct that contains the property and the owner with accessors
- L27 _public prototype_ `FPropertyAnimatorCoreData() = default;`
- L30 _public prototype_ `explicit FPropertyAnimatorCoreData(UObject* InObject, FProperty* InMemberProperty, FProperty* InProperty, TSubclassOf<UPropertyAnimatorCoreResolver> InResolverClass = nullptr);` — Takes the owner, the member property and the inner property inside
- L33 _public prototype_ `explicit FPropertyAnimatorCoreData(UObject* InObject, const TArray<FProperty*>& InChainProperties, TSubclassOf<UPropertyAnimatorCoreResolver> InResolverClass = nullptr);` — Take the owner and the full property chain, from member property to inner property
- L36 _public prototype_ `explicit FPropertyAnimatorCoreData(UObject* InObject, const TArray<FProperty*>& InChainProperties, FProperty* InProperty, TSubclassOf<UPropertyAnimatorCoreResolver> InResolverClass = nullptr);` — Take the owner, the property chain until the inner property and lastly the inner property
- L39 _public prototype_ `explicit FPropertyAnimatorCoreData(AActor* InActor, const FString& InPropertyLocatorPath);` — Takes an actor and a locator path, tries to resolve property and owner
- L42 _public prototype_ `bool IsResolvable() const;` — Is this a resolvable property that uses a custom resolver
- L45 _public prototype_ `UPropertyAnimatorCoreResolver* GetPropertyResolver() const;` — Get the linked property resolver for resolvable properties
- L48 _public prototype_ `TSubclassOf<UPropertyAnimatorCoreResolver> GetPropertyResolverClass() const;` — Get the property resolver class
- L51 _public function_ `bool IsResolved() const` — Checks if the property is resolved and can be used
- L61 _public function_ `bool operator==(const FPropertyAnimatorCoreData& InOther) const`
- L67 _public prototype_ `AActor* GetOwningActor() const;` — Returns the owning actor from this owner object
- L70 _public prototype_ `UActorComponent* GetOwningComponent() const;` — Returns the owning component from this owner object if any
- L73 _public function_ `UObject* GetOwner() const` — The owner object of the member property
- L78 _public function_ `TWeakObjectPtr<UObject> GetOwnerWeak() const`
- L84 _public prototype_ `TArray<UObject*> GetOuters(const UObject* InStopOuter) const;` — Returns chain of owner until it reaches StopOuter
- L87 _public function_ `FProperty* GetMemberProperty() const` — The member property of the owner, top property inside the owner itself
- L93 _public function_ `FProperty* GetLeafProperty() const` — The last property in the chain, could be member property if there is only one
- L99 _public prototype_ `FString GetPropertyDisplayName() const;` — The friendly display name from the member property to the inner property
- L105 _public prototype_ `FString GetPathHash() const;` — DEPRECATED, use GetLocatorPath instead The full path of a property with its owner
- L108 _public prototype_ `FString GetLocatorPath() const;` — The path to retrieve owner and property on any actor
- L111 _public prototype_ `FName GetLocatorPathHash() const;` — Hash used to store property, based on the locator path
- L114 _public prototype_ `FName GetMemberPropertyName() const;` — The member property name
- L116 _public prototype_ `FName GetMemberPropertyTypeName() const;`
- L119 _public prototype_ `FName GetLeafPropertyName() const;` — The leaf property name
- L121 _public prototype_ `FName GetLeafPropertyTypeName() const;`
- L124 _public prototype_ `TArray<FProperty*> GetChainProperties() const;` — The chain properties from member to inner property
- L127 _public prototype_ `TArray<FName> GetChainPropertyNames() const;` — The chain property names from member to inner property
- L130 _public prototype_ `bool HasSetter() const;` — Checks if the property is settable via setter
- L133 _public prototype_ `bool IsParentOf(const FPropertyAnimatorCoreData& InOtherProperty) const;` — Checks if we contain this other property directly
- L136 _public prototype_ `bool IsChildOf(const FPropertyAnimatorCoreData& InOtherProperty) const;` — Checks if we are contained inside this other property directly
- L139 _public prototype_ `bool IsOwning(const FPropertyAnimatorCoreData& InOtherProperty) const;` — Checks if we own this other nested property
- L142 _public prototype_ `bool IsTransient() const;` — Returns true if the owner or the property is transient
- L145 _public prototype_ `TOptional<FPropertyAnimatorCoreData> GetChildOf(const FPropertyAnimatorCoreData& InOtherProperty) const;` — Tries to find, based on this property, the direct child of other property
- L148 _public prototype_ `TOptional<FPropertyAnimatorCoreData> GetParent() const;` — Returns the parent of this property if there is one
- L151 _public prototype_ `TOptional<FPropertyAnimatorCoreData> GetRootParent() const;` — Returns the top most parent / member property if there is one
- L156 _public function_ `bool IsA() const`
- L167 _public prototype_ `TArray<FPropertyAnimatorCoreData> GetChildrenProperties(int32 InDepthSearch = 3) const;` — Gets the children of this property
- L172 _public function_ `bool HasA() const`
- L190 _public function_ `template <typename OutValueType> void GetPropertyValuePtr(OutValueType* OutValue) const` — Gets the value ptr for this property will use getter if available, otherwise directly access the property address
- L200 _public function_ `template <typename InValueType> void SetPropertyValuePtr(InValueType* InValue) const` — Sets the value ptr for this property, will use setter if available, otherwise directly set the property address
- L206 _public prototype_ `UPropertyAnimatorCoreHandlerBase* GetPropertyHandler() const;` — Gets the property handler to perform operation on property without knowing the type
- L209 _public prototype_ `void GeneratePropertyPath();` — Internal use only, (re)creates the property path, locator path, display name
- L212 _private prototype_ `static void CopyPropertyValue(const FProperty* InProperty, const void* InSrc, void* OutDest);`
- L214 _private prototype_ `static FName GetPropertyTypeName(const FProperty* InProperty);`
- L217 _private prototype_ `void GetPropertyValuePtrInternal(void* OutValue) const;` — Internal use only, get property value
- L220 _private prototype_ `void SetPropertyValuePtrInternal(const void* InValue) const;` — Internal use only, set property value
- L223 _private prototype_ `void SetLeafPropertyValuePtrInternal(void* InContainer, const void* InValue) const;` — Internal use only, set leaf property value
- L226 _private prototype_ `void GetLeafPropertyValuePtrInternal(const void* InContainer, void* OutValue) const;` — Internal use only, get leaf property value
- L229 _private prototype_ `void* ContainerToValuePtr(const void* InContainer, int32 InStartPropertyIndex) const;` — Uses chained properties to resolve from container to
- L232 _private prototype_ `bool FindSetterFunctions();` — Tries to find setter function for this property
- L235 _private prototype_ `void GeneratePropertyLocatorPath();` — Creates a single path that contains resolver, owner and properties for (de)serialization
- L238 _private prototype_ `void GeneratePropertyDisplayName();` — Creates the display name for the underlying property
- L242 _private member_ `TWeakObjectPtr<UObject> OwnerWeak;` — `UPROPERTY()` — Owner of the property
- L246 _private member_ `FString PropertyDisplayName;` — `UPROPERTY(Transient)` — The cached friendly display name of the property we are controlling
- L252 _private member_ `FString PathHash;` — `UPROPERTY()` — DEPRECATED, use locator path instead, Previously used to quickly compare struct of this type, replaced by LocatorPath
- L256 _private member_ `FString LocatorPath;` — `UPROPERTY()` — Property locator path to find the property and owner on any actor
- L260 _private member_ `TArray<TFieldPath<FProperty>> ChainProperties;` — `UPROPERTY()` — Chain from member property to inner property
- L264 _private member_ `TWeakObjectPtr<UFunction> SetterFunctionWeak;` — `UPROPERTY(Transient)` — Matching Setter ufunction found when no setter is specified
- L267 _private member_ `bool bSetterFunctionCached = false;` — `UPROPERTY(Transient)`
- L271 _private member_ `TSubclassOf<UPropertyAnimatorCoreResolver> PropertyResolverClass;` — `UPROPERTY()` — Used by virtual properties to resolve
- L275 _private member_ `TObjectPtr<UPropertyAnimatorCoreHandlerBase> PropertyHandler;` — `UPROPERTY(Transient)` — Used by properties to get/set value with a property bag without knowing the underlying type

#### Free symbols / members of external scopes

- L56 _function_ `friend uint32 GetTypeHash(const FPropertyAnimatorCoreData& InItem)`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Properties/PropertyAnimatorCoreResolver.h` (Public)


#### class `UPropertyAnimatorCoreResolver`  
`class UPropertyAnimatorCoreResolver : public UObject, public IPropertyAnimatorCorePresetable`  
_L17-55_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject,IPropertyAnimatorCorePresetable`
- desc: Base class to find properties hidden or not reachable, allows to discover resolvable properties for specific actors/components/objects that we cannot reach or are transient, will be resolved when needed
- L22 _public function_ `UPropertyAnimatorCoreResolver() : UPropertyAnimatorCoreResolver(NAME_None)`
- L26 _public function_ `UPropertyAnimatorCoreResolver(FName InResolverName) : ResolverName(InResolverName)`
- L31 _public function_ `virtual bool FixUpProperty(FPropertyAnimatorCoreData& InOldProperty)` — Tries to resolve old property against new one
- L37 _public function_ `virtual void GetTemplateProperties(UObject* InContext, TSet<FPropertyAnimatorCoreData>& OutProperties, const TArray<FName>* InSearchPath = nullptr)` — Get template properties based on context
- L40 _public function_ `virtual void ResolveTemplateProperties(const FPropertyAnimatorCoreData& InTemplateProperty, TArray<FPropertyAnimatorCoreData>& OutProperties, bool bInForEvaluation)` — Called when we actually need the underlying properties of a template property
- L42 _public function_ `FName GetResolverName() const`
- L48 _public prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L49 _public prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L54 _private member_ `FName ResolverName = NAME_None;` — `UPROPERTY()`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Sequencer/MovieSceneAnimatorSection.h` (Public)


#### class `UMovieSceneAnimatorSection`  
`class UMovieSceneAnimatorSection : public UMovieSceneSection`  
_L11-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Movie scene section for a sequencer animator track
- L16 _public prototype_ `UMovieSceneAnimatorSection();`
- L18 _public prototype_ `void SetEvalTimeMode(EMovieSceneAnimatorEvalTimeMode InMode);`
- L20 _public function_ `EMovieSceneAnimatorEvalTimeMode GetEvalTimeMode() const`
- L25 _public prototype_ `void SetCustomStartTime(double InTime);`
- L27 _public function_ `double GetCustomStartTime() const`
- L32 _public prototype_ `void SetCustomEndTime(double InTime);`
- L34 _public function_ `double GetCustomEndTime() const`
- L41 _protected member_ `EMovieSceneAnimatorEvalTimeMode EvalTimeMode = EMovieSceneAnimatorEvalTimeMode::Section;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Animator")`
- L44 _protected member_ `double CustomStartTime = 0.0;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Animator", meta=(EditCondition="EvalTimeMode == EMovieSceneAnimatorEvalTimeMode::Custom"))`
- L47 _protected member_ `double CustomEndTime = 1.0;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Animator", meta=(EditCondition="EvalTimeMode == EMovieSceneAnimatorEvalTimeMode::Custom"))`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Sequencer/MovieSceneAnimatorTrack.h` (Public)


#### class `UMovieSceneAnimatorTrack`  
`class UMovieSceneAnimatorTrack : public UMovieSceneNameableTrack, public IMovieSceneTrackTemplateProducer`  
_L11-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Movie scene track used to drive animator with sequencer
- L16 _public prototype_ `UMovieSceneAnimatorTrack();`
- L19 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> InSectionClass) const override;`
- L20 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L21 _public prototype_ `virtual void AddSection(UMovieSceneSection& InSection) override;`
- L22 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L23 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& InSection) const override;`
- L24 _public prototype_ `virtual bool IsEmpty() const override;`
- L25 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L26 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& InSection) override;`
- L27 _public prototype_ `virtual void RemoveSectionAt(int32 InSectionIndex) override;`
- L29 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L34 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L39 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Sequencer/MovieSceneAnimatorTypes.h` (Public)


#### enum `EMovieSceneAnimatorEvalTimeMode`  
`enum class EMovieSceneAnimatorEvalTimeMode : uint8`  
_L12-20_
- reflection: `UENUM()`
- desc: Enumerates all possible ways of interpreting time
- L15 _public enumerator_ `Sequence` — The sequence time, if the section has an offset, it won't matter
- L17 _public enumerator_ `Section` — The section time, takes into account any offset the section has
- L19 _public enumerator_ `Custom` — Custom provided time, interpolate between start and end time based on progress

#### struct `FMovieSceneAnimatorSectionData`  
`struct FMovieSceneAnimatorSectionData`  
_L22-32_
- L24 _public member_ `EMovieSceneAnimatorEvalTimeMode EvalTimeMode = EMovieSceneAnimatorEvalTimeMode::Sequence;`
- L26 _public member_ `double CustomStartTime;`
- L28 _public member_ `double CustomEndTime;`
- L31 _public member_ `const UMovieSceneAnimatorSection* Section = nullptr;` — The section object to get easing from

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/Subsystems/PropertyAnimatorCoreSubsystem.h` (Public)


#### class `UPropertyAnimatorCoreSubsystem`  
`class UPropertyAnimatorCoreSubsystem : public UEngineSubsystem`  
_L22-258_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: This subsystem handle all property animators
- L30 _public prototype_ `static UPropertyAnimatorCoreSubsystem* Get();` — Get this subsystem instance
- L33 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L34 _public prototype_ `virtual void Deinitialize() override;`
- L38 _public prototype_ `bool RegisterAnimatorClass(const UClass* InAnimatorClass);` — Register the property animator class to allow its usage
- L41 _public prototype_ `bool UnregisterAnimatorClass(const UClass* InAnimatorClass);` — Unregister the property animator class to disallow its usage
- L44 _public prototype_ `bool IsAnimatorClassRegistered(const UClass* InAnimatorClass) const;` — Checks if the property animator class is already registered
- L47 _public prototype_ `UPropertyAnimatorCoreBase* GetAnimatorRegistered(const UClass* InAnimatorClass) const;` — Gets the animator CDO registered from the class
- L50 _public prototype_ `bool IsPropertySupported(const FPropertyAnimatorCoreData& InPropertyData, bool bInCheckNestedProperties = true) const;` — Returns true if any animator is able to control that property or nested otherwise false
- L53 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetPropertyLinkedAnimators(const FPropertyAnimatorCoreData& InPropertyData) const;` — Find all animators linked to the property
- L56 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetExistingAnimators(const FPropertyAnimatorCoreData& InPropertyData) const;` — Returns a set of existing property animator objects in owner that supports that property
- L57 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetExistingAnimators(const AActor* InActor) const;`
- L60 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetAvailableAnimators(const FPropertyAnimatorCoreData* InPropertyData) const;` — Returns a set of property animator CDO that supports that property
- L61 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetAvailableAnimators() const;`
- L64 _public prototype_ `bool RegisterHandlerClass(const UClass* InHandlerClass);` — Register the property handler class to allow its usage
- L67 _public prototype_ `bool UnregisterHandlerClass(const UClass* InHandlerClass);` — Unregister the property handler class to disallow its usage
- L70 _public prototype_ `bool IsHandlerClassRegistered(const UClass* InHandlerClass) const;` — Checks if the property handler class is already registered
- L73 _public prototype_ `UPropertyAnimatorCoreHandlerBase* GetHandler(const FPropertyAnimatorCoreData& InPropertyData) const;` — Gets a property handler for this property
- L76 _public prototype_ `bool RegisterResolverClass(const UClass* InResolverClass);` — Register a resolver for custom properties
- L79 _public prototype_ `bool UnregisterResolverClass(const UClass* InResolverClass);` — Unregister a resolver
- L81 _public prototype_ `UPropertyAnimatorCoreResolver* FindResolverByName(FName InResolverName);`
- L83 _public prototype_ `UPropertyAnimatorCoreResolver* FindResolverByClass(const UClass* InResolverClass);`
- L86 _public prototype_ `bool IsResolverClassRegistered(const UClass* InResolverClass) const;` — Is this resolver registered
- L89 _public prototype_ `bool RegisterTimeSourceClass(UClass* InTimeSourceClass);` — Register a time source class to control clock for animators
- L92 _public prototype_ `bool UnregisterTimeSourceClass(UClass* InTimeSourceClass);` — Unregister a time source class
- L95 _public prototype_ `bool IsTimeSourceClassRegistered(UClass* InTimeSourceClass) const;` — Check time source class is registered
- L98 _public prototype_ `TArray<FName> GetTimeSourceNames() const;` — Get all time source names available
- L101 _public prototype_ `TArray<UPropertyAnimatorCoreTimeSourceBase*> GetTimeSources() const;` — Get all time sources available
- L104 _public prototype_ `UPropertyAnimatorCoreTimeSourceBase* GetTimeSource(FName InTimeSourceName) const;` — Get a registered time source using its name
- L107 _public prototype_ `UPropertyAnimatorCoreTimeSourceBase* CreateNewTimeSource(FName InTimeSourceName, UObject* InOwner);` — Create a new time source for an animator
- L110 _public prototype_ `bool RegisterPresetClass(const UClass* InPresetClass);` — Register a preset class
- L113 _public prototype_ `bool UnregisterPresetClass(const UClass* InPresetClass);` — Unregister a preset class
- L116 _public prototype_ `bool IsPresetClassRegistered(const UClass* InPresetClass) const;` — Is this preset class registered
- L119 _public prototype_ `TSet<UPropertyAnimatorCorePresetBase*> GetAvailablePresets(TSubclassOf<UPropertyAnimatorCorePresetBase> InPresetClass) const;` — Get all registered preset available
- L122 _public prototype_ `TSet<UPropertyAnimatorCorePresetBase*> GetSupportedPresets(const AActor* InActor, const UPropertyAnimatorCoreBase* InAnimator, TSubclassOf<UPropertyAnimatorCorePresetBase> InPresetClass) const;` — Gets all supported presets for a specific animator and actor
- L124 _public prototype_ `bool RegisterSetterResolver(FName InPropertyName, TFunction<UFunction*(const UObject*)>&& InFunction);`
- L126 _public prototype_ `bool UnregisterSetterResolver(FName InPropertyName);`
- L128 _public prototype_ `bool IsSetterResolverRegistered(FName InPropertyName) const;`
- L130 _public prototype_ `UFunction* ResolveSetter(FName InPropertyName, const UObject* InOwner);`
- L133 _public prototype_ `bool RegisterConverterClass(const UClass* InConverterClass);` — Register a converter class
- L136 _public prototype_ `bool UnregisterConverterClass(const UClass* InConverterClass);` — Unregister a converter class
- L139 _public prototype_ `bool IsConverterClassRegistered(const UClass* InConverterClass);` — Is this converter class registered
- L142 _public prototype_ `bool IsConversionSupported(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty);` — Checks if any converter supports the type conversion
- L145 _public prototype_ `TSet<UPropertyAnimatorCoreConverterBase*> GetSupportedConverters(const FPropertyBagPropertyDesc& InFromProperty, const FPropertyBagPropertyDesc& InToProperty) const;` — Finds suitable converters for a type conversion
- L148 _public prototype_ `bool RegisterPropertyAlias(const FString& InPropertyIdentifier, const FString& InAliasPropertyName);` — Registers a property alias by using a property identifier and property name, property identifier should be like Type.InnerType.PropertyName
- L151 _public prototype_ `bool UnregisterPropertyAlias(const FString& InPropertyIdentifier);` — Unregisters a property alias
- L154 _public prototype_ `FString FindPropertyAlias(const FString& InPropertyIdentifier) const;` — Finds a property alias registered or none
- L157 _public prototype_ `UPropertyAnimatorCoreBase* CreateAnimator(AActor* InActor, const UClass* InAnimatorClass, UPropertyAnimatorCorePresetBase* InPreset = nullptr, bool bInTransact = false) const;` — Create an animator of specific class for an actor
- L160 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> CreateAnimators(const TSet<AActor*>& InActors, const UClass* InAnimatorClass, UPropertyAnimatorCorePresetBase* InPreset = nullptr, bool bInTransact = false) const;` — Create animators of specific class for actors
- L163 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> CreateAnimators(const TSet<AActor*>& InActors, const UClass* InAnimatorClass, const TSet<UPropertyAnimatorCorePresetBase*>& InPresets, bool bInTransact = false) const;` — Create animators of specific class for actors with presets
- L166 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> CloneAnimators(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, AActor* InTargetActor, bool bInTransact = false) const;` — Clone animators onto an actor
- L169 _public prototype_ `bool RemoveAnimator(UPropertyAnimatorCoreBase* InAnimator, bool bInTransact = false) const;` — Removes a animator bound to an owner
- L172 _public prototype_ `bool RemoveAnimators(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, bool bInTransact = false) const;` — Removes animators from their owner
- L175 _public prototype_ `bool RemoveAnimatorComponents(const TSet<UPropertyAnimatorCoreComponent*>& InComponents, bool bInTransact = false) const;` — Removes animator components from their actor
- L178 _public prototype_ `bool ApplyAnimatorPreset(UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCorePresetBase* InPreset, bool bInTransact = false);` — Apply a preset on an existing animator
- L181 _public prototype_ `bool UnapplyAnimatorPreset(UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCorePresetBase* InPreset, bool bInTransact = false);` — Unapply a preset from an existing animator
- L184 _public prototype_ `bool LinkAnimatorProperty(UPropertyAnimatorCoreBase* InAnimator, FPropertyAnimatorCoreData& InProperty, bool bInTransact = false);` — Link a property to an existing animator
- L185 _public prototype_ `bool LinkAnimatorProperties(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties, bool bInTransact = false);`
- L188 _public prototype_ `bool UnlinkAnimatorProperty(UPropertyAnimatorCoreBase* InAnimator, FPropertyAnimatorCoreData& InProperty, bool bInTransact = false);` — Unlink a property from an existing animator
- L189 _public prototype_ `bool UnlinkAnimatorProperties(UPropertyAnimatorCoreBase* InAnimator, const TSet<FPropertyAnimatorCoreData>& InProperties, bool bInTransact = false);`
- L190 _public prototype_ `bool UnlinkAnimatorProperties(const TSet<UPropertyAnimatorCoreContext*>& InPropertyContexts, bool bInTransact = false);`
- L193 _public prototype_ `void SetAnimatorPropertiesEnabled(const TSet<UPropertyAnimatorCoreContext*>& InPropertyContexts, bool bInEnabled, bool bInTransact = false);` — Set the enabled state of animator property context
- L196 _public prototype_ `void SetActorAnimatorsEnabled(const TSet<AActor*>& InActors, bool bInEnabled, bool bInTransact = false);` — Set the enabled state of animators attached to actors, will disable state globally on the component
- L199 _public prototype_ `void SetLevelAnimatorsEnabled(const UWorld* InWorld, bool bInEnabled, bool bInTransact = false);` — Set the enabled state of animators in a world, will disable state globally on the component
- L202 _public prototype_ `void SetAnimatorsEnabled(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, bool bInEnabled, bool bInTransact = false);` — Set the enabled state of animators provided
- L206 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAnimatorsSetEnabled, const UWorld* , bool , bool ) static FOnAnimatorsSetEnabled OnAnimatorsSetEnabledDelegate;` — Delegate to change state of animators in a world
- L218 _protected prototype_ `void RegisterAnimatorClasses();` — Scan for children of each of the following classes and registers their CDO: 1. UPropertyAnimatorCoreBase 2. UPropertyAnimatorCoreHandlerBase 3. UPropertyAnimatorCoreResolver 4. UPropertyAnimatorCoreTimeSourceBase 5. UPropertyAnimatorCorePresetBase 6. UPropertyAnimatorCoreConverterBase
- L220 _protected prototype_ `void OnAssetRegistryFilesLoaded();`
- L221 _protected prototype_ `void OnAssetRegistryAssetAdded(const FAssetData& InAssetData);`
- L222 _protected prototype_ `void OnAssetRegistryAssetRemoved(const FAssetData& InAssetData);`
- L223 _protected prototype_ `void OnAssetRegistryAssetUpdated(const FAssetData& InAssetData);`
- L224 _protected prototype_ `void RegisterPresetAsset(const FAssetData& InAssetData);`
- L225 _protected prototype_ `void UnregisterPresetAsset(const FAssetData& InAssetData);`
- L229 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCoreTimeSourceBase>> TimeSourcesWeak;` — `UPROPERTY()` — Time sources available to use with animators
- L233 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCoreBase>> AnimatorsWeak;` — `UPROPERTY()` — Animators available to link properties to
- L237 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCoreHandlerBase>> HandlersWeak;` — `UPROPERTY()` — Handlers are used to set/get same type properties and reuse logic
- L241 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCoreResolver>> ResolversWeak;` — `UPROPERTY()` — Resolvers find properties to let user control them when they are unreachable/hidden
- L245 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCorePresetBase>> PresetsWeak;` — `UPROPERTY()` — Presets available to apply on animator
- L249 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCoreConverterBase>> ConvertersWeak;` — `UPROPERTY()` — Converters available to transform a type to another type
- L252 _protected member_ `TMap<FName, TFunction<UFunction*(const UObject*)>> SetterResolvers;` — Some property and their setter cannot be identified automatically, use manual setter resolvers
- L255 _protected member_ `TMap<FString, FString> PropertyAliases;` — Some property should have a friendlier name and replace the original name by an alias
- L257 _protected member_ `bool bFilesLoaded = false;`

#### Free symbols / members of external scopes

- L206 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAnimatorsSetEnabled, const UWorld* , bool , bool ) static FOnAnimatorsSetEnabled OnAnimatorsSetEnabledDelegate;` — Delegate to change state of animators in a world

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/TimeSources/PropertyAnimatorCoreManualTimeSource.h` (Public)


#### enum `EPropertyAnimatorCoreManualStatus`  
`enum class EPropertyAnimatorCoreManualStatus : uint8`  
_L9-19_
- reflection: `UENUM()`
- L12 _public enumerator_ `Stopped` — Animation is done
- L14 _public enumerator_ `Paused` — Animation is paused
- L16 _public enumerator_ `PlayingForward` — Animation is playing
- L18 _public enumerator_ `PlayingBackward` — Animation is playing in reverse

#### class `UPropertyAnimatorCoreManualTimeSource`  
`class UPropertyAnimatorCoreManualTimeSource : public UPropertyAnimatorCoreTimeSourceBase`  
_L22-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyAnimatorCoreTimeSourceBase`
- L27 _public prototype_ `static FName GetCustomTimePropertyName();`
- L29 _public function_ `UPropertyAnimatorCoreManualTimeSource() : UPropertyAnimatorCoreTimeSourceBase(TEXT("Manual"))`
- L33 _public prototype_ `void SetCustomTime(double InTime);`
- L34 _public function_ `double GetCustomTime() const`
- L39 _public prototype_ `void SetPlaybackState(EPropertyAnimatorCoreManualStatus InState);`
- L40 _public function_ `EPropertyAnimatorCoreManualStatus GetPlaybackState() const`
- L45 _public prototype_ `void Play(bool bInForward);`
- L46 _public prototype_ `void Pause();`
- L47 _public prototype_ `void Stop();`
- L49 _public prototype_ `EPropertyAnimatorCoreManualStatus GetPlaybackStatus() const;`
- L50 _public prototype_ `bool IsPlaying() const;`
- L55 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L60 _protected prototype_ `virtual bool UpdateEvaluationData(FPropertyAnimatorCoreTimeSourceEvaluationData& OutData) override;`
- L61 _protected prototype_ `virtual void OnTimeSourceActive() override;`
- L62 _protected prototype_ `virtual void OnTimeSourceInactive() override;`
- L63 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L64 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L67 _protected prototype_ `void OnStateChanged();`
- L71 _protected member_ `double CustomTime = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — Time to evaluate
- L81 _protected member_ `EPropertyAnimatorCoreManualStatus PlaybackState = EPropertyAnimatorCoreManualStatus::Paused;` — `UPROPERTY(EditInstanceOnly, Transient, DuplicateTransient, NoClear, Setter, Getter, Category="Animator")` — Playback state Stopped = 0 Paused = 1 PlayingForward = 2 PlayingReverse = 3
- L84 _protected member_ `EPropertyAnimatorCoreManualStatus ActiveStatus = EPropertyAnimatorCoreManualStatus::Paused;` — Current active status for the player

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/TimeSources/PropertyAnimatorCoreSequencerTimeSource.h` (Public)


#### struct `FPropertyAnimatorCoreSequencerTimeSourceEvalResult`  
`struct FPropertyAnimatorCoreSequencerTimeSourceEvalResult`  
_L9-22_
- reflection: `USTRUCT()`
- L14 _public member_ `bool bEvalValid = false;` — Is the evaluation state valid
- L18 _public member_ `double EvalTime = 0.0;` — `UPROPERTY(VisibleInstanceOnly, Transient, Category="Animator", meta=(Units=Seconds))` — Last evaluated time received
- L21 _public member_ `float EvalMagnitude = 1.f;` — Last evaluated magnitude received

#### class `UPropertyAnimatorCoreSequencerTimeSource`  
`class UPropertyAnimatorCoreSequencerTimeSource : public UPropertyAnimatorCoreTimeSourceBase`  
_L26-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyAnimatorCoreTimeSourceBase`
- desc: Time source that sync with a sequencer animator track
- L31 _public function_ `UPropertyAnimatorCoreSequencerTimeSource() : UPropertyAnimatorCoreTimeSourceBase(TEXT("Sequencer"))`
- L36 _public prototype_ `virtual bool UpdateEvaluationData(FPropertyAnimatorCoreTimeSourceEvaluationData& OutData) override;`
- L39 _public prototype_ `void OnSequencerTimeEvaluated(const TOptional<double>& InTimeEval, const TOptional<float>& InMagnitudeEval);`
- L43 _protected member_ `FPropertyAnimatorCoreSequencerTimeSourceEvalResult EvalResult;` — `UPROPERTY(EditInstanceOnly, DisplayName="EvalTime", Category="Animator")`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/TimeSources/PropertyAnimatorCoreSystemTimeSource.h` (Public)


#### enum `EPropertyAnimatorCoreSystemMode`  
`enum class EPropertyAnimatorCoreSystemMode : uint8`  
_L12-20_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates all possible modes for the machine clock time source
- L15 _public enumerator_ `LocalTime` — Local time of the machine
- L17 _public enumerator_ `Countdown` — Specified duration elapsing until it reaches 0
- L19 _public enumerator_ `Stopwatch` — Current time elapsed since the time source is active

#### enum `EPropertyAnimatorCoreSystemCountdownFormat`  
`enum class EPropertyAnimatorCoreSystemCountdownFormat : uint8`  
_L24-38_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates all possible format interpretation in countdown mode
- L31 _public enumerator_ `Duration` — Default: format time provided is the duration of the countdown (relative) eg: if current time is 10:00:00 and format is set to 12:00:00, then countdown duration will be 12 hours until it reaches 0
- L37 _public enumerator_ `Target` — Format time provided is the target time (absolute) eg: if current time is 10:00.00 and format is set to 12:00:00, then countdown is 02:00:00 since 2 hours remains before reaching target time

#### class `UPropertyAnimatorCoreSystemTimeSource`  
`class UPropertyAnimatorCoreSystemTimeSource : public UPropertyAnimatorCoreTimeSourceBase`  
_L42-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyAnimatorCoreTimeSourceBase`
- desc: System time source that support various option
- L47 _public function_ `UPropertyAnimatorCoreSystemTimeSource() : UPropertyAnimatorCoreTimeSourceBase(TEXT("System"))`
- L51 _public prototype_ `void SetMode(EPropertyAnimatorCoreSystemMode InMode);`
- L52 _public function_ `EPropertyAnimatorCoreSystemMode GetMode() const`
- L57 _public prototype_ `void SetUseUtc(bool bInUseUtc);`
- L58 _public function_ `bool GetUseUtc() const`
- L63 _public prototype_ `void SetCountdownFormat(EPropertyAnimatorCoreSystemCountdownFormat InFormat);`
- L64 _public function_ `EPropertyAnimatorCoreSystemCountdownFormat GetCountdownFormat() const`
- L69 _public prototype_ `void SetCountdownDuration(const FTimespan& InTimeSpan);`
- L70 _public function_ `void GetCountdownDuration(FTimespan& OutTimeSpan) const`
- L75 _public prototype_ `void SetCountdownDuration(const FString& InDuration);`
- L76 _public function_ `const FString& GetCountdownDuration() const`
- L82 _protected prototype_ `static FTimespan ParseTime(const FString& InFormat);`
- L86 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L91 _protected prototype_ `virtual bool UpdateEvaluationData(FPropertyAnimatorCoreTimeSourceEvaluationData& OutData) override;`
- L92 _protected prototype_ `virtual void OnTimeSourceActive() override;`
- L93 _protected prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L94 _protected prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L97 _protected prototype_ `void OnModeChanged();`
- L98 _protected prototype_ `void SetActivationTime();`
- L102 _protected member_ `EPropertyAnimatorCoreSystemMode Mode = EPropertyAnimatorCoreSystemMode::LocalTime;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator")` — Machine time mode to use
- L106 _protected member_ `bool bUseUtc = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetUseUtc", Getter="GetUseUtc", Category="Animator")` — Use universal time for calculations = greenwich mean time
- L110 _protected member_ `EPropertyAnimatorCoreSystemCountdownFormat CountdownFormat = EPropertyAnimatorCoreSystemCountdownFormat::Duration;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(EditCondition="Mode == EPropertyAnimatorCoreSystemMode::Countdown", EditConditionHides))` — Format interpretation for the countdown
- L122 _protected member_ `FString CountdownDuration = TEXT("23:` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Countdown Time", Category="Animator", meta=(EditCondition="Mode == EPropertyAnimatorCoreSystemMode::Countdown", EditConditionHides))` — Countdown time format (duration or target) : 120 = 2 minutes 02:00 = 2 minutes 00:02:00 = 2 minutes 2m = 2 minutes 1h = 1 hour 120s = 2 minutes
- L126 _private member_ `FTimespan CountdownTimeSpan;` — `UPROPERTY(Transient)`
- L129 _private member_ `FDateTime ActivationTime;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/TimeSources/PropertyAnimatorCoreTimeSourceBase.h` (Public)


#### enum `EPropertyAnimatorCoreTimeSourceResult`  
`enum class EPropertyAnimatorCoreTimeSourceResult`  
_L11-19_
- desc: Enumerates all possible outcomes for the time source
- L14 _public enumerator_ `Skip` — Time is the same as previous, evaluation can be skipped
- L16 _public enumerator_ `Idle` — Time is in an invalid state or out of range
- L18 _public enumerator_ `Evaluate` — Time is valid and in range, evaluate time

#### struct `FPropertyAnimatorCoreTimeSourceEvaluationData`  
`struct FPropertyAnimatorCoreTimeSourceEvaluationData`  
_L22-29_
- desc: Stores all the data used by animators during evaluation
- L25 _public member_ `double TimeElapsed = 0.0;` — Time elapsed for animators evaluation
- L28 _public member_ `float Magnitude = 1.f;` — Time magnitude for animators to fade in/out effect based on time

#### class `UPropertyAnimatorCoreTimeSourceBase`  
`class UPropertyAnimatorCoreTimeSourceBase : public UObject, public IPropertyAnimatorCorePresetable`  
_L36-124_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject,IPropertyAnimatorCorePresetable`
- desc: Abstract base class for time source used by property animators Can be transient or saved to disk if contains user set data
- L43 _public function_ `UPropertyAnimatorCoreTimeSourceBase() : UPropertyAnimatorCoreTimeSourceBase(NAME_None)`
- L47 _public function_ `UPropertyAnimatorCoreTimeSourceBase(const FName& InSourceName) : TimeSourceName(InSourceName)`
- L51 _public prototype_ `void ActivateTimeSource();`
- L52 _public prototype_ `void DeactivateTimeSource();`
- L54 _public function_ `bool IsTimeSourceActive() const`
- L59 _public prototype_ `EPropertyAnimatorCoreTimeSourceResult FetchEvaluationData(FPropertyAnimatorCoreTimeSourceEvaluationData& OutEvaluationData);`
- L61 _public function_ `FName GetTimeSourceName() const`
- L66 _public prototype_ `void SetFrameRate(float InFrameRate);`
- L67 _public function_ `float GetFrameRate() const`
- L72 _public prototype_ `void SetUseFrameRate(bool bInUseFrameRate);`
- L73 _public function_ `bool GetUseFrameRate() const`
- L78 _public function_ `double GetLastTimeElapsed() const`
- L84 _public prototype_ `virtual bool ImportPreset(const UPropertyAnimatorCorePresetBase* InPreset, const TSharedRef<FPropertyAnimatorCorePresetArchive>& InValue) override;`
- L85 _public prototype_ `virtual bool ExportPreset(const UPropertyAnimatorCorePresetBase* InPreset, TSharedPtr<FPropertyAnimatorCorePresetArchive>& OutValue) const override;`
- L90 _protected prototype_ `virtual bool UpdateEvaluationData(FPropertyAnimatorCoreTimeSourceEvaluationData& OutData);` — Retrieve evaluation data to provide animators, return true if data is valid, false otherwise
- L93 _protected function_ `virtual void OnTimeSourceRegistered()` — Time source CDO is registered by subsystem
- L96 _protected function_ `virtual void OnTimeSourceUnregistered()` — Time source CDO is unregistered by subsystem
- L99 _protected function_ `virtual void OnTimeSourceActive()` — Time source is active on the animator
- L102 _protected function_ `virtual void OnTimeSourceInactive()` — Time source is inactive on the animator
- L105 _private prototype_ `bool IsFramerateAllowed(double InNewTime) const;`
- L109 _private member_ `bool bUseFrameRate = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetUseFrameRate", Getter="GetUseFrameRate", Category="Animator", meta=(InlineEditConditionToggle))` — Use a specific framerate
- L113 _private member_ `float FrameRate = 30.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Animator", meta=(ClampMin="0", EditCondition="bUseFrameRate"))` — The frame rate to target for the animator effect
- L117 _private member_ `FName TimeSourceName;` — `UPROPERTY(Transient)` — Name used to display this time source to the user
- L120 _private member_ `double LastTimeElapsed = 0;` — Cached time elapsed
- L123 _private member_ `bool bTimeSourceActive = false;` — Is this time source active on the animator

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Public/TimeSources/PropertyAnimatorCoreWorldTimeSource.h` (Public)


#### class `UPropertyAnimatorCoreWorldTimeSource`  
`class UPropertyAnimatorCoreWorldTimeSource : public UPropertyAnimatorCoreTimeSourceBase`  
_L13-25_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPropertyAnimatorCoreTimeSourceBase`
- desc: Time source that follows world time, Transient because it does not contain user saved data, can be recreated
- L18 _public function_ `UPropertyAnimatorCoreWorldTimeSource() : UPropertyAnimatorCoreTimeSourceBase(TEXT("World"))`
- L23 _public prototype_ `virtual bool UpdateEvaluationData(FPropertyAnimatorCoreTimeSourceEvaluationData& OutData) override;`
