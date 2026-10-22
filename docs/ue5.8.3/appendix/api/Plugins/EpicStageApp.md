# Plugins / EpicStageApp

- module root: `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp`
- headers: 8; symbols: 198
- symbol kinds: class=5, enum=2, enumerator=6, function=32, member=86, prototype=45, struct=21, typedef=1
- PrivateDependencyModuleNames: DeveloperSettings, DiscoveryBeaconReceiver, DisplayCluster, DisplayClusterLightCardEditor, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, DisplayClusterScenePreview, Engine, ImageWrapper, Networking, RHI, RemoteControl, RemoteControlCommon, Sockets, UnrealEd, WebRemoteControl
- PublicDependencyModuleNames: Core, CoreUObject, Serialization

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Private/EpicStageApp.h` (Private)


#### class `FEpicStageAppModule`  
`class FEpicStageAppModule : public IModuleInterface`  
_L12-28_
- inherits: `IModuleInterface`
- L15 _private prototype_ `virtual void StartupModule() override;`
- L16 _private prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `FStageAppRouteHandler RouteHandler;` — Handler for WebSocket routes.
- L24 _private member_ `FStageAppBeaconReceiver StageAppBeaconReceiver;` — Receiver that responds to beacon messages from the stage app.
- L27 _private member_ `FDelegateHandle WebSocketServerStartedDelegate;` — Delegate for when the websocket server starts.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Private/StageAppBeaconReceiver.h` (Private)


#### class `FStageAppBeaconReceiver`  
`class FStageAppBeaconReceiver : public FDiscoveryBeaconReceiver`  
_L11-34_
- inherits: `FDiscoveryBeaconReceiver`
- desc: Receives beacon messages from the Unreal Stage App and replies with connection information. This allows the app to detect compatible Unreal instances on the local network and list them for the user.
- L15 _public prototype_ `FStageAppBeaconReceiver();`
- L16 _public function_ `virtual ~FStageAppBeaconReceiver()`
- L20 _public prototype_ `virtual void Startup() override;`
- L23 _protected prototype_ `virtual bool GetDiscoveryAddress(FIPv4Address& OutAddress) const override;`
- L24 _protected prototype_ `virtual int32 GetDiscoveryPort() const override;`
- L25 _protected prototype_ `virtual bool MakeBeaconResponse(uint8 BeaconProtocolVersion, FArrayReader& InMessageData, FArrayWriter& OutResponseData) const override;`
- L30 _private prototype_ `FString GetFriendlyName() const;` — Get the name to report to apps searching for the engine.
- L33 _private member_ `uint32 WebsocketPort;` — The websocket port with which to reply.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Private/StageAppRequest.h` (Private)


#### enum `ERCWebSocketNDisplayPreviewRenderType`  
`enum class ERCWebSocketNDisplayPreviewRenderType : uint8`  
_L12-16_
- reflection: `UENUM()`
- desc: Type of preview render to perform, exposed as a UENUM. Corresponds to EDisplayClusterMeshProjectionOutput.
- L14 _public enumerator_ `Color`
- L15 _public enumerator_ `Normals`

#### enum `ERCWebSocketNDisplayPreviewRenderProjectionType`  
`enum class ERCWebSocketNDisplayPreviewRenderProjectionType : uint8`  
_L20-26_
- reflection: `UENUM()`
- desc: Type of projection to use for a preview render, exposed as a UENUM. Corresponds to EDisplayClusterMeshProjectionType.
- L22 _public enumerator_ `Perspective`
- L23 _public enumerator_ `Azimuthal`
- L24 _public enumerator_ `Orthographic`
- L25 _public enumerator_ `UV`

#### struct `FRCWebSocketNDisplayPreviewRendererSettings`  
`struct FRCWebSocketNDisplayPreviewRendererSettings`  
_L30-75_
- reflection: `USTRUCT()`
- desc: Preview renderer settings exposed to WebSocket clients.
- L38 _public member_ `ERCWebSocketNDisplayPreviewRenderType RenderType = ERCWebSocketNDisplayPreviewRenderType::Color;` — `UPROPERTY()` — The type of render to perform.
- L44 _public member_ `ERCWebSocketNDisplayPreviewRenderProjectionType ProjectionType = ERCWebSocketNDisplayPreviewRenderProjectionType::Azimuthal;` — `UPROPERTY()` — The type of projection to use.
- L50 _public member_ `FIntPoint Resolution = FIntPoint(1024, 1024);` — `UPROPERTY()` — The resolution of the image to render.
- L56 _public member_ `float FOV = 130.0f;` — `UPROPERTY()` — The preview camera's field of view (both horizontal and vertical) in degrees.
- L62 _public member_ `FRotator Rotation = FRotator(90, 0, 0);` — `UPROPERTY()` — The preview camera's Euler rotation relative to the camera's actual rotation in the scene.
- L68 _public member_ `int32 JpegQuality = 50;` — `UPROPERTY()` — The quality of the JPEG to send back to the requesting client, in range 50-100.
- L74 _public member_ `bool IncludeActorPositions = false;` — `UPROPERTY()` — If true, include a list of projected positions within the preview render for each rendered actor when responding to a render request.

#### struct `FRCWebSocketNDisplayPreviewRendererCreateBody`  
`struct FRCWebSocketNDisplayPreviewRendererCreateBody : public FRCRequest`  
_L81-106_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to create an nDisplay preview renderer.
- L85 _public function_ `FRCWebSocketNDisplayPreviewRendererCreateBody()`
- L93 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L99 _public member_ `FString RootActorPath = "";` — `UPROPERTY()` — The path of the root DisplayCluster actor to preview. This may be empty, in which case you can set the root actor later.
- L105 _public member_ `FRCWebSocketNDisplayPreviewRendererSettings Settings;` — `UPROPERTY()` — Initial settings for the renderer.

#### struct `FRCWebSocketNDisplayPreviewRendererSetRootBody`  
`struct FRCWebSocketNDisplayPreviewRendererSetRootBody : public FRCRequest`  
_L112-137_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to change the root DisplayCluster actor of an nDisplay preview renderer.
- L116 _public function_ `FRCWebSocketNDisplayPreviewRendererSetRootBody()`
- L124 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L130 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the renderer returned when it was created.
- L136 _public member_ `FString RootActorPath = "";` — `UPROPERTY()` — The path of the root DisplayCluster actor to preview.

#### struct `FRCWebSocketNDisplayPreviewRendererDestroyBody`  
`struct FRCWebSocketNDisplayPreviewRendererDestroyBody : public FRCRequest`  
_L143-162_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to destroy an nDisplay preview renderer.
- L147 _public function_ `FRCWebSocketNDisplayPreviewRendererDestroyBody()`
- L155 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L161 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the renderer returned when it was created.

#### struct `FRCWebSocketNDisplayPreviewRendererConfigureBody`  
`struct FRCWebSocketNDisplayPreviewRendererConfigureBody : public FRCRequest`  
_L168-183_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Change a preview renderer's settings for future renders.
- L176 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the renderer returned when it was created.
- L182 _public member_ `FRCWebSocketNDisplayPreviewRendererSettings Settings;` — `UPROPERTY()` — Settings to use for future renders.

#### struct `FRCWebSocketNDisplayPreviewRenderBody`  
`struct FRCWebSocketNDisplayPreviewRenderBody : public FRCRequest`  
_L189-208_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to render a preview of a display cluster.
- L193 _public function_ `FRCWebSocketNDisplayPreviewRenderBody()`
- L201 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L207 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the renderer returned when it was created.

#### struct `FRCWebSocketNDisplayPreviewActorDragBeginBody`  
`struct FRCWebSocketNDisplayPreviewActorDragBeginBody : public FRCRequest`  
_L214-252_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to start dragging one or more actors.
- L218 _public function_ `FRCWebSocketNDisplayPreviewActorDragBeginBody()`
- L226 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L232 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the preview renderer returned when it was created.
- L238 _public member_ `TArray<FString> Actors;` — `UPROPERTY()` — Paths of the actors that will be included in this drag action.
- L244 _public member_ `FString PrimaryActor;` — `UPROPERTY()` — The actor to use as the origin point for the drag.
- L251 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The sequence number of this change. The highest sequence number received from this client will be sent back to the client in future position updates.

#### struct `FRCWebSocketNDisplayPreviewActorDragMoveBody`  
`struct FRCWebSocketNDisplayPreviewActorDragMoveBody : public FRCRequest`  
_L259-291_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to move the actors that are currently being dragged for a preview renderer.
- L263 _public function_ `FRCWebSocketNDisplayPreviewActorDragMoveBody()`
- L271 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L277 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the preview renderer returned when it was created.
- L283 _public member_ `FVector2D DragPosition = FVector2D::ZeroVector;` — `UPROPERTY()` — The position of the drag cursor in coordinates normalized to the size of the preview image.
- L290 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The sequence number of this change. The highest sequence number received from this client will be sent back to the client in future position updates.

#### struct `FRCWebSocketNDisplayPreviewActorDragEndBody`  
`struct FRCWebSocketNDisplayPreviewActorDragEndBody : public FRCRequest`  
_L297-329_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to stop dragging actors for a preview renderer.
- L301 _public function_ `FRCWebSocketNDisplayPreviewActorDragEndBody()`
- L309 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L315 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the preview renderer returned when it was created.
- L321 _public member_ `FVector2D DragPosition = FVector2D::ZeroVector;` — `UPROPERTY()` — The final position of the drag cursor in coordinates normalized to the size of the preview image.
- L328 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The sequence number of this change. The highest sequence number received from this client will be sent back to the client in future position updates.

#### struct `FRCWebSocketNDisplayPreviewActorCreateBody`  
`struct FRCWebSocketNDisplayPreviewActorCreateBody : public FRCRequest`  
_L335-414_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to create an actor, optionally positioned relative to the previewed area.
- L339 _public function_ `FRCWebSocketNDisplayPreviewActorCreateBody()`
- L347 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L353 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the preview renderer to use when positioning this light card.
- L359 _public member_ `FString ActorName = "";` — `UPROPERTY()` — The name of the actor to spawn. A number will be appended if this conflicts with another name.
- L365 _public member_ `FString ActorClass = "";` — `UPROPERTY()` — The name of the class of the actor to spawn.
- L373 _public member_ `FString TemplatePath = "";` — `UPROPERTY()` — The path of the template to use for the lightcard. If empty, a lightcard will be created using the default template. If "None", a lightcard will be created with default settings regardless of whether there's a default template.
- L380 _public member_ `bool OverridePosition = false;` — `UPROPERTY()` — If true, override the default/template position for the lightcard with the provided Position. Otherwise, use the template's position, or if no template, create at viewport center (0.5, 0.5).
- L387 _public member_ `FVector2D Position = FVector2D::ZeroVector;` — `UPROPERTY()` — If OverridePosition is true and PreviewRendererId points to a valid preview renderer, place the lightcard at this normalized viewport coordinate (in range [0, 1]).
- L393 _public member_ `bool OverrideColor = false;` — `UPROPERTY()` — If true, override the default/template color for the actor if it's a lightcard.
- L400 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY()` — If OverrideColor is true and PreviewRendererId points to a valid preview renderer, use this color when creating a lightcard.
- L406 _public member_ `bool bIsLightCardFlag = false;` — `UPROPERTY()` — Whether this actor should be created as a flag if it's a lightcard.
- L413 _public member_ `int32 RequestId = -1;` — `UPROPERTY()` — An optional number that will be passed back in the RequestedActorsCreated response to tell apart the results of multiple requests.

#### struct `FRCWebSocketNDisplayActorDuplicateBody`  
`struct FRCWebSocketNDisplayActorDuplicateBody : public FRCRequest`  
_L420-446_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to duplicate one or more actors.
- L424 _public function_ `FRCWebSocketNDisplayActorDuplicateBody()`
- L432 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L438 _public member_ `TArray<FString> Actors;` — `UPROPERTY()` — The list of paths of actors to duplicate.
- L445 _public member_ `int32 RequestId = -1;` — `UPROPERTY()` — An optional number that will be passed back in the RequestedActorsCreated response to tell apart the results of multiple requests.

#### struct `FRCWebSocketStageAppClientObjectCreateBody`  
`struct FRCWebSocketStageAppClientObjectCreateBody : public FRCRequest`  
_L453-479_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to create an object whose lifetime will be bound to the lifetime of the requesting client's connection.
- L457 _public function_ `FRCWebSocketStageAppClientObjectCreateBody()`
- L465 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L471 _public member_ `TSubclassOf<UObject> ObjectClass;` — `UPROPERTY()` — The class of the object to create.
- L478 _public member_ `int32 RequestId = -1;` — `UPROPERTY()` — An optional number that will be passed back in the ClientObjectCreated response to tell apart the results of multiple requests.

#### struct `FRCWebSocketStageAppClientObjectDestroyBody`  
`struct FRCWebSocketStageAppClientObjectDestroyBody : public FRCRequest`  
_L486-512_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to destroy an object whose lifetime is bound to the lifetime of the requesting client's connection.
- L490 _public function_ `FRCWebSocketStageAppClientObjectDestroyBody()`
- L498 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L504 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The path of the object. Must be an object created using the stageapp.clientobject.create route.
- L511 _public member_ `int32 RequestId = -1;` — `UPROPERTY()` — An optional number that will be passed back in the RequestedClientObjectCreated response to tell apart the results of multiple requests.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Private/StageAppResponse.h` (Private)


#### struct `FRCPreviewRendererCreatedEvent`  
`struct FRCPreviewRendererCreatedEvent`  
_L12-32_
- reflection: `USTRUCT()`
- desc: Event sent to a client that created a renderer.
- L16 _public function_ `FRCPreviewRendererCreatedEvent() : Type(TEXT("PreviewRendererCreated"))`
- L25 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L31 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the new renderer

#### struct `FRCPreviewRenderCompletedEventActorPosition`  
`struct FRCPreviewRenderCompletedEventActorPosition`  
_L35-46_
- reflection: `USTRUCT()`
- L41 _public member_ `FString Path;` — `UPROPERTY()` — The actor's path.
- L45 _public member_ `FVector2D Position = FVector2D::ZeroVector;` — `UPROPERTY()` — The actor's position on the preview texture in coordinates normalized to the size of the preview render's texture.

#### struct `FRCPreviewRenderCompletedEvent`  
`struct FRCPreviewRenderCompletedEvent`  
_L52-102_
- reflection: `USTRUCT()`
- desc: Event sent to a client that created a renderer.
- L56 _public function_ `FRCPreviewRenderCompletedEvent() : Type(TEXT("PreviewRenderCompleted"))`
- L65 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L71 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the renderer that created the image.
- L77 _public member_ `FString ImageBase64 = "";` — `UPROPERTY()` — Base64 encoded JPEG data of the preview render.
- L83 _public member_ `FIntPoint Resolution = FIntPoint(1024, 1024);` — `UPROPERTY()` — The resolution of the image included with this message.
- L89 _public member_ `TArray<FRCPreviewRenderCompletedEventActorPosition> ActorPositions;` — `UPROPERTY()` — A list of projected positions within the preview render for each rendered actor.
- L95 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The last sequence number that the client sent during a stage actor drag operation on this renderer.
- L101 _public member_ `bool IsRealTimeDisabled = false;` — `UPROPERTY()` — If true, real-time preview rendering is disabled in the engine, which may prevent nDisplay previews and stage actor positions from updating correctly.

#### struct `FRCActorDragCancelled`  
`struct FRCActorDragCancelled`  
_L108-128_
- reflection: `USTRUCT()`
- desc: Event sent to a client when a drag operation is cancelled by the engine.
- L112 _public function_ `FRCActorDragCancelled() : Type(TEXT("ActorDragCancelled"))`
- L121 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L127 _public member_ `int32 RendererId = -1;` — `UPROPERTY()` — The ID of the renderer associated with the drag operation.

#### struct `FRCRequestedActorsCreated`  
`struct FRCRequestedActorsCreated`  
_L134-160_
- reflection: `USTRUCT()`
- desc: Event sent to a client when light cards were created at the request of the client.
- L138 _public function_ `FRCRequestedActorsCreated() : Type(TEXT("RequestedActorsCreated"))`
- L147 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L153 _public member_ `TArray<FString> ActorPaths;` — `UPROPERTY()` — The list of newly-created actors' paths.
- L159 _public member_ `int32 RequestId = -1;` — `UPROPERTY()` — The ID passed when the actors were created, or -1 if no ID was provided.

#### struct `FRCRequestedClientObjectCreated`  
`struct FRCRequestedClientObjectCreated`  
_L166-192_
- reflection: `USTRUCT()`
- desc: Event sent to a client when a client-bound object was created at the request of the client.
- L170 _public function_ `FRCRequestedClientObjectCreated() : Type(TEXT("RequestedClientObjectCreated"))`
- L179 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L185 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The list of newly-created object's path.
- L191 _public member_ `int32 RequestId = -1;` — `UPROPERTY()` — The ID passed when the actors were created, or -1 if no ID was provided.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Private/StageAppRouteHandler.h` (Private)


#### class `FStageAppRouteHandler`  
`class FStageAppRouteHandler`  
_L18-199_
- desc: Handler for Epic Stage App websocket requests.
- L98 _private typedef_ `using TClientIdToPerRendererDataMap = TMap<int32, FPerRendererData>;` — Map from renderer IDs created by a client (keyed by ID) to per-renderer data used by the handler.
- L102 _public prototype_ `void RegisterRoutes(IWebRemoteControlModule& WebRemoteControl);` — Registers the WebSocket routes with the provided WebRemoteControl module.
- L105 _public prototype_ `void UnregisterRoutes(IWebRemoteControlModule& WebRemoteControl);` — Unregisters the WebSocket routes with the provided WebRemoteControl module.
- L108 _public prototype_ `void RegisterEngineEvents();` — Registers events that require the engine to be initialized first.
- L111 _public prototype_ `void UnregisterEngineEvents();` — Unregisters events that required the engine to be initialized first.
- L115 _private prototype_ `void RegisterRoute(TUniquePtr<FRemoteControlWebsocketRoute> Route);` — Register a WebSocket route with the WebRemoteControl module.
- L118 _private prototype_ `void HandleWebSocketNDisplayPreviewRendererCreate(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles creating a preview renderer.
- L121 _private prototype_ `void HandleWebSocketNDisplayPreviewRendererSetRoot(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles setting the root actor of a renderer.
- L124 _private prototype_ `void HandleWebSocketNDisplayPreviewRendererConfigure(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles changing renderer settings.
- L127 _private prototype_ `void HandleWebSocketNDisplayPreviewRendererDestroy(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles destroying a preview renderer.
- L130 _private prototype_ `void HandleWebSocketNDisplayPreviewRender(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles rendering a preview.
- L133 _private prototype_ `void HandleWebSocketNDisplayPreviewActorDragBegin(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles beginning an actor drag operation.
- L136 _private prototype_ `void HandleWebSocketNDisplayPreviewActorDragMove(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles moving actors with a drag operation.
- L139 _private prototype_ `void HandleWebSocketNDisplayPreviewActorDragEnd(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles ending an actor drag operation.
- L142 _private prototype_ `void HandleWebSocketNDisplayPreviewActorCreate(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles creating an actor.
- L145 _private prototype_ `void HandleWebSocketStageAppActorsDuplicate(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles duplicating actors.
- L148 _private prototype_ `void HandleWebSocketStageAppClientObjectCreate(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles creating an object whose lifetime is tied to the lifetime of the requesting client's connection.
- L151 _private prototype_ `void HandleWebSocketStageAppClientObjectDestroy(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles destroying an object whose lifetime is tied to the lifetime of the requesting client's connection.
- L154 _private prototype_ `void HandleClientDisconnected(FGuid ClientId);` — Called when a client disconnects from the WebSocket server.
- L160 _private prototype_ `void OnTransactionStateChanged(const FTransactionContext& InTransactionContext, const ETransactionStateEventType InTransactionState);` — Called when the state of an editor transaction changes.
- L164 _private prototype_ `void ChangePreviewRendererSettings(const FGuid& ClientId, int32 RendererId, const FRCWebSocketNDisplayPreviewRendererSettings& NewSettings);` — Change the settings for a client's preview renderer.
- L167 _private prototype_ `FPerRendererData* GetClientPerRendererData(const FGuid& ClientId, int32 RendererId);` — Get the nDisplay preview rendering data for the given client and renderer ID, or null if it's an invalid client/renderer ID.
- L170 _private prototype_ `void DragActors(FPerRendererData& PreviewData, FVector2D DragPosition);` — Drag actors to the specified position.
- L173 _private prototype_ `bool TimeOutDrags(float DeltaTime);` — Check if any actor drag operations have timed out, and if so, end them.
- L176 _private prototype_ `void EndActorDrag(FPerRendererData& PreviewData, const FGuid& ClientId, int32 RendererId, bool bEndedByClient);` — End a client's actor drag operation.
- L179 _private prototype_ `void SetRendererRootActorPath(const int32 RendererId, const FString& RootActorPath);` — Set root actor via path.
- L183 _private member_ `IWebRemoteControlModule* RemoteControlModule = nullptr;` — The module for the WebSocket server for which this is handling routes.
- L186 _private member_ `TArray<TUniquePtr<FRemoteControlWebsocketRoute>> Routes;` — Routes this has registered with the WebSocket server.
- L189 _private member_ `TMap<FGuid, TClientIdToPerRendererDataMap> PerRendererDataMapsByClientId;` — Map from client GUID to preview renderer data maps for that client.
- L192 _private member_ `TMap<FGuid, TArray<UObject*>> BoundObjectsByClientId;` — Map from client GUID to objects bound to the lifetime of that client's connection.
- L195 _private member_ `class IImageWrapperModule* ImageWrapperModule = nullptr;` — Image wrapper module used to compress preview images.
- L198 _private member_ `FTSTicker::FDelegateHandle DragTimeoutTickerHandle;` — Handle for timing out drags.

#### struct `FStageAppRouteHandler::FPerRendererData`  
`struct FPerRendererData`  
_L22-95_
- desc: Data used for editing lightcard positions within the context of a preview.
- L24 _public prototype_ `FPerRendererData(int RendererId);`
- L27 _public member_ `TArray<FDisplayClusterWeakStageActorPtr> DraggedActors;` — The list of actors currently being dragged by this client. Empty if a drag is not in progress.
- L30 _public member_ `FDisplayClusterWeakStageActorPtr PrimaryActor;` — The actor to use as the origin point for the drag operation.
- L33 _public member_ `FVector2D LastDragPosition;` — The last position sent by a client during a drag operation.
- L36 _public member_ `bool bHasDragMovedRecently = false;` — If true, the dragged lightcards have moved since the last timeout check.
- L39 _public member_ `bool bIsRenderPending = false;` — If true, the client is currently waiting for a render to be completed.
- L43 _public member_ `FGuid TransactionId;` — The GUID of the current drag transaction.
- L48 _public prototype_ `FDisplayClusterLightCardEditorHelper& GetLightCardHelper();` — Get or create a FDisplayClusterLightCardEditorHelper for this client preview renderer.
- L51 _public prototype_ `const FRCWebSocketNDisplayPreviewRendererSettings& GetPreviewSettings() const;` — Get the preview settings to use for renders.
- L54 _public prototype_ `void SetPreviewSettings(const FRCWebSocketNDisplayPreviewRendererSettings& NewSettings);` — Change the preview settings to use for renders.
- L57 _public prototype_ `bool GetSceneViewInitOptions(FSceneViewInitOptions& ViewInitOptions, bool bApplyActorRotation = true);` — Get the scene view init options to be used for preview renders based on the stored settings.
- L60 _public prototype_ `void UpdateDragSequenceNumber(int64 ReceivedSequenceNumber);` — Update the sequence number if the provided one is higher than the previous.
- L63 _public prototype_ `int64 GetDragSequenceNumber() const;` — Get the highest sequence number received from the client during a drag operation.
- L66 _public prototype_ `ADisplayClusterRootActor* GetRootActor() const;` — Get DCRA from the scene that is used to render preview.
- L77 _public prototype_ `ADisplayClusterRootActor* GetRootActorProxy() const;` — Get the RootActorProxy that is used for rendering to the final texture. This actor is used because of special rendering rules that differ from the RootActor settings in the scene, which requires a separate RootActor instance to be created. For example: - DCRA in a scene may have settings that disable preview rendering (or even freeze it). But this app will always force this feature. - An app can have custom DisplayDevice settings. However, the DCRA of the scene cannot be modified on this side. - The app can have custom preview settings, such as "PreviewSceeenPercentage," to set its own image quality, etc.
- L81 _private prototype_ `void UpdateLightCardHelperSettings();` — Update LightCardHelper's settings based on the ones stored in PreviewSettings.
- L85 _private member_ `TSharedPtr<FDisplayClusterLightCardEditorHelper> LightCardHelper;` — Helper used to move light cards and project their coordinates.
- L88 _private member_ `FRCWebSocketNDisplayPreviewRendererSettings PreviewSettings;` — Settings used for generating previews.
- L91 _private member_ `int RendererId;` — The ID of the renderer with which this is associated.
- L94 _private member_ `int64 SequenceNumber = 0;` — Highest sequence number received from the client during a drag operation.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Public/StageAppLibrary.h` (Public)


#### class `UStageAppFunctionLibrary`  
`class UStageAppFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Generally useful Blueprint/remote functions for Epic Stage App integration.
- L21 _public prototype_ `static FString GetAPIVersion();` — `UFUNCTION(BlueprintPure, Category = "Development", meta = (BlueprintThreadSafe))` — Get the current semantic version for the stage app API as a formatted string.
- L25 _public prototype_ `static int32 GetRemoteControlWebInterfacePort();` — `UFUNCTION(BlueprintPure, Category = "Development", meta = (BlueprintThreadSafe))` — Get the port number used to access the remote control web interface for this engine instance.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Public/StageAppSettings.h` (Public)


#### class `UStageAppSettings`  
`class UStageAppSettings : public UDeveloperSettings`  
_L13-58_
- reflection: `UCLASS(config = Engine)`
- inherits: `UDeveloperSettings`
- desc: Global settings for Epic Stage App integration.
- L19 _public function_ `virtual FName GetContainerName() const`
- L24 _public function_ `virtual FName GetCategoryName() const`
- L29 _public function_ `virtual FName GetSectionName() const`
- L34 _public function_ `virtual FText GetSectionText() const`
- L44 _public member_ `FString DiscoveryEndpoint = "23` — `UPROPERTY(config, EditAnywhere, Category = "Epic Stage App")` — The IP endpoint to listen to for app discovery messages.
- L50 _public member_ `int32 DiscoveryPort = 6667;` — `UPROPERTY(config, EditAnywhere, Category = "Epic Stage App")` — The port to listen to for app discovery messages.
- L57 _public member_ `float DiscoverySocketWaitTime = 10.f;` — `UE_DEPRECATED(5.4, "This setting is no longer used.")` — `UPROPERTY(config, EditAnywhere, Category = "Epic Stage App")` — How many seconds to wait for app discovery messages.

### `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Public/StageAppVersion.h` (Public)


#### struct `FEpicStageAppAPIVersion`  
`struct FEpicStageAppAPIVersion`  
_L8-18_
- desc: Holds info about a version of the stage app API.
- L11 _public member_ `static const uint16 Major = 1;` — The major component of the current version.
- L14 _public member_ `static const uint16 Minor = 10;` — The minor component of the current version.
- L17 _public member_ `static const uint16 Patch = 0;` — The patch component of the current version.
