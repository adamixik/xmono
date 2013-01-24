//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================
#pragma once

#include "Interface/IMonoObject.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

#include "xMonoAssembly.h"
#include "xMonoClass.h"




class xMonoObject : public IMonoObject
{
private:
	xMonoClass * m_pClass;
	MonoObject * m_pObject;
public:
	xMonoObject(xMonoClass * pClass);

	void * Call(char * _func, char * format = NULL, ...);

	void * GetMonoObject() { return m_pObject; };
};