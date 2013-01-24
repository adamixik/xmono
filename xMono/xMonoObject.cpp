//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>

#include "xMonoObject.h"
#include "xMonoDefaults.h"
#include <stdarg.h>

MonoArray * CreateArray(xArray * xArr, xMonoClass * m_pClass);

xMonoObject::xMonoObject(xMonoClass * pClass)
{
	m_pClass = pClass;

	m_pObject = mono_object_new((MonoDomain*)pClass->GetAssembly()->GetDomain(), pClass->GetClass());
}

void * xMonoObject::Call(char * _func, char * format, ...)
{
	void * args[64];
	bool unbox = true;
	int argcount = 0;
	MonoMethod* method = mono_class_get_method_from_name(m_pClass->GetClass(), _func, -1);
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
							args[argcount] = mono_string_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), sz);
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
							MonoArray * arr = CreateArray(xArr, m_pClass);
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
		retobj = mono_runtime_invoke(method, GetMonoObject(), args, 0);
		if(retobj && unbox)
			return ((char*)retobj) + sizeof (MonoObject);
		else if(retobj && !unbox)
			return retobj;
		else
			return NULL;
	}
	return NULL;
}

MonoArray * CreateArray(xArray * xArr, xMonoClass * m_pClass)
{
	MonoArray * arr = NULL;
	switch(xArr->type)
	{
	case XMONO_STRING_TYPE:
		{
			arr = mono_array_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), mono_defaults.string_class, xArr->m_objects.size());
			break;
		}
	case XMONO_INTEGER_TYPE:
		{
			arr = mono_array_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), mono_defaults.int32_class, xArr->m_objects.size());

			break;
		}
	case XMONO_FLOAT_TYPE:
		{
			arr = mono_array_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), mono_defaults.double_class, xArr->m_objects.size());

			break;
		}
	case XMONO_OBJECT_TYPE:
		{
			xMonoObject * pObject = (xMonoObject*)xArr->m_objects[0].object;
			arr = mono_array_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), mono_object_get_class(
				(MonoObject*)pObject->GetMonoObject()), xArr->m_objects.size());

			break;
		}
	case XMONO_NATIVE_OBJECT_TYPE:
		{
			MonoObject * pObject = (MonoObject*)xArr->m_objects[0].object;
			arr = mono_array_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), mono_object_get_class(
				(MonoObject*)pObject), xArr->m_objects.size());
			break;
		}
	}
	for(int i = 0; i < xArr->m_objects.size(); i++)
	{
		switch(xArr->type)
		{
		case XMONO_STRING_TYPE:
			{
				MonoString * arg = mono_string_new((MonoDomain*)m_pClass->GetAssembly()->GetDomain(), (const char*)xArr->m_objects[i].object);
				mono_array_setref(arr, i, arg);
				break;
			}
		case XMONO_INTEGER_TYPE:
			{
				mono_array_set(arr, int, i, (int)xArr->m_objects[i].object);
				break;
			}
		case XMONO_FLOAT_TYPE:
			{
				mono_array_setref(arr, i, xArr->m_objects[i].object);
				break;
			}
		case XMONO_OBJECT_TYPE:
			{
				xMonoObject * obj = (xMonoObject*)xArr->m_objects[i].object;
				mono_array_setref(arr, i, obj->GetMonoObject());
				break;
			}
		case XMONO_NATIVE_OBJECT_TYPE:
			{
				mono_array_setref(arr, i, xArr->m_objects[i].object);
				break;
			}
		}
	}
	return arr;
}