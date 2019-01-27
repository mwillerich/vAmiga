//
// This file is part of VirtualC64 - A cycle accurate Commodore 64 emulator
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
//

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>
#import "C64_types.h"
#import "basic.h"

// Forward declarations of proxy classes
@class MyController;
@class C64Proxy;
@class CPUProxy;
@class MemoryProxy;
@class VICProxy;
@class SIDProxy;
@class KeyboardProxy;
@class ControlPortProxy;
@class DriveProxy;
@class DiskProxy;
@class MouseProxy;

@class AnyC64FileProxy;
@class AnyArchiveProxy;
@class AnyDiskProxy;
@class D64FileProxy;
@class G64FileProxy;

// Forward declarations of wrappers for C++ classes.
// We wrap classes into normal C structs to avoid any reference to C++.

struct C64Wrapper;
struct CpuWrapper;
struct MemoryWrapper;
struct VicWrapper;
struct SidBridgeWrapper;
struct KeyboardWrapper;
struct ControlPortWrapper;
struct IecWrapper;
struct DriveWrapper;
struct DiskWrapper;
struct MouseWrapper;
struct AnyC64FileWrapper;


// -----------------------------------------------------------------------------
//                                   C64 proxy
// -----------------------------------------------------------------------------

@interface C64Proxy : NSObject {
    
    struct C64Wrapper *wrapper;
    
    CPUProxy *cpu;
    MemoryProxy *mem;
    VICProxy *vic;
    SIDProxy *sid;
    KeyboardProxy *keyboard;
    ControlPortProxy *port1;
    ControlPortProxy *port2;
    DriveProxy *drive1;
    DriveProxy *drive2;
    MouseProxy *mouse;
}

@property (readonly) struct C64Wrapper *wrapper;
@property (readonly) CPUProxy *cpu;
@property (readonly) MemoryProxy *mem;
@property (readonly) VICProxy *vic;
@property (readonly) SIDProxy *sid;
@property (readonly) KeyboardProxy *keyboard;
@property (readonly) ControlPortProxy *port1;
@property (readonly) ControlPortProxy *port2;
@property (readonly) DriveProxy *drive1;
@property (readonly) DriveProxy *drive2;
@property (readonly) MouseProxy *mouse;

- (void) kill;

- (DriveProxy *)drive:(NSInteger)nr;

- (void) ping;
- (void) dump;
- (BOOL) developmentMode;

// Configuring the emulator
- (NSInteger) model;
- (void) setModel:(NSInteger)value;

// Accessing the message queue
- (Message)message;
- (void) addListener:(const void *)sender function:(Callback *)func;
- (void) removeListener:(const void *)sender;

// Running the emulator
- (void) powerUp;
- (void) run;
- (void) halt;
- (void) suspend;
- (void) resume;
- (BOOL) isRunnable;
- (BOOL) isRunning;
- (BOOL) isHalted;
- (void) step;
- (void) stepOver;

// Managing the execution thread
- (BOOL) warp;
- (BOOL) alwaysWarp;
- (void) setAlwaysWarp:(BOOL)b;
- (BOOL) warpLoad;
- (void) setWarpLoad:(BOOL)b;

// Handling ROMs
- (BOOL) isBasicRom:(NSURL *)url;
- (BOOL) loadBasicRom:(NSURL *)url;
- (BOOL) isBasicRomLoaded;
- (uint64_t) basicRomFingerprint;
- (BOOL) isCharRom:(NSURL *)url;
- (BOOL) loadCharRom:(NSURL *)url;
- (BOOL) isCharRomLoaded;
- (uint64_t) charRomFingerprint;
- (BOOL) isKernalRom:(NSURL *)url;
- (BOOL) loadKernalRom:(NSURL *)url;
- (BOOL) isKernalRomLoaded;
- (uint64_t) kernalRomFingerprint;
- (BOOL) isVC1541Rom:(NSURL *)url;
- (BOOL) loadVC1541Rom:(NSURL *)url;
- (BOOL) isVC1541RomLoaded;
- (uint64_t) vc1541RomFingerprint;

- (BOOL) isRom:(NSURL *)url;
- (BOOL) loadRom:(NSURL *)url;

@end


// -----------------------------------------------------------------------------
//                                 CPU proxy
// -----------------------------------------------------------------------------

@interface CPUProxy : NSObject {
    
    struct CpuWrapper *wrapper;
}

- (CPUInfo) getInfo;
- (void) dump;

- (BOOL) tracing;
- (void) setTracing:(BOOL)b;

- (UInt64) cycle;
- (uint16_t) pc;
- (void) setPC:(uint16_t)pc;
- (void) setSP:(uint8_t)sp;
- (void) setA:(uint8_t)a;
- (void) setX:(uint8_t)x;
- (void) setY:(uint8_t)y;
- (void) setNflag:(BOOL)b;
- (void) setZflag:(BOOL)b;
- (void) setCflag:(BOOL)b;
- (void) setIflag:(BOOL)b;
- (void) setBflag:(BOOL)b;
- (void) setDflag:(BOOL)b;
- (void) setVflag:(BOOL)b;

- (BOOL) breakpoint:(uint16_t)addr;
- (void) setBreakpoint:(uint16_t)addr;
- (void) deleteBreakpoint:(uint16_t)addr;
- (void) toggleBreakpoint:(uint16_t)addr;

- (NSInteger) recordedInstructions;
- (RecordedInstruction) readRecordedInstruction;
- (RecordedInstruction) readRecordedInstruction:(NSInteger)previous;

- (DisassembledInstruction) disassemble:(uint16_t)addr hex:(BOOL)h;
- (DisassembledInstruction) disassembleRecordedInstr:(RecordedInstruction)instr hex:(BOOL)h;

@end


// -----------------------------------------------------------------------------
//                                 Memory proxy
// -----------------------------------------------------------------------------

@interface MemoryProxy : NSObject {
    
    struct MemoryWrapper *wrapper;
}

- (void) dump;

- (NSInteger) ramInitPattern;
- (void) setRamInitPattern:(NSInteger)type;
- (void) eraseWithPattern:(NSInteger)type;

- (void) deleteBasicRom;
- (void) deleteCharacterRom;
- (void) deleteKernalRom;

- (MemoryType) peekSource:(uint16_t)addr;
- (MemoryType) pokeTarget:(uint16_t)addr;

- (uint8_t) spypeek:(uint16_t)addr source:(MemoryType)source;
- (uint8_t) spypeek:(uint16_t)addr;
- (uint8_t) spypeekIO:(uint16_t)addr;

- (void) poke:(uint16_t)addr value:(uint8_t)value target:(MemoryType)target;
- (void) poke:(uint16_t)addr value:(uint8_t)value;
- (void) pokeIO:(uint16_t)addr value:(uint8_t)value;

@end


// -----------------------------------------------------------------------------
//                                 CIA proxy
// -----------------------------------------------------------------------------
/*
@interface CIAProxy : NSObject {
    
    struct CiaWrapper *wrapper;
}

- (CIAInfo) getInfo;
- (void) dump;
- (BOOL) tracing;
- (void) setTracing:(BOOL)b;

- (NSInteger) model;
- (void) setModel:(NSInteger)value;
- (BOOL) emulateTimerBBug;
- (void) setEmulateTimerBBug:(BOOL)value;

- (void) poke:(uint16_t)addr value:(uint8_t)value;

@end

*/

// -----------------------------------------------------------------------------
//                                VICII proxy
// -----------------------------------------------------------------------------


@interface VICProxy : NSObject {
    
	struct VicWrapper *wrapper;
}

- (NSInteger) model;
- (void) setModel:(NSInteger)value;
- (NSInteger) videoPalette;
- (void) setVideoPalette:(NSInteger)value;
- (NSInteger) glueLogic;
- (void) setGlueLogic:(NSInteger)value;
- (BOOL) hasGrayDotBug;
- (BOOL) emulateGrayDotBug;
- (void) setEmulateGrayDotBug:(BOOL)value;
- (BOOL) isPAL;

// - (void *) screenBuffer;
// - (NSColor *) color:(NSInteger)nr;
// - (UInt32) rgbaColor:(NSInteger)nr palette:(VICPalette)palette;
- (double)brightness;
- (void)setBrightness:(double)value;
- (double)contrast;
- (void)setContrast:(double)value;
- (double)saturation;
- (void)setSaturation:(double)value;

- (VICInfo) getInfo;
- (SpriteInfo) getSpriteInfo:(NSInteger)sprite;
- (void) dump;

- (void) setMemoryBankAddr:(uint16_t)addr;
- (void) setScreenMemoryAddr:(uint16_t)addr;
- (void) setCharacterMemoryAddr:(uint16_t)addr;

- (void) setDisplayMode:(DisplayMode)mode;
- (void) setScreenGeometry:(ScreenGeometry)mode;
- (void) setHorizontalRasterScroll:(uint8_t)offset;
- (void) setVerticalRasterScroll:(uint8_t)offset;

- (void) setSpriteEnabled:(NSInteger)nr value:(BOOL)flag;
- (void) toggleSpriteEnabled:(NSInteger)nr;
- (void) setSpriteX:(NSInteger)nr value:(NSInteger)x;
- (void) setSpriteY:(NSInteger)nr value:(NSInteger)y;
- (void) setSpritePtr:(NSInteger)nr value:(NSInteger)ptr;
- (void) setSpriteStretchX:(NSInteger)nr value:(BOOL)flag;
- (void) toggleSpriteStretchX:(NSInteger)nr;
- (void) setSpriteStretchY:(NSInteger)nr value:(BOOL)flag;
- (void) toggleSpriteStretchY:(NSInteger)nr;
- (void) setSpriteColor:(NSInteger)nr value:(int)c;
- (void) setSpritePriority:(NSInteger)nr value:(BOOL)flag;
- (void) toggleSpritePriority:(NSInteger)nr;
- (void) setSpriteMulticolor:(NSInteger)nr value:(BOOL)flag;
- (void) toggleSpriteMulticolor:(NSInteger)nr;

- (void) setIrqOnSpriteSpriteCollision:(BOOL)value;
- (void) toggleIrqOnSpriteSpriteCollision;
- (void) setIrqOnSpriteBackgroundCollision:(BOOL)value;
- (void) toggleIrqOnSpriteBackgroundCollision;

- (void) setRasterInterruptLine:(uint16_t)line;
- (void) setRasterInterruptEnabled:(BOOL)b;
- (void) toggleRasterInterruptFlag;

- (BOOL) hideSprites;
- (void) setHideSprites:(BOOL)b;
- (BOOL) showIrqLines;
- (void) setShowIrqLines:(BOOL)b;
- (BOOL) showDmaLines;
- (void) setShowDmaLines:(BOOL)b;

@end


// -----------------------------------------------------------------------------
//                                 SID proxy
// -----------------------------------------------------------------------------

@interface SIDProxy : NSObject {
    
    struct SidBridgeWrapper *wrapper;
}

- (SIDInfo) getInfo;
- (VoiceInfo) getVoiceInfo:(NSInteger)voice;
- (void) dump;

- (BOOL) reSID;
- (void) setReSID:(BOOL)b;
- (uint32_t) sampleRate;
- (void) setSampleRate:(uint32_t)rate;
- (BOOL) audioFilter;
- (void) setAudioFilter:(BOOL)b;
- (NSInteger) samplingMethod;
- (void) setSamplingMethod:(NSInteger)value;
- (NSInteger) model;
- (void) setModel:(NSInteger)value;

- (NSInteger) ringbufferSize;
- (float) ringbufferData:(NSInteger)offset;
// - (double) fillLevel;
// - (NSInteger) bufferUnderflows;
// - (NSInteger) bufferOverflows;

- (void) readMonoSamples:(float *)target size:(NSInteger)n;
- (void) readStereoSamples:(float *)target1 buffer2:(float *)target2 size:(NSInteger)n;
- (void) readStereoSamplesInterleaved:(float *)target size:(NSInteger)n;

- (void) rampUp;
- (void) rampUpFromZero;
- (void) rampDown;

@end


// -----------------------------------------------------------------------------
//                               Keyboard proxy
// -----------------------------------------------------------------------------

@interface KeyboardProxy : NSObject {
    
    struct KeyboardWrapper *wrapper;
}

- (void) dump;

- (void) pressKeyAtRow:(NSInteger)row col:(NSInteger)col;
- (void) pressRestoreKey;

- (void) releaseKeyAtRow:(NSInteger)row col:(NSInteger)col;
- (void) releaseRestoreKey;
- (void) releaseAll;

- (BOOL) leftShiftIsPressed;
- (BOOL) rightShiftIsPressed;
- (BOOL) controlIsPressed;
- (BOOL) commodoreIsPressed;

- (BOOL) shiftLockIsHoldDown;
- (void) lockShift;
- (void) unlockShift;

- (BOOL) inUpperCaseMode;

@end


// -----------------------------------------------------------------------------
//                             Control port proxy
// -----------------------------------------------------------------------------

@interface ControlPortProxy : NSObject {
    
    struct ControlPortWrapper *wrapper;
}

- (void) dump;
- (BOOL) autofire;
- (void) setAutofire:(BOOL)value;
- (NSInteger) autofireBullets;
- (void) setAutofireBullets:(NSInteger)value;
- (float) autofireFrequency;
- (void) setAutofireFrequency:(float)value;

- (void) trigger:(JoystickEvent)event;

@end


// -----------------------------------------------------------------------------
//                             Expansion port proxy
// -----------------------------------------------------------------------------

/*
@interface ExpansionPortProxy : NSObject {
    
    struct ExpansionPortWrapper *wrapper;
}

- (void) dump;

- (BOOL) cartridgeAttached;
- (CartridgeType) cartridgeType;
- (BOOL) attachGeoRamCartridge:(NSInteger)capacity;
- (void) attachIsepicCartridge;
- (void) detachCartridgeAndReset;

- (NSInteger) numButtons;
- (NSString *) getButtonTitle:(NSInteger)nr;
- (void) pressButton:(NSInteger)nr;
- (void) releaseButton:(NSInteger)nr;

- (BOOL) hasSwitch;
- (NSInteger) switchPosition;
- (NSString *) switchDescription:(NSInteger)pos;
- (BOOL) validSwitchPosition:(NSInteger)pos;
- (BOOL) switchIsNeutral;
- (BOOL) switchIsLeft;
- (BOOL) switchIsRight;
- (void) setSwitchPosition:(NSInteger)pos;

- (BOOL) hasLed;
- (BOOL) led;
- (void) setLed:(BOOL)value;

- (BOOL) hasBattery;
- (void) setBattery:(BOOL)value;

@end

*/


// -----------------------------------------------------------------------------
//                                Drive proxy
// -----------------------------------------------------------------------------

@interface DriveProxy : NSObject {
    
    struct DriveWrapper *wrapper;
    
    // Sub proxys
    DiskProxy *disk;
}

@property (readonly) struct DriveWrapper *wrapper;
@property (readonly) DiskProxy *disk;

- (BOOL) isPoweredOn;
- (void) powerOn;
- (void) powerOff;
- (void) togglePowerSwitch;

- (void) deleteRom;

- (BOOL) redLED;
- (BOOL) hasDisk;
- (BOOL) hasModifiedDisk;
- (void) setModifiedDisk:(BOOL)b;
- (void) prepareToInsert;
- (void) prepareToEject;
- (void) ejectDisk;
- (BOOL) writeProtected;
- (void) setWriteProtection:(BOOL)b;
- (BOOL) hasWriteProtectedDisk;
- (BOOL) sendSoundMessages;
- (void) setSendSoundMessages:(BOOL)b;

- (Halftrack) halftrack;
- (void) setTrack:(Track)t;
- (void) setHalftrack:(Halftrack)ht;
- (uint16_t) sizeOfCurrentHalftrack;
- (uint16_t) offset;
- (void) setOffset:(uint16_t)value;
- (uint8_t) readBitFromHead;
- (void) writeBitToHead:(uint8_t)value;

- (void) moveHeadUp;
- (void) moveHeadDown;
- (BOOL) isRotating;
- (void) rotateDisk;
- (void) rotateBack;

@end


// -----------------------------------------------------------------------------
//                                Disk proxy
// -----------------------------------------------------------------------------

@interface DiskProxy : NSObject {
    
    struct DiskWrapper *wrapper;
}

@property (readonly) struct DiskWrapper *wrapper;

- (void) dump;
- (BOOL)writeProtected;
- (void)setWriteProtection:(BOOL)b;
- (void)toggleWriteProtection;
- (NSInteger)nonemptyHalftracks;
- (void)analyzeTrack:(Track)t;
- (void)analyzeHalftrack:(Halftrack)ht;
- (NSInteger)numErrors;
- (NSString *)errorMessage:(NSInteger)nr;
- (NSInteger)firstErroneousBit:(NSInteger)nr;
- (NSInteger)lastErroneousBit:(NSInteger)nr;
- (SectorInfo)sectorInfo:(Sector)s;
- (const char *)diskNameAsString;
- (const char *)trackDataAsString;
- (const char *)sectorHeaderAsString:(Sector)nr;
- (const char *)sectorDataAsString:(Sector)nr;
@end



// -----------------------------------------------------------------------------
//                                 Mouse proxy
// -----------------------------------------------------------------------------

@interface MouseProxy : NSObject {
    
    struct MouseWrapper *wrapper;
}

- (NSInteger) model;
- (void) setModel:(NSInteger)model;
- (void) connect:(NSInteger)toPort;
- (void) disconnect;
- (void) setXY:(NSPoint)pos;
- (void) setLeftButton:(BOOL)pressed;
- (void) setRightButton:(BOOL)pressed;

@end
