# Plugins / RawInput

- module root: `Plugins/Experimental/RawInput/Source/RawInput`
- headers: 4; symbols: 401
- symbol kinds: class=5, delegate=1, function=29, macro=3, member=305, prototype=37, struct=12, typedef=9
- PrivateDependencyModuleNames: DeveloperSettings, InputDevice
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, InputCore, Slate, SlateCore

### `Plugins/Experimental/RawInput/Source/RawInput/Public/RawInput.h` (Public)


#### class `IRawInput`  
`class IRawInput : public IInputDevice`  
_L13-78_
- inherits: `IInputDevice`
- L16 _public prototype_ `IRawInput(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);`
- L18 _public function_ `virtual ~IRawInput()`
- L21 _public function_ `virtual void QueryConnectedDevices()` — Query connected devices and populate the ConnectedDeviceInfoList
- L24 _public prototype_ `virtual int32 RegisterInputDevice(int32 DeviceType, int32 Flags, uint16 DeviceID, int16 PageID, void* Handle) = 0;` — Register a device for use.
- L27 _public function_ `virtual void RemoveRegisteredInputDevice(int32 DeviceHandle)` — Remove a registered device
- L35 _public function_ `virtual void BindButtonForDevice(int32 DeviceHandle, FName EventName, int32 ButtonIndex )` — Register a button on a device to send input events with a given name @param DeviceHandle	Device handle to bind to @param KeyName		Key Name (e.g FRawInputKeyNames::GenericUSBController_Button1) @param ButtonIndex	Index of the button to bind
- L43 _public function_ `virtual void BindAnalogForDevice(int32 DeviceHandle, FName KeyName, int32 AxisIndex )` — Register axis/analog on a device to send input events with a given name @param DeviceHandle	Device handle to bind to @param KeyName		Name of key to emit (e.g FRawInputKeyNames::GenericUSBController_Axis1) @param AxisIndex		Index of the axis/analog to bind
- L46 _public function_ `FRawInputDataDelegate& GetDataReceivedHandler()` — Returns the delegate for a data received handler
- L54 _public function_ `virtual void SetAnalogAxisIsInverted(int32 DeviceHandle, int32 AxisIndex, bool bInvert)` — Set whether an axis is inverted @param DeviceHandle	Handle to the device on which to set the axis inverted. @param AxisIndex		Index of the axis entry to set. If INDEX_NONE all will be set. @param bInvert		Whether the axis is to have its value inverted or not
- L62 _public function_ `virtual void SetAnalogAxisOffset(int32 DeviceHandle, int32 AxisIndex, float Offset)` — Sets the offset of the given axis @param DeviceHandle	Handle to the device on which to set the offset @param AxisIndex		Index of the axis to set. If INDEX_NONE all will be set. @param Offset		Value to offset the normalized (and optionally inverted) value by
- L67 _protected member_ `FRawInputDataDelegate DataReceivedHandler;` — Delegate to allow for manual parsing of HID data.
- L70 _protected member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;` — Handler to send all messages to.
- L73 _protected function_ `int32 GetNextInputHandle()` — Helper to get next input handle to assign.
- L77 _private member_ `int32 LastAssignedInputHandle;`

#### class `FRawInputPlugin`  
`class FRawInputPlugin : public IInputDeviceModule`  
_L80-100_
- inherits: `IInputDeviceModule`
- L82 _private prototype_ `virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;`
- L84 _private member_ `TSharedPtr< class IRawInput > RawInputDevice;`
- L87 _public function_ `TSharedPtr< class IRawInput >& GetRawInputDevice()`
- L89 _public prototype_ `virtual void StartupModule() override;`
- L91 _public function_ `static inline FRawInputPlugin& Get()`
- L96 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FRawInputDataDelegate, int32 , const struct tagRAWINPUT* );`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FRawInputDataDelegate, int32 , const struct tagRAWINPUT* );`

### `Plugins/Experimental/RawInput/Source/RawInput/Public/RawInputFunctionLibrary.h` (Public)


#### struct `FRawInputKeyNames`  
`struct FRawInputKeyNames`  
_L11-134_
- L13 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis1;`
- L14 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis2;`
- L15 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis3;`
- L16 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis4;`
- L17 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis5;`
- L18 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis6;`
- L19 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis7;`
- L20 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis8;`
- L21 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis9;`
- L22 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis10;`
- L23 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis11;`
- L24 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis12;`
- L25 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis13;`
- L26 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis14;`
- L27 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis15;`
- L28 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis16;`
- L29 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis17;`
- L30 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis18;`
- L31 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis19;`
- L32 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis20;`
- L33 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis21;`
- L34 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis22;`
- L35 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis23;`
- L36 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Axis24;`
- L38 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button1;`
- L39 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button2;`
- L40 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button3;`
- L41 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button4;`
- L42 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button5;`
- L43 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button6;`
- L44 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button7;`
- L45 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button8;`
- L46 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button9;`
- L47 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button10;`
- L48 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button11;`
- L49 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button12;`
- L50 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button13;`
- L51 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button14;`
- L52 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button15;`
- L53 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button16;`
- L54 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button17;`
- L55 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button18;`
- L56 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button19;`
- L57 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button20;`
- L58 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button21;`
- L59 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button22;`
- L60 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button23;`
- L61 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button24;`
- L62 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button25;`
- L63 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button26;`
- L64 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button27;`
- L65 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button28;`
- L66 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button29;`
- L67 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button30;`
- L68 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button31;`
- L69 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button32;`
- L70 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button33;`
- L71 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button34;`
- L72 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button35;`
- L73 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button36;`
- L74 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button37;`
- L75 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button38;`
- L76 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button39;`
- L77 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button40;`
- L78 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button41;`
- L79 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button42;`
- L80 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button43;`
- L81 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button44;`
- L82 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button45;`
- L83 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button46;`
- L84 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button47;`
- L85 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button48;`
- L86 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button49;`
- L87 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button50;`
- L88 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button51;`
- L89 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button52;`
- L90 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button53;`
- L91 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button54;`
- L92 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button55;`
- L93 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button56;`
- L94 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button57;`
- L95 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button58;`
- L96 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button59;`
- L97 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button60;`
- L98 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button61;`
- L99 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button62;`
- L100 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button63;`
- L101 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button64;`
- L102 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button65;`
- L103 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button66;`
- L104 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button67;`
- L105 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button68;`
- L106 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button69;`
- L107 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button70;`
- L108 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button71;`
- L109 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button72;`
- L110 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button73;`
- L111 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button74;`
- L112 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button75;`
- L113 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button76;`
- L114 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button77;`
- L115 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button78;`
- L116 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button79;`
- L117 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button80;`
- L118 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button81;`
- L119 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button82;`
- L120 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button83;`
- L121 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button84;`
- L122 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button85;`
- L123 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button86;`
- L124 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button87;`
- L125 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button88;`
- L126 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button89;`
- L127 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button90;`
- L128 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button91;`
- L129 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button92;`
- L130 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button93;`
- L131 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button94;`
- L132 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button95;`
- L133 _public member_ `static const FGamepadKeyNames::Type GenericUSBController_Button96;`

#### struct `FRawInputKeys`  
`struct FRawInputKeys`  
_L136-260_
- L138 _public member_ `static const FKey GenericUSBController_Axis1;`
- L139 _public member_ `static const FKey GenericUSBController_Axis2;`
- L140 _public member_ `static const FKey GenericUSBController_Axis3;`
- L141 _public member_ `static const FKey GenericUSBController_Axis4;`
- L142 _public member_ `static const FKey GenericUSBController_Axis5;`
- L143 _public member_ `static const FKey GenericUSBController_Axis6;`
- L144 _public member_ `static const FKey GenericUSBController_Axis7;`
- L145 _public member_ `static const FKey GenericUSBController_Axis8;`
- L146 _public member_ `static const FKey GenericUSBController_Axis9;`
- L147 _public member_ `static const FKey GenericUSBController_Axis10;`
- L148 _public member_ `static const FKey GenericUSBController_Axis11;`
- L149 _public member_ `static const FKey GenericUSBController_Axis12;`
- L150 _public member_ `static const FKey GenericUSBController_Axis13;`
- L151 _public member_ `static const FKey GenericUSBController_Axis14;`
- L152 _public member_ `static const FKey GenericUSBController_Axis15;`
- L153 _public member_ `static const FKey GenericUSBController_Axis16;`
- L154 _public member_ `static const FKey GenericUSBController_Axis17;`
- L155 _public member_ `static const FKey GenericUSBController_Axis18;`
- L156 _public member_ `static const FKey GenericUSBController_Axis19;`
- L157 _public member_ `static const FKey GenericUSBController_Axis20;`
- L158 _public member_ `static const FKey GenericUSBController_Axis21;`
- L159 _public member_ `static const FKey GenericUSBController_Axis22;`
- L160 _public member_ `static const FKey GenericUSBController_Axis23;`
- L161 _public member_ `static const FKey GenericUSBController_Axis24;`
- L163 _public member_ `static const FKey GenericUSBController_Button1;`
- L164 _public member_ `static const FKey GenericUSBController_Button2;`
- L165 _public member_ `static const FKey GenericUSBController_Button3;`
- L166 _public member_ `static const FKey GenericUSBController_Button4;`
- L167 _public member_ `static const FKey GenericUSBController_Button5;`
- L168 _public member_ `static const FKey GenericUSBController_Button6;`
- L169 _public member_ `static const FKey GenericUSBController_Button7;`
- L170 _public member_ `static const FKey GenericUSBController_Button8;`
- L171 _public member_ `static const FKey GenericUSBController_Button9;`
- L172 _public member_ `static const FKey GenericUSBController_Button10;`
- L173 _public member_ `static const FKey GenericUSBController_Button11;`
- L174 _public member_ `static const FKey GenericUSBController_Button12;`
- L175 _public member_ `static const FKey GenericUSBController_Button13;`
- L176 _public member_ `static const FKey GenericUSBController_Button14;`
- L177 _public member_ `static const FKey GenericUSBController_Button15;`
- L178 _public member_ `static const FKey GenericUSBController_Button16;`
- L179 _public member_ `static const FKey GenericUSBController_Button17;`
- L180 _public member_ `static const FKey GenericUSBController_Button18;`
- L181 _public member_ `static const FKey GenericUSBController_Button19;`
- L182 _public member_ `static const FKey GenericUSBController_Button20;`
- L183 _public member_ `static const FKey GenericUSBController_Button21;`
- L184 _public member_ `static const FKey GenericUSBController_Button22;`
- L185 _public member_ `static const FKey GenericUSBController_Button23;`
- L186 _public member_ `static const FKey GenericUSBController_Button24;`
- L187 _public member_ `static const FKey GenericUSBController_Button25;`
- L188 _public member_ `static const FKey GenericUSBController_Button26;`
- L189 _public member_ `static const FKey GenericUSBController_Button27;`
- L190 _public member_ `static const FKey GenericUSBController_Button28;`
- L191 _public member_ `static const FKey GenericUSBController_Button29;`
- L192 _public member_ `static const FKey GenericUSBController_Button30;`
- L193 _public member_ `static const FKey GenericUSBController_Button31;`
- L194 _public member_ `static const FKey GenericUSBController_Button32;`
- L195 _public member_ `static const FKey GenericUSBController_Button33;`
- L196 _public member_ `static const FKey GenericUSBController_Button34;`
- L197 _public member_ `static const FKey GenericUSBController_Button35;`
- L198 _public member_ `static const FKey GenericUSBController_Button36;`
- L199 _public member_ `static const FKey GenericUSBController_Button37;`
- L200 _public member_ `static const FKey GenericUSBController_Button38;`
- L201 _public member_ `static const FKey GenericUSBController_Button39;`
- L202 _public member_ `static const FKey GenericUSBController_Button40;`
- L203 _public member_ `static const FKey GenericUSBController_Button41;`
- L204 _public member_ `static const FKey GenericUSBController_Button42;`
- L205 _public member_ `static const FKey GenericUSBController_Button43;`
- L206 _public member_ `static const FKey GenericUSBController_Button44;`
- L207 _public member_ `static const FKey GenericUSBController_Button45;`
- L208 _public member_ `static const FKey GenericUSBController_Button46;`
- L209 _public member_ `static const FKey GenericUSBController_Button47;`
- L210 _public member_ `static const FKey GenericUSBController_Button48;`
- L211 _public member_ `static const FKey GenericUSBController_Button49;`
- L212 _public member_ `static const FKey GenericUSBController_Button50;`
- L213 _public member_ `static const FKey GenericUSBController_Button51;`
- L214 _public member_ `static const FKey GenericUSBController_Button52;`
- L215 _public member_ `static const FKey GenericUSBController_Button53;`
- L216 _public member_ `static const FKey GenericUSBController_Button54;`
- L217 _public member_ `static const FKey GenericUSBController_Button55;`
- L218 _public member_ `static const FKey GenericUSBController_Button56;`
- L219 _public member_ `static const FKey GenericUSBController_Button57;`
- L220 _public member_ `static const FKey GenericUSBController_Button58;`
- L221 _public member_ `static const FKey GenericUSBController_Button59;`
- L222 _public member_ `static const FKey GenericUSBController_Button60;`
- L223 _public member_ `static const FKey GenericUSBController_Button61;`
- L224 _public member_ `static const FKey GenericUSBController_Button62;`
- L225 _public member_ `static const FKey GenericUSBController_Button63;`
- L226 _public member_ `static const FKey GenericUSBController_Button64;`
- L227 _public member_ `static const FKey GenericUSBController_Button65;`
- L228 _public member_ `static const FKey GenericUSBController_Button66;`
- L229 _public member_ `static const FKey GenericUSBController_Button67;`
- L230 _public member_ `static const FKey GenericUSBController_Button68;`
- L231 _public member_ `static const FKey GenericUSBController_Button69;`
- L232 _public member_ `static const FKey GenericUSBController_Button70;`
- L233 _public member_ `static const FKey GenericUSBController_Button71;`
- L234 _public member_ `static const FKey GenericUSBController_Button72;`
- L235 _public member_ `static const FKey GenericUSBController_Button73;`
- L236 _public member_ `static const FKey GenericUSBController_Button74;`
- L237 _public member_ `static const FKey GenericUSBController_Button75;`
- L238 _public member_ `static const FKey GenericUSBController_Button76;`
- L239 _public member_ `static const FKey GenericUSBController_Button77;`
- L240 _public member_ `static const FKey GenericUSBController_Button78;`
- L241 _public member_ `static const FKey GenericUSBController_Button79;`
- L242 _public member_ `static const FKey GenericUSBController_Button80;`
- L243 _public member_ `static const FKey GenericUSBController_Button81;`
- L244 _public member_ `static const FKey GenericUSBController_Button82;`
- L245 _public member_ `static const FKey GenericUSBController_Button83;`
- L246 _public member_ `static const FKey GenericUSBController_Button84;`
- L247 _public member_ `static const FKey GenericUSBController_Button85;`
- L248 _public member_ `static const FKey GenericUSBController_Button86;`
- L249 _public member_ `static const FKey GenericUSBController_Button87;`
- L250 _public member_ `static const FKey GenericUSBController_Button88;`
- L251 _public member_ `static const FKey GenericUSBController_Button89;`
- L252 _public member_ `static const FKey GenericUSBController_Button90;`
- L253 _public member_ `static const FKey GenericUSBController_Button91;`
- L254 _public member_ `static const FKey GenericUSBController_Button92;`
- L255 _public member_ `static const FKey GenericUSBController_Button93;`
- L256 _public member_ `static const FKey GenericUSBController_Button94;`
- L257 _public member_ `static const FKey GenericUSBController_Button95;`
- L258 _public member_ `static const FKey GenericUSBController_Button96;`

#### struct `FRegisteredDeviceInfo`  
`struct FRegisteredDeviceInfo`  
_L263-281_
- reflection: `USTRUCT(BlueprintType)`
- L268 _public member_ `int32 Handle = 0;` — `UPROPERTY(BlueprintReadOnly, Category="RawInput")`
- L272 _public member_ `int32 VendorID = 0;` — `UPROPERTY(BlueprintReadOnly, Category="RawInput")` — Integer representation of the vendor ID (e.g. 0xC262 = 49762)
- L276 _public member_ `int32 ProductID = 0;` — `UPROPERTY(BlueprintReadOnly, Category="RawInput")` — Integer representation of the product ID (e.g. 0xC262 = 49762)
- L280 _public member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category="RawInput")` — Driver supplied device name

#### class `URawInputFunctionLibrary`  
`class URawInputFunctionLibrary : public UBlueprintFunctionLibrary`  
_L284-291_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L290 _public prototype_ `static TArray<FRegisteredDeviceInfo> GetRegisteredDevices();` — `UFUNCTION(BlueprintPure, Category="RawInput")`

### `Plugins/Experimental/RawInput/Source/RawInput/Public/RawInputSettings.h` (Public)


#### struct `FRawInputDeviceAxisProperties`  
`struct FRawInputDeviceAxisProperties`  
_L12-43_
- reflection: `USTRUCT()`
- L16 _public function_ `FRawInputDeviceAxisProperties() : bEnabled(true) , bInverted(false) , bGamepadStick(false) , Offset(0.f)`
- L26 _public member_ `uint8 bEnabled:1;` — `UPROPERTY(EditAnywhere, Category="Axis Properties")` — Whether the axis is enabled.
- L30 _public member_ `FKey Key;` — `UPROPERTY(EditAnywhere, Category="Axis Properties", meta=(EditCondition="bEnabled"))` — Which key to emit the values from this axis to.
- L34 _public member_ `uint8 bInverted:1;` — `UPROPERTY(EditAnywhere, Category="Axis Properties", meta=(EditCondition="bEnabled"))` — Whether the value of the axis as supplied from the driver should be inverted.
- L38 _public member_ `uint8 bGamepadStick:1;` — `UPROPERTY(EditAnywhere, Category="Axis Properties", meta=(EditCondition="bEnabled"))` — Whether this is a gamepad stick, which means it should scale from -1 to 1 instead of 0 to 1
- L42 _public member_ `float Offset;` — `UPROPERTY(EditAnywhere, Category="Axis Properties", meta=(EditCondition="bEnabled"))` — The amount to offset the axis value by to get the desired range (note that this offset is applied after the value has been inverted).

#### struct `FRawInputDeviceButtonProperties`  
`struct FRawInputDeviceButtonProperties`  
_L46-62_
- reflection: `USTRUCT()`
- L50 _public function_ `FRawInputDeviceButtonProperties() : bEnabled(true)`
- L57 _public member_ `uint8 bEnabled:1;` — `UPROPERTY(EditAnywhere, Category="Button Properties")` — Whether the button is enabled.
- L61 _public member_ `FKey Key;` — `UPROPERTY(EditAnywhere, Category="Button Properties", meta=(EditCondition="bEnabled"))` — Which key to emit the values from this button to.

#### struct `FRawInputDeviceConfiguration`  
`struct FRawInputDeviceConfiguration`  
_L65-84_
- reflection: `USTRUCT()`
- L69 _public prototype_ `FRawInputDeviceConfiguration();`
- L73 _public member_ `FString VendorID;` — `UPROPERTY(EditAnywhere, Category="Device Config")` — The hexadecimal vendor ID in string form (e.g. 0x046D). If this is empty, will match all vendors
- L77 _public member_ `FString ProductID;` — `UPROPERTY(EditAnywhere, Category="Device Config")` — The hexadecimal product ID in string form (e.g. 0xC262). If this is empty, will match all products
- L80 _public member_ `TArray<FRawInputDeviceAxisProperties> AxisProperties;` — `UPROPERTY(EditAnywhere, Category="Device Config")`
- L83 _public member_ `TArray<FRawInputDeviceButtonProperties> ButtonProperties;` — `UPROPERTY(EditAnywhere, Category="Device Config")`

#### class `URawInputSettings`  
`class URawInputSettings : public UDeveloperSettings`  
_L87-113_
- reflection: `UCLASS(config=Input, defaultconfig)`
- inherits: `UDeveloperSettings`
- L95 _public prototype_ `virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& PropertyChangedEvent ) override;`
- L100 _public prototype_ `virtual FName GetCategoryName() const override;`
- L102 _public prototype_ `virtual FText GetSectionText() const override;`
- L108 _public member_ `TArray<FRawInputDeviceConfiguration> DeviceConfigurations;` — `UPROPERTY(config, EditAnywhere, Category="Device Configurations")` — List of bindings to apply based on Vendor and Product Id, these are applied in order. To set a default, add an entry with empty product/vendor id at the end of the array
- L112 _public member_ `bool bRegisterDefaultDevice = true;` — `UPROPERTY(config, EditAnywhere, Category="Device Configurations")` — Whether the plugin should try to register a default device to handle generic gamepads and joysticks

### `Plugins/Experimental/RawInput/Source/RawInput/Public/Windows/RawInputWindows.h` (Public)


#### struct `FDLLPointers`  
`struct FDLLPointers`  
_L24-56_
- desc: Helper class to provide an interface into the HID API via the DLL
- L29 _public typedef_ `typedef bool(WINAPI *HidD_GetSerialNumberStringType)(HANDLE device, PVOID buffer, uint32 buffer_len);` — typedefs for the functions we want
- L30 _public typedef_ `typedef bool(WINAPI *HidD_GetManufacturerStringType)(HANDLE handle, PVOID buffer, uint32 buffer_len);`
- L31 _public typedef_ `typedef bool(WINAPI *HidD_GetProductStringType)(HANDLE handle, PVOID buffer, uint32 buffer_len);`
- L32 _public typedef_ `typedef int32(WINAPI *HidP_GetValueCapsType)(HIDP_REPORT_TYPE ReportType, PHIDP_VALUE_CAPS ValueCaps, uint16* ValueCapsLength, PHIDP_PREPARSED_DATA PreparsedData);`
- L33 _public typedef_ `typedef int32(WINAPI *HidP_GetButtonCapsType)(HIDP_REPORT_TYPE ReportType, PHIDP_BUTTON_CAPS ButtonCaps, uint16* ButtonCapsLength, PHIDP_PREPARSED_DATA PreparsedData);`
- L34 _public typedef_ `typedef int32(WINAPI *HidP_GetCapsType)(PHIDP_PREPARSED_DATA PreparsedData, PHIDP_CAPS Capabilities);`
- L35 _public typedef_ `typedef int32(WINAPI *HidP_GetUsagesType)(HIDP_REPORT_TYPE ReportType, uint16 UsagePage, uint16 LinkCollection, uint16* UsageList, uint32* UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, uint32 ReportLength);`
- L36 _public typedef_ `typedef int32(WINAPI *HidP_GetUsageValueType)(HIDP_REPORT_TYPE ReportType, uint16 UsagePage, uint16 LinkCollection, uint16 Usage, uint32* UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, uint32 ReportLength);`
- L38 _public prototype_ `FDLLPointers();`
- L39 _public prototype_ `virtual ~FDLLPointers();`
- L42 _public prototype_ `bool InitFuncPointers();` — Initialize the function pointers
- L45 _public member_ `void* HIDDLLHandle;` — Handle to the DLL
- L48 _public member_ `HidD_GetSerialNumberStringType HidD_GetSerialNumberString;` — Function pointers to the functions within the DLL.
- L49 _public member_ `HidD_GetManufacturerStringType HidD_GetManufacturerString;`
- L50 _public member_ `HidD_GetProductStringType HidD_GetProductString;`
- L51 _public member_ `HidP_GetButtonCapsType HidP_GetButtonCaps;`
- L52 _public member_ `HidP_GetValueCapsType HidP_GetValueCaps;`
- L53 _public member_ `HidP_GetCapsType HidP_GetCaps;`
- L54 _public member_ `HidP_GetUsagesType HidP_GetUsages;`
- L55 _public member_ `HidP_GetUsageValueType HidP_GetUsageValue;`

#### struct `FRawInputRegisteredDevice`  
`struct FRawInputRegisteredDevice`  
_L58-102_
- L60 _public function_ `FRawInputRegisteredDevice() : bIsValid(false)`
- L65 _public function_ `FRawInputRegisteredDevice(const int32 InDeviceType, const uint16 InUsage, const int16 InUsagePage, const HANDLE _handle) : hDevice(_handle) , VendorID(0) , ProductID(0) , DeviceType(InDeviceType) , Usage(InUsage) , UsagePage(InUsagePage) , bIsValid(true)`
- L76 _public function_ `bool operator==(const FRawInputRegisteredDevice& Other) const`
- L88 _public member_ `FString DeviceName;` — Driver supplied device name
- L89 _public member_ `HANDLE hDevice;`
- L92 _public member_ `int32 VendorID;` — Device identifiers
- L93 _public member_ `int32 ProductID;`
- L96 _public member_ `int32 DeviceType;` — HIDP device values
- L97 _public member_ `uint16 Usage;`
- L98 _public member_ `uint16 UsagePage;`
- L101 _public member_ `uint8 bIsValid:1;` — Whether the data has been populated

#### struct `FAnalogData`  
`struct FAnalogData`  
_L104-178_
- L106 _public function_ `FAnalogData() : Index(INDEX_NONE) , Value(0.f) , PreviousValue(0.f) , RangeMin(-1.f) , RangeMax(-1.f) , Offset(0.f) , bInverted(false) , bGamepadStick(false)`
- L118 _public function_ `FAnalogData(const int32 InIndex, const float InValue, const float InRangeMin, const float InRangeMax, const float InOffset, const bool bInInverted, const bool bInGamepadStick, const FName InKeyName) : Index(InIndex) , Value(InValue) , PreviousValue(0.f) , RangeMin(InRangeMin) , RangeMax(InRangeMax) , Offset(0.f) , bInverted(bInInverted) , bGamepadStick(bInGamepadStick) , KeyName(InKeyName)`
- L132 _public function_ `float GetValue() const` — Helper function to get the offset and normalized value
- L147 _public function_ `bool HasValue() const` — Whether the data represents a valid value
- L153 _public member_ `int32 Index;` — Index in the value data
- L156 _public member_ `float Value;` — Current analog value
- L159 _public member_ `float PreviousValue;` — Last analog value
- L162 _public member_ `float RangeMin;` — Min Analog value
- L165 _public member_ `float RangeMax;` — Max analog value
- L168 _public member_ `float Offset;` — Offset to apply to normalized axis value
- L171 _public member_ `bool bInverted;` — Is this axis inverted
- L174 _public member_ `bool bGamepadStick;` — Is this axis centered on 0 instead of 0.5
- L177 _public member_ `FName KeyName;` — Key name

#### struct `FButtonData`  
`struct FButtonData`  
_L180-196_
- L182 _public function_ `FButtonData() : bButtonState(false) , bPreviousButtonState(false)`
- L189 _public member_ `uint8 bButtonState:1;` — Current button state
- L192 _public member_ `uint8 bPreviousButtonState:1;` — Button state last update
- L195 _public member_ `FName ButtonName;` — Button name

#### struct `FRawWindowsDeviceEntry`  
`struct FRawWindowsDeviceEntry`  
_L198-219_
- L201 _public prototype_ `FRawWindowsDeviceEntry();`
- L202 _public prototype_ `FRawWindowsDeviceEntry(const FRawInputRegisteredDevice& InDeviceData);`
- L204 _public prototype_ `void InitializeNameArrays();`
- L206 _public member_ `FRawInputRegisteredDevice DeviceData;`
- L209 _public member_ `TArray<FButtonData> ButtonData;` — Button data
- L212 _public member_ `TArray<FAnalogData> AnalogData;` — Analog data
- L215 _public member_ `uint8 bNeedsUpdate:1;` — Device has controller data to send
- L218 _public member_ `uint8 bIsConnected:1;` — Device is connected

#### struct `FConnectedDeviceInfo`  
`struct FConnectedDeviceInfo`  
_L221-235_
- L224 _public function_ `FConnectedDeviceInfo()`
- L225 _public function_ `FConnectedDeviceInfo(FString InDeviceName, const RID_DEVICE_INFO& InRIDDeviceInfo, const HANDLE Handle) : DeviceName(MoveTemp(InDeviceName)) , RIDDeviceInfo(InRIDDeviceInfo) , hDevice(Handle)`
- L232 _public member_ `FString DeviceName;`
- L233 _public member_ `RID_DEVICE_INFO RIDDeviceInfo;`
- L234 _public member_ `HANDLE hDevice;`

#### class `FRawInputWindows`  
`class FRawInputWindows : public IRawInput, IWindowsMessageHandler`  
_L237-325_
- inherits: `IRawInput,IWindowsMessageHandler`
- L241 _public prototype_ `FRawInputWindows(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);`
- L243 _public prototype_ `virtual ~FRawInputWindows();`
- L246 _public prototype_ `virtual void QueryConnectedDevices() override;`
- L247 _public prototype_ `virtual int32 RegisterInputDevice(int32 DeviceType, int32 Flags, uint16 DeviceID, int16 PageID, HANDLE Handle) override;`
- L248 _public prototype_ `virtual void RemoveRegisteredInputDevice(int32 DeviceHandle) override;`
- L249 _public prototype_ `virtual void BindButtonForDevice(int32 DeviceHandle, FName EventName, int32 ButtonIndex ) override;`
- L250 _public prototype_ `virtual void BindAnalogForDevice(int32 DeviceHandle, FName EventName, int32 AxisIndex ) override;`
- L251 _public prototype_ `virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;`
- L252 _public prototype_ `virtual void SetAnalogAxisIsInverted(int32 DeviceHandle, int32 AxisIndex, bool bInvert) override;`
- L253 _public prototype_ `virtual void SetAnalogAxisOffset(int32 DeviceHandle, int32 AxisIndex, float Offset) override;`
- L257 _public function_ `virtual void Tick(float DeltaTime) override`
- L258 _public prototype_ `virtual void SendControllerEvents() override;`
- L259 _public function_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override`
- L260 _public function_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override`
- L261 _public function_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L265 _public prototype_ `virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override;`
- L269 _public function_ `FRawInputDataDelegate& GetFilteredInputDataHandler()` — Get the delegate for raw data can be handled manually.
- L272 _public prototype_ `FString GetErrorString(int32 StatusCode) const;` — Return a string for the error of a given status code.
- L275 _public prototype_ `FRegisteredDeviceInfo GetDeviceInfo(int32 DeviceHandle) const;` — Returns user facing data for a registered device.
- L280 _private prototype_ `void ShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);` — Adds on screen messages for the buttons stats and analog values when "ShowDebug RawInput" has been specified via the console.
- L283 _private prototype_ `void ShowDeviceInfo(const FConnectedDeviceInfo& DeviceInfo) const;` — Dumps the properties of a RID_DEVICE_INFO struct to the log.
- L290 _private prototype_ `void SetupBindings(int32 DeviceHandle, bool bApplyDefaults);` — Sets up the bindings for the specified device. @param DeviceHandle		The handle to the device to setup @param bApplyDefaults	Whether to setup default bindings if no entry is found in the Raw Input Settings device configurations.
- L293 _private prototype_ `void ParseInputData(int32 Handle, const RAWINPUT* RawInputData, PHIDP_PREPARSED_DATA Data, const HIDP_CAPS& Capabilities);` — Parse raw input data.
- L296 _private prototype_ `static bool CompareDeviceInfo(const RID_DEVICE_INFO& DeviceInfo, const FRawInputRegisteredDevice& OtherInfo);` — Compare a RID_DEVICE_INFO structure with a FRawInputRegisteredDevice one.
- L299 _private prototype_ `static void CopyConnectedDeviceInfo(FRawWindowsDeviceEntry& RegisteredDevice, const FConnectedDeviceInfo* ConnectedDevice);` — Updates a raw device with connected device info, if null will reset data
- L302 _private prototype_ `int32 FindRegisteredDeviceHandle(const FRawInputRegisteredDevice& InDeviceData) const;` — Returns the handle to a registered device or INDEX_NONE if the device doesn't exist.
- L305 _private member_ `FRawInputDataDelegate FilteredInputDataHandler;` — Handler for filtered raw data (i.e. only devices we registered via RegisterInputDevice)
- L308 _private member_ `TArray<FConnectedDeviceInfo> ConnectedDeviceInfoList;` — List of connected devices populated by GetRawInputDeviceList.
- L311 _private member_ `TMap<int32, FRawWindowsDeviceEntry> RegisteredDeviceList;` — Map of device handles to details of registered devices
- L314 _private member_ `FDLLPointers DLLPointers;` — Structure for HID DLL interaction.
- L317 _private member_ `int32 DefaultDeviceHandle;` — Handle to the default device.
- L320 _private member_ `TArray<uint8> PreParsedData;` — Private resizable memory blocks for API calls
- L321 _private member_ `TArray<char> DeviceNameBuffer;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define MAX_NUM_CONTROLLER_BUTTONS 96`
- L15 _macro_ `#define MAX_NUM_CONTROLLER_ANALOG 24`
- L16 _macro_ `#define RAW_INPUT_ERROR (uint32)(-1)`
- L327 _typedef_ `typedef FRawInputWindows FPlatformRawInput;`
