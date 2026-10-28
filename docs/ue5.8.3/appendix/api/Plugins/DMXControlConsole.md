# Plugins / DMXControlConsole

- module root: `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole`
- headers: 19; symbols: 359
- symbol kinds: class=19, delegate=5, enum=2, enumerator=7, function=83, member=83, prototype=158, struct=2
- PrivateDependencyModuleNames: CoreUObject, DMXGDTF, DMXProtocol, DMXRuntime, Engine
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsole.h` (Internal)


#### class `UDMXControlConsole`  
`class UDMXControlConsole : public UObject`  
_L20-65_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: DMX Control Console. A DMX control console that can send DMX to output ports.
- L27 _public prototype_ `UDMXControlConsole();` — Constructor
- L30 _public function_ `UDMXControlConsoleData* GetControlConsoleData() const` — Gets the Control Console data used in this console
- L33 _public prototype_ `void CopyControlConsoleData(UDMXControlConsoleData* InControlConsoleData);` — Copies the provided Control Console Data into this instance
- L37 _public function_ `DECLARE_EVENT_OneParam(UDMXControlConsole, FDMXControlConsoleSavedEvent, const UDMXControlConsole*) FDMXControlConsoleSavedEvent& GetOnControlConsoleSaved()` — Returns an event that is broadcast when the control console asset is saved
- L44 _public member_ `TObjectPtr<UDMXControlConsoleEditorLayoutsBase> ControlConsoleEditorLayouts;` — `UPROPERTY()` — Control Console Editor Layouts reference
- L48 _public member_ `TObjectPtr<UDMXControlConsoleEditorDataBase> ControlConsoleEditorData;` — `UPROPERTY()` — Control Console Editor Data reference
- L53 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L59 _private member_ `TObjectPtr<UDMXControlConsoleData> ControlConsoleData;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Control Console")` — Control Console Data reference
- L63 _private member_ `FDMXControlConsoleSavedEvent OnControlConsoleSaved;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_EVENT_OneParam(UDMXControlConsole, FDMXControlConsoleSavedEvent, const UDMXControlConsole*) FDMXControlConsoleSavedEvent& GetOnControlConsoleSaved() { return OnControlConsoleSaved; } #endif` — Returns an event that is broadcast when the control console asset is saved

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleActor.h` (Internal)


#### class `ADMXControlConsoleActor`  
`class ADMXControlConsoleActor : public AActor`  
_L15-101_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `AActor`
- desc: Actor class for DMX Control Console
- L22 _public prototype_ `ADMXControlConsoleActor();` — Constructor
- L25 _public prototype_ `void SetDMXControlConsoleData(UDMXControlConsoleData* InDMXControlConsoleData);` — Sets the Control Console Data used in this actor
- L28 _public function_ `UDMXControlConsoleData* GetControlConsoleData() const` — Returns the Control Console Data used for this actor
- L32 _public prototype_ `void StartSendingDMX();` — `UFUNCTION(BlueprintCallable, Category = "DMX Control Console")` — Sets the current DMX Control Console to start sending DMX data
- L36 _public prototype_ `void StopSendingDMX();` — `UFUNCTION(BlueprintCallable, Category = "DMX Control Console")` — Sets the current DMX Control Console to stop sending DMX data
- L40 _public prototype_ `void PauseSendingDMX();` — `UFUNCTION(BlueprintCallable, Category = "DMX Control Console")` — Sets the current DMX Control Console to pause sending DMX data
- L44 _public prototype_ `void ResetToDefault();` — `UFUNCTION(BlueprintCallable, Category = "DMX Control Console")` — Resets all the faders in this Control Console to their default values
- L48 _public prototype_ `void ResetToZero();` — `UFUNCTION(BlueprintCallable, Category = "DMX Control Console")` — Resets all the faders in this Control Console to zero
- L52 _public function_ `static FSimpleMulticastDelegate& GetOnControlConsoleReset()` — Returns the delegate called when the Control Console has been reset
- L55 _public function_ `static FName GetControlConsoleDataPropertyNameChecked()` — Property name getters
- L56 _public function_ `static FName GetAutoActivatePropertyNameChecked()`
- L57 _public function_ `static FName GetSendDMXInEditorPropertyNameChecked()`
- L62 _protected prototype_ `virtual void PostLoad() override;`
- L63 _protected prototype_ `virtual void BeginPlay() override;`
- L64 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L66 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L73 _private prototype_ `void ApplySendDMXInEditorState();` — Applies the play in editor state. Enables send when auto activate is on, send DMX in editor is enabled and not currently playing
- L78 _private member_ `TObjectPtr<UDMXControlConsoleData> ControlConsoleData;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Control Console")` — The Control Console Data used in this actor
- L82 _private member_ `bool bAutoActivate = true;` — `UPROPERTY(EditAnywhere, Category = "DMX Control Console")` — True if the Control Console should send DMX data in runtime
- L87 _private member_ `bool bSendDMXInEditor = false;` — `UPROPERTY(EditAnywhere, Category = "DMX Control Console", Meta = (DisplayName = "Send DMX in Editor"))` — True if the Control Console should send DMX data in Editor
- L92 _private member_ `static FSimpleMulticastDelegate OnControlConsoleReset;` — Called when the Control Console has been reset
- L95 _private member_ `bool bIsPlayInWorld = false;` — True while the actor plays in a world
- L100 _private member_ `TObjectPtr<USceneComponent> RootSceneComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Actor", AdvancedDisplay, Meta = (AllowPrivateAccess = true))` — Scene component to make the Actor easily visible in Editor

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleCueStack.h` (Internal)


#### struct `FDMXControlConsoleCue`  
`struct FDMXControlConsoleCue`  
_L15-39_
- reflection: `USTRUCT()`
- desc: Struct which describes a cue in the DMX Control Console
- L21 _public member_ `FGuid CueID = FGuid::NewGuid();` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — The unique id of this cue
- L25 _public member_ `FString CueLabel;` — `UPROPERTY()` — The name label of this cue
- L29 _public member_ `FLinearColor CueColor = FLinearColor::Transparent;` — `UPROPERTY()` — The color of this cue
- L33 _public member_ `TMap<TWeakObjectPtr<UDMXControlConsoleFaderBase>, uint32> FaderToValueMap;` — `UPROPERTY()` — A fader object to value map
- L35 _public function_ `bool operator==(const FDMXControlConsoleCue& Other) const`

#### class `UDMXControlConsoleCueStack`  
`class UDMXControlConsoleCueStack : public UObject`  
_L43-115_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A stack of cues in the DMX Control Console
- L58 _public prototype_ `FDMXControlConsoleCue* AddNewCue(const TArray<UDMXControlConsoleFaderBase*>& Faders, const FString CueLabel = TEXT(""), const FLinearColor CueColor = FLinearColor::Transparent);` — Adds a new cue to this stack by using the given faders array @param Faders the array of faders to provide ad cue data. @param CueLabel (optional) the label name of the new cue. @param CueColor (optional) the color used for highlight the cue in the editor. @return Returns a pointer to the newly created cue, or nullptr if no cue could be created.
- L61 _public prototype_ `void RemoveCue(const FDMXControlConsoleCue& Cue);` — Removes the given cue from the stack, if valid
- L64 _public prototype_ `FDMXControlConsoleCue* FindCue(const FGuid CueID);` — Finds the cue with the given unique id in this cue stack
- L67 _public prototype_ `FDMXControlConsoleCue* FindCue(const FString& CueLabel);` — Finds the cue with the given label in this cue stack
- L70 _public prototype_ `void UpdateCueData(const FGuid CueID, const TArray<UDMXControlConsoleFaderBase*>& Faders);` — Updates the given cue with the given faders data if contained by this cue stack
- L73 _public prototype_ `void MoveCueToIndex(const FDMXControlConsoleCue& Cue, const uint32 NewIndex);` — Moves the given Cue to the specified index, if valid
- L76 _public prototype_ `void Recall(const FDMXControlConsoleCue& Cue);` — Recalls the given Cue if contained by this cue stack
- L79 _public function_ `const TArray<FDMXControlConsoleCue>& GetCuesArray() const` — Gets a reference to the cue stack array
- L82 _public prototype_ `void Clear();` — Clears the cues array
- L86 _public function_ `bool CanStore() const` — Returns true if the cues stack can store cue data
- L89 _public prototype_ `void OnFadersPropertiesChanged(FPropertyChangedEvent& PropertyChangedEvent);` — Called when a property of a fader in the console has changed
- L93 _public function_ `FSimpleMulticastDelegate& GetOnCueStackChanged()` — Called when the cue stack has been changed
- L96 _public prototype_ `virtual void PostInitProperties() override;`
- L101 _private prototype_ `FString GenerateUniqueCueLabel(const FString& CueLabel);` — Generates a unique label name for a cue
- L104 _private member_ `FSimpleMulticastDelegate OnCueStackChanged;` — Executed when the cue stack has been changed
- L108 _private member_ `TArray<FDMXControlConsoleCue> CuesArray;` — `UPROPERTY()` — The array of cues
- L113 _private member_ `bool bCanStore = false;` — `UPROPERTY()` — True if the stack can store cues data

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleData.h` (Internal)


#### enum `EDMXControlConsoleStopDMXMode`  
`enum class EDMXControlConsoleStopDMXMode : uint8`  
_L21-26_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `SendDefaultValues UMETA(DisplayName = "Send Default Values")`
- L24 _public enumerator_ `SendZeroValues UMETA(DisplayName = "Send Zero Values")`
- L25 _public enumerator_ `DoNotSendValues UMETA(DisplayName = "Keep Last Mapped Values")`

#### class `UDMXControlConsoleData`  
`class UDMXControlConsoleData : public UObject , public FTickableGameObject`  
_L32-187_
- reflection: `UCLASS()`
- inherits: `UObject,FTickableGameObject`
- desc: This class is responsible to hold all the data of a DMX Control Console
- L43 _public prototype_ `UDMXControlConsoleData();` — Constructor
- L46 _public prototype_ `UDMXControlConsoleFaderGroupRow* AddFaderGroupRow(const int32 RowIndex);` — Adds a Fader Group Row to this DMX Control Console
- L49 _public prototype_ `void DeleteFaderGroupRow(UDMXControlConsoleFaderGroupRow* FaderGroupRow);` — Removes a Fader Group Row from this DMX Control Console
- L52 _public function_ `const TArray<UDMXControlConsoleFaderGroupRow*>& GetFaderGroupRows() const` — Gets this DMX Control Console's Fader Group Rows array
- L55 _public prototype_ `TArray<UDMXControlConsoleFaderGroup*> GetAllFaderGroups() const;` — Gets an array of all Fader Groups in this DMX Control Console
- L58 _public prototype_ `UDMXControlConsoleFaderGroup* FindFaderGroupByFixturePatch(const UDMXEntityFixturePatch* InFixturePatch) const;` — Returns the Fader Group matching the given Fixture Patch or nullptr if it's no longer valid.
- L61 _public prototype_ `void GenerateFromDMXLibrary();` — Generates sorted Fader Groups based on the DMX Control Console's current DMX Library
- L64 _public function_ `UDMXLibrary* GetDMXLibrary() const` — Gets this DMX Control Console's DMX Library
- L67 _public function_ `UDMXControlConsoleCueStack* GetCueStack() const` — Gets this DMX Control Console's Cue Stack
- L70 _public prototype_ `void StartSendingDMX();` — Sends DMX on this DMX Control Console on tick
- L73 _public prototype_ `void StopSendingDMX();` — Stops DMX on this DMX Control Console on tick
- L76 _public prototype_ `void PauseSendingDMX();` — Puses DMX data sending on this DMX Control Console
- L79 _public function_ `bool IsSendingDMX() const` — Gets if DMX is sending DMX data or not
- L82 _public function_ `bool IsPausedDMX() const` — Gets if DMX data sending is paused or not
- L85 _public prototype_ `void SetStopDMXMode(EDMXControlConsoleStopDMXMode NewStopDMXMode);` — Sets the stop DMX mode for this control console
- L88 _public function_ `EDMXControlConsoleStopDMXMode GetStopDMXMode() const` — Gets the current stop DMX mode of this control console
- L91 _public prototype_ `void UpdateOutputPorts(const TArray<FDMXOutputPortSharedRef> InOutputPorts);` — Updates DMX Output Ports
- L94 _public prototype_ `void Clear(bool bOnlyPatchedFaderGroups = false);` — Clears FaderGroupRows array from data
- L97 _public prototype_ `virtual void PostInitProperties() override;`
- L98 _public prototype_ `virtual void PostLoad() override;`
- L100 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L105 _public function_ `FDMXControlConsoleFaderGroupDelegate& GetOnFaderGroupAdded()` — Gets a reference to OnFaderGroupAdded delegate
- L108 _public function_ `FDMXControlConsoleFaderGroupDelegate& GetOnFaderGroupRemoved()` — Gets a reference to OnFaderGroupRemoved delegate
- L111 _public function_ `FSimpleMulticastDelegate& GetOnDMXLibraryReloaded()` — Called when the DMX Library has been reloaded
- L115 _public function_ `FSimpleMulticastDelegate& GetOnDMXLibraryChanged()` — Called when the DMX Library has been changed
- L121 _public member_ `FString FilterString;` — `UPROPERTY()` — The current editor filter string
- L125 _public function_ `static FName GetDMXLibraryPropertyName()` — Property Name getters
- L128 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L129 _public function_ `virtual bool IsTickable() const override`
- L130 _public function_ `virtual bool IsTickableInEditor() const override`
- L131 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L132 _public prototype_ `virtual TStatId GetStatId() const override;`
- L137 _private prototype_ `void ClearAll();` — Clears the DMX Control Console to its default
- L140 _private prototype_ `void ClearPatchedFaderGroups();` — Clears Patched Fader Groups from data
- L143 _private prototype_ `void OnFixturePatchAddedToLibrary(UDMXLibrary* Library, TArray<UDMXEntity*> Entities);` — Called when a Fixture Patch was added to a DMX Library
- L146 _private member_ `FDMXControlConsoleFaderGroupDelegate OnFaderGroupAdded;` — Called when a Fader Group is added to the Control Console
- L149 _private member_ `FDMXControlConsoleFaderGroupDelegate OnFaderGroupRemoved;` — Called when a Fader Group is removed from the Control Console
- L152 _private member_ `FSimpleMulticastDelegate OnDMXLibraryReloadedDelegate;` — Called when the DMX Library has been reloaded
- L156 _private member_ `FSimpleMulticastDelegate OnDMXLibraryChangedDelegate;` — Called when the DMX Library has been changed
- L161 _private member_ `TSoftObjectPtr<UDMXLibrary> SoftDMXLibraryPtr;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "DMX Library", ShowDisplayNames), Category = "DMX Control Console")` — Library used to generate Fader Groups
- L165 _private member_ `TWeakObjectPtr<UDMXLibrary> CachedWeakDMXLibrary;` — `UPROPERTY()` — Cached DMX Library for faster access
- L169 _private member_ `TObjectPtr<UDMXControlConsoleCueStack> CueStack;` — `UPROPERTY()` — The Cue Stack for this DMX Control Console
- L173 _private member_ `TArray<TObjectPtr<UDMXControlConsoleFaderGroupRow>> FaderGroupRows;` — `UPROPERTY()` — DMX Control Console's Fader Group Rows array
- L176 _private member_ `TArray<FDMXOutputPortSharedRef> OutputPorts;` — Output ports to output dmx to
- L179 _private member_ `bool bSendDMX = false;` — True when this object is ticking
- L182 _private member_ `bool bPauseDMX = false;` — True when sending DMX is paused
- L186 _private member_ `EDMXControlConsoleStopDMXMode StopDMXMode = EDMXControlConsoleStopDMXMode::DoNotSendValues;` — `UPROPERTY()` — The stop DMX mode currently in use by the console

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleFaderGroupDelegate, const UDMXControlConsoleFaderGroup*);`
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleFaderGroupDelegate, const UDMXControlConsoleFaderGroup*);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleEditorDataBase.h` (Internal)


#### class `UDMXControlConsoleEditorDataBase`  
`class UDMXControlConsoleEditorDataBase : public UObject`  
_L12-16_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base class for Control Console editor data

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleFaderBase.h` (Internal)


#### class `UDMXControlConsoleFaderBase`  
`class UDMXControlConsoleFaderBase : public UObject , public IDMXControlConsoleFaderGroupElement`  
_L18-182_
- reflection: `UCLASS(Abstract, AutoExpandCategories = ("DMX Fader"))`
- inherits: `UObject,IDMXControlConsoleFaderGroupElement`
- desc: Base class for a Fader in the DMX Control Console.
- L26 _public prototype_ `UDMXControlConsoleFaderBase();` — Constructor
- L29 _public prototype_ `virtual UDMXControlConsoleFaderGroup& GetOwnerFaderGroupChecked() const override;`
- L30 _public prototype_ `virtual UDMXControlConsoleControllerBase* GetElementController() const override;`
- L31 _public prototype_ `virtual void SetElementController(UDMXControlConsoleControllerBase* NewController) override;`
- L32 _public prototype_ `virtual int32 GetIndex() const override;`
- L33 _public function_ `virtual const TArray<UDMXControlConsoleFaderBase*>& GetFaders() const override`
- L34 _public function_ `virtual int32 GetUniverseID() const override`
- L35 _public function_ `virtual int32 GetStartingAddress() const override`
- L36 _public function_ `virtual int32 GetEndingAddress() const override`
- L37 _public prototype_ `virtual void Destroy() override;`
- L41 _public function_ `const FString& GetFaderName() const` — Gets the name of the Fader
- L44 _public prototype_ `virtual void SetFaderName(const FString& NewName);` — Sets the name of the Fader
- L47 _public function_ `virtual EDMXFixtureSignalFormat GetDataType() const` — Gets Fader's Data Type
- L50 _public function_ `uint32 GetDefaultValue() const` — Returns the default value of the fader
- L53 _public function_ `uint32 GetValue() const` — Returns the current value of the fader
- L56 _public prototype_ `virtual void SetValue(uint32 NewValue);` — Sets the current value of the fader
- L59 _public function_ `uint32 GetMinValue() const` — Gets the min value of the fader
- L62 _public prototype_ `virtual void SetMinValue(uint32 NewMinValue);` — Sets Fader's Min Value
- L65 _public function_ `uint32 GetMaxValue() const` — Gets the max value of the fader
- L68 _public prototype_ `virtual void SetMaxValue(uint32 NewMaxValue);` — Sets Fader's Max Value
- L71 _public function_ `bool GetUseLSBMode() const` — Gets wheter this Fader uses LSB mode or not
- L74 _public function_ `bool IsEnabled() const` — True if the Fader can't send DMX data
- L77 _public prototype_ `void SetEnabled(bool bEnable);` — Sets the enable state of this Fader
- L80 _public prototype_ `bool IsLocked() const;` — True if the value of the Fader can't be changed
- L83 _public prototype_ `void SetLocked(bool bLock);` — Sets lock state of this Controller
- L86 _public prototype_ `void ResetToDefault();` — Resets the fader to its default value
- L89 _public prototype_ `virtual void PostInitProperties() override;`
- L90 _public prototype_ `virtual void PostLoad() override;`
- L94 _public function_ `static FName GetFaderNamePropertyName()` — Property Name getters
- L95 _public function_ `static FName GetDataTypePropertyName()`
- L96 _public function_ `static FName GetUniverseIDPropertyName()`
- L97 _public function_ `static FName GetStartingAddressPropertyName()`
- L98 _public function_ `static FName GetEndingAddressPropertyName()`
- L99 _public function_ `static FName GetValuePropertyName()`
- L100 _public function_ `static FName GetMinValuePropertyName()`
- L101 _public function_ `static FName GetMaxValuePropertyName()`
- L102 _public function_ `static FName GetUseLSBModePropertyName()`
- L103 _public function_ `static FName GetIsEnabledPropertyName()`
- L107 _protected prototype_ `virtual void SetUniverseID(int32 InUniversID);` — Sets a new universe ID, checking for its validity
- L110 _protected prototype_ `virtual void SetValueRange();` — Sets min/max range, according to the number of channels
- L113 _protected prototype_ `virtual void SetDataType(EDMXFixtureSignalFormat InDataType);` — Sets this fader's number of channels
- L116 _protected prototype_ `virtual void SetAddressRange(int32 InStartingAddress);` — Sets starting/ending address range, according to the number of channels
- L120 _protected member_ `FString FaderName;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "1"), Category = "DMX Fader")` — Cached Name of the Fader
- L124 _protected member_ `EDMXFixtureSignalFormat DataType;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "2", HideEditConditionToggle, EditCondition = "bCanEditDMXAssignment"), Category = "DMX Fader")` — The number of channels this Fader uses
- L128 _protected member_ `int32 UniverseID = 1;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "3", HideEditConditionToggle, EditCondition = "bCanEditDMXAssignment"), Category = "DMX Fader")` — The universe the should send to fader
- L132 _protected member_ `int32 StartingAddress = 1;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "4", HideEditConditionToggle, EditCondition = "bCanEditDMXAssignment"), Category = "DMX Fader")` — The starting channel Address to send DMX to
- L136 _protected member_ `int32 EndingAddress = 1;` — `UPROPERTY(VisibleAnywhere, meta = (DisplayPriority = "5", HideEditConditionToggle, EditCondition = "bCanEditDMXAssignment"), Category = "DMX Fader")` — The end channel Address to send DMX to
- L140 _protected member_ `uint32 Value = 0;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "6", HideEditConditionToggle, EditCondition = "!bIsLocked"), Category = "DMX Fader")` — The current Fader Value
- L144 _protected member_ `uint32 DefaultValue = 0;` — `UPROPERTY()` — Fader's default Value
- L148 _protected member_ `uint32 MinValue = 0;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "7", HideEditConditionToggle, EditCondition = "!bIsLocked"), Category = "DMX Fader")` — The minimum Fader Value
- L152 _protected member_ `uint32 MaxValue = 255;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "8", HideEditConditionToggle, EditCondition = "!bIsLocked"), Category = "DMX Fader")` — The maximum Fader Value
- L156 _protected member_ `bool bUseLSBMode = false;` — `UPROPERTY(EditAnywhere, meta = (DisplayPriority = "9", HideEditConditionToggle, EditCondition = "bCanEditDMXAssignment"), Category = "DMX Fader")` — Use Least Significant Byte mode. Individual bytes(channels) be interpreted with the first bytes being the lowest part of the number(endianness).
- L160 _protected member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "DMX Fader")` — If true, the Fader doesn't send DMX
- L164 _protected member_ `bool bIsLocked = false;` — `UPROPERTY()` — If true, the value of the Fader can't be changed
- L168 _protected member_ `TSoftObjectPtr<UDMXControlConsoleControllerBase> SoftControllerPtr;` — `UPROPERTY()` — Soft reference to the Controller of this Fader
- L172 _protected member_ `TWeakObjectPtr<UDMXControlConsoleControllerBase> CachedWeakElementController;` — `UPROPERTY(Transient)` — Cached reference to the Controller of this Fader, for fast access
- L175 _protected member_ `TArray<UDMXControlConsoleFaderBase*> ThisFaderAsArray;` — This fader as an array for fast access
- L180 _protected member_ `bool bCanEditDMXAssignment = false;` — `UPROPERTY()` — If true, dmx related properties are editable in the editor

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleFaderGroup.h` (Internal)


#### class `UDMXControlConsoleFaderGroup`  
`class UDMXControlConsoleFaderGroup : public UObject`  
_L27-230_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A Group of Faders in the DMX Control Console
- L35 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleElementDelegate, IDMXControlConsoleFaderGroupElement*);`
- L36 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMXOnFaderGroupFixturePatchChangedDelegate, UDMXControlConsoleFaderGroup*, UDMXEntityFixturePatch*);`
- L40 _public prototype_ `UDMXControlConsoleRawFader* AddRawFader();` — Adds a raw fader to this Fader Group
- L43 _public prototype_ `UDMXControlConsoleFixturePatchFunctionFader* AddFixturePatchFunctionFader(const FDMXFixtureFunction& FixtureFunction, const int32 InUniverseID, const int32 StartingChannel);` — Adds a fixture patch function fader to this Fader Group
- L46 _public prototype_ `UDMXControlConsoleFixturePatchMatrixCell* AddFixturePatchMatrixCell(const FDMXCell& Cell, const int32 InUniverseID, const int32 StartingChannel);` — Adds a fixture patch matrix cell to this Fader Group
- L49 _public prototype_ `void DeleteElement(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& Element);` — Deletes an Element from this Fader Group
- L52 _public prototype_ `void ClearElements();` — Clears all Elements in this Group
- L55 _public prototype_ `TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> GetElements(bool bSortByUniverseAndAddress = false) const;` — Gets the Elements array of this Fader Group
- L58 _public prototype_ `TArray<UDMXControlConsoleFaderBase*> GetAllFaders() const;` — Gets all single faders from the Faders array of this Fader Group
- L61 _public prototype_ `void SortElementsByStartingAddress() const;` — Sorts the array of Elements by their starting address
- L64 _public prototype_ `int32 GetIndex() const;` — Gets this Fader Group's index according to its Fader Group Row owner
- L67 _public prototype_ `UDMXControlConsoleFaderGroupRow& GetOwnerFaderGroupRowChecked() const;` — Gets the owner Fader Group Row of this Fader Group
- L70 _public prototype_ `UDMXControlConsoleControllerBase* GetFaderGroupController() const;` — Gets the Controller of this Fader Group, if valid
- L73 _public prototype_ `void SetFaderGroupController(UDMXControlConsoleControllerBase* NewController);` — Sets the Controller of this Fader Group
- L76 _public function_ `FString GetFaderGroupName() const` — Gets the name of this Fader Group
- L79 _public prototype_ `void SetFaderGroupName(const FString& NewName);` — Sets the name of the Fader Group
- L82 _public prototype_ `void GenerateFromFixturePatch(UDMXEntityFixturePatch* InFixturePatch);` — Automatically generates a Fader Group based on Fixture Patch Ref property
- L85 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Gets the Fixture Patch used by this Fader Group, if valid
- L88 _public prototype_ `void ReloadFixturePatch();` — Reloads the Fixture Patch used by this Fader Group, if valid
- L91 _public prototype_ `bool HasFixturePatch() const;` — Gets wheter this Fader Group is bound to a Fixture Patch
- L94 _public prototype_ `bool HasMatrixProperties() const;` — Gets wheter this Fader Group has Matrix Faders
- L97 _public prototype_ `TMap<int32, TMap<int32, uint8>> GetUniverseToFragmentMap() const;` — Gets a universeID to fragment map for the current list of Raw Faders
- L100 _public prototype_ `TMap<FDMXAttributeName, int32> GetAttributeMap() const;` — Gets an AttributeName to values map for the current list of Fixture Patch Function Faders
- L103 _public prototype_ `TMap<FIntPoint, TMap<FDMXAttributeName, float>> GetMatrixCoordinateToAttributeMap() const;` — Gets a cell coordinate to AttributeName/Value map for the current list of Fixture Patch Matrix Faders
- L106 _public prototype_ `UDMXControlConsoleFaderGroup* Duplicate() const;` — Duplicates this Fader Group if there's no Fixture Patch data
- L109 _public prototype_ `void Clear();` — Clears this Fader Group and all its elements
- L112 _public prototype_ `void Destroy();` — Destroys this Fader Group
- L115 _public function_ `bool IsEnabled() const` — True if the Fader Group can't send DMX data
- L118 _public prototype_ `void SetEnabled(bool bEnable);` — Sets the enable state of this Fader Group
- L122 _public function_ `bool IsMatchingFilter() const` — True if Fader Group matches Control Console filtering system
- L125 _public function_ `void SetIsMatchingFilter(bool bMatches)` — Sets wheter Fader Group matches Control Console filtering system
- L128 _public prototype_ `void ShowAllElementsInEditor();` — Sets in Editor visibility state of all elements to true
- L131 _public prototype_ `bool HasValidData() const;` — Returns true if this fader group contains valid data
- L135 _public prototype_ `virtual void PostInitProperties() override;`
- L136 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L137 _public prototype_ `virtual void PostLoad() override;`
- L141 _public function_ `FDMXControlConsoleElementDelegate& GetOnElementAdded()` — Gets a reference to OnElementAdded delegate
- L144 _public function_ `FDMXControlConsoleElementDelegate& GetOnElementRemoved()` — Gets a reference to OnElementRemoved delegate
- L147 _public function_ `FDMXOnFaderGroupFixturePatchChangedDelegate& GetOnFixturePatchChanged()` — Gets a reference to OnFixturePatchChanged delegate
- L150 _public function_ `static FName GetElementsPropertyName()` — Property Name getters
- L151 _public function_ `static FName GetFaderGroupNamePropertyName()`
- L152 _public function_ `static FName GetFixturePatchRefPropertyName()`
- L153 _public function_ `static FName GetIsEnabledPropertyName()`
- L158 _public member_ `FString FilterString;` — `UPROPERTY()` — Last string from Editor filtering
- L163 _private prototype_ `void OnFixturePatchRemovedFromLibrary(UDMXLibrary* Library, TArray<UDMXEntity*> Entities);` — Called when a Fixture Patch was removed from a DMX Library
- L166 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* InFixturePatch);` — Called when the Fixture Patch is changed inside its DMX Library
- L169 _private prototype_ `void UpdateFaderGroupFromFixturePatch(UDMXEntityFixturePatch* InFixturePatch);` — Updates FaderGroup properties according to the given FixturePatch
- L172 _private prototype_ `void UpdateFixturePatchFunctionFaders(UDMXEntityFixturePatch* InFixturePatch);` — Updates FixtureFunctionFaders properties according to the given FixturePatch
- L175 _private prototype_ `void UpdateFixturePatchMatrixCells(UDMXEntityFixturePatch* InFixturePatch);` — Updates MatrixCells properties according to the given FixturePatch
- L178 _private prototype_ `void SubscribeToFixturePatchDelegates();` — Subscribes this Fader Group to Fixture Patch delegates
- L181 _private prototype_ `void GetNextAvailableUniverseAndAddress(int32& OutUniverse, int32& OutAddress) const;` — Gets the next Universe and Address available for a new fader
- L184 _private member_ `FDMXControlConsoleElementDelegate OnElementAdded;` — Called when an Element is added to the Fader Group
- L187 _private member_ `FDMXControlConsoleElementDelegate OnElementRemoved;` — Called when an Element is removed from the Fader Group
- L190 _private member_ `FDMXOnFaderGroupFixturePatchChangedDelegate OnFixturePatchChangedDelegate;` — Called when Fixture Patch is changed
- L194 _private member_ `FString FaderGroupName;` — `UPROPERTY(EditAnywhere, Category = "DMX Fader Group")` — Name identifier of this Fader Group
- L199 _private member_ `TSoftObjectPtr<UDMXEntityFixturePatch> SoftFixturePatchPtr_DEPRECATED;` — `UPROPERTY()` — Fixture Patch this Fader Group is based on
- L203 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> CachedWeakFixturePatch_DEPRECATED;` — `UPROPERTY(Transient)` — Cached fixture patch for faster access
- L208 _private member_ `FDMXEntityFixturePatchRef FixturePatchRef;` — `UPROPERTY()` — Fixture Patch this Fader Group is based on
- L212 _private member_ `TSoftObjectPtr<UDMXControlConsoleControllerBase> SoftControllerPtr;` — `UPROPERTY()` — Soft reference to the Controller of this Fader Group
- L216 _private member_ `TWeakObjectPtr<UDMXControlConsoleControllerBase> CachedWeakFaderGroupController;` — `UPROPERTY(Transient)` — Cached reference to the Controller of this Fader Group, for fast access
- L220 _private member_ `TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> Elements;` — `UPROPERTY()` — Elements in this Fader Group
- L224 _private member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "DMX Fader Group")` — If true, the Fader Group doesn't send DMX
- L228 _private member_ `bool bIsMatchingFilter = true;` — True if Fader Group matches Control Console filtering system

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleElementDelegate, IDMXControlConsoleFaderGroupElement*);`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMXOnFaderGroupFixturePatchChangedDelegate, UDMXControlConsoleFaderGroup*, UDMXEntityFixturePatch*);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleFaderGroupRow.h` (Internal)


#### class `UDMXControlConsoleFaderGroupRow`  
`class UDMXControlConsoleFaderGroupRow : public UObject`  
_L15-64_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A Row of Fader Groups in the DMX Control Console
- L22 _public prototype_ `UDMXControlConsoleFaderGroup* AddFaderGroup(const int32 Index);` — Adds a new Fader Group to this Fader Group Row
- L25 _public prototype_ `UDMXControlConsoleFaderGroup* AddFaderGroup(UDMXControlConsoleFaderGroup* FaderGroup, const int32 Index);` — Adds the given Fader Group to this Fader Group Row
- L28 _public prototype_ `UDMXControlConsoleFaderGroup* DuplicateFaderGroup(const int32 Index);` — Duplicates the Fader Group at the given index
- L31 _public prototype_ `void DeleteFaderGroup(UDMXControlConsoleFaderGroup* FaderGroup);` — Deletes the given Fader Group. If it's the last Fader Group in this Fader Group Row, requests it to be deleted
- L34 _public prototype_ `void ClearFaderGroups();` — Clears FaderGroups array
- L37 _public function_ `const TArray<UDMXControlConsoleFaderGroup*>& GetFaderGroups() const` — Gets the Fader Group array of this Fader Group Row
- L40 _public prototype_ `int32 GetRowIndex() const;` — Gets the Index of this Row according to the DMX Control Console
- L43 _public prototype_ `UDMXControlConsoleData& GetOwnerControlConsoleDataChecked() const;` — Returns the DMX Control Console Data that owns this row
- L46 _public prototype_ `void Destroy();` — Destroys this Fader Group Row
- L50 _public prototype_ `bool HasValidData() const;` — Returns true if this fader group row contains valid data
- L54 _public prototype_ `virtual void PostLoad() override;`
- L58 _public function_ `static FName GetFaderGroupsPropertyName()` — Property Name getters
- L63 _private member_ `TArray<TObjectPtr<UDMXControlConsoleFaderGroup>> FaderGroups;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Fader Group Row")` — Fader Groups array of this Fader Group Row

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleFixturePatchCellAttributeFader.h` (Internal)


#### class `UDMXControlConsoleFixturePatchCellAttributeFader`  
`class UDMXControlConsoleFixturePatchCellAttributeFader : public UDMXControlConsoleFaderBase`  
_L17-48_
- reflection: `UCLASS()`
- inherits: `UDMXControlConsoleFaderBase`
- desc: A fader matching a Fixture Cell Attribute in the DMX Control Console.
- L24 _public prototype_ `virtual UDMXControlConsoleFaderGroup& GetOwnerFaderGroupChecked() const override;`
- L25 _public prototype_ `virtual int32 GetIndex() const override;`
- L27 _public prototype_ `virtual void SetIsMatchingFilter(bool bMatches) override;`
- L29 _public prototype_ `virtual void Destroy() override;`
- L33 _public prototype_ `void SetPropertiesFromFixtureCellAttribute(const FDMXFixtureCellAttribute& FixtureCellAttribute, const int32 InUniverseID, const int32 StartingChannel);` — Sets Matrix Cell Fader's properties values using the given Fixture Cell Attribute
- L36 _public prototype_ `UDMXControlConsoleFixturePatchMatrixCell& GetOwnerMatrixCellChecked() const;` — Gets the owner Matrix Cell of this Matrix Cell Fader
- L39 _public function_ `const FDMXAttributeName& GetAttributeName() const` — Returns the name of the attribute mapped to this fader
- L42 _public function_ `static FName GetAttributePropertyName()` — Property Name getters
- L47 _private member_ `FDMXAttributeName Attribute;` — `UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Attribute Mapping", DisplayPriority = "2"), Category = "DMX Fader")` — Name of the attribute mapped to this Fader

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleFixturePatchFunctionFader.h` (Internal)


#### class `UDMXControlConsoleFixturePatchFunctionFader`  
`class UDMXControlConsoleFixturePatchFunctionFader : public UDMXControlConsoleFaderBase`  
_L17-60_
- reflection: `UCLASS()`
- inherits: `UDMXControlConsoleFaderBase`
- desc: A fader matching a Fixture Patch Function in the DMX Control Console.
- L24 _public prototype_ `void SetPropertiesFromFixtureFunction(const FDMXFixtureFunction& FixtureFunction, const int32 InUniverseID, const int32 StartingChannel);` — Sets Fader's properties values using the given Fixture Function
- L27 _public function_ `const FDMXAttributeName& GetAttributeName() const` — Returns the name of the attribute mapped to this Fader
- L30 _public function_ `EDMXGDTFPhysicalUnit GetPhysicalUnit() const` — Returns the physical unit of this Fader
- L33 _public function_ `double GetPhysicalFrom() const` — Returns the physical value lower boundary of this Fader
- L36 _public function_ `double GetPhysicalTo() const` — Returns the physical value upper boundary of this Fader
- L39 _public prototype_ `double GetPhysicalValue() const;` — Returns the physical value of this Fader
- L42 _public function_ `static FName GetAttributePropertyName()` — Property Name getters
- L47 _private member_ `FDMXAttributeName Attribute;` — `UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Attribute Mapping", DisplayPriority = "2"), Category = "DMX Fader")` — The Attribute of the Function this Fader is based on
- L51 _private member_ `EDMXGDTFPhysicalUnit PhysicalUnit = EDMXGDTFPhysicalUnit::None;` — `UPROPERTY()` — The Physical Unit of the Function this Fader is based on
- L55 _private member_ `double PhysicalFrom = 0.0;` — `UPROPERTY()` — The lower boundary of the Physical Value range of the Function this Fader is based on
- L59 _private member_ `double PhysicalTo = 1.0;` — `UPROPERTY()` — The upper boundary of the Physical Value range of the Function this Fader is based on

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleFixturePatchMatrixCell.h` (Internal)


#### class `UDMXControlConsoleFixturePatchMatrixCell`  
`class UDMXControlConsoleFixturePatchMatrixCell : public UObject , public IDMXControlConsoleFaderGroupElement`  
_L20-110_
- reflection: `UCLASS()`
- inherits: `UObject,IDMXControlConsoleFaderGroupElement`
- desc: A fader matching a Fixture Patch Matrix Cell in the DMX Control Console.
- L28 _public prototype_ `virtual UDMXControlConsoleFaderGroup& GetOwnerFaderGroupChecked() const override;`
- L29 _public prototype_ `virtual UDMXControlConsoleControllerBase* GetElementController() const override;`
- L30 _public prototype_ `virtual void SetElementController(UDMXControlConsoleControllerBase* NewController) override;`
- L31 _public prototype_ `virtual int32 GetIndex() const override;`
- L32 _public function_ `virtual const TArray<UDMXControlConsoleFaderBase*>& GetFaders() const override`
- L33 _public prototype_ `virtual int32 GetUniverseID() const override;`
- L34 _public prototype_ `virtual int32 GetStartingAddress() const override;`
- L35 _public prototype_ `virtual int32 GetEndingAddress() const override;`
- L37 _public prototype_ `virtual void SetIsMatchingFilter(bool bMatches) override;`
- L39 _public prototype_ `virtual void Destroy() override;`
- L43 _public prototype_ `UDMXControlConsoleFixturePatchCellAttributeFader* AddFixturePatchCellAttributeFader(const FDMXFixtureCellAttribute& CellAttribute, const int32 InUniverseID, const int32 StartingChannel);` — Adds a Matrix Cell Fader to this Matrix Cell
- L46 _public prototype_ `void DeleteCellAttributeFader(UDMXControlConsoleFixturePatchCellAttributeFader* CellAttributeFader);` — Deletes a Matrix Cell Fader from this Matrix Cell
- L49 _public prototype_ `void SetPropertiesFromCell(const FDMXCell& Cell, const int32 InUniverseID, const int32 InStartingChannel);` — Sets Fader's properties values from the given AttributeToChannel map
- L52 _public prototype_ `void SortElementsByStartingAddress() const;` — Sorts the array of Elements by their starting address
- L55 _public function_ `int32 GetCellID() const` — Gets ID index of this Matrix Cell
- L58 _public function_ `int32 GetCellX() const` — Gets X coordinate of this Matrix Cell
- L61 _public function_ `int32 GetCellY() const` — Gets Y coordinate of this Matrix Cell
- L65 _public prototype_ `bool HasVisibleInEditorCellAttributeFaders() const;` — True if there's at least one CellAttributeFader visible in Editor
- L68 _public prototype_ `void ShowAllFadersInEditor();` — Sets in Editor visibility state of all elements to true
- L72 _public prototype_ `virtual void PostLoad() override;`
- L76 _public function_ `static FName GetCellXPropertyName()` — Property Name getters
- L77 _public function_ `static FName GetCellYPropertyName()`
- L78 _public function_ `static FName GetCellAttributeFadersPropertyName()`
- L82 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* InFixturePatch);` — Called when the Fixture Patch is changed inside its DMX Library
- L85 _private prototype_ `void UpdateFixturePatchCellAttributeFaders(UDMXEntityFixturePatch* InFixturePatch);` — Updates CellAttributeFaders properties according to the given FixturePatch
- L89 _private member_ `int32 CellID = 0;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Matrix Cell")` — Cell Index ID
- L93 _private member_ `int32 CellX = 0;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Matrix Cell")` — Cell X coordinate
- L97 _private member_ `int32 CellY = 0;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Matrix Cell")` — Cell Y coordinate
- L101 _private member_ `TSoftObjectPtr<UDMXControlConsoleControllerBase> SoftControllerPtr;` — `UPROPERTY()` — Soft reference to the Controller of this Element
- L105 _private member_ `TWeakObjectPtr<UDMXControlConsoleControllerBase> CachedWeakElementController;` — `UPROPERTY(Transient)` — Cached reference to the Controller of this Element, for fast access
- L109 _private member_ `TArray<TObjectPtr<UDMXControlConsoleFaderBase>> CellAttributeFaders;` — `UPROPERTY(VisibleAnywhere, Category = "DMX Matrix Cell")` — Faders array of this Matrix Cell

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/DMXControlConsoleRawFader.h` (Internal)


#### class `UDMXControlConsoleRawFader`  
`class UDMXControlConsoleRawFader : public UDMXControlConsoleFaderBase`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UDMXControlConsoleFaderBase`
- desc: A fader matching that sends Raw DMX
- L19 _public prototype_ `UDMXControlConsoleRawFader();` — Constructor
- L22 _public function_ `virtual void SetDataType(EDMXFixtureSignalFormat InDataType) override`
- L23 _public function_ `virtual void SetUniverseID(int32 InUniversID) override`
- L24 _public function_ `virtual void SetAddressRange(int32 InStartingAddress) override`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/IDMXControlConsoleFaderGroupElement.h` (Internal)


#### class `UDMXControlConsoleFaderGroupElement`  
`class UDMXControlConsoleFaderGroupElement : public UInterface`  
_L20-24_
- reflection: `UINTERFACE()`
- inherits: `UInterface`
- desc: Interface used by elmeents that can be placed inside a Fixture Group. Note, an Element has to be a set of consecutive channels.

#### class `IDMXControlConsoleFaderGroupElement`  
`class IDMXControlConsoleFaderGroupElement`  
_L26-71_
- L32 _public prototype_ `virtual UDMXControlConsoleFaderGroup& GetOwnerFaderGroupChecked() const = 0;` — Returns the Fader Group this Element resides in
- L35 _public prototype_ `virtual UDMXControlConsoleControllerBase* GetElementController() const = 0;` — Returns the Element Controller of this Element
- L38 _public prototype_ `virtual void SetElementController(UDMXControlConsoleControllerBase* NewController) = 0;` — Sets the Element Controller of this Element
- L41 _public prototype_ `virtual int32 GetIndex() const = 0;` — Returns the index of the Element in the Fader Group
- L44 _public prototype_ `virtual const TArray<UDMXControlConsoleFaderBase*>& GetFaders() const = 0;` — Returns the Faders of this Element
- L47 _public prototype_ `virtual int32 GetUniverseID() const = 0;` — Returns the index of the Element in the Fader Group
- L50 _public prototype_ `virtual int32 GetStartingAddress() const = 0;` — Returns the first Channel of this Element
- L53 _public prototype_ `virtual int32 GetEndingAddress() const = 0;` — Returns the last Channel of this Element
- L57 _public function_ `virtual bool IsMatchingFilter() const` — True if the Element matches the Control Console filtering system
- L60 _public function_ `virtual void SetIsMatchingFilter(bool bMatches)` — Sets wheter the Element matches the Control Console filtering system
- L64 _public prototype_ `virtual void Destroy() = 0;` — Destroys the Element
- L69 _protected member_ `bool bIsMatchingFilter = true;` — True if the Element matches Control Console filtering system

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/Layouts/Controllers/DMXControlConsoleControllerBase.h` (Internal)


#### class `UDMXControlConsoleControllerBase`  
`class UDMXControlConsoleControllerBase : public UObject`  
_L16-47_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base class for Controllers
- L23 _public function_ `bool IsLocked() const` — True if the value of the Controller can't be changed
- L27 _public function_ `static FOnPropertiesChangedDelegate& GetOnPropertiesChanged()` — Returns the delegate called when a Controller property has been changed
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _public function_ `static FName GetIsLockedPropertyName()` — Property Name getters
- L40 _protected member_ `bool bIsLocked = false;` — `UPROPERTY(EditAnywhere, Category = "DMX Controller")` — If true, the value of the Controller can't be changed
- L45 _private member_ `static FOnPropertiesChangedDelegate OnPropertiesChanged;` — Called when a Controller property has been changed

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertiesChangedDelegate, FPropertyChangedEvent&);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertiesChangedDelegate, FPropertyChangedEvent&);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Internal/Layouts/DMXControlConsoleEditorLayoutsBase.h` (Internal)


#### class `UDMXControlConsoleEditorLayoutsBase`  
`class UDMXControlConsoleEditorLayoutsBase : public UObject`  
_L12-16_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base class for Control Console layouts

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Private/DMXControlConsoleMainStreamObjectVersion.h` (Private)


#### struct `FDMXControlConsoleMainStreamObjectVersion`  
`struct FDMXControlConsoleMainStreamObjectVersion`  
_L8-27_
- desc: Custom serialization version for changes to DMX Control Console Objects in the //Main Stream
- L23 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L26 _private function_ `FDMXControlConsoleMainStreamObjectVersion()`

#### enum `FDMXControlConsoleMainStreamObjectVersion::Type`  
`enum Type`  
_L10-20_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 5.5
- L16 _public enumerator_ `DMXControlConsoleFaderGroupUsesFixturePatchRef` — 5.5 Upgrade Control Console Fader Group to use a Fixture Patch Ref instead of a Soft Object Ptr
- L18 _public enumerator_ `VersionPlusOne`
- L19 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Private/Oscillators/DMXControlConsoleFloatOscillator_Sine.h` (Private)


#### class `UDMXControlConsoleFloatOscillator_Sine`  
`class UDMXControlConsoleFloatOscillator_Sine : public UDMXControlConsoleFloatOscillator`  
_L12-37_
- reflection: `UCLASS(Meta = (DisplayName = "Sine Wave"))`
- inherits: `UDMXControlConsoleFloatOscillator`
- desc: Generates DMX Signals in a Sine Pattern
- L20 _public member_ `float FrequencyHz = .25f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", UIMin = "0", UIMax = "120"), Category = "Sine Wave Oscillator")` — The frequency of the sine wave, in Hz
- L24 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"), Category = "Sine Wave Oscillator")` — The amplitude of the sine wave, in the range [0, 1]
- L28 _public member_ `float Offset = 0.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"), Category = "Sine Wave Oscillator")` — The offset of the sine wave, in the range [0, 1]
- L31 _public prototype_ `virtual float GetNormalizedValue_Implementation(float DeltaTime) override;`
- L36 _private member_ `double CurrentTime = 0.f;` — The current time, used to generate the sine wave

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Private/Oscillators/DMXControlConsoleFloatOscillator_Square.h` (Private)


#### class `UDMXControlConsoleFloatOscillator_Square`  
`class UDMXControlConsoleFloatOscillator_Square : public UDMXControlConsoleFloatOscillator`  
_L12-37_
- reflection: `UCLASS(Meta = (DisplayName = "Square Wave"))`
- inherits: `UDMXControlConsoleFloatOscillator`
- desc: Generates DMX Signals in a Square Wave Pattern
- L20 _public member_ `float FrequencyHz = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", UIMin = "0"), Category = "Sine Wave Oscillator")` — The frequency of the square wave, in Hz
- L24 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"), Category = "Sine Wave Oscillator")` — The amplitude of the square wave, in the range [0, 1]
- L28 _public member_ `float Offset = 0.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"), Category = "Sine Wave Oscillator")` — The offset of the square wave, in the range [0, 1]
- L31 _public prototype_ `virtual float GetNormalizedValue_Implementation(float DeltaTime) override;`
- L36 _private member_ `double CurrentTime = 0.f;` — The current time, used to generate the square wave

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsole/Public/Oscillators/DMXControlConsoleFloatOscillator.h` (Public)


#### class `UDMXControlConsoleFloatOscillator`  
`class UDMXControlConsoleFloatOscillator : public UObject`  
_L14-24_
- reflection: `UCLASS(Blueprintable, BlueprintType, EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: A value Oscillator that can be used in the DMX Control Console. Outputs float (normalized values)
- L22 _public prototype_ `float GetNormalizedValue(float DeltaTime);` — `UFUNCTION(BlueprintNativeEvent, Category = "DMX")` — Gets a normalized value that is sent as DMX
- L23 _public function_ `virtual float GetNormalizedValue_Implementation(float DeltaTime)`
