//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///		Used to define configuration page
///
///	\copyright
///		Copyright (C) FYCYC-CreativeHouse - All Rights Reserved
///		Unauthorized copying of this file, via any medium is strictly
/// prohibited 		Proprietary and confidential
//======== ======== ======== ======== ======== ======== ======== ========
#include "./include/configuration.h"
#include "ui_configuration.h"

Configuration::Configuration(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Configuration) {
  this->setFixedSize(800, 600);
  ui->setupUi(this);
}

Configuration::~Configuration() { delete ui; }
void Configuration::SetConfig(Config &p_config) {
  m_config = &p_config;

  ui->configuration_server->setText(m_config->config_server);
  ui->configuration_datarate->setText(
      QString::number(m_config->config_dataRate, 10));
  ui->configuration_framerate->setText(
      QString::number(m_config->config_frameRate, 10));
}
void Configuration::closeEvent(QCloseEvent *event) {
  (void)event;
  bool ok;
  m_config->config_server = ui->configuration_server->text();
  m_config->config_dataRate = ui->configuration_datarate->text().toInt(&ok, 10);
  m_config->config_frameRate =
      ui->configuration_framerate->text().toInt(&ok, 10);
  emit SendConfig();
}
void Configuration::paintEvent(QPaintEvent *event) {
  (void)event;

  QPainter painter(this);
  painter.fillRect(QRect(0, 10, this->width(), this->height()),
                   QBrush(QColor(240, 240, 240))); // Set background color
}
