#ifndef COMPILECONFIG_H
#define COMPILECONFIG_H

#ifdef GD_PLATFORM_WINDOWS
    #ifndef GD_WINDOW_WIN32
        #error ERROR Please select window manager class
    #endif
#endif

#endif // COMPILECONFIG_H
