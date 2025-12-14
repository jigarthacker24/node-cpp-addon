#ifndef GREETER_H
#define GREETER_H

#include <napi.h>

// Forward declarations
napi_value GreetCAPI(napi_env env, napi_callback_info info);
napi_value Calculate(napi_env env, napi_callback_info info);

// C++ Wrapper class
class Greeter : public Napi::ObjectWrap<Greeter> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Greeter(const Napi::CallbackInfo& info);
    
private:
    Napi::Value Greet(const Napi::CallbackInfo& info);
    Napi::Value GetUserInfo(const Napi::CallbackInfo& info);
};

#endif