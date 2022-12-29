#include "MyWidget.h"

MyWidget* MyWidget::m_instance = nullptr;

MyWidget *MyWidget::getInstance(int scrType){
    if(m_instance == nullptr){
        m_instance = new MyWidget(scrType);
    }
    return m_instance;
}

MyWidget::MyWidget(int scrType, QObject *parent): QObject(parent)
{
    qDebug() << "create instance my widget to shared";
    m_qmlComponent = nullptr;
    m_parent = nullptr;
    m_callback = nullptr;
}

void MyWidget::initialize(ICallbackInterface *cb){
    qDebug() << "my widget initialize function";
    m_callback = cb;
}

// đóng gói main qml của widget
QQmlComponent* MyWidget::getComponent() {
    qDebug() << "return component for widget";
    m_parent = m_callback->getRootObject(); // assistant window call getRootObject
    if(m_parent == nullptr){
        qDebug() << "return null component widget";
        return nullptr;
    }

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    // đóng gói widget component
    if(m_qmlComponent == nullptr){
        QQmlEngine* engine = qmlEngine(m_parent); // return 1 engine mà liên kết với m_parent
        qDebug() << "engine widget: " << engine->rootContext();
        if(engine){
            engine->rootContext()->setContextProperty("MyWidgetAW", this);
//            engine->rootContext()->setContextProperty("widget_context", QString("widget context"));
            m_qmlComponent = new QQmlComponent(engine, QUrl::fromLocalFile("/home/gen5/qml-cpp/AppWidgetPlugin/MyWidget/qml/main.qml"), this);
        }
    }
    qDebug() << m_qmlComponent->url().toString();
    return m_qmlComponent == nullptr ? nullptr : m_qmlComponent;
}

//QString MyWidget::getString(){
//    return m_str;
//}

//void MyWidget::setString(QString str){
//    qDebug() << "my widget " << str;
//    m_str = str;
//}

MyWidgetInterface* getObject(int scrType){
    return MyWidget::getInstance(scrType);
}
