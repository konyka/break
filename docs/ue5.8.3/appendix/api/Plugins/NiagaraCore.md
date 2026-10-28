# Plugins / NiagaraCore

- module root: `Plugins/FX/Niagara/Source/NiagaraCore`
- headers: 7; symbols: 157
- symbol kinds: class=4, delegate=1, enum=4, enumerator=102, function=18, member=7, prototype=15, struct=5, typedef=1
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject, VectorVM
- PublicIncludePathModuleNames: RenderCore

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraCompileHash.h` (Public)


#### struct `FNiagaraCompileHash`  
`struct FNiagaraCompileHash`  
_L9-67_
- reflection: `USTRUCT()`
- L13 _public function_ `FNiagaraCompileHash()`
- L17 _public function_ `explicit FNiagaraCompileHash(const TArray<uint8>& InDataHash)`
- L23 _public function_ `explicit FNiagaraCompileHash(const uint8* InDataHash, uint32 InCount) : DataHash(InDataHash, InCount)`
- L28 _public function_ `bool operator==(const FNiagaraCompileHash& Other) const`
- L29 _public function_ `bool operator!=(const FNiagaraCompileHash& Other) const`
- L30 _public prototype_ `bool operator==(const FSHAHash& Other) const;`
- L31 _public function_ `inline bool operator!=(const FSHAHash& Other) const`
- L33 _public prototype_ `bool ToSHAHash(FSHAHash& OutHash) const;`
- L35 _public prototype_ `bool IsValid() const;`
- L37 _public prototype_ `uint32 GetTypeHash() const;`
- L39 _public prototype_ `const uint8* GetData() const;`
- L41 _public prototype_ `void AppendString(FString& Out) const;`
- L43 _public function_ `FString ToString() const`
- L52 _public member_ `static constexpr uint32 HashSize = 20;`
- L66 _private member_ `TArray<uint8> DataHash;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L54 _function_ `friend bool operator<(const FNiagaraCompileHash& Lhs, const FNiagaraCompileHash& Rhs)`
- L69 _function_ `inline uint32 GetTypeHash(const FNiagaraCompileHash& Hash)`
- L74 _function_ `inline bool operator==(const FSHAHash& Lhs, const FNiagaraCompileHash& Rhs)`
- L78 _function_ `inline bool operator!=(const FSHAHash& Lhs, const FNiagaraCompileHash& Rhs)`

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraCore.h` (Public)


#### enum `ENiagaraParameterAccessLevel`  
`enum class ENiagaraParameterAccessLevel : uint8`  
_L12-24_
- reflection: `UENUM()`
- L17 _public enumerator_ `Private` — Parameter is not be visibile to Verse.
- L23 _public enumerator_ `Public` — Parameter has unrestricted access, and can be modify anytime. Note: Modifications such are renaming, deleting, changing default values, could have an impact on existing projects and result in compilation / publishing failures.

#### enum `ENiagaraIterationSource`  
`enum class ENiagaraIterationSource : uint8`  
_L27-35_
- reflection: `UENUM()`
- L30 _public enumerator_ `Particles = 0` — Iterate over all active particles.
- L32 _public enumerator_ `DataInterface` — Iterate over all elements in the data interface.
- L34 _public enumerator_ `DirectSet` — Iterate over a user provided number of elements.

#### struct `FNiagaraVariableCommonReference`  
`struct FNiagaraVariableCommonReference`  
_L39-56_
- reflection: `USTRUCT()`
- desc: A utility class allowing for references to FNiagaraVariableBase outside of the Niagara module.
- L44 _public member_ `FName Name;` — `UPROPERTY()`
- L47 _public member_ `TObjectPtr<UObject> UnderlyingType;` — `UPROPERTY()`
- L49 _public prototype_ `bool Serialize(FArchive& Ar);`
- L52 _public function_ `bool operator==(const FNiagaraVariableCommonReference& Other)const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNiagaraVariableCommonReference> : public TStructOpsTypeTraitsBase2<FNiagaraVariableCommonReference>`  
_L58-64_
- inherits: `TStructOpsTypeTraitsBase2<FNiagaraVariableCommonReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L61-63_

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef uint64 FNiagaraSystemInstanceID;`
- L62 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb9d3e5010103`)
- L66 _function_ `inline bool operator<<(FArchive& Ar, FNiagaraVariableCommonReference& VariableReference)`

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraCoreModule.h` (Public)


#### class `INiagaraCoreModule`  
`class INiagaraCoreModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`
- desc: Niagara core module interface

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraCustomVersion.h` (Public)


#### struct `FNiagaraCustomVersion`  
`struct FNiagaraCustomVersion`  
_L10-237_
- desc: Custom serialization version for all packages containing Niagara asset types
- L230 _public prototype_ `static FGuid GetLatestScriptCompileVersion();` — This value represents the compiler version. It does not provide "backward" compatibility since it is a GUID. It is meant to capture the state of the translator/VM compiler structure and force a flush of any files in the DDC. Since it is a GUID, we don't need to worry about multiple people editing the translator having conflicting files in the shared DDC as there should never be any collisions.
- L233 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L236 _private function_ `FNiagaraCustomVersion()`

#### enum `FNiagaraCustomVersion::Type`  
`enum Type`  
_L12-224_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in niagara
- L18 _public enumerator_ `VMExternalFunctionBindingRework` — Reworked vm external function binding to be more robust.
- L21 _public enumerator_ `PostLoadCompilationEnabled` — Making all Niagara files reference the version number, allowing post loading recompilation if necessary.
- L24 _public enumerator_ `VMExternalFunctionBindingReworkPartDeux` — Moved some runtime cost from external functions into the binding step and used variadic templates to neaten that code greatly.
- L27 _public enumerator_ `DataInterfacePerInstanceRework` — Moved per instance data needed for certain data interfaces out to it's own struct.
- L30 _public enumerator_ `NiagaraShaderMaps` — Added shader maps and corresponding infrastructure
- L33 _public enumerator_ `UpdateSpawnEventGraphCombination` — Combined Spawn, Update, and Event scripts into one graph.
- L36 _public enumerator_ `DataSetLayoutRework` — Reworked data layout to store float and int data separately.
- L39 _public enumerator_ `AddedEmitterAndSystemScripts` — Reworked scripts to support emitter & system scripts
- L42 _public enumerator_ `ScriptExecutionContextRework` — Rework of script execution contexts to allow better reuse and reduce overhead of parameter handling.
- L45 _public enumerator_ `RemovalOfNiagaraVariableIDs` — Removed the Niagara variable ID's making hookup impossible until next compile
- L48 _public enumerator_ `SystemEmitterScriptSimulations` — System and emitter script simulations.
- L51 _public enumerator_ `IntegerRandom` — Adding integer random to VM. TODO: The vm really needs its own versioning system that will force a recompile when changes.
- L54 _public enumerator_ `AddedEmitterSpawnAttributes` — Added emitter spawn attributes
- L57 _public enumerator_ `NiagaraShaderMapCooking` — cooking of shader maps and corresponding infrastructure
- L58 _public enumerator_ `NiagaraShaderMapCooking2` — don't serialize shader maps for system scripts
- L60 _public enumerator_ `AddedScriptRapidIterationVariables` — Added script rapid iteration variables, usually top-level module parameters...
- L63 _public enumerator_ `AddedTypeToDataInterfaceInfos` — Added type to data interface infos
- L66 _public enumerator_ `EnabledAutogeneratedDefaultValuesForFunctionCallNodes` — Hooked up autogenerated default values for function call nodes.
- L69 _public enumerator_ `CurveLUTNowOnByDefault` — Now curve data interfaces have look-up tables on by default.
- L72 _public enumerator_ `ScriptsNowUseAGuidForIdentificationInsteadOfAnIndex` — Scripts now use a guid for identification instead of an index when there are more than one with the same usage.
- L74 _public enumerator_ `NiagaraCombinedGPUSpawnUpdate` — don't serialize shader maps for update scripts
- L76 _public enumerator_ `DontCompileGPUWhenNotNeeded` — don't serialize shader maps for emitters that don't run on gpu.
- L78 _public enumerator_ `LifeCycleRework`
- L80 _public enumerator_ `NowSerializingReadWriteDataSets` — We weren't serializing event data sets previously.
- L82 _public enumerator_ `TranslatorClearOutBetweenEmitters` — Forcing the internal parameter map vars to be reset between emitter calls.
- L84 _public enumerator_ `AddSamplerDataInterfaceParams` — added sampler shader params based on DI buffer descriptors
- L86 _public enumerator_ `GPUShadersForceRecompileNeeded` — Need to force the GPU shaders to recompile
- L88 _public enumerator_ `PlaybackRangeStoredOnSystem` — The playback range for the timeline is now stored in the system editor data.
- L90 _public enumerator_ `MovedToDerivedDataCache` — All cached values will auto-recompile.
- L92 _public enumerator_ `DataInterfacesNotAllocated` — Data interfaces are preallocated
- L94 _public enumerator_ `EmittersHaveGenericUniqueNames` — emitter scripts are built using "Emitter." instead of the full name.
- L96 _public enumerator_ `MovingTranslatorVersionToGuid` — no longer have compiler version enum value in this list, instead moved to a guid, which works better for the DDC
- L98 _public enumerator_ `AddingParamMapToDataSetBaseNode` — adding a parameter map in/out to the data set base node
- L100 _public enumerator_ `DataInterfaceComputeShaderParamRefactor` — refactor of CS parameters allowing regular params as well as buffers.
- L102 _public enumerator_ `CurveLUTRegen` — bumping version and forcing curves to regen their LUT on version change.
- L104 _public enumerator_ `AssignmentNodeUsesBeginDefaults` — Changing the graph generation for assignment nodes so that it uses a "Begin Defaults" node where appropriate.
- L106 _public enumerator_ `AssignmentNodeHasCorrectUsageBitmask` — Updating the usage flage bitmask for assignment nodes to match the part of the stack it's used in.
- L108 _public enumerator_ `EmitterLocalSpaceLiteralConstant` — Emitter local space is compiled into the hlsl as a literal constant to expose it to emitter scripts and allow for some better optimization of particle transforms.
- L110 _public enumerator_ `TextureDataInterfaceUsesCustomSerialize` — The cpu cache of the texture is now directly serialized instead of using array property serialization.
- L112 _public enumerator_ `TextureDataInterfaceSizeSerialize` — The texture data interface now streams size info
- L114 _public enumerator_ `SkelMeshInterfaceAPIImprovements` — API to skeletal mesh interface was improved but requires a recompile and some graph fixup.
- L116 _public enumerator_ `ImproveLoadTimeFixupOfOpAddPins` — Only do op add pin fixup on existing nodes which are before this version
- L118 _public enumerator_ `MoveCommonInputMetadataToProperties` — Moved commonly used input metadata out of the strin/string property metadata map to actual properties on the metadata struct.
- L120 _public enumerator_ `UseHashesToIdentifyCompileStateOfTopLevelScripts` — Move to using the traversed graph hash and the base script id for the FNiagaraVMExecutableDataId instead of the change id guid to prevent invalidating the DDC.
- L122 _public enumerator_ `MetaDataAndParametersUpdate` — Reworked how the metadata is stored in NiagaraGraph from storing a Map of FNiagaraVariableMetaData to storing a map of UNiagaraScriptVariable* to be used with the Details panel.
- L124 _public enumerator_ `MoveInheritanceDataFromTheEmitterHandleToTheEmitter` — Moved the emitter inheritance data from the emitter handle to the emitter to allow for chained emitter inheritance.
- L126 _public enumerator_ `AddLibraryAssetProperty` — Add property to all Niagara scripts indicating whether or not they belong to the library
- L128 _public enumerator_ `AddAdditionalDefinesProperty` — Addding additional defines to the GPU script
- L130 _public enumerator_ `RemoveGraphUsageCompileIds` — Remove the random compile id guids from the cached script usage and from the compile and script ids since the hashes serve the same purpose and are deterministic.
- L132 _public enumerator_ `AddRIAndDetailLevel` — Adding UseRapidIterationParams and DetailLevelMask to the GPU script
- L134 _public enumerator_ `ChangeEmitterCompiledDataToSharedRefs` — Changing the system and emitter compiled data to shared pointers to deal with lifetime issues in the editor.  They now are handled directly in system serialize.
- L136 _public enumerator_ `DisableSortingByDefault` — Sorting on Renderers is disabled by default, we add a version to maintain existing systems that expected sorting to be enabled
- L138 _public enumerator_ `MemorySaving` — Convert TMap into TArray to save memory, TMap contains an inline allocator which pushes the size to 80 bytes
- L140 _public enumerator_ `AddSimulationStageUsageEnum` — Added a new value to the script usage enum, and we need a custom version to fix the existing bitfields.
- L142 _public enumerator_ `AddGeneratedFunctionsToGPUParamInfo` — Save the functions generated by a GPU data interface inside FNiagaraDataInterfaceGPUParamInfo
- L144 _public enumerator_ `PlatformScalingRefactor` — Removed DetailLevel in favor of FNiagaraPlatfomSet based selection of per platform settings.
- L146 _public enumerator_ `PrecompileNamespaceFixup` — Promote parameters used across script executions to the Dataset, and Demote unused parameters.
- L148 _public enumerator_ `FixNullScriptVariables` — Postload fixup in UNiagaraGraph to fixup VariableToScriptVariable map entries being null.
- L150 _public enumerator_ `PrecompileNamespaceFixup2` — Move FNiagaraVariableMetaData from storing scope enum to storing registered scope name.
- L152 _public enumerator_ `SimulationStageInUsageBitmask` — Enable the simulation stage flag by default in the usage bitmask of modules and functions
- L154 _public enumerator_ `StandardizeParameterNames` — Fix graph parameter map parameters on post load so that they all have a consisten parsable format and update the UI to show and filter based on these formats.
- L156 _public enumerator_ `ComponentsOnlyHaveUserVariables` — Make sure that UNiagaraComponents only have override maps for User variables.
- L158 _public enumerator_ `RibbonRendererUVRefactor` — Refactor the options for UV settings on the ribbon renderer.
- L160 _public enumerator_ `VariablesUseTypeDefRegistry` — Replace the TypeDefinition in VariableBase with an index into the type registry
- L162 _public enumerator_ `AddLibraryVisibilityProperty` — Expand the visibility options of the scripts to be able to hide a script completely from the user
- L164 _public enumerator_ `SignificanceHandlers`
- L166 _public enumerator_ `ModuleVersioning` — Added support for multiple versions of script data
- L168 _public enumerator_ `MoveDefaultValueFromFNiagaraVariableMetaDataToUNiagaraScriptVariable`
- L170 _public enumerator_ `ChangeSystemDeterministicDefault` — Changed the default mode from deterministic to non-deterministic which matches emitters
- L172 _public enumerator_ `StaticSwitchFunctionPinsUsePersistentGuids` — Update static switch pins to use the PersistentId from their script variable so that when they're renamed their values aren't lost when reallocating pins.
- L174 _public enumerator_ `VisibilityCullingImprovements` — Extended visibility culling options and moved properties into their own struct.
- L176 _public enumerator_ `AddBakerCameraBookmarks`
- L178 _public enumerator_ `PopulateFunctionCallNodePinNameBindings` — Function call node refresh from external changes has been refactored so that they don't need to populate their name bindings every load.
- L180 _public enumerator_ `ComponentRendererSpawnProperty` — Changed the default value for the component renderer's OnlyCreateComponentsOnParticleSpawn property
- L182 _public enumerator_ `RepopulateFunctionCallNodePinNameBindings` — Previous repopulate didn't handle module attributes like Particles.Module.Name so they need to be repopulated for renaming to work correctly.
- L184 _public enumerator_ `EventSpawnsUpdateInitialAttributeValues` — Event spawns now optionally update Initial. attribute values. New default is true but old data is kept false to maintain existing behavior.
- L186 _public enumerator_ `AddVariadicParametersToGPUFunctionInfo` — Adds list of variadic parameters to the information about GPU functions.
- L188 _public enumerator_ `DynamicPinNodeFixup` — Some data fixup for NiagaraNodeWithDynamicPins.
- L190 _public enumerator_ `RibbonRendererLinkOrderDefaultIsUniqueID` — Ribbon renderer will default to unique ID rather than normalized age to make more things 'just work'
- L192 _public enumerator_ `SubImageBlendEnabledByDefault` — Renderer SubImage Blends are enabled by default
- L194 _public enumerator_ `RibbonPlaneUseGeometryNormals` — Ribbon renderer will use geometry normals by default rather than screen / facing aligned normals
- L196 _public enumerator_ `InitialOwnerVelocityFromActor` — Actors velocity is used for the initial velocity before the component has any tracking, old assets use the old zero velocity
- L198 _public enumerator_ `ParameterBindingWithValueRenameFixup` — FNiagaraParameterBindingWithValue wouldn't necessarily have the appropriate ResolvedParameter namespace when it comes to emitter merging
- L200 _public enumerator_ `SimCache_BulkDataVersion1` — Sim Cache moved to bulk data by default
- L202 _public enumerator_ `InheritanceUxRefactor` — Decoupling of 'Template' and 'Inheritance'
- L204 _public enumerator_ `NDCSpawnGroupOverrideDisabledByDefault` — NDC Read DIs will not override spawn group by default when spawning particles. Old content will remain unchanged.
- L206 _public enumerator_ `CustomSortingBindingToAge` — Before it was normalized age which can introduce flickering with sorting and random lifetimes
- L208 _public enumerator_ `StatelessInitialMeshOrientationV1` — Update Initial Mesh Orientation Module
- L210 _public enumerator_ `HierarchyEditorScriptSupport` — Hierarchy Editor was implemented
- L212 _public enumerator_ `EmitterStateAddLoopDelayEnabled` — Added loop delay enabled to emitter state
- L214 _public enumerator_ `SerializeUsageBitMaskToGPUFunctionInfo` — Make sure that we serialize the UsageBitMask with the GPUFunctionInfo
- L216 _public enumerator_ `AddedNewInterpolatedSpawnMode` — Changed the interpolated spawn property into an enum
- L218 _public enumerator_ `UserAssetTagStorageInMetaData` — Adding user asset tag storage in UMetaData for all UPackages
- L222 _public enumerator_ `VersionPlusOne` — DO NOT ADD A NEW VERSION UNLESS YOU HAVE TALKED TO THE NIAGARA LEAD. Mismanagement of these versions can lead to data loss if it is adjusted in multiple streams simultaneously. -----<new versions can be added above this line>  -------------------------------------------------
- L223 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraDataInterfaceBase.h` (Public)


#### struct `FNiagaraDataInterfaceParametersCS`  
`struct FNiagaraDataInterfaceParametersCS`  
_L35-38_
- desc: An interface to the parameter bindings for the data interface used by a Niagara compute shader.

#### class `UNiagaraDataInterfaceBase`  
`class UNiagaraDataInterfaceBase : public UNiagaraNotifyOnChanged`  
_L44-82_
- reflection: `UCLASS(abstract, EditInlineNew, MinimalAPI)`
- inherits: `UNiagaraNotifyOnChanged`
- desc: Base class for all Niagara data interfaces.
- L67 _public function_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const` — Override this method to provide parameters to the GPU (SRV / UAV / Constants / etc) The most common usage will be to provide a single structure which is nested with other parameters. The structure would be declared like this BEGIN_SHADER_PARAMETER_STRUCT(FMyShaderParameters, ) SHADER_PARAMETER(float, MyValue) SHADER_PARAMETER_SRV(Buffer<float>, MySRV) END_SHADER_PARAMETER_STRUCT() And inside the override BuildShaderParameters you would simple add the structure ShaderParametersBuilder.AddNestedStruct<FMyShaderParameters>(); You should also ensure that AppendCompileHash includes the parameters like this InVisitor->UpdateShaderParameters<FMyShaderParameters>(); When filling the data inside the set function you would ask for parameters using the same structure. Note: This function is only called on the CDO only not the instance
- L73 _public function_ `virtual FNiagaraDataInterfaceParametersCS* CreateShaderStorage(const FNiagaraDataInterfaceGPUParamInfo& ParameterInfo, const FShaderParameterMap& ParameterMap) const` — Optional storage that can be created per shader when not in legacy binding mode. This can be used to store information about the compilation state to avoid doing runtime checks / look-ups.
- L78 _public function_ `virtual const FTypeLayoutDesc* GetShaderStorageType() const` — If we create shader storage we must also supply the type of the storage so we understand how to serialize it. This function effectively returns &StaticGetTypeLayoutDesc<ParameterType>().
- L81 _public function_ `virtual bool HasInternalAttributeReads(const UNiagaraEmitter* OwnerEmitter, const UNiagaraEmitter* Provider) const` — Returns true if the DI (owned by OwnerEmitter) reads any attributes from the Provider emitter

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraMergeable.h` (Public)


#### class `UNiagaraMergeable`  
`class UNiagaraMergeable : public UNiagaraNotifyOnChanged`  
_L10-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNiagaraNotifyOnChanged`
- L15 _public prototype_ `UNiagaraMergeable();`
- L18 _public prototype_ `bool Equals(const UNiagaraMergeable* Other);`
- L20 _public prototype_ `FGuid GetMergeId() const;`
- L23 _protected prototype_ `UNiagaraMergeable* StaticDuplicateWithNewMergeIdInternal(UObject* InOuter) const;`
- L29 _private member_ `FGuid MergeId;` — `UPROPERTY()`

### `Plugins/FX/Niagara/Source/NiagaraCore/Public/NiagaraNotifyOnChanged.h` (Public)


#### class `UNiagaraNotifyOnChanged`  
`class UNiagaraNotifyOnChanged : public UObject`  
_L8-26_
- reflection: `UCLASS()`
- inherits: `UObject`
- L15 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`
- L18 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L19 _public prototype_ `FOnChanged& OnChanged();`
- L22 _private member_ `FOnChanged OnChangedDelegate;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`
