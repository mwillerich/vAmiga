// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------
// THIS FILE MUST CONFORM TO ANSI-C TO BE COMPATIBLE WITH SWIFT
// -----------------------------------------------------------------------------

#pragma once

#include "Aliases.h"
#include "AudioFilter.h"

//
// Enumerations
//

enum_long(SMP_METHOD)
{
    SMP_NONE,
    SMP_NEAREST,
    SMP_LINEAR,

    SMP_COUNT
};
typedef SMP_METHOD SamplingMethod;

//
// Structures
//

typedef struct
{
    i8 state;
    bool dma;
    u16 audlenLatch;
    u16 audlen;
    u16 audperLatch;
    i32 audper;
    u16 audvolLatch;
    u16 audvol;
    u16 auddat;
}
AudioChannelInfo;

typedef struct
{
    AudioChannelInfo channel[4];
}
AudioInfo;

typedef struct
{
    // Selects how the audio buffer is resampled to match the target frequency
    SamplingMethod samplingMethod;

    // The selected audio filter
    FilterType filterType;

    // If set to true, the Amiga can't deactivate the filter
    bool filterAlwaysOn;

    // Master volume (left and right channel)
    i64 volL;
    i64 volR;

    // Channel volumes and pan factors
    i64 vol[4];
    i64 pan[4];
}
MuxerConfig;

typedef struct
{
    long bufferUnderflows;
    long bufferOverflows;
}
MuxerStats;
