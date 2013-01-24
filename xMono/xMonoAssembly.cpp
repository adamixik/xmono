//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

#include "xMonoAssembly.h"
#include "xMonoClass.h"

xMonoAssembly::xMonoAssembly(MonoDomain * pDomain, char * szFileName, bool callMain, int argc, char * argv[])
{
	m_pDomain = pDomain;
	m_pAssembly = mono_domain_assembly_open(pDomain, szFileName);

	if(callMain)
		mono_jit_exec(pDomain, m_pAssembly, argc, argv);

	m_pImage = mono_assembly_get_image(m_pAssembly);
}

IMonoClass * xMonoAssembly::GetClass(char * szNamespace, char * szClassName)
{
	return new xMonoClass(this, szNamespace, szClassName);
}