#ifndef _FFT_SOFT_H
#define _FFT_SOFT_H

#include <stdint.h>

#define SWAP(a, b) do {complex t = (a); (a) = (b); (b) = t;} while(0)

typedef struct{double real, imag;} complex;

#ifdef __cplusplus
extern "C" {
#endif

    void fft_soft(complex *data, int n);
    void ifft_soft(complex *data, int n);
    void show(complex *data, int n);
#ifdef __cplusplus
}
#endif

#endif /* _FFT_SOFT_H */