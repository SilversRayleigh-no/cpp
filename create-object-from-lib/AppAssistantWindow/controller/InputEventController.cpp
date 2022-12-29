#include "InputEventController.h"

InputEventController::InputEventController(QQuickView *view) : m_ParentViewer{view} {
    qDebug() << "an instance InputEventController create";
}
