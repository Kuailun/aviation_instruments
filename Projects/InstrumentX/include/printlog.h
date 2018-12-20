#ifndef PRINTLOG_H
#define PRINTLOG_H

#include <QString>
#include <QDateTime>
#include <QTextStream>
#include <QFile>

enum LogLevel
{
    debugInfo,
    Info,
    Warning,
    Error
};
void PrintLog(LogLevel logLevel,QString s);
void CreateFile(QString fileName);
void DeleteFile();


#endif // PRINTLOG_H
