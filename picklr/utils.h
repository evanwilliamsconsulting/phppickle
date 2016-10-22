#include "basics.h"

// http://stackoverflow.com/questions/15240/how-do-you-create-a-debug-only-function-that-takes-a-variable-argument-list-lik

using namespace std;

class Utils {
	protected:
		int debugLevel;
	public:
		Utils(int debugLevel=0);
		dprintf(char *format, ...);
};
