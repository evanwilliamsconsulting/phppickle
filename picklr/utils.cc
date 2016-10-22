#include "utils.h"

void utils::dprintf(char *format, ...)
{
	debugLevel = this->debugLevel;
        va_list args;
        va_start(args, format);
        if(debugLevel == 1) {
                printf(format, args);
        }
        va_end(args);
}
