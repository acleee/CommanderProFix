CommanderProFix
==============

This is a forked version of the [Lilu](https://github.com/acidanthera/Lilu) plugin [RestrictEvents](https://github.com/acidanthera/RestrictEvents) that has been modified to only prevent  `/usr/libexec/ioupsd` from running. This removes the "UPS battery backup" warning at the cost of disabling macOS's UPS support.


#### Boot arguments
- `-revoff` (or `-liluoff`) to disable
- `-revdbg` (or `-liludbgall`) to enable verbose logging (in DEBUG builds)
- `-revbeta` (or `-lilubetaall`) to enable on macOS older than 10.8 or newer than 11
- `-revproc` to enable verbose process logging (in DEBUG builds)

#### Credits
- [Acidanthera](https://github.com/vit9696) for RestrictEvents  
- [Apple](https://www.apple.com) for macOS  
- [vit9696](https://github.com/vit9696) for [Lilu.kext](https://github.com/vit9696/Lilu) and great help in implementing some features 
