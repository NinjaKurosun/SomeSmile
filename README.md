# SomeSmile - ***a free, [open source](https://en.wikipedia.org/wiki/Open_source) and not yet cross-platform***

<div align="center">
  <img src="https://github.com/Sonic-TheHedgehog/SomeSmile/blob/main/SomeSmile/Screenshots/5.PNG" alt="screenshot" />
</div>

## Table Of Contents
- [Structure]()
- [Start](#Start)
- [Usage Guide](#Usage-Guide)
- [How To Build](#How-To-Build)
- [Screenshots](#Screenshots)
- [End](#End)

## Structure
```
  SomeSmile-main/
  ├────SomeSmile/
  │    ├────SomeSmileDll/
  │    │    └────Switcher/
  │    │         ├────Switcher/
  │    │         └→Switcher.sln // To Open In Visual Studio
  │    ├────Screenshots/
  │    └────SomeSmileApp/
  │         ├────Resource/
  │         │    ├────Translations/
  │         │    ├────QStyle/
  │         │    ├────iconSource/
  │         │    ├→SomeSmileIcon.ico
  │         │    └→AboutIcon.png
  │         └→SomeSmile.pro // To Open In QtCreator
  └→README.md //You See
```

## Start
- [Download](https://github.com/Sonic-TheHedgehog/SomeSmile/releases).
- Move the archive to any path and unzip it.
- Run.
- Your mind: Wow, you did it!
- Let's get [Usage Guide](#Usage-Guide)!

## Usage Guide
- Do not delete line 71 in the SSMainWindow file.
  <div>
    <img src="https://github.com/Sonic-TheHedgehog/SomeSmile/blob/main/SomeSmile/Screenshots/6.png" alt="screenshot" />
  </div>
- To translate the entered Key into Value, you must press Ctrl
- I think this program is intuitive (should be)
- The End

## How To Build
1. Open it SomeSmile.pro in Qt Creator, select the configuration and press Ctrl+R.
2. Next, compile the library (`Switcher` from the `SomeSmileDll` folder) in Visual Studio in all configurations, then rename the output files to `Switcher32.dll` and `Switcher64.dll`, depending on the bits.
3. Copy the `Switcher32.dll` and `Switcher64.dll` files to the `release` folder, and run `windeployqt.exe`.


## Screenshots
<div align="center">
  <img src="https://github.com/Sonic-TheHedgehog/SomeSmile/blob/main/SomeSmile/Screenshots/1.png" alt="screenshot1" />
  <img src="https://github.com/Sonic-TheHedgehog/SomeSmile/blob/main/SomeSmile/Screenshots/2.png" alt="screenshot2" />
  <img src="https://github.com/Sonic-TheHedgehog/SomeSmile/blob/main/SomeSmile/Screenshots/4.png" alt="screenshot4" />
</div> 

## End
> Our Telegram [Channel](https://t.me/SomeSmile_ru_en) and [ChatGroup](https://t.me/SomeSmile_ru_en).
> The license [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl.html)
