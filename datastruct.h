#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <Qstring>


struct screen
{
    int data_x=100;
    int data_y=100;
    int data_width=1600;
    int data_height=900;
};

class DataStruct
{
public:
    DataStruct();

    QString data_server="127.0.0.1";
    int data_fullscreen=0;
    int data_showBorder=1;
    int data_allowShutdown=0;
    int data_stayOnTop=0;
    screen data_screen;
    int data_frameRate=30;
    int data_dataRate=10;

};

#endif // DATASTRUCT_H
