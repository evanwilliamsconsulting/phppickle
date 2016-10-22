#include "stackitem.h"

void StackItem::initializeTuple()
{
	someTuple = (Tuple*)malloc(sizeof(Tuple));
}
void StackItem::getString(char* theCharString)
{
	strcpy(theCharString,someString);
}
void StackItem::initializeDict()
{
	someDict = (Dict*)malloc(sizeof(Dict));
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
int StackItem::getIndex()
{
	return someTuple->index;
}
char* StackItem::getModuleName()
{
	return someTuple->moduleName;
}
void StackItem::setModuleName(char *theModuleName)
{
	moduleName=theModuleName;
}
void StackItem::setClassName(char *theClassName)
{
	className=theClassName;
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
	free(someString);
}
