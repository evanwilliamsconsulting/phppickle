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

#ifndef PHPZOPE_H
#define PHPZOPE_H

#define PHPZOPE_EXTNAME  "phpzope"
#define PHPZOPE_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include "php.h"


extern zend_module_entry phpzope_module_entry;
#define phpext_phpzope_ptr &phpzope_module_entry;

#endif /* PHPZOPE_H */

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
    char* returnPickleFile(stack<StackItem>& theStack,vector<StackItem>& theMemo);
    int retrieve_state(ifstream& infile,string& state2,stack<StackItem>& theStack,int& lastMark,vector<StackItem>& theMemo);
    char* returnModuleName();
    char* returnKlassName();
    stack<StackItem> currentStack;
    vector<StackItem> theMemo;
    int retrieveStackDepth();
    stack<StackItem>& retrieveCurrentStack();
    vector<StackItem>& retrieveCurrentMemo();
    int getMemoSize();
private:
    char filename[100];
    char buffer[1000];
    int continueSHORT_BINSTRING;
    int memoSize;
};

zend_object_handlers phpzope_object_handlers;

struct phpzope_object {
    zend_object std;
    class PHPZope *phpzope;
};
zend_class_entry *phpzope_ce;
