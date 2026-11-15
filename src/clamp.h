#ifndef CLAMP_H
#define CLAMP_H

// C++ mangles function names (encodes parameter types into the symbol) and C does not.
// extern "C" tells a C++ compiler to look for the plain C symbol `clamp_int`.
// Without it, the linker error is: undefined reference to `clamp_int(int, int, int)`.
#ifdef __cplusplus
extern "C" {
#endif

// Returns v limited to the range [lo, hi]. Requires lo <= hi.
int clamp_int(int v, int lo, int hi);

#ifdef __cplusplus
}
#endif

#endif // CLAMP_H
