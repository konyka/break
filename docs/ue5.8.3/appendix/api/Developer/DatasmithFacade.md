# Developer / DatasmithFacade

- module root: `Source/Developer/Datasmith/DatasmithFacade`
- headers: 22; symbols: 913
- symbol kinds: class=49, delegate=1, enum=22, enumerator=114, function=161, macro=2, member=29, prototype=527, struct=7, typedef=1
- PrivateDependencyModuleNames: DatasmithExporter, Imath
- PublicDependencyModuleNames: Core, DatasmithCore, DirectLink

### `Source/Developer/Datasmith/DatasmithFacade/Private/DirectLink/DatasmithFacadeEndpointObserverImpl.h` (Private)


#### class `FDatasmithFacadeEndpointObserverImpl`  
`class FDatasmithFacadeEndpointObserverImpl : public DirectLink::IEndpointObserver`  
_L9-39_
- inherits: `DirectLink::IEndpointObserver`
- L12 _public function_ `virtual void OnStateChanged(const DirectLink::FRawInfo& RawInfo) override`
- L21 _public function_ `void RegisterOnStateChangedDelegate(FDatasmithFacadeEndpointObserver::OnStateChangedDelegate InOnStateChangedDelegate)`
- L29 _public function_ `void UnregisterOnStateChangedDelegate(FDatasmithFacadeEndpointObserver::OnStateChangedDelegate InOnStateChangedDelegate)`
- L38 _private member_ `FDatasmithFacadeEndpointObserver::OnStateChangedDelegate OnStateChangedPtr;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeActor.h` (Public)


#### class `FDatasmithFacadeActor`  
`class FDatasmithFacadeActor : public FDatasmithFacadeElement`  
_L11-207_
- inherits: `FDatasmithFacadeElement`
- L31 _public prototype_ `FDatasmithFacadeActor( const TCHAR* InElementName );`
- L35 _public function_ `virtual ~FDatasmithFacadeActor()`
- L37 _public prototype_ `void SetWorldTransform( const double InWorldMatrix[16], bool bRowMajor = false );`
- L42 _public function_ `void SetWorldTransform( const float InWorldMatrix[16], bool bRowMajor = false )`
- L55 _public prototype_ `void SetScale( double X, double Y, double Z );`
- L61 _public prototype_ `void GetScale( double& OutX, double& OutY, double& OutZ ) const;`
- L67 _public prototype_ `void SetRotation( double Pitch, double Yaw, double Roll );`
- L73 _public prototype_ `void GetRotation( double& OutPitch, double& OutYaw, double& OutRoll ) const;`
- L79 _public prototype_ `void SetRotation( double X, double Y, double Z, double W );`
- L86 _public prototype_ `void GetRotation( double& OutX, double& OutY, double& OutZ, double& OutW ) const;`
- L93 _public prototype_ `void SetTranslation( double X, double Y, double Z );`
- L99 _public prototype_ `void GetTranslation( double& OutX, double& OutY, double& OutZ ) const;`
- L106 _public prototype_ `void SetLayer( const TCHAR* InLayerName );` — Set the layer of the Datasmith actor.
- L111 _public prototype_ `const TCHAR* GetLayer() const;` — Get the layer of the Datasmith actor.
- L114 _public prototype_ `void AddTag( const TCHAR* InTag );` — Add a new tag to the Datasmith actor.
- L119 _public prototype_ `void ResetTags();` — Remove all Tags on the Actor element
- L122 _public prototype_ `int32 GetTagsCount() const;` — Get the number of tags attached to an Actor element
- L125 _public prototype_ `const TCHAR* GetTag( int32 TagIndex ) const;` — Get the 'TagIndex'th tag of an Actor element
- L130 _public prototype_ `bool IsComponent() const;` — Get whether or not the Datasmith actor is a component when used in a hierarchy.
- L133 _public prototype_ `void SetIsComponent( bool bInIsComponent );` — Set whether or not the Datasmith actor is a component when used in a hierarchy.
- L138 _public prototype_ `void AddChild( FDatasmithFacadeActor* InChildActorPtr` — Add a new child to the Datasmith actor.
- L143 _public prototype_ `int32 GetChildrenCount() const;` — Get the number of children on this actor
- L150 _public prototype_ `FDatasmithFacadeActor* GetNewChild( int32 InIndex );` — Returns a new FDatasmithFacadeActor pointing to the InIndex-th child of the mesh actor If there is no child at the given index, returned value is nullptr. The caller is responsible of deleting the returned object pointer.
- L154 _public prototype_ `void RemoveChild( FDatasmithFacadeActor* InChild );`
- L163 _public function_ `FDatasmithFacadeActor* GetNewParentActor() const` — Returns a new FDatasmithFacadeActor pointing to the parent Actor of the actor If there is no parent of if actor is directly under the scene root, the returned value is nullptr. The caller is responsible of deleting the returned object pointer.
- L169 _public prototype_ `void SetVisibility( bool bInVisibility );` — Get a mesh actor's visibility
- L174 _public prototype_ `bool GetVisibility() const;` — Set a mesh actor's visibility
- L176 _public prototype_ `void SetCastShadow( bool bInCastShadow );`
- L180 _public prototype_ `bool GetCastShadow() const;`
- L182 _public prototype_ `EActorType GetActorType() const;`
- L188 _protected prototype_ `explicit FDatasmithFacadeActor( const TSharedRef<IDatasmithActorElement>& InInternalActor );`
- L192 _protected prototype_ `static EActorType GetActorType( const TSharedPtr<const IDatasmithActorElement>& InActor );`
- L196 _protected prototype_ `static FDatasmithFacadeActor* GetNewFacadeActorFromSharedPtr( const TSharedPtr<IDatasmithActorElement>& InActor );`
- L201 _protected prototype_ `FTransform ConvertTransform( const double InSourceMatrix[16], bool bRowMajor ) const;` — Convert a source matrix into a Datasmith actor transform.
- L206 _protected prototype_ `TSharedRef<IDatasmithActorElement> GetDatasmithActorElement() const;`

#### enum `FDatasmithFacadeActor::EActorType`  
`enum class EActorType`  
_L16-29_
- L18 _public enumerator_ `DirectionalLight`
- L19 _public enumerator_ `AreaLight`
- L20 _public enumerator_ `EnvironmentLight`
- L21 _public enumerator_ `LightmassPortal`
- L22 _public enumerator_ `PointLight`
- L23 _public enumerator_ `SpotLight`
- L24 _public enumerator_ `StaticMeshActor`
- L25 _public enumerator_ `Camera`
- L26 _public enumerator_ `Actor`
- L27 _public enumerator_ `Decal`
- L28 _public enumerator_ `Unsupported`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeActorCamera.h` (Public)


#### class `FDatasmithFacadeActorCamera`  
`class FDatasmithFacadeActorCamera : public FDatasmithFacadeActor`  
_L9-123_
- inherits: `FDatasmithFacadeActor`
- L14 _public prototype_ `FDatasmithFacadeActorCamera( const TCHAR* InElementName );`
- L18 _public function_ `virtual ~FDatasmithFacadeActorCamera()`
- L21 _public prototype_ `void SetCameraPosition( double InX,` — Set the world position of the Datasmith camera actor.
- L28 _public prototype_ `void SetCameraRotation( double InForwardX,` — Set the world rotation of the Datasmith camera actor with the camera world forward and up directions.
- L38 _public prototype_ `void SetSensorWidth( float InSensorWidth` — Set the sensor width of the Datasmith camera.
- L43 _public prototype_ `float GetSensorWidth() const;` — Get camera sensor width
- L46 _public prototype_ `void SetAspectRatio( float InAspectRatio` — Set the aspect ratio of the Datasmith camera.
- L51 _public prototype_ `float GetAspectRatio() const;` — Get Datasmith camera aspect ratio (width/height)
- L54 _public prototype_ `void SetFocusDistance( float InTargetX,` — Set the Datasmith camera focus distance with the current camera world position and a target world position.
- L61 _public prototype_ `void SetFocusDistance( float InFocusDistance` — Set the Datasmith camera focus distance.
- L66 _public prototype_ `float GetFocusDistance() const;` — Get camera focus distance
- L69 _public prototype_ `void SetFocalLength( float InFocalLength` — Set the Datasmith camera focal length.
- L74 _public prototype_ `void SetFocalLength( float InFOV,` — Set the Datasmith camera focal length.
- L80 _public prototype_ `float GetFocalLength() const;` — Get camera focal length in millimeters
- L83 _public prototype_ `void SetLookAtActor( const TCHAR* InActorName` — Set the Datasmith camera look-at actor.
- L88 _public prototype_ `const TCHAR* GetLookAtActor() const;` — Get the Datasmith camera look-at actor.
- L91 _public prototype_ `void SetLookAtAllowRoll( bool bInAllow` — Set the Datasmith camera look-at roll allowed state.
- L96 _public prototype_ `bool GetLookAtAllowRoll() const;` — Get the Datasmith camera look-at actor.
- L99 _public prototype_ `bool GetEnableDepthOfField() const;` — The focus method of the camera, either None (no DoF) or Manual
- L102 _public prototype_ `void SetEnableDepthOfField( bool bInEnableDepthOfField );` — The focus method of the camera, either None (no DoF) or Manual
- L107 _public prototype_ `float GetFStop() const;` — Get camera FStop also known as FNumber
- L110 _public prototype_ `void SetFStop( float InFStop );` — Set camera FStop also known as FNumber
- L118 _protected prototype_ `FDatasmithFacadeActorCamera( const TSharedRef<IDatasmithCameraActorElement>& InInternalElement );`
- L122 _protected prototype_ `TSharedRef<IDatasmithCameraActorElement> GetDatasmithActorCameraElement() const;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeActorLight.h` (Public)


#### class `FDatasmithFacadeActorLight`  
`class FDatasmithFacadeActorLight : public FDatasmithFacadeActor`  
_L12-174_
- inherits: `FDatasmithFacadeActor`
- L15 _public function_ `virtual ~FDatasmithFacadeActorLight()`
- L18 _public prototype_ `bool IsEnabled() const;` — Return true on light enabled, false otherwise
- L21 _public prototype_ `void SetEnabled( bool bIsEnabled );` — Set enable property of the light
- L26 _public prototype_ `double GetIntensity() const;` — Get light intensity
- L29 _public prototype_ `void SetIntensity( double Intensity );` — Set light intensity
- L34 _public prototype_ `void GetColor( uint8& OutR, uint8& OutG, uint8& OutB, uint8& OutA ) const;` — Get light color in sRGB mode
- L42 _public prototype_ `void GetColor( float& OutR, float& OutG, float& OutB, float& OutA ) const;` — Get light color on linear mode
- L50 _public prototype_ `void SetColor( uint8 InR, uint8 InG, uint8 InB, uint8 InA );` — Set the Datasmith light sRGBA color.
- L58 _public prototype_ `void SetColor( float InR, float InG, float InB, float InA );` — Set the Datasmith light linear color.
- L66 _public prototype_ `double GetTemperature() const;` — Get the light temperature in Kelvin
- L69 _public prototype_ `void SetTemperature( double Temperature );` — Set the light temperature in Kelvin
- L74 _public prototype_ `bool GetUseTemperature() const;` — Get if the light color is controlled by temperature
- L77 _public prototype_ `void SetUseTemperature( bool bUseTemperature );` — Set if the light color is controlled by temperature
- L82 _public prototype_ `const TCHAR* GetIesFile() const;` — Get the path of the Ies definition file
- L84 _public prototype_ `void WriteIESFile( const TCHAR* InIESFileFolder, const TCHAR* InIESFileName, const TCHAR* InIESData );`
- L91 _public prototype_ `void SetIesFile( const TCHAR* IesFile );` — Set the path of the Ies definition file
- L96 _public prototype_ `bool GetUseIes() const;` — Set if this light is controlled by Ies definition file
- L99 _public prototype_ `void SetUseIes( bool bUseIes );` — Get if this light is controlled by Ies definition file
- L104 _public prototype_ `double GetIesBrightnessScale() const;` — Get the Ies brightness multiplier
- L107 _public prototype_ `void SetIesBrightnessScale( double IesBrightnessScale );` — Set the Ies brightness multiplier
- L112 _public prototype_ `bool GetUseIesBrightness() const;` — Get if the emissive amount of the ies is controlled by the brightness scale
- L115 _public prototype_ `void SetUseIesBrightness( bool bUseIesBrightness );` — Set if the emissive amount of the ies is controlled by the brightness scale
- L120 _public prototype_ `void GetIesRotation( float& OutX, float& OutY, float& OutZ, float& OutW ) const;` — Get the rotation applied to the IES shape in the form of quaternion members
- L128 _public prototype_ `void GetIesRotation( float& OutPitch, float& OutYaw, float& OutRoll ) const;` — Get the rotation applied to the IES shape in the form of euler angles
- L135 _public prototype_ `void SetIesRotation( float X, float Y, float Z, float W );` — Set the rotation to apply to the IES shape in Quaternion format
- L143 _public prototype_ `void SetIesRotation( float Pitch, float Yaw, float Roll );` — Set the rotation to apply to the IES shape from euler angles
- L154 _public prototype_ `FDatasmithFacadeMaterialID* GetNewLightFunctionMaterial();` — Returns a new FDatasmithFacadeMaterialID pointing to emissive material on this light If there is no child at the given index, returned value is nullptr. The caller is responsible of deleting the returned object pointer.
- L157 _public prototype_ `void SetLightFunctionMaterial( FDatasmithFacadeMaterialID& InMaterial );` — Set emissive material on this light
- L162 _public prototype_ `void SetLightFunctionMaterial( const TCHAR* InMaterialName );` — Set emissive material on this light
- L169 _protected prototype_ `FDatasmithFacadeActorLight( const TSharedRef<IDatasmithLightActorElement>& InInternalActor );`
- L173 _protected prototype_ `TSharedRef<IDatasmithLightActorElement> GetDatasmithLightActorElement() const;`

#### class `FDatasmithFacadePointLight`  
`class FDatasmithFacadePointLight : public FDatasmithFacadeActorLight`  
_L176-234_
- inherits: `FDatasmithFacadeActorLight`
- L188 _public prototype_ `FDatasmithFacadePointLight( const TCHAR* InElementName );`
- L192 _public function_ `virtual ~FDatasmithFacadePointLight()`
- L194 _public prototype_ `void SetIntensityUnits( EPointLightIntensityUnit InUnits );`
- L198 _public prototype_ `EPointLightIntensityUnit GetIntensityUnits() const;`
- L201 _public prototype_ `float GetSourceRadius() const;` — Get light radius, width in case of 2D light sources
- L204 _public prototype_ `void SetSourceRadius( float SourceRadius );` — Set light radius, width in case of 2D light sources
- L209 _public prototype_ `float GetSourceLength() const;` — Get light length only affects 2D shaped lights
- L212 _public prototype_ `void SetSourceLength( float SourceLength );` — Set light length only affects 2D shaped lights
- L217 _public prototype_ `float GetAttenuationRadius() const;` — Get attenuation radius in centimeters
- L220 _public prototype_ `void SetAttenuationRadius( float AttenuationRadius );` — Set attenuation radius in centimeters
- L227 _protected prototype_ `FDatasmithFacadePointLight( const TSharedRef<IDatasmithPointLightElement>& InInternalActor );`
- L233 _private prototype_ `TSharedRef<IDatasmithPointLightElement> GetDatasmithPointLightElement() const;`

#### enum `FDatasmithFacadePointLight::EPointLightIntensityUnit`  
`enum class EPointLightIntensityUnit`  
_L181-186_
- desc: Possible Datasmith point light intensity units. Copy of EDatasmithLightUnits from DatasmithCore DatasmithDefinitions.h.
- L183 _public enumerator_ `Unitless`
- L184 _public enumerator_ `Candelas`
- L185 _public enumerator_ `Lumens`

#### class `FDatasmithFacadeSpotLight`  
`class FDatasmithFacadeSpotLight: public FDatasmithFacadePointLight`  
_L236-271_
- inherits: `FDatasmithFacadePointLight`
- L239 _public prototype_ `FDatasmithFacadeSpotLight( const TCHAR* InElementName );`
- L243 _public function_ `virtual ~FDatasmithFacadeSpotLight()`
- L246 _public prototype_ `float GetInnerConeAngle() const;` — Get the inner cone angle for spot lights in degrees
- L249 _public prototype_ `void SetInnerConeAngle( float InnerConeAngle );` — Set the inner cone angle for spot lights in degrees
- L254 _public prototype_ `float GetOuterConeAngle() const;` — Get the outer cone angle for spot lights in degrees
- L257 _public prototype_ `void SetOuterConeAngle( float OuterConeAngle );` — Set the outer cone angle for spot lights in degrees
- L264 _protected prototype_ `FDatasmithFacadeSpotLight( const TSharedRef<IDatasmithSpotLightElement>& InInternalActor );`
- L270 _private prototype_ `TSharedRef<IDatasmithSpotLightElement> GetDatasmithSpotLightElement() const;`

#### class `FDatasmithFacadeDirectionalLight`  
`class FDatasmithFacadeDirectionalLight : public FDatasmithFacadeActorLight`  
_L273-288_
- inherits: `FDatasmithFacadeActorLight`
- L276 _public prototype_ `FDatasmithFacadeDirectionalLight( const TCHAR* InElementName );`
- L280 _public function_ `virtual ~FDatasmithFacadeDirectionalLight()`
- L285 _protected prototype_ `FDatasmithFacadeDirectionalLight( const TSharedRef<IDatasmithDirectionalLightElement>& InInternalActor );`

#### class `FDatasmithFacadeAreaLight`  
`class FDatasmithFacadeAreaLight : public FDatasmithFacadeSpotLight`  
_L293-360_
- inherits: `FDatasmithFacadeSpotLight`
- desc: An area light is an emissive shape (light shape) with a light component (light type)
- L296 _public prototype_ `FDatasmithFacadeAreaLight( const TCHAR* InElementName );`
- L300 _public function_ `virtual ~FDatasmithFacadeAreaLight()`
- L324 _public prototype_ `EAreaLightShape GetLightShape() const;` — Get the light shape Rectangle/Sphere/Disc/Cylinder
- L327 _public prototype_ `void SetLightShape( EAreaLightShape Shape );` — Set the light shape Rectangle/Sphere/Disc/Cylinder
- L332 _public prototype_ `void SetLightType( EAreaLightType LightType );` — Set the type of light for an area light: Point/Spot/Rect
- L336 _public prototype_ `EAreaLightType GetLightType() const;`
- L339 _public prototype_ `void SetWidth( float InWidth );` — Set the area light shape size on the Y axis
- L343 _public prototype_ `float GetWidth() const;`
- L346 _public prototype_ `void SetLength( float InLength );` — Set the area light shape size on the X axis
- L350 _public prototype_ `float GetLength() const;`
- L355 _protected prototype_ `FDatasmithFacadeAreaLight( const TSharedRef<IDatasmithAreaLightElement>& InInternalActor );`
- L359 _protected prototype_ `TSharedRef<IDatasmithAreaLightElement> GetDatasmithAreaLightElement() const;`

#### enum `FDatasmithFacadeAreaLight::EAreaLightShape`  
`enum class EAreaLightShape : uint8`  
_L304-311_
- desc: Possible Datasmith area light shapes. Copy of EDatasmithLightShape from DatasmithCore DatasmithDefinitions.h.
- L306 _public enumerator_ `Rectangle`
- L307 _public enumerator_ `Disc`
- L308 _public enumerator_ `Sphere`
- L309 _public enumerator_ `Cylinder`
- L310 _public enumerator_ `None`

#### enum `FDatasmithFacadeAreaLight::EAreaLightType`  
`enum class EAreaLightType`  
_L315-321_
- desc: Possible Datasmith area light types. Copy of EDatasmithAreaLightType from DatasmithCore DatasmithDefinitions.h.
- L317 _public enumerator_ `Point`
- L318 _public enumerator_ `Spot`
- L319 _public enumerator_ `IES_DEPRECATED`
- L320 _public enumerator_ `Rect`

#### class `FDatasmithFacadeLightmassPortal`  
`class FDatasmithFacadeLightmassPortal : public FDatasmithFacadePointLight`  
_L367-382_
- inherits: `FDatasmithFacadePointLight`
- desc: Represents a ALightmassPortal Use the actor scale to drive the portal dimensions
- L370 _public prototype_ `FDatasmithFacadeLightmassPortal( const TCHAR* InElementName );`
- L374 _public function_ `virtual ~FDatasmithFacadeLightmassPortal()`
- L379 _protected prototype_ `FDatasmithFacadeLightmassPortal( const TSharedRef<IDatasmithLightmassPortalElement>& InInternalActor );`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeActorMesh.h` (Public)


#### class `FDatasmithFacadeActorMesh`  
`class FDatasmithFacadeActorMesh : public FDatasmithFacadeActor`  
_L10-71_
- inherits: `FDatasmithFacadeActor`
- L15 _public prototype_ `FDatasmithFacadeActorMesh( const TCHAR* InElementName`
- L19 _public function_ `virtual ~FDatasmithFacadeActorMesh()`
- L22 _public prototype_ `void SetMesh( const TCHAR* InMeshName` — Set the static mesh of the Datasmith mesh actor.
- L27 _public prototype_ `const TCHAR* GetMeshName() const;` — Get the name of the StaticMesh associated with the actor
- L30 _public prototype_ `void AddMaterialOverride( const TCHAR* MaterialName` — Adds a new material override to the Actor Element
- L36 _public prototype_ `void AddMaterialOverride( FDatasmithFacadeMaterialID& Material );` — Adds a new material override to the Actor Element
- L41 _public prototype_ `int32 GetMaterialOverridesCount() const;` — Get the amount of material overrides on this mesh
- L48 _public prototype_ `FDatasmithFacadeMaterialID* GetNewMaterialOverride( int32 MaterialOverrideIndex );` — Returns a new FDatasmithFacadeMaterialID pointing to the i-th material override of this actor. If there is no child at the given index, returned value is nullptr. The caller is responsible of deleting the returned object pointer.
- L53 _public prototype_ `void RemoveMaterialOverride( FDatasmithFacadeMaterialID& Material );` — Remove material from the Actor Element
- L60 _public prototype_ `void ResetMaterialOverrides();` — Remove all material overrides from the Actor Element.
- L66 _protected prototype_ `FDatasmithFacadeActorMesh( const TSharedRef<IDatasmithMeshActorElement>& InInternalElement );`
- L70 _protected prototype_ `TSharedRef<IDatasmithMeshActorElement> GetDatasmithMeshActorElement() const;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeAnimation.h` (Public)


#### enum `EDatasmithFacadeCurveInterpMode`  
`enum class EDatasmithFacadeCurveInterpMode`  
_L7-12_
- L9 _public enumerator_ `Linear`
- L10 _public enumerator_ `Constant`
- L11 _public enumerator_ `Cubic`

#### enum `EDatasmithFacadeAnimationTransformType`  
`enum class EDatasmithFacadeAnimationTransformType`  
_L14-19_
- L16 _public enumerator_ `Translation`
- L17 _public enumerator_ `Rotation`
- L18 _public enumerator_ `Scale`

#### enum `EDatasmithFacadeElementAnimationSubType`  
`enum class EDatasmithFacadeElementAnimationSubType : uint64`  
_L21-27_
- L23 _public enumerator_ `BaseAnimation = 0`
- L24 _public enumerator_ `TransformAnimation = 1 << 0`
- L25 _public enumerator_ `VisibilityAnimation = 1 << 1`
- L26 _public enumerator_ `SubsequenceAnimation = 1 << 2`

#### enum `EDatasmithFacadeCompletionMode`  
`enum class EDatasmithFacadeCompletionMode : uint8`  
_L29-34_
- L31 _public enumerator_ `KeepState`
- L32 _public enumerator_ `RestoreState`
- L33 _public enumerator_ `ProjectDefault`

#### enum `EDatasmithFacadeTransformChannels`  
`enum class EDatasmithFacadeTransformChannels : uint16`  
_L36-56_
- L38 _public enumerator_ `None = 0x000`
- L40 _public enumerator_ `TranslationX = 0x001`
- L41 _public enumerator_ `TranslationY = 0x002`
- L42 _public enumerator_ `TranslationZ = 0x004`
- L43 _public enumerator_ `Translation = TranslationX | TranslationY | TranslationZ`
- L45 _public enumerator_ `RotationX = 0x008`
- L46 _public enumerator_ `RotationY = 0x010`
- L47 _public enumerator_ `RotationZ = 0x020`
- L48 _public enumerator_ `Rotation = RotationX | RotationY | RotationZ`
- L50 _public enumerator_ `ScaleX = 0x040`
- L51 _public enumerator_ `ScaleY = 0x080`
- L52 _public enumerator_ `ScaleZ = 0x100`
- L53 _public enumerator_ `Scale = ScaleX | ScaleY | ScaleZ`
- L55 _public enumerator_ `All = Translation | Rotation | Scale`

#### class `FDatasmithFacadeBaseAnimation`  
`class FDatasmithFacadeBaseAnimation : public FDatasmithFacadeElement`  
_L58-78_
- inherits: `FDatasmithFacadeElement`
- L61 _public prototype_ `bool IsSubType( const EDatasmithFacadeElementAnimationSubType AnimSubType ) const;`
- L64 _public prototype_ `void SetCompletionMode(EDatasmithFacadeCompletionMode CompletionMode);` — Set how the actor should behave once its animation completes
- L67 _public prototype_ `EDatasmithFacadeCompletionMode GetCompletionMode() const;` — Get how the actor behaves once this animation is complete
- L73 _protected prototype_ `explicit FDatasmithFacadeBaseAnimation( const TSharedRef<IDatasmithBaseAnimationElement>& InInternalAnimation );`
- L77 _protected prototype_ `TSharedRef<IDatasmithBaseAnimationElement> GetDatasmithBaseAnimation() const;`

#### class `FDatasmithFacadeTransformAnimation`  
`class FDatasmithFacadeTransformAnimation : public FDatasmithFacadeBaseAnimation`  
_L80-118_
- inherits: `FDatasmithFacadeBaseAnimation`
- L83 _public prototype_ `FDatasmithFacadeTransformAnimation(const TCHAR* InName);`
- L86 _public prototype_ `void AddFrame(EDatasmithFacadeAnimationTransformType TransformType, int32 FrameNumber, float X, float Y, float Z);` — Add a frame of the given transform type to the animation
- L89 _public prototype_ `int32 GetFramesCount(EDatasmithFacadeAnimationTransformType TransformType) const;` — Return the number of frames of the given transform type in the animation
- L92 _public prototype_ `void SetCurveInterpMode(EDatasmithFacadeAnimationTransformType TransformType, EDatasmithFacadeCurveInterpMode CurveInterpMode);` — Set the interpolation mode of the given transform type in the animation
- L95 _public prototype_ `EDatasmithFacadeCurveInterpMode GetCurveInterpMode(EDatasmithFacadeAnimationTransformType TransformType) const;` — Get the interpolation mode of the given transform type in the animation
- L98 _public prototype_ `void GetFrame(EDatasmithFacadeAnimationTransformType TransformType, int32 Index, int32& OutFrameNumber, double& OutX, double& OutY, double& OutZ) const;` — Return the frame of the given transform type at the given index or an invalid frame if the index was out of bounds
- L101 _public prototype_ `void RemoveFrame(EDatasmithFacadeAnimationTransformType TransformType, int32 Index);` — Remove the frame of the given transform type at the given index from the animation
- L104 _public prototype_ `EDatasmithFacadeTransformChannels GetEnabledTransformChannels() const;` — Gets which channels of this animation will be moved to the animation assets or serialized. All channels are enabled by default
- L107 _public prototype_ `void SetEnabledTransformChannels(EDatasmithFacadeTransformChannels Channels);` — Sets which channels of this animation will be moved to the animation assets or serialized. All channels are enabled by default
- L113 _protected prototype_ `explicit FDatasmithFacadeTransformAnimation( const TSharedRef<IDatasmithTransformAnimationElement>& InInternalAnimation );`
- L117 _protected prototype_ `TSharedRef<IDatasmithTransformAnimationElement> GetDatasmithTransformAnimation() const;`

#### class `FDatasmithFacadeVisibilityAnimation`  
`class FDatasmithFacadeVisibilityAnimation : public FDatasmithFacadeBaseAnimation`  
_L120-158_
- inherits: `FDatasmithFacadeBaseAnimation`
- L123 _public prototype_ `FDatasmithFacadeVisibilityAnimation(const TCHAR* InName);`
- L126 _public prototype_ `void AddFrame(int32 FrameNumber, bool bVisible);` — Add a frame to the animation
- L129 _public prototype_ `int32 GetFramesCount() const;` — Return the number of frames of the animation
- L132 _public prototype_ `void SetCurveInterpMode(EDatasmithFacadeCurveInterpMode CurveInterpMode);` — Set the interpolation mode of the animation
- L135 _public prototype_ `EDatasmithFacadeCurveInterpMode GetCurveInterpMode() const;` — Get the interpolation mode of the animation
- L138 _public prototype_ `void GetFrame(int32 Index, int32& OutFrameNumber, bool& bOutVisible) const;` — Return the frame of the animation at the given index or an invalid frame if the index was out of bounds
- L141 _public prototype_ `void RemoveFrame(int32 Index);` — Remove the frame at the given index from the animation
- L144 _public prototype_ `void SetPropagateToChildren(bool bPropagate);` — Sets whether this animation will be duplicated to all children (recursively) when imported
- L147 _public prototype_ `bool GetPropagateToChildren() const;` — Gets whether this animation will be duplicated to all children (recursively) when imported
- L153 _protected prototype_ `explicit FDatasmithFacadeVisibilityAnimation( const TSharedRef<IDatasmithVisibilityAnimationElement>& InInternalAnimation );`
- L157 _protected prototype_ `TSharedRef<IDatasmithVisibilityAnimationElement> GetDatasmithVisibilityAnimation() const;`

#### class `FDatasmithFacadeSubsequenceAnimation`  
`class FDatasmithFacadeSubsequenceAnimation : public FDatasmithFacadeBaseAnimation`  
_L162-200_
- inherits: `FDatasmithFacadeBaseAnimation`
- L165 _public prototype_ `FDatasmithFacadeSubsequenceAnimation(const TCHAR* InName);`
- L168 _public prototype_ `int32 GetStartTime() const;` — Get the frame where the subsequence starts
- L171 _public prototype_ `void SetStartTime(int32 InFrameNumber);` — Set the frame where the subsequence starts
- L174 _public prototype_ `int32 GetDuration() const;` — Get the subsequence duration in number of frames
- L177 _public prototype_ `void SetDuration(int32 InDuration);` — Set the subsequence duration in number of frames
- L180 _public prototype_ `float GetTimeScale() const;` — Get the time scale used for the subsequence
- L183 _public prototype_ `void SetTimeScale(float InTimeScale);` — Set the time scale used for the subsequence
- L186 _public prototype_ `FDatasmithFacadeLevelSequence* GetNewSubsequence() const;` — Get a pointer to the subsequence that this element references
- L189 _public prototype_ `void SetSubsequence(FDatasmithFacadeLevelSequence* InSubsequence);` — Set the subsequence that this element references
- L195 _protected prototype_ `explicit FDatasmithFacadeSubsequenceAnimation( const TSharedRef<IDatasmithSubsequenceAnimationElement>& InInternalAnimation );`
- L199 _protected prototype_ `TSharedRef<IDatasmithSubsequenceAnimationElement> GetDatasmithSubsequenceAnimation() const;`

#### class `FDatasmithFacadeLevelSequence`  
`class FDatasmithFacadeLevelSequence : public FDatasmithFacadeElement`  
_L202-256_
- inherits: `FDatasmithFacadeElement`
- L205 _public prototype_ `FDatasmithFacadeLevelSequence(const TCHAR* InName);`
- L208 _public prototype_ `const TCHAR* GetFile() const;` — Get the output filename, it can be absolute or relative to the scene file
- L211 _public prototype_ `void SetFile(const TCHAR* InFile);` — Set the output filename, it can be absolute or relative to the scene file
- L214 _public prototype_ `void GetFileHash(TCHAR OutBuffer[33], size_t BufferSize) const;` — Return a MD5 hash of the content of the Level Sequence Element. Used in CalculateElementHash to quickly identify Element with identical content
- L217 _public prototype_ `void SetFileHash(const TCHAR* Hash);` — Set the MD5 hash of the Level Sequence file. This should be a hash of its content.
- L220 _public prototype_ `float GetFrameRate() const;` — Gets the frame rate for the animations in the level sequence
- L223 _public prototype_ `void SetFrameRate(float FramePerSecs);` — Sets the frame rate for the animations in the level sequence
- L230 _public prototype_ `void AddAnimation(FDatasmithFacadeTransformAnimation* InAnimation);` — Adds an animation to the level sequence. @param InAnimation the animation to add
- L233 _public prototype_ `int32 GetAnimationsCount() const;` — Returns the number of animations in the level sequence
- L236 _public prototype_ `FDatasmithFacadeTransformAnimation* GetNewTransformAnimation(int32 InIndex);` — Returns the animation using this index
- L237 _public prototype_ `FDatasmithFacadeVisibilityAnimation* GetNewVisibilityAnimation(int32 InIndex);`
- L238 _public prototype_ `FDatasmithFacadeSubsequenceAnimation* GetNewSubsequenceAnimation(int32 InIndex);`
- L245 _public prototype_ `void RemoveAnimation(FDatasmithFacadeBaseAnimation* InAnimation);` — Removes an animation from the level sequence. @param InAnimation the animation to remove
- L251 _protected prototype_ `explicit FDatasmithFacadeLevelSequence( const TSharedRef<IDatasmithLevelSequenceElement>& InInternalLevelSequence );`
- L255 _protected prototype_ `TSharedRef<IDatasmithLevelSequenceElement> GetDatasmithLevelSequence() const;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeDecal.h` (Public)


#### class `FDatasmithFacadeActorDecal`  
`class FDatasmithFacadeActorDecal : public FDatasmithFacadeActor`  
_L9-46_
- inherits: `FDatasmithFacadeActor`
- L14 _public prototype_ `FDatasmithFacadeActorDecal( const TCHAR* InElementName`
- L18 _public function_ `virtual ~FDatasmithFacadeActorDecal()`
- L21 _public prototype_ `void GetDimensions(double& OutX, double& OutY, double& OutZ) const;` — Get the Decal element size
- L24 _public prototype_ `void SetDimensions(double InX, double InY, double InZ);` — Set the Decal element size
- L27 _public prototype_ `const TCHAR* GetDecalMaterialPathName() const;` — Get the path name of the Material associated with the actor
- L30 _public prototype_ `void SetDecalMaterialPathName(const TCHAR*);` — Set the path name of the Material that the Decal actor uses
- L33 _public prototype_ `int32 GetSortOrder() const;` — Get the order in which Decal element is rendered
- L36 _public prototype_ `void SetSortOrder(int32);` — Set the order in which decal elements are rendered.  Higher values draw later (on top)
- L41 _protected prototype_ `FDatasmithFacadeActorDecal( const TSharedRef<IDatasmithDecalActorElement>& InInternalActor );`
- L45 _protected prototype_ `TSharedRef<IDatasmithDecalActorElement> GetDatasmithDecalActorElement() const;`

#### class `FDatasmithFacadeDecalMaterial`  
`class FDatasmithFacadeDecalMaterial : public FDatasmithFacadeBaseMaterial`  
_L48-81_
- inherits: `FDatasmithFacadeBaseMaterial`
- L54 _public prototype_ `FDatasmithFacadeDecalMaterial( const TCHAR* InElementName`
- L58 _public function_ `virtual ~FDatasmithFacadeDecalMaterial()`
- L61 _public prototype_ `const TCHAR* GetDiffuseTexturePathName() const;` — Get path name of the diffuse texture associated with the material
- L64 _public prototype_ `void SetDiffuseTexturePathName(const TCHAR* DiffuseTexturePathName);` — Set path name of the diffuse texture associated with the material
- L67 _public prototype_ `const TCHAR* GetNormalTexturePathName() const;` — Get path name of the normal texture associated with the material
- L70 _public prototype_ `void SetNormalTexturePathName(const TCHAR* NormalTexturePathName);` — Set path name of the normal texture associated with the material
- L76 _protected prototype_ `FDatasmithFacadeDecalMaterial( const TSharedRef<IDatasmithDecalMaterialElement>& InMaterialRef );`
- L80 _protected prototype_ `TSharedRef<IDatasmithDecalMaterialElement> GetDatasmithDecalMaterial() const;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeElement.h` (Public)


#### class `FDatasmithFacadeElement`  
`class FDatasmithFacadeElement`  
_L10-112_
- L27 _public prototype_ `static void SetCoordinateSystemType( ECoordinateSystemType InWorldCoordinateSystemType` — Set the coordinate system type of the world geometries and transforms.
- L35 _public prototype_ `static void SetWorldUnitScale( float InWorldUnitScale` — Set the scale factor from world units to Datasmith centimeters. If the given value is too close to 0, it is clamped to SMALL_NUMBER value.
- L39 _public function_ `virtual ~FDatasmithFacadeElement()`
- L42 _public prototype_ `static void GetStringHash( const TCHAR* InString, TCHAR OutBuffer[33], size_t BufferSize );` — Hash the given InString and fills the OutBuffer up to the BufferSize. A string hash has 32 character (+ null character).
- L45 _public prototype_ `void SetName( const TCHAR* InElementName` — Set the Datasmith element name.
- L50 _public prototype_ `const TCHAR* GetName() const;` — Return the Datasmith element name.
- L53 _public prototype_ `void SetLabel( const TCHAR* InElementLabel` — Set the Datasmith element label.
- L58 _public prototype_ `const TCHAR* GetLabel() const;` — Return the Datasmith element label.
- L64 _protected prototype_ `template<bool kIsForward, bool kIsDirection, typename Vec_t> static Vec_t Convert(const Vec_t& V);`
- L66 _protected prototype_ `static FVector ConvertDirection (const FVector& In);`
- L67 _protected prototype_ `static FVector ConvertBackDirection(const FVector& In);`
- L68 _protected prototype_ `static FVector ConvertPosition (const FVector& In);`
- L69 _protected prototype_ `static FVector ConvertBackPosition (const FVector& In);`
- L71 _protected prototype_ `static FVector ConvertDirection (double InX, double InY, double InZ);`
- L72 _protected prototype_ `static FVector ConvertBackDirection(double InX, double InY, double InZ);`
- L73 _protected prototype_ `static FVector ConvertPosition (double InX, double InY, double InZ);`
- L74 _protected prototype_ `static FVector ConvertBackPosition (double InX, double InY, double InZ);`
- L76 _protected prototype_ `static FVector3f ConvertDirection (const FVector3f& In);`
- L77 _protected prototype_ `static FVector3f ConvertBackDirection(const FVector3f& In);`
- L78 _protected prototype_ `static FVector3f ConvertPosition (const FVector3f& In);`
- L79 _protected prototype_ `static FVector3f ConvertBackPosition (const FVector3f& In);`
- L81 _protected prototype_ `static FVector3f ConvertDirection (float InX, float InY, float InZ);`
- L82 _protected prototype_ `static FVector3f ConvertBackDirection(float InX, float InY, float InZ);`
- L83 _protected prototype_ `static FVector3f ConvertPosition (float InX, float InY, float InZ);`
- L84 _protected prototype_ `static FVector3f ConvertBackPosition (float InX, float InY, float InZ);`
- L86 _protected function_ `static FVector ConvertTranslation(FVector const& InVertex)`
- L87 _protected function_ `static FVector3f ConvertTranslation(FVector3f const& InVertex)`
- L91 _protected prototype_ `virtual void ExportAsset( FString const& InAssetFolder` — Build and export the Datasmith scene element asset when required. This must be done before building a Datasmith scene element.
- L95 _protected function_ `TSharedRef<IDatasmithElement>& GetDatasmithElement()`
- L97 _protected function_ `const TSharedRef<IDatasmithElement>& GetDatasmithElement() const`
- L101 _protected prototype_ `FDatasmithFacadeElement( const TSharedRef<IDatasmithElement>& InElement );`
- L106 _protected member_ `static ECoordinateSystemType WorldCoordinateSystemType;` — Coordinate system type of the world geometries and transforms.
- L109 _protected member_ `static float WorldUnitScale;` — Scale factor from world units to Datasmith centimeters.
- L111 _protected member_ `TSharedRef<IDatasmithElement> InternalDatasmithElement;`

#### enum `FDatasmithFacadeElement::ECoordinateSystemType`  
`enum class ECoordinateSystemType`  
_L17-22_
- desc: Possible coordinate system types.
- L19 _public enumerator_ `LeftHandedYup` — left-handed Y-up coordinate system: Cinema 4D
- L20 _public enumerator_ `LeftHandedZup` — left-handed Z-up coordinate system: Unreal native
- L21 _public enumerator_ `RightHandedZup` — right-handed Z-up coordinate system: Revit

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeKeyValueProperty.h` (Public)


#### class `FDatasmithFacadeKeyValueProperty`  
`class FDatasmithFacadeKeyValueProperty : public FDatasmithFacadeElement`  
_L10-61_
- inherits: `FDatasmithFacadeElement`
- L23 _public prototype_ `FDatasmithFacadeKeyValueProperty( const TCHAR* InName );`
- L25 _public function_ `virtual ~FDatasmithFacadeKeyValueProperty()`
- L28 _public function_ `EKeyValuePropertyType GetPropertyType() const` — Get the type of this property
- L34 _public function_ `void SetPropertyType( EKeyValuePropertyType InType )` — Set the type of this property
- L40 _public function_ `const TCHAR* GetValue() const` — Get the value of this property
- L46 _public function_ `void SetValue( const TCHAR* Value )` — Sets the value of this property
- L55 _protected prototype_ `FDatasmithFacadeKeyValueProperty( const TSharedRef<IDatasmithKeyValueProperty>& InKeyValueProperty );`
- L57 _protected function_ `TSharedRef<IDatasmithKeyValueProperty> GetDatasmithKeyValueProperty() const`

#### enum `FDatasmithFacadeKeyValueProperty::EKeyValuePropertyType`  
`enum class EKeyValuePropertyType`  
_L13-21_
- L15 _public enumerator_ `String`
- L16 _public enumerator_ `Color`
- L17 _public enumerator_ `Float`
- L18 _public enumerator_ `Bool`
- L19 _public enumerator_ `Texture`
- L20 _public enumerator_ `Vector`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeLog.h` (Public)


#### class `FDatasmithFacadeLog`  
`class FDatasmithFacadeLog`  
_L11-40_
- L15 _public prototype_ `FDatasmithFacadeLog();`
- L18 _public prototype_ `void AddLine( const TCHAR* InLine` — Append a text line to the log string.
- L23 _public prototype_ `void MoreIndentation();` — Add one level of indentation for further logged text lines.
- L26 _public prototype_ `void LessIndentation();` — Remove one level of indentation for further logged text lines.
- L29 _public prototype_ `void WriteFile( const TCHAR* InFilePath` — Write the multi-line log string into a text file.
- L36 _private member_ `FString Log;` — Multi-line log string.
- L39 _private member_ `int LineIndentation;` — Number of levels of indentation for logged text lines.

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithFacade, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithFacade, Log, All);`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeMaterial.h` (Public)


#### class `FDatasmithFacadeBaseMaterial`  
`class FDatasmithFacadeBaseMaterial : public FDatasmithFacadeElement`  
_L11-41_
- inherits: `FDatasmithFacadeElement`
- L23 _public prototype_ `EDatasmithMaterialType GetDatasmithMaterialType() const;`
- L28 _protected prototype_ `FDatasmithFacadeBaseMaterial( const TSharedRef<IDatasmithBaseMaterialElement>& BaseMaterialElement );`
- L32 _protected prototype_ `static EDatasmithMaterialType GetDatasmithMaterialType( const TSharedRef<IDatasmithBaseMaterialElement>& InMaterial );`
- L36 _protected prototype_ `TSharedRef<IDatasmithBaseMaterialElement> GetDatasmithBaseMaterial() const;`
- L38 _protected prototype_ `static FDatasmithFacadeBaseMaterial* GetNewFacadeBaseMaterialFromSharedPtr( const TSharedPtr<IDatasmithBaseMaterialElement>& InMaterial );`

#### enum `FDatasmithFacadeBaseMaterial::EDatasmithMaterialType`  
`enum class EDatasmithMaterialType`  
_L15-21_
- L17 _public enumerator_ `MaterialInstance`
- L18 _public enumerator_ `UEPbrMaterial`
- L19 _public enumerator_ `DecalMaterial`
- L20 _public enumerator_ `Unsupported`

#### class `FDatasmithFacadeMaterialInstance`  
`class FDatasmithFacadeMaterialInstance : public FDatasmithFacadeBaseMaterial`  
_L43-165_
- inherits: `FDatasmithFacadeBaseMaterial`
- L76 _public prototype_ `FDatasmithFacadeMaterialInstance( const TCHAR* InElementName );`
- L80 _public function_ `virtual ~FDatasmithFacadeMaterialInstance()`
- L82 _public prototype_ `EMaterialInstanceType GetMaterialType() const;`
- L84 _public prototype_ `void SetMaterialType( EMaterialInstanceType InMaterialInstanceType );`
- L88 _public prototype_ `EMaterialInstanceQuality GetQuality() const;`
- L90 _public prototype_ `void SetQuality( EMaterialInstanceQuality InQuality );`
- L95 _public prototype_ `const TCHAR* GetCustomMaterialPathName() const;` — Get the material path name used when material type is set to Custom
- L98 _public prototype_ `void SetCustomMaterialPathName( const TCHAR* InPathName );` — Set the material path name used when material type is set to Custom
- L103 _public prototype_ `void AddColor( const TCHAR* InPropertyName,` — Add a Datasmith material sRGBA color property.
- L121 _public prototype_ `void AddTexture( const TCHAR* InPropertyName,` — Add a Datasmith material texture property.
- L127 _public prototype_ `void AddString( const TCHAR* InPropertyName,` — Add a Datasmith material string property.
- L133 _public prototype_ `void AddFloat( const TCHAR* InPropertyName,` — Add a Datasmith material float property.
- L139 _public prototype_ `void AddBoolean( const TCHAR* InPropertyName,` — Add a Datasmith material boolean property.
- L144 _public prototype_ `int32 GetPropertiesCount() const;`
- L147 _public prototype_ `FDatasmithFacadeKeyValueProperty* GetNewProperty( int32 PropertyIndex ) const;` — Returns a new FDatasmithFacadeKeyValueProperty pointing to the KeyValueProperty at the given index, the returned value must be deleted after used, can be nullptr.
- L152 _public prototype_ `FDatasmithFacadeKeyValueProperty* GetNewPropertyByName( const TCHAR* PropertyName ) const;` — Returns a new FDatasmithFacadeKeyValueProperty pointing to the KeyValueProperty with the given name, the returned value must be deleted after used, can be nullptr.
- L160 _protected prototype_ `FDatasmithFacadeMaterialInstance( const TSharedRef<IDatasmithMaterialInstanceElement>& InMaterialRef );`
- L164 _protected prototype_ `TSharedRef<IDatasmithMaterialInstanceElement> GetDatasmithMaterialInstance() const;`

#### enum `FDatasmithFacadeMaterialInstance::EMaterialInstanceType`  
`enum class EMaterialInstanceType`  
_L51-64_
- desc: Possible Datasmith material types, from EDatasmithMaterialInstanceType in DatasmithDefinitions.h
- L53 _public enumerator_ `Auto`
- L54 _public enumerator_ `Opaque`
- L55 _public enumerator_ `Transparent`
- L56 _public enumerator_ `ClearCoat`
- L57 _public enumerator_ `Custom`
- L59 _public enumerator_ `CutOut` — Material has a transparent cutout map
- L60 _public enumerator_ `Emissive`
- L61 _public enumerator_ `Decal`
- L63 _public enumerator_ `Count` — Dummy element to count the number of types

#### enum `FDatasmithFacadeMaterialInstance::EMaterialInstanceQuality`  
`enum class EMaterialInstanceQuality : uint8`  
_L66-72_
- L68 _public enumerator_ `High`
- L69 _public enumerator_ `Low`
- L71 _public enumerator_ `Count` — Dummy element to count the number of qualities

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeMaterialID.h` (Public)


#### class `FDatasmithFacadeMaterialID`  
`class FDatasmithFacadeMaterialID : public FDatasmithFacadeElement`  
_L9-34_
- inherits: `FDatasmithFacadeElement`
- L13 _public prototype_ `FDatasmithFacadeMaterialID( const TCHAR* MaterialIDName );`
- L17 _public function_ `virtual ~FDatasmithFacadeMaterialID()`
- L19 _public prototype_ `void SetId( int32 Id );`
- L23 _public prototype_ `int32 GetId() const;`
- L29 _protected prototype_ `FDatasmithFacadeMaterialID( const TSharedRef<IDatasmithMaterialIDElement>& InMaterialElement );`
- L33 _protected prototype_ `TSharedRef<IDatasmithMaterialIDElement> GetMaterialIDElement() const;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeMaterialsUtils.h` (Public)


#### class `FDatasmithFacadeMaterialsUtils`  
`class FDatasmithFacadeMaterialsUtils`  
_L19-130_
- L23 _public prototype_ `FDatasmithFacadeMaterialsUtils() = delete;` — This is a static only class.
- L72 _public prototype_ `static FDatasmithFacadeMaterialExpressionTexture* CreateNewFacadeTextureExpression( FDatasmithFacadeUEPbrMaterial& MaterialElement, const TCHAR* ParameterName, const TCHAR* TextureMapPath, const FUVEditParameters& UVParameters );` — Generate material expressions on a given DatasmithUEPbrMaterialElement to output a texture with UV settings applied to it The returned pointer must be deleted after use. @param MaterialElement		The UEPbrMaterialElement on which to create the material expressions @param ParameterName			The display name for the Texture expression @param TextureMapPath		The texture to use for the Texture expression @param UVParameters			The UVEditParameters to apply @return						Texture expression with UVEdit applied to it; nullptr if no TextureMapPath is specified
- L120 _public prototype_ `static FDatasmithFacadeMaterialExpression* CreateNewFacadeWeightedMaterialExpression( FDatasmithFacadeUEPbrMaterial& MaterialElement, const TCHAR* ParameterName, FWeightedMaterialExpressionParameters& WeightedExpressionParameter );` — Generate material expressions on a given FDatasmithFacadeUEPbrMaterial that output a color or scalar interpolated with a MaterialExpression. The returned pointer must be deleted after use. @param MaterialElement				The UEPbrMaterialElement on which to create the material expressions @param ParameterName					The display name for the Color or Scalar input @param WeightedExpressionParamater	The structure defining the parameters of this weighted expression.
- L129 _public prototype_ `static FDatasmithFacadeTexture* CreateSimpleTextureElement( const TCHAR* InTextureFilePath, FDatasmithFacadeTexture::ETextureMode InTextureMode = FDatasmithFacadeTexture::ETextureMode::Diffuse );` — Create a new FDatasmithFacadeTexture and automatically fill its properties from the given arguments. The returned pointer can be null if the path in empty and must be deleted after use. @param InTextureFilePath	The file path of the texture, used to determine the texture name and label as well. @param InTextureMode		The mode of the texture, used to determine the texture name and label as well.

#### struct `FDatasmithFacadeMaterialsUtils::FUVEditParameters`  
`struct FUVEditParameters`  
_L25-61_
- L28 _public prototype_ `void SetUVOffset( float X, float Y );` — UV space has its origin at top-left, with U going left-to-right, V top-to-bottom
- L29 _public prototype_ `void GetUVOffset( float& OutX, float& OutY ) const;`
- L32 _public prototype_ `void SetUVTiling( float X, float Y );` — FVector2D UVTiling;
- L33 _public prototype_ `void GetUVTiling( float& OutX, float& OutY ) const;`
- L36 _public prototype_ `void SetRotationPivot( float X, float Y, float Z );` — W rotation center
- L37 _public prototype_ `void GetRotationPivot( float& OutX, float& OutY, float& OutZ ) const;`
- L40 _public prototype_ `void SetRotationAngle( float Angle );` — W rotation in degrees (rotation is counterclockwise)
- L41 _public prototype_ `float GetRotationAngle() const;`
- L44 _public prototype_ `void SetChannelIndex( uint8 ChannelIndex );` — UV channel to use
- L45 _public prototype_ `uint8 GetChannelIndex() const;`
- L48 _public prototype_ `void SetIsUsingRealWorldScale( bool bIsUsingRealWorldScale );` — Enable "Real-World Scale" behavior as in 3ds max
- L49 _public prototype_ `bool GetIsUsingRealWorldScale() const;`
- L52 _public prototype_ `void SetMirrorU( bool bMirrorU );` — Enable mirroring of texture in U and V
- L53 _public prototype_ `bool GetMirrorU() const;`
- L54 _public prototype_ `void SetMirrorV( bool bMirrorV );`
- L55 _public prototype_ `bool GetMirrorV() const;`
- L60 _protected member_ `DatasmithMaterialsUtils::FUVEditParameters UVEditParameters;`

#### struct `FDatasmithFacadeMaterialsUtils::FWeightedMaterialExpressionParameters`  
`struct FWeightedMaterialExpressionParameters`  
_L75-111_
- desc: Helper struct used for reproducing the behavior of the optional value-type in interfaced language.
- L78 _public function_ `FWeightedMaterialExpressionParameters( float InWeight ) : Weight( InWeight ) , TextureMode( FDatasmithFacadeTexture::ETextureMode::Diffuse ) , Expression( nullptr, TSharedPtr<IDatasmithUEPbrMaterialElement>() )`
- L85 _public prototype_ `void SetColor( float R, float G, float B, float A );` — Set the color parameter taking linear channel input.
- L87 _public prototype_ `void SetColorsRGB( uint8 R, uint8 G, uint8 B, uint8 A );` — Set the color parameter taking non-linear sRGB channel input.
- L89 _public prototype_ `void SetScalar( float Value );`
- L91 _public prototype_ `void SetTextureMode( FDatasmithFacadeTexture::ETextureMode InTextureMode );`
- L93 _public prototype_ `void SetExpression( const FDatasmithFacadeMaterialExpression& InExpression );`
- L99 _protected member_ `TOptional<FLinearColor> Color;` — bHasColor used to emulate TOptional<> behavior, if bHasColor is false, the Color parameter will be ignored.
- L102 _protected member_ `TOptional<float> Scalar;` — bHasScalar used to emulate TOptional<> behavior, if bHasColor is false, the Scalar parameter will be ignored.
- L104 _protected member_ `float Weight;`
- L106 _protected member_ `FDatasmithFacadeTexture::ETextureMode TextureMode;`
- L110 _protected member_ `FDatasmithFacadeMaterialExpression Expression;` — Local copy of the optional FDatasmithFacadeMaterialExpression. We shall not create a getter for this member as Expression may hold invalid pointer to the actual IDatasmithMaterialExpression.

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeMesh.h` (Public)


#### class `FDatasmithFacadeMesh`  
`class FDatasmithFacadeMesh`  
_L13-436_
- L17 _public function_ `FDatasmithFacadeMesh() : RootOwnerMesh(MakeShared<FDatasmithMesh>()) , InternalMesh(RootOwnerMesh.Get())`
- L22 _public function_ `void SetName( const TCHAR* InName )`
- L29 _public function_ `const TCHAR* GetName() const`
- L35 _public prototype_ `void CalculateHash(TCHAR OutBuffer[33], size_t BufferSize) const;` — Return a MD5 hash of the content of the Datasmith Mesh
- L41 _public function_ `void SetFacesCount( int32 NumFaces )` — Setting the amount of faces is mandatory before filling the array
- L49 _public function_ `int32 GetFacesCount() const` — Retrieves the amount of faces
- L62 _public function_ `void SetFace( int32 Index, int32 Vertex1, int32 Vertex2, int32 Vertex3, int32 MaterialId = 0 )` — Sets the geometry of the face @param Index		value to choose the face that will be affected @param Vertex1	Index of the first geometric vertex that defines this face @param Vertex2	Index of the second geometric vertex that defines this face @param Vertex3	Index of the third geometric vertex that defines this face
- L73 _public function_ `void GetFace( int32 Index, int32& OutVertex1, int32& OutVertex2, int32& OutVertex3, int32& OutMaterialId ) const`
- L90 _public function_ `void SetFaceSmoothingMask( int32 Index, uint32 SmoothingMask )` — Sets the smoothing mask of the face @param Index			Index of the face that will be affected @param SmoothingMask	32 bits mask, 0 means no smoothing
- L103 _public function_ `uint32 GetFaceSmoothingMask( int32 Index ) const` — Gets the smoothing mask of a face @param Index		Index of the face to retrieve the smoothing mask from
- L110 _public function_ `int32 GetMaterialsCount() const`
- L115 _public function_ `bool IsMaterialIdUsed( int32 MaterialId ) const`
- L126 _public function_ `void SetVerticesCount( int32 NumVerts )` — Setting the amount of geometric vertices is mandatory before filling the array
- L134 _public function_ `int32 GetVerticesCount() const` — Retrieves the amount of geometric vertices. The validity of the vertex data is not guaranteed
- L147 _public prototype_ `void SetVertex( int32 Index, float X, float Y, float Z );` — Sets the 3d position of the vertex @param Index value to choose the vertex that will be affected @x position on the x axis @y position on the y axis @z position on the z axis
- L154 _public prototype_ `void GetVertex( int32 Index, float& OutX, float& OutY, float& OutZ ) const;`
- L172 _public prototype_ `void SetNormal( int32 Index, float X, float Y, float Z );` — Sets the 3d normal @param Index value to choose the normal that will be affected @x direction on the x axis @y direction on the y axis @z direction on the z axis
- L179 _public prototype_ `void GetNormal( int32 Index, float& OutX, float& OutY, float& OutZ ) const;`
- L194 _public function_ `void SetUVChannelsCount( int32 ChannelCount )` — Sets the amount of UV channels on this mesh @param ChannelCount	The number of UV channels
- L204 _public function_ `void AddUVChannel()` — Add a UV channel at the end
- L212 _public function_ `void RemoveUVChannel()` — Remove the last UV channel
- L218 _public function_ `int32 GetUVChannelsCount() const` — Gets the amount of UV channels on this mesh
- L229 _public function_ `void SetUVCount( int32 Channel, int32 NumVerts )` — Setting the amount of UV coordinates on the channel is mandatory before filling the array @param Channel	The channel to set the numbers of UVs @param NumVerts	The number of UVs in the channel
- L238 _public function_ `int32 GetUVCount( int32 Channel ) const` — Retrieves the amount of UV coordinates on the channel. The validity of the vertex data is not guaranteed
- L252 _public function_ `void SetUV( int32 Channel, int32 Index, double U, double V )` — Sets the 2d position of the UV vertex for the first uv mapping @param Index	Value to choose the vertex that will be affected @param U		Horizontal coordinate @param V		Vertical coordinate
- L265 _public function_ `uint32 GetHashForUVChannel( int32 Channel ) const` — Get the hash for a uv channel
- L278 _public function_ `void GetUV( int32 Channel, int32 Index, double& OutU, double& OutV ) const` — Gets the UV coordinates for a channel @param Channel	The channel we want to retrieve the UVs from @param Index		The UV coordinates to retrieve
- L299 _public function_ `void SetFaceUV( int32 Index, int32 Channel, int32 Vertex1, int32 Vertex2, int32 Vertex3 )` — Sets the channel UV coordinates of the face @param Index		Index of the face that will be affected @param Channel	UV channel, starting at 0 @param Vertex1	Index of the first uv vertex that defines this face @param Vertex2	Index of the second uv vertex that defines this face @param Vertex3	Index of the third uv vertex that defines this face
- L319 _public function_ `void GetFaceUV( int32 Index, int32 Channel, int32& OutVertex1, int32& OutVertex2, int32& OutVertex3 ) const` — Gets the UV coordinates of the vertices of a face @param Index		Index of the face to retrieve the UVs from @param Channel	UV channel, starting at 0 @param Vertex1	Index of the first uv vertex that defines this face @param Vertex2	Index of the second uv vertex that defines this face @param Vertex3	Index of the third uv vertex that defines this face
- L331 _public function_ `int32 GetVertexColorCount() const` — Get the number of vertex color
- L342 _public function_ `void SetVertexColor( int32 Index, uint8 R, uint8 G, uint8 B, uint8 A )` — Set a vertex color @param Index		Index of the vertex color that will be affected @param Color		The color for the vertex
- L358 _public function_ `void GetVertexColor( int32 Index, uint8& OutR, uint8 OutG, uint8& OutB, uint8& OutA ) const` — Get the color for a vertex @param Index		Index of the vertex color to retrieve
- L377 _public function_ `void SetLightmapSourceUVChannel( int32 Channel )` — Sets the UV channel that will be used as the source UVs for lightmap UVs generation at import, defaults to channel 0. Will be overwritten during Mesh export if we choose to generate the lightmap source UVs.
- L385 _public function_ `int32 GetLightmapSourceUVChannel() const` — Gets the UV channel that will be used for lightmap UVs generation at import
- L395 _public function_ `void AddLOD(const FDatasmithFacadeMesh& InLODMesh)` — Adds a LOD mesh to this base LOD mesh
- L396 _public function_ `int32 GetLODsCount() const`
- L397 _public function_ `FDatasmithFacadeMesh* GetNewLOD(int32 Index)`
- L411 _public function_ `float ComputeArea() const` — Returns the total surface area
- L422 _protected function_ `FDatasmithFacadeMesh( const TSharedRef<FDatasmithMesh>& InRootOwnerMesh, FDatasmithMesh& InReferencedMesh ) : RootOwnerMesh(InRootOwnerMesh) , InternalMesh(InReferencedMesh)`
- L430 _protected function_ `FDatasmithMesh& GetDatasmithMesh()`
- L431 _protected function_ `const FDatasmithMesh& GetDatasmithMesh() const`
- L434 _private member_ `TSharedRef<FDatasmithMesh> RootOwnerMesh;`
- L435 _private member_ `FDatasmithMesh& InternalMesh;`

#### class `FDatasmithFacadeMeshElement`  
`class FDatasmithFacadeMeshElement : public FDatasmithFacadeElement`  
_L438-574_
- inherits: `FDatasmithFacadeElement`
- L441 _public prototype_ `FDatasmithFacadeMeshElement( const TCHAR* InElementName );`
- L446 _public function_ `const TCHAR* GetFile() const` — Get the output filename, it can be absolute or relative to the scene file
- L452 _public function_ `void SetFile( const TCHAR* InFile )` — Set the output filename, it can be absolute or relative to the scene file
- L460 _public prototype_ `void GetFileHash( TCHAR OutBuffer[33], size_t BufferSize ) const;` — Return a string representation of a MD5 hash of the content of the Mesh Element. Used in CalculateElementHash to quickly identify Element with identical content
- L466 _public prototype_ `void SetFileHash( const TCHAR* Hash );` — Set the MD5 hash of the current texture file. This should be a hash of its content.
- L478 _public function_ `void SetDimensions( float InArea, float InWidth, float InHeight, float InDepth )` — Set surface area and bounding box dimensions to be used on lightmap size calculation. @param InArea total surface area @param InWidth bounding box width @param InHeight bounding box height @param InDepth bounding box depth
- L489 _public function_ `float GetArea() const` — Get the total surface area
- L495 _public function_ `float GetWidth() const` — Get the bounding box width
- L501 _public function_ `float GetHeight() const` — Get the bounding box height
- L507 _public function_ `float GetDepth() const` — Get the bounding box depth
- L513 _public function_ `int32 GetLightmapCoordinateIndex() const` — Get the UV channel that will be used for the lightmap
- L522 _public function_ `void SetLightmapCoordinateIndex(int32 UVChannel)` — Set the UV channel that will be used for the lightmap Note: If the lightmap coordinate index is something greater than -1 it will make the importer skip the lightmap generation
- L528 _public function_ `int32 GetLightmapSourceUV() const` — Get the source UV channel that will be used at import to generate the lightmap UVs
- L534 _public function_ `void SetLightmapSourceUV(int32 UVChannel)` — Set the source UV channel that will be used at import to generate the lightmap UVs
- L540 _public function_ `void SetMaterial(const TCHAR* MaterialPathName, int32 SlotId)` — Set the material slot Id to use the material MaterialPathName
- L546 _public function_ `const TCHAR* GetMaterial(int32 SlotId) const` — Get the name of the material mapped to slot Id, return nullptr if slot isn't mapped
- L552 _public function_ `int32 GetMaterialSlotCount() const` — Get the number of material slot set on this mesh
- L558 _public prototype_ `FDatasmithFacadeMaterialID* GetMaterialSlotAt( int32 Index );` — Get the material mapping for slot Index
- L566 _protected prototype_ `FDatasmithFacadeMeshElement( const TSharedRef<IDatasmithMeshElement>& InMeshElement );`
- L570 _protected function_ `TSharedRef<IDatasmithMeshElement> GetDatasmithMeshElement() const`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeMetaData.h` (Public)


#### class `FDatasmithFacadeMetaData`  
`class FDatasmithFacadeMetaData : public FDatasmithFacadeElement`  
_L12-96_
- inherits: `FDatasmithFacadeElement`
- L16 _public prototype_ `FDatasmithFacadeMetaData( const TCHAR* InElementName );`
- L21 _public prototype_ `void AddPropertyBoolean( const TCHAR* InPropertyName, bool bInPropertyValue );` — Add a property boolean property to the Datasmith actor.
- L27 _public prototype_ `void AddPropertyColor( const TCHAR* InPropertyName, uint8 InR, uint8 InG, uint8 InB, uint8 InA );` — Add a property sRGBA color property to the Datasmith actor.
- L36 _public prototype_ `void AddPropertyFloat( const TCHAR* InPropertyName, float InPropertyValue );` — Add a property float property to the Datasmith actor.
- L42 _public prototype_ `void AddPropertyString( const TCHAR* InPropertyName, const TCHAR* InPropertyValue );` — Add a property string property to the Datasmith actor.
- L48 _public prototype_ `void AddPropertyTexture( const TCHAR* InPropertyName, const TCHAR* InTextureFilePath );` — Add a property texture property to the Datasmith actor.
- L54 _public prototype_ `void AddPropertyVector( const TCHAR* InPropertyName, const TCHAR* InPropertyValue );` — Add a property vector property to the Datasmith actor.
- L59 _public prototype_ `void AddProperty( const FDatasmithFacadeKeyValueProperty* InProperty );`
- L64 _public prototype_ `int32 GetPropertiesCount() const;` — Get the total amount of properties in this meta data.
- L67 _public prototype_ `FDatasmithFacadeKeyValueProperty* GetNewProperty( int32 PropertyIndex ) const;` — Returns a new FDatasmithFacadeKeyValueProperty pointing to the KeyValueProperty at the given index, the returned value must be deleted after used, can be nullptr.
- L72 _public prototype_ `void SetAssociatedElement( const FDatasmithFacadeElement* Element );` — Sets the Datasmith element that is associated with this meta data
- L77 _public prototype_ `void RemoveProperty( const FDatasmithFacadeKeyValueProperty* Property );` — Remove the property from this meta data
- L82 _public function_ `void ResetProperties()` — Remove all properties in this meta data
- L91 _protected prototype_ `FDatasmithFacadeMetaData( const TSharedRef<IDatasmithMetaDataElement>& InMetaDataElement );`
- L95 _protected prototype_ `TSharedRef<IDatasmithMetaDataElement> GetDatasmithMetaDataElement() const;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeScene.h` (Public)


#### class `FDatasmithFacadeScene`  
`class FDatasmithFacadeScene`  
_L21-397_
- L35 _public prototype_ `FDatasmithFacadeScene( const TCHAR* InApplicationHostName,`
- L43 _public prototype_ `void AddActor( FDatasmithFacadeActor* InActorPtr` — Collect an element for the Datasmith scene to build.
- L47 _public prototype_ `int32 GetActorsCount() const;`
- L49 _public prototype_ `FDatasmithFacadeActor* GetNewActor( int32 ActorIndex );`
- L53 _public prototype_ `void RemoveActor( FDatasmithFacadeActor* InActorPtr, EActorRemovalRule RemovalRule = EActorRemovalRule::RemoveChildren );`
- L58 _public function_ `void RemoveActorAt( int32 ActorIndex, EActorRemovalRule RemovalRule = EActorRemovalRule::RemoveChildren )`
- L66 _public prototype_ `void AddMaterial( FDatasmithFacadeBaseMaterial* InMaterialPtr );`
- L73 _public prototype_ `int32 GetMaterialsCount() const;` — Returns the number of material elements added to the scene.
- L81 _public prototype_ `FDatasmithFacadeBaseMaterial* GetNewMaterial( int32 MaterialIndex );` — Returns a new FDatasmithFacadeBaseMaterial pointing to the Material at the specified index. If the given index is invalid, the returned value is nullptr. @param MaterialIndex The index of the material in the scene.
- L90 _public prototype_ `void RemoveMaterial( FDatasmithFacadeBaseMaterial* InMaterialPtr );` — Removes a Material Element from the scene. @param InMaterialPtr the Material Element to remove
- L94 _public function_ `void RemoveMaterialAt( int32 MaterialIndex )`
- L101 _public prototype_ `FDatasmithFacadeMeshElement* ExportDatasmithMesh( FDatasmithFacadeMesh* Mesh, FDatasmithFacadeMesh* CollisionMesh = nullptr );`
- L106 _public prototype_ `bool ExportDatasmithMesh( FDatasmithFacadeMeshElement* MeshElement, FDatasmithFacadeMesh* Mesh, FDatasmithFacadeMesh* CollisionMesh = nullptr );`
- L112 _public prototype_ `void AddMesh( FDatasmithFacadeMeshElement* InMeshPtr );`
- L116 _public function_ `int32 GetMeshesCount() const`
- L121 _public prototype_ `FDatasmithFacadeMeshElement* GetNewMesh( int32 MeshIndex );`
- L125 _public prototype_ `void RemoveMesh( FDatasmithFacadeMeshElement* MeshElement );`
- L129 _public function_ `void RemoveMeshAt( int32 MeshIndex )`
- L136 _public prototype_ `void AddTexture( FDatasmithFacadeTexture* InTexturePtr );`
- L140 _public prototype_ `int32 GetTexturesCount() const;`
- L146 _public prototype_ `FDatasmithFacadeTexture* GetNewTexture( int32 TextureIndex );` — Returns a new FDatasmithFacadeTexture pointing to the Texture at the specified index. If the given index is invalid, the returned value is nullptr.
- L150 _public prototype_ `void RemoveTexture( FDatasmithFacadeTexture* InTexturePtr );`
- L154 _public function_ `void RemoveTextureAt( int32 TextureIndex )`
- L161 _public prototype_ `void AddLevelVariantSets( FDatasmithFacadeLevelVariantSets* InLevelVariantSetsPtr );`
- L165 _public prototype_ `int32 GetLevelVariantSetsCount() const;`
- L167 _public prototype_ `FDatasmithFacadeLevelVariantSets* GetNewLevelVariantSets( int32 LevelVariantSetsIndex );`
- L171 _public prototype_ `void RemoveLevelVariantSets( FDatasmithFacadeLevelVariantSets* InLevelVariantSetsPtr );`
- L175 _public function_ `void RemoveLevelVariantSetsAt( int32 LevelVariantSetsIndex )`
- L182 _public prototype_ `void AddLevelSequence( FDatasmithFacadeLevelSequence* InLevelSequence );`
- L186 _public prototype_ `int32 GetLevelSequencesCount() const;`
- L188 _public prototype_ `FDatasmithFacadeLevelSequence* GetNewLevelSequence( int32 LevelSequenceIndex );`
- L192 _public prototype_ `void RemoveLevelSequence( FDatasmithFacadeLevelSequence* InLevelSequence );`
- L196 _public function_ `void RemoveLevelSequenceAt( int32 LevelSequenceIndex )`
- L203 _public prototype_ `void AddMetaData( FDatasmithFacadeMetaData* InMetaDataPtr );`
- L207 _public prototype_ `int32 GetMetaDataCount() const;`
- L213 _public prototype_ `FDatasmithFacadeMetaData* GetNewMetaData( int32 MetaDataIndex );` — Returns a new FDatasmithFacadeMetaData pointing to the MetaData at the specified index. If the given index is invalid, the returned value is nullptr.
- L221 _public prototype_ `FDatasmithFacadeMetaData* GetNewMetaData( FDatasmithFacadeElement* Element );` — Returns a new FDatasmithFacadeMetaData pointing to the MetaData associated to the specified DatasmithElement. If there is no associated metadata or the element is null, the returned value is nullptr.
- L225 _public prototype_ `void RemoveMetaData( FDatasmithFacadeMetaData* InMetaDataPtr );`
- L229 _public function_ `void RemoveMetaDataAt( int32 MetaDataIndex )`
- L237 _public prototype_ `void SetName(const TCHAR* InName);` — Set the Datasmith scene name
- L240 _public prototype_ `const TCHAR* GetName() const;` — Get the Datasmith scene file name
- L243 _public prototype_ `void SetOutputPath(const TCHAR* InOutputPath);` — Set the path to the folder where the .datasmith file will be saved.
- L246 _public prototype_ `const TCHAR* GetOutputPath() const;` — Get the path to the folder where the .datasmith file will be saved.
- L249 _public prototype_ `const TCHAR* GetAssetsOutputPath() const;` — Get the path were additional assets will be saved to.
- L252 _public prototype_ `void GetGeolocation(double& OutLatitude, double& OutLongitude, double& OutElevation) const;` — Get the Datasmith scene Geolocation data
- L255 _public prototype_ `void SetGeolocationLatitude(double Latitude);` — Set the Datasmith scene Geolocation data
- L256 _public prototype_ `void SetGeolocationLongitude(double Longitude);`
- L257 _public prototype_ `void SetGeolocationElevation(double Elevation);`
- L260 _public prototype_ `void PreExport();` — Instantiate an exporter and register export start time
- L263 _public prototype_ `void CleanUp();` — Validate assets and remove unused ones.
- L269 _public prototype_ `static void Shutdown();` — Manually shutdown the Facade and close down all the core engine systems and release the resources they allocated You don't need to call this function on Windows platform.
- L276 _public prototype_ `bool ExportScene( const TCHAR* InOutputPath,` — Build and export a Datasmith scene instance and its scene element assets. The passed InOutputPath parameter will override any Name and OutputPath previously specified. @param bCleanupUnusedElements Remove unused meshes, textures and materials before exporting @return True if the scene was properly exported.
- L285 _public prototype_ `bool ExportScene( bool bCleanupUnusedElements = true );` — Build and export a Datasmith scene instance and its scene element assets. @param bCleanupUnusedElements Remove unused meshes, textures and materials before exporting @return True if the scene was properly exported.
- L291 _public prototype_ `void SerializeLevelSequences();` — Save Datasmith LevelSequences into files and specify those files in each corresponding LevelSequenceElement
- L298 _public prototype_ `void SetLabel( const TCHAR* InSceneLabel );` — Set the Datasmith scene's label. This is mainly used in conjunction with DirectLink. The scene's label is used to name the source (stream) created to broadcast the content of the scene
- L303 _public prototype_ `const TCHAR* GetLabel() const;` — Return the Datasmith scene's label.
- L305 _public function_ `void Reset()`
- L312 _public function_ `const TCHAR* GetHost() const` — Gets the name of the host application which created the scene
- L322 _public function_ `void SetHost( const TCHAR* InHost )` — Sets the name of the host application from which we're exporting from. @param InHost	The host application name
- L330 _public function_ `const TCHAR* GetVendor() const` — Returns the vendor name of the application used to export the scene
- L340 _public function_ `void SetVendor( const TCHAR* InApplicationVendorName )` — Sets the vendor name of the application used to export the scene. @param InVendor	The application vendor name
- L348 _public function_ `const TCHAR* GetProductName() const` — Returns the product name of the application used to export the scene
- L358 _public function_ `void SetProductName( const TCHAR* InApplicationProductName )` — Sets the product name of the application used to export the scene. @param InProductName	The application name
- L366 _public function_ `const TCHAR* GetProductVersion() const` — Returns the product version of the application used to export the scene
- L376 _public function_ `void SetProductVersion( const TCHAR* InApplicationProductVersion )` — Sets the product version of the application used to export the scene. @param InProductVersion	The application version
- L388 _protected prototype_ `TSharedRef<IDatasmithScene> GetScene() const;` — Return the build Datasmith scene instance.
- L393 _private member_ `TSharedRef<IDatasmithScene> SceneRef;` — Datasmith scene instance built with the collected elements.
- L396 _private member_ `TSharedRef<FDatasmithSceneExporter> SceneExporterRef;` — Datasmith scene exporter

#### enum `FDatasmithFacadeScene::EActorRemovalRule`  
`enum class EActorRemovalRule : uint32`  
_L26-33_
- desc: Copy from EDatasmithActorRemovalRule
- L29 _public enumerator_ `RemoveChildren` — Remove also the actors children
- L32 _public enumerator_ `KeepChildrenAndKeepRelativeTransform` — Keeps current relative transform as the relative transform to the new parent.

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeTexture.h` (Public)


#### class `FDatasmithFacadeTexture`  
`class FDatasmithFacadeTexture : public FDatasmithFacadeElement`  
_L9-157_
- inherits: `FDatasmithFacadeElement`
- L77 _public prototype_ `FDatasmithFacadeTexture( const TCHAR* InElementName`
- L81 _public function_ `virtual ~FDatasmithFacadeTexture()`
- L84 _public prototype_ `const TCHAR* GetFile() const;` — Get texture filename
- L87 _public prototype_ `void SetFile( const TCHAR* File );` — Set texture filename
- L97 _public prototype_ `void SetData( const uint8* InData, uint32 InDataSize, ETextureFormat InFormat );` — Set the output data buffer, used only when no output filename is set @param InData data to load the texture from @param InDataSize size in bytes of the buffer @param InFormat texture format(e.g. png or jpeg) @note The given data is not freed by the DatasmithImporter.
- L100 _public prototype_ `const uint8* GetData( uint32& OutDataSize, ETextureFormat& OutFormat ) const;` — Return the optional data, if loading from memory. Must be callable from any thread.
- L103 _public prototype_ `void GetFileHash( TCHAR OutBuffer[33], size_t BufferSize ) const;` — Return a string representation of a MD5 hash of the content of the Texture Element. Used in CalculateElementHash to quickly identify Element with identical content
- L106 _public prototype_ `void SetFileHash( const TCHAR* Hash );` — Set the MD5 hash of the current texture file. This should be a hash of its content.
- L109 _public prototype_ `ETextureMode GetTextureMode() const;` — Get texture usage
- L112 _public prototype_ `void SetTextureMode( ETextureMode Mode );` — Set texture usage
- L115 _public prototype_ `ETextureFilter GetTextureFilter() const;` — Get texture filter
- L118 _public prototype_ `void SetTextureFilter( ETextureFilter Filter );` — Set texture filter
- L121 _public prototype_ `ETextureAddress GetTextureAddressX() const;` — Get texture X axis address mode
- L124 _public prototype_ `void SetTextureAddressX( ETextureAddress Mode );` — Set texture X axis address mode
- L127 _public prototype_ `ETextureAddress GetTextureAddressY() const;` — Get texture Y axis address mode
- L130 _public prototype_ `void SetTextureAddressY( ETextureAddress Mode );` — Set texture Y axis address mode
- L133 _public prototype_ `bool GetAllowResize() const;` — Get allow texture resizing
- L136 _public prototype_ `void SetAllowResize( bool bAllowResize );` — Set allow texture resizing
- L139 _public prototype_ `float GetRGBCurve() const;` — Get texture gamma <= 0 for auto
- L142 _public prototype_ `void SetRGBCurve( const float InRGBCurve );` — Set texture gamma <= 0 for auto
- L145 _public prototype_ `EColorSpace GetSRGB() const;` — Gets the color space of the texture
- L148 _public prototype_ `void SetSRGB( EColorSpace Option );` — Sets the color space of the texture
- L154 _protected prototype_ `FDatasmithFacadeTexture( TSharedRef<IDatasmithTextureElement> InTextureElement );`
- L156 _protected prototype_ `TSharedRef<IDatasmithTextureElement> GetDatasmithTextureElement() const;`

#### enum `FDatasmithFacadeTexture::ETextureMode`  
`enum class ETextureMode : uint8`  
_L16-25_
- desc: Possible Datasmith texture modes. Copy of EDatasmithTextureMode from DatasmithCore DatasmithDefinitions.h.
- L18 _public enumerator_ `Diffuse`
- L19 _public enumerator_ `Specular`
- L20 _public enumerator_ `Normal`
- L21 _public enumerator_ `NormalGreenInv`
- L22 _public enumerator_ `Displace`
- L23 _public enumerator_ `Other`
- L24 _public enumerator_ `Bump`

#### enum `FDatasmithFacadeTexture::ETextureFilter`  
`enum class ETextureFilter`  
_L31-38_
- desc: Texture filtering for textures. Copy of EDatasmithTextureFilter from DatasmithCore DatasmithDefinitions.h.
- L33 _public enumerator_ `Nearest`
- L34 _public enumerator_ `Bilinear`
- L35 _public enumerator_ `Trilinear`
- L37 _public enumerator_ `Default` — Use setting from the Texture Group.

#### enum `FDatasmithFacadeTexture::ETextureAddress`  
`enum class ETextureAddress`  
_L44-49_
- desc: Texture address mode for textures.  Note: Preserve enum order. Copy of EDatasmithTextureAddress from DatasmithCore DatasmithDefinitions.h.
- L46 _public enumerator_ `Wrap`
- L47 _public enumerator_ `Clamp`
- L48 _public enumerator_ `Mirror`

#### enum `FDatasmithFacadeTexture::ETextureFormat`  
`enum class ETextureFormat`  
_L55-59_
- desc: Texture format for raw data importing. Copy of EDatasmithTextureFormat from DatasmithCore DatasmithDefinitions.h.
- L57 _public enumerator_ `PNG`
- L58 _public enumerator_ `JPEG`

#### enum `FDatasmithFacadeTexture::EColorSpace`  
`enum class EColorSpace`  
_L68-73_
- desc: Texture color space. Default: Leave at whatever is default for the texture mode sRGB: Enable the sRGB boolean regardless of texture mode Linear: Disable the sRGB boolean regardless of texture mode Copy of EDatasmithColorSpace from DatasmithCore DatasmithDefinitions.h.
- L70 _public enumerator_ `Default`
- L71 _public enumerator_ `sRGB`
- L72 _public enumerator_ `Linear`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeUEPbrMaterial.h` (Public)


#### class `FDatasmithFacadeExpressionInput`  
`class FDatasmithFacadeExpressionInput`  
_L19-49_
- L22 _public prototype_ `const TCHAR* GetName() const;`
- L23 _public prototype_ `void SetName(const TCHAR* InName);`
- L26 _public prototype_ `FDatasmithFacadeMaterialExpression* GetNewFacadeExpression();` — Returns a new FDatasmithFacadeMaterialExpression pointing to the connected expression, the returned value must be deleted after used, can be nullptr.
- L27 _public prototype_ `void SetExpression( FDatasmithFacadeMaterialExpression* InExpression );`
- L29 _public prototype_ `int32 GetOutputIndex() const;`
- L30 _public prototype_ `void SetOutputIndex( int32 InOutputIndex );`
- L35 _protected function_ `FDatasmithFacadeExpressionInput( IDatasmithExpressionInput* InExpressionInput, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : InternalExpressionInput(InExpressionInput) , ReferencedMaterial(InMaterialElement)`
- L40 _protected function_ `IDatasmithExpressionInput& GetExpressionInput()`
- L41 _protected function_ `const IDatasmithExpressionInput& GetExpressionInput() const`
- L45 _private member_ `IDatasmithExpressionInput* InternalExpressionInput;`
- L48 _private member_ `TSharedPtr<IDatasmithUEPbrMaterialElement> ReferencedMaterial;` — We hold a shared pointer to the material to make sure it stays valid while a facade objects points to it.

#### enum `EDatasmithFacadeMaterialExpressionType`  
`enum class EDatasmithFacadeMaterialExpressionType : uint64`  
_L51-62_
- L53 _public enumerator_ `ConstantBool`
- L54 _public enumerator_ `ConstantColor`
- L55 _public enumerator_ `ConstantScalar`
- L56 _public enumerator_ `FlattenNormal`
- L57 _public enumerator_ `FunctionCall`
- L58 _public enumerator_ `Generic`
- L59 _public enumerator_ `Texture`
- L60 _public enumerator_ `TextureCoordinate`
- L61 _public enumerator_ `None = 255`

#### class `FDatasmithFacadeMaterialExpression`  
`class FDatasmithFacadeMaterialExpression`  
_L77-124_
- L82 _public prototype_ `const TCHAR* GetName() const;` — The name of the expression. Used as parameter name for material instances.
- L83 _public prototype_ `void SetName( const TCHAR* InName );`
- L85 _public prototype_ `EDatasmithFacadeMaterialExpressionType GetExpressionType() const;`
- L88 _public prototype_ `void ConnectExpression( FDatasmithFacadeExpressionInput& ExpressionInput );` — Connects the default output to an expression input
- L91 _public prototype_ `void ConnectExpression( FDatasmithFacadeExpressionInput& ExpressionInput, int32 OutputIndex );` — Connects a specific output to an expression input
- L93 _public prototype_ `int32 GetInputCount() const;`
- L99 _public prototype_ `FDatasmithFacadeExpressionInput* GetNewFacadeInput( int32 Index );` — Returns a pointer to a new FDatasmithFacadeExpressionInput object wrapping the IDatasmithExpressionInput at the specified index if it exists. Returns null if the index is invalid. The caller is responsible for the destruction of returned object.
- L102 _public prototype_ `int32 GetDefaultOutputIndex() const;` — The output index to use by default for this expression when connecting it to other inputs.
- L103 _public prototype_ `void SetDefaultOutputIndex( int32 OutputIndex );`
- L105 _public prototype_ `virtual ~FDatasmithFacadeMaterialExpression() = default;`
- L107 _public function_ `void ResetExpression()`
- L112 _protected function_ `FDatasmithFacadeMaterialExpression( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : InternalMaterialExpression( InMaterialExpression ) , ReferencedMaterial( InMaterialElement )`
- L117 _protected function_ `IDatasmithMaterialExpression* GetMaterialExpression()`
- L118 _protected function_ `const IDatasmithMaterialExpression* GetMaterialExpression() const`
- L120 _protected member_ `IDatasmithMaterialExpression* InternalMaterialExpression;`
- L123 _protected member_ `TSharedPtr<IDatasmithUEPbrMaterialElement> ReferencedMaterial;` — We hold a shared pointer to the material to make sure it stays valid while a facade objects points to it.

#### class `FDatasmithFacadeExpressionParameter`  
`class FDatasmithFacadeExpressionParameter`  
_L129-136_
- desc: Facade representation of Abstract class IDatasmithExpressionParameter
- L132 _public prototype_ `virtual ~FDatasmithFacadeExpressionParameter() = default;`
- L134 _public prototype_ `virtual const TCHAR* GetGroupName() const = 0;`
- L135 _public prototype_ `virtual void SetGroupName( const TCHAR* InGroupName ) = 0;`

#### class `FDatasmithFacadeMaterialExpressionBool`  
`class FDatasmithFacadeMaterialExpressionBool : public FDatasmithFacadeMaterialExpression, public FDatasmithFacadeExpressionParameter`  
_L141-156_
- inherits: `FDatasmithFacadeMaterialExpression,FDatasmithFacadeExpressionParameter`
- desc: Represents a UMaterialExpressionStaticBoolParameter
- L144 _public prototype_ `bool GetBool() const;`
- L145 _public prototype_ `void SetBool(bool InValue);`
- L147 _public prototype_ `virtual const TCHAR* GetGroupName() const override;`
- L148 _public prototype_ `virtual void SetGroupName( const TCHAR* InGroupName ) override;`
- L153 _protected function_ `FDatasmithFacadeMaterialExpressionBool( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionColor`  
`class FDatasmithFacadeMaterialExpressionColor : public FDatasmithFacadeMaterialExpression, public FDatasmithFacadeExpressionParameter`  
_L158-188_
- inherits: `FDatasmithFacadeMaterialExpression,FDatasmithFacadeExpressionParameter`
- L164 _public prototype_ `void GetsRGBColor( uint8& OutR, uint8& OutG, uint8& OutB, uint8& OutA ) const;` — Get the color value of the expression in a sRGB format
- L168 _public prototype_ `void SetsRGBColor( uint8 R, uint8 G, uint8 B, uint8 A );` — Set the color value of the expression in a sRGB format
- L173 _public prototype_ `void GetColor( float& OutR, float& OutG, float& OutB, float& OutA ) const;` — Get the color value of the expression in a linear format with values between 0 and 1.
- L177 _public prototype_ `void SetColor( float R, float G, float B, float A );` — Set the color value of the expression in a linear format with values between 0 and 1.
- L179 _public prototype_ `virtual const TCHAR* GetGroupName() const override;`
- L180 _public prototype_ `virtual void SetGroupName( const TCHAR* InGroupName ) override;`
- L185 _protected function_ `FDatasmithFacadeMaterialExpressionColor( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionScalar`  
`class FDatasmithFacadeMaterialExpressionScalar : public FDatasmithFacadeMaterialExpression, public FDatasmithFacadeExpressionParameter`  
_L190-205_
- inherits: `FDatasmithFacadeMaterialExpression,FDatasmithFacadeExpressionParameter`
- L193 _public prototype_ `float GetScalar() const;`
- L194 _public prototype_ `void SetScalar( float InScalar );`
- L196 _public prototype_ `virtual const TCHAR* GetGroupName() const override;`
- L197 _public prototype_ `virtual void SetGroupName( const TCHAR* InGroupName ) override;`
- L202 _protected function_ `FDatasmithFacadeMaterialExpressionScalar( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionTexture`  
`class FDatasmithFacadeMaterialExpressionTexture : public FDatasmithFacadeMaterialExpression, public FDatasmithFacadeExpressionParameter`  
_L207-236_
- inherits: `FDatasmithFacadeMaterialExpression,FDatasmithFacadeExpressionParameter`
- L210 _public prototype_ `const TCHAR* GetTexturePathName() const;`
- L211 _public prototype_ `void SetTexturePathName( const TCHAR* InTexturePathName );`
- L216 _public prototype_ `FDatasmithFacadeExpressionInput GetInputCoordinate();` — Inputs
- L227 _public prototype_ `virtual const TCHAR* GetGroupName() const override;`
- L228 _public prototype_ `virtual void SetGroupName( const TCHAR* InGroupName ) override;`
- L233 _protected function_ `FDatasmithFacadeMaterialExpressionTexture( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionTextureCoordinate`  
`class FDatasmithFacadeMaterialExpressionTextureCoordinate : public FDatasmithFacadeMaterialExpression`  
_L238-256_
- inherits: `FDatasmithFacadeMaterialExpression`
- L241 _public prototype_ `int32 GetCoordinateIndex() const;`
- L242 _public prototype_ `void SetCoordinateIndex( int32 InCoordinateIndex );`
- L244 _public prototype_ `float GetUTiling() const;`
- L245 _public prototype_ `void SetUTiling( float InUTiling );`
- L247 _public prototype_ `float GetVTiling() const;`
- L248 _public prototype_ `void SetVTiling( float InVTiling );`
- L253 _protected function_ `FDatasmithFacadeMaterialExpressionTextureCoordinate( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionFlattenNormal`  
`class FDatasmithFacadeMaterialExpressionFlattenNormal : public FDatasmithFacadeMaterialExpression`  
_L258-274_
- inherits: `FDatasmithFacadeMaterialExpression`
- L264 _public prototype_ `FDatasmithFacadeExpressionInput GetNormal() const;` — Inputs
- L266 _public prototype_ `FDatasmithFacadeExpressionInput GetFlatness() const;`
- L271 _protected function_ `FDatasmithFacadeMaterialExpressionFlattenNormal( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionGeneric`  
`class FDatasmithFacadeMaterialExpressionGeneric : public FDatasmithFacadeMaterialExpression`  
_L276-297_
- inherits: `FDatasmithFacadeMaterialExpression`
- L279 _public prototype_ `void SetExpressionName( const TCHAR* InExpressionName );`
- L280 _public prototype_ `const TCHAR* GetExpressionName() const;`
- L283 _public prototype_ `int32 GetPropertiesCount() const;` — Get the total amount of properties in this expression
- L286 _public prototype_ `void AddProperty( const FDatasmithFacadeKeyValueProperty* InPropertyPtr );` — Add a property to this expression
- L289 _public prototype_ `FDatasmithFacadeKeyValueProperty* GetNewProperty( int32 Index );` — Returns a new FDatasmithFacadeKeyValueProperty pointing to the property at the given index, the returned value must be deleted after used, can be nullptr.
- L294 _protected function_ `FDatasmithFacadeMaterialExpressionGeneric( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeMaterialExpressionFunctionCall`  
`class FDatasmithFacadeMaterialExpressionFunctionCall : public FDatasmithFacadeMaterialExpression`  
_L299-311_
- inherits: `FDatasmithFacadeMaterialExpression`
- L302 _public prototype_ `void SetFunctionPathName( const TCHAR* InFunctionPathName );`
- L303 _public prototype_ `const TCHAR* GetFunctionPathName() const;`
- L308 _protected function_ `FDatasmithFacadeMaterialExpressionFunctionCall( IDatasmithMaterialExpression* InMaterialExpression, const TSharedPtr<IDatasmithUEPbrMaterialElement>& InMaterialElement ) : FDatasmithFacadeMaterialExpression( InMaterialExpression, InMaterialElement )`

#### class `FDatasmithFacadeUEPbrMaterial`  
`class FDatasmithFacadeUEPbrMaterial : public FDatasmithFacadeBaseMaterial`  
_L314-386_
- inherits: `FDatasmithFacadeBaseMaterial`
- L320 _public prototype_ `FDatasmithFacadeUEPbrMaterial( const TCHAR* InElementName );`
- L322 _public function_ `virtual ~FDatasmithFacadeUEPbrMaterial()`
- L324 _public prototype_ `FDatasmithFacadeExpressionInput GetBaseColor() const;`
- L325 _public prototype_ `FDatasmithFacadeExpressionInput GetMetallic() const;`
- L326 _public prototype_ `FDatasmithFacadeExpressionInput GetSpecular() const;`
- L327 _public prototype_ `FDatasmithFacadeExpressionInput GetRoughness() const;`
- L328 _public prototype_ `FDatasmithFacadeExpressionInput GetEmissiveColor() const;`
- L329 _public prototype_ `FDatasmithFacadeExpressionInput GetOpacity() const;`
- L330 _public prototype_ `FDatasmithFacadeExpressionInput GetNormal() const;`
- L331 _public prototype_ `FDatasmithFacadeExpressionInput GetRefraction() const;`
- L332 _public prototype_ `FDatasmithFacadeExpressionInput GetAmbientOcclusion() const;`
- L333 _public prototype_ `FDatasmithFacadeExpressionInput GetClearCoat() const;`
- L334 _public prototype_ `FDatasmithFacadeExpressionInput GetClearCoatRoughness() const;`
- L335 _public prototype_ `FDatasmithFacadeExpressionInput GetWorldPositionOffset() const;`
- L336 _public prototype_ `FDatasmithFacadeExpressionInput GetMaterialAttributes() const;`
- L338 _public prototype_ `int GetBlendMode() const;`
- L339 _public prototype_ `void SetBlendMode( int bInBlendMode );`
- L341 _public prototype_ `bool GetTwoSided() const;`
- L342 _public prototype_ `void SetTwoSided( bool bTwoSided );`
- L344 _public prototype_ `bool GetUseMaterialAttributes() const;`
- L345 _public prototype_ `void SetUseMaterialAttributes( bool bInUseMaterialAttributes );`
- L348 _public prototype_ `bool GetMaterialFunctionOnly() const;` — If a material is only referenced by other materials then it is only used as a material function and there is no need to instantiate it.
- L349 _public prototype_ `void SetMaterialFunctionOnly(bool bInMaterialFunctionOnly);`
- L351 _public prototype_ `float GetOpacityMaskClipValue() const;`
- L352 _public prototype_ `void SetOpacityMaskClipValue(float InClipValue);`
- L354 _public prototype_ `int32 GetExpressionsCount() const;`
- L357 _public prototype_ `FDatasmithFacadeMaterialExpression* GetNewFacadeExpression( int32 Index );` — Returns a new FDatasmithFacadeMaterialExpression pointing to the expression at the given index, the returned value must be deleted after used, can be nullptr.
- L359 _public prototype_ `int32 GetExpressionIndex( const FDatasmithFacadeMaterialExpression& Expression ) const;`
- L362 _public function_ `template< typename T > T AddMaterialExpression()`
- L367 _public function_ `void ResetExpressionGraph()` — Reset all expression to their default values and remove all connections
- L374 _public prototype_ `void SetParentLabel( const TCHAR* InParentLabel );` — If a parent material is generated from this material, this will be its label. If none, the instance and the parent will have the same label.
- L375 _public prototype_ `const TCHAR* GetParentLabel() const;`
- L381 _protected prototype_ `FDatasmithFacadeUEPbrMaterial( const TSharedRef<IDatasmithUEPbrMaterialElement>& InMaterialRef );`
- L383 _protected prototype_ `IDatasmithMaterialExpression* AddMaterialExpression( const EDatasmithFacadeMaterialExpressionType ExpressionType );`
- L385 _protected prototype_ `TSharedRef<IDatasmithUEPbrMaterialElement> GetDatasmithUEPbrMaterialElement() const;`
- L389 _function_ `template<> inline FDatasmithFacadeMaterialExpressionBool FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionBool >()`
- L395 _function_ `template<> inline FDatasmithFacadeMaterialExpressionColor FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionColor >()`
- L401 _function_ `template<> inline FDatasmithFacadeMaterialExpressionFlattenNormal FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionFlattenNormal >()`
- L407 _function_ `template<> inline FDatasmithFacadeMaterialExpressionFunctionCall FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionFunctionCall >()`
- L413 _function_ `template<> inline FDatasmithFacadeMaterialExpressionGeneric FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionGeneric >()`
- L419 _function_ `template<> inline FDatasmithFacadeMaterialExpressionScalar FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionScalar >()`
- L425 _function_ `template<> inline FDatasmithFacadeMaterialExpressionTexture FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionTexture >()`
- L431 _function_ `template<> inline FDatasmithFacadeMaterialExpressionTextureCoordinate FDatasmithFacadeUEPbrMaterial::AddMaterialExpression< FDatasmithFacadeMaterialExpressionTextureCoordinate >()`

#### Free symbols / members of external scopes

- L65 _macro_ `#define DS_CHECK_ENUM_MISMATCH(name) static_assert((uint64)EDatasmithFacadeMaterialExpressionType::name == (uint64)EDatasmithMaterialExpressionType::name, "enum mismatch");` — not trivial to reuse EDatasmithMaterialExpressionType (eg with a "using" declaration). #swig

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeUtils.h` (Public)


#### class `FDatasmithFacadeUniqueNameProvider`  
`class FDatasmithFacadeUniqueNameProvider`  
_L9-43_
- L12 _public prototype_ `FDatasmithFacadeUniqueNameProvider();`
- L20 _public prototype_ `const TCHAR* GenerateUniqueName(const TCHAR* BaseName);` — Generates a unique name @param BaseName Name that will be suffixed with an index to be unique @return TCHAR* Unique name. Calling "Contains()" with this name will be false. Pointer is only valid until the next GenerateUniqueName() call.
- L26 _public prototype_ `void Reserve( int32 NumberOfName );` — Reserves space in the internal data structures to contain at least the number of name specified. @param NumberOfName The number of name to reserve for.
- L32 _public prototype_ `void AddExistingName(const TCHAR* Name);` — Register a name as known @param Name name to register
- L38 _public prototype_ `void RemoveExistingName(const TCHAR* Name);` — Remove a name from the list of existing name @param Name name to unregister
- L41 _private member_ `TUniquePtr<FDatasmithUniqueNameProvider> InternalNameProvider;`
- L42 _private member_ `FString CachedGeneratedName;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DatasmithFacadeVariant.h` (Public)


#### enum `EDatasmithFacadePropertyCategory`  
`enum class EDatasmithFacadePropertyCategory : uint64`  
_L19-30_
- L21 _public enumerator_ `Undefined = 0`
- L22 _public enumerator_ `Generic = 1`
- L23 _public enumerator_ `RelativeLocation = 2`
- L24 _public enumerator_ `RelativeRotation = 4`
- L25 _public enumerator_ `RelativeScale3D = 8`
- L26 _public enumerator_ `Visibility = 16`
- L27 _public enumerator_ `Material = 32`
- L28 _public enumerator_ `Color = 64`
- L29 _public enumerator_ `Option = 128`

#### class `FDatasmithFacadePropertyCapture`  
`class FDatasmithFacadePropertyCapture : public FDatasmithFacadeElement`  
_L45-69_
- inherits: `FDatasmithFacadeElement`
- L50 _public prototype_ `FDatasmithFacadePropertyCapture();`
- L52 _public function_ `virtual ~FDatasmithFacadePropertyCapture()`
- L54 _public prototype_ `void SetPropertyPath(const TCHAR* Path);`
- L56 _public prototype_ `const TCHAR* GetPropertyPath();`
- L58 _public prototype_ `EDatasmithFacadePropertyCategory GetCategory() const;`
- L64 _protected prototype_ `explicit FDatasmithFacadePropertyCapture( const TSharedRef<IDatasmithBasePropertyCaptureElement>& InInternalPropertyCapture );`
- L68 _protected prototype_ `TSharedRef<IDatasmithBasePropertyCaptureElement> GetDatasmithPropertyCapture() const;`

#### class `FDatasmithFacadeActorBinding`  
`class FDatasmithFacadeActorBinding : public FDatasmithFacadeElement`  
_L71-156_
- inherits: `FDatasmithFacadeElement`
- L76 _public prototype_ `FDatasmithFacadeActorBinding( FDatasmithFacadeActor* InActorPtr );`
- L80 _public function_ `virtual ~FDatasmithFacadeActorBinding()`
- L82 _public prototype_ `void AddPropertyCapture( FDatasmithFacadePropertyCapture* InPropertyCapturePtr );`
- L86 _public prototype_ `int32 GetPropertyCapturesCount() const;`
- L88 _public prototype_ `FDatasmithFacadePropertyCapture* GetNewPropertyCapture( int32 PropertyCaptureIndex );`
- L92 _public prototype_ `void RemovePropertyCapture( FDatasmithFacadePropertyCapture* InPropertyCapturePtr );`
- L96 _public prototype_ `void AddRelativeLocationCapture( double X, double Y, double Z );`
- L102 _public prototype_ `void AddRelativeRotationCapture( double Pitch, double Yaw, double Roll );`
- L108 _public prototype_ `void AddRelativeRotationCapture( double X, double Y, double Z, double W );`
- L115 _public prototype_ `void AddRelativeScaleCapture( double X, double Y, double Z );`
- L121 _public prototype_ `void AddRelativeTransformCapture( const double InMatrix[16], bool bRowMajor = false );`
- L126 _public function_ `void AddRelativeTransformCapture( const float InMatrix[16], bool bRowMajor = false )`
- L139 _public prototype_ `void AddVisibilityCapture( bool bInVisibility );`
- L143 _public prototype_ `void AddMaterialCapture( FDatasmithFacadeBaseMaterial* InMaterialPtr );`
- L151 _protected prototype_ `explicit FDatasmithFacadeActorBinding( const TSharedRef<IDatasmithActorBindingElement>& InInternalActorBinding );`
- L155 _protected prototype_ `TSharedRef<IDatasmithActorBindingElement> GetDatasmithActorBinding() const;`

#### class `FDatasmithFacadeVariant`  
`class FDatasmithFacadeVariant : public FDatasmithFacadeElement`  
_L158-192_
- inherits: `FDatasmithFacadeElement`
- L163 _public prototype_ `FDatasmithFacadeVariant( const TCHAR* InElementName );`
- L167 _public function_ `virtual ~FDatasmithFacadeVariant()`
- L169 _public prototype_ `void AddActorBinding( FDatasmithFacadeActorBinding* InActorBindingPtr );`
- L173 _public prototype_ `int32 GetActorBindingsCount() const;`
- L175 _public prototype_ `FDatasmithFacadeActorBinding* GetNewActorBinding( int32 ActorBindingIndex );`
- L179 _public prototype_ `void RemoveActorBinding( FDatasmithFacadeActorBinding* InActorBindingPtr );`
- L187 _protected prototype_ `explicit FDatasmithFacadeVariant( const TSharedRef<IDatasmithVariantElement>& InInternalVariant );`
- L191 _protected prototype_ `TSharedRef<IDatasmithVariantElement> GetDatasmithVariant() const;`

#### class `FDatasmithFacadeVariantSet`  
`class FDatasmithFacadeVariantSet : public FDatasmithFacadeElement`  
_L194-228_
- inherits: `FDatasmithFacadeElement`
- L199 _public prototype_ `FDatasmithFacadeVariantSet( const TCHAR* InElementName );`
- L203 _public function_ `virtual ~FDatasmithFacadeVariantSet()`
- L205 _public prototype_ `void AddVariant( FDatasmithFacadeVariant* InVariantPtr );`
- L209 _public prototype_ `int32 GetVariantsCount() const;`
- L211 _public prototype_ `FDatasmithFacadeVariant* GetNewVariant( int32 VariantIndex );`
- L215 _public prototype_ `void RemoveVariant( FDatasmithFacadeVariant* InVariantPtr );`
- L223 _protected prototype_ `explicit FDatasmithFacadeVariantSet( const TSharedRef<IDatasmithVariantSetElement>& InInternalVariantSet );`
- L227 _protected prototype_ `TSharedRef<IDatasmithVariantSetElement> GetDatasmithVariantSet() const;`

#### class `FDatasmithFacadeLevelVariantSets`  
`class FDatasmithFacadeLevelVariantSets : public FDatasmithFacadeElement`  
_L230-264_
- inherits: `FDatasmithFacadeElement`
- L235 _public prototype_ `FDatasmithFacadeLevelVariantSets( const TCHAR* InElementName );`
- L239 _public function_ `virtual ~FDatasmithFacadeLevelVariantSets()`
- L241 _public prototype_ `void AddVariantSet( FDatasmithFacadeVariantSet* InVariantSetPtr );`
- L245 _public prototype_ `int32 GetVariantSetsCount() const;`
- L247 _public prototype_ `FDatasmithFacadeVariantSet* GetNewVariantSet( int32 VariantSetIndex );`
- L251 _public prototype_ `void RemoveVariantSet( FDatasmithFacadeVariantSet* InVariantSetPtr );`
- L259 _protected prototype_ `explicit FDatasmithFacadeLevelVariantSets( const TSharedRef<IDatasmithLevelVariantSetsElement>& InInternalLevelVariantsSet );`
- L263 _protected prototype_ `TSharedRef<IDatasmithLevelVariantSetsElement> GetDatasmithLevelVariantSets() const;`

#### Free symbols / members of external scopes

- L33 _macro_ `#define DS_CHECK_ENUM_MISMATCH(name) static_assert((uint64)EDatasmithFacadePropertyCategory::name == (uint64)EDatasmithPropertyCategory::name, "enum mismatch");` — not trivial to reuse EDatasmithMaterialExpressionType (eg with a "using" declaration). #swig

### `Source/Developer/Datasmith/DatasmithFacade/Public/DirectLink/DatasmithFacadeDirectLink.h` (Public)


#### class `FDatasmithFacadeDirectLink`  
`class FDatasmithFacadeDirectLink`  
_L12-42_
- L15 _public prototype_ `static bool Init();`
- L16 _public prototype_ `static bool Init(bool bUseDatasmithExporterUI, const TCHAR* RemoteEngineDirPath);`
- L17 _public function_ `static int ValidateCommunicationSetup()`
- L18 _public prototype_ `static bool Shutdown();`
- L20 _public prototype_ `bool InitializeForScene(FDatasmithFacadeScene* FacadeScene);`
- L21 _public prototype_ `bool UpdateScene(FDatasmithFacadeScene* FacadeScene);`
- L26 _public prototype_ `void CloseCurrentSource();` — Close the initialized DirectLink source if any.
- L32 _public prototype_ `void AddEndpointObserver(FDatasmithFacadeEndpointObserver* Observer);` — Register an IEndpointObserver that will be notified periodically with the last state of the swarm. @param Observer      Object that should be notified
- L38 _public prototype_ `void RemoveEndpointObserver(FDatasmithFacadeEndpointObserver* Observer);` — Removes a previously added observer @param Observer      Observer to remove
- L41 _private member_ `FDatasmithDirectLink Impl;`

### `Source/Developer/Datasmith/DatasmithFacade/Public/DirectLink/DatasmithFacadeEndpointObserver.h` (Public)


#### struct `FDatasmithFacadeRawInfo`  
`struct FDatasmithFacadeRawInfo`  
_L12-141_
- L110 _public function_ `FMessageAddress GetThisEndpointAddress() const` — Returns the MessageAddress associated to the current DirectLink Endpoint.
- L116 _public prototype_ `FDatasmithFacadeEndpointInfo* GetNewEndpointInfo(const FMessageAddress* MessageAddress) const;` — Returns the Endpoint info associated to given MessageAddress, returns null if there is no Endpoint associated to the MessageAddress. The caller is responsible of deleting the returned object pointer.
- L122 _public prototype_ `FDatasmithFacadeDataPointInfo* GetNewDataPointsInfo(const FGuid* Id) const;` — Returns the DataPointInfo (Source or Destination) associated to the given Id, returns null if there is no DataPointInfo associated to the Id. The caller is responsible of deleting the returned object pointer.
- L124 _public function_ `int32 GetNumberOfStreamsInfo() const`
- L130 _public prototype_ `FDatasmithFacadeStreamInfo* GetNewStreamInfo(int32 Index) const;` — Returns the Stream info at the given index, returns null if the index is invalid. The caller is responsible of deleting the returned object pointer.
- L135 _private function_ `explicit FDatasmithFacadeRawInfo(const DirectLink::FRawInfo& InRawInfo) : RawInfo(InRawInfo)`
- L140 _private member_ `DirectLink::FRawInfo RawInfo;`

#### struct `FDatasmithFacadeRawInfo::FDatasmithFacadeDataPointId`  
`struct FDatasmithFacadeDataPointId`  
_L14-31_
- L18 _public function_ `const TCHAR* GetName() const`
- L19 _public function_ `FGuid GetId() const`
- L20 _public function_ `bool IsPublic() const`
- L25 _private function_ `explicit FDatasmithFacadeDataPointId(const DirectLink::FRawInfo::FDataPointId& InDataPointId) : DataPointId(InDataPointId)`
- L30 _private member_ `DirectLink::FRawInfo::FDataPointId DataPointId;`

#### struct `FDatasmithFacadeRawInfo::FDatasmithFacadeEndpointInfo`  
`struct FDatasmithFacadeEndpointInfo`  
_L33-67_
- L36 _public function_ `const TCHAR* GetName() const`
- L38 _public function_ `int32 GetNumberOfDestinations() const`
- L43 _public prototype_ `FDatasmithFacadeDataPointId* GetNewDestination(int32 Index) const;` — Returns the Destination info at the given index, returns null if the index is invalid. The caller is responsible of deleting the returned object pointer.
- L45 _public function_ `int32 GetNumberOfSources() const`
- L50 _public prototype_ `FDatasmithFacadeDataPointId* GetNewSource(int32 Index) const;` — Returns the Source info at the given index, returns null if the index is invalid. The caller is responsible of deleting the returned object pointer.
- L52 _public function_ `const TCHAR* GetUserName() const`
- L53 _public function_ `const TCHAR* GetExecutableName() const`
- L54 _public function_ `const TCHAR* GetComputerName() const`
- L55 _public function_ `bool IsLocal() const`
- L56 _public function_ `uint32 GetProcessId() const`
- L61 _private function_ `explicit FDatasmithFacadeEndpointInfo(const DirectLink::FRawInfo::FEndpointInfo& InEndpointInfo) : EndpointInfo(InEndpointInfo)`
- L66 _private member_ `DirectLink::FRawInfo::FEndpointInfo EndpointInfo;`

#### struct `FDatasmithFacadeRawInfo::FDatasmithFacadeDataPointInfo`  
`struct FDatasmithFacadeDataPointInfo`  
_L69-86_
- L71 _public function_ `FMessageAddress GetEndpointAddress() const`
- L72 _public function_ `const TCHAR* GetName() const`
- L73 _public function_ `bool IsSource() const`
- L74 _public function_ `bool IsOnThisEndpoint() const`
- L75 _public function_ `bool IsPublic() const`
- L80 _private function_ `explicit FDatasmithFacadeDataPointInfo(const DirectLink::FRawInfo::FDataPointInfo& InDataPointInfo) : DataPointInfo(InDataPointInfo)`
- L85 _private member_ `DirectLink::FRawInfo::FDataPointInfo DataPointInfo;`

#### struct `FDatasmithFacadeRawInfo::FDatasmithFacadeStreamInfo`  
`struct FDatasmithFacadeStreamInfo`  
_L88-105_
- L91 _public function_ `uint32 GetStreamId() const`
- L92 _public function_ `FGuid GetSource() const`
- L93 _public function_ `FGuid GetDestination() const`
- L94 _public function_ `bool IsActive() const`
- L99 _private function_ `explicit FDatasmithFacadeStreamInfo(const DirectLink::FRawInfo::FStreamInfo& InStreamInfo) : StreamInfo(InStreamInfo)`
- L104 _private member_ `DirectLink::FRawInfo::FStreamInfo StreamInfo;`

#### class `FDatasmithFacadeEndpointObserver`  
`class FDatasmithFacadeEndpointObserver`  
_L145-163_
- L148 _public typedef_ `typedef void(*OnStateChangedDelegate)(FDatasmithFacadeRawInfo*);`
- L150 _public prototype_ `FDatasmithFacadeEndpointObserver();`
- L152 _public prototype_ `void RegisterOnStateChangedDelegateInternal(FDatasmithFacadeEndpointObserver::OnStateChangedDelegate InOnStateChanged);`
- L153 _public prototype_ `void UnregisterOnStateChangedDelegateInternal(FDatasmithFacadeEndpointObserver::OnStateChangedDelegate InOnStateChanged);`
- L159 _private function_ `const TSharedRef<FDatasmithFacadeEndpointObserverImpl>& GetObserver() const`
- L162 _private member_ `TSharedRef<FDatasmithFacadeEndpointObserverImpl> ObserverImpl;`
