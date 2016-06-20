/* Standard C++ headers */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <string.h>
#include <stdexcept>
#include <fstream>
#include <regex>

using namespace std;

class Tuple {
    public:
	char* moduleName;
	char* className;
	int index;
        int asObject;
        Tuple()
	{
	    index = 0;
	    asObject = 0;
	}
        Tuple(const Tuple &otherItem)
	{
	    asObject = otherItem.asObject;
	    index = otherItem.index;
	    moduleName = otherItem.moduleName;
	    className = otherItem.className;
	}
	Tuple& operator= (const Tuple &otherItem);
};
