#include "pickle.h"

#define USE_OLD_MALLOC 1


Opcode::Opcode(char opcodeChar,const char *desc,fn funct)
{
    this->opcode = opcodeChar;
    this->opfunc = funct;
    strcpy(this->desc,(const char *)desc);
}
void Opcode::setModule(std::string inModule)
{
	this->module=inModule;
}
void Opcode::setName(std::string inName) 
{
	this->name=inName;
}
void Opcode::setPid(std::string inPid) 
{
	this->pid=inPid;
}
char* Opcode::getDescription()
{
	return this->desc;
}
Pickle::Pickle()
{
    opcodes[GLOBAL1] = new Opcode('~',"GLOBAL1",Opcode::fnGLOBAL1);
    opcodes[GLOBAL2] = new Opcode('!',"GLOBAL2",Opcode::fnGLOBAL2);
    opcodes[GLOBAL3] = new Opcode('*',"GLOBAL3",Opcode::fnGLOBAL3);
    opcodes[STOP] = new Opcode('.',"STOP",Opcode::fnSTOP);
    opcodes[MARK] = new Opcode('(',"MARK",Opcode::fnMARK);
    opcodes[POP] = new Opcode('0',"POP",Opcode::fnPOP);
    opcodes[POP_MARK] = new Opcode('1',"POP_MARK",Opcode::fnPOP_MARK);
    opcodes[DUP] = new Opcode('2',"DUP",Opcode::fnDUP);
    opcodes[FLOAT] = new Opcode('F',"FLOAT",Opcode::fnFLOAT);
    opcodes[INT] = new Opcode('I',"INT",Opcode::fnINT);
    opcodes[BININT] = new Opcode('J',"BININT",Opcode::fnBININT);
    opcodes[BININT2] = new Opcode('M',"BININT2",Opcode::fnBININT2);
    opcodes[LLONG] = new Opcode('L',"LLONG",Opcode::fnLONG);
    opcodes[NONE] = new Opcode('N',"NONE",Opcode::fnNONE);
    opcodes[PERSID] = new Opcode('P',"PERSID",Opcode::fnPERSID);
    opcodes[BINPERSID] = new Opcode('Q',"BINPERSID",Opcode::fnBINPERSID);
    opcodes[REDUCE] = new Opcode('R',"REDUCE",Opcode::fnREDUCE);
    opcodes[STRING] = new Opcode('S',"STRING",Opcode::fnSTRING);
    opcodes[BINSTRING] = new Opcode('T',"BINSTRING",Opcode::fnBINSTRING);
    opcodes[SHORT_BINSTRING] = new Opcode('U',"SHORT_BINSTRING",Opcode::fnSHORT_BINSTRING);
    opcodes[SHORT_BINSTRING1] = new Opcode('U',"SHORT_BINSTRING",Opcode::fnSHORT_BINSTRING1);
    opcodes[UNICODE] = new Opcode('V',"UNICODE",Opcode::fnUNICODE);
    opcodes[BINUNICODE] = new Opcode('X',"BINUNICODE",Opcode::fnBINUNICODE);
    opcodes[APPEND] = new Opcode('a',"APPEND",Opcode::fnAPPEND);  
    opcodes[BUILD] = new Opcode('b',"BUILD",Opcode::fnBUILD);  
    opcodes[GLOBAL] = new Opcode('c',"GLOBAL",Opcode::fnGLOBAL);
    opcodes[DICT] = new Opcode('d',"DICT",Opcode::fnDICT);
    opcodes[EMPTY_DICT] = new Opcode('}',"EMPTY_DICT",Opcode::fnEMPTY_DICT);
    opcodes[APPENDS] = new Opcode('e',"APPENDS",Opcode::fnAPPENDS);
    opcodes[GET] = new Opcode('g',"GET",Opcode::fnGET);    
    opcodes[BINGET] = new Opcode('h',"BINGET",Opcode::fnBINGET);
    opcodes[INST] = new Opcode('i',"INST",Opcode::fnINST); 
    opcodes[LONG_BINGET] = new Opcode('j',"LONG_BINGET",Opcode::fnLONG_BINGET);
    opcodes[LIST] = new Opcode('l',"LIST",Opcode::fnLIST);     
    opcodes[EMPTY_LIST] = new Opcode(']',"EMPTY_LIST",Opcode::fnEMPTY_LIST);
    opcodes[OBJ] = new Opcode('o',"OBJ",Opcode::fnOBJ);     
    opcodes[PUT] = new Opcode('p',"PUT",Opcode::fnPUT);    
    opcodes[BINPUT] = new Opcode('q',"BINPUT",Opcode::fnBINPUT);
    opcodes[LONG_BINPUT] = new Opcode('r',"LONG_BINPUT",Opcode::fnLONG_BINPUT);
    opcodes[SETITEM] = new Opcode('s',"SETITEM",Opcode::fnSETITEM);  
    opcodes[TUPLE] = new Opcode('t',"TUPLE",Opcode::fnTUPLE);   
    opcodes[EMPTY_TUPLE] = new Opcode(')',"EMPTY_TUPLE",Opcode::fnEMPTY_TUPLE);
    opcodes[SETITEMS] = new Opcode('u',"SETITEMS",Opcode::fnSETITEMS); 
    opcodes[BINFLOAT] = new Opcode('G',"BINFLOAT",Opcode::fnBINFLOAT);
    opcodes[PROTO] = new Opcode('\x80',"PROTO",Opcode::fnPROTO);  
    opcodes[NEWOBJ] = new Opcode('\x81',"NEWOBJ",Opcode::fnNEWOBJ);
    opcodes[EXT1] = new Opcode('\x82',"EXT1",Opcode::fnEXT1);
    opcodes[EXT2] = new Opcode('\x83',"EXT2",Opcode::fnEXT2);
    opcodes[EXT4] = new Opcode('\x84',"EXT4",Opcode::fnEXT4);
    opcodes[TUPLE1] = new Opcode('\x85',"TUPLE1",Opcode::fnTUPLE1);
    opcodes[TUPLE2] = new Opcode('\x86',"TUPLE2",Opcode::fnTUPLE2);
    opcodes[TUPLE3] = new Opcode('\x87',"TUPLE3",Opcode::fnTUPLE3);
    opcodes[TRUE] = new Opcode('\x88',"TRUE",Opcode::fnTRUE);
    opcodes[FALSE] = new Opcode('\x89',"FALSE",Opcode::fnFALSE);
    opcodes[LONG1] = new Opcode('\x8a',"LONG1",Opcode::fnLONG1);
    opcodes[LONG4] = new Opcode('\x8b',"LONG4",Opcode::fnLONG4);
}
// These are Dummy Opcodes
int Opcode::fnGLOBAL1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnGLOBAL1\n");
	int len;
	StackItem *currentItem;
	currentItem=&theStack.top();
	char *ptr;
	char *buf;
	int isNewObj = 0;
	int lastMark;
	int j = 0;
#ifdef USE_OLD_MALLOC
	buf = (char*)malloc(sizeof(char)*200);
#else
	buf = (char*)malloc(sizeof(char)*200);
#endif
	ptr = buf;
	len = 0;
	while (it1 != str1.end() && *it1 != '\000')
        {
	    *ptr++ = *it1;
	    it1++;
	    len++;
	}
#ifdef USE_OLD_MALLOC
	currentItem->someString=(char*)malloc(sizeof(char)*(len+1));
#else
	currentItem->someString=(char*)malloc(sizeof(char)*(len+1));
#endif
	strcpy(currentItem->someString,buf);
	Utils::dprintf("- Global1: %s\n",buf);
	printf("- Global1: %s\n",buf);
	currentItem->lastMark = lastMark;
	currentItem->opcode = '~';
	currentItem->hasString = 0;
#ifdef USE_OLD_MALLOC
	free(buf);
#else
	free(buf);
#endif

	it1++;
	return 0;	
}
int Opcode::fnGLOBAL2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnGLOBAL2\n");
}
int Opcode::fnGLOBAL3(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnGLOBAL3\n");
}
// push special markobject on stack
// push special markobject on stack
int Opcode::fnMARK(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
/*
	it1++;
	// 2do: modify to not pop if nothing on stack
	std::string strMARK;
	int stackDepth = theStack.size();
	StackItem *theItem;
	theItem = &theStack.top();
	theItem->theMark = stackDepth;
	theItem->lastMark = stackDepth;
	theItem->opcode = '(';
*/
	Utils::dprintf("fnMARK\n");
        it1++;	
	return 0;
}
// every pickle ends with STOP
int Opcode::fnSTOP(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnSTOP\n");
	it1++;
	return 1;
}
// discard topmost stack item
int Opcode::fnPOP(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnPOP\n");
	it1++;
	//cout << "POP";
        //cout << endl;
	return 0;
}
// discard stack top through topmost markobject
int Opcode::fnPOP_MARK(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnPOP_MARK\n");
	//cout << "POP_MARK";
        //cout << endl;
	return 0;
}
// duplicate top stack item
int Opcode::fnDUP(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnDUP\n");
	//cout << "DUP";
        //cout << endl;
	return 0;
}
// push float object; decimal string argument
int Opcode::fnFLOAT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnFLOAT\n");
	//cout << "FLOAT";
	return 0;
}
int Opcode::fnINT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnINT\n");
	std::string strInt;
	it1++;
	while (*it1 != '|')
	{
		strInt.append(sizeof(char),*it1);
		it1++;
	}
	//cout << "INT";
	//cout << strInt;
        //cout << endl;
	return 0;
}
// push four-byte signed int
int Opcode::fnBININT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBININT\n");
	//cout << "BININT";
        //cout << endl;
	return 0;
}
// push 1-byte unsigned int
int Opcode::fnBININT1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBININT1\n");
	//cout << "BININT1";
        //cout << endl;
	return 0;
}
// push long; decimal string argument
int Opcode::fnLONG(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnLONG\n");
	//cout << "LONG";
        //cout << endl;
	return 0;
}
// push 2-byte unsigned int
int Opcode::fnBININT2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBININT2\n");
	//cout << "BININT2";
        //cout << endl;
	return 0;
}
// push None
int Opcode::fnNONE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnNONE\n");
	it1++;
	//cout << "NONE";
        //cout << endl;
	return 0;
}
// push persistent object; id is taken from string arg
int Opcode::fnPERSID(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnPERSID\n");
/*
	std::string pid;
	int countNewline = 0;
	it1++;
	int forward = 1;
	while (it1 != str1.end() && countNewline < 1)
        {
	     int item;
	     item = *it1;
	     if (*it1 == '|')
             {
		if (countNewline == 0)
		{
			((Opcode*)classPtr)->setPid(pid);
		}	
		countNewline++;
	     }
             else
             {
		if (countNewline == 0)
		{
			pid.append(sizeof(char),*it1);
		}
             }
	     it1++;
	     forward++; 
	}
        //cout << "PERSID";
	//cout << endl;
	
	if (forward != 0)
		return 1;
	else
		return 0;
*/
	return 1;
}
int Opcode::fnBINPERSID(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBINPERSID\n");
	//cout << "BINPERSID";
	//cout << endl;
	it1++;
	return 1;
}
// apply callable to argtuple, both on stack
// This is a bit of gobblelty gook.
// Because
// Essentially fnREDUCE takes the topmost element on the stack
// Be it a tuple or whatever
// And applies the earlier function to it
// Which is great, except in the first case of a pickle
// The earlier function is the undocumented see
// http://bugs.python.org/issue3816
// __newobj__ function: so if that is the case
// it means go create a new object
// since we are concentrating on a PHP output
// that means to me that whatever element is called by the tuple
// should have a matching PHP class that is available to the extension.

// we can pretty much ignore this for now
// because it is not until the 'b' BUILD opcode occurs
// that the values are set by setitem in the new object

int Opcode::fnREDUCE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnREDUCE\n");
/*
	StackItem *theItem,*tupleItem;
        theItem=&theStack.top();
	theStack.pop();
	tupleItem=&theStack.top();
	tupleItem->setAsObject();
*/
	
	it1++;
	return 0;
}
// push string; NL-terminated string argument
int Opcode::fnSTRING(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnSTRING\n");
	StackItem *theItem;
	theItem=&theStack.top();
	std::string strString;
	int countApostrophe = 0;
	int forward = 1;
	char *ptr;
	char *buf;
	int len;
#ifdef USE_OLD_MALLOC
	buf = (char*)malloc(sizeof(char)*200);
#else
	buf = (char*)malloc(sizeof(char)*200);
#endif
	ptr = buf;
	len = 0;
	it1++;
	while (it1 != str1.end() && *it1 != '\177' && *it1 != '\000')
        {
	     *ptr++ = *it1;
	     len++;
	     it1++;
	     forward++;
	}
	it1++;
#ifdef USE_OLD_MALLOC
	theItem->someString=(char*)malloc(sizeof(char)*(len+1));
#else
	theItem->someString=(char*)malloc(sizeof(char)*(len+1));
#endif
	theItem->hasString = 0;
	strcpy(theItem->someString,buf);
#ifdef USE_OLD_MALLOC
	free(buf);
#else
	free(buf);
#endif
	return 1;
}
// push string; counted binary string argument
int Opcode::fnBINSTRING(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBINSTRING\n");
	//cout << "BINSTRING";
	//cout << endl;
	return 0;
}
//  "     "   ;    "      "       "      " < 256 bytes
int Opcode::fnSHORT_BINSTRING(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnSHORT_BINSTRING\n");
	StackItem *theItem;
	theItem=&theStack.top();
	int intBinstring;
	std::string shortBinstring;
	// Next byte contains length
	// Of the binstring to read
	it1++;
	/*	
	if (it1 != str1.end() && *it1 != '\000')
	{
	    Utils::dprintf("fnSHORT_BINSTRING: capture length return 4 code\n");
	    return 4;
	}
	*/	
	theItem=&theStack.top();
	// Next byte contains length
	// Of the binstring to read
	intBinstring = *it1;
	Utils::dprintf("fnSHORT_BINSTRING: the String Length: %i\n",intBinstring);
	int intCountDown;
	intCountDown = intBinstring;	
	it1++;
	while (it1 != str1.end() && intCountDown > 0)
	{
	    shortBinstring.append(sizeof(char),*it1);
	    it1++;
	    intCountDown--;
	}
#ifdef USE_OLD_MALLOC
	theItem->someString=(char*)malloc(sizeof(char)*(intBinstring+1));
#else
	theItem->someString=(char*)malloc(sizeof(char)*(intBinstring+1));
#endif
	strcpy(theItem->someString,shortBinstring.c_str());
	/*
	2do: render non-printable characters
	Utils::dprintf("fnSHORT_BINSTRING: the String: %s\n",theItem->someString);
	*/
	theItem->hasString = 0;
	return 0;
}
// fnSHORT_BINSTRING1 for when it is continued onto the next line
int Opcode::fnSHORT_BINSTRING1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnSHORT_BINSTRING1\n");
	StackItem *theItem;
	theItem=&theStack.top();
	int intBinstring;
	std::string shortBinstring;
	// Next byte contains length
	// Of the binstring to read
	intBinstring = *it1;
	it1++;
	int intCountDown;
	intCountDown = intBinstring;	
	while (*it1 != '\000' && (it1 != str1.end() || intCountDown > 0))
	{
	    shortBinstring.append(sizeof(char),*it1);
	    it1++;
	    intCountDown--;
	}
#ifdef USE_OLD_MALLOC
	theItem->someString=(char*)malloc(sizeof(char)*(intBinstring+1));
#else
	theItem->someString=(char*)malloc(sizeof(char)*(intBinstring+1));
#endif
	theItem->hasString = 0;
	strcpy(theItem->someString,shortBinstring.c_str());
	Utils::dprintf("fnSHORT_BINSTRING1: the String: %s\n",theItem->someString);
	return 0;
}

// push Unicode string; raw-unicode-escaped'd argument
int Opcode::fnUNICODE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnUNICODE\n");
	//cout << "UNICODE";
	//cout << endl;
	return 0;
}
//   "     "       "  ; counted UTF-8 string argument
int Opcode::fnBINUNICODE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBINUNICODE\n");
	//cout << "BINUNICODE";
	//cout << endl;
	return 0;
}
// append stack top to list below it
int Opcode::fnAPPEND(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo) 
{
	Utils::dprintf("fnAPPEND\n");
	//cout << "APPEND";
	//cout << endl;
	return 0;
}
// call __setstate__ or __dict__.update()
int Opcode::fnBUILD(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBUILD\n");
	//cout << "BUILD";
	//cout << endl;
	it1++;
	return 0;
}
// push self.find_class(modname, name); 2 string args
// Except if module is copy_reg and name is __newobj__
// This is the new module constructor to be used
// by the REDUCE macro to turn a tuple into an object. 
int Opcode::fnGLOBAL(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnGLOBAL\n");
	int isNewObj = 0;
	StackItem *moduleItem,*nameItem,*currentItem;
	currentItem=&theStack.top();
	theStack.pop();
	int lastMark;
	lastMark = currentItem->lastMark;
	std::string state;
	std::string module;
	std::string name;
	int countNewline = 0;
	int forward = 1;
	//it1++;
#ifdef USE_OLD_MALLOC
	moduleItem = (StackItem*)malloc(sizeof(StackItem));
#else
	moduleItem = (StackItem*)malloc(sizeof(StackItem));
#endif
	char *ptr;
	char *buf;
#ifdef USE_OLD_MALLOC
	buf = (char*)malloc(sizeof(char)*200);
#else
	buf = (char*)malloc(sizeof(char)*200);
#endif
	ptr = buf;
	int len;
	len = 0;
	while (it1 < str1.end() && *it1 != '\177' && *it1 != '\000')
        {
	     *ptr++ = *it1;
	     len++;
	     it1++;
	     forward++;
	}
	// Push new Class onto the Stack
#ifdef USE_OLD_MALLOC
	char* stringPtr=(char*)malloc(sizeof(char)*(len+1));
	moduleItem->someString = stringPtr;
#else
	moduleItem->someString=(char*)malloc(sizeof(char)*(len+1));
#endif
	moduleItem->hasString = 0;
	moduleItem->lastMark = lastMark;
	Utils::dprintf("- Global1: %s\n",buf);
	printf("- Global1: %s\n",buf);
	strcpy(moduleItem->someString,buf);
	int retval;
	retval = 3;
	if (0 == strcmp("copy_reg",buf))
	{
	    moduleItem->opcode='*';
	    isNewObj = 1;
	    retval = 5;
	}
        else
        {
	    moduleItem->opcode = '!';
	}
#ifdef USE_OLD_MALLOC
	free(buf);
#else
	free(buf);
#endif
	theStack.push(*moduleItem);
	return retval;
}
// build a dict from stack Stack
int Opcode::fnDICT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnDICT\n");
	StackItem *theItem,*tupleItem;
	theItem=&theStack.top();
	theItem->initializeDict();
	theItem->opcode='d';
        it1++;
        int forward = 1;
	if (forward != 0)
		return 1;
	else
		return 0;
}
// push empty dict
int Opcode::fnEMPTY_DICT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnEMPTY_DICT\n");
	StackItem *theItem,*tupleItem;
	theItem=&theStack.top();
	theItem->initializeDict();
	theItem->opcode='d';
        it1++;
	return 0;
}
// extend list on stack by topmost stack slice
int Opcode::fnAPPENDS(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnAPPENDS\n");
	//cout << "APPENDS";
	//cout << endl;
	return 0;
}
// push item from memo on stack; index is string arg
int Opcode::fnGET(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnGET\n");
	std::string strPut;
	int getLevel;
	char theInt[10];
	int countNewline = 0;
	int forward = 0;
	while (it1 < str1.end())
        {
	     int item;
	     item = *it1;
	     strPut.append(sizeof(char),*it1);
	     it1++;
	     forward++;
	}
	sprintf(theInt,"%s",strPut.c_str());
	// pop the GET opcode from the stack
	getLevel = atoi(theInt);
	if (getLevel > 0)
		getLevel--;
	theStack.pop();
	int stackDepth = theStack.size();
	StackItem *memoItem;

	int memoSize;
	memoSize = theMemo.size();
	int matchk = memoSize - getLevel - 6;
	for (int k=0; k<memoSize; k++ )
	{
	     int result;
	     if (k == matchk)
	     {
	         StackItem memoItem = theMemo[k];
	         theStack.push(memoItem);
		 break;
	     }
	}

	
	return 1;
}
//   "    "    "    "   "   "  ;   "    " 1-byte arg
int Opcode::fnBINGET(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBINGET\n");
	//cout << "BINGET";
	//cout << endl;
	it1++;
	it1++;
	return 0;
}
// build & push class instance
int Opcode::fnINST(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo) 
{
	Utils::dprintf("fnINST\n");
/*
	std::string module;
	std::string name;
	int countNewline = 0;
	it1++;
	int forward = 1;
	while (it1 != str1.end() && countNewline < 2)
        {
	     int item;
	     item = *it1;
	     if (*it1 == '|')
             {
		if (countNewline == 0)
		{
			((Opcode*)classPtr)->setModule(module);
		}	
		else if (countNewline == 1)
		{
			((Opcode*)classPtr)->setName(name);
		}
		countNewline++;
	     }
             else
             {
		if (countNewline == 0)
		{
			module.append(sizeof(char),*it1);
		}
		else if (countNewline == 1)
		{
			name.append(sizeof(char),*it1);
		}
             }
	     it1++;
	     forward++;
	}
        //cout << "INST";
	//cout << endl;
	
	if (forward != 0)
		return 1;
	else
		return 0;
*/
	return 1;
}
// push item from memo on stack; index is 4-byte arg
int Opcode::fnLONG_BINGET(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnLONG_BINGET\n");
	//cout << "LONG_BINGET";
	//cout << endl;
	return 0;
}
// build list from topmost stack Stack
int Opcode::fnLIST(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnLIST\n");
	//cout << "LIST";
	//cout << endl;
	return 0;
}
// push empty list
int Opcode::fnEMPTY_LIST(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnEMPTY_LIST\n");
	//cout << "EMPTY_LIST";
	//cout << endl;
	return 0;
}
// build & push class instance
int Opcode::fnOBJ(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo) 
{
	Utils::dprintf("fnOBJ\n");
	//cout << "OBJ";
	//cout << endl;
	return 0;
}
// store stack top in memo; index is string arg
int Opcode::fnPUT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)    
{
	Utils::dprintf("fnPUT\n");
	// I don't need to store things in the memo.
	StackItem *newItem;
	std::string strPut;
	char theInt[10];
	int countNewline = 0;
	while (it1 < str1.end() && *it1 != '\000')
        {
	     int item;
	     item = *it1;
	     strPut.append(sizeof(char),*it1);
	     it1++;
	}
	sprintf(theInt,"%s",strPut.c_str());
	// Push new Class onto the Stack
	StackItem *putItem,*prevItem;
	putItem= &theStack.top();
	putItem->someInt = atoi(theInt);
	// Find current Stack Depth
	
	// POP THE STACK, because PUT goes into the Memo
	// Memo is the static stack in the stackitem structure
	// What opcode also uses Memo? setitem
	theStack.pop();
	prevItem = &theStack.top();
        theMemo.push_back(*prevItem);

#ifdef USE_OLD_MALLOC
	newItem = (StackItem*)malloc(sizeof(StackItem));
#else
	newItem = (StackItem*)malloc(sizeof(StackItem));
#endif
	newItem->opcode = 'p';
	newItem->someInt = atoi(theInt);

	//theStack.push(*newItem);
	
	return 1;
}
//   "     "    "   "   " ;   "    " 1-byte arg
int Opcode::fnBINPUT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBINPUT\n");
	StackItem *theItem;
	// This is one byte long
	// As said above ... DUH
	std::string strBinput;
	int getValue;
	char theInt[10];
	int countNewline = 0;
	int item;
	theItem = &theStack.top();
	it1++;
	getValue = *it1;
	Utils::dprintf("- BINPUT: %i\n",getValue);
	theItem->someInt = getValue;
	it1++;

	return 0;
}
//   "     "    "   "   " ;   "    " 4-byte arg
int Opcode::fnLONG_BINPUT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnLONG_BINPUT\n");
	//cout << "LONG_BINPUT";
	//cout << endl;
	return 0;
}
// add key+value pair to dict
int Opcode::fnSETITEM(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnSETITEM\n");
	it1++;
	return 0;
/*
	char *ptrKey;
	char *bufKey;
	int lenKey;
#ifdef USE_OLD_MALLOC
	bufKey = (char*)malloc(sizeof(char)*200);
#else
	bufKey = (char*)malloc(sizeof(char)*200);
#endif
	ptrKey = bufKey;
	char bufValue[201];
	char *ptrValue;
	int lenValue;

	StackItem *theItem,*valueItem,*keyItem,*someItem,*newItem;
	int forward;
	forward = 1;
	it1++;


	// Every pop overwrites the last: it is just one address
	// So we will have to save values.
	int onTarget = 1;
	theItem = &theStack.top();
	int lastMark = theItem->lastMark;
	valueItem = &theStack.top();
	ptrValue=bufValue;
	//strcpy(ptrValue,valueItem->someString);
	theStack.pop();
	keyItem = &theStack.top();
	if (keyItem->someString == 0)
	{
	    strcpy(ptrKey,"BLANK_KEY");
	}
	else
	{
	    strcpy(ptrKey,keyItem->someString);
	}
	theStack.pop();
	valueItem = &theStack.top();
	if (valueItem->someString == 0)
	{
	    strcpy(ptrValue,"BLANK_VALUE");
	}
	else
	{
	    strcpy(ptrValue,valueItem->someString);
	}
	theStack.pop();
	theStack.pop();
	theStack.pop();
#ifdef USE_OLD_MALLOC
	newItem = (StackItem*)malloc(sizeof(StackItem));
#else
	newItem = (StackItem*)malloc(sizeof(StackItem));
#endif
	newItem->opcode = 'd';
	newItem->initializeDict();	
	int len = 50;
#ifdef USE_OLD_MALLOC
	newItem->someString=(char*)malloc(sizeof(char)*(len+1));
#else
	newItem->someString=(char*)malloc(sizeof(char)*(len+1));
#endif
	newItem->hasString = 0;
	strcpy(newItem->someString,"NEWDICT");
	newItem->lastMark = lastMark;
	newItem->insertDictPair(ptrKey,ptrValue);
	theStack.push(*newItem);
#ifdef USE_OLD_MALLOC
	free(bufKey);
#else
	free(bufKey);
#endif

        return 0;
*/
}
// build tuple from topmost stack Stack
int Opcode::fnTUPLE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnTUPLE\n");
	// Everything since the last mark becomes the tuple
	// What is a tuple?
	StackItem *theItem,*tupleItem;
	int len;
	int index;
	char *moduleName;
	char *className;
	char theOpcode;
	
	do
	{
	    theStack.pop();
	    theItem=&theStack.top();
	    theOpcode = theItem->opcode;
	    // harvest module name
	    if (theOpcode == '!')
            {
		moduleName=theItem->someString;
	    }
	    // harvest class name
            if (theOpcode == '~')
            {
		className=theItem->someString;
            }
	} while (theOpcode != '(');


	// What we did here was to pull the top of the stack off,
	// And assume that it was a Tuple.  It was not a Tuple!
	tupleItem = &theStack.top();

	tupleItem->initializeTuple();

	tupleItem->setModuleName(moduleName);
	tupleItem->setClassName(className);
	tupleItem->setIndex(0);

	tupleItem->opcode = 't';

	// For Now We Note that TUPLE exists!
	it1++;
	return 0;
}
// push empty tuple
int Opcode::fnEMPTY_TUPLE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnEMPTY_TUPLE\n");
	//cout << "EMPTY_TUPLE";
	//cout << endl;
	return 0;
}
// modify dict by adding topmost key+value pairs
int Opcode::fnSETITEMS(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnSETITEMS\n");
	//cout << "SETITEMS";
	//cout << endl;
	it1++;
	int getValue = *it1;
	Utils::dprintf("- SETITEMS: %i\n",getValue);
	/*
	while (getValue > 0)
	{
		it1++;
		getValue--;
	}	
	*/
	it1++;
	return 0;
}
// push float; arg is 8-byte float encoding
int Opcode::fnBINFLOAT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnBINFLOAT\n");
	//cout << "BINFLOAT";
	it1++;
	it1++;
	it1++;
	it1++;
	it1++;
	it1++;
	it1++;
	it1++;
	//cout << endl;
	return 0;
}
// identify pickle protocol
int Opcode::fnPROTO(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnPROTO");
	//cout << "PROTO";
	//cout << endl;
	return 0;
}
// build object by applying cls.__new__ to argtuple
int Opcode::fnNEWOBJ(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnNEWOBJ");
	//cout << "NEWOBJ";
	//cout << endl;
	return 0;
}
// push object from extension registry; 1-byte index
int Opcode::fnEXT1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo) 
{
	Utils::dprintf("fnEXT1");
	//cout << "EXT1";
	//cout << endl;
	return 0;
}
// ditto, but 2-byte index
int Opcode::fnEXT2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnEXT2");
	//cout << "EXT2";
	//cout << endl;
	return 0;
}
// ditto, but 4-byte index
int Opcode::fnEXT4(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnEXT4");
	//cout << "EXT4";
	//cout << endl;
	return 0;
}
// build 1-tuple from stack top
int Opcode::fnTUPLE1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnTUPLE1");
	//cout << "TUPLE1";
	//cout << endl;
	return 0;
}
// build 2-tuple from two topmost stack Stack
int Opcode::fnTUPLE2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnTUPLE2");
	//cout << "TUPLE2";
	//cout << endl;
	return 0;
}
// build 3-tuple from three topmost stack Stack
int Opcode::fnTUPLE3(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnTUPLE3");
	//cout << "TUPLE3";
	//cout << endl;
	return 0;
}
// push True
int Opcode::fnTRUE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnTRUE");
	//cout << "TRUE";
	//cout << endl;
	return 0;
}
// push False
int Opcode::fnFALSE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnFALSE");
	//cout << "FALSE";
	//cout << endl;
	return 0;
}
// push long from < 256 bytes
int Opcode::fnLONG1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnLONG1");
	//cout << "LONG1";
	//cout << endl;
	return 0;
}
// push really big long
int Opcode::fnLONG4(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	Utils::dprintf("fnLONG4");
	//cout << "LONG4";
	//cout << endl;
	return 0;
}
