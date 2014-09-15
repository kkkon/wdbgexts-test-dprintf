/*
 * The MIT License
 *
 * Copyright 2014 Kiyofumi Kondoh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "kktest-dprintf_APIS32.h"

#if defined(WORKAROUND__DPRINTF_LY)
#include <DbgEng.h>
#pragma comment(lib,"dbgeng.lib")

IDebugClient*	gDebugClient = NULL;
IDebugControl*	gDebugControl = NULL;

void initDebugEngine(void)
{
	if ( NULL != gDebugControl )
	{
		gDebugControl->Release();
		gDebugControl = NULL;
	}
	if ( NULL != gDebugClient )
	{
		gDebugClient->Release();
		gDebugClient = NULL;
	}

	{
		HRESULT hResult = S_FALSE;
		hResult = DebugCreate( __uuidof(IDebugClient), (PVOID *)&gDebugClient );
		if ( FAILED(hResult) )
		{
			dprintf( "get IDebugClient fail\n" );
			return;
		}

		if ( NULL != gDebugClient )
		{
			hResult = gDebugClient->QueryInterface( __uuidof(IDebugControl), (PVOID *)&gDebugControl );
			if ( FAILED(hResult) )
			{
				dprintf( "get IDebugControl fail\n" );
			}
		}
	}
}

void execute_dprintf_sourceline( const ULONG address )
{
	if ( NULL != gDebugControl )
	{
		char	buff[128];
		::wsprintfA( buff, ".printf \"\t%%ly\", 0x%p", address );
		//dprintf( "%s", buff );
		HRESULT hResult = gDebugControl->Execute( DEBUG_OUTCTL_ALL_OTHER_CLIENTS, buff, DEBUG_EXECUTE_NOT_LOGGED );
		if ( FAILED(hResult) )
		{
			dprintf( "execute command failed '%s'\n", buff );
		}
		else
		{
			dprintf( "\n" );
		}
	}
}

#endif // defined(WORKAROUND__DPRINTF_LY)
