#ifndef XMLCONTROL_H
#define XMLCONTROL_H
#include <QFile>
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "datastruct.h"
#include <QString>
#include <QDebug>


class XMLControl
{
public:
    XMLControl();
    Config* ReadFile();
    void SetDataStruct(Config* p_datastruct);
private:
    Config *m_config;
    void CreateFile(QString fileName);
    void WriteFile();
};

#endif // XMLCONTROL_H
