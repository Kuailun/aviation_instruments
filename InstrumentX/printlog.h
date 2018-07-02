#ifndef PRINTLOG_H
#define PRINTLOG_H

#include <QString>
#include <QDateTime>
#include <QTextStream>
#include <QFile>

void PrintLog(QString s);
void CreateFile(QString fileName);
void DeleteFile();

#endif // PRINTLOG_H
