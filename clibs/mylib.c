#include "mylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

const char* get_greeting(const char* name) {
    static char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello, %s! From C library.", name);
    return greeting;
}