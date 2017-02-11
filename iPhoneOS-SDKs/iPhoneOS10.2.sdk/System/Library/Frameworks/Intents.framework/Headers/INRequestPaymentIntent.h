//
//  INRequestPaymentIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;
@class INCurrencyAmount;
@class INCurrencyAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INRequestPaymentIntent : INIntent

- (instancetype)initWithPayer:(nullable INPerson *)payer
               currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         note:(nullable NSString *)note NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payer;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *currencyAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *note;

@end

@class INRequestPaymentIntentResponse;

/*!
 @brief Protocol to declare support for handling an INRequestPaymentIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INRequestPaymentIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INRequestPaymentIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  requestPaymentIntent The input intent
 @param  completion The response handling block takes a INRequestPaymentIntentResponse containing the details of the result of having executed the intent

 @see  INRequestPaymentIntentResponse
 */

- (void)handleRequestPayment:(INRequestPaymentIntent *)intent
                  completion:(void (^)(INRequestPaymentIntentResponse *response))completion NS_SWIFT_NAME(handle(requestPayment:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  requestPaymentIntent The input intent
 @param  completion The response block contains an INRequestPaymentIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INRequestPaymentIntentResponse

 */

- (void)confirmRequestPayment:(INRequestPaymentIntent *)intent
                   completion:(void (^)(INRequestPaymentIntentResponse *response))completion NS_SWIFT_NAME(confirm(requestPayment:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  requestPaymentIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolvePayerForRequestPayment:(INRequestPaymentIntent *)intent
                       withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayer(forRequestPayment:with:));

- (void)resolveCurrencyAmountForRequestPayment:(INRequestPaymentIntent *)intent
                                withCompletion:(void (^)(INCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(forRequestPayment:with:));

- (void)resolveNoteForRequestPayment:(INRequestPaymentIntent *)intent
                      withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveNote(forRequestPayment:with:));

@end

NS_ASSUME_NONNULL_END
