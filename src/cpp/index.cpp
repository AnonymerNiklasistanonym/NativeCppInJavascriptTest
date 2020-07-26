#include <string>
#include "napi.h"
#include "count.hpp"
#include "custom_object.hpp"
#include "greeting.hpp"

Napi::String interfaceHelloUser(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    const std::string result = helloUser("Mike");
    return Napi::String::New(env, result);
}

Napi::Number interfaceCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info[0].IsNull()) {
        napi_throw_error(env, "NUMBER_WAS_NULL", "");
    }
    if (info[0].IsUndefined()) {
        napi_throw_error(env, "NUMBER_WAS_UNDEFINED", "");
    }
    if (!info[0].IsNumber()) {
        napi_throw_error(env, "NUMBER_WAS_NOT_A_NUMBER", "");
    }
    const auto number = info[0].As<Napi::Number>();
    // TODO Check if the value is not an integer!
    const auto result = count(number.Int32Value());
    return Napi::Number::New(env, result);
}

Napi::Object Init(const Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    exports.Set(
        Napi::String::New(env, "helloUser"),
        Napi::Function::New(env, interfaceHelloUser)
    );
    exports.Set(
        Napi::String::New(env, "count"),
        Napi::Function::New(env, interfaceCount)
    );
    return exports;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    exports.Set(
        Napi::String::New(env, "helloUser"),
        Napi::Function::New(env, interfaceHelloUser)
    );
    exports.Set(
        Napi::String::New(env, "count"),
        Napi::Function::New(env, interfaceCount)
    );
    CustomObject::Init(env, exports);
    return exports;
}

// register 'greet' module which calls the `Init` method
NODE_API_MODULE(NativeModule, InitAll)
