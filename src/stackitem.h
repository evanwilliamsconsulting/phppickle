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
#include <stdlib.h>

#include "php.h"

#include "tuple.h"
#include "dict.h"

using namespace std;

class StackItem {
    public:
        char opcode;
        int someInt;
	char *someString;
	int hasString;
	Tuple* someTuple;
	Dict* someDict;
	char *moduleName;
	char *className;
	int theMark;
	int lastMark;
        StackItem()
	{
	    hasString = -1;
	    theMark = 0;
	}
	void initialize();
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
