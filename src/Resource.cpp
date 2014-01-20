/*
 * Tetris
 *
 * Resource.cpp
 *
 */

#include "Resource.h"

Resource::Resource(const char * filename)
{
	static int handles = 0;
	
	resource = filename;
	handle = ++handles;
}

Resource::~Resource()
{
	// destructor
}

int Resource::getHandle()
{
	return handle;
}

