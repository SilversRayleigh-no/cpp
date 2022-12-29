#ifndef INPUTEVENTCONTROLLER_H
#define INPUTEVENTCONTROLLER_H
#include <QObject>
#include <QQuickView>
#include <QDebug>
#include <QGuiApplication>
class InputEventController : public QObject
{
    Q_OBJECT
public:
    explicit InputEventController(QQuickView* view = nullptr);
protected:
    bool eventFilter(QObject *obj, QEvent *e) override{
//        qDebug() << "function eventFilter";
        if(e->type() == QEvent::MouseButtonPress){
            qDebug() << "event filter mouse press";
            return true;
        }
        QKeyEvent* keyE = static_cast<QKeyEvent*>(e);
        if(keyE->key() == Qt::Key_Escape){
            qDebug() << "event filter key esc";
            return true;
        }
        return false;
    }

private:
    QQuickView* m_ParentViewer;
};

#endif // INPUTEVENTCONTROLLER_H
