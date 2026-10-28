# Editor / ActionableMessage

- module root: `Source/Editor/ActionableMessage`
- headers: 2; symbols: 35
- symbol kinds: class=3, function=5, macro=2, member=16, prototype=8, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore, UnrealEd

### `Source/Editor/ActionableMessage/Public/ActionableMessageSubsystem.h` (Public)


#### struct `FActionableMessage`  
`struct FActionableMessage`  
_L12-38_
- L17 _public member_ `FText Message;` — The message that will be displayed in the widget.
- L22 _public member_ `FText ActionMessage;` — The text displayed inside the action button, if any.
- L27 _public member_ `FText Tooltip;` — The tooltip of the widget.
- L32 _public member_ `TFunction<void()> ActionCallback;` — The callback associated with the action button, if any.
- L37 _public member_ `bool bForceExpand = false;` — If true, this message requires the panel to be expanded.

#### class `UActionableMessageSubsystem`  
`class UActionableMessageSubsystem : public UWorldSubsystem`  
_L46-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: Used to push messages that will be used by a viewport widget to present to the user.
- L55 _public function_ `const TMap<FName, TSharedPtr<FActionableMessage>>& GetActionableMessages() const` — Gets all current actionable messages. @return A map containing current actionable messages.
- L62 _public prototype_ `void SetActionableMessage(FName InProvider, const FActionableMessage& InActionableMessage);` — Pushes a unique actionable message. @param InProvider The name of the entry. @param InActionableMessage The content of the actionable message.
- L68 _public prototype_ `void ClearActionableMessage(FName InProvider);` — Removes an entry from the current actionable messages. @param InProvider The name of the entry to remove.
- L74 _public function_ `uint32 GetStateID() const` — Returns the current stateID. Any modification in the current entries will update it. @return the current stateID
- L77 _private member_ `TMap<FName, TSharedPtr<FActionableMessage>> ProviderActionableMessageMap;`
- L78 _private member_ `uint32 StateID = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ACTIONABLEMESSAGE_API`
- L40 _prototype_ `FORCEINLINE bool operator!=(const FActionableMessage& LHS, const FActionableMessage& RHS);`

### `Source/Editor/ActionableMessage/Public/SActionableMessageViewportWidget.h` (Public)


#### class `SActionableMessageEntry`  
`class SActionableMessageEntry : public SCompoundWidget`  
_L14-27_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SActionableMessageEntry)`
- L18 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FActionableMessage>, ActionableMessage) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `void SetActionableMessage(TSharedPtr<FActionableMessage> InActionableMessage);`
- L25 _private member_ `TSharedPtr<FActionableMessage> ActionableMessage;`
- L26 _private member_ `FOnClicked OnClicked;`

#### class `SActionableMessageViewportWidget`  
`class SActionableMessageViewportWidget : public SCompoundWidget`  
_L29-51_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SActionableMessageViewportWidget)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `EVisibility GetVisibility();`
- L38 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FActionableMessage> InActionableMessage, const TSharedRef<STableViewBase>& OwnerTable);`
- L41 _private function_ `bool IsExpanded() const`
- L44 _private member_ `TSharedPtr<SListView<TSharedPtr<FActionableMessage>>> ActionableMessageList;`
- L45 _private member_ `TSharedPtr<STextBlock> TextBlock;`
- L46 _private member_ `TArray<TSharedPtr<FActionableMessage>> ActionableMessages;`
- L47 _private member_ `uint32 CachedStateID = 0;`
- L48 _private member_ `TWeakObjectPtr<const UObject> CachedDataSourceID;`
- L49 _private member_ `bool bExpanded = false;`
- L50 _private member_ `bool bForceExpand = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ACTIONABLEMESSAGE_API`
