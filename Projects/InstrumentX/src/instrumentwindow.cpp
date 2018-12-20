#include "./include/instrumentwindow.h"
#include "ui_instrumentwindow.h"
#include <QPainter>
#include <QStringListModel>

InstrumentWindow::InstrumentWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::InstrumentWindow) {
  this->setFixedSize(800, 600);
  ui->setupUi(this);
  connect(ui->pushButton_Add, SIGNAL(clicked()), this, SLOT(ClickButton_Add()));
  connect(ui->pushButton_Delete, SIGNAL(clicked()), this,
          SLOT(ClickButton_Delete()));
  connect(ui->pushButton_Clear, SIGNAL(clicked()), this,
          SLOT(ClickButton_Clear()));
}

InstrumentWindow::~InstrumentWindow() { delete ui; }
void InstrumentWindow::paintEvent(QPaintEvent *event) {
  (void)event;

  QPainter painter(this);
  painter.fillRect(QRect(0, 10, this->width(), this->height()),
                   QBrush(QColor(240, 240, 240))); // Set background color
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
void InstrumentWindow::ClickButton_Add() {
  QItemSelectionModel *selmodel = ui->listView_Available->selectionModel();
  QModelIndexList indexs = selmodel->selectedRows();
  if (indexs.size() <= 0) {
    return;
  }
  int index = indexs[0].row();
  emit SendCommand(0, index);
}
void InstrumentWindow::ClickButton_Clear() { emit SendCommand(2, -1); }
void InstrumentWindow::ClickButton_Delete() {
  QItemSelectionModel *selmodel = ui->listView_Exist->selectionModel();
  QModelIndexList indexs = selmodel->selectedRows();
  if (indexs.size() <= 0) {
    return;
  }
  int index = indexs[0].row();
  emit SendCommand(1, index);
}
