
#include "kktest-dprintf_APIS64.h"

EXT_API_VERSION		ApiVersion = {
	1
	, 0
	, EXT_API_VERSION_NUMBER64
	, 0
};

WINDBG_EXTENSION_APIS	ExtensionApis;
ULONG	SavedMajorVersion;
ULONG	SavedMinorVersion;

__declspec(dllexport)
VOID
WinDbgExtensionDllInit(
	IN PWINDBG_EXTENSION_APIS lpExtensionApis
	, IN USHORT MajorVersion
	, IN USHORT MinorVersion
)
{
	ExtensionApis = *lpExtensionApis;

	SavedMajorVersion = MajorVersion;
	SavedMinorVersion = MinorVersion;

	return;
}

__declspec(dllexport)
LPEXT_API_VERSION
ExtensionApiVersion(
	VOID
)
{
	return &ApiVersion;
}

__declspec(dllexport)
VOID
CheckVersion(
	VOID
)
{
	return;
}



__declspec(dllexport)
DECLARE_API ( kktest )
{
	EXTSTACKTRACE64	stackFrames[32];
	const ULONG count = StackTrace( 0, 0, 0, stackFrames, sizeof(stackFrames)/sizeof(stackFrames[0]) );

	{
		size_t index = 0;
		for ( index = 0; index < count; ++index )
		{
			dprintf( "	%ly\n", stackFrames[index].ProgramCounter );
		}
	}

	return;
}







