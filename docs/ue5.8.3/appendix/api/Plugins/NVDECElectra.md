# Plugins / NVDECElectra

- module root: `Plugins/Media/NVDECElectra/Source/NVDECElectra`
- headers: 2; symbols: 6
- symbol kinds: class=1, delegate=1, prototype=4
- PrivateDependencyModuleNames: CUDA, Core, D3D12RHI, ElectraBase, ElectraCodecFactory, ElectraDecoders, ElectraSamples, RHI
- PublicDependencyModuleNames: DirectX, nvDecode

### `Plugins/Media/NVDECElectra/Source/NVDECElectra/Private/NVDEC/ElectraMediaNVDEC.h` (Private)


#### class `FElectraMediaNVDECDecoder`  
`class FElectraMediaNVDECDecoder`  
_L8-14_
- L11 _public prototype_ `static void Startup();`
- L12 _public prototype_ `static void Shutdown();`
- L13 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/NVDECElectra/Source/NVDECElectra/Private/NVDECElectraModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNVDECElectraDecoder, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNVDECElectraDecoder, Log, All);`
