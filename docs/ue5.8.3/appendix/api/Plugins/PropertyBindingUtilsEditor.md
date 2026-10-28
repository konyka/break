# Plugins / PropertyBindingUtilsEditor

- module root: `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsEditor`
- headers: 3; symbols: 135
- symbol kinds: class=3, delegate=2, enum=1, enumerator=2, function=14, member=24, namespace=7, prototype=74, struct=4, variable=4
- PrivateDependencyModuleNames: StructUtilsEditor
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, EditorFramework, Engine, InputCore, PropertyBindingUtils, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsEditor/Public/PropertyBindingExtension.h` (Public)


#### struct `UE::PropertyBinding::FPropertyInfoOverride`  
`struct FPropertyInfoOverride`  
_L28-35_
- L31 _public member_ `FText TypeNameText;` — Display Name Text of the Ref Type
- L34 _public member_ `FEdGraphPinType PinType;` — Ref Type expressed as a Pin Type

#### enum `UE::PropertyBinding::Meta::Private::(anonymous)`  
``  
_L41-46_

#### struct `UE::PropertyBinding::FCachedBindingData`  
`struct FCachedBindingData`  
_L84-193_
- L86 _public prototype_ `FCachedBindingData(IPropertyBindingBindingCollectionOwner* InPropertyBindingsOwner , const FPropertyBindingPath& InTargetPath , const TSharedPtr<const IPropertyHandle>& InPropertyHandle , const TConstArrayView<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> InAccessibleStructs );`
- L92 _public prototype_ `virtual ~FCachedBindingData() = default;`
- L94 _public prototype_ `[[nodiscard]] bool HasBinding(FPropertyBindingBindingCollection::ESearchMode SearchMode) const;`
- L95 _public prototype_ `[[nodiscard]] const FPropertyBindingBinding* FindBinding(FPropertyBindingBindingCollection::ESearchMode SearchMode) const;`
- L96 _public prototype_ `void AddBinding(TConstArrayView<FBindingChainElement> InBindingChain);`
- L97 _public prototype_ `void RemoveBinding(FPropertyBindingBindingCollection::ESearchMode RemoveMode);`
- L99 _public prototype_ `[[nodiscard]] UStruct* ResolveIndirection(TConstArrayView<FBindingChainElement> InBindingChain);`
- L101 _public prototype_ `[[nodiscard]] bool CanAcceptPropertyOrChildren(const FProperty* SourceProperty, TConstArrayView<FBindingChainElement> InBindingChain);`
- L103 _public prototype_ `[[nodiscard]] bool CanBindToProperty(const FProperty* SourceProperty, TConstArrayView<FBindingChainElement> InBindingChain);`
- L104 _public prototype_ `[[nodiscard]] bool CanBindToContextStruct(const UStruct* InStruct, int32 InStructIndex);`
- L106 _public prototype_ `[[nodiscard]] bool CanCreateParameter(const FPropertyBindingBindableStructDescriptor& InStructDesc, TArray<TSharedPtr<const UE::PropertyBinding::FPropertyInfoOverride>>& OutPropertyInfoOverrides) const;`
- L107 _public prototype_ `void PromoteToParameter(FName InPropertyName, TConstStructView<FPropertyBindingBindableStructDescriptor> InStructDesc, TSharedPtr<const FPropertyInfoOverride> InPropertyInfoOverride);`
- L109 _public prototype_ `[[nodiscard]] FText GetText();`
- L110 _public prototype_ `[[nodiscard]] FText GetTooltipText();`
- L111 _public prototype_ `[[nodiscard]] FLinearColor GetColor();`
- L112 _public prototype_ `[[nodiscard]] const FSlateBrush* GetImage();`
- L114 _public prototype_ `[[nodiscard]] TConstStructView<FPropertyBindingBindableStructDescriptor> GetBindableStructDescriptor(int32 InStructIndex) const;`
- L115 _public prototype_ `[[nodiscard]] TStructView<FPropertyBindingBindableStructDescriptor> GetMutableBindableStructDescriptor(int32 InStructIndex);`
- L116 _public prototype_ `[[nodiscard]] TWeakObjectPtr<> GetWeakOwner() const;`
- L117 _public prototype_ `[[nodiscard]] UObject* GetOwner() const;`
- L118 _public prototype_ `[[nodiscard]] const IPropertyHandle* GetPropertyHandle() const;`
- L119 _public prototype_ `[[nodiscard]] const FPropertyBindingPath& GetSourcePath() const;`
- L120 _public prototype_ `[[nodiscard]] const FPropertyBindingPath& GetTargetPath() const;`
- L121 _public prototype_ `[[nodiscard]] TConstArrayView<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> GetAccessibleStructs() const;`
- L122 _public prototype_ `[[nodiscard]] virtual TNotNull<const UEdGraphSchema_K2*> GetEdGraphSchema() const;`
- L124 _public prototype_ `[[nodiscard]] FText GetFormatableText() const;`
- L125 _public prototype_ `[[nodiscard]] FText GetFormatableTooltipText() const;`
- L127 _public prototype_ `[[nodiscard]] virtual bool IsPropertyReference(const FProperty& InProperty);`
- L128 _public prototype_ `virtual void UpdateSourcePropertyPath(TConstStructView<FPropertyBindingBindableStructDescriptor> InDescriptor, const FPropertyBindingPath& InSourcePath, FString& OutString);`
- L129 _public prototype_ `virtual void UpdatePropertyReferenceTooltip(const FProperty& InProperty, FTextBuilder& InOutTextBuilder) const;`
- L130 _public prototype_ `[[nodiscard]] virtual bool CanBindToContextStructInternal(const UStruct* InStruct, int32 InStructIndex);`
- L131 _public prototype_ `[[nodiscard]] virtual bool CanAcceptPropertyOrChildrenInternal(const FProperty& InProperty, TConstArrayView<FBindingChainElement> InBindingChain);`
- L132 _public prototype_ `[[nodiscard]] virtual bool AddBindingInternal(TConstStructView<FPropertyBindingBindableStructDescriptor> InDescriptor, FPropertyBindingPath& InOutSourcePath, const FPropertyBindingPath& InTargetPath);`
- L134 _public prototype_ `virtual void AddPropertyInfoOverride(const FProperty& InProperty, TArray<TSharedPtr<const UE::PropertyBinding::FPropertyInfoOverride>>& OutPropertyInfoOverrides) const;`
- L135 _public prototype_ `virtual void GetSourceDataViewForNewBinding(TNotNull<IPropertyBindingBindingCollectionOwner*> InBindingsOwner,TConstStructView<FPropertyBindingBindableStructDescriptor> InDescriptor, FPropertyBindingDataView& OutSourceDataView);`
- L146 _public prototype_ `[[nodiscard]] virtual bool GetPinTypeAndIconForProperty(const FProperty& InProperty, FPropertyBindingDataView InTargetDataView, FEdGraphPinType& OutPinType, FName& OutIconName) const final;` — `UE_DEPRECATED(5.7, "Use GetPinInfoForProperty instead")`
- L148 _public prototype_ `[[nodiscard]] virtual bool GetPinTypeAndIconForProperty(const FProperty& InProperty, FPropertyBindingDataView InTargetDataView, FEdGraphPinType& OutPinType, const FSlateBrush*& OutIconBrush) const final;` — `UE_DEPRECATED(5.8, "Use GetPinInfoForProperty instead")`
- L149 _public prototype_ `[[nodiscard]] virtual FPinInfo GetPinInfoForProperty(TNotNull<const FProperty*> InProperty, FPropertyBindingDataView InTargetDataView) const;`
- L150 _public prototype_ `[[nodiscard]] virtual bool GetPropertyFunctionText(FConstStructView InPropertyFunctionStructView, FText& OutText) const;`
- L151 _public prototype_ `[[nodiscard]] virtual bool GetPropertyFunctionTooltipText(FConstStructView InPropertyFunctionStructView, FText& OutText) const;`
- L152 _public prototype_ `[[nodiscard]] virtual bool GetPropertyFunctionIconColor(FConstStructView InPropertyFunctionStructView, FLinearColor& OutColor) const;`
- L153 _public prototype_ `[[nodiscard]] virtual bool GetPropertyFunctionImage(FConstStructView InPropertyFunctionStructView, const FSlateBrush*& OutImage) const;`
- L156 _public prototype_ `[[nodiscard]] virtual bool DeterminePropertiesCompatibilityInternal( const FProperty* InSourceProperty, const FProperty* InTargetProperty, const void* InSourcePropertyValue, const void* InTargetPropertyValue, bool& bOutAreCompatible) const;` — @return whether the compatibility has been evaluated.
- L162 _public prototype_ `[[nodiscard]] virtual bool DeterminePropertyAndContextStructCompatibleInternal(const UStruct* SourceStruct, const FProperty* TargetProperty) const;`
- L164 _public prototype_ `void UpdateData();`
- L167 _private prototype_ `void ConditionallyUpdateData();`
- L168 _private prototype_ `bool ArePropertyAndContextStructCompatible(const UStruct* SourceStruct, const FProperty* TargetProperty) const;`
- L169 _private prototype_ `bool ArePropertiesCompatible(const FProperty* SourceProperty, const FProperty* TargetProperty, const void* SourcePropertyValue, const void* TargetPropertyValue) const;`
- L171 _private member_ `TWeakInterfacePtr<IPropertyBindingBindingCollectionOwner> WeakBindingsOwner = nullptr;`
- L172 _private member_ `FPropertyBindingPath CachedSourcePath;`
- L173 _private member_ `FPropertyBindingPath TargetPath;`
- L174 _private member_ `TSharedPtr<const IPropertyHandle> PropertyHandle;`
- L175 _private member_ `TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> AccessibleStructs;`
- L178 _private member_ `FText SourceStructName;` — Default name of the source struct.
- L181 _private member_ `FText FormatableText;` — Binding's display name text. Expects it's source struct name to be injected before use.
- L184 _private member_ `FText FormatableTooltipText;` — Binding's tooltip text. Expects it's source struct name to be injected before use.
- L186 _private member_ `FLinearColor Color = FLinearColor::White;`
- L187 _private member_ `const FSlateBrush* Image = nullptr;`
- L190 _private member_ `bool bIsCachedDataValid = false;` — The binding is invalid. The image/color/tooltip/... represents an error state.
- L192 _private member_ `bool bIsDataCached = false;`
- L195 _function_ `inline TConstStructView<FPropertyBindingBindableStructDescriptor> FCachedBindingData::GetBindableStructDescriptor(const int32 InStructIndex) const`
- L201 _function_ `inline TStructView<FPropertyBindingBindableStructDescriptor> FCachedBindingData::GetMutableBindableStructDescriptor(const int32 InStructIndex)`
- L207 _function_ `inline TWeakObjectPtr<> FCachedBindingData::GetWeakOwner() const`
- L212 _function_ `inline UObject* FCachedBindingData::GetOwner() const`
- L217 _function_ `inline const IPropertyHandle* FCachedBindingData::GetPropertyHandle() const`
- L222 _function_ `inline const FPropertyBindingPath& FCachedBindingData::GetSourcePath() const`
- L227 _function_ `inline const FPropertyBindingPath& FCachedBindingData::GetTargetPath() const`
- L232 _function_ `inline TConstArrayView<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> FCachedBindingData::GetAccessibleStructs() const`
- L237 _function_ `inline FText FCachedBindingData::GetFormatableText() const`
- L242 _function_ `inline FText FCachedBindingData::GetFormatableTooltipText() const`

#### struct `UE::PropertyBinding::FCachedBindingData::FPinInfo`  
`struct FPinInfo`  
_L137-142_
- L139 _public member_ `FEdGraphPinType Type;`
- L140 _public member_ `const FSlateBrush* IconBrush = nullptr;`
- L141 _public member_ `FLinearColor IconColor = FLinearColor::White;`

#### class `FPropertyBindingExtension`  
`class FPropertyBindingExtension : public IDetailPropertyExtensionHandler`  
_L249-293_
- inherits: `IDetailPropertyExtensionHandler`
- L254 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& InPropertyHandle) const override;`
- L255 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L259 _protected prototype_ `virtual TSharedPtr<UE::PropertyBinding::FCachedBindingData> CreateCachedBindingData(IPropertyBindingBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath, const TSharedPtr<IPropertyHandle>& InPropertyHandle, TConstArrayView<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> InAccessibleStructs) const;`
- L260 _protected prototype_ `virtual bool CanBindToProperty(const FPropertyBindingPath& InTargetPath, const IPropertyHandle& InPropertyHandle) const;`
- L261 _protected prototype_ `virtual uint64 GetDisallowedPropertyFlags() const;`
- L269 _protected prototype_ `virtual bool GetPromotionToParameterOverrideInternal(const FProperty& InProperty, bool& bOutOverride) const;` — The optional override criteria of whether the property can be promoted to parameter @param InProperty the property to be tested upon @param bOutOverride Whether the property should be promoted to parameter, if the return value is true @return Whether the promotion criteria is overridden for this property
- L270 _protected prototype_ `virtual void UpdateContextStruct(TConstStructView<FPropertyBindingBindableStructDescriptor> InStructDesc, FBindingContextStruct& InOutContextStruct, TMap<FString, FText>& InOutSectionNames) const;`
- L271 _protected prototype_ `virtual void CustomizeDetailWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, IPropertyBindingBindingCollectionOwner* InBindingsOwner, TSharedPtr<IPropertyHandle> InPropertyHandle, const FPropertyBindingPath& InTargetPath, TSharedPtr<UE::PropertyBinding::FCachedBindingData> InCachedBindingData) const;`
- L273 _protected prototype_ `virtual void CustomizePropertyBindingWidgetArgs(FPropertyBindingWidgetArgs& Args, IPropertyBindingBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath, TSharedPtr<UE::PropertyBinding::FCachedBindingData> InCachedBindingData);`
- L276 _protected function_ `virtual void CustomizeWidgetArgs(FPropertyBindingWidgetArgs& Args, IPropertyBindingBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath, TSharedPtr<UE::PropertyBinding::FCachedBindingData> InCachedBindingData) final` — `UE_DEPRECATED(5.7, "CustomizeWidgetArgs is deprecated. Use CustomizePropertyBindingWidgetArgs instead.")`
- L281 _protected prototype_ `virtual bool CanBindToArrayElements() const;`
- L282 _protected prototype_ `[[nodiscard]] virtual TNotNull<const UEdGraphSchema_K2*> GetEdGraphSchema() const;`
- L284 _protected prototype_ `void WrapValueWidget(FDetailWidgetRow& InWidgetRow, const TSharedPtr<UE::PropertyBinding::FCachedBindingData>& InCachedBindingData) const;`
- L285 _protected prototype_ `void CustomizeResetToDefault(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const TSharedPtr<IPropertyHandle>& InPropertyHandle, const TSharedPtr<UE::PropertyBinding::FCachedBindingData>& InCachedBindingData) const;`
- L288 _protected prototype_ `static TSharedRef<SWidget> MakeContextStructWidget(const FPropertyBindingBindableStructDescriptor& InContextStruct);` — `UE_DEPRECATED(5.8, "Use the overload with Schema instead.")`
- L289 _protected prototype_ `static TSharedRef<SWidget> MakeContextStructWidget(TNotNull<const UEdGraphSchema_K2*> Schema, const FPropertyBindingBindableStructDescriptor& InContextStruct);`
- L292 _private prototype_ `bool CanPromoteToParameter(const TSharedPtr<IPropertyHandle>& InPropertyHandle) const;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace PropertyBinding` (scope `UE`)
- L37 _namespace_ `namespace Meta` (scope `UE::PropertyBinding`)
- L37 _namespace_ `namespace Private` (scope `UE::PropertyBinding::Meta`)
- L43 _enumerator_ `NoBinding` (scope `UE::PropertyBinding::Meta::Private::__anon9bac61420103`) — [ClassMetadata] [PropertyMetadata] [StructMetadata] The property cannot be bound to (target of a binding).
- L45 _enumerator_ `NoPromoteToParameter` (scope `UE::PropertyBinding::Meta::Private::__anon9bac61420103`) — [ClassMetadata] [PropertyMetadata] [StructMetadata] The property cannot be promoted to parameters.
- L49 _variable_ `const FLazyName MetaDataStructIDName("Str` (scope `UE::PropertyBinding`)
- L50 _variable_ `const FLazyName MetaDataNoBindingName("NoB` (scope `UE::PropertyBinding`)
- L51 _variable_ `const FLazyName MetaDataNoPromoteToParameter("NoP` (scope `UE::PropertyBinding`)
- L58 _variable_ `const FLazyName MetaDataBindingRoot("Bin` (scope `UE::PropertyBinding`) — Useful if you'd like to cut off some properties from the final path. For example, if your bindable struct descriptors point to structs, and you have these structs wrapped into object nodes on your graph, then you'd annotate the struct property inside the UObject node with both StructIDForPropertyBinding and BindingRoot.
- L61 _prototype_ `extern FText GetPropertyTypeText(const FProperty* Property);` (scope `UE::PropertyBinding`) — `UE_DEPRECATED(5.8, "Use the overload with Schema instead.")`
- L62 _prototype_ `extern FText GetPropertyTypeText(TNotNull<const UEdGraphSchema_K2*> Schema, const FProperty* Property);` (scope `UE::PropertyBinding`)
- L73 _prototype_ `extern TSharedPtr<const IPropertyHandle> MakeStructPropertyPathFromPropertyHandle( const TSharedPtr<const IPropertyHandle>& InPropertyHandle , FPropertyBindingPath& OutPath , FGuid InFallbackStructID = {} );` (scope `UE::PropertyBinding`) — Returns property path for a specific property. Walks towards root up until a property with metadata "MetaDataName" is found. The property's metadata "MetaDataName" is expected to specify the containing struct ID. @param InPropertyHandle Handle to the property to find path for. @param OutPath Resulting property path. @param InFallbackStructID If no bindable struct are found this ID will be used to build the property path. @return property handle of the property found with the required metadata.
- L82 _prototype_ `bool IsPropertyBindable(const FProperty& Property);` (scope `UE::PropertyBinding`) — Returns true if provided Property is bindable.

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsEditor/Public/PropertyBindingUtilsEditorModule.h` (Public)


#### class `IPropertyBindingUtilsEditorModule`  
`class IPropertyBindingUtilsEditorModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static IPropertyBindingUtilsEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtilsEditor/Public/Widgets/SPropertyBindingView.h` (Public)


#### class `UE::PropertyBinding::SBindingView`  
`class SBindingView : public SCompoundWidget`  
_L21-58_
- inherits: `SCompoundWidget`
- L33 _public prototype_ `DECLARE_DELEGATE_RetVal(const FPropertyBindingBindingCollection*, FOnGetBindingCollection);`
- L34 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnBindingClicked, bool bInIsStruct, const FPropertyBindingPath& InBindingPath);`
- L36 _public function_ `SLATE_BEGIN_ARGS(SBindingView)`
- L38 _public prototype_ `SLATE_EVENT(FOnGetBindingCollection, GetBindingCollection) SLATE_EVENT(FOnBindingClicked, OnBindingClicked) SLATE_ARGUMENT(TScriptInterface<const IPropertyBindingBindingCollectionOwner>, CollectionOwner) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — `UE_DEPRECATED(5.8, "Use CollectionOwner->GetEditorPropertyBindings() instead")`
- L45 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L48 _private prototype_ `void RequestRefresh();`
- L50 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FItem> Value, const TSharedRef<STableViewBase>& OwnerTable);`
- L53 _private member_ `FOnBindingClicked OnBindingClicked;`
- L55 _private member_ `TWeakInterfacePtr<const IPropertyBindingBindingCollectionOwner> CollectionOwner;`
- L56 _private member_ `TSharedPtr<SListView<TSharedPtr<FItem>>> ListView;`
- L57 _private member_ `TArray<TSharedPtr<FItem>> Values;`

#### struct `UE::PropertyBinding::SBindingView::FItem`  
`struct FItem`  
_L25-30_
- L27 _public member_ `FPropertyBindingPath SourcePath;`
- L28 _public member_ `FPropertyBindingPath TargetPath;`
- L29 _public member_ `TWeakObjectPtr<const UScriptStruct> FunctionNodeStruct;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PropertyBinding` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::PropertyBinding`)
- L33 _delegate_ `DECLARE_DELEGATE_RetVal(const FPropertyBindingBindingCollection*, FOnGetBindingCollection);`
- L34 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBindingClicked, bool bInIsStruct, const FPropertyBindingPath& InBindingPath);`
