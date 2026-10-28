# Editor / InputBindingEditor

- module root: `Source/Editor/InputBindingEditor`
- headers: 5; symbols: 62
- symbol kinds: class=4, function=11, member=17, prototype=30
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, InputCore, PropertyEditor, Settings, SettingsEditor, Slate, SlateCore, UnrealEd

### `Source/Editor/InputBindingEditor/Private/EditorKeyboardShortcutSettings.h` (Private)


#### class `UEditorKeyboardShortcutSettings`  
`class UEditorKeyboardShortcutSettings : public UDeveloperSettings`  
_L11-17_
- reflection: `UCLASS(config=EditorKeyBindings, meta=(DisplayName="Keyboard Shortcuts"))`
- inherits: `UDeveloperSettings`
- L16 _public function_ `virtual bool SupportsAutoRegistration() const override`

### `Source/Editor/InputBindingEditor/Private/Widgets/SChordEditBox.h` (Private)


#### class `SChordEditBox`  
`class SChordEditBox : public SCompoundWidget`  
_L23-95_
- inherits: `SCompoundWidget`
- desc: A widget that adds visuals to an SChordEditor
- L28 _public function_ `SLATE_BEGIN_ARGS( SChordEditBox )`
- L37 _public prototype_ `void Construct( const FArguments& InArgs, TSharedPtr<FUICommandInfo> InputCommand, EMultipleKeyBindingIndex ChordIndex );` — Constructs the widget. @param InArgs The Slate argument list.
- L41 _private prototype_ `const FSlateBrush* GetBorderImage() const;` — @return Border image for the text box based on the hovered and focused state
- L43 _private prototype_ `FText GetNotificationMessage() const;`
- L46 _private prototype_ `void OnChordEditorLostFocus();` — Called when the chord editor loses focus
- L49 _private prototype_ `void OnChordEditingStarted();` — Called when editing starts in the chord editor
- L52 _private prototype_ `void OnChordEditingStopped();` — Called when editing stops in the chord editor
- L55 _private prototype_ `void OnChordChanged();` — Called when the edited chord changes
- L58 _private prototype_ `EVisibility GetChordRemoveButtonVisibility() const;` — @return the visibility of the chord edit button
- L61 _private prototype_ `FReply OnChordRemoveButtonClicked();` — Called when the chord edit button is clicked
- L64 _private prototype_ `FReply OnAcceptNewChordButtonClicked();` — Called when the accept button is clicked.
- L67 _private prototype_ `TSharedRef<SWidget> OnGetContentForConflictPopup();` — @return content to be shown in the key binding conflict pop-up
- L70 _private prototype_ `void OnConflictPopupOpenChanged(bool bIsOpen);` — Called when conflict popup opens or closes
- L73 _private prototype_ `EVisibility GetNotificationVisibility() const;` — @return The visibility of the duplicate binding notification area
- L74 _private prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent );`
- L79 _private member_ `TSharedPtr<class SChordEditor> ChordEditor;` — The chord editor for this box
- L82 _private member_ `TSharedPtr<SMenuAnchor> ConflictPopup;` — Menu anchor where the conflict pop-up is shown
- L85 _private member_ `mutable TSharedPtr<SButton> ChordAcceptButton;` — The button for committing chord
- L88 _private member_ `const FSlateBrush* BorderImageNormal;` — Styling: border image to draw when not hovered or focused
- L91 _private member_ `const FSlateBrush* BorderImageHovered;` — Styling: border image to draw when hovered
- L94 _private member_ `const FSlateBrush* BorderImageFocused;` — Styling: border image to draw when focused

### `Source/Editor/InputBindingEditor/Private/Widgets/SChordEditor.h` (Private)


#### class `SChordEditor`  
`class SChordEditor : public SEditableText`  
_L23-148_
- inherits: `SEditableText`
- desc: A specialized text edit box that visualizes a new chord being entered           .
- L28 _public function_ `SLATE_BEGIN_ARGS( SChordEditor )`
- L38 _public function_ `SChordEditor() : bIsEditing( false ) , bIsTyping( false )` — Default constructor.
- L51 _public prototype_ `void Construct( const FArguments& InArgs, TSharedPtr<FUICommandInfo> InputCommand, EMultipleKeyBindingIndex ChordIndex);` — Constructs the widget. @param InArgs The Slate argument list. @param InputCommand
- L53 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L56 _public prototype_ `void StartEditing();` — Starts editing the chord.
- L59 _public prototype_ `void StopEditing();` — Stops editing the chord.
- L62 _public prototype_ `void CommitNewChord();` — Commits the new chord to the commands active chord.
- L65 _public prototype_ `void RemoveActiveChord();` — Removes the active chord from the command.
- L68 _public function_ `bool IsEditing() const` — @return Whether or not we are in editing mode.
- L71 _public function_ `bool IsTyping() const` — @return True if the user is physically typing a key.
- L74 _public function_ `bool IsEditedChordValid() const` — @return Whether or not the chord being edited is valid.
- L77 _public function_ `bool IsActiveChordValid() const` — @return Whether or not the command has a valid chord.
- L80 _public function_ `const FText& GetNotificationText() const` — @return the Notification message being displayed if any.
- L83 _public function_ `bool HasConflict() const` — @return true if the edited chord has a conflict with an existing chord.
- L88 _private member_ `static TWeakPtr<SChordEditor> ChordBeingEdited;` — Chord that is currently being edited.
- L90 _private prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L91 _private prototype_ `virtual FReply OnKeyUp( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L92 _private prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L93 _private prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L94 _private prototype_ `virtual void OnFocusLost( const FFocusEvent& InFocusEvent ) override;`
- L95 _private prototype_ `virtual FReply OnKeyChar( const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent ) override;`
- L102 _private prototype_ `void OnChordTyped( const FInputChord& NewChord );` — Called when the chord changes. @param NewChord The new chord.
- L109 _private prototype_ `void OnChordCommitted( const FInputChord& NewChord );` — Called when the chord changes. @param NewChord The chord to commit.
- L112 _private prototype_ `FText OnGetChordInputText() const;` — @return The chord input text (If editing, the edited chord, otherwise the active chord)
- L115 _private prototype_ `FText OnGetChordInputHintText() const;` — @return The hint text to display in the text box if it is empty
- L120 _private member_ `TSharedPtr<FUICommandInfo> CommandInfo;` — The command we are editing a chord for.
- L123 _private member_ `EMultipleKeyBindingIndex ChordIndex;` — The index of the chord we are editing (within the multiple key bindings.
- L126 _private member_ `FSimpleDelegate OnEditBoxLostFocus;` — Delegate to execute when the edit box loses focus.
- L129 _private member_ `FSimpleDelegate OnChordChanged;` — Delegate to execute when the chord changes.
- L132 _private member_ `FSimpleDelegate OnEditingStopped;` — Delegate to execute when we stop editing.
- L135 _private member_ `FSimpleDelegate OnEditingStarted;` — Delegate to execute when we start editing.
- L138 _private member_ `FText NotificationMessage;` — The notification message (duplicate bindings) being displayed.
- L141 _private member_ `FInputChord EditingInputChord;` — Temp chord being edited.
- L144 _private member_ `bool bIsEditing;` — Whether or not we are in edit mode.
- L147 _private member_ `bool bIsTyping;` — Whether or not the user is physically typing a new key.

### `Source/Editor/InputBindingEditor/Public/InputBindingEditor.h` (Public)
_(no declarations extracted)_

### `Source/Editor/InputBindingEditor/Public/Interfaces/IInputBindingEditorModule.h` (Public)


#### class `IInputBindingEditorModule`  
`class IInputBindingEditorModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- desc: Interface for input binding editor modules.
- L17 _public prototype_ `virtual ~IInputBindingEditorModule( ) = default;` — Virtual destructor.
