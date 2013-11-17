#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdarg>
#include "Types.h"

namespace novaengine
{

enum E_LOG_LEVEL
{
    ELL_ALL               = 0x0,
    ELL_DEEP_DEBUG        = 0x1,
    ELL_DEBUG_ENGINE      = 0x2,
    ELL_DEBUG_APP         = 0x3,
    ELL_INFO              = 0x4,
    ELL_WARNING           = 0x5,
    ELL_ERROR             = 0x6,
    ELL_FATAL_ERROR       = 0x7,
    ELL_NONE              = 0xf,
};

#ifndef GD_MIN_LOG_LEVEL
#ifdef DEBUG
#define GD_MIN_LOG_LEVEL ELL_DEEP_DEBUG
#else
#define GD_MIN_LOG_LEVEL ELL_INFO
#endif
#endif

namespace io
{
class Log
{
public:
    /// \brief input - println("a") output - "a"
    static void print(core::cstring str,s32 log_level = ELL_INFO)
    {
        if(log_level < GD_MIN_LOG_LEVEL)
            return;

        std::cout << str;
    }
    /// \brief input - println("a","b") output - "a: b "
    static void print(core::cstring str,core::cstring param,s32 log_level = ELL_INFO)
    {
        if(log_level < GD_MIN_LOG_LEVEL)
            return;

        std::cout << str << ": " << param;
    }
    /// \brief input - println("a","b","c") output - "a: b [c] "
    static void print(core::cstring str,core::cstring param,core::cstring descr,s32 log_level = ELL_INFO)
    {
        if(log_level < GD_MIN_LOG_LEVEL)
            return;

        std::cout << str << ": " << param << " [" << descr << "] ";
    }
    /// \brief input - println("a") output - "a \n"
    static void println(core::cstring str,s32 log_level = ELL_INFO)
    {
        if(log_level < GD_MIN_LOG_LEVEL)
            return;

        print(str,log_level);
        std::cout << std::endl;
    }
    /// \brief input - println("a","b") output - "a: b \n"
    static void println(core::cstring str,core::cstring param,s32 log_level = ELL_INFO)
    {
        if(log_level < GD_MIN_LOG_LEVEL)
            return;

        print(str,param,log_level);
        std::cout << std::endl;
    }
    /// \brief input - println("a","b","c") output - "a: b [c] \n"
    static void println(core::cstring str,core::cstring param,core::cstring descr,s32 log_level = ELL_INFO)
    {
        if(log_level < GD_MIN_LOG_LEVEL)
            return;

        print(str,param,descr,log_level);
        std::cout << std::endl;
    }
};
}
}
#endif // LOGGER_H
