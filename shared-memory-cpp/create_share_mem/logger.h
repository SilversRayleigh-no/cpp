#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>
#define LOG qDebug() << "[2]" << "[" << Q_FUNC_INFO <<"][" << __LINE__ << "]"
#endif // LOGGER_H
