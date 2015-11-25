#pragma once

/// OS detection
#define NPP_TARGET_WIN64 0
#define NPP_TARGET_WIN 0
#define NPP_TARGET_WIN32 0
#define NPP_TARGET_IPHONE 0
#define NPP_TARGET_IOS 0
#define NPP_TARGET_IOS_SIM 0
#define NPP_TARGET_IOS_SIMULATOR 0
#define NPP_TARGET_IPHONE_SIM 0
#define NPP_TARGET_IPHONE_SIMULATOR 0
#define NPP_TARGET_APPLE 0
#define NPP_TARGET_OSX 0
#define NPP_TARGET_ANDROID 0
#define NPP_TARGET_UNIX 0
#define NPP_TARGET_LINUX 0
#define NPP_TARGET_BSD 0
#define NPP_TARGET_UNKNOWN 0

#ifdef _WIN64
  #undef NPP_TARGET_WIN64
  #undef NPP_TARGET_WIN
  #define NPP_TARGET_WIN64 1
  #define NPP_TARGET_WIN 1
#elif _WIN32
  #undef NPP_TARGET_WIN32
  #undef NPP_TARGET_WIN
  #define NPP_TARGET_WIN32 1
  #define NPP_TARGET_WIN 1
#elif __APPLE__
  #include "TargetConditionals.h"
  #if NPP_TARGET_OS_IPHONE
    #undef NPP_TARGET_IPHONE
    #undef NPP_TARGET_IOS
    #define NPP_TARGET_IPHONE 1
    #define NPP_TARGET_IOS 1
  #elif NPP_TARGET_IPHONE_SIMULATOR
    #undef NPP_TARGET_IPHONE
    #undef NPP_TARGET_IOS
    #undef NPP_TARGET_IOS_SIM
    #undef NPP_TARGET_IOS_SIMULATOR
    #undef NPP_TARGET_IPHONE_SIM
    #undef NPP_TARGET_IPHONE_SIMULATOR
    #define NPP_TARGET_IPHONE 1
    #define NPP_TARGET_IOS 1
    #define NPP_TARGET_IOS_SIM 1
    #define NPP_TARGET_IOS_SIMULATOR 1
    #define NPP_TARGET_IPHONE_SIM 1
    #define NPP_TARGET_IPHONE_SIMULATOR 1
  #elif NPP_TARGET_OS_MAC
    #undef NPP_TARGET_APPLE
    #undef NPP_TARGET_OSX
    #define NPP_TARGET_APPLE 1
    #define NPP_TARGET_OSX 1
  #endif
#elif __ANDROID__
  #undef NPP_TARGET_ANDROID
  #define NPP_TARGET_ANDROID 1
#elif __unix || __unix__
  #undef NPP_TARGET_UNIX
  #define NPP_TARGET_UNIX 1
  #if __linux
    #undef NPP_TARGET_LINUX
    #define NPP_TARGET_LINUX 1
  #else
    #include <sys/param.h>
    #if (defined(BSD) && (BSD >= 199103))`
      #undef NPP_TARGET_BSD
      #define NPP_TARGET_BSD 1
    #endif
  #endif
#else
  #undef NPP_TARGET_UNKNOWN
  #define NPP_TARGET_UNKNOWN 1
#endif
