//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include "xMonoMethod.h"

void logprintf(char * format, ...);

xMonoMethod::xMonoMethod(xMonoClass * pClass, char * szMethod, void * obj)
{
	m_pClass = pClass;

	if(!obj)
	{
		m_pMethod = mono_class_get_method_from_name(m_pClass->GetClass(), szMethod, -1);
	}
	else
	{
		m_pMethod = mono_get_delegate_invoke(mono_object_get_class((MonoObject*)obj));
	}
	logprintf("mth2: 0x%x", m_pMethod);
}

void * xMonoMethod::GetUnmanagedThunk()
{
	return mono_method_get_unmanaged_thunk(m_pMethod);
}

const char * xMonoMethod::GetName()
{
	return mono_method_get_name(m_pMethod);
}
