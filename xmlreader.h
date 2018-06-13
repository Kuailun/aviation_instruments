#ifndef XMLREADER_H
#define XMLREADER_H
#include <QFile>
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QXmlStreamWriter>


class XMLReader
{
public:
    XMLReader();
    void WriteFile();
    void ReadFile();
private:
    void CreateFile(QString fileName);
};

#endif // XMLREADER_H
