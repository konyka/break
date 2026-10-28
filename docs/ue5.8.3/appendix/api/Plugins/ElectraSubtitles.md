# Plugins / ElectraSubtitles

- module root: `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles`
- headers: 14; symbols: 395
- symbol kinds: class=26, delegate=2, enum=4, enumerator=17, function=59, member=114, namespace=15, prototype=130, struct=18, typedef=10
- PrivateDependencyModuleNames: Core, ElectraBase, Expat

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ElectraSubtitleDecoder.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ElectraSubtitleDecoderFactory.h` (Private)


#### class `IElectraSubtitleDecoderFactory`  
`class IElectraSubtitleDecoderFactory`  
_L9-14_
- L12 _public prototype_ `virtual ~IElectraSubtitleDecoderFactory() = default;`
- L13 _public prototype_ `virtual TSharedPtr<IElectraSubtitleDecoder, ESPMode::ThreadSafe> CreateDecoder(const FString& SubtitleCodecName) = 0;`

#### class `IElectraSubtitleDecoderFactoryRegistry`  
`class IElectraSubtitleDecoderFactoryRegistry`  
_L17-30_
- L20 _public prototype_ `virtual ~IElectraSubtitleDecoderFactoryRegistry() = default;`
- L28 _public prototype_ `virtual void AddDecoderFactory(const TArray<FCodecInfo>& InCodecInformation, IElectraSubtitleDecoderFactory* InDecoderFactory) = 0;`

#### struct `IElectraSubtitleDecoderFactoryRegistry::FCodecInfo`  
`struct FCodecInfo`  
_L22-26_
- L24 _public member_ `FString CodecName;`
- L25 _public member_ `int32 Priority = 0;`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ElectraSubtitleModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraSubtitles, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraSubtitles, Log, All);`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ElectraSubtitleUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ElectraSubtitleUtils`
- L10 _function_ `inline bool StringEquals(const TCHAR * const s1, const TCHAR * const s2)` (scope `ElectraSubtitleUtils`)
- L15 _function_ `inline bool StringStartsWith(const TCHAR * const s1, const TCHAR * const s2, SIZE_T n)` (scope `ElectraSubtitleUtils`)
- L23 _function_ `static inline uint8 GetFromBigEndian(uint8 value)` (scope `ElectraSubtitleUtils`)
- L24 _function_ `static inline int8 GetFromBigEndian(int8 value)` (scope `ElectraSubtitleUtils`)
- L25 _function_ `static inline uint16 GetFromBigEndian(uint16 value)` (scope `ElectraSubtitleUtils`)
- L26 _function_ `static inline int16 GetFromBigEndian(int16 value)` (scope `ElectraSubtitleUtils`)
- L27 _function_ `static inline int32 GetFromBigEndian(int32 value)` (scope `ElectraSubtitleUtils`)
- L28 _function_ `static inline uint32 GetFromBigEndian(uint32 value)` (scope `ElectraSubtitleUtils`)
- L29 _function_ `static inline int64 GetFromBigEndian(int64 value)` (scope `ElectraSubtitleUtils`)
- L30 _function_ `static inline uint64 GetFromBigEndian(uint64 value)` (scope `ElectraSubtitleUtils`)
- L32 _function_ `static inline uint16 EndianSwap(uint16 value)` (scope `ElectraSubtitleUtils`)
- L33 _function_ `static inline int16 EndianSwap(int16 value)` (scope `ElectraSubtitleUtils`)
- L34 _function_ `static inline uint32 EndianSwap(uint32 value)` (scope `ElectraSubtitleUtils`)
- L35 _function_ `static inline int32 EndianSwap(int32 value)` (scope `ElectraSubtitleUtils`)
- L36 _function_ `static inline uint64 EndianSwap(uint64 value)` (scope `ElectraSubtitleUtils`)
- L37 _function_ `static inline int64 EndianSwap(int64 value)` (scope `ElectraSubtitleUtils`)
- L49 _function_ `template <typename T> static inline T ValueFromBigEndian(const T value)` (scope `ElectraSubtitleUtils`)

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ttml/ElectraSubtitleDecoder_TTML.h` (Private)


#### class `FElectraSubtitleDecoderTTML`  
`class FElectraSubtitleDecoderTTML : public IElectraSubtitleDecoder`  
_L16-80_
- inherits: `IElectraSubtitleDecoder`
- desc: TTML / IMSC1 subtitle decoder (https://www.w3.org/TR/ttml2/ and https://www.w3.org/TR/ttml-imsc1.2/) This is for the IMSC1 text profile only. Images are not supported.
- L19 _public prototype_ `static void RegisterCodecs(IElectraSubtitleDecoderFactoryRegistry& InRegistry);`
- L21 _public prototype_ `FElectraSubtitleDecoderTTML(const FString& CodecOrMimetype);`
- L23 _public prototype_ `virtual ~FElectraSubtitleDecoderTTML();`
- L28 _public prototype_ `virtual bool InitializeStreamWithCSD(const TArray<uint8>& InCSD, const Electra::FParamDict& InAdditionalInfo) override;` — Methods from IElectraSubtitleDecoder
- L29 _public prototype_ `virtual IElectraSubtitleDecoder::FOnSubtitleReceivedDelegate& GetParsedSubtitleReceiveDelegate() override;`
- L30 _public prototype_ `virtual Electra::FTimeValue GetStreamedDeliveryTimeOffset() override;`
- L31 _public prototype_ `virtual void AddStreamedSubtitleData(const TArray<uint8>& InData, Electra::FTimeValue InAbsoluteTimestamp, Electra::FTimeValue InDuration, const Electra::FParamDict& InAdditionalInfo) override;`
- L32 _public prototype_ `virtual void SignalStreamedSubtitleEOD() override;`
- L33 _public prototype_ `virtual void Flush() override;`
- L34 _public prototype_ `virtual void Start() override;`
- L35 _public prototype_ `virtual void Stop() override;`
- L36 _public prototype_ `virtual void UpdatePlaybackPosition(Electra::FTimeValue InAbsolutePosition, Electra::FTimeValue InLocalPosition) override;`
- L59 _private prototype_ `void ClearLastError();`
- L62 _private member_ `Electra::FTimeValue DurationOfEmptySubtitle;`
- L63 _private member_ `Electra::FTimeValue DurationWindow;`
- L64 _private member_ `bool bSendEmptySubtitleDuringGaps = false;`
- L66 _private member_ `FOnSubtitleReceivedDelegate ParsedSubtitleDelegate;`
- L67 _private member_ `EDocumentType DocumentType = EDocumentType::Undefined;`
- L68 _private member_ `FString LastErrorMsg;`
- L70 _private member_ `FCriticalSection AccessLock;`
- L71 _private member_ `TArray<FTimelineHandlers> TimelineHandlers;`
- L72 _private member_ `FSideloadedSubtitleHandler SideloadedHandler;`
- L73 _private member_ `Electra::FTimeValue LastPlaybackUpdateAbsPos;`
- L75 _private member_ `int32 Width = 0;`
- L76 _private member_ `int32 Height = 0;`
- L77 _private member_ `int32 TranslationX = 0;`
- L78 _private member_ `int32 TranslationY = 0;`
- L79 _private member_ `uint32 Timescale = 0;`

#### enum `FElectraSubtitleDecoderTTML::EDocumentType`  
`enum class EDocumentType`  
_L39-44_
- L41 _public enumerator_ `Undefined`
- L42 _public enumerator_ `STPP` — ISO/IEC 14496-30
- L43 _public enumerator_ `TTMLXML` — sideloaded XML document

#### struct `FElectraSubtitleDecoderTTML::FSideloadedSubtitleHandler`  
`struct FSideloadedSubtitleHandler`  
_L46-50_
- L48 _public member_ `FString ContentID;`
- L49 _public member_ `TSharedPtr<ElectraTTMLParser::ITTMLSubtitleHandler, ESPMode::ThreadSafe> Handler;`

#### struct `FElectraSubtitleDecoderTTML::FTimelineHandlers`  
`struct FTimelineHandlers`  
_L52-57_
- L54 _public member_ `TSharedPtr<ElectraTTMLParser::ITTMLSubtitleHandler, ESPMode::ThreadSafe> Handler;`
- L55 _public member_ `Electra::FTimeRange AbsoluteTimeRange;`
- L56 _public member_ `Electra::FTimeValue MediaLocalPTO;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ElectraTTMLParser`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ttml/TTMLParser.h` (Private)


#### class `ElectraTTMLParser::ITTMLParser`  
`class ITTMLParser`  
_L14-57_
- L17 _public prototype_ `static TSharedPtr<ITTMLParser, ESPMode::ThreadSafe> Create();`
- L19 _public prototype_ `virtual ~ITTMLParser() = default;`
- L24 _public prototype_ `virtual const FString& GetLastErrorMessage() const = 0;` — Returns the most recent error message.
- L31 _public prototype_ `virtual bool ParseXMLDocument(const TArray<uint8>& InXMLDocumentData, const Electra::FParamDict& InOptions) = 0;` — Parses the provided XML as a TTML document. @return true if successful, false if not. Get error message from GetLastErrorMessage().
- L48 _public prototype_ `virtual bool BuildSubtitleList(const Electra::FTimeValue& InDocumentStartTime, const Electra::FTimeValue& InDocumentDuration, const Electra::FParamDict& InOptions) = 0;` — Creates an internal list of subtitles sorted by time. Call this after a successful parse of the document. NOTE: This call will modify the parsed document in-place. This can be called only once. @param InDocumentStartTime The base start time to offset internal timestamps with @param InDocumentDuration The duration this document is valid for. Subtitles falling outside the document range will not be used. @param InOptions Additional options: "sendEmptySubtitleDuringGaps"(bool) : Set to true to have an empty subtitle being sent in between actual subtitles Useful to remove subtitles from the screen without considering start times and display durations. @return true if successful, false otherwise.
- L56 _public prototype_ `virtual TSharedPtr<ITTMLSubtitleHandler, ESPMode::ThreadSafe> GetSubtitleHandler() = 0;` — Get the handler for the list of subtitles after a successful call to BuildSubtitleList(). With this handler retrieved and kept it is ok to destroy this parser. @return Handler to the list of parsed subtitles within the active document time range.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L8 _namespace_ `namespace Electra`
- L10 _namespace_ `namespace ElectraTTMLParser`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ttml/TTMLSubtitleHandler.h` (Private)


#### class `ElectraTTMLParser::ITTMLSubtitleHandler`  
`class ITTMLSubtitleHandler`  
_L13-34_
- L16 _public prototype_ `virtual ~ITTMLSubtitleHandler() = default;`
- L27 _public prototype_ `virtual void ClearActiveRange() = 0;` — Resets the current active range on a time discontinuity (eg. seeking).
- L30 _public prototype_ `virtual bool UpdateActiveRange(const Electra::FTimeRange& InRange) = 0;` — Updates the active subtitle range. Returns true if changed, false if not changed.
- L33 _public prototype_ `virtual void GetActiveSubtitles(TArray<FActiveSubtitle>& OutSubtitles) const = 0;` — Returns the active subtitle.

#### struct `ElectraTTMLParser::ITTMLSubtitleHandler::FActiveSubtitle`  
`struct FActiveSubtitle`  
_L18-23_
- L20 _public member_ `FString Text;`
- L21 _public member_ `Electra::FTimeRange TimeRange;`
- L22 _public member_ `bool bIsEmptyGap = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ElectraTTMLParser`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ttml/TTMLSubtitleList.h` (Private)


#### class `ElectraTTMLParser::ITTMLSubtitleList`  
`class ITTMLSubtitleList : public ITTMLSubtitleHandler`  
_L15-24_
- inherits: `ITTMLSubtitleHandler`
- L18 _public prototype_ `static TSharedPtr<ITTMLSubtitleList, ESPMode::ThreadSafe> Create();`
- L20 _public prototype_ `virtual ~ITTMLSubtitleList() = default;`
- L21 _public prototype_ `virtual const FString& GetLastErrorMessage() const = 0;`
- L23 _public prototype_ `virtual bool CreateFrom(TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe> InTTMLTT, const Electra::FTimeValue& InDocumentStartTime, const Electra::FTimeValue& InDocumentDuration, const Electra::FParamDict& InOptions) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace Electra`
- L11 _namespace_ `namespace ElectraTTMLParser`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/ttml/TTMLXMLElements.h` (Private)


#### struct `ElectraTTMLParser::FXmlAttribute`  
`struct FXmlAttribute`  
_L14-37_
- L16 _public function_ `const FString& GetName() const`
- L17 _public function_ `const FString& GetValue() const`
- L18 _public function_ `const FString& GetNamespace() const`
- L20 _public function_ `FString GetFullName() const`
- L29 _public function_ `FString GetValueNoWS() const`
- L34 _public member_ `FString Name;`
- L35 _public member_ `FString Value;`
- L36 _public member_ `FString Namespace;`

#### class `ElectraTTMLParser::FTTMLTimeContainer`  
`class FTTMLTimeContainer`  
_L40-81_
- L50 _public function_ `ETimeType GetTimeType() const`
- L53 _public function_ `Electra::FTimeRange GetRange() const`
- L56 _public function_ `Electra::FTimeValue GetBegin() const`
- L58 _public function_ `void SetBegin(const Electra::FTimeValue& InBegin)`
- L61 _public function_ `Electra::FTimeValue GetEnd() const`
- L63 _public function_ `void SetEnd(const Electra::FTimeValue& InEnd)`
- L66 _public function_ `Electra::FTimeValue GetDuration() const`
- L68 _public function_ `void SetDuration(const Electra::FTimeValue& InDuration)`
- L71 _public prototype_ `bool ProcessTimeAttributes(TArray<FXmlAttribute>& OutAttributes, ITTMLXMLElement* Element, FTTMLParser* Parser, const TArray<FXmlAttribute>& InAttributes);`
- L73 _public prototype_ `void RecalculateTimesFromParent(FTTMLTimeContainer* InParent);`
- L76 _private prototype_ `bool SetTimeContainerType(FTTMLParser* Parser, const FString& InTimeContainerType);`
- L78 _private member_ `ETimeType TimeType = ETimeType::Par;`
- L79 _private member_ `Electra::FTimeRange Range;`
- L80 _private member_ `Electra::FTimeValue Duration;`

#### enum `ElectraTTMLParser::FTTMLTimeContainer::ETimeType`  
`enum class ETimeType`  
_L43-47_
- L45 _public enumerator_ `Par`
- L46 _public enumerator_ `Seq`

#### class `ElectraTTMLParser::ITTMLXMLElement`  
`class ITTMLXMLElement : public TSharedFromThis<ITTMLXMLElement, ESPMode::ThreadSafe>`  
_L87-142_
- inherits: `TSharedFromThis<ITTMLXMLElement,ESPMode::ThreadSafe>`
- L103 _public function_ `ITTMLXMLElement(const FString& InName, EType InType) : Name(InName), Type(InType)`
- L106 _public prototype_ `virtual ~ITTMLXMLElement() = default;`
- L108 _public prototype_ `virtual EType GetType() const;`
- L109 _public prototype_ `void SetParentElement(const TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe>& InParentElement);`
- L110 _public prototype_ `bool PushAndProcessNewElement(FTTMLParser* Parser, const TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe>& Element, const TArray<FXmlAttribute>& Attributes, int32 InLineNumber);`
- L111 _public prototype_ `bool SetError(FTTMLParser* Parser, FString ErrorMsg);`
- L112 _public prototype_ `const FString& GetName() const;`
- L113 _public prototype_ `void SetData(const FString& InData);`
- L114 _public prototype_ `void AppendData(const FString& InData);`
- L115 _public prototype_ `const FString& GetData() const;`
- L116 _public prototype_ `void SetLineNumber(int32 InLineNumber);`
- L117 _public prototype_ `int32 GetLineNumber() const;`
- L118 _public function_ `TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe> GetParentElement() const`
- L120 _public function_ `virtual bool GetPreserveSpace() const`
- L122 _public function_ `virtual void SetPreserveSpace(bool bInPreserveSpace)`
- L125 _public prototype_ `virtual bool ProcessElement(FTTMLParser* Parser, const FString& ElementName, const TArray<FXmlAttribute>& Attributes, int32 LineNumber);`
- L126 _public prototype_ `virtual bool ProcessAttributes(FTTMLParser* Parser, const TArray<FXmlAttribute>& Attributes);`
- L127 _public prototype_ `virtual bool ProcessClose(FTTMLParser* Parser, const FString& ElementName);`
- L129 _public function_ `virtual FTTMLTimeContainer* GetTimeContainer()`
- L131 _public prototype_ `virtual void RecalculateTimes(bool bRecursively);`
- L134 _protected member_ `TWeakPtr<ITTMLXMLElement, ESPMode::ThreadSafe> ParentElement;` — Weak pointer to the parent element.
- L135 _protected member_ `FString Name;` — Element name
- L136 _protected member_ `FString Data;` — Element data string
- L137 _protected member_ `TArray<FXmlAttribute> OtherAttributes;` — An array containing attributes not explicitly parsed into element members.
- L138 _protected member_ `TArray<TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe>> OtherChildren;` — An array of children that were not explicitly parsed.
- L139 _protected member_ `EType Type;` — Element type
- L140 _protected member_ `int32 LineNumber = 0;`
- L141 _protected member_ `bool bPreserveSpace = false;`

#### enum `ElectraTTMLParser::ITTMLXMLElement::EType`  
`enum class EType`  
_L90-101_
- L92 _public enumerator_ `Other`
- L93 _public enumerator_ `TT`
- L94 _public enumerator_ `Head`
- L95 _public enumerator_ `Body`
- L96 _public enumerator_ `Div`
- L97 _public enumerator_ `P`
- L98 _public enumerator_ `Span`
- L99 _public enumerator_ `AnonymousSpan`
- L100 _public enumerator_ `Br`

#### class `ElectraTTMLParser::FTTMLXML_OtherElement`  
`class FTTMLXML_OtherElement : public ITTMLXMLElement`  
_L146-152_
- inherits: `ITTMLXMLElement`
- L148 _private typedef_ `typedef ITTMLXMLElement Super;`
- L150 _public function_ `FTTMLXML_OtherElement(const FString& InName, EType InType=EType::Other) : Super(InName, InType)`
- L151 _public prototype_ `virtual ~FTTMLXML_OtherElement() = default;`

#### class `ElectraTTMLParser::FTTMLXML_HeadElement`  
`class FTTMLXML_HeadElement : public FTTMLXML_OtherElement`  
_L155-161_
- inherits: `FTTMLXML_OtherElement`
- L157 _private typedef_ `typedef FTTMLXML_OtherElement Super;`
- L159 _public function_ `FTTMLXML_HeadElement(const FString& InName, EType InType=EType::Head) : Super(InName, InType)`
- L160 _public prototype_ `virtual ~FTTMLXML_HeadElement() = default;`

#### class `ElectraTTMLParser::FTTMLXML_ContentElement`  
`class FTTMLXML_ContentElement : public ITTMLXMLElement, public FTTMLTimeContainer`  
_L166-192_
- inherits: `ITTMLXMLElement,FTTMLTimeContainer`
- desc: <p> and <span> are basically equivalent. <span> may have @xlink attributes and <p> may have regions, both of which we do not support at the moment. Otherwise they are identical and can thus form a common class.
- L168 _private typedef_ `typedef ITTMLXMLElement Super;`
- L170 _public function_ `FTTMLXML_ContentElement(const FString& InName, EType InType=EType::Other) : Super(InName, InType)`
- L171 _public prototype_ `virtual ~FTTMLXML_ContentElement() = default;`
- L172 _public prototype_ `virtual bool ProcessElement(FTTMLParser* Parser, const FString& ElementName, const TArray<FXmlAttribute>& Attributes, int32 LineNumber) override;`
- L173 _public prototype_ `virtual bool ProcessAttributes(FTTMLParser* Parser, const TArray<FXmlAttribute>& Attributes) override;`
- L174 _public prototype_ `virtual bool ProcessClose(FTTMLParser* Parser, const FString& ElementName) override;`
- L176 _public function_ `virtual FTTMLTimeContainer* GetTimeContainer() override`
- L178 _public prototype_ `virtual void RecalculateTimes(bool bRecursively);`
- L180 _public prototype_ `virtual void SetText(FString InText);`
- L181 _public function_ `virtual const FString& GetText() const`
- L184 _public function_ `const TArray<TSharedPtr<FTTMLXML_ContentElement, ESPMode::ThreadSafe>>& GetChildren() const`
- L188 _protected prototype_ `void MergeChildren();`
- L190 _protected member_ `TArray<TSharedPtr<FTTMLXML_ContentElement, ESPMode::ThreadSafe>> Children;`
- L191 _protected member_ `FString Text;`

#### class `ElectraTTMLParser::FTTMLXML_BR_Element`  
`class FTTMLXML_BR_Element : public FTTMLXML_ContentElement`  
_L194-206_
- inherits: `FTTMLXML_ContentElement`
- L196 _private typedef_ `typedef FTTMLXML_ContentElement Super;`
- L198 _public function_ `FTTMLXML_BR_Element(const FString& InName, EType InType=EType::Br) : Super(InName, InType)`
- L199 _public prototype_ `virtual ~FTTMLXML_BR_Element() = default;`
- L200 _public function_ `virtual const FString& GetText() const`
- L202 _public function_ `virtual bool GetPreserveSpace() const`
- L204 _public function_ `virtual void SetPreserveSpace(bool bInPreserveSpace)`

#### class `ElectraTTMLParser::FTTMLXML_Span_Element`  
`class FTTMLXML_Span_Element : public FTTMLXML_ContentElement`  
_L209-215_
- inherits: `FTTMLXML_ContentElement`
- L211 _private typedef_ `typedef FTTMLXML_ContentElement Super;`
- L213 _public function_ `FTTMLXML_Span_Element(const FString& InName, EType InType=EType::Span) : Super(InName, InType)`
- L214 _public prototype_ `virtual ~FTTMLXML_Span_Element() = default;`

#### class `ElectraTTMLParser::FTTMLXML_P_Element`  
`class FTTMLXML_P_Element : public FTTMLXML_ContentElement`  
_L218-224_
- inherits: `FTTMLXML_ContentElement`
- L220 _private typedef_ `typedef FTTMLXML_ContentElement Super;`
- L222 _public function_ `FTTMLXML_P_Element(const FString& InName, EType InType=EType::P) : Super(InName, InType)`
- L223 _public prototype_ `virtual ~FTTMLXML_P_Element() = default;`

#### class `ElectraTTMLParser::FTTMLXML_DivElement`  
`class FTTMLXML_DivElement : public ITTMLXMLElement, public FTTMLTimeContainer`  
_L227-247_
- inherits: `ITTMLXMLElement,FTTMLTimeContainer`
- L229 _private typedef_ `typedef ITTMLXMLElement Super;`
- L231 _public function_ `FTTMLXML_DivElement(const FString& InName, EType InType=EType::Div) : Super(InName, InType)`
- L232 _public prototype_ `virtual ~FTTMLXML_DivElement() = default;`
- L233 _public prototype_ `virtual bool ProcessElement(FTTMLParser* Parser, const FString& ElementName, const TArray<FXmlAttribute>& Attributes, int32 LineNumber) override;`
- L234 _public prototype_ `virtual bool ProcessAttributes(FTTMLParser* Parser, const TArray<FXmlAttribute>& Attributes) override;`
- L236 _public function_ `virtual FTTMLTimeContainer* GetTimeContainer() override`
- L238 _public prototype_ `virtual void RecalculateTimes(bool bRecursively);`
- L240 _public function_ `const TArray<TSharedPtr<FTTMLXML_ContentElement, ESPMode::ThreadSafe>>& GetContentElements() const`
- L243 _public prototype_ `void CollectContentElementRoots(TArray<TSharedPtr<FTTMLXML_ContentElement, ESPMode::ThreadSafe>> &OutContentElements, bool bWithPositiveDurationOnly);`
- L246 _private member_ `TArray<TSharedPtr<FTTMLXML_ContentElement, ESPMode::ThreadSafe>> ContentElements;`

#### class `ElectraTTMLParser::FTTMLXML_BodyElement`  
`class FTTMLXML_BodyElement : public ITTMLXMLElement, public FTTMLTimeContainer`  
_L250-271_
- inherits: `ITTMLXMLElement,FTTMLTimeContainer`
- L252 _private typedef_ `typedef ITTMLXMLElement Super;`
- L254 _public function_ `FTTMLXML_BodyElement(const FString& InName, EType InType=EType::Body) : Super(InName, InType)`
- L255 _public prototype_ `virtual ~FTTMLXML_BodyElement() = default;`
- L256 _public prototype_ `virtual bool ProcessElement(FTTMLParser* Parser, const FString& ElementName, const TArray<FXmlAttribute>& Attributes, int32 LineNumber) override;`
- L257 _public prototype_ `virtual bool ProcessAttributes(FTTMLParser* Parser, const TArray<FXmlAttribute>& Attributes) override;`
- L259 _public function_ `virtual FTTMLTimeContainer* GetTimeContainer() override`
- L261 _public prototype_ `virtual void RecalculateTimes(bool bRecursively);`
- L263 _public function_ `const TArray<TSharedPtr<FTTMLXML_DivElement, ESPMode::ThreadSafe>>& GetDivs() const`
- L267 _public prototype_ `void CollectContentElementRoots(TArray<TSharedPtr<FTTMLXML_ContentElement, ESPMode::ThreadSafe>> &OutContentElements, bool bWithPositiveDurationOnly);`
- L270 _private member_ `TArray<TSharedPtr<FTTMLXML_DivElement, ESPMode::ThreadSafe>> Divs;`

#### class `ElectraTTMLParser::FTTMLXML_TTElement`  
`class FTTMLXML_TTElement : public ITTMLXMLElement, public FTTMLTimeContainer`  
_L274-291_
- inherits: `ITTMLXMLElement,FTTMLTimeContainer`
- L276 _private typedef_ `typedef ITTMLXMLElement Super;`
- L278 _public function_ `FTTMLXML_TTElement(const FString& InName, EType InType=EType::TT) : Super(InName, InType)`
- L279 _public prototype_ `virtual ~FTTMLXML_TTElement() = default;`
- L280 _public prototype_ `virtual bool ProcessElement(FTTMLParser* Parser, const FString& ElementName, const TArray<FXmlAttribute>& Attributes, int32 LineNumber) override;`
- L281 _public prototype_ `virtual bool ProcessAttributes(FTTMLParser* Parser, const TArray<FXmlAttribute>& Attributes) override;`
- L283 _public function_ `virtual FTTMLTimeContainer* GetTimeContainer() override`
- L286 _public function_ `TSharedPtr<FTTMLXML_BodyElement, ESPMode::ThreadSafe> GetBody() const`
- L289 _private member_ `TSharedPtr<FTTMLXML_HeadElement, ESPMode::ThreadSafe> Head;`
- L290 _private member_ `TSharedPtr<FTTMLXML_BodyElement, ESPMode::ThreadSafe> Body;`

#### class `ElectraTTMLParser::FTTMLXML_RootElement`  
`class FTTMLXML_RootElement : public ITTMLXMLElement`  
_L293-306_
- inherits: `ITTMLXMLElement`
- L295 _private typedef_ `typedef ITTMLXMLElement Super;`
- L297 _public function_ `FTTMLXML_RootElement(const FString& InName, EType InType=EType::Other) : Super(InName, InType)`
- L298 _public prototype_ `virtual ~FTTMLXML_RootElement() = default;`
- L299 _public prototype_ `virtual bool ProcessElement(FTTMLParser* Parser, const FString& ElementName, const TArray<FXmlAttribute>& Attributes, int32 LineNumber) override;`
- L301 _public function_ `TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe> GetTT() const`
- L305 _private member_ `TSharedPtr<ITTMLXMLElement, ESPMode::ThreadSafe> TT;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ElectraTTMLParser`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/tx3g/ElectraSubtitleDecoder_TX3G.h` (Private)


#### class `FElectraSubtitleDecoderTX3G`  
`class FElectraSubtitleDecoderTX3G : public IElectraSubtitleDecoder`  
_L12-137_
- inherits: `IElectraSubtitleDecoder`
- desc: 3GPP / TX3G subtitle decoder (ETSI TS 126 245 V11.0.0)
- L15 _public prototype_ `static void RegisterCodecs(IElectraSubtitleDecoderFactoryRegistry& InRegistry);`
- L17 _public prototype_ `FElectraSubtitleDecoderTX3G();`
- L19 _public prototype_ `virtual ~FElectraSubtitleDecoderTX3G();`
- L24 _public prototype_ `virtual bool InitializeStreamWithCSD(const TArray<uint8>& InCSD, const Electra::FParamDict& InAdditionalInfo) override;` — Methods from IElectraSubtitleDecoder
- L25 _public prototype_ `virtual IElectraSubtitleDecoder::FOnSubtitleReceivedDelegate& GetParsedSubtitleReceiveDelegate() override;`
- L26 _public prototype_ `virtual Electra::FTimeValue GetStreamedDeliveryTimeOffset() override;`
- L27 _public prototype_ `virtual void AddStreamedSubtitleData(const TArray<uint8>& InData, Electra::FTimeValue InAbsoluteTimestamp, Electra::FTimeValue InDuration, const Electra::FParamDict& InAdditionalInfo) override;`
- L28 _public prototype_ `virtual void SignalStreamedSubtitleEOD() override;`
- L29 _public prototype_ `virtual void Flush() override;`
- L30 _public prototype_ `virtual void Start() override;`
- L31 _public prototype_ `virtual void Stop() override;`
- L32 _public prototype_ `virtual void UpdatePlaybackPosition(Electra::FTimeValue InAbsolutePosition, Electra::FTimeValue InLocalPosition) override;`
- L121 _private member_ `FOnSubtitleReceivedDelegate ParsedSubtitleDelegate;`
- L122 _private member_ `uint32 NextID = 0;`
- L124 _private member_ `uint16 DataReferenceIndex = 0;`
- L125 _private member_ `int32 Width = 0;`
- L126 _private member_ `int32 Height = 0;`
- L127 _private member_ `int32 TranslationX = 0;`
- L128 _private member_ `int32 TranslationY = 0;`
- L129 _private member_ `uint32 Timescale = 0;`
- L130 _private member_ `uint32 DisplayFlags = 0;`
- L131 _private member_ `int8 HorizontalJustification = 0;`
- L132 _private member_ `int8 VerticalJustification = 0;`
- L133 _private member_ `uint8 BackgroundColorRGBA[4] {0};`
- L134 _private member_ `FBoxRecord BoxRecord;`
- L135 _private member_ `FStyleRecord StyleRecord;`
- L136 _private member_ `TArray<FFontRecord> FontRecords;`

#### struct `FElectraSubtitleDecoderTX3G::FBoxRecord`  
`struct FBoxRecord`  
_L35-41_
- L37 _public member_ `int16 Top = 0;`
- L38 _public member_ `int16 Left = 0;`
- L39 _public member_ `int16 Bottom = 0;`
- L40 _public member_ `int16 Right = 0;`

#### struct `FElectraSubtitleDecoderTX3G::FStyleRecord`  
`struct FStyleRecord`  
_L43-51_
- L45 _public member_ `uint16 StartChar = 0;`
- L46 _public member_ `uint16 EndChar = 0;`
- L47 _public member_ `uint16 FontID = 0;`
- L48 _public member_ `uint8 FaceStyleFlags = 0;`
- L49 _public member_ `uint8 FontSize = 0;`
- L50 _public member_ `uint8 TextColorRGBA[4] { 0 };`

#### struct `FElectraSubtitleDecoderTX3G::FFontRecord`  
`struct FFontRecord`  
_L53-57_
- L55 _public member_ `uint16 FontID = 0;`
- L56 _public member_ `FString FontName;`

#### struct `FElectraSubtitleDecoderTX3G::FHighlight`  
`struct FHighlight`  
_L59-63_
- L61 _public member_ `uint16 StartCharOffset = 0;`
- L62 _public member_ `uint16 EndCharOffset = 0;`

#### struct `FElectraSubtitleDecoderTX3G::FHighlightColor`  
`struct FHighlightColor`  
_L65-68_
- L67 _public member_ `uint8 TextColorRGBA[4] { 0 };`

#### struct `FElectraSubtitleDecoderTX3G::FTextKaraoke`  
`struct FTextKaraoke`  
_L70-80_
- L72 _public member_ `uint32 HighlightStartTime = 0;`
- L79 _public member_ `TArray<FEntry> Entries;`

#### struct `FElectraSubtitleDecoderTX3G::FTextKaraoke::FEntry`  
`struct FEntry`  
_L73-78_
- L75 _public member_ `uint32 HightlightEndTime = 0;`
- L76 _public member_ `uint16 StartCharOffset = 0;`
- L77 _public member_ `uint16 EndCharOffset = 0;`

#### struct `FElectraSubtitleDecoderTX3G::FScrollDelay`  
`struct FScrollDelay`  
_L82-85_
- L84 _public member_ `uint32 ScrollDelay = 0;`

#### struct `FElectraSubtitleDecoderTX3G::FHyperText`  
`struct FHyperText`  
_L87-93_
- L89 _public member_ `uint16 StartCharOffset = 0;`
- L90 _public member_ `uint16 EndCharOffset = 0;`
- L91 _public member_ `FString URL;`
- L92 _public member_ `FString AltString;`

#### struct `FElectraSubtitleDecoderTX3G::FBlink`  
`struct FBlink`  
_L95-99_
- L97 _public member_ `uint16 StartCharOffset = 0;`
- L98 _public member_ `uint16 EndCharOffset = 0;`

#### struct `FElectraSubtitleDecoderTX3G::FTextWrap`  
`struct FTextWrap`  
_L101-104_
- L103 _public member_ `uint8 WrapFlag = 0;`

#### struct `FElectraSubtitleDecoderTX3G::FSubtitleEntry`  
`struct FSubtitleEntry`  
_L107-119_
- L109 _public member_ `FString Text;`
- L110 _public member_ `FBoxRecord Box;`
- L111 _public member_ `TArray<FStyleRecord> Styles;`
- L112 _public member_ `TArray<FHighlight> Highlights;`
- L113 _public member_ `TOptional<FHighlightColor> HighlightColor;`
- L114 _public member_ `TOptional<FTextKaraoke> Karaoke;`
- L115 _public member_ `FScrollDelay ScrollDelay;`
- L116 _public member_ `TArray<FHyperText> HyperTexts;`
- L117 _public member_ `TArray<FBlink> Blinks;`
- L118 _public member_ `TOptional<FTextWrap> TextWrap;`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/wvtt/ElectraSubtitleDecoder_WVTT.h` (Private)


#### class `FElectraSubtitleDecoderWVTT`  
`class FElectraSubtitleDecoderWVTT : public IElectraSubtitleDecoder`  
_L16-59_
- inherits: `IElectraSubtitleDecoder`
- desc: WebVTT subtitle decoder (https://www.w3.org/TR/webvtt1/)
- L19 _public prototype_ `static void RegisterCodecs(IElectraSubtitleDecoderFactoryRegistry& InRegistry);`
- L21 _public prototype_ `FElectraSubtitleDecoderWVTT();`
- L23 _public prototype_ `virtual ~FElectraSubtitleDecoderWVTT();`
- L28 _public prototype_ `virtual bool InitializeStreamWithCSD(const TArray<uint8>& InCSD, const Electra::FParamDict& InAdditionalInfo) override;` — Methods from IElectraSubtitleDecoder
- L29 _public prototype_ `virtual IElectraSubtitleDecoder::FOnSubtitleReceivedDelegate& GetParsedSubtitleReceiveDelegate() override;`
- L30 _public prototype_ `virtual Electra::FTimeValue GetStreamedDeliveryTimeOffset() override;`
- L31 _public prototype_ `virtual void AddStreamedSubtitleData(const TArray<uint8>& InData, Electra::FTimeValue InAbsoluteTimestamp, Electra::FTimeValue InDuration, const Electra::FParamDict& InAdditionalInfo) override;`
- L32 _public prototype_ `virtual void SignalStreamedSubtitleEOD() override;`
- L33 _public prototype_ `virtual void Flush() override;`
- L34 _public prototype_ `virtual void Start() override;`
- L35 _public prototype_ `virtual void Stop() override;`
- L36 _public prototype_ `virtual void UpdatePlaybackPosition(Electra::FTimeValue InAbsolutePosition, Electra::FTimeValue InLocalPosition) override;`
- L48 _private member_ `FCriticalSection ParsedTimerangeLock;`
- L49 _private member_ `TArray<TSharedPtr<FParsedTimerange, ESPMode::ThreadSafe>> ParsedTimeranges;`
- L50 _private member_ `FTimespan NextEvaluationAt { FTimespan::MinValue() };`
- L51 _private member_ `TSharedPtr<FSubtitleDecoderOutputWVTT, ESPMode::ThreadSafe> LastSentSubtitle;`
- L52 _private member_ `Electra::FTimeValue LastPlaybackUpdateAbsPos;`
- L54 _private member_ `FOnSubtitleReceivedDelegate ParsedSubtitleDelegate;`
- L55 _private member_ `uint32 NextID = 0;`
- L56 _private member_ `bool bNeedsParsing = false;`
- L57 _private member_ `bool bSendEmptySubtitleDuringGaps = false;`
- L58 _private member_ `FTimespan SendEmptySubtitleAt { FTimespan::MinValue() };`

#### struct `FElectraSubtitleDecoderWVTT::FParsedTimerange`  
`struct FParsedTimerange`  
_L40-47_
- L42 _public member_ `TSharedPtr<ElectraWebVTTParser::IWebVTTParser, ESPMode::ThreadSafe> Parser;`
- L43 _public member_ `TUniquePtr<ElectraWebVTTParser::IWebVTTParser::ICueIterator> CurrentCueIterator;`
- L44 _public member_ `Electra::FTimeValue AbsoluteStartTime;`
- L45 _public member_ `Electra::FTimeValue Duration;`
- L46 _public member_ `FString SourceID;`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Private/wvtt/WebVTTParser.h` (Private)


#### class `ElectraWebVTTParser::IWebVTTParser`  
`class IWebVTTParser`  
_L13-59_
- L16 _public prototype_ `static TSharedPtr<IWebVTTParser, ESPMode::ThreadSafe> Create();`
- L18 _public prototype_ `virtual ~IWebVTTParser() = default;`
- L23 _public prototype_ `virtual const FString& GetLastErrorMessage() const = 0;` — Returns the most recent error message.
- L30 _public prototype_ `virtual bool ParseWebVTT(const TArray<uint8>& InWebVTTData, const Electra::FParamDict& InOptions) = 0;` — Parses the provided WebVTT document. @return true if successful, false if not. Get error message from GetLastErrorMessage().
- L49 _public prototype_ `virtual void GetCuesAtTime(TArray<TUniquePtr<ICue>>& OutCues, FTimespan& OutNextChangeAt, TUniquePtr<ICueIterator>& InOutIterator, const FTimespan& InAtTime) = 0;`
- L58 _public prototype_ `static FString ProcessCueTextForType(FStringView InText, EWebVTTType InType);`

#### class `ElectraWebVTTParser::IWebVTTParser::ICue`  
`class ICue`  
_L33-41_
- L36 _public prototype_ `virtual ~ICue() = default;`
- L37 _public prototype_ `virtual FTimespan GetStartTime() const = 0;`
- L38 _public prototype_ `virtual FTimespan GetEndTime() const = 0;`
- L39 _public prototype_ `virtual FString GetID() const = 0;`
- L40 _public prototype_ `virtual FString GetText() const = 0;`

#### class `ElectraWebVTTParser::IWebVTTParser::ICueIterator`  
`class ICueIterator`  
_L43-47_
- L46 _public prototype_ `virtual ~ICueIterator() = default;`

#### enum `ElectraWebVTTParser::IWebVTTParser::EWebVTTType`  
`enum class EWebVTTType`  
_L52-57_
- L54 _public enumerator_ `Subtitle`
- L55 _public enumerator_ `Chapters`
- L56 _public enumerator_ `Metadata`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L8 _namespace_ `namespace Electra`
- L10 _namespace_ `namespace ElectraWebVTTParser`

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Public/IElectraSubtitleDecoder.h` (Public)


#### class `IElectraSubtitleDecoder`  
`class IElectraSubtitleDecoder`  
_L15-52_
- desc: Base class of a subtitle decoder.
- L18 _public prototype_ `virtual ~IElectraSubtitleDecoder() = default;`
- L24 _public prototype_ `virtual bool InitializeStreamWithCSD(const TArray<uint8>& InCSD, const Electra::FParamDict& InAdditionalInfo) = 0;` — Initialization methods Initializes with codec specific data and additional attributes.
- L29 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubtitleReceivedDelegate, ISubtitleDecoderOutputPtr );` — Delegate to which the application can subscribe to receive parsed subtitles.
- L30 _public prototype_ `virtual FOnSubtitleReceivedDelegate& GetParsedSubtitleReceiveDelegate() = 0;`
- L36 _public prototype_ `virtual Electra::FTimeValue GetStreamedDeliveryTimeOffset() = 0;` — Data handling methods Returns a time offset at which streamed subtitles should be delivered ahead of their actual timestamp (if they are available earlier)
- L38 _public prototype_ `virtual void AddStreamedSubtitleData(const TArray<uint8>& InData, Electra::FTimeValue InAbsoluteTimestamp, Electra::FTimeValue InDuration, const Electra::FParamDict& InAdditionalInfo) = 0;` — Adds streamed subtitle data.
- L40 _public prototype_ `virtual void SignalStreamedSubtitleEOD() = 0;` — Signals no more streamed subtitles will be arriving.
- L42 _public prototype_ `virtual void Flush() = 0;` — Flushes all input and output.
- L48 _public prototype_ `virtual void Start() = 0;` — Handling methods
- L49 _public prototype_ `virtual void Stop() = 0;`
- L50 _public prototype_ `virtual void UpdatePlaybackPosition(Electra::FTimeValue InAbsolutePosition, Electra::FTimeValue InLocalPosition) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace Electra`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubtitleReceivedDelegate, ISubtitleDecoderOutputPtr );` — Delegate to which the application can subscribe to receive parsed subtitles.

### `Plugins/Media/ElectraSubtitles/Source/ElectraSubtitles/Public/IElectraSubtitleModule.h` (Public)


#### class `IElectraSubtitleModularFeature`  
`class IElectraSubtitleModularFeature : public IModularFeature`  
_L13-43_
- inherits: `IModularFeature`
- L16 _public prototype_ `virtual ~IElectraSubtitleModularFeature() = default;`
- L23 _public prototype_ `virtual bool SupportsFormat(const FString& SubtitleCodecName) const = 0;` — Queries whether or not this plugin's modular feature is capable of handling subtitles of the specified format. The codec string is a commonly known format like "wvtt", "tx3g", "imsc1", etc. but may also be a MIME type like "application/ttml+xml" for sideloaded subtitles.
- L28 _public prototype_ `virtual void GetSupportedFormats(TArray<FString>& OutSupportedCodecNames) const = 0;` — Returns a list of the supported subtitle codecs.
- L37 _public prototype_ `virtual int32 GetPriorityForFormat(const FString& SubtitleCodecName) const = 0;` — Returns a priority for this plugin's subtitle format feature. The return value is not standardized, but the decoder returning the largest value for a format will be used to handle the subtitles. This is mainly used if you provide a plugin of your own that handles a format better than another plugin does and you want to make sure yours will be used.
- L42 _public prototype_ `virtual TSharedPtr<IElectraSubtitleDecoder, ESPMode::ThreadSafe> CreateDecoderForFormat(const FString& SubtitleCodecName) = 0;` — Called to create a decoder for the given format from this plugin's modular feature.

#### class `IElectraSubtitlesModule`  
`class IElectraSubtitlesModule : public IModuleInterface`  
_L50-83_
- inherits: `IModuleInterface`
- desc: Interface for the `ElectraSubtitles` module.
- L53 _public prototype_ `virtual ~IElectraSubtitlesModule() = default;`
- L55 _public function_ `static FName GetModularFeatureName()`
