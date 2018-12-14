#include "instrumentwindow.h"
#include "ui_instrumentwindow.h"
#include <QPainter>
#include <QStringListModel>

InstrumentWindow::InstrumentWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::InstrumentWindow) {
  this->setFixedSize(800, 600);
  ui->setupUi(this);
}

InstrumentWindow::~InstrumentWindow() { delete ui; }
void InstrumentWindow::paintEvent(QPaintEvent *event) {
  (void)event;

  QPainter painter(this);
  painter.fillRect(QRect(0, 10, this->width(), this->height()),
                   QBrush(QColor(240, 240, 240))); // Set background color
}
void InstrumentWindow::SetReferenceConfig(
    std::vector<Instrument *> &p_data) // Set Data Reference for Instruments
{
  m_instruments = &p_data;
}
void InstrumentWindow::UpdateForm(QStringList p_list1, QStringList p_list2) {
  QStringListModel *model1, *model2;

  model1 = new QStringListModel(this);
  model1->setStringList(p_list1);
  model2 = new QStringListModel(this);
  model2->setStringList(p_list2);
  ui->listView_Available->setModel(model1);
  ui->listView_Exist->setModel(model2);
}
