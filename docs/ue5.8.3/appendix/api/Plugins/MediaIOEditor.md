# Plugins / MediaIOEditor

- module root: `Plugins/Media/MediaIOFramework/Source/MediaIOEditor`
- headers: 14; symbols: 171
- symbol kinds: class=13, delegate=4, function=29, macro=8, member=36, prototype=79, struct=1, typedef=1
- PrivateDependencyModuleNames: AssetDefinition, Engine, MediaAssets, PropertyEditor
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, MediaIOCore, Slate, SlateCore, TimeManagement, UnrealEd

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Private/AssetDefinition/AssetDefinition_FileMediaOutput.h` (Private)


#### class `UAssetDefinition_FileMediaOutput`  
`class UAssetDefinition_FileMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Private/Customizations/MediaCaptureOptionsCustomization.h` (Private)


#### class `FMediaCaptureOptionsCustomization`  
`class FMediaCaptureOptionsCustomization : public IPropertyTypeCustomization`  
_L13-33_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for FMediaCaptureOptions. Automatically enables bForceAlphaToOneOnConversion when BackBufferReady capture phase is selected, and makes the option read-only while that phase is active.
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _private prototype_ `void OnCapturePhaseChanged();` — Called when CapturePhase changes; auto-sets bForceAlphaToOneOnConversion to true when BackBufferReady is selected.
- L26 _private prototype_ `bool IsForceAlphaEditable() const;` — Returns false when BackBufferReady is the active capture phase, making the force-alpha option read-only.
- L29 _private member_ `TSharedPtr<IPropertyHandle> CapturePhaseHandle;` — Handle to the CapturePhase property; watched to drive the alpha-forcing behavior.
- L32 _private member_ `TSharedPtr<IPropertyHandle> ForceAlphaHandle;` — Handle to the bForceAlphaToOneOnConversion property; toggled and gated based on the selected capture phase.

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Private/FileMediaOutputFactory.h` (Private)


#### class `UFileMediaOutputFactory`  
`class UFileMediaOutputFactory : public UFactory`  
_L15-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- desc: Implements a factory for UFileMediaOutput objects.
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Private/MediaIOEditorModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaIOEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaIOEditor, Log, All);`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/AssetDefinition/AssetDefinition_MediaOutput.h` (Public)


#### class `UAssetDefinition_MediaOutput`  
`class UAssetDefinition_MediaOutput : public UAssetDefinitionDefault`  
_L10-19_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FLinearColor GetAssetColor() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual bool CanImport() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Customizations/MediaIOConfigurationCustomization.h` (Public)


#### class `FMediaIOConfigurationCustomization`  
`class FMediaIOConfigurationCustomization : public FMediaIOCustomizationBase`  
_L14-41_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the FMediaIOConfiguration
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _protected prototype_ `virtual void OnCustomizeObjects(const TArray<UObject*>& InCustomizedObjects) override;`
- L24 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L25 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`
- L27 _private prototype_ `ECheckBoxState GetAutoCheckboxState() const;`
- L28 _private prototype_ `void SetAutoCheckboxState(ECheckBoxState CheckboxState);`
- L29 _private prototype_ `void OnSelectionChanged(FMediaIOConfiguration SelectedItem);`
- L30 _private prototype_ `FReply OnButtonClicked();`
- L31 _private prototype_ `bool ShowAdvancedColumns(FName ColumnName, const TArray<FMediaIOConfiguration>& UniquePermutationsForThisColumn) const;`
- L32 _private prototype_ `bool IsAutoDetected() const;`
- L33 _private prototype_ `void SetIsAutoDetected(bool Value);`
- L36 _private member_ `TWeakPtr<SWidget> PermutationSelector;`
- L37 _private member_ `FMediaIOConfiguration SelectedConfiguration;`
- L38 _private member_ `bool bAutoDetectFormat = false;`
- L40 _private member_ `TArray<TWeakObjectPtr<UObject>> Objects;` — List of customized objects.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Customizations/MediaIOCustomizationBase.h` (Public)


#### class `FMediaIOCustomizationBase`  
`class FMediaIOCustomizationBase : public IPropertyTypeCustomization`  
_L16-63_
- inherits: `IPropertyTypeCustomization`
- desc: Base implementation of different MediaIO details view customization
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L25 _protected function_ `template<class T> T* GetPropertyValueFromPropertyHandle()`
- L43 _protected function_ `template<class T> void AssignValue(const T& NewValue) const`
- L48 _protected prototype_ `virtual TAttribute<FText> GetContentText() = 0;`
- L49 _protected prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() = 0;`
- L50 _protected function_ `TSharedPtr<IPropertyHandle> GetMediaProperty() const`
- L51 _protected prototype_ `TArray<UObject*> GetCustomizedObjects() const;`
- L54 _protected function_ `virtual void OnCustomizeObjects(const TArray<UObject*>& InCustomizedObjects)` — Used to give a chance to the child implementations to get access to the customized objects as soon as possible.
- L56 _protected member_ `FName DeviceProviderName;`
- L59 _private prototype_ `void AssignValueImpl(const void* NewValue) const;`
- L62 _private member_ `TSharedPtr<IPropertyHandle> MediaProperty;` — Pointer to the property handle.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Customizations/MediaIODeviceCustomization.h` (Public)


#### class `FMediaIODeviceCustomization`  
`class FMediaIODeviceCustomization : public FMediaIOCustomizationBase`  
_L12-20_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the FMediaIODevice
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L19 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Customizations/MediaIOInputConfigurationCustomization.h` (Public)


#### class `FMediaIOInputConfigurationCustomization`  
`class FMediaIOInputConfigurationCustomization : public FMediaIOCustomizationBase`  
_L14-28_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the FMediaIOInputConfiguration
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L21 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`
- L23 _private prototype_ `void OnSelectionChanged(FMediaIOInputConfiguration SelectedItem);`
- L24 _private prototype_ `FReply OnButtonClicked() const;`
- L26 _private member_ `TWeakPtr<SWidget> PermutationSelector;`
- L27 _private member_ `FMediaIOInputConfiguration SelectedConfiguration;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Customizations/MediaIOOutputConfigurationCustomization.h` (Public)


#### class `FMediaIOOutputConfigurationCustomization`  
`class FMediaIOOutputConfigurationCustomization : public FMediaIOCustomizationBase`  
_L14-28_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the FMediaIOOutputConfiguration
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L21 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`
- L23 _private prototype_ `void OnSelectionChanged(FMediaIOOutputConfiguration SelectedItem);`
- L24 _private prototype_ `FReply OnButtonClicked() const;`
- L26 _private member_ `TWeakPtr<SWidget> PermutationSelector;`
- L27 _private member_ `FMediaIOOutputConfiguration SelectedConfiguration;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Customizations/MediaIOVideoTimecodeConfigurationCustomization.h` (Public)


#### class `FMediaIOVideoTimecodeConfigurationCustomization`  
`class FMediaIOVideoTimecodeConfigurationCustomization : public FMediaIOCustomizationBase`  
_L12-33_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the video timecode configuration.
- L15 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L18 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L19 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`
- L21 _private prototype_ `void OnSelectionChanged(FMediaIOVideoTimecodeConfiguration SelectedItem);`
- L22 _private prototype_ `FReply OnButtonClicked();`
- L23 _private prototype_ `ECheckBoxState GetAutoCheckboxState() const;`
- L24 _private prototype_ `void SetAutoCheckboxState(ECheckBoxState CheckboxState);`
- L25 _private prototype_ `bool ShowAdvancedColumns(FName ColumnName, const TArray<FMediaIOVideoTimecodeConfiguration>& UniquePermutationsForThisColumn) const;`
- L26 _private prototype_ `bool IsAutoDetected() const;`
- L27 _private prototype_ `void SetIsAutoDetected(bool Value);`
- L30 _private member_ `TWeakPtr<SWidget> PermutationSelector;`
- L31 _private member_ `FMediaIOVideoTimecodeConfiguration SelectedConfiguration;`
- L32 _private member_ `bool bAutoDetectFormat = false;`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/MediaIOPermutationsSelectorBuilder.h` (Public)


#### struct `FMediaIOPermutationsSelectorBuilder`  
`struct FMediaIOPermutationsSelectorBuilder`  
_L11-50_
- L13 _public member_ `static const FName NAME_DeviceIdentifier;`
- L14 _public member_ `static const FName NAME_TransportType;`
- L15 _public member_ `static const FName NAME_QuadType;`
- L16 _public member_ `static const FName NAME_Resolution;`
- L17 _public member_ `static const FName NAME_Standard;`
- L18 _public member_ `static const FName NAME_FrameRate;`
- L20 _public member_ `static const FName NAME_InputType;`
- L21 _public member_ `static const FName NAME_OutputType;`
- L22 _public member_ `static const FName NAME_KeyPortSource;`
- L23 _public member_ `static const FName NAME_OutputReference;`
- L24 _public member_ `static const FName NAME_SyncPortSource;`
- L26 _public prototype_ `static bool IdenticalProperty(FName ColumnName, const FMediaIOConnection& Left, const FMediaIOConnection& Right);`
- L27 _public prototype_ `static bool Less(FName ColumnName, const FMediaIOConnection& Left, const FMediaIOConnection& Right);`
- L28 _public prototype_ `static FText GetLabel(FName ColumnName, const FMediaIOConnection& Item);`
- L29 _public prototype_ `static FText GetTooltip(FName ColumnName, const FMediaIOConnection& Item);`
- L31 _public prototype_ `static bool IdenticalProperty(FName ColumnName, const FMediaIOMode& Left, const FMediaIOMode& Right);`
- L32 _public prototype_ `static bool Less(FName ColumnName, const FMediaIOMode& Left, const FMediaIOMode& Right);`
- L33 _public prototype_ `static FText GetLabel(FName ColumnName, const FMediaIOMode& Item);`
- L34 _public prototype_ `static FText GetTooltip(FName ColumnName, const FMediaIOMode& Item);`
- L36 _public prototype_ `static bool IdenticalProperty(FName ColumnName, const FMediaIOConfiguration& Left, const FMediaIOConfiguration& Right);`
- L37 _public prototype_ `static bool Less(FName ColumnName, const FMediaIOConfiguration& Left, const FMediaIOConfiguration& Right);`
- L38 _public prototype_ `static FText GetLabel(FName ColumnName, const FMediaIOConfiguration& Item);`
- L39 _public prototype_ `static FText GetTooltip(FName ColumnName, const FMediaIOConfiguration& Item);`
- L41 _public prototype_ `static bool IdenticalProperty(FName ColumnName, const FMediaIOInputConfiguration& Left, const FMediaIOInputConfiguration& Right);`
- L42 _public prototype_ `static bool Less(FName ColumnName, const FMediaIOInputConfiguration& Left, const FMediaIOInputConfiguration& Right);`
- L43 _public prototype_ `static FText GetLabel(FName ColumnName, const FMediaIOInputConfiguration& Item);`
- L44 _public prototype_ `static FText GetTooltip(FName ColumnName, const FMediaIOInputConfiguration& Item);`
- L46 _public prototype_ `static bool IdenticalProperty(FName ColumnName, const FMediaIOOutputConfiguration& Left, const FMediaIOOutputConfiguration& Right);`
- L47 _public prototype_ `static bool Less(FName ColumnName, const FMediaIOOutputConfiguration& Left, const FMediaIOOutputConfiguration& Right);`
- L48 _public prototype_ `static FText GetLabel(FName ColumnName, const FMediaIOOutputConfiguration& Item);`
- L49 _public prototype_ `static FText GetTooltip(FName ColumnName, const FMediaIOOutputConfiguration& Item);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAIOEDITOR_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Widgets/SMediaPermutationsSelector.h` (Public)


#### class `TMediaPermutationsSelectorBuilder`  
`template <typename ItemType> class TMediaPermutationsSelectorBuilder`  
_L54-61_
- L57 _public function_ `static bool IdenticalProperty(FName ColumnName, ItemType Left, ItemType Right)`
- L58 _public function_ `static bool Less(FName ColumnName, ItemType Left, ItemType Right)`
- L59 _public function_ `static FText GetLabel(FName ColumnName, ItemType Item)`
- L60 _public function_ `static FText GetTooltip(FName ColumnName, ItemType Item)`

#### class `SMediaPermutationsSelector`  
`template <typename ItemType, typename ItemBuilder = TMediaPermutationsSelectorBuilder<ItemType>> class SMediaPermutationsSelector : public SCompoundWidget`  
_L64-205_
- inherits: `SCompoundWidget`
- L67 _public typedef_ `using ThisClass = SMediaPermutationsSelector<ItemType, ItemBuilder>;`
- L70 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, ItemType );` — A delegate type invoked when the selection changes.
- L78 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsColumnVisible, FName , const TArray<ItemType>& );` — A delegate type invoked when we fill a column and wants to check if it should be visible. @param ColumnName the name of the ColumnName @param UniqueItemInColumn  List of items used to generate the column. Multiples items may be shared the value but only one will be in that list. @return true if the column should be visible
- L83 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGetExtensions, TArray<TSharedRef<SWidget>>& );` — A delegate called to add additional widgets to the left of the apply button.
- L128 _public function_ `SLATE_BEGIN_ARGS(ThisClass) : _ColumnHeight(200)`
- L134 _public prototype_ `SLATE_ARGUMENT(TArray<ItemType>, PermutationsSource) SLATE_ARGUMENT(TOptional<ItemType>, SelectedPermutation) SLATE_ATTRIBUTE(FOptionalSize, ColumnHeight) SLATE_ARGUMENT(TSharedPtr<SWidget>, OverrideButtonWidget) SLATE_EVENT(FOnClicked, OnButtonClicked) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnGetExtensions, OnGetExtensions) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Array of data items that we are displaying
- L152 _public prototype_ `static typename FColumn::FArguments Column(const FName& InColumnName);` — Create a column with a specified ColumnId
- L155 _public prototype_ `ItemType GetSelectedItem() const;` — Get a copy of the current selected item.
- L159 _private member_ `TArray<ItemType> PermutationsSource;` — Array of data items that we are displaying.
- L162 _private member_ `int32 SelectedPermutationIndex;` — Index of the selected item in ItemsSource. It will always be valid.
- L165 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate to invoke when selection changes.
- L168 _private member_ `TIndirectArray<FColumn> PropertyColumns;` — Columns information.
- L171 _private member_ `TSharedPtr<SHorizontalBox> ColumnContainer;` — Box used as container for the radio button menu.
- L174 _private prototype_ `void BuildColumns(int32 StartIndex);`
- L175 _private prototype_ `void ItemSelected(int32 UniqueItemIndexSelected, int32 ColumnSelected);`
- L176 _private prototype_ `TArray<int32> GenerateItemIndexes() const;`
- L177 _private prototype_ `bool IsColumnVisible(const FColumn& Column, const TArray<int32>& UniqueItemIndexes) const;`
- L180 _private function_ `bool IdenticalProperty(FName ColumnName, int32 LeftItemIndex, int32 RightItemIndex)`
- L187 _private function_ `bool Less(FName ColumnName, int32 LeftItemIndex, int32 RightItemIndex)`
- L194 _private function_ `FText GetLabel(FName ColumnName, int32 ItemIndex)`
- L200 _private function_ `FText GetTooltip(FName ColumnName, int32 ItemIndex)`

#### class `SMediaPermutationsSelector::FColumn`  
`class FColumn`  
_L87-125_
- desc: Describes a single column
- L90 _public function_ `SLATE_BEGIN_ARGS(FColumn)`
- L93 _public function_ `SLATE_ARGUMENT(FName, ColumnName) SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(FText, Tooltip) SLATE_EVENT(FIsColumnVisible, IsColumnVisible) SLATE_END_ARGS() FColumn(const FArguments& InArgs) : ColumnName(InArgs._ColumnName) , Label(InArgs._Label) , Tooltip(InArgs._Tooltip) , IsColumnVisible(InArgs._IsColumnVisible)` — A unique ID for this property, so that it can be saved and restored.
- L112 _public member_ `FName ColumnName;` — A unique ID for this property, so that it can be saved and restored.
- L115 _public member_ `TAttribute< FText > Label;` — Text to use as the Column header.
- L118 _public member_ `TAttribute< FText > Tooltip;` — Text to use as the Column tooltip.
- L121 _public member_ `TSharedPtr< SWidget > Widget;` — Widget created by this menu.
- L124 _public member_ `FIsColumnVisible IsColumnVisible;` — Delegate to invoke when build the column and check the visibility.

#### Free symbols / members of external scopes

- L70 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, ItemType );` — A delegate type invoked when the selection changes.
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsColumnVisible, FName , const TArray<ItemType>& );` — A delegate type invoked when we fill a column and wants to check if it should be visible. @param ColumnName the name of the ColumnName @param UniqueItemInColumn  List of items used to generate the column. Multiples items may be shared the value but only one will be in that list. @return true if the column should be visible
- L83 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetExtensions, TArray<TSharedRef<SWidget>>& );` — A delegate called to add additional widgets to the left of the apply button.

### `Plugins/Media/MediaIOFramework/Source/MediaIOEditor/Public/Widgets/SMediaPermutationsSelector.inl` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `template <typename ItemType, typename ItemBuilder> typename SMediaPermutationsSelector<ItemType, ItemBuilder>::FColumn::FArguments SMediaPermutationsSelector<ItemType, ItemBuilder>::Column(const FName& InColumnName)` (scope `SMediaPermutationsSelector`)
- L17 _function_ `template <typename ItemType, typename ItemBuilder> ItemType SMediaPermutationsSelector<ItemType, ItemBuilder>::GetSelectedItem() const` (scope `SMediaPermutationsSelector`)
- L23 _function_ `template <typename ItemType, typename ItemBuilder> void SMediaPermutationsSelector<ItemType, ItemBuilder>::Construct(const FArguments& InArgs)` (scope `SMediaPermutationsSelector`)
- L110 _function_ `template <typename ItemType, typename ItemBuilder> void SMediaPermutationsSelector<ItemType, ItemBuilder>::BuildColumns(int32 StartIndex)` (scope `SMediaPermutationsSelector`)
- L177 _function_ `UniqueItemsForColumnIndexes.Sort([this, ColumnName](int32 Left, int32 Right) { return Less(ColumnName, Left, Right); });` (scope `SMediaPermutationsSelector::BuildColumns`) — Sort the column items
- L188 _function_ `FExecuteAction::CreateLambda([this, UniqueItemIndex, ColumnIndex] { ItemSelected(UniqueItemIndex, ColumnIndex); }), FCanExecuteAction(), FIsActionChecked::CreateLambda([this, UniqueItemIndex, ColumnName] { return IdenticalProperty(ColumnName, SelectedPermutationIndex, UniqueItemIndex); }) ), NAME_None, EUserInterfaceActionType::RadioButton );` (scope `SMediaPermutationsSelector::BuildColumns`)
- L199 _function_ `.Visibility_Lambda([this, Column, UniqueItemsForColumnIndexes]() { return IsColumnVisible(Column, UniqueItemsForColumnIndexes) ? EVisibility::Visible : EVisibility::Collapsed; }) + SVerticalBox::Slot() .AutoHeight() .HAlign(HAlign_Left) .Padding(2, 0, 5, 0) [ SNew(STextBlock) .Text(Column.Label) ] + SVerticalBox::Slot() .FillHeight(1.f) [ MenuBuilder.MakeWidget() ];` (scope `SMediaPermutationsSelector::BuildColumns`)
- L224 _function_ `template <typename ItemType, typename ItemBuilder> void SMediaPermutationsSelector<ItemType, ItemBuilder>::ItemSelected(int32 UniqueItemIndex, int32 ColumnIndex)` (scope `SMediaPermutationsSelector`)
- L311 _function_ `template <typename ItemType, typename ItemBuilder> TArray<int32> SMediaPermutationsSelector<ItemType, ItemBuilder>::GenerateItemIndexes() const` (scope `SMediaPermutationsSelector`)
- L324 _function_ `template <typename ItemType, typename ItemBuilder> bool SMediaPermutationsSelector<ItemType, ItemBuilder>::IsColumnVisible(const FColumn& Column, const TArray<int32>& UniqueItemIndexes) const` (scope `SMediaPermutationsSelector`)
