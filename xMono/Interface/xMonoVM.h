//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include "IMono.h"
#include "IMonoAssembly.h"

// Defines
// Converts MonoString* to utf8 char * array
#define XMONO_STRING(x) ConvertMonoString((void*)x)
// Unboxes value
#define XMONO_UNBOX(x) Unbox((void*)x)

// Main
extern "C"
{
	// Create a new Mono Virtual Machine
	IMono * GetMonoVM(const char * szName, const char * szLibDir);

	// For conversion of MonoString*
	char * ConvertMonoString(void * str);

	// Unbox value
	void * Unbox(void * obj);
}