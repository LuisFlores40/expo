/**
 * Copyright (c) 2015-present, Horcrux.
 * All rights reserved.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI49_0_0RNSVGLine.h"
#import <ABI49_0_0React/ABI49_0_0RCTLog.h>

#ifdef ABI49_0_0RCT_NEW_ARCH_ENABLED
#import <ABI49_0_0React/ABI49_0_0RCTConversions.h>
#import <ABI49_0_0React/ABI49_0_0RCTFabricComponentsPlugins.h>
#import <react/renderer/components/rnsvg/ComponentDescriptors.h>
#import <react/renderer/components/view/conversions.h>
#import "ABI49_0_0RNSVGFabricConversions.h"
#endif // ABI49_0_0RCT_NEW_ARCH_ENABLED

@implementation ABI49_0_0RNSVGLine

#ifdef ABI49_0_0RCT_NEW_ARCH_ENABLED
using namespace ABI49_0_0facebook::ABI49_0_0React;

- (instancetype)initWithFrame:(CGRect)frame
{
  if (self = [super initWithFrame:frame]) {
    static const auto defaultProps = std::make_shared<const ABI49_0_0RNSVGLineProps>();
    _props = defaultProps;
  }
  return self;
}

#pragma mark - ABI49_0_0RCTComponentViewProtocol

+ (ComponentDescriptorProvider)componentDescriptorProvider
{
  return concreteComponentDescriptorProvider<ABI49_0_0RNSVGLineComponentDescriptor>();
}

- (void)updateProps:(Props::Shared const &)props oldProps:(Props::Shared const &)oldProps
{
  const auto &newProps = *std::static_pointer_cast<const ABI49_0_0RNSVGLineProps>(props);

  self.x1 = [ABI49_0_0RNSVGLength lengthWithString:ABI49_0_0RCTNSStringFromString(newProps.x1)];
  self.y1 = [ABI49_0_0RNSVGLength lengthWithString:ABI49_0_0RCTNSStringFromString(newProps.y1)];
  self.x2 = [ABI49_0_0RNSVGLength lengthWithString:ABI49_0_0RCTNSStringFromString(newProps.x2)];
  self.y2 = [ABI49_0_0RNSVGLength lengthWithString:ABI49_0_0RCTNSStringFromString(newProps.y2)];

  setCommonRenderableProps(newProps, self);
  _props = std::static_pointer_cast<ABI49_0_0RNSVGLineProps const>(props);
}

- (void)prepareForRecycle
{
  [super prepareForRecycle];
  _x1 = nil;
  _y1 = nil;
  _x2 = nil;
  _y2 = nil;
}
#endif // ABI49_0_0RCT_NEW_ARCH_ENABLED

- (void)setX1:(ABI49_0_0RNSVGLength *)x1
{
  if ([x1 isEqualTo:_x1]) {
    return;
  }
  [self invalidate];
  _x1 = x1;
}

- (void)setY1:(ABI49_0_0RNSVGLength *)y1
{
  if ([y1 isEqualTo:_y1]) {
    return;
  }
  [self invalidate];
  _y1 = y1;
}

- (void)setX2:(ABI49_0_0RNSVGLength *)x2
{
  if ([x2 isEqualTo:_x2]) {
    return;
  }
  [self invalidate];
  _x2 = x2;
}

- (void)setY2:(ABI49_0_0RNSVGLength *)y2
{
  if ([y2 isEqualTo:_y2]) {
    return;
  }
  [self invalidate];
  _y2 = y2;
}

- (CGPathRef)getPath:(CGContextRef)context
{
  CGMutablePathRef path = CGPathCreateMutable();
  CGFloat x1 = [self relativeOnWidth:self.x1];
  CGFloat y1 = [self relativeOnHeight:self.y1];
  CGFloat x2 = [self relativeOnWidth:self.x2];
  CGFloat y2 = [self relativeOnHeight:self.y2];
  CGPathMoveToPoint(path, nil, x1, y1);
  CGPathAddLineToPoint(path, nil, x2, y2);

  return (CGPathRef)CFAutorelease(path);
}

@end

#ifdef ABI49_0_0RCT_NEW_ARCH_ENABLED
Class<ABI49_0_0RCTComponentViewProtocol> ABI49_0_0RNSVGLineCls(void)
{
  return ABI49_0_0RNSVGLine.class;
}
#endif // ABI49_0_0RCT_NEW_ARCH_ENABLED
