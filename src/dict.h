/* Standard C++ headers */
#include "basics.h"
#include "php.h"

using namespace std;

class Dict {
    public:
	char *output;
	char **keys;
	char *values[50];
	int keyIndex;
	int count = 0;
	void insertPair(char* theKey,char* theValue);
	int getIndex();
	void incrementIndex();
	char* printDict();
        Dict();
        Dict(const Dict& otherItem);
	Dict operator= (const Dict& otherItem);
};
