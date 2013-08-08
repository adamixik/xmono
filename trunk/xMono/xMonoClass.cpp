//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

#include "xMonoClass.h"
#include "xMonoAssembly.h"
#include "xMonoObject.h"
#include "xMonoMethod.h"
#include <stdarg.h>

MonoArray * CreateArray(xArray * xArr, xMonoClass * m_pClass);


xMonoClass::xMonoClass(xMonoAssembly * pAssembly, char * szNamespace, char * szClassName)
{
	m_pAssembly = pAssembly;

	m_pClass = mono_class_from_name((MonoImage*)pAssembly->GetImage(), szNamespace, szClassName);
}

void * xMonoClass::Call(char * _func, char * format, ...)
{
	void * args[64];
	bool unbox = true;
	int argcount = 0;
	MonoMethod* method = mono_class_get_method_from_name(m_pClass, _func, -1);
	if(method)
	{
			const char* p = format;
			if(p)
			{
				va_list ap;
				va_start(ap, format);
				while(*p)
				{
					switch(*p)
					{
					case 'b':
						{
							// TODO
							unbox = false;
						}
						break;
					case 'i':
						{
							int * i = new int;
							*i = va_arg(ap, int);
							args[argcount] = i;
							break;
						}
					case 'f':
						{
							float * f = new float;
							*f = va_arg(ap, double);
							args[argcount] = f;
							break;
						}
						break;
					case 's':
						{
							char* sz = va_arg(ap, char*);
							args[argcount] = mono_string_new((MonoDomain*)m_pAssembly->GetDomain(), sz);
							break;
						}
					case 'o':
						{
							xMonoObject * pObject = va_arg(ap, xMonoObject*);
							args[argcount] = pObject->GetMonoObject();
							break;
						}
					case 'n':
						{
							void * pObject = va_arg(ap, void*);
							args[argcount] = pObject;
							break;
						}
					case 'a':
						{
							xArray * xArr = va_arg(ap, xArray*);
							MonoArray * arr = CreateArray(xArr, this);
							args[argcount] = arr;
							break;
						}
					}
					argcount++;
					++p;
				}
				va_end(ap);
			}

		MonoObject * retobj = NULL;

		MonoObject * exc = NULL;
		retobj = mono_runtime_invoke(method, NULL, args, &exc);

		if(exc)
		{
			return NULL;
		}

		if(retobj && unbox)
			return ((char*)retobj) + sizeof (MonoObject);
		else if(retobj && !unbox)
			return retobj;
		else
			return NULL;
	}
	return NULL;
}

IMonoObject * xMonoClass::New()
{
	xMonoObject * pObject = new xMonoObject(this);

	return pObject;
}

const char * xMonoClass::GetName()
{
	return mono_class_get_name(m_pClass);
}

const char * xMonoClass::GetNamespace()
{
	return mono_class_get_namespace(m_pClass);
}

IMonoMethod * xMonoClass::GetMethod(char * szMethod)
{
	return new xMonoMethod(this, szMethod);
}