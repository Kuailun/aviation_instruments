//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///		Used to print out log information
///
///	\copyright
///		Copyright (C) FYCYC-CreativeHouse - All Rights Reserved
///		Unauthorized copying of this file, via any medium is strictly prohibited
///		Proprietary and confidential
//======== ======== ======== ======== ======== ======== ======== ========


#include "printlog.h"

void PrintLog(LogLevel logLevel,QString s)
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

    //print out according to logLevel
    switch(logLevel)
    {
        case LogLevel::debugInfo:
        text_stream<<current_date_time<<"--Debug     :  "<<s<<"\r\n";
            break;
        case LogLevel::Info:
        text_stream<<current_date_time<<"--Info      :  "<<s<<"\r\n";
            break;
        case LogLevel::Warning:
        text_stream<<current_date_time<<"--Warning   :  "<<s<<"\r\n";
            break;
        case LogLevel::Error:
        text_stream<<current_date_time<<"--Error     :  "<<s<<"\r\n";
            break;
        default:
        text_stream<<current_date_time<<"--Warning   :  "<<"Wrong print code"<<"\r\n";
            break;
    }
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
