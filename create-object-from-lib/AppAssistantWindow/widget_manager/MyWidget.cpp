#include "MyWidget.h"

WidgetPlugin::WidgetPlugin(QString pluginFolder)
{
    m_widgetObj = nullptr;
    qDebug() << "create instance WidgetPlugin plugin: " << pluginFolder;
}

//QString WidgetPlugin::getString(){
//    return m_widgetObj->getString();
//}

//void WidgetPlugin::setString(QString str){
//    m_widgetObj->setString(str);
//}

bool WidgetPlugin::loadPlugin(){
    GetObjectFunction func;
    m_lib.setFileName("/app/plugins/MyWidgetPlugin/libMyWidgetPlugin");
    qDebug() << "lib name: " << m_lib.fileName();

    if(m_lib.load()){
        qDebug() << "load success";
    }
    else{
        qDebug() << m_lib.errorString();
    }

    func = (GetObjectFunction)m_lib.resolve("getObject");
    if(!func){
        qDebug() << m_lib.errorString();
        m_lib.unload();
        return false;
    }
    m_widgetObj = (*func)(4);
    if(!m_widgetObj){
        m_lib.unload();
    }
    return (m_widgetObj != NULL);
}
