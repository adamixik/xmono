//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================
#pragma once

#include "Interface/IMonoClass.h"
#include "Interface/IMonoMethod.h"
#include "Interface/IMonoAssembly.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

class xMonoAssembly;
class xMonoObject;
class xMonoMethod;

class xMonoClass : public IMonoClass
{
private:
	xMonoAssembly * m_pAssembly;
	MonoClass * m_pClass;
public:
	xMonoClass(xMonoAssembly * pAssembly, char * szNamespace, char * szClassName);

	void * Call(char * _func, char * format = NULL, ...);

	IMonoObject * New();

	const char * GetName();
	const char * GetNamespace();

	IMonoMethod * GetMethod(char * szMethod);

	IMonoAssembly * GetAssembly() { return (IMonoAssembly*)m_pAssembly; };
	MonoClass * GetClass() { return m_pClass; };
};