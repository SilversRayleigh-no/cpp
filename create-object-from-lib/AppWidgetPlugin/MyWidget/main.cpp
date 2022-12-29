#include <QGuiApplication>
#include "MyWidget.h"
int main(int argc, char *argv[])
{
    QGuiApplication gui(argc, argv);
    MyWidgetInterface* mwidget = new MyWidget(&gui);

    return gui.exec();
}
