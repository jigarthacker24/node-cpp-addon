#include "greeter.h"

// C++ Wrapper implementation
Greeter::Greeter(const Napi::CallbackInfo& info) 
    : Napi::ObjectWrap<Greeter>(info) {}

Napi::Value Greeter::Greet(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    std::string name = info[0].As<Napi::String>().Utf8Value();
    return Napi::String::New(env, "Hello from C++ wrapper, " + name + "!");
}

Napi::Value Greeter::GetUserInfo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object result = Napi::Object::New(env);

    result.Set("name", Napi::String::New(env, "John Doe"));
    result.Set("age", Napi::Number::New(env, 30));
    result.Set("isDeveloper", Napi::Boolean::New(env, true));

    Napi::Array languages = Napi::Array::New(env, 3);
    languages.Set(0u, Napi::String::New(env, "C++"));
    languages.Set(1u, Napi::String::New(env, "JavaScript"));
    languages.Set(2u, Napi::String::New(env, "Python"));
    
    result.Set("languages", languages);
    return result;
}

Napi::Object Greeter::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Greeter", {
        InstanceMethod("greet", &Greeter::Greet),
        InstanceMethod("getUserInfo", &Greeter::GetUserInfo)
    });

    // Store the constructor as a persistent reference
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    
    // Store the constructor in the exports object
    exports.Set("Greeter", func);
    return exports;
}