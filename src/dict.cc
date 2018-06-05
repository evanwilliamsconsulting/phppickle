#include "dict.h"


Dict Dict::operator=(const Dict& otherItem)
{
	count = otherItem.count;
	keyIndex = otherItem.keyIndex;
	return *this;
}
Dict::Dict()
{
	count = 0;
	keyIndex = 0;
}
Dict::Dict(const Dict& otherItem)
{
	count = otherItem.count;
	keyIndex = otherItem.keyIndex;
}
int Dict::getIndex()
{
	return keyIndex;
}
void Dict::incrementIndex()
{
	keyIndex++;
}
void Dict::insertPair(char* theKey,char* theValue)
{
	    int theIndex;
	    theIndex = 1;
	    char *keyptr,*valueptr;
	    keyptr=(char*)malloc(sizeof(char)*200);
	    strcpy(keyptr,theKey);
	    keys[theIndex]=keyptr;
	    valueptr=(char*)malloc(sizeof(char)*200);
	    strcpy(valueptr,theValue);
	    values[theIndex]=valueptr;
	    incrementIndex();
}
char* Dict::printDict()
{
	int theIndex;
	theIndex = this->getIndex();
	this->output=(char*)malloc(sizeof(char)*100);
	for (int i=0;i<theIndex;i++)
	{
		sprintf(this->output,"%s",values[i]);
		break;
	}
	return this->output;
}
