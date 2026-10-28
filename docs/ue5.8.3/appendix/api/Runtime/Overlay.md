# Runtime / Overlay

- module root: `Source/Runtime/Overlay`
- headers: 6; symbols: 44
- symbol kinds: class=5, delegate=1, enum=1, enumerator=2, function=1, member=12, prototype=21, struct=1
- PrivateDependencyModuleNames: Slate, SlateCore, UMG
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/Overlay/Private/OverlayPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOverlay, Log, All);` — Declares a log category for this module.
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOverlay, Log, All);` — Declares a log category for this module.

### `Source/Runtime/Overlay/Public/BasicOverlays.h` (Public)


#### class `UBasicOverlays`  
`class UBasicOverlays : public UOverlays`  
_L25-63_
- reflection: `UCLASS(BlueprintType, hidecategories = (Object), MinimalAPI)`
- inherits: `UOverlays`
- desc: Implements an asset that contains a set of overlay data (which includes timing, text, and position) to be displayed for any given source (including, but not limited to, audio, dialog, and movies)
- L34 _public member_ `TArray<FOverlayItem> Overlays;` — `UPROPERTY(EditAnywhere, Category="Overlay Data")` — The overlay data held by this asset. Contains info on timing, position, and the subtitle to display
- L40 _public member_ `TObjectPtr<UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Import Settings")` — The import data used to make this overlays asset
- L48 _public prototype_ `virtual TArray<FOverlayItem> GetAllOverlays() const override;`
- L49 _public prototype_ `virtual void GetOverlaysForTime(const FTimespan& Time, TArray<FOverlayItem>& OutOverlays) const override;`
- L55 _public prototype_ `virtual void PostInitProperties() override;`
- L56 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L58 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`

### `Source/Runtime/Overlay/Public/IOverlayModule.h` (Public)


#### class `IOverlayModule`  
`class IOverlayModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- desc: Interface for the Overlay module
- L15 _public prototype_ `virtual ~IOverlayModule() = default;` — Virtual destructor

### `Source/Runtime/Overlay/Public/LocalizedOverlays.h` (Public)


#### class `ULocalizedOverlays`  
`class ULocalizedOverlays : public UOverlays`  
_L29-81_
- reflection: `UCLASS(BlueprintType, hidecategories = (Object), MinimalAPI)`
- inherits: `UOverlays`
- desc: Implements an asset that contains a set of Basic Overlays that will be displayed in accordance with the current locale, or a default set if an appropriate locale is not found
- L38 _public member_ `TObjectPtr<UBasicOverlays> DefaultOverlays;` — `UPROPERTY(EditAnywhere, Category="Overlay Data")` — The overlays to use if no overlays are found for the current culture
- L48 _public member_ `TMap<FString, TObjectPtr<UBasicOverlays>> LocaleToOverlaysMap;` — `UPROPERTY(EditAnywhere, Category="Overlay Data")` — Maps a set of cultures to specific BasicOverlays assets. Cultures are comprised of three hyphen-separated parts: A two-letter ISO 639-1 language code (e.g., "zh") An optional four-letter ISO 15924 script code (e.g., "Hans") An optional two-letter ISO 3166-1 country code  (e.g., "CN")
- L54 _public member_ `TObjectPtr<UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Import Settings")` — The import data used to make this overlays asset
- L62 _public prototype_ `virtual TArray<FOverlayItem> GetAllOverlays() const override;`
- L63 _public prototype_ `virtual void GetOverlaysForTime(const FTimespan& Time, TArray<FOverlayItem>& OutOverlays) const override;`
- L70 _public prototype_ `virtual void PostInitProperties() override;`
- L71 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L73 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L80 _private prototype_ `UBasicOverlays* GetCurrentLocaleOverlays() const;` — Retrieves the overlays object for the current locale

### `Source/Runtime/Overlay/Public/Overlays.h` (Public)


#### struct `FOverlayItem`  
`struct FOverlayItem`  
_L14-40_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public function_ `FOverlayItem() : StartTime(0) , EndTime(0) , Position(0.0f, 0.0f)`
- L27 _public member_ `FTimespan StartTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Display Times")` — When the overlay should be displayed
- L31 _public member_ `FTimespan EndTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Display Times")` — When the overlay should be cleared
- L35 _public member_ `FString Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Display Data", meta=(MultiLine=True))` — Text that appears onscreen when the overlay is shown
- L39 _public member_ `FVector2D Position;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Display Data")` — The position of the text on screen (Between 0.0 and 1.0)

#### class `UOverlays`  
`class UOverlays : public UObject`  
_L47-66_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: An interface class for creating overlay data assets
- L57 _public prototype_ `virtual TArray<FOverlayItem> GetAllOverlays() const PURE_VIRTUAL(UOverlays::GetAllOverlays, return TArray<FOverlayItem>(););` — Retrieves the set of overlays that should be used by this object (must be implemented by child classes)
- L65 _public prototype_ `virtual void GetOverlaysForTime(const FTimespan& Time, TArray<FOverlayItem>& OutOverlays) const PURE_VIRTUAL(UOverlays::GetAllOverlays, return;);` — Retrieves the set of overlays associated with this object for the given timespan (must be implemented by child classes) @param	Time			Determines what overlays should be displayed @param	OutOverlays		All overlays that should be displayed for the given Time. Expect this to be emptied.

### `Source/Runtime/Overlay/Public/OverlaysImporter.h` (Public)


#### enum `EOverlaysFileType`  
`enum class EOverlaysFileType`  
_L11-15_
- L13 _public enumerator_ `Unknown`
- L14 _public enumerator_ `SubRipSubtitles`

#### class `FOverlaysImporter`  
`class FOverlaysImporter`  
_L17-52_
- L20 _public prototype_ `FOverlaysImporter();`
- L21 _public prototype_ `~FOverlaysImporter();`
- L29 _public prototype_ `bool OpenFile(const FString& FilePath);` — Opens the file and preparses it for import @param	Filename	The file to open @return	True if the file was opened successfully, false if the file could not be opened or is not an overlay file.
- L37 _public prototype_ `bool ImportBasic(TArray<FOverlayItem>& OutOverlays) const;` — Parses the supplied import file for basic overlay data @param	OutSubtitles	The output array where new overlays are stored. This is emptied when the import begins @return	True if the file was parsed successfully
- L42 _public prototype_ `void Reset();` — Resets the importer to a default state
- L45 _private prototype_ `bool ParseSubRipSubtitles(TArray<FOverlayItem>& OutSubtitles) const;`
- L48 _private member_ `FString Filename;`
- L49 _private member_ `FString FileContents;`
- L51 _private member_ `EOverlaysFileType FileType;`
