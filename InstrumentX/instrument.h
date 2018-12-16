

#ifndef Instrument_H
#define Instrument_H

#include <QAction>
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
  void InitialInstrument(int p_index, int p_width, int p_height);
  void
  SetReferenceConfig(const Config &p_data); // Set Data Reference for Config
  void
  SetDisplayData(const DisplayData &p_data); // Set Data Reference for Display
  void SetID(int p_id) { this->id = p_id; }  // Set Instrument ID
  int GetID() { return this->id; }           // Get Instrument ID
  void SetName(QString p_name) { this->m_instrumentName = p_name; }
  QString GetName() { return this->m_instrumentName; } // Get Instrument Name
  void Destroy(); // Destroy and close Instrument;

  int position_x = 100;
  int position_y = 100;
  int type = 0;
  double o2r_ratio = 1;

protected:
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void wheelEvent(QWheelEvent *event);
  virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
  void paintEvent(QPaintEvent *event);

  bool mMoving = false;
  QPoint mMovePosition;
  const Config *m_config;
  const DisplayData *m_displaydata;

  int m_runningMode = RunningMode::Running; // Running mode
  QString m_instrumentName = "Default";     // Window title
  int original_width = 1000;
  int original_height = 1000;
  int real_width = 1000;
  int real_height = 1013;
  int id = -1;

  inline int X(int p_x) { return p_x * o2r_ratio; }
  inline int Y(int p_y) { return p_y * o2r_ratio + 13; }
  inline int W(int p_w) { return (original_width - p_w) * o2r_ratio; }
  inline int H(int p_h) { return (original_height - p_h) * o2r_ratio; }

signals:
  void UpdateXML();                 // Update the XML File
  void DestroyInstrument(int p_id); // Tell mainwindow to destroy the instrument
};

#endif // Instrument_H
