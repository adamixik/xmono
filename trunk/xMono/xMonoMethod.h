//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include "Interface/IMonoMethod.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

#include "xMonoAssembly.h"
#include "xMonoClass.h"

class xMonoMethod : public IMonoMethod
{
private:
	xMonoClass * m_pClass;
	MonoMethod * m_pMethod;
public:
	xMonoMethod(xMonoClass * pClass, char * szMethod = NULL, void * obj = NULL);

	void * GetUnmanagedThunk();
	const char * GetName();
};