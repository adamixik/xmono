#pragma once

#include "IMonoAssembly.h"

class IMono
{
public:
	// Loads assembly into memory and executes it, returns assembly
	virtual IMonoAssembly * LoadAssembly(char * szFileName, bool callMain = false, int argc = 0, char * argv[] = NULL) = 0;
	
	// Adds internal call for Mono assemblys
	virtual void AddInternalCall(char * szFuncName, const void * pFunc) = 0;
};