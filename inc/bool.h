/**
 * @author Gregory Lerbret
 * @file
 * @brief Type booleen
 * @date 06/04/2005
 * @version 1.0
 */

#ifndef GL_BOOL_H
#define GL_BOOL_H

#if __STDC_VERSION__ >= 199901L || defined(__MINGW32_VERSION) || defined(__CYGWIN__) || defined(__GNUC__)
   /* Compilateur conforme C99 et GCC, les booleens "C99" existe deja et sont definis dans stdbool.h */
   #include <stdbool.h>
#elif defined(__BORLANDC__) || (defined(_MSC_VER) && _MSC_VER < 1400)
   /* Compilateur Borland C++ et Visual C++ anterieur a la version 8,
      un type BOOL existe deja, on cree le type booleen "C99-like" a partir de ce type BOOL */
   #include <windows.h>
   typedef BOOL _Bool;
   #define true TRUE
   #define false FALSE
   #define bool _Bool
   #define __bool_true_false_are_defined 1
#elif !defined(__bool_true_false_are_defined)
   /* Les booleens "C99" n'existe pas, on cree un type booleen "C99-like" a partir de char */
   typedef char _Bool;
   #define true 1
   #define false 0
   #define bool _Bool
   #define __bool_true_false_are_defined 1
#endif

#endif
