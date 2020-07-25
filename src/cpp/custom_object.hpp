#pragma once

#include <napi.h>

class CustomObject : public Napi::ObjectWrap<CustomObject>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  CustomObject(const Napi::CallbackInfo &info);

private:
  static Napi::FunctionReference constructor;

  Napi::Value GetValue(const Napi::CallbackInfo &info);
  Napi::Value PlusOne(const Napi::CallbackInfo &info);
  Napi::Value Multiply(const Napi::CallbackInfo &info);

  double value_;
};
