#include <napi.h>

// C API implementation (from hello.cpp)
napi_value GreetCAPI(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    if (argc < 1) {
        napi_throw_error(env, nullptr, "Expected one argument");
        return nullptr;
    }

    napi_valuetype valuetype;
    status = napi_typeof(env, argv[0], &valuetype);
    if (status != napi_ok || valuetype != napi_string) {
        napi_throw_type_error(env, nullptr, "Expected a string as first argument");
        return nullptr;
    }

    char name[256];
    size_t name_length;
    status = napi_get_value_string_utf8(env, argv[0], name, sizeof(name), &name_length);
    if (status != napi_ok) return nullptr;

    std::string greeting = "Hello from C API, " + std::string(name, name_length) + "!";
    
    napi_value result;
    status = napi_create_string_utf8(env, greeting.c_str(), NAPI_AUTO_LENGTH, &result);
    if (status != napi_ok) return nullptr;
    
    return result;
}

napi_value Calculate(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    if (argc < 2) {
        napi_throw_error(env, nullptr, "Expected two arguments");
        return nullptr;
    }

    napi_valuetype type1, type2;
    napi_typeof(env, argv[0], &type1);
    napi_typeof(env, argv[1], &type2);
    
    if (type1 != napi_number || type2 != napi_number) {
        napi_throw_type_error(env, nullptr, "Expected numbers as arguments");
        return nullptr;
    }

    double a, b;
    napi_get_value_double(env, argv[0], &a);
    napi_get_value_double(env, argv[1], &b);

    napi_value result;
    status = napi_create_object(env, &result);
    if (status != napi_ok) return nullptr;

    napi_value value;
    napi_create_double(env, a + b, &value);
    napi_set_named_property(env, result, "sum", value);
    
    napi_create_double(env, a - b, &value);
    napi_set_named_property(env, result, "difference", value);
    
    napi_create_double(env, a * b, &value);
    napi_set_named_property(env, result, "product", value);
    
    napi_create_double(env, b != 0 ? a / b : NAN, &value);
    napi_set_named_property(env, result, "quotient", value);

    return result;
}

// C++ Wrapper implementation
Napi::String HelloMethod(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expected one argument").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Expected a string as first argument").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    std::string name = info[0].As<Napi::String>().Utf8Value();
    std::string greeting = "Hello from C++ wrapper, " + name + "!";
    
    return Napi::String::New(env, greeting);
}

Napi::Object GetUserInfo(const Napi::CallbackInfo& info) {
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

// Initialize the module
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // Export C API functions
    napi_value fn;
    napi_create_function(env, nullptr, 0, GreetCAPI, nullptr, &fn);
    napi_set_named_property(env, exports, "greetCAPI", fn);
    
    napi_create_function(env, nullptr, 0, Calculate, nullptr, &fn);
    napi_set_named_property(env, exports, "calculate", fn);

    // Export C++ Wrapper functions
    exports.Set(
        Napi::String::New(env, "greetCPP"), 
        Napi::Function::New(env, HelloMethod, "greetCPP")
    );
    
    exports.Set(
        Napi::String::New(env, "getUserInfo"),
        Napi::Function::New(env, GetUserInfo, "getUserInfo")
    );

    return exports;
}

NODE_API_MODULE(addon, Init)