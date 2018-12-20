#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "configuration.h"
#include "instrument.h"
#include "instrumentwindow.h"
#include "printlog.h"
#include "xmlcontrol.h"
#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include <vector>

class mainwindow : public QMainWindow {
  Q_OBJECT
public:
  explicit mainwindow(QWidget *parent = nullptr);
signals:

private slots:
  void ChangeDisplayMode();                     //变换显示模式
  void ChangeTitleBar();                        //变换标题栏
  void ChangeFullScreen();                      //变换全屏模式
  void OpenConfiguration();                     //打开设置界面
  void OpenWindows();                           // Open windows page
  void ReceiveConfig();                         //更新设置
  void ReceiveCommand(int p_func, int p_index); // Receive command from window
  void UpdateXML();                             // Update the XML file
  void DestroyIS(int p_id);                     // Destroy the Instrument
  void GetDisplayData();                        // Get Display Data
private:
  //数据区域
  Config m_config;
  std::vector<Instrument *> m_Instruments;
  DisplayData m_displaydata_new;
  DisplayData m_displaydata_last;
  DisplayData m_calculated_displaydata;
#define types 2
  QString Namelist[types];
  instrumentData Datalist[types];
  // XML记录+显示变量区
  XMLControl *xmlcontrol; // XML读写类

  //内部变量区

  Configuration *configuration;
  InstrumentWindow *instrumentwindow;
  int debug = 0;            // 0=Running，1=Debugging
  int mode = 0;             // 0=RunningMode::Running，1=RunningMode::Setting
  bool initialized = false; // Flag, whether initialization is finished
  QTimer *timer_display;    // Timer for update screen

  //内部功能函数

  //内部响应函数
  void paintEvent(QPaintEvent *event);   //绘制事件
  void resizeEvent(QResizeEvent *event); //缩放窗口事件
  void moveEvent(QMoveEvent *event);     //移动窗口事件
  void SetRightMenu();                   //设置鼠标右键菜单
  void SetTimmer_Display();              //设置重绘时钟
  void SetInstrument();                  // Restore Instrument
  void keyPressEvent(QKeyEvent *event);  //快捷键设置
  void prepareInstrument(int p_x, int p_y, int p_index);
  void initialData();  // Initial Instrument base data
  void UpdateWindow(); // Update data in window

protected:
  void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
