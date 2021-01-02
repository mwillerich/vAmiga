// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

// This file must conform to standard ANSI-C to be compatible with Swift.

#ifndef _FILE_TYPES_H
#define _FILE_TYPES_H

#include "Aliases.h"

enum_long(FILETYPE)
{
    FILETYPE_UKNOWN,
    FILETYPE_SNAPSHOT,
    FILETYPE_ADF,
    FILETYPE_HDF,
    FILETYPE_EXT,
    FILETYPE_IMG,
    FILETYPE_DMS,
    FILETYPE_EXE,
    FILETYPE_DIR,
    FILETYPE_ROM,
    FILETYPE_EXTENDED_ROM
    // FILETYPE_COUNT
};
typedef FILETYPE FileType;

inline bool isFileType(long value)
{
    return (unsigned long)value < FILETYPE_EXTENDED_ROM;
}

inline const char *FileTypeName(FileType value)
{
    switch (value) {
            
        case FILETYPE_UKNOWN:        return "UNKNOWN";
        case FILETYPE_SNAPSHOT:      return "SNAPSHOT";
        case FILETYPE_ADF:           return "ADF";
        case FILETYPE_HDF:           return "HDF";
        case FILETYPE_EXT:           return "EXT";
        case FILETYPE_IMG:           return "IMG";
        case FILETYPE_DMS:           return "DMS";
        case FILETYPE_EXE:           return "EXE";
        case FILETYPE_DIR:           return "DIR";
        case FILETYPE_ROM:           return "ROM";
        case FILETYPE_EXTENDED_ROM:  return "EXTENDED_ROM";
    }
    return "???";
}

enum_long( RomIdentifier)
{
    ROM_MISSING,
    ROM_UNKNOWN,

    // Boot Roms (A1000)
    ROM_BOOT_A1000_8K,
    ROM_BOOT_A1000_64K,

    // Kickstart V1.x
    ROM_KICK11_31_034,
    ROM_KICK12_33_166,
    ROM_KICK12_33_180,
    ROM_KICK121_34_004,
    ROM_KICK13_34_005,
    ROM_KICK13_34_005_SK,

    // Kickstart V2.x
    ROM_KICK20_36_028,
    ROM_KICK202_36_207,
    ROM_KICK204_37_175,
    ROM_KICK205_37_299,
    ROM_KICK205_37_300,
    ROM_KICK205_37_350,

    // Kickstart V3.x
    ROM_KICK30_39_106,
    ROM_KICK31_40_063,

    // Hyperion
    ROM_HYP314_46_143,

    // Free Kickstart Rom replacements
    ROM_AROS_55696,
    ROM_AROS_55696_EXT,

    // Diagnostic cartridges
    ROM_DIAG11,
    ROM_DIAG12,
    ROM_DIAG121,
    ROM_LOGICA20,

    ROM_CNT
};

static inline bool isRomRevision(long value) { return value >= 0 && value <= ROM_CNT; }

enum_long( FileError)
{
    ERR_FILE_OK,
    
    // General
    ERR_FILE_NOT_FOUND,
    ERR_INVALID_TYPE,
    ERR_CANT_READ,
    ERR_CANT_WRITE,
    ERR_OUT_OF_MEMORY,
    ERR_UNKNOWN,
    
    // Snapshots
    ERR_UNSUPPORTED_SNAPSHOT,
    
    // Encrypted Roms
    ERR_MISSING_ROM_KEY,
    ERR_INVALID_ROM_KEY
};

enum_long( BootBlockType)
{
    BB_STANDARD,
    BB_VIRUS,
    BB_CUSTOM
};

#endif
