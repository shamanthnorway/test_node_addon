#include "classexample.h"

Napi::FunctionReference ClassExample::constructor;

Napi::Object ClassExample::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ClassExample", {
        InstanceMethod("getValue", &ClassExample::GetValue),
        InstanceMethod("add", &ClassExample::Add),
        InstanceMethod("subtract", &ClassExample::Subtract)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("ClassExample", func);
    return exports;
}
ClassExample::ClassExample(const Napi::CallbackInfo &info) 
    : Napi::ObjectWrap<ClassExample>(info) 
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if(length != 1) {
        Napi::TypeError::New(env, "Only one argument expected").ThrowAsJavaScriptException();
    }

    if(!info[0].IsNumber()) {
        Napi::Object object_parent = info[0].As<Napi::Object>();
        ClassExample* example_parent = Napi::ObjectWrap<ClassExample>::Unwrap(object_parent);
        ActualClass* parent_actual_class_instance = example_parent->GetInternalInstance();
        this->mActualClass = new ActualClass(parent_actual_class_instance->getValue());
        return;
    }

    Napi::Number value = info[0].As<Napi::Number>();
    this->mActualClass = new ActualClass(value.DoubleValue());
}

// Private functions
Napi::Value ClassExample::GetValue(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double value = this->mActualClass->getValue();
    return Napi::Number::New(env, value);

}
Napi::Value ClassExample::Add(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number a = info[0].As<Napi::Number>();
    return Napi::Number::New(env, this->mActualClass->add(a.DoubleValue()));

}
Napi::Value ClassExample::Subtract(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number a = info[0].As<Napi::Number>();
    return Napi::Number::New(env, this->mActualClass->subtract(a.DoubleValue()));
}


ActualClass* ClassExample::GetInternalInstance() {
    return mActualClass;
}