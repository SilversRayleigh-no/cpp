#include "WidgetManager.h"

WidgetManager::WidgetManager(ICallbackInterface *cb, QObject *parent) : m_cb{cb}, QObject(parent)
{
    qDebug() <<"create instance WidgetManager";
}
