//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///		Container of all windows
///
///	\copyright
///		Copyright (C) FYCYC-CreativeHouse - All Rights Reserved
///		Unauthorized copying of this file, via any medium is strictly
/// prohibited 		Proprietary and confidential
//======== ======== ======== ======== ======== ======== ======== ========

#include "mainwindow.h"
#include "instrument.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent) {
  DeleteFile();                              // Delete log.txt if exist
  PrintLog(LogLevel::Info, "start program"); // Log to the file

  //===== ===== ===== ===== ===== Initializing ===== ===== ===== ===== ===== //
  this->setWindowTitle("FYCYC-Aviation Instruments X"); // Set window title

  initialData();

  configuration = new Configuration(); // Initializing page: config
  configuration->SetConfig(m_config);
  xmlcontrol = new XMLControl(); // Initializing class: xmlcontrol
  xmlcontrol->SetReferenceConfig(m_config);
  xmlcontrol->SetReferenceConfig(m_Instruments);
  instrumentwindow = new InstrumentWindow(); // Initillizing page: window

  xmlcontrol->ReadFile(); // Read data from XML

  connect(configuration, SIGNAL(SendConfig()), this,
          SLOT(ReceiveConfig())); //子窗体回传设置
  connect(instrumentwindow, SIGNAL(SendCommand(int, int)), this,
          SLOT(ReceiveCommand(int, int))); // Receive data from page

  SetTimmer_Display(); // Set refresh frequency
  SetRightMenu();      // Set right mouse menu

  initialized = true; // Initialization is finished.

  this->resize(QSize(this->m_config.config_screen.real_width,
                     this->m_config.config_screen.real_height));
  this->move(this->m_config.config_screen.position_x,
             this->m_config.config_screen.position_y);
  SetInstrument(); // Restore Instrument;
}
void mainwindow::paintEvent(QPaintEvent *event) {
  (void)event; //去掉报警信息

  QPainter painter(this);
  //设置背景颜色
  if (mode == 0) {
    painter.fillRect(QRect(0, 0, this->width(), this->height()),
                     QBrush(Qt::black));
  } else if (mode == 1) {
    painter.fillRect(QRect(0, 0, this->width(), this->height()),
                     QBrush(Qt::blue));
  }
}
void mainwindow::resizeEvent(QResizeEvent *event) {
  (void)event; //去掉报警信息

  m_config.config_screen.real_height = this->height();
  m_config.config_screen.real_width = this->width();
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::moveEvent(QMoveEvent *event) {
  (void)event; //去掉报警信息

  m_config.config_screen.position_x = this->x();
  m_config.config_screen.position_y = this->y();
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::SetRightMenu() {
  QAction *paConfiguration = new QAction("Configuration", this);
  QAction *paDisplayMode = new QAction("Display Mode    F12", this);
  QAction *paTitle = new QAction("TitleBar", this);
  QAction *paFullScreen = new QAction("FullScreen      F11", this);
  QAction *paWindow = new QAction("Windows", this);

  addAction(paConfiguration);
  addAction(paDisplayMode);
  addAction(paTitle);
  addAction(paFullScreen);
  addAction(paWindow);

  connect(paConfiguration, SIGNAL(triggered()), this,
          SLOT(OpenConfiguration()));
  connect(paDisplayMode, SIGNAL(triggered()), this, SLOT(ChangeDisplayMode()));
  connect(paTitle, SIGNAL(triggered()), this, SLOT(ChangeTitleBar()));
  connect(paFullScreen, SIGNAL(triggered()), this, SLOT(ChangeFullScreen()));
  connect(paWindow, SIGNAL(triggered()), this, SLOT(OpenWindows()));

  setContextMenuPolicy(Qt::ActionsContextMenu);
}
void mainwindow::ChangeDisplayMode() {
  mode = 1 - mode;

  std::vector<Instrument *>::iterator iter;
  iter = m_Instruments.begin();

  switch (mode) {
  case 0: {
    for (int i = 0; i < m_Instruments.size(); i++) {
      (*iter)->SetDisplayMode(Instrument::RunningMode::Running);
      iter++;
    }
  } break;
  case 1: {
    for (int i = 0; i < m_Instruments.size(); i++) {
      (*iter)->SetDisplayMode(Instrument::RunningMode::Setting);
      iter++;
    }
    break;
  }
  default:
    break;
  }
}
void mainwindow::ChangeTitleBar() {
  m_config.config_showBorder = 1 - m_config.config_showBorder;
  if (m_config.config_showBorder == 0) {
    this->setWindowFlags(Qt::FramelessWindowHint);
    show();
  } else {
    this->setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
    show();
  }
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::ChangeFullScreen() {
  m_config.config_fullscreen = 1 - m_config.config_fullscreen;
  if (m_config.config_fullscreen == 0) {
    showNormal();
  } else {
    showFullScreen();
  }
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::SetTimmer_Display() {
  if (initialized && timer_display != nullptr && timer_display->isActive()) {
    timer_display->stop();
    delete timer_display;
  }
  timer_display = new QTimer(this);
  connect(timer_display, SIGNAL(timeout()), this, SLOT(update()));
  timer_display->start((int)(1000 / m_config.config_frameRate));
}
void mainwindow::keyPressEvent(QKeyEvent *event) {
  if (Qt::Key_F12 == event->key()) {
    ChangeDisplayMode();
    return;
  }
  if (Qt::Key_F11 == event->key()) {
    ChangeFullScreen();
    return;
  }
}
void mainwindow::OpenConfiguration() {
  configuration->setWindowTitle("Configuration");
  configuration->SetConfig(m_config);

  configuration->show();
}
void mainwindow::OpenWindows() {
  instrumentwindow->setWindowTitle("Windows");

  UpdateWindow();

  instrumentwindow->show();
}
void mainwindow::ReceiveConfig() {
  // m_config = p_config;
  xmlcontrol->UpdateXML(); //更新XML数据
  SetTimmer_Display();
}
void mainwindow::ReceiveCommand(int p_func, int p_index) {
  switch (p_func) {
  case 0: // add
  {
    instrumentData *temp_data = new instrumentData();
    temp_data->type = p_index;
    temp_data->o2r_ratio = 1;
    temp_data->position_x = 100;
    temp_data->position_y = 100;
    m_config.m_instrumentData.push_back(temp_data);
    prepareInstrument(temp_data->position_x, temp_data->position_y,
                      m_Instruments.size());
  } break;
  case 1: // delete
    DestroyIS(p_index);
    break;
  case 2: // clear
    while (m_Instruments.size() != 0) {
      DestroyIS(0);
    }
    break;
  }
}
// Set data to Instrument
void mainwindow::prepareInstrument(int p_x, int p_y, int p_index) {
  Instrument *temp_instrument = new Instrument(this);
  int type = m_config.m_instrumentData[p_index]->type;
  temp_instrument->SetReferenceConfig(m_config);
  temp_instrument->SetDisplayData(m_calculated_displaydata);
  temp_instrument->SetID(m_Instruments.size());
  temp_instrument->InitialInstrument(type, Datalist[type].original_width,
                                     Datalist[type].original_height);
  temp_instrument->SetName(Namelist[type]);
  temp_instrument->move(p_x, p_y);
  temp_instrument->show();

  connect(temp_instrument, SIGNAL(UpdateXML()), this,
          SLOT(UpdateXML())); // Update the XML File
  connect(temp_instrument, SIGNAL(DestroyInstrument(int)), this,
          SLOT(DestroyIS(int))); // Destroy Instrument
  m_Instruments.push_back(temp_instrument);
  m_config.config_instruNumber = m_Instruments.size();
  UpdateWindow();
}
void mainwindow::UpdateXML() {
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::DestroyIS(int p_id) {
  delete m_Instruments[p_id];
  m_Instruments[p_id] = NULL;
  delete m_config.m_instrumentData[p_id];
  m_config.m_instrumentData[p_id] = NULL;
  for (int i = p_id; i < m_Instruments.size() - 1; i++) {
    m_Instruments[i] = m_Instruments[i + 1];
    m_Instruments[i]->SetID(i);
    m_config.m_instrumentData[i] = m_config.m_instrumentData[i + 1];
  }
  m_Instruments.erase(m_Instruments.begin() + m_Instruments.size() - 1);
  m_config.m_instrumentData.erase(m_config.m_instrumentData.begin() +
                                  m_config.m_instrumentData.size() - 1);
  UpdateWindow();
  m_config.config_instruNumber = m_config.m_instrumentData.size();
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::SetInstrument() {
  for (int i = 0; i < m_config.m_instrumentData.size(); i++) {
    switch (m_config.m_instrumentData[i]->type) {
    case 0:
      prepareInstrument(m_config.m_instrumentData[i]->position_x,
                        m_config.m_instrumentData[i]->position_y, i);
      break;
    case 1:
      prepareInstrument(m_config.m_instrumentData[i]->position_x,
                        m_config.m_instrumentData[i]->position_y, i);
      break;
    }
  }
}
void mainwindow::closeEvent(QCloseEvent *event) {
  (void)event;
  bool ok;
  UpdateXML();

  configuration->hide();
  instrumentwindow->hide();
  delete configuration;
  configuration = NULL;
  delete instrumentwindow;
  instrumentwindow = NULL;
}
void mainwindow::initialData() {
  Namelist[0] = "IS_Default";
  Namelist[1] = "IS_DefaultR";

  Datalist[0].o2r_ratio = 1;
  Datalist[0].original_width = 1500;
  Datalist[0].original_height = 1500;
  Datalist[0].type = 0;

  Datalist[1].o2r_ratio = 1;
  Datalist[1].original_width = 1500;
  Datalist[1].original_height = 1500;
  Datalist[1].type = 0;
}
void mainwindow::UpdateWindow() {
  QStringList m_list_Exist;
  QStringList m_list_Available;
  for (int i = 0; i < m_Instruments.size(); i++) {
    QString str1 = "ID: ";
    QString str2 = QString::number(m_Instruments[i]->GetID(), 10);
    QString str3 = "   ";
    QString str4 = m_Instruments[i]->GetName();

    QString str;
    str = str.append(str1);
    str = str.append(str2);
    str = str.append(str3);
    str = str.append(str4);
    m_list_Exist.push_back(str);
  }

  for (int i = 0; i < types; i++) {
    QString str1 = "Type: ";
    QString str2 = Namelist[i];

    QString str;
    str = str.append(str1);
    str = str.append(str2);
    m_list_Available.push_back(str);
  }
  instrumentwindow->UpdateForm(m_list_Available, m_list_Exist);
  // instrumentwindow->show();
}
void mainwindow::GetDisplayData() {
  count++;
  m_displaydata_last.demo_x = m_displaydata_new.demo_x;
  m_displaydata_last.demo_y = m_displaydata_new.demo_y;

  if (m_displaydata_new.demo_x <= 1500) {
    m_displaydata_new.demo_x += 20;
    m_displaydata_new.demo_y += 20;
  } else {
    m_displaydata_new.demo_x = 0;
    m_displaydata_new.demo_y = 0;
  }
}
