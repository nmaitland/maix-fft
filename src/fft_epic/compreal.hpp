// Copyright Neil Maitland 1992
//
// Description:
//
// This file provides complex number functions using single precision floating
// point types.  Four basic arithmetic operators are overloaded. Operators for
// taking conjugates, calculating magnitudes, and comparison operators are
// provided.
//
// Modifications :
//  02-01-93 : Neil Maitland - added compound maths operators to help
//                             increase speed
//  07-05-93 : Neil Maitland - tidied comments
//

// ensure class is only defined once
#ifndef __COMPREAL__

#define __COMPREAL__ 1


#include <math.h>

class compreal {

public:
   compreal(float _re_val, float _im_val=0); // standard constructor, defaults
                                             // imag part to 0 if not given
   compreal();                               // default value constructor
   friend float real(compreal&);             // return the real part
   friend float imag(compreal&);             // return the imaginary part
   float real();             // return the real part
   float imag();             // return the imaginary part
   friend compreal conj(compreal&);          // return the complex conjugate
   friend float mag(compreal&);              // return the magnitude
   friend compreal operator+(compreal&, compreal&); // complex addition
   friend compreal operator-(compreal&, compreal&); // complex subtraction
   friend compreal operator-(compreal&);            // complex negation
   friend compreal operator*(compreal&, compreal&); // complex mutiplication
   friend compreal operator*(compreal&, float);     // multiplication by a
                                                    // constant
   friend compreal operator/(compreal&, compreal&); // complex division
   friend compreal operator/(compreal&, float);     // division by a constant
   compreal& operator/=(compreal&);   // compound complex division
   compreal& operator/=(float);       // compound division by a constant
   compreal& operator*=(compreal&);   // compound complex multiplication
   compreal& operator*=(float);       // compound multiplication by a constant
   compreal& operator+=(compreal&);   // compound complex addition
   compreal& operator-=(compreal&);   // compound complex subtraction
   friend compreal ptor(compreal&);   // polar to rectangular
   friend compreal rtop(compreal&);   // rectangular to polar
   friend int operator==(compreal&, compreal&);     // test for equality
   friend int operator!=(compreal&, compreal&);     // test for inequality

private:
   float re, im;     // implemented as single precision floats
};




// ***************************************************************************

inline compreal::compreal (float _re_val, float _im_val)
{
   re = _re_val;
   im = _im_val;
}




// ***************************************************************************

inline compreal::compreal()
{
   re = im = 0;
}




// ***************************************************************************

inline float real(compreal& _z)
{
   return _z.re;
}




// ***************************************************************************

inline float  imag(compreal& _z)
{
   return _z.im;
}


// ***************************************************************************

inline float compreal::real()
{
   return re;
}

// ***************************************************************************

inline float compreal::imag()
{
   return im;
}


// ***************************************************************************

inline compreal conj(compreal& _z)
{
   return compreal(_z.re, -_z.im);
}




// ***************************************************************************

inline float mag(compreal& _z)
{
   return (sqrt(_z.re*_z.re + _z.im*_z.im));
}




// ***************************************************************************

inline compreal operator+(compreal& _z1, compreal& _z2)
{
   return compreal(_z1.re + _z2.re, _z1.im + _z2.im);
}




// ***************************************************************************

inline compreal operator-(compreal& _z1, compreal& _z2)
{
   return compreal(_z1.re - _z2.re, _z1.im - _z2.im);
}




// ***************************************************************************

inline compreal operator-(compreal& _z1)
{
   return compreal(-_z1.re, -_z1.im);
}




// ***************************************************************************

inline compreal operator*(compreal& _z1, compreal& _z2)
{
   return compreal ( (_z1.re*_z2.re)-(_z1.im*_z2.im),
                     (_z1.re*_z2.im)+(_z1.im*_z2.re));
}




// ***************************************************************************

inline compreal operator*(compreal& _z1, float _real2)
{
   return compreal(_z1.re * _real2, _z1.im * _real2);
}




// ***************************************************************************

inline compreal operator/(compreal& _z1, compreal& _z2)
{
   float temp = (_z2.re*_z2.re + _z2.im*_z2.im);
   return compreal( (_z1.re*_z2.re + _z1.im*_z2.im)/temp,
            (_z1.im*_z2.re - _z1.re*_z2.im)/temp );
}




// ***************************************************************************

inline compreal operator/(compreal& _z1, float _real2)
{
   return compreal(_z1.re / _real2, _z1.im / _real2);
}




// ***************************************************************************

inline compreal& compreal::operator/=(compreal& _z2)
{
   float temp = (_z2.re*_z2.re + _z2.im*_z2.im);
   float tempre = (re*_z2.re + im*_z2.im)/temp;
   im = (im*_z2.re - re*_z2.im)/temp;
   re = tempre;
   return *this;
}




// ***************************************************************************

inline compreal& compreal::operator/=(float _real2)
{
   re /= _real2;
   im /= _real2;
   return *this;
}




// ***************************************************************************

inline compreal& compreal::operator*=(compreal& _z2)
{
   float tempre = re*_z2.re - im*_z2.im;
   im = re*_z2.im + im*_z2.re;
   re = tempre;
   return *this;
}




// ***************************************************************************

inline compreal& compreal::operator*=(float _real2)
{
   re *= _real2;
   im *= _real2;
   return *this;
}




// ***************************************************************************

inline compreal& compreal::operator+=(compreal& _z2)
{
   re += _z2.re;
   im += _z2.im;
   return *this;
}




// ***************************************************************************

inline compreal& compreal::operator-=(compreal& _z2)
{
   re -= _z2.re;
   im -= _z2.im;
   return *this;
}




// ***************************************************************************

inline compreal rtop(compreal& _z2)
{
   float phase;
   float magn = mag(_z2);
   if (_z2.re!=0.0) {
      phase = atan(_z2.im/_z2.re);
      if (real(_z2)<0.0) {
         if (imag(_z2)>0.0) phase += M_PI;
         else if (imag(_z2)<0.0) phase -= M_PI;
      }
   }
   else {
      if (_z2.im > 0.0) phase = M_PI/2;
      else phase = -M_PI/2;
   }
   return compreal(magn, phase);
}




// ***************************************************************************

inline compreal ptor(compreal& _z2)
{
   return compreal(_z2.re*cos(_z2.im), _z2.re*sin(_z2.im));
}




// ***************************************************************************

inline int operator==(compreal& _z1, compreal& _z2)
{
   return _z1.re == _z2.re && _z1.im == _z2.im;
}




// ***************************************************************************

inline int operator!=(compreal& _z1, compreal& _z2)
{
   return _z1.re != _z2.re || _z1.im != _z2.im;
}




#endif
