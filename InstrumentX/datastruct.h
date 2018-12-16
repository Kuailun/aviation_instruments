#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <Qstring>
#include <vector>

struct instrumentData {
  int position_x = 100;
  int position_y = 100;
  int original_width = 1000;
  int original_height = 1000;
  int real_width = 1000;
  int real_height = 1013;
  double o2r_ratio = 1;
  int type = 0;
};

struct Config {
  QString config_server = "127.0.0.1";
  int config_fullscreen = 0;
  int config_showBorder = 1;
  int config_allowShutdown = 0;
  int config_stayOnTop = 0;
  int config_instruNumber = 0;
  instrumentData config_screen;
  std::vector<instrumentData *> m_instrumentData;
  int config_frameRate = 30;
  int config_dataRate = 10;
};

struct DisplayData {
  double demo_x = 0; // data for test
  double demo_y = 0; // data for test
};

#endif // DATASTRUCT_H
