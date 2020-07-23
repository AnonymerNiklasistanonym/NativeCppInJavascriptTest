#include <string>

#include "napi.h"
#include "greeting.h"

Napi::String greetHello(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string result = helloUser("Mike");
    return Napi::String::New(env, result);
}

Napi::Number count(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int number = info[0].ToNumber().Int32Value();
    double result = 0;
    for (int i = 0; i < number; i++)
    {
        result += i;
    }
    return Napi::Number::New(env, result);
}


Napi::Object Init(const Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "greetHello"),
        Napi::Function::New(env, greetHello)
    );
    exports.Set(
        Napi::String::New(env, "count"),
        Napi::Function::New(env, count)
    );
    return exports;
}

// register 'greet' module which calls the `Init` method
NODE_API_MODULE(greet, Init)
