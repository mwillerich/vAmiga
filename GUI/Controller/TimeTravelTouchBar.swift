// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

/*

@available(OSX 10.12.2, *)
extension NSTouchBarItem.Identifier {
    
    static let ttscrubber = NSTouchBarItem.Identifier("com.vAmiga.TouchBarItem.ttscrubber")
}

@available(OSX 10.12.2, *)
class TimeTravelTouchBar: NSTouchBar {
    
    var parentItem: NSPopoverTouchBarItem?
    var c: MyController?
    
    func dismiss(_ sender: Any?) {

        guard let popover = parentItem else { return }
        popover.dismissPopover(sender)
    }
    
    override init() {

        super.init()
        delegate = self
        defaultItemIdentifiers = [.ttscrubber]
    }
    
    required init?(coder aDecoder: NSCoder) {

        fatalError("init(coder:) has not been implemented")
    }
    
    convenience init(parent: NSPopoverTouchBarItem?, controller: MyController?) {

        self.init()
        self.parentItem = parent
        self.c = controller
    }
}

@available(OSX 10.12.2, *)
extension TimeTravelTouchBar: NSTouchBarDelegate {

    func touchBar(_ touchBar: NSTouchBar, makeItemForIdentifier identifier: NSTouchBarItem.Identifier) -> NSTouchBarItem? {
        
       track()
        
        switch identifier {
        default:
            return nil
        }
    }
}

 */
