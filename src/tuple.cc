#include "tuple.h"

Tuple& Tuple::operator=(const Tuple& otherItem)
{
	asObject = otherItem.asObject;
	index = otherItem.index;
	moduleName = otherItem.moduleName;
	className = otherItem.className;
	return *this;
}
