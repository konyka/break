# Config dictionary (*.ini)

- ini files under Engine (ThirdParty excluded): 348; sections: 1780; key lines: 14974
- distinct section names: 1168

Engine config hierarchy (FConfigCacheIni): Base.ini → Base<Cat>.ini → Platform/<Plat><Cat>.ini → project Default<Cat>.ini → … Engine-side layers are listed here; every key line is in `config_keys.tsv`.


## Build (1 files)


### `Build/Linux/SanitizerRuntimeSuppressions.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no section)` | 0 | 3 | called_from_lib:libembree3.so, called_from_lib:libtbbmalloc.so, called_from_lib:libtbb.so |

## Engine (1 files)


### `Config/PluginBase.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 4 | 2 | bCanSaveAllSections, Section |

## Engine base (22 files)


### `Config/Base.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 7 | 2 | bCanSaveAllSections, Section |

### `Config/BaseCompat.ini` — 3 sections, 500 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `AppCompat` | 1 | 27 | CPUScore1, CPUScore2, CPUScore3, CPUScore4, CPUScore5, CPUSpeed1, CPUSpeed2, CPUSpeed3, CPUSpeed4, CPUSpeed5, CPUMultiCoreMult, CPUHyperThreadMult |
| `AppCompatGPU-0x10DE` | 30 | 153 | VendorName, VendorMobileTag, 0x014F, 0x00F3, 0x0221, 0x0163, 0x0162, 0x0161, 0x0160, 0x0141, 0x00F2, 0x0140 |
| `AppCompatGPU-0x1002` | 190 | 320 | VendorName, VendorMobileTag, 0x5653, 0x7248, 0x7268, 0x554D, 0x556D, 0x5D52, 0x5D72, 0x564F, 0x4154, 0x4174 |

### `Config/BaseDeviceProfiles.ini` — 189 sections, 1101 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DeviceProfile` | 3 | 1 | TextureLODGroups |
| `DeviceProfiles` | 6 | 175 | DeviceProfileNameAndTypes |
| `GlobalDefaults DeviceProfile` | 183 | 29 | TextureLODGroups, CVars |
| `Windows DeviceProfile` | 214 | 5 | DeviceType, BaseProfileName, bIsVisibleForAssets, CVars |
| `WindowsEditor DeviceProfile` | 221 | 2 | DeviceType, BaseProfileName |
| `WindowsClient DeviceProfile` | 226 | 3 | DeviceType, BaseProfileName, CVars |
| `WindowsServer DeviceProfile` | 231 | 3 | DeviceType, BaseProfileName, CVars |
| `WindowsCookedEditor DeviceProfile` | 236 | 5 | DeviceType, BaseProfileName, CVars |
| `IOSDeviceMappings` | 246 | 89 | iPhone8,1, iPhone8,2, iPhone8,4, iPhone9,[13], iPhone9,[24], iPhone10,[1,4], iPhone10,[2,5], iPhone10,[3,6], iPhone11,2, iPhone11,[4,6], iPhone11,8, iPhone12,1 |
| `IOSFallbackDeviceMappings` | 337 | 7 | iPhone, iPod, iPad, AppleTV, VisionPro0.*, VisionPro1.*, .* |
| `IOS DeviceProfile` | 347 | 40 | DeviceType, BaseProfileName, bIsVisibleForAssets, CVars, PreviewAllowlistCVars |
| `IOS_Low DeviceProfile` | 413 | 12 | BaseProfileName, CVars |
| `IOS_Mid DeviceProfile` | 427 | 11 | BaseProfileName, CVars |
| `IOS_High DeviceProfile` | 440 | 11 | BaseProfileName, CVars |
| `IOS_Epic DeviceProfile` | 453 | 11 | BaseProfileName, CVars |
| `iPhone6S DeviceProfile` | 466 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone6SPlus DeviceProfile` | 471 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhoneSE DeviceProfile` | 476 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone7 DeviceProfile` | 481 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone7Plus DeviceProfile` | 486 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone8 DeviceProfile` | 491 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone8Plus DeviceProfile` | 496 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhoneX DeviceProfile` | 501 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhoneXS DeviceProfile` | 507 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhoneXSMax DeviceProfile` | 513 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhoneXR DeviceProfile` | 519 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhone11 DeviceProfile` | 525 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhone11Pro DeviceProfile` | 531 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhone11ProMax DeviceProfile` | 537 | 4 | DeviceType, BaseProfileName, CVars |
| `iPhoneSE2 DeviceProfile` | 543 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone12Mini DeviceProfile` | 548 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone12 DeviceProfile` | 553 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone12Pro DeviceProfile` | 558 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone12ProMax DeviceProfile` | 563 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone13Mini DeviceProfile` | 568 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone13 DeviceProfile` | 573 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone13Pro DeviceProfile` | 578 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone13ProMax DeviceProfile` | 583 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhoneSE3 DeviceProfile` | 588 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone14 DeviceProfile` | 593 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone14Plus DeviceProfile` | 598 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone14Pro DeviceProfile` | 603 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone14ProMax DeviceProfile` | 608 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone15 DeviceProfile` | 613 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone15Plus DeviceProfile` | 618 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone15Pro DeviceProfile` | 623 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone15ProMax DeviceProfile` | 628 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone16 DeviceProfile` | 633 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone16e DeviceProfile` | 638 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone16Plus DeviceProfile` | 643 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone16Pro DeviceProfile` | 648 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone16ProMax DeviceProfile` | 653 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone17Pro DeviceProfile` | 658 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone17ProMax DeviceProfile` | 663 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhone17 DeviceProfile` | 668 | 3 | DeviceType, BaseProfileName, CVars |
| `iPhoneAir DeviceProfile` | 674 | 3 | DeviceType, BaseProfileName, CVars |
| `iPodTouch7 DeviceProfile` | 679 | 3 | DeviceType, BaseProfileName, CVars |
| `iPadAir2 DeviceProfile` | 684 | 3 | DeviceType, BaseProfileName, CVars |
| `iPadMini4 DeviceProfile` | 689 | 3 | DeviceType, BaseProfileName, CVars |
| `iPadPro DeviceProfile` | 694 | 8 | DeviceType, BaseProfileName, CVars |
| `iPadPro97 DeviceProfile` | 704 | 2 | DeviceType, BaseProfileName |
| `iPadPro129 DeviceProfile` | 708 | 2 | DeviceType, BaseProfileName |
| `iPadPro105 DeviceProfile` | 712 | 2 | DeviceType, BaseProfileName |
| `iPadPro11 DeviceProfile` | 716 | 2 | DeviceType, BaseProfileName |
| `iPadPro2_11 DeviceProfile` | 720 | 2 | DeviceType, BaseProfileName |
| `iPad5 DeviceProfile` | 724 | 2 | DeviceType, BaseProfileName |
| `iPad6 DeviceProfile` | 728 | 2 | DeviceType, BaseProfileName |
| `iPad7 DeviceProfile` | 732 | 2 | DeviceType, BaseProfileName |
| `iPad8 DeviceProfile` | 736 | 2 | DeviceType, BaseProfileName |
| `iPad9 DeviceProfile` | 740 | 2 | DeviceType, BaseProfileName |
| `iPadPro2_129 DeviceProfile` | 744 | 2 | DeviceType, BaseProfileName |
| `iPadPro3_129 DeviceProfile` | 748 | 2 | DeviceType, BaseProfileName |
| `iPadPro4_129 DeviceProfile` | 752 | 2 | DeviceType, BaseProfileName |
| `iPadAir3 DeviceProfile` | 756 | 2 | DeviceType, BaseProfileName |
| `iPadMini5 DeviceProfile` | 760 | 3 | DeviceType, BaseProfileName, CVars |
| `iPadPro3_11 DeviceProfile` | 766 | 8 | DeviceType, BaseProfileName, CVars |
| `iPadAir4 DeviceProfile` | 776 | 2 | DeviceType, BaseProfileName |
| `iPadAir5 DeviceProfile` | 780 | 2 | DeviceType, BaseProfileName |
| `iPad10 DeviceProfile` | 784 | 2 | DeviceType, BaseProfileName |
| `iPadPro5_129 DeviceProfile` | 788 | 2 | DeviceType, BaseProfileName |
| `iPadPro4_11 DeviceProfile` | 793 | 8 | DeviceType, BaseProfileName, CVars |
| `iPadPro6_129 DeviceProfile` | 803 | 2 | DeviceType, BaseProfileName |
| `iPadAir6 DeviceProfile` | 807 | 2 | DeviceType, BaseProfileName |
| `iPadAir6_13 DeviceProfile` | 811 | 2 | DeviceType, BaseProfileName |
| `iPadMini6 DeviceProfile` | 815 | 3 | DeviceType, BaseProfileName, CVars |
| `iPadAir7 DeviceProfile` | 821 | 2 | DeviceType, BaseProfileName |
| `iPadAir7_13 DeviceProfile` | 825 | 2 | DeviceType, BaseProfileName |
| `iPadPro5_11 DeviceProfile` | 830 | 2 | DeviceType, BaseProfileName |
| `iPadPro7_129 DeviceProfile` | 834 | 2 | DeviceType, BaseProfileName |
| `iPad11 DeviceProfile` | 838 | 2 | DeviceType, BaseProfileName |
| `iPadPro8_11 DeviceProfile` | 842 | 2 | DeviceType, BaseProfileName |
| `iPadPro8_13 DeviceProfile` | 846 | 2 | DeviceType, BaseProfileName |
| `iPadMini7 DeviceProfile` | 850 | 2 | DeviceType, BaseProfileName |
| `AppleTV DeviceProfile` | 854 | 5 | DeviceType, BaseProfileName, CVars |
| `TVOS DeviceProfile` | 861 | 2 | DeviceType, BaseProfileName |
| `AppleTV4K DeviceProfile` | 865 | 3 | DeviceType, BaseProfileName, CVars |
| `AppleTV2_4K DeviceProfile` | 870 | 2 | DeviceType, BaseProfileName |
| `VisionPro DeviceProfile` | 874 | 4 | DeviceType, BaseProfileName, CVars |
| `VisionProSimulator DeviceProfile` | 880 | 3 | DeviceType, BaseProfileName, CVars |
| `VisionOS DeviceProfile` | 885 | 2 | DeviceType, BaseProfileName |
| `/Script/AndroidDeviceProfileSelector.AndroidDeviceProfileMatchingRules` | 893 | 65 | MatchProfile |
| `Android DeviceProfile` | 987 | 20 | DeviceType, BaseProfileName, bIsVisibleForAssets, CVars, PreviewAllowlistCVars |
| `Android_Preview_OpenGL DeviceProfile` | 1023 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Preview_Vulkan DeviceProfile` | 1029 | 2 | DeviceType, BaseProfileName |
| `Android_Low DeviceProfile` | 1033 | 13 | DeviceType, BaseProfileName, CVars |
| `Android_Mid DeviceProfile` | 1049 | 14 | DeviceType, BaseProfileName, CVars |
| `Android_High DeviceProfile` | 1065 | 15 | DeviceType, BaseProfileName, CVars |
| `Android_Epic DeviceProfile` | 1082 | 15 | DeviceType, BaseProfileName, CVars |
| `Android_Emulator DeviceProfile` | 1099 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PC_Emulator DeviceProfile` | 1104 | 4 | DeviceType, BaseProfileName, CVars |
| `Android_Default DeviceProfile` | 1110 | 2 | DeviceType, BaseProfileName |
| `Android_Vulkan_SM5 DeviceProfile` | 1115 | 33 | DeviceType, BaseProfileName, CVars |
| `Android_Preview_Vulkan_SM5 DeviceProfile` | 1151 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Adreno_Vulkan_SM5 DeviceProfile` | 1156 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_Vulkan_SM5 DeviceProfile` | 1160 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Xclipse_Vulkan_SM5 DeviceProfile` | 1165 | 2 | DeviceType, BaseProfileName |
| `Android_Adreno4xx DeviceProfile` | 1172 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Adreno5xx_Low DeviceProfile` | 1177 | 2 | DeviceType, BaseProfileName |
| `Android_Adreno5xx DeviceProfile` | 1181 | 2 | DeviceType, BaseProfileName |
| `Android_Adreno6xx DeviceProfile` | 1185 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Adreno6xx_Vulkan DeviceProfile` | 1191 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Adreno7xx DeviceProfile` | 1197 | 2 | DeviceType, BaseProfileName |
| `Android_Adreno7xx_Vulkan DeviceProfile` | 1201 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Adreno8xx DeviceProfile` | 1207 | 2 | DeviceType, BaseProfileName |
| `Android_Adreno8xx_Vulkan DeviceProfile` | 1211 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Xclipse_5xx DeviceProfile` | 1220 | 2 | DeviceType, BaseProfileName |
| `Android_Xclipse_5xx_Vulkan DeviceProfile` | 1224 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Xclipse_9xx DeviceProfile` | 1230 | 2 | DeviceType, BaseProfileName |
| `Android_Xclipse_9xx_Vulkan DeviceProfile` | 1234 | 4 | DeviceType, BaseProfileName, CVars |
| `Android_Xclipse_xxx DeviceProfile` | 1242 | 2 | DeviceType, BaseProfileName |
| `Android_Xclipse_xxx_Vulkan DeviceProfile` | 1246 | 4 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_G6xxx DeviceProfile` | 1257 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_GT7xxx DeviceProfile` | 1262 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_GE8xxx DeviceProfile` | 1267 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_GM9xxx DeviceProfile` | 1272 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_GM9xxx_Vulkan DeviceProfile` | 1277 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_Series_High DeviceProfile` | 1283 | 2 | DeviceType, BaseProfileName |
| `Android_PowerVR_Series_Mid DeviceProfile` | 1287 | 2 | DeviceType, BaseProfileName |
| `Android_PowerVR_Series_Low DeviceProfile` | 1291 | 2 | DeviceType, BaseProfileName |
| `Android_PowerVR_Series_High_Vulkan DeviceProfile` | 1295 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_Series_Mid_Vulkan DeviceProfile` | 1300 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_PowerVR_Series_Low_Vulkan DeviceProfile` | 1305 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_T6xx DeviceProfile` | 1313 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_T7xx DeviceProfile` | 1318 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_T8xx DeviceProfile` | 1323 | 4 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G71 DeviceProfile` | 1330 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G72 DeviceProfile` | 1334 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G72_Vulkan DeviceProfile` | 1338 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G76 DeviceProfile` | 1344 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G76_Vulkan DeviceProfile` | 1348 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G77 DeviceProfile` | 1354 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G77_Vulkan DeviceProfile` | 1358 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G78 DeviceProfile` | 1364 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G78_Vulkan DeviceProfile` | 1368 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G710 DeviceProfile` | 1374 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G710_Vulkan DeviceProfile` | 1378 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G7xx DeviceProfile` | 1384 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G7xx_Vulkan DeviceProfile` | 1388 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_G9xx DeviceProfile` | 1394 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_G9xx_Vulkan DeviceProfile` | 1398 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_Gx DeviceProfile` | 1404 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_Gx_Vulkan DeviceProfile` | 1408 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_Mali_Gx_Ultra DeviceProfile` | 1413 | 2 | DeviceType, BaseProfileName |
| `Android_Mali_Gx_Ultra_Vulkan DeviceProfile` | 1417 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_TegraK1 DeviceProfile` | 1422 | 2 | DeviceType, BaseProfileName |
| `Android_Unknown_Vulkan DeviceProfile` | 1426 | 3 | DeviceType, BaseProfileName, CVars |
| `Android_OpenXR DeviceProfile` | 1432 | 10 | DeviceType, BaseProfileName, CVars, Cvars |
| `Meta_Quest_3 DeviceProfile` | 1444 | 6 | DeviceType, BaseProfileName, CVars |
| `Meta_Quest_3S DeviceProfile` | 1452 | 6 | DeviceType, BaseProfileName, CVars |
| `Meta_Quest_Pro DeviceProfile` | 1460 | 6 | DeviceType, BaseProfileName, CVars |
| `Oculus_Quest2 DeviceProfile` | 1468 | 7 | DeviceType, BaseProfileName, CVars |
| `Oculus_Quest DeviceProfile` | 1477 | 6 | DeviceType, BaseProfileName, CVars |
| `Mac DeviceProfile` | 1486 | 7 | DeviceType, BaseProfileName, bIsVisibleForAssets, CVars |
| `MacClient DeviceProfile` | 1495 | 2 | DeviceType, BaseProfileName |
| `MacEditor DeviceProfile` | 1499 | 2 | DeviceType, BaseProfileName |
| `MacServer DeviceProfile` | 1503 | 2 | DeviceType, BaseProfileName |
| `Linux DeviceProfile` | 1507 | 7 | DeviceType, BaseProfileName, bIsVisibleForAssets, MeshLODSettings, TextureLODSettings, CVars |
| `LinuxEditor DeviceProfile` | 1516 | 4 | DeviceType, BaseProfileName, MeshLODSettings, TextureLODSettings |
| `LinuxAArch6 DeviceProfile` | 1522 | 4 | DeviceType, BaseProfileName, MeshLODSettings, TextureLODSettings |
| `LinuxClient DeviceProfile` | 1528 | 2 | DeviceType, BaseProfileName |
| `LinuxArm64Client DeviceProfile` | 1532 | 2 | DeviceType, BaseProfileName |
| `LinuxServer DeviceProfile` | 1536 | 5 | DeviceType, BaseProfileName, MeshLODSettings, TextureLODSettings, CVars |
| `LinuxArm64Server DeviceProfile` | 1543 | 5 | DeviceType, BaseProfileName, MeshLODSettings, TextureLODSettings, CVars |
| `LinuxCookedEditor DeviceProfile` | 1550 | 5 | DeviceType, BaseProfileName, CVars |
| `MagicLeap_Vulkan DeviceProfile` | 1557 | 6 | DeviceType, BaseProfileName, CVars, Cvars |
| `cv DeviceProfile` | 1566 | 13 | DeviceType, BaseProfileName, CVars, Cvars |
| `Valve_Frame_Lepton DeviceProfile` | 1581 | 7 | DeviceType, BaseProfileName, CVars, Cvars |
| `Windows_Preview_ES31 DeviceProfile` | 1590 | 2 | DeviceType, BaseProfileName |
| `Windows_Preview_ES31_NonSDF DeviceProfile` | 1594 | 2 | DeviceType, BaseProfileName |

### `Config/BaseEditor.ini` — 73 sections, 437 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 5 | 4 | Section |
| `Internationalization` | 11 | 5 | LocalizationPaths, ToolTipLocalizationPaths, PropertyNameLocalizationPaths |
| `ImportSetting` | 19 | 1 | CheckSingleInfluenceLOD |
| `LogWindow` | 22 | 1 | MaxNumberOfLogLines |
| `SlateRenderer` | 25 | 3 | GrayscaleFontAtlasSize, ColorFontAtlasSize, SdfFontAtlasSize |
| `PythonScriptPlugin` | 30 | 4 | DisablePythonForCommandlet |
| `AssetTools` | 36 | 0 |  |
| `/Script/UnrealEd.ThumbnailManager` | 42 | 34 | RenderableThumbnailTypes |
| `/Script/UnrealEd.DefaultSizedThumbnailRenderer` | 78 | 2 | DefaultSizeX, DefaultSizeY |
| `/Script/ContentBrowserData.ContentBrowserDataSubsystem` | 82 | 3 | EnabledDataSources |
| `/Script/UnrealEd.CollisionAutomationTestConfigData` | 87 | 36 | ComponentSweepMultiTests, LineTraceSingleByChannelTests |
| `/Script/UnrealEd.WorldThumbnailRenderer` | 143 | 4 | GlobalOrbitPitchOffset, GlobalOrbitYawOffset, bUseUnlitScene, bAllowWorldThumbnails |
| `/Script/UnrealEd.ActorFactory` | 149 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryStaticMesh` | 152 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryInteractiveFoliage` | 155 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryPlayerStart` | 158 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryDirectionalLight` | 161 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryPointLight` | 164 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactorySpotLight` | 167 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryPhysicsActor` | 170 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactorySkeletalMesh` | 173 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactorySkeletalMeshSingleAnim` | 176 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryAmbientSoundSimpleToggleable` | 179 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryAmbientSoundNonLoopingToggleable` | 182 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryAmbientSoundSimple` | 185 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryAmbientSound` | 188 | 1 | MenuPriority |
| `/Script/UnrealEd.ActorFactoryAmbientSoundMovable` | 191 | 1 | MenuPriority |
| `/Script/BlueprintGraph.EdGraphSchema_K2` | 194 | 14 | EditoronlyBPFunctionRedirects, AllowedMutableContainerFunctions |
| `BlueprintEditor.Palette` | 217 | 1 | bUseLegacyLayout |
| `BlueprintEditor.Favorites` | 220 | 21 | Profiles, DefaultProfile, StarterProfile |
| `BlueprintEditor.Menu` | 243 | 5 | BlueprintHiddenFields |
| `UnrealEd.HitProxy` | 250 | 1 | HitProxySize |
| `/Script/UnrealEd.UnrealEdOptions` | 253 | 18 | EditorCategories, EditorCommands, bExpandClassPickerClassList, NewAssetDefaultClasses |
| `Cooker.CleanStaticMeshMtrlSkip` | 279 | 1 | Class |
| `AudioImporter` | 282 | 1 | EnableUEWavComp |
| `TextureImporter` | 285 | 3 | AllowNonPowerOfTwoTextures, RetainJpegFormat, EnableUEJpeg |
| `/Script/Cascade.CascadeConfiguration` | 291 | 16 | ModuleMenu_ModuleRejections, ModuleMenu_TypeDataToBaseModuleRejections, ModuleMenu_TypeDataToSpecificModuleRejections |
| `CurveEditor` | 309 | 1 | bShouldPromptOnCurveRemoveAll |
| `UnrealEd.URLs` | 312 | 17 | DocumentationURL, APIDocsURL, CommunityHomeURL, OnlineLearningURL, ForumsURL, SearchForAnswersURL, SnippetsURL, SupportWebsiteURL, SourceCodeIDEURL_Windows, SourceCodeIDEURL_Mac, SourceCodeIDEURL_Linux, SourceCodeIDEURL_Other |
| `UnrealEd.URLOverrides` | 332 | 0 |  |
| `UserDefinedStructure` | 335 | 1 | bUseUserDefinedStructure |
| `CustomBlueprintFunctionLibrary` | 338 | 1 | bCanCreateNew |
| `StructSerialization` | 341 | 2 | SkipByteCodeSerialization, BreakSerializationRecursion |
| `ScriptErrorLog` | 345 | 1 | MaxNumOfAccessViolation |
| `/Script/Engine.ParticleSystemAuditCommandlet` | 349 | 2 | HighSpawnRateOrBurstThreshold, FarLODDistanceTheshold |
| `GatherTextFromAssets` | 353 | 2 | MinFreeMemory, MaxUsedMemory |
| `CookSettings` | 357 | 69 | SkipOnlyEditorOnly, BulkDataRegistryEnabled, CookContentMissingSeverity, CookerIdleWarningSeverity, UnexpectedLoadWarningSeverity, CookIncrementalDefaultIncremental, LegacyIterative, PackagesPerGC, IdleTimeToGC, MemoryMinFreePhysical, MemoryMinFreeVirtual, MemoryMaxUsedPhysical |
| `AppendToClassSchema` | 527 | 0 |  |
| `EditorDomain` | 536 | 11 | EditorDomainEnabled, SaveUnversioned, ClassBlockList, PackageBlockList, GlobalCanConstructClasses |
| `IncrementalValidate` | 567 | 1 | LoggingSoftMaximum |
| `CookPlatformDataCacheSettings` | 575 | 0 |  |
| `TextureBuild` | 580 | 1 | NewTextureBuilds |
| `Texture` | 583 | 0 |  |
| `/Script/Localization.LocalizationSettings` | 590 | 8 | EngineTargetsSettings, GameTargetsSettings |
| `/Script/UnrealEd.EditorProjectAppearanceSettings` | 600 | 14 | bDisplayUnits, DistanceUnits, MassUnits, TimeUnits, AngleUnits, SpeedUnits, AngularSpeedUnits, AccelerationUnits, TemperatureUnits, ForceUnits, TorqueUnits, ImpulseUnits |
| `BlueprintSearchSettings` | 616 | 49 | AsyncTaskBatchSize, bDisableDeferredIndexing, bDisableThreadedIndexing, bEnableCsvStatsProfiling, bEnableDeveloperMenuTools, bDisableSearchResultTemplates, bDisableImmediateAssetDiscovery, ClassesWithStaticSearchableValues, StaticSearchableTagNames, ExcludedAssetTypes, ExcludedFolderPaths, NoExportT |
| `/Script/UnrealEd.BlueprintEditorProjectSettings` | 693 | 1 | bValidateUnloadedSoftActorReferences |
| `/Script/UnrealEd.AssetViewerSettings` | 696 | 1 | Profiles |
| `/Script/DataValidation.DataValidationManager` | 699 | 1 | bValidateOnSave |
| `/Script/UMGEditor.UMGEditorProjectSettings` | 702 | 13 | DebugResolutions |
| `/Script/UnrealEd.DiffAssetRegistriesCommandlet` | 717 | 2 | P4EngineBasePath, P4EngineAssetPath |
| `EditorSettings` | 722 | 1 | bCanModifyPluginsFromBrowser |
| `/Script/GameFeaturesEditor.GameFeaturesEditorSettings` | 725 | 2 | PluginTemplates |
| `EditorBulkData` | 729 | 1 | LogCookedStatus |
| `BulkDataRegistry` | 732 | 1 | CommandletsUsingBulkDataRegistry |
| `DeviceDiscovery` | 735 | 1 | AppleRescanRate |
| `/Script/TextureUtilitiesCommon.TextureImportSettings` | 738 | 1 | CompressedFormatForFloatTextures |
| `/Script/Blutility.EditorUtilityWidgetProjectSettings` | 741 | 24 | bShowWidgetsFromEngineContent, bShowWidgetsFromDeveloperContent, bUseWidgetTemplateSelector, CommonRootWidgetClasses, WidgetClassesToHide |
| `/Script/RenderResourceViewer.RenderResourceViewerSettings` | 767 | 8 | Filters |
| `MemoryPools` | 777 | 1 | PersistentAllocatorReserveSizeMB |
| `/Script/RigVM.RigVMProjectSettings` | 780 | 4 | VariantTags |
| `AIAssistant` | 786 | 1 | bIsEnabled |
| `ConsoleVariables` | 789 | 1 | SplineComponent.OnlyUpdateActiveSpline |

### `Config/BaseEditorKeyBindings.ini` — 2 sections, 10 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.UnrealEdKeyBindings` | 1 | 9 | KeyBindings |
| `UserDefinedGestures` | 13 | 1 | Content |

### `Config/BaseEditorPerProjectUserSettings.ini` — 64 sections, 713 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.EditorPerProjectUserSettings` | 21 | 19 | bEnableOutputLogClearOnPIE, AllowFlightCameraToRemapKeys, bSuppressFullyLoadPrompt, bAllowSelectTranslucent, bUpdateActorsInGridLevelsImmediately, bDisplayMemorySizeDataInLevelBrowser, bAutoReimportAnimSets, PropertyMatrix_NumberOfPasteOperationsBeforeWarning, bSCSEditorShowGrid, bKeepFbxNamespace,  |
| `/Script/UnrealEd.FbxExportOption` | 68 | 8 | FbxExportCompatibility, bASCII, bForceFrontXAxis, LevelOfDetail, bExportMorphTargets, Collision, VertexColor, MapSkeletalMotionToRoot |
| `/Script/UnrealEd.EditorStyleSettings` | 78 | 13 | bEnableUserEditorLayoutManagement, ColorVisionDeficiencyPreviewType, ColorVisionDeficiencySeverity, XAxisColor, YAxisColor, ZAxisColor, bUseSmallToolBarIcons, bShowFriendlyNames, bExpandConfigurationMenus, bShowProjectMenus, bShowLaunchMenus, bShowAllAdvancedDetails |
| `/Script/OutputLog.OutputLogSettings` | 104 | 7 | LogBackgroundColor, LogSelectionBackgroundColor, LogNormalColor, LogCommandColor, LogWarningColor, LogErrorColor, LogFontSize |
| `/Script/Levels.LevelBrowserSettings` | 113 | 5 | bDisplayActorCount, bDisplayLightmassSize, bDisplayFileSize, bDisplayPaths, bDisplayEditorOffset |
| `/Script/SceneOutliner.ActorBrowsingModeSettings` | 122 | 5 | bHideTemporaryActors, bShowOnlyActorsInCurrentLevel, bShowOnlySelectedActors, bHideActorComponents, bHideLevelInstanceHierarchy |
| `/Script/UnrealEd.ClassViewerSettings` | 135 | 2 | DisplayInternalClasses, DeveloperFolderType |
| `/Script/UnrealEd.SkeletalMeshEditorSettings` | 141 | 6 | AnimPreviewFloorColor, AnimPreviewSkyColor, AnimPreviewSkyBrightness, AnimPreviewLightBrightness, AnimPreviewLightingDirection, AnimPreviewDirectionalColor |
| `/Script/UnrealEd.EditorExperimentalSettings` | 151 | 13 | bWorldBrowser, bBreakOnExceptions, bToolbarCustomization, bBehaviorTreeEditor, bEnableFindAndReplaceReferences, bExampleLayersAndBlends, bEnableProjectLauncherExtensions, bEnableAsyncTextureCompilation, bEnableAsyncStaticMeshCompilation, bEnableAsyncSkinnedAssetCompilation, bEnableAsyncSoundWaveComp |
| `/Script/UnrealEd.EditorLoadingSavingSettings` | 171 | 14 | LoadLevelAtStartup, bAutoReimportTextures, bAutoReimportCSV, bDirtyMigratedBlueprints, bAutoSaveEnable, bAutoSaveMaps, bAutoSaveContent, AutoSaveTimeMinutes, AutoSaveInteractionDelayInSeconds, AutoSaveWarningInSeconds, AutoReimportDirectorySettings, bPromptForCheckoutOnAssetModification |
| `/Script/UnrealEd.LevelEditorMiscSettings` | 202 | 13 | bAutoApplyLightingEnable, bBSPAutoUpdate, bAutoMoveBSPPivotOffset, bNavigationAutoUpdate, bReplaceCopyPropertiesDefault, bReplaceCopiesPropertiesWhenRelatedByNativeParent, bReplaceRespectsScale, bCheckReferencesOnDelete, bAllowBackgroundAudio, bEnableRealTimeAudio, EditorVolumeLevel, bEnableEditorSo |
| `/Script/UnrealEd.LevelEditorPlaySettings` | 231 | 91 | PlayFromHerePlayerStartClassName, EnableGameSound, NewWindowWidth, NewWindowHeight, CenterNewWindow, StandaloneWindowWidth, StandaloneWindowHeight, CenterStandaloneWindow, ShowMouseControlLabel, AutoRecompileBlueprints, ShouldMinimizeEditorOnVRPIE, bOnlyLoadVisibleLevelsInPIE |
| `/Script/UnrealEd.LevelEditorViewportSettings` | 337 | 106 | FlightCameraControlType, LandscapeEditorControlType, FoliageEditorControlType, bPanMovesCanvas, bCenterZoomAroundCursor, bAllowTranslateRotateZWidget, bClickBSPSelectsBrush, CameraSpeed, CameraSpeedScalar, MouseScrollCameraSpeed, MouseSensitivty, bInvertMouseLookYAxis |
| `ColorPickerUI` | 484 | 3 | bAdvancedSectionExpanded, bSRGBEnabled, bWheelMode |
| `Undo` | 490 | 1 | UndoBufferSize |
| `PropertySettings` | 495 | 2 | ShowFriendlyPropertyNames, ExpandDistributions |
| `MRU` | 499 | 0 |  |
| `/Script/UnrealEd.MaterialEditorOptions` | 502 | 7 | bShowGrid, bShowBackground, bHideUnusedConnectorsSetting, bRealtimeMaterialViewport, bRealtimeExpressionViewport, bAlwaysRefreshAllPreviews, bLivePreviewUpdate |
| `UnEdViewport` | 512 | 1 | InterpEdPanInvert |
| `FEditorModeTools` | 516 | 4 | ShowWidget, CoordSystem, UseAbsoluteTranslation, AllowTranslateRotateZWidget |
| `LightingBuildOptions` | 522 | 8 | OnlyBuildSelectedActors, OnlyBuildCurrentLevel, OnlyBuildChanged, BuildBSP, BuildActors, QualityLevel, NumUnusedLocalCores, ShowLightingBuildInfo |
| `/Script/UnrealEd.PhysicsAssetEditorOptions` | 532 | 13 | AngularSnap, LinearSnap, bDrawContacts, FloorGap, GravScale, bPromptOnBoneDelete, PokeStrength, InteractionDistance, bShowNamesInHierarchy, PokePauseTime, PokeBlendTime, ConstraintDrawSize |
| `/Script/UnrealEd.CurveEdOptions` | 548 | 9 | MinViewRange, MaxViewRange, BackgroundColor, LabelColor, SelectedLabelColor, GridColor, GridTextColor, LabelBlockBkgColor, SelectedKeyColor |
| `/Script/UnrealEd.PersonaOptions` | 560 | 9 | bShowGrid, bHighlightOrigin, bShowSky, bShowFloor, GridSize, ViewModeType, ViewportBackgroundColor, ViewFOV, ShowMeshStats |
| `UnrealEd.UIEditorOptions` | 572 | 15 | WindowPosition, ViewportSashPosition, PropertyWindowSashPosition, ViewportGutterSize, VirtualSizeX, VirtualSizeY, bRenderViewportOutline, bRenderContainerOutline, bRenderSelectionOutline, bRenderSelectionHandles, bRenderPerWidgetSelectionOutline, GridSize |
| `/Script/UnrealEd.CascadeOptions` | 590 | 37 | bShowModuleDump, BackgroundColor, bUseSubMenus, bUseSpaceBarReset, bUseSpaceBarResetInLevel, Empty_Background, Emitter_Background, Emitter_Unselected, Emitter_Selected, ModuleColor_General_Unselected, ModuleColor_General_Selected, ModuleColor_TypeData_Unselected |
| `ContentBrowserFilter` | 630 | 1 | FavoriteTypes_1 |
| `FAutoPackageBackup` | 634 | 3 | Enabled, MaxAllowedSpaceInMB, BackupIntervalInMinutes |
| `/Script/UnrealEd.FbxImportUI` | 640 | 16 | bOverrideFullName, bCreatePhysicsAsset, bAutoComputeLodDistances, LodDistance0, LodDistance1, LodDistance2, LodDistance3, LodDistance4, LodDistance5, LodDistance6, LodDistance7, MinimumLodNumber |
| `/Script/UnrealEd.FbxAssetImportData` | 658 | 6 | ImportTranslation, ImportRotation, ImportUniformScale, bConvertScene, bForceFrontXAxis, bConvertSceneUnit |
| `/Script/UnrealEd.FbxMeshImportData` | 666 | 7 | bTransformVertexToAbsolute, bBakePivotInVertex, bReorderMaterialToFbxOrder, bImportMeshLODs, NormalImportMethod, NormalGenerationMethod, bComputeWeightedNormals |
| `/Script/UnrealEd.FbxStaticMeshImportData` | 675 | 10 | StaticMeshLODGroup, VertexColorImportOption, VertexOverrideColor, bRemoveDegenerates, bBuildReversedIndexBuffer, bGenerateLightmapUVs, bOneConvexHullPerUCX, bAutoGenerateCollision, bCombineMeshes, NormalImportMethod |
| `/Script/UnrealEd.FbxSkeletalMeshImportData` | 688 | 12 | VertexColorImportOption, VertexOverrideColor, bUpdateSkeletonReferencePose, bUseT0AsRefPose, bPreserveSmoothingGroups, bKeepSectionsSeparate, bImportMeshesInBoneHierarchy, bImportMorphTargets, ThresholdPosition, ThresholdTangentNormal, ThresholdUV, MorphThresholdPosition |
| `/Script/UnrealEd.FbxAnimSequenceImportData` | 702 | 13 | bImportMeshesInBoneHierarchy, AnimationLength, FrameImportRange, bUseDefaultSampleRate, CustomSampleRate, bImportCustomAttribute, bDeleteExistingCustomAttributeCurves, bImportBoneTracks, bSetMaterialDriveParameterOnCustomAttribute, bRemoveRedundantKeys, bDeleteExistingMorphTargetCurves, bDoNotImport |
| `/Script/UnrealEd.FbxTextureImportData` | 717 | 10 | bInvertNormalMaps, MaterialSearchLocation, BaseMaterialName, BaseColorName, BaseDiffuseTextureName, BaseNormalTextureName, BaseEmissiveColorName, BaseEmmisiveTextureName, BaseSpecularTextureName, BaseOpacityTextureName |
| `SoundSettings` | 729 | 2 | ChirpSoundClasses, BatchProcessMatureNodeSoundClasses |
| `EditorPreviewMesh` | 734 | 1 | PreviewMeshNames |
| `EditorLayout` | 739 | 1 | SlateMainFrameLayout |
| `LandscapeEdit` | 743 | 39 | ToolStrength, WeightTargetValue, bUseWeightTargetValue, BrushRadius, BrushComponentSize, BrushFalloff, bUseClayBrush, AlphaBrushScale, AlphaBrushRotation, AlphaBrushPanU, AlphaBrushPanV, AlphaTextureName |
| `FoliageEdit` | 785 | 7 | Radius, PaintDensity, UnpaintDensity, bFilterLandscape, bFilterStaticMesh, bFilterBSP, bFilterTranslucent |
| `MeshPaintEdit` | 795 | 1 | DefaultBrushRadius |
| `BlueprintSpawnNodes` | 799 | 10 | Node |
| `DefaultEventNodes` | 812 | 27 | Node |
| `MaterialEditorSpawnNodes` | 841 | 21 | Node |
| `WidgetTemplatesExpanded` | 864 | 1 | Common |
| `DetailCustomWidgetExpansion` | 867 | 1 | LandscapeEditorObject |
| `LevelSequenceEditor SequencerSettings` | 870 | 6 | bShowRangeSlider, bKeepPlayRangeInSectionBounds, ZeroPadFrames, bInfiniteKeyAreas, bAutoSetTrackDefaults, FrameNumberDisplayFormat |
| `TemplateSequenceEditor SequencerSettings` | 878 | 6 | bShowRangeSlider, bKeepPlayRangeInSectionBounds, ZeroPadFrames, bInfiniteKeyAreas, bAutoSetTrackDefaults, FrameNumberDisplayFormat |
| `TakeRecorderSequenceEditor SequencerSettings` | 886 | 8 | bShowRangeSlider, bKeepPlayRangeInSectionBounds, ZeroPadFrames, bInfiniteKeyAreas, bAutoSetTrackDefaults, FrameNumberDisplayFormat, bAutoScrollEnabled, bCleanPlaybackMode |
| `EmbeddedActorSequenceEditor SequencerSettings` | 896 | 6 | bShowRangeSlider, bKeepPlayRangeInSectionBounds, ZeroPadFrames, bInfiniteKeyAreas, bAutoSetTrackDefaults, bCompileDirectorOnEvaluate |
| `NiagaraSequenceEditor SequencerSettings` | 904 | 16 | bAutoScrollEnabled, bKeepPlayRangeInSectionBounds, bShowRangeSlider, LoopMode, bCleanPlaybackMode, bShowLayerBars, ColumnVisibilitySettings |
| `DaySequenceEditor SequencerSettings` | 922 | 6 | bShowRangeSlider, bKeepPlayRangeInSectionBounds, ZeroPadFrames, bInfiniteKeyAreas, bAutoSetTrackDefaults, FrameNumberDisplayFormat |
| `/Script/LevelSequenceEditor.LevelSequenceEditorSettings` | 930 | 6 | TrackSettings |
| `/Script/LevelSequenceEditor.TakeRecorderEditorSettings` | 938 | 5 | TrackSettings |
| `/Script/DaySequenceEditor.DaySequenceEditorSettings` | 945 | 6 | TrackSettings |
| `/Script/MovieSceneTools.MovieSceneToolsProjectSettings` | 953 | 3 | FbxSettings |
| `/Script/SpeedTreeImporter.SpeedTreeImportData` | 958 | 14 | TreeScale, ImportGeometryType, LODType, IncludeCollision, MakeMaterialsCheck, IncludeNormalMapCheck, IncludeDetailMapCheck, IncludeSpecularMapCheck, IncludeBranchSeamSmoothing, IncludeSpeedTreeAO, IncludeColorAdjustment, IncludeVertexProcessingCheck |
| `/Script/MeshPaint.MeshPaintSettings` | 974 | 1 | VertexPreviewSize |
| `/Script/ClothPainter.ClothPainterSettings` | 977 | 1 | VertexPreviewSize |
| `/Script/UndoHistory.UndoHistorySettings` | 980 | 1 | bShowTransactionDetails |
| `/Script/LiveCoding.LiveCodingSettings` | 983 | 4 | Startup, bEnabled, bEnableReinstancing, bAutomaticallyCompileNewClasses |
| `/Script/AssetManagerEditor.ReferenceViewerSettings` | 989 | 19 | bLimitSearchDepth, bIsShowReferencers, MaxSearchReferencerDepth, bIsShowDependencies, MaxSearchDependencyDepth, bLimitSearchBreadth, MaxSearchBreadth, bIsShowSoftReferences, bIsShowHardReferences, bIsShowEditorOnlyReferences, bIsShowManagementReferences, bIsShowSearchableNames |
| `/Script/BlueprintHeaderView.BlueprintHeaderViewSettings` | 1011 | 4 | SyntaxColors, FontSize, SelectionColor, SortMethod |
| `AssetRegistry` | 1017 | 1 | BlockingInitialLoad |

### `Config/BaseEditorSettings.ini` — 9 sections, 42 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Internationalization` | 5 | 3 | ShouldUseLocalizedNumericInput, ShouldUseLocalizedPropertyNames, ShouldUseLocalizedNodeAndPinNames |
| `/Script/UnrealEd.CrashReportsPrivacySettings` | 10 | 1 | bSendUnattendedBugReports |
| `/Script/UnrealEd.AnalyticsPrivacySettings` | 13 | 1 | bSendUsageData |
| `/Script/UnrealEd.ContentBrowserSettings` | 16 | 14 | NumObjectsToLoadBeforeWarning, RealTimeThumbnails, DisplayFolders, DisplayEmptyFolders, DisplayEngineFolder, DisplayDevelopersFolder, DisplayCollections, DisplayCppFolders, DisplayPluginFolders, NumObjectsInRecentList, IncludeClassNames, IncludeAssetPaths |
| `/Script/UnrealEd.PropertyColorSettings` | 46 | 1 | CustomProperties |
| `/Script/VREditor.VRModeSettings` | 49 | 14 | bEnableAutoVREditMode, bAutokeySequences, InteractorHand, bShowWorldMovementGrid, bShowWorldMovementPostProcess, bShowWorldScaleProgressBar, bScaleWorldFromFloor, bScaleWorldWithDynamicPivot, bAllowSimultaneousWorldScalingAndRotation, UIBrightness, GizmoScale, DoubleClickTime |
| `/Script/TakeRecorder.TakeRecorderProjectSettings` | 65 | 1 | Settings |
| `DefaultTakeMetaData TakeMetaData` | 68 | 1 | Duration |
| `/Script/UnrealEd.EditorPerformanceSettings` | 71 | 6 | bEnableEditorPeformanceTool, bEnableNotifications, NotifyList |

### `Config/BaseEngine.ini` — 230 sections, 2797 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 5 | 5 | Section |
| `/Script/EngineSettings.GameMapsSettings` | 12 | 6 | GameInstanceClass, EditorStartupMap, GameDefaultMap, ServerDefaultMap, GlobalDefaultGameMode, LocalMapOptions |
| `InstallBundleManager` | 23 | 2 | ModuleName, EditorModuleName |
| `URL` | 27 | 4 | Protocol, Name, SaveExt, Port |
| `AutoLoadModulesByPhase` | 33 | 0 |  |
| `AutoLoadModulesByPhase_Editor` | 35 | 1 | FileSystemReady |
| `HTTP` | 39 | 8 | HttpConnectionTimeout, HttpActivityTimeout, FlushSoftTimeLimitDefault, FlushHardTimeLimitDefault, FlushSoftTimeLimitShutdown, FlushHardTimeLimitShutdown, FlushSoftTimeLimitFullFlush, FlushHardTimeLimitFullFlush |
| `HTTP.Curl` | 55 | 1 | bAllowSeekFunction |
| `BackgroundHttp` | 58 | 4 | MaxActiveDownloads, TempFileTimeOutSeconds, DeleteTempFilesWithoutURLMappingEntries, RemoveURLMappingEntriesWithoutPhysicalTempFiles |
| `WebSockets` | 73 | 7 | WebSocketsProtocols, TextMessageMemoryLimit |
| `WebSockets.LibWebSockets` | 82 | 5 | ThreadStackSize, ThreadTargetFrameTimeInSeconds, ThreadMinimumSleepTimeInSeconds, MaxHttpHeaderData, PingPongInterval |
| `Ping` | 89 | 2 | StackSize, MinPingSendWaitTimeMs |
| `Voice` | 93 | 2 | bEnabled, bDuckingOptOut |
| `SlateStyle` | 97 | 1 | DefaultFontName |
| `PlatformMemoryBuckets` | 100 | 5 | LargestMemoryBucket_MinGB, LargerMemoryBucket_MinGB, DefaultMemoryBucket_MinGB, SmallerMemoryBucket_MinGB, SmallestMemoryBucket_MinGB |
| `CoreUObject.UninitializedScriptStructMembersCheck` | 108 | 3 | EngineModuleReflectedUninitializedPropertyVerbosity, ProjectModuleReflectedUninitializedPropertyVerbosity, ObjectReferenceReflectedUninitializedPropertyVerbosity |
| `CoreUObject.ShortTypeNameInMetaDataCheck` | 113 | 15 | MetaDataKeys |
| `/Script/Engine.Engine` | 130 | 220 | ConsoleClassName, GameViewportClientClassName, LocalPlayerClassName, WorldSettingsClassName, NavigationSystemClassName, NavigationSystemConfigClassName, AvoidanceManagerClassName, PhysicsCollisionHandlerClassName, LevelScriptActorClassName, DefaultBlueprintBaseClassName, GameUserSettingsClassName, A |
| `/Script/Engine.OnlineEngineInterface` | 365 | 1 | ClassName |
| `CoreRedirects` | 368 | 796 | ClassRedirects, PackageRedirects, StructRedirects, FunctionRedirects, PropertyRedirects, EnumRedirects |
| `CoreUObject.Metadata` | 1450 | 12 | MetadataRedirects |
| `EnumRemap` | 1465 | 0 |  |
| `PlatformInterface` | 1469 | 2 | CloudStorageInterfaceClassName, InGameAdManagerClassName |
| `/Script/Engine.UserInterfaceSettings` | 1473 | 4 | UIScaleRule, UIScaleCurve, bLoadWidgetsOnDedicatedServer, bAllowHighDPIInGameMode |
| `/Script/IrisCore.PartialNetObjectAttachmentHandlerConfig` | 1481 | 1 | MaxPartCount |
| `/Script/IrisCore.NetBlobHandlerDefinitions` | 1484 | 3 | NetBlobHandlerDefinitions |
| `/Script/IrisCore.DataStreamDefinitions` | 1489 | 2 | DataStreamDefinitions |
| `/Script/IrisCore.NetObjectPrioritizerDefinitions` | 1493 | 2 | NetObjectPrioritizerDefinitions |
| `/Script/IrisCore.NetObjectFilterDefinitions` | 1497 | 2 | NetObjectFilterDefinitions |
| `/Script/IrisCore.ReplicationFilteringConfig` | 1501 | 2 | bEnableObjectScopeHysteresis, DefaultHysteresisFrameCount |
| `/Script/IrisCore.ObjectReplicationBridgeConfig` | 1505 | 9 | RequiredNetDriverChannelClassName, DefaultSpatialFilterName, FilterConfigs, PrioritizerConfigs, DeltaCompressionConfigs, CriticalClassConfigs |
| `/Script/IrisCore.ReplicationStateDescriptorConfig` | 1535 | 32 | bEnsureAllClassesAreFullyPushModel, EnsureFullyPushModelClassNames, SupportsStructNetSerializerList |
| `/Script/IrisCore.NetTokenTypeIdConfig` | 1571 | 5 | ReservedTypeIds |
| `/Script/Engine.GameEngine` | 1580 | 2 | MaxDeltaTime, ServerFlushLogInterval |
| `Engine.StartupPackages` | 1584 | 49 | Package |
| `Core.Log` | 1642 | 0 |  |
| `Core.System` | 1646 | 18 | Paths, CutdownPaths, ZeroEngineVersionWarning, UseStrictEngineVersioning, CanStripEditorOnlyExportsAndImports, CanSkipEditorReferencedPackagesWhenCooking, CanUseUnversionedPropertySerialization, TestUnversionedPropertySerializationWhenCooking, DetailedCallstacksInNonMonolithicBuilds, UseSeperateBulk |
| `Core.System.Experimental` | 1666 | 2 | EnablePackageSidecarSaving, AllowVirtualizationOptOut |
| `Core.ContentVirtualization` | 1671 | 3 | SystemName, LazyInit, InitPreSlate |
| `Core.VirtualizationModule` | 1676 | 18 | EnablePayloadVirtualization, EnableCacheOnPull, EnableCacheOnPush, MinPayloadLength, BackendGraph, VirtualizationProcessTag, AllowSubmitIfVirtualizationFailed, FilterMode, FilterMapContent, LazyInitConnections, DisableLazyInitIfInteractive, UseLegacyErrorHandling |
| `/Script/Virtualization.VirtualizationFilterSettings` | 1696 | 1 | ExcludePackagePaths |
| `ContentVirtualizationBackendGraph_None` | 1700 | 2 | CacheStorageHierarchy, PersistentStorageHierarchy |
| `ContentVirtualizationBackendGraph_LocalCache` | 1705 | 3 | CacheStorageHierarchy, PersistentStorageHierarchy, LocalFileCache |
| `/Script/Engine.StreamingSettings` | 1710 | 18 | s.MinBulkDataSizeForAsyncLoading, s.AsyncLoadingThreadEnabled, s.EventDrivenLoaderEnabled, s.WarnIfTimeLimitExceeded, s.TimeLimitExceededMultiplier, s.TimeLimitExceededMinTime, s.UseBackgroundLevelStreaming, s.PriorityAsyncLoadingExtraTime, s.LevelStreamingActorsUpdateTimeLimit, s.PriorityLevelStrea |
| `/Script/Engine.EditorStreamingSettings` | 1730 | 3 | ParallelPreloadExclusions |
| `/Script/Engine.GarbageCollectionSettings` | 1744 | 11 | gc.MaxObjectsNotConsideredByGC, gc.NumRetriesBeforeForcingGC, gc.AllowParallelGC, gc.TimeBetweenPurgingPendingKillObjects, gc.MaxObjectsInEditor, gc.IncrementalBeginDestroyEnabled, gc.CreateGCClusters, gc.MinGCClusterSize, gc.AssetClustreringEnabled, gc.ActorClusteringEnabled, gc.VerifyUObjectsAreNo |
| `Internationalization` | 1761 | 6 | LocalizationPaths, CultureDisplayNameSubstitutes |
| `Audio` | 1770 | 23 | UnfocusedVolumeMultiplier, UseAudioThread, EnableAudioMixer, DeferStartupPrecache, AllWaveFormats, FormatModuleHints, AudioInfoModules, FallbackFormat, PlatformFormat, PlatformStreamingFormat |
| `AudioChannelAzimuthMap` | 1796 | 10 | FrontLeft, FrontRight, FrontCenter, BackLeft, BackRight, FrontLeftOfCenter, FrontRightOfCenter, BackCenter, SideLeft, SideRight |
| `AudioDefaultChannelOrder` | 1809 | 8 | FrontLeft, FrontRight, FrontCenter, LowFrequency, SideLeft, SideRight, BackLeft, BackRight |
| `/Script/Engine.AudioSettings` | 1819 | 10 | DefaultSoundClassName, DefaultMediaSoundClassName, DefaultSoundSubmixName, MasterSubmix, ReverbSubmix, EQSubmix, AmbisonicSubmix, LowPassFilterResonance, MaximumConcurrentStreams, DialogueFilenameFormat |
| `/Script/Engine.SoundGroups` | 1831 | 5 | SoundGroupProfiles |
| `/Script/Engine.Player` | 1838 | 2 | ConfiguredInternetSpeed, ConfiguredLanSpeed |
| `/Script/Engine.NetDriver` | 1842 | 4 | ChannelDefinitions |
| `/Script/Engine.RendererSettings` | 1848 | 2 | VisualizeCalibrationColorMaterialPath, VisualizeCalibrationGrayscaleMaterialPath |
| `/Script/OnlineSubsystemUtils.IpNetDriver` | 1852 | 19 | AllowPeerConnections, AllowPeerVoice, ConnectionTimeout, InitialConnectTimeout, RecentlyDisconnectedTrackingTime, TimeoutMultiplierForUnoptimizedBuilds, KeepAliveTime, MaxClientRate, MaxInternetClientRate, ServerDesiredSocketReceiveBufferBytes, ClientDesiredSocketReceiveBufferBytes, RelevantTimeout |
| `DDoSDetection` | 1873 | 10 | bDDoSDetection, bDDoSAnalytics, DDoSLogSpamLimit, HitchTimeQuotaMS, HitchFrameTolerance, DetectionSeverity |
| `DDoSDetection.Burst` | 1886 | 4 | bSendEscalateAnalytics, EscalateQuotaPacketsPerSec, EscalateQuotaDisconnPacketsPerSec, EscalateQuotaBadPacketsPerSec |
| `DDoSDetection.PersistentBurst` | 1893 | 6 | bSendEscalateAnalytics, EscalateQuotaPacketsPerSec, EscalateQuotaDisconnPacketsPerSec, EscalateQuotaBadPacketsPerSec, EscalateTimeQuotaMSPerFrame, CooloffTime |
| `DDoSDetection.DDoS` | 1902 | 5 | bSendEscalateAnalytics, EscalateTimeQuotaMSPerFrame, PacketLimitPerFrame, PacketTimeLimitMSPerFrame, CooloffTime |
| `DDoSDetection.ExpensiveDDoS` | 1910 | 5 | bSendEscalateAnalytics, EscalateTimeQuotaMSPerFrame, PacketLimitPerFrame, PacketTimeLimitMSPerFrame, CooloffTime |
| `DDoSDetection.DebilitatingDDoS` | 1918 | 4 | bSendEscalateAnalytics, PacketLimitPerFrame, NetConnPacketTimeLimitMSPerFrame, CooloffTime |
| `GameNetDriver RPCDoSDetection` | 1924 | 15 | bRPCDoSDetection, bRPCDoSAnalytics, HitchTimeQuotaMS, HitchSuspendDetectionTimeMS, InitialConnectToleranceMS, RPCBlockAllowlist, DetectionSeverity |
| `BeaconNetDriver RPCDoSDetection` | 1941 | 12 | bRPCDoSDetection, bRPCDoSAnalytics, HitchTimeQuotaMS, HitchSuspendDetectionTimeMS, InitialConnectToleranceMS, DetectionSeverity |
| `RPCDoSDetection.Normal` | 1956 | 2 | EscalateQuotaRPCsPerFrame, EscalateTimeQuotaMSPerFrame |
| `RPCDoSDetection.Hitch` | 1961 | 5 | EscalateQuotaRPCsPerPeriod, EscalateTimeQuotaMSPerPeriod, EscalateQuotaTimePeriod, CooloffTime, AutoEscalateTime |
| `RPCDoSDetection.Burst` | 1969 | 5 | EscalateQuotaRPCsPerPeriod, EscalateTimeQuotaMSPerPeriod, EscalateQuotaTimePeriod, CooloffTime, AutoEscalateTime |
| `RPCDoSDetection.PersistentBurst` | 1977 | 10 | bLogEscalate, bSendEscalateAnalytics, bTrackRecentRPCs, EscalateQuotaRPCsPerPeriod, EscalateTimeQuotaMSPerPeriod, EscalateQuotaTimePeriod, EscalationCountTolerance, EscalationTimeToleranceMS, CooloffTime, AutoEscalateTime |
| `RPCDoSDetection.DoS` | 1990 | 13 | bLogEscalate, bSendEscalateAnalytics, bTrackRecentRPCs, EscalateQuotaRPCsPerPeriod, EscalateTimeQuotaMSPerPeriod, EscalateQuotaTimePeriod, EscalationCountTolerance, EscalationTimeToleranceMS, RPCRepeatLimitPerPeriod, RPCRepeatLimitMSPerPeriod, RPCRepeatLimitTimePeriod, CooloffTime |
| `RPCDoSDetection.ExpensiveDoS` | 2006 | 12 | bLogEscalate, bSendEscalateAnalytics, bTrackRecentRPCs, EscalateQuotaRPCsPerPeriod, EscalateTimeQuotaMSPerPeriod, EscalateQuotaTimePeriod, EscalationCountTolerance, EscalationTimeToleranceMS, RPCRepeatLimitPerPeriod, RPCRepeatLimitMSPerPeriod, RPCRepeatLimitTimePeriod, CooloffTime |
| `RPCDoSDetection.Kick` | 2021 | 3 | bLogEscalate, bSendEscalateAnalytics, bKickPlayer |
| `/Script/Engine.DemoNetDriver` | 2027 | 6 | NetConnectionClassName, DemoSpectatorClass, SpawnPrioritySeconds, ChannelDefinitions |
| `TextureStreaming` | 2035 | 12 | NeverStreamOutRenderAssets, MinTextureResidentMipCount, PoolSize, MemoryMargin, MinFudgeFactor, LoadMapTimeLimit, LightmapStreamingFactor, ShadowmapStreamingFactor, MaxLightmapRadius, AllowStreamingLightmaps, UseDynamicStreaming, BoostPlayerTextures |
| `/Script/UnrealEd.EditorEngine` | 2049 | 13 | LocalPlayerClassName, GameCommandLine, FOVAngle, GodMode, UseAxisIndicator, HeightMapExportClassName, bCustomCameraAlignEmitter, CustomCameraAlignEmitterDistance, bDrawSocketsInGMode, bSmoothFrameRate, SmoothedFrameRateRange, UseOldStyleMICEditorGroups |
| `/Script/UnrealEd.UnrealEdEngine` | 2064 | 104 | AutoSaveIndex, TemplateMapInfos, PackagesToBeFullyLoadedAtStartup |
| `DevOptions.Shaders` | 2176 | 17 | bAllowCompilingThroughWorkers, bAllowAsynchronousShaderCompiling, NumUnusedShaderCompilingThreads, NumUnusedShaderCompilingThreadsDuringGame, ShaderCompilerCoreCountThreshold, PercentageUnusedShaderCompilingThreads, MaxShaderJobBatchSize, bPromptToRetryFailedShaderCompiles, bDebugBreakOnPromptToRetr |
| `ShaderCompiler` | 2218 | 6 | r.Shaders.Symbols, r.Shaders.GenerateSymbols, r.Shaders.WriteSymbols, r.Shaders.WriteSymbols.Zip, r.Shaders.SymbolPathOverride, r.Shaders.AllowUniqueSymbols |
| `ShaderCompiler_BuildMachine` | 2233 | 6 | r.Shaders.Symbols, r.Shaders.GenerateSymbols, r.Shaders.WriteSymbols, r.Shaders.WriteSymbols.Zip, r.Shaders.SymbolPathOverride, r.Shaders.AllowUniqueSymbols |
| `Rendering.AutoScreenPercentage` | 2248 | 6 | MinDisplayResolution, MinRenderingResolution, MidDisplayResolution, MidRenderingResolution, MaxDisplayResolution, MaxRenderingResolution |
| `LogFiles` | 2256 | 3 | PurgeLogsDays, MaxLogFilesOnDisk, LogTimes |
| `Kismet` | 2261 | 22 | AllowDerivedBlueprints, CompileDisplaysBinaryBackend, CompileDisplaysAnimBlueprintBackend, bTurnOffEditorConstructionScript, bLogPrintStringSource, PrintStringDuration, bUseLocalGraphVariables, bPersistentUberGraphFrame, bReinstanceOnlyWhenNecessary, bChangeDefaultValueWithoutReinstancing, bDisplays |
| `/Script/Engine.Blueprint` | 2285 | 1 | bRecompileOnLoad |
| `/Script/Engine.LevelScriptBlueprint` | 2288 | 1 | bRecompileOnLoad |
| `/Script/Engine.AnimBlueprint` | 2291 | 1 | bRecompileOnLoad |
| `CustomStats` | 2294 | 75 | LD, MEMLEAN, GameThread, Mobile, SplitScreen |
| `MemReportCommands` | 2371 | 34 | Cmd |
| `MemReportFullCommands` | 2408 | 43 | Cmd |
| `MemoryPools` | 2457 | 2 | FLightPrimitiveInteractionInitialBlockSize, PersistentAllocatorReserveSizeMB |
| `ProcessLimits` | 2461 | 1 | VirtualMemoryLimitInKB |
| `SystemSettings` | 2464 | 6 | con.DebugEarlyDefault, con.DebugEarlyCheat, con.DebugLateDefault, con.DebugLateCheat, LogNamedEventFilters |
| `SystemSettingsEditor` | 2477 | 1 | r.VSync |
| `SystemSettingsSplitScreen2` | 2483 | 0 |  |
| `OnlineSubsystem` | 2490 | 10 | bHasVoiceEnabled, VoiceNotificationDelta, MaxLocalTalkers, MaxRemoteTalkers, PollingIntervalInMs, bUseBuildIdOverride, BuildIdOverride, AdditionalModulesToLoad |
| `OnlineSubsystemSteam` | 2510 | 9 | bEnabled, SteamDevAppId, GameServerQueryPort, bInitServerOnClient, bRelaunchInSteam, GameVersion, bVACEnabled, bAllowP2PPacketRelay, P2PConnectionTimeout |
| `/Script/OnlineSubsystemSteam.SteamNetDriver` | 2521 | 1 | NetConnectionClassName |
| `/Script/SteamSockets.SteamSocketsNetDriver` | 2524 | 11 | NetConnectionClassName, ConnectionTimeout, InitialConnectTimeout, NetServerMaxTickRate, MaxNetTickRate, KeepAliveTime, MaxClientRate, MaxInternetClientRate, RelevantTimeout, SpawnPrioritySeconds, ServerTravelPause |
| `OnlineSubsystemAmazon` | 2537 | 1 | bEnabled |
| `OnlineSubsystemGoogle` | 2540 | 1 | bEnabled |
| `OnlineSubsystemGoogle.OnlineIdentityGoogle` | 2543 | 3 | LoginRedirectUrl, LoginDomains, RedirectPort |
| `OnlineSubsystemFacebook` | 2548 | 2 | bEnabled, APIVer |
| `OnlineSubsystemFacebook.OnlineIdentityFacebook` | 2552 | 5 | LoginUrl, LoginRedirectUrl, MeURL, LoginDomains, bUsePopup |
| `/Script/Engine.DataDrivenConsoleVariableSettings` | 2559 | 1 | CVarsArray |
| `OnlineSubsystemFacebook.OnlineSharingFacebook` | 2563 | 1 | PermissionsURL |
| `OnlineSubsystemFacebook.OnlineFriendsFacebook` | 2566 | 1 | FriendsUrl |
| `OnlineSubsystemSamsung` | 2569 | 1 | bEnabled |
| `OnlineSubsystemSamsung.OnlinePurchaseSamsung` | 2572 | 3 | QueryReceiptsResumeFailDelaySeconds, CheckoutResumeFailDelaySeconds, bIncludeSamsungLocText |
| `OnlineSubsystemApple` | 2577 | 1 | bEnabled |
| `/Script/OnlineSubsystemEOS.EOSSettings` | 2580 | 4 | AuthScopeFlags, bPreferPersistentAuth |
| `OnlineSubsystemNull` | 2586 | 56 | bEnabled, bAutoLoginAtStartup, bRequireLoginCredentials, bAddUserNumToNullId, bForceStableNullId, bForceOfflineMode, Achievement_0_Id, Achievement_0_bIsHidden, Achievement_0_Title, Achievement_0_LockedDesc, Achievement_0_UnlockedDesc, Achievement_1_Id |
| `/Script/OnlineSubsystemUtils.OnlineBeacon` | 2654 | 2 | BeaconConnectionInitialTimeout, BeaconConnectionTimeout |
| `/Script/OnlineSubsystemUtils.OnlineBeaconHost` | 2658 | 1 | ListenPort |
| `/Script/OnlineSubsystemUtils.PartyBeaconHost` | 2661 | 3 | bLogoutOnSessionTimeout, SessionTimeoutSecs, TravelSessionTimeoutSecs |
| `/Script/OnlineSubsystemUtils.SpectatorBeaconHost` | 2666 | 3 | bLogoutOnSessionTimeout, SessionTimeoutSecs, TravelSessionTimeoutSecs |
| `/Script/Lobby.LobbyBeaconClient` | 2671 | 2 | BeaconConnectionInitialTimeout, BeaconConnectionTimeout |
| `OnlineServices.Lobbies` | 2675 | 6 | SchemaDescriptors, SchemaCategoryDescriptors, SchemaCategoryAttributeDescriptors, SchemaAttributeDescriptors |
| `StaticMeshLODSettings` | 2683 | 7 | LevelArchitecture, SmallProp, LargeProp, Deco, Vista, Foliage, HighDetail |
| `TextureTracking` | 2692 | 0 |  |
| `RuntimeAssetCache` | 2702 | 2 | BucketConfigs, PathToRAC |
| `HybridCookedEditor` | 2706 | 3 | bIsSupported, RuntimeTargetPlatform, RuntimeServerPlatform |
| `Zen.Plugin.AndroidPortForwarder` | 2716 | 1 | Name |
| `Zen` | 2719 | 1 | AutoLaunch |
| `Zen.AutoLaunch` | 2722 | 8 | DataPath, LimitProcessLifetime, RemoteNetworkService, LocalDataCachePathEnvOverride, LocalDataCachePathCommandLineOverride, LocalDataCachePathEditorOverrideSetting, ExtraArgs, Plugins |
| `Zen.ConnectExisting` | 2732 | 2 | HostName, Port |
| `StorageServers` | 2739 | 3 | Local, Shared, Cloud |
| `DerivedDataCacheGraphs` | 2770 | 21 | Default, Installed, NoShared, NoZenLocalFallback, InstalledNoZenLocalFallback, Cold, Warm, CreateProjectPak, CreateInstalledProjectPak, CreateEnginePak, CreateInstalledEnginePak, CreateInstalledEnterprisePak |
| `DerivedDataCacheStores` | 2810 | 17 | ZenLocal, ZenShared, Cloud, Local, InstalledLocal, Shared, Pak, ProjectPak, InstalledProjectPak, EnginePak, InstalledEnginePak, EnterprisePak |
| `VirtualTextureChunkDDCCache` | 2890 | 3 | UnusedFileAge, MaxFileChecksPerSec, Path |
| `DDCCleanup` | 2895 | 2 | TimeToWaitAfterInit, MaxFileChecksPerSec |
| `/Script/Engine.LocalPlayer` | 2899 | 1 | AspectRatioAxisConstraint |
| `ContentComparisonReferenceTypes` | 2902 | 6 | Class |
| `AssetRegistry` | 2910 | 39 | CookedTagsBlacklist, bUseAssetRegistryTagsWhitelistInsteadOfBlacklist, CookedTagsWhitelist, CookedTagsAsFName, CookedTagsAsPathName, bSerializeAssetRegistry, bSerializeDependencies, bSerializeSearchableNameDependencies, bSerializeManageDependencies, bSerializePackageData, bFilterAssetDataWithNoTags, |
| `AutomationTesting` | 2994 | 3 | ImportTestPath, ImportTestPackagePath, bForceSmokeTests |
| `AutomationTesting.FbxImport` | 2999 | 3 | FbxImportTestPath, FbxImportEditorTestPath, FbxImportTestPackagePath |
| `AutomationTesting.Blueprint` | 3004 | 4 | TestAllBlueprints, InstanceTestMaps, ReparentTest.ChildrenPackagePaths, ReparentTest.ParentsPackagePaths |
| `/Script/Engine.AutomationTestSettings` | 3010 | 6 | EditorTestModules, TestLevelFolders, MaterialEditorPromotionTest |
| `AutomationTesting.StaticMeshEditorTest` | 3018 | 14 | EditorViewButtons, EditorViewButtonsObject, DefaultInteractiveFramerate, DefaultInteractiveFramerateWaitTime, DefaultInteractiveFramerateDuration |
| `/Script/NavigationSystem.NavigationSystemV1` | 3038 | 2 | bAutoCreateNavigationData, bAddPlayersToGenerationSeeds |
| `/Script/NavigationSystem.NavigationData` | 3042 | 1 | RuntimeGeneration |
| `/Script/NavigationSystem.RecastNavMesh` | 3045 | 18 | TileSetUpdateInterval, MaxTileGridWidth, MaxTileGridHeight, DefaultDrawDistance, TileSizeUU, CellSize, CellHeight, NavMeshResolutionParams[0], NavMeshResolutionParams[1], NavMeshResolutionParams[2], AgentRadius, AgentHeight |
| `/Script/NavigationSystem.NavArea_Null` | 3068 | 1 | DrawColor |
| `/Script/NavigationSystem.NavArea_Default` | 3071 | 1 | DrawColor |
| `Trace.ChannelPresets` | 3074 | 4 | Rendering, Loading, TaskGraph, ContextSwitching |
| `RemoteConfiguration` | 3080 | 6 | Enabled, ConfigPathPrefix, ConfigPathSuffix, Timeout, IniToLoad |
| `Engine.ErrorHandling` | 3088 | 2 | bPromptForRemoteDebugging, bPromptForRemoteDebugOnEnsure |
| `Niagara` | 3092 | 1 | EnableNiagara |
| `/Script/Engine.Actor` | 3095 | 1 | DefaultUpdateOverlapsMethodDuringLevelStreaming |
| `/Script/Engine.TriggerVolume` | 3099 | 1 | DefaultUpdateOverlapsMethodDuringLevelStreaming |
| `/Script/Engine.CollisionProfile` | 3102 | 33 | Profiles, OldProfiles, ProfileRedirects, CollisionChannelRedirects |
| `Engine.BufferVisualizationMaterials` | 3140 | 24 | BaseColor, CustomDepth, CustomStencil, FinalImage, ShadingModel, MaterialAO, Metallic, Opacity, Roughness, Anisotropy, SceneColor, SceneDepth |
| `DeviceProfileManager` | 3166 | 1 | DeviceProfileSelectionModule |
| `SlateRenderer` | 3169 | 5 | TextureAtlasSize, GrayscaleFontAtlasSize, ColorFontAtlasSize, SdfFontAtlasSize, NumPreallocatedVertices |
| `MobileSlateUI` | 3178 | 1 | bTouchFallbackToMouse |
| `Pak` | 3181 | 19 | bDoUseOodleDespiteNoPluginCompression, ExtensionsToNotUsePluginCompression, FileNamesToNotUsePluginCompression, DirectoryIndexKeepFiles, DirectoryIndexKeepEmptyDirectories, IndexValidationIgnore |
| `/Script/GameplayDebugger.GameplayDebuggingReplicator` | 3203 | 4 | MaxEQSQueries, DebugComponentClassName, DebugComponentHUDClassName, DebugComponentControllerClassName |
| `/Script/GameplayDebugger.GameplayDebuggingHUDComponent` | 3209 | 4 | MenuStartX, MenuStartY, DebugInfoStartX, DebugInfoStartY |
| `/Script/IOSRuntimeSettings.IOSRuntimeSettings` | 3217 | 56 | bEnableStoreKitSupport, bEnableGameCenterSupport, bSupportsPortraitOrientation, bSupportsITunesFileSharing, bSupportsUpsideDownOrientation, bSupportsLandscapeLeftOrientation, bSupportsLandscapeRightOrientation, PreferredLandscapeOrientation, bSupportsMetal, bSupportHighRefreshRates, bGameSupportsMul |
| `/Script/AndroidRuntimeSettings.AndroidRuntimeSettings` | 3276 | 72 | SDKAPILevelOverride, NDKAPILevelOverride, BuildToolsOverride, bEnableGooglePlaySupport, bSupportAdMob, bBuildForArm64, bBuildForX8664, bBuildForES31, bSupportsVulkan, bSupportsVulkanSM5, bForceEmulatorProfileSelectionInNonShippingBuilds, bDetectVulkanByDefault |
| `/Script/AndroidPlatformEditor.AndroidSDKSettings` | 3350 | 2 | SDKAPILevel, NDKAPILevel |
| `/Script/UnrealEd.CookerSettings` | 3354 | 42 | DefaultASTCQualityBySpeed, DefaultASTCQualityBySize, DefaultASTCQualityBySizeHQ, ClassesExcludedOnDedicatedServer, ClassesExcludedOnDedicatedClient, VersionedIntRValues |
| `/Script/CoreUObject.ChunkDependencyInfo` | 3401 | 0 |  |
| `/Script/Engine.PhysicsSettings` | 3406 | 2 | DefaultGravityZ, bEnable2DPhysics |
| `/Script/WindowsTargetPlatform.WindowsTargetSettings` | 3410 | 16 | D3D12TargetedShaderFormats, D3D11TargetedShaderFormats, bEnableDistanceFields, RayTracingMode, bTarget32Bit, CacheSizeKB, MaxSampleRate, HighSampleRate, MedSampleRate, LowSampleRate, MinSampleRate, CompressionQualityModifier |
| `/Script/LinuxTargetPlatform.LinuxTargetSettings` | 3428 | 2 | TargetedRHIs, RayTracingMode |
| `/Script/MacTargetPlatform.MacTargetSettings` | 3432 | 17 | MetalLanguageVersion, TargetedRHIs, UseFastIntrinsics, EnableMathOptimisations, StripIndividualMetalLibs, TargetArchitecture, EditorTargetArchitecture, EditorDefaultArchitecture, DefaultArchitecture, bBuildAllSupportedOnBuildMachine, AudioSampleRate, AudioCallbackBufferFrameSize |
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 3451 | 16 | bUseAutomaticCodeSigning, bMacSignToRunLocally, bUsePremadeDSYMInXcArchive, CodeSigningTeam, CodeSigningPrefix, BundleIdentifier, AppCategory, TemplateMacPlist, TemplateIOSPlist, PremadeMacEntitlements, ShippingSpecificMacEntitlements, bUseEntitlementsForPrograms |
| `AutomationTestExcludelistSettings:Windows` | 3471 | 4 | SupportedRHIs |
| `AutomationTestExcludelistSettings:Linux` | 3477 | 2 | SupportedRHIs |
| `AutomationTestExcludelistSettings:Mac` | 3481 | 2 | SupportedRHIs |
| `HMDPluginPriority` | 3485 | 3 | OculusHMD, SteamVR, OpenXRHMD |
| `/Script/OculusHMD.OculusHMDRuntimeSettings` | 3493 | 1 | XrApi |
| `/Script/Engine.AISystemBase` | 3496 | 2 | AISystemModuleName, AISystemClassName |
| `/Script/AIModule.AISystem` | 3500 | 1 | PerceptionSystemClassName |
| `AutomationController.History` | 3503 | 2 | bTrackHistory, NumberOfHistoryItemsTracked |
| `VisualLogger` | 3507 | 2 | FrameCacheLenght, UseCompression |
| `GameplayDebuggerSettings` | 3511 | 16 | OverHead, Basic, BehaviorTree, EQS, EnableEQSOnHUD, Perception, GameView1, GameView2, GameView3, GameView4, GameView5, NameForGameView1 |
| `Browser` | 3529 | 1 | bForceMessageLoop |
| `PacketSimulationProfile.Off` | 3532 | 6 | PktLoss, PktIncomingLoss, PktLagMin, PktLagMax, PktIncomingLagMin, PktIncomingLagMax |
| `PacketSimulationProfile.Average` | 3541 | 6 | PktLoss, PktIncomingLoss, PktLagMin, PktLagMax, PktIncomingLagMin, PktIncomingLagMax |
| `PacketSimulationProfile.Bad` | 3550 | 6 | PktLoss, PktIncomingLoss, PktLagMin, PktLagMax, PktIncomingLagMin, PktIncomingLagMax |
| `PacketSimulationProfile.BufferBloat` | 3559 | 8 | PktLoss, PktIncomingLoss, PktLagMin, PktLagMax, PktIncomingLagMin, PktIncomingLagMax, PktBufferBloatInMS, PktIncomingBufferBloatInMS |
| `/Script/Engine.NetworkSettings` | 3570 | 3 | NetworkEmulationProfiles |
| `PacketHandlerComponents` | 3575 | 0 |  |
| `/Script/GameplayDebugger.GameplayDebuggingControllerComponent` | 3579 | 14 | CategoryZeroBind, CategoryOneBind, CategoryTwoBind, CategoryThreeBind, CategoryFourBind, CategoryFiveBind, CategorySixBind, CategorySevenBind, CategoryEightBind, CategoryNineBind, CycleDetailsViewBind, DebugCameraBind |
| `/Script/GameFeatures.GameFeatureAction_AddChunkOverride` | 3595 | 1 | LowestAllowedChunkIndexForAutoGeneration |
| `/Script/Engine.SkeletalMeshLODSettings` | 3598 | 4 | LODGroups |
| `/Script/Engine.PlayerCameraManager` | 3604 | 1 | ServerUpdateCameraTimeout |
| `/Script/CinematicCamera.CineCameraSettings` | 3607 | 31 | FilmbackPresets, DefaultFilmbackPreset, LensPresets, DefaultLensPresetName, CropPresets, DefaultCropPresetName, DefaultLensFocalLength, DefaultLensFStop |
| `/Script/TcpMessaging.TcpMessagingSettings` | 3640 | 4 | EnableTransport, ListenEndpoint, ConnectToEndpoints, ConnectionRetryDelay |
| `CrashReportClient` | 3646 | 7 | bHideLogFilesOption, bHideAllowToBeContactedOption, bIsAllowedToCloseWithoutSending, bIsAllowedToSendWithoutDetailedInfo, CrashConfigPurgeDays, Stall.RecordDump, Ensure.RecordDump |
| `SteamVR.Settings` | 3655 | 1 | HMDWornMovementThreshold |
| `/Script/Engine.AnimationSettings` | 3658 | 2 | bStripAnimationDataOnDedicatedServer, BoneTimecodeCustomAttributeNameSettings |
| `Animation.DefaultObjectSettings` | 3662 | 7 | BoneCompressionSettingsFallback, BoneCompressionSettings, AnimationRecorderBoneCompressionSettingsFallback, AnimationRecorderBoneCompressionSettings, CurveCompressionSettingsFallback, CurveCompressionSettings, VariableFrameStrippingSettings |
| `/Script/Engine.MeshSimplificationSettings` | 3677 | 1 | r.MeshReductionModule |
| `/Script/ClassViewer.ClassViewerProjectSettings` | 3680 | 5 | InternalOnlyPaths, InternalOnlyClasses |
| `/Script/ClassViewer.StructViewerProjectSettings` | 3687 | 3 | InternalOnlyPaths |
| `/Script/LevelSequence.LevelSequence` | 3692 | 1 | DefaultCompletionMode |
| `/Script/TemplateSequence.TemplateSequence` | 3695 | 1 | DefaultCompletionMode |
| `/Script/MovieSceneAnimMixer.MovieSceneAnimMixerSettings` | 3698 | 1 | DefaultUAFModule |
| `PlatformCrypto` | 3701 | 3 | PlatformRequiresDataCrypto, PakSigningRequired, PakEncryptionRequired |
| `/Script/AppleARKit.AppleARKitSettings` | 3706 | 3 | bEnableLiveLinkForFaceTracking, LiveLinkPublishingPort, bRequireDeviceSupportsARKit |
| `/Script/Engine.RendererSettings` | 3713 | 2 | r.GPUCrashDebugging, MaxSkinBones |
| `Messaging` | 3717 | 1 | bAllowDelayedMessaging |
| `/Script/ChaosSolverEngine.ChaosSolverSettings` | 3720 | 1 | DefaultChaosSolverActorClass |
| `PlatformPaths` | 3723 | 1 | UnrealBuildTool |
| `AlternateTextureCompression` | 3726 | 1 | TextureCompressionFormat |
| `TextureFormatOodleSettings` | 3729 | 4 | bDebugColor, DebugDumpFilter, LogVerbosity, GlobalLambdaMultiplier |
| `/Script/Engine.TextureEncodingProjectSettings` | 3740 | 10 | bFinalUsesRDO, FinalRDOLambda, FinalEffortLevel, FinalUniversalTiling, bFastUsesRDO, FastRDOLambda, FastEffortLevel, FastUniversalTiling, CookUsesSpeed, EditorUsesSpeed |
| `OodleDataCompressionFormat` | 3752 | 1 | PreallocatedBufferCount |
| `Plugins` | 3757 | 1 | ConfigFilesPluginsCannotOverride |
| `ClothSettings` | 3760 | 3 | EnvironmentCollisionPadding, EnvironmentCollisionThickness, EnvironmentCollisionMaxShapes |
| `BuildPatchServices` | 3768 | 1 | bEnableDiskOverflowStore |
| `/Script/Engine.BlueprintGeneratedClass` | 3772 | 1 | RequiresCompleteValueForPostConstruction |
| `Ias` | 3778 | 3 | EnableInEditor, CreatePerContainerTocs, UsePerContainerTocs |
| `/Script/InterchangeEngine.InterchangeProjectSettings` | 3784 | 6 | ContentImportSettings, SceneImportSettings, FilePickerClass, bStaticMeshUseSmoothEdgesIfSmoothingInformationIsMissing, GenericPipelineClass, ConverterDefaultPipeline |
| `/Script/Engine.NetworkMetricsLog` | 3792 | 1 | IntervalSeconds |
| `/Script/Engine.NetworkMetricsCSV_Replication` | 3795 | 1 | IntervalSeconds |
| `/Script/Engine.NetworkMetricsPerfCounters` | 3798 | 1 | IntervalSeconds |
| `/Script/Engine.NetworkMetricsConfig` | 3801 | 73 | Listeners |
| `StudioTelemetry.Config` | 3877 | 4 | SendTelemetry, SendUserData, SendHardwareData, SendOSData |
| `StudioTelemetry.Provider.Log` | 3886 | 6 | Name, Enabled, ProviderModule, UsageType, FileName, FolderPath |
| `StudioTelemetry.Provider.CSV` | 3897 | 5 | Name, Enabled, ProviderModule, UsageType, FolderPath |
| `StudioTelemetry.Provider.Horde` | 3908 | 7 | Name, ProviderModule, Enabled, UsageType, APIKeyET, APIServerET, APIEndpointET |
| `/Script/Engine.WorldPartitionSettings` | 3951 | 4 | EditorHashDefaultClass, RuntimeHashDefaultClass, UnsupportedActorClassesPerHLODLayerType, bShouldEDLPackagesInheritWorldChunkAssignmentsDuringCook |
| `/Script/Engine.WorldPartitionRuntimeCellTransformerSettings` | 3957 | 2 | IgnoredComponentClasses, IgnoredExactComponentClasses |
| `BuildPatchTool` | 3961 | 1 | VerificationThreadCount |
| `/Script/ControlRig.ControlRigSettings` | 3964 | 1 | DefaultRootModule |
| `/Script/MSGamingSupport.MSGamingSettings` | 3967 | 1 | bUseSimplifiedUserModel |
| `/Script/Engine.PSOPrecacheSettingsManager` | 3970 | 8 | Settings |
| `/Script/Hotfix.OnlineHotfixManager` | 3983 | 7 | HotfixableAssetClasses |
| `/Script/DownlinkBandwidthManager.DownlinkBandwidthManagerConfig` | 3992 | 2 | RolloutPercentage, EnforceDistributionAllocation |

### `Config/BaseGame.ini` — 29 sections, 232 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 5 | 2 | Section |
| `Internationalization` | 9 | 1 | LocalizationPaths |
| `DefaultPlayer` | 16 | 1 | Name |
| `/Script/Engine.GameNetworkManager` | 19 | 28 | TotalNetBandwidth, MaxDynamicBandwidth, MinDynamicBandwidth, MoveRepSize, MAXPOSITIONERRORSQUARED, MAXNEARZEROVELOCITYSQUARED, CLIENTADJUSTUPDATECOST, MAXCLIENTUPDATEINTERVAL, MaxClientForcedUpdateDuration, ServerForcedUpdateHitchThreshold, ServerForcedUpdateHitchCooldown, MaxMoveDeltaTime |
| `/Script/Party.Party` | 49 | 1 | DefaultMaxPartySize |
| `/Script/Party.SocialSettings` | 52 | 10 | SocialPlatformDescriptions |
| `/Script/Lobby.LobbyBeaconState` | 64 | 1 | WaitForPlayersTimeRemaining |
| `/Script/Engine.GameSession` | 67 | 4 | MaxPlayers, MaxSpectators, MaxSplitscreensPerConnection, bRequiresPushToTalk |
| `/Script/EngineSettings.GeneralProjectSettings` | 73 | 12 | CompanyName, CompanyDistinguishedName, CopyrightNotice, Description, LicensingTerms, PrivacyPolicy, ProjectName, ProjectVersion, Homepage, SupportContact, MinWindowWidth, MinWindowHeight |
| `/Script/UnrealEd.ProjectPackagingSettings` | 87 | 79 | EngineCustomBuilds, ProjectCustomBuilds, Build, BuildConfiguration, FullRebuild, UsePakFile, bUseIoStore, bUseZenStore, bCompressed, PackageCompressionFormat, PackageCompressionMethod, PackageCompressionLevel_Distribution |
| `/Script/DeveloperToolSettings.PlatformsMenuSettings` | 175 | 5 | StagingDirectory, LaunchOnTarget, PerPlatformBuildConfig, PerPlatformTargetFlavorName, PerPlatformBuildTarget |
| `/Script/Engine.HUD` | 182 | 1 | DebugDisplay |
| `/Script/Engine.PlayerController` | 185 | 4 | InputYawScale, InputPitchScale, InputRollScale, ForceFeedbackScale |
| `/Script/Engine.DebugCameraController` | 191 | 1 | bShowSelectedInfo |
| `/Script/Engine.WorldSettings` | 194 | 9 | ChanceOfPhysicsChunkOverride, bEnableChanceOfPhysicsChunkOverride, DefaultAmbientZoneSettings, MinUndilatedFrameTime, MaxUndilatedFrameTime, MinGlobalTimeDilation, MaxGlobalTimeDilation, MinCinematicTimeDilation, MaxCinematicTimeDilation |
| `/Script/AIModule.AIPerceptionComponent` | 205 | 4 | HearingRange, SightRadius, LoseSightRadius, PeripheralVisionAngle |
| `/Script/AIModule.AISense_Hearing` | 211 | 1 | SpeedOfSoundSq |
| `/Script/AIModule.AISenseConfig_Hearing` | 214 | 3 | Implementation, HearingRange, DetectionByAffiliation |
| `/Script/AIModule.AISenseConfig_Sight` | 219 | 6 | Implementation, SightRadius, LoseSightRadius, PeripheralVisionAngleDegrees, DetectionByAffiliation, AutoSuccessRangeFromLastSeenLocation |
| `/Script/AIModule.AISenseConfig_Damage` | 227 | 1 | Implementation |
| `/Script/AIModule.EnvQueryManager` | 230 | 4 | MaxAllowedTestingTime, bTestQueriesUsingBreadth, QueryCountWarningThreshold, QueryCountWarningInterval |
| `/Script/LiveLink.LiveLinkSettings` | 236 | 2 | FrameInterpolationProcessor, DefaultRoleSettings |
| `/Script/SubtitlesAndClosedCaptions.SubtitlesSettings` | 240 | 2 | SubtitleWidgetToUse, SubtitleWidgetToUseDefault |
| `/Script/Engine.AssetManagerSettings` | 244 | 3 | PrimaryAssetTypesToScan |
| `ShaderPipelineCache.CacheFile` | 257 | 0 |  |
| `Staging` | 260 | 0 |  |
| `CookedEditorSettings` | 269 | 30 | EngineAssetPaths, ProjectAssetPaths, DisallowedObjectClassesToLoad, DisallowedAssetClassesToGather, DisallowedPathsToGather, EngineExtraStageFiles, bStageShaderDirs, bStagePlatformBuildDirs, bStageExtrasDirs, bStagePlatformDirs, bStageUAT, bIsForExternalDistribution |
| `CookedEditorSettings_CookedEditor` | 314 | 12 | MapMode, DisabledPlugins, DisabledPluginsInShipping, EngineExtraStageFiles, ProjectExtraStageFiles |
| `CookedEditorSettings_CookedCooker` | 335 | 5 | MapMode, EngineExtraStageFiles, ProjectExtraStageFiles |

### `Config/BaseGameUserSettings.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Internationalization` | 1 | 1 | ShouldUseLocalizedNumericInput |

### `Config/BaseHardware.ini` — 6 sections, 33 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `GPU_NVIDIA Windows` | 40 | 15 | SuggestedDriverVersion, DriverDenyList, SuggestedDriverList |
| `GPU_NVIDIA Linux` | 66 | 2 | SuggestedDriverVersion, DriverDenyList |
| `GPU_AMD Windows` | 82 | 4 | SuggestedDriverVersion, DriverDenyList, SuggestedDriverList |
| `GPU_AMD Linux` | 95 | 2 | SuggestedDriverVersion, DriverDenyList |
| `GPU_Intel Windows` | 104 | 8 | SuggestedDriverList, DriverDenyList, SuggestedDriverVersion |
| `GPU_Intel Linux` | 125 | 2 | SuggestedDriverVersion, DriverDenyList |

### `Config/BaseInput.ini` — 6 sections, 234 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | Section |
| `/Script/Engine.InputSettings` | 4 | 23 | bEnableMouseSmoothing, bEnableFOVScaling, FOVScale, DoubleClickTime, DefaultTouchInterface, bAlwaysShowTouchInterface, bShowConsoleOnFourFingerTap, bAltEnterTogglesFullscreen, bF11TogglesFullscreen, bRequireCtrlToNavigateAutoComplete, bEnableGestureRecognizer, ConsoleKeys |
| `/Script/Engine.PlayerInput` | 34 | 17 | DebugExecBindings |
| `/Script/Engine.Console` | 56 | 1 | HistoryBot |
| `/Script/EngineSettings.ConsoleSettings` | 59 | 190 | MaxScrollbackSize, AutoCompleteMapPaths, ManualAutoCompleteList, BackgroundOpacityPercentage, InputColor, HistoryColor, AutoCompleteCommandColor, AutoCompleteCVarColor, AutoCompleteFadedColor |
| `/Script/EnhancedInput.EnhancedInputDeveloperSettings` | 258 | 2 | DefaultMappingContextInputModeQuery, DefaultInputMode |

### `Config/BaseInstallBundle.ini` — 2 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InstallBundleDefinition FilterGlobals` | 4 | 3 | Tags, FileRegex, Order |
| `InstallBundleSource.Bulk.MiscSettings` | 9 | 2 | bShouldSerializeMissingBulkBuildDataIni, bOnlyGatherPaksInBulkData |

### `Config/BaseLightmass.ini` — 17 sections, 215 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DevOptions.StaticLighting` | 14 | 21 | bAllowMultiThreadedStaticLighting, ViewSingleBounceNumber, bUseBilinearFilterLightmaps, bCompressLightmaps, bUseConservativeTexelRasterization, bAccountForTexelSize, bUseMaxWeight, MaxTriangleLightingSamples, MaxTriangleIrradiancePhotonCacheSamples, bAllow64bitProcess, DefaultStaticMeshLightingRes,  |
| `DevOptions.StaticLightingSceneConstants` | 39 | 9 | StaticLightingLevelScale, VisibilityRayOffsetDistance, VisibilityNormalOffsetDistance, VisibilityNormalOffsetSampleRadiusScale, VisibilityTangentOffsetSampleRadiusScale, SmallestTexelRadius, LightGridSize, AutomaticImportanceVolumeExpandBy, MinimumImportanceVolumeExtentWithoutWarning |
| `DevOptions.StaticLightingMaterial` | 51 | 10 | bUseDebugMaterial, ShowMaterialAttribute, EmissiveSampleSize, DiffuseSampleSize, SpecularSampleSize, TransmissionSampleSize, NormalSampleSize, TerrainSampleScalar, DebugDiffuse, EnvironmentColor |
| `DevOptions.MeshAreaLights` | 65 | 7 | bVisualizeMeshAreaLightPrimitives, EmissiveIntensityThreshold, MeshAreaLightGridSize, MeshAreaLightSimplifyNormalAngleThreshold, MeshAreaLightSimplifyCornerDistanceThreshold, MeshAreaLightSimplifyMeshBoundingRadiusFractionThreshold, MeshAreaLightGeneratedDynamicLightSurfaceOffset |
| `DevOptions.PrecomputedDynamicObjectLighting` | 75 | 12 | bVisualizeVolumeLightSamples, bVisualizeVolumeLightInterpolation, NumHemisphereSamplesScale, SurfaceLightSampleSpacing, FirstSurfaceSampleLayerHeight, SurfaceSampleLayerHeightSpacing, NumSurfaceSampleLayers, DetailVolumeSampleSpacing, VolumeLightSampleSpacing, MaxVolumeSamples, bUseMaxSurfaceSampleN |
| `DevOptions.VolumetricLightmaps` | 91 | 10 | BrickSize, MaxRefinementLevels, VoxelizationCellExpansionForSurfaceGeometry, VoxelizationCellExpansionForVolumeGeometry, VoxelizationCellExpansionForLights, TargetNumVolumetricLightmapTasks, MinBrickError, SurfaceLightmapMinTexelsPerVoxelAxis, bCullBricksBelowLandscape, LightBrightnessSubdivideThres |
| `DevOptions.PrecomputedVisibility` | 104 | 13 | bVisualizePrecomputedVisibility, bCompressVisibilityData, bPlaceCellsOnOpaqueOnly, NumCellDistributionBuckets, CellRenderingBucketSize, NumCellRenderingBuckets, PlayAreaHeight, MeshBoundsScale, VisibilitySpreadingIterations, MinMeshSamples, MaxMeshSamples, NumCellSamples |
| `DevOptions.PrecomputedVisibilityModeratelyAggressive` | 119 | 2 | MeshBoundsScale, VisibilitySpreadingIterations |
| `DevOptions.PrecomputedVisibilityMostAggressive` | 123 | 2 | MeshBoundsScale, VisibilitySpreadingIterations |
| `DevOptions.VolumeDistanceField` | 127 | 4 | VoxelSize, VolumeMaxDistance, NumVoxelDistanceSamples, MaxVoxels |
| `DevOptions.StaticShadows` | 134 | 15 | bUseZeroAreaLightmapSpaceFilteredLights, NumShadowRays, NumPenumbraShadowRays, NumBounceShadowRays, bFilterShadowFactor, ShadowFactorGradientTolerance, bAllowSignedDistanceFieldShadows, MaxTransitionDistanceWorldSpace, ApproximateHighResTexelsPerMaxTransitionDistance, MinDistanceFieldUpsampleFactor, |
| `DevOptions.ImportanceTracing` | 153 | 10 | bUseStratifiedSampling, NumHemisphereSamples, MaxHemisphereRayAngle, NumAdaptiveRefinementLevels, AdaptiveBrightnessThreshold, AdaptiveFirstBouncePhotonConeAngle, AdaptiveSkyVarianceThreshold, bUseRadiositySolverForSkylightMultibounce, bCacheFinalGatherHitPointsForRadiosity, bUseRadiositySolverForLi |
| `DevOptions.PhotonMapping` | 165 | 33 | bUsePhotonMapping, bUseFinalGathering, bUsePhotonDirectLightingInFinalGather, bVisualizeCachedApproximateDirectLighting, bUseIrradiancePhotons, bCacheIrradiancePhotonsOnSurfaces, bVisualizePhotonPaths, bVisualizePhotonGathers, bVisualizePhotonImportanceSamples, bVisualizeIrradiancePhotonCalculation, |
| `DevOptions.IrradianceCache` | 206 | 13 | bAllowIrradianceCaching, bUseIrradianceGradients, bShowGradientsOnly, bVisualizeIrradianceSamples, RecordRadiusScale, InterpolationMaxAngle, PointBehindRecordMaxAngle, DistanceSmoothFactor, AngleSmoothFactor, SkyOcclusionSmoothnessReduction, MaxRecordRadius, CacheTaskSize |
| `DevOptions.StaticLightingMediumQuality` | 224 | 18 | NumShadowRaysScale, NumPenumbraShadowRaysScale, ApproximateHighResTexelsPerMaxTransitionDistanceScale, MinDistanceFieldUpsampleFactor, NumHemisphereSamplesScale, NumImportanceSearchPhotonsScale, NumDirectPhotonsScale, DirectPhotonSearchDistanceScale, NumIndirectPhotonPathsScale, NumIndirectPhotonsSc |
| `DevOptions.StaticLightingHighQuality` | 244 | 18 | NumShadowRaysScale, NumPenumbraShadowRaysScale, ApproximateHighResTexelsPerMaxTransitionDistanceScale, MinDistanceFieldUpsampleFactor, NumHemisphereSamplesScale, NumImportanceSearchPhotonsScale, NumDirectPhotonsScale, DirectPhotonSearchDistanceScale, NumIndirectPhotonPathsScale, NumIndirectPhotonsSc |
| `DevOptions.StaticLightingProductionQuality` | 264 | 18 | NumShadowRaysScale, NumPenumbraShadowRaysScale, ApproximateHighResTexelsPerMaxTransitionDistanceScale, MinDistanceFieldUpsampleFactor, NumHemisphereSamplesScale, NumImportanceSearchPhotonsScale, NumDirectPhotonsScale, DirectPhotonSearchDistanceScale, NumIndirectPhotonPathsScale, NumIndirectPhotonsSc |

### `Config/BaseMaterialExpressions.ini` — 278 sections, 584 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.MaterialExpressionBentNormalCustomOutput` | 3 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionClearCoatNormalCustomOutput` | 6 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTangentOutput` | 9 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionThinTranslucentMaterialOutput` | 12 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFirstPersonOutput` | 15 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeGrassOutput` | 18 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeLayerBlend` | 21 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeLayerCoords` | 24 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeLayerSample` | 27 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeLayerSwitch` | 30 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeLayerWeight` | 33 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapePhysicalMaterialOutput` | 36 | 1 | MenuCategories |
| `/Script/Landscape.MaterialExpressionLandscapeVisibilityMask` | 39 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionAbs` | 42 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionAbsorptionMediumMaterialOutput` | 45 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionActorPositionWS` | 48 | 3 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionAdd` | 53 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureSample` | 56 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureSampleParameter2D` | 59 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionAntialiasedTextureMask` | 63 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionAppendVector` | 66 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionArccosine` | 70 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArccosineFast` | 73 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArcsine` | 76 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArcsineFast` | 79 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArctangent` | 82 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArctangent2` | 85 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArctangent2Fast` | 88 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionArctangentFast` | 91 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionAtmosphericFogColor` | 94 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionAtmosphericLightColor` | 98 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionAtmosphericLightVector` | 102 | 3 | MenuCategories, bShaderInputData, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionBindlessSwitch` | 107 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionBlackBody` | 110 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionBlendMaterialAttributes` | 113 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionLegacyBlendMaterialAttributes` | 116 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionBounds` | 120 | 14 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionBreakMaterialAttributes` | 136 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionBumpOffset` | 139 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCameraPositionWS` | 142 | 3 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionCameraVectorWS` | 147 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionCeil` | 152 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionComment` | 155 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionVectorParameter` | 158 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionChannelMaskParameter` | 161 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionClamp` | 165 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCloudSampleAttribute` | 168 | 5 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionCollectionParameter` | 175 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCollectionTransform` | 178 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionColorRamp` | 181 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionComponentMask` | 184 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionComposite` | 188 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionConstant` | 191 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionConstant2Vector` | 194 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionConstant3Vector` | 198 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionConstant4Vector` | 202 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionConstantBiasScale` | 206 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCosine` | 209 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCrossProduct` | 212 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionScalarParameter` | 216 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCurveAtlasRowParameter` | 219 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionCustom` | 222 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDataDrivenShaderPlatformInfoSwitch` | 225 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDBufferTexture` | 228 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionDDX` | 232 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDDY` | 235 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDecalColor` | 238 | 3 | MenuCategories, bShaderInputData, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionDecalDerivative` | 243 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionDecalLifetimeOpacity` | 247 | 3 | MenuCategories, bShaderInputData, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionDecalMipmapLevel` | 252 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionDeltaTime` | 256 | 3 | MenuCategories, bShaderInputData, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionDepthFade` | 261 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionDepthOfFieldFunction` | 265 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionDeriveNormalZ` | 269 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDesaturation` | 272 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionDistance` | 276 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDistanceCullFade` | 279 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionDistanceFieldApproxAO` | 283 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDistanceFieldGradient` | 286 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDistanceFieldsRenderingSwitch` | 289 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDistanceToNearestSurface` | 292 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDivide` | 295 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDotProduct` | 298 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionDoubleVectorParameter` | 302 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionDynamicParameter` | 305 | 3 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionExponential` | 310 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionExponential2` | 313 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionEyeAdaptation` | 318 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionEyeAdaptationInverse` | 323 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionFeatureLevelSwitch` | 328 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFloatToUInt` | 331 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionUIntToFloat` | 334 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFloor` | 337 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFmod` | 340 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFontSample` | 343 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionFontSampleParameter` | 347 | 4 | MenuCategories |
| `/Script/Engine.MaterialExpressionFontSignedDistance` | 353 | 3 | MenuCategories, ExternalCodeIdentifiers, Caption |
| `/Script/Engine.MaterialExpressionFrac` | 358 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFresnel` | 361 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFunctionInput` | 364 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionFunctionOutput` | 367 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionConstantDouble` | 370 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionGetMaterialAttributes` | 373 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionGIReplace` | 376 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionHairAttributes` | 379 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionHairColor` | 382 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionHsvToRgb` | 385 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionIf` | 388 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionIfThenElse` | 391 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionInverseLinearInterpolate` | 394 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionIsFirstPerson` | 398 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionIsOrthographic` | 404 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionLength` | 409 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionLightmapUVs` | 412 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionLightmassReplace` | 417 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionLightVector` | 420 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionLinearInterpolate` | 424 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionLocalPosition` | 428 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionLogarithm` | 432 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionLogarithm10` | 435 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionLogarithm2` | 438 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMakeMaterialAttributes` | 441 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMapARPassthroughCameraUV` | 444 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMaterialAttributeLayers` | 447 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionMaterialFunctionCall` | 451 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMaterialProxyReplace` | 454 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMax` | 457 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMeshPaintTextureCoordinateIndex` | 460 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionMeshPaintTextureObject` | 464 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionMeshPaintTextureReplace` | 468 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMin` | 471 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionModulo` | 474 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionMultiply` | 477 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionNamedRerouteDeclaration` | 480 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionNaniteReplace` | 483 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionNeuralNetworkInput` | 486 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionNeuralNetworkOutput` | 489 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionNoise` | 493 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionScalarBlueNoise` | 496 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionNormalize` | 500 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionObjectBounds` | 504 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionObjectLocalBounds` | 509 | 6 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionObjectOrientation` | 517 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionObjectPositionWS` | 523 | 3 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionObjectRadius` | 528 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionOneMinus` | 533 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionPanner` | 536 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionParticleColor` | 539 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleDirection` | 545 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleMacroUV` | 551 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleMotionBlurFade` | 556 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticlePositionWS` | 562 | 6 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleRadius` | 570 | 4 | MenuCategories, bShaderInputData, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionParticleRandom` | 576 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleRelativeTime` | 582 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleSize` | 588 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleSpeed` | 594 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleSpriteRotation` | 600 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionParticleSubUV` | 606 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionParticleSubUVProperties` | 610 | 6 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPathTracingBufferTexture` | 618 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionPathTracingQualitySwitch` | 622 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionPathTracingRayTypeSwitch` | 625 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionPerInstanceCustomData` | 628 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPerInstanceCustomData3Vector` | 633 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPerInstanceFadeAmount` | 638 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPerInstanceRandom` | 643 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPinBase` | 648 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionPixelDepth` | 651 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPixelNormalWS` | 656 | 3 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionPostVolumeUserFlagTest` | 661 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionPower` | 664 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionPrecomputedAOMask` | 667 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPreSkinnedLocalBounds` | 672 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionPreSkinnedNormal` | 676 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPreSkinnedPosition` | 681 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionPreviousFrameSwitch` | 686 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionQualitySwitch` | 689 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRayTracingQualitySwitch` | 692 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionReflectionCapturePassSwitch` | 695 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionReflectionVectorWS` | 698 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionReroute` | 702 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRequiredSamplersSwitch` | 705 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRgbToHsv` | 708 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRotateAboutAxis` | 711 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRotator` | 714 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRound` | 717 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRuntimeVirtualTextureCustomData` | 720 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRuntimeVirtualTextureOutput` | 723 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRuntimeVirtualTextureReplace` | 726 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRuntimeVirtualTextureSample` | 729 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionRuntimeVirtualTextureSampleParameter` | 732 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionSamplePhysicsVectorField` | 736 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSamplePhysicsScalarField` | 739 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSamplePhysicsIntegerField` | 742 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSaturate` | 745 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSceneColor` | 748 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionSceneDepth` | 752 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionSceneDepthWithoutWater` | 756 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionSceneTexelSize` | 760 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionSceneTexture` | 764 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionScreenPosition` | 768 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionSetMaterialAttributes` | 774 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionShaderStageSwitch` | 777 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionShadingModel` | 780 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionShadingPathSwitch` | 783 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionShadowReplace` | 786 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSign` | 789 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSine` | 792 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSingleLayerWaterMaterialOutput` | 795 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSkyAtmosphereLightDirection` | 798 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyAtmosphereLightIlluminance` | 802 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyAtmosphereLightIlluminanceOnGround` | 806 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyAtmosphereLightDiskLuminance` | 810 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyAtmosphereAerialPerspective` | 814 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyAtmosphereDistantLightScatteredLuminance` | 818 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyAtmosphereViewLuminance` | 822 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSkyLightEnvMapSample` | 826 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSobol` | 830 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSmoothStep` | 833 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionSparseVolumeTextureObject` | 837 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionSparseVolumeTextureSample` | 841 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSparseVolumeTextureSampleParameter` | 844 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionSparseVolumeTextureObjectParameter` | 848 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionSpeedTree` | 852 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSphereMask` | 855 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSphericalParticleOpacity` | 858 | 2 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionSquareRoot` | 862 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSRGBColorToWorkingColorSpace` | 865 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionStaticBool` | 868 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionStaticBoolParameter` | 872 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionStaticComponentMaskParameter` | 875 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionStaticSwitch` | 879 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionStaticSwitchParameter` | 882 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionStep` | 885 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionSubsurfaceMediumMaterialOutput` | 889 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSubtract` | 892 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionSwitch` | 895 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTangent` | 898 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTemporalSobol` | 901 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureCoordinate` | 904 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureCollection` | 907 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureCollectionParameter` | 910 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureObject` | 914 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureObjectFromCollection` | 918 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureObjectParameter` | 921 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureProperty` | 925 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionTextureSampleParameter2DArray` | 929 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureSampleParameterCube` | 933 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureSampleParameterCubeArray` | 937 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureSampleParameterSubUV` | 941 | 3 | MenuCategories |
| `/Script/Engine.MaterialExpressionTextureSampleParameterVolume` | 946 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionTime` | 950 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionTransform` | 954 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTransformPosition` | 957 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTruncate` | 960 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTruncateLWC` | 963 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionTwoSidedSign` | 966 | 3 | MenuCategories, bShaderInputData, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionUserSceneTexture` | 971 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionVectorNoise` | 975 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionVertexColor` | 978 | 3 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionVertexInterpolator` | 983 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionVertexNormalWS` | 986 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionVertexTangentWS` | 992 | 4 | MenuCategories, ExternalCodeIdentifiers, bShaderInputData |
| `/Script/Engine.MaterialExpressionViewProperty` | 998 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionViewSize` | 1002 | 2 | MenuCategories, bShaderInputData |
| `/Script/Engine.MaterialExpressionVirtualTextureFeatureSwitch` | 1006 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionVolumetricAdvancedMaterialInput` | 1009 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionVolumetricCloudEmptySpaceSkippingInput` | 1012 | 3 | MenuCategories, ExternalCodeIdentifiers |
| `/Script/Engine.MaterialExpressionVolumetricAdvancedMaterialOutput` | 1017 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionVolumetricCloudEmptySpaceSkippingOutput` | 1020 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionWorldPosition` | 1023 | 2 | MenuCategories, bShaderInputData |
| `/Script/Paper2D.MaterialExpressionSpriteTextureSampler` | 1027 | 2 | MenuCategories |
| `/Script/Engine.MaterialExpressionRecordTextureStreamingInfo` | 1031 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionOperator` | 1034 | 1 | MenuCategories |
| `/Script/Engine.MaterialExternalCodeCollection` | 1037 | 101 | ExternalCodeDeclarations |
| `/Script/Engine.MaterialExpressionAggregate` | 1147 | 1 | MenuCategories |
| `/Script/Engine.MaterialExpressionBlend` | 1150 | 1 | MenuCategories |

### `Config/BasePakFileRules.ini` — 2 sections, 10 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsWithoutRules` | 13 | 2 | Section |
| `ExcludeContentForMobile` | 18 | 8 | Platforms, bExcludeFromPaks, bOverrideChunkManifest, Files |

### `Config/BaseRuntimeOptions.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.RuntimeOptionsBase` | 2 | 0 |  |

### `Config/BaseScalability.ini` — 52 sections, 839 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `ScalabilitySettings` | 16 | 12 | PerfIndexThresholds_ResolutionQuality, PerfIndexThresholds_ViewDistanceQuality, PerfIndexThresholds_AntiAliasingQuality, PerfIndexThresholds_ShadowQuality, PerfIndexThresholds_GlobalIlluminationQuality, PerfIndexThresholds_ReflectionQuality, PerfIndexThresholds_PostProcessQuality, PerfIndexThreshold |
| `ResolutionQuality` | 39 | 6 | ResolutionPresets |
| `AntiAliasingQuality@0` | 52 | 9 | r.FXAA.Quality, r.TemporalAA.Quality, r.TSR.History.R11G11B10, r.TSR.History.ScreenPercentage, r.TSR.History.UpdateQuality, r.TSR.ShadingRejection.Flickering, r.TSR.RejectionAntiAliasingQuality, r.TSR.ReprojectionField, r.TSR.Resurrection |
| `AntiAliasingQuality@1` | 63 | 9 | r.FXAA.Quality, r.TemporalAA.Quality, r.TSR.History.R11G11B10, r.TSR.History.ScreenPercentage, r.TSR.History.UpdateQuality, r.TSR.ShadingRejection.Flickering, r.TSR.RejectionAntiAliasingQuality, r.TSR.ReprojectionField, r.TSR.Resurrection |
| `AntiAliasingQuality@2` | 74 | 9 | r.FXAA.Quality, r.TemporalAA.Quality, r.TSR.History.R11G11B10, r.TSR.History.ScreenPercentage, r.TSR.History.UpdateQuality, r.TSR.ShadingRejection.Flickering, r.TSR.RejectionAntiAliasingQuality, r.TSR.ReprojectionField, r.TSR.Resurrection |
| `AntiAliasingQuality@3` | 85 | 9 | r.FXAA.Quality, r.TemporalAA.Quality, r.TSR.History.R11G11B10, r.TSR.History.ScreenPercentage, r.TSR.History.UpdateQuality, r.TSR.ShadingRejection.Flickering, r.TSR.RejectionAntiAliasingQuality, r.TSR.ReprojectionField, r.TSR.Resurrection |
| `AntiAliasingQuality@Cine` | 96 | 9 | r.FXAA.Quality, r.TemporalAA.Quality, r.TSR.History.R11G11B10, r.TSR.History.ScreenPercentage, r.TSR.History.UpdateQuality, r.TSR.ShadingRejection.Flickering, r.TSR.RejectionAntiAliasingQuality, r.TSR.ReprojectionField, r.TSR.Resurrection |
| `ViewDistanceQuality@0` | 110 | 2 | r.SkeletalMeshLODBias, r.ViewDistanceScale |
| `ViewDistanceQuality@1` | 114 | 2 | r.SkeletalMeshLODBias, r.ViewDistanceScale |
| `ViewDistanceQuality@2` | 118 | 2 | r.SkeletalMeshLODBias, r.ViewDistanceScale |
| `ViewDistanceQuality@3` | 122 | 2 | r.SkeletalMeshLODBias, r.ViewDistanceScale |
| `ViewDistanceQuality@Cine` | 126 | 2 | r.SkeletalMeshLODBias, r.ViewDistanceScale |
| `ShadowQuality@0` | 132 | 33 | r.LightFunctionQuality, r.ShadowQuality, r.Shadow.CSM.MaxCascades, r.Shadow.MaxResolution, r.Shadow.MaxCSMResolution, r.Shadow.RadiusThreshold, r.Shadow.DistanceScale, r.Shadow.CSM.TransitionScale, r.Shadow.PreShadowResolutionFactor, r.DistanceFieldShadowing, r.VolumetricFog, r.LightMaxDrawDistanceS |
| `ShadowQuality@1` | 167 | 33 | r.LightFunctionQuality, r.ShadowQuality, r.Shadow.CSM.MaxCascades, r.Shadow.MaxResolution, r.Shadow.MaxCSMResolution, r.Shadow.RadiusThreshold, r.Shadow.DistanceScale, r.Shadow.CSM.TransitionScale, r.Shadow.PreShadowResolutionFactor, r.DistanceFieldShadowing, r.VolumetricFog, r.LightMaxDrawDistanceS |
| `ShadowQuality@2` | 202 | 36 | r.LightFunctionQuality, r.ShadowQuality, r.Shadow.CSM.MaxCascades, r.Shadow.MaxResolution, r.Shadow.MaxCSMResolution, r.Shadow.RadiusThreshold, r.Shadow.DistanceScale, r.Shadow.CSM.TransitionScale, r.Shadow.PreShadowResolutionFactor, r.DistanceFieldShadowing, r.VolumetricFog, r.VolumetricFog.GridPix |
| `ShadowQuality@3` | 240 | 36 | r.LightFunctionQuality, r.ShadowQuality, r.Shadow.CSM.MaxCascades, r.Shadow.MaxResolution, r.Shadow.MaxCSMResolution, r.Shadow.RadiusThreshold, r.Shadow.DistanceScale, r.Shadow.CSM.TransitionScale, r.Shadow.PreShadowResolutionFactor, r.DistanceFieldShadowing, r.VolumetricFog, r.VolumetricFog.GridPix |
| `ShadowQuality@Cine` | 278 | 36 | r.LightFunctionQuality, r.ShadowQuality, r.Shadow.CSM.MaxCascades, r.Shadow.MaxResolution, r.Shadow.MaxCSMResolution, r.Shadow.RadiusThreshold, r.Shadow.DistanceScale, r.Shadow.CSM.TransitionScale, r.Shadow.PreShadowResolutionFactor, r.DistanceFieldShadowing, r.VolumetricFog, r.VolumetricFog.GridPix |
| `GlobalIlluminationQuality@0` | 318 | 5 | r.AOQuality, r.DistanceFieldAO, r.SkylightIntensityMultiplier, r.Lumen.DiffuseIndirect.Allow, r.RayTracing.Scene.BuildMode |
| `GlobalIlluminationQuality@1` | 326 | 33 | r.DistanceFieldAO, r.SkylightIntensityMultiplier, r.AOQuality, r.Lumen.DiffuseIndirect.Allow, r.Lumen.FinalGatherMethod, r.LumenScene.SurfaceCache.AtlasSize, r.LumenScene.SurfaceCache.CardTexelDensityScale, r.LumenScene.SurfaceCache.CardMinResolution, r.LumenScene.SurfaceCache.CardMaxResolution, r.L |
| `GlobalIlluminationQuality@2` | 369 | 43 | r.DistanceFieldAO, r.SkylightIntensityMultiplier, r.AOQuality, r.Lumen.DiffuseIndirect.Allow, r.Lumen.FinalGatherMethod, r.LumenScene.SurfaceCache.AtlasSize, r.LumenScene.SurfaceCache.CardTexelDensityScale, r.LumenScene.SurfaceCache.CardMinResolution, r.LumenScene.SurfaceCache.CardMaxResolution, r.L |
| `GlobalIlluminationQuality@3` | 416 | 44 | r.DistanceFieldAO, r.SkylightIntensityMultiplier, r.AOQuality, r.Lumen.DiffuseIndirect.Allow, r.Lumen.FinalGatherMethod, r.LumenScene.SurfaceCache.AtlasSize, r.LumenScene.SurfaceCache.CardTexelDensityScale, r.LumenScene.SurfaceCache.CardMinResolution, r.LumenScene.SurfaceCache.CardMaxResolution, r.L |
| `GlobalIlluminationQuality@Cine` | 464 | 44 | r.DistanceFieldAO, r.SkylightIntensityMultiplier, r.AOQuality, r.Lumen.DiffuseIndirect.Allow, r.Lumen.FinalGatherMethod, r.LumenScene.SurfaceCache.AtlasSize, r.LumenScene.SurfaceCache.CardTexelDensityScale, r.LumenScene.SurfaceCache.CardMinResolution, r.LumenScene.SurfaceCache.CardMaxResolution, r.L |
| `ReflectionQuality@0` | 514 | 3 | r.SSR.Quality, r.SSR.HalfResSceneColor, r.Lumen.Reflections.Allow |
| `ReflectionQuality@1` | 519 | 3 | r.SSR.Quality, r.SSR.HalfResSceneColor, r.Lumen.Reflections.Allow |
| `ReflectionQuality@2` | 524 | 10 | r.SSR.Quality, r.SSR.HalfResSceneColor, r.Lumen.Reflections.Allow, r.Lumen.Reflections.DownsampleFactor, r.Lumen.Reflections.MaxRoughnessToTraceForFoliage, r.Lumen.ScreenProbeGather.MaxRoughnessToEvaluateRoughSpecularForFoliage, r.Lumen.Reflections.ScreenSpaceReconstruction.NumSamples, r.Lumen.Refle |
| `ReflectionQuality@3` | 536 | 10 | r.SSR.Quality, r.SSR.HalfResSceneColor, r.Lumen.Reflections.Allow, r.Lumen.Reflections.DownsampleFactor, r.Lumen.Reflections.MaxRoughnessToTraceForFoliage, r.Lumen.ScreenProbeGather.MaxRoughnessToEvaluateRoughSpecularForFoliage, r.Lumen.Reflections.ScreenSpaceReconstruction.NumSamples, r.Lumen.Refle |
| `ReflectionQuality@Cine` | 548 | 10 | r.SSR.Quality, r.SSR.HalfResSceneColor, r.Lumen.Reflections.Allow, r.Lumen.Reflections.DownsampleFactor, r.Lumen.Reflections.MaxRoughnessToTraceForFoliage, r.Lumen.ScreenProbeGather.MaxRoughnessToEvaluateRoughSpecularForFoliage, r.Lumen.Reflections.ScreenSpaceReconstruction.NumSamples, r.Lumen.Refle |
| `PostProcessQuality@0` | 564 | 20 | r.MotionBlurQuality, r.MotionBlur.HalfResGather, r.AmbientOcclusionMipLevelFactor, r.AmbientOcclusionMaxQuality, r.AmbientOcclusionLevels, r.AmbientOcclusionRadiusScale, r.DepthOfFieldQuality, r.RenderTargetPoolMin, r.LensFlareQuality, r.SceneColorFringeQuality, r.EyeAdaptationQuality, r.BloomQualit |
| `PostProcessQuality@1` | 586 | 31 | r.MotionBlurQuality, r.MotionBlur.HalfResGather, r.AmbientOcclusionMipLevelFactor, r.AmbientOcclusionMaxQuality, r.AmbientOcclusionLevels, r.AmbientOcclusionRadiusScale, r.DepthOfFieldQuality, r.RenderTargetPoolMin, r.LensFlareQuality, r.SceneColorFringeQuality, r.EyeAdaptationQuality, r.BloomQualit |
| `PostProcessQuality@2` | 621 | 33 | r.MotionBlurQuality, r.MotionBlur.HalfResGather, r.AmbientOcclusionMipLevelFactor, r.AmbientOcclusionMaxQuality, r.AmbientOcclusionLevels, r.AmbientOcclusionRadiusScale, r.DepthOfFieldQuality, r.RenderTargetPoolMin, r.LensFlareQuality, r.SceneColorFringeQuality, r.EyeAdaptationQuality, r.BloomQualit |
| `PostProcessQuality@3` | 658 | 34 | r.MotionBlurQuality, r.MotionBlur.HalfResGather, r.AmbientOcclusionMipLevelFactor, r.AmbientOcclusionMaxQuality, r.AmbientOcclusionLevels, r.AmbientOcclusionRadiusScale, r.DepthOfFieldQuality, r.RenderTargetPoolMin, r.LensFlareQuality, r.SceneColorFringeQuality, r.EyeAdaptationQuality, r.BloomQualit |
| `PostProcessQuality@Cine` | 697 | 35 | r.MotionBlurQuality, r.MotionBlur.HalfResGather, r.AmbientOcclusionMipLevelFactor, r.AmbientOcclusionMaxQuality, r.AmbientOcclusionLevels, r.AmbientOcclusionRadiusScale, r.GTAO.Numangles, r.DepthOfFieldQuality, r.RenderTargetPoolMin, r.LensFlareQuality, r.SceneColorFringeQuality, r.EyeAdaptationQual |
| `TextureQuality@0` | 740 | 9 | r.Streaming.MipBias, r.Streaming.AmortizeCPUToGPUCopy, r.Streaming.MaxNumTexturesToStreamPerFrame, r.Streaming.Boost, r.MaxAnisotropy, r.VT.MaxAnisotropy, r.Streaming.LimitPoolSizeToVRAM, r.Streaming.PoolSize, r.Streaming.MaxEffectiveScreenSize |
| `TextureQuality@1` | 752 | 9 | r.Streaming.MipBias, r.Streaming.AmortizeCPUToGPUCopy, r.Streaming.MaxNumTexturesToStreamPerFrame, r.Streaming.Boost, r.MaxAnisotropy, r.VT.MaxAnisotropy, r.Streaming.LimitPoolSizeToVRAM, r.Streaming.PoolSize, r.Streaming.MaxEffectiveScreenSize |
| `TextureQuality@2` | 763 | 9 | r.Streaming.MipBias, r.Streaming.AmortizeCPUToGPUCopy, r.Streaming.MaxNumTexturesToStreamPerFrame, r.Streaming.Boost, r.MaxAnisotropy, r.VT.MaxAnisotropy, r.Streaming.LimitPoolSizeToVRAM, r.Streaming.PoolSize, r.Streaming.MaxEffectiveScreenSize |
| `TextureQuality@3` | 774 | 9 | r.Streaming.MipBias, r.Streaming.AmortizeCPUToGPUCopy, r.Streaming.MaxNumTexturesToStreamPerFrame, r.Streaming.Boost, r.MaxAnisotropy, r.VT.MaxAnisotropy, r.Streaming.LimitPoolSizeToVRAM, r.Streaming.PoolSize, r.Streaming.MaxEffectiveScreenSize |
| `TextureQuality@Cine` | 785 | 9 | r.Streaming.MipBias, r.Streaming.AmortizeCPUToGPUCopy, r.Streaming.MaxNumTexturesToStreamPerFrame, r.Streaming.Boost, r.MaxAnisotropy, r.VT.MaxAnisotropy, r.Streaming.LimitPoolSizeToVRAM, r.Streaming.PoolSize, r.Streaming.MaxEffectiveScreenSize |
| `EffectsQuality@0` | 798 | 27 | r.TranslucencyLightingVolume.Dim, r.RefractionQuality, r.SceneColorFormat, r.DetailMode, r.TranslucencyLightingVolume.Blur, r.MaterialQualityLevel, r.SSS.Scale, r.SSS.SampleSet, r.SSS.Quality, r.SSS.HalfRes, r.SSGI.Quality, r.EmitterSpawnRateScale |
| `EffectsQuality@1` | 827 | 27 | r.TranslucencyLightingVolume.Dim, r.RefractionQuality, r.SceneColorFormat, r.DetailMode, r.TranslucencyLightingVolume.Blur, r.MaterialQualityLevel, r.SSS.Scale, r.SSS.SampleSet, r.SSS.Quality, r.SSS.HalfRes, r.SSGI.Quality, r.EmitterSpawnRateScale |
| `EffectsQuality@2` | 856 | 30 | r.TranslucencyLightingVolume.Dim, r.RefractionQuality, r.SceneColorFormat, r.DetailMode, r.TranslucencyLightingVolume.Blur, r.MaterialQualityLevel, r.SSS.Scale, r.SSS.SampleSet, r.SSS.Quality, r.SSS.HalfRes, r.SSGI.Quality, r.EmitterSpawnRateScale |
| `EffectsQuality@3` | 888 | 33 | r.TranslucencyLightingVolume.Dim, r.RefractionQuality, r.SceneColorFormat, r.DetailMode, r.TranslucencyLightingVolume.Blur, r.MaterialQualityLevel, r.SSS.Scale, r.SSS.SampleSet, r.SSS.Quality, r.SSS.HalfRes, r.SSGI.Quality, r.EmitterSpawnRateScale |
| `EffectsQuality@Cine` | 923 | 37 | r.TranslucencyLightingVolume.Dim, r.RefractionQuality, r.SceneColorFormat, r.DetailMode, r.TranslucencyLightingVolume.Blur, r.MaterialQualityLevel, r.SSS.Scale, r.SSS.SampleSet, r.SSS.Quality, r.SSS.HalfRes, r.SSGI.Quality, r.EmitterSpawnRateScale |
| `FoliageQuality@0` | 964 | 3 | foliage.DensityScale, grass.DensityScale, pcg.Quality |
| `FoliageQuality@1` | 972 | 3 | foliage.DensityScale, grass.DensityScale, pcg.Quality |
| `FoliageQuality@2` | 980 | 3 | foliage.DensityScale, grass.DensityScale, pcg.Quality |
| `FoliageQuality@3` | 988 | 3 | foliage.DensityScale, grass.DensityScale, pcg.Quality |
| `FoliageQuality@Cine` | 996 | 3 | foliage.DensityScale, grass.DensityScale, pcg.Quality |
| `ShadingQuality@0` | 1006 | 4 | r.HairStrands.SkyLighting.IntegrationType, r.HairStrands.SkyAO.SampleCount, r.HairStrands.Visibility.MSAA.SamplePerPixel, r.AnisotropicMaterials |
| `ShadingQuality@1` | 1012 | 4 | r.HairStrands.SkyLighting.IntegrationType, r.HairStrands.SkyAO.SampleCount, r.HairStrands.Visibility.MSAA.SamplePerPixel, r.AnisotropicMaterials |
| `ShadingQuality@2` | 1018 | 4 | r.HairStrands.SkyLighting.IntegrationType, r.HairStrands.SkyAO.SampleCount, r.HairStrands.Visibility.MSAA.SamplePerPixel, r.AnisotropicMaterials |
| `ShadingQuality@3` | 1024 | 4 | r.HairStrands.SkyLighting.IntegrationType, r.HairStrands.SkyAO.SampleCount, r.HairStrands.Visibility.MSAA.SamplePerPixel, r.AnisotropicMaterials |
| `ShadingQuality@Cine` | 1030 | 4 | r.HairStrands.SkyLighting.IntegrationType, r.HairStrands.SkyAO.SampleCount, r.HairStrands.Visibility.MSAA.SamplePerPixel, r.AnisotropicMaterials |

### `Config/BaseSourceControlSettings.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |

### `Config/BaseUnrealInsightsSettings.ini` — 9 sections, 76 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `Insights.PersistentTimingView` | 4 | 2 | Name |
| `Insights.TimingProfiler` | 8 | 11 | DefaultZoomLevel, bAutoHideEmptyTracks, bAllowPanningOnScreenEdges, TimingTrackDepthLimit.Min, TimingTrackDepthLimit.Max, bAutoScroll, AutoScrollFrameAlignment, AutoScrollViewportOffsetPercent, AutoScrollMinDelay, ThreadsToUseRatio, bShowFormatInTimerNames |
| `Insights.TimingProfiler.FramesView` | 60 | 5 | bShowUpperThresholdLine, bShowLowerThresholdLine, UpperThreshold, LowerThreshold, bAutoZoomOnFrameSelection |
| `Insights.TimingProfiler.TimingView` | 78 | 15 | ShowAllGpuTracks, ShowGpuWorkTracks, ShowGpuWorkOverlays, ShowGpuWorkExtendedLines, ShowGpuFencesRelations, ShowGpuFencesTracks, ShowGpuFencesExtendedLines, ShowAllVerseTracks, ShowAllCpuTracks, ShowAllCpuSamplingTracks, ShowCpuCoreTracks, ShowContextSwitches |
| `Insights.TimingProfiler.MainGraph` | 104 | 8 | ShowPoints, ShowPointsWithBorder, ShowConnectedLines, ShowPolygons, ShowEventDuration, ShowBars, ShowGameFrames, ShowRenderingFrame |
| `Insights.TimingProfiler.TimersView` | 131 | 18 | GameFrameColumns, RenderingFrameColumns, InstanceColumns, Mode, GroupingMode, ShowGpuTimers, ShowCpuTimers, ShowCpuSamplingTimers, ShowVerseSamplingTimers, ShowZeroCountTimers |
| `Insights.MemoryProfiler` | 171 | 1 | BudgetFilePath |
| `Insights.MemoryProfiler.TimingView` | 176 | 15 | ShowAllGpuTracks, ShowGpuWorkTracks, ShowGpuWorkOverlays, ShowGpuWorkExtendedLines, ShowGpuFencesRelations, ShowGpuFencesTracks, ShowGpuFencesExtendedLines, ShowAllVerseTracks, ShowAllCpuTracks, ShowAllCpuSamplingTracks, ShowCpuCoreTracks, ShowContextSwitches |

### `Config/ConfigRedirects.ini` — 10 sections, 15 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionNameRemap` | 20 | 2 | /Script/Engine.TextureLODSettings, /Script/Party.SocialSettings_XboxCommonGDK |
| `Staging` | 30 | 4 | WhitelistConfigFiles, BlacklistConfigFiles, WhitelistDirectories, BlacklistLocalizationTargets |
| `/Script/UnrealEd.ProjectPackagingSettings` | 36 | 2 | IniKeyBlacklist, IniSectionBlacklist |
| `/Script/Engine.RPCDoSDetectionConfig` | 40 | 1 | RPCBlockWhitelist |
| `LwsWebSocket` | 43 | 1 | bDisableDomainWhitelist |
| `WinHttpWebSocket` | 46 | 1 | bDisableDomainWhitelist |
| `OnlineServices.EOS` | 49 | 1 | EncryptionKey |
| `EOSVoiceChat` | 52 | 1 | EncryptionKey |
| `/Script/OnlineSubsystemEOS.EOSSettings` | 55 | 1 | EncryptionKey |
| `HTTP.Curl` | 58 | 1 | bForbidReuse |

### `Config/ConsoleVariables.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Startup` | 32 | 2 | p.chaos.AllowCreatePhysxBodies, fx.SkipVectorVMBackendOptimizations |

## Engine platform (Android) (7 files)


### `Config/Android/AndroidEngine.ini` — 12 sections, 63 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.Engine` | 1 | 2 | DefaultBloomKernelTextureName, DefaultFilmGrainTextureName |
| `PlatformCrypto` | 8 | 2 | PlatformRequiresDataCrypto, PakSigningRequired |
| `Audio` | 12 | 4 | PlatformFormat, PlatformStreamingFormat, AudioMixerModuleName, PlatformHeadroomDB |
| `PlatformMemoryBuckets` | 22 | 5 | LargestMemoryBucket_MinGB, LargerMemoryBucket_MinGB, DefaultMemoryBucket_MinGB, SmallerMemoryBucket_MinGB, SmallestMemoryBucket_MinGB |
| `DeviceProfileManager` | 31 | 2 | DeviceProfileSelectionModule, PreviewDeviceProfileSelectionModule |
| `Advertising` | 35 | 1 | DefaultProviderName |
| `/Script/TcpMessaging.TcpMessagingSettings` | 38 | 4 | EnableTransport, ListenEndpoint, ConnectToEndpoints, ConnectionRetryDelay |
| `LocalNotification` | 44 | 1 | DefaultPlatformService |
| `DeviceScreenDensity` | 47 | 13 | Devices |
| `ConsoleVariables` | 66 | 26 | Slate.CacheRenderData, r.VSync, TaskGraph.EnablePowerSavingThreadPriorityReduction, r.Vulkan.Depth24Bit, r.Forward.LightGridSizeZ, r.Forward.MaxCulledLightsPerCell, r.HairStrands.Simulation, r.HairStrands.Strands, r.HairStrands.Binding, r.Vulkan.MemoryBacktrace, r.Vulkan.Submission.AllowTimelineSema |
| `AlternateTextureCompression` | 111 | 0 |  |
| `SystemSettings` | 116 | 3 | QualityLevelMapping, fx.Niagara.QualityLevel.Min, fx.Niagara.QualityLevel.Max |

### `Config/Android/AndroidScalability.ini` — 34 sections, 153 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FoliageQuality@0` | 5 | 2 | foliage.DensityScale, grass.DensityScale |
| `FoliageQuality@1` | 9 | 3 | grass.densityScale, grass.CullDistanceScale, foliage.DensityScale |
| `FoliageQuality@2` | 14 | 3 | grass.densityScale, grass.CullDistanceScale, foliage.DensityScale |
| `FoliageQuality@3` | 19 | 3 | grass.densityScale, grass.CullDistanceScale, foliage.DensityScale |
| `ViewDistanceQuality@0` | 28 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ViewDistanceQuality@1` | 32 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ViewDistanceQuality@2` | 36 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ViewDistanceQuality@3` | 40 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ShadowQuality@0` | 48 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DistanceFieldShadowing, r.DFShadowQuality |
| `ShadowQuality@1` | 59 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DistanceFieldShadowing, r.DFShadowQuality |
| `ShadowQuality@2` | 70 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DFShadowQuality, r.Mobile.SupportInsetShadows |
| `ShadowQuality@3` | 81 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DFShadowQuality, r.Mobile.SupportInsetShadows |
| `ReflectionQuality@0` | 94 | 1 | r.SSR.Quality |
| `ReflectionQuality@1` | 97 | 1 | r.SSR.Quality |
| `ReflectionQuality@2` | 100 | 1 | r.SSR.Quality |
| `ReflectionQuality@3` | 103 | 1 | r.SSR.Quality |
| `ReflectionQuality@Cine` | 106 | 1 | r.SSR.Quality |
| `PostProcessQuality@0` | 113 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `PostProcessQuality@1` | 122 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `PostProcessQuality@2` | 131 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `PostProcessQuality@3` | 140 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `AntiAliasingQuality@0` | 149 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `AntiAliasingQuality@1` | 154 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `AntiAliasingQuality@2` | 159 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `AntiAliasingQuality@3` | 164 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `EffectsQuality@0` | 173 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `EffectsQuality@1` | 186 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `EffectsQuality@2` | 199 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `EffectsQuality@3` | 212 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `TextureQuality@0` | 229 | 1 | r.MaxAnisotropy |
| `TextureQuality@1` | 232 | 1 | r.MaxAnisotropy |
| `TextureQuality@2` | 235 | 1 | r.MaxAnisotropy |
| `TextureQuality@3` | 238 | 1 | r.MaxAnisotropy |
| `ScalabilityPreview` | 241 | 5 | CVarDenyList |

### `Config/Android/BaseAndroidEngine.ini` — 9 sections, 16 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `OnlineSubsystem` | 1 | 3 | DefaultPlatformService, NativePlatformService, LocalPlatformName |
| `OnlineSubsystemGooglePlay.Store` | 6 | 1 | bSupportsInAppPurchasing |
| `Audio` | 9 | 1 | AudioCaptureModuleName |
| `BuildPatchTool` | 16 | 1 | VerificationThreadCount |
| `/Script/Engine.GarbageCollectionSettings` | 19 | 1 | gc.MaxObjectsInGame |
| `SlateRenderer` | 22 | 1 | NumPreallocatedVertices |
| `/Script/Engine.RendererSettings` | 25 | 5 | r.DistanceFields, r.TemporalAA.Mobile.UseCompute, r.Visibility.DynamicMeshElements.Parallel, r.VolumetricCloud.Support, r.OIT.SortedTriangles |
| `/Script/AndroidRuntimeSettings.AndroidRuntimeSettings` | 34 | 1 | ASTCVersion |
| `MemoryMappedFiles` | 39 | 2 | Enable, Alignment |

### `Config/Android/BaseAndroidGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | PackageCompressionMethod |

### `Config/Android/BaseAndroidInput.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Android InputPlatformSettings` | 1 | 2 | MaxPlatformUserCount, input.DeviceMappingPolicy |

### `Config/Android/BaseAndroidInstallBundle.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InstallBundleSource.Bulk.MiscSettings` | 1 | 2 | bShouldSerializeMissingBulkBuildDataIni, bOnlyGatherPaksInBulkData |

### `Config/Android/DataDrivenPlatformInfo.ini` — 7 sections, 122 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 20 | bIsConfidential, TargetSettingsIniSectionName, bHasDedicatedGamepad, bInputSupportConfigurable, DefaultInputType, bSupportsMouseAndKeyboard, bSupportsGamepad, bCanChangeGamepadType, bSupportsTouch, GlobalIdentifier, NormalIconPath, LargeIconPath |
| `PreviewPlatform AndroidES31` | 24 | 10 | EnabledCVar, PlatformName, ShaderPlatform, ShaderFormat, ActiveIconName, InactiveIconName, MenuTooltip, IconText, DeviceProfileName, FriendlyName |
| `PreviewPlatform AndroidVulkan` | 37 | 10 | EnabledCVar, PlatformName, ShaderPlatform, ShaderFormat, ActiveIconName, InactiveIconName, MenuTooltip, IconText, DeviceProfileName, FriendlyName |
| `PreviewPlatform AndroidVulkanSM5` | 50 | 10 | EnabledCVar, PlatformName, ShaderPlatform, ShaderFormat, PreviewFeatureLevel, ActiveIconName, InactiveIconName, MenuTooltip, IconText, DeviceProfileName |
| `ShaderPlatform OPENGL_ES3_1_ANDROID` | 62 | 19 | Language, MaxFeatureLevel, ShaderFormat, bIsMobile, bIsAndroidOpenGLES, bTargetsTiledGPU, bSupportsMobileMultiView, bNeedsOfflineCompiler, bSupportsUnrestrictedHalfFloatBuffers, bSupportsManualVertexFetch, bSupportsClipDistance, bSupportsShaderPipelines |
| `ShaderPlatform VULKAN_ES3_1_ANDROID` | 83 | 22 | Language, MaxFeatureLevel, ShaderFormat, bIsMobile, bSupportsSpecializationConstants, bTargetsTiledGPU, bSupportsMobileMultiView, bSupportsVertexShaderLayer, bNeedsOfflineCompiler, bSupportsIndexBufferUAVs, bSupportsManualVertexFetch, bSupportsClipDistance |
| `ShaderPlatform VULKAN_SM5_ANDROID` | 109 | 31 | Language, MaxFeatureLevel, ShaderFormat, bTargetsTiledGPU, bNeedsOfflineCompiler, bSupportsIndexBufferUAVs, bRequiresDisableForwardLocalLights, bWaterUsesSimpleForwardShading, bSupportsVertexShaderSRVs, bSupportsManualVertexFetch, bSupportsUniformBufferObjects, bSupportsRayTracing |

## Engine platform (IOS) (7 files)


### `Config/IOS/BaseIOSEngine.ini` — 24 sections, 62 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.Engine` | 1 | 2 | DefaultBloomKernelTextureName, DefaultFilmGrainTextureName |
| `/Script/Engine.GarbageCollectionSettings` | 8 | 1 | gc.MaxObjectsInGame |
| `/Script/Engine.RendererSettings` | 11 | 5 | r.DistanceFields, r.TemporalAA.Mobile.UseCompute, r.Visibility.DynamicMeshElements.Parallel, r.VolumetricCloud.Support, r.OIT.SortedTriangles |
| `/Script/UdpMessaging.UdpMessagingSettings` | 20 | 1 | EnableTransport |
| `Advertising` | 24 | 1 | DefaultProviderName |
| `AlternateTextureCompression` | 27 | 0 |  |
| `Audio` | 32 | 5 | AudioCaptureModuleName, AudioMixerModuleName, PlatformHeadroomDB, PlatformFormat, PlatformStreamingFormat |
| `BackgroundHttp.iOSSettings` | 43 | 11 | bUseForegroundSession, bDiscretionary, bShouldSendLaunchEvents, MaximumConnectionsPerHost, BackgroundReceiveTimeout, BackgroundHttpResourceTimeout, RetryResumeDataLimit, CDNReorderingTimeout, bCDNReorderByPingTime, CheckForForegroundStaleDownloadsWithInterval, ForegroundStaleDownloadTimeout |
| `ConsoleVariables` | 68 | 9 | Input.EnableNativeGestureRecognition, Slate.CacheRenderData, r.HairStrands.Simulation, r.HairStrands.Strands, r.HairStrands.Binding, r.Forward.LightGridSizeZ, r.Forward.MaxCulledLightsPerCell, s.StreamableStripDebugName, s.StreamableStripDebugNameInShipping |
| `DeviceProfileManager` | 81 | 2 | DeviceProfileSelectionModule, PreviewDeviceProfileSelectionModule |
| `LocalNotification` | 85 | 1 | DefaultPlatformService |
| `MemoryMappedFiles` | 88 | 2 | Enable, Alignment |
| `OnlineSubsystem` | 92 | 3 | DefaultPlatformService, NativePlatformService, LocalPlatformName |
| `OnlineSubsystemIOS.Store` | 97 | 1 | bSupportsInAppPurchasing |
| `PlatformCrypto` | 100 | 2 | PlatformRequiresDataCrypto, PakSigningRequired |
| `PlatformMemoryBuckets` | 104 | 5 | LargestMemoryBucket_MinGB, LargerMemoryBucket_MinGB, DefaultMemoryBucket_MinGB, SmallerMemoryBucket_MinGB, SmallestMemoryBucket_MinGB |
| `Ping` | 112 | 1 | StackSize |
| `SlateRenderer` | 115 | 1 | NumPreallocatedVertices |
| `SystemSettings` | 118 | 4 | net.DisableIPv6, QualityLevelMapping, fx.Niagara.QualityLevel.Min, fx.Niagara.QualityLevel.Max |
| `TextureStreaming` | 129 | 1 | PoolSizeVRAMPercentage |
| `BuildPatchTool` | 133 | 1 | VerificationThreadCount |
| `ShaderPlatformConfig METAL_ES3_1_IOS` | 136 | 1 | BindlessConfiguration |
| `ShaderPlatformConfig METAL_SM5_IOS` | 139 | 1 | BindlessConfiguration |
| `ShaderPlatformConfig METAL_SM6_IOS` | 142 | 1 | BindlessConfiguration |

### `Config/IOS/BaseIOSGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | PackageCompressionMethod |

### `Config/IOS/BaseIOSInput.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_IOS InputPlatformSettings` | 1 | 2 | MaxPlatformUserCount, input.DeviceMappingPolicy |

### `Config/IOS/BaseIOSInstallBundle.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InstallBundleSource.Bulk.MiscSettings` | 1 | 2 | bShouldSerializeMissingBulkBuildDataIni, bOnlyGatherPaksInBulkData |

### `Config/IOS/DataDrivenPlatformInfo.ini` — 7 sections, 130 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 24 | bIsConfidential, TargetSettingsIniSectionName, bHasDedicatedGamepad, bInputSupportConfigurable, DefaultInputType, bSupportsMouseAndKeyboard, bSupportsGamepad, bCanChangeGamepadType, bSupportsTouch, GlobalIdentifier, NormalIconPath, LargeIconPath |
| `PreviewPlatform IOSMetal` | 28 | 9 | PlatformName, ShaderFormat, ShaderPlatform, ActiveIconName, InactiveIconName, MenuTooltip, IconText, DeviceProfileName, FriendlyName |
| `PreviewPlatform IOSMetalSM5` | 39 | 9 | PlatformName, ShaderFormat, ShaderPlatform, EnabledCVar, ActiveIconName, InactiveIconName, MenuTooltip, IconText, DeviceProfileName |
| `ShaderPlatform METAL_ES3_1_IOS` | 50 | 14 | Language, MaxFeatureLevel, ShaderFormat, bIsMobile, bTargetsTiledGPU, bSupports4ComponentUAVReadWrite, bSupportsManualVertexFetch, bSupportsVolumeTextureAtomics, bSupportsShaderPipelines, bSupportsIndependentSamplers, bSupportsComputeFramework, bSupportsDistanceFields |
| `ShaderPlatform METAL_SM5_IOS` | 66 | 13 | Language, MaxFeatureLevel, ShaderFormat, bTargetsTiledGPU, bSupportsIndexBufferUAVs, bSupports4ComponentUAVReadWrite, bSupportsManualVertexFetch, bSupportsVolumeTextureAtomics, bSupportsDistanceFields, bSupportsIndependentSamplers, bSupportsComputeFramework, bSupportsBindless |
| `ShaderPlatform METAL_SM6_IOS` | 81 | 49 | Language, MaxFeatureLevel, ShaderFormat, bTargetsTiledGPU, bSupportsAnisotropicMaterials, bSupportsDistanceFields, bSupportsGen5TemporalAA, bSupportsLumenGI, bSupportsSSDIndirect, bSupportsWaveOperations, MinimumWaveSize, MaximumWaveSize |
| `ShaderPlatform METAL_SIM` | 132 | 12 | Language, MaxFeatureLevel, ShaderFormat, bIsMobile, bTargetsTiledGPU, bSupports4ComponentUAVReadWrite, bSupportsManualVertexFetch, bSupportsVolumeTextureAtomics, bSupportsShaderPipelines, bSupportsIndependentSamplers, bSupportsComputeFramework, FriendlyName |

### `Config/IOS/IOSGame.ini` — 2 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 0 |  |
| `/Script/UnrealEd.ProjectPackagingSettings` | 3 | 4 | FileExtensionsToSkipCompressionInPak, FileExtensionsToSkipEncryptionInPak |

### `Config/IOS/IOSScalability.ini` — 34 sections, 153 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FoliageQuality@0` | 5 | 2 | foliage.DensityScale, grass.DensityScale |
| `FoliageQuality@1` | 9 | 3 | grass.densityScale, grass.CullDistanceScale, foliage.DensityScale |
| `FoliageQuality@2` | 14 | 3 | grass.densityScale, grass.CullDistanceScale, foliage.DensityScale |
| `FoliageQuality@3` | 19 | 3 | grass.densityScale, grass.CullDistanceScale, foliage.DensityScale |
| `ViewDistanceQuality@0` | 28 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ViewDistanceQuality@1` | 32 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ViewDistanceQuality@2` | 36 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ViewDistanceQuality@3` | 40 | 2 | r.ViewDistanceScale, r.NeverOcclusionTestDistance |
| `ShadowQuality@0` | 48 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DistanceFieldShadowing, r.DFShadowQuality |
| `ShadowQuality@1` | 59 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DistanceFieldShadowing, r.DFShadowQuality |
| `ShadowQuality@2` | 70 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DFShadowQuality, r.Mobile.SupportInsetShadows |
| `ShadowQuality@3` | 81 | 9 | r.ShadowQuality, r.Shadow.MaxCSMResolution, r.Shadow.DistanceScale, r.Shadow.CSM.MaxCascades, r.Shadow.RadiusThreshold, r.VolumetricFog, r.ContactShadows, r.DFShadowQuality, r.Mobile.SupportInsetShadows |
| `ReflectionQuality@0` | 94 | 1 | r.SSR.Quality |
| `ReflectionQuality@1` | 97 | 1 | r.SSR.Quality |
| `ReflectionQuality@2` | 100 | 1 | r.SSR.Quality |
| `ReflectionQuality@3` | 103 | 1 | r.SSR.Quality |
| `ReflectionQuality@Cine` | 106 | 1 | r.SSR.Quality |
| `PostProcessQuality@0` | 113 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `PostProcessQuality@1` | 122 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `PostProcessQuality@2` | 131 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `PostProcessQuality@3` | 140 | 7 | r.Tonemapper.Quality, r.BloomQuality, r.DepthOfFieldQuality, r.LightShaftQuality, r.EyeAdaptationQuality, r.AmbientOcclusionLevels, r.LensFlareQuality |
| `AntiAliasingQuality@0` | 149 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `AntiAliasingQuality@1` | 154 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `AntiAliasingQuality@2` | 159 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `AntiAliasingQuality@3` | 164 | 3 | r.Mobile.AntiAliasing, r.TemporalAA.Quality, r.FXAA.Quality |
| `EffectsQuality@0` | 173 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `EffectsQuality@1` | 186 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `EffectsQuality@2` | 199 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `EffectsQuality@3` | 212 | 11 | r.SkyAtmosphere.AerialPerspectiveLUT.FastApplyOnOpaque, r.SkyAtmosphere.AerialPerspectiveLUT.SampleCountMaxPerSlice, r.SkyAtmosphere.AerialPerspectiveLUT.DepthResolution, r.SkyAtmosphere.FastSkyLUT, r.SkyAtmosphere.FastSkyLUT.SampleCountMin, r.SkyAtmosphere.FastSkyLUT.SampleCountMax, r.SkyAtmosphere |
| `TextureQuality@0` | 229 | 1 | r.MaxAnisotropy |
| `TextureQuality@1` | 232 | 1 | r.MaxAnisotropy |
| `TextureQuality@2` | 235 | 1 | r.MaxAnisotropy |
| `TextureQuality@3` | 238 | 1 | r.MaxAnisotropy |
| `ScalabilityPreview` | 241 | 5 | CVarDenyList |

## Engine platform (Layouts) (2 files)


### `Config/Layouts/DefaultLayout.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `EditorLayouts` | 1 | 4 | UnrealEd_Layout_v1.6, LevelEditor_Layout_v1.8, LayoutName, LayoutDescription |

### `Config/Layouts/UE4ClassicLayout.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `EditorLayouts` | 1 | 4 | LayoutName, LayoutDescription, UnrealEd_Layout_v1.6, LevelEditor_Layout_v1.8 |

## Engine platform (Linux) (6 files)


### `Config/Linux/BaseLinuxEngine.ini` — 6 sections, 10 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `OnlineSubsystem` | 1 | 1 | LocalPlatformName |
| `PlatformPaths` | 4 | 1 | UnrealBuildTool |
| `CrashReportClient` | 7 | 1 | bAgreeToCrashUpload |
| `ShaderPlatformConfig VULKAN_SM6` | 10 | 1 | BindlessConfiguration |
| `Linux.SDL` | 14 | 0 |  |
| `/Script/Engine.RendererSettings` | 21 | 6 | r.Substrate.RoughDiffuse, r.Substrate.ShadingQuality, r.Substrate.TileCoord8bits, r.Substrate.Glints, r.Substrate.ClosuresPerPixel, r.Refraction.Blur |

### `Config/Linux/DataDrivenPlatformInfo.ini` — 1 sections, 26 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 26 | IniParent, TargetSettingsIniSectionName, bHasDedicatedGamepad, bDefaultInputStandardKeyboard, bInputSupportConfigurable, DefaultInputType, bSupportsMouseAndKeyboard, bSupportsGamepad, bCanChangeGamepadType, bSupportsTouch, GlobalIdentifier, NormalIconPath |

### `Config/Linux/LinuxEditorGameAgnostic.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

### `Config/Linux/LinuxEditorPerProjectUserSettings.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/GraphEditor.GraphEditorSettings` | 21 | 2 | bUseHighPrecisionMouseMovement, bUseInterpolationWithManualPanning |

### `Config/Linux/LinuxEngine.ini` — 7 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Audio` | 1 | 1 | PlatformHeadroomDB |
| `SystemSettings` | 5 | 4 | r.setres, fx.NiagaraAllowRuntimeScalabilityChanges, QualityLevelMapping, r.Shadow.DetectVertexShaderLayerAtRuntime |
| `TextureStreaming` | 12 | 1 | PoolSizeVRAMPercentage |
| `DeviceProfileManager` | 16 | 1 | DeviceProfileSelectionModule |
| `ConsoleVariables` | 19 | 2 | g.TimeoutForBlockOnRenderFence, memory.MemoryPressureCriticalThresholdPercent |
| `PlatformCrypto` | 24 | 1 | PlatformRequiresDataCrypto |
| `/Script/Engine.RendererSettings` | 27 | 1 | r.Shaders.RemoveUnusedInterpolators |

### `Config/Linux/LinuxGame.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 0 |  |

## Engine platform (LinuxArm64) (3 files)


### `Config/LinuxArm64/BaseLinuxArm64Engine.ini` — 2 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CrashReportClient` | 1 | 1 | bAgreeToCrashUpload |
| `/Script/Engine.RendererSettings` | 4 | 6 | r.Substrate.RoughDiffuse, r.Substrate.ShadingQuality, r.Substrate.TileCoord8bits, r.Substrate.Glints, r.Substrate.ClosuresPerPixel, r.Refraction.Blur |

### `Config/LinuxArm64/DataDrivenPlatformInfo.ini` — 1 sections, 28 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 28 | IniParent, TargetSettingsIniSectionName, bIsConfidential, bHasDedicatedGamepad, bDefaultInputStandardKeyboard, bInputSupportConfigurable, DefaultInputType, bSupportsMouseAndKeyboard, bSupportsGamepad, bCanChangeGamepadType, bSupportsTouch, GlobalIdentifier |

### `Config/LinuxArm64/LinuxArm64Engine.ini` — 7 sections, 10 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Audio` | 1 | 1 | PlatformHeadroomDB |
| `SystemSettings` | 5 | 4 | r.setres, QualityLevelMapping, fx.Niagara.QualityLevel.Min, fx.Niagara.QualityLevel.Max |
| `TextureStreaming` | 15 | 1 | PoolSizeVRAMPercentage |
| `DeviceProfileManager` | 19 | 1 | DeviceProfileSelectionModule |
| `ConsoleVariables` | 22 | 1 | g.TimeoutForBlockOnRenderFence |
| `PlatformCrypto` | 26 | 1 | PlatformRequiresDataCrypto |
| `ShaderPlatformConfig VULKAN_SM6` | 29 | 1 | BindlessConfiguration |

## Engine platform (Localization) (10 files)


### `Config/Localization/Category.ini` — 8 sections, 52 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 21 | ManifestDependencies, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 25 | 16 | CommandletClass, ModulesToPreload, IncludePathFilters, ExcludePathFilters, InputKeys, OutputNamespaces, OutputKeys, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 44 | 1 | CommandletClass |
| `GatherTextStep2` | 48 | 2 | CommandletClass, bPurgeOldEmptyEntries |
| `GatherTextStep3` | 53 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 58 | 2 | CommandletClass, ResourceName |
| `GatherTextStep5` | 63 | 2 | CommandletClass, bExportLoc |
| `GatherTextStep6` | 68 | 6 | CommandletClass, DestinationPath, bWordCountReport, WordCountReportName, bConflictReport, ConflictReportName |

### `Config/Localization/Editor.ini` — 10 sections, 91 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 21 | ManifestDependencies, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 25 | 15 | CommandletClass, SearchDirectoryPaths, ExcludePathFilters, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 43 | 8 | CommandletClass, IncludePathFilters, PackageFileNameFilters, bFixBroken, ShouldGatherFromEditorOnlyData |
| `GatherTextStep2` | 54 | 32 | CommandletClass, ModulesToPreload, IncludePathFilters, ExcludePathFilters, FieldTypesToInclude, FieldOwnerTypesToInclude, InputKeys, OutputNamespaces, OutputKeys, ShouldGatherFromEditorOnlyData |
| `GatherTextStep3` | 92 | 1 | CommandletClass |
| `GatherTextStep4` | 96 | 2 | CommandletClass, bPurgeOldEmptyEntries |
| `GatherTextStep5` | 101 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep6` | 106 | 2 | CommandletClass, ResourceName |
| `GatherTextStep7` | 111 | 2 | CommandletClass, bExportLoc |
| `GatherTextStep8` | 116 | 6 | CommandletClass, DestinationPath, bWordCountReport, WordCountReportName, bConflictReport, ConflictReportName |

### `Config/Localization/Engine.ini` — 9 sections, 71 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 22 | CommandletClass, SearchDirectoryPaths, ExcludePathFilters, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 49 | 14 | CommandletClass, IncludePathFilters, ExcludePathFilters, PackageFileNameFilters, bFixBroken, ShouldGatherFromEditorOnlyData |
| `GatherTextStep2` | 66 | 1 | CommandletClass |
| `GatherTextStep3` | 70 | 2 | CommandletClass, bPurgeOldEmptyEntries |
| `GatherTextStep4` | 75 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep5` | 80 | 2 | CommandletClass, ResourceName |
| `GatherTextStep6` | 85 | 2 | CommandletClass, bExportLoc |
| `GatherTextStep7` | 90 | 6 | CommandletClass, DestinationPath, bWordCountReport, WordCountReportName, bConflictReport, ConflictReportName |

### `Config/Localization/Keywords.ini` — 8 sections, 47 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 12 | CommandletClass, IncludePathFilters, ExcludePathFilters, InputKeys, OutputNamespaces, OutputKeys, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 39 | 1 | CommandletClass |
| `GatherTextStep2` | 43 | 2 | CommandletClass, bPurgeOldEmptyEntries |
| `GatherTextStep3` | 48 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 53 | 2 | CommandletClass, ResourceName |
| `GatherTextStep5` | 58 | 2 | CommandletClass, bExportLoc |
| `GatherTextStep6` | 63 | 6 | CommandletClass, DestinationPath, bWordCountReport, WordCountReportName, bConflictReport, ConflictReportName |

### `Config/Localization/PortableObjectExport.ini` — 6 sections, 38 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 8 | bExportLoc, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 11 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep1` | 19 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep2` | 27 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep3` | 35 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep4` | 43 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |

### `Config/Localization/PortableObjectImport.ini` — 6 sections, 38 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 8 | bImportLoc, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 11 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep1` | 19 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep2` | 27 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep3` | 35 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |
| `GatherTextStep4` | 43 | 6 | CommandletClass, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName |

### `Config/Localization/PropertyNames.ini` — 8 sections, 56 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 21 | ManifestDependencies, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 25 | 20 | CommandletClass, ModulesToPreload, IncludePathFilters, ExcludePathFilters, FieldTypesToExclude, FieldOwnerTypesToExclude, FieldOuterTypesToExclude, InputKeys, OutputNamespaces, OutputKeys, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 48 | 1 | CommandletClass |
| `GatherTextStep2` | 52 | 2 | CommandletClass, bPurgeOldEmptyEntries |
| `GatherTextStep3` | 57 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 62 | 2 | CommandletClass, ResourceName |
| `GatherTextStep5` | 67 | 2 | CommandletClass, bExportLoc |
| `GatherTextStep6` | 72 | 6 | CommandletClass, DestinationPath, bWordCountReport, WordCountReportName, bConflictReport, ConflictReportName |

### `Config/Localization/RepairData.ini` — 11 sections, 51 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 6 | CulturesToGenerate |
| `GatherTextStep0` | 10 | 4 | CommandletClass, DestinationPath, ManifestName, ArchiveName |
| `GatherTextStep1` | 17 | 5 | CommandletClass, SourcePath, DestinationPath, ManifestName, ResourceName |
| `GatherTextStep2` | 25 | 4 | CommandletClass, DestinationPath, ManifestName, ArchiveName |
| `GatherTextStep3` | 32 | 5 | CommandletClass, SourcePath, DestinationPath, ManifestName, ResourceName |
| `GatherTextStep4` | 40 | 4 | CommandletClass, DestinationPath, ManifestName, ArchiveName |
| `GatherTextStep5` | 47 | 5 | CommandletClass, SourcePath, DestinationPath, ManifestName, ResourceName |
| `GatherTextStep6` | 55 | 4 | CommandletClass, DestinationPath, ManifestName, ArchiveName |
| `GatherTextStep7` | 62 | 5 | CommandletClass, SourcePath, DestinationPath, ManifestName, ResourceName |
| `GatherTextStep8` | 70 | 4 | CommandletClass, DestinationPath, ManifestName, ArchiveName |
| `GatherTextStep9` | 77 | 5 | CommandletClass, SourcePath, DestinationPath, ManifestName, ResourceName |

### `Config/Localization/ToolTips.ini` — 8 sections, 55 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 21 | ManifestDependencies, SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 25 | 19 | CommandletClass, ModulesToPreload, IncludePathFilters, ExcludePathFilters, InputKeys, OutputNamespaces, OutputKeys, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 47 | 1 | CommandletClass |
| `GatherTextStep2` | 51 | 2 | CommandletClass, bPurgeOldEmptyEntries |
| `GatherTextStep3` | 56 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 61 | 2 | CommandletClass, ResourceName |
| `GatherTextStep5` | 66 | 2 | CommandletClass, bExportLoc |
| `GatherTextStep6` | 71 | 6 | CommandletClass, DestinationPath, bWordCountReport, WordCountReportName, bConflictReport, ConflictReportName |

### `Config/Localization/WordCount.ini` — 8 sections, 43 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 15 | bWordCountReport, DestinationPath, CulturesToGenerate |
| `GatherTextStep0` | 19 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |
| `GatherTextStep1` | 26 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |
| `GatherTextStep2` | 33 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |
| `GatherTextStep3` | 40 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |
| `GatherTextStep4` | 47 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |
| `GatherTextStep5` | 54 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |
| `GatherTextStep6` | 61 | 4 | CommandletClass, SourcePath, ManifestName, WordCountReportName |

## Engine platform (Mac) (5 files)


### `Config/Mac/BaseMacEngine.ini` — 14 sections, 43 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Audio` | 1 | 5 | AudioCaptureModuleName, AudioMixerModuleName, PlatformFormat, PlatformStreamingFormat, PlatformHeadroomDB |
| `DevOptions.Shaders` | 11 | 1 | MaxShaderJobBatchSize |
| `OnlineSubsystem` | 14 | 1 | LocalPlatformName |
| `PlatformCrypto` | 17 | 1 | PlatformRequiresDataCrypto |
| `PlatformPaths` | 20 | 1 | UnrealBuildTool |
| `TextureStreaming` | 23 | 1 | PoolSizeVRAMPercentage |
| `SystemSettings` | 27 | 5 | r.setres, g.TimeoutForBlockOnRenderFence, framepro.ScopeMinTimeMicroseconds, fx.NiagaraAllowRuntimeScalabilityChanges, QualityLevelMapping |
| `ConsoleVariables` | 35 | 3 | r.HairStrands.Visibility.MSAA.SamplePerPixel, r.SceneCulling.ExplicitCellBounds, Slate.NoAnimationOnTabForegroundedEvent |
| `/Script/Engine.RendererSettings` | 41 | 6 | r.Substrate.RoughDiffuse, r.Substrate.ShadingQuality, r.Substrate.TileCoord8bits, r.Substrate.Glints, r.Substrate.ClosuresPerPixel, r.Refraction.Blur |
| `ShaderPlatformConfig METAL_ES3_1` | 50 | 1 | BindlessConfiguration |
| `ShaderPlatformConfig METAL_SM5` | 53 | 1 | BindlessConfiguration |
| `ShaderPlatformConfig METAL_SM6` | 56 | 1 | BindlessConfiguration |
| `/Script/GameplayDebugger.GameplayDebuggingControllerComponent` | 59 | 14 | CategoryZeroBind, CategoryOneBind, CategoryTwoBind, CategoryThreeBind, CategoryFourBind, CategoryFiveBind, CategorySixBind, CategorySevenBind, CategoryEightBind, CategoryNineBind, CycleDetailsViewBind, DebugCameraBind |
| `/Script/BuildSettings.BuildSettings` | 75 | 2 | bCompileCEF3, bMultiViewPerSlateWindowSupport |

### `Config/Mac/BaseMacInput.ini` — 2 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `MacInput` | 1 | 1 | bPlatformDeleteIsBackspace |
| `InputPlatformSettings_Mac InputPlatformSettings` | 10 | 2 | MaxPlatformUserCount, input.DeviceMappingPolicy |

### `Config/Mac/DataDrivenPlatformInfo.ini` — 6 sections, 135 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 23 | bIsConfidential, TargetSettingsIniSectionName, bHasDedicatedGamepad, bDefaultInputStandardKeyboard, bInputSupportConfigurable, DefaultInputType, bSupportsMouseAndKeyboard, bSupportsGamepad, bCanChangeGamepadType, bSupportsTouch, GlobalIdentifier, NormalIconPath |
| `ShaderPlatform METAL_SM5` | 27 | 39 | Language, MaxFeatureLevel, ShaderFormat, bIsPC, bSupportsDebugViewShaders, bSupportsAnisotropicMaterials, bSupportsDistanceFields, bSupportsGen5TemporalAA, bSupportsLumenGI, bSupportsSSDIndirect, bSupportsWaveOperations, MinimumWaveSize |
| `ShaderPlatform METAL_SM6` | 68 | 50 | Language, MaxFeatureLevel, ShaderFormat, bIsPC, bSupportsDebugViewShaders, bSupportsAnisotropicMaterials, bSupportsDistanceFields, bSupportsGen5TemporalAA, bSupportsLumenGI, bSupportsSSDIndirect, bSupportsWaveOperations, MinimumWaveSize |
| `ShaderPlatform METAL_ES3_1` | 120 | 14 | Language, MaxFeatureLevel, ShaderFormat, bIsPC, bIsMobile, bSupports4ComponentUAVReadWrite, bSupportsManualVertexFetch, bSupportsVolumeTextureAtomics, bSupportsShaderPipelines, bSupportsDualSourceBlending, bSupportsIndependentSamplers, bSupportsComputeFramework |
| `PreviewPlatform METAL_SM5` | 136 | 5 | PlatformName, ShaderFormat, ShaderPlatform, PreviewFeatureLevel, MenuTooltip |
| `PreviewPlatform METAL_SM6` | 143 | 4 | PlatformName, ShaderFormat, ShaderPlatform, MenuTooltip |

### `Config/Mac/MacEditorPerProjectUserSettings.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.EditorLoadingSavingSettings` | 21 | 1 | TextDiffToolPath |

### `Config/Mac/MacGame.ini` — 2 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 0 |  |
| `/Script/UnrealEd.ProjectPackagingSettings` | 3 | 4 | FileExtensionsToSkipCompressionInPak, FileExtensionsToSkipEncryptionInPak |

## Engine platform (TVOS) (2 files)


### `Config/TVOS/DataDrivenPlatformInfo.ini` — 3 sections, 38 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 16 | bIsConfidential, IniParent, TargetSettingsIniSectionName, GlobalIdentifier, NormalIconPath, LargeIconPath, XLargeIconPath, AutoSDKPath, TutorialPath, Windows:bIsEnabled, Mac:bIsEnabled, Linux:bIsEnabled |
| `ShaderPlatform METAL_SM5_TVOS` | 20 | 12 | Language, MaxFeatureLevel, ShaderFormat, bTargetsTiledGPU, bSupportsIndexBufferUAVs, bSupports4ComponentUAVReadWrite, bSupportsManualVertexFetch, bSupportsDualSourceBlending, bSupportsIndependentSamplers, bSupportsDistanceFields, bSupportsLumenGI, FriendlyName |
| `ShaderPlatform METAL_ES3_1_TVOS` | 34 | 10 | Language, MaxFeatureLevel, ShaderFormat, bIsMobile, bTargetsTiledGPU, bSupports4ComponentUAVReadWrite, bSupportsManualVertexFetch, bSupportsShaderPipelines, bSupportsIndependentSamplers, FriendlyName |

### `Config/TVOS/TVOSEngine.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

## Engine platform (Unix) (2 files)


### `Config/Unix/DataDrivenPlatformInfo.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 4 | bIsConfidential, IniParent, bIsFakePlatform, GlobalIdentifier |

### `Config/Unix/UnixEngine.ini` — 3 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Audio` | 1 | 1 | AudioMixerModuleName |
| `PlatformCrypto` | 4 | 1 | PlatformRequiresDataCrypto |
| `SystemSettings` | 7 | 0 |  |

## Engine platform (VulkanPC) (1 files)


### `Config/VulkanPC/DataDrivenPlatformInfo.ini` — 6 sections, 182 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 6 | 3 | bIsConfidential, bIsFakePlatform, GlobalIdentifier |
| `ShaderPlatform VULKAN_SM5` | 11 | 69 | Language, MaxFeatureLevel, ShaderFormat, bSupportsSpecializationConstants, bIsMobile, bIsMetalMRT, bIsPC, bIsConsole, bIsAndroidOpenGLES, bSupportsDxc, bIsSPIRV, bSupportsDebugViewShaders |
| `ShaderPlatform VULKAN_SM6` | 141 | 80 | Language, MaxFeatureLevel, ShaderFormat, bIsMobile, bIsMetalMRT, bIsPC, bIsConsole, bIsAndroidOpenGLES, bSupportsDxc, bIsSPIRV, bSupportsSpecializationConstants, bSupportsDebugViewShaders |
| `ShaderPlatform VULKAN_PCES3_1` | 269 | 22 | Language, MaxFeatureLevel, ShaderFormat, bIsPC, bIsMobile, bSupportsSpecializationConstants, bSupportsDebugViewShaders, bTargetsTiledGPU, bSupportsMobileMultiView, bSupportsIndexBufferUAVs, bSupportsManualVertexFetch, bSupportsVertexShaderLayer |
| `PreviewPlatform VULKAN_SM5` | 295 | 4 | PlatformName, ShaderFormat, ShaderPlatform, MenuTooltip |
| `PreviewPlatform VULKAN_SM6` | 301 | 4 | PlatformName, ShaderFormat, ShaderPlatform, MenuTooltip |

## Engine platform (Windows) (8 files)


### `Config/Windows/BaseWindowsEngine.ini` — 13 sections, 38 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Audio` | 1 | 5 | AudioCaptureModuleName, AudioMixerModuleName, PlatformFormat, PlatformStreamingFormat, PlatformHeadroomDB |
| `TextureStreaming` | 11 | 1 | PoolSizeVRAMPercentage |
| `SystemSettings` | 15 | 11 | r.setres, framepro.ScopeMinTimeMicroseconds, fx.NiagaraAllowRuntimeScalabilityChanges, QualityLevelMapping, r.Occlusion.SingleRHIThreadStall, r.Nanite.Streaming.ReservedResources, D3D12.Bindless.ResourceDescriptorHeapSize, D3D12.Bindless.SamplerDescriptorHeapSize, r.PSOPrecache.GlobalShaders, r.VRS. |
| `PlatformCrypto` | 30 | 1 | PlatformRequiresDataCrypto |
| `/Script/Engine.RendererSettings` | 33 | 8 | r.Shaders.RemoveUnusedInterpolators, r.Shadow.DetectVertexShaderLayerAtRuntime, r.Substrate.RoughDiffuse, r.Substrate.ShadingQuality, r.Substrate.TileCoord8bits, r.Substrate.Glints, r.Substrate.ClosuresPerPixel, r.Refraction.Blur |
| `OnlineSubsystem` | 44 | 1 | LocalPlatformName |
| `DeviceProfileManager` | 47 | 1 | DeviceProfileSelectionModule |
| `ShaderPlatformConfig PCD3D_SM5` | 50 | 2 | BindlessConfiguration, SubstrateMaxClosuresPerPixel |
| `ShaderPlatformConfig PCD3D_SM6` | 54 | 1 | BindlessConfiguration |
| `ShaderPlatformConfig VULKAN_SM5` | 57 | 2 | BindlessConfiguration, SubstrateMaxClosuresPerPixel |
| `ShaderPlatformConfig VULKAN_SM6` | 61 | 1 | BindlessConfiguration |
| `/Script/WindowsRuntimeSettings.WindowsRuntimeSettings` | 65 | 2 | MaxNumTlsSlots, MaxNumThreadsWithTlsSlots |
| `ConsoleVariables` | 69 | 2 | WindowsApplication.UseWorkerThreadForRawInput, r.PSOPrecache.KeepInMemoryForActiveMaterials |

### `Config/Windows/BaseWindowsGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 1 | AllowedDirectories |

### `Config/Windows/BaseWindowsInput.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Windows InputPlatformSettings` | 1 | 2 | MaxPlatformUserCount, input.DeviceMappingPolicy |

### `Config/Windows/DataDrivenPlatformInfo.ini` — 10 sections, 182 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 31 | bIsConfidential, IniParent, PlatformNameAliases, TargetSettingsIniSectionName, Freezing_b32Bit, Freezing_MaxFieldAlignment32, Freezing_MaxFieldAlignment64, Freezing_bAlignBases, bHasDedicatedGamepad, bDefaultInputStandardKeyboard, bInputSupportConfigurable, DefaultInputType |
| `ShaderPlatform PCD3D_SM5` | 36 | 33 | Language, MaxFeatureLevel, ShaderFormat, bIsPC, bSupportsDebugViewShaders, bSupportsRayTracing, bSupportsGPUScene, bSupportsNanite, bSupportsSceneDataCompressedTransforms, bSupportsComputeFramework, bSupportsLumenGI, bSupportsDistanceFields |
| `PreviewPlatform PCD3D_SM5` | 72 | 4 | PlatformName, ShaderFormat, ShaderPlatform, MenuTooltip |
| `ShaderPlatform PCD3D_SM6` | 78 | 61 | FriendlyName, Language, MaxFeatureLevel, ShaderFormat, bIsPC, MaxMeshShaderThreadGroupSize, bSupportsDebugViewShaders, bSupportsRayTracing, bSupportsRayTracingShaders, bSupportsInlineRayTracing, bInlineRayTracingRequiresBindless, bSupportsRayTracingCallableShaders |
| `PreviewPlatform PCD3D_SM6` | 141 | 4 | PlatformName, ShaderFormat, ShaderPlatform, MenuTooltip |
| `ShaderPlatform PCD3D_ES3_1` | 147 | 18 | Language, MaxFeatureLevel, ShaderFormat, bIsPC, bIsMobile, bSupportsDistanceFields, bSupportsComputeFramework, bSupportsInstancedStereo, bSupportsVertexShaderLayer, bSupportsManualVertexFetch, bSupportsSceneDataCompressedTransforms, bSupportsDebugViewShaders |
| `PreviewPlatform PCD3D_ES3_1` | 167 | 6 | PlatformName, ShaderFormat, ShaderPlatform, MenuTooltip, DeviceProfileName, PreviewDeviceProfileName |
| `PreviewShaderPlatform SP_PCD3D_ES3_1_NONSDF` | 175 | 4 | ParentShaderPlatform, bSupportsDistanceFields, bCanUsePreviewPlatformForMaterialValidation, FriendlyName |
| `PreviewPlatform PCD3D_ES3_1_NONSDF` | 181 | 7 | PlatformName, ShaderFormat, ShaderPlatform, PreviewShaderPlatform, MenuTooltip, DeviceProfileName, PreviewDeviceProfileName |
| `ShaderPlatform OPENGL_PCES3_1` | 190 | 14 | Language, bIsPC, ShaderFormat, MaxFeatureLevel, bIsMobile, bSupportsManualVertexFetch, bSupportsClipDistance, bSupportsShaderPipelines, bSupportsVertexShaderSRVs, bSupportsUniformBufferObjects, bSupportsIndependentSamplers, bSupportsComputeFramework |

### `Config/Windows/WindowsEditorPerProjectUserSettings.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/LiveCoding.LiveCodingSettings` | 21 | 1 | bEnabled |

### `Config/Windows/WindowsEditorSettings.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/AudioEditor.AudioEditorSettings` | 1 | 2 | AudioMixerPlatforms |

### `Config/Windows/WindowsGame.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 0 |  |

### `Config/Windows/WindowsInput.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Windows InputPlatformSettings` | 1 | 1 | HardwareDevices |

## Extras (1 files)


### `Extras/P4VUtils/P4VUtils.ini` — 1 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no section)` | 0 | 6 | HordeServer, RobomergeURL, JiraServer, JiraRegexPattern, JiraRegexHelp, SafeBackoutHelpText |

## Platforms (3 files)


### `Platforms/VisionOS/Config/BaseVisionOSEngine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 1 | 1 | bUseSwiftUIMain |

### `Platforms/VisionOS/Config/DataDrivenPlatformInfo.ini` — 1 sections, 16 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DataDrivenPlatformInfo` | 1 | 16 | bIsConfidential, IniParent, TargetSettingsIniSectionName, GlobalIdentifier, NormalIconPath, LargeIconPath, XLargeIconPath, AutoSDKPath, TutorialPath, Windows:bIsEnabled, Mac:bIsEnabled, Linux:bIsEnabled |

### `Platforms/VisionOS/Config/VisionOSEngine.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.RendererSettings` | 6 | 4 | vr.InstancedStereo, vr.MobileMultiView, xr.OpenXRAcquireMode, // These are required for .mixed mode, aka AR |

## Plugins (plugin) (227 files)


### `Plugins/2D/Paper2D/Config/DefaultPaper2D.ini` — 1 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 7 | ClassRedirects, PropertyRedirects |

### `Plugins/AI/MassAI/Config/DefaultMassAI.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | FunctionRedirects |

### `Plugins/AI/MassCrowd/Config/DefaultMassCrowd.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 0 |  |

### `Plugins/Animation/ACLPlugin/Config/FilterPlugin.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 4 | 2 | /LICENSE, /README.md |

### `Plugins/Animation/AnimatorKit/Config/Editor.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/RigVM.RigVMProjectSettings` | 1 | 2 | VariantTags |

### `Plugins/Animation/BlendStack/Config/DefaultBlendStack.ini` — 1 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 9 | ClassRedirects, StructRedirects |

### `Plugins/Animation/ControlRig/Config/DefaultControlRig.ini` — 2 sections, 425 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 424 | ClassRedirects, StructRedirects, PropertyRedirects, EnumRedirects |
| `/Script/Engine.Engine` | 447 | 1 | K2ParamRedirects |

### `Plugins/Animation/DeformerGraph/Config/DefaultDeformerGraph.ini` — 2 sections, 27 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 25 | ClassRedirects, StructRedirects, EnumRedirects |
| `/Script/OptimusSettings.OptimusSettings` | 45 | 2 | DefaultDeformer, DefaultRecomputeTangentDeformer |

### `Plugins/Animation/DeformerGraph/Config/Editor.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CookSettings` | 1 | 1 | AutomaticOptionalInclusionAssetType |

### `Plugins/Animation/IKRig/Config/DefaultIKRig.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | ClassRedirects, FunctionRedirects |

### `Plugins/Animation/LiveLink/Config/DefaultLiveLink.ini` — 1 sections, 17 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 17 | ClassRedirects, FunctionRedirects, StructRedirects, EnumRedirects, PropertyRedirects |

### `Plugins/Animation/LiveLinkHub/Config/DefaultLiveLinkHub.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Config/DefaultMLDeformerFramework.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | ClassRedirects, PropertyRedirects |

### `Plugins/Animation/PhysicsControl/Config/DefaultPhysicsControl.ini` — 1 sections, 12 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 12 | PropertyRedirects, FunctionRedirects, ClassRedirects |

### `Plugins/Animation/PoseSearch/Config/DefaultPoseSearch.ini` — 1 sections, 21 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 21 | StructRedirects, PropertyRedirects, FunctionRedirects |

### `Plugins/Animation/RigLogic/Config/DefaultRigLogic.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/AudioGameplayVolume/Config/DefaultAudioGameplayVolume.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 2 | 1 | ClassRedirects |

### `Plugins/Bridge/Config/FilterPlugin.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /ThirdParty/megascans/... |

### `Plugins/Bridge/Config/FilterPluginLinux.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /ThirdParty/Linux/... |

### `Plugins/Bridge/Config/FilterPluginMac.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /ThirdParty/Mac/... |

### `Plugins/Bridge/Config/FilterPluginWin64.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /ThirdParty/Win/... |

### `Plugins/Cameras/GameplayCameras/Config/DefaultGameplayCameras.ini` — 1 sections, 28 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 28 | FunctionRedirects, ClassRedirects, StructRedirects, PropertyRedirects, EnumRedirects |

### `Plugins/ChaosClothAssetEditorCore/Config/DefaultChaosClothAssetEditorCore.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PackageRedirects |

### `Plugins/ChaosOutfitAsset/Config/Editor.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/ChaosVD/Config/ConfigRedirects.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionNameRemap` | 1 | 2 | /Script/ChaosVD.ChaosVDGenericDebugDrawSettings Instance, /Script/ChaosVD.ChaosVDAccelerationStructureVisualizationSettings Instance |

### `Plugins/ChaosVD/Config/DefaultChaosVD.ini` — 2 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `/Script/ChaosVD.ChaosVDParticleVisualizationColorSettings` | 4 | 4 | ParticleColorMode, ColorsByShapeType, ColorsByParticleState, ColorsByClientServer |

### `Plugins/ChaosVD/Config/Engine.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/ChaosVD.ChaosVDCoreSettings` | 1 | 8 | QueryOnlyMeshesMaterial, SimOnlyMeshesMaterial, InstancedMeshesMaterial, InstancedMeshesQueryOnlyMaterial, SkySphereActorClass, AmbientCubeMapTexture, BoxMesh, SphereMesh |

### `Plugins/Compositing/Composite/Config/DefaultComposite.ini` — 1 sections, 43 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 43 | ClassRedirects, EnumRedirects, StructRedirects, PackageRedirects, PropertyRedirects |

### `Plugins/Compositing/CompositeCore/Config/DefaultCompositeCore.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | ClassRedirects, PropertyRedirects |

### `Plugins/Compositing/Composure/Config/DefaultComposure.ini` — 2 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/ComposureLayersEditor.DefaultComposureEditorSettings` | 1 | 5 | FeaturedCompShotClasses, FeaturedElementClasses, DefaultElementNames |
| `CoreRedirects` | 10 | 1 | ClassRedirects |

### `Plugins/Compositing/Composure/Config/DefaultGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysCook |

### `Plugins/Compositing/OpenCVLensDistortion/Config/DefaultOpenCVLensDistortion.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | PackageRedirects, StructRedirects, ClassRedirects, PropertyRedirects |

### `Plugins/Compositing/OpenColorIO/Config/DefaultOpenColorIO.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | Section |

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Config/DefaultMultiUserClient.ini` — 2 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MultiUserClient.MultiUserReplicationSettings` | 1 | 2 | ReplicationEditorSettings, FrequencyRules |
| `CoreRedirects` | 5 | 1 | ClassRedirects |

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Config/DefaultConcertSyncCore.ini` — 1 sections, 13 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/ConcertSyncCore.ConcertSyncConfig` | 1 | 13 | IncludeObjectClassFilters, AllowedTransientProperties, ExcludedProperties, ExcludeTransactionClassFilters, PostReplicateActions |

### `Plugins/Developer/TraceSourceFiltering/Config/DefaultTraceSourceFilters.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `WorldTypeTraceFilter` | 1 | 1 | DisabledWorldTypes |

### `Plugins/Editor/ConsoleVariablesEditor/Config/DefaultConsoleVariables.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/Editor/DisplayClusterLaunch/Config/DefaultDisplayClusterLaunch.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/DisplayClusterLaunchEditor.DisplayClusterLaunchEditorProjectSettings` | 1 | 4 | AdditionalConsoleVariables, AdditionalConsoleCommands, CommandLineArguments, Logging |

### `Plugins/Editor/EditorScriptingUtilities/Config/DefaultEditorScriptingUtilities.ini` — 1 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 7 | ClassRedirects, StructRedirects, EnumRedirects |

### `Plugins/Editor/GuidedTutorials/Config/DefaultGuidedTutorials.ini` — 1 sections, 20 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/IntroTutorials.EditorTutorialSettings` | 1 | 20 | Categories, StartupTutorial, TutorialContexts |

### `Plugins/Editor/LandscapePatch/Config/Engine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/ClassViewer.ClassViewerProjectSettings` | 1 | 1 | InternalOnlyClasses |

### `Plugins/Editor/MaterialValidation/Config/DefaultMaterialValidation.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | EnumRedirects |

### `Plugins/Editor/WaveformEditor/Config/DefaultWaveformEditor.ini` — 2 sections, 10 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/WaveformEditorWidgets.WaveformEditorWidgetsSettings` | 1 | 9 | PlayheadColor, WaveformColor, WaveformBackgroundColor, MajorGridColor, MinorGridColor, RulerBackgroundColor, RulerTicksColor, RulerTextColor, RulerFontSize |
| `CoreRedirects` | 13 | 1 | PropertyRedirects |

### `Plugins/EnhancedInput/Config/DefaultEnhancedInput.ini` — 1 sections, 13 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 13 | FunctionRedirects, PropertyRedirects |

### `Plugins/EnhancedInput/Config/Input.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/EngineSettings.ConsoleSettings` | 1 | 3 | ManualAutoCompleteList |

### `Plugins/Enterprise/DataprepEditor/Config/DefaultDataprepEditor.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | ClassRedirects, PropertyRedirects, EnumRedirects |

### `Plugins/Enterprise/DatasmithCADImporter/Config/DefaultDatasmithCADImporter.ini` — 2 sections, 13 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 10 | ClassRedirects, PropertyRedirects |
| `SectionsToSave` | 18 | 3 | Section |

### `Plugins/Enterprise/DatasmithContent/Config/DefaultDatasmithContent.ini` — 2 sections, 20 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 18 | PackageRedirects |
| `SectionsToSave` | 21 | 2 | Section |

### `Plugins/Enterprise/DatasmithImporter/Config/DefaultDatasmithImporter.ini` — 3 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |
| `FileProducerTessellationOptions` | 5 | 4 | ChordTolerance, MaxEdgeLength, NormalTolerance, StitchingTechnique |
| `FileProducerImportOptions` | 11 | 6 | SceneHandling, IncludeGeometry, IncludeMaterial, IncludeLight, IncludeCamera, IncludeAnimation |

### `Plugins/Enterprise/GLTFExporter/Config/DefaultGLTFExporter.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PackageRedirects |

### `Plugins/Enterprise/GLTFExporter/Config/FilterPlugin.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /Shaders/* |

### `Plugins/Enterprise/LidarPointCloud/Config/DefaultLidarPointCloud.ini` — 1 sections, 23 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 23 | ClassRedirects, StructRedirects, EnumRedirects, PropertyRedirects, PackageRedirects |

### `Plugins/Enterprise/MDLImporter/Config/DefaultMDLImporter.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PackageRedirects |

### `Plugins/Enterprise/VariantManagerContent/Config/DefaultVariantManagerContent.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | EnumRedirects |

### `Plugins/Experimental/AIAssistant/Config/DefaultAIAssistant.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

### `Plugins/Experimental/AnimToTexture/Config/DefaultAnimToTexture.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | StructRedirects, PropertyRedirects, FunctionRedirects |

### `Plugins/Experimental/Animation/AnimationLayering/Config/DefaultAnimationLayering.ini` — 1 sections, 12 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 12 | StructRedirects, ClassRedirects |

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Config/DefaultHierarchyTableAnimation.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | StructRedirects |

### `Plugins/Experimental/Animation/Scribble/Config/DefaultScribble.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

### `Plugins/Experimental/ChaosMover/Config/DefaultChaosMover.ini` — 2 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |
| `/Script/Engine.PhysicsSettings` | 4 | 1 | PhysicsPrediction |

### `Plugins/Experimental/CineCameraRigs/Config/DefaultCineCameraRigs.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/CineCameraRigs.CineCameraRigRailSettings` | 1 | 3 | DefaultSplineMeshMaterial, DefaultSplineMeshTexture, SpeedModeSplineMeshTexture |

### `Plugins/Experimental/ColorCorrectRegions/Config/DefaultColorCorrectRegions.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 3 | ClassRedirects, PackageRedirects |

### `Plugins/Experimental/ControlRigPhysics/Config/DefaultControlRigPhysics.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/Experimental/DaySequence/Config/Engine.ini` — 1 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 11 | PackageRedirects, ClassRedirects, StructRedirects, EnumRedirects |

### `Plugins/Experimental/FastGeoStreaming/Config/DefaultFastGeoStreaming.ini` — 1 sections, 20 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/FastGeoStreaming.FastGeoWorldPartitionRuntimeCellTransformer` | 1 | 20 | BuiltinAllowedActorClasses, BuiltinDisallowedActorClasses, BuiltinAllowedComponentClasses, BuiltinDisallowedComponentClasses, BuiltinIgnoredRemainingComponentClasses |

### `Plugins/Experimental/FullBodyIK/Config/DefaultFullBodyIK.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/Experimental/HairCardGenerator/Config/Editor.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/HairCardGeneratorEditor.HairCardGeneratorEditorSettings` | 1 | 2 | HairCardAssetNameFormat, HairCardAssetPathFormat |

### `Plugins/Experimental/InterchangeAxF/Assets/Config/DefaultInterchangeAxFAssets.ini` — 1 sections, 37 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 37 | PackageRedirects |

### `Plugins/Experimental/InterchangeAxF/Assets/Config/FilterPlugin.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 0 |  |

### `Plugins/Experimental/InterchangeAxF/Runtime/Config/FilterPlugin.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 0 |  |

### `Plugins/Experimental/MeshPartition/Config/DefaultMeshPartition.ini` — 2 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MeshPartition.Settings` | 1 | 1 | DefaultDefinition |
| `CoreRedirects` | 4 | 4 | EnumRedirects, ClassRedirects |

### `Plugins/Experimental/MetaHuman/MetaHumanCharacterUAF/Config/DefaultMetaHumanCharacterUAF.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MetaHumanCharacterUAFEditor.MetaHumanCharacterUAFProjectSettings` | 1 | 1 | Blueprints |

### `Plugins/Experimental/MotoSynth/Config/DefaultMotoSynth.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | ClassRedirects |

### `Plugins/Experimental/Mover/Config/DefaultMover.ini` — 1 sections, 18 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 18 | ClassRedirects, StructRedirects, FunctionRedirects |

### `Plugins/Experimental/NNERuntimeIREE/Config/Linux/LinuxGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysStageAsNonUFS |

### `Plugins/Experimental/NNERuntimeIREE/Config/LinuxArm64/LinuxArm64Game.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysStageAsNonUFS |

### `Plugins/Experimental/NNERuntimeIREE/Config/Mac/MacGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysStageAsNonUFS |

### `Plugins/Experimental/NNERuntimeIREE/Config/Windows/WindowsGame.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysStageAsNonUFS |

### `Plugins/Experimental/ProceduralVegetationEditor/Config/DefaultProceduralVegetationEditor.ini` — 1 sections, 32 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 32 | ClassRedirects, StructRedirects, EnumRedirects, PropertyRedirects |

### `Plugins/Experimental/RawInput/Config/Input.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

### `Plugins/Experimental/RemoteSession/Config/DefaultRemoteSession.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | PropertyRedirects |

### `Plugins/Experimental/Shotgrid/Config/DefaultShotgrid.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 3 | ClassRedirects, PackageRedirects |

### `Plugins/Experimental/ToolPresets/Config/DefaultToolPresets.ini` — 1 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 9 | PackageRedirects, ClassRedirects, StructRedirects |

### `Plugins/Experimental/UAF/UAF/Config/DefaultUAF.ini` — 1 sections, 277 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 277 | StructRedirects, ClassRedirects, PropertyRedirects, EnumRedirects, FunctionRedirects, PackageRedirects |

### `Plugins/Experimental/UAF/UAFAnimGraph/Config/DefaultUAFAnimGraph.ini` — 1 sections, 186 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 186 | StructRedirects, ClassRedirects, PropertyRedirects, EnumRedirects, PackageRedirects |

### `Plugins/Experimental/UAF/UAFAnimNode/Config/DefaultUAFAnimNode.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | StructRedirects |

### `Plugins/Experimental/UAF/UAFChooser/Config/DefaultUAFChooser.ini` — 1 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 9 | PackageRedirects, StructRedirects |

### `Plugins/Experimental/UAF/UAFControlRig/Config/DefaultUAFControlRig.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | PackageRedirects, StructRedirects |

### `Plugins/Experimental/UAF/UAFPoseSearch/Config/DefaultUAFPoseSearch.ini` — 1 sections, 16 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 16 | PackageRedirects, StructRedirects, ClassRedirects, PropertyRedirects |

### `Plugins/Experimental/UAF/UAFStateTree/Config/DefaultUAFStateTree.ini` — 1 sections, 21 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 21 | PackageRedirects, StructRedirects, ClassRedirects |

### `Plugins/Experimental/UAF/UAFTestSuites/Config/DefaultUAFTestSuites.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/Experimental/UAF/UAFWarping/Config/DefaultUAFWarping.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 8 | PackageRedirects, StructRedirects |

### `Plugins/Experimental/USDPregen/Config/DefaultUSDPregen.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/USDPregenInterchange.USDPregenSettings` | 1 | 1 | PackageSubPathTemplate |

### `Plugins/Experimental/USDPregen/Templates/PregenProject/Config/DefaultEngine.ini` — 14 sections, 81 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/EngineSettings.GameMapsSettings` | 3 | 2 | GameDefaultMap, EditorStartupMap |
| `/Script/Engine.WorldPartitionSettings` | 7 | 1 | bNewMapsEnableWorldPartitionStreaming |
| `/Script/Engine.RendererSettings` | 10 | 16 | r.AllowStaticLighting, r.RayTracing, r.RayTracing.RayTracingProxies.ProjectEnabled, r.Shadow.Virtual.Enable, r.Lumen.Global.Enable, r.DynamicGlobalIlluminationMethod, r.ReflectionMethod, r.GenerateMeshDistanceFields, r.SkinCache.CompileShaders, r.DefaultFeature.MotionBlur, r.DefaultFeature.LensFlare |
| `/Script/Engine.WorldSettings` | 28 | 2 | bEnableWorldPartition, bEnableWorldPartition2D |
| `/Script/Engine.Engine` | 32 | 4 | bUseFixedFrameRate, FixedFrameRate, ActiveGameNameRedirects |
| `/Script/Engine.AudioSettings` | 38 | 1 | bDisableAudio |
| `ConsoleVariables` | 41 | 3 | Interchange.FeatureFlags.Import.USD.ToLevel, USD.InstancingAwareTranslation, Interchange.FeatureFlags.Import.USDPregen.Enable |
| `/Script/WindowsTargetPlatform.WindowsTargetSettings` | 46 | 28 | DefaultGraphicsRHI, D3D12TargetedShaderFormats, D3D11TargetedShaderFormats, Compiler, AudioSampleRate, AudioCallbackBufferFrameSize, AudioNumBuffersToEnqueue, AudioMaxChannels, AudioNumSourceWorkers, SpatializationPlugin, SourceDataOverridePlugin, ReverbPlugin |
| `/Script/LinuxTargetPlatform.LinuxTargetSettings` | 76 | 2 | TargetedRHIs |
| `/Script/MacTargetPlatform.MacTargetSettings` | 80 | 2 | TargetedRHIs |
| `/Script/HardwareTargeting.HardwareTargetingSettings` | 84 | 4 | TargetedHardwareClass, AppliedTargetedHardwareClass, DefaultGraphicsPerformance, AppliedDefaultGraphicsPerformance |
| `/Script/WorldPartitionEditor.WorldPartitionEditorSettings` | 90 | 1 | CommandletClass |
| `/Script/Engine.UserInterfaceSettings` | 93 | 3 | bAuthorizeAutomaticWidgetVariableCreation, FontDPIPreset, FontDPI |
| `/Script/AndroidFileServerEditor.AndroidFileServerRuntimeSettings` | 98 | 12 | bEnablePlugin, bAllowNetworkConnection, SecurityToken, bIncludeInShipping, bAllowExternalStartInShipping, bCompileAFSProject, bUseCompression, bLogFiles, bReportStats, ConnectionType, bUseManualIPAddress, ManualIPAddress |

### `Plugins/Experimental/USDPregen/Templates/PregenProject/Config/DefaultGame.ini` — 2 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/CommonUI.CommonUISettings` | 3 | 1 | CommonButtonAcceptKeyHandling |
| `/Script/EngineSettings.GeneralProjectSettings` | 6 | 1 | ProjectID |

### `Plugins/Experimental/USDPregen/Templates/PregenProject/Config/DefaultInput.ini` — 1 sections, 82 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.InputSettings` | 1 | 82 | AxisConfig, bAltEnterTogglesFullscreen, bF11TogglesFullscreen, bUseMouseForTouch, bEnableMouseSmoothing, bEnableFOVScaling, bCaptureMouseOnLaunch, bEnableLegacyInputScales, bEnableMotionControls, bFilterInputByPlatformUser, bShouldFlushPressedKeysOnViewportFocusLost, bAlwaysShowTouchInterface |

### `Plugins/Experimental/USDPregen/Templates/PregenProject/Config/DefaultUSDPregen.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/USDPregenInterchange.USDPregenSettings` | 1 | 2 | ImportContentPath, PackageSubPathTemplate |

### `Plugins/Experimental/UserToolBoxBasicCommand/Config/FilterPlugin.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 0 |  |

### `Plugins/Experimental/VirtualProductionUtilities/Config/DefaultVirtualProductionUtilities.ini` — 3 sections, 25 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 18 | ClassRedirects, FunctionRedirects, PropertyRedirects, PackageRedirects |
| `/Script/VPUtilities.VPBookmarkSettings` | 28 | 5 | BookmarkMeshPath, BookmarkMaterialPath, BookmarkSplineMeshPath, BookmarkSplineMeshMaterialPath, BookmarkLabelMaterialPath |
| `/Script/VPUtilitiesEditor.VPUtilitiesEditorSettings` | 36 | 2 | ScoutingSubsystemEditorUtilityClassPath, GestureManagerEditorUtilityClassPath |

### `Plugins/Experimental/WaterAdvanced/Config/DefaultWaterAdvanced.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | PropertyRedirects, StructRedirects, FunctionRedirects |

### `Plugins/Experimental/WaterExtras/Config/DefaultWaterExtras.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

### `Plugins/Experimental/WebSocketNetworking/Config/Engine.ini` — 1 sections, 17 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/WebSocketNetworking.WebSocketNetDriver` | 7 | 17 | AllowPeerConnections, AllowPeerVoice, ConnectionTimeout, InitialConnectTimeout, RecentlyDisconnectedTrackingTime, AckTimeout, KeepAliveTime, MaxClientRate, MaxInternetClientRate, RelevantTimeout, SpawnPrioritySeconds, ServerTravelPause |

### `Plugins/Experimental/WidgetEditorToolPalette/Config/DefaultWidgetEditorToolPalette.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/WidgetEditorToolPalette.CreateWidgetToolSettings` | 1 | 5 | CreateWidgetStacks |

### `Plugins/Experimental/Workspace/Config/DefaultWorkspace.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/FX/Niagara/Config/DefaultNiagara.ini` — 4 sections, 107 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 43 | ClassRedirects, EnumRedirects, PackageRedirects, StructRedirects, PropertyRedirects |
| `/Script/Niagara.NiagaraBakerSettings` | 65 | 1 | BakeQualityLevel |
| `/Script/Niagara.NiagaraSettings` | 68 | 10 | AdditionalParameterEnums, QualityLevels, ComponentRendererWarningsPerClass, DefaultPSOPrecacheSettings |
| `/Script/NiagaraEditor.NiagaraEditorSettings` | 80 | 53 | DefaultSystem, DefaultEmitter, DefaultScript, DefaultDynamicInputScript, DefaultFunctionScript, DefaultModuleScript, DefaultEmptyEmitter, DefaultMeshRendererMesh, DefaultDecalRendererMaterial, DefaultRibbonRendererMaterial, DefaultSpriteRendererMaterial, SystemAssetWizardConfiguration |

### `Plugins/FX/NiagaraFluids/Config/DefaultNiagaraFluids.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PackageRedirects |

### `Plugins/Fab/Config/DefaultFab.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Fab.MegascansMaterialParentSettings` | 1 | 1 | MaterialParents |

### `Plugins/Fab/Config/Engine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `ConsoleVariables` | 1 | 1 | r.CEFGPUAcceleration |

### `Plugins/Fab/Config/FilterPlugin.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 3 | /ThirdParty/index.html, /Config/BaseFab.ini, /Config/DefaultFab.ini |

### `Plugins/Fab/Config/FilterPluginLinux.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /ThirdParty/libBuildPatchInstallerLib.so |

### `Plugins/Fab/Config/FilterPluginMac.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 3 | /ThirdParty/BuildPatchInstallerLib.dylib, /ThirdParty/BuildPatchInstallerLib-arm.dylib, /ThirdParty/BuildPatchInstallerLib-x86.dylib |

### `Plugins/Fab/Config/FilterPluginWin64.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /ThirdParty/BuildPatchInstallerLib.dll |

### `Plugins/GameInputWindows/Config/Input.ini` — 1 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Windows InputPlatformSettings` | 1 | 6 | HardwareDevices |

### `Plugins/Interchange/Assets/Config/DefaultInterchangeAssets.ini` — 1 sections, 145 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 145 | PackageRedirects |

### `Plugins/Interchange/Extensions/OpenUSD/Config/DefaultInterchangeOpenUSD.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/Interchange/Runtime/Config/DefaultInterchange.ini` — 5 sections, 55 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `CoreRedirects` | 4 | 45 | EnumRedirects, ClassRedirects, PackageRedirects |
| `/Script/InterchangePipelines.GLTFPipelineSettings` | 59 | 1 | MaterialParents |
| `/Script/InterchangePipelines.MaterialXPipelineSettings` | 62 | 4 | PredefinedSurfaceShaders, PredefinedBSDF, PredefinedEDF, PredefinedVDF |
| `/Script/InterchangeImport.InterchangeFbxTranslatorProjectSettings` | 68 | 4 | bConvertScene, bForceFrontXAxis, bConvertSceneUnit, bKeepFbxNamespace |

### `Plugins/Media/AjaMedia/Config/DefaultAjaMedia.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/Media/BlackmagicMedia/Config/DefaultBlackmagicMedia.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | EnumRedirects |

### `Plugins/Media/MediaFrameworkUtilities/Config/DefaultMediaFrameworkUtilities.ini` — 1 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 7 | ClassRedirects |

### `Plugins/Media/MediaIOFramework/Config/DefaultMediaIOFramework.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | EnumRedirects |

### `Plugins/Media/PixelStreaming/Config/DefaultPixelStreaming.ini` — 2 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/PixelStreaming.PixelStreamingSettings` | 1 | 4 | DefaultCursorClassName, TextEditBeamCursorClassName, HiddenCursorClassName, bMouseAlwaysAttached |
| `CoreRedirects` | 7 | 3 | ClassRedirects, PropertyRedirects |

### `Plugins/Media/PixelStreaming2/Config/DefaultPixelStreaming2.ini` — 2 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/PixelStreaming2Settings.PixelStreaming2PluginSettings` | 1 | 3 | DefaultCursorClassName, TextEditBeamCursorClassName, HiddenCursorClassName |
| `CoreRedirects` | 6 | 6 | ClassRedirects, EnumRedirects |

### `Plugins/Media/TimecodeSynchronizer/Config/DefaultTimecodeSynchronizer.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/MetaHuman/MetaHumanAnimator/Config/DefaultMetaHuman.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 8 | ClassRedirects, PackageRedirects, PropertyRedirects |

### `Plugins/MetaHuman/MetaHumanAnimator/Config/Engine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MetaHumanSequencer.MetaHumanSceneSequence` | 1 | 1 | DefaultCompletionMode |

### `Plugins/MetaHuman/MetaHumanCharacter/Config/DefaultMetaHumanCharacter.ini` — 3 sections, 33 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MetaHumanCharacterEditor.MetaHumanCharacterEditorSettings` | 1 | 8 | SculptManipulatorMesh, MoveManipulatorMesh, KeyPointCharacterManipulatorMesh, KeyPointTargetManipulatorMesh, ShowHandsPose, TemplateAnimationDataTableAssets, ScalableNormalsTypeMaterials |
| `/Script/MetaHumanCharacterPalette.MetaHumanCharacterPaletteProjectSettings` | 11 | 3 | DefaultCharacterPipelineClass, DefaultCharacterLegacyPipelines, DefaultCharacterUEFNPipelines |
| `CoreRedirects` | 16 | 22 | ClassRedirects, EnumRedirects, StructRedirects, FunctionRedirects |

### `Plugins/MetaHuman/MetaHumanCharacter/Config/Editor.ini` — 1 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MetaHumanCharacterEditor.MetaHumanCharacterEditorWardrobeSettings` | 1 | 11 | WardrobeSections, PresetDirectories, SlotNameToCategoryNameMap, EyelashesTypeToAssetPath |

### `Plugins/MetaHuman/MetaHumanLiveLink/Config/Engine.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/LiveLinkHub.LiveLinkHubSettings` | 1 | 2 | ProjectSettingsToDisplay |

### `Plugins/MetaHuman/MetaHumanLiveLink/Config/Game.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysCook |

### `Plugins/MetaHuman/MetaHumanSDK/Config/DefaultMetaHumanSDK.ini` — 3 sections, 13 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MetaHumanSDKEditor.MetaHumanSDKSettings` | 1 | 1 | VersionServiceBaseUrl |
| `/Script/MetaHumanSDKEditor.MetaHumanCloudServicesSettings` | 4 | 9 | TextureSynthesisServiceUrl, AutorigServiceUrl, ServiceEnvironment, ProdEosConstants, Timeout, RetryCount, AuthTimeout, AuthPollInterval, LongPollTimeout |
| `CoreRedirects` | 15 | 3 | StructRedirects, ClassRedirects |

### `Plugins/MovieScene/MovieRenderPipeline/Config/DefaultMovieRenderPipeline.ini` — 1 sections, 13 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 13 | PropertyRedirects, ClassRedirects, EnumRedirects |

### `Plugins/Mutable/Config/DefaultMutable.ini` — 3 sections, 62 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 58 | StructRedirects, PropertyRedirects, ClassRedirects, FunctionRedirects |
| `Features` | 69 | 1 | bExtraBoneInfluencesEnabled |
| `EditorDefaults` | 83 | 3 | ClipMorphMaterialName, ClipMeshMaterialName, DynamicallyGenerated_DGGUI_Path |

### `Plugins/Mutable/Config/FilterPlugin.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 0 |  |

### `Plugins/NNE/NNEDenoiser/Config/Game.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysCook |

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Config/DefaultAndroidFetchBackgroundDownload.ini` — 1 sections, 129 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `AndroidBackgroundHTTP.DefaultTextLoc` | 1 | 129 | DefaultNotificationText_Title, DefaultNotificationText_Content, DefaultNotificationText_Complete, DefaultNotificationText_Cancel, DefaultNotificationText_NoInternet, DefaultNotificationText_AirplaneMode, DefaultNotificationText_DataSaverEnabled, DefaultNotificationText_WaitingForCellular, DefaultNot |

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Config/Localization/OnlineSubsystemGooglePlay.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/IOS/OnlineSubsystemIOS/Config/Localization/OnlineSubsystemIOS.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Config/Localization/OnlineSubsystemGDK.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/OnlineFramework/Config/Localization/OnlineFramework.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/OnlineServicesEOSGS/Config/Engine.ini` — 1 sections, 202 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `OnlineServices.EOS.Lobbies` | 1 | 202 | ServiceDescriptors, ServiceAttributeDescriptors |

### `Plugins/Online/OnlineServicesNull/Config/Engine.ini` — 1 sections, 202 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `OnlineServices.EOS.Lobbies` | 1 | 202 | ServiceDescriptors, ServiceAttributeDescriptors |

### `Plugins/Online/OnlineSubsystem/Config/Localization/OnlineSubsystem.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/OnlineSubsystemAmazon/Config/Localization/OnlineSubsystemAmazon.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/OnlineSubsystemEOS/Config/DefaultOnlineSubsystemEOS.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/Online/OnlineSubsystemFacebook/Config/Localization/OnlineSubsystemFacebook.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/OnlineSubsystemSteam/Config/Localization/OnlineSubsystemSteam.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Online/OnlineSubsystemUtils/Config/Editor.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/OnlineSubsystemUtils.OnlinePIEConfig` | 1 | 1 | LoginTypesAllowingDuplicates |

### `Plugins/Online/OnlineSubsystemUtils/Config/Localization/OnlineSubsystemUtils.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/PCG/Config/DefaultPCG.ini` — 1 sections, 118 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 118 | FunctionRedirects, PropertyRedirects, ClassRedirects, StructRedirects, EnumRedirects |

### `Plugins/PCG/Config/EditorPerProjectUserSettings.ini` — 1 sections, 38 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `PCGEditorSpawnNodes` | 1 | 38 | Node |

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Config/DefaultPCGGeometryScriptInterop.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | ClassRedirects, PropertyRedirects |

### `Plugins/Performance/AutomatedPerfTesting/Config/Engine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SystemSettings` | 1 | 1 | APT.DynamicRes.LockedScreenPercentage |

### `Plugins/Runtime/ApexDestruction/Config/DefaultApexDestruction.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | ClassRedirects |

### `Plugins/Runtime/AudioModulation/Config/DefaultAudioModulation.ini` — 2 sections, 12 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 3 | EnumRedirects, ClassRedirects |
| `/Script/AudioModulation.AudioModulationSettings` | 6 | 9 | Parameters |

### `Plugins/Runtime/CommonUI/Config/DefaultCommonUI.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 3 | ClassRedirects |

### `Plugins/Runtime/CommonUI/Config/Input.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/CommonUI.CommonUIInputSettings` | 1 | 1 | DefaultVirtualPointerClass |

### `Plugins/Runtime/GameFeatures/Config/DedicatedServer/DedicatedServerInstallBundle.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `GameFeaturePlugins` | 1 | 1 | bGFPAreAlwaysResident |

### `Plugins/Runtime/GameplayAbilities/Config/DefaultGameplayAbilities.ini` — 1 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 6 | ClassRedirects, FunctionRedirects, PropertyRedirects, EnumRedirects |

### `Plugins/Runtime/GameplayAbilities/Config/Input.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/EngineSettings.ConsoleSettings` | 1 | 1 | ManualAutoCompleteList |

### `Plugins/Runtime/GameplayBehaviorSmartObjects/Config/DefaultGameplayBehaviorSmartObjects.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 8 | ClassRedirects, FunctionRedirects, PropertyRedirects |

### `Plugins/Runtime/GameplayInteractions/Config/DefaultGameplayInteractions.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 8 | StructRedirects, PropertyRedirects, FunctionRedirects |

### `Plugins/Runtime/GameplayStateTree/Config/DefaultGameplayStateTree.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | ClassRedirects |

### `Plugins/Runtime/GeoReferencing/Resources/PROJ/proj.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `general` | 1 | 5 | cdn_endpoint, cache_enabled, cache_size_MB, cache_ttl_sec, tmerc_default_algo |

### `Plugins/Runtime/HTTPChunkInstaller/Config/Localization/HTTPChunkInstaller.ini` — 7 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CommonSettings` | 1 | 20 | SourcePath, DestinationPath, ManifestName, ArchiveName, PortableObjectName, ResourceName, NativeCulture, CulturesToGenerate |
| `GatherTextStep0` | 24 | 9 | CommandletClass, SearchDirectoryPaths, FileNameFilters, ShouldGatherFromEditorOnlyData |
| `GatherTextStep1` | 36 | 1 | CommandletClass |
| `GatherTextStep2` | 40 | 1 | CommandletClass |
| `GatherTextStep3` | 44 | 2 | CommandletClass, bImportLoc |
| `GatherTextStep4` | 49 | 1 | CommandletClass |
| `GatherTextStep5` | 53 | 2 | CommandletClass, bExportLoc |

### `Plugins/Runtime/HairStrands/Config/DefaultHairStrands.ini` — 2 sections, 22 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Startup` | 1 | 1 | fx.UseShaderStages |
| `CoreRedirects` | 5 | 21 | PropertyRedirects, ClassRedirects |

### `Plugins/Runtime/Harmonix/Config/DefaultHarmonix.ini` — 1 sections, 19 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 19 | ClassRedirects, PropertyRedirects, StructRedirects, FunctionRedirects |

### `Plugins/Runtime/IOSDeviceProfileSelector/Config/DeviceModelsInfo.ini` — 1 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DeviceModelToDeviceSpec` | 2 | 11 | Entry |

### `Plugins/Runtime/InputDebugging/Config/Input.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/EngineSettings.ConsoleSettings` | 1 | 2 | ManualAutoCompleteList |

### `Plugins/Runtime/InstancedActors/Config/DefaultInstancedActors.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | PropertyRedirects |

### `Plugins/Runtime/MassGameplay/Config/DefaultMassGameplay.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | StructRedirects |

### `Plugins/Runtime/Metasound/Config/DefaultMetaSound.ini` — 1 sections, 30 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 30 | PropertyRedirects, StructRedirects, ClassRedirects, EnumRedirects, FunctionRedirects |

### `Plugins/Runtime/MixedRealityCaptureFramework/Config/DefaultMixedRealityCaptureFramework.ini` — 1 sections, 41 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 41 | PackageRedirects, ClassRedirects, StructRedirects, FunctionRedirects, ObjectRedirects |

### `Plugins/Runtime/ModelViewViewModel/Config/DefaultModelViewViewModel.ini` — 2 sections, 18 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 17 | ClassRedirects, StructRedirects, FunctionRedirects, PropertyRedirects |
| `/Script/ModelViewViewModelBlueprint.MVVMDeveloperProjectSettings` | 20 | 1 | FieldSelectorPermissions |

### `Plugins/Runtime/MultiServerReplication/Config/Engine.ini` — 1 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.Engine` | 1 | 6 | NetDriverDefinitions, IrisNetDriverConfigs |

### `Plugins/Runtime/NetworkPrediction/Config/DefaultNetworkPrediction.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/NetworkPrediction.NetworkPredictionSettingsObject` | 1 | 2 | Settings, DevHUDs |

### `Plugins/Runtime/NetworkPredictionExtras/Config/DefaultNetworkPredictionExtras.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/Runtime/OSC/Config/DefaultOSC.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | FunctionRedirects |

### `Plugins/Runtime/OpenXR/Config/Engine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `OpenXR` | 1 | 1 | ProblematicOpenXRApiLayerInfos |

### `Plugins/Runtime/PropertyBindingUtils/Config/DefaultPropertyBindingUtils.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | StructRedirects, EnumRedirects |

### `Plugins/Runtime/RigVM/Config/DefaultRigVM.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | StructRedirects, PropertyRedirects |

### `Plugins/Runtime/RigVM/Config/Editor.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/RigVM.RigVMProjectSettings` | 1 | 2 | VariantTags |

### `Plugins/Runtime/SmartObjects/Config/DefaultSmartObjects.ini` — 2 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/SmartObjectsModule.SmartObjectSubsystem` | 1 | 1 | SpacePartitionClassName |
| `CoreRedirects` | 4 | 6 | FunctionRedirects, EnumRedirects, StructRedirects |

### `Plugins/Runtime/Soundscape/Config/FilterPlugin.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 0 |  |

### `Plugins/Runtime/StateTree/Config/DefaultStateTree.ini` — 1 sections, 56 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 56 | PropertyRedirects, StructRedirects, EnumRedirects, ClassRedirects |

### `Plugins/Runtime/Steam/SteamController/Config/Input.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Windows InputPlatformSettings` | 1 | 1 | HardwareDevices |

### `Plugins/Runtime/Synthesis/Config/DefaultSynthesis.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | ClassRedirects, PropertyRedirects |

### `Plugins/Runtime/USDCore/Config/DefaultUSDCore.ini` — 1 sections, 20 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 20 | PackageRedirects |

### `Plugins/Runtime/WebBrowserWidget/Config/DefaultWebBrowserWidget.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysCook |

### `Plugins/Runtime/Windows/MSGameOSSSelector/Config/MSGameOSSEngine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `OnlineSubsystem` | 1 | 1 | DefaultPlatformService |

### `Plugins/Runtime/Windows/WinDualShock/Config/Input.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Windows InputPlatformSettings` | 1 | 2 | HardwareDevices |

### `Plugins/Runtime/Windows/XInputDevice/Config/Input.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `InputPlatformSettings_Windows InputPlatformSettings` | 1 | 1 | HardwareDevices |

### `Plugins/Runtime/XR/XRVisualization/Config/DefaultXRVisualization.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 4 | DirectoriesToAlwaysCook |

### `Plugins/Runtime/ZoneGraph/Config/DefaultZoneGraph.ini` — 1 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 11 | EnumRedirects, StructRedirects, PropertyRedirects |

### `Plugins/Runtime/ZoneGraphAnnotations/Config/DefaultZoneGraphAnnotations.ini` — 1 sections, 10 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 10 | PackageRedirects, StructRedirects, ClassRedirects, PropertyRedirects |

### `Plugins/Runtime/nDisplay/Config/DefaultnDisplay.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 8 | StructRedirects, PropertyRedirects, ClassRedirects |

### `Plugins/TextureGraph/Config/FilterPlugin.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /Binaries/*/*.dll |

### `Plugins/TraceUtilities/Config/DefaultTraceUtilities.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `EditorTraceUtilities` | 1 | 3 | OpenLiveSesssionOnTraceStart, OpenInsightsAfterTrace, ShowInExplorerAfterTrace |

### `Plugins/VirtualProduction/ActorModifier/Config/DefaultActorModifier.ini` — 1 sections, 30 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 30 | EnumRedirects, StructRedirects, ClassRedirects |

### `Plugins/VirtualProduction/ActorModifierCore/Config/DefaultActorModifierCore.ini` — 1 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 9 | ClassRedirects, StructRedirects, FunctionRedirects |

### `Plugins/VirtualProduction/Avalanche/Config/DefaultAvalanche.ini` — 2 sections, 294 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 293 | ClassRedirects, EnumRedirects, StructRedirects, PropertyRedirects, PackageRedirects, FunctionRedirects |
| `/Script/Avalanche.AvaAnimation` | 322 | 1 | DefaultCompletionMode |

### `Plugins/VirtualProduction/CameraCalibrationCore/Config/DefaultCameraCalibrationCore.ini` — 1 sections, 19 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 19 | ClassRedirects, PackageRedirects, PropertyRedirects, EnumRedirects |

### `Plugins/VirtualProduction/CameraCalibrationCore/Config/Game.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | DirectoriesToAlwaysCook |

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Config/Engine.ini` — 2 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | EnumRedirects |
| `/Script/LiveLinkHub.LiveLinkHubSettings` | 5 | 1 | ProjectSettingsToDisplay |

### `Plugins/VirtualProduction/CinematicAssemblyTools/Config/DefaultCinematicAssemblyTools.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | ClassRedirects |

### `Plugins/VirtualProduction/ClonerEffector/Config/DefaultClonerEffector.ini` — 1 sections, 95 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 95 | ClassRedirects, StructRedirects, PropertyRedirects, EnumRedirects, FunctionRedirects |

### `Plugins/VirtualProduction/DMX/DMXEngine/Config/DefaultDMXEngine.ini` — 1 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 2 | 7 | EnumRedirects, FunctionRedirects, StructRedirects, PropertyRedirects |

### `Plugins/VirtualProduction/DMX/DMXFixtures/Config/DefaultDMXFixtures.ini` — 1 sections, 19 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 19 | PropertyRedirects, FunctionRedirects |

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Config/DefaultDMXPixelMapping.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 2 | 3 | ClassRedirects, PropertyRedirects |

### `Plugins/VirtualProduction/DMX/DMXProtocol/Config/DefaultDMXProtocol.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | // 4.26, StructRedirects, PropertyRedirects, // 4.27, EnumRedirects |

### `Plugins/VirtualProduction/DynamicMaterial/Config/DefaultDynamicMaterial.ini` — 1 sections, 36 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 36 | ClassRedirects, EnumRedirects, PackageRedirects, PropertyRedirects, FunctionRedirects |

### `Plugins/VirtualProduction/LensComponent/Config/DefaultLensComponent.ini` — 1 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 5 | ClassRedirects, EnumRedirects |

### `Plugins/VirtualProduction/LevelSnapshots/Config/DefaultLevelSnapshots.ini` — 1 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 6 | ClassRedirects, PropertyRedirects |

### `Plugins/VirtualProduction/LiveLinkCamera/Config/DefaultLiveLinkCamera.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Config/DefaultPerformanceCaptureWorkflow.ini` — 3 sections, 42 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `/Script/PerformanceCaptureWorkflow.PerformanceCaptureSettings` | 4 | 8 | StageRoot, ViewModelClass, MocapManagerDefaultWorkflow, WorkflowPhaseUIBaseClass, MocapManagerUI, DatabaseHelperClass, AllowedCaptureCharacterActorClasses, DisallowedCaptureCharacterActorClasses |
| `CoreRedirects` | 14 | 33 | ClassRedirects, PackageRedirects, PropertyRedirects |

### `Plugins/VirtualProduction/PropertyAnimator/Config/DefaultPropertyAnimator.ini` — 1 sections, 28 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 28 | ClassRedirects, EnumRedirects, StructRedirects, PropertyRedirects |

### `Plugins/VirtualProduction/PropertyAnimatorCore/Config/DefaultPropertyAnimatorCore.ini` — 1 sections, 20 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 20 | ClassRedirects, StructRedirects, PropertyRedirects, EnumRedirects |

### `Plugins/VirtualProduction/RemoteControl/Config/DefaultRemoteControl.ini` — 2 sections, 18 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | PropertyRedirects, EnumRedirects |
| `/Script/RemoteControlLogic.RemoteControlLogicConfig` | 7 | 14 | SupportedControllerTypes, SupportedControllerStructTypes, SupportedControllerObjectClassPaths, SupportedControllerCustomTypes |

### `Plugins/VirtualProduction/RemoteControlWebInterface/Config/FilterPlugin.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `FilterPlugin` | 1 | 1 | /WebApp/... |

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Config/DefaultEngine.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | EnumRedirects |

### `Plugins/VirtualProduction/SceneState/Config/DefaultSceneState.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 1 | ClassRedirects |

### `Plugins/VirtualProduction/StageMonitoring/Config/DefaultStageMonitoring.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 2 | PropertyRedirects |

### `Plugins/VirtualProduction/Takes/Config/DefaultTakes.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `TakeRecorderSequenceEditor SequencerSettings` | 1 | 1 | ThumbnailCaptureSettings |

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Config/DefaultViewportWidgetOverlay.ini` — 1 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 6 | ClassRedirects, StructRedirects, EnumRedirects, PackageRedirects |

### `Plugins/VirtualProduction/VirtualCamera/Config/DefaultVirtualCamera.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 4 | PackageRedirects |

### `Plugins/VirtualProduction/VirtualCameraCore/Config/DefaultVCamInputSettings.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/VCamCore.VCamInputSettings` | 1 | 2 | DefaultInputProfile, InputProfiles |

### `Plugins/VirtualProduction/VirtualCameraCore/Config/DefaultVirtualCameraCore.ini` — 1 sections, 8 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 8 | ClassRedirects, FunctionRedirects |

### `Plugins/VirtualProduction/VirtualScouting/Config/DefaultVirtualScouting.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/VirtualScouting.VirtualScoutingSettings` | 1 | 1 | bUseImperial |

## Programs (30 files)


### `Programs/BuildPatchTool/Config/DefaultEngine.ini` — 30 sections, 56 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Configuration` | 1 | 1 | BasedOn |
| `Core.Log` | 4 | 11 | LogInit, LogTaskGraph, LogDevObjectVersion, LogMemory, LogTextLocalizationManager, LogObj, LogExit, LogPlatformFile, LogICUInternationalization, LogHttp, LogOnline |
| `BuildPatchTool.ConsoleLog` | 17 | 2 | ExcludedCategories |
| `OnlineSubsystem` | 21 | 1 | DefaultPlatformService |
| `OnlineSubsystemMcp` | 24 | 1 | bEnabled |
| `HTTP` | 27 | 1 | HttpMaxConnectionsPerServer |
| `OnlineSubsystemMcp.OnlinePartyMcp` | 31 | 5 | PartyPendingCreateResponseTimeout, PartyPendingJoinResponseTimeout, PartyPendingLeaveResponseTimeout, PartyPendingKickResponseTimeout, PartyPendingJoinRequestTimeout |
| `OnlineSubsystemMcp.OnlineIdentityMcp` | 39 | 2 | ServiceName, Protocol |
| `OnlineSubsystemMcp.OnlineIdentityMcp Prod` | 43 | 2 | Domain, RedirectUrl |
| `OnlineSubsystemMcp.OnlineIdentityMcp Stage` | 47 | 2 | Domain, RedirectUrl |
| `OnlineSubsystemMcp.OnlineIdentityMcp GameDev` | 51 | 2 | Domain, RedirectUrl |
| `OnlineSubsystemMcp.OnlineIdentityMcp LocalHost` | 55 | 2 | Domain, RedirectUrl |
| `OnlineSubsystemMcp.OnlineIdentityMcp CI` | 59 | 2 | Domain, RedirectUrl |
| `OnlineSubsystemMcp.OnlineArtifactServiceMcp` | 65 | 2 | ServiceName, Protocol |
| `OnlineSubsystemMcp.OnlineArtifactServiceMcp Prod` | 69 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineArtifactServiceMcp Stage` | 72 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineArtifactServiceMcp GameDev` | 75 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineArtifactServiceMcp CI` | 78 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineArtifactServiceMcp LocalHost` | 81 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineArtifactDeliveryServiceMcp` | 85 | 2 | ServiceName, Protocol |
| `OnlineSubsystemMcp.OnlineArtifactDeliveryServiceMcp GameDev` | 89 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineArtifactDeliveryServiceMcp Prod` | 92 | 2 | Domain, AltDomains |
| `OnlineSubsystemMcp.OnlineBuildInfoMcpV2` | 97 | 2 | ServiceName, Protocol |
| `OnlineSubsystemMcp.OnlineBuildInfoMcpV2 Prod` | 101 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineBuildInfoMcpV2 Stage` | 104 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineBuildInfoMcpV2 GameDev` | 107 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineBuildInfoMcpV2 CI` | 110 | 1 | Domain |
| `OnlineSubsystemMcp.OnlineBuildInfoMcpV2 LocalHost` | 113 | 1 | Domain |
| `OnlineSubsystemMcp.ContentProtectionServiceMcp` | 118 | 2 | ServiceName, Protocol |
| `OnlineSubsystemMcp.ContentProtectionServiceMcp GameDev` | 122 | 1 | Domain |

### `Programs/BuildStorageTool/Config/DefaultEngine.ini` — 4 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.NetworkSettings` | 2 | 1 | n.VerifyPeer |
| `StudioTelemetry.Provider.EpicStudio` | 5 | 1 | Enabled |
| `StudioTelemetry.Provider.Horde.Dev` | 8 | 1 | Enabled |
| `StudioTelemetry.Provider.Horde` | 11 | 1 | Enabled |

### `Programs/BuildStorageTool/Config/DefaultGame.ini` — 2 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 4 | AllowedDirectories, AllowedConfigFiles |
| `/Script/UnrealEd.ProjectPackagingSettings` | 7 | 1 | IniSectionDenylist |

### `Programs/ChaosVisualDebugger/Config/DefaultEngine.ini` — 5 sections, 22 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/Engine.GarbageCollectionSettings` | 1 | 3 | gc.MaxObjectsInProgram, gc.MaxObjectsInGame, gc.MaxObjectsInEditor |
| `SystemSettingsEditor` | 6 | 3 | s.AllowUnversionedContentInEditor, cook.AllowCookedDataInEditorBuilds, s.EnforcePackageCompatibleVersionCheck |
| `SystemSettings` | 11 | 3 | s.AllowUnversionedContentInEditor, cook.AllowCookedDataInEditorBuilds, s.EnforcePackageCompatibleVersionCheck |
| `/Script/AndroidFileServerEditor.AndroidFileServerRuntimeSettings` | 16 | 12 | bEnablePlugin, bAllowNetworkConnection, SecurityToken, bIncludeInShipping, bAllowExternalStartInShipping, bCompileAFSProject, bUseCompression, bLogFiles, bReportStats, ConnectionType, bUseManualIPAddress, ManualIPAddress |
| `ConsoleVariables` | 30 | 1 | r.Nanite.ProjectEnabled |

### `Programs/ChaosVisualDebugger/Config/DefaultGame.ini` — 3 sections, 16 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.ProjectPackagingSettings` | 1 | 1 | bUseZenStore |
| `Staging` | 4 | 1 | DisallowedLocalizationTargets |
| `CookedEditorSettings` | 7 | 14 | bSupportCookedEditor, CookedEditorTargetName, bStageUAT, bStageShaderDirs, bStagePlatformBuildDirs, bStageExtrasDirs, bStagePlatformDirs, bIsForExternalDistribution, MapMode, EngineExtraStageFiles, FinalStripFiles |

### `Programs/CrashReportClient/Config/DefaultEngine.ini` — 3 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CrashReportClient` | 1 | 6 | CrashReportClientVersion, bAllowToBeContacted, bSendLogFile, CanSendWhenUIFailedToInitialize, UIInitRetryCount, UIInitRetryInterval |
| `/Script/Engine.NetworkSettings` | 9 | 1 | n.VerifyPeer |
| `/Script/UdpMessaging.UdpMessagingSettings` | 12 | 2 | EnableTransport, MulticastTimeToLive |

### `Programs/LiveCodingConsole/Config/DefaultEngine.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `LiveCodingConsole` | 1 | 2 | bDisableActionLimit, ActionLimit |

### `Programs/LowLevelTests/Config/DefaultEngine.ini` — 3 sections, 38 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DerivedDataCacheGraphs` | 1 | 21 | TestInvalidCacheGraph1, TestInvalidCacheGraph2, TestInvalidCacheGraph3, TestInvalidCacheGraph4, TestInvalidCacheGraph5, TestInvalidCacheGraph6, TestInvalidCacheStore1, TestInvalidCacheStore2, TestInvalidCacheStore3, TestCacheGraphInlineStore1, TestCacheGraphInlineStore2, TestCacheGraph0 |
| `DerivedDataCacheStores` | 24 | 11 | TestInvalidStore1, TestInvalidStore2, TestInvalidStore3, TestStore1, TestStore2, TestStore3, TestStore4, TestStore5, TestStore6, TestStore7, TestStore8 |
| `TestLegacyCacheGraph1` | 37 | 6 | Root, Verify, AsyncPut, Hierarchy, TestLegacyStore1, TestStore2 |

### `Programs/ShaderCompileWorker/Config/DefaultEngine.ini` — 2 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DerivedDataCacheGraphs` | 1 | 2 | Default, DerivedDataBackendGraph |
| `DerivedDataCacheStores` | 5 | 2 | Local, ProjectPak |

### `Programs/ShaderCompileWorker/Config/Mac/MacEngine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `DerivedDataCacheStores` | 1 | 1 | Shared |

### `Programs/SubmitTool/Config/DefaultGame.ini` — 2 sections, 11 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Staging` | 1 | 10 | RemapDirectories, AllowedDirectories, AllowedConfigFiles |
| `/Script/UnrealEd.ProjectPackagingSettings` | 13 | 1 | DirectoriesToAlwaysStageAsNonUFS |

### `Programs/SubmitTool/Config/Linux/LinuxSubmitTool.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Validator.NonUnityAndStaticAnalysis` | 1 | 2 | ExecutablePath, Platform |

### `Programs/SubmitTool/Config/Mac/MacSubmitTool.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Validator.NonUnityAndStaticAnalysis` | 1 | 2 | ExecutablePath, Platform |

### `Programs/SubmitTool/Config/SubmitTool.ini` — 11 sections, 120 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SubmitTool.CopyLog` | 7 | 3 | LogsToCollect, "$(SubmitToolSavedDir)Logs/SubmitTool.log"\, ) |
| `Tags.ReviewedBy` | 33 | 23 | TagId, TagLabel, ToolTip, InputType, InputSubType, MinValues, MaxValues, bIsUserValue, Validation, bIsMandatory, RegexValidation, RegexErrorMessage |
| `Tags.ComboSample` | 58 | 12 | TagId, TagLabel, ToolTip, DocumentationURL, InputType, MinValues, MaxValues, SelectValues, "I",\, "am",\, "an ",\, "example") |
| `Tags.EmptySample` | 72 | 4 | TagId, TagLabel, ToolTip, InputType |
| `Tags.TextSample` | 78 | 4 | TagId, TagLabel, ToolTip, InputType |
| `Validator.Tag` | 109 | 5 | Type, CustomName, IsRequired, ToolTip, TaskArea |
| `Validator.BuildUAT` | 121 | 12 | Type, IsRequired, bUsesIncrementalCache, bLaunchHidden, bLaunchReallyHidden, CustomName, IncludeFilesWithExtension, ExecutablePath, ExecutableArguments, ToolTip, ExecutionBlockGroups, TaskArea |
| `Validator.AnalyzeSharedDotNet` | 138 | 11 | Type, IsRequired, bTreatWarningsAsErrors, CustomName, bUsesIncrementalCache, AppliesToCLRegex, ExecutablePath, ExecutableArguments, ToolTip, ExecutionBlockGroups, TaskArea |
| `Validator.NonUnityAndStaticAnalysis` | 151 | 24 | Type, IsRequired, bUsesIncrementalCache, CustomName, IncludeFilesWithExtension, ExecutablePath, ExecutableArguments, StaticAnalysers, StaticAnalyser, StaticAnalyserArg, bUseStaticAnalyser, FileListArgument |
| `Validator.CheckBalancedMacros` | 177 | 15 | Type, IsRequired, bUsesIncrementalCache, bLaunchHidden, bLaunchReallyHidden, bTreatWarningsAsErrors, CustomName, FileListArgument, ExecutablePath, ExecutableArguments, IncludeFilesWithExtension, ErrorMessages |
| `Validator.CrossChangelist` | 195 | 7 | Type, IsRequired, Invalidated, CustomName, bAcceptDeletedFiles, ToolTip, TaskArea |

### `Programs/UbaVisualizer/Config/DefaultEngine.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 1 | 1 | TemplateMacPlist |

### `Programs/UnrealFrontend/Config/DefaultEngine.ini` — 3 sections, 9 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `URL` | 1 | 1 | GameNameShort |
| `Plugins` | 4 | 6 | EnabledPlugins, ProgramEnabledPlugins |
| `SectionsToSave` | 12 | 2 | bCanSaveAllSections, Section |

### `Programs/UnrealGameSync/UnrealGameSync.ini` — 3 sections, 50 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Options` | 1 | 26 | UseFastModularVersioning, UseFastModularVersioningV2, UseCrashReportClientEditor, DebugGameHasSeparateExecutable, BuildUnrealHeaderTool, ExcludeChanges, SyncCategory |
| `Build` | 31 | 13 | Step |
| `Default` | 46 | 11 | EditorTarget, DefaultEditorArgument, SdkInstallerDir, SdkInfo |

### `Programs/UnrealHeaderTool/Config/DefaultEngine.ini` — 5 sections, 189 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Plugins` | 1 | 3 | ScriptSupportedModules |
| `/Script/Engine.GarbageCollectionSettings` | 6 | 1 | gc.MaxObjectsInProgram |
| `UnrealHeaderTool` | 9 | 173 | StructsWithNoPrefix, StructsWithTPrefix, DelegateParameterCountStrings, TypeRedirects, Units |
| `UnrealHeaderTool` | 184 | 10 | EngineNativePointerMemberBehavior, EngineObjectPtrMemberBehavior, EnginePluginNativePointerMemberBehavior, EnginePluginObjectPtrMemberBehavior, NonEngineNativePointerMemberBehavior, NonEngineObjectPtrMemberBehavior, AutomaticSettersAndGetters, AreRigVMUObjectPropertiesEnabled, AreRigVMUInterfaceProp |
| `UnrealHeaderTool` | 196 | 2 | DocumentationPolicies, DefaultDocumentationPolicy |

### `Programs/UnrealInsights/Config/DefaultEngine.ini` — 2 sections, 16 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Plugins` | 1 | 15 | ProgramEnabledPlugins |
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 18 | 1 | TemplateMacPlist |

### `Programs/UnrealInsights/Config/DefaultUnrealInsightsFrontendSettings.ini` — 2 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `Insights.SessionBrowser` | 4 | 4 | AutoConnect, AutoStartAnalysis, AutoStartAnalysisPlatform, AutoStartAnalysisAppName |

### `Programs/UnrealInsights/Config/DefaultUnrealInsightsSettings.ini` — 4 sections, 17 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `Insights.PersistentTimingView` | 4 | 1 | Name |
| `Insights` | 7 | 0 |  |
| `Insights.LoadingProfiler.TimingView` | 17 | 15 | ShowAllGpuTracks, ShowGpuWorkTracks, ShowGpuWorkOverlays, ShowGpuWorkExtendedLines, ShowGpuFencesRelations, ShowGpuFencesTracks, ShowGpuFencesExtendedLines, ShowAllVerseTracks, ShowAllCpuTracks, ShowAllCpuSamplingTracks, ShowCpuCoreTracks, ShowContextSwitches |

### `Programs/UnrealLightmass/Config/DefaultEngine.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Plugins` | 1 | 2 | EnabledPlugins, ProgramEnabledPlugins |

### `Programs/UnrealLightmass/Config/Mac/MacEngine.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MacTargetPlatform.MacTargetSettings` | 1 | 2 | TargetArchitecture, DefaultArchitecture |

### `Programs/UnrealMultiUserServer/Config/DefaultEngine.ini` — 3 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `URL` | 1 | 1 | GameNameShort |
| `Plugins` | 4 | 3 | ProgramEnabledPlugins |
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 9 | 1 | TemplateMacPlist |

### `Programs/UnrealMultiUserSlateServer/Config/DefaultEngine.ini` — 3 sections, 6 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `URL` | 1 | 1 | GameNameShort |
| `Plugins` | 4 | 4 | ProgramEnabledPlugins |
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 10 | 1 | TemplateMacPlist |

### `Programs/UnrealPak/Config/DefaultEngine.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

### `Programs/UnrealRecoverySvc/Config/DefaultEngine.ini` — 3 sections, 5 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `URL` | 1 | 1 | GameNameShort |
| `Plugins` | 4 | 2 | ProgramEnabledPlugins |
| `/Script/UdpMessaging.UdpMessagingSettings` | 8 | 2 | EnableTransport, MulticastTimeToLive |

### `Programs/UnrealVirtualizationTool/Config/DefaultEngine.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Plugins` | 1 | 0 |  |

### `Programs/Unsync/Config/Mac/MacEngine.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/MacTargetPlatform.MacTargetSettings` | 1 | 2 | TargetArchitecture, DefaultArchitecture |

### `Programs/ZenDashboard/Config/DefaultEngine.ini` — 1 sections, 0 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `(no sections: empty or comments only)` | 0 | 0 |  |

## Source (10 files)


### `Source/Programs/GPUReshape/Resources/BuildConfig.ini` — 1 sections, 3 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Startup` | 3 | 3 | r.Shaders.Symbols, r.Shaders.Optimize, r.D3D.ForceDXC |

### `Source/Programs/GPUReshape/Resources/RuntimeConfig.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Startup` | 3 | 1 | gc.MaxTimeForFinishDestroyGC |

### `Source/Programs/IoStoreDependencyViewer/PackageSettings.ini` — 1 sections, 4 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `Packaging` | 1 | 4 | OutputPath, Version, IncludeZenTools, ZenReleasePath |

### `Source/Programs/LiveLinkHub/Config/DefaultEditor.ini` — 3 sections, 7 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `EditorSettings` | 1 | 5 | bCanCreatePluginsFromBrowser, bCanModifyUserPluginDirectoriesFromBrowser, bCanModifyProjectPluginDirectoriesFromBrowser, HidePluginCategoriesFromBrowser |
| `Analytics` | 15 | 1 | AppIdOverride |
| `/Script/UnrealEd.LevelEditorViewportSettings` | 18 | 1 | bLevelEditorJoystickControls |

### `Source/Programs/LiveLinkHub/Config/DefaultEditorPerProjectUserSettings.ini` — 1 sections, 1 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `/Script/UnrealEd.EditorLoadingSavingSettings` | 1 | 1 | bAutoSaveEnable |

### `Source/Programs/LiveLinkHub/Config/DefaultEngine.ini` — 17 sections, 45 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `SectionsToSave` | 1 | 1 | bCanSaveAllSections |
| `LiveLink` | 4 | 6 | bUseLiveLinkHubSettingsDetailCustomization, bPanelControllerSeparateSourcesSubjects, bUseModularClientReference, bEnableParentSubjects, bCreateLiveLinkHubInstance, bEnableReconnectingToStaleSource |
| `LiveLinkHub` | 12 | 2 | bEnableLLHMessageBusSourceFactory, bUseMessagingConnectionManager |
| `TimedDataMonitor` | 16 | 1 | bEnableTimedDataMonitor |
| `/Script/MacTargetPlatform.XcodeProjectSettings` | 19 | 1 | TemplateMacPlist |
| `/Script/LiveLinkInterface.LiveLinkDefaultSourceSettings` | 22 | 1 | DefaultSourceFrameBufferSize |
| `/Script/LiveLinkInterface.LiveLinkDefaultSubjectSettings` | 25 | 2 | bRebroadcastSubjectsByDefault, bAllowEditingRebroadcastProperty |
| `/Script/LiveLinkHub.LiveLinkHubSettings` | 29 | 8 | AutoConnectClients, ProjectSettingsToDisplay, bShowFrameRate, TargetFrameRate |
| `/Script/AppleARKit.AppleARKitSettings` | 39 | 1 | bEnableLiveLinkForFaceTracking |
| `/Script/UnrealEd.ProjectPackagingSettings` | 42 | 1 | bShareMaterialShaderCode |
| `ConsoleVariables` | 45 | 3 | DetailsPanel.Style.EnableCardLayout, Slate.EnableGamepadEditorNavigation, LiveLinkHub.EnableStatusBar |
| `/Script/BuildSettings.BuildSettings` | 50 | 2 | DefaultEditorTarget, bIncludeParentAssembly |
| `/Script/InterchangeEngine.InterchangeProjectSettings` | 55 | 6 | ContentImportSettings, SceneImportSettings, FilePickerClass, bStaticMeshUseSmoothEdgesIfSmoothingInformationIsMissing, GenericPipelineClass, ConverterDefaultPipeline |
| `Animation.DefaultObjectSettings` | 64 | 2 | BoneCompressionSettings, CurveCompressionSettings |
| `/Script/UdpMessaging.UdpMessagingSettings` | 68 | 1 | NodeMemoryLoggingThresholdMB |
| `CoreRedirects` | 71 | 2 | PropertyRedirects, ClassRedirects |
| `MediaProfile` | 75 | 5 | ButtonMenu, ButtonAlignment, bUseTransientProfile, bAllowActiveViewportCapture, bAllowManagedViewportCapture |

### `Source/Programs/LiveLinkHub/Config/DefaultGame.ini` — 4 sections, 19 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CookedEditorSettings_CookedEditor` | 1 | 8 | CookedEditorTargetName, bStageShaderDirs, bStagePlatformBuildDirs, bStageExtrasDirs, bStagePlatformDirs, bStageUAT, bStagePython, bIsForExternalDistribution |
| `/Script/LiveLink.LiveLinkSettings` | 12 | 6 | DefaultSettingsClass, DefaultRoleSettings, DefaultVirtualSubjectClass, bPreProcessRebroadcastFrames, bTranslateRebroadcastFrames |
| `/Script/EngineSettings.GeneralProjectSettings` | 20 | 2 | ProjectID, ProjectName |
| `/Script/MediaFrameworkUtilities.MediaProfileSettings` | 24 | 3 | bApplyInCommandlet, bAutosaveAfterChange, StartupMediaProfile |

### `Source/Programs/LiveLinkHub/Config/DefaultHardware.ini` — 1 sections, 2 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `GPU_NVIDIA Windows` | 1 | 2 | SuggestedDriverVersion, DriverDenyList |

### `Source/Programs/LiveLinkHub/Source/LiveLinkHubLauncher/RuntimeDependencies.ini` — 1 sections, 103 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `LiveLinkHubLauncher` | 1 | 103 | RuntimeDependencies |

### `Source/Runtime/Experimental/TraceBasedDebuggers/Config/BaseEngine.ini` — 1 sections, 12 keys

| section | line | keys | sample keys |
|---|---|---|---|
| `CoreRedirects` | 1 | 12 | EnumRedirects, StructRedirects |
