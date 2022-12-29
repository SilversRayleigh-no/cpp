#include "AppHostEngine.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    AppHostEngine* engine = AppHostEngine::getInstance(&a);
    engine->init();

    engine->exec();
}
