//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================
#include "xMonoAssembly.h"
#include "Interface/IMono.h"

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

// Defines

#define XMONO_STRING(x) mono_string_to_utf8((MonoString*)x)

// Main Class


class xMono : public IMono
{
private:
	MonoDomain * m_pDomain;
public:
	xMono(char * szName, char * szLibDir);
	~xMono();
	IMonoAssembly * LoadAssembly(char * szFileName, bool callMain = false, int argc = 0, char * argv[] = NULL);
	void AddInternalCall(char * szFuncName, const void * pFunc);

	MonoDomain * GetDomain() { return m_pDomain; };

	void * CreateMonoString(const char * str);
};
