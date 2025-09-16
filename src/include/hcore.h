#ifndef __HCORE__
#define __HCORE__

// Universal complex type compatibility layer
#include <complex.h>

// Detect complex number type compatibility
#ifdef MKL
  #include <mkl.h>
  #include <mkl_lapack.h>
  //#pragma message("MKL is used")
  
  // Intel MKL uses MKL_Complex16, need conversion from GCC _Complex double
  #define COMPLEX_TYPE_MKL
  
  // Convert GCC complex double to MKL_Complex16
  #define TO_LAPACK_COMPLEX(z) ((MKL_Complex16){creal(z), cimag(z)})
  
  // Convert MKL_Complex16 to GCC complex double
  #define FROM_LAPACK_COMPLEX(z) (creal(z) + cimag(z) * I)
  
  // Convert complex pointer types (for arrays)
  #define TO_LAPACK_COMPLEX_PTR(ptr) ((MKL_Complex16*)(ptr))
  #define FROM_LAPACK_COMPLEX_PTR(ptr) ((double _Complex*)(ptr))
  
  // Helper macros for common complex constants
  #define LAPACK_ZERO ((MKL_Complex16){0.0, 0.0})
  #define LAPACK_ONE  ((MKL_Complex16){1.0, 0.0})
  
#elif defined(ARMPL)
  #include <armpl.h>
  //#pragma message("ARMPL is used")
  
  // ARM Performance Libraries - check if they use different complex types
  #ifdef __ARM_FEATURE_SVE
    // ARM SVE might use different complex representation
    #define COMPLEX_TYPE_ARMPL
    #define TO_LAPACK_COMPLEX(z) (z)  // Assume compatible for now
    #define FROM_LAPACK_COMPLEX(z) (z)
    #define TO_LAPACK_COMPLEX_PTR(ptr) (ptr)
    #define FROM_LAPACK_COMPLEX_PTR(ptr) (ptr)
    #define LAPACK_ZERO (0.0 + 0.0*I)
    #define LAPACK_ONE  (1.0 + 0.0*I)
  #else
    // Standard ARM PL - should be compatible with GCC complex
    #define TO_LAPACK_COMPLEX(z) (z)
    #define FROM_LAPACK_COMPLEX(z) (z)
    #define TO_LAPACK_COMPLEX_PTR(ptr) (ptr)
    #define FROM_LAPACK_COMPLEX_PTR(ptr) (ptr)
    #define LAPACK_ZERO (0.0 + 0.0*I)
    #define LAPACK_ONE  (1.0 + 0.0*I)
  #endif
  
#elif defined(OPENBLAS) || defined(__OPENBLAS)
  #include <cblas.h>
  //#pragma message("OpenBLAS is used")
  
  // OpenBLAS typically uses standard complex types
  #define TO_LAPACK_COMPLEX(z) (z)
  #define FROM_LAPACK_COMPLEX(z) (z)
  #define TO_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define FROM_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define LAPACK_ZERO (0.0 + 0.0*I)
  #define LAPACK_ONE  (1.0 + 0.0*I)
  
#elif defined(ATLAS) || defined(__ATLAS)
  #include <cblas.h>
  //#pragma message("ATLAS is used")
  
  // ATLAS uses standard complex types
  #define TO_LAPACK_COMPLEX(z) (z)
  #define FROM_LAPACK_COMPLEX(z) (z)
  #define TO_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define FROM_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define LAPACK_ZERO (0.0 + 0.0*I)
  #define LAPACK_ONE  (1.0 + 0.0*I)
  
#elif defined(GOTO) || defined(__GOTO)
  #include <cblas.h>
  //#pragma message("GotoBLAS is used")
  
  // GotoBLAS uses standard complex types
  #define TO_LAPACK_COMPLEX(z) (z)
  #define FROM_LAPACK_COMPLEX(z) (z)
  #define TO_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define FROM_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define LAPACK_ZERO (0.0 + 0.0*I)
  #define LAPACK_ONE  (1.0 + 0.0*I)
  
#else
  #include <cblas.h>
  //#pragma message("Standard BLAS/LAPACK is used")
  
  // Standard LAPACKE uses double _Complex, no conversion needed
  #define TO_LAPACK_COMPLEX(z) (z)
  #define FROM_LAPACK_COMPLEX(z) (z)
  #define TO_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define FROM_LAPACK_COMPLEX_PTR(ptr) (ptr)
  #define LAPACK_ZERO (0.0 + 0.0*I)
  #define LAPACK_ONE  (1.0 + 0.0*I)
  
  #ifdef LAPACKE_UTILS
    #include <lapacke_utils.h>
  #endif
  #include <lapacke.h>
  //#pragma message("MKL is NOT used")
#endif

#ifndef hcore_min
#define hcore_min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef hcore_max
#define hcore_max(a, b) ((a) < (b) ? (b) : (a))
#endif



#define HCORE_NoTrans         111
#define HCORE_Trans           112
#define HCORE_ConjTrans       113

#define HCORE_Upper           121
#define HCORE_Lower           122
#define HCORE_UpperLower      123

#define HCORE_NonUnit         131
#define HCORE_Unit            132

#define HCORE_Left            141
#define HCORE_Right           142

typedef int  HCORE_enum;
#endif
