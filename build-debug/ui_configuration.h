/********************************************************************************
** Form generated from reading UI file 'configuration.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATION_H
#define UI_CONFIGURATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Configuration
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *configuration_server;
    QFrame *line;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QCheckBox *checkBox;
    QGroupBox *groupBox_4;
    QLineEdit *configuration_datarate;
    QLabel *label_2;
    QLineEdit *configuration_framerate;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Configuration)
    {
        if (Configuration->objectName().isEmpty())
            Configuration->setObjectName(QStringLiteral("Configuration"));
        Configuration->resize(800, 600);
        centralwidget = new QWidget(Configuration);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 291, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 54, 16));
        configuration_server = new QLineEdit(groupBox);
        configuration_server->setObjectName(QStringLiteral("configuration_server"));
        configuration_server->setGeometry(QRect(72, 30, 121, 20));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(300, 0, 20, 561));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 90, 291, 71));
        groupBox_2->setFont(font);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 170, 291, 71));
        groupBox_3->setFont(font);
        checkBox = new QCheckBox(groupBox_3);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 37, 141, 21));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 250, 291, 231));
        groupBox_4->setFont(font);
        configuration_datarate = new QLineEdit(groupBox_4);
        configuration_datarate->setObjectName(QStringLiteral("configuration_datarate"));
        configuration_datarate->setGeometry(QRect(130, 40, 121, 20));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 91, 16));
        configuration_framerate = new QLineEdit(groupBox_4);
        configuration_framerate->setObjectName(QStringLiteral("configuration_framerate"));
        configuration_framerate->setGeometry(QRect(130, 70, 121, 20));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 91, 16));
        Configuration->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Configuration);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Configuration->setMenuBar(menubar);
        statusbar = new QStatusBar(Configuration);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Configuration->setStatusBar(statusbar);

        retranslateUi(Configuration);

        QMetaObject::connectSlotsByName(Configuration);
    } // setupUi

    void retranslateUi(QMainWindow *Configuration)
    {
        Configuration->setWindowTitle(QApplication::translate("Configuration", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Configuration", "InstrumentX Server", Q_NULLPTR));
        label->setText(QApplication::translate("Configuration", "Server", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Configuration", "General Options", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Configuration", "Interface", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Configuration", "Stay on top", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Configuration", "Tuning", Q_NULLPTR));
        label_2->setText(QApplication::translate("Configuration", "Data rate", Q_NULLPTR));
        label_3->setText(QApplication::translate("Configuration", "Frame rate", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Configuration: public Ui_Configuration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATION_H
