#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "datastruct.h"
#include <QMainWindow>
#include <QPainter>

namespace Ui {
class Configuration;
}

class Configuration : public QMainWindow {
  Q_OBJECT

public:
  explicit Configuration(QWidget *parent = 0);
  void SetConfig(Config *p_config);
  ~Configuration();

private:
  Ui::Configuration *ui;
  Config *m_config;
  void paintEvent(QPaintEvent *event); //绘制事件

signals:
  void SendConfig(Config *p_config); //回传设置

protected:
  void closeEvent(QCloseEvent *event);
};

#endif // CONFIGURATION_H
