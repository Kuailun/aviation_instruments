#include "printlog.h"

void PrintLog(QString s)
{
    QString current_date_time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString fileName="log.txt";
    QFile file(fileName);
    if(!file.exists(fileName))
    {
        CreateFile(fileName);
    }
    file.open(QIODevice::WriteOnly);
    QTextStream text_stream(&file);
    text_stream<<current_date_time<<"  :  "<<s<<"\r\n";
    file.flush();
    file.close();
}
void CreateFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
}
void DeleteFile()
{
    QString fileName="log.txt";
    QFile file(fileName);
    if(!file.exists(fileName))
    {
        CreateFile(fileName);
    }
    file.open(QIODevice::WriteOnly);
    QFile::remove("/log.txt");
}
