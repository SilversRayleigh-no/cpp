#include <QGuiApplication>
#include "AssistantEngine.h"
#include <csignal>

void signal_handler(int signal_num)
{
    qDebug() << "The interrupt signal is (" << signal_num << "). \n";

    // It terminates the  program
    exit(signal_num);
}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, signal_handler);
    QGuiApplication a(argc, argv);

    AssistantEngine* assis_engine = AssistantEngine::getInstance();
    assis_engine->init_widget();
    assis_engine->getWidget()->loadWidget("/app/plugins/MyWidgetPlugin/libMyWidgetPlugin");
    assis_engine->getWidget()->installWidget();
    assis_engine->init_viewer();

    assis_engine->init_inputController();
//    QQmlComponent* comp = assis_engine->getWidget()->getComponentWidget();
//    if(comp == nullptr){
//        qDebug() << "null component";
//    }
//    QObject* obj = comp->create(assis_engine->getEngine()->rootContext());
    return a.exec();
}
