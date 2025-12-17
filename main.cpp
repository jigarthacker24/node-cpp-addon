#include "greeter.h"
#include "usesharedlib.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    // Initialize C API functions
    napi_value fn;
    napi_create_function(env, nullptr, 0, GreetCAPI, nullptr, &fn);
    napi_set_named_property(env, exports, "greetCAPI", fn);
    
    napi_create_function(env, nullptr, 0, Calculate, nullptr, &fn);
    napi_set_named_property(env, exports, "calculate", fn);

    // Initialize C++ Wrapper
    Greeter::Init(env, exports);
    
    // Initialize C++ Shared Lib Wrapper
    InitSharedLibWrapper(env, exports);
    
    return exports;
}

NODE_API_MODULE(addon, InitAll)