//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================
#pragma once

#include "Interface/IMonoAssembly.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

class xMonoClass;
class IMonoClass;

class xMonoAssembly : public IMonoAssembly
{
private:
	MonoDomain * m_pDomain;
	MonoAssembly * m_pAssembly;
	MonoImage * m_pImage;
public:
	xMonoAssembly(MonoDomain * pDomain, char * szFileName, bool callMain = false, int argc = 0, char * argv[] = NULL);

	IMonoClass * GetClass(char * szNamespace, char * szClassName);

	void * GetDomain() { return m_pDomain; };
	void * GetAssembly() { return m_pAssembly; };
	void * GetImage() { return m_pImage; };
};