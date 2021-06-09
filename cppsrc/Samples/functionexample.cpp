#include "functionexample.h"

std::string functionexample::hello() {
    return "Hello World!";
}
Napi::String functionexample::HelloWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, functionexample::hello());
    return returnValue;
}

int functionexample::add(int a, int b) {
    return a + b;
}
Napi::Number functionexample::AddWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number a = info[0].As<Napi::Number>();
    Napi::Number b = info[1].As<Napi::Number>();

    int returnValue = functionexample::add(a.Int32Value(), b.Int32Value());
    return Napi::Number::New(env, returnValue);
}

int functionexample::subtract(int a, int b) {
    return a - b;
}
Napi::Number functionexample::SubtractWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    int a = info[0].As<Napi::Number>().Int32Value();
    int b = info[1].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, functionexample::subtract(a, b));
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("hello", Napi::Function::New(env, functionexample::HelloWrapped));
    exports.Set("add", Napi::Function::New(env, functionexample::AddWrapped));
    exports.Set("subtract", Napi::Function::New(env, functionexample::SubtractWrapped));
    return exports;
}