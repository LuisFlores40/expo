// Copyright 2018-present 650 Industries. All rights reserved.

#if __has_include(<ABI47_0_0EXNotifications/ABI47_0_0EXServerRegistrationModule.h>)

#import <ABI47_0_0EXNotifications/ABI47_0_0EXServerRegistrationModule.h>

NS_ASSUME_NONNULL_BEGIN

@interface ABI47_0_0EXScopedServerRegistrationModule : ABI47_0_0EXServerRegistrationModule

- (instancetype)initWithScopeKey:(NSString *)scopeKey;

@end

NS_ASSUME_NONNULL_END

#endif
