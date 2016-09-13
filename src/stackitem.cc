#include "stackitem.h"

void StackItem::initializeTuple()
{
	someTuple = (Tuple*)emalloc(sizeof(Tuple));
}
void StackItem::getString(char* theCharString)
{
	strcpy(theCharString,someString);
}
void StackItem::initializeDict()
{
	someDict = (Dict*)emalloc(sizeof(Dict));
}
void StackItem::insertDictPair(char* theKey,char* theValue)
{
	someDict->insertPair(theKey,theValue);
}
void StackItem::setIndex(int theIndex)
{
	someTuple->index = theIndex;
}
void StackItem::setAsObject()
{
	someTuple->asObject = 1;
}
void StackItem::setModuleName(char* theModuleName)
{
	someTuple->moduleName = (char*)emalloc(sizeof(char)*100);
	strcpy(someTuple->moduleName,theModuleName);
}
void StackItem::setClassName(char* theClassName)
{
	someTuple->className = (char*)emalloc(sizeof(char)*100);
	strcpy(someTuple->className,theClassName);
}
int StackItem::getIndex()
{
	return someTuple->index;
}
char* StackItem::getModuleName()
{
	return someTuple->moduleName;
}
char* StackItem::getClassName()
{
	return someTuple->className;
}
char* StackItem::getDict()
{
	return someDict->printDict();
}
void StackItem::freeMemory()
{
	efree(someString);
}
