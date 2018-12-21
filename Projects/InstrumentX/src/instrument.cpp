#include "./include/instrument.h"

Instrument::Instrument(QWidget *parent) : QDialog(parent) {
  setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  hide();
}

Instrument::~Instrument() {}
void Instrument::paintEvent(QPaintEvent *event) {
  (void)event;
  QPainter painter(this);

  switch (type) {
  case Instrument::InstrumentType::IS_Default: {
    painter.fillRect(QRect(X(0), Y(0), W(0), H(0)), QBrush(Qt::green));
    painter.fillRect(QRect(static_cast<int>(X(m_displaydata->demo_x)),
                           static_cast<int>(Y(m_displaydata->demo_y)),
                           static_cast<int>(30 * o2r_ratio),
                           static_cast<int>(30 * o2r_ratio)),
                     QBrush(Qt::blue));
    break;
  }
  case Instrument::InstrumentType::IS_DefaultR:
    painter.fillRect(QRect(X(0), Y(0), W(0), H(0)), QBrush(Qt::red));
    break;

  case Instrument::InstrumentType::IS_SpeedIndicator: {
    painter.drawImage(QRect(X(0), Y(0), W(0), H(0)),
                      QImage(":/image/image/Speed_Indicator.png"));

    painter.save();
    QPixmap pix(":/image/image/Indicator.png");
    painter.translate(X(250), Y(250));
    painter.rotate(m_displaydata->Speed_Indicator_Speed);
    painter.translate(X(-250), Y(-250));
    painter.drawPixmap(X(237), Y(0), Wi(25), H(0), pix);
    painter.restore();
    break;
  }
  }

  // if in the setting mode
  if (m_runningMode ==
      RunningMode::Setting) // Display window name when in moving mode
  {
    painter.setPen(QPen(Qt::green, 3)); // Display green stroke
    painter.drawRect(QRect(1, 13, this->width() - 3, this->height() - 15));
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);
    QString str;
    str = str.append(m_instrumentName);
    str = str.append("-");
    str = str.append(QString::number(id, 10));
    painter.drawText(QPoint(0, 10), str);
  }
}

void Instrument::mousePressEvent(QMouseEvent *event) {
  (void)event;
  if (m_runningMode == RunningMode::Setting) {
    mMoving = true;
  }
  //记录下鼠标相对于窗口的位置
  // event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
  // pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
  mMovePosition = event->globalPos() - pos();
  return QDialog::mousePressEvent(event);
}
void Instrument::mouseMoveEvent(QMouseEvent *event) {
  //(event->buttons() && Qt::LeftButton)按下是左键
  //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
  //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
  if (mMoving && (event->buttons() && Qt::LeftButton) &&
      (event->globalPos() - mMovePosition).manhattanLength() >
          QApplication::startDragDistance()) {
    move(event->globalPos() - mMovePosition);
    mMovePosition = event->globalPos() - pos();
  }
  return QDialog::mouseMoveEvent(event);
}
void Instrument::mouseReleaseEvent(QMouseEvent *event) {
  (void)event;
  mMoving = false;

  position_x = this->x();
  position_y = this->y();
  emit UpdateXML();
}
// Wheel Event
void Instrument::wheelEvent(QWheelEvent *event) {
  if (mMoving) {
    if (event->delta() > 0 && o2r_ratio <= 4) {
      o2r_ratio = o2r_ratio + 0.01;
    } else if (event->delta() < 0 && o2r_ratio >= 0.5) {
      o2r_ratio = o2r_ratio - 0.01;
    }
    this->real_width = static_cast<int>(o2r_ratio * original_width);
    this->real_height = static_cast<int>(o2r_ratio * original_height + 13);
    this->resize(real_width, real_height);
  }
}
void Instrument::SetDisplayMode(RunningMode rm) { this->m_runningMode = rm; }

// Set variable to Instrument
void Instrument::InitialInstrument(int p_index, int p_width, int p_height) {
  p_index = 0; // silence the warning
  this->type = m_config->m_instrumentData[id]->type;
  this->position_x = m_config->m_instrumentData[id]->position_x;
  this->position_y = m_config->m_instrumentData[id]->position_y;
  this->o2r_ratio = m_config->m_instrumentData[id]->o2r_ratio;

  this->original_width = p_width;
  this->original_height = p_height;

  this->real_width = static_cast<int>(o2r_ratio * original_width);
  this->real_height = static_cast<int>(o2r_ratio * original_height + 13);
  this->resize(real_width, real_height);
}
void Instrument::SetReferenceConfig(
    const Config &p_data) // Set Data Reference for Config
{
  m_config = &p_data;
}
void Instrument::SetDisplayData(const DisplayData &p_data) {
  m_displaydata = &p_data;
}
void Instrument::mouseDoubleClickEvent(QMouseEvent *event) {
  (void)event;
  Destroy();
  emit DestroyInstrument(this->id);
}
void Instrument::Destroy() {}
