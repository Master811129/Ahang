#include "gempyre.h"
#include "mainwindow.hpp"
#include <print>


int main (int argc, char **argv)
{
    //Gempyre::set_debug(true);
    mywindow w("index.html","Ahang",1152,614);    
    //Qt6 is a bit quirky when it comes to wayland so i disabled it
    //putenv(const_cast<char *>("QT_QPA_PLATFORM=xcb"));
    //TODO maybe an icon manager?
    if(argc > 1)
    {
        w.index_songs_on_ui(argv[1]);
    }
    w.run();
    std::println("Back To main():\nCleaning up\n");
    std::println("Program has ended successfully✅");
    return 0;
}
