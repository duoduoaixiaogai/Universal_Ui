#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef NOT_EXPORT
  #if defined(BUILD_LIB)
    #define EXPORT __declspec(dllexport)
  #else
    #define EXPORT __declspec(dllimport)
  #endif
#else
  #define EXPORT
#endif

#endif // GLOBAL_H
