[English](README.md) [فارسی](README.persian.md)

# Ahang
Ahang is a simple music player.

## Warning: 🚧this project is not ready for daily use🚧

Ahang is yet another simple and minimalistic music player like G4Music and Amberol wtitten modern C++. You just select a folder and it shows the musics inside it. Then you click and play. Simple. but there are some key feature that makes it a bit different:

## Key Features
- built in AdBlocker for songs that put website names on audio tags: So people that download for free won't be bothered.
- Non Gstreamer: unlike literally almost Every music player in the linux world. this software is not using Gstreamer. instead It uses [Soloud](solhsa.com) as its engine.
- convergent: You can use it on other platforms
- blur :)

## installing
### Flatpak
SOON
### Snap
TODO

## building

### deps
[Gempyre](https://github.com/mmertama/Gempyre) `taglib` `qt6` `pyside6` `sdl`

### instructions
```
    mkdir build
    cd build
    cmake -G Ninja ..
    cmake --build . --config Release
```
### Futute plans
- automatic dark-light implementation
- Flatpak Support
- Snap support
- Android
