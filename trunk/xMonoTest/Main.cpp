//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include "../xMono/Interface/xMonoVM.h"

IMono * pMono = NULL;

static void Func(int num, void* text, float x)
{
	FILE * f = fopen("test.txt", "a");
	fprintf(f, "Func called: %d %s %f\n", num, XMONO_STRING(text), x);
	fclose(f);
}

static void * Func2(void * text)
{
	const char * str = XMONO_STRING(text);
	char * ret = new char[256];
	sprintf(ret, "Returning: %s\n", str);
	return pMono->CreateMonoString(ret);
}

int main()
{
	pMono = GetMonoVM("xMono", "./");
	pMono->AddInternalCall("MonoEmbed::Func", (void*)Func);
	pMono->AddInternalCall("MonoEmbed::Func2", (void*)Func2);
	IMonoAssembly * pAssembly = pMono->LoadAssembly("./test.dll");

	IMonoClass * pClass = pAssembly->GetClass("", "Module");
	pClass->Call("RunStatic");

	IMonoObject * pObject = pClass->New();

	pObject->Call(".ctor");
	pObject->Call("Run");
	pObject->Call("Test", "sif", "tease", 18, 16.111f);

	char * str = (char*)pObject->Call("stringTest", "sb", "test");
	printf("returned str: %s\n", XMONO_STRING(str));

	IMonoClass * pTestClass = pAssembly->GetClass("", "Test");
	pTestClass->Call("Testing", "o", pObject);

	int i = *(int*)pObject->Call("Test", "sif", "teasear", 555, 11.111f);
	printf("returned: %d\n", i);
	
	IMonoClass * pVectorClass = pAssembly->GetClass("", "CVector3");
	IMonoObject * pVectorObject = pVectorClass->New();
	pVectorObject->Call(".ctor", "iii", 5, 15, 25);

	pObject->Call("VectorTest", "o", pVectorObject);
#ifndef LINUX
	IMonoMethod * pTestMethod = pClass->GetMethod("Testing");
	typedef int (__stdcall *TestingMethod) (void * obj, int i, void **);
	void * ex;
	TestingMethod func = (TestingMethod)pTestMethod->GetUnmanagedThunk();
	printf("value: %d\n", func(pObject->GetMonoObject(), 5, &ex));
#endif
	xArray * arrInt = new xArray(XMONO_INTEGER_TYPE);
	arrInt->Push(5);
	arrInt->Push(10);
	pObject->Call("arraysInt", "a", arrInt);

	xArray * arrString = new xArray(XMONO_STRING_TYPE);
	arrString->Push("testString1");
	arrString->Push("testString2");
	arrString->Push("testString3");
	pObject->Call("arraysString", "a", arrString);

	xArray * arrFloat = new xArray(XMONO_FLOAT_TYPE);
	arrFloat->Push(15.5f);
	arrFloat->Push(51.8f);
	pObject->Call("arraysFloat", "a", arrFloat);

	// lets try to use CVector
	xArray * arrVector = new xArray(XMONO_NATIVE_OBJECT_TYPE);
	arrVector->Push(pVectorObject);
	pObject->Call("arraysVector", "a", arrVector);

	void * obj = (void*)pObject->Call("end1", "b");
	char * str2 = (char*)pObject->Call("end2", "nb", obj);
	printf("omgvector: %s", XMONO_STRING(str2));

	pClass->Call("delegevent", "a", arrInt);

	return 0;
}
