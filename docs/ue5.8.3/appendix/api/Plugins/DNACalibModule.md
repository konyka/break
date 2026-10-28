# Plugins / DNACalibModule

- module root: `Plugins/Animation/DNACalib/Source/DNACalibModule`
- headers: 30; symbols: 513
- symbol kinds: class=27, enum=1, enumerator=4, function=11, macro=2, member=28, prototype=438, struct=1, typedef=1
- PrivateDependencyModuleNames: DNACalibLib, RigLogicLib
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RigLogicModule, UnrealEd

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Private/DNACalibUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `template<typename TContainer> dnac::ConstArrayView<typename TContainer::ElementType> ViewOf(const TContainer& Source)`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Private/VecArray.h` (Private)


#### struct `FVecArray`  
`struct FVecArray`  
_L9-79_
- L11 _public member_ `TArray<float> Xs;`
- L12 _public member_ `TArray<float> Ys;`
- L13 _public member_ `TArray<float> Zs;`
- L15 _public prototype_ `FVecArray() = default;`
- L18 _public function_ `template<typename TVec> FVecArray(TArrayView<TVec> Source)`
- L24 _public function_ `template<typename T> FVecArray(TArrayView<T> SourceXs, TArrayView<T> SourceYs, TArrayView<T> SourceZs)`
- L29 _public function_ `int Num()`
- L35 _public function_ `void Empty()`
- L42 _public function_ `void Reserve(int Number)`
- L49 _public function_ `void AddUninitialized(int Count)`
- L57 _public function_ `template<typename TVec> void Assign(TArrayView<TVec> Source)`
- L70 _public function_ `template<typename T> void Assign(TArrayView<T> SourceXs, TArrayView<T> SourceYs, TArrayView<T> SourceZs)`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibCalculateMeshLowerLODsCommand.h` (Public)


#### class `FDNACalibCalculateMeshLowerLODsCommand`  
`class FDNACalibCalculateMeshLowerLODsCommand : public IDNACalibCommand`  
_L13-32_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibCalculateMeshLowerLODsCommand();`
- L16 _public prototype_ `FDNACalibCalculateMeshLowerLODsCommand(uint16 MeshIndex);`
- L18 _public prototype_ `~FDNACalibCalculateMeshLowerLODsCommand();`
- L20 _public prototype_ `FDNACalibCalculateMeshLowerLODsCommand(const FDNACalibCalculateMeshLowerLODsCommand&) = delete;`
- L21 _public prototype_ `FDNACalibCalculateMeshLowerLODsCommand& operator=(const FDNACalibCalculateMeshLowerLODsCommand&) = delete;`
- L23 _public prototype_ `FDNACalibCalculateMeshLowerLODsCommand(FDNACalibCalculateMeshLowerLODsCommand&&);`
- L24 _public prototype_ `FDNACalibCalculateMeshLowerLODsCommand& operator=(FDNACalibCalculateMeshLowerLODsCommand&&);`
- L26 _public prototype_ `void SetMeshIndex(uint16 MeshIndex);`
- L27 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L31 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibClearBlendShapesCommand.h` (Public)


#### class `FDNACalibClearBlendShapesCommand`  
`class FDNACalibClearBlendShapesCommand : public IDNACalibCommand`  
_L13-30_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibClearBlendShapesCommand();`
- L17 _public prototype_ `~FDNACalibClearBlendShapesCommand();`
- L19 _public prototype_ `FDNACalibClearBlendShapesCommand(const FDNACalibClearBlendShapesCommand&) = delete;`
- L20 _public prototype_ `FDNACalibClearBlendShapesCommand& operator=(const FDNACalibClearBlendShapesCommand&) = delete;`
- L22 _public prototype_ `FDNACalibClearBlendShapesCommand(FDNACalibClearBlendShapesCommand&&);`
- L23 _public prototype_ `FDNACalibClearBlendShapesCommand& operator=(FDNACalibClearBlendShapesCommand&&);`
- L25 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L29 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibCommandSequence.h` (Public)


#### class `FDNACalibCommandSequence`  
`class FDNACalibCommandSequence : public IDNACalibCommand`  
_L13-56_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibCommandSequence();`
- L16 _public prototype_ `~FDNACalibCommandSequence();`
- L18 _public prototype_ `FDNACalibCommandSequence(const FDNACalibCommandSequence&) = delete;`
- L19 _public prototype_ `FDNACalibCommandSequence& operator=(const FDNACalibCommandSequence&) = delete;`
- L21 _public prototype_ `FDNACalibCommandSequence(FDNACalibCommandSequence&&);`
- L22 _public prototype_ `FDNACalibCommandSequence& operator=(FDNACalibCommandSequence&&);`
- L24 _public prototype_ `void Add(IDNACalibCommand* Command);`
- L25 _public prototype_ `void Add(TArrayView<IDNACalibCommand> Commands);`
- L28 _public function_ `template<class ... TCommands> void Add(TCommands... Commands)`
- L36 _public prototype_ `void Remove(IDNACalibCommand* Command);`
- L37 _public prototype_ `void Remove(TArrayView<IDNACalibCommand> Commands);`
- L40 _public function_ `template<class ... TCommands> void Remove(TCommands... Commands)`
- L48 _public prototype_ `bool Contains(IDNACalibCommand* Command) const;`
- L49 _public prototype_ `size_t Size() const;`
- L51 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L55 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibComputeVertexPositionDeltasCommand.h` (Public)


#### class `FDNACalibComputeVertexPositionDeltasCommand`  
`class FDNACalibComputeVertexPositionDeltasCommand : public IDNACalibCommand`  
_L15-36_
- inherits: `IDNACalibCommand`
- L17 _public prototype_ `FDNACalibComputeVertexPositionDeltasCommand();`
- L18 _public prototype_ `FDNACalibComputeVertexPositionDeltasCommand(IDNAReader* ReaderA, IDNAReader* ReaderB);`
- L20 _public prototype_ `~FDNACalibComputeVertexPositionDeltasCommand();`
- L22 _public prototype_ `FDNACalibComputeVertexPositionDeltasCommand(const FDNACalibComputeVertexPositionDeltasCommand&) = delete;`
- L23 _public prototype_ `FDNACalibComputeVertexPositionDeltasCommand& operator=(const FDNACalibComputeVertexPositionDeltasCommand&) = delete;`
- L25 _public prototype_ `FDNACalibComputeVertexPositionDeltasCommand(FDNACalibComputeVertexPositionDeltasCommand&&);`
- L26 _public prototype_ `FDNACalibComputeVertexPositionDeltasCommand& operator=(FDNACalibComputeVertexPositionDeltasCommand&&);`
- L28 _public prototype_ `void SetReaderA(IDNAReader* Reader);`
- L29 _public prototype_ `void SetReaderB(IDNAReader* Reader);`
- L31 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L35 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibConditionalCommand.h` (Public)


#### class `FDNACalibConditionalCommand`  
`class FDNACalibConditionalCommand : public IDNACalibCommand`  
_L13-37_
- inherits: `IDNACalibCommand`
- L15 _public typedef_ `using TCondition = TFunction<bool(IDNACalibCommand*, FDNACalibDNAReader*)>;`
- L18 _public prototype_ `FDNACalibConditionalCommand();`
- L19 _public prototype_ `FDNACalibConditionalCommand(IDNACalibCommand* Command, TCondition Condition);`
- L21 _public prototype_ `~FDNACalibConditionalCommand();`
- L23 _public prototype_ `FDNACalibConditionalCommand(const FDNACalibConditionalCommand&) = delete;`
- L24 _public prototype_ `FDNACalibConditionalCommand& operator=(const FDNACalibConditionalCommand&) = delete;`
- L26 _public prototype_ `FDNACalibConditionalCommand(FDNACalibConditionalCommand&&);`
- L27 _public prototype_ `FDNACalibConditionalCommand& operator=(FDNACalibConditionalCommand&&);`
- L29 _public prototype_ `void SetCommand(IDNACalibCommand* Command);`
- L30 _public prototype_ `void SetCondition(TCondition Condition);`
- L32 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L36 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibPruneBlendShapeTargetsCommand.h` (Public)


#### class `FDNACalibPruneBlendShapeTargetsCommand`  
`class FDNACalibPruneBlendShapeTargetsCommand : public IDNACalibCommand`  
_L13-32_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibPruneBlendShapeTargetsCommand();`
- L16 _public prototype_ `FDNACalibPruneBlendShapeTargetsCommand(float Threshold);`
- L18 _public prototype_ `~FDNACalibPruneBlendShapeTargetsCommand();`
- L20 _public prototype_ `FDNACalibPruneBlendShapeTargetsCommand(const FDNACalibPruneBlendShapeTargetsCommand&) = delete;`
- L21 _public prototype_ `FDNACalibPruneBlendShapeTargetsCommand& operator=(const FDNACalibPruneBlendShapeTargetsCommand&) = delete;`
- L23 _public prototype_ `FDNACalibPruneBlendShapeTargetsCommand(FDNACalibPruneBlendShapeTargetsCommand&&);`
- L24 _public prototype_ `FDNACalibPruneBlendShapeTargetsCommand& operator=(FDNACalibPruneBlendShapeTargetsCommand&&);`
- L26 _public prototype_ `void SetThreshold(float Threshold);`
- L27 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L31 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRemoveAnimatedMapCommand.h` (Public)


#### class `FDNACalibRemoveAnimatedMapCommand`  
`class FDNACalibRemoveAnimatedMapCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRemoveAnimatedMapCommand();`
- L16 _public prototype_ `FDNACalibRemoveAnimatedMapCommand(uint16 AnimatedMapIndex);`
- L17 _public prototype_ `FDNACalibRemoveAnimatedMapCommand(TArrayView<uint16> AnimatedMapIndices);`
- L19 _public prototype_ `~FDNACalibRemoveAnimatedMapCommand();`
- L21 _public prototype_ `FDNACalibRemoveAnimatedMapCommand(const FDNACalibRemoveAnimatedMapCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRemoveAnimatedMapCommand& operator=(const FDNACalibRemoveAnimatedMapCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRemoveAnimatedMapCommand(FDNACalibRemoveAnimatedMapCommand&&);`
- L25 _public prototype_ `FDNACalibRemoveAnimatedMapCommand& operator=(FDNACalibRemoveAnimatedMapCommand&&);`
- L27 _public prototype_ `void SetAnimatedMapIndex(uint16 AnimatedMapIndex);`
- L28 _public prototype_ `void SetAnimatedMapIndices(TArrayView<uint16> AnimatedMapIndices);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRemoveBlendShapeCommand.h` (Public)


#### class `FDNACalibRemoveBlendShapeCommand`  
`class FDNACalibRemoveBlendShapeCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRemoveBlendShapeCommand();`
- L16 _public prototype_ `FDNACalibRemoveBlendShapeCommand(uint16 BlendShapeIndex);`
- L17 _public prototype_ `FDNACalibRemoveBlendShapeCommand(TArrayView<uint16> BlendShapeIndices);`
- L19 _public prototype_ `~FDNACalibRemoveBlendShapeCommand();`
- L21 _public prototype_ `FDNACalibRemoveBlendShapeCommand(const FDNACalibRemoveBlendShapeCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRemoveBlendShapeCommand& operator=(const FDNACalibRemoveBlendShapeCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRemoveBlendShapeCommand(FDNACalibRemoveBlendShapeCommand&&);`
- L25 _public prototype_ `FDNACalibRemoveBlendShapeCommand& operator=(FDNACalibRemoveBlendShapeCommand&&);`
- L27 _public prototype_ `void SetBlendShapeIndex(uint16 BlendShapeIndex);`
- L28 _public prototype_ `void SetBlendShapeIndices(TArrayView<uint16> BlendShapeIndices);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRemoveJointAnimationCommand.h` (Public)


#### class `FDNACalibRemoveJointAnimationCommand`  
`class FDNACalibRemoveJointAnimationCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRemoveJointAnimationCommand();`
- L16 _public prototype_ `FDNACalibRemoveJointAnimationCommand(uint16 JointIndex);`
- L17 _public prototype_ `FDNACalibRemoveJointAnimationCommand(TArrayView<uint16> JointIndices);`
- L19 _public prototype_ `~FDNACalibRemoveJointAnimationCommand();`
- L21 _public prototype_ `FDNACalibRemoveJointAnimationCommand(const FDNACalibRemoveJointAnimationCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRemoveJointAnimationCommand& operator=(const FDNACalibRemoveJointAnimationCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRemoveJointAnimationCommand(FDNACalibRemoveJointAnimationCommand&&);`
- L25 _public prototype_ `FDNACalibRemoveJointAnimationCommand& operator=(FDNACalibRemoveJointAnimationCommand&&);`
- L27 _public prototype_ `void SetJointIndex(uint16 JointIndex);`
- L28 _public prototype_ `void SetJointIndices(TArrayView<uint16> JointIndices);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRemoveJointCommand.h` (Public)


#### class `FDNACalibRemoveJointCommand`  
`class FDNACalibRemoveJointCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRemoveJointCommand();`
- L16 _public prototype_ `FDNACalibRemoveJointCommand(uint16 JointIndex);`
- L17 _public prototype_ `FDNACalibRemoveJointCommand(TArrayView<uint16> JointIndices);`
- L19 _public prototype_ `~FDNACalibRemoveJointCommand();`
- L21 _public prototype_ `FDNACalibRemoveJointCommand(const FDNACalibRemoveJointCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRemoveJointCommand& operator=(const FDNACalibRemoveJointCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRemoveJointCommand(FDNACalibRemoveJointCommand&&);`
- L25 _public prototype_ `FDNACalibRemoveJointCommand& operator=(FDNACalibRemoveJointCommand&&);`
- L27 _public prototype_ `void SetJointIndex(uint16 JointIndex);`
- L28 _public prototype_ `void SetJointIndices(TArrayView<uint16> JointIndices);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRemoveMeshCommand.h` (Public)


#### class `FDNACalibRemoveMeshCommand`  
`class FDNACalibRemoveMeshCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRemoveMeshCommand();`
- L16 _public prototype_ `FDNACalibRemoveMeshCommand(uint16 MeshIndex);`
- L17 _public prototype_ `FDNACalibRemoveMeshCommand(TArrayView<uint16> MeshIndices);`
- L19 _public prototype_ `~FDNACalibRemoveMeshCommand();`
- L21 _public prototype_ `FDNACalibRemoveMeshCommand(const FDNACalibRemoveMeshCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRemoveMeshCommand& operator=(const FDNACalibRemoveMeshCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRemoveMeshCommand(FDNACalibRemoveMeshCommand&&);`
- L25 _public prototype_ `FDNACalibRemoveMeshCommand& operator=(FDNACalibRemoveMeshCommand&&);`
- L27 _public prototype_ `void SetMeshIndex(uint16 MeshIndex);`
- L28 _public prototype_ `void SetMeshIndices(TArrayView<uint16> MeshIndices);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRenameAnimatedMapCommand.h` (Public)


#### class `FDNACalibRenameAnimatedMapCommand`  
`class FDNACalibRenameAnimatedMapCommand : public IDNACalibCommand`  
_L13-35_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRenameAnimatedMapCommand();`
- L16 _public prototype_ `FDNACalibRenameAnimatedMapCommand(uint16 AnimatedMapIndex, const FString& NewName);`
- L17 _public prototype_ `FDNACalibRenameAnimatedMapCommand(const FString& OldName, const FString& NewName);`
- L19 _public prototype_ `~FDNACalibRenameAnimatedMapCommand();`
- L21 _public prototype_ `FDNACalibRenameAnimatedMapCommand(const FDNACalibRenameAnimatedMapCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRenameAnimatedMapCommand& operator=(const FDNACalibRenameAnimatedMapCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRenameAnimatedMapCommand(FDNACalibRenameAnimatedMapCommand&&);`
- L25 _public prototype_ `FDNACalibRenameAnimatedMapCommand& operator=(FDNACalibRenameAnimatedMapCommand&&);`
- L27 _public prototype_ `void SetName(uint16 AnimatedMapIndex, const FString& NewName);`
- L28 _public prototype_ `void SetName(const FString& OldName, const FString& NewName);`
- L30 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L34 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRenameBlendShapeCommand.h` (Public)


#### class `FDNACalibRenameBlendShapeCommand`  
`class FDNACalibRenameBlendShapeCommand : public IDNACalibCommand`  
_L13-35_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRenameBlendShapeCommand();`
- L16 _public prototype_ `FDNACalibRenameBlendShapeCommand(uint16 BlendShapeIndex, const FString& NewName);`
- L17 _public prototype_ `FDNACalibRenameBlendShapeCommand(const FString& OldName, const FString& NewName);`
- L19 _public prototype_ `~FDNACalibRenameBlendShapeCommand();`
- L21 _public prototype_ `FDNACalibRenameBlendShapeCommand(const FDNACalibRenameBlendShapeCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRenameBlendShapeCommand& operator=(const FDNACalibRenameBlendShapeCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRenameBlendShapeCommand(FDNACalibRenameBlendShapeCommand&&);`
- L25 _public prototype_ `FDNACalibRenameBlendShapeCommand& operator=(FDNACalibRenameBlendShapeCommand&&);`
- L27 _public prototype_ `void SetName(uint16 BlendShapeIndex, const FString& NewName);`
- L28 _public prototype_ `void SetName(const FString& OldName, const FString& NewName);`
- L30 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L34 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRenameJointCommand.h` (Public)


#### class `FDNACalibRenameJointCommand`  
`class FDNACalibRenameJointCommand : public IDNACalibCommand`  
_L13-35_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRenameJointCommand();`
- L16 _public prototype_ `FDNACalibRenameJointCommand(uint16 JointIndex, const FString& NewName);`
- L17 _public prototype_ `FDNACalibRenameJointCommand(const FString& OldName, const FString& NewName);`
- L19 _public prototype_ `~FDNACalibRenameJointCommand();`
- L21 _public prototype_ `FDNACalibRenameJointCommand(const FDNACalibRenameJointCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRenameJointCommand& operator=(const FDNACalibRenameJointCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRenameJointCommand(FDNACalibRenameJointCommand&&);`
- L25 _public prototype_ `FDNACalibRenameJointCommand& operator=(FDNACalibRenameJointCommand&&);`
- L27 _public prototype_ `void SetName(uint16 JointIndex, const FString& NewName);`
- L28 _public prototype_ `void SetName(const FString& OldName, const FString& NewName);`
- L30 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L34 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRenameMeshCommand.h` (Public)


#### class `FDNACalibRenameMeshCommand`  
`class FDNACalibRenameMeshCommand : public IDNACalibCommand`  
_L13-35_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRenameMeshCommand();`
- L16 _public prototype_ `FDNACalibRenameMeshCommand(uint16 MeshIndex, const FString& NewName);`
- L17 _public prototype_ `FDNACalibRenameMeshCommand(const FString& OldName, const FString& NewName);`
- L19 _public prototype_ `~FDNACalibRenameMeshCommand();`
- L21 _public prototype_ `FDNACalibRenameMeshCommand(const FDNACalibRenameMeshCommand&) = delete;`
- L22 _public prototype_ `FDNACalibRenameMeshCommand& operator=(const FDNACalibRenameMeshCommand&) = delete;`
- L24 _public prototype_ `FDNACalibRenameMeshCommand(FDNACalibRenameMeshCommand&&);`
- L25 _public prototype_ `FDNACalibRenameMeshCommand& operator=(FDNACalibRenameMeshCommand&&);`
- L27 _public prototype_ `void SetName(uint16 MeshIndex, const FString& NewName);`
- L28 _public prototype_ `void SetName(const FString& OldName, const FString& NewName);`
- L30 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L34 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibRotateCommand.h` (Public)


#### class `FDNACalibRotateCommand`  
`class FDNACalibRotateCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibRotateCommand();`
- L16 _public prototype_ `FDNACalibRotateCommand(FVector Degrees, FVector Origin);`
- L18 _public prototype_ `~FDNACalibRotateCommand();`
- L20 _public prototype_ `FDNACalibRotateCommand(const FDNACalibRotateCommand&) = delete;`
- L21 _public prototype_ `FDNACalibRotateCommand& operator=(const FDNACalibRotateCommand&) = delete;`
- L23 _public prototype_ `FDNACalibRotateCommand(FDNACalibRotateCommand&&);`
- L24 _public prototype_ `FDNACalibRotateCommand& operator=(FDNACalibRotateCommand&&);`
- L26 _public prototype_ `void SetRotation(FVector Degrees);`
- L27 _public prototype_ `void SetOrigin(FVector Origin);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibScaleCommand.h` (Public)


#### class `FDNACalibScaleCommand`  
`class FDNACalibScaleCommand : public IDNACalibCommand`  
_L13-34_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibScaleCommand();`
- L16 _public prototype_ `FDNACalibScaleCommand(float Scale, FVector Origin);`
- L18 _public prototype_ `~FDNACalibScaleCommand();`
- L20 _public prototype_ `FDNACalibScaleCommand(const FDNACalibScaleCommand&) = delete;`
- L21 _public prototype_ `FDNACalibScaleCommand& operator=(const FDNACalibScaleCommand&) = delete;`
- L23 _public prototype_ `FDNACalibScaleCommand(FDNACalibScaleCommand&&);`
- L24 _public prototype_ `FDNACalibScaleCommand& operator=(FDNACalibScaleCommand&&);`
- L26 _public prototype_ `void SetScale(float Scale);`
- L27 _public prototype_ `void SetOrigin(FVector Origin);`
- L29 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L33 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibSetBlendShapeTargetDeltasCommand.h` (Public)


#### class `FDNACalibSetBlendShapeTargetDeltasCommand`  
`class FDNACalibSetBlendShapeTargetDeltasCommand : public IDNACalibCommand`  
_L14-43_
- inherits: `IDNACalibCommand`
- L16 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand();`
- L17 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand(uint16 MeshIndex, uint16 BlendShapeTargetIndex, TArrayView<const FVector> Deltas, TArrayView<const uint32> VertexIndices, EDNACalibVectorOperation Operation);`
- L18 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand(uint16 MeshIndex, uint16 BlendShapeTargetIndex, TArrayView<const float> DXs, TArrayView<const float> DYs, TArrayView<const float> DZs, TArrayView<const uint32> VertexIndices, EDNACalibVectorOperation Operation);`
- L19 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand(uint16 MeshIndex, uint16 BlendShapeTargetIndex, TArrayView<const FVector> Deltas, TArrayView<const uint32> VertexIndices, TArrayView<const float> Masks, EDNACalibVectorOperation Operation);`
- L22 _public prototype_ `~FDNACalibSetBlendShapeTargetDeltasCommand();`
- L24 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand(const FDNACalibSetBlendShapeTargetDeltasCommand&) = delete;`
- L25 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand& operator=(const FDNACalibSetBlendShapeTargetDeltasCommand&) = delete;`
- L27 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand(FDNACalibSetBlendShapeTargetDeltasCommand&&);`
- L28 _public prototype_ `FDNACalibSetBlendShapeTargetDeltasCommand& operator=(FDNACalibSetBlendShapeTargetDeltasCommand&&);`
- L30 _public prototype_ `void SetMeshIndex(uint16 MeshIndex);`
- L31 _public prototype_ `void SetBlendShapeTargetIndex(uint16 BlendShapeTargetIndex);`
- L32 _public prototype_ `void SetDeltas(TArrayView<const FVector> Deltas);`
- L33 _public prototype_ `void SetDeltas(TArrayView<const float> DXs, TArrayView<const float> DYs, TArrayView<const float> DZs);`
- L34 _public prototype_ `void SetVertexIndices(TArrayView<const uint32> VertexIndices);`
- L35 _public prototype_ `void SetMasks(TArrayView<const float> Masks);`
- L36 _public prototype_ `void SetOperation(EDNACalibVectorOperation Operation);`
- L38 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L42 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibSetLODsCommand.h` (Public)


#### class `FDNACalibSetLODsCommand`  
`class FDNACalibSetLODsCommand : public IDNACalibCommand`  
_L13-33_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibSetLODsCommand();`
- L16 _public prototype_ `FDNACalibSetLODsCommand(TArrayView<const uint16> LODs);`
- L18 _public prototype_ `~FDNACalibSetLODsCommand();`
- L20 _public prototype_ `FDNACalibSetLODsCommand(const FDNACalibSetLODsCommand&) = delete;`
- L21 _public prototype_ `FDNACalibSetLODsCommand& operator=(const FDNACalibSetLODsCommand&) = delete;`
- L23 _public prototype_ `FDNACalibSetLODsCommand(FDNACalibSetLODsCommand&&);`
- L24 _public prototype_ `FDNACalibSetLODsCommand& operator=(FDNACalibSetLODsCommand&&);`
- L26 _public prototype_ `void SetLODs(TArrayView<const uint16> LODs);`
- L28 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L32 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibSetNeutralJointRotationsCommand.h` (Public)


#### class `FDNACalibSetNeutralJointRotationsCommand`  
`class FDNACalibSetNeutralJointRotationsCommand : public IDNACalibCommand`  
_L13-35_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand();`
- L16 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand(TArrayView<const FVector> Positions);`
- L17 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand(TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs);`
- L19 _public prototype_ `~FDNACalibSetNeutralJointRotationsCommand();`
- L21 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand(const FDNACalibSetNeutralJointRotationsCommand&) = delete;`
- L22 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand& operator=(const FDNACalibSetNeutralJointRotationsCommand&) = delete;`
- L24 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand(FDNACalibSetNeutralJointRotationsCommand&&);`
- L25 _public prototype_ `FDNACalibSetNeutralJointRotationsCommand& operator=(FDNACalibSetNeutralJointRotationsCommand&&);`
- L27 _public prototype_ `void SetRotations(TArrayView<const FVector> Positions);`
- L28 _public prototype_ `void SetRotations(TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs);`
- L30 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L34 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibSetNeutralJointTranslationsCommand.h` (Public)


#### class `FDNACalibSetNeutralJointTranslationsCommand`  
`class FDNACalibSetNeutralJointTranslationsCommand : public IDNACalibCommand`  
_L13-35_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand();`
- L16 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand(TArrayView<const FVector> Translations);`
- L17 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand(TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs);`
- L19 _public prototype_ `~FDNACalibSetNeutralJointTranslationsCommand();`
- L21 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand(const FDNACalibSetNeutralJointTranslationsCommand&) = delete;`
- L22 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand& operator=(const FDNACalibSetNeutralJointTranslationsCommand&) = delete;`
- L24 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand(FDNACalibSetNeutralJointTranslationsCommand&&);`
- L25 _public prototype_ `FDNACalibSetNeutralJointTranslationsCommand& operator=(FDNACalibSetNeutralJointTranslationsCommand&&);`
- L27 _public prototype_ `void SetTranslations(TArrayView<const FVector> Translations);`
- L28 _public prototype_ `void SetTranslations(TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs);`
- L30 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L34 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibSetSkinWeightsCommand.h` (Public)


#### class `FDNACalibSetSkinWeightsCommand`  
`class FDNACalibSetSkinWeightsCommand : public IDNACalibCommand`  
_L13-36_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibSetSkinWeightsCommand();`
- L16 _public prototype_ `FDNACalibSetSkinWeightsCommand(uint16 MeshIndex, uint32 VertexIndex, TArrayView<const float> Weights, TArrayView<const uint16> JointIndices);`
- L18 _public prototype_ `~FDNACalibSetSkinWeightsCommand();`
- L20 _public prototype_ `FDNACalibSetSkinWeightsCommand(const FDNACalibSetSkinWeightsCommand&) = delete;`
- L21 _public prototype_ `FDNACalibSetSkinWeightsCommand& operator=(const FDNACalibSetSkinWeightsCommand&) = delete;`
- L23 _public prototype_ `FDNACalibSetSkinWeightsCommand(FDNACalibSetSkinWeightsCommand&&);`
- L24 _public prototype_ `FDNACalibSetSkinWeightsCommand& operator=(FDNACalibSetSkinWeightsCommand&&);`
- L26 _public prototype_ `void SetMeshIndex(uint16 MeshIndex);`
- L27 _public prototype_ `void SetVertexIndex(uint32 VertexIndex);`
- L28 _public prototype_ `void SetWeights(TArrayView<const float> Weights);`
- L29 _public prototype_ `void SetJointIndices(TArrayView<const uint16> JointIndices);`
- L31 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L35 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibSetVertexPositionsCommand.h` (Public)


#### class `FDNACalibSetVertexPositionsCommand`  
`class FDNACalibSetVertexPositionsCommand : public IDNACalibCommand`  
_L14-41_
- inherits: `IDNACalibCommand`
- L16 _public prototype_ `FDNACalibSetVertexPositionsCommand();`
- L17 _public prototype_ `FDNACalibSetVertexPositionsCommand(uint16 MeshIndex, TArrayView<const FVector> Positions, EDNACalibVectorOperation Operation);`
- L18 _public prototype_ `FDNACalibSetVertexPositionsCommand(uint16 MeshIndex, TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs, EDNACalibVectorOperation Operation);`
- L19 _public prototype_ `FDNACalibSetVertexPositionsCommand(uint16 MeshIndex, TArrayView<const FVector> Positions, TArrayView<const float> Masks, EDNACalibVectorOperation Operation);`
- L20 _public prototype_ `FDNACalibSetVertexPositionsCommand(uint16 MeshIndex, TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs, TArrayView<const float> Masks, EDNACalibVectorOperation Operation);`
- L22 _public prototype_ `~FDNACalibSetVertexPositionsCommand();`
- L24 _public prototype_ `FDNACalibSetVertexPositionsCommand(const FDNACalibSetVertexPositionsCommand&) = delete;`
- L25 _public prototype_ `FDNACalibSetVertexPositionsCommand& operator=(const FDNACalibSetVertexPositionsCommand&) = delete;`
- L27 _public prototype_ `FDNACalibSetVertexPositionsCommand(FDNACalibSetVertexPositionsCommand&&);`
- L28 _public prototype_ `FDNACalibSetVertexPositionsCommand& operator=(FDNACalibSetVertexPositionsCommand&&);`
- L30 _public prototype_ `void SetMeshIndex(uint16 MeshIndex);`
- L31 _public prototype_ `void SetPositions(TArrayView<const FVector> Positions);`
- L32 _public prototype_ `void SetPositions(TArrayView<const float> Xs, TArrayView<const float> Ys, TArrayView<const float> Zs);`
- L33 _public prototype_ `void SetMasks(TArrayView<const float> Masks);`
- L34 _public prototype_ `void SetOperation(EDNACalibVectorOperation Operation);`
- L36 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L40 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibTranslateCommand.h` (Public)


#### class `FDNACalibTranslateCommand`  
`class FDNACalibTranslateCommand : public IDNACalibCommand`  
_L13-33_
- inherits: `IDNACalibCommand`
- L15 _public prototype_ `FDNACalibTranslateCommand();`
- L16 _public prototype_ `FDNACalibTranslateCommand(FVector Translation);`
- L18 _public prototype_ `~FDNACalibTranslateCommand();`
- L20 _public prototype_ `FDNACalibTranslateCommand(const FDNACalibTranslateCommand&) = delete;`
- L21 _public prototype_ `FDNACalibTranslateCommand& operator=(const FDNACalibTranslateCommand&) = delete;`
- L23 _public prototype_ `FDNACalibTranslateCommand(FDNACalibTranslateCommand&&);`
- L24 _public prototype_ `FDNACalibTranslateCommand& operator=(FDNACalibTranslateCommand&&);`
- L26 _public prototype_ `void SetTranslation(FVector Translation);`
- L28 _public prototype_ `void Run(FDNACalibDNAReader* Output) override;`
- L32 _private member_ `TUniquePtr<Impl> ImplPtr;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/Commands/DNACalibVectorOperation.h` (Public)


#### enum `EDNACalibVectorOperation`  
`enum class EDNACalibVectorOperation: uint8`  
_L12-18_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Interpolate`
- L15 _public enumerator_ `Add`
- L16 _public enumerator_ `Subtract`
- L17 _public enumerator_ `Multiply`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/DNACalibCommand.h` (Public)


#### class `IDNACalibCommand`  
`class IDNACalibCommand`  
_L10-16_
- desc: @brief UE Interface for DNACalib Command wrappers.
- L13 _public prototype_ `virtual ~IDNACalibCommand() = default;`
- L14 _public prototype_ `virtual void Run(FDNACalibDNAReader* Output) = 0;`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/DNACalibDNAReader.h` (Public)


#### class `FDNACalibDNAReader`  
`class FDNACalibDNAReader : public IDNAReader`  
_L17-208_
- inherits: `IDNAReader`
- desc: @brief A UE wrapper for a special purpose DNA Reader type which serves as the output parameter of DNACalib.
- L20 _public prototype_ `explicit FDNACalibDNAReader(IDNAReader* Source);`
- L23 _public prototype_ `uint16 GetFileFormatGeneration() const override;` — Header
- L24 _public prototype_ `uint16 GetFileFormatVersion() const override;`
- L26 _public prototype_ `FString GetName() const override;` — Descriptor
- L27 _public prototype_ `EArchetype GetArchetype() const override;`
- L28 _public prototype_ `EGender GetGender() const override;`
- L29 _public prototype_ `uint16 GetAge() const override;`
- L30 _public prototype_ `uint32 GetMetaDataCount() const override;`
- L31 _public prototype_ `FString GetMetaDataKey(uint32 Index) const override;`
- L32 _public prototype_ `FString GetMetaDataValue(const FString& Key) const override;`
- L33 _public prototype_ `ETranslationUnit GetTranslationUnit() const override;`
- L34 _public prototype_ `ERotationUnit GetRotationUnit() const override;`
- L35 _public prototype_ `FCoordinateSystem GetCoordinateSystem() const override;`
- L36 _public prototype_ `ERotationSequence GetRotationSequence() const override;`
- L37 _public prototype_ `FRotationSign GetRotationSign() const override;`
- L38 _public prototype_ `EFaceWindingOrder GetFaceWindingOrder() const override;`
- L39 _public prototype_ `uint16 GetLODCount() const override;`
- L40 _public prototype_ `uint16 GetDBMaxLOD() const override;`
- L41 _public prototype_ `FString GetDBComplexity() const override;`
- L42 _public prototype_ `FString GetDBName() const override;`
- L44 _public prototype_ `uint16 GetGUIControlCount() const override;` — Definition
- L45 _public prototype_ `FString GetGUIControlName(uint16 Index) const override;`
- L46 _public prototype_ `uint16 GetRawControlCount() const override;`
- L47 _public prototype_ `FString GetRawControlName(uint16 Index) const override;`
- L48 _public prototype_ `uint16 GetJointCount() const override;`
- L49 _public prototype_ `FString GetJointName(uint16 Index) const override;`
- L50 _public prototype_ `uint16 GetJointIndexListCount() const override;`
- L51 _public prototype_ `TArrayView<const uint16> GetJointIndicesForLOD(uint16 LOD) const override;`
- L52 _public prototype_ `uint16 GetJointParentIndex(uint16 Index) const override;`
- L53 _public prototype_ `uint16 GetBlendShapeChannelCount() const override;`
- L54 _public prototype_ `FString GetBlendShapeChannelName(uint16 Index) const override;`
- L55 _public prototype_ `uint16 GetBlendShapeChannelIndexListCount() const override;`
- L56 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelIndicesForLOD(uint16 LOD) const override;`
- L57 _public prototype_ `uint16 GetAnimatedMapCount() const override;`
- L58 _public prototype_ `FString GetAnimatedMapName(uint16 Index) const override;`
- L59 _public prototype_ `uint16 GetAnimatedMapIndexListCount() const override;`
- L60 _public prototype_ `TArrayView<const uint16> GetAnimatedMapIndicesForLOD(uint16 LOD) const override;`
- L61 _public prototype_ `uint16 GetMeshCount() const override;`
- L62 _public prototype_ `FString GetMeshName(uint16 Index) const override;`
- L63 _public prototype_ `uint16 GetMeshIndexListCount() const override;`
- L64 _public prototype_ `TArrayView<const uint16> GetMeshIndicesForLOD(uint16 LOD) const override;`
- L65 _public prototype_ `uint16 GetMeshBlendShapeChannelMappingCount() const override;`
- L66 _public prototype_ `FMeshBlendShapeChannelMapping GetMeshBlendShapeChannelMapping(uint16 Index) const override;`
- L67 _public prototype_ `TArrayView<const uint16> GetMeshBlendShapeChannelMappingIndicesForLOD(uint16 LOD) const override;`
- L68 _public prototype_ `FVector GetNeutralJointTranslation(uint16 Index) const override;`
- L69 _public prototype_ `FVector GetNeutralJointRotation(uint16 Index) const override;`
- L71 _public prototype_ `TArrayView<const uint16> GetGUIToRawInputIndices() const override;` — Behavior
- L72 _public prototype_ `TArrayView<const uint16> GetGUIToRawOutputIndices() const override;`
- L73 _public prototype_ `TArrayView<const float> GetGUIToRawFromValues() const override;`
- L74 _public prototype_ `TArrayView<const float> GetGUIToRawToValues() const override;`
- L75 _public prototype_ `TArrayView<const float> GetGUIToRawSlopeValues() const override;`
- L76 _public prototype_ `TArrayView<const float> GetGUIToRawCutValues() const override;`
- L77 _public prototype_ `uint16 GetPSDCount() const override;`
- L78 _public prototype_ `TArrayView<const uint16> GetPSDRowIndices() const override;`
- L79 _public prototype_ `TArrayView<const uint16> GetPSDColumnIndices() const override;`
- L80 _public prototype_ `TArrayView<const float> GetPSDValues() const override;`
- L81 _public prototype_ `uint16 GetJointRowCount() const override;`
- L82 _public prototype_ `uint16 GetJointColumnCount() const override;`
- L83 _public prototype_ `TArrayView<const uint16> GetJointVariableAttributeIndices(uint16 LOD) const override;`
- L84 _public prototype_ `uint16 GetJointGroupCount() const override;`
- L85 _public prototype_ `TArrayView<const uint16> GetJointGroupLODs(uint16 JointGroupIndex) const override;`
- L86 _public prototype_ `TArrayView<const uint16> GetJointGroupInputIndices(uint16 JointGroupIndex) const override;`
- L87 _public prototype_ `TArrayView<const uint16> GetJointGroupOutputIndices(uint16 JointGroupIndex) const override;`
- L88 _public prototype_ `TArrayView<const float> GetJointGroupValues(uint16 JointGroupIndex) const override;`
- L89 _public prototype_ `TArrayView<const uint16> GetJointGroupJointIndices(uint16 JointGroupIndex) const override;`
- L90 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelLODs() const override;`
- L91 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelOutputIndices() const override;`
- L92 _public prototype_ `TArrayView<const uint16> GetBlendShapeChannelInputIndices() const override;`
- L93 _public prototype_ `TArrayView<const uint16> GetAnimatedMapLODs() const override;`
- L94 _public prototype_ `TArrayView<const uint16> GetAnimatedMapInputIndices() const override;`
- L95 _public prototype_ `TArrayView<const uint16> GetAnimatedMapOutputIndices() const override;`
- L96 _public prototype_ `TArrayView<const float> GetAnimatedMapFromValues() const override;`
- L97 _public prototype_ `TArrayView<const float> GetAnimatedMapToValues() const override;`
- L98 _public prototype_ `TArrayView<const float> GetAnimatedMapSlopeValues() const override;`
- L99 _public prototype_ `TArrayView<const float> GetAnimatedMapCutValues() const override;`
- L101 _public prototype_ `uint32 GetVertexPositionCount(uint16 MeshIndex) const override;` — Geometry
- L102 _public prototype_ `FVector GetVertexPosition(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L103 _public prototype_ `TArrayView<const float> GetVertexPositionXs(uint16 MeshIndex) const override;`
- L104 _public prototype_ `TArrayView<const float> GetVertexPositionYs(uint16 MeshIndex) const override;`
- L105 _public prototype_ `TArrayView<const float> GetVertexPositionZs(uint16 MeshIndex) const override;`
- L106 _public prototype_ `uint32 GetVertexTextureCoordinateCount(uint16 MeshIndex) const override;`
- L107 _public prototype_ `FTextureCoordinate GetVertexTextureCoordinate(uint16 MeshIndex, uint32 TextureCoordinateIndex) const override;`
- L108 _public prototype_ `uint32 GetVertexNormalCount(uint16 MeshIndex) const override;`
- L109 _public prototype_ `FVector GetVertexNormal(uint16 MeshIndex, uint32 NormalIndex) const override;`
- L110 _public prototype_ `uint32 GetFaceCount(uint16 MeshIndex) const override;`
- L111 _public prototype_ `TArrayView<const uint32> GetFaceVertexLayoutIndices(uint16 MeshIndex, uint32 FaceIndex) const override;`
- L112 _public prototype_ `uint32 GetVertexLayoutCount(uint16 MeshIndex) const override;`
- L113 _public prototype_ `FVertexLayout GetVertexLayout(uint16 MeshIndex, uint32 LayoutIndex) const override;`
- L114 _public prototype_ `uint16 GetMaximumInfluencePerVertex(uint16 MeshIndex) const override;`
- L115 _public prototype_ `uint32 GetSkinWeightsCount(uint16 MeshIndex) const override;`
- L116 _public prototype_ `TArrayView<const float> GetSkinWeightsValues(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L117 _public prototype_ `TArrayView<const uint16> GetSkinWeightsJointIndices(uint16 MeshIndex, uint32 VertexIndex) const override;`
- L118 _public prototype_ `uint16 GetBlendShapeTargetCount(uint16 MeshIndex) const override;`
- L119 _public prototype_ `uint16 GetBlendShapeChannelIndex(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L120 _public prototype_ `uint32 GetBlendShapeTargetDeltaCount(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L121 _public prototype_ `FVector GetBlendShapeTargetDelta(uint16 MeshIndex, uint16 BlendShapeTargetIndex, uint32 DeltaIndex) const override;`
- L122 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaXs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L123 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaYs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L124 _public prototype_ `TArrayView<const float> GetBlendShapeTargetDeltaZs(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L125 _public prototype_ `TArrayView<const uint32> GetBlendShapeTargetVertexIndices(uint16 MeshIndex, uint16 BlendShapeTargetIndex) const override;`
- L127 _public prototype_ `uint16 GetMLControlCount() const override;` — Machine Learned Behavior
- L128 _public prototype_ `FString GetMLControlName(uint16 Index) const override;`
- L129 _public prototype_ `uint16 GetNeuralNetworkCount() const override;`
- L130 _public prototype_ `uint16 GetNeuralNetworkIndexListCount() const override;`
- L131 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForLOD(uint16 LOD) const override;`
- L132 _public prototype_ `uint16 GetMeshRegionCount(uint16 MeshIndex) const override;`
- L133 _public prototype_ `FString GetMeshRegionName(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L134 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkIndicesForMeshRegion(uint16 MeshIndex, uint16 RegionIndex) const override;`
- L135 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkInputIndices(uint16 NetIndex) const override;`
- L136 _public prototype_ `TArrayView<const uint16> GetNeuralNetworkOutputIndices(uint16 NetIndex) const override;`
- L137 _public prototype_ `uint16 GetNeuralNetworkLayerCount(uint16 NetIndex) const override;`
- L138 _public prototype_ `EActivationFunction GetNeuralNetworkLayerActivationFunction(uint16 NetIndex, uint16 LayerIndex) const override;`
- L139 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerActivationFunctionParameters(uint16 NetIndex, uint16 LayerIndex) const override;`
- L140 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerBiases(uint16 NetIndex, uint16 LayerIndex) const override;`
- L141 _public prototype_ `TArrayView<const float> GetNeuralNetworkLayerWeights(uint16 NetIndex, uint16 LayerIndex) const override;`
- L143 _public prototype_ `ETranslationRepresentation GetJointTranslationRepresentation(uint16 JointIndex) const override;` — JointBehaviorMetadataReader
- L144 _public prototype_ `ERotationRepresentation GetJointRotationRepresentation(uint16 JointIndex) const override;`
- L145 _public prototype_ `EScaleRepresentation GetJointScaleRepresentation(uint16 JointIndex) const override;`
- L147 _public prototype_ `uint16 GetRBFPoseCount() const override;` — RBFBehavior
- L148 _public prototype_ `FString GetRBFPoseName(uint16 PoseIndex) const override;`
- L149 _public prototype_ `TArrayView<const uint16> GetRBFPoseJointOutputIndices(uint16 PoseIndex) const override;`
- L150 _public prototype_ `TArrayView<const uint16> GetRBFPoseBlendShapeChannelOutputIndices(uint16 PoseIndex) const override;`
- L151 _public prototype_ `TArrayView<const uint16> GetRBFPoseAnimatedMapOutputIndices(uint16 PoseIndex) const override;`
- L152 _public prototype_ `TArrayView<const float> GetRBFPoseJointOutputValues(uint16 PoseIndex) const override;`
- L153 _public prototype_ `float GetRBFPoseScale(uint16 PoseIndex) const override;`
- L154 _public prototype_ `uint16 GetRBFPoseControlCount() const override;`
- L155 _public prototype_ `FString GetRBFPoseControlName(uint16 PoseControlIndex) const override;`
- L156 _public prototype_ `TArrayView<const uint16> GetRBFPoseInputControlIndices(uint16 PoseIndex) const override;`
- L157 _public prototype_ `TArrayView<const uint16> GetRBFPoseOutputControlIndices(uint16 PoseIndex) const override;`
- L158 _public prototype_ `TArrayView<const float> GetRBFPoseOutputControlWeights(uint16 PoseIndex) const override;`
- L159 _public prototype_ `uint16 GetRBFSolverCount() const override;`
- L160 _public prototype_ `uint16 GetRBFSolverIndexListCount() const override;`
- L161 _public prototype_ `TArrayView<const uint16> GetRBFSolverIndicesForLOD(uint16 LOD) const override;`
- L162 _public prototype_ `FString GetRBFSolverName(uint16 SolverIndex) const override;`
- L163 _public prototype_ `TArrayView<const uint16> GetRBFSolverRawControlIndices(uint16 SolverIndex) const override;`
- L164 _public prototype_ `TArrayView<const uint16> GetRBFSolverPoseIndices(uint16 SolverIndex) const override;`
- L165 _public prototype_ `TArrayView<const float> GetRBFSolverRawControlValues(uint16 SolverIndex) const override;`
- L166 _public prototype_ `ERBFSolverType GetRBFSolverType(uint16 SolverIndex) const override;`
- L167 _public prototype_ `float GetRBFSolverRadius(uint16 SolverIndex) const override;`
- L168 _public prototype_ `EAutomaticRadius GetRBFSolverAutomaticRadius(uint16 SolverIndex) const override;`
- L169 _public prototype_ `float GetRBFSolverWeightThreshold(uint16 SolverIndex) const override;`
- L170 _public prototype_ `ERBFDistanceMethod GetRBFSolverDistanceMethod(uint16 SolverIndex) const override;`
- L171 _public prototype_ `ERBFNormalizeMethod GetRBFSolverNormalizeMethod(uint16 SolverIndex) const override;`
- L172 _public prototype_ `ERBFFunctionType GetRBFSolverFunctionType(uint16 SolverIndex) const override;`
- L173 _public prototype_ `ETwistAxis GetRBFSolverTwistAxis(uint16 SolverIndex) const override;`
- L175 _public prototype_ `uint16 GetTwistCount() const override;` — TwistSwingBehavior
- L176 _public prototype_ `ETwistAxis GetTwistSetupTwistAxis(uint16 TwistIndex) const override;`
- L177 _public prototype_ `TArrayView<const uint16> GetTwistInputControlIndices(uint16 TwistIndex) const override;`
- L178 _public prototype_ `TArrayView<const uint16> GetTwistOutputJointIndices(uint16 TwistIndex) const override;`
- L179 _public prototype_ `TArrayView<const float> GetTwistBlendWeights(uint16 TwistIndex) const override;`
- L180 _public prototype_ `uint16 GetSwingCount() const override;`
- L181 _public prototype_ `ETwistAxis GetSwingSetupTwistAxis(uint16 SwingIndex) const override;`
- L182 _public prototype_ `TArrayView<const uint16> GetSwingInputControlIndices(uint16 SwingIndex) const override;`
- L183 _public prototype_ `TArrayView<const uint16> GetSwingOutputJointIndices(uint16 SwingIndex) const override;`
- L184 _public prototype_ `TArrayView<const float> GetSwingBlendWeights(uint16 SwingIndex) const override;`
- L186 _public prototype_ `uint16 GetMLTypeCount() const override;` — MachineLearnedBehaviorExtReader
- L187 _public prototype_ `uint16 GetMLOperationSetCount(uint16 MLTypeIndex) const override;`
- L188 _public prototype_ `uint16 GetMLOperationCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L189 _public prototype_ `EMachineLearnedBehaviorOperationType GetMLOperationType(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L190 _public prototype_ `TArrayView<const uint32> GetMLOperationParameters(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L191 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationSetIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L192 _public prototype_ `TArrayView<const uint16> GetMLOperationDependencyOperationIndices(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 MLOperationIndex) const override;`
- L193 _public prototype_ `uint16 GetMLOperationIndexListCount(uint16 MLTypeIndex, uint16 MLOperationSetIndex) const override;`
- L194 _public prototype_ `TArrayView<const uint16> GetMLOperationIndicesForLOD(uint16 MLTypeIndex, uint16 MLOperationSetIndex, uint16 LOD) const override;`
- L195 _public prototype_ `TArrayView<const uint16> GetMLJointsInputIndices() const override;`
- L196 _public prototype_ `TArrayView<const uint16> GetMLJointsOutputIndices() const override;`
- L197 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterKeys() const override;`
- L198 _public prototype_ `TArrayView<const uint16> GetMLJointsParameterValues() const override;`
- L199 _public prototype_ `void Unload(EDNADataLayer layer) override;`
- L201 _public prototype_ `const FDNAConfig& GetConfig() const override;`
- L203 _public prototype_ `dna::Reader* Unwrap() const override;`
- L206 _private member_ `TUniquePtr<IDNAReader> ReaderPtr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DNACALIBMODULE_API`

### `Plugins/Animation/DNACalib/Source/DNACalibModule/Public/DNACalibModule.h` (Public)


#### class `FDNACalibModule`  
`class FDNACalibModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DNACALIBMODULE_API`
