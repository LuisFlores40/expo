/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI49_0_0RCTBridgeModuleDecorator.h"

@implementation ABI49_0_0RCTBridgeModuleDecorator

- (instancetype)initWithViewRegistry:(ABI49_0_0RCTViewRegistry *)viewRegistry
                      moduleRegistry:(ABI49_0_0RCTModuleRegistry *)moduleRegistry
                       bundleManager:(ABI49_0_0RCTBundleManager *)bundleManager
                   callableJSModules:(ABI49_0_0RCTCallableJSModules *)callableJSModules
{
  if (self = [super init]) {
    _viewRegistry_DEPRECATED = viewRegistry;
    _moduleRegistry = moduleRegistry;
    _bundleManager = bundleManager;
    _callableJSModules = callableJSModules;
  }
  return self;
}

- (void)attachInteropAPIsToModule:(id<ABI49_0_0RCTBridgeModule>)bridgeModule
{
  /**
   * Attach the ABI49_0_0RCTViewRegistry to this TurboModule, which allows this TurboModule
   * To query a ABI49_0_0React component's UIView, given its ABI49_0_0ReactTag.
   *
   * Usage: In the TurboModule @implementation, include:
   *   `@synthesize viewRegistry_DEPRECATED = _viewRegistry_DEPRECATED`
   */
  if ([bridgeModule respondsToSelector:@selector(setViewRegistry_DEPRECATED:)]) {
    bridgeModule.viewRegistry_DEPRECATED = _viewRegistry_DEPRECATED;
  }

  /**
   * Attach the ABI49_0_0RCTBundleManager to this TurboModule, which allows this TurboModule to
   * read from/write to the app's bundle URL.
   *
   * Usage: In the TurboModule @implementation, include:
   *   `@synthesize bundleManager = _bundleManager`
   */
  if ([bridgeModule respondsToSelector:@selector(setBundleManager:)]) {
    bridgeModule.bundleManager = _bundleManager;
  }

  /**
   * Attach the ABI49_0_0RCTCallableJSModules to this TurboModule, which allows this TurboModule
   * to call JS Module methods.
   *
   * Usage: In the TurboModule @implementation, include:
   *   `@synthesize callableJSModules = _callableJSModules`
   */
  if ([bridgeModule respondsToSelector:@selector(setCallableJSModules:)]) {
    bridgeModule.callableJSModules = _callableJSModules;
  }

  /**
   * Attach the ABI49_0_0RCTModuleRegistry to this TurboModule, which allows this TurboModule
   * to require other TurboModules/NativeModules.
   *
   * Usage: In the TurboModule @implementation, include:
   *   `@synthesize moduleRegistry = _moduleRegistry`
   */
  if ([bridgeModule respondsToSelector:@selector(setModuleRegistry:)]) {
    bridgeModule.moduleRegistry = _moduleRegistry;
  }
}

@end
