/* Standard C++ headers */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>
#include <fstream>
#include <regex>
#include <vector>

#include "pickle.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

using namespace std;
//  File Name : pycodes.hpp    Purpose : Python Opcodes
// Pickle opcodes.  See ZODB pickle.py for extensive docs.  The listing
// here is in kind-of alphabetical order of 1-character pickle code.
// pickletools groups them by purpose.

//  Basic PHPZOPE Class
class PHPZope {
public:
    PHPZope();
    ~PHPZope();
    int returnValue();
    int readPickle(char *strFile);
    int setPickle(char *thePickle);
    void readFile(stack<StackItem>& theStack,vector<StackItem>& theMemo);
    char* returnPickleString(stack<StackItem>& theStack,vector<StackItem>& theMemo);
    int retrieve_state(ifstream& infile,string& state2,stack<StackItem>& theStack,int& lastMark,vector<StackItem>& theMemo);
    char* returnModuleName();
    char* returnKlassName();
    stack<StackItem> currentStack;
    vector<StackItem> theMemo;
    int retrieveStackDepth();
    stack<StackItem>& retrieveCurrentStack();
    vector<StackItem>& retrieveCurrentMemo();
    int getMemoSize();
    std::string theString;
private:
    char filename[100];
    char buffer[1000];
    int continueSHORT_BINSTRING;
    int memoSize;
};
