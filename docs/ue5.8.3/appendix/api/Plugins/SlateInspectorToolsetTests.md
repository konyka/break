# Plugins / SlateInspectorToolsetTests

- module root: `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolsetTests`
- headers: 1; symbols: 16
- symbol kinds: class=1, function=1, member=13, prototype=1
- PrivateDependencyModuleNames: CQTest, Core, CoreUObject, Engine, InputCore, Slate, SlateCore, SlateInspectorToolset

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolsetTests/Private/SlateInspectorToolsetTestPanel.h` (Private)


#### class `SSlateInspectorToolsetTestPanel`  
`class SSlateInspectorToolsetTestPanel : public SCompoundWidget`  
_L19-50_
- inherits: `SCompoundWidget`
- desc: A widget panel containing one of each common widget type. Used by SlateInspectorToolset automation tests to exercise snapshot, observer, and input simulation tools against known widgets.
- L23 _public function_ `SLATE_BEGIN_ARGS(SSlateInspectorToolsetTestPanel)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public member_ `int32 ButtonClickCount = 0;` — Button
- L30 _public member_ `int32 SecondButtonClickCount = 0;`
- L33 _public member_ `TSharedPtr<SEditableTextBox> TextBox;` — Text input
- L34 _public member_ `TSharedPtr<SMultiLineEditableTextBox> MultiLineTextBox;`
- L35 _public member_ `TSharedPtr<SSearchBox> SearchBox;`
- L38 _public member_ `TSharedPtr<SCheckBox> CheckBox;` — Toggle
- L41 _public member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;` — Combobox
- L42 _public member_ `TArray<TSharedPtr<FString>> ComboOptions;`
- L43 _public member_ `TSharedPtr<FString> SelectedComboOption;`
- L46 _public member_ `TSharedPtr<SSlider> Slider;` — Slider / SpinBox
- L47 _public member_ `float SliderValue = 0.0f;`
- L48 _public member_ `TSharedPtr<SSpinBox<float>> SpinBox;`
- L49 _public member_ `float SpinBoxValue = 0.0f;`
