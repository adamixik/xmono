//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include "../xMono/Interface/xMonoVM.h"

static void Func(int num, void* text, float x)
{
	FILE * f = fopen("test.txt", "a");
	fprintf(f, "Func called: %d %s %f\n", num, XMONO_STRING(text), x);
	fclose(f);
}

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

	IMonoMethod * pTestMethod = pClass->GetMethod("Testing");
	typedef int (__stdcall *TestingMethod) (void * obj, int i, void **);
	void * ex;
	TestingMethod func = (TestingMethod)pTestMethod->GetUnmanagedThunk();
	printf("value: %d\n", func(pObject->GetMonoObject(), 5, &ex));

	xArray * arrInt = new xArray(XMONO_INTEGER_TYPE);
	arrInt->Push((void*)5);
	arrInt->Push((void*)10);
	pObject->Call("arraysInt", "a", arrInt);

	xArray * arrString = new xArray(XMONO_STRING_TYPE);
	arrString->Push("testString1");
	arrString->Push("testString2");
	arrString->Push("testString3");
	pObject->Call("arraysString", "a", arrString);

	xArray * arrFloat = new xArray(XMONO_FLOAT_TYPE);
	float val1 = 15.5f;
	float val2 = 51.8f;
	unsigned int val3 = *(unsigned int*)&val1;
	unsigned int val4 = *(unsigned int*)&val2;
	arrFloat->Push((void*)val3);
	arrFloat->Push((void*)val4);
	pObject->Call("arraysFloat", "a", arrFloat);

	// lets try to use CVector
	xArray * arrVector = new xArray(XMONO_NATIVE_OBJECT_TYPE);
	arrVector->Push(pVectorObject->GetMonoObject());
	pObject->Call("arraysVector", "a", arrVector);

	void * obj = (void*)pObject->Call("end1", "b");
	char * str2 = (char*)pObject->Call("end2", "nb", obj);
	printf("omgvector: %s", XMONO_STRING(str2));

	return 0;
}
