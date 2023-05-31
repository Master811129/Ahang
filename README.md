[[English](README.md)]  [[فارسی](README.persian.md)]

# Ahang
Ahang is a simple music player.


Ahang is yet another simple and minimalistic music player like G4Music and Amberol wtitten in modern C++. You just select a folder and it shows the musics inside it. Then you click and play. Simple. but there are some key feature that makes it a bit different:

## Key Features
- built-in AdBlocker for songs that put website names on audio tags: So people that download for free won't be bothered.
- Non Gstreamer: unlike literally almost every music player in the Linux world, this software doesn't use Gstreamer. instead, It uses [Soloud](solhsa.com) as its engine.
- convergent: You can use it on other platforms
- blur :)

## installing
### Flatpak
*SOON*
### Snap
*TODO*

## building

### deps

[Gempyre](https://github.com/mmertama/Gempyre) `taglib` `qt6` `pyside6` `sdl` 
___
### Linux
For Ubuntu/Debian based it will be: `sudo apt install libsdl2-dev libtag1-dev libtag-extras-dev`

note that the build system is cmake and I only tested it with snap version of Ubuntu. So It's better to use the snap version. 

`snap install cmake`

For Arch-based it will be: `sudo pacman -S taglib sdl2 ninja`

also using `ninja` is optional 
___
### Windows 8,10,11
#### Using Mingw

make sure that you have Gempyre and run this.

`pacman -S libtag`
___
### instructions
```
    mkdir build
    cd build
    cmake -G Ninja ..
    cmake --build . --config Release
```
___

## Futute plans
- automatic dark-light implementation.
- Flatpak Support
- Snap support
- Android

## Buy me a pizza🍕
Monero: 47ME2ogosZGNJV89SaBPiSNkqExVwbpK5UBb7Kp73WXmgJxXsQdniGtBD5VRf48rZH6UksNCntRoP6XvHGeW1mBs1rFW7s1

ETH: 0xd8F3200BF4728D77E2F26448caE97c8e132e71C1

Thanks