<p align="center">
      <img src="https://github.com/Scaarj/heretic/assets/25565781/4a7a8432-c7fa-45d6-adc0-11dbae6558cc" width="320">
</p>

<p align="center">
   <img src="https://img.shields.io/badge/Sdk%20Version-4.0.2.89-green" alt="SDK Version">
   <img src="https://img.shields.io/badge/Game%20Version-1.0.77-blue" alt="Game Version">
   <img src="https://img.shields.io/badge/License-Apache%20License-yellow" alt="License">
</p>

## About

Heretic is a dark fantasy first-person shooter video game released in December 1994. It was developed by Raven Software and published by id Software through GT Interactive. This project based on anothor port Linux Heretic 1.03 by Andre` Werthmann. You may check [doomwiki](https://doomwiki.org/wiki/Linux_Heretic) for inforamtion and download Linux Heretic 1.03 source code from [here](https://www.doomworld.com/3ddownloads/ports/linux-heretic-1.03.tar.gz).

In this repository, the port of the game to the mobile operating system Aurora Os. Source code was ported from C to C++ using the Aurora Framework. All control is through the touch screen and special buttons. The render was saved from the original game and the screen matrix is ​​converted to QImage and displayed through the qml engine at 18-19 frames per second (fps is original). Game event loop works in parallel with QT eventloop via QTimer calls.

<img src="https://github.com/Scaarj/heretic/assets/25565781/d3ef5398-3012-4304-bd94-3c37b71c006c" width="320">
<img src="https://github.com/Scaarj/heretic/assets/25565781/506740b9-40bd-4ed8-8e25-3d97fca96749" width="320">
<img src="https://github.com/Scaarj/heretic/assets/25565781/2a85ca27-1b28-4473-bff9-31e302265c3b" width="320">
<img src="https://github.com/Scaarj/heretic/assets/25565781/f827329e-8837-43a1-9118-ea2939d54798" width="320">

https://github.com/Scaarj/heretic/assets/25565781/df9ca86f-ccfe-4fa5-a3c2-03105008ee52

## Control

### Intro screen
- Tap for unclock main menu screen
### Main menu screen
- Double tap anywhere on the game screen (everything except black areas) to bring up the menu
- Double tap anywhere on the game screen (everything except black areas) outside the menu to close it
- Double tap on menu items for menu selection
- Double tap outside the menu for going previous menu
- Left swipe for decrease settings
- Right swipe for increase settings
### Game Screen
- Touch move in left side screen for wasd-moving in total in 8 directions.
- Touch move in right side screen for moving camera view.

### Settings
- Changing mouse-x and mouse-y sensivity
- Volume level
- Screen size - increase/decrease frame of screen

## Todo list

- Sound player
- Flight controll
- Map viewing
- Game controllers - ps4, bt-keyboard, etc
- Android port
- Network game (wifi, bluethooth)

## Download

- Devices - [armv7hl](https://disk.yandex.ru/d/WtclhRIuZ58yrg)
- Emulator - [i486](https://disk.yandex.ru/d/BlcEpgYJrYxOoA)

## Developers

- [Steve Dubrov](https://github.com/Scaarj)

## License

Copyright 2023 Steve Dubrov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

[Apache 2.0 ](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
