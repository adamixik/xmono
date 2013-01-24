//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include <stdio.h>
#include "IMonoClass.h"

class IMonoAssembly
{
public:
	// Gets interface of assembly class
	virtual IMonoClass * GetClass(char * szNamespace, char * szClassName) = 0;

	// For internal use only
	virtual void * GetDomain() = 0;
	virtual void * GetAssembly() = 0;
	virtual void * GetImage() = 0;
};