# Plugins / SequencerScripting

- module root: `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting`
- headers: 31; symbols: 593
- symbol kinds: class=43, enum=1, enumerator=2, function=243, macro=16, member=49, prototype=223, struct=4, typedef=12
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, LevelSequence, Slate, SlateCore, UniversalObjectLocator
- PublicDependencyModuleNames: Core, MovieScene, MovieSceneTracks, TimeManagement

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingActorReference.h` (Private)


#### class `UMovieSceneScriptingActorReferenceKey`  
`class UMovieSceneScriptingActorReferenceKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneActorReferenceChannel, FMovieSceneActorReferenceKey>`  
_L21-63_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneActorReferenceChannel,FMovieSceneActorReferenceKey>`
- desc: Exposes a Sequencer Actor Reference type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L31 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Actor Reference)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L40 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Actor Reference)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L47 _public function_ `FMovieSceneObjectBindingID GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Actor Reference)"))` — Gets the value for this key from the owning channel. @return	The object binding for this key.
- L58 _public function_ `void SetValue(const FMovieSceneObjectBindingID& InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Actor Reference)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new object binding for this key.

#### class `UMovieSceneScriptingActorReferenceChannel`  
`class UMovieSceneScriptingActorReferenceChannel : public UMovieSceneScriptingChannel`  
_L66-209_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L70 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneActorReferenceChannel, UMovieSceneScriptingActorReferenceKey, FMovieSceneActorReferenceKey>;`
- L82 _public function_ `UMovieSceneScriptingActorReferenceKey* AddKey(const FFrameNumber InTime, FMovieSceneObjectBindingID NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Actor Reference)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L92 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Actor Reference)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L103 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Actor Reference)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingActorReferenceKeys contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L115 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Actor Reference)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L125 _public function_ `void SetDefault(FMovieSceneObjectBindingID InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Actor Reference)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L136 _public function_ `FMovieSceneObjectBindingID GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Actor Reference)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L154 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Actor Reference)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L185 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Actor Reference)"))` — @return Does this channel have a default value set?
- L200 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Actor Reference)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L206 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L207 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L208 _public member_ `TMovieSceneChannelHandle<FMovieSceneActorReferenceChannel> ChannelHandle;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingBool.h` (Private)


#### class `UMovieSceneScriptingBoolKey`  
`class UMovieSceneScriptingBoolKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneBoolChannel, bool>`  
_L20-60_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneBoolChannel,bool>`
- desc: Exposes a Sequencer bool type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L30 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Bool)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L39 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Bool)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L46 _public function_ `bool GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Bool)"))` — Gets the value for this key from the owning channel. @return	The value for this key.
- L56 _public function_ `void SetValue(bool InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Bool)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new value for this key.

#### class `UMovieSceneScriptingBoolChannel`  
`class UMovieSceneScriptingBoolChannel : public UMovieSceneScriptingChannel`  
_L63-205_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L67 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneBoolChannel, UMovieSceneScriptingBoolKey, bool>;`
- L79 _public function_ `UMovieSceneScriptingBoolKey* AddKey(const FFrameNumber& InTime, bool NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta=(DisplayName = "Add Key (Bool)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L88 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta=(DisplayName = "Remove Key (Bool)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L99 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Bool)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingBoolKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L111 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Bool)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L120 _public function_ `int32 GetNumKeys() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Num Keys (Bool)"))` — Returns number of keys in this channel.
- L131 _public function_ `TArray<bool> EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Bool)"))` — Gets baked keys in this channel. @return	An array of values contained by this channel. Returns baked keys in the specified range.
- L142 _public function_ `FSequencerScriptingRange ComputeEffectiveRange() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Compute Effective Range (Bool)"))` — Compute the effective range of this channel, for example, the extents of its key times @return A range that represents the greatest range of times occupied by this channel, in the sequence's frame resolution
- L152 _public function_ `void SetDefault(bool InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Bool)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L162 _public function_ `bool GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Bool)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L172 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Bool)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L181 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Bool)"))` — @return Does this channel have a default value set?
- L196 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Bool)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L202 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L203 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L204 _public member_ `TMovieSceneChannelHandle<FMovieSceneBoolChannel> ChannelHandle;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingByte.h` (Private)


#### class `UMovieSceneScriptingByteKey`  
`class UMovieSceneScriptingByteKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneByteChannel, uint8>`  
_L22-62_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneByteChannel,uint8>`
- desc: Exposes a Sequencer byte/enum type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L32 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Enum)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L41 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Enum)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L48 _public function_ `uint8 GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Enum)"))` — Gets the value for this key from the owning channel. @return	The value for this key.
- L58 _public function_ `void SetValue(uint8 InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Enum)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new value for this key.

#### class `UMovieSceneScriptingByteChannel`  
`class UMovieSceneScriptingByteChannel : public UMovieSceneScriptingChannel`  
_L65-177_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L69 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneByteChannel, UMovieSceneScriptingByteKey, uint8>;`
- L82 _public function_ `UMovieSceneScriptingByteKey* AddKey(const FFrameNumber& InTime, uint8 NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, EMovieSceneKeyInterpolation InInterpolation = EMovieSceneKeyInterpolation::Auto)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Enum)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @param	InInterpolation	Interpolation method the key should use. @return	The key that was created with the specified values at the specified time.
- L91 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Enum)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L102 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Enum)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingByteKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L114 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Enum)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L124 _public function_ `void SetDefault(uint8 InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Enum)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L134 _public function_ `uint8 GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Enum)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L144 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Enum)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L153 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Enum)"))` — @return Does this channel have a default value set?
- L168 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Enum)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L174 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L175 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L176 _public member_ `TMovieSceneChannelHandle<FMovieSceneByteChannel> ChannelHandle;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingDouble.h` (Private)


#### class `UMovieSceneScriptingDoubleKey`  
`class UMovieSceneScriptingDoubleKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneDoubleChannel, FMovieSceneDoubleValue>`  
_L24-225_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneDoubleChannel,FMovieSceneDoubleValue>`
- desc: Exposes a Sequencer double type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L34 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Double)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L43 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Double)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L50 _public function_ `double GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Double)"))` — Gets the value for this key from the owning channel. @return	The double value this key represents.
- L60 _public function_ `void SetValue(double InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Double)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new double value for this key.
- L72 _public function_ `ERichCurveInterpMode GetInterpolationMode() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Gets the interpolation mode for this key from the owning channel. @return	Interpolation mode this key uses to interpolate between this key and the next.
- L82 _public function_ `void SetInterpolationMode(ERichCurveInterpMode InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the interpolation mode for this key, reflecting it in the owning channel. @param InNewValue	Interpolation mode this key should use to interpolate between this key and the next.
- L94 _public function_ `ERichCurveTangentMode GetTangentMode() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Gets the tangent mode for this key from the owning channel. @return	Tangent mode that this key is using specifying which tangent values are respected when evaluating.
- L104 _public function_ `void SetTangentMode(ERichCurveTangentMode InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the tangent mode for this key, reflecting it in the owning channel. @param InNewValue	Tangent mode that this key should use to specify which tangent values are respected when evaluating. See ERichCurveTangentMode for more details.
- L116 _public function_ `float GetArriveTangent() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the arriving tangent at this key @return Arrival Tangent value. Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L126 _public function_ `void SetArriveTangent(float InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the arriving tangent at this key. @param InNewValue	Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L139 _public function_ `float GetLeaveTangent() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the leaving tangent at this key @return Leaving Tangent value. Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L149 _public function_ `void SetLeaveTangent(float InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the leaving tangent at this key. @param InNewValue	Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L162 _public function_ `ERichCurveTangentWeightMode GetTangentWeightMode() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the tangent weight mode at this key @return Tangent Weight Mode. See ERichCurveTangentWeightMode for more detail on what each mode does.
- L172 _public function_ `void SetTangentWeightMode(ERichCurveTangentWeightMode InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the tangent weight mode at this key. @param InNewValue	Specifies which tangent weights should be respected when evaluating the key.
- L185 _public function_ `float GetArriveTangentWeight() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedArrive or RCTWM_WeightedBoth, the weight of the arriving tangent on the left side. @return Tangent Weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.
- L195 _public function_ `void SetArriveTangentWeight(float InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedArrive or RCTWM_WeightedBoth, the weight of the arriving tangent on the left side. @param InNewValue	Specifies the new arriving tangent weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.
- L208 _public function_ `float GetLeaveTangentWeight() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedLeave or RCTWM_WeightedBoth, the weight of the leaving tangent on the right side. @return Tangent Weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.
- L218 _public function_ `void SetLeaveTangentWeight(float InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedLeave or RCTWM_WeightedBoth, the weight of the leaving tangent on the right side. @param InNewValue	Specifies the new leaving tangent weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.

#### class `UMovieSceneScriptingDoubleChannel`  
`class UMovieSceneScriptingDoubleChannel : public UMovieSceneScriptingChannel`  
_L228-436_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L232 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneDoubleChannel, UMovieSceneScriptingDoubleKey, double>;`
- L245 _public function_ `UMovieSceneScriptingDoubleKey* AddKey(const FFrameNumber& InTime, double NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, EMovieSceneKeyInterpolation InInterpolation = EMovieSceneKeyInterpolation::Auto)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Double)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @param	InInterpolation	Interpolation method the key should use. @return	The key that was created with the specified values at the specified time.
- L254 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Double)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L265 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Double)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingDoubleKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L277 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Double)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L285 _public function_ `int32 GetNumKeys() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Num Keys (Double)"))` — Returns number of keys in this channel.
- L296 _public function_ `TArray<double> EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Double)"))` — Gets baked keys in this channel. @return	An array of double's contained by this channel. Returns baked keys in the specified range.
- L307 _public function_ `FSequencerScriptingRange ComputeEffectiveRange() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Compute Effective Range (Double)"))` — Compute the effective range of this channel, for example, the extents of its key times @return A range that represents the greatest range of times occupied by this channel, in the sequence's frame resolution
- L316 _public function_ `ERichCurveExtrapolation GetPreInfinityExtrapolation() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — @return Gets the Pre-infinity extrapolation state. See ERichCurveExtrapolation for more detail.
- L333 _public function_ `void SetPreInfinityExtrapolation(ERichCurveExtrapolation InExtrapolation)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the Pre-infinity extrapolation state. See ERichCurveExtrapolation for more detail. @param InExtrapolation The new extrapolation mode this key should use for evaluating before this key.
- L349 _public function_ `ERichCurveExtrapolation GetPostInfinityExtrapolation() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — @return Gets the Post-infinity extrapolation state. See ERichCurveExtrapolation for more detail.
- L366 _public function_ `void SetPostInfinityExtrapolation(ERichCurveExtrapolation InExtrapolation)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the Post-infinity extrapolation state. See ERichCurveExtrapolation for more detail. @param InExtrapolation The new extrapolation mode this key should use for evaluating after this key.
- L383 _public function_ `void SetDefault(double InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Double)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L393 _public function_ `double GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Double)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L403 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Double)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L412 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Double)"))` — @return Does this channel have a default value set?
- L427 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Double)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L433 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L434 _public member_ `TMovieSceneChannelHandle<FMovieSceneDoubleChannel> ChannelHandle;`
- L435 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingEvent.h` (Private)


#### class `UMovieSceneScriptingEventKey`  
`class UMovieSceneScriptingEventKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneEventChannel, FMovieSceneEvent>`  
_L17-57_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneEventChannel,FMovieSceneEvent>`
- desc: Exposes a Sequencer Event type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L27 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Event)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L36 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Event)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L43 _public function_ `FMovieSceneEvent GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Event)"))` — Gets the value for this key from the owning channel. @return	The event payload for this key which contains an event name and data.
- L53 _public function_ `void SetValue(const FMovieSceneEvent& InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Event)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new event payload for this key.

#### class `UMovieSceneScriptingEventChannel`  
`class UMovieSceneScriptingEventChannel : public UMovieSceneScriptingChannel`  
_L60-133_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L64 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneEventChannel, UMovieSceneScriptingEventKey, FMovieSceneEvent>;`
- L76 _public function_ `UMovieSceneScriptingEventKey* AddKey(const FFrameNumber& InTime, FMovieSceneEvent NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Event)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L85 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Event)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L96 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Event)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingEventKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L108 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Event)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L123 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Event)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L129 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L130 _public member_ `TMovieSceneChannelHandle<FMovieSceneEventChannel> ChannelHandle;`
- L131 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingFloat.h` (Private)


#### class `UMovieSceneScriptingFloatKey`  
`class UMovieSceneScriptingFloatKey : public UMovieSceneScriptingKey`  
_L23-155_
- reflection: `UCLASS(abstract, BlueprintType)`
- inherits: `UMovieSceneScriptingKey`
- desc: Exposes a Sequencer float type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L33 _public prototype_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetTime, return FFrameTime(););` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Float)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L42 _public prototype_ `virtual void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetTime);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Float)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L49 _public prototype_ `virtual float GetValue() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetValue, return 0;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Float)"))` — Gets the value for this key from the owning channel. @return	The float value this key represents.
- L56 _public prototype_ `virtual void SetValue(float InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetValue);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Float)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new float value for this key.
- L63 _public prototype_ `virtual ERichCurveInterpMode GetInterpolationMode() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetInterpolationMode, return ERichCurveInterpMode::RCIM_None;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Gets the interpolation mode for this key from the owning channel. @return	Interpolation mode this key uses to interpolate between this key and the next.
- L70 _public prototype_ `virtual void SetInterpolationMode(ERichCurveInterpMode InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetInterpolationMode);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the interpolation mode for this key, reflecting it in the owning channel. @param InNewValue	Interpolation mode this key should use to interpolate between this key and the next.
- L77 _public prototype_ `virtual ERichCurveTangentMode GetTangentMode() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetTangentMode, return ERichCurveTangentMode::RCTM_None;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Gets the tangent mode for this key from the owning channel. @return	Tangent mode that this key is using specifying which tangent values are respected when evaluating.
- L84 _public prototype_ `virtual void SetTangentMode(ERichCurveTangentMode InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetTangentMode);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the tangent mode for this key, reflecting it in the owning channel. @param InNewValue	Tangent mode that this key should use to specify which tangent values are respected when evaluating. See ERichCurveTangentMode for more details.
- L91 _public prototype_ `virtual float GetArriveTangent() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetArriveTangent, return 0;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the arriving tangent at this key @return Arrival Tangent value. Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L98 _public prototype_ `virtual void SetArriveTangent(float InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetArriveTangent);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the arriving tangent at this key. @param InNewValue	Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L105 _public prototype_ `virtual float GetLeaveTangent() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetLeaveTangent, return 0;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the leaving tangent at this key @return Leaving Tangent value. Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L112 _public prototype_ `virtual void SetLeaveTangent(float InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetLeaveTangent);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the leaving tangent at this key. @param InNewValue	Represents the geometric tangents in the form of "tan(y/x)" where y is the key's value and x is the seconds (both relative to key)
- L119 _public prototype_ `virtual ERichCurveTangentWeightMode GetTangentWeightMode() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetTangentWeightMode, return ERichCurveTangentWeightMode::RCTWM_WeightedNone;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the tangent weight mode at this key @return Tangent Weight Mode. See ERichCurveTangentWeightMode for more detail on what each mode does.
- L126 _public prototype_ `virtual void SetTangentWeightMode(ERichCurveTangentWeightMode InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetTangentWeightMode);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Interpolation Mode is RCIM_Cubic, the tangent weight mode at this key. @param InNewValue	Specifies which tangent weights should be respected when evaluating the key.
- L133 _public prototype_ `virtual float GetArriveTangentWeight() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetArriveTangentWeight, return 0;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedArrive or RCTWM_WeightedBoth, the weight of the arriving tangent on the left side. @return Tangent Weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.
- L140 _public prototype_ `virtual void SetArriveTangentWeight(float InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetArriveTangentWeight);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedArrive or RCTWM_WeightedBoth, the weight of the arriving tangent on the left side. @param InNewValue	Specifies the new arriving tangent weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.
- L147 _public prototype_ `virtual float GetLeaveTangentWeight() const PURE_VIRTUAL(UMovieSceneScriptingFloatKey::GetLeaveTangentWeight, return 0;);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedLeave or RCTWM_WeightedBoth, the weight of the leaving tangent on the right side. @return Tangent Weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.
- L154 _public prototype_ `virtual void SetLeaveTangentWeight(float InNewValue) PURE_VIRTUAL(UMovieSceneScriptingFloatKey::SetLeaveTangentWeight);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — If Tangent Weight Mode is RCTWM_WeightedLeave or RCTWM_WeightedBoth, the weight of the leaving tangent on the right side. @param InNewValue	Specifies the new leaving tangent weight. Represents the length of the hypotenuse in the form of "sqrt(x*x+y*y)" using the same definitions for x and y as tangents.

#### class `UMovieSceneScriptingActualFloatKey`  
`class UMovieSceneScriptingActualFloatKey : public UMovieSceneScriptingFloatKey, public TMovieSceneScriptingKey<FMovieSceneFloatChannel, FMovieSceneFloatValue>`  
_L158-255_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingFloatKey,TMovieSceneScriptingKey<FMovieSceneFloatChannel,FMovieSceneFloatValue>`
- L162 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override`
- L166 _public function_ `virtual void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) override`
- L170 _public function_ `virtual float GetValue() const override`
- L174 _public function_ `virtual void SetValue(float InNewValue) override`
- L180 _public function_ `virtual ERichCurveInterpMode GetInterpolationMode() const override`
- L184 _public function_ `virtual void SetInterpolationMode(ERichCurveInterpMode InNewValue) override`
- L190 _public function_ `virtual ERichCurveTangentMode GetTangentMode() const override`
- L194 _public function_ `virtual void SetTangentMode(ERichCurveTangentMode InNewValue) override`
- L200 _public function_ `virtual float GetArriveTangent() const override`
- L204 _public function_ `virtual void SetArriveTangent(float InNewValue) override`
- L211 _public function_ `virtual float GetLeaveTangent() const override`
- L215 _public function_ `virtual void SetLeaveTangent(float InNewValue) override`
- L222 _public function_ `virtual ERichCurveTangentWeightMode GetTangentWeightMode() const override`
- L226 _public function_ `virtual void SetTangentWeightMode(ERichCurveTangentWeightMode InNewValue) override`
- L233 _public function_ `virtual float GetArriveTangentWeight() const override`
- L237 _public function_ `virtual void SetArriveTangentWeight(float InNewValue) override`
- L244 _public function_ `virtual float GetLeaveTangentWeight() const override`
- L248 _public function_ `virtual void SetLeaveTangentWeight(float InNewValue) override`

#### class `UMovieSceneScriptingDoubleAsFloatKey`  
`class UMovieSceneScriptingDoubleAsFloatKey : public UMovieSceneScriptingFloatKey, public TMovieSceneScriptingKey<FMovieSceneDoubleChannel, FMovieSceneDoubleValue>`  
_L258-355_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingFloatKey,TMovieSceneScriptingKey<FMovieSceneDoubleChannel,FMovieSceneDoubleValue>`
- L262 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override`
- L266 _public function_ `virtual void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) override`
- L270 _public function_ `virtual float GetValue() const override`
- L274 _public function_ `virtual void SetValue(float InNewValue) override`
- L280 _public function_ `virtual ERichCurveInterpMode GetInterpolationMode() const override`
- L284 _public function_ `virtual void SetInterpolationMode(ERichCurveInterpMode InNewValue) override`
- L290 _public function_ `virtual ERichCurveTangentMode GetTangentMode() const override`
- L294 _public function_ `virtual void SetTangentMode(ERichCurveTangentMode InNewValue) override`
- L300 _public function_ `virtual float GetArriveTangent() const override`
- L304 _public function_ `virtual void SetArriveTangent(float InNewValue) override`
- L311 _public function_ `virtual float GetLeaveTangent() const override`
- L315 _public function_ `virtual void SetLeaveTangent(float InNewValue) override`
- L322 _public function_ `virtual ERichCurveTangentWeightMode GetTangentWeightMode() const override`
- L326 _public function_ `virtual void SetTangentWeightMode(ERichCurveTangentWeightMode InNewValue) override`
- L333 _public function_ `virtual float GetArriveTangentWeight() const override`
- L337 _public function_ `virtual void SetArriveTangentWeight(float InNewValue) override`
- L344 _public function_ `virtual float GetLeaveTangentWeight() const override`
- L348 _public function_ `virtual void SetLeaveTangentWeight(float InNewValue) override`

#### class `UMovieSceneScriptingFloatChannel`  
`class UMovieSceneScriptingFloatChannel : public UMovieSceneScriptingChannel`  
_L358-693_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L362 _private typedef_ `using FloatImpl = TMovieSceneScriptingChannel<FMovieSceneFloatChannel, UMovieSceneScriptingActualFloatKey, float>;`
- L363 _private typedef_ `using DoubleImpl = TMovieSceneScriptingChannel<FMovieSceneDoubleChannel, UMovieSceneScriptingDoubleAsFloatKey, double>;`
- L376 _public function_ `UMovieSceneScriptingFloatKey* AddKey(const FFrameNumber& InTime, float NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, EMovieSceneKeyInterpolation InInterpolation = EMovieSceneKeyInterpolation::Auto)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Float)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @param	InInterpolation	Interpolation method the key should use. @return	The key that was created with the specified values at the specified time.
- L393 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Float)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L411 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Float)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingFloatKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L430 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Float)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L446 _public function_ `int32 GetNumKeys() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Num Keys (Float)"))` — Returns number of keys in this channel.
- L468 _public function_ `TArray<float> EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Float)"))` — Gets baked keys in this channel. @return	An array of float's contained by this channel. Returns baked keys in the specified range.
- L490 _public function_ `FSequencerScriptingRange ComputeEffectiveRange() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Compute Effective Range (Float)"))` — Compute the effective range of this channel, for example, the extents of its key times @return A range that represents the greatest range of times occupied by this channel, in the sequence's frame resolution
- L506 _public function_ `ERichCurveExtrapolation GetPreInfinityExtrapolation() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — @return Gets the Pre-infinity extrapolation state. See ERichCurveExtrapolation for more detail.
- L529 _public function_ `void SetPreInfinityExtrapolation(ERichCurveExtrapolation InExtrapolation)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the Pre-infinity extrapolation state. See ERichCurveExtrapolation for more detail. @param InExtrapolation The new extrapolation mode this key should use for evaluating before this key.
- L552 _public function_ `ERichCurveExtrapolation GetPostInfinityExtrapolation() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — @return Gets the Post-infinity extrapolation state. See ERichCurveExtrapolation for more detail.
- L575 _public function_ `void SetPostInfinityExtrapolation(ERichCurveExtrapolation InExtrapolation)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys")` — Sets the Post-infinity extrapolation state. See ERichCurveExtrapolation for more detail. @param InExtrapolation The new extrapolation mode this key should use for evaluating after this key.
- L599 _public function_ `void SetDefault(float InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Float)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L617 _public function_ `float GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Float)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L635 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Float)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L651 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Float)"))` — @return Does this channel have a default value set?
- L673 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Float)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L686 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L687 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L691 _private member_ `TMovieSceneChannelHandle<FMovieSceneFloatChannel> FloatChannelHandle;`
- L692 _private member_ `TMovieSceneChannelHandle<FMovieSceneDoubleChannel> DoubleChannelHandle;`

#### Free symbols / members of external scopes

- L479 _function_ `Algo::Transform(DoubleValues, FloatValues, [](double Value) { return (float)Value; });` (scope `UMovieSceneScriptingFloatChannel::EvaluateKeys`)

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingInteger.h` (Private)


#### class `UMovieSceneScriptingIntegerKey`  
`class UMovieSceneScriptingIntegerKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneIntegerChannel, int32>`  
_L22-62_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneIntegerChannel,int32>`
- desc: Exposes a Sequencer integer type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L32 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Integer)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L41 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Integer)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L48 _public function_ `int32 GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Integer)"))` — Gets the value for this key from the owning channel. @return	The value for this key.
- L58 _public function_ `void SetValue(int32 InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Integer)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new value for this key.

#### class `UMovieSceneScriptingIntegerChannel`  
`class UMovieSceneScriptingIntegerChannel : public UMovieSceneScriptingChannel`  
_L65-214_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L69 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneIntegerChannel, UMovieSceneScriptingIntegerKey, int32>;`
- L81 _public function_ `UMovieSceneScriptingIntegerKey* AddKey(const FFrameNumber& InTime, int32 NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Integer)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L90 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Integer)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L101 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Integer)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingIntegerKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L113 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Integer)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L122 _public function_ `int32 GetNumKeys() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Num Keys (Integer)"))` — Returns number of keys in this channel.
- L133 _public function_ `TArray<int32> EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Integer)"))` — Gets baked keys in this channel. @return	An array of values contained by this channel. Returns baked keys in the specified range.
- L143 _public function_ `void SetDefault(int32 InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Integer)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L153 _public function_ `int32 GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Integer)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L163 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Integer)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L172 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Integer)"))` — @return Does this channel have a default value set?
- L181 _public function_ `void SetInterpolateLinearKeys(bool bInInterpolateLinearKeys)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Interpolate Linear Keys (Integer)"))` — Set this channel to evaluate linear keys with interpolation.
- L190 _public function_ `bool GetInterpolateLinearKeys() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Interpolate Linear Keys (Integer)"))` — Get whether this channel will evaluate linear keys with interpolation.
- L205 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Integer)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L211 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L212 _public member_ `TMovieSceneChannelHandle<FMovieSceneIntegerChannel> ChannelHandle;`
- L213 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingObjectPath.h` (Private)


#### class `UMovieSceneScriptingObjectPathKey`  
`class UMovieSceneScriptingObjectPathKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneObjectPathChannel, FMovieSceneObjectPathChannelKeyValue>`  
_L22-64_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneObjectPathChannel,FMovieSceneObjectPathChannelKeyValue>`
- desc: Exposes a Sequencer Object Path type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L32 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Object Path)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L41 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Object Path)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L48 _public function_ `UObject* GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Object Path)"))` — Gets the value for this key from the owning channel. @return	The object for this key.
- L59 _public function_ `void SetValue(UObject* InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Object Path)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new object for this key.

#### class `UMovieSceneScriptingObjectPathChannel`  
`class UMovieSceneScriptingObjectPathChannel : public UMovieSceneScriptingChannel`  
_L67-226_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L71 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneObjectPathChannel, UMovieSceneScriptingObjectPathKey, FMovieSceneObjectPathChannelKeyValue>;`
- L83 _public function_ `UMovieSceneScriptingObjectPathKey* AddKey(const FFrameNumber InTime, UObject* NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Object Path)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L93 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Object Path)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L104 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Object Path)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingObjectPathKey contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L116 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Object Path)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L126 _public function_ `void SetDefault(UObject* InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Object Path)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L153 _public function_ `UObject* GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Object Path)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L171 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Object Path)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L202 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Object Path)"))` — @return Does this channel have a default value set?
- L217 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Object Path)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L223 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L224 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L225 _public member_ `TMovieSceneChannelHandle<FMovieSceneObjectPathChannel> ChannelHandle;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingParticle.h` (Private)


#### class `UMovieSceneScriptingParticleKey`  
`class UMovieSceneScriptingParticleKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneParticleChannel, uint8>`  
_L21-62_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneParticleChannel,uint8>`
- desc: Exposes a Sequencer partcicle type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L31 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Particle)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L40 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Particle)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L47 _public function_ `EParticleKey GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Particle)"))` — Gets the value for this key from the owning channel. @return	The value for this key.
- L57 _public function_ `void SetValue(EParticleKey InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Particle)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new value for this key.

#### class `UMovieSceneScriptingParticleChannel`  
`class UMovieSceneScriptingParticleChannel : public UMovieSceneScriptingChannel`  
_L65-216_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L69 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneParticleChannel, UMovieSceneScriptingParticleKey, uint8>;`
- L81 _public function_ `UMovieSceneScriptingParticleKey* AddKey(const FFrameNumber& InTime, EParticleKey NewParticleValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Particle)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L91 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Particle)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L102 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Particle)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingParticleKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L114 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Particle)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L123 _public function_ `int32 GetNumKeys() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Num Keys (Particle)"))` — Returns number of keys in this channel.
- L134 _public function_ `TArray<EParticleKey> EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Particle)"))` — Gets baked keys in this channel. @return	An array of values contained by this channel. Returns baked keys in the specified range.
- L152 _public function_ `FSequencerScriptingRange ComputeEffectiveRange() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Compute Effective Range (Particle)"))` — Compute the effective range of this channel, for example, the extents of its key times @return A range that represents the greatest range of times occupied by this channel, in the sequence's frame resolution
- L162 _public function_ `void SetDefault(EParticleKey InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Particle)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L173 _public function_ `EParticleKey GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Particle)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L183 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Particle)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L192 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Particle)"))` — @return Does this channel have a default value set?
- L207 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Particle)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L213 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L214 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L215 _public member_ `TMovieSceneChannelHandle<FMovieSceneParticleChannel> ChannelHandle;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingString.h` (Private)


#### class `UMovieSceneScriptingStringKey`  
`class UMovieSceneScriptingStringKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneStringChannel, FString>`  
_L21-61_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneStringChannel,FString>`
- desc: Exposes a Sequencer string type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L31 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (String)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L40 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (String)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L47 _public function_ `FString GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (String)"))` — Gets the value for this key from the owning channel. @return	The value for this key.
- L57 _public function_ `void SetValue(const FString& InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (String)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new value for this key.

#### class `UMovieSceneScriptingStringChannel`  
`class UMovieSceneScriptingStringChannel : public UMovieSceneScriptingChannel`  
_L64-176_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L68 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneStringChannel, UMovieSceneScriptingStringKey, FString>;`
- L81 _public function_ `UMovieSceneScriptingStringKey* AddKey(const FFrameNumber& InTime, FString NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (String)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @param	InInterpolation	Interpolation method the key should use. @return	The key that was created with the specified values at the specified time.
- L90 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (String)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L101 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (String)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingStringKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L113 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (String)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L123 _public function_ `void SetDefault(FString InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (String)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L133 _public function_ `FString GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (String)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L143 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (String)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L152 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (String)"))` — @return Does this channel have a default value set?
- L167 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (String)"))` — Transform the OffsetFrame in time in the channel by an offset, scale and pivot @param	DeltaFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L173 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L174 _public member_ `TMovieSceneChannelHandle<FMovieSceneStringChannel> ChannelHandle;`
- L175 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Private/KeysAndChannels/MovieSceneScriptingText.h` (Private)


#### class `UMovieSceneScriptingTextKey`  
`class UMovieSceneScriptingTextKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneTextChannel, FText>`  
_L20-67_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneTextChannel,FText>`
- desc: Exposes a Sequencer text type key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L31 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Text)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L43 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Text)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L53 _public function_ `FText GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Text)"))` — Gets the value for this key from the owning channel. @return	The value for this key.
- L63 _public function_ `void SetValue(const FText& InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Text)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new value for this key.

#### class `UMovieSceneScriptingTextChannel`  
`class UMovieSceneScriptingTextChannel : public UMovieSceneScriptingChannel`  
_L70-181_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L74 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneTextChannel, UMovieSceneScriptingTextKey, FText>;`
- L86 _public function_ `UMovieSceneScriptingTextKey* AddKey(const FFrameNumber& InTime, FText NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Text)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L95 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Text)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L106 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Text)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingTextKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L118 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Text)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L128 _public function_ `void SetDefault(FText InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Text)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L138 _public function_ `FText GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Text)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L148 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Text)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L157 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Text)"))` — @return Does this channel have a default value set?
- L172 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Text)"))` — Transform the OffsetFrame in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L178 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L179 _public member_ `TMovieSceneChannelHandle<FMovieSceneTextChannel> ChannelHandle;`
- L180 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneBindingExtensions.h` (Public)


#### class `UMovieSceneBindingExtensions`  
`class UMovieSceneBindingExtensions : public UBlueprintFunctionLibrary`  
_L19-218_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto FMovieSceneBindingProxies for scripting
- L27 _public prototype_ `static bool IsValid(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Check whether the specified binding is valid
- L31 _public prototype_ `static bool EqualEqual_MovieSceneBindingProxy(FMovieSceneBindingProxy A, FMovieSceneBindingProxy B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (MovieSceneBindingProxy)", CompactNodeTitle = "==", ScriptOperator = "==", BlueprintThreadSafe), Category = "Sequencer|Sequence")` — Returns true if the values are equal (A == B)
- L35 _public prototype_ `static bool NotEqual_MovieSceneBindingProxy(FMovieSceneBindingProxy A, FMovieSceneBindingProxy B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (MovieSceneBindingProxy)", CompactNodeTitle = "!=", ScriptOperator = "!=", BlueprintThreadSafe), Category = "Sequencer|Sequence")` — Returns true if the values are not equal (A != B)
- L44 _public prototype_ `static FGuid GetId(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get this binding's ID @param InBinding     The binding to get the ID of @return The guid that uniquely represents this binding
- L53 _public prototype_ `static FText GetDisplayName(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get this binding's name @param InBinding     The binding to get the name of @return The display name of the binding
- L62 _public prototype_ `static void SetDisplayName(const FMovieSceneBindingProxy& InBinding, const FText& InDisplayName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod, DevelopmentOnly))` — Set this binding's name @param InBinding     The binding to get the name of @param InName The display name of the binding
- L71 _public prototype_ `static FString GetName(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get this binding's object non-display name @param InBinding     The binding to get the name of @return The name of the binding
- L80 _public prototype_ `static void SetName(const FMovieSceneBindingProxy& InBinding, const FString& InName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Set this binding's object non-display name @param InBinding     The binding to get the name of @param InName The name of the binding
- L89 _public prototype_ `static int32 GetSortingOrder(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Get the sorting order for this binding @param InBinding        The binding to get the sorting order from @return The sorting order of the requested binding
- L98 _public prototype_ `static void SetSortingOrder(const FMovieSceneBindingProxy& InBinding, int32 SortingOrder);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Set the sorting order for this binding @param InBinding        The binding to get the sorting order from @param SortingOrder The sorting order to set
- L107 _public prototype_ `static TArray<UMovieSceneTrack*> GetTracks(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get all the tracks stored within this binding @param InBinding     The binding to find tracks in @return An array containing all the binding's tracks
- L117 _public prototype_ `static TArray<UMovieSceneTrack*> FindTracksByType(const FMovieSceneBindingProxy& InBinding, TSubclassOf<UMovieSceneTrack> TrackType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod, DeterminesOutputType="TrackType"))` — Find all tracks within a given binding of the specified type @param InBinding     The binding to find tracks in @param TrackType     A UMovieSceneTrack class type specifying which types of track to return @return An array containing any tracks that match the type specified
- L127 _public prototype_ `static TArray<UMovieSceneTrack*> FindTracksByExactType(const FMovieSceneBindingProxy& InBinding, TSubclassOf<UMovieSceneTrack> TrackType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod, DeterminesOutputType="TrackType"))` — Find all tracks within a given binding of the specified type, not allowing sub-classed types @param InBinding     The binding to find tracks in @param TrackType     A UMovieSceneTrack class type specifying the exact types of track to return @return An array containing any tracks that are exactly the same as the type specified
- L136 _public prototype_ `static void RemoveTrack(const FMovieSceneBindingProxy& InBinding, UMovieSceneTrack* TrackToRemove);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove the specified track from this binding @param InBinding     The binding to remove the track from @param TrackToRemove The track to remove
- L144 _public prototype_ `static void Remove(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove the specified binding @param InBinding     The binding to remove the track from
- L154 _public prototype_ `static UMovieSceneTrack* AddTrack(const FMovieSceneBindingProxy& InBinding, TSubclassOf<UMovieSceneTrack> TrackType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Add a new track to the specified binding @param InBinding     The binding to add tracks to @param TrackType     A UMovieSceneTrack class type specifying the type of track to create @return The newly created track, if successful
- L163 _public prototype_ `static TArray<FMovieSceneBindingProxy> GetChildPossessables(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get all the children of this binding @param InBinding     The binding to to get children of @return An array containing all the binding's children
- L172 _public prototype_ `static UObject* GetObjectTemplate(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get this binding's object template @param InBinding     The binding to get the object template of @return The object template of the binding
- L181 _public prototype_ `static UClass* GetPossessedObjectClass(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get this binding's possessed object class @param InBinding     The binding to get the possessed object class of @return The possessed object class of the binding
- L190 _public prototype_ `static FMovieSceneBindingProxy GetParent(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the parent of this binding @param InBinding     The binding to get the parent of @return The binding's parent
- L199 _public prototype_ `static void SetParent(const FMovieSceneBindingProxy& InBinding, const FMovieSceneBindingProxy& InParentBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set the parent to this binding @param InBinding     The binding to set @param InParentBinding     The parent to set the InBinding to
- L208 _public prototype_ `static void MoveBindingContents(const FMovieSceneBindingProxy& SourceBindingId, const FMovieSceneBindingProxy& DestinationBindingId);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Move all the contents (tracks, child bindings) of the specified binding ID onto another @param SourceBindingId The identifier of the binding ID to move all tracks and children from @param DestinationBindingId The identifier of the binding ID to move the contents to
- L217 _public prototype_ `static void SetSpawnableBindingID(const FMovieSceneBindingProxy& InBinding, const FMovieSceneObjectBindingID& SpawnableBindingID);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set the spawnable id that the possessable binding should possess @param InBinding     The binding to set @param SpawnableBindingID The spawnable's binding id

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneBindingTagExtensions.h` (Public)


#### class `UMovieSceneBindingTagExtensions`  
`class UMovieSceneBindingTagExtensions : public UBlueprintFunctionLibrary`  
_L24-55_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Extension methods for reading and writing Sequencer binding tags. Binding tags are name-based labels attached to object bindings in a Sequence. They are authored interactively via RMB -> Expose on a binding in the Sequencer editor, and queried at runtime via UMovieSceneSequence::FindBindingByTag. These extensions expose the authoring operations that are otherwise only available through the editor UI.
- L32 _public prototype_ `static TArray<FName> GetAllBindingTags(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Tags", meta=(ScriptMethod))` — Get every tag name registered on the sequence's MovieScene.
- L36 _public prototype_ `static TArray<FName> GetBindingTags(const FMovieSceneBindingProxy& Binding);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Tags", meta=(ScriptMethod))` — Get every tag currently attached to this specific binding.
- L43 _public prototype_ `static void TagBinding(const FMovieSceneBindingProxy& Binding, FName TagName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Tags", meta=(ScriptMethod))` — Attach a tag to the given binding. If the tag name has not been seen before, it is registered in the MovieScene's tag list automatically.
- L47 _public prototype_ `static void UntagBinding(const FMovieSceneBindingProxy& Binding, FName TagName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Tags", meta=(ScriptMethod))` — Remove a tag from the given binding. No-op if the binding lacks the tag.
- L54 _public prototype_ `static void RemoveBindingTag(UMovieSceneSequence* Sequence, FName TagName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Tags", meta=(ScriptMethod))` — Remove a tag entirely from the sequence. Clears the tag from every binding that had it, and removes the registration.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneConditionExtensions.h` (Public)


#### class `UMovieSceneConditionExtensions`  
`class UMovieSceneConditionExtensions : public UBlueprintFunctionLibrary`  
_L17-61_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Extension methods for getting and setting conditions on sections and tracks
- L25 _public prototype_ `static UMovieSceneCondition* GetSectionCondition(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section", meta=(ScriptMethod))` — Get the condition on this section, or nullptr if none is set
- L30 _public prototype_ `static void SetSectionCondition(UMovieSceneSection* Section, TSubclassOf<UMovieSceneCondition> ConditionClass);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta=(ScriptMethod))` — Set a condition on this section by creating a new instance of the given class. Pass nullptr to clear the condition.
- L34 _public prototype_ `static void ClearSectionCondition(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta=(ScriptMethod))` — Remove the condition from this section
- L38 _public prototype_ `static UMovieSceneCondition* GetTrackCondition(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Track", meta=(ScriptMethod))` — Get the track-level condition, or nullptr if none is set
- L43 _public prototype_ `static void SetTrackCondition(UMovieSceneTrack* Track, TSubclassOf<UMovieSceneCondition> ConditionClass);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Set a track-level condition by creating a new instance of the given class. Pass nullptr to clear the condition.
- L47 _public prototype_ `static void ClearTrackCondition(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Remove the track-level condition
- L51 _public prototype_ `static UMovieSceneCondition* GetTrackRowCondition(UMovieSceneTrack* Track, int32 RowIndex);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Track", meta=(ScriptMethod))` — Get the condition on a specific track row, or nullptr if none is set
- L56 _public prototype_ `static void SetTrackRowCondition(UMovieSceneTrack* Track, int32 RowIndex, TSubclassOf<UMovieSceneCondition> ConditionClass);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Set a condition on a specific track row by creating a new instance of the given class. Pass nullptr to clear the row condition.
- L60 _public prototype_ `static void ClearTrackRowCondition(UMovieSceneTrack* Track, int32 RowIndex);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Remove the condition from a specific track row

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneEventTrackExtensions.h` (Public)


#### class `UMovieSceneEventTrackExtensions`  
`class UMovieSceneEventTrackExtensions : public UBlueprintFunctionLibrary`  
_L20-52_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneEventTrack for scripting
- L33 _public prototype_ `static UMovieSceneEventRepeaterSection* AddEventRepeaterSection(UMovieSceneEventTrack* InTrack);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Create a new event repeater section for the given track @param Track        The event track to add the new event repeater section to @return The newly created event repeater section
- L42 _public prototype_ `static UMovieSceneEventTriggerSection* AddEventTriggerSection(UMovieSceneEventTrack* InTrack);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Create a new event trigger section for the given track @param Track        The event track to add the new event trigger section to @return The newly created event trigger section
- L51 _public function_ `static UClass* GetBoundObjectPropertyClass(const FMovieSceneEvent& EventKey)` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Event", meta = (ScriptMethod))` — Return the class of the bound object property @param EventKey    The event key to get the bound object property from @return The class of the bound object property

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneFolderExtensions.h` (Public)


#### class `UMovieSceneFolderExtensions`  
`class UMovieSceneFolderExtensions : public UBlueprintFunctionLibrary`  
_L20-149_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneFolders for scripting
- L32 _public prototype_ `static FName GetFolderName(UMovieSceneFolder* Folder);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the given folder's display name @param Folder	The folder to use @return The target folder's name
- L42 _public prototype_ `static bool SetFolderName(UMovieSceneFolder* Folder, FName InFolderName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Set the name of the given folder @param Folder		The folder to set the name of @param InFolderName	The new name for the folder @return True if the setting of the folder name succeeds
- L51 _public prototype_ `static FColor GetFolderColor(UMovieSceneFolder* Folder);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Get the display color of the given folder @param Folder	The folder to get the display color of @return The display color of the given folder
- L61 _public prototype_ `static bool SetFolderColor(UMovieSceneFolder* Folder, FColor InFolderColor);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod, DevelopmentOnly))` — Set the display color of the given folder @param Folder			The folder to set the display color of @param InFolderColor		The new display color for the folder @return True if the folder's display color is set successfully
- L70 _public prototype_ `static TArray<UMovieSceneFolder*> GetChildFolders(UMovieSceneFolder* Folder);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the child folders of a given folder @param Folder	The folder to get the child folders of @return The child folders associated with the given folder
- L80 _public prototype_ `static bool AddChildFolder(UMovieSceneFolder* TargetFolder, UMovieSceneFolder* FolderToAdd);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Add a child folder to the target folder @param TargetFolder	The folder to add a child folder to @param FolderToAdd	The child folder to be added @return True if the addition is successful
- L90 _public prototype_ `static bool RemoveChildFolder(UMovieSceneFolder* TargetFolder, UMovieSceneFolder* FolderToRemove);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove a child folder from the given folder @param TargetFolder		The folder from which to remove a child folder @param FolderToRemove	The child folder to be removed @return True if the removal succeeds
- L99 _public prototype_ `static TArray<UMovieSceneTrack*> GetChildTracks(UMovieSceneFolder* Folder);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get the tracks contained by this folder @param Folder	The folder to get the tracks of @return The tracks under the given folder
- L109 _public prototype_ `static bool AddChildTrack(UMovieSceneFolder* Folder, UMovieSceneTrack* InTrack);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Add a track to this folder @param Folder			The folder to add a child track to @param InTrack		    The track to add to the folder @return True if the addition is successful
- L119 _public prototype_ `static bool RemoveChildTrack(UMovieSceneFolder* Folder, UMovieSceneTrack* InTrack);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove a track from the given folder @param Folder			The folder from which to remove a track @param InTrack		    The track to remove @return True if the removal succeeds
- L128 _public prototype_ `static TArray<FMovieSceneBindingProxy> GetChildObjectBindings(UMovieSceneFolder* Folder);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the object bindings contained by this folder @param Folder	The folder to get the bindings of @return The object bindings under the given folder
- L138 _public prototype_ `static bool AddChildObjectBinding(UMovieSceneFolder* Folder, FMovieSceneBindingProxy InObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Add a guid for an object binding to this folder @param Folder			The folder to add a child object to @param InObjectBinding	The binding to add to the folder @return True if the addition is successful
- L148 _public prototype_ `static bool RemoveChildObjectBinding(UMovieSceneFolder* Folder, const FMovieSceneBindingProxy InObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove an object binding from the given folder @param Folder			The folder from which to remove an object binding @param InObjectBinding	The object binding to remove @return True if the operation succeeds

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneMaterialTrackExtensions.h` (Public)


#### class `UMovieSceneMaterialTrackExtensions`  
`class UMovieSceneMaterialTrackExtensions : public UBlueprintFunctionLibrary`  
_L21-60_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneMaterialTrack for scripting
- L34 _public prototype_ `static void SetMaterialIndex(UMovieSceneComponentMaterialTrack* Track, const int32 MaterialIndex);` — `UE_DEPRECATED(5.4, "Use SetMaterialInfo instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "Use SetMaterialInfo instead"))` — Set material index of the component that is animated by the material track. @param Track The track to use @param MaterialIndex The desired material index to animate. Values of < 0 or >= NumMaterials will be silently ignored and evaluation will fail.
- L43 _public prototype_ `static int32 GetMaterialIndex(UMovieSceneComponentMaterialTrack* Track);` — `UE_DEPRECATED(5.4, "Use SetMaterialInfo instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage = "Use SetMaterialInfo instead"))` — Get material index of the component that is animated by the material track. @param Track The track to use @return The material index.
- L51 _public prototype_ `static void SetMaterialInfo(UMovieSceneComponentMaterialTrack* Track, const FComponentMaterialInfo& MaterialInfo);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set material info of the component that is animated by the material track. @param Track The track to use @param MaterialInfo The desired material info to animate.
- L59 _public prototype_ `static FComponentMaterialInfo GetMaterialInfo(UMovieSceneComponentMaterialTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage = "Use SetMaterialInfo instead"))` — Get material info of the component that is animated by the material track. @param Track The track to use @return The material info.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieScenePrimitiveMaterialTrackExtensions.h` (Public)


#### class `UMovieScenePrimitiveMaterialTrackExtensions`  
`class UMovieScenePrimitiveMaterialTrackExtensions : public UBlueprintFunctionLibrary`  
_L17-56_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieScenePrimitiveMaterialTrack for scripting
- L30 _public prototype_ `static void SetMaterialIndex(UMovieScenePrimitiveMaterialTrack* Track, const int32 MaterialIndex);` — `UE_DEPRECATED(5.4, "Use SetMaterialInfo instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "Use SetMaterialInfo instead"))` — Set material index of the element that is animated by the primitive material track. @param Track The track to use @param MaterialIndex The desired material index to animate. Values of < 0 or >= NumMaterials will be silently ignored and evaluation will fail.
- L39 _public prototype_ `static int32 GetMaterialIndex(UMovieScenePrimitiveMaterialTrack* Track);` — `UE_DEPRECATED(5.4, "Use SetMaterialInfo instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage = "Use SetMaterialInfo instead"))` — Get material index of the element that is animated by the primitive material track. @param Track The track to use @return The material index.
- L47 _public prototype_ `static void SetMaterialInfo(UMovieScenePrimitiveMaterialTrack* Track, const FComponentMaterialInfo& MaterialInfo);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set material info of the component that is animated by the material track. @param Track The track to use @param MaterialInfo The desired material info to animate.
- L55 _public prototype_ `static FComponentMaterialInfo GetMaterialInfo(UMovieScenePrimitiveMaterialTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage = "Use SetMaterialInfo instead"))` — Get material info of the component that is animated by the material track. @param Track The track to use @return The material info.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieScenePropertyTrackExtensions.h` (Public)


#### class `UMovieScenePropertyTrackExtensions`  
`class UMovieScenePropertyTrackExtensions : public UBlueprintFunctionLibrary`  
_L19-98_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieScenePropertyTrack for scripting
- L33 _public prototype_ `static void SetPropertyNameAndPath(UMovieScenePropertyTrack* Track, const FName& InPropertyName, const FString& InPropertyPath);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set this track's property name and path @param Track        The track to use @param InPropertyName The property name @param InPropertyPath The property path
- L42 _public prototype_ `static FName GetPropertyName(UMovieScenePropertyTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Get this track's property name @param Track        The track to use @return This track's property name
- L51 _public prototype_ `static FString GetPropertyPath(UMovieScenePropertyTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Get this track's property path @param Track        The track to use @return This track's property path
- L60 _public prototype_ `static FName GetUniqueTrackName(UMovieScenePropertyTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Get this track's unique name @param Track        The track to use @return This track's unique name
- L70 _public prototype_ `static void SetObjectPropertyClass(UMovieSceneObjectPropertyTrack* Track, UClass* PropertyClass, bool bInClassProperty = false);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set this object property track's property class @param Track        The track to use @param PropertyClass The property class to set @param bInClassProperty Whether the property class is a class property or not, which determines whether a class property chooser should be used instead of an object property chooser
- L79 _public prototype_ `static UClass* GetObjectPropertyClass(UMovieSceneObjectPropertyTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Get this object property track's property class @param Track        The track to use @return The property class for this object property track
- L88 _public prototype_ `static void SetByteTrackEnum(UMovieSceneByteTrack* Track, UEnum* InEnum);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set this byte track's enum @param Track        The track to use @param InEnum The enum to set
- L97 _public prototype_ `static UEnum* GetByteTrackEnum(UMovieSceneByteTrack* Track);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Track", meta = (ScriptMethod))` — Get this byte track's enum @param Track        The track to use @return The enum for this byte track

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneSectionEasingExtensions.h` (Public)


#### class `UMovieSceneSectionEasingExtensions`  
`class UMovieSceneSectionEasingExtensions : public UBlueprintFunctionLibrary`  
_L15-36_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing easing methods that should be hoisted onto UMovieSceneSections for scripting
- L23 _public prototype_ `static int32 GetEaseInDuration(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section", meta=(ScriptMethod))` — Get the effective ease-in duration in frames, considering manual override
- L27 _public prototype_ `static int32 GetEaseOutDuration(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section", meta=(ScriptMethod))` — Get the effective ease-out duration in frames, considering manual override
- L31 _public prototype_ `static void SetEaseInDuration(UMovieSceneSection* Section, int32 InDuration);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta=(ScriptMethod))` — Set manual ease-in duration in frames, enabling the manual override
- L35 _public prototype_ `static void SetEaseOutDuration(UMovieSceneSection* Section, int32 InDuration);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta=(ScriptMethod))` — Set manual ease-out duration in frames, enabling the manual override

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneSectionExtensions.h` (Public)


#### class `UMovieSceneSectionExtensions`  
`class UMovieSceneSectionExtensions : public UBlueprintFunctionLibrary`  
_L24-279_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneSections for scripting
- L36 _public prototype_ `static bool HasStartFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Has start frame @param Section        The section being queried @return Whether this section has a valid start frame (else infinite)
- L45 _public prototype_ `static int32 GetStartFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get start frame. Will throw an exception if section has no start frame, use HasStartFrame to check first. @param Section        The section within which to get the start frame @return Start frame of this section
- L54 _public prototype_ `static float GetStartFrameSeconds(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get start time in seconds. Will throw an exception if section has no start frame, use HasStartFrame to check first. @param Section        The section within which to get the start time @return Start time of this section
- L63 _public prototype_ `static bool HasEndFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Has end frame @param Section        The section being queried @return Whether this section has a valid end frame (else infinite)
- L72 _public prototype_ `static int32 GetEndFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get end frame. Will throw an exception if section has no end frame, use HasEndFrame to check first. @param Section        The section within which to get the end frame @return End frame of this section
- L81 _public prototype_ `static float GetEndFrameSeconds(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get end time in seconds. Will throw an exception if section has no end frame, use HasEndFrame to check first. @param Section        The section within which to get the end time @return End time of this section
- L90 _public prototype_ `static bool GetAutoSizeHasStartFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Checks to see if this section has an AutoSize implementation, and if so, if that implementation has a start frame. @param Section        The section being queried @return Whether this section has a valid autosize range, and a valid start frame
- L99 _public prototype_ `static int32 GetAutoSizeStartFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get start frame of the AutoSize. Will throw an exception if section has no start frame, use GetAutoSizeHasStartFrame to check first. @param Section        The section being queried @return The start frame of the AutoSize data.
- L108 _public prototype_ `static float GetAutoSizeStartFrameSeconds(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get start time of the AutoSize in seconds. Will throw an exception if section has no start frame, use GetAutoSizeHasStartFrame to check first. @param Section        The section being queried @return The start frame of the AutoSize data in seconds.
- L117 _public prototype_ `static bool GetAutoSizeHasEndFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Checks to see if this section has an AutoSize implementation, and if so, if that implementation has a end frame. @param Section        The section being queried @return Whether this section has a valid autosize range, and a valid end frame
- L126 _public prototype_ `static int32 GetAutoSizeEndFrame(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get end frame of the AutoSize. Will throw an exception if section has no end frame, use GetAutoSizeHasEndFrame to check first. @param Section        The section being queried @return The end frame of the AutoSize data.
- L135 _public prototype_ `static float GetAutoSizeEndFrameSeconds(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get end time of the AutoSize seconds. Will throw an exception if section has no end frame, use GetAutoSizeHasEndFrame to check first. @param Section        The section being queried @return The end frame of the AutoSize data in seconds.
- L145 _public prototype_ `static void SetRange(UMovieSceneSection* Section, int32 StartFrame, int32 EndFrame);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set range @param Section        The section within which to set the range @param StartFrame The desired start frame for this section @param EndFrame The desired end frame for this section
- L155 _public prototype_ `static void SetRangeSeconds(UMovieSceneSection* Section, float StartTime, float EndTime);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set range in seconds @param Section        The section within which to set the range @param StartTime The desired start frame for this section @param EndTime The desired end frame for this section
- L164 _public prototype_ `static void SetStartFrame(UMovieSceneSection* Section, int32 StartFrame);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set start frame @param Section        The section within which to set the start frame @param StartFrame The desired start frame for this section
- L173 _public prototype_ `static void SetStartFrameSeconds(UMovieSceneSection* Section, float StartTime);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set start time in seconds @param Section        The section within which to set the start time @param StartTime The desired start time for this section
- L182 _public prototype_ `static void SetStartFrameBounded(UMovieSceneSection* Section, bool bIsBounded);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set start frame bounded @param Section        The section to set whether the start frame is bounded or not @param IsBounded The desired bounded state of the start frame
- L191 _public prototype_ `static void SetEndFrame(UMovieSceneSection* Section, int32 EndFrame);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set end frame @param Section        The section within which to set the end frame @param EndFrame The desired start frame for this section
- L200 _public prototype_ `static void SetEndFrameSeconds(UMovieSceneSection* Section, float EndTime);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set end time in seconds @param Section        The section within which to set the end time @param EndTime The desired end time for this section
- L209 _public prototype_ `static void SetEndFrameBounded(UMovieSceneSection* Section, bool bIsBounded);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Set end frame bounded @param Section        The section to set whether the end frame is bounded or not @param IsBounded The desired bounded state of the end frame
- L220 _public prototype_ `static TArray<UMovieSceneScriptingChannel*> GetAllChannels(UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta=(ScriptMethod, DevelopmentOnly))` — Find all channels that belong to the specified UMovieSceneSection. Some sections have many channels (such as Transforms containing 9 double channels to represent Translation/Rotation/Scale), and a section may have mixed channel types. @param Section       The section to use. @return An array containing any key channels that match the type specified
- L231 _public prototype_ `static TArray<UMovieSceneScriptingChannel*> GetChannelsByType(UMovieSceneSection* Section, TSubclassOf<UMovieSceneScriptingChannel> ChannelType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod, DeterminesOutputType="TrackType", DevelopmentOnly))` — Find all channels that belong to the specified UMovieSceneSection that match the specific type. This will filter out any children who do not inherit from the specified type for you. @param Section        The section to use. @param ChannelType	The class type to look for. @return An array containing any key channels that match the type specified
- L243 _public prototype_ `static UMovieSceneScriptingChannel* GetChannel(UMovieSceneSection* Section, const FName& ChannelName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod, DeterminesOutputType = "TrackType", DevelopmentOnly))` — Get channel from specified section and channel name @param Section        The section to use. @param ChannelName	The name of the channel. @return The channel if it exists
- L255 _public prototype_ `static int32 GetParentSequenceFrame(UMovieSceneSubSection* Section, int32 InFrame, UMovieSceneSequence* ParentSequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section", meta = (ScriptMethod))` — Get the frame in the space of its parent sequence @param Section        The section that the InFrame is local to @param InFrame The desired local frame @param ParentSequence The parent sequence to traverse from @return The frame at the parent sequence
- L261 _public prototype_ `static FMovieSceneChannel* GetMovieSceneChannel(UMovieSceneSection* InSection, const FName& InName);` — Utility function to get channel from a section and a name
- L268 _public prototype_ `static FGuid SetGetCustomChannelsFunction(TFunction<bool(UMovieSceneSection* Section, TSubclassOf<UMovieSceneScriptingChannel> ChannelType, TArray<UMovieSceneScriptingChannel*>& OutChannels)> CustommFunc);` — Function to add a channel type for a section @param CustommFunc function to get called when asking for custom channels @return the Guid used to remove it later
- L274 _public prototype_ `static void RemoveGetCustomChannelsFunction(const FGuid& InGuid);` — Function to remove custom channels function @param InGuid guid to remove that was returned with SetGetCustomChannelsFunction
- L278 _private member_ `static TMap<FGuid,TFunction<bool(UMovieSceneSection* Section, TSubclassOf<UMovieSceneScriptingChannel> ChannelType, TArray<UMovieSceneScriptingChannel*>& OutChannels)>> CustomChannelsCallbacks;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`
- L287 _function_ `template<typename ChannelType, typename ScriptingChannelType> void SetScriptingChannelHandle(ScriptingChannelType* ScriptingChannel, FMovieSceneChannelProxy& ChannelProxy, int32 ChannelIndex)`
- L293 _function_ `template<typename ChannelType, typename ScriptingChannelType> void GetScriptingChannelsForChannel(FMovieSceneChannelProxy& ChannelProxy, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, TArray<UMovieSceneScriptingChannel*>& OutChannels)`
- L320 _function_ `template<typename ChannelType, typename ScriptingChannelType> UMovieSceneScriptingChannel* GetScriptingChannelForChannel(const FMovieSceneChannel* MovieSceneChannel, FMovieSceneChannelProxy& ChannelProxy, const FMovieSceneChannelHandle& ChanneHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, const FName& ChannelName)`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneSequenceExtensions.h` (Public)


#### class `UMovieSceneSequenceExtensions`  
`class UMovieSceneSequenceExtensions : public UBlueprintFunctionLibrary`  
_L29-665_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneSequences for scripting purposes
- L40 _public prototype_ `static UMovieScene* GetMovieScene(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Get this sequence's movie scene data @param Sequence        The sequence to use @return This sequence's movie scene data object
- L49 _public prototype_ `static TArray<UMovieSceneTrack*> GetTracks(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Get all tracks @param Sequence        The sequence to use @return An array containing all tracks in this sequence
- L59 _public prototype_ `static TArray<UMovieSceneTrack*> FindTracksByType(UMovieSceneSequence* Sequence, TSubclassOf<UMovieSceneTrack> TrackType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeterminesOutputType = "TrackType"))` — Find all tracks of the specified type @param Sequence        The sequence to use @param TrackType     A UMovieSceneTrack class type specifying which types of track to return @return An array containing any tracks that match the type specified
- L69 _public prototype_ `static TArray<UMovieSceneTrack*> FindTracksByExactType(UMovieSceneSequence* Sequence, TSubclassOf<UMovieSceneTrack> TrackType);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod, DeterminesOutputType="TrackType"))` — Find all tracks of the specified type, not allowing sub-classed types @param Sequence        The sequence to use @param TrackType     A UMovieSceneTrack class type specifying the exact types of track to return @return An array containing any tracks that are exactly the same as the type specified
- L79 _public prototype_ `static UMovieSceneTrack* AddTrack(UMovieSceneSequence* Sequence, TSubclassOf<UMovieSceneTrack> TrackType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeterminesOutputType = "TrackType"))` — Add a new track of the specified type @param Sequence        The sequence to use @param TrackType     A UMovieSceneTrack class type to create @return The newly created track, if successful
- L89 _public prototype_ `static bool RemoveTrack(UMovieSceneSequence* Sequence, UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Removes a track @param Sequence        The sequence to use @param Track           The track to remove @return Whether the track was successfully removed
- L98 _public prototype_ `static FFrameRate GetDisplayRate(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Gets this sequence's display rate @param Sequence        The sequence to use @return The display rate that this sequence is displayed as
- L107 _public prototype_ `static void SetDisplayRate(UMovieSceneSequence* Sequence, FFrameRate DisplayRate);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Sets this sequence's display rate @param Sequence        The sequence to use @param DisplayRate The display rate that this sequence is displayed as
- L116 _public prototype_ `static FFrameRate GetTickResolution(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Gets this sequence's tick resolution @param Sequence        The sequence to use @return The tick resolution of the sequence, defining the smallest unit of time representable on this sequence
- L125 _public prototype_ `static void SetTickResolution(UMovieSceneSequence* Sequence, FFrameRate TickResolution);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Sets this sequence's tick resolution and migrates frame times @param Sequence        The sequence to use @param TickResolution The tick resolution of the sequence, defining the smallest unit of time representable on this sequence
- L134 _public prototype_ `static void SetTickResolutionDirectly(UMovieSceneSequence* Sequence, FFrameRate TickResolution);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Sets this sequence's tick resolution directly without migrating frame times @param Sequence        The sequence to use @param TickResolution The tick resolution of the sequence, defining the smallest unit of time representable on this sequence
- L145 _public prototype_ `static FSequencerScriptingRange MakeRange(UMovieSceneSequence* Sequence, int32 StartFrame, int32 Duration);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Make a new range for this sequence in its display rate @param Sequence        The sequence within which to find the binding @param StartFrame      The frame at which to start the range @param Duration        The length of the range @return Specified sequencer range
- L156 _public prototype_ `static FSequencerScriptingRange MakeRangeSeconds(UMovieSceneSequence* Sequence, float StartTime, float Duration);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Make a new range for this sequence in seconds @param Sequence        The sequence within which to find the binding @param StartTime       The time in seconds at which to start the range @param Duration        The length of the range in seconds @return Specified sequencer range
- L165 _public prototype_ `static FSequencerScriptingRange GetPlaybackRange(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get playback range of this sequence in display rate resolution @param Sequence        The sequence within which to get the playback range @return Playback range of this sequence
- L174 _public prototype_ `static int32 GetPlaybackStart(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get playback start of this sequence in display rate resolution @param Sequence        The sequence within which to get the playback start @return Playback start of this sequence
- L183 _public prototype_ `static float GetPlaybackStartSeconds(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get playback start of this sequence in seconds @param Sequence        The sequence within which to get the playback start @return Playback start of this sequence
- L192 _public prototype_ `static int32 GetPlaybackEnd(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get playback end of this sequence in display rate resolution @param Sequence        The sequence within which to get the playback end @return Playback end of this sequence
- L201 _public prototype_ `static float GetPlaybackEndSeconds(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get playback end of this sequence in seconds @param Sequence        The sequence within which to get the playback end @return Playback end of this sequence
- L210 _public prototype_ `static void SetPlaybackStart(UMovieSceneSequence* Sequence, int32 StartFrame);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set playback start of this sequence @param Sequence        The sequence within which to set the playback start @param StartFrame      The desired start frame for this sequence
- L219 _public prototype_ `static void SetPlaybackStartSeconds(UMovieSceneSequence* Sequence, float StartTime);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set playback start of this sequence in seconds @param Sequence        The sequence within which to set the playback start @param StartTime       The desired start time in seconds for this sequence
- L228 _public prototype_ `static void SetPlaybackEnd(UMovieSceneSequence* Sequence, int32 EndFrame);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set playback end of this sequence @param Sequence        The sequence within which to set the playback end @param EndFrame        The desired end frame for this sequence
- L237 _public prototype_ `static void SetPlaybackEndSeconds(UMovieSceneSequence* Sequence, float EndTime);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set playback end of this sequence in seconds @param Sequence        The sequence within which to set the playback end @param EndTime         The desired end time in seconds for this sequence
- L246 _public prototype_ `static void SetViewRangeStart(UMovieSceneSequence* InSequence, double StartTimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Set the sequence view range start in seconds @param Sequence The sequence within which to set the view range start @param StartTimeInSeconds The desired view range start time in seconds for this sequence
- L255 _public prototype_ `static double GetViewRangeStart(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Get the sequence view range start in seconds @param Sequence The sequence within which to get the view range start @return The view range start time in seconds for this sequence
- L264 _public prototype_ `static void SetViewRangeEnd(UMovieSceneSequence* InSequence, double EndTimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Set the sequence view range end in seconds @param Sequence The sequence within which to set the view range end @param StartTimeInSeconds The desired view range end time in seconds for this sequence
- L273 _public prototype_ `static double GetViewRangeEnd(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Get the sequence view range end in seconds @param Sequence The sequence within which to get the view range end @return The view range end time in seconds for this sequence
- L282 _public prototype_ `static void SetWorkRangeStart(UMovieSceneSequence* InSequence, double StartTimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Set the sequence work range start in seconds @param Sequence The sequence within which to set the work range start @param StartTimeInSeconds The desired work range start time in seconds for this sequence
- L291 _public prototype_ `static double GetWorkRangeStart(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Get the sequence work range start in seconds @param Sequence The sequence within which to get the work range start @return The work range start time in seconds for this sequence
- L300 _public prototype_ `static void SetWorkRangeEnd(UMovieSceneSequence* InSequence, double EndTimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Set the sequence work range end in seconds @param Sequence The sequence within which to set the work range end @param StartTimeInSeconds The desired work range end time in seconds for this sequence
- L309 _public prototype_ `static double GetWorkRangeEnd(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod, DevelopmentOnly))` — Get the sequence work range end in seconds @param Sequence The sequence within which to get the work range end @return The work range end time in seconds for this sequence
- L318 _public prototype_ `static void SetEvaluationType(UMovieSceneSequence* InSequence, EMovieSceneEvaluationType InEvaluationType);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set the evaluation type for this sequence @param Sequence The sequence within which to set the evaluation type @param InEvaluationType The evaluation type to set for this sequence
- L327 _public prototype_ `static EMovieSceneEvaluationType GetEvaluationType(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get the evaluation type for this sequence @param Sequence The sequence within which to get the evaluation type @return The evaluation type for this sequence
- L336 _public prototype_ `static void SetClockSource(UMovieSceneSequence* InSequence, EUpdateClockSource InClockSource);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set the clock source for this sequence @param Sequence The sequence within which to set the clock source @param InClockSource The clock source to set for this sequence
- L345 _public prototype_ `static EUpdateClockSource GetClockSource(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get the clock source for this sequence @param Sequence The sequence within which to get the clock source @return The clock source for this sequence
- L354 _public prototype_ `static UMovieSceneClock* GetCustomClock(UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get the custom clock for this sequence @param Sequence The Sequence within which to get the custom clock @return The MovieSceneClock for this sequence
- L364 _public prototype_ `static FMovieSceneBindingProxy FindBindingByName(UMovieSceneSequence* Sequence, FString Name);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Attempt to locate a binding in this sequence by its name @param Sequence        The sequence within which to find the binding @param Name            The display name of the binding to look up @return A unique identifier for the binding, or invalid
- L374 _public prototype_ `static FMovieSceneBindingProxy FindBindingById(UMovieSceneSequence* Sequence, FGuid BindingId);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Attempt to locate a binding in this sequence by its Id @param Sequence        The sequence within which to find the binding @param BindingId       The binding Id to look up @return A unique identifier for the binding, or invalid
- L383 _public prototype_ `static TArray<FMovieSceneBindingProxy> GetBindings(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Get all the bindings in this sequence @param Sequence        The sequence to get bindings for @return An array of unique identifiers for all the bindings in this sequence
- L392 _public prototype_ `static TArray<FMovieSceneBindingProxy> GetSpawnables(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Get all the spawnables in this sequence. For Level Sequences, this includes bindings with binding type UMovieSceneSpawnableActorBinding. @param Sequence        The sequence to get spawnables for @return Spawnables in this sequence
- L401 _public prototype_ `static TArray<FMovieSceneBindingProxy> GetPossessables(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Get all the possessables in this sequence. It is understood for the purpose of this function that this means the bindings are not custom. @param Sequence        The sequence to get possessables for @return Possessables in this sequence
- L411 _public prototype_ `static FMovieSceneBindingProxy AddPossessable(UMovieSceneSequence* Sequence, UObject* ObjectToPossess);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Add a new binding to this sequence that will possess the specified object @param Sequence        The sequence to add a possessable to @param ObjectToPossess The object that this sequence should possess when evaluating @return A unique identifier for the new binding
- L423 _public prototype_ `static FMovieSceneBindingProxy AddSpawnableFromInstance(UMovieSceneSequence* Sequence, UObject* ObjectToSpawn);` — `UE_DEPRECATED(5.5, "AddSpawnableFromInstance is deprecated. Please use AddSpawnableFromInstance in the Level Sequence Editor Subsystem")` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage = "AddSpawnableFromInstance is deprecated. Please use AddSpawnableFromInstance in the Level Sequence Editor Subsystem"))` — Add a new binding to this sequence that will spawn the specified object. For level sequences this will make a custom binding of type UMovieSceneSpawnableActorBinding. @param Sequence        The sequence to add to @param ObjectToSpawn   An object instance to use as a template for spawning @return A unique identifier for the new binding
- L435 _public prototype_ `static FMovieSceneBindingProxy AddSpawnableFromClass(UMovieSceneSequence* Sequence, UClass* ClassToSpawn);` — `UE_DEPRECATED(5.5, "AddSpawnableFromClass is deprecated. Please use AddSpawnableFromClass in the Level Sequence Editor Subsystem")` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage = "AddSpawnableFromClass is deprecated. Please use AddSpawnableFromClass in the Level Sequence Editor Subsystem"))` — Add a new binding to this sequence that will spawn the specified object For level sequences this will make a custom binding of type UMovieSceneSpawnableActorBinding. @param Sequence        The sequence to add to @param ClassToSpawn    A class or blueprint type to spawn for this binding @return A unique identifier for the new binding
- L446 _public prototype_ `static TArray<UObject*> LocateBoundObjects(UMovieSceneSequence* Sequence, const FMovieSceneBindingProxy& InBinding, UObject* Context);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Locate all the objects that correspond to the specified object ID, using the specified context @param Sequence   The sequence to locate bound objects for @param InBinding  The object binding @param Context    Optional context to use to find the required object @return An array of all bound objects
- L457 _public prototype_ `static FMovieSceneObjectBindingID GetBindingID(UMovieSceneSequence* Sequence, const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get the binding ID for a binding within a sequence. @note: The resulting binding is only valid when applied to properties within the same sequence as this binding. Use GetPortableBindingID for bindings which live in different sub-sequences. @param Binding The binding proxy to generate the binding id from @return The binding's id
- L471 _public prototype_ `static FMovieSceneObjectBindingID GetPortableBindingID(UMovieSceneSequence* RootSequence, UMovieSceneSequence* DestinationSequence, const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Get a portable binding ID for a binding that resides in a different sequence to the one where this binding will be resolved. @note: This function must be used over GetBindingID when the target binding resides in different shots or sub-sequences. @note: Only unique instances of sequences within a root sequences are supported @param RootSequence The root sequence that contains both the destination sequence (that will resolve the binding ID) and the target sequence that contains the actual binding @param DestinationSequence The sequence that will own or resolve the resulting binding ID. For example, if the binding ID will be applied to a camera cut section pass the sequence that contains the camera cut track to this parameter. @param Binding The target binding to create the ID from @return The binding's id
- L481 _public prototype_ `static FMovieSceneBindingProxy ResolveBindingID(UMovieSceneSequence* RootSequence, FMovieSceneObjectBindingID InObjectBindingID);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Make a binding for the given binding ID @param RootSequence  The root sequence that contains the sequence @param ObjectBindingID The object binding id that has the guid and the sequence id @return The new binding proxy
- L491 _public prototype_ `static TArray<UMovieSceneFolder*> GetRootFoldersInSequence(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Get the root folders in the provided sequence @param Sequence	The sequence to retrieve folders from @return The folders contained within the given sequence
- L501 _public prototype_ `static UMovieSceneFolder* AddRootFolderToSequence(UMovieSceneSequence* Sequence, FString NewFolderName);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Add a root folder to the given sequence @param Sequence			The sequence to add a folder to @param NewFolderName		The name to give the added folder @return The newly created folder
- L510 _public prototype_ `static void RemoveRootFolderFromSequence(UMovieSceneSequence* Sequence, UMovieSceneFolder* Folder);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Sequence", meta=(ScriptMethod))` — Remove a root folder from the given sequence. Will throw an exception if the specified folder is not valid or not a root folder. @param Sequence			The sequence That the folder belongs to @param Folder			The folder to remove
- L522 _public prototype_ `static TArray<UMovieSceneTrack*> FilterTracks(TArrayView<UMovieSceneTrack* const> InTracks, UClass* DesiredClass, bool bExactMatch);` — Filter the specified array of tracks by class, optionally only matching exact classes @param InTracks       The array of tracks to filter @param DesiredClass   The class to match against @param bExactMatch    Whether to match sub classes or not @return A filtered array of tracks
- L532 _public prototype_ `static TArray<FMovieSceneMarkedFrame> GetMarkedFramesFromSequence(UMovieSceneSequence* Sequence, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DisplayName = "Get Marked Frames"))` — Get the marked frames for this sequence @return Return the user marked frames
- L536 _public function_ `static TArray<FMovieSceneMarkedFrame> GetMarkedFrames(UMovieSceneSequence* Sequence)` — `UE_DEPRECATED(5.4, "GetMarkedFrames is deprecated. Please use GetMarkedFrames that takes a time unit and defaults to display rate instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "GetMarkedFrames is deprecated. Please use GetMarkedFrames that takes a time unit instead"))`
- L546 _public prototype_ `static int32 AddMarkedFrameToSequence(UMovieSceneSequence* Sequence, const FMovieSceneMarkedFrame& InMarkedFrame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DisplayName = "Add Marked Frame"))` — Add a given user marked frame. A unique label will be generated if the marked frame label is empty @InMarkedFrame The given user marked frame to add @return The index to the newly added marked frame
- L550 _public function_ `static int32 AddMarkedFrame(UMovieSceneSequence* Sequence, const FMovieSceneMarkedFrame& InMarkedFrame)` — `UE_DEPRECATED(5.4, "AddMarkedFrame is deprecated. Please use AddMarkedFrame that takes a time unit and defaults to display rate instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "AddMarkedFrame is deprecated. Please use AddMarkedFrame that takes a time unit instead"))`
- L559 _public prototype_ `static void SetMarkedFrameInSequence(UMovieSceneSequence* Sequence, int32 InMarkIndex, FFrameNumber InFrameNumber, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DisplayName = "Set Marked Frame"))` — Sets the frame number for the given marked frame index. Does not maintain sort. Call SortMarkedFrames @InMarkIndex The given user marked frame index to edit @InFrameNumber The frame number to set
- L563 _public function_ `static void SetMarkedFrame(UMovieSceneSequence* Sequence, int32 InMarkIndex, FFrameNumber InFrameNumber)` — `UE_DEPRECATED(5.4, "SetMarkedFrame is deprecated. Please use SetMarkedFrame that takes a time unit and defaults to display rate instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "SetMarkedFrame is deprecated. Please use SetMarkedFrame that takes a time unit instead"))`
- L571 _public prototype_ `static void DeleteMarkedFrame(UMovieSceneSequence* Sequence, int32 DeleteIndex);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Delete the user marked frame by index. @DeleteIndex The index to the user marked frame to delete
- L577 _public prototype_ `static void DeleteMarkedFrames(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Delete all user marked frames
- L583 _public prototype_ `static void SortMarkedFrames(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Sort the marked frames in chronological order
- L591 _public prototype_ `static int32 FindMarkedFrameByLabel(UMovieSceneSequence* Sequence, const FString& InLabel);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Find the user marked frame by label @InLabel The label to the user marked frame to find
- L599 _public prototype_ `static int32 FindMarkedFrameByFrameNumberInSequence(UMovieSceneSequence* Sequence, FFrameNumber InFrameNumber, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DisplayName = "Find Marked Frame By Frame Number"))` — Find the user marked frame by frame number @InFrameNumber The frame number of the user marked frame to find
- L603 _public function_ `static int32 FindMarkedFrameByFrameNumber(UMovieSceneSequence* Sequence, FFrameNumber InFrameNumber)` — `UE_DEPRECATED(5.4, "FindMarkedFrameByFrameNumber is deprecated. Please use FindMarkedFrameByFrameNumber that takes a time unit and defaults to display rate instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "FindMarkedFrameByFrameNumber is deprecated. Please use FindMarkedFrameByFrameNumber that takes a time unit instead"))`
- L612 _public prototype_ `static int32 FindNextMarkedFrameInSequence(UMovieSceneSequence* Sequence, FFrameNumber InFrameNumber, bool bForward, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DisplayName = "Find Next Marked Frame"))` — Find the next/previous user marked frame from the given frame number @InFrameNumber The frame number to find the next/previous user marked frame from @bForward Find forward from the given frame number.
- L616 _public function_ `static int32 FindNextMarkedFrame(UMovieSceneSequence* Sequence, FFrameNumber InFrameNumber, bool bForward)` — `UE_DEPRECATED(5.4, "FindNextMarkedFrame is deprecated. Please use FindNextMarkedFrame that takes a time unit instead")` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod, DeprecatedFunction, DeprecationMessage = "FindNextMarkedFrame is deprecated. Please use FindNextMarkedFrame that takes a time unit and defaults to display rate instead"))`
- L624 _public prototype_ `static void SetReadOnly(UMovieSceneSequence* Sequence, bool bInReadOnly);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set read only @bInReadOnly Whether the movie scene should be read only or not
- L632 _public prototype_ `static bool IsReadOnly(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Is read only @return Whether the movie scene is read only or not
- L640 _public prototype_ `static void SetPlaybackRangeLocked(UMovieSceneSequence* Sequence, bool bInLocked);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set playback range locked @bInLocked Whether the movie scene playback range should be locked
- L648 _public prototype_ `static bool IsPlaybackRangeLocked(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Is playback ranged locked @return Whether the movie scene playback range is locked
- L656 _public prototype_ `static void SetMarkedFramesLocked(UMovieSceneSequence* Sequence, bool bInLocked);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Set marked frames locked @bInLocked Whether the movie scene marked frames should be locked
- L664 _public prototype_ `static bool AreMarkedFramesLocked(UMovieSceneSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta = (ScriptMethod))` — Are marked frames locked @return Whether the movie scene marked frames are locked

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneTimeWarpExtensions.h` (Public)


#### class `UMovieSceneTimeWarpExtensions`  
`class UMovieSceneTimeWarpExtensions : public UBlueprintFunctionLibrary`  
_L16-53_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that relate to time-warp within Sequencer
- L26 _public prototype_ `static double Conv_TimeWarpVariantToPlayRate(const FMovieSceneTimeWarpVariant& TimeWarp);` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "To PlayRate", BlueprintAutocast), Category="Sequencer|TimeWarp")` — Converts a timewarp variant struct to a constant play rate
- L32 _public prototype_ `static FMovieSceneTimeWarpVariant Conv_PlayRateToTimeWarpVariant(double ConstantPlayRate);` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "To TimeWarp", BlueprintAutocast), Category="Sequencer|TimeWarp")` — Converts a constant playrate to a timewarp variant
- L38 _public prototype_ `static double ToFixedPlayRate(const FMovieSceneTimeWarpVariant& TimeWarp);` — `UFUNCTION(BlueprintPure, meta=(ScriptMethod), Category="Sequencer|TimeWarp")` — Retrieve this timewarp's constant play rate. Will throw an error if the timewarp is not a constant play rate.
- L44 _public prototype_ `static void SetFixedPlayRate(UPARAM(ref) FMovieSceneTimeWarpVariant& TimeWarp, double FixedPlayRate);` — `UFUNCTION(BlueprintPure, meta=(ScriptMethod), Category="Sequencer|TimeWarp")` — Assign a constant playrate to this timewarp, overwriting any existing timewarp implementation.
- L49 _public prototype_ `static void BreakTimeWarp(const FMovieSceneTimeWarpVariant& TimeWarp, double& FixedPlayRate);` — `UFUNCTION(BlueprintPure, Category="Sequencer|TimeWarp")`
- L52 _public prototype_ `static FMovieSceneTimeWarpVariant MakeTimeWarp(double FixedPlayRate);` — `UFUNCTION(BlueprintPure, Category="Sequencer|TimeWarp")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneTrackExtensions.h` (Public)


#### class `UMovieSceneTrackExtensions`  
`class UMovieSceneTrackExtensions : public UBlueprintFunctionLibrary`  
_L20-147_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneTracks for scripting
- L33 _public prototype_ `static void SetDisplayName(UMovieSceneTrack* Track, const FText& InName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Set this track's display name @param Track        The track to use @param InName The name for this track
- L42 _public prototype_ `static FText GetDisplayName(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Get this track's display name @param Track        The track to use @return This track's display name
- L52 _public prototype_ `static void SetTrackRowDisplayName(UMovieSceneTrack* Track, const FText& InName, int32 RowIndex);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Set this track row's display name @param Track        The track to use @param InName The name for this track @param RowIndex The row index for the track
- L63 _public prototype_ `static FText GetTrackRowDisplayName(UMovieSceneTrack* Track, int32 RowIndex);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Get this track row's display name @param Track        The track to use @param RowIndex The row index for the track @return This track's display name
- L72 _public prototype_ `static UMovieSceneSection* AddSection(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Add a new section to this track @param Track        The track to use @return The newly create section if successful
- L81 _public prototype_ `static TArray<UMovieSceneSection*> GetSections(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Access all this track's sections @param Track        The track to use @return An array of this track's sections
- L90 _public prototype_ `static void RemoveSection(UMovieSceneTrack* Track, UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod))` — Remove the specified section @param Track        The track to remove the section from, if present @param Section      The section to remove
- L99 _public prototype_ `static int32 GetSortingOrder(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Get the sorting order for this track @param Track        The track to get the sorting order from @return The sorting order of the requested track
- L108 _public prototype_ `static void SetSortingOrder(UMovieSceneTrack* Track, int32 SortingOrder);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Set the sorting order for this track @param Track        The track to get the sorting order from @param SortingOrder The sorting order to set
- L117 _public prototype_ `static FColor GetColorTint(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Get the color tint for this track @param Track        The track to get the color tint from @return The color tint of the requested track
- L126 _public prototype_ `static void SetColorTint(UMovieSceneTrack* Track, const FColor& ColorTint);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Set the color tint for this track @param Track        The track to set the color tint for @param ColorTint The color tint to set
- L135 _public prototype_ `static UMovieSceneSection* GetSectionToKey(UMovieSceneTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Get the section to key for this track @param Track        The track to get the section to key for @return The section to key for the requested track
- L146 _public prototype_ `static void SetSectionToKey(UMovieSceneTrack* Track, UMovieSceneSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta=(ScriptMethod, DevelopmentOnly))` — Set the section to key for this track. When properties for this section are modified externally, this section will receive those modifications and act accordingly (add/update keys). This is especially useful when there are multiple overlapping sections. @param Track        The track to set the section to key for @param Section      The section to key for this track

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/MovieSceneVectorTrackExtensions.h` (Public)


#### class `UMovieSceneFloatVectorTrackExtensions`  
`class UMovieSceneFloatVectorTrackExtensions : public UBlueprintFunctionLibrary`  
_L18-41_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneFloatVectorTrack for scripting
- L31 _public prototype_ `static void SetNumChannelsUsed(UMovieSceneFloatVectorTrack* Track, int32 InNumChannelsUsed);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set the number of channels used for this track @param Track        The track to set @param InNumChannelsUsed The number of channels to use for this track
- L40 _public prototype_ `static int32 GetNumChannelsUsed(UMovieSceneFloatVectorTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Get the number of channels used for this track @param Track        The track to query for the number of channels used @return The number of channels used for this track

#### class `UMovieSceneDoubleVectorTrackExtensions`  
`class UMovieSceneDoubleVectorTrackExtensions : public UBlueprintFunctionLibrary`  
_L47-70_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto UMovieSceneDoubleVectorTrack for scripting
- L60 _public prototype_ `static void SetNumChannelsUsed(UMovieSceneDoubleVectorTrack* Track, int32 InNumChannelsUsed);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Set the number of channels used for this track @param Track        The track to set @param InNumChannelsUsed The number of channels to use for this track
- L69 _public prototype_ `static int32 GetNumChannelsUsed(UMovieSceneDoubleVectorTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Track", meta = (ScriptMethod))` — Get the number of channels used for this track @param Track        The track to query for the number of channels used @return The number of channels used for this track

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/ExtensionLibraries/SequencerScriptingRangeExtensions.h` (Public)


#### class `USequencerScriptingRangeExtensions`  
`class USequencerScriptingRangeExtensions : public UBlueprintFunctionLibrary`  
_L17-116_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto FSequencerScriptingRanges
- L27 _public prototype_ `static bool HasStart(const FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Check whether this range has a start @param Range       The range to check
- L35 _public prototype_ `static bool HasEnd(const FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Check whether this range has an end @param Range       The range to check
- L43 _public prototype_ `static void RemoveStart(UPARAM(ref) FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove the start from this range, making it infinite @param Range       The range to remove the start from
- L51 _public prototype_ `static void RemoveEnd(UPARAM(ref) FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Remove the end from this range, making it infinite @param Range       The range to remove the end from
- L59 _public prototype_ `static float GetStartSeconds(const FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the starting time for the specified range in seconds, if it has one. Defined as the first valid time that is inside the range. @param Range       The range to get the start from
- L67 _public prototype_ `static float GetEndSeconds(const FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the ending time for the specified range in seconds, if it has one. Defined as the first time that is outside of the range. @param Range       The range to get the end from
- L75 _public prototype_ `static void SetStartSeconds(UPARAM(ref) FSequencerScriptingRange& Range, float Start);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Set the starting time for the specified range in seconds. Interpreted as the first valid time that is inside the range. @param Range       The range to set the start on
- L83 _public prototype_ `static void SetEndSeconds(UPARAM(ref) FSequencerScriptingRange& Range, float End);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Set the ending time for the specified range in seconds. Interpreted as the first time that is outside of the range. @param Range       The range to set the end on
- L91 _public prototype_ `static int32 GetStartFrame(const FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the starting frame for the specified range, if it has one. Defined as the first valid frame that is inside the range. @param Range       The range to get the start from
- L99 _public prototype_ `static int32 GetEndFrame(const FSequencerScriptingRange& Range);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Get the ending frame for the specified range, if it has one. Defined as the first subsequent frame that is outside of the range. @param Range       The range to get the end from
- L107 _public prototype_ `static void SetStartFrame(UPARAM(ref) FSequencerScriptingRange& Range, int32 Start);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Set the starting frame for the specified range. Interpreted as the first valid frame that is inside the range. @param Range       The range to set the start on
- L115 _public prototype_ `static void SetEndFrame(UPARAM(ref) FSequencerScriptingRange& Range, int32 End);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Sequence", meta=(ScriptMethod))` — Set the ending frame for the specified range. Interpreted as the first subsequent frame that is outside of the range. @param Range       The range to set the end on

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/MovieSceneScriptingChannel.h` (Public)


#### class `UMovieSceneScriptingKey`  
`class UMovieSceneScriptingKey : public UObject`  
_L19-35_
- reflection: `UCLASS(abstract, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L30 _public prototype_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const PURE_VIRTUAL(UMovieSceneScriptingKey::GetTime, return FFrameTime(););` — Gets the time for this key from the owning channel. @param TimeUnit (Optional) Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? Defaults to Display Rate. @return					 The FrameTime of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L32 _public member_ `FKeyHandle KeyHandle;`
- L33 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L34 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`

#### class `UMovieSceneScriptingChannel`  
`class UMovieSceneScriptingChannel : public UObject`  
_L39-62_
- reflection: `UCLASS(abstract, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L49 _public prototype_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const PURE_VIRTUAL(UMovieSceneScriptingChannel::GetKeys, return TArray<UMovieSceneScriptingKey*>(););` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L57 _public prototype_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32> &Indices) const PURE_VIRTUAL(UMovieSceneScriptingChannel::GetKeysByIndex, return TArray<UMovieSceneScriptingKey*>(););` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L61 _public member_ `FName ChannelName;` — `UPROPERTY(BlueprintReadOnly, Category="Sequencer|Keys")`

#### struct `TMovieSceneScriptingChannel`  
`template<typename ChannelType, typename ScriptingKeyType, typename ScriptingKeyValueType> struct TMovieSceneScriptingChannel`  
_L65-415_
- L67 _public function_ `static ScriptingKeyType* AddKeyInChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, const FFrameNumber InTime, ScriptingKeyValueType& NewValue, float SubFrame, EMovieSceneTimeUnit TimeUnit, EMovieSceneKeyInterpolation Interpolation)`
- L120 _public function_ `static void RemoveKeyFromChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, UMovieSceneScriptingKey* Key)`
- L154 _public function_ `static TArray<UMovieSceneScriptingKey*> GetKeysInChannelByIndex(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, const TArray<int32>& Indices)`
- L190 _public function_ `static TArray<UMovieSceneScriptingKey*> GetKeysInChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section)`
- L218 _public function_ `static TArray<ScriptingKeyValueType> EvaluateKeysInChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, FSequencerScriptingRange ScriptingRange, FFrameRate FrameRate)`
- L251 _public function_ `static FSequencerScriptingRange ComputeEffectiveRangeInChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence)`
- L267 _public function_ `static void SetDefaultInChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, ScriptingKeyValueType& InDefaultValue)`
- L293 _public function_ `static void RemoveDefaultFromChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section)`
- L319 _public function_ `static TOptional<ScriptingKeyValueType> GetDefaultFromChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle)`
- L373 _public function_ `static void TransformKeysInChannel(TMovieSceneChannelHandle<ChannelType> ChannelHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, FFrameNumber InOffsetFrame, double InScale, FFrameNumber InPivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit)`

#### struct `TMovieSceneScriptingChannel::FTransformRetiming`  
`struct FTransformRetiming : UE::MovieScene::IRetimingInterface`  
_L339-371_
- inherits: `UE::MovieScene::IRetimingInterface`
- L341 _public function_ `FTransformRetiming(FFrameNumber InOffsetFrame, double InScale, FFrameNumber InPivotFrame, const TRange<FFrameNumber>& InRange) : OffsetFrame(InOffsetFrame) , Scale(InScale) , PivotFrame(InPivotFrame) , Range(InRange)`
- L347 _public function_ `virtual FFrameTime RemapTime(FFrameTime InTime) const override`
- L362 _public function_ `double GetScale() const override`
- L363 _public function_ `TUniquePtr<IRetimingInterface> RecurseInto(UMovieScene* InMovieScene) const override`
- L364 _public function_ `void Begin(UMovieScene* InMovieScene) const override`
- L365 _public function_ `void End(UMovieScene* InMovieScene) const override`
- L367 _public member_ `FFrameNumber OffsetFrame;`
- L368 _public member_ `double Scale = 0.0;`
- L369 _public member_ `FFrameNumber PivotFrame;`
- L370 _public member_ `TRange<FFrameNumber> Range;`

#### struct `TMovieSceneScriptingKey`  
`template<typename ChannelType, typename ChannelDataType> struct TMovieSceneScriptingKey`  
_L422-540_
- desc: The existing Sequencer code is heavily template-based. We cannot create templated UObjects nor create UFUNCTIONS out template functions. This template class serves as a way to minimize boilerplate code when creating UObject versions of the Sequencer key data.
- L424 _public function_ `FFrameTime GetTimeFromChannel(FKeyHandle KeyHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, EMovieSceneTimeUnit TimeUnit) const`
- L453 _public function_ `void SetTimeInChannel(FKeyHandle KeyHandle, TWeakObjectPtr<UMovieSceneSequence> Sequence, TWeakObjectPtr<UMovieSceneSection> Section, const FFrameNumber NewFrameNumber, EMovieSceneTimeUnit TimeUnit, float SubFrame)`
- L494 _public function_ `ChannelDataType GetValueFromChannel(FKeyHandle KeyHandle) const`
- L515 _public function_ `void SetValueInChannel(FKeyHandle KeyHandle, TWeakObjectPtr<UMovieSceneSection> Section, ChannelDataType InNewValue)`
- L539 _public member_ `TMovieSceneChannelHandle<ChannelType> ChannelHandle;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SEQUENCERSCRIPTING_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/SequenceTimeUnit.h` (Public)


#### enum `ESequenceTimeUnit`  
`enum class UE_DEPRECATED(5.4, "ESequenceTimeUnit is deprecated, please use EMovieSceneTimeUnit") ESequenceTimeUnit : uint8`  
_L8-12_
- reflection: `UENUM()`
- L10 _public enumerator_ `DisplayRate`
- L11 _public enumerator_ `TickResolution`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/SequencerBindingProxy.h` (Public)
_(no declarations extracted)_

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/SequencerScripting.h` (Public)


#### class `FSequencerScriptingModule`  
`class FSequencerScriptingModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScripting/Public/SequencerScriptingRange.h` (Public)


#### struct `FSequencerScriptingRange`  
`struct FSequencerScriptingRange`  
_L15-97_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public function_ `FSequencerScriptingRange() : bHasStart(0), bHasEnd(0), InclusiveStart(0), ExclusiveEnd(0)`
- L23 _public function_ `static FSequencerScriptingRange FromNative(const TRange<FFrameNumber>& InRange, FFrameRate InputRate)`
- L43 _public function_ `static FSequencerScriptingRange FromNative(const TRange<FFrameNumber>& InRange, FFrameRate InputRate, FFrameRate InOutputRate)`
- L64 _public function_ `TRange<FFrameNumber> ToNative(FFrameRate OutputRate) const`
- L84 _public member_ `uint8 bHasStart : 1;` — `UPROPERTY(BlueprintReadWrite, Category=Range, meta=(ScriptName="HasStartValue"))`
- L87 _public member_ `uint8 bHasEnd : 1;` — `UPROPERTY(BlueprintReadWrite, Category=Range, meta=(ScriptName="HasEndValue"))`
- L90 _public member_ `int32 InclusiveStart;` — `UPROPERTY(BlueprintReadWrite, Category=Range)`
- L93 _public member_ `int32 ExclusiveEnd;` — `UPROPERTY(BlueprintReadWrite, Category=Range)`
- L96 _public member_ `FFrameRate InternalRate;` — `UPROPERTY()`
