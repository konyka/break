# Plugins / MusicEnvironmentEditor

- module root: `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironmentEditor`
- headers: 3; symbols: 24
- symbol kinds: class=2, delegate=1, function=2, macro=1, member=7, prototype=11
- PrivateDependencyModuleNames: Core, CoreUObject, MusicEnvironment, PropertyEditor, Slate, SlateCore

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironmentEditor/Private/Customization/FrameBasedTimeSignatureCustomization.h` (Private)


#### class `FFrameBasedTimeSignatureCustomization`  
`class FFrameBasedTimeSignatureCustomization : public IPropertyTypeCustomization`  
_L9-24_
- inherits: `IPropertyTypeCustomization`
- L12 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L17 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _private member_ `TSharedPtr<IPropertyHandle> MyPropertyHandle;`

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironmentEditor/Public/MusicEnvironmentEditorModule.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/MusicEnvironment/Source/MusicEnvironmentEditor/Public/Widgets/Input/SFrameBasedTimeSignatureInput.h` (Public)


#### class `SFrameBasedTimeSignatureInput`  
`class SFrameBasedTimeSignatureInput : public SCompoundWidget`  
_L11-68_
- inherits: `SCompoundWidget`
- L16 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnValueCommitted, const FFrameBasedTimeSignature&, ETextCommit::Type);` — Notification for numeric value committed
- L18 _public function_ `SLATE_BEGIN_ARGS(SFrameBasedTimeSignatureInput) : _Value(FFrameBasedTimeSignature()) , _MaxNumerator(DefaultMaxNumerator) , _MaxDenominator(DefaultMaxDenominator) , _IsEnabled(true) , _OnValueCommitted() , _Font(FCoreStyle::Get().GetFontStyle(TEXT("NormalFont")))`
- L27 _public prototype_ `SLATE_ATTRIBUTE(FFrameBasedTimeSignature, Value) SLATE_ATTRIBUTE(int32, MaxNumerator) SLATE_ATTRIBUTE(int32, MaxDenominator) SLATE_ATTRIBUTE(bool, IsEnabled) SLATE_EVENT(FOnValueCommitted, OnValueCommitted) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `FFrameBasedTimeSignature GetValue() const;`
- L45 _public prototype_ `void SetValue(const FFrameBasedTimeSignature& Value);`
- L50 _private member_ `static constexpr int32 DefaultMaxNumerator = 99;` — The default minimum fractional digits
- L53 _private member_ `static constexpr int32 DefaultMaxDenominator = 99;` — The default maximum fractional digits
- L55 _private member_ `TAttribute<FFrameBasedTimeSignature> ValueAttribute;`
- L56 _private member_ `TAttribute< int32 > MaxNumerator;`
- L57 _private member_ `TAttribute< int32 > MaxDenominator;`
- L58 _private member_ `FOnValueCommitted OnValueCommitted;`
- L60 _private prototype_ `FString GetValueAsString() const;`
- L61 _private prototype_ `FText GetValueAsText() const;`
- L63 _private prototype_ `static TOptional<FFrameBasedTimeSignature> ParseValueFromString(const FString& InString);`
- L65 _private prototype_ `void TextBox_OnTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L67 _private prototype_ `bool TextBox_VerifyTextChanged(const FText& InText, FText& OutErrorMessage) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUSICENVIRONMENTEDITOR_API`
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnValueCommitted, const FFrameBasedTimeSignature&, ETextCommit::Type);` — Notification for numeric value committed
