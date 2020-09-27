// Copyright Neil Maitland 1992
//
//
// Description:
//
// This file contains a function for performing a fast Fourier transform
// of an array of complex numbers of type compreal.  It has been written to
// be reasonably independent of the main project code, and could therefore
// be reused on its own.
//
// The parameters are:
//
//   numelems -  specifies the size of the complex arrays (must be power of 2)
//
//   data -      array of complex values to be transformed.  Type compreal.
//               Values are transformed in place.
//
//   operation - states whether to divide elements of output array by N to
//               cater for 2-D FFTs.  It is of enum type fftinput.
//
//   forrev -    states whether transform is forward or inverse.  It is
//               of enum type direction.
//
// The FFT algorithm itself was developed from the FORTRAN code given in
// Cooley, Lewis and Welch's paper "The Fast Fourier Transform and Its
// Applications" published in IEEE Transactions on Education Vol.12, No. 1,
// in March 1969.
//
// Modifications:
//  29-09-92 : Neil Maitland -
//  22-12-92 : Neil Maitland - Removed some redundant floating point
//                             operations to increase speed.
//  02-01-93 : Neil Maitland - Still trying to increase speed!
//                             Added loop induction variables for main
//                             multiply and sum loop.  Also made use of
//                             compound maths operators added to compreal
//                             class.
//  27-03-93 : Neil Maitland - added all of the compiler directives for
//                             optimisation.
//


#include <math.h>
#include <float.h>
#define M_PI 3.14159265358979323846

#include "compreal.hpp"

// #ifndef DEBUG // then optimise code

// #pragma option -vi  // expand C++ inline functions
// #pragma option -G   // optimise code for speed
// #pragma option -O2  // turn on all speed optimisations
// #pragma option -po  // localise C++ object members with SI register
// #pragma option -k-  // can use non-standard stack frames

// #endif

// #pragma option -2   // use 80286p instructions
// #pragma option -a   // align data on even addresses
// #pragma option -K   // use unsigned chars
// #pragma option -v   // include debug info in OBJs
// #pragma option -Z   // optimise register usage
// #pragma option -d   // merge duplicate strings

// // turn off invariant code motion optimisation as it produces a bug in the
// // code
// #pragma option -O-m

// define enumerated types used as input parameters
#ifndef directions
enum directions {FORWARD, INVERSE};
#endif

#ifndef trantype
enum trantype {DIVIDE, NODIVIDE};
#endif


// ***************************************************************************
// this is the main fft routine described at the top of this file
//
void fft_epic(int numelems, compreal data[],
            enum directions forinv, enum trantype operation)
{

   // type compreal is a complex number class implemented with floats
   compreal tempcomplx, w, u, *index1, *index2;

   // sign of sine term of coeffs - depends on direction of transform
   float sign = (forinv==INVERSE) ? 1.0 : -1.0;


   // various loop variables
   int loop1, loop2, tempint, outer, innerstep, halfinnerstep, numbits;
   int halfelems = numelems>>1;
   int numelemsm1 = numelems-1;

   // calculate the number of significant bits in numelems
   // i.e. log(numelems)/log(2)
   numbits = -1;
   tempint = numelems;
   while (tempint>0) {
      numbits++;
      tempint >>= 1;
   }

   // reorder elements ready for multiplication by folding in powers of 2
   // i.e. bit reversal
   for (loop2=loop1=1; loop1 <= numelemsm1; loop1++) {
      if (loop1 < loop2) {
         tempcomplx = data[loop2-1];
         data[loop2-1] = data[loop1-1];
         data[loop1-1] = tempcomplx;
      }
      tempint = halfelems;
      while (tempint < loop2) {
         loop2 -= tempint;
         tempint >>= 1;
      }
      loop2 += tempint;
   }

   // now multiply and sum butterfly elements
   for (outer=1; outer <= numbits; outer++) {
      innerstep = 1<<outer;   // i.e. = pow(2, outer);
      halfinnerstep = innerstep>>1;
      u = compreal (1, 0);
      w = compreal (cos(M_PI/halfinnerstep), sign*(sin(M_PI/halfinnerstep)));
      for (loop2=1; loop2 <= halfinnerstep; loop2++) {
         index1 = &data[loop2-1];
         for (loop1=loop2; loop1 <= numelems; loop1+=innerstep) {
            index2 = index1 + halfinnerstep;
            tempcomplx = *index2;
            tempcomplx *= u;
            *index2 = *index1 - tempcomplx;
            *index1 += tempcomplx;
            index1 += innerstep;
         }
         u *= w;
      }
   }

   // finally, divide elements by N if required
   if (operation == DIVIDE)
      for (loop1 = 0; loop1 < numelems; loop1++)
         data[loop1] /= numelems;
}
