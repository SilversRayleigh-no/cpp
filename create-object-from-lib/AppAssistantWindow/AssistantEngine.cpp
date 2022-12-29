#include "AssistantEngine.h"
#include <QThread>
AssistantEngine* AssistantEngine::m_instance = nullptr;

PluginCardInterface* getAWObject(int scrType){
    return AssistantEngine::getInstance(scrType);
}

AssistantEngine::AssistantEngine(int _scrType)
    : m_pQmlComponent{nullptr}, m_pWidget{nullptr}, m_pInputEvtCtrl{nullptr}, m_pRootView{nullptr}
{
    qDebug() << "create instance AssistantEngine object";
}

AssistantEngine *AssistantEngine::getInstance(int _scrType){
    if(m_instance == nullptr){
        m_instance = new AssistantEngine(_scrType);
    }
    return m_instance;
}

QQmlContext *AssistantEngine::getRootContext() {
    return m_pRootView->rootContext();
}

QQuickItem *AssistantEngine::getRootObject() {
    if(m_pRootView->rootObject() == nullptr){
        return nullptr;
    }
    return qobject_cast<QQuickItem*>(m_pRootView->rootObject());
}

QQmlComponent *AssistantEngine::getPluginCard() {
    // object qml app host
    if(m_pRootView->rootObject() == nullptr) {
        qDebug() << " root item app host is null";
        return nullptr;
    }
    if(m_pQmlComponent == nullptr){
        QQmlEngine* engine = qmlEngine(m_pRootView->rootObject());
        if(engine != nullptr){
            try{
                m_pQmlComponent = new QQmlComponent (engine, "/home/gen5/qml-cpp/AppAssistantWindow/qml/main.qml");
            }
            catch(std::bad_alloc &msg){
                qDebug() << "bad alloc: " << msg.what();
                m_pQmlComponent = nullptr;
            }
        }
    }
    return m_pQmlComponent;
}

bool AssistantEngine::initializePluginCard(QQuickView *rootView, QObject* parent) {
    Q_UNUSED(parent);
    qDebug() << "initializePluginCard aw";
    init_widget(4);
    m_pRootView = rootView;

    m_pWidget->loadWidget("/app/plugins/MyWidgetPlugin");
    m_pWidget->installWidget();

    m_pRootView->rootContext()->setContextProperty("screen_widget", m_pWidget->getComponentWidget());
    m_pRootView->rootContext()->setContextProperty("widget_context", QString("general context"));

    init_inputController();
}

void AssistantEngine::init_widget(int _scrType){
    if(m_pWidget == nullptr){
        qDebug() << "init_widget";
        m_pWidget = new WidgetManager(AssistantEngine::getInstance(_scrType));
    }
}

WidgetManager *AssistantEngine::getWidget(){
    return m_pWidget;
}

void AssistantEngine::init_inputController(){
    if(m_pInputEvtCtrl == nullptr){
        m_pInputEvtCtrl = new InputEventController(m_pRootView);
    }

    if(m_pInputEvtCtrl){
        qDebug() << "install event filter m_pInputEvtCtrl";
        m_pRootView->installEventFilter(m_pInputEvtCtrl);
    }
}
