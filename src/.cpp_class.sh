#
#!/bin/sh
#
# cpp_class.sh
#

if [ "$2" != "" ]; then
	project=$2
else
	echo "Missing project name."
	exit 2
fi

if [ "$1" != "" ]; then
	
	class=$1 # should capitalize
	upper=${class^^}
	echo "/*
 * $project
 *
 * $class.h
 *
 */

#ifndef ${upper}_H
#define ${upper}_H

/*!
 * ...
 */
class $class
{
public:
	//! Constructor.
	/*!
	 * Constructs an instance of the $class class.
	 */
	$class();
	~$class();

protected:
private:
};

#endif // ${upper}_H
" > $class.h

	echo "/*
 * $project
 *
 * $class.cpp
 *
 */

#include \"$class.h\"

$class::$class()
{
	// constructor
}

$class::~$class()
{
	// destructor
}
" > $class.cpp

else
	echo "Missing class name."
	exit 1
fi

