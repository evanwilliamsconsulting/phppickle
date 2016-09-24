/* Standard C++ headers */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>
#include <fstream>
#include <stack>
#include <regex>

#include "php.h"

#include "tuple.h"
#include "dict.h"

using namespace std;

class StackItem {
    public:
        char opcode;
        int someInt;
	char* someString;
	int hasString;
	Tuple* someTuple;
	Dict* someDict;
	char* moduleName;
	char* className;
	int theMark;
	int lastMark;
        StackItem()
	{
	    hasString = -1;
	    theMark = 0;
	    initializeTuple();
/*
	    someTuple->moduleName = (char*)malloc(sizeof(char)*100);
 	    someTuple->className = (char*)malloc(sizeof(char)*100);
	    moduleName = (char*)malloc(sizeof(char)*100);
 	    className = (char*)malloc(sizeof(char)*100);
*/
	}
	void initialize()
	{
	    hasString = -1;
	    theMark = 0;
	    initializeTuple();
/*
	    someTuple->moduleName = (char*)malloc(sizeof(char)*100);
 	    someTuple->className = (char*)malloc(sizeof(char)*100);
	    moduleName = (char*)malloc(sizeof(char)*100);
 	    className = (char*)malloc(sizeof(char)*100);
*/
	}
        StackItem(const StackItem &otherItem)
	{
	    hasString = otherItem.hasString;
	    opcode = otherItem.opcode;
	    someInt = otherItem.someInt;
	    someString = otherItem.someString;
	    theMark = otherItem.theMark;
	    lastMark = otherItem.lastMark;
	    someTuple = otherItem.someTuple;
	    someDict = otherItem.someDict;
	}
	StackItem& operator= (const StackItem &otherItem)
	{
	    hasString = otherItem.hasString;
	    opcode = otherItem.opcode;
	    someInt = otherItem.someInt;
	    someString = otherItem.someString;
	    theMark = otherItem.theMark;
	    lastMark = otherItem.lastMark;
	    someTuple = otherItem.someTuple;
	    someDict = otherItem.someDict;
	}
	void initializeTuple();
	void initializeDict();
	void insertDictPair(char* theKey,char* theValue);
	void setIndex(int theIndex);
	void setModuleName(char* theModuleName);
	void setClassName(char* theClassName);
	void setAsObject();
	void freeMemory();
	char* getModuleName();
	char* getClassName();
	void getString(char* theCharString);
	char* getDict();
	int getIndex();
};
