# Runtime / UELibrary

- module root: `Source/Runtime/UELibrary`
- headers: 2; symbols: 9
- symbol kinds: macro=4, prototype=5
- PrivateDependencyModuleNames: ApplicationCore, Launch
- PublicDependencyModuleNames: Core, Engine, InputCore

### `Source/Runtime/UELibrary/Private/UELibrary.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/UELibrary/Public/UELibraryAPI.h` (Public)


#### Free symbols / members of external scopes

- L16 _macro_ `#define UELIBRARYAPI __declspec(dllexport)`
- L18 _macro_ `#define UELIBRARYAPI __declspec(dllimport)`
- L37 _prototype_ `UELIBRARYAPI int UELibrary_InitA(HINSTANCE hInst, HWND hWnd, const char* CmdLine);` — Initializes UE as a library. @param  hInst    The instance of the outer application which wants to embed UE. @param  hWnd     The window of the outer application into which UE is to be embedded. @param  CmdLine  The command line to pass to UE - should contain a .uproject file and map to load at minimum. @return  Zero if creation was successful, non-zero if an error occurred. @note  UE can currently only be embedded in a single window. @note  There is an A and W overload for different character widths of the command line argument. Typical usage should be to use the UELibrary_Init function which maps to the appropriate overload for the outer application's Unicode setting.
- L38 _prototype_ `UELIBRARYAPI int UELibrary_InitW(HINSTANCE hInst, HWND hWnd, const wchar_t* CmdLine);`
- L41 _macro_ `#define UELibrary_Init UELibrary_InitW`
- L43 _macro_ `#define UELibrary_Init UELibrary_InitA`
- L52 _prototype_ `UELIBRARYAPI int UELibrary_Tick();` — Ticks the UE library.  This should be called frequently by the outer application. @return  Zero if ticking was successful, non-zero if an error occurred.
- L65 _prototype_ `UELIBRARYAPI LRESULT UELibrary_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);` — Passes windows messages from the outer application to the UE library. @param  hWnd     As per WndProc. @param  message  As per WndProc. @param  wParam   As per WndProc. @param  lParam   As per WndProc. @return  As per WndProc.
- L75 _prototype_ `UELIBRARYAPI int UELibrary_Shutdown();` — Shuts down the UE library. @return  Zero if shutdown was successful, non-zero if an error occurred. @note  UE cannot be started up again once shut down.
