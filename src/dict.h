/* Standard C++ headers */
#include "basics.h"
#include "php.h"

using namespace std;

class Dict {
    public:
	char output[200];
	char *keys[50];
	char *values[50];
	int keyIndex = 0;
	int count = 0;
	void insertPair(char* theKey,char* theValue);
	int getIndex()
	{
	    return keyIndex;
	}
	void incrementIndex()
	{
	    keyIndex++;
	}
	char* printDict();
        Dict()
	{
	    count = 0;
	    keyIndex = 0;
	}
        Dict(const Dict &otherItem)
	{
	    count = otherItem.count;
	    keyIndex = otherItem.keyIndex;
	}
	Dict& operator= (const Dict& otherItem);
};
