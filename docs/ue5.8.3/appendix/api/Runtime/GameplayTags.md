# Runtime / GameplayTags

- module root: `Source/Runtime/GameplayTags`
- headers: 13; symbols: 649
- symbol kinds: class=22, delegate=7, enum=9, enumerator=38, function=114, macro=6, member=141, namespace=17, prototype=273, struct=21, typedef=1
- PrivateDependencyModuleNames: Json, JsonUtilities, NetCore, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine

### `Source/Runtime/GameplayTags/Classes/BlueprintGameplayTagLibrary.h` (Public)


#### class `UBlueprintGameplayTagLibrary`  
`class UBlueprintGameplayTagLibrary : public UBlueprintFunctionLibrary`  
_L15-307_
- reflection: `UCLASS(meta=(ScriptName="GameplayTagLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L29 _private prototype_ `static bool MatchesTag(FGameplayTag TagOne, FGameplayTag TagTwo, bool bExactMatch);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (Keywords = "DoGameplayTagsMatch", BlueprintThreadSafe))` — Determine if TagOne matches against TagTwo @param TagOne			Tag to check for match @param TagTwo			Tag to check match against @param bExactMatch		If true, the tag has to be exactly present, if false then TagOne will include it's parent tags while matching @return True if TagOne matches TagTwo
- L41 _private prototype_ `static bool MatchesAnyTags(FGameplayTag TagOne, const FGameplayTagContainer& OtherContainer, bool bExactMatch);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (BlueprintThreadSafe))` — Determine if TagOne matches against any tag in OtherContainer @param TagOne			Tag to check for match @param OtherContainer	Container to check against. @param bExactMatch		If true, the tag has to be exactly present, if false then TagOne will include it's parent tags while matching @return True if TagOne matches any tags explicitly present in OtherContainer
- L45 _private prototype_ `static bool EqualEqual_GameplayTag( FGameplayTag A, FGameplayTag B );` — `UFUNCTION(BlueprintPure, meta=(DisplayName="Equal (GameplayTag)", CompactNodeTitle="==", BlueprintThreadSafe), Category="GameplayTags")` — Returns true if the values are equal (A == B)
- L49 _private prototype_ `static bool NotEqual_GameplayTag( FGameplayTag A, FGameplayTag B );` — `UFUNCTION(BlueprintPure, meta=(DisplayName="Not Equal (GameplayTag)", CompactNodeTitle="!=", BlueprintThreadSafe), Category="GameplayTags")` — Returns true if the values are not equal (A != B)
- L53 _private prototype_ `static bool IsGameplayTagValid(FGameplayTag GameplayTag);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Returns true if the passed in gameplay tag is non-null
- L57 _private prototype_ `static FName GetTagName(const FGameplayTag& GameplayTag);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Returns FName of this tag
- L61 _private prototype_ `static FGameplayTag MakeLiteralGameplayTag(FGameplayTag Value);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a literal FGameplayTag
- L71 _private prototype_ `static int32 GetNumGameplayTagsInContainer(const FGameplayTagContainer& TagContainer);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (BlueprintThreadSafe))` — Get the number of gameplay tags in the specified container @param TagContainer	Tag container to get the number of tags from @return The number of tags in the specified container
- L83 _private prototype_ `static bool HasTag(const FGameplayTagContainer& TagContainer, FGameplayTag Tag, bool bExactMatch);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (Keywords = "DoesContainerHaveTag", BlueprintThreadSafe))` — Check if the tag container has the specified tag @param TagContainer			Container to check for the tag @param Tag					Tag to check for in the container @param bExactMatch			If true, the tag has to be exactly present, if false then TagContainer will include it's parent tags while matching @return True if the container has the specified tag, false if it does not
- L95 _private prototype_ `static bool HasAnyTags(const FGameplayTagContainer& TagContainer, const FGameplayTagContainer& OtherContainer, bool bExactMatch);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (Keywords = "DoesContainerMatchAnyTagsInContainer", BlueprintThreadSafe))` — Check if the specified tag container has ANY of the tags in the other container @param TagContainer			Container to check if it matches any of the tags in the other container @param OtherContainer		Container to check against. @param bExactMatch			If true, the tag has to be exactly present, if false then TagContainer will include it's parent tags while matching @return True if the container has ANY of the tags in the other container
- L107 _private prototype_ `static bool HasAllTags(const FGameplayTagContainer& TagContainer, const FGameplayTagContainer& OtherContainer, bool bExactMatch);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (Keywords = "DoesContainerMatchAllTagsInContainer", BlueprintThreadSafe))` — Check if the specified tag container has ALL of the tags in the other container @param TagContainer			Container to check if it matches all of the tags in the other container @param OtherContainer		Container to check against. If this is empty, the check will succeed @param bExactMatch			If true, the tag has to be exactly present, if false then TagContainer will include it's parent tags while matching @return True if the container has ALL of the tags in the other container
- L118 _private prototype_ `static FGameplayTagContainer Filter(const FGameplayTagContainer& TagContainer, const FGameplayTagContainer& OtherContainer, bool bExactMatch);` — `UFUNCTION(BlueprintPure, Category="GameplayTags", meta = (BlueprintThreadSafe))` — Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer @param OtherContainer		The Container to filter against @param bExactMatch			If true, the tag has to be exactly present, if false then TagContainer will include it's parent tags while matching @return A FGameplayTagContainer containing the filtered tags
- L128 _private prototype_ `static bool IsTagQueryEmpty(const FGameplayTagQuery& TagQuery);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Check if the specified tag query is empty @param TagQuery				Query to check @return True if the query is empty, false otherwise.
- L139 _private prototype_ `static bool DoesContainerMatchTagQuery(const FGameplayTagContainer& TagContainer, const FGameplayTagQuery& TagQuery);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Check if the specified tag container matches the given Tag Query @param TagContainer			Container to check if it matches all of the tags in the other container @param TagQuery				Query to match against @return True if the container matches the query, false otherwise.
- L149 _private prototype_ `static void GetAllActorsOfClassMatchingTagQuery(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FGameplayTagQuery& GameplayTagQuery, TArray<AActor*>& OutActors);` — `UFUNCTION(BlueprintCallable, Category="GameplayTags", meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))` — Get an array of all actors of a specific class (or subclass of that class) which match the specified gameplay tag query. @param ActorClass			Class of actors to fetch @param GameplayTagQuery		Query to match against
- L158 _private prototype_ `static void AddGameplayTag(UPARAM(ref) FGameplayTagContainer& TagContainer, FGameplayTag Tag);` — `UFUNCTION(BlueprintCallable, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Adds a single tag to the passed in tag container @param InOutTagContainer		The container that will be appended too. @param Tag					The tag to add to the container
- L167 _private prototype_ `static bool RemoveGameplayTag(UPARAM(ref) FGameplayTagContainer& TagContainer, FGameplayTag Tag);` — `UFUNCTION(BlueprintCallable, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Remove a single tag from the passed in tag container, returns true if found @param InOutTagContainer		The container that will be appended too. @param Tag					The tag to add to the container
- L176 _private prototype_ `static void AppendGameplayTagContainers(UPARAM(ref) FGameplayTagContainer& InOutTagContainer, const FGameplayTagContainer& InTagContainer);` — `UFUNCTION(BlueprintCallable, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Appends all tags in the InTagContainer to InOutTagContainer @param InOutTagContainer		The container that will be appended too. @param InTagContainer		The container to append.
- L180 _private prototype_ `static bool EqualEqual_GameplayTagContainer( const FGameplayTagContainer& A, const FGameplayTagContainer& B );` — `UFUNCTION(BlueprintPure, meta=(DisplayName="Equal (GameplayTagContainer)", CompactNodeTitle="==", BlueprintThreadSafe), Category="GameplayTags")` — Returns true if the values are equal (A == B)
- L184 _private prototype_ `static bool NotEqual_GameplayTagContainer( const FGameplayTagContainer& A, const FGameplayTagContainer& B );` — `UFUNCTION(BlueprintPure, meta=(DisplayName="Not Equal (GameplayTagContainer)", CompactNodeTitle="!=", BlueprintThreadSafe), Category="GameplayTags")` — Returns true if the values are not equal (A != B)
- L188 _private prototype_ `static FGameplayTagContainer MakeLiteralGameplayTagContainer(FGameplayTagContainer Value);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a literal FGameplayTagContainer
- L192 _private prototype_ `static FGameplayTagContainer MakeGameplayTagContainerFromArray(const TArray<FGameplayTag>& GameplayTags);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a FGameplayTagContainer from the array of passed in tags
- L196 _private prototype_ `static FGameplayTagContainer MakeGameplayTagContainerFromTag(FGameplayTag SingleTag);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a FGameplayTagContainer containing a single tag
- L200 _private prototype_ `static void BreakGameplayTagContainer(const FGameplayTagContainer& GameplayTagContainer, TArray<FGameplayTag>& GameplayTags);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Breaks tag container into explicit array of tags
- L210 _private prototype_ `static FGameplayTagQuery MakeGameplayTagQuery(FGameplayTagQuery TagQuery);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a literal FGameplayTagQuery @param	TagQuery	value to set the FGameplayTagQuery to @return	The literal FGameplayTagQuery
- L220 _private prototype_ `static FGameplayTagQuery MakeGameplayTagQuery_MatchAnyTags(const FGameplayTagContainer& InTags);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a literal FGameplayTagQuery with a prepopulated AnyTagsMatch expression @param	InTags	value to set the FGameplayTagQuery expression @return	The literal FGameplayTagQuery
- L230 _private prototype_ `static FGameplayTagQuery MakeGameplayTagQuery_MatchAllTags(const FGameplayTagContainer& InTags);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a literal FGameplayTagQuery with a prepopulated AllTagsMatch expression @param	InTags	value to set the FGameplayTagQuery expression @return	The literal FGameplayTagQuery
- L240 _private prototype_ `static FGameplayTagQuery MakeGameplayTagQuery_MatchNoTags(const FGameplayTagContainer& InTags);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe))` — Creates a literal FGameplayTagQuery with a prepopulated NoTagsMatch expression @param	InTags	value to set the FGameplayTagQuery expression @return	The literal FGameplayTagQuery
- L251 _private prototype_ `static bool HasAllMatchingGameplayTags(TScriptInterface<IGameplayTagAssetInterface> TagContainerInterface, const FGameplayTagContainer& OtherContainer);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "TRUE"))` — Check Gameplay tags in the interface has all of the specified tags in the tag container (expands to include parents of asset tags) @param TagContainerInterface		An Interface to a tag container @param OtherContainer			A Tag Container @return True if the tagcontainer in the interface has all the tags inside the container.
- L262 _private prototype_ `static bool HasAnyMatchingGameplayTags(TScriptInterface<IGameplayTagAssetInterface> TagContainerInterface, const FGameplayTagContainer& OtherContainer);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "TRUE"))` — Check Gameplay tags in the interface has ANY of the specified tags in the tag container (expands to include parents of asset tags) @param TagContainerInterface		An Interface to a tag container @param OtherContainer			A Tag Container @return True if the tagcontainer in the interface has ANY of the tags inside the container.
- L273 _private prototype_ `static bool DoesTagAssetInterfaceHaveTag(TScriptInterface<IGameplayTagAssetInterface> TagContainerInterface, FGameplayTag Tag);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "TRUE"))` — Check if the specified tag container has the specified tag, using the specified tag matching types @param TagContainerInterface		An Interface to a tag container @param Tag						Tag to check for in the container @return True if the container has the specified tag, false if it does not
- L277 _private prototype_ `static bool NotEqual_TagTag(FGameplayTag A, FString B);` — `UFUNCTION(BlueprintPure, Category = PinOptions, meta = (BlueprintInternalUseOnly = "TRUE"))` — Checks if a gameplay tag's name and a string are not equal to one another
- L281 _private prototype_ `static bool NotEqual_TagContainerTagContainer(FGameplayTagContainer A, FString B);` — `UFUNCTION(BlueprintPure, Category = PinOptions, meta = (BlueprintInternalUseOnly = "TRUE"))` — Checks if a gameplay tag containers's name and a string are not equal to one another
- L285 _private prototype_ `static UPARAM(DisplayName = "Owned Tags") FGameplayTagContainer GetOwnedGameplayTags(TScriptInterface<IGameplayTagAssetInterface> TagContainerI` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta=(DefaultToSelf=TagContainerInterface))` — @return the tags currently owned by the TagContainerInterface object
- L289 _private prototype_ `static TScriptInterface<IGameplayTagAssetInterface> Conv_ObjectToGameplayTagAssetInterface(UObject* InObject);` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "To GameplayTagAssetInterface", CompactNodeTitle = "->", BlueprintAutocast), Category="Utilities|Casting")` — Converts a UObject to a GameplayTagAssetInterface. This specialty Autocast function exists so we can auto-convert the GameplayTagAssetInterface member functions to static Blueprint functions using redirects.
- L297 _private prototype_ `static FString GetDebugStringFromGameplayTagContainer(const FGameplayTagContainer& TagContainer);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe, BlueprintAutocast))` — Returns an FString listing all of the gameplay tags in the tag container for debugging purposes. @param TagContainer	The tag container to get the debug string from.
- L305 _private prototype_ `static FString GetDebugStringFromGameplayTag(FGameplayTag GameplayTag);` — `UFUNCTION(BlueprintPure, Category = "GameplayTags", meta = (BlueprintThreadSafe, BlueprintAutocast))` — Returns an FString representation of a gameplay tag for debugging purposes. @param GameplayTag	The tag to get the debug string from.

### `Source/Runtime/GameplayTags/Classes/GameplayTagAssetInterface.h` (Public)


#### class `UGameplayTagAssetInterface`  
`class UGameplayTagAssetInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for assets which contain gameplay tags

#### class `IGameplayTagAssetInterface`  
`class IGameplayTagAssetInterface`  
_L19-67_
- L28 _private prototype_ `virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const=0;` — Get any owned gameplay tags on the asset @param OutTags	[OUT] Set of tags on the asset
- L38 _private prototype_ `virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;` — `UFUNCTION(BlueprintCallable, Category=GameplayTags)` — Check if the asset has a gameplay tag that matches against the specified tag (expands to include parents of asset tags) @param TagToCheck	Tag to check for a match @return True if the asset has a gameplay tag that matches, false if not
- L48 _private prototype_ `virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;` — `UFUNCTION(BlueprintCallable, Category=GameplayTags)` — Check if the asset has gameplay tags that matches against all of the specified tags (expands to include parents of asset tags) @param TagContainer			Tag container to check for a match @return True if the asset has matches all of the gameplay tags, will be true if container is empty
- L58 _private prototype_ `virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;` — `UFUNCTION(BlueprintCallable, Category=GameplayTags)` — Check if the asset has gameplay tags that matches against any of the specified tags (expands to include parents of asset tags) @param TagContainer			Tag container to check for a match @return True if the asset has matches any of the gameplay tags, will be false if container is empty
- L66 _protected prototype_ `virtual UPARAM(DisplayName = "Owned Tags") FGameplayTagContainer BP_GetOwnedGameplayTag` — `UFUNCTION(BlueprintCallable, Category = GameplayTags, BlueprintInternalUseOnly, meta=(DisplayName="Get Owned Gameplay Tags", AllowPrivateAccess=true))` — Gets the owned gameplay tags for the asset.  Exposed to allow redirects of existing GetOwnedGameplayTags calls.  In Blueprints, new nodes will use BlueprintGameplayTagLibrary's version.

### `Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h` (Public)


#### enum `EGameplayContainerMatchType`  
`enum class EGameplayContainerMatchType : uint8`  
_L24-31_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `Any` — Means the filter is populated by any tag matches in this container.
- L30 _public enumerator_ `All` — Means the filter is only populated if all of the tags in this container match.

#### struct `FGameplayTag`  
`struct FGameplayTag`  
_L41-230_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake = "/Script/GameplayTags.BlueprintGameplayTagLibrary.MakeLiteralGameplayTag", HasNativeBreak = "/Script/GameplayTags.BlueprintGameplayTagLibrary.GetTagName", DisableSplitPin))`
- desc: A single gameplay tag, which represents a hierarchical name of the form x.y that is registered in the GameplayTagsManager You can filter the gameplay tags displayed in the editor using, meta = (Categories = "Tag1.Tag2.Tag3"))
- L46 _public function_ `FGameplayTag()` — Constructors
- L57 _public prototype_ `static FGameplayTag RequestGameplayTag(const FName& TagName, bool ErrorIfNotFound=true);` — Gets the FGameplayTag that corresponds to the TagName @param TagName The Name of the tag to search for @param ErrorIfNotfound: ensure() that tag exists. @return Will return the corresponding FGameplayTag or an empty one if not found.
- L66 _public prototype_ `static bool IsValidGameplayTagString(const FString& TagString, FText* OutError = nullptr, FString* OutFixedString = nullptr);` — Returns true if this is a valid gameplay tag string (foo.bar.baz). If false, it will fill @param TagString String to check for validity @param OutError If non-null and string invalid, will fill in with an error message @param OutFixedString If non-null and string invalid, will attempt to fix. Will be empty if no fix is possible @return True if this can be added to the tag dictionary, false if there's a syntax error
- L69 _public function_ `inline bool operator==(FGameplayTag const& Other) const` — Operators
- L74 _public function_ `inline bool operator!=(FGameplayTag const& Other) const`
- L79 _public function_ `inline bool operator<(FGameplayTag const& Other) const`
- L91 _public prototype_ `bool MatchesTag(const FGameplayTag& TagToCheck) const;` — Determine if this tag matches TagToCheck, expanding out parent tags "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False If TagToCheck is not Valid it will always return False @return True if this tag matches TagToCheck
- L100 _public function_ `inline bool MatchesTagExact(const FGameplayTag& TagToCheck) const` — Determine if TagToCheck is valid and exactly matches this tag "A.1".MatchesTagExact("A") will return False If TagToCheck is not Valid it will always return False @return True if TagToCheck is Valid and is exactly this tag
- L117 _public prototype_ `int32 MatchesTagDepth(const FGameplayTag& TagToCheck) const;` — Check to see how closely two FGameplayTags match. Higher values indicate more matching terms in the tags. @param TagToCheck	Tag to match against @return The depth of the match, higher means they are closer to an exact match
- L126 _public prototype_ `bool MatchesAny(const FGameplayTagContainer& ContainerToCheck) const;` — Checks if this tag matches ANY of the tags in the specified container, also checks against our parent tags "A.1".MatchesAny({"A","B"}) will return True, "A".MatchesAny({"A.1","B"}) will return False If ContainerToCheck is empty/invalid it will always return False @return True if this tag matches ANY of the tags of in ContainerToCheck
- L135 _public prototype_ `bool MatchesAnyExact(const FGameplayTagContainer& ContainerToCheck) const;` — Checks if this tag matches ANY of the tags in the specified container, only allowing exact matches "A.1".MatchesAny({"A","B"}) will return False If ContainerToCheck is empty/invalid it will always return False @return True if this tag matches ANY of the tags of in ContainerToCheck exactly
- L138 _public function_ `inline bool IsValid() const` — Returns whether the tag is valid or not; Invalid tags are set to NAME_None and do not exist in the game-specific global dictionary
- L144 _public prototype_ `FGameplayTagContainer GetSingleTagContainer() const;` — Returns a GameplayTagContainer containing only this tag
- L147 _public prototype_ `FGameplayTag RequestDirectParent() const;` — Returns direct parent GameplayTag of this GameplayTag, calling on x.y will return x
- L153 _public prototype_ `FGameplayTagContainer GetGameplayTagParents() const;` — Returns a new tag container that includes this tag and all parent tags as explicitly added tags. For example, calling this on x.y.z would return a tag container with x.y.z, x.y, and x
- L159 _public prototype_ `void ParseParentTags(TArray<FGameplayTag>& UniqueParentTags) const;` — Parses the tag name and fills in UniqueParentTags with raw parent tags, without validating with the tag manager. For example, calling this on x.y.z would add x.y and x to UniqueParentTags if they were not already in the array
- L165 _public prototype_ `FName GetTagLeafName() const;` — Parses the tag name and returns the name of the leaf. For example, calling this on x.y.z would return the z component.
- L174 _public function_ `inline FString ToString() const` — Displays gameplay tag as a string for blueprint graph usage
- L180 _public function_ `inline FName GetTagName() const` — Get the tag represented as a name
- L196 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Overridden for fast serialize
- L199 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Handles fixup and errors. This is only called when not serializing a full FGameplayTagContainer
- L200 _public prototype_ `bool NetSerialize_Packed(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L203 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Used to upgrade a Name property to a GameplayTag struct property
- L206 _public prototype_ `void FromExportString(const FString& ExportString, int32 PortFlags = 0);` — Sets from a ImportText string, used in asset registry
- L209 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);` — Handles importing tag strings without (TagName=) in it
- L212 _public member_ `static const FGameplayTag EmptyTag;` — An empty Gameplay Tag
- L216 _protected prototype_ `bool NetSerialize_ForReplayUsingFastReplication(FArchive& Ar, class UPackageMapClient& PackageMapClient);`
- L219 _protected prototype_ `explicit FGameplayTag(const FName& InTagName);` — Intentionally private so only the tag manager can use
- L223 _protected member_ `FName TagName;` — `UPROPERTY(VisibleAnywhere, Category = GameplayTags, SaveGame)` — This Tags Name
- L644 _function_ `inline bool FGameplayTag::MatchesAnyExact(const FGameplayTagContainer& ContainerToCheck) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FGameplayTag > : public TStructOpsTypeTraitsBase2< FGameplayTag >`  
_L233-243_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayTag>`
- L666 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L236-242_

#### struct `FGameplayTagContainer`  
`struct FGameplayTagContainer`  
_L247-642_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake = "/Script/GameplayTags.BlueprintGameplayTagLibrary.MakeGameplayTagContainerFromArray", HasNativeBreak = "/Script/GameplayTags.BlueprintGameplayTagLibrary.BreakGameplayTagContainer"))`
- desc: A Tag Container holds a collection of FGameplayTags, tags are included explicitly by adding them, and implicitly from adding child tags
- L252 _public function_ `FGameplayTagContainer()` — Constructors
- L256 _public function_ `FGameplayTagContainer(FGameplayTagContainer const& Other)`
- L262 _public function_ `explicit FGameplayTagContainer(const FGameplayTag& Tag)` — Explicit to prevent people from accidentally using the wrong type of operation
- L267 _public function_ `FGameplayTagContainer(FGameplayTagContainer&& Other) : GameplayTags(MoveTemp(Other.GameplayTags)) , ParentTags(MoveTemp(Other.ParentTags))`
- L274 _public prototype_ `~FGameplayTagContainer() = default;`
- L278 _public function_ `template<class AllocatorType> static FGameplayTagContainer CreateFromArray(const TArray<FGameplayTag, AllocatorType>& SourceTags)` — Creates a container from an array of tags, this is more efficient than adding them all individually
- L287 _public prototype_ `FGameplayTagContainer& operator=(FGameplayTagContainer const& Other);` — Assignment/Equality operators
- L288 _public prototype_ `FGameplayTagContainer& operator=(FGameplayTagContainer&& Other);`
- L289 _public prototype_ `bool operator==(FGameplayTagContainer const& Other) const;`
- L290 _public prototype_ `bool operator!=(FGameplayTagContainer const& Other) const;`
- L299 _public function_ `inline bool HasTag(const FGameplayTag& TagToCheck) const` — Determine if TagToCheck is present in this container, also checking against parent tags {"A.1"}.HasTag("A") will return True, {"A"}.HasTag("A.1") will return False If TagToCheck is not Valid it will always return False @return True if TagToCheck is in this container, false if it is not
- L316 _public function_ `inline bool HasTagExact(const FGameplayTag& TagToCheck) const` — Determine if TagToCheck is explicitly present in this container, only allowing exact matches {"A.1"}.HasTagExact("A") will return False If TagToCheck is not Valid it will always return False @return True if TagToCheck is in this container, false if it is not
- L333 _public function_ `inline bool HasAny(const FGameplayTagContainer& ContainerToCheck) const` — Checks if this container contains ANY of the tags in the specified container, also checks against parent tags {"A.1"}.HasAny({"A","B"}) will return True, {"A"}.HasAny({"A.1","B"}) will return False If ContainerToCheck is empty/invalid it will always return False @return True if this container has ANY of the tags of in ContainerToCheck
- L356 _public function_ `inline bool HasAnyExact(const FGameplayTagContainer& ContainerToCheck) const` — Checks if this container contains ANY of the tags in the specified container, only allowing exact matches {"A.1"}.HasAny({"A","B"}) will return False If ContainerToCheck is empty/invalid it will always return False @return True if this container has ANY of the tags of in ContainerToCheck
- L379 _public function_ `inline bool HasAll(const FGameplayTagContainer& ContainerToCheck) const` — Checks if this container contains ALL of the tags in the specified container, also checks against parent tags {"A.1","B.1"}.HasAll({"A","B"}) will return True, {"A","B"}.HasAll({"A.1","B.1"}) will return False If ContainerToCheck is empty/invalid it will always return True, because there were no failed checks @return True if this container has ALL of the tags of in ContainerToCheck, including if ContainerToCheck is empty
- L402 _public function_ `inline bool HasAllExact(const FGameplayTagContainer& ContainerToCheck) const` — Checks if this container contains ALL of the tags in the specified container, only allowing exact matches {"A.1","B.1"}.HasAll({"A","B"}) will return False If ContainerToCheck is empty/invalid it will always return True, because there were no failed checks @return True if this container has ALL of the tags of in ContainerToCheck, including if ContainerToCheck is empty
- L419 _public function_ `inline int32 Num() const` — Returns the number of explicitly added tags
- L425 _public function_ `inline bool IsValid() const` — Returns whether the container has any valid tags
- L431 _public function_ `inline bool IsEmpty() const` — Returns true if container is empty
- L437 _public prototype_ `FGameplayTagContainer GetGameplayTagParents() const;` — Returns a new container explicitly containing the tags of this container and all of their parent tags
- L446 _public prototype_ `FGameplayTagContainer Filter(const FGameplayTagContainer& OtherContainer) const;` — Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents @param OtherContainer		The Container to filter against @return A FGameplayTagContainer containing the filtered tags
- L455 _public prototype_ `FGameplayTagContainer FilterExact(const FGameplayTagContainer& OtherContainer) const;` — Returns a filtered version of this container, returns all tags that match exactly one in OtherContainer @param OtherContainer		The Container to filter against @return A FGameplayTagContainer containing the filtered tags
- L464 _public prototype_ `bool MatchesQuery(const struct FGameplayTagQuery& Query) const;` — Checks if this container matches the given query. @param Query		Query we are checking against @return True if this container matches the query, false otherwise.
- L472 _public prototype_ `void AppendTags(FGameplayTagContainer const& Other);` — Adds all the tags from one container to this container NOTE: From set theory, this effectively is the union of the container this is called on with Other. @param Other TagContainer that has the tags you want to add to this container
- L487 _public prototype_ `void AppendMatchingTags(FGameplayTagContainer const& OtherA, FGameplayTagContainer const& OtherB);` — Adds all the tags that match between the two specified containers to this container.  WARNING: This matches any parent tag in A, not just exact matches!  So while this should be the union of the container this is called on with the intersection of OtherA and OtherB, it's not exactly that.  Since OtherB matches against its parents, any tag in OtherA which has a parent match with a parent of OtherB will count.  For example, if OtherA has Color.Green and OtherB has Color.Red, that will count as a match due to the Color parent match! If you want an exact match, you need to call A.FilterExact(B) (above) to get the intersection of A with B. If you need the disjunctive union (the union of two sets minus their intersection), use AppendTags to create Union, FilterExact to create Intersection, and then call Union.RemoveTags(Intersection). @param OtherA TagContainer that has the matching tags you want to add to this container, these tags have their parents expanded @param OtherB TagContainer used to check for matching tags.  If the tag matches on any parent, it counts as a match.
- L494 _public prototype_ `void AddTag(const FGameplayTag& TagToAdd);` — Add the specified tag to the container @param TagToAdd Tag to add to the container
- L503 _public prototype_ `void AddTagFast(const FGameplayTag& TagToAdd);` — Add the specified tag to the container without checking for uniqueness @param TagToAdd Tag to add to the container Useful when building container from another data struct (TMap for example)
- L512 _public prototype_ `bool AddLeafTag(const FGameplayTag& TagToAdd);` — Adds a tag to the container and removes any direct parents, wont add if child already exists @param Tag			The tag to try and add to this container @return True if tag was added
- L520 _public prototype_ `bool RemoveTag(const FGameplayTag& TagToRemove, bool bDeferParentTags=false);` — Tag to remove from the container @param TagToRemove		Tag to remove from the container @param bDeferParentTags	Skip calling FillParentTags for performance (must be handled by calling code)
- L527 _public prototype_ `void RemoveTags(const FGameplayTagContainer& TagsToRemove);` — Removes all tags in TagsToRemove from this container @param TagsToRemove	Tags to remove from the container
- L530 _public prototype_ `void Reset(int32 Slack = 0);` — Remove all tags from the container. Will maintain slack by default
- L533 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);` — Serialize the tag container
- L536 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Efficient network serialize, takes advantage of the dictionary
- L539 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);` — Handles fixup after importing from text
- L542 _public prototype_ `void PostScriptConstruct();` — Fill in the ParentTags array and any other transient parameters
- L545 _public prototype_ `FString ToString() const;` — Returns string version of container in ImportText format
- L548 _public prototype_ `void FromExportString(const FString& ExportString, int32 PortFlags = 0);` — Sets from a ImportText string, used in asset registry
- L551 _public prototype_ `FString ToStringSimple(bool bQuoted = false) const;` — Returns abbreviated human readable Tag list without parens or property names. If bQuoted is true it will quote each tag
- L554 _public prototype_ `TArray<FString> ToStringsMaxLen(int32 MaxLen) const;` — Returns abbreviated human readable Tag list without parens or property names, but will limit each string to specified len.  This is to get around output restrictions
- L557 _public prototype_ `FText ToMatchingText(EGameplayContainerMatchType MatchType, bool bInvertCondition) const;` — Returns human readable description of what match is being looked for on the readable tag list.
- L560 _public function_ `void GetGameplayTagArray(TArray<FGameplayTag>& InOutGameplayTags) const` — Gets the explicit list of gameplay tags
- L566 _public prototype_ `const TArray<FGameplayTag>& GetGameplayTagArray() const;` — Gets the explicit list of gameplay tags
- L569 _public function_ `TArray<FGameplayTag>::TConstIterator CreateConstIterator() const` — Creates a const iterator for the contents of this array
- L574 _public function_ `bool IsValidIndex(int32 Index) const`
- L579 _public function_ `FGameplayTag GetByIndex(int32 Index) const`
- L588 _public function_ `FGameplayTag First() const`
- L593 _public function_ `FGameplayTag Last() const`
- L599 _public prototype_ `void FillParentTags();` — Fills in ParentTags from GameplayTags
- L602 _public member_ `static const FGameplayTagContainer EmptyContainer;` — An empty Gameplay Tag Container
- L613 _protected prototype_ `bool RemoveTagByExplicitName(const FName& TagName);` — If a Tag with the specified tag name explicitly exists, it will remove that tag and return true.  Otherwise, it returns false.  It does NOT check the TagName for validity (i.e. the tag could be obsolete and so not exist in the table). It also does NOT check parents (because it cannot do so for a tag that isn't in the table). NOTE: This function should ONLY ever be used by GameplayTagsManager when redirecting tags.  Do NOT make this function public!
- L616 _protected prototype_ `void AddParentsForTag(const FGameplayTag& Tag);` — `UE_DEPRECATED(5.4, "Use ParseParentTags or ExtractParentTags instead")`
- L620 _protected member_ `TArray<FGameplayTag> GameplayTags;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=GameplayTags, SaveGame)` — Array of gameplay tags
- L624 _protected member_ `TArray<FGameplayTag> ParentTags;` — `UPROPERTY(Transient)` — Array of expanded parent tags, in addition to GameplayTags. Used to accelerate parent searches. May contain duplicates in some cases

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayTagContainer> : public TStructOpsTypeTraitsBase2<FGameplayTagContainer>`  
_L654-667_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayTagContainer>`
- L666 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L657-665_

#### struct `FGameplayTagNativeAdder`  
`struct FGameplayTagNativeAdder`  
_L670-679_
- desc: Class that can be subclassed by a game/plugin to allow easily adding native gameplay tags at startup
- L672 _public prototype_ `FGameplayTagNativeAdder();`
- L674 _public prototype_ `virtual ~FGameplayTagNativeAdder();`
- L676 _public prototype_ `virtual void AddTags() = 0;`
- L678 _public member_ `FDelegateHandle AddTagsHandle;`

#### struct `FGameplayTagCreationWidgetHelper`  
`struct FGameplayTagCreationWidgetHelper`  
_L683-686_
- reflection: `USTRUCT()`
- desc: Helper struct: drop this in another struct to get an embedded create new tag widget.

#### enum `EGameplayTagQueryExprType`  
`enum class EGameplayTagQueryExprType : uint8`  
_L690-701_
- reflection: `UENUM()`
- desc: Enumerates the list of supported query expression types.
- L692 _public enumerator_ `Undefined = 0`
- L693 _public enumerator_ `AnyTagsMatch`
- L694 _public enumerator_ `AllTagsMatch`
- L695 _public enumerator_ `NoTagsMatch`
- L696 _public enumerator_ `AnyExprMatch`
- L697 _public enumerator_ `AllExprMatch`
- L698 _public enumerator_ `NoExprMatch`
- L699 _public enumerator_ `AnyTagsExactMatch`
- L700 _public enumerator_ `AllTagsExactMatch`

#### enum `EGameplayTagQueryStreamVersion::Type`  
`enum Type`  
_L705-713_
- L707 _public enumerator_ `InitialVersion = 0`
- L711 _public enumerator_ `VersionPlusOne` — -----<new versions can be added before this line>------------------------------------------------- - this needs to be the last line (see note below)
- L712 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FGameplayTagQuery`  
`struct FGameplayTagQuery`  
_L737-863_
- reflection: `USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/GameplayTags.BlueprintGameplayTagLibrary.MakeGameplayTagQuery"))`
- desc: An FGameplayTagQuery is a logical query that can be run against an FGameplayTagContainer.  A query that succeeds is said to "match". Queries are logical expressions that can test the intersection properties of another tag container (all, any, or none), or the matching state of a set of sub-expressions (all, any, or none). This allows queries to be arbitrarily recursive and very expressive.  For instance, if you wanted to test if a given tag container contained tags ((A && B) || (C)) && (!D), you would construct your query in the form ALL( ANY( ALL(A,B), ALL(C) ), NONE(D) ) You can expose the query structs to Blueprints and edit them with a custom editor, or you can construct them natively in code. Example of how to build a query via code: FGameplayTagQuery Q; Q.BuildQuery( FGameplayTagQueryExpression() .AllTagsMatch() .AddTag(FGameplayTag::RequestGameplayTag(FName("Animal.Mammal.Dog.Corgi"))) .AddTag(FGameplayTag::RequestGameplayTag(FName("Plant.Tree.Spruce"))) ); Queries are internally represented as a byte stream that is memory-efficient and can be evaluated quickly at runtime. Note: these have an extensive details and graph pin customization for editing, so there is no need to expose the internals to Blueprints.
- L742 _public prototype_ `FGameplayTagQuery();`
- L744 _public prototype_ `FGameplayTagQuery(FGameplayTagQuery const& Other);`
- L745 _public prototype_ `FGameplayTagQuery(FGameplayTagQuery&& Other);`
- L748 _public prototype_ `FGameplayTagQuery& operator=(FGameplayTagQuery const& Other);` — Assignment/Equality operators
- L749 _public prototype_ `FGameplayTagQuery& operator=(FGameplayTagQuery&& Other);`
- L751 _public prototype_ `bool operator==(const FGameplayTagQuery& Other) const;`
- L752 _public prototype_ `bool operator!=(const FGameplayTagQuery& Other) const;`
- L759 _private member_ `int32 TokenStreamVersion;` — `UPROPERTY(EditAnywhere, Category = Hidden)` — Versioning for future token stream protocol changes. See EGameplayTagQueryStreamVersion.
- L763 _private member_ `TArray<FGameplayTag> TagDictionary;` — `UPROPERTY(EditAnywhere, Category = Hidden)` — List of tags referenced by this entire query. Token stream stored indices into this list.
- L767 _private member_ `TArray<uint8> QueryTokenStream;` — `UPROPERTY(EditAnywhere, Category = Hidden)` — Stream representation of the actual hierarchical query
- L771 _private member_ `FString UserDescription;` — `UPROPERTY(EditAnywhere, Category = Hidden)` — User-provided string describing the query
- L775 _private member_ `FString AutoDescription;` — `UPROPERTY(EditAnywhere, Category = Hidden)` — Auto-generated string describing the query
- L778 _private function_ `FGameplayTag GetTagFromIndex(int32 TagIdx) const` — Returns a gameplay tag from the tag dictionary
- L787 _public function_ `void ReplaceTagsFast(FGameplayTagContainer const& Tags)` — Replaces existing tags with passed in tags. Does not modify the tag query expression logic. Useful when you need to cache off and update often used query. Must use same sized tag container!
- L795 _public function_ `void ReplaceTagFast(FGameplayTag const& Tag)` — Replaces existing tags with passed in tag. Does not modify the tag query expression logic. Useful when you need to cache off and update often used query.
- L803 _public prototype_ `bool Matches(FGameplayTagContainer const& Tags) const;` — Returns true if the given tags match this query, or false otherwise.
- L806 _public prototype_ `bool IsEmpty() const;` — Returns true if this query is empty, false otherwise.
- L809 _public prototype_ `void Clear();` — Resets this query to its default empty state.
- L812 _public prototype_ `void Build(struct FGameplayTagQueryExpression& RootQueryExpr, FString InUserDescription = FString());` — Creates this query with the given root expression.
- L815 _public prototype_ `static FGameplayTagQuery BuildQuery(struct FGameplayTagQueryExpression& RootQueryExpr, FString InDescription = FString());` — Static function to assemble and return a query.
- L818 _public prototype_ `void GetQueryExpr(struct FGameplayTagQueryExpression& OutExpr) const;` — Builds a FGameplayTagQueryExpression from this query.
- L821 _public prototype_ `void Serialize(FArchive& Ar);` — Serialize the tag query
- L824 _public function_ `void SetUserDescription(const FString& InUserDescription)` — Sets the user-specified description of this query.
- L827 _public function_ `const FString& GetDescription() const` — Returns description string.
- L830 _public function_ `void GetGameplayTagArray(TArray<FGameplayTag>& OutGameplayTags) const` — Gets the explicit list of all unique gameplay tags referenced by the query.
- L836 _public prototype_ `const TArray<FGameplayTag>& GetGameplayTagArray() const;` — Gets the explicit list of all unique gameplay tags referenced by the query.
- L840 _public prototype_ `void BuildFromEditableQuery(class UEditableGameplayTagQuery& EditableQuery);` — Creates this query based on the given EditableQuery object
- L843 _public prototype_ `UEditableGameplayTagQuery* CreateEditableQuery() const;` — Creates editable query object tree based on this query
- L846 _public member_ `static const FGameplayTagQuery EmptyQuery;`
- L854 _public prototype_ `static FGameplayTagQuery MakeQuery_MatchAnyTags(FGameplayTagContainer const& InTags);` — Creates a tag query that will match if there are any common tags between the given tags and the tags being queries against.
- L855 _public prototype_ `static FGameplayTagQuery MakeQuery_MatchAllTags(FGameplayTagContainer const& InTags);`
- L856 _public prototype_ `static FGameplayTagQuery MakeQuery_MatchNoTags(FGameplayTagContainer const& InTags);`
- L857 _public prototype_ `static FGameplayTagQuery MakeQuery_ExactMatchAnyTags(FGameplayTagContainer const& InTags);`
- L858 _public prototype_ `static FGameplayTagQuery MakeQuery_ExactMatchAllTags(FGameplayTagContainer const& InTags);`
- L860 _public prototype_ `static FGameplayTagQuery MakeQuery_MatchTag(FGameplayTag const& InTag);`

#### struct `FGameplayTagQueryExpression`  
`struct FGameplayTagQueryExpression`  
_L865-973_
- L871 _public function_ `FGameplayTagQueryExpression& AnyTagsMatch()`
- L877 _public function_ `FGameplayTagQueryExpression& AllTagsMatch()`
- L883 _public function_ `FGameplayTagQueryExpression& NoTagsMatch()`
- L889 _public function_ `FGameplayTagQueryExpression& AnyTagsExactMatch()`
- L895 _public function_ `FGameplayTagQueryExpression& AllTagsExactMatch()`
- L901 _public function_ `FGameplayTagQueryExpression& AnyExprMatch()`
- L907 _public function_ `FGameplayTagQueryExpression& AllExprMatch()`
- L913 _public function_ `FGameplayTagQueryExpression& NoExprMatch()`
- L919 _public function_ `FGameplayTagQueryExpression& AddTag(TCHAR const* TagString)`
- L923 _public prototype_ `FGameplayTagQueryExpression& AddTag(FName TagName);`
- L924 _public function_ `FGameplayTagQueryExpression& AddTag(FGameplayTag Tag)`
- L931 _public function_ `FGameplayTagQueryExpression& AddTags(FGameplayTagContainer const& Tags)`
- L938 _public function_ `FGameplayTagQueryExpression& AddExpr(FGameplayTagQueryExpression& Expr)`
- L946 _public prototype_ `void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary) const;` — Writes this expression to the given token stream.
- L949 _public member_ `EGameplayTagQueryExprType ExprType;` — Which type of expression this is.
- L952 _public member_ `TArray<struct FGameplayTagQueryExpression> ExprSet;` — Expression list, for expression types that need it
- L955 _public member_ `TArray<FGameplayTag> TagSet;` — Tag list, for expression types that need it
- L958 _public function_ `inline bool UsesTagSet() const` — Returns true if this expression uses the tag data.
- L963 _public function_ `inline bool UsesExprSet() const` — Returns true if this expression uses the expression list data.
- L969 _public prototype_ `bool ConvertToJsonObject(TSharedRef<FJsonObject>& OutObject) const;` — Converts the existing TagQueryExpression into a json object. Returns true on success
- L972 _public prototype_ `static bool MakeFromJsonObject(const TSharedRef<FJsonObject>& InObject, FGameplayTagQueryExpression& OutQueryExpression);` — Uses the input json object and fills out the OutQueryExpression with the data.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayTagQuery> : public TStructOpsTypeTraitsBase2<FGameplayTagQuery>`  
_L976-982_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayTagQuery>`
- L666 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L979-981_

#### class `UEditableGameplayTagQuery`  
`class UEditableGameplayTagQuery : public UObject`  
_L993-1021_
- reflection: `UCLASS(editinlinenew, collapseCategories, Transient, MinimalAPI)`
- inherits: `UObject`
- desc: This is an editor-only representation of a query, designed to be editable with a typical property window. To edit a query in the editor, an FGameplayTagQuery is converted to a set of UObjects and edited,  When finished, the query struct is rewritten and these UObjects are discarded. This query representation is not intended for runtime use.
- L1000 _public member_ `FString UserDescription;` — `UPROPERTY(EditDefaultsOnly, Category = Query)` — User-supplied description, shown in property details. Auto-generated description is shown if not supplied.
- L1003 _public member_ `FString AutoDescription;` — Automatically-generated description
- L1007 _public member_ `TObjectPtr<class UEditableGameplayTagQueryExpression> RootExpression;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category = Query)` — The base expression of this query.
- L1011 _public prototype_ `void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString=nullptr) const;` — Converts this editor query construct into the runtime-usable token stream.
- L1014 _public prototype_ `FString GetTagQueryExportText(FGameplayTagQuery const& TagQuery);` — Generates and returns the export text for this query.
- L1020 _private member_ `FGameplayTagQuery TagQueryExportText_Helper;` — `UPROPERTY()` — Property to hold a gameplay tag query so we can use the exporttext path to get a string representation.

#### class `UEditableGameplayTagQueryExpression`  
`class UEditableGameplayTagQueryExpression : public UObject`  
_L1024-1037_
- reflection: `UCLASS(abstract, editinlinenew, collapseCategories, Transient, MinimalAPI)`
- inherits: `UObject`
- L1031 _public function_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString=nullptr) const` — Converts this editor query construct into the runtime-usable token stream.
- L1034 _protected prototype_ `void EmitTagTokens(FGameplayTagContainer const& TagsToEmit, TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString) const;`
- L1035 _protected prototype_ `void EmitExprListTokens(TArray<UEditableGameplayTagQueryExpression*> const& ExprList, TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString) const;`

#### class `UEditableGameplayTagQueryExpression_AnyTagsMatch`  
`class UEditableGameplayTagQueryExpression_AnyTagsMatch : public UEditableGameplayTagQueryExpression`  
_L1040-1050_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta=(DisplayName="Any Tags Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1045 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(EditDefaultsOnly, Category = Expr)`
- L1048 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_AllTagsMatch`  
`class UEditableGameplayTagQueryExpression_AllTagsMatch : public UEditableGameplayTagQueryExpression`  
_L1053-1063_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "All Tags Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1058 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(EditDefaultsOnly, Category = Expr)`
- L1061 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_NoTagsMatch`  
`class UEditableGameplayTagQueryExpression_NoTagsMatch : public UEditableGameplayTagQueryExpression`  
_L1066-1076_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "No Tags Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1071 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(EditDefaultsOnly, Category = Expr)`
- L1074 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_AnyTagsExactMatch`  
`class UEditableGameplayTagQueryExpression_AnyTagsExactMatch : public UEditableGameplayTagQueryExpression`  
_L1079-1089_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "Any Tags Exact Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1084 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(EditDefaultsOnly, Category = Expr)`
- L1087 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_AllTagsExactMatch`  
`class UEditableGameplayTagQueryExpression_AllTagsExactMatch : public UEditableGameplayTagQueryExpression`  
_L1092-1102_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "All Tags Exact Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1097 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(EditDefaultsOnly, Category = Expr)`
- L1100 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_AnyExprMatch`  
`class UEditableGameplayTagQueryExpression_AnyExprMatch : public UEditableGameplayTagQueryExpression`  
_L1105-1115_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "Any Expressions Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1110 _public member_ `TArray<TObjectPtr<UEditableGameplayTagQueryExpression>> Expressions;` — `UPROPERTY(EditAnywhere, Instanced, Category = Expr)`
- L1113 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_AllExprMatch`  
`class UEditableGameplayTagQueryExpression_AllExprMatch : public UEditableGameplayTagQueryExpression`  
_L1118-1128_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "All Expressions Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1123 _public member_ `TArray<TObjectPtr<UEditableGameplayTagQueryExpression>> Expressions;` — `UPROPERTY(EditAnywhere, Instanced, Category = Expr)`
- L1126 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### class `UEditableGameplayTagQueryExpression_NoExprMatch`  
`class UEditableGameplayTagQueryExpression_NoExprMatch : public UEditableGameplayTagQueryExpression`  
_L1131-1141_
- reflection: `UCLASS(BlueprintType, editinlinenew, collapseCategories, meta = (DisplayName = "No Expressions Match"))`
- inherits: `UEditableGameplayTagQueryExpression`
- L1136 _public member_ `TArray<TObjectPtr<UEditableGameplayTagQueryExpression>> Expressions;` — `UPROPERTY(EditAnywhere, Instanced, Category = Expr)`
- L1139 _public prototype_ `virtual void EmitTokens(TArray<uint8>& TokenStream, TArray<FGameplayTag>& TagDictionary, FString* DebugString = nullptr) const override;`

#### Free symbols / members of external scopes

- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayTags, Log, All);`
- L19 _delegate_ `DECLARE_STATS_GROUP(TEXT("Gameplay Tags"), STATGROUP_GameplayTags, STATC`
- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("FGameplayTagContainer::DoesTagContainerMatch"), STAT_FGameplayTagContainer_DoesTagContainerMatch`
- L33 _typedef_ `typedef uint16 FGameplayTagNetIndex;`
- L34 _macro_ `#define INVALID_TAGNETINDEX MAX_uint16`
- L168 _function_ `inline friend uint32 GetTypeHash(const FGameplayTag& Tag)` — Used so we can have a TMap of this struct
- L185 _function_ `friend FArchive& operator<<(FArchive& Ar, FGameplayTag& GameplayTag)`
- L190 _function_ `friend void operator<<(FStructuredArchive::FSlot Slot, FGameplayTag& GameplayTag)`
- L237 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90103`)
- L238 _enumerator_ `WithNetSharedSerialization = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90103`)
- L239 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90103`)
- L240 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90103`)
- L241 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90103`)
- L640 _function_ `inline friend TArray<FGameplayTag>::TConstIterator begin(const FGameplayTagContainer& Array)`
- L641 _function_ `inline friend TArray<FGameplayTag>::TConstIterator end(const FGameplayTagContainer& Array)`
- L658 _enumerator_ `WithStructuredSerializer = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L659 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L660 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L661 _enumerator_ `WithNetSharedSerialization = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L662 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L663 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L664 _enumerator_ `WithPostScriptConstruct = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90203`)
- L703 _namespace_ `namespace EGameplayTagQueryStreamVersion`
- L980 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon5bd5d6f90303`)

### `Source/Runtime/GameplayTags/Classes/GameplayTagsManager.h` (Public)


#### struct `FGameplayTagTableRow`  
`struct FGameplayTagTableRow : public FTableRowBase`  
_L38-60_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- desc: Simple struct for a table row in the gameplay tag table and element in the ini list
- L44 _public member_ `FName Tag;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GameplayTag)` — Tag specified in the table
- L48 _public member_ `FString DevComment;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GameplayTag)` — Developer comment clarifying the usage of a particular tag, not user facing
- L51 _public function_ `FGameplayTagTableRow()` — Constructors
- L52 _public function_ `FGameplayTagTableRow(FName InTag, const FString& InDevComment = TEXT("")) : Tag(InTag), DevComment(InDevComment)`
- L53 _public prototype_ `FGameplayTagTableRow(FGameplayTagTableRow const& Other);`
- L56 _public prototype_ `FGameplayTagTableRow& operator=(FGameplayTagTableRow const& Other);` — Assignment/Equality operators
- L57 _public prototype_ `bool operator==(FGameplayTagTableRow const& Other) const;`
- L58 _public prototype_ `bool operator!=(FGameplayTagTableRow const& Other) const;`
- L59 _public prototype_ `bool operator<(FGameplayTagTableRow const& Other) const;`

#### struct `FRestrictedGameplayTagTableRow`  
`struct FRestrictedGameplayTagTableRow : public FGameplayTagTableRow`  
_L64-81_
- reflection: `USTRUCT()`
- inherits: `FGameplayTagTableRow`
- desc: Simple struct for a table row in the restricted gameplay tag table and element in the ini list
- L70 _public member_ `bool bAllowNonRestrictedChildren;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayTag)` — Tag specified in the table
- L73 _public function_ `FRestrictedGameplayTagTableRow() : bAllowNonRestrictedChildren(false)` — Constructors
- L74 _public function_ `FRestrictedGameplayTagTableRow(FName InTag, const FString& InDevComment = TEXT(""), bool InAllowNonRestrictedChildren = false) : FGameplayTagTableRow(InTag, InDevComment), bAllowNonRestrictedChildren(InAllowNonRestrictedChildren)`
- L75 _public prototype_ `FRestrictedGameplayTagTableRow(FRestrictedGameplayTagTableRow const& Other);`
- L78 _public prototype_ `FRestrictedGameplayTagTableRow& operator=(FRestrictedGameplayTagTableRow const& Other);` — Assignment/Equality operators
- L79 _public prototype_ `bool operator==(FRestrictedGameplayTagTableRow const& Other) const;`
- L80 _public prototype_ `bool operator!=(FRestrictedGameplayTagTableRow const& Other) const;`

#### enum `EGameplayTagSourceType`  
`enum class EGameplayTagSourceType : uint8`  
_L84-92_
- reflection: `UENUM()`
- L86 _public enumerator_ `Native` — Was added from C++ code
- L87 _public enumerator_ `DefaultTagList` — The default tag list in DefaultGameplayTags.ini
- L88 _public enumerator_ `TagList` — Another tag list from an ini in tags/*.ini
- L89 _public enumerator_ `RestrictedTagList` — Restricted tags from an ini
- L90 _public enumerator_ `DataTable` — From a DataTable
- L91 _public enumerator_ `Invalid` — Not a real source

#### enum `EGameplayTagSelectionType`  
`enum class EGameplayTagSelectionType : uint8`  
_L97-103_
- reflection: `UENUM()`
- L99 _public enumerator_ `None`
- L100 _public enumerator_ `NonRestrictedOnly`
- L101 _public enumerator_ `RestrictedOnly`
- L102 _public enumerator_ `All`

#### struct `FGameplayTagSource`  
`struct FGameplayTagSource`  
_L107-151_
- reflection: `USTRUCT()`
- desc: Struct defining where gameplay tags are loaded/saved from. Mostly for the editor
- L113 _public member_ `FName SourceName;` — `UPROPERTY()` — Name of this source
- L117 _public member_ `EGameplayTagSourceType SourceType;` — `UPROPERTY()` — Type of this source
- L121 _public member_ `TObjectPtr<class UGameplayTagsList> SourceTagList;` — `UPROPERTY()` — If this is bound to an ini object for saving, this is the one
- L125 _public member_ `TObjectPtr<class URestrictedGameplayTagsList> SourceRestrictedTagList;` — `UPROPERTY()` — If this has restricted tags and is bound to an ini object for saving, this is the one
- L127 _public function_ `FGameplayTagSource() : SourceName(NAME_None), SourceType(EGameplayTagSourceType::Invalid), SourceTagList(nullptr), SourceRestrictedTagList(nullptr)`
- L132 _public function_ `FGameplayTagSource(FName InSourceName, EGameplayTagSourceType InSourceType, UGameplayTagsList* InSourceTagList = nullptr, URestrictedGameplayTagsList* InSourceRestrictedTagList = nullptr) : SourceName(InSourceName), SourceType(InSourceType), SourceTagList(InSourceTagList), SourceRestrictedTagList(InSourceRestrictedTagList)`
- L138 _public prototype_ `FString GetConfigFileName() const;` — Returns the config file that created this source, if valid
- L140 _public prototype_ `static FName GetNativeName();`
- L142 _public prototype_ `static FName GetDefaultName();`
- L145 _public prototype_ `static FName GetFavoriteName();`
- L147 _public prototype_ `static void SetFavoriteName(FName TagSourceToFavorite);`
- L149 _public prototype_ `static FName GetTransientEditorName();`

#### struct `FGameplayTagSearchPathInfo`  
`struct FGameplayTagSearchPathInfo`  
_L154-180_
- desc: Struct describing the places to look for ini search paths
- L157 _public member_ `TArray<FName> SourcesInPath;` — Which sources should be loaded from this path
- L160 _public member_ `TArray<FString> TagIniList;` — Config files to load from, will normally correspond to FoundSources
- L163 _public member_ `bool bWasSearched = false;` — True if this path has already been searched
- L166 _public member_ `bool bWasAddedToTree = false;` — True if the tags in sources have been added to the current tree
- L168 _public function_ `inline void Reset()`
- L176 _public function_ `inline bool IsValid()`

#### struct `FGameplayTagNode`  
`struct FGameplayTagNode`  
_L184-332_
- reflection: `USTRUCT()`
- desc: Simple tree node for gameplay tags, this stores metadata about specific tags
- L187 _public function_ `FGameplayTagNode()`
- L190 _public prototype_ `FGameplayTagNode(FName InTag, FName InFullTag, TSharedPtr<FGameplayTagNode> InParentNode, bool InIsExplicitTag, bool InIsRestrictedTag, bool InAllowNonRestrictedChildren);` — Simple constructor, passing redundant data for performance
- L193 _public function_ `inline const FGameplayTagContainer& GetSingleTagContainer() const` — Returns a correctly constructed container with only this tag, useful for doing container queries
- L200 _public function_ `inline const FGameplayTag& GetCompleteTag() const` — Get the complete tag for the node, including all parent tags, delimited by periods @return Complete tag for the node
- L201 _public function_ `inline FName GetCompleteTagName() const`
- L202 _public function_ `inline FString GetCompleteTagString() const`
- L209 _public function_ `inline FName GetSimpleTagName() const` — Get the simple tag for the node (doesn't include any parent tags) @return Simple tag for the node
- L216 _public function_ `inline TArray< TSharedPtr<FGameplayTagNode> >& GetChildTagNodes()` — Get the children nodes of this node @return Reference to the array of the children nodes of this node
- L223 _public function_ `inline const TArray< TSharedPtr<FGameplayTagNode> >& GetChildTagNodes() const` — Get the children nodes of this node @return Reference to the array of the children nodes of this node
- L230 _public function_ `inline TSharedPtr<FGameplayTagNode> GetParentTagNode() const` — Get the parent tag node of this node @return The parent tag node of this node
- L237 _public function_ `inline FGameplayTagNetIndex GetNetIndex() const` — Get the net index of this node @return The net index of this node
- L240 _public prototype_ `void ResetNode();` — Reset the node of all of its values
- L243 _public function_ `inline bool IsExplicitTag() const` — Returns true if the tag was explicitly specified in code or data
- L252 _public function_ `inline bool GetAllowNonRestrictedChildren() const` — Returns true if the tag is a restricted tag and allows non-restricted children
- L261 _public function_ `inline bool IsRestrictedGameplayTag() const` — Returns true if the tag is a restricted tag
- L270 _public function_ `FName GetFirstSourceName() const`
- L271 _public function_ `const TArray<FName>& GetAllSourceNames() const`
- L276 _public function_ `FString GetDevComment() const` — Returns the Comment for this tag
- L284 _public prototype_ `void Hash(FBlake3& Hasher);` — Update the hasher with a deterministic hash of the data on this. Used for e.g. IncrementalCook keys. Does not include data from this node's child or parent nodes.
- L289 _private member_ `FName Tag;` — Raw name for this tag at current rank in the tree
- L292 _private member_ `FGameplayTagContainer CompleteTagWithParents;` — This complete tag is at GameplayTags[0], with parents in ParentTags[]
- L295 _private member_ `TArray< TSharedPtr<FGameplayTagNode> > ChildTags;` — Child gameplay tag nodes
- L298 _private member_ `TSharedPtr<FGameplayTagNode> ParentNode;` — Owner gameplay tag node, if any
- L301 _private member_ `FGameplayTagNetIndex NetIndex;` — Net Index of this node
- L305 _private member_ `TArray<FName> SourceNames;` — Module or Package or config file this tag came from. If empty this is an implicitly added tag
- L308 _private member_ `FString DevComment;` — Comment for this tag
- L311 _private member_ `uint8 bIsRestrictedTag : 1;` — If this is true then the tag can only have normal tag children if bAllowNonRestrictedChildren is true
- L314 _private member_ `uint8 bAllowNonRestrictedChildren : 1;` — If this is true then any children of this tag must come from the restricted tags
- L317 _private member_ `uint8 bIsExplicitTag : 1;` — If this is true then the tag was explicitly added and not only implied by its child tags
- L320 _private member_ `uint8 bDescendantHasConflict : 1;` — If this is true then at least one tag that inherits from this tag is coming from multiple sources. Used for updating UI in the editor.
- L323 _private member_ `uint8 bNodeHasConflict : 1;` — If this is true then this tag is coming from multiple sources. No descendants can be changed on this tag until this is resolved.
- L326 _private member_ `uint8 bAncestorHasConflict : 1;` — If this is true then at least one tag that this tag descends from is coming from multiple sources. This tag and it's descendants can't be changed in the editor.

#### class `UGameplayTagsManager`  
`class UGameplayTagsManager : public UObject`  
_L336-1057_
- reflection: `UCLASS(config=Engine, MinimalAPI)`
- inherits: `UObject`
- desc: Holds data about the tag dictionary, is in a singleton UObject
- L341 _private prototype_ `~UGameplayTagsManager();` — Destructor
- L344 _private function_ `inline static UGameplayTagsManager& Get()` — Returns the global UGameplayTagsManager manager
- L355 _private function_ `inline static UGameplayTagsManager* GetIfAllocated()` — Returns possibly nullptr to the manager. Needed for some shutdown cases to avoid reallocating.
- L365 _private prototype_ `void RequestGameplayTagContainer(const TArray<FString>& TagStrings, FGameplayTagContainer& OutTagsContainer, bool bErrorIfNotFound=true) const;` — Adds the gameplay tags corresponding to the strings in the array TagStrings to OutTagsContainer @param TagStrings Array of strings to search for as tags to add to the tag container @param OutTagsContainer Container to add the found tags to. @param ErrorIfNotfound: ensure() that tags exists.
- L375 _private prototype_ `FGameplayTag RequestGameplayTag(FName TagName, bool ErrorIfNotFound=true) const;` — Gets the FGameplayTag that corresponds to the TagName @param TagName The Name of the tag to search for @param ErrorIfNotfound: ensure() that tag exists. @return Will return the corresponding FGameplayTag or an empty one if not found.
- L384 _private prototype_ `bool IsValidGameplayTagString(const TCHAR* TagString, FText* OutError = nullptr, FString* OutFixedString = nullptr);` — Returns true if this is a valid gameplay tag string (foo.bar.baz). If false, it will fill @param TagString String to check for validity @param OutError If non-null and string invalid, will fill in with an error message @param OutFixedString If non-null and string invalid, will attempt to fix. Will be empty if no fix is possible @return True if this can be added to the tag dictionary, false if there's a syntax error
- L385 _private prototype_ `bool IsValidGameplayTagString(const FString& TagString, FText* OutError = nullptr, FString* OutFixedString = nullptr);`
- L386 _private prototype_ `bool IsValidGameplayTagString(const FStringView& TagString, FText* OutError = nullptr, FStringBuilderBase* OutFixedString = nullptr);`
- L392 _private prototype_ `FGameplayTag FindGameplayTagFromPartialString_Slow(FString PartialString) const;` — Searches for a gameplay tag given a partial string. This is slow and intended mainly for console commands/utilities to make developer life's easier. This will attempt to match as best as it can. If you pass "A.b" it will match on "A.b." before it matches "a.b.c".
- L403 _private prototype_ `FGameplayTag AddNativeGameplayTag(FName TagName, const FString& TagDevComment = TEXT("(Nat` — Registers the given name as a gameplay tag, and tracks that it is being directly referenced from code This can be called after initial engine startup but can invalidate FastReplication @param TagName The Name of the tag to add @param TagDevComment The developer comment clarifying the usage of the tag @return Will return the corresponding FGameplayTag
- L407 _private prototype_ `void AddNativeGameplayTag(FNativeGameplayTag* TagSource);` — Only callable from FNativeGameplayTag, these functions do less error checking and can happen after initial tag loading is done
- L408 _private prototype_ `void RemoveNativeGameplayTag(const FNativeGameplayTag* TagSource);`
- L412 _public prototype_ `void DoneAddingNativeTags();` — Call to flush the list of native tags, once called it is unsafe to add more
- L416 _public prototype_ `static FSimpleMulticastDelegate& OnLastChanceToAddNativeTags();` — `UE_DEPRECATED(5.8, "Replace with CallOrRegister_OnAddNativeTagsDelegate or call AddNativeGameplayTag directly, tags can be safely added after startup with default settings")` — This is a delegate that is called during initialization/initial loading and signals the last chance to add tags before we are considered to be fully loaded (all tags registered).
- L422 _public prototype_ `static FDelegateHandle CallOrRegister_OnAddNativeTagsDelegate(const FSimpleMulticastDelegate::FDelegate& Delegate);` — Register a callback for initialization to add additional native tags right before fully initializing gameplay tags. Or, if the startup native tags have already been added, execute Delegate before the end of the current module load.
- L429 _public prototype_ `static FDelegateHandle CallOrRegister_OnDoneAddingNativeTagsDelegate(const FSimpleMulticastDelegate::FDelegate& Delegate);` — Register a callback for when native tags are done being added (this is also a safe point to consider that the gameplay tags have fully been initialized). Or, if the native tags have already been added (and thus we have registered all valid tags), then execute this Delegate immediately. This is useful if your code is potentially executed during load time, and therefore any tags in your block of code could be not-yet-loaded, but possibly valid after being loaded.
- L435 _public prototype_ `static void UnregisterNativeTagDelegate(FDelegateHandle DelegateHandle);` — Unregisters a previously registered callback from either OnAddNativeTagsDelegate or OnDoneAddingNativeTagsDelegate. If the delegate has already activated or the handle is empty this will do nothing.
- L446 _public prototype_ `FGameplayTagContainer RequestGameplayTagParents(const FGameplayTag& GameplayTag) const;` — Gets a Tag Container containing the supplied tag and all of its parents as explicit tags. For example, passing in x.y.z would return a tag container with x.y.z, x.y, and x. This will only work for tags that have been properly registered. @param GameplayTag The tag to use at the child most tag for this container @return A tag container with the supplied tag and all its parents added explicitly, or an empty container if that failed
- L458 _public prototype_ `bool ExtractParentTags(const FGameplayTag& GameplayTag, TArray<FGameplayTag>& UniqueParentTags) const;` — Fills in an array of gameplay tags with all of tags that are the parents of the passed in tag. For example, passing in x.y.z would add x.y and x to UniqueParentTags if they was not already there. This is used by the GameplayTagContainer code and may work for unregistered tags depending on serialization settings. @param GameplayTag The gameplay tag to extract parent tags from @param UniqueParentTags A list of parent tags that will be added to if necessary @return true if any tags were added to UniqueParentTags
- L467 _public prototype_ `FGameplayTagContainer RequestGameplayTagChildren(const FGameplayTag& GameplayTag) const;` — Gets a Tag Container containing the all tags in the hierarchy that are children of this tag. Does not return the original tag @param GameplayTag					The Tag to use at the parent tag @return A Tag Container with the supplied tag and all its parents added explicitly
- L470 _public prototype_ `FGameplayTag RequestGameplayTagDirectParent(const FGameplayTag& GameplayTag) const;` — Returns direct parent GameplayTag of this GameplayTag, calling on x.y will return x
- L473 _public function_ `inline const FGameplayTagContainer* GetSingleTagContainer(const FGameplayTag& GameplayTag) const` — `UE_DEPRECATED(5.4, "This function is not threadsafe, use FindTagNode or FGameplayTag::GetSingleTagContainer")`
- L485 _public function_ `inline TSharedPtr<FGameplayTagNode> FindTagNode(const FGameplayTag& GameplayTag) const` — Checks node tree to see if a FGameplayTagNode with the tag exists @param TagName	The name of the tag node to search for @return A shared pointer to the FGameplayTagNode found, or NULL if not found.
- L521 _public function_ `inline TSharedPtr<FGameplayTagNode> FindTagNode(FName TagName) const` — Checks node tree to see if a FGameplayTagNode with the name exists @param TagName	The name of the tag node to search for @return A shared pointer to the FGameplayTagNode found, or NULL if not found.
- L528 _public prototype_ `void LoadGameplayTagTables(bool bAllowAsyncLoad = false);` — Loads the tag tables referenced in the GameplayTagSettings object
- L531 _public prototype_ `void AddTagIniSearchPath(const FString& RootDir, const TSet<FString>* PluginConfigsCache = nullptr);` — Loads tag inis contained in the specified path, passes an optional PluginConfigCache to speed up disk searches
- L534 _public prototype_ `bool RemoveTagIniSearchPath(const FString& RootDir);` — Tries to remove the specified search path, will return true if anything was removed
- L537 _public prototype_ `void GetTagSourceSearchPaths(TArray<FString>& OutPaths);` — Gets all the current directories to look for tag sources in
- L540 _public prototype_ `int32 GetNumTagSourceSearchPaths();` — Gets the number of tag source search paths
- L543 _public prototype_ `void ConstructGameplayTagTree();` — Helper function to construct the gameplay tag tree
- L546 _public prototype_ `void DestroyGameplayTagTree();` — Helper function to destroy the gameplay tag tree
- L549 _public prototype_ `void SplitGameplayTagFName(const FGameplayTag& Tag, TArray<FName>& OutNames) const;` — Splits a tag such as x.y.z into an array of names {x,y,z}
- L552 _public prototype_ `void RequestAllGameplayTags(FGameplayTagContainer& TagContainer, bool OnlyIncludeDictionaryTags) const;` — Gets the list of all registered tags, setting OnlyIncludeDictionaryTags will exclude implicitly added tags if possible
- L555 _public prototype_ `bool ValidateTagCreation(FName TagName) const;` — Returns true if if the passed in name is in the tag dictionary and can be created
- L558 _public prototype_ `const FGameplayTagSource* FindTagSource(FName TagSourceName) const;` — Returns the tag source for a given tag source name and type, or null if not found
- L561 _public prototype_ `FGameplayTagSource* FindTagSource(FName TagSourceName);` — Returns the tag source for a given tag source name and type, or null if not found
- L564 _public prototype_ `void FindTagSourcesWithType(EGameplayTagSourceType TagSourceType, TArray<const FGameplayTagSource*>& OutArray) const;` — Fills in an array with all tag sources of a specific type
- L566 _public prototype_ `void FindTagsWithSource(FStringView PackageNameOrPath, TArray<FGameplayTag>& OutTags) const;`
- L576 _public prototype_ `int32 GameplayTagsMatchDepth(const FGameplayTag& GameplayTagOne, const FGameplayTag& GameplayTagTwo) const;` — Check to see how closely two FGameplayTags match. Higher values indicate more matching terms in the tags. @param GameplayTagOne	The first tag to compare @param GameplayTagTwo	The second tag to compare @return the length of the longest matching pair
- L582 _public prototype_ `int32 GetNumberOfTagNodes(const FGameplayTag& GameplayTag) const;` — Returns the number of parents a particular gameplay tag has.  Useful as a quick way to determine which tags may be more "specific" than other tags without comparing whether they are in the same hierarchy or anything else. Example: "TagA.SubTagA" has 2 Tag Nodes.  "TagA.SubTagA.LeafTagA" has 3 Tag Nodes.
- L585 _public prototype_ `bool ShouldImportTagsFromINI() const;` — Returns true if we should import tags from UGameplayTagsSettings objects (configured by INI files)
- L588 _public function_ `bool ShouldWarnOnInvalidTags() const` — Should we print loading errors when trying to load invalid tags
- L595 _public function_ `bool ShouldClearInvalidTags() const` — `UE_DEPRECATED(5.5, "We should never clear invalid tags as we're not guaranteed the required plugin has loaded")` — Should we clear references to invalid tags loaded/saved in the editor
- L601 _public function_ `bool ShouldUseFastReplication() const` — Should use fast replication
- L607 _public function_ `bool ShouldUseDynamicReplication() const` — Should use dynamic replication (Gameplay Tags need not match between client/server)
- L613 _public prototype_ `bool ShouldUnloadTags() const;` — If we are allowed to unload tags
- L616 _public prototype_ `void SetShouldUnloadTagsOverride(bool bShouldUnloadTags);` — Pushes an override that supersedes bShouldAllowUnloadingTags to allow/disallow unloading of GameplayTags in controlled scenarios
- L619 _public prototype_ `void ClearShouldUnloadTagsOverride();` — Clears runtime overrides, reverting to bShouldAllowUnloadingTags when determining GameplayTags unload behavior
- L622 _public prototype_ `void SetShouldDeferGameplayTagTreeRebuilds(bool bShouldDeferRebuilds);` — Pushes an override that suppresses calls to HandleGameplayTagTreeChanged that would result in a complete rebuild of the GameplayTag tree
- L625 _public prototype_ `void ClearShouldDeferGameplayTagTreeRebuilds(bool bRebuildTree);` — Stops suppressing GameplayTag tree rebuilds and (optionally) rebuilds the tree
- L628 _public prototype_ `void PushDeferOnGameplayTagTreeChangedBroadcast();` — Temporarily disables IGameplayTagsModule::OnGameplayTagTreeChanged callback for changes to the gameplay tag tree. This does not stop it from actually rebuilding the tree
- L631 _public prototype_ `void PopDeferOnGameplayTagTreeChangedBroadcast();` — Re-enables OnGameplayTagTreeChanged callbacks, there must be one call to this function for every Push. This will execute callbacks immediately if they were deferred
- L634 _public function_ `uint32 GetNetworkGameplayTagNodeIndexHash() const` — Returns the hash of NetworkGameplayTagNodeIndex
- L637 _public prototype_ `void GetRestrictedTagConfigFiles(TArray<FString>& RestrictedConfigFiles) const;` — Returns a list of the ini files that contain restricted tags
- L640 _public prototype_ `void GetRestrictedTagSources(TArray<const FGameplayTagSource*>& Sources) const;` — Returns a list of the source files that contain restricted tags
- L643 _public prototype_ `void GetOwnersForTagSource(const FString& SourceName, TArray<FString>& OutOwners) const;` — Returns a list of the owners for a restricted tag config file. May be empty
- L646 _public prototype_ `void GameplayTagContainerLoaded(FGameplayTagContainer& Container, FProperty* SerializingProperty) const;` — Notification that a tag container has been loaded via serialize
- L649 _public prototype_ `void SingleGameplayTagLoaded(FGameplayTag& Tag, FProperty* SerializingProperty) const;` — Notification that a gameplay tag has been loaded via serialize
- L652 _public prototype_ `void RedirectTagsForContainer(FGameplayTagContainer& Container, FProperty* SerializingProperty) const;` — Handles redirectors for an entire container, will also error on invalid tags
- L655 _public prototype_ `void RedirectSingleGameplayTag(FGameplayTag& Tag, FProperty* SerializingProperty) const;` — Handles redirectors for a single tag, will also error on invalid tag. This is only called for when individual tags are serialized on their own
- L658 _public prototype_ `bool ImportSingleGameplayTag(FGameplayTag& Tag, FName ImportedTagName, bool bImportFromSerialize = false) const;` — Handles establishing a single tag from an imported tag name (accounts for redirects too). Called when tags are imported via text.
- L661 _public prototype_ `FName GetTagNameFromNetIndex(FGameplayTagNetIndex Index) const;` — Gets a tag name from net index and vice versa, used for replication efficiency
- L662 _public prototype_ `FGameplayTagNetIndex GetNetIndexFromTag(const FGameplayTag &InTag) const;`
- L665 _public function_ `int32 GetNetIndexTrueBitNum() const` — Cached number of bits we need to replicate tags. That is, Log2(Number of Tags). Will always be <= 16.
- L668 _public function_ `int32 GetNetIndexFirstBitSegment() const` — The length in bits of the first segment when net serializing tags. We will serialize NetIndexFirstBitSegment + 1 bit to indicatore "more" (more = second segment that is NetIndexTrueBitNum - NetIndexFirstBitSegment)
- L671 _public function_ `FGameplayTagNetIndex GetInvalidTagNetIndex() const` — This is the actual value for an invalid tag "None". This is computed at runtime as (Total number of tags) + 1
- L673 _public function_ `const TArray<TSharedPtr<FGameplayTagNode>>& GetNetworkGameplayTagNodeIndex() const`
- L675 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnGameplayTagLoaded, const FGameplayTag& ) FOnGameplayTagLoaded OnGameplayTagLoadedDelegate;`
- L679 _public member_ `int32 NumBitsForContainerSize;` — Numbers of bits to use for replicating container size. This can be set via config.
- L683 _private member_ `int32 NetIndexTrueBitNum;` — Cached number of bits we need to replicate tags. That is, Log2(Number of Tags). Will always be <= 16.
- L686 _private member_ `int32 NetIndexFirstBitSegment;` — The length in bits of the first segment when net serializing tags. We will serialize NetIndexFirstBitSegment + 1 bit to indicatore "more" (more = second segment that is NetIndexTrueBitNum - NetIndexFirstBitSegment)
- L689 _private member_ `FGameplayTagNetIndex InvalidTagNetIndex;` — This is the actual value for an invalid tag "None". This is computed at runtime as (Total number of tags) + 1
- L695 _public prototype_ `void GetFilteredGameplayRootTags(const FString& InFilterString, TArray< TSharedPtr<FGameplayTagNode> >& OutTagArray) const;` — Gets a Filtered copy of the GameplayRootTags Array based on the comma delimited filter string passed in
- L698 _public prototype_ `FString GetCategoriesMetaFromPropertyHandle(TSharedPtr<class IPropertyHandle> PropertyHandle) const;` — Returns "Categories" meta property from given handle, used for filtering by tag widget
- L701 _public prototype_ `static FString StaticGetCategoriesMetaFromPropertyHandle(TSharedPtr<class IPropertyHandle> PropertyHandle);` — Helper function, made to be called by custom OnGetCategoriesMetaFromPropertyHandle handlers
- L705 _public function_ `template <typename TFieldType> static FString GetCategoriesMetaFromField(TFieldType* Field)` — Returns "Categories" meta property from given field, used for filtering by tag widget
- L720 _public prototype_ `static FString GetCategoriesMetaFromFunction(const UFunction* Func, FName ParamName = NAME_None);` — Returns "GameplayTagFilter" meta property from given function, used for filtering by tag widget for any parameters of the function that end up as BP pins
- L723 _public prototype_ `void GetAllTagsFromSource(FName TagSource, TArray< TSharedPtr<FGameplayTagNode> >& OutTagArray) const;` — Gets a list of all gameplay tag nodes added by the specific source
- L726 _public prototype_ `bool IsDictionaryTag(FName TagName) const;` — Returns true if this tag was explicitly registered, this is false for implictly added parent tags
- L729 _public prototype_ `bool GetTagEditorData(FName TagName, FString& OutComment, FName &OutFirstTagSource, bool& bOutIsTagExplicit, bool &bOutIsRestrictedTag, bool &bOutAllowNonRestrictedChildren) const;` — Returns information about tag. If not found return false
- L732 _public prototype_ `bool GetTagEditorData(FName TagName, FString& OutComment, TArray<FName>& OutTagSources, bool& bOutIsTagExplicit, bool &bOutIsRestrictedTag, bool &bOutAllowNonRestrictedChildren) const;` — Returns information about tag. If not found return false
- L738 _public member_ `static FSimpleMulticastDelegate OnEditorRefreshGameplayTagTree;` — This is called after EditorRefreshGameplayTagTree. Useful if you need to do anything editor related when the gameplay tag tree is destroyed and recreated. IGameplayTagsModule::OnGameplayTagTreeChanged is called first and will happen when any tags are added or removed, not just when the settings are fully refreshed.
- L741 _public prototype_ `void EditorRefreshGameplayTagTree();` — Refresh the gameplaytag tree due to an editor change
- L744 _public prototype_ `void SuspendEditorRefreshGameplayTagTree(FGuid SuspendToken);` — Suspends EditorRefreshGameplayTagTree requests
- L747 _public prototype_ `void ResumeEditorRefreshGameplayTagTree(FGuid SuspendToken);` — Resumes EditorRefreshGameplayTagTree requests; triggers a refresh if a request was made while it was suspended
- L750 _public prototype_ `FGameplayTagContainer RequestGameplayTagChildrenInDictionary(const FGameplayTag& GameplayTag) const;` — Gets a Tag Container containing all of the tags in the hierarchy that are children of this tag, and were explicitly added to the dictionary
- L753 _public prototype_ `FGameplayTagContainer RequestGameplayTagDirectDescendantsInDictionary(const FGameplayTag& GameplayTag, EGameplayTagSelectionType SelectionType) const;` — Gets a Tag Container containing all of the tags in the hierarchy that are children of this tag, were explicitly added to the dictionary, and do not have any explicitly added tags between them and the specified tag
- L757 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayTagDoubleClickedEditor, FGameplayTag, FSimpleMulticastDelegate& ) FOnGameplayTagDoubleClickedEditor OnGatherGameplayTagDoubleClickedEditor;`
- L761 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetCategoriesMetaFromPropertyHandle, TSharedPtr<IPropertyHandle>, FString& ) FOnGetCategoriesMetaFromPropertyHandle OnGetCategoriesMetaFromPropertyHandle;` — Chance to dynamically change filter string based on a property handle
- L765 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFilterGameplayTagChildren, const FString& , TSharedPtr<FGameplayTagNode>& , bool& ) FOnFilterGameplayTagChildren OnFilterGameplayTagChildren;` — Allows dynamic hiding of gameplay tags in SGameplayTagWidget. Allows higher order structs to dynamically change which tags are visible based on its own data
- L794 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFilterGameplayTag, const FFilterGameplayTagContext& , bool& ) FOnFilterGameplayTag OnFilterGameplayTag;` — Allows dynamic hiding of gameplay tags in SGameplayTagWidget. Allows higher order structs to dynamically change which tags are visible based on its own data Applies to all tags, and has more context than OnFilterGameplayTagChildren
- L797 _public prototype_ `void NotifyGameplayTagDoubleClickedEditor(FString TagName);`
- L799 _public prototype_ `bool ShowGameplayTagAsHyperLinkEditor(FString TagName);`
- L807 _public prototype_ `UE::Cook::FCookDependency CreateCookDependency(const FGameplayTag& Tag) const;` — Used for incremental cooking. Create an FCookDependency for a gameplay tag. Packages that pass this dependency to AddCookLoadDependency or AddCookSaveDependency in their OnCookEvent or (if Ar.IsCooking()) Serialize function will be invalidated and recooked by the incremental cook whenever those tags change.
- L809 _public prototype_ `void AppendDependencyHash(const FName& TagName, FBlake3& OutHasher) const;`
- L812 _public prototype_ `void DumpSources(FOutputDevice& Out) const;` — Implementation of console command GameplayTags.DumpSources
- L815 _public prototype_ `void PrintReplicationIndices();`
- L816 _public function_ `int32 GetNumGameplayTagNodes() const`
- L821 _public prototype_ `void PrintReplicationFrequencyReport();`
- L822 _public prototype_ `void NotifyTagReplicated(FGameplayTag Tag, bool WasInContainer);`
- L824 _public member_ `TMap<FGameplayTag, int32> ReplicationCountMap;`
- L825 _public member_ `TMap<FGameplayTag, int32> ReplicationCountMap_SingleTags;`
- L826 _public member_ `TMap<FGameplayTag, int32> ReplicationCountMap_Containers;`
- L832 _private prototype_ `static void InitializeManager();` — Initializes the manager
- L835 _private prototype_ `static FSimpleMulticastDelegate& OnDoneAddingNativeTagsDelegate();` — finished loading/adding native tags
- L838 _private member_ `static UGameplayTagsManager* SingletonManager;` — The Tag Manager singleton
- L854 _private function_ `inline const FGameplayTagContainer* GetSingleTagContainerPtr(const FGameplayTag& GameplayTag) const` — Helper function to get the stored TagContainer containing only this tag, which has searchable ParentTags NOTE: This function is not threadsafe and should only be used in code that locks the tag map critical section @param GameplayTag		Tag to get single container of @return					Pointer to container with this tag
- L898 _private prototype_ `int32 InsertTagIntoNodeArray(FName Tag, FName FullTag, TSharedPtr<FGameplayTagNode> ParentNode, TArray< TSharedPtr<FGameplayTagNode> >& NodeArray, FName SourceName, const FString& DevComment, bool bIsExplicitTag, bool bIsRestrictedTag, bool bAllowNonRestrictedChildren);` — Helper function to insert a tag into a tag node array @param Tag							Short name of tag to insert @param FullTag						Full tag, passed in for performance @param ParentNode					Parent node, if any, for the tag @param NodeArray						Node array to insert the new node into, if necessary (if the tag already exists, no insertion will occur) @param SourceName					File tag was added from @param DevComment					Comment from developer about this tag @param bIsExplicitTag				Is the tag explicitly defined or is it implied by the existence of a child tag @param bIsRestrictedTag				Is the tag a restricted tag or a regular gameplay tag @param bAllowNonRestrictedChildren	If the tag is a restricted tag, can it have regular gameplay tag children or should all of its children be restricted tags as well? @return Index of the node of the tag
- L901 _private prototype_ `void PopulateTreeFromDataTable(class UDataTable* Table);` — Helper function to populate the tag tree from each table
- L903 _private prototype_ `void AddTagTableRow(const FGameplayTagTableRow& TagRow, FName SourceName, bool bIsRestrictedTag = false);`
- L905 _private prototype_ `void AddChildrenTags(FGameplayTagContainer& TagContainer, TSharedPtr<FGameplayTagNode> GameplayTagNode, bool RecurseAll=true, bool OnlyIncludeDictionaryTags=false) const;`
- L907 _private prototype_ `void AddRestrictedGameplayTagSource(const FString& FileName);`
- L909 _private prototype_ `void AddTagsFromAdditionalLooseIniFiles(const TArray<FString>& IniFileList);`
- L918 _private prototype_ `void GetAllParentNodeNames(TSet<FName>& NamesList, TSharedPtr<FGameplayTagNode> GameplayTag) const;` — Helper function for GameplayTagsMatch to get all parents when doing a parent match, NOTE: Must never be made public as it uses the FNames which should never be exposed @param NameList		The list we are adding all parent complete names too @param GameplayTag	The current Tag we are adding to the list
- L921 _private prototype_ `FGameplayTagSource* FindOrAddTagSource(FName TagSourceName, EGameplayTagSourceType SourceType, const FString& RootDirToUse = FString());` — Returns the tag source for a given tag source name, or null if not found
- L924 _private prototype_ `void ConstructNetIndex();` — Constructs the net indices for each tag
- L927 _private prototype_ `void MarkChildrenOfNodeConflict(TSharedPtr<FGameplayTagNode> CurNode);` — Marks all of the nodes that descend from CurNode as having an ancestor node that has a source conflict.
- L929 _private function_ `void VerifyNetworkIndex() const`
- L941 _private function_ `void InvalidateNetworkIndex()`
- L944 _private prototype_ `void BroadcastOnGameplayTagTreeChanged();` — Called in both editor and game when the tag tree changes during startup or editing
- L947 _private prototype_ `void HandleGameplayTagTreeChanged(bool bRecreateTree);` — Call after modifying the tag tree nodes, this will either call the full editor refresh or a limited game refresh
- L950 _private prototype_ `void HandleModuleObjectsLoaded(FName InModuleName, bool bCanProcessNewlyLoadedObjects);` — Handles pending tag changes
- L953 _private prototype_ `void PushDeferGameplayTagTreeRebuilds();` — Temporarily disables any game or editor rebuilds of the gameplay tag tree, this should only be used when making multiple tag changes at once
- L956 _private prototype_ `void PopDeferGameplayTagTreeRebuilds();` — Re-enables game and editor rebuilds of the gameplay tag tree, there must be one call to this function for every Push. This will rebuild the tree immediately if it was deferred
- L960 _private prototype_ `GameplayTagUtil::FGameplayTagCookDependency CreateGameplayTagCookDependency(const FGameplayTag& Tag) const;`
- L962 _private prototype_ `void ValidateGameplayTagCookDependencies(const FCbFieldViewIterator& Args, UE::Cook::FCookDependencyContext& Context) const;`
- L969 _private member_ `TSet<FName> LegacyNativeTags;` — These are the old native tags that use to be resisted via a function call with no specific site/ownership.
- L972 _private member_ `TMap<FString, FGameplayTagSearchPathInfo> RegisteredSearchPaths;` — Map of all config directories to load tag inis from
- L975 _private member_ `TSharedPtr<FGameplayTagNode> GameplayRootTag;` — Roots of gameplay tag nodes
- L978 _private member_ `TMap<FGameplayTag, TSharedPtr<FGameplayTagNode>> GameplayTagNodeMap;` — Map of Tags to Nodes - Internal use only. FGameplayTag is inside node structure, do not use FindKey!
- L981 _private member_ `TArray<FGameplayTag> CommonlyReplicatedTags;` — Our aggregated, sorted list of commonly replicated tags. These tags are given lower indices to ensure they replicate in the first bit segment.
- L985 _private member_ `TMap<FName, FGameplayTagSource> TagSources;` — `UPROPERTY()` — Map of gameplay tag source names to source objects
- L987 _private member_ `TSet<FName> RestrictedGameplayTagSourceNames;`
- L989 _private member_ `bool bIsConstructingGameplayTagTree = false;`
- L992 _private member_ `bool bUseFastReplication;` — Cached runtime value for whether we are using fast replication or not. Initialized from config setting.
- L995 _private member_ `bool bUseDynamicReplication;` — Cached runtime value for whether we are using dynamic replication or not. Initialized from the config setting.
- L998 _private member_ `bool bShouldWarnOnInvalidTags;` — Cached runtime value for whether we should warn when loading invalid tags
- L1001 _private member_ `bool bShouldAllowUnloadingTags;` — Cached runtime value for whether we should allow unloading of tags
- L1004 _private member_ `TOptional<bool> ShouldAllowUnloadingTagsOverride;` — Augments usage of bShouldAllowUnloadingTags to allow runtime overrides to allow/disallow unloading of GameplayTags in controlled scenarios
- L1007 _private member_ `TOptional<bool> ShouldDeferGameplayTagTreeRebuilds;` — Used to suppress calls to HandleGameplayTagTreeChanged that would result in a complete rebuild of the GameplayTag tree
- L1010 _private member_ `FDelegateHandle HandleModuleObjectsLoadedHandle;` — Used for HandleModuleObjectsLoaded
- L1013 _private member_ `bool bDoneAddingNativeTags;` — True if native tags have all been added and flushed
- L1016 _private member_ `int32 DeferBroadcastOnGameplayTagTreeChanged = 0;` — Used to suppress calls to BroadcastOnGameplayTagTreeChanged
- L1017 _private member_ `bool bBroadcastOnGameplayTagTreeChangedWasDeferred = false;`
- L1020 _private member_ `int32 DeferGameplayTagTreeRebuilds = 0;` — Used to suppress calls to HandleGameplayTagTreeChanged that would result in a complete rebuild of the GameplayTag tree
- L1021 _private member_ `bool bGameplayTagTreeRebuildWasDeferred = false;`
- L1024 _private member_ `bool bNeedsTreeRebuildOnDoneAddingGameplayTags = false;` — If true, an action that would require a tree rebuild was performed during initialization
- L1027 _private member_ `FString InvalidTagCharacters;` — String with outlawed characters inside tags
- L1031 _private member_ `mutable FTransactionallySafeCriticalSection GameplayTagMapCritical;` — This critical section is to handle an issue where tag requests come from another thread when async loading from a background thread in FGameplayTagContainer::Serialize. This class is not generically threadsafe, but this should be locked by any operation that could update something read by a background thread.
- L1035 _private member_ `TSet<FName> TransientEditorTags;` — Transient editor-only tags to support quick-iteration PIE workflows
- L1037 _private member_ `FBlake3Hash IncrementalCookHash;`
- L1041 _private member_ `TArray<TSharedPtr<FGameplayTagNode>> NetworkGameplayTagNodeIndex;` — Sorted list of nodes, used for network replication
- L1043 _private member_ `uint32 NetworkGameplayTagNodeIndexHash;`
- L1045 _private member_ `bool bNetworkIndexInvalidated = true;`
- L1049 _private member_ `TArray<TObjectPtr<UDataTable>> GameplayTagTables;` — `UPROPERTY()` — Holds all of the valid gameplay-related tags that can be applied to assets
- L1051 _private member_ `const static FName NAME_Categories;`
- L1052 _private member_ `const static FName NAME_GameplayTagFilter;`
- L1056 _private member_ `mutable TLruCache<FGameplayTag, FGameplayTagContainer> ChildNodesCache;`

#### struct `UGameplayTagsManager::FFilterGameplayTagContext`  
`struct FFilterGameplayTagContext`  
_L773-788_
- desc: This is a container to filter out gameplay tags when they are invalid or when they don't meet the filter string If used from editor to filter out tags when picking them the FilterString is optional and the ReferencingPropertyHandle is required If used to validate an asset / assets you can provide the TagSourceAssets. The FilterString and ReferencingPropertyHandle is optional
- L775 _public member_ `const FString& FilterString;`
- L776 _public member_ `const TSharedPtr<FGameplayTagNode>& TagNode;`
- L777 _public member_ `const FGameplayTagSource* TagSource;`
- L778 _public member_ `const TSharedPtr<IPropertyHandle> ReferencingPropertyHandle;`
- L779 _public member_ `const TArray<FAssetData> TagSourceAssets;`
- L781 _public function_ `FFilterGameplayTagContext(const FString& InFilterString, const TSharedPtr<FGameplayTagNode>& InTagNode, const FGameplayTagSource* InTagSource, const TSharedPtr<IPropertyHandle>& InReferencingPropertyHandle) : FilterString(InFilterString), TagNode(InTagNode), TagSource(InTagSource), ReferencingPropertyHandle(InReferencingPropertyHandle)`
- L785 _public function_ `FFilterGameplayTagContext(const TSharedPtr<FGameplayTagNode>& InTagNode, const FGameplayTagSource* InTagSource, const TArray<FAssetData>& InTagSourceAssets, const FString& InFilterString = FString()) : FilterString(InFilterString), TagNode(InTagNode), TagSource(InTagSource), TagSourceAssets(InTagSourceAssets)`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace GameplayTagUtil`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Cook` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Cook` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace Cook` (scope `UE`)
- L94 _prototype_ `ENUM_RANGE_BY_COUNT(EGameplayTagSourceType, EGameplayTagSourceType::Invalid);`
- L675 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnGameplayTagLoaded, const FGameplayTag& ) FOnGameplayTagLoaded OnGameplayTagLoadedDelegate;`
- L757 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayTagDoubleClickedEditor, FGameplayTag, FSimpleMulticastDelegate& ) FOnGameplayTagDoubleClickedEditor OnGatherGameplayTagDoubleClickedEditor;`
- L761 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetCategoriesMetaFromPropertyHandle, TSharedPtr<IPropertyHandle>, FString& ) FOnGetCategoriesMetaFromPropertyHandle OnGetCategoriesMetaFromPropertyHandle;` — Chance to dynamically change filter string based on a property handle
- L765 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFilterGameplayTagChildren, const FString& , TSharedPtr<FGameplayTagNode>& , bool& ) FOnFilterGameplayTagChildren OnFilterGameplayTagChildren;` — Allows dynamic hiding of gameplay tags in SGameplayTagWidget. Allows higher order structs to dynamically change which tags are visible based on its own data
- L794 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFilterGameplayTag, const FFilterGameplayTagContext& , bool& ) FOnFilterGameplayTag OnFilterGameplayTag;` — Allows dynamic hiding of gameplay tags in SGameplayTagWidget. Allows higher order structs to dynamically change which tags are visible based on its own data Applies to all tags, and has more context than OnFilterGameplayTagChildren

### `Source/Runtime/GameplayTags/Classes/GameplayTagsSettings.h` (Public)


#### struct `FGameplayTagCategoryRemap`  
`struct FGameplayTagCategoryRemap`  
_L16-30_
- reflection: `USTRUCT()`
- desc: Category remapping. This allows base engine tag category meta data to remap to multiple project-specific categories.
- L21 _public member_ `FString BaseCategory;` — `UPROPERTY(EditAnywhere, Category = GameplayTags)`
- L24 _public member_ `TArray<FString> RemapCategories;` — `UPROPERTY(EditAnywhere, Category = GameplayTags)`

#### class `UGameplayTagsList`  
`class UGameplayTagsList : public UObject`  
_L34-52_
- reflection: `UCLASS(config = GameplayTagsList, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for storing a list of gameplay tags as an ini list. This is used for both the central list and additional lists
- L40 _private member_ `FString ConfigFileName;` — `UPROPERTY()` — Relative path to the ini file that is backing this list
- L44 _private member_ `TArray<FGameplayTagRedirect> GameplayTagRedirects;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags, meta = (ConfigRestartRequired = true))` — List of active tag redirects
- L48 _private member_ `TArray<FGameplayTagTableRow> GameplayTagList;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags)` — List of tags saved to this file
- L51 _private prototype_ `void SortTags();` — Sorts tags alphabetically

#### class `URestrictedGameplayTagsList`  
`class URestrictedGameplayTagsList : public UObject`  
_L56-70_
- reflection: `UCLASS(config = GameplayTags, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for storing a list of restricted gameplay tags as an ini list. This is used for both the central list and additional lists
- L62 _private member_ `FString ConfigFileName;` — `UPROPERTY()` — Relative path to the ini file that is backing this list
- L66 _private member_ `TArray<FRestrictedGameplayTagTableRow> RestrictedGameplayTagList;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags)` — List of restricted tags saved to this file
- L69 _private prototype_ `void SortTags();` — Sorts tags alphabetically

#### struct `FRestrictedConfigInfo`  
`struct FRestrictedConfigInfo`  
_L73-86_
- reflection: `USTRUCT()`
- L79 _public member_ `FString RestrictedConfigName;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = GameplayTags)` — Allows new tags to be saved into their own INI file. This is make merging easier for non technical developers by setting up their own ini file.
- L82 _public member_ `TArray<FString> Owners;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = GameplayTags)`
- L84 _public prototype_ `bool operator==(const FRestrictedConfigInfo& Other) const;`
- L85 _public prototype_ `bool operator!=(const FRestrictedConfigInfo& Other) const;`

#### class `UGameplayTagsSettings`  
`class UGameplayTagsSettings : public UGameplayTagsList`  
_L103-190_
- reflection: `UCLASS(config=GameplayTags, defaultconfig, MinimalAPI)`
- inherits: `UGameplayTagsList`
- desc: Class for importing GameplayTags directly from a config file. FGameplayTagsEditorModule::StartupModule adds this class to the Project Settings menu to be edited. Editing this in Project Settings will output changes to Config/DefaultGameplayTags.ini. Primary advantages of this approach are: -Adding new tags doesn't require checking out external and editing file (CSV or xls) then reimporting. -New tags are mergeable since .ini are text and non exclusive checkout. To do: -Better support could be added for adding new tags. We could match existing tags and autocomplete subtags as the user types (e.g, autocomplete 'Damage.Physical' as the user is adding a 'Damage.Physical.Slash' tag).
- L109 _private member_ `bool ImportTagsFromConfig;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags)` — If true, will import tags from ini files in the config/tags folder
- L113 _private member_ `bool WarnOnInvalidTags;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags, meta = (ConfigRestartRequired = true))` — If true, will give load warnings when reading in saved tag references that are not in the dictionary
- L117 _private member_ `bool ClearInvalidTags = false;` — `UE_DEPRECATED(5.5, "We never clear invalid tags when reading saved tag references as the loading order of native tags is not guaranteed.")` — `UPROPERTY(config)`
- L121 _private member_ `bool AllowEditorTagUnloading;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Gameplay Tags")` — If true, will allow unloading of tags in the editor when plugins are removed
- L125 _private member_ `bool AllowGameTagUnloading;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Gameplay Tags")` — If true, will allow unloading of tags in a non-editor gebuild when plugins are removed, this is potentially unsafe and affects requests to unload during play in editor
- L129 _private member_ `bool FastReplication;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Replication")` — If true, will replicate gameplay tags by index instead of name. For this to work, tags must be identical on client and server
- L133 _private member_ `bool bDynamicReplication;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Replication", meta=(EditCondition="!FastReplication"))` — If true, will replicate gameplay tags dynamically by index per connection. Slightly higher cost than FastReplication, but tags can differ between client and server
- L137 _private member_ `FString InvalidTagCharacters;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags)` — These characters cannot be used in gameplay tags, in addition to special ones like newline
- L141 _private member_ `TArray<FGameplayTagCategoryRemap> CategoryRemapping;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags)` — Category remapping. This allows base engine tag category meta data to remap to multiple project-specific categories.
- L145 _private member_ `TArray<FSoftObjectPath> GameplayTagTableList;` — `UPROPERTY(config, EditAnywhere, Category = GameplayTags, meta = (AllowedClasses = "/Script/Engine.DataTable"))` — List of data tables to load tags from
- L149 _private member_ `TArray<FName> CommonlyReplicatedTags;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Replication")` — List of most frequently replicated tags
- L153 _private member_ `int32 NumBitsForContainerSize;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Replication")` — Numbers of bits to use for replicating container size, set this based on how large your containers tend to be
- L157 _private member_ `int32 NetIndexFirstBitSegment;` — `UPROPERTY(config, EditAnywhere, Category= "Advanced Replication")` — The length in bits of the first segment when net serializing tags. We will serialize NetIndexFirstBitSegment + 1 bit to indicate "more", which is slower to replicate
- L161 _private member_ `TArray<FRestrictedConfigInfo> RestrictedConfigFiles;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Advanced Gameplay Tags")` — A list of .ini files used to store restricted gameplay tags.
- L170 _private member_ `FString RestrictedTagList;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, transient, Category = "Advanced Gameplay Tags")` — Restricted Gameplay Tags. Restricted tags are intended to be top level tags that are important for your data hierarchy and modified by very few people.
- L174 _private member_ `FString NewTagSource;` — `UPROPERTY(EditAnywhere, transient, Category = "GameplayTags")` — Add a new gameplay tag config file for saving plugin or game-specific tags.
- L178 _private member_ `FString CleanupUnusedTags;` — `UPROPERTY(EditAnywhere, transient, Category = "GameplayTags")` — Find and remove unused tags
- L182 _private prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L183 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L188 _private member_ `TArray<FRestrictedConfigInfo> RestrictedConfigFilesTempCopy;` — temporary copy of RestrictedConfigFiles that we use to identify changes in the list this is required to autopopulate the owners field

#### class `UGameplayTagsDeveloperSettings`  
`class UGameplayTagsDeveloperSettings : public UDeveloperSettings`  
_L193-206_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Gameplay Tag Editing"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L197 _private prototype_ `virtual FName GetCategoryName() const override;`
- L201 _private member_ `FString DeveloperConfigName;` — `UPROPERTY(config, EditAnywhere, Category=GameplayTags)` — Allows new tags to be saved into their own INI file. This is make merging easier for non technical developers by setting up their own ini file.
- L205 _private member_ `FName FavoriteTagSource;` — `UPROPERTY(config, EditAnywhere, Category=GameplayTags)` — Stores the favorite tag source, used as the default ini when adding new tags, can be toggled on/off using the button next to the tag source picker

#### Free symbols / members of external scopes

- L26 _function_ `friend inline bool operator==(const FGameplayTagCategoryRemap& A, const FGameplayTagCategoryRemap& B)`

### `Source/Runtime/GameplayTags/Private/InternalGameplayTagContainerNetSerializer.h` (Private)


#### struct `FGameplayTagContainerNetSerializerSerializationHelper`  
`struct FGameplayTagContainerNetSerializerSerializationHelper`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `TArray<FGameplayTag> GameplayTags;` — `UPROPERTY()`

### `Source/Runtime/GameplayTags/Public/GameplayTagContainerNetSerializer.h` (Public)


#### struct `FGameplayTagContainerNetSerializerConfig`  
`struct FGameplayTagContainerNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/GameplayTags/Public/GameplayTagNetSerializer.h` (Public)


#### struct `FGameplayTagNetSerializerConfig`  
`struct FGameplayTagNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/GameplayTags/Public/GameplayTagRedirectors.h` (Public)


#### struct `FGameplayTagRedirect`  
`struct FGameplayTagRedirect`  
_L19-42_
- reflection: `USTRUCT()`
- desc: A single redirect from a deleted tag to the new tag that should replace it
- L24 _public function_ `FGameplayTagRedirect()`
- L27 _public member_ `FName OldTagName;` — `UPROPERTY(EditAnywhere, Category = GameplayTags)`
- L30 _public member_ `FName NewTagName;` — `UPROPERTY(EditAnywhere, Category = GameplayTags)`
- L38 _public function_ `bool operator==(FName OtherOldTagName) const` — This enables lookups by old tag name via FindByKey

#### class `FGameplayTagRedirectors`  
`class FGameplayTagRedirectors`  
_L45-79_
- desc: This class is not thread safe and is protected against issues using the locks in GameplayTagManager
- L48 _public prototype_ `static FGameplayTagRedirectors& Get();`
- L51 _public prototype_ `bool RedirectTag(const FName& InTagName, FGameplayTag& OutTag) const;` — Sees if the tag name should be redirected to a different tag, returns false if there is no active redirect
- L54 _public prototype_ `void AddRedirectsFromSource(const struct FGameplayTagSource* Source);` — Adds redirects from the specified source. Faster than refreshing the entire list
- L57 _public prototype_ `void RefreshTagRedirects();` — Refreshes the redirect map after a config change
- L61 _public prototype_ `void Hash(FBlake3& Hasher);` — Update the hasher with a deterministic hash of the existing redirects. Used for e.g. IncrementalCook keys.
- L68 _public prototype_ `bool FindRedirectorsFromTargetTagName(const FName& TargetTagName, TArray<FName>& SourceTagNames) const;` — Find all source tag names from a target tag name. Only used in the cook so far. The reverse lookup is done with a loop, there is nothing to make it fast so used only if you have to. Or better, make a reverse lookup structure!
- L72 _private prototype_ `FGameplayTagRedirectors();`
- L75 _private prototype_ `void AddRedirects(const TArray<FGameplayTagRedirect>& Redirects);` — Adds a list of tag redirects to the map
- L78 _private member_ `TMap<FName, FGameplayTag> TagRedirects;` — The map of ini-configured tag redirectors

#### Free symbols / members of external scopes

- L32 _function_ `friend inline bool operator==(const FGameplayTagRedirect& A, const FGameplayTagRedirect& B)`

### `Source/Runtime/GameplayTags/Public/GameplayTagTokenStore.h` (Public)


#### class `UE::Net::FGameplayTagTokenStore`  
`class FGameplayTagTokenStore : public FNameTokenStore`  
_L14-33_
- inherits: `FNameTokenStore`
- desc: For now, this is just a specialization of NameTokenStore
- L18 _public prototype_ `explicit FGameplayTagTokenStore(FNetTokenStore& TokenStore);`
- L21 _public prototype_ `FNetToken GetOrCreateToken(FGameplayTag Tag);` — Create a NetToken for the provided name
- L24 _public prototype_ `FGameplayTag ResolveToken(FNetToken Token, const FNetTokenStoreState* RemoteTokenStoreState = nullptr) const;` — Resolve NetToken, to resolve remote tokens RemoteTokenStoreState must be valid
- L26 _public function_ `static FName GetTokenStoreName()`
- L32 _private member_ `inline static FName GameplayTokenStoreName = "Ga`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/GameplayTags/Public/GameplayTags.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/GameplayTags/Public/GameplayTagsModule.h` (Public)


#### class `IGameplayTagsModule`  
`class IGameplayTagsModule : public IModuleInterface`  
_L18-52_
- inherits: `IModuleInterface`
- desc: The public interface to this module, generally you should access the manager directly instead
- L29 _public function_ `static inline IGameplayTagsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L47 _public member_ `static FSimpleMulticastDelegate OnGameplayTagTreeChanged;` — Delegate for when assets are added to the tree
- L50 _public member_ `static FSimpleMulticastDelegate OnTagSettingsChanged;` — Delegate that gets called after the settings have changed in the editor

### `Source/Runtime/GameplayTags/Public/NativeGameplayTags.h` (Public)


#### enum `ENativeGameplayTagToken`  
`enum class ENativeGameplayTagToken`  
_L14-14_
- L14 _public enumerator_ `enum class ENativeGameplayTagToken { PRIVATE_USE_MACRO_INSTEAD }; namespace UE::GameplayTags::Private { constexpr bool HasFileExtension(const char* File) { const char* It = File;`

#### class `FNativeGameplayTag`  
`class FNativeGameplayTag : public FNoncopyable`  
_L58-113_
- inherits: `FNoncopyable`
- desc: Holds a gameplay tag that was registered during static construction of the module, and will be unregistered when the module unloads.  Each registration is based on the native tag pointer so even if two modules register the same tag and one is unloaded, the tag will still be registered by the other one.
- L61 _public member_ `static FName NAME_NativeGameplayTag;`
- L64 _public prototype_ `FNativeGameplayTag(FName PluginName, FName ModuleName, FName TagName, const FString& TagDevComment, ENativeGameplayTagToken);`
- L65 _public prototype_ `~FNativeGameplayTag();`
- L67 _public function_ `operator FGameplayTag() const`
- L69 _public function_ `FGameplayTag GetTag() const`
- L71 _public function_ `FGameplayTagTableRow GetGameplayTagTableRow() const`
- L85 _public function_ `FName GetPlugin() const`
- L86 _public function_ `FName GetModuleName() const`
- L87 _public function_ `FName GetModulePackageName() const`
- L95 _private member_ `FGameplayTag InternalTag;`
- L98 _private member_ `FName PluginName;`
- L99 _private member_ `FName ModuleName;`
- L100 _private member_ `FName ModulePackageName;`
- L101 _private member_ `mutable bool bValidated = false;`
- L103 _private prototype_ `void ValidateTagRegistration() const;`
- L107 _private member_ `FString DeveloperComment;`
- L110 _private prototype_ `static TSet<const class FNativeGameplayTag*>& GetRegisteredNativeTags();`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GameplayTags` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::GameplayTags`)
- L19 _function_ `constexpr bool HasFileExtension(const char* File)` (scope `UE::GameplayTags::Private`) — Used to prevent people from putting UE_DEFINE_GAMEPLAY_TAG_STATIC and UE_DEFINE_GAMEPLAY_TAG in their headers.
- L31 _macro_ `#define UE_DECLARE_GAMEPLAY_TAG_EXTERN(TagName) extern FNativeGameplayTag TagName;` — Declares a native gameplay tag that is defined in a cpp with UE_DEFINE_GAMEPLAY_TAG to allow other modules or code to use the created tag variable.
- L36 _macro_ `#define UE_DEFINE_GAMEPLAY_TAG_COMMENT(TagName, Tag, Comment) FNativeGameplayTag TagName(UE_PLUGIN_NAME, UE_MODULE_NAME, Tag, TEXT(Comment), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD); static_assert(UE::GameplayTags::Private::HasFi` — Defines a native gameplay tag with a comment that is externally declared in a header to allow other modules or code to use the created tag variable.
- L41 _macro_ `#define UE_DEFINE_GAMEPLAY_TAG(TagName, Tag) FNativeGameplayTag TagName(UE_PLUGIN_NAME, UE_MODULE_NAME, Tag, TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD); static_assert(UE::GameplayTags::Private::HasFileExtension(__FILE__),` — Defines a native gameplay tag with no comment that is externally declared in a header to allow other modules or code to use the created tag variable.
- L46 _macro_ `#define UE_DEFINE_GAMEPLAY_TAG_STATIC(TagName, Tag) static FNativeGameplayTag TagName(UE_PLUGIN_NAME, UE_MODULE_NAME, Tag, TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD); static_assert(UE::GameplayTags::Private::HasFileExtens` — Defines a native gameplay tag such that it's only available to the cpp file you define it in.
- L49 _macro_ `#define UE_INCLUDE_NATIVE_GAMEPLAYTAG_METADATA WITH_EDITOR && !UE_BUILD_SHIPPING`
