/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI49_0_0BridgingTest.h"

namespace ABI49_0_0facebook::ABI49_0_0React {

using namespace std::literals;

TEST_F(BridgingTest, jsiTest) {
  jsi::Value value = true;
  jsi::Value string = jsi::String::createFromAscii(rt, "hello");
  jsi::Value object = jsi::Object(rt);
  jsi::Value array = jsi::Array::createWithElements(rt, value, object);
  jsi::Value func = function("() => {}");

  // The bridging mechanism needs to know how to copy and downcast values.
  ABI49_0_0EXPECT_NO_THROW(bridging::fromJs<jsi::Value>(rt, value, invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::fromJs<jsi::String>(rt, string, invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::fromJs<jsi::Object>(rt, object, invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::fromJs<jsi::Array>(rt, array, invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::fromJs<jsi::Function>(rt, func, invoker));

  // Should throw when attempting an invalid cast.
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<jsi::Object>(rt, value, invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<jsi::String>(rt, array, invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<jsi::Array>(rt, object, invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<jsi::Array>(rt, string, invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<jsi::Array>(rt, func, invoker));

  // Should be able to generically no-op convert JSI.
  ABI49_0_0EXPECT_NO_THROW(bridging::toJs(rt, value, invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::toJs(rt, string.asString(rt), invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::toJs(rt, object.asObject(rt), invoker));
  ABI49_0_0EXPECT_NO_THROW(bridging::toJs(rt, array.asObject(rt).asArray(rt), invoker));
  ABI49_0_0EXPECT_NO_THROW(
      bridging::toJs(rt, func.asObject(rt).asFunction(rt), invoker));
}

TEST_F(BridgingTest, boolTest) {
  ABI49_0_0EXPECT_TRUE(bridging::fromJs<bool>(rt, jsi::Value(true), invoker));
  ABI49_0_0EXPECT_FALSE(bridging::fromJs<bool>(rt, jsi::Value(false), invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<bool>(rt, jsi::Value(1), invoker));

  ABI49_0_0EXPECT_TRUE(bridging::toJs(rt, true).asBool());
  ABI49_0_0EXPECT_FALSE(bridging::toJs(rt, false).asBool());
}

TEST_F(BridgingTest, numberTest) {
  ABI49_0_0EXPECT_EQ(1, bridging::fromJs<int>(rt, jsi::Value(1), invoker));
  ABI49_0_0EXPECT_FLOAT_EQ(1.2f, bridging::fromJs<float>(rt, jsi::Value(1.2), invoker));
  ABI49_0_0EXPECT_DOUBLE_EQ(1.2, bridging::fromJs<double>(rt, jsi::Value(1.2), invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<double>(rt, jsi::Value(true), invoker));

  ABI49_0_0EXPECT_EQ(1, static_cast<int>(bridging::toJs(rt, 1).asNumber()));
  ABI49_0_0EXPECT_FLOAT_EQ(
      1.2f, static_cast<float>(bridging::toJs(rt, 1.2f).asNumber()));
  ABI49_0_0EXPECT_DOUBLE_EQ(1.2, bridging::toJs(rt, 1.2).asNumber());

  ABI49_0_0EXPECT_EQ(
      42,
      static_cast<uint32_t>(
          bridging::toJs(rt, static_cast<uint32_t>(42)).asNumber()));

  ABI49_0_0EXPECT_EQ(
      -42,
      static_cast<uint32_t>(
          bridging::toJs(rt, static_cast<uint32_t>(-42)).asNumber()));

  ABI49_0_0EXPECT_FALSE(
      -42 ==
      static_cast<int32_t>(
          bridging::toJs(rt, static_cast<uint32_t>(-42)).asNumber()));
}

TEST_F(BridgingTest, stringTest) {
  auto string = jsi::String::createFromAscii(rt, "hello");

  ABI49_0_0EXPECT_EQ("hello"s, bridging::fromJs<std::string>(rt, string, invoker));
  ABI49_0_0EXPECT_JSI_THROW(bridging::fromJs<std::string>(rt, jsi::Value(1), invoker));

  ABI49_0_0EXPECT_TRUE(
      jsi::String::strictEquals(rt, string, bridging::toJs(rt, "hello")));
  ABI49_0_0EXPECT_TRUE(
      jsi::String::strictEquals(rt, string, bridging::toJs(rt, "hello"s)));
  ABI49_0_0EXPECT_TRUE(
      jsi::String::strictEquals(rt, string, bridging::toJs(rt, "hello"sv)));
}

TEST_F(BridgingTest, objectTest) {
  auto object = jsi::Object(rt);
  object.setProperty(rt, "foo", "bar");

  auto omap =
      bridging::fromJs<std::map<std::string, std::string>>(rt, object, invoker);
  auto umap = bridging::fromJs<std::unordered_map<std::string, std::string>>(
      rt, object, invoker);
  auto bmap = bridging::fromJs<butter::map<std::string, std::string>>(
      rt, object, invoker);

  ABI49_0_0EXPECT_EQ(1, omap.size());
  ABI49_0_0EXPECT_EQ(1, umap.size());
  ABI49_0_0EXPECT_EQ(1, bmap.size());
  ABI49_0_0EXPECT_EQ("bar"s, omap["foo"]);
  ABI49_0_0EXPECT_EQ("bar"s, umap["foo"]);
  ABI49_0_0EXPECT_EQ("bar"s, bmap["foo"]);

  ABI49_0_0EXPECT_EQ(
      "bar"s,
      bridging::toJs(rt, omap, invoker)
          .getProperty(rt, "foo")
          .asString(rt)
          .utf8(rt));
  ABI49_0_0EXPECT_EQ(
      "bar"s,
      bridging::toJs(rt, umap, invoker)
          .getProperty(rt, "foo")
          .asString(rt)
          .utf8(rt));
  ABI49_0_0EXPECT_EQ(
      "bar"s,
      bridging::toJs(rt, bmap, invoker)
          .getProperty(rt, "foo")
          .asString(rt)
          .utf8(rt));
}

TEST_F(BridgingTest, hostObjectTest) {
  struct TestHostObject : public jsi::HostObject {
    jsi::Value get(jsi::Runtime &rt, const jsi::PropNameID &name) override {
      if (name.utf8(rt) == "test") {
        return jsi::Value(1);
      }
      return jsi::Value::undefined();
    }
  };

  auto hostobject = std::make_shared<TestHostObject>();
  auto object = bridging::toJs(rt, hostobject);

  ABI49_0_0EXPECT_EQ(1, object.getProperty(rt, "test").asNumber());
  ABI49_0_0EXPECT_EQ(
      hostobject, bridging::fromJs<decltype(hostobject)>(rt, object, invoker));
}

TEST_F(BridgingTest, weakbjectTest) {
  auto object = jsi::Object(rt);
  auto weakobject = jsi::WeakObject(rt, object);

  ABI49_0_0EXPECT_TRUE(jsi::Object::strictEquals(
      rt,
      object,
      bridging::fromJs<jsi::WeakObject>(rt, object, invoker)
          .lock(rt)
          .asObject(rt)));

  ABI49_0_0EXPECT_TRUE(jsi::Object::strictEquals(
      rt, object, bridging::toJs(rt, weakobject).asObject(rt)));
}

TEST_F(BridgingTest, arrayTest) {
  auto vec = std::vector({"foo"s, "bar"s});
  auto array = jsi::Array::createWithElements(rt, "foo", "bar");

  ABI49_0_0EXPECT_EQ(
      vec, bridging::fromJs<std::vector<std::string>>(rt, array, invoker));

  ABI49_0_0EXPECT_EQ(vec.size(), bridging::toJs(rt, vec, invoker).size(rt));
  for (size_t i = 0; i < vec.size(); i++) {
    ABI49_0_0EXPECT_EQ(
        vec[i],
        bridging::toJs(rt, vec, invoker)
            .getValueAtIndex(rt, i)
            .asString(rt)
            .utf8(rt));
  }

  ABI49_0_0EXPECT_EQ(2, bridging::toJs(rt, std::make_pair(1, "2"), invoker).size(rt));
  ABI49_0_0EXPECT_EQ(2, bridging::toJs(rt, std::make_tuple(1, "2"), invoker).size(rt));
  ABI49_0_0EXPECT_EQ(2, bridging::toJs(rt, std::array<int, 2>{1, 2}, invoker).size(rt));
  ABI49_0_0EXPECT_EQ(2, bridging::toJs(rt, std::deque<int>{1, 2}, invoker).size(rt));
  ABI49_0_0EXPECT_EQ(2, bridging::toJs(rt, std::list<int>{1, 2}, invoker).size(rt));
  ABI49_0_0EXPECT_EQ(
      2,
      bridging::toJs(rt, std::initializer_list<int>{1, 2}, invoker).size(rt));
}

TEST_F(BridgingTest, functionTest) {
  auto object = jsi::Object(rt);
  object.setProperty(rt, "foo", "bar");

  auto lambda = [](std::map<std::string, std::string> map, std::string key) {
    return map[key];
  };

  auto func = bridging::toJs(rt, lambda, invoker);

  ABI49_0_0EXPECT_EQ(
      "bar"s,
      func.call(rt, object, jsi::String::createFromAscii(rt, "foo"))
          .asString(rt)
          .utf8(rt));

  // Should throw if not enough arguments are passed or are the wrong types.
  ABI49_0_0EXPECT_JSI_THROW(func.call(rt, object));
  ABI49_0_0EXPECT_JSI_THROW(func.call(rt, object, jsi::Value(1)));

  // Test with non-capturing lambda converted to function pointer.
  func = bridging::toJs(rt, +lambda, invoker);

  ABI49_0_0EXPECT_EQ(
      "bar"s,
      func.call(rt, object, jsi::String::createFromAscii(rt, "foo"))
          .asString(rt)
          .utf8(rt));
}

TEST_F(BridgingTest, syncCallbackTest) {
  auto fn = function("(a, b) => a + b");
  auto cb = bridging::fromJs<SyncCallback<std::string(std::string, int)>>(
      rt, fn, invoker);
  auto foo = "foo"s;

  ABI49_0_0EXPECT_EQ("foo1"s, cb(foo, 1)); // Tests lvalue string
  ABI49_0_0EXPECT_EQ("bar2", cb("bar", 2)); // Tests rvalue C string
  ABI49_0_0EXPECT_TRUE(fn.isFunction(rt)); // Ensure the function wasn't invalidated.
}

TEST_F(BridgingTest, syncCallbackImplicitBridgingTest) {
  { // Value
    auto fn = function("(a, b) => a + b");
    auto cb = bridging::fromJs<SyncCallback<std::string(jsi::Value, int)>>(
        rt, fn, invoker);
    jsi::Value foo(jsi::String::createFromAscii(rt, "foo"));

    ABI49_0_0EXPECT_EQ(cb(std::move(foo), 1), "foo1");
    ABI49_0_0EXPECT_EQ(cb(jsi::String::createFromAscii(rt, "bar"), 2), "bar2");
    ABI49_0_0EXPECT_TRUE(fn.isFunction(rt));
  }
  { // Object
    auto fn = function("(a, b) => a.obj + b");
    auto cb = bridging::fromJs<SyncCallback<std::string(jsi::Object, int)>>(
        rt, fn, invoker);

    jsi::Object foo(rt);
    foo.setProperty(rt, "obj", "foo");

    ABI49_0_0EXPECT_EQ(cb(std::move(foo), 1), "foo1");
    ABI49_0_0EXPECT_TRUE(fn.isFunction(rt));
  }
  { // String
    auto fn = function("(a, b) => a + b");
    auto cb = bridging::fromJs<SyncCallback<std::string(jsi::String, int)>>(
        rt, fn, invoker);
    jsi::String foo(jsi::String::createFromAscii(rt, "foo"));

    ABI49_0_0EXPECT_EQ(cb(std::move(foo), 1), "foo1");
    ABI49_0_0EXPECT_EQ(cb(jsi::String::createFromAscii(rt, "bar"), 2), "bar2");
    ABI49_0_0EXPECT_TRUE(fn.isFunction(rt));
  }
  { // Array
    auto fn = function("(a, b) => a[0] + b");
    auto cb = bridging::fromJs<SyncCallback<std::string(jsi::Array, int)>>(
        rt, fn, invoker);

    jsi::Array foo(rt, 1);
    foo.setValueAtIndex(rt, 0, jsi::String::createFromAscii(rt, "foo"));

    ABI49_0_0EXPECT_EQ(cb(std::move(foo), 1), "foo1");
    ABI49_0_0EXPECT_TRUE(fn.isFunction(rt));
  }
}

TEST_F(BridgingTest, asyncCallbackTest) {
  std::string output;

  auto func = std::function<void(std::string)>([&](auto str) { output = str; });

  auto cb = bridging::fromJs<AsyncCallback<decltype(func), std::string>>(
      rt, function("(func, str) => func(str)"), invoker);

  cb(func, "hello");

  flushQueue(); // Run scheduled async work

  ABI49_0_0EXPECT_EQ("hello"s, output);
}

TEST_F(BridgingTest, asyncCallbackImplicitBridgingTest) {
  std::string output;
  auto func = std::function<void(std::string)>([&](auto str) { output = str; });
  { // Value
    auto cb = bridging::fromJs<AsyncCallback<decltype(func), jsi::Value, int>>(
        rt, function("(func, a, b) => func(a + b)"), invoker);
    jsi::Value foo(jsi::String::createFromAscii(rt, "foo"));

    cb(func, std::move(foo), 1);
    flushQueue();
    ABI49_0_0EXPECT_EQ(output, "foo1");

    cb(func, jsi::String::createFromAscii(rt, "bar"), 2);
    flushQueue();
    ABI49_0_0EXPECT_EQ(output, "bar2");

    output.clear();
  }
  { // Object
    auto cb = bridging::fromJs<AsyncCallback<decltype(func), jsi::Object, int>>(
        rt, function("(func, a, b) => func(a.obj + b)"), invoker);

    jsi::Object foo(rt);
    foo.setProperty(rt, "obj", "foo");

    cb(func, std::move(foo), 1);
    flushQueue();
    ABI49_0_0EXPECT_EQ(output, "foo1");

    output.clear();
  }
  { // String
    auto cb = bridging::fromJs<AsyncCallback<decltype(func), jsi::String, int>>(
        rt, function("(func, a, b) => func(a + b)"), invoker);
    jsi::String foo(jsi::String::createFromAscii(rt, "foo"));

    cb(func, std::move(foo), 1);
    flushQueue();
    ABI49_0_0EXPECT_EQ(output, "foo1");

    cb(func, jsi::String::createFromAscii(rt, "bar"), 2);
    flushQueue();
    ABI49_0_0EXPECT_EQ(output, "bar2");

    output.clear();
  }
  { // Array
    auto fn = function("(func, a, b) => func(a[0] + b)");
    auto cb = bridging::fromJs<AsyncCallback<decltype(func), jsi::Array, int>>(
        rt, fn, invoker);

    jsi::Array foo(rt, 1);
    foo.setValueAtIndex(rt, 0, jsi::String::createFromAscii(rt, "foo"));

    cb(func, std::move(foo), 1);
    flushQueue();
    ABI49_0_0EXPECT_EQ(output, "foo1");

    output.clear();
  }
}

TEST_F(BridgingTest, promiseTest) {
  auto func = function(
      "(promise, obj) => {"
      "  promise.then("
      "    (res) => { obj.res = res; },"
      "    (err) => { obj.err = err; }"
      "  )"
      "}");

  auto promise = AsyncPromise<std::vector<std::string>>(rt, invoker);
  auto output = jsi::Object(rt);

  func.call(rt, bridging::toJs(rt, promise, invoker), output);
  promise.resolve({"foo"s, "bar"s});
  flushQueue();

  ABI49_0_0EXPECT_EQ(1, output.getPropertyNames(rt).size(rt));
  ABI49_0_0EXPECT_EQ(2, output.getProperty(rt, "res").asObject(rt).asArray(rt).size(rt));
  ABI49_0_0EXPECT_NO_THROW(promise.resolve({"ignored"}));
  ABI49_0_0EXPECT_NO_THROW(promise.reject("ignored"));

  promise = AsyncPromise<std::vector<std::string>>(rt, invoker);
  output = jsi::Object(rt);

  func.call(rt, bridging::toJs(rt, promise, invoker), output);
  promise.reject("fail");
  flushQueue();

  ABI49_0_0EXPECT_EQ(1, output.getPropertyNames(rt).size(rt));
  ABI49_0_0EXPECT_EQ(
      "fail"s,
      output.getProperty(rt, "err")
          .asObject(rt)
          .getProperty(rt, "message")
          .asString(rt)
          .utf8(rt));
  ABI49_0_0EXPECT_NO_THROW(promise.resolve({"ignored"}));
  ABI49_0_0EXPECT_NO_THROW(promise.reject("ignored"));
}

TEST_F(BridgingTest, optionalTest) {
  ABI49_0_0EXPECT_EQ(
      1, bridging::fromJs<std::optional<int>>(rt, jsi::Value(1), invoker));
  ABI49_0_0EXPECT_EQ(
      1,
      bridging::fromJs<std::optional<int>>(
          rt, std::make_optional(jsi::Value(1)), invoker));
  ABI49_0_0EXPECT_EQ(
      "hi"s,
      bridging::fromJs<std::optional<std::string>>(
          rt,
          std::make_optional(jsi::String::createFromAscii(rt, "hi")),
          invoker));
  ABI49_0_0EXPECT_FALSE(
      bridging::fromJs<std::optional<int>>(rt, jsi::Value::undefined(), invoker)
          .has_value());
  ABI49_0_0EXPECT_FALSE(
      bridging::fromJs<std::optional<int>>(rt, jsi::Value::null(), invoker)
          .has_value());

  ABI49_0_0EXPECT_TRUE(bridging::toJs(rt, std::optional<int>(), invoker).isNull());
  ABI49_0_0EXPECT_EQ(1, bridging::toJs(rt, std::optional<int>(1), invoker).asNumber());
}

TEST_F(BridgingTest, pointerTest) {
  auto str = "hi"s;
  auto unique = std::make_unique<std::string>(str);
  auto shared = std::make_shared<std::string>(str);
  auto weak = std::weak_ptr<std::string>(shared);

  ABI49_0_0EXPECT_EQ(str, bridging::toJs(rt, unique, invoker).asString(rt).utf8(rt));
  ABI49_0_0EXPECT_EQ(str, bridging::toJs(rt, shared, invoker).asString(rt).utf8(rt));
  ABI49_0_0EXPECT_EQ(str, bridging::toJs(rt, weak, invoker).asString(rt).utf8(rt));

  shared.reset();

  ABI49_0_0EXPECT_TRUE(bridging::toJs(rt, weak, invoker).isNull());
}

TEST_F(BridgingTest, supportTest) {
  // Ensure sure can convert some basic types, including primitives that can be
  // trivially converted to JSI values.
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<bool>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<bool, bool>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<bool, jsi::Value &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<int>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<int, int>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<int, jsi::Value &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<double>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<double, double>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<double, jsi::Value &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::string>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::string, jsi::String>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::string, jsi::String &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::set<int>, jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::set<int>, jsi::Array &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::vector<int>, jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<std::vector<int>, jsi::Array &>));
  ABI49_0_0EXPECT_TRUE(
      (bridging::supportsFromJs<std::map<std::string, int>, jsi::Object>));
  ABI49_0_0EXPECT_TRUE(
      (bridging::supportsFromJs<std::map<std::string, int>, jsi::Object &>));

  // Ensure incompatible conversions will fail.
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<bool, jsi::String>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<bool, jsi::String &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<int, jsi::String>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<int, jsi::String &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<double, jsi::String>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<double, jsi::String &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<bool, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<bool, jsi::Object &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<int, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<int, jsi::Object &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<double, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<double, jsi::Object &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<std::string, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<std::string, jsi::Object &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<std::set<int>, jsi::String>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<std::set<int>, jsi::String &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<std::vector<int>, jsi::String>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<std::vector<int>, jsi::String &>));

  // Ensure copying and up/down casting JSI values is also supported.
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Value>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Value, jsi::Value &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Value, jsi::Object>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Value, jsi::Object &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::String>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::String, jsi::String>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::String, jsi::String &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object, jsi::Object>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object, jsi::Object &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object, jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object, jsi::Array &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object, jsi::Function>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Object, jsi::Function &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Array, jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Array, jsi::Array &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Array, jsi::Object>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Array, jsi::Object &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Function>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Function, jsi::Function>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Function, jsi::Function &>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Function, jsi::Object>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsFromJs<jsi::Function, jsi::Object &>));

  // Ensure incorrect casts will fail.
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<jsi::Array, jsi::Function>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<jsi::Array, jsi::Function &>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<jsi::Function, jsi::Array>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsFromJs<jsi::Function, jsi::Array &>));

  // Ensure we can convert some basic types to JSI values.
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<bool>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<int>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<double>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::string>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::string, jsi::String>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::set<int>>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::set<int>, jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::vector<int>>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::vector<int>, jsi::Array>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<std::map<std::string, int>>));
  ABI49_0_0EXPECT_TRUE(
      (bridging::supportsToJs<std::map<std::string, int>, jsi::Object>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<void (*)()>));
  ABI49_0_0EXPECT_TRUE((bridging::supportsToJs<void (*)(), jsi::Function>));

  // Ensure invalid conversions to JSI values are not supported.
  ABI49_0_0EXPECT_FALSE((bridging::supportsToJs<void *>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsToJs<bool, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsToJs<int, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsToJs<double, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsToJs<std::string, jsi::Object>));
  ABI49_0_0EXPECT_FALSE((bridging::supportsToJs<std::vector<int>, jsi::Function>));
}

} // namespace ABI49_0_0facebook::ABI49_0_0React
