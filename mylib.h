#ifndef MYLIB_H
#define MYLIB_H

#ifdef __cplusplus
extern "C" {
#endif

// Simple function that adds two numbers
int add(int a, int b);

// Function that returns a greeting
const char* get_greeting(const char* name);

#ifdef __cplusplus
}
#endif

#endif // MYLIB_H