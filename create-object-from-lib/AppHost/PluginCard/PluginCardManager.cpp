#include "PluginCardManager.h"

PluginCardManager::PluginCardManager(QQuickView *rootview, QObject *parent)
    : m_QQmlComponent{nullptr}, m_pPluginCardIface{nullptr}
{
    qDebug() << "create instance PluginCardManager object";
    initializePluginCard(rootview, parent);
}

QQmlComponent *PluginCardManager::getPluginCard(){
    return m_QQmlComponent;
}

bool PluginCardManager::initializePluginCard(QQuickView *rootview, QObject *parent) {
    bool ret = false;
    if(load() == true){
        m_pPluginCardIface->initializePluginCard(rootview, parent);
        m_QQmlComponent = m_pPluginCardIface->getPluginCard();
        ret = true;
    }
    qDebug() << "ret: " << ret;
    return ret;
}

bool PluginCardManager::load() {
    qDebug() << "load aw";
    CARDiface func = nullptr;
    m_lib.setFileName("/app/plugins/AssistantWindow/libAppAssistantWindow");
    qDebug() << "lib name: " << m_lib.fileName();

    if(m_lib.load()){
        qDebug() << "load success";
    }
    else{
        qDebug() << m_lib.errorString();
    }

    func = (CARDiface)m_lib.resolve("getAWObject");
    if(!func){
        qDebug() << m_lib.errorString();
        m_lib.unload();
        return false;
    }

    m_pPluginCardIface = (*func)(4);
    if(!m_pPluginCardIface){
        m_lib.unload();
    }
    return (m_pPluginCardIface != NULL);
}
