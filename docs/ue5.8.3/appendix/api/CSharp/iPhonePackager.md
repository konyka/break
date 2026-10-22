# CSharp / iPhonePackager

- project root: `Source/Programs/IOS/iPhonePackager`
- files: 26; symbols: 1177
- symbol kinds: class=81, const=65, ctor=42, delegate=4, enum=3, enumerator=61, field=390, method=495, property=33, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/IOS/iPhonePackager/CodeSigning.cs` (iPhonePackager)


#### class `iPhonePackager.NestedCodeBundle`  
`public class NestedCodeBundle`  
_public; L22-38_
- desc: A code bundle nested inside of the application bundle (an embedded framework), which gets signed on its own before the application bundle that contains it is signed
- L27 _public field_ `public string BundlePath` — Path of the bundle relative to the root of the application bundle (e.g., "Frameworks/Foo.framework")
- L32 _public field_ `public byte[] CodeDirectoryHash` — The canonical hash of the code directory of the bundle's signature
- L37 _public field_ `public string RequirementText` — The requirement that the bundle's signature satisfies, in text form

#### class `iPhonePackager.CodeSignatureBuilder`  
`public class CodeSignatureBuilder`  
_public; L40-1332_
- L45 _public field_ `public FileOperations.FileSystemAdapter FileSystem` — The file system used to read/write different parts of the application bundle
- L50 _public field_ `public Utilities.PListHelper Info = null` — The contents of Info.plist, mutable after PrepareForSigning is called, until PerformSigning is called, where it is flattened back to bytes
- L55 _public field_ `public X509Certificate2 SigningCert` — The certificate used for code signing
- L60 _protected field_ `protected MobileProvision Provision` — The mobile provision used to sign the application
- L65-91 _public method_ `public static string InstallCertificate(string CertificateFilename, string PrivateKeyFilename)` — Returns null if successful, or an error string if it failed
- L96-193 _public method_ `public static bool FindRequiredFiles(out MobileProvision Provision, out X509Certificate2 Cert, out bool bHasOverridesFile, out bool bNameMatch, bool bNameCheck = true)` — Makes sure the required files for code signing exist and can be found
- L195-215 _protected method_ `protected virtual byte[] GetMobileProvision(string CFBundleIdentifier)`
- L217-231 _public method_ `public void LoadMobileProvision(string CFBundleIdentifier)`
- L233 _private field_ `static private string CertToolData = ""`
- L234-239 _public method_ `static public void OutputReceivedCertToolProcessCall(Object Sender, DataReceivedEventArgs Line)`
- L244-307 _public method_ `public static void FindCertificates()` — Finds all valid installed certificates
- L312-423 _public method_ `public static void FindProvisions(string CFBundleIdentifier)` — Finds all valid installed provisions
- L429-525 _public method_ `public static X509Certificate2 FindCertificate(MobileProvision ProvisionToWorkFrom)` — Tries to find a matching certificate on this machine from the the serial number of one of the certificates in the mobile provision (the one in the mobileprovision is missing the public/private key pair)
- L531-556 _public method_ `public static void InstallCertificates(List<string> CertFilenames)` — Installs a list of certificates to the local store
- L561-564 _protected method_ `protected virtual X509Certificate2 LoadSigningCertificate()` — Loads the signing certificate
- L567-572 _protected method_ `protected Dictionary<string, object> CreateResource(int Weight)`
- L575-581 _protected method_ `protected Dictionary<string, object> CreateOmittedResource(int Weight)`
- L584-590 _protected method_ `protected Dictionary<string, object> CreateOptionalResource(int Weight)`
- L593-599 _protected method_ `protected Dictionary<string, object> CreateNestedResource(int Weight)`
- L606-620 _private method_ `private static bool IsInsideNestedCodeBundle(string Filename, List<NestedCodeBundle> NestedBundles)` — Returns true if the given file (path relative to the root of the bundle being signed) belongs to one of the nested code bundles of that bundle, and is therefore covered by the signature of the nested bundle instead of being hashed as a resource of the containing bundle
- L627-726 _protected method_ `protected virtual byte[] BuildCodeResourcesDirectory(FileOperations.FileSystemAdapter BundleFileSystem, string CFBundleExecutable, List<NestedCodeBundle> NestedBundles)` — Creates the contents of the _CodeSignature/CodeResources file for a bundle, which holds a hash of every resource in that bundle. Any nested code bundles are referenced by the hash of their own signature rather than by hashing the individual files inside of them. The caller is responsible for writing the result out.
- L728-732 _protected method_ `protected virtual Utilities.PListHelper LoadInfoPList()`
- L739-780 _public method_ `public void PrepareForSigning()` — Prepares this signer to sign an application Modifies the following files: embedded.mobileprovision
- L785-808 _private method_ `private string BuildEntitlementString(string CFBundleIdentifier, out string TeamIdentifier)` — Creates an entitlements blob string from the entitlements structure in the mobile provision, merging in an on disk file if it is present.
- L822-870 _public method_ `public void PerformSigning()` — Does the actual work of signing the application Modifies the following files: Info.plist [Executable] (file name derived from CFBundleExecutable in the Info.plist, e.g., UnrealGame) _CodeSignature/CodeResources [ResourceRules] (file name derived from CFBundleResourceSpecification, e.g., CustomResourceRules.plist) And, for each embedded framework: Frameworks/[Name].framework/[Executable] Frameworks/[Name].framework/_CodeSignature/CodeResources
- L876-907 _protected method_ `protected virtual List<string> FindNestedCodeBundlePaths()` — Finds the nested code bundles of the application bundle, returning their paths relative to the root of the application bundle (e.g., "Frameworks/Foo.framework")
- L916-991 _protected method_ `protected virtual List<NestedCodeBundle> SignNestedCodeBundles(string TeamIdentifier, DateTime SigningTime)` — Signs each of the frameworks embedded in the application bundle, returning the information that the application bundle needs in order to reference their signatures. Nested code has to be signed before the bundle that contains it, since the code resources of the containing bundle hold the hash of the code directory of each nested bundle.
- L997-1005 _protected method_ `protected string CreateRequirementText(string BundleIdentifier)` — Creates the text form of the designated requirement of a bundle signed with the current certificate, in the same form that Apple's codesign records it in the code resources of the containing bundle
- L1010-1013 _private method_ `private static string EscapeRequirementString(string Value)` — Escapes a string so that it can be used as a quoted string inside of a requirement expression
- L1028-1314 _protected method_ `protected byte[] SignMachOImage(byte[] SourceExeData, string BundleIdentifier, string TeamIdentifier, byte[] RawInfoPList, byte[] ResourceDirBytes, string EntitlementsText, bool bIsMainExecutable, DateTime SigningTime, out byte[] CodeDirectoryHash)` — Signs one Mach-O image (either a thin binary or every architecture of a fat binary), returning the signed image. Nothing is written out, the caller decides where the result goes.
- L1321-1331 _protected method_ `protected static byte[] ComputeCanonicalCodeDirectoryHash(CodeDirectoryBlob CodeDirectory)` — Computes the canonical hash of a code directory, which is how a bundle refers to the signature of the code bundles nested inside of it. This is the hash of the code directory blob (the data that the CMS signature signs), truncated to the length of a SHA1 hash regardless of the hash type of the code directory itself.

### `Source/Programs/IOS/iPhonePackager/CompileTime.cs` (iPhonePackager)


#### class `iPhonePackager.Settings`  
`public class Settings`  
_public; L19-21_

#### class `iPhonePackager.CompileTime`  
`public class CompileTime`  
_public; L26-715_
- L32 _private field_ `private static string XcodeDeveloperDir = ""`
- L34 _private field_ `private static string iPhone_SigningDevRootMac = ""`
- L39 _private field_ `private static string MacMobileProvisionFilename` — The file name (no path) of the temporary mobile provision that will be placed on the remote mac for use in makeapp
- L40 _private field_ `private static string MacSigningIdentityFilename`
- L42 _private field_ `private static string MacName = ""`
- L43 _private field_ `private static string MacStagingRootDir = ""`
- L44 _private field_ `private static string MacBinariesDir = ""`
- L45 _private field_ `private static string MacXcodeStagingDir = ""`
- L48-51 _public property_ `public static string RemoteAppPayloadDirectory { get; }`
- L54-57 _protected property_ `protected static string RemoteAppDirectory { get; }`
- L61-64 _protected property_ `protected static string RemoteExecutablePath { get; }`
- L66 _private field_ `private static string CurrentBaseXCodeCommandLine`
- L71-102 _private method_ `static private string GetBaseXcodeCommandline()`
- L107-160 _public method_ `static public void ConfigurePaths()`
- L167-178 _public method_ `static public void OutputReceivedRemoteProcessCall(Object Sender, DataReceivedEventArgs Line)` — Logs out a line of stdout or stderr from RPCUtility.exe to the program log
- L180-208 _private* method_ `static bool FindMobileProvision(string BundleIdentifier, out string OutFileName, bool bCheckCert = true)`
- L213-238 _public method_ `static public void ExportCertificate()` — Export the certificate to a file
- L243-354 _public method_ `static public void CopyFilesNeededForMakeApp()` — Copy the files always needed (even in a stub IPA)
- L359-571 _public method_ `public static bool RunRPCUtilty( string RPCCommand, bool bIsSilent = false )`
- L577-624 _public method_ `static public void CreateApplicationDirOnMac()`
- L629-651 _public method_ `static public void PackageIPAOnMac()`
- L653-656 _public method_ `static public void DangerouslyFastMode()`
- L658-661 _public method_ `static public void ExecuteRemoteCommand(string RemoteCommand, bool bIsSilent = false)`
- L663-714 _public method_ `static public bool ExecuteCompileCommand(string Command, string RPCCommand)`

### `Source/Programs/IOS/iPhonePackager/Config.cs` (iPhonePackager)


#### class `iPhonePackager.Config`  
`internal class Config`  
_internal; L15-591_
- L20 _public field_ `public static string AppDisplayName = "Unreal iOS Configuration"` — The display name in title bars, popups, etc...
- L22 _public field_ `public static string RootRelativePath = @"..\..\..\..\"`
- L24 _public field_ `public static string GameDirectory = ""`
- L25 _public field_ `public static string BinariesDirectory = ""`
- L30 _public field_ `public static string SigningPrefix = ""` — Optional Prefix to append to .xcent and .mobileprovision files, for handling multiple certificates on same source game
- L32 _public field_ `public static string PCStagingRootDir = ""`
- L37 _public field_ `public static string PCXcodeStagingDir = ""` — The local staging directory for files needed by Xcode on the Mac (on PC)
- L42 _public field_ `public static string RepackageStagingDirectory = ""` — The staging directory from UAT that is passed into IPP (for repackaging, etc...)
- L47 _public field_ `public static string DeltaManifest = ""` — The delta manifest for deploying files for iterative deploy
- L52 _public field_ `public static List<string> FilesForBackup = new List<string>()`
- L56 _public field_ `public static string ProjectFile = ""` — The project file that is passed into IPP from UAT
- L61 _public field_ `public static string DeviceId = ""` — The device to deploy or launch on
- L66 _public field_ `public static bool bUseRPCUtil = true` — Determine whether to use RPC Util or not
- L71 _public field_ `public static string OverrideDevRoot = null` — Optional override for the dev root on the target mac for remote builds.
- L76 _public field_ `public static string OSString = "IOS"` — Optional value specifying that we are working with tvOS
- L81-91 _public property_ `public static string BuildDirectory { get; }` — The local build directory (on PC)
- L93 _public field_ `public static string XcodeGetProvisionParentDirectory = "xcodebuild -version | head -1 | sed -n 's/.* \\([0-9]*\\).*/\\1/p' | { read VERSION; if [ $VERSION -lt 16 ]; then echo \"MobileDevice\"; else echo \"Developer/Xcode/UserData\"; fi; } | xargs -L1 -I { ...`
- L95-103 _private method_ `private static string GetXcodeSpecificProvisionParentDirectory()`
- L108-117 _public property_ `public static string ProvisionDirectory { get; }` — The shared provision library directory (on PC)
- L122-131 _public property_ `public static string EngineBuildDirectory { get; }` — The shared (Engine) build directory (on PC)
- L136-146 _public property_ `public static string IntermediateDirectory { get; }` — The local build intermediate directory (on PC)
- L148-153 _private* ctor_ `static Config()`
- L158-161 _public property_ `public static string CookedDirectory { get; }` — The local directory cooked files are placed (on PC)
- L166-169 _public property_ `public static string ConfigDirectory { get; }` — The local directory config files are placed (on PC)
- L174-177 _public property_ `public static string DefaultConfigDirectory { get; }` — The engine config files are placed (on PC)
- L182-185 _public property_ `public static string EngineDirectory { get; }` — The engine directory
- L191-194 _public property_ `public static string PayloadDirectory { get; }`
- L199-202 _public property_ `public static string PayloadCookedDirectory { get; }` — The local directory that a payload (GameName.app) is assembled into before being copied to the Mac (on PC)
- L207-210 _public property_ `public static string PayloadRootDirectory { get; }` — The local directory that a payload (GameName.app) is assembled into before being copied to the Mac (on PC)
- L215-228 _public property_ `public static string IPAFilenameOnMac { get; }` — Returns the filename for the IPA (no path, just filename)
- L233-236 _public method_ `public static string GetPlistOverrideFilename()` — Returns the name of the file containing user overrides that will be applied when packaging on PC
- L238-247 _public method_ `public static string GetPlistOverrideFilename(bool bWantDistributionOverlay)`
- L252-269 _public method_ `public static string GetIPAPath(string FileSuffix)` — Returns the full path for either the stub or final IPA on the PC
- L271-306 _public method_ `public static string RemapIPAPath(string FileSuffix)`
- L312-315 _public method_ `public static string GetTargetName()` — Returns target name, either the GameName + optional Client or specified by -targetname
- L320-330 _public method_ `public static string GetIPAPathForReading(string FileSuffix)` — Returns the full path for the stub IPA, following the signing prefix resolution rules
- L335 _public field_ `public static bool bVerbose = true` — Whether or not to output extra information (like every file copy and date/time stamp)
- L340 _public field_ `public static bool bCodeSignVerbose = false` — Whether or not to output extra information in code signing
- L346 _public field_ `public static bool bCreateStubSet = false` — Whether or not non-critical files will be packaged (critical == required for signing or .app validation, the app may still fail to run with only 'critical' files present). Also affects the name and location of the IPA back on the PC
- L351 _public field_ `public static bool bForDistribution = false` — Is this a distribution packaging build? Controls a number of aspects of packing (which signing prefix and provisioning profile to use, etc...)
- L356 _public field_ `public static bool bIsCodeBasedProject = false` — Is this a c++ code based project? So far used on repackagefromstage to properly choose the .ipa name
- L361 _public field_ `public static bool bAutomaticSigning = false` — Is this going to try automatic signing?
- L366 _public field_ `public static bool bForceStripSymbols = false` — Whether or not to strip symbols (they will always be stripped when packaging for distribution)
- L371 _public field_ `public static bool bPerformResignWhenRepackaging = false` — Do a code signing update when repackaging?
- L376 _public field_ `public static bool bCookOnTheFly = false` — Whether the cooked data will be cooked on the fly or was already cooked by the books.
- L381 _public field_ `public static bool bProvision = false` — Whether the install should be performed on a provision
- L386 _public field_ `public static string Provision = ""` — provision to be installed
- L391 _public field_ `public static string ProvisionUUID = ""` — provision to be installed
- L396 _public field_ `public static string ProvisionFile` — provision to extract certificate for
- L401 _public field_ `public static string TargetName = ""` — target name specificied by the command line, if not set GameName + optional Client will be used
- L406 _public field_ `public static string TeamID = ""` — IOS Team ID to be used for automatic signing
- L411 _public field_ `public static bool bCert = false` — Whether the install should be performed on a certificate
- L416 _public field_ `public static string Certificate = ""` — Certificate to be installed
- L421 _public field_ `public static string OutputCertificate = null` — Certificate to be output
- L426 _public field_ `public static string OverrideMacName = null` — An override server Mac name
- L431 _public field_ `public static string OverrideBundleName = null` — A name to use for the bundle indentifier and display name when resigning
- L437 _public field_ `public static int RecompressionSetting = 0` — Whether to use None or Best for the compression setting when repackaging IPAs (int version of Ionic.Zlib.CompressionLevel) By making this an int, we are able to delay load the Ionic assembly from a different path (which is required)
- L442-446 _public property_ `public static string AppDirectoryInZIP { get; set; }` — Returns the application directory inside the zip
- L447 _private field_ `private static string _AppDirectoryInZIP = null`
- L453 _public field_ `public static bool bMaintainExistingRequirementsWhenCodeSigning = false` — If the requirements blob is present in the existing executable when code signing, should it be carried forward (true) or should a dummy requirements blob be created with no actual requirements (false)
- L459 _public field_ `public static bool bSignEmbeddedFrameworks = true` — Should the frameworks embedded in the application bundle be signed as well as the application itself? When this is disabled, whatever signature they were built or downloaded with is left alone.
- L464 _public field_ `public static string CodeSigningIdentity` — The code signing identity to use when signing via RPC
- L469 _public field_ `public static string MinOSVersion` — The minimum OS version
- L474 _public field_ `public static bool bIterate = false` — Create an iterative IPA (i.e. a stub only with Icons and Splash images)
- L480-483 _public method_ `public static string GetRootBackedUpDocumentsDirectory()` — Returns a path to the place to back up documents from a device
- L485-590 _public method_ `public static bool Initialize(string InitialCurrentDirectory, string GamePath)`

### `Source/Programs/IOS/iPhonePackager/ConfigureMobileGame.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.ConfigureMobileGame`  
`partial class ConfigureMobileGame`  
_internal*; L7-203_
- L12 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L18-25 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L33-187 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L191 _private field_ `private System.Windows.Forms.Label label1`
- L192 _private field_ `private System.Windows.Forms.TextBox BundleNameEdit`
- L193 _private field_ `private System.Windows.Forms.Button GenerateResignFileButton`
- L194 _private field_ `private System.Windows.Forms.TextBox BundleDisplayNameEdit`
- L195 _private field_ `private System.Windows.Forms.TextBox BundleIdentifierEdit`
- L196 _private field_ `private System.Windows.Forms.Button EditManuallyButton`
- L197 _private field_ `private System.Windows.Forms.FolderBrowserDialog PickDestFolderDialog`
- L198 _private field_ `private System.Windows.Forms.LinkLabel AppleReferenceHyperlink`
- L199 _private field_ `private System.Windows.Forms.Label label4`
- L200 _private field_ `private System.Windows.Forms.Label label2`
- L201 _private field_ `private System.Windows.Forms.Label label3`
- L202 _private field_ `private System.Windows.Forms.Label label5`

### `Source/Programs/IOS/iPhonePackager/ConfigureMobileGame.cs` (iPhonePackager)


#### class `iPhonePackager.ConfigureMobileGame`  
`public partial class ConfigureMobileGame : Form`  
_public; L19-203_
- inherits: `Form`
- L21 _public field_ `public bool bSucceededConfiguring = false`
- L23-26 _public ctor_ `public ConfigureMobileGame()`
- L37-67 _private* method_ `void ReloadPList()`
- L69-72 _private method_ `private void ReloadButton_Click(object sender, EventArgs e)`
- L74-113 _private method_ `private void SaveChanges()`
- L115-124 _private method_ `private void EditManuallyButton_Click(object sender, EventArgs e)`
- L126-141 _private* method_ `string ReadOrCreate(string Filename)`
- L143-146 _private method_ `private void ShowError(string Message)`
- L148-179 _private method_ `private void GenerateResignFileButton_Click(object sender, EventArgs e)`
- L181-189 _private method_ `private void SavePList(Utilities.PListHelper Helper, string Filename)`
- L191-195 _private method_ `private void ConfigureMobileGame_Load(object sender, EventArgs e)`
- L197-202 _private method_ `private void ShowHyperlink(object sender, LinkLabelLinkClickedEventArgs e)`

### `Source/Programs/IOS/iPhonePackager/CookTime.cs` (iPhonePackager)


#### class `iPhonePackager.CookTime`  
`public class CookTime`  
_public; L22-383_
- L27 _private field_ `static private HashSet<string> FilesBeingModifiedToPrintOut = new HashSet<string>()` — List of files being inserted or updated in the Zip
- L32-37 _private method_ `static private ZipFile SetupWorkIPA()`
- L42-85 _private method_ `static private ZipFile CreateWorkingIPA(string SourceIPAPath, string WorkIPAPath)` — Creates a copy of a source IPA to a working path and opens it up as a Zip for further modifications
- L90-114 _private method_ `static private string ExtractEmbeddedPList(ZipFile Zip)` — Extracts Info.plist from a Zip
- L116-149 _private method_ `static private void CopyEngineOrGameFiles(string Subdirectory, string Filter)`
- L151-172 _public method_ `static public void CopySignedFiles()`
- L177-186 _private method_ `static private void UpdateSaveProgress(object Sender, SaveProgressEventArgs Event)`
- L192-200 _public method_ `public static void UpdateVersion(Utilities.PListHelper Info)` — Updates the version string and then applies the settings in the user overrides plist
- L205-377 _public method_ `static public void RepackageIPAFromStub()`
- L379-382 _public method_ `static public bool ExecuteCookCommand(string Command, string RPCCommand)`

### `Source/Programs/IOS/iPhonePackager/DeployTime.cs` (iPhonePackager)


#### struct `iPhonePackager.ConnectedDeviceInformation`  
`public struct ConnectedDeviceInformation`  
_public; L20-35_
- attrs: `[Serializable]`
- L22 _public field_ `public string DeviceName`
- L23 _public field_ `public string UDID`
- L24 _public field_ `public string DeviceType`
- L25 _public field_ `public string DeviceInterface`
- L28-34 _public ctor_ `public ConnectedDeviceInformation(string DeviceName, string UDID, string DeviceType, string DeviceInterface)`

#### class `iPhonePackager.DeployTimeReporter`  
`class DeployTimeReporter`  
_internal*; L38-64_
- attrs: `[Serializable]`
- L40-43 _public method_ `public void Log(string Line)`
- L45-48 _public method_ `public void Error(string Line)`
- L50-53 _public method_ `public void Warning(string Line)`
- L55-58 _public method_ `public void SetProgressIndex(int Progress)`
- L60-63 _public method_ `public int GetTransferProgressDivider()`

#### class `iPhonePackager.DeploymentHelper`  
`class DeploymentHelper`  
_internal*; L66-536_
- L68-110 _public method_ `public static void InstallIPAOnConnectedDevices(string IPAPath)`
- L112-248 _public method_ `public static bool ExecuteDeployCommand(string Command, string GamePath, string RPCCommand)`
- L250 _private* field_ `static DeployTimeReporter Reporter = new DeployTimeReporter()`
- L251-314 _private* method_ `static string ExecuteLibimobileProcess(string ProcessName, string ProcessArguments = "", bool bTreatOutputAsUTF8 = true)`
- L315-358 _public method_ `public static bool PushFiles(string BundleIdentifier, string ManifestFile)`
- L360-387 _private* method_ `static bool BackupFiles(string BundleIdentifier, string[] DestinationFiles)`
- L389-426 _public method_ `public static bool BackupDocumentsDirectory(string BundleIdentifier, string DestinationDocumentsDirectory)`
- L428-463 _private* method_ `static bool ActionOnIPAOnDevices(string args, string IPAPath)`
- L465-468 _public method_ `public static bool UninstallIPAOnDevices(string IPAPath)`
- L470-473 _public method_ `public static bool InstallIPAOnDevices(string IPAPath)`
- L475-535 _public method_ `public static ConnectedDeviceInformation[] GetAllConnectedDevices()`

### `Source/Programs/IOS/iPhonePackager/FileOperations.cs` (iPhonePackager)


#### class `iPhonePackager.ProxyReadStream`  
`public class ProxyReadStream : Stream`  
_public; L26-117_
- inherits: `Stream`
- L28 _public field_ `public long InternalPosition`
- L29 _public field_ `public Stream ParentStream`
- L31-40 _public ctor_ `public ProxyReadStream(Stream InParentStream)`
- L42-45 _public property_ `public override bool CanRead { get; }`
- L47-50 _public property_ `public override bool CanSeek { get; }`
- L52-55 _public property_ `public override bool CanWrite { get; }`
- L57-60 _public property_ `public override long Length { get; }`
- L62-66 _public property_ `public override long Position { get; set; }`
- L68-83 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L85-88 _public method_ `public override void SetLength(long value)`
- L90-93 _public method_ `public override void Flush()`
- L95-101 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L103-106 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L108-111 _protected method_ `protected override void Dispose(bool disposing)`
- L113-116 _public method_ `public override void Close()`

#### class `iPhonePackager.FileOperations`  
`public partial class FileOperations`  
_public; L119-1137_
- L121 _private const_ `private const int DefaultRetryCount = 5`
- L123 _private field_ `private static Socket RPCSocket`
- L126-146 _private method_ `static private bool ConditionalInitRemoting(string MacName)`
- L154-157 _public method_ `static public string FindPrefixedFile(string BasePath, string FileName)` — Find a prefixable file (checks first with the prefix and then without it)
- L165-177 _public method_ `static public string FindAnyFileWithExtension(string BasePath, string FileExt)` — Finds the first file in the directory with a given extension (if it exists). This method is to provide some idiot-proofing (for example, .mobileprovision files, which will be expected to be saved from the website as GameName.mobileprovision or Distro_GameName.mobileprovision, but falling back to using the first one we find if the correctly named one is not found helps the user if they mess up during the process.
- L187-199 _public method_ `static public string FindPrefixedFileOrDirectory(string BasePath, string Name, bool bIsDirectory)` — Find a prefixable file or directory (checks first with the prefix and then without it)
- L204-239 _public method_ `static public void DeleteDirectory( DirectoryInfo DirInfo )`
- L244-261 _public method_ `static public void DeleteFile( string FileName )`
- L266-290 _private method_ `static private void RecursiveFolderCopy( DirectoryInfo SourceFolderInfo, DirectoryInfo DestFolderInfo, bool bLowercase )`
- L293-329 _public method_ `static public bool CopyFolder(string SourceFolder, string DestFolder, string DisplayDestFolder, bool bDeleteTarget, bool bLowercase)`
- L331-346 _public method_ `static public void RecursiveBatchUploadFolder(DirectoryInfo SourceFolderInfo, string DestFolder, List<string> FilesToUpload)`
- L348-390 _public method_ `static public bool BatchUploadFolder(string MacName, string SourceFolder, string DestFolder, bool bDeleteTarget)`
- L392-416 _public method_ `static public bool DownloadFile(string MacName, string SourceFilename, string DestFilename)`
- L421-425 _public method_ `static public void CopyRequiredFile(string SourcePath, string DestPath)`
- L430-433 _public method_ `static public void CopyNonEssentialFile(string SourcePath, string DestPath)`
- L438-516 _public method_ `static public bool CopyFile(FileInfo SourceFileInfo, string DestFileName, bool bCopyMustSucceed, int MaxRetryCount)`
- L521-559 _public method_ `static public bool CopyFiles( string SourceFolder, string DestFolder, string DisplayDestFolder, string FileSpec, string ExcludeExtension )`
- L564-590 _public method_ `static public bool RenameFile( string Folder, string SourceName, string DestName )`

#### class `iPhonePackager.FileOperations.FileSystemAdapter`  
`public abstract class FileSystemAdapter`  
_public; L596-614_
- desc: This class exposes an interface that represents a limited subset of file system functionality, so the same code can work with a Zip file or a raw .app directory
- L598 _public method_ `public abstract byte[] ReadAllBytes(string RelativeFilename)`
- L599 _public method_ `public abstract Stream OpenRead(string RelativeFilename)`
- L600 _public method_ `public abstract void CloseFile(Stream InStream)`
- L601 _public method_ `public abstract void WriteAllBytes(string RelativeFilename, byte[] Data)`
- L602 _public method_ `public abstract void WriteStream(string RelativeFilename, Stream Data)`
- L603 _public method_ `public abstract void Close()`
- L605 _public method_ `public abstract IEnumerable<string> GetAllPayloadFiles()`
- L611-613 _public method_ `public virtual void SetFileExecutable(string RelativeFilename)` — Marks a file as needing the executable bit set (the binary of an embedded framework for example). Does nothing by default, for file systems where the permissions of the file are already correct.

#### class `iPhonePackager.FileOperations.RegularFileSystem`  
`public class RegularFileSystem : FileSystemAdapter`  
_public; L619-687_
- inherits: `FileSystemAdapter`
- desc: Implementation of the FileSystemAdapter interface that handles the native file system
- L621 _protected field_ `protected string MyAppDirectory`
- L623-626 _protected method_ `protected string GetNativePath(string RelativeFilename)`
- L628-637 _protected method_ `protected string GetZipStyleRelativePath(string NativeFilename)`
- L639-642 _public ctor_ `public RegularFileSystem(string AppDirectory)`
- L644-647 _public method_ `public override byte[] ReadAllBytes(string RelativeFilename)`
- L649-652 _public method_ `public override Stream OpenRead(string RelativeFilename)`
- L654-656 _public method_ `public override void CloseFile(Stream InStream)`
- L658-661 _public method_ `public override void WriteAllBytes(string RelativeFilename, byte[] Data)`
- L663-668 _public method_ `public override void WriteStream(string RelativeFilename, Stream Data)`
- L670-672 _public method_ `public override void Close()`
- L674-686 _public method_ `public override IEnumerable<string> GetAllPayloadFiles()`

#### class `iPhonePackager.FileOperations.ZipFileSystem`  
`public class ZipFileSystem : FileSystemAdapter`  
_public; L692-1031_
- inherits: `FileSystemAdapter`
- desc: Implementation of the FileSystemAdapter interface that handles Zip files
- L695 _protected field_ `protected ZipFile Zip`
- L696 _protected field_ `protected string InternalRootPath`
- L699 _protected field_ `protected Dictionary<string, Stream> PendingWrites = ...`
- L699 _protected field_ `protected Dictionary< PendingWrites = new Dictionary<string, Stream>()`
- L702 _public field_ `public String ExecutableFileName` — Name of executable file name, so we can set correct attributes when zipping
- L706 _protected field_ `protected HashSet<string> AdditionalExecutableFiles = new HashSet<string>()` — Full paths of any other files that need to be marked as executable when zipping (the binaries of embedded frameworks for example)
- L712-728 _public method_ `public static string FindRootPathInIPA(ZipFile Zip)` — Finds the root path in a given IPA (e.g., "Payload/UnrealGame.app/")
- L730-734 _public ctor_ `public ZipFileSystem(string Filename)`
- L736-740 _public ctor_ `public ZipFileSystem(ZipFile InZip)`
- L742-746 _public ctor_ `public ZipFileSystem(ZipFile InZip, string RootPath)`
- L748-752 _protected method_ `protected string GetFileName(string RelativeFilename)`
- L754-759 _protected method_ `protected static void SplitPath(string RelativeFilename, out string ZipPath, out string ZipFilename)`
- L761-768 _public method_ `public override byte[] ReadAllBytes(string RelativeFilename)`
- L770-817 _public method_ `public override Stream OpenRead(string RelativeFilename)`
- L819-826 _public method_ `public override void CloseFile(Stream InStream)`
- L828-831 _public method_ `public override void WriteAllBytes(string RelativeFilename, byte[] Data)`
- L833-840 _public method_ `public override void WriteStream(string RelativeFilename, Stream Data)`
- L842-845 _public method_ `public override void SetFileExecutable(string RelativeFilename)`
- L849-864 _protected method_ `protected void EnsureDirectoriesExistInStrictPath(string DirectoryName)` — Make sure every directory in a path has an explicit entry (the input must be a directory name only, with no filename)
- L871-880 _protected method_ `protected void EnsureDirectoriesExist(string Filename)` — Make sure every directory in a fully qualified path has an explicit entry For a file named foo/bar.baz, ionic will only create one entry for foo/bar.baz, but the Mac or 7z would create a foo/ entry as well.
- L882-889 _private* method_ `void CommitWrite(string FullPath, Stream StreamData)`
- L891-990 _public method_ `public override void Close()`
- L993-1025 _public method_ `public override IEnumerable<string> GetAllPayloadFiles()`
- L1027-1030 _public method_ `public void SetCompression(Ionic.Zlib.CompressionLevel Level)`

#### class `iPhonePackager.FileOperations.ReadOnlyZipFileSystem`  
`public class ReadOnlyZipFileSystem : ZipFileSystem`  
_public; L1036-1062_
- inherits: `ZipFileSystem`
- desc: Implementation of the FileSystemAdapter interface that handles read-only access to Zip files
- L1038-1041 _public ctor_ `public ReadOnlyZipFileSystem(ZipFile InZip, string RootPath) : base(InZip, RootPath)`
- L1043-1046 _public ctor_ `public ReadOnlyZipFileSystem(ZipFile InZip) : base(InZip)`
- L1048-1050 _public ctor_ `public ReadOnlyZipFileSystem(string Filename) : base(Filename)`
- L1052-1056 _public method_ `public override void Close()`
- L1058-1061 _public method_ `public override void WriteAllBytes(string RelativeFilename, byte[] Data)`

#### class `iPhonePackager.FileOperations.SubdirectoryFileSystem`  
`public class SubdirectoryFileSystem : FileSystemAdapter`  
_public; L1069-1136_
- inherits: `FileSystemAdapter`
- desc: Implementation of the FileSystemAdapter interface that presents a subdirectory of another file system as if it was the root of that file system. This allows nested bundles (embedded frameworks) to be signed with the same code that signs the application bundle containing them.
- L1072 _protected field_ `protected FileSystemAdapter Parent` — The file system that actually holds the data
- L1075 _protected field_ `protected string PathPrefix` — The path of the subdirectory in the parent file system, including a trailing slash
- L1077-1081 _public ctor_ `public SubdirectoryFileSystem(FileSystemAdapter InParent, string SubdirectoryPath)`
- L1083-1086 _public method_ `public override byte[] ReadAllBytes(string RelativeFilename)`
- L1088-1091 _public method_ `public override Stream OpenRead(string RelativeFilename)`
- L1093-1096 _public method_ `public override void CloseFile(Stream InStream)`
- L1098-1101 _public method_ `public override void WriteAllBytes(string RelativeFilename, byte[] Data)`
- L1103-1106 _public method_ `public override void WriteStream(string RelativeFilename, Stream Data)`
- L1108-1111 _public method_ `public override void SetFileExecutable(string RelativeFilename)`
- L1113-1116 _public method_ `public override void Close()`
- L1118-1135 _public method_ `public override IEnumerable<string> GetAllPayloadFiles()`

### `Source/Programs/IOS/iPhonePackager/GenerateSigningRequestDialog.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.GenerateSigningRequestDialog`  
`partial class GenerateSigningRequestDialog`  
_internal*; L3-338_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-311 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L315 _private field_ `private System.Windows.Forms.Label LabelPrompt`
- L316 _private field_ `private System.Windows.Forms.Button GenerateRequestButton`
- L317 _private field_ `private System.Windows.Forms.Label LabelEMailAddress`
- L318 _private field_ `private System.Windows.Forms.TextBox EMailEditBox`
- L319 _private field_ `private System.Windows.Forms.TextBox CommonNameEditBox`
- L320 _private field_ `private System.Windows.Forms.Label LabelCommonName`
- L321 _private field_ `private System.Windows.Forms.SaveFileDialog SaveDialog`
- L322 _private field_ `private System.Windows.Forms.TextBox KeyPairFilenameBox`
- L323 _private field_ `private System.Windows.Forms.Label label1`
- L324 _private field_ `private System.Windows.Forms.OpenFileDialog OpenDialog`
- L325 _private field_ `private System.Windows.Forms.Label label6`
- L326 _private field_ `private System.Windows.Forms.Label label11`
- L327 _private field_ `private System.Windows.Forms.PictureBox EmailCheck`
- L328 _private field_ `private System.Windows.Forms.Label label2`
- L329 _private field_ `private System.Windows.Forms.PictureBox CommonNameCheck`
- L330 _private field_ `private System.Windows.Forms.Label label3`
- L331 _private field_ `private System.Windows.Forms.PictureBox KeyPairCheck`
- L332 _private field_ `private System.Windows.Forms.Label label4`
- L333 _private field_ `private System.Windows.Forms.PictureBox GenerateRequestCheck`
- L334 _private field_ `private System.Windows.Forms.Panel panel1`
- L335 _private field_ `private System.Windows.Forms.Button GenerateKeyPairButton`
- L336 _private field_ `private System.Windows.Forms.Button ChooseKeyPairButton`
- L337 _private field_ `private System.Windows.Forms.Label label5`

### `Source/Programs/IOS/iPhonePackager/GenerateSigningRequestDialog.cs` (iPhonePackager)


#### class `iPhonePackager.GenerateSigningRequestDialog`  
`public partial class GenerateSigningRequestDialog : Form`  
_public; L26-230_
- inherits: `Form`
- L28 _protected field_ `protected Dictionary<bool, Bitmap> CheckStateImages = ...`
- L28 _protected field_ `protected Dictionary< CheckStateImages = new Dictionary<bool, Bitmap>()`
- L30-38 _public ctor_ `public GenerateSigningRequestDialog()`
- L40-43 _private method_ `private void GenerateSigningRequestDialog_Load(object sender, EventArgs e)`
- L46-104 _private method_ `private void GenerateSigningRequestViaOpenSSL(string TargetCertRequestFileName, AsymmetricCipherKeyPair KeyPair)`
- L107-127 _private method_ `private void GenerateSigningRequestViaBouncyCastle(string TargetCertRequestFileName, AsymmetricCipherKeyPair KeyPair)`
- L129-173 _private method_ `private void GenerateRequestButton_Click(object sender, EventArgs e)`
- L175-178 _private method_ `private void GenerateSigningRequestDialog_FormClosing(object sender, FormClosingEventArgs e)`
- L180-183 _private method_ `private void GenerateSigningRequestDialog_FormClosed(object sender, FormClosedEventArgs e)`
- L185-200 _private method_ `private void GenerateKeyPairButton_Click(object sender, EventArgs e)`
- L202-216 _private method_ `private void ChooseKeyPairButton_Click(object sender, EventArgs e)`
- L218-229 _private method_ `private void ValidateCertSteps(object sender, EventArgs e)`

### `Source/Programs/IOS/iPhonePackager/GraphicalResignTool.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.GraphicalResignTool`  
`partial class GraphicalResignTool`  
_internal*; L3-725_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-666 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L670 _private field_ `private System.Windows.Forms.SaveFileDialog saveFileDialog1`
- L671 _private field_ `private System.Windows.Forms.ContextMenuStrip UDIDContextMenu`
- L672 _private field_ `private System.Windows.Forms.ToolStripMenuItem copyUDIDToClipboardToolStripMenuItem`
- L673 _private field_ `private System.Windows.Forms.ToolStripMenuItem CheckThisUDIDAgainstAMobileprovMenuItem`
- L674 _private field_ `private System.Windows.Forms.ToolStripMenuItem CheckUDIDInIPAMenuItem`
- L675 _private field_ `private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2`
- L676 _private field_ `private System.Windows.Forms.ContextMenuStrip ProfilesMenu`
- L677 _private field_ `private System.Windows.Forms.ToolStripMenuItem copySelectedToolStripMenuItem`
- L678 _private field_ `private System.Windows.Forms.ToolStripMenuItem copyFullPathToProvisionToolStripMenuItem`
- L679 _private field_ `private System.Windows.Forms.ToolStripMenuItem exportCertificateToolStripMenuItem`
- L680 _public field_ `public System.Windows.Forms.TabPage DeploymentPage`
- L681 _private field_ `private System.Windows.Forms.Button UninstallIPAButton`
- L682 _private field_ `private System.Windows.Forms.Button BackupDocumentsButton`
- L683 _private field_ `private System.Windows.Forms.Button CheckProvisionForUDIDButton`
- L684 _private field_ `private System.Windows.Forms.Button CheckIPAForUDIDButton`
- L685 _private field_ `private System.Windows.Forms.Label label3`
- L686 _private field_ `private System.Windows.Forms.TextBox ScanningUDIDEdit`
- L687 _private field_ `private System.Windows.Forms.Label label2`
- L688 _private field_ `private System.Windows.Forms.ListView ConnectedDevicesList`
- L689 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader1`
- L690 _private field_ `private System.Windows.Forms.ColumnHeader columnHeader2`
- L691 _private field_ `private System.Windows.Forms.ColumnHeader DeviceTypeHeader`
- L692 _private field_ `private System.Windows.Forms.Button FetchUDIDButton`
- L693 _private field_ `private System.Windows.Forms.Button InstallIPAButton`
- L694 _public field_ `public System.Windows.Forms.TabPage ResignPage`
- L695 _private field_ `private System.Windows.Forms.GroupBox groupBox5`
- L696 _private field_ `private System.Windows.Forms.CheckBox CBCompressModifiedFiles`
- L697 _private field_ `private System.Windows.Forms.Button ResignButton`
- L698 _private field_ `private System.Windows.Forms.GroupBox groupBox4`
- L699 _private field_ `private System.Windows.Forms.Button InputIPABrowseButton`
- L700 _private field_ `private System.Windows.Forms.TextBox IPAFilenameEdit`
- L701 _private field_ `private System.Windows.Forms.GroupBox groupBox3`
- L702 _private field_ `private System.Windows.Forms.TextBox BundleIDEdit`
- L703 _private field_ `private System.Windows.Forms.Label label6`
- L704 _private field_ `private System.Windows.Forms.TextBox DisplayNameEdit`
- L705 _private field_ `private System.Windows.Forms.Label label5`
- L706 _private field_ `private System.Windows.Forms.Button ImportInfoButton`
- L707 _private field_ `private System.Windows.Forms.Button ExportInfoButton`
- L708 _private field_ `private System.Windows.Forms.RadioButton RBReplaceInfoPList`
- L709 _private field_ `private System.Windows.Forms.RadioButton RBModifyInfoPList`
- L710 _private field_ `private System.Windows.Forms.RadioButton RBLeaveInfoPListAlone`
- L711 _private field_ `private System.Windows.Forms.GroupBox groupBox2`
- L712 _private field_ `private System.Windows.Forms.RadioButton RBUseExplicitCert`
- L713 _private field_ `private System.Windows.Forms.RadioButton RBSearchForMatchingCert`
- L714 _private field_ `private System.Windows.Forms.Button CertificateBrowseButton`
- L715 _private field_ `private System.Windows.Forms.TextBox CertificateEdit`
- L716 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L717 _private field_ `private System.Windows.Forms.RadioButton RBSpecifyMobileProvision`
- L718 _private field_ `private System.Windows.Forms.RadioButton RBUseEmbeddedProvision`
- L719 _private field_ `private System.Windows.Forms.Button MobileProvisionBrowseButton`
- L720 _private field_ `private System.Windows.Forms.TextBox MobileProvisionEdit`
- L721 _public field_ `public System.Windows.Forms.TabControl TabBook`

### `Source/Programs/IOS/iPhonePackager/GraphicalResignTool.cs` (iPhonePackager)


#### class `iPhonePackager.GraphicalResignTool`  
`public partial class GraphicalResignTool : Form`  
_public; L19-647_
- inherits: `Form`
- L22 _public field_ `public static GraphicalResignTool ActiveInstance = null`
- L24 _private field_ `private string ExportImportPListFilename = ""`
- L25 _private field_ `private byte[] ImportedPListData = null`
- L27-34 _public method_ `public static GraphicalResignTool GetActiveInstance()`
- L36-47 _public ctor_ `public GraphicalResignTool()`
- L53-55 _private* method_ `void InitializeGameSelectionBox()` — Reads through directories that are peer to Binaries for any that match the *Game pattern and adds the games to a drop-down list that can be picked.
- L57-60 _private method_ `private void GraphicalResignTool_Load(object sender, EventArgs e)`
- L63-71 _private method_ `private void InputIPABrowseButton_Click(object sender, EventArgs e)`
- L73-80 _private method_ `private void MobileProvisionBrowseButton_Click(object sender, EventArgs e)`
- L82-89 _private method_ `private void CertificateBrowseButton_Click(object sender, EventArgs e)`
- L91-94 _private* method_ `void ShowError(string Context, Exception ex)`
- L96-99 _private* method_ `void ShowErrorMessage(string Msg, params object [] Args)`
- L101-130 _private method_ `private void ExportInfoButton_Click(object sender, EventArgs e)`
- L132-147 _private method_ `private void ImportInfoButton_Click(object sender, EventArgs e)`
- L149-160 _private method_ `private void SwitchingInfoEditMode(object sender, EventArgs e)`
- L162-166 _private method_ `private void SwitchingSigningMode(object sender, EventArgs e)`
- L168-172 _private method_ `private void SwitchingMobileProvisionMode(object sender, EventArgs e)`
- L174-210 _private method_ `private void ResignButton_Click(object sender, EventArgs e)`
- L258-331 _private* method_ `void ResignIPA(FileOperations.FileSystemAdapter FileSystem)`
- L333-336 _private method_ `private void CloseThisWindowButton_Click(object sender, EventArgs e)`
- L338-349 _private method_ `private void InstallIPAButton_Click(object sender, EventArgs e)`
- L351-354 _private method_ `private void UninstallIPAButton_Click(object sender, EventArgs e)`
- L356-387 _private* method_ `void ScanConnectedDevices()`
- L389-392 _private method_ `private void FetchUDIDButton_Click(object sender, EventArgs e)`
- L394-397 _private method_ `private void UDIDContextMenu_Opening(object sender, CancelEventArgs e)`
- L399-402 _private method_ `private void textBox1_TextChanged(object sender, EventArgs e)`
- L404-408 _private method_ `private void ImportCertificateButton3_Click(object sender, EventArgs e)`
- L410-414 _private method_ `private void ImportProvisionButton3_Click(object sender, EventArgs e)`
- L416-418 _private* method_ `void RefreshProvisionsList()`
- L420-423 _private method_ `private void RefreshProvisionListButton_Click(object sender, EventArgs e)`
- L425-431 _private method_ `private void GraphicalResignTool_FormClosed(object sender, FormClosedEventArgs e)`
- L433-439 _private method_ `private void TabBook_SelectedIndexChanged(object sender, EventArgs e)`
- L441-454 _private method_ `private void GameSelectionBox_SelectedIndexChanged(object sender, EventArgs e)`
- L456-458 _private method_ `private void copyToolStripMenuItem_Click(object sender, EventArgs e)`
- L460-462 _private method_ `private void copyFullPathToProvisionToolStripMenuItem_Click(object sender, EventArgs e)`
- L464-467 _private method_ `private void GraphicalResignTool_Shown(object sender, EventArgs e)`
- L469-486 _private method_ `private void copyUDIDToClipboardToolStripMenuItem_Click(object sender, EventArgs e)`
- L488-505 _private* method_ `static void CheckProvisionForUDID(MobileProvision Provision, string UDID, string Context)`
- L507-522 _private* method_ `void PickProvisionAndCheckForUDID(string UDID)`
- L524-534 _private method_ `private void CheckThisUDIDAgainstAMobileprovMenuItem_Click(object sender, EventArgs e)`
- L536-551 _private* method_ `void PickIpaAndCheckForUDID(string UDID)`
- L553-563 _private method_ `private void CheckUDIDInIPAMenuItem_Click(object sender, EventArgs e)`
- L565-577 _private method_ `private void CheckIPAForUDIDButton_Click(object sender, EventArgs e)`
- L579-591 _private method_ `private void CheckProvisionForUDIDButton_Click(object sender, EventArgs e)`
- L593-614 _private* method_ `string PickIPAAndFetchBundleIdentifier()`
- L616-628 _private method_ `private void BackupDocumentsButton_Click(object sender, EventArgs e)`
- L630-642 _private method_ `private void UninstallIPAButton_Click_1(object sender, EventArgs e)`
- L644-646 _private method_ `private void exportCertificateToolStripMenuItem_Click(object sender, EventArgs e)`

#### class `iPhonePackager.GraphicalResignTool.CustomCodeSigner`  
`class CustomCodeSigner : CodeSignatureBuilder`  
_private*; L215-253_
- inherits: `CodeSignatureBuilder`
- desc: This class is used to override specific parts of the default resigning behavior
- L220 _public field_ `public byte[] CustomMobileProvision = null` — If non-null, this will be used instead of the existing embedded mobile provision
- L225 _public field_ `public X509Certificate2 CustomSigningCert = null` — If non-null, this certificate will be used instead of doing a cert scan
- L230 _public field_ `public byte[] CustomInfoPList = null` — If non-null, this data will completely replace the original Info.plist
- L232-235 _protected method_ `protected override byte[] GetMobileProvision(string CFBundleIdentifier)`
- L237-240 _protected method_ `protected override X509Certificate2 LoadSigningCertificate()`
- L242-252 _protected method_ `protected override Utilities.PListHelper LoadInfoPList()`

### `Source/Programs/IOS/iPhonePackager/MachObjects.cs` (iPhonePackager)


#### enum `MachObjectHandling.CpuType`  
`public enum CpuType`  
_public; L29-36_
- L31 _public* enumerator_ `ARCH_ABI64 = 0x1000000`
- L32 _public* enumerator_ `I386 = 7`
- L33 _public* enumerator_ `ARM = 12`
- L34 _public* enumerator_ `POWERPC = 18`
- L35 _public* enumerator_ `ARM64 = ARCH_ABI64 | ARM`

#### class `MachObjectHandling.Bits`  
`public class Bits`  
_public; L38-49_
- L45-48 _public method_ `public static int Bytes(Num num)`

#### enum `MachObjectHandling.Bits.Num`  
`public enum Num`  
_public; L40-44_
- L42 _public* enumerator_ `_32 = 32`
- L43 _public* enumerator_ `_64 = 64`

#### class `MachObjectHandling.RWContextBase`  
`public abstract class RWContextBase`  
_public; L51-123_
- L53 _protected field_ `protected bool bIsOutput = false`
- L54 _public field_ `public bool bStreamLittleEndian = true`
- L55 _protected field_ `protected Stack<long> Positions = new Stack<long>()`
- L56 _protected field_ `protected byte[] SwapBuffer = new byte[8]`
- L59 _protected field_ `protected long ArchiveFileOffset`
- L61-74 _public method_ `public void OpenFatArchiveAt(long AtOffset)`
- L75-83 _public method_ `public void CloseFatArchive()`
- L85-89 _public method_ `public void PushPositionAndJump(long NewOffset)`
- L91-94 _public method_ `public void PushPosition()`
- L96-99 _public method_ `public void PopPosition()`
- L101-105 _public property_ `public abstract long Position { get; set; }`
- L107-116 _public method_ `public void VerifyStreamPosition(long StartingStreamPosition, long JustReadCount)`
- L118-122 _public method_ `public void VerifyStreamPosition(ref long StreamPosition, long JustReadCount)`

#### class `MachObjectHandling.ReadingContext`  
`public class ReadingContext : RWContextBase`  
_public; L125-209_
- inherits: `RWContextBase`
- L127 _protected field_ `protected BinaryReader SR`
- L129-132 _public ctor_ `public ReadingContext(BinaryReader Stream)`
- L134-138 _public property_ `public override long Position { get; set; }`
- L140-146 _public method_ `public UInt64 ReadUInt(Bits.Num Num)`
- L148-160 _public method_ `public UInt32 ReadUInt32()`
- L162-174 _public method_ `public UInt64 ReadUInt64()`
- L176-179 _public method_ `public byte[] ReadBytes(int DataSize)`
- L181-184 _public method_ `public byte[] ReadBytes(UInt32 DataSize)`
- L186-189 _public method_ `public byte ReadByte()`
- L191-194 _public method_ `public string ReadFixedASCII(int Length)`
- L196-208 _public method_ `public string ReadASCIIZ()`

#### class `MachObjectHandling.WritingPhase`  
`public class WritingPhase`  
_public; L212-246_
- L214 _public delegate_ `public delegate void DelayedWriteCallback(WritingContext Context)`
- L216 _public field_ `public Queue<DelayedWriteCallback> PendingWrites = new Queue<DelayedWriteCallback>()`
- L218-240 _public method_ `public void Drain(WritingContext Context)`
- L242-245 _public property_ `public bool bWorkRemaining { get; }`

#### class `MachObjectHandling.DeferredFieldU32or64`  
`public class DeferredFieldU32or64`  
_public; L248-281_
- L251 _protected field_ `protected long AnchorPoint`
- L254 _public field_ `public long WritePoint`
- L256 _public field_ `public Bits.Num AddressSize`
- L258-265 _public ctor_ `public DeferredFieldU32or64(WritingContext Context, long Base, Bits.Num Address)`
- L267-280 _public method_ `public void Commit(WritingContext Context)`

#### class `MachObjectHandling.LengthFieldU32or64`  
`public class LengthFieldU32or64 : DeferredFieldU32or64`  
_public; L283-294_
- inherits: `DeferredFieldU32or64`
- L285-288 _public ctor_ `public LengthFieldU32or64(WritingContext Context, long BaseOffset, Bits.Num Address) : base(Context, BaseOffset, Address)`
- L290-293 _public method_ `public void Rebase(long NewBaseOffset)`

#### class `MachObjectHandling.OffsetFieldU32or64`  
`public class OffsetFieldU32or64 : DeferredFieldU32or64`  
_public; L296-302_
- inherits: `DeferredFieldU32or64`
- L298-301 _public ctor_ `public OffsetFieldU32or64(WritingContext Context, long BaseOffset, Bits.Num Address) : base(Context, BaseOffset, Address)`

#### class `MachObjectHandling.WritingContext`  
`public class WritingContext : RWContextBase`  
_public; L304-498_
- inherits: `RWContextBase`
- L306 _public field_ `public WritingPhase CurrentPhase = new WritingPhase()`
- L308 _private* field_ `Stack<WritingPhase> PendingPhases = new Stack<WritingPhase>()`
- L310-314 _public method_ `public void CreateNewPhase()`
- L316-320 _public method_ `public void Flush()`
- L326-337 _public method_ `public bool ProcessEntirePhase()` — Processes a phase worth of work, returning false when no work remains
- L339-342 _public method_ `public LengthFieldU32or64 WriteDeferredLength(long AlreadyCountedBytes, Bits.Num Num)`
- L344-347 _public method_ `public void CommitDeferredField(DeferredFieldU32or64 Field)`
- L355-358 _public method_ `public OffsetFieldU32or64 WriteDeferredOffset(long AlreadyCountedBytes, Bits.Num Num)` — Emits an offset field that needs to be committed once the true offset is known
- L367-370 _public method_ `public OffsetFieldU32or64 WriteDeferredOffsetFrom(long BasePosition, Bits.Num Num)` — Emits an offset field that needs to be committed once the true offset is known
- L372 _protected field_ `protected BinaryWriter SW`
- L374-378 _public ctor_ `public WritingContext(BinaryWriter Stream)`
- L380-384 _public property_ `public override long Position { get; set; }`
- L386-392 _public method_ `public void CompleteWritingAndClose()`
- L394-408 _public method_ `public void WriteZeros(long NumZeros)`
- L410-416 _public method_ `public void WriteUInt(UInt64 Value, Bits.Num Num)`
- L418-430 _public method_ `public void Write(UInt32 Value)`
- L432-444 _public method_ `public void Write(UInt64 Value)`
- L446-449 _public method_ `public void Write(int Value)`
- L451-454 _public method_ `public void Write(byte[] Buffer)`
- L456-459 _public method_ `public void Write(byte[] Buffer, int Offset, int Length)`
- L461-464 _public method_ `public void Write(byte Value)`
- L466-469 _public method_ `public void WriteFixedASCII(string Value, int BufferLength)`
- L471-474 _public method_ `public void WriteAbsoluteOffsetAndDelayedData(byte[] Data, long Alignment, Bits.Num Num)`
- L476-497 _public method_ `public void WriteOffsetAndDelayedData(byte[] Data, long Alignment, long OffsetFrom, Bits.Num Num)`

#### class `MachObjectHandling.MachSection`  
`class MachSection`  
_internal*; L505-595_
- desc: Information about a single section within a segment Warning: Contains absolute file offsets
- L507 _private* field_ `string SectionName`
- L508 _private* field_ `string SegmentName`
- L509 _private* field_ `UInt64 Addr`
- L510 _private* field_ `UInt64 Size`
- L512 _private* field_ `UInt32 LogAlignment`
- L513 _private* field_ `UInt32 RelocationOffset`
- L514 _private* field_ `UInt32 NumRelocations`
- L515 _private* field_ `int Flags`
- L516 _private* field_ `UInt32 Reserved1`
- L517 _private* field_ `UInt32 Reserved2`
- L519 _private* field_ `UInt32 Reserved3`
- L521 _private* field_ `Bits.Num AddressSize`
- L523 _private* field_ `byte[] SectionData`
- L526 _private* const_ `const int S_ZEROFILL = 0x1`
- L527 _private* const_ `const int S_GB_ZEROFILL = 0xC`
- L529-532 _public ctor_ `public MachSection(Bits.Num Num)`
- L534-541 _public property_ `public int SectionType { get; set; }`
- L543-576 _public method_ `public void Read(ReadingContext SR)`
- L578-594 _public method_ `public void Write(WritingContext SW)`

#### class `MachObjectHandling.MachLoadCommand`  
`public abstract class MachLoadCommand`  
_public; L597-763_
- L599 _public field_ `public UInt32 Command`
- L600 _public field_ `public bool RequiredForDynamicLoad`
- L608 _public field_ `public long StartingLoadOffset = -1` — The offset (in bytes) from the start of the file when loading this command from a Mach Object file, or -1 if this was created in memory. Only used for special modification code that modifies individual commands without fully understanding the file format, since MachO files aren't designed in such a way that allows piecemeal modifications...
- L613 _public const_ `public const UInt32 LC_SEGMENT = 0x01` — Information on a segment (payload type: MachLoadCommandSegment)
- L614 _public const_ `public const UInt32 LC_SEGMENT_64 = 0x19`
- L619 _public const_ `public const UInt32 LC_SYMTAB = 0x02` — Symbol and string tables (payload type: MachLoadCommandSymbolTable)
- L624 _public const_ `public const UInt32 LC_THREAD = 0x04` — Defines information about the main thread (payload type: MachLoadCommandMainThreadInfo)
- L625 _public const_ `public const UInt32 LC_UNIXTHREAD = 0x05`
- L630 _public const_ `public const UInt32 LC_DYSYMTAB = 0x0B` — Information about the parts of the symbol table that are used for dynamic linking (payload type: MachLoadCommandDynamicSymbolTable)
- L633 _public const_ `public const UInt32 LC_LOAD_DYLIB = 0x0C`
- L634 _public const_ `public const UInt32 LC_ID_DYLIB = 0x0D`
- L639 _public const_ `public const UInt32 LC_LOAD_DYLINKER = 0x0E` — Specifies the name of the dynamic linker to use (payload type: MachLoadCommandDynamicLinkerName)
- L640 _public const_ `public const UInt32 LC_ID_DYLINKER = 0x0F`
- L645 _public const_ `public const UInt32 LC_LOAD_WEAK_DYLIB = 0x18` — Specifies a weak dynamically linked library (payload type: MachLoadCommandReferencedDLL)
- L650 _public const_ `public const UInt32 LC_UUID = 0x1B` — Specifies a GUID (payload type: MachLoadCommandUUID)
- L655 _public const_ `public const UInt32 LC_CODE_SIGNATURE = 0x1D` — Specifies the code signature information
- L660 _public const_ `public const UInt32 LC_ENCRYPTION_INFO = 0x21` — Specifies an encrypted segment (payload type: MachLoadCommandEncryptedSegmentInfo)
- L665 _public const_ `public const UInt32 LC_DYLD_INFO = 0x22` — Specifies information the dynamic loader needs to load this object (payload type: MachLoadCommandDynamicLoaderInfo)
- L668 _protected method_ `protected abstract void PackageData(WritingContext SW)`
- L669 _protected method_ `protected abstract void UnpackageData(ReadingContext SR, int CommandSize)`
- L671-746 _public method_ `public static MachLoadCommand CreateFromStream(ReadingContext SR)`
- L748-762 _public method_ `public void Write(WritingContext SW)`

#### class `MachObjectHandling.MachLoadCommandOpaque`  
`class MachLoadCommandOpaque : MachLoadCommand`  
_internal*; L768-824_
- inherits: `MachLoadCommand`
- desc: Opaque mach load command
- L770 _protected field_ `protected byte[] MyCommandData`
- L772-775 _protected method_ `protected override void PackageData(WritingContext SW)`
- L777-782 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L788-818 _protected method_ `protected string PayloadToString(int N, int Offset)` — Converts the N bytes at starting at Offset of the payload buffer to text (standard hex editor rules) If N is 0, N is set to the size of the payload
- L820-823 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandLinkEditBlob`  
`class MachLoadCommandLinkEditBlob : MachLoadCommand`  
_internal*; L831-852_
- inherits: `MachLoadCommand`
- desc: A blob of data in the __LINKEDIT segment Warning: Contains absolute file offsets
- L833 _public field_ `public UInt32 BlobFileOffset`
- L834 _public field_ `public UInt32 BlobFileSize`
- L836-840 _protected method_ `protected override void PackageData(WritingContext SW)`
- L842-846 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L848-851 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandSegment`  
`class MachLoadCommandSegment : MachLoadCommand`  
_internal*; L858-984_
- inherits: `MachLoadCommand`
- desc: Payload for LC_SEGMENT && LC_SEGMENT_64 Warning: Contains absolute file offsets (what an awful file format!)
- L860 _public field_ `public string SegmentName`
- L862 _public field_ `public UInt64 VirtualAddress`
- L863 _public field_ `public UInt64 VirtualSize`
- L865 _public field_ `public UInt64 FileOffset`
- L866 _public field_ `public UInt64 FileSize`
- L868 _public field_ `public UInt32 MaxProt`
- L869 _public field_ `public UInt32 InitProt`
- L870 _public field_ `public List<MachSection> Sections = new List<MachSection>()`
- L871 _public field_ `public UInt32 Flags`
- L873 _public field_ `public Bits.Num AddressSize`
- L875-878 _public ctor_ `public MachLoadCommandSegment(Bits.Num Addressing)`
- L883-914 _public method_ `public void PatchFileLength(WritingContext SW, UInt32 NewLength)` — Patches just the file length of this segment in an existing file
- L916-951 _protected method_ `protected override void PackageData(WritingContext SW)`
- L953-956 _public method_ `public override string ToString()`
- L958-983 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`

#### class `MachObjectHandling.MachLoadCommandSymbolTable`  
`class MachLoadCommandSymbolTable : MachLoadCommand`  
_internal*; L990-1019_
- inherits: `MachLoadCommand`
- desc: Payload for LC_SYMTAB Warning: Contains absolute offsets
- L992 _private* field_ `UInt32 SymbolTableOffset`
- L993 _private* field_ `UInt32 SymbolCount`
- L994 _private* field_ `UInt32 StringTableOffset`
- L995 _private* field_ `UInt32 StringTableSize`
- L997-1003 _protected method_ `protected override void PackageData(WritingContext SW)`
- L1005-1011 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L1013-1018 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandMainThreadInfo`  
`class MachLoadCommandMainThreadInfo : MachLoadCommandOpaque`  
_internal*; L1024-1038_
- inherits: `MachLoadCommandOpaque`
- desc: Payload for LC_THREAD and LC_UNIXTHREAD
- L1026-1037 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandDynamicSymbolTable`  
`class MachLoadCommandDynamicSymbolTable : MachLoadCommand`  
_internal*; L1044-1069_
- inherits: `MachLoadCommand`
- desc: Payload for LC_DYSYMTAB Warning: Contains absolute file offsets
- L1046 _private* field_ `UInt32 [] Payload = new UInt32[18]`
- L1049-1055 _protected method_ `protected override void PackageData(WritingContext SW)`
- L1057-1063 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L1065-1068 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandDylib`  
`class MachLoadCommandDylib : MachLoadCommandOpaque`  
_internal*; L1074-1097_
- inherits: `MachLoadCommandOpaque`
- desc: Payload for LC_LOAD_DYLIB, LC_LOAD_WEAK_DYLIB, and LC_ID_DYLIB
- L1076-1096 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandDynamicLinkerName`  
`class MachLoadCommandDynamicLinkerName : MachLoadCommandOpaque`  
_internal*; L1102-1108_
- inherits: `MachLoadCommandOpaque`
- desc: Payload for LC_LOAD_DYLINKER and LC_ID_DYLINKER
- L1104-1107 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandUUID`  
`class MachLoadCommandUUID : MachLoadCommandOpaque`  
_internal*; L1113-1120_
- inherits: `MachLoadCommandOpaque`
- desc: Payload for LC_UUID
- L1115-1119 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandEncryptedSegmentInfo`  
`class MachLoadCommandEncryptedSegmentInfo : MachLoadCommand`  
_internal*; L1125-1149_
- inherits: `MachLoadCommand`
- desc: Payload for LC_ENCRYPTION_INFO
- L1127 _private* field_ `UInt32 EncryptedFileOffset`
- L1128 _private* field_ `UInt32 EncryptedFileSize`
- L1129 _private* field_ `UInt32 EncryptionMode`
- L1131-1136 _protected method_ `protected override void PackageData(WritingContext SW)`
- L1138-1143 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L1145-1148 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandDynamicLoaderInfo`  
`class MachLoadCommandDynamicLoaderInfo : MachLoadCommand`  
_internal*; L1155-1181_
- inherits: `MachLoadCommand`
- desc: Payload for LC_DYLD_INFO Warning: Contains absolute file offsets
- L1157 _private* field_ `UInt32[] Payload = new UInt32[10]`
- L1160-1166 _protected method_ `protected override void PackageData(WritingContext SW)`
- L1169-1175 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L1177-1180 _public method_ `public override string ToString()`

#### class `MachObjectHandling.SigningBlob`  
`class SigningBlob`  
_internal*; L1183-1186_
- L1185 _private* const_ `const UInt32 Magic = 0xC00CDEFA`

#### class `MachObjectHandling.MachObjectFile`  
`public class MachObjectFile`  
_public; L1188-1304_
- L1190 _public field_ `public UInt32 Magic`
- L1191 _public field_ `public UInt32 CpuType`
- L1192 _public field_ `public UInt32 CpuSubType`
- L1193 _public field_ `public UInt32 FileType`
- L1196 _public field_ `public UInt32 Flags`
- L1197 _public field_ `public UInt32 Reserved64`
- L1199 _public field_ `public List<MachLoadCommand> Commands = new List<MachLoadCommand>()`
- L1202 _public const_ `public const UInt32 MH_MAGIC = 0xFEEDFACE`
- L1203 _public const_ `public const UInt32 MH_CIGAM = 0xCEFAEDFE`
- L1204 _public const_ `public const UInt32 MH_MAGIC_64 = 0xFEEDFACF`
- L1205 _public const_ `public const UInt32 MH_CIGAM_64 = 0xCFFAEDFE`
- L1208 _public const_ `public const UInt32 MH_EXECUTE = 2`
- L1210 _public const_ `public const int MachHeaderPad = 0x1A60`
- L1212-1246 _public method_ `public void Read(ReadingContext SR)`
- L1248-1278 _public method_ `public void Write(WritingContext Context)`
- L1280-1286 _public method_ `public void LoadFromFile(string Filename)`
- L1288-1295 _public method_ `public void LoadFromBytes(byte[] Data)`
- L1297-1303 _public method_ `public void WriteToFile(string Filename)`

#### class `MachObjectHandling.EntitlementsBlob`  
`public class EntitlementsBlob : OpaqueBlob`  
_public; L1309-1327_
- inherits: `OpaqueBlob`
- desc: Blob for magic CSMAGIC_ENTITLEMENTS
- L1311-1314 _public ctor_ `public EntitlementsBlob()`
- L1316-1319 _public method_ `public override string ToString()`
- L1321-1326 _public method_ `public static EntitlementsBlob Create(string EntitlementsText)`

#### class `MachObjectHandling.EntitlementsDerBlob`  
`public class EntitlementsDerBlob : OpaqueBlob`  
_public; L1332-1428_
- inherits: `OpaqueBlob`
- desc: Blob for magic CSMAGIC_ENTITLEMENTS_DER
- L1334-1337 _public ctor_ `public EntitlementsDerBlob()`
- L1339-1342 _public method_ `public override string ToString()`
- L1344-1427 _public method_ `public static EntitlementsDerBlob Create(string EntitlementsXmlText)`

#### class `MachObjectHandling.RequirementsBlob`  
`public class RequirementsBlob : SuperBlob`  
_public; L1436-1490_
- inherits: `SuperBlob`
- desc: Blob for magic CSMAGIC_REQUIREMENTS_TABLE http://www.opensource.apple.com/source/libsecurity_codesigning/libsecurity_codesigning-36885/lib/requirement.h Currently does not attempt to understand or parse the individual requirements and treats them as opaque data
- L1438-1441 _public ctor_ `public RequirementsBlob()`
- L1444 _private* const_ `const int kSecHostRequirementType = 1`
- L1447 _private* const_ `const int kSecGuestRequirementType = 2`
- L1450 _private* const_ `const int kSecDesignatedRequirementType = 3`
- L1453 _private* const_ `const int kSecLibraryRequirementType = 4`
- L1455-1458 _public method_ `public static RequirementsBlob CreateEmpty()`
- L1460-1475 _protected method_ `protected string KeyToString(int Key)`
- L1477-1489 _public method_ `public override string ToString()`

#### class `MachObjectHandling.RequirementBlob`  
`public class RequirementBlob : OpaqueBlob`  
_public; L1492-1854_
- inherits: `OpaqueBlob`
- L1494 _private* const_ `const UInt32 kOpUnknown = 1000`
- L1495 _private* const_ `const UInt32 kOpIdent = 2`
- L1496 _private* const_ `const UInt32 kOpAnchorHash = 4`
- L1497 _private* const_ `const UInt32 kOpAnd = 6`
- L1498 _private* const_ `const UInt32 kOpCertField = 11`
- L1499 _private* const_ `const UInt32 kOpCertGeneric = 14`
- L1500 _private* const_ `const UInt32 kOpGenericAnchor = 15`
- L1757 _private* const_ `const int kReqExpression = 1`
- L1759 _private* const_ `const int kMatchExists = 0`
- L1760 _private* const_ `const int kMatchEqual = 1`
- L1762 _private* field_ `string BundleIdentifier = ""`
- L1763 _private* field_ `string CertificateName = ""`
- L1765 _public field_ `public ExpressionOp Expression = null`
- L1767-1770 _public ctor_ `public RequirementBlob()`
- L1772-1777 _public method_ `public static RequirementBlob CreateFromCertificate(X509Certificate2 SigningCert, string Bundle, ExpressionOp OldReq = null)`
- L1782-1817 _public method_ `public static string GetCommonNameFromCert(X509Certificate2 SigningCert)` — Returns the common name of a certificate, which is the name that requirements match a signature against
- L1819-1833 _protected method_ `protected void InitializeFromCert(X509Certificate2 SigningCert, string Bundle, ExpressionOp OldReq = null)`
- L1835-1841 _protected method_ `protected override void PackageData(WritingContext SW)`
- L1843-1853 _protected method_ `protected override void UnpackageData(ReadingContext SR, UInt32 Length)`

#### class `MachObjectHandling.RequirementBlob.ExpressionOp`  
`public class ExpressionOp`  
_public; L1502-1560_
- L1504 _public field_ `public UInt32 OpVal = kOpUnknown`
- L1506 _public ctor_ `public ExpressionOp()`
- L1507-1510 _public ctor_ `public ExpressionOp(UInt32 InOpVal)`
- L1512-1513 _public method_ `public virtual void ReadData(ReadingContext SR)`
- L1515-1518 _public method_ `public virtual void WriteData(WritingContext SW)`
- L1520-1521 _public method_ `public virtual void UpdateCertificateAndBundle(string CertificateName, string BundleIdentifier)`
- L1523-1559 _public method_ `static public ExpressionOp ReadOperand(ReadingContext SR)`

#### class `MachObjectHandling.RequirementBlob.AndOp`  
`class AndOp : ExpressionOp`  
_private*; L1562-1590_
- inherits: `ExpressionOp`
- L1564 _public field_ `public ExpressionOp Op1`
- L1565 _public field_ `public ExpressionOp Op2`
- L1567-1570 _public ctor_ `public AndOp()`
- L1572-1576 _public method_ `public override void ReadData(ReadingContext SR)`
- L1578-1583 _public method_ `public override void WriteData(WritingContext SW)`
- L1585-1589 _public method_ `public override void UpdateCertificateAndBundle(string CertificateName, string BundleIdentifier)`

#### class `MachObjectHandling.RequirementBlob.IdentOp`  
`class IdentOp : ExpressionOp`  
_private*; L1592-1624_
- inherits: `ExpressionOp`
- L1594 _public field_ `public string BundleIdentifier`
- L1596-1599 _public ctor_ `public IdentOp()`
- L1601-1608 _public method_ `public override void ReadData(ReadingContext SR)`
- L1610-1618 _public method_ `public override void WriteData(WritingContext SW)`
- L1620-1623 _public method_ `public override void UpdateCertificateAndBundle(string InCertificateName, string InBundleIdentifier)`

#### class `MachObjectHandling.RequirementBlob.CertFieldOp`  
`class CertFieldOp : ExpressionOp`  
_private*; L1626-1681_
- inherits: `ExpressionOp`
- L1628 _public field_ `public int CertificateIndex = 0`
- L1629 _public field_ `public string FieldName = "subject.CN"`
- L1635 _private* field_ `MatchSuffix MatchOp`
- L1637-1641 _public ctor_ `public CertFieldOp()`
- L1643-1658 _public method_ `public override void ReadData(ReadingContext SR)`
- L1660-1675 _public method_ `public override void WriteData(WritingContext SW)`
- L1677-1680 _public method_ `public override void UpdateCertificateAndBundle(string InCertificateName, string InBundleIdentifier)`

#### struct `MachObjectHandling.RequirementBlob.CertFieldOp.MatchSuffix`  
`struct MatchSuffix`  
_private*; L1630-1634_
- L1632 _public field_ `public UInt32 MatchOp`
- L1633 _public field_ `public string CertificateName`

#### class `MachObjectHandling.RequirementBlob.CertGenericOp`  
`class CertGenericOp : ExpressionOp`  
_private*; L1683-1724_
- inherits: `ExpressionOp`
- L1685 _public field_ `public int OIDIndex = 1`
- L1686 _private* field_ `byte[] OID = new byte[] { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x63, 0x64, 0x06, 0x02, 0x01 }`
- L1691 _private* field_ `MatchSuffix MatchOp`
- L1693-1697 _public ctor_ `public CertGenericOp()`
- L1699-1709 _public method_ `public override void ReadData(ReadingContext SR)`
- L1711-1723 _public method_ `public override void WriteData(WritingContext SW)`

#### struct `MachObjectHandling.RequirementBlob.CertGenericOp.MatchSuffix`  
`struct MatchSuffix`  
_private*; L1687-1690_
- L1689 _public field_ `public UInt32 MatchOp`

#### class `MachObjectHandling.RequirementBlob.AnchorHashOp`  
`class AnchorHashOp : ExpressionOp`  
_private*; L1726-1755_
- inherits: `ExpressionOp`
- L1728 _private* field_ `byte[] Hash = new byte[] { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x63, 0x64, 0x06, 0x02, 0x01 }`
- L1729 _private* field_ `int CertificateIndex = -1`
- L1730-1733 _public ctor_ `public AnchorHashOp()`
- L1735-1743 _public method_ `public override void ReadData(ReadingContext SR)`
- L1745-1754 _public method_ `public override void WriteData(WritingContext SW)`

#### class `MachObjectHandling.CodeSigningTableBlob`  
`public class CodeSigningTableBlob : SuperBlob`  
_public; L1856-1868_
- inherits: `SuperBlob`
- L1858-1861 _public ctor_ `public CodeSigningTableBlob()`
- L1863-1867 _public method_ `public static CodeSigningTableBlob Create()`

#### class `MachObjectHandling.AbstractBlob`  
`public abstract class AbstractBlob`  
_public; L1870-1973_
- L1873 _public const_ `public const UInt32 CSSLOT_CODEDIRECTORY = 0`
- L1876 _public const_ `public const UInt32 CSMAGIC_REQUIREMENT = 0xFADE0C00`
- L1879 _public const_ `public const UInt32 CSMAGIC_REQUIREMENTS_TABLE = 0xFADE0C01`
- L1882 _public const_ `public const UInt32 CSMAGIC_CODEDIRECTORY = 0xFADE0C02`
- L1885 _public const_ `public const UInt32 CSMAGIC_EMBEDDED_SIGNATURE = 0xFADE0CC0`
- L1888 _public const_ `public const UInt32 CSMAGIC_ENTITLEMENTS = 0xFADE7171`
- L1891 _public const_ `public const UInt32 CSMAGIC_ENTITLEMENTS_DER = 0xFADE7172`
- L1894 _public const_ `public const UInt32 CSMAGIC_CODEDIR_SIGNATURE = 0xFADE0B01`
- L1897 _public field_ `public UInt32 MyMagic`
- L1899 _protected method_ `protected abstract void PackageData(WritingContext SW)`
- L1900 _protected method_ `protected abstract void UnpackageData(ReadingContext SR, UInt32 Length)`
- L1902-1946 _public method_ `public static AbstractBlob CreateFromStream(ReadingContext SR)`
- L1948-1955 _public method_ `public void Write(WritingContext SW)`
- L1961-1972 _public method_ `public byte[] GetBlobBytes()` — Always uses big endian!!! Converts a blob back into an array of bytes (does not work if there are any file-absolute offsets, as it serializes starting at 0 of a fake stream)

#### class `MachObjectHandling.OpaqueBlob`  
`public class OpaqueBlob : AbstractBlob`  
_public; L1978-1996_
- inherits: `AbstractBlob`
- L1980 _protected field_ `protected byte[] MyData`
- L1982-1985 _protected method_ `protected override void UnpackageData(ReadingContext SR, UInt32 Length)`
- L1987-1990 _protected method_ `protected override void PackageData(WritingContext SW)`
- L1992-1995 _public method_ `public override string ToString()`

#### class `MachObjectHandling.SuperBlob`  
`public abstract class SuperBlob : AbstractBlob`  
_public; L1998-2040_
- inherits: `AbstractBlob`
- L2000 _protected field_ `protected BlobTable Table = new BlobTable()`
- L2002-2012 _public method_ `public AbstractBlob GetBlobByMagic(UInt32 Magic)`
- L2014-2024 _public method_ `public AbstractBlob GetBlobByKey(UInt32 Key)`
- L2026-2029 _protected method_ `protected override void UnpackageData(ReadingContext SR, uint Length)`
- L2031-2034 _protected method_ `protected override void PackageData(WritingContext SW)`
- L2036-2039 _public method_ `public void Add(UInt32 Key, AbstractBlob Value)`

#### class `MachObjectHandling.BlobTable`  
`public class BlobTable`  
_public; L2057-2145_
- desc: References: http://www.opensource.apple.com/source/libsecurity_utilities/libsecurity_utilities-36984/lib/blob.h http://www.opensource.apple.com/source/libsecurity_utilities/libsecurity_utilities-38535/lib/superblob.h http://www.opensource.apple.com/source/libsecurity_codesigning/libsecurity_codesigning-36885/lib/cscdefs.h BlobTable: U32 SlotCount SerializedSlot Slots[Count] SerializedSlot KeyType Type U32 Offset (relative to start of BlobTable)
- L2059 _public field_ `public List<KeyValuePair<UInt32, AbstractBlob>> Slots = ...`
- L2059 _public field_ `public List<KeyValuePair< Slots = new List<KeyValuePair<UInt32, AbstractBlob>>()`
- L2061-2072 _public method_ `public AbstractBlob GetByKey(UInt32 Key)`
- L2077-2084 _private* method_ `AbstractBlob ReadBlob(ReadingContext SR, long Offset)` — Reads in a data blob, preserving the stream read pointer (Offset is relative to the start of the underlying stream)
- L2086-2124 _public method_ `public void Write(WritingContext SW)`
- L2126-2144 _public method_ `public void Read(ReadingContext SR)`

#### class `MachObjectHandling.CodeDirectorySignatureBlob`  
`public class CodeDirectorySignatureBlob : OpaqueBlob`  
_public; L2148-2226_
- inherits: `OpaqueBlob`
- L2150-2153 _public ctor_ `public CodeDirectorySignatureBlob()`
- L2155-2158 _public method_ `public static CodeDirectorySignatureBlob Create()`
- L2160-2193 _public method_ `public void DebugCMSData(byte[] Data, string Prefix)`
- L2198-2219 _public method_ `public void SignCodeDirectory(X509Certificate2 SigningCert, DateTime SigningTime, CodeDirectoryBlob CodeDirectory)` — Populates this CMS blob with the data from signing a code directory
- L2221-2225 _public method_ `public override string ToString()`

#### class `MachObjectHandling.CodeDirectoryBlob`  
`public class CodeDirectoryBlob : AbstractBlob`  
_public; L2228-2512_
- inherits: `AbstractBlob`
- L2230 _public const_ `public const UInt32 cVersion2 = 0x20200`
- L2231 _public const_ `public const UInt32 cVersion3 = 0x20400`
- L2233 _public field_ `public UInt32 Version`
- L2234 _private* field_ `UInt32 Flags`
- L2237 _private* field_ `byte[] Hashes`
- L2240 _private* field_ `string Identifier`
- L2242 _private* field_ `UInt32 SpecialSlotCount`
- L2243 _private* field_ `UInt32 CodeSlotCount`
- L2244 _private* field_ `UInt32 MainImageSignatureLimit`
- L2245 _private* field_ `byte BytesPerHash`
- L2246 _private* field_ `byte HashType`
- L2247 _private* field_ `byte Spare1`
- L2248 _private* field_ `byte LogPageSize`
- L2249 _private* field_ `UInt32 Spare2`
- L2250 _private* field_ `UInt32 ScatterCount`
- L2252 _private* field_ `string Team`
- L2254 _private* field_ `UInt32 Spare3`
- L2255 _private* field_ `UInt64 CodeLimit64`
- L2257 _private* field_ `UInt64 ExecSegBase`
- L2258 _private* field_ `UInt64 ExecSegLimit`
- L2259 _private* field_ `UInt64 ExecSegFlags`
- L2262 _public const_ `public const int cdInfoSlot = 1`
- L2265 _public const_ `public const int cdRequirementsSlot = 2`
- L2268 _public const_ `public const int cdResourceDirSlot = 3`
- L2271 _public const_ `public const int cdApplicationSlot = 4`
- L2274 _public const_ `public const int cdEntitlementSlot = 5`
- L2277 _public const_ `public const int cdUnknown6Slot = 6`
- L2280 _public const_ `public const int cdDerEntitlementSlot = 7`
- L2283 _public const_ `public const int cdSlotMax = cdDerEntitlementSlot`
- L2288 _protected field_ `protected SHA256CryptoServiceProvider HashProvider2 = new SHA256CryptoServiceProvider()` — Hash provider (SHA1)
- L2290-2347 _protected method_ `protected override void UnpackageData(ReadingContext SR, UInt32 Length)`
- L2349-2352 _private* method_ `void PrintHash(string Prefix, int SlotIndex)`
- L2354-2398 _protected method_ `protected override void PackageData(WritingContext SW)`
- L2400-2403 _public ctor_ `public CodeDirectoryBlob()`
- L2408-2411 _public property_ `public int PageSize { get; }` — The page size in bytes
- L2416-2423 _public method_ `public void GenerateSpecialSlotHash(int SpecialSlotIndex, byte[] SourceData)` — Generates a hash for one of the special slots and copies it into the hash array
- L2430-2436 _public method_ `public void GenerateSpecialSlotHash(int SpecialSlotIndex)` — Generates an empty hash (all zeros) for a special slot that isn't used (only cdApplicationSlot gets this treatment)
- L2442 _public const_ `public const UInt64 ExecSegFlagsMainBinary = 17` — Exec segment flags for the main executable of a bundle (CS_EXECSEG_MAIN_BINARY | CS_EXECSEG_ALLOW_UNSIGNED). Libraries loaded by that executable (the binaries of embedded frameworks) use no flags at all.
- L2444-2450 _public method_ `public static CodeDirectoryBlob Create(string ApplicationID, string TeamID, int SignedFileLength, UInt64 InExecSegBase, UInt64 InExecSegLimit, UInt64 InExecSegFlags = ExecSegFlagsMainBinary)`
- L2452-2484 _public method_ `public void Allocate(string ApplicationID, string TeamID, int SignedFileLength, UInt64 InExecSegBase, UInt64 InExecSegLimit, UInt64 InExecSegFlags = ExecSegFlagsMainBinary)`
- L2489-2499 _public method_ `public void ComputeImageHashes(byte[] SignedFileData)` — Calculates the hashes for every 4 KB of the main executable
- L2501-2511 _public method_ `public override string ToString()`

#### class `MachObjectHandling.MachLoadCommandCodeSignature`  
`class MachLoadCommandCodeSignature : MachLoadCommandLinkEditBlob`  
_internal*; L2517-2574_
- inherits: `MachLoadCommandLinkEditBlob`
- desc: Payload for LC_CODE_SIGNATURE
- L2519 _public field_ `public CodeSigningTableBlob Payload`
- L2521-2524 _public method_ `public override string ToString()`
- L2526-2546 _protected method_ `protected override void UnpackageData(ReadingContext SR, int CommandSize)`
- L2552-2573 _public method_ `public void PatchPositionAndSize(WritingContext SW, UInt32 NewOffset, UInt32 NewLength)` — Patches the the blob length and offset of the code signing blob in an existing file

#### class `MachObjectHandling.FatBinaryArch`  
`public class FatBinaryArch`  
_public; L2580-2587_
- L2582 _public field_ `public UInt32 CpuType`
- L2583 _public field_ `public UInt32 CpuSubType`
- L2584 _public field_ `public UInt32 Offset`
- L2585 _public field_ `public UInt32 Size`
- L2586 _public field_ `public UInt32 Align`

#### class `MachObjectHandling.FatBinaryFile`  
`public class FatBinaryFile`  
_public; L2589-2792_
- L2592 _public const_ `public const UInt32 CPU_TYPE_ARM64 = 0x0100000C`
- L2594 _public field_ `public UInt32 Magic`
- L2595 _public field_ `public UInt32 NumArchs`
- L2598 _public field_ `public bool bIsFatBinary`
- L2600 _public field_ `public List<FatBinaryArch> Archs`
- L2602 _public field_ `public List<MachObjectFile> MachObjectFiles = new List<MachObjectFile>()`
- L2605 _public const_ `public const UInt32 FAT_MAGIC = 0xCAFEBABE`
- L2606 _public const_ `public const UInt32 FAT_CIGAM = 0xBEBAFECA`
- L2608-2653 _protected method_ `protected void Read(ReadingContext SR)`
- L2655-2700 _protected method_ `protected void Write(WritingContext Context)`
- L2702-2766 _public method_ `public void WriteHeader(ref byte[] OutputData, uint Offset)`
- L2768-2774 _public method_ `public void LoadFromFile(string Filename)`
- L2776-2783 _public method_ `public void LoadFromBytes(byte[] Data)`
- L2785-2791 _public method_ `public void WriteToFile(string Filename)`

### `Source/Programs/IOS/iPhonePackager/MobileProvisionUtilities.cs` (iPhonePackager)


#### class `iPhonePackager.MobileProvision`  
`public class MobileProvision`  
_public; L21-575_
- desc: Represents the salient parts of a mobile provision, wrt. using it for code signing
- L23 _public field_ `public object Tag`
- L25 _public field_ `public string ApplicationIdentifierPrefix = null`
- L26 _public field_ `public string ApplicationIdentifier = null`
- L27 _public field_ `public List<X509Certificate2> DeveloperCertificates = new List<X509Certificate2>()`
- L28 _public field_ `public List<string> ProvisionedDeviceIDs`
- L29 _public field_ `public string ProvisionName`
- L30 _public field_ `public bool bDebug`
- L31 _public field_ `public Utilities.PListHelper Data`
- L32 _public field_ `public DateTime CreationDate`
- L33 _public field_ `public DateTime ExpirationDate`
- L34 _public field_ `public string FileName`
- L35 _public field_ `public string UUID`
- L36 _public field_ `public string Platform`
- L38-103 _public method_ `public static void CacheMobileProvisions()`
- L105-119 _public method_ `public static void CleanMobileProvisions()`
- L122-320 _public method_ `public static string FindCompatibleProvision(string CFBundleIdentifier, out bool bNameMatch, bool bCheckCert = true, bool bCheckIdentifier = true, bool bCheckDistro = true)`
- L326-466 _public method_ `public string GetEntitlementsString(string CFBundleIdentifier, out string TeamIdentifier)` — Extracts the dict values for the Entitlements key and creates a new full .plist file from them (with outer plist and dict keys as well as doctype, etc...)
- L471-556 _public ctor_ `public MobileProvision(string EmbeddedPListText)` — Constructs a MobileProvision from an xml blob extracted from the real ASN.1 file
- L561-574 _public method_ `public bool ContainsUDID(string UDID)` — Does this provision contain the specified UDID?

#### class `iPhonePackager.MobileProvisionParser`  
`public class MobileProvisionParser`  
_public; L581-674_
- desc: This class understands how to get the embedded plist in a .mobileprovision file. It doesn't understand the full format and is not capable of writing a new one out or anything similar.
- L583-608 _private method_ `private static int StrStrByteArray(byte[] Haystack, int Offset, string Needle)`
- L610-640 _public method_ `public static MobileProvision ParseFile(byte[] RawData)`
- L642-650 _public method_ `public static MobileProvision ParseFile(Stream InputStream)`
- L653-661 _public method_ `public static MobileProvision ParseFile(string Filename)`
- L666-673 _public method_ `public static MobileProvision ParseIPA(string Filename)` — Opens embedded.mobileprovision from within an IPA

### `Source/Programs/IOS/iPhonePackager/PasswordDialog.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.PasswordDialog`  
`partial class PasswordDialog`  
_internal*; L3-90_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-83 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L87 _private field_ `private System.Windows.Forms.MaskedTextBox PasswordEntryBox`
- L88 _private field_ `private System.Windows.Forms.Label PasswordEntryPrompt`
- L89 _private field_ `private System.Windows.Forms.Button OKButton`

### `Source/Programs/IOS/iPhonePackager/PasswordDialog.cs` (iPhonePackager)


#### class `iPhonePackager.PasswordDialog`  
`public partial class PasswordDialog : Form`  
_public; L14-38_
- inherits: `Form`
- L16 _private* field_ `string PasswordResult = null`
- L18-21 _public ctor_ `public PasswordDialog()`
- L23-30 _public method_ `public static bool RequestPassword(out string Password)`
- L32-37 _private method_ `private void OKButton_Click(object sender, EventArgs e)`

### `Source/Programs/IOS/iPhonePackager/Properties/AssemblyInfo.cs` (iPhonePackager)
_(no declarations)_


### `Source/Programs/IOS/iPhonePackager/Properties/Resources.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.Properties.Resources`  
`internal class Resources`  
_internal; L19-70_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [System.Diagnostics.DebuggerNonUserCodeAttribute()] [System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L21 _private field_ `private static System.Resources.ResourceManager resourceMan`
- L23 _private field_ `private static System.Globalization.CultureInfo resourceCulture`
- L26-27 _internal ctor_ `internal Resources()` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L30-38 _internal property_ `internal static System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]`
- L41-48 _internal property_ `internal static System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]`
- L50-55 _internal property_ `internal static System.Drawing.Bitmap GreyCheck { get; }`
- L57-62 _internal property_ `internal static System.Drawing.Bitmap GreenCheck { get; }`
- L64-69 _internal property_ `internal static System.Drawing.Bitmap YellowCheck { get; }`

### `Source/Programs/IOS/iPhonePackager/RPCCommandHelper.cs` (iPhonePackager)


#### class `DotNETUtilities.RPCCommandHelper`  
`public class RPCCommandHelper`  
_public; L17-558_
- L20 _private* const_ `const int MaxChunkSize = 10 * 1024 * 1024`
- L27-48 _public method_ `public static bool PingRemoteHost(string RemoteHostNameOrAddressToPing)`
- L54-59 _public method_ `public static Socket ConnectToUnrealRemoteTool(string MachineName)`
- L61 _private* const_ `const Int64 TypeString = 0`
- L62 _private* const_ `const Int64 TypeLong = 1`
- L63 _private* const_ `const Int64 TypeBlob = 2`
- L65 _private field_ `private static UTF8Encoding Encoder = new UTF8Encoding()`
- L67 _private field_ `private static byte[] TypeStringBytes = BitConverter.GetBytes(TypeString)`
- L68 _private field_ `private static byte[] TypeLongBytes = BitConverter.GetBytes(TypeLong)`
- L69 _private field_ `private static byte[] TypeBlobBytes = BitConverter.GetBytes(TypeBlob)`
- L71-79 _private method_ `private static void SendString(MemoryStream Stream, string Value)`
- L81-86 _private method_ `private static void SendLong(MemoryStream Stream, Int64 Value)`
- L88-94 _private method_ `private static void SendBlob(MemoryStream Stream, byte[] Value)`
- L96-135 _private method_ `private static object ReadObject(byte[] MessageBuffer, ref Int64 Offset)`
- L137-241 _private method_ `private static Hashtable SendMessageWithReply(Socket Socket, Hashtable Message)`
- L242-249 _public method_ `public static void DummyFileCommand(Socket Socket)`
- L251-259 _public method_ `public static void MakeDirectory(Socket Socket, string DirName)`
- L261-271 _public method_ `public static int GetCommandSlots(Socket Socket)`
- L273-281 _public method_ `public static void RemoveDirectory(Socket Socket, string DirName)`
- L283-355 _public method_ `public static void RPCBatchUpload(Socket Socket, string[] CopyCommands)`
- L360-384 _public method_ `public static Int64[] RPCBatchFileInfo(Socket Socket, string FileList)`
- L386-428 _public method_ `public static Hashtable RPCUpload(Socket Socket, string SourceFilename, string DestFilename)`
- L430-467 _public method_ `public static Hashtable RPCDownload(Socket Socket, string SourceFilename, string DestFilename)`
- L469-482 _public method_ `public static DateTime FromRemoteTime(Int64 RemoteTime)`
- L484-500 _public method_ `public static Int64 ToRemoteTime(DateTime LocalTime)`
- L502-516 _public method_ `public static bool GetFileInfo(Socket Socket, string Filename, DateTime ClientNow, out DateTime ModificationTime, out long Length)`
- L518-532 _public method_ `public static Hashtable RPCCommand(Socket Socket, string WorkingDirectory, string CommandName, string CommandArgs, string RemoteOutputPath)`
- L535-556 _public method_ `public static void RPCSoakTest(Socket Socket)`

### `Source/Programs/IOS/iPhonePackager/SSHCommandHelper.cs` (iPhonePackager)


#### class `iPhonePackager.SSHCommandHelper`  
`public partial class SSHCommandHelper`  
_public; L14-384_
- L16 _private field_ `private static string SSHExePath = ""`
- L17 _private field_ `private static string SSHAuthentication = ""`
- L18 _private field_ `private static string SSHUser = ""`
- L19 _private field_ `private static string RSyncExePath = ""`
- L24-105 _public method_ `public static bool ParseSSHProperties(string[] Arguments)`
- L107-138 _private method_ `private static bool ValidateSetup()`
- L142 _private field_ `private static Dictionary<Object, StringBuilder> SSHOutputMap = ...`
- L142 _private field_ `private static Dictionary< SSHOutputMap = new Dictionary<object, StringBuilder>()`
- L143 _public field_ `public static Hashtable SSHReturn = new Hashtable()`
- L147-196 _public method_ `static public bool Command(string RemoteMac, string Command, string WorkingFolder)`
- L201-240 _public method_ `public static void BatchUpload(string RemoteMac, string[] CopyCommands)`
- L245-294 _public method_ `static public Hashtable UploadFile(string RemoteMac, string LocalPath, string RemotePath)`
- L300-349 _public method_ `static public Hashtable DownloadFile(string RemoteMac, string RemotePath, string LocalPath)`
- L352-358 _public method_ `static public void OutputReceivedForRsync(Object Sender, DataReceivedEventArgs Line)`
- L361-373 _public method_ `static public void OutputReceivedForSSH(Object Sender, DataReceivedEventArgs Line)`
- L376-383 _private method_ `private static string ConvertPathToCygwin(string InPath)`

### `Source/Programs/IOS/iPhonePackager/SlowProgressDialog.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.SlowProgressDialog`  
`partial class SlowProgressDialog`  
_internal*; L3-85_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-78 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L82 _private field_ `private System.ComponentModel.BackgroundWorker SlowWork`
- L83 _private field_ `private System.Windows.Forms.ProgressBar ProgressIndicator`
- L84 _private field_ `private System.Windows.Forms.Label StatusLabel`

### `Source/Programs/IOS/iPhonePackager/SlowProgressDialog.cs` (iPhonePackager)


#### class `iPhonePackager.SlowProgressDialog`  
`public partial class SlowProgressDialog : Form`  
_public; L13-62_
- inherits: `Form`
- L15-18 _public ctor_ `public SlowProgressDialog()`
- L20 _public delegate_ `public delegate void WorkToDoSignature(BackgroundWorker BGWorker)`
- L21 _public field_ `public WorkToDoSignature OnBeginBackgroundWork = null`
- L23-28 _private method_ `private void SlowWork_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)`
- L30-43 _private method_ `private void SlowWork_DoWork(object sender, DoWorkEventArgs e)`
- L45-49 _private method_ `private void SlowWork_ProgressChanged(object sender, ProgressChangedEventArgs e)`
- L51-61 _private method_ `private void SlowProgressDialog_Shown(object sender, EventArgs e)`

### `Source/Programs/IOS/iPhonePackager/ToolsHub.Designer.cs` (iPhonePackager)


#### class `iPhonePackager.ToolsHub`  
`partial class ToolsHub`  
_internal*; L3-537_
- L8 _private field_ `private System.ComponentModel.IContainer components = null` — Required designer variable.
- L14-21 _protected method_ `protected override void Dispose(bool disposing)` — Clean up any resources being used.
- L29-499 _private method_ `private void InitializeComponent()` — Required method for Designer support - do not modify the contents of this method with the code editor.
- L503 _private field_ `private System.Windows.Forms.Button ReadyToPackageButton`
- L504 _private field_ `private System.Windows.Forms.Button CancelThisFormButton`
- L505 _private field_ `private System.Windows.Forms.TabControl tabControl1`
- L506 _private field_ `private System.Windows.Forms.TabPage tabPage1`
- L507 _private field_ `private System.Windows.Forms.Button CreateCSRButton`
- L508 _private field_ `private System.Windows.Forms.TabPage tabPage2`
- L509 _private field_ `private System.Windows.Forms.PictureBox CertificatePresentCheck`
- L510 _private field_ `private System.Windows.Forms.PictureBox MobileProvisionCheck`
- L511 _private field_ `private System.Windows.Forms.Button ImportMobileProvisionButton`
- L512 _private field_ `private System.Windows.Forms.Button ImportCertificateButton`
- L513 _private field_ `private System.Windows.Forms.Label label11`
- L514 _private field_ `private System.Windows.Forms.Label label12`
- L515 _private field_ `private System.Windows.Forms.Label label8`
- L516 _private field_ `private System.Windows.Forms.Label label9`
- L517 _private field_ `private System.Windows.Forms.PictureBox CertificatePresentCheck2`
- L518 _private field_ `private System.Windows.Forms.PictureBox MobileProvisionCheck2`
- L519 _private field_ `private System.Windows.Forms.Button ImportProvisionButton2`
- L520 _private field_ `private System.Windows.Forms.Button ImportCertificateButton2`
- L521 _private field_ `private System.Windows.Forms.TabPage tabPage3`
- L522 _private field_ `private System.Windows.Forms.Label label2`
- L523 _private field_ `private System.Windows.Forms.Label label13`
- L524 _private field_ `private System.Windows.Forms.Label label3`
- L525 _private field_ `private System.Windows.Forms.Label label10`
- L526 _private field_ `private System.Windows.Forms.Label label5`
- L527 _private field_ `private System.Windows.Forms.Label label6`
- L528 _private field_ `private System.Windows.Forms.Label label14`
- L529 _private field_ `private System.Windows.Forms.Button InstallIPAButton`
- L530 _private field_ `private System.Windows.Forms.Label label20`
- L531 _private field_ `private System.Windows.Forms.Label label21`
- L532 _private field_ `private System.Windows.Forms.GroupBox groupBox1`
- L533 _private field_ `private System.Windows.Forms.Label label19`
- L534 _private field_ `private System.Windows.Forms.Label label17`
- L535 _private field_ `private System.Windows.Forms.Button OtherDeployToolsButton`
- L536 _private field_ `private System.Windows.Forms.Button ResignIPAButton`

### `Source/Programs/IOS/iPhonePackager/ToolsHub.cs` (iPhonePackager)


#### class `iPhonePackager.ToolsHub`  
`public partial class ToolsHub : Form`  
_public; L20-438_
- inherits: `Form`
- L26 _private* method_ `static int MessageBox(IntPtr hWnd, String Text, String Caption, uint type)`
- L29 _public method_ `public static extern int MessageBox(IntPtr hWnd, String Text, String Caption, uint type)` — attrs: `[DllImport("user32.dll")]`
- L31 _protected field_ `protected Dictionary<int, Bitmap> CheckStateImages = ...`
- L31 _protected field_ `protected Dictionary< CheckStateImages = new Dictionary<int, Bitmap>()`
- L33 _public field_ `public static string IpaFilter = "iOS packaged applications (*.ipa)|*.ipa|All Files (*.*)|*.*"`
- L34 _public field_ `public static string CertificateRequestFilter = "Certificate Request (*.csr)|*.csr|All Files (*.*)|*.*"`
- L35 _public field_ `public static string MobileProvisionFilter = "Mobile provision files (*.mobileprovision)|*.mobileprovision|All files (*.*)|*.*"`
- L36 _public field_ `public static string CertificatesFilter = "Code signing certificates (*.cer;*.p12)|*.cer;*.p12|All files (*.*)|*.*"`
- L37 _public field_ `public static string KeysFilter = "Keys (*.key;*.p12)|*.key;*.p12|All files (*.*)|*.*"`
- L38 _public field_ `public static string JustXmlKeysFilter = "XML Public/Private Key Pair (*.key)|*.key|All Files (*.*)|*.*"`
- L39 _public field_ `public static string PListFilter = "Property Lists (*.plist)|*.plist|All Files (*.*)|*.*"`
- L40 _public field_ `public static string JustP12Certificates = "Code signing certificates (*.p12)|*.p12|All files (*.*)|*.*"`
- L44 _public field_ `public static string ChoosingFilesToInstallDirectory = null`
- L45 _public field_ `public static string ChoosingIpaDirectory = null`
- L57-89 _public method_ `public static bool ShowOpenFileDialog(string Filter, string Title, string DefaultExtension, string StartingFilename, ref string SavedDirectory, out string OutFilename)` — Shows a file dialog, preserving the current working directory of the application
- L92-101 _public ctor_ `public ToolsHub()`
- L103-108 _public method_ `public static ToolsHub CreateShowingTools()`
- L110-121 _private method_ `private void ToolsHub_Shown(object sender, EventArgs e)`
- L123-150 _private* method_ `void UpdateStatus()`
- L152-156 _private method_ `private void CreateCSRButton_Click(object sender, EventArgs e)`
- L159-167 _public method_ `public static void ShowError(string Message)`
- L169-172 _public method_ `public static bool IsProfileForDistribution(MobileProvision Provision)`
- L174-227 _public method_ `public static void TryInstallingMobileProvision(string ProvisionFilename, bool ShowPrompt = true)`
- L230-234 _private method_ `private void ImportMobileProvisionButton_Click(object sender, EventArgs e)`
- L237 _private field_ `static private string CertToolData = ""`
- L238-244 _public method_ `static public void OutputReceivedCertToolProcessCall(Object Sender, DataReceivedEventArgs Line)`
- L246-344 _public method_ `public static void TryInstallingCertificate_PromptForKey(string CertificateFilename, bool ShowPrompt = true)`
- L347-351 _private method_ `private void ImportCertificateButton_Click(object sender, EventArgs e)`
- L353-358 _private method_ `private void EditPlistButton_Click(object sender, EventArgs e)`
- L360-364 _private method_ `private void CancelThisFormButton_Click(object sender, EventArgs e)`
- L366-370 _private method_ `private void ReadyToPackageButton_Click(object sender, EventArgs e)`
- L372-383 _private method_ `private void InstallIPAButton_Click(object sender, EventArgs e)`
- L385-390 _private method_ `private void ResignIPAButton_Click(object sender, EventArgs e)`
- L392-397 _private method_ `private void ProvisionCertToolsButton_Click(object sender, EventArgs e)`
- L399-404 _private method_ `private void OtherDeployToolsButton_Click(object sender, EventArgs e)`
- L406-411 _private* method_ `void OpenHelpWebsite()`
- L413-416 _private method_ `private void ToolsHub_HelpButtonClicked(object sender, CancelEventArgs e)`
- L418-424 _private method_ `private void ToolsHub_KeyUp(object sender, KeyEventArgs e)`
- L426-431 _private method_ `private void HyperlinkClicked(object sender, LinkLabelLinkClickedEventArgs e)`
- L433-436 _private method_ `private void InstallIPA_Click(object sender, EventArgs e)`

### `Source/Programs/IOS/iPhonePackager/Utilities.cs` (iPhonePackager)


#### class `iPhonePackager.Utilities`  
`public class Utilities`  
_public; L27-649_
- L32-43 _public method_ `public static string ReadFixedASCII(BinaryReader SR, int Length)` — Reads a string from a fixed-length ASCII array
- L48-64 _public method_ `public static void WriteFixedASCII(BinaryWriter SW, string WriteOut, int Length)` — Writes a string as a fixed-length ASCII array
- L66-83 _public method_ `public static byte[] CreateASCIIZ(string WriteOut)`
- L85-92 _public method_ `public static void VerifyStreamPosition(BinaryWriter SW, long StartingStreamPosition, long JustWroteCount)`
- L101-110 _public method_ `public static bool GetEnvironmentVariable(string VarName, bool bDefault)`
- L119-127 _public method_ `public static string GetStringEnvironmentVariable(string VarName, string Default)`
- L136-144 _public method_ `public static double GetEnvironmentVariable(string VarName, double Default)`
- L153-161 _public method_ `public static string GetEnvironmentVariable(string VarName, string Default)`
- L166-179 _public method_ `public static int RunExecutableAndWait(string ExeName, string ArgumentList, out string StdOutResults)` — Runs an executable with the specified argument list and waits for it to terminate, capturing the standard output and return code
- L576-600 _public method_ `static public string GetStringFromPList(string KeyName)`
- L602-625 _public method_ `static public string GetPrecompileSourcePListFilename()`
- L630-648 _public method_ `static public bool GetSourcePList(out string PListSource)`

#### class `iPhonePackager.Utilities.PListHelper`  
`public class PListHelper`  
_public; L181-574_
- L183 _public field_ `public XmlDocument Doc`
- L185 _private* field_ `bool bReadOnly = false`
- L187-190 _public method_ `public void SetReadOnly(bool bNowReadOnly)`
- L192-197 _public ctor_ `public PListHelper(string Source)`
- L199-203 _public method_ `public static PListHelper CreateFromFile(string Filename)`
- L205-208 _public method_ `public void SaveToFile(string Filename)`
- L210-223 _public ctor_ `public PListHelper()`
- L225-298 _public method_ `public XmlElement ConvertValueToPListFormat(object Value)`
- L300-312 _public method_ `public void AddKeyValuePair(XmlNode DictRoot, string KeyName, object Value)`
- L314-319 _public method_ `public void AddKeyValuePair(string KeyName, object Value)`
- L324-337 _public method_ `public static PListHelper CloneDictionaryRootedAt(XmlNode Root)` — Clones a dictionary from an existing .plist into a new one. Root should point to the dict key in the source plist.
- L339-352 _public method_ `public bool GetString(string Key, out string Value)`
- L354-367 _public method_ `public bool GetDate(string Key, out string Value)`
- L369-380 _public method_ `public bool GetBool(string Key)`
- L382 _public delegate_ `public delegate void ProcessOneNodeEvent(XmlNode ValueNode)`
- L384-393 _public method_ `public void ProcessValueForKey(string Key, string ExpectedValueType, ProcessOneNodeEvent ValueHandler)`
- L399-435 _public method_ `public void MergePlistIn(string DominantPlist, HashSet<string> WeakKeysToKeep=null)` — Merge two plists together. Whenever both have the same key, the value in the dominant source list wins. This is special purpose code, and only handles things inside of the tag
- L442-460 _public method_ `public List<string> GetArray(string Key, string EntryType)` — Returns each of the entries in the value tag of type array for a given key If the key is missing, an empty array is returned. Only entries of a given type within the array are returned.
- L465-471 _public method_ `public bool HasKey(string KeyName)` — Returns true if the key exists (and has a value) and false otherwise
- L473-497 _public method_ `public void RemoveKeyValue(string KeyName)`
- L499-536 _public method_ `public void SetValueForKey(string KeyName, object Value)`
- L538-541 _public method_ `public void SetString(string Key, string Value)`
- L543-573 _public method_ `public string SaveToString()`

#### class `iPhonePackager.VersionUtilities`  
`class VersionUtilities`  
_internal*; L652-778_
- L654-657 _private* property_ `static string RunningVersionFilename { get; }`
- L663-672 _public method_ `public static string ReadRunningVersion()` — Reads the GameName.PackageVersionCounter from disk and bumps the minor version number in it
- L683-706 _public method_ `public static void PullApartVersion(string CFBundleVersion, out int VersionMajor, out int VersionMinor, out string TimeStamp)` — Pulls apart a version string of one of the two following formats: "7301.15 11-01 10:28" (Major.Minor Date Time) "7486.0" (Major.Minor)
- L708-711 _public method_ `public static string ConstructVersion(int MajorVersion, int MinorVersion)`
- L722-754 _public method_ `public static string CalculateUpdatedMinorVersionString(string CFBundleVersion)` — Parses the version string (expected to be of the form major.minor or major) Also parses the major.minor from the running version file and increments it's minor by 1. If the running version major matches and the running version minor is newer, then the bundle version is updated. In either case, the running version is set to the current bundle version number and written back out.
- L760-777 _public method_ `public static void UpdateMinorVersion(Utilities.PListHelper PList)` — Updates the minor version in the CFBundleVersion key of the specified PList if this is a new package. Also updates the key EpicAppVersion with the bundle version and the current date/time (no year)

#### class `iPhonePackager.CryptoAdapter`  
`class CryptoAdapter`  
_internal*; L780-989_
- L782-792 _public method_ `public static AsymmetricCipherKeyPair GenerateBouncyKeyPair()`
- L795-810 _public method_ `public static RSACryptoServiceProvider LoadKeyPairFromPKCS12Store(string Filename)`
- L812-826 _public method_ `public static Org.BouncyCastle.X509.X509Certificate LoadBouncyCertFromPKCS12Store(string Filename)`
- L828-862 _public method_ `public static RSACryptoServiceProvider LoadKeyPairFromDiskNET(string Filename)`
- L864-875 _public method_ `public static AsymmetricCipherKeyPair LoadKeyPairFromDiskBouncy(string Filename)`
- L877-880 _public method_ `public static AsymmetricCipherKeyPair ConvertNETKeyPairToBouncy(RSACryptoServiceProvider KeyPair)`
- L882-887 _public method_ `public static RSACryptoServiceProvider ConvertBouncyKeyPairToNET(AsymmetricCipherKeyPair KeyPair)`
- L889-899 _public method_ `public static RSACryptoServiceProvider ConvertBouncyKeyPairToNET(RsaPrivateCrtKeyParameters PrivateKeyInfo)`
- L901-920 _public method_ `public static string GetCommonNameFromCert(X509Certificate2 Cert)`
- L922-939 _public method_ `public static string GetFriendlyNameFromCert(X509Certificate2 Cert)`
- L944-988 _public method_ `public static X509Certificate2 CombineKeyAndCert(string CertificateFilename, string KeyFilename)` — Merges a certificate and private key into a single combined certificate

### `Source/Programs/IOS/iPhonePackager/iPhonePackager.cs` (iPhonePackager)


#### enum `iPhonePackager.ErrorCodes`  
`public enum ErrorCodes`  
_public; L25-81_
- L27 _public* enumerator_ `Error_UATNotFound = -1`
- L28 _public* enumerator_ `Error_Success = 0`
- L29 _public* enumerator_ `Error_Unknown = 1`
- L30 _public* enumerator_ `Error_Arguments = 2`
- L31 _public* enumerator_ `Error_UnknownCommand = 3`
- L32 _public* enumerator_ `Error_SDKNotFound = 10`
- L33 _public* enumerator_ `Error_ProvisionNotFound = 11`
- L34 _public* enumerator_ `Error_CertificateNotFound = 12`
- L35 _public* enumerator_ `Error_ProvisionAndCertificateNotFound = 13`
- L36 _public* enumerator_ `Error_InfoPListNotFound = 14`
- L37 _public* enumerator_ `Error_KeyNotFoundInPList = 15`
- L38 _public* enumerator_ `Error_ProvisionExpired = 16`
- L39 _public* enumerator_ `Error_CertificateExpired = 17`
- L40 _public* enumerator_ `Error_CertificateProvisionMismatch = 18`
- L41 _public* enumerator_ `Error_CodeUnsupported = 19`
- L42 _public* enumerator_ `Error_PluginsUnsupported = 20`
- L43 _public* enumerator_ `Error_UnknownCookFailure = 25`
- L44 _public* enumerator_ `Error_UnknownDeployFailure = 26`
- L45 _public* enumerator_ `Error_UnknownBuildFailure = 27`
- L46 _public* enumerator_ `Error_UnknownPackageFailure = 28`
- L47 _public* enumerator_ `Error_UnknownLaunchFailure = 29`
- L48 _public* enumerator_ `Error_StageMissingFile = 30`
- L49 _public* enumerator_ `Error_FailedToCreateIPA = 31`
- L50 _public* enumerator_ `Error_FailedToCodeSign = 32`
- L51 _public* enumerator_ `Error_DeviceBackupFailed = 33`
- L52 _public* enumerator_ `Error_AppUninstallFailed = 34`
- L53 _public* enumerator_ `Error_AppInstallFailed = 35`
- L54 _public* enumerator_ `Error_AppNotFound = 36`
- L55 _public* enumerator_ `Error_StubNotSignedCorrectly = 37`
- L56 _public* enumerator_ `Error_IPAMissingInfoPList = 38`
- L57 _public* enumerator_ `Error_DeleteFile = 39`
- L58 _public* enumerator_ `Error_DeleteDirectory = 40`
- L59 _public* enumerator_ `Error_CreateDirectory = 41`
- L60 _public* enumerator_ `Error_CopyFile = 42`
- L61 _public* enumerator_ `Error_OnlyOneObbFileSupported = 50`
- L62 _public* enumerator_ `Error_FailureGettingPackageInfo = 51`
- L63 _public* enumerator_ `Error_OnlyOneTargetConfigurationSupported = 52`
- L64 _public* enumerator_ `Error_ObbNotFound = 53`
- L65 _public* enumerator_ `Error_AndroidBuildToolsPathNotFound = 54`
- L66 _public* enumerator_ `Error_NoApkSuitableForArchitecture = 55`
- L67 _public* enumerator_ `Error_FilesInstallFailed = 56`
- L68 _public* enumerator_ `Error_RemoteCertificatesNotFound = 57`
- L69 _public* enumerator_ `Error_LauncherFailed = 100`
- L70 _public* enumerator_ `Error_UATLaunchFailure = 101`
- L71 _public* enumerator_ `Error_FailedToDeleteStagingDirectory = 102`
- L72 _public* enumerator_ `Error_MissingExecutable = 103`
- L73 _public* enumerator_ `Error_DeviceNotSetupForDevelopment = 150`
- L74 _public* enumerator_ `Error_DeviceOSNewerThanSDK = 151`
- L75 _public* enumerator_ `Error_TestFailure = 152`
- L76 _public* enumerator_ `Error_SymbolizedSONotFound = 153`
- L77 _public* enumerator_ `Error_LicenseNotAccepted = 154`
- L78 _public* enumerator_ `Error_AndroidOBBError = 155`
- L79 _public* enumerator_ `Error_SDKInstallFailed = 200`
- L80 _public* enumerator_ `Error_DeviceUpdateFailed = 201`

#### class `iPhonePackager.Program`  
`public partial class Program`  
_public; L83-1096_
- L85 _public field_ `static public int ReturnCode = 0`
- L86 _private* field_ `static string MainCommand = ""`
- L87 _private* field_ `static string MainRPCCommand = ""`
- L88 _public field_ `static public string GameName = ""`
- L89 _private field_ `static private string GamePath = ""`
- L90 _public field_ `static public string GameConfiguration = ""`
- L91 _public field_ `static public string Architecture = ""`
- L92 _public field_ `static public string SchemeName = ""`
- L93 _public field_ `static public string SchemeConfiguration = ""`
- L96 _public field_ `static public SlowProgressDialog ProgressDialog = null`
- L98 _public field_ `static public BackgroundWorker BGWorker = null`
- L99 _public field_ `static public int ProgressIndex = 0`
- L100 _public field_ `static public string AdditionalCommandline = ""`
- L101 _public field_ `static public bool IsClient = false`
- L103-110 _public method_ `static public void UpdateStatus(string Line)`
- L112-116 _public method_ `static public void Log(string Line)`
- L118-121 _public method_ `static public void Log(string Line, params object[] Args)`
- L123-130 _public method_ `static public void LogVerbose(string Line)`
- L132-135 _public method_ `static public void LogVerbose(string Line, params object[] Args)`
- L137-148 _public method_ `static public void Error(string Line, int Code = 1)`
- L150-153 _public method_ `static public void Error(string Line, params object[] Args)`
- L155-160 _public method_ `static public void Warning(string Line)`
- L162-165 _public method_ `static public void Warning(string Line, params object[] Args)`
- L167-548 _private method_ `static private bool ParseCommandLine(ref string[] Arguments)`
- L550-565 _private method_ `static private bool CheckArguments()`
- L567-636 _public method_ `static public void ExecuteCommand(string Command, string RPCCommand)`
- L641-709 _private* method_ `static Assembly CurrentDomain_AssemblyResolve(Object sender, ResolveEventArgs args)`
- L712 _private* delegate_ `delegate Form CreateFormDelegate()`
- L714 _private* field_ `static bool bVisualsStarted = false`
- L715-733 _private* method_ `static void StartVisuals()`
- L736 _private method_ `private static extern bool SetProcessDPIAware()` — attrs: `[System.Runtime.InteropServices.DllImport("user32.dll")]`
- L738-744 _private* method_ `static void RunInVisualMode(CreateFormDelegate Work)`
- L746-760 _private* method_ `static void ListDevices()`
- L762-790 _private* method_ `static string FindWindowsStoreITunesDLL()`
- L796-1095 _private* method_ `static int Main(string[] args)` — attrs: `[STAThread]`
