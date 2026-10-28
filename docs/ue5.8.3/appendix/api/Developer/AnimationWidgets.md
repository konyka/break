# Developer / AnimationWidgets

- module root: `Source/Developer/AnimationWidgets`
- headers: 2; symbols: 144
- symbol kinds: class=2, delegate=28, enum=3, enumerator=23, function=40, member=14, namespace=3, prototype=28, typedef=3
- PrivateDependencyModuleNames: CoreUObject, Engine, GraphEditor, PropertyEditor, UnrealEd
- PublicDependencyModuleNames: AnimationCore, Core, InputCore, Slate, SlateCore, ToolWidgets

### `Source/Developer/AnimationWidgets/Public/SAdvancedRotationInputBox.h` (Public)


#### enum `ESlateRotationRepresentation::Type`  
`enum Type : int`  
_L21-33_
- L23 _public enumerator_ `EulerXYZ`
- L24 _public enumerator_ `EulerXZY`
- L25 _public enumerator_ `EulerYXZ`
- L26 _public enumerator_ `EulerYZX`
- L27 _public enumerator_ `EulerZXY`
- L28 _public enumerator_ `EulerZYX`
- L29 _public enumerator_ `Rotator`
- L30 _public enumerator_ `Quaternion`
- L31 _public enumerator_ `AxisAndAngle`
- L32 _public enumerator_ `Max`

#### enum `ESlateTransformSubComponent::Type`  
`enum Type : int`  
_L38-49_
- L40 _public enumerator_ `X`
- L41 _public enumerator_ `Y`
- L42 _public enumerator_ `Z`
- L43 _public enumerator_ `W`
- L44 _public enumerator_ `Angle`
- L45 _public enumerator_ `Pitch`
- L46 _public enumerator_ `Yaw`
- L47 _public enumerator_ `Roll`
- L48 _public enumerator_ `Max`

#### class `SAdvancedRotationInputBox`  
`template<typename NumericType = FVector::FReal> class SAdvancedRotationInputBox : public SCompoundWidget`  
_L56-981_
- inherits: `SCompoundWidget`
- desc: Generic Rotation Slate control
- L60 _public typedef_ `typedef SNumericVectorInputBox<NumericType, UE::Math::TVector<NumericType>, 3> SNumericVectorInputBox3;`
- L61 _public typedef_ `typedef SNumericVectorInputBox<NumericType, UE::Math::TVector4<NumericType>, 4> SNumericVectorInputBox4;`
- L64 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRotatorChanged, FRotator);` — Delegate for notification for a rotator value change
- L67 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRotatorCommitted, FRotator, ETextCommit::Type);` — Delegate for notification for a rotator value commit
- L70 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnQuaternionChanged, FQuat);` — Delegate for notification for a quaternion value change
- L73 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnQuaternionCommitted, FQuat, ETextCommit::Type);` — Delegate for notification for a quaternion value commit
- L76 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<NumericType>, FOnGetNumericValue, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve a numerictype value
- L79 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnNumericValueChanged, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for numerictype value change
- L82 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnNumericValueCommitted, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType, ETextCommit::Type);` — Notification for numerictype value committed
- L85 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnBeginSliderMovement, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Notification for begin slider movement
- L88 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnEndSliderMovement, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for end slider movement
- L91 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(ECheckBoxState, FOnGetToggleChecked, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve toggle checkstate
- L94 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnToggleChanged, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, ECheckBoxState);` — Notification for toggle checkstate change
- L96 _public function_ `SLATE_BEGIN_ARGS( SAdvancedRotationInputBox ) : _Representation(ESlateRotationRepresentation::Rotator) , _bColorAxisLabels(true) , _Font(FAppStyle::Get().GetFontStyle("NormalFont")) , _AllowSpin(true) , _DisplayToggle( false ) , _TogglePadding( FMargin( 1.f,0.f,1.f,0.f ) ) , _PreventThrottling(false)`
- L107 _public function_ `SLATE_ATTRIBUTE( ESlateRotationRepresentation::Type, Representation ) SLATE_ATTRIBUTE( TOptional<FRotator>, Rotator ) SLATE_EVENT( FOnRotatorChanged, OnRotatorChanged ) SLATE_EVENT( FOnRotatorCommitted, OnRotatorCommitted ) SLATE_ATTRIBUTE( TOptional<FQuat>, Quaternion ) SLATE_EVENT( FOnQuaternionChanged, OnQuaternionChanged ) SLATE_EVENT( FOnQuaternionCommitted, OnQuaternionCommitted ) SLATE_EVENT( FOnGetNumericValue, OnGetNumericValue ) SLATE_EVENT( FOnNumericValueChanged, OnNumericValueChanged ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericValueCommitted ) SLATE_EVENT(FOnBeginSliderMovement, OnBeginSliderMovement) SLATE_EVENT(FOnEndSliderMovement, OnEndSliderMovement) SLATE_ARGUMENT( bool, bColorAxisLabels ) SLATE_ATTRIBUTE( FSlateFontInfo, Font )` — Representation of the rotation
- L423 _public function_ `static bool IsValidComponent(ESlateRotationRepresentation::Type InRepresentation, ESlateTransformSubComponent::Type InSubComponent)`
- L493 _private member_ `TAttribute<ESlateRotationRepresentation::Type> Representation;`
- L494 _private member_ `TAttribute<TOptional<FRotator>> Rotator;`
- L495 _private member_ `FOnRotatorChanged OnRotatorChanged;`
- L496 _private member_ `FOnRotatorCommitted OnRotatorCommitted;`
- L497 _private member_ `TAttribute<TOptional<FQuat>> Quaternion;`
- L498 _private member_ `FOnQuaternionChanged OnQuaternionChanged;`
- L499 _private member_ `FOnQuaternionCommitted OnQuaternionCommitted;`
- L500 _private member_ `FOnGetNumericValue OnGetNumericValue;`
- L501 _private member_ `FOnNumericValueChanged OnNumericValueChanged;`
- L502 _private member_ `FOnNumericValueCommitted OnNumericValueCommitted;`
- L503 _private member_ `FOnBeginSliderMovement OnBeginSliderMovement;`
- L504 _private member_ `FOnEndSliderMovement OnEndSliderMovement;`
- L505 _private member_ `FOnGetToggleChecked OnGetToggleChecked;`
- L506 _private member_ `FOnToggleChanged OnToggleChanged;`
- L508 _private function_ `TOptional<NumericType> HandleGetNumericValue(ESlateTransformSubComponent::Type InSubComponent) const`
- L644 _private function_ `bool GetRotatorAndQuat(TOptional<FRotator>& Rot, TOptional<FQuat> &Quat) const`
- L677 _private function_ `bool ApplyNumericValueChangeToRotatorAndQuat(TOptional<FRotator>& Rot, TOptional<FQuat> &Quat, NumericType InValue, ESlateTransformSubComponent::Type InSubComponent) const`
- L826 _private function_ `void HandleOnNumericValueChanged(NumericType InValue, ESlateTransformSubComponent::Type InSubComponent)`
- L855 _private function_ `void HandleOnNumericValueCommitted(NumericType InValue, ETextCommit::Type InCommitType, ESlateTransformSubComponent::Type InSubComponent)`
- L883 _private function_ `ECheckBoxState HandleGetToggleChecked(ESlateTransformSubComponent::Type InSubComponent) const`
- L896 _private function_ `void HandleOnToggleChanged(ECheckBoxState InValue, ESlateTransformSubComponent::Type InSubComponent)`
- L908 _private function_ `void HandleOnBeginSliderMovement(ESlateTransformSubComponent::Type InSubComponent)`
- L920 _private function_ `void HandleOnEndSliderMovement(NumericType InValue, ESlateTransformSubComponent::Type InSubComponent)`
- L932 _private function_ `EVisibility IsRotatorInputBoxVisible() const`
- L938 _private function_ `EVisibility IsEulerInputBoxVisible() const`
- L956 _private function_ `EVisibility IsQuaternionInputBoxVisible() const`
- L969 _private function_ `EVisibility IsAxisAndAngleInputBoxVisible() const`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ESlateRotationRepresentation`
- L36 _namespace_ `namespace ESlateTransformSubComponent`
- L64 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRotatorChanged, FRotator);` — Delegate for notification for a rotator value change
- L67 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRotatorCommitted, FRotator, ETextCommit::Type);` — Delegate for notification for a rotator value commit
- L70 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQuaternionChanged, FQuat);` — Delegate for notification for a quaternion value change
- L73 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQuaternionCommitted, FQuat, ETextCommit::Type);` — Delegate for notification for a quaternion value commit
- L76 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<NumericType>, FOnGetNumericValue, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve a numerictype value
- L79 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnNumericValueChanged, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for numerictype value change
- L82 _delegate_ `DECLARE_DELEGATE_FourParams(FOnNumericValueCommitted, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType, ETextCommit::Type);` — Notification for numerictype value committed
- L85 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBeginSliderMovement, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Notification for begin slider movement
- L88 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnEndSliderMovement, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for end slider movement
- L91 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(ECheckBoxState, FOnGetToggleChecked, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve toggle checkstate
- L94 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnToggleChanged, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, ECheckBoxState);` — Notification for toggle checkstate change
- L394 _function_ `` (scope `SAdvancedRotationInputBox::SLATE_ATTRIBUTE`)

### `Source/Developer/AnimationWidgets/Public/SAdvancedTransformInputBox.h` (Public)


#### enum `ESlateTransformComponent::Type`  
`enum Type : int`  
_L29-35_
- L31 _public enumerator_ `Location`
- L32 _public enumerator_ `Rotation`
- L33 _public enumerator_ `Scale`
- L34 _public enumerator_ `Max`

#### class `SAdvancedTransformInputBox`  
`template<typename TransformType = FTransform, typename NumericType = FVector::FReal> class SAdvancedTransformInputBox : public SCompoundWidget`  
_L42-1671_
- inherits: `SCompoundWidget`
- desc: Generic Transform Slate control
- L46 _public typedef_ `typedef SNumericVectorInputBox<NumericType, UE::Math::TVector<NumericType>, 3> SNumericVectorInputBox3;`
- L49 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTransformChanged, TransformType);` — Delegate for notification for a transform value change
- L52 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnTransformCommitted, TransformType, ETextCommit::Type);` — Delegate for notification for a transform value commit
- L55 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TOptional<NumericType>, FOnGetNumericValue, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve a numerictype value
- L58 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnNumericValueChanged, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for numerictype value change
- L61 _public prototype_ `DECLARE_DELEGATE_FiveParams(FOnNumericValueCommitted, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType, ETextCommit::Type);` — Notification for numerictype value committed
- L64 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnBeginSliderMovement, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Notification for begin slider movement
- L67 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnEndSliderMovement, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for end slider movement
- L70 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetIsComponentRelative, ESlateTransformComponent::Type);` — Delegate to retrieve relative / world state
- L73 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnIsComponentRelativeChanged, ESlateTransformComponent::Type, bool );` — Notification for a relative / world state change
- L76 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRotationRepresentationChanged, ESlateRotationRepresentation::Type);` — Notification for the rotation representation change
- L79 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnScaleLockChanged, bool );` — Notification for the scale lock change
- L82 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(ECheckBoxState, FOnGetToggleChecked, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve toggle checkstate
- L85 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnToggleChanged, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, ECheckBoxState);` — Notification for toggle checkstate change
- L88 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCopyToClipboard, ESlateTransformComponent::Type);` — Delegate to fire when a row or the whole transform (type == max) is being copied to the clipboard
- L91 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPasteFromClipboard, ESlateTransformComponent::Type);` — Delegate to fire when a row or the whole transform (type == max) is being pasted into from the clipboard
- L94 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnResetToDefault, ESlateTransformComponent::Type);` — Delegate to fire when a row or the whole transform (type == max) needs to be reset to its default
- L97 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FDiffersFromDefault, ESlateTransformComponent::Type);` — Delegate to determine if the row or the whole transform (type == max) differs from its default
- L99 _public function_ `SLATE_BEGIN_ARGS( SAdvancedTransformInputBox ) : _ConstructLocation(true) , _ConstructRotation(true) , _ConstructScale(true) , _UseQuaternionForRotation(false) , _RotationRepresentation(TSharedPtr<ESlateRotationRepresentation::Type>( new ESlateRotationRepresentation::Type(ESlateRotationRepresentation::Rotator))) , _bColorAxisLabels(true) , _ShowInlineLabels(false) , _LocationLabel(NSLOCTEXT("SAdvancedTransformInputBox", "Location", "Location")) , _RotationLabel(NSLOCTEXT("SAdvancedTransformInputBox", "Rotation", "Rotation")) , _ScaleLabel(NSLOCTEXT("SAdvancedTransformInputBox", "Scale", "Scale")) , _LabelPadding( FMargin( 0.f,0.f,6.f,0.f ) ) , _Font(FAppStyle::Get().GetFontStyle("NormalFont")) , _AllowSpin(true) , _LocationSpinDelta(0.01f) , _ScaleSpinDelta(0.001f) , _AllowEditRotationRepresentation(true) , _DisplayScaleLock(true) , _IsScaleLocked(TSharedPtr<bool>(new bool(false))) , _DisplayRelativeWorld(false) , _DisplayToggle( false ) , _TogglePadding( FMargin( 1.f,0.f,1.f,0.f ) ) , _PreventThrottling(false)`
- L125 _public function_ `SLATE_ARGUMENT( bool, ConstructLocation ) SLATE_ARGUMENT( bool, ConstructRotation ) SLATE_ARGUMENT( bool, ConstructScale ) SLATE_ARGUMENT( bool, UseQuaternionForRotation ) SLATE_ATTRIBUTE( TOptional<TransformType>, Transform ) SLATE_EVENT( FOnTransformChanged, OnTransformChanged ) SLATE_EVENT( FOnTransformCommitted, OnTransformCommitted ) SLATE_ARGUMENT( TSharedPtr<ESlateRotationRepresentation::Type>, RotationRepresentation ) SLATE_EVENT( FOnRotationRepresentationChanged, OnRotationRepresentationChanged ) SLATE_EVENT( FOnGetNumericValue, OnGetNumericValue ) SLATE_EVENT( FOnNumericValueChanged, OnNumericValueChanged ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericValueCommitted ) SLATE_EVENT(FOnBeginSliderMovement, OnBeginSliderMovement) SLATE_EVENT(FOnEndSliderMovement, OnEndSliderMovement)` — Whether or not to construct the location component
- L286 _public function_ `static TSharedRef<SWidget> ConstructWidget(const FArguments& InArgs, ESlateTransformComponent::Type InComponent)` — Construct an input widget
- L912 _public function_ `static TSharedRef<SWidget> ConstructLabel(const FArguments& InArgs, ESlateTransformComponent::Type InComponent)` — Constructs a label widget
- L1042 _public function_ `static TSharedRef<SWidget> ConstructScaleLockWidget(const FArguments& InArgs, ESlateTransformComponent::Type InComponent )` — Constructs a relative / world switcher button
- L1084 _public function_ `static const FSlateBrush* GetScaleLockIcon(bool bIsLocked)` — Gather the icon for scale locked / unlocked
- L1092 _public function_ `static TSharedRef<SWidget> ConstructRelativeWorldWidget(const FArguments& InArgs, ESlateTransformComponent::Type InComponent)` — Constructs a relative / world switcher button
- L1179 _public function_ `static const FSlateIcon& GetRelativeWorldIcon(bool bRelative)` — Gather the icon for relative world
- L1195 _public function_ `static IDetailGroup& ConstructDetailGroup(IDetailCategoryBuilder& InBuilder, FName GroupName, const FText& LocalizedDisplayName)`
- L1200 _public function_ `static IDetailGroup& ConstructDetailGroup(IDetailChildrenBuilder& InBuilder, FName GroupName, const FText& LocalizedDisplayName)`
- L1205 _public function_ `static void ConfigureComponentWidgetRow( FDetailWidgetRow& WidgetRow, ESlateTransformComponent::Type InComponent, typename SAdvancedTransformInputBox<TransformType>::FArguments WidgetArgs)`
- L1271 _public function_ `static void ConfigureHeader( FDetailWidgetRow& HeaderRow, const FText& InLabel, const FText& InTooltip, typename SAdvancedTransformInputBox<TransformType>::FArguments WidgetArgs, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>() )`
- L1298 _public function_ `template<typename BuilderType = IDetailCategoryBuilder> static FDetailWidgetRow& ConstructGroupedTransformRows( BuilderType& InBuilder, const FText& InLabel, const FText& InTooltip, typename SAdvancedTransformInputBox<TransformType>::FArguments WidgetArgs, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>() )`
- L1333 _public function_ `static const TArray<FText>& GetRotationRepresentationLabels()`
- L1351 _public function_ `static void ConstrainScale( int32 ComponentIndex, UE::Math::TVector<NumericType> OldValue, UE::Math::TVector<NumericType>& NewValue, TAttribute<bool> ConstrainComponents)`
- L1371 _public function_ `static TOptional<NumericType> GetNumericValueFromTransform( const TransformType& Transform, ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent)`
- L1489 _public function_ `static void ApplyNumericValueChange( TransformType& Transform, NumericType Value, ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent)`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace ESlateTransformComponent`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTransformChanged, TransformType);` — Delegate for notification for a transform value change
- L52 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnTransformCommitted, TransformType, ETextCommit::Type);` — Delegate for notification for a transform value commit
- L55 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TOptional<NumericType>, FOnGetNumericValue, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve a numerictype value
- L58 _delegate_ `DECLARE_DELEGATE_FourParams(FOnNumericValueChanged, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for numerictype value change
- L61 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnNumericValueCommitted, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType, ETextCommit::Type);` — Notification for numerictype value committed
- L64 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnBeginSliderMovement, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Notification for begin slider movement
- L67 _delegate_ `DECLARE_DELEGATE_FourParams(FOnEndSliderMovement, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, NumericType);` — Notification for end slider movement
- L70 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetIsComponentRelative, ESlateTransformComponent::Type);` — Delegate to retrieve relative / world state
- L73 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnIsComponentRelativeChanged, ESlateTransformComponent::Type, bool );` — Notification for a relative / world state change
- L76 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRotationRepresentationChanged, ESlateRotationRepresentation::Type);` — Notification for the rotation representation change
- L79 _delegate_ `DECLARE_DELEGATE_OneParam(FOnScaleLockChanged, bool );` — Notification for the scale lock change
- L82 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(ECheckBoxState, FOnGetToggleChecked, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type);` — Delegate to retrieve toggle checkstate
- L85 _delegate_ `DECLARE_DELEGATE_FourParams(FOnToggleChanged, ESlateTransformComponent::Type, ESlateRotationRepresentation::Type, ESlateTransformSubComponent::Type, ECheckBoxState);` — Notification for toggle checkstate change
- L88 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCopyToClipboard, ESlateTransformComponent::Type);` — Delegate to fire when a row or the whole transform (type == max) is being copied to the clipboard
- L91 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPasteFromClipboard, ESlateTransformComponent::Type);` — Delegate to fire when a row or the whole transform (type == max) is being pasted into from the clipboard
- L94 _delegate_ `DECLARE_DELEGATE_OneParam(FOnResetToDefault, ESlateTransformComponent::Type);` — Delegate to fire when a row or the whole transform (type == max) needs to be reset to its default
- L97 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FDiffersFromDefault, ESlateTransformComponent::Type);` — Delegate to determine if the row or the whole transform (type == max) differs from its default
- L319 _function_ `` (scope `SAdvancedTransformInputBox::ConstructWidget`)
- L929 _function_ `` (scope `SAdvancedTransformInputBox::ConstructLabel`)
- L940 _function_ `` (scope `SAdvancedTransformInputBox::ConstructLabel::__anon3deb66933102`)
- L1056 _function_ `` (scope `SAdvancedTransformInputBox::ConstructScaleLockWidget`)
- L1130 _function_ `` (scope `SAdvancedTransformInputBox::ConstructRelativeWorldWidget`)
- L1215 _function_ `` (scope `SAdvancedTransformInputBox::ConfigureComponentWidgetRow`)
