# Plugins / InterchangeNodes

- module root: `Plugins/Interchange/Runtime/Source/Nodes`
- headers: 34; symbols: 1700
- symbol kinds: class=50, delegate=3, enum=17, enumerator=407, function=127, macro=19, member=75, namespace=143, prototype=544, struct=11, variable=304
- PublicDependencyModuleNames: Core, CoreUObject, InterchangeCore

### `Plugins/Interchange/Runtime/Source/Nodes/Private/InterchangeNodeLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeNode, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeNode, Log, All);`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeAnimationDefinitions.h` (Public)


#### enum `EInterchangePropertyTracks`  
`enum class EInterchangePropertyTracks : int32`  
_L11-356_
- reflection: `UENUM()`
- L14 _public enumerator_ `AffectDistanceFieldLighting` — Common Properties
- L15 _public enumerator_ `AffectDynamicIndirectLighting`
- L16 _public enumerator_ `AffectIndirectLightingWhileHidden`
- L17 _public enumerator_ `AutoActivate`
- L18 _public enumerator_ `BodyInstanceAngularDamping`
- L19 _public enumerator_ `BodyInstancebEnableGravity`
- L20 _public enumerator_ `BodyInstancebNotifyRigidBodyCollision`
- L21 _public enumerator_ `BodyInstancebSimulatePhysics`
- L22 _public enumerator_ `BodyInstancebUpdateKinematicFromSimulation`
- L23 _public enumerator_ `BodyInstancebUseCCD`
- L24 _public enumerator_ `BodyInstanceLinearDamping`
- L25 _public enumerator_ `BodyInstanceMassScale`
- L26 _public enumerator_ `BoundsScale`
- L27 _public enumerator_ `CastContactShadow`
- L28 _public enumerator_ `CastHiddenShadow`
- L29 _public enumerator_ `CastInsetShadow`
- L30 _public enumerator_ `CastShadow`
- L31 _public enumerator_ `CustomDepthStencilValue`
- L32 _public enumerator_ `CustomDepthStencilWriteMask`
- L33 _public enumerator_ `DefaultUpVector`
- L34 _public enumerator_ `DrawDebug`
- L35 _public enumerator_ `EmissiveLightSource`
- L36 _public enumerator_ `ExcludeFromLightAttachmentGroup`
- L37 _public enumerator_ `HiddenInGame` — This visibility property is set on the Component
- L38 _public enumerator_ `HiddenInSceneCapture`
- L39 _public enumerator_ `Holdout`
- L40 _public enumerator_ `LightAttachmentsAsGroup`
- L41 _public enumerator_ `Mobility`
- L42 _public enumerator_ `OnlyOwnerSee`
- L43 _public enumerator_ `OwnerNoSee`
- L44 _public enumerator_ `ReceivesDecals`
- L45 _public enumerator_ `RenderCustomDepth`
- L46 _public enumerator_ `RenderInDepthPass`
- L47 _public enumerator_ `RenderInMainPass`
- L48 _public enumerator_ `SingleSampleShadowFromStationaryLights`
- L49 _public enumerator_ `TranslucencySortDistanceOffset`
- L50 _public enumerator_ `VisibleInRayTracing`
- L51 _public enumerator_ `VisibleInReflections`
- L52 _public enumerator_ `VisibleInSceneCaptureOnly`
- L53 _public enumerator_ `ActorHiddenInGame` — This visibility property is set on the Actor
- L56 _public enumerator_ `LightAffectGlobalIllumination` — Light Properties
- L57 _public enumerator_ `LightAffectReflection`
- L58 _public enumerator_ `LightAffectTranslucentLighting`
- L59 _public enumerator_ `LightAtmosphereSunDiskColorScale`
- L60 _public enumerator_ `LightAtmosphereSunLight`
- L61 _public enumerator_ `LightAtmosphereSunLightIndex`
- L62 _public enumerator_ `LightAttenuationRadius`
- L63 _public enumerator_ `LightBarnDoorAngle`
- L64 _public enumerator_ `LightBarnDoorLength`
- L65 _public enumerator_ `LightBloomMaxBrightness`
- L66 _public enumerator_ `LightBloomScale`
- L67 _public enumerator_ `LightBloomThreshold`
- L68 _public enumerator_ `LightBloomTint`
- L69 _public enumerator_ `LightCascadeDistributionExponent`
- L70 _public enumerator_ `LightCascadeTransitionFraction`
- L71 _public enumerator_ `LightCastDeepShadow`
- L72 _public enumerator_ `LightCastShadows`
- L73 _public enumerator_ `LightCastVolumetricShadow`
- L74 _public enumerator_ `LightCloudAmbientOcclusionStrength`
- L75 _public enumerator_ `LightCloudScatteredLuminanceScale`
- L76 _public enumerator_ `LightCloudShadowOnAtmosphereStrength`
- L77 _public enumerator_ `LightCloudShadowOnSurfaceStrength`
- L78 _public enumerator_ `LightCloudShadowStrength`
- L79 _public enumerator_ `LightColor`
- L80 _public enumerator_ `LightDynamicShadowCascades`
- L81 _public enumerator_ `LightDynamicShadowDistanceMovableLight`
- L82 _public enumerator_ `LightDynamicShadowDistanceStationaryLight`
- L83 _public enumerator_ `LightEnableLightShaftBloom`
- L84 _public enumerator_ `LightEnableLightShaftOcclusion`
- L85 _public enumerator_ `LightFalloffExponent`
- L86 _public enumerator_ `LightForceCachedShadowsForMovablePrimitives`
- L87 _public enumerator_ `LightForwardShadingPriority`
- L88 _public enumerator_ `LightFunctionFadeDistance`
- L89 _public enumerator_ `LightFunctionScale`
- L90 _public enumerator_ `LightIESBrightnessScale`
- L91 _public enumerator_ `LightIndirectLightingIntensity`
- L92 _public enumerator_ `LightInnerConeAngle`
- L93 _public enumerator_ `LightIntensity`
- L94 _public enumerator_ `LightIntensityUnits`
- L95 _public enumerator_ `LightInverseExposureBlend`
- L96 _public enumerator_ `LightLowerHemisphereColor`
- L97 _public enumerator_ `LightmassSettingsLightSourceAngle`
- L98 _public enumerator_ `LightMinOcclusion`
- L99 _public enumerator_ `LightModulatedShadowColor`
- L100 _public enumerator_ `LightOcclusionDepthRange`
- L101 _public enumerator_ `LightOcclusionExponent`
- L102 _public enumerator_ `LightOcclusionMaskDarkness`
- L103 _public enumerator_ `LightOcclusionTint`
- L104 _public enumerator_ `LightOuterConeAngle`
- L105 _public enumerator_ `LightSamplesPerPixel`
- L106 _public enumerator_ `LightShadowAmount`
- L107 _public enumerator_ `LightShadowBias`
- L108 _public enumerator_ `LightShadowCascadeBiasDistribution`
- L109 _public enumerator_ `LightShadowDistanceFadeoutFraction`
- L110 _public enumerator_ `LightShadowSlopeBias`
- L111 _public enumerator_ `LightShadowSourceAngleFactor`
- L112 _public enumerator_ `LightShaftOverrideDirection`
- L113 _public enumerator_ `LightSoftSourceRadius`
- L114 _public enumerator_ `LightSourceAngle`
- L115 _public enumerator_ `LightSourceCubemapAngle`
- L116 _public enumerator_ `LightSourceHeight`
- L117 _public enumerator_ `LightSourceLength`
- L118 _public enumerator_ `LightSourceRadius`
- L119 _public enumerator_ `LightSourceSoftAngle`
- L120 _public enumerator_ `LightSourceWidth`
- L121 _public enumerator_ `LightSpecularScale`
- L122 _public enumerator_ `LightDiffuseScale`
- L123 _public enumerator_ `LightTemperature`
- L124 _public enumerator_ `LightTransmission`
- L125 _public enumerator_ `LightUseIESBrightness`
- L126 _public enumerator_ `LightUseInverseSquaredFalloff`
- L127 _public enumerator_ `LightUseTemperature`
- L128 _public enumerator_ `LightVolumetricScatteringIntensity`
- L131 _public enumerator_ `CameraAspectRatio` — Camera Properties
- L132 _public enumerator_ `CameraAspectRatioAxisConstraint`
- L133 _public enumerator_ `CameraAutoCalculateOrthoPlanes`
- L134 _public enumerator_ `CameraAutoPlaneShift`
- L135 _public enumerator_ `CameraConstrainAspectRatio`
- L136 _public enumerator_ `CameraCurrentAperture`
- L137 _public enumerator_ `CameraCurrentFocalLength`
- L138 _public enumerator_ `CameraCustomNearClippingPlane`
- L139 _public enumerator_ `CameraFieldOfView`
- L140 _public enumerator_ `CameraFilmbackSensorAspectRatio`
- L141 _public enumerator_ `CameraFilmbackSensorHeight`
- L142 _public enumerator_ `CameraFilmbackSensorHorizontalOffset`
- L143 _public enumerator_ `CameraFilmbackSensorVerticalOffset`
- L144 _public enumerator_ `CameraFilmbackSensorWidth`
- L145 _public enumerator_ `CameraFocusSettingsFocusOffset`
- L146 _public enumerator_ `CameraFocusSettingsManualFocusDistance`
- L147 _public enumerator_ `CameraFocusSettingsTrackingFocusSettingsRelativeOffset`
- L148 _public enumerator_ `CameraOrthoFarClipPlane`
- L149 _public enumerator_ `CameraOrthoNearClipPlane`
- L150 _public enumerator_ `CameraOrthoWidth`
- L151 _public enumerator_ `CameraOverrideAspectRatioAxisConstraint`
- L152 _public enumerator_ `CameraPostProcessBlendWeight`
- L153 _public enumerator_ `CameraPostProcessSettingsAmbientCubemapIntensity`
- L154 _public enumerator_ `CameraPostProcessSettingsAmbientCubemapTint`
- L155 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionBias`
- L156 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionFadeDistance`
- L157 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionFadeRadius`
- L158 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionIntensity`
- L159 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionMipBlend`
- L160 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionMipScale`
- L161 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionMipThreshold`
- L162 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionPower`
- L163 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionQuality`
- L164 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionRadius`
- L165 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionStaticFraction`
- L166 _public enumerator_ `CameraPostProcessSettingsAmbientOcclusionTemporalBlendWeight`
- L167 _public enumerator_ `CameraPostProcessSettingsAutoExposureBias`
- L168 _public enumerator_ `CameraPostProcessSettingsAutoExposureHighPercent`
- L169 _public enumerator_ `CameraPostProcessSettingsAutoExposureLowPercent`
- L170 _public enumerator_ `CameraPostProcessSettingsAutoExposureMaxBrightness`
- L171 _public enumerator_ `CameraPostProcessSettingsAutoExposureMinBrightness`
- L172 _public enumerator_ `CameraPostProcessSettingsAutoExposureSpeedDown`
- L173 _public enumerator_ `CameraPostProcessSettingsAutoExposureSpeedUp`
- L174 _public enumerator_ `CameraPostProcessSettingsBloom1Size`
- L175 _public enumerator_ `CameraPostProcessSettingsBloom1Tint`
- L176 _public enumerator_ `CameraPostProcessSettingsBloom2Size`
- L177 _public enumerator_ `CameraPostProcessSettingsBloom2Tint`
- L178 _public enumerator_ `CameraPostProcessSettingsBloom3Size`
- L179 _public enumerator_ `CameraPostProcessSettingsBloom3Tint`
- L180 _public enumerator_ `CameraPostProcessSettingsBloom4Size`
- L181 _public enumerator_ `CameraPostProcessSettingsBloom4Tint`
- L182 _public enumerator_ `CameraPostProcessSettingsBloom5Size`
- L183 _public enumerator_ `CameraPostProcessSettingsBloom5Tint`
- L184 _public enumerator_ `CameraPostProcessSettingsBloom6Size`
- L185 _public enumerator_ `CameraPostProcessSettingsBloom6Tint`
- L186 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionBufferScale`
- L187 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionCenterUV`
- L188 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionPreFilterMax`
- L189 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionPreFilterMin`
- L190 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionPreFilterMult`
- L191 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionScatterDispersion`
- L192 _public enumerator_ `CameraPostProcessSettingsBloomConvolutionSize`
- L193 _public enumerator_ `CameraPostProcessSettingsBloomDirtMaskIntensity`
- L194 _public enumerator_ `CameraPostProcessSettingsBloomDirtMaskTint`
- L195 _public enumerator_ `CameraPostProcessSettingsBloomIntensity`
- L196 _public enumerator_ `CameraPostProcessSettingsBloomSizeScale`
- L197 _public enumerator_ `CameraPostProcessSettingsBloomThreshold`
- L198 _public enumerator_ `CameraPostProcessSettingsBlueCorrection`
- L199 _public enumerator_ `CameraPostProcessSettingsCameraISO`
- L200 _public enumerator_ `CameraPostProcessSettingsCameraShutterSpeed`
- L201 _public enumerator_ `CameraPostProcessSettingsChromaticAberrationStartOffset`
- L202 _public enumerator_ `CameraPostProcessSettingsColorContrast`
- L203 _public enumerator_ `CameraPostProcessSettingsColorContrastHighlights`
- L204 _public enumerator_ `CameraPostProcessSettingsColorContrastMidtones`
- L205 _public enumerator_ `CameraPostProcessSettingsColorContrastShadows`
- L206 _public enumerator_ `CameraPostProcessSettingsColorCorrectionHighlightsMax`
- L207 _public enumerator_ `CameraPostProcessSettingsColorCorrectionHighlightsMin`
- L208 _public enumerator_ `CameraPostProcessSettingsColorCorrectionShadowsMax`
- L209 _public enumerator_ `CameraPostProcessSettingsColorGain`
- L210 _public enumerator_ `CameraPostProcessSettingsColorGainHighlights`
- L211 _public enumerator_ `CameraPostProcessSettingsColorGainMidtones`
- L212 _public enumerator_ `CameraPostProcessSettingsColorGainShadows`
- L213 _public enumerator_ `CameraPostProcessSettingsColorGamma`
- L214 _public enumerator_ `CameraPostProcessSettingsColorGammaHighlights`
- L215 _public enumerator_ `CameraPostProcessSettingsColorGammaMidtones`
- L216 _public enumerator_ `CameraPostProcessSettingsColorGammaShadows`
- L217 _public enumerator_ `CameraPostProcessSettingsColorGradingIntensity`
- L218 _public enumerator_ `CameraPostProcessSettingsColorOffset`
- L219 _public enumerator_ `CameraPostProcessSettingsColorOffsetHighlights`
- L220 _public enumerator_ `CameraPostProcessSettingsColorOffsetMidtones`
- L221 _public enumerator_ `CameraPostProcessSettingsColorOffsetShadows`
- L222 _public enumerator_ `CameraPostProcessSettingsColorSaturation`
- L223 _public enumerator_ `CameraPostProcessSettingsColorSaturationHighlights`
- L224 _public enumerator_ `CameraPostProcessSettingsColorSaturationMidtones`
- L225 _public enumerator_ `CameraPostProcessSettingsColorSaturationShadows`
- L226 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldBladeCount`
- L227 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldDepthBlurAmount`
- L228 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldDepthBlurRadius`
- L229 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldFarBlurSize`
- L230 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldFarTransitionRegion`
- L231 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldFocalDistance`
- L232 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldFocalRegion`
- L233 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldFstop`
- L234 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldMinFstop`
- L235 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldNearBlurSize`
- L236 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldNearTransitionRegion`
- L237 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldOcclusion`
- L238 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldScale`
- L239 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldSkyFocusDistance`
- L240 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldUseHairDepth`
- L241 _public enumerator_ `CameraPostProcessSettingsDepthOfFieldVignetteSize`
- L242 _public enumerator_ `CameraPostProcessSettingsDynamicGlobalIlluminationMethod`
- L243 _public enumerator_ `CameraPostProcessSettingsExpandGamut`
- L244 _public enumerator_ `CameraPostProcessSettingsFilmBlackClip`
- L245 _public enumerator_ `CameraPostProcessSettingsFilmGrainHighlightsMax`
- L246 _public enumerator_ `CameraPostProcessSettingsFilmGrainHighlightsMin`
- L247 _public enumerator_ `CameraPostProcessSettingsFilmGrainIntensity`
- L248 _public enumerator_ `CameraPostProcessSettingsFilmGrainIntensityHighlights`
- L249 _public enumerator_ `CameraPostProcessSettingsFilmGrainIntensityMidtones`
- L250 _public enumerator_ `CameraPostProcessSettingsFilmGrainIntensityShadows`
- L251 _public enumerator_ `CameraPostProcessSettingsFilmGrainShadowsMax`
- L252 _public enumerator_ `CameraPostProcessSettingsFilmGrainScale`
- L253 _public enumerator_ `CameraPostProcessSettingsFilmShoulder`
- L254 _public enumerator_ `CameraPostProcessSettingsFilmSlope`
- L255 _public enumerator_ `CameraPostProcessSettingsFilmToe`
- L256 _public enumerator_ `CameraPostProcessSettingsFilmWhiteClip`
- L257 _public enumerator_ `CameraPostProcessSettingsHistogramLogMax`
- L258 _public enumerator_ `CameraPostProcessSettingsHistogramLogMin`
- L259 _public enumerator_ `CameraPostProcessSettingsIndirectLightingColor`
- L260 _public enumerator_ `CameraPostProcessSettingsIndirectLightingIntensity`
- L261 _public enumerator_ `CameraPostProcessSettingsLensFlareBokehSize`
- L262 _public enumerator_ `CameraPostProcessSettingsLensFlareIntensity`
- L263 _public enumerator_ `CameraPostProcessSettingsLensFlareThreshold`
- L264 _public enumerator_ `CameraPostProcessSettingsLensFlareTint`
- L265 _public enumerator_ `CameraPostProcessSettingsLocalExposureBlurredLuminanceBlend`
- L266 _public enumerator_ `CameraPostProcessSettingsLocalExposureBlurredLuminanceKernelSizePercent`
- L267 _public enumerator_ `CameraPostProcessSettingsLocalExposureDetailStrength`
- L268 _public enumerator_ `CameraPostProcessSettingsLocalExposureHighlightContrastScale`
- L269 _public enumerator_ `CameraPostProcessSettingsLocalExposureHighlightThreshold`
- L270 _public enumerator_ `CameraPostProcessSettingsLocalExposureMiddleGreyBias`
- L271 _public enumerator_ `CameraPostProcessSettingsLocalExposureShadowContrastScale`
- L272 _public enumerator_ `CameraPostProcessSettingsLocalExposureShadowThreshold`
- L273 _public enumerator_ `CameraPostProcessSettingsLumenDiffuseColorBoost`
- L274 _public enumerator_ `CameraPostProcessSettingsLumenAmbientOcclusionIntensity`
- L275 _public enumerator_ `CameraPostProcessSettingsLumenFinalGatherLightingUpdateSpeed`
- L276 _public enumerator_ `CameraPostProcessSettingsLumenFinalGatherQuality`
- L277 _public enumerator_ `CameraPostProcessSettingsLumenFinalGatherScreenTraces`
- L278 _public enumerator_ `CameraPostProcessSettingsLumenFrontLayerTranslucencyReflections`
- L279 _public enumerator_ `CameraPostProcessSettingsLumenFullSkylightLeakingDistance`
- L280 _public enumerator_ `CameraPostProcessSettingsLumenMaxReflectionBounces`
- L281 _public enumerator_ `CameraPostProcessSettingsLumenMaxRefractionBounces`
- L282 _public enumerator_ `CameraPostProcessSettingsLumenMaxRoughnessToTraceReflections`
- L283 _public enumerator_ `CameraPostProcessSettingsLumenMaxTraceDistance`
- L284 _public enumerator_ `CameraPostProcessSettingsLumenRayLightingMode`
- L285 _public enumerator_ `CameraPostProcessSettingsLumenReflectionQuality`
- L286 _public enumerator_ `CameraPostProcessSettingsLumenReflectionsScreenTraces`
- L287 _public enumerator_ `CameraPostProcessSettingsLumenSceneDetail`
- L288 _public enumerator_ `CameraPostProcessSettingsLumenSceneLightingQuality`
- L289 _public enumerator_ `CameraPostProcessSettingsLumenSceneLightingUpdateSpeed`
- L290 _public enumerator_ `CameraPostProcessSettingsLumenSceneViewDistance`
- L291 _public enumerator_ `CameraPostProcessSettingsLumenSkylightLeaking`
- L292 _public enumerator_ `CameraPostProcessSettingsLumenSkylightLeakingTint`
- L293 _public enumerator_ `CameraPostProcessSettingsMotionBlurAmount`
- L294 _public enumerator_ `CameraPostProcessSettingsMotionBlurMax`
- L295 _public enumerator_ `CameraPostProcessSettingsMotionBlurPerObjectSize`
- L296 _public enumerator_ `CameraPostProcessSettingsPathTracingMaxBounces`
- L297 _public enumerator_ `CameraPostProcessSettingsPathTracingMaxPathIntensity`
- L298 _public enumerator_ `CameraPostProcessSettingsRayTracingAO`
- L299 _public enumerator_ `CameraPostProcessSettingsRayTracingAOIntensity`
- L300 _public enumerator_ `CameraPostProcessSettingsRayTracingAORadius`
- L301 _public enumerator_ `CameraPostProcessSettingsRayTracingAOSamplesPerPixel`
- L302 _public enumerator_ `CameraPostProcessSettingsRayTracingTranslucencyMaxRoughness`
- L303 _public enumerator_ `CameraPostProcessSettingsRayTracingTranslucencyRefraction`
- L304 _public enumerator_ `CameraPostProcessSettingsRayTracingTranslucencyRefractionRays`
- L305 _public enumerator_ `CameraPostProcessSettingsRayTracingTranslucencySamplesPerPixel`
- L306 _public enumerator_ `CameraPostProcessSettingsRayTracingTranslucencyShadows`
- L307 _public enumerator_ `CameraPostProcessSettingsReflectionMethod`
- L308 _public enumerator_ `CameraPostProcessSettingsSceneColorTint`
- L309 _public enumerator_ `CameraPostProcessSettingsSceneFringeIntensity`
- L310 _public enumerator_ `CameraPostProcessSettingsScreenSpaceReflectionIntensity`
- L311 _public enumerator_ `CameraPostProcessSettingsScreenSpaceReflectionMaxRoughness`
- L312 _public enumerator_ `CameraPostProcessSettingsScreenSpaceReflectionQuality`
- L313 _public enumerator_ `CameraPostProcessSettingsSharpen`
- L314 _public enumerator_ `CameraPostProcessSettingsTemperatureType`
- L315 _public enumerator_ `CameraPostProcessSettingsToneCurveAmount`
- L316 _public enumerator_ `CameraPostProcessSettingsTranslucencyType`
- L317 _public enumerator_ `CameraPostProcessSettingsVignetteIntensity`
- L318 _public enumerator_ `CameraPostProcessSettingsWhiteTemp`
- L319 _public enumerator_ `CameraPostProcessSettingsWhiteTint`
- L320 _public enumerator_ `CameraProjectionMode`
- L321 _public enumerator_ `CameraUpdateOrthoPlanes`
- L322 _public enumerator_ `CameraUseCameraHeightAsViewTarget`
- L323 _public enumerator_ `CameraUseFieldOfViewForLOD`
- L326 _public enumerator_ `MeshOverlayMaterialMaxDrawDistance` — Common Mesh Properties
- L329 _public enumerator_ `SkinnedMeshCapsuleIndirectShadowMinVisibility` — Skinned Mesh Properties
- L330 _public enumerator_ `SkinnedMeshCastCapsuleDirectShadow`
- L331 _public enumerator_ `SkinnedMeshCastCapsuleIndirectShadow`
- L332 _public enumerator_ `SkinnedMeshRenderStatic`
- L333 _public enumerator_ `SkinnedMeshVisibilityBasedAnimTickOption`
- L336 _public enumerator_ `SkeletalMesh` — Skeletal Mesh Properties
- L337 _public enumerator_ `SkeletalMeshAllowClothActors`
- L338 _public enumerator_ `SkeletalMeshAnimationMode`
- L339 _public enumerator_ `SkeletalMeshClothBlendWeight`
- L340 _public enumerator_ `SkeletalMeshClothMaxDistanceScale`
- L343 _public enumerator_ `StaticMeshDistanceFieldSelfShadowBias` — Static Mesh Properties
- L344 _public enumerator_ `StaticMeshEvaluateWorldPositionOffset`
- L345 _public enumerator_ `StaticMeshEvaluateWorldPositionOffsetInRayTracing`
- L346 _public enumerator_ `StaticMeshForcedLodModel`
- L347 _public enumerator_ `StaticMeshReverseCulling`
- L348 _public enumerator_ `StaticMeshWorldPositionOffsetDisableDistance`
- L349 _public enumerator_ `StaticMesh`
- L352 _public enumerator_ `HeterogeneousVolumeFrame` — Heterogeneous Volume Component Properties
- L354 _public enumerator_ `None = -1 UMETA(hidden)`
- L355 _public enumerator_ `Visibility UE_DEPRECATED(5.6, "Renamed to 'ActorHiddenInGame'") = ActorHiddenInGame UMETA(hidden)`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeAnimationTrackSetNode.h` (Public)


#### enum `EInterchangeAnimationPayLoadType`  
`enum class EInterchangeAnimationPayLoadType : uint8`  
_L14-29_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `NONE = 0`
- L17 _public enumerator_ `CURVE`
- L18 _public enumerator_ `MORPHTARGETCURVE` — Handles/generates the same properties as the CURVE variation, but the way it is acquired might be different (depending on the Translator).
- L19 _public enumerator_ `STEPCURVE`
- L20 _public enumerator_ `BAKED`
- L21 _public enumerator_ `MORPHTARGETCURVEWEIGHTINSTANCE` — Handled within UInterchangeAnimSequenceFactory, contrary to the others which are handled in the Translators
- L28 _public enumerator_ `GEOMETRY_CACHE_TRANSFORM` — Purpose of this type is to generate a 1 frame long Animation with the Instantiated Morph Target Curve Weights. This is needed for the special use cases where the imported 3d file format has a concept of MorphTargetWeight usages on StaticMeshes. UE5 does not have support for this particular concept, and the workaround is to create a 1 frame long animation with the desired MorphTargetWeight settings. This is also needed for the use cases where the import is a Level import and the 3d file format is instantiating a StaticMesh with a particular MorphTargetWeight settings. This is done through the AnimSequnce being used on the SkeletalMeshActor's instance. Related Ticket: UE-186102

#### struct `FInterchangeAnimationPayLoadKey`  
`struct FInterchangeAnimationPayLoadKey`  
_L33-62_
- reflection: `USTRUCT(BlueprintType)`
- L40 _public member_ `FString UniqueId = "";` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Node")`
- L43 _public member_ `EInterchangeAnimationPayLoadType Type = EInterchangeAnimationPayLoadType::NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Node")`
- L45 _public function_ `FInterchangeAnimationPayLoadKey()`
- L47 _public function_ `FInterchangeAnimationPayLoadKey(const FString& InUniqueId, const EInterchangeAnimationPayLoadType& InType) : UniqueId(InUniqueId) , Type(InType)`
- L53 _public function_ `bool operator==(const FInterchangeAnimationPayLoadKey& Other) const`

#### struct `UE::Interchange::FAnimationStaticData`  
`struct FAnimationStaticData : public FBaseNodeStaticData`  
_L70-76_
- inherits: `FBaseNodeStaticData`
- L72 _public prototype_ `static const FAttributeKey& AnimationPayLoadUidKey();`
- L73 _public prototype_ `static const FAttributeKey& AnimationPayLoadTypeKey();`
- L74 _public prototype_ `static const FAttributeKey& MorphTargetAnimationPayLoadUidKey();`
- L75 _public prototype_ `static const FAttributeKey& MorphTargetAnimationPayLoadTypeKey();`

#### enum `EInterchangeAnimatedProperty`  
`enum class EInterchangeAnimatedProperty : uint8`  
_L89-94_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration specifying which properties of a camera, light or scene node can be animated besides transform.
- L91 _public enumerator_ `None UMETA(DisplayName = "No property.", ToolTip = "The associated animation track will be ignored.")`
- L92 _public enumerator_ `Visibility UMETA(DisplayName = "Visibility property.", ToolTip = "The associated animation track is applied to the visibility property of the actor.")`
- L93 _public enumerator_ `MAX`

#### enum `EInterchangeAimationCompletionMode`  
`enum class EInterchangeAimationCompletionMode : uint8`  
_L98-106_
- desc: Enumeration specifying how to handle the state of the animated property at the end of an animation track.
- L101 _public enumerator_ `KeepState` — Keep the animated property at the state set at the end of the animation track.
- L103 _public enumerator_ `RestoreState` — Restore the animated property to its state before the start of the animation track.
- L105 _public enumerator_ `ProjectDefault` — Restore the animated property to the state set in the project for that property.

#### class `UInterchangeAnimationTrackSetNode`  
`class UInterchangeAnimationTrackSetNode : public UInterchangeBaseNode`  
_L112-179_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- desc: Class to represent a set of animation track nodes that share the same frame rate.
- L116 _private prototype_ `UInterchangeAnimationTrackSetNode();`
- L119 _public function_ `static FStringView StaticAssetTypeName()`
- L127 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L137 _public prototype_ `int32 GetCustomAnimationTrackUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Retrieve the number of track dependencies for this object.
- L143 _public prototype_ `void GetCustomAnimationTrackUids(TArray<FString>& OutAnimationTrackUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Retrieve the track dependency for this object.
- L149 _public prototype_ `void GetCustomAnimationTrackUid(const int32 Index, FString& OutAnimationTrackUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Retrieve one track dependency for this object.
- L155 _public prototype_ `bool AddCustomAnimationTrackUid(const FString& AnimationTrackUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Add one track dependency to this object.
- L161 _public prototype_ `bool RemoveCustomAnimationTrackUid(const FString& AnimationTrackUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Remove one track dependency from this object.
- L167 _public prototype_ `bool SetCustomFrameRate(const float& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Set the frame rate for the animations in the level sequence.
- L173 _public prototype_ `bool GetCustomFrameRate(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSet")` — Get the frame rate for the animations in the level sequence.
- L176 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomFrameRateKey = UE::Interchange::FAttributeKey(TEXT("Fram`
- L178 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> CustomAnimationTrackUids;`

#### class `UInterchangeAnimationTrackBaseNode`  
`class UInterchangeAnimationTrackBaseNode : public UInterchangeBaseNode`  
_L185-219_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- desc: Abstract class providing the minimal services required for an animation track node.
- L190 _public function_ `static FStringView StaticAssetTypeName()`
- L198 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L208 _public prototype_ `bool SetCustomCompletionMode(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Set how the actor's animated property should behave once its animation completes.
- L215 _public prototype_ `bool GetCustomCompletionMode(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Get how the actor's animated property behaves once this animation is complete. The output value will be clamped to the range of values defined in EInterchangeAimationCompletionMode.
- L218 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomCompletionModeKey = UE::Interchange::FAttributeKey(TEXT("Comp`

#### class `UInterchangeAnimationTrackSetInstanceNode`  
`class UInterchangeAnimationTrackSetInstanceNode : public UInterchangeAnimationTrackBaseNode`  
_L225-297_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeAnimationTrackBaseNode`
- desc: Class to represent an animation that instances another animation track set node.
- L230 _public function_ `static FStringView StaticAssetTypeName()`
- L238 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L248 _public prototype_ `bool SetCustomTimeScale(const float& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Set the time scale used for the level sequence instance.
- L254 _public prototype_ `bool GetCustomTimeScale(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Get the time scale used for the level sequence instance.
- L260 _public prototype_ `bool SetCustomDuration(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Set the level sequence instance duration in number of frames.
- L266 _public prototype_ `bool GetCustomDuration(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Get the level sequence instance duration in number of frames.
- L272 _public prototype_ `bool SetCustomStartFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Set the frame where the level sequence instance starts.
- L278 _public prototype_ `bool GetCustomStartFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Get the frame where the level sequence instance starts.
- L284 _public prototype_ `bool SetCustomTrackSetDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Set the unique id of the level sequence this instance references.
- L290 _public prototype_ `bool GetCustomTrackSetDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrackSetInstance")` — Get the unique id of the level sequence this instance references.
- L293 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomStartFrameKey = UE::Interchange::FAttributeKey(TEXT("Star`
- L294 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDurationKey = UE::Interchange::FAttributeKey(TEXT("Dura`
- L295 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomTimeScaleKey = UE::Interchange::FAttributeKey(TEXT("Time`
- L296 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomTrackSetDependencyUidKey = UE::Interchange::FAttributeKey(TEXT("Sequ`

#### class `UInterchangeAnimationTrackNode`  
`class UInterchangeAnimationTrackNode : public UInterchangeAnimationTrackBaseNode`  
_L304-384_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeAnimationTrackBaseNode`
- desc: Class to represent an animation on the property of a camera, light, or scene node The list of supported properties is enumerated in EInterchangeAnimatedProperty.
- L309 _public function_ `static FStringView StaticAssetTypeName()`
- L317 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L327 _public prototype_ `bool SetCustomActorDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Set the actor dependency to this object.
- L333 _public prototype_ `bool GetCustomActorDependencyUid(FString& DependencyUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Get the actor dependency to this object.
- L336 _public prototype_ `bool SetCustomPropertyTrack(const FName& PropertyTrack);` — `UE_DEPRECATED(5.5, "SetCustomPropertyTrack using an FName has been deprecated, please use the function with the enum instead.")`
- L339 _public prototype_ `bool GetCustomPropertyTrack(FName& PropertyTrack) const;` — `UE_DEPRECATED(5.5, "SetCustomPropertyTrack using an FName has been deprecated, please use the function with the enum instead.")`
- L345 _public prototype_ `bool SetCustomPropertyTrack(EInterchangePropertyTracks PropertyTrack);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Set the property animated by this track.
- L351 _public prototype_ `bool GetCustomPropertyTrack(EInterchangePropertyTracks& PropertyTrack) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Get the property animated by this track.
- L357 _public prototype_ `bool SetCustomAnimationPayloadKey(const FString& InUniqueId, const EInterchangeAnimationPayLoadType& InType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Set the payload key needed to retrieve the animation for this track.
- L363 _public prototype_ `bool GetCustomAnimationPayloadKey(FInterchangeAnimationPayLoadKey& AnimationPayLoadKey) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Get the payload key needed to retrieve the animation for this track.
- L369 _public prototype_ `bool SetCustomFrameCount(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Set the number of frames for the animation of this track.
- L375 _public prototype_ `bool GetCustomFrameCount(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimationTrack")` — Get the number of frames for the animation of this track.
- L378 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomActorDependencyKey = UE::Interchange::FAttributeKey(TEXT("Acto`
- L379 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAnimationPayloadUidKey = UE::Interchange::FAttributeKey(TEXT("Anim`
- L380 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAnimationPayloadTypeKey = UE::Interchange::FAttributeKey(TEXT("Anim`
- L381 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomFrameCountKey = UE::Interchange::FAttributeKey(TEXT("Fram`
- L382 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomTargetedPropertyKey = UE::Interchange::FAttributeKey(TEXT("Targ`
- L383 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomPropertyTrackKey = UE::Interchange::FAttributeKey(TEXT("Prop`

#### class `UInterchangeTransformAnimationTrackNode`  
`class UInterchangeTransformAnimationTrackNode : public UInterchangeAnimationTrackNode`  
_L390-441_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeAnimationTrackNode`
- desc: Class to represent an animation on the transform of a camera, light, or scene node.
- L395 _public function_ `static FStringView StaticAssetTypeName()`
- L403 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L430 _public prototype_ `bool SetCustomUsedChannels(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | TransformAnimationTrack")` — Set which channels of this animation should be used. This is a bitwise mask. Bits are interpreted as follow: None          = 0x000, TranslationX  = 0x001, TranslationY  = 0x002, TranslationZ  = 0x004, Translation   = TranslationX | TranslationY | TranslationZ, RotationX     = 0x008, RotationY     = 0x010, RotationZ     = 0x020, Rotation      = RotationX | RotationY | RotationZ, ScaleX        = 0x040, ScaleY        = 0x080, ScaleZ        = 0x100, Scale         = ScaleX | ScaleY | ScaleZ, AllTransform  = Translation | Rotation | Scale, Weight        = 0x200, All           = Translation | Rotation | Scale | Weight,
- L437 _public prototype_ `bool GetCustomUsedChannels(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | TransformAnimationTrack")` — Get which channels of this animation should be used. This is a bitmask. See SetCustomUsedChannels for description of bitmask
- L440 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomUsedChannelsKey = UE::Interchange::FAttributeKey(TEXT("Used`

#### class `UInterchangeSkeletalAnimationTrackNode`  
`class UInterchangeSkeletalAnimationTrackNode : public UInterchangeAnimationTrackBaseNode`  
_L447-592_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeAnimationTrackBaseNode`
- desc: Class to hold onto the relationships between a set of animation tracks and the bones, morph targets of a skeleton.
- L452 _public prototype_ `UInterchangeSkeletalAnimationTrackNode();`
- L457 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SlotMaterialDependencies on load.
- L471 _public function_ `static FStringView StaticAssetTypeName()`
- L479 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L489 _public prototype_ `bool GetCustomSkeletonNodeUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Get the unique ID of the skeleton factory node. Return false if the attribute is not set.
- L493 _public prototype_ `bool SetCustomSkeletonNodeUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Set the unique ID of the skeleton factory node. Return false if the attribute could not be set.
- L499 _public prototype_ `bool SetCustomAnimationSampleRate(const double& SampleRate);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Set the animation sample rate. Return false if the attribute could not be set.
- L505 _public prototype_ `bool GetCustomAnimationSampleRate(double& SampleRate) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Get the animation sample rate. Return false if the attribute is not set.
- L511 _public prototype_ `bool SetCustomAnimationStartTime(const double& StartTime);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Set the animation start time. Return false if the attribute could not be set.
- L517 _public prototype_ `bool GetCustomAnimationStartTime(double& StartTime) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Get the animation start time. Return false if the attribute is not set.
- L523 _public prototype_ `bool SetCustomAnimationStopTime(const double& StopTime);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Set the animation stop time. Return false if the attribute could not be set.
- L529 _public prototype_ `bool GetCustomAnimationStopTime(double& StopTime) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Get the animation stop time. Return false if the attribute is not set.
- L537 _public prototype_ `bool SetCustomSourceTimelineAnimationStartTime(const double& StartTime);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Set the source timeline animation start time. Return false if the attribute could not be set. Note: This represent the DCC setup of the time for the animation. Optional: if not set CustomAnimationStartTime will be used
- L545 _public prototype_ `bool GetCustomSourceTimelineAnimationStartTime(double& StartTime) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Get the source timeline animation start time. Return false if the attribute is not set. Note: This represent the DCC setup of the time for the animation. Optional: if not set CustomAnimationStartTime will be used
- L553 _public prototype_ `bool SetCustomSourceTimelineAnimationStopTime(const double& StopTime);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Set the source timeline animation stop time. Return false if the attribute could not be set. Note: This represent the DCC setup of the time for the animation. Optional: if not set CustomAnimationStopTime will be used
- L561 _public prototype_ `bool GetCustomSourceTimelineAnimationStopTime(double& StopTime) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")` — Get the source timeline animation stop time. Return false if the attribute is not set. Note: This represent the DCC setup of the time for the animation. Optional: if not set CustomAnimationStopTime will be used
- L565 _public prototype_ `void GetSceneNodeAnimationPayloadKeys(TMap<FString, FString>& OutSceneNodeAnimationPayloadKeyUids, TMap<FString, uint8>& OutSceneNodeAnimationPayloadKeyTypes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L568 _public prototype_ `bool SetAnimationPayloadKeyForSceneNodeUid(const FString& SceneNodeUid, const FString& InUniqueId, const EInterchangeAnimationPayLoadType& InType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L571 _public prototype_ `void GetMorphTargetNodeAnimationPayloadKeys(TMap<FString, FString>& OutMorphTargetNodeAnimationPayloadKeyUids, TMap<FString, uint8>& OutMorphTargetNodeAnimationPayloadKeyTypes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L574 _public prototype_ `bool SetAnimationPayloadKeyForMorphTargetNodeUid(const FString& MorphTargetNodeUid, const FString& InUniqueId, const EInterchangeAnimationPayLoadType& InType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L577 _public prototype_ `bool IsNodeAnimatedWithBakedCurve(const FString& SceneNodeUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L580 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSkeletonNodeUidKey = UE::Interchange::FAttributeKey(TEXT("Skel`
- L581 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAnimationSampleRateKey = UE::Interchange::FAttributeKey(TEXT("Anim`
- L582 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAnimationStartTimeKey = UE::Interchange::FAttributeKey(TEXT("Anim`
- L583 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAnimationStopTimeKey = UE::Interchange::FAttributeKey(TEXT("Anim`
- L584 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSourceTimelineAnimationStartTimeKey = UE::Interchange::FAttributeKey(TEXT("Sour`
- L585 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSourceTimelineAnimationStopTimeKey = UE::Interchange::FAttributeKey(TEXT("Sour`
- L587 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SceneNodeAnimationPayloadKeyUidMap;`
- L588 _private member_ `UE::Interchange::TMapAttributeHelper<FString, uint8> SceneNodeAnimationPayloadKeyTypeMap;`
- L590 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> MorphTargetPayloadKeyUidMap;`
- L591 _private member_ `UE::Interchange::TMapAttributeHelper<FString, uint8> MorphTargetPayloadKeyTypeMap;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGENODES_API`
- L58 _function_ `friend uint32 GetTypeHash(const FInterchangeAnimationPayLoadKey& InterchangeAnimationPayLoadKey)`
- L65 _namespace_ `namespace UE`
- L67 _namespace_ `namespace Interchange` (scope `UE`)
- L78 _namespace_ `namespace Animation` (scope `UE::Interchange`)
- L80 _prototype_ `FFrameRate ConvertSampleRateToFrameRate(double SampleRate);` (scope `UE::Interchange::Animation`)

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeAudioSoundWaveNode.h` (Public)


#### struct `UE::Interchange::FSoundWaveNodeStaticData`  
`struct FSoundWaveNodeStaticData : FBaseNodeStaticData`  
_L15-18_
- inherits: `FBaseNodeStaticData`
- L17 _public prototype_ `static const FAttributeKey& PayloadSourceFileKey();`

#### class `UInterchangeAudioSoundWaveNode`  
`class UInterchangeAudioSoundWaveNode : public UInterchangeBaseNode`  
_L22-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L27 _public prototype_ `static UInterchangeAudioSoundWaveNode* Create(UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeName);`
- L29 _public function_ `virtual FString GetTypeName() const override`
- L34 _public function_ `static FString MakeNodeUid(const FStringView NodeName)`
- L39 _public prototype_ `const TOptional<FString> GetPayloadKey() const;`
- L41 _public prototype_ `void SetPayloadKey(const FString& PayloadKey);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeCameraNode.h` (Public)


#### enum `EInterchangeAutoExposureMethod`  
`enum class EInterchangeAutoExposureMethod : uint8`  
_L12-24_
- reflection: `UENUM(BlueprintType)`
- desc: Mirrors EAutoExposureMethod from Scene.h
- L15 _public enumerator_ `Histogram UMETA(DisplayName = "Auto Exposure Histogram")` — requires compute shader to construct 64 bin histogram
- L18 _public enumerator_ `Basic UMETA(DisplayName = "Auto Exposure Basic")` — faster method that computes single value by downsampling
- L21 _public enumerator_ `Manual UMETA(DisplayName = "Manual")` — Uses camera settings.
- L23 _public enumerator_ `MAX`

#### class `UInterchangeBaseCameraNode`  
`class UInterchangeBaseCameraNode : public UInterchangeBaseNode`  
_L27-111_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- L33 _public function_ `bool GetCustomNearClipPlane(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L39 _public function_ `bool SetCustomNearClipPlane(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L45 _public function_ `bool GetCustomAutoExposureMethod(EInterchangeAutoExposureMethod& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L51 _public function_ `bool SetCustomAutoExposureMethod(const EInterchangeAutoExposureMethod& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L57 _public function_ `bool GetCustomExposureCompensation(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L63 _public function_ `bool SetCustomExposureCompensation(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L69 _public function_ `bool GetCustomExposureFstop(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L75 _public function_ `bool SetCustomExposureFstop(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L81 _public function_ `bool GetCustomExposureISO(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L87 _public function_ `bool SetCustomExposureISO(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L93 _public function_ `bool GetCustomExposureShutterSpeed(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L99 _public function_ `bool SetCustomExposureShutterSpeed(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L105 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NearClipPlane);`
- L106 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AutoExposureMethod);`
- L107 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureCompensation);`
- L108 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureFstop);`
- L109 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureISO);`
- L110 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureShutterSpeed);`

#### class `UInterchangePhysicalCameraNode`  
`class UInterchangePhysicalCameraNode : public UInterchangeBaseCameraNode`  
_L114-239_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseCameraNode`
- L119 _public function_ `static FStringView StaticAssetTypeName()`
- L127 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L135 _public function_ `bool GetCustomFocalLength(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L141 _public function_ `bool SetCustomFocalLength(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L147 _public function_ `bool GetCustomFocusDistance(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L153 _public function_ `bool SetCustomFocusDistance(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L159 _public function_ `bool GetCustomSensorWidth(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L165 _public function_ `bool SetCustomSensorWidth(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L171 _public function_ `bool GetCustomSensorHeight(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L177 _public function_ `bool SetCustomSensorHeight(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L183 _public function_ `bool GetCustomSensorHorizontalOffset(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L189 _public function_ `bool SetCustomSensorHorizontalOffset(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L195 _public function_ `bool GetCustomSensorVerticalOffset(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L201 _public function_ `bool SetCustomSensorVerticalOffset(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L207 _public function_ `bool GetCustomEnableDepthOfField(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L213 _public function_ `bool SetCustomEnableDepthOfField(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L219 _public function_ `bool GetCustomDepthOfFieldFstop(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L225 _public function_ `bool SetCustomDepthOfFieldFstop(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L231 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FocalLength);`
- L232 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FocusDistance);`
- L233 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorWidth);`
- L234 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorHeight);`
- L235 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorHorizontalOffset);`
- L236 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorVerticalOffset);`
- L237 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(EnableDepthOfField);`
- L238 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(DepthOfFieldFstop);`

#### enum `EInterchangeCameraProjectionType`  
`enum class EInterchangeCameraProjectionType : uint8`  
_L242-246_
- reflection: `UENUM(BlueprintType)`
- L244 _public enumerator_ `Perspective`
- L245 _public enumerator_ `Orthographic`

#### class `UInterchangeStandardCameraNode`  
`class UInterchangeStandardCameraNode : public UInterchangeBaseCameraNode`  
_L250-333_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseCameraNode`
- desc: Primarily used for Ortho Camera
- L255 _public function_ `static FStringView StaticAssetTypeName()`
- L263 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L271 _public function_ `bool GetCustomProjectionMode(EInterchangeCameraProjectionType& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L276 _public function_ `bool SetCustomProjectionMode(const EInterchangeCameraProjectionType& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L282 _public function_ `bool GetCustomWidth(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L287 _public function_ `bool SetCustomWidth(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L293 _public function_ `bool GetCustomFarClipPlane(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L298 _public function_ `bool SetCustomFarClipPlane(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L304 _public function_ `bool GetCustomAspectRatio(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L309 _public function_ `bool SetCustomAspectRatio(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L316 _public function_ `bool GetCustomFieldOfView(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")` — Field of View in Degrees.
- L322 _public function_ `bool SetCustomFieldOfView(const float& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")` — Field of View in Degrees.
- L328 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ProjectionMode);`
- L329 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Width);`
- L330 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FarClipPlane);`
- L331 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AspectRatio);`
- L332 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FieldOfView);`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeDecalMaterialNode.h` (Public)


#### class `UInterchangeDecalMaterialNode`  
`class UInterchangeDecalMaterialNode : public UInterchangeShaderNode`  
_L14-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeShaderNode`
- L20 _public function_ `bool GetCustomDiffuseTexturePath(FString& AttributeValue) const`
- L25 _public function_ `bool SetCustomDiffuseTexturePath(FString AttributeValue)`
- L30 _public function_ `bool GetCustomNormalTexturePath(FString& AttributeValue) const`
- L35 _public function_ `bool SetCustomNormalTexturePath(FString AttributeValue)`
- L41 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDiffuseTexturePathKey = UE::Interchange::FAttributeKey(TEXT("Diff`
- L42 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNormalTexturePathKey= UE::Interchange::FAttributeKey(TEXT("Norm`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeDecalNode.h` (Public)


#### class `UInterchangeDecalNode`  
`class UInterchangeDecalNode : public UInterchangeBaseNode`  
_L11-56_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- L17 _public function_ `bool GetCustomSortOrder(int32& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L23 _public function_ `bool SetCustomSortOrder(const int32& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L29 _public function_ `bool GetCustomDecalSize(FVector& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L35 _public function_ `bool SetCustomDecalSize(const FVector& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L41 _public function_ `bool GetCustomDecalMaterialPathName(FString& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L47 _public function_ `bool SetCustomDecalMaterialPathName(const FString& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L53 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSortOrderKey = UE::Interchange::FAttributeKey(TEXT("Sort`
- L54 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDecalSizeKey = UE::Interchange::FAttributeKey(TEXT("Deca`
- L55 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDecalMaterialPathNameKey = UE::Interchange::FAttributeKey(TEXT("Deca`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeGroomBindingNode.h` (Public)


#### class `UInterchangeGroomBindingNode`  
`class UInterchangeGroomBindingNode : public UInterchangeBaseNode`  
_L12-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L17 _public prototype_ `virtual FString GetTypeName() const override;`
- L21 _public prototype_ `bool GetGroomDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Binding")` — Get the groom asset to build the binding from
- L25 _public prototype_ `bool SetGroomDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Binding")` — Set the groom asset to build the binding from
- L29 _public prototype_ `bool GetTargetMeshDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Binding")` — Get the target mesh to build the binding from
- L33 _public prototype_ `bool SetTargetMeshDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Binding")` — Set the target mesh to build the binding from
- L36 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomUid);`
- L37 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(TargetMeshUid);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeGroomComponentNode.h` (Public)


#### class `UInterchangeGroomComponentNode`  
`class UInterchangeGroomComponentNode : public UInterchangeSceneComponentNode`  
_L13-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeSceneComponentNode`
- L18 _public prototype_ `UInterchangeGroomComponentNode();`
- L20 _public prototype_ `virtual FString GetTypeName() const override;`
- L24 _public prototype_ `bool GetGroomDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Get the groom asset to apply on the groom component
- L28 _public prototype_ `bool SetGroomDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Set the groom asset to apply on the groom component
- L32 _public prototype_ `bool GetGroomBindingDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Get the groom binding asset to apply on the groom component
- L36 _public prototype_ `bool SetGroomBindingDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Set the groom binding asset to apply on the groom component
- L39 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomUid);`
- L40 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomBindingUid);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeGroomNode.h` (Public)


#### struct `UE::Interchange::FGroomNodeStaticData`  
`struct FGroomNodeStaticData : public FBaseNodeStaticData`  
_L13-17_
- inherits: `FBaseNodeStaticData`
- L15 _public prototype_ `static const FAttributeKey& PayloadKey();`
- L16 _public prototype_ `static const FAttributeKey& PayloadTypeKey();`

#### enum `EInterchangeGroomPayLoadType`  
`enum class EInterchangeGroomPayLoadType : uint8`  
_L21-25_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `STATIC UMETA(DisplayName = "Groom Asset")`
- L24 _public enumerator_ `ANIMATED UMETA(DisplayName = "Groom Cache")`

#### enum `EInterchangeGroomCacheAttributes`  
`enum class EInterchangeGroomCacheAttributes : uint8`  
_L28-40_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `None = 0`
- L31 _public enumerator_ `Position = 1`
- L32 _public enumerator_ `Width = 1 << 1`
- L33 _public enumerator_ `Color = 1 << 2`
- L36 _public enumerator_ `PositionWidth = (Position | Width) UMETA(DisplayName = "Position & Width")` — For display names
- L37 _public enumerator_ `PositionColor = (Position | Color) UMETA(DisplayName = "Position & Color")`
- L38 _public enumerator_ `WidthColor = (Width | Color) UMETA(DisplayName = "Width & Color")`
- L39 _public enumerator_ `PositionWidthColor = (Position | Width | Color) UMETA(DisplayName = "Position, Width, Color")`

#### struct `FInterchangeGroomPayloadKey`  
`struct FInterchangeGroomPayloadKey`  
_L43-82_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `FString UniqueId = "";` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Groom")`
- L53 _public member_ `EInterchangeGroomPayLoadType Type = EInterchangeGroomPayLoadType::STATIC;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Groom")`
- L56 _public member_ `int32 FrameNumber = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Groom Cache")`
- L58 _public function_ `FInterchangeGroomPayloadKey()`
- L60 _public function_ `FInterchangeGroomPayloadKey(const FString& InUniqueId, const EInterchangeGroomPayLoadType& InType) : UniqueId(InUniqueId) , Type(InType)`
- L66 _public function_ `FInterchangeGroomPayloadKey(const FString& InUniqueId, int32 InFrameNumber) : UniqueId(InUniqueId) , Type(EInterchangeGroomPayLoadType::ANIMATED) , FrameNumber(InFrameNumber)`
- L73 _public function_ `bool operator==(const FInterchangeGroomPayloadKey& Other) const`

#### class `UInterchangeGroomNode`  
`class UInterchangeGroomNode : public UInterchangeBaseNode`  
_L85-143_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L90 _public prototype_ `virtual FString GetTypeName() const override;`
- L92 _public prototype_ `const TOptional<FInterchangeGroomPayloadKey> GetPayloadKey() const;`
- L95 _public prototype_ `void SetPayloadKey(const FString& PayloadKey, EInterchangeGroomPayLoadType PayLoadType = EInterchangeGroomPayLoadType::STATIC);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom")`
- L99 _public prototype_ `bool GetCustomStartFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Get the start frame index of the animation
- L103 _public prototype_ `bool SetCustomStartFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Set the start frame index of the animation
- L107 _public prototype_ `bool GetCustomEndFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Get the end frame index of the animation
- L111 _public prototype_ `bool SetCustomEndFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Set the end frame index of the animation
- L115 _public prototype_ `bool GetCustomNumFrames(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Get the number of frames in the animation
- L119 _public prototype_ `bool SetCustomNumFrames(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Set the number of frames in the animation
- L123 _public prototype_ `bool GetCustomFrameRate(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Get the animation's frame rate
- L127 _public prototype_ `bool SetCustomFrameRate(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Set the animation's frame rate
- L131 _public prototype_ `bool GetCustomGroomCacheAttributes(EInterchangeGroomCacheAttributes& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Get the groom attributes that are animated
- L135 _public prototype_ `bool SetCustomGroomCacheAttributes(const EInterchangeGroomCacheAttributes& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")` — Set the groom attributes that are animated
- L138 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NumFrames);`
- L139 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(StartFrame);`
- L140 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(EndFrame);`
- L141 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FrameRate);`
- L142 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomCacheAttributes);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L78 _function_ `friend uint32 GetTypeHash(const FInterchangeGroomPayloadKey& InterchangeGroomPayLoadKey)`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeJointNode.h` (Public)


#### class `UInterchangeJointNode`  
`class UInterchangeJointNode : public UInterchangeSceneNode`  
_L15-101_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeSceneNode`
- L31 _public prototype_ `UInterchangeJointNode();`
- L33 _public prototype_ `virtual FName GetIconName() const override;`
- L36 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L41 _public prototype_ `bool GetBindPoseLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Get the local transform of the bind pose scene node.
- L45 _public prototype_ `bool SetBindPoseLocalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Set the local transform of the bind pose scene node.
- L49 _public prototype_ `bool GetBindPoseGlobalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Get the global transform of the bind pose scene node. This value is computed from the local transforms of all parent bind poses.
- L52 _public prototype_ `void SetMeshUIDToGlobalBindPoseReferenceMap(const TMap<FString, FMatrix>& InMeshToGlobalBindPoseReferences);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")`
- L56 _public prototype_ `bool GetGlobalBindPoseReferenceFromMeshUID(const FString& MeshUID, FMatrix& GlobalBindPoseReference) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Get the Global Bind Pose Reference for given MeshUID.
- L60 _public prototype_ `bool SetHasInvalidBindPose(const bool& bHasInvalidBindPose);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Sets if Joint has invalid Bind Pose. Automatic T0 usage will be configured in case if the Skeleton contains at least 1 Joint with invalid BindPose.
- L64 _public prototype_ `bool GetHasInvalidBindPose(bool & bHasInvalidBindPose) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Gets if the joint has invalid BindPose (if the setter was used, otherwise returns with false and T0 evaluation presumes bHasInvalidBindPose == false).
- L68 _public prototype_ `bool GetTimeZeroLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Get the local transform of the time-zero scene node.
- L72 _public prototype_ `bool SetTimeZeroLocalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Set the local transform of the time-zero scene node.
- L76 _public prototype_ `bool GetTimeZeroGlobalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Get the global transform of the time-zero scene node. This value is computed from the local transforms of all parent time-zero scene nodes.
- L80 _public prototype_ `bool SetGlobalMatrixForT0Rebinding(const FMatrix& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Sets the Global Transformation Matrix used for T0 rebinding.
- L84 _public prototype_ `bool GetGlobalMatrixForT0Rebinding(FMatrix& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Gets the Global Transformation Matrix used for T0 rebinding.
- L88 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(BindPoseLocalTransform);` — Scene node Local bind pose transforms
- L91 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasInvalidBindPose);` — Tracks if Joint node Has invalid Bind Pose.
- L94 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(TimeZeroLocalTransform);` — Scene node local transforms at time zero. This attribute is important for rigid mesh import or if the translator did not fill the bind pose.
- L97 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GlobalMatrixForT0Rebinding);` — Global Transform Matrix specifically used for T0 re-binding.
- L100 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FMatrix> MeshToGlobalBindPoseReferences;` — BindPose References per Mesh for a JointNode.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeLightNode.h` (Public)


#### enum `EInterchangeLightUnits`  
`enum class EInterchangeLightUnits : uint8`  
_L14-21_
- reflection: `UENUM()`
- desc: This enum is used as a placeholder for ELightUnits. Because InterchangeWorker is not compiled against Engine, the LightFactoryNode is not affected.
- L16 _public enumerator_ `Unitless`
- L17 _public enumerator_ `Candelas`
- L18 _public enumerator_ `Lumens`
- L19 _public enumerator_ `EV`
- L20 _public enumerator_ `Nits`

#### enum `EInterchangeSkyLightSourceType`  
`enum class EInterchangeSkyLightSourceType : uint8`  
_L25-29_
- reflection: `UENUM()`
- desc: Mirrors ESkyLightSourceType
- L27 _public enumerator_ `CapturedScene`
- L28 _public enumerator_ `SpecifiedCubemap`

#### class `UInterchangeBaseLightNode`  
`class UInterchangeBaseLightNode : public UInterchangeBaseNode`  
_L32-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L37 _public prototype_ `static FStringView StaticAssetTypeName();`
- L42 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L45 _public prototype_ `bool GetCustomLightColor(FLinearColor& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L48 _public prototype_ `bool SetCustomLightColor(const FLinearColor& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L51 _public prototype_ `bool GetCustomIntensity(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L54 _public prototype_ `bool SetCustomIntensity(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L57 _public prototype_ `bool GetCustomTemperature(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L60 _public prototype_ `bool SetCustomTemperature(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L63 _public prototype_ `bool GetCustomUseTemperature(bool & AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`
- L66 _public prototype_ `bool SetCustomUseTemperature(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | BaseLight")`

#### class `UInterchangeLightNode`  
`class UInterchangeLightNode : public UInterchangeBaseLightNode`  
_L77-130_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseLightNode`
- L83 _public prototype_ `virtual FString GetTypeName() const override;`
- L86 _public prototype_ `bool GetCustomIntensityUnits(EInterchangeLightUnits& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L89 _public prototype_ `bool SetCustomIntensityUnits(const EInterchangeLightUnits & AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L92 _public prototype_ `bool GetCustomAttenuationRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L95 _public prototype_ `bool SetCustomAttenuationRadius(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L98 _public prototype_ `bool GetCustomIESTexture(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L101 _public prototype_ `bool SetCustomIESTexture(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L104 _public prototype_ `bool GetCustomUseIESBrightness(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L107 _public prototype_ `bool SetCustomUseIESBrightness(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L110 _public prototype_ `bool GetCustomIESBrightnessScale(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L113 _public prototype_ `bool SetCustomIESBrightnessScale(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L116 _public prototype_ `bool GetCustomRotation(FRotator& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`
- L119 _public prototype_ `bool SetCustomRotation(const FRotator& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Light")`

#### class `UInterchangePointLightNode`  
`class UInterchangePointLightNode : public UInterchangeLightNode`  
_L133-163_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeLightNode`
- L139 _public prototype_ `virtual FString GetTypeName() const override;`
- L142 _public prototype_ `bool GetCustomUseInverseSquaredFalloff(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLight")`
- L145 _public prototype_ `bool SetCustomUseInverseSquaredFalloff(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLight")`
- L148 _public prototype_ `bool GetCustomLightFalloffExponent(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLight")`
- L151 _public prototype_ `bool SetCustomLightFalloffExponent(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLight")`
- L154 _public prototype_ `bool GetCustomSourceRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLight")`
- L157 _public prototype_ `bool SetCustomSourceRadius(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLight")`

#### class `UInterchangeSpotLightNode`  
`class UInterchangeSpotLightNode : public UInterchangePointLightNode`  
_L166-190_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangePointLightNode`
- L172 _public prototype_ `virtual FString GetTypeName() const override;`
- L175 _public prototype_ `bool GetCustomInnerConeAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLight")`
- L178 _public prototype_ `bool SetCustomInnerConeAngle(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLight")`
- L181 _public prototype_ `bool GetCustomOuterConeAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLight")`
- L184 _public prototype_ `bool SetCustomOuterConeAngle(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLight")`

#### class `UInterchangeRectLightNode`  
`class UInterchangeRectLightNode : public UInterchangeLightNode`  
_L193-216_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeLightNode`
- L199 _public prototype_ `virtual FString GetTypeName() const override;`
- L202 _public prototype_ `bool GetCustomSourceWidth(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLight")`
- L205 _public prototype_ `bool SetCustomSourceWidth(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLight")`
- L208 _public prototype_ `bool GetCustomSourceHeight(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLight")`
- L211 _public prototype_ `bool SetCustomSourceHeight(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLight")`

#### class `UInterchangeDirectionalLightNode`  
`class UInterchangeDirectionalLightNode : public UInterchangeBaseLightNode`  
_L219-235_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseLightNode`
- L225 _public prototype_ `virtual FString GetTypeName() const override;`
- L228 _public prototype_ `bool GetCustomLightSourceAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | DirectionalLight")`
- L231 _public prototype_ `bool SetCustomLightSourceAngle(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | DirectionalLight")`

#### class `UInterchangeSkyLightNode`  
`class UInterchangeSkyLightNode : public UInterchangeBaseLightNode`  
_L238-262_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseLightNode`
- L244 _public prototype_ `virtual FString GetTypeName() const override;`
- L247 _public prototype_ `bool GetCustomCubemapDependency(FString& TextureCubeNodeUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLight")`
- L250 _public prototype_ `bool SetCustomCubemapDependency(FString TextureCubeNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLight")`
- L253 _public prototype_ `bool GetCustomSourceType(EInterchangeSkyLightSourceType& SourceType) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLight")`
- L256 _public prototype_ `bool SetCustomSourceType(EInterchangeSkyLightSourceType SourceType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLight")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMaterialDefinitions.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace Materials` (scope `UE::Interchange`)
- L13 _namespace_ `namespace Standard` (scope `UE::Interchange::Materials`)
- L15 _namespace_ `namespace Nodes` (scope `UE::Interchange::Materials::Standard`)
- L17 _namespace_ `namespace Add` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L19 _variable_ `const FName Name = TEXT("Add` (scope `UE::Interchange::Materials::Standard::Nodes::Add`)
- L21 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Add`)
- L23 _variable_ `const FName A = TEXT("A")` (scope `UE::Interchange::Materials::Standard::Nodes::Add::Inputs`)
- L24 _variable_ `const FName B = TEXT("B")` (scope `UE::Interchange::Materials::Standard::Nodes::Add::Inputs`)
- L28 _namespace_ `namespace FlattenNormal` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L30 _variable_ `const FName Name = TEXT("Fla` (scope `UE::Interchange::Materials::Standard::Nodes::FlattenNormal`)
- L32 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::FlattenNormal`)
- L34 _variable_ `const FName Normal = TEXT("Nor` (scope `UE::Interchange::Materials::Standard::Nodes::FlattenNormal::Inputs`)
- L35 _variable_ `const FName Flatness = TEXT("Fla` (scope `UE::Interchange::Materials::Standard::Nodes::FlattenNormal::Inputs`)
- L39 _namespace_ `namespace Lerp` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L41 _variable_ `const FName Name = TEXT("Ler` (scope `UE::Interchange::Materials::Standard::Nodes::Lerp`)
- L43 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Lerp`)
- L45 _variable_ `const FName A = TEXT("A")` (scope `UE::Interchange::Materials::Standard::Nodes::Lerp::Inputs`) — Type: linear color
- L46 _variable_ `const FName B = TEXT("B")` (scope `UE::Interchange::Materials::Standard::Nodes::Lerp::Inputs`) — Type: linear color
- L47 _variable_ `const FName Factor = TEXT("Fac` (scope `UE::Interchange::Materials::Standard::Nodes::Lerp::Inputs`) — Type: float
- L51 _namespace_ `namespace Luminance` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L53 _variable_ `const FName Name = TEXT("Lum` (scope `UE::Interchange::Materials::Standard::Nodes::Luminance`)
- L55 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Luminance`)
- L57 _variable_ `const FName Input = TEXT("Inp` (scope `UE::Interchange::Materials::Standard::Nodes::Luminance::Inputs`)
- L60 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Luminance`)
- L62 _variable_ `const FName LuminanceFactors = TEXT("Lum` (scope `UE::Interchange::Materials::Standard::Nodes::Luminance::Attributes`)
- L66 _namespace_ `namespace Mask` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L68 _variable_ `const FName Name = TEXT("Com` (scope `UE::Interchange::Materials::Standard::Nodes::Mask`)
- L70 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Mask`)
- L72 _variable_ `const FName R = TEXT("R")` (scope `UE::Interchange::Materials::Standard::Nodes::Mask::Attributes`)
- L73 _variable_ `const FName G = TEXT("G")` (scope `UE::Interchange::Materials::Standard::Nodes::Mask::Attributes`)
- L74 _variable_ `const FName B = TEXT("B")` (scope `UE::Interchange::Materials::Standard::Nodes::Mask::Attributes`)
- L75 _variable_ `const FName A = TEXT("A")` (scope `UE::Interchange::Materials::Standard::Nodes::Mask::Attributes`)
- L78 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Mask`)
- L80 _variable_ `const FName Input = TEXT("Inp` (scope `UE::Interchange::Materials::Standard::Nodes::Mask::Inputs`)
- L84 _namespace_ `namespace Multiply` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L86 _variable_ `const FName Name = TEXT("Mul` (scope `UE::Interchange::Materials::Standard::Nodes::Multiply`)
- L88 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Multiply`)
- L90 _variable_ `const FName A = TEXT("A")` (scope `UE::Interchange::Materials::Standard::Nodes::Multiply::Inputs`)
- L91 _variable_ `const FName B = TEXT("B")` (scope `UE::Interchange::Materials::Standard::Nodes::Multiply::Inputs`)
- L95 _namespace_ `namespace MakeFloat3` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L97 _variable_ `const FName Name = TEXT("Mak` (scope `UE::Interchange::Materials::Standard::Nodes::MakeFloat3`)
- L98 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::MakeFloat3`)
- L100 _variable_ `const FName X = TEXT("X")` (scope `UE::Interchange::Materials::Standard::Nodes::MakeFloat3::Inputs`)
- L101 _variable_ `const FName Y = TEXT("Y")` (scope `UE::Interchange::Materials::Standard::Nodes::MakeFloat3::Inputs`)
- L102 _variable_ `const FName Z = TEXT("Z")` (scope `UE::Interchange::Materials::Standard::Nodes::MakeFloat3::Inputs`)
- L106 _namespace_ `namespace Noise` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L108 _variable_ `const FName Name = TEXT("Noi` (scope `UE::Interchange::Materials::Standard::Nodes::Noise`)
- L110 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Noise`)
- L112 _variable_ `const FName Position = TEXT("Pos` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Inputs`)
- L113 _variable_ `const FName FilterWidth = TEXT("Fil` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Inputs`)
- L116 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Noise`)
- L118 _variable_ `const FName Scale = TEXT("Sca` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L119 _variable_ `const FName Quality = TEXT("Qua` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L120 _variable_ `const FName Function = TEXT("Noi` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L121 _variable_ `const FName Turbulence = TEXT("bTu` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L122 _variable_ `const FName Levels = TEXT("Lev` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L123 _variable_ `const FName OutputMin = TEXT("Out` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L124 _variable_ `const FName OutputMax = TEXT("Out` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L125 _variable_ `const FName LevelScale = TEXT("Lev` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L126 _variable_ `const FName Tiling = TEXT("bTi` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L127 _variable_ `const FName RepeatSize = TEXT("Rep` (scope `UE::Interchange::Materials::Standard::Nodes::Noise::Attributes`)
- L131 _namespace_ `namespace NormalFromHeightMap` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L133 _variable_ `const FName Name = TEXT("Nor` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap`)
- L135 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap`)
- L137 _variable_ `const FName HeightMap = TEXT("Hei` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap::Inputs`) — Type: FString (unique id of a texture node)
- L138 _variable_ `const FName Intensity = TEXT("Nor` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap::Inputs`) — Type: float
- L139 _variable_ `const FName Offset = TEXT("Hei` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap::Inputs`) — Type: float
- L140 _variable_ `const FName Coordinates = TEXT("Coo` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap::Inputs`) — Type: vec2
- L141 _variable_ `const FName Channel = TEXT("Hei` (scope `UE::Interchange::Materials::Standard::Nodes::NormalFromHeightMap::Inputs`) — Type: vec4
- L145 _namespace_ `namespace OneMinus` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L147 _variable_ `const FName Name = TEXT("One` (scope `UE::Interchange::Materials::Standard::Nodes::OneMinus`)
- L149 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::OneMinus`)
- L151 _variable_ `const FName Input = TEXT("Inp` (scope `UE::Interchange::Materials::Standard::Nodes::OneMinus::Inputs`)
- L155 _namespace_ `namespace Rotator` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L157 _variable_ `const FName Name = TEXT("Rot` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator`)
- L159 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator`)
- L161 _variable_ `const FName CenterX = TEXT("Cen` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator::Attributes`)
- L162 _variable_ `const FName CenterY = TEXT("Cen` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator::Attributes`)
- L163 _variable_ `const FName Speed = TEXT("Spe` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator::Attributes`)
- L166 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator`)
- L168 _variable_ `const FName Coordinate = TEXT("Coo` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator::Inputs`)
- L169 _variable_ `const FName Time = TEXT("Tim` (scope `UE::Interchange::Materials::Standard::Nodes::Rotator::Inputs`)
- L173 _namespace_ `namespace RotateAboutAxis` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L175 _variable_ `const FName Name = TEXT("Rot` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis`)
- L177 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis`)
- L179 _variable_ `const FName Period = TEXT("Per` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis::Attributes`)
- L182 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis`)
- L184 _variable_ `const FName NormalizedRotationAxis = TEXT("Nor` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis::Inputs`)
- L185 _variable_ `const FName RotationAngle = TEXT("Rot` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis::Inputs`)
- L186 _variable_ `const FName PivotPoint = TEXT("Piv` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis::Inputs`)
- L187 _variable_ `const FName Position = TEXT("Pos` (scope `UE::Interchange::Materials::Standard::Nodes::RotateAboutAxis::Inputs`)
- L191 _namespace_ `namespace Switch` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L193 _variable_ `const FName Name = TEXT("Swi` (scope `UE::Interchange::Materials::Standard::Nodes::Switch`)
- L195 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Switch`)
- L197 _variable_ `const FName Value = TEXT("Swi` (scope `UE::Interchange::Materials::Standard::Nodes::Switch::Inputs`)
- L198 _variable_ `const FName Default = TEXT("Swi` (scope `UE::Interchange::Materials::Standard::Nodes::Switch::Inputs`)
- L199 _variable_ `const FName InputName = TEXT("Swi` (scope `UE::Interchange::Materials::Standard::Nodes::Switch::Inputs`) — The caller should concatenate this input with an index to get the InputName in the array of the MaterialExpressionSwitch
- L202 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Switch`)
- L204 _variable_ `const FName InputCount = TEXT("Swi` (scope `UE::Interchange::Materials::Standard::Nodes::Switch::Attributes`) — Used to know the number of inputs in the Switch
- L208 _namespace_ `namespace TextureCoordinate` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L210 _variable_ `const FName Name = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate`)
- L212 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate`)
- L214 _variable_ `const FName Index = TEXT("Ind` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: int
- L215 _variable_ `const FName UTiling = TEXT("UTi` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: float
- L216 _variable_ `const FName VTiling = TEXT("VTi` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: float
- L217 _variable_ `const FName Offset = TEXT("Off` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: vec2
- L218 _variable_ `const FName Scale = TEXT("Sca` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: vec2
- L219 _variable_ `const FName Rotate = TEXT("Rot` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: float, Range: 0-1
- L220 _variable_ `const FName RotationCenter = TEXT("Rot` (scope `UE::Interchange::Materials::Standard::Nodes::TextureCoordinate::Inputs`) — Type: vec2
- L224 _namespace_ `namespace TextureObject` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L226 _variable_ `const FName Name = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureObject`)
- L228 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::TextureObject`)
- L230 _variable_ `const FName Texture = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureObject::Inputs`) — Type: FString (unique id of a texture node)
- L234 _namespace_ `namespace TextureProperty` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L236 _variable_ `const FName Name = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureProperty`)
- L238 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::TextureProperty`)
- L240 _variable_ `const FName Texture = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureProperty::Inputs`) — Type: FString (unique id of a texture node)
- L243 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::TextureProperty`)
- L245 _variable_ `const FName Property = TEXT("Pro` (scope `UE::Interchange::Materials::Standard::Nodes::TextureProperty::Attributes`) — Type: enum
- L249 _namespace_ `namespace TextureSample` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L251 _variable_ `const FName Name = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample`)
- L253 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample`)
- L255 _variable_ `const FName Coordinates = TEXT("Coo` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Inputs`) — Type: vec2
- L256 _variable_ `const FName Texture = TEXT("Tex` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Inputs`) — Type: FString (unique id of a texture node)
- L259 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample`)
- L261 _variable_ `const FName RGB = TEXT("RGB` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Outputs`) — Type: linear color
- L262 _variable_ `const FName R = TEXT("R")` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Outputs`) — Type: float
- L263 _variable_ `const FName G = TEXT("G")` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Outputs`) — Type: float
- L264 _variable_ `const FName B = TEXT("B")` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Outputs`) — Type: float
- L265 _variable_ `const FName A = TEXT("A")` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Outputs`) — Type: float
- L266 _variable_ `const FName RGBA = TEXT("RGB` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSample::Outputs`) — Type: linear color
- L270 _namespace_ `namespace TextureSampleBlur` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L274 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSampleBlur`)
- L276 _variable_ `const FName KernelSize = TEXT("Ker` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSampleBlur::Attributes`) — Type: float
- L277 _variable_ `const FName FilterSize = TEXT("Fil` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSampleBlur::Attributes`) — Type: float
- L278 _variable_ `const FName FilterOffset= TEXT("Fil` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSampleBlur::Attributes`) — Type: float
- L279 _variable_ `const FName Filter = TEXT("Fil` (scope `UE::Interchange::Materials::Standard::Nodes::TextureSampleBlur::Attributes`) — Type: int
- L283 _namespace_ `namespace Time` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L285 _variable_ `const FName Name = TEXT("Tim` (scope `UE::Interchange::Materials::Standard::Nodes::Time`)
- L287 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Time`)
- L289 _variable_ `const FName IgnorePause= TEXT("bIg` (scope `UE::Interchange::Materials::Standard::Nodes::Time::Attributes`)
- L290 _variable_ `const FName OverridePeriod = TEXT("bOv` (scope `UE::Interchange::Materials::Standard::Nodes::Time::Attributes`)
- L291 _variable_ `const FName Period = TEXT("Per` (scope `UE::Interchange::Materials::Standard::Nodes::Time::Attributes`)
- L295 _namespace_ `namespace TransformPosition` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L297 _variable_ `const FName Name = TEXT("Tra` (scope `UE::Interchange::Materials::Standard::Nodes::TransformPosition`)
- L299 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::TransformPosition`)
- L301 _variable_ `const FName TransformSourceType = TEXT("Tra` (scope `UE::Interchange::Materials::Standard::Nodes::TransformPosition::Attributes`)
- L302 _variable_ `const FName TransformType = TEXT("Tra` (scope `UE::Interchange::Materials::Standard::Nodes::TransformPosition::Attributes`)
- L305 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::TransformPosition`)
- L307 _variable_ `const FName Input = TEXT("Inp` (scope `UE::Interchange::Materials::Standard::Nodes::TransformPosition::Inputs`)
- L311 _namespace_ `namespace TransformVector` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L313 _variable_ `const FName Name = TEXT("Tra` (scope `UE::Interchange::Materials::Standard::Nodes::TransformVector`)
- L315 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::TransformVector`)
- L317 _variable_ `const FName TransformSourceType = TEXT("Tra` (scope `UE::Interchange::Materials::Standard::Nodes::TransformVector::Attributes`)
- L318 _variable_ `const FName TransformType = TEXT("Tra` (scope `UE::Interchange::Materials::Standard::Nodes::TransformVector::Attributes`)
- L321 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::TransformVector`)
- L323 _variable_ `const FName Input = TEXT("Inp` (scope `UE::Interchange::Materials::Standard::Nodes::TransformVector::Inputs`)
- L327 _namespace_ `namespace Trigonometry` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L329 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::Trigonometry`)
- L331 _variable_ `const FName Input = TEXT("Inp` (scope `UE::Interchange::Materials::Standard::Nodes::Trigonometry::Inputs`)
- L334 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::Trigonometry`)
- L336 _variable_ `const FName Period = TEXT("Per` (scope `UE::Interchange::Materials::Standard::Nodes::Trigonometry::Attributes`)
- L340 _namespace_ `namespace Cosine` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L342 _variable_ `const FName Name = TEXT("Cos` (scope `UE::Interchange::Materials::Standard::Nodes::Cosine`)
- L346 _namespace_ `namespace Sine` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L348 _variable_ `const FName Name = TEXT("Sin` (scope `UE::Interchange::Materials::Standard::Nodes::Sine`)
- L352 _namespace_ `namespace Tangent` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L354 _variable_ `const FName Name = TEXT("Tan` (scope `UE::Interchange::Materials::Standard::Nodes::Tangent`)
- L358 _namespace_ `namespace VectorNoise` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L361 _variable_ `const FName Name = TEXT("Vec` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise`)
- L363 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise`)
- L365 _variable_ `const FName Function = TEXT("Noi` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise::Attributes`)
- L366 _variable_ `const FName Quality = TEXT("Qua` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise::Attributes`)
- L367 _variable_ `const FName Tiling = TEXT("bTi` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise::Attributes`)
- L368 _variable_ `const FName TileSize = TEXT("Til` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise::Attributes`)
- L371 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise`)
- L373 _variable_ `const FName Position = TEXT("Pos` (scope `UE::Interchange::Materials::Standard::Nodes::VectorNoise::Inputs`)
- L377 _namespace_ `namespace VertexColor` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L379 _variable_ `const FName Name = TEXT("Ver` (scope `UE::Interchange::Materials::Standard::Nodes::VertexColor`)
- L382 _namespace_ `namespace ScalarParameter` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L384 _variable_ `const FName Name = TEXT("Sca` (scope `UE::Interchange::Materials::Standard::Nodes::ScalarParameter`)
- L385 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::ScalarParameter`)
- L387 _variable_ `const FName DefaultValue = TEXT("Def` (scope `UE::Interchange::Materials::Standard::Nodes::ScalarParameter::Attributes`)
- L391 _namespace_ `namespace VectorParameter` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L393 _variable_ `const FName Name = TEXT("Vec` (scope `UE::Interchange::Materials::Standard::Nodes::VectorParameter`)
- L394 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::VectorParameter`)
- L396 _variable_ `const FName DefaultValue = TEXT("Def` (scope `UE::Interchange::Materials::Standard::Nodes::VectorParameter::Attributes`)
- L400 _namespace_ `namespace StaticBoolParameter` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L402 _variable_ `const FName Name = TEXT("Sta` (scope `UE::Interchange::Materials::Standard::Nodes::StaticBoolParameter`)
- L403 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::StaticBoolParameter`)
- L405 _variable_ `const FName DefaultValue = TEXT("Def` (scope `UE::Interchange::Materials::Standard::Nodes::StaticBoolParameter::Attributes`)
- L409 _namespace_ `namespace SlabBSDF` (scope `UE::Interchange::Materials::Standard::Nodes`)
- L411 _variable_ `const FName Name = TEXT("Sub` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF`)
- L413 _namespace_ `namespace Attributes` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF`)
- L415 _variable_ `const FName SpecularProfile = TEXT("Spe` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Attributes`)
- L418 _namespace_ `namespace Inputs` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF`)
- L420 _variable_ `const FName DiffuseAlbedo = TEXT("Dif` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L421 _variable_ `const FName F0 = TEXT("F0"` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L422 _variable_ `const FName F90 = TEXT("F90` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L423 _variable_ `const FName Roughness = TEXT("Rou` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L424 _variable_ `const FName Anisotropy = TEXT("Ani` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L425 _variable_ `const FName Normal = TEXT("Nor` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L426 _variable_ `const FName Tangent = TEXT("Tan` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L427 _variable_ `const FName SSSMFP = TEXT("SSS` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L428 _variable_ `const FName SSSMFPScale = TEXT("SSS` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L429 _variable_ `const FName SSSPhaseAnisotropy = TEXT("SSS` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L430 _variable_ `const FName EmissiveColor = TEXT("Emi` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L431 _variable_ `const FName SecondRoughness = TEXT("Sec` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L432 _variable_ `const FName SecondRoughnessWeight = TEXT("Sec` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L433 _variable_ `const FName FuzzRoughness = TEXT("Fuz` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L434 _variable_ `const FName FuzzAmount = TEXT("Fuz` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L435 _variable_ `const FName FuzzColor = TEXT("Fuz` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L436 _variable_ `const FName GlintValue = TEXT("Gli` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L437 _variable_ `const FName GlintUV = TEXT("Gli` (scope `UE::Interchange::Materials::Standard::Nodes::SlabBSDF::Inputs`)
- L443 _namespace_ `namespace Common` (scope `UE::Interchange::Materials`)
- L445 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Common`)
- L447 _variable_ `const FName EmissiveColor = TEXT("Emi` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: linear color
- L448 _variable_ `const FName Normal = TEXT("Nor` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: vector3f
- L449 _variable_ `const FName Tangent = TEXT("Tan` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: vector3f
- L450 _variable_ `const FName Opacity = TEXT("Opa` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: float
- L451 _variable_ `const FName OpacityMask = TEXT("Opa` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: float
- L452 _variable_ `const FName Occlusion = TEXT("Occ` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: float
- L453 _variable_ `const FName IndexOfRefraction = TEXT("IOR` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: float
- L454 _variable_ `const FName BxDF = TEXT("BxD` (scope `UE::Interchange::Materials::Common::Parameters`) — input/output of BSDF or BRDF or BXDF or BTDF data
- L455 _variable_ `const FName Refraction = TEXT("Ref` (scope `UE::Interchange::Materials::Common::Parameters`) — input/output of BSDF or BRDF or BXDF or BTDF data
- L456 _variable_ `const FName Anisotropy = TEXT("Ani` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: float
- L457 _variable_ `const FName Displacement = TEXT("Dis` (scope `UE::Interchange::Materials::Common::Parameters`) — Type: float
- L461 _namespace_ `namespace Lambert` (scope `UE::Interchange::Materials`)
- L463 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Lambert`)
- L467 _variable_ `const FName DiffuseColor = TEXT("Dif` (scope `UE::Interchange::Materials::Lambert::Parameters`) — Type: linear color
- L471 _namespace_ `namespace OpenPBRSurface` (scope `UE::Interchange::Materials`)
- L473 _variable_ `const FName Name = TEXT("ope` (scope `UE::Interchange::Materials::OpenPBRSurface`)
- L475 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::OpenPBRSurface`)
- L477 _variable_ `const FName BaseWeight = TEXT("bas` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L478 _variable_ `const FName BaseColor = TEXT("bas` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L479 _variable_ `const FName BaseRoughness = TEXT("bas` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L480 _variable_ `const FName BaseMetalness = TEXT("bas` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L481 _variable_ `const FName SpecularWeight = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L482 _variable_ `const FName SpecularColor = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L483 _variable_ `const FName SpecularRoughness = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L484 _variable_ `const FName SpecularIOR = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L485 _variable_ `const FName SpecularIORLevel = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L486 _variable_ `const FName SpecularAnisotropy = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L487 _variable_ `const FName SpecularRotation = TEXT("spe` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L488 _variable_ `const FName TransmissionWeight = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L489 _variable_ `const FName TransmissionColor = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L490 _variable_ `const FName TransmissionDepth = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L491 _variable_ `const FName TransmissionScatter = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L492 _variable_ `const FName TransmissionScatterAnisotropy = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L493 _variable_ `const FName TransmissionDispersionScale = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L494 _variable_ `const FName TransmissionDispersionAbbeNumber = TEXT("tra` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L495 _variable_ `const FName SubsurfaceWeight = TEXT("sub` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L496 _variable_ `const FName SubsurfaceColor = TEXT("sub` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L497 _variable_ `const FName SubsurfaceRadius = TEXT("sub` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L498 _variable_ `const FName SubsurfaceRadiusScale = TEXT("sub` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L499 _variable_ `const FName SubsurfaceAnisotropy = TEXT("sub` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L500 _variable_ `const FName FuzzWeight = TEXT("fuz` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L501 _variable_ `const FName FuzzColor = TEXT("fuz` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L502 _variable_ `const FName FuzzRoughness = TEXT("fuz` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L503 _variable_ `const FName CoatWeight = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L504 _variable_ `const FName CoatColor = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L505 _variable_ `const FName CoatRoughness = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L506 _variable_ `const FName CoatAnisotropy = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L507 _variable_ `const FName CoatRotation = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L508 _variable_ `const FName CoatIOR = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L509 _variable_ `const FName CoatIORLevel = TEXT("coa` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L510 _variable_ `const FName ThinFilmThickness = TEXT("thi` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L511 _variable_ `const FName ThinFilmIOR = TEXT("thi` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L512 _variable_ `const FName EmissionLuminance = TEXT("emi` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L513 _variable_ `const FName EmissionColor = TEXT("emi` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L514 _variable_ `const FName GeometryOpacity = TEXT("geo` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L515 _variable_ `const FName GeometryThinWalled = TEXT("geo` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L516 _variable_ `const FName GeometryNormal = TEXT("geo` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L517 _variable_ `const FName GeometryCoatNormal = TEXT("geo` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L518 _variable_ `const FName GeometryTangent = TEXT("geo` (scope `UE::Interchange::Materials::OpenPBRSurface::Parameters`)
- L521 _namespace_ `namespace SubstrateMaterial` (scope `UE::Interchange::Materials::OpenPBRSurface`)
- L523 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::OpenPBRSurface::SubstrateMaterial`)
- L525 _variable_ `const FName FrontMaterial = TEXT("Ope` (scope `UE::Interchange::Materials::OpenPBRSurface::SubstrateMaterial::Outputs`)
- L526 _variable_ `const FName OpacityMask = TEXT("Opa` (scope `UE::Interchange::Materials::OpenPBRSurface::SubstrateMaterial::Outputs`)
- L531 _namespace_ `namespace Phong` (scope `UE::Interchange::Materials`)
- L533 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Phong`)
- L537 _variable_ `const FName SpecularColor = TEXT("Spe` (scope `UE::Interchange::Materials::Phong::Parameters`) — Type: linear color
- L538 _variable_ `const FName Shininess = TEXT("Shi` (scope `UE::Interchange::Materials::Phong::Parameters`) — Type: float, this is the specular exponent, expected range: 2-100
- L539 _variable_ `const FName AmbientColor = TEXT("Amb` (scope `UE::Interchange::Materials::Phong::Parameters`) — Type: linear color
- L544 _namespace_ `namespace PBRSG` (scope `UE::Interchange::Materials`)
- L546 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::PBRSG`)
- L550 _variable_ `const FName DiffuseColor = TEXT("Dif` (scope `UE::Interchange::Materials::PBRSG::Parameters`) — Type: vector3
- L551 _variable_ `const FName SpecularColor = TEXT("Spe` (scope `UE::Interchange::Materials::PBRSG::Parameters`) — Type: vector3
- L552 _variable_ `const FName Glossiness = TEXT("Glo` (scope `UE::Interchange::Materials::PBRSG::Parameters`) — Type: float
- L557 _namespace_ `namespace PBRMR` (scope `UE::Interchange::Materials`)
- L559 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::PBRMR`)
- L563 _variable_ `const FName BaseColor = TEXT("Bas` (scope `UE::Interchange::Materials::PBRMR::Parameters`) — Type: vector3
- L564 _variable_ `const FName Metallic = TEXT("Met` (scope `UE::Interchange::Materials::PBRMR::Parameters`) — Type: float
- L565 _variable_ `const FName Specular = TEXT("Spe` (scope `UE::Interchange::Materials::PBRMR::Parameters`) — Type: float
- L566 _variable_ `const FName Roughness = TEXT("Rou` (scope `UE::Interchange::Materials::PBRMR::Parameters`) — Type: float
- L570 _namespace_ `namespace ClearCoat` (scope `UE::Interchange::Materials`)
- L572 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::ClearCoat`)
- L574 _variable_ `const FName ClearCoat = TEXT("Cle` (scope `UE::Interchange::Materials::ClearCoat::Parameters`) — Type: float
- L575 _variable_ `const FName ClearCoatRoughness = TEXT("Cle` (scope `UE::Interchange::Materials::ClearCoat::Parameters`) — Type: float
- L576 _variable_ `const FName ClearCoatNormal = TEXT("Cle` (scope `UE::Interchange::Materials::ClearCoat::Parameters`) — Type: vector3
- L580 _namespace_ `namespace ThinTranslucent` (scope `UE::Interchange::Materials`)
- L582 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::ThinTranslucent`)
- L584 _variable_ `const FName TransmissionColor = TEXT("Tra` (scope `UE::Interchange::Materials::ThinTranslucent::Parameters`) — Type: vector3
- L585 _variable_ `const FName SurfaceCoverage = TEXT("Sur` (scope `UE::Interchange::Materials::ThinTranslucent::Parameters`) — Type: float
- L589 _namespace_ `namespace Sheen` (scope `UE::Interchange::Materials`)
- L591 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Sheen`)
- L593 _variable_ `const FName SheenColor = TEXT("She` (scope `UE::Interchange::Materials::Sheen::Parameters`) — Type: vector3
- L594 _variable_ `const FName SheenRoughness = TEXT("She` (scope `UE::Interchange::Materials::Sheen::Parameters`) — Type: float
- L598 _namespace_ `namespace Subsurface` (scope `UE::Interchange::Materials`)
- L600 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Subsurface`)
- L602 _variable_ `const FName SubsurfaceColor = TEXT("Sub` (scope `UE::Interchange::Materials::Subsurface::Parameters`) — Type: linear color
- L606 _namespace_ `namespace StandardSurface` (scope `UE::Interchange::Materials`)
- L608 _variable_ `const FName Name = TEXT("sta` (scope `UE::Interchange::Materials::StandardSurface`)
- L610 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::StandardSurface`)
- L612 _variable_ `const FName Base = TEXT("bas` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L613 _variable_ `const FName BaseColor = TEXT("bas` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L614 _variable_ `const FName DiffuseRoughness = TEXT("dif` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L615 _variable_ `const FName Metalness = TEXT("met` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L616 _variable_ `const FName Specular = TEXT("spe` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L617 _variable_ `const FName SpecularColor = TEXT("spe` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L618 _variable_ `const FName SpecularRoughness = TEXT("spe` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L619 _variable_ `const FName SpecularIOR = TEXT("spe` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L620 _variable_ `const FName SpecularAnisotropy = TEXT("spe` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L621 _variable_ `const FName SpecularRotation = TEXT("spe` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L622 _variable_ `const FName Transmission = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L623 _variable_ `const FName TransmissionColor = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L624 _variable_ `const FName TransmissionDepth = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L625 _variable_ `const FName TransmissionScatter = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L626 _variable_ `const FName TransmissionScatterAnisotropy = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L627 _variable_ `const FName TransmissionDispersion = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L628 _variable_ `const FName TransmissionExtraRoughness = TEXT("tra` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L629 _variable_ `const FName Subsurface = TEXT("sub` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L630 _variable_ `const FName SubsurfaceColor = TEXT("sub` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L631 _variable_ `const FName SubsurfaceRadius = TEXT("sub` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L632 _variable_ `const FName SubsurfaceScale = TEXT("sub` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L633 _variable_ `const FName SubsurfaceAnisotropy = TEXT("sub` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L634 _variable_ `const FName Sheen = TEXT("she` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L635 _variable_ `const FName SheenColor = TEXT("she` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L636 _variable_ `const FName SheenRoughness = TEXT("she` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L637 _variable_ `const FName Coat = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L638 _variable_ `const FName CoatColor = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L639 _variable_ `const FName CoatRoughness = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L640 _variable_ `const FName CoatAnisotropy = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L641 _variable_ `const FName CoatRotation = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L642 _variable_ `const FName CoatIOR = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L643 _variable_ `const FName CoatNormal = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L644 _variable_ `const FName CoatAffectColor = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L645 _variable_ `const FName CoatAffectRoughness = TEXT("coa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L646 _variable_ `const FName ThinFilmThickness = TEXT("thi` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L647 _variable_ `const FName ThinFilmIOR = TEXT("thi` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L648 _variable_ `const FName Emission = TEXT("emi` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L649 _variable_ `const FName EmissionColor = TEXT("emi` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L650 _variable_ `const FName Opacity = TEXT("opa` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L651 _variable_ `const FName ThinWalled = TEXT("thi` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L652 _variable_ `const FName Normal = TEXT("nor` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L653 _variable_ `const FName Tangent = TEXT("tan` (scope `UE::Interchange::Materials::StandardSurface::Parameters`)
- L657 _namespace_ `namespace SubstrateMaterial` (scope `UE::Interchange::Materials::StandardSurface`)
- L659 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::StandardSurface::SubstrateMaterial`)
- L661 _variable_ `const FName Opaque = TEXT("Sub` (scope `UE::Interchange::Materials::StandardSurface::SubstrateMaterial::Outputs`)
- L662 _variable_ `const FName Translucent = TEXT("Sub` (scope `UE::Interchange::Materials::StandardSurface::SubstrateMaterial::Outputs`)
- L663 _variable_ `const FName Opacity = TEXT("Geo` (scope `UE::Interchange::Materials::StandardSurface::SubstrateMaterial::Outputs`)
- L664 _variable_ `const FName Refraction = TEXT("Ref` (scope `UE::Interchange::Materials::StandardSurface::SubstrateMaterial::Outputs`)
- L669 _namespace_ `namespace Surface` (scope `UE::Interchange::Materials`)
- L671 _variable_ `const FName Name = TEXT("sur` (scope `UE::Interchange::Materials::Surface`)
- L673 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Surface`)
- L675 _variable_ `const FName BSDF = TEXT("bsd` (scope `UE::Interchange::Materials::Surface::Parameters`)
- L676 _variable_ `const FName EDF = TEXT("edf` (scope `UE::Interchange::Materials::Surface::Parameters`)
- L677 _variable_ `const FName Opacity = TEXT("opa` (scope `UE::Interchange::Materials::Surface::Parameters`)
- L680 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::Surface`)
- L682 _variable_ `const FName Surface = TEXT("Sur` (scope `UE::Interchange::Materials::Surface::Outputs`)
- L685 _namespace_ `namespace Substrate` (scope `UE::Interchange::Materials::Surface`)
- L687 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::Surface::Substrate`)
- L690 _variable_ `const FName Opacity = TEXT("Opa` (scope `UE::Interchange::Materials::Surface::Substrate::Outputs`)
- L695 _namespace_ `namespace SurfaceUnlit` (scope `UE::Interchange::Materials`)
- L697 _variable_ `const FName Name = TEXT("sur` (scope `UE::Interchange::Materials::SurfaceUnlit`)
- L699 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::SurfaceUnlit`)
- L701 _variable_ `const FName Emission = TEXT("emi` (scope `UE::Interchange::Materials::SurfaceUnlit::Parameters`)
- L702 _variable_ `const FName EmissionColor = TEXT("emi` (scope `UE::Interchange::Materials::SurfaceUnlit::Parameters`)
- L703 _variable_ `const FName Transmission = TEXT("tra` (scope `UE::Interchange::Materials::SurfaceUnlit::Parameters`)
- L704 _variable_ `const FName TransmissionColor = TEXT("tra` (scope `UE::Interchange::Materials::SurfaceUnlit::Parameters`)
- L705 _variable_ `const FName Opacity = TEXT("opa` (scope `UE::Interchange::Materials::SurfaceUnlit::Parameters`)
- L708 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::SurfaceUnlit`)
- L710 _variable_ `const FName OpacityMask = TEXT("Opa` (scope `UE::Interchange::Materials::SurfaceUnlit::Outputs`)
- L713 _namespace_ `namespace Substrate` (scope `UE::Interchange::Materials::SurfaceUnlit`)
- L715 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::SurfaceUnlit::Substrate`)
- L718 _variable_ `const FName SurfaceUnlit = TEXT("Sur` (scope `UE::Interchange::Materials::SurfaceUnlit::Substrate::Outputs`)
- L723 _namespace_ `namespace UsdPreviewSurface` (scope `UE::Interchange::Materials`)
- L725 _variable_ `const FName Name = TEXT("Usd` (scope `UE::Interchange::Materials::UsdPreviewSurface`)
- L727 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::UsdPreviewSurface`)
- L729 _variable_ `const FName DiffuseColor = TEXT("dif` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L730 _variable_ `const FName EmissiveColor = TEXT("emi` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L731 _variable_ `const FName SpecularColor = TEXT("spe` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L732 _variable_ `const FName Metallic = TEXT("met` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L733 _variable_ `const FName Roughness = TEXT("rou` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L734 _variable_ `const FName Clearcoat = TEXT("cle` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L735 _variable_ `const FName ClearcoatRoughness = TEXT("cle` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L736 _variable_ `const FName Opacity = TEXT("opa` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L737 _variable_ `const FName OpacityThreshold = TEXT("opa` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L738 _variable_ `const FName IOR = TEXT("ior` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L739 _variable_ `const FName Normal = TEXT("nor` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L740 _variable_ `const FName Displacement = TEXT("dis` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L741 _variable_ `const FName Occlusion = TEXT("occ` (scope `UE::Interchange::Materials::UsdPreviewSurface::Parameters`)
- L745 _namespace_ `namespace SubstrateMaterial` (scope `UE::Interchange::Materials::UsdPreviewSurface`)
- L747 _namespace_ `namespace Outputs` (scope `UE::Interchange::Materials::UsdPreviewSurface::SubstrateMaterial`)
- L749 _variable_ `const FName FrontMaterial = TEXT("Sub` (scope `UE::Interchange::Materials::UsdPreviewSurface::SubstrateMaterial::Outputs`)
- L750 _variable_ `const FName Displacement = TEXT("Dis` (scope `UE::Interchange::Materials::UsdPreviewSurface::SubstrateMaterial::Outputs`)
- L751 _variable_ `const FName Occlusion = TEXT("Occ` (scope `UE::Interchange::Materials::UsdPreviewSurface::SubstrateMaterial::Outputs`)
- L756 _namespace_ `namespace Unlit` (scope `UE::Interchange::Materials`)
- L758 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::Unlit`)
- L760 _variable_ `const FName UnlitColor = TEXT("Unl` (scope `UE::Interchange::Materials::Unlit::Parameters`) — Type: linear color
- L764 _namespace_ `namespace SubstrateMaterial` (scope `UE::Interchange::Materials`)
- L766 _variable_ `const FName SpecularProfile = TEXT("Spe` (scope `UE::Interchange::Materials::SubstrateMaterial`) — Used by MaterialInstances otherwise look at SubstrateSlabBSDF
- L768 _namespace_ `namespace Parameters` (scope `UE::Interchange::Materials::SubstrateMaterial`)
- L770 _variable_ `const FName FrontMaterial = TEXT("Fro` (scope `UE::Interchange::Materials::SubstrateMaterial::Parameters`)
- L771 _variable_ `const FName OpacityMask = TEXT("Opa` (scope `UE::Interchange::Materials::SubstrateMaterial::Parameters`)
- L772 _variable_ `const FName Displacement = TEXT("Dis` (scope `UE::Interchange::Materials::SubstrateMaterial::Parameters`)
- L773 _variable_ `const FName Occlusion = TEXT("Occ` (scope `UE::Interchange::Materials::SubstrateMaterial::Parameters`)
- L777 _namespace_ `namespace Factory` (scope `UE::Interchange::Materials`)
- L779 _namespace_ `namespace Expression` (scope `UE::Interchange::Materials::Factory`)
- L781 _variable_ `const FName Path = TEXT("Mat` (scope `UE::Interchange::Materials::Factory::Expression`) — Attribute used by the factory to store the path of a UMaterialExpression

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMaterialInstanceNode.h` (Public)


#### class `UInterchangeMaterialInstanceNode`  
`class UInterchangeMaterialInstanceNode : public UInterchangeBaseNode`  
_L15-93_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L24 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L26 _public prototype_ `virtual FName GetIconName() const override;`
- L31 _public prototype_ `static FString MakeNodeUid(const FStringView NodeName, const FStringView ParentNodeUid);` — Build and return a UID name for a material instance node.
- L36 _public prototype_ `static UInterchangeMaterialInstanceNode* Create(UInterchangeBaseNodeContainer* NodeContainer, const FStringView NodeName, const FStringView ParentNodeUid);` — Creates a new UInterchangeMaterialInstanceNode and adds it to NodeContainer as a translated node.
- L40 _public prototype_ `bool SetCustomParent(const FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")` — Path to an existing Material or the UID of a ShaderGraphNode
- L43 _public prototype_ `bool GetCustomParent(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L46 _public prototype_ `bool AddScalarParameterValue(const FString & ParameterName, float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L49 _public prototype_ `bool GetScalarParameterValue(const FString& ParameterName, float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L52 _public prototype_ `bool AddVectorParameterValue(const FString& ParameterName, const FLinearColor& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L55 _public prototype_ `bool GetVectorParameterValue(const FString& ParameterName, FLinearColor& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L58 _public prototype_ `bool AddTextureParameterValue(const FString& ParameterName, const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L61 _public prototype_ `bool GetTextureParameterValue(const FString& ParameterName, FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L64 _public prototype_ `bool AddStaticSwitchParameterValue(const FString& ParameterName, bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L67 _public prototype_ `bool GetStaticSwitchParameterValue(const FString& ParameterName, bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Instance")`
- L70 _public prototype_ `bool GetCustomBlendMode(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L73 _public prototype_ `bool SetCustomBlendMode(int32 AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L76 _public prototype_ `bool GetCustomTwoSided(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L79 _public prototype_ `bool SetCustomTwoSided(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L82 _public prototype_ `bool GetCustomEnableTessellation(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L85 _public prototype_ `bool SetCustomEnableTessellation(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L89 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Parent);`
- L90 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(BlendMode);`
- L91 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(TwoSided);`
- L92 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(EnableTessellation);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMaterialReferenceNode.h` (Public)


#### class `UInterchangeMaterialReferenceNode`  
`class UInterchangeMaterialReferenceNode : public UInterchangeBaseNode`  
_L19-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: Describes a reference to an existing (as in, not imported) material. The idea is that mesh / actor nodes can reference one of these nodes as a slot dependency, and Interchange will assign that existing material to the corresponding slot during import
- L24 _public prototype_ `virtual FString GetTypeName() const override;`
- L29 _public prototype_ `bool GetCustomContentPath(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Reference")` — Gets the content path of the target material (e.g. "/Game/MyFolder/Red.Red")
- L33 _public prototype_ `bool SetCustomContentPath(const FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material Reference")` — Sets the content path of the target material (e.g. "/Game/MyFolder/Red.Red")
- L36 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ContentPath);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMeshBundleNode.h` (Public)


#### class `UInterchangeMeshBundleNode`  
`class UInterchangeMeshBundleNode : public UInterchangeBaseNode`  
_L22-73_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: This node represents a collection of UInterchangeMeshNode UIDs, each associated with N transforms. This is used in the context of collapsing, where the transforms represent collapsed instances of the corresponding mesh nodes. The whole MeshBundle may be converted into a single static mesh or a single skeletal mesh. In both cases, the transforms are relative to the "collapsing root". When the bundle has a valid SkeletonDependencyUid, it represents a group of skinned meshes that should be combined into a single skeletal mesh asset.
- L28 _public prototype_ `UInterchangeMeshBundleNode();`
- L30 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L32 _public prototype_ `virtual FString GetTypeName() const override;`
- L33 _public prototype_ `virtual FName GetIconName() const override;`
- L36 _public prototype_ `bool AddMeshNodeTransform(const FString& MeshNodeUid, const FTransform& Transform);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | MeshBundle")`
- L39 _public prototype_ `bool AddMeshNodeTransforms(const FString& MeshNodeUid, const TArray<FTransform>& Transforms);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | MeshBundle")`
- L42 _public prototype_ `bool GetMeshNodeUids(TArray<FString>& OutMeshNodeUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | MeshBundle")`
- L45 _public prototype_ `bool GetMeshNodeTransforms(const FString& MeshNodeUid, TArray<FTransform>& OutNodeTransforms) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | MeshBundle")`
- L48 _public prototype_ `bool RemoveMeshNodeUid(const FString& MeshLODNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | MeshBundle")`
- L51 _public prototype_ `void ResetMeshNodeUids();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | MeshBundle")`
- L55 _public prototype_ `bool GetCustomSkeletonDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MeshBundle")` — Get the skeleton dependency UID for this bundle. Returns false if not set.
- L59 _public prototype_ `bool SetCustomSkeletonDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MeshBundle")` — Set the skeleton dependency UID. When set, this bundle represents a group of skinned meshes.
- L62 _public prototype_ `bool IsSkinnedMeshBundle() const;` — Returns true if this bundle has a valid skeleton dependency, meaning it represents skinned meshes.
- L66 _public prototype_ `void GetAllMeshNodesAndTransforms(TMap<FString, TArray<FTransform>>& OutMeshNodeToTransforms) const;` — Separate C++ only functions as the signature is not valid for a UFUNCTION
- L67 _public prototype_ `void SetAllMeshNodesAndTransforms(const TMap<FString, TArray<FTransform>>& InMeshNodeToTransforms);`
- L70 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SkeletonDependencyUid);`
- L72 _private member_ `UE::Interchange::TMapAttributeHelper<FString, TArray<FTransform>> MeshNodeToTransforms;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMeshDefinitions.h` (Public)


#### enum `EInterchangeMeshCollision`  
`enum class EInterchangeMeshCollision : uint8`  
_L11-39_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Box` — Generates a new box collision mesh encompassing the static mesh
- L17 _public enumerator_ `Sphere` — Generates a new sphere collision mesh encompassing the static mesh
- L20 _public enumerator_ `Capsule` — Generates a new capsule collision mesh encompassing the static mesh
- L23 _public enumerator_ `Convex10DOP_X UMETA(DisplayName="10DOP-X Simplified")` — Generates a new axis-aligned box collision mesh with the 4 X-axis aligned edges beveled (10 total sides) encompassing the static mesh
- L26 _public enumerator_ `Convex10DOP_Y UMETA(DisplayName = "10DOP-Y Simplified")` — Generates a new axis-aligned box collision mesh with the 4 Y-axis aligned edges beveled (10 total sides) encompassing the static mesh
- L29 _public enumerator_ `Convex10DOP_Z UMETA(DisplayName = "10DOP-Z Simplified")` — Generates a new axis-aligned box collision mesh with the 4 Z-axis aligned edges beveled (10 total sides) encompassing the static mesh
- L32 _public enumerator_ `Convex18DOP UMETA(DisplayName = "18DOP Simplified")` — Generates a new axis-aligned box collision mesh with all edges beveled (18 total sides) encompassing the static mesh
- L35 _public enumerator_ `Convex26DOP UMETA(DisplayName = "26DOP Simplified")` — Generates a new axis-aligned box collision mesh with all edges and corners beveled (26 total sides) encompassing the static mesh
- L38 _public enumerator_ `None = 0xFF` — Generates no collisions, but continue to import custom collisions if the file has ones

#### enum `EInterchangeMotionVectorsHandling`  
`enum class EInterchangeMotionVectorsHandling : uint8`  
_L42-50_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `NoMotionVectors` — No motion vectors will be present in the geometry cache.
- L47 _public enumerator_ `ImportVelocitiesAsMotionVectors` — Imports the velocities and converts them to motion vectors. This will increase file size as the motion vectors will be stored on disc.
- L49 _public enumerator_ `CalculateMotionVectorsDuringImport` — Force calculation of motion vectors during import. This will increase file size as the motion vectors will be stored on disc.

#### Free symbols / members of external scopes

- L52 _namespace_ `namespace UE`
- L54 _namespace_ `namespace Interchange` (scope `UE`)
- L56 _namespace_ `namespace MeshPayload` (scope `UE::Interchange`)
- L58 _namespace_ `namespace Attributes` (scope `UE::Interchange::MeshPayload`)
- L61 _variable_ `const FString RootJointGlobalTransform = TEXT("__P` (scope `UE::Interchange::MeshPayload::Attributes`) — Global transform of the scene node that corresponds to the root joint of the skeleton. Already includes GlobalOffsetTransform
- L64 _variable_ `const FString MeshGlobalTransform = TEXT("__P` (scope `UE::Interchange::MeshPayload::Attributes`) — Global transform for the mesh scene node. Already includes GlobalOffsetTransform
- L67 _variable_ `const FString GlobalOffsetTransform = TEXT("__P` (scope `UE::Interchange::MeshPayload::Attributes`) — Additional transform to be added last during the mesh baking (so as if an additional parent transform of the top level actor)
- L70 _variable_ `const FString BakeMeshes = TEXT("__P` (scope `UE::Interchange::MeshPayload::Attributes`) — Whether to perform mesh baking or not

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMeshLODContainerNode.h` (Public)


#### class `UInterchangeMeshLODContainerNode`  
`class UInterchangeMeshLODContainerNode : public UInterchangeBaseNode`  
_L16-87_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L22 _public member_ `inline static const FString MeshLODPrefix = TEXT("\\M`
- L24 _public prototype_ `UInterchangeMeshLODContainerNode();`
- L26 _public prototype_ `virtual FString GetTypeName() const override;`
- L28 _public prototype_ `virtual FName GetIconName() const override;`
- L30 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L43 _public prototype_ `bool AddMeshLODNodeUid(const FString& MeshLODNodeUid);` — `UE_DEPRECATED(5.8, "Deprecated. Use AddMeshForLODIndex instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | LODContainer")` — Deprecated functions
- L47 _public prototype_ `void GetMeshLODNodeUids(TArray<FString>& OutMeshLODNodeUid) const;` — `UE_DEPRECATED(5.8, "Deprecated. Use GetLODMeshDataPerLODIndices or GetAllReferencedMeshUids instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | LODContainer")`
- L51 _public prototype_ `bool RemoveMeshLODNodeUid(const FString& MeshLODNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | LODContainer")`
- L54 _public prototype_ `bool ResetMeshLODNodeUids();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | LODContainer")`
- L57 _public prototype_ `bool AddMeshForLODIndex(const int32 LODIndex, const FString& MeshUid, const FTransform& Transform);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | LODContainer")`
- L63 _public prototype_ `void GetLODMeshDataPerLODIndices(TMap<int32, TArray<FInterchangeLODMeshData>>& OutLODMeshesPerLODIndices) const;` — Gets all LOD Meshes (MeshUID+Transform) per LOD Indices. We only use the MeshUid and Transform attributes from FInterchangeLODMeshData.
- L66 _public prototype_ `void GetAllReferencedMeshUids(TSet<FString>& OutMeshUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | LODContainer")`
- L72 _public prototype_ `void ValidateMorphTargets(UInterchangeBaseNodeContainer* NodeContainer, const TMap<int32, TArray<FInterchangeLODMeshData>>& LODMeshesPerLODIndices) const;` — Validates that all MorphTargets used by LOD Index X are present and used by LOD Index X-1. In case the validation failed we report warning.
- L78 _public prototype_ `static bool CheckForLODPattern(const FString& Candidate, int32& LODIndex, FString& LODContainerName, FString& ErrorString);` — Supported LOD Pattern: "LODx_Name", where xx is a number and the Name is the LOD Container/Group's name.
- L80 _public prototype_ `static FString MakeMeshLODContainerUid(const FString& OriginalUid);`
- L86 _private member_ `UE::Interchange::TMapAttributeHelper<int32, TArray<FInterchangeLODMeshData>> LODMeshDataPerLODIndices;` — Attribute to store FInterchangeLODMeshData per LODIndex. #interchange_LODRefactor_Note: we only use MeshUid and Transform from FInterchangeLODMeshData at this stage.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeMeshLODContainerNode, Log, All) class UInterchangeBaseNodeContainer;`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeMeshNode.h` (Public)


#### struct `UE::Interchange::FMeshNodeStaticData`  
`struct FMeshNodeStaticData : public FBaseNodeStaticData`  
_L19-31_
- inherits: `FBaseNodeStaticData`
- L21 _public prototype_ `static const FAttributeKey& PayLoadKey();`
- L22 _public prototype_ `static const FAttributeKey& PayLoadTypeKey();`
- L23 _public prototype_ `static const FAttributeKey& IsSkinnedMeshKey();`
- L24 _public prototype_ `static const FAttributeKey& IsMorphTargetKey();`
- L25 _public prototype_ `static const FAttributeKey& MorphTargetNameKey();`
- L26 _public prototype_ `static const FAttributeKey& GetSkeletonDependenciesKey();`
- L27 _public prototype_ `static const FAttributeKey& GetMorphTargetDependenciesKey();`
- L28 _public prototype_ `static const FAttributeKey& GetSceneInstancesUidsKey();`
- L29 _public prototype_ `static const FAttributeKey& GetSlotMaterialDependenciesKey();`
- L30 _public prototype_ `static const FAttributeKey& GetAssemblyPartDependenciesKey();`

#### enum `EInterchangeMeshPayLoadType`  
`enum class EInterchangeMeshPayLoadType : uint8`  
_L37-44_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `NONE = 0`
- L40 _public enumerator_ `STATIC`
- L41 _public enumerator_ `SKELETAL`
- L42 _public enumerator_ `MORPHTARGET`
- L43 _public enumerator_ `ANIMATED`

#### struct `FInterchangeMeshPayLoadKey`  
`struct FInterchangeMeshPayLoadKey`  
_L48-96_
- reflection: `USTRUCT(BlueprintType)`
- L55 _public member_ `FString UniqueId = "";` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Mesh")`
- L58 _public member_ `EInterchangeMeshPayLoadType Type = EInterchangeMeshPayLoadType::NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Mesh")`
- L61 _public member_ `int32 FrameNumber = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | GeometryCache")`
- L63 _public function_ `FInterchangeMeshPayLoadKey()`
- L65 _public function_ `FInterchangeMeshPayLoadKey(const FString& InUniqueId, const EInterchangeMeshPayLoadType& InType) : UniqueId(InUniqueId) , Type(InType)`
- L71 _public function_ `FInterchangeMeshPayLoadKey(const FString& InUniqueId, int32 InFrameNumber) : UniqueId(InUniqueId) , Type(EInterchangeMeshPayLoadType::ANIMATED) , FrameNumber(InFrameNumber)`
- L78 _public function_ `bool operator==(const FInterchangeMeshPayLoadKey& Other) const`
- L84 _public function_ `static FString GetTransformString(const FTransform& Transform)` — Return the translator key merge with the transform

#### class `UInterchangeMeshNode`  
`class UInterchangeMeshNode : public UInterchangeBaseNode`  
_L100-425_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- L105 _public prototype_ `UInterchangeMeshNode();`
- L108 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L110 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L116 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L121 _public prototype_ `virtual FName GetIconName() const override;` — Icon names are created by adding "InterchangeIcon_" in front of the specialized type. If there is no special type, the function will return NAME_None, which will use the default icon.
- L126 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SlotMaterialDependencies on load.
- L140 _public prototype_ `bool IsSkinnedMesh() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Return true if this node represents a skinned mesh.
- L146 _public prototype_ `bool SetSkinnedMesh(const bool bIsSkinnedMesh);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the IsSkinnedMesh attribute to determine whether this node represents a skinned mesh.
- L152 _public prototype_ `bool IsMorphTarget() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Return true if this node represents a morph target.
- L158 _public prototype_ `bool SetMorphTarget(const bool bIsMorphTarget);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the IsMorphTarget attribute to determine whether this node represents a morph target.
- L165 _public prototype_ `bool GetMorphTargetName(FString& OutMorphTargetName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get the morph target name. Return true if we successfully retrieved the MorphTargetName attribute.
- L171 _public prototype_ `bool SetMorphTargetName(const FString& MorphTargetName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the MorphTargetName attribute to determine the name of the morph target.
- L173 _public prototype_ `virtual const TOptional<FInterchangeMeshPayLoadKey> GetPayLoadKey() const;`
- L176 _public prototype_ `virtual void SetPayLoadKey(const FString& PayLoadKey, const EInterchangeMeshPayLoadType& PayLoadType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")`
- L180 _public prototype_ `bool GetCustomVertexCount(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query the vertex count of this mesh. Return false if the attribute was not set.
- L184 _public prototype_ `bool SetCustomVertexCount(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the vertex count of this mesh. Return false if the attribute could not be set.
- L188 _public prototype_ `bool GetCustomPolygonCount(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query the polygon count of this mesh. Return false if the attribute was not set.
- L192 _public prototype_ `bool SetCustomPolygonCount(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the polygon count of this mesh. Return false if the attribute could not be set.
- L196 _public prototype_ `bool GetCustomBoundingBox(FBox& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query the bounding box of this mesh. Return false if the attribute was not set.
- L200 _public prototype_ `bool SetCustomBoundingBox(const FBox& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the bounding box of this mesh. Return false if the attribute could not be set.
- L204 _public prototype_ `bool GetCustomHasVertexNormal(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query whether this mesh has vertex normals. Return false if the attribute was not set.
- L208 _public prototype_ `bool SetCustomHasVertexNormal(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the vertex normal attribute of this mesh. Return false if the attribute could not be set.
- L212 _public prototype_ `bool GetCustomHasVertexBinormal(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query whether this mesh has vertex bi-normals. Return false if the attribute was not set.
- L216 _public prototype_ `bool SetCustomHasVertexBinormal(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the vertex bi-normal attribute of this mesh. Return false if the attribute could not be set.
- L220 _public prototype_ `bool GetCustomHasVertexTangent(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query whether this mesh has vertex tangents. Return false if the attribute was not set.
- L224 _public prototype_ `bool SetCustomHasVertexTangent(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the vertex tangent attribute of this mesh. Return false if the attribute could not be set.
- L228 _public prototype_ `bool GetCustomHasSmoothGroup(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query whether this mesh has smoothing groups. Return false if the attribute was not set.
- L232 _public prototype_ `bool SetCustomHasSmoothGroup(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the smoothing group attribute of this mesh. Return false if the attribute could not be set.
- L236 _public prototype_ `bool GetCustomHasVertexColor(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query whether this mesh has vertex colors. Return false if the attribute was not set.
- L240 _public prototype_ `bool SetCustomHasVertexColor(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the vertex color attribute of this mesh. Return false if the attribute could not be set.
- L244 _public prototype_ `bool GetCustomUVCount(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query the UV count of this mesh. Return false if the attribute was not set.
- L248 _public prototype_ `bool SetCustomUVCount(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the UV count attribute of this mesh. Return false if the attribute could not be set.
- L254 _public prototype_ `int32 GetSkeletonDependeciesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the number of skeleton dependencies for this object.
- L260 _public prototype_ `void GetSkeletonDependencies(TArray<FString>& OutDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the skeleton dependency for this object.
- L266 _public prototype_ `void GetSkeletonDependency(const int32 Index, FString& OutDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the specified skeleton dependency for this object.
- L272 _public prototype_ `bool SetSkeletonDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add the specified skeleton dependency to this object.
- L278 _public prototype_ `bool RemoveSkeletonDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Remove the specified skeleton dependency from this object.
- L284 _public prototype_ `int32 GetMorphTargetDependeciesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the number of morph target dependencies for this object.
- L290 _public prototype_ `void GetMorphTargetDependencies(TArray<FString>& OutDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve all morph target dependencies for this object.
- L296 _public prototype_ `void GetMorphTargetDependency(const int32 Index, FString& OutDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the specified morph target dependency for this object.
- L302 _public prototype_ `bool SetMorphTargetDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add the specified morph target dependency to this object.
- L308 _public prototype_ `bool RemoveMorphTargetDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Remove the specified morph target dependency from this object.
- L314 _public prototype_ `int32 GetSceneInstanceUidsCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the number of scene nodes instancing this mesh.
- L320 _public prototype_ `void GetSceneInstanceUids(TArray<FString>& OutDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the asset instances this scene node refers to.
- L326 _public prototype_ `void GetSceneInstanceUid(const int32 Index, FString& OutDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the asset instance this scene node refers to.
- L332 _public prototype_ `bool SetSceneInstanceUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add the specified asset instance this scene node refers to.
- L338 _public prototype_ `bool RemoveSceneInstanceUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Remove the specified asset instance this scene node refers to.
- L344 _public prototype_ `void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Retrieve the correspondence table between slot names and assigned materials for this object.
- L350 _public prototype_ `bool GetSlotMaterialDependencyUid(const FString& SlotName, FString& OutMaterialDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Retrieve the specified Material dependency for a given slot of this object.
- L356 _public prototype_ `bool SetSlotMaterialDependencyUid(const FString& SlotName, const FString& MaterialDependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Add the specified Material dependency to a specific slot name of this object.
- L362 _public prototype_ `bool RemoveSlotMaterialDependencyUid(const FString& SlotName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Remove the Material dependency associated with the given slot name from this object.
- L368 _public prototype_ `int32 GetAssemblyPartDependenciesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the number of Nanite assembly part dependencies for this object.
- L374 _public prototype_ `void GetAssemblyPartDependencies(TArray<FString>& OutDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the Nanite assembly part dependencies for this object.
- L380 _public prototype_ `void GetAssemblyPartDependency(const int32 Index, FString& OutDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Retrieve the specified Nanite assembly part dependency for this object.
- L386 _public prototype_ `bool AddAssemblyPartDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add the specified Nanite assembly part dependency to this object.
- L392 _public prototype_ `bool RemoveAssemblyPartDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Remove the specified Nanite assembly part dependency from this object.
- L400 _public prototype_ `bool GetCustomCollisionType(EInterchangeMeshCollision& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get the type of collision shapes we should generate from this mesh. Note: This is a separate mechanism from the FBX-style collision shape name prefixes. For now, these collision shapes will only be used for the static mesh generated from this very same Mesh node
- L404 _public prototype_ `bool SetCustomCollisionType(EInterchangeMeshCollision AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the type of collision shapes we should generate from this mesh
- L407 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(VertexCount);`
- L408 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(PolygonCount);`
- L409 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(BoundingBox);`
- L410 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasVertexNormal);`
- L411 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasVertexBinormal);`
- L412 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasVertexTangent);`
- L413 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasSmoothGroup);`
- L414 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasVertexColor);`
- L415 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(UVCount);`
- L416 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(CollisionType);`
- L418 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> SkeletonDependencies;`
- L419 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> MaterialDependencies;`
- L420 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> MorphTargetDependencies;`
- L421 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> AssemblyPartDependencies;`
- L422 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> SceneInstancesUids;`
- L424 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SlotMaterialDependencies;`

#### class `UInterchangeGeometryCacheNode`  
`class UInterchangeGeometryCacheNode : public UInterchangeMeshNode`  
_L428-472_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeMeshNode`
- L433 _public prototype_ `UInterchangeGeometryCacheNode();`
- L437 _public prototype_ `bool GetCustomStartFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Query the start frame of the animated mesh. Return false if the attribute was not set.
- L441 _public prototype_ `bool SetCustomStartFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the start frame of the animated mesh. Return false if the attribute could not be set.
- L445 _public prototype_ `bool GetCustomEndFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Query the end frame of the animated mesh. Return false if the attribute was not set.
- L449 _public prototype_ `bool SetCustomEndFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the end frame of the animated mesh. Return false if the attribute could not be set.
- L453 _public prototype_ `bool GetCustomFrameRate(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Query the frame rate of the animated mesh. Return false if the attribute was not set.
- L457 _public prototype_ `bool SetCustomFrameRate(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the frame rate of the animated mesh. Return false if the attribute could not be set.
- L461 _public prototype_ `bool GetCustomHasConstantTopology(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Query whether this animated mesh has constant topoplogy. Return false if the attribute was not set.
- L465 _public prototype_ `bool SetCustomHasConstantTopology(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the constant topology attribute of this animated mesh. Return false if the attribute could not be set.
- L468 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(StartFrame);`
- L469 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(EndFrame);`
- L470 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FrameRate);`
- L471 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HasConstantTopology);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGENODES_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)
- L92 _function_ `friend uint32 GetTypeHash(const FInterchangeMeshPayLoadKey& InterchangeMeshPayLoadKey)`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeNodesModule.h` (Public)


#### class `IInterchangeNodesModule`  
`class IInterchangeNodesModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L25 _public function_ `static inline IInterchangeNodesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeNodes, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeNodes, Log, All);`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeSceneComponentNodes.h` (Public)


#### class `UInterchangeSceneComponentNode`  
`class UInterchangeSceneComponentNode : public UInterchangeBaseNode`  
_L15-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L21 _public prototype_ `UInterchangeSceneComponentNode();`
- L26 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L30 _public prototype_ `bool AddComponentUid(const FString& ComponentUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L33 _public prototype_ `void GetComponentUids(TArray<FString>& OutComponentUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L37 _public prototype_ `bool GetCustomLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L40 _public prototype_ `bool SetCustomLocalTransform(const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L44 _public prototype_ `bool GetCustomComponentVisibility(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L47 _public prototype_ `bool SetCustomComponentVisibility(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L52 _public prototype_ `const UInterchangeSceneNode* GetParentSceneNodeAndTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, FTransform& SceneNodeTransform, bool bForceRecache = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Instanced")` — Get's the SceneNode that the SceneComponentNode belongs to, also calculates the GlobalTransform within the SceneNode space.
- L56 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomLocalTransformKey = UE::Interchange::FAttributeKey(TEXT("Loca` — Component's Local Transform.
- L59 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomComponentVisibilityKey = UE::Interchange::FAttributeKey(TEXT("Comp` — Component's Visibility
- L62 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> ComponentUids;` — Children Component Uids.
- L65 _private member_ `mutable TOptional<FTransform> CacheSceneNodeTransform;` — mutable caches for global transforms
- L66 _private member_ `mutable TOptional<const UInterchangeSceneNode*> CacheParentSceneNode;`

#### class `UInterchangeInstancedStaticMeshComponentNode`  
`class UInterchangeInstancedStaticMeshComponentNode : public UInterchangeSceneComponentNode`  
_L70-104_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeSceneComponentNode`
- L75 _public prototype_ `UInterchangeInstancedStaticMeshComponentNode();`
- L80 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L83 _public prototype_ `void AddInstanceTransform(const FTransform& InstanceTransform);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Instanced")`
- L85 _public prototype_ `void AddInstanceTransforms(const TArray<FTransform>& InInstanceTransforms);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Instanced")`
- L88 _public prototype_ `void GetInstanceTransforms(TArray<FTransform>& OutInstanceTransforms) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Instanced")`
- L92 _public prototype_ `bool GetCustomInstancedAssetUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Instanced")` — Get which asset, if any, a scene node is instantiating. Return false if the Attribute was not set previously.
- L96 _public prototype_ `bool SetCustomInstancedAssetUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Instanced")` — Add an asset for this scene node to instantiate.
- L100 _private member_ `UE::Interchange::TArrayAttributeHelper<FTransform> InstanceTransforms;` — Instanced StaticMesh Component's Instances.
- L103 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAssetInstanceUidKey = UE::Interchange::FAttributeKey(TEXT("Asse` — To track/connect StaticMesh.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeSceneNode.h` (Public)


#### struct `UE::Interchange::FSceneNodeStaticData`  
`struct FSceneNodeStaticData : public FBaseNodeStaticData`  
_L20-37_
- inherits: `FBaseNodeStaticData`
- L22 _public prototype_ `static const FAttributeKey& GetNodeSpecializeTypeBaseKey();`
- L23 _public prototype_ `static const FAttributeKey& GetMaterialDependencyUidsBaseKey();`
- L24 _public prototype_ `static const FString& GetMeshToGlobalBindPoseReferencesString();`
- L25 _public prototype_ `static const FString& GetSlotMaterialDependenciesString();`
- L26 _public prototype_ `static const FString& GetMorphTargetCurveWeightsKey();`
- L27 _public prototype_ `static const FString& GetLayerNamesKey();`
- L28 _public prototype_ `static const FString& GetTagsKey();`
- L29 _public prototype_ `static const FString& GetCurveAnimationTypesKey();`
- L30 _public prototype_ `static const FString& GetComponentUidsKey();`
- L33 _public prototype_ `static const FString& GetJointSpecializeTypeString();` — `UE_DEPRECATED(5.8, "Use typed class UInterchangeJointNode instead")`
- L36 _public prototype_ `static const FString& GetLodGroupSpecializeTypeString();` — `UE_DEPRECATED(5.8, "Use UInterchangeMeshLODContainerNode class instead")`

#### class `UInterchangeSceneNode`  
`class UInterchangeSceneNode : public UInterchangeBaseNode`  
_L47-381_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: The scene node represents a transform node in the scene. Scene nodes can have user-defined attributes. Use UInterchangeUserDefinedAttributesAPI to get and set user-defined attribute data.
- L52 _public prototype_ `UInterchangeSceneNode();`
- L57 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SlotMaterialDependencies on load.
- L70 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L73 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L75 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L80 _public prototype_ `virtual FName GetIconName() const override;` — Icon names are created by adding "InterchangeIcon_" in front of the specialized type. If there is no special type, the function will return NAME_None, which will use the default icon.
- L83 _public prototype_ `bool IsSpecializedTypeContains(const FString& SpecializedType) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")`
- L87 _public prototype_ `int32 GetSpecializedTypeCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Get the specialized type this scene node represents (for example, Joint or LODGroup).
- L90 _public prototype_ `void GetSpecializedType(const int32 Index, FString& OutSpecializedType) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")`
- L93 _public prototype_ `void GetSpecializedTypes(TArray<FString>& OutSpecializedTypes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")`
- L96 _public prototype_ `bool AddSpecializedType(const FString& SpecializedType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")`
- L99 _public prototype_ `bool RemoveSpecializedType(const FString& SpecializedType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")`
- L103 _public prototype_ `bool GetCustomAssetInstanceUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Get which asset, if any, a scene node is instantiating. Return false if the Attribute was not set previously.
- L107 _public prototype_ `bool SetCustomAssetInstanceUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Add an asset for this scene node to instantiate.
- L115 _public prototype_ `bool GetCustomLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Get the default scene node local transform. The default transform is the local transform of the node (no bind pose, no time evaluation).
- L122 _public prototype_ `bool SetCustomLocalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Set the default scene node local transform. The default transform is the local transform of the node (no bind pose, no time evaluation).
- L125 _public prototype_ `bool SetCustomLocalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue, bool bResetCache);` — `UE_DEPRECATED(5.8, "Use the overload without the bResetCache parameter; it is no longer needed.")`
- L129 _public prototype_ `bool GetCustomGlobalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Get the default scene node global transform. This value is computed from the local transforms of all parent scene nodes.
- L132 _public prototype_ `bool GetCustomGlobalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue, bool bForceRecache) const;` — `UE_DEPRECATED(5.8, "Use the overload without the bForceRecache parameter; it is no longer needed.")`
- L137 _public prototype_ `bool GetCustomGeometricTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Get the geometric offset. Any mesh attached to this scene node will be offset using this transform.
- L141 _public prototype_ `bool SetCustomGeometricTransform(const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Set the geometric offset. Any mesh attached to this scene node will be offset using this transform.
- L145 _public prototype_ `bool GetCustomPivotNodeTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Get the node pivot geometric offset.
- L149 _public prototype_ `bool SetCustomPivotNodeTransform(const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Set the node pivot geometric offset.
- L153 _public prototype_ `bool GetCustomComponentVisibility(bool& bOutIsVisible) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Gets whether components spawned from this node should be visible
- L157 _public prototype_ `bool SetCustomComponentVisibility(bool bInIsVisible);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Sets whether components spawned from this node should be visible
- L161 _public prototype_ `bool GetCustomActorVisibility(bool& bOutIsVisible) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Gets whether actors spawned from this node should be visible
- L165 _public prototype_ `bool SetCustomActorVisibility(bool bInIsVisible);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Sets whether actors spawned from this node should be visible
- L168 _public prototype_ `static void ResetAllGlobalTransformCaches(const UInterchangeBaseNodeContainer* BaseNodeContainer);` — This static function ensures all the global transform caches are reset for all the UInterchangeSceneNode nodes in the UInterchangeBaseNodeContainer.
- L171 _public prototype_ `static void ResetGlobalTransformCachesOfNodeAndAllChildren(const UInterchangeBaseNodeContainer* BaseNodeContainer, const UInterchangeBaseNode* ParentNode);` — This static function ensures all the global transform caches are reset for all the UInterchangeSceneNode nodes children in the UInterchangeBaseNodeContainer.
- L177 _public prototype_ `void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Meshes")` — Retrieve the correspondence table between slot names and assigned materials for this object.
- L183 _public prototype_ `bool GetSlotMaterialDependencyUid(const FString& SlotName, FString& OutMaterialDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Meshes")` — Retrieve the Material dependency for a given slot of this object.
- L189 _public prototype_ `bool SetSlotMaterialDependencyUid(const FString& SlotName, const FString& MaterialDependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Meshes")` — Add the specified Material dependency to a specific slot name of this object.
- L195 _public prototype_ `bool RemoveSlotMaterialDependencyUid(const FString& SlotName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Meshes")` — Remove the Material dependency associated with the given slot name from this object.
- L199 _public prototype_ `bool SetMorphTargetCurveWeight(const FString& MorphTargetName, const float& Weight);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set MorphTarget with given weight.
- L203 _public prototype_ `void GetMorphTargetCurveWeights(TMap<FString, float>& OutMorphTargetCurveWeights) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Get MorphTargets and their weights.
- L208 _public prototype_ `bool SetCustomAnimationAssetUidToPlay(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the Animation Asset To Play by this Scene Node. Only relevant for SkeletalMeshActors (that is, SceneNodes that are instantiating Skeletal Meshes).
- L211 _public prototype_ `bool GetCustomAnimationAssetUidToPlay(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Get the Animation Asset To Play by this Scene Node.
- L214 _public prototype_ `void GetLayerNames(TArray<FString>& OutLayerNames) const;` — Gets the LayerNames that this SceneNode (Actor) is supposed to be part of.
- L217 _public prototype_ `bool AddLayerName(const FString& LayerName);` — Add LayerName that this SceneNode (Actor) is supposed to be part of.
- L220 _public prototype_ `bool RemoveLayerName(const FString& LayerName);` — Remove LayerName that this SceneNode (Actor) is supposed to be part of.
- L223 _public prototype_ `void GetTags(TArray<FString>& OutTags) const;` — Gets the Tags that this SceneNode (Actor) is supposed to have.
- L226 _public prototype_ `bool AddTag(const FString& Tag);` — Add Tag that this SceneNode (Actor) is supposed to have.
- L229 _public prototype_ `bool RemoveTag(const FString& Tag);` — Remove Tag that this SceneNode (Actor) is supposed to have.
- L233 _public prototype_ `bool SetAnimationCurveTypeForCurveName(const FString& CurveName, const EInterchangeAnimationPayLoadType& AnimationCurveType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Sets the Animation Curve Type for the given CurveName (StepCurve or Curve). (Mostly used for tracking Custom Attributes' Animation Types)
- L237 _public prototype_ `bool GetAnimationCurveTypeForCurveName(const FString& CurveName, EInterchangeAnimationPayLoadType& OutCurveAnimationType) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint")` — Gets the Animation Curve Type for the given CurveName.
- L240 _public prototype_ `bool AddComponentUid(const FString& ComponentUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L243 _public prototype_ `void GetComponentUids(TArray<FString>& OutComponentUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L247 _public prototype_ `bool SetCustomIsSceneRoot(const bool& IsSceneRoot);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")` — Sets IsSceneRootNode, which indicates if the SceneNode is a Scene Root Node.
- L251 _public prototype_ `bool GetCustomIsSceneRoot(bool& IsSceneRoot) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")` — Gets IsSceneRoot, which indicates if the SceneNode is a Scene Root Node.
- L255 _public prototype_ `bool GetCustomDoNotInstantiateInLevel(bool& bOutDoNotInstantiateInLevel) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Gets whether the scene node was part of a Named LOD Group, indicating if it should show up in the scene or not.
- L259 _public prototype_ `bool SetCustomDoNotInstantiateInLevel(bool bInDoNotInstantiateInLevel);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Scene")` — Sets whether the scene node was part of a Named LOD Group, indicating if it should show up in the scene or not.
- L267 _public prototype_ `bool GetCustomBindPoseLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::GetBindPoseLocalTransform")`
- L271 _public prototype_ `bool SetCustomBindPoseLocalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue, bool bResetCache = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::SetBindPoseLocalTransform")`
- L275 _public prototype_ `bool GetCustomBindPoseGlobalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue, bool bForceRecache = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::GetBindPoseGlobalTransform")`
- L279 _public prototype_ `bool GetCustomTimeZeroLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::GetTimeZeroLocalTransform")`
- L283 _public prototype_ `bool SetCustomTimeZeroLocalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue, bool bResetCache = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::SetTimeZeroLocalTransform")`
- L287 _public prototype_ `bool GetCustomTimeZeroGlobalTransform(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue, bool bForceRecache = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::GetTimeZeroGlobalTransform")`
- L291 _public prototype_ `void SetGlobalBindPoseReferenceForMeshUIDs(const TMap<FString, FMatrix>& GlobalBindPoseReferenceForMeshUIDs);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::SetMeshUIDToGlobalBindPoseReferenceMap")`
- L295 _public prototype_ `bool GetGlobalBindPoseReferenceForMeshUID(const FString& MeshUID, FMatrix& GlobalBindPoseReference) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::GetGlobalBindPoseReferenceFromMeshUID")`
- L299 _public prototype_ `bool SetCustomHasBindPose(const bool& bHasBindPose);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::SetHasInvalidBindPose")`
- L303 _public prototype_ `bool GetCustomHasBindPose(bool& bHasBindPose) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::SetHasInvalidBindPose")`
- L307 _public prototype_ `bool SetCustomGlobalMatrixForT0Rebinding(const FMatrix& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::SetGlobalMatrixForT0Rebinding")`
- L311 _public prototype_ `bool GetCustomGlobalMatrixForT0Rebinding(FMatrix& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Joint", meta = (DeprecatedFunction, DeprecationMessage = "Moved to UInterchangeJointNode."))` — `UE_DEPRECATED(5.8, "This function moved to UInterchangeJointNode::GetGlobalMatrixForT0Rebinding")`
- L318 _protected prototype_ `bool GetGlobalTransformWithOffsetInternal(const UE::Interchange::FAttributeKey LocalTransformKey , const UInterchangeBaseNodeContainer* BaseNodeContainer , const FTransform& GlobalOffsetTransform , FTransform& OutAttributeValue) const;`
- L323 _protected prototype_ `void ResetGlobalTransformCacheInternal(const UInterchangeBaseNodeContainer* BaseNodeContainer, const UE::Interchange::FAttributeKey LocalTransformKey) const;`
- L326 _private prototype_ `bool GetGlobalTransformInternal(const UE::Interchange::FAttributeKey LocalTransformKey , const UInterchangeBaseNodeContainer* BaseNodeContainer , FTransform& OutAttributeValue) const;`
- L331 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(LocalTransform);` — Scene node default local transforms.
- L334 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GeometricTransform);` — A scene node can have a transform apply to the mesh it reference.
- L337 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(PivotNodeTransform);` — A scene node can have a pivot transform apply to the mesh it reference (use this pivot only if you are not baking the vertices of the mesh).
- L340 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ComponentVisibility);` — A scene node can be invisible, but still be imported. We have two of these to match how you can separately animate actor and component visibility
- L341 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ActorVisibility);`
- L344 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AssetInstanceUid);` — A scene node can reference an asset. Asset can be Mesh, Light, camera...
- L347 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> NodeSpecializeTypes;` — A scene node can represent many special types
- L350 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SlotMaterialDependencies;` — A scene node can have is own set of materials for the mesh it reference.
- L353 _private member_ `UE::Interchange::TMapAttributeHelper<FString, float> MorphTargetCurveWeights;` — A scene node can have different MorphTarget curve settings:
- L356 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> LayerNames;` — A scene node can be part of multiple Layers.
- L359 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> Tags;` — A scene node can have multiple Tags.
- L362 _private member_ `UE::Interchange::TMapAttributeHelper<FString, EInterchangeAnimationPayLoadType> CurveAnimationTypes;` — A scene node can have Attributes defining Curves. (Mostly used for tracking Custom Attributes' Animation Types).
- L365 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> ComponentUids;` — A scene node can represent many special types
- L368 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AnimationAssetUidToPlay);` — A scene node can reference an animation asset on top of base asset:
- L371 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(IsSceneRoot);` — For storing flag in case SceneNode is a Scene Root Node.
- L374 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(DoNotInstantiateInLevel);` — For storing flag in case SceneNode is part of a Named LOD Group.
- L380 _protected member_ `mutable TMap<UE::Interchange::FAttributeKey, FTransform> GlobalTransformCache;` — Depending on its usage, A SceneNode can be part of multiple spaces (transform, time zero, and bind pose) We want to be able to cache any global transform calculated for any space

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGENODES_API`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeShaderGraphNode.h` (Public)


#### class `UInterchangeShaderPortsAPI`  
`class UInterchangeShaderPortsAPI : public UObject`  
_L19-160_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Shader Ports API manages a set of inputs and outputs attributes. This API can be used over any InterchangeBaseNode that wants to support shader ports as attributes.
- L28 _public prototype_ `static FString MakeInputConnectionKey(const FString& InputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Makes an attribute key to represent a node being connected to an input (that is, Inputs:InputName:Connect).
- L34 _public prototype_ `static FString MakeInputValueKey(const FString& InputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Makes an attribute key to represent a value being given to an input (that is, Inputs:InputName:Value).
- L41 _public prototype_ `static FString MakeInputParameterKey(const FString& InputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Makes an attribute key to represent a parameter being given to an input (that is, Inputs:InputName:Parameter). This is more relevant to Materials, but could be used to differentiate between constant values and parameters.
- L47 _public prototype_ `static FString MakeInputName(const FString& InputKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — From an attribute key associated with an input (that is, Inputs:InputName:Value), retrieves the input name.
- L53 _public prototype_ `static bool IsAnInput(const FString& AttributeKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Returns true if the attribute key is associated with an input (starts with "Inputs:").
- L59 _public prototype_ `static bool IsAParameter(const FString& AttributeKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Returns true if the attribute key is an input that represents parameters (ends with ":Parameter").
- L65 _public prototype_ `static bool HasInput(const UInterchangeBaseNode* InterchangeNode, const FName& InInputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Checks whether a particular input exists on a given node.
- L71 _public prototype_ `static bool HasParameter(const UInterchangeBaseNode* InterchangeNode, const FName& InInputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Checks whether a particular input exists as a parameter on a given node.
- L77 _public prototype_ `static void GatherInputs(const UInterchangeBaseNode* InterchangeNode, TArray<FString>& OutInputNames);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Retrieves the names of all the inputs for a given node.
- L87 _public prototype_ `static bool ConnectDefaultOuputToInput(UInterchangeBaseNode* InterchangeNode, const FString& InputName, const FString& ExpressionUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Adds an input connection attribute. @param InterchangeNode	The node to create the input on. @param InputName			The name to give to the input. @param ExpressionUid		The unique ID of the node to connect to the input. @return					True if the input connection was successfully added to the node.
- L96 _public prototype_ `static bool DisconnectInput(UInterchangeBaseNode* InterchangeNode, const FString& InputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Remove an input connection attribute. @param InterchangeNode	The node to disconnect the input from. @param InputName			The name of the input to disconnect. @return					True if the input connection was successfully removed from the node.
- L107 _public prototype_ `static bool DisconnectInputFromOutputNode(UInterchangeBaseNode* InterchangeNode, const FString& InputName, FString& OutExpressionUid, FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Remove an input connection attribute by also retrieving the node unique id and the output name connected to the given input, if any. @param InterchangeNode	The node to disconnect the input from. @param InputName			The name of the input to disconnect. @param OutExpressionUid  The Uid of the node that was disconnected from the input. @param OutputName        The name of node output. @return					True if the input connection was successfully removed from the node.
- L118 _public prototype_ `static bool ConnectOuputToInputByName(UInterchangeBaseNode* InterchangeNode, const FString& InputName, const FString& ExpressionUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Adds an input connection attribute. @param InterchangeNode	The node to create the input on. @param InputName			The name to give to the input. @param ExpressionUid		The unique ID of the node to connect to the input. @param OutputName		The name of the output from ExpressionUid to connect to the input. @return					True if the input connection was successfully added to the node.
- L120 _public function_ `static bool ConnectOuputToInput(UInterchangeBaseNode* InterchangeNode, const FString& InputName, const FString& ExpressionUid, const FString& OutputName)` — `UE_DEPRECATED(5.3, "This function is replace by ConnectOuputToInputByName.")`
- L136 _public prototype_ `static bool ConnectOuputToInputByIndex(UInterchangeBaseNode* InterchangeNode, const FString& InputName, const FString& ExpressionUid, int32 OutputIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Adds an input connection attribute. @param InterchangeNode	The node to create the input on. @param InputName			The name to give to the input. @param ExpressionUid		The unique ID of the node to connect to the input. @param OutputIndex		The index of the output from ExpressionUid to connect to the input. @return					True if the input connection was successfully added to the node. OutputIndex is encoded in a string in the following pattern: ExpressionUid:OutputByIndex:FString::FromInt(OutputIndex) The index should be retrieved using UInterchangeShaderPortsAPI::GetOutputIndexFromName().
- L142 _public prototype_ `static bool GetInputConnection(const UInterchangeBaseNode* InterchangeNode, const FString& InputName, FString& OutExpressionUid, FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Retrieves the node unique id and the output name connected to a given input, if any.
- L147 _public prototype_ `static UE::Interchange::EAttributeTypes GetInputType(const UInterchangeBaseNode* InterchangeNode, const FString& InputName, bool bIsAParameter = false);` — For an input with a value, returns the type of the stored value.
- L152 _public prototype_ `static int32 GetOutputIndexFromName(const FString& OutputName);` — Returns INDEX_NONE if OutputName is not an index.
- L155 _private member_ `static const TCHAR* InputPrefix;`
- L156 _private member_ `static const TCHAR* InputSeparator;`
- L157 _private member_ `static const TCHAR* OutputByIndex;`
- L159 _private member_ `static const TCHAR* ParameterSuffix;`

#### class `UInterchangeShaderNode`  
`class UInterchangeShaderNode : public UInterchangeBaseNode`  
_L166-222_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: A shader node is a named set of inputs and outputs. It can be connected to other shader nodes and finally to a shader graph input.
- L174 _public prototype_ `static FString MakeNodeUid(const FStringView NodeName, const FStringView ParentNodeUid);` — Build and return a UID name for a shader node.
- L179 _public prototype_ `static UInterchangeShaderNode* Create(UInterchangeBaseNodeContainer* NodeContainer, const FStringView NodeName, const FStringView ParentNodeUid);` — Creates a new UInterchangeShaderNode and adds it to NodeContainer as a translated node.
- L181 _public prototype_ `virtual FString GetTypeName() const override;`
- L191 _public prototype_ `bool AddFloatInput(const FString& InputName, const float& AttributeValue, bool bIsAParameter = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the Float Attribute on the Shader Node. If bIsAParameter is set to true, it would be treated as a ScalarParameter when the Material Pipeline creates the materials. Otherwise it would be a constant expression in the shader graph. Note: It is assumed that the input name would be the parameter name when bIsAParameter is true.
- L199 _public prototype_ `bool AddLinearColorInput(const FString& InputName, const FLinearColor& AttributeValue, bool bIsAParameter = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the Linear Color Attribute on the Shader Node. If bIsAParameter is set to true, it would be treated as a VectorParameter when the Material Pipeline creates the materials. Otherwise it would be a constant 3 vector expression in the shader graph. Note: It is assumed that the input name would be the parameter name when bIsAParameter is true.
- L207 _public prototype_ `bool AddStringInput(const FString& InputName, const FString& AttributeValue, bool bIsAParameter = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the String Attribute on the Shader Node. If bIsAParameter is set to true, it would be treated as a overridable Texture or else it should be treated as a LUT Texture. Note: It is assumed that the input name would be the parameter name when bIsAParameter is true.
- L211 _public prototype_ `bool GetCustomShaderType(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L218 _public prototype_ `bool SetCustomShaderType(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets which type of shader this nodes represents. Can be arbitrary or one of the predefined shader types. The material pipeline handling the shader node should be aware of the shader type that is being set here.
- L221 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomShaderTypeKey = UE::Interchange::FAttributeKey(TEXT("Shad`

#### class `UInterchangeFunctionCallShaderNode`  
`class UInterchangeFunctionCallShaderNode : public UInterchangeShaderNode`  
_L228-247_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeShaderNode`
- desc: A function call shader node has a named set of inputs and outputs which corresponds to the inputs and outputs of the shader function it instances.
- L233 _public prototype_ `virtual FString GetTypeName() const override;`
- L237 _public prototype_ `bool GetCustomMaterialFunction(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L243 _public prototype_ `bool SetCustomMaterialFunction(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the unique id of the material function referenced by the function call expression.
- L246 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomMaterialFunctionKey = UE::Interchange::FAttributeKey(TEXT("Mate`

#### class `UInterchangeShaderGraphNode`  
`class UInterchangeShaderGraphNode : public UInterchangeShaderNode`  
_L253-352_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeShaderNode`
- desc: A shader graph has its own set of inputs on which shader nodes can be connected to.
- L261 _public prototype_ `static FString MakeNodeUid(const FStringView NodeName);` — Build and return a UID name for a shader graph node.
- L266 _public prototype_ `static UInterchangeShaderGraphNode* Create(UInterchangeBaseNodeContainer* NodeContainer, const FStringView NodeName);` — Create a new UInterchangeShaderGraphNode and add it to NodeContainer as a translated node.
- L271 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L275 _public prototype_ `bool GetCustomTwoSided(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L281 _public prototype_ `bool SetCustomTwoSided(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set if this shader graph should be rendered two-sided or not. Defaults to off.
- L287 _public prototype_ `bool GetCustomTwoSidedTransmission(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Forces two-sided even for Transmission materials.
- L290 _public prototype_ `bool SetCustomTwoSidedTransmission(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L293 _public prototype_ `bool GetCustomOpacityMaskClipValue(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L299 _public prototype_ `bool SetCustomOpacityMaskClipValue(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — The shader is transparent if its alpha value is lower than the clip value, or opaque if it is higher.
- L302 _public prototype_ `bool GetCustomIsAShaderFunction(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L308 _public prototype_ `bool SetCustomIsAShaderFunction(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set whether this shader graph should be considered as a material (false), or a material function (true).
- L311 _public prototype_ `bool GetCustomScreenSpaceReflections(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L314 _public prototype_ `bool SetCustomScreenSpaceReflections(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L320 _public prototype_ `bool GetCustomBlendMode(int& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the Blend Mode using EBlendMode to avoid a dependency on the Engine.
- L323 _public prototype_ `bool SetCustomBlendMode(int AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L329 _public prototype_ `bool GetCustomDisplacementCenterMode(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the center of the displacement
- L332 _public prototype_ `bool SetCustomDisplacementCenterMode(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L338 _public prototype_ `bool GetCustomDisplacementMagnitude(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the magnitude of the displacement
- L341 _public prototype_ `bool SetCustomDisplacementMagnitude(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeSpecularProfileNode.h` (Public)


#### class `UInterchangeSpecularProfileNode`  
`class UInterchangeSpecularProfileNode : public UInterchangeBaseNode`  
_L12-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- L21 _public prototype_ `static FString MakeNodeUid(const FStringView& NodeName);` — Build and return a UID name for a specular profile node.
- L26 _public prototype_ `static UInterchangeSpecularProfileNode* Create(UInterchangeBaseNodeContainer* NodeContainer, const FStringView& NodeName);` — Create a new UInterchangeSpecularProfileNode and add it to NodeContainer as a translated node.
- L33 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L37 _public prototype_ `bool SetCustomFormat(uint8 Format);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpecularProfile")` — Set/Get the format based on ESpecularProfileFormat
- L40 _public prototype_ `bool GetCustomFormat(uint8& Format) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpecularProfile")`
- L43 _public prototype_ `bool GetCustomTexture(FString& TextureUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpecularProfile")`
- L46 _public prototype_ `bool SetCustomTexture(const FString& TextureUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpecularProfile")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTexture2DArrayNode.h` (Public)


#### class `UInterchangeTexture2DArrayNode`  
`class UInterchangeTexture2DArrayNode : public UInterchangeTextureNode`  
_L14-28_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureNode`
- L23 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTexture2DNode.h` (Public)


#### struct `UE::Interchange::FTexture2DNodeStaticData`  
`struct FTexture2DNodeStaticData : public FBaseNodeStaticData`  
_L15-22_
- inherits: `FBaseNodeStaticData`
- L17 _public function_ `static const FAttributeKey& GetBaseSourceBlocksKey()`

#### class `UInterchangeTexture2DNode`  
`class UInterchangeTexture2DNode : public UInterchangeTextureNode`  
_L26-158_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeTextureNode`
- L35 _public prototype_ `static FString MakeNodeUid(const FStringView NodeName);` — Build and return a UID name for a texture 2D node.
- L40 _public prototype_ `static UInterchangeTexture2DNode* Create(UInterchangeBaseNodeContainer* NodeContainer, const FString& TextureNodeUid, const FString& TextureNodeName);` — Creates a new UInterchangeTexture2DNode and adds it to NodeContainer as a translated node.
- L42 _public function_ `virtual void PostInitProperties()`
- L51 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L60 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SourceBlocks on load.
- L79 _public function_ `TMap<int32, FString> GetSourceBlocks() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Get the source blocks for the texture. If the map is empty, the texture is imported as a normal texture using the payload key.
- L91 _public function_ `void SetSourceBlocks(TMap<int32, FString>&& InSourceBlocks)` — Set the source blocks for the texture. Using this suggests to the pipeline to consider this texture as a UDIM. The pipeline can choose whether to pass these blocks to the texture factory node. @param InSourceBlocks The blocks and their source image that compose the whole texture. The textures must be of the same format and use the same pixel format. The first block in the map is used to determine the accepted texture format and pixel format.
- L104 _public function_ `void SetSourceBlocks(const TMap<int32, FString>& InSourceBlocks)` — Set the source blocks for the texture. Using this suggests to the pipeline to consider this texture as a UDIM. The pipeline can choose whether to pass these blocks to the texture factory node. @param InSourceBlocks The blocks and their source image that compose the whole texture. The textures must be of the same format and use the same pixel format. The first block in the map is used to determine the accepted texture format and pixel format.
- L114 _protected member_ `UE::Interchange::TMapAttributeHelper<int32, FString> SourceBlocks;`
- L119 _public function_ `bool SetCustomWrapU(const EInterchangeTextureWrapMode& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L125 _public function_ `bool GetCustomWrapU(EInterchangeTextureWrapMode& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L131 _public function_ `bool SetCustomWrapV(const EInterchangeTextureWrapMode& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L137 _public function_ `bool GetCustomWrapV(EInterchangeTextureWrapMode& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L143 _public function_ `bool SetForceLongLatCubemap(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L149 _public function_ `bool GetForceLongLatCubemap(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L155 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(WrapU);`
- L156 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(WrapV);`
- L157 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ForceLongLatCubemap);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTextureBlurNode.h` (Public)


#### class `UInterchangeTextureBlurNode`  
`class UInterchangeTextureBlurNode : public UInterchangeTexture2DNode`  
_L14-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTexture2DNode`
- L23 _public prototype_ `static FString MakeNodeUid(const FStringView NodeName);` — Build and return a UID name for a texture 2D node.
- L28 _public prototype_ `static UInterchangeTextureBlurNode* Create(UInterchangeBaseNodeContainer* NodeContainer, const FStringView TextureNodeName);` — Creates a new UInterchangeTexture2DNode and adds it to NodeContainer as a translated node.
- L33 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTextureCubeArrayNode.h` (Public)


#### class `UInterchangeTextureCubeArrayNode`  
`class UInterchangeTextureCubeArrayNode : public UInterchangeTextureNode`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureNode`
- L21 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTextureCubeNode.h` (Public)


#### class `UInterchangeTextureCubeNode`  
`class UInterchangeTextureCubeNode : public UInterchangeTextureNode`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureNode`
- L21 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTextureLightProfileNode.h` (Public)


#### class `UInterchangeTextureLightProfileNode`  
`class UInterchangeTextureLightProfileNode : public UInterchangeTextureNode`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureNode`
- L21 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeTextureNode.h` (Public)


#### struct `UE::Interchange::FTextureNodeStaticData`  
`struct FTextureNodeStaticData : public FBaseNodeStaticData`  
_L15-22_
- inherits: `FBaseNodeStaticData`
- L17 _public function_ `static const FAttributeKey& PayloadSourceFileKey()`

#### enum `EInterchangeTextureWrapMode`  
`enum class EInterchangeTextureWrapMode : uint8`  
_L27-32_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Wrap`
- L30 _public enumerator_ `Clamp`
- L31 _public enumerator_ `Mirror`

#### enum `EInterchangeTextureFilterMode`  
`enum class EInterchangeTextureFilterMode : uint8`  
_L35-42_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `Nearest`
- L38 _public enumerator_ `Bilinear`
- L39 _public enumerator_ `Trilinear`
- L41 _public enumerator_ `Default` — Use setting from the Texture Group.

#### enum `EInterchangeTextureColorSpace`  
`enum class EInterchangeTextureColorSpace : uint8`  
_L45-63_
- reflection: `UENUM(BlueprintType)`
- L47 _public enumerator_ `TCS_None = 0 UMETA(DisplayName = "None", ToolTip = "No explicit color space definition.")`
- L48 _public enumerator_ `TCS_sRGB = 1 UMETA(DisplayName = "sRGB / Rec709", ToolTip = "sRGB / Rec709 (BT.709) color primaries, with D65 white point.")`
- L49 _public enumerator_ `TCS_Rec2020 = 2 UMETA(DisplayName = "Rec2020", ToolTip = "Rec2020 (BT.2020) primaries with D65 white point.")`
- L50 _public enumerator_ `TCS_ACESAP0 = 3 UMETA(DIsplayName = "ACES AP0", ToolTip = "ACES AP0 wide gamut primaries, with D60 white point.")`
- L51 _public enumerator_ `TCS_ACESAP1 = 4 UMETA(DIsplayName = "ACES AP1 / ACEScg", ToolTip = "ACES AP1 / ACEScg wide gamut primaries, with D60 white point.")`
- L52 _public enumerator_ `TCS_P3DCI = 5 UMETA(DisplayName = "P3DCI", ToolTip = "P3 (Theater) primaries, with DCI Calibration white point.")`
- L53 _public enumerator_ `TCS_P3D65 = 6 UMETA(DisplayName = "P3D65", ToolTip = "P3 (Display) primaries, with D65 white point.")`
- L54 _public enumerator_ `TCS_REDWideGamut = 7 UMETA(DisplayName = "RED Wide Gamut", ToolTip = "RED Wide Gamut primaries, with D65 white point.")`
- L55 _public enumerator_ `TCS_SonySGamut3 = 8 UMETA(DisplayName = "Sony S-Gamut3", ToolTip = "Sony S-Gamut/S-Gamut3 primaries, with D65 white point.")`
- L56 _public enumerator_ `TCS_SonySGamut3Cine = 9 UMETA(DisplayName = "Sony S-Gamut3 Cine", ToolTip = "Sony S-Gamut3 Cine primaries, with D65 white point.")`
- L57 _public enumerator_ `TCS_AlexaWideGamut = 10 UMETA(DisplayName = "Alexa Wide Gamut", ToolTip = "Alexa Wide Gamut primaries, with D65 white point.")`
- L58 _public enumerator_ `TCS_CanonCinemaGamut = 11 UMETA(DisplayName = "Canon Cinema Gamut", ToolTip = "Canon Cinema Gamut primaries, with D65 white point.")`
- L59 _public enumerator_ `TCS_GoProProtuneNative = 12 UMETA(DisplayName = "GoPro Protune Native", ToolTip = "GoPro Protune Native primaries, with D65 white point.")`
- L60 _public enumerator_ `TCS_PanasonicVGamut = 13 UMETA(DisplayName = "Panasonic V-Gamut", ToolTip = "Panasonic V-Gamut primaries, with D65 white point.")`
- L61 _public enumerator_ `TCS_Custom = 99 UMETA(DisplayName = "Custom", ToolTip = "User defined color space and white point.")`
- L62 _public enumerator_ `TCS_MAX`

#### class `UInterchangeTextureNode`  
`class UInterchangeTextureNode : public UInterchangeBaseNode`  
_L66-201_
- reflection: `UCLASS(BlueprintType, Abstract, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- L74 _public function_ `static FString MakeNodeUid(const FStringView NodeName)` — Build and return a UID name for a texture node.
- L82 _public prototype_ `static bool ExtractNodeUidAndNameFromFilePath(const FStringView TextureFilePath, FString& OutNodeUid, FString& OutNodeName);` — Utility function to build a unique and deterministic UID and Name for a given texture file path.
- L87 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L93 _public function_ `virtual FName GetIconName() const override`
- L99 _public function_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override`
- L110 _public function_ `virtual FGuid GetHash() const override`
- L116 _public function_ `virtual const TOptional<FString> GetPayLoadKey() const` — Texture node Interface Begin
- L138 _public function_ `virtual void SetPayLoadKey(const FString& PayloadKey)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L148 _public function_ `bool GetCustomSRGB(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L154 _public function_ `bool SetCustomSRGB(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L160 _public function_ `bool GetCustombFlipGreenChannel(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L166 _public function_ `bool SetCustombFlipGreenChannel(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L172 _public function_ `bool GetCustomFilter(EInterchangeTextureFilterMode& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L178 _public function_ `bool SetCustomFilter(const EInterchangeTextureFilterMode& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L184 _public function_ `bool GetCustomColorSpace(EInterchangeTextureColorSpace& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L190 _public function_ `bool SetCustomColorSpace(const EInterchangeTextureColorSpace& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeVariantSetNode.h` (Public)


#### class `UInterchangeVariantSetNode`  
`class UInterchangeVariantSetNode : public UInterchangeBaseNode`  
_L16-95_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: Class to represent a set of variants.
- L20 _private prototype_ `UInterchangeVariantSetNode();`
- L23 _public function_ `static FStringView StaticAssetTypeName()`
- L31 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L41 _public prototype_ `bool GetCustomDisplayText(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | VariantSet")` — Retrieve the text that is displayed in the UI for this VariantSet.
- L47 _public prototype_ `bool SetCustomDisplayText(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | VariantSet")` — Set the text to be displayed in the UI for this VariantSet.
- L53 _public prototype_ `bool GetCustomVariantsPayloadKey(FString& PayloadKey) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | VariantSet")` — Get the payload key needed to retrieve the variants for this VariantSet.
- L59 _public prototype_ `bool SetCustomVariantsPayloadKey(const FString& PayloadKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | VariantSet")` — Set the payload key needed to retrieve the variants for this VariantSet.
- L65 _public prototype_ `int32 GetCustomDependencyUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Retrieve the number of translated node's unique IDs for this VariantSet.
- L71 _public prototype_ `void GetCustomDependencyUids(TArray<FString>& OutDependencyUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Retrieve all the translated node's unique IDs for this VariantSet.
- L77 _public prototype_ `void GetCustomDependencyUid(const int32 Index, FString& OutDependencyUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Retrieve the specified translated node's unique ID for this VariantSet.
- L83 _public prototype_ `bool AddCustomDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Add the specified translated node's unique ID to this VariantSet.
- L89 _public prototype_ `bool RemoveCustomDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Remove the specified translated node's unique ID from this VariantSet.
- L92 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDisplayTextKey = UE::Interchange::FAttributeKey(TEXT("Disp`
- L93 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomVariantsPayloadKey = UE::Interchange::FAttributeKey(TEXT("Vari`
- L94 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> CustomDependencyUids;`

#### class `UInterchangeSceneVariantSetsNode`  
`class UInterchangeSceneVariantSetsNode : public UInterchangeBaseNode`  
_L101-154_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: Class to represent a set of VariantSet nodes
- L105 _private prototype_ `UInterchangeSceneVariantSetsNode();`
- L108 _public function_ `static FStringView StaticAssetTypeName()`
- L116 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L126 _public prototype_ `int32 GetCustomVariantSetUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Retrieve the number of VariantSets for this object.
- L132 _public prototype_ `void GetCustomVariantSetUids(TArray<FString>& OutVariantUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Retrieve all the VariantSets' unique ids for this object.
- L138 _public prototype_ `void GetCustomVariantSetUid(const int32 Index, FString& OutVariantUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Retrieve the specified VariantSet's unique id for this object.
- L144 _public prototype_ `bool AddCustomVariantSetUid(const FString& VariantUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Add the specified VariantSet's unique id to this object.
- L150 _public prototype_ `bool RemoveCustomVariantSetUid(const FString& VariantUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSet")` — Remove the specified VariantSet's unique id from this object.
- L153 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> CustomVariantSetUids;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeVolumeNode.h` (Public)


#### struct `UE::Interchange::FInterchangeVolumeNodeStaticData`  
`struct FInterchangeVolumeNodeStaticData : public FBaseNodeStaticData`  
_L14-18_
- inherits: `FBaseNodeStaticData`
- L16 _public prototype_ `static const FAttributeKey& GetCustomGridDependeciesBaseKey();`
- L17 _public prototype_ `static const FAttributeKey& GetCustomFrameIndicesInAnimationBaseKey();`

#### class `UInterchangeVolumeNode`  
`class UInterchangeVolumeNode : public UInterchangeBaseNode`  
_L26-116_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: Represents a file that contains volume data in the form of (potentially multiple) grids, which are represented as UInterchangeVolumeGridNode dependencies
- L31 _public prototype_ `UInterchangeVolumeNode();`
- L33 _public prototype_ `virtual FString GetTypeName() const override;`
- L43 _public prototype_ `bool GetCustomFileName(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the filename of the file with volume data (e.g. "C:/MyFolder/File.vdb"). This is stored on the translated node as well as the source data, as a volume import may discover other additional files in order to handle animated volume imports.
- L52 _public prototype_ `bool SetCustomFileName(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the filename of the file with volume data (e.g. "C:/MyFolder/File.vdb"). This is stored on the translated node as well as the source data, as a volume import may discover other additional files in order to handle animated volume imports.
- L59 _public prototype_ `int32 GetCustomGridDependeciesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the number of UInterchangeVolumeGridNodes declared as dependencies by this volume node (in other words, returns the number of volume grids contained in this file)
- L63 _public prototype_ `void GetCustomGridDependecies(TArray<FString>& OutDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the Node IDs of UInterchangeVolumeGridNodes declared as dependencies by this volume node
- L67 _public prototype_ `void GetCustomGridDependency(const int32 Index, FString& OutDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the Node ID of an UInterchangeVolumeGridNode dependency
- L71 _public prototype_ `bool AddCustomGridDependency(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the Node ID of an UInterchangeVolumeGridNode dependency
- L75 _public prototype_ `bool RemoveCustomGridDependency(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Removes the Node ID of an UInterchangeVolumeGridNode dependency
- L82 _public prototype_ `bool GetCustomAnimationID(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets an identifier that is shared by all volume nodes that correspond to the same animation (i.e. every volume node within the animation will have the same AnimationID)
- L89 _public prototype_ `bool SetCustomAnimationID(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets an identifier that is shared by all volume nodes that correspond to the same animation (i.e. every volume node within the animation will have the same AnimationID)
- L96 _public prototype_ `void GetCustomFrameIndicesInAnimation(TArray<int32>& OutAnimationIndices) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Get the frame indices for which this volume is displayed within the animation that it belongs to, if any (e.g. if this had [2, 3] then frames 2 and 3 of the animation with AnimationID should display this volume)
- L100 _public prototype_ `void GetCustomFrameIndexInAnimation(int32 IndexIndex, int32& OutIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets one of the frame indices for which this volume is displayed within the animation that it belongs to, if any
- L104 _public prototype_ `bool AddCustomFrameIndexInAnimation(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Adds a frame index for which this volume is displayed within the animation that it belongs to, if any
- L108 _public prototype_ `bool RemoveCustomFrameIndexInAnimation(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Removes a frame index for which this volume is displayed within the animation that it belongs to, if any
- L111 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FileName);`
- L112 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AnimationID);`
- L114 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> GridDependencies;`
- L115 _private member_ `UE::Interchange::TArrayAttributeHelper<int32> IndexInVolumeAnimation;`

#### enum `EVolumeGridElementType`  
`enum class EVolumeGridElementType : uint8`  
_L119-125_
- reflection: `UENUM(Blueprintable)`
- L121 _public enumerator_ `Unknown`
- L122 _public enumerator_ `Half`
- L123 _public enumerator_ `Float`
- L124 _public enumerator_ `Double`

#### class `UInterchangeVolumeGridNode`  
`class UInterchangeVolumeGridNode : public UInterchangeBaseNode`  
_L131-194_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseNode`
- desc: Represents a single grid (essentially a 3d texture) within a volumetric file
- L136 _public prototype_ `virtual FString GetTypeName() const override;`
- L141 _public prototype_ `bool GetCustomElementType(EVolumeGridElementType& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Gets the datatype of the value of each voxel in the grid
- L145 _public prototype_ `bool SetCustomElementType(const EVolumeGridElementType& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the datatype of the value of each voxel in the grid
- L149 _public prototype_ `bool GetCustomNumComponents(int32& NumComponents) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the number of components of each voxel of the grid (e.g. 3 components for a vector grid)
- L153 _public prototype_ `bool SetCustomNumComponents(const int32& NumComponents);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the number of components of each voxel of the grid (e.g. 3 components for a vector grid)
- L157 _public prototype_ `bool GetCustomGridTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the grid transform contained in the volume file
- L161 _public prototype_ `bool SetCustomGridTransform(const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the grid transform contained in the volume file
- L165 _public prototype_ `bool GetCustomGridActiveAABBMin(FIntVector& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the min X, Y and Z of the grid's active axis-aligned bounding box.
- L169 _public prototype_ `bool SetCustomGridActiveAABBMin(const FIntVector& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the min X, Y and Z of the grid's active axis-aligned bounding box.
- L173 _public prototype_ `bool GetCustomGridActiveAABBMax(FIntVector& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the max X, Y and Z of the grid's active axis-aligned bounding box.
- L177 _public prototype_ `bool SetCustomGridActiveAABBMax(const FIntVector& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the max X, Y and Z of the grid's active axis-aligned bounding box.
- L181 _public prototype_ `bool GetCustomGridActiveDimensions(FIntVector& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Gets the size of the grid, in voxels.
- L185 _public prototype_ `bool SetCustomGridActiveDimensions(const FIntVector& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Volume")` — Sets the size of the grid, in voxels.
- L188 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ElementType);`
- L189 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NumComponents);`
- L190 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GridTransform);`
- L191 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GridActiveAABBMin);`
- L192 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GridActiveAABBMax);`
- L193 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GridActiveDim);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGENODES_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Nodes/Public/InterchangeVolumeTextureNode.h` (Public)


#### class `UInterchangeVolumeTextureNode`  
`class UInterchangeVolumeTextureNode : public UInterchangeTextureNode`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureNode`
- L21 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
