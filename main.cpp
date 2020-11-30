#include "OfficeDesk.h"
#include "graphAPI.h"
#include "custom_framelistener.h"
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create window
    OfficeDesk desk;
    desk.show();

    //paint
    graphAPI new_graphAPI;
    std::thread thread1(&graphAPI::readMvx, &new_graphAPI, &desk);//

    return a.exec();
}