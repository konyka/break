# Plugins / CaptureManagerTakeMetadata

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerTakeMetadata`
- headers: 1; symbols: 105
- symbol kinds: class=4, enum=3, enumerator=9, function=2, macro=1, member=52, prototype=22, struct=11, typedef=1
- PrivateDependencyModuleNames: Core, Projects, RapidJSON
- PublicDependencyModuleNames: ImageCore

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerTakeMetadata/Public/CaptureManagerTakeMetadata.h` (Public)


#### class `FTakeThumbnailData`  
`class FTakeThumbnailData`  
_L18-64_
- desc: Class for constructing take thumbnails and accessing thumbnail data.
- L31 _public prototype_ `FTakeThumbnailData();` — Default thumbnail constructor.
- L34 _public prototype_ `FTakeThumbnailData(FString InImagePath);` — Construct thumbnail from file path.
- L37 _public prototype_ `FTakeThumbnailData(TArray<uint8> InCompressedImageData);` — Construct thumbnail from file data array.
- L40 _public prototype_ `FTakeThumbnailData(TArray<FColor> InDecompressedImageData, uint32 InWidth, uint32 InHeight, ERawImageFormat::Type InFormat);` — Construct thumbnail from raw data array.
- L43 _public prototype_ `void operator=(FString InImagePath);` — Construct thumbnail from file path.
- L46 _public prototype_ `void operator=(TArray<uint8> InCompressedImageData);` — Construct thumbnail from file data array.
- L49 _public prototype_ `void operator=(FRawImage InRawImage);` — Assign thumbnail from raw data array.
- L52 _public prototype_ `TOptional<TArray<uint8>> GetThumbnailData() const;` — Get thumbnail.
- L55 _public prototype_ `TOptional<FString> GetThumbnailPath() const;` — Get thumbnail file path.
- L58 _public prototype_ `TOptional<FRawImage> GetRawImage() const;` — Get decompressed image.
- L62 _private typedef_ `using FThumbnail = TVariant<FEmptyVariantState, FString, TArray<uint8>, FRawImage>;`
- L63 _private member_ `FThumbnail Thumbnail;`

#### struct `FTakeThumbnailData::FRawImage`  
`struct FRawImage`  
_L22-28_
- L24 _public member_ `TArray<FColor> DecompressedImageData;`
- L25 _public member_ `uint32 Width;`
- L26 _public member_ `uint32 Height;`
- L27 _public member_ `ERawImageFormat::Type Format;`

#### class `FTakeMetadata`  
`class FTakeMetadata`  
_L67-222_
- desc: Data assosciated with a take.
- L71 _public member_ `static const FString FileExtension;` — File extension for take metadata files.
- L86 _public function_ `friend uint32 GetTypeHash(const FSchemaVersion& InVersion)`
- L195 _public member_ `FSchemaVersion Version;` — Schema version of the take metadata file.
- L197 _public member_ `TOptional<FDateTime> DateTime;`
- L200 _public member_ `FTakeThumbnailData Thumbnail;` — Thumbnail.
- L203 _public member_ `FString UniqueId;` — Unique identifier (GUID).
- L205 _public member_ `uint32 TakeNumber = 0;`
- L206 _public member_ `FString Slate;`
- L209 _public member_ `FDevice Device;` — Schema version (Major.Minor).
- L212 _public member_ `TArray<FVideo> Video;` — Video list.
- L215 _public member_ `TArray<FVideo> Depth;` — Depth list.
- L218 _public member_ `TArray<FCalibration> Calibration;` — Calibration list.
- L221 _public member_ `TArray<FAudio> Audio;` — Audio list.

#### struct `FTakeMetadata::FSchemaVersion`  
`struct FSchemaVersion`  
_L74-90_
- desc: Version of the take metadata schema.
- L76 _public member_ `uint32 Major = 0;`
- L77 _public member_ `uint32 Minor = 0;`
- L79 _public prototype_ `bool operator==(const FSchemaVersion& rhs) const = default;`
- L81 _public function_ `bool operator<(const FSchemaVersion& rhs) const`

#### struct `FTakeMetadata::FDevice`  
`struct FDevice`  
_L93-114_
- desc: Device information.
- L107 _public member_ `FString Name;`
- L108 _public member_ `FString Type;`
- L109 _public member_ `FString Model;`
- L112 _public member_ `TOptional<FDevice::FPlatform> Platform;`
- L113 _public member_ `TArray<FDevice::FSoftware> Software;`

#### struct `FTakeMetadata::FDevice::FPlatform`  
`struct FPlatform`  
_L95-99_
- L97 _public member_ `FString Name;`
- L98 _public member_ `TOptional<FString> Version;`

#### struct `FTakeMetadata::FDevice::FSoftware`  
`struct FSoftware`  
_L101-105_
- L103 _public member_ `FString Name;`
- L104 _public member_ `TOptional<FString> Version;`

#### struct `FTakeMetadata::FVideo`  
`struct FVideo`  
_L117-159_
- desc: Video information.
- L133 _public member_ `FString Name;`
- L134 _public member_ `FString Path;`
- L137 _public member_ `TOptional<EPathType> PathType;` — Path type (e.g. Folder or File).
- L140 _public member_ `FString Format;` — Format e.g. mov, png.
- L143 _public member_ `TOptional<EOrientation> Orientation;` — Orientation (e.g. Original, CW90, CW180 or CW270).
- L146 _public member_ `TOptional<uint32> FramesCount;` — Number of frames.
- L149 _public member_ `TOptional<TArray<uint32>> DroppedFrames;` — List of dropped frames.
- L151 _public member_ `TOptional<uint32> FrameHeight;`
- L152 _public member_ `TOptional<uint32> FrameWidth;`
- L155 _public member_ `float FrameRate = 0.0f;` — Frame rate.
- L158 _public member_ `TOptional<FString> TimecodeStart;` — Timecode of the first frame.

#### enum `FTakeMetadata::FVideo::EPathType`  
`enum class EPathType`  
_L119-123_
- L121 _public enumerator_ `Folder`
- L122 _public enumerator_ `File`

#### enum `FTakeMetadata::FVideo::EOrientation`  
`enum class EOrientation`  
_L125-131_
- L127 _public enumerator_ `Original`
- L128 _public enumerator_ `CW90`
- L129 _public enumerator_ `CW180`
- L130 _public enumerator_ `CW270`

#### struct `FTakeMetadata::FCalibration`  
`struct FCalibration`  
_L162-169_
- desc: Calibration information.
- L164 _public member_ `FString Name;`
- L165 _public member_ `FString Path;`
- L168 _public member_ `FString Format;` — File format (e.g. mhaical, unreal).

#### struct `FTakeMetadata::FAudio`  
`struct FAudio`  
_L172-185_
- desc: Audio information.
- L174 _public member_ `FString Name;`
- L175 _public member_ `FString Path;`
- L178 _public member_ `TOptional<float> Duration;` — Duration in seconds.
- L181 _public member_ `TOptional<FString> TimecodeStart;` — Timecode of the first sample.
- L184 _public member_ `TOptional<float> TimecodeRate;` — Timecode rate.

#### struct `FTakeMetadata::FFrameLog`  
`struct FFrameLog`  
_L188-191_
- desc: Frame log information.
- L190 _public member_ `FString Path;`

#### struct `FTakeMetadataParserError`  
`struct FTakeMetadataParserError`  
_L224-235_
- L233 _public member_ `EOrigin Origin;`
- L234 _public member_ `FText Message;`

#### enum `FTakeMetadataParserError::EOrigin`  
`enum EOrigin`  
_L226-231_
- L228 _public enumerator_ `Reader`
- L229 _public enumerator_ `Validator` — Reader,   Error reading the file.
- L230 _public enumerator_ `Parser` — Validator,   Error validating the file.

#### struct `FTakeMetadataSerializerError`  
`struct FTakeMetadataSerializerError`  
_L237-240_
- L239 _public member_ `FText Message;`

#### class `FTakeMetadataParser`  
`class FTakeMetadataParser`  
_L242-261_
- L245 _public prototype_ `FTakeMetadataParser();`
- L246 _public prototype_ `~FTakeMetadataParser();`
- L248 _public prototype_ `FTakeMetadataParser(const FTakeMetadataParser& other) = delete;`
- L249 _public prototype_ `FTakeMetadataParser(FTakeMetadataParser&& other);`
- L251 _public prototype_ `FTakeMetadataParser& operator=(const FTakeMetadataParser& other) = delete;`
- L252 _public prototype_ `FTakeMetadataParser& operator=(FTakeMetadataParser&& other);`
- L255 _public prototype_ `TValueOrError<FTakeMetadata, FTakeMetadataParserError> Parse(const FString& InJsonFile);` — Tries to parse file into a take metadata object.
- L259 _private member_ `TUniquePtr<FImpl> ImplPtr;`

#### class `FTakeMetadataPathUtils`  
`class FTakeMetadataPathUtils`  
_L264-275_
- desc: Utility functions for handling paths within take metadata files.
- L268 _public prototype_ `static FTakeMetadata::FVideo::EPathType DetectPathType(const FString& InPath);` — Detects path type from the input path (Folder or File).
- L271 _public prototype_ `static bool ValidatePathType(const FString& InPath, FTakeMetadata::FVideo::EPathType InPathType);` — Checks the path matches the path type.
- L274 _public prototype_ `static FString PathTypeToString(FTakeMetadata::FVideo::EPathType InPathType);` — Converts path type to a string.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CAPTUREMANAGERTAKEMETADATA_API`
- L278 _prototype_ `TOptional<FTakeMetadataSerializerError> SerializeTakeMetadata(const FString& InFilePath, const FTakeMetadata& InMetadata);` — Writes a take metadata object to the specified path.
