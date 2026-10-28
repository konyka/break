# Plugins / DynamicMaterialMediaStreamBridge

- module root: `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridge`
- headers: 3; symbols: 51
- symbol kinds: class=3, function=2, member=4, prototype=42
- PrivateDependencyModuleNames: MediaStream, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, DynamicMaterial, Engine

### `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridge/Private/DynamicMaterialMediaStreamBridgeModule.h` (Private)


#### class `FDynamicMaterialMediaStreamBridgeModule`  
`class FDynamicMaterialMediaStreamBridgeModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- desc: Media Stream Material Designer Bridge - Integrates the Media Stream plugin with the Material Designer.
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridge/Public/DMMaterialValueMediaStream.h` (Public)


#### class `UDMMaterialValueMediaStream`  
`class UDMMaterialValueMediaStream : public UDMMaterialValueTexture`  
_L16-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueTexture`
- desc: Component representing a render target texture value. Manages its own parameter.
- L21 _public prototype_ `UDMMaterialValueMediaStream();`
- L26 _public prototype_ `UMediaStream* GetMediaStream() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L31 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L35 _public function_ `virtual bool AllowEditValue() const`
- L36 _public prototype_ `virtual void ResetDefaultValue() override;`
- L37 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L41 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L42 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L43 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L44 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L48 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L49 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L50 _public prototype_ `virtual void PostLoad() override;`
- L57 _protected member_ `TObjectPtr<UMediaStream> MediaStream;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer|Media Stream", meta = (AllowPrivateAccess = "true", NotKeyframeable))`
- L59 _protected member_ `TWeakObjectPtr<UMediaStream> SubscribedStreamWeak;`
- L62 _protected prototype_ `void UpdateTextureFromMediaStream();`
- L64 _protected prototype_ `void SubscribeToEvents();`
- L66 _protected prototype_ `void UnsubscribeFromEvents();`
- L69 _protected prototype_ `void OnSourceChanged(UMediaStream* InMediaStream);` — `UFUNCTION()`
- L72 _protected prototype_ `void OnPlayerChanged(UMediaStream* InMediaStream);` — `UFUNCTION()`
- L74 _protected prototype_ `void UpdatePlayer();`
- L77 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L81 _protected prototype_ `virtual void OnComponentAdded() override;`
- L82 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/Experimental/DynamicMaterialMediaStreamBridge/Source/DynamicMaterialMediaStreamBridge/Public/DMMaterialValueMediaStreamDynamic.h` (Public)


#### class `UDMMaterialValueMediaStreamDynamic`  
`class UDMMaterialValueMediaStreamDynamic : public UDMMaterialValueTextureDynamic`  
_L16-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueTextureDynamic`
- desc: Link to a UDMMaterialValueMediaStream for Material Designer Model Dynamics.
- L25 _public prototype_ `UDMMaterialValueMediaStreamDynamic();`
- L28 _public function_ `UMediaStream* GetMediaStream() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L32 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L33 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L38 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L39 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L40 _public prototype_ `virtual FSlateIcon GetComponentIcon() const override;`
- L44 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L45 _public prototype_ `virtual void PostLoad() override;`
- L52 _protected member_ `TObjectPtr<UMediaStream> MediaStream;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer|Media Stream", meta = (AllowPrivateAccess = "true", NotKeyframeable))`
- L54 _protected member_ `TWeakObjectPtr<UMediaStream> SubscribedStreamWeak;`
- L57 _protected prototype_ `void UpdateTextureFromMediaStream();`
- L59 _protected prototype_ `void SubscribeToEvents();`
- L61 _protected prototype_ `void UnsubscribeFromEvents();`
- L64 _protected prototype_ `void OnSourceChanged(UMediaStream* InMediaStream);` — `UFUNCTION()`
- L67 _protected prototype_ `void OnPlayerChanged(UMediaStream* InMediaStream);` — `UFUNCTION()`
- L69 _protected prototype_ `void UpdatePlayer();`
- L72 _protected prototype_ `virtual void OnComponentAdded() override;`
- L73 _protected prototype_ `virtual void OnComponentRemoved() override;`
- L78 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
