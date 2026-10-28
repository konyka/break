# Plugins / ActorModifierEditor

- module root: `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor`
- headers: 8; symbols: 69
- symbol kinds: class=9, delegate=4, function=6, member=14, namespace=3, prototype=33
- PrivateDependencyModuleNames: ActorModifier, ActorModifierCore, ActorModifierLayout, ClonerEffectorEditor, CoreUObject, Engine, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/ActorModifierEditorModule.h` (Private)


#### class `FActorModifierEditorModule`  
`class FActorModifierEditorModule : public IModuleInterface`  
_L8-17_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `TArray<FName> RegisteredCustomizations;`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/Customizations/ActorModifierEditorActorComponentClassPropertyTypeCustomization.h` (Private)


#### class `UE::ActorModifierEditor::Private::FActorModifierEditorActorComponentClassPropertyTypeIdentifier`  
`class FActorModifierEditorActorComponentClassPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L20-28_
- inherits: `IPropertyTypeIdentifier`
- desc: Only allow property customization with class metadata specifier
- L23 _public member_ `static const FLazyName MetadataSpecifier;`
- L26 _public prototype_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override;`

#### class `UE::ActorModifierEditor::Private::FActorModifierEditorActorComponentClassPropertyTypeCustomization`  
`class FActorModifierEditorActorComponentClassPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L33-48_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for an actor property to only show filtered actor based on component class
- L36 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L39 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L40 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L44 _protected prototype_ `bool OnFilterActorByComponentClass(const AActor* InActor);`
- L46 _protected member_ `TSubclassOf<UActorComponent> ComponentClass;`
- L47 _protected member_ `TSharedPtr<FCEEditorClonerCustomActorPickerNodeBuilder> ActorPickerNodeBuilder;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ActorModifierEditor` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::ActorModifierEditor`)

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/Customizations/ActorModifierEditorAnchorAlignmentPropertyTypeCustomization.h` (Private)


#### class `FActorModifierEditorAnchorAlignmentPropertyTypeCustomization`  
`class FActorModifierEditorAnchorAlignmentPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L21-37_
- inherits: `IPropertyTypeCustomization`
- desc: Motion Design Anchor Alignment Customization Shows a grid of buttons for setting anchor alignment in the following layout: [HLeft ] [HCenter] [HRight ] [VTop  ] [VCenter] [VBottom] [DFront] [DCenter] [DBack  ]
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L32 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L34 _private prototype_ `FActorModifierAnchorAlignment GetAnchors() const;`
- L36 _private prototype_ `void OnAnchorChanged(const FActorModifierAnchorAlignment NewAnchor) const;`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/Customizations/SActorModifierEditorAnchorAlignment.h` (Private)


#### class `SActorModifierEditorAnchorAlignment`  
`class SActorModifierEditorAnchorAlignment : public SCompoundWidget`  
_L17-47_
- inherits: `SCompoundWidget`
- desc: Motion Design Anchor Alignment Widget that holds holds axis alignment widgets for Left/Center/Right, Top/Center/Bottom, and Front/Center/Back. One alignment button set per axis row (Horizontal, Vertical, Depth).
- L20 _public function_ `DECLARE_DELEGATE_OneParam(FOnAnchorChanged, FActorModifierAnchorAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorAnchorAlignment)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(FActorModifierAnchorAlignment, Anchors) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnAnchorChanged, OnAnchorChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `EVisibility GetHorizontalVisibility() const;`
- L32 _public prototype_ `EVisibility GetVerticalVisibility() const;`
- L33 _public prototype_ `EVisibility GetDepthVisibility() const;`
- L35 _public prototype_ `EActorModifierHorizontalAlignment GetHorizontalAlignment() const;`
- L36 _public prototype_ `EActorModifierVerticalAlignment GetVerticalAlignment() const;`
- L37 _public prototype_ `EActorModifierDepthAlignment GetDepthAlignment() const;`
- L39 _public prototype_ `void OnHorizontalAlignmentChanged(const EActorModifierHorizontalAlignment InAlignment);`
- L40 _public prototype_ `void OnVerticalAlignmentChanged(const EActorModifierVerticalAlignment InAlignment);`
- L41 _public prototype_ `void OnDepthAlignmentChanged(const EActorModifierDepthAlignment InAlignment);`
- L44 _protected member_ `TAttribute<FActorModifierAnchorAlignment> Anchors;`
- L46 _protected member_ `FOnAnchorChanged OnAnchorChanged;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAnchorChanged, FActorModifierAnchorAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorAnchorAlignment) {} SLATE_ATTRIBUTE(FActorModifierAnchorAlignment, Anchors) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnAnchorChanged, OnAnchorChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/Customizations/SActorModifierEditorDepthAlignment.h` (Private)


#### class `SActorModifierEditorDepthAlignment`  
`class SActorModifierEditorDepthAlignment : public SCompoundWidget`  
_L15-37_
- inherits: `SCompoundWidget`
- desc: Motion Design Depth Axis Alignment Widget that holds three buttons for either Front, Center, and Back.
- L18 _public function_ `DECLARE_DELEGATE_OneParam(FOnDepthAlignmentChanged, EActorModifierDepthAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorDepthAlignment)`
- L22 _public prototype_ `SLATE_ATTRIBUTE(EActorModifierDepthAlignment, Alignment) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnDepthAlignmentChanged, OnAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _protected member_ `TAttribute<EActorModifierDepthAlignment> Alignment;`
- L32 _protected member_ `FOnDepthAlignmentChanged OnAlignmentChanged;`
- L34 _protected prototype_ `EActorModifierDepthAlignment GetCurrentAlignment() const;`
- L36 _protected prototype_ `void OnCurrentAlignmentChanged(const EActorModifierDepthAlignment NewAlignment);`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDepthAlignmentChanged, EActorModifierDepthAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorDepthAlignment) {} SLATE_ATTRIBUTE(EActorModifierDepthAlignment, Alignment) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnDepthAlignmentChanged, OnAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/Customizations/SActorModifierEditorHorizontalAlignment.h` (Private)


#### class `SActorModifierEditorHorizontalAlignment`  
`class SActorModifierEditorHorizontalAlignment : public SCompoundWidget`  
_L15-37_
- inherits: `SCompoundWidget`
- desc: Avalanche Horizontal Axis Alignment Widget that holds three buttons for either Left, Center, and Right.
- L18 _public function_ `DECLARE_DELEGATE_OneParam(FOnHorizontalAlignmentChanged, EActorModifierHorizontalAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorHorizontalAlignment)`
- L22 _public prototype_ `SLATE_ATTRIBUTE(EActorModifierHorizontalAlignment, Alignment) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnHorizontalAlignmentChanged, OnAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _protected member_ `TAttribute<EActorModifierHorizontalAlignment> Alignment;`
- L32 _protected member_ `FOnHorizontalAlignmentChanged OnAlignmentChanged;`
- L34 _protected prototype_ `EActorModifierHorizontalAlignment GetCurrentAlignment() const;`
- L36 _protected prototype_ `void OnCurrentAlignmentChanged(const EActorModifierHorizontalAlignment NewAlignment);`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHorizontalAlignmentChanged, EActorModifierHorizontalAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorHorizontalAlignment) {} SLATE_ATTRIBUTE(EActorModifierHorizontalAlignment, Alignment) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnHorizontalAlignmentChanged, OnAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Private/Customizations/SActorModifierEditorVerticalAlignment.h` (Private)


#### class `SActorModifierEditorVerticalAlignment`  
`class SActorModifierEditorVerticalAlignment : public SCompoundWidget`  
_L15-36_
- inherits: `SCompoundWidget`
- desc: Motion Design Vertical Axis Alignment Widget that holds three buttons for either Top, Center, and Bottom.
- L18 _public function_ `DECLARE_DELEGATE_OneParam(FOnVerticalAlignmentChanged, EActorModifierVerticalAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorVerticalAlignment)`
- L22 _public prototype_ `SLATE_ATTRIBUTE(EActorModifierVerticalAlignment, Alignment) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnVerticalAlignmentChanged, OnAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _protected member_ `TAttribute<EActorModifierVerticalAlignment> Alignment;`
- L31 _protected member_ `FOnVerticalAlignmentChanged OnAlignmentChanged;`
- L33 _protected prototype_ `EActorModifierVerticalAlignment GetCurrentAlignment() const;`
- L35 _protected prototype_ `void OnCurrentAlignmentChanged(const EActorModifierVerticalAlignment NewAlignment);`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVerticalAlignmentChanged, EActorModifierVerticalAlignment) SLATE_BEGIN_ARGS(SActorModifierEditorVerticalAlignment) {} SLATE_ATTRIBUTE(EActorModifierVerticalAlignment, Alignment) SLATE_ATTRIBUTE(FMargin, UniformPadding) SLATE_EVENT(FOnVerticalAlignmentChanged, OnAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierEditor/Public/Styles/ActorModifierEditorStyle.h` (Public)


#### class `FActorModifierEditorStyle`  
`class FActorModifierEditorStyle final : public FSlateStyleSet`  
_L10-28_
- inherits: `FSlateStyleSet`
- L13 _public function_ `static FActorModifierEditorStyle& Get()`
- L19 _public prototype_ `FActorModifierEditorStyle();`
- L22 _public prototype_ `static const FSlateColor& GetModifierCategoryColor(FName CategoryName);`
- L25 _private prototype_ `void OnModifierClassRegistered(const FActorModifierCoreMetadata& InMetadata);`
- L27 _private member_ `static TMap<FName, FSlateColor> ModifierCategoriesColors;`
