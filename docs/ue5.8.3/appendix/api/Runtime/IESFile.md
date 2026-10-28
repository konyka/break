# Runtime / IESFile

- module root: `Source/Runtime/IESFile`
- headers: 2; symbols: 35
- symbol kinds: class=2, function=3, member=10, prototype=20
- PrivateDependencyModuleNames: Core

### `Source/Runtime/IESFile/Private/IESLoader.h` (Private)


#### class `FIESLoader`  
`class FIESLoader`  
_L16-85_
- desc: To load the IES file image format. IES files exist for many real world lights. The file stores how much light is emitted in a specific direction. The data is usually measured but tools to paint IES files exist.
- L20 _public prototype_ `FIESLoader(const uint8* Buffer, uint32 BufferLength);` — is loading the file, can take some time, success can be checked with IsValid()
- L23 _public prototype_ `float ExtractInRGBA16F(TArray<uint8>& OutData);` — @return Multiplier as the texture is normalized
- L25 _public prototype_ `bool IsValid() const;`
- L27 _public prototype_ `uint32 GetWidth() const;`
- L28 _public prototype_ `uint32 GetHeight() const;`
- L31 _public prototype_ `float GetBrightness() const;` — @return in Lumens
- L33 _public function_ `const TCHAR* GetError() const`
- L40 _private member_ `TArray<float> HAngles;`
- L41 _private member_ `TArray<float> VAngles;`
- L42 _private member_ `TArray<float> CandelaValues;`
- L45 _private member_ `float Brightness;` — in Lumens, always >0
- L48 _private member_ `float CachedIntegral;` — used by ComputeFullIntegral(), integrated over the unit sphere, to avoid computing it twice, -1 if not computed yet
- L51 _private member_ `EIESPhotometricType PhotometricType;` — The photometric type associated with the IES file being loaded
- L54 _private prototype_ `void Load(const uint8* Buffer);` — will set Error to 0 on success
- L57 _private member_ `FString Error;` — 0 if no error, otherwise points to an ASCII error string
- L59 _private prototype_ `float ComputeMax() const;`
- L63 _private prototype_ `float ComputeFullIntegral();` — integrate over the unit sphere @return in Candela
- L65 _private prototype_ `static float ComputeFilterPos(float Value, const TArray<float>& SortedValues);`
- L70 _private prototype_ `float InterpolatePoint(int X, int Y) const;` — low level code, only used by InterpolateBilinear @param X 0..HAngles.size()-1 @param Y 0..VAngles.size()-1
- L75 _private prototype_ `float InterpolateBilinear(float fX, float fY) const;` — low level code, used by Interpolate2D() and Interpolate1D() @param fX 0..HAngles.size()-1 @param fY 0..VAngles.size()-1
- L80 _private prototype_ `float Interpolate2D(float HAngle, float VAngle) const;` — high level code to compute the Candela value for a given direction @param HAngle n degrees e.g. 0..360 @param VAngle n degrees e.g. 0..180
- L84 _private prototype_ `float Interpolate1D(float VAngle) const;` — like Interpolate2D but also integrates over HAngle @param VAngle n degrees e.g. 0..180

### `Source/Runtime/IESFile/Public/IESConverter.h` (Public)


#### class `FIESConverter`  
`class FIESConverter`  
_L11-57_
- desc: To load the IES file image format. IES files exist for many real world lights. The file stores how much light is emitted in a specific direction. The data is usually measured but tools to paint IES files exist.
- L15 _public prototype_ `FIESConverter(const uint8* Buffer, uint32 BufferLength);` — is loading the file, can take some time, success can be checked with IsValid()
- L21 _public prototype_ `bool IsValid() const;` — @return true if the photometric data are valid @note Call GetError to get a description of the error
- L26 _public prototype_ `const TCHAR* GetError() const;` — @return a brief description of the reason why the IES data is invalid
- L31 _public function_ `float GetMultiplier() const` — @return Multiplier as the texture is normalized
- L39 _public function_ `const TArray<uint8>& GetRawData() const` — @return data to create UTextureProfile
- L44 _public prototype_ `uint32 GetWidth() const;`
- L45 _public prototype_ `uint32 GetHeight() const;`
- L50 _public prototype_ `float GetBrightness() const;` — @return brightness in Lumens
- L53 _private member_ `TArray<uint8> RawData;`
- L54 _private member_ `float Multiplier;`
- L56 _private member_ `TSharedPtr<class FIESLoader> Impl;`
