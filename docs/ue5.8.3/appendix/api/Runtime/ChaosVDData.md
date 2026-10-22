# Runtime / ChaosVDData

- module root: `Source/Runtime/Experimental/ChaosVDData`
- headers: 2; symbols: 213
- symbol kinds: class=1, delegate=1, enum=4, enumerator=12, function=45, macro=1, member=69, namespace=2, prototype=65, struct=10, typedef=3
- PublicDependencyModuleNames: Chaos, ChaosVDRuntime, Core, CoreUObject

### `Source/Runtime/Experimental/ChaosVDData/Public/ChaosVDDataModule.h` (Public)


#### class `FChaosVDDataModule`  
`class FChaosVDDataModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`

### `Source/Runtime/Experimental/ChaosVDData/Public/ChaosVDRecording.h` (Public)


#### struct `FChaosVDCustomUserDataHandle`  
`struct FChaosVDCustomUserDataHandle`  
_L37-63_
- desc: Handle to user-defined data types in a CVD recorded frame. These handles share ownership of the data
- L43 _public prototype_ `template <typename DataStructType> static FChaosVDCustomUserDataHandle MakeHandle(const TSharedRef<DataStructType>& DataPtr);` — Creates a handle for the provided data instance. This handle will hold a reference to the data @param DataPtr Shared ref pointer to the data we want to rpovide access to
- L46 _public prototype_ `FName GetTypeName() const;` — Returns the FName of the UStruct type that this handle represents
- L50 _public prototype_ `template <typename DataStructType> DataStructType* GetData() const;` — Returns a raw ptr to the data this handle provides access to.
- L54 _public prototype_ `template <typename DataStructType> TSharedPtr<DataStructType> GetDataAsShared() const;` — Returns a shared ptr to the data this handle provides access to
- L59 _private prototype_ `template <typename DataStructType> bool IsA_Internal(const TSharedPtr<FStructOnScope>& InStructOnScope) const;` — Checks if this handle is of another type, using the UStruct data we parsed on creation
- L61 _private member_ `TSharedPtr<FStructOnScope> DataStruct;`
- L62 _private member_ `TSharedPtr<void> DataSharedPtr;`
- L66 _function_ `template <typename DataStructType> TSharedPtr<DataStructType> FChaosVDCustomUserDataHandle::GetDataAsShared() const`
- L76 _function_ `template <typename DataStructType> FChaosVDCustomUserDataHandle FChaosVDCustomUserDataHandle::MakeHandle(const TSharedRef<DataStructType>& DataPtr)`
- L87 _function_ `template <typename DataStructType> DataStructType* FChaosVDCustomUserDataHandle::GetData() const`
- L98 _function_ `template <typename DataStructType> bool FChaosVDCustomUserDataHandle::IsA_Internal(const TSharedPtr<FStructOnScope>& InStructOnScope) const`

#### struct `FChaosVDCustomFrameData`  
`struct FChaosVDCustomFrameData`  
_L109-127_
- L111 _public prototype_ `void AddData(const FChaosVDCustomUserDataHandle& InData);`
- L117 _public prototype_ `template<typename DataType> TSharedPtr<DataType> GetData() const;` — Returns the shared ptr to a custom data instance, if such data type was added to this frame. If the data type was not loaded, the ptr will be null
- L123 _public prototype_ `template<typename DataType> TSharedPtr<DataType> GetOrAddDefaultData();` — Returns the shared ptr to a custom data instance, if such data type was added to this frame. If the data type was not loaded, a new instance will be created and automatically added to the frame's data.
- L126 _private member_ `TMap<FName, FChaosVDCustomUserDataHandle> CustomDataHandlesByType;`
- L754 _function_ `template <typename DataType> TSharedPtr<DataType> FChaosVDCustomFrameData::GetData() const`
- L765 _function_ `template <typename DataType> TSharedPtr<DataType> FChaosVDCustomFrameData::GetOrAddDefaultData()`

#### enum `EChaosVDSolverStageFlags`  
`enum class EChaosVDSolverStageFlags : uint8`  
_L130-137_
- desc: Set of flags used to define characteristics of a loaded solver stage
- L132 _public enumerator_ `None = 0`
- L134 _public enumerator_ `Open = 1 << 0` — Set if the solver stage is open and can take new data
- L136 _public enumerator_ `ExplicitStage = 1 << 1` — Set if the solver stage was explicitly recorded - If not set, this stage was created on the fly during load

#### struct `FChaosVDFrameStageData`  
`struct FChaosVDFrameStageData`  
_L141-169_
- L143 _public member_ `FString StepName;`
- L144 _public member_ `TArray<TSharedPtr<FChaosVDParticleDataWrapper>> RecordedParticlesData;`
- L145 _public member_ `TArray<TSharedPtr<FChaosVDParticlePairMidPhase>> RecordedMidPhases;`
- L146 _public member_ `TArray<TSharedPtr<FChaosVDJointConstraint>> RecordedJointConstraints;`
- L147 _public member_ `TArray<FChaosVDConstraint> RecordedConstraints;`
- L148 _public member_ `TMap<int32, TArray<FChaosVDConstraint>> RecordedConstraintsByParticleID;`
- L149 _public member_ `TMap<int32, TArray<TSharedPtr<FChaosVDParticlePairMidPhase>>> RecordedMidPhasesByParticleID;`
- L150 _public member_ `TSet<int32> ParticlesDestroyedIDs;`
- L153 _public member_ `TMap<int32, int32> CurrentRecordedParticlesIndexes;` — Used for de-duplication during trace analysis
- L155 _public member_ `EChaosVDSolverStageFlags StageFlags = EChaosVDSolverStageFlags::None;`
- L157 _public function_ `FChaosVDCustomFrameData& GetCustomDataHandler()`
- L162 _public function_ `const FChaosVDCustomFrameData& GetCustomDataHandler() const`
- L168 _private member_ `FChaosVDCustomFrameData CustomData;`

#### struct `FChaosVDTrackedLocation`  
`struct FChaosVDTrackedLocation`  
_L174-178_
- L176 _public member_ `FString DebugName;`
- L177 _public member_ `FVector Location;`

#### struct `FChaosVDTrackedTransform`  
`struct FChaosVDTrackedTransform`  
_L180-184_
- L182 _public member_ `FString DebugName;`
- L183 _public member_ `FTransform Transform;`

#### enum `EChaosVDNetworkSyncDataRequirements`  
`enum class EChaosVDNetworkSyncDataRequirements`  
_L186-193_
- L188 _public enumerator_ `None = 0`
- L189 _public enumerator_ `InternalFrameNumber = 1 << 0`
- L190 _public enumerator_ `NetworkTickOffset = 1 << 1`
- L192 _public enumerator_ `All = InternalFrameNumber | NetworkTickOffset`

#### enum `EChaosVDSolverFrameAttributes`  
`enum class EChaosVDSolverFrameAttributes : uint16`  
_L203-207_
- reflection: `UENUM()`
- L205 _public enumerator_ `None = 0`
- L206 _public enumerator_ `HasGTDataToReRoute = 1 << 0`

#### struct `FChaosVDSolverFrameData`  
`struct FChaosVDSolverFrameData`  
_L210-303_
- L213 _public prototype_ `FChaosVDSolverFrameData() = default;`
- L214 _public prototype_ `FChaosVDSolverFrameData(const FChaosVDSolverFrameData& Other) = default;`
- L215 _public prototype_ `FChaosVDSolverFrameData(FChaosVDSolverFrameData&& Other) noexcept = default;`
- L216 _public prototype_ `FChaosVDSolverFrameData& operator=(const FChaosVDSolverFrameData& Other) = default;`
- L217 _public prototype_ `FChaosVDSolverFrameData& operator=(FChaosVDSolverFrameData&& Other) noexcept = default;`
- L220 _public member_ `FName DebugFName;`
- L222 _public member_ `FString DebugName;` — `UE_DEPRECATED(5.5, "Please use the DebugFName instead")`
- L223 _public member_ `int32 SolverID = INDEX_NONE;`
- L224 _public member_ `int32 InternalFrameNumber = INDEX_NONE;`
- L225 _public member_ `int32 NetworkTickOffset = INDEX_NONE;`
- L226 _public member_ `uint64 FrameCycle = 0;`
- L227 _public member_ `Chaos::FRigidTransform3 SimulationTransform;`
- L228 _public member_ `bool bIsKeyFrame = false;`
- L229 _public member_ `bool bIsResimulated = false;`
- L230 _public member_ `FChaosVDFrameStagesContainer SolverSteps;`
- L231 _public member_ `TSet<int32> ParticlesDestroyedIDs;`
- L232 _public member_ `double StartTime = -1.0;`
- L233 _public member_ `double EndTime = -1.0;`
- L235 _public member_ `TArray<TSharedPtr<FChaosVDCharacterGroundConstraint>> RecordedCharacterGroundConstraints;`
- L240 _public function_ `double GetFrameTime() const` — Calculates and returns the frame time for this recorded frame. @return Calculated frame time. -1 if it was not recorded
- L251 _public function_ `bool HasNetworkSyncData(EChaosVDNetworkSyncDataRequirements Requirements = EChaosVDNetworkSyncDataRequirements::All) const` — Returns true if we have the necessary data to sync this frame with other frame based on network ticks offsets
- L269 _public function_ `int32 GetClampedNetworkTickOffset() const` — Returns the current network tick offset. If we didn't have recorded a network tick, we will still return 0 to keep compatibility with other files
- L274 _public function_ `FChaosVDCustomFrameData& GetCustomData()`
- L279 _public function_ `const FChaosVDCustomFrameData& GetCustomData() const`
- L284 _public function_ `EChaosVDSolverFrameAttributes GetAttributes() const`
- L289 _public function_ `void AddAttributes(EChaosVDSolverFrameAttributes NewAttributes)`
- L294 _public function_ `void RemoveAttributes(EChaosVDSolverFrameAttributes AttributesToRemove)`
- L300 _private member_ `FChaosVDCustomFrameData CustomData;`
- L302 _private member_ `EChaosVDSolverFrameAttributes FrameAttributes = EChaosVDSolverFrameAttributes::None;`

#### struct `FChaosVDGameFrameData`  
`struct FChaosVDGameFrameData`  
_L305-383_
- L309 _public prototype_ `FChaosVDGameFrameData() = default;`
- L310 _public prototype_ `FChaosVDGameFrameData(const FChaosVDGameFrameData& Other) = default;`
- L311 _public prototype_ `FChaosVDGameFrameData(FChaosVDGameFrameData&& Other) noexcept = default;`
- L312 _public prototype_ `FChaosVDGameFrameData& operator=(const FChaosVDGameFrameData& Other) = default;`
- L313 _public prototype_ `FChaosVDGameFrameData& operator=(FChaosVDGameFrameData&& Other) noexcept = default;`
- L316 _public member_ `uint64 FirstCycle;`
- L317 _public member_ `uint64 LastCycle;`
- L318 _public member_ `double StartTime = -1.0;`
- L319 _public member_ `double EndTime = -1.0;`
- L324 _public function_ `double GetFrameTime() const` — Calculates and returns the frame time for this recorded frame. @return Calculated frame time. -1 if it was not recorded
- L334 _public function_ `bool IsDirty() const`
- L339 _public function_ `void MarkDirty()`
- L345 _public member_ `TMap<FName, FChaosVDTrackedLocation> RecordedNonSolverLocationsByID;` — `UE_DEPRECATED(5.6, "RecordedNonSolverLocationsByID is deprecated and will be removed in a future release.")`
- L347 _public member_ `TMap<FName, FChaosVDTrackedTransform> RecordedNonSolverTransformsByID;` — `UE_DEPRECATED(5.6, "RecordedNonSolverTransformsByID is deprecated and will be removed in a future release.")`
- L350 _public member_ `TMap<int32, TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>>> RecordedSceneQueriesBySolverID;` — `UE_DEPRECATED(5.6, "RecordedDebugDrawBoxesBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L353 _public member_ `TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>> RecordedSceneQueries;` — `UE_DEPRECATED(5.5, "RecordedSceneQueries is deprecated and will be removed in a future release, use RecordedSceneQueriesByQueryID instead.")`
- L356 _public member_ `TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>> RecordedSceneQueriesByQueryID;` — `UE_DEPRECATED(5.6, "RecordedDebugDrawBoxesBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L359 _public member_ `TMap<int32, TArray<TSharedPtr<FChaosVDAABBTreeDataWrapper>>> RecordedAABBTreesBySolverID;` — `UE_DEPRECATED(5.6, "RecordedAABBTreesBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L362 _public member_ `TMap<int32,TArray<TSharedPtr<FChaosVDDebugDrawBoxDataWrapper>>> RecordedDebugDrawBoxesBySolverID;` — `UE_DEPRECATED(5.6, "RecordedDebugDrawBoxesBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L364 _public member_ `TMap<int32,TArray<TSharedPtr<FChaosVDDebugDrawLineDataWrapper>>> RecordedDebugDrawLinesBySolverID;` — `UE_DEPRECATED(5.6, "RecordedDebugDrawLinesBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L366 _public member_ `TMap<int32,TArray<TSharedPtr<FChaosVDDebugDrawSphereDataWrapper>>> RecordedDebugDrawSpheresBySolverID;` — `UE_DEPRECATED(5.6, "RecordedDebugDrawSpheresBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L368 _public member_ `TMap<int32,TArray<TSharedPtr<FChaosVDDebugDrawImplicitObjectDataWrapper>>> RecordedDebugDrawImplicitObjectsBySolverID;` — `UE_DEPRECATED(5.6, "RecordedDebugDrawImplicitObjectsBySolverID is deprecated and will be removed in a future release, use GetCustomDataContainer instead.")`
- L370 _public function_ `FChaosVDCustomFrameData& GetCustomDataHandler()`
- L375 _public function_ `const FChaosVDCustomFrameData& GetCustomDataHandler() const`
- L381 _private member_ `FChaosVDCustomFrameData CustomData;`
- L382 _private member_ `bool bIsDirty = false;`

#### struct `FChaosVDGameFrameDataWrapper`  
`struct FChaosVDGameFrameDataWrapper`  
_L386-391_
- reflection: `USTRUCT()`
- L390 _public member_ `TSharedPtr<FChaosVDGameFrameData> FrameData;`

#### struct `FChaosVDGameFrameDataWrapperContext`  
`struct FChaosVDGameFrameDataWrapperContext`  
_L394-399_
- reflection: `USTRUCT()`
- L398 _public member_ `TArray<int32, TInlineAllocator<25>> SupportedSolverIDs;`

#### enum `EChaosVDRecordingAttributes`  
`enum class EChaosVDRecordingAttributes : uint8`  
_L401-408_
- L403 _public enumerator_ `None = 0`
- L405 _public enumerator_ `Live = 1 << 0` — Set if this recording is being populated from a live session
- L407 _public enumerator_ `Merged = 1 << 1` — Set if this recording contains data from multiple recordings

#### struct `FChaosVDRecording`  
`struct FChaosVDRecording`  
_L415-751_
- desc: Struct that represents a recorded Physics simulation. It is currently populated while analyzing a Trace session
- L417 _public prototype_ `FChaosVDRecording();`
- L421 _public member_ `static constexpr int32 CommonTrackCount = 16;` — Constant used to define inline allocators - Unless there are some scenarios with a lot of RBAN solvers in the recording, we usually don't go over 3 tracks most of the time so 16 should be plenty by default
- L424 _public function_ `int32 GetAvailableSolversNumber_AssumesLocked() const` — Returns the current available recorded solvers number
- L430 _public prototype_ `int32 GetAvailableGameFramesNumber() const;` — Returns the current available Game Frames
- L431 _public prototype_ `int32 GetAvailableGameFramesNumber_AssumesLocked() const;`
- L434 _public function_ `const TArray<FChaosVDGameFrameData>& GetAvailableGameFrames_AssumesLocked() const` — Returns a reference to the array holding all the available game frames
- L440 _public function_ `const TMap<int32, TArray<FChaosVDSolverFrameData>>& GetAvailableSolvers_AssumesLocked() const` — Returns a reference to the map containing the available solver data
- L449 _public prototype_ `int32 GetAvailableSolverFramesNumber(int32 SolverID) const;` — Returns the number of available frame data for the specified solver ID @param SolverID ID of the solver
- L450 _public prototype_ `int32 GetAvailableSolverFramesNumber_AssumesLocked(int32 SolverID) const;`
- L456 _public prototype_ `FName GetSolverFName(int32 SolverID);` — Returns the name of the specified solver id @param SolverID ID of the solver
- L459 _public function_ `FString GetSolverName(int32 SolverID)` — `UE_DEPRECATED(5.6, "Please use the GetSolverFName instead")`
- L468 _public prototype_ `FName GetSolverFName_AssumedLocked(int32 SolverID);` — Returns the name of the specified solver id. Must be called from within a ReadLock @param SolverID ID of the solver
- L470 _public prototype_ `bool IsServerSolver_AssumesLocked(int32 SolverID);`
- L471 _public prototype_ `bool IsServerSolver(int32 SolverID);`
- L474 _public function_ `FString GetSolverName_AssumedLocked(int32 SolverID)` — `UE_DEPRECATED(5.6, "Please use the GetSolverFName_AssumedLocked instead")`
- L486 _public prototype_ `FChaosVDSolverFrameData* GetSolverFrameData_AssumesLocked(int32 SolverID, int32 FrameNumber, bool bKeyFrameOnly = false);` — Return a ptr to the existing solver frame data from the specified ID and Frame number @param SolverID ID of the solver @param FrameNumber Frame number @param bKeyFrameOnly True if we should return a keyframe (real or generated) for the provided frame number if available or nothing @return Ptr to the existing solver frame data from the specified ID and Frame number - It is a ptr to the array element, Do not store
- L494 _public prototype_ `FChaosVDSolverFrameData* GetSolverFrameDataAtCycle_AssumesLocked(int32 SolverID, uint64 Cycle);` — Return a ptr to the existing solver frame data from the specified ID and Frame number @param SolverID ID if the solver @param Cycle Platform cycle at which the solver frame was recorded @return Ptr to the existing solver frame data from the specified ID and Frame number - It is a ptr to the array element, Do not store
- L502 _public prototype_ `int32 GetLowestSolverFrameNumberAtCycle(int32 SolverID, uint64 Cycle);` — Searches and returns the lowest frame number of a solver at the specified cycle @param SolverID ID if the solver @param Cycle Platform cycle to use as lower bound @return Found frame number. INDEX_NONE if no frame is found for the specified cycle
- L503 _public prototype_ `int32 GetLowestSolverFrameNumberAtCycle_AssumesLocked(int32 SolverID, uint64 Cycle);`
- L505 _public prototype_ `int32 GetLowestSolverFrameNumberAtNetworkFrameNumber_AssumesLocked(int32 SolverID, int32 NetworkFrameNumber);`
- L507 _public prototype_ `int32 FindFirstSolverKeyFrameNumberFromFrame_AssumesLocked(int32 SolverID, int32 StartFrameNumber);`
- L515 _public prototype_ `int32 GetLowestSolverFrameNumberGameFrame(int32 SolverID, int32 GameFrame);` — Searches and returns the lowest frame number of a solver at the specified cycle @param SolverID ID if the solver @param GameFrame Platform cycle to use as lower bound @return Found frame number. INDEX_NONE if no frame is found for the specified cycle
- L516 _public prototype_ `int32 GetLowestSolverFrameNumberGameFrame_AssumesLocked(int32 SolverID, int32 GameFrame);`
- L524 _public prototype_ `int32 GetLowestGameFrameAtSolverFrameNumber(int32 SolverID, int32 SolverFrame);` — Searches and returns the lowest game frame number at the specified solver frame @param SolverID ID if the solver to evaluate @param SolverFrame Frame number of the solver to evaluate @return Found Game frame number. INDEX_NONE if no frame is found for the specified cycle
- L525 _public prototype_ `int32 GetLowestGameFrameAtSolverFrameNumber_AssumesLocked(int32 SolverID, int32 SolverFrame);`
- L532 _public prototype_ `void AddFrameForSolver(const int32 SolverID, FChaosVDSolverFrameData&& InFrameData);` — Adds a Solver Frame Data entry for a specific Solver ID. Creates a solver entry if it does not exist @param SolverID ID of the solver to add @param InFrameData Reference to the frame data we want to add
- L538 _public prototype_ `void AddGameFrameData(const FChaosVDGameFrameData& InFrameData);` — Adds a Game Frame Data entry. Creates a solver entry if it does not exist @param InFrameData Reference to the frame data we want to add
- L541 _public function_ `FChaosVDGeometryDataLoaded& OnGeometryDataLoaded()` — Called each time new geometry data becomes available in the recording - Mainly when a new frame is added from the Trace analysis
- L551 _public prototype_ `FChaosVDGameFrameData* GetGameFrameDataAtCycle_AssumesLocked(uint64 Cycle);` — Searches for a recorded Game frame at the specified cycle @param Cycle Platform Cycle to be used in the search @return A ptr to the recorded game frame data - This is a ptr to the array element. Do not store
- L558 _public prototype_ `FChaosVDGameFrameData* GetGameFrameData_AssumesLocked(int32 FrameNumber);` — Searches for a recorded Game frame at the specified cycle @param FrameNumber Frame Number @return A ptr to the recorded game frame data - This is a ptr to the array element. Do not store
- L561 _public prototype_ `FChaosVDGameFrameData* GetLastGameFrameData_AssumesLocked();` — Returns a ptr to the last recorded game frame - This is a ptr to the array element. Do not store
- L568 _public prototype_ `int32 GetLowestGameFrameNumberAtCycle(uint64 Cycle);` — Searches and returns the lowest game frame number at the specified cycle @param Cycle Platform Cycle to be used in the search as lower bound @return Found Game frame number. INDEX_NONE if no frame is found for the specified cycle
- L569 _public prototype_ `int32 GetLowestGameFrameNumberAtCycle_AssumesLocked(uint64 Cycle);`
- L576 _public prototype_ `int32 GetLowestGameFrameNumberAtTime(double Time);` — Searches and returns the lowest game frame number at the specified cycle @param Time Platform Time to be used in the search as lower bound @return Found Game frame number. INDEX_NONE if no frame is found for the specified cycle
- L584 _public prototype_ `template<typename TAllocator> void GetAvailableSolverIDsAtGameFrameNumber(int32 FrameNumber,TArray<int32, TAllocator>& OutSolversID);` — Gathers all available solvers IDs at the given Game frame number @param FrameNumber Game Frame number to evaluate @param OutSolversID Solver's ID array to be filled with any IDs found
- L586 _public prototype_ `template<typename TAllocator> void GetAvailableSolverIDsAtGameFrameNumber_AssumesLocked(int32 FrameNumber, TArray<int32, TAllocator>& OutSolversID);`
- L588 _public prototype_ `template<typename TAllocator> void GetAvailableSolverIDsAtGameFrame(const FChaosVDGameFrameData& GameFrameData, TArray<int32, TAllocator>& OutSolversID);`
- L590 _public prototype_ `template<typename TAllocator> void GetAvailableSolverIDsAtGameFrame_AssumesLocked(const FChaosVDGameFrameData& GameFrameData, TArray<int32, TAllocator>& OutSolversID);`
- L593 _public prototype_ `void CollapseSolverFramesRange_AssumesLocked(int32 SolverID, int32 StartFrame, int32 EndFrame, FChaosVDSolverFrameData& OutCollapsedFrameData);` — Collapses the most important frame data from a range of solver frames into a single solver frame data
- L596 _public function_ `const TMap<uint32, Chaos::FConstImplicitObjectPtr>& GetGeometryMap() const` — Returns a reference to the GeometryID-ImplicitObject map of this recording
- L602 _public function_ `const TMap<uint32, TSharedPtr<const Chaos::FImplicitObject>>& GetGeometryDataMap() const` — `UE_DEPRECATED(5.4, "Please use GetGeometryMap instead")`
- L610 _public prototype_ `void AddImplicitObject(const uint32 ID, const Chaos::FImplicitObjectPtr& InImplicitObject);` — Adds a shared Implicit Object to the recording
- L613 _public prototype_ `void AddImplicitObject(const uint32 ID, const TSharedPtr<Chaos::FImplicitObject>& InImplicitObject);` — `UE_DEPRECATED(5.4, "Please use AddImplicitObject with FImplicitObjectPtr instead")`
- L616 _public member_ `FString SessionName;` — Session name of the trace session used to re-build this recording
- L618 _public function_ `FRWLock& GetRecordingDataLock()`
- L624 _public function_ `bool IsLive() const` — Returns true if this recording is being populated from a live session
- L630 _public function_ `void SetIsLive(bool bNewIsLive)` — Sets if this recording is being populated from a live session
- L642 _public function_ `void AddAttributes(EChaosVDRecordingAttributes Attributes)`
- L648 _public function_ `void RemoveAttributes(EChaosVDRecordingAttributes Attributes)`
- L654 _public function_ `EChaosVDRecordingAttributes GetAttributes() const`
- L660 _public function_ `EChaosVDRecordingAttributes GetAttributes_AssumesLocked() const`
- L666 _public prototype_ `bool IsEmpty() const;` — Returns true if this recording does not have any usable data
- L669 _public function_ `uint64 GetLastUpdatedTimeAsCycle()` — Returns the last Platform Cycle on which this recording was updated (A new frame was added)
- L674 _public function_ `TSharedPtr<FChaosVDCollisionChannelsInfoContainer> GetCollisionChannelsInfoContainer()`
- L679 _public prototype_ `void SetCollisionChannelsInfoContainer(const TSharedPtr<FChaosVDCollisionChannelsInfoContainer>& InCollisionChannelsInfo);`
- L681 _public prototype_ `bool HasSolverID(int32 SolverID);`
- L682 _public prototype_ `bool HasSolverID_AssumesLocked(int32 SolverID);`
- L684 _public prototype_ `void ReserveSolverID(int32 SolverID);`
- L685 _public prototype_ `void ReserveSolverID_AssumesLocked(int32 SolverID);`
- L687 _public prototype_ `void CommitSolverID(int32 SolverID);`
- L688 _public prototype_ `void CommitSolverID_AssumesLocked(int32 SolverID);`
- L690 _public function_ `int32 GetAvailableTrackIDForRemapping()`
- L695 _public function_ `FChaosVDCustomFrameData& GetCustomDataHandler()`
- L700 _public function_ `const FChaosVDCustomFrameData& GetCustomDataHandler() const`
- L706 _private member_ `FChaosVDCustomFrameData CustomData;`
- L711 _protected prototype_ `void AddImplicitObject(const uint32 ID, const Chaos::FImplicitObject* InImplicitObject);` — Adds an Implicit Object to the recording and takes ownership of it
- L713 _protected prototype_ `void AddImplicitObject_Internal(const uint32 ID, const Chaos::FConstImplicitObjectPtr& InImplicitObject);`
- L718 _protected prototype_ `void AddKeyFrameNumberForSolver(int32 SolverID, int32 FrameNumber);` — Stores a frame number of a solver that is a Key Frame - These are used when scrubbing to make sure the visualization is in sync with what was recorded
- L719 _protected prototype_ `void AddKeyFrameNumberForSolver_AssumesLocked(int32 SolverID, int32 FrameNumber);`
- L720 _protected prototype_ `void GenerateAndStoreKeyframeForSolver_AssumesLocked(int32 SolverID, int32 CurrentFrameNumber, int32 LastKeyFrameNumber);`
- L722 _protected member_ `TMap<int32, TArray<FChaosVDSolverFrameData>> RecordedFramesDataPerSolver;`
- L723 _protected member_ `TMap<int32, TMap<int32, FChaosVDSolverFrameData>> GeneratedKeyFrameDataPerSolver;`
- L724 _protected member_ `TMap<int32, TArray<int32>> RecordedKeyFramesNumberPerSolver;`
- L725 _protected member_ `TArray<FChaosVDGameFrameData> GameFrames;`
- L727 _protected member_ `FChaosVDGeometryDataLoaded GeometryDataLoaded;`
- L730 _protected member_ `TMap<uint32, Chaos::FConstImplicitObjectPtr> ImplicitObjects;` — Id to Ptr map of all shared geometry data required to visualize
- L732 _protected member_ `mutable FRWLock RecordingDataLock;`
- L734 _protected member_ `EChaosVDRecordingAttributes RecordingAttributes = EChaosVDRecordingAttributes::None;`
- L737 _protected member_ `std::atomic<uint64> LastUpdatedTimeAsCycle;` — Last Platform Cycle on which this recording was updated
- L740 _protected member_ `TMap<int32, TSharedPtr<FChaosVDParticleDataWrapper>> ParticlesOnCurrentGeneratedKeyframe;` — Map that temporary holds generated particle data during the key frame generation process, keeping its memory allocation between generated frames
- L742 _protected member_ `TSharedPtr<FChaosVDCollisionChannelsInfoContainer> CollisionChannelsInfoContainer;`
- L744 _protected member_ `TSet<int32> ReservedSolverIDs;`
- L745 _protected member_ `TSet<int32> SolverIDs;`
- L747 _protected member_ `std::atomic<int32> AvailableTrackIDForRemapping = 1;`
- L783 _function_ `template <typename TAllocator> void FChaosVDRecording::GetAvailableSolverIDsAtGameFrameNumber(int32 FrameNumber, TArray<int32, TAllocator>& OutSolversID)`
- L790 _function_ `template <typename TAllocator> void FChaosVDRecording::GetAvailableSolverIDsAtGameFrameNumber_AssumesLocked(int32 FrameNumber, TArray<int32, TAllocator>& OutSolversID)`
- L801 _function_ `template <typename TAllocator> void FChaosVDRecording::GetAvailableSolverIDsAtGameFrame(const FChaosVDGameFrameData& GameFrameData, TArray<int32, TAllocator>& OutSolversID)`
- L808 _function_ `template <typename TAllocator> void FChaosVDRecording::GetAvailableSolverIDsAtGameFrame_AssumesLocked(const FChaosVDGameFrameData& GameFrameData, TArray<int32, TAllocator>& OutSolversID)`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API CHAOSVDDATA_API`
- L27 _namespace_ `namespace Chaos`
- L27 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FChaosVDGeometryDataLoaded, const Chaos::FConstImplicitObjectPtr&, const uint32 GeometryID) struct FChaosVDCustomUserDataHandle { template <typename DataStructType> static FChaosVDCustomUserDataHandle MakeHandle(const TSharedRef<DataStructType>& DataPtr); FName GetTypeName() const; template <typename DataStructType> DataStructType* GetData() const; template <typename DataStructType> TSharedPtr<DataStructType> GetDataAsShared() const; private: template <typename DataStructType> bool IsA_Internal(const TSharedPtr<FStructOnScope>& InStructOnScope) const; TSharedPtr<FStructOnScope> DataStruct; TSharedPtr<void> DataSharedPtr; };`
- L172 _typedef_ `typedef FChaosVDFrameStageData FChaosVDStepData;` — `UE_DEPRECATED(5.6, "FChaosVDStepData is deprecated and will be removed. Please use FChaosVDFrameStageData instead.")`
- L198 _typedef_ `typedef TArray<FChaosVDFrameStageData, TInlineAllocator<16>> FChaosVDStepsContainer;` — `UE_DEPRECATED(5.6, "This FChaosVDStepsContainer is deprecated and it will be removed in the future. Use FChaosVDStagesContainer instead.")`
- L200 _typedef_ `typedef TArray<FChaosVDFrameStageData, TInlineAllocator<16>> FChaosVDFrameStagesContainer;`
