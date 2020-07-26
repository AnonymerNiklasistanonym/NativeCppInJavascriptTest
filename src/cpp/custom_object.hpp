#pragma once
#include <napi.h>

class CustomObject : public Napi::ObjectWrap<CustomObject>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    CustomObject(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference constructor;

    Napi::Value getValue(const Napi::CallbackInfo &info);
    Napi::Value plusOne(const Napi::CallbackInfo &info);
    Napi::Value multiply(const Napi::CallbackInfo &info);
    Napi::Value runCallback(const Napi::CallbackInfo &info);

    double value;
    Napi::ObjectReference options;
};
