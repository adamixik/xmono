//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include <stdio.h>

#include <vector>

enum xValueType
{
	XMONO_STRING_TYPE,
	XMONO_INTEGER_TYPE,
	XMONO_FLOAT_TYPE,
	XMONO_OBJECT_TYPE,
	XMONO_NATIVE_OBJECT_TYPE,
	XMONO_ARRAY_TYPE
};

struct xObject
{
	void * object;
};

struct xArray
{
	std::vector<xObject> m_objects;
	xValueType type;
	xArray(xValueType type)
	{
		this->type = type;
	}
	void Push(void * object)
	{
		xObject * obj = new xObject;
		obj->object = object;
		m_objects.push_back(*obj);
	};
	~xArray()
	{
		for(unsigned int i = 0; i < m_objects.size(); i++)
		{
			delete &m_objects[i];
		}
		m_objects.clear();
	};
};

class IMonoObject
{
public:
	// Calls object function
	// Format:
	// b = do call without unboxing returned value(especially used for strings)
	// s = string
	// i = int32
	// f = float
	// o = IMonoObject
	// n = native object
	virtual void * Call(char * _func, char * format = NULL, ...) = 0;

	// For internal use
	virtual void * GetMonoObject() = 0;
};