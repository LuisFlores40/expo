/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// NOTE: This entire file should be codegen'ed.

#include <ABI47_0_0ReactCommon/ABI47_0_0SampleTurboModuleSpec.h>

namespace ABI47_0_0facebook {
namespace ABI47_0_0React {

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_voidFunc(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt, VoidKind, "voidFunc", "()V", args, count, cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getBool(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt, BooleanKind, "getBool", "(Z)Z", args, count, cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getNumber(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt, NumberKind, "getNumber", "(D)D", args, count, cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getString(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          StringKind,
          "getString",
          "(Ljava/lang/String;)Ljava/lang/String;",
          args,
          count,
          cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getArray(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          ArrayKind,
          "getArray",
          "(Lcom/facebook/ABI47_0_0React/bridge/ReadableArray;)Lcom/facebook/ABI47_0_0React/bridge/WritableArray;",
          args,
          count,
          cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getObject(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          ObjectKind,
          "getObject",
          "(Lcom/facebook/ABI47_0_0React/bridge/ReadableMap;)Lcom/facebook/ABI47_0_0React/bridge/WritableMap;",
          args,
          count,
          cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getRootTag(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt, NumberKind, "getRootTag", "(D)D", args, count, cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getValue(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          ObjectKind,
          "getValue",
          "(DLjava/lang/String;Lcom/facebook/ABI47_0_0React/bridge/ReadableMap;)Lcom/facebook/ABI47_0_0React/bridge/WritableMap;",
          args,
          count,
          cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getValueWithCallback(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          VoidKind,
          "getValueWithCallback",
          "(Lcom/facebook/ABI47_0_0React/bridge/Callback;)V",
          args,
          count,
          cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getValueWithPromise(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          PromiseKind,
          "getValueWithPromise",
          "(ZLcom/facebook/ABI47_0_0React/bridge/Promise;)V",
          args,
          count,
          cachedMethodId);
}

static ABI47_0_0facebook::jsi::Value
__hostFunction_NativeSampleTurboModuleSpecJSI_getConstants(
    ABI47_0_0facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const ABI47_0_0facebook::jsi::Value *args,
    size_t count) {
  static jmethodID cachedMethodId = nullptr;
  return static_cast<JavaTurboModule &>(turboModule)
      .invokeJavaMethod(
          rt,
          ObjectKind,
          "getConstants",
          "()Ljava/util/Map;",
          args,
          count,
          cachedMethodId);
}

NativeSampleTurboModuleSpecJSI::NativeSampleTurboModuleSpecJSI(
    const JavaTurboModule::InitParams &params)
    : JavaTurboModule(params) {
  methodMap_["voidFunc"] =
      MethodMetadata{0, __hostFunction_NativeSampleTurboModuleSpecJSI_voidFunc};

  methodMap_["getBool"] =
      MethodMetadata{1, __hostFunction_NativeSampleTurboModuleSpecJSI_getBool};

  methodMap_["getNumber"] = MethodMetadata{
      1, __hostFunction_NativeSampleTurboModuleSpecJSI_getNumber};

  methodMap_["getString"] = MethodMetadata{
      1, __hostFunction_NativeSampleTurboModuleSpecJSI_getString};

  methodMap_["getArray"] =
      MethodMetadata{1, __hostFunction_NativeSampleTurboModuleSpecJSI_getArray};

  methodMap_["getObject"] = MethodMetadata{
      1, __hostFunction_NativeSampleTurboModuleSpecJSI_getObject};

  methodMap_["getRootTag"] = MethodMetadata{
      1, __hostFunction_NativeSampleTurboModuleSpecJSI_getRootTag};

  methodMap_["getValue"] =
      MethodMetadata{3, __hostFunction_NativeSampleTurboModuleSpecJSI_getValue};

  methodMap_["getValueWithCallback"] = MethodMetadata{
      1, __hostFunction_NativeSampleTurboModuleSpecJSI_getValueWithCallback};

  methodMap_["getValueWithPromise"] = MethodMetadata{
      1, __hostFunction_NativeSampleTurboModuleSpecJSI_getValueWithPromise};

  methodMap_["getConstants"] = MethodMetadata{
      0, __hostFunction_NativeSampleTurboModuleSpecJSI_getConstants};
}

std::shared_ptr<TurboModule> SampleTurboModuleSpec_ModuleProvider(
    const std::string &moduleName,
    const JavaTurboModule::InitParams &params) {
  if (moduleName == "SampleTurboModule") {
    return std::make_shared<NativeSampleTurboModuleSpecJSI>(params);
  }
  return nullptr;
}

} // namespace ABI47_0_0React
} // namespace ABI47_0_0facebook
