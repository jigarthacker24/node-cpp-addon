#include "greeter.h"

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