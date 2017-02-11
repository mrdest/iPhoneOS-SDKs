//
//  INDateComponentsResolutionResult.m
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
@interface INDateComponentsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given NSDateComponents. The resolvedDateComponents can be different than the original NSDateComponents. This allows app extensions to apply business logic constraints. For example, the extension could round the interval to the nearest day.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedDateComponents:(NSDateComponents *)resolvedDateComponents NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided dateComponentss.
+ (instancetype)disambiguationWithDateComponentsToDisambiguate:(NSArray<NSDateComponents *> *)dateComponentsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the dateComponents with which the user wants to continue.
+ (instancetype)confirmationRequiredWithDateComponentsToConfirm:(nullable NSDateComponents *)dateComponentsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
