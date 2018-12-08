#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <Qstring>

struct instrument {
  int position_x = 100;
  int position_y = 100;
  int original_width = 1000;
  int original_height = 1000;
  int real_width = 1000;
  int real_height = 1013;
  int o2r_ratio = 1;
};

struct Config {
  QString config_server = "127.0.0.1";
  int config_fullscreen = 0;
  int config_showBorder = 1;
  int config_allowShutdown = 0;
  int config_stayOnTop = 0;
  instrument config_screen;
  int config_frameRate = 30;
  int config_dataRate = 10;
};

#endif // DATASTRUCT_H
