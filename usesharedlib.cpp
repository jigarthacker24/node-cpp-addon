#include <napi.h>
#include "mylib.h"  // Our C library header

// Wrapper for the add function
Napi::Number AddWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Expected two numbers").ThrowAsJavaScriptException();
        return Napi::Number::New(env, 0);
    }

    if (!info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Expected numbers as arguments").ThrowAsJavaScriptException();
        return Napi::Number::New(env, 0);
    }

    int a = info[0].As<Napi::Number>().Int32Value();
    int b = info[1].As<Napi::Number>().Int32Value();

    int result = add(a, b);  // Call the C function
    return Napi::Number::New(env, result);
}

// Wrapper for the get_greeting function
Napi::String GetGreetingWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expected a name").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Expected a string as argument").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    std::string name = info[0].As<Napi::String>().Utf8Value();
    const char* greeting = get_greeting(name.c_str());  // Call the C function
    
    return Napi::String::New(env, greeting);
}

// Initialize the module
Napi::Object InitSharedLibWrapper(Napi::Env env, Napi::Object exports) {
    // Export the functions
    exports.Set(
        Napi::String::New(env, "add"),
        Napi::Function::New(env, AddWrapped, "add")
    );
    
    exports.Set(
        Napi::String::New(env, "getGreeting"),
        Napi::Function::New(env, GetGreetingWrapped, "getGreeting")
    );

    return exports;
}



