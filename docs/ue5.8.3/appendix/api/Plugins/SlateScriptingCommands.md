# Plugins / SlateScriptingCommands

- module root: `Plugins/Slate/SlateScripting/Source/SlateScriptingCommands`
- headers: 2; symbols: 79
- symbol kinds: class=2, delegate=3, function=8, macro=1, member=17, prototype=44, struct=4
- PrivateDependencyModuleNames: InputCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore

### `Plugins/Slate/SlateScripting/Source/SlateScriptingCommands/Public/SlateScriptingCommandsModule.h` (Public)


#### class `FSlateScriptingCommandsModule`  
`class FSlateScriptingCommandsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Slate/SlateScripting/Source/SlateScriptingCommands/Public/UICommandsScriptingSubsystem.h` (Public)


#### struct `FScriptingCommandInfo`  
`struct FScriptingCommandInfo`  
_L25-62_
- reflection: `USTRUCT(BlueprintType)`
- desc: The data defining a scripting command. At the exception of its delegates.
- L31 _public member_ `FName ContextName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor Scripting | Commands")` — The editor context this command is bound to
- L35 _public member_ `FName Set;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor Scripting | Commands")` — The command set this command belongs to. This is to avoid conflicts and could refer to the owner of the command
- L39 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor Scripting | Commands")` — The command name. Must be unique in its set.
- L43 _public member_ `FText Label;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor Scripting | Commands")` — The command label or what name will be displayed for it
- L47 _public member_ `FText Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor Scripting | Commands")` — The description of the command
- L51 _public member_ `FInputChord InputChord;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor Scripting | Commands")` — The input chord to bound to the command
- L54 _public prototype_ `bool Equals(const FScriptingCommandInfo& InCommandInfo, const bool bCheckInputChord = false) const;` — Compares this command info with the given one per context, set, name and optionally input chord
- L57 _public function_ `FName GetFullName() const` — Builds a full name in the format context.set.command_name to avoid conflicts with commands registered in different contexts/sets

#### struct `FScriptingCommand`  
`struct FScriptingCommand`  
_L74-115_
- reflection: `USTRUCT()`
- desc: All the internal data related to a scripting command as well as methods to easily expose the command to the binding manager
- L78 _public prototype_ `FScriptingCommand() = default;`
- L80 _public function_ `FScriptingCommand(const FScriptingCommandInfo& InCommandInfo, const FExecuteAction InOnExecuteAction, const FCanExecuteAction InOnCanExecuteAction) : CommandInfo(InCommandInfo), OnExecuteAction(InOnExecuteAction), OnCanExecuteAction(InOnCanExecuteAction)`
- L87 _public member_ `FScriptingCommandInfo CommandInfo;` — The command definition
- L90 _public member_ `FExecuteAction OnExecuteAction;` — The delegate to call when executing the command
- L93 _public member_ `FCanExecuteAction OnCanExecuteAction;` — The delegate to call to check whether the command can be executed
- L95 _public function_ `inline bool operator==(const FScriptingCommand& Other) const`
- L96 _public function_ `inline bool operator!=(const FScriptingCommand& Other) const`
- L98 _public function_ `inline bool operator==(const FName OtherName) const`
- L99 _public function_ `inline bool operator!=(const FName OtherName) const`
- L102 _public function_ `FName GetFullName() const` — Builds a full name in the format context.set.command_name to avoid conflicts with commands registered in different contexts/sets
- L111 _public prototype_ `TSharedPtr<FUICommandInfo> MakeUICommandInfo() const;` — Registers a new UICommandInfo in the associated context through the binding manager. At this point, the command is exposed to the manager but not mapped to any command list.
- L114 _public prototype_ `bool UnregisterUICommandInfo() const;` — Unregisters this command's UICommandInfo from its associated context through the binding manager

#### struct `FScriptingCommandsContext`  
`struct FScriptingCommandsContext`  
_L122-157_
- reflection: `USTRUCT()`
- desc: The list of commands and UI Command Lists associated with a context. This enables easier management of commands within registered contexts and their UI Command Lists.
- L126 _public prototype_ `FScriptingCommandsContext() = default;`
- L128 _public function_ `FScriptingCommandsContext(const FName InContextName) : ContextName(InContextName)`
- L131 _public member_ `FName ContextName;` — The context these command lists are bound to
- L134 _public member_ `TArray<TWeakPtr<FUICommandList>> CommandLists;` — An array of command list associated to the given context
- L137 _public member_ `TArray<TSharedPtr<FScriptingCommand>> ScriptingCommands;` — The commands bound in these command lists
- L141 _public prototype_ `bool MapCommand(const TSharedRef<FScriptingCommand> ScriptingCommand);` — Maps the given command to all the command lists of this context
- L144 _public prototype_ `bool UnmapCommand(const TSharedRef<FScriptingCommand> ScriptingCommand);` — Unmaps the given command from all the command lists of this context
- L147 _public prototype_ `bool RegisterCommandList(const TSharedRef<FUICommandList> CommandList);` — Registers a command list in this context then map to it all commands existing within this context
- L150 _public prototype_ `bool UnregisterCommandList(const TSharedRef<FUICommandList> CommandList);` — Unregisters command list from this context then unmap from it all commands existing within this context
- L153 _public prototype_ `void MapAllCommands(TSharedRef<FUICommandList> CommandList);` — Maps all commands existing within this context to the given command list
- L156 _public prototype_ `void UnmapAllCommands(TSharedRef<FUICommandList> CommandList);` — Unmaps all commands existing within this context from the given command list

#### struct `FScriptingCommandSet`  
`struct FScriptingCommandSet`  
_L164-173_
- reflection: `USTRUCT()`
- desc: To avoid conflicts between scripts, each command is associated to a command set which must be registered manually.
- L169 _public member_ `TArray<TSharedPtr<FScriptingCommand>> ScriptingCommands;` — The commands in this set
- L172 _public member_ `bool bCanExecuteCommands = true;` — Whether the commands in this set are enabled

#### class `UUICommandsScriptingSubsystem`  
`class UUICommandsScriptingSubsystem : public UEngineSubsystem`  
_L180-370_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: UEditorInputSubsystem Subsystem for dynamically registering editor commands through scripting
- L192 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem Interface: handles initialization of instances of the system This is where the subsystem binds to the CommandListRegistered delegate of the InputBindingManager To expose command lists from external systems to this subsystem, call FInputBindingManager::RegisterCommandList from the external system. The binding manager will then broadcast the registered command list to all subscribers.
- L195 _public prototype_ `virtual void Deinitialize() override;` — USubsystem Interface: handles deinitialization of instances of the system
- L206 _public prototype_ `void RegisterCommandListForContext(const FName ContextName, TSharedRef<FUICommandList> CommandList);` — Registers a command list in the given context. Optionally registering the context itself if it does not exist Note the context should already be existing and registered through the binding manager. This should be called by modules and tools looking to expose their command lists to the subsystem. @param	ContextName		The context name as defined in the binding manager @param	CommandList		The command list to register in this context
- L213 _public prototype_ `void UnregisterCommandListForContext(const FName ContextName, TSharedRef<FUICommandList> CommandList);` — Unregisters a command list from the given context. @param	ContextName		The context name as defined in the binding manager @param	CommandList		The command list to register in this context
- L219 _public prototype_ `bool UnregisterContext(const FName ContextName);` — Unregisters all command lists from the given context. @param	ContextName		The context name as defined in the binding manager
- L231 _public prototype_ `bool RegisterCommand(FScriptingCommandInfo CommandInfo, FExecuteCommand OnExecuteCommand, bool bOverrideExisting = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands |")` — Registers a command within the given context and set. The set must be registered beforehand. @param	CommandInfo			The command infos such as name, label, description and input chord. @param	OnExecuteCommand	The delegate to be executed for handling this command. @param	bOverrideExisting	Whether existing command with matching context, set and name should be overriden @return Whether the command was succesfully registered
- L243 _public prototype_ `bool RegisterCommandChecked(FScriptingCommandInfo CommandInfo, FExecuteCommand OnExecuteCommand, FCanExecuteCommand OnCanExecuteCommand, bool bOverrideExisting = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands |")` — Registers a command within the given context and set. The set must be registered beforehand. @param	CommandInfo				The command infos such as name, label, description and input chord. @param	OnExecuteCommand 		The delegate to be executed for handling this command. @param	OnCanExecuteCommand 	The delegate to be executed for checking if this command can be executed. @param	bOverrideExisting		Whether existing command with matching context, set and name should be overriden @return Whether the command was successfully registered
- L251 _public prototype_ `bool UnregisterCommand(FScriptingCommandInfo CommandInfo);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands |")` — Unregisters a command previously registered. The command name, set and context will be used for comparison. @return Whether the command was successfully unregistered.
- L255 _public prototype_ `bool IsCommandRegistered(FScriptingCommandInfo CommandInfo, bool bCheckInputChord = true) const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands |")` — Checks whether the given command is registered within the subsystem. Using name, set and context for comparison
- L259 _public prototype_ `TArray<FScriptingCommandInfo> GetRegisteredCommands() const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Global")` — Retrieves the list of command info for all commands currently registered in the subsystem
- L263 _public prototype_ `bool CanExecuteCommands() const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Global")` — Checks whether commands registered in the subsystem can be executed
- L267 _public prototype_ `void SetCanExecuteCommands(bool bShouldExecuteCommands);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Global")` — Sets whether commands registered in the subsystem can be executed
- L274 _public prototype_ `void UnregisterAllSets();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Global")` — Unregisters all commands dynamically registered within all contexts and sets. @warning this will unregister all commands currently registered by this subsystem
- L282 _public prototype_ `bool RegisterCommandSet(FName SetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Sets")` — Registers a new command set @return Whether the set did not already exist and was successfully registered
- L286 _public prototype_ `bool IsCommandSetRegistered(FName SetName) const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Sets")` — Checks whether the given set is currently registered in the subsystem
- L293 _public prototype_ `bool UnregisterCommandSet(FName SetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Sets")` — Unregisters the corresponding command set with all commands registered within it @return Whether the command set existed and was successfully unregistered
- L297 _public prototype_ `void SetCanSetExecuteCommands(FName SetName, bool bShouldExecuteCommands);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Sets", Meta = (DisplayName = "Set Can Execute Commands"))` — Enables or disables execution of commands registered within the given set
- L301 _public prototype_ `bool CanSetExecuteCommands(const FName SetName) const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Sets", Meta = (DisplayName = "Can Execute Commands"))` — Checks whether commands in the given set can be executed. This will also check CanExecuteCommands at a global scope
- L309 _public prototype_ `TArray<FName> GetAvailableContexts() const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Contexts")` — Retrieves the list of names for all contexts currently registered in the subsystem. This does not check whether the contexts are bound to any UI Command List.
- L316 _public prototype_ `bool IsContextRegistered(FName ContextName) const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Contexts")` — Checks whether the context with the given name is currently registered in the subsystem This does not check whether the context is bound to any UI Command List.
- L323 _public prototype_ `int GetBindingCountForContext(FName ContextName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Contexts")` — Retrieves the number of UI Command Lists registered within this context through the subsystem. UI Command Lists are typically used to bind the list of commands associated with a single UI (i.e. a single viewport).
- L330 _public prototype_ `bool IsInputChordMapped(FName ContextName, FInputChord InputChord) const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Commands | Contexts")` — Checks whether the given input chord is already mapped to a command in the given context. This includes commands not registered through the subsystem.
- L334 _private prototype_ `bool RegisterNewScriptingCommand(FScriptingCommandInfo CommandInfo, FExecuteCommand OnExecuteCommand, FCanExecuteAction OnCanExecuteAction, bool bOverrideExisting = false);` — The internal method to dynamically registers an editor command
- L338 _private prototype_ `bool RegisterScriptingCommand(const TSharedRef<FScriptingCommand> ScriptingCommand);` — Registers a context command in its command lists. This assumes the command is already contained in a set
- L341 _private prototype_ `bool UnregisterScriptingCommand(const TSharedRef<FScriptingCommand> ScriptingCommand);` — Unregisters a context command from its command lists. This assumes the command is already contained in a set
- L345 _private prototype_ `static void HandleExecuteAction(FExecuteCommand OnExecuteAction, const FScriptingCommandInfo CommandInfo);` — `UFUNCTION()` — The delegate bound to registered commands. It will broadcast back to the given dynamic delegate
- L352 _private prototype_ `bool HandleCanExecuteAction(FCanExecuteCommand OnCanExecuteAction, const FScriptingCommandInfo CommandInfo) const;` — `UFUNCTION()` — The delegate used to check whether a command can be executed. @return true if the given delegate returns true and the given set and all subsystem commands are enabled
- L359 _private prototype_ `bool DefaultCanExecuteAction(FName SetName) const;` — `UFUNCTION()` — The default delegate to check if a command can be executed (when the user does not provide a specific delegate). @return true if the given set and all subsystem commands are enabled
- L363 _private member_ `TMap<FName, FScriptingCommandsContext> CommandsInContext;` — The list of commands contexts. Each context contains its own list of registered commands and UI command lists
- L366 _private member_ `TMap<FName, FScriptingCommandSet> CommandSets;` — The list of command sets. Each set contains its own list of registered commands
- L369 _private member_ `bool bCanExecuteCommands = true;` — Whether the commands for all the sets of the subsystem can be executed

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SLATESCRIPTINGCOMMANDS_API`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommandsScripting, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommandsScripting, Log, All);`
- L65 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FExecuteCommand, FScriptingCommandInfo, CommandInfo);` — Exposing FExecuteAction as dynamic
- L65 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FExecuteCommand, FScriptingCommandInfo, CommandInfo);` — Exposing FExecuteAction as dynamic
- L68 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FCanExecuteCommand, FScriptingCommandInfo, CommandInfo);` — Exposing FCanExecuteAction as dynamic
- L68 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FCanExecuteCommand, FScriptingCommandInfo, CommandInfo);` — Exposing FCanExecuteAction as dynamic
