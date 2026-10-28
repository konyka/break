# Plugins / SlateIMEngine

- module root: `Plugins/Experimental/SlateIM/Source/SlateIMEngine`
- headers: 2; symbols: 47
- symbol kinds: class=1, delegate=1, enum=1, enumerator=2, member=31, prototype=7, struct=4
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SlateCore

### `Plugins/Experimental/SlateIM/Source/SlateIMEngine/Public/Implementation/SlateIMEngineCanvasDrawCommandList.h` (Public)


#### class `USlateIMEngineCanvasDrawCommandList`  
`class USlateIMEngineCanvasDrawCommandList : public UObject`  
_L16-42_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FCanvasDrawCommand, UCanvas*) USlateIMEngineCanvasDrawCommandList();`
- L25 _public prototype_ `ESlateIMEngineCanvasUpdateType GetUpdateType() const;`
- L27 _public prototype_ `void SetUpdateType(ESlateIMEngineCanvasUpdateType InUpdateType);`
- L29 _public prototype_ `void Invalidate();`
- L31 _public prototype_ `bool NeedsUpdate() const;`
- L33 _public prototype_ `void EnqueueCommand(FCanvasDrawCommand&& InDrawCommand);`
- L36 _public prototype_ `void ProcessCommands(UCanvas* InCanvas, int32 InWidth, int32 InHeight);` — `UFUNCTION()`
- L39 _protected member_ `ESlateIMEngineCanvasUpdateType UpdateType;`
- L40 _protected member_ `bool bInvalidated = false;`
- L41 _protected member_ `TArray<FCanvasDrawCommand> DrawCommands;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FCanvasDrawCommand, UCanvas*) USlateIMEngineCanvasDrawCommandList();`

### `Plugins/Experimental/SlateIM/Source/SlateIMEngine/Public/SlateIMEngineParameters.h` (Public)


#### enum `ESlateIMEngineCanvasUpdateType`  
`enum class ESlateIMEngineCanvasUpdateType : uint8`  
_L14-27_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `EveryFrame` — Redraw the canvas every frame.
- L23 _public enumerator_ `Invalidation` — Only redraw when specifically invalidated. Warning: Textures and materials may not be rendered correctly if they are not loaded or shaders are not cached.

#### struct `FSlateIMEngineCanvasParams`  
`struct FSlateIMEngineCanvasParams`  
_L30-49_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public member_ `FSlateColor ColorAndOpacity = FSlateColor(EStyleColor::White);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — Tint applied to the resulting image.
- L40 _public member_ `FVector2D DesiredSize = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The size of the image drawn in the UI. This may be different from the size of the canvas.
- L44 _public member_ `TObjectPtr<UObject> WorldContext = nullptr;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The world related to the canvas being drawn, if any.
- L48 _public member_ `ESlateIMEngineCanvasUpdateType UpdateType = ESlateIMEngineCanvasUpdateType::EveryFrame;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — When the texture will be redrawn.

#### struct `FSlateIMEngineTileRenderParams`  
`struct FSlateIMEngineTileRenderParams`  
_L55-82_
- reflection: `USTRUCT(BlueprintType)`
- desc: Extra optional parameters for rendering tiles (textures and materials.)
- L61 _public member_ `FVector2D UVPosition = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The top left of the area on the tile to draw, in texels.
- L65 _public member_ `FVector2D UVSize = FVector2D::UnitVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The size of the area on the tile to draw, in texels.
- L69 _public member_ `FLinearColor RenderColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — A tint to apply to tile.
- L73 _public member_ `TEnumAsByte<EBlendMode> BlendMode = BLEND_Translucent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The blend mode with which to draw the tile.
- L77 _public member_ `float Rotation = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The rotation of the tile, in degrees.
- L81 _public member_ `FVector2D PivotPoint = FVector2D(0.5, 0.5);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The point on the tile around which it is rotated, in texels.

#### struct `FSlateIMEngineTextRenderParams`  
`struct FSlateIMEngineTextRenderParams`  
_L88-127_
- reflection: `USTRUCT(BlueprintType)`
- desc: Extra optional parameters for rendering text.
- L94 _public member_ `FVector2D Scale = FVector2D(1.0f, 1.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The scale of the text on the canvas.
- L98 _public member_ `FLinearColor RenderColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The color of the text.
- L102 _public member_ `float Kerning = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — Adjust the distance between letters.
- L106 _public member_ `FLinearColor ShadowColor = FLinearColor::Black;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The color of the text shadow.
- L110 _public member_ `FVector2D ShadowOffset = FVector2D::UnitVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The offset of the shadow from the text it is shadowing.
- L114 _public member_ `bool bCentreX = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — If true, the text is centered on the given draw position on the X axis.
- L118 _public member_ `bool bCentreY = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — If true, the text is centered on the given draw position on the Y axis.
- L122 _public member_ `bool bOutlined = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — If true, outline the text.
- L126 _public member_ `FLinearColor OutlineColor = FLinearColor::Black;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — Color of the text outline.

#### struct `FSlateIMEngineBorderRenderParams`  
`struct FSlateIMEngineBorderRenderParams`  
_L135-174_
- reflection: `USTRUCT(BlueprintType)`
- desc: Extra optional parameters for rendering borders. Tile refers to the centre texture.
- L141 _public member_ `FVector2D UVPosition = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The top left of the area on the tile to draw, in texels.
- L145 _public member_ `FVector2D UVSize = FVector2D::UnitVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The size of the area on the tile to draw, in texels.
- L149 _public member_ `FLinearColor RenderColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — A tint to apply to tile.
- L153 _public member_ `TEnumAsByte<EBlendMode> BlendMode = BLEND_Translucent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The blend mode with which to draw the tile.
- L157 _public member_ `float Rotation = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The rotation of the tile, in degrees.
- L161 _public member_ `FVector2D PivotPoint = FVector2D(0.5, 0.5);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The point on the tile around which it is rotated, in texels.
- L165 _public member_ `FVector2D BorderScale = FVector2D(0.1, 0.1);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The scale of the border.
- L169 _public member_ `FVector2D BackgroundScale = FVector2D(0.1, 0.1);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — The scale of the background.
- L173 _public member_ `FVector2D CornerSize = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIMEngine")` — Frame corner size, in percent (should be < 0.5f).
