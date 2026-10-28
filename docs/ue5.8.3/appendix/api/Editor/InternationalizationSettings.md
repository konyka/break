# Editor / InternationalizationSettings

- module root: `Source/Editor/InternationalizationSettings`
- headers: 6; symbols: 197
- symbol kinds: class=6, delegate=1, enum=3, enumerator=106, function=8, macro=3, member=23, namespace=1, prototype=44, struct=1, typedef=1
- DynamicallyLoadedModuleNames: SettingsEditor
- PrivateDependencyModuleNames: AppFramework, Core, CoreUObject, Engine, InputCore, Localization, PropertyEditor, Slate, SlateCore
- PrivateIncludePathModuleNames: 

### `Source/Editor/InternationalizationSettings/Classes/InternationalizationSettingsModel.h` (Public)


#### enum `ETimezoneSetting`  
`enum class ETimezoneSetting : uint8`  
_L16-119_
- reflection: `UENUM()`
- L18 _public enumerator_ `InternationalDateLineWest UMETA(DisplayName="(UTC-12:00) International Date Line West")`
- L19 _public enumerator_ `CoordinatedUniversalTimeNeg11 UMETA(DisplayName="(UTC-11:00) Coordinated Universal Time -11")`
- L20 _public enumerator_ `Samoa UMETA(DisplayName="(UTC-11:00) Samoa")`
- L21 _public enumerator_ `Hawaii UMETA(DisplayName="(UTC-10:00) Hawaii")`
- L22 _public enumerator_ `Alaska UMETA(DisplayName="(UTC-09:00) Alaska")`
- L23 _public enumerator_ `PacificTime_USCAN UMETA(DisplayName="(UTC-08:00) Pacific Time (US and Canada)")`
- L24 _public enumerator_ `BajaCalifornia UMETA(DisplayName="(UTC-08:00) Baja California")`
- L25 _public enumerator_ `MountainTime_USCAN UMETA(DisplayName="(UTC-07:00) Mountain Time (US and Canada)")`
- L26 _public enumerator_ `Chihuahua_LaPaz_Mazatlan UMETA(DisplayName="(UTC-07:00) Chihuahua, La Paz, Mazatlan")`
- L27 _public enumerator_ `Arizona UMETA(DisplayName="(UTC-07:00) Arizona")`
- L28 _public enumerator_ `Saskatchewan UMETA(DisplayName="(UTC-06:00) Saskatchewan")`
- L29 _public enumerator_ `CentralAmerica UMETA(DisplayName="(UTC-06:00) Central America")`
- L30 _public enumerator_ `CentralTime_USCAN UMETA(DisplayName="(UTC-06:00) Central Time (US and Canada)")`
- L31 _public enumerator_ `Guadalajara_MexicoCity_Monterrey UMETA(DisplayName="(UTC-06:00) Guadalajara, Mexico City, Monterrey")`
- L32 _public enumerator_ `EasternTime_USCAN UMETA(DisplayName="(UTC-05:00) Eastern Time (US and Canada)")`
- L33 _public enumerator_ `Bogota_Lima_Quito UMETA(DisplayName="(UTC-05:00) Bogota, Lima, Quito")`
- L34 _public enumerator_ `Indiana_US UMETA(DisplayName="(UTC-05:00) Indiana (East)")`
- L35 _public enumerator_ `Caracas UMETA(DisplayName="(UTC-04:30) Caracas")`
- L36 _public enumerator_ `AtlanticTime_Canada UMETA(DisplayName="(UTC-04:00) Atlantic Time (Canada)")`
- L37 _public enumerator_ `Cuiaba UMETA(DisplayName="(UTC-04:00) Cuiaba")`
- L38 _public enumerator_ `Santiago UMETA(DisplayName="(UTC-04:00) Santiago")`
- L39 _public enumerator_ `Georgetown_LaPaz_Manaus_SanJuan UMETA(DisplayName="(UTC-04:00) Georgetown, La Paz, Manaus, San Juan")`
- L40 _public enumerator_ `Asuncion UMETA(DisplayName="(UTC-04:00) Asuncion")`
- L41 _public enumerator_ `Newfoundland UMETA(DisplayName="(UTC-03:30) Newfoundland")`
- L42 _public enumerator_ `Brasilia UMETA(DisplayName="(UTC-03:00) Brasilia")`
- L43 _public enumerator_ `Greenland UMETA(DisplayName="(UTC-03:00) Greenland")`
- L44 _public enumerator_ `Montevideo UMETA(DisplayName="(UTC-03:00) Montevideo")`
- L45 _public enumerator_ `Cayenne_Fortaleza UMETA(DisplayName="(UTC-03:00) Cayenne, Fortaleza")`
- L46 _public enumerator_ `BuenosAires UMETA(DisplayName="(UTC-03:00) Buenos Aires")`
- L47 _public enumerator_ `MidAtlantic UMETA(DisplayName="(UTC-02:00) Mid-Atlantic")`
- L48 _public enumerator_ `CoordinatedUniversalTimeNeg02 UMETA(DisplayName="(UTC-02:00) Coordinated Universal Time -02")`
- L49 _public enumerator_ `Azores UMETA(DisplayName="(UTC-01:00) Azores")`
- L50 _public enumerator_ `CaboVerdeIs UMETA(DisplayName="(UTC-01:00) Cabo Verde Is.")`
- L51 _public enumerator_ `Dublin_Edinburgh_Lisbon_London UMETA(DisplayName="(UTC) Dublin, Edinburgh, Lisbon, London")`
- L52 _public enumerator_ `Monrovia_Reykjavik UMETA(DisplayName="(UTC) Monrovia, Reykjavik")`
- L53 _public enumerator_ `Casablanca UMETA(DisplayName="(UTC) Casablanca")`
- L54 _public enumerator_ `UTC UMETA(DisplayName="(UTC) Coordinated Universal Time")`
- L55 _public enumerator_ `Belgrade_Bratislava_Budapest_Ljubljana_Prague UMETA(DisplayName="(UTC+01:00) Belgrade, Bratislava, Budapest, Ljubljana, Prague")`
- L56 _public enumerator_ `Sarajevo_Skopje_Warsaw_Zagreb UMETA(DisplayName="(UTC+01:00) Sarajevo, Skopje, Warsaw, Zagreb")`
- L57 _public enumerator_ `Brussels_Copenhagen_Madrid_Paris UMETA(DisplayName="(UTC+01:00) Brussels, Copenhagen, Madrid, Paris")`
- L58 _public enumerator_ `WestCentralAfrica UMETA(DisplayName="(UTC+01:00) West Central Africa")`
- L59 _public enumerator_ `Amsterdam_Berlin_Bern_Rome_Stockholm_Vienna UMETA(DisplayName="(UTC+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna")`
- L60 _public enumerator_ `Windhoek UMETA(DisplayName="(UTC+01:00) Windhoek")`
- L61 _public enumerator_ `Minsk UMETA(DisplayName="(UTC+02:00) Minsk")`
- L62 _public enumerator_ `Cairo UMETA(DisplayName="(UTC+02:00) Cairo")`
- L63 _public enumerator_ `Helsinki_Kyiv_Riga_Sofia_Tallinn_Vilnius UMETA(DisplayName="(UTC+02:00) Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius")`
- L64 _public enumerator_ `Athens_Bucharest UMETA(DisplayName="(UTC+02:00) Athens, Bucharest")`
- L65 _public enumerator_ `Jerusalem UMETA(DisplayName="(UTC+02:00) Jerusalem")`
- L66 _public enumerator_ `Amman UMETA(DisplayName="(UTC+02:00) Amman")`
- L67 _public enumerator_ `Beirut UMETA(DisplayName="(UTC+02:00) Beirut")`
- L68 _public enumerator_ `Harare_Pretoria UMETA(DisplayName="(UTC+02:00) Harare, Pretoria")`
- L69 _public enumerator_ `Damascus UMETA(DisplayName="(UTC+02:00) Damascus")`
- L70 _public enumerator_ `Istanbul UMETA(DisplayName="(UTC+02:00) Istanbul")`
- L71 _public enumerator_ `Kuwait_Riyadh UMETA(DisplayName="(UTC+03:00) Kuwait, Riyadh")`
- L72 _public enumerator_ `Baghdad UMETA(DisplayName="(UTC+03:00) Baghdad")`
- L73 _public enumerator_ `Nairobi UMETA(DisplayName="(UTC+03:00) Nairobi")`
- L74 _public enumerator_ `Kaliningrad UMETA(DisplayName="(UTC+02:00) Kaliningrad")`
- L75 _public enumerator_ `Tehran UMETA(DisplayName="(UTC+03:30) Tehran")`
- L76 _public enumerator_ `Moscow_StPetersburg_Volgograd UMETA(DisplayName="(UTC+03:00) Moscow, St. Petersburg, Volgograd")`
- L77 _public enumerator_ `AbuDhabi_Muscat UMETA(DisplayName="(UTC+04:00) Abu Dhabi, Muscat")`
- L78 _public enumerator_ `Baku UMETA(DisplayName="(UTC+04:00) Baku")`
- L79 _public enumerator_ `Yerevan UMETA(DisplayName="(UTC+04:00) Yerevan")`
- L80 _public enumerator_ `Tbilisi UMETA(DisplayName="(UTC+04:00) Tbilisi")`
- L81 _public enumerator_ `PortLouis UMETA(DisplayName="(UTC+04:00) Port Louis")`
- L82 _public enumerator_ `Kabul UMETA(DisplayName="(UTC+04:30) Kabul")`
- L83 _public enumerator_ `Tashkent UMETA(DisplayName="(UTC+05:00) Tashkent")`
- L84 _public enumerator_ `Islamabad_Karachi UMETA(DisplayName="(UTC+05:00) Islamabad, Karachi")`
- L85 _public enumerator_ `Chennai_Kolkata_Mumbai_NewDelhi UMETA(DisplayName="(UTC+05:30) Chennai, Kolkata, Mumbai, New Delhi")`
- L86 _public enumerator_ `SriJayawardenepura UMETA(DisplayName="(UTC+05:30) Sri Jayawardenepura")`
- L87 _public enumerator_ `Kathmandu UMETA(DisplayName="(UTC+05:45) Kathmandu")`
- L88 _public enumerator_ `Ekaterinburg UMETA(DisplayName="(UTC+05:00) Ekaterinburg")`
- L89 _public enumerator_ `Astana UMETA(DisplayName="(UTC+06:00) Astana")`
- L90 _public enumerator_ `Dhaka UMETA(DisplayName="(UTC+06:00) Dhaka")`
- L91 _public enumerator_ `Yangon_Rangoon UMETA(DisplayName="(UTC+06:30) Yangon (Rangoon)")`
- L92 _public enumerator_ `Bangkok_Hanoi_Jakarta UMETA(DisplayName="(UTC+07:00) Bangkok, Hanoi, Jakarta")`
- L93 _public enumerator_ `Krasnoyarsk UMETA(DisplayName="(UTC+07:00) Krasnoyarsk")`
- L94 _public enumerator_ `Novosibirsk UMETA(DisplayName="(UTC+07:00) Novosibirsk")`
- L95 _public enumerator_ `Beijing_Chongqing_HongKong_Urumqi UMETA(DisplayName="(UTC+08:00) Beijing, Chongqing, Hong Kong, Urumqi")`
- L96 _public enumerator_ `KualaLumpur_Singapore UMETA(DisplayName="(UTC+08:00) Kuala Lumpur, Singapore")`
- L97 _public enumerator_ `Taipei UMETA(DisplayName="(UTC+08:00) Taipei")`
- L98 _public enumerator_ `Perth UMETA(DisplayName="(UTC+08:00) Perth")`
- L99 _public enumerator_ `Ulaanbaatar UMETA(DisplayName="(UTC+08:00) Ulaanbaatar")`
- L100 _public enumerator_ `Irkutsk UMETA(DisplayName="(UTC+08:00) Irkutsk")`
- L101 _public enumerator_ `Seoul UMETA(DisplayName="(UTC+09:00) Seoul")`
- L102 _public enumerator_ `Osaka_Sapporo_Tokyo UMETA(DisplayName="(UTC+09:00) Osaka, Sapporo, Tokyo")`
- L103 _public enumerator_ `Darwin UMETA(DisplayName="(UTC+09:30) Darwin")`
- L104 _public enumerator_ `Adelaide UMETA(DisplayName="(UTC+09:30) Adelaide")`
- L105 _public enumerator_ `Yakutsk UMETA(DisplayName="(UTC+9:00) Yakutsk")`
- L106 _public enumerator_ `Canberra_Melbourne_Sydney UMETA(DisplayName="(UTC+10:00) Canberra, Melbourne, Sydney")`
- L107 _public enumerator_ `Brisbane UMETA(DisplayName="(UTC+10:00) Brisbane")`
- L108 _public enumerator_ `Hobart UMETA(DisplayName="(UTC+10:00) Hobart")`
- L109 _public enumerator_ `Guam_PortMoresby UMETA(DisplayName="(UTC+10:00) Guam, Port Moresby")`
- L110 _public enumerator_ `Vladivostok UMETA(DisplayName="(UTC+10:00) Vladivostok")`
- L111 _public enumerator_ `SolomonIs_NewCaledonia UMETA(DisplayName="(UTC+11:00) Solomon Is., New Caledonia")`
- L112 _public enumerator_ `Magadan UMETA(DisplayName="(UTC+11:00) Magadan")`
- L113 _public enumerator_ `Fiji UMETA(DisplayName="(UTC+12:00) Fiji")`
- L114 _public enumerator_ `Auckland_Wellington UMETA(DisplayName="(UTC+12:00) Auckland, Wellington")`
- L115 _public enumerator_ `CoordinatedUniversalTime12 UMETA(DisplayName="(UTC+12:00) Coordinated Universal Time +12")`
- L116 _public enumerator_ `Nukualofa UMETA(DisplayName="(UTC+13:00) Nuku'alofa")`
- L118 _public enumerator_ `LocalTime`

#### class `UInternationalizationSettingsModel`  
`class UInternationalizationSettingsModel : public UObject`  
_L125-154_
- reflection: `UCLASS(MinimalAPI, config=EditorSettings)`
- inherits: `UObject`
- desc: Implements loading and saving of internationalization settings.
- L131 _public prototype_ `void ResetToDefault();`
- L132 _public prototype_ `bool GetEditorLanguage(FString& OutEditorLanguage) const;`
- L133 _public prototype_ `void SetEditorLanguage(const FString& InEditorLanguage);`
- L134 _public prototype_ `bool GetEditorLocale(FString& OutEditorLocale) const;`
- L135 _public prototype_ `void SetEditorLocale(const FString& InEditorLocale);`
- L136 _public prototype_ `bool GetPreviewGameLanguage(FString& OutPreviewGameLanguage) const;`
- L137 _public prototype_ `void SetPreviewGameLanguage(const FString& InPreviewGameLanguage);`
- L138 _public prototype_ `bool ShouldUseLocalizedNumericInput() const;`
- L139 _public prototype_ `void SetShouldUseLocalizedNumericInput(const bool Value);`
- L140 _public prototype_ `bool ShouldUseLocalizedPropertyNames() const;`
- L141 _public prototype_ `void SetShouldUseLocalizedPropertyNames(const bool Value);`
- L142 _public prototype_ `bool ShouldUseLocalizedNodeAndPinNames() const;`
- L143 _public prototype_ `void SetShouldUseLocalizedNodeAndPinNames(const bool Value);`
- L145 _public prototype_ `int32 GetTimezoneValue() const;`
- L152 _public member_ `ETimezoneSetting DisplayTimezone;` — `UPROPERTY(EditAnywhere, Config, Category = Time)` — Timezone to use for display purposes in FDateTime

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERNATIONALIZATIONSETTINGS_API`

### `Source/Editor/InternationalizationSettings/Private/UserGeneratedContentLocalizationDescriptorDetails.h` (Private)


#### class `FUserGeneratedContentLocalizationDescriptorDetails`  
`class FUserGeneratedContentLocalizationDescriptorDetails : public IPropertyTypeCustomization`  
_L10-43_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _private prototype_ `void CustomizeNativeCulture(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils);`
- L26 _private prototype_ `FCulturePtr NativeCulture_GetCulture() const;`
- L27 _private prototype_ `bool NativeCulture_IsCulturePickable(FCulturePtr Culture) const;`
- L28 _private prototype_ `void NativeCulture_OnSelectionChanged(FCulturePtr SelectedCulture, ESelectInfo::Type SelectInfo);`
- L30 _private prototype_ `void CustomizeCulturesToGenerate(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils);`
- L31 _private prototype_ `void CulturesToGenerate_OnPreBatchSelect();`
- L32 _private prototype_ `void CulturesToGenerate_OnPostBatchSelect();`
- L33 _private prototype_ `void CulturesToGenerate_OnCultureSelectionChanged(bool IsSelected, FCulturePtr Culture);`
- L34 _private prototype_ `bool CulturesToGenerate_IsCultureSelected(FCulturePtr Culture) const;`
- L36 _private member_ `TArray<FCulturePtr> AvailableCultures;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> NativeCultureHandle;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> CulturesToGenerateHandle;`
- L42 _private member_ `bool CulturesToGenerate_IsInBatchSelectOperation = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Source/Editor/InternationalizationSettings/Public/InternationalizationSettings.h` (Public)
_(no declarations extracted)_

### `Source/Editor/InternationalizationSettings/Public/InternationalizationSettingsModelDetails.h` (Public)


#### class `FInternationalizationSettingsModelDetails`  
`class FInternationalizationSettingsModelDetails : public IDetailCustomization`  
_L13-21_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERNATIONALIZATIONSETTINGS_API`

### `Source/Editor/InternationalizationSettings/Public/InternationalizationSettingsModule.h` (Public)


#### class `IInternationalizationSettingsModule`  
`class IInternationalizationSettingsModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L12 _public function_ `static inline IInternationalizationSettingsModule& Get()`
- L17 _public function_ `static inline bool IsAvailable()`

### `Source/Editor/InternationalizationSettings/Public/SCulturePicker.h` (Public)


#### struct `FCultureEntry`  
`struct FCultureEntry`  
_L33-55_
- L35 _public member_ `FCulturePtr Culture;`
- L36 _public member_ `TArray< TSharedPtr<FCultureEntry> > Children;`
- L37 _public member_ `bool IsSelectable;`
- L38 _public member_ `bool AutoExpand = false;`
- L40 _public function_ `FCultureEntry(const FCulturePtr& InCulture, const bool InIsSelectable = true) : Culture(InCulture) , IsSelectable(InIsSelectable)`
- L45 _public function_ `FCultureEntry(const FCultureEntry& Source) : Culture(Source.Culture) , IsSelectable(Source.IsSelectable)`

#### class `SCulturePicker`  
`class SCulturePicker : public SCompoundWidget`  
_L57-154_
- inherits: `SCompoundWidget`
- L61 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsCulturePickable, FCulturePtr);` — A delegate type invoked when a selection changes somewhere.
- L62 _public typedef_ `typedef TSlateDelegates< FCulturePtr >::FOnSelectionChanged FOnSelectionChanged;`
- L86 _public function_ `SLATE_BEGIN_ARGS( SCulturePicker ) : _DisplayNameFormat(ECultureDisplayFormat::ActiveCultureDisplayName) , _ViewMode(ECulturesViewMode::Hierarchical) , _CanSelectNone(false)`
- L91 _public function_ `SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FIsCulturePickable, IsCulturePickable ) SLATE_ARGUMENT( FCulturePtr, InitialSelection ) SLATE_ARGUMENT(ECultureDisplayFormat, DisplayNameFormat) SLATE_ARGUMENT(ECulturesViewMode, ViewMode) SLATE_ARGUMENT(bool, CanSelectNone) SLATE_END_ARGS() SCulturePicker() : DisplayNameFormat(ECultureDisplayFormat::ActiveCultureDisplayName) , CanSelectNone(false) , SuppressSelectionCallback(false)`
- L105 _public prototype_ `void Construct( const FArguments& InArgs );`
- L106 _public prototype_ `void RequestTreeRefresh();`
- L109 _private prototype_ `TSharedPtr<FCultureEntry> FindEntryForCulture(FCulturePtr Culture) const;`
- L110 _private prototype_ `TSharedPtr<FCultureEntry> FindEntryForCultureImpl(FCulturePtr Culture, const TArray<TSharedPtr<FCultureEntry>>& Entries) const;`
- L112 _private prototype_ `void AutoExpandEntries();`
- L113 _private prototype_ `void AutoExpandEntriesImpl(const TArray<TSharedPtr<FCultureEntry>>& Entries);`
- L115 _private prototype_ `void BuildStockEntries();`
- L116 _private prototype_ `void RebuildEntries();`
- L118 _private prototype_ `void OnFilterStringChanged(const FText& InFilterString);`
- L119 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FCultureEntry> Entry, const TSharedRef<STableViewBase>& Table);`
- L120 _private prototype_ `void OnGetChildren(TSharedPtr<FCultureEntry> Entry, TArray< TSharedPtr<FCultureEntry> >& Children);`
- L121 _private prototype_ `void OnSelectionChanged(TSharedPtr<FCultureEntry> Entry, ESelectInfo::Type SelectInfo);`
- L124 _private prototype_ `FString GetCultureDisplayName(const FCultureRef& Culture, const bool bIsRootItem) const;`
- L126 _private member_ `TSharedPtr< STreeView< TSharedPtr<FCultureEntry> > > TreeView;`
- L129 _private member_ `TArray< TSharedPtr<FCultureEntry> > StockEntries;` — The top level culture entries for all possible stock cultures.
- L132 _private member_ `TArray< TSharedPtr<FCultureEntry> > RootEntries;` — The top level culture entries to be displayed in the tree view.
- L135 _private member_ `FString FilterString;` — The string by which to filter cultures names.
- L138 _private member_ `FOnSelectionChanged OnCultureSelectionChanged;` — Delegate to invoke when selection changes.
- L141 _private member_ `FIsCulturePickable IsCulturePickable;` — Delegate to invoke to set whether a culture is "pickable".
- L144 _private member_ `ECultureDisplayFormat DisplayNameFormat;` — How should we display culture names?
- L147 _private member_ `ECulturesViewMode ViewMode;` — How should we display the list of cultures?
- L150 _private member_ `bool CanSelectNone;` — Should a null culture option be available?
- L153 _private member_ `bool SuppressSelectionCallback;` — Flags that the selection callback shouldn't be called when selecting - useful for initial selection, for instance.

#### enum `SCulturePicker::ECultureDisplayFormat`  
`enum class ECultureDisplayFormat`  
_L65-75_
- desc: Different display name formats that can be used for a culture
- L68 _public enumerator_ `ActiveCultureDisplayName` — Should the culture display the name used by the active culture?
- L70 _public enumerator_ `NativeCultureDisplayName` — Should the culture display the name used by the given culture? (ie, localized in their own native culture)
- L72 _public enumerator_ `ActiveAndNativeCultureDisplayName` — Should the culture display both the active and native cultures name? (will appear as "<ActiveName> (<NativeName>)")
- L74 _public enumerator_ `NativeAndActiveCultureDisplayName` — Should the culture display both the native and active cultures name? (will appear as "<NativeName> (<ActiveName>)")

#### enum `SCulturePicker::ECulturesViewMode`  
`enum class ECulturesViewMode`  
_L77-83_
- L80 _public enumerator_ `Hierarchical` — Display the cultures hierarchically in a tree
- L82 _public enumerator_ `Flat` — Display the cultures as a flat list

#### class `SCulturePickerCombo`  
`class SCulturePickerCombo : public SCompoundWidget`  
_L156-184_
- inherits: `SCompoundWidget`
- L159 _public function_ `SLATE_BEGIN_ARGS(SCulturePickerCombo) : _DisplayNameFormat(SCulturePicker::ECultureDisplayFormat::ActiveCultureDisplayName) , _ViewMode(SCulturePicker::ECulturesViewMode::Hierarchical) , _CanSelectNone(false)`
- L164 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_EVENT(SCulturePicker::FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(SCulturePicker::FIsCulturePickable, IsCulturePickable) SLATE_ATTRIBUTE(FCulturePtr, SelectedCulture) SLATE_ARGUMENT(SCulturePicker::ECultureDisplayFormat, DisplayNameFormat) SLATE_ARGUMENT(SCulturePicker::ECulturesViewMode, ViewMode) SLATE_ARGUMENT(bool, CanSelectNone) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L176 _private prototype_ `FText GetSelectedCultureDisplayName() const;`
- L177 _private prototype_ `void OnSelectedCultureChanged(FCulturePtr NewSelectedCulture, ESelectInfo::Type SelectInfo);`
- L179 _private member_ `TAttribute<FCulturePtr> SelectedCulture;`
- L180 _private member_ `SCulturePicker::FOnSelectionChanged OnSelectionChanged;`
- L181 _private member_ `SCulturePicker::ECultureDisplayFormat DisplayNameFormat;`
- L183 _private member_ `TSharedPtr<SComboButton> ComboButton;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API INTERNATIONALIZATIONSETTINGS_API`
- L61 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsCulturePickable, FCulturePtr);` — A delegate type invoked when a selection changes somewhere.
