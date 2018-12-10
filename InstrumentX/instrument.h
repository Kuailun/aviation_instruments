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
  void InitialInstrument(int p_index);
  void
  SetReferenceConfig(const Config &p_data); // Set Data Reference for Config

  int position_x = 100;
  int position_y = 100;
  int type = 0;
  double o2r_ratio = 1;

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
  const Config *m_config;

  int m_runningMode = RunningMode::Running; // Running mode
  QString m_instrumentName = "Default";     // Window title
  int demo_x = 0;
  int demo_y = 0;
  int original_width = 1000;
  int original_height = 1000;
  int real_width = 1000;
  int real_height = 1013;

signals:
  void UpdateXML(); // Update the XML File
};

#endif // Instrument_H
