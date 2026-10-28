# Runtime / InputCore

- module root: `Source/Runtime/InputCore`
- headers: 11; symbols: 621
- symbol kinds: class=3, delegate=1, enum=8, enumerator=71, function=50, member=395, namespace=3, prototype=71, struct=14, typedef=5
- PrivateIncludePathModuleNames: ApplicationCore, SDL3
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/InputCore/Classes/InputCoreTypes.h` (Public)


#### enum `EControllerHand`  
`enum class EControllerHand : uint8`  
_L16-38_
- reflection: `UENUM(BlueprintType)`
- desc: Defines the controller hands for tracking.  Could be expanded, as needed, to facilitate non-handheld controllers
- L18 _public enumerator_ `Left`
- L19 _public enumerator_ `Right`
- L20 _public enumerator_ `AnyHand`
- L21 _public enumerator_ `Pad`
- L22 _public enumerator_ `ExternalCamera`
- L23 _public enumerator_ `Gun`
- L24 _public enumerator_ `HMD`
- L25 _public enumerator_ `Chest`
- L26 _public enumerator_ `LeftShoulder`
- L27 _public enumerator_ `RightShoulder`
- L28 _public enumerator_ `LeftElbow`
- L29 _public enumerator_ `RightElbow`
- L30 _public enumerator_ `Waist`
- L31 _public enumerator_ `LeftKnee`
- L32 _public enumerator_ `RightKnee`
- L33 _public enumerator_ `LeftFoot`
- L34 _public enumerator_ `RightFoot`
- L35 _public enumerator_ `Special`
- L37 _public enumerator_ `ControllerHand_Count UMETA(Hidden, DisplayName = "<INVALID>")`

#### enum `EPairedAxis`  
`enum class EPairedAxis : uint8`  
_L40-46_
- L42 _public enumerator_ `Unpaired` — This key is unpaired
- L43 _public enumerator_ `X` — This key represents the X axis of its PairedAxisKey
- L44 _public enumerator_ `Y` — This key represents the Y axis of its PairedAxisKey
- L45 _public enumerator_ `Z` — This key represents the Z axis of its PairedAxisKey - Currently unused

#### struct `FKey`  
`struct FKey`  
_L49-127_
- reflection: `USTRUCT(BlueprintType,Blueprintable)`
- L53 _public function_ `FKey()`
- L57 _public function_ `FKey(const FName InName) : KeyName(InName)`
- L62 _public function_ `FKey(const TCHAR* InName) : KeyName(FName(InName))`
- L67 _public function_ `FKey(const ANSICHAR* InName) : KeyName(FName(InName))`
- L72 _public prototype_ `bool IsValid() const;`
- L73 _public prototype_ `bool IsModifierKey() const;`
- L74 _public prototype_ `bool IsGamepadKey() const;`
- L75 _public prototype_ `bool IsTouch() const;`
- L76 _public prototype_ `bool IsMouseButton() const;`
- L77 _public prototype_ `bool IsButtonAxis() const;`
- L78 _public prototype_ `bool IsAxis1D() const;`
- L79 _public prototype_ `bool IsAxis2D() const;`
- L80 _public prototype_ `bool IsAxis3D() const;`
- L81 _public prototype_ `bool IsDigital() const;`
- L82 _public prototype_ `bool IsAnalog() const;`
- L83 _public prototype_ `bool IsVirtual() const;`
- L84 _public prototype_ `bool IsBindableInBlueprints() const;`
- L85 _public prototype_ `bool ShouldUpdateAxisWithoutSamples() const;`
- L86 _public prototype_ `bool IsBindableToActions() const;`
- L87 _public prototype_ `bool IsDeprecated() const;`
- L88 _public prototype_ `bool IsGesture() const;`
- L89 _public prototype_ `FText GetDisplayName(bool bLongDisplayName = true) const;`
- L90 _public prototype_ `FString ToString() const;`
- L91 _public prototype_ `FName GetFName() const;`
- L92 _public prototype_ `FName GetMenuCategory() const;`
- L93 _public prototype_ `EPairedAxis GetPairedAxis() const;`
- L94 _public prototype_ `FKey GetPairedAxisKey() const;`
- L95 _public prototype_ `FKey GetVirtualKey() const;`
- L101 _public prototype_ `bool IsSameResolvedKey(const FKey& Other) const;` — @param Other		The key to compare against @return			True if this FKey's name or its virtual key name (if it has one) is the same as the other.
- L103 _public prototype_ `bool SerializeFromMismatchedTag(struct FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L104 _public prototype_ `bool ExportTextItem(FString& ValueStr, FKey const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;`
- L105 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);`
- L106 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L107 _public prototype_ `void PostScriptConstruct();`
- L116 _public member_ `static const TCHAR* SyntheticCharPrefix;`
- L121 _private member_ `FName KeyName;` — `UPROPERTY(EditAnywhere, Category="Input")`
- L123 _private member_ `mutable class TSharedPtr<struct FKeyDetails> KeyDetails;`
- L125 _private prototype_ `void ConditionalLookupKeyDetails() const;`
- L126 _private prototype_ `void ResetKey();`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FKey> : public TStructOpsTypeTraitsBase2<FKey>`  
_L130-141_
- inherits: `TStructOpsTypeTraitsBase2<FKey>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L133-140_

#### struct `FKeyDetails`  
`struct FKeyDetails`  
_L145-251_
- L178 _public prototype_ `FKeyDetails(const FKey InKey, const TAttribute<FText>& InLongDisplayName, const uint32 InKeyFlags = 0, const FName InMenuCategory = NAME_None, const TAttribute<FText>& InShortDisplayName = TAttribute<FText>() );`
- L179 _public prototype_ `FKeyDetails(const FKey InKey, const TAttribute<FText>& InLongDisplayName, const TAttribute<FText>& InShortDisplayName, const uint32 InKeyFlags = 0, const FName InMenuCategory = NAME_None);`
- L181 _public function_ `inline bool IsModifierKey() const`
- L182 _public function_ `inline bool IsGamepadKey() const`
- L183 _public function_ `inline bool IsTouch() const`
- L184 _public function_ `inline bool IsMouseButton() const`
- L185 _public function_ `inline bool IsAxis1D() const`
- L186 _public function_ `inline bool IsAxis2D() const`
- L187 _public function_ `inline bool IsAxis3D() const`
- L188 _public function_ `inline bool IsButtonAxis() const` — Analog 1D axis emulating a digital button press.
- L189 _public function_ `inline bool IsAnalog() const`
- L190 _public function_ `inline bool IsDigital() const`
- L191 _public function_ `inline bool IsBindableInBlueprints() const`
- L192 _public function_ `inline bool ShouldUpdateAxisWithoutSamples() const`
- L193 _public function_ `inline bool IsBindableToActions() const`
- L194 _public function_ `inline bool IsGesture() const`
- L195 _public function_ `inline bool IsDeprecated() const`
- L196 _public function_ `inline bool IsVirtual() const`
- L197 _public function_ `inline FName GetMenuCategory() const`
- L198 _public prototype_ `FText GetDisplayName(const bool bLongDisplayName = true) const;`
- L199 _public function_ `inline const FKey& GetKey() const`
- L202 _public function_ `inline EPairedAxis GetPairedAxis() const` — Key pairing
- L203 _public function_ `inline const FKey& GetPairedAxisKey() const`
- L208 _public function_ `inline const FKey& GetVirtualKey() const` — For virtual Keys, this will return the virtual key value. For non-virtual keys, it will return the "normal" key for easier checking
- L213 _private prototype_ `void CommonInit(const uint32 InKeyFlags);`
- L224 _private member_ `FKey Key;`
- L227 _private member_ `EPairedAxis PairedAxis = EPairedAxis::Unpaired;` — Key pairing
- L228 _private member_ `FKey PairedAxisKey;` — Paired axis reference. This is the FKey representing the final paired vector axis. Note: NOT the other key in the pairing.
- L233 _private member_ `FKey VirtualKeyValue;` — The actual FKey which should be used at runtime for virtual FKeys
- L235 _private member_ `FName MenuCategory;`
- L237 _private member_ `uint8 bIsModifierKey : 1;`
- L238 _private member_ `uint8 bIsGamepadKey : 1;`
- L239 _private member_ `uint8 bIsTouch : 1;`
- L240 _private member_ `uint8 bIsMouseButton : 1;`
- L241 _private member_ `uint8 bIsBindableInBlueprints : 1;`
- L242 _private member_ `uint8 bShouldUpdateAxisWithoutSamples : 1;`
- L243 _private member_ `uint8 bIsBindableToActions : 1;`
- L244 _private member_ `uint8 bIsDeprecated : 1;`
- L245 _private member_ `uint8 bIsVirtual : 1;`
- L246 _private member_ `uint8 bIsGesture : 1;`
- L247 _private member_ `EInputAxisType AxisType;`
- L249 _private member_ `TAttribute<FText> LongDisplayName;`
- L250 _private member_ `TAttribute<FText> ShortDisplayName;`

#### enum `FKeyDetails::EKeyFlags`  
`enum EKeyFlags`  
_L147-176_
- L149 _public enumerator_ `GamepadKey = 1 << 0`
- L150 _public enumerator_ `Touch = 1 << 1`
- L151 _public enumerator_ `MouseButton = 1 << 2`
- L152 _public enumerator_ `ModifierKey = 1 << 3`
- L153 _public enumerator_ `NotBlueprintBindableKey = 1 << 4`
- L154 _public enumerator_ `Axis1D = 1 << 5`
- L155 _public enumerator_ `Axis3D = 1 << 6`
- L156 _public enumerator_ `UpdateAxisWithoutSamples = 1 << 7`
- L157 _public enumerator_ `NotActionBindableKey = 1 << 8`
- L158 _public enumerator_ `Deprecated = 1 << 9`
- L161 _public enumerator_ `ButtonAxis = 1 << 10` — All axis representations
- L162 _public enumerator_ `Axis2D = 1 << 11`
- L165 _public enumerator_ `Gesture = 1 << 12` — Gesture input types such as Flick, Pinch, and Rotate
- L173 _public enumerator_ `Virtual = 1 << 13` — A key is "Virtual" if it is an abstract key whose actual value may change dependent on the platform. For example, the standard "Accept" button on some platforms may be Gamepad_FaceButton_Down, while on other platforms it may be Gamepad_FaceButton_Right. Virtual keys are typically the most useful when it comes to building UI related code because they allow you to create experiences and screens displayed to the end user which are consistent with the platform's UI.
- L175 _public enumerator_ `NoFlags = 0`

#### enum `FKeyDetails::EInputAxisType`  
`enum class EInputAxisType : uint8`  
_L215-222_
- L217 _public enumerator_ `None`
- L218 _public enumerator_ `Button` — Whilst the physical input is an analog axis the FKey uses it to emulate a digital button.
- L219 _public enumerator_ `Axis1D`
- L220 _public enumerator_ `Axis2D`
- L221 _public enumerator_ `Axis3D`

#### enum `ETouchIndex::Type`  
`enum Type : int`  
_L257-275_
- desc: The number of entries in ETouchIndex must match the number of touch keys defined in EKeys and NUM_TOUCH_KEYS above
- L259 _public enumerator_ `Touch1`
- L260 _public enumerator_ `Touch2`
- L261 _public enumerator_ `Touch3`
- L262 _public enumerator_ `Touch4`
- L263 _public enumerator_ `Touch5`
- L264 _public enumerator_ `Touch6`
- L265 _public enumerator_ `Touch7`
- L266 _public enumerator_ `Touch8`
- L267 _public enumerator_ `Touch9`
- L268 _public enumerator_ `Touch10`
- L273 _public enumerator_ `CursorPointerIndex UMETA(Hidden)` — This entry is special.  NUM_TOUCH_KEYS - 1, is used for the cursor so that it's represented as another finger index, but doesn't overlap with touch input indexes.
- L274 _public enumerator_ `MAX_TOUCHES UMETA(Hidden)`

#### struct `FTouchId`  
`struct FTouchId`  
_L283-332_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- desc: Identifies a specific touch contact on a specific input device. Combines device identity (FInputDeviceId) with finger index (ETouchIndex) so that multiple touchscreens can each have independent finger-0, etc.
- L287 _public prototype_ `FTouchId() = default;`
- L289 _public function_ `explicit FTouchId(const FInputDeviceId InDeviceId, const ETouchIndex::Type InTouchIndex) : DeviceId(InDeviceId) , TouchIndex(InTouchIndex)`
- L295 _public function_ `FInputDeviceId GetDeviceId() const`
- L300 _public function_ `ETouchIndex::Type GetIndex() const`
- L305 _public prototype_ `bool operator==(const FTouchId& Other) const = default;`
- L307 _public prototype_ `bool operator!=(const FTouchId& Other) const = default;`
- L309 _public function_ `bool IsValid() const`
- L325 _private member_ `FInputDeviceId DeviceId = INPUTDEVICEID_NONE;` — `UPROPERTY(BlueprintReadOnly, Category = "Input|Touch", meta = (AllowPrivateAccess = "true"))` — The device being touched.
- L331 _private member_ `TEnumAsByte<ETouchIndex::Type> TouchIndex = ETouchIndex::Touch1;` — `UPROPERTY(BlueprintReadOnly, Category = "Input|Touch", meta = (AllowPrivateAccess = "true"))` — The device-specific index that differentiates this touch from other simultaneous touch inputs on the same device.

#### enum `EConsoleForGamepadLabels::Type`  
`enum Type : int`  
_L337-342_
- L339 _public enumerator_ `None`
- L340 _public enumerator_ `XBoxOne`
- L341 _public enumerator_ `PS4`

#### struct `EKeys`  
`struct EKeys`  
_L345-827_
- L347 _public member_ `static const FKey AnyKey;`
- L349 _public member_ `static const FKey MouseX;`
- L350 _public member_ `static const FKey MouseY;`
- L351 _public member_ `static const FKey Mouse2D;`
- L352 _public member_ `static const FKey MouseScrollUp;`
- L353 _public member_ `static const FKey MouseScrollDown;`
- L354 _public member_ `static const FKey MouseWheelAxis;`
- L356 _public member_ `static const FKey LeftMouseButton;`
- L357 _public member_ `static const FKey RightMouseButton;`
- L358 _public member_ `static const FKey MiddleMouseButton;`
- L359 _public member_ `static const FKey ThumbMouseButton;`
- L360 _public member_ `static const FKey ThumbMouseButton2;`
- L362 _public member_ `static const FKey BackSpace;`
- L363 _public member_ `static const FKey Tab;`
- L364 _public member_ `static const FKey Enter;`
- L365 _public member_ `static const FKey Pause;`
- L367 _public member_ `static const FKey CapsLock;`
- L368 _public member_ `static const FKey Escape;`
- L369 _public member_ `static const FKey SpaceBar;`
- L370 _public member_ `static const FKey PageUp;`
- L371 _public member_ `static const FKey PageDown;`
- L372 _public member_ `static const FKey End;`
- L373 _public member_ `static const FKey Home;`
- L375 _public member_ `static const FKey Left;`
- L376 _public member_ `static const FKey Up;`
- L377 _public member_ `static const FKey Right;`
- L378 _public member_ `static const FKey Down;`
- L380 _public member_ `static const FKey Insert;`
- L381 _public member_ `static const FKey Delete;`
- L383 _public member_ `static const FKey Zero;`
- L384 _public member_ `static const FKey One;`
- L385 _public member_ `static const FKey Two;`
- L386 _public member_ `static const FKey Three;`
- L387 _public member_ `static const FKey Four;`
- L388 _public member_ `static const FKey Five;`
- L389 _public member_ `static const FKey Six;`
- L390 _public member_ `static const FKey Seven;`
- L391 _public member_ `static const FKey Eight;`
- L392 _public member_ `static const FKey Nine;`
- L394 _public member_ `static const FKey A;`
- L395 _public member_ `static const FKey B;`
- L396 _public member_ `static const FKey C;`
- L397 _public member_ `static const FKey D;`
- L398 _public member_ `static const FKey E;`
- L399 _public member_ `static const FKey F;`
- L400 _public member_ `static const FKey G;`
- L401 _public member_ `static const FKey H;`
- L402 _public member_ `static const FKey I;`
- L403 _public member_ `static const FKey J;`
- L404 _public member_ `static const FKey K;`
- L405 _public member_ `static const FKey L;`
- L406 _public member_ `static const FKey M;`
- L407 _public member_ `static const FKey N;`
- L408 _public member_ `static const FKey O;`
- L409 _public member_ `static const FKey P;`
- L410 _public member_ `static const FKey Q;`
- L411 _public member_ `static const FKey R;`
- L412 _public member_ `static const FKey S;`
- L413 _public member_ `static const FKey T;`
- L414 _public member_ `static const FKey U;`
- L415 _public member_ `static const FKey V;`
- L416 _public member_ `static const FKey W;`
- L417 _public member_ `static const FKey X;`
- L418 _public member_ `static const FKey Y;`
- L419 _public member_ `static const FKey Z;`
- L421 _public member_ `static const FKey NumPadZero;`
- L422 _public member_ `static const FKey NumPadOne;`
- L423 _public member_ `static const FKey NumPadTwo;`
- L424 _public member_ `static const FKey NumPadThree;`
- L425 _public member_ `static const FKey NumPadFour;`
- L426 _public member_ `static const FKey NumPadFive;`
- L427 _public member_ `static const FKey NumPadSix;`
- L428 _public member_ `static const FKey NumPadSeven;`
- L429 _public member_ `static const FKey NumPadEight;`
- L430 _public member_ `static const FKey NumPadNine;`
- L432 _public member_ `static const FKey Multiply;`
- L433 _public member_ `static const FKey Add;`
- L434 _public member_ `static const FKey Subtract;`
- L435 _public member_ `static const FKey Decimal;`
- L436 _public member_ `static const FKey Divide;`
- L438 _public member_ `static const FKey F1;`
- L439 _public member_ `static const FKey F2;`
- L440 _public member_ `static const FKey F3;`
- L441 _public member_ `static const FKey F4;`
- L442 _public member_ `static const FKey F5;`
- L443 _public member_ `static const FKey F6;`
- L444 _public member_ `static const FKey F7;`
- L445 _public member_ `static const FKey F8;`
- L446 _public member_ `static const FKey F9;`
- L447 _public member_ `static const FKey F10;`
- L448 _public member_ `static const FKey F11;`
- L449 _public member_ `static const FKey F12;`
- L451 _public member_ `static const FKey NumLock;`
- L453 _public member_ `static const FKey ScrollLock;`
- L455 _public member_ `static const FKey LeftShift;`
- L456 _public member_ `static const FKey RightShift;`
- L457 _public member_ `static const FKey LeftControl;`
- L458 _public member_ `static const FKey RightControl;`
- L459 _public member_ `static const FKey LeftAlt;`
- L460 _public member_ `static const FKey RightAlt;`
- L461 _public member_ `static const FKey LeftCommand;`
- L462 _public member_ `static const FKey RightCommand;`
- L464 _public member_ `static const FKey Semicolon;`
- L465 _public member_ `static const FKey Equals;`
- L466 _public member_ `static const FKey Comma;`
- L467 _public member_ `static const FKey Underscore;`
- L468 _public member_ `static const FKey Hyphen;`
- L469 _public member_ `static const FKey Period;`
- L470 _public member_ `static const FKey Slash;`
- L471 _public member_ `static const FKey Tilde;`
- L472 _public member_ `static const FKey LeftBracket;`
- L473 _public member_ `static const FKey Backslash;`
- L474 _public member_ `static const FKey RightBracket;`
- L475 _public member_ `static const FKey Apostrophe;`
- L477 _public member_ `static const FKey Ampersand;`
- L478 _public member_ `static const FKey Asterix;`
- L479 _public member_ `static const FKey Caret;`
- L480 _public member_ `static const FKey Colon;`
- L481 _public member_ `static const FKey Dollar;`
- L482 _public member_ `static const FKey Exclamation;`
- L483 _public member_ `static const FKey LeftParantheses;`
- L484 _public member_ `static const FKey RightParantheses;`
- L485 _public member_ `static const FKey Quote;`
- L487 _public member_ `static const FKey A_AccentGrave;`
- L488 _public member_ `static const FKey E_AccentGrave;`
- L489 _public member_ `static const FKey E_AccentAigu;`
- L490 _public member_ `static const FKey C_Cedille;`
- L491 _public member_ `static const FKey Section;`
- L497 _public member_ `static const FKey Platform_Delete;` — Platform Keys These keys platform specific versions of keys that go by different names. The delete key is a good example, on Windows Delete is the virtual key for Delete. On Macs, the Delete key is the virtual key for BackSpace.
- L500 _public member_ `static const FKey Gamepad_Left2D;` — Gamepad Keys
- L501 _public member_ `static const FKey Gamepad_LeftX;`
- L502 _public member_ `static const FKey Gamepad_LeftY;`
- L503 _public member_ `static const FKey Gamepad_Right2D;`
- L504 _public member_ `static const FKey Gamepad_RightX;`
- L505 _public member_ `static const FKey Gamepad_RightY;`
- L506 _public member_ `static const FKey Gamepad_LeftTriggerAxis;`
- L507 _public member_ `static const FKey Gamepad_RightTriggerAxis;`
- L509 _public member_ `static const FKey Gamepad_LeftThumbstick;`
- L510 _public member_ `static const FKey Gamepad_RightThumbstick;`
- L511 _public member_ `static const FKey Gamepad_Special_Left;`
- L512 _public member_ `static const FKey Gamepad_Special_Left_X;`
- L513 _public member_ `static const FKey Gamepad_Special_Left_Y;`
- L514 _public member_ `static const FKey Gamepad_Special_Left_Touched;`
- L515 _public member_ `static const FKey Gamepad_Special_Right;`
- L516 _public member_ `static const FKey Gamepad_FaceButton_Bottom;`
- L517 _public member_ `static const FKey Gamepad_FaceButton_Right;`
- L518 _public member_ `static const FKey Gamepad_FaceButton_Left;`
- L519 _public member_ `static const FKey Gamepad_FaceButton_Top;`
- L520 _public member_ `static const FKey Gamepad_LeftShoulder;`
- L521 _public member_ `static const FKey Gamepad_RightShoulder;`
- L522 _public member_ `static const FKey Gamepad_LeftTrigger;`
- L523 _public member_ `static const FKey Gamepad_RightTrigger;`
- L524 _public member_ `static const FKey Gamepad_DPad_Up;`
- L525 _public member_ `static const FKey Gamepad_DPad_Down;`
- L526 _public member_ `static const FKey Gamepad_DPad_Right;`
- L527 _public member_ `static const FKey Gamepad_DPad_Left;`
- L530 _public member_ `static const FKey Gamepad_LeftStick_Up;` — Virtual key codes used for input axis button press/release emulation
- L531 _public member_ `static const FKey Gamepad_LeftStick_Down;`
- L532 _public member_ `static const FKey Gamepad_LeftStick_Right;`
- L533 _public member_ `static const FKey Gamepad_LeftStick_Left;`
- L535 _public member_ `static const FKey Gamepad_RightStick_Up;`
- L536 _public member_ `static const FKey Gamepad_RightStick_Down;`
- L537 _public member_ `static const FKey Gamepad_RightStick_Right;`
- L538 _public member_ `static const FKey Gamepad_RightStick_Left;`
- L541 _public member_ `static const FKey Tilt;` — static const FKey Vector axes (FVector; not float)
- L542 _public member_ `static const FKey RotationRate;`
- L543 _public member_ `static const FKey Gravity;`
- L544 _public member_ `static const FKey Acceleration;`
- L547 _public member_ `static const FKey Gesture_Pinch;` — Gestures
- L548 _public member_ `static const FKey Gesture_Flick;`
- L549 _public member_ `static const FKey Gesture_Rotate;`
- L550 _public member_ `static const FKey Gesture_Pan;`
- L551 _public member_ `static const FKey Gesture_Tap;`
- L552 _public member_ `static const FKey Gesture_LongPress;`
- L555 _public member_ `static const FKey Steam_Touch_0;` — Steam Controller Specific
- L556 _public member_ `static const FKey Steam_Touch_1;`
- L557 _public member_ `static const FKey Steam_Touch_2;`
- L558 _public member_ `static const FKey Steam_Touch_3;`
- L559 _public member_ `static const FKey Steam_Back_Left;`
- L560 _public member_ `static const FKey Steam_Back_Right;`
- L563 _public member_ `static const FKey Global_Menu;` — Xbox One global speech commands
- L564 _public member_ `static const FKey Global_View;`
- L565 _public member_ `static const FKey Global_Pause;`
- L566 _public member_ `static const FKey Global_Play;`
- L567 _public member_ `static const FKey Global_Back;`
- L570 _public member_ `static const FKey Android_Back;` — Android-specific
- L571 _public member_ `static const FKey Android_Volume_Up;`
- L572 _public member_ `static const FKey Android_Volume_Down;`
- L573 _public member_ `static const FKey Android_Menu;`
- L576 _public member_ `static const FKey Vive_Left_Grip_Click;` — HTC Vive Controller
- L577 _public member_ `static const FKey Vive_Left_Menu_Click;`
- L578 _public member_ `static const FKey Vive_Left_Trigger_Click;`
- L579 _public member_ `static const FKey Vive_Left_Trigger_Axis;`
- L580 _public member_ `static const FKey Vive_Left_Trackpad_2D;`
- L581 _public member_ `static const FKey Vive_Left_Trackpad_X;`
- L582 _public member_ `static const FKey Vive_Left_Trackpad_Y;`
- L583 _public member_ `static const FKey Vive_Left_Trackpad_Click;`
- L584 _public member_ `static const FKey Vive_Left_Trackpad_Touch;`
- L585 _public member_ `static const FKey Vive_Left_Trackpad_Up;`
- L586 _public member_ `static const FKey Vive_Left_Trackpad_Down;`
- L587 _public member_ `static const FKey Vive_Left_Trackpad_Left;`
- L588 _public member_ `static const FKey Vive_Left_Trackpad_Right;`
- L589 _public member_ `static const FKey Vive_Right_Grip_Click;`
- L590 _public member_ `static const FKey Vive_Right_Menu_Click;`
- L591 _public member_ `static const FKey Vive_Right_Trigger_Click;`
- L592 _public member_ `static const FKey Vive_Right_Trigger_Axis;`
- L593 _public member_ `static const FKey Vive_Right_Trackpad_2D;`
- L594 _public member_ `static const FKey Vive_Right_Trackpad_X;`
- L595 _public member_ `static const FKey Vive_Right_Trackpad_Y;`
- L596 _public member_ `static const FKey Vive_Right_Trackpad_Click;`
- L597 _public member_ `static const FKey Vive_Right_Trackpad_Touch;`
- L598 _public member_ `static const FKey Vive_Right_Trackpad_Up;`
- L599 _public member_ `static const FKey Vive_Right_Trackpad_Down;`
- L600 _public member_ `static const FKey Vive_Right_Trackpad_Left;`
- L601 _public member_ `static const FKey Vive_Right_Trackpad_Right;`
- L604 _public member_ `static const FKey MixedReality_Left_Menu_Click;` — Microsoft Mixed Reality Motion Controller
- L605 _public member_ `static const FKey MixedReality_Left_Grip_Click;`
- L606 _public member_ `static const FKey MixedReality_Left_Trigger_Click;`
- L607 _public member_ `static const FKey MixedReality_Left_Trigger_Axis;`
- L608 _public member_ `static const FKey MixedReality_Left_Thumbstick_2D;`
- L609 _public member_ `static const FKey MixedReality_Left_Thumbstick_X;`
- L610 _public member_ `static const FKey MixedReality_Left_Thumbstick_Y;`
- L611 _public member_ `static const FKey MixedReality_Left_Thumbstick_Click;`
- L612 _public member_ `static const FKey MixedReality_Left_Thumbstick_Up;`
- L613 _public member_ `static const FKey MixedReality_Left_Thumbstick_Down;`
- L614 _public member_ `static const FKey MixedReality_Left_Thumbstick_Left;`
- L615 _public member_ `static const FKey MixedReality_Left_Thumbstick_Right;`
- L616 _public member_ `static const FKey MixedReality_Left_Trackpad_2D;`
- L617 _public member_ `static const FKey MixedReality_Left_Trackpad_X;`
- L618 _public member_ `static const FKey MixedReality_Left_Trackpad_Y;`
- L619 _public member_ `static const FKey MixedReality_Left_Trackpad_Click;`
- L620 _public member_ `static const FKey MixedReality_Left_Trackpad_Touch;`
- L621 _public member_ `static const FKey MixedReality_Left_Trackpad_Up;`
- L622 _public member_ `static const FKey MixedReality_Left_Trackpad_Down;`
- L623 _public member_ `static const FKey MixedReality_Left_Trackpad_Left;`
- L624 _public member_ `static const FKey MixedReality_Left_Trackpad_Right;`
- L625 _public member_ `static const FKey MixedReality_Right_Menu_Click;`
- L626 _public member_ `static const FKey MixedReality_Right_Grip_Click;`
- L627 _public member_ `static const FKey MixedReality_Right_Trigger_Click;`
- L628 _public member_ `static const FKey MixedReality_Right_Trigger_Axis;`
- L629 _public member_ `static const FKey MixedReality_Right_Thumbstick_2D;`
- L630 _public member_ `static const FKey MixedReality_Right_Thumbstick_X;`
- L631 _public member_ `static const FKey MixedReality_Right_Thumbstick_Y;`
- L632 _public member_ `static const FKey MixedReality_Right_Thumbstick_Click;`
- L633 _public member_ `static const FKey MixedReality_Right_Thumbstick_Up;`
- L634 _public member_ `static const FKey MixedReality_Right_Thumbstick_Down;`
- L635 _public member_ `static const FKey MixedReality_Right_Thumbstick_Left;`
- L636 _public member_ `static const FKey MixedReality_Right_Thumbstick_Right;`
- L637 _public member_ `static const FKey MixedReality_Right_Trackpad_2D;`
- L638 _public member_ `static const FKey MixedReality_Right_Trackpad_X;`
- L639 _public member_ `static const FKey MixedReality_Right_Trackpad_Y;`
- L640 _public member_ `static const FKey MixedReality_Right_Trackpad_Click;`
- L641 _public member_ `static const FKey MixedReality_Right_Trackpad_Touch;`
- L642 _public member_ `static const FKey MixedReality_Right_Trackpad_Up;`
- L643 _public member_ `static const FKey MixedReality_Right_Trackpad_Down;`
- L644 _public member_ `static const FKey MixedReality_Right_Trackpad_Left;`
- L645 _public member_ `static const FKey MixedReality_Right_Trackpad_Right;`
- L648 _public member_ `static const FKey OculusTouch_Left_X_Click;` — Oculus Touch Controller
- L649 _public member_ `static const FKey OculusTouch_Left_Y_Click;`
- L650 _public member_ `static const FKey OculusTouch_Left_X_Touch;`
- L651 _public member_ `static const FKey OculusTouch_Left_Y_Touch;`
- L652 _public member_ `static const FKey OculusTouch_Left_Menu_Click;`
- L653 _public member_ `static const FKey OculusTouch_Left_Grip_Click;`
- L654 _public member_ `static const FKey OculusTouch_Left_Grip_Axis;`
- L655 _public member_ `static const FKey OculusTouch_Left_Trigger_Click;`
- L656 _public member_ `static const FKey OculusTouch_Left_Trigger_Axis;`
- L657 _public member_ `static const FKey OculusTouch_Left_Trigger_Touch;`
- L658 _public member_ `static const FKey OculusTouch_Left_Thumbstick_2D;`
- L659 _public member_ `static const FKey OculusTouch_Left_Thumbstick_X;`
- L660 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Y;`
- L661 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Click;`
- L662 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Touch;`
- L663 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Up;`
- L664 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Down;`
- L665 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Left;`
- L666 _public member_ `static const FKey OculusTouch_Left_Thumbstick_Right;`
- L667 _public member_ `static const FKey OculusTouch_Right_A_Click;`
- L668 _public member_ `static const FKey OculusTouch_Right_B_Click;`
- L669 _public member_ `static const FKey OculusTouch_Right_A_Touch;`
- L670 _public member_ `static const FKey OculusTouch_Right_B_Touch;`
- L671 _public member_ `static const FKey OculusTouch_Right_Grip_Click;`
- L672 _public member_ `static const FKey OculusTouch_Right_Grip_Axis;`
- L673 _public member_ `static const FKey OculusTouch_Right_Trigger_Click;`
- L674 _public member_ `static const FKey OculusTouch_Right_Trigger_Axis;`
- L675 _public member_ `static const FKey OculusTouch_Right_Trigger_Touch;`
- L676 _public member_ `static const FKey OculusTouch_Right_Thumbstick_2D;`
- L677 _public member_ `static const FKey OculusTouch_Right_Thumbstick_X;`
- L678 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Y;`
- L679 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Click;`
- L680 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Touch;`
- L681 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Up;`
- L682 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Down;`
- L683 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Left;`
- L684 _public member_ `static const FKey OculusTouch_Right_Thumbstick_Right;`
- L687 _public member_ `static const FKey ValveIndex_Left_A_Click;` — Valve Index Controller
- L688 _public member_ `static const FKey ValveIndex_Left_B_Click;`
- L689 _public member_ `static const FKey ValveIndex_Left_A_Touch;`
- L690 _public member_ `static const FKey ValveIndex_Left_B_Touch;`
- L691 _public member_ `static const FKey ValveIndex_Left_Grip_Axis;`
- L692 _public member_ `static const FKey ValveIndex_Left_Grip_Force;`
- L693 _public member_ `static const FKey ValveIndex_Left_Trigger_Click;`
- L694 _public member_ `static const FKey ValveIndex_Left_Trigger_Axis;`
- L695 _public member_ `static const FKey ValveIndex_Left_Trigger_Touch;`
- L696 _public member_ `static const FKey ValveIndex_Left_Thumbstick_2D;`
- L697 _public member_ `static const FKey ValveIndex_Left_Thumbstick_X;`
- L698 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Y;`
- L699 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Click;`
- L700 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Touch;`
- L701 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Up;`
- L702 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Down;`
- L703 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Left;`
- L704 _public member_ `static const FKey ValveIndex_Left_Thumbstick_Right;`
- L705 _public member_ `static const FKey ValveIndex_Left_Trackpad_2D;`
- L706 _public member_ `static const FKey ValveIndex_Left_Trackpad_X;`
- L707 _public member_ `static const FKey ValveIndex_Left_Trackpad_Y;`
- L708 _public member_ `static const FKey ValveIndex_Left_Trackpad_Force;`
- L709 _public member_ `static const FKey ValveIndex_Left_Trackpad_Touch;`
- L710 _public member_ `static const FKey ValveIndex_Left_Trackpad_Up;`
- L711 _public member_ `static const FKey ValveIndex_Left_Trackpad_Down;`
- L712 _public member_ `static const FKey ValveIndex_Left_Trackpad_Left;`
- L713 _public member_ `static const FKey ValveIndex_Left_Trackpad_Right;`
- L714 _public member_ `static const FKey ValveIndex_Right_A_Click;`
- L715 _public member_ `static const FKey ValveIndex_Right_B_Click;`
- L716 _public member_ `static const FKey ValveIndex_Right_A_Touch;`
- L717 _public member_ `static const FKey ValveIndex_Right_B_Touch;`
- L718 _public member_ `static const FKey ValveIndex_Right_Grip_Axis;`
- L719 _public member_ `static const FKey ValveIndex_Right_Grip_Force;`
- L720 _public member_ `static const FKey ValveIndex_Right_Trigger_Click;`
- L721 _public member_ `static const FKey ValveIndex_Right_Trigger_Axis;`
- L722 _public member_ `static const FKey ValveIndex_Right_Trigger_Touch;`
- L723 _public member_ `static const FKey ValveIndex_Right_Thumbstick_2D;`
- L724 _public member_ `static const FKey ValveIndex_Right_Thumbstick_X;`
- L725 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Y;`
- L726 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Click;`
- L727 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Touch;`
- L728 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Up;`
- L729 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Down;`
- L730 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Left;`
- L731 _public member_ `static const FKey ValveIndex_Right_Thumbstick_Right;`
- L732 _public member_ `static const FKey ValveIndex_Right_Trackpad_2D;`
- L733 _public member_ `static const FKey ValveIndex_Right_Trackpad_X;`
- L734 _public member_ `static const FKey ValveIndex_Right_Trackpad_Y;`
- L735 _public member_ `static const FKey ValveIndex_Right_Trackpad_Force;`
- L736 _public member_ `static const FKey ValveIndex_Right_Trackpad_Touch;`
- L737 _public member_ `static const FKey ValveIndex_Right_Trackpad_Up;`
- L738 _public member_ `static const FKey ValveIndex_Right_Trackpad_Down;`
- L739 _public member_ `static const FKey ValveIndex_Right_Trackpad_Left;`
- L740 _public member_ `static const FKey ValveIndex_Right_Trackpad_Right;`
- L745 _public member_ `static const FKey Virtual_Accept;` — `UE_DEPRECATED(5.7, "Use Virtual_Gamepad_Accept.GetVirtualKey() instead")`
- L747 _public member_ `static const FKey Virtual_Back;` — `UE_DEPRECATED(5.7, "Use Virtual_Gamepad_Back.GetVirtualKey() instead")`
- L749 _public member_ `static const FKey Virtual_Gamepad_Accept;`
- L750 _public member_ `static const FKey Virtual_Gamepad_Back;`
- L752 _public member_ `static const FKey Invalid;`
- L754 _public member_ `static const int32 NUM_TOUCH_KEYS = 11;`
- L755 _public member_ `static const FKey TouchKeys[NUM_TOUCH_KEYS];`
- L758 _public member_ `static const int32 NUM_XR_KEY_TOKENS = 4;` — XR key names are parseable into exactly 4 tokens
- L760 _public member_ `static EConsoleForGamepadLabels::Type ConsoleForGamepadLabels;`
- L762 _public member_ `static const FName NAME_KeyboardCategory;`
- L763 _public member_ `static const FName NAME_GamepadCategory;`
- L764 _public member_ `static const FName NAME_MouseCategory;`
- L765 _public member_ `static const FName NAME_VirtualCategory;`
- L767 _public prototype_ `static void Initialize();`
- L768 _public prototype_ `static void AddKey(const FKeyDetails& KeyDetails);`
- L770 _public prototype_ `static void AddPairedKey(const FKeyDetails& PairedKeyDetails, FKey KeyX, FKey KeyY);` — Map the two provided keys to the X and Y axes of the paired key
- L771 _public prototype_ `static void AddVirtualKey(const FKeyDetails& VirtualKeyDetails, const FKey& VirtualKeyValue);`
- L772 _public prototype_ `static void GetAllKeys(TArray<FKey>& OutKeys);`
- L773 _public prototype_ `static TSharedPtr<FKeyDetails> GetKeyDetails(const FKey Key);`
- L774 _public prototype_ `static void RemoveKeysWithCategory(const FName InCategory);`
- L777 _public function_ `static bool IsModifierKey(FKey Key)` — These exist for backwards compatibility reasons only
- L778 _public function_ `static bool IsGamepadKey(FKey Key)`
- L779 _public function_ `static bool IsAxis(FKey Key)`
- L780 _public function_ `static bool IsBindableInBlueprints(const FKey Key)`
- L781 _public function_ `static void SetConsoleForGamepadLabels(const EConsoleForGamepadLabels::Type Console)`
- L784 _public prototype_ `static FText GetGamepadDisplayName(const FKey Key);` — Function that provides remapping for some gamepad keys in display windows
- L786 _public prototype_ `static void AddMenuCategoryDisplayInfo(const FName CategoryName, const FText DisplayName, const FName PaletteIcon);`
- L787 _public prototype_ `static FText GetMenuCategoryDisplayName(const FName CategoryName);`
- L788 _public prototype_ `static FName GetMenuCategoryPaletteIcon(const FName CategoryName);`
- L806 _public prototype_ `static FPairedKeyDetails* GetPairedKeyDetails(const FKey& PairedKey);`
- L816 _private member_ `static TMap<FKey, TSharedPtr<FKeyDetails>> InputKeys;`
- L822 _private member_ `static TMap<FKey, FPairedKeyDetails> PairedInputKeysLookup;` — A map of Paired Key's (keys which are made up of a "pair" of other FKeys, such as Mouse2D being made up of MouseX and MouseY) to the keys which make up their pair.
- L824 _private member_ `static TMap<FName, FCategoryDisplayInfo> MenuCategoryDisplayInfo;`
- L825 _private member_ `static bool bInitialized;`

#### struct `EKeys::FPairedKeyDetails`  
`struct FPairedKeyDetails`  
_L795-804_
- desc: Stores some data which make up a pair from the "root" key of the pair. Created in EKeys::AddPairedKey. The key details of these types should always be valid
- L797 _public function_ `explicit FPairedKeyDetails(TSharedPtr<FKeyDetails> XDetails, TSharedPtr<FKeyDetails> YDetails) : XKeyDetails(XDetails) , YKeyDetails(YDetails)`
- L802 _public member_ `TSharedPtr<FKeyDetails> XKeyDetails;`
- L803 _public member_ `TSharedPtr<FKeyDetails> YKeyDetails;`

#### struct `EKeys::FCategoryDisplayInfo`  
`struct FCategoryDisplayInfo`  
_L810-814_
- L812 _public member_ `FText DisplayName;`
- L813 _public member_ `FName PaletteIcon;`

#### enum `ETouchType::Type`  
`enum Type : int`  
_L833-843_
- L835 _public enumerator_ `Began`
- L836 _public enumerator_ `Moved`
- L837 _public enumerator_ `Stationary`
- L838 _public enumerator_ `ForceChanged`
- L839 _public enumerator_ `FirstMove`
- L840 _public enumerator_ `Ended`
- L842 _public enumerator_ `NumTypes`

#### struct `FInputKeyManager`  
`struct FInputKeyManager`  
_L847-869_
- L850 _public prototype_ `static FInputKeyManager& Get();`
- L852 _public prototype_ `void GetCodesFromKey(const FKey Key, const uint32*& KeyCode, const uint32*& CharCode) const;`
- L858 _public prototype_ `FKey GetKeyFromCodes( const uint32 KeyCode, const uint32 CharCode ) const;` — Retrieves the key mapped to the specified character code. @param KeyCode	The key code to get the name for.
- L859 _public prototype_ `void InitKeyMappings();`
- L861 _private function_ `FInputKeyManager()`
- L866 _private member_ `static TSharedPtr< FInputKeyManager > Instance;`
- L867 _private member_ `TMap<uint32, FKey> KeyMapVirtualToEnum;`
- L868 _private member_ `TMap<uint32, FKey> KeyMapCharToEnum;`

#### class `UInputCoreTypes`  
`class UInputCoreTypes : public UObject`  
_L872-876_
- reflection: `UCLASS(abstract)`
- inherits: `UObject`

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInput, Log, All);`
- L109 _function_ `friend bool operator==(const FKey& KeyA, const FKey& KeyB)`
- L110 _function_ `friend bool operator!=(const FKey& KeyA, const FKey& KeyB)`
- L111 _function_ `friend bool operator<(const FKey& KeyA, const FKey& KeyB)`
- L112 _function_ `friend uint32 GetTypeHash(const FKey& Key)`
- L134 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon7b1907320103`)
- L135 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon7b1907320103`)
- L136 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon7b1907320103`)
- L137 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon7b1907320103`)
- L138 _enumerator_ `WithPostScriptConstruct = true` (scope `TStructOpsTypeTraits::__anon7b1907320103`)
- L139 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon7b1907320103`) — Necessary so that TSharedPtr<FKeyDetails> Data is copied around
- L143 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetKeyDisplayNameSignature, const FKey);`
- L143 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetKeyDisplayNameSignature, const FKey);`
- L254 _namespace_ `namespace ETouchIndex`
- L314 _function_ `friend uint32 GetTypeHash(const FTouchId& Id)`
- L335 _namespace_ `namespace EConsoleForGamepadLabels`
- L831 _namespace_ `namespace ETouchType`

### `Source/Runtime/InputCore/Public/Android/AndroidPlatformInput.h` (Public)


#### struct `FAndroidPlatformInput`  
`struct FAndroidPlatformInput : FGenericPlatformInput`  
_L8-12_
- inherits: `FGenericPlatformInput`
- L10 _public prototype_ `static uint32 GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings);`
- L11 _public prototype_ `static uint32 GetKeyMap( uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings );`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef FAndroidPlatformInput FPlatformInput;`

### `Source/Runtime/InputCore/Public/GenericPlatform/GenericPlatformInput.h` (Public)


#### struct `FGenericPlatformInput`  
`struct FGenericPlatformInput`  
_L11-51_
- L14 _public function_ `inline static uint32 GetKeyMap( uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings )`
- L19 _public function_ `inline static uint32 GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings)`
- L25 _public function_ `inline static FKey RemapKey(FKey Key)` — Remap a given key to something else if necessary.
- L27 _public function_ `static FKey GetGamepadAcceptKey()`
- L32 _public function_ `static FKey GetGamepadBackKey()`
- L37 _public function_ `static FKey GetPlatformDeleteKey()`
- L50 _protected prototype_ `static uint32 GetStandardPrintableKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings, bool bMapUppercaseKeys, bool bMapLowercaseKeys);` — Retrieves some standard key code mappings (usually called by a subclass's GetCharKeyMap) @param OutKeyMap Key map to add to. @param bMapUppercaseKeys If true, will map A, B, C, etc to EKeys::A, EKeys::B, EKeys::C @param bMapLowercaseKeys If true, will map a, b, c, etc to EKeys::A, EKeys::B, EKeys::C

### `Source/Runtime/InputCore/Public/HAL/PlatformInput.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/InputCore/Public/IInputDebuggingInterface.h` (Public)


#### class `IInputDebuggingInterface`  
`class IInputDebuggingInterface : public IModuleInterface, public IModularFeature`  
_L13-31_
- inherits: `IModuleInterface,IModularFeature`
- desc: The public interface of the InputDeviceModule
- L16 _public function_ `static FName GetModularFeatureName()`
- L22 _public function_ `static inline bool IsAvailable()`
- L27 _public function_ `static inline IInputDebuggingInterface& Get()`

### `Source/Runtime/InputCore/Public/IOS/IOSPlatformInput.h` (Public)


#### struct `FIOSPlatformInput`  
`struct FIOSPlatformInput : FGenericPlatformInput`  
_L8-12_
- inherits: `FGenericPlatformInput`
- L10 _public prototype_ `static uint32 GetKeyMap( uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings );`
- L11 _public prototype_ `static uint32 GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings);`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef FIOSPlatformInput FPlatformInput;`

### `Source/Runtime/InputCore/Public/InputCore.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/InputCore/Public/InputCoreModule.h` (Public)


#### class `FInputCoreModule`  
`class FInputCoreModule : public IModuleInterface`  
_L8-19_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created Overloaded to allow the default subsystem a chance to load

### `Source/Runtime/InputCore/Public/Linux/LinuxPlatformInput.h` (Public)


#### struct `FLinuxPlatformInput`  
`struct FLinuxPlatformInput : FGenericPlatformInput`  
_L9-13_
- inherits: `FGenericPlatformInput`
- L11 _public prototype_ `static uint32 GetKeyMap( uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings );`
- L12 _public prototype_ `static uint32 GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings);`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef FLinuxPlatformInput FPlatformInput;`

### `Source/Runtime/InputCore/Public/Mac/MacPlatformInput.h` (Public)


#### struct `FMacPlatformInput`  
`struct FMacPlatformInput : FGenericPlatformInput`  
_L8-14_
- inherits: `FGenericPlatformInput`
- L10 _public prototype_ `static uint32 GetKeyMap( uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings );`
- L11 _public prototype_ `static uint32 GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings);`
- L12 _public prototype_ `static FKey GetPlatformDeleteKey();`
- L13 _public prototype_ `static uint32 GetMacNativeModifierKeyCode(uint32 ModifierKeyCode);`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef FMacPlatformInput FPlatformInput;`

### `Source/Runtime/InputCore/Public/Windows/WindowsPlatformInput.h` (Public)


#### struct `FWindowsPlatformInput`  
`struct FWindowsPlatformInput : FGenericPlatformInput`  
_L8-12_
- inherits: `FGenericPlatformInput`
- L10 _public prototype_ `static uint32 GetKeyMap( uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings );`
- L11 _public prototype_ `static uint32 GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings);`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef FWindowsPlatformInput FPlatformInput;`
