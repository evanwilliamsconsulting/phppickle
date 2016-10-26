#include "phpzope.h"


//  Basic PHPZOPE Class
PHPZope::PHPZope() {
}

PHPZope::~PHPZope() {
}

int PHPZope::returnValue() {
	return 8;
}
stack<StackItem>& PHPZope::retrieveCurrentStack()
{
	return this->currentStack;
}
vector<StackItem>& PHPZope::retrieveCurrentMemo()
{
	return this->theMemo;
}
int PHPZope::retrieveStackDepth() {
	stack<StackItem> theStack = this->currentStack;
	int stackDepth = theStack.size();
	return stackDepth;
}
int PHPZope::setPickle(char *pickle)
{
	this->theString.assign(pickle,strlen(pickle));
	return 0;
}
int PHPZope::readPickle(char *src)
{
	// http://en.cppreference.com/w/cpp/string/byte/strcpy
	//this->filename = new char(std::strlen(src)+10);
    	strcpy(this->filename, src);
	return 0;
} 
int PHPZope::getMemoSize()
{
	return memoSize;
}

int PHPZope::retrieve_state(ifstream& infile,string& state2,stack<StackItem>& theStack,int& lastMark,vector<StackItem>& theMemo)
        {
	std::string::iterator it;
	std::string theString;
	std::string filename = "state.txt";
	StackItem *ptrStackItem,*testStackItem;
	int result = 0;
	char opcode;
	char *ptr;
	char *buf;
	char buffer[1000];
	int saveString = -1;

	/* fetch the data : retrieve all the rows in the result set */

	this->currentStack = theStack;
	Pickle *myPickler = new Pickle();
	int num = 0;
	std::stringstream parse(state2);
	int len = parse.gcount();
	char someChar;
	int someInt;
	parse >> someChar;
	theString = parse.str();
	it = theString.begin();
	Opcode *nextOpcode;
	buf = (char*)malloc(sizeof(char)*200);
	strcpy(buf,"BEGIN");
	do
	{
	    for (int i = 0; i < OPCODE_COUNT; i++)
	    {
	    	Opcode *currentOpcode = myPickler->opcodes[i];

		if (result == 2)
		{
	    		for (int i = 0; i < OPCODE_COUNT; i++)
	    		{
	    			nextOpcode = myPickler->opcodes[i];
	        		if (nextOpcode->opcode == someChar)
				{
					break;
				}
			}
	            ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
		    ptrStackItem->initialize();
		    ptrStackItem->opcode = someChar;
		    ptrStackItem->theMark = 0;
		    ptrStackItem->lastMark = lastMark;
	    	    theStack.push(*ptrStackItem);
	            result = (nextOpcode->opfunc)(infile,theString,it,*ptrStackItem,theStack,theMemo);
		    result = 1;
		}
		else if (result == 3)
		{
			someChar = '~';
	                ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
		    	ptrStackItem->initialize();
		        ptrStackItem->opcode = someChar;
		        ptrStackItem->theMark = 0;
		        ptrStackItem->lastMark = lastMark;
		        ptrStackItem->someString=(char*)malloc(sizeof(char)*100);
			strcpy(ptrStackItem->someString,buf);
	    	        theStack.push(*ptrStackItem);
	            	result = (Opcode::fnGLOBAL1)(infile,theString,it,*ptrStackItem,theStack,theMemo);
	            	//result = (currentOpcode->opfunc)(infile,theString,it,*ptrStackItem,theStack,theMemo);
			getline(infile,theString);
			it = theString.begin();
			someChar = *it;
			result = 1;
		}
		else if (result == 4)
		{
			someChar = 'U';
	                ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
		    	ptrStackItem->initialize();
		        ptrStackItem->opcode = someChar;
		        ptrStackItem->theMark = 0;
		        ptrStackItem->lastMark = lastMark;
	    	        theStack.push(*ptrStackItem);
			Utils::dprintf("fnSHORT_BINSTRING: result == 4, calling fnSHORT_BINSTRING1\n");
	            	result = (Opcode::fnSHORT_BINSTRING1)(infile,theString,it,*ptrStackItem,theStack,theMemo);
			result = 1;
		}	
		else if (result == 5)
		{
			result = 1;
		}
	        else if (currentOpcode->opcode == someChar)
                {
		    char *someString;
	            ptrStackItem = (StackItem*)malloc(1+sizeof(StackItem));
		    ptrStackItem->initialize();
		    ptrStackItem->opcode = someChar;
		    ptrStackItem->theMark = 0;
		    ptrStackItem->lastMark = lastMark;
		    
		    if (saveString==0)
		    {
			ptrStackItem->someString=(char*)malloc(sizeof(char)*1000);
			Utils::dprintf("saveString: %s\n",ptrStackItem->someString);
			strcpy(ptrStackItem->someString,buf);
			ptrStackItem->hasString = 0;
			free(buf);
		    }
		    Utils::dprintf("\nopcode: %c\n",someChar);
	    	    theStack.push(*ptrStackItem);
	            result = (currentOpcode->opfunc)(infile,theString,it,*ptrStackItem,theStack,theMemo);

		    if (ptrStackItem->hasString == 0)
		    {
			buf=(char*)malloc(sizeof(char)*strlen(ptrStackItem->someString));
			strcpy(buf,ptrStackItem->someString);
			saveString = 0;
		    }

		    if (result == 2)
		    {
		        someChar = *it++;
		    }
		    else if (result == 3)
		    {
		        getline(infile,theString);
			// If this is a newobj opcode, discard the next line
			testStackItem = &theStack.top();
			if (testStackItem->opcode == '*')
			{
		        	getline(infile,theString);
			    	it = theString.begin();
				someChar = *it;
			        result = 1;
			}
			else
			{
			    someChar = '~';
			    it = theString.begin();
			}
		    }
		    else if (result == 4)
		    {
			Utils::dprintf("fnSHORT_BINSTRING: result == 4, after capture, prepare\n");
		        getline(infile,theString);
			someChar = 'U';
			it = theString.begin();
		    }
		    else if (result == 5)
		    {
				getline(infile,theString);
				it = theString.begin();
				someChar = *it++;
			    }	
			    else
			    {
				someChar = *it;
				continueSHORT_BINSTRING = 0;
			    }

			    strcpy(buf,"BEGIN");
			    // strcpy(buf,ptrStackItem->someString);
			    ptrStackItem = &theStack.top();
			    lastMark = ptrStackItem->lastMark;	
			}
		    }
	} while ( *it != '\000' && it != theString.end() && (result == 0 || result == 2 || result == 3 || result == 4 || result == 5));

	printf("\n");
	return 0;
} // retrieve_state()

void PHPZope::readFile(stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	memoSize = 15;
	std::string state;
	int j;
	int boolSTOP;
	int lastMark = 0;
	continueSHORT_BINSTRING = 0;

	ifstream infile;

        //__asm__("int3");
	infile.open(this->filename);
	boolSTOP = -1;
        if ( infile.fail() )
        {
	   strcpy(this->filename,strerror(errno));
	}
	else
	{
	    while (!infile.eof())
            {
		theMemo.resize(memoSize);
		getline(infile,state);
//		std::stringstream parse(state);
//	        this->retrieve_state(infile,parse,theStack,lastMark,theMemo);

		cout << state;

	        this->retrieve_state(infile,state,theStack,lastMark,theMemo);
		memoSize += 1;
	    }
	    infile.close();
	    int i;
        }
}

char* PHPZope::returnPickleString(stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	memoSize = 15;
	int j;
	int boolSTOP;
	int lastMark = 0;
	continueSHORT_BINSTRING = 0;
	ifstream infile;
	std::string state;

	theMemo.resize(memoSize);
	std::stringstream parse(this->theString);
	this->retrieve_state(infile,state,theStack,lastMark,theMemo);
	memoSize += 1;

	return 0;
}
