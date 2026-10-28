# Plugins / HAPMedia

- module root: `Plugins/Media/HAPMedia/Source/HAPMedia`
- headers: 2; symbols: 20
- symbol kinds: class=1, delegate=1, member=2, prototype=16
- PrivateDependencyModuleNames: Core, HAPLib, Projects, SnappyLib, WmfMedia, WmfMediaFactory

### `Plugins/Media/HAPMedia/Source/HAPMedia/Private/HAPDecoder/WmfMediaHAPDecoder.h` (Private)


#### class `WmfMediaHAPDecoder`  
`class WmfMediaHAPDecoder : public WmfMediaDecoder`  
_L9-39_
- inherits: `WmfMediaDecoder`
- L14 _public prototype_ `WmfMediaHAPDecoder();`
- L15 _public prototype_ `virtual ~WmfMediaHAPDecoder();`
- L17 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppv) override;`
- L18 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetOutputAvailableType(DWORD dwOutputStreamID, DWORD dwTypeIndex, IMFMediaType** ppType) override;`
- L19 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ProcessMessage(MFT_MESSAGE_TYPE eMessage, ULONG_PTR ulParam) override;`
- L20 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ProcessOutput(DWORD dwFlags, DWORD cOutputBufferCount, MFT_OUTPUT_DATA_BUFFER* pOutputSamples, DWORD* pdwStatus) override;`
- L21 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetAttributes(IMFAttributes** pAttributes) override;`
- L23 _public prototype_ `virtual bool IsExternalBufferSupported() const override;`
- L25 _public prototype_ `static bool IsSupported(const GUID& InGuid);`
- L26 _public prototype_ `static bool SetOutputFormat(const GUID& InGuid, GUID& OutVideoFormat);`
- L30 _private prototype_ `virtual bool HasPendingOutput() const override;`
- L32 _private prototype_ `HRESULT InternalProcessOutput(IMFSample *InSample);`
- L33 _private prototype_ `virtual HRESULT InternalProcessInput(LONGLONG InTimeStamp, BYTE* InData, DWORD InDataSize) override;`
- L34 _private prototype_ `virtual HRESULT OnCheckInputType(IMFMediaType *InMediaType) override;`
- L35 _private prototype_ `virtual HRESULT OnSetInputType(IMFMediaType *InMediaType) override;`
- L37 _private member_ `GUID InputSubType;`
- L38 _private member_ `TComPtr<IMFMediaBuffer> MediaBuffer;`

### `Plugins/Media/HAPMedia/Source/HAPMedia/Private/HAPMediaModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHAPMedia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHAPMedia, Log, All);`
