#include <gempyre.h>
#include "mainwindow.hpp"
#include "resources.h"
#include <chrono>
#include <cstdlib>
#include <thread>

int main (int argc, char **argv)
{
    //Gempyre::set_debug();
    mywindow w(Resourcesh,"index.html","Ahang",1152,648);
    //Qt6 is a bit quirky when it comes to wayland so i disabled it
    setenv("QT_QPA_PLATFORM", "xcb", true);
    //TODO maybe an icon manager?
    w.run();
    std::cout << "Back To main():\nCleaning up\n";
    std::cout << "Program has ended successfully✅" <<std::endl;
    return 0;
}
