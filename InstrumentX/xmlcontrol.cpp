//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///		Used to read and write xml files
///
///	\copyright
///		Copyright (C) FYCYC-CreativeHouse - All Rights Reserved
///		Unauthorized copying of this file, via any medium is strictly
/// prohibited 		Proprietary and confidential
//======== ======== ======== ======== ======== ======== ======== ========

#include "xmlcontrol.h"
#include "printlog.h"

XMLControl::XMLControl() {}
void XMLControl::CreateFile(QString fileName) {
  QFile file(fileName);
  file.open(QIODevice::ReadWrite);
  QDomDocument doc;
  QDomProcessingInstruction instruction;
  instruction = doc.createProcessingInstruction(
      "xml", "version=\"1.0\" encoding=\"utf-8\"");
  doc.appendChild(instruction);
  QDomElement root = doc.createElement("config");

  doc.appendChild(root);
  QDomText text = doc.createTextNode("");
  root.appendChild(text);

  QTextStream out(&file);
  doc.save(out, 4);
  file.close();
}
void XMLControl::WriteFile() {
  QString fileName = "config.xml";
  QFile file(fileName);
  if (!file.exists(fileName)) {
    PrintLog(LogLevel::Info, "No Existing XML File"); // Log to the file
    CreateFile(fileName);
    PrintLog(LogLevel::Info, "Creating XML File"); // Log to the file
  }
  file.open(QIODevice::WriteOnly);
  QXmlStreamWriter xmlWriter(&file);

  QDomDocument doc;
  QDomProcessingInstruction instruction;
  instruction = doc.createProcessingInstruction(
      "xml", "version=\"1.0\" encoding=\"utf-8\"");
  doc.appendChild(instruction);
  QDomElement root = doc.createElement("config");
  doc.appendChild(root);

  // server address
  QDomElement itemm = doc.createElement("server");
  QDomElement itemmm, itemmm4;
  QDomText textt;
  itemm.setAttribute("name", m_config->config_server);
  root.appendChild(itemm);

  // Full screen
  itemm = doc.createElement("fullscreen");
  itemm.setAttribute("value", QString::number(m_config->config_fullscreen, 10));
  root.appendChild(itemm);

  // Display border
  itemm = doc.createElement("showBorder");
  itemm.setAttribute("value", QString::number(m_config->config_showBorder, 10));
  root.appendChild(itemm);

  // Allow remote shutting down
  itemm = doc.createElement("allowShutdown");
  itemm.setAttribute("value",
                     QString::number(m_config->config_allowShutdown, 10));
  root.appendChild(itemm);

  // Stay on top
  itemm = doc.createElement("stayOnTop");
  itemm.setAttribute("value", QString::number(m_config->config_stayOnTop, 10));
  root.appendChild(itemm);

  // Screen data
  itemm = doc.createElement("screen");
  itemmm = doc.createElement("x");
  textt = doc.createTextNode(
      QString::number(m_config->config_screen.position_x, 10));
  itemmm.appendChild(textt);
  itemm.appendChild(itemmm);

  itemmm = doc.createElement("y");
  textt = doc.createTextNode(
      QString::number(m_config->config_screen.position_y, 10));
  itemmm.appendChild(textt);
  itemm.appendChild(itemmm);

  itemmm = doc.createElement("width");
  textt = doc.createTextNode(
      QString::number(m_config->config_screen.real_width, 10));
  itemmm.appendChild(textt);
  itemm.appendChild(itemmm);

  itemmm = doc.createElement("height");
  textt = doc.createTextNode(
      QString::number(m_config->config_screen.real_height, 10));
  itemmm.appendChild(textt);
  itemm.appendChild(itemmm);

  root.appendChild(itemm);

  // Instrument Data
  itemm = doc.createElement("instrument_number");
  itemm.setAttribute("value",
                     QString::number(m_config->config_instruNumber, 10));
  root.appendChild(itemm);

  // Instrument Data in details
  itemm = doc.createElement("instrument_details");
  for (int i = 0; i < m_instruments->size(); i++) {
    itemmm = doc.createElement("instrument");
    itemmm4 = doc.createElement("x");
    textt = doc.createTextNode(
        QString::number((*m_instruments)[i]->position_x, 10));
    itemmm4.appendChild(textt);
    itemmm.appendChild(itemmm4);

    itemmm4 = doc.createElement("y");
    textt = doc.createTextNode(
        QString::number((*m_instruments)[i]->position_y, 10));
    itemmm4.appendChild(textt);
    itemmm.appendChild(itemmm4);

    itemmm4 = doc.createElement("ratio");
    textt = doc.createTextNode(
        QString::number((*m_instruments)[i]->o2r_ratio, 10, 3));
    itemmm4.appendChild(textt);
    itemmm.appendChild(itemmm4);

    itemmm4 = doc.createElement("type");
    textt = doc.createTextNode(QString::number((*m_instruments)[i]->type, 10));
    itemmm4.appendChild(textt);
    itemmm.appendChild(itemmm4);

    itemm.appendChild(itemmm);
  }
  root.appendChild(itemm);

  // Drawing frequency
  itemm = doc.createElement("frameRate");
  itemm.setAttribute("value", QString::number(m_config->config_frameRate, 10));
  root.appendChild(itemm);

  // Fetching data frequency
  itemm = doc.createElement("dataRate");
  itemm.setAttribute("value", QString::number(m_config->config_dataRate, 10));
  root.appendChild(itemm);

  QTextStream out(&file);
  doc.save(out, 4);
  file.close();
}
Config XMLControl::ReadFile() {
  QString fileName = "config.xml";
  QFile file(fileName);

  // If no existing file then create it
  if (!file.exists(fileName)) {
    PrintLog(LogLevel::Info, "No Existing XML File"); // Log to the file
    CreateFile(fileName);
    PrintLog(LogLevel::Info, "Creating XML File"); // Log to the file
    WriteFile();
  } else {
    // Read the file
    file.open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(&file);
    QDomElement root = doc.documentElement();
    if (root.tagName() != "config") {
      WriteFile();
    }
    QDomNode n = root.firstChild();
    while (!n.isNull()) {
      QDomElement e = n.toElement();
      if (!e.isNull()) {
        if (e.nodeName() == "server") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              m_config->config_server = tmpMap.item(i).nodeValue();
            }
          }
        } else if (e.nodeName() == "fullscreen") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_fullscreen =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "showBorder") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_showBorder =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "allowShutdown") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_allowShutdown =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "stayOnTop") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_stayOnTop =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "frameRate") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_frameRate =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "screen") {
          if (e.hasChildNodes()) {
            QDomNodeList screenlist = e.childNodes();
            for (int i = 0; i < (int)screenlist.size(); i++) {
              if (screenlist.at(i).toElement().tagName() == "x") {
                bool ok;
                m_config->config_screen.position_x =
                    screenlist.at(i).toElement().text().toInt(&ok, 10);
              } else if (screenlist.at(i).toElement().tagName() == "y") {
                bool ok;
                m_config->config_screen.position_y =
                    screenlist.at(i).toElement().text().toInt(&ok, 10);
              } else if (screenlist.at(i).toElement().tagName() == "width") {
                bool ok;
                m_config->config_screen.real_width =
                    screenlist.at(i).toElement().text().toInt(&ok, 10);
              } else if (screenlist.at(i).toElement().tagName() == "height") {
                bool ok;
                m_config->config_screen.real_height =
                    screenlist.at(i).toElement().text().toInt(&ok, 10);
              }
            }
          }
        } else if (e.nodeName() == "dataRate") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_dataRate =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "instrment_number") {
          if (e.hasAttributes()) {
            QDomNamedNodeMap tmpMap = e.attributes();
            for (int i = 0; i < (int)tmpMap.size(); i++) {
              bool ok;
              m_config->config_instruNumber =
                  tmpMap.item(i).nodeValue().toInt(&ok, 10);
            }
          }
        } else if (e.nodeName() == "instrument_details") {
          if (e.hasChildNodes()) {
            QDomNode qd = e.firstChild();
            while (!qd.isNull()) {
              QDomElement ee = qd.toElement();
              if (!ee.isNull()) {
                if (ee.nodeName() == "instrument") {
                  if (ee.hasChildNodes()) {
                    QDomNodeList instrumentlist = ee.childNodes();
                    instrumentData *temp_data = new instrumentData();
                    for (int j = 0; j < (int)instrumentlist.size(); j++) {
                      if (instrumentlist.at(j).toElement().tagName() == "x") {
                        bool ok;
                        temp_data->position_x =
                            instrumentlist.at(j).toElement().text().toInt(&ok,
                                                                          10);
                      } else if (instrumentlist.at(j).toElement().tagName() ==
                                 "y") {
                        bool ok;
                        temp_data->position_y =
                            instrumentlist.at(j).toElement().text().toInt(&ok,
                                                                          10);
                      } else if (instrumentlist.at(j).toElement().tagName() ==
                                 "ratio") {
                        temp_data->o2r_ratio =
                            instrumentlist.at(j).toElement().text().toDouble();
                      } else if (instrumentlist.at(j).toElement().tagName() ==
                                 "type") {
                        bool ok;
                        temp_data->type =
                            instrumentlist.at(j).toElement().text().toInt(&ok,
                                                                          10);
                      }
                    }
                    m_config->m_instrumentData.push_back(temp_data);
                  }
                }
              }
              qd = qd.nextSiblingElement();
            }
          }
        }
      }
      n = n.nextSiblingElement();
    }
  }
  return *m_config;
}
void XMLControl::SetInstrumentData(
    const std::vector<Instrument *> *p_data) // Prepare the instrument data
{
  *(this->m_instruments) = *p_data;
}
void XMLControl::SetReferenceConfig(Config &p_data) {
  this->m_config = &p_data;
}
void XMLControl::SetReferenceConfig(std::vector<Instrument *> &p_data) {
  this->m_instruments = &p_data;
}
void XMLControl::UpdateXML() { WriteFile(); }
