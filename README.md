# maix-fft

FFT benchmark for the Kendryte K210 (Sipeed Maix One Dock).

Compares the K210's hardware FFT accelerator against two software FFT implementations — a standard C double-precision Cooley-Tukey and a C++ single-precision version — measuring accuracy and execution time.

## Hardware

- Sipeed Maix One Dock (Kendryte K210, RISC-V)

## Build

Requires [PlatformIO](https://platformio.org/).

```bash
pio run -e sipeed-maix-one-dock -t upload
pio device monitor -b 115200
```

Output shows real/imaginary comparisons, power spectra, phase angles, and timing in microseconds for all three implementations.
