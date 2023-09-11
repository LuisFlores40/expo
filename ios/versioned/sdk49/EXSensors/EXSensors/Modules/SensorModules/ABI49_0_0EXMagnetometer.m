// Copyright 2015-present 650 Industries. All rights reserved.

#import <ABI49_0_0EXSensors/ABI49_0_0EXMagnetometer.h>
#import <ABI49_0_0ExpoModulesCore/ABI49_0_0EXMagnetometerInterface.h>

@implementation ABI49_0_0EXMagnetometer

ABI49_0_0EX_EXPORT_MODULE(ExponentMagnetometer);

- (const NSString *)updateEventName
{
  return @"magnetometerDidUpdate";
}

- (id)getSensorServiceFromModuleRegistry:(ABI49_0_0EXModuleRegistry *)moduleRegistry
{
  return [moduleRegistry getModuleImplementingProtocol:@protocol(ABI49_0_0EXMagnetometerInterface)];
}

- (void)setUpdateInterval:(double)updateInterval onSensorService:(id)sensorService
{
  [sensorService setMagnetometerUpdateInterval:updateInterval];
}

- (BOOL)isAvailable:(id)sensorService
{
  return [sensorService isMagnetometerAvailable];
}

- (void)subscribeToSensorService:(id)sensorService withHandler:(void (^)(NSDictionary *event))handlerBlock
{
  [sensorService sensorModuleDidSubscribeForMagnetometerUpdates:self withHandler:handlerBlock];
}

- (void)unsubscribeFromSensorService:(id)sensorService
{
  [sensorService sensorModuleDidUnsubscribeForMagnetometerUpdates:self];
}

@end
