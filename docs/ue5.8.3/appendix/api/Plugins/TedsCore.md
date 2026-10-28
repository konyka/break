# Plugins / TedsCore

- module root: `Plugins/Experimental/EditorDataStorage/Source/TedsCore`
- headers: 55; symbols: 1930
- symbol kinds: class=80, enum=8, enumerator=30, function=117, macro=24, member=417, namespace=160, prototype=954, struct=88, typedef=51, union=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, MassCore, MassEntity, MassEntityEditor, Slate, SlateCore, TypedElementFramework, UnrealEd

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Commands/EditorDataStorageCommandBuffer.h` (Private)


#### struct `UE::Editor::DataStorage::FNopCommand`  
`struct FNopCommand final`  
_L13-13_
- desc: Empty command that does nothing. Can be used as placeholder or to disable an existing command.

#### class `UE::Editor::DataStorage::FCommandBuffer`  
`template<typename... TCommand> class FCommandBuffer final`  
_L27-235_
- desc: Class to store, optimize and process commands. Only the list of provided command objects can be used or TNopCommand which will is automatically added. Commands take the form of a struct with any number, including zero, member variables. The typical use case of the command buffer is to repeatedly call `AddCommand`. This can be safely done from any thread. Periodically, e.g. once per frame, `Collect` is called which collects all commands from all threads into a single local collection. This stores references to the commands so doesn't move or copy the commands out of the scratch buffer where commands are created. Keep the lifetime of objects in the scratch buffer in mind. The returned collection can be further processed. This typically involves steps such as patching commands e.g. by resolving the table index, sort commands in order, optimize commands to remove/replace/add commands as needed and finally the commands are processed so they get executed. A utility class is also provided to help with optimizing the command buffer.
- L31 _public typedef_ `using TCommandVariant = TVariant<FNopCommand, TCommand...>;` — Note that FNopCommand is always inserted at index 0. This means that any code using sizeof...(TCommand) needs to add 1 to the count.
- L203 _public prototype_ `void Initialize(FScratchBuffer& InScratchBuffer);`
- L207 _public prototype_ `template<typename T> void AddCommand();` — Adds a command the command buffer in a thread-safe manner. T has to be one of the provided commands or TNopCommand.
- L211 _public prototype_ `template<typename T> void AddCommand(T&& Command);` — Adds a command the command buffer in a thread-safe manner. T has to be one of the provided commands or TNopCommand.
- L218 _public prototype_ `SIZE_T Collect(FCollection& Storage);` — Collects commands from all thread locally for further processing. This needs to be called every frame as commands are stored in a temporary buffer that will get cleared after the frame. Returns the number of collected commands.
- L231 _private member_ `FCommandInstance* CommandFront = nullptr;`
- L232 _private member_ `std::atomic<FCommandInstance*> CommandBack = nullptr;`
- L234 _private member_ `FScratchBuffer* ScratchBuffer = nullptr;`

#### class `UE::Editor::DataStorage::FCommandBuffer::FCollection`  
`class FCollection final`  
_L34-100_
- desc: Storage for commands collected from all threads that haven't been executed yet.
- L39 _public prototype_ `FCollection();`
- L43 _public prototype_ `template<typename T> void AddCommand();` — Adds a new command at the end of the command collection.
- L46 _public prototype_ `template<typename T> void AddCommand(T&& Command);` — Adds a new command at the end of the command collection.
- L53 _public prototype_ `template<typename T> void ReplaceCommand(int32 Index);` — Replaces the command at the given index. Prefer this over directly replacing the command variant to make sure tracking in the buffer remains consistent.
- L59 _public prototype_ `template<typename T> void ReplaceCommand(int32 Index, T&& Command);` — Replaces the command at the given index. Prefer this over directly replacing the command variant to make sure tracking in the buffer remains consistent.
- L63 _public prototype_ `template<typename T> void InsertCommandBefore(int32 Index);` — Inserts a new command before the provided index, moving the command at the given index one position up.
- L67 _public prototype_ `template<typename T> void InsertCommandBefore(int32 Index, T&& Command);` — Inserts a new command before the provided index, moving the command at the given index one position up.
- L73 _public prototype_ `void ForEach(TFunctionRef<void(int32 Index, TCommandVariant& Command)> Iterator);` — Iterates over all collected commands, allowing commands to be updated. Do not use this function to replace a command with new one as this will cause internal counters to mismatch.
- L77 _public prototype_ `template<bool bStableSort = true> void Sort(TFunctionRef<bool(const TCommandVariant& Lhs, const TCommandVariant& Rhs)> Comparer);` — Sorts commands using the provided compare function.
- L85 _public prototype_ `template<typename TProcessor> void Process(TProcessor&& Processor) const;` — Processes the local commands, that are retrieved after calling Collect or that still remain in the local queue. The provided can be any object that has functions that can receive a comment. As an example struct FProcessor{ void operator()(const TNopCommand&) {} };
- L88 _public prototype_ `void Reset();` — Resets the locally stored information, effectively clearing the command buffer until the next collect is called.
- L92 _public prototype_ `template<typename Command> uint32 GetCommandCount() const;` — Returns the number of instances of a command that are locally queued.
- L95 _public prototype_ `uint32 GetTotalCommandCount() const;` — Returns the total number of commands, excluding nop operations.
- L97 _private member_ `TArray<TCommandVariant*> CommandReferences;`
- L98 _private member_ `uint32 CommandCount[sizeof...(TCommand) + 1];`
- L99 _private member_ `FScratchBuffer* ScratchBuffer = nullptr;`

#### class `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`  
`class FOptimizer`  
_L103-201_
- desc: Utility class to help optimize a collection of commands.
- L106 _public typedef_ `using IsValidCallback = TFunction<bool(const TCommandVariant& Command)>;`
- L108 _public prototype_ `explicit FOptimizer(FCommandBuffer::FCollection& InCommands);`
- L110 _public prototype_ `TCommandVariant& GetLeft();`
- L111 _public prototype_ `TCommandVariant& GetRight();`
- L119 _public prototype_ `void MoveToNextLeft();` — Moves the left index one command to the right. If the right index is on the same command, right will also be moved one position to the right. Before: 0 | L1 | R2 | 3  | 4 After:  0 | 1  | L2 | R3 | 4
- L125 _public prototype_ `void MoveToNextRight();` — Move the right index one command to the right Before: 0 | L1 | R2 | 3  | 4 After:  0 | L1 | 2  | R3 | 4
- L131 _public prototype_ `void MoveToNextLeftAndRight();` — Moves both the left and right index one command to the right Before: 0 | L1 | 2  | R3 | 4 After:  0 | 1  | L2 | 3  | R4
- L137 _public prototype_ `void ResetRightNextToLeft();` — Resets the right index to be one next to the left index. Before: 0 | L1 | 2  | 3 | R4 After:  0 | L1 | R2 | 3 | 4
- L143 _public prototype_ `void MoveLeftBeforeRight();` — Moves the left index to one less than the right index. Before: L0 | 1 | 2  | R3 | 4 After:  0  | 1 | L2 | R3 | 4
- L149 _public prototype_ `void MoveLeftToRight();` — Moves the left index to the right index and moves the right index one to the right. Before: L0 | 1 | 2 | R3 | 4 After:  0  | 1 | 2 | L3 | R4
- L153 _public prototype_ `template<typename T> void ReplaceLeft(T&& Command);` — Replaces the command at the left index with a new command.
- L156 _public prototype_ `template<typename T> void ReplaceLeft();` — Replaces the command at the left index with a new command.
- L159 _public prototype_ `template<typename T> void ReplaceRight(T&& Command);` — Replaces the command at the right index with a new command.
- L162 _public prototype_ `template<typename T> void ReplaceRight();` — Replaces the command at the right index with a new command.
- L170 _public prototype_ `template<typename T> void InsertBeforeLeft(T&& Command);` — Inserts a new command before the command at the left index. Before: 10 | L20 | 30  | R40 | 50 After:  10 | 15  | L20 | 30  | R40 | 50
- L177 _public prototype_ `template<typename T> void InsertBeforeLeft();` — Inserts a new command before the command at the left index. Before: 10 | L20 | 30  | R40 | 50 After:  10 | 15  | L20 | 30  | R40 | 50
- L180 _public prototype_ `FOptimizer BranchOnLeft();` — Creates a new optimizer starting at the left of the current optimizer.
- L182 _public prototype_ `FOptimizer BranchOnLeft(IsValidCallback Callback);` — Creates a new optimizer starting at the left of the current optimizer. The provides callback is used to check range.
- L184 _public prototype_ `FOptimizer BranchOnRight();` — Creates a new optimizer starting at the right of the current optimizer.
- L186 _public prototype_ `FOptimizer BranchOnRight(IsValidCallback Callback);` — Creates a new optimizer starting at the right of the current optimizer. The provides callback is used to check range.
- L188 _public prototype_ `bool IsValid() const;`
- L191 _private prototype_ `FOptimizer(FCommandBuffer::FCollection& InCommands, int32 InLeft);`
- L192 _private prototype_ `FOptimizer(FCommandBuffer::FCollection& InCommands, int32 InLeft, IsValidCallback InCallback);`
- L194 _private prototype_ `int32 MoveToNextNonNop(int32 Location);`
- L195 _private prototype_ `int32 MoveToPreviousNonNop(int32 Location);`
- L197 _private member_ `IsValidCallback IsValidCheck;`
- L198 _private member_ `int32 Left;`
- L199 _private member_ `int32 Right;`
- L200 _private member_ `FCommandBuffer::FCollection& Commands;`

#### struct `UE::Editor::DataStorage::FCommandBuffer::FCommandInstance`  
`struct FCommandInstance final`  
_L222-230_
- desc: Wrapper object used to store a command in the scratch buffer.
- L224 _public prototype_ `FCommandInstance() = default;`
- L226 _public prototype_ `template <typename U, typename... TArgs> explicit FCommandInstance(TInPlaceType<U>&&, TArgs&&... Args);`
- L228 _public member_ `TCommandVariant Command;`
- L229 _public member_ `std::atomic<FCommandInstance*> Next = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Commands/EditorDataStorageCommandBuffer.inl` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _function_ `template<typename... TCommand> FCommandBuffer<TCommand...>::FCollection::FCollection()` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L20 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FCollection::AddCommand()` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L28 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FCollection::AddCommand(T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L36 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FCollection::ReplaceCommand(int32 Index)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L49 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FCollection::ReplaceCommand(int32 Index, T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L62 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FCollection::InsertCommandBefore(int32 Index)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L71 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FCollection::InsertCommandBefore(int32 Index, T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L79 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FCollection::ForEach(TFunctionRef<void(int32 Index, TCommandVariant& Command)> Iterator)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L90 _function_ `template<typename... TCommand> template<bool bStableSort> void FCommandBuffer<TCommand...>::FCollection::Sort(TFunctionRef<bool(const TCommandVariant&, const TCommandVariant&)> Comparer)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L104 _function_ `template<typename... TCommand> template<typename TProcessor> void FCommandBuffer<TCommand...>::FCollection::Process(TProcessor&& Processor) const` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L113 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FCollection::Reset()` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L121 _function_ `template<typename... TCommand> template<typename Command> uint32 FCommandBuffer<TCommand...>::FCollection::GetCommandCount() const` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L127 _function_ `template<typename... TCommand> uint32 FCommandBuffer<TCommand...>::FCollection::GetTotalCommandCount() const` (scope `UE::Editor::DataStorage::FCommandBuffer::FCollection`)
- L143 _function_ `template<typename... TCommand> FCommandBuffer<TCommand...>::FOptimizer::FOptimizer(FCommandBuffer::FCollection& InCommands) : Left(0) , Right(1) , Commands(InCommands)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L160 _function_ `template<typename... TCommand> FCommandBuffer<TCommand...>::FOptimizer::FOptimizer(FCommandBuffer::FCollection& InCommands, int32 InLeft) : Left(InLeft) , Right(InLeft + 1) , Commands(InCommands)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L177 _function_ `template<typename... TCommand> FCommandBuffer<TCommand...>::FOptimizer::FOptimizer(FCommandBuffer::FCollection& InCommands, int32 InLeft, IsValidCallback InCallback) : IsValidCheck(MoveTemp(InCallback)) , Left(InLeft) , Right(InLeft + 1) , Commands(InCommands)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L195 _function_ `template<typename... TCommand> typename FCommandBuffer<TCommand...>::TCommandVariant& FCommandBuffer<TCommand...>::FOptimizer::GetLeft()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L202 _function_ `template<typename... TCommand> typename FCommandBuffer<TCommand...>::TCommandVariant& FCommandBuffer<TCommand...>::FOptimizer::GetRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L209 _function_ `template<typename... TCommand> int32 FCommandBuffer<TCommand...>::FOptimizer::MoveToNextNonNop(int32 Location)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L220 _function_ `template<typename... TCommand> int32 FCommandBuffer<TCommand...>::FOptimizer::MoveToPreviousNonNop(int32 Location)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L234 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FOptimizer::MoveToNextLeft()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L244 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FOptimizer::MoveToNextRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L250 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FOptimizer::MoveToNextLeftAndRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L261 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FOptimizer::ResetRightNextToLeft()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L268 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FOptimizer::MoveLeftBeforeRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L274 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::FOptimizer::MoveLeftToRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L281 _function_ `template<typename... TCommand> bool FCommandBuffer<TCommand...>::FOptimizer::IsValid() const` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L295 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FOptimizer::ReplaceLeft(T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L302 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FOptimizer::ReplaceLeft()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L309 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FOptimizer::ReplaceRight(T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L316 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FOptimizer::ReplaceRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L323 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FOptimizer::InsertBeforeLeft(T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L332 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::FOptimizer::InsertBeforeLeft()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L340 _function_ `template<typename... TCommand> typename FCommandBuffer<TCommand...>::FOptimizer FCommandBuffer<TCommand...>::FOptimizer::BranchOnLeft()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L346 _function_ `template<typename... TCommand> typename FCommandBuffer<TCommand...>::FOptimizer FCommandBuffer<TCommand...>::FOptimizer::BranchOnLeft(IsValidCallback Callback)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L352 _function_ `template<typename... TCommand> typename FCommandBuffer<TCommand...>::FOptimizer FCommandBuffer<TCommand...>::FOptimizer::BranchOnRight()` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L358 _function_ `template<typename... TCommand> typename FCommandBuffer<TCommand...>::FOptimizer FCommandBuffer<TCommand...>::FOptimizer::BranchOnRight(IsValidCallback Callback)` (scope `UE::Editor::DataStorage::FCommandBuffer::FOptimizer`)
- L372 _function_ `template<typename... TCommand> template <typename U, typename... TArgs> FCommandBuffer<TCommand...>::FCommandInstance::FCommandInstance(TInPlaceType<U>&&, TArgs&&... Args) : Command(TInPlaceType<U>(), Forward<TArgs>(Args)...)` (scope `UE::Editor::DataStorage::FCommandBuffer::FCommandInstance`)
- L384 _function_ `template<typename... TCommand> void FCommandBuffer<TCommand...>::Initialize(FScratchBuffer& InScratchBuffer)` (scope `UE::Editor::DataStorage::FCommandBuffer`)
- L393 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::AddCommand()` (scope `UE::Editor::DataStorage::FCommandBuffer`)
- L405 _function_ `template<typename... TCommand> template<typename T> void FCommandBuffer<TCommand...>::AddCommand(T&& Command)` (scope `UE::Editor::DataStorage::FCommandBuffer`)
- L416 _function_ `template<typename... TCommand> SIZE_T FCommandBuffer<TCommand...>::Collect(FCollection& Storage)` (scope `UE::Editor::DataStorage::FCommandBuffer`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Commands/EditorDataStorageCompatibilityCommands.h` (Private)


#### enum `UE::Editor::DataStorage::EObjectType`  
`enum class EObjectType : uint8`  
_L22-26_
- L24 _public enumerator_ `Struct`
- L25 _public enumerator_ `Class`

#### struct `UE::Editor::DataStorage::FObjectTypeInfo`  
`struct FObjectTypeInfo`  
_L33-47_
- desc: Objects with type info defined in either UScriptStruct or UClass can be stored into TEDS via the ICompatibilityProvider This is a discriminated union which aids with callbacks made when objects are added
- L35 _public member_ `EObjectType TypeInfoType;`
- L43 _public prototype_ `FObjectTypeInfo(const UScriptStruct* InScriptStruct);`
- L44 _public prototype_ `FObjectTypeInfo(const UClass* InClass);`
- L46 _public prototype_ `FName GetFName() const;`

#### union `UE::Editor::DataStorage::FObjectTypeInfo::(anonymous)`  
``  
_L38-41_

#### struct `UE::Editor::DataStorage::FTypeInfoReinstanced`  
`struct FTypeInfoReinstanced final`  
_L51-55_
- L53 _public member_ `TWeakObjectPtr<UStruct> Original;`
- L54 _public member_ `TWeakObjectPtr<UStruct> Reinstanced;`

#### struct `UE::Editor::DataStorage::FTypeBatchInfoReinstanced`  
`struct FTypeBatchInfoReinstanced final`  
_L57-65_
- L59 _public member_ `TArrayView<FTypeInfoReinstanced> Batch;`
- L62 _public prototype_ `template<typename T> static FTypeInfoReinstanced* FindObject(TArrayView<FTypeInfoReinstanced> Range, const TWeakObjectPtr<T>& Object);`
- L64 _public prototype_ `template<typename T> static TWeakObjectPtr<T> FindObjectRecursively(TArrayView<FTypeInfoReinstanced> Range, const TWeakObjectPtr<T>& Object);`

#### struct `UE::Editor::DataStorage::FRegisterTypeTableAssociation`  
`struct FRegisterTypeTableAssociation final`  
_L67-71_
- L69 _public member_ `TWeakObjectPtr<UStruct> TypeInfo;`
- L70 _public member_ `TableHandle Table;`

#### struct `UE::Editor::DataStorage::FAddCompatibleUObject`  
`struct FAddCompatibleUObject final`  
_L73-78_
- L75 _public member_ `TWeakObjectPtr<UObject> Object;`
- L76 _public member_ `RowHandle Row;`
- L77 _public member_ `TableHandle Table;`

#### struct `UE::Editor::DataStorage::FRegisterObjectAddedCallback`  
`struct FRegisterObjectAddedCallback final`  
_L84-88_
- L86 _public member_ `ObjectAddedCallback Callback;`
- L87 _public member_ `FDelegateHandle Handle;`

#### struct `UE::Editor::DataStorage::FUnregisterObjectAddedCallback`  
`struct FUnregisterObjectAddedCallback final`  
_L90-93_
- L92 _public member_ `FDelegateHandle Handle;`

#### struct `UE::Editor::DataStorage::FBatchAddCompatibleUObject`  
`struct FBatchAddCompatibleUObject final`  
_L100-106_
- L102 _public member_ `TWeakObjectPtr<UObject>* ObjectArray;`
- L103 _public member_ `RowHandle* RowArray;`
- L104 _public member_ `TableHandle Table;`
- L105 _public member_ `uint32 Count;`

#### struct `UE::Editor::DataStorage::FAddCompatibleExternalObject`  
`struct FAddCompatibleExternalObject final`  
_L108-114_
- L110 _public member_ `void* Object;`
- L111 _public member_ `TWeakObjectPtr<const UScriptStruct> TypeInfo;`
- L112 _public member_ `RowHandle Row;`
- L113 _public member_ `TableHandle Table;`

#### struct `UE::Editor::DataStorage::FCreateMemento`  
`struct FCreateMemento final`  
_L116-120_
- L118 _public member_ `RowHandle ReservedMementoRow;`
- L119 _public member_ `RowHandle TargetRow;`

#### struct `UE::Editor::DataStorage::FRestoreMemento`  
`struct FRestoreMemento final`  
_L122-126_
- L124 _public member_ `RowHandle MementoRow;`
- L125 _public member_ `RowHandle TargetRow;`

#### struct `UE::Editor::DataStorage::FDestroyMemento`  
`struct FDestroyMemento final`  
_L128-131_
- L130 _public member_ `RowHandle MementoRow;`

#### struct `UE::Editor::DataStorage::FRemoveCompatibleUObject`  
`struct FRemoveCompatibleUObject final`  
_L133-137_
- L135 _public member_ `const UObject* Object;`
- L136 _public member_ `RowHandle ObjectRow = InvalidRowHandle;`

#### struct `UE::Editor::DataStorage::FRemoveCompatibleExternalObject`  
`struct FRemoveCompatibleExternalObject final`  
_L139-143_
- L141 _public member_ `void* Object;`
- L142 _public member_ `RowHandle ObjectRow;`

#### struct `UE::Editor::DataStorage::FBatchAddCompatibleExternalObject`  
`struct FBatchAddCompatibleExternalObject final`  
_L145-152_
- L147 _public member_ `void** ObjectArray;`
- L148 _public member_ `TWeakObjectPtr<const UScriptStruct>* TypeInfoArray;`
- L149 _public member_ `RowHandle* RowArray;`
- L150 _public member_ `TableHandle Table;`
- L151 _public member_ `uint32 Count;`

#### struct `UE::Editor::DataStorage::FAddSyncFromWorldTag`  
`struct FAddSyncFromWorldTag final`  
_L154-161_
- L156 _public member_ `TObjectKey<const UObject> Target;`
- L157 _public member_ `RowHandle Row;`
- L159 _public prototype_ `static const UScriptStruct* GetType();`
- L160 _public prototype_ `static const UScriptStruct** GetTypeAddress();`

#### struct `UE::Editor::DataStorage::FAddInteractiveSyncFromWorldTag`  
`struct FAddInteractiveSyncFromWorldTag final`  
_L163-170_
- L165 _public member_ `TObjectKey<const UObject> Target;`
- L166 _public member_ `RowHandle Row;`
- L168 _public prototype_ `static const UScriptStruct* GetType();`
- L169 _public prototype_ `static const UScriptStruct** GetTypeAddress();`

#### struct `UE::Editor::DataStorage::FRemoveInteractiveSyncFromWorldTag`  
`struct FRemoveInteractiveSyncFromWorldTag final`  
_L172-176_
- L174 _public member_ `TObjectKey<const UObject> Target;`
- L175 _public member_ `RowHandle Row;`

#### struct `UE::Editor::DataStorage::FPatchData`  
`struct FPatchData final`  
_L207-226_
- desc: Patches data in preparation for processing. This can include fixing tables like the type-to-table map if type information has changed.
- L223 _public prototype_ `static bool IsPatchingRequired(const CompatibilityCommandBuffer::FCollection& Commands);`
- L224 _public prototype_ `static void RunPatch(CompatibilityCommandBuffer::FCollection& Commands, UEditorDataStorageCompatibility& StorageCompat, FScratchBuffer& ScratchBuffer);`

#### struct `UE::Editor::DataStorage::FPatchData::FPatchCommand`  
`struct FPatchCommand final`  
_L209-221_
- L211 _public prototype_ `explicit FPatchCommand(TArrayView<FTypeInfoReinstanced>& InReinstances);`
- L214 _public function_ `template<typename T> void operator()(T&)`
- L216 _public prototype_ `void operator()(FRegisterTypeTableAssociation& Command);`
- L217 _public prototype_ `void operator()(FAddCompatibleExternalObject& Command);`
- L218 _public prototype_ `void operator()(FBatchAddCompatibleExternalObject& Command);`
- L220 _public member_ `TArrayView<FTypeInfoReinstanced>& Reinstances;`

#### struct `UE::Editor::DataStorage::FPrepareCommands`  
`struct FPrepareCommands final`  
_L229-251_
- desc: Prepares each command for further processing, e.g. resolving the target table.
- L231 _public prototype_ `FPrepareCommands(ICoreProvider& InStorage, UEditorDataStorageCompatibility& InStorageCompat, CompatibilityCommandBuffer::FCollection& InCommands);`
- L235 _public function_ `template<typename T> void operator()(T&)`
- L236 _public prototype_ `void operator()(FAddCompatibleUObject& Object);`
- L237 _public prototype_ `void operator()(FAddCompatibleExternalObject& Object);`
- L238 _public prototype_ `void operator()(FRemoveCompatibleUObject& Command);`
- L239 _public prototype_ `void operator()(FRemoveCompatibleExternalObject& Command);`
- L240 _public prototype_ `void operator()(FAddInteractiveSyncFromWorldTag& Command);`
- L241 _public prototype_ `void operator()(FRemoveInteractiveSyncFromWorldTag& Command);`
- L242 _public prototype_ `void operator()(FAddSyncFromWorldTag& Command);`
- L244 _public member_ `ICoreProvider& Storage;`
- L245 _public member_ `UEditorDataStorageCompatibility& StorageCompat;`
- L246 _public member_ `CompatibilityCommandBuffer::FCollection& Commands;`
- L247 _public member_ `int32 CurrentIndex = 0;`
- L249 _public prototype_ `static void RunPreparation(ICoreProvider& Storage, UEditorDataStorageCompatibility& StorageCompat, CompatibilityCommandBuffer::FCollection& Commands);`

#### struct `UE::Editor::DataStorage::FGetSourceRowHandle`  
`struct FGetSourceRowHandle`  
_L254-269_
- desc: Retrieve the source row handle from a command.
- L257 _public function_ `template<typename T> RowHandle operator()(const T&)`
- L258 _public prototype_ `RowHandle operator()(const FAddCompatibleUObject& Command);`
- L259 _public prototype_ `RowHandle operator()(const FAddCompatibleExternalObject& Command);`
- L260 _public prototype_ `RowHandle operator()(const FCreateMemento& Command);`
- L261 _public prototype_ `RowHandle operator()(const FRestoreMemento& Command);`
- L262 _public prototype_ `RowHandle operator()(const FDestroyMemento& Command);`
- L263 _public prototype_ `RowHandle operator()(const FRemoveCompatibleUObject& Command);`
- L264 _public prototype_ `RowHandle operator()(const FRemoveCompatibleExternalObject& Command);`
- L265 _public prototype_ `RowHandle operator()(const FAddInteractiveSyncFromWorldTag& Command);`
- L266 _public prototype_ `RowHandle operator()(const FRemoveInteractiveSyncFromWorldTag& Command);`
- L267 _public prototype_ `RowHandle operator()(const FAddSyncFromWorldTag& Command);`
- L268 _public prototype_ `static RowHandle Get(const CompatibilityCommandBuffer::TCommandVariant& Command);`

#### struct `UE::Editor::DataStorage::FGetCommandGroupId`  
`struct FGetCommandGroupId`  
_L275-292_
- desc: Group id for a command. Commands within the same group are not reordered for commands on the same row. The default order follows the order in which the commands are declared in the command buffer.
- L278 _public function_ `template<typename T> SIZE_T operator()(const T&)`
- L281 _public prototype_ `SIZE_T operator()(const FBatchAddCompatibleUObject& Command);` — FAddCompatibleUObject group
- L282 _public prototype_ `SIZE_T operator()(const FAddCompatibleExternalObject& Command);`
- L283 _public prototype_ `SIZE_T operator()(const FBatchAddCompatibleExternalObject& Command);`
- L284 _public prototype_ `SIZE_T operator()(const FCreateMemento& Command);`
- L285 _public prototype_ `SIZE_T operator()(const FRestoreMemento& Command);`
- L286 _public prototype_ `SIZE_T operator()(const FDestroyMemento& Command);`
- L287 _public prototype_ `SIZE_T operator()(const FRemoveCompatibleUObject& Command);`
- L288 _public prototype_ `SIZE_T operator()(const FRemoveCompatibleExternalObject& Command);`
- L290 _public prototype_ `SIZE_T operator()(const FRemoveInteractiveSyncFromWorldTag& Command);` — FAddInteractiveSyncFromWorldTag group
- L291 _public prototype_ `static SIZE_T Get(const CompatibilityCommandBuffer::TCommandVariant& Command);`

#### struct `UE::Editor::DataStorage::FSorter`  
`struct FSorter final`  
_L294-297_
- L296 _public prototype_ `static void SortCommands(CompatibilityCommandBuffer::FCollection& Commands);`

#### struct `UE::Editor::DataStorage::FCommandProcessor`  
`struct FCommandProcessor final`  
_L300-331_
- desc: Executes the commands in the command buffer for TEDS Compatibility.
- L302 _public prototype_ `FCommandProcessor(ICoreProvider& InStorage, UEditorDataStorageCompatibility& InStorageCompatibility);`
- L304 _public prototype_ `static void SetupRow(ICoreProvider& Storage, UEditorDataStorageCompatibility& StorageCompatibility, RowHandle Row, UObject* Object);`
- L306 _public prototype_ `static void SetupRow(ICoreProvider& Storage, UEditorDataStorageCompatibility& StorageCompatibility, RowHandle Row, void* Object, TWeakObjectPtr<const UScriptStruct> TypeInfo);`
- L309 _public function_ `void operator()(FNopCommand&)`
- L310 _public function_ `void operator()(FTypeInfoReinstanced&)`
- L311 _public prototype_ `void operator()(FTypeBatchInfoReinstanced& Command);`
- L312 _public prototype_ `void operator()(FRegisterTypeTableAssociation& Command);`
- L313 _public prototype_ `void operator()(FRegisterObjectAddedCallback& Command);`
- L314 _public prototype_ `void operator()(FUnregisterObjectAddedCallback& Command);`
- L315 _public prototype_ `void operator()(FAddCompatibleUObject& Object);`
- L316 _public prototype_ `void operator()(FBatchAddCompatibleUObject& Batch);`
- L317 _public prototype_ `void operator()(FAddCompatibleExternalObject& Object);`
- L318 _public prototype_ `void operator()(FBatchAddCompatibleExternalObject& Object);`
- L319 _public prototype_ `void operator()(FCreateMemento& Command);`
- L320 _public prototype_ `void operator()(FRestoreMemento& Command);`
- L321 _public prototype_ `void operator()(FDestroyMemento& Command);`
- L322 _public prototype_ `void operator()(FRemoveCompatibleUObject& Command);`
- L323 _public prototype_ `void operator()(FRemoveCompatibleExternalObject& Command);`
- L324 _public prototype_ `void operator()(FAddInteractiveSyncFromWorldTag& Command);`
- L325 _public prototype_ `void operator()(FRemoveInteractiveSyncFromWorldTag& Command);`
- L326 _public prototype_ `void operator()(FAddSyncFromWorldTag& Command);`
- L328 _public member_ `ICoreProvider& Storage;`
- L329 _public member_ `UEditorDataStorageCompatibility& StorageCompatibility;`
- L330 _public member_ `FMementoSystem& MementoSystem;`

#### struct `UE::Editor::DataStorage::FRecordCommands`  
`struct FRecordCommands final`  
_L333-358_
- L335 _public prototype_ `void operator()(const FNopCommand& Command);`
- L336 _public prototype_ `void operator()(const FTypeInfoReinstanced& Command);`
- L337 _public prototype_ `void operator()(const FTypeBatchInfoReinstanced& Command);`
- L338 _public prototype_ `void operator()(const FRegisterTypeTableAssociation& Command);`
- L339 _public prototype_ `void operator()(const FRegisterObjectAddedCallback& Command);`
- L340 _public prototype_ `void operator()(const FUnregisterObjectAddedCallback& Command);`
- L341 _public prototype_ `void operator()(const FAddCompatibleUObject& Command);`
- L342 _public prototype_ `void operator()(const FBatchAddCompatibleUObject& Command);`
- L343 _public prototype_ `void operator()(const FAddCompatibleExternalObject& Command);`
- L344 _public prototype_ `void operator()(const FBatchAddCompatibleExternalObject& Command);`
- L345 _public prototype_ `void operator()(const FCreateMemento& Command);`
- L346 _public prototype_ `void operator()(const FRestoreMemento& Command);`
- L347 _public prototype_ `void operator()(const FDestroyMemento& Command);`
- L348 _public prototype_ `void operator()(const FRemoveCompatibleUObject& Command);`
- L349 _public prototype_ `void operator()(const FRemoveCompatibleExternalObject& Command);`
- L350 _public prototype_ `void operator()(const FAddInteractiveSyncFromWorldTag& Command);`
- L351 _public prototype_ `void operator()(const FRemoveInteractiveSyncFromWorldTag& Command);`
- L352 _public prototype_ `void operator()(const FAddSyncFromWorldTag& Command);`
- L354 _public member_ `FString CommandDescriptions;`
- L355 _public member_ `bool bIncludeNops = false;`
- L357 _public prototype_ `static FString PrintToString(CompatibilityCommandBuffer::FCollection& Commands, bool bIncludeNops);`

#### struct `UE::Editor::DataStorage::FCommandOptimizer`  
`struct FCommandOptimizer final`  
_L361-391_
- desc: Looks at the current command and applies the next optimization.
- L365 _public prototype_ `FCommandOptimizer(CompatibilityCommandBuffer::FOptimizer& InOptimizer, FScratchBuffer& InScratchBuffer);` — TODO: Allow [add object + restore memento] to be folded into one and [create memento + remove object]. Not sure how that will fit into the batch add though.
- L368 _public function_ `template<typename T> void operator()(const T&)`
- L369 _public prototype_ `void operator()(const FAddCompatibleUObject& Command);`
- L370 _public prototype_ `void operator()(const FAddCompatibleExternalObject& Command);`
- L371 _public prototype_ `void operator()(const FRemoveCompatibleUObject& Command);`
- L372 _public prototype_ `void operator()(const FRemoveCompatibleExternalObject& Command);`
- L373 _public prototype_ `void operator()(const FAddInteractiveSyncFromWorldTag& Command);`
- L374 _public prototype_ `void operator()(const FRemoveInteractiveSyncFromWorldTag& Command);`
- L375 _public prototype_ `void operator()(const FAddSyncFromWorldTag& Command);`
- L377 _public member_ `CompatibilityCommandBuffer::FOptimizer& Optimizer;`
- L378 _public member_ `FScratchBuffer& ScratchBuffer;`
- L381 _public prototype_ `template<typename AddCommandType> int32 FoldCommandsForAdd(const AddCommandType& Command);`
- L382 _public prototype_ `void FoldSyncFromWorldTags(CompatibilityCommandBuffer::FOptimizer& Cluster);`
- L387 _public prototype_ `CompatibilityCommandBuffer::FOptimizer CreateRangeOptimizer(RowHandle RowCluster);` — Creates a new optimizer starting at the left of the current optimizer that will run only as long as commands on the right use the same row as the provided argument.
- L389 _public prototype_ `void RunRightOnRowCluster(RowHandle RowCluster);` — Keeps processing a subset of commands until the right no longer has a command with the provided source row.
- L390 _public prototype_ `static void Run(CompatibilityCommandBuffer::FCollection& Commands, FScratchBuffer& ScratchBuffer);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L39 _member_ `const UScriptStruct* ScriptStruct;` (scope `UE::Editor::DataStorage::FObjectTypeInfo::__anon32ef6134010a`)
- L40 _member_ `const UClass* Class;` (scope `UE::Editor::DataStorage::FObjectTypeInfo::__anon32ef6134010a`)
- L80 _typedef_ `using ObjectAddedCallback = TFunction<void( const void* , const FObjectTypeInfo&, RowHandle )>;` (scope `UE::Editor::DataStorage`)
- L95 _typedef_ `using ObjectRemovedCallback = TFunction<void( const void* , const FObjectTypeInfo&, RowHandle )>;` (scope `UE::Editor::DataStorage`)
- L178 _typedef_ `using CompatibilityCommandBuffer = FCommandBuffer < FTypeInfoReinstanced, FTypeBatchInfoReinstanced, FRegisterTypeTableAssociation, FRegisterObjectAddedCallback, FUnregisterObjectAddedCallback, FAddCompatibleUObject, FBatchAddCompatibleUObject, FAddCompatibleExternalObject, FBatchAddCompatibleExternalObject, FCreateMemento, FRestoreMemento, FDestroyMemento, FRemoveCompatibleUObject, FRemoveCompatibleExternalObject, FAddInteractiveSyncFromWorldTag, FRemoveInteractiveSyncFromWorldTag, FAddSyncFromWorldTag >;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Compatibility/TypedElementObjectReinstancingManager.h` (Private)


#### class `UTedsObjectReinstancingManager`  
`class UTedsObjectReinstancingManager : public UObject`  
_L23-53_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L27 _public prototype_ `UTedsObjectReinstancingManager();`
- L29 _public prototype_ `void Initialize(UEditorDataStorage& InDataStorage, UEditorDataStorageCompatibility& InDataStorageCompatibility);`
- L30 _public prototype_ `void Deinitialize();`
- L33 _private prototype_ `void UpdateCompleted();`
- L34 _private prototype_ `void HandleOnObjectPreRemoved( const void* Object, const UE::Editor::DataStorage::FObjectTypeInfo& TypeInfo, UE::Editor::DataStorage::RowHandle ObjectRow);`
- L38 _private prototype_ `void HandleOnObjectsReinstanced(const FCoreUObjectDelegates::FReplacementObjectMap& ObjectReplacementMap);`
- L41 _private member_ `TObjectPtr<UEditorDataStorage> DataStorage = nullptr;` — `UPROPERTY()`
- L43 _private member_ `TObjectPtr<UEditorDataStorageCompatibility> DataStorageCompatibility = nullptr;` — `UPROPERTY()`
- L47 _private member_ `TMap<const void*, UE::Editor::DataStorage::RowHandle> OldObjectToMementoMap;` — Reverse lookup that holds all populated mementos for recently deleted objects Entry removed when the memento is removed
- L49 _private member_ `UE::Editor::DataStorage::TableHandle MementoRowBaseTable;`
- L50 _private member_ `FDelegateHandle UpdateCompletedCallbackHandle;`
- L51 _private member_ `FDelegateHandle ReinstancingCallbackHandle;`
- L52 _private member_ `FDelegateHandle ObjectRemovedCallbackHandle;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Compatibility/TypedElementUObjectNameQueries.h` (Private)


#### class `UObjectNameDataStorageFactory`  
`class UObjectNameDataStorageFactory : public UEditorDataStorageFactory`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UObjectNameDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _private prototype_ `void RegisterUObjectAddNameColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the Name columns to new actors that do not have one already.

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Compatibility/TypedElementUObjectWorldQueries.h` (Private)


#### class `UObjectWorldDataStorageFactory`  
`class UObjectWorldDataStorageFactory : public UEditorDataStorageFactory`  
_L11-33_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UObjectWorldDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _private prototype_ `void RegisterAddWorldColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Checks rows with UObjects that don't have a world column yet if one needs to be added whenever the row is marked for updates.
- L30 _private prototype_ `void RegisterUpdateOrRemoveWorldColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Updates the world column with the world in the UObject or removes it if there's no world associated with the UObject anymore.
- L32 _private prototype_ `void RegisterPIEWorldSyncQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Debug/TypedElementDatabaseDebugTypes.h` (Private)


#### enum `ETedsDebugEnum`  
`enum class ETedsDebugEnum : int8`  
_L13-23_
- reflection: `UENUM()`
- L15 _public enumerator_ `Red`
- L16 _public enumerator_ `Blue`
- L17 _public enumerator_ `Green`
- L18 _public enumerator_ `Yellow`
- L19 _public enumerator_ `Black`
- L20 _public enumerator_ `Pink`
- L21 _public enumerator_ `Orange`
- L22 _public enumerator_ `Purple`

#### struct `FTestDynamicColumn`  
`struct FTestDynamicColumn : public FEditorDataStorageColumn`  
_L26-33_
- reflection: `USTRUCT(meta=(EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageColumn`
- L32 _public member_ `TArray<int32> IntArray;` — Note: Not trivial type to check that non-default move/copying works Should work regardless of UPROPERTY

#### struct `FTestDynamicTag`  
`struct FTestDynamicTag : public FEditorDataStorageTag`  
_L36-39_
- reflection: `USTRUCT(meta=(EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/DynamicColumnGenerator.h` (Private)


#### struct `FTedsValueTagColumn`  
`struct FTedsValueTagColumn : public FTedsSharedColumn`  
_L20-26_
- reflection: `USTRUCT(meta=(EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FTedsSharedColumn`
- desc: The template struct that is used to generate the ValueTag column
- L25 _public member_ `FName Value;` — `UPROPERTY()`

#### struct `UE::Editor::DataStorage::FDynamicColumnInfo`  
`struct FDynamicColumnInfo`  
_L33-36_
- L35 _public member_ `const UScriptStruct* Type;`

#### struct `UE::Editor::DataStorage::FDynamicColumnGeneratorInfo`  
`struct FDynamicColumnGeneratorInfo`  
_L38-43_
- L40 _public member_ `const UScriptStruct* Type;`
- L41 _public member_ `const UScriptStruct* Template;`
- L42 _public member_ `bool bNewlyGenerated;`

#### class `UE::Editor::DataStorage::FDynamicColumnGenerator`  
`class FDynamicColumnGenerator`  
_L48-109_
- desc: Utility class that TEDS can use to dynamically generate column types on the fly
- L51 _public prototype_ `void SetQueryStore(FExtendedQueryStore& InQueryStore);`
- L56 _public prototype_ `FDynamicColumnGeneratorInfo GenerateColumn(const UScriptStruct& Template, const FName& Identifier);` — Generates a dynamic TEDS column type based on a Template type (if it hasn't been generated before)
- L58 _public prototype_ `void ForEachDynamicColumn(const UScriptStruct& Template, TFunctionRef<void(const FDynamicColumnGeneratorInfo&)> Callback) const;`
- L60 _public prototype_ `bool IsDynamicTemplate(const UScriptStruct& InCandidate) const;`
- L61 _public prototype_ `const UScriptStruct* FindByTemplateId(const UScriptStruct& Template, const FName& Identifier) const;`
- L64 _public prototype_ `bool FindByGeneratedType(const UScriptStruct& GeneratedType, FDynamicColumnGeneratorInfo& Out) const;` — Returns true if found, false otherwise. If found, Out will be populated
- L79 _private function_ `friend bool operator==(const FTemplateIdKey& Lhs, const FTemplateIdKey& Rhs)`
- L84 _private function_ `friend bool operator!=(const FTemplateIdKey& Lhs, const FTemplateIdKey& Rhs)`
- L89 _private function_ `friend uint32 GetTypeHash(const FTemplateIdKey& Key)`
- L95 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(AccessDetector);`
- L97 _private member_ `TArray<FGeneratedColumnRecord> GeneratedColumnData;`
- L99 _private member_ `TSet<const UScriptStruct*> TemplateTypeLookup;`
- L103 _private member_ `TMap<FTemplateIdKey, int32> TemplateIdLookup;` — Looks up generated column index by template and ID used to generate it Used to de-duplicate
- L106 _private member_ `TMap<const UScriptStruct*, int32> GeneratedTypeLookup;` — Looks up generated column data by the generated column type
- L108 _private member_ `FExtendedQueryStore* QueryStore = nullptr;`

#### struct `UE::Editor::DataStorage::FDynamicColumnGenerator::FGeneratedColumnRecord`  
`struct FGeneratedColumnRecord`  
_L67-72_
- L69 _public member_ `FName Identifier;`
- L70 _public member_ `const UScriptStruct* Template;`
- L71 _public member_ `const UScriptStruct* Type;`

#### struct `UE::Editor::DataStorage::FDynamicColumnGenerator::FTemplateIdKey`  
`struct FTemplateIdKey`  
_L74-93_
- L76 _public member_ `const UScriptStruct& Template;`
- L77 _public member_ `FName Identifier;`

#### class `UE::Editor::DataStorage::FValueTagManager`  
`class FValueTagManager`  
_L111-123_
- L114 _public prototype_ `explicit FValueTagManager(FMassEntityManager& InEntityManager, FDynamicColumnGenerator& InColumnGenerator);`
- L115 _public prototype_ `FConstSharedStruct GenerateValueTag(const FValueTag& InTag, const FName& InValue);`
- L116 _public prototype_ `const UScriptStruct* GenerateColumnType(const FValueTag& InTag);`
- L119 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(AccessDetector);`
- L121 _private member_ `FMassEntityManager& EntityManager;`
- L122 _private member_ `FDynamicColumnGenerator& ColumnGenerator;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Editor` (scope `UE`)
- L28 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L31 _typedef_ `using FValueTagColumn = FTedsValueTagColumn;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/EditorDataStorageSettings.h` (Private)


#### enum `EChunkMemorySize`  
`enum class EChunkMemorySize : int32`  
_L10-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `Size4Kb = 4 * 1024 UMETA(DisplayName = "4kb")`
- L13 _public enumerator_ `Size8Kb = 8 * 1024 UMETA(DisplayName = "8kb")`
- L14 _public enumerator_ `Size16Kb = 16 * 1024 UMETA(DisplayName = "16kb")`
- L15 _public enumerator_ `Size32Kb = 32 * 1024 UMETA(DisplayName = "32kb")`
- L16 _public enumerator_ `Size64Kb = 64 * 1024 UMETA(DisplayName = "64kb")`
- L17 _public enumerator_ `Size128Kb = 128 * 1024 UMETA(DisplayName = "128kb")`
- L18 _public enumerator_ `Size256Kb = 256 * 1024 UMETA(DisplayName = "256kb")`
- L19 _public enumerator_ `Size512Kb = 512 * 1024 UMETA(DisplayName = "512kb")`

#### class `UEditorDataStorageSettings`  
`class UEditorDataStorageSettings : public UObject`  
_L23-33_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UObject`
- L29 _public member_ `EChunkMemorySize ChunkMemorySize = EChunkMemorySize::Size128Kb;` — `UPROPERTY(EditAnywhere, config, Category = MassSettings)`
- L32 _public member_ `TMap<FName, EChunkMemorySize> TableSpecificChunkMemorySize;` — `UPROPERTY(EditAnywhere, config, Category = MassSettings)`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/GlobalLock.h` (Private)


#### enum `UE::Editor::DataStorage::EGlobalLockStatus`  
`enum class EGlobalLockStatus : uint8`  
_L12-17_
- L14 _public enumerator_ `Unlocked`
- L15 _public enumerator_ `SharedLocked`
- L16 _public enumerator_ `ExclusiveLocked`

#### enum `UE::Editor::DataStorage::EGlobalLockScope`  
`enum class EGlobalLockScope : uint8`  
_L19-29_
- L22 _public enumerator_ `Public` — The lock request is coming from a public facing call.
- L28 _public enumerator_ `Internal` — The lock is coming from an internal call. These typically have a wider range of calling threads, but only support shared access. Exclusive locks will check for validity.

#### class `UE::Editor::DataStorage::FGlobalLock`  
`class FGlobalLock`  
_L46-64_
- desc: Sets a lock for all of TEDS systems. This is used whenever access to any data within TEDS is needed in a thread-safe manner. Shared locks will allow multiple thread to safely read data, while exclusive locks provide safe read/write access. The Global lock has an internal lock so shared locks can be freely handed out to requests with an internal scope. Exclusive locks with the same scope will assert. This is meant to only be called by TEDS Core to lock the global lock for the duration of a processing phase. This is the only safe time to call it as all operations within a phase will be processed on all threads before a phase ends. If this is used for global calls it's possible that such a call is still processing when TEDS Core releases the lock and another exclusive lock is acquired. Therefore global locks fall back to full lock. Use global locks except from within adaptors that run in Mass processors. The global lock uses internal reference counting to allow recursive calls from the same thread. Further state management also helps track incorrect requests for an exclusive lock on a thread that already has a shared lock. An assert triggers in this case to prevent deadlocks.
- L49 _public prototype_ `static void SharedLock(EGlobalLockScope Scope);`
- L50 _public prototype_ `static void ExclusiveLock(EGlobalLockScope Scope);`
- L51 _public prototype_ `static void Unlock(EGlobalLockScope Scope);`
- L53 _public prototype_ `static EGlobalLockStatus GetLockStatus(EGlobalLockScope Scope);`
- L56 _private prototype_ `static void InternalSharedLock();`
- L57 _private prototype_ `static void InternalSharedUnlock();`
- L59 _private member_ `static FTransactionallySafeRWLock Lock;`
- L61 _private member_ `static thread_local EGlobalLockStatus LockStatus;` — Keep track of the lock status because FRWLock is non-recursive and with a global lock it's easy to get recursive calls.
- L62 _private member_ `static thread_local uint64 LockCount;`
- L63 _private member_ `static std::atomic<EGlobalLockStatus> InternalLockStatus;`

#### class `UE::Editor::DataStorage::FScopedSharedLock`  
`class FScopedSharedLock`  
_L66-74_
- L69 _public prototype_ `explicit FScopedSharedLock(EGlobalLockScope InScope);`
- L70 _public prototype_ `~FScopedSharedLock();`
- L73 _private member_ `EGlobalLockScope Scope;`

#### class `UE::Editor::DataStorage::FScopedExclusiveLock`  
`class FScopedExclusiveLock`  
_L76-84_
- L79 _public prototype_ `explicit FScopedExclusiveLock(EGlobalLockScope InScope);`
- L80 _public prototype_ `~FScopedExclusiveLock();`
- L83 _private member_ `EGlobalLockScope Scope;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Hierarchy/EditorDataStorageHierarchyColumns.h` (Private)


#### struct `FEditorDataHierarchyData_Template`  
`struct FEditorDataHierarchyData_Template final : public FEditorDataStorageColumn`  
_L11-20_
- reflection: `USTRUCT(meta = (DisplayName = "EditorDataHierarchyData (Template)", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageColumn`
- L16 _public member_ `FTedsRowHandle Parent;` — `UPROPERTY()`
- L19 _public member_ `TArray<FTedsRowHandle> Children;` — `UPROPERTY()`

#### struct `FEditorDataHierarchyParentTag_Template`  
`struct FEditorDataHierarchyParentTag_Template : public FEditorDataStorageTag`  
_L23-26_
- reflection: `USTRUCT(meta = (DisplayName = "EditorDataHierarchyParentTag (Template)", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`

#### struct `FEditorDataHierarchyChildTag_Template`  
`struct FEditorDataHierarchyChildTag_Template : public FEditorDataStorageTag`  
_L29-32_
- reflection: `USTRUCT(meta = (DisplayName = "EditorDataHierarchyChildTag (Template)", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`

#### struct `FEditorDataHierarchyUnresolvedParent_Template`  
`struct FEditorDataHierarchyUnresolvedParent_Template final : public FEditorDataStorageColumn`  
_L35-45_
- reflection: `USTRUCT(meta = (DisplayName = "Unresolved Parent (Template)", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageColumn`
- L40 _public member_ `UE::Editor::DataStorage::FMapKey ParentId;` — The Id used to lookup the parent row every frame
- L43 _public member_ `FName MappingDomain;` — The mapping domain the ParentID is looked up in

#### struct `FEditorDataHierarchyParentChangedTag_Template`  
`struct FEditorDataHierarchyParentChangedTag_Template final : public FEditorDataStorageTag`  
_L48-51_
- reflection: `USTRUCT(meta = (DisplayName = "Parent Changed Column (Template)", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace Editor` (scope `UE`)
- L54 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L56 _typedef_ `using FHierarchyData_Template = FEditorDataHierarchyData_Template;` (scope `UE::Editor::DataStorage`)
- L57 _typedef_ `using FHierarchyParentTag_Template = FEditorDataHierarchyParentTag_Template;` (scope `UE::Editor::DataStorage`)
- L58 _typedef_ `using FHierarchyChildTag_Template = FEditorDataHierarchyChildTag_Template;` (scope `UE::Editor::DataStorage`)
- L59 _typedef_ `using FHierarchyUnresolvedParentColumn_Template = FEditorDataHierarchyUnresolvedParent_Template;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Hierarchy/EditorDataStorageHierarchyImplementation.h` (Private)


#### enum `UE::Editor::DataStorage::EHierarchyBackend`  
`enum class EHierarchyBackend : uint8`  
_L11-15_
- L13 _public enumerator_ `Legacy = 0`
- L14 _public enumerator_ `Relations = 1`

#### class `UE::Editor::DataStorage::FTedsHierarchyRegistrar`  
`class FTedsHierarchyRegistrar final`  
_L18-71_
- L22 _public prototype_ `~FTedsHierarchyRegistrar();`
- L27 _public prototype_ `FHierarchyHandle RegisterHierarchy(ICoreProvider* InProvider, const FHierarchyRegistrationParams& Params);` — Registers a hierarchy type with TEDS This sets up the internal columns and processors to kee the bidirectional relationship in sync
- L31 _public prototype_ `FHierarchyHandle FindHierarchyByName(const FName& Name) const;` — Finds a registered hierarchy by name
- L35 _public prototype_ `const FTedsHierarchyAccessInterface* GetAccessInterface(FHierarchyHandle) const;` — Gets an interface to add and remove rows from a hierarchy and walk the hierarchy
- L40 _public prototype_ `void ListHierarchyNames(TFunctionRef<void(const FName& HierarchyName)> Callback) const;` — Iterate over all registered hierarchyes
- L45 _public prototype_ `void ResolveHierarchy(ICoreProvider& CoreProvider, FHierarchyHandle HierarchyHandle);` — Try to resolve all child rows with unresolved parent columns
- L48 _private prototype_ `FHierarchyHandle RegisterHierarchyLegacy(ICoreProvider* InProvider, const FHierarchyRegistrationParams& Params);`
- L49 _private prototype_ `FHierarchyHandle RegisterHierarchyRelations(ICoreProvider* InProvider, const FHierarchyRegistrationParams& Params);`
- L50 _private prototype_ `void RegisterObservers(ICoreProvider& CoreProvider, const FHierarchyHandle& Handle);`
- L51 _private prototype_ `void RegisterProcessors(ICoreProvider& CoreProvider, const FHierarchyHandle& Handle);`
- L67 _private prototype_ `const FRegisteredHierarchy* FindRegisteredHierarchy(const FHierarchyHandle& Handle);`
- L70 _private member_ `TArray<FRegisteredHierarchy> RegisteredHierarchies;`

#### struct `UE::Editor::DataStorage::FTedsHierarchyRegistrar::FRegisteredHierarchy`  
`struct FRegisteredHierarchy`  
_L53-65_
- L55 _public member_ `FName Name;`
- L56 _public member_ `const UScriptStruct* ChildTag;`
- L57 _public member_ `const UScriptStruct* ParentTag;`
- L58 _public member_ `const UScriptStruct* HierarchyData;`
- L59 _public member_ `const UScriptStruct* UnresolvedParentColumn;`
- L60 _public member_ `const UScriptStruct* ParentChangedColumn;`
- L61 _public member_ `TUniquePtr<FTedsHierarchyAccessInterface> AccessInterface;`
- L62 _public member_ `QueryHandle UnresolvedChildRowsQueryHandle = InvalidQueryHandle;`
- L63 _public member_ `EHierarchyBackend Backend = EHierarchyBackend::Legacy;`
- L64 _public member_ `RelationTypeHandle HierarchyRelationType = InvalidRelationTypeHandle;`

#### class `UE::Editor::DataStorage::FTedsHierarchyAccessInterface`  
`class FTedsHierarchyAccessInterface`  
_L80-130_
- desc: Abstract interface for accessing hierarchy operations. Concrete backends (adjacency-list and relations) are defined in the .cpp. The non-virtual context-dispatch overloads are generic and live here because they delegate to the virtual ICoreProvider* overloads via context unwrapping.
- L83 _public prototype_ `virtual ~FTedsHierarchyAccessInterface() = default;`
- L85 _public prototype_ `virtual const UScriptStruct* GetChildTagType() const = 0;`
- L86 _public prototype_ `virtual const UScriptStruct* GetParentTagType() const = 0;`
- L87 _public prototype_ `virtual const UScriptStruct* GetHierarchyDataColumnType() const = 0;`
- L88 _public prototype_ `virtual const UScriptStruct* GetUnresolvedParentColumnType() const = 0;`
- L89 _public prototype_ `virtual const UScriptStruct* GetParentChangedColumnType() const = 0;`
- L91 _public prototype_ `virtual void SetParentRow(ICoreProvider* CoreProvider, RowHandle Target, RowHandle Parent) const = 0;`
- L92 _public prototype_ `virtual void SetUnresolvedParent(ICoreProvider* CoreProvider, RowHandle Target, FMapKey ParentId, FName MappingDomain) const = 0;`
- L93 _public prototype_ `virtual RowHandle GetParentRow(const ICoreProvider* CoreProvider, RowHandle Target) const = 0;`
- L95 _public prototype_ `virtual bool HasChildren(const ICoreProvider& Context, RowHandle Row) const = 0;`
- L96 _public prototype_ `virtual void WalkDepthFirst( const ICoreProvider& Context, RowHandle Row, TFunction<void(const ICoreProvider& Context, RowHandle Owner, RowHandle Target)> OnVisitedFn, ICoreProvider::ETraversalOrder TraversalOrder = ICoreProvider::ETraversalOrder::PreOrder) const = 0;`
- L102 _public function_ `virtual bool IterateChildren( const ICoreProvider& Context, RowHandle Row, TFunctionRef<bool(const ICoreProvider& Context, RowHandle Child)> OnVisitedFn) const`
- L110 _public prototype_ `virtual TFunction<RowHandle(const void*, const UScriptStruct*)> CreateParentExtractionFunction() const = 0;`
- L113 _public prototype_ `void SetParentRow(IQueryContext& Context, RowHandle Target, RowHandle Parent) const;` — Non-virtual context-dispatch overloads — generic for all backends.
- L114 _public prototype_ `void SetUnresolvedParent(IQueryContext& Context, RowHandle Target, FMapKey ParentId, FName MappingDomain) const;`
- L115 _public prototype_ `RowHandle GetParentRow(const IQueryContext& Context, RowHandle Target) const;`
- L116 _public prototype_ `void SetParentRow(ISubqueryContext& Context, RowHandle Target, RowHandle Parent) const;`
- L117 _public prototype_ `void SetUnresolvedParent(ISubqueryContext& Context, RowHandle Target, FMapKey ParentId, FName MappingDomain) const;`
- L118 _public prototype_ `RowHandle GetParentRow(const ISubqueryContext& Context, RowHandle Target) const;`
- L119 _public prototype_ `void SetParentRow(IDirectQueryContext& Context, RowHandle Target, RowHandle Parent) const;`
- L120 _public prototype_ `void SetUnresolvedParent(IDirectQueryContext& Context, RowHandle Target, FMapKey ParentId, FName MappingDomain) const;`
- L121 _public prototype_ `RowHandle GetParentRow(const IDirectQueryContext& Context, RowHandle Target) const;`
- L125 _protected prototype_ `void SetParent(ICommonQueryContext& Context, RowHandle Target, RowHandle Parent) const;` — Generic context-dispatch helpers shared by all backends.
- L126 _protected prototype_ `void SetUnresolvedParent(ICommonQueryContext& Context, RowHandle Target, FMapKey ParentId, FName MappingDomain) const;`
- L129 _protected prototype_ `virtual RowHandle GetParent(const ICommonQueryContext& Context, RowHandle Target) const;` — Context-aware parent lookup. Default returns InvalidRowHandle; override in column-backed backends.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Memento/TypedElementMementoRowTypes.h` (Private)


#### struct `FTypedElementMementoTag`  
`struct FTypedElementMementoTag : public FEditorDataStorageTag`  
_L17-20_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageTag`
- desc: MementoTag denotes that the row is a memento

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Memento/TypedElementMementoSystem.h` (Private)


#### class `UE::Editor::DataStorage::FMementoSystem`  
`class FMementoSystem`  
_L15-31_
- L18 _public prototype_ `FMementoSystem(ICoreProvider& InDataStorage, FTableManager& TableManager);`
- L20 _public prototype_ `RowHandle CreateMemento(RowHandle SourceRow);`
- L21 _public prototype_ `void CreateMemento(RowHandle ReservedMementoRow, RowHandle SourceRow);`
- L22 _public prototype_ `void RestoreMemento(RowHandle MementoRow, RowHandle TargetRow);`
- L23 _public prototype_ `void DestroyMemento(RowHandle MementoRow);`
- L26 _private prototype_ `void CreateMementoInternal(RowHandle MementoRow, RowHandle SourceRow);`
- L28 _private member_ `TArray<const UTedsMementoTranslatorBase*> MementoTranslators;`
- L29 _private member_ `TableHandle MementoRowBaseTable;`
- L30 _private member_ `ICoreProvider& DataStorage;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Memento/TypedElementMementoizedColumns.h` (Private)


#### class `UTedsSelectionColumnMementoTranslator`  
`class UTedsSelectionColumnMementoTranslator final : public UTedsDefaultMementoTranslator`  
_L14-19_
- reflection: `UCLASS()`
- inherits: `UTedsDefaultMementoTranslator`
- desc: Enable SelectionColumn to be mementoized
- L18 _public function_ `virtual const UScriptStruct* GetColumnType() const override`

#### class `UTedsVisibilityColumnMementoTranslator`  
`class UTedsVisibilityColumnMementoTranslator final : public UTedsDefaultMementoTranslator`  
_L25-32_
- reflection: `UCLASS()`
- inherits: `UTedsDefaultMementoTranslator`
- desc: Enable Visibility to be mementoized
- L30 _public prototype_ `UTedsVisibilityColumnMementoTranslator();`
- L31 _public prototype_ `virtual const UScriptStruct* GetColumnType() const override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Processors/QueryCapabilityImplementationForwarder.h` (Private)


#### struct `UE::Editor::DataStorage::Queries::Private::TImplementationForwarder`  
`template<typename Environment, typename Interface, typename... Implementations> struct TImplementationForwarder`  
_L17-22_
- L27 _public prototype_ `TImplementationForwarder() = default;`
- L30 _public function_ `template<typename... TArgs> explicit TImplementationForwarder(TArgs&&... Args) : ContextEnvironment(Forward<TArgs>(Args)...)`
- L35 _public member_ `Environment ContextEnvironment;`

#### struct `UE::Editor::DataStorage::Queries::Private::TImplementationForwarder`  
`template<typename Environment, typename Interface> struct TImplementationForwarder<Environment, Interface> : Interface`  
_L25-36_
- inherits: `Interface`
- L27 _public prototype_ `TImplementationForwarder() = default;`
- L30 _public function_ `template<typename... TArgs> explicit TImplementationForwarder(TArgs&&... Args) : ContextEnvironment(Forward<TArgs>(Args)...)`
- L35 _public member_ `Environment ContextEnvironment;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L11 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::Queries`)
- L41 _macro_ `#define ArgTypeName(Type, Name) Type Name`
- L42 _macro_ `#define ArgName(Type, Name) Name`
- L43 _macro_ `#define ForwardArg(Type, Name) Forward< Type >( Name )`
- L45 _macro_ `#define CallFunction(Capability, ReturnValue, FunctionName, ...) \`
- L61 _macro_ `#define CapabilityStart(Capability, Flags) \`
- L75 _macro_ `#define Function0(Capability, Return, Function) virtual Return Function() \`
- L77 _macro_ `#define Function1(Capability, Return, Function, Arg1) virtual Return Function(ArgTypeName Arg1 ) override \`
- L79 _macro_ `#define Function2(Capability, Return, Function, Arg1, Arg2) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) override \`
- L81 _macro_ `#define Function3(Capability, Return, Function, Arg1, Arg2, Arg3) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) override \`
- L83 _macro_ `#define Function4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) override \`
- L86 _macro_ `#define ConstFunction0(Capability, Return, Function) virtual Return Function() const \`
- L88 _macro_ `#define ConstFunction1(Capability, Return, Function, Arg1) virtual Return Function(ArgTypeName Arg1 ) const override \`
- L90 _macro_ `#define ConstFunction2(Capability, Return, Function, Arg1, Arg2) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 ) const override \`
- L92 _macro_ `#define ConstFunction3(Capability, Return, Function, Arg1, Arg2, Arg3) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 ) const override \`
- L94 _macro_ `#define ConstFunction4(Capability, Return, Function, Arg1, Arg2, Arg3, Arg4) virtual Return Function(ArgTypeName Arg1 , ArgTypeName Arg2 , ArgTypeName Arg3 , ArgTypeName Arg4 ) const override \`
- L97 _macro_ `#define CapabilityEnd(Capability) \`
- L100 _macro_ `#define DeprecatedFunction(Version, Msg) UE_DEPRECATED(Version, Msg)`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Processors/TypedElementProcessorAdaptors.h` (Private)


#### struct `UE::Editor::DataStorage::FPhasePreOrPostAmbleExecutor`  
`struct FPhasePreOrPostAmbleExecutor`  
_L21-34_
- L23 _public prototype_ `FPhasePreOrPostAmbleExecutor(FMassEntityManager& EntityManager, float DeltaTime);`
- L24 _public prototype_ `~FPhasePreOrPostAmbleExecutor();`
- L26 _public prototype_ `void ExecuteQuery( FQueryDescription& Description, FExtendedQueryStore& QueryStore, FEnvironment& Environment, FMassEntityQuery& NativeQuery, QueryCallbackRef Callback);`
- L33 _public member_ `FMassExecutionContext Context;`

#### struct `FTypedElementQueryProcessorData`  
`struct FTypedElementQueryProcessorData`  
_L38-101_
- reflection: `USTRUCT()`
- L42 _public prototype_ `FTypedElementQueryProcessorData() = default;`
- L43 _public prototype_ `explicit FTypedElementQueryProcessorData(UMassProcessor& Owner);`
- L45 _public prototype_ `bool CommonQueryConfiguration( UMassProcessor& InOwner, UE::Editor::DataStorage::FExtendedQuery& InQuery, UE::Editor::DataStorage::FExtendedQueryStore::Handle InQueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& InQueryStore, UE::Editor::DataStorage::FEnvironment& InEnvironment, TArrayView<FMassEntityQuery> Subqueries);`
- L52 _public prototype_ `static EMassProcessingPhase MapToMassProcessingPhase(UE::Editor::DataStorage::EQueryTickPhase Phase);`
- L53 _public prototype_ `FString GetProcessorName() const;`
- L54 _public prototype_ `void DebugOutputDescription(FOutputDevice& Ar, int32 Indent) const;`
- L56 _public prototype_ `static UE::Editor::DataStorage::FQueryResult Execute( UE::Editor::DataStorage::DirectQueryCallbackRef& Callback, UE::Editor::DataStorage::FQueryDescription& Description, FMassEntityQuery& NativeQuery, FMassEntityManager& EntityManager, UE::Editor::DataStorage::FEnvironment& Environment, UE::Editor::DataStorage::EDirectQueryExecutionFlags ExecutionFlags);`
- L63 _public prototype_ `static UE::Editor::DataStorage::FQueryResult Execute( UE::Editor::DataStorage::Queries::TQueryFunction<void>& Callback, UE::Editor::DataStorage::FQueryDescription& Description, FMassEntityQuery& NativeQuery, FMassEntityManager& EntityManager, UE::Editor::DataStorage::FEnvironment& Environment, UE::Editor::DataStorage::ERunQueryFlags ExecutionFlags);`
- L70 _public prototype_ `static UE::Editor::DataStorage::FQueryResult Execute( const UE::Editor::DataStorage::Queries::TConstQueryFunction<void>& Callback, const UE::Editor::DataStorage::FQueryDescription& Description, FMassEntityQuery& NativeQuery, FMassEntityManager& EntityManager, UE::Editor::DataStorage::FEnvironment& Environment, UE::Editor::DataStorage::ERunQueryFlags ExecutionFlags);`
- L77 _public prototype_ `static UE::Editor::DataStorage::FQueryResult Execute( UE::Editor::DataStorage::SubqueryCallbackRef& Callback, UE::Editor::DataStorage::FQueryDescription& Description, FMassEntityQuery& NativeQuery, FMassEntityManager& EntityManager, UE::Editor::DataStorage::FEnvironment& Environment, FMassExecutionContext& ParentContext);`
- L84 _public prototype_ `static UE::Editor::DataStorage::FQueryResult Execute( UE::Editor::DataStorage::SubqueryCallbackRef& Callback, UE::Editor::DataStorage::FQueryDescription& Description, UE::Editor::DataStorage::RowHandle RowHandle, FMassEntityQuery& NativeQuery, FMassEntityManager& EntityManager, UE::Editor::DataStorage::FEnvironment& Environment, FMassExecutionContext& ParentContext);`
- L92 _public prototype_ `void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context);`
- L94 _public prototype_ `static bool PrepareCachedDependenciesOnQuery( UE::Editor::DataStorage::FQueryDescription& Description, FMassExecutionContext& Context);`
- L97 _public member_ `UE::Editor::DataStorage::FExtendedQueryStore::Handle ParentQuery;`
- L98 _public member_ `UE::Editor::DataStorage::FExtendedQueryStore* QueryStore{ nullptr };`
- L99 _public member_ `UE::Editor::DataStorage::FEnvironment* Environment{ nullptr };`
- L100 _public member_ `FMassEntityQuery NativeQuery;`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorBase : public UMassProcessor`  
_L107-140_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Adapts processor queries callback for MASS.
- L112 _public prototype_ `UTypedElementQueryProcessorCallbackAdapterProcessorBase();`
- L114 _public prototype_ `FMassEntityQuery& GetQuery();`
- L115 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment);`
- L121 _public prototype_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode) const override;`
- L124 _protected prototype_ `bool ConfigureQueryCallbackData( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment, TArrayView<FMassEntityQuery> Subqueries);`
- L130 _protected prototype_ `void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override;`
- L131 _protected prototype_ `void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& TargetParentQuery) override;`
- L133 _protected prototype_ `void PostInitProperties() override;`
- L134 _protected prototype_ `FString GetProcessorName() const override;`
- L135 _protected prototype_ `void DebugOutputDescription(FOutputDevice& Ar, int32 Indent) const override;`
- L139 _private member_ `FTypedElementQueryProcessorData Data;` — `UPROPERTY(transient)`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessor`  
`class UTypedElementQueryProcessorCallbackAdapterProcessor final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L143-146_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith1Subquery`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith1Subquery final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L157-170_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L162 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L169 _private member_ `FMassEntityQuery NativeSubqueries[1];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith2Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith2Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L173-186_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L178 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L185 _private member_ `FMassEntityQuery NativeSubqueries[2];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith3Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith3Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L189-202_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L194 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L201 _private member_ `FMassEntityQuery NativeSubqueries[3];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith4Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith4Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L205-218_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L210 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L217 _private member_ `FMassEntityQuery NativeSubqueries[4];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith5Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith5Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L221-234_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L226 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L233 _private member_ `FMassEntityQuery NativeSubqueries[5];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith6Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith6Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L237-250_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L242 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L249 _private member_ `FMassEntityQuery NativeSubqueries[6];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith7Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith7Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L253-266_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L258 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L265 _private member_ `FMassEntityQuery NativeSubqueries[7];`

#### class `UTypedElementQueryProcessorCallbackAdapterProcessorWith8Subqueries`  
`class UTypedElementQueryProcessorCallbackAdapterProcessorWith8Subqueries final : public UTypedElementQueryProcessorCallbackAdapterProcessorBase`  
_L269-282_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryProcessorCallbackAdapterProcessorBase`
- L274 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L281 _private member_ `FMassEntityQuery NativeSubqueries[8];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorBase`  
`class UTypedElementQueryObserverCallbackAdapterProcessorBase : public UMassObserverProcessor`  
_L288-321_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- desc: Adapts observer queries callback for MASS.
- L293 _public prototype_ `UTypedElementQueryObserverCallbackAdapterProcessorBase();`
- L295 _public prototype_ `FMassEntityQuery& GetQuery();`
- L296 _public prototype_ `const UScriptStruct* GetObservedType() const;`
- L297 _public prototype_ `EMassObservedOperationFlags GetObservedOperations() const;`
- L298 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment);`
- L305 _protected prototype_ `bool ConfigureQueryCallbackData( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment, TArrayView<FMassEntityQuery> Subqueries);`
- L311 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L312 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& TargetParentQuery) override;`
- L314 _protected prototype_ `virtual void PostInitProperties() override;`
- L315 _protected prototype_ `virtual void Register() override;`
- L316 _protected prototype_ `virtual FString GetProcessorName() const override;`
- L317 _protected prototype_ `virtual void DebugOutputDescription(FOutputDevice& Ar, int32 Indent) const override;`
- L320 _private member_ `FTypedElementQueryProcessorData Data;`

#### class `UTypedElementQueryObserverCallbackAdapterProcessor`  
`class UTypedElementQueryObserverCallbackAdapterProcessor final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L324-327_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith1Subquery`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith1Subquery final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L338-351_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L343 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L350 _private member_ `FMassEntityQuery NativeSubqueries[1];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith2Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith2Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L354-367_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L359 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L366 _private member_ `FMassEntityQuery NativeSubqueries[2];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith3Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith3Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L370-383_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L375 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L382 _private member_ `FMassEntityQuery NativeSubqueries[3];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith4Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith4Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L386-399_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L391 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L398 _private member_ `FMassEntityQuery NativeSubqueries[4];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith5Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith5Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L402-415_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L407 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L414 _private member_ `FMassEntityQuery NativeSubqueries[5];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith6Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith6Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L418-431_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L423 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L430 _private member_ `FMassEntityQuery NativeSubqueries[6];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith7Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith7Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L434-447_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L439 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L446 _private member_ `FMassEntityQuery NativeSubqueries[7];`

#### class `UTypedElementQueryObserverCallbackAdapterProcessorWith8Subqueries`  
`class UTypedElementQueryObserverCallbackAdapterProcessorWith8Subqueries final : public UTypedElementQueryObserverCallbackAdapterProcessorBase`  
_L450-463_
- reflection: `UCLASS()`
- inherits: `UTypedElementQueryObserverCallbackAdapterProcessorBase`
- L455 _public prototype_ `virtual bool ConfigureQueryCallback( UE::Editor::DataStorage::FExtendedQuery& Query, UE::Editor::DataStorage::FExtendedQueryStore::Handle QueryHandle, UE::Editor::DataStorage::FExtendedQueryStore& QueryStore, UE::Editor::DataStorage::FEnvironment& Environment) override;`
- L462 _private member_ `FMassEntityQuery NativeSubqueries[8];`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySearchers/DefaultPropertySearcherFactory.h` (Private)


#### class `UDefaultPropertySearcherFactory`  
`class UDefaultPropertySearcherFactory : public UEditorDataStorageFactory`  
_L13-19_
- reflection: `UCLASS(Transient)`
- inherits: `UEditorDataStorageFactory`
- desc: Factory used to register searcher for text properties.
- L18 _public prototype_ `virtual void RegisterPropertySearchers(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySearchers/PropertySearcherBase.h` (Private)


#### class `UE::Editor::DataStorage::Searchers::TPropertySearcherBase`  
`template<typename SearchableType, typename PropertyType> class TPropertySearcherBase : public FColumnSearcherInterface`  
_L18-33_
- inherits: `FColumnSearcherInterface`
- L21 _public prototype_ `TPropertySearcherBase(TWeakObjectPtr<const UScriptStruct> ColumnType, const PropertyType* Property);`
- L23 _public prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const override;`
- L26 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const SearchableType& Value) const = 0;`
- L29 _private prototype_ `const SearchableType* GetValue(const ICoreProvider& Storage, const UScriptStruct* Column, RowHandle Row) const;`
- L31 _private member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`
- L32 _private member_ `const PropertyType* Property;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Searchers` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySearchers/PropertySearcherBase.inl` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Editor` (scope `UE`)
- L5 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L5 _namespace_ `namespace Searchers` (scope `UE::Editor::DataStorage`)
- L8 _function_ `template<typename SearchableType, typename PropertyType> TPropertySearcherBase<SearchableType, PropertyType>::TPropertySearcherBase( TWeakObjectPtr<const UScriptStruct> ColumnType, const PropertyType* Property) : ColumnType(MoveTemp(ColumnType)) , Property(Property)` (scope `UE::Editor::DataStorage::Searchers::TPropertySearcherBase`)
- L16 _function_ `template<typename SearchableType, typename PropertyType> void TPropertySearcherBase<SearchableType, PropertyType>::GetSearchableString( FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const` (scope `UE::Editor::DataStorage::Searchers::TPropertySearcherBase`)
- L29 _function_ `template<typename SearchableType, typename PropertyType> const SearchableType* TPropertySearcherBase<SearchableType, PropertyType>::GetValue( const ICoreProvider& Storage, const UScriptStruct* Column, RowHandle Row) const` (scope `UE::Editor::DataStorage::Searchers::TPropertySearcherBase`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySearchers/StringSearchers.h` (Private)


#### class `UE::Editor::DataStorage::Searchers::FStringSearcher`  
`class FStringSearcher final : public TPropertySearcherBase<FString, FStrProperty>`  
_L21-29_
- inherits: `TPropertySearcherBase<FString,FStrProperty>`
- L23 _private typedef_ `using BaseType = TPropertySearcherBase<FString, FStrProperty>;`
- L25 _public prototype_ `FStringSearcher(TWeakObjectPtr<const UScriptStruct> ColumnType, const FStrProperty* Property);`
- L28 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const FString& Value) const override;`

#### class `UE::Editor::DataStorage::Searchers::FTextSearcher`  
`class FTextSearcher final : public TPropertySearcherBase<FText, FTextProperty>`  
_L32-40_
- inherits: `TPropertySearcherBase<FText,FTextProperty>`
- L34 _private typedef_ `using BaseType = TPropertySearcherBase<FText, FTextProperty>;`
- L36 _public prototype_ `FTextSearcher(TWeakObjectPtr<const UScriptStruct> ColumnType, const FTextProperty* Property);`
- L39 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const FText& Value) const override;`

#### class `UE::Editor::DataStorage::Searchers::FNameSearcher`  
`class FNameSearcher final : public TPropertySearcherBase<FName, FNameProperty>`  
_L43-51_
- inherits: `TPropertySearcherBase<FName,FNameProperty>`
- L45 _private typedef_ `using BaseType = TPropertySearcherBase<FName, FNameProperty>;`
- L47 _public prototype_ `FNameSearcher(TWeakObjectPtr<const UScriptStruct> ColumnType, const FNameProperty* Property);`
- L50 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const FName& Value) const override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _namespace_ `namespace Searchers` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySorters/DefaultPropertySorterFactory.h` (Private)


#### class `UDefaultPropertySorterFactory`  
`class UDefaultPropertySorterFactory : public UEditorDataStorageFactory`  
_L13-19_
- reflection: `UCLASS(Transient)`
- inherits: `UEditorDataStorageFactory`
- desc: Factory used to register sorter for numeric and text properties.
- L18 _public prototype_ `virtual void RegisterPropertySorters(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySorters/NumericSorters.h` (Private)


#### class `UE::Editor::DataStorage::Sorters::TNumericSorter`  
`template<typename NumericType, typename NumericPropertyType> class TNumericSorter final : public TPropertySorterBase<FColumnSorterInterface::ESortType::FixedSize64, NumericType, NumericPropertyType>`  
_L21-31_
- inherits: `TPropertySorterBase<FColumnSorterInterface::ESortType::FixedSize64,NumericType,NumericPropertyType>`
- L24 _private typedef_ `using BaseType = TPropertySorterBase<FColumnSorterInterface::ESortType::FixedSize64, NumericType, NumericPropertyType>;`
- L26 _public prototype_ `TNumericSorter(TWeakObjectPtr<const UScriptStruct> ColumnType, const NumericPropertyType* Property);`
- L29 _protected prototype_ `virtual int32 Compare(const NumericType& Left, const NumericType& Right) const override;`
- L30 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const NumericType& Value, uint32 ByteIndex) const override;`
- L50 _function_ `template<typename NumericType, typename NumericPropertyType> TNumericSorter<NumericType, NumericPropertyType>::TNumericSorter( TWeakObjectPtr<const UScriptStruct> ColumnType, const NumericPropertyType* Property) : BaseType(MoveTemp(ColumnType), Property)`
- L57 _function_ `template<typename NumericType, typename NumericPropertyType> int32 TNumericSorter<NumericType, NumericPropertyType>::Compare(const NumericType& Left, const NumericType& Right) const`
- L63 _function_ `template<typename NumericType, typename NumericPropertyType> FPrefixInfo TNumericSorter<NumericType, NumericPropertyType>::CalculatePrefix(const NumericType& Value, uint32 ByteIndex) const`

#### class `UE::Editor::DataStorage::Sorters::FBooleanSorter`  
`class FBooleanSorter final : public TPropertySorterBase<FColumnSorterInterface::ESortType::FixedSize64, bool, FBoolProperty>`  
_L33-42_
- inherits: `TPropertySorterBase<FColumnSorterInterface::ESortType::FixedSize64,bool,FBoolProperty>`
- L35 _private typedef_ `using BaseType = TPropertySorterBase<FColumnSorterInterface::ESortType::FixedSize64, bool, FBoolProperty>;`
- L37 _public prototype_ `FBooleanSorter(TWeakObjectPtr<const UScriptStruct> ColumnType, const FBoolProperty* Property);`
- L40 _protected prototype_ `virtual int32 Compare(const bool& Left, const bool& Right) const override;`
- L41 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const bool& Value, uint32 ByteIndex) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace Sorters` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySorters/PropertySorterBase.h` (Private)


#### class `UE::Editor::DataStorage::Sorters::TPropertySorterBase`  
`template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> class TPropertySorterBase : public FColumnSorterInterface`  
_L18-37_
- inherits: `FColumnSorterInterface`
- L21 _public prototype_ `TPropertySorterBase(TWeakObjectPtr<const UScriptStruct> ColumnType, const PropertyType* Property);`
- L23 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L24 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`
- L25 _public prototype_ `ESortType GetSortType() const override final;`
- L26 _public prototype_ `FText GetShortName() const override final;`
- L29 _protected prototype_ `virtual int32 Compare(const CompareType& Left, const CompareType& Right) const = 0;`
- L30 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const CompareType& Value, uint32 ByteIndex) const = 0;`
- L33 _private prototype_ `const CompareType* GetValue(const ICoreProvider& Storage, const UScriptStruct* Column, RowHandle Row) const;`
- L35 _private member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`
- L36 _private member_ `const PropertyType* Property;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Sorters` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySorters/PropertySorterBase.inl` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Editor` (scope `UE`)
- L5 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L5 _namespace_ `namespace Sorters` (scope `UE::Editor::DataStorage`)
- L8 _function_ `template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> TPropertySorterBase<SortType, CompareType, PropertyType>::TPropertySorterBase( TWeakObjectPtr<const UScriptStruct> ColumnType, const PropertyType* Property) : ColumnType(MoveTemp(ColumnType)) , Property(Property)` (scope `UE::Editor::DataStorage::Sorters::TPropertySorterBase`)
- L16 _function_ `template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> int32 TPropertySorterBase<SortType, CompareType, PropertyType>::Compare( const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const` (scope `UE::Editor::DataStorage::Sorters::TPropertySorterBase`)
- L32 _function_ `template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> FPrefixInfo TPropertySorterBase<SortType, CompareType, PropertyType>::CalculatePrefix( const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const` (scope `UE::Editor::DataStorage::Sorters::TPropertySorterBase`)
- L49 _function_ `template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> FColumnSorterInterface::ESortType TPropertySorterBase<SortType, CompareType, PropertyType>::GetSortType() const` (scope `UE::Editor::DataStorage::Sorters::TPropertySorterBase`)
- L55 _function_ `template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> FText TPropertySorterBase<SortType, CompareType, PropertyType>::GetShortName() const` (scope `UE::Editor::DataStorage::Sorters::TPropertySorterBase`)
- L62 _function_ `template<FColumnSorterInterface::ESortType SortType, typename CompareType, typename PropertyType> const CompareType* TPropertySorterBase<SortType, CompareType, PropertyType>::GetValue( const ICoreProvider& Storage, const UScriptStruct* Column, RowHandle Row) const` (scope `UE::Editor::DataStorage::Sorters::TPropertySorterBase`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/PropertySorters/StringSorters.h` (Private)


#### class `UE::Editor::DataStorage::Sorters::FStringSorter`  
`class FStringSorter final : public TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort, FString, FStrProperty>`  
_L21-32_
- inherits: `TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort,FString,FStrProperty>`
- L23 _private typedef_ `using BaseType = TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort, FString, FStrProperty>;`
- L25 _public prototype_ `FStringSorter(TWeakObjectPtr<const UScriptStruct> ColumnType, const FStrProperty* Property);`
- L28 _protected prototype_ `virtual int32 Compare(const FString& Left, const FString& Right) const override;`
- L29 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const FString& Value, uint32 ByteIndex) const override;`
- L31 _protected member_ `bool bCaseSensitive = false;`

#### class `UE::Editor::DataStorage::Sorters::FTextSorter`  
`class FTextSorter final : public TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort, FText, FTextProperty>`  
_L35-46_
- inherits: `TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort,FText,FTextProperty>`
- L37 _private typedef_ `using BaseType = TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort, FText, FTextProperty>;`
- L39 _public prototype_ `FTextSorter(TWeakObjectPtr<const UScriptStruct> ColumnType, const FTextProperty* Property);`
- L42 _protected prototype_ `virtual int32 Compare(const FText& Left, const FText& Right) const override;`
- L43 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const FText& Value, uint32 ByteIndex) const override;`
- L45 _protected member_ `bool bCaseSensitive = false;`

#### class `UE::Editor::DataStorage::Sorters::FNameSorter`  
`class FNameSorter final : public TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort, FName, FNameProperty>`  
_L49-60_
- inherits: `TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort,FName,FNameProperty>`
- L51 _private typedef_ `using BaseType = TPropertySorterBase<FColumnSorterInterface::ESortType::HybridSort, FName, FNameProperty>;`
- L53 _public prototype_ `FNameSorter(TWeakObjectPtr<const UScriptStruct> ColumnType, const FNameProperty* Property);`
- L56 _protected prototype_ `virtual int32 Compare(const FName& Left, const FName& Right) const override;`
- L57 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const FName& Value, uint32 ByteIndex) const override;`
- L59 _protected member_ `ESortByNameFlags SortByFlags = ESortByNameFlags::Default;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _namespace_ `namespace Sorters` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/DirectContextEnvironment.h` (Private)


#### struct `UE::Editor::DataStorage::Queries::FDirectContextEnvironment`  
`struct FDirectContextEnvironment final : IContextEnvironment`  
_L19-38_
- inherits: `IContextEnvironment`
- L21 _public prototype_ `FDirectContextEnvironment() = default;`
- L22 _public prototype_ `FDirectContextEnvironment(FEnvironment& Environment, UEditorDataStorage& DirectContext);`
- L24 _public prototype_ `void SetBatch(FRowHandleArrayView InRows);`
- L26 _public prototype_ `virtual FEnvironment* GetEnvironment() override;`
- L27 _public prototype_ `virtual const FEnvironment* GetEnvironment() const override;`
- L29 _public prototype_ `virtual FRowHandleArrayView GetBatchRows() const override;`
- L30 _public prototype_ `virtual void GetConstColumns(TArrayView<const void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) const override;`
- L31 _public prototype_ `virtual void GetMutableColumns(TArrayView<void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L32 _public prototype_ `virtual void SetCurrentRow(RowHandle Row) override;`
- L34 _public member_ `FRowHandleArrayView Rows;`
- L35 _public member_ `FEnvironment* Environment = nullptr;`
- L36 _public member_ `UEditorDataStorage* DirectContext = nullptr;`
- L37 _public member_ `RowHandle CurrentRow = InvalidRowHandle;`

#### struct `UE::Editor::DataStorage::Queries::FConstDirectContextEnvironment`  
`struct FConstDirectContextEnvironment final : IContextEnvironment`  
_L40-60_
- inherits: `IContextEnvironment`
- L43 _public prototype_ `FConstDirectContextEnvironment() = default;` — The provided rows need to be contiguous in the same table.
- L44 _public prototype_ `FConstDirectContextEnvironment(const FEnvironment& Environment, const UEditorDataStorage& DirectContext);`
- L46 _public prototype_ `void SetBatch(FRowHandleArrayView InRows);`
- L48 _public prototype_ `virtual FEnvironment* GetEnvironment() override;`
- L49 _public prototype_ `virtual const FEnvironment* GetEnvironment() const override;`
- L51 _public prototype_ `virtual FRowHandleArrayView GetBatchRows() const override;`
- L52 _public prototype_ `virtual void GetConstColumns(TArrayView<const void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) const override;`
- L53 _public prototype_ `virtual void GetMutableColumns(TArrayView<void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L54 _public prototype_ `virtual void SetCurrentRow(RowHandle Row) override;`
- L56 _public member_ `FRowHandleArrayView Rows;`
- L57 _public member_ `const FEnvironment* Environment = nullptr;`
- L58 _public member_ `const UEditorDataStorage* DirectContext = nullptr;`
- L59 _public member_ `RowHandle CurrentRow = InvalidRowHandle;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L17 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L62 _typedef_ `using QueryContext_DirectApi = TQueryContextImpl<false, FDirectContextEnvironment, FCurrentTableInfoContextCapability, FTableInfoContextCapability, FSingleRowInfoContextCapability, FRowBatchInfoContextCapability, FDynamicColumnInfoContextCapability>;` (scope `UE::Editor::DataStorage::Queries`)
- L69 _typedef_ `using QueryContext_ConstDirectApi = TQueryContextImpl<true, FConstDirectContextEnvironment, FCurrentTableInfoContextCapability, FTableInfoContextCapability, FSingleRowInfoContextCapability, FRowBatchInfoContextCapability, FDynamicColumnInfoContextCapability>;` (scope `UE::Editor::DataStorage::Queries`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/ProcessorContextEnvironment.h` (Private)


#### struct `UE::Editor::DataStorage::Queries::FProcessorContextEnvironment`  
`struct FProcessorContextEnvironment final : IContextEnvironment`  
_L17-38_
- inherits: `IContextEnvironment`
- L19 _public prototype_ `FProcessorContextEnvironment(FEnvironment& Environment, FMassExecutionContext& MassContext);`
- L21 _public prototype_ `virtual FEnvironment* GetEnvironment() override;`
- L22 _public prototype_ `virtual const FEnvironment* GetEnvironment() const override;`
- L24 _public prototype_ `virtual FRowHandleArrayView GetBatchRows() const override;`
- L25 _public prototype_ `virtual void GetConstColumns(TArrayView<const void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) const override;`
- L26 _public prototype_ `virtual void GetMutableColumns(TArrayView<void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L27 _public prototype_ `virtual void SetCurrentRow(RowHandle Row) override;`
- L29 _public function_ `void SetSubRange(int32 InStart, int32 InLength)`
- L30 _public function_ `void ClearSubRange()`
- L31 _public function_ `bool HasSubRange() const`
- L33 _public member_ `FEnvironment& Environment;`
- L34 _public member_ `FMassExecutionContext& MassContext;`
- L35 _public member_ `RowHandle CurrentRow = InvalidRowHandle;`
- L36 _public member_ `int32 SubRangeStart = 0;`
- L37 _public member_ `int32 SubRangeLength = -1;`

#### struct `UE::Editor::DataStorage::Queries::FConstProcessorContextEnvironment`  
`struct FConstProcessorContextEnvironment final : IContextEnvironment`  
_L40-61_
- inherits: `IContextEnvironment`
- L42 _public prototype_ `FConstProcessorContextEnvironment(const FEnvironment& Environment, const FMassExecutionContext& MassContext);`
- L44 _public prototype_ `virtual FEnvironment* GetEnvironment() override;`
- L45 _public prototype_ `virtual const FEnvironment* GetEnvironment() const override;`
- L47 _public prototype_ `virtual FRowHandleArrayView GetBatchRows() const override;`
- L48 _public prototype_ `virtual void GetConstColumns(TArrayView<const void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) const override;`
- L49 _public prototype_ `virtual void GetMutableColumns(TArrayView<void*> ColumnsData, TConstArrayView<const UScriptStruct*> ColumnTypes) override;`
- L50 _public prototype_ `virtual void SetCurrentRow(RowHandle Row) override;`
- L52 _public function_ `void SetSubRange(int32 InStart, int32 InLength)`
- L53 _public function_ `void ClearSubRange()`
- L54 _public function_ `bool HasSubRange() const`
- L56 _public member_ `const FEnvironment& Environment;`
- L57 _public member_ `const FMassExecutionContext& MassContext;`
- L58 _public member_ `RowHandle CurrentRow = InvalidRowHandle;`
- L59 _public member_ `int32 SubRangeStart = 0;`
- L60 _public member_ `int32 SubRangeLength = -1;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)
- L63 _typedef_ `using QueryContext_ProcessorApi = TQueryContextImpl<false, FProcessorContextEnvironment, FCurrentTableInfoContextCapability, FTableInfoContextCapability, FSingleRowInfoContextCapability, FRowBatchInfoContextCapability, FDynamicColumnInfoContextCapability>;` (scope `UE::Editor::DataStorage::Queries`)
- L70 _typedef_ `using QueryContext_ConstProcessorApi = TQueryContextImpl<true, FConstProcessorContextEnvironment, FCurrentTableInfoContextCapability, FTableInfoContextCapability, FSingleRowInfoContextCapability, FRowBatchInfoContextCapability, FDynamicColumnInfoContextCapability>;` (scope `UE::Editor::DataStorage::Queries`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/QueryContextCapabilities/ContextEnvironment.h` (Private)


#### struct `UE::Editor::DataStorage::Queries::IContextEnvironment`  
`struct IContextEnvironment : IQueryFunctionResponse`  
_L15-21_
- inherits: `IQueryFunctionResponse`
- L17 _public prototype_ `virtual ~IContextEnvironment() = default;`
- L19 _public prototype_ `virtual FEnvironment* GetEnvironment() = 0;`
- L20 _public prototype_ `virtual const FEnvironment* GetEnvironment() const = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/QueryContextCapabilities/EditorDataStorageDynamicColumnInfo.h` (Private)


#### class `UE::Editor::DataStorage::Queries::FDynamicColumnInfoContextCapability`  
`class FDynamicColumnInfoContextCapability : public ImplementsContextCapability<DynamicColumnInfo>`  
_L22-29_
- inherits: `ImplementsContextCapability<DynamicColumnInfo>`
- desc: Implementation for the DynamicColumnInfo context capability. This provides read access to the dynamic columns in order to retrieve information about them from any thread. This class provides an implementation block and is not meant to be directly used but should be inherited from by a class that's compatible with TQueryContextImpl.
- L25 _public prototype_ `static const UScriptStruct* FindDynamicColumnType( const IContextEnvironment& Environment, const UScriptStruct& TemplateType, const FName& Identifier);`
- L27 _public prototype_ `static void ForEachDynamicColumnType( const IContextEnvironment& Environment, const UScriptStruct& TemplateType, TFunctionRef<void(const UScriptStruct& Type)> Callback);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/QueryContextCapabilities/RowBatch.h` (Private)


#### class `UE::Editor::DataStorage::Queries::FRowBatchInfoContextCapability`  
`class FRowBatchInfoContextCapability : public ImplementsContextCapability<RowBatchInfo>`  
_L17-35_
- inherits: `ImplementsContextCapability<RowBatchInfo>`
- L20 _public prototype_ `static uint32 GetBatchRowCount(const IContextEnvironment& Environment);`
- L21 _public prototype_ `static FRowHandleArrayView GetBatchRowHandles(const IContextEnvironment& Environment);`
- L22 _public prototype_ `static bool CurrentBatchTableHasColumns(const IContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L24 _public prototype_ `static bool CurrentBatchTableHasColumns(const FProcessorContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L25 _public prototype_ `static const void* GetColumnBatchAddress(const FProcessorContextEnvironment& Environment, const UScriptStruct* ColumnType);`
- L26 _public prototype_ `static void* GetMutableColumnBatchAddress(FProcessorContextEnvironment& Environment, const UScriptStruct* ColumnType);`
- L28 _public prototype_ `static bool CurrentBatchTableHasColumns(const FConstProcessorContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L29 _public prototype_ `static const void* GetColumnBatchAddress(const FConstProcessorContextEnvironment& Environment, const UScriptStruct* ColumnType);`
- L31 _public prototype_ `static const void* GetColumnBatchAddress(const FDirectContextEnvironment& Environment, const UScriptStruct* ColumnType);`
- L32 _public prototype_ `static void* GetMutableColumnBatchAddress(FDirectContextEnvironment& Environment, const UScriptStruct* ColumnType);`
- L34 _public prototype_ `static const void* GetColumnBatchAddress(const FConstDirectContextEnvironment& Environment, const UScriptStruct* ColumnType);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/QueryContextCapabilities/SingleRow.h` (Private)


#### class `UE::Editor::DataStorage::Queries::FSingleRowInfoContextCapability`  
`class FSingleRowInfoContextCapability : public ImplementsContextCapability<SingleRowInfo>`  
_L22-34_
- inherits: `ImplementsContextCapability<SingleRowInfo>`
- L25 _public prototype_ `static bool CurrentRowHasColumns(const IContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L26 _public prototype_ `static bool CurrentRowHasColumns(const FProcessorContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L27 _public prototype_ `static bool CurrentRowHasColumns(const FConstProcessorContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L30 _public function_ `template<CHasCurrentRow EnvironmentType> static RowHandle GetCurrentRow(const EnvironmentType& Environment)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/QueryContextCapabilities/TableCapabilities.h` (Private)


#### class `UE::Editor::DataStorage::Queries::FTableInfoContextCapability`  
`class FTableInfoContextCapability : public ImplementsContextCapability<TableInfo>`  
_L23-44_
- inherits: `ImplementsContextCapability<TableInfo>`
- L26 _public prototype_ `static bool IsTableValid(const IContextEnvironment& Environment, TableHandle Table);`
- L27 _public prototype_ `static TableHandle FindTable(const IContextEnvironment& Environment, const FName& TableName);`
- L28 _public prototype_ `static TableHandle FindTable(const IContextEnvironment& Environment, RowHandle Row);`
- L29 _public prototype_ `static void ListTables(const IContextEnvironment& Environment, TFunctionRef<void(TableHandle)> Callback);`
- L30 _public prototype_ `static void ListTables(const IContextEnvironment& Environment, ETableType TableType, TFunctionRef<void(TableHandle)> Callback);`
- L31 _public prototype_ `static void ListTableColumns( const IContextEnvironment& Environment, TableHandle Table, TFunctionRef<bool(const UScriptStruct*)> Callback);`
- L34 _public prototype_ `static bool TableHasColumns( const IContextEnvironment& Environment, TableHandle Table, TConstArrayView<const UScriptStruct*> Columns);`
- L36 _public prototype_ `static FTableInfoView GetTableInfo(const IContextEnvironment& Environment, TableHandle Table);`
- L37 _public prototype_ `static void ListTableRows( const IContextEnvironment& Environment, TableHandle Table, TFunctionRef<void(FRowHandleArrayView)> Callback);`
- L40 _public prototype_ `static void ListTableForeignKeyDomains( const IContextEnvironment& Environment, TableHandle Table, bool bIncludeParents, TFunctionRef<void(const FName&)> Callback);`
- L43 _public prototype_ `static const UScriptStruct* GetTagForTable(const IContextEnvironment& Environment, TableHandle Table);`

#### class `UE::Editor::DataStorage::Queries::FCurrentTableInfoContextCapability`  
`class FCurrentTableInfoContextCapability : public ImplementsContextCapability<CurrentTableInfo>`  
_L46-69_
- inherits: `ImplementsContextCapability<CurrentTableInfo>`
- L49 _public prototype_ `static TableHandle GetCurrentTable(const IContextEnvironment& Environment);`
- L50 _public prototype_ `static TableHandle GetCurrentTable(const FProcessorContextEnvironment& Environment);`
- L51 _public prototype_ `static TableHandle GetCurrentTable(const FConstProcessorContextEnvironment& Environment);`
- L53 _public prototype_ `static bool CurrentTableHasColumns( const IContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L55 _public prototype_ `static bool CurrentTableHasColumns( const FProcessorContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L57 _public prototype_ `static bool CurrentTableHasColumns( const FConstProcessorContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns);`
- L61 _public function_ `template<typename EnvironmentContextType> requires (TIsDerivedFrom<EnvironmentContextType, IContextEnvironment>::Value) static const UScriptStruct* GetTagForCurrentTable(const EnvironmentContextType& Environment)`

#### class `UE::Editor::DataStorage::Queries::FTableManagementContextCapability`  
`class FTableManagementContextCapability : public ImplementsContextCapability<TableManagement>`  
_L71-88_
- inherits: `ImplementsContextCapability<TableManagement>`
- L74 _public prototype_ `static TableHandle RegisterTable(IContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns, const FName& TableName);`
- L76 _public prototype_ `static TableHandle RegisterTable(IContextEnvironment& Environment, TConstArrayView<const UScriptStruct*> Columns, const FName& TableName, FTableRegistrationOptions Options);`
- L78 _public prototype_ `static void RegisterTableForeignKey(IContextEnvironment& Environment, TableHandle Table, const FName& Domain, const Queries::TConstQueryFunction<FForeignKey>& KeyConstructor);`
- L80 _public prototype_ `static void RegisterTableForeignKey(IContextEnvironment& Environment, TableHandle Table, const FName& Domain, Queries::TConstQueryFunction<FForeignKey>&& KeyConstructor);`
- L82 _public prototype_ `static FForeignKey BuildForeignKey(const FDirectContextEnvironment& Environment, const FName& Domain, RowHandle Row);`
- L83 _public prototype_ `static FForeignKey BuildForeignKey(const FConstDirectContextEnvironment& Environment, const FName& Domain, RowHandle Row);`
- L86 _private prototype_ `static FForeignKey BuildForeignKey( const FEnvironment* Environment, const UEditorDataStorage* DirectContext, const FName& Domain, RowHandle Row);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace Queries` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/TedsVisibilityQueries.h` (Private)


#### class `UTedsVisibilityFactory`  
`class UTedsVisibilityFactory : public UEditorDataStorageFactory`  
_L14-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Removes all FVisibilityChangeTag at the end of an update cycle.
- L19 _public prototype_ `~UTedsVisibilityFactory() override = default;`
- L21 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/TypedElementExtendedQueryStore.h` (Private)


#### struct `UE::Editor::DataStorage::FExtendedQuery`  
`struct FExtendedQuery`  
_L22-41_
- L24 _public member_ `mutable FMassEntityQuery NativeQuery;` — Used if there's no processor bound. Mutable because NativeQuery does internal state caching.
- L25 _public member_ `FQueryDescription Description;`
- L26 _public member_ `TStrongObjectPtr<UMassProcessor> Processor;`
- L27 _public member_ `FMassEntityQuery* QueryReference;`
- L29 _public function_ `FMassEntityQuery* GetQuery()`

#### class `UE::Editor::DataStorage::FExtendedQueryStore`  
`class FExtendedQueryStore`  
_L46-250_
- desc: Storage and utilities for Typed Element queries after they've been processed by the Data Storage implementation.
- L49 _private typedef_ `using QueryStore = THandleStore<FExtendedQuery>;`
- L51 _public typedef_ `using Handle = QueryStore::Handle;`
- L52 _public typedef_ `using ListAliveEntriesConstCallback = QueryStore::ListAliveEntriesConstCallback;`
- L54 _public prototype_ `explicit FExtendedQueryStore(FDynamicColumnGenerator& InDynamicColumnGenerator);`
- L62 _public prototype_ `Handle RegisterQuery( FQueryDescription Query, FEnvironment& Environment, FMassEntityManager& EntityManager, FMassProcessingPhaseManager& PhaseManager);` — Adds a new query to the store and initializes the query with the provided arguments.
- L68 _public prototype_ `void UnregisterQuery(Handle Query, FMassEntityManager& EntityManager, FMassProcessingPhaseManager& PhaseManager);` — Removes the query at the given handle if still alive and otherwise does nothing.
- L71 _public prototype_ `void Clear(FMassEntityManager& EntityManager, FMassProcessingPhaseManager& PhaseManager);` — Removes all data in the query store.
- L74 _public prototype_ `void RegisterTickGroup(FName GroupName, EQueryTickPhase Phase, FName BeforeGroup, FName AfterGroup, EExecutionMode ExecutionMode);` — Register the defaults for a tick group. These will be applied on top of any settings provided with a query registration.
- L77 _public prototype_ `void UnregisterTickGroup(FName GroupName, EQueryTickPhase Phase);` — Removes a previously registered set of tick group defaults.
- L85 _public prototype_ `FExtendedQuery* Get(Handle Entry);` — Retrieves the query at the provided handle, if still alive or otherwise returns a nullptr.
- L87 _public prototype_ `FExtendedQuery* GetMutable(Handle Entry);` — Retrieves the query at the provided handle, if still alive or otherwise returns a nullptr.
- L89 _public prototype_ `const FExtendedQuery* Get(Handle Entry) const;` — Retrieves the query at the provided handle, if still alive or otherwise returns a nullptr.
- L92 _public prototype_ `FExtendedQuery& GetChecked(Handle Entry);` — Retrieves the query at the provided handle, if still alive. It's up to the caller to guarantee the query is still alive.
- L94 _public prototype_ `FExtendedQuery& GetMutableChecked(Handle Entry);` — Retrieves the query at the provided handle, if still alive. It's up to the caller to guarantee the query is still alive.
- L96 _public prototype_ `const FExtendedQuery& GetChecked(Handle Entry) const;` — Retrieves the query at the provided handle, if still alive. It's up to the caller to guarantee the query is still alive.
- L99 _public prototype_ `const FQueryDescription& GetQueryDescription(Handle Query) const;` — Gets the original description used to create an extended query or an empty default if the provided query isn't alive.
- L105 _public prototype_ `uint64 CalculateQueryTablesTopologyHash(Handle Query) const;` — Calculates a hash based on the topology revision id of the tables associated with the provided query. If this value changes it indicates that one or more tables has new rows added, had rows removed and/or rows have been reordered.
- L108 _public prototype_ `bool IsAlive(Handle Entry) const;` — Checks to see if a query is still available or has been removed.
- L111 _public prototype_ `void ListAliveEntries(const ListAliveEntriesConstCallback& Callback) const;` — Calls the provided callback for each query that's available.
- L119 _public prototype_ `void UpdateActivatableQueries();` — Update the active activatable queries. In practice this means decrementing any active queries that automatically decrement.
- L121 _public prototype_ `void ActivateQueries(FName ActivationName);` — Triggers a query to run for a single update cycle.
- L128 _public prototype_ `FQueryResult RunQuery(FMassEntityManager& EntityManager, Handle Query);`
- L129 _public prototype_ `FQueryResult RunQuery( FMassEntityManager& EntityManager, FEnvironment& Environment, Handle Query, EDirectQueryExecutionFlags DirectExecutionFlags, DirectQueryCallbackRef Callback);`
- L135 _public prototype_ `FQueryResult RunQuery( FMassEntityManager& EntityManager, FEnvironment& Environment, Handle Query, ERunQueryFlags Flags, const Queries::TQueryFunction<void>& Callback);`
- L141 _public prototype_ `FQueryResult RunQuery( FMassEntityManager& EntityManager, FEnvironment& Environment, Handle Query, ERunQueryFlags Flags, const Queries::TConstQueryFunction<void>& Callback) const;`
- L147 _public prototype_ `FQueryResult RunQuery( FMassEntityManager& EntityManager, FEnvironment& Environment, FMassExecutionContext& ParentContext, Handle Query, SubqueryCallbackRef Callback);`
- L153 _public prototype_ `FQueryResult RunQuery( FMassEntityManager& EntityManager, FEnvironment& Environment, FMassExecutionContext& ParentContext, Handle Query, RowHandle Row, SubqueryCallbackRef Callback);`
- L160 _public prototype_ `void RunPhasePreambleQueries( FMassEntityManager& EntityManager, FEnvironment& Environment, EQueryTickPhase Phase, float DeltaTime);`
- L165 _public prototype_ `void RunPhasePostambleQueries( FMassEntityManager& EntityManager, FEnvironment& Environment, EQueryTickPhase Phase, float DeltaTime);`
- L171 _public prototype_ `void NotifyNewDynamicColumn(const FDynamicColumnGeneratorInfo& GeneratedColumnInfo);`
- L173 _public prototype_ `void DebugPrintQueryCallbacks(FOutputDevice& Output) const;`
- L176 _private typedef_ `using QueryTickPhaseType = std::underlying_type_t<EQueryTickPhase>;`
- L177 _private member_ `static constexpr QueryTickPhaseType MaxTickPhase = static_cast<QueryTickPhaseType>(EQueryTickPhase::Max);`
- L184 _private function_ `friend inline uint32 GetTypeHash(const FTickGroupId& Id)`
- L185 _private function_ `friend inline bool operator==(const FTickGroupId& Lhs, const FTickGroupId& Rhs)`
- L186 _private function_ `friend inline bool operator!=(const FTickGroupId& Lhs, const FTickGroupId& Rhs)`
- L197 _private prototype_ `template<typename CallbackReference, typename ExecutionFlagsType> FQueryResult RunQueryCallbackCommon( FMassEntityManager& EntityManager, FEnvironment& Environment, FMassExecutionContext* ParentContext, Handle Query, ExecutionFlagsType ExecutionFlags, CallbackReference Callback);`
- L204 _private prototype_ `FQueryResult RunQueryCallbackCommon( FMassEntityManager& EntityManager, FEnvironment& Environment, FMassExecutionContext* ParentContext, Handle Query, ERunQueryFlags ExecutionFlags, const Queries::TConstQueryFunction<void>& Callback) const;`
- L212 _private prototype_ `FMassEntityQuery& SetupNativeQuery(FQueryDescription& Query, FExtendedQuery& StoredQuery, FEnvironment& Environment);`
- L213 _private prototype_ `bool SetupDynamicColumns(FQueryDescription& Query, FEnvironment& Environment);`
- L214 _private prototype_ `bool SetupHierarchyDependencies(FQueryDescription& Query, FEnvironment& Environment);`
- L215 _private prototype_ `bool SetupSelectedColumns(FQueryDescription& Query, FMassEntityQuery& NativeQuery);`
- L216 _private prototype_ `bool SetupConditions(FQueryDescription& Query, FEnvironment& Environment, FMassEntityQuery& NativeQuery);`
- L217 _private prototype_ `bool SetupChunkFilters(Handle QueryHandle, FQueryDescription& Query, FEnvironment& Environment, FMassEntityQuery& NativeQuery);`
- L218 _private prototype_ `bool SetupDependencies(FQueryDescription& Query, FMassEntityQuery& NativeQuery);`
- L219 _private prototype_ `bool SetupTickGroupDefaults(FQueryDescription& Query);`
- L220 _private prototype_ `bool SetupProcessors(Handle QueryHandle, FExtendedQuery& StoredQuery, FEnvironment& Environment, FMassEntityManager& EntityManager, FMassProcessingPhaseManager& PhaseManager);`
- L222 _private prototype_ `bool SetupActivatable(Handle QueryHandle, FExtendedQuery& StoredQuery);`
- L224 _private prototype_ `EMassFragmentAccess ConvertToNativeAccessType(EQueryAccessType AccessType);`
- L225 _private prototype_ `EMassFragmentPresence ConvertToNativePresenceType(EQueryAccessType AccessType);`
- L226 _private prototype_ `EMassFragmentPresence ConvertToNativePresenceType(FQueryDescription::EOperatorType OperatorType);`
- L228 _private prototype_ `void RegisterPreambleQuery(EQueryTickPhase Phase, Handle Query);`
- L229 _private prototype_ `void RegisterPostambleQuery(EQueryTickPhase Phase, Handle Query);`
- L230 _private prototype_ `void UnregisterPreambleQuery(EQueryTickPhase Phase, Handle Query);`
- L231 _private prototype_ `void UnregisterPostambleQuery(EQueryTickPhase Phase, Handle Query);`
- L232 _private prototype_ `void RunPhasePreOrPostAmbleQueries(FMassEntityManager& EntityManager, FEnvironment& Environment, EQueryTickPhase Phase, float DeltaTime, TArray<Handle>& QueryHandles);`
- L235 _private prototype_ `void UnregisterQueryData(Handle Query, FExtendedQuery& QueryData, FMassEntityManager& EntityManager, FMassProcessingPhaseManager& PhaseManager);`
- L237 _private prototype_ `bool CheckCompatibility(const FQueryDescription& QueryDescription, const Queries::TQueryFunction<void> QueryCallback) const;`
- L238 _private prototype_ `bool CheckCompatibility(const FQueryDescription& QueryDescription, const Queries::TConstQueryFunction<void> QueryCallback) const;`
- L240 _private member_ `static const FQueryDescription EmptyDescription;`
- L242 _private member_ `QueryStore Queries;`
- L243 _private member_ `TMultiMap<FName, Handle> ActivatableMapping;`
- L244 _private member_ `TMap<FTickGroupId, FTickGroupDescription> TickGroupDescriptions;`
- L245 _private member_ `TArray<Handle> PhasePreparationQueries[MaxTickPhase];`
- L246 _private member_ `TArray<Handle> PhaseFinalizationQueries[MaxTickPhase];`
- L247 _private member_ `TArray<Handle> PendingActivatables;`
- L248 _private member_ `TArray<Handle> ActiveActivatables;`
- L249 _private member_ `FDynamicColumnGenerator* DynamicColumnGenerator;`

#### struct `UE::Editor::DataStorage::FExtendedQueryStore::FTickGroupId`  
`struct FTickGroupId`  
_L179-187_
- L181 _public member_ `FName Name;`
- L182 _public member_ `EQueryTickPhase Phase;`

#### struct `UE::Editor::DataStorage::FExtendedQueryStore::FTickGroupDescription`  
`struct FTickGroupDescription`  
_L189-194_
- L191 _public member_ `TArray<FName> BeforeGroups;`
- L192 _public member_ `TArray<FName> AfterGroups;`
- L193 _public member_ `EExecutionMode ExecutionMode = EExecutionMode::Default;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/TypedElementHierarchyQueries.h` (Private)


#### class `UTypedElementHiearchyQueriesFactory`  
`class UTypedElementHiearchyQueriesFactory : public UEditorDataStorageFactory`  
_L14-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Calls to queries for general hierarchy management.
- L19 _public prototype_ `~UTypedElementHiearchyQueriesFactory() override = default;`
- L21 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Queries/TypedElementMiscQueries.h` (Private)


#### class `UTypedElementRemoveSyncToWorldTagFactory`  
`class UTypedElementRemoveSyncToWorldTagFactory : public UEditorDataStorageFactory`  
_L14-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Removes all FTypedElementSyncBackToWorldTags at the end of an update cycle.
- L19 _public prototype_ `~UTypedElementRemoveSyncToWorldTagFactory() override = default;`
- L21 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Relations/EditorDataStorageRelationColumns.h` (Private)


#### struct `FTedsRelationSubjectChanged_Template`  
`struct FTedsRelationSubjectChanged_Template : public FEditorDataStorageTag`  
_L17-20_
- reflection: `USTRUCT(meta = (DisplayName = "Relation Subject Changed", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`
- desc: Template tag column stamped on a Subject row when a relation of a specific type is created or destroyed. Removed at FrameEnd. Use as a per-frame change notification in queries/observers. Each relation type generates its own unique instance via GenerateDynamicColumn.

#### struct `FTedsRelationObjectChanged_Template`  
`struct FTedsRelationObjectChanged_Template : public FEditorDataStorageTag`  
_L28-31_
- reflection: `USTRUCT(meta = (DisplayName = "Relation Object Changed", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`
- desc: Template tag column stamped on an Object row when a relation of a specific type is created or destroyed. Removed at FrameEnd. Use as a per-frame change notification in queries/observers. Each relation type generates its own unique instance via GenerateDynamicColumn.

#### struct `FWalkOnlyHierarchyMetadata`  
`struct FWalkOnlyHierarchyMetadata final : public FEditorDataStorageColumn`  
_L35-44_
- reflection: `USTRUCT(meta = (DisplayName = "Walk-Only Hierarchy Metadata"))`
- inherits: `FEditorDataStorageColumn`
- desc: Hierarchy metadata column for WalkOnly relations. Added to each relation row.
- L40 _public member_ `int32 Depth = 0;` — `UPROPERTY(meta = (Searchable, Sortable))`
- L43 _public member_ `FTedsRowHandle Root;` — `UPROPERTY(meta = (Searchable))`

#### struct `FIntervalEncodedHierarchyMetadata`  
`struct FIntervalEncodedHierarchyMetadata final : public FEditorDataStorageColumn`  
_L48-66_
- reflection: `USTRUCT(meta = (DisplayName = "Interval-Encoded Hierarchy Metadata"))`
- inherits: `FEditorDataStorageColumn`
- desc: Hierarchy metadata column for IntervalEncoded relations. Added to each relation row.
- L53 _public member_ `int32 Depth = 0;` — `UPROPERTY(meta = (Searchable, Sortable))`
- L56 _public member_ `uint32 IntervalVersion = 0;` — `UPROPERTY(meta = (Searchable))`
- L59 _public member_ `int64 IntervalLeft = 0;` — `UPROPERTY(meta = (Sortable))`
- L62 _public member_ `int64 IntervalRight = 0;` — `UPROPERTY(meta = (Sortable))`
- L65 _public member_ `FTedsRowHandle Root;` — `UPROPERTY(meta = (Searchable))`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Relations/EditorDataStorageRelationsImplementation.h` (Private)


#### class `UE::Editor::DataStorage::FTedsRelationAdapter`  
`class FTedsRelationAdapter final`  
_L21-67_
- desc: Maps TEDS relation types to their underlying Mass representation.
- L24 _public prototype_ `FTedsRelationAdapter() = default;`
- L25 _public prototype_ `~FTedsRelationAdapter() = default;`
- L28 _public prototype_ `FTedsRelationAdapter(const FTedsRelationAdapter&) = delete;` — Non-copyable
- L29 _public prototype_ `FTedsRelationAdapter& operator=(const FTedsRelationAdapter&) = delete;`
- L32 _public prototype_ `RelationTypeHandle RegisterRelationType( FMassEntityManager& EntityManager, FTableManager& TableManager, const FRelationRegistrationParams& Params);` — Register a new relation type. Returns the handle, or InvalidRelationTypeHandle on failure.
- L38 _public prototype_ `RelationTypeHandle FindRelationType(const FName& Name) const;` — Find a relation type by name. Returns InvalidRelationTypeHandle if not found.
- L40 _public prototype_ `bool IsValidRelationType(RelationTypeHandle Type) const;`
- L41 _public prototype_ `const FTedsRelationTraits* GetTraits(RelationTypeHandle Type) const;`
- L42 _public prototype_ `UE::Mass::FTypeHandle GetMassHandle(RelationTypeHandle TedsHandle) const;`
- L43 _public prototype_ `FName GetTypeName(RelationTypeHandle Type) const;`
- L44 _public prototype_ `bool IsHierarchical(RelationTypeHandle Type) const;`
- L45 _public prototype_ `const UScriptStruct* GetRelationTag(RelationTypeHandle Type) const;`
- L46 _public prototype_ `const UScriptStruct* GetSubjectChangedColumn(RelationTypeHandle Type) const;`
- L47 _public prototype_ `const UScriptStruct* GetObjectChangedColumn(RelationTypeHandle Type) const;`
- L48 _public prototype_ `void SetChangedColumns(RelationTypeHandle Type, const UScriptStruct* SubjectChanged, const UScriptStruct* ObjectChanged);`
- L49 _public prototype_ `bool HasMassRelationData(RelationTypeHandle Type) const;`
- L50 _public prototype_ `void SetHasMassRelationData(RelationTypeHandle Type);`
- L51 _public prototype_ `void ListTypes(TFunctionRef<void(RelationTypeHandle, const FName&)> Callback) const;`
- L65 _private member_ `TArray<FRegisteredType> RegisteredTypes;`
- L66 _private member_ `TMap<FName, RelationTypeHandle> NameToHandle;`

#### struct `UE::Editor::DataStorage::FTedsRelationAdapter::FRegisteredType`  
`struct FRegisteredType`  
_L54-63_
- L56 _public member_ `FName Name;`
- L57 _public member_ `FTedsRelationTraits TedsTraits;`
- L58 _public member_ `UE::Mass::FTypeHandle MassHandle;`
- L59 _public member_ `TStrongObjectPtr<UScriptStruct> DynamicRelationTag;`
- L60 _public member_ `bool bHasMassRelationData = false;`
- L61 _public member_ `const UScriptStruct* SubjectChangedColumn = nullptr;`
- L62 _public member_ `const UScriptStruct* ObjectChangedColumn = nullptr;`

#### class `UE::Editor::DataStorage::FTedsHierarchicalRelationManager`  
`class FTedsHierarchicalRelationManager final`  
_L70-206_
- desc: Manages hierarchy metadata (depth, root, interval encoding) for hierarchical relation types.
- L73 _public prototype_ `FTedsHierarchicalRelationManager() = default;`
- L76 _public prototype_ `void InitializeHierarchyMetadata( ICoreProvider& Provider, RelationTypeHandle Type, RowHandle RelationRow, RowHandle Subject, RowHandle Object);` — Initialize hierarchy metadata for a newly created relation row.
- L84 _public prototype_ `void RemoveHierarchyMetadata(RelationTypeHandle Type, RowHandle Subject);` — Clean up hierarchy metadata when a relation is destroyed.
- L87 _public prototype_ `bool IsDescendantOf( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Descendant, RowHandle Ancestor, bool bIncludeSelf = false) const;` — Check if Descendant is anywhere below Ancestor in the hierarchy.
- L95 _public prototype_ `bool IsDescendantOf( FMassEntityManager& EntityManager, const FTedsRelationAdapter& RelationAdapter, RelationTypeHandle Type, RowHandle Descendant, RowHandle Ancestor, bool bIncludeSelf = false) const;` — IsDescendantOf overload for use inside query contexts (reads Mass fragments directly).
- L104 _public prototype_ `RowHandle GetHierarchyRoot( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row) const;` — Get the root of the hierarchy containing the given row.
- L110 _public prototype_ `int32 GetHierarchyDepth( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row) const;` — Get the depth of a row in its hierarchy. Roots are depth 0.
- L116 _public prototype_ `int32 ComputeDescendantCount( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row) const;` — Count descendants by walking the tree. Not cached.
- L122 _public prototype_ `void GetDescendants( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row, TArray<RowHandle>& OutDescendants) const;` — Get all descendants of a row.
- L129 _public prototype_ `void GetAncestors( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row, TArray<RowHandle>& OutAncestors) const;` — Get all ancestors of a row, ordered parent to root.
- L136 _public prototype_ `void TraverseDescendants( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row, ICoreProvider::FRelationTraversalCallback Callback, ICoreProvider::ETraversalOrder Order = ICoreProvider::ETraversalOrder::PreOrder, int32 MaxDepth = TNumericLimits<int32>::Max()) const;` — Traverse all descendants depth-first.
- L145 _public prototype_ `void MarkForRebalance(RelationTypeHandle Type);` — Schedule interval rebalancing for this type at the next ProcessRebalancing call.
- L148 _public prototype_ `void ProcessRebalancing(ICoreProvider& Provider);` — Rebalance intervals for all marked types. Called at frame end.
- L151 _public prototype_ `void RegisterHierarchyMode(RelationTypeHandle Type, EHierarchyMode Mode, int64 InitialGap);` — Register the hierarchy mode and initial gap for a relation type.
- L154 _private prototype_ `RowHandle FindRelationRow(RelationTypeHandle Type, RowHandle Subject) const;`
- L157 _private prototype_ `int32 ReadDepth(const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle RelationRow) const;` — Metadata accessors that dispatch based on the hierarchy mode (WalkOnly vs IntervalEncoded).
- L158 _private prototype_ `RowHandle ReadRoot(const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle RelationRow) const;`
- L159 _private prototype_ `const FIntervalEncodedHierarchyMetadata* ReadIntervalMetadata(const ICoreProvider& Provider, RowHandle RelationRow) const;`
- L160 _private prototype_ `FIntervalEncodedHierarchyMetadata* ReadIntervalMetadataMutable(ICoreProvider& Provider, RowHandle RelationRow) const;`
- L161 _private prototype_ `FWalkOnlyHierarchyMetadata* ReadWalkOnlyMetadataMutable(ICoreProvider& Provider, RowHandle RelationRow) const;`
- L163 _private prototype_ `void TraversePreOrder( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle StartRow, int32 MaxDepth, ICoreProvider::FRelationTraversalCallback& Callback) const;`
- L170 _private prototype_ `void TraversePostOrder( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle StartRow, int32 MaxDepth, ICoreProvider::FRelationTraversalCallback& Callback) const;`
- L177 _private prototype_ `void GatherDescendants( const ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row, TArray<RowHandle>& OutDescendants) const;`
- L184 _private prototype_ `int64 AssignIntervals( ICoreProvider& Provider, RelationTypeHandle Type, RowHandle Row, int64 StartInterval, int64 Gap);` — Assign interval [Left, Right] values to all nodes in a subtree via DFS. Returns the next available interval.
- L192 _private member_ `TMap<RelationTypeHandle, TMap<RowHandle, RowHandle>> SubjectToRelationRow;` — (RelationType, SubjectRow) -> RelationRow lookup for hierarchy metadata.
- L199 _private member_ `TMap<RelationTypeHandle, FHierarchySettings> TypeSettings;`
- L202 _private member_ `TMap<RelationTypeHandle, uint32> TypeVersions;` — Per-type interval version counters. Starts at 1; 0 means "never stamped" (always falls back to walk).
- L205 _private member_ `TSet<RelationTypeHandle> TypesNeedingRebalance;` — Types queued for interval rebalancing at next ProcessRebalancing call.

#### struct `UE::Editor::DataStorage::FTedsHierarchicalRelationManager::FHierarchySettings`  
`struct FHierarchySettings`  
_L194-198_
- L196 _public member_ `EHierarchyMode Mode = EHierarchyMode::Disabled;`
- L197 _public member_ `int64 InitialGap = 1000;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Scope/TypedElementScopeSystem.h` (Private)


#### class `UE::Editor::DataStorage::FScopeSystem`  
`class FScopeSystem`  
_L16-42_
- L19 _public prototype_ `explicit FScopeSystem(ICoreProvider& InDataStorage);`
- L21 _public prototype_ `RowHandle AddScopeRow();`
- L22 _public prototype_ `RowHandle AddScopeRow(FStringView Label);`
- L23 _public prototype_ `RowHandle AddScopeRow(FStringView Label, RowHandle Parent);`
- L24 _public prototype_ `void RemoveScopeRow(RowHandle Row);`
- L25 _public prototype_ `void SetParentScope(RowHandle Child, RowHandle Parent);`
- L26 _public prototype_ `RowHandle GetParentScope(RowHandle Row);`
- L27 _public prototype_ `const void* GetScopeDataRaw(RowHandle Row, const UScriptStruct* ColumnType);`
- L28 _public prototype_ `Scope::FScopeDataVersion GetScopeDataVersion(RowHandle Row, const UScriptStruct* ColumnType);`
- L29 _public prototype_ `Scope::FScopeDataVersion SetScopeData(RowHandle Row, const UScriptStruct* ColumnType, ColumnCreationCallbackRef Initializer, ColumnCopyOrMoveCallback Relocator);`
- L31 _public prototype_ `bool RemoveScopeData(RowHandle Row, const UScriptStruct* ColumnType);`
- L32 _public prototype_ `TArray<const UScriptStruct*> GetAllVisibleScopeColumns(RowHandle Row);`
- L33 _public prototype_ `FHierarchyHandle GetScopeHierarchy();`
- L34 _public prototype_ `RowHandle GetRootScope() const;`
- L35 _public prototype_ `void InitRootScope();`
- L38 _private prototype_ `TableHandle GetOrCreateScopeTable();`
- L40 _private member_ `ICoreProvider& DataStorage;`
- L41 _private member_ `RowHandle RootScopeRow = InvalidRowHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TableManager.h` (Private)


#### struct `FEditorDataStorageTableDynamicTag`  
`struct FEditorDataStorageTableDynamicTag final : public FEditorDataStorageTag`  
_L27-30_
- reflection: `USTRUCT(meta = (DisplayName = "Table", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`
- desc: Base type for the tag that automatically gets added to any table to identify it.

#### class `UE::Editor::DataStorage::FTableManager`  
`class FTableManager final`  
_L38-104_
- L41 _public prototype_ `FTableManager(FMassEntityManager& InMassEntityManager, FDynamicColumnGenerator& InDynamicColumns);`
- L42 _public prototype_ `~FTableManager();`
- L44 _public prototype_ `void Clear();`
- L46 _public prototype_ `TableHandle Register(TConstArrayView<const UScriptStruct*> ColumnList, const FName& TableName);`
- L47 _public prototype_ `TableHandle Register( TConstArrayView<const UScriptStruct*> ColumnList, const FName& TableName, FTableRegistrationOptions Options);`
- L50 _public prototype_ `bool IsTableValid(TableHandle Table) const;`
- L52 _public prototype_ `TableHandle Find(const FName& TableName) const;`
- L53 _public prototype_ `TableHandle Find(const FMassArchetypeHandle& Archetype) const;`
- L54 _public prototype_ `TableHandle Find(RowHandle Row) const;`
- L56 _public prototype_ `const UScriptStruct* GetTagForTable(TableHandle Table) const;`
- L58 _public prototype_ `void List(TFunctionRef<void(TableHandle)> Callback) const;`
- L59 _public prototype_ `void List(ETableType TableType, TFunctionRef<void(TableHandle)> Callback) const;`
- L61 _public prototype_ `void ListColumns(TableHandle Table, TFunctionRef<bool(const UScriptStruct*)> Callback) const;`
- L62 _public prototype_ `bool HasColumns(TableHandle Table, TConstArrayView<const UScriptStruct*> Columns) const;`
- L64 _public prototype_ `FTableInfoView GetInfo(TableHandle Table) const;`
- L65 _public prototype_ `void ListRows(TableHandle Table, TFunctionRef<void(FRowHandleArrayView)> Callback) const;`
- L67 _public prototype_ `void RegisterForeignKey(TableHandle Table, const FName& Domain, Queries::TConstQueryFunction<FForeignKey> KeyConstructor);`
- L68 _public prototype_ `Queries::EFlowControl BuildForeignKeys(TArrayView<FForeignKey> Results, const FName& Domain, Queries::TForwardingConstQueryContext<Queries::CurrentTableInfo> Contract, Queries::IQueryFunctionResponse& Response) const;`
- L70 _public prototype_ `void ListForeignKeyDomains(TableHandle Table, bool bIncludeParents, TFunctionRef<void(const FName&)> Callback) const;`
- L72 _public prototype_ `FMassArchetypeHandle GetArchetype(TableHandle Table) const;`
- L89 _private prototype_ `void OnNewArchetype(const FMassArchetypeHandle& Archetype);`
- L91 _private prototype_ `int32 ConvertTableHandleToIndex(const TableHandle InTableHandle) const;`
- L92 _private prototype_ `int32 GetTableChunkSize(const FName& TableName) const;`
- L93 _private prototype_ `void RemoveTableTag(FMassArchetypeCompositionDescriptor& Composition);`
- L95 _private member_ `TArray<FTableInfo> Tables;` — Contains tables and variants.
- L96 _private member_ `TMap<FName, TableHandle> NameLookup;` — Only includes tables.
- L97 _private member_ `TMap<FMassArchetypeHandle, TableHandle> MassLookup;` — Includes tables and variants.
- L99 _private member_ `FDelegateHandle OnNewArchetypeEventHandle;`
- L100 _private member_ `FMassEntityManager& MassEntityManager;`
- L101 _private member_ `FDynamicColumnGenerator& DynamicColumns;`
- L103 _private member_ `bool bRegisteringNewTable = false;`

#### struct `UE::Editor::DataStorage::FTableManager::FTableInfo`  
`struct FTableInfo`  
_L74-87_
- L76 _public typedef_ `using ForeignKeyMap = TMap<FName, Queries::TConstQueryFunction<FForeignKey>>;`
- L77 _public member_ `ForeignKeyMap ForeignKeyConstructors;`
- L78 _public member_ `TArray<TableHandle> Variants;`
- L79 _public member_ `TArray<TableHandle> Derivatives;`
- L80 _public member_ `FMassArchetypeHandle Archetype;`
- L81 _public member_ `FName Name;`
- L82 _public member_ `ETableType Type;`
- L83 _public member_ `TNonNullPtr<const UScriptStruct> Tag;`
- L86 _public member_ `TableHandle Parent;` — If this is a dynamically generated variant then the Parent represents the table used as the basis for the variant. If this is a derived copy then the Parent represents the table that was passed in as the template for this table.

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Editor` (scope `UE`)
- L32 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L34 _typedef_ `using FTableDynamicTag = FEditorDataStorageTableDynamicTag;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDataStorageProfilingMacros.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define ENABLE_TEDS_PROFILING_MACROS 1`
- L13 _macro_ `#define TEDS_EVENT_PREFIX TEXT("[TEDS] ")`
- L15 _macro_ `#define TEDS_EVENT_SCOPE(StrLiteral) TRACE_CPUPROFILER_EVENT_SCOPE_STR(TEDS_EVENT_PREFIX StrLiteral)` — Scoped event which prefixes the string literal with "[TEDS] " for consistent filtering
- L19 _macro_ `#define TEDS_EVENT_SCOPE(StrLiteral) do {} while(false)`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDataStorageSharedColumn.h` (Private)


#### struct `FTedsSharedColumn`  
`struct FTedsSharedColumn`  
_L13-16_
- reflection: `USTRUCT()`
- desc: Shared Columns are virtual columns shared by many rows

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabase.h` (Private)


#### class `UEditorDataStorage`  
`class UEditorDataStorage final : public UObject , public ImplementationForwarder`  
_L40-420_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,ImplementationForwarder`
- L67 _public typedef_ `using FactoryIterator = TFactoryIterator<UEditorDataStorageFactory, UEditorDataStorage>;`
- L68 _public typedef_ `using FactoryConstIterator = TFactoryIterator<const UEditorDataStorageFactory, const UEditorDataStorage>;`
- L73 _public prototype_ `void Initialize();`
- L74 _public prototype_ `void PostInitialize();`
- L76 _public prototype_ `void SetFactories(TConstArrayView<UClass*> InFactories);`
- L77 _public prototype_ `void ResetFactories();`
- L80 _public prototype_ `FactoryIterator CreateFactoryIterator();` — An iterator which allows traversal of factory instances. Ordered lowest->highest of GetOrder()
- L82 _public prototype_ `FactoryConstIterator CreateFactoryIterator() const;` — An iterator which allows traversal of factory instances. Ordered lowest->highest of GetOrder()
- L85 _public prototype_ `virtual const UEditorDataStorageFactory* FindFactory(const UClass* FactoryType) const override;` — Returns factory instance given the type of factory
- L87 _public prototype_ `virtual UEditorDataStorageFactory* FindFactory(const UClass* FactoryType) override;`
- L89 _public prototype_ `void Deinitialize();`
- L92 _public prototype_ `void OnPreMassTick(float DeltaTime);` — Triggered at the start of the underlying Mass' tick cycle.
- L94 _public prototype_ `void OnPostMassTick(float DeltaTime);` — Triggered just before underlying Mass processing completes it's tick cycle.
- L96 _public prototype_ `TSharedPtr<FMassEntityManager> GetActiveMutableEditorEntityManager();`
- L97 _public prototype_ `TSharedPtr<const FMassEntityManager> GetActiveEditorEntityManager() const;`
- L100 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle ReserveRow() override;`
- L101 _public prototype_ `virtual void BatchReserveRows(int32 Count, TFunctionRef<void(UE::Editor::DataStorage::RowHandle)> ReservationCallback) override;`
- L102 _public prototype_ `virtual void BatchReserveRows(TArrayView<UE::Editor::DataStorage::RowHandle> ReservedRows) override;`
- L103 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle AddRow(UE::Editor::DataStorage::TableHandle Table, UE::Editor::DataStorage::RowCreationCallbackRef OnCreated) override;`
- L105 _public prototype_ `UE::Editor::DataStorage::RowHandle AddRow(UE::Editor::DataStorage::TableHandle Table) override;`
- L106 _public prototype_ `virtual bool AddRow(UE::Editor::DataStorage::RowHandle ReservedRow, UE::Editor::DataStorage::TableHandle Table) override;`
- L107 _public prototype_ `virtual bool AddRow(UE::Editor::DataStorage::RowHandle ReservedRow, UE::Editor::DataStorage::TableHandle Table, UE::Editor::DataStorage::RowCreationCallbackRef OnCreated) override;`
- L109 _public prototype_ `virtual bool BatchAddRow(UE::Editor::DataStorage::TableHandle Table, int32 Count, UE::Editor::DataStorage::RowCreationCallbackRef OnCreated) override;`
- L111 _public prototype_ `virtual bool BatchAddRow(UE::Editor::DataStorage::TableHandle Table, TConstArrayView<UE::Editor::DataStorage::RowHandle> ReservedHandles, UE::Editor::DataStorage::RowCreationCallbackRef OnCreated) override;`
- L113 _public prototype_ `virtual void RemoveRow(UE::Editor::DataStorage::RowHandle Row) override;`
- L114 _public prototype_ `virtual void BatchRemoveRows(TConstArrayView<UE::Editor::DataStorage::RowHandle> Rows) override;`
- L115 _public prototype_ `virtual void RemoveAllRowsWithColumns(TConstArrayView<const UScriptStruct*> Columns) override;`
- L116 _public prototype_ `virtual bool IsRowAvailable(UE::Editor::DataStorage::RowHandle Row) const override;`
- L117 _public prototype_ `virtual bool IsRowAssigned(UE::Editor::DataStorage::RowHandle Row) const override;`
- L119 _public prototype_ `bool IsRowAvailableUnsafe(UE::Editor::DataStorage::RowHandle Row) const;` — Same as IsRowAvailable, but doesn't check if the data storage has been initialized.
- L121 _public prototype_ `bool IsRowAssignedUnsafe(UE::Editor::DataStorage::RowHandle Row) const;` — Same as IsRowAssigned, but doesn't check if the data storage has been initialized.
- L122 _public prototype_ `virtual void FilterRowsBy(UE::Editor::DataStorage::FRowHandleArray& Result, UE::Editor::DataStorage::FRowHandleArrayView Input, EFilterOptions Options, UE::Editor::DataStorage::Queries::TConstQueryFunction<bool>& Filter) const override;`
- L125 _public prototype_ `virtual void AddColumn(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) override;`
- L126 _public prototype_ `virtual void AddColumn(UE::Editor::DataStorage::RowHandle Row, const UE::Editor::DataStorage::FValueTag& Tag, const FName& InValue) override;`
- L127 _public prototype_ `virtual void AddColumnData(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType, const UE::Editor::DataStorage::ColumnCreationCallbackRef Initializer, UE::Editor::DataStorage::ColumnCopyOrMoveCallback Relocator) override;`
- L130 _public prototype_ `virtual void RemoveColumn(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) override;`
- L131 _public prototype_ `virtual void RemoveColumn(UE::Editor::DataStorage::RowHandle Row, const UE::Editor::DataStorage::FValueTag& Tag) override;`
- L132 _public prototype_ `virtual void* GetColumnData(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) override;`
- L133 _public prototype_ `virtual const void* GetColumnData(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) const override;`
- L134 _public prototype_ `virtual void AddColumns(UE::Editor::DataStorage::RowHandle Row, TConstArrayView<const UScriptStruct*> Columns) override;`
- L135 _public prototype_ `virtual void RemoveColumns(UE::Editor::DataStorage::RowHandle Row, TConstArrayView<const UScriptStruct*> Columns) override;`
- L136 _public prototype_ `virtual void AddRemoveColumns(UE::Editor::DataStorage::RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnsToAdd, TConstArrayView<const UScriptStruct*> ColumnsToRemove) override;`
- L138 _public prototype_ `virtual void BatchAddRemoveColumns(TConstArrayView<UE::Editor::DataStorage::RowHandle> Rows,TConstArrayView<const UScriptStruct*> ColumnsToAdd, TConstArrayView<const UScriptStruct*> ColumnsToRemove) override;`
- L140 _public prototype_ `virtual bool HasColumns(UE::Editor::DataStorage::RowHandle Row, TConstArrayView<const UScriptStruct*> ColumnTypes) const override;`
- L141 _public prototype_ `virtual bool HasColumns(UE::Editor::DataStorage::RowHandle Row, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes) const override;`
- L142 _public prototype_ `virtual void ListColumns(UE::Editor::DataStorage::RowHandle Row, UE::Editor::DataStorage::ColumnListCallbackRef Callback) const override;`
- L143 _public prototype_ `virtual void ListColumns(UE::Editor::DataStorage::RowHandle Row, UE::Editor::DataStorage::ColumnListWithDataCallbackRef Callback) override;`
- L144 _public prototype_ `virtual bool MatchesColumns(UE::Editor::DataStorage::RowHandle Row, const UE::Editor::DataStorage::Queries::FConditions& Conditions) const override;`
- L146 _public prototype_ `virtual const UScriptStruct* GenerateDynamicColumn(const UE::Editor::DataStorage::FDynamicColumnDescription& Description) override;`
- L147 _public prototype_ `virtual void ForEachDynamicColumn(const UScriptStruct& Template, TFunctionRef<void(const UScriptStruct& Type)> Callback) const override;`
- L149 _public prototype_ `virtual UE::Editor::DataStorage::FHierarchyHandle RegisterHierarchy(const UE::Editor::DataStorage::FHierarchyRegistrationParams& Params) override;`
- L150 _public prototype_ `virtual UE::Editor::DataStorage::FHierarchyHandle FindHierarchyByName(const FName& Name) const override;`
- L151 _public prototype_ `virtual bool IsValidHierarchyHandle(UE::Editor::DataStorage::FHierarchyHandle) const override;`
- L152 _public prototype_ `virtual const UScriptStruct* GetChildTagType( UE::Editor::DataStorage::FHierarchyHandle) const override;`
- L154 _public prototype_ `virtual const UScriptStruct* GetParentTagType( UE::Editor::DataStorage::FHierarchyHandle) const override;`
- L156 _public prototype_ `virtual const UScriptStruct* GetHierarchyDataColumnType( UE::Editor::DataStorage::FHierarchyHandle) const override;`
- L158 _public prototype_ `virtual const UScriptStruct* GetParentChangedColumnType( UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle) const override;`
- L160 _public prototype_ `virtual void ResolveHierarchy(UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle) override;`
- L161 _public prototype_ `virtual void ListHierarchyNames(TFunctionRef<void(const FName& HierarchyName)> Callback) const override;`
- L162 _public prototype_ `virtual void SetParentRow( UE::Editor::DataStorage::FHierarchyHandle, UE::Editor::DataStorage::RowHandle Target, UE::Editor::DataStorage::RowHandle Parent) override;`
- L164 _public prototype_ `virtual void SetUnresolvedParent( UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle, UE::Editor::DataStorage::RowHandle Target, UE::Editor::DataStorage::FMapKey ParentId, FName MappingDomain) override;`
- L167 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetParentRow( UE::Editor::DataStorage::FHierarchyHandle, UE::Editor::DataStorage::RowHandle Target) const override;`
- L169 _public prototype_ `virtual TFunction<UE::Editor::DataStorage::RowHandle(const void*, const UScriptStruct*)> CreateParentExtractionFunction( UE::Editor::DataStorage::FHierarchyHandle) const override;`
- L171 _public prototype_ `virtual bool HasChildren( UE::Editor::DataStorage::FHierarchyHandle, UE::Editor::DataStorage::RowHandle Row) const override;`
- L173 _public prototype_ `virtual void WalkDepthFirst( UE::Editor::DataStorage::FHierarchyHandle, UE::Editor::DataStorage::RowHandle Row, TFunction<void(const ICoreProvider& Context, UE::Editor::DataStorage::RowHandle Owner, UE::Editor::DataStorage::RowHandle Target)> VisitFn, ETraversalOrder TraversalOrder = ETraversalOrder::PreOrder) const override;`
- L178 _public prototype_ `virtual bool IterateChildren( UE::Editor::DataStorage::FHierarchyHandle, UE::Editor::DataStorage::RowHandle Row, TFunctionRef<bool(const ICoreProvider& Context, UE::Editor::DataStorage::RowHandle Child)> VisitFn) const override;`
- L184 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle AddScopeRow() override;` — Scope
- L185 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle AddScopeRow(FStringView Label) override;`
- L186 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle AddScopeRow(FStringView Label, UE::Editor::DataStorage::RowHandle Parent) override;`
- L187 _public prototype_ `virtual void RemoveScopeRow(UE::Editor::DataStorage::RowHandle Row) override;`
- L188 _public prototype_ `virtual void SetParentScope(UE::Editor::DataStorage::RowHandle Child, UE::Editor::DataStorage::RowHandle Parent) override;`
- L189 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetParentScope(UE::Editor::DataStorage::RowHandle Row) override;`
- L190 _public prototype_ `virtual const void* GetScopeDataRaw(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) override;`
- L191 _public prototype_ `virtual UE::Editor::DataStorage::Scope::FScopeDataVersion GetScopeDataVersion( UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) override;`
- L193 _public prototype_ `virtual UE::Editor::DataStorage::Scope::FScopeDataVersion SetScopeData( UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType, UE::Editor::DataStorage::ColumnCreationCallbackRef Initializer, UE::Editor::DataStorage::ColumnCopyOrMoveCallback Relocator) override;`
- L196 _public prototype_ `virtual bool RemoveScopeData(UE::Editor::DataStorage::RowHandle Row, const UScriptStruct* ColumnType) override;`
- L197 _public prototype_ `virtual TArray<const UScriptStruct*> GetAllVisibleScopeColumns( UE::Editor::DataStorage::RowHandle Row) override;`
- L199 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetRootScope() const override;`
- L200 _public prototype_ `virtual UE::Editor::DataStorage::FHierarchyHandle GetScopeHierarchy() override;`
- L203 _public prototype_ `virtual UE::Editor::DataStorage::RelationTypeHandle RegisterRelationType( const UE::Editor::DataStorage::FRelationRegistrationParams& Params) override;` — Relations Interface - Relation Type Management
- L205 _public prototype_ `virtual UE::Editor::DataStorage::RelationTypeHandle FindRelationType( const FName& InName) const override;`
- L207 _public prototype_ `virtual bool IsValidRelationType( UE::Editor::DataStorage::RelationTypeHandle Type) const override;`
- L209 _public prototype_ `virtual const UE::Editor::DataStorage::FTedsRelationTraits* GetRelationTypeTraits( UE::Editor::DataStorage::RelationTypeHandle Type) const override;`
- L211 _public prototype_ `virtual void ListRelationTypes( TFunctionRef<void(UE::Editor::DataStorage::RelationTypeHandle, const FName&)> Callback) const override;`
- L213 _public prototype_ `virtual const UScriptStruct* GetRelationSubjectChangedColumn( UE::Editor::DataStorage::RelationTypeHandle Type) const override;`
- L215 _public prototype_ `virtual const UScriptStruct* GetRelationObjectChangedColumn( UE::Editor::DataStorage::RelationTypeHandle Type) const override;`
- L219 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle CreateRelation( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject, UE::Editor::DataStorage::RowHandle Object) override;` — Relations Interface - Relation Instance Management
- L223 _public prototype_ `virtual void BatchCreateRelations( UE::Editor::DataStorage::RelationTypeHandle Type, TConstArrayView<UE::Editor::DataStorage::RowHandle> Subjects, TConstArrayView<UE::Editor::DataStorage::RowHandle> Objects, TArray<UE::Editor::DataStorage::RowHandle>* OutRelationRows = nullptr) override;`
- L228 _public prototype_ `virtual bool DestroyRelation( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject, UE::Editor::DataStorage::RowHandle Object) override;`
- L232 _public prototype_ `virtual bool HasRelation( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject, UE::Editor::DataStorage::RowHandle Object) const override;`
- L236 _public prototype_ `virtual bool HasRelationObject( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject) const override;`
- L239 _public prototype_ `virtual bool HasRelationSubject( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Object) const override;`
- L244 _public prototype_ `virtual void GetRelationObjects( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject, TArray<UE::Editor::DataStorage::RowHandle>& OutObjects) const override;` — Relations Interface - Relation Queries
- L248 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetRelationObject( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject) const override;`
- L251 _public prototype_ `virtual void GetRelationSubjects( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Object, TArray<UE::Editor::DataStorage::RowHandle>& OutSubjects) const override;`
- L255 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetRelationSubject( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Object) const override;`
- L260 _public prototype_ `virtual bool IsDescendantOf( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Descendant, UE::Editor::DataStorage::RowHandle Ancestor, bool bIncludeSelf = false) const override;` — Relations Interface - Hierarchical Queries
- L265 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetHierarchyRoot( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Row) const override;`
- L268 _public prototype_ `virtual int32 GetHierarchyDepth( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Row) const override;`
- L271 _public prototype_ `virtual void GetDescendants( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Ancestor, TArray<UE::Editor::DataStorage::RowHandle>& OutDescendants) const override;`
- L275 _public prototype_ `virtual void GetAncestors( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Descendant, TArray<UE::Editor::DataStorage::RowHandle>& OutAncestors) const override;`
- L279 _public prototype_ `virtual void TraverseDescendants( UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle StartRow, FRelationTraversalCallback Callback, ETraversalOrder Order = ETraversalOrder::PreOrder, int32 MaxDepth = TNumericLimits<int32>::Max()) const override;`
- L287 _public prototype_ `virtual void ForEachRelationObject(UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Subject, TFunctionRef<void(UE::Editor::DataStorage::RowHandle)> Callback) const override;` — Relations Interface - Callback-Based Enumeration
- L290 _public prototype_ `virtual void ForEachRelationSubject(UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Object, TFunctionRef<void(UE::Editor::DataStorage::RowHandle)> Callback) const override;`
- L293 _public prototype_ `virtual void TraverseAncestors(UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Descendant, TFunctionRef<bool(UE::Editor::DataStorage::RowHandle, int32)> Callback) const override;`
- L296 _public prototype_ `virtual int32 ComputeDescendantCount(UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Ancestor) const override;`
- L298 _public prototype_ `virtual bool HasRelationSubjects(UE::Editor::DataStorage::RelationTypeHandle Type, UE::Editor::DataStorage::RowHandle Object) const override;`
- L301 _public prototype_ `void RegisterTickGroup(FName GroupName, UE::Editor::DataStorage::EQueryTickPhase Phase, FName BeforeGroup, FName AfterGroup, UE::Editor::DataStorage::EExecutionMode ExecutionMode);`
- L302 _public prototype_ `void UnregisterTickGroup(FName GroupName, UE::Editor::DataStorage::EQueryTickPhase Phase);`
- L304 _public prototype_ `UE::Editor::DataStorage::QueryHandle RegisterQuery(UE::Editor::DataStorage::FQueryDescription&& Query) override;`
- L305 _public prototype_ `virtual void UnregisterQuery(UE::Editor::DataStorage::QueryHandle Query) override;`
- L306 _public prototype_ `virtual const UE::Editor::DataStorage::FQueryDescription& GetQueryDescription(UE::Editor::DataStorage::QueryHandle Query) const override;`
- L307 _public prototype_ `virtual uint64 CalculateQueryTablesTopologyHash(UE::Editor::DataStorage::QueryHandle Query) const override;`
- L308 _public prototype_ `virtual FName GetQueryTickGroupName(UE::Editor::DataStorage::EQueryTickGroups Group) const override;`
- L309 _public prototype_ `virtual UE::Editor::DataStorage::FQueryResult RunQuery(UE::Editor::DataStorage::QueryHandle Query) override;`
- L310 _public prototype_ `virtual UE::Editor::DataStorage::FQueryResult RunQuery(UE::Editor::DataStorage::QueryHandle Query, UE::Editor::DataStorage::DirectQueryCallbackRef Callback) override;`
- L311 _public prototype_ `virtual UE::Editor::DataStorage::FQueryResult RunQuery(UE::Editor::DataStorage::QueryHandle Query, UE::Editor::DataStorage::EDirectQueryExecutionFlags Flags, UE::Editor::DataStorage::DirectQueryCallbackRef Callback) override;`
- L313 _public prototype_ `virtual UE::Editor::DataStorage::FQueryResult RunQuery(UE::Editor::DataStorage::QueryHandle Query, UE::Editor::DataStorage::ERunQueryFlags Flags, const UE::Editor::DataStorage::Queries::TQueryFunction<void>& Callback) override;`
- L315 _public prototype_ `virtual UE::Editor::DataStorage::FQueryResult RunQuery(UE::Editor::DataStorage::QueryHandle Query, UE::Editor::DataStorage::ERunQueryFlags Flags, const UE::Editor::DataStorage::Queries::TConstQueryFunction<void>& Callback) const override;`
- L317 _public prototype_ `virtual void ActivateQueries(FName ActivationName) override;`
- L319 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle LookupMappedRow( const FName& Domain, const UE::Editor::DataStorage::FMapKeyView& Key) const override;`
- L321 _public prototype_ `virtual void MapRow( const FName& Domain, UE::Editor::DataStorage::FMapKey Key, UE::Editor::DataStorage::RowHandle Row) override;`
- L323 _public prototype_ `virtual void BatchMapRows( const FName& Domain, TArrayView<TPair<UE::Editor::DataStorage::FMapKey, UE::Editor::DataStorage::RowHandle>> MapRowPairs) override;`
- L325 _public prototype_ `virtual void RemapRow( const FName& Domain, const UE::Editor::DataStorage::FMapKeyView& OriginalKey, UE::Editor::DataStorage::FMapKey NewKey) override;`
- L327 _public prototype_ `virtual void RemoveRowMapping( const FName& Domain, const UE::Editor::DataStorage::FMapKeyView& Key) override;`
- L330 _public prototype_ `virtual UE::Editor::DataStorage::FTypedElementOnDataStorageUpdate& OnUpdate() override;`
- L331 _public prototype_ `virtual UE::Editor::DataStorage::FTypedElementOnDataStorageUpdate& OnUpdateCompleted() override;`
- L332 _public prototype_ `virtual void RegisterCooperativeUpdate(const FName& TaskName, ECooperativeTaskPriority Priority, FOnCooperativeUpdate Callback) override;`
- L333 _public prototype_ `virtual void UnregisterCooperativeUpdate(const FName& TaskName) override;`
- L334 _public prototype_ `virtual bool IsAvailable() const override;`
- L335 _public prototype_ `virtual void* GetExternalSystemAddress(UClass* Target) override;`
- L337 _public prototype_ `virtual bool SupportsExtension(FName Extension) const override;`
- L338 _public prototype_ `virtual void ListExtensions(TFunctionRef<void(FName)> Callback) const override;`
- L340 _public prototype_ `TSharedPtr<UE::Editor::DataStorage::FEnvironment> GetEnvironmentPtr();`
- L341 _public prototype_ `TSharedPtr<const UE::Editor::DataStorage::FEnvironment> GetEnvironmentPtr() const;`
- L343 _public prototype_ `UE::Editor::DataStorage::FEnvironment& GetEnvironment();`
- L344 _public prototype_ `const UE::Editor::DataStorage::FEnvironment& GetEnvironment() const;`
- L346 _public prototype_ `void DebugPrintQueryCallbacks(FOutputDevice& Output) override;`
- L348 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L351 _private prototype_ `void PreparePhase(UE::Editor::DataStorage::EQueryTickPhase Phase, float DeltaTime);`
- L352 _private prototype_ `void FinalizePhase(UE::Editor::DataStorage::EQueryTickPhase Phase, float DeltaTime);`
- L353 _private prototype_ `void Reset();`
- L355 _private prototype_ `void TickCooperativeTasks();`
- L379 _private member_ `static const FName TickGroupName_Default;`
- L380 _private member_ `static const FName TickGroupName_PreUpdate;`
- L381 _private member_ `static const FName TickGroupName_Update;`
- L382 _private member_ `static const FName TickGroupName_PostUpdate;`
- L383 _private member_ `static const FName TickGroupName_SyncWidget;`
- L384 _private member_ `static const FName TickGroupName_SyncExternalToDataStorage;`
- L385 _private member_ `static const FName TickGroupName_SyncDataStorageToExternal;`
- L388 _private member_ `TArray<FFactoryTypePair> Factories;` — Ordered array of factories by the return value of GetOrder()
- L390 _private member_ `TSharedPtr<UE::Editor::DataStorage::FEnvironment> Environment;`
- L392 _private member_ `UE::Editor::DataStorage::FTypedElementOnDataStorageUpdate OnUpdateDelegate;`
- L393 _private member_ `UE::Editor::DataStorage::FTypedElementOnDataStorageUpdate OnUpdateCompletedDelegate;`
- L394 _private member_ `FDelegateHandle OnPreMassTickHandle;`
- L395 _private member_ `FDelegateHandle OnPostMassTickHandle;`
- L405 _private member_ `TArray<FCooperativeTask> CooperativeTasks;`
- L406 _private member_ `FTimespan LastFrameCooperativeTickDuration;`
- L407 _private member_ `uint64 CooperativeTickStartTime = 0;`
- L411 _private member_ `int32 CooperativeTaskIdleFrameCount = 0;` — The number of frames the cooperative tasks have been idle due to a lack of available time. Once this reaches a user specified number the cooperative tasks will start processing with a minimal amount of time to avoid tasks starving.
- L412 _private member_ `bool bRunningCooperativeUpdate = false;`
- L414 _private member_ `TSharedPtr<FMassEntityManager> ActiveEditorEntityManager;`
- L415 _private member_ `TSharedPtr<FMassProcessingPhaseManager> ActiveEditorPhaseManager;`
- L419 _private member_ `mutable uint32 ActiveCallsCount = 0;` — Track the number of active calls, incrementing whenever a function calls another direct API call. This prevents the command buffer from being flushed early and guarantees it only being flushed when the call chain has completed.

#### class `UEditorDataStorage::TFactoryIterator`  
`template<typename FactoryType, typename DatabaseType> class TFactoryIterator`  
_L48-65_
- L51 _public typedef_ `using ThisType = TFactoryIterator<FactoryType, DatabaseType>;`
- L52 _public typedef_ `using FactoryPtr = FactoryType*;`
- L53 _public typedef_ `using DatabasePtr = DatabaseType*;`
- L55 _public prototype_ `TFactoryIterator() = default;`
- L56 _public prototype_ `explicit TFactoryIterator(DatabasePtr InDatabase);`
- L58 _public prototype_ `FactoryPtr operator*() const;`
- L59 _public prototype_ `ThisType& operator++();`
- L60 _public prototype_ `operator bool() const;`
- L63 _private member_ `DatabasePtr Database = nullptr;`
- L64 _private member_ `int32 Index = 0;`
- L423 _function_ `template <typename FactoryType, typename DatabaseType> UEditorDataStorage::TFactoryIterator<FactoryType, DatabaseType>::TFactoryIterator(DatabasePtr InDatabase): Database(InDatabase)`
- L427 _function_ `template <typename FactoryType, typename DatabaseType> typename UEditorDataStorage::TFactoryIterator<FactoryType, DatabaseType>::FactoryPtr UEditorDataStorage::TFactoryIterator<FactoryType, DatabaseType>::operator*() const`
- L433 _function_ `template <typename FactoryType, typename DatabaseType> typename UEditorDataStorage::TFactoryIterator<FactoryType, DatabaseType>::ThisType& UEditorDataStorage::TFactoryIterator<FactoryType, DatabaseType>::operator++()`
- L443 _function_ `template <typename FactoryType, typename DatabaseType> UEditorDataStorage::TFactoryIterator<FactoryType, DatabaseType>::operator bool() const`

#### struct `UEditorDataStorage::FFactoryTypePair`  
`struct FFactoryTypePair`  
_L357-363_
- L360 _public member_ `TObjectPtr<UClass> Type;` — Used to find the factory by type without needing to dereference each one
- L362 _public member_ `TObjectPtr<UEditorDataStorageFactory> Instance;`

#### struct `UEditorDataStorage::FActiveCallScope`  
`struct FActiveCallScope`  
_L366-377_
- desc: Wrapper around ActiveCallsCount to avoid issues with timing such as early outs.
- L368 _public prototype_ `explicit FActiveCallScope(const UEditorDataStorage& Owner);`
- L369 _public prototype_ `~FActiveCallScope();`
- L371 _public prototype_ `FActiveCallScope(const FActiveCallScope&) = delete;`
- L372 _public prototype_ `FActiveCallScope(FActiveCallScope&&) = delete;`
- L373 _public prototype_ `FActiveCallScope& operator=(const FActiveCallScope&) = delete;`
- L374 _public prototype_ `FActiveCallScope& operator=(FActiveCallScope&&) = delete;`
- L376 _public member_ `const UEditorDataStorage& Owner;`

#### struct `UEditorDataStorage::FCooperativeTask`  
`struct FCooperativeTask`  
_L397-404_
- L399 _public member_ `FOnCooperativeUpdate Callback;`
- L400 _public member_ `FName Name;`
- L401 _public member_ `uint8 OrderResetValue;`
- L402 _public member_ `uint8 Order;`
- L403 _public member_ `bool bHasRun;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API TEDSCORE_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Editor` (scope `UE`)
- L27 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L32 _typedef_ `using ImplementationForwarder = UE::Editor::DataStorage::Queries::Private::TImplementationForwarder< UE::Editor::DataStorage::Queries::FDirectContextEnvironment, UE::Editor::DataStorage::ICoreProvider, UE::Editor::DataStorage::Queries::FTableInfoContextCapability, UE::Editor::DataStorage::Queries::FTableManagementContextCapability, UE::Editor::DataStorage::Queries::FDynamicColumnInfoContextCapability>;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabaseCommandBuffer.h` (Private)


#### class `UE::Editor::DataStorage::Legacy::FCommandBuffer`  
`class FCommandBuffer final`  
_L22-134_
- L25 _public prototype_ `explicit FCommandBuffer(FEnvironment& InEnvironment);`
- L28 _public prototype_ `void* GetQueuedDataColumn(RowHandle Row, const UScriptStruct* ColumnType);` — Returns a pointer to the queued data column, if it exists and hasn't been processed yet. Otherwise null is returned.
- L30 _public prototype_ `bool HasColumn(RowHandle Row, const UScriptStruct* ColumnType) const;` — Returns if the column on the provided row is pending processing.
- L32 _public prototype_ `void ListColumns(RowHandle Row, ColumnListCallbackRef Callback) const;` — Returns a list of columns pending processing for a row..
- L34 _public prototype_ `void ListColumns(RowHandle Row, ColumnListWithDataCallbackRef Callback);` — Returns a list of columns and their data addresses (can be null for tags) pending processing for a row..
- L40 _public prototype_ `void Queue_AddColumnCommand(RowHandle Row, const UScriptStruct* ColumnType);` — @section Queue_* functions create a command that can be stored for later execution in the provided command buffer. Typically the Execute_* counter part will be called for execution.
- L41 _public prototype_ `void* Queue_AddDataColumnCommandUnitialized(RowHandle Row, const UScriptStruct* ColumnType, ColumnCopyOrMoveCallback Relocator);`
- L43 _public prototype_ `void Queue_AddColumnsCommand(RowHandle Row, FMassFragmentBitSet FragmentsToAdd, FMassTagBitSet TagsToAdd);`
- L45 _public prototype_ `void Queue_RemoveColumnCommand(RowHandle Row, const UScriptStruct* ColumnType);`
- L46 _public prototype_ `void Queue_RemoveColumnsCommand(RowHandle Row, FMassFragmentBitSet FragmentsToRemove, FMassTagBitSet TagsToRemove);`
- L48 _public prototype_ `void Queue_AddRemoveColumnsCommand(TConstArrayView<RowHandle> Rows, FMassElementBitSet ColumnsToAdd, FMassElementBitSet ColumnsToRemove);`
- L54 _public prototype_ `static bool Execute_IsRowAvailable(const FMassEntityManager& MassEntityManager, RowHandle Row);`
- L55 _public prototype_ `static bool Execute_IsRowAssigned(const FMassEntityManager& MassEntityManager, RowHandle Row);`
- L57 _public prototype_ `static void Execute_AddColumnCommand( FMassEntityManager& MassEntityManager, RowHandle Row, const UScriptStruct* ColumnType);`
- L59 _public prototype_ `static void Execute_AddDataColumnCommand( FMassEntityManager& MassEntityManager, RowHandle Row, const UScriptStruct* ColumnType, void* Data, ColumnCopyOrMoveCallback Relocator);`
- L62 _public prototype_ `static void Execute_AddSharedColumnCommand( FMassEntityManager& MassEntityManager, RowHandle Row, const FConstSharedStruct& SharedColumn);`
- L64 _public prototype_ `static void Execute_RemoveSharedColumnCommand( FMassEntityManager& MassEntityManager, RowHandle Row, const UScriptStruct& ColumnType);`
- L66 _public prototype_ `static void Execute_AddColumnsCommand( FMassEntityManager& MassEntityManager, RowHandle Row, FMassFragmentBitSet FragmentsToAdd, FMassTagBitSet TagsToAdd);`
- L69 _public prototype_ `static void Execute_RemoveColumnCommand( FMassEntityManager& MassEntityManager, RowHandle Row, const UScriptStruct* ColumnType);`
- L71 _public prototype_ `static void Execute_RemoveColumnsCommand( FMassEntityManager& MassEntityManager, RowHandle Row, FMassFragmentBitSet FragmentsToRemove, FMassTagBitSet TagsToRemove);`
- L74 _public prototype_ `static void Execute_AddRemoveColumnsCommand( FMassEntityManager& MassEntityManager, TArrayView<RowHandle> Rows, FMassElementBitSet ElementsToAdd, FMassElementBitSet ElementsToRemove);`
- L78 _public prototype_ `void ProcessCommands();`
- L79 _public prototype_ `void ClearCommands();`
- L119 _private typedef_ `using CommandData = TVariant< FAddColumnCommand, FAddDataColumnCommand, FAddColumnsCommand, FRemoveColumnCommand, FRemoveColumnsCommand, FAddRemoveColumnsCommand>;`
- L128 _private prototype_ `template<typename T> void AddCommand(T&& Args);`
- L130 _private typedef_ `using PendingColumnMappingKey = TPair<RowHandle, TWeakObjectPtr<const UScriptStruct>>;`
- L131 _private member_ `TMap<PendingColumnMappingKey, void*> PendingColumns;`
- L132 _private member_ `TArray<CommandData> Commands;`
- L133 _private member_ `FEnvironment& Environment;`

#### struct `UE::Editor::DataStorage::Legacy::FCommandBuffer::FAddColumnCommand`  
`struct FAddColumnCommand`  
_L82-86_
- L84 _public member_ `RowHandle Row;`
- L85 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`

#### struct `UE::Editor::DataStorage::Legacy::FCommandBuffer::FAddDataColumnCommand`  
`struct FAddDataColumnCommand`  
_L87-95_
- L89 _public member_ `RowHandle Row;`
- L90 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`
- L91 _public member_ `ColumnCopyOrMoveCallback Relocator;`
- L92 _public member_ `void* Data;`
- L94 _public prototype_ `~FAddDataColumnCommand();`

#### struct `UE::Editor::DataStorage::Legacy::FCommandBuffer::FAddColumnsCommand`  
`struct FAddColumnsCommand`  
_L96-101_
- L98 _public member_ `RowHandle Row;`
- L99 _public member_ `FMassFragmentBitSet FragmentsToAdd;`
- L100 _public member_ `FMassTagBitSet TagsToAdd;`

#### struct `UE::Editor::DataStorage::Legacy::FCommandBuffer::FRemoveColumnCommand`  
`struct FRemoveColumnCommand`  
_L102-106_
- L104 _public member_ `RowHandle Row;`
- L105 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`

#### struct `UE::Editor::DataStorage::Legacy::FCommandBuffer::FRemoveColumnsCommand`  
`struct FRemoveColumnsCommand`  
_L107-112_
- L109 _public member_ `RowHandle Row;`
- L110 _public member_ `FMassFragmentBitSet FragmentsToRemove;`
- L111 _public member_ `FMassTagBitSet TagsToRemove;`

#### struct `UE::Editor::DataStorage::Legacy::FCommandBuffer::FAddRemoveColumnsCommand`  
`struct FAddRemoveColumnsCommand`  
_L113-118_
- L115 _public member_ `TArrayView<RowHandle> Rows;`
- L116 _public member_ `FMassElementBitSet ElementsToAdd;`
- L117 _public member_ `FMassElementBitSet ElementsToRemove;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace Legacy` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabaseCompatibility.h` (Private)


#### class `UEditorDataStorageCompatibility`  
`class UEditorDataStorageCompatibility : public UObject , public UE::Editor::DataStorage::ICompatibilityProvider`  
_L34-243_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Editor::DataStorage::ICompatibilityProvider`
- L46 _public prototype_ `void Initialize(UEditorDataStorage* InStorage);`
- L47 _public prototype_ `void PostInitialize(UEditorDataStorage* InStorage);`
- L48 _public prototype_ `void Deinitialize();`
- L50 _public prototype_ `void RegisterRegistrationFilter(ObjectRegistrationFilter Filter) override;`
- L51 _public prototype_ `void RegisterDealiaserCallback(ObjectToRowDealiaser Dealiaser) override;`
- L52 _public prototype_ `void RegisterTypeTableAssociation(TWeakObjectPtr<UStruct> TypeInfo, UE::Editor::DataStorage::TableHandle Table) override;`
- L53 _public prototype_ `FDelegateHandle RegisterObjectAddedCallback(UE::Editor::DataStorage::ObjectAddedCallback&& OnObjectAdded);`
- L54 _public prototype_ `void UnregisterObjectAddedCallback(FDelegateHandle Handle);`
- L55 _public prototype_ `FDelegateHandle RegisterObjectRemovedCallback(UE::Editor::DataStorage::ObjectRemovedCallback&& OnObjectRemoved);`
- L56 _public prototype_ `void UnregisterObjectRemovedCallback(FDelegateHandle Handle);`
- L58 _public prototype_ `UE::Editor::DataStorage::RowHandle AddCompatibleObjectExplicit(UObject* Object) override;`
- L59 _public prototype_ `UE::Editor::DataStorage::RowHandle AddCompatibleObjectExplicit(void* Object, TWeakObjectPtr<const UScriptStruct> TypeInfo) override;`
- L61 _public prototype_ `void RemoveCompatibleObjectExplicit(UObject* Object) override;`
- L62 _public prototype_ `void RemoveCompatibleObjectExplicit(void* Object) override;`
- L64 _public prototype_ `UE::Editor::DataStorage::RowHandle FindRowWithCompatibleObjectExplicit(const UObject* Object) const override;`
- L65 _public prototype_ `UE::Editor::DataStorage::RowHandle FindRowWithCompatibleObjectExplicit(const void* Object) const override;`
- L67 _public prototype_ `bool SupportsExtension(FName Extension) const override;`
- L68 _public prototype_ `void ListExtensions(TFunctionRef<void(FName)> Callback) const override;`
- L71 _protected prototype_ `void EnterImmediateMode(UE::Editor::DataStorage::FObjectCompatibilityImmediateScope& Scope) override;`
- L72 _protected prototype_ `void LeaveImmediateMode(UE::Editor::DataStorage::FObjectCompatibilityImmediateScope& Scope) override;`
- L109 _private prototype_ `void Prepare();`
- L110 _private prototype_ `void CreateStandardArchetypes();`
- L111 _private prototype_ `void RegisterTypeInformationQueries();`
- L113 _private prototype_ `bool ShouldAddObject(const UObject* Object) const;`
- L114 _private prototype_ `UE::Editor::DataStorage::TableHandle FindBestMatchingTable(const UStruct* TypeInfo) const;`
- L116 _private prototype_ `template<bool bEnableTransactions> UE::Editor::DataStorage::RowHandle AddCompatibleObjectExplicitTransactionable(UObject* Object);`
- L118 _private prototype_ `template<bool bEnableTransactions> void RemoveCompatibleObjectExplicitTransactionable(const UObject* Object);`
- L120 _private prototype_ `template<bool bEnableTransactions> void RemoveCompatibleObjectExplicitTransactionable(const UObject* Object, UE::Editor::DataStorage::RowHandle ObjectRow);`
- L121 _private prototype_ `UE::Editor::DataStorage::RowHandle DealiasObject(const UObject* Object) const;`
- L123 _private prototype_ `void Tick();`
- L124 _private prototype_ `void TickPendingCommands();`
- L125 _private prototype_ `void TickPendingUObjectRegistration();`
- L126 _private prototype_ `void TickPendingExternalObjectRegistration();`
- L127 _private prototype_ `void TickObjectSync();`
- L129 _private prototype_ `void OnPrePropertyChanged(UObject* Object, const FEditPropertyChain& PropertyChain);`
- L130 _private prototype_ `void OnPostEditChangeProperty(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L131 _private prototype_ `void OnObjectModified(UObject* Object);`
- L132 _private prototype_ `void TriggerOnObjectAdded(const void* Object, UE::Editor::DataStorage::FObjectTypeInfo TypeInfo, UE::Editor::DataStorage::RowHandle Row) const;`
- L133 _private prototype_ `void TriggerOnPreObjectRemoved(const void* Object, UE::Editor::DataStorage::FObjectTypeInfo TypeInfo, UE::Editor::DataStorage::RowHandle Row) const;`
- L134 _private prototype_ `void OnObjectReinstanced(const FCoreUObjectDelegates::FReplacementObjectMap& ReplacedObjects);`
- L136 _private prototype_ `void OnPostGcUnreachableAnalysis();`
- L162 _private member_ `FPendingTypeInformationUpdate PendingTypeInformationUpdate;`
- L195 _private member_ `UE::Editor::DataStorage::CompatibilityCommandBuffer QueuedCommands;`
- L196 _private member_ `UE::Editor::DataStorage::CompatibilityCommandBuffer::FCollection PendingCommands;`
- L197 _private member_ `PendingRegistration<TWeakObjectPtr<UObject>> UObjectsPendingRegistration;`
- L198 _private member_ `PendingRegistration<ExternalObjectRegistration> ExternalObjectsPendingRegistration;`
- L199 _private member_ `TArray<UE::Editor::DataStorage::RowHandle> RowScratchBuffer;`
- L201 _private member_ `TArray<ObjectRegistrationFilter> ObjectRegistrationFilters;`
- L202 _private member_ `TArray<ObjectToRowDealiaser> ObjectToRowDialiasers;`
- L203 _private typedef_ `using TypeToTableMapType = TMap<TWeakObjectPtr<UStruct>, UE::Editor::DataStorage::TableHandle>;`
- L204 _private member_ `TypeToTableMapType TypeToTableMap;`
- L205 _private member_ `TArray<TPair<UE::Editor::DataStorage::ObjectAddedCallback, FDelegateHandle>> ObjectAddedCallbackList;`
- L206 _private member_ `TArray<TPair<UE::Editor::DataStorage::ObjectRemovedCallback, FDelegateHandle>> PreObjectRemovedCallbackList;`
- L208 _private member_ `static thread_local UE::Editor::DataStorage::FObjectCompatibilityImmediateScope* ImmediateModeTracker;`
- L210 _private member_ `UE::Editor::DataStorage::TableHandle StandardUObjectTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L211 _private member_ `UE::Editor::DataStorage::TableHandle StandardExternalObjectTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L212 _private member_ `UE::Editor::DataStorage::ICoreProvider* Storage{ nullptr };`
- L227 _private member_ `static constexpr uint32 MaxExpectedTagsForObjectSync = 2;`
- L228 _private typedef_ `using ObjectsNeedingSyncTagsMapKey = TObjectKey<const UObject>;`
- L229 _private typedef_ `using ObjectsNeedingSyncTagsMapValue = TArray<FSyncTagInfo, TInlineAllocator<MaxExpectedTagsForObjectSync>>;`
- L230 _private typedef_ `using ObjectsNeedingSyncTagsMap = TMap<ObjectsNeedingSyncTagsMapKey, ObjectsNeedingSyncTagsMapValue>;`
- L231 _private member_ `ObjectsNeedingSyncTagsMap ObjectsNeedingSyncTags;`
- L233 _private member_ `FDelegateHandle PreEditChangePropertyDelegateHandle;`
- L234 _private member_ `FDelegateHandle PostEditChangePropertyDelegateHandle;`
- L235 _private member_ `FDelegateHandle ObjectModifiedDelegateHandle;`
- L236 _private member_ `FDelegateHandle ObjectReinstancedDelegateHandle;`
- L237 _private member_ `FDelegateHandle PostGcUnreachableAnalysisHandle;`
- L239 _private member_ `TSharedPtr<UE::Editor::DataStorage::FEnvironment> Environment;`
- L240 _private member_ `UE::Editor::DataStorage::QueryHandle ClassTypeInfoQuery;`
- L241 _private member_ `UE::Editor::DataStorage::QueryHandle ScriptStructTypeInfoQuery;`
- L242 _private member_ `UE::Editor::DataStorage::QueryHandle UObjectQuery;`

#### class `UEditorDataStorageCompatibility::FRegistrationCommandChange`  
`class FRegistrationCommandChange final : public FCommandChange`  
_L78-92_
- inherits: `FCommandChange`
- desc: The below changes expect UEditorDataStorageCompatibility to be the object passed in to StoreUndo. Note that we cannot pass in TargetObject to StoreUndo because doing so seems to stomp regular Modify() changes for that object.
- L81 _public prototype_ `FRegistrationCommandChange(UEditorDataStorageCompatibility* InOwner, UObject* InTargetObject);`
- L84 _public prototype_ `void Apply(UObject* Object) override;`
- L85 _public prototype_ `void Revert(UObject* Object) override;`
- L86 _public prototype_ `FString ToString() const override;`
- L89 _private member_ `TWeakObjectPtr<UEditorDataStorageCompatibility> Owner;`
- L90 _private member_ `TWeakObjectPtr<UObject> TargetObject;`
- L91 _private member_ `UE::Editor::DataStorage::RowHandle MementoRow = UE::Editor::DataStorage::InvalidRowHandle;`

#### class `UEditorDataStorageCompatibility::FDeregistrationCommandChange`  
`class FDeregistrationCommandChange final : public FCommandChange`  
_L93-107_
- inherits: `FCommandChange`
- L96 _public prototype_ `FDeregistrationCommandChange(UEditorDataStorageCompatibility* InOwner, UObject* InTargetObject);`
- L99 _public prototype_ `void Apply(UObject* Object) override;`
- L100 _public prototype_ `void Revert(UObject* Object) override;`
- L101 _public prototype_ `FString ToString() const override;`
- L104 _private member_ `TWeakObjectPtr<UEditorDataStorageCompatibility> Owner;`
- L105 _private member_ `TWeakObjectPtr<UObject> TargetObject;`
- L106 _private member_ `UE::Editor::DataStorage::RowHandle MementoRow = UE::Editor::DataStorage::InvalidRowHandle;`

#### struct `UEditorDataStorageCompatibility::FPendingTypeInformationUpdate`  
`struct FPendingTypeInformationUpdate`  
_L138-161_
- L141 _public prototype_ `FPendingTypeInformationUpdate();`
- L143 _public prototype_ `void AddTypeInformation(const TMap<UObject*, UObject*>& ReplacedObjects);`
- L144 _public prototype_ `void Process(UEditorDataStorageCompatibility& Compatibility);`
- L147 _private prototype_ `TOptional<TWeakObjectPtr<UObject>> ProcessResolveTypeRecursively(const TWeakObjectPtr<const UObject>& Target);`
- L153 _private typedef_ `using PendingTypeInformationMap = TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UObject>, FDefaultSetAllocator, FTypeInfoEntryKeyFuncs>;`
- L155 _private member_ `PendingTypeInformationMap PendingTypeInformationUpdates[2];`
- L156 _private member_ `PendingTypeInformationMap* PendingTypeInformationUpdatesActive;`
- L157 _private member_ `PendingTypeInformationMap* PendingTypeInformationUpdatesSwapped;`
- L158 _private member_ `TArray<TTuple<TWeakObjectPtr<UStruct>, UE::Editor::DataStorage::TableHandle>> UpdatedTypeInfoScratchBuffer;`
- L159 _private member_ `UE::FMutex Safeguard;`
- L160 _private member_ `std::atomic<bool> bHasPendingUpdate = false;`

#### struct `UEditorDataStorageCompatibility::FPendingTypeInformationUpdate::FTypeInfoEntryKeyFuncs`  
`struct FTypeInfoEntryKeyFuncs : TDefaultMapHashableKeyFuncs<TWeakObjectPtr<UObject>, TWeakObjectPtr<UObject>, false>`  
_L149-152_
- inherits: `TDefaultMapHashableKeyFuncs<TWeakObjectPtr<UObject>,TWeakObjectPtr<UObject>,false>`
- L151 _public function_ `static inline bool Matches(KeyInitType Lhs, KeyInitType Rhs)`

#### struct `UEditorDataStorageCompatibility::ExternalObjectRegistration`  
`struct ExternalObjectRegistration`  
_L164-168_
- L166 _public member_ `void* Object;`
- L167 _public member_ `TWeakObjectPtr<const UScriptStruct> TypeInfo;`

#### struct `UEditorDataStorageCompatibility::PendingRegistration`  
`template<typename AddressType> struct PendingRegistration`  
_L171-193_
- L180 _private member_ `TArray<FEntry> Entries;`
- L181 _private member_ `TArray<FEntry> ProcessingEntries;`
- L184 _public prototype_ `void Add(UE::Editor::DataStorage::RowHandle ReservedRowHandle, AddressType Address);`
- L185 _public prototype_ `bool IsEmpty() const;`
- L186 _public prototype_ `int32 Num() const;`
- L188 _public prototype_ `void ForEachAddress(const TFunctionRef<void(AddressType&)>& Callback);`
- L191 _public prototype_ `void ProcessEntries(UE::Editor::DataStorage::ICoreProvider& Storage, UEditorDataStorageCompatibility& Compatibility, const TFunctionRef<void(UE::Editor::DataStorage::RowHandle, const AddressType&)>& SetupRowCallback);` — Processes the entries and return the entries remaining in the list. They will be at the back of the list Once this returns, the list will contain only entries that were not processed

#### struct `UEditorDataStorageCompatibility::PendingRegistration::FEntry`  
`struct FEntry`  
_L174-179_
- L176 _public member_ `AddressType Address;`
- L177 _public member_ `UE::Editor::DataStorage::RowHandle Row;`
- L178 _public member_ `UE::Editor::DataStorage::TableHandle Table;`

#### struct `UEditorDataStorageCompatibility::FSyncTagInfo`  
`struct FSyncTagInfo`  
_L218-225_
- desc: Reference of objects (UObject and AActor) that need to be fully synced from the world to the database. Caution: Could point to objects that have been GC-ed
- L220 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`
- L221 _public member_ `bool bAddColumn;`
- L223 _public prototype_ `bool operator==(const FSyncTagInfo& Rhs) const = default;`
- L224 _public prototype_ `bool operator!=(const FSyncTagInfo& Rhs) const = default;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API TEDSCORE_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Editor` (scope `UE`)
- L27 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L245 _prototype_ `SIZE_T GetTypeHash(const UEditorDataStorageCompatibility::FSyncTagInfo& Column);`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabaseEnvironment.h` (Private)


#### class `UE::Editor::DataStorage::FEnvironment`  
`class FEnvironment final`  
_L25-125_
- L28 _public prototype_ `FEnvironment(UEditorDataStorage& InDataStorage, FMassEntityManager& InMassEntityManager, FMassProcessingPhaseManager& InMassPhaseManager);`
- L31 _public prototype_ `~FEnvironment();`
- L33 _public prototype_ `Legacy::FCommandBuffer& GetDirectDeferredCommands();`
- L34 _public prototype_ `const Legacy::FCommandBuffer& GetDirectDeferredCommands() const;`
- L36 _public prototype_ `FMappingTable& GetMappingTable();`
- L37 _public prototype_ `const FMappingTable& GetMappingTable() const;`
- L39 _public prototype_ `FScratchBuffer& GetScratchBuffer();`
- L40 _public prototype_ `const FScratchBuffer& GetScratchBuffer() const;`
- L42 _public prototype_ `FExtendedQueryStore& GetQueryStore();`
- L43 _public prototype_ `const FExtendedQueryStore& GetQueryStore() const;`
- L45 _public prototype_ `FMementoSystem& GetMementoSystem();`
- L46 _public prototype_ `const FMementoSystem& GetMementoSystem() const;`
- L48 _public prototype_ `FScopeSystem& GetScopeSystem();`
- L49 _public prototype_ `const FScopeSystem& GetScopeSystem() const;`
- L51 _public prototype_ `FMassEntityManager& GetMassEntityManager();`
- L52 _public prototype_ `const FMassEntityManager& GetMassEntityManager() const;`
- L54 _public prototype_ `FTedsHierarchyRegistrar& GetHierarchyRegistrar();`
- L55 _public prototype_ `const FTedsHierarchyRegistrar& GetHierarchyRegistrar() const;`
- L57 _public prototype_ `FTedsRelationAdapter& GetRelationAdapter();`
- L58 _public prototype_ `const FTedsRelationAdapter& GetRelationAdapter() const;`
- L60 _public prototype_ `FTedsHierarchicalRelationManager& GetHierarchicalRelationManager();`
- L61 _public prototype_ `const FTedsHierarchicalRelationManager& GetHierarchicalRelationManager() const;`
- L63 _public prototype_ `FMassProcessingPhaseManager& GetMassPhaseManager();`
- L64 _public prototype_ `const FMassProcessingPhaseManager& GetMassPhaseManager() const;`
- L66 _public prototype_ `TSharedPtr<FMassCommandBuffer> GetSharedMassCommandBuffer();`
- L67 _public prototype_ `TSharedPtr<const FMassCommandBuffer> GetSharedMassCommandBuffer() const;`
- L69 _public prototype_ `FTableManager& GetTableManager();`
- L70 _public prototype_ `const FTableManager& GetTableManager() const;`
- L74 _public prototype_ `const UScriptStruct* FindDynamicColumn(const UScriptStruct& Template, const FName& Identifier) const;` — Finds the type information for the dynamic column Dynamic columns are specified by a template layout and a FName Identifier
- L77 _public prototype_ `const UScriptStruct* GenerateDynamicColumn(const UScriptStruct& Template, const FName& Identifier);` — Generates or returns an existing type for the dynamic column Dynamic columns are specified by a template layout and a FName Identifier
- L80 _public prototype_ `const UScriptStruct* GenerateColumnType(const FValueTag& Tag);` — Creates or Finds the column type associated with the value tag
- L83 _public prototype_ `void ForEachDynamicColumn(const UScriptStruct& Template, TFunctionRef<void(const UScriptStruct& Type)> Callback) const;` — Executes the given callback for each known dynamic column that derives from the base template provided
- L86 _public prototype_ `FConstSharedStruct GenerateValueTag(const FValueTag& Tag, const FName& Value);` — Creates an instance of a value tag
- L88 _public prototype_ `void NextUpdateCycle();`
- L89 _public prototype_ `uint64 GetUpdateCycleId() const;`
- L99 _public prototype_ `void PushCommands(TConstArrayView<const FEnvironmentCommand> Commands);` — Commands are automatically flushed on NextUpdateCycle or when explicitly flushed with `FlushCommands`.
- L100 _public prototype_ `void FlushCommands();`
- L103 _private member_ `Legacy::FCommandBuffer DirectDeferredCommands;`
- L104 _private member_ `FDynamicColumnGenerator DynamicColumnGenerator;`
- L105 _private member_ `FTableManager TableManager;`
- L106 _private member_ `FMappingTable MappingTable;`
- L107 _private member_ `FScratchBuffer ScratchBuffer;`
- L108 _private member_ `FExtendedQueryStore Queries;`
- L109 _private member_ `FMementoSystem MementoSystem;`
- L110 _private member_ `FScopeSystem ScopeSystem;`
- L111 _private member_ `FValueTagManager ValueTagManager;`
- L112 _private member_ `FTedsHierarchyRegistrar HierarchyInterface;`
- L113 _private member_ `FTedsRelationAdapter RelationAdapter;`
- L114 _private member_ `FTedsHierarchicalRelationManager HierarchicalRelationManager;`
- L116 _private member_ `FMutex CommandQueueMutex;`
- L117 _private member_ `TArray<FEnvironmentCommand> CommandQueues[2];`
- L118 _private member_ `TArray<FEnvironmentCommand>* ActiveCommandQueue;`
- L120 _private member_ `FMassEntityManager& MassEntityManager;`
- L121 _private member_ `FMassProcessingPhaseManager& MassPhaseManager;`
- L122 _private member_ `TSharedPtr<FMassCommandBuffer> SharedMassCommandBuffer;`
- L124 _private member_ `uint64 UpdateCycleId = 0;`

#### struct `UE::Editor::DataStorage::FEnvironment::FEnvironmentCommand`  
`struct FEnvironmentCommand`  
_L91-96_
- L93 _public member_ `void (*CommandFunction)(void*);`
- L95 _public member_ `void* CommandData = nullptr;` — If this is not static data or null, it should be a pointer into the scratch buffer

#### struct `UE::Editor::DataStorage::FEmptyEnvironmentRetrievalBase`  
`struct FEmptyEnvironmentRetrievalBase`  
_L127-127_

#### class `UE::Editor::DataStorage::IQueryEnvironmentRetrieval`  
`template<typename Base = FEmptyEnvironmentRetrievalBase> class IQueryEnvironmentRetrieval : public Base`  
_L130-138_
- inherits: `Base`
- L133 _public prototype_ `virtual ~IQueryEnvironmentRetrieval() = default;`
- L136 _protected prototype_ `virtual FEnvironment& GetEnvironment() = 0;`
- L137 _protected prototype_ `virtual const FEnvironment& GetEnvironment() const = 0;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L140 _typedef_ `using QueryEnvironmentRetrieval = IQueryEnvironmentRetrieval<>;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabaseIndexTable.h` (Private)


#### class `UE::Editor::DataStorage::FMappingTable`  
`class FMappingTable final`  
_L26-193_
- L29 _public prototype_ `explicit FMappingTable(UEditorDataStorage& DataStorage);`
- L30 _public prototype_ `~FMappingTable();`
- L32 _public prototype_ `RowHandle Lookup(EGlobalLockScope LockScope, const FName& Domain, const FMapKeyView& Key) const;`
- L33 _public prototype_ `void Map(EGlobalLockScope LockScope, const FName& Domain, FMapKey Key, RowHandle Row);`
- L34 _public prototype_ `void BatchMap(EGlobalLockScope LockScope, const FName& Domain, TArrayView<TPair<FMapKey, RowHandle>> MapRowPairs);`
- L35 _public prototype_ `void Remap(EGlobalLockScope LockScope, const FName& Domain, const FMapKeyView& OriginalKey, FMapKey NewKey);`
- L36 _public prototype_ `void Remove(EGlobalLockScope LockScope, const FName& Domain, const FMapKeyView& Key);`
- L38 _public prototype_ `void MarkDirty();`
- L96 _private member_ `static constexpr int32 InvalidId = -1;`
- L97 _private member_ `static constexpr int32 HashCollisionId = -2;`
- L179 _private typedef_ `using DomainMap = TMap<FName, FDomain>;`
- L180 _private member_ `DomainMap Domains;`
- L182 _private member_ `int32 RemainingUnverifiedDomains = 0;`
- L185 _private member_ `static constexpr int8 DefaultCleanUpFrameDelay = 5;` — The number of frames to wait to start the cleanup. This delay is added as several operations in the editor do a delete spread out of over a few frames.
- L186 _private member_ `std::atomic<int8> CleanUpFrameDelay = 0;`
- L187 _private member_ `std::atomic<bool> DirtyDueToRemoval = false;`
- L189 _private member_ `UEditorDataStorage& DataStorage;`
- L191 _private prototype_ `void RemoveInvalidRows(FTimespan RemainingTime);`
- L192 _private prototype_ `bool IsDirty() const;`

#### struct `UE::Editor::DataStorage::FMappingTable::FCleanUpInfo`  
`struct FCleanUpInfo final`  
_L41-94_
- L43 _public typedef_ `using InvalidRowContainer = TArray<int32>;`
- L46 _public member_ `static const FTimespan JobShrinkThreshold;` — If less than this time is available after running jobs in a frame, reduce the number of jobs.
- L48 _public member_ `static const FTimespan JobGrowthThreshold;` — If more than this time is left per frame, increase the number of jobs.
- L50 _public member_ `static constexpr float JobShrinkFactor = 0.7f;` — The rate at which to grow the number of jobs run per frame.
- L52 _public member_ `static constexpr float JobGrowthFactor = 1.2f;` — The rate at which to shrink the number of jobs run per frame.
- L54 _public member_ `static constexpr int32 MinJobCount = 4;` — The minimum required number of jobs.
- L56 _public member_ `static constexpr int32 MaxJobCount = 1024;` — The maximum number of allowed jobs.
- L61 _public member_ `static const FTimespan MaxBatchDuration;` — If enough batches exceed this limit, the batch size for jobs is reduced. Aim for 4 batches per thread. Increasing this number increases the spikes that can happen when batches are too big. Decreasing this number increases the overhead of scheduling jobs and makes it more expensive overall.
- L63 _public member_ `static const FTimespan MinBatchDuration;` — If enough batches are under this limit, the batch size for jobs is increased.
- L65 _public member_ `static constexpr int32 MinBatchSize = 1000;` — The absolute minimum number of rows to check for validity per batch.
- L67 _public member_ `static constexpr int32 MaxBatchSize = 100'000;` — The absolute maximum number of rows to check for validity per batch.
- L70 _public member_ `static constexpr uint32 BatchShrinkThreshold = 2;` — The number of jobs that need to take longer than MaxBatchDuration before the batch size gets shrunken down. This is used to mitigate the occasional spike due to for instance the OS handing off work to other programs.
- L72 _public member_ `static constexpr float BatchIncreaseThreshold = 0.9f;` — The portion of jobs that need to be below the MinBatchDuration threshold before the batch size gets increased.
- L74 _public member_ `static constexpr float BatchShrinkFactor = 0.8f;` — The rate at which the batch size gets reduced if enough batches went over time.
- L76 _public member_ `static constexpr float BatchGrowthFactor = 1.1f;` — The rate at which the batch size gets increased if there's time left.
- L79 _public member_ `TMpscQueue<InvalidRowContainer> DeletionQueue;` — Queue containing arrays with removed row indices.
- L82 _public member_ `int32 BatchSize = 4096;` — The maximum number of rows that a single job will process.
- L84 _public member_ `std::atomic<uint32> BatchWentOverTime = 0;` — The number of jobs that had too many batches to process within MaxBatchDuration.
- L86 _public member_ `std::atomic<uint32> BatchWentUnderTime = 0;` — The number of jobs that processed their batches faster than MinBatchDuration.
- L89 _public member_ `int32 MaxNumJobs = 8;` — The maximum number of jobs to run per frame.
- L91 _public member_ `int32 JobCount = 0;` — The total number of jobs needed to inspect all indexed rows.
- L93 _public member_ `int32 RemainingJobs = 0;` — The number of jobs that were not completed in the previous frame.

#### struct `UE::Editor::DataStorage::FMappingTable::FCollisionSafeHashMap`  
`struct FCollisionSafeHashMap`  
_L99-123_
- L101 _public typedef_ `using IndexLookupMultiMapType = TMultiMap<uint64, int32>;`
- L102 _public typedef_ `using IndexLookupMapType = TMap<uint64, int32>;`
- L104 _public member_ `IndexLookupMultiMapType MapBackup;` — Backup map in case there's a valid hash collision.
- L105 _public member_ `IndexLookupMapType Map;`
- L107 _public prototype_ `const int32* Find(uint64 Hash, const FMapKey& Key, const TArray<FMapKey>& Keys) const;`
- L108 _public prototype_ `const int32* Find(uint64 Hash, const FMapKeyView& Key, const TArray<FMapKey>& Keys) const;`
- L109 _public prototype_ `int32* Find(uint64 Hash, const FMapKey& Key, const TArray<FMapKey>& Keys);`
- L110 _public prototype_ `int32* Find(uint64 Hash, const FMapKeyView& Key, const TArray<FMapKey>& Keys);`
- L112 _public prototype_ `void ReserveAdditional(int32 Count);`
- L113 _public prototype_ `void Add(uint64 Hash, int32 Index);`
- L114 _public prototype_ `int32 Remove(uint64 Hash, const FMapKey& Key, const TArray<FMapKey>& Keys);`
- L115 _public prototype_ `int32 Remove(uint64 Hash, const FMapKeyView& Key, const TArray<FMapKey>& Keys);`
- L116 _public prototype_ `void Remove(uint64 Hash, int32 Index);`
- L120 _private prototype_ `template<typename KeyType> int32* FindTemplate(uint64 Hash, const KeyType& Key, const TArray<FMapKey>& Keys);`
- L122 _private prototype_ `template<typename KeyType> int32 RemoveTemplate(uint64 Hash, const KeyType& Key, const TArray<FMapKey>& Keys);`

#### struct `UE::Editor::DataStorage::FMappingTable::FShardedMap`  
`struct FShardedMap final`  
_L125-145_
- L127 _public member_ `static constexpr int32 ShardBits = 8;`
- L129 _public member_ `FCollisionSafeHashMap Shards[1 << ShardBits];`
- L131 _public prototype_ `const int32* Find(uint64 Hash, const FMapKey& Key, const TArray<FMapKey>& Keys) const;`
- L132 _public prototype_ `const int32* Find(uint64 Hash, const FMapKeyView& Key, const TArray<FMapKey>& Keys) const;`
- L133 _public prototype_ `int32* Find(uint64 Hash, const FMapKey& Key, const TArray<FMapKey>& Keys);`
- L134 _public prototype_ `int32* Find(uint64 Hash, const FMapKeyView& Key, const TArray<FMapKey>& Keys);`
- L136 _public prototype_ `void ReserveAdditional(TArrayView<TPair<FMapKey, RowHandle>> MapRowPairs);`
- L137 _public prototype_ `void Add(uint64 Hash, int32 Index);`
- L138 _public prototype_ `int32 Remove(uint64 Hash, const FMapKey& Key, const TArray<FMapKey>& Keys);`
- L139 _public prototype_ `int32 Remove(uint64 Hash, const FMapKeyView& Key, const TArray<FMapKey>& Keys);`
- L140 _public prototype_ `void Remove(uint64 Hash, int32 Index);`
- L143 _private prototype_ `int32 GetShard(uint64 Hash) const;`
- L144 _private prototype_ `uint64 ModifyHash(uint64 Hash) const;`

#### struct `UE::Editor::DataStorage::FMappingTable::FDomain`  
`struct FDomain final`  
_L147-178_
- L149 _public member_ `FShardedMap IndexLookupMap;`
- L150 _public member_ `TArray<RowHandle> Rows;`
- L151 _public member_ `TArray<FMapKey> Keys;`
- L152 _public member_ `TDeque<int32> FreeList;`
- L154 _public member_ `TUniquePtr<FCleanUpInfo> CleanUpInfo = MakeUnique<FCleanUpInfo>();`
- L156 _public prototype_ `int32 FindIndexUnguarded(const FMapKey& Key) const;`
- L157 _public prototype_ `int32 FindIndexUnguarded(uint64 Hash, const FMapKey& Key) const;`
- L158 _public prototype_ `int32 FindIndexUnguarded(const FMapKeyView& Key) const;`
- L159 _public prototype_ `int32 FindIndexUnguarded(uint64 Hash, const FMapKeyView& Key) const;`
- L161 _public prototype_ `void IndexRowUnguarded(UEditorDataStorage& DataStorage, FMapKey&& Key, RowHandle Row, bool bIsDirty);`
- L162 _public prototype_ `int32 RemoveUnguarded(const FMapKeyView& Key);`
- L163 _public prototype_ `void RemapUnguarded(UEditorDataStorage& InDataStorage, const FMapKeyView& OriginalKey, FMapKey NewKey, bool bIsDirty);`
- L171 _public prototype_ `ERemoveInvalidRowsResult RemoveInvalidRows(const FName& DomainName, UEditorDataStorage& DataStorage, FTimespan& RemainingTime);`
- L173 _public prototype_ `void InspectRowBlockForCleanUp(UEditorDataStorage& DataStorage, int32 Block);`
- L174 _public prototype_ `void DrainDeletionQueue(FTimespan RemainingFrameTime);`
- L175 _public prototype_ `void ClearRow(int32 Index);`
- L176 _public prototype_ `void AdjustJobCount(FTimespan RemainingFrameTime);`
- L177 _public prototype_ `void AdjustBatchSize(int32 JobCount);`

#### enum `UE::Editor::DataStorage::FMappingTable::FDomain::ERemoveInvalidRowsResult`  
`enum class ERemoveInvalidRowsResult`  
_L165-170_
- L167 _public enumerator_ `NoWork`
- L168 _public enumerator_ `HasRemainingWork`
- L169 _public enumerator_ `CompletedWork`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabaseScratchBuffer.h` (Private)


#### class `UE::Editor::DataStorage::FScratchBuffer`  
`class FScratchBuffer`  
_L13-103_
- L26 _private typedef_ `using MemoryAllocator = TConcurrentLinearBulkObjectAllocator<FAllocationTag>;`
- L36 _public prototype_ `FScratchBuffer();`
- L39 _public prototype_ `void* AllocateUninitialized(SIZE_T Size, uint32 Alignment);` — Allocate uninitialized memory.
- L46 _public prototype_ `template<typename T, ERequiresTrivialDestructor RequiresTrivialDestructors = ERequiresTrivialDestructor::Yes> T* AllocateUninitialized();` — Allocates memory for a single object but does not initialize the memory. Memory is only reserved and the destructor will not be called.
- L53 _public prototype_ `template<typename T, ERequiresTrivialDestructor RequiresTrivialDestructors = ERequiresTrivialDestructor::Yes> TArrayView<T> AllocateUninitializedArray(int32 Count);` — Allocates memory for an array of object but does not initialize the memory. Memory is only reserved and the destructor will not be called.
- L56 _public prototype_ `void* AllocateZeroInitialized(SIZE_T Size, uint32 Alignment);` — Allocate memory and sets it to zero.
- L63 _public prototype_ `template<typename T, ERequiresTrivialDestructor RequiresTrivialDestructors = ERequiresTrivialDestructor::Yes> T* AllocateZeroInitialized();` — Allocates memory for a single object and sets the memory to zero. This is not the same as calling a constructor, which can be done using Emplace. Memory is only reserved and the destructor will not be called.
- L70 _public prototype_ `template<typename T, ERequiresTrivialDestructor RequiresTrivialDestructors = ERequiresTrivialDestructor::Yes> TArrayView<T> AllocateZeroInitializedArray(int32 Count);` — Allocates memory for an array of object and sets the memory to zero. This is not the same as calling a constructor, which can be done using Emplace. Memory is only reserved and the destructor will not be called.
- L77 _public prototype_ `template<typename T, typename... ArgTypes> T* Emplace(ArgTypes... Args);` — Allocate memory for one object and construct it with the provided arguments. The object created by this call will has its constructor and destructor called.
- L84 _public prototype_ `template<typename T, typename... ArgTypes> TArrayView<T> EmplaceArray(int32 Count, const ArgTypes&... Args);` — Allocate memory for an array of objects and initialize each object with the provided arguments. Objects created by this call will have their constructor and destructor called.
- L88 _public prototype_ `void BatchDelete();` — Activates a new allocator and deletes all commands and objects in the least recently touched scratch buffer.
- L89 _public prototype_ `constexpr static int32 MaxAllocationSize();`
- L99 _private member_ `MemoryAllocator Allocators[3];`
- L100 _private member_ `std::atomic<MemoryAllocator*> CurrentAllocator;`
- L101 _private member_ `MemoryAllocator* PreviousAllocator;`
- L102 _private member_ `MemoryAllocator* LeastRecentAllocator;`
- L106 _function_ `template<typename T, FScratchBuffer::ERequiresTrivialDestructor RequiresTrivialDestructors> T* FScratchBuffer::AllocateUninitialized()`
- L117 _function_ `template<typename T, FScratchBuffer::ERequiresTrivialDestructor RequiresTrivialDestructors> TArrayView<T> FScratchBuffer::AllocateUninitializedArray(int32 Count)`
- L129 _function_ `template<typename T, FScratchBuffer::ERequiresTrivialDestructor RequiresTrivialDestructors> T* FScratchBuffer::AllocateZeroInitialized()`
- L140 _function_ `template<typename T, FScratchBuffer::ERequiresTrivialDestructor RequiresTrivialDestructors> TArrayView<T> FScratchBuffer::AllocateZeroInitializedArray(int32 Count)`
- L152 _function_ `template<typename T, typename... ArgTypes> T* FScratchBuffer::Emplace(ArgTypes... Args)`
- L158 _function_ `template<typename T, typename... ArgTypes> TArrayView<T> FScratchBuffer::EmplaceArray(int32 Count, const ArgTypes&... Args)`
- L164 _function_ `constexpr int32 FScratchBuffer::MaxAllocationSize()`

#### struct `UE::Editor::DataStorage::FScratchBuffer::FAllocationTag`  
`struct FAllocationTag`  
_L16-25_
- L18 _public member_ `static constexpr uint32 BlockSize = 64 * 1024;` — Blocksize used to allocate from
- L19 _public member_ `static constexpr bool AllowOversizedBlocks = true;` — The allocator supports oversized Blocks and will store them in a separate Block with counter 1
- L20 _public member_ `static constexpr bool RequiresAccurateSize = false;` — GetAllocationSize returning the accurate size of the allocation otherwise it could be relaxed to return the size to the end of the Block
- L21 _public member_ `static constexpr bool InlineBlockAllocation = true;` — Inline or Noinline the BlockAllocation which can have an impact on Performance
- L22 _public member_ `static constexpr const char* TagName = "Te`
- L24 _public typedef_ `using Allocator = TBlockAllocationLockFreeCache<BlockSize, FAlignedAllocator>;`

#### enum `UE::Editor::DataStorage::FScratchBuffer::ERequiresTrivialDestructor`  
`enum class ERequiresTrivialDestructor : bool`  
_L30-34_
- desc: Whether or not functions that do not handle destruction of typed objects allow classes with non-trivial destructor.
- L32 _public enumerator_ `Yes`
- L33 _public enumerator_ `No`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementDatabaseUI.h` (Private)


#### class `UEditorDataStorageUi`  
`class UEditorDataStorageUi final : public UObject , public UE::Editor::DataStorage::IUiProvider`  
_L27-212_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Editor::DataStorage::IUiProvider`
- L34 _public prototype_ `~UEditorDataStorageUi() override = default;`
- L36 _public prototype_ `void Initialize( UE::Editor::DataStorage::ICoreProvider* StorageInterface, UE::Editor::DataStorage::ICompatibilityProvider* StorageCompatibilityInterface);`
- L39 _public prototype_ `void PostInitialize( UE::Editor::DataStorage::ICoreProvider* StorageInterface, UE::Editor::DataStorage::ICompatibilityProvider* StorageCompatibilityInterface);`
- L42 _public prototype_ `void Deinitialize();`
- L44 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle RegisterWidgetPurpose(const FPurposeID& PurposeID, const FPurposeInfo& InPurposeInfo) override;`
- L45 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle RegisterWidgetPurpose(const FPurposeInfo& InPurposeInfo) override;`
- L47 _public prototype_ `virtual bool RegisterWidgetFactory(UE::Editor::DataStorage::RowHandle PurposeRow, const UScriptStruct* Constructor) override;`
- L48 _public prototype_ `virtual bool RegisterWidgetFactory(UE::Editor::DataStorage::RowHandle PurposeRow, const UScriptStruct* Constructor, UE::Editor::DataStorage::Queries::FConditions Columns) override;`
- L50 _public prototype_ `virtual bool RegisterDecoratorWidgetFactory(UE::Editor::DataStorage::RowHandle PurposeRow, const UScriptStruct* Constructor, const UScriptStruct* Column) override;`
- L53 _public prototype_ `virtual void CreateWidgetConstructors(UE::Editor::DataStorage::RowHandle PurposeRow, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetConstructionCallback& Callback) override;`
- L55 _public prototype_ `virtual void CreateWidgetConstructors(UE::Editor::DataStorage::RowHandle PurposeRow, EMatchApproach MatchApproach, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetConstructionCallback& Callback) override;`
- L57 _public prototype_ `virtual void ConstructWidgets(UE::Editor::DataStorage::RowHandle PurposeRow, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetCreatedCallback& ConstructionCallback) override;`
- L62 _public prototype_ `virtual void CreateWidgetConstructors(UE::Editor::DataStorage::RowHandle PurposeRow, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) override;` — Deprecated functions
- L66 _public prototype_ `virtual bool RegisterWidgetFactory(UE::Editor::DataStorage::RowHandle PurposeRow, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor) override;`
- L68 _public prototype_ `virtual bool RegisterWidgetFactory(UE::Editor::DataStorage::RowHandle PurposeRow, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor, UE::Editor::DataStorage::Queries::FConditions Columns) override;`
- L70 _public prototype_ `void RegisterWidgetPurpose(FName Purpose, EPurposeType Type, FText Description) override;`
- L71 _public prototype_ `bool RegisterWidgetFactory(FName Purpose, const UScriptStruct* Constructor) override;`
- L72 _public prototype_ `bool RegisterWidgetFactory(FName Purpose, const UScriptStruct* Constructor, UE::Editor::DataStorage::Queries::FConditions Columns) override;`
- L74 _public prototype_ `bool RegisterWidgetFactory(FName Purpose, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor) override;`
- L75 _public prototype_ `bool RegisterWidgetFactory(FName Purpose, TUniquePtr<FTypedElementWidgetConstructor>&& Constructor, UE::Editor::DataStorage::Queries::FConditions Columns) override;`
- L77 _public prototype_ `void CreateWidgetConstructors(FName Purpose, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) override;`
- L79 _public prototype_ `void CreateWidgetConstructors(FName Purpose, EMatchApproach MatchApproach, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetConstructorCallback& Callback) override;`
- L81 _public prototype_ `void ConstructWidgets(FName Purpose, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetCreatedCallback& ConstructionCallback) override;`
- L86 _public prototype_ `TSharedPtr<SWidget> ConstructWidget(UE::Editor::DataStorage::RowHandle Row, FTypedElementWidgetConstructor& Constructor, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L89 _public prototype_ `virtual TSharedPtr<SWidget> ConstructInternalWidget(UE::Editor::DataStorage::RowHandle Row, FTypedElementWidgetConstructor& Constructor, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L92 _public prototype_ `void ListWidgetPurposes(const WidgetPurposeCallback& Callback) const override;`
- L94 _public prototype_ `bool SupportsExtension(FName Extension) const override;`
- L95 _public prototype_ `void ListExtensions(TFunctionRef<void(FName)> Callback) const override;`
- L98 _public prototype_ `virtual TSharedPtr<UE::Editor::DataStorage::ITedsWidget> CreateContainerTedsWidget(UE::Editor::DataStorage::RowHandle UiRowHandle) const override;` — Create the container widget that every TEDS UI widget is stored in
- L101 _public prototype_ `virtual UE::Editor::DataStorage::TableHandle GetWidgetTable() const override;` — Get the table where TEDS UI widgets are stored
- L103 _public prototype_ `virtual void GeneratePropertySearchers(TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>>& Results, TArrayView<TWeakObjectPtr<const UScriptStruct>> Columns) const override;`
- L106 _public prototype_ `virtual void RegisterSearcherGeneratorForProperty(const FFieldClass* PropertyType, PropertySearcherConstructorCallback PropertySearcherConstructor) override;`
- L109 _public prototype_ `virtual void UnregisterSearcherGeneratorForProperty(const FFieldClass* PropertyType) override;`
- L111 _public prototype_ `virtual void GeneratePropertySorters(TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>>& Results, TArrayView<TWeakObjectPtr<const UScriptStruct>> Columns) const override;`
- L114 _public prototype_ `virtual void RegisterSorterGeneratorForProperty(const FFieldClass* PropertyType, PropertySorterConstructorCallback PropertySorterConstructor) override;`
- L117 _public prototype_ `virtual void UnregisterSorterGeneratorForProperty(const FFieldClass* PropertyType) override;`
- L120 _public prototype_ `virtual FPurposeID GetDefaultWidgetPurposeID() const;` — Get the ID of the default TEDS UI widget purpose used to register default widgets for different types of data (e.g FText -> STextBlock)
- L123 _public prototype_ `virtual FPurposeID GetGeneralWidgetPurposeID() const;` — Get the ID of the general TEDS UI purpose used to register general purpose widgets for columns
- L125 _public prototype_ `virtual UE::Editor::DataStorage::FHierarchyHandle GetWidgetPurposeHierarchyHandle() const override;`
- L128 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle FindPurpose(const FPurposeID& PurposeID) const override;` — Find the row handle for a purpose by looking it up using the purpose ID
- L131 _private prototype_ `void CreateStandardArchetypes();`
- L132 _private prototype_ `void RegisterQueries();`
- L133 _private prototype_ `void RegisterHierarchies();`
- L134 _private prototype_ `void PostDataStorageUpdate();`
- L136 _private typedef_ `using FWidgetConstructionMethod = TFunction<bool(UE::Editor::DataStorage::RowHandle, TArray<TWeakObjectPtr<const UScriptStruct>>)>;`
- L138 _private prototype_ `bool CreateSingleWidgetConstructor( UE::Editor::DataStorage::RowHandle FactoryRow, const UE::Editor::DataStorage::FMetaDataView& Arguments, TArray<TWeakObjectPtr<const UScriptStruct>> MatchedColumnTypes, const WidgetConstructionCallback& Callback);`
- L144 _private prototype_ `void CreateWidgetInstance( FTypedElementWidgetConstructor& Constructor, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetCreatedCallback& ConstructionCallback);`
- L149 _private prototype_ `void CreateWidgetInstance( const UScriptStruct* ConstructorType, const UE::Editor::DataStorage::FMetaDataView& Arguments, const WidgetCreatedCallback& ConstructionCallback);`
- L154 _private prototype_ `bool CreateWidgetConstructors_LongestMatch( const TArray<UE::Editor::DataStorage::RowHandle>& WidgetFactories, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, FWidgetConstructionMethod ConstructionFunction);`
- L159 _private prototype_ `void CreateWidgetConstructors_ExactMatch( const TArray<UE::Editor::DataStorage::RowHandle>& WidgetFactories, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, FWidgetConstructionMethod ConstructionFunction);`
- L164 _private prototype_ `void CreateWidgetConstructors_SingleMatch( const TArray<UE::Editor::DataStorage::RowHandle>& WidgetFactories, TArray<TWeakObjectPtr<const UScriptStruct>>& Columns, FWidgetConstructionMethod ConstructionFunction);`
- L169 _private prototype_ `TSharedPtr<FTedsDecoratorWidgetConstructor> CreateSingleDecoratorWidget( UE::Editor::DataStorage::RowHandle FactoryRow, const UE::Editor::DataStorage::FMetaDataView& Arguments, TArray<TWeakObjectPtr<const UScriptStruct>> MatchedColumnTypes);`
- L175 _private prototype_ `UE::Editor::DataStorage::RowHandle RegisterWidgetFactoryRow(UE::Editor::DataStorage::RowHandle PurposeRowHandle, bool bDecoratorWidgetFactory = false) const;` — Register a widget factory for the provided purpose
- L178 _private prototype_ `UE::Editor::DataStorage::RowHandle RegisterUniqueWidgetFactoryRow(UE::Editor::DataStorage::RowHandle PurposeRowHandle, bool bDecoratorWidgetFactory = false) const;` — Register a unique factory for the provided purpose, clearing the info if there was any factory previously registered for the purpose
- L181 _private prototype_ `void GetWidgetFactories(UE::Editor::DataStorage::RowHandle PurposeRowHandle, TArray<UE::Editor::DataStorage::RowHandle>& OutFactories) const;` — Get all (non-decorator) factories for the provided purpose
- L184 _private prototype_ `void GetDecoratorWidgetFactories(UE::Editor::DataStorage::RowHandle PurposeRowHandle, TArray<UE::Editor::DataStorage::RowHandle>& OutFactories) const;` — Get all decorator factories for the provided purpose
- L187 _private prototype_ `const UE::Editor::DataStorage::Queries::FConditions& GetFactoryConditions(UE::Editor::DataStorage::RowHandle FactoryRow) const;` — The query conditions for the provided factory
- L190 _private prototype_ `TSharedPtr<SWidget> CreateDecoratorWidgets(UE::Editor::DataStorage::RowHandle WidgetRowHandle, TSharedPtr<SWidget> InternalWidget, FTypedElementWidgetConstructor& Constructor, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Create decorator widgets for the given TEDS UI widget
- L193 _private prototype_ `void RegisterDecoratorWidgetObservers(UE::Editor::DataStorage::RowHandle PurposeRowHandle, const UScriptStruct* DecoratorColumn);` — Register observers for the given decorator + purpose combo to automatically add/remove the decorator widget when the column is added/removed from widget rows
- L195 _private member_ `TMap<const FFieldClass*, PropertySorterConstructorCallback> PropertySorterConstructors;`
- L196 _private member_ `TMap<const FFieldClass*, PropertySearcherConstructorCallback> PropertySearcherConstructors;`
- L198 _private member_ `UE::Editor::DataStorage::TableHandle WidgetTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L199 _private member_ `UE::Editor::DataStorage::TableHandle WidgetPurposeTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L200 _private member_ `UE::Editor::DataStorage::TableHandle WidgetFactoryTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L201 _private member_ `UE::Editor::DataStorage::TableHandle DecoratorWidgetFactoryTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L203 _private member_ `UE::Editor::DataStorage::ICoreProvider* Storage{ nullptr };`
- L204 _private member_ `UE::Editor::DataStorage::ICompatibilityProvider* StorageCompatibility{ nullptr };`
- L206 _private member_ `TArray<UE::Editor::DataStorage::QueryHandle> DecoratorObservers;`
- L209 _private member_ `TSet<UE::Editor::DataStorage::RowHandle> WidgetsToUpdateDecorators;` — Widget rows that need their decorators updated
- L211 _private member_ `UE::Editor::DataStorage::FHierarchyHandle WidgetPurposesHierarchyHandle;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TEDSCORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorDataStorageUI, Log, All);`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementHandleStore.h` (Private)


#### class `UE::Editor::DataStorage::THandleStore`  
`template<typename DataType, uint32 ReservationSize = 64> class THandleStore`  
_L14-85_
- L56 _public typedef_ `using ListAliveEntriesConstCallback = TFunctionRef<void(Handle, const DataType&)>;`
- L57 _public typedef_ `using ListAliveEntriesCallback = TFunctionRef<void(Handle, DataType&)>;`
- L59 _public prototype_ `THandleStore() = default;`
- L60 _public prototype_ `~THandleStore();`
- L61 _public prototype_ `THandleStore(const THandleStore&) = delete;`
- L62 _public prototype_ `THandleStore(THandleStore&&) = delete;`
- L63 _public prototype_ `THandleStore& operator=(const THandleStore&) = delete;`
- L64 _public prototype_ `THandleStore& operator=(THandleStore&&) = delete;`
- L67 _public prototype_ `template<typename... Args> Handle Emplace(Args... Arguments);`
- L69 _public prototype_ `DataType& Get(Handle Entry);`
- L70 _public prototype_ `DataType& GetMutable(Handle Entry);`
- L71 _public prototype_ `const DataType& Get(Handle Entry) const;`
- L74 _public prototype_ `void Remove(Handle Entry);` — Removes the entry at the given handle if alive.
- L76 _public prototype_ `bool IsAlive(Handle Entry) const;`
- L77 _public prototype_ `void ListAliveEntries(const ListAliveEntriesConstCallback& Callback) const;`
- L78 _public prototype_ `void ListAliveEntries(const ListAliveEntriesConstCallback& Callback);`
- L79 _public prototype_ `void ListAliveEntries(const ListAliveEntriesCallback& Callback);`
- L82 _private member_ `TArray<DataType> Data;`
- L83 _private member_ `TArray<FGeneration> Generations;`
- L84 _private member_ `TDeque<uint32> RecycleBin;` — Using a deque to avoid the same slot being constantly reused.
- L91 _function_ `template<typename DataType, uint32 ReservationSize> THandleStore<DataType, ReservationSize>::~THandleStore()` — Implementations
- L115 _function_ `template<typename DataType, uint32 ReservationSize> template<typename... Args> auto THandleStore<DataType, ReservationSize>::Emplace(Args... Arguments) -> Handle`
- L143 _function_ `template<typename DataType, uint32 ReservationSize> DataType& THandleStore<DataType, ReservationSize>::Get(Handle Entry)`
- L150 _function_ `template<typename DataType, uint32 ReservationSize> DataType& THandleStore<DataType, ReservationSize>::GetMutable(Handle Entry)`
- L157 _function_ `template<typename DataType, uint32 ReservationSize> const DataType& THandleStore<DataType, ReservationSize>::Get(Handle Entry) const`
- L164 _function_ `template<typename DataType, uint32 ReservationSize> void THandleStore<DataType, ReservationSize>::Remove(Handle Entry)`
- L180 _function_ `template<typename DataType, uint32 ReservationSize> bool THandleStore<DataType, ReservationSize>::IsAlive(Handle Entry) const`
- L188 _function_ `template<typename DataType, uint32 ReservationSize> void THandleStore<DataType, ReservationSize>::ListAliveEntries(const ListAliveEntriesConstCallback& Callback) const`
- L208 _function_ `template<typename DataType, uint32 ReservationSize> void THandleStore<DataType, ReservationSize>::ListAliveEntries(const ListAliveEntriesConstCallback& Callback)`
- L214 _function_ `template<typename DataType, uint32 ReservationSize> void THandleStore<DataType, ReservationSize>::ListAliveEntries(const ListAliveEntriesCallback& Callback)`

#### struct `UE::Editor::DataStorage::THandleStore::FGeneration`  
`struct FGeneration`  
_L17-21_
- L19 _public member_ `uint32 Generation : 31;`
- L20 _public member_ `uint32 bIsAlive : 1;`

#### class `UE::Editor::DataStorage::THandleStore::Handle`  
`class Handle`  
_L23-54_
- L26 _public prototype_ `Handle() = default;`
- L27 _public function_ `explicit Handle(uint64 InPackedData) : PackedData(InPackedData)`
- L31 _public function_ `Handle(uint32 Index, uint32 Generation)`
- L36 _public function_ `uint64 Packed() const`
- L41 _public function_ `uint32_t Generation() const`
- L46 _public function_ `uint32_t Index() const`
- L53 _private member_ `uint64 PackedData = TNumericLimits<uint64>::Max();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/TypedElementUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _prototype_ `inline FMassEntityHandle RowToMassEntityConversion(RowHandle Row);` (scope `UE::Editor::DataStorage`)
- L12 _prototype_ `inline RowHandle MassEntityToRowConversion(FMassEntityHandle Entity);` (scope `UE::Editor::DataStorage`)
- L14 _prototype_ `inline TConstArrayView<FMassEntityHandle> RowsToMassEntitiesConversion(TConstArrayView<RowHandle> Rows);` (scope `UE::Editor::DataStorage`)
- L15 _prototype_ `inline TArrayView<FMassEntityHandle> RowsToMassEntitiesConversion(TArrayView<RowHandle> Rows);` (scope `UE::Editor::DataStorage`)
- L16 _prototype_ `inline TConstArrayView<RowHandle> MassEntitiesToRowsConversion(TConstArrayView<FMassEntityHandle> Entities);` (scope `UE::Editor::DataStorage`)
- L17 _prototype_ `inline TArrayView<RowHandle> MassEntitiesToRowsConversion(TArrayView<FMassEntityHandle> Entities);` (scope `UE::Editor::DataStorage`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L23 _function_ `FMassEntityHandle RowToMassEntityConversion(RowHandle Row)` (scope `UE::Editor::DataStorage`)
- L28 _function_ `RowHandle MassEntityToRowConversion(FMassEntityHandle Entity)` (scope `UE::Editor::DataStorage`)
- L33 _function_ `TConstArrayView<FMassEntityHandle> RowsToMassEntitiesConversion(TConstArrayView<RowHandle> Rows)` (scope `UE::Editor::DataStorage`)
- L38 _function_ `TArrayView<FMassEntityHandle> RowsToMassEntitiesConversion(TArrayView<RowHandle> Rows)` (scope `UE::Editor::DataStorage`)
- L43 _function_ `TConstArrayView<RowHandle> MassEntitiesToRowsConversion(TConstArrayView<FMassEntityHandle> Entities)` (scope `UE::Editor::DataStorage`)
- L48 _function_ `TArrayView<RowHandle> MassEntitiesToRowsConversion(TArrayView<FMassEntityHandle> Entities)` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/Widgets/STedsWidget.h` (Private)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<UE::Editor::DataStorage::Widgets::STedsWidget>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `UE::Editor::DataStorage::Widgets::STedsWidget`  
`class STedsWidget : public SCompoundWidget, public UE::Editor::DataStorage::ITedsWidget`  
_L38-74_
- inherits: `SCompoundWidget,UE::Editor::DataStorage::ITedsWidget`
- desc: All Teds widgets will be contained inside STedsWidget which acts like a container widget so we can have guaranteed access to the contents inside to dynamically update them if required. This widget is created and returned for any Teds widget requested for a row, regardless of if the actual internal widget exists or not. Currently this is simply an SCompoundWidget
- L42 _public function_ `SLATE_BEGIN_ARGS(STedsWidget) : _UiRowHandle(UE::Editor::DataStorage::InvalidRowHandle) , _Content()`
- L49 _public prototype_ `SLATE_ARGUMENT(UE::Editor::DataStorage::RowHandle, UiRowHandle) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The UI Row this widget will be assigned to
- L58 _public prototype_ `virtual void SetContent(const TSharedRef< SWidget >& InContent) override;`
- L60 _public prototype_ `virtual UE::Editor::DataStorage::RowHandle GetRowHandle() const override;`
- L62 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() override;`
- L66 _private prototype_ `void RegisterTedsWidget(const TSharedPtr<SWidget>& InContentWidget);`
- L68 _private prototype_ `static ICoreProvider* GetStorageIfAvailable();`
- L69 _private prototype_ `static IUiProvider* GetStorageUiIfAvailable();`
- L73 _private member_ `RowHandle UiRowHandle = InvalidRowHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace Widgets` (scope `UE::Editor::DataStorage`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Editor` (scope `UE`)
- L28 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L28 _namespace_ `namespace Widgets` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Public/Memento/TypedElementMementoTranslators.h` (Public)


#### class `UTedsMementoTranslatorBase`  
`class UTedsMementoTranslatorBase : public UObject`  
_L13-54_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: A MementoTranslator is used to convert columns of data to mementos and back again Mementos are special types of columns that hold a subset of column data for dehydrating a row.  This can be useful for reinstancing, undo/redo, LODs, etc.
- L20 _public function_ `virtual const UScriptStruct* GetColumnType() const` — The type information of the column that this translator acts on
- L29 _public function_ `virtual const UScriptStruct* GetMementoType() const` — Type information for the memento
- L38 _public prototype_ `virtual void TranslateColumnToMemento(const void* TypeErasedColumn, void* TypeErasedMemento) const PURE_VIRTUAL(UTedsMementoTranslatorBase, ) virtual void TranslateMementoToColumn(const void* TypeErasedMemento, void* TypeErasedColumn) const PURE_VIRTUAL(UTedsMementoTranslatorBase, ) const UScriptStruct* GetColumnToAddOnRestore() const;` — Implements the logic to convert a column to a memento
- L53 _protected member_ `TObjectPtr<const UScriptStruct> ColumnToAddOnRestore = nullptr;` — `UPROPERTY()` — Optional column that will be added to the object row after the memento is restored

#### class `UTedsDefaultMementoTranslator`  
`class UTedsDefaultMementoTranslator : public UTedsMementoTranslatorBase`  
_L85-106_
- reflection: `UCLASS(Abstract)`
- inherits: `UTedsMementoTranslatorBase`
- desc: Turn-key translator to convert columns to mementos and back Creates a new struct that has the same UPROPERTIES the ColumnType To opt-in a column to be mementoized, override the GetColumnType with the column that should be mementoized As an example, suppose there was a column defined as: ``` USTRUCT() struct FPathColumn : public FEditorDataStorageColumn { GENERATED_BODY() UPROPERTY() FString Path; }; ``` To opt into a default memento translator for FPathColumn, define a default translator: ``` UCLASS() class UTypedElementPathColumnTranslator : public UTypedElementDefaultMementoTranslator { virtual const UScriptStruct* GetColumnType() const override { return FPathColumn::StaticStruct; } }; ``` The system will take care of doing the required operations when rows are deleted that that have both FTypedElementMementoOnDelete and FPathColumn columns
- L92 _public function_ `virtual const UScriptStruct* GetColumnType() const override` — Override this in derived classes to get automatic mementoization of the given column
- L93 _public prototype_ `virtual const UScriptStruct* GetMementoType() const final override;`
- L95 _public prototype_ `virtual void PostInitProperties() final override;`
- L97 _public prototype_ `virtual void TranslateColumnToMemento(const void* Column, void* Memento) const final override;`
- L98 _public prototype_ `virtual void TranslateMementoToColumn(const void* TypeErasedMemento, void* TypeErasedColumn) const final override;`
- L102 _private member_ `TObjectPtr<const UScriptStruct> MementoType = nullptr;` — `UPROPERTY()`
- L104 _private member_ `TArray<const FProperty*> MementoizedColumnProperties;`
- L105 _private member_ `TArray<const FProperty*> MementoProperties;`

### `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Public/TypedElementsDataStorage.h` (Public)


#### class `FEditorDataStorageModule`  
`class FEditorDataStorageModule : public IModuleInterface, public FGCObject`  
_L16-42_
- inherits: `IModuleInterface,FGCObject`
- L19 _public prototype_ `~FEditorDataStorageModule() override = default;`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L34 _public prototype_ `FString GetReferencerName() const override;`
- L37 _private member_ `TObjectPtr<UEditorDataStorage> DataStorage;`
- L38 _private member_ `TObjectPtr<UEditorDataStorageCompatibility> DataStorageCompatibility;`
- L39 _private member_ `TObjectPtr<UEditorDataStorageUi> DataStorageUi;`
- L40 _private member_ `TObjectPtr<UTedsObjectReinstancingManager> ObjectReinstancingManager;`
- L41 _private member_ `bool bInitialized{ false };`
