#include "mainwindow.hpp"

int main (int argc, char **argv)
{
    mywindow w("index.html","Ahang",1152,614);    
    //Qt6 is a bit quirky when it comes to wayland so i disabled it
    //putenv(const_cast<char *>("QT_QPA_PLATFORM=xcb"));
    //TODO maybe an icon manager?
    if(argc > 1)
    {
        w.index_songs_on_ui(argv[1]);
    }
    w.run();
    std::cout << "Back To main():\nCleaning up\n";
    std::cout << "Program has ended successfully✅" << std::endl;
    return 0;
}
