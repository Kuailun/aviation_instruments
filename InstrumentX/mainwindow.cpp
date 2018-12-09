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
  // m_config = new Config(); // Initializing struct: config

  configuration = new Configuration(); // Initializing page: config
  xmlcontrol = new XMLControl();       // Initializing class: xmlcontrol
  xmlcontrol->SetReferenceConfig(m_config);
  xmlcontrol->SetReferenceConfig(m_Instruments);

  xmlcontrol->ReadFile(); // Read data from XML

  connect(configuration, SIGNAL(SendConfig(Config *)), this,
          SLOT(ReceiveConfig(Config *))); //子窗体回传设置

  SetTimmer();    // Set refresh frequency
  SetRightMenu(); // Set right mouse menu

  initialized = true; // Initialization is finished.

  this->resize(QSize(this->m_config.config_screen.real_width,
                     this->m_config.config_screen.real_height));
  this->move(this->m_config.config_screen.position_x,
             this->m_config.config_screen.position_y);

  debug = 1;
  if (debug) {

    prepareInstrument(Instrument::InstrumentType::IS_Default, "Green", 100,
                      100);
    prepareInstrument(Instrument::InstrumentType::IS_DefaultR, "Red", 700, 100);

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

  addAction(paConfiguration);
  addAction(paDisplayMode);
  addAction(paTitle);
  addAction(paFullScreen);

  connect(paConfiguration, SIGNAL(triggered()), this,
          SLOT(OpenConfiguration()));
  connect(paDisplayMode, SIGNAL(triggered()), this, SLOT(ChangeDisplayMode()));
  connect(paTitle, SIGNAL(triggered()), this, SLOT(ChangeTitleBar()));
  connect(paFullScreen, SIGNAL(triggered()), this, SLOT(ChangeFullScreen()));

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
  // configuration->SetConfig(m_config);
}
void mainwindow::ReceiveConfig(Config *p_config) {
  // m_config = p_config;
  // xmlcontrol->SetDataStruct(m_config); //更新XML数据
  SetTimmer();
}
// Set data to Instrument
void mainwindow::prepareInstrument(Instrument::InstrumentType p_type,
                                   QString p_name, int p_x, int p_y) {
  Instrument *temp_instrument = new Instrument(this);
  temp_instrument->InitialInstrument(p_name, p_type, p_x, p_y);
  temp_instrument->move(p_x, p_y);
  temp_instrument->show();
  connect(temp_instrument, SIGNAL(UpdateXML()), this,
          SLOT(UpdateXML())); // Update the XML File
  m_Instruments.push_back(temp_instrument);
}
void mainwindow::UpdateXML() {
  xmlcontrol->UpdateXML(); // Write XML Data
}
