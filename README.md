# Settlers 4 unit selection limit remover

By default, you can only select at most 100 units. This mod aims to remove that limit so that you can manage huge armies with ease.

![186-units-selected](units-selected.png)

There is a [German translation for this README](README_DE.md). Please note that it may be outdated.



## Requirements

You need the **History Edition of The Settlers 4**. Note that this mod will not work with the original gold version. The mod is working and tested on a S4_Main.exe with the following MD5 checksum:  `bcdd32fd35f85a8eb96641dcc4eacfa9`. 



## How to use

1. [Download a release](https://github.com/nyfrk/S4_UnlimitedSelection/releases). Unpack it to wherever you like. Just make sure the files `Injector.exe` and `S4_UnlimitedSelection.dll` both reside in the same directory.
2. Launch the `Injector.exe` by double clicking it. A console window should open.
3. Start the game and wait until the console windows reports a successful injection.
4. Close the console window if you like. The mod will still continue to work. 

The injector begins to inject the DLL when the game is started. Note that you do not have to use my injector. Feel free to use whatever injector you want. Make sure to **not rename** the `S4_UnlimitedSelection.dll` file when using my injector. Otherwise, the injector won't pick it up.



## Uninstall

The mod will not modify any files permanently. Just remove both downloaded files if you do not want to use this mod anymore. 



## Known Problems

* The game is limited to draw at most 100 health bubbles onto your screen. That means that you have to play with the zoom level to inspect the health of of your army chunk-wise. 
* Group assignments are still limited to max 100 units per group.
* Not all selection tools are implemented yet. Actually only the box selection tool is implemented. Using Alt+Click does still employ the original limit of 100 units per selection.
* Crashes occur when selecting too many units.  I have therefore set the limit to 250 units per selection to prevent these crashes. I hope that we can push this limit even further in the future.
* This mod does not support the gold edition yet.



## How does it work

The mod will modify code sections of the game during runtime. It will also add some code to the game to fix accruing crashes. If you happen to use another game version, you must locate the code sections documented at the bottom of the [cheat-unlimited-selection.cpp](S4_UnlimitedSelection/cheat-unlimited-selection.cpp#L240) file. Just adjust the addresses and patterns in that file. Then you can recompile it yourself. However the automatic pattern searcher should already increase the compatibility even across different game versions. Here is a short summary of the addresses that are modified by this mod. Note that it may not be complete. See the source code for a more complete list.

```
buffer overflow (fatal error) fix for the health bubbles:
S4_Main.exe+26041B - 8B 0D 2C75A701        - mov ecx,[S4_Main.exe+105752C]

remove the limit for box selections:
S4_Main.exe+ED241 - 0F83 84000000         - jae S4_Main.exe+ED2CB

remove the limit for units that can be moved by right clicking:
S4_Main.exe+EC8CF - B8 64000000           - mov eax,00000064

ClearSelection() function of the game:
S4_Main.exe+EE530 - A1 F836AA01           - mov eax,[S4_Main.exe+10836F8]
```



## Compile it yourself

Download Visual Studio 2017 or 2019 with the C++ toolchain. I configured to build it with the Windows XP compatible **v141_xp** toolchain. However you should be able to change the toolchain to whatever you like. No additional libraries are required so it should compile out of the box. If you do a debug build the mod spawns a console upon loading and will output various debug information and addresses to it. 



## Contribute

The official repository of this project is available at https://github.com/nyfrk/S4_UnlimitedSelection. Feel free to fork this repository. You can use everything for whatever you like. Please see [LICENSE.md](LICENSE.md) for details. However please open a pull request if you manage to fix some of the unsolved problems of this mod. 
