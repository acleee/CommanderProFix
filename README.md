CommanderProFix
==============

This is a forked version of the [Lilu](https://github.com/acidanthera/Lilu) plugin [RestrictEvents](https://github.com/acidanthera/RestrictEvents) that has been modified to only prevent  `/usr/libexec/ioupsd` from running. This removes the "UPS battery backup" warning at the cost of disabling macOS's UPS support.

### Background / Why does this exist?
There exists a USB UPS that is called the Commander Pro. When plugged into an internal USB header the Corsair Commander Pro also appears with the name "Commander Pro". macOS (lazily) checks the USB name instead of the vendor/product IDs and believes there is a UPS plugged in when it detects the Corsair Commander Pro.

I got the idea for this after seeing [this thread](https://www.tonymacx86.com/threads/solved-catalina-thinks-my-corsair-commander-pro-is-a-ups.288458/) on tonymacx86, which showed how the fix shown (which basically overwrote `ioupsd` to sleep forever) did not work on Big Sur.

In my case, I have a custom water cooled PC, with my fans and a temperature probe running thru the Commander Pro. I wanted to be able to monitor the fan RPM and my coolant temperature, to verify the fan curves stayed applied in macOS but also because I like having those temps readily accessible so I can see what the computer is "doing". CommanderProFix _does_ work on Big Sur, and as of yet nobody has yelled at me telling me this is a horrible idea or horrible way to fix this ¯\\\_(ツ)_/¯

### Perks of CommanderProFix
- No need to disable the Commander Pro in your USB map, which means: 
  - You can still fully access USB headers connected to the Commander Pro
  - [liquidctl](https://github.com/liquidctl/liquidctl) remains usable for pulling fan and temperature sensor info / RGB control
  - [OpenRGB](https://gitlab.com/CalcProgrammer1/OpenRGB) might work (will need to test - my ASUS Aura device showed on the same USB port as the Commander Pro)
  - macOS no longer harrasses you about your "UPS" battery being dead

### Cons
- If you have a USB UPS, you probably can't poll it for data and have it integrate into macOS anymore.

### Boot arguments (same as RestrictEvents)
- `-revoff` (or `-liluoff`) to disable
- `-revdbg` (or `-liludbgall`) to enable verbose logging (in DEBUG builds)
- `-revbeta` (or `-lilubetaall`) to enable on macOS older than 10.8 or newer than 11
- `-revproc` to enable verbose process logging (in DEBUG builds)

### Credits
- [Acidanthera](https://github.com/vit9696) for RestrictEvents  
- [Apple](https://www.apple.com) for macOS  
- [vit9696](https://github.com/vit9696) for [Lilu.kext](https://github.com/vit9696/Lilu) and great help in implementing some features 
