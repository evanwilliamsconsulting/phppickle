#include "stackitem.h"


void StackItem::initialize()
{
}
void StackItem::initializeTuple()
{
	this->someTuple = new Tuple();
}
void StackItem::getString(char* theCharString)
{
	strcpy(theCharString,someString);
}
void StackItem::initializeDict()
{
	this->someDict = new Dict();
	this->someDict->output=(char*)malloc(sizeof(char)*200);
	this->someDict->keys=(char**)malloc(sizeof(char*)*50);
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
	return this->moduleName;
}
void StackItem::setModuleName(char *theModuleName)
{
	this->moduleName=(char*)malloc(sizeof(char)*100);
	strcpy(this->moduleName,theModuleName);
}
void StackItem::setClassName(char *theClassName)
{
	this->className=(char*)malloc(sizeof(char)*100);
	strcpy(this->className,theClassName);
}
char* StackItem::getClassName()
{
	return this->className;
}
char* StackItem::getDict()
{
	return this->someDict->printDict();
}
void StackItem::freeMemory()
{
	efree(someString);
}
