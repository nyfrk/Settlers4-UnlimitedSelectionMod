# The Settlers 4: Unlimited Selection Mod

By default, you can only select at most 100 units. This mod aims to remove that limit so that you can manage huge armies with ease.

![units-selected](units-selected.png)

There is a [German translation for this README](README_DE.md). Please note that it may be outdated.



## Features

* Increase the selection limit to 2500 units per selection
* Extended controls for your selections:
  * You can right click or left click unit-icons in the side panel to include or exclude them from the selection
  * You can right click the red plus button to deselect all wounded units (left click in contrast selects all wounded units)
  * You can right click the groups menu button to deselect all units that are already assigned to a group
* Compatibility: Works with the Gold Edition and the History Edition of The Settlers 4
* Multiplayer interoperability: You can play multiplayer with participants that do not use this mod
* Open Source: Most parts of the project including patterns, offsets, enums and structs will become open source soon!



## How to use

There are two methods on how you can use this mod. If you are a developer or just want to quickly try the mod you probably want to use the provided injector (method 1). The Injector is mainly targeted to developers to enable fast loading and unloading of the mod without having to restart the game for each build. Method 2 is more suited for end-users who want the mod to get loaded whenever the game starts. You can use an ASI loader to achieve that. 

#### Method 1: Provided Injector

1. [Download a release](https://github.com/nyfrk/S4_UnlimitedSelection/releases). Unpack it to wherever you like. Just make sure the files `Injector.exe` and `S4_UnlimitedSelection.asi` both reside in the same directory.
2. Launch the `Injector.exe` by double clicking it. A console window should open.
3. Start the game and wait until the console windows reports a successful injection.
4. Close the console window if you like. The mod will still continue to work. 

The injector begins to inject the mod when the game is started. Make sure to **not rename** the `S4_UnlimitedSelection.asi`. Otherwise, the injector won't pick it up. 

The mod will not modify any files permanently. Just remove both downloaded files if you do not want to use this mod anymore. 

#### Method 2: Using ASI Loader

The advantage of using an ASI loader is that you can install multiple mods just by pasting them into a predestined directory. I recommend [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) as it works nicely with the History Edition of The Settlers 4 and does not require any configuration. It does not seem to work with the Gold Edition though. Let me know if you find an ASI Loader that works with the Gold Edition. If you already have an ASI loader installed skip the first steps and jump directly to step 4. 

1. [Download a release of the Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases). Make sure to choose the x86 Version (*not* x64).
2. Unpack it to the very same directory of your S4_Main.exe. This resides in you installation directory of The Settlers 4. For the gold edition it is in a subfolder named exe/
3. In the same directory: 
3.1. Rename the `binkw32.dll` to `binkw32Hooked.dll`
3.2. Rename the `dinput8.dll` that you just unpacked to `binkw32.dll`
3.3. Create a directory in the very same folder and name it `plugins`
4. [Download a release of the Unlimited Selection Mod](https://github.com/nyfrk/S4_UnlimitedSelection/releases). Unpack the `S4_UnlimitedSelection.asi`  to the `plugins` directory. Note that `Injector.exe` is not required. 
5. Start the game. The mod will load automatically.

To uninstall the mod remove `S4_UnlimitedSelection.asi` from the `plugins` directory. If you do not want to use the ASI loader anymore just reverse the described steps. 



## Known Problems

* Group assignments are still limited to max 100 units per group. 
* Uplay interferes with the injection when used to start the game. Just restart the injector when the game has launched.



## Issues and Questions

The project uses the Github Issue tracker. Please open a ticket [here](https://github.com/nyfrk/Settlers4-UnlimitedSelectionMod/issues). 



## Contribute

The official repository of this project is available at https://github.com/nyfrk/Settlers4-UnlimitedSelectionMod. You can contribute in the following ways:

* Answer questions
* Submit bugs or help to verify them
* Review code and test the proposed fixes
* Submit pull requests

#### Compile it yourself

Download Visual Studio 2017 or 2019 with the C++ toolchain. The project is configured to build it with the Windows XP compatible **v141_xp** toolchain. However, you should be able to change the toolchain to whatever you like. No additional libraries are required so it should compile out of the box. If you want to use rendering features (like menus, text, etc) you will have to install the [latest DirectX 9 SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812). Although the code should compile even without the SDK since it will skip the rendering parts in case the SDK is missing. 

#### Future work

* A Framework: Some hooks are interesting for various other mods too. Especially the tick hook that you can use to inject your own events. 

  It is a good idea to create a shared library and a framework for plugins. Creating plugins would become easier as the framework could manage all the hooking, patching and struct mapping whereas plugin developers would just have to access the API of the framework. This would reduce incompatibilities between mods as the shared library could delegate hook access to multiple plugins. So, if you use parts of this project (especially the same hooks / patches) for your own project, please consider making it open source. If you open source your project too, we can easily alter the projects to use a framework in the future. 



## License

The project is licensed under the [MIT](LICENSE.md) License. 
