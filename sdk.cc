#include "sdk/include/nlss_api.h"
#include <node.h>

namespace live
{

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;

void Method(const FunctionCallbackInfo<Value> &args)
{
    int iVideoDeviceNum = 0;
    int iAudioDeviceNum = 0;
    Nlss_GetFreeDevicesNum(&iVideoDeviceNum, &iAudioDeviceNum);
    Isolate *isolate = args.GetIsolate();


    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "World"));
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(live, init)

} // namespace live
