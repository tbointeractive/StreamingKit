//
//  STKMixableQueueEntry.h
//  StreamingKit
//
//  Created by James Gordon on 09/12/2014.
//

#import "STKDataSource.h"
#import "STKQueueEntry.h"


typedef enum
{
    STKMixableQueueEntryErrorEof,
    STKMixableQueueEntryErrorDataSourceError
}
STKMixableQueueEntryError;

@class STKMixableQueueEntry;

@protocol STKMixableQueueEntryErrorDelegate <NSObject>

-(void) mixableEntry:(STKMixableQueueEntry *)entry didError:(STKMixableQueueEntryError)error;

@end

@interface STKMixableQueueEntry : STKQueueEntry<STKDataSourceDelegate>
{
@public
    AudioBuffer* _pcmAudioBuffer;
    
    volatile UInt32 _pcmBufferFrameStartIndex;
    volatile UInt32 _pcmBufferUsedFrameCount;
    volatile UInt32 _pcmBufferTotalFrameCount;
    volatile UInt32 _pcmBufferFrameSizeInBytes;
    
    Float64 _fadeFrom;
    Float64 _fadeRatio;
    
    BOOL _waiting;
}

@property (readwrite, weak) id<STKMixableQueueEntryErrorDelegate> errorDelegate;

- (void)setFadeoutAt:(Float64)fadeFrame overDuration:(Float64)fadeForFrames trackDuration:(Float64)totalFrames;
- (void)fadeFromNow;
- (void)beginEntryLoad;
- (void)continueBuffering;
- (void)wakeupPlaybackThread;
- (void)tidyUp;

- (void)changeToURL:(NSURL *)url;

@end
