[English](README.md) [فارسی](README.persian.md)

# آهنگ
برنامه ی پخش آهنگ

## 🚧هنوز در دست توسعه🚧

Ahang is yet another simple and minimalistic music player like G4Music and Amberol wtitten in C++20. You just select a folder and it shows the musics inside it. Then you click and play. Simple. but there are some key feature that makes it a bit different:

## ویژگی ها
- built in AdBlocker for songs that put website names on audio tags: So people that download for free won't be bothered.
- Non Gstreamer: unlike literally almost Every music player in the linux world. this software is not using Gstreamer instead It uses [Soloud](solhsa.com) as its engine.
- convergent: you can use it on other platforms
- blur :)

## نصب
### Flatpak
بزودی...
### Snap
TODO

## building

### deps
Gempyre `taglib` `qt6` `pyside6` `sdl`

### instructions
```
    mkdir build
    cd build
    cmake -G Ninja ..
    cmake --build . --config Release
```
### برنامه های آینده
- automatic dark-light implementation
- Flatpak Support
- Snap support
