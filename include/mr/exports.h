
#ifndef MR_EXPORTS_H
#define MR_EXPORTS_H

#ifdef SHARED_EXPORTS_BUILT_AS_STATIC
#  define MR_EXPORTS
#  define MR_CORE_NO_EXPORT
#else
#  ifndef MR_EXPORTS
#    ifdef mr_core_EXPORTS
/* We are building this library */
#      define MR_EXPORTS __declspec(dllexport)
#    else
/* We are using this library */
#      define MR_EXPORTS __declspec(dllimport)
#    endif
#  endif

#  ifndef MR_CORE_NO_EXPORT
#    define MR_CORE_NO_EXPORT 
#  endif
#endif

#ifndef MR_CORE_DEPRECATED
#  define MR_CORE_DEPRECATED __declspec(deprecated)
#endif

#ifndef MR_CORE_DEPRECATED_EXPORT
#  define MR_CORE_DEPRECATED_EXPORT MR_EXPORTS MR_CORE_DEPRECATED
#endif

#ifndef MR_CORE_DEPRECATED_NO_EXPORT
#  define MR_CORE_DEPRECATED_NO_EXPORT MR_CORE_NO_EXPORT MR_CORE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MR_CORE_NO_DEPRECATED
#    define MR_CORE_NO_DEPRECATED
#  endif
#endif

#endif
