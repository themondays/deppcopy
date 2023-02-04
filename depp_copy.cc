#include <node.h>
#include <v8.h>

using v8::Array;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::MaybeLocal;
using v8::Object;
using v8::String;
using v8::Value;

MaybeLocal<Value> DeppCopy(Local<Value> value, Isolate* isolate, Local<Context> context) {
  if (!value->IsObject() && !value->IsArray()) {
    return value;
  }

  // Dealing with arrays and objects
  if (value->IsArray()) {
    Local<Array> source = value.As<Array>();
    Local<Array> copy = Array::New(isolate, source->Length());
    for (uint32_t i = 0; i < source->Length(); i++) {
      Local<Value> element = source->Get(context, i).ToLocalChecked();
      MaybeLocal<Value> maybe_deep_copy_value = DeppCopy(element, isolate, context);
      if (!maybe_deep_copy_value.IsEmpty()) {
        if (copy->Set(context, i, maybe_deep_copy_value.ToLocalChecked()).IsJust()) {
        }
      }
    }
    return copy;
  } else {
    Local<Object> source = value.As<Object>();
    Local<Object> copy = Object::New(isolate);

    Local<Array> properties = source->GetOwnPropertyNames(context).ToLocalChecked();
    for (uint32_t i = 0; i < properties->Length(); i++) {
      Local<Value> key = properties->Get(context, i).ToLocalChecked();
      Local<Value> property_value = source->Get(context, key).ToLocalChecked();

      MaybeLocal<Value> maybe_deep_copy_value = DeppCopy(property_value, isolate, context);
      if (!maybe_deep_copy_value.IsEmpty()) {
        if (copy->Set(context, key, maybe_deep_copy_value.ToLocalChecked()).IsJust()) {
        }
      }
    }

    return copy;
  }
}

void DeppCopyWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<Value> source = args[0];
  MaybeLocal<Value> maybe_copy = DeppCopy(source, isolate, context);
  if (!maybe_copy.IsEmpty()) {
    args.GetReturnValue().Set(maybe_copy.ToLocalChecked());
  }
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "deppCopy", DeppCopyWrapper);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
