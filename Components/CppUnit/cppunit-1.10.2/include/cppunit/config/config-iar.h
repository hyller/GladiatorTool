#ifndef _INCLUDE_CPPUNIT_CONFIG_RVDK_H
#define _INCLUDE_CPPUNIT_CONFIG_RVDK_H 1

//#undef CPPUNIT_WITHOUT_CPP_STREAM	
#define CPPUNIT_WITHOUT_CPP_STREAM	1 // Pas ostream, sstream, cout <<, cerr << ...
//#define	CPPUNIT_WITHOUT_C_OUTPUT	1 // Pas de printf ...
#undef CPPUNIT_WITHOUT_C_OUTPUT

#define CPPUNIT_LIGHT_VERSION	1

/*
#ifdef __cplusplus
extern "C" {
  #pragma import(__use_no_semihosting_swi)
}
#endif
*/

#define CPPUNIT_NO_TESTPLUGIN	1

#define HAVE_CMATH 1
 
/* include/cppunit/config-iar.h. Manually adapted from 
   include/cppunit/config-rvdk.h Manually adapted from 
   include/cppunit/config-msvc6.h */

/* define to 1 if the compiler implements namespaces */
#ifdef CPPUNIT_HAVE_NAMESPACES 
#undef CPPUNIT_HAVE_NAMESPACES  //ALI
#endif

/* define if library uses std::string::compare(string,pos,n) */
#ifdef CPPUNIT_FUNC_STRING_COMPARE_STRING_FIRST 
#undef CPPUNIT_FUNC_STRING_COMPARE_STRING_FIRST
#endif

/* Define if you have the <dlfcn.h> header file. */
#ifdef CPPUNIT_HAVE_DLFCN_H 
#undef CPPUNIT_HAVE_DLFCN_H 
#endif


/* define if the compiler supports Run-Time Type Identification */
#ifndef CPPUNIT_HAVE_RTTI 
#define CPPUNIT_HAVE_RTTI  1 
#endif

/* Define to 1 to use type_info::name() for class names */
#ifndef CPPUNIT_USE_TYPEINFO_NAME 
#define CPPUNIT_USE_TYPEINFO_NAME  CPPUNIT_HAVE_RTTI 
#endif

#define CPPUNIT_HAVE_SSTREAM 1//ALI
#undef CPPUNIT_HAVE_STRSTREAM
//#define CPPUNIT_HAVE_CLASS_STRSTREAM 1

/* Name of package */
#ifndef CPPUNIT_PACKAGE 
#define CPPUNIT_PACKAGE  "cppunit" 
#endif


// Compiler error location format for CompilerOutputter
// See class CompilerOutputter for format.
#undef CPPUNIT_COMPILER_LOCATION_FORMAT
/*#if _MSC_VER >= 1300    // VS 7.0
# define CPPUNIT_COMPILER_LOCATION_FORMAT "%p(%l) : error : "
#else
# define CPPUNIT_COMPILER_LOCATION_FORMAT "%p(%l):"
#endif*/
# define CPPUNIT_COMPILER_LOCATION_FORMAT "%p(%l) : error : "

// Uncomment to turn on STL wrapping => use this to test compilation. 
// This will make CppUnit subclass std::vector & co to provide default
// parameter.
/*#define CPPUNIT_STD_NEED_ALLOCATOR 1
#define CPPUNIT_STD_ALLOCATOR std::allocator<T>
#define CPPUNIT_NO_NAMESPACE 1 //ALI
*/


/* _INCLUDE_CPPUNIT_CONFIG_RVDK_H */
#endif
