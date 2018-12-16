//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///		Define the window config page
///
///	\copyright
///		Copyright (C) FYCYC-CreativeHouse - All Rights Reserved
///		Unauthorized copying of this file, via any medium is strictly
/// prohibited 		Proprietary and confidential
//======== ======== ======== ======== ======== ======== ======== ========

#ifndef INSTRUMENTWINDOW_H
#define INSTRUMENTWINDOW_H

#include <QWidget>
#include <instrument.h>

namespace Ui {
class InstrumentWindow;
}

class InstrumentWindow : public QWidget {
  Q_OBJECT

public:
  explicit InstrumentWindow(QWidget *parent = nullptr);
  ~InstrumentWindow();
  void SetReferenceConfig(
      std::vector<Instrument *> &p_data); // Set Data Reference for Instruments
  void UpdateForm(QStringList p_list1, QStringList p_list2);
public slots:
  void ClickButton_Add();
  void ClickButton_Delete();
  void ClickButton_Clear();
signals:
  void SendCommand(int p_func, int p_index); // return command

private:
  Ui::InstrumentWindow *ui;
  void paintEvent(QPaintEvent *event); //绘制事件

  std::vector<Instrument *> *m_instruments;
};

#endif // INSTRUMENTWINDOW_H
