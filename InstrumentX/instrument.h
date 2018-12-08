#ifndef Instrument_H
#define Instrument_H

#include "internaldata.h"
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QMouseEvent>
#include <QPainter>

class Instrument : public QDialog {
  Q_OBJECT

public:
  Instrument(QWidget *parent = 0);
  ~Instrument();

  enum RunningMode { Running, Setting };
  enum InstrumentType { IS_Default, IS_DefaultR };

  void SetDisplayMode(RunningMode rm); // Set running mode
  void InitialInstrument(QString p_name, InstrumentType p_type, int p_x,
                         int p_y);

protected:
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void wheelEvent(QWheelEvent *event);

private:
  void paintEvent(QPaintEvent *event);
  // void resizeEvent(QResizeEvent *event);

  bool mMoving = false;
  QPoint mMovePosition;

  int m_runningMode = RunningMode::Running;           // Running mode
  QString m_instrumentName = "Default";               // Window title
  InstrumentType m_type = InstrumentType::IS_Default; // Instrument Type
  struct windowData m_window;                         // Window data
  double m_ratio = 1; // Window Size Ratio to oringinal

  int demo_x = 0;
  int demo_y = 0;
};

#endif // Instrument_H
