#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

int Utils::debugLevel = 1;

Utils::Utils(int debugLvl)
{
	Utils::debugLevel=debugLvl;
}
void Utils::dprintf(const char *format, ...)
{
	int debugLvl = Utils::debugLevel;
        va_list args;
        va_start(args, format);
        if(debugLvl == 1) {
                vprintf(format, args);
        }
        va_end(args);
}
