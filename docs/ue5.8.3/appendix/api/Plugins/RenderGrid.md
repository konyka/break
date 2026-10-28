# Plugins / RenderGrid

- module root: `Plugins/Experimental/RenderGrid/Source/RenderGrid`
- headers: 14; symbols: 553
- symbol kinds: class=25, delegate=11, enum=1, enumerator=2, function=112, member=111, namespace=28, prototype=256, struct=7
- PrivateDependencyModuleNames: Json, LevelSequence, LevelSequenceEditor, MovieRenderPipelineCore, MovieRenderPipelineEditor, MovieRenderPipelineRenderPasses, MovieScene, Serialization, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RemoteControl

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Private/Factories/RenderGridPropsSourceFactoryLocal.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridPropsSourceFactoryLocal`  
`class FRenderGridPropsSourceFactoryLocal final : public IRenderGridPropsSourceFactory`  
_L14-18_
- inherits: `IRenderGridPropsSourceFactory`
- desc: The factory class for URenderGridPropsSourceLocal.
- L17 _public prototype_ `virtual URenderGridPropsSourceBase* CreateInstance(UObject* PropsSourceOrigin) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Private/Factories/RenderGridPropsSourceFactoryRemoteControl.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridPropsSourceFactoryRemoteControl`  
`class FRenderGridPropsSourceFactoryRemoteControl final : public IRenderGridPropsSourceFactory`  
_L14-18_
- inherits: `IRenderGridPropsSourceFactory`
- desc: The factory class for URenderGridPropsSourceRemoteControl.
- L17 _public prototype_ `virtual URenderGridPropsSourceBase* CreateInstance(UObject* PropsSourceOrigin) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Private/RenderGridModule.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridModule`  
`class FRenderGridModule : public IRenderGridModule`  
_L15-42_
- inherits: `IRenderGridModule`
- desc: The implementation of the IRenderGridModule interface.
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual FRenderGridManager& GetManager() const override;`
- L26 _public prototype_ `virtual URenderGridPropsSourceBase* CreatePropsSource(ERenderGridPropsSourceType PropsSourceType, UObject* PropsSourceOrigin) override;`
- L27 _public function_ `virtual const TMap<ERenderGridPropsSourceType, TSharedPtr<IRenderGridPropsSourceFactory>>& GetPropsSourceFactories() const override`
- L31 _private prototype_ `void CreateManager();`
- L32 _private prototype_ `void RemoveManager();`
- L34 _private prototype_ `void RegisterPropsSourceFactories();`
- L35 _private prototype_ `void UnregisterPropsSourceFactories();`
- L36 _private prototype_ `void RegisterPropsSourceFactory(const ERenderGridPropsSourceType PropsSourceType, const TSharedPtr<IRenderGridPropsSourceFactory>& InFactory);`
- L37 _private prototype_ `void UnregisterPropsSourceFactory(const ERenderGridPropsSourceType PropsSourceType);`
- L40 _private member_ `TUniquePtr<FRenderGridManager> Manager;`
- L41 _private member_ `TMap<ERenderGridPropsSourceType, TSharedPtr<IRenderGridPropsSourceFactory>> PropsSourceFactories;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGrid` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/Factories/IRenderGridPropsSourceFactory.h` (Public)


#### class `UE::RenderGrid::IRenderGridPropsSourceFactory`  
`class IRenderGridPropsSourceFactory`  
_L16-21_
- desc: The base class for the factory classes that will create URenderGridPropsSourceBase instances.
- L19 _public prototype_ `virtual ~IRenderGridPropsSourceFactory() = default;`
- L20 _public function_ `virtual URenderGridPropsSourceBase* CreateInstance(UObject* PropsSourceOrigin)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RenderGrid` (scope `UE`)

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/IRenderGridModule.h` (Public)


#### class `UE::RenderGrid::IRenderGridModule`  
`class IRenderGridModule : public IModuleInterface`  
_L24-50_
- inherits: `IModuleInterface`
- desc: RenderGrid module interface.
- L32 _public function_ `static IRenderGridModule& Get()` — Singleton-like access to IRenderGridModule. @return Returns RenderGridModule singleton instance, loading the module on demand if needed.
- L43 _public prototype_ `virtual FRenderGridManager& GetManager() const = 0;` — Singleton-like access to FRenderGridManager. Will error if this module hasn't started (or has stopped). @return Returns RenderGridManager singleton instance.
- L46 _public prototype_ `virtual URenderGridPropsSourceBase* CreatePropsSource(ERenderGridPropsSourceType PropsSourceType, UObject* PropsSourceOrigin) = 0;` — Creates a URenderGridPropsSourceBase instance, based on the given ERenderGridPropsSourceType.
- L49 _public prototype_ `virtual const TMap<ERenderGridPropsSourceType, TSharedPtr<IRenderGridPropsSourceFactory>>& GetPropsSourceFactories() const = 0;` — Returns all set IRenderGridPropsSourceFactory instances, these are used to create URenderGridPropsSourceBase instances based on a given ERenderGridPropsSourceType.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RenderGrid` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RenderGrid` (scope `UE`)

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/RenderGrid/RenderGrid.h` (Public)


#### struct `FRenderGridRemoteControlPropertyData`  
`struct FRenderGridRemoteControlPropertyData`  
_L25-39_
- reflection: `USTRUCT(BlueprintType)`
- desc: This struct contains the data for a certain remote control property. It's currently simply a wrapper around a byte array. This struct is needed so that that byte array can be used in another UPROPERTY container (TMap, TArray, etc).
- L30 _public prototype_ `FRenderGridRemoteControlPropertyData() = default;`
- L31 _public function_ `FRenderGridRemoteControlPropertyData(const TArray<uint8>& InBytes) : Bytes(InBytes)`
- L38 _public member_ `TArray<uint8> Bytes;` — `UPROPERTY()` — The property data, as bytes.

#### class `URenderGridSettings`  
`class URenderGridSettings : public UObject`  
_L48-86_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This class contains the default values of render grid jobs. This is placed in a separate class, primarily so that it be separated easily from the render grid when using the details view widget.
- L53 _public prototype_ `URenderGridSettings();`
- L55 _public function_ `void CopyValuesFrom(URenderGridSettings* From)`
- L64 _public member_ `TSoftObjectPtr<UWorld> Level;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid", DisplayName="Level", Meta=(AllowedClasses="/Script/Engine.World"))`
- L68 _public member_ `ERenderGridPropsSourceType PropsSourceType;` — `UPROPERTY(/*EditInstanceOnly, Category="Render Grid", Meta=(DisplayName="Properties Type")*/)` — The type of the properties that a job in this grid can have.
- L72 _public member_ `TObjectPtr<URemoteControlPreset> PropsSourceOrigin_RemoteControl;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid", Meta=(DisplayName="Remote Control Preset" /*, EditCondition="PropsSourceType == ERenderGridPropsSourceType::RemoteControl", EditConditionHides*/))` — The remote control properties that a job in this grid can have, only use this if PropsSourceType is ERenderGridPropsSourceType::RemoteControl.
- L77 _public member_ `mutable TObjectPtr<URenderGridPropsSourceBase> CachedPropsSource;` — `UPROPERTY(Transient)` — GetPropsSource calls are somewhat expensive, we speed that up by caching the result (the PropsSource) that has been last outputted by that function.
- L81 _public member_ `mutable ERenderGridPropsSourceType CachedPropsSourceType;` — `UPROPERTY(Transient)` — GetPropsSource calls are somewhat expensive, we speed that up by caching the PropsSourceType last used in that function.
- L85 _public member_ `mutable TWeakObjectPtr<UObject> CachedPropsSourceOriginWeakPtr;` — `UPROPERTY(Transient)` — GetPropsSource calls are somewhat expensive, we speed that up by caching the PropsSourceOrigin last used in that function.

#### class `URenderGridDefaults`  
`class URenderGridDefaults : public UObject`  
_L95-121_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This class contains the default values of render grid jobs. This is placed in a separate class, primarily so that it be separated easily from the render grid when using the details view widget.
- L100 _public prototype_ `URenderGridDefaults();`
- L102 _public function_ `void CopyValuesFrom(URenderGridDefaults* From)`
- L112 _public member_ `TObjectPtr<ULevelSequence> LevelSequence;` — `UPROPERTY(EditInstanceOnly, Category="Defaults", Meta=(DisplayName="Default Level Sequence"))` — The default level sequence for new jobs, this is what will be rendered during rendering. A job without a level sequence can't be rendered.
- L116 _public member_ `TObjectPtr<UMoviePipelinePrimaryConfig> RenderPreset;` — `UPROPERTY(EditInstanceOnly, Category="Defaults", Meta=(DisplayName="Default Render Preset"))` — The default movie pipeline render preset for new jobs. Render grid jobs are rendered using the movie pipeline plugin. This 'preset' contains the configuration of that plugin.
- L120 _public member_ `FString OutputDirectory;` — `UPROPERTY(EditInstanceOnly, Category="Defaults", Meta=(DisplayName="Default Output Directory"))` — The default output directory for new jobs. This is the folder in which the output files (of rendering) are placed into. To be more specific, the output files are placed in: {OutputDirectory}/{JobId}/, this folder will be created if it doesn't exist at the time of rendering.

#### class `URenderGridJob`  
`class URenderGridJob : public UObject`  
_L131-404_
- reflection: `UCLASS(BlueprintType, Meta=(DontUseGenericSpawnObject="true"))`
- inherits: `UObject`
- desc: This class represents a render grid job, in other words, an entry (a row) of a render grid. It contains a level sequence and custom properties that will be applied while rendering. Each RenderGridJob must belong to a RenderGrid.
- L136 _public prototype_ `URenderGridJob();`
- L140 _public prototype_ `FString ToDebugString() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job", Meta=(DisplayName="To Debug String (Render Grid Job)", CompactNodeTitle="DEBUG"))` — Obtains a string representation of this object. Shouldn't be used for anything other than logging/debugging.
- L143 _public prototype_ `TSharedPtr<FJsonValue> ToDebugJson() const;` — Obtains a JSON representation of this object. Shouldn't be used for anything other than logging/debugging.
- L147 _public prototype_ `TOptional<int32> GetSequenceStartFrame() const;` — Gets the calculated start frame, not taking the framerate of the render preset into account.
- L150 _public prototype_ `TOptional<int32> GetSequenceEndFrame() const;` — Gets the calculated end frame, not taking the framerate of the render preset into account.
- L153 _public prototype_ `bool SetSequenceStartFrame(const int32 NewCustomStartFrame);` — Sets the custom start frame to match the given sequence start frame.
- L156 _public prototype_ `bool SetSequenceEndFrame(const int32 NewCustomEndFrame);` — Sets the custom end frame to match the given sequence end frame.
- L160 _public prototype_ `TOptional<int32> GetStartFrame() const;` — Gets the calculated start frame, if possible.
- L163 _public prototype_ `TOptional<int32> GetEndFrame() const;` — Gets the calculated end frame, if possible.
- L166 _public prototype_ `TOptional<double> GetStartTime() const;` — Gets the calculated start time (in seconds), if possible.
- L169 _public prototype_ `TOptional<double> GetEndTime() const;` — Gets the calculated end time (in seconds), if possible.
- L172 _public prototype_ `TOptional<double> GetDuration() const;` — Gets the calculated duration (in seconds), if possible.
- L177 _public prototype_ `void GetStartFrame(bool& bSuccess, int32& StartFrame) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the calculated start frame, if possible.
- L181 _public prototype_ `void GetEndFrame(bool& bSuccess, int32& EndFrame) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the calculated end frame, if possible.
- L185 _public prototype_ `void GetStartTime(bool& bSuccess, double& StartTime) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the calculated start time, if possible.
- L189 _public prototype_ `void GetEndTime(bool& bSuccess, double& EndTime) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the calculated end time, if possible.
- L193 _public prototype_ `void GetDuration(bool& bSuccess, double& Duration) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the calculated duration in seconds, if possible.
- L198 _public prototype_ `FIntPoint GetOutputResolution() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the resolution that this job will be rendered in.
- L202 _public prototype_ `double GetOutputAspectRatio() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Gets the aspect ratio that this job will be rendered in.
- L206 _public prototype_ `bool MatchesSearchTerm(const FString& SearchTerm) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Checks whether the job contains data that matches the search terms.
- L211 _public function_ `FGuid GetGuid() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")` — Returns the GUID, which is randomly generated at creation.
- L215 _public function_ `void GenerateNewGuid()` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")` — Randomly generates a new GUID.
- L219 _public function_ `int32 GetWaitFramesBeforeRendering() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L222 _public function_ `void SetWaitFramesBeforeRendering(const int32 NewWaitFramesBeforeRendering)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L226 _public function_ `ULevelSequence* GetLevelSequence() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L229 _public function_ `void SetLevelSequence(ULevelSequence* NewSequence)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L233 _public function_ `bool GetIsUsingCustomStartFrame() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L236 _public function_ `void SetIsUsingCustomStartFrame(const bool bNewOverrideStartFrame)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L239 _public function_ `int32 GetCustomStartFrame() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L242 _public function_ `void SetCustomStartFrame(const int32 NewCustomStartFrame)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L246 _public function_ `bool GetIsUsingCustomEndFrame() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L249 _public function_ `void SetIsUsingCustomEndFrame(const bool bNewOverrideEndFrame)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L252 _public function_ `int32 GetCustomEndFrame() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L255 _public function_ `void SetCustomEndFrame(const int32 NewCustomEndFrame)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L259 _public function_ `bool GetIsUsingCustomResolution() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L262 _public function_ `void SetIsUsingCustomResolution(const bool bNewOverrideResolution)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L265 _public function_ `FIntPoint GetCustomResolution() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L268 _public function_ `void SetCustomResolution(const FIntPoint NewCustomResolution)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L272 _public function_ `FString GetJobId() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L275 _public prototype_ `void SetJobId(const FString& NewJobId);` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L276 _public function_ `void SetJobIdRaw(const FString& NewJobId)`
- L280 _public function_ `FString GetJobName() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L283 _public function_ `void SetJobName(const FString& NewJobName)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L284 _public function_ `void SetJobNameRaw(const FString& NewJobName)`
- L288 _public function_ `bool GetIsEnabled() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L291 _public function_ `void SetIsEnabled(const bool bEnabled)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L295 _public prototype_ `FString GetOutputDirectory() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L296 _public function_ `FString GetOutputDirectoryRaw() const`
- L299 _public function_ `FString GetOutputDirectoryForDisplay() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L302 _public prototype_ `void SetOutputDirectory(const FString& NewOutputDirectory);` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L303 _public function_ `void SetOutputDirectoryRaw(const FString& NewOutputDirectory)`
- L307 _public function_ `UMoviePipelinePrimaryConfig* GetRenderPreset() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L310 _public prototype_ `UMoviePipelineOutputSetting* GetRenderPresetOutputSettings() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L313 _public function_ `void SetRenderPreset(UMoviePipelinePrimaryConfig* NewRenderPreset)` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L316 _public prototype_ `TArray<URemoteControlPreset*> GetRemoteControlPresets() const;`
- L318 _public prototype_ `bool HasStoredRemoteControlValueBytes(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity) const;`
- L319 _public prototype_ `bool GetRemoteControlValueBytes(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, TArray<uint8>& OutBytes) const;`
- L320 _public prototype_ `bool SetRemoteControlValueBytes(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, const TArray<uint8>& Bytes);`
- L322 _public prototype_ `bool HasStoredRemoteControlValueBytes(const FGuid& FieldId) const;`
- L323 _public prototype_ `bool GetRemoteControlValueBytes(const FGuid& FieldId, TArray<uint8>& OutBytes) const;`
- L324 _public prototype_ `bool SetRemoteControlValueBytes(const FGuid& FieldId, const TArray<uint8>& Bytes);`
- L326 _public function_ `TMap<FGuid, FRenderGridRemoteControlPropertyData>& GetRemoteControlValuesBytesRef()`
- L330 _public prototype_ `bool GetRemoteControlValue(const FGuid& FieldId, FString& Json) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L333 _public prototype_ `bool SetRemoteControlValue(const FGuid& FieldId, const FString& Json);` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L336 _public prototype_ `bool GetRemoteControlFieldIdFromLabel(const FString& Label, FGuid& FieldId) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L339 _public prototype_ `bool GetRemoteControlLabelFromFieldId(const FGuid& FieldId, FString& Label) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Job")`
- L342 _public prototype_ `TMap<FGuid, FString> GetRemoteControlValues() const;` — `UFUNCTION(BlueprintCallable, Category="Render Grid Job")`
- L347 _private member_ `FGuid Guid;` — `UPROPERTY()` — The unique ID of this job.
- L351 _private member_ `int32 WaitFramesBeforeRendering;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", ClampMin="0"))` — Waits the given number of frames before it will render this job. This can be set to a higher amount when the renderer has to wait for your code to complete (such as construction scripts etc). Try increasing this value when rendering doesn't produce the output you expect it to.
- L355 _private member_ `TObjectPtr<ULevelSequence> LevelSequence;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true"))` — The level sequence, this is what will be rendered during rendering. A job without a level sequence can't be rendered.
- L359 _private member_ `bool bOverrideStartFrame;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — If this is true, the CustomStartFrame property will override the start frame of the level sequence.
- L363 _private member_ `int32 CustomStartFrame;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", EditCondition="bOverrideStartFrame"))` — If bOverrideStartFrame is true, this property will override the start frame of the level sequence.
- L367 _private member_ `bool bOverrideEndFrame;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — If this is true, the CustomEndFrame property will override the end frame of the level sequence.
- L371 _private member_ `int32 CustomEndFrame;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", EditCondition="bOverrideEndFrame"))` — If bOverrideEndFrame is true, this property will override the end frame of the level sequence.
- L375 _private member_ `bool bOverrideResolution;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — If this is true, the CustomResolution property will override the resolution of the render.
- L379 _private member_ `FIntPoint CustomResolution;` — `UPROPERTY(EditInstanceOnly, Category="Render Grid Job", Meta=(AllowPrivateAccess="true", EditCondition="bOverrideResolution", ClampMin="1", UIMin="1"))` — If bOverrideResolution is true, this property will override the resolution of the render.
- L383 _private member_ `bool bIsEnabled;` — `UPROPERTY()` — If this is true, this job will be rendered during a batch rendering, otherwise it will be skipped.
- L387 _private member_ `FString JobId;` — `UPROPERTY()` — The 'ID' of this job, this 'ID' is set by users. During rendering it will place all the output files of this job into a folder called after this 'ID', this means that this string can only contain file-safe characters.
- L391 _private member_ `FString JobName;` — `UPROPERTY()` — The name of this job, this can be anything, it's set by the user, it serves as a way for the user to understand what job this is.
- L395 _private member_ `FString OutputDirectory;` — `UPROPERTY()` — This is the folder in which the output files (of rendering) are placed into. To be more specific, the output files are placed in: {OutputDirectory}/{JobId}/, this folder will be created if it doesn't exist at the time of rendering.
- L399 _private member_ `TObjectPtr<UMoviePipelinePrimaryConfig> RenderPreset;` — `UPROPERTY()` — The movie pipeline render preset. Render grid jobs are rendered using the movie pipeline plugin. This 'preset' contains the configuration of that plugin.
- L403 _private member_ `mutable TMap<FGuid, FRenderGridRemoteControlPropertyData> RemoteControlValues;` — `UPROPERTY()` — The remote control plugin can be used to customize and modify the way a job is rendered. If remote control is being used, the property values of this job will be stored in this map (remote control entity id -> value as bytes).

#### class `URenderGrid`  
`class URenderGrid : public UObject`  
_L412-774_
- reflection: `UCLASS(Blueprintable, BlueprintType, EditInlineNew, Meta=(DontUseGenericSpawnObject="true"))`
- inherits: `UObject`
- desc: This class represents a render grid, which is basically just a collection of render grid jobs. A render grid is the asset that is shown in the content browser, it's the asset that can be opened and edited using the editor.
- L417 _public prototype_ `URenderGrid();`
- L421 _public prototype_ `FString ToDebugString() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid", Meta=(DisplayName="To Debug String (Render Grid)", CompactNodeTitle="DEBUG"))` — Obtains a string representation of this object. Shouldn't be used for anything other than logging/debugging.
- L424 _public prototype_ `TSharedPtr<FJsonValue> ToDebugJson() const;` — Obtains a JSON representation of this object. Shouldn't be used for anything other than logging/debugging.
- L428 _public prototype_ `virtual UWorld* GetWorld() const override;` — UObject interface
- L429 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L430 _public prototype_ `virtual void PostLoad() override;`
- L434 _public prototype_ `void CopyJobs(URenderGrid* From);` — Copy jobs from the given RenderGrid to self.
- L437 _public prototype_ `void CopyAllPropertiesExceptJobs(URenderGrid* From);` — Copy all properties except jobs from the given RenderGrid to self.
- L440 _public prototype_ `void CopyAllProperties(URenderGrid* From);` — Copy all properties from the given RenderGrid to self.
- L443 _public prototype_ `void CopyAllUserVariables(URenderGrid* From);` — Copy all user variables (configured in the blueprint graph) from the given RenderGrid to self.
- L446 _public function_ `static TArray<FString> GetBlueprintImplementableEvents()`
- L468 _protected prototype_ `void ReceiveBeginEditor();` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="BeginEditor"))` — Event for when this asset is opened in the editor. The asset will also be closed and reopened during a blueprint compile. In here, you could for example obtain jobs from an external source and replace the current jobs of this render grid asset with those.
- L476 _protected prototype_ `void ReceiveEndEditor();` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="EndEditor"))` — Event for when this asset is closed in the editor. The asset will also be closed and reopened during a blueprint compile. In here, you could do any cleanup required at the end of editing this render grid asset.
- L482 _protected prototype_ `void ReceiveTick(float DeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="Tick"))` — The tick event, will only execute when the asset is open in the editor.
- L490 _protected prototype_ `void ReceiveBeginBatchRender(URenderGridQueue* Queue);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="BeginBatchRender"))` — Event for when batch rendering begins. In here, you could for example obtain jobs from an external source and add them to the queue.
- L498 _protected prototype_ `void ReceiveEndBatchRender(URenderGridQueue* Queue);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="EndBatchRender"))` — Event for when batch rendering ends. In here, you could do any cleanup required at the end of a batch render.
- L506 _protected prototype_ `void ReceiveBeginJobRender(URenderGridQueue* Queue, URenderGridJob* Job);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="BeginJobRender"))` — Event for when job rendering begins. In here, you could for example change elements in the world according to what job this is.
- L515 _protected prototype_ `void ReceiveEndJobRender(URenderGridQueue* Queue, URenderGridJob* Job);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="EndJobRender"))` — Event for when job rendering ends. In here, you could do any cleanup required at the end of rendering out a job, like for example undoing the changes you've made to the world for this job.
- L525 _protected prototype_ `void ReceiveBeginViewportRender(URenderGridJob* Job);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="BeginViewportRender"))` — Event for when job rendering for the viewport viewer-mode begins. This event will fire every frame, as long as the viewport viewer-mode is open. In here, you could for example change elements in the world according to what job this is.
- L536 _protected prototype_ `void ReceiveEndViewportRender(URenderGridJob* Job);` — `UFUNCTION(BlueprintImplementableEvent, Meta=(DisplayName="EndViewportRender"))` — Event for when job rendering for the viewport viewer-mode ends. This event will fire every frame, as long as the viewport viewer-mode is open. In here, you could do any cleanup required at the end of rendering out a job, like for example undoing the changes you've made to the world for this job.
- L540 _public prototype_ `virtual void BeginEditor();` — Overridable native event for when this asset is opened in the editor. The asset will also be closed and reopened during a blueprint compile.
- L543 _public prototype_ `virtual void EndEditor();` — Overridable native event for when this asset is closed in the editor. The asset will also be closed and reopened during a blueprint compile.
- L546 _public prototype_ `virtual void Tick(float DeltaTime);` — Overridable native event for when this asset is ticked by the editor.
- L549 _public prototype_ `virtual void BeginBatchRender(URenderGridQueue* Queue);` — Overridable native event for when batch rendering begins.
- L552 _public prototype_ `virtual void EndBatchRender(URenderGridQueue* Queue);` — Overridable native event for when batch rendering ends.
- L555 _public prototype_ `virtual void BeginJobRender(URenderGridQueue* Queue, URenderGridJob* Job);` — Overridable native event for when job rendering begins.
- L558 _public prototype_ `virtual void EndJobRender(URenderGridQueue* Queue, URenderGridJob* Job);` — Overridable native event for when job rendering ends.
- L561 _public prototype_ `virtual void BeginViewportRender(URenderGridJob* Job);` — Overridable native event for when job rendering for the viewport viewer-mode begins.
- L564 _public prototype_ `virtual void EndViewportRender(URenderGridJob* Job);` — Overridable native event for when job rendering for the viewport viewer-mode ends.
- L567 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(URenderGridQueue*, FRenderGridRunRenderJobsDefaultObjectCallback, URenderGrid* , TArray<URenderGridJob*> );`
- L568 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(URenderGridQueue*, FRenderGridRunRenderJobsCallback, URenderGrid* , TArray<URenderGridJob*> );`
- L569 _private prototype_ `URenderGridQueue* RunRenderJobs(const TArray<URenderGridJob*>& Jobs, const FRenderGridRunRenderJobsDefaultObjectCallback& DefaultObjectCallback, const FRenderGridRunRenderJobsCallback& Callback);`
- L574 _public prototype_ `URenderGridQueue* Render();` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders all the enabled jobs of this render grid.
- L578 _public prototype_ `URenderGridQueue* RenderJob(URenderGridJob* Job);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders the given job of this render grid.
- L582 _public prototype_ `URenderGridQueue* RenderJobs(const TArray<URenderGridJob*>& Jobs);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders all the given jobs of this render grid.
- L587 _public prototype_ `URenderGridQueue* RenderSingleFrame(const int32 Frame);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders all the enabled jobs of this render grid. Only renders a single frame of each job.
- L591 _public prototype_ `URenderGridQueue* RenderJobSingleFrame(URenderGridJob* Job, const int32 Frame);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders the given job of this render grid. Only renders a single frame.
- L595 _public prototype_ `URenderGridQueue* RenderJobsSingleFrame(const TArray<URenderGridJob*>& Jobs, const int32 Frame);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders all the given jobs of this render grid. Only renders a single frame of each job.
- L600 _public prototype_ `URenderGridQueue* RenderSingleFramePosition(const double FramePosition);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders all the enabled jobs of this render grid. Only renders a single frame of each job. The frame number it renders is based on the given FramePosition (0.0 is the first frame, 1.0 is the last frame, 0.5 is the frame in the middle, etc).
- L604 _public prototype_ `URenderGridQueue* RenderJobSingleFramePosition(URenderGridJob* Job, const double FramePosition);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders the given job of this render grid. Only renders a single frame. The frame number it renders is based on the given FramePosition (0.0 is the first frame, 1.0 is the last frame, 0.5 is the frame in the middle, etc).
- L608 _public prototype_ `URenderGridQueue* RenderJobsSingleFramePosition(const TArray<URenderGridJob*>& Jobs, const double FramePosition);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Renders all the given jobs of this render grid. Only renders a single frame of each job. The frame number it renders is based on the given FramePosition (0.0 is the first frame, 1.0 is the last frame, 0.5 is the frame in the middle, etc).
- L613 _public function_ `FGuid GetGuid() const` — `UFUNCTION(BlueprintPure, Category="Render Grid")` — Returns the GUID, which is randomly generated at creation.
- L617 _public function_ `void GenerateNewGuid()` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Randomly generates a new GUID.
- L620 _public function_ `URenderGridSettings* GetSettingsObject()`
- L623 _public prototype_ `TSoftObjectPtr<UWorld> GetLevel() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L626 _public prototype_ `void SetPropsSource(ERenderGridPropsSourceType InPropsSourceType, UObject* InPropsSourceOrigin = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L629 _public prototype_ `URenderGridPropsSourceBase* GetPropsSource() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L632 _public function_ `template<typename Type> Type* GetPropsSource() const`
- L639 _public function_ `ERenderGridPropsSourceType GetPropsSourceType() const` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L642 _public prototype_ `UObject* GetPropsSourceOrigin() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L645 _public function_ `URenderGridDefaults* GetDefaultsObject()`
- L648 _public function_ `ULevelSequence* GetDefaultLevelSequence() const` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L651 _public function_ `void SetDefaultLevelSequence(ULevelSequence* NewSequence)` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L654 _public function_ `UMoviePipelinePrimaryConfig* GetDefaultRenderPreset() const` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L657 _public prototype_ `UMoviePipelineOutputSetting* GetDefaultRenderPresetOutputSettings() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L660 _public function_ `void SetDefaultRenderPreset(UMoviePipelinePrimaryConfig* NewRenderPreset)` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L663 _public prototype_ `FString GetDefaultOutputDirectory() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L664 _public function_ `FString GetDefaultOutputDirectoryRaw() const`
- L667 _public function_ `FString GetDefaultOutputDirectoryForDisplay() const` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L670 _public prototype_ `void SetDefaultOutputDirectory(const FString& NewOutputDirectory);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L671 _public function_ `void SetDefaultOutputDirectoryRaw(const FString& NewOutputDirectory)`
- L675 _public prototype_ `void ClearRenderGridJobs();` — `UFUNCTION(BlueprintCallable, Category="Render Grid", Meta=(Keywords="remove delete all"))`
- L678 _public prototype_ `void SetRenderGridJobs(const TArray<URenderGridJob*>& Jobs);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L681 _public prototype_ `void AddRenderGridJob(URenderGridJob* Job);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L684 _public prototype_ `void RemoveRenderGridJob(URenderGridJob* Job);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L687 _public prototype_ `void InsertRenderGridJob(URenderGridJob* Job, int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L690 _public function_ `bool HasAnyRenderGridJobs() const` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L693 _public prototype_ `bool HasRenderGridJob(URenderGridJob* Job) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L696 _public prototype_ `int32 GetIndexOfRenderGridJob(URenderGridJob* Job) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L698 _public function_ `TArray<TObjectPtr<URenderGridJob>>& GetRenderGridJobsRef()`
- L701 _public prototype_ `TArray<URenderGridJob*> GetRenderGridJobs() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L704 _public prototype_ `TArray<URenderGridJob*> GetEnabledRenderGridJobs() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L707 _public prototype_ `TArray<URenderGridJob*> GetDisabledRenderGridJobs() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")`
- L710 _public prototype_ `void InsertRenderGridJobBefore(URenderGridJob* Job, URenderGridJob* BeforeJob);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L713 _public prototype_ `void InsertRenderGridJobAfter(URenderGridJob* Job, URenderGridJob* AfterJob);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")`
- L718 _public prototype_ `FString GenerateUniqueRandomJobId();` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Generates a unique job ID by grabbing the current time, as well as 16 random bytes, and converting that to a base64 string.
- L722 _public prototype_ `FString GenerateNextJobId();` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Generates a unique job ID by finding the currently highest job ID and increasing it by one.
- L726 _public prototype_ `bool DoesJobIdExist(const FString& JobId);` — `UFUNCTION(BlueprintPure, Category="Render Grid")` — Finds whether given job ID already exists in this grid.
- L730 _public prototype_ `URenderGridJob* CreateTempRenderGridJob();` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Creates a new job. This job won't be added to the grid, so it will eventually be garbage collected.
- L734 _public prototype_ `URenderGridJob* CreateAndAddNewRenderGridJob();` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Creates a new job and adds it to this grid.
- L738 _public prototype_ `URenderGridJob* DuplicateAndAddRenderGridJob(URenderGridJob* Job);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Copy the given job in this grid.
- L742 _public prototype_ `bool ReorderRenderGridJob(URenderGridJob* Job, URenderGridJob* DroppedOnJob, const bool bAfter = true);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Relocates the given job in this grid to the position of the given dropped-on job.
- L746 _public function_ `bool IsCurrentlyExecutingUserCode() const` — Returns true when it's currently executing a blueprint implementable event, returns false otherwise.
- L751 _private member_ `FGuid Guid;` — `UPROPERTY()` — The unique ID of this render grid.
- L756 _private member_ `TObjectPtr<URenderGridSettings> Settings;` — `UPROPERTY(Instanced)` — The settings of this render grid.
- L760 _private member_ `TObjectPtr<URenderGridDefaults> Defaults;` — `UPROPERTY(Instanced)` — The default values for new jobs.
- L764 _private member_ `TArray<TObjectPtr<URenderGridJob>> RenderGridJobs;` — `UPROPERTY(Instanced)` — The jobs of this render grid.
- L769 _private member_ `bool bExecutingBlueprintEvent;` — `UPROPERTY(Transient)` — True when it's currently executing a blueprint event, false otherwise.
- L773 _private member_ `mutable TWeakObjectPtr<UWorld> CachedWorldWeakPtr;` — GetWorld calls can be expensive, we speed them up by caching the last found world until it goes away.

#### Free symbols / members of external scopes

- L567 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(URenderGridQueue*, FRenderGridRunRenderJobsDefaultObjectCallback, URenderGrid* , TArray<URenderGridJob*> );`
- L568 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(URenderGridQueue*, FRenderGridRunRenderJobsCallback, URenderGrid* , TArray<URenderGridJob*> );`

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/RenderGrid/RenderGridBlueprintGeneratedClass.h` (Public)


#### class `URenderGridBlueprintGeneratedClass`  
`class URenderGridBlueprintGeneratedClass : public UBlueprintGeneratedClass`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UBlueprintGeneratedClass`
- desc: A UBlueprintGeneratedClass child class for the RenderGrid modules. Required in order for a RenderGrid to be able to have a blueprint graph.
- L21 _public prototype_ `virtual uint8* GetPersistentUberGraphFrame(UObject* Obj, UFunction* FuncToCheck) const override;`

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/RenderGrid/RenderGridManager.h` (Public)


#### struct `FRenderGridManagerPreviousPropValues`  
`struct FRenderGridManagerPreviousPropValues`  
_L22-39_
- reflection: `USTRUCT()`
- desc: This struct keeps track of the values of the properties before new values were applied, so we can rollback to the previous state.
- L27 _public prototype_ `FRenderGridManagerPreviousPropValues() = default;`
- L28 _public function_ `FRenderGridManagerPreviousPropValues(const TMap<TObjectPtr<URenderGridPropRemoteControl>, FRenderGridRemoteControlPropertyData>& InRemoteControlData) : RemoteControlData(InRemoteControlData)`
- L33 _public function_ `bool IsEmpty() const`
- L38 _public member_ `TMap<TObjectPtr<URenderGridPropRemoteControl>, FRenderGridRemoteControlPropertyData> RemoteControlData;` — `UPROPERTY()` — The previous values of the remote control properties.

#### struct `UE::RenderGrid::FRenderGridManagerRenderPreviewFrameArgs`  
`struct FRenderGridManagerRenderPreviewFrameArgs`  
_L51-71_
- desc: The arguments for the FRenderGridManager::RenderPreviewFrame function.
- L55 _public member_ `bool bHeadless = false;` — Whether it should run invisibly (so without any UI elements popping up during rendering) or not.
- L58 _public member_ `TStrongObjectPtr<URenderGrid> RenderGrid = nullptr;` — The render grid of the given render grid jobs that will be rendered.
- L61 _public member_ `TStrongObjectPtr<URenderGridJob> RenderGridJob = nullptr;` — The specific render grid job that will be rendered.
- L64 _public member_ `TOptional<int32> Frame;` — The specific frame number that will be rendered.
- L67 _public member_ `FIntPoint Resolution = FIntPoint(0, 0);` — The resolution it will be rendered in.
- L70 _public member_ `FRenderGridManagerRenderPreviewFrameArgsCallback Callback;` — The delegate for when the rendering has finished.

#### class `UE::RenderGrid::FRenderGridManager`  
`class FRenderGridManager`  
_L79-127_
- desc: The singleton class that manages render grids. This functionality is separated from the UI in order to make it is reusable, meaning that it can also be used in other modules.
- L83 _public member_ `inline static FString TmpRenderedFramesPath = FPaths::AutomationTransientDir() / TEXT("Ren` — A folder in which rendered frames for temporary use will be placed in.
- L86 _public member_ `static constexpr int32 GeneratedIdCharacterLength = 4;` — The number of characters for a generated ID. For example, a value of 4 results in IDs: "0001", "0002", etc.
- L90 _public prototype_ `URenderGridQueue* CreateBatchRenderQueue(URenderGrid* Grid, const TArray<URenderGridJob*>& Jobs);` — Batch render the given render grid job(s) of the given render grid.
- L93 _public prototype_ `URenderGridQueue* CreateBatchRenderQueueSingleFrame(URenderGrid* Grid, const TArray<URenderGridJob*>& Jobs, const int32 Frame);` — Batch render the given render grid job(s) of the given render grid. Only renders a single frame of each job.
- L96 _public prototype_ `URenderGridQueue* CreateBatchRenderQueueSingleFramePosition(URenderGrid* Grid, const TArray<URenderGridJob*>& Jobs, const double FramePosition);` — Batch render the given render grid job(s) of the given render grid. Only renders a single frame of each job. The frame number it renders is based on the given FramePosition (0.0 is the first frame, 1.0 is the last frame, 0.5 is the frame in the middle, etc).
- L100 _public prototype_ `URenderGridQueue* RenderPreviewFrame(const FRenderGridManagerRenderPreviewFrameArgs& Args);` — Render a preview frame (or multiple if no frame number is specified) of the given render grid job.
- L103 _public prototype_ `UTexture2D* GetSingleRenderedPreviewFrame(URenderGridJob* Job, UTexture2D* ReusingTexture2D, bool& bOutReusedGivenTexture2D);` — Gets the rendered preview frame (of a rendering in which the frame number was specified).
- L106 _public prototype_ `UTexture2D* GetSingleRenderedPreviewFrame(URenderGridJob* Job);` — Gets the rendered preview frame (of a rendering in which the frame number was specified).
- L109 _public prototype_ `UTexture2D* GetRenderedPreviewFrame(URenderGridJob* Job, const int32 Frame, UTexture2D* ReusingTexture2D, bool& bOutReusedGivenTexture2D);` — Gets the rendered preview frame of the given frame number (of a rendering in which the frame number was not specified).
- L112 _public prototype_ `UTexture2D* GetRenderedPreviewFrame(URenderGridJob* Job, const int32 Frame);` — Gets the rendered preview frame of the given frame number (of a rendering in which the frame number was not specified).
- L116 _public prototype_ `void UpdateStoredRenderGridJobsPropValues(URenderGrid* Grid);` — Makes sure that all the data from the current props source is stored in all of the render grid jobs of this render grid.
- L119 _public prototype_ `FRenderGridManagerPreviousPropValues ApplyJobPropValues(const URenderGrid* Grid, const URenderGridJob* Job);` — Applies the props of the given render grid job, also requires the render grid to be given as well (to know what props the render grid job is using).
- L122 _public prototype_ `void RestorePropValues(const FRenderGridManagerPreviousPropValues& PreviousPropValues);` — Restores the props that were previously applied, to the values that they were before.
- L126 _private member_ `TMap<FGuid, int32> StartFrameOfRenders;` — The map that stores the start frame (of a render) of each rendered render grid job.

#### Free symbols / members of external scopes

- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace RenderGrid` (scope `UE`)
- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FRenderGridManagerRenderPreviewFrameArgsCallback, bool );` — A delegate for when FRenderGridManager::RenderPreviewFrame has finished.
- L45 _prototype_ `DECLARE_DELEGATE_OneParam(FRenderGridManagerRenderPreviewFrameArgsCallback, bool );` (scope `UE::RenderGrid`) — A delegate for when FRenderGridManager::RenderPreviewFrame has finished.

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/RenderGrid/RenderGridPropsSource.h` (Public)


#### enum `ERenderGridPropsSourceType`  
`enum class ERenderGridPropsSourceType : uint8`  
_L18-22_
- reflection: `UENUM(BlueprintType)`
- desc: The type of the properties source. In other words, where the properties come from that each render grid job can have.
- L20 _public enumerator_ `Local = 0 UMETA(Hidden, DisplayName = "Local Source")`
- L21 _public enumerator_ `RemoteControl = 1 UMETA(DisplayName = "Remote Control Preset")`

#### class `URenderGridPropBase`  
`class URenderGridPropBase : public UObject`  
_L32-35_
- reflection: `UCLASS(Abstract, HideCategories=Object)`
- inherits: `UObject`
- desc: The base class of the render grid property abstraction.

#### class `URenderGridPropsBase`  
`class URenderGridPropsBase : public UObject`  
_L41-48_
- reflection: `UCLASS(Abstract, HideCategories=Object)`
- inherits: `UObject`
- desc: The base class of the render grid properties abstraction.
- L47 _public function_ `virtual TArray<URenderGridPropBase*> GetAll() const` — Returns all props.

#### class `URenderGridPropsSourceBase`  
`class URenderGridPropsSourceBase : public UObject`  
_L54-78_
- reflection: `UCLASS(Abstract, BlueprintType, HideCategories=Object)`
- inherits: `UObject`
- desc: The base class of the render grid properties source abstraction.
- L60 _public function_ `FGuid GetGuid() const` — Returns the GUID, which is randomly generated at creation.
- L63 _public function_ `void GenerateNewGuid()` — Randomly generates a new GUID.
- L67 _public function_ `virtual ERenderGridPropsSourceType GetType() const` — Returns the type of this properties source.
- L70 _public function_ `virtual void SetSourceOrigin(UObject* SourceOrigin)` — Sets the properties source.
- L73 _public function_ `virtual URenderGridPropsBase* GetProps() const` — Returns the collection of properties (that this properties source contains).
- L77 _protected member_ `FGuid Guid = FGuid::NewGuid();` — `UPROPERTY()`

#### class `URenderGridPropLocal`  
`class URenderGridPropLocal : public URenderGridPropBase`  
_L88-91_
- reflection: `UCLASS(HideCategories=Object)`
- inherits: `URenderGridPropBase`
- desc: The local properties implementation of the render grid property abstraction.

#### class `URenderGridPropsLocal`  
`class URenderGridPropsLocal : public URenderGridPropsBase`  
_L97-100_
- reflection: `UCLASS(HideCategories=Object)`
- inherits: `URenderGridPropsBase`
- desc: The local properties implementation of the render grid properties abstraction.

#### class `URenderGridPropsSourceLocal`  
`class URenderGridPropsSourceLocal : public URenderGridPropsSourceBase`  
_L106-115_
- reflection: `UCLASS(BlueprintType, HideCategories=Object, Meta=(DontUseGenericSpawnObject="true"))`
- inherits: `URenderGridPropsSourceBase`
- desc: The local properties implementation of the render grid properties source abstraction.
- L112 _public function_ `virtual ERenderGridPropsSourceType GetType() const override`
- L113 _public function_ `virtual URenderGridPropsBase* GetProps() const override`

#### class `URenderGridPropRemoteControl`  
`class URenderGridPropRemoteControl : public URenderGridPropBase`  
_L125-158_
- reflection: `UCLASS(HideCategories=Object)`
- inherits: `URenderGridPropBase`
- desc: The remote control properties implementation of the render grid property abstraction.
- L131 _public prototype_ `static bool GetValueOfEntity(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, TArray<uint8>& OutBytes);` — Gets the value (as bytes) of the given property (remote control entity). Returns true if the operation was successful, false otherwise.
- L134 _public prototype_ `static bool SetValueOfEntity(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, const TArray<uint8>& Bytes);` — Set the value (as bytes) of the given property (remote control entity). Returns true if the operation was successful, false otherwise.
- L137 _public prototype_ `static bool CanSetValueOfEntity(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, const TArray<uint8>& Bytes);` — Tests if it can set the value (as bytes) of the given property (remote control entity). Returns true if the set operation would likely be successful, false otherwise.
- L141 _public prototype_ `void Initialize(const TSharedPtr<FRemoteControlEntity>& InRemoteControlEntity);` — Sets the initial values of this instance.
- L144 _public function_ `TSharedPtr<FRemoteControlEntity> GetRemoteControlEntity() const` — Returns the property, which is a remote control entity (which can be a field or a function).
- L147 _public function_ `bool GetValue(TArray<uint8>& OutBytes) const` — Gets the value (as bytes) of this property. Returns true if the operation was successful, false otherwise.
- L150 _public function_ `bool SetValue(const TArray<uint8>& Bytes)` — Set the value (as bytes) of this property. Returns true if the operation was successful, false otherwise.
- L153 _public function_ `bool CanSetValue(const TArray<uint8>& Bytes)` — Tests if it can set the value (as bytes) of this property. Returns true if the set operation would likely be successful, false otherwise.
- L157 _protected member_ `TSharedPtr<FRemoteControlEntity> RemoteControlEntity = nullptr;` — The property, which is a remote control entity (which can be a field or a function).

#### class `URenderGridPropsRemoteControl`  
`class URenderGridPropsRemoteControl : public URenderGridPropsBase`  
_L164-192_
- reflection: `UCLASS(HideCategories=Object)`
- inherits: `URenderGridPropsBase`
- desc: The remote control properties implementation of the render grid properties abstraction.
- L170 _public prototype_ `void Initialize(URemoteControlPreset* InRemoteControlPreset);` — Sets the initial values of this instance.
- L173 _public prototype_ `virtual TArray<URenderGridPropBase*> GetAll() const override;`
- L177 _public prototype_ `TArray<URenderGridPropRemoteControl*> GetAllCasted() const;` — Returns all props, casted to URenderGridPropRemoteControl, for ease of use.
- L180 _public prototype_ `URenderGridPropRemoteControl* GetById(const FGuid& Id) const;` — Returns the prop with the given ID, or NULL if not found.
- L183 _public prototype_ `URenderGridPropRemoteControl* GetByLabel(const FString& Label) const;` — Returns the prop with the given label, or NULL if not found.
- L186 _public function_ `URemoteControlPreset* GetRemoteControlPreset() const` — Returns the remote control preset.
- L191 _protected member_ `TObjectPtr<URemoteControlPreset> RemoteControlPreset = nullptr;` — `UPROPERTY()` — The source of properties, which is a remote control preset.

#### class `URenderGridPropsSourceRemoteControl`  
`class URenderGridPropsSourceRemoteControl : public URenderGridPropsSourceBase`  
_L198-223_
- reflection: `UCLASS(BlueprintType, HideCategories=Object, Meta=(DontUseGenericSpawnObject="true"))`
- inherits: `URenderGridPropsSourceBase`
- desc: The remote control properties implementation of the render grid properties source abstraction.
- L204 _public function_ `virtual ERenderGridPropsSourceType GetType() const override`
- L205 _public prototype_ `virtual void SetSourceOrigin(UObject* SourceOrigin) override;`
- L206 _public prototype_ `virtual URenderGridPropsRemoteControl* GetProps() const override;`
- L210 _public prototype_ `void GetAvailablePresetGroups(TArray<FName>& OutPresetGroups) const;` — Returns (in the out parameter) the preset groups that are available in this remote control preset.
- L213 _public function_ `URemoteControlPreset* GetRemoteControlPreset() const` — Returns the remote control preset.
- L218 _protected member_ `TObjectPtr<URemoteControlPreset> RemoteControlPreset = nullptr;` — `UPROPERTY(VisibleInstanceOnly, Category="Render Grid|Remote Control")` — The source of properties, which is a remote control preset.
- L222 _protected member_ `FName ActivePresetGroup;` — `UPROPERTY(VisibleInstanceOnly, Category="Render Grid|Remote Control")` — The preset group (of the remote control preset) that we should obtain the properties from.

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/RenderGrid/RenderGridQueue.h` (Public)


#### struct `UE::RenderGrid::FRenderGridQueueCreateArgs`  
`struct FRenderGridQueueCreateArgs`  
_L41-79_
- desc: The arguments for the URenderGridQueue::Create function.
- L45 _public member_ `TStrongObjectPtr<URenderGrid> RenderGrid = nullptr;` — The render grid of the given render grid jobs that will be rendered.
- L48 _public member_ `TArray<TStrongObjectPtr<URenderGridJob>> RenderGridJobs;` — The specific render grid jobs that will be rendered.
- L51 _public member_ `TSubclassOf<UMoviePipelinePIEExecutor> PipelineExecutorClass = nullptr;` — If not null, it will override the movie pipeline executor class with this class.
- L54 _public member_ `TArray<TSubclassOf<UMoviePipelineSetting>> DisablePipelineSettingsClasses;` — The movie pipeline settings classes to disable (things like Anti-Aliasing, High-Res, etc).
- L57 _public member_ `TOptional<int32> Frame;` — The specific frame number that will be rendered.
- L60 _public member_ `TOptional<double> FramePosition;` — The specific frame number (percentage-wise, between 0.0 and 1.0) that will be rendered.
- L63 _public member_ `bool bIsBatchRender = false;` — Whether it should run the Begin and End Batch Render events or not.
- L66 _public member_ `bool bHeadless = false;` — Whether it should run invisibly (so without any UI elements popping up during rendering) or not.
- L69 _public member_ `bool bForceOutputImage = false;` — Whether it should make sure it will output an image or not (if this bool is true, it will test if JPG/PNG/etc output is enabled, if none are, it will enable PNG output).
- L72 _public member_ `bool bForceOnlySingleOutput = false;` — Whether it should make sure it will only output in a single format (if this bool is true, if for example JPG and PNG output are enabled, one will be disabled, so that there will only be 1 output that's enabled).
- L75 _public member_ `bool bForceUseSequenceFrameRate = false;` — Whether it should use the sequence's framerate rather than any manually set framerate (if this bool is true, it will make sure bUseCustomFrameRate is set to false).
- L78 _public member_ `bool bEnsureSequentialFilenames = false;` — Whether it should make sure it will output files named 0000000001, 0000000002, etc (if this bool is true, it will override the FileNameFormat to simply output the frame number, and it will add 1000000000 to that frame number to hopefully ensure that any negative frame numbers will not result in filenames starting with a minus character).

#### class `URenderGridMoviePipelineRenderJob`  
`class URenderGridMoviePipelineRenderJob : public UObject`  
_L87-176_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This class is responsible for the movie pipeline part of the rendering of the given render grid job.
- L93 _public prototype_ `static URenderGridMoviePipelineRenderJob* Create(URenderGridQueue* Queue, URenderGridJob* Job, const UE::RenderGrid::FRenderGridQueueCreateArgs& Args);` — Creates a new render job, it won't be started right away.
- L96 _public prototype_ `virtual void BeginDestroy() override;` — The destructor, cleans up the TPromise (if it's set).
- L99 _public prototype_ `TSharedFuture<void> Execute();` — Starts this render job.
- L102 _public prototype_ `void Cancel();` — Cancels this render job. Relies on the internal movie pipeline implementation of job canceling on whether this will do anything or not.
- L105 _public prototype_ `FString GetStatus() const;` — Retrieves the rendering status of the given render grid job.
- L108 _public prototype_ `float GetStatusPercentage() const;` — Retrieves the rendering status of the given render grid job.
- L111 _public prototype_ `int32 GetEngineWarmUpCount() const;` — Retrieves the "Engine Warm Up Count" value from the AntiAliasingSettings from the render preset that this render grid job uses.
- L115 _public prototype_ `void OnWaitForEngineWarmUpCount();` — An event that will be fired when the rendering process is waiting for this job's engine warm up.
- L118 _public prototype_ `void OnPreRenderEvent();` — An event that will be fired when the rendering process is executing the BeginJobRender event for this job.
- L121 _public prototype_ `void OnPostRenderEvent();` — An event that will be fired when the rendering process is executing the EndJobRender event for this job.
- L125 _public function_ `bool IsCanceled() const` — Returns true if this render job was canceled (which for example can be caused by calling Cancel(), or by closing the render popup).
- L128 _public function_ `bool CanExecute() const` — Returns true if this render job can render (otherwise it will be skipped).
- L131 _private prototype_ `void ComputePlaybackContext(bool& bOutAllowBinding);`
- L132 _private prototype_ `void ExecuteFinished(UMoviePipelineExecutorBase* InPipelineExecutor, const bool bSuccess);`
- L137 _protected member_ `TObjectPtr<URenderGridJob> RenderGridJob;` — `UPROPERTY(Transient)` — The render grid job that will be rendered.
- L141 _protected member_ `TObjectPtr<URenderGrid> RenderGrid;` — `UPROPERTY(Transient)` — The render grid that the render grid job (that will be rendered) belongs to.
- L145 _protected member_ `TObjectPtr<UMoviePipelineQueue> PipelineQueue;` — `UPROPERTY(Transient)` — The movie pipeline queue.
- L149 _protected member_ `TObjectPtr<UMoviePipelineExecutorBase> PipelineExecutor;` — `UPROPERTY(Transient)` — The movie pipeline executor.
- L153 _protected member_ `TObjectPtr<UMoviePipelineExecutorJob> PipelineExecutorJob;` — `UPROPERTY(Transient)` — The movie pipeline executor job of the given render grid job.
- L156 _protected member_ `TSharedPtr<TPromise<void>> Promise;` — The TPromise of the rendering process.
- L159 _protected member_ `TSharedFuture<void> PromiseFuture;` — The TFuture of the rendering process.
- L163 _protected member_ `FString Status;` — `UPROPERTY(Transient)` — The rendering status of the given render grid job.
- L167 _protected member_ `bool bCanExecute;` — `UPROPERTY(Transient)` — Whether the entry can execute, or whether it should just skip execution.
- L171 _protected member_ `bool bCanceled;` — `UPROPERTY(Transient)` — Whether the entry was canceled (like by calling Cancel(), or by closing the render popup).
- L175 _protected member_ `bool bFinished;` — `UPROPERTY(Transient)` — Whether the entry has finished (or was canceled).

#### class `URenderGridQueue`  
`class URenderGridQueue : public UObject, public FTickableGameObject`  
_L183-410_
- reflection: `UCLASS(BlueprintType, Meta=(DontUseGenericSpawnObject="true"))`
- inherits: `UObject,FTickableGameObject`
- desc: This class is responsible for rendering the given render grid jobs.
- L188 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRenderingQueueChanged);`
- L190 _public function_ `static FOnRenderingQueueChanged& OnRenderingQueueChanged()` — The event that will be fired when the currently rendering queue changes (like for example when the previous one has finished rendering).
- L194 _public prototype_ `static void CloseEditorOnCompletion();` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="execution execute finish close stop end done quit"))` — Call this function to make it so that the editor will be closed when all rendering queues have finished. This function has to only be called once.
- L198 _private prototype_ `static void RequestAppExitIfSetToExitOnCompletion();` — Closes the editor, but only if CloseEditorOnCompletion has been called.
- L202 _public prototype_ `static bool IsRenderingAny();` — Returns true if it's currently rendering any queues.
- L206 _public prototype_ `static URenderGridQueue* GetCurrentlyRenderingQueue();` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="executing execution execute running rendering"))` — Returns the currently rendering queue, or NULL if there isn't any currently rendering.
- L210 _public prototype_ `static int32 GetRemainingRenderingQueuesCount();` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="executing execution execute running rendering left todo queued"))` — Returns the number of rendering queues that are currently queued up. This also includes the currently rendering queue.
- L214 _private prototype_ `static void AddRenderingQueue(URenderGridQueue* Queue);` — Adds the given queue. Will automatically start rendering it if it's the only one currently.
- L217 _private prototype_ `static void DoNextRenderingQueue();` — Starts the next rendering queue, if there is one. Nothing will happen until the next tick.
- L221 _private member_ `static TArray<TObjectPtr<URenderGridQueue>> RenderingQueues;` — The queue of rendering queues. This contains the currently rendering queue, as well as the ones that should be rendered after it.
- L224 _private member_ `static FOnRenderingQueueChanged OnRenderingQueueChangedDelegate;` — The delegate for when data in the ExecutingQueues has changed.
- L227 _private member_ `static bool bExitOnCompletion;` — Whether the editor should be closed when all rendering queues finish rendering.
- L231 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L232 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L233 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L234 _public function_ `virtual bool IsTickableInEditor() const override`
- L235 _public function_ `virtual TStatId GetStatId() const override`
- L243 _public prototype_ `static URenderGridQueue* Create(const UE::RenderGrid::FRenderGridQueueCreateArgs& Args);` — Creates a new render queue, it won't be started right away.
- L247 _public prototype_ `FString ToDebugString() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(DisplayName="To Debug String (Render Grid Queue)", CompactNodeTitle="DEBUG"))` — Obtains a string representation of this object. Shouldn't be used for anything other than logging/debugging.
- L250 _public prototype_ `TSharedPtr<FJsonValue> ToDebugJson() const;` — Obtains a JSON representation of this object. Shouldn't be used for anything other than logging/debugging.
- L253 _public prototype_ `void Execute();` — Starts this render queue.
- L258 _public function_ `FGuid GetGuid() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue")` — Returns the GUID, which is randomly generated at creation.
- L262 _public function_ `void GenerateNewGuid()` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue")` — Randomly generates a new GUID.
- L266 _public prototype_ `void AddJob(URenderGridJob* Job);` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="render append"))` — Queues the given job.
- L270 _public prototype_ `void Pause();` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="wait"))` — Pauses the queue.
- L274 _public prototype_ `void Resume();` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="unwait unpause"))` — Resumes the queue.
- L278 _public prototype_ `void Cancel();` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="stop quit exit kill terminate end"))` — Cancels the current and the remaining queued jobs. Relies on the internal movie pipeline implementation of job canceling on whether this will stop the current render grid job from rendering or not. Will always prevent new render grid jobs from rendering.
- L282 _public function_ `bool IsStarted() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="stopped quited exited killed terminated ended succeeded completed finished canceled cancelled"))` — Returns true if this queue has been started.
- L286 _public function_ `bool IsPaused() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="stopped quited exited killed terminated ended succeeded completed finished canceled cancelled"))` — Returns true if this queue is currently paused.
- L290 _public function_ `bool IsCanceled() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="stopped quited exited killed terminated ended succeeded completed finished canceled cancelled"))` — Returns true if this queue has been canceled.
- L294 _public function_ `bool IsFinished() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="stopped quited exited killed terminated ended succeeded completed finished canceled cancelled"))` — Returns true if this queue has been canceled.
- L298 _public function_ `bool IsCurrentlyRendering() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="stopped quited exited killed terminated ended succeeded completed finished canceled cancelled"))` — Returns true if this queue is the one that's currently rendering, returns false if it hasn't started yet, or if it's waiting in the queue, or if it has finished.
- L302 _public function_ `URenderGrid* GetRenderGrid() const` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering"))` — Retrieves the rendering status of the given render grid job.
- L306 _public prototype_ `URenderGridJob* GetCurrentlyRenderingJob() const;` — `UFUNCTION(BlueprintCallable, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain"))` — Retrieves the currently rendering render grid job, can return NULL.
- L310 _public prototype_ `FString GetJobStatus(URenderGridJob* Job) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain text"))` — Retrieves the rendering status of the given render grid job. Will return an empty string if this job wasn't found in this queue.
- L314 _public prototype_ `float GetJobStatusPercentage(URenderGridJob* Job) const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain number amount finished complete completion"))` — Returns the percentage of the rendering status of the given render grid job. Will return 0 if this job wasn't found in this queue.
- L318 _public prototype_ `TArray<URenderGridJob*> GetJobs() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain"))` — Returns all the jobs that have been and will be rendered.
- L322 _public prototype_ `int32 GetJobsCount() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain number amount"))` — Returns the number of jobs that have been and will be rendered.
- L326 _public prototype_ `int32 GetJobsRemainingCount() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain number amount finished"))` — Returns the number of jobs that are still left to render, includes the job that is currently rendering.
- L330 _public prototype_ `int32 GetJobsCompletedCount() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain number amount finished"))` — Returns the number of jobs that have finished rendering. Basically just returns [Get Jobs Count] minus [Get Jobs Remaining Count].
- L334 _public prototype_ `FString GetStatus() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain text"))` — Returns the status of the rendering process.
- L338 _public prototype_ `float GetStatusPercentage() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid Queue", Meta=(Keywords="rendering progression obtain number amount finished complete completion"))` — Returns the percentage of jobs finished, this includes the progression of the job that is currently rendering.
- L341 _protected prototype_ `void OnStart();`
- L342 _protected prototype_ `void OnProcessJob(URenderGridJob* Job);`
- L343 _protected prototype_ `void OnFinish();`
- L348 _protected member_ `FGuid Guid;` — `UPROPERTY()` — The unique ID of this queue.
- L351 _protected member_ `UE::RenderGrid::FRenderGridQueueCreateArgs Args;` — The queue containing the render actions.
- L354 _protected member_ `TSharedPtr<UE::RenderGrid::Private::FRenderGridGenericExecutionQueue> Queue;` — The queue containing the render actions.
- L358 _protected member_ `TArray<TObjectPtr<URenderGridJob>> RemainingJobs;` — `UPROPERTY(Transient)` — The render grid jobs that are to be rendered, removed when one is grabbed from it and added to the execution queue.
- L362 _protected member_ `TMap<TObjectPtr<URenderGridJob>, TObjectPtr<URenderGridMoviePipelineRenderJob>> Entries;` — `UPROPERTY(Transient)` — The render grid jobs that are to be rendered, mapped to the movie pipeline render job of each specific render grid job.
- L366 _protected member_ `TObjectPtr<URenderGridJob> CurrentJob;` — `UPROPERTY(Transient)` — The render grid jobs that is currently being rendered.
- L370 _protected member_ `TObjectPtr<URenderGridMoviePipelineRenderJob> CurrentEntry;` — `UPROPERTY(Transient)` — The movie pipeline render job that is currently being rendered.
- L374 _protected member_ `TObjectPtr<URenderGrid> RenderGrid;` — `UPROPERTY(Transient)` — The render grid of the given render grid job that will be rendered.
- L378 _protected member_ `bool bStarted;` — `UPROPERTY(Transient)` — Whether the queue has been started yet.
- L382 _protected member_ `bool bPaused;` — `UPROPERTY(Transient)` — Whether the queue has been paused.
- L386 _protected member_ `bool bCanceled;` — `UPROPERTY(Transient)` — Whether the queue has been canceled.
- L390 _protected member_ `bool bFinished;` — `UPROPERTY(Transient)` — Whether the queue has been finished.
- L394 _protected member_ `FRenderGridManagerPreviousPropValues PreviousProps;` — `UPROPERTY(Transient)` — The property values that have been overwritten by the currently applied render grid job property values.
- L398 _protected member_ `FRenderGridPreviousEngineFpsSettings PreviousFrameLimitSettings;` — `UPROPERTY(Transient)` — The engine framerate settings values that have been overwritten by the currently applied engine framerate settings values.
- L402 _public function_ `UE::RenderGrid::FOnRenderGridQueueStarted& OnExecuteStarted()` — A delegate for when the queue is about to start.
- L405 _public function_ `UE::RenderGrid::FOnRenderGridQueueFinished& OnExecuteFinished()` — A delegate for when the queue has finished.
- L408 _private member_ `UE::RenderGrid::FOnRenderGridQueueStarted OnExecuteStartedDelegate;`
- L409 _private member_ `UE::RenderGrid::FOnRenderGridQueueFinished OnExecuteFinishedDelegate;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace RenderGrid` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace RenderGrid` (scope `UE`)
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRenderGridQueueStarted, URenderGridQueue* );` — A delegate for when a rendering queue is about to start.
- L33 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRenderGridQueueStarted, URenderGridQueue* );` (scope `UE::RenderGrid`) — A delegate for when a rendering queue is about to start.
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRenderGridQueueFinished, URenderGridQueue* , bool );` — A delegate for when a rendering queue has finished.
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRenderGridQueueFinished, URenderGridQueue* , bool );` (scope `UE::RenderGrid`) — A delegate for when a rendering queue has finished.
- L188 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRenderingQueueChanged);`

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/RenderGridLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogRenderGrid, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogRenderGrid, Log, All);`

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/Utils/RenderGridGenericExecutionQueue.h` (Public)


#### struct `UE::RenderGrid::Private::FRenderGridGenericExecutionQueueDelay`  
`struct FRenderGridGenericExecutionQueueDelay`  
_L16-47_
- desc: Struct containing the delay data (such as the frames or the seconds of delay this delay requires before it can move on to the next step).
- L19 _public function_ `static FRenderGridGenericExecutionQueueDelay Frames(const int64 Frames)`
- L20 _public function_ `static FRenderGridGenericExecutionQueueDelay Seconds(const double Seconds)`
- L21 _public function_ `static FRenderGridGenericExecutionQueueDelay FramesOrSeconds(const int64 Frames, const double Seconds)`
- L24 _public function_ `FRenderGridGenericExecutionQueueDelay(TYPE_OF_NULLPTR)`
- L28 _private function_ `FRenderGridGenericExecutionQueueDelay()`
- L31 _private function_ `explicit FRenderGridGenericExecutionQueueDelay(const int64 Frames) : MinimumFrames(Frames)`
- L35 _private function_ `explicit FRenderGridGenericExecutionQueueDelay(const double Seconds) : MinimumSeconds(Seconds)`
- L39 _private function_ `explicit FRenderGridGenericExecutionQueueDelay(const int64 Frames, const double Seconds) : MinimumFrames(Frames) , MinimumSeconds(Seconds)`
- L45 _public member_ `const int64 MinimumFrames = 0;`
- L46 _public member_ `const double MinimumSeconds = 0.0f;`

#### struct `UE::RenderGrid::Private::FRenderGridGenericExecutionQueueEntry`  
`struct FRenderGridGenericExecutionQueueEntry`  
_L65-89_
- desc: Struct containing the data of a queued action.
- L68 _public function_ `FRenderGridGenericExecutionQueueEntry(const FRenderGridGenericExecutionQueueAction& Action) : ActionRegular(Action)`
- L72 _public function_ `FRenderGridGenericExecutionQueueEntry(const FRenderGridGenericExecutionQueueActionReturningDelay& Action) : ActionReturningDelay(Action)`
- L76 _public function_ `FRenderGridGenericExecutionQueueEntry(const FRenderGridGenericExecutionQueueActionReturningDelayFuture& Action) : ActionReturningDelayFuture(Action)`
- L80 _public function_ `FRenderGridGenericExecutionQueueEntry(const FRenderGridGenericExecutionQueueActionReturningDelayFutureReturningDelay& Action) : ActionReturningDelayFutureReturningDelay(Action)`
- L85 _public member_ `const FRenderGridGenericExecutionQueueAction ActionRegular;`
- L86 _public member_ `const FRenderGridGenericExecutionQueueActionReturningDelay ActionReturningDelay;`
- L87 _public member_ `const FRenderGridGenericExecutionQueueActionReturningDelayFuture ActionReturningDelayFuture;`
- L88 _public member_ `const FRenderGridGenericExecutionQueueActionReturningDelayFutureReturningDelay ActionReturningDelayFutureReturningDelay;`

#### class `UE::RenderGrid::Private::FRenderGridGenericExecutionQueue`  
`class FRenderGridGenericExecutionQueue : public TSharedFromThis<FRenderGridGenericExecutionQueue>, public FTickableGameObject`  
_L95-172_
- inherits: `TSharedFromThis<FRenderGridGenericExecutionQueue>,FTickableGameObject`
- desc: This class provides generic queue support, with built-in support for delays between actions.
- L99 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L100 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L101 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L102 _public function_ `virtual bool IsTickableInEditor() const override`
- L103 _public function_ `virtual TStatId GetStatId() const override`
- L111 _public function_ `void Add(const FRenderGridGenericExecutionQueueEntry& Entry)` — Queues the given action.
- L114 _public function_ `void Delay(const FRenderGridGenericExecutionQueueDelay& Delay)` — Queues the given delay.
- L117 _public function_ `void DelayFrames(const int64 Frames)` — Queues the given delay, which will wait for the given number of frames.
- L120 _public function_ `void DelaySeconds(const double Seconds)` — Queues the given delay, which will wait for the given number of seconds.
- L123 _public function_ `void DelayFramesOrSeconds(const int64 Frames, const double Seconds)` — Queues the given delay, which will wait for the given number of frames or seconds, whatever takes the longest.
- L126 _public prototype_ `void Start();` — Starts the execution of this queue.
- L129 _public prototype_ `void Stop();` — Stops (pauses) the execution of this queue, this can be resumed by calling the Start function again. Currently queued up delays will continue to run/expire.
- L132 _public function_ `bool IsRunning()` — Returns true if Start() has been called and Stop() hasn't been called yet.
- L136 _protected prototype_ `void ExecuteNext();` — Executes the next delay (if there are any), otherwise it executes the next entry (action).
- L139 _protected prototype_ `bool ExecuteNextDelay();` — Executes the next delay, returns true if it found any, returns false if there were no queued up delays.
- L142 _protected prototype_ `bool ExecuteNextEntry();` — Executes the next entry (action), returns true if it found and executed an entry, returns false if there were no queued up entries.
- L145 _protected function_ `void QueueDelay(const FRenderGridGenericExecutionQueueDelay& Delay)` — Adds the delay to the queued delays.
- L149 _protected member_ `TDoubleLinkedList<FRenderGridGenericExecutionQueueEntry> QueuedEntries;` — The queued up entries (actions).
- L152 _protected member_ `TDoubleLinkedList<FRenderGridGenericExecutionQueueDelay> QueuedDelays;` — The queued up delays.
- L156 _protected member_ `bool bRunning = false;` — Whether it has started (and hasn't been stopped/paused yet). This means that if this is true, Start() has been called, and Stop() hasn't been called yet since then.
- L159 _protected member_ `bool bExecuting = false;` — Whether it's currently executing a delay or an entry (action). False means there were no delays and entries queued up anymore.
- L162 _protected member_ `int64 DelayRemainingFrames = 0;` — The number of frames the current delay has to wait for.
- L165 _protected member_ `double DelayRemainingSeconds = 0.0f;` — The number of seconds the current delay has to wait for.
- L168 _protected member_ `TSharedFuture<void> DelayRemainingFuture;` — The TFuture it's waiting for (if any).
- L171 _protected member_ `TSharedFuture<FRenderGridGenericExecutionQueueDelay> DelayRemainingFutureReturningDelay;` — The TFuture it's waiting for (if any), that can return a delay.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RenderGrid` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L51 _delegate_ `DECLARE_DELEGATE(FRenderGridGenericExecutionQueueAction);` — A delegate for a queued action.
- L51 _prototype_ `DECLARE_DELEGATE(FRenderGridGenericExecutionQueueAction);` (scope `UE::RenderGrid::Private`) — A delegate for a queued action.
- L54 _delegate_ `DECLARE_DELEGATE_RetVal(FRenderGridGenericExecutionQueueDelay, FRenderGridGenericExecutionQueueActionReturningDelay);` — A delegate for a queued action, that optionally requires a delay after its execution.
- L54 _prototype_ `DECLARE_DELEGATE_RetVal(FRenderGridGenericExecutionQueueDelay, FRenderGridGenericExecutionQueueActionReturningDelay);` (scope `UE::RenderGrid::Private`) — A delegate for a queued action, that optionally requires a delay after its execution.
- L57 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedFuture<void>, FRenderGridGenericExecutionQueueActionReturningDelayFuture);` — A delegate for a queued action, that will delay execution until the returned TFuture finishes.
- L57 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedFuture<void>, FRenderGridGenericExecutionQueueActionReturningDelayFuture);` (scope `UE::RenderGrid::Private`) — A delegate for a queued action, that will delay execution until the returned TFuture finishes.
- L60 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedFuture<FRenderGridGenericExecutionQueueDelay>, FRenderGridGenericExecutionQueueActionReturningDelayFutureReturningDelay);` — A delegate for a queued action, that will delay execution until the returned TFuture finishes, which can optionally return yet another delay if required.
- L60 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedFuture<FRenderGridGenericExecutionQueueDelay>, FRenderGridGenericExecutionQueueActionReturningDelayFutureReturningDelay);` (scope `UE::RenderGrid::Private`) — A delegate for a queued action, that will delay execution until the returned TFuture finishes, which can optionally return yet another delay if required.
- L114 _function_ `void Delay(const FRenderGridGenericExecutionQueueDelay& Delay)` (scope `UE::RenderGrid::Private::FRenderGridGenericExecutionQueue::Delay`) — Queues the given delay.

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/Utils/RenderGridRemoteControlUtils.h` (Public)


#### class `URenderGridRemoteControlUtils`  
`class URenderGridRemoteControlUtils : public UBlueprintFunctionLibrary`  
_L13-114_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static void ParseJsonAsByte(const FString& Json, const uint8 DefaultValue, bool& bSuccess, uint8& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L22 _public prototype_ `static void ParseJsonAsInt32(const FString& Json, const int32 DefaultValue, bool& bSuccess, int32& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L25 _public prototype_ `static void ParseJsonAsInt64(const FString& Json, const int64 DefaultValue, bool& bSuccess, int64& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L28 _public prototype_ `static void ParseJsonAsFloat(const FString& Json, const double DefaultValue, bool& bSuccess, double& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control double"))`
- L31 _public prototype_ `static void ParseJsonAsBoolean(const FString& Json, bool DefaultValue, bool& bSuccess, bool& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L34 _public prototype_ `static void ParseJsonAsString(const FString& Json, const FString& DefaultValue, bool& bSuccess, FString& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L37 _public prototype_ `static void ParseJsonAsName(const FString& Json, const FName& DefaultValue, bool& bSuccess, FName& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L40 _public prototype_ `static void ParseJsonAsText(const FString& Json, const FText& DefaultValue, bool& bSuccess, FText& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L43 _public prototype_ `static void ParseJsonAsObjectReference(const FString& Json, UObject* DefaultValue, bool& bSuccess, UObject*& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L46 _public prototype_ `static void ParseJsonAsClassReference(const FString& Json, UClass* DefaultValue, bool& bSuccess, UClass*& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L49 _public prototype_ `static void ParseJsonAsStruct(const FString& Json, const FInstancedStruct& DefaultValue, bool& bSuccess, FInstancedStruct& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L52 _public prototype_ `static void ParseJsonAsVector(const FString& Json, const FVector& DefaultValue, bool& bSuccess, FVector& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L55 _public prototype_ `static void ParseJsonAsRotator(const FString& Json, const FRotator& DefaultValue, bool& bSuccess, FRotator& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L58 _public prototype_ `static void ParseJsonAsTransform(const FString& Json, const FTransform& DefaultValue, bool& bSuccess, FTransform& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L61 _public prototype_ `static void ParseJsonAsColor(const FString& Json, const FColor& DefaultValue, bool& bSuccess, FColor& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L64 _public prototype_ `static void ParseJsonAsLinearColor(const FString& Json, const FLinearColor& DefaultValue, bool& bSuccess, FLinearColor& Value);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L68 _public prototype_ `static void ByteToJson(uint8 Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L71 _public prototype_ `static void Int32ToJson(int32 Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L74 _public prototype_ `static void Int64ToJson(int64 Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L77 _public prototype_ `static void FloatToJson(double Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control double"))`
- L80 _public prototype_ `static void BooleanToJson(bool Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L83 _public prototype_ `static void StringToJson(const FString& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L86 _public prototype_ `static void NameToJson(const FName& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L89 _public prototype_ `static void TextToJson(const FText& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L92 _public prototype_ `static void ObjectReferenceToJson(UObject* Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L95 _public prototype_ `static void ClassReferenceToJson(UClass* Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L98 _public prototype_ `static void StructToJson(const FInstancedStruct& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L101 _public prototype_ `static void VectorToJson(const FVector& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L104 _public prototype_ `static void RotatorToJson(const FRotator& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L107 _public prototype_ `static void TransformToJson(const FTransform& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L110 _public prototype_ `static void ColorToJson(const FColor& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`
- L113 _public prototype_ `static void LinearColorToJson(const FLinearColor& Value, FString& Json);` — `UFUNCTION(BlueprintPure, Category="Render Grid Utils", Meta=(Keywords="remote control"))`

### `Plugins/Experimental/RenderGrid/Source/RenderGrid/Public/Utils/RenderGridUtils.h` (Public)


#### struct `FRenderGridPreviousEngineFpsSettings`  
`struct FRenderGridPreviousEngineFpsSettings`  
_L19-51_
- reflection: `USTRUCT()`
- desc: This struct keeps track of the values of the GEngine framerate settings before new values were applied, so we can rollback to the previous state.
- L26 _public member_ `bool bHasBeenSet = false;` — `UPROPERTY()` — Whether the values have been set or not.
- L30 _public member_ `bool bUseFixedFrameRate = false;` — `UPROPERTY()` — The previous value of GEngine->bUseFixedFrameRate.
- L34 _public member_ `bool bForceDisableFrameRateSmoothing = false;` — `UPROPERTY()` — The previous value of GEngine->bForceDisableFrameRateSmoothing.
- L38 _public member_ `float MaxFps = 0;` — `UPROPERTY()` — The previous value of GEngine->GetMaxFPS().
- L42 _public member_ `bool bVSync = false;` — `UPROPERTY()` — The previous value of console variable "r.VSync".
- L46 _public member_ `bool bVSyncEditor = false;` — `UPROPERTY()` — The previous value of console variable "r.VSyncEditor".
- L50 _public member_ `bool bThrottleCPUWhenNotForeground = false;` — `UPROPERTY()` — The previous value of UEditorPerformanceSettings->bThrottleCPUWhenNotForeground.

#### class `UE::RenderGrid::Private::FRenderGridUtils`  
`class FRenderGridUtils`  
_L59-203_
- desc: A class containing static utility functions for the RenderGrid module.
- L65 _public prototype_ `static bool IsImage(const FString& ImagePath);` — Returns true if the given file is likely a valid image.
- L74 _public prototype_ `static UTexture2D* GetImage(const FString& ImagePath, UTexture2D* Texture2D, bool& bOutReusedGivenTexture2D);` — Loads an image from the disk, tries to automatically figure out the correct image format. Returns NULL if it fails. Will re-use the given Texture2D if possible, bOutReusedGivenTexture2D will be true if it was possible.
- L82 _public prototype_ `static UTexture2D* BytesToImage(const TArray<uint8>& ByteArray, const EImageFormat ImageFormat);` — Converts bytes into a texture. Returns NULL if it fails.
- L91 _public prototype_ `static UTexture2D* BytesToExistingImage(const TArray<uint8>& ByteArray, const EImageFormat ImageFormat, UTexture2D* Texture2D, bool& bOutReusedGivenTexture2D);` — Converts bytes into an texture. Returns NULL if it fails. Will re-use the given Texture2D if possible, bOutReusedGivenTexture2D will be true if it was possible.
- L98 _public prototype_ `static UTexture2D* DataToTexture2D(int32 Width, int32 Height, const void* Src, SIZE_T Count);` — Converts texture data into a texture. Returns NULL if it fails.
- L107 _public prototype_ `static UTexture2D* DataToExistingTexture2D(int32 Width, int32 Height, const void* Src, SIZE_T Count, UTexture2D* Texture2D, bool& bOutReusedGivenTexture2D);` — Converts texture data into an texture. Returns NULL if it fails. Will re-use the given Texture2D if possible, bOutReusedGivenTexture2D will be true if it was possible.
- L113 _public prototype_ `static TArray<FString> GetFiles(const FString& Directory, const bool bRecursive = false);` — Returns the paths of the files that exist in the given directory path.
- L120 _public prototype_ `static TArray<uint8> GetFileData(const FString& File);` — Returns the data of the file, returns an empty byte array if the file doesn't exist. Note: Can only open files of 2GB and smaller, will return an empty byte array if it is bigger than 2GB.
- L126 _public prototype_ `static void DeleteDirectory(const FString& Directory);` — Deletes all files and directories in the given directory, including the given directory.
- L131 _public prototype_ `static void EmptyDirectory(const FString& Directory);` — Deletes all files and directories in the given directory, won't delete the given directory.
- L137 _public prototype_ `static FString NormalizeOutputDirectory(const FString& OutputDirectory);` — Returns a normalized directory path.
- L143 _public prototype_ `static FString PurgeJobIdOrReturnEmptyString(const FString& JobId);` — Returns a job ID with all invalid characters removed from it. Returns an empty string if it contains no valid characters.
- L148 _public prototype_ `static FString PurgeJobId(const FString& JobId);` — Returns a job ID with all invalid characters removed from it. Returns string "0" if it contains no valid characters.
- L154 _public prototype_ `static FString PurgeJobIdOrGenerateUniqueId(URenderGrid* Grid, const FString& JobId);` — Returns a job ID with all invalid characters removed from it. Returns a newly generated unique ID if it contains no valid characters. The generated string is only unique relative to the job IDs that currently exist in the given RenderGrid.
- L159 _public prototype_ `static FString PurgeJobName(const FString& JobName);` — Returns a job name with all invalid characters removed from it. Returns an empty string if it contains no valid characters.
- L164 _public prototype_ `static FString NormalizeJobOutputDirectory(const FString& NewOutputDirectory);` — Returns a job output directory that's converted to a full path (if it's currently relative) and that also has the project directory path replaced by "{project_dir}" (if the given path contains that string).
- L169 _public prototype_ `static FString DenormalizeJobOutputDirectory(const FString& NormalizedOutputDirectory);` — Returns a job output directory that's a usable valid filesystem path. Replaces string "{project_dir}" by the project directory.
- L175 _public prototype_ `static FString ToJsonString(const TSharedPtr<FJsonValue>& Value, const bool PrettyPrint = false);` — Converts the given FJsonValue to a string.
- L180 _public prototype_ `static TSharedPtr<FJsonValue> ParseJson(const FString& Json);` — Parses the given JSON string and returns the FJsonValue. Will return an invalid pointer if the given JSON couldn't be parsed.
- L186 _public prototype_ `static FString GetRemoteControlValueJsonFromBytes(const TArray<uint8>& ValueBytes, const bool PrettyPrint = false);` — Converts the low-level FProperty binary data to a clean JSON string.
- L191 _public prototype_ `static TArray<uint8> GetRemoteControlValueBytesFromJson(const TArray<uint8>& OldValueBytes, const FString& NewValueJson);` — Converts a clean JSON string to low-level FProperty binary data.
- L197 _public prototype_ `static FRenderGridPreviousEngineFpsSettings DisableFpsLimit();` — Disables the current FPS limiting, returns the previous settings which allow you to revert back to the previous state.
- L202 _public prototype_ `static void RestoreFpsLimit(const FRenderGridPreviousEngineFpsSettings& Settings);` — Reverts back to the previous (given) state.

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace RenderGrid` (scope `UE`)
- L54 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
