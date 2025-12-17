#ifndef USE_SHARED_LIB_H
#define USE_SHARED_LIB_H

#include <napi.h>

Napi::Object InitSharedLibWrapper(Napi::Env env, Napi::Object exports);

#endif