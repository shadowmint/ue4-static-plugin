#pragma once

/// OS detection
#define TARGET_WIN64 0
#define TARGET_WIN 0
#define TARGET_WIN32 0
#define TARGET_IPHONE 0
#define TARGET_IOS 0
#define TARGET_IOS_SIM 0
#define TARGET_IOS_SIMULATOR 0
#define TARGET_IPHONE_SIM 0
#define TARGET_IPHONE_SIMULATOR 0
#define TARGET_APPLE 0
#define TARGET_OSX 0
#define TARGET_ANDROID 0
#define TARGET_UNIX 0
#define TARGET_LINUX 0
#define TARGET_BSD 0
#define TARGET_UNKNOWN 0

#ifdef _WIN64
  #undef TARGET_WIN64
  #undef TARGET_WIN
  #define TARGET_WIN64 1
  #define TARGET_WIN 1
#elif _WIN32
  #undef TARGET_WIN32
  #undef TARGET_WIN
  #define TARGET_WIN32 1
  #define TARGET_WIN 1
#elif __APPLE__
  #include "TargetConditionals.h"
  #if TARGET_OS_IPHONE
    #undef TARGET_IPHONE
    #undef TARGET_IOS
    #define TARGET_IPHONE 1
    #define TARGET_IOS 1
  #elif TARGET_IPHONE_SIMULATOR
    #undef TARGET_IPHONE
    #undef TARGET_IOS
    #undef TARGET_IOS_SIM
    #undef TARGET_IOS_SIMULATOR
    #undef TARGET_IPHONE_SIM
    #undef TARGET_IPHONE_SIMULATOR
    #define TARGET_IPHONE 1
    #define TARGET_IOS 1
    #define TARGET_IOS_SIM 1
    #define TARGET_IOS_SIMULATOR 1
    #define TARGET_IPHONE_SIM 1
    #define TARGET_IPHONE_SIMULATOR 1
  #elif TARGET_OS_MAC
    #undef TARGET_APPLE
    #undef TARGET_OSX
    #define TARGET_APPLE 1
    #define TARGET_OSX 1
  #endif
#elif __ANDROID__
  #undef TARGET_ANDROID
  #define TARGET_ANDROID 1
#elif __unix || __unix__
  #undef TARGET_UNIX
  #define TARGET_UNIX 1
  #if __linux
    #undef TARGET_LINUX
    #define TARGET_LINUX 1
  #else
    #include <sys/param.h>
    #if (defined(BSD) && (BSD >= 199103))`
      #undef TARGET_BSD
      #define TARGET_BSD 1
    #endif
  #endif
#else
  #undef TARGET_UNKNOWN
  #define TARGET_UNKNOWN 1
#endif
