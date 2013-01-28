//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

#include "xMono.h"
#include "xMonoDefaults.h"

MonoDefaults mono_defaults;

xMono::xMono(char * szName, char * szLibDir)
{
	mono_set_dirs(szLibDir, szLibDir);
	m_pDomain = mono_jit_init(szName);

	mono_defaults.corlib = mono_get_corlib();

	mono_defaults.object_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Object");

	mono_defaults.void_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Void");

	mono_defaults.boolean_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Boolean");

	mono_defaults.byte_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Byte");

	mono_defaults.sbyte_class = mono_class_from_name (
                mono_defaults.corlib, "System", "SByte");

	mono_defaults.int16_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Int16");

	mono_defaults.uint16_class = mono_class_from_name (
                mono_defaults.corlib, "System", "UInt16");

	mono_defaults.int32_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Int32");

	mono_defaults.uint32_class = mono_class_from_name (
                mono_defaults.corlib, "System", "UInt32");

	mono_defaults.uint_class = mono_class_from_name (
                mono_defaults.corlib, "System", "UIntPtr");

	mono_defaults.int_class = mono_class_from_name (
                mono_defaults.corlib, "System", "IntPtr");

	mono_defaults.int64_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Int64");
	mono_defaults.uint64_class = mono_class_from_name (
                mono_defaults.corlib, "System", "UInt64");

	mono_defaults.single_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Single");

	mono_defaults.double_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Double");

	mono_defaults.char_class = mono_class_from_name (
                mono_defaults.corlib, "System", "Char");

	mono_defaults.string_class = mono_class_from_name (
                mono_defaults.corlib, "System", "String");
}

xMono::~xMono()
{
	mono_jit_cleanup(m_pDomain);
}

IMonoAssembly * xMono::LoadAssembly(char * szFileName, bool callMain, int argc, char * argv[])
{
	return new xMonoAssembly(m_pDomain, szFileName, callMain, argc, argv);
}

void xMono::AddInternalCall(char * szFuncName, const void * pFunc)
{
	mono_add_internal_call(szFuncName, pFunc);
}

void * xMono::CreateMonoString(const char * str)
{
	return mono_string_new(m_pDomain, str);
}
