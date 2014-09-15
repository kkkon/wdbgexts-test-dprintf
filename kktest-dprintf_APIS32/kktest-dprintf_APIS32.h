
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <WDBGEXTS.H>



#define WORKAROUND__DPRINTF_LY

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(WORKAROUND__DPRINTF_LY)
void initDebugEngine(void);
void execute_dprintf_sourceline( const ULONG address );
#endif // defined(WORKAROUND__DPRINTF_LY)

#if defined(__cplusplus)
} // extern "C" {
#endif

