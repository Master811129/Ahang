[English](README.md) [فارسی](README.persian.md)

# آهنگ
برنامه ی پخش آهنگ

## 🚧هنوز در دست توسعه🚧

Ahang is yet another simple and minimalistic music player like G4Music and Amberol wtitten in C++20. You just select a folder and it shows the musics inside it. Then you click and play. Simple. but there are some key feature that makes it a bit different:

## ویژگی ها
- یک ادبلاکر ساده که نام وبسایت ها رو از روی عنوان موسیقی پنهان می کنه.
- Non Gstreamer: unlike literally almost Every music player in the linux world. this software is not using Gstreamer instead It uses [Soloud](solhsa.com) as its engine.
- تغییر پذیر: یعنی میشه ازش توی سکو های مختلف استفاده کرد.
- چند سکویی: میشه ازش توی پلت فرم های مختلف استفاده کرد (فعلا لینوکس.)
- زمینه ی مات

## نصب
### فلت پک
بزودی...
### اسنپ
قصد دارم

## کامپایل از منبع

### پیش نیاز ها
[Gempyre](https://github.com/mmertama/Gempyre) `taglib` `qt6` `pyside6` `sdl`

### دستورات
```
    mkdir build
    cd build
    cmake -G Ninja ..
    cmake --build . --config Release
```
### برنامه های آینده
- پس زمینه ی روز و شب، همزمان با توجه به تنظیمات سیستم عامل
- پشتیبانی از فلت پک
- پشتیبانی از اسنپ
