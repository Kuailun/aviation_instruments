#ifndef XMLCONTROL_H
#define XMLCONTROL_H
#include <QFile>
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "datastruct.h"
#include <QString>


class XMLControl
{
public:
    XMLControl();
    DataStruct* ReadFile();
    void SetDataStruct(DataStruct* p_datastruct);
private:
    DataStruct *datastruct;
    void CreateFile(QString fileName);
    void WriteFile();
};

#endif // XMLCONTROL_H
