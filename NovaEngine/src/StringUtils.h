#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "Types.h"

namespace novaengine
{
    namespace utils
    {
        core::cstring to_string(s32 num)
        {
            return core::cstring(itoa(num,0,0));
        }
    }
}

#endif // STRINGUTILS_H
