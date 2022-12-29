#include "AppHostEngine.h"

AppHostEngine* AppHostEngine::m_instance = nullptr;

AppHostEngine::AppHostEngine(QGuiApplication *parent)
    : mApp{parent}, mPluginCardManager{nullptr}, mRootView{nullptr}
{
    qDebug() << "create instance AppHostEngine object";
}

AppHostEngine *AppHostEngine::getInstance(QGuiApplication *app){
    if(m_instance == nullptr){
        m_instance = new AppHostEngine(app);
    }
    return m_instance;
}

void AppHostEngine::init(){
    initViewer();
    mPluginCardManager = new PluginCardManager(mRootView, mApp);
    mRootView->rootContext()->setContextProperty("AW_Screen", mPluginCardManager->getPluginCard());

    mRootView->show();
}

void AppHostEngine::initViewer(){
    mRootView = new QQuickView;
    mRootView->rootContext()->setContextProperty("AW_Screen", nullptr);
    mRootView->setSource(QUrl::fromLocalFile("/home/gen5/qml-cpp/AppHost/qml/main.qml"));
}

int AppHostEngine::exec(){
    if(mApp != nullptr){
        return mApp->exec();
    }
    return -1;
}


