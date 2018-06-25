#include "xmlcontrol.h"

XMLControl::XMLControl()
{
    m_config=new Config();
}
void XMLControl::CreateFile(QString fileName)
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
void XMLControl::WriteFile()
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
    QDomElement itemmm;
    QDomText textt;
    itemm.setAttribute("name",m_config->config_server);
    root.appendChild(itemm);

    //全屏
    itemm=doc.createElement("fullscreen");
    itemm.setAttribute("value",QString::number(m_config->config_fullscreen,10));
    root.appendChild(itemm);

    //显示边框
    itemm=doc.createElement("showBorder");
    itemm.setAttribute("value",QString::number(m_config->config_showBorder,10));
    root.appendChild(itemm);

    //允许远程关闭
    itemm=doc.createElement("allowShutdown");
    itemm.setAttribute("value",QString::number(m_config->config_allowShutdown,10));
    root.appendChild(itemm);

    //始终置顶
    itemm=doc.createElement("stayOnTop");
    itemm.setAttribute("value",QString::number(m_config->config_stayOnTop,10));
    root.appendChild(itemm);

    //屏幕数据
    itemm=doc.createElement("screen");
    itemmm=doc.createElement("x");
    textt=doc.createTextNode(QString::number(m_config->config_screen.data_x,10));
    itemmm.appendChild(textt);
    itemm.appendChild(itemmm);

    itemmm=doc.createElement("y");
    textt=doc.createTextNode(QString::number(m_config->config_screen.data_y,10));
    itemmm.appendChild(textt);
    itemm.appendChild(itemmm);

    itemmm=doc.createElement("width");
    textt=doc.createTextNode(QString::number(m_config->config_screen.data_width,10));
    itemmm.appendChild(textt);
    itemm.appendChild(itemmm);

    itemmm=doc.createElement("height");
    textt=doc.createTextNode(QString::number(m_config->config_screen.data_height,10));
    itemmm.appendChild(textt);
    itemm.appendChild(itemmm);

    root.appendChild(itemm);

    //绘制速率
    itemm=doc.createElement("frameRate");
    itemm.setAttribute("value",QString::number(m_config->config_frameRate,10));
    root.appendChild(itemm);

    //数据速率
    itemm=doc.createElement("dataRate");
    itemm.setAttribute("value",QString::number(m_config->config_dataRate,10));
    root.appendChild(itemm);


    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}
Config* XMLControl::ReadFile()
{
    QString fileName="config.xml";
    QFile file(fileName);
    //若无该文件则生成文件并返回默认值
    if(!file.exists(fileName))
    {
        //生成文件
        CreateFile(fileName);
        WriteFile();
    }
    else
    {
        //读取文件
        file.open(QIODevice::ReadOnly);
        QDomDocument doc;
        doc.setContent(&file);
        QDomElement root=doc.documentElement();
        if(root.tagName()!="config")
        {
            WriteFile();
        }
        QDomNode n=root.firstChild();
        while(!n.isNull())
        {
            QDomElement e=n.toElement();
            if(!e.isNull())
            {
                if(e.nodeName()=="server")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            m_config->config_server=tmpMap.item(i).nodeValue();
                        }
                    }
                }
                else if(e.nodeName()=="fullscreen")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            bool ok;
                            m_config->config_fullscreen=tmpMap.item(i).nodeValue().toInt(&ok,10);
                        }
                    }
                }
                else if(e.nodeName()=="showBorder")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            bool ok;
                            m_config->config_showBorder=tmpMap.item(i).nodeValue().toInt(&ok,10);
                        }
                    }
                }
                else if(e.nodeName()=="allowShutdown")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            bool ok;
                            m_config->config_allowShutdown=tmpMap.item(i).nodeValue().toInt(&ok,10);
                        }
                    }
                }
                else if(e.nodeName()=="stayOnTop")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            bool ok;
                            m_config->config_stayOnTop=tmpMap.item(i).nodeValue().toInt(&ok,10);
                        }
                    }
                }
                else if(e.nodeName()=="frameRate")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            bool ok;
                            m_config->config_frameRate=tmpMap.item(i).nodeValue().toInt(&ok,10);
                        }
                    }
                }
                else if(e.nodeName()=="screen")
                {
                    if(e.hasChildNodes())
                    {
                        QDomNodeList screenlist=e.childNodes();
                        for(int i=0;i<(int)screenlist.size();i++)
                        {
                            if(screenlist.at(i).toElement().tagName()=="x")
                            {
                                bool ok;
                                m_config->config_screen.data_x=screenlist.at(i).toElement().text().toInt(&ok,10);
                            }
                            else if(screenlist.at(i).toElement().tagName()=="y")
                            {
                                bool ok;
                                m_config->config_screen.data_y=screenlist.at(i).toElement().text().toInt(&ok,10);
                            }
                            else if(screenlist.at(i).toElement().tagName()=="width")
                            {
                                bool ok;
                                m_config->config_screen.data_width=screenlist.at(i).toElement().text().toInt(&ok,10);
                            }
                            else if(screenlist.at(i).toElement().tagName()=="height")
                            {
                                bool ok;
                                m_config->config_screen.data_height=screenlist.at(i).toElement().text().toInt(&ok,10);
                            }
                        }
                    }
                }
                else if(e.nodeName()=="dataRate")
                {
                    if(e.hasAttributes())
                    {
                        QDomNamedNodeMap tmpMap=e.attributes();
                        for(int i=0;i<(int)tmpMap.size();i++)
                        {
                            bool ok;
                            m_config->config_dataRate=tmpMap.item(i).nodeValue().toInt(&ok,10);
                        }
                    }
                }

            }
            n=n.nextSiblingElement();
        }

    }
    return this->m_config;
}
void XMLControl::SetDataStruct(Config* p_datastruct)
{
    this->m_config=p_datastruct;
    WriteFile();
}
