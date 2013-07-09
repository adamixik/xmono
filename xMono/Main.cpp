//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include <stdio.h>
#include <string.h>

#include "xMono.h"
#include "xMonoAssembly.h"
#include "xMonoClass.h"
#include "xMonoObject.h"
#include "xMonoMethod.h"

#if 0
static void Func(int num, MonoString* text, float x)
{
	FILE * f = fopen("test.txt", "a");
	fprintf(f, "Func called: %d %s %f\n", num, XMONO_STRING(text), x);
	fclose(f);
}
#endif

#ifdef WIN32
#define XEXPORT __declspec(dllexport)
#else
#define XEXPORT
#endif

extern "C"
{
	XEXPORT void PrintSomething(char * str)
	{
	   printf("%s\n", str);
	}
	XEXPORT IMono * GetMonoVM(const char * szName, const char * szLibDir)
	{
		return new xMono(szName, szLibDir);
	}
	XEXPORT char * ConvertMonoString(void * str)
	{
		return mono_string_to_utf8((MonoString*)str);
	}
	XEXPORT void * Unbox(void * obj)
	{
		return mono_object_unbox((MonoObject*)obj);
	}
}

int main()
{
	return 0;
}

/*
int main()
{
	IMono * pMono = GetMonoVM("xMono", "./");
	pMono->AddInternalCall("MonoEmbed::Func", (void*)Func);
	IMonoAssembly * pAssembly = pMono->LoadAssembly("./test.dll");

	IMonoClass * pClass = pAssembly->GetClass("", "Module");
	pClass->Call("RunStatic");

	IMonoObject * pObject = pClass->New();

	pObject->Call(".ctor");
	pObject->Call("Run");
	pObject->Call("Test", "sif", "tease", 18, 16.111f);

	char * str = (char*)pObject->Call("stringTest", "s", "sdfasdfasdf");
	printf("returned str: %s\n", XMONO_STRING(str));

	IMonoClass * pTestClass = pAssembly->GetClass("", "Test");
	pTestClass->Call("Testing", "o", pObject);

	int i = *(int*)pObject->Call("Test", "sif", "teasear", 555, 11.111f);
	printf("returned: %d\n", i);
	
	IMonoClass * pVectorClass = pAssembly->GetClass("", "CVector3");
	IMonoObject * pVectorObject = pVectorClass->New();
	pVectorObject->Call(".ctor", "iii", 5, 15, 25);

	pObject->Call("VectorTest", "o", pVectorObject);

	IMonoMethod * pTestMethod = pClass->GetMethod("Testing");

	/*typedef int (*GetHashCode) (int i);

	GetHashCode func = (GetHashCode)pTestMethod->GetUnmanagedThunk();
	printf("value: %d\n", func(5));*/
//}

