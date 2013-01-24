//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include <stdio.h>
#include "IMonoObject.h"
#include "IMonoMethod.h"

class IMonoClass
{
public:
	// Calls static function in class
	// Format:
	// b = do call without unboxing returned value(especially used for strings)
	// s = string
	// i = int32
	// f = float
	// o = IMonoObject
	// n = native object
	virtual void * Call(char * _func, char * format = NULL, ...) = 0;

	// Creates a new object of class
	virtual IMonoObject * New() = 0;

	// Gets class name
	virtual const char * GetName() = 0;

	// Gets class namespace name
	virtual const char * GetNamespace() = 0;

	// Gets interface to selected method
	virtual IMonoMethod * GetMethod(char * szMethod) = 0;
};