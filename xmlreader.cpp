#include "xmlreader.h"

XMLReader::XMLReader()
{

}
void XMLReader::CreateFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(instruction);
    QDomElement root=doc.createElement("config");

    doc.appendChild(root);
    QDomText text=doc.createTextNode("");
    root.appendChild(text);

    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}
void XMLReader::WriteFile()
{
    QString fileName="config.xml";
    QFile file(fileName);
    if(!file.exists(fileName))
    {
        CreateFile(fileName);
    }
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(instruction);
    QDomElement root=doc.createElement("config");
    doc.appendChild(root);

    //服务器名称
    QDomElement itemm=doc.createElement("server");
    itemm.setAttribute("name","127.0.0.1");
    root.appendChild(itemm);

    //全屏
    itemm=doc.createElement("fullscreen");
    itemm.setAttribute("value","false");
    root.appendChild(itemm);

    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}
void XMLReader::ReadFile()
{
    QString fileName="config.xml";
    QFile file(fileName);
    if(!file.exists(fileName))
    {
        CreateFile(fileName);
    }
}
