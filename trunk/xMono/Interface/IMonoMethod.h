#pragma once

#include <stdio.h>

class IMonoMethod
{
public:
	// Gets unmanaged thunk(look at Mono's wiki page)
	virtual void * GetUnmanagedThunk() = 0;

	// Gets name of method
	virtual const char * GetName() = 0;
};