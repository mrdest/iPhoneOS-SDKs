//
//  MPMediaLibrary.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaEntity;
@class MPMediaQuery;
@class MPMediaPlaylist;
@class MPMediaPlaylistCreationMetadata;

// MPMediaLibrary represents a collection of media on a device, and can be used 
// to fetch items and playlists from the user's synced iTunes library.
// 
// See MPMediaQuery.h for a list of common queries or to build a custom query 
// from a chain of filter predicates.

// -----------------------------------------------------------------------------

typedef NS_ENUM(NSInteger, MPMediaLibraryAuthorizationStatus) {
    MPMediaLibraryAuthorizationStatusNotDetermined = 0,
    MPMediaLibraryAuthorizationStatusDenied,
    MPMediaLibraryAuthorizationStatusRestricted,
    MPMediaLibraryAuthorizationStatusAuthorized,
} NS_ENUM_AVAILABLE_IOS(9_3);

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(3.0, 10.12.2, 3.0)
@interface MPMediaLibrary : NSObject <NSSecureCoding>

+ (MPMediaLibrary *)defaultMediaLibrary;

// Returns the date at which the media library was last modified.
@property (nonatomic, readonly) NSDate *lastModifiedDate;

// MPMediaLibraryDidChangeNotification will be posted when a sync happens.
- (void)beginGeneratingLibraryChangeNotifications;
- (void)endGeneratingLibraryChangeNotifications;

+ (MPMediaLibraryAuthorizationStatus)authorizationStatus NS_AVAILABLE_IOS(9_3);
+ (void)requestAuthorization:(void (^)(MPMediaLibraryAuthorizationStatus status))handler NS_AVAILABLE_IOS(9_3);

- (void)addItemWithProductID:(NSString *)productID completionHandler:(nullable void (^)(NSArray <__kindof MPMediaEntity *> *entities, NSError * __nullable error))completionHandler NS_AVAILABLE_IOS(9_3);

/*!
 * Finds the playlist associated with the UUID.
 * If the playlist exists, the creation metadata is ignored.
 * If no such playlist exists and creation metadata is valid, a playlist associated the UUID will be created.
 *
 * @discussion The UUID should typically be pre-generated to avoid creating a new playlist with every call.
 */

- (void)getPlaylistWithUUID:(NSUUID *)uuid creationMetadata:(nullable MPMediaPlaylistCreationMetadata *)creationMetadata completionHandler:(void (^)(MPMediaPlaylist * __nullable playlist, NSError * __nullable error))completionHandler NS_AVAILABLE_IOS(9_3);

@end


// -----------------------------------------------------------------------------
// Notifications

// Any items or playlists which were previously cached should be re-evaluated from queries when MPMediaLibraryDidChangeNotification is posted.
MP_EXTERN __TVOS_PROHIBITED NSString * const MPMediaLibraryDidChangeNotification;

NS_ASSUME_NONNULL_END
