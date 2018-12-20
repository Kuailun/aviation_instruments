#include "./include/msocket.h"
#include "ui_msocket.h"
#include <QJsonObject>
#include <QJsonParseError>

mSocket::mSocket(QWidget *parent) : QWidget(parent), ui(new Ui::mSocket) {
  ui->setupUi(this);
  m_socket = new QUdpSocket();
  m_socket->bind(1011);
  connect(m_socket, SIGNAL(readyRead()), this, SLOT(ProcessPending()));
}

mSocket::~mSocket() { delete ui; }
void mSocket::Process() {
  m_calculated_displaydata->demo_x +=
      Confine(m_displaydata_new->demo_x, m_displaydata_last->demo_x,
              m_calculated_displaydata->demo_x, 10);
  m_calculated_displaydata->demo_y +=
      Confine(m_displaydata_new->demo_y, m_displaydata_last->demo_y,
              m_calculated_displaydata->demo_y, 10);
}
void mSocket::ProcessPending() {
  m_displaydata_last->demo_x = m_displaydata_new->demo_x;
  m_displaydata_last->demo_y = m_displaydata_new->demo_y;

  m_displaydata_new->demo_x = m_receiveData.degree_pitch;
  m_displaydata_new->demo_y = m_receiveData.degree_bank;

  QByteArray datagram;
  do {
    datagram.resize(m_socket->pendingDatagramSize());
    m_socket->readDatagram(datagram.data(), datagram.size());
    ParseJson(&datagram);
  } while (m_socket->hasPendingDatagrams());
}
double mSocket::Confine(double p_new, double p_last, double p_cal,
                        double p_scale) {
  m_onepiece = (p_new - p_last) / interval;
  if (m_onepiece > 0 && (p_cal + m_onepiece) <= p_new) {
    return m_onepiece > p_scale ? p_scale : m_onepiece;
  } else if (m_onepiece > 0 && (p_cal - m_onepiece) >= p_new) {
    return m_onepiece > p_scale ? -p_scale : -m_onepiece;
  } else if (m_onepiece < 0 && (p_cal + m_onepiece) >= p_new) {
    return m_onepiece < -p_scale ? -p_scale : m_onepiece;
  } else if (m_onepiece < 0 && (p_cal - m_onepiece) <= p_new) {
    return -m_onepiece > p_scale ? p_scale : -m_onepiece;
  } else {
    return 0;
  }
}
void mSocket::ParseJson(QByteArray *p_data) {
  QJsonParseError jsonError;
  QJsonDocument document = QJsonDocument::fromJson(*p_data, &jsonError);
  if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
    if (document.isObject()) {
      QJsonObject object = document.object();
      m_receiveData.degree_pitch =
          ParseDouble(object, "degree_pitch", m_receiveData.degree_pitch);
      m_receiveData.degree_bank =
          ParseDouble(object, "degree_bank", m_receiveData.degree_bank);
    }
  }
}
QString mSocket::ParseString(QJsonObject p_o, QString p_data,
                             QString p_oringinal) {
  if (p_o.contains(p_data)) {
    QJsonValue value = p_o.value(p_data);
    if (value.isString()) {
      return value.toString();
    }
  }
  return p_oringinal;
}
double mSocket::ParseDouble(QJsonObject p_o, QString p_data,
                            double p_oringinal) {
  if (p_o.contains(p_data)) {
    QJsonValue value = p_o.value(p_data);
    if (value.isDouble()) {
      return value.toVariant().toDouble();
    }
  }
  return p_oringinal;
}
bool mSocket::ParseBool(QJsonObject p_o, QString p_data, bool p_oringinal) {
  if (p_o.contains(p_data)) {
    QJsonValue value = p_o.value(p_data);
    if (value.isBool()) {
      return value.toBool();
    }
  }
  return p_oringinal;
}
