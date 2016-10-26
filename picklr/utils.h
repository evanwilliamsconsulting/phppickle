#include "basics.h"

// http://stackoverflow.com/questions/15240/how-do-you-create-a-debug-only-function-that-takes-a-variable-argument-list-lik

using namespace std;

class Utils {
	public:
		static int debugLevel;
		Utils(int debugLevel);
		static void dprintf(const char *format, ...);
};
