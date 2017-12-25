#ifndef TENSORFLOW_CONTRIB_LITE_C_TENSORFLOW_LITE_MACRO_H_
#define TENSORFLOW_CONTRIB_LITE_C_TENSORFLOW_LITE_MACRO_H_

#ifdef SWIG
#define TFL_CAPI_EXPORT
#else
#if defined(COMPILER_MSVC)
#ifdef TF_COMPILE_LIBRARY
#define TFL_CAPI_EXPORT __declspec(dllexport)
#else
#define TFL_CAPI_EXPORT __declspec(dllimport)
#endif  // TF_COMPILE_LIBRARY
#else
#define TFL_CAPI_EXPORT __attribute__((visibility("default")))
#endif  // COMPILER_MSVC
#endif  // SWIG

#endif // TENSORFLOW_CONTRIB_LITE_C_TENSORFLOW_LITE_MACRO_H_