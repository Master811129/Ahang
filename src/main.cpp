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
    const char *waylandenv = std::getenv("WAYLAND_DISPLAY");
    setenv("WAYLAND_DISPLAY", "", true);
    std::thread t([waylandenv]{
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
        if(waylandenv!=nullptr)setenv("WAYLAND_DISPLAY", waylandenv, true);
    });
    //TODO maybe an icon manager?

    w.run();
    std::cout << "Back To main():\nCleaning up\n";
    t.join();
    std::cout << "Program has ended successfully✅" <<std::endl;
    return 0;
}
