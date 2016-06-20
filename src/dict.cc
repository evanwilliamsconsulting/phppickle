#include "dict.h"

Dict& Dict::operator=(const Dict& otherItem)
{
	count = otherItem.count;
	keyIndex = otherItem.keyIndex;
	return *this;
}
void Dict::insertPair(char* theKey,char* theValue)
{
	    int theIndex;
	    theIndex = getIndex();
	    char *keyptr,*valueptr;
	    keyptr=(char*)emalloc(sizeof(char)*200);
	    strcpy(keyptr,theKey);
	    keys[theIndex]=keyptr;
	    valueptr=(char*)emalloc(sizeof(char)*200);
	    strcpy(valueptr,theValue);
	    values[theIndex]=valueptr;
	    incrementIndex();
}
char* Dict::printDict()
{
	char* buf;
	buf = output;
	int theIndex;
	theIndex--;
	theIndex = getIndex();
	buf += sprintf(output,"DICT: ");
	theIndex -= 1;
	for (int i=theIndex;i>=0;i--)
	{
		buf += sprintf(buf," |%s => %s| ",keys[i],values[i]);
	}
	return output;
}
