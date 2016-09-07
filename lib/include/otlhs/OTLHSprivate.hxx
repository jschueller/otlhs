
#ifndef OTLHS_PRIVATE_HXX
#define OTLHS_PRIVATE_HXX

/* From http://gcc.gnu.org/wiki/Visibility */
/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
#define OTLHS_HELPER_DLL_IMPORT __declspec(dllimport)
#define OTLHS_HELPER_DLL_EXPORT __declspec(dllexport)
#define OTLHS_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define OTLHS_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define OTLHS_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define OTLHS_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define OTLHS_HELPER_DLL_IMPORT
#define OTLHS_HELPER_DLL_EXPORT
#define OTLHS_HELPER_DLL_LOCAL
#endif
#endif

/* Now we use the generic helper definitions above to define OTLHS_API and OTLHS_LOCAL.
 * OTLHS_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * OTLHS_LOCAL is used for non-api symbols. */

#ifndef OTLHS_STATIC /* defined if OT is compiled as a DLL */
#ifdef OTLHS_DLL_EXPORTS /* defined if we are building the OT DLL (instead of using it) */
#define OTLHS_API OTLHS_HELPER_DLL_EXPORT
#else
#define OTLHS_API OTLHS_HELPER_DLL_IMPORT
#endif /* OTLHS_DLL_EXPORTS */
#define OTLHS_LOCAL OTLHS_HELPER_DLL_LOCAL
#else /* OTLHS_STATIC is defined: this means OT is a static lib. */
#define OTLHS_API
#define OTLHS_LOCAL
#endif /* !OTLHS_STATIC */


#endif // OTLHS_PRIVATE_HXX

