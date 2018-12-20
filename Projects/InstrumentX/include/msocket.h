#ifndef MSOCKET_H
#define MSOCKET_H

#include <./include/datastruct.h>
#include <QTimer>
#include <QWidget>
#include <QtNetwork/QUdpSocket>

namespace Ui {
class mSocket;
}

class mSocket : public QWidget {
  Q_OBJECT

public:
  explicit mSocket(QWidget *parent = nullptr);
  ~mSocket();
  void SetConfig(Config &p_config) { m_config = &p_config; }
  void SetDisplayData(DisplayData &p_new, DisplayData &p_last,
                      DisplayData &p_data) {
    m_displaydata_new = &p_new;
    m_displaydata_last = &p_last;
    m_calculated_displaydata = &p_data;
  }
  void SetInterval(double p_data) { interval = p_data; }
  void Process(); //绘制事件

private:
  Ui::mSocket *ui;
  Config *m_config;
  DisplayData *m_displaydata_new;
  DisplayData *m_displaydata_last;
  DisplayData *m_calculated_displaydata;
  ReceiveData m_receiveData;
  QUdpSocket *m_socket;
  double m_onepiece;
  double interval = 3;
  double inline Confine(double p_new, double p_last, double p_cal,
                        double p_scale);
  void ParseJson(QByteArray *p_data);
  QString ParseString(QJsonObject p_o, QString p_data, QString p_oritinal);
  double ParseDouble(QJsonObject p_o, QString p_data, double p_oritinal);
  bool ParseBool(QJsonObject p_o, QString p_data, bool p_oritinal);
private slots:
  void ProcessPending();
};

#endif // MSOCKET_H
