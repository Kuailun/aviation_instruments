#ifndef Instrument_H
#define Instrument_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QMouseEvent>
#include <QPainter>
#include <datastruct.h>

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
  instrumentData GetInstrumentData() { return this->m_instrument; }

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

  int m_runningMode = RunningMode::Running; // Running mode
  QString m_instrumentName = "Default";     // Window title
  instrumentData m_instrument;              // Instrument Data

  int demo_x = 0;
  int demo_y = 0;

signals:
  void UpdateXML(); // Update the XML File
};

#endif // Instrument_H
