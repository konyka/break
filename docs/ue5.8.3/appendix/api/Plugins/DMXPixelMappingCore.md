# Plugins / DMXPixelMappingCore

- module root: `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingCore`
- headers: 2; symbols: 30
- symbol kinds: enum=3, enumerator=22, function=1, prototype=3, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, DMXProtocol, DMXRuntime
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingCore/Public/DMXPixelMappingTypes.h` (Public)


#### enum `EDMXPixelMappingRendererType`  
`enum class EDMXPixelMappingRendererType : uint8`  
_L11-16_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Texture`
- L14 _public enumerator_ `Material`
- L15 _public enumerator_ `UMG`

#### enum `EDMXCellFormat`  
`enum class EDMXCellFormat : uint8`  
_L19-41_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `PF_R UMETA(DisplayName = "R")`
- L22 _public enumerator_ `PF_G UMETA(DisplayName = "G")`
- L23 _public enumerator_ `PF_B UMETA(DisplayName = "B")`
- L25 _public enumerator_ `PF_RG UMETA(DisplayName = "RG")`
- L26 _public enumerator_ `PF_RB UMETA(DisplayName = "RB")`
- L27 _public enumerator_ `PF_GB UMETA(DisplayName = "GB")`
- L28 _public enumerator_ `PF_GR UMETA(DisplayName = "GR")`
- L29 _public enumerator_ `PF_BR UMETA(DisplayName = "BR")`
- L30 _public enumerator_ `PF_BG UMETA(DisplayName = "BG")`
- L32 _public enumerator_ `PF_RGB UMETA(DisplayName = "RGB")`
- L33 _public enumerator_ `PF_BRG UMETA(DisplayName = "BRG")`
- L34 _public enumerator_ `PF_GRB UMETA(DisplayName = "GRB")`
- L35 _public enumerator_ `PF_GBR UMETA(DisplayName = "GBR")`
- L37 _public enumerator_ `PF_RGBA UMETA(DisplayName = "RGBA")`
- L38 _public enumerator_ `PF_GBRA UMETA(DisplayName = "GBRA")`
- L39 _public enumerator_ `PF_BRGA UMETA(DisplayName = "BRGA")`
- L40 _public enumerator_ `PF_GRBA UMETA(DisplayName = "GRBA")`

#### enum `EDMXColorMode`  
`enum class EDMXColorMode : uint8`  
_L44-48_
- reflection: `UENUM(BlueprintType)`
- L46 _public enumerator_ `CM_RGB UMETA(DisplayName = "RGB")`
- L47 _public enumerator_ `CM_Monochrome UMETA(DisplayName = "Monochrome")`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingCore/Public/DMXPixelMappingUtils.h` (Public)


#### struct `FDMXPixelMappingUtils`  
`struct FDMXPixelMappingUtils`  
_L14-393_
- desc: Core helper classes
- L27 _public function_ `template<typename T> static void TextureDistributionSort(EDMXPixelMappingDistribution InDistribution, const int32& InNumXPanels, const int32& InNumYPanels, const TArray<T>& InUnorderedList, TArray<T>& OutSortedList)` — Sort a distribution array for texture @param InDistribution			Distribution schema @param InNumXPanels				Num columns @param InNumYPanels				Num rows @param InUnorderedList			Templated unsorted array input @param OutSortedList				Templated unsorted array output
- L376 _public prototype_ `static uint32 GetNumChannelsPerCell(EDMXCellFormat InPixelFormat);` — Calculate amount of the channels @param					InPixelFormat given pixel format. From 1 up to 4 colors per pixel @return Amount of the channels
- L384 _public prototype_ `static uint32 GetUniverseMaxChannels(EDMXCellFormat InPixelFormat, uint32 InStartAddress);` — Dynamically calculate amount of the channels based on Pixel Format schema @param					InPixelFormat given pixel format. From 1 up to 4 colors per pixel @param					InStartAddress start universe address @return Max channel value
- L392 _public prototype_ `static bool CanFitCellIntoChannels(EDMXCellFormat InPixelFormat, uint32 InStartAddress);` — Checking is there enough channel space for giver offset @param					InPixelFormat given pixel format. From 1 up to 4 colors per pixel @param					InStartAddress start universe address @return True if it possible to fit at lease one pixel
