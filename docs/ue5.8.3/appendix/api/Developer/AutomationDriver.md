# Developer / AutomationDriver

- module root: `Source/Developer/AutomationDriver`
- headers: 25; symbols: 559
- symbol kinds: class=47, delegate=6, enum=2, enumerator=6, function=8, macro=2, member=19, prototype=456, struct=2, typedef=11
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, Json, Slate, SlateCore

### `Source/Developer/AutomationDriver/Private/AutomatedApplication.h` (Private)


#### class `FAutomatedApplication`  
`class FAutomatedApplication : public GenericApplication`  
_L12-37_
- inherits: `GenericApplication`
- L17 _public function_ `TSharedRef<FGenericApplicationMessageHandler> GetRealMessageHandler()`
- L19 _public prototype_ `virtual void AllowPlatformMessageHandling() = 0;`
- L20 _public prototype_ `virtual void DisablePlatformMessageHandling() = 0;`
- L21 _public prototype_ `virtual bool IsHandlingMessages() const = 0;`
- L22 _public prototype_ `virtual void SetOverrideRealCursorCoordinates(bool bOverrideRealCursor) = 0;`
- L24 _public prototype_ `virtual void SetFakeModifierKeys(FModifierKeysState Value) = 0;`
- L26 _public function_ `FAutomatedApplication( const TSharedPtr<ICursor>& InCursor) : GenericApplication(InCursor)`
- L33 _protected member_ `TSharedPtr<FGenericApplicationMessageHandler> RealMessageHandler;`

#### class `FAutomatedApplicationFactory`  
`class FAutomatedApplicationFactory`  
_L39-46_
- L43 _public prototype_ `static TSharedRef<FAutomatedApplication> Create( const TSharedRef<GenericApplication>& PlatformApplication, const TSharedRef<IPassThroughMessageHandlerFactory>& PassThroughMessageHandlerFactory);`

### `Source/Developer/AutomationDriver/Private/AutomationDriver.h` (Private)


#### class `FAsyncAutomationDriver`  
`class FAsyncAutomationDriver : public IAsyncAutomationDriver , public TSharedFromThis<FAsyncAutomationDriver, ESPMode::ThreadSafe>`  
_L20-94_
- inherits: `IAsyncAutomationDriver,TSharedFromThis<FAsyncAutomationDriver,ESPMode::ThreadSafe>`
- L26 _public prototype_ `virtual ~FAsyncAutomationDriver();`
- L28 _public prototype_ `virtual TAsyncResult<bool> Wait(FTimespan Timespan) override;`
- L29 _public prototype_ `virtual TAsyncResult<bool> Wait(const FDriverWaitDelegate& Delegate) override;`
- L31 _public prototype_ `virtual TSharedRef<IAsyncDriverSequence, ESPMode::ThreadSafe> CreateSequence() override;`
- L33 _public prototype_ `virtual TAsyncResult<FVector2D> GetCursorPosition() const override;`
- L35 _public prototype_ `virtual TAsyncResult<FModifierKeysState> GetModifierKeys() const override;`
- L37 _public prototype_ `virtual TSharedRef<IAsyncDriverElement, ESPMode::ThreadSafe> FindElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) override;`
- L39 _public prototype_ `virtual TSharedRef<IAsyncDriverElementCollection, ESPMode::ThreadSafe> FindElements(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) override;`
- L41 _public prototype_ `virtual TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe> GetConfiguration() const override;`
- L48 _public prototype_ `bool PinActionSequence(const TSharedPtr<IAsyncActionSequence, ESPMode::ThreadSafe>& Sequence);` — Saves a shared pointer to the action sequence object to ensure it remains in memory until execution is complete. @param Sequence shared pointer to the action sequence. @return true if the pointer has been saved successfully; false if another pinned sequence is currently being executed.
- L55 _public prototype_ `bool UnpinActionSequence(const TSharedPtr<IAsyncActionSequence, ESPMode::ThreadSafe>& Sequence);` — Resets an internally stored shared pointer to the previously pinned action sequence object so that it can be deleted. @param Sequence shared pointer to the action sequence. @return true if the pointer has been reset successfully; false if the provided sequence hasn't been pinned previously or if it is still executing
- L59 _public prototype_ `void TrackPress(int32 KeyCode, int32 CharCode);`
- L60 _public prototype_ `void TrackPress(EMouseButtons::Type Button);`
- L62 _public prototype_ `void TrackRelease(int32 KeyCode, int32 CharCode);`
- L63 _public prototype_ `void TrackRelease(EMouseButtons::Type Button);`
- L65 _public prototype_ `bool IsPressed(int32 KeyCode, int32 CharCode) const;`
- L66 _public prototype_ `bool IsPressed(EMouseButtons::Type Button) const;`
- L68 _public prototype_ `int32 ProcessCharacterForControlCodes(int32 CharCode) const;`
- L72 _private function_ `FAsyncAutomationDriver( const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& InApplication, const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe>& InConfiguration) : Application(InApplication) , Configuration(InConfiguration)`
- L79 _private prototype_ `void Initialize();`
- L83 _private member_ `const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe> Application;`
- L84 _private member_ `const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe> Configuration;`
- L85 _private member_ `TSharedPtr<IAsyncActionSequence, ESPMode::ThreadSafe> PinnedSequence;`
- L87 _private member_ `TSet<FKey> PressedModifiers;`
- L88 _private member_ `TSet<int32> PressedKeys;`
- L89 _private member_ `TSet<int32> PressedChars;`
- L90 _private member_ `TSet<EMouseButtons::Type> PressedButtons;`
- L91 _private member_ `TMap<int32, int32> CharactersToControlCodes;`

#### class `FAsyncAutomationDriverFactory`  
`class FAsyncAutomationDriverFactory`  
_L96-106_
- L100 _public prototype_ `static TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& AutomatedApplication);`
- L103 _public prototype_ `static TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& AutomatedApplication, const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe>& Configuration);`

#### class `FAutomationDriver`  
`class FAutomationDriver : public IAutomationDriver , public TSharedFromThis<FAutomationDriver, ESPMode::ThreadSafe>`  
_L111-160_
- inherits: `IAutomationDriver,TSharedFromThis<FAutomationDriver,ESPMode::ThreadSafe>`
- L117 _public prototype_ `virtual ~FAutomationDriver();`
- L119 _public prototype_ `virtual bool Wait(FTimespan Timespan) override;`
- L120 _public prototype_ `virtual bool Wait(const FDriverWaitDelegate& Delegate) override;`
- L122 _public prototype_ `virtual TSharedRef<IDriverSequence, ESPMode::ThreadSafe> CreateSequence() override;`
- L124 _public prototype_ `virtual FVector2D GetCursorPosition() const override;`
- L126 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const override;`
- L128 _public prototype_ `virtual TSharedRef<IDriverElement, ESPMode::ThreadSafe> FindElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) override;`
- L130 _public prototype_ `virtual TSharedRef<IDriverElementCollection, ESPMode::ThreadSafe> FindElements(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) override;`
- L132 _public prototype_ `virtual TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe> GetConfiguration() const override;`
- L136 _public prototype_ `void TrackPress(int32 KeyCode, int32 CharCode);`
- L137 _public prototype_ `void TrackPress(EMouseButtons::Type Button);`
- L139 _public prototype_ `void TrackRelease(int32 KeyCode, int32 CharCode);`
- L140 _public prototype_ `void TrackRelease(EMouseButtons::Type Button);`
- L142 _public prototype_ `bool IsPressed(int32 KeyCode, int32 CharCode) const;`
- L143 _public prototype_ `bool IsPressed(EMouseButtons::Type Button) const;`
- L147 _private function_ `FAutomationDriver( const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& InApplication, const TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe>& InAsyncDriver) : Application(InApplication) , AsyncDriver(InAsyncDriver)`
- L156 _private member_ `const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe> Application;`
- L157 _private member_ `const TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe> AsyncDriver;`

#### class `FAutomationDriverFactory`  
`class FAutomationDriverFactory`  
_L162-172_
- L166 _public prototype_ `static TSharedRef<FAutomationDriver, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& AutomatedApplication);`
- L169 _public prototype_ `static TSharedRef<FAutomationDriver, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& AutomatedApplication, const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe>& Configuration);`

### `Source/Developer/AutomationDriver/Private/AutomationDriverLogging.h` (Private)


#### class `FAutomationDriverLogging`  
`class FAutomationDriverLogging`  
_L11-32_
- L15 _public prototype_ `static void TooManyElementsFound(const TArray<TSharedRef<IApplicationElement>>& Elements);`
- L17 _public prototype_ `static void CannotFindElement(const TSharedPtr<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`
- L19 _public prototype_ `static void ElementNotVisible(const TSharedPtr<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`
- L21 _public prototype_ `static void ElementNotInteractable(const TSharedPtr<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`
- L23 _public prototype_ `static void ElementHasNoWindow(const TSharedPtr<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`
- L25 _public prototype_ `static void CannotClickUnhoveredElement(const TSharedPtr<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`
- L27 _public prototype_ `static void CannotExecuteMultipleActionSequencesInParallel();`
- L29 _public prototype_ `static void CannotUnpinActionSequenceIfNotPinned();`
- L31 _public prototype_ `static void CannotUnpinActionSequenceIfExecuting();`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomationDriver, Error, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomationDriver, Error, All);`

### `Source/Developer/AutomationDriver/Private/DriverElement.h` (Private)


#### class `FAsyncDriverElementCollectionFactory`  
`class FAsyncDriverElementCollectionFactory`  
_L13-20_
- L17 _public prototype_ `static TSharedRef<IAsyncDriverElementCollection, ESPMode::ThreadSafe> Create( const TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe>& AsyncDriver, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`

#### class `FAsyncDriverElementFactory`  
`class FAsyncDriverElementFactory`  
_L22-29_
- L26 _public prototype_ `static TSharedRef<IAsyncDriverElement, ESPMode::ThreadSafe> Create( const TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe>& AsyncDriver, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`

#### class `FDriverElementCollectionFactory`  
`class FDriverElementCollectionFactory`  
_L37-44_
- L41 _public prototype_ `static TSharedRef<IDriverElementCollection, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomationDriver, ESPMode::ThreadSafe>& Driver, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`

#### class `FDriverElementFactory`  
`class FDriverElementFactory`  
_L46-53_
- L50 _public prototype_ `static TSharedRef<IDriverElement, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomationDriver, ESPMode::ThreadSafe>& Driver, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator);`

### `Source/Developer/AutomationDriver/Private/DriverSequence.h` (Private)


#### class `FAsyncActionSequenceFactory`  
`class FAsyncActionSequenceFactory`  
_L14-21_
- L18 _public prototype_ `static TSharedRef<FAsyncActionSequence, ESPMode::ThreadSafe> Create( const TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe>& AsyncDriver, const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& Application);`

#### class `FAsyncDriverSequenceFactory`  
`class FAsyncDriverSequenceFactory`  
_L23-29_
- L27 _public prototype_ `static TSharedRef<IAsyncDriverSequence, ESPMode::ThreadSafe> Create( const TSharedRef<FAsyncActionSequence, ESPMode::ThreadSafe>& ActionSequence);`

#### class `FActionSequenceFactory`  
`class FActionSequenceFactory`  
_L37-45_
- L41 _public prototype_ `static TSharedRef<FActionSequence, ESPMode::ThreadSafe> Create( const TSharedRef<FAutomationDriver, ESPMode::ThreadSafe>& Driver, const TSharedRef<FAsyncAutomationDriver, ESPMode::ThreadSafe>& AsyncDriver, const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& Application);`

#### class `FDriverSequenceFactory`  
`class FDriverSequenceFactory`  
_L47-53_
- L51 _public prototype_ `static TSharedRef<IDriverSequence, ESPMode::ThreadSafe> Create( const TSharedRef<FActionSequence, ESPMode::ThreadSafe>& ActionSequence);`

### `Source/Developer/AutomationDriver/Private/IStepExecutor.h` (Private)


#### struct `FStepResult`  
`struct FStepResult`  
_L8-29_
- L19 _public function_ `FStepResult(EState InState, FTimespan InNextWait) : NextWait(MoveTemp(InNextWait)) , State(InState)`
- L25 _public member_ `FTimespan NextWait;` — How long the executor should wait before either executing this same step, the next step or before declaring all steps complete
- L28 _public member_ `EState State;` — Whether the step that just completed is completely finished or should be rescheduled again for execution

#### enum `FStepResult::EState`  
`enum class EState : uint8`  
_L12-17_
- L14 _public enumerator_ `DONE`
- L15 _public enumerator_ `FAILED`
- L16 _public enumerator_ `REPEAT`

#### class `IStepExecutor`  
`class IStepExecutor`  
_L31-49_
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FStepResult, FExecuteStepDelegate, const FTimespan& );`
- L36 _public prototype_ `virtual void Add(const TSharedRef<FExecuteStepDelegate>& Step) = 0;`
- L38 _public prototype_ `virtual void Add(const TFunction<FStepResult(const FTimespan&)>& StepFunction) = 0;`
- L40 _public prototype_ `virtual void InsertNext(const TSharedRef<FExecuteStepDelegate>& Step) = 0;`
- L42 _public prototype_ `virtual void InsertNext(const TFunction<FStepResult(const FTimespan&)>& StepFunction) = 0;`
- L44 _public prototype_ `virtual TAsyncResult<bool> Execute() = 0;`
- L46 _public prototype_ `virtual bool IsExecuting() const = 0;`
- L48 _public prototype_ `virtual void OnCompleted(TFunction<void()> Callback) = 0;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FStepResult, FExecuteStepDelegate, const FTimespan& );`

### `Source/Developer/AutomationDriver/Private/Locators/SlateWidgetLocatorByDelegate.h` (Private)


#### class `FSlateWidgetLocatorByDelegateFactory`  
`class FSlateWidgetLocatorByDelegateFactory`  
_L8-17_
- L12 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Create( const FLocateSlateWidgetElementDelegate& Delegate, FStringView DebugName = { });`
- L15 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Create( const FLocateSlateWidgetPathElementDelegate& Delegate, FStringView DebugName = { });`

### `Source/Developer/AutomationDriver/Private/Locators/SlateWidgetLocatorByPath.h` (Private)


#### class `FSlateWidgetLocatorByPathFactory`  
`class FSlateWidgetLocatorByPathFactory`  
_L9-19_
- L13 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Create( const FString& Path);`
- L16 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Create( const FDriverElementPtr& Root, const FString& Path);`

### `Source/Developer/AutomationDriver/Private/Locators/SlateWidgetLocatorByUniqueTag.h` (Private)


#### class `FSlateWidgetLocatorByUniqueTagFactory`  
`class FSlateWidgetLocatorByUniqueTagFactory`  
_L9-15_
- L13 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Create( const TSharedRef<FDriverUniqueTagMetaData>& UniqueMetaData);`

### `Source/Developer/AutomationDriver/Private/Locators/WidgetLocatorByFilter.h` (Private)


#### class `FWidgetLocatorByFilterFactory`  
`class FWidgetLocatorByFilterFactory`  
_L11-29_
- desc: This class provides a utility function for creating instances of the filter locator.
- L14 _public typedef_ `using FFilterFunction = TFunction<bool(const TSharedRef<IApplicationElement>&)>;`
- L24 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Create( const FString& DebugString, const FElementLocatorRef& RootLocator, FFilterFunction Filter );` — Creates a new element locator that limits the elements discovered by the provided root locator to those determined by the filter function. @param DebugString - The string used for debugging and logging purposes to represent this particular instance of the filter locator @param RootLocator - The reference to the element locator where the search will be started from @param Filter - The function applied to the elements found by the root locator to determine which should be saved as a result. @return a locator which uses the specified root locator and a filter function to discover appropriate elements

### `Source/Developer/AutomationDriver/Private/MetaData/DriverUniqueTagMetaData.h` (Private)


#### class `FDriverUniqueTagMetaData`  
`class FDriverUniqueTagMetaData : public ISlateMetaData`  
_L6-14_
- inherits: `ISlateMetaData`
- L10 _public function_ `SLATE_METADATA_TYPE(FDriverUniqueTagMetaData, ISlateMetaData) FDriverUniqueTagMetaData()`

### `Source/Developer/AutomationDriver/Private/PassThroughMessageHandler.h` (Private)


#### class `FPassThroughMessageHandler`  
`class FPassThroughMessageHandler : public FGenericApplicationMessageHandler`  
_L6-17_
- inherits: `FGenericApplicationMessageHandler`
- L11 _public prototype_ `virtual ~FPassThroughMessageHandler() = default;`
- L13 _public prototype_ `virtual bool IsHandlingMessages() const = 0;`
- L15 _public prototype_ `virtual void SetAllowMessageHandling(bool bValue) = 0;`

#### class `IPassThroughMessageHandlerFactory`  
`class IPassThroughMessageHandlerFactory`  
_L19-27_
- L23 _public prototype_ `virtual ~IPassThroughMessageHandlerFactory() = default;`
- L25 _public prototype_ `virtual TSharedRef<FPassThroughMessageHandler> Create( const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler) const = 0;`

#### class `FPassThroughMessageHandlerFactoryFactory`  
`class FPassThroughMessageHandlerFactoryFactory`  
_L29-34_
- L33 _public prototype_ `static TSharedRef<IPassThroughMessageHandlerFactory> Create();`

### `Source/Developer/AutomationDriver/Private/SlateWidgetElement.h` (Private)


#### class `FSlateWidgetElementFactory`  
`class FSlateWidgetElementFactory`  
_L9-15_
- L13 _public prototype_ `static TSharedRef<IApplicationElement> Create( const FWidgetPath& WidgetPath);`

### `Source/Developer/AutomationDriver/Private/StepExecutor.h` (Private)


#### class `FStepExecutorFactory`  
`class FStepExecutorFactory`  
_L10-18_
- L14 _public prototype_ `static TSharedRef<IStepExecutor, ESPMode::ThreadSafe> Create( const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe>& Configuration, const TSharedRef<FAutomatedApplication, ESPMode::ThreadSafe>& Application);`

### `Source/Developer/AutomationDriver/Public/AutomationDriverCommon.h` (Public)
_(no declarations extracted)_

### `Source/Developer/AutomationDriver/Public/AutomationDriverTypeDefs.h` (Public)


#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedPtr<IAutomationDriver, ESPMode::ThreadSafe> FAutomationDriverPtr;`
- L13 _typedef_ `typedef TSharedRef<IAutomationDriver, ESPMode::ThreadSafe> FAutomationDriverRef;`
- L14 _typedef_ `typedef TSharedPtr<IDriverElement, ESPMode::ThreadSafe> FDriverElementPtr;`
- L15 _typedef_ `typedef TSharedRef<IDriverElement, ESPMode::ThreadSafe> FDriverElementRef;`
- L16 _typedef_ `typedef TSharedPtr<IDriverElementCollection, ESPMode::ThreadSafe> FDriverElementCollectionPtr;`
- L17 _typedef_ `typedef TSharedRef<IDriverElementCollection, ESPMode::ThreadSafe> FDriverElementCollectionRef;`
- L18 _typedef_ `typedef TSharedPtr<IDriverSequence, ESPMode::ThreadSafe> FDriverSequencePtr;`
- L19 _typedef_ `typedef TSharedRef<IDriverSequence, ESPMode::ThreadSafe> FDriverSequenceRef;`
- L20 _typedef_ `typedef TSharedPtr<IElementLocator, ESPMode::ThreadSafe> FElementLocatorPtr;`
- L21 _typedef_ `typedef TSharedRef<IElementLocator, ESPMode::ThreadSafe> FElementLocatorRef;`

### `Source/Developer/AutomationDriver/Public/DriverConfiguration.h` (Public)


#### class `FDriverConfiguration`  
`class FDriverConfiguration`  
_L10-30_
- desc: A model class that holds all the configuration options for an AutomationDriver
- L18 _public member_ `FTimespan ImplicitWait;` — The timespan any action should conditionally wait for a scenario to occur before failing, such as, waiting for a locator to locate a specific application element.
- L24 _public member_ `float ExecutionSpeedMultiplier;` — The multiplier at which the automation driver should adjusts the time between individual steps by. The automation driver caps the minimum wait time to one frame.
- L26 _public function_ `FDriverConfiguration() : ImplicitWait(FTimespan::FromSeconds(3)) , ExecutionSpeedMultiplier(1.0)`

### `Source/Developer/AutomationDriver/Public/IApplicationElement.h` (Public)


#### class `IApplicationElement`  
`class IApplicationElement`  
_L10-82_
- L15 _public prototype_ `virtual FString ToDebugString() const = 0;` — @return a string representation of this element intended to be used solely for debugging purposes
- L18 _public prototype_ `virtual FVector2D GetAbsolutePosition() const = 0;` — @return the position on this element in screen space
- L21 _public prototype_ `virtual FVector2D GetSize() const = 0;` — @return the size of the interactable area of this element on screen
- L24 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindow() const = 0;` — @return the OS window containing this element
- L27 _public prototype_ `virtual bool IsVisible() const = 0;` — @return whether the element is currently visible to the user
- L30 _public prototype_ `virtual bool IsInteractable() const = 0;` — @return whether the user can currently interact with the element
- L33 _public prototype_ `virtual bool IsChecked() const = 0;` — @return whether the element is currently checked
- L36 _public prototype_ `virtual FText GetText() const = 0;` — @return the text being displayed to the user via this element
- L39 _public prototype_ `virtual TSharedRef<IElementLocator, ESPMode::ThreadSafe> CreateLocator() const = 0;` — @return a special element locator that can be used to recall this specific element
- L42 _public prototype_ `virtual bool CanFocus() const = 0;` — @return whether this element can be focused
- L45 _public prototype_ `virtual bool Focus() const = 0;` — @return whether focus was changed to the element for the default user
- L48 _public prototype_ `virtual bool Focus(uint32 UserIndex) const = 0;` — @return whether focus was changed to the element for the specified user
- L51 _public prototype_ `virtual bool IsFocused() const = 0;` — @return whether the element is currently the focus of the default user
- L54 _public prototype_ `virtual bool IsFocused(uint32 UserIndex) const = 0;` — @return whether the element is currently the focus of the specified user
- L57 _public prototype_ `virtual bool HasFocusedDescendants() const = 0;` — @return whether the element is currently in the parent hierarchy of the focus of the default user
- L60 _public prototype_ `virtual bool HasFocusedDescendants(uint32 UserIndex) const = 0;` — @return whether the element is currently in the parent hierarchy of the focus of the specified user
- L63 _public prototype_ `virtual bool IsHovered() const = 0;` — @return whether this element is currently being hovered over by the cursor
- L66 _public prototype_ `virtual bool IsScrollable() const = 0;` — @return whether this application element is scrollable
- L69 _public prototype_ `virtual bool IsScrollable(EOrientation& OutScrollOrientation) const = 0;` — @return whether this application element is scrollable; OutScrollOrientation will be set to the orientation of the element only if the element is scrollable
- L72 _public prototype_ `virtual bool IsScrolledToBeginning() const = 0;` — @return whether the element's scroll position is at the very top; only valid on scrollable elements
- L75 _public prototype_ `virtual bool IsScrolledToEnd() const = 0;` — @return whether the element's scroll position is at the very bottom; only valid on scrollable elements
- L78 _public prototype_ `virtual TSharedPtr<IApplicationElement> GetScrollableParent() const = 0;` — @return a parent element of this element which is scrollable; null if no scrollable parent exists
- L81 _public prototype_ `virtual void* GetRawElement() const = 0;` — @return an empty, null element

### `Source/Developer/AutomationDriver/Public/IAutomationDriver.h` (Public)


#### class `IAsyncAutomationDriver`  
`class IAsyncAutomationDriver`  
_L20-71_
- desc: The AsyncAutomationDriver is the async varition of the general AutomationDriver API. The AutomationDriver can create sequences and locate elements to simulate input for.
- L28 _public prototype_ `virtual TAsyncResult<bool> Wait(FTimespan Timespan) = 0;` — Performs an async wait no shorter than for the specified Timespan @return true after at least the specified amount of time has elasped; may return false if the wait is forcibly interrupted
- L34 _public prototype_ `virtual TAsyncResult<bool> Wait(const FDriverWaitDelegate& Delegate) = 0;` — Performs an async wait until the specified DriverWaitDelegate returns a PASSED or FAILED response @return true if the delegate ultimately returned PASSED; otherwise false
- L39 _public prototype_ `virtual TSharedRef<IAsyncDriverSequence, ESPMode::ThreadSafe> CreateSequence() = 0;` — @return a new async driver sequence which can be used to issue a serious of commands to the driver
- L44 _public prototype_ `virtual TAsyncResult<FVector2D> GetCursorPosition() const = 0;` — @return the current position of the cursor
- L49 _public prototype_ `virtual TAsyncResult<FModifierKeysState> GetModifierKeys() const = 0;` — @return the current state of modifier keys for the application
- L57 _public prototype_ `virtual TSharedRef<IAsyncDriverElement, ESPMode::ThreadSafe> FindElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — This is a non-blocking call and doesn't invoke the locator until some action is performed on the element. You will need to invoke the Exists() method on the element to confirm the elements existence if that is what you want to do. @return a driver element representing a single element located by the specified locator
- L65 _public prototype_ `virtual TSharedRef<IAsyncDriverElementCollection, ESPMode::ThreadSafe> FindElements(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — This is a non-blocking call and doesn't invoke the locator until some action is performed on the element. You will need to invoke the GetElements() method on the collection to confirm the existence of any elements. @return a driver element collection representing multiple elements potentially located by the specified locator
- L70 _public prototype_ `virtual TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe> GetConfiguration() const = 0;` — @return the driver's configuration details

#### class `IAutomationDriver`  
`class IAutomationDriver`  
_L82-133_
- desc: The AutomationDriver can create sequences and locate elements to simulate input for.
- L90 _public prototype_ `virtual bool Wait(FTimespan Timespan) = 0;` — Performs an wait no shorter than for the specified Timespan @return true after at least the specified amount of time has elasped; may return false if the wait is forcibly interrupted
- L96 _public prototype_ `virtual bool Wait(const FDriverWaitDelegate& Delegate) = 0;` — Performs an wait until the specified DriverWaitDelegate returns a PASSED or FAILED response @return true if the delegate ultimately returned PASSED; otherwise false
- L101 _public prototype_ `virtual TSharedRef<IDriverSequence, ESPMode::ThreadSafe> CreateSequence() = 0;` — @return a new driver sequence which can be used to issue a series of commands to the driver
- L106 _public prototype_ `virtual FVector2D GetCursorPosition() const = 0;` — @return the current position of the cursor
- L111 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const = 0;` — @return the current state of modifier keys for the application
- L119 _public prototype_ `virtual TSharedRef<IDriverElement, ESPMode::ThreadSafe> FindElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — This doesn't invoke the locator until some action is performed on the element. You will need to invoke the Exists() method on the element to confirm the elements existence if that is what you want to do. @return a driver element representing a single element located by the specified locator
- L127 _public prototype_ `virtual TSharedRef<IDriverElementCollection, ESPMode::ThreadSafe> FindElements(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — This doesn't invoke the locator until some action is performed on the element. You will need to invoke the GetElements() method on the collection to confirm the existence of any elements. @return a driver element collection representing multiple elements potentially located by the specified locator
- L132 _public prototype_ `virtual TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe> GetConfiguration() const = 0;` — @return the driver's configuration details

### `Source/Developer/AutomationDriver/Public/IAutomationDriverModule.h` (Public)


#### class `IAutomationDriverModule`  
`class IAutomationDriverModule : public IModuleInterface`  
_L11-60_
- inherits: `IModuleInterface`
- L16 _public function_ `static inline IAutomationDriverModule& Get()`
- L24 _public prototype_ `virtual TSharedRef<IAutomationDriver, ESPMode::ThreadSafe> CreateDriver() const = 0;` — @return a new automation driver that can be used to simulate input
- L29 _public prototype_ `virtual TSharedRef<IAutomationDriver, ESPMode::ThreadSafe> CreateDriver(const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe>& Configuration) const = 0;` — @return a new automation driver that can be used to simulate input; using the specified configuration
- L34 _public prototype_ `virtual TSharedRef<IAsyncAutomationDriver, ESPMode::ThreadSafe> CreateAsyncDriver() const = 0;` — @return a new async automation driver that can be used to simulate input
- L39 _public prototype_ `virtual TSharedRef<IAsyncAutomationDriver, ESPMode::ThreadSafe> CreateAsyncDriver(const TSharedRef<FDriverConfiguration, ESPMode::ThreadSafe>& Configuration) const = 0;` — @return a new async automation driver that can be used to simulate input; using the specified configuration
- L44 _public prototype_ `virtual bool IsEnabled() const = 0;` — @return whether the automation driver module is actively enabled
- L52 _public prototype_ `virtual void Enable() = 0;` — Enables the automation driver. Enabling the automation driver module causes most traditional input messages from the platform to stop being received, and instead only input simulated via an actual automation driver is received.
- L59 _public prototype_ `virtual void Disable() = 0;` — Disables the automation driver. Disabling the automation driver module restores the platform specific messaging so they are once again received by the application.

### `Source/Developer/AutomationDriver/Public/IDriverElement.h` (Public)


#### class `IAsyncDriverElement`  
`class IAsyncDriverElement : public IElementLocator`  
_L12-353_
- inherits: `IElementLocator`
- desc: Represents the async API for a potential application element
- L21 _public prototype_ `virtual TAsyncResult<bool> Hover() = 0;` — Moves the cursor over the element, triggering any hover cue the element may have @return whether the cursor move was successful
- L26 _public prototype_ `virtual TAsyncResult<bool> IsHovered() const = 0;` — @return whether the element believes it is currently being hovered by the cursor
- L32 _public prototype_ `virtual TAsyncResult<bool> Click(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a click with the specified mouse button @return whether the click was successful
- L38 _public prototype_ `virtual TAsyncResult<bool> Click() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a click with the left mouse button @return whether the click was successful
- L44 _public prototype_ `virtual TAsyncResult<bool> DoubleClick(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a double click with the specified mouse button @return whether the double click was successful
- L50 _public prototype_ `virtual TAsyncResult<bool> DoubleClick() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a double click with the left mouse button @return whether the double click was successful
- L57 _public prototype_ `virtual TAsyncResult<bool> ScrollBy(float Delta) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta. Most average user scrolling is limited to a range of -5 to 5. @return whether the scroll by delta was successful
- L64 _public prototype_ `virtual TAsyncResult<bool> ScrollToBeginning() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the beginning @return whether the scroll to beginning was successful
- L71 _public prototype_ `virtual TAsyncResult<bool> ScrollToBeginning(float Amount) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the beginning @return whether the scroll to beginning was successful
- L78 _public prototype_ `virtual TAsyncResult<bool> ScrollToBeginningUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& DesiredElementLocator) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator is locates the desired element or the beginning is reached @return whether the scroll to beginning until was successful
- L85 _public prototype_ `virtual TAsyncResult<bool> ScrollToEnd() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the beginning @return whether the scroll to end was successful
- L92 _public prototype_ `virtual TAsyncResult<bool> ScrollToEnd(float Amount) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the end @return whether the scroll to end was successful
- L99 _public prototype_ `virtual TAsyncResult<bool> ScrollToEndUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& DesiredElementLocator) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator is locates the desired element or the end is reached @return whether the scroll to end until was successful
- L106 _public prototype_ `virtual TAsyncResult<bool> Type(const TCHAR* Text) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing. @return whether the type was successful
- L113 _public prototype_ `virtual TAsyncResult<bool> Type(FString Text) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing. @return whether the type was successful
- L119 _public prototype_ `virtual TAsyncResult<bool> Type(FKey Key) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for the specified character. @return whether the type was successful
- L126 _public prototype_ `virtual TAsyncResult<bool> Type(TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for the specified key. Not all control and modifier keys are supported with this method of typing. @return whether the type was successful
- L132 _public prototype_ `virtual TAsyncResult<bool> Type(const TArray<FKey>& Keys) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each key specified. @return whether the type was successful
- L140 _public prototype_ `virtual TAsyncResult<bool> TypeChord(FKey Key1, FKey Key2) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L148 _public prototype_ `virtual TAsyncResult<bool> TypeChord(FKey Key1, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L156 _public prototype_ `virtual TAsyncResult<bool> TypeChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L164 _public prototype_ `virtual TAsyncResult<bool> TypeChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L172 _public prototype_ `virtual TAsyncResult<bool> Press(TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for pressing the specified character. The character will not be released, nor will their be repeat character events issued for holding the character. @return whether the press was successful
- L180 _public prototype_ `virtual TAsyncResult<bool> Press(FKey Key) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for pressing the specified key. The key will not be released, nor will their be repeat key events issued for holding the key. @return whether the press was successful
- L187 _public prototype_ `virtual TAsyncResult<bool> Press(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke mouse input for pressing the specified button. The button will not be released. @return whether the press was successful
- L194 _public prototype_ `virtual TAsyncResult<bool> PressChord(FKey Key1, FKey Key2) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L201 _public prototype_ `virtual TAsyncResult<bool> PressChord(FKey Key1, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L208 _public prototype_ `virtual TAsyncResult<bool> PressChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L215 _public prototype_ `virtual TAsyncResult<bool> PressChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L222 _public prototype_ `virtual TAsyncResult<bool> Release(TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed. @return whether the release was successful
- L229 _public prototype_ `virtual TAsyncResult<bool> Release(FKey Key) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified key. The key will not be pressed if it is not currently being pressed. @return whether the release was successful
- L236 _public prototype_ `virtual TAsyncResult<bool> Release(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke mouse input for releasing the specified button. The button will not be pressed if it is not currently pressed. @return whether the release was successful
- L243 _public prototype_ `virtual TAsyncResult<bool> ReleaseChord(FKey Key1, FKey Key2) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed. @return whether the release chord was successful
- L250 _public prototype_ `virtual TAsyncResult<bool> ReleaseChord(FKey Key1, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed. @return whether the release chord was successful
- L257 _public prototype_ `virtual TAsyncResult<bool> ReleaseChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed. @return whether the release chord was successful
- L264 _public prototype_ `virtual TAsyncResult<bool> ReleaseChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed. @return whether the release chord was successful
- L270 _public prototype_ `virtual TAsyncResult<bool> Focus() = 0;` — Moves focus to the element for the default user @return whether the focus change was successful
- L276 _public prototype_ `virtual TAsyncResult<bool> Focus(uint32 UserIndex) = 0;` — Moves focus to the element for the specified user @return whether the focus change was successful
- L281 _public prototype_ `virtual TAsyncResult<bool> CanFocus() const = 0;` — @return whether the element can be focused
- L286 _public prototype_ `virtual TAsyncResult<bool> IsFocused() const = 0;` — @return whether the element is currently the focus for the default user
- L291 _public prototype_ `virtual TAsyncResult<bool> IsFocused(uint32 UserIndex) const = 0;` — @return whether the element is currently the focus for the specified user
- L296 _public prototype_ `virtual TAsyncResult<bool> HasFocusedDescendants() const = 0;` — @return whether the element is currently in the parent hierarchy of the focus of the default user
- L301 _public prototype_ `virtual TAsyncResult<bool> HasFocusedDescendants(uint32 UserIndex) const = 0;` — @return whether the element is currently in the parent hierarchy of the focus of the specified user
- L306 _public prototype_ `virtual TAsyncResult<bool> Exists() const = 0;` — @return whether the element is currently exists
- L311 _public prototype_ `virtual TAsyncResult<bool> IsVisible() const = 0;` — @return whether the element is currently visible; the element must be on screen
- L316 _public prototype_ `virtual TAsyncResult<bool> IsChecked() const = 0;` — @return whether the element is currently checked; will return false if the element is uncheckable
- L321 _public prototype_ `virtual TAsyncResult<bool> IsInteractable() const = 0;` — @return whether the element is currently interactable; the element must be on screen
- L326 _public prototype_ `virtual TAsyncResult<bool> IsScrollable() const = 0;` — @return whether the element is scrollable; an element is considered scrollable if it has any scrollable descendants
- L331 _public prototype_ `virtual TAsyncResult<bool> IsScrolledToBeginning() const = 0;` — @return is true if the element is scrollable and at the beginning position
- L336 _public prototype_ `virtual TAsyncResult<bool> IsScrolledToEnd() const = 0;` — @return is true if the element is scrollable and at the end position
- L341 _public prototype_ `virtual TAsyncResult<FVector2D> GetAbsolutePosition() const = 0;` — @return the screen space absolute position of the element's top left corner
- L346 _public prototype_ `virtual TAsyncResult<FVector2D> GetSize() const = 0;` — @return the screen size of the element
- L352 _public prototype_ `virtual TAsyncResult<FText> GetText() const = 0;` — @return the text displayed by the element; if the element does not display text itself, then if there is only a single descendant of the element that displays text, then that descendants text will be returned

#### class `IAsyncDriverElementCollection`  
`class IAsyncDriverElementCollection`  
_L359-367_
- desc: Represents a potential collection of elements
- L366 _public prototype_ `virtual TAsyncResult<TArray<TSharedRef<IAsyncDriverElement, ESPMode::ThreadSafe>>> GetElements() = 0;` — @return the elements discovered by the locator at this current moment; calling this multiple times may return different elements

#### class `FEmptyAsyncDriverElementFactory`  
`class FEmptyAsyncDriverElementFactory`  
_L369-373_
- L372 _public prototype_ `static TSharedRef<IAsyncDriverElement, ESPMode::ThreadSafe> Create();`

#### class `IDriverElement`  
`class IDriverElement : public IElementLocator`  
_L378-719_
- inherits: `IElementLocator`
- desc: Represents the API for a potential application element
- L387 _public prototype_ `virtual bool Hover() = 0;` — Moves the cursor over the element, triggering any hover cue the element may have @return whether the cursor move was successful
- L392 _public prototype_ `virtual bool IsHovered() const = 0;` — @return whether the element believes it is currently being hovered by the cursor
- L398 _public prototype_ `virtual bool Click(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a click with the specified mouse button @return whether the click was successful
- L404 _public prototype_ `virtual bool Click() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a click with the left mouse button @return whether the click was successful
- L410 _public prototype_ `virtual bool DoubleClick(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a double click with the specified mouse button @return whether the double click was successful
- L416 _public prototype_ `virtual bool DoubleClick() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a double click with the left mouse button @return whether the double click was successful
- L423 _public prototype_ `virtual bool ScrollBy(float Delta) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta. Most average user scrolling is limited to a range of -5 to 5. @return whether the scroll by delta was successful
- L430 _public prototype_ `virtual bool ScrollToBeginning() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the beginning @return whether the scroll to beginning was successful
- L437 _public prototype_ `virtual bool ScrollToBeginning(float Amount) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the beginning @return whether the scroll to beginning was successful
- L444 _public prototype_ `virtual bool ScrollToBeginningUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& DesiredElementLocator) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator is locates the desired element or the beginning is reached @return whether the scroll to beginning until was successful
- L451 _public prototype_ `virtual bool ScrollToEnd() = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the beginning @return whether the scroll to end was successful
- L458 _public prototype_ `virtual bool ScrollToEnd(float Amount) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the end @return whether the scroll to end was successful
- L465 _public prototype_ `virtual bool ScrollToEndUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& DesiredElementLocator) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator is locates the desired element or the end is reached @return whether the scroll to end until was successful
- L472 _public prototype_ `virtual bool Type(const TCHAR* Text) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing. @return whether the type was successful
- L479 _public prototype_ `virtual bool Type(FString Text) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing. @return whether the type was successful
- L485 _public prototype_ `virtual bool Type(FKey Key) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for the specified character. @return whether the type was successful
- L492 _public prototype_ `virtual bool Type(TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for the specified key. Not all control and modifier keys are supported with this method of typing. @return whether the type was successful
- L498 _public prototype_ `virtual bool Type(const TArray<FKey>& Keys) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each key specified. @return whether the type was successful
- L506 _public prototype_ `virtual bool TypeChord(FKey Key1, FKey Key2) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L514 _public prototype_ `virtual bool TypeChord(FKey Key1, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L522 _public prototype_ `virtual bool TypeChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L530 _public prototype_ `virtual bool TypeChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S @return whether the type chord was successful
- L538 _public prototype_ `virtual bool Press(TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for pressing the specified character. The character will not be released, nor will their be repeat character events issued for holding the character. @return whether the press was successful
- L546 _public prototype_ `virtual bool Press(FKey Key) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for pressing the specified key. The key will not be released, nor will their be repeat key events issued for holding the key. @return whether the press was successful
- L553 _public prototype_ `virtual bool Press(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke mouse input for pressing the specified button. The button will not be released. @return whether the press was successful
- L560 _public prototype_ `virtual bool PressChord(FKey Key1, FKey Key2) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L567 _public prototype_ `virtual bool PressChord(FKey Key1, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L574 _public prototype_ `virtual bool PressChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L581 _public prototype_ `virtual bool PressChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released. @return whether the press chord was successful
- L588 _public prototype_ `virtual bool Release(TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed. @return whether the release was successful
- L595 _public prototype_ `virtual bool Release(FKey Key) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified key. The key will not be pressed if it is not currently being pressed. @return whether the release was successful
- L602 _public prototype_ `virtual bool Release(EMouseButtons::Type MouseButton) = 0;` — Moves the cursor over the element, then triggers the series of events to invoke mouse input for releasing the specified button. The button will not be pressed if it is not currently pressed. @return whether the release was successful
- L609 _public prototype_ `virtual bool ReleaseChord(FKey Key1, FKey Key2) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if if not currently being pressed. @return whether the release chord was successful
- L616 _public prototype_ `virtual bool ReleaseChord(FKey Key1, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if if not currently being pressed. @return whether the release chord was successful
- L623 _public prototype_ `virtual bool ReleaseChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if if not currently being pressed. @return whether the release chord was successful
- L630 _public prototype_ `virtual bool ReleaseChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Moves focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if if not currently being pressed. @return whether the release chord was successful
- L636 _public prototype_ `virtual bool Focus() = 0;` — Moves focus to the element for the default user @return whether the focus change was successful
- L642 _public prototype_ `virtual bool Focus(uint32 UserIndex) = 0;` — Moves focus to the element for the specified user @return whether the focus change was successful
- L647 _public prototype_ `virtual bool CanFocus() const = 0;` — @return whether the element can be focused
- L652 _public prototype_ `virtual bool IsFocused() const = 0;` — @return whether the element is currently the focus for the default user
- L657 _public prototype_ `virtual bool IsFocused(uint32 UserIndex) const = 0;` — @return whether the element is currently the focus for the specified user
- L662 _public prototype_ `virtual bool HasFocusedDescendants() const = 0;` — @return whether the element is currently in the parent hierarchy of the focus of the default user
- L667 _public prototype_ `virtual bool HasFocusedDescendants(uint32 UserIndex) const = 0;` — @return whether the element is currently in the parent hierarchy of the focus of the specified user
- L672 _public prototype_ `virtual bool Exists() const = 0;` — @return whether the element is currently exists
- L677 _public prototype_ `virtual bool IsVisible() const = 0;` — @return whether the element is currently visible; the element must be on screen
- L682 _public prototype_ `virtual bool IsChecked() const = 0;` — @return whether the element is currently checked; will return false if the element is uncheckable
- L687 _public prototype_ `virtual bool IsInteractable() const = 0;` — @return whether the element is currently interactable; the element must be on screen
- L692 _public prototype_ `virtual bool IsScrollable() const = 0;` — @return whether the element is scrollable; an element is considered scrollable if it has any scrollable descendants
- L697 _public prototype_ `virtual bool IsScrolledToBeginning() const = 0;` — @return is true if the element is scrollable and at the beginning position
- L702 _public prototype_ `virtual bool IsScrolledToEnd() const = 0;` — @return is true if the element is scrollable and at the end position
- L707 _public prototype_ `virtual FVector2D GetAbsolutePosition() const = 0;` — @return the screen space absolute position of the element's top left corner
- L712 _public prototype_ `virtual FVector2D GetSize() const = 0;` — @return the screen size of the element
- L718 _public prototype_ `virtual FText GetText() const = 0;` — @return the text displayed by the element; if the element does not display text itself, then if there is only a single descendant of the element that displays text, then that descendants text will be returned

#### class `IDriverElementCollection`  
`class IDriverElementCollection`  
_L724-732_
- desc: Represents a potential collection of elements
- L731 _public prototype_ `virtual TArray<TSharedRef<IDriverElement, ESPMode::ThreadSafe>> GetElements() = 0;` — @return the elements discovered by the locator at this current moment; calling this multiple times may return different elements

#### class `FEmptyDriverElementFactory`  
`class FEmptyDriverElementFactory`  
_L734-738_
- L737 _public prototype_ `static TSharedRef<IDriverElement, ESPMode::ThreadSafe> Create();`

### `Source/Developer/AutomationDriver/Public/IDriverSequence.h` (Public)


#### class `IAsyncActionSequence`  
`class IAsyncActionSequence`  
_L12-439_
- L19 _public prototype_ `virtual IAsyncActionSequence& Wait(FTimespan Timespan) = 0;` — Queues a wait no shorter than for the specified Timespan
- L24 _public prototype_ `virtual IAsyncActionSequence& Wait(const FDriverWaitDelegate& Delegate) = 0;` — Queues a wait until the specified DriverWaitDelegate returns a PASSED or FAILED response
- L29 _public prototype_ `virtual IAsyncActionSequence& MoveToElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, int32 XOffset, int32 YOffset) = 0;` — Queues a move of the cursor over the center of the element offset by the specified amounts, triggering any hover cue the element may have
- L34 _public prototype_ `virtual IAsyncActionSequence& MoveToElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the center of the element, triggering any hover cue the element may have
- L39 _public prototype_ `virtual IAsyncActionSequence& MoveByOffset(int32 XOffset, int32 YOffset) = 0;` — Queues a move of the cursor from its current position by the specified offsets
- L44 _public prototype_ `virtual IAsyncActionSequence& MoveToPosition(const FVector2D& Position) = 0;` — Queues a move of the cursor from its current position to a new position which is specified
- L50 _public prototype_ `virtual IAsyncActionSequence& ScrollBy(float Delta) = 0;` — Queues the series of events to invoke a mouse wheel scroll by the specified delta at the current mouse position Most average user scrolling is limited to a range of -5 to 5.
- L55 _public prototype_ `virtual IAsyncActionSequence& ScrollBy(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, float Delta) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta
- L61 _public prototype_ `virtual IAsyncActionSequence& ScrollToBeginning(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the beginning
- L67 _public prototype_ `virtual IAsyncActionSequence& ScrollToBeginning(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, float Amount) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the beginning
- L73 _public prototype_ `virtual IAsyncActionSequence& ScrollToBeginningUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues the series of events to invoke a mouse wheel scroll until the specified locator is locates the desired element or the beginning is reached at the current cursor position
- L79 _public prototype_ `virtual IAsyncActionSequence& ScrollToBeginningUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ScrollableElementLocator, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the scrollable element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator locates the desired element or the beginning is reached
- L85 _public prototype_ `virtual IAsyncActionSequence& ScrollToEnd(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the end
- L91 _public prototype_ `virtual IAsyncActionSequence& ScrollToEnd(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, float Delta) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the end
- L97 _public prototype_ `virtual IAsyncActionSequence& ScrollToEndUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator locates the desired element or the end is reached
- L103 _public prototype_ `virtual IAsyncActionSequence& ScrollToEndUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ScrollableElementLocator, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the scrollable element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator locates the desired element or the end is reached
- L108 _public prototype_ `virtual IAsyncActionSequence& Click(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a click with the left mouse button
- L113 _public prototype_ `virtual IAsyncActionSequence& Click(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a click with the specified mouse button
- L118 _public prototype_ `virtual IAsyncActionSequence& Click(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke a click with the specified mouse button at the current cursor location
- L123 _public prototype_ `virtual IAsyncActionSequence& Click() = 0;` — Queues the series of events to invoke a click with the left mouse button at the current cursor location
- L128 _public prototype_ `virtual IAsyncActionSequence& DoubleClick(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a double click with the left mouse button
- L133 _public prototype_ `virtual IAsyncActionSequence& DoubleClick(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a double click with the specified mouse button
- L138 _public prototype_ `virtual IAsyncActionSequence& DoubleClick(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke a double click with the specified mouse button at the current cursor location
- L143 _public prototype_ `virtual IAsyncActionSequence& DoubleClick() = 0;` — Queues the series of events to invoke a double click with the left mouse button at the current cursor location
- L149 _public prototype_ `virtual IAsyncActionSequence& Type(const TCHAR* Text) = 0;` — Queues the series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing.
- L155 _public prototype_ `virtual IAsyncActionSequence& Type(FString Text) = 0;` — Queues the series of events to invoke keyboard input for each character of the string specified. Not all control and modifier keys are supported with this method of typing.
- L160 _public prototype_ `virtual IAsyncActionSequence& Type(FKey Key) = 0;` — Queues the series of events to invoke keyboard input for the key specified.
- L166 _public prototype_ `virtual IAsyncActionSequence& Type(TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for the character specified. Not all control and modifier keys are supported with this method of typing.
- L171 _public prototype_ `virtual IAsyncActionSequence& Type(const TArray<FKey>& Keys) = 0;` — Queues the series of events to invoke keyboard input for each key specified.
- L177 _public prototype_ `virtual IAsyncActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, const TCHAR* Text) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing.
- L183 _public prototype_ `virtual IAsyncActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FString Text) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each character of the string specified. Not all control and modifier keys are supported with this method of typing.
- L188 _public prototype_ `virtual IAsyncActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for the key specified.
- L194 _public prototype_ `virtual IAsyncActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, TCHAR Character) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for the character specified. Not all control and modifier keys are supported with this method of typing.
- L199 _public prototype_ `virtual IAsyncActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, const TArray<FKey>& Keys) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each key specified.
- L206 _public prototype_ `virtual IAsyncActionSequence& TypeChord(FKey Key1, FKey Key2) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L213 _public prototype_ `virtual IAsyncActionSequence& TypeChord(FKey Key1, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L220 _public prototype_ `virtual IAsyncActionSequence& TypeChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L227 _public prototype_ `virtual IAsyncActionSequence& TypeChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L234 _public prototype_ `virtual IAsyncActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L241 _public prototype_ `virtual IAsyncActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, TCHAR Character) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L248 _public prototype_ `virtual IAsyncActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L255 _public prototype_ `virtual IAsyncActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L261 _public prototype_ `virtual IAsyncActionSequence& Press(TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for pressing the specified character. The character will not be released, nor will their be repeat character events issued for holding the character.
- L267 _public prototype_ `virtual IAsyncActionSequence& Press(FKey Key) = 0;` — Queues the series of events to invoke keyboard input for pressing the specified key. The key will not be released, nor will their be repeat key events issued for holding the character.
- L273 _public prototype_ `virtual IAsyncActionSequence& Press(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke mouse input for pressing the specified button. The button will not be released, nor will their be repeat button events issued for holding the button.
- L279 _public prototype_ `virtual IAsyncActionSequence& Press(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, TCHAR Character) = 0;` — Queues a change of focus to the specified element, then a series of events to invoke keyboard input for pressing the specified character. The character will not be released, nor will their be repeat character events issued for holding the character.
- L285 _public prototype_ `virtual IAsyncActionSequence& Press(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key) = 0;` — Queues a change of focus to the specified element, then a series of events to invoke keyboard input for pressing the specified key. The key will not be released, nor will their be repeat key events issued for holding the character.
- L291 _public prototype_ `virtual IAsyncActionSequence& Press(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then a series of events to invoke mouse input for pressing the specified button. The button will not be released, nor will their be repeat button events issued for holding the button.
- L297 _public prototype_ `virtual IAsyncActionSequence& PressChord(FKey Key1, FKey Key2) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L303 _public prototype_ `virtual IAsyncActionSequence& PressChord(FKey Key1, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L309 _public prototype_ `virtual IAsyncActionSequence& PressChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L315 _public prototype_ `virtual IAsyncActionSequence& PressChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L321 _public prototype_ `virtual IAsyncActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L327 _public prototype_ `virtual IAsyncActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L333 _public prototype_ `virtual IAsyncActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L339 _public prototype_ `virtual IAsyncActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L345 _public prototype_ `virtual IAsyncActionSequence& Release(TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed.
- L351 _public prototype_ `virtual IAsyncActionSequence& Release(FKey Key) = 0;` — Queues the series of events to invoke keyboard input for releasing the specified key. The key will not be pressed if it is not currently being pressed.
- L357 _public prototype_ `virtual IAsyncActionSequence& Release(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke mouse input for releasing the specified button. The button will not be pressed if it is not currently being pressed.
- L363 _public prototype_ `virtual IAsyncActionSequence& Release(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed.
- L369 _public prototype_ `virtual IAsyncActionSequence& Release(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed.
- L375 _public prototype_ `virtual IAsyncActionSequence& Release(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke mouse input for releasing the specified button. The button will not be pressed if it is not currently being pressed.
- L381 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(FKey Key1, FKey Key2) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L387 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(FKey Key1, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L393 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L399 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L405 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L411 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L417 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L423 _public prototype_ `virtual IAsyncActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L428 _public prototype_ `virtual IAsyncActionSequence& Focus(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a change of focus to the element for the default user
- L433 _public prototype_ `virtual IAsyncActionSequence& Focus(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, uint32 UserFocus) = 0;` — Queues a change of focus to the element for the specified user
- L438 _public prototype_ `virtual bool IsExecuting() = 0;` — Checks whether the sequence is currently executing actions

#### class `IAsyncDriverSequence`  
`class IAsyncDriverSequence`  
_L444-457_
- desc: Represents a sequence of actions that can be performed as a single unit by the automation driver associted with this sequence
- L451 _public prototype_ `virtual IAsyncActionSequence& Actions() = 0;` — @return the sequence of actions this driver sequence represents; any actions called on this are queued for execution on the next Perform call
- L456 _public prototype_ `virtual TAsyncResult<bool> Perform() = 0;` — Executes all the actions that have been queued for this sequence. Additional actions cannot be queued while the sequence is being performed

#### class `IActionSequence`  
`class IActionSequence`  
_L459-881_
- L466 _public prototype_ `virtual IActionSequence& Wait(FTimespan Timespan) = 0;` — Queues a wait no shorter than for the specified Timespan
- L471 _public prototype_ `virtual IActionSequence& Wait(const FDriverWaitDelegate& Delegate) = 0;` — Queues a wait until the specified DriverWaitDelegate returns a PASSED or FAILED response
- L476 _public prototype_ `virtual IActionSequence& MoveToElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, int32 XOffset, int32 YOffset) = 0;` — Queues a move of the cursor over the center of the element offset by the specified amounts, triggering any hover cue the element may have
- L481 _public prototype_ `virtual IActionSequence& MoveToElement(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the center of the element, triggering any hover cue the element may have
- L486 _public prototype_ `virtual IActionSequence& MoveByOffset(int32 XOffset, int32 YOffset) = 0;` — Queues a move of the cursor from its current position by the specified offsets
- L491 _public prototype_ `virtual IActionSequence& MoveToPosition(const FVector2D& Position) = 0;` — Queues a move of the cursor from its current position to a new position which is specified
- L497 _public prototype_ `virtual IActionSequence& ScrollBy(float Delta) = 0;` — Queues the series of events to invoke a mouse wheel scroll by the specified delta at the current mouse position Most average user scrolling is limited to a range of -5 to 5.
- L502 _public prototype_ `virtual IActionSequence& ScrollBy(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, float Delta) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta
- L508 _public prototype_ `virtual IActionSequence& ScrollToBeginning(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the beginning
- L514 _public prototype_ `virtual IActionSequence& ScrollToBeginning(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, float Amount) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the beginning
- L520 _public prototype_ `virtual IActionSequence& ScrollToBeginningUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues the series of events to invoke a mouse wheel scroll until the specified locator is locates the desired element or the beginning is reached at the current cursor position
- L526 _public prototype_ `virtual IActionSequence& ScrollToBeginningUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ScrollableElementLocator, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the scrollable element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator locates the desired element or the beginning is reached
- L532 _public prototype_ `virtual IActionSequence& ScrollToEnd(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll, scrolling the element until it reaches the end
- L538 _public prototype_ `virtual IActionSequence& ScrollToEnd(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, float Amount) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll by the specified delta amount, scrolling the element until it reaches the end
- L544 _public prototype_ `virtual IActionSequence& ScrollToEndUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator locates the desired element or the end is reached
- L550 _public prototype_ `virtual IActionSequence& ScrollToEndUntil(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ScrollableElementLocator, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the scrollable element, then triggers the series of events to invoke a mouse wheel scroll until the specified locator locates the desired element or the end is reached
- L555 _public prototype_ `virtual IActionSequence& Click(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a click with the left mouse button
- L560 _public prototype_ `virtual IActionSequence& Click(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a click with the specified mouse button
- L565 _public prototype_ `virtual IActionSequence& Click(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke a click with the specified mouse button at the current cursor location
- L570 _public prototype_ `virtual IActionSequence& Click() = 0;` — Queues the series of events to invoke a click with the left mouse button at the current cursor location
- L575 _public prototype_ `virtual IActionSequence& DoubleClick(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a double click with the left mouse button
- L580 _public prototype_ `virtual IActionSequence& DoubleClick(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke a double click with the specified mouse button
- L585 _public prototype_ `virtual IActionSequence& DoubleClick(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke a double click with the specified mouse button at the current cursor location
- L590 _public prototype_ `virtual IActionSequence& DoubleClick() = 0;` — Queues the series of events to invoke a double click with the left mouse button at the current cursor location
- L596 _public prototype_ `virtual IActionSequence& Type(const TCHAR* Text) = 0;` — Queues the series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing.
- L602 _public prototype_ `virtual IActionSequence& Type(FString Text) = 0;` — Queues the series of events to invoke keyboard input for each character of the string specified. Not all control and modifier keys are supported with this method of typing.
- L607 _public prototype_ `virtual IActionSequence& Type(FKey Key) = 0;` — Queues the series of events to invoke keyboard input for the key specified.
- L613 _public prototype_ `virtual IActionSequence& Type(TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for the character specified. Not all control and modifier keys are supported with this method of typing.
- L618 _public prototype_ `virtual IActionSequence& Type(const TArray<FKey>& Keys) = 0;` — Queues the series of events to invoke keyboard input for each key specified.
- L624 _public prototype_ `virtual IActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, const TCHAR* Text) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each character specified. Not all control and modifier keys are supported with this method of typing.
- L630 _public prototype_ `virtual IActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FString Text) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each character of the string specified. Not all control and modifier keys are supported with this method of typing.
- L635 _public prototype_ `virtual IActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for the key specified.
- L641 _public prototype_ `virtual IActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, TCHAR Character) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for the character specified. Not all control and modifier keys are supported with this method of typing.
- L646 _public prototype_ `virtual IActionSequence& Type(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, const TArray<FKey>& Keys) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each key specified.
- L653 _public prototype_ `virtual IActionSequence& TypeChord(FKey Key1, FKey Key2) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L660 _public prototype_ `virtual IActionSequence& TypeChord(FKey Key1, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L667 _public prototype_ `virtual IActionSequence& TypeChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L674 _public prototype_ `virtual IActionSequence& TypeChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L681 _public prototype_ `virtual IActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L688 _public prototype_ `virtual IActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, TCHAR Character) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L695 _public prototype_ `virtual IActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L702 _public prototype_ `virtual IActionSequence& TypeChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the a change of focus to the specified element, then a series of events to invoke keyboard input for each argument in order from 1 to N and then releasing those keys in order from N to 1 Chord typing is intended to ease the to execution keyboard shortcuts, such as, CTRL + SHIFT + S
- L708 _public prototype_ `virtual IActionSequence& Press(TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for pressing the specified character. The character will not be released, nor will their be repeat character events issued for holding the character.
- L714 _public prototype_ `virtual IActionSequence& Press(FKey Key) = 0;` — Queues the series of events to invoke keyboard input for pressing the specified key. The key will not be released, nor will their be repeat key events issued for holding the character.
- L720 _public prototype_ `virtual IActionSequence& Press(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke mouse input for pressing the specified button. The button will not be released, nor will their be repeat button events issued for holding the button.
- L726 _public prototype_ `virtual IActionSequence& Press(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, TCHAR Character) = 0;` — Queues a change of focus to the specified element, then a series of events to invoke keyboard input for pressing the specified character. The character will not be released, nor will their be repeat character events issued for holding the character.
- L732 _public prototype_ `virtual IActionSequence& Press(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key) = 0;` — Queues a change of focus to the specified element, then a series of events to invoke keyboard input for pressing the specified key. The key will not be released, nor will their be repeat key events issued for holding the character.
- L738 _public prototype_ `virtual IActionSequence& Press(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then a series of events to invoke mouse input for pressing the specified button. The button will not be released, nor will their be repeat button events issued for holding the button.
- L744 _public prototype_ `virtual IActionSequence& PressChord(FKey Key1, FKey Key2) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L750 _public prototype_ `virtual IActionSequence& PressChord(FKey Key1, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L756 _public prototype_ `virtual IActionSequence& PressChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L762 _public prototype_ `virtual IActionSequence& PressChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L768 _public prototype_ `virtual IActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L774 _public prototype_ `virtual IActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L780 _public prototype_ `virtual IActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L786 _public prototype_ `virtual IActionSequence& PressChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from 1 to N. They will not be released.
- L792 _public prototype_ `virtual IActionSequence& Release(TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed.
- L798 _public prototype_ `virtual IActionSequence& Release(FKey Key) = 0;` — Queues the series of events to invoke keyboard input for releasing the specified key. The key will not be pressed if it is not currently being pressed.
- L804 _public prototype_ `virtual IActionSequence& Release(EMouseButtons::Type MouseButton) = 0;` — Queues the series of events to invoke mouse input for releasing the specified button. The button will not be pressed if it is not currently being pressed.
- L810 _public prototype_ `virtual IActionSequence& Release(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed.
- L816 _public prototype_ `virtual IActionSequence& Release(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for releasing the specified character. The character will not be pressed if it is not currently being pressed.
- L822 _public prototype_ `virtual IActionSequence& Release(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, EMouseButtons::Type MouseButton) = 0;` — Queues a move of the cursor over the element, then triggers the series of events to invoke mouse input for releasing the specified button. The button will not be pressed if it is not currently being pressed.
- L828 _public prototype_ `virtual IActionSequence& ReleaseChord(FKey Key1, FKey Key2) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L834 _public prototype_ `virtual IActionSequence& ReleaseChord(FKey Key1, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L840 _public prototype_ `virtual IActionSequence& ReleaseChord(FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L846 _public prototype_ `virtual IActionSequence& ReleaseChord(FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L852 _public prototype_ `virtual IActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L858 _public prototype_ `virtual IActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L864 _public prototype_ `virtual IActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, FKey Key3) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L870 _public prototype_ `virtual IActionSequence& ReleaseChord(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FKey Key1, FKey Key2, TCHAR Character) = 0;` — Queues a change of focus to the element, then triggers the series of events to invoke keyboard input for each argument in order from N to 1. They will not be pressed if it is not currently being pressed.
- L875 _public prototype_ `virtual IActionSequence& Focus(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator) = 0;` — Queues a change of focus to the element for the default user
- L880 _public prototype_ `virtual IActionSequence& Focus(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, uint32 UserFocus) = 0;` — Queues a change of focus to the element for the specified user

#### class `IDriverSequence`  
`class IDriverSequence`  
_L886-899_
- desc: Represents a sequence of actions that can be performed as a single unit by the automation driver associted with this sequence
- L893 _public prototype_ `virtual IActionSequence& Actions() = 0;` — @return the sequence of actions this driver sequence represents; any actions called on this are queued for execution on the next Perform call
- L898 _public prototype_ `virtual bool Perform() = 0;` — Executes all the actions that have been queued for this sequence.

### `Source/Developer/AutomationDriver/Public/IElementLocator.h` (Public)


#### class `IElementLocator`  
`class IElementLocator`  
_L12-25_
- desc: Represents an object whose sole purpose is to discover one or more application elements
- L19 _public prototype_ `virtual FString ToDebugString() const = 0;` — @return a string only to be used for debugging and logging purposes that represents this locator
- L24 _public prototype_ `virtual void Locate(TArray<TSharedRef<IApplicationElement>>& OutElements) const = 0;` — @return Attempts to locate a specific element or set of elements in the application

### `Source/Developer/AutomationDriver/Public/LocateBy.h` (Public)


#### class `By`  
`class By`  
_L18-371_
- desc: Represents a collection of fluent helper functions designed to make accessing and creating element locators easy
- L29 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Delegate(const FLocateSlateWidgetElementDelegate& Value, FStringView DebugName = { });` — Creates a new element locator that exposes the collection of SWidgets returned from the FLocateSlateWidgetElementDelegate as discovered elements @param Value - The delegate to use @param DebugName - The string to display for errors when no elements can be located @return a locator which uses the specified delegate to discover appropriate elements
- L38 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Delegate(const FLocateSlateWidgetPathElementDelegate& Value, FStringView DebugName = { });` — Creates a new element locator that exposes the collection of FWidgetPaths returned from the FLocateSlateWidgetElementDelegate as discovered elements @param Value - The delegate to use @param DebugName - The string to display for errors when no elements can be located @return a locator which uses the specified delegate to discover appropriate elements
- L47 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> WidgetLambda(const TFunction<void(TArray<TSharedRef<SWidget>>&)>& Value, FStringView DebugName = { });` — Creates a new element locator that exposes the collection of SWidgets returned from the lambda as discovered elements @param Value - The lambda to use @param DebugName - The string to display for errors when no elements can be located @return a locator which uses the specified lambda to discover appropriate elements
- L56 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> WidgetPathLambda(const TFunction<void(TArray<FWidgetPath>&)>& Value, FStringView DebugName = { });` — Creates a new element locator that exposes the collection of FWidgetPaths returned from the lambda as discovered elements @param Value - The lambda to use @param DebugName - The string to display for errors when no elements can be located @return a locator which uses the specified lambda to discover appropriate elements
- L63 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const FString& Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L72 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const FDriverElementRef& Root, const FString& Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id, starting from the Root element given to the function @param Root - The reference to the element where the search will be started from @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L79 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const FName& Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L88 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const FDriverElementRef& Root, const FName& Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id, starting from the Root element given to the function @param Root - The reference to the element where the search will be started from @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L96 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const TCHAR* Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L105 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const FDriverElementRef& Root, const TCHAR* Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id, starting from the Root element given to the function @param Root - The reference to the element where the search will be started from @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L113 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const char* Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L122 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Id(const FDriverElementRef& Root, const char* Value);` — Creates a new element locator that limits its discovered elements to ones with the specified Id, starting from the Root element given to the function @param Root - The reference to the element where the search will be started from @param Value - The MetaData ID of the element to find @return a locator which uses the specified Id to discover appropriate elements
- L145 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const FString& Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path" Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L170 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const FDriverElementRef& Root, const FString& Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path", starting from the Root element given to the function Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Root - The reference to the element where the search will be started from @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L194 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const FName& Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path" Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L219 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const FDriverElementRef& Root, const FName& Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path", starting from the Root element given to the function Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Root - The reference to the element where the search will be started from @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L242 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const TCHAR* Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path" Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L267 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const FDriverElementRef& Root, const TCHAR* Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path", starting from the Root element given to the function Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Root - The reference to the element where the search will be started from @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L290 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const char* Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path" Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L315 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Path(const FDriverElementRef& Root, const char* Value);` — Creates a new element locator that limits its discovered elements to ones matching the specified "path", starting from the Root element given to the function Path Example: "#Suite//Piano/Key//<STextBlock>" Path Syntax: #Suite = # represents that the following text is an explicit Id, in the case of a SWidget it needs to be tagged with the driver Id metadata Piano = plain text represents general tags, in the case of a SWidget it needs to have a Tag or TagMetadata with the appropriate plain text value <STextBlock> = <> represents types, in the case of a SWidget it should be the explicit type used in the SNew construction Hierarchy is represented by forward slashes / = a single forward slash represents that the next value must match a direct child of the element matched before it // = a double forward slash represents that the next value must match any descendant of the element matched before it Reference the AutomationDriver.spec.cpp expectations for additional examples of the syntax in use @param Root - The reference to the element where the search will be started from @param Value - The path to use @return a locator which uses the specified path to discover appropriate elements
- L321 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Cursor();` — Creates a new element locator that limits its discovered elements to the one under the cursors current position @return a locator which uses the cursor position to discover appropriate elements
- L327 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> KeyboardFocus();` — Creates a new element locator that limits its discovered element to the one that's currently in keyboard focus @return a locator which uses the keyboard focus to discover the appropriate element
- L333 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> UserFocus(uint32 UserIndex = 0);` — Creates a new element locator that limits its discovered element to the one that's currently in user focus @return a locator which uses the user focus to discover the appropriate element

#### class `By::TextFilter`  
`class TextFilter`  
_L335-370_
- L349 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Contains( const FElementLocatorRef& RootLocator, const FString& Value, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase, ESearchDir::Type SearchDir = ESearchDir::FromStart );` — Creates a new element locator that limits the elements discovered by the root locator provided to the function to those containing the specified text substring. @param RootLocator - The reference to the element locator where the search will be started from @param Value - The text of the element to find @param SearchCase - Indicates whether the search is case sensitive or not ( defaults to ESearchCase::IgnoreCase ) @param SearchDir - Indicates whether the search starts at the beginning or at the end ( defaults to ESearchDir::FromStart ) @return a locator which uses the specified root locator and a text string to discover appropriate elements
- L365 _public prototype_ `static TSharedRef<IElementLocator, ESPMode::ThreadSafe> Equals( const FElementLocatorRef& RootLocator, const FString& Value, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive );` — Creates a new element locator that limits the elements discovered by the root locator provided to the function to those containing the specified text. @param RootLocator - The reference to the element locator where the search will be started from @param Value - The text of the element to find @param SearchCase - Indicates whether the search is case sensitive or not ( defaults to ESearchCase::CaseSensitive ) @return a locator which uses the specified root locator and a text string to discover appropriate elements

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUTOMATIONDRIVER_API`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FLocateSlateWidgetElementDelegate, TArray<TSharedRef<SWidget>>& );`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FLocateSlateWidgetElementDelegate, TArray<TSharedRef<SWidget>>& );`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FLocateSlateWidgetPathElementDelegate, TArray<FWidgetPath>& );`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FLocateSlateWidgetPathElementDelegate, TArray<FWidgetPath>& );`

### `Source/Developer/AutomationDriver/Public/WaitUntil.h` (Public)


#### struct `FDriverWaitResponse`  
`struct FDriverWaitResponse`  
_L18-56_
- desc: Represents the state of an active wait action for the driver
- L32 _public prototype_ `static FDriverWaitResponse Passed();` — @return a FDriverWaitResponse with a state of PASSED and a wait of zero
- L37 _public prototype_ `static FDriverWaitResponse Wait();` — @return a FDriverWaitResponse with a state of WAIT and a wait of 0.5 seconds
- L42 _public prototype_ `static FDriverWaitResponse Wait(FTimespan Timespan);` — @return a FDriverWaitResponse with a state of WAIT and a wait of the specified timespan
- L47 _public prototype_ `static FDriverWaitResponse Failed();` — @return a FDriverWaitResponse with a state of FAILED and a wait of zero
- L49 _public prototype_ `FDriverWaitResponse(EState InState, FTimespan InNextWait);`
- L52 _public member_ `const FTimespan NextWait;` — How long the driver should wait before re-evaluating the wait condition again
- L55 _public member_ `const EState State;` — Whether the wait condition is completely finished or should be rescheduled again for execution

#### enum `FDriverWaitResponse::EState`  
`enum class EState : uint8`  
_L22-27_
- L24 _public enumerator_ `PASSED`
- L25 _public enumerator_ `WAIT`
- L26 _public enumerator_ `FAILED`

#### class `FWaitTimeout`  
`class FWaitTimeout`  
_L64-76_
- desc: A fluent wrapper around timespan to enforce obvious differences between specified Timeout and Interval values for waits
- L68 _public prototype_ `static FWaitTimeout InMilliseconds(double Value);`
- L69 _public prototype_ `static FWaitTimeout InSeconds(double Value);`
- L70 _public prototype_ `static FWaitTimeout InMinutes(double Value);`
- L71 _public prototype_ `static FWaitTimeout InHours(double Value);`
- L73 _public prototype_ `explicit FWaitTimeout(FTimespan InTimespan);`
- L75 _public member_ `const FTimespan Timespan;`

#### class `FWaitInterval`  
`class FWaitInterval`  
_L81-93_
- desc: A fluent wrapper around timespan to enforce obvious differences between specified Timeout and Interval values for waits
- L85 _public prototype_ `static FWaitInterval InMilliseconds(double Value);`
- L86 _public prototype_ `static FWaitInterval InSeconds(double Value);`
- L87 _public prototype_ `static FWaitInterval InMinutes(double Value);`
- L88 _public prototype_ `static FWaitInterval InHours(double Value);`
- L90 _public prototype_ `explicit FWaitInterval(FTimespan InTimespan);`
- L92 _public member_ `const FTimespan Timespan;`

#### class `Until`  
`class Until`  
_L98-220_
- desc: Represents a collection of fluent helper functions designed to make accessing and creating driver wait delegates easier
- L105 _public prototype_ `static FDriverWaitDelegate ElementExists(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers elements or if the specified timeout timespan elapses
- L111 _public prototype_ `static FDriverWaitDelegate ElementExists(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers elements or if the specified timeout timespan elapses; The element locator is only re-evaluated at the specified wait interval
- L116 _public prototype_ `static FDriverWaitDelegate ElementIsVisible(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers visible elements or if the specified timeout timespan elapses
- L122 _public prototype_ `static FDriverWaitDelegate ElementIsVisible(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers visible elements or if the specified timeout timespan elapses; The element locator is only re-evaluated at the specified wait interval
- L127 _public prototype_ `static FDriverWaitDelegate ElementIsHidden(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers hidden elements or if the specified timeout timespan elapses
- L133 _public prototype_ `static FDriverWaitDelegate ElementIsHidden(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers hidden elements or if the specified timeout timespan elapses; The element locator is only re-evaluated at the specified wait interval
- L138 _public prototype_ `static FDriverWaitDelegate ElementIsInteractable(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers interactable elements or if the specified timeout timespan elapses
- L144 _public prototype_ `static FDriverWaitDelegate ElementIsInteractable(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers interactable elements or if the specified timeout timespan elapses; The element locator is only re-evaluated at the specified wait interval
- L150 _public prototype_ `static FDriverWaitDelegate ElementIsScrolledToBeginning(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers a scrollable element whose scroll position is at the beginning or if the specified timeout timespan elapses
- L157 _public prototype_ `static FDriverWaitDelegate ElementIsScrolledToBeginning(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers a scrollable element whose scroll position is at the beginning or if the specified timeout timespan elapses The element locator is only re-evaluated at the specified wait interval
- L163 _public prototype_ `static FDriverWaitDelegate ElementIsScrolledToEnd(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers a scrollable element whose scroll position is at the end or if the specified timeout timespan elapses
- L170 _public prototype_ `static FDriverWaitDelegate ElementIsScrolledToEnd(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers a scrollable element whose scroll position is at the end or if the specified timeout timespan elapses The element locator is only re-evaluated at the specified wait interval
- L175 _public prototype_ `static FDriverWaitDelegate ElementIsFocusedByKeyboard(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes its wait only if the specified element locator discovers an element focused by the default user or if the specified timeout timespan elapses
- L181 _public prototype_ `static FDriverWaitDelegate ElementIsFocusedByKeyboard(const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers an element focused by the default user or if the specified timeout timespan elapses; The element locator is only re-evaluated at the specified wait interval
- L186 _public prototype_ `static FDriverWaitDelegate ElementIsFocusedByUser(uint32 UserIndex, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitTimeout Timeout);` — Creates a new wait delegate which completes its wait only if the specified element locator discovers an element focused by the specified user or if the specified timeout timespan elapses
- L192 _public prototype_ `static FDriverWaitDelegate ElementIsFocusedByUser(uint32 UserIndex, const TSharedRef<IElementLocator, ESPMode::ThreadSafe>& ElementLocator, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified element locator discovers an element focused by the specified user or if the specified timeout timespan elapses; The element locator is only re-evaluated at the specified wait interval
- L197 _public prototype_ `static FDriverWaitDelegate Condition(const TFunction<bool()>& Function, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified condition returns true or if the specified timeout timespan elapses
- L203 _public prototype_ `static FDriverWaitDelegate Condition(const TFunction<bool()>& Function, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified condition returns true or if the specified timeout timespan elapses The lambda is only re-evaluated at the specified wait interval
- L208 _public prototype_ `static FDriverWaitDelegate Condition(const FDriverWaitConditionDelegate& Delegate, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified condition returns true or if the specified timeout timespan elapses
- L214 _public prototype_ `static FDriverWaitDelegate Condition(const FDriverWaitConditionDelegate& Delegate, FWaitInterval Interval, FWaitTimeout Timeout);` — Creates a new wait delegate which completes it's wait only if the specified condition returns true or if the specified timeout timespan elapses The delegate is only re-evaluated at the specified wait interval
- L219 _public prototype_ `static FDriverWaitDelegate Lambda(const TFunction<FDriverWaitResponse(const FTimespan&)>& Value);` — Creates a new wait delegate which drives its state off the result of the specified lambda

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUTOMATIONDRIVER_API`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FDriverWaitResponse, FDriverWaitDelegate, const FTimespan& );`
- L58 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FDriverWaitResponse, FDriverWaitDelegate, const FTimespan& );`
- L59 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FDriverWaitConditionDelegate);`
- L59 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FDriverWaitConditionDelegate);`
