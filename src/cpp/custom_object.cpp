#include "custom_object.hpp"

Napi::FunctionReference CustomObject::constructor;

Napi::Object CustomObject::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "CustomObject", {
        InstanceMethod("getValue", &CustomObject::getValue),
        InstanceMethod("plusOne", &CustomObject::plusOne),
        InstanceMethod("value", &CustomObject::getValue),
        InstanceMethod("multiply", &CustomObject::multiply),
        InstanceMethod("runCallback", &CustomObject::runCallback)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("CustomObject", func);
    return exports;
}

CustomObject::CustomObject(const Napi::CallbackInfo& info) : Napi::ObjectWrap<CustomObject>(info)  {
    auto env = info.Env();
    // What does this line do?
    Napi::HandleScope scope(env);

    const int length = info.Length();

    if (length <= 0 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected as first argument").ThrowAsJavaScriptException();
    }

    Napi::Number value = info[0].As<Napi::Number>();
    this->value = value.DoubleValue();

    if (length >= 2) {
        if (!info[1].IsObject()) {
            Napi::TypeError::New(env, "Object expected as optional second argument").ThrowAsJavaScriptException();
        }
        Napi::Object obj = info[1].As<Napi::Object>();
        this->options = Reference<Napi::Object>::New(obj);
    } else {
        Napi::Object defaultObj = Napi::Object::New(env);
        this->options = Reference<Napi::Object>::New(defaultObj);
    }
}

Napi::Value CustomObject::getValue(const Napi::CallbackInfo& info) {
    double num = this->value;

    return Napi::Number::New(info.Env(), num);
}

Napi::Value CustomObject::plusOne(const Napi::CallbackInfo& info) {
    this->value = this->value + 1;

    return CustomObject::getValue(info);
}

Napi::Value CustomObject::multiply(const Napi::CallbackInfo& info) {
    Napi::Number factor;
    if (info.Length() <= 0 || !info[0].IsNumber()) {
        factor = Napi::Number::New(info.Env(), 1);
    } else {
        factor = info[0].As<Napi::Number>();
    }

    Napi::Object obj = constructor.New({ Napi::Number::New(info.Env(), this->value * factor.DoubleValue()) });

    return obj;
}

Napi::Value CustomObject::runCallback(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();

    // Here you can call the js function and at the same time you can use your
    // C / C++ library

    if (!this->options) {
        Napi::TypeError::New(env, "Options were never assigned").ThrowAsJavaScriptException();
    }

    if (this->options.IsEmpty()) {
        Napi::TypeError::New(env, "Options were never assigned (empty)").ThrowAsJavaScriptException();
    }

    Napi::Function callback = this->options.Get("callback").As<Napi::Function>();

    if (callback.IsFunction()) {
        callback.Call(env.Global(), {Napi::String::New(env, "It works")});
    }

    return info.Env().Undefined();
}
