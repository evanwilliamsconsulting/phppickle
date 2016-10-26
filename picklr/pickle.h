#include "basics.h"
#include "utils.h"
#include "stackitem.h"

using namespace std;

enum pycodes {
  MARK,
  STOP,
  POP,
  POP_MARK,
  DUP,
  FLOAT,
  INT,
  BININT,
  BININT2,
  LLONG,
  NONE,
  PERSID,
  BINPERSID,
  REDUCE,
  STRING,
  BINSTRING,
  SHORT_BINSTRING,
  SHORT_BINSTRING1,
  UNICODE,
  BINUNICODE,
  APPEND,  
  BUILD,  
  GLOBAL,
  DICT,
  EMPTY_DICT,
  APPENDS,
  GET,    
  BINGET,
  INST, 
  LONG_BINGET,
  LIST,     
  EMPTY_LIST,
  OBJ,     
  PUT,    
  BINPUT,
  LONG_BINPUT,
  SETITEM,  
  TUPLE,   
  EMPTY_TUPLE,
  SETITEMS, 
  BINFLOAT,
  PROTO,  
  NEWOBJ,
  EXT1, 
  EXT2,
  EXT4,
  TUPLE1,
  TUPLE2,
  TUPLE3,
  TRUE,
  FALSE,
  LONG1,
  LONG4,
  GLOBAL1,
  GLOBAL2,
  GLOBAL3,
  OPCODE_COUNT
};


using namespace std;

	class Opcode {
		typedef int (*fn)(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
		protected:
		    std::string module;
		    std::string name;
		    std::string pid;
		public:
		    char opcode;
		    char desc[25];
		    fn opfunc;
		    Opcode(char opcodeChar,const char *desc,fn funct);
		    char *getDescription();
		    void setModule(std::string inModule);
		    void setName(std::string inName); 
		    void setPid(std::string inPid);
		    // Dummy Opcodes
		    static int fnGLOBAL1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
		    static int fnGLOBAL2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
		    static int fnGLOBAL3(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
		    static int fnSTOP(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
	    static int fnMARK(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnPOP(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnPOP_MARK(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnDUP(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnFLOAT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnINT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnBININT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnBININT1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnLONG(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnBININT2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnNONE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnPERSID(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnBINPERSID(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnREDUCE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnSTRING(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnBINSTRING(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnSHORT_BINSTRING(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnSHORT_BINSTRING1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnUNICODE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnBINUNICODE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnAPPEND(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);  
            static int fnBUILD(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);  
            static int fnGLOBAL(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnDICT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnEMPTY_DICT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnAPPENDS(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnGET(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);    
            static int fnBINGET(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnINST(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo); 
            static int fnLONG_BINGET(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnLIST(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);     
            static int fnEMPTY_LIST(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnOBJ(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);     
            static int fnPUT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);    
            static int fnBINPUT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnLONG_BINPUT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnSETITEM(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);  
            static int fnTUPLE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);   
            static int fnEMPTY_TUPLE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnSETITEMS(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo); 
            static int fnBINFLOAT(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnPROTO(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);  
            static int fnNEWOBJ(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnEXT1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo); 
            static int fnEXT2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnEXT4(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnTUPLE1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnTUPLE2(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnTUPLE3(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnTRUE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnFALSE(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnLONG1(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
            static int fnLONG4(ifstream &instream,std::string str1,std::string::iterator &it1,StackItem &theStackItem,stack<StackItem>& theStack,vector<StackItem>& theMemo);
};

class Pickle {
    public:
        Pickle();
	Opcode *opcodes[OPCODE_COUNT];
};
