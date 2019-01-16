// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

import Foundation

extension PreferencesController {
    
    func refreshEmulatorTab() {
        
        track()
        
        guard let c64 = proxy, let controller = myController else { return }
        
        // VC1541
        emuWarpLoad.state = c64.warpLoad() ? .on : .off
        emuDriveSounds.state = c64.drive1.sendSoundMessages() ? .on : .off
        
        // Screenshots
        emuScreenshotSourcePopup.selectItem(withTag: controller.screenshotSource)
        emuScreenshotTargetPopup.selectItem(withTag: controller.screenshotTargetIntValue)
        
        // Documents
        emuCloseWithoutAskingButton.state = controller.closeWithoutAsking ? .on : .off
        emuEjectWithoutAskingButton.state = controller.ejectWithoutAsking ? .on : .off
        
        // Miscellaneous
        emuPauseInBackground.state = controller.pauseInBackground ? .on : .off
        emuAutoSnapshots.state = c64.takeAutoSnapshots() ? .on : .off
        emuSnapshotInterval.integerValue = c64.snapshotInterval()
        emuSnapshotInterval.isEnabled = c64.takeAutoSnapshots()
    }

    //
    // Action methods (VC1541)
    //
    
    @IBAction func emuWarpLoadAction(_ sender: NSButton!) {
        
        proxy?.setWarpLoad(sender.state == .on)
        refresh()
    }
    
    @IBAction func emuDriveSoundsAction(_ sender: NSButton!) {
        
        proxy?.drive1.setSendSoundMessages(sender.state == .on)
        proxy?.drive2.setSendSoundMessages(sender.state == .on)
        refresh()
    }
    
    
    //
    // Action methods (Screenshots)
    //
    
    @IBAction func emuScreenshotSourceAction(_ sender: NSPopUpButton!) {
        
        myController?.screenshotSource = sender.selectedTag()
        refresh()
    }
    
    @IBAction func emuScreenshotTargetAction(_ sender: NSPopUpButton!) {
        
        myController?.screenshotTargetIntValue = sender.selectedTag()
        refresh()
    }
    
    
    //
    // Action methods (User Dialogs)
    //
    
    @IBAction func emuCloseWithoutAskingAction(_ sender: NSButton!) {
        
        myController?.closeWithoutAsking = (sender.state == .on)
        refresh()
    }
    
    @IBAction func emuEjectWithoutAskingAction(_ sender: NSButton!) {
        
        myController?.ejectWithoutAsking = (sender.state == .on)
        refresh()
    }
    
    
    //
    // Action methods (Miscellaneous)
    //
    
    @IBAction func emuPauseInBackgroundAction(_ sender: NSButton!) {
        
        myController?.pauseInBackground = (sender.state == .on)
        refresh()
    }
    
    @IBAction func emuAutoSnapshotAction(_ sender: NSButton!) {
        
        proxy?.setTakeAutoSnapshots(sender.state == .on)
        refresh()
    }
    
    @IBAction func emuSnapshotIntervalAction(_ sender: NSTextField!) {
        
        track("\(sender.integerValue)")
        if sender.integerValue > 0 {
            proxy?.setSnapshotInterval(sender.integerValue)
        } else {
            track("IGNORING")
        }
        refresh()
    }
    
    
    //
    // Action methods (Misc)
    //
    
    @IBAction func emuFactorySettingsAction(_ sender: Any!) {
        
        myController?.resetEmulatorUserDefaults()
        refresh()
    }
}

