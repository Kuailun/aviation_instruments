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

  SetTimmer();    // Set refresh frequency
  SetRightMenu(); // Set right mouse menu

  initialized = true; // Initialization is finished.

  this->resize(QSize(this->m_config.config_screen.real_width,
                     this->m_config.config_screen.real_height));
  this->move(this->m_config.config_screen.position_x,
             this->m_config.config_screen.position_y);
  SetInstrument(); // Restore Instrument;

  debug = 0;
  if (debug) {
    instrumentData temp_data;
    temp_data.type = 0;
    temp_data.o2r_ratio = 1;
    temp_data.position_x = 100;
    temp_data.position_y = 100;
    m_config.m_instrumentData.push_back(&temp_data);
    prepareInstrument(100, 100, 0);

    instrumentData temp_dataa;
    temp_dataa.type = 1;
    temp_dataa.o2r_ratio = 1;
    temp_dataa.position_x = 700;
    temp_dataa.position_y = 100;
    m_config.m_instrumentData.push_back(&temp_dataa);
    prepareInstrument(700, 100, 1);

  } else {
  }
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
void mainwindow::SetTimmer() {
  if (initialized && timer != nullptr && timer->isActive()) {
    timer->stop();
    delete timer;
  }
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start((int)(1000 / m_config.config_frameRate));
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
  SetTimmer();
}
// Set data to Instrument
void mainwindow::prepareInstrument(int p_x, int p_y, int p_index) {
  Instrument *temp_instrument = new Instrument(this);
  temp_instrument->SetReferenceConfig(m_config);
  temp_instrument->InitialInstrument(p_index, Datalist[p_index].original_width,
                                     Datalist[p_index].original_height);
  temp_instrument->SetName(Namelist[p_index]);
  temp_instrument->move(p_x, p_y);
  temp_instrument->show();
  temp_instrument->SetID(m_Instruments.size());
  connect(temp_instrument, SIGNAL(UpdateXML()), this,
          SLOT(UpdateXML())); // Update the XML File
  connect(temp_instrument, SIGNAL(DestroyInstrument(int)), this,
          SLOT(DestroyIS(int))); // Destroy Instrument
  m_Instruments.push_back(temp_instrument);
  m_config.config_instruNumber = m_Instruments.size();
}
void mainwindow::UpdateXML() {
  xmlcontrol->UpdateXML(); // Write XML Data
}
void mainwindow::DestroyIS(int p_id) {
  delete m_Instruments[p_id];
  m_Instruments[p_id] = NULL;
  for (int i = p_id; i < m_Instruments.size() - 1; i++) {
    m_Instruments[i] = m_Instruments[i + 1];
    m_Instruments[i]->SetID(i);
  }
  m_Instruments.erase(m_Instruments.begin() + m_Instruments.size() - 1);
  UpdateWindow();
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
}
void mainwindow::initialData() {
  Namelist[0] = "IS_Default";
  Namelist[1] = "IS_DefaultR";

  Datalist[0].o2r_ratio = 1;
  Datalist[0].original_width = 500;
  Datalist[0].original_height = 500;
  Datalist[0].type = 0;

  Datalist[1].o2r_ratio = 1;
  Datalist[1].original_width = 500;
  Datalist[1].original_height = 500;
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
