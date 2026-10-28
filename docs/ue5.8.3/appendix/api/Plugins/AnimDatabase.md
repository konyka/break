# Plugins / AnimDatabase

- module root: `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase`
- headers: 7; symbols: 2173
- symbol kinds: class=129, delegate=1, enum=11, enumerator=42, function=6, macro=7, member=600, namespace=16, prototype=1319, struct=42
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DrawDebugLibrary, Engine, InputCore, Json, JsonUtilities, RigVM, UnrealEd
- PublicDependencyModuleNames: Core, Learning

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Private/RigUnit_AnimDatabase.h` (Private)


#### struct `FRigVMFunction_AnimDatabaseBase`  
`struct FRigVMFunction_AnimDatabaseBase : public FRigVMStruct`  
_L21-24_
- reflection: `USTRUCT(meta = (Abstract, Category = "AnimDatabase", NodeColor = "0.83077 0.846873 0.049707", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all Anim Database functions

#### struct `FRigUnit_AnimDatabaseBase`  
`struct FRigUnit_AnimDatabaseBase : public FRigVMStruct`  
_L30-37_
- reflection: `USTRUCT(meta=(Abstract, ExecuteContext = "FRigVMExecuteContext", Category="AnimDatabase", NodeColor = "0.83077 0.846873 0.049707", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: Base class for all Anim Database rig units
- L36 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### struct `FRigVMFunction_FrameAttributeIntersection`  
`struct FRigVMFunction_FrameAttributeIntersection : public FRigVMFunction_AnimDatabaseBase`  
_L41-59_
- reflection: `USTRUCT(meta = (DisplayName = "Intersection"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Frame Attribute Intersection
- L45 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L50 _public member_ `FAnimDatabaseFrameAttribute A;` — `UPROPERTY(meta = (Input))` — Input Frame Attribute
- L54 _public member_ `FAnimDatabaseFrameRanges B;` — `UPROPERTY(meta = (Input))` — Input Frame Ranges
- L58 _public member_ `FAnimDatabaseFrameAttribute Result;` — `UPROPERTY(meta = (Output))` — Output Frame Attribute

#### struct `FRigVMFunction_FrameAttributeAdd`  
`struct FRigVMFunction_FrameAttributeAdd : public FRigVMFunction_AnimDatabaseBase`  
_L63-81_
- reflection: `USTRUCT(meta = (DisplayName = "Add (Frame Attribute)"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Frame Attribute Add
- L67 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L72 _public member_ `FAnimDatabaseFrameAttribute A;` — `UPROPERTY(meta = (Input))` — Input Frame Attribute A
- L76 _public member_ `FAnimDatabaseFrameAttribute B;` — `UPROPERTY(meta = (Input))` — Input Frame Attribute B
- L80 _public member_ `FAnimDatabaseFrameAttribute Result;` — `UPROPERTY(meta = (Output))` — Result Frame Attribute

#### struct `FRigVMFunction_FrameAttributeInertializationMatchingDistance`  
`struct FRigVMFunction_FrameAttributeInertializationMatchingDistance : public FRigVMFunction_AnimDatabaseBase`  
_L85-131_
- reflection: `USTRUCT(meta = (DisplayName = "Inertialization Matching Distance"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Computes a Frame Attribute representing Inertialization Matching Distance
- L89 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L94 _public member_ `FAnimDatabaseFrameAttribute LocationAttribute;` — `UPROPERTY(meta = (Input))` — Location Attribute
- L98 _public member_ `FAnimDatabaseFrameAttribute VelocityAttribute;` — `UPROPERTY(meta = (Input))` — Velocity Attribute
- L102 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Input Location
- L106 _public member_ `FVector Velocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Input Velocity
- L110 _public member_ `float BlendTime = 0.2f;` — `UPROPERTY(meta = (Input))` — Inertialization Blend Time
- L114 _public member_ `float LocationScale = 100.0f;` — `UPROPERTY(meta = (Input))` — Location scales
- L118 _public member_ `float VelocityScale = 200.0f;` — `UPROPERTY(meta = (Input))` — Velocity scales
- L122 _public member_ `float LocationWeight = 1.0f;` — `UPROPERTY(meta = (Input))` — Location weight
- L126 _public member_ `float VelocityWeight = 1.0f;` — `UPROPERTY(meta = (Input))` — Velocity weight
- L130 _public member_ `FAnimDatabaseFrameAttribute Result;` — `UPROPERTY(meta = (Output))` — Resulting Distance Attribute

#### struct `FRigUnit_FindFrameAttributeMinimumSequence`  
`struct FRigUnit_FindFrameAttributeMinimumSequence : public FRigUnit_AnimDatabaseBase`  
_L135-165_
- reflection: `USTRUCT(meta = (DisplayName = "Find Frame Attribute Minimum Sequence"))`
- inherits: `FRigUnit_AnimDatabaseBase`
- desc: Finds the AnimSequence corresponding to the minimum value in a frame attribute
- L139 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L144 _public member_ `FAnimDatabaseFrameAttribute Attribute;` — `UPROPERTY(meta = (Input))` — Input Attribute
- L148 _public member_ `TObjectPtr<UAnimDatabase> Database;` — `UPROPERTY(meta = (Input))` — Input Database
- L152 _public member_ `TObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(meta = (Output))` — Output Anim Sequence
- L156 _public member_ `float SequenceTime = 0.0f;` — `UPROPERTY(meta = (Output))` — Output Anim Sequence Time
- L160 _public member_ `bool bIsMirrored = false;` — `UPROPERTY(meta = (Output))` — If the output Anim Sequence should be mirrored
- L164 _public member_ `float MinimumValue = 0.0f;` — `UPROPERTY(meta = (Output))` — Output minimum value

#### struct `FRigVMFunction_MakeFloatFrameAttributeFromUniformRandom`  
`struct FRigVMFunction_MakeFloatFrameAttributeFromUniformRandom : public FRigVMFunction_AnimDatabaseBase`  
_L169-195_
- reflection: `USTRUCT(meta = (DisplayName = "Make Float Frame Attribute from Uniform Random"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Makes a float frame attribute from a uniform distribution.
- L173 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L178 _public member_ `FAnimDatabaseFrameRanges FrameRanges;` — `UPROPERTY(meta = (Input))` — Input Frame Ranges
- L182 _public member_ `int32 Seed = 1234;` — `UPROPERTY(meta = (Input, Output))` — Random State
- L186 _public member_ `float Min = 0.0f;` — `UPROPERTY(meta = (Input))` — Minimum Value
- L190 _public member_ `float Max = 1.0f;` — `UPROPERTY(meta = (Input))` — Maximum Value
- L194 _public member_ `FAnimDatabaseFrameAttribute Result;` — `UPROPERTY(meta = (Output))` — Result Float Frame Attribute

#### struct `FRigVMFunction_DatabaseIndexGetDatabase`  
`struct FRigVMFunction_DatabaseIndexGetDatabase : public FRigVMFunction_AnimDatabaseBase`  
_L199-213_
- reflection: `USTRUCT(meta = (DisplayName = "Get Database (Database Index)"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Gets the Database from a DatabaseIndex
- L203 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L208 _public member_ `TObjectPtr<UAnimDatabaseIndex> Index;` — `UPROPERTY(meta = (Input))` — Database Index
- L212 _public member_ `TObjectPtr<UAnimDatabase> Database;` — `UPROPERTY(meta = (Output))` — Output Database

#### struct `FRigVMFunction_FindDatabaseIndexFrames`  
`struct FRigVMFunction_FindDatabaseIndexFrames : public FRigVMFunction_AnimDatabaseBase`  
_L217-239_
- reflection: `USTRUCT(meta = (DisplayName = "Find Database Index Frames"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Find frames in a Database Index
- L221 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L226 _public member_ `TObjectPtr<UAnimDatabaseIndex> Index;` — `UPROPERTY(meta = (Input))` — Database Index
- L230 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — Name to look-up
- L234 _public member_ `bool bFound = false;` — `UPROPERTY(meta = (Output))` — Output Found
- L238 _public member_ `FAnimDatabaseFrames Frames;` — `UPROPERTY(meta = (Output))` — Output Frames

#### struct `FRigVMFunction_FindDatabaseIndexFrameRanges`  
`struct FRigVMFunction_FindDatabaseIndexFrameRanges : public FRigVMFunction_AnimDatabaseBase`  
_L243-265_
- reflection: `USTRUCT(meta = (DisplayName = "Find Database Index Frame Ranges"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Find frame ranges in a Database Index
- L247 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L252 _public member_ `TObjectPtr<UAnimDatabaseIndex> Index;` — `UPROPERTY(meta = (Input))` — Database Index
- L256 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — Name to look-up
- L260 _public member_ `bool bFound = false;` — `UPROPERTY(meta = (Output))` — Output Found
- L264 _public member_ `FAnimDatabaseFrameRanges FrameRanges;` — `UPROPERTY(meta = (Output))` — Output Frame Ranges

#### struct `FRigVMFunction_FindDatabaseIndexFrameAttribute`  
`struct FRigVMFunction_FindDatabaseIndexFrameAttribute : public FRigVMFunction_AnimDatabaseBase`  
_L269-291_
- reflection: `USTRUCT(meta = (DisplayName = "Find Database Index Frame Attribute"))`
- inherits: `FRigVMFunction_AnimDatabaseBase`
- desc: Find frame attributes in a Database Index
- L273 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L278 _public member_ `TObjectPtr<UAnimDatabaseIndex> Index;` — `UPROPERTY(meta = (Input))` — Database Index
- L282 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — Name to look-up
- L286 _public member_ `bool bFound = false;` — `UPROPERTY(meta = (Output))` — Output Found
- L290 _public member_ `FAnimDatabaseFrameAttribute FrameAttribute;` — `UPROPERTY(meta = (Output))` — Output Frame Attribute

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMDATABASE_API`

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Public/AnimDatabase.h` (Public)


#### class `FAnimDatabaseModule`  
`class FAnimDatabaseModule : public IModuleInterface`  
_L52-58_
- inherits: `IModuleInterface`
- L57 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation

#### enum `EAnimDatabaseRotationOrder`  
`enum class EAnimDatabaseRotationOrder : uint8`  
_L66-74_
- reflection: `UENUM(BlueprintType)`
- desc: Rotation order used when exporting data as euler angles
- L68 _public enumerator_ `XYZ`
- L69 _public enumerator_ `XZY`
- L70 _public enumerator_ `YXZ`
- L71 _public enumerator_ `YZX`
- L72 _public enumerator_ `ZXY`
- L73 _public enumerator_ `ZYX`

#### enum `EAnimDatabaseTransformMode`  
`enum class EAnimDatabaseTransformMode : uint8`  
_L78-83_
- reflection: `UENUM(BlueprintType)`
- desc: Transform mode for use with animation database functions
- L80 _public enumerator_ `PreMultiply`
- L81 _public enumerator_ `PostMultiply`
- L82 _public enumerator_ `Replace`

#### class `UAnimDatabaseViewportSettings`  
`class UAnimDatabaseViewportSettings : public UObject`  
_L89-268_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class containing all the UAnimDatabase Editor window viewport settings
- L99 _public member_ `TObjectPtr<USkeletalMesh> PreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Mesh to use for previewing the character
- L105 _public member_ `bool bDrawSkeleton = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton")` — If to draw the skeleton of all characters
- L109 _public member_ `bool bDrawSimpleSkeleton = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — Draw a simple skeleton made up of lines connecting bones
- L113 _public member_ `float DrawSkeletonOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — Opacity of the drawn skeleton
- L117 _public member_ `float DrawSkeletonScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — The scale of the drawn skeleton bones
- L121 _public member_ `bool bDrawMeshBonesOnly = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to only draw the skeleton of the mesh bones used by the PreviewMesh
- L125 _public member_ `int32 DrawMeshBonesLOD = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "5", UIMax = "5", EditCondition = "bDrawSkeleton && bDrawMeshBonesOnly", HideEditConditionToggle))` — Mesh bone LOD index to use when only drawing mesh bones
- L129 _public member_ `bool bDrawBoneNamesAndIndices = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — Draw the bone names and indices
- L133 _public member_ `bool bDrawLinearVelocities = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to draw linear velocities for each of the skeleton's bones
- L137 _public member_ `float DrawLinearVelocitiesScale = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawSkeleton && bDrawLinearVelocities", HideEditConditionToggle))` — The scale of the linear velocities being drawn
- L141 _public member_ `float DrawLinearVelocitiesOpacity = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawSkeleton && bDrawLinearVelocities", HideEditConditionToggle))` — Opacity of the linear velocities being drawn
- L145 _public member_ `bool bDrawAngularVelocities = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to draw angular velocities for each of the skeleton's bones
- L149 _public member_ `float DrawAngularVelocitiesScale = 2.5f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawSkeleton && bDrawAngularVelocities", HideEditConditionToggle))` — The scale of the angular velocities being drawn
- L153 _public member_ `float DrawAngularVelocitiesOpacity = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawSkeleton && bDrawAngularVelocities", HideEditConditionToggle))` — Opacity of the angular velocities being drawn
- L157 _public member_ `bool bDrawBoneTransforms = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to draw bone transforms
- L163 _public member_ `bool bDrawRoot = true;` — `UPROPERTY(EditAnywhere, Category = "Root")` — If to draw the root of the skeleton as a transform
- L167 _public member_ `float DrawRootOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Root", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawRoot", HideEditConditionToggle))` — Opacity of the drawn root
- L171 _public member_ `float DrawRootScale = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Root", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRoot", HideEditConditionToggle))` — The scale of the drawn root
- L177 _public member_ `bool bDrawTrajectories = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — If to draw the trajectories of the selected ranges
- L181 _public member_ `bool bDrawTrajectoryOrientations = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (EditCondition = "bDrawTrajectories", HideEditConditionToggle))` — If to draw the trajectory orientations of the selected ranges
- L187 _public member_ `bool bRangesStartAtOrigin = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — Re-orients all ranges so that they start at the scene origin rather than wherever they started in the source data
- L191 _public member_ `bool bOffsetRanges = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin", HideEditConditionToggle))` — Offset different ranges away from origin so they can be viewed together
- L195 _public member_ `float RangeOffsetSpacing = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bOffsetRanges", HideEditConditionToggle))` — Spacing to use for offsetting ranges
- L199 _public member_ `bool bOffsetRangesInGrid = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bOffsetRanges", HideEditConditionToggle))` — If to offset selected ranges as a grid
- L203 _public member_ `bool bAccumulateRootMotion = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to accumulate root motion during playback
- L207 _public member_ `bool bDisableRootTranslation = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin", HideEditConditionToggle))` — Remove root translation when display ranges
- L211 _public member_ `bool bDisableRootRotation = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin && bDisableRootTranslation", HideEditConditionToggle))` — Remove root rotation when display ranges
- L215 _public member_ `bool bDrawRangeIdentifier = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to draw the colored range identifier over the character to show which range in the query the animation is from
- L219 _public member_ `int32 RangeIdentifierColorSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — Seed used for the colors of the range identifiers
- L223 _public member_ `bool bColorSkeletonBonesUsingRangeIdentifier = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to color the skeleton bones using the range identifier color
- L227 _public member_ `float DrawRangeIdentifierThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Thickness of the range identifier
- L231 _public member_ `float DrawRangeIdentifierRadius = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Radius of the range identifier
- L235 _public member_ `float DrawRangeIdentifierOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Opacity of the range identifier
- L239 _public member_ `float DrawRangeIdentifierHeight = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Height offset used to draw the range identifier
- L243 _public member_ `bool bOverrideRangeIdentifierColor = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to override the range identifier color
- L247 _public member_ `FLinearColor RangeIdentifierColorOverride = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bOverrideRangeIdentifierColor", HideEditConditionToggle))` — Color to use to override the range identifier
- L253 _public member_ `bool bDrawOrigin = true;` — `UPROPERTY(EditAnywhere, Category = "Origin")` — If to draw the scene origin as a transform
- L257 _public member_ `float DrawOriginLineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Thickness of the drawn scene origin
- L261 _public member_ `float DrawOriginOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Opacity of the drawn scene origin
- L265 _public member_ `float DrawOriginScale = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Scale of the drawn scene origin

#### struct `UE::AnimDatabase::Editor::FQueryEntry`  
`struct FQueryEntry`  
_L275-284_
- desc: An entry in the list of queries used by UAnimDatabaseQuery.
- L277 _public member_ `const UAnimSequence* Sequence = nullptr;`
- L278 _public member_ `FString Name;`
- L279 _public member_ `int32 StartFrame = 0;`
- L280 _public member_ `int32 StopFrame = 0;`
- L281 _public member_ `bool bIsMirrored = false;`
- L282 _public member_ `bool bIsSelected = false;`
- L283 _public member_ `FLinearColor Color = FLinearColor::Black;`

#### enum `EAnimDatabaseFunctionQueryRanges`  
`enum class EAnimDatabaseFunctionQueryRanges : uint8`  
_L289-295_
- reflection: `UENUM(BlueprintType)`
- desc: Which ranges to pass from the query to the database function
- L291 _public enumerator_ `Database = 0`
- L292 _public enumerator_ `Query = 1`
- L293 _public enumerator_ `Selection = 2`
- L294 _public enumerator_ `Custom = 3`

#### class `UAnimDatabaseQuery`  
`class UAnimDatabaseQuery : public UObject`  
_L302-419_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This class is used for displaying the query window in the UAnimDatabase UI. The query window is implemented as a details customization of this class.
- L312 _public prototype_ `void ForceRefresh();` — `UFUNCTION(CallInEditor, Category = "Query", DisplayName = "Refresh")` — Forces a refresh of the query object
- L320 _public member_ `TObjectPtr<UAnimDatabase> Database;` — `UPROPERTY()` — A pointer to the query database, used when constructing the query ranges
- L323 _public member_ `bool bForceRefresh = false;` — Flag to force refresh the query during update
- L326 _public member_ `int32 DatabaseContentHash = 0;` — This hash is used to detect when the database might have changed and re-run the query
- L330 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Query")` — The query class being used to filter the database
- L333 _public member_ `FAnimDatabaseFrameRanges QueryRanges;` — Query Ranges object for the current query
- L336 _public member_ `TArray<TSharedPtr<UE::AnimDatabase::Editor::FQueryEntry>> QueryEntries;` — List of UI entries for the current query
- L339 _public member_ `TArray<int32> ActiveRanges;` — Temporary array of active ranges used to compare selected ranges
- L342 _public member_ `TArray<int32> SelectedRanges;` — Indices of all the currently selected ranges
- L345 _public member_ `FAnimDatabaseFrameRanges SelectedFrameRanges;` — The frame ranges of the selected ranges
- L348 _public member_ `int32 RangeIdentifierColorSeed = 1234;` — Seed used for the colors of the range identifiers
- L358 _public prototype_ `bool Update();` — Checks if QueryRanges needs updating, and if so updates it. returns true if QueryRanges was updated (and therefore the UI may need updating), otherwise false.
- L361 _public prototype_ `void DeleteSelectedFromDatabase();` — Deletes the selected sequences from the database
- L366 _private prototype_ `void UpdateQueryEntries();` — Internal function for updating the QueryEntries array from an updated QueryRanges
- L376 _public member_ `TArray<FAnimDatabaseFramesEntry> AdditionalFrames;` — `UPROPERTY(EditAnywhere, Category = "Timeline")` — Additional Frames to display in the timeline
- L380 _public member_ `TArray<FAnimDatabaseFrameRangesEntry> AdditionalFrameRanges;` — `UPROPERTY(EditAnywhere, Category = "Timeline")` — Additional Frame Ranges to display in the timeline
- L384 _public member_ `TArray<FAnimDatabaseFrameAttributeEntry> AdditionalFrameAttributes;` — `UPROPERTY(EditAnywhere, Category = "Timeline")` — Additional Frame Attributes to display in the timeline
- L390 _public member_ `TObjectPtr<UAnimDatabaseDebugDraw> DebugDrawer;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Debug Draw")` — Custom debug draw object that can be used to add additional debug draw behavior
- L396 _public member_ `EAnimDatabaseFunctionQueryRanges FunctionRanges = EAnimDatabaseFunctionQueryRanges::Database;` — `UPROPERTY(EditAnywhere, Category = "Function")` — Which set of ranges to pass to the database function
- L400 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> CustomFrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Function", meta = (EditCondition = "FunctionRanges == EAnimDatabaseFunctionQueryRanges::Custom", EditConditionHides))` — Custom frame ranges to use for the database function
- L404 _public member_ `bool bFunctionShouldTransact = true;` — `UPROPERTY(EditAnywhere, Category = "Function")` — If the function call should transact (be undo-able)
- L408 _public member_ `TObjectPtr<UAnimDatabaseFunction> FunctionObject;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Function")` — Function object to call
- L416 _public prototype_ `void RunFunction();` — `UFUNCTION(CallInEditor, Category = "Function", DisplayName = "Run Function")` — Evaluate the given function on the database with the chosen ranges

#### enum `EAnimDatabaseSampler`  
`enum class EAnimDatabaseSampler : uint8`  
_L424-458_
- reflection: `UENUM(BlueprintType)`
- L432 _public enumerator_ `Nearest` — Snaps to the nearest keyframe in the animation sequence. This interpolation mode is not recommended for downstream tasks since it does not produce any velocities when you sample the animation data, but may be useful for debugging and inspecting the data.
- L441 _public enumerator_ `Linear` — Linearly interpolates animation data. This will give the same result as what is seen in the AnimSequence asset viewer. The main problem with this interpolation method is that it produces a velocity discontinuity as it switches key-frames. This means velocities tend to change in discrete jumps and sometimes the velocity discontinuity is visible when playing the animation back slowly.
- L449 _public enumerator_ `Cubic` — Interpolations animation data using a cubic catmull-rom spline. This produces a smooth interpolation of the animation data with smoothly varying velocities. The only potential downside of this method is that it can produce "over-shooting" where the joint rotations and translations can over-extend past the keyframes during the interpolation period.
- L457 _public enumerator_ `CubicMono` — Interpolates animation data using a monotone cubic spline. This produces a similar result to the Cubic interpolation but uses monotone interpolation to ensure that the animation pose never "over-shoots" during the interpolation. The cost of this is that CubicMono interpolation can sometimes produce more shaky looking motion at end-effectors.

#### class `UAnimDatabase`  
`class UAnimDatabase : public UDataAsset`  
_L473-825_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Animation", meta = (DisplayName = "Animation Database"))`
- inherits: `UDataAsset`
- desc: Animation Database Asset This asset contains an array of animations, as well as a skeleton, and a mirror table. It is assumed that all added animations should match the provided skeleton. As well as providing a hook for a custom UI and tooling, this asset provides functions for sampling animation data at a single uniform framerate and in the pose representation used by the database. The number of "Sequences" in this database (as returned by GetSequenceNum()) will be two times the number of entries in "Entries" when the mirror data table is present and valid, otherwise it will be the same as the number of entries.
- L479 _private prototype_ `UAnimDatabase(const FObjectInitializer& ObjectInitializer);`
- L485 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Skeleton structure for Animation Sequences
- L489 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Mirror Data Table. Leave as null if you don't want to include mirrored animations in the database.
- L493 _public member_ `FFrameRate FrameRate = FFrameRate(60, 1);` — `UPROPERTY(EditAnywhere, Category = "Database")` — FrameRate to use for sampling the database. This should generally set to the target frame rate of your game.
- L497 _public member_ `EAnimDatabaseSampler PoseSampler = EAnimDatabaseSampler::Cubic;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Interpolation method used for sampling poses in the database.
- L501 _public member_ `EAnimDatabaseSampler CurveSampler = EAnimDatabaseSampler::Linear;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Interpolation method used for sampling curves in the database.
- L505 _public member_ `TArray<TObjectPtr<UAnimSequence>> Entries;` — `UPROPERTY(EditAnywhere, Category = "Database")` — List of Animations in Database
- L513 _public member_ `FAnimDatabaseOnSkeletonChanged OnSkeletonChanged;` — Callback to fire when the skeleton is changed
- L518 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& Event) override;` — We use this to ensure that entries added have a matching skeleton
- L528 _public prototype_ `int32 GetContentHash() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets a hash value which can be used to test if the underlying content in the database, or database properties have changed. This hash should not be relied on for detecting changes with certainty, and so should only be used for non-critical purposes (e.g. UI updates).
- L534 _public prototype_ `FFrameRate GetFrameRate() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the database frame rate
- L538 _public prototype_ `USkeleton* GetSkeleton() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get a pointer to the database skeleton
- L542 _public prototype_ `UMirrorDataTable* GetMirrorDataTable() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get a pointer to the database mirror table
- L546 _public prototype_ `int32 GetBoneNum() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the number of bones in the database skeleton
- L550 _public prototype_ `FName GetBoneName(const int32 BoneIndex) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone name for the given bone index in the database skeleton
- L554 _public prototype_ `void GetBoneNames(TArray<FName>& OutBoneNames) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone names for all bones on the skeleton
- L555 _public prototype_ `void GetBoneNamesToArrayView(TArrayView<FName> OutBoneNames) const;`
- L559 _public prototype_ `int32 FindBoneIndex(const FName BoneName) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds the bone index for a given bone name in the database skeleton
- L563 _public prototype_ `void FindBoneIndices(TArray<int32>& OutBoneIndices, const TArray<FName>& BoneNames) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds the bone indices associated with the given bone names in the database skeleton
- L564 _public prototype_ `void FindBoneIndicesFromArrayViews(const TArrayView<int32> OutBoneIndices, const TArrayView<const FName> BoneNames) const;`
- L568 _public prototype_ `int32 GetBoneParent(const int32 BoneIndex) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the parent bone index
- L572 _public prototype_ `void GetBoneParents(TArray<int32>& OutParents) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the array of bone parent indices for the database skeleton
- L573 _public prototype_ `void GetBoneParentsToArrayView(const TArrayView<int32> OutParents) const;`
- L579 _public prototype_ `int32 GetSequenceNum() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the number of sequences in the database. This will be two times the number of entries when a mirror table is provided.
- L583 _public prototype_ `int32 FindSequenceIndex(UAnimSequence* AnimSequence, const bool bIsMirrored) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds the sequence index associated with a given animation
- L587 _public prototype_ `UAnimSequence* GetAnimSequence(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets a pointer for the animation corresponding to a particular sequence index
- L594 _public prototype_ `void WaitForCompressionOnAnimSequence(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase")` — Waits for the animation compression to complete for the given sequence. It is generally best to do this before trying to sample a sequence as otherwise the evaluation can be incredibly slow.
- L601 _public prototype_ `void WaitForCompressionOnAnimSequences(const TArray<int32>& SequenceIndices) const;` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase")` — Waits for the animation compression to complete for the given sequences. It is generally best to do this before trying to sample a sequence as otherwise the evaluation can be incredibly slow.
- L602 _public prototype_ `void WaitForCompressionOnAnimSequencesFromArrayView(const TArrayView<const int32> SequenceIndices) const;`
- L603 _public prototype_ `void WaitForCompressionOnAll() const;`
- L607 _public prototype_ `bool GetIsMirrored(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns if a given sequence index is for a mirrored animation or not
- L611 _public prototype_ `float GetSequenceDuration(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns the duration of a sequence in seconds
- L615 _public prototype_ `int32 GetSequenceFrameNum(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the number of frames in a sequence
- L619 _public prototype_ `FString GetSequenceAssetName(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the asset name for a sequence index
- L623 _public prototype_ `FString GetSequencePathString(const int32 SequenceIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the path string for a sequence index
- L627 _public prototype_ `float GetTotalDuration() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the total duration of all sequences
- L631 _public prototype_ `int32 GetTotalFrameNum() const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the total number of frames across all sequences
- L635 _public prototype_ `float GetSequenceTimeFromFrame(const int32 SequenceIdx, const int32 FrameIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the sequence time for the start of a given frame
- L639 _public prototype_ `int32 GetClosestFrameFromSequenceTime(const int32 SequenceIdx, const float SequenceTime) const;` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the closest frame associated with a sequence time
- L645 _public prototype_ `FVector GetBoneReferenceLocation(const int32 BoneIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone location in the reference skeleton
- L649 _public prototype_ `void GetBoneReferenceLocations(TArray<FVector>& OutReferenceLocations);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone locations in the reference skeleton
- L650 _public prototype_ `void GetBoneReferenceLocationsToArrayView(TArrayView<FVector> OutReferenceLocations);`
- L654 _public prototype_ `FQuat GetBoneReferenceRotation(const int32 BoneIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone rotation in the reference skeleton
- L658 _public prototype_ `void GetBoneReferenceRotations(TArray<FQuat>& OutReferenceRotations);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone rotations in the reference skeleton
- L659 _public prototype_ `void GetBoneReferenceRotationsToArrayView(TArrayView<FQuat> OutReferenceRotations);`
- L663 _public prototype_ `FVector GetBoneReferenceScale(const int32 BoneIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets the bone scale in the reference skeleton
- L668 _public prototype_ `void GetRootTransform(const TLearningArrayView<1, FTransform> OutTransforms, const int32 SequenceIdx, const int32 FrameStart) const;` — Gets the root transform for a given sequence and start frame
- L671 _public prototype_ `void GetRootLocation(const TLearningArrayView<1, FVector> OutLocations, const int32 SequenceIdx, const int32 FrameStart) const;` — Gets the root location for a given sequence and start frame
- L674 _public prototype_ `void GetRootRotation(const TLearningArrayView<1, FQuat4f> OutRotations, const int32 SequenceIdx, const int32 FrameStart) const;` — Gets the root rotation for a given sequence and start frame
- L677 _public prototype_ `void GetRootDirection(const TLearningArrayView<1, FVector3f> OutDirections, const int32 SequenceIdx, const int32 FrameStart, const FVector3f ForwardVector = FVector3f(0.0f, 1.0f, 0.0f)) const;` — Gets the root direction for a given sequence and start frame
- L680 _public prototype_ `void GetRootLinearVelocity(const TLearningArrayView<1, FVector3f> OutLinearVelocities, const int32 SequenceIdx, const int32 FrameStart) const;` — Gets the root linear velocity for a given sequence and start frame
- L683 _public prototype_ `void GetRootAngularVelocity(const TLearningArrayView<1, FVector3f> OutAngularVelocities, const int32 SequenceIdx, const int32 FrameStart) const;` — Gets the root angular velocity for a given sequence and start frame
- L686 _public prototype_ `void GetPoseRootData( const UE::AnimDatabase::FPoseRootDataView& OutPoseRootData, const int32 SequenceIdx, const int32 FrameStart) const;` — Get a number of frames of root data for a given sequence and frame range
- L692 _public prototype_ `void GetPoseLocalBoneData( const UE::AnimDatabase::FPoseLocalBoneDataView& OutPoseLocalBoneData, const int32 SequenceIdx, const int32 FrameStart) const;` — Gets a number of frames of local bone data for a given sequence and frame range
- L698 _public prototype_ `void GetPoseLocalBoneSubsetData( const UE::AnimDatabase::FPoseLocalBoneDataView& OutPoseLocalBoneData, const int32 SequenceIdx, const int32 FrameStart, const UE::Learning::FIndexSet BoneIndices) const;` — Gets a number of frames of local bone data for a given sequence and frame range, and a subset of bones
- L705 _public prototype_ `void GetCurveActiveData( const TLearningArrayView<2, bool> OutCurveActive, const int32 SequenceIdx, const int32 FrameStart, const TArrayView<const FName> CurveNames) const;` — Gets if the given curves are active for a given sequence and frame range
- L712 _public prototype_ `void GetCurveData( const TLearningArrayView<2, float> OutCurveValues, const TLearningArrayView<2, float> OutCurveVelocities, const TLearningArrayView<2, bool> OutCurveActive, const int32 SequenceIdx, const int32 FrameStart, const TArrayView<const FName> CurveNames) const;` — Gets curve data for a given sequence and frame range
- L721 _public prototype_ `void GetAttributeData( const UE::AnimDatabase::FPoseAttributeDataView& OutAttributeData, const int32 SequenceIdx, const int32 FrameStart, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes) const;` — Gets a number of frames of attribute data for a given sequence and frame range
- L728 _public prototype_ `void GetPoseData( const UE::AnimDatabase::FPoseDataView& OutPoseData, const int32 SequenceIdx, const int32 FrameStart, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes = {}) const;` — Gets a number of frames of pose data for a given sequence and frame range
- L735 _public prototype_ `void GetPoseSubsetData( const UE::AnimDatabase::FPoseDataView& OutPoseData, const int32 SequenceIdx, const int32 FrameStart, const UE::Learning::FIndexSet BoneIndices, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes = {}) const;` — Gets a number of frames of pose data for a given sequence and frame range, and a subset of bones
- L745 _public prototype_ `FTransform SampleRootTransform(const int32 SequenceIdx, const float SequenceTime) const;` — Samples the root transform for a given sequence and sequence time
- L748 _public prototype_ `FVector SampleRootLocation(const int32 SequenceIdx, const float SequenceTime) const;` — Samples the root location for a given sequence and sequence time
- L751 _public prototype_ `FQuat4f SampleRootRotation(const int32 SequenceIdx, const float SequenceTime) const;` — Samples the root rotation for a given sequence and sequence time
- L754 _public prototype_ `FVector3f SampleRootDirection(const int32 SequenceIdx, const float SequenceTime, const FVector3f ForwardVector = FVector3f(0.0f, 1.0f, 0.0f)) const;` — Samples the root direction for a given sequence and sequence time
- L757 _public prototype_ `FVector3f SampleRootLinearVelocity(const int32 SequenceIdx, const float SequenceTime) const;` — Samples the root linear velocity for a given sequence and sequence time
- L760 _public prototype_ `void SamplePoseRootData( const UE::AnimDatabase::FPoseRootDataView& OutPoseRootData, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes) const;` — Samples root data for the given sequences and times in those sequences
- L766 _public prototype_ `void SamplePoseLocalBoneData( const UE::AnimDatabase::FPoseLocalBoneDataView& OutPoseLocalBoneData, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes) const;` — Samples local bone data for the given sequences and times in those sequences
- L772 _public prototype_ `void SamplePoseLocalBoneSubsetData( const UE::AnimDatabase::FPoseLocalBoneDataView& OutPoseLocalBoneData, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes, const UE::Learning::FIndexSet BoneIndices) const;` — Samples local bone data for the given sequences and times in those sequences, and a subset of bones.
- L779 _public prototype_ `void SampleCurveActiveData( const TLearningArrayView<2, bool> OutCurveActive, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes, const TArrayView<const FName> CurveNames) const;` — Samples if curve are active for the given sequences and times in those sequences.
- L786 _public prototype_ `void SampleCurveData( const TLearningArrayView<2, float> OutCurveValues, const TLearningArrayView<2, float> OutCurveVelocities, const TLearningArrayView<2, bool> OutCurveActive, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes, const TArrayView<const FName> CurveNames) const;` — Samples curve data for the given sequences and times in those sequences.
- L795 _public prototype_ `void SampleAttributeData( const UE::AnimDatabase::FPoseAttributeDataView& OutAttributeData, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes, const TLearningArrayView<1, const FAnimDatabaseFrameAttribute> FrameAttributes) const;` — Samples attribute data for the given sequences and times in those sequences.
- L802 _public prototype_ `void SamplePoseData( const UE::AnimDatabase::FPoseDataView& OutPoseData, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes, const TLearningArrayView<1, const FAnimDatabaseFrameAttribute> FrameAttributes = {}) const;` — Samples pose data for the given sequences and times in those sequences.
- L809 _public prototype_ `void SamplePoseSubsetData( const UE::AnimDatabase::FPoseDataView& OutPoseData, const TLearningArrayView<1, const int32> SequenceIndices, const TLearningArrayView<1, const float> SequenceTimes, const UE::Learning::FIndexSet BoneIndices, const TLearningArrayView<1, const FAnimDatabaseFrameAttribute> FrameAttributes = {}) const;` — Samples pose data for the given sequences and times in those sequences, for a subset of bones.
- L820 _public member_ `TObjectPtr<UAnimDatabaseViewportSettings> ViewportSettings;` — `UPROPERTY(Instanced)` — Editor-only object containing the viewport settings for the editor window
- L824 _public member_ `TObjectPtr<UAnimDatabaseQuery> Query;` — `UPROPERTY(Instanced)` — Editor-only object containing the query state for the editor window

#### class `UAnimDatabaseFunction`  
`class UAnimDatabaseFunction : public UObject`  
_L831-844_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Class that can be implemented to perform an operation on an animation database
- L841 _public prototype_ `void Run(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimDatabase", meta = (ForceAsFunction))` — Run the database function on the provided database and frame ranges

#### class `UAnimDatabaseLibrary`  
`class UAnimDatabaseLibrary : public UBlueprintFunctionLibrary`  
_L854-1074_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: A blueprint library providing functions for writing back frame attribute data into an animation database. This library provides something akin to AnimModifiers, where it becomes possible to write an asset action which can extract some frame attributes and then write these back to the animation data either in the form of AnimNotifies, AnimNotifyStates, Curves, or modifications to bone transforms. This method of AnimModifiers is far more efficient as it can be scripted via blueprints but still perform processing in batch.
- L862 _public prototype_ `static void GetAnimSequenceAnimNotifyClasses(TArray<TSubclassOf<UAnimNotify>>& OutClasses, UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase")` — Gets all the AnimNotify classes present in a given AnimSequence
- L866 _public prototype_ `static void GetAnimSequenceAnimNotifyStateClasses(TArray<TSubclassOf<UAnimNotifyState>>& OutClasses, UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase")` — Gets all the AnimNotifyState classes present in a given AnimSequence
- L870 _public prototype_ `static void GetAnimSequenceAnimNotifyTimes(TArray<float>& OutTimes, const TSubclassOf<UAnimNotify>& Class, UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase")` — Gets the times of each AnimNotify of the given class, in the given sequence
- L874 _public prototype_ `static void GetAnimSequenceAnimNotifyStateTimesAndDurations(TArray<float>& OutTimes, TArray<float>& OutDurations, const TSubclassOf<UAnimNotifyState>& Class, UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase")` — Gets the times and durations of each AnimNotifyState of the given class, in the given sequence
- L877 _public prototype_ `static void SetAnimSequencePoseData( UAnimSequence* AnimSequence, TScriptInterface<IAnimationDataController> Controller, const int32 StartFrame, const UE::AnimDatabase::FPoseDataConstView& PoseData, const UE::Learning::FIndexSet UsedBones, const bool bShouldTransact = false);` — Sets the pose data on a sequence using the given FPoseDataConstView
- L887 _public prototype_ `static void AddAnimNotifiesToSequence(UAnimSequence* AnimSequence, const FName TrackName, const TSubclassOf<UAnimNotify>& Class, const TArray<float>& Times);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Adds AnimNotifies of the provided class to a sequence at the given times
- L888 _public prototype_ `static void AddAnimNotifiesToSequenceArrayView(UAnimSequence* AnimSequence, const FName TrackName, const TSubclassOf<UAnimNotify>& Class, const TArrayView<const float> Times);`
- L892 _public prototype_ `static void AddAnimNotifyStatesToSequence(UAnimSequence* AnimSequence, const FName TrackName, const TSubclassOf<UAnimNotifyState>& Class, const TArray<float>& Times, const TArray<float>& Durations);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Adds AnimNotifyStates of the provided class to a sequence at the given times with the given durations
- L893 _public prototype_ `static void AddAnimNotifyStatesToSequenceArrayView(UAnimSequence* AnimSequence, const FName TrackName, const TSubclassOf<UAnimNotifyState>& Class, const TArrayView<const float> Times, const TArrayView<const float> Durations);`
- L897 _public prototype_ `static void RemoveAllAnimNotifiesAndAnimNotifyStatesFromSequence(UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Removes all AnimNotifies and AnimNotifyStates from a sequence
- L901 _public prototype_ `static void EnableRootMotionAndForceRootLockOnSequences(const TArray<UAnimSequence*>& Sequences);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Enables root motion and force root lock on the given animation sequences
- L902 _public prototype_ `static void EnableRootMotionAndForceRootLockOnSequencesArrayView(TConstArrayView<UAnimSequence*> Sequences);`
- L908 _public prototype_ `static void DatabaseRemoveNotifies(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Removes all AnimNotifies and AnimNotifyStates from the given frame ranges
- L912 _public prototype_ `static void DatabaseExportNotifies(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FFilePath& Path);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, RelativePath, FilePathFilter = "json"))` — Exports all AnimNotifies and AnimNotifyStates as JSON
- L916 _public prototype_ `static void DatabaseImportNotifies(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FFilePath& Path);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, RelativePath, FilePathFilter = "json"))` — Imports AnimNotifies and AnimNotifyStates from a JSON file
- L922 _public prototype_ `static void DatabaseExportAsBVH(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FDirectoryPath& Path, const bool bAddRootAxesChangeRotation = true, const EAnimDatabaseRotationOrder RotationOrder = EAnimDatabaseRotationOrder::XYZ);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, RelativePath))` — Exports the given frame ranges in the database as BVH files into the provided directory
- L926 _public prototype_ `static void DatabaseImportFromBVH(UAnimDatabase* Database, const FDirectoryPath& ImportPath, const FDirectoryPath& AssetPath, const bool bRemoveRootAxesChangeRotation = true, const bool bAddToDatabase = true, const bool bIgnoreMirrored = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, RelativePath))` — Imports all the BVH files from the given ImportPath directory into the AssetPath directory and adds them to the database
- L930 _public prototype_ `static void DatabaseExportAsAnimSequences(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FDirectoryPath& Path, const FString& AssetNameFormatString, const bool bExportMirrored, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, RelativePath))` — Exports the given frame ranges in the database as AnimSequences into the provided path
- L934 _public prototype_ `static void DatabaseExportRootMotion(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FFilePath& Path);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, RelativePath, FilePathFilter = "json"))` — Exports the root motion of given frame ranges in the database as a JSON file
- L940 _public prototype_ `static void DatabaseAddCurve(UAnimDatabase* Database, const FName CurveName, const FAnimDatabaseFrameAttribute& FloatFrameAttribute, const FLinearColor Color = FLinearColor::Red, const bool bSparseKeys = false, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Write the provided float frame attribute back to the animations in the database with the given curve name
- L944 _public prototype_ `static void DatabaseAddCurves(UAnimDatabase* Database, const TArray<FName>& CurveNames, const TArray<FAnimDatabaseFrameAttribute>& FloatFrameAttributes, const TArray<FLinearColor>& Colors, const bool bSparseKeys = false, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, AutoCreateRefTerm = "Colors"))` — Write the provided float frame attributes back to the animations in the database with the given curve names
- L945 _public prototype_ `static void DatabaseAddCurvesFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> CurveNames, const TArrayView<const FAnimDatabaseFrameAttribute> FloatFrameAttributes, const TArrayView<const FLinearColor> Colors, const bool bSparseKeys = false, const bool bShouldTransact = false);`
- L951 _public prototype_ `static void DatabaseAddAnimNotify(UAnimDatabase* Database, const FName AnimNotifyTrackName, const TSubclassOf<UAnimNotify> Class, const FAnimDatabaseFrames& Frames, const FLinearColor Color = FLinearColor::Red, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Create AnimNotifies at the provided Frames in the database using the given track name and class
- L955 _public prototype_ `static void DatabaseAddAnimNotifies(UAnimDatabase* Database, const TArray<FName>& AnimNotifyTrackNames, const TArray<TSubclassOf<UAnimNotify>>& Classes, const TArray<FAnimDatabaseFrames>& Frames, const TArray<FLinearColor>& Colors, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, AutoCreateRefTerm = "Colors"))` — Create AnimNotifies at the provided Frames in the database using the given track names and classes
- L956 _public prototype_ `static void DatabaseAddAnimNotifiesFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> AnimNotifyTrackNames, const TArrayView<const TSubclassOf<UAnimNotify>> Classes, const TArrayView<const FAnimDatabaseFrames> Frames, const TArrayView<const FLinearColor> Colors, const bool bShouldTransact = false);`
- L960 _public prototype_ `static void DatabaseAddAnimNotifyObject(UAnimDatabase* Database, const FName& TrackName, UAnimNotify* AnimNotify, const FAnimDatabaseFrames& Frames, const FLinearColor Color = FLinearColor::Red, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Create AnimNotifies at the provided Frames from a duplicate of the given AnimNotify
- L964 _public prototype_ `static void DatabaseAddAnimNotifyObjects(UAnimDatabase* Database, const TArray<FName>& AnimNotifyTrackNames, const TArray<UAnimNotify*>& AnimNotifies, const TArray<FAnimDatabaseFrames>& Frames, const TArray<FLinearColor>& Colors, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, AutoCreateRefTerm="Colors"))` — Create AnimNotifies at the provided Frames in the database using the given track names and duplicates of the given AnimNotifies
- L965 _public prototype_ `static void DatabaseAddAnimNotifyObjectsFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> AnimNotifyTrackNames, const TArrayView<UAnimNotify* const> AnimNotifies, const TArrayView<const FAnimDatabaseFrames> Frames, const TArrayView<const FLinearColor> Colors, const bool bShouldTransact = false);`
- L969 _public prototype_ `static void DatabaseRemoveAnimNotifiesFromTrack(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName AnimNotifyTrackName, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Remove all the anim notifies on a given track
- L973 _public prototype_ `static void DatabaseRemoveAnimNotifiesFromTracks(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& AnimNotifyTrackNames, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Remove all the anim notifies from the given tracks
- L974 _public prototype_ `static void DatabaseRemoveAnimNotifiesFromTracksArrayView(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> AnimNotifyTrackNames, const bool bShouldTransact = false);`
- L980 _public prototype_ `static void DatabaseAddAnimNotifyState(UAnimDatabase* Database, const FName AnimNotifyStateTrackName, const TSubclassOf<UAnimNotifyState> Class, const FAnimDatabaseFrameRanges& FrameRanges, const FLinearColor Color = FLinearColor::Red, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Create AnimNotifyStates at the provided FrameRanges in the database using the given track name and class
- L984 _public prototype_ `static void DatabaseAddAnimNotifyStates(UAnimDatabase* Database, const TArray<FName>& AnimNotifyStateTrackNames, const TArray<TSubclassOf<UAnimNotifyState>>& Classes, const TArray<FAnimDatabaseFrameRanges>& FrameRanges, const TArray<FLinearColor>& Colors, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, AutoCreateRefTerm = "Colors"))` — Create AnimNotifyStates at the provided FrameRanges in the database using the given track names and classes
- L985 _public prototype_ `static void DatabaseAddAnimNotifyStatesFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> AnimNotifyStateTrackNames, const TArrayView<const TSubclassOf<UAnimNotifyState>> Classes, const TArrayView<const FAnimDatabaseFrameRanges> FrameRanges, const TArrayView<const FLinearColor> Colors, const bool bShouldTransact = false);`
- L989 _public prototype_ `static void DatabaseAddAnimNotifyStateObject(UAnimDatabase* Database, const FName TrackName, UAnimNotifyState* AnimNotifyState, const FAnimDatabaseFrameRanges& FrameRanges, const FLinearColor Color = FLinearColor::Red, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Create AnimNotifyStates at the provided FrameRanges from a duplicate of the given AnimNotifyState
- L993 _public prototype_ `static void DatabaseAddAnimNotifyStateObjects(UAnimDatabase* Database, const TArray<FName>& AnimNotifyStateTrackNames, const TArray<UAnimNotifyState*>& AnimNotifyStates, const TArray<FAnimDatabaseFrameRanges>& FrameRanges, const TArray<FLinearColor>& Colors, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, AutoCreateRefTerm = "Colors"))` — Create AnimNotifyStates at the provided FrameRanges in the database using the given track names and duplicates of the given AnimNotifyStates
- L994 _public prototype_ `static void DatabaseAddAnimNotifyStateObjectsFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> AnimNotifyStateTrackNames, const TArrayView<UAnimNotifyState* const> AnimNotifyStates, const TArrayView<const FAnimDatabaseFrameRanges> FrameRanges, const TArrayView<const FLinearColor> Colors, const bool bShouldTransact = false);`
- L1000 _public prototype_ `static void DatabaseAddSyncMarker(UAnimDatabase* Database, const FName SyncMarkerTrackName, const FName SyncMarkerName, const FAnimDatabaseFrames& Frames, const FLinearColor Color = FLinearColor::Red, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Create SyncMarkers at the provided Frames in the database using the given track name and sync marker name
- L1004 _public prototype_ `static void DatabaseAddSyncMarkers(UAnimDatabase* Database, const TArray<FName>& SyncMarkerTrackNames, const TArray<FName>& SyncMarkerNames, const TArray<FAnimDatabaseFrames>& Frames, const TArray<FLinearColor>& Colors, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly, AutoCreateRefTerm = "Colors"))` — Create SyncMarkers at the provided Frames in the database using the given track names and sync marker names
- L1005 _public prototype_ `static void DatabaseAddSyncMarkersFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> SyncMarkerTrackNames, const TArrayView<const FName> SyncMarkerNames, const TArrayView<const FAnimDatabaseFrames> Frames, const TArrayView<const FLinearColor> Colors, const bool bShouldTransact = false);`
- L1009 _public prototype_ `static void DatabaseRemoveSyncMarkerFromTrack(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName SyncMarkerTrackName, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Remove all the sync markers on a given track
- L1013 _public prototype_ `static void DatabaseRemoveSyncMarkerFromTracks(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& SyncMarkerTrackNames, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Remove all the sync markers from the given tracks
- L1014 _public prototype_ `static void DatabaseRemoveSyncMarkerFromTracksArrayView(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> SyncMarkerTrackNames, const bool bShouldTransact = false);`
- L1020 _public prototype_ `static void DatabaseSetLocalBoneTransform(UAnimDatabase* Database, const FName BoneName, const FAnimDatabaseFrameAttribute& TransformFrameAttribute, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Set the given bone's local transform in the database at the given transform frame attribute
- L1024 _public prototype_ `static void DatabaseSetLocalBoneTransforms(UAnimDatabase* Database, const TArray<FName>& BoneNames, const TArray<FAnimDatabaseFrameAttribute>& TransformFrameAttributes, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Set the given bones' local transforms in the database at the given transform frame attributes
- L1025 _public prototype_ `static void DatabaseSetLocalBoneTransformsFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> BoneNames, const TArrayView<const FAnimDatabaseFrameAttribute> TransformFrameAttributes, const bool bShouldTransact = false);`
- L1029 _public prototype_ `static void DatabaseSetGlobalBoneTransform(UAnimDatabase* Database, const FName BoneName, const FAnimDatabaseFrameAttribute& TransformFrameAttribute, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Set the given bone's global transform in the database at the given transform frame attribute
- L1033 _public prototype_ `static void DatabaseSetGlobalBoneTransforms(UAnimDatabase* Database, const TArray<FName>& BoneNames, const TArray<FAnimDatabaseFrameAttribute>& TransformFrameAttributes, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Set the given bones' global transforms in the database at the given transform frame attributes
- L1034 _public prototype_ `static void DatabaseSetGlobalBoneTransformsFromArrayViews(UAnimDatabase* Database, const TArrayView<const FName> BoneNames, const TArrayView<const FAnimDatabaseFrameAttribute> TransformFrameAttributes, const bool bShouldTransact = false);`
- L1038 _public prototype_ `static void DatabaseResetBoneTransform(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Set the given bone's local transforms in the database to the reference pose
- L1042 _public prototype_ `static void DatabaseResetBoneTransforms(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& BoneNames, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Set the given bones' local transforms in the database to the reference pose
- L1043 _public prototype_ `static void DatabaseResetBoneTransformsFromArrayViews(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> BoneNames, const bool bShouldTransact = false);`
- L1049 _public prototype_ `static void DatabaseStripUnusedBoneTracks(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Strips unused bone tracks from the data to reduce the file size on disk
- L1052 _public prototype_ `static void DatabaseModifyPoseData(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TFunctionRef<void(const UE::AnimDatabase::FPoseDataView& InOutPoseData)> Function, const bool bShouldTransact = false);` — Uses the provided function to modify the database pose data
- L1056 _public prototype_ `static void DatabaseMakeLooped(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float StartEndRatio, const float BlendInTime, const float BlendOutTime, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Makes the given ranges looped in the database
- L1060 _public prototype_ `static void DatabasePatchRanges(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const bool bApplyToRoot, const TArray<int32>& BoneIndices, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Patches the given ranges for the provided bones with a simple interpolation
- L1064 _public prototype_ `static void DatabaseSetToReferencePose(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const bool bApplyToRoot, const TArray<int32>& IgnoreBoneIndices, const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Sets the given ranges to the reference pose, with the exception of the provided IgnoreBoneIndices
- L1068 _public prototype_ `static void DatabaseRemoveFootGroundPenetration(UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName LeftToeBone, const FName RightToeBone, const float ToeBoneLength, const float PelvisHeightAdjustment = -1.0f, const FVector LeftKneeSideVector = FVector(0.0f, 0.0f, +1.0f), const FVector RightKneeSideVector = FVector(0.0f, 0.0f, +1.0f), const FVector LeftToeForwardVector = FVector(-1.0f, 0.0f, 0.0f), const FVector RightToeForwardVector = FVector(-1.0f, 0.0f, 0.0f), const bool bShouldTransact = false);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (DevelopmentOnly))` — Removes foot ground penetration in the database
- L1073 _private prototype_ `static void LoadAllBlueprintAssetsOfClass(UClass* Class);` — Loads into memory all the blueprint assets of a given class.

#### class `UAnimDatabaseFunction_StripUnusedBoneTracks`  
`class UAnimDatabaseFunction_StripUnusedBoneTracks : public UAnimDatabaseFunction`  
_L1078-1091_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Strip Unused Bone Tracks Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for stripping unused bone-tracks from the AnimSequence to reduce the file size on desk
- L1088 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ExportBVH`  
`class UAnimDatabaseFunction_ExportBVH : public UAnimDatabaseFunction`  
_L1095-1120_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Export to BVH Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for exporting the given ranges as BVH
- L1103 _public member_ `FDirectoryPath ExportDirectory;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (RelativePath))` — Directory to export BVH files to.
- L1107 _public member_ `bool bAddRootAxesChangeRotation = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to add the appropriate root rotation to account for the axes switch.
- L1111 _public member_ `EAnimDatabaseRotationOrder RotationOrder = EAnimDatabaseRotationOrder::XYZ;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Rotation order to use for conversion to euler angles.
- L1117 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ImportBVH`  
`class UAnimDatabaseFunction_ImportBVH : public UAnimDatabaseFunction`  
_L1124-1157_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Import from BVH Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for importing from BVH
- L1132 _public member_ `FDirectoryPath ImportDirectory;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (RelativePath))` — Directory to import BVH files from.
- L1136 _public member_ `FDirectoryPath AssetDirectory;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (RelativePath))` — Directory to write AnimSequences to.
- L1140 _public member_ `bool bRemoveRootAxesChangeRotation = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to remove the appropriate root rotation to account for the axes switch.
- L1144 _public member_ `bool bIgnoreMirrored = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Ignores BVH files with the _mirrored suffix
- L1148 _public member_ `bool bAddToDatabase = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to add the imported assets to the database.
- L1154 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ExportNotifies`  
`class UAnimDatabaseFunction_ExportNotifies : public UAnimDatabaseFunction`  
_L1161-1182_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Export Notifies Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for exporting all AnimNotifies and AnimNotifyStates from the given animations
- L1169 _public member_ `FDirectoryPath ExportDirectory;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (RelativePath))` — Directory to export the notifies to.
- L1173 _public member_ `FString FileName = TEXT("Not` — `UPROPERTY(EditAnywhere, Category = "Settings")` — File to export notifies as.
- L1179 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ImportNotifies`  
`class UAnimDatabaseFunction_ImportNotifies : public UAnimDatabaseFunction`  
_L1186-1203_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Import Notifies Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for importing AnimNotifies and AnimNotifyStates onto the given animations
- L1194 _public member_ `FFilePath ImportPath;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (RelativePath))` — File to import Notifies from.
- L1200 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_RemoveNotifies`  
`class UAnimDatabaseFunction_RemoveNotifies : public UAnimDatabaseFunction`  
_L1207-1218_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Remove Notifies Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for removing AnimNotifies and AnimNotifyStates from the given animations
- L1215 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_UpdateIKBones`  
`class UAnimDatabaseFunction_UpdateIKBones : public UAnimDatabaseFunction`  
_L1222-1271_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Update IK Bones Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for placing IK bones at the correct hand and foot locations
- L1231 _public member_ `FName RootBone = TEXT("roo` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1234 _public member_ `FName FootBoneL = TEXT("foo` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1237 _public member_ `FName FootBoneR = TEXT("foo` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1240 _public member_ `FName HandBoneL = TEXT("han` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1243 _public member_ `FName HandBoneR = TEXT("han` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1248 _public member_ `FName IKFootBoneL = TEXT("ik_` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1251 _public member_ `FName IKFootBoneR = TEXT("ik_` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1254 _public member_ `FName IKHandBoneGun = TEXT("ik_` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1257 _public member_ `FName IKHandBoneL = TEXT("ik_` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1260 _public member_ `FName IKHandBoneR = TEXT("ik_` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1268 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SetRootFromLookAt`  
`class UAnimDatabaseFunction_SetRootFromLookAt : public UAnimDatabaseFunction`  
_L1275-1354_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Set Root from Look-At Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for computing the root transform using the look-at direction
- L1285 _public member_ `FName RootBone = TEXT("roo` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Root bone name
- L1289 _public member_ `FName PelvisBone = TEXT("pel` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Pelvis bone name
- L1293 _public member_ `FName RootLocationBone = TEXT("pel` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Bone to project onto the floor to use as the root location
- L1297 _public member_ `FName RootDirectionBone = TEXT("hea` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Bone to use for the root facing direction
- L1301 _public member_ `FVector RootDirectionBoneDirection = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Local forward direction of the above bone to use as the facing direction
- L1305 _public member_ `FVector RootDirection = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Root bone forward vector
- L1311 _public member_ `bool bApplySmoothing = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to apply smoothing to the root
- L1315 _public member_ `bool bUseSavGolFilter = true;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bApplySmoothing", HideEditConditionToggle))` — If to use a SavGol filter for smoothing. A SavGol filter can work better when applying large amounts of smoothing
- L1319 _public member_ `float LocationSavGolFilterWidth = 1.5;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s", ClampMin = "1", UIMin = "1", EditCondition = "bApplySmoothing && bUseSavGolFilter", HideEditConditionToggle))` — Filter width for the location savgol filter. Larger values create smoother trajectories.
- L1323 _public member_ `int32 LocationSavGolPolynomialDegree = 3;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", ClampMax = "9", UIMin = "1", UIMax = "9", EditCondition = "bApplySmoothing && bUseSavGolFilter", HideEditConditionToggle))` — Degree of polynomial to use for the location savgol filter. Larger degrees allow for more bendy trajectories.
- L1327 _public member_ `float DirectionSavGolFilterWidth = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s", ClampMin = "1", UIMin = "1", EditCondition = "bApplySmoothing && bUseSavGolFilter", HideEditConditionToggle))` — Filter width for the direction savgol filter. Larger values create smoother trajectories.
- L1331 _public member_ `int32 DirectionSavGolPolynomialDegree = 3;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", ClampMax = "9", UIMin = "1", UIMax = "9", EditCondition = "bApplySmoothing && bUseSavGolFilter", HideEditConditionToggle))` — Degree of polynomial to use for the direction savgol filter. Larger degrees allow for more bendy trajectories.
- L1335 _public member_ `bool bUseGaussianWindowedSavGolFilter = true;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bApplySmoothing && bUseSavGolFilter", HideEditConditionToggle))` — If to use a gaussian window on the SavGol filter weights
- L1339 _public member_ `float LocationSmoothingTime = 0.15f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s", EditCondition = "bApplySmoothing && !bUseSavGolFilter", HideEditConditionToggle))` — Amount of smoothing to apply to the projected bone location
- L1343 _public member_ `float DirectionSmoothingTime = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s", EditCondition = "bApplySmoothing && !bUseSavGolFilter", HideEditConditionToggle))` — Amount of smoothing to apply to the facing direction
- L1351 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SetRootFromPelvis`  
`class UAnimDatabaseFunction_SetRootFromPelvis : public UAnimDatabaseFunction`  
_L1358-1391_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Set Root from Pelvis"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for computing the root transform using a fixed offset from the pelvis
- L1368 _public member_ `FName RootBone = TEXT("roo` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Root bone name
- L1372 _public member_ `FName PelvisBone = TEXT("pel` — `UPROPERTY(EditAnywhere, Category = "Bones")` — Pelvis bone name
- L1376 _public member_ `FTransform Offset = FTransform(FRotator(-90.0f, 0.0f, 0.0f), FVector(-100.0f, 0.0f, 0.0f), FVector::OneVector);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Fixed Offset to apply to the pelvis
- L1380 _public member_ `bool bApplyInLocalSpace = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to apply the offset in the local space of the pelvis or the world space
- L1388 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_BakeRootMotionIntoPelvis`  
`class UAnimDatabaseFunction_BakeRootMotionIntoPelvis : public UAnimDatabaseFunction`  
_L1395-1418_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bake Root Motion into Pelvis Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for baking root motion into the pelvis
- L1404 _public member_ `FName RootBone = TEXT("roo` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1407 _public member_ `FName PelvisBone = TEXT("pel` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1415 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_MakeRootStartAtOrigin`  
`class UAnimDatabaseFunction_MakeRootStartAtOrigin : public UAnimDatabaseFunction`  
_L1422-1442_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Make Root Start at Origin Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for making the root motion start at the origin for all the provided ranges
- L1431 _public member_ `FName RootBone = TEXT("roo` — `UPROPERTY(EditAnywhere, Category = "Bones")`
- L1439 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ExportToAnimSequences`  
`class UAnimDatabaseFunction_ExportToAnimSequences : public UAnimDatabaseFunction`  
_L1446-1472_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Export to Anim Sequences Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for exporting ranges to AnimSequences
- L1455 _public member_ `FDirectoryPath ExportDirectory;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1458 _public member_ `FString AssetNameFormatString = TEXT("{Se` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1461 _public member_ `bool bExportMirrored = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1469 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ExportRootMotion`  
`class UAnimDatabaseFunction_ExportRootMotion : public UAnimDatabaseFunction`  
_L1476-1501_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Export Root Motion Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for exporting root motion from the given animations
- L1486 _public member_ `FDirectoryPath ExportDirectory;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (RelativePath))` — Directory to export the root motion to.
- L1490 _public member_ `FString FileName = TEXT("Roo` — `UPROPERTY(EditAnywhere, Category = "Settings")` — File to export root motion as.
- L1498 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_MakeLooped`  
`class UAnimDatabaseFunction_MakeLooped : public UAnimDatabaseFunction`  
_L1505-1531_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Make Looped Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for making ranges looping
- L1514 _public member_ `float StartEndRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))`
- L1517 _public member_ `float BlendInTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s"))`
- L1520 _public member_ `float BlendOutTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s"))`
- L1528 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_PatchBones`  
`class UAnimDatabaseFunction_PatchBones : public UAnimDatabaseFunction`  
_L1535-1561_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Patch Bones Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for patching ranges
- L1544 _public member_ `bool bApplyToRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1547 _public member_ `bool bEntirePose = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1550 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bEntirePose", HideEditConditionToggle))`
- L1558 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SetToReferencePose`  
`class UAnimDatabaseFunction_SetToReferencePose : public UAnimDatabaseFunction`  
_L1565-1588_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Set to Reference Pose Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for setting to the reference pose
- L1574 _public member_ `bool bApplyToRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1577 _public member_ `TArray<FName> IgnoreBoneNames;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1585 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_BoneApplyTransform`  
`class UAnimDatabaseFunction_BoneApplyTransform : public UAnimDatabaseFunction`  
_L1592-1618_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Apply Transform Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for applying a transform to a bone
- L1601 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1604 _public member_ `EAnimDatabaseTransformMode Mode = EAnimDatabaseTransformMode::Replace;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1607 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1615 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_AddAnimNotifyState`  
`class UAnimDatabaseFunction_AddAnimNotifyState : public UAnimDatabaseFunction`  
_L1622-1648_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Add Anim Notify State Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for adding AnimNotifyStates from a reference object
- L1631 _public member_ `FName TrackName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1634 _public member_ `TObjectPtr<UAnimNotifyState> AnimNotifyState;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1637 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1645 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_Sequence`  
`class UAnimDatabaseFunction_Sequence : public UAnimDatabaseFunction`  
_L1652-1672_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Sequence Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function that can execute a sequence of sub-functions
- L1661 _public member_ `TArray<TObjectPtr<UAnimDatabaseFunction>> Functions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1669 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_AddAnimNotifyAtFrames`  
`class UAnimDatabaseFunction_AddAnimNotifyAtFrames : public UAnimDatabaseFunction`  
_L1676-1705_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Add Anim Notify at Frames Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for adding an AnimNotify from a frame function
- L1685 _public member_ `FName TrackName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1688 _public member_ `TObjectPtr<UAnimNotify> AnimNotify;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1691 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> Frames;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1694 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1702 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_AddAnimNotifyStateAtFrameRanges`  
`class UAnimDatabaseFunction_AddAnimNotifyStateAtFrameRanges : public UAnimDatabaseFunction`  
_L1709-1738_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Add Anim Notify State at Frame Ranges Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for adding an AnimNotifyState from a frame ranges function
- L1718 _public member_ `FName TrackName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1721 _public member_ `TObjectPtr<UAnimNotifyState> AnimNotifyState;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1724 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1727 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1735 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_AddCurveFromFrameAttribute`  
`class UAnimDatabaseFunction_AddCurveFromFrameAttribute : public UAnimDatabaseFunction`  
_L1742-1771_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Add Curve from Frame Attribute Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for adding a curve from a frame attribute function
- L1751 _public member_ `FName CurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1754 _public member_ `TObjectPtr<UAnimDatabaseFrameAttributeFunction> FrameAttribute;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1757 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1760 _public member_ `bool bSparseKeys = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1768 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ProcessContacts`  
`class UAnimDatabaseFunction_ProcessContacts : public UAnimDatabaseFunction`  
_L1775-1962_
- reflection: `UCLASS(BlueprintType, Blueprintable, DontCollapseCategories, meta = (DisplayName = "Process Contacts Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for processing contacts
- L1785 _public member_ `bool bAddFootSpeedCurves = false;` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves")` — If to add foot speed curves
- L1789 _public member_ `FName LeftFootSpeedCurveName = TEXT("foo` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves", meta = (EditCondition = "bAddFootSpeedCurves", HideEditConditionToggle))` — Name of the foot speed curve for the left foot
- L1793 _public member_ `FName RightFootSpeedCurveName = TEXT("foo` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves", meta = (EditCondition = "bAddFootSpeedCurves", HideEditConditionToggle))` — Name of the foot speed curve for the right foot
- L1797 _public member_ `FName LeftFootSpeedBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves", meta = (EditCondition = "bAddFootSpeedCurves", HideEditConditionToggle))` — Name of the left bone to generate the foot speed curve for
- L1801 _public member_ `FName RightFootSpeedBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves", meta = (EditCondition = "bAddFootSpeedCurves", HideEditConditionToggle))` — Name of the right bone to generate the foot speed curve for
- L1805 _public member_ `FLinearColor LeftFootSpeedCurveColor = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves", meta = (EditCondition = "bAddFootSpeedCurves", HideEditConditionToggle))` — Color of the left foot speed curve
- L1809 _public member_ `FLinearColor RightFootSpeedCurveColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Foot Speed Curves", meta = (EditCondition = "bAddFootSpeedCurves", HideEditConditionToggle))` — Color of the right foot speed curve
- L1815 _public member_ `bool bAddContactCurves = false;` — `UPROPERTY(EditAnywhere, Category = "Contact Curves")` — If to add contact curves
- L1819 _public member_ `FName LeftContactCurveName = TEXT("con` — `UPROPERTY(EditAnywhere, Category = "Contact Curves", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — Name of the contact curve for the left foot
- L1823 _public member_ `FName RightContactCurveName = TEXT("con` — `UPROPERTY(EditAnywhere, Category = "Contact Curves", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — Name of the contact curve for the right foot
- L1827 _public member_ `FName LeftContactBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Contact Curves", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — Name of the left bone to generate the contact curve for
- L1831 _public member_ `FName RightContactBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Contact Curves", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — Name of the right bone to generate the contact curve for
- L1835 _public member_ `FLinearColor LeftContactCurveColor = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Contact Curves", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — Color of the left contact curve
- L1839 _public member_ `FLinearColor RightContactCurveColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Contact Curves", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — Color of the right contact curve
- L1845 _public member_ `bool bAddAnimNotifies = false;` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies")` — If to add anim notifies
- L1849 _public member_ `bool bClearAnimNotifyTracks = true;` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — Clears all Anim Notifies on the given tracks before adding new ones
- L1853 _public member_ `FName LeftContactAnimNotifyTrackName = TEXT("Foo` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — The track name for the left anim notifies
- L1857 _public member_ `FName RightContactAnimNotifyTrackName = TEXT("Foo` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — The track name for the right anim notifies
- L1861 _public member_ `TObjectPtr<UAnimNotify> LeftContactAnimNotify;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — The object to use for the left contact anim notify
- L1865 _public member_ `TObjectPtr<UAnimNotify> RightContactAnimNotify;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — The object to use for the right contact anim notify
- L1869 _public member_ `FLinearColor LeftContactAnimNotifyColor = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — Color of the left anim notify track
- L1873 _public member_ `FLinearColor RightContactAnimNotifyColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle))` — Color of the right anim notify track
- L1877 _public member_ `float AnimNotifyOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Anim Notifies", meta = (EditCondition = "bAddAnimNotifies", HideEditConditionToggle, ForceUnits = "s"))` — The amount of time before the contact (in seconds) to place the location of the Anim Notifies
- L1883 _public member_ `bool bAddSyncMarkers = false;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers")` — If to add sync markers
- L1887 _public member_ `bool bClearSyncMarkerTracks = true;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — Clears all Sync Markers on the given tracks before adding new ones
- L1891 _public member_ `FName LeftContactSyncMarkerTrackName = TEXT("Foo` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — The track name for the left sync markers
- L1895 _public member_ `FName RightContactSyncMarkerTrackName = TEXT("Foo` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — The track name for the right sync markers
- L1899 _public member_ `FName LeftContactSyncMarker = TEXT("L")` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — The name of the left sync marker
- L1903 _public member_ `FName RightContactSyncMarker = TEXT("R")` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — The name of the right sync marker
- L1907 _public member_ `FLinearColor LeftContactSyncMarkerColor = FLinearColor(0.5f, 0.0, 0.5f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — Color of the left sync marker track
- L1911 _public member_ `FLinearColor RightContactSyncMarkerColor = FLinearColor(0.5f, 0.0, 0.5f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle))` — Color of the right sync marker track
- L1915 _public member_ `float SyncMarkerOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta = (EditCondition = "bAddSyncMarkers", HideEditConditionToggle, ForceUnits = "s"))` — The amount of time before the contact (in seconds) to place the location of the sync markers
- L1921 _public member_ `float HeightThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Filtering", meta = (EditCondition = "bAddContactCurves || bAddAnimNotifies || bAddSyncMarkers", HideEditConditionToggle, ForceUnits = "cm"))` — Maximum height for which the bone can be considered in contact
- L1925 _public member_ `float VelocityThreshold = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Filtering", meta = (EditCondition = "bAddContactCurves || bAddAnimNotifies || bAddSyncMarkers", HideEditConditionToggle, ForceUnits = "cm/s"))` — Maximum velocity for which the bone can be considered in contact
- L1929 _public member_ `bool bFilterContactCurves = true;` — `UPROPERTY(EditAnywhere, Category = "Filtering", meta = (EditCondition = "bAddContactCurves || bAddAnimNotifies || bAddSyncMarkers", HideEditConditionToggle))` — If to filter the contact curves
- L1933 _public member_ `float ContactFilterTime = 0.025f;` — `UPROPERTY(EditAnywhere, Category = "Filtering", meta = (EditCondition = "(bAddContactCurves || bAddAnimNotifies || bAddSyncMarkers) && bFilterContactCurves", HideEditConditionToggle, ForceUnits = "s", UIMin="0.0", ClampMin="0.0"))` — Roughly corresponds to the minimum contact duration (in seconds) that will be allowed. Reduce if very brief contacts are being missed. Increase if you are getting lots of very short contacts or lifts.
- L1937 _public member_ `bool bRemoveFirstFrameContactEvent = true;` — `UPROPERTY(EditAnywhere, Category = "Filtering", meta = (EditCondition = "bAddAnimNotifies || bAddSyncMarkers", HideEditConditionToggle))` — If there is a contact event on the first frame then it is removed
- L1943 _public member_ `bool bSmoothContactCurves = true;` — `UPROPERTY(EditAnywhere, Category = "Smoothing", meta = (EditCondition = "bAddContactCurves", HideEditConditionToggle))` — If to smooth the contact curves
- L1947 _public member_ `float SmoothingAmount = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Smoothing", meta = (EditCondition = "bAddContactCurves && bSmoothContactCurves", HideEditConditionToggle))` — Amount of smoothing to apply to the resulting contact curve (in frames)
- L1951 _public member_ `bool bSparseKeys = true;` — `UPROPERTY(EditAnywhere, Category = "Smoothing", meta = (EditCondition = "bAddFootSpeedCurves || bAddContactCurves", HideEditConditionToggle))` — If to write curves using sparse keys
- L1959 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ProcessPhaseCurves`  
`class UAnimDatabaseFunction_ProcessPhaseCurves : public UAnimDatabaseFunction`  
_L1967-2054_
- reflection: `UCLASS(BlueprintType, Blueprintable, DontCollapseCategories, meta = (DisplayName = "Process Phase Curves Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for generating phase curves from another source
- L1977 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> ZeroPhaseFrames;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — The frames used to label a phase time of zero
- L1981 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> HalfPhaseFrames;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — The frames used to label that half the phase time has elapsed
- L1985 _public member_ `EAnimDatabasePhaseExtrapolationMode ExtrapolationMode = EAnimDatabasePhaseExtrapolationMode::Extrapolate;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Phase extrapolation mode for the ends of the animation
- L1989 _public member_ `bool bSparseKeys = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to write curves using sparse keys
- L1995 _public member_ `bool bAddPhaseAngle = false;` — `UPROPERTY(EditAnywhere, Category = "Phase Angle")` — If to add the phase angle as a curve
- L1999 _public member_ `FName PhaseAngleCurveName = TEXT("pha` — `UPROPERTY(EditAnywhere, Category = "Phase Angle", meta = (EditCondition = "bAddPhaseAngle", HideEditConditionToggle))` — Name of the angular phase curve
- L2003 _public member_ `FLinearColor PhaseAngleCurveColor = FLinearColor(0.5f, 0.25, 0.5f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Phase Angle", meta = (EditCondition = "bAddPhaseAngle", HideEditConditionToggle))` — Color of the angular phase curve
- L2007 _public member_ `bool bRescalePhaseAngle = false;` — `UPROPERTY(EditAnywhere, Category = "Phase Angle", meta = (EditCondition = "bAddPhaseAngle", HideEditConditionToggle))` — If to re-scale the phase angle to be between 0 and 1
- L2013 _public member_ `bool bAddPhaseDirection = false;` — `UPROPERTY(EditAnywhere, Category = "Phase Direction")` — If to add two phase direction as two curves
- L2017 _public member_ `FName PhaseDirectionXCurveName = TEXT("pha` — `UPROPERTY(EditAnywhere, Category = "Phase Direction", meta = (EditCondition = "bAddPhaseDirection", HideEditConditionToggle))` — Name of the x phase curve
- L2021 _public member_ `FName PhaseDirectionYCurveName = TEXT("pha` — `UPROPERTY(EditAnywhere, Category = "Phase Direction", meta = (EditCondition = "bAddPhaseDirection", HideEditConditionToggle))` — Name of the y phase curve
- L2025 _public member_ `FLinearColor PhaseDirectionXCurveColor = FLinearColor(0.5f, 0.5f, 0.25, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Phase Direction", meta = (EditCondition = "bAddPhaseDirection", HideEditConditionToggle))` — Color of the x phase curve
- L2029 _public member_ `FLinearColor PhaseDirectionYCurveColor = FLinearColor(0.5f, 0.5f, 0.75, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Phase Direction", meta = (EditCondition = "bAddPhaseDirection", HideEditConditionToggle))` — Color of the y phase curve
- L2035 _public member_ `bool bAddPhaseRamp = false;` — `UPROPERTY(EditAnywhere, Category = "Phase Ramp")` — If to add the phase angle as a ramp that goes up and down between -1 and 1
- L2039 _public member_ `FName PhaseRampCurveName = TEXT("pha` — `UPROPERTY(EditAnywhere, Category = "Phase Ramp", meta = (EditCondition = "bAddPhaseRamp", HideEditConditionToggle))` — Name of the phase ramp curve
- L2043 _public member_ `FLinearColor PhaseRampCurveColor = FLinearColor(0.5f, 0.75, 0.5f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Phase Ramp", meta = (EditCondition = "bAddPhaseRamp", HideEditConditionToggle))` — Color of the phase ramp curve
- L2051 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SetBoneLocalTransformFromFrameAttribute`  
`class UAnimDatabaseFunction_SetBoneLocalTransformFromFrameAttribute : public UAnimDatabaseFunction`  
_L2059-2082_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Set Bone Local Transform from Frame Attribute Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for setting a bone local transform from frame attribute function
- L2068 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L2071 _public member_ `TObjectPtr<UAnimDatabaseFrameAttributeFunction> FrameAttribute;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L2079 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SetBoneGlobalTransformFromFrameAttribute`  
`class UAnimDatabaseFunction_SetBoneGlobalTransformFromFrameAttribute : public UAnimDatabaseFunction`  
_L2086-2109_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Set Bone Global Transform from Frame Attribute Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function for setting a bone global transform from frame attribute function
- L2095 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L2098 _public member_ `TObjectPtr<UAnimDatabaseFrameAttributeFunction> FrameAttribute;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L2106 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### enum `EAnimDatabaseBoneSpace`  
`enum class EAnimDatabaseBoneSpace : uint8`  
_L2112-2118_
- reflection: `UENUM(BlueprintType)`
- L2115 _public enumerator_ `Local` — Local (parent) space
- L2117 _public enumerator_ `Global` — Global (world) space

#### class `UAnimDatabaseFunction_CopyBones`  
`class UAnimDatabaseFunction_CopyBones : public UAnimDatabaseFunction`  
_L2122-2147_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Copy Bones Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Copy bone transforms from certain bones to others
- L2132 _public member_ `TMap<FName, FName> BoneMap;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Bone Mapping
- L2136 _public member_ `EAnimDatabaseBoneSpace Space = EAnimDatabaseBoneSpace::Global;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Space to perform copying in
- L2144 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_ResetBones`  
`class UAnimDatabaseFunction_ResetBones : public UAnimDatabaseFunction`  
_L2151-2171_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Reset Bones Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Reset bone transforms to the reference pose
- L2160 _public member_ `TArray<FName> Bones;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L2168 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SetBoneToRootTransformAtFrames`  
`class UAnimDatabaseFunction_SetBoneToRootTransformAtFrames : public UAnimDatabaseFunction`  
_L2175-2198_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Set Bone to Root Transform at Frames Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function to set bone to root location at frame
- L2184 _public member_ `FName BoneName = TEXT("att` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L2187 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> Frames;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L2195 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_AdjustNeckRotation`  
`class UAnimDatabaseFunction_AdjustNeckRotation : public UAnimDatabaseFunction`  
_L2202-2247_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Adjust Neck Rotation Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function to adjust neck rotation to remove potential artifacts after retargeting
- L2212 _public member_ `FName Neck0Bone = TEXT("nec` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the neck0 bone
- L2216 _public member_ `FName Neck1Bone = TEXT("nec` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the neck1 bone
- L2220 _public member_ `FName HeadBone = TEXT("hea` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the head bone
- L2224 _public member_ `float Neck0Rotation = -18.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "deg"))` — Rotation to apply to the neck0 bone
- L2228 _public member_ `float Neck1Rotation = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "deg"))` — Rotation to apply to the neck1 bone
- L2232 _public member_ `float HeadRotation = 18.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "deg"))` — Rotation to apply to the head bone
- L2236 _public member_ `FVector LocalAxis = FVector(0.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local axis to apply rotation on
- L2244 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_RemoveFootGroundPenetration`  
`class UAnimDatabaseFunction_RemoveFootGroundPenetration : public UAnimDatabaseFunction`  
_L2251-2300_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Remove Foot Ground Penetration Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Function to remove foot ground penetration
- L2261 _public member_ `FName LeftToeBone = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left toe bone
- L2265 _public member_ `FName RightToeBone = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right toe bone
- L2269 _public member_ `float ToeBoneLength = 7.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(ForceUnits="cm"))` — Length of the toe joint
- L2273 _public member_ `FVector LeftKneeSideVector = FVector(0.0f, 0.0f, +1.0f);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Side Vector of the Left Knee
- L2277 _public member_ `FVector RightKneeSideVector = FVector(0.0f, 0.0f, +1.0f);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Side Vector of the Right Knee
- L2281 _public member_ `FVector LeftToeForwardVector = FVector(-1.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Forward Vector of the Left Toe
- L2285 _public member_ `FVector RightToeForwardVector = FVector(-1.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Forward Vector of the Right Toe
- L2289 _public member_ `float PelvisHeightAdjustment = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Adjustment to apply to the pelvis height
- L2297 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_Statistics`  
`class UAnimDatabaseFunction_Statistics : public UAnimDatabaseFunction`  
_L2304-2325_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Statistics Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Computes various statistics about the provided ranges
- L2314 _public member_ `FAnimDatabaseFrameRangesStatistics Statistics;` — `UPROPERTY(VisibleAnywhere, Category = "Settings")` — Statistics for the given ranges
- L2322 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_SpeedStatistics`  
`class UAnimDatabaseFunction_SpeedStatistics : public UAnimDatabaseFunction`  
_L2329-2376_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Speed Statistics Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Computes various stats about root speeds for the provide frame ranges
- L2339 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame ranges over which to compute the statistics
- L2345 _public member_ `float AverageLinearVelocity = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "cm/s"))` — Average linear velocity across the frame ranges
- L2349 _public member_ `float MinimumLinearVelocity = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "cm/s"))` — Smallest linear velocity across the frame ranges
- L2353 _public member_ `float MaximumLinearVelocity = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "cm/s"))` — Largest linear velocity across the frame ranges
- L2357 _public member_ `float AverageAngularVelocity = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "deg/s"))` — Average angular velocity across the frame ranges
- L2361 _public member_ `float MinimumAngularVelocity = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "deg/s"))` — Smallest angular velocity across the frame ranges
- L2365 _public member_ `float MaximumAngularVelocity = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "deg/s"))` — Largest angular velocity across the frame ranges
- L2373 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseFunction_TransitionStatistics`  
`class UAnimDatabaseFunction_TransitionStatistics : public UAnimDatabaseFunction`  
_L2380-2439_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Transition Statistics Function"))`
- inherits: `UAnimDatabaseFunction`
- desc: Computes various statistics regarding transitions given by the provided FrameRanges
- L2390 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame ranges over which to compute the statistics
- L2396 _public member_ `float AverageTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "s"))` — Average duration of the given frame ranges
- L2400 _public member_ `float MinimumTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "s"))` — Shortest duration of the given frame ranges
- L2404 _public member_ `float MaximumTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "s"))` — Longest duration of the given frame ranges
- L2408 _public member_ `float AverageDistance = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Average distance traveled during the given frame ranges
- L2412 _public member_ `float MinimumDistance = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Minimum distance traveled during the given frame ranges
- L2416 _public member_ `float MaximumDistance = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Maximum distance traveled during the given frame ranges
- L2420 _public member_ `float AverageAngle = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "deg"))` — Average angle traveled during the given frame ranges
- L2424 _public member_ `float MinimumAngle = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "deg"))` — Minimum angle traveled during the given frame ranges
- L2428 _public member_ `float MaximumAngle = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (ForceUnits = "deg"))` — Maximum angle traveled during the given frame ranges
- L2436 _public prototype_ `virtual void Run_Implementation(UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const bool bShouldTransact) override;`

#### class `UAnimDatabaseDebugDraw`  
`class UAnimDatabaseDebugDraw : public UObject`  
_L2447-2478_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Class that can be implemented to perform custom debug draw functionality
- L2457 _public prototype_ `void InitializeDrawDebug(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimDatabase", meta = (ForceAsFunction))` — Make any required frame attributes or other data. This function is called once when the class is initialized
- L2463 _public prototype_ `void DrawDebug( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimDatabase", meta = (ForceAsFunction))` — Draw Debug function which is called each frame with the current pose state, database, and attribute information

#### class `UAnimDatabaseDebugDraw_Attributes`  
`class UAnimDatabaseDebugDraw_Attributes : public UAnimDatabaseDebugDraw`  
_L2482-2519_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Attributes"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for drawing attributes
- L2492 _public member_ `float VerticalSpacing = 16.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Spacing for text lines vertically
- L2496 _public member_ `float PropertyHorizontalOffset = 250.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Pixel offset to display the properties
- L2504 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_ContactCurves`  
`class UAnimDatabaseDebugDraw_ContactCurves : public UAnimDatabaseDebugDraw`  
_L2523-2582_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Contact Curves Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for drawing contact curves
- L2533 _public member_ `FName LeftToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left toe bone
- L2537 _public member_ `FName RightToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right toe bone
- L2541 _public member_ `FName LeftContactCurveName = TEXT("con` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left contact curve
- L2545 _public member_ `FName RightContactCurveName = TEXT("con` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right contact curve
- L2549 _public member_ `float ContactCircleRadius = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Radius for the circle to display to show contacts
- L2554 _protected member_ `FAnimDatabaseFrameAttribute LeftContactCurve;` — Left contact curve attribute
- L2557 _protected member_ `FAnimDatabaseFrameAttribute RightContactCurve;` — Right contact curve attribute
- L2565 _public prototype_ `virtual void InitializeDrawDebug_Implementation(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`
- L2567 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_ContactThresholds`  
`class UAnimDatabaseDebugDraw_ContactThresholds : public UAnimDatabaseDebugDraw`  
_L2587-2679_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Contact Thresholds Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for working out correct contact thresholds
- L2597 _public member_ `FName LeftToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left toe bone
- L2601 _public member_ `FName RightToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right toe bone
- L2605 _public member_ `float VelocityThreshold = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm/s"))` — Velocity Threshold for contacts
- L2609 _public member_ `float HeightThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Height Threshold for contacts
- L2613 _public member_ `float ContactCircleRadius = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Radius for the circle to display to show contacts
- L2617 _public member_ `float ContactCircleThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Thickness of the circle to display to show contacts
- L2621 _public member_ `float VelocityLineScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Scale of the line drawn to show the velocity
- L2625 _public member_ `float VelocityLineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Thickness of the line drawn to show the velocity
- L2629 _public member_ `float GraphHeight = 150.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — Graph Scale in Pixels
- L2633 _public member_ `float GraphWidth = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — Graph Scale in Pixels
- L2637 _public member_ `int32 GraphFrameNum = 60;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", UIMin = "1"))` — Number of frames to plot in the graphs
- L2641 _public member_ `float GraphMaxVelocity = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm/s"))` — Maximum Velocity to display on graph
- L2645 _public member_ `float GraphMaxHeight = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Maximum Height to display on graph
- L2649 _protected member_ `FAnimDatabaseFrameAttribute LeftContactVelocity, LeftContactHeight;`
- L2649 _protected member_ `FAnimDatabaseFrameAttribute LeftContactVelocity, LeftContactHeight;`
- L2650 _protected member_ `FAnimDatabaseFrameAttribute RightContactVelocity, RightContactHeight;`
- L2650 _protected member_ `FAnimDatabaseFrameAttribute RightContactVelocity, RightContactHeight;`
- L2652 _protected member_ `TArray<float> TimeValues;`
- L2653 _protected member_ `TArray<float> LeftVelocityValues, LeftHeightValues;`
- L2653 _protected member_ `TArray<float> LeftVelocityValues, LeftHeightValues;`
- L2654 _protected member_ `TArray<float> RightVelocityValues, RightHeightValues;`
- L2654 _protected member_ `TArray<float> RightVelocityValues, RightHeightValues;`
- L2662 _public prototype_ `virtual void InitializeDrawDebug_Implementation(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`
- L2664 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_Multi`  
`class UAnimDatabaseDebugDraw_Multi : public UAnimDatabaseDebugDraw`  
_L2684-2719_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Multi Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for multiple other debug drawers
- L2694 _public member_ `TArray<TObjectPtr<UAnimDatabaseDebugDraw>> Drawers;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Widget Radius
- L2702 _public prototype_ `virtual void InitializeDrawDebug_Implementation(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`
- L2704 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_RootOrientation`  
`class UAnimDatabaseDebugDraw_RootOrientation : public UAnimDatabaseDebugDraw`  
_L2723-2764_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Root Orientation Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for drawing root orientation
- L2733 _public member_ `float FloorOffset = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Vertical Offset from Floor
- L2737 _public member_ `float Radius = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Widget Radius
- L2741 _public member_ `FVector ForwardVector = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local root forward direction
- L2749 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_MovementDirection`  
`class UAnimDatabaseDebugDraw_MovementDirection : public UAnimDatabaseDebugDraw`  
_L2768-2821_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Movement Direction Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for drawing the current movement direction
- L2778 _public member_ `float FloorOffset = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Vertical Offset from Floor
- L2782 _public member_ `FVector Direction = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local root forward direction
- L2786 _public member_ `float VelocityThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Character is only considered moving when the velocity is above this threshold
- L2790 _public member_ `float DirectionArrowLength = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Direction Arrow Length
- L2794 _public member_ `float VelocityScale = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Velocity Scale
- L2798 _public member_ `float Thickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Widget Thickness
- L2806 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_BoneTransform`  
`class UAnimDatabaseDebugDraw_BoneTransform : public UAnimDatabaseDebugDraw`  
_L2825-2870_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Transform Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw the transform of the given bone
- L2835 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Bone name to draw widget for
- L2839 _public member_ `float Radius = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Widget Radius
- L2843 _public member_ `float Thickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Widget Thickness
- L2847 _public member_ `bool bDepthTest = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to depth test while drawing
- L2855 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_BoneAttachment`  
`class UAnimDatabaseDebugDraw_BoneAttachment : public UAnimDatabaseDebugDraw`  
_L2875-2936_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Attachment Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw a bone attachment such as a prop
- L2885 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Bone attached to
- L2889 _public member_ `FTransform RelativeTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Relative transform of the attachment to the bone
- L2893 _public member_ `bool bDrawTransform = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to draw the attachment transform
- L2897 _public member_ `float TransformRadius = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Transform Radius
- L2901 _public member_ `float TransformThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Transform Thickness
- L2905 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Static mesh to use for attachment (will draw bounding box only)
- L2909 _public member_ `float BoundingBoxThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Bounding box Thickness
- L2913 _public member_ `bool bDepthTest = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to depth test while drawing
- L2921 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_RootVelocity`  
`class UAnimDatabaseDebugDraw_RootVelocity : public UAnimDatabaseDebugDraw`  
_L2940-2987_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Root Velocity Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for drawing root velocities
- L2950 _public member_ `float MaxLinearVelocity = 500.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm/s"))` — Graph axes maximum for linear velocity
- L2954 _public member_ `float MaxAngularVelocity = 180.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "deg/s"))` — Graph axes maximum for angular velocity
- L2959 _protected member_ `FAnimDatabaseFrameAttribute RootLinearVelocity;` — Root Linear Velocity attribute
- L2962 _protected member_ `FAnimDatabaseFrameAttribute RootAngularVelocity;` — Root Angular Velocity attribute
- L2970 _public prototype_ `virtual void InitializeDrawDebug_Implementation(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`
- L2972 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### class `UAnimDatabaseDebugDraw_ChairOnAttach`  
`class UAnimDatabaseDebugDraw_ChairOnAttach : public UAnimDatabaseDebugDraw`  
_L2992-3036_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Chair on Attach Debug Draw"))`
- inherits: `UAnimDatabaseDebugDraw`
- desc: Debug Draw class for drawing a chair at the attach bone
- L3002 _public member_ `FName AttachBoneName = TEXT("att` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the attach bone
- L3006 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> AttachRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Ranges where the attach bone is valid
- L3011 _protected member_ `FAnimDatabaseFrameRanges ValidAttachRanges;` — Valid ranges for attachment
- L3019 _public prototype_ `virtual void InitializeDrawDebug_Implementation(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`
- L3021 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) override;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API ANIMDATABASE_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L60 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimDatabase, Log, All);`
- L272 _namespace_ `namespace UE`
- L272 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L272 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)
- L460 _delegate_ `DECLARE_MULTICAST_DELEGATE(FAnimDatabaseOnSkeletonChanged);`
- L460 _prototype_ `DECLARE_MULTICAST_DELEGATE(FAnimDatabaseOnSkeletonChanged);`

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Public/AnimDatabaseFrameAttribute.h` (Public)


#### enum `EAnimDatabaseAttributeType`  
`enum class EAnimDatabaseAttributeType : uint8`  
_L27-42_
- reflection: `UENUM(BlueprintType)`
- desc: The type of an attribute
- L29 _public enumerator_ `Null = 0`
- L30 _public enumerator_ `Bool = 1`
- L31 _public enumerator_ `Float = 2`
- L32 _public enumerator_ `Location = 3`
- L33 _public enumerator_ `Rotation = 4`
- L34 _public enumerator_ `Scale = 5`
- L35 _public enumerator_ `LinearVelocity = 6`
- L36 _public enumerator_ `AngularVelocity = 7`
- L37 _public enumerator_ `ScalarVelocity = 8`
- L38 _public enumerator_ `Direction = 9`
- L39 _public enumerator_ `Transform = 10`
- L40 _public enumerator_ `Event = 11`
- L41 _public enumerator_ `Angle = 12`

#### enum `EAnimDatabasePhaseExtrapolationMode`  
`enum class EAnimDatabasePhaseExtrapolationMode : uint8`  
_L46-53_
- reflection: `UENUM(BlueprintType)`
- desc: Mode for handling edges in phase extraction
- L49 _public enumerator_ `Repeat = 0` — Repeats the phase value at the start and end frames
- L52 _public enumerator_ `Extrapolate = 1` — Extrapolates the phase value using the nearest pair of frames

#### struct `FAnimDatabaseFrameAttribute`  
`struct FAnimDatabaseFrameAttribute`  
_L66-136_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a property associated with a set of frame ranges within a UAnimDatabase. Internally, this is effectively a thin blueprint wrapper around the UE::Learning::FFrameAttribute data structure plus an additional type tag which allows for dynamic type checking in the blueprint interface. Below we provide a Blueprint Function Library that allows for the construction, modification and scripting of these objects in blueprints, but if you want to handle them in C++ at a low level if you can also access the internal FrameAttribute object directly. It is assumed that all FrameAttribute objects used by this wrapper are stored at the FrameRate of the database they were created from.
- L73 _public prototype_ `bool IsValid() const;` — Checks if the given FrameAttribute is valid (i.e. the shared pointer is not null)
- L76 _public prototype_ `bool GetAsBool(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a Bool. Assumes the Attribute Type is correct.
- L79 _public prototype_ `float GetAsFloat(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a float. Assumes the Attribute Type is correct.
- L82 _public prototype_ `void GetAsEvent(bool& bOutTimeUntilEventKnown, float& OutTimeUntilEvent, const int32 FrameIdx) const;` — Returns the attribute data at the given frame as an event. Assumes the Attribute Type is correct.
- L85 _public prototype_ `FVector3f GetAsLocation(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a location. Assumes the Attribute Type is correct.
- L88 _public prototype_ `FVector3f GetAsScale(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a scale. Assumes the Attribute Type is correct.
- L91 _public prototype_ `FVector3f GetAsVelocity(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a velocity. Assumes the Attribute Type is correct.
- L94 _public prototype_ `FVector3f GetAsDirection(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a direction. Assumes the Attribute Type is correct.
- L97 _public prototype_ `FQuat4f GetAsRotation(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a rotation. Assumes the Attribute Type is correct.
- L100 _public prototype_ `FTransform3f GetAsTransform(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a transform. Assumes the Attribute Type is correct.
- L103 _public prototype_ `FVector GetAsLocationDouble(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a double-precision location. Assumes the Attribute Type is correct.
- L106 _public prototype_ `FVector GetAsScaleDouble(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a double-precision scale. Assumes the Attribute Type is correct.
- L109 _public prototype_ `FVector GetAsVelocityDouble(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a double-precision velocity. Assumes the Attribute Type is correct.
- L112 _public prototype_ `FVector GetAsDirectionDouble(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a double-precision direction. Assumes the Attribute Type is correct.
- L115 _public prototype_ `FQuat GetAsRotationDouble(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a double-precision rotation. Assumes the Attribute Type is correct.
- L118 _public prototype_ `FTransform GetAsTransformDouble(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as a double-precision transform. Assumes the Attribute Type is correct.
- L121 _public prototype_ `float GetAsAngleDegrees(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as an angle in degrees. Assumes the Attribute Type is correct.
- L124 _public prototype_ `float GetAsAngleRadians(const int32 FrameIdx) const;` — Returns the attribute data at the given frame as an angle in radians. Assumes the Attribute Type is correct.
- L127 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L132 _public member_ `EAnimDatabaseAttributeType Type = EAnimDatabaseAttributeType::Null;` — The type of this Frame Attribute
- L135 _public member_ `TSharedPtr<UE::Learning::FFrameAttribute, ESPMode::ThreadSafe> FrameAttribute;` — Shared pointer to the actual FrameAttribute data structure

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimDatabaseFrameAttribute> : TStructOpsTypeTraitsBase2<FAnimDatabaseFrameAttribute>`  
_L141-148_
- inherits: `TStructOpsTypeTraitsBase2<FAnimDatabaseFrameAttribute>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L144-147_

#### class `UAnimDatabaseFrameAttributeLibrary`  
`class UAnimDatabaseFrameAttributeLibrary : public UBlueprintFunctionLibrary`  
_L152-2058_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- L160 _public prototype_ `static int32 AttributeTypeSize(const EAnimDatabaseAttributeType Type);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the size (number of channels in the FrameAttribute) for a given type
- L164 _public prototype_ `static FString AttributeTypeName(const EAnimDatabaseAttributeType Type);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the name for a given type
- L165 _public prototype_ `static const TCHAR* AttributeTypeNameInternal(const EAnimDatabaseAttributeType Type);`
- L169 _public prototype_ `static FAnimDatabaseFrameRanges FrameAttributeFrameRanges(const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (BlueprintAutocast, CompactNodeTitle = "->"))` — Gets the Frame Ranges associated with a given Frame Attribute
- L173 _public prototype_ `static void FrameAttributeAnimSequences(TArray<UAnimSequence*>& OutAnimSequences, const UAnimDatabase* Database, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Gets the Frame Ranges associated with a given Frame Attribute
- L179 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEmptyFrameAttribute();` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Make an empty Frame Attribute
- L183 _public prototype_ `static FAnimDatabaseFrameAttribute MakeNullFrameAttribute(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Make a null Frame Attribute for the given ranges
- L187 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFrameAttributeFromFunction(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const UAnimDatabaseFrameAttributeFunction* Function);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a Frame Attribute using the given UAnimDatabaseFrameAttributeFunction
- L191 _public prototype_ `static void MakeFrameAttributesFromFunctions( TArray<FAnimDatabaseFrameAttribute>& OutFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<UAnimDatabaseFrameAttributeFunction*>& Functions);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes Frame Attributes using the given UAnimDatabaseFrameAttributeFunctions
- L197 _public prototype_ `static void MakeFrameAttributesFromFunctionsArrayView( const TArrayView<FAnimDatabaseFrameAttribute> OutFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<UAnimDatabaseFrameAttributeFunction* const> Functions);`
- L206 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFrameAttributeFromClass(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimDatabaseFrameAttributeFunction> Class);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a Frame Attribute using the given UAnimDatabaseFrameAttributeFunction
- L210 _public prototype_ `static void MakeFrameAttributesFromClasses( TArray<FAnimDatabaseFrameAttribute>& OutFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<TSubclassOf<UAnimDatabaseFrameAttributeFunction>>& Classes);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make Frame Attributes using the given array of UAnimDatabaseFrameAttributeFunctions
- L216 _public prototype_ `static void MakeFrameAttributesFromClassesArrayView( const TArrayView<FAnimDatabaseFrameAttribute> OutFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const TSubclassOf<UAnimDatabaseFrameAttributeFunction>> Classes);`
- L224 _public prototype_ `static void MakeFrameAttributesFromClassesMap( TMap<FName, FAnimDatabaseFrameAttribute>& OutFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TMap<FName, TSubclassOf<UAnimDatabaseFrameAttributeFunction>>& Classes);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make Frame Attributes using the given map of UAnimDatabaseFrameAttributeFunctions
- L234 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromConstant(const bool bActive, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Make a bool frame range attribute from the given ranges and constant value
- L238 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromTrue(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Make a bool frame range attribute from the given ranges with all frames set to true
- L242 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromFalse(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Make a bool frame range attribute from the given ranges with all frames set to false
- L246 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRandomBoolFrameAttribute(UPARAM(ref) int32& State, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta=(NotBlueprintThreadSafe))` — Makes a bool frame attribute for the given ranges where each truth value is randomly sampled
- L250 _public prototype_ `static void MakeRandomBoolFrameAttributes(TArray<FAnimDatabaseFrameAttribute>& OutFrameAttributes, UPARAM(ref) int32& State, const FAnimDatabaseFrameRanges& FrameRanges, const int32 FrameAttributeNum);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes multiple random bool frame attributes from the given range set
- L254 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromActiveRanges(const FAnimDatabaseFrameRanges& Active, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a bool frame attribute which is true where the frame is contained in given Active FrameRangeSet, and false elsewhere
- L258 _public prototype_ `static void MakeBoolFrameAttributesFromActiveRanges(TArray<FAnimDatabaseFrameAttribute>& OutFrameAttributes, const TArray<FAnimDatabaseFrameRanges>& Actives, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes multiple bool frame attributes which are true where the frame is contained in given Active FrameRangeSets, and false elsewhere
- L259 _public prototype_ `static void MakeBoolFrameAttributesFromActiveRangesArrayViews(TArrayView<FAnimDatabaseFrameAttribute> OutFrameAttributes, const TArrayView<const FAnimDatabaseFrameRanges> Actives, const FAnimDatabaseFrameRanges& FrameRanges);`
- L263 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromAnimNotifyState(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> NotifyState);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a bool frame attribute from the given ranges, which is true when the provided NotifyState is active, and false everywhere else
- L267 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromCurveActive(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName CurveName);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a bool frame attribute from the given ranges, which is true when the provided curve is present in the data, and false everywhere else
- L271 _public prototype_ `static void MakeBoolFrameAttributesFromCurvesActive(TArray<FAnimDatabaseFrameAttribute>& OutBoolFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& CurveNames);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a set of bool frame attributes from the given ranges, which are true when the provided curves are present in the data and false everywhere else
- L272 _public prototype_ `static void MakeBoolFrameAttributesFromCurvesActiveArrayView(TArrayView<FAnimDatabaseFrameAttribute> OutBoolFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> CurveNames);`
- L276 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromMirrored(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a bool frame attribute which is true where the frame is mirrored, and false elsewhere
- L280 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoolFrameAttributeFromNotMirrored(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a bool frame attribute which is true where the frame is NOT mirrored, and false elsewhere
- L286 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromConstant(const FAnimDatabaseFrameRanges& FrameRanges, const float Value = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a float frame attribute from the given ranges, filled with the provided value.
- L290 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromZero(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a float frame attribute from the given ranges, filled with zero.
- L294 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromOne(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a float frame attribute from the given ranges, filled with one.
- L298 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromCurve(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName CurveName);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a float frame attribute from the given ranges, using the given curve name. For when the curve is not present in the animations a default value of 0 will be used.
- L302 _public prototype_ `static void MakeFloatFrameAttributesFromCurves(TArray<FAnimDatabaseFrameAttribute>& OutFloatFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& CurveNames);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes multiple float frame attributes from the given ranges and curve names. For when the curve is not present in the animations a default value of 0 will be used.
- L303 _public prototype_ `static void MakeFloatFrameAttributesFromCurvesArrayView(const TArrayView<FAnimDatabaseFrameAttribute> OutFloatFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> CurveNames);`
- L307 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromCurveWhenActive(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName CurveName);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a float frame attribute using the given curve name. For when the curve is not present in the database the attribute will be inactive.
- L311 _public prototype_ `static void MakeFloatFrameAttributesFromCurvesWhenActive(TArray<FAnimDatabaseFrameAttribute>& OutFloatFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& CurveNames);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes multiple float frame attributes from the given ranges and curve names. For when the curve is not present in the animations the attribute will be inactive.
- L312 _public prototype_ `static void MakeFloatFrameAttributesFromCurvesWhenActiveArrayView(const TArrayView<FAnimDatabaseFrameAttribute> OutFloatFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> CurveNames);`
- L316 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromRangeTimes(const FAnimDatabaseFrameRanges& FrameRanges, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a float frame attribute where the value of the attribute is given by the time since the start of the range for each frame in each range in the set.
- L320 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromSequenceTimes(const FAnimDatabaseFrameRanges& FrameRanges, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a float frame attribute where the value of the attribute is given by the sequence time of each frame in each range in the set.
- L324 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromNearestFrameSequenceTimes(const FAnimDatabaseFrameRanges& FrameRanges, const FAnimDatabaseFrames& Frames, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a float frame attribute where the value of the attribute is given by the sequence time of the nearest frame in the Frames frames set. If the range does not contain a frame from Frames, then the time is 0.0
- L328 _public prototype_ `static FAnimDatabaseFrameAttribute MakeFloatFrameAttributeFromUniformRandom(const FAnimDatabaseFrameRanges& FrameRanges, UPARAM(ref) int32& State, const float Min = 0.0f, const float Max = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a float frame attribute from a uniform distribution.
- L334 _public prototype_ `static FAnimDatabaseFrameAttribute MakeLocationFrameAttribute(const FAnimDatabaseFrameAttribute& X, const FAnimDatabaseFrameAttribute& Y, const FAnimDatabaseFrameAttribute& Z);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a location frame attribute from X, Y and Z attributes.
- L338 _public prototype_ `static FAnimDatabaseFrameAttribute MakeLocationFrameAttributeFromConstant(const FAnimDatabaseFrameRanges& FrameRanges, const FVector Location = FVector::ZeroVector);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a location frame attribute from the given ranges, filled with the provided value.
- L344 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRotationFrameAttribute(const FAnimDatabaseFrameAttribute& Pitch, const FAnimDatabaseFrameAttribute& Yaw, const FAnimDatabaseFrameAttribute& Roll);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a rotation frame attribute from Yaw, Pitch and Roll.
- L348 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRotationFrameAttributeFromConstant(const FAnimDatabaseFrameRanges& FrameRanges, const FRotator Rotation = FRotator::ZeroRotator);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a rotation frame attribute from the given ranges, filled with the provided value.
- L352 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRotationFrameAttributeFromConstantQuat(const FAnimDatabaseFrameRanges& FrameRanges, const FQuat Rotation);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a rotation frame attribute from the given ranges, filled with the provided value.
- L356 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRotationFrameAttributeFromBasisDirections(const FAnimDatabaseFrameAttribute& ForwardDirection, const FAnimDatabaseFrameAttribute& RightDirection, const FAnimDatabaseFrameAttribute& UpDirection);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a rotation frame attribute from a set of basis directions.
- L362 _public prototype_ `static FAnimDatabaseFrameAttribute MakeDirectionFrameAttribute(const FAnimDatabaseFrameAttribute& X, const FAnimDatabaseFrameAttribute& Y, const FAnimDatabaseFrameAttribute& Z);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a direction frame attribute from X, Y and Z attributes.
- L366 _public prototype_ `static FAnimDatabaseFrameAttribute MakeDirectionFrameAttributeFromConstant(const FAnimDatabaseFrameRanges& FrameRanges, const FVector Direction = FVector::ForwardVector);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a direction frame attribute from the given ranges, filled with the provided value.
- L372 _public prototype_ `static FAnimDatabaseFrameAttribute MakeScaleFrameAttribute(const FAnimDatabaseFrameAttribute& X, const FAnimDatabaseFrameAttribute& Y, const FAnimDatabaseFrameAttribute& Z);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a scale frame attribute from X, Y and Z attributes.
- L376 _public prototype_ `static FAnimDatabaseFrameAttribute MakeScaleFrameAttributeFromConstant(const FAnimDatabaseFrameRanges& FrameRanges, const FVector Scale = FVector(1, 1, 1));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a scale frame attribute from the given ranges, filled with the provided value.
- L382 _public prototype_ `static FAnimDatabaseFrameAttribute MakeAngleFrameAttributeFromFloatDegrees(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an angle frame attribute from a float frame attribute with values in degrees
- L386 _public prototype_ `static FAnimDatabaseFrameAttribute MakeAngleFrameAttributeFromFloatRadians(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an angle frame attribute from a float frame attribute with values in radians
- L390 _public prototype_ `static FAnimDatabaseFrameAttribute MakeAngleFrameAttributeFromConstantDegrees(const FAnimDatabaseFrameRanges& FrameRanges, const float Value = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an angle frame attribute from the given ranges, filled with the provided value in degrees.
- L394 _public prototype_ `static FAnimDatabaseFrameAttribute MakeAngleFrameAttributeFromConstantRadians(const FAnimDatabaseFrameRanges& FrameRanges, const float Value = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an angle frame attribute from the given ranges, filled with the provided value in radians.
- L400 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootLocationFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a location frame attribute from the root location of the character at the given frame ranges
- L407 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootRotationFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a rotation frame attribute from the root rotation of the character at the given frame ranges
- L414 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootLinearVelocityFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a linear velocity frame attribute from the root linear velocity of the character at the given frame ranges
- L421 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootAngularVelocityFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a angular velocity frame attribute from the root angular velocity of the character at the given frame ranges
- L428 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootDirectionFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a direction frame attribute from the root direction of the character at the given frame ranges
- L436 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootTransformFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a transform frame attribute from the root transform of the character at the given frame ranges
- L443 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootTransformAtSequenceStartFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 2))` — Makes a transform frame attribute from the root transform of the character at the start of each sequence
- L449 _public prototype_ `static void MakeRootLocationAndRotationFrameAttribute( FAnimDatabaseFrameAttribute& OutRootLocationFrameAttribute, FAnimDatabaseFrameAttribute& OutRootRotationFrameAttribute, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes a location and rotation frame attribute from the root location and rotation of the character at the given frame ranges
- L458 _public prototype_ `static void MakeRootLocationAndDirectionFrameAttribute( FAnimDatabaseFrameAttribute& OutRootLocationFrameAttribute, FAnimDatabaseFrameAttribute& OutRootDirectionFrameAttribute, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float RelativeTime = 0.0f, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes a location and direction frame attribute from the root location and direction of the character at the given frame ranges
- L468 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootLocationAtRangeStartFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a location frame attribute from the character root location at the start of the range for every range in the given frame ranges
- L474 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootDirectionAtRangeStartFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a direction frame attribute from the character root direction at the start of the range for every range in the given frame ranges
- L481 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootLocationAtRangeEndFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a location frame attribute from the character root location at the end of the range for every range in the given frame ranges
- L487 _public prototype_ `static FAnimDatabaseFrameAttribute MakeRootDirectionAtRangeEndFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a direction frame attribute from the character root direction at the end of the range for every range in the given frame ranges
- L497 _public prototype_ `static void MakeRootLocationAndDirectionAtRangeEndFrameAttribute( FAnimDatabaseFrameAttribute& OutLocationFrameAttribute, FAnimDatabaseFrameAttribute& OutDirectionFrameAttribute, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes a location and direction frame attribute from the character root location and direction at the end of the range for every range in the given frame ranges
- L508 _public prototype_ `static void MakeTrajectoryFrameAttribute( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutDirectionFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 8))` — Makes an array of location and direction frame attributes for the root at the given sample times into the future
- L520 _public prototype_ `static void MakeLocationTrajectoryFrameAttribute( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 6))` — Makes an array of location frame attributes for the root at the given sample times into the future
- L533 _public prototype_ `static void MakeLookAtTrajectoryFrameAttribute( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutDirectionFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 LookAtBoneIndex, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector LocalDirection = FVector(0.0f, 1.0f, 0.0f), const float DirectionSmoothingAmount = 15.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 10))` — Makes an array of location and direction frame attributes for the root location and look-at-direction of the provided bone at the given sample times into the future
- L550 _public prototype_ `static void MakeRootLocalTrajectoryFrameAttributeAndScale( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutDirectionFrameAttributes, float& OutLocationScale, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 9))` — Makes trajectory frame attributes transformed local to the character's root location and rotation. Computes the overall scale of locations - which is useful for scaling distance costs for use with matching.
- L566 _public prototype_ `static void MakeRootLocalLookAtTrajectoryFrameAttributeAndScale( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutDirectionFrameAttributes, float& OutLocationScale, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 LookAtBoneIndex, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector LocalDirection = FVector(0.0f, 1.0f, 0.0f), const float DirectionSmoothingAmount = 15.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 11))` — Makes look-at trajectory frame attributes transformed local to the character's root location and rotation. Computes the overall scale of locations - which is useful for scaling distance costs for use with matching.
- L590 _public prototype_ `static void MakeBoneLocalFrameAttributes( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutRotationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutScaleFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutLinearVelocityFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutAngularVelocityFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutScalarVelocityFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneLocationIndices, const TArray<int32>& BoneRotationIndices, const TArray<int32>& BoneScaleIndices, const TArray<int32>& BoneLinearVelocityIndices, const TArray<int32>& BoneAngularVelocityIndices, const TArray<int32>& BoneScalarVelocityIndices, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 14, AutoCreateRefTerm = "BoneLocationIndices, BoneRotationIndices, BoneScaleIndices, BoneLinearVelocityIndices, BoneAngularVelocityIndices, BoneScalarVelocityIndices"))` — General function for computing bone attributes in the local space. Outputs various arrays of frame attributes based on the bone indices passed in. This is the most efficient way of computing multiple local bone attributes as it combines all required bone indices into one large array, evaluates the pose data in the animation sequences once extracting information for these bones. Given that evaluating the animation data for a whole animation database can be relatively slow it is encouraged to use this function wherever possible rather than the more convenient individual functions for computing bone attributes.
- L607 _public prototype_ `static void MakeBoneLocalFrameAttributesFromArrayViews( const TArrayView<FAnimDatabaseFrameAttribute> OutLocationFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutRotationFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutScaleFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutLinearVelocityFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutAngularVelocityFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutScalarVelocityFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneLocationIndices = {}, const TArrayView<const int32> BoneRotationIndices = {}, const TArrayView<const int32> BoneScaleIndices = {}, const TArrayView<const int32> BoneLinearVelocityIndices = {}, const TArrayView<const int32> BoneAngularVelocityIndices = {}, const TArrayView<const int32> BoneScalarVelocityIndices = {}, const float RelativeTime = 0.0f);`
- L633 _public prototype_ `static void MakeBoneLocalTransformFrameAttributes( TArray<FAnimDatabaseFrameAttribute>& OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AutoCreateRefTerm = "BoneIndices"))` — General function for computing bone transforms in the local space. Outputs frame attributes based on the bone indices passed in. This is the most efficient way of computing multiple local bone transform attributes as it combines all required bone indices into one large array, evaluates the pose data in the animation sequences once extracting information for these bones. Given that evaluating the animation data for a whole animation database can be relatively slow it is encouraged to use this function wherever possible rather than the more convenient individual functions for computing bone transform attributes.
- L640 _public prototype_ `static void MakeBoneLocalTransformFrameAttributesFromArrayViews( const TArrayView<FAnimDatabaseFrameAttribute> OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneIndices = {}, const float RelativeTime = 0.0f);`
- L648 _public prototype_ `static void MakeBoneLocalTransformFrameAttributesFromNames( TArray<FAnimDatabaseFrameAttribute>& OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& BoneNames, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AutoCreateRefTerm = "BoneNames"))`
- L655 _public prototype_ `static void MakeBoneLocalTransformFrameAttributesFromNamesArrayView( const TArrayView<FAnimDatabaseFrameAttribute> OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> BoneNames = {}, const float RelativeTime = 0.0f);`
- L664 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalTransformFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a location frame attribute from the local transform of a bone
- L668 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalTransformFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a location frame attribute from the local transform of a bone, provided by name
- L672 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalLocationFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a location frame attribute from the local location of a bone
- L676 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalLocationFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a location frame attribute from the local location of a bone, provided by name
- L680 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalRotationFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a rotation frame attribute from the local rotation of a bone
- L684 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalRotationFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a rotation frame attribute from the local rotation of a bone, provided by name
- L688 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalScaleFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a scale frame attribute from the local scale of a bone
- L692 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneLocalScaleFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a scale frame attribute from the local scale of a bone, provided by name
- L705 _public prototype_ `static void MakeBoneGlobalFrameAttributes( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutRotationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutScaleFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutLinearVelocityFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutAngularVelocityFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutScalarVelocityFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneLocationIndices, const TArray<int32>& BoneRotationIndices, const TArray<int32>& BoneScaleIndices, const TArray<int32>& BoneLinearVelocityIndices, const TArray<int32>& BoneAngularVelocityIndices, const TArray<int32>& BoneScalarVelocityIndices, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 14, AutoCreateRefTerm = "BoneLocationIndices, BoneRotationIndices, BoneScaleIndices, BoneLinearVelocityIndices, BoneAngularVelocityIndices, BoneScalarVelocityIndices"))` — General function for computing bone attributes in the world space. Outputs various arrays of frame attributes based on the bone indices passed in. This is the most efficient way of computing multiple global bone attributes as it combines all required bone indices into one large array, evaluates the pose data in the animation sequences once extracting information for these bones, and then performs just the subset of forward kinematics required to extract the desired properties. Given that evaluating the animation data for a whole animation database can be relatively slow it is encouraged to use this function wherever possible rather than the more convenient individual functions for computing bone attributes.
- L722 _public prototype_ `static void MakeBoneGlobalFrameAttributesFromArrayViews( const TArrayView<FAnimDatabaseFrameAttribute> OutLocationFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutRotationFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutScaleFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutLinearVelocityFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutAngularVelocityFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutScalarVelocityFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneLocationIndices = {}, const TArrayView<const int32> BoneRotationIndices = {}, const TArrayView<const int32> BoneScaleIndices = {}, const TArrayView<const int32> BoneLinearVelocityIndices = {}, const TArrayView<const int32> BoneAngularVelocityIndices = {}, const TArrayView<const int32> BoneScalarVelocityIndices = {}, const float RelativeTime = 0.0f);`
- L749 _public prototype_ `static void MakeBoneGlobalTransformFrameAttributes( TArray<FAnimDatabaseFrameAttribute>& OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4, AutoCreateRefTerm = "BoneIndices"))` — General function for computing bone transforms in the world space. Outputs frame attributes based on the bone indices passed in. This is the most efficient way of computing multiple global bone transform attributes as it combines all required bone indices into one large array, evaluates the pose data in the animation sequences once extracting information for these bones, and then performs just the subset of forward kinematics required to extract the desired properties. Given that evaluating the animation data for a whole animation database can be relatively slow it is encouraged to use this function wherever possible rather than the more convenient individual functions for computing bone transform attributes.
- L756 _public prototype_ `static void MakeBoneGlobalFrameAttributesFromArrayViews( const TArrayView<FAnimDatabaseFrameAttribute> OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneIndices = {}, const float RelativeTime = 0.0f);`
- L773 _public prototype_ `static void MakeBoneGlobalTransformFrameAttributesFromNames( TArray<FAnimDatabaseFrameAttribute>& OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& BoneNames, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4, AutoCreateRefTerm = "BoneNames"))` — General function for computing bone transforms in the world space. Outputs frame attributes based on the bone names passed in. This is the most efficient way of computing multiple global bone transform attributes as it combines all required bone names into one large array, evaluates the pose data in the animation sequences once extracting information for these bones, and then performs just the subset of forward kinematics required to extract the desired properties. Given that evaluating the animation data for a whole animation database can be relatively slow it is encouraged to use this function wherever possible rather than the more convenient individual functions for computing bone transform attributes.
- L780 _public prototype_ `static void MakeBoneGlobalTransformFrameAttributesFromNamesArrayView( const TArrayView<FAnimDatabaseFrameAttribute> OutTransformFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> BoneNames, const float RelativeTime = 0.0f);`
- L789 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalLocationFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a location frame attribute from the global location of a bone
- L793 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalLocationFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a location frame attribute from the global location of a bone, provided by name
- L797 _public prototype_ `static void MakeBoneGlobalLocationFrameAttributes(TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes location frame attributes from the global location of bones
- L798 _public prototype_ `static void MakeBoneGlobalLocationFrameAttributesFromArrayViews(const TArrayView<FAnimDatabaseFrameAttribute> OutLocationFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneIndices, const float RelativeTime = 0.0f);`
- L802 _public prototype_ `static void MakeBoneGlobalLocationFrameAttributesFromNames(TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& BoneNames, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes location frame attributes from the global location of bones, provided by name
- L803 _public prototype_ `static void MakeBoneGlobalLocationFrameAttributesFromNamesArrayView(const TArrayView<FAnimDatabaseFrameAttribute> OutLocationFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> BoneNames, const float RelativeTime = 0.0f);`
- L807 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalRotationFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a rotation frame attribute from the global rotation of a bone
- L811 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalRotationFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a rotation frame attribute from the global rotation of a bone, provided by name
- L815 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalDirectionFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FVector LocalDirection = FVector::ForwardVector, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes a direction frame attribute from the global direction of a bone
- L819 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalDirectionFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const FVector LocalDirection = FVector::ForwardVector, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes a direction frame attribute from the global direction of a bone, provided by name
- L823 _public prototype_ `static void MakeBoneGlobalDirectionFrameAttributes(TArray<FAnimDatabaseFrameAttribute>& OutDirectionFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices, const FVector LocalDirection = FVector::ForwardVector, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 5))` — Makes direction frame attributes from the global direction of bones
- L824 _public prototype_ `static void MakeBoneGlobalDirectionFrameAttributesFromArrayViews(const TArrayView<FAnimDatabaseFrameAttribute> OutDirectionFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneIndices, const FVector LocalDirection = FVector::ForwardVector, const float RelativeTime = 0.0f);`
- L828 _public prototype_ `static void MakeBoneGlobalDirectionFrameAttributesFromNames(TArray<FAnimDatabaseFrameAttribute>& OutDirectionFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& BoneNames, const FVector LocalDirection = FVector::ForwardVector, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 5))` — Makes direction frame attributes from the global direction of bones, provided by name
- L829 _public prototype_ `static void MakeBoneGlobalDirectionFrameAttributesFromNamesArrayView(const TArrayView<FAnimDatabaseFrameAttribute> OutDirectionFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> BoneNames, const FVector LocalDirection = FVector::ForwardVector, const float RelativeTime = 0.0f);`
- L833 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalLinearVelocityFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a linear velocity frame attribute from the global linear velocity of a bone
- L837 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalLinearVelocityFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a linear velocity frame attribute from the global linear velocity of a bone, provided by name
- L841 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalAngularVelocityFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a angular velocity frame attribute from the global angular velocity of a bone
- L845 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalAngularVelocityFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a angular velocity frame attribute from the global angular velocity of a bone, provided by name
- L849 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalTransformFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a transform frame attribute from the global transform of a bone
- L853 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalTransformFrameAttributeFromName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 3))` — Makes a transform frame attribute from the global transform of a bone, provided by name
- L857 _public prototype_ `static void MakeBoneGlobalLocationAndLinearVelocityFrameAttribute(FAnimDatabaseFrameAttribute& OutLocationFrameAttribute, FAnimDatabaseFrameAttribute& OutLinearVelocityFrameAttribute, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (AdvancedDisplay = 5))` — Makes a location and linear velocity frame attribute from the global location and linear velocity of a bone
- L861 _public prototype_ `static void MakeBoneGlobalLocationAndLinearVelocityFrameAttributeFromName(FAnimDatabaseFrameAttribute& OutLocationFrameAttribute, FAnimDatabaseFrameAttribute& OutLinearVelocityFrameAttribute, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (AdvancedDisplay = 5))` — Makes a location and linear velocity frame attribute from the global location and linear velocity of a bone, provided by name
- L865 _public prototype_ `static FAnimDatabaseFrameAttribute MakeGlobalDirectionBetweenBonesFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndexFrom, const int32 BoneIndexTo);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes a direction frame attribute from the global vector between bones
- L869 _public prototype_ `static FAnimDatabaseFrameAttribute MakeGlobalDirectionBetweenBonesFrameAttributeFromNames(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneNameFrom, const FName BoneNameTo);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 4))` — Makes a direction frame attribute from the global vector between bones, provided by name
- L873 _public prototype_ `static void MakePoseFrameAttribute( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutLinearVelocityFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices, const float RelativeTime = 0.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AdvancedDisplay = 5))` — Makes arrays of frame attributes for a pose from the provided bone indices
- L886 _public prototype_ `static void MakeRootLocalPoseFrameAttributeAndScale( TArray<FAnimDatabaseFrameAttribute>& OutLocationFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutLinearVelocityFrameAttributes, float& OutLocationScale, float& OutLinearVelocityScale, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes arrays of frame attributes for a pose from the provided bone indices, transformed to be local to the root location and rotation, and then computes the overall scale of the locations and velocities.
- L897 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalLocationAtNearestFramesFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes the global bone location of a bone at the nearest frame in the set of Frames
- L905 _public prototype_ `static FAnimDatabaseFrameAttribute MakeBoneGlobalDirectionAtNearestFramesFrameAttribute( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FAnimDatabaseFrames& Frames, const FVector LocalDirection = FVector::ForwardVector);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes the global bone direction of a bone at the nearest frame in the set of Frames
- L916 _public prototype_ `static void MakeFrameAttributesFromCurves( TArray<FAnimDatabaseFrameAttribute>& OutFloatCurveValueFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutFloatCurveVelocityFrameAttributes, TArray<FAnimDatabaseFrameAttribute>& OutBoolCurveActiveFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FName>& CurveNames);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes frame attributes for curve values, curve velocities, and if a curve is active from a set of given curves
- L924 _public prototype_ `static void MakeFrameAttributesFromCurvesArrayViews( const TArrayView<FAnimDatabaseFrameAttribute> OutFloatCurveValueFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutFloatCurveVelocityFrameAttributes, const TArrayView<FAnimDatabaseFrameAttribute> OutBoolCurveActiveFrameAttributes, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> CurveNames);`
- L936 _public prototype_ `static FAnimDatabaseFrameAttribute MakeTransformFrameAttributeFromConstant(const FAnimDatabaseFrameRanges& FrameRanges, const FTransform Transform = FTransform());` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a transform frame attribute from the given frame ranges filled with a constant value
- L940 _public prototype_ `static FAnimDatabaseFrameAttribute MakeTransformFrameAttributeFromIdentity(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a transform frame attribute from the given frame ranges filled with the identity transform
- L944 _public prototype_ `static FAnimDatabaseFrameAttribute MakeTransformFrameAttribute(const FAnimDatabaseFrameAttribute& Location, const FAnimDatabaseFrameAttribute& Rotation, const FAnimDatabaseFrameAttribute& Scale);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a transform frame attribute from the given Location, Rotation, and Scale frame attributes
- L948 _public prototype_ `static FAnimDatabaseFrameAttribute MakeTransformFrameAttributeNoScale(const FAnimDatabaseFrameAttribute& Location, const FAnimDatabaseFrameAttribute& Rotation);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes a transform frame attribute from the given Location and Rotation frame attributes
- L954 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttribute(const FAnimDatabaseFrames& EventFrames, const FAnimDatabaseFrameRanges& FrameRanges, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an event frame attribute from the given ranges, at the times of the given frames
- L958 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeAtRangeStarts(const FAnimDatabaseFrameRanges& EventFrameRanges, const FAnimDatabaseFrameRanges& FrameRanges, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an event frame attribute from the given ranges, at the start times of the given EventFrameRanges
- L962 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeAtRangeEnds(const FAnimDatabaseFrameRanges& EventFrameRanges, const FAnimDatabaseFrameRanges& FrameRanges, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Makes an event frame attribute from the given ranges, at the end times of the given EventFrameRanges
- L966 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeFromAnimNotify(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotify> Notify);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes an event frame attribute from the given ranges, at the times of the given anim notifies
- L970 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeFromAnimNotifyUnion(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<TSubclassOf<UAnimNotify>>& Notifies);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes an event frame attribute from the given ranges, at the times of the given anim notifies
- L971 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeFromAnimNotifyUnionArrayView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const TSubclassOf<UAnimNotify>> Notifies);`
- L975 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeFromAnimNotifyStateStarts(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> NotifyState);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes an event frame attribute from the given ranges, at the times of the given anim notify state starts
- L979 _public prototype_ `static FAnimDatabaseFrameAttribute MakeEventFrameAttributeFromAnimNotifyStateEnds(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> NotifyState);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Makes an event frame attribute from the given ranges, at the times of the given anim notify state ends
- L985 _public prototype_ `static bool FrameAttributeBoolAtFrame(bool& OutBool, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a bool. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L989 _public prototype_ `static bool FrameAttributeFloatAtFrame(float& OutValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a float. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L993 _public prototype_ `static bool FrameAttributeLocationAtFrame(FVector& OutLocation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a location. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L994 _public prototype_ `static bool FrameAttributeLocationAtFrameFloat(FVector3f& OutLocation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L998 _public prototype_ `static bool FrameAttributeRotationAtFrame(FRotator& OutRotation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a rotation. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L999 _public prototype_ `static bool FrameAttributeRotationAtFrameAsQuat(FQuat& OutRotation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1000 _public prototype_ `static bool FrameAttributeRotationAtFrameAsQuatFloat(FQuat4f& OutRotation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1004 _public prototype_ `static bool FrameAttributeScaleAtFrame(FVector& OutScale, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a scale. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1005 _public prototype_ `static bool FrameAttributeScaleAtFrameFloat(FVector3f& OutScale, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1009 _public prototype_ `static bool FrameAttributeLinearVelocityAtFrame(FVector& OutLinearVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a linear velocity. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1010 _public prototype_ `static bool FrameAttributeLinearVelocityAtFrameFloat(FVector3f& OutLinearVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1014 _public prototype_ `static bool FrameAttributeAngularVelocityAtFrame(FVector& OutAngularVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as an angular velocity. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1015 _public prototype_ `static bool FrameAttributeAngularVelocityAtFrameFloat(FVector3f& OutAngularVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1019 _public prototype_ `static bool FrameAttributeScalarVelocityAtFrame(FVector& OutScalarVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as scalar velocity. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1020 _public prototype_ `static bool FrameAttributeScalarVelocityAtFrameFloat(FVector3f& OutScalarVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1024 _public prototype_ `static bool FrameAttributeDirectionAtFrame(FVector& OutDirection, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a direction. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1025 _public prototype_ `static bool FrameAttributeDirectionAtFrameFloat(FVector3f& OutDirection, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1029 _public prototype_ `static bool FrameAttributeTransformAtFrame(FTransform& OutTransform, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as a transform. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1030 _public prototype_ `static bool FrameAttributeTransformAtFrameFloat(FTransform3f& OutTransform, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);`
- L1034 _public prototype_ `static bool FrameAttributeEventAtFrame(bool& OutTimeUntilEventKnown, float& OutTimeUntilEvent, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as an event. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1038 _public prototype_ `static bool FrameAttributeLocationsAtFrame(TArray<FVector>& OutLocations, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttributes at the provide Sequence and Frame as an array of locations. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1039 _public prototype_ `static bool FrameAttributeLocationsAtFrameToArrayView(const TArrayView<FVector> OutLocations, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 SequenceIdx, const int32 FrameIdx);`
- L1043 _public prototype_ `static bool FrameAttributeDirectionsAtFrame(TArray<FVector>& OutDirections, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttributes at the provide Sequence and Frame as an array of directions. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1044 _public prototype_ `static bool FrameAttributeDirectionsAtFrameToArrayView(const TArrayView<FVector> OutDirections, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 SequenceIdx, const int32 FrameIdx);`
- L1048 _public prototype_ `static bool FrameAttributeLinearVelocitiesAtFrame(TArray<FVector>& OutLinearVelocities, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttributes at the provide Sequence and Frame as an array of linear velocities. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1049 _public prototype_ `static bool FrameAttributeLinearVelocitiesAtFrameToArrayView(const TArrayView<FVector> OutLinearVelocities, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 SequenceIdx, const int32 FrameIdx);`
- L1053 _public prototype_ `static bool FrameAttributeAngleAtFrameDegrees(float& OutValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as an angle in degrees. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1057 _public prototype_ `static bool FrameAttributeAngleAtFrameRadians(float& OutValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Frame as an angle in radians. Returns false if sequence and frame is not within Frame Attribute Ranges.
- L1064 _public prototype_ `static bool FrameAttributeSampleBool(bool& OutBool, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a bool. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1068 _public prototype_ `static bool FrameAttributeSampleFloat(float& OutValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a float. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1072 _public prototype_ `static void FrameAttributeSampleFloatRange(TArray<float>& OutValues, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float StartTime, const float EndTime, const int32 Num, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time Range as a float.
- L1073 _public prototype_ `static void FrameAttributeSampleFloatRangeToArrayView(TArrayView<float> OutValues, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float StartTime, const float EndTime, const int32 Num, const FFrameRate& FrameRate);`
- L1077 _public prototype_ `static bool FrameAttributeSampleLocation(FVector& OutLocation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a location. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1078 _public prototype_ `static bool FrameAttributeSampleLocationFloat(FVector3f& OutLocation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1082 _public prototype_ `static bool FrameAttributeSampleRotation(FRotator& OutRotation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a rotation. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1083 _public prototype_ `static bool FrameAttributeSampleRotationAsQuat(FQuat& OutRotation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1084 _public prototype_ `static bool FrameAttributeSampleRotationAsQuatFloat(FQuat4f& OutRotation, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1088 _public prototype_ `static bool FrameAttributeSampleScale(FVector& OutScale, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a scale. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1089 _public prototype_ `static bool FrameAttributeSampleScaleFloat(FVector3f& OutScale, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1093 _public prototype_ `static bool FrameAttributeSampleLinearVelocity(FVector& OutLinearVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a linear velocity. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1094 _public prototype_ `static bool FrameAttributeSampleLinearVelocityFloat(FVector3f& OutLinearVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1098 _public prototype_ `static bool FrameAttributeSampleAngularVelocity(FVector& OutAngularVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as an angular velocity. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1099 _public prototype_ `static bool FrameAttributeSampleAngularVelocityFloat(FVector3f& OutAngularVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1103 _public prototype_ `static bool FrameAttributeSampleScalarVelocity(FVector& OutScalarVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as scalar velocity. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1104 _public prototype_ `static bool FrameAttributeSampleScalarVelocityFloat(FVector3f& OutScalarVelocity, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1108 _public prototype_ `static bool FrameAttributeSampleDirection(FVector& OutDirection, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a direction. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1109 _public prototype_ `static bool FrameAttributeSampleDirectionFloat(FVector3f& OutDirection, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1113 _public prototype_ `static bool FrameAttributeSampleTransform(FTransform& OutTransform, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as a transform. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1114 _public prototype_ `static bool FrameAttributeSampleTransformFloat(FTransform3f& OutTransform, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1118 _public prototype_ `static bool FrameAttributeSampleEvent(bool& OutTimeUntilEventKnown, float& OutTimeUntilEvent, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as an event. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1122 _public prototype_ `static bool FrameAttributeSampleLocations(TArray<FVector>& OutLocations, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttributes at the provide Sequence and Time as an array of locations. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1123 _public prototype_ `static bool FrameAttributeSampleLocationsToArrayView(const TArrayView<FVector> OutLocations, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1127 _public prototype_ `static bool FrameAttributeSampleDirections(TArray<FVector>& OutDirections, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttributes at the provide Sequence and Time as an array of directions. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1128 _public prototype_ `static bool FrameAttributeSampleDirectionsToArrayView(const TArrayView<FVector> OutDirections, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1132 _public prototype_ `static bool FrameAttributeSampleLinearVelocities(TArray<FVector>& OutLinearVelocities, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttributes at the provide Sequence and Time as an array of linear velocities. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1133 _public prototype_ `static bool FrameAttributeSampleLinearVelocitiesToArrayView(const TArrayView<FVector> OutLinearVelocities, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);`
- L1137 _public prototype_ `static bool FrameAttributeSampleAngleDegrees(float& OutValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as an angle in degrees. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1141 _public prototype_ `static bool FrameAttributeSampleAngleRadians(float& OutValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Sample the given FrameAttribute at the provide Sequence and Time as an angle in radians. Returns false if sequence and time is not within Frame Attribute Ranges.
- L1147 _public prototype_ `static int32 FrameAttributeTotalRangeNum(const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the total number of ranges in a frame attribute
- L1151 _public prototype_ `static int32 FrameAttributeTotalFrameNum(const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the total number of frames in a frame attribute
- L1155 _public prototype_ `static void FrameAttributeToBoolArray(TArray<bool>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of bools
- L1156 _public prototype_ `static void FrameAttributeToBoolArrayView(const TArrayView<bool> OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1160 _public prototype_ `static void FrameAttributeToFloatArray(TArray<float>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of floats
- L1161 _public prototype_ `static void FrameAttributeToFloatArrayView(const TArrayView<float> OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1165 _public prototype_ `static void FrameAttributeToVectorArray(TArray<FVector>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of vectors
- L1166 _public prototype_ `static void FrameAttributeToVectorArrayView(TArray<FVector>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1170 _public prototype_ `static void FrameAttributeToQuatArray(TArray<FQuat>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of quats
- L1171 _public prototype_ `static void FrameAttributeToQuatArrayView(TArray<FQuat>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1175 _public prototype_ `static void FrameAttributeToRotatorArray(TArray<FRotator>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of rotators
- L1176 _public prototype_ `static void FrameAttributeToRotatorArrayView(TArray<FRotator>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1180 _public prototype_ `static void FrameAttributeToTransformArray(TArray<FTransform>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of transforms
- L1181 _public prototype_ `static void FrameAttributeToTransformArrayView(TArray<FTransform>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1185 _public prototype_ `static void FrameAttributeToAngleArrayDegrees(TArray<float>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of floats in degrees
- L1186 _public prototype_ `static void FrameAttributeToAngleArrayViewDegrees(const TArrayView<float> OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1190 _public prototype_ `static void FrameAttributeToAngleArrayRadians(TArray<float>& OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Converts a frame attribute to an array of floats in radians
- L1191 _public prototype_ `static void FrameAttributeToAngleArrayViewRadians(const TArrayView<float> OutArray, const FAnimDatabaseFrameAttribute& FrameAttribute);`
- L1197 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLocationMatchingDistance( const FAnimDatabaseFrameAttribute& LocationFrameAttribute, const FVector Location, const float Scale = 100.0f, const float Weight = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Computes a float frame attribute representing the matching distance between some location frame attribute and a constant location value.
- L1205 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDirectionMatchingDistance( const FAnimDatabaseFrameAttribute& DirectionFrameAttribute, const FVector Direction, const float Weight = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Computes a float frame attribute representing the matching distance between some direction frame attribute and a constant direction value.
- L1212 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRotationMatchingDistance( const FAnimDatabaseFrameAttribute& RotationFrameAttribute, const FQuat Rotation, const float Weight = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Computes a float frame attribute representing the matching distance between some rotation frame attribute and a constant rotation value.
- L1219 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeVelocityMatchingDistance( const FAnimDatabaseFrameAttribute& VelocityFrameAttribute, const FVector Velocity, const float Scale = 200.0f, const float Weight = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Computes a float frame attribute representing the matching distance between some velocity frame attribute and a constant velocity value.
- L1227 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeEventMatchingDistance( const FAnimDatabaseFrameAttribute& EventFrameAttribute, const bool bTimeUntilEventKnown, const float TimeUntilEvent, const float Weight = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Computes a float frame attribute representing the matching distance between some event frame attribute and a constant event value.
- L1242 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeInertializationMatchingDistance( const FAnimDatabaseFrameAttribute& LocationFrameAttribute, const FAnimDatabaseFrameAttribute& LinearVelocityFrameAttribute, const FVector Location, const FVector Velocity, const float BlendTime = 0.2f, const float LocationScale = 100.0f, const float VelocityScale = 200.0f, const float LocationWeight = 1.0f, const float VelocityWeight = 1.0f);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Computes a float frame attribute representing the matching distance between some location and linear velocity frame attributes and a constant location and velocity. Computes this distance using a combination of the maximum velocity offset that would be produced by inertialization, and the integral of the offset displacement produced from inertialization. In general this provides a "nicer" distance metric than just comparing locations and velocities independently because it accounts for the fact that some velocity offsets can actually better correct location offsets during inertialization.
- L1257 _public prototype_ `static float FrameAttributeAverageStd(const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of the std across all channels of a frame attribute
- L1261 _public prototype_ `static float FrameAttributesAverageStd(const TArray<FAnimDatabaseFrameAttribute>& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of the std across all channels of multiple frame attributes
- L1262 _public prototype_ `static float FrameAttributesAverageStdFromArrayView(const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes);`
- L1268 _public prototype_ `static void FindFrameAttributeMinimum( int32& OutSequenceIdx, int32& OutSequenceFrame, float& OutMinimumValue, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Find the sequence and sequence frame with the smallest value in a float frame attribute
- L1276 _public prototype_ `static void FindFrameAttributeMaximum( int32& OutSequenceIdx, int32& OutSequenceFrame, float& OutMaximumValue, const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Find the sequence and sequence frame with the largest value in a float frame attribute
- L1284 _public prototype_ `static void FindFrameAttributeMinimumSequence( UAnimSequence*& OutAnimSequence, float& OutAnimSequenceTime, bool& bOutAnimSequenceMirrored, float& OutMinimumValue, const FAnimDatabaseFrameAttribute& FrameAttribute, const UAnimDatabase* Database);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Find the sequence with the smallest value in a float frame attribute
- L1296 _public prototype_ `static bool FrameAttributeFrameRangesEqual(const FAnimDatabaseFrameAttribute& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Checks if the frame ranges associated with two frame attributes are equal
- L1300 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeIntersection(const FAnimDatabaseFrameAttribute& InFrameAttribute, const FAnimDatabaseFrameRanges& InFrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "INTERSECTION"))` — Returns the intersection of a frame attribute and some range set.
- L1304 _public prototype_ `static FAnimDatabaseFrameRanges FrameAttributeBoolToFrameRanges(const FAnimDatabaseFrameAttribute& BoolFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a Bool frame attribute into frame ranges
- L1308 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFrameRangesToBool(const FAnimDatabaseFrameRanges& ActiveFrameRanges, const FAnimDatabaseFrameRanges& InFrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts frame ranges to a Bool frame attribute
- L1312 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSelect(const FAnimDatabaseFrameAttribute& Cond, const FAnimDatabaseFrameAttribute& True, const FAnimDatabaseFrameAttribute& False);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Selects between True and False based on the given condition bool frame attribute
- L1319 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRepeatFirstInRange(const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Creates a frame attribute that repeats the first value in each range for the rest of the range
- L1325 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAdd(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "+"))` — Adds two frame attributes. Assumes types are compatible
- L1329 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSubtract(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "-"))` — Subtracts two frame attributes. Assumes types are compatible
- L1333 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMultiply(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "*"))` — Multiplies two frame attributes. Assumes types are compatible
- L1337 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDivide(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "/"))` — Divides two frame attributes. Assumes types are compatible
- L1341 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMax(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "MAX"))` — Computes the component-wise maximum of two frame attributes. Assumes types are compatible
- L1345 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMin(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "MIN"))` — Computes the component-wise minimum of two frame attributes. Assumes types are compatible
- L1349 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDot(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "DOT"))` — Computes the dot product of two frame attributes. Assumes types are compatible
- L1353 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeCross(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "CROSS"))` — Computes the cross product of two frame attributes. Assumes types are compatible
- L1359 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAddFloat(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "+"))` — Adds a constant float value to a frame attribute. Assumes types are compatible
- L1363 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSubtractFloat(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "-"))` — Subtracts a constant float value to a frame attribute. Assumes types are compatible
- L1367 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMultiplyFloat(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Multiplies a frame attribute by a constant float value. Assumes types are compatible
- L1371 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDivideFloat(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "/"))` — Divides a frame attribute by a constant float value. Assumes types are compatible
- L1375 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMaxFloat(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "MAX"))` — Computes the component-wise maximum of a frame attribute and a float value. Assumes types are compatible
- L1379 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMinFloat(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "MIN"))` — Computes the component-wise minimum of a frame attribute and a float value. Assumes types are compatible
- L1384 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAddVector(const FAnimDatabaseFrameAttribute& A, const FVector B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "+"))` — Adds a constant vector value to a frame attribute. Assumes types are compatible
- L1388 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSubtractVector(const FAnimDatabaseFrameAttribute& A, const FVector B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "-"))` — Subtracts a constant vector value to a frame attribute. Assumes types are compatible
- L1392 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMultiplyVector(const FAnimDatabaseFrameAttribute& A, const FVector B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Multiplies a frame attribute by a constant vector value. Assumes types are compatible
- L1396 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDivideVector(const FAnimDatabaseFrameAttribute& A, const FVector B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "/"))` — Divides a frame attribute by a constant vector value. Assumes types are compatible
- L1401 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeQuatMultiply(const FQuat A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Multiplies a frame attribute by a constant quat value. Assumes types are compatible
- L1405 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeQuatDivide(const FQuat A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "/"))` — Divides a frame attribute by a constant quat value. Assumes types are compatible
- L1409 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMultiplyQuat(const FAnimDatabaseFrameAttribute& A, const FQuat B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Multiplies a frame attribute by a constant quat value. Assumes types are compatible
- L1413 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDivideQuat(const FAnimDatabaseFrameAttribute& A, const FQuat B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "/"))` — Divides a frame attribute by a constant quat value. Assumes types are compatible
- L1418 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeTransformMultiply(const FTransform& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Multiplies a frame attribute by a constant transform value. Assumes types are compatible
- L1422 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeTransformDivide(const FTransform& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "/"))` — Divides a frame attribute by a constant transform value. Assumes types are compatible
- L1426 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMultiplyTransform(const FAnimDatabaseFrameAttribute& A, const FTransform& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Multiplies a frame attribute by a constant transform value. Assumes types are compatible
- L1430 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDivideTransform(const FAnimDatabaseFrameAttribute& A, const FTransform& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "/"))` — Divides a frame attribute by a constant transform value. Assumes types are compatible
- L1434 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeTransformApply(const FTransform& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "*"))` — Applies a constant transformation to a frame attribute. Assumes types are compatible
- L1438 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeApplyTransformLocation(const FAnimDatabaseFrameAttribute& A, const FVector B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Applies a transformation to a constant location vector. Assumes types are compatible
- L1442 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeApplyTransformDirection(const FAnimDatabaseFrameAttribute& A, const FVector B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Applies a transformation to a constant direction vector. Assumes types are compatible
- L1447 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAddAngleDegrees(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "+"))` — Adds a constant angle value in degrees to an angle frame attribute.
- L1451 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSubtractAngleDegrees(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "-"))` — Subtracts a constant angle value in degrees to an angle frame attribute.
- L1455 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAddAngleRadians(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "+"))` — Adds a constant angle value in radians to an angle frame attribute.
- L1459 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSubtractAngleRadians(const FAnimDatabaseFrameAttribute& A, const float B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "-"))` — Subtracts a constant angle value in radians to an angle frame attribute.
- L1465 _public prototype_ `static void FrameAttributesAdd(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Adds a frame attribute to multiple others. Assumes types are compatible
- L1466 _public prototype_ `static void FrameAttributesAddArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> A, const FAnimDatabaseFrameAttribute& B);`
- L1470 _public prototype_ `static void FrameAttributesSubtract(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Subtracts a frame attribute to multiple others. Assumes types are compatible
- L1471 _public prototype_ `static void FrameAttributesSubtractArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> A, const FAnimDatabaseFrameAttribute& B);`
- L1475 _public prototype_ `static void FrameAttributesMultiply(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Multiplies a frame attribute to multiple others. Assumes types are compatible
- L1476 _public prototype_ `static void FrameAttributesMultiplyArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> A, const FAnimDatabaseFrameAttribute& B);`
- L1480 _public prototype_ `static void FrameAttributesDivide(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Divides a frame attribute to multiple others. Assumes types are compatible
- L1481 _public prototype_ `static void FrameAttributesDivideArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> A, const FAnimDatabaseFrameAttribute& B);`
- L1487 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSum(const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the sum of multiple frame attributes. Assumes all are the same type
- L1488 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSumFromArrayView(const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes);`
- L1492 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeWeightedSum(const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const TArray<float>& Weights);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the weighted sum of multiple frame attributes. Assumes all are the same type
- L1493 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeWeightedSumFromArrayView(const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const TArrayView<const float> Weights);`
- L1497 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDynamicWeightedSum(const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const TArray<FAnimDatabaseFrameAttribute>& Weights);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the weighted sum of multiple frame attributes where the weights are dynamic. Assumes all are the same type
- L1498 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDynamicWeightedSumFromArrayView(const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const TArrayView<const FAnimDatabaseFrameAttribute> Weights);`
- L1502 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeProduct(const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the product of multiple frame attributes. Assumes all are the same type
- L1503 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeProductFromArrayView(const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes);`
- L1509 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeCopy(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Copies a frame attribute.
- L1513 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeNegate(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Negates a frame attribute. Assumes types can be negated
- L1517 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeInvert(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Inverts a frame attribute. Assumes types can be inverted. For float attributes this computes 1/A
- L1521 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAbs(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Takes the absolute value of a frame attribute. Assumes operation is valid on the input type
- L1525 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLog(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Takes the log value of a frame attribute. Assumes operation is valid on the input type
- L1529 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeExp(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Takes the exp value of a frame attribute. Assumes operation is valid on the input type
- L1533 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSin(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Takes the sin value of a frame attribute. Assumes input is an Angle attribute.
- L1537 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeCos(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Takes the cos value of a frame attribute. Assumes input is an Angle attribute.
- L1541 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAtan2(const FAnimDatabaseFrameAttribute& Y, const FAnimDatabaseFrameAttribute& X);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the atan2 value of two frame attributes. Assumes inputs are Float attributes. Output is an Angle attribute.
- L1547 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeInverseMultiply(const FAnimDatabaseFrameAttribute& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes inv(A) x B for two frame attributes. Assumes types are compatible
- L1551 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeMultiplyInverse(const FAnimDatabaseFrameAttribute& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes A x inv(B) for two frame attributes. This is the same as division. Assumes types are compatible
- L1555 _public prototype_ `static void FrameAttributesInverseMultiply(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes inv(A) x B for arrays of frame attributes. Assumes types are compatible
- L1556 _public prototype_ `static void FrameAttributesInverseMultiplyArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> A, const FAnimDatabaseFrameAttribute& B);`
- L1560 _public prototype_ `static void FrameAttributesMultiplyInverse(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& A, const FAnimDatabaseFrameAttribute& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes A x inv(B) for arrays of frame attributes. Assumes types are compatible
- L1561 _public prototype_ `static void FrameAttributesMultiplyInverseArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> A, const FAnimDatabaseFrameAttribute& B);`
- L1567 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRotate(const FAnimDatabaseFrameAttribute& Rotation, const FAnimDatabaseFrameAttribute& Vector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Rotates a vector frame attribute by the given rotation frame attribute
- L1571 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeUnrotate(const FAnimDatabaseFrameAttribute& Rotation, const FAnimDatabaseFrameAttribute& Vector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Unrotates a vector frame attribute by the given rotation frame attribute
- L1575 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeQuatRotate(const FQuat& Rotation, const FAnimDatabaseFrameAttribute& Vector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Rotates a vector frame attribute by the given rotation
- L1579 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeQuatUnrotate(const FQuat& Rotation, const FAnimDatabaseFrameAttribute& Vector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Unrotates a vector frame attribute by the given rotation
- L1584 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRotateDirection(const FAnimDatabaseFrameAttribute& Rotation, const FVector Direction = FVector::ForwardVector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Rotates the given constant direction by the rotation frame attribute
- L1588 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeUnrotateDirection(const FAnimDatabaseFrameAttribute& Rotation, const FVector Direction = FVector::ForwardVector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Unrotates the given constant direction by the rotation frame attribute
- L1592 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRotationBetweenDirection(const FAnimDatabaseFrameAttribute& Directions, const FVector Direction = FVector::ForwardVector);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Compute the rotation between the given direction frame attribute and the constant direction provided
- L1596 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRotateAndAdd(const FAnimDatabaseFrameAttribute& Vector, const FAnimDatabaseFrameAttribute& Rotation, const FAnimDatabaseFrameAttribute& Addition);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Rotates and Adds a vector frame attribute by the given addition and rotation frame attributes
- L1600 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSubtractAndUnrotate(const FAnimDatabaseFrameAttribute& Vector, const FAnimDatabaseFrameAttribute& Subtraction, const FAnimDatabaseFrameAttribute& Rotation);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Subtracts and Unrotates a vector frame attribute by the given subtract and rotation frame attributes
- L1604 _public prototype_ `static void FrameAttributesRotate(TArray<FAnimDatabaseFrameAttribute>& OutVectors, const FAnimDatabaseFrameAttribute& Rotation, const TArray<FAnimDatabaseFrameAttribute>& InVectors);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Rotates multiple frame attributes by a rotation frame attribute. Assumes types are compatible
- L1605 _public prototype_ `static void FrameAttributesRotateArrayView(const TArrayView<FAnimDatabaseFrameAttribute> OutVectors, const FAnimDatabaseFrameAttribute& Rotation, const TArrayView<const FAnimDatabaseFrameAttribute> InVectors);`
- L1609 _public prototype_ `static void FrameAttributesUnrotate(TArray<FAnimDatabaseFrameAttribute>& OutVectors, const FAnimDatabaseFrameAttribute& Rotation, const TArray<FAnimDatabaseFrameAttribute>& InVectors);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Unrotates multiple frame attributes by a rotation frame attribute. Assumes types are compatible
- L1610 _public prototype_ `static void FrameAttributesUnrotateArrayView(const TArrayView<FAnimDatabaseFrameAttribute> OutVectors, const FAnimDatabaseFrameAttribute& Rotation, const TArrayView<const FAnimDatabaseFrameAttribute> InVectors);`
- L1614 _public prototype_ `static void FrameAttributesRotateAndAdd(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const FAnimDatabaseFrameAttribute& Rotation, const FAnimDatabaseFrameAttribute& Addition);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Rotates and adds multiple frame attributes by rotation and addition frame attributes. Assumes types are compatible
- L1615 _public prototype_ `static void FrameAttributesRotateAndAddArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const FAnimDatabaseFrameAttribute& Rotation, const FAnimDatabaseFrameAttribute& Addition);`
- L1619 _public prototype_ `static void FrameAttributesSubtractAndUnrotate(TArray<FAnimDatabaseFrameAttribute>& Out, const TArray<FAnimDatabaseFrameAttribute>& FrameAttributes, const FAnimDatabaseFrameAttribute& Subtraction, const FAnimDatabaseFrameAttribute& Rotation);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Subtracts and unrotates multiple frame attributes by subtraction and rotation frame attributes. Assumes types are compatible
- L1620 _public prototype_ `static void FrameAttributesSubtractAndUnrotateArrayView(const TArrayView<FAnimDatabaseFrameAttribute> Out, const TArrayView<const FAnimDatabaseFrameAttribute> FrameAttributes, const FAnimDatabaseFrameAttribute& Subtraction, const FAnimDatabaseFrameAttribute& Rotation);`
- L1624 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeToRotationVector(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a rotation frame attribute into an angular velocity frame attribute.
- L1628 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFromRotationVector(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts an angular velocity frame attribute into a rotation frame attribute.
- L1634 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeX(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the X component of a frame attribute. Assumes type is subscriptable
- L1638 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeY(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the Y component of a frame attribute. Assumes type is subscriptable
- L1642 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeZ(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the Z component of a frame attribute. Assumes type is subscriptable
- L1646 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeW(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the W component of a frame attribute. Assumes type is subscriptable
- L1650 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeTransformLocation(const FAnimDatabaseFrameAttribute& Transform);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the Location part of a Transform frame attribute
- L1654 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeTransformRotation(const FAnimDatabaseFrameAttribute& Transform);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the Rotation part of a Transform frame attribute
- L1658 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeTransformScale(const FAnimDatabaseFrameAttribute& Transform);` — `UFUNCTION(BlueprintPure = true, Category = "AnimDatabase")` — Gets the Scale part of a Transform frame attribute
- L1662 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLength(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "LENGTH"))` — Computes the vector length of a frame attribute. Assumes type has a meaningful length
- L1666 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeProject(const FAnimDatabaseFrameAttribute& A, const FVector Projection = FVector(1.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Projects a frame attribute with the given vector. Assumes type is compatible
- L1670 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributePitch(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the Pitch component of a rotation frame attribute.
- L1674 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeYaw(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the Yaw component of a rotation frame attribute.
- L1678 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeRoll(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts the Roll component of a rotation frame attribute.
- L1684 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeEqual(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "=="))` — Returns a bool frame attribute describing if two frame attributes are numerically equal on each frame
- L1688 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeEqualTransform(const FAnimDatabaseFrameAttribute& TransformFrameAttribute, const FTransform& Transform);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "=="))` — Returns a bool frame attribute describing if the given transform attribute is equal to the provided transform on each frame
- L1692 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeGreaterThanFloat(const FAnimDatabaseFrameAttribute& FloatFrameAttribute, const float Threshold);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = ">"))` — Compares if a float frame attribute is greater than the given threshold and returns a bool frame attribute
- L1696 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLessThanFloat(const FAnimDatabaseFrameAttribute& FloatFrameAttribute, const float Threshold);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "<"))` — Compares if a float frame attribute is less than the given threshold and returns a bool frame attribute
- L1700 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeGreaterThanAngleDegrees(const FAnimDatabaseFrameAttribute& AngleFrameAttribute, const float Threshold);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = ">"))` — Compares if a angle frame attribute is greater than the given threshold in degrees and returns a bool frame attribute
- L1704 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLessThanAngleDegrees(const FAnimDatabaseFrameAttribute& AngleFrameAttribute, const float Threshold);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "<"))` — Compares if a angle frame attribute is less than the given threshold in degrees and returns a bool frame attribute
- L1708 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeGreaterThanAngleRadians(const FAnimDatabaseFrameAttribute& AngleFrameAttribute, const float Threshold);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = ">"))` — Compares if a angle frame attribute is greater than the given threshold in radians and returns a bool frame attribute
- L1712 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLessThanAngleRadians(const FAnimDatabaseFrameAttribute& AngleFrameAttribute, const float Threshold);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "<"))` — Compares if a angle frame attribute is less than the given threshold in radians and returns a bool frame attribute
- L1716 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeNot(const FAnimDatabaseFrameAttribute& A);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "NOT"))` — Computes the logical not of a bool frame attribute
- L1720 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAnd(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "AND"))` — Computes the logical and of two bool frame attributes
- L1724 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeOr(FAnimDatabaseFrameAttribute A, FAnimDatabaseFrameAttribute B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "OR"))` — Computes the logical or of two bool frame attributes
- L1728 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeBoolToFloat(const FAnimDatabaseFrameAttribute& BoolFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a bool frame attribute to a float frame attribute
- L1732 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAngleToFloatDegrees(const FAnimDatabaseFrameAttribute& AngleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts an angle frame attribute to a float frame attribute in degrees
- L1736 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeAngleToFloatRadians(const FAnimDatabaseFrameAttribute& AngleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts an angle frame attribute to a float frame attribute in radians
- L1740 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFloatToBool(const FAnimDatabaseFrameAttribute& FloatFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a float frame attribute to a bool frame attribute
- L1744 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFloatToAngleDegrees(const FAnimDatabaseFrameAttribute& FloatFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a float frame attribute to an angle frame attribute in degrees
- L1748 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFloatToAngleRadians(const FAnimDatabaseFrameAttribute& FloatFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a float frame attribute to an angle frame attribute in radians
- L1752 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeDirectionToLocation(const FAnimDatabaseFrameAttribute& DirectionFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a direction frame attribute to a location frame attribute
- L1756 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeLocationToDirection(const FAnimDatabaseFrameAttribute& LocationFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a location frame attribute to a direction frame attribute (normalizing the result)
- L1760 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeVelocityToDirection(const FAnimDatabaseFrameAttribute& VelocityFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Converts a velocity frame attribute to a direction frame attribute (normalizing the result)
- L1766 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeExtractPhase(const FAnimDatabaseFrameRanges& FrameRanges, const FAnimDatabaseFrames& ZeroPhaseFrames, const FAnimDatabaseFrames& HalfPhaseFrames, const EAnimDatabasePhaseExtrapolationMode ExtrapolationMode = EAnimDatabasePhaseExtrapolationMode::Repeat);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Extracts a phase angle from two sets of frames representing the start of the phase and half way through the phase
- L1772 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFilterGaussian(const FAnimDatabaseFrameAttribute& FloatFrameAttribute, const float StandardDeviationInFrames = 3.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Applies a Gaussian smoothing filter to the values in each range of a frame attribute. Assumes type is compatible
- L1776 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFilterSavGol(const FAnimDatabaseFrameAttribute& FloatFrameAttribute, const int32 FilterWidthInFrames = 7, const int32 PolynomialDegree = 3, const bool bGaussianWindowed = true);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Applies a SavGol filter to the values in each range of a frame attribute. Assumes type is compatible
- L1780 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFilterMajorityVote(const FAnimDatabaseFrameAttribute& BoolFrameAttribute, const int32 FilterWidthInFrames = 5);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Applies a majority vote filter to the values in each range of a frame attribute. Assumes type is compatible
- L1786 _public prototype_ `static void FrameAttributeLocationMeanAndStd(FVector& OutMean, FVector& OutStd, const FAnimDatabaseFrameAttribute& LocationFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the mean and std of a location frame attribute
- L1790 _public prototype_ `static void FrameAttributeFloatAverage(float& OutAverageFloat, const FAnimDatabaseFrameAttribute& FloatFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of a float frame attribute
- L1794 _public prototype_ `static void FrameAttributeAngleAverageDegrees(float& OutAverageAngle, const FAnimDatabaseFrameAttribute& AngleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of an angle frame attribute in degrees
- L1798 _public prototype_ `static void FrameAttributeAngleAverageRadians(float& OutAverageAngle, const FAnimDatabaseFrameAttribute& AngleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of an angle frame attribute in radians
- L1802 _public prototype_ `static void FrameAttributeFloatMinAndMax(float& OutMin, float& OutMax, const FAnimDatabaseFrameAttribute& FloatFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the min and max of a float frame attribute
- L1806 _public prototype_ `static void FrameAttributeAngleMinAndMaxDegrees(float& OutMin, float& OutMax, const FAnimDatabaseFrameAttribute& AngleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the min and max of an angle frame attribute in degrees
- L1810 _public prototype_ `static void FrameAttributeAngleMinAndMaxRadians(float& OutMin, float& OutMax, const FAnimDatabaseFrameAttribute& AngleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the min and max of an angle frame attribute in radians
- L1814 _public prototype_ `static void FrameAttributeLocationAverage(FVector& OutAverageLocation, const FAnimDatabaseFrameAttribute& LocationFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of a location frame attribute
- L1818 _public prototype_ `static void FrameAttributeDirectionAverage(FVector& OutAverageDirection, const FAnimDatabaseFrameAttribute& DirectionFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the average of a direction frame attribute
- L1822 _public prototype_ `static void FrameAttributeRotationMeanAndStd(FRotator& OutMean, FVector& OutStd, const FAnimDatabaseFrameAttribute& RotationFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the mean and std (represented as an angular velocity) of a rotation frame attribute
- L1823 _public prototype_ `static void FrameAttributeRotationMeanAndStdAsQuat(FQuat& OutMean, FVector& OutStd, const FAnimDatabaseFrameAttribute& RotationFrameAttribute);`
- L1827 _public prototype_ `static void FrameAttributeScaleMeanAndStd(FVector& OutMean, FVector& OutLogStd, const FAnimDatabaseFrameAttribute& ScaleFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the mean and log std of a scale frame attribute
- L1831 _public prototype_ `static void FrameAttributeVelocityMeanAndStd(FVector& OutMean, FVector& OutStd, const FAnimDatabaseFrameAttribute& VelocityFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the mean and std of a velocity frame attribute
- L1835 _public prototype_ `static void FrameAttributeLocationDistanceTraveled(float& OutMean, float& OutStd, float& OutMin, float& OutMax, const FAnimDatabaseFrameAttribute& LocationFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the mean, std, min, and max distance traveled across each range in a location frame attribute
- L1839 _public prototype_ `static void FrameAttributeRotationAngleTraveled(float& OutMean, float& OutStd, float& OutMin, float& OutMax, const FAnimDatabaseFrameAttribute& RotationFrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes the mean, std, min, and max angle traveled (in degrees) across each range in a rotation frame attribute
- L1845 _public prototype_ `static FString FrameAttributeToString(const FAnimDatabaseFrameAttribute& FrameAttribute);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "FrameAttribute", Keywords="Print,Log,Display,Name"))` — Converts a FrameAttribute object to a string.
- L1849 _public prototype_ `static FString FrameAttributeToStringFormat(const UAnimDatabase* Database, const FAnimDatabaseFrameAttribute& FrameAttribute, const int32 Cutoff = 11);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta= (Keywords = "Print,Log,Display,Name"))` — Converts a FrameAttribute object to a string object in full.
- L1869 _public prototype_ `static FAnimDatabaseFrameRanges FrameAttributeOutlierFrameRanges( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 Padding = 60, const float Threshold = 10.0f, const float LocationMinimumDifference = 5.0f, const float RotationMinimumDifference = 5.0f, const float ScaleMinimumDifference = 0.1f, const float LinearVelocityMinimumDifference = 10.0f, const float AngularVelocityMinimumDifference = 10.0f, const float ScalarVelocityMinimumDifference = 0.2f);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes frame ranges across the given set of range CheckFrameRanges which may contain outliers or glitches in the character pose. @param Database							Database to check for outliers in @param FrameRanges						Ranges in the database to check for outliers @param Padding							Padding to apply to returned outlier ranges in frames @param Threshold							Number of multiples of the standard deviation away from the mean to treat as an outlier @param LocationMinimumDifference			Minimum difference away from the mean (in cm) for bone locations to treat as outliers @param RotationMinimumDifference			Minimum difference away from the mean (in degrees) for bone rotations to treat as outliers @param ScaleMinimumDifference			Minimum difference away from the mean for bone scales to treat as outliers @param LinearVelocityMinimumDifference	Minimum difference away from the mean (in cm/s) for bone linear velocities to treat as outliers @param AngularVelocityMinimumDifference	Minimum difference away from the mean (in deg/s) for bone angular velocities to treat as outliers @param ScalarVelocityMinimumDifference	Minimum difference away from the mean for bone scalar velocities to treat as outliers
- L1897 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeSavGolSmoothedRootTransform( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName RootLocationProjectionBoneName = TEXT("spine_02"), const FName RootRotationProjectionBoneName = TEXT("pelvis"), const FVector RootRotationBoneForwardDirection = FVector(0, 1, 0), const FVector RootForwardDirection = FVector(0, 1, 0), const int32 LocationSavGolFrameNum = 61, const int32 LocationSavGolPolynomialDegree = 3, const int32 DirectionSavGolFrameNum = 91, const int32 DirectionSavGolPolynomialDegree = 3, const bool bGaussianWindowed = true);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes a root transform by projecting bones onto the ground plane and smoothing the resulting location and direction with a SavGol filter. @param Database							Database to use @param FrameRanges						Ranges in the database to use @param RootLocationProjectionBoneName	Name of the bone to project onto the ground plane and use as the root location @param RootRotationProjectionBoneName	Name of the bone to project onto the ground plane and use as the root rotation @param RootRotationBoneForwardDirection	Local forward direction of the bone to use as the root rotation @param RootForwardDirection				Local forward direction of the desired root transform @param LocationSavGolFrameNum			Number of frames over which to apply the location savgol filter @param LocationSavGolPolynomialDegree	Degree of polynomial to use for the location savgol filter @param DirectionSavGolFrameNum			Number of frames over which to apply the location direction filter @param DirectionSavGolPolynomialDegree	Degree of polynomial to use for the direction savgol filter @param bGaussianWindowed					If to apply a gaussian weighted window to the savgol polynomial fitting
- L1923 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeGaussianSmoothedRootTransform( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName RootLocationProjectionBoneName = TEXT("spine_02"), const FName RootRotationProjectionBoneName = TEXT("pelvis"), const FVector RootRotationBoneForwardDirection = FVector(0, 1, 0), const FVector RootForwardDirection = FVector(0, 1, 0), const float LocationSmoothingAmount = 9.0f, const float RotationSmoothingAmount = 15.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes a root transform by projecting bones onto the ground plane and smoothing the resulting location and direction with a Gaussian filter. @param Database							Database to use @param FrameRanges						Ranges in the database to use @param RootLocationProjectionBoneName	Name of the bone to project onto the ground plane and use as the root location @param RootRotationProjectionBoneName	Name of the bone to project onto the ground plane and use as the root rotation @param RootRotationBoneForwardDirection	Local forward direction of the bone to use as the root rotation @param RootForwardDirection				Local forward direction of the desired root transform @param LocationSmoothingAmount			Amount of smoothing to apply to the root location projection (in frames) @param RotationSmoothingAmount			Amount of smoothing to apply to the root rotation projection (in frames)
- L1941 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeBoneSpeed( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName = TEXT("foot` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes a float attribute representing the global speed of a given joint. @param Database							Database to use @param FrameRanges						Ranges in the database to use @param BoneName							Name of the bone to compute the speed of
- L1961 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeContactCurve( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName = TEXT("ball_l"), const float HeightThreshold = 20.0f, const float VelocityThreshold = 25.0f, const bool bFilterCurve = true, const int32 MajorityVoteFilterWidth = 5, const bool bSmoothCurve = true, const float SmoothingAmount = 3.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes a float attribute representing a contact state for the given joint. @param Database							Database to use @param FrameRanges						Ranges in the database to use @param BoneName							Name of the bone to compute the contact state for @param HeightThreshold					Maximum height (in cm) for which the bone can be considered in contact @param VelocityThreshold					Maximum velocity (in cm/s) for which the bone can be considered in contact @param bFilterCurve						If to apply the majority vote filter to the curve @param MajorityVoteFilterWidth			Filter width (in frames) for the majority vote filter used to remove very short contact transitions. contact periods (or non-contact periods) less than half this duration will be removed. @param bSmoothCurve						If to apply the smoothing filter to the curve @param SmoothingAmount					Amount of smoothing to apply to the resulting contact curve (in frames)
- L1985 _public prototype_ `static FAnimDatabaseFrameRanges FrameAttributeContactRanges( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName = TEXT("ball_l"), const float HeightThreshold = 20.0f, const float VelocityThreshold = 25.0f, const bool bFilterCurve = true, const int32 MajorityVoteFilterWidth = 5);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes a frame ranges object representing the contact down times for the given joint. @param Database							Database to use @param FrameRanges						Ranges in the database to use @param BoneName							Name of the bone to compute the contact state for @param HeightThreshold					Maximum height (in cm) for which the bone can be considered in contact @param VelocityThreshold					Maximum velocity (in cm/s) for which the bone can be considered in contact @param bFilterCurve						If to apply the majority vote filter to the curve @param MajorityVoteFilterWidth			Filter width (in frames) for the majority vote filter used to remove very short contact transitions. contact periods (or non-contact periods) less than half this duration will be removed.
- L2009 _public prototype_ `static FAnimDatabaseFrames FrameAttributeContactFrames( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName = TEXT("ball_l"), const float HeightThreshold = 20.0f, const float VelocityThreshold = 25.0f, const bool bFilterCurve = true, const int32 MajorityVoteFilterWidth = 5, const float FrameOffset = 0.0f, const bool bIgnoreFirstFrame = true);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Computes a frames object representing the contact down times for the given joint. @param Database							Database to use @param FrameRanges						Ranges in the database to use @param BoneName							Name of the bone to compute the contact state for @param HeightThreshold					Maximum height (in cm) for which the bone can be considered in contact @param VelocityThreshold					Maximum velocity (in cm/s) for which the bone can be considered in contact @param bFilterCurve						If to apply the majority vote filter to the curve @param MajorityVoteFilterWidth			Filter width (in frames) for the majority vote filter used to remove very short contact transitions. contact periods (or non-contact periods) less than half this duration will be removed. @param FrameOffset						The amount of time before the contact (in seconds) to have the frame @param bIgnoreFirstFrame					Removes contact frames that occur on the first frame of the frame ranges
- L2035 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFitTransform( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FAnimDatabaseFrameAttribute>& FitLocations, const TArray<FAnimDatabaseFrameAttribute>& FitForwardDirections, const TArray<FAnimDatabaseFrameAttribute>& FitRightDirections, const TArray<FAnimDatabaseFrameAttribute>& FitUpDirections, const TArray<FAnimDatabaseFrameAttribute>& FitLocationWeights, const TArray<FAnimDatabaseFrameAttribute>& FitForwardDirectionWeights, const TArray<FAnimDatabaseFrameAttribute>& FitRightDirectionWeights, const TArray<FAnimDatabaseFrameAttribute>& FitUpDirectionWeights);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, AutoCreateRefTerm="FitLocationWeights, FitForwardDirectionWeights, FitRightDirectionWeights, FitUpDirectionWeights"))` — Fits a transform from the given location and direction attributes @param Database							Database to use @param FrameRanges						Ranges in the database to use @param FitLocations						Array of attributes for computing the locations to use for the fit @param FitForwardDirections				Array of attributes for computing the forward directions to use for the fit @param FitRightDirections				Array of attributes for computing the right directions to use for the fit @param FitUpDirections					Array of attributes for computing the up directions to use for the fit @param FitLocationWeights				Optional array of weights to use for the fit locations @param FitForwardDirectionWeights		Optional array of weights to use for the fit forward directions @param FitRightDirectionWeights			Optional array of weights to use for the fit right directions @param FitUpDirectionWeights				Optional array of weights to use for the fit up directions
- L2047 _public prototype_ `static FAnimDatabaseFrameAttribute FrameAttributeFitTransformFromArrayViews( const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FAnimDatabaseFrameAttribute> FitLocations, const TArrayView<const FAnimDatabaseFrameAttribute> FitForwardDirections, const TArrayView<const FAnimDatabaseFrameAttribute> FitRightDirections, const TArrayView<const FAnimDatabaseFrameAttribute> FitUpDirections, const TArrayView<const FAnimDatabaseFrameAttribute> FitLocationWeights, const TArrayView<const FAnimDatabaseFrameAttribute> FitForwardDirectionWeights, const TArrayView<const FAnimDatabaseFrameAttribute> FitRightDirectionWeights, const TArrayView<const FAnimDatabaseFrameAttribute> FitUpDirectionWeights);`

#### class `UAnimDatabaseFrameAttributeFunction`  
`class UAnimDatabaseFrameAttributeFunction : public UObject`  
_L2062-2071_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: A simple class that has a single implementable function which constructs a FAnimDatabaseFrameAttribute object from a UAnimDatabase.
- L2070 _public prototype_ `FAnimDatabaseFrameAttribute MakeFrameAttribute(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimDatabase")` — Callback that constructs a FrameAttribute from a UAnimDatabase

#### class `UAnimDatabaseFrameAttributeFunction_FrameRanges`  
`class UAnimDatabaseFrameAttributeFunction_FrameRanges : public UAnimDatabaseFrameAttributeFunction`  
_L2075-2088_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Frame Ranges Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bool Frame Attribute for the given Frame Ranges
- L2083 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRangesFunction;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame Ranges to use
- L2087 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_Filter`  
`class UAnimDatabaseFrameAttributeFunction_Filter : public UAnimDatabaseFrameAttributeFunction`  
_L2092-2109_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Filter Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes an Attribute for the given Frame Ranges
- L2100 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRangesFunction;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame Ranges to filter to
- L2104 _public member_ `TObjectPtr<UAnimDatabaseFrameAttributeFunction> FrameAttributeFunction;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame Attribute to create
- L2108 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Outliers`  
`class UAnimDatabaseFrameRangesFunction_Outliers : public UAnimDatabaseFrameRangesFunction`  
_L2113-2158_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Outliers Frame Attribute"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the potential outlier frame ranges in a database
- L2121 _public member_ `int32 Padding = 60;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Padding to apply to returned outlier ranges in frames
- L2125 _public member_ `float Threshold = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Number of multiples of the standard deviation away from the mean to treat as an outlier
- L2129 _public member_ `float LocationMinimumDifference = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Minimum difference away from the mean (in cm) for bone locations to treat as outliers
- L2133 _public member_ `float RotationMinimumDifference = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Minimum difference away from the mean (in degrees) for bone rotations to treat as outliers
- L2137 _public member_ `float ScaleMinimumDifference = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Minimum difference away from the mean for bone scales to treat as outliers
- L2141 _public member_ `float LinearVelocityMinimumDifference = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Minimum difference away from the mean (in cm/s) for bone linear velocities to treat as outliers
- L2145 _public member_ `float AngularVelocityMinimumDifference = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Minimum difference away from the mean (in deg/s) for bone angular velocities to treat as outliers
- L2149 _public member_ `float ScalarVelocityMinimumDifference = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Minimum difference away from the mean for bone scalar velocities to treat as outliers
- L2153 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> ExcludedRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Ranges that are excluded from the outlier detection
- L2157 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_ContactCurve`  
`class UAnimDatabaseFrameAttributeFunction_ContactCurve : public UAnimDatabaseFrameAttributeFunction`  
_L2162-2202_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Contact Curve Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a contact curve attribute
- L2170 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the contact state for
- L2174 _public member_ `float HeightThreshold = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Maximum height (in cm) for which the bone can be considered in contact
- L2178 _public member_ `float VelocityThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Maximum velocity (in cm/s) for which the bone can be considered in contact
- L2182 _public member_ `bool bFilterCurve = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to filter the curve
- L2189 _public member_ `int32 MajorityVoteFilterWidth = 5;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bFilterCurve", HideEditConditionToggle))` — Filter width (in frames) for the majority vote filter used to remove very short contact transitions. Contact periods (or non-contact periods) less than half this duration will be removed.
- L2193 _public member_ `bool bSmoothCurve = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to smooth the curve
- L2197 _public member_ `float SmoothingAmount = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bSmoothCurve", HideEditConditionToggle))` — Amount of smoothing to apply to the resulting contact curve (in frames)
- L2201 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFramesFunction_ContactFrames`  
`class UAnimDatabaseFramesFunction_ContactFrames : public UAnimDatabaseFramesFunction`  
_L2206-2246_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Contact Frames Frame Attribute"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Computes contact frames
- L2214 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the contact state for
- L2218 _public member_ `float HeightThreshold = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Maximum height (in cm) for which the bone can be considered in contact
- L2222 _public member_ `float VelocityThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Maximum velocity (in cm/s) for which the bone can be considered in contact
- L2226 _public member_ `bool bFilterCurve = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to filter the curve
- L2233 _public member_ `int32 MajorityVoteFilterWidth = 5;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bFilterCurve", HideEditConditionToggle))` — Filter width (in frames) for the majority vote filter used to remove very short contact transitions. Contact periods (or non-contact periods) less than half this duration will be removed.
- L2237 _public member_ `float EventOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s"))` — The amount of time before the contact (in seconds) to have the event
- L2241 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> EventFilter;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — If provided, will be used to filter the contact events
- L2245 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_ContactEvent`  
`class UAnimDatabaseFrameAttributeFunction_ContactEvent : public UAnimDatabaseFrameAttributeFunction`  
_L2250-2290_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Contact Event Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a contact event attribute
- L2258 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the contact state for
- L2262 _public member_ `float HeightThreshold = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Maximum height (in cm) for which the bone can be considered in contact
- L2266 _public member_ `float VelocityThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Maximum velocity (in cm/s) for which the bone can be considered in contact
- L2270 _public member_ `bool bFilterCurve = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to filter the curve
- L2277 _public member_ `int32 MajorityVoteFilterWidth = 5;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bFilterCurve", HideEditConditionToggle))` — Filter width (in frames) for the majority vote filter used to remove very short contact transitions. Contact periods (or non-contact periods) less than half this duration will be removed.
- L2281 _public member_ `float EventOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "s"))` — The amount of time before the contact (in seconds) to have the event
- L2285 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> EventFilter;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — If provided, will be used to filter the contact events
- L2289 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_FitTransform`  
`class UAnimDatabaseFrameAttributeFunction_FitTransform : public UAnimDatabaseFrameAttributeFunction`  
_L2294-2335_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Fit Transform Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Fits a transform to the given locations and directions
- L2302 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitLocations;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Array of attributes for computing the locations to use for the fit
- L2306 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitForwardDirections;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Array of attributes for computing the forward directions to use for the fit
- L2310 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitRightDirections;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Array of attributes for computing the right directions to use for the fit
- L2314 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitUpDirections;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Array of attributes for computing the up directions to use for the fit
- L2318 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitLocationWeights;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Optional array of weights to use for the fit locations
- L2322 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>>FitForwardDirectionWeights;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Optional array of weights to use for the fit forward directions
- L2326 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitRightDirectionWeights;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Optional array of weights to use for the fit right directions
- L2330 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameAttributeFunction>> FitUpDirectionWeights;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Optional array of weights to use for the fit up directions
- L2334 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_BoneGlobalTransform`  
`class UAnimDatabaseFrameAttributeFunction_BoneGlobalTransform : public UAnimDatabaseFrameAttributeFunction`  
_L2339-2356_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Global Transform Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bone global transform attribute
- L2347 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the transform of
- L2351 _public member_ `FTransform LocalOffset = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local offset transform
- L2355 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_BoneRelativeTransform`  
`class UAnimDatabaseFrameAttributeFunction_BoneRelativeTransform : public UAnimDatabaseFrameAttributeFunction`  
_L2360-2377_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Relative Transform Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bone global transform attribute relative to another
- L2368 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the transform of
- L2372 _public member_ `FName RelativeBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the transform relative to
- L2376 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_BoneRelativeAngularVelocity`  
`class UAnimDatabaseFrameAttributeFunction_BoneRelativeAngularVelocity : public UAnimDatabaseFrameAttributeFunction`  
_L2381-2398_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Relative Angular Velocity Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bone global angular velocity attribute relative to another
- L2389 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the angular velocity of
- L2393 _public member_ `FName RelativeBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the angular velocity relative to
- L2397 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_BoneGlobalLocation`  
`class UAnimDatabaseFrameAttributeFunction_BoneGlobalLocation : public UAnimDatabaseFrameAttributeFunction`  
_L2402-2419_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Global Location Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bone global location attribute
- L2410 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the location of
- L2414 _public member_ `FVector LocalOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local offset vector
- L2418 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_BoneGlobalDirection`  
`class UAnimDatabaseFrameAttributeFunction_BoneGlobalDirection : public UAnimDatabaseFrameAttributeFunction`  
_L2423-2440_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Global Direction Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bone global direction attribute
- L2431 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the direction of
- L2435 _public member_ `FVector LocalDirection = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local direction vector
- L2439 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_BoneGlobalLinearVelocityMagnitude`  
`class UAnimDatabaseFrameAttributeFunction_BoneGlobalLinearVelocityMagnitude : public UAnimDatabaseFrameAttributeFunction`  
_L2444-2457_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bone Global Linear Velocity Magnitude Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Computes a bone velocity magnitude attribute
- L2452 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the bone to compute the velocity magnitude for
- L2456 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameAttributeFunction_GaussianSmoothingFilter`  
`class UAnimDatabaseFrameAttributeFunction_GaussianSmoothingFilter : public UAnimDatabaseFrameAttributeFunction`  
_L2461-2478_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Gaussian Smoothing Filter Frame Attribute"))`
- inherits: `UAnimDatabaseFrameAttributeFunction`
- desc: Filter a frame attribute using a gaussian smoothing filter
- L2469 _public member_ `TObjectPtr<UAnimDatabaseFrameAttributeFunction> FilterFrameAttribute;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame attribute to filter
- L2473 _public member_ `float StandardDeviation = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(ForceUnits="s"))` — Standard Deviation (in seconds) for the gaussian smoothing filter.
- L2477 _public prototype_ `virtual FAnimDatabaseFrameAttribute MakeFrameAttribute_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_MajorityVoteFilter`  
`class UAnimDatabaseFrameRangesFunction_MajorityVoteFilter : public UAnimDatabaseFrameRangesFunction`  
_L2482-2501_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Majority Vote Filter Frame Attribute"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Filter frame ranges with a majority vote filter
- L2490 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FilterFrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Frame ranges to filter
- L2496 _public member_ `int32 MajorityVoteFilterWidth = 15;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Filter width (in frames) for the majority vote filter used to remove very short frame ranges less than half this duration will be removed.
- L2500 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_MovingInDirection`  
`class UAnimDatabaseFrameRangesFunction_MovingInDirection : public UAnimDatabaseFrameRangesFunction`  
_L2505-2526_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Moving in Direction Frame Attribute"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Frame ranges where the character is moving in the given direction
- L2513 _public member_ `FVector Direction = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local direction to check if the character is moving in
- L2517 _public member_ `float VelocityThreshold = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Character is only considered moving when the velocity is above this threshold
- L2521 _public member_ `float AngleThreshold = 45.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "deg"))` — Character is considered moving in the direction when the angle between the velocity direction and the specified direction is less than this
- L2525 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_RootLinearVelocityBelowThreshold`  
`class UAnimDatabaseFrameRangesFunction_RootLinearVelocityBelowThreshold : public UAnimDatabaseFrameRangesFunction`  
_L2530-2542_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Root Linear Velocity Below Threshold Frame Attribute"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Frame ranges where the root linear velocity magnitude is below some threshold
- L2537 _public member_ `float Threshold = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))`
- L2541 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_RootLinearVelocityAboveThreshold`  
`class UAnimDatabaseFrameRangesFunction_RootLinearVelocityAboveThreshold : public UAnimDatabaseFrameRangesFunction`  
_L2546-2558_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Root Linear Velocity Above Threshold Frame Attribute"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Frame ranges where the root linear velocity magnitude is above some threshold
- L2553 _public member_ `float Threshold = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))`
- L2557 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### struct `FAnimDatabaseFrameAttributeEntry`  
`struct FAnimDatabaseFrameAttributeEntry`  
_L2562-2575_
- reflection: `USTRUCT(BlueprintType)`
- desc: Entry specifying a frame attribute function
- L2570 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Frame Attribute name
- L2574 _public member_ `TObjectPtr<UAnimDatabaseFrameAttributeFunction> FrameAttribute;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Frame Attribute function

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMDATABASE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Learning` (scope `UE`)
- L138 _prototype_ `bool operator==(const FAnimDatabaseFrameAttribute& Lhs, const FAnimDatabaseFrameAttribute& Rhs);`
- L145 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon984a22c20103`)
- L146 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon984a22c20103`)
- L2577 _prototype_ `bool operator==(const FAnimDatabaseFrameAttributeEntry& Lhs, const FAnimDatabaseFrameAttributeEntry& Rhs);`

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Public/AnimDatabaseFrameRanges.h` (Public)


#### struct `FAnimDatabaseFrames`  
`struct FAnimDatabaseFrames`  
_L39-51_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a set of frames within a UAnimDatabase. Internally, this is effectively a thin blueprint wrapper around the UE::Learning::FFrameSet data structure. Below we provide a Blueprint Function Library that allows for the construction, modification and scripting of these objects in blueprints, but if you want to handle them in C++ at a low level if you should access the internal FrameSet object directly. It is assumed that all FrameSet objects used by this wrapper are stored at the FrameRate of the database they were created from.
- L44 _public prototype_ `bool IsValid() const;` — Checks if the given FrameSet is valid (i.e. the shared pointer is not null)
- L47 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L50 _public member_ `TSharedPtr<UE::Learning::FFrameSet, ESPMode::ThreadSafe> FrameSet;` — Shared pointer to the actual FrameSet data structure

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimDatabaseFrames> : TStructOpsTypeTraitsBase2<FAnimDatabaseFrames>`  
_L56-63_
- inherits: `TStructOpsTypeTraitsBase2<FAnimDatabaseFrames>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L59-62_

#### struct `FAnimDatabaseFrameRanges`  
`struct FAnimDatabaseFrameRanges`  
_L75-87_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a set of frame ranges within a UAnimDatabase. Internally, this is effectively a thin blueprint wrapper around the UE::Learning::FFrameRangeSet data structure. Below we provide a Blueprint Function Library that allows for the construction, modification and scripting of these objects in blueprints, but if you want to handle them in C++ at a low level if you can also access the internal FrameRangeSet object directly. It is assumed that all FrameRangeSet objects used by this wrapper are stored at the FrameRate of the database they were created from.
- L80 _public prototype_ `bool IsValid() const;` — Checks if the given FrameRangeSet is valid (i.e. the shared pointer is not null)
- L83 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L86 _public member_ `TSharedPtr<UE::Learning::FFrameRangeSet, ESPMode::ThreadSafe> FrameRangeSet;` — Shared pointer to the actual FrameRangeSet data structure

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimDatabaseFrameRanges> : TStructOpsTypeTraitsBase2<FAnimDatabaseFrameRanges>`  
_L92-99_
- inherits: `TStructOpsTypeTraitsBase2<FAnimDatabaseFrameRanges>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L95-98_

#### enum `EAnimDatabaseFrameShiftBehavior`  
`enum class EAnimDatabaseFrameShiftBehavior : uint8`  
_L102-108_
- reflection: `UENUM(BlueprintType)`
- L105 _public enumerator_ `Remove = 0` — Remove frames which are shifted to beyond the start or end of an anim sequence
- L107 _public enumerator_ `Clamp = 1` — Clamp frames which are shifted to beyond the start or end of an anim sequence to the start or end

#### class `UAnimDatabaseFramesLibrary`  
`class UAnimDatabaseFramesLibrary : public UBlueprintFunctionLibrary`  
_L111-220_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- L119 _public prototype_ `static FAnimDatabaseFrames MakeEmptyFrames();` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make an empty set of Frames
- L123 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromFunction(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const UAnimDatabaseFramesFunction* Function);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames using the given function
- L127 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromClass(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimDatabaseFramesFunction> Class);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames using the given class
- L131 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromAnimNotify(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotify> Notify);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames from the times given by all the instances of the given AnimNotify class in the database
- L135 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromAnimNotifiesOnTrack(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName TrackName);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames from the times given by all the instances of AnimNotifies in the database that are on a track with the given name
- L139 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromSyncMarker(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName SyncMarkerName);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames from the times given by all the instances of the given SyncMarker in the database
- L143 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromAnimNotifyStateStart(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> State);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames from the start times of all the instances of the given UAnimNotifyState class in the database
- L147 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromAnimNotifyStateEnd(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> State);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames from the end times of all the instances of the given UAnimNotifyState class in the database
- L151 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromAnimNotifyUnion(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<TSubclassOf<UAnimNotify>>& Notifies);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames from all of the given anim notifies
- L152 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromAnimNotifyArrayViewUnion(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const TSubclassOf<UAnimNotify>> Notifies);`
- L156 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromSequenceAndTime(const UAnimDatabase* Database, const int32 SequenceIdx, const float Time);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe))` — Make a set of Frames consisting of a single frame from the given Sequence Index in the Database, at the given time
- L162 _public prototype_ `static FAnimDatabaseFrames FramesNone();` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "NONE"))` — Makes an empty set of frames. (This is the same as MakeEmptyFrames).
- L166 _public prototype_ `static bool FramesIsEmpty(const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Check if the given set is empty
- L170 _public prototype_ `static FAnimDatabaseFrames FramesBefore(const UAnimDatabase* Database, const FAnimDatabaseFrames& Frames, const int32 FramesBefore, const EAnimDatabaseFrameShiftBehavior ShiftBehavior = EAnimDatabaseFrameShiftBehavior::Remove);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, CompactNodeTitle = "BEFORE"))` — Make a set of Frames at a given number of frames before another set of frames. Will use ShiftBehavior to decided if to clamp or discard frames that fall out of the valid sequence range.
- L174 _public prototype_ `static FAnimDatabaseFrames FramesAfter(const UAnimDatabase* Database, const FAnimDatabaseFrames& Frames, const int32 FramesAfter, const EAnimDatabaseFrameShiftBehavior ShiftBehavior = EAnimDatabaseFrameShiftBehavior::Remove);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (NotBlueprintThreadSafe, CompactNodeTitle = "AFTER"))` — Make a set of Frames at a given number of frames after another set of frames. Will use ShiftBehavior to decided if to clamp or discard frames that fall out of the valid sequence range.
- L178 _public prototype_ `static bool FramesEqual(const FAnimDatabaseFrames& A, const FAnimDatabaseFrames& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "EQUAL"))` — Checks if two sets of Frames are equal
- L182 _public prototype_ `static FAnimDatabaseFrames FramesUnion(FAnimDatabaseFrames A, FAnimDatabaseFrames B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "UNION"))` — Computes the union of two sets of Frames
- L186 _public prototype_ `static FAnimDatabaseFrames FramesIntersection(FAnimDatabaseFrames A, FAnimDatabaseFrames B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "INTERSECTION"))` — Computes the intersection of two sets of Frames
- L190 _public prototype_ `static FAnimDatabaseFrames FramesDifference(FAnimDatabaseFrames A, FAnimDatabaseFrames B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "DIFFERENCE"))` — Computes the difference of two sets of Frames
- L194 _public prototype_ `static FAnimDatabaseFrames FramesUnionFromArray(const TArray<FAnimDatabaseFrames>& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "UNION"))` — Computes the union of an array of Frames objects
- L197 _public prototype_ `static FAnimDatabaseFrames FramesUnionFromArrayView(const TArrayView<const FAnimDatabaseFrames> Frames);` — Computes the union of an array of Frames objects using an array view
- L201 _public prototype_ `static FAnimDatabaseFrames FramesIntersectionFromArray(const TArray<FAnimDatabaseFrames>& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "INTERSECTION"))` — Computes the intersection of an array of Frames objects
- L204 _public prototype_ `static FAnimDatabaseFrames FramesIntersectionFromArrayView(const TArrayView<const FAnimDatabaseFrames> Frames);` — Computes the intersection of an array of Frames objects using an array view
- L208 _public prototype_ `static FAnimDatabaseFrames FramesDifferenceFromArray(const TArray<FAnimDatabaseFrames>& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "DIFFERENCE"))` — Computes the difference of an array of Frames objects
- L211 _public prototype_ `static FAnimDatabaseFrames FramesDifferenceFromArrayView(const TArrayView<const FAnimDatabaseFrames> Frames);` — Computes the difference of an array of Frames objects using an array view
- L215 _public prototype_ `static FString FramesToString(const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "Frames", Keywords = "Print,Log,Display,Name"))` — Converts a Frames object to a string.
- L219 _public prototype_ `static FString FramesToStringFormat(const UAnimDatabase* Database, const FAnimDatabaseFrames& Frames, const int32 Cutoff = 11);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (Keywords = "Print,Log,Display,Name"))` — Converts a Frames object to a string object in full.

#### class `UAnimDatabaseFramesFunction`  
`class UAnimDatabaseFramesFunction : public UObject`  
_L224-233_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: A simple class that has a single implementable function which constructs a FAnimDatabaseFrames object from a UAnimDatabase.
- L232 _public prototype_ `FAnimDatabaseFrames MakeFrames(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimDatabase")` — Callback that constructs a Frames set from a UAnimDatabase

#### class `UAnimDatabaseFramesFunction_Empty`  
`class UAnimDatabaseFramesFunction_Empty : public UAnimDatabaseFramesFunction`  
_L237-244_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Empty Frames"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Returns the empty set of Frames
- L243 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFramesFunction_AnimNotify`  
`class UAnimDatabaseFramesFunction_AnimNotify : public UAnimDatabaseFramesFunction`  
_L248-260_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify Frames"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Finds all the frames for a given Anim Notify Class
- L255 _public member_ `TSubclassOf<UAnimNotify> AnimNotify;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L259 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFramesFunction_AnimNotifiesOnTrack`  
`class UAnimDatabaseFramesFunction_AnimNotifiesOnTrack : public UAnimDatabaseFramesFunction`  
_L264-276_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notifies on Track Frames"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Finds all the frames for all Anim Notifies on a given track
- L271 _public member_ `FName TrackName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L275 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFramesFunction_SyncMarker`  
`class UAnimDatabaseFramesFunction_SyncMarker : public UAnimDatabaseFramesFunction`  
_L280-292_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Sync Marker Frames"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Finds all the frames for a given Sync Marker
- L287 _public member_ `FName SyncMarker = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L291 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFramesFunction_FrameRangeStarts`  
`class UAnimDatabaseFramesFunction_FrameRangeStarts : public UAnimDatabaseFramesFunction`  
_L296-308_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Frame Range Start Frames"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Finds all the frames at the start of the given frame ranges
- L303 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L307 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFramesFunction_FrameRangeEnds`  
`class UAnimDatabaseFramesFunction_FrameRangeEnds : public UAnimDatabaseFramesFunction`  
_L312-324_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Frame Range End Frames"))`
- inherits: `UAnimDatabaseFramesFunction`
- desc: Finds all the frames at the end of the given frame ranges
- L319 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L323 _public prototype_ `virtual FAnimDatabaseFrames MakeFrames_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### struct `FAnimDatabaseFramesEntry`  
`struct FAnimDatabaseFramesEntry`  
_L328-341_
- reflection: `USTRUCT(BlueprintType)`
- desc: Entry specifying a frames function
- L336 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Frames name
- L340 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> Frames;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Frames function

#### struct `FAnimDatabaseFrameRangesStatistics`  
`struct FAnimDatabaseFrameRangesStatistics`  
_L347-398_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains various statistics about a set of ranges within the UAnimDatabase
- L353 _public member_ `float DiskSize = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Kilobytes"))` — Approximate size of the animation data in the ranges on disk in kilobytes. Will only count mirrored data once.
- L357 _public member_ `float UncompressedSize = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Kilobytes"))` — Approximate size of the uncompressed animation data in the ranges in kilobytes. Will only count mirrored data once.
- L361 _public member_ `float CompressedSize = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Kilobytes"))` — Approximate size of the compressed animation data in the ranges in kilobytes. Will only count mirrored data once.
- L365 _public member_ `int32 TotalRangeNum = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics")` — The total number of ranges
- L369 _public member_ `int32 TotalSequenceNum = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics")` — The total number of unique sequences. Mirrored sequences are counted as a unique sequence.
- L373 _public member_ `int32 TotalFrameNum = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics")` — The total number of frames in the given ranges
- L377 _public member_ `float TotalDuration = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Seconds"))` — The total duration of animation in the ranges in seconds
- L381 _public member_ `float AverageRangeDuration = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Seconds"))` — The average duration of a ranges in seconds
- L385 _public member_ `float MinimumRangeDuration = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Seconds"))` — The minimum duration from the ranges in seconds
- L389 _public member_ `float MaximumRangeDuration = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (Units = "Seconds"))` — The maximum duration from the ranges in seconds
- L393 _public member_ `TArray<TSubclassOf<UAnimNotify>> AnimNotifies;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics")` — Anim Notifies contained within range
- L397 _public member_ `TArray<TSubclassOf<UAnimNotifyState>> AnimNotifyStates;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics")` — Anim Notify States contained within range

#### class `UAnimDatabaseFrameRangesLibrary`  
`class UAnimDatabaseFrameRangesLibrary : public UBlueprintFunctionLibrary`  
_L401-776_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- L409 _public prototype_ `static FAnimDatabaseFrameRanges MakeEmptyFrameRanges();` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make an empty set of FrameRanges
- L413 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromDatabase(const UAnimDatabase* Database);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (BlueprintAutocast, CompactNodeTitle = "->"))` — Make a set of FrameRanges for all animations in a database
- L417 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromNotMirrored(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the non-mirrored animations in a set of frame ranges
- L421 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromMirrored(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the mirrored animations in a set of frame ranges
- L425 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromRootMotionEnabled(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the animations with root motion enabled in a set of frame ranges
- L429 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromRootMotionDisabled(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the animations with root motion disabled in a set of frame ranges
- L433 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromForceRootLockEnabled(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the animations with force root lock enabled in a set of frame ranges
- L437 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromForceRootLockDisabled(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the animations with force root lock disabled in a set of frame ranges
- L441 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromNotLooped(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the animations which are not looped in a set of frame ranges
- L445 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromLooped(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for just the animations which are looped in a set of frame ranges
- L449 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromSequenceIndex(const UAnimDatabase* Database, const int32 SequenceIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for a single sequence in a database
- L453 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromSequenceRange(const UAnimDatabase* Database, const int32 SequenceIdx, const int32 RangeStart, const int32 RangeLength);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for a single range in a sequence in a database
- L457 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimSequence(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for a given anim sequence in a database
- L461 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimSequences(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<UAnimSequence*>& AnimSequences);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for a given anim sequence in a database
- L462 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimSequencesArrayView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<UAnimSequence* const> AnimSequences);`
- L466 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetName(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FString& AssetName);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences with a matching asset name in a set of frame ranges
- L467 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameStringView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FStringView AssetName);`
- L471 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameStartsWith(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FString& Prefix);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences with the given string as a prefix in their asset name
- L472 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameStartsWithStringView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FStringView Prefix);`
- L476 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameEndsWith(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FString& Suffix);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences with the given string as a suffix in their asset name
- L477 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameEndsWithStringView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FStringView Suffix);`
- L481 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameContains(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FString& Substring);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences with the given string contained in their asset name
- L482 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameContainsStringView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FStringView Substring);`
- L486 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameStartsWithOneOf(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FString>& Prefixes);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences where the asset name starts with any of the given prefixes
- L487 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameStartsWithOneOfArrayView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FString> Prefixes);`
- L491 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameEndsWithOneOf(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FString>& Suffixes);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences where the asset name ends with any of the given suffixes
- L492 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameEndsWithOneOfArrayView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FString> Suffixes);`
- L496 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameContainsOneOf(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FString>& Substrings);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences where the asset name contains any of the given strings
- L497 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetNameContainsOneOfArrayView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FString> Substrings);`
- L501 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetPackageContains(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FString& Substring);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences where the package name contains the given substring
- L502 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetPackageContainsStringView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FStringView Substring);`
- L506 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetPackageContainsOneOf(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<FString>& Substring);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all sequences where the package name contains any of the given substrings
- L507 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAssetPackageContainsOneOfArrayView(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FString> Substrings);`
- L511 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromSequences(const UAnimDatabase* Database, const TArray<UAnimSequence*>& AnimSequences);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for out of all the given anim sequences
- L512 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromSequencesArrayView(const UAnimDatabase* Database, const TArrayView<UAnimSequence* const> AnimSequences);`
- L516 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromFunction(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const UAnimDatabaseFrameRangesFunction* Function);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges using the given UAnimDatabaseFrameRangesFunction object
- L520 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromClass(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimDatabaseFrameRangesFunction> Class);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges using the given UAnimDatabaseFrameRangesFunction class
- L524 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotifyState(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> State);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges with ranges specified by the given anim notify state
- L528 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotifyStateNotActive(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotifyState> State);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges with ranges specified by when the given anim notify state is not active
- L532 _public prototype_ `static void MakeFrameRangesFromAnimNotifyStates(TArray<FAnimDatabaseFrameRanges>& OutFrameRanges, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<TSubclassOf<UAnimNotifyState>>& States);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make several FrameRanges with ranges specified by the given anim notify states
- L533 _public prototype_ `static void MakeFrameRangesFromAnimNotifyStatesToArrayView(const TArrayView<FAnimDatabaseFrameRanges> OutFrameRanges, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const TSubclassOf<UAnimNotifyState>> States);`
- L537 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotifyStatesUnion(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<TSubclassOf<UAnimNotifyState>>& States);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges with ranges specified by any of the given anim notify states
- L538 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotifyStatesArrayViewUnion(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const TSubclassOf<UAnimNotifyState>> States);`
- L542 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotifyStatesIntersection(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<TSubclassOf<UAnimNotifyState>>& States);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges with ranges specified by all of the given anim notify states
- L543 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotifyStatesArrayViewIntersection(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const TSubclassOf<UAnimNotifyState>> States);`
- L547 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromFrames(const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta=(BlueprintAutocast, CompactNodeTitle = "->"))` — Make a set of single frame FrameRanges from the given frames
- L551 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAfterFrames(const FAnimDatabaseFrameRanges& FrameRanges, const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all the frames after a given set of frames
- L555 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromBeforeFrames(const FAnimDatabaseFrameRanges& FrameRanges, const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of FrameRanges for all the frames before a given set of frames
- L559 _public prototype_ `static FAnimDatabaseFrames MakeFramesAtFrameRangesStarts(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of Frames from all the start frames of a given FrameRanges set
- L563 _public prototype_ `static FAnimDatabaseFrames MakeFramesAtFrameRangesEnds(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of Frames from all the end frames of a given FrameRanges set
- L567 _public prototype_ `static FAnimDatabaseFrames MakeFramesFromFrameRangesInterval(const FAnimDatabaseFrameRanges& FrameRanges, const int32 IntervalFrames = 10);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of Frames from the given FrameRanges set sampling frames at a regular interval
- L571 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromAnimNotify(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TSubclassOf<UAnimNotify> Notify);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of single frame FrameRanges from the given anim notify
- L575 _public prototype_ `static FAnimDatabaseFrameRanges MakeFrameRangesFromSyncMarker(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName SyncMarkerName);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Make a set of single frame FrameRanges from the given sync marker
- L582 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesNone();` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "NONE"))` — Makes an empty set of frame ranges. (This is the same as MakeEmptyFrameRanges).
- L586 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesAll(const UAnimDatabase* Database);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "ALL"))` — Make a set of frame ranges for all the data in a database. (This is the same as MakeFrameRangesFromDatabase).
- L590 _public prototype_ `static bool FrameRangesIsEmpty(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Check if a given set of frame ranges is empty
- L594 _public prototype_ `static bool FrameRangesEqual(const FAnimDatabaseFrameRanges& A, const FAnimDatabaseFrameRanges& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "EQUAL"))` — Check if two sets of frame ranges are equal
- L598 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesUnion(FAnimDatabaseFrameRanges A, FAnimDatabaseFrameRanges B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "UNION"))` — Returns the union of one or more frame range sets
- L602 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesIntersection(FAnimDatabaseFrameRanges A, FAnimDatabaseFrameRanges B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "INTERSECTION"))` — Returns the intersection of one or more frame range sets
- L606 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesDifference(FAnimDatabaseFrameRanges A, FAnimDatabaseFrameRanges B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CommutativeAssociativeBinaryOperator, CompactNodeTitle = "DIFFERENCE"))` — Returns the difference of one or more frame range sets
- L610 _public prototype_ `static FAnimDatabaseFrameRanges FramesFrameRangesUnion(const FAnimDatabaseFrames& Frames, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "UNION"))` — Returns the union of a set of frames and a set of frame ranges
- L614 _public prototype_ `static FAnimDatabaseFrames FramesFrameRangesIntersection(const FAnimDatabaseFrames& Frames, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "INTERSECTION"))` — Returns the intersection of a set of frames and a set of frame ranges
- L618 _public prototype_ `static FAnimDatabaseFrames FramesFrameRangesDifference(const FAnimDatabaseFrames& Frames, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "DIFFERENCE"))` — Returns the difference of a set of frames and a set of frame ranges
- L622 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesFramesDifference(const FAnimDatabaseFrameRanges& FrameRanges, const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "DIFFERENCE"))` — Returns the difference of a set of frame ranges and a set of frames
- L626 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesUnionFromArray(const TArray<FAnimDatabaseFrameRanges>& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "UNION"))` — Returns the union of multiple frame ranges
- L627 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesUnionFromArrayView(const TArrayView<const FAnimDatabaseFrameRanges> FrameRanges);`
- L631 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesIntersectionFromArray(const TArray<FAnimDatabaseFrameRanges>& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "INTERSECTION"))` — Returns the intersection of multiple frame ranges
- L632 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesIntersectionFromArrayView(const TArrayView<const FAnimDatabaseFrameRanges> FrameRanges);`
- L636 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesDifferenceFromArray(const TArray<FAnimDatabaseFrameRanges>& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "DIFFERENCE"))` — Returns the difference of multiple frame ranges
- L637 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesDifferenceFromArrayView(const TArrayView<const FAnimDatabaseFrameRanges> FrameRanges);`
- L641 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesNot(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "NOT"))` — Returns all the frame ranges in the data minus the given set of frame ranges.
- L645 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesBounds(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "BOUNDS"))` — Returns the frame ranges that bound the given frame ranges in each sequence
- L649 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesBoundsFrames(const FAnimDatabaseFrames& Frames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "BOUNDS"))` — Returns the frame ranges that bound the given frames in each sequence
- L653 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesIntersects(const FAnimDatabaseFrameRanges& A, const FAnimDatabaseFrameRanges& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "INTERSECTS"))` — Returns all the frame ranges from A which contain any part of the frame ranges from B
- L657 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesIntersectsFrames(const FAnimDatabaseFrameRanges& A, const FAnimDatabaseFrames& B);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "INTERSECTS"))` — Returns all the frame ranges from A which contain any part of the frames from B
- L661 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesTrim(const FAnimDatabaseFrameRanges& A, const int32 TrimStartFrames, const int32 TrimEndFrames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "TRIM"))` — Return a set of frame ranges with the given amount of frames trimmed from either end. Ranges shorter than the combined TrimStartFrames + TrimEndFrames will be removed.
- L665 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesTrimStart(const FAnimDatabaseFrameRanges& A, const int32 TrimFrames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "TRIM START"))` — Return a set of frame ranges with the given amount of frames trimmed from the beginning. Ranges shorter than the TrimFrames will be removed.
- L669 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesTrimEnd(const FAnimDatabaseFrameRanges& A, const int32 TrimFrames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "TRIM END"))` — Return a set of frame ranges with the given amount of frames trimmed from the end. Ranges shorter than the TrimFrames will be removed.
- L673 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesPad(const FAnimDatabaseFrameRanges& A, const int32 PadStartFrames, const int32 PadEndFrames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "PAD"))` — Return a set of frame ranges with the given amount of frames added to either end. Will merge ranges if this causes overlaps.
- L677 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesPadStart(const FAnimDatabaseFrameRanges& A, const int32 PadFrames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "PAD START"))` — Return a set of frame ranges with the given amount of frames added to the beginning. Will merge ranges if this causes overlaps.
- L681 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesPadEnd(const FAnimDatabaseFrameRanges& A, const int32 PadFrames);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (CompactNodeTitle = "PAD END"))` — Return a set of frame ranges with the given amount of frames added to the end. Will merge ranges if this causes overlaps.
- L685 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesGatherRanges(const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& RangeIndices);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns a set of frame ranges with just the ranges of the given indices.
- L686 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesGatherRangesFromIndexSet(const FAnimDatabaseFrameRanges& FrameRanges, const UE::Learning::FIndexSet RangeIndices);`
- L690 _public prototype_ `static void FrameRangesAnimSequences(TArray<UAnimSequence*>& OutAnimSequences, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets all the anim sequences included in a given set of frame ranges
- L694 _public prototype_ `static void FrameRangesAnimSequenceAssets(TArray<UAnimSequence*>& OutAnimSequenceAssets, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets all the anim sequence assets included in a given set of frame ranges
- L698 _public prototype_ `static void FrameRangesStatistics(FAnimDatabaseFrameRangesStatistics& OutStatistics, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes various useful statistics for a given set of frame ranges
- L705 _public prototype_ `static int32 FrameRangesContentHash(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Computes a hash representing the contents of a set of frame ranges in a database. This hash is not strong, so should not be relied on for critical purposes, but can be used to detect data changes for things such as displaying warnings in UIs.
- L709 _public prototype_ `static bool FrameRangesContainsSequence(const FAnimDatabaseFrameRanges& FrameRanges, const int32 SequenceIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Check if a set of frame ranges contains the given sequence
- L713 _public prototype_ `static bool FrameRangesContains(const FAnimDatabaseFrameRanges& FrameRanges, const int32 SequenceIdx, const int32 FrameIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Check if a set of frame ranges contains the given sequence and frame
- L717 _public prototype_ `static bool FrameRangesContainsTime(const FAnimDatabaseFrameRanges& FrameRanges, const int32 SequenceIdx, const float SequenceTime, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Check if a set of frame ranges contains the given sequence and time
- L723 _public prototype_ `static int32 FrameRangesTotalRangeNum(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns the total number of ranges in a set of frame ranges
- L727 _public prototype_ `static int32 FrameRangesTotalFrameNum(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns the total number of frames in a set of frame ranges
- L731 _public prototype_ `static float FrameRangesAverageFrameNum(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns the average number of frames in a set of frame ranges
- L735 _public prototype_ `static int32 FrameRangesMinFrameNum(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns the smallest number of frames in a set of frame ranges
- L739 _public prototype_ `static int32 FrameRangesMaxFrameNum(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns the largest number of frames in a set of frame ranges
- L743 _public prototype_ `static FAnimDatabaseFrameRanges FrameRangesRangeAtIndex(const FAnimDatabaseFrameRanges& FrameRanges, const int32 RangeIdx);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Returns a single frame range from a set of frame ranges for the given index
- L749 _public prototype_ `static FString FrameRangesToString(const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "FrameRanges", Keywords = "Print,Log,Display,Name"))` — Converts a FrameRanges object to a string.
- L753 _public prototype_ `static FString FrameRangesToStringFormat(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 Cutoff = 11);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta=(Keywords = "Print,Log,Display,Name"))` — Converts a FrameRanges object to a string object in full.
- L759 _public prototype_ `static void FindAnimNotifyClassesInFrameRanges(TArray<TSubclassOf<UAnimNotify>>& OutAnimNotifyClasses, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds all of the Anim Notify Classes in the given frame ranges
- L763 _public prototype_ `static void FindAnimNotifyStateClassesInFrameRanges(TArray<TSubclassOf<UAnimNotifyState>>& OutAnimNotifyStateClasses, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds all of the Anim Notify State Classes in the given frame ranges
- L767 _public prototype_ `static void FindCurvesInFrameRanges(TArray<FName>& OutCurves, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds all of the Curves present in the given frame ranges
- L771 _public prototype_ `static void FindSyncMarkersInFrameRanges(TArray<FName>& SyncMarkers, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Finds all of the sync markers which are present in the given frame ranges
- L775 _public prototype_ `static void FindAllAnimNotifyStateClasses(TArray<TSubclassOf<UAnimNotifyState>>& OutClasses, const TSubclassOf<UAnimNotifyState> BaseClass);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta=(BaseClass = "/Script/Engine.AnimNotifyState"))` — Finds all of the AnimNotifyState Classes which are subclasses of the given base class (exclusive). Only returns classes loaded in memory.

#### class `UAnimDatabaseFrameRangesFunction`  
`class UAnimDatabaseFrameRangesFunction : public UObject`  
_L780-789_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: A simple class that has a single implementable function which constructs a FAnimDatabaseFrameRanges object from a UAnimDatabase.
- L788 _public prototype_ `FAnimDatabaseFrameRanges MakeFrameRanges(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimDatabase")` — Callback that constructs a FrameRanges set from a UAnimDatabase

#### class `UAnimDatabaseFrameRangesFunction_Empty`  
`class UAnimDatabaseFrameRangesFunction_Empty : public UAnimDatabaseFrameRangesFunction`  
_L793-800_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Empty Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Returns the empty set of frame ranges
- L799 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Identity`  
`class UAnimDatabaseFrameRangesFunction_Identity : public UAnimDatabaseFrameRangesFunction`  
_L804-811_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Identity Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Returns the Frame Ranges given as input
- L810 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Frames`  
`class UAnimDatabaseFrameRangesFunction_Frames : public UAnimDatabaseFrameRangesFunction`  
_L815-825_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Frames Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Returns the Frame Ranges given by a set of frames
- L820 _private member_ `TObjectPtr<UAnimDatabaseFramesFunction> Frames;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L824 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_All`  
`class UAnimDatabaseFrameRangesFunction_All : public UAnimDatabaseFrameRangesFunction`  
_L829-836_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "All Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Ignores the frames given as input and returns all the frame ranges in the database
- L835 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Mirrored`  
`class UAnimDatabaseFrameRangesFunction_Mirrored : public UAnimDatabaseFrameRangesFunction`  
_L840-847_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Mirrored Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that are mirrored
- L846 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_NotMirrored`  
`class UAnimDatabaseFrameRangesFunction_NotMirrored : public UAnimDatabaseFrameRangesFunction`  
_L851-858_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Not Mirrored Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that are not mirrored
- L857 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_RootMotionEnabled`  
`class UAnimDatabaseFrameRangesFunction_RootMotionEnabled : public UAnimDatabaseFrameRangesFunction`  
_L862-869_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Root Motion Enabled Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that have root motion enabled
- L868 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_RootMotionDisabled`  
`class UAnimDatabaseFrameRangesFunction_RootMotionDisabled : public UAnimDatabaseFrameRangesFunction`  
_L873-880_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Root Motion Disabled Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that have root motion disabled
- L879 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_ForceRootLockEnabled`  
`class UAnimDatabaseFrameRangesFunction_ForceRootLockEnabled : public UAnimDatabaseFrameRangesFunction`  
_L884-891_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Force Root Lock Enabled Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that have force root lock enabled
- L890 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_ForceRootLockDisabled`  
`class UAnimDatabaseFrameRangesFunction_ForceRootLockDisabled : public UAnimDatabaseFrameRangesFunction`  
_L895-902_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Force Root Lock Disabled Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that have force root lock disabled
- L901 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Looped`  
`class UAnimDatabaseFrameRangesFunction_Looped : public UAnimDatabaseFrameRangesFunction`  
_L906-913_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Looped Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that are looped
- L912 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_NotLooped`  
`class UAnimDatabaseFrameRangesFunction_NotLooped : public UAnimDatabaseFrameRangesFunction`  
_L917-924_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Not Looped Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that are not looped
- L923 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimSequence`  
`class UAnimDatabaseFrameRangesFunction_AnimSequence : public UAnimDatabaseFrameRangesFunction`  
_L928-940_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Sequence Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges corresponding to the given Anim Sequence
- L935 _public member_ `TObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L939 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimSequences`  
`class UAnimDatabaseFrameRangesFunction_AnimSequences : public UAnimDatabaseFrameRangesFunction`  
_L944-956_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Sequences Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges corresponding to the given Anim Sequences
- L951 _public member_ `TArray<TObjectPtr<UAnimSequence>> AnimSequences;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L955 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimNotify`  
`class UAnimDatabaseFrameRangesFunction_AnimNotify : public UAnimDatabaseFrameRangesFunction`  
_L960-972_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with a given Anim Notify Class
- L967 _public member_ `TSubclassOf<UAnimNotify> AnimNotify;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L971 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_SyncMarker`  
`class UAnimDatabaseFrameRangesFunction_SyncMarker : public UAnimDatabaseFrameRangesFunction`  
_L976-988_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Sync Marker Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with a given Sync Marker
- L983 _public member_ `FName SyncMarker = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L987 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimNotifyState`  
`class UAnimDatabaseFrameRangesFunction_AnimNotifyState : public UAnimDatabaseFrameRangesFunction`  
_L992-1004_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify State Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with a given Anim Notify State Class
- L999 _public member_ `TSubclassOf<UAnimNotifyState> AnimNotifyState;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1003 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimNotifyStateNotActive`  
`class UAnimDatabaseFrameRangesFunction_AnimNotifyStateNotActive : public UAnimDatabaseFrameRangesFunction`  
_L1008-1020_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify State Not Active Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which do not have the given Anim Notify State Class active
- L1015 _public member_ `TSubclassOf<UAnimNotifyState> AnimNotifyState;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1019 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimNotifyStateUnion`  
`class UAnimDatabaseFrameRangesFunction_AnimNotifyStateUnion : public UAnimDatabaseFrameRangesFunction`  
_L1024-1036_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify State Union Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with any of the given Anim Notify State Classes
- L1031 _public member_ `TArray<TSubclassOf<UAnimNotifyState>> AnimNotifyStates;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1035 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimNotifyStateIntersection`  
`class UAnimDatabaseFrameRangesFunction_AnimNotifyStateIntersection : public UAnimDatabaseFrameRangesFunction`  
_L1040-1052_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify State Intersection Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with all of the given Anim Notify State Classes
- L1047 _public member_ `TArray<TSubclassOf<UAnimNotifyState>> AnimNotifyStates;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1051 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AnimNotifyStateWithMirrored`  
`class UAnimDatabaseFrameRangesFunction_AnimNotifyStateWithMirrored : public UAnimDatabaseFrameRangesFunction`  
_L1056-1071_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Anim Notify State with Mirrored Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with a given Anim Notify State classes for mirrored and un-mirrored sequences
- L1063 _public member_ `TSubclassOf<UAnimNotifyState> NotMirroredAnimNotifyState;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1066 _public member_ `TSubclassOf<UAnimNotifyState> MirroredAnimNotifyState;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1070 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetNameContains`  
`class UAnimDatabaseFrameRangesFunction_AssetNameContains : public UAnimDatabaseFrameRangesFunction`  
_L1075-1087_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Name Contains Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with the given sub-string in the name
- L1082 _public member_ `FString AssetNameSubstring;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1086 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetNameContainsOneOf`  
`class UAnimDatabaseFrameRangesFunction_AssetNameContainsOneOf : public UAnimDatabaseFrameRangesFunction`  
_L1091-1103_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Name Contains One Of Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with any of the given sub-strings in the name
- L1098 _public member_ `TArray<FString> AssetNameSubstrings;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1102 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetPackageContains`  
`class UAnimDatabaseFrameRangesFunction_AssetPackageContains : public UAnimDatabaseFrameRangesFunction`  
_L1107-1119_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Package Contains Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with the given sub-string in the package
- L1114 _public member_ `FString AssetPackageSubstring;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1118 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetPackageContainsOneOf`  
`class UAnimDatabaseFrameRangesFunction_AssetPackageContainsOneOf : public UAnimDatabaseFrameRangesFunction`  
_L1123-1135_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Package Contains One Of Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges with any of the given sub-strings in the package
- L1130 _public member_ `TArray<FString> AssetPackageSubstrings;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1134 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetNameStartsWith`  
`class UAnimDatabaseFrameRangesFunction_AssetNameStartsWith : public UAnimDatabaseFrameRangesFunction`  
_L1139-1151_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Name Starts With Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that start with the given sub-string in the name
- L1146 _public member_ `FString AssetNamePrefix;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1150 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetNameStartsWithOneOf`  
`class UAnimDatabaseFrameRangesFunction_AssetNameStartsWithOneOf : public UAnimDatabaseFrameRangesFunction`  
_L1155-1167_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Name Starts With One Of Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that start with any of the given sub-strings in the name
- L1162 _public member_ `TArray<FString> AssetNamePrefixes;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1166 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetNameEndsWith`  
`class UAnimDatabaseFrameRangesFunction_AssetNameEndsWith : public UAnimDatabaseFrameRangesFunction`  
_L1171-1183_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Name Ends With Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that end with the given sub-string in the name
- L1178 _public member_ `FString AssetNameSuffix;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1182 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_AssetNameEndsWithOneOf`  
`class UAnimDatabaseFrameRangesFunction_AssetNameEndsWithOneOf : public UAnimDatabaseFrameRangesFunction`  
_L1187-1199_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Asset Name Ends With One Of Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges that end with any of the given sub-strings in the name
- L1194 _public member_ `TArray<FString> AssetNameSuffixes;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L1198 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Filter`  
`class UAnimDatabaseFrameRangesFunction_Filter : public UAnimDatabaseFrameRangesFunction`  
_L1203-1215_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Filter Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Applies a sequence of FrameRangesFunctions to filter ranges
- L1210 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameRangesFunction>> Functions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1214 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Not`  
`class UAnimDatabaseFrameRangesFunction_Not : public UAnimDatabaseFrameRangesFunction`  
_L1219-1231_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Not Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Returns all the frame ranges in the database that are NOT given by the provided function
- L1226 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1230 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Union`  
`class UAnimDatabaseFrameRangesFunction_Union : public UAnimDatabaseFrameRangesFunction`  
_L1235-1247_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Union Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which are a union of the given sub-ranges
- L1242 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameRangesFunction>> Functions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1246 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Intersection`  
`class UAnimDatabaseFrameRangesFunction_Intersection : public UAnimDatabaseFrameRangesFunction`  
_L1251-1263_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Intersection Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which are an intersection of the given sub-ranges
- L1258 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameRangesFunction>> Functions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1262 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Difference`  
`class UAnimDatabaseFrameRangesFunction_Difference : public UAnimDatabaseFrameRangesFunction`  
_L1267-1279_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Difference Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which are an difference of the given sub-ranges
- L1274 _public member_ `TArray<TObjectPtr<UAnimDatabaseFrameRangesFunction>> Functions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1278 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Bounds`  
`class UAnimDatabaseFrameRangesFunction_Bounds : public UAnimDatabaseFrameRangesFunction`  
_L1283-1295_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bounds Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which bounds another set of ranges
- L1290 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1294 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Intersects`  
`class UAnimDatabaseFrameRangesFunction_Intersects : public UAnimDatabaseFrameRangesFunction`  
_L1299-1311_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Intersects Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which contain any part of the provided frame ranges
- L1306 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1310 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_IntersectsFrames`  
`class UAnimDatabaseFrameRangesFunction_IntersectsFrames : public UAnimDatabaseFrameRangesFunction`  
_L1315-1327_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Intersects Frames Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which contain any part of the provided frames
- L1322 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1326 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_BoundsFrames`  
`class UAnimDatabaseFrameRangesFunction_BoundsFrames : public UAnimDatabaseFrameRangesFunction`  
_L1331-1343_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Bounds Frames Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Finds all the frame ranges which bounds another set of frames
- L1338 _public member_ `TObjectPtr<UAnimDatabaseFramesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1342 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Interval`  
`class UAnimDatabaseFrameRangesFunction_Interval : public UAnimDatabaseFrameRangesFunction`  
_L1347-1359_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Interval Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Frame ranges consisting of single frames spaced at a regular interval
- L1354 _public member_ `int32 Interval = 10;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))`
- L1358 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Trim`  
`class UAnimDatabaseFrameRangesFunction_Trim : public UAnimDatabaseFrameRangesFunction`  
_L1363-1383_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Trim Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Trims the given frame ranges
- L1370 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1374 _public member_ `int32 TrimStart = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — Number of frames to trim from the start of the frame ranges
- L1378 _public member_ `int32 TrimEnd = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — Number of frames to trim from the end of the frame ranges
- L1382 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### class `UAnimDatabaseFrameRangesFunction_Pad`  
`class UAnimDatabaseFrameRangesFunction_Pad : public UAnimDatabaseFrameRangesFunction`  
_L1387-1407_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Pad Frame Ranges"))`
- inherits: `UAnimDatabaseFrameRangesFunction`
- desc: Pads the given frame ranges
- L1394 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")`
- L1398 _public member_ `int32 PadStart = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — Number of frames to pad the start of the frame ranges with
- L1402 _public member_ `int32 PadEnd = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — Number of frames to pad the end of the frame ranges with
- L1406 _public prototype_ `virtual FAnimDatabaseFrameRanges MakeFrameRanges_Implementation(const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges) const override;`

#### struct `FAnimDatabaseFrameRangesEntry`  
`struct FAnimDatabaseFrameRangesEntry`  
_L1411-1424_
- reflection: `USTRUCT(BlueprintType)`
- desc: Entry specifying a frame ranges function
- L1419 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Frame Ranges name
- L1423 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Frame Ranges function

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ANIMDATABASE_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Learning` (scope `UE`)
- L53 _prototype_ `bool operator==(const FAnimDatabaseFrames& Lhs, const FAnimDatabaseFrames& Rhs);`
- L60 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon3d33390e0103`)
- L61 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon3d33390e0103`)
- L89 _prototype_ `bool operator==(const FAnimDatabaseFrameRanges& Lhs, const FAnimDatabaseFrameRanges& Rhs);`
- L96 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon3d33390e0203`)
- L97 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon3d33390e0203`)
- L343 _prototype_ `bool operator==(const FAnimDatabaseFramesEntry& Lhs, const FAnimDatabaseFramesEntry& Rhs);`
- L1426 _prototype_ `bool operator==(const FAnimDatabaseFrameRangesEntry& Lhs, const FAnimDatabaseFrameRangesEntry& Rhs);`

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Public/AnimDatabaseIndex.h` (Public)


#### class `UAnimDatabaseIndexFunction`  
`class UAnimDatabaseIndexFunction : public UObject`  
_L18-36_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Function used to create an index from a database
- L28 _public prototype_ `void BuildIndex( TMap<FName, FAnimDatabaseFrames>& OutIndexFrames, TMap<FName, FAnimDatabaseFrameRanges>& OutIndexFrameRanges, TMap<FName, FAnimDatabaseFrameAttribute>& OutIndexFrameAttributes, UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Index", meta = (ForceAsFunction))` — Builds the index for the given database and frame ranges

#### class `UAnimDatabaseIndex`  
`class UAnimDatabaseIndex : public UDataAsset`  
_L42-89_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UDataAsset`
- desc: A Database Index is an asset you can use to store Frames, FrameRanges, and FrameAttributes derived from an AnimDatabase
- L51 _public member_ `TSoftObjectPtr<UAnimDatabase> Database;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")` — Database to build the index for
- L55 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Build")` — The frame ranges to build the index over
- L59 _public member_ `TObjectPtr<UAnimDatabaseIndexFunction> Function;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Build")` — Function used to build the index
- L65 _public prototype_ `void Build();` — `UFUNCTION(CallInEditor, Category = "Build")` — Builds the index by calling the BuildIndex function
- L72 _public member_ `TObjectPtr<UAnimDatabase> IndexDatabase;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Index")` — Database this index corresponds to
- L76 _public member_ `int32 IndexContentHash = 0;` — `UPROPERTY()` — Hash of the database content at the time of indexing
- L80 _public member_ `TMap<FName,FAnimDatabaseFrames> IndexFrames;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Index")` — Map of index AnimDatabaseFrames structures
- L84 _public member_ `TMap<FName,FAnimDatabaseFrameRanges> IndexFrameRanges;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Index")` — Map of index AnimDatabaseFrameRanges structures
- L88 _public member_ `TMap<FName,FAnimDatabaseFrameAttribute> IndexFrameAttributes;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Index")` — Map of index AnimDatabaseFrameAttributes structures

#### class `UAnimDatabaseIndexFunction_Basic`  
`class UAnimDatabaseIndexFunction_Basic : public UAnimDatabaseIndexFunction`  
_L93-125_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Basic"))`
- inherits: `UAnimDatabaseIndexFunction`
- desc: Function used to create an index from a set of different frames, frame ranges, and frame attribute entries
- L101 _private member_ `TArray<FAnimDatabaseFramesEntry> Frames;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — List of frames to store
- L105 _private member_ `TArray<FAnimDatabaseFrameRangesEntry> FrameRanges;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — List of frame ranges to store
- L109 _private member_ `TArray<FAnimDatabaseFrameAttributeEntry> FrameAttributes;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — List of frame attribute to store
- L117 _public prototype_ `virtual void BuildIndex_Implementation( TMap<FName, FAnimDatabaseFrames>& OutIndexFrames, TMap<FName, FAnimDatabaseFrameRanges>& OutIndexFrameRanges, TMap<FName, FAnimDatabaseFrameAttribute>& OutIndexFrameAttributes, UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`

#### class `UAnimDatabaseIndexFunction_TransitionPose`  
`class UAnimDatabaseIndexFunction_TransitionPose : public UAnimDatabaseIndexFunction`  
_L129-165_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Transition Pose"))`
- inherits: `UAnimDatabaseIndexFunction`
- desc: Function used to create an index containing frame attribute and ranges for measuring transition cost
- L137 _private member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> TransitionRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Ranges to store the toe location and velocities for
- L141 _private member_ `FName LeftToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left toe bone
- L145 _private member_ `FName RightToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right toe bone
- L149 _private member_ `TArray<FAnimDatabaseFrameRangesEntry> StyleRanges;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — List of style ranges to store
- L157 _public prototype_ `virtual void BuildIndex_Implementation( TMap<FName, FAnimDatabaseFrames>& OutIndexFrames, TMap<FName, FAnimDatabaseFrameRanges>& OutIndexFrameRanges, TMap<FName, FAnimDatabaseFrameAttribute>& OutIndexFrameAttributes, UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`

#### class `UAnimDatabaseIndexFunction_AttachBone`  
`class UAnimDatabaseIndexFunction_AttachBone : public UAnimDatabaseIndexFunction`  
_L169-195_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Attach Bone"))`
- inherits: `UAnimDatabaseIndexFunction`
- desc: Function used to create an index containing attach bone data
- L176 _private member_ `FName AttachBoneName = TEXT("att` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L179 _private member_ `FVector AttachForwardVector = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L187 _public prototype_ `virtual void BuildIndex_Implementation( TMap<FName, FAnimDatabaseFrames>& OutIndexFrames, TMap<FName, FAnimDatabaseFrameRanges>& OutIndexFrameRanges, TMap<FName, FAnimDatabaseFrameAttribute>& OutIndexFrameAttributes, UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) override;`

#### class `UAnimDatabaseIndexLibrary`  
`class UAnimDatabaseIndexLibrary : public UBlueprintFunctionLibrary`  
_L199-245_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library of helper functions for Animation Database Indices
- L207 _public prototype_ `static bool FindTransitionPoseMatch( UAnimSequence*& OutAnimSequence, float& OutAnimSequenceTime, bool& bOutAnimSequenceMirrored, float& OutMinimumValue, const UAnimDatabaseIndex* Index, const FVector LeftToeBoneLocation, const FVector LeftToeBoneVelocity, const FVector RightToeBoneLocation, const FVector RightToeBoneVelocity, const FTransform& RootTransform, UPARAM(ref) int32& RandomState, const FName StyleName = NAME_None, const float BlendTime = 0.2f, const float LocationScale = 100.0f, const float VelocityScale = 200.0f, const float LocationWeight = 1.0f, const float VelocityWeight = 1.0f, const float RandomWeight = 0.1f);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta=(AutoCreateRefTerm = "RootTransform"))` — Finds the best matching transition pose given the Transition Pose index
- L229 _public prototype_ `static bool FindAttachBoneMatch( UAnimSequence*& OutAnimSequence, float& OutAnimSequenceTime, bool& bOutAnimSequenceMirrored, float& OutMinimumValue, const UAnimDatabaseIndex* Index, const FVector AttachBoneLocation, const FVector AttachBoneDirection, const FVector RootLinearVelocity, const FTransform& RootTransform, const float LocationScale = 100.0f, const float VelocityScale = 200.0f, const float LocationWeight = 1.0f, const float DirectionWeight = 1.0f, const float VelocityWeight = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "AnimDatabase", meta = (AutoCreateRefTerm = "RootTransform"))` — Finds the best matching pose for the provided attach bone location and direction

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMDATABASE_API`

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Public/AnimDatabaseMath.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ANIMDATABASE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L16 _namespace_ `namespace Math` (scope `UE::AnimDatabase`)
- L20 _prototype_ `FVector3f VectorMax(const FVector3f V, const float W);` (scope `UE::AnimDatabase::Math`)
- L21 _prototype_ `FVector3f VectorMin(const FVector3f V, const float W);` (scope `UE::AnimDatabase::Math`)
- L22 _prototype_ `FVector3f VectorMax(const FVector3f V, const FVector3f W);` (scope `UE::AnimDatabase::Math`)
- L23 _prototype_ `FVector3f VectorMin(const FVector3f V, const FVector3f W);` (scope `UE::AnimDatabase::Math`)
- L24 _prototype_ `FVector3f VectorDivMax(const float V, const FVector3f W, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L25 _prototype_ `FVector3f VectorDivMax(const FVector3f V, const FVector3f W, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L26 _prototype_ `FVector3f VectorInvExpApprox(const FVector3f V);` (scope `UE::AnimDatabase::Math`)
- L27 _prototype_ `FVector3f VectorEerp(const FVector3f V, const FVector3f W, const float Alpha, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L28 _prototype_ `FVector3f VectorLog(const FVector3f V);` (scope `UE::AnimDatabase::Math`)
- L29 _prototype_ `FVector3f VectorExp(const FVector3f V);` (scope `UE::AnimDatabase::Math`)
- L30 _prototype_ `FVector3f VectorLogSafe(const FVector3f V, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L31 _prototype_ `FVector3f VectorExpSafe(const FVector3f V, const float Max = 10.0f);` (scope `UE::AnimDatabase::Math`)
- L32 _prototype_ `FVector3f VectorSqrt(const FVector3f A);` (scope `UE::AnimDatabase::Math`)
- L33 _prototype_ `FVector3f VectorGt(const FVector3f A, const float W);` (scope `UE::AnimDatabase::Math`)
- L34 _prototype_ `FVector3f VectorSign(const FVector3f A);` (scope `UE::AnimDatabase::Math`)
- L35 _prototype_ `FVector3f VectorAbs(const FVector3f A);` (scope `UE::AnimDatabase::Math`)
- L36 _prototype_ `FVector3f VectorEq(const FVector3f A, const FVector3f W);` (scope `UE::AnimDatabase::Math`)
- L37 _prototype_ `float VectorLength(const FVector4f X);` (scope `UE::AnimDatabase::Math`)
- L38 _prototype_ `FVector4f VectorNormalize(const FVector4f X);` (scope `UE::AnimDatabase::Math`)
- L39 _prototype_ `FVector VectorLogSafe(const FVector V, const double Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L40 _prototype_ `FVector VectorExpSafe(const FVector V, const double Max = 10.0);` (scope `UE::AnimDatabase::Math`)
- L44 _prototype_ `FQuat4f MakeQuatFromMatrixRightHanded(const FMatrix44f Matrix);` (scope `UE::AnimDatabase::Math`)
- L48 _prototype_ `void LerpToTargetInplace( const TLearningArrayView<1, float> InOut, const TLearningArrayView<1, const float> Target, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L53 _prototype_ `void LerpToTargetInplace( const TLearningArrayView<2, float> InOut, const TLearningArrayView<2, const float> Target, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L60 _prototype_ `float HalfLifeToDamping(const float HalfLife);` (scope `UE::AnimDatabase::Math`)
- L61 _prototype_ `float DampingToHalfLife(const float Damping);` (scope `UE::AnimDatabase::Math`)
- L63 _prototype_ `void CriticalSpringUpdate( FVector& InOutValue, FVector& InOutVelocity, const FVector& DesiredValue, const float HalfLife, const float DeltaTime);` (scope `UE::AnimDatabase::Math`)
- L70 _prototype_ `void CriticalSpringUpdate( FQuat& InOutValue, FVector& InOutVelocity, const FQuat& DesiredValue, const float HalfLife, const float DeltaTime);` (scope `UE::AnimDatabase::Math`)
- L77 _prototype_ `void CriticalSpringUpdate( FRotator& InOutValue, FVector& InOutVelocity, const FRotator& DesiredValue, const float HalfLife, const float DeltaTime);` (scope `UE::AnimDatabase::Math`)
- L84 _prototype_ `void CriticalSpringUpdatePositionFromVelocity( FVector& InOutPosition, FVector& InOutVelocity, FVector& InOutAcceleration, const FVector& DesiredVelocity, const float HalfLife, const float DeltaTime);` (scope `UE::AnimDatabase::Math`)
- L94 _prototype_ `void ExtrapolateTranslation( FVector3f& OutTranslation, FVector3f& OutVelocity, const FVector3f Translation, const FVector3f Velocity, const float Time, const FVector3f DecayHalflife, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L103 _prototype_ `void ExtrapolateTranslation( FVector& OutTranslation, FVector3f& OutVelocity, const FVector Translation, const FVector3f Velocity, const float Time, const FVector3f DecayHalflife, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L112 _prototype_ `void ExtrapolateRotation( FQuat4f& OutRotation, FVector3f& OutVelocity, const FQuat4f Rotation, const FVector3f Velocity, const float Time, const FVector3f DecayHalflife, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L121 _prototype_ `void ExtrapolateScale( FVector3f& OutScale, FVector3f& OutVelocity, const FVector3f Scale, const FVector3f Velocity, const float Time, const FVector3f DecayHalflife, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L130 _prototype_ `void ExtrapolateCurve( float& OutCurve, float& OutVelocity, const float Curve, const float Velocity, const float Time, const float DecayHalflife, const float Epsilon = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L141 _prototype_ `void DecayCubic( FVector3f& OutPosition, FVector3f& OutVelocity, const FVector3f Position, const FVector3f Velocity, const float Time, const float DecayDuration);` (scope `UE::AnimDatabase::Math`)
- L151 _prototype_ `float ClipMagnitudeToGreaterThanEpsilon(const float X, const float Epsilon = UE_KINDA_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L153 _prototype_ `float ComputeDecayHalfLifeFromDiffAndVelocity( const float SrcDstDiff, const float SrcVelocity, const float HalfLife, const float HalfLifeMin, const float HalfLifeMax, const float Epsilon = UE_KINDA_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L161 _prototype_ `FVector3f ComputeDecayHalfLifeFromDiffAndVelocity( const FVector3f SrcDstDiff, const FVector3f SrcVelocity, const float HalfLife, const float HalfLifeMin, const float HalfLifeMax, const float Epsilon = UE_KINDA_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L171 _prototype_ `void LocationInertializeCubicUpdate( FVector& OutLocation, FVector3f& OutLinearVelocity, float& InOutTimeSinceTransition, const FVector InLocation, const FVector3f InLinearVelocity, const FVector3f InLocationOffset, const FVector3f InLinearVelocityOffset, const float DeltaTime, const float BlendTime = 0.2f);` (scope `UE::AnimDatabase::Math`)
- L182 _prototype_ `void LocationInertializeCubicTransition( FVector3f& InOutLocationOffset, FVector3f& InOutLinearVelocityOffset, float& InOutTimeSinceTransition, const FVector InSrcLocation, const FVector3f InSrcLinearVelocity, const FVector InDstLocation, const FVector3f InDstLinearVelocity, const float BlendTime = 0.2f);` (scope `UE::AnimDatabase::Math`)
- L194 _prototype_ `void HermiteValueInterpolate(float& OutValue, float& OutValueVelocity, const float P0, const float P1, const float V0, const float V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L195 _prototype_ `void HermiteAngleInterpolate(float& OutAngle, float& OutAngularVelocity, const float A0, const float A1, const float V0, const float V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L196 _prototype_ `void HermiteLocationInterpolate(FVector& OutPosition, FVector3f& OutLinearVelocity, const FVector P0, const FVector P1, const FVector3f V0, const FVector3f V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L197 _prototype_ `void HermiteLocationInterpolate(FVector3f& OutPosition, FVector3f& OutLinearVelocity, const FVector3f P0, const FVector3f P1, const FVector3f V0, const FVector3f V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L198 _prototype_ `void HermiteRotationInterpolate(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R0, const FQuat4f R1, const FVector3f V0, const FVector3f V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L199 _prototype_ `void HermiteScaleInterpolate(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S0, const FVector3f S1, const FVector3f V0, const FVector3f V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L200 _prototype_ `void HermiteArrayInterpolate( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> V0, const TLearningArrayView<1, const float> V1, const float X, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L210 _prototype_ `void HermiteValueInterpolate(float& OutValue, const float P0, const float P1, const float V0, const float V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L211 _prototype_ `void HermiteAngleInterpolate(float& OutAngle , const float A0, const float A1, const float V0, const float V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L212 _prototype_ `void HermiteLocationInterpolate(FVector& OutPosition, const FVector P0, const FVector P1, const FVector3f V0, const FVector3f V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L213 _prototype_ `void HermiteLocationInterpolate(FVector3f& OutPosition, const FVector3f P0, const FVector3f P1, const FVector3f V0, const FVector3f V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L214 _prototype_ `void HermiteRotationInterpolate(FQuat4f& OutRotation, const FQuat4f R0, const FQuat4f R1, const FVector3f V0, const FVector3f V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L215 _prototype_ `void HermiteScaleInterpolate(FVector3f& OutScale, const FVector3f S0, const FVector3f S1, const FVector3f V0, const FVector3f V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L216 _prototype_ `void HermiteArrayInterpolate( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> V0, const TLearningArrayView<1, const float> V1, const float X);` (scope `UE::AnimDatabase::Math`)
- L226 _prototype_ `void ValueInterpolateLinear(float& OutValue, float& OutValueVelocity, const float P0, const float P1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L227 _prototype_ `void AngleInterpolateLinear(float& OutAngle, float& OutAngularVelocity, const float A0, const float A1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L228 _prototype_ `void LocationInterpolateLinear(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P0, const FVector P1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L229 _prototype_ `void LocationInterpolateLinear(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P0, const FVector3f P1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L230 _prototype_ `void RotationInterpolateLinear(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R0, const FQuat4f R1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L231 _prototype_ `void ScaleInterpolateLinear(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S0, const FVector3f S1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L232 _prototype_ `void ArrayInterpolateLinear( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L240 _prototype_ `void ValueInterpolateLinear(float& OutValue, const float P0, const float P1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L241 _prototype_ `void AngleInterpolateLinear(float& OutAngle, const float A0, const float A1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L242 _prototype_ `void LocationInterpolateLinear(FVector& OutLocation, const FVector P0, const FVector P1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L243 _prototype_ `void LocationInterpolateLinear(FVector3f& OutLocation, const FVector3f P0, const FVector3f P1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L244 _prototype_ `void RotationInterpolateLinear(FQuat4f& OutRotation, const FQuat4f R0, const FQuat4f R1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L245 _prototype_ `void ScaleInterpolateLinear(FVector3f& OutScale, const FVector3f S0, const FVector3f S1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L246 _prototype_ `void DirectionInterpolateLinear(FVector3f& OutDirection, const FVector3f D0, const FVector3f D1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L247 _prototype_ `void TransformInterpolateLinear(FTransform3f& OutTransform, const FTransform3f T0, const FTransform3f T1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L248 _prototype_ `void ArrayInterpolateLinear( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L256 _prototype_ `void ValueInterpolateCubic(float& OutValue, float& OutValueVelocity, const float P0, const float P1, const float P2, const float P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L257 _prototype_ `void AngleInterpolateCubic(float& OutAngle, float& OutAngularVelocity, const float A0, const float A1, const float A2, const float A3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L258 _prototype_ `void LocationInterpolateCubic(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P0, const FVector P1, const FVector P2, const FVector P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L259 _prototype_ `void LocationInterpolateCubic(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P0, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L260 _prototype_ `void RotationInterpolateCubic(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L261 _prototype_ `void ScaleInterpolateCubic(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S0, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L262 _prototype_ `void ArrayInterpolateCubic( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L272 _prototype_ `void ValueInterpolateCubic(float& OutValue, const float P0, const float P1, const float P2, const float P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L273 _prototype_ `void AngleInterpolateCubic(float& OutAngle, const float A0, const float A1, const float A2, const float A3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L274 _prototype_ `void LocationInterpolateCubic(FVector& OutLocation, const FVector P0, const FVector P1, const FVector P2, const FVector P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L275 _prototype_ `void LocationInterpolateCubic(FVector3f& OutLocation, const FVector3f P0, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L276 _prototype_ `void RotationInterpolateCubic(FQuat4f& OutRotation, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L277 _prototype_ `void ScaleInterpolateCubic(FVector3f& OutScale, const FVector3f S0, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L278 _prototype_ `void DirectionInterpolateCubic(FVector3f& OutDirection, const FVector3f D0, const FVector3f D1, const FVector3f D2, const FVector3f D3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L279 _prototype_ `void TransformInterpolateCubic(FTransform3f& OutTransform, const FTransform3f T0, const FTransform3f T1, const FTransform3f T2, const FTransform3f T3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L280 _prototype_ `void ArrayInterpolateCubic( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L290 _prototype_ `void ValueInterpolateCubicStart(float& OutValue, float& OutValueVelocity, const float P1, const float P2, const float P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L291 _prototype_ `void AngleInterpolateCubicStart(float& OutAngle, float& OutAngularVelocity, const float A1, const float A2, const float A3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L292 _prototype_ `void LocationInterpolateCubicStart(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P1, const FVector P2, const FVector P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L293 _prototype_ `void LocationInterpolateCubicStart(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L294 _prototype_ `void RotationInterpolateCubicStart(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L295 _prototype_ `void ScaleInterpolateCubicStart(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L296 _prototype_ `void ArrayInterpolateCubicStart( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L305 _prototype_ `void ValueInterpolateCubicStart(float& OutValue, const float P1, const float P2, const float P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L306 _prototype_ `void AngleInterpolateCubicStart(float& OutAngle, const float A1, const float A2, const float A3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L307 _prototype_ `void LocationInterpolateCubicStart(FVector& OutLocation, const FVector P1, const FVector P2, const FVector P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L308 _prototype_ `void LocationInterpolateCubicStart(FVector3f& OutLocation, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L309 _prototype_ `void RotationInterpolateCubicStart(FQuat4f& OutRotation, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L310 _prototype_ `void ScaleInterpolateCubicStart(FVector3f& OutScale, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L311 _prototype_ `void DirectionInterpolateCubicStart(FVector3f& OutDirection, const FVector3f D1, const FVector3f D2, const FVector3f D3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L312 _prototype_ `void TransformInterpolateCubicStart(FTransform3f& OutTransform, const FTransform3f T1, const FTransform3f T2, const FTransform3f T3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L313 _prototype_ `void ArrayInterpolateCubicStart( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L322 _prototype_ `void ValueInterpolateCubicEnd(float& OutValue, float& OutValueVelocity, const float P0, const float P1, const float P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L323 _prototype_ `void AngleInterpolateCubicEnd(float& OutAngle, float& OutAngularVelocity, const float A0, const float A1, const float A2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L324 _prototype_ `void LocationInterpolateCubicEnd(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P0, const FVector P1, const FVector P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L325 _prototype_ `void LocationInterpolateCubicEnd(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P0, const FVector3f P1, const FVector3f P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L326 _prototype_ `void RotationInterpolateCubicEnd(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L327 _prototype_ `void ScaleInterpolateCubicEnd(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S0, const FVector3f S1, const FVector3f S2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L328 _prototype_ `void ArrayInterpolateCubicEnd( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L337 _prototype_ `void ValueInterpolateCubicEnd(float& OutValue, const float P0, const float P1, const float P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L338 _prototype_ `void AngleInterpolateCubicEnd(float& OutAngle, const float A0, const float A1, const float A2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L339 _prototype_ `void LocationInterpolateCubicEnd(FVector& OutLocation, const FVector P0, const FVector P1, const FVector P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L340 _prototype_ `void LocationInterpolateCubicEnd(FVector3f& OutLocation, const FVector3f P0, const FVector3f P1, const FVector3f P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L341 _prototype_ `void RotationInterpolateCubicEnd(FQuat4f& OutRotation, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L342 _prototype_ `void ScaleInterpolateCubicEnd(FVector3f& OutScale, const FVector3f S0, const FVector3f S1, const FVector3f S2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L343 _prototype_ `void DirectionInterpolateCubicEnd(FVector3f& OutDirection, const FVector3f D0, const FVector3f D1, const FVector3f D2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L344 _prototype_ `void TransformInterpolateCubicEnd(FTransform3f& OutTransform, const FTransform3f T0, const FTransform3f T1, const FTransform3f T2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L345 _prototype_ `void ArrayInterpolateCubicEnd( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L354 _prototype_ `float ComputeMonotoneVelocity(const float D0, const float D1);` (scope `UE::AnimDatabase::Math`)
- L355 _prototype_ `FVector3f ComputeMonotoneVelocity(const FVector3f D0, const FVector3f D1);` (scope `UE::AnimDatabase::Math`)
- L359 _prototype_ `void ValueInterpolateCubicMono(float& OutValue, float& OutValueVelocity, const float P0, const float P1, const float P2, const float P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L360 _prototype_ `void AngleInterpolateCubicMono(float& OutAngle, float& OutAngularVelocity, const float A0, const float A1, const float A2, const float A3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L361 _prototype_ `void LocationInterpolateCubicMono(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P0, const FVector P1, const FVector P2, const FVector P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L362 _prototype_ `void LocationInterpolateCubicMono(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P0, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L363 _prototype_ `void RotationInterpolateCubicMono(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L364 _prototype_ `void ScaleInterpolateCubicMono(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S0, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L365 _prototype_ `void ArrayInterpolateCubicMono( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L375 _prototype_ `void ValueInterpolateCubicMono(float& OutValue, const float P0, const float P1, const float P2, const float P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L376 _prototype_ `void AngleInterpolateCubicMono(float& OutAngle, const float A0, const float A1, const float A2, const float A3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L377 _prototype_ `void LocationInterpolateCubicMono(FVector& OutLocation, const FVector P0, const FVector P1, const FVector P2, const FVector P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L378 _prototype_ `void LocationInterpolateCubicMono(FVector3f& OutLocation, const FVector3f P0, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L379 _prototype_ `void RotationInterpolateCubicMono(FQuat4f& OutRotation, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L380 _prototype_ `void ScaleInterpolateCubicMono(FVector3f& OutScale, const FVector3f S0, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L381 _prototype_ `void DirectionInterpolateCubicMono(FVector3f& OutDirection, const FVector3f D0, const FVector3f D1, const FVector3f D2, const FVector3f D3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L382 _prototype_ `void TransformInterpolateCubicMono(FTransform3f& OutTransform, const FTransform3f T0, const FTransform3f T1, const FTransform3f T2, const FTransform3f T3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L383 _prototype_ `void ArrayInterpolateCubicMono( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L393 _prototype_ `void ValueInterpolateCubicMonoStart(float& OutValue, float& OutValueVelocity, const float P1, const float P2, const float P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L394 _prototype_ `void AngleInterpolateCubicMonoStart(float& OutAngle, float& OutAngularVelocity, const float A1, const float A2, const float A3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L395 _prototype_ `void LocationInterpolateCubicMonoStart(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P1, const FVector P2, const FVector P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L396 _prototype_ `void LocationInterpolateCubicMonoStart(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L397 _prototype_ `void RotationInterpolateCubicMonoStart(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L398 _prototype_ `void ScaleInterpolateCubicMonoStart(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L399 _prototype_ `void ArrayInterpolateCubicMonoStart( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L408 _prototype_ `void ValueInterpolateCubicMonoStart(float& OutValue, const float P1, const float P2, const float P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L409 _prototype_ `void AngleInterpolateCubicMonoStart(float& OutAngle, const float A1, const float A2, const float A3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L410 _prototype_ `void LocationInterpolateCubicMonoStart(FVector& OutLocation, const FVector P1, const FVector P2, const FVector P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L411 _prototype_ `void LocationInterpolateCubicMonoStart(FVector3f& OutLocation, const FVector3f P1, const FVector3f P2, const FVector3f P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L412 _prototype_ `void RotationInterpolateCubicMonoStart(FQuat4f& OutRotation, const FQuat4f R1, const FQuat4f R2, const FQuat4f R3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L413 _prototype_ `void ScaleInterpolateCubicMonoStart(FVector3f& OutScale, const FVector3f S1, const FVector3f S2, const FVector3f S3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L414 _prototype_ `void DirectionInterpolateCubicMonoStart(FVector3f& OutDirection, const FVector3f D1, const FVector3f D2, const FVector3f D3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L415 _prototype_ `void TransformInterpolateCubicMonoStart(FTransform3f& OutTransform, const FTransform3f T1, const FTransform3f T2, const FTransform3f T3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L416 _prototype_ `void ArrayInterpolateCubicMonoStart( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const TLearningArrayView<1, const float> P3, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L425 _prototype_ `void ValueInterpolateCubicMonoEnd(float& OutValue, float& OutValueVelocity, const float P0, const float P1, const float P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L426 _prototype_ `void AngleInterpolateCubicMonoEnd(float& OutAngle, float& OutAngularVelocity, const float A0, const float A1, const float A2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L427 _prototype_ `void LocationInterpolateCubicMonoEnd(FVector& OutLocation, FVector3f& OutLinearVelocity, const FVector P0, const FVector P1, const FVector P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L428 _prototype_ `void LocationInterpolateCubicMonoEnd(FVector3f& OutLocation, FVector3f& OutLinearVelocity, const FVector3f P0, const FVector3f P1, const FVector3f P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L429 _prototype_ `void RotationInterpolateCubicMonoEnd(FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L430 _prototype_ `void ScaleInterpolateCubicMonoEnd(FVector3f& OutScale, FVector3f& OutScalarVelocity, const FVector3f S0, const FVector3f S1, const FVector3f S2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L431 _prototype_ `void ArrayInterpolateCubicMonoEnd( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutValueVelocities, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const float Alpha, const float FrameTime);` (scope `UE::AnimDatabase::Math`)
- L440 _prototype_ `void ValueInterpolateCubicMonoEnd(float& OutValue, const float P0, const float P1, const float P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L441 _prototype_ `void AngleInterpolateCubicMonoEnd(float& OutAngle, const float A0, const float A1, const float A2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L442 _prototype_ `void LocationInterpolateCubicMonoEnd(FVector& OutLocation, const FVector P0, const FVector P1, const FVector P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L443 _prototype_ `void LocationInterpolateCubicMonoEnd(FVector3f& OutLocation, const FVector3f P0, const FVector3f P1, const FVector3f P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L444 _prototype_ `void RotationInterpolateCubicMonoEnd(FQuat4f& OutRotation, const FQuat4f R0, const FQuat4f R1, const FQuat4f R2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L445 _prototype_ `void ScaleInterpolateCubicMonoEnd(FVector3f& OutScale, const FVector3f S0, const FVector3f S1, const FVector3f S2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L446 _prototype_ `void DirectionInterpolateCubicMonoEnd(FVector3f& OutDirection, const FVector3f D0, const FVector3f D1, const FVector3f D2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L447 _prototype_ `void TransformInterpolateCubicMonoEnd(FTransform3f& OutTransform, const FTransform3f T0, const FTransform3f T1, const FTransform3f T2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L448 _prototype_ `void ArrayInterpolateCubicMonoEnd( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, const float> P0, const TLearningArrayView<1, const float> P1, const TLearningArrayView<1, const float> P2, const float Alpha);` (scope `UE::AnimDatabase::Math`)
- L457 _prototype_ `int64 ComputeNearestSampleFrame( const float FrameTime, const int64 FrameNum);` (scope `UE::AnimDatabase::Math`)
- L461 _prototype_ `void ComputeLinearSampleFramesAndAlpha( int64& OutSampleFrame0, int64& OutSampleFrame1, float& OutSampleAlpha, const float FrameTime, const int64 FrameNum);` (scope `UE::AnimDatabase::Math`)
- L468 _prototype_ `void ComputeCubicSampleFramesAndAlpha( int64& OutSampleFrame0, int64& OutSampleFrame1, int64& OutSampleFrame2, int64& OutSampleFrame3, float& OutSampleAlpha, const float FrameTime, const int64 FrameNum);` (scope `UE::AnimDatabase::Math`)
- L477 _prototype_ `int64 ComputeNearestSampleFrame( const int64 FrameTime, const int64 FrameNum);` (scope `UE::AnimDatabase::Math`)
- L481 _prototype_ `void ComputeLinearSampleFramesAndAlpha( int64& OutSampleFrame0, int64& OutSampleFrame1, float& OutSampleAlpha, const int64 FrameTime, const int64 FrameNum);` (scope `UE::AnimDatabase::Math`)
- L488 _prototype_ `void ComputeCubicSampleFramesAndAlpha( int64& OutSampleFrame0, int64& OutSampleFrame1, int64& OutSampleFrame2, int64& OutSampleFrame3, float& OutSampleAlpha, const int64 FrameTime, const int64 FrameNum);` (scope `UE::AnimDatabase::Math`)
- L499 _prototype_ `void ValueSampleNearest( float& OutValue, const TLearningArrayView<1, const float> InValues, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L504 _prototype_ `void AngleSampleNearest( float& OutAngle, const TLearningArrayView<1, const float> InAngles, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L509 _prototype_ `void LocationSampleNearest( FVector& OutLocation, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L514 _prototype_ `void LocationSampleNearest( FVector& OutLocation, FVector3f& OutLinearVelocity, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L520 _prototype_ `void RotationSampleNearest( FQuat4f& OutRotation, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L525 _prototype_ `void RotationSampleNearest( FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L531 _prototype_ `void TransformSampleNearest( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L540 _prototype_ `void TransformSampleNearest( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, FVector3f& OutLinearVelocity, FVector3f& OutAngularVelocity, FVector3f& OutScalarVelocity, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L552 _prototype_ `void TransformSampleNearest( const TLearningArrayView<1, FVector3f> OutLocations, const TLearningArrayView<1, FQuat4f> OutRotations, const TLearningArrayView<1, FVector3f> OutScales, const TLearningArrayView<1, FVector3f> OutLinearVelocities, const TLearningArrayView<1, FVector3f> OutAngularVelocities, const TLearningArrayView<1, FVector3f> OutScalarVelocities, const TLearningArrayView<2, const FVector3f> InLocations, const TLearningArrayView<2, const FQuat4f> InRotations, const TLearningArrayView<2, const FVector3f> InScales, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L564 _prototype_ `void ArraySampleNearest( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L569 _prototype_ `void ArraySampleNearest( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutVelocities, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame);` (scope `UE::AnimDatabase::Math`)
- L575 _prototype_ `void ValueSampleLinear( float& OutValue, const TLearningArrayView<1, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L582 _prototype_ `void AngleSampleLinear( float& OutAngle, const TLearningArrayView<1, const float> InAngles, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L589 _prototype_ `void LocationSampleLinear( FVector& OutLocation, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L596 _prototype_ `void LocationSampleLinear( FVector& OutLocation, FVector3f& OutLinearVelocity, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L605 _prototype_ `void RotationSampleLinear( FQuat4f& OutRotation, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L612 _prototype_ `void RotationSampleLinear( FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L621 _prototype_ `void TransformSampleLinear( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L632 _prototype_ `void TransformSampleLinear( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, FVector3f& OutLinearVelocity, FVector3f& OutAngularVelocity, FVector3f& OutScalarVelocity, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L647 _prototype_ `void TransformSampleLinear( const TLearningArrayView<1, FVector3f> OutLocations, const TLearningArrayView<1, FQuat4f> OutRotations, const TLearningArrayView<1, FVector3f> OutScales, const TLearningArrayView<1, FVector3f> OutLinearVelocities, const TLearningArrayView<1, FVector3f> OutAngularVelocities, const TLearningArrayView<1, FVector3f> OutScalarVelocities, const TLearningArrayView<2, const FVector3f> InLocations, const TLearningArrayView<2, const FQuat4f> InRotations, const TLearningArrayView<2, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L662 _prototype_ `void ArraySampleLinear( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L669 _prototype_ `void ArraySampleLinear( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutVelocities, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L678 _prototype_ `void ValueSampleCubic( float& OutValue, const TLearningArrayView<1, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L687 _prototype_ `void AngleSampleCubic( float& OutAngle, const TLearningArrayView<1, const float> InAngles, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L696 _prototype_ `void LocationSampleCubic( FVector& OutLocation, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L705 _prototype_ `void LocationSampleCubic( FVector& OutLocation, FVector3f& OutLinearVelocity, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L716 _prototype_ `void RotationSampleCubic( FQuat4f& OutRotation, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L725 _prototype_ `void RotationSampleCubic( FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L736 _prototype_ `void TransformSampleCubic( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L749 _prototype_ `void TransformSampleCubic( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, FVector3f& OutLinearVelocity, FVector3f& OutAngularVelocity, FVector3f& OutScalarVelocity, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L766 _prototype_ `void TransformSampleCubic( const TLearningArrayView<1, FVector3f> OutLocations, const TLearningArrayView<1, FQuat4f> OutRotations, const TLearningArrayView<1, FVector3f> OutScales, const TLearningArrayView<1, FVector3f> OutLinearVelocities, const TLearningArrayView<1, FVector3f> OutAngularVelocities, const TLearningArrayView<1, FVector3f> OutScalarVelocities, const TLearningArrayView<2, const FVector3f> InLocations, const TLearningArrayView<2, const FQuat4f> InRotations, const TLearningArrayView<2, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L783 _prototype_ `void ArraySampleCubic( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L792 _prototype_ `void ArraySampleCubic( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutVelocities, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L803 _prototype_ `void ValueSampleCubicMono( float& OutValue, const TLearningArrayView<1, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L812 _prototype_ `void AngleSampleCubicMono( float& OutAngle, const TLearningArrayView<1, const float> InAngles, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L821 _prototype_ `void LocationSampleCubicMono( FVector& OutLocation, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L830 _prototype_ `void LocationSampleCubicMono( FVector& OutLocation, FVector3f& OutLinearVelocity, const TLearningArrayView<1, const FVector> InLocations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L841 _prototype_ `void RotationSampleCubicMono( FQuat4f& OutRotation, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L850 _prototype_ `void RotationSampleCubicMono( FQuat4f& OutRotation, FVector3f& OutAngularVelocity, const TLearningArrayView<1, const FQuat4f> InRotations, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L861 _prototype_ `void TransformSampleCubicMono( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L874 _prototype_ `void TransformSampleCubicMono( FVector& OutLocation, FQuat4f& OutRotation, FVector3f& OutScale, FVector3f& OutLinearVelocity, FVector3f& OutAngularVelocity, FVector3f& OutScalarVelocity, const TLearningArrayView<1, const FVector> InLocations, const TLearningArrayView<1, const FQuat4f> InRotations, const TLearningArrayView<1, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L891 _prototype_ `void TransformSampleCubicMono( const TLearningArrayView<1, FVector3f> OutLocations, const TLearningArrayView<1, FQuat4f> OutRotations, const TLearningArrayView<1, FVector3f> OutScales, const TLearningArrayView<1, FVector3f> OutLinearVelocities, const TLearningArrayView<1, FVector3f> OutAngularVelocities, const TLearningArrayView<1, FVector3f> OutScalarVelocities, const TLearningArrayView<2, const FVector3f> InLocations, const TLearningArrayView<2, const FQuat4f> InRotations, const TLearningArrayView<2, const FVector3f> InScales, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L908 _prototype_ `void ArraySampleCubicMono( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha);` (scope `UE::AnimDatabase::Math`)
- L917 _prototype_ `void ArraySampleCubicMono( const TLearningArrayView<1, float> OutValues, const TLearningArrayView<1, float> OutVelocities, const TLearningArrayView<2, const float> InValues, const int32 SampleFrame0, const int32 SampleFrame1, const int32 SampleFrame2, const int32 SampleFrame3, const float SampleAlpha, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L930 _prototype_ `void NearestSample( float& OutSampledValue, const TLearningArrayView<1, const float> InValues, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L936 _prototype_ `void NearestSampleArray( const TLearningArrayView<1, float> OutSampledVector, const TLearningArrayView<2, const float> InVectors, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L942 _prototype_ `void LinearSample( float& OutSampledValue, const TLearningArrayView<1, const float> InValues, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L948 _prototype_ `void LinearSampleArray( const TLearningArrayView<1, float> OutSampledVector, const TLearningArrayView<2, const float> InVectors, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L954 _prototype_ `void CubicSample( float& OutSampledValue, const TLearningArrayView<1, const float> InValues, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L960 _prototype_ `void CubicSampleArray( const TLearningArrayView<1, float> OutSampledVector, const TLearningArrayView<2, const float> InVectors, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L966 _prototype_ `void CubicMonoSample( float& OutSampledValue, const TLearningArrayView<1, const float> InValues, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L972 _prototype_ `void CubicMonoSampleLocation( FVector& OutSampledLocation, const TLearningArrayView<1, const FVector> InLocations, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L978 _prototype_ `void CubicMonoSampleLocation( FVector& OutSampledLocation, FVector3f& OutSampledVelocity, const TLearningArrayView<1, const FVector> InLocations, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L985 _prototype_ `void CubicMonoSampleArray( const TLearningArrayView<1, float> OutSampledVector, const TLearningArrayView<2, const float> InVectors, const float Time, const float FrameDeltaTime);` (scope `UE::AnimDatabase::Math`)
- L993 _prototype_ `float Sum(const TLearningArrayView<1, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L995 _prototype_ `void ComputeMean( float& OutMean, const TLearningArrayView<1, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L999 _prototype_ `void ComputeMeanStd( float& OutMean, float& OutStd, const TLearningArrayView<1, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L1004 _prototype_ `void ComputeMean( const TLearningArrayView<1, float> OutMean, const TLearningArrayView<2, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L1008 _prototype_ `void ComputeMeanStd( const TLearningArrayView<1, float> OutMean, const TLearningArrayView<1, float> OutStd, const TLearningArrayView<2, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L1013 _prototype_ `void ComputeMeanStd( const TLearningArrayView<1, float> OutMean, const TLearningArrayView<1, float> OutStd, const TLearningArrayView<2, const float> Data, const int32 ColSliceStart, const int32 ColSliceNum);` (scope `UE::AnimDatabase::Math`)
- L1020 _prototype_ `void ComputeMeanStdMasked( const TLearningArrayView<1, float> OutMean, const TLearningArrayView<1, float> OutStd, const TLearningArrayView<2, const float> Data, const TLearningArrayView<1, const bool> Mask, const int32 ColSliceStart, const int32 ColSliceNum);` (scope `UE::AnimDatabase::Math`)
- L1028 _prototype_ `void ComputeMeanStd( FVector3f& OutMean, FVector3f& OutStd, const TLearningArrayView<1, const FVector3f> Data);` (scope `UE::AnimDatabase::Math`)
- L1033 _prototype_ `void ComputeLocalMeanStd( FVector3f& OutMean, FVector3f& OutStd, const TLearningArrayView<1, const FVector3f> Data, const TLearningArrayView<1, const FQuat4f> Reference);` (scope `UE::AnimDatabase::Math`)
- L1039 _prototype_ `void ComputeMeanStdOfLog( FVector3f& OutMeanLog, FVector3f& OutStdLog, const TLearningArrayView<1, const FVector3f> Data);` (scope `UE::AnimDatabase::Math`)
- L1044 _prototype_ `void ComputeMeanStd( const TLearningArrayView<1, FVector3f> OutMeans, const TLearningArrayView<1, FVector3f> OutStds, const TLearningArrayView<2, const FVector3f> Vectors);` (scope `UE::AnimDatabase::Math`)
- L1049 _prototype_ `void ComputeMeanStdOfLog( const TLearningArrayView<1, FVector3f> OutMeanLogs, const TLearningArrayView<1, FVector3f> OutStdLogs, const TLearningArrayView<2, const FVector3f> Vectors);` (scope `UE::AnimDatabase::Math`)
- L1054 _prototype_ `FVector4f DominantEigenVector( const FMatrix44f& A, const FVector4f V0);` (scope `UE::AnimDatabase::Math`)
- L1058 _prototype_ `void ComputeMeanStd( const TLearningArrayView<1, FQuat4f> OutMeans, const TLearningArrayView<1, FMatrix44f> OutAccum, const TLearningArrayView<1, FVector3f> OutStds, const TLearningArrayView<2, const FQuat4f> Rotations);` (scope `UE::AnimDatabase::Math`)
- L1064 _prototype_ `void ComputeMeanStdWithReference( FQuat4f& OutMean, FVector3f& OutStd, const TLearningArrayView<1, const FQuat4f> Rotations, const FQuat4f Reference);` (scope `UE::AnimDatabase::Math`)
- L1070 _prototype_ `void ComputeMeanStdWithReference( const TLearningArrayView<1, FQuat4f> OutMeans, const TLearningArrayView<1, FMatrix44f> OutAccum, const TLearningArrayView<1, FVector3f> OutStds, const TLearningArrayView<2, const FQuat4f> Rotations, const TLearningArrayView<1, const FQuat4f> Reference);` (scope `UE::AnimDatabase::Math`)
- L1077 _prototype_ `void ComputeMeanStdAroundReference( const TLearningArrayView<1, FQuat4f> OutMeans, const TLearningArrayView<1, FVector3f> OutStds, const TLearningArrayView<2, const FQuat4f> Rotations, const TLearningArrayView<1, const FQuat4f> Reference);` (scope `UE::AnimDatabase::Math`)
- L1083 _prototype_ `void ComputeMinMax( float& OutMin, float& OutMax, const TLearningArrayView<1, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L1088 _prototype_ `void ComputeMinMax( const TLearningArrayView<1, float> OutMin, const TLearningArrayView<1, float> OutMax, const TLearningArrayView<2, const float> Data);` (scope `UE::AnimDatabase::Math`)
- L1093 _prototype_ `void ComputeMinMax( const TLearningArrayView<1, float> OutMin, const TLearningArrayView<1, float> OutMax, const TLearningArrayView<2, const float> Data, const int32 ColSliceStart, const int32 ColSliceNum);` (scope `UE::AnimDatabase::Math`)
- L1100 _prototype_ `void ComputeMaskedMinMax( const TLearningArrayView<1, float> OutMin, const TLearningArrayView<1, float> OutMax, const TLearningArrayView<2, const float> Data, const TLearningArrayView<2, const bool> Mask);` (scope `UE::AnimDatabase::Math`)
- L1108 _prototype_ `void ScaleInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Scale);` (scope `UE::AnimDatabase::Math`)
- L1112 _prototype_ `void NormalizeInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Mean, const TLearningArrayView<1, const float> Std, const float Eps = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L1118 _prototype_ `void NormalizeInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Mean, const float Std, const float Eps = UE_SMALL_NUMBER);` (scope `UE::AnimDatabase::Math`)
- L1124 _prototype_ `void DenormalizeInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Mean, const TLearningArrayView<1, const float> Std);` (scope `UE::AnimDatabase::Math`)
- L1129 _prototype_ `void DenormalizeInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Mean, const float Std);` (scope `UE::AnimDatabase::Math`)
- L1134 _prototype_ `void ClampInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Min, const TLearningArrayView<1, const float> Max);` (scope `UE::AnimDatabase::Math`)
- L1139 _prototype_ `void MaskedClampInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<2, const bool> Mask, const TLearningArrayView<1, const float> Min, const TLearningArrayView<1, const float> Max);` (scope `UE::AnimDatabase::Math`)
- L1145 _prototype_ `void ClampNormalizedInplace( const TLearningArrayView<2, float> InOutData, const TLearningArrayView<1, const float> Mean, const float Std, const TLearningArrayView<1, const float> Min, const TLearningArrayView<1, const float> Max);` (scope `UE::AnimDatabase::Math`)
- L1155 _prototype_ `bool AnyBoneIndicesInvalid(const UE::Learning::FIndexSet Indices);` (scope `UE::AnimDatabase::Math`)
- L1157 _prototype_ `bool BoneIndicesAreSortedAndUnique(const UE::Learning::FIndexSet Indices);` (scope `UE::AnimDatabase::Math`)
- L1159 _prototype_ `int32 BoneAscendantsInclusiveNum( const int32 BoneIdx, const TLearningArrayView<1, const int32> BoneParents);` (scope `UE::AnimDatabase::Math`)
- L1163 _prototype_ `void BoneAscendantsInclusive( const TLearningArrayView<1, int32> OutBoneAscendants, const int32 BoneIdx, const TLearningArrayView<1, const int32> BoneParents);` (scope `UE::AnimDatabase::Math`)
- L1168 _prototype_ `void BoneAscendantsInclusive( TArray<int32>& OutBoneAscendants, const int32 BoneIdx, const TLearningArrayView<1, const int32> BoneParents);` (scope `UE::AnimDatabase::Math`)
- L1173 _prototype_ `int32 BoneUnionNum( const UE::Learning::FIndexSet Lhs, const UE::Learning::FIndexSet Rhs);` (scope `UE::AnimDatabase::Math`)
- L1177 _prototype_ `void BoneUnion( const TLearningArrayView<1, int32> OutBoneUnion, const UE::Learning::FIndexSet Lhs, const UE::Learning::FIndexSet Rhs);` (scope `UE::AnimDatabase::Math`)
- L1182 _prototype_ `void BoneUnion( TArray<int32>& OutBoneUnion, const UE::Learning::FIndexSet Lhs, const UE::Learning::FIndexSet Rhs);` (scope `UE::AnimDatabase::Math`)
- L1187 _prototype_ `void BoneFindIndicesOf( const TLearningArrayView<1, int32> OutIndicesOf, const UE::Learning::FIndexSet Items, const UE::Learning::FIndexSet Elements);` (scope `UE::AnimDatabase::Math`)
- L1192 _prototype_ `void BoneChildrenMatrix( TLearningArrayView<2, bool> OutBoneChildren, const TLearningArrayView<1, const int32> BoneParents);` (scope `UE::AnimDatabase::Math`)
- L1196 _prototype_ `void BoneDescedantsMatrix( TLearningArrayView<2, bool> OutBoneDescendants, const TLearningArrayView<1, const int32> BoneParents);` (scope `UE::AnimDatabase::Math`)

### `Plugins/Experimental/Animation/AnimDatabase/Source/AnimDatabase/Public/AnimDatabasePose.h` (Public)


#### struct `UE::AnimDatabase::FPoseRootDataConstView`  
`struct FPoseRootDataConstView`  
_L35-47_
- desc: Const View of Pose Root Data
- L37 _public prototype_ `int32 GetFrameNum() const;`
- L39 _public prototype_ `FPoseRootDataConstView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L41 _public member_ `TLearningArrayView<1, const FVector> RootLocations;`
- L42 _public member_ `TLearningArrayView<1, const FQuat4f> RootRotations;`
- L43 _public member_ `TLearningArrayView<1, const FVector3f> RootScales;`
- L44 _public member_ `TLearningArrayView<1, const FVector3f> RootLinearVelocities;`
- L45 _public member_ `TLearningArrayView<1, const FVector3f> RootAngularVelocities;`
- L46 _public member_ `TLearningArrayView<1, const FVector3f> RootScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseRootDataView`  
`struct FPoseRootDataView`  
_L50-63_
- desc: Non-Const View of Pose Root Data
- L52 _public prototype_ `int32 GetFrameNum() const;`
- L54 _public prototype_ `FPoseRootDataConstView ConstView() const;`
- L55 _public prototype_ `FPoseRootDataView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L57 _public member_ `TLearningArrayView<1, FVector> RootLocations;`
- L58 _public member_ `TLearningArrayView<1, FQuat4f> RootRotations;`
- L59 _public member_ `TLearningArrayView<1, FVector3f> RootScales;`
- L60 _public member_ `TLearningArrayView<1, FVector3f> RootLinearVelocities;`
- L61 _public member_ `TLearningArrayView<1, FVector3f> RootAngularVelocities;`
- L62 _public member_ `TLearningArrayView<1, FVector3f> RootScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseRootData`  
`struct FPoseRootData`  
_L66-85_
- desc: Pose Root Data
- L68 _public prototype_ `int32 GetFrameNum() const;`
- L70 _public prototype_ `void Resize(const int32 FrameNum);`
- L71 _public prototype_ `bool IsEmpty() const;`
- L72 _public prototype_ `void Empty();`
- L74 _public prototype_ `FPoseRootDataView View();`
- L75 _public prototype_ `FPoseRootDataConstView ConstView() const;`
- L76 _public prototype_ `FPoseRootDataView Slice(const int32 FrameStart, const int32 FrameNum);`
- L77 _public prototype_ `FPoseRootDataConstView ConstSlice(const int32 FrameStart, const int32 FrameNum) const;`
- L79 _public member_ `TLearningArray<1, FVector> RootLocations;`
- L80 _public member_ `TLearningArray<1, FQuat4f> RootRotations;`
- L81 _public member_ `TLearningArray<1, FVector3f> RootScales;`
- L82 _public member_ `TLearningArray<1, FVector3f> RootLinearVelocities;`
- L83 _public member_ `TLearningArray<1, FVector3f> RootAngularVelocities;`
- L84 _public member_ `TLearningArray<1, FVector3f> RootScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseLocalBoneDataConstView`  
`struct FPoseLocalBoneDataConstView`  
_L90-103_
- desc: Const View of Pose Local Bone Transforms and Velocities
- L92 _public prototype_ `int32 GetFrameNum() const;`
- L93 _public prototype_ `int32 GetBoneNum() const;`
- L95 _public prototype_ `FPoseLocalBoneDataConstView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L97 _public member_ `TLearningArrayView<2, const FVector3f> BoneLocations;`
- L98 _public member_ `TLearningArrayView<2, const FQuat4f> BoneRotations;`
- L99 _public member_ `TLearningArrayView<2, const FVector3f> BoneScales;`
- L100 _public member_ `TLearningArrayView<2, const FVector3f> BoneLinearVelocities;`
- L101 _public member_ `TLearningArrayView<2, const FVector3f> BoneAngularVelocities;`
- L102 _public member_ `TLearningArrayView<2, const FVector3f> BoneScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseLocalBoneDataView`  
`struct FPoseLocalBoneDataView`  
_L106-120_
- desc: Non-Const View of Pose Local Bone Transforms and Velocities
- L108 _public prototype_ `int32 GetFrameNum() const;`
- L109 _public prototype_ `int32 GetBoneNum() const;`
- L111 _public prototype_ `FPoseLocalBoneDataConstView ConstView() const;`
- L112 _public prototype_ `FPoseLocalBoneDataView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L114 _public member_ `TLearningArrayView<2, FVector3f> BoneLocations;`
- L115 _public member_ `TLearningArrayView<2, FQuat4f> BoneRotations;`
- L116 _public member_ `TLearningArrayView<2, FVector3f> BoneScales;`
- L117 _public member_ `TLearningArrayView<2, FVector3f> BoneLinearVelocities;`
- L118 _public member_ `TLearningArrayView<2, FVector3f> BoneAngularVelocities;`
- L119 _public member_ `TLearningArrayView<2, FVector3f> BoneScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseLocalBoneData`  
`struct FPoseLocalBoneData`  
_L123-143_
- desc: Pose Local Bone Transforms and Velocities
- L125 _public prototype_ `int32 GetFrameNum() const;`
- L126 _public prototype_ `int32 GetBoneNum() const;`
- L128 _public prototype_ `void Resize(const int32 FrameNum, const int32 BoneNum);`
- L129 _public prototype_ `bool IsEmpty() const;`
- L130 _public prototype_ `void Empty();`
- L132 _public prototype_ `FPoseLocalBoneDataView View();`
- L133 _public prototype_ `FPoseLocalBoneDataConstView ConstView() const;`
- L134 _public prototype_ `FPoseLocalBoneDataView Slice(const int32 FrameStart, const int32 FrameNum);`
- L135 _public prototype_ `FPoseLocalBoneDataConstView ConstSlice(const int32 FrameStart, const int32 FrameNum) const;`
- L137 _public member_ `TLearningArray<2, FVector3f> BoneLocations;`
- L138 _public member_ `TLearningArray<2, FQuat4f> BoneRotations;`
- L139 _public member_ `TLearningArray<2, FVector3f> BoneScales;`
- L140 _public member_ `TLearningArray<2, FVector3f> BoneLinearVelocities;`
- L141 _public member_ `TLearningArray<2, FVector3f> BoneAngularVelocities;`
- L142 _public member_ `TLearningArray<2, FVector3f> BoneScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseGlobalBoneDataConstView`  
`struct FPoseGlobalBoneDataConstView`  
_L148-161_
- desc: Const View of Pose Global Bone Transforms and Velocities
- L150 _public prototype_ `int32 GetFrameNum() const;`
- L151 _public prototype_ `int32 GetBoneNum() const;`
- L153 _public prototype_ `FPoseGlobalBoneDataConstView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L155 _public member_ `TLearningArrayView<2, const FVector> BoneLocations;`
- L156 _public member_ `TLearningArrayView<2, const FQuat4f> BoneRotations;`
- L157 _public member_ `TLearningArrayView<2, const FVector3f> BoneScales;`
- L158 _public member_ `TLearningArrayView<2, const FVector3f> BoneLinearVelocities;`
- L159 _public member_ `TLearningArrayView<2, const FVector3f> BoneAngularVelocities;`
- L160 _public member_ `TLearningArrayView<2, const FVector3f> BoneScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseGlobalBoneDataView`  
`struct FPoseGlobalBoneDataView`  
_L164-177_
- desc: Non-Const View of Pose Global Bone Transforms and Velocities
- L166 _public prototype_ `int32 GetFrameNum() const;`
- L167 _public prototype_ `int32 GetBoneNum() const;`
- L169 _public prototype_ `FPoseGlobalBoneDataView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L171 _public member_ `TLearningArrayView<2, FVector> BoneLocations;`
- L172 _public member_ `TLearningArrayView<2, FQuat4f> BoneRotations;`
- L173 _public member_ `TLearningArrayView<2, FVector3f> BoneScales;`
- L174 _public member_ `TLearningArrayView<2, FVector3f> BoneLinearVelocities;`
- L175 _public member_ `TLearningArrayView<2, FVector3f> BoneAngularVelocities;`
- L176 _public member_ `TLearningArrayView<2, FVector3f> BoneScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseGlobalBoneData`  
`struct FPoseGlobalBoneData`  
_L180-200_
- desc: Pose Global Bone Transforms and Velocities
- L182 _public prototype_ `int32 GetFrameNum() const;`
- L183 _public prototype_ `int32 GetBoneNum() const;`
- L185 _public prototype_ `void Resize(const int32 FrameNum, const int32 BoneNum);`
- L186 _public prototype_ `bool IsEmpty() const;`
- L187 _public prototype_ `void Empty();`
- L189 _public prototype_ `FPoseGlobalBoneDataView View();`
- L190 _public prototype_ `FPoseGlobalBoneDataConstView ConstView() const;`
- L191 _public prototype_ `FPoseGlobalBoneDataView Slice(const int32 FrameStart, const int32 FrameNum);`
- L192 _public prototype_ `FPoseGlobalBoneDataConstView ConstSlice(const int32 FrameStart, const int32 FrameNum) const;`
- L194 _public member_ `TLearningArray<2, FVector> BoneLocations;`
- L195 _public member_ `TLearningArray<2, FQuat4f> BoneRotations;`
- L196 _public member_ `TLearningArray<2, FVector3f> BoneScales;`
- L197 _public member_ `TLearningArray<2, FVector3f> BoneLinearVelocities;`
- L198 _public member_ `TLearningArray<2, FVector3f> BoneAngularVelocities;`
- L199 _public member_ `TLearningArray<2, FVector3f> BoneScalarVelocities;`

#### struct `UE::AnimDatabase::FPoseAttributeDataConstView`  
`struct FPoseAttributeDataConstView`  
_L205-238_
- desc: Const View of Pose Attribute Data
- L207 _public prototype_ `int32 GetFrameNum() const;`
- L208 _public prototype_ `int32 GetAttributeNum() const;`
- L209 _public prototype_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> GetAttributeTypes() const;`
- L210 _public prototype_ `TLearningArrayView<1, const FName> GetAttributeNames() const;`
- L212 _public prototype_ `FPoseAttributeDataConstView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L214 _public prototype_ `EAnimDatabaseAttributeType GetAttributeType(const int32 AttributeIdx) const;`
- L215 _public prototype_ `FName GetAttributeName(const int32 AttributeIdx) const;`
- L216 _public prototype_ `int32 GetAttributeOffset(const int32 AttributeIdx) const;`
- L217 _public prototype_ `int32 GetAttributeSize(const int32 AttributeIdx) const;`
- L218 _public prototype_ `bool GetAttributeActive(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L220 _public prototype_ `bool GetBool(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L221 _public prototype_ `float GetFloat(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L222 _public prototype_ `float GetAngle(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L223 _public prototype_ `FVector3f GetLocation(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L224 _public prototype_ `FQuat4f GetRotation(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L225 _public prototype_ `FVector3f GetScale(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L226 _public prototype_ `FVector3f GetLinearVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L227 _public prototype_ `FVector3f GetAngularVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L228 _public prototype_ `FVector3f GetScalarVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L229 _public prototype_ `FVector3f GetDirection(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L230 _public prototype_ `FTransform3f GetTransform(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L231 _public prototype_ `void GetEvent(bool& bOutTimeUntilEventKnown, float& OutTimeUntilEvent, const int32 FrameIdx, const int32 AttributeIdx) const;`
- L233 _public member_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> AttributeTypes;`
- L234 _public member_ `TLearningArrayView<1, const FName> AttributeNames;`
- L235 _public member_ `TLearningArrayView<1, const int32> AttributeOffsets;`
- L236 _public member_ `TLearningArrayView<2, const bool> AttributeActive;`
- L237 _public member_ `TLearningArrayView<2, const float> AttributeData;`

#### struct `UE::AnimDatabase::FPoseAttributeDataView`  
`struct FPoseAttributeDataView`  
_L241-290_
- desc: Non-Const View of Pose Attribute Data
- L243 _public prototype_ `int32 GetFrameNum() const;`
- L244 _public prototype_ `int32 GetAttributeNum() const;`
- L245 _public prototype_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> GetAttributeTypes() const;`
- L246 _public prototype_ `TLearningArrayView<1, const FName> GetAttributeNames() const;`
- L248 _public prototype_ `FPoseAttributeDataConstView ConstView() const;`
- L249 _public prototype_ `FPoseAttributeDataView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L251 _public prototype_ `EAnimDatabaseAttributeType GetAttributeType(const int32 AttributeIdx) const;`
- L252 _public prototype_ `FName GetAttributeName(const int32 AttributeIdx) const;`
- L253 _public prototype_ `int32 GetAttributeOffset(const int32 AttributeIdx) const;`
- L254 _public prototype_ `int32 GetAttributeSize(const int32 AttributeIdx) const;`
- L255 _public prototype_ `bool GetAttributeActive(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L257 _public prototype_ `bool GetBool(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L258 _public prototype_ `float GetFloat(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L259 _public prototype_ `float GetAngle(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L260 _public prototype_ `FVector3f GetLocation(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L261 _public prototype_ `FQuat4f GetRotation(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L262 _public prototype_ `FVector3f GetScale(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L263 _public prototype_ `FVector3f GetLinearVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L264 _public prototype_ `FVector3f GetAngularVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L265 _public prototype_ `FVector3f GetScalarVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L266 _public prototype_ `FVector3f GetDirection(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L267 _public prototype_ `FTransform3f GetTransform(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L268 _public prototype_ `void GetEvent(bool& bOutTimeUntilEventKnown, float& OutTimeUntilEvent, const int32 FrameIdx, const int32 AttributeIdx) const;`
- L270 _public prototype_ `void SetAttributeActive(const int32 FrameIdx, const int32 AttributeIdx, const bool bActive) const;`
- L272 _public prototype_ `void SetBool(const int32 FrameIdx, const int32 AttributeIdx, const bool bValue) const;`
- L273 _public prototype_ `void SetFloat(const int32 FrameIdx, const int32 AttributeIdx, const float Value) const;`
- L274 _public prototype_ `void SetAngle(const int32 FrameIdx, const int32 AttributeIdx, const float Value) const;`
- L275 _public prototype_ `void SetLocation(const int32 FrameIdx, const int32 AttributeIdx, const FVector3f Location) const;`
- L276 _public prototype_ `void SetRotation(const int32 FrameIdx, const int32 AttributeIdx, const FQuat4f Rotation) const;`
- L277 _public prototype_ `void SetScale(const int32 FrameIdx, const int32 AttributeIdx, const FVector3f Scale) const;`
- L278 _public prototype_ `void SetLinearVelocity(const int32 FrameIdx, const int32 AttributeIdx, const FVector3f LinearVelocity) const;`
- L279 _public prototype_ `void SetAngularVelocity(const int32 FrameIdx, const int32 AttributeIdx, const FVector3f AngularVelocity) const;`
- L280 _public prototype_ `void SetScalarVelocity(const int32 FrameIdx, const int32 AttributeIdx, const FVector3f ScalarVelocity) const;`
- L281 _public prototype_ `void SetDirection(const int32 FrameIdx, const int32 AttributeIdx, const FVector3f Direction) const;`
- L282 _public prototype_ `void SetTransform(const int32 FrameIdx, const int32 AttributeIdx, const FTransform3f Transform) const;`
- L283 _public prototype_ `void SetEvent(const int32 FrameIdx, const int32 AttributeIdx, const bool bTimeUntilEventKnown, const float TimeUntilEvent) const;`
- L285 _public member_ `TLearningArrayView<1, EAnimDatabaseAttributeType> AttributeTypes;`
- L286 _public member_ `TLearningArrayView<1, FName> AttributeNames;`
- L287 _public member_ `TLearningArrayView<1, int32> AttributeOffsets;`
- L288 _public member_ `TLearningArrayView<2, bool> AttributeActive;`
- L289 _public member_ `TLearningArrayView<2, float> AttributeData;`

#### struct `UE::AnimDatabase::FPoseAttributeData`  
`struct FPoseAttributeData`  
_L293-333_
- desc: Pose Attribute Data
- L295 _public prototype_ `int32 GetFrameNum() const;`
- L296 _public prototype_ `int32 GetAttributeNum() const;`
- L297 _public prototype_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> GetAttributeTypes() const;`
- L298 _public prototype_ `TLearningArrayView<1, const FName> GetAttributeNames() const;`
- L300 _public prototype_ `void Resize(const int32 FrameNum, const TLearningArrayView<1, const EAnimDatabaseAttributeType> InAttributeTypes, const TLearningArrayView<1, const FName> InAttributeNames);`
- L301 _public prototype_ `bool IsEmpty() const;`
- L302 _public prototype_ `void Empty();`
- L304 _public prototype_ `FPoseAttributeDataView View();`
- L305 _public prototype_ `FPoseAttributeDataConstView ConstView() const;`
- L306 _public prototype_ `FPoseAttributeDataView Slice(const int32 FrameStart, const int32 FrameNum);`
- L307 _public prototype_ `FPoseAttributeDataConstView ConstSlice(const int32 FrameStart, const int32 FrameNum) const;`
- L309 _public prototype_ `EAnimDatabaseAttributeType GetAttributeType(const int32 AttributeIdx) const;`
- L310 _public prototype_ `FName GetAttributeName(const int32 AttributeIdx) const;`
- L311 _public prototype_ `int32 GetAttributeOffset(const int32 AttributeIdx) const;`
- L312 _public prototype_ `int32 GetAttributeSize(const int32 AttributeIdx) const;`
- L313 _public prototype_ `bool GetAttributeActive(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L315 _public prototype_ `bool GetBool(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L316 _public prototype_ `float GetFloat(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L317 _public prototype_ `float GetAngle(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L318 _public prototype_ `FVector3f GetLocation(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L319 _public prototype_ `FQuat4f GetRotation(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L320 _public prototype_ `FVector3f GetScale(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L321 _public prototype_ `FVector3f GetLinearVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L322 _public prototype_ `FVector3f GetAngularVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L323 _public prototype_ `FVector3f GetScalarVelocity(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L324 _public prototype_ `FVector3f GetDirection(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L325 _public prototype_ `FTransform3f GetTransform(const int32 FrameIdx, const int32 AttributeIdx) const;`
- L326 _public prototype_ `void GetEvent(bool& bOutTimeUntilEventKnown, float& OutTimeUntilEvent, const int32 FrameIdx, const int32 AttributeIdx) const;`
- L328 _public member_ `TLearningArray<1, EAnimDatabaseAttributeType> AttributeTypes;`
- L329 _public member_ `TLearningArray<1, FName> AttributeNames;`
- L330 _public member_ `TLearningArray<1, int32> AttributeOffsets;`
- L331 _public member_ `TLearningArray<2, bool> AttributeActive;`
- L332 _public member_ `TLearningArray<2, float> AttributeData;`

#### struct `UE::AnimDatabase::FPoseDataConstView`  
`struct FPoseDataConstView`  
_L338-351_
- desc: Const View of Pose Data
- L340 _public prototype_ `int32 GetFrameNum() const;`
- L341 _public prototype_ `int32 GetBoneNum() const;`
- L342 _public prototype_ `int32 GetAttributeNum() const;`
- L343 _public prototype_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> GetAttributeTypes() const;`
- L344 _public prototype_ `TLearningArrayView<1, const FName> GetAttributeNames() const;`
- L346 _public prototype_ `FPoseDataConstView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L348 _public member_ `FPoseRootDataConstView RootData;`
- L349 _public member_ `FPoseLocalBoneDataConstView LocalBoneData;`
- L350 _public member_ `FPoseAttributeDataConstView AttributeData;`

#### struct `UE::AnimDatabase::FPoseDataView`  
`struct FPoseDataView`  
_L354-367_
- desc: Non-Const View of Pose Data
- L356 _public prototype_ `int32 GetFrameNum() const;`
- L357 _public prototype_ `int32 GetBoneNum() const;`
- L358 _public prototype_ `int32 GetAttributeNum() const;`
- L359 _public prototype_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> GetAttributeTypes() const;`
- L360 _public prototype_ `TLearningArrayView<1, const FName> GetAttributeNames() const;`
- L362 _public prototype_ `FPoseDataView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L364 _public member_ `FPoseRootDataView RootData;`
- L365 _public member_ `FPoseLocalBoneDataView LocalBoneData;`
- L366 _public member_ `FPoseAttributeDataView AttributeData;`

#### struct `UE::AnimDatabase::FPoseData`  
`struct FPoseData`  
_L370-390_
- desc: Full Pose Data containing root data, local bone transforms, and attribute data
- L372 _public prototype_ `int32 GetFrameNum() const;`
- L373 _public prototype_ `int32 GetBoneNum() const;`
- L374 _public prototype_ `int32 GetAttributeNum() const;`
- L375 _public prototype_ `TLearningArrayView<1, const EAnimDatabaseAttributeType> GetAttributeTypes() const;`
- L376 _public prototype_ `TLearningArrayView<1, const FName> GetAttributeNames() const;`
- L378 _public prototype_ `void Resize(const int32 FrameNum, const int32 BoneNum, const TLearningArrayView<1, const EAnimDatabaseAttributeType> InAttributeTypes, const TLearningArrayView<1, const FName> InAttributeNames);`
- L379 _public prototype_ `bool IsEmpty() const;`
- L380 _public prototype_ `void Empty();`
- L382 _public prototype_ `FPoseDataView View();`
- L383 _public prototype_ `FPoseDataConstView ConstView() const;`
- L384 _public prototype_ `FPoseDataView Slice(const int32 FrameStart, const int32 FrameNum);`
- L385 _public prototype_ `FPoseDataConstView ConstSlice(const int32 FrameStart, const int32 FrameNum) const;`
- L387 _public member_ `FPoseRootData RootData;`
- L388 _public member_ `FPoseLocalBoneData LocalBoneData;`
- L389 _public member_ `FPoseAttributeData AttributeData;`

#### struct `UE::AnimDatabase::PoseData::ContactPinning::FContactStateConstView`  
`struct FContactStateConstView`  
_L809-822_
- desc: Const View of Contact States
- L811 _public function_ `int32 GetFrameNum() const`
- L812 _public function_ `int32 GetBoneNum() const`
- L813 _public prototype_ `FContactStateConstView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L815 _public member_ `TLearningArrayView<2, const bool> Locked;`
- L816 _public member_ `TLearningArrayView<2, const float> TimeSinceTransition;`
- L817 _public member_ `TLearningArrayView<2, const FVector> Position;`
- L818 _public member_ `TLearningArrayView<2, const FVector3f> Velocity;`
- L819 _public member_ `TLearningArrayView<2, const FVector> Point;`
- L820 _public member_ `TLearningArrayView<2, const FVector3f> OffsetPosition;`
- L821 _public member_ `TLearningArrayView<2, const FVector3f> OffsetVelocity;`

#### struct `UE::AnimDatabase::PoseData::ContactPinning::FContactStateView`  
`struct FContactStateView`  
_L825-838_
- desc: Non-Const View of Contact States
- L827 _public function_ `int32 GetFrameNum() const`
- L828 _public function_ `int32 GetBoneNum() const`
- L829 _public prototype_ `FContactStateView Slice(const int32 FrameStart, const int32 FrameNum) const;`
- L831 _public member_ `TLearningArrayView<2, bool> Locked;`
- L832 _public member_ `TLearningArrayView<2, float> TimeSinceTransition;`
- L833 _public member_ `TLearningArrayView<2, FVector> Position;`
- L834 _public member_ `TLearningArrayView<2, FVector3f> Velocity;`
- L835 _public member_ `TLearningArrayView<2, FVector> Point;`
- L836 _public member_ `TLearningArrayView<2, FVector3f> OffsetPosition;`
- L837 _public member_ `TLearningArrayView<2, FVector3f> OffsetVelocity;`

#### struct `UE::AnimDatabase::PoseData::ContactPinning::FContactState`  
`struct FContactState`  
_L841-861_
- desc: Contact State data
- L843 _public function_ `int32 GetFrameNum() const`
- L844 _public function_ `int32 GetBoneNum() const`
- L845 _public prototype_ `void Resize(const int32 FrameNum, const int32 BoneNum);`
- L846 _public prototype_ `bool IsEmpty() const;`
- L847 _public prototype_ `void Empty();`
- L849 _public prototype_ `FContactStateView View();`
- L850 _public prototype_ `FContactStateConstView ConstView() const;`
- L851 _public prototype_ `FContactStateView Slice(const int32 FrameStart, const int32 FrameNum);`
- L852 _public prototype_ `FContactStateConstView ConstSlice(const int32 FrameStart, const int32 FrameNum) const;`
- L854 _public member_ `TLearningArray<2, bool> Locked;`
- L855 _public member_ `TLearningArray<2, float> TimeSinceTransition;`
- L856 _public member_ `TLearningArray<2, FVector> Position;`
- L857 _public member_ `TLearningArray<2, FVector3f> Velocity;`
- L858 _public member_ `TLearningArray<2, FVector> Point;`
- L859 _public member_ `TLearningArray<2, FVector3f> OffsetPosition;`
- L860 _public member_ `TLearningArray<2, FVector3f> OffsetVelocity;`

#### struct `UE::AnimDatabase::PoseData::ContactPinning::FContactPinningSettings`  
`struct FContactPinningSettings`  
_L894-904_
- desc: Contact pinning settings
- L896 _public member_ `float BlendTime = 0.25f;`
- L897 _public member_ `float LockRadius = 5.0f;`
- L898 _public member_ `float UnlockRadius = 20.0f;`
- L899 _public member_ `float ContactHeight = 0.0f;`
- L900 _public member_ `float MinToeHeight = 0.0f;`
- L901 _public member_ `float MinAnkleHeight = 7.0f;`
- L902 _public member_ `float ToeLength = 5.0f;`
- L903 _public member_ `float HyperExtensionLimit = 0.5f;`

#### struct `FAnimDatabasePoseState`  
`struct FAnimDatabasePoseState`  
_L953-971_
- reflection: `USTRUCT(BlueprintType)`
- desc: Provides a simple Blueprint-accessible wrapper around Pose Data. This is a struct that can be used to provide access to pose data to blueprint code. Since it references a batch of pose data the PoseIdx variable can be set to say which pose the blueprint code is accessing. This also records the DeltaTime and the previous pose data since this allows for the detection of the occurrence (and prediction) of events in the attribute data.
- L960 _public prototype_ `bool IsValid() const;` — Check if the given pose state is valid
- L963 _public prototype_ `void Init(const UE::AnimDatabase::FPoseDataConstView& PoseData, const TLearningArrayView<1, const int32> InBoneParents);` — Initialize the pose state
- L967 _public member_ `int32 PoseIdx = 0;`
- L968 _public member_ `TLearningArray<1, int32> BoneParents;`
- L969 _public member_ `TSharedPtr<UE::AnimDatabase::FPoseData, ESPMode::ThreadSafe> CurrPoseData;`
- L970 _public member_ `TSharedPtr<UE::AnimDatabase::FPoseGlobalBoneData, ESPMode::ThreadSafe> PoseGlobalBoneData;`

#### class `UAnimDatabasePoseStateLibrary`  
`class UAnimDatabasePoseStateLibrary : public UBlueprintFunctionLibrary`  
_L975-1113_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: This provides a blueprint interface to the pose state.
- L983 _public prototype_ `static FAnimDatabasePoseState MakePoseState();` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Construct a new Empty Pose State
- L987 _public prototype_ `static void PoseStateCopy(UPARAM(ref) FAnimDatabasePoseState& OutPoseState, const FAnimDatabasePoseState& InPoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase", meta=(NonBlueprintThreadSafe))` — Copy a PoseState
- L991 _public prototype_ `static FTransform PoseStateRootTransform(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root transform of the pose state
- L995 _public prototype_ `static FVector PoseStateRootLocation(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root location of the pose state
- L999 _public prototype_ `static FRotator PoseStateRootRotation(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root rotation of the pose state
- L1003 _public prototype_ `static void PoseStateRootLocationAndRotation(FVector& OutRootLocation, FRotator& OutRootRotation, const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root location and rotation of the pose state
- L1007 _public prototype_ `static FVector PoseStateRootScale3D(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root scale of the pose state
- L1011 _public prototype_ `static FVector PoseStateRootDirection(const FAnimDatabasePoseState& PoseState, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f));` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root direction of the pose state
- L1015 _public prototype_ `static FVector PoseStateRootLinearVelocity(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root linear velocity of the pose state
- L1019 _public prototype_ `static FVector PoseStateRootAngularVelocity(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root angular velocity of the pose state
- L1023 _public prototype_ `static FVector PoseStateRootScalarVelocity(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the root scalar velocity of the pose state
- L1027 _public prototype_ `static FVector PoseStateBoneWorldLocation(const FAnimDatabasePoseState& PoseState, const int32 BoneIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the world location of a given bone in the pose state
- L1031 _public prototype_ `static FRotator PoseStateBoneWorldRotation(const FAnimDatabasePoseState& PoseState, const int32 BoneIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the world rotation of a given bone in the pose state
- L1035 _public prototype_ `static FVector PoseStateBoneWorldLinearVelocity(const FAnimDatabasePoseState& PoseState, const int32 BoneIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the world linear velocity of a given bone in the pose state
- L1039 _public prototype_ `static FTransform PoseStateBoneWorldTransform(const FAnimDatabasePoseState& PoseState, const int32 BoneIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the world transform of a given bone in the pose state
- L1043 _public prototype_ `static int32 PoseStateAttributeNum(const FAnimDatabasePoseState& PoseState);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get if the number of attributes in the pose state
- L1047 _public prototype_ `static bool PoseStateIsAttributeActive(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get if the given attribute is active in the pose state
- L1051 _public prototype_ `static FName PoseStateAttributeName(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get if the given attribute name in the pose state
- L1055 _public prototype_ `static EAnimDatabaseAttributeType PoseStateAttributeType(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get if the given attribute type in the pose state
- L1059 _public prototype_ `static FString PoseStateAttributeString(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Gets a string representation of the given attribute in the pose state
- L1063 _public prototype_ `static bool PoseStateBoolAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a bool
- L1067 _public prototype_ `static float PoseStateFloatAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a float
- L1071 _public prototype_ `static float PoseStateAngleAttributeDegrees(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a angle in degrees
- L1075 _public prototype_ `static float PoseStateAngleAttributeRadians(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a angle in radians
- L1079 _public prototype_ `static FVector PoseStateLocationAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a location
- L1083 _public prototype_ `static FRotator PoseStateRotationAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a rotation
- L1084 _public prototype_ `static FQuat PoseStateRotationAttributeAsQuat(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);`
- L1088 _public prototype_ `static FVector PoseStateScaleAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a scale
- L1092 _public prototype_ `static FVector PoseStateLinearVelocityAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a linear velocity
- L1096 _public prototype_ `static FVector PoseStateAngularVelocityAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as an angular velocity
- L1100 _public prototype_ `static FVector PoseStateScalarVelocityAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a scalar velocity
- L1104 _public prototype_ `static FVector PoseStateDirectionAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a direction
- L1108 _public prototype_ `static FTransform PoseStateTransformAttribute(const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as a transform
- L1112 _public prototype_ `static void PoseStateEventAttribute(bool& bOutTimeUntilEventKnown, float& OutTimeUntilEvent, const FAnimDatabasePoseState& PoseState, const int32 AttributeIndex);` — `UFUNCTION(BlueprintPure, Category = "AnimDatabase")` — Get the given attribute as an event

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMDATABASE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L394 _namespace_ `namespace PoseData` (scope `UE::AnimDatabase`)
- L397 _prototype_ `void Reset(const FPoseRootDataView& OutRootData);` (scope `UE::AnimDatabase::PoseData`) — Resets root data
- L400 _prototype_ `void Reset(const FPoseLocalBoneDataView& OutPoseLocalBoneData, const TLearningArrayView<1, const FTransform> ReferenceTransforms, const TLearningArrayView<1, const int32> IgnoreBoneIndices = {});` (scope `UE::AnimDatabase::PoseData`) — Resets local bone data to the reference pose
- L403 _prototype_ `void Reset(const FPoseAttributeDataView& OutAttributeData);` (scope `UE::AnimDatabase::PoseData`) — Reset attribute data to zero
- L406 _prototype_ `void Reset(const FPoseDataView& OutPoseData, const TLearningArrayView<1, const FTransform> ReferenceTransforms, const TLearningArrayView<1, const int32> IgnoreBoneIndices = {});` (scope `UE::AnimDatabase::PoseData`) — Reset pose data to the reference pose
- L410 _prototype_ `void Copy(const FPoseRootDataView& OutRootData, const FPoseRootDataConstView& InRootData);` (scope `UE::AnimDatabase::PoseData`) — Copy root data
- L413 _prototype_ `void Copy(const FPoseLocalBoneDataView& OutPoseLocalBoneData, const FPoseLocalBoneDataConstView& InPoseLocalBoneData);` (scope `UE::AnimDatabase::PoseData`) — Copy local pose data
- L416 _prototype_ `void Copy(const FPoseAttributeDataView& OutAttributeData, const FPoseAttributeDataConstView& InAttributeData);` (scope `UE::AnimDatabase::PoseData`) — Copy attribute data
- L419 _prototype_ `void Copy(const FPoseDataView& OutPoseData, const FPoseDataConstView& InPoseData);` (scope `UE::AnimDatabase::PoseData`) — Copy one pose to another
- L434 _prototype_ `void ForwardKinematics( const FPoseGlobalBoneDataView& OutPoseGlobalBoneData, const FPoseLocalBoneDataConstView& InPoseLocalBoneData, const FPoseRootDataConstView& InPoseRootData, const TLearningArrayView<1, const int32> BoneParents, const UE::Learning::FIndexSet BoneIndices);` (scope `UE::AnimDatabase::PoseData`) — Compute Forward Kinematics on a subset of bones to produce global transforms from local transforms. The OutPoseGlobalBoneData and InPoseLocalBoneData parameters are expected to be allocated for just the subset of bones being used, which is then provided by BoneIndices. The BoneParents array however should still refer to bone indices in the full reference skeleton. All required parent bones must be present in BoneIndices. @param OutPoseGlobalBoneData		Output Global Bone Transforms of shape (FrameNum, BoneIndicesNum) @param InPoseLocalBoneData		Input Local Bone Transforms of shape (FrameNum, BoneIndicesNum) @param InPoseRootData			Input Root Transforms of shape (FrameNum) @param BoneParents				Input Bone Parents Array of shape (BoneNum) @param BoneIndices				Input Bone Indices Array of shape (BoneIndicesNum)
- L469 _prototype_ `void ForwardKinematicsPartial( const FPoseGlobalBoneDataView& OutPoseGlobalBoneData, const FPoseLocalBoneDataConstView& InPoseLocalBoneData, const FPoseRootDataConstView& InPoseRootData, const TLearningArrayView<1, const int32> BoneParents, const UE::Learning::FIndexSet BoneIndices, const UE::Learning::FIndexSet BonesToUpdate);` (scope `UE::AnimDatabase::PoseData`) — Compute Forward Kinematics on a subset of bones to produce global transforms from local transforms. The OutPoseGlobalBoneData and InPoseLocalBoneData parameters are expected to be allocated for just the subset of bones being used, which is then provided by BoneIndices. The BoneParents array however should still refer to bone indices in the full reference skeleton. All required parent bones must be present in BoneIndices. @param OutPoseGlobalBoneData		Output Global Bone Transforms of shape (FrameNum, BoneIndicesNum) @param InPoseLocalBoneData		Input Local Bone Transforms of shape (FrameNum, BoneIndicesNum) @param InPoseRootData			Input Root Transforms of shape (FrameNum) @param BoneParents				Input Bone Parents Array of shape (BoneNum) @param BoneIndices				Input Bone Indices Array of shape (BoneIndicesNum) @param BonesToUpdate				Which bones to compute the global transforms for
- L486 _prototype_ `void ComputeUsedBones( TArray<int32>& OutBoneIndices, const FPoseLocalBoneDataConstView& InPoseLocalBoneData, const TLearningArrayView<1, const FTransform> ReferenceTransforms, const bool bRootIsAlwaysUsed = true, const float Eps = UE_KINDA_SMALL_NUMBER);` (scope `UE::AnimDatabase::PoseData`) — Computes the bone indices which are different from the reference pose transforms in the given pose data @param OutBoneIndices			Output used bone indices @param InPoseLocalBoneData		Input Local Bone Transforms of shape (FrameNum, BoneNum) @param ReferenceTransforms		Reference pose transforms (BoneNum) @param bRootIsAlwaysUsed			If to always include the root bone (bone 0) in the used bones @param Eps						Epsilon to use when comparing bone transforms
- L517 _prototype_ `void ComputeDefaultBoneValuesAndIndices( TLearningArrayView<1, FVector3f> OutDefaultBoneLocations, TLearningArrayView<1, FQuat4f> OutDefaultBoneRotations, TLearningArrayView<1, FVector3f> OutDefaultBoneScales, TArray<int32>& OutBoneLocationIndices, TArray<int32>& OutBoneRotationIndices, TArray<int32>& OutBoneScaleIndices, const FPoseLocalBoneDataConstView& InPoseLocalBoneData, const TLearningArrayView<1, const FTransform> ReferenceTransforms, const TLearningArrayView<1, const int32> ExcludedBoneIndices, const float BoneLocationThreshold = 1.0f,` (scope `UE::AnimDatabase::PoseData`) — Computes the default bone values and required bone indices for some given pose data. Here, the default bone values will be their average/mean in the dataset, unless they are included in ExcludedBoneIndices, in which case they will be the transforms in the reference pose. The required bone indices will be all of the bones which have some variation in the dataset (i.e. are not just described by the mean value). This is found by computing the standard deviation of each of the bone properties and checking if they are below the given thresholds. These thresholds are important because sometimes things like mirroring and compression can produce very small numerical variation in the data which does not really imply any visual difference and so these bones are not required to be predicted. @param OutDefaultBoneLocations	Output default bone locations (BoneNum) @param OutDefaultBoneRotations	Output default bone rotations (BoneNum) @param OutDefaultBoneScales		Output default bone scales (BoneNum) @param OutBoneLocationIndices	Output required bone location indices @param OutBoneRotationIndices	Output required bone rotation indices @param OutBoneScaleIndices		Output required bone scale indices @param InPoseLocalBoneData		Input Local Bone Transforms of shape (FrameNum, BoneNum) @param ReferenceTransforms		Reference pose transforms (BoneNum) @param ExcludedBoneIndices		Bones in exclude. Will use the reference transform as the default. @param BoneLocationThreshold		Threshold for including a b
- L532 _prototype_ `void ComputeRequiredBoneIndices( TArray<int32>& OutBoneRequiredIndices, const TLearningArrayView<1, const int32> BoneLocationIndices, const TLearningArrayView<1, const int32> BoneRotationIndices, const TLearningArrayView<1, const int32> BoneScaleIndices);` (scope `UE::AnimDatabase::PoseData`) — Computes the full set of required bones given the individual bones required for location, rotation, and scales
- L539 _prototype_ `int32 AttributeTypeEncodingSize(const EAnimDatabaseAttributeType Type);` (scope `UE::AnimDatabase::PoseData`) — Gets the encoding size for a given attribute type
- L542 _prototype_ `int32 PoseVectorSize( const int32 BoneLocationNum, const int32 BoneRotationNum, const int32 BoneScaleNum, const TLearningArrayView<1, const EAnimDatabaseAttributeType> AttributeTypes);` (scope `UE::AnimDatabase::PoseData`) — Gets the pose vector size for a given set of bones and attributes.
- L549 _prototype_ `void SetDefaultPoseData( const FPoseDataView& OutPoseData, const TLearningArrayView<1, const FVector3f> DefaultBoneLocations, const TLearningArrayView<1, const FQuat4f> DefaultBoneRotations, const TLearningArrayView<1, const FVector3f> DefaultBoneScales);` (scope `UE::AnimDatabase::PoseData`) — Initialize a pose vector with some set of default bones.
- L564 _prototype_ `void ToPoseVectors( const TLearningArrayView<2, float> OutPoseVectors, const FPoseDataConstView& InPoseData, const Learning::FIndexSet BoneLocationIndices, const Learning::FIndexSet BoneRotationIndices, const Learning::FIndexSet BoneScaleIndices, const TLearningArrayView<1, const FVector3f> DefaultBoneLocations, const TLearningArrayView<1, const FQuat4f> DefaultBoneRotations, const TLearningArrayView<1, const FVector3f> DefaultBoneScales);` (scope `UE::AnimDatabase::PoseData`) — Convert a pose to a pose vector.
- L587 _prototype_ `void FromPoseVectors( const FPoseDataView& OutPoseData, const TLearningArrayView<2, const float> InPoseVectors, const TLearningArrayView<1, const FVector> InRootLocations, const TLearningArrayView<1, const FQuat4f> InRootRotations, const Learning::FIndexSet BoneLocationIndices, const Learning::FIndexSet BoneRotationIndices, const Learning::FIndexSet BoneScaleIndices, const TLearningArrayView<1, const FVector3f> DefaultBoneLocations, const TLearningArrayView<1, const FQuat4f> DefaultBoneRotations, const TLearningArrayView<1, const FVector3f> DefaultBoneScales);` (scope `UE::AnimDatabase::PoseData`) — Get a pose from a pose vector.
- L614 _prototype_ `void FitPoseVectorNormalization( TLearningArrayView<1, float> OutPoseVectorOffset, TLearningArrayView<1, float> OutPoseVectorScale, const TLearningArrayView<2, const float> InPoseVectors, const int32 BoneLocationNum, const int32 BoneRotationNum, const int32 BoneScaleNum, const TLearningArrayView<1, const EAnimDatabaseAttributeType> AttributeTypes);` (scope `UE::AnimDatabase::PoseData`) — Fits normalization offset and scale to a set of pose vectors
- L624 _prototype_ `void ComputePoseVectorWeightsFromDescendantBoneLengths( TLearningArrayView<1, float> OutPoseVectorWeights, const TLearningArrayView<1, const FTransform> ReferenceTransforms, const TLearningArrayView<1, const int32> BoneParents, const Learning::FIndexSet BoneLocationIndices, const Learning::FIndexSet BoneRotationIndices, const Learning::FIndexSet BoneScaleIndices, const float RootWeight = 10.0f);` (scope `UE::AnimDatabase::PoseData`) — Compute pose vector weights using descendant bone lengths
- L634 _prototype_ `void ComputePoseVectorWeightsCylinderApprox( TLearningArrayView<1, float> OutPoseVectorWeights, const TLearningArrayView<1, const FTransform> ReferenceTransforms, const TLearningArrayView<1, const int32> BoneParents, const Learning::FIndexSet RequiredIndices, const Learning::FIndexSet BoneLocationIndices, const Learning::FIndexSet BoneRotationIndices, const Learning::FIndexSet BoneScaleIndices, const float RootWeight = 10.0f, const float BoneBaseWeightMultiplier = 1.0f, const float AttributeWeight = 10.0f);` (scope `UE::AnimDatabase::PoseData`) — Compute pose vector weights that allow for error compensation down the joint chain
- L647 _prototype_ `void MakeLooped( const FPoseDataView& InOutPoseData, const FFrameRate FrameRate, const float StartEndRatio, const float BlendInTime, const float BlendOutTime);` (scope `UE::AnimDatabase::PoseData`) — Makes the provided pose data loop seamlessly
- L655 _prototype_ `void PatchInterpolate(const FPoseDataView& InOutPoseData, const FFrameRate FrameRate, const bool bApplyToRoot, const UE::Learning::FIndexSet Bones);` (scope `UE::AnimDatabase::PoseData`) — Replaces the given bones in the data in the middle with an interpolation between the first and last frames
- L658 _prototype_ `void RecomputeVelocities(const FPoseRootDataView& InOutRootData, const float DeltaTime);` (scope `UE::AnimDatabase::PoseData`) — Recomputes Velocities using finite difference assuming the first dimension is frames
- L661 _prototype_ `void Teleport( const FPoseRootDataView& InOutRootData, const TLearningArrayView<1, const FVector> RootLocations, const TLearningArrayView<1, const FQuat4f> RootRotations);` (scope `UE::AnimDatabase::PoseData`) — Teleport some pose data to a new location and rotation. Adjusts the velocities appropriately.
- L667 _prototype_ `void BlendRoot( const FPoseRootDataView& OutPoseData, const FPoseRootDataConstView& InPoseA, const FPoseRootDataConstView& InPoseB, const float Alpha);` (scope `UE::AnimDatabase::PoseData`) — Blend root data using a given alpha value
- L674 _prototype_ `void IntegrateRoot(const FPoseRootDataView& InOutRootData, const float DeltaTime);` (scope `UE::AnimDatabase::PoseData`) — Integrates the root location and rotation using the velocities.
- L677 _prototype_ `void BlendVia( const FPoseLocalBoneDataView& OutPoseData, const TLearningArrayView<2, FQuat4f> InOutViaRotations, const FPoseLocalBoneDataConstView& InPoseA, const FPoseLocalBoneDataConstView& InPoseB, const float Alpha);` (scope `UE::AnimDatabase::PoseData`) — Blend pose data of two poses, ensuring to blend via the given set of rotations. Updates the blend via rotations.
- L685 _prototype_ `void FitExtrapolationHalfLives( const TLearningArrayView<2, FVector3f> OutBoneLocationHalfLives, const TLearningArrayView<2, FVector3f> OutBoneRotationHalfLives, const TLearningArrayView<2, FVector3f> OutBoneScaleHalfLives, const FPoseLocalBoneDataConstView& InPoseSource, const FPoseLocalBoneDataConstView& InPoseTarget, const float ExtrapolationHalfLife = 1.0f, const float ExtrapolationHalfLifeMin = 0.05f, const float ExtrapolationHalfLifeMax = 1.0f, const float MaxLinearVelocity = 500.0f, const float MaxAngularVelocity = UE_TWO_PI, const float MaxScalarVelocity = 4.0f);` (scope `UE::AnimDatabase::PoseData`) — Fit extrapolation half-lives given source and target pose data
- L699 _prototype_ `void ExtrapolateRoot( const FPoseRootDataView& OutPoseData, const FPoseRootDataConstView& InPoseData, const float Time, const float RootHalfLife = 1.0f);` (scope `UE::AnimDatabase::PoseData`) — Extrapolate the root data forward given a half-life
- L706 _prototype_ `void Extrapolate( const FPoseLocalBoneDataView& OutPoseData, const FPoseLocalBoneDataConstView& InPoseData, const float Time, const TLearningArrayView<2, const FVector3f> BoneLocationHalfLives, const TLearningArrayView<2, const FVector3f> BoneRotationHalfLives, const TLearningArrayView<2, const FVector3f> BoneScaleHalfLives);` (scope `UE::AnimDatabase::PoseData`) — Extrapolate pose data forward in time given sets of half-lives
- L715 _prototype_ `void FitInertializationOffsetsRoot( const FPoseRootDataView& OutOffsetPose, const FPoseRootDataConstView& InPoseSource, const FPoseRootDataConstView& InPoseTarget);` (scope `UE::AnimDatabase::PoseData`) — Fit inertialization offsets to the provided root data
- L721 _prototype_ `void ApplyInertializationOffsetsRoot( const FPoseRootDataView& OutFinalPose, const FPoseRootDataConstView& InOffsetPose, const FPoseRootDataConstView& InPoseTarget, const float BlendTime, const float BlendDuration);` (scope `UE::AnimDatabase::PoseData`) — Apply inertialization offsets to the given root data
- L729 _prototype_ `void FitInertializationOffsets( const FPoseLocalBoneDataView& OutOffsetPose, const FPoseLocalBoneDataConstView& InPoseSource, const FPoseLocalBoneDataConstView& InPoseTarget);` (scope `UE::AnimDatabase::PoseData`) — Fit inertialization offsets to the provided pose data
- L735 _prototype_ `void ApplyInertializationOffsets( const FPoseLocalBoneDataView& OutFinalPose, const FPoseLocalBoneDataConstView& InOffsetPose, const FPoseLocalBoneDataConstView& InPoseTarget, const float BlendTime, const float BlendDuration);` (scope `UE::AnimDatabase::PoseData`) — Apply inertialization offsets to the given pose data
- L743 _prototype_ `void FitInertializationOffsetsAttributes( const FPoseAttributeDataView& OutOffsetPose, const FPoseAttributeDataConstView& InPoseSource, const FPoseAttributeDataConstView& InPoseTarget);` (scope `UE::AnimDatabase::PoseData`) — Fit inertialization offsets to the provided attribute data
- L749 _prototype_ `void ApplyInertializationOffsetsAttributes( const FPoseAttributeDataView& OutFinalPose, const FPoseAttributeDataConstView& InOffsetPose, const FPoseAttributeDataConstView& InPoseTarget, const float BlendTime, const float BlendDuration);` (scope `UE::AnimDatabase::PoseData`) — Apply inertialization offsets to the given attribute data
- L757 _prototype_ `void UpdateInplaceUsingVelocityIntegrationMix( const FPoseRootDataView& InOutPose, const FPoseRootDataConstView& InTargetPose, const float DeltaTime, const float VelocityAlpha = 0.25f);` (scope `UE::AnimDatabase::PoseData`) — Update root data in-place using a mix of integrating the velocity and the next target pose
- L764 _prototype_ `void UpdateInplaceUsingVelocityIntegrationMix( const FPoseLocalBoneDataView& InOutPose, const FPoseLocalBoneDataConstView& InTargetPose, const float DeltaTime, const float VelocityAlpha = 0.25f);` (scope `UE::AnimDatabase::PoseData`) — Update pose data in-place using a mix of integrating the velocity and the next target pose
- L771 _prototype_ `void DampInplaceUsingVelocityIntegrationMix( const FPoseLocalBoneDataView& InOutPose, const FPoseLocalBoneDataConstView& InTargetPose, const float DeltaTime, const float PoseSmoothingTime = 0.2f);` (scope `UE::AnimDatabase::PoseData`) — Update pose data in-place using a mix of integrating the velocity and the next target pose
- L778 _prototype_ `void DampInplaceUsingAdaptiveVelocityIntegrationMix( const FPoseLocalBoneDataView& InOutPose, const FPoseLocalBoneDataConstView& InTargetPose, const float DeltaTime, const float MinPoseSmoothingTime = 0.0f, const float MaxPoseSmoothingTime = 0.25f, const float LinearVelocitySmoothingThreshold = 5.0f, const float AngularVelocitySmoothingThreshold = UE_PI / 8.0f, const float ScalarVelocitySmoothingThreshold = 0.5f);` (scope `UE::AnimDatabase::PoseData`) — Update pose data in-place using an adaptive mix of integrating the velocity and the next target pose based on the absolute velocity magnitude
- L789 _prototype_ `void DampFramesInplaceUsingAdaptiveVelocityIntegrationMix( const FPoseLocalBoneDataView& InOutPoses, const float DeltaTime, const float MinPoseSmoothingTime = 0.0f, const float MaxPoseSmoothingTime = 0.25f, const float LinearVelocitySmoothingThreshold = 5.0f, const float AngularVelocitySmoothingThreshold = UE_PI / 8.0f, const float ScalarVelocitySmoothingThreshold = 0.5f);` (scope `UE::AnimDatabase::PoseData`) — Update pose data representing a sequence of frames in-place using an adaptive mix of integrating the velocity and the next target pose based on the absolute velocity magnitude
- L799 _prototype_ `void DampAttributesInPlace( const FPoseAttributeDataView& InOutAttributes, const FPoseAttributeDataConstView& InTargetAttributes, const float DeltaTime, const float SmoothingTime);` (scope `UE::AnimDatabase::PoseData`) — Update attributes in-place damping them toward the target attributes with the given smoothing time
- L806 _namespace_ `namespace ContactPinning` (scope `UE::AnimDatabase::PoseData`)
- L864 _prototype_ `void ContactLookAtIK( FQuat4f& InOutBoneRotation, const FQuat4f GlobalParentRotation, const FQuat4f GlobalRotation, const FVector GlobalPosition, const FVector ChildPosition, const FVector TargetPosition, const float Eps = 1e-5f);` (scope `UE::AnimDatabase::PoseData::ContactPinning`) — Contact look-at IK helper function
- L874 _prototype_ `void ContactTwoBoneIK( FQuat4f& BoneRootLocalRotation, FQuat4f& BoneMidLocalRotation, const FVector BoneRoot, const FVector BoneMid, const FVector BoneEnd, const FVector Target, const FVector3f RotationAxis, const FQuat4f BoneRootGlobalRotation, const FQuat4f BoneMidGlobalRotation, const FQuat4f BoneParentGlobalRotation, const float MaxLengthBuffer = 1.0f);` (scope `UE::AnimDatabase::PoseData::ContactPinning`) — Contact two-bone IK helper function
- L888 _prototype_ `void ResetContactPinning( const FContactStateView& OutContactState, const FPoseGlobalBoneDataConstView& InPoseGlobalBoneData, const TArrayView<const int32> ToeBoneIndices);` (scope `UE::AnimDatabase::PoseData::ContactPinning`) — Resets the contact pinning state given the pose data and toe indices
- L907 _prototype_ `void UpdateContactPinning( const FContactStateView& InOutContactState, const FPoseGlobalBoneDataView& InOutPoseGlobalBoneData, const FPoseLocalBoneDataView& InOutPoseLocalBoneData, const FPoseRootDataConstView& InPoseRootData, const FPoseAttributeDataConstView& InPoseAttributeData, const TArrayView<const int32> InBoneParents, const TArrayView<const int32> ContactStateAttributeIndices, const TArrayView<const int32> PelvisBoneIndices, const TArrayView<const int32> HipBoneIndices, const TArrayView<const int32> KneeBoneIndices, const TArrayView<const int32> AnkleBoneIndices, const TArrayView<const int32> ToeBoneIndices, const TArrayView<const FVector3f> KneeSideVectors, const TArrayView<const FVector3f> ToeForwardVectors, const float DeltaTime, const FContactPinningSettings& Settings = FContactPinningSettings());` (scope `UE::AnimDatabase::PoseData::ContactPinning`) — Updates the contact pinning state using the provided pose data, bone indices, and settings
- L926 _prototype_ `void RemoveFootGroundPenetration( const FPoseGlobalBoneDataView& InOutPoseGlobalBoneData, const FPoseLocalBoneDataView& InOutPoseLocalBoneData, const FPoseRootDataConstView& InPoseRootData, const TArrayView<const int32> InBoneParents, const TArrayView<const int32> PelvisBoneIndices, const TArrayView<const int32> HipBoneIndices, const TArrayView<const int32> KneeBoneIndices, const TArrayView<const int32> AnkleBoneIndices, const TArrayView<const int32> ToeBoneIndices, const TArrayView<const FVector3f> KneeSideVectors, const TArrayView<const FVector3f> ToeForwardVectors, const FContactPinningSettings& Settings = FContactPinningSettings());` (scope `UE::AnimDatabase::PoseData::ContactPinning`) — Removes Foot-Ground penetration without pinning the feet
