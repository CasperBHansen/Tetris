/*
 * Tetris
 *
 * Resource.h
 *
 */

#ifndef RESOURCE_H
#define RESOURCE_H

/*!
 * ...
 */
class Resource
{
public:
	//! Constructor.
	/*!
	 * Constructs an instance of the Resource class.
	 */
	Resource(const char * filename);
	virtual ~Resource();
	
	virtual int load() = 0;
	virtual void release() = 0;
	
	int getHandle();

protected:
	const char * resource;
	
private:
	int handle;
};

#endif // RESOURCE_H

