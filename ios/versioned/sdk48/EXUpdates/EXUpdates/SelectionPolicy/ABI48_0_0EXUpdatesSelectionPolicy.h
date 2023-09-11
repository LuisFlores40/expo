//  Copyright © 2021 650 Industries. All rights reserved.

#import <ABI48_0_0EXUpdates/ABI48_0_0EXUpdatesLauncherSelectionPolicy.h>
#import <ABI48_0_0EXUpdates/ABI48_0_0EXUpdatesLoaderSelectionPolicy.h>
#import <ABI48_0_0EXUpdates/ABI48_0_0EXUpdatesReaperSelectionPolicy.h>
#import <ABI48_0_0EXUpdates/ABI48_0_0EXUpdatesUpdate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Pluggable class whose essential responsibility is to determine an ordering of the updates stored
 * locally. Ordering updates is important in three separate cases, which map to the three methods
 * here.
 *
 * The default/basic implementations of these methods use an ordering based on `commitTime` (with
 * allowances for EAS Update branches). This has implications for rollbacks (rolled back updates
 * must have a new `id` and `commitTime` in order to take effect), amongst other things, and so this
 * class was designed to be pluggable in order to allow different implementations to be swapped in
 * with relative ease, in situations with different tradeoffs.
 *
 * The three methods are individually pluggable to allow for different behavior of specific parts of
 * the module in different situations. For example, in a development client, our policy for
 * retaining and deleting updates is different than in a release build, so we use a different
 * implementation of ABI48_0_0EXUpdatesReaperSelectionPolicy.
 *
 * Importantly (and non-trivially), expo-updates must be able to make all these determinations
 * without talking to any server. This is because the embedded update can change at any time,
 * without warning, and without the opportunity to talk to the updates server - when a new build is
 * installed via the App Store/TestFlight/sideloading - and this class must be able to decide which
 * update to launch in that case.
 */
@interface ABI48_0_0EXUpdatesSelectionPolicy : NSObject

@property (nonatomic, strong, readonly) id<ABI48_0_0EXUpdatesLauncherSelectionPolicy> launcherSelectionPolicy;
@property (nonatomic, strong, readonly) id<ABI48_0_0EXUpdatesLoaderSelectionPolicy> loaderSelectionPolicy;
@property (nonatomic, strong, readonly) id<ABI48_0_0EXUpdatesReaperSelectionPolicy> reaperSelectionPolicy;

- (instancetype)initWithLauncherSelectionPolicy:(id<ABI48_0_0EXUpdatesLauncherSelectionPolicy>)launcherSelectionPolicy
                          loaderSelectionPolicy:(id<ABI48_0_0EXUpdatesLoaderSelectionPolicy>)loaderSelectionPolicy
                          reaperSelectionPolicy:(id<ABI48_0_0EXUpdatesReaperSelectionPolicy>)reaperSelectionPolicy;

- (nullable ABI48_0_0EXUpdatesUpdate *)launchableUpdateFromUpdates:(NSArray<ABI48_0_0EXUpdatesUpdate *> *)updates filters:(nullable NSDictionary *)filters;
- (NSArray<ABI48_0_0EXUpdatesUpdate *> *)updatesToDeleteWithLaunchedUpdate:(ABI48_0_0EXUpdatesUpdate *)launchedUpdate updates:(NSArray<ABI48_0_0EXUpdatesUpdate *> *)updates filters:(nullable NSDictionary *)filters;
- (BOOL)shouldLoadNewUpdate:(nullable ABI48_0_0EXUpdatesUpdate *)newUpdate withLaunchedUpdate:(nullable ABI48_0_0EXUpdatesUpdate *)launchedUpdate filters:(nullable NSDictionary *)filters;

@end

NS_ASSUME_NONNULL_END
