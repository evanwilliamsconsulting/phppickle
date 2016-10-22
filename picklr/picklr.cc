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

#include "phpzope.h"


char* getCmdOption(char ** begin, char ** end, const std::string & options)
{
	char ** itr = std::find(begin,end,options);
	if ( itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char ** begin, char ** end, const std::string& option)
{
	return std::find(begin, end , option) != end;
}

int main(int argc, char *argv[])
{
	PHPZope *myzoper = new PHPZope();
	if (cmdOptionExists(argv, argv+argc, "-h"))
	{
		cout << "help";
	}

	char * filename	= getCmdOption(argv, argv + argc, "-f");

	if (filename)
	{
		myzoper->readPickle(filename);
	        stack<StackItem> theStack = myzoper->retrieveCurrentStack();
	        vector<StackItem> theMemo = myzoper->retrieveCurrentMemo();
	        myzoper->readFile(theStack,theMemo);

		StackItem topStackItem = theStack.top();

		int stackDepth = theStack.size();
	
		cout << "Results:\n";

		while (stackDepth > 1)
		{
			cout << "Stack Item:\n";
			cout <<  topStackItem.opcode;
			cout << ": ";
			//cout << topStackItem.someString;
			//cout << "\n";
			theStack.pop();
			topStackItem = theStack.top();
			stackDepth--;
		}
	}

	return 0;
}
