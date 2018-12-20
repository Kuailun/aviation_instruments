#ifndef XMLCONTROL_H
#define XMLCONTROL_H
#include "./include/datastruct.h"
#include <./include/instrument.h>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QtXml/QDomDocument>

class XMLControl {
public:
  XMLControl();
  Config ReadFile();
  void SetInstrumentData(
      const std::vector<Instrument *> *p_data); // Prepare the instrument data
  void SetReferenceConfig(Config &p_data);      // Set Data Reference for Config
  void SetReferenceConfig(
      std::vector<Instrument *> &p_data); // Set Data Reference for Instruments
  void UpdateXML();                       // Write XML Data to the file

private:
  Config *m_config;
  std::vector<Instrument *> *m_instruments;
  void CreateFile(QString fileName);
  void WriteFile();
};

#endif // XMLCONTROL_H
