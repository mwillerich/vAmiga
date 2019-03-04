// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Amiga.h"

Blitter::Blitter()
{
    setDescription("Blitter");
    
    registerSnapshotItems(vector<SnapshotItem> {
        
        { &bltcon0,    sizeof(bltcon0),    0 },
        { &bltcon1,    sizeof(bltcon1),    0 },

        { &bltapt,     sizeof(bltapt),     0 },
        { &bltbpt,     sizeof(bltbpt),     0 },
        { &bltcpt,     sizeof(bltcpt),     0 },
        { &bltdpt,     sizeof(bltdpt),     0 },

        { &bltafwm,    sizeof(bltafwm),    0 },
        { &bltalwm,    sizeof(bltalwm),    0 },

        { &bltsize,    sizeof(bltsize),    0 },

        { &bltamod,    sizeof(bltamod),    0 },
        { &bltbmod,    sizeof(bltbmod),    0 },
        { &bltcmod,    sizeof(bltcmod),    0 },
        { &bltdmod,    sizeof(bltdmod),    0 },

        { &anew,       sizeof(anew),       0 },
        { &bnew,       sizeof(bnew),       0 },
        { &ahold,      sizeof(ahold),      0 },
        { &bhold,      sizeof(bhold),      0 },
        { &chold,      sizeof(chold),      0 },
        { &dhold,      sizeof(dhold),      0 },
        { &ashift,     sizeof(ashift),     0 },
        { &bshift,     sizeof(bshift),     0 },

    });
}

BlitterInfo
Blitter::getInfo()
{
    BlitterInfo info;
    
    /* Note: We call the Blitter 'active' if there is a pending message in the
     * Copper event slot.
     */
    info.active  = amiga->dma.eventHandler.isPending(BLT_SLOT);
    info.bltcon0 = bltcon0;
    info.bltcon1 = bltcon1;
    info.bltapt  = bltapt;
    info.bltbpt  = bltbpt;
    info.bltcpt  = bltcpt;
    info.bltdpt  = bltdpt;
    info.bltafwm = bltafwm;
    info.bltalwm = bltalwm;
    info.bltsize = bltsize;
    info.bltamod = bltamod;
    info.bltbmod = bltbmod;
    info.bltcmod = bltcmod;
    info.bltdmod = bltdmod;
    info.anew = anew;
    info.bnew = bnew;
    info.ahold = ahold;
    info.bhold = bhold;
    info.chold = chold;
    info.dhold = dhold;

    return info;
}

void
Blitter::_powerOn()
{
    
}

void
Blitter::_powerOff()
{
    
}

void
Blitter::_reset()
{
    
}

void
Blitter::_ping()
{
    
}

void
Blitter::_dump()
{
    plainmsg("   bltcon0: %X\n", bltcon0);
    plainmsg("   bltcon1: %X\n", bltcon1);
    plainmsg("    bltapt: %X\n", bltapt);
    plainmsg("    bltbpt: %X\n", bltbpt);
    plainmsg("    bltcpt: %X\n", bltcpt);
    plainmsg("    bltdpt: %X\n", bltdpt);
    plainmsg("   bltafwm: %X\n", bltafwm);
    plainmsg("   bltalwm: %X\n", bltalwm);
    plainmsg("   bltsize: %X\n", bltsize);
    plainmsg("   bltamod: %X\n", bltamod);
    plainmsg("   bltbmod: %X\n", bltbmod);
    plainmsg("   bltcmod: %X\n", bltcmod);
    plainmsg("   bltdmod: %X\n", bltdmod);
    plainmsg("      anew: %X\n", anew);
    plainmsg("      bnew: %X\n", bnew);
    plainmsg("     ahold: %X\n", ahold);
    plainmsg("     bhold: %X\n", bhold);
    plainmsg("     chold: %X\n", chold);
    plainmsg("     dhold: %X\n", dhold);
}

void
Blitter::pokeBLTCON0(uint16_t value)
{
    debug("pokeBLTCON0(%X)\n", value);
    bltcon0 = value;
}

void
Blitter::pokeBLTCON1(uint16_t value)
{
    debug("pokeBLTCON1(%X)\n", value);
    bltcon1 = value;
}

void
Blitter::pokeBLTAPTH(uint16_t value)
{
    debug("pokeBLTAPTH(%X)\n", value);
    bltapt = REPLACE_HI_WORD(bltapt, value & 0x7);
}

void
Blitter::pokeBLTAPTL(uint16_t value)
{
    debug("pokeBLTAPTL(%X)\n", value);
    bltapt = REPLACE_LO_WORD(bltapt, value);
}

void
Blitter::pokeBLTBPTH(uint16_t value)
{
    debug("pokeBLTBPTH(%X)\n", value);
    bltbpt = REPLACE_HI_WORD(bltbpt, value & 0x7);
}

void
Blitter::pokeBLTBPTL(uint16_t value)
{
    debug("pokeBLTBPTL(%X)\n", value);
    bltbpt = REPLACE_LO_WORD(bltbpt, value);
}

void
Blitter::pokeBLTCPTH(uint16_t value)
{
    debug("pokeBLTCPTH(%X)\n", value);
    bltcpt = REPLACE_HI_WORD(bltcpt, value & 0x7);
}

void
Blitter::pokeBLTCPTL(uint16_t value)
{
    debug("pokeBLTCPTL(%X)\n", value);
    bltcpt = REPLACE_LO_WORD(bltcpt, value);
}

void
Blitter::pokeBLTDPTH(uint16_t value)
{
    debug("pokeBLTDPTH(%X)\n", value);
    bltdpt = REPLACE_HI_WORD(bltdpt, value & 0x7);
}

void
Blitter::pokeBLTDPTL(uint16_t value)
{
    debug("pokeBLTDPTL(%X)\n", value);
    bltdpt = REPLACE_LO_WORD(bltdpt, value);
}

void
Blitter::pokeBLTAFWM(uint16_t value)
{
    debug("pokeBLTAFWM(%X)\n", value);
    bltafwm = value;
}

void
Blitter::pokeBLTALWM(uint16_t value)
{
    debug("pokeBLTALWM(%X)\n", value);
    bltalwm = value;
}

void
Blitter::pokeBLTSIZE(uint16_t value)
{
    debug("pokeBLTSIZE(%X)\n", value);
    bltsize = value;
}

void
Blitter::scheduleNextEvent(Cycle offset, EventID id, int64_t data)
{
    amiga->dma.eventHandler.scheduleNextEvent(BLT_SLOT, offset, id, data);
}

void
Blitter::cancelEvent()
{
    amiga->dma.eventHandler.cancelEvent(BLT_SLOT);
}

void
Blitter::serviceEvent(EventID id, int64_t data)
{
    uint16_t instr;
    int16_t incPC = 1;
    
    debug("Servicing Blitter event %d\n", id);
    
    switch (id) {
            
        case BLT_INIT:
            
            if (bltLINE()) {
                // TODO
            } else {
                
                // Load micro instruction code
                
                // Set counters
                wcounter = bltsizeW();
                hcounter = bltsizeH();
                
                // Schedule code to be executed
                scheduleNextEvent(1, BLT_EXECUTE);
            }
            break;
            
        case BLT_EXECUTE:
            
            // Execute next Blitter micro instruction
            instr = microInstr[bltpc];
            
            if (instr & WRITE_D) {
                
                amiga->mem.pokeChip16(bltdpt, dhold);
                INC_OCS_PTR(bltdpt, 2 + (isLastWord() ? bltdmod : 0));
            }
            
            if (instr & HOLD_A) {
                
                ahold = ashift >> bltASH() & 0xFFFF;
            }

            if (instr & HOLD_B) {
                
                bhold = bshift >> bltBSH() & 0xFFFF;
            }
            
            if (instr & HOLD_D) {
                
                dhold = 0;

                // Run the minterm generator
                if (bltcon0 & 0b10000000) dhold |=  ahold &  bhold &  chold;
                if (bltcon0 & 0b01000000) dhold |=  ahold &  bhold & ~chold;
                if (bltcon0 & 0b00100000) dhold |=  ahold &  bhold &  chold;
                if (bltcon0 & 0b00010000) dhold |=  ahold & ~bhold & ~chold;
                if (bltcon0 & 0b00001000) dhold |= ~ahold &  bhold &  chold;
                if (bltcon0 & 0b00000100) dhold |= ~ahold &  bhold & ~chold;
                if (bltcon0 & 0b00000010) dhold |= ~ahold & ~bhold &  chold;
                if (bltcon0 & 0b00000001) dhold |= ~ahold & ~bhold & ~chold;
                
                // Run the fill logic circuit
                // TODO
                
                // Move to next coordinate or terminate the blit
                if (wcounter > 1) {
                    wcounter--;
                } else {
                    if (hcounter > 1) {
                        wcounter = bltsizeW();
                        hcounter--;
                    } else {
                        // We are done
                        cancelEvent();
                        break;
                    }
                }
            }
            
            if (instr & FETCH_A) {
                
                setanew(amiga->mem.peek16(bltapt));
                INC_OCS_PTR(bltapt, 2 + (isLastWord() ? bltamod : 0));
            }
            
            if (instr & FETCH_B) {
                
                setbnew(amiga->mem.peek16(bltbpt));
                INC_OCS_PTR(bltbpt, 2 + (isLastWord() ? bltbmod : 0));
            }

            if (instr & FETCH_C) {
                
                chold = amiga->mem.peek16(bltcpt);
                INC_OCS_PTR(bltcpt, 2 + (isLastWord() ? bltcmod : 0));
            }
            
            if (instr & LOOPBACK) {
                
                if (wcounter > 1 || hcounter > 1)
                    incPC = -(instr & 7);
            }
            
            // Continue running the blitter
            bltpc += incPC;
            scheduleNextEvent(1, BLT_EXECUTE);
            break;
            
        default:
            
            assert(false);
            break;
    }
}

void
Blitter::buildMicrocode()
{
    /* The following code is inspired by Table 6.2 of the HRM:
     *
     *           Active
     * BLTCON0  Channels            Cycle sequence
     *    F     A B C D    A0 B0 C0 -- A1 B1 C1 D0 A2 B2 C2 D1 D2
     *    E     A B C      A0 B0 C0 A1 B1 C1 A2 B2 C2
     *    D     A B   D    A0 B0 -- A1 B1 D0 A2 B2 D1 -- D2
     *    C     A B        A0 B0 -- A1 B1 -- A2 B2
     *    B     A   C D    A0 C0 -- A1 C1 D0 A2 C2 D1 -- D2
     *    A     A   C      A0 C0 A1 C1 A2 C2
     *    9     A     D    A0 -- A1 D0 A2 D1 -- D2
     *    8     A          A0 -- A1 -- A2
     *    7       B C D    B0 C0 -- -- B1 C1 D0 -- B2 C2 D1 -- D2
     *    6       B C      B0 C0 -- B1 C1 -- B2 C2
     *    5       B   D    B0 -- -- B1 D0 -- B2 D1 -- D2
     *    4       B        B0 -- -- B1 -- -- B2
     *    3         C D    C0 -- -- C1 D0 -- C2 D1 -- D2
     *    2         C      C0 -- C1 -- C2
     *    1           D    D0 -- D1 -- D2
     *    0                -- -- -- --
     */
    
    uint8_t A = !!bltUSEA();
    uint8_t B = !!bltUSEB();
    uint8_t C = !!bltUSEC();
    uint8_t D = !!bltUSED();
    
    switch ((A << 3) | (B << 2) | (C << 1) | D) {
            
        case 0b1111: { // A0 B0 C0 -- A1 B1 C1 D0 A2 B2 C2 D1 D2
            
            uint16_t prog[] = {
                
                FETCH_A,
                FETCH_B | HOLD_A,
                FETCH_C | HOLD_B,
                HOLD_D,
                
                FETCH_A,
                FETCH_B | HOLD_A,
                FETCH_C | HOLD_B,
                WRITE_D | HOLD_D | LOOPBACK3,
                
                WRITE_D
            };
            memcpy(microInstr, prog, sizeof(prog));
            break;
        }
            
        case 0b1110: { // A0 B0 C0 A1 B1 C1 A2 B2 C2
            
            uint16_t prog[] = {
                
                FETCH_A,
                FETCH_B | HOLD_A,
                FETCH_C | HOLD_B,
                
                FETCH_A | HOLD_D,
                FETCH_B | HOLD_A,
                FETCH_C | HOLD_B | LOOPBACK2,
                
                HOLD_D
            };
            memcpy(microInstr, prog, sizeof(prog));
            break;
        }
            
        default:
            
            fatalError("Unimplemented Blitter configuration\n");
            assert(false);
    }

}
