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

class Config
{
public:
    Config();

    QString config_server="127.0.0.1";
    int config_fullscreen=0;
    int config_showBorder=1;
    int config_allowShutdown=0;
    int config_stayOnTop=0;
    screen config_screen;
    int config_frameRate=30;
    int config_dataRate=10;

};

#endif // DATASTRUCT_H
